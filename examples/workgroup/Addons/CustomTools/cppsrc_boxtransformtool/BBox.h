#ifndef BBOX_INCLUDED
#define BBOX_INCLUDED
///////////////////////////////////////////////////////////////////////////
//
// File: BBox.h
//
// Description: Box transform bounding box helper class
//
// Copyright 2010 Autodesk, Inc. All rights reserved.
// Use of this software is subject to the terms of the Autodesk license
// agreement provided at the time of installation or download, or which
// otherwise accompanies this software in either electronic or hard copy
// form.
//
///////////////////////////////////////////////////////////////////////////
#include <xsi_math.h>
#include <xsi_toolcontext.h>

using namespace XSI; 
using namespace XSI::MATH; 

class BBox {
public:
	enum BBoxFace { // Faces
		// X=Left/Right, Y=Bottom/Top, Z=Front/Back
		kLeft,
		kRight,
		kBottom,
		kTop,
		kFront,
		kBack
	};

	enum BBoxPoint { // Points
		// X=Left/Right, Y=Bottom/Top, Z=Front/Back
		kLeftBottomFront,
		kLeftBottomBack,
		kLeftTopFront,
		kLeftTopBack,
		kRightBottomFront,
		kRightBottomBack,
		kRightTopFront,
		kRightTopBack
	};
  
	enum BBoxEdge { // Edges
		// X=Left/Right, Y=Bottom/Top, Z=Front/Back
		kLeftBottom,
		kLeftTop,
		kRightBottom,
		kRightTop,
		kLeftFront,
		kLeftBack,
		kRightFront,
		kRightBack,
		kBottomFront,
		kBottomBack,
		kTopFront,
		kTopBack
	};

	BBox();
	BBox( const BBox &x );
	BBox & operator = ( const BBox &x );
	void	 		Clear();
	bool	 		IsValid() const;
	bool	 		IsEmpty() const;
	void	 		IncludePoint( const CVector3 &in_value );
	CVector3 		GetMin( bool in_bWorld = false ) const;
	CVector3 		GetMax( bool in_bWorld = false ) const;
	CVector3 		GetCenter( bool in_bWorld = false ) const;
	CVector3 		GetExtent( bool in_bWorld = false ) const;
	BBoxPoint		GetOppositePoint( BBoxPoint in_eCorner ) const;
	BBoxPoint		GetAdjacentPoint( BBoxPoint in_eCorner, LONG in_AxisIndex ) const;
	BBoxPoint		GetAdjacentPoint( BBoxEdge in_eEdge, LONG in_Index ) const;
	BBoxFace		GetAdjacentFace( BBoxEdge in_eEdge, LONG in_Index ) const;
	CVector3 		GetPoint( BBoxPoint in_eCorner, bool in_bWorld = false  ) const;
	CVector3 		GetPoint( BBoxEdge in_eEdge, LONG in_Index, bool in_bWorld = false ) const;
	CVector3 		GetMidPoint( BBoxEdge in_eEdge, bool in_bWorld = false ) const;
	CVector3 		GetMidPoint( BBoxFace in_eFace, bool in_bWorld = false ) const;
	CVector3		GetNormal( BBoxFace in_eFace, bool in_bWorld = false ) const;
	void			Draw( ToolContext &in_ctxt );
	double			GetApproxViewSize( ToolContext &in_ctxt ) const;
	CVector3   		WorldToBBox( const CVector3 & ) const;
	CVector3		BBoxToWorld( const CVector3 & ) const;
	void			SetTransform( const CTransformation &in_xfo );
	const CTransformation & GetTransform() const;
	const CTransformation & GetInverseTransform() const;

private: // Data
	CVector3		m_minmax[2];
	CTransformation	m_transfo, m_transfoInv;
};

#endif // SMARTMANIPULATORBBOX_INCLUDED
