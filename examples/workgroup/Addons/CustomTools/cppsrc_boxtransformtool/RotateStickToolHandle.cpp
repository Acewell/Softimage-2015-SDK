///////////////////////////////////////////////////////////////////////////
//
// File: RotateStickToolHandle.cpp
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
#include "RotateStickToolHandle.h"

RotateStickToolHandle::~RotateStickToolHandle()
{}

RotateStickToolHandle::RotateStickToolHandle( BoxTransformToolDelegate * in_pTool, ToolHandleID in_ID )
{
	Setup( in_pTool, in_ID );
}

void RotateStickToolHandle::MouseDown( ToolContext& in_ctxt )
{
	m_objects = m_pTool->GetTargets();
	const BBox &l_bbox = m_pTool->GetBBox();
	m_initialXfo = l_bbox.GetTransform();
	in_ctxt.BeginTransformUpdate( m_objects );
	in_ctxt.GetMousePosition( m_startX, m_startY );
	m_dBallRadius = 0.0;
	m_activeConstraint = -1;

	double dScale = GetViewScaleFactor( in_ctxt, l_bbox.GetMidPoint(BBox::kBack, true/*world*/), kRotateStickLength );
	if ( dScale == 0.0 )
		return;

	// Initialize arcball rotation controller
	m_pivot = l_bbox.GetCenter( true/*world*/ );
	m_constraintAxes[0] = l_bbox.GetNormal( BBox::kRight, true/*world*/ );
	m_constraintAxes[1] = l_bbox.GetNormal( BBox::kTop,   true/*world*/ );

	// Find the end of the stick to compute the radius
	CVector3 extent = l_bbox.GetMidPoint( BBox::kBack );
	extent.PutZ( extent.GetZ() + dScale + dScale*kRotateStickSphereRadius/kRotateStickLength );
	extent = l_bbox.BBoxToWorld( extent ); // Convert to world-space
	double dRadius = extent.SubInPlace( m_pivot ).GetLength();

	if ( InitializeArcball( in_ctxt, m_startX, m_startY, m_pivot, dRadius ) != CStatus::OK )
		return;
}

void RotateStickToolHandle::MouseDrag( ToolContext& in_ctxt )
{
	LONG x, y;
	in_ctxt.GetMousePosition( x, y );
	CVector3 mouseVec( x-m_startX, y-m_startY, 0.0 );
	if ( mouseVec.GetLength() < kHandleDragThreshold )
		return;

	// Get closest constraint axis
	LONG activeConstraint = m_activeConstraint;
	if ( activeConstraint < 0 )
	{
		activeConstraint = GetClosestArcballAxis( in_ctxt, x, y, 2, m_constraintAxes );
		if ( activeConstraint < 0 )
			return; // Shouldn't happen

		// Freeze choice if we have exceeded gesture threshold
		if ( mouseVec.GetLength() > kGestureDragThreshold )
			m_activeConstraint = activeConstraint;
	}

	// Get current rotation value
	CRotation rot = GetArcballRotation( in_ctxt, x, y, &m_constraintAxes[activeConstraint] );

	// Negate rotation angle if negative scaling... maybe?

	// Round to the nearest scale snap increment when control key pressed
	if ( in_ctxt.IsControlKeyDown() )
		rot = GetNearestRotationIncrement( rot );

	// Apply the transform
	CTransformation xfo;
	xfo.SetRotation( rot );
	in_ctxt.UpdateTransform( m_objects, xfo, siRot, siGlobal, siRelative, siXYZ, true/*pivot*/, m_pivot );

	// Update the box transform
	CTransformation bboxXfo;
	bboxXfo.Mul( m_initialXfo, xfo );
	m_pTool->UpdateBBoxOrientation( bboxXfo.GetRotation() );
}

void RotateStickToolHandle::MouseUp( ToolContext& in_ctxt )
{
	in_ctxt.EndTransformUpdate( m_objects );
	m_objects = CRefArray();
}

void RotateStickToolHandle::Draw( ToolContext &in_ctxt )
{
	const BBox &l_bbox = m_pTool->GetBBox();
	if ( (IsSelected() && in_ctxt.IsInteracting() && in_ctxt.IsActiveView()) ||
		 l_bbox.GetApproxViewSize( in_ctxt ) > kRotateStickMinBBoxSize )
	{
		double l_dScale = GetViewScaleFactor( in_ctxt, l_bbox.GetMidPoint(BBox::kBack, true/*world*/), kRotateStickLength );
		if ( l_dScale != 0.0 )
		{
			GLdouble mat[16];
			CTransformation transfo = l_bbox.GetTransform();
			transfo.SetScalingFromValues(1.0, 1.0, 1.0); // Cancel out scaling
			transfo.GetMatrix4().Get(
				mat[0],  mat[1],  mat[2],  mat[3],
				mat[4],  mat[5],  mat[6],  mat[7],
				mat[8],  mat[9],  mat[10], mat[11],
				mat[12], mat[13], mat[14], mat[15]
			);
			glPushMatrix();
			glMultMatrixd( mat );

			// Draw stick (if not picking)
			CVector3 l_Pos = l_bbox.GetMidPoint( BBox::kBack );
			CVector3 l_End( l_Pos.GetX(), l_Pos.GetY(), l_Pos.GetZ() + l_dScale );
			if ( !in_ctxt.IsPickDraw() )
			{
				SetGLColor( IsSelected() ? kSelectedHandleColor : kRotateStickLineColor );
				glBegin( GL_LINES );
					glVertex3d( l_Pos.GetX(), l_Pos.GetY(), l_Pos.GetZ() );
					glVertex3d( l_End.GetX(), l_End.GetY(), l_End.GetZ() );
				glEnd();				
			}

			// Draw ball
			ULONG color = IsSelected() ? kSelectedHandleColor : kRotateStickBallColor;
			bool l_bUseLighting = !IsSelected();
			if ( l_bUseLighting )
			{
				GLfloat blackColor[] = { 0.0, 0.0, 0.0, 1.0 };
				GLfloat diffuseColor[] = { RGBA_R(color)/255.0f, RGBA_G(color)/255.0f, RGBA_B(color)/255.0f, RGBA_A(color)/255.0f };
				GLfloat ambientColor[] = { diffuseColor[0]*0.2f, diffuseColor[1]*0.2f, diffuseColor[2]*0.2f, diffuseColor[3] };
				glMaterialfv( GL_FRONT, GL_AMBIENT, ambientColor );
				glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuseColor );
				glMaterialfv( GL_FRONT, GL_SPECULAR, blackColor );
				glMaterialf(  GL_FRONT, GL_SHININESS, 0.0 );
				glEnable( GL_LIGHTING );
			}

			SetGLColor( color );
			glDepthMask( GL_TRUE );
			glTranslated( l_End.GetX(), l_End.GetY(), l_End.GetZ() );
			DrawSphere( l_dScale*kRotateStickSphereRadius/kRotateStickLength, kRotateStickSphereSlices, kRotateStickSphereStacks );
			glDepthMask( GL_FALSE );

			if ( l_bUseLighting )
				glDisable( GL_LIGHTING );
			glPopMatrix();
		}
	}
}

void RotateStickToolHandle::DrawSphere( double in_dRadius, int in_nSlices, int in_nStacks )
{
    GLUquadricObj *quadric = gluNewQuadric();
	gluQuadricDrawStyle( quadric, GLU_FILL );
	gluQuadricNormals( quadric, GLU_SMOOTH );
	gluSphere( quadric, in_dRadius, in_nSlices, in_nStacks );
	gluDeleteQuadric( quadric );
}
