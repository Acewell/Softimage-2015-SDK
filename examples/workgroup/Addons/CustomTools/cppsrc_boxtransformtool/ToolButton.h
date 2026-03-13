#ifndef TOOL_BUTTON_INCLUDED
#define TOOL_BUTTON_INCLUDED
///////////////////////////////////////////////////////////////////////////
//
// File: ToolButton.h
//
// Description: Helper class for tool (mode) buttons
//
// Copyright 2010 Autodesk, Inc. All rights reserved.
// Use of this software is subject to the terms of the Autodesk license
// agreement provided at the time of installation or download, or which
// otherwise accompanies this software in either electronic or hard copy
// form.
//
///////////////////////////////////////////////////////////////////////////
#include <xsi_toolcontext.h>
#ifndef linux
#define WIN32_LEAN_AND_MEAN
#include <windows.h> // Needed for OpenGL on windows
#endif
#include <string.h>
#include <GL/gl.h>

using namespace XSI; 

////////////////////////////////////////////////////////////////////////////////
//
// ToolButton class
//
////////////////////////////////////////////////////////////////////////////////

class ToolButton {
public:
	ToolButton();
	~ToolButton();
	void Setup( const wchar_t *basename, LONG in_index, LONG in_count );
	void Cleanup();
	bool IsSelected() const { return m_bSelected; }
	void SetSelected( bool in_bSelected ) { m_bSelected = in_bSelected; }
	bool IsPointInside( ToolContext &in_ctxt, LONG x, LONG y ) const;
	void Draw( ToolContext &in_ctxt );
	void LoadTextures( ToolContext &in_ctxt );

private: // Implementation
	CStatus GetButtonPosition( ToolContext &in_ctxt, LONG out_rect[] ) const;

private: // Data
	CString		m_basename;			// Base texture name
	GLuint		m_textureID[2];		// OpenGL texture IDs
	LONG		m_buttonSize[2];	// Button size
	LONG		m_buttonIndex;		// Index of button
	LONG		m_buttonCount;		// Total number of buttons
	bool		m_bSelected;		// Selected state
};

#endif // TOOL_BUTTON_INCLUDED
