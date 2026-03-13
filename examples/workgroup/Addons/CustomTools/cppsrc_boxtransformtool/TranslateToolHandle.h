#ifndef TRANSLATE_TOOL_HANDLE_INCLUDED
#define TRANSLATE_TOOL_HANDLE_INCLUDED
///////////////////////////////////////////////////////////////////////////
//
// File: TranslateToolHandle.h
//
// Description: Helper class for translation handles
//
// Copyright 2010 Autodesk, Inc. All rights reserved.
// Use of this software is subject to the terms of the Autodesk license
// agreement provided at the time of installation or download, or which
// otherwise accompanies this software in either electronic or hard copy
// form.
//
///////////////////////////////////////////////////////////////////////////
#include "ToolHandle.h"

////////////////////////////////////////////////////////////////////////////////
//
// TranslateToolHandle class
//
////////////////////////////////////////////////////////////////////////////////

class TranslateToolHandle : public ToolHandle {
public: // Methods
	TranslateToolHandle( BoxTransformToolDelegate * in_pTool, ToolHandleID in_ID );
	~TranslateToolHandle();
	void Draw( ToolContext &in_ctxt );
	void MouseDown( ToolContext& in_ctxt );
	void MouseDrag( ToolContext& in_ctxt );
	void MouseUp( ToolContext& in_ctxt );
	CString GetHandleDescription() const { return L"Translate, <Shift> for Constrained"; }

protected: // Methods
	CVector3 GetPosition( ToolContext &in_ctxt );
	void DrawPoint( ToolContext &in_ctxt, LONG in_size, ULONG in_color, bool in_bSmooth );

protected: // Data
	CRefArray			m_objects;
	CPlane				m_manipPlane;
	CVector3			m_initialPosition;
	CLine				m_dragAxis[3];
	LONG				m_activeAxis;
	LONG				m_startX, m_startY;
};

#endif // TRANSLATE_TOOL_HANDLE_INCLUDED
