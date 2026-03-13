///////////////////////////////////////////////////////////////////////////
//
// File: DimensionToolHandle.cpp
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
#include <stdio.h>
#include "DimensionToolHandle.h"
#include <wchar.h>

inline double DistanceBetween( const CVector3 &a, const CVector3 &b )
{
	CVector3 tmp; return tmp.Sub(a, b).GetLength();
}

inline double Bias( double a, double t )
{
	// @devnote: Fast (and symmetric) alternative to Perlin's bias function (Graphics Gems IV)
	// 
	//   0.5: Bias(x) = x (identity)
	// < 0.5: Bias(x) < x (amplify low values)
	// > 0.5: Bias(x) > x (amplify high values)
	//
	return ( t > 0.0 && t < 1.0 ? (t / ((1.0/a - 2.0)*(1.0 - t) + 1.0)) : t );
}

DimensionToolHandle::~DimensionToolHandle()
{}

DimensionToolHandle::DimensionToolHandle( BoxTransformToolDelegate * in_pTool, ToolHandleID in_ID )
:	m_length(0)
{
	Setup( in_pTool, in_ID );
	m_textBox[0] = m_textBox[1] = m_textBox[2] = m_textBox[3] = 0;
	m_editBox[0] = m_editBox[1] = m_editBox[2] = m_editBox[3] = 0;
}

void DimensionToolHandle::MouseUp( ToolContext &in_ctxt )
{
	LONG x, y;
	if ( in_ctxt.GetMousePosition( x, y ) == CStatus::OK )
	{
		if ( x > m_textBox[0] && x < m_textBox[2] && y > m_textBox[1] && y < m_textBox[3] )
		{
			// Sanity check (so we don't abort if number is too big)
			if ( m_length > 1.0e12 ) return;

			wchar_t l_Scratch[128];
			swprintf( l_Scratch, sizeof(l_Scratch)/sizeof(l_Scratch[0]), L"%0.3f", m_length );
			CString editText = l_Scratch;
			if ( in_ctxt.EditTextString( editText, m_editBox[0], m_editBox[1], m_editBox[2]-m_editBox[0], m_editBox[3]-m_editBox[1] ) == CStatus::OK )
			{
				wchar_t *stop = 0;
				const wchar_t *start = editText.GetWideString();
				double value = wcstod( start, &stop );
				if ( value != 0.0 || stop != start ) // See wcstod docs for details...
				{
					// Got a valid number
					ScaleObjects( value / m_length );
				}
			}
		}
	}
}

void DimensionToolHandle::Draw( ToolContext &in_ctxt )
{
	if ( in_ctxt.IsActiveView() )
	{
		bool wasDrawn = false;
		const BBox &l_bbox = m_pTool->GetBBox();
		if ( l_bbox.GetApproxViewSize( in_ctxt ) > kDimensionMinBBoxSize )
		{
			static BBox::BBoxEdge AxisEdgeMap[][4] = {
				/* X -> */ { BBox::kBottomFront, BBox::kBottomBack, BBox::kTopFront,    BBox::kTopBack   },
				/* Y -> */ { BBox::kLeftFront,   BBox::kLeftBack,   BBox::kRightFront,  BBox::kRightBack },
				/* Z -> */ { BBox::kLeftBottom,  BBox::kLeftTop,    BBox::kRightBottom, BBox::kRightTop  },
			};

			// Identify which edge to label
			CVector3 eye( 0, 0, 0 ); // Eye is always at origin in camera-space
			LONG axis = HandleID() - kDimensionScaleXID;
			in_ctxt.CameraToWorld( eye, eye );
			eye = l_bbox.WorldToBBox( eye ); // Use bbox space

			CVector3 targetPos( -FLT_MIN, -FLT_MAX, 0 );
			BBox::BBoxEdge targetEdge;
			CVector3 targetEdgePt1, targetEdgePt2, targetEdgeMid;

			// For each candidate edge...
			bool foundEdge = false;
			for ( int i = 0; i < 4; ++i )
			{
				BBox::BBoxEdge edge = AxisEdgeMap[axis][i];

				// Only consider silhouette edges
				bool backfacing[2];
				for ( int j = 0; j < 2; ++j )
				{
					BBox::BBoxFace face = l_bbox.GetAdjacentFace( edge, j );
					CVector3 normal = l_bbox.GetNormal(face);
					CVector3 view; view.Sub( eye, l_bbox.GetMidPoint(face) );
					backfacing[j] = ( normal.Dot( view ) < 0.0 );
				}
				if ( backfacing[0] == backfacing[1] )
					continue; // Not a silhouette edge

				// Pick rightmost edge followed by topmost
				CVector3 edgePt1, edgePt2, edgeMid;
				if ( in_ctxt.WorldToView( l_bbox.GetPoint(edge, 0, true/*world*/), edgePt1 ) != CStatus::OK || 
					 in_ctxt.WorldToView( l_bbox.GetPoint(edge, 1, true/*world*/), edgePt2 ) != CStatus::OK ||
					 in_ctxt.WorldToView( l_bbox.GetMidPoint(edge, true/*world*/), edgeMid ) != CStatus::OK )
					continue;
				
				// Remove depth information
				edgePt1.PutZ( 0.0 );
				edgePt2.PutZ( 0.0 );
				edgeMid.PutZ( 0.0 );

				// Exclude edges that are too small in screen-space
				double dist = DistanceBetween( edgePt1, edgePt2 );
				if ( dist < kDimensionMinEdgeSize )
					continue;

				// Pick edge based on maximum screen-space X followd by Y
				CVector3 delta;
				delta.Sub( edgeMid, targetEdgeMid );
				bool rightMost = ( delta.GetX() > 0 );
				bool sameXButHigher = ( fabs(delta.GetX()) < 1.0e-3 && delta.GetY() > 0 );
				if ( rightMost || sameXButHigher )
				{
					targetEdge    = edge;
					targetEdgePt1 = edgePt1;
					targetEdgePt2 = edgePt2;
					targetEdgeMid = edgeMid;
					foundEdge = true;
				}
			}

			if ( foundEdge ) {
				if ( DrawDimension( in_ctxt, l_bbox, targetEdge, targetEdgePt1, targetEdgePt2, targetEdgeMid ) == CStatus::OK )
					wasDrawn = true;
			}
		}

		if ( !wasDrawn )
		{
			m_length = 0;
			m_textBox[0] = m_textBox[1] = m_textBox[2] = m_textBox[3] = 0;
			m_editBox[0] = m_editBox[1] = m_editBox[2] = m_editBox[3] = 0;
		}
	}
}

CStatus DimensionToolHandle::DrawDimension( ToolContext &in_ctxt, const BBox &in_bbox, BBox::BBoxEdge in_eEdge, CVector3 &in_Pt1, CVector3 &in_Pt2, CVector3 &in_Mid )
{
	// Get center of bbox in screen-space
	CVector3 boxCenter = in_bbox.GetCenter( true/*world*/ );
	if ( in_ctxt.WorldToView( boxCenter, boxCenter ) != CStatus::OK )
		return CStatus::Fail;
	boxCenter.PutZ( 0.0 ); // Remove depth information

	// Calculate distance and get display string
	// Note: distance is rotation invariant so we can calculate in bbox-space
	CVector3 edgePt1 = in_bbox.GetPoint( in_eEdge, 0 );
	CVector3 edgePt2 = in_bbox.GetPoint( in_eEdge, 1 );
	m_length = DistanceBetween( edgePt1, edgePt2 );

	// Sanity check (so we don't abort if number is too big)
	if ( m_length > 1.0e12 )
		return CStatus::Fail;

	// Get text size (for display and editing)
	wchar_t l_Scratch[128];
	LONG descent = 0, halfWidth = 0, halfHeight = 0, halfEditWidth = 0, halfEditHeight = 0;
	swprintf( l_Scratch, sizeof(l_Scratch)/sizeof(l_Scratch[0]), L" %0.3f ", m_length );
	in_ctxt.GetTextSize( l_Scratch, halfEditWidth, halfEditHeight, descent );
	swprintf( l_Scratch, sizeof(l_Scratch)/sizeof(l_Scratch[0]), L" %0.1f ", m_length );
	in_ctxt.GetTextSize( l_Scratch, halfWidth, halfHeight, descent );
	halfWidth      = halfWidth/2      + kDimensionTextMargin;
	halfHeight     = halfHeight/2     + kDimensionTextMargin;
	halfEditWidth  = halfEditWidth/2  + kDimensionEditMargin;
	halfEditHeight = halfEditHeight/2 + kDimensionEditMargin;

	// Compute initial offset from angle of line in screen-space
	CVector3 viewVec; viewVec.Sub( in_Pt2, in_Pt1 );
	double viewLen = viewVec.GetLength();

	// @devnote: use bias to push text further from the line at shallow angles
	double scaleX = Bias( 0.8, fabs(viewVec.GetY()) / viewLen );
	double scaleY = Bias( 0.8, fabs(viewVec.GetX()) / viewLen );
	CVector3 offset( scaleX * (halfWidth + kDimensionTextOffset), scaleY * (halfHeight + kDimensionTextOffset), 0.0 );
	if ( viewVec.GetX() < 0 ) offset.PutX( -offset.GetX() );
	if ( viewVec.GetY() > 0 ) offset.PutY( -offset.GetY() );
	CVector3 textPos; textPos.Add( in_Mid, offset );

	// Finally position label on the outside of the edge (based on bbox center)
	if ( !in_Mid.EpsilonEquals( boxCenter, 1.0e-3 ) )
	{
		CLine edgeLine( in_Pt1, viewVec );
		CVector3 boxVec  = edgeLine.Project( boxCenter ).SubInPlace( boxCenter );
		CVector3 textVec = edgeLine.Project( textPos ).SubInPlace( textPos );
		if ( textVec.Dot( boxVec ) >= 0.0 )
		{
			// Flip label to other side of the edge...
			offset.NegateInPlace();
			textPos.Add( in_Mid, offset );
		}
	}
	
	// Save text location
	LONG x = (LONG)textPos.GetX();
	LONG y = (LONG)textPos.GetY() + descent;
	if ( !in_ctxt.IsPickDraw() )
	{
		m_textBox[0] = x - halfWidth;
		m_textBox[1] = y - halfHeight - descent;
		m_textBox[2] = x + halfWidth;
		m_textBox[3] = y + halfHeight - descent;

		m_editBox[0] = x - halfEditWidth;
		m_editBox[1] = y - halfEditHeight - descent;
		m_editBox[2] = x + halfEditWidth;
		m_editBox[3] = y + halfEditHeight - descent;
	}

	// Draw setup
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glEnable( GL_BLEND );

	// Draw box
	SetGLColor( kDimensionBackColor );
	glBegin( GL_QUADS );
		glVertex2d( m_textBox[0], m_textBox[3] );
		glVertex2d( m_textBox[0], m_textBox[1] );
		glVertex2d( m_textBox[2], m_textBox[1] );
		glVertex2d( m_textBox[2], m_textBox[3] );
	glEnd();

	// Draw text
	SetGLColor( kDimensionTextColor );
	glRasterPos2d( x, y );
	in_ctxt.DrawTextString( l_Scratch, siCenterAlign, siCenterAlign );

	// Cleanup 
	glDisable( GL_BLEND );
	return CStatus::OK;
}


void DimensionToolHandle::ScaleObjects( double in_scale )
{
	double scale[3] = { 1.0, 1.0, 1.0 };
	LONG axis = HandleID()-kDimensionScaleXID;
	CRefArray targets = m_pTool->GetTargets();
	bool l_bSetPivot = (targets.GetCount() > 1);
	LONG l_RefMode = (l_bSetPivot ? siObjCtr : siLocal);
	scale[axis] = in_scale;

	CValue result;
	CValueArray args;
	args.Add( targets.GetAsText() );			// Objects
	args.Add( CValue(scale[0]) );				// Scale X
	args.Add( CValue(scale[1]) );				// Scale Y
	args.Add( CValue(scale[2]) );				// Scale Z
	args.Add( CValue((LONG)siRelative) );		// Delta
	args.Add( CValue((LONG)l_RefMode) );		// RefMode
	args.Add( CValue((LONG)siObj) );			// CenterMode
	args.Add( CValue((LONG)(siX << axis)) );	// Axis
	if ( l_bSetPivot )
	{
		CVector3 pivot = m_pTool->GetBBox().GetCenter( true/*world*/ );
		args.Add( CValue() );					// Not used
		args.Add( CValue() );					// Not used
		args.Add( CValue() );					// Not used
		args.Add( CValue(true) );				// Pivot
		args.Add( CValue(pivot.GetX()) );		// Pivot X
		args.Add( CValue(pivot.GetY()) );		// Pivot Y
		args.Add( CValue(pivot.GetZ()) );		// Pivot Z
	}
	Application().ExecuteCommand( L"Scale", args, result );
}
