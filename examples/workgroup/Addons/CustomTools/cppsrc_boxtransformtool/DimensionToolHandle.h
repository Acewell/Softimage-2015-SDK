#ifndef DIMENSION_TOOL_HANDLE_INCLUDED
#define DIMENSION_TOOL_HANDLE_INCLUDED
///////////////////////////////////////////////////////////////////////////
//
// File: DimensionToolHandle.h
//
// Description: Helper class for dimension text handles
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
// DimensionToolHandle class
//
////////////////////////////////////////////////////////////////////////////////

class DimensionToolHandle : public ToolHandle {
public: // Methods
	~DimensionToolHandle();
	DimensionToolHandle( BoxTransformToolDelegate * in_pTool, ToolHandleID in_ID );
	bool	RequiresViewDraw() const { return true; }
	void	Draw( ToolContext &in_ctxt );
	void	MouseUp( ToolContext& in_ctxt );
	CString GetHandleDescription() const { return L"Edit Length"; }

protected: // Implementation Methods
	CStatus DrawDimension( ToolContext &in_ctxt, const BBox &in_bbox, BBox::BBoxEdge in_eEdge, CVector3 &in_Pt1, CVector3 &in_Pt2, CVector3 &in_Mid );
	void ScaleObjects( double in_scale );

protected: // Data
	double		m_length;
	LONG		m_textBox[4];
	LONG		m_editBox[4];
};

#endif // DIMENSION_TOOL_HANDLE_INCLUDED
