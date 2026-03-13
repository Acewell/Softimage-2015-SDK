///////////////////////////////////////////////////////////////////////////
//
// File: AnnotationTool.cpp
//
// Description: This plugin uses picking to identify points
// close to the cursor.
//
// The tool can be invoked by typing AnnotationTool at the command
// line or by assigning a hotkey to the AnnotationTool custom script
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
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h> // Needed for OpenGL on windows
#include <Shellapi.h>
#endif
#include <GL/gl.h>
#include <xsi_application.h>
#include <xsi_status.h>
#include <xsi_argument.h>
#include <xsi_selection.h>
#include <xsi_toolcontext.h>
#include <xsi_math.h>
#include <xsi_model.h>
#include <xsi_menu.h>
#include <xsi_annotation.h>
#include <algorithm>

using namespace XSI; 
using namespace XSI::MATH; 

////////////////////////////////////////////////////////////////////////////////
//
// AnnotationTool class
//
////////////////////////////////////////////////////////////////////////////////

class AnnotationTool {
private: // Data
	LONG		m_cursorX;      // Mouse position that was last picked.
	LONG 		m_cursorY;      // Mouse position that was last picked.
	X3DObject 	m_hovering;     // Annotation that was last hovered with the mouse.
	X3DObject 	m_clicked;      // Annotation that was last clicked with the mouse.
    CString     m_URL;          // URL in annotation that was last hovered.

    ////////////////////////////////////////////////////////////////////////////////
    // Perform a picking session at the mouse position and return the annotation
    // object picked, if any.
    void PickAnnotation( ToolContext& in_ctxt, X3DObject& out_annotation )
    {
		out_annotation.ResetObject();
		in_ctxt.GetMousePosition( m_cursorX, m_cursorY );

		CLongArray l_points;
		l_points.Add( m_cursorX );
		l_points.Add( m_cursorY );

		CRefArray objects;
		in_ctxt.Pick( l_points, siPickSingleObject, siPickRectangle, L"", Application().GetActiveSceneRoot().GetChildren(), objects );

        for ( LONG i = 0; i < objects.GetCount(); ++i )
		{
            X3DObject obj = objects.GetItem( i );
			if ( obj.IsA( XSI::siAnnotationID ) )
            {
                out_annotation = obj;
            }
		}
    }

    ////////////////////////////////////////////////////////////////////////////////
    // Perform a picking session at the mouse position and return the annotation
    // object picked, if any, and the URL under the mouse, if any.
    //
    void PickAnnotationURL( ToolContext& in_ctxt, X3DObject& out_annotation, CString& out_URL )
    {
        PickAnnotation( in_ctxt, out_annotation );
        if ( out_annotation.IsValid() )
        {
			// Retrieve the screen-space bounding-box of the URl of the annotation.
		    // Return an invalid bbox if there are no URL.
			out_URL = XSI::Annotation(out_annotation).GetURLAt( in_ctxt.GetViewIndex(), m_cursorX, m_cursorY );
        }
        else
        {
            out_URL.Clear();
        }
    }

    ////////////////////////////////////////////////////////////////////////////////
    // Selection mode for selecting annotation, based on modifier keys.
    enum SelectionMode
    {
        SelectionModeSingle,
        SelectionModeToggle,
        SelectionModeInclude,
        SelectionModeExclude
    };

    static SelectionMode GetSelectionMode( ToolContext& in_ctxt )
    {
        if ( in_ctxt.IsShiftKeyDown() )
            return in_ctxt.IsControlKeyDown() ? SelectionModeExclude : SelectionModeInclude;
        else
            return in_ctxt.IsControlKeyDown() ? SelectionModeToggle : SelectionModeSingle;
    }

    ////////////////////////////////////////////////////////////////////////////////
    // Change the selection, related to the annotation, based in the selection mode.
    static void SelectAnnotation( X3DObject& in_annotation, SelectionMode in_Mode )
    {
        switch ( in_Mode )
        {
            case SelectionModeSingle:
                Application().GetSelection().Clear();
                if ( in_annotation.IsValid() )
                    Application().GetSelection().Add( in_annotation );
                break;
            case SelectionModeToggle:
                if ( in_annotation.IsValid() )
                    if ( Application().GetSelection().GetItem( in_annotation.GetName() ).IsValid() )
                        Application().GetSelection().Remove( in_annotation );
                    else
                        Application().GetSelection().Add( in_annotation );
                break;
            case SelectionModeInclude:
                if ( in_annotation.IsValid() )
                    Application().GetSelection().Add( in_annotation );
                break;
            case SelectionModeExclude:
                if ( in_annotation.IsValid() )
                    Application().GetSelection().Remove( in_annotation );
                break;
        }
    }

    ////////////////////////////////////////////////////////////////////////////////
    // Execute a Softimage command taking a single parameter.
    static CValue ExecuteCommand( const wchar_t* in_Cmd, const CValue& in_Arg )
    {
        CValueArray args;
        args.Add( in_Arg );

        CValue result;
        Application().ExecuteCommand( in_Cmd, args, result );
		return result;
    }

    ////////////////////////////////////////////////////////////////////////////////
    // Open the property page showing the given annotation.
    static void ShowProperties( X3DObject& in_annotation )
    {
        if ( in_annotation.IsValid() )
        {
            ExecuteCommand( L"InspectObj", CRef( in_annotation ) );
        }
    }

    ////////////////////////////////////////////////////////////////////////////////
    // Delete the given annotation from the scene. Also reset some internal values.
    void DeleteAnnotation( X3DObject& in_annotation )
    {
        if ( in_annotation.IsValid() )
        {
            ExecuteCommand( L"DeleteObj", CRef( in_annotation ) );

            // Clear the cached objects, but only after calling the command.
            m_hovering.ResetObject();
            m_clicked.ResetObject();
        }
    }

    ////////////////////////////////////////////////////////////////////////////////
    // Convert from a URL path to a disk path.
    //
    // For simplicity, we will use straight Win32 paths within
    // the file: and script: URL. We expect users to be more
    // familiar with that syntax than the obscure syntex used
    // to encode full paths, with the weird drive notation.
    //
    // It also allows copying paths from the file explorer
    // directly in the annotation, and avoids nasty surprised
    // with the backslashes.
    static CString ConvertURLPathToFilePath( const CString& in_URLPath )
    {
        return in_URLPath;
    }

    ////////////////////////////////////////////////////////////////////////////////
    // Launch the given script in Softimage.
    static void LaunchScript( const CString& in_URLPath )
    {
		CValueArray foo;
		CValue boo;
        Application().ExecuteScript( ConvertURLPathToFilePath( in_URLPath ), CString(), CString(), foo, boo );
    }

    ////////////////////////////////////////////////////////////////////////////////
    // Launch the given file in Windows.
    //
    // Since we use the default handler for the file, it can be a program,
    // but it can also be any file that can be opened (image, doc, etc).
    static void LaunchExecutable( const CString& in_URLPath )
    {	
#ifndef linux
        DWORD_PTR result = (DWORD_PTR) ::ShellExecuteW( NULL, NULL, ConvertURLPathToFilePath( in_URLPath ).GetWideString(), NULL, NULL, SW_SHOWDEFAULT );
        // Yep, the error check is weird: anything above 32 is success.
        // That's the spec of ShellExecute().
        if ( result <= 32 )
        {
            CString error;
            switch ( result )
            {
                case ERROR_PATH_NOT_FOUND:
                case ERROR_FILE_NOT_FOUND:
                    error = L"File not found: ";
                    break;
                default:
                    // Pretty much all other errors are variation on a low-level
                    // "something went wrong", the exact detail of which would be
                    // of little value to the user (DDE failure, sharing violation,
                    // timeout, DLL not found...). Just tell the user we could not
                    // open the file.
                    error = L"Cannot open: ";
                    break;
            }
            error += in_URLPath;
            Application().LogMessage( error, siErrorMsg );
        }
#else
		// use the system command on linux
		ExecuteCommand( L"System", ConvertURLPathToFilePath( in_URLPath ).GetWideString() );
#endif
    }

    ////////////////////////////////////////////////////////////////////////////////
    // Open the given URL in the Softimage net view.
    static void LaunchURL( const CString& in_URL )
    {
        ExecuteCommand( L"OpenNetView", in_URL );
    }

    ////////////////////////////////////////////////////////////////////////////////
    // Handle the given URL according to its protocol.
    static void ProcessURL( const CString& in_URL )
    {
        CStringArray parts = in_URL.Split("://");
        // Need at least protocol and "something else".
        if ( parts.GetCount() <= 1 )
            return;

        CString protocol = parts[0];
        if ( protocol.IsEqualNoCase( L"script" ) )
        {
            LaunchScript( parts[1] );
        }
        else if ( protocol.IsEqualNoCase( L"file" ) )
        {
            LaunchExecutable( parts[1] );
        }
        else
        {
            LaunchURL( in_URL );
        }
    }

public: // Methods
	AnnotationTool()
	{}

	~AnnotationTool()
	{}

    ////////////////////////////////////////////////////////////////////////////////
    // Handle the mouse movements by picking which annotation is under the mouse.
    // When hovering over an embeeded URL, show it in a tooltip in the Draw() method.
	CStatus MouseMove( ToolContext& in_ctxt )
	{
        PickAnnotationURL( in_ctxt, m_hovering, m_URL );
        siToolCursor cursor = m_URL.IsEmpty() ? siArrowCursor : siHandCursor;
        in_ctxt.SetCursor( cursor );
		in_ctxt.Redraw( false );
		return CStatus::OK;
	}

    ////////////////////////////////////////////////////////////////////////////////
    // On mouse down, either open a context menu and clear the clicked annotation
    // variable, so it won't be processed on mouse up if it's the right mouse button.
    // Otherwise (not right button), pick which annotation is under the mouse to be
    // compared to the one under the mouse on mouse up.
	CStatus MouseDown( ToolContext& in_ctxt )
	{
		if ( in_ctxt.IsRightButtonDown() )
		{
            m_clicked.ResetObject();

		    LONG x, y;
		    in_ctxt.GetMousePosition( x, y );
			in_ctxt.ShowContextMenu( x, y );
        }
        else
        {
            PickAnnotation( in_ctxt, m_clicked );
        }
		return CStatus::OK;
	}

    ////////////////////////////////////////////////////////////////////////////////
    // On mouse up, if the mouse is still over the same annotation, then either
    // process its URL if the mouse is over the URL or open the property page
    // if it's over any other part.
	CStatus MouseUp( ToolContext& in_ctxt )
	{
        X3DObject releasedOver;
        CString url;
        PickAnnotationURL( in_ctxt, releasedOver, url );
        if ( releasedOver.IsEqualTo( m_clicked ) )
        {
            if ( releasedOver.IsValid() )
            {
                SelectAnnotation( releasedOver, GetSelectionMode( in_ctxt) );
                if ( ! url.IsEmpty() )
                {
                    ProcessURL( url );
                }
                else
                {
                    ShowProperties( releasedOver );
                }
            }
        }
		in_ctxt.Redraw( false );
		return CStatus::OK;
	}

    ////////////////////////////////////////////////////////////////////////////////
    // Show the menu for the annotation: open PPG or delete.
	CStatus MenuInit( ToolContext& in_ctxt )
	{
		MenuItem menuItem;
		Menu menu = in_ctxt.GetSource();
		menu.AddCallbackItem( L"Delete", L"AnnotationTool_DeleteAnnotation", menuItem );
		menu.AddSeparatorItem();
		menu.AddCallbackItem( L"Properties", L"AnnotationTool_ShowProperties", menuItem );
		return CStatus::OK;
	}

    ////////////////////////////////////////////////////////////////////////////////
    // Show the property of the annotation under the mouse, if any.
	CStatus ShowProperties( ToolContext& in_ctxt )
	{
        ShowProperties( m_hovering );
		return CStatus::OK;
    }

    ////////////////////////////////////////////////////////////////////////////////
    // Delete the annotation under the mouse, if any.
	CStatus DeleteAnnotation( ToolContext& in_ctxt )
	{
        DeleteAnnotation( m_hovering );
		return CStatus::OK;
    }

    ////////////////////////////////////////////////////////////////////////////////
    // Draw the URL of the annotation under the mouse in a tooltip, if any.
    // Also, potentially draw debug information to help debugging URL pciking.
	CStatus Draw( ToolContext& in_ctxt )
	{
		if ( ! in_ctxt.IsActiveView() )
		    return CStatus::OK;

        if ( m_URL.IsEmpty() )
		    return CStatus::OK;

		in_ctxt.BeginViewDraw();

        // Save the state of the color to be restored later.
        double d4SavedColor[4];
        glGetDoublev(GL_CURRENT_COLOR, d4SavedColor);

		LONG width = 0, height = 0, descent = 0;
		in_ctxt.GetTextSize( m_URL, width, height, descent );
        GLint x = std::max( (GLint)0, (GLint)(m_cursorX - width/2) );
        GLint y = (GLint)m_cursorY + 20;

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
		in_ctxt.DrawTextString( m_URL );

        glColor4dv(d4SavedColor);

        in_ctxt.EndViewDraw();

		return CStatus::OK;
	}

};


////////////////////////////////////////////////////////////////////////////////
//
// Plugin callbacks and tool callback registration.
//
////////////////////////////////////////////////////////////////////////////////


SICALLBACK AnnotationTool_Init( CRef& in_ctxt )
{
	ToolContext l_ctxt( in_ctxt );

	// Create an instance of our tool.
	AnnotationTool *l_pTool = new AnnotationTool;
	if ( l_pTool ) {
		l_ctxt.PutUserData( CValue((CValue::siPtrType)l_pTool) );
	}
	return CStatus::OK;
}

SICALLBACK AnnotationTool_Term( CRef& in_ctxt )
{
	ToolContext l_ctxt( in_ctxt );
	AnnotationTool *l_pTool = (AnnotationTool *)(CValue::siPtrType)l_ctxt.GetUserData();
	if ( l_pTool ) {
		delete l_pTool;
		l_ctxt.PutUserData( CValue((CValue::siPtrType)NULL) ); // Clear user data.
	}
	return CStatus::OK;
}

#define DECLARE_TOOL_CALLBACK(TOOL,CALLBACK) \
SICALLBACK TOOL##_##CALLBACK( ToolContext& in_ctxt ) { \
	TOOL *l_pTool = (TOOL *)(CValue::siPtrType)in_ctxt.GetUserData(); \
	return ( l_pTool ? l_pTool->CALLBACK( in_ctxt ) : CStatus::Fail ); \
}

DECLARE_TOOL_CALLBACK( AnnotationTool, MouseMove );
DECLARE_TOOL_CALLBACK( AnnotationTool, MouseDown );
DECLARE_TOOL_CALLBACK( AnnotationTool, MouseUp );
DECLARE_TOOL_CALLBACK( AnnotationTool, MenuInit );
DECLARE_TOOL_CALLBACK( AnnotationTool, ShowProperties );
DECLARE_TOOL_CALLBACK( AnnotationTool, DeleteAnnotation );
DECLARE_TOOL_CALLBACK( AnnotationTool, Draw );
