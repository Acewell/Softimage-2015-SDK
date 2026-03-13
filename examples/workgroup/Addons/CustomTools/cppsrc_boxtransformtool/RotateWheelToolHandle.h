#ifndef ROTATE_WHEEL_TOOL_HANDLE_INCLUDED
#define ROTATE_WHEEL_TOOL_HANDLE_INCLUDED
///////////////////////////////////////////////////////////////////////////
//
// File: RotateWheelToolHandle.h
//
// Description: Helper class for rotation wheel handle
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
// RotateWheelToolHandle class
//
////////////////////////////////////////////////////////////////////////////////

class RotateWheelToolHandle : public RotateToolHandle {
public: // Methods
	~RotateWheelToolHandle();
	RotateWheelToolHandle( BoxTransformToolDelegate * in_pTool, ToolHandleID in_ID );
	void Draw( ToolContext &in_ctxt );
	void MouseDown( ToolContext& in_ctxt );
	void MouseDrag( ToolContext& in_ctxt );
	void MouseUp( ToolContext& in_ctxt );

protected: // Methods
	void DrawTorus( double in_dInnerRadius, double in_dOuterRadius, int in_nSides, int in_nRings );

protected: // Data
	CTransformation		m_initialXfo;
	CRefArray			m_objects;
	CVector3			m_pivot;
	CVector3 			m_constraintAxis;
	LONG				m_startX, m_startY;
};

#endif // ROTATE_WHEEL_TOOL_HANDLE_INCLUDED
