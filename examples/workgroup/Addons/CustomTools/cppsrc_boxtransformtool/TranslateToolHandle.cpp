///////////////////////////////////////////////////////////////////////////
//
// File: TranslateToolHandle.cpp
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
#include "TranslateToolHandle.h"
#include <xsi_preferences.h>

enum {
	kNoDragAxis = -1,
	kXDragAxis,
	kYDragAxis,
	kZDragAxis,
	kGridDrag,
};

TranslateToolHandle::~TranslateToolHandle()
{}

TranslateToolHandle::TranslateToolHandle( BoxTransformToolDelegate * in_pTool, ToolHandleID in_ID )
{
	Setup( in_pTool, in_ID );
}

void TranslateToolHandle::MouseDown( ToolContext& in_ctxt )
{
	m_objects = m_pTool->GetTargets();
	const BBox &l_bbox = m_pTool->GetBBox();
	in_ctxt.BeginTransformUpdate( m_objects );
	in_ctxt.GetMousePosition( m_startX, m_startY );

	// Setup a manipulation plane parellel to the visible grid and passing through the handle
	in_ctxt.GetGridPlane( m_manipPlane );
	m_initialPosition = GetPosition( in_ctxt );

	CVector3 l_offset = m_manipPlane.Project( m_initialPosition );
	l_offset.Sub( m_initialPosition, l_offset );
	CVector3 l_origin = m_manipPlane.GetOrigin();
	m_manipPlane.SetOrigin( l_origin.AddInPlace( l_offset ) );
	in_ctxt.SetManipulationPlane( m_manipPlane );

	// Compute constraint axes from box edges
	m_activeAxis = kNoDragAxis; // Defined by drag direction
	CVector3 anchor = l_bbox.GetPoint( BBox::kLeftBottomFront, true/*world*/ );
	for ( int i = 0; i < kGridDrag; ++i ) {
		CVector3 axis = l_bbox.GetPoint( l_bbox.GetAdjacentPoint(BBox::kLeftBottomFront, i), true/*world*/ );
		axis.SubInPlace( anchor ).NormalizeInPlace();
		m_dragAxis[i].Set( m_initialPosition, axis );
	}
}

void TranslateToolHandle::MouseDrag( ToolContext& in_ctxt )
{
	LONG x, y;
	in_ctxt.GetMousePosition( x, y );
	CVector3 mouseVec( x-m_startX, y-m_startY, 0.0 );
	if ( mouseVec.GetLength() < kHandleDragThreshold )
		return;

	// Compute constrained drag axis (Note: use best axis and freeze choice when gesture threshold exceeded)
	LONG activeAxis = m_activeAxis;
	if ( activeAxis == kNoDragAxis )
	{
		double projectedLen = 0;
		if ( in_ctxt.IsShiftKeyDown() )
		{
			// Find axis that best matches the mouse drag direction
			activeAxis = GetClosestDragAxis( in_ctxt, mouseVec, m_dragAxis, projectedLen );

			// Did we get a drag axis?
			if ( activeAxis == kNoDragAxis )
				return;
		}
		else
		{
			activeAxis = kGridDrag;
			projectedLen = mouseVec.GetLength();
		}

		// Freeze choice if we have exceeded gesture threshold
		if ( projectedLen > kGestureDragThreshold )
			m_activeAxis = activeAxis;
	}

	CVector3 l_translation;
	if ( activeAxis == kGridDrag )
	{
		// Get projected 3D point
		in_ctxt.EnableSnapping( true );
		CVector3 l_position;
		if ( in_ctxt.GetWorldPosition( x, y, l_position ) != CStatus::OK )
			return;

		// Reject intersection points behind the camera
		CVector3 l_cameraPos;
		if ( in_ctxt.WorldToCamera( l_position, l_cameraPos ) != CStatus::OK || l_cameraPos.GetZ() > 0.0 )
			return;
	
		// Compute relative translation
		l_translation.Sub(l_position, m_initialPosition);
	}
	else 
	{
		// Get world cursor ray
		CLine cursorRay;
		in_ctxt.EnableSnapping( false );
		if ( in_ctxt.GetWorldRay( x, y, cursorRay ) != CStatus::OK )
			return;

		// Will cursor intersect drag axis?
		if ( cursorRay.Parallel( m_dragAxis[activeAxis] ) )
			return;

		// Compute intersection between cursor ray and drag axis
		CVector3 l_position = m_dragAxis[activeAxis].GetClosestPoint( cursorRay );

		// Reject intersection points behind the camera
		CVector3 l_cameraPos;
		if ( in_ctxt.WorldToCamera( l_position, l_cameraPos ) != CStatus::OK || l_cameraPos.GetZ() > 0.0 )
			return;
	
		// Compute relative translation
		l_translation.Sub( l_position, m_initialPosition );

		// Round to the nearest translation snap increment when control key pressed
		if ( in_ctxt.IsControlKeyDown() )
		{
			double dLen = l_translation.GetLength();
			if ( dLen > 1.0e-6 )
			{
				CValue transSnap( 0.0 );
				Application().GetPreferences().GetPreferenceValue( L"TransformProperties.translatesnap", transSnap );
				double dNewLen = GetClosestIncrement( dLen, transSnap );
				l_translation.ScaleInPlace( dNewLen / dLen );
			}
		}
	}

	// Apply the transform
	CTransformation xfo;
	xfo.SetTranslation( l_translation );
	in_ctxt.UpdateTransform( m_objects, xfo, siTrn, siGlobal, siRelative, siXYZ );
}

void TranslateToolHandle::MouseUp( ToolContext& in_ctxt )
{
	in_ctxt.EndTransformUpdate( m_objects );
	m_objects = CRefArray();
	in_ctxt.EnableSnapping( false );
}

void TranslateToolHandle::Draw( ToolContext &in_ctxt )
{
	if ( HandleID() != kTranslateCenterID )
	{
		// Corner/Edge handle
		bool l_bEdge = ( HandleID() >= kTranslateEdgeMinID && HandleID() <= kTranslateEdgeMaxID );
		DrawPoint( in_ctxt, kTranslateHandleSize, kTranslateHandleColor, l_bEdge/*smooth*/ );
	}
	else
	{
		// Center handle
		glDepthMask( GL_FALSE );
		glDisable( GL_DEPTH_TEST );
		DrawPoint( in_ctxt, kCenterSize, kCenterOutlineColor, true/*smooth*/ );
		if ( !IsSelected() )
		{
			// Draw bullseye
			DrawPoint( in_ctxt, kCenterInnerRingSize, kCenterFillColor, true/*smooth*/ );
			DrawPoint( in_ctxt, kCenterInnerCircleSize, kCenterOutlineColor, true/*smooth*/ );
		}
		glEnable( GL_DEPTH_TEST );
		glDepthMask( GL_TRUE );
	}
}

CVector3 TranslateToolHandle::GetPosition( ToolContext &in_ctxt )
{
	const BBox &l_bbox = m_pTool->GetBBox();	
	if ( HandleID() >= kTranslateCornerMinID && HandleID() <= kTranslateCornerMaxID )
		return l_bbox.GetPoint( (BBox::BBoxPoint)(HandleID()-kTranslateCornerMinID), true/*world*/ );

	if ( HandleID() >= kTranslateEdgeMinID && HandleID() <= kTranslateEdgeMaxID )
		return l_bbox.GetMidPoint( (BBox::BBoxEdge)(HandleID()-kTranslateEdgeMinID), true/*world*/ );

	return m_pTool->GetCenter(); // HandleID() == kTranslateCenterID )
}

void TranslateToolHandle::DrawPoint( ToolContext &in_ctxt, LONG in_size, ULONG in_color, bool in_bSmooth )
{
	CVector3 l_Pos = GetPosition( in_ctxt );
	if ( in_bSmooth )
		glEnable( GL_POINT_SMOOTH );
	else
		glDisable( GL_POINT_SMOOTH );
	glPointSize( (GLfloat)in_size );
	SetGLColor( IsSelected() ? kSelectedHandleColor : in_color );
	glBegin( GL_POINTS );
	glVertex3d( l_Pos.GetX(), l_Pos.GetY(), l_Pos.GetZ() );
	glEnd();
	if ( in_bSmooth )
		glDisable( GL_POINT_SMOOTH );
}
