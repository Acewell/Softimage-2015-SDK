#ifndef ROTATE_TOOL_HANDLE_INCLUDED
#define ROTATE_TOOL_HANDLE_INCLUDED
///////////////////////////////////////////////////////////////////////////
//
// File: RotateToolHandle.h
//
// Description: Base class for box rotate handles
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
// RotateToolHandle base class
//
////////////////////////////////////////////////////////////////////////////////

class RotateToolHandle : public ToolHandle {
public:
	virtual ~RotateToolHandle();
	CString GetHandleDescription() const { return L"Rotate"; }

protected: // Methods
	RotateToolHandle(); // Abstract base class	
	CStatus InitializeArcball( ToolContext &in_ctxt, LONG x, LONG y, const CVector3 &center, double in_dRadius );
	LONG GetClosestArcballAxis( ToolContext &in_ctxt, LONG x, LONG y, LONG numConstraints, const CVector3 *constraintAxes );
	CRotation GetArcballRotation( ToolContext &in_ctxt, LONG x, LONG y, const CVector3 *constraintAxis = NULL );
	CRotation GetNearestRotationIncrement( const CRotation &in_rot );

protected: // Data
	LONG			m_ballDownX, m_ballDownY;
	CVector3		m_ballCenter;
	double 			m_dBallRadius;
};

#endif // ROTATE_TOOL_HANDLE_INCLUDED
