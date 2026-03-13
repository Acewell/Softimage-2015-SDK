#ifndef SCALE_TOOL_HANDLE_INCLUDED
#define SCALE_TOOL_HANDLE_INCLUDED
///////////////////////////////////////////////////////////////////////////
//
// File: ScaleToolHandle.h
//
// Description: Helper class for scaling handles
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
// ScaleToolHandle class
//
////////////////////////////////////////////////////////////////////////////////

class ScaleToolHandle : public ToolHandle {
public: // Methods
	~ScaleToolHandle();
	ScaleToolHandle( BoxTransformToolDelegate * in_pTool, ToolHandleID in_ID );
	void Draw( ToolContext &in_ctxt );
	void MouseDown( ToolContext& in_ctxt );
	void MouseDrag( ToolContext& in_ctxt );
	void MouseUp( ToolContext& in_ctxt );
	CString GetHandleDescription() const { return L"Scale, <Shift> for Uniform"; }

protected: // Methods
	BBox::BBoxPoint GetBoxPoint() { return (BBox::BBoxPoint)(HandleID()-kScaleCornerMinID); }

protected: // Data
	CRefArray			m_objects;
	BBox		m_startBBox;
	CVector3			m_pivot;
	CLine				m_scaleAxis[4];
	LONG				m_activeAxis;
	LONG				m_startX, m_startY;
};

#endif // SCALE_TOOL_HANDLE_INCLUDED
