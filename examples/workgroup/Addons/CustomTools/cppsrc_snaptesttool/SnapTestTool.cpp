///////////////////////////////////////////////////////////////////////////
//
// File: SnapTestTool.cpp
//
// Description: This plugin uses snapping to identify snap targets
// close to the cursor.
//
// The tool can be invoked by typing SnapTestTool at the command
// line or by assigning a hotkey to the SnapTestTool custom script
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
#include <xsi_pluginregistrar.h>
#include <xsi_application.h>
#include <xsi_status.h>
#include <xsi_argument.h>
#include <xsi_toolcontext.h>
#include <xsi_math.h>

using namespace XSI; 
using namespace XSI::MATH; 

////////////////////////////////////////////////////////////////////////////////
//
// SnapTestTool class
//
////////////////////////////////////////////////////////////////////////////////

class SnapTestTool {
private: // Data
	LONG		m_cursorX;
	LONG 		m_cursorY;
	CVector3	m_worldPos;
	CString		m_snapType;
	CString 	m_snapTarget;

public: // Methods
	SnapTestTool()
	{}

	~SnapTestTool()
	{}

	CStatus MouseMove( ToolContext& in_ctxt )
	{
		CString oldType = m_snapType;
		CString oldTarget = m_snapTarget;
		m_snapType.Clear();
		m_snapTarget.Clear();
		in_ctxt.GetMousePosition( m_cursorX, m_cursorY );
		const CStringArray familyFilter; // empty but could specify just meshes etc.
		const CRefArray targets; // empty but could use selection or some other list
		ULONG everything = siSnap0D | siSnap1D | siSnap2D | siSnapGrid;
		if ( in_ctxt.Snap( m_cursorX, m_cursorY, 20/*pixels*/, everything, familyFilter, targets, m_worldPos ) == CStatus::OK )
		{
			// Get snap type
			switch ( in_ctxt.GetSnapType() ) {
			case siSnapPoint:		m_snapType = L"point"; break;
			case siSnapKnot:		m_snapType = L"knot"; break;
			case siSnapCenter:		m_snapType = L"center"; break;
			case siSnapMidPoint:	m_snapType = L"midpoint"; break;
			case siSnapBBox:		m_snapType = L"bbox"; break;
			case siSnapEdge:		m_snapType = L"edge"; break;
			case siSnapCurve:		m_snapType = L"curve"; break;
			case siSnapUIsocurve:	m_snapType = L"ucurve"; break;
			case siSnapVIsocurve:	m_snapType = L"vcurve"; break;
			case siSnapBoundary:	m_snapType = L"boundarycurve"; break;
			case siSnapFace:		m_snapType = L"face"; break;
			case siSnapSurface:		m_snapType = L"surface"; break;
			case siSnapGrid:		m_snapType = L"grid"; break;
			}

			// Get snap target info
			if (m_snapType.Length() > 0 )
			{
				// Try getting component first and then object
				CRef target = in_ctxt.GetSnapComponent();
				if ( !target.IsValid() )
					target = in_ctxt.GetSnapObject();
				if ( target.IsValid() )
					m_snapTarget = target.GetAsText();
			}
		}

		// Redraw active view if anything has changed since the last mouse move
		if ( m_snapType != oldType || m_snapTarget != oldTarget )
			in_ctxt.Redraw( false );

		return CStatus::OK;
	}

	CStatus Draw( ToolContext& in_ctxt )
	{
		if ( in_ctxt.IsActiveView() )
		{
			if ( m_snapType.Length() > 0 )
			{
				in_ctxt.BeginViewDraw();

				CVector3 l_snapPos;
				if ( in_ctxt.WorldToView( m_worldPos, l_snapPos ) == CStatus::OK )
				{
					l_snapPos.PutZ( 0.0 ); // Remove depth info

					CString l_Str = m_snapType;
					if ( m_snapTarget.Length() > 0 )
						l_Str += L": " + m_snapTarget;

					LONG width = 0, height = 0, descent = 0;
					in_ctxt.GetTextSize( l_Str, width, height, descent );
					GLint x = (GLint)l_snapPos.GetX() + 20/*pixels*/, y = (GLint)l_snapPos.GetY() + 10/*pixels*/;

					// Draw background
					glColor3d(1.0, 1.0, 160/255.0);
					glBegin( GL_POLYGON );
					glVertex2d( x - 2, y - descent + height + 2 );
					glVertex2d( l_snapPos.GetX(), l_snapPos.GetY() );
					glVertex2d( x - 2, y - descent - 2);
					glVertex2d( x + width + 2, y - descent - 2 );
					glVertex2d( x + width + 2, y - descent + height + 2 );
					glEnd();

					// Draw outline
					glColor3d( 0, 0, 0 );
					glBegin( GL_LINE_LOOP );
					glVertex2d( x - 2, y - descent + height + 2 );
					glVertex2d( l_snapPos.GetX(), l_snapPos.GetY() );
					glVertex2d( x - 2, y - descent - 2 );
					glVertex2d( x + width + 2, y - descent - 2 );
					glVertex2d( x + width + 2, y - descent + height + 2 );
					glEnd();

					// Draw text
					glRasterPos2i( x, y );
					in_ctxt.DrawTextString( l_Str );
				}
			}
		}
		return CStatus::OK;
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
	in_reg.PutName(L"SnapTestTool Plugin");
	in_reg.PutVersion(1,0);
	in_reg.RegisterTool(L"SnapTestTool");
	//RegistrationInsertionPoint - do not remove this line
	return CStatus::OK;
}

SICALLBACK SnapTestTool_Init( CRef& in_ctxt )
{
	// Create an instance of our tool
	SnapTestTool *l_pTool = new SnapTestTool;
	if ( !l_pTool ) return CStatus::Fail;
	ToolContext l_ctxt( in_ctxt );
	l_ctxt.PutUserData( CValue((CValue::siPtrType)l_pTool) );
	return CStatus::OK;
}

SICALLBACK SnapTestTool_Term( CRef& in_ctxt )
{
	ToolContext l_ctxt( in_ctxt );
	SnapTestTool *l_pTool = (SnapTestTool *)(CValue::siPtrType)l_ctxt.GetUserData();
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

DECLARE_TOOL_CALLBACK( SnapTestTool, MouseMove );
DECLARE_TOOL_CALLBACK( SnapTestTool, Draw );
