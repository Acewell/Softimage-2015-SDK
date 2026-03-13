
#ifndef ROTATE_STICK_TOOL_HANDLE_INCLUDED
#define ROTATE_STICK_TOOL_HANDLE_INCLUDED
///////////////////////////////////////////////////////////////////////////
//
// File: RotateStickToolHandle.h
//
// Description: Helper class for rotation stick handle
//
// Copyright 2010 Autodesk, Inc. All rights reserved.
// Use of this software is subject to the terms of the Autodesk license
// agreement provided at the time of installation or download, or which
// otherwise accompanies this software in either electronic or hard copy
// form.
//
///////////////////////////////////////////////////////////////////////////
#include "RotateToolHandle.h"

////////////////////////////////////////////////////////////////////////////////
//
// RotateStickToolHandle class
//
////////////////////////////////////////////////////////////////////////////////

class RotateStickToolHandle : public RotateToolHandle {
public: // Methods
	~RotateStickToolHandle();
	RotateStickToolHandle( BoxTransformToolDelegate * in_pTool, ToolHandleID in_ID );
	void Draw( ToolContext &in_ctxt );
	void MouseDown( ToolContext& in_ctxt );
	void MouseDrag( ToolContext& in_ctxt );
	void MouseUp( ToolContext& in_ctxt );

protected:
	void DrawSphere( double in_dRadius, int in_nSlices, int in_nStacks );

protected: // Data
	CTransformation		m_initialXfo;
	CRefArray			m_objects;
	CVector3			m_pivot;
	CVector3 			m_constraintAxes[2];
	LONG				m_startX, m_startY;
	LONG				m_activeConstraint;
};

#endif // ROTATE_STICK_TOOL_HANDLE_INCLUDED
