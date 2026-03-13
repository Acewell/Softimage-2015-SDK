///////////////////////////////////////////////////////////////////////////
//
// File: SpotLightCreateTool.cpp
//
// Description: This plugin implements a spotlight creation tool.
//
// The tool can be invoked by typing SpotLightCreateTool at the command
// line or by assigning a hotkey to the SpotLightCreateTool custom script
// command in the keyboard mapping dialog.
//
// To create a spotlight the user clicks at the positon on the visible
// grid where they would like the interest and then drags while holding 
// the mouse down to specify the direction. The elevation of the spotlight
// can be set by holding down the shift key during creation.
//
// The tool will exit after the spotlight has been created.
//
// Copyright 2010 Autodesk, Inc. All rights reserved.
// Use of this software is subject to the terms of the Autodesk license
// agreement provided at the time of installation or download, or which
// otherwise accompanies this software in either electronic or hard copy
// form.
//
///////////////////////////////////////////////////////////////////////////
#ifndef linux
#define WIN32_LEAN_AND_MEAN
#include <windows.h> // Needed for OpenGL on windows
#endif
#include <GL/gl.h>
#include <xsi_pluginregistrar.h>
#include <xsi_application.h>
#include <xsi_context.h>
#include <xsi_status.h>
#include <xsi_argument.h>
#include <xsi_toolcontext.h>
#include <xsi_math.h>
#include <xsi_light.h>
#include <xsi_lightrig.h>
#include <xsi_model.h>
#include <xsi_selection.h>
#include <xsi_kinematics.h>
#include <xsi_kinematicstate.h>
#include <xsi_menu.h>
#include <xsi_menuitem.h>

using namespace XSI; 
using namespace XSI::MATH; 

////////////////////////////////////////////////////////////////////////////////
//
// SpotLightCreateTool class
//
////////////////////////////////////////////////////////////////////////////////

class SpotLightCreateTool {
private: // Data
	LightRig		m_spotRig;			// Spotlight rig
	CPlane			m_gridPlane;		// Visible grid plane
	CPlane			m_manipPlane;		// Manipulation plane
	CVector3		m_vertAxis;			// Vertical axis
	CVector3		m_intPos;			// Interest position
	CVector3		m_lightPos;			// Light position

public: // Methods
	SpotLightCreateTool()
	{}

	~SpotLightCreateTool()
	{}

	CStatus Activate( ToolContext& in_ctxt )
	{
		// Called when tool becomes active
		in_ctxt.SetCursor( siCrossCursor );
		in_ctxt.EnableSnapping( true );
		in_ctxt.SetToolDescription( L"Create SpotLight (hold Shift while dragging to adjust height)\nCreate Spotlight" );
		return CStatus::OK;
	}

	CStatus MouseDown( ToolContext& in_ctxt )
	{
		// Called when mouse button is pressed
		LONG x, y;
		in_ctxt.GetMousePosition( x, y );

		if ( in_ctxt.IsLeftButtonDown() )
		{
			// Use visible grid as default projection (not view plane)
			CPlane l_ViewPlane;
			in_ctxt.GetGridPlane( m_gridPlane );
			in_ctxt.GetViewPlane( l_ViewPlane );
			m_manipPlane = m_gridPlane;
			in_ctxt.SetManipulationPlane( m_manipPlane );
			if ( !m_manipPlane.Parallel( l_ViewPlane ) )
				m_vertAxis = m_manipPlane.GetNormal();
			else
				m_vertAxis.PutNull(); // Normal is orthogonal to view

			// Get projected 3D point
			CVector3 l_Pos;
			if ( in_ctxt.GetWorldPosition( x, y, l_Pos ) == CStatus::OK )
			{
				// Reject points behind the camera
				CVector3 l_cameraPos;
				if ( in_ctxt.WorldToCamera( l_Pos, l_cameraPos ) == CStatus::OK && l_cameraPos.GetZ() < 0.0 )
				{
					// Create a spot light
					Application().GetActiveSceneRoot().AddLightRig( L"Spot", L"SpotLight", m_spotRig );

					if ( m_spotRig.IsValid() )
					{
						// Save information
						m_lightPos = m_intPos = l_Pos;

						// Set initial position
						HideObject( m_spotRig );
						SelectObject( m_spotRig, true/*branch*/ );
						KinematicState interestKine = m_spotRig.GetLight().GetInterest().GetKinematics().GetGlobal();
						interestKine.GetParameter(L"posx").PutValue(l_Pos.GetX());
						interestKine.GetParameter(L"posy").PutValue(l_Pos.GetY());
						interestKine.GetParameter(L"posz").PutValue(l_Pos.GetZ());

						KinematicState lightKine = m_spotRig.GetLight().GetKinematics().GetGlobal();
						Parameter posX = lightKine.GetParameter(L"posx");
						Parameter posY = lightKine.GetParameter(L"posy");
						Parameter posZ = lightKine.GetParameter(L"posz");
						in_ctxt.BeginParameterUpdate( posX );
						in_ctxt.BeginParameterUpdate( posY );
						in_ctxt.BeginParameterUpdate( posZ );
						in_ctxt.UpdateParameter( posX, l_Pos.GetX() );
						in_ctxt.UpdateParameter( posY, l_Pos.GetY() );
						in_ctxt.UpdateParameter( posZ, l_Pos.GetZ() );
						return CStatus::OK;
					}
				}
			}
		}
		return CStatus::False; // Ignore other mouse buttons etc.
	}

	CStatus MouseDrag( ToolContext& in_ctxt )
	{
		// Called when mouse is moved with a mouse button pressed
		LONG x, y;
		in_ctxt.GetMousePosition( x, y );

		if ( in_ctxt.IsLeftButtonDown() )
		{
			if (!in_ctxt.IsShiftKeyDown() || m_vertAxis.GetLengthSquared() < MicroEPS)
			{
				// Move in plane
				in_ctxt.SetCursor( siCrossCursor );

				CVector3 l_Pos;
				in_ctxt.EnableSnapping( true );
				if ( in_ctxt.GetWorldPosition( x, y, l_Pos ) != CStatus::OK )
					return CStatus::OK;

				// Reject points behind the camera
				CVector3 l_cameraPos;
				if ( in_ctxt.WorldToCamera( l_Pos, l_cameraPos ) != CStatus::OK || l_cameraPos.GetZ() > 0.0 )
					return CStatus::OK;

				// Update position
				m_lightPos = l_Pos;
			}
			else
			{
				// Calculate vertical offset
				in_ctxt.SetCursor( siDragYCursor );

				CLine l_Ray;
				in_ctxt.EnableSnapping( false );
				if ( in_ctxt.GetWorldRay( x, y, l_Ray ) != CStatus::OK )
					return CStatus::OK;

				// Calculate vertical offset
				CLine l_Vert( m_lightPos, m_vertAxis );
				CVector3 l_Pos = l_Vert.GetClosestPoint( l_Ray );
				CVector3 l_Off = l_Pos; l_Off -= m_lightPos;

				// Update position
				m_lightPos = l_Pos;

				// Update manipulation plane
				CVector3 l_NewOrigin = m_manipPlane.GetOrigin();
				m_manipPlane.SetOrigin( l_NewOrigin += l_Off );
				in_ctxt.SetManipulationPlane( m_manipPlane );
			}

			KinematicState lightKine = m_spotRig.GetLight().GetKinematics().GetGlobal();
			in_ctxt.UpdateParameter( lightKine.GetParameter(L"posx"), m_lightPos.GetX() );
			in_ctxt.UpdateParameter( lightKine.GetParameter(L"posy"), m_lightPos.GetY() );
			in_ctxt.UpdateParameter( lightKine.GetParameter(L"posz"), m_lightPos.GetZ() );
		}
		return CStatus::OK;
	}

	CStatus MouseUp( ToolContext& in_ctxt )
	{
		// Called when mouse button is released
		KinematicState lightKine = m_spotRig.GetLight().GetKinematics().GetGlobal();
		in_ctxt.EndParameterUpdate( lightKine.GetParameter(L"posx") );
		in_ctxt.EndParameterUpdate( lightKine.GetParameter(L"posy") );
		in_ctxt.EndParameterUpdate( lightKine.GetParameter(L"posz") );
		in_ctxt.ExitTool();
		return CStatus::OK;
	}

	CStatus Draw( ToolContext& in_ctxt )
	{
		// Called to draw tool feedback
		if ( in_ctxt.IsInteracting() )
		{
			// Only show feedback during interaction
			CVector3 l_basePos = m_gridPlane.Project( m_lightPos );
			::glColor3d( 0.0, 1.0, 0.0 );
			::glBegin( GL_LINE_LOOP );
			::glVertex3d( m_intPos.GetX(), m_intPos.GetY(), m_intPos.GetZ() );
			::glVertex3d( l_basePos.GetX(), l_basePos.GetY(), l_basePos.GetZ() );
			::glVertex3d( m_lightPos.GetX(), m_lightPos.GetY(), m_lightPos.GetZ() );
			::glEnd();
		}
		return CStatus::OK;
	}

private: // Helper methods

	void HideObject( X3DObject &in_obj )
	{
		Property visibility = in_obj.GetProperties().GetItem(L"Visibility");
		visibility.GetParameter("viewvis").PutValue(CValue(false));
	}

	CValue SelectObject( X3DObject &in_obj, bool in_bBranch )
	{
		CValue result;
		CValueArray args;
		args.Add( in_obj.GetFullName() );
		args.Add( in_bBranch ? L"BRANCH" : L"NODE");
		Application().ExecuteCommand( L"SelectObj", args, result );
		return result;
	}
};


////////////////////////////////////////////////////////////////////////////////
//
// Plugin callbacks
//
////////////////////////////////////////////////////////////////////////////////

SICALLBACK XSILoadPlugin( PluginRegistrar& in_reg )
{
	in_reg.PutAuthor(L"Autodesk");
	in_reg.PutName(L"SpotLightCreateTool Plugin");
	in_reg.PutVersion(1,0);
	in_reg.RegisterTool(L"SpotLightCreateTool");
	in_reg.RegisterMenu(siMenuTbGetLightID, L"SpotLightCreateMenu", false, false);
	//RegistrationInsertionPoint - do not remove this line
	return CStatus::OK;
}

SICALLBACK SpotLightCreateMenu_Init( CRef& in_ctxt )
{
	Context ctxt( in_ctxt );
 	MenuItem menuItem;
 	Menu menu = ctxt.GetSource();
 	menu.AddCommandItem( L"SpotLight Tool", L"SpotLightCreateTool", menuItem );
 	return true;
}

SICALLBACK SpotLightCreateTool_Init( CRef& in_ctxt )
{
	SpotLightCreateTool *l_pTool = new SpotLightCreateTool;
	if ( !l_pTool ) return CStatus::Fail;
	ToolContext l_ctxt( in_ctxt );
	l_ctxt.PutUserData( CValue((CValue::siPtrType)l_pTool) );
	return CStatus::OK;
}

SICALLBACK SpotLightCreateTool_Term( CRef& in_ctxt )
{
	ToolContext l_ctxt( in_ctxt );
	SpotLightCreateTool *l_pTool = (SpotLightCreateTool *)(CValue::siPtrType)l_ctxt.GetUserData();
	if ( !l_pTool ) return CStatus::Fail;
	delete l_pTool;
	l_ctxt.PutUserData( CValue((CValue::siPtrType)NULL) ); // Clear user data
	return CStatus::OK;
}

// Use a macro to simplify the callback setup and forwarding
#define DECLARE_TOOL_CALLBACK(TOOL,CALLBACK) \
SICALLBACK TOOL##_##CALLBACK( ToolContext& in_ctxt ) { \
	TOOL *l_pTool = (TOOL *)(CValue::siPtrType)in_ctxt.GetUserData(); \
	return ( l_pTool ? l_pTool->CALLBACK( in_ctxt ) : CStatus::Fail ); }

// Tool callbacks
DECLARE_TOOL_CALLBACK( SpotLightCreateTool, Activate );
DECLARE_TOOL_CALLBACK( SpotLightCreateTool, MouseDown );
DECLARE_TOOL_CALLBACK( SpotLightCreateTool, MouseDrag );
DECLARE_TOOL_CALLBACK( SpotLightCreateTool, MouseUp );
DECLARE_TOOL_CALLBACK( SpotLightCreateTool, Draw );
