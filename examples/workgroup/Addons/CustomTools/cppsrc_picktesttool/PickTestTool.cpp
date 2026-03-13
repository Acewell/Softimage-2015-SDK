///////////////////////////////////////////////////////////////////////////
//
// File: PickTestTool.cpp
//
// Description: This plugin uses picking to identify objects and points
// close to the cursor. Picking options can be set using a RMB context menu.
//
// The tool can be invoked by typing PickTestTool at the command
// line or by assigning a hotkey to the PickTestTool custom script
// command in the keyboard mapping dialog.
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
#include <xsi_math.h>
#include <xsi_pluginregistrar.h>
#include <xsi_application.h>
#include <xsi_status.h>
#include <xsi_argument.h>
#include <xsi_toolcontext.h>
#include <xsi_menu.h>
#include <xsi_menuitem.h>

using namespace XSI; 
using namespace XSI::MATH; 

////////////////////////////////////////////////////////////////////////////////
//
// PickTestTool class
//
////////////////////////////////////////////////////////////////////////////////

class PickTestTool {
private: // Data
	LONG		m_cursorX;
	LONG 		m_cursorY;
	CRefArray	m_picked;
	CLongArray  m_points;
	siPickMode	m_pickMode;
	siPickType	m_pickType;
	bool		m_subcomp;

public: // Methods
	PickTestTool()
	{}

	~PickTestTool()
	{}

	CStatus Activate( ToolContext& in_ctxt )
	{
		in_ctxt.SetCursor( siCrossCursor );
		in_ctxt.SetToolDescription( L"PickTestTool\n\n\nContext Menu" );
		m_pickType = siPickRaycast;
		m_pickMode = siPickSingleObject;
		m_subcomp = false;
		m_points.Add( 0 );
		m_points.Add( 0 );
		return CStatus::OK;
	}

	CStatus MouseDown( ToolContext& in_ctxt )
	{
		// Called when mouse button is pressed
		LONG x, y;
		in_ctxt.GetMousePosition( x, y );

		if ( in_ctxt.IsRightButtonDown() )
			in_ctxt.ShowContextMenu( x, y );

		return CStatus::False;
	}

	CStatus MouseMove( ToolContext& in_ctxt )
	{
		m_picked.Clear();
		in_ctxt.GetMousePosition( m_cursorX, m_cursorY );

		CLongArray l_points;
		for ( LONG i = 0, count = m_points.GetCount(); i < count; i += 2 ) {
			l_points.Add( m_cursorX + m_points[i] );
			l_points.Add( m_cursorY + m_points[i+1] );
		}

		// First get object under the cursor
		in_ctxt.Pick( l_points, m_pickMode, m_pickType, L"", CRefArray(), m_picked );

		if ( m_subcomp && m_picked.GetCount() > 0 )
		{
			CRefArray components;
			siPickMode	subcompMode = ( m_pickMode == siPickSingleObject ? siPickSingleSubComponent : siPickMultipleSubComponents );
			in_ctxt.Pick( l_points, subcompMode, m_pickType, siPointFilter, m_picked, components );
			if ( components.GetCount() > 0 )
				m_picked = components;
		}

		in_ctxt.Redraw( false );
		return CStatus::OK;
	}

	CStatus Draw( ToolContext& in_ctxt )
	{
		if ( in_ctxt.IsActiveView() )
		{
			in_ctxt.BeginViewDraw();

			if ( m_picked.GetCount() > 0 )
			{

				CString l_Str = m_picked.GetAsText();
				if ( l_Str.Length() > 0 )
				{
					LONG width = 0, height = 0, descent = 0;
					in_ctxt.GetTextSize( l_Str, width, height, descent );
					GLint x = (GLint)m_cursorX - width/2, y = (GLint)m_cursorY + 40/*pixels*/;

					// Draw background
					glColor3d(160/255.0, 1.0, 1.0);
					glBegin( GL_QUADS );
					glVertex2d( x - 2, y - descent + height + 2 );
					glVertex2d( x - 2, y - descent - 2);
					glVertex2d( x + width + 2, y - descent - 2 );
					glVertex2d( x + width + 2, y - descent + height + 2 );
					glEnd();

					// Draw outline
					glColor3d( 0, 0, 0 );
					glBegin( GL_LINE_LOOP );
					glVertex2d( x - 2, y - descent + height + 2 );
					glVertex2d( x - 2, y - descent - 2 );
					glVertex2d( x + width + 2, y - descent - 2 );
					glVertex2d( x + width + 2, y - descent + height + 2 );
					glEnd();

					// Draw text
					glRasterPos2i( x, y );
					in_ctxt.DrawTextString( l_Str );
				}
			}

			if ( m_points.GetCount() > 2 )
			{
				glLineStipple( 2, 0xAAAA );
				glEnable( GL_LINE_STIPPLE );
				glColor3d( 0.0, 0.0, 1.0 );
				switch ( m_pickType ) {
				case siPickRectangleRaycast:
				case siPickRectangle: {
					glBegin( GL_LINE_LOOP );
					glVertex2d( m_cursorX + m_points[0], m_cursorY + m_points[1] );
					glVertex2d( m_cursorX + m_points[2], m_cursorY + m_points[1] );
					glVertex2d( m_cursorX + m_points[2], m_cursorY + m_points[3] );
					glVertex2d( m_cursorX + m_points[0], m_cursorY + m_points[3] );
					glEnd();
					break;
				}
				case siPickLasso: {
					glBegin( GL_LINE_LOOP );
					for ( LONG i = 0, count = m_points.GetCount(); i < count; i += 2 )
						glVertex2d( m_cursorX + m_points[i], m_cursorY + m_points[i+1] );
					glEnd();
					break;
				}
				case siPickFreeform: {
					glBegin( GL_LINE_STRIP );
					for ( LONG i = 0, count = m_points.GetCount(); i < count; i += 2 )
						glVertex2d( m_cursorX + m_points[i], m_cursorY + m_points[i+1] );
					glEnd();
					break;
				}
				default:
					break;
				}
				glDisable( GL_LINE_STIPPLE );
			}
			in_ctxt.EndViewDraw();
		}
		return CStatus::OK;
	}

	CStatus MenuInit( ToolContext& in_ctxt )
	{
		// Called to initialize the context menu
		MenuItem menuItem;
		Menu menu = in_ctxt.GetSource();
		menu.AddCallbackItem( L"Raycast",      L"PickTestTool_Raycast", menuItem );
		menuItem.PutChecked( m_pickType == siPickRaycast );
		menu.AddCallbackItem( L"Rectangle",    L"PickTestTool_Rectangle", menuItem );
		menuItem.PutChecked( m_pickType == siPickRectangle );
		menu.AddCallbackItem( L"Lasso",        L"PickTestTool_Lasso", menuItem );
		menuItem.PutChecked( m_pickType == siPickLasso );
		menu.AddCallbackItem( L"Freeform",     L"PickTestTool_Freeform", menuItem );
		menuItem.PutChecked( m_pickType == siPickFreeform );
		menu.AddCallbackItem( L"Rect Raycast", L"PickTestTool_RectangleRaycast", menuItem );
		menuItem.PutChecked( m_pickType == siPickRectangleRaycast );
		menu.AddSeparatorItem();
		menu.AddCallbackItem( L"Single",       L"PickTestTool_Single", menuItem );
		menuItem.PutChecked( m_pickMode == siPickSingleObject );
		menu.AddCallbackItem( L"Multiple",     L"PickTestTool_Multiple", menuItem );
		menuItem.PutChecked( m_pickMode == siPickMultipleObjects );
		menu.AddSeparatorItem();
		menu.AddCallbackItem( L"Points",     L"PickTestTool_Points", menuItem );
		menuItem.PutChecked( m_subcomp );
		menu.AddSeparatorItem();
		menu.AddCallbackItem( L"Exit Tool",    L"PickTestTool_DoExitTool", menuItem );
		return CStatus::OK;
	}

	CStatus Rectangle( ToolContext& in_ctxt )
	{
		m_pickType = siPickRectangle;
		CLongArray l_points;
		l_points.Add( -40 );
		l_points.Add( -20 );
		l_points.Add(  40 );
		l_points.Add(  20 );
		m_points = l_points;
		return CStatus::OK;
	}

	CStatus Raycast( ToolContext& in_ctxt )
	{
		m_pickType = siPickRaycast;
		CLongArray l_points;
		l_points.Add( 0 );
		l_points.Add( 0 );
		m_points = l_points;
		return CStatus::OK;
	}

	CStatus Lasso( ToolContext& in_ctxt )
	{
		m_pickType = siPickLasso;
		CLongArray l_points;
		l_points.Add( -30 );
		l_points.Add(   0 );
		l_points.Add(   0 );
		l_points.Add(  30 );
		l_points.Add(  30 );
		l_points.Add(   0 );
		l_points.Add(   0 );
		l_points.Add( -30 );
		m_points = l_points;
		return CStatus::OK;
	}

	CStatus Freeform( ToolContext& in_ctxt )
	{
		m_pickType = siPickFreeform;
		CLongArray l_points;
		l_points.Add(   0 );
		l_points.Add(  30 );
		l_points.Add( -30 );
		l_points.Add(   0 );
		l_points.Add(  30 );
		l_points.Add(   0 );
		l_points.Add(   0 );
		l_points.Add( -30 );
		m_points = l_points;
		return CStatus::OK;
	}

	CStatus RectangleRaycast( ToolContext& in_ctxt )
	{
		m_pickType = siPickRectangleRaycast;
		CLongArray l_points;
		l_points.Add( -40 );
		l_points.Add( -20 );
		l_points.Add(  40 );
		l_points.Add(  20 );
		m_points = l_points;
		return CStatus::OK;
	}

	CStatus Single( ToolContext& in_ctxt )
	{
		m_pickMode = siPickSingleObject;
		return CStatus::OK;
	}

	CStatus Multiple( ToolContext& in_ctxt )
	{
		m_pickMode = siPickMultipleObjects;
		return CStatus::OK;
	}

	CStatus Points( ToolContext& in_ctxt )
	{
		m_subcomp = !m_subcomp;
		return CStatus::OK;
	}

	CStatus DoExitTool( ToolContext& in_ctxt )
	{
		in_ctxt.ExitTool();
		return CStatus::OK;
	}

}; // end class

////////////////////////////////////////////////////////////////////////////////
//
// Plugin callbacks
//
////////////////////////////////////////////////////////////////////////////////

SICALLBACK XSILoadPlugin( PluginRegistrar& in_reg )
{
	in_reg.PutAuthor(L"Autodesk");
	in_reg.PutName(L"PickTestTool Plugin");
	in_reg.PutVersion(1,0);
	in_reg.RegisterTool(L"PickTestTool");
	//RegistrationInsertionPoint - do not remove this line
	return CStatus::OK;
}

SICALLBACK PickTestTool_Init( CRef& in_ctxt )
{
	// Create an instance of our tool
	PickTestTool *l_pTool = new PickTestTool;
	if ( !l_pTool ) return CStatus::Fail;
	ToolContext l_ctxt( in_ctxt );
	l_ctxt.PutUserData( CValue((CValue::siPtrType)l_pTool) );
	return CStatus::OK;
}

SICALLBACK PickTestTool_Term( CRef& in_ctxt )
{
	ToolContext l_ctxt( in_ctxt );
	PickTestTool *l_pTool = (PickTestTool *)(CValue::siPtrType)l_ctxt.GetUserData();
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

DECLARE_TOOL_CALLBACK( PickTestTool, Activate );
DECLARE_TOOL_CALLBACK( PickTestTool, Draw );
DECLARE_TOOL_CALLBACK( PickTestTool, MouseDown );
DECLARE_TOOL_CALLBACK( PickTestTool, MouseMove );
DECLARE_TOOL_CALLBACK( PickTestTool, MenuInit );

DECLARE_TOOL_CALLBACK( PickTestTool, Rectangle );
DECLARE_TOOL_CALLBACK( PickTestTool, Raycast );
DECLARE_TOOL_CALLBACK( PickTestTool, RectangleRaycast );
DECLARE_TOOL_CALLBACK( PickTestTool, Lasso );
DECLARE_TOOL_CALLBACK( PickTestTool, Freeform );
DECLARE_TOOL_CALLBACK( PickTestTool, Single );
DECLARE_TOOL_CALLBACK( PickTestTool, Multiple );
DECLARE_TOOL_CALLBACK( PickTestTool, Points );
DECLARE_TOOL_CALLBACK( PickTestTool, DoExitTool );
