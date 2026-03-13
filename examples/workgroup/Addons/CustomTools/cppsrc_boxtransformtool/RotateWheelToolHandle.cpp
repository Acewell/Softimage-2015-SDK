///////////////////////////////////////////////////////////////////////////
//
// File: RotateWheelToolHandle.cpp
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
#include "RotateWheelToolHandle.h"

RotateWheelToolHandle::~RotateWheelToolHandle()
{}

RotateWheelToolHandle::RotateWheelToolHandle( BoxTransformToolDelegate * in_pTool, ToolHandleID in_ID )
{
	Setup( in_pTool, in_ID );
}

void RotateWheelToolHandle::MouseDown( ToolContext& in_ctxt )
{
	m_objects = m_pTool->GetTargets();
	const BBox &l_bbox = m_pTool->GetBBox();
	m_initialXfo = l_bbox.GetTransform();
	in_ctxt.BeginTransformUpdate( m_objects );
	in_ctxt.GetMousePosition( m_startX, m_startY );
	m_dBallRadius = 0.0;

	double dScale = GetViewScaleFactor( in_ctxt, l_bbox.GetMidPoint(BBox::kBack, true/*world*/), kRotateWheelOuterRadius );
	if ( dScale == 0.0 )
		return;

	// Initialize arcball rotation controller
	m_pivot = l_bbox.GetMidPoint( BBox::kBack, true/*world*/ );
	m_constraintAxis = l_bbox.GetNormal( BBox::kBack, true/*world*/ );
	if ( InitializeArcball( in_ctxt, m_startX, m_startY, m_pivot, dScale ) != CStatus::OK )
		return;
}

void RotateWheelToolHandle::MouseDrag( ToolContext& in_ctxt )
{
	LONG x, y;
	in_ctxt.GetMousePosition( x, y );
	CVector3 mouseVec( x-m_startX, y-m_startY, 0.0 );
	if ( mouseVec.GetLength() < kHandleDragThreshold )
		return;

	// Get current rotation value
	CRotation rot = GetArcballRotation( in_ctxt, x, y, &m_constraintAxis );

	// Negate rotation angle if negative scaling... maybe?

	// Round to the nearest rotation snap increment when control key pressed
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

void RotateWheelToolHandle::MouseUp( ToolContext& in_ctxt )
{
	in_ctxt.EndTransformUpdate( m_objects );
	m_objects = CRefArray();
}

void RotateWheelToolHandle::Draw( ToolContext &in_ctxt )
{
	const BBox &l_bbox = m_pTool->GetBBox();
	if ( (IsSelected() && in_ctxt.IsInteracting() && in_ctxt.IsActiveView()) ||
		 l_bbox.GetApproxViewSize( in_ctxt ) > kRotateStickMinBBoxSize )
	{
		double l_dScale = GetViewScaleFactor( in_ctxt, l_bbox.GetMidPoint(BBox::kBack, true/*world*/), kRotateWheelOuterRadius );
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
			ULONG color = IsSelected() ? kSelectedHandleColor : kRotateWheelColor;
			SetGLColor( color );
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
			glDepthMask( GL_TRUE );
			CVector3 l_Pos = l_bbox.GetMidPoint( BBox::kBack );
			glTranslated( l_Pos.GetX(), l_Pos.GetY(), l_Pos.GetZ() );
			glRotated( 90.0, 1.0, 0.0, 0.0 );
			DrawTorus( l_dScale/kRotateWheelOuterRadius*kRotateWheelInnerRadius, l_dScale, kRotateWheelSides, kRotateWheelRings );
			glDepthMask( GL_FALSE );
			if ( l_bUseLighting )
				glDisable( GL_LIGHTING );
			glPopMatrix();
		}
	}
}

void RotateWheelToolHandle::DrawTorus( double in_dInnerRadius, double in_dOuterRadius, int in_nSides, int in_nRings )
{
	double l_dR1 = in_dOuterRadius, l_dR2 = in_dInnerRadius;
	double l_dTwoPIRings = 2.0*PI/in_nRings, l_dTwoPISides = 2.0*PI/in_nSides;
	double l_dTheta = 0.0, l_dSinTheta = 0.0, l_dCosTheta = 1.0;
    for ( int i = 0; i < in_nRings; ++i ) 
	{
		double l_dTheta1 = (i+1)*l_dTwoPIRings;
		double l_dSinTheta1 = sin( l_dTheta1 );
		double l_dCosTheta1 = cos( l_dTheta1 );
		double l_dPhi = 0.0, l_dSinPhi = 0.0, l_dCosPhi = 1.0;
		for (int j = 0; j < in_nSides; j++)
		{
			double l_dPhi1 = (j+1)*l_dTwoPISides;
			double l_dSinPhi1 = sin( l_dPhi1 );
			double l_dCosPhi1 = cos( l_dPhi1 );

			glBegin(GL_QUADS);
				glNormal3d( l_dCosTheta*l_dCosPhi1, l_dSinPhi1, l_dSinTheta*l_dCosPhi1 );
				glVertex3d( l_dCosTheta*(l_dR1+l_dR2*l_dCosPhi1), l_dR2*l_dSinPhi1, l_dSinTheta*(l_dR1+l_dR2*l_dCosPhi1) );
				glNormal3d( l_dCosTheta1*l_dCosPhi1, l_dSinPhi1, l_dSinTheta1*l_dCosPhi1 );
				glVertex3d( l_dCosTheta1*(l_dR1+l_dR2*l_dCosPhi1), l_dR2*l_dSinPhi1, l_dSinTheta1*(l_dR1+l_dR2*l_dCosPhi1) );
				glNormal3d( l_dCosTheta1*l_dCosPhi, l_dSinPhi, l_dSinTheta1*l_dCosPhi );
				glVertex3d( l_dCosTheta1*(l_dR1+l_dR2*l_dCosPhi), l_dR2*l_dSinPhi, l_dSinTheta1*(l_dR1+l_dR2*l_dCosPhi) );
				glNormal3d( l_dCosTheta*l_dCosPhi, l_dSinPhi, l_dSinTheta*l_dCosPhi );
				glVertex3d( l_dCosTheta*(l_dR1+l_dR2*l_dCosPhi), l_dR2*l_dSinPhi, l_dSinTheta*(l_dR1+l_dR2*l_dCosPhi) );
			glEnd();

			l_dPhi    = l_dPhi1;
			l_dCosPhi = l_dCosPhi1;
			l_dSinPhi = l_dSinPhi1;
		}
		l_dTheta    = l_dTheta1;
		l_dCosTheta = l_dCosTheta1;
		l_dSinTheta = l_dSinTheta1;
    }
}
