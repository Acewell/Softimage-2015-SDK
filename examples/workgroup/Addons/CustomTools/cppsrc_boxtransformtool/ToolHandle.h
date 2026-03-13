#ifndef HANDLE_INCLUDED
#define HANDLE_INCLUDED
///////////////////////////////////////////////////////////////////////////
//
// File: ToolHandle.h
//
// Description: Base class for handles
//
// Copyright 2010 Autodesk, Inc. All rights reserved.
// Use of this software is subject to the terms of the Autodesk license
// agreement provided at the time of installation or download, or which
// otherwise accompanies this software in either electronic or hard copy
// form.
//
///////////////////////////////////////////////////////////////////////////
#include "Constants.h"
#include "BoxTransformToolDelegate.h"
#include <xsi_status.h>
#include <xsi_argument.h>
#include <xsi_toolcontext.h>
#include <xsi_application.h>

////////////////////////////////////////////////////////////////////////////////
//
// ToolHandle base class
//
////////////////////////////////////////////////////////////////////////////////

class ToolHandle {
public:
	virtual ~ToolHandle();

	// Tool callbacks
	virtual void Setup( BoxTransformToolDelegate * in_pTool, ToolHandleID in_ID );
	virtual void Cleanup() {}
	virtual void Draw( ToolContext &in_ctxt ) {}
	virtual void MouseDown( ToolContext& in_ctxt ) {}
	virtual void MouseDrag( ToolContext& in_ctxt ) {}
	virtual void MouseUp( ToolContext& in_ctxt ) {}

	// Data access
	ToolHandleID HandleID() const { return m_HandleID; }
	bool IsSelected() const { return m_bSelected; }
	void SetSelected( bool in_bSelected ) { m_bSelected = in_bSelected; }
	virtual bool RequiresViewDraw() const { return false; } // 2D vs 3D Handle
	virtual CString GetHandleDescription() const { return CString(); }

protected: // Methods
	ToolHandle(); // Abstract base class
	double GetViewScaleFactor( ToolContext &in_ctxt, const CVector3 &in_Pos, double in_dViewSize ) const;
	LONG GetClosestDragAxis( ToolContext &in_ctxt, const CVector3 &in_mouseVec, CLine in_axes[], double &out_projectedlength ) const;
	double GetClosestIncrement( double in_value, double in_increment ) const;

protected: // Data
	BoxTransformToolDelegate *	m_pTool;			// Owner
	ToolHandleID				m_HandleID;			// Handle ID
	bool						m_bSelected;		// Selection state
};

#endif // HANDLE_INCLUDED
