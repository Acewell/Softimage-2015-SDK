///////////////////////////////////////////////////////////////////////////
//
// File: ScaleToolHandle.cpp
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
#include "ScaleToolHandle.h"
#include <xsi_preferences.h>

enum {
	kNoScaleAxis = -1,
	kXScaleAxis,
	kYScaleAxis,
	kZScaleAxis,
	kDiagonalScaleAxis
};

ScaleToolHandle::~ScaleToolHandle()
{}

ScaleToolHandle::ScaleToolHandle( BoxTransformToolDelegate * in_pTool, ToolHandleID in_ID )
{
	Setup( in_pTool, in_ID );
}

void ScaleToolHandle::MouseDown( ToolContext& in_ctxt )
{
	m_objects = m_pTool->GetTargets();
	m_startBBox = m_pTool->GetBBox();
	in_ctxt.BeginTransformUpdate( m_objects );
	in_ctxt.GetMousePosition( m_startX, m_startY );

	// Compute scale constraint axes
	CVector3 initial = m_startBBox.GetPoint(GetBoxPoint(), true/*world*/);
	m_pivot = m_startBBox.GetPoint(m_startBBox.GetOppositePoint(GetBoxPoint()), true/*world*/);
	m_scaleAxis[kDiagonalScaleAxis].Set( m_pivot, CVector3(initial).SubInPlace(m_pivot) ); // XYZ (diagonal)

	if ( m_objects.GetCount() > 1 )
	{
		// Uniform scaling (Note: don't need to compute X/Y/Z axes)
		m_activeAxis = kDiagonalScaleAxis;
	}
	else
	{
		// Single axis scaling
		m_activeAxis = kNoScaleAxis; // Defined by drag direction
		for ( int i = 0; i < kDiagonalScaleAxis; ++i ) {
			CVector3 anchor = m_startBBox.GetPoint(m_startBBox.GetAdjacentPoint(GetBoxPoint(), i), true/*world*/);
			m_scaleAxis[i].Set( anchor, CVector3(initial).SubInPlace(anchor) );
		}
	}
}

void ScaleToolHandle::MouseDrag( ToolContext& in_ctxt )
{
	LONG x, y;
	in_ctxt.GetMousePosition( x, y );
	CVector3 mouseVec( x-m_startX, y-m_startY, 0.0 );
	if ( mouseVec.GetLength() < kHandleDragThreshold )
		return;

	// Get world cursor ray
	CLine cursorRay;
	if ( in_ctxt.GetWorldRay( x, y, cursorRay ) != CStatus::OK )
		return;

	// Compute constrained drag axis (Note: use best axis and freeze choice when gesture threshold exceeded)
	LONG activeAxis = ( in_ctxt.IsShiftKeyDown() ? kDiagonalScaleAxis : m_activeAxis );
	if ( activeAxis == kNoScaleAxis )
	{
		// Find axis that best matches the mouse drag direction
		double projectedLen = 0;
		activeAxis = GetClosestDragAxis( in_ctxt, mouseVec, m_scaleAxis, projectedLen );

		// Did we get a drag axis?
		if ( activeAxis == kNoScaleAxis )
			return;

		// Freeze choice if we have exceeded gesture threshold
		if ( projectedLen > kGestureDragThreshold )
			m_activeAxis = activeAxis;
	}

	// Will cursor intersect drag axis?
	if ( cursorRay.Parallel( m_scaleAxis[activeAxis] ) )
		return;

	// Compute intersection between cursor ray and drag axis
	CVector3 dragPoint = m_scaleAxis[activeAxis].GetClosestPoint( cursorRay );

	// Reject intersection points behind the camera
	CVector3 cameraPoint;
	if ( in_ctxt.WorldToCamera( dragPoint, cameraPoint ) != CStatus::OK || cameraPoint.GetZ() > 0.0 )
		return;

	// The parametric value represents our scale factor directly
	double dScale = m_scaleAxis[activeAxis].GetParameter( dragPoint );

	// Round to the nearest scale snap increment when control key pressed
	if ( in_ctxt.IsControlKeyDown() )
	{
		CValue scaleSnap( 0.0 );
		Application().GetPreferences().GetPreferenceValue( L"TransformProperties.scalesnap", scaleSnap );
		dScale = GetClosestIncrement( dScale, scaleSnap );
	}

 	// Don't allow negative scaling
	if ( dScale < 0.001 )
		dScale = 0.001;

	// Force uniform scaling if more than one object is selected or shift key pressed
	double scale[3] = { 1.0, 1.0, 1.0 };
	if ( activeAxis == kDiagonalScaleAxis )
		scale[0] = scale[1] = scale[2] = dScale;
	else
		scale[activeAxis] = dScale;

	// Apply the transform
	CTransformation xfo;
	xfo.SetScalingFromValues( scale[0], scale[1], scale[2] );
	in_ctxt.UpdateTransform( m_objects, xfo, siScl, siLocal, siRelative, siXYZ, true/*pivot*/, m_pivot );
}

void ScaleToolHandle::MouseUp( ToolContext& in_ctxt )
{
	in_ctxt.EndTransformUpdate( m_objects );
	m_objects = CRefArray();
}

void ScaleToolHandle::Draw( ToolContext &in_ctxt )
{
	const BBox &l_bbox = m_pTool->GetBBox();	
	CVector3 l_Pos = l_bbox.GetPoint( GetBoxPoint(), true/*world*/ );
	glEnable( GL_POINT_SMOOTH );
	glPointSize( (GLfloat)kScaleHandleSize );
	SetGLColor( IsSelected() ? kSelectedHandleColor : kScaleHandleColor );
	glBegin( GL_POINTS );
	glVertex3d( l_Pos.GetX(), l_Pos.GetY(), l_Pos.GetZ() );
	glEnd();
	glDisable( GL_POINT_SMOOTH );
}
