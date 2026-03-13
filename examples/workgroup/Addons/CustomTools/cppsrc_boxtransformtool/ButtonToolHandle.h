#ifndef BUTTON_TOOL_HANDLE_INCLUDED
#define BUTTON_TOOL_HANDLE_INCLUDED
///////////////////////////////////////////////////////////////////////////
//
// File: ButtonToolHandle.h
//
// Description: Helper class for button handles
//
// Copyright 2010 Autodesk, Inc. All rights reserved.
// Use of this software is subject to the terms of the Autodesk license
// agreement provided at the time of installation or download, or which
// otherwise accompanies this software in either electronic or hard copy
// form.
//
///////////////////////////////////////////////////////////////////////////
#include "ToolHandle.h"
#include "ToolButton.h"

////////////////////////////////////////////////////////////////////////////////
//
// ButtonToolHandle class
//
////////////////////////////////////////////////////////////////////////////////

class ButtonToolHandle : public ToolHandle {
public: // Methods
	ButtonToolHandle( BoxTransformToolDelegate * in_pTool, ToolHandleID in_ID, ToolButton * in_button );
	~ButtonToolHandle();
	bool	RequiresViewDraw() const { return true; }
	void	Draw( ToolContext &in_ctxt );
	void	MouseDown( ToolContext& in_ctxt );
	void	MouseDrag( ToolContext& in_ctxt );
	void	MouseUp( ToolContext& in_ctxt );

protected: // Data
	ToolButton *	m_pButton;
	bool			m_bWasSelected;
};

#endif // BUTTON_TOOL_HANDLE_INCLUDED
