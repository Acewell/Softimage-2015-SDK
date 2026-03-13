///////////////////////////////////////////////////////////////////////////
//
// File: BBox.cpp
//
// Description: Bounding box helper class
//
// Copyright 2010 Autodesk, Inc. All rights reserved.
// Use of this software is subject to the terms of the Autodesk license
// agreement provided at the time of installation or download, or which
// otherwise accompanies this software in either electronic or hard copy
// form.
//
///////////////////////////////////////////////////////////////////////////
#include "BBox.h"
#ifndef linux
#define WIN32_LEAN_AND_MEAN
#include <windows.h> // Needed for OpenGL on windows
#endif
#include <GL/gl.h>

BBox::BBox()
{
	Clear();
}

BBox::BBox( const BBox &x )
{
	*this = x;
}

BBox & BBox::operator = ( const BBox &x )
{
	m_minmax[0] = x.m_minmax[0];
	m_minmax[1] = x.m_minmax[1];
	m_transfo    = x.m_transfo;
	m_transfoInv = x.m_transfoInv;
	return *this;
}

void BBox::Clear()
{
	m_minmax[0].Set(  FLT_MAX,  FLT_MAX,  FLT_MAX );
	m_minmax[1].Set( -FLT_MAX, -FLT_MAX, -FLT_MAX );
	m_transfo.SetIdentity();
	m_transfoInv.SetIdentity();
}

bool BBox::IsValid() const
{
	return m_minmax[0].GetX() <= m_minmax[1].GetX(); // min <= max
}

bool BBox::IsEmpty() const
{
	return !IsValid() || m_minmax[0].EpsilonEquals( m_minmax[1], 1.0e-9 ); // all sides are zero length
}

CVector3 BBox::GetMin( bool in_bWorld ) const
{
	return !in_bWorld ? m_minmax[0] : BBoxToWorld( m_minmax[0] );
}

CVector3 BBox::GetMax( bool in_bWorld ) const
{
	return !in_bWorld ? m_minmax[1] : BBoxToWorld( m_minmax[1] );
}

CVector3 BBox::GetCenter( bool in_bWorld ) const
{
	CVector3 center( 0, 0, 0 );
	if ( !IsEmpty() )
		center.Add( m_minmax[0], m_minmax[1] ).ScaleInPlace( 0.5 );
	return !in_bWorld ? center : BBoxToWorld( center );
}

CVector3 BBox::GetExtent( bool in_bWorld ) const
{
	CVector3 size( 0, 0, 0 );
	if (!IsEmpty() )
		size.Sub( GetMax(in_bWorld), GetMin(in_bWorld) );
	return size;
}

BBox::BBoxPoint BBox::GetOppositePoint( BBoxPoint in_ePoint ) const
{
	static BBoxPoint OppositePointMap[] = {
		/*kLeftBottomFront	-> */ kRightTopBack,
		/*kLeftBottomBack 	-> */ kRightTopFront,
		/*kLeftTopFront		-> */ kRightBottomBack,
		/*kLeftTopBack		-> */ kRightBottomFront,
		/*kRightBottomFront	-> */ kLeftTopBack,
		/*kRightBottomBack	-> */ kLeftTopFront,
		/*kRightTopFront	-> */ kLeftBottomBack,
		/*kRightTopBack		-> */ kLeftBottomFront
	};
	return OppositePointMap[in_ePoint];
}

BBox::BBoxPoint BBox::GetAdjacentPoint( BBoxPoint in_ePoint, LONG in_AxisIndex ) const
{
	static BBoxPoint AdjacentAxisMap[][3] = {
		/*kLeftBottomFront	-> */ { kRightBottomFront,	kLeftTopFront,		kLeftBottomBack		},
		/*kLeftBottomBack 	-> */ { kRightBottomBack, 	kLeftTopBack, 		kLeftBottomFront	},
		/*kLeftTopFront		-> */ { kRightTopFront,		kLeftBottomFront,	kLeftTopBack		},
		/*kLeftTopBack		-> */ { kRightTopBack,		kLeftBottomBack,	kLeftTopFront		},
		/*kRightBottomFront	-> */ { kLeftBottomFront,	kRightTopFront,		kRightBottomBack	},
		/*kRightBottomBack	-> */ { kLeftBottomBack,	kRightTopBack,		kRightBottomFront	},
		/*kRightTopFront	-> */ { kLeftTopFront,		kRightBottomFront,	kRightTopBack		},
		/*kRightTopBack		-> */ { kLeftTopBack,		kRightBottomBack,	kRightTopFront		}
	};
	return AdjacentAxisMap[in_ePoint][in_AxisIndex];
}

BBox::BBoxPoint BBox::GetAdjacentPoint( BBoxEdge in_eEdge, LONG in_Index ) const
{
	static BBoxPoint AdjacentPointMap[][2] = {
		/*kLeftBottom 	-> */ { kLeftBottomFront,	kLeftBottomBack		},
		/*kLeftTop		-> */ { kLeftTopFront,		kLeftTopBack		},
		/*kRightBottom	-> */ { kRightBottomFront,	kRightBottomBack 	},
		/*kRightTop		-> */ { kRightTopFront,		kRightTopBack		},
		/*kLeftFront	-> */ { kLeftBottomFront, 	kLeftTopFront		},
		/*kLeftBack		-> */ { kLeftBottomBack, 	kLeftTopBack		},
		/*kRightFront	-> */ { kRightBottomFront,	kRightTopFront		},
		/*kRightBack	-> */ { kRightBottomBack,	kRightTopBack		},
		/*kBottomFront	-> */ { kLeftBottomFront,	kRightBottomFront	},
		/*kBottomBack	-> */ { kLeftBottomBack,	kRightBottomBack	},
		/*kTopFront		-> */ { kLeftTopFront,		kRightTopFront		},
		/*kTopBack		-> */ { kLeftTopBack,		kRightTopBack		}
	};
	return AdjacentPointMap[in_eEdge][in_Index == 0 ? 0 : 1];
}

BBox::BBoxFace BBox::GetAdjacentFace( BBoxEdge in_eEdge, LONG in_Index ) const
{
	static BBoxFace AdjacentFaceMap[][2] = {
		/*kLeftBottom 	-> */ { kLeft,		kBottom	},
		/*kLeftTop		-> */ { kLeft,		kTop	},
		/*kRightBottom	-> */ { kRight,		kBottom },
		/*kRightTop		-> */ { kRight,		kTop	},
		/*kLeftFront	-> */ { kLeft,	 	kFront	},
		/*kLeftBack		-> */ { kLeft,		kBack	},
		/*kRightFront	-> */ { kRight,		kFront	},
		/*kRightBack	-> */ { kRight,		kBack	},
		/*kBottomFront	-> */ { kBottom,	kFront	},
		/*kBottomBack	-> */ { kBottom,	kBack	},
		/*kTopFront		-> */ { kTop,		kFront	},
		/*kTopBack		-> */ { kTop,		kBack	}
	};
	return AdjacentFaceMap[in_eEdge][in_Index == 0 ? 0 : 1];
}

CVector3 BBox::GetPoint( BBoxPoint in_ePoint, bool in_bWorld ) const
{
	static LONG PointIndexMap[][3] = {
		/* kLeftBottomFront		-> */ { 0, 0, 0 },
		/* kLeftBottomBack		-> */ { 0, 0, 1 },
		/* kLeftTopFront		-> */ { 0, 1, 0 },
		/* kLeftTopBack			-> */ { 0, 1, 1 },
		/* kRightBottomFront	-> */ { 1, 0, 0 },
		/* kRightBottomBack		-> */ { 1, 0, 1 },
		/* kRightTopFront		-> */ { 1, 1, 0 },
		/* kRightTopBack		-> */ { 1, 1, 1 }
	};
	LONG *l_Index = PointIndexMap[in_ePoint];
	CVector3 result( m_minmax[l_Index[0]].GetX(), m_minmax[l_Index[1]].GetY(), m_minmax[l_Index[2]].GetZ() );
	return !in_bWorld ? result : BBoxToWorld( result );
}

CVector3 BBox::GetPoint( BBoxEdge in_eEdge, LONG in_Index, bool in_bWorld ) const
{
	return GetPoint( GetAdjacentPoint( in_eEdge, in_Index ), in_bWorld );
}

CVector3 BBox::GetMidPoint( BBoxEdge in_eEdge, bool in_bWorld ) const
{
	CVector3 result;
	result.Add(GetPoint(in_eEdge, 0), GetPoint(in_eEdge, 1)).ScaleInPlace(0.5);
	return !in_bWorld ? result : BBoxToWorld( result );
}

CVector3 BBox::GetMidPoint( BBoxFace in_eFace, bool in_bWorld ) const
{
	static LONG FacePointMap[][3] = {
		/* kLeft		-> */ { 0, 1, 1 },
		/* kRight		-> */ { 2, 1, 1 },
		/* kBottom		-> */ { 1, 0, 1 },
		/* kTop			-> */ { 1, 2, 1 },
		/* kFront		-> */ { 1, 1, 0 },
		/* kBack		-> */ { 1, 1, 2 }
	};
	LONG *l_Index = FacePointMap[in_eFace];
	CVector3 l_MinMidMax[3] = { m_minmax[0], GetCenter(), m_minmax[1] };
	CVector3 result( l_MinMidMax[l_Index[0]].GetX(), l_MinMidMax[l_Index[1]].GetY(), l_MinMidMax[l_Index[2]].GetZ() );
	return !in_bWorld ? result : BBoxToWorld( result );
}

CVector3 BBox::GetNormal( BBoxFace in_eFace, bool in_bWorld ) const
{
	static CVector3 FaceNormalMap[] = {
		/* kLeft		-> */ CVector3(-1,  0,  0 ),
		/* kRight		-> */ CVector3( 1,  0,  0 ),
		/* kBottom		-> */ CVector3( 0, -1,  0 ),
		/* kTop			-> */ CVector3( 0,  1,  0 ),
		/* kFront		-> */ CVector3( 0,  0, -1 ),
		/* kBack		-> */ CVector3( 0,  0,  1 )
	};
	CVector3 result( FaceNormalMap[in_eFace] );
	if ( in_bWorld )
	{
		// Normals are transformed by adjoint (inverse-transpose)
		CVector4 tmp( result.GetX(), result.GetY(), result.GetZ(), 0.0 ); // Homgeneous vector
		CMatrix4 adjoint( m_transfoInv.GetMatrix4() );
		adjoint.TransposeInPlace();
		tmp.MulByMatrix4InPlace( adjoint );
		result.Set( tmp.GetX(), tmp.GetY(), tmp.GetZ() );
	}
	return result;
}

void BBox::IncludePoint( const CVector3 &in_value )
{
	// Update min
	if ( in_value.GetX() < m_minmax[0].GetX() ) m_minmax[0].PutX( in_value.GetX() );
	if ( in_value.GetY() < m_minmax[0].GetY() ) m_minmax[0].PutY( in_value.GetY() );
	if ( in_value.GetZ() < m_minmax[0].GetZ() ) m_minmax[0].PutZ( in_value.GetZ() );

	// Update max
	if ( in_value.GetX() > m_minmax[1].GetX() ) m_minmax[1].PutX( in_value.GetX() );
	if ( in_value.GetY() > m_minmax[1].GetY() ) m_minmax[1].PutY( in_value.GetY() );
	if ( in_value.GetZ() > m_minmax[1].GetZ() ) m_minmax[1].PutZ( in_value.GetZ() );
}

void BBox::Draw( ToolContext &in_ctxt )
{
	GLdouble mat[16];
	m_transfo.GetMatrix4().Get(
		mat[0],  mat[1],  mat[2],  mat[3],
		mat[4],  mat[5],  mat[6],  mat[7],
		mat[8],  mat[9],  mat[10], mat[11],
		mat[12], mat[13], mat[14], mat[15]
	);
	glPushMatrix();
	glMultMatrixd( mat );
	glBegin( GL_LINE_STRIP );
		glVertex3d( m_minmax[0].GetX(), m_minmax[0].GetY(), m_minmax[0].GetZ() );
		glVertex3d( m_minmax[1].GetX(), m_minmax[0].GetY(), m_minmax[0].GetZ() );
		glVertex3d( m_minmax[1].GetX(), m_minmax[1].GetY(), m_minmax[0].GetZ() );
		glVertex3d( m_minmax[0].GetX(), m_minmax[1].GetY(), m_minmax[0].GetZ() );
		glVertex3d( m_minmax[0].GetX(), m_minmax[0].GetY(), m_minmax[0].GetZ() );
		glVertex3d( m_minmax[0].GetX(), m_minmax[0].GetY(), m_minmax[1].GetZ() );
		glVertex3d( m_minmax[1].GetX(), m_minmax[0].GetY(), m_minmax[1].GetZ() );
		glVertex3d( m_minmax[1].GetX(), m_minmax[1].GetY(), m_minmax[1].GetZ() );
		glVertex3d( m_minmax[0].GetX(), m_minmax[1].GetY(), m_minmax[1].GetZ() );
		glVertex3d( m_minmax[0].GetX(), m_minmax[0].GetY(), m_minmax[1].GetZ() );
	glEnd();
	glBegin( GL_LINES );
		glVertex3d( m_minmax[1].GetX(), m_minmax[0].GetY(), m_minmax[0].GetZ() );
		glVertex3d( m_minmax[1].GetX(), m_minmax[0].GetY(), m_minmax[1].GetZ() );
		glVertex3d( m_minmax[1].GetX(), m_minmax[1].GetY(), m_minmax[0].GetZ() );
		glVertex3d( m_minmax[1].GetX(), m_minmax[1].GetY(), m_minmax[1].GetZ() );
		glVertex3d( m_minmax[0].GetX(), m_minmax[1].GetY(), m_minmax[0].GetZ() );
		glVertex3d( m_minmax[0].GetX(), m_minmax[1].GetY(), m_minmax[1].GetZ() );
	glEnd();
	glPopMatrix();
}

double BBox::GetApproxViewSize( ToolContext &in_ctxt ) const
{
	// Return size of largest diagonal in screen-space
	CVector3 l_Pts[] = {
		GetPoint( kLeftBottomFront, true/*world*/ ),
		GetPoint( kRightTopBack,    true/*world*/ ),
		GetPoint( kLeftBottomBack,  true/*world*/ ),
		GetPoint( kRightTopFront,   true/*world*/ )
	};

	// Convert diagonal points to screen-space
	for ( int i = 0; i < 4; ++i ) {
		if ( in_ctxt.WorldToView( l_Pts[i], l_Pts[i] ) != CStatus::OK )
			return 0.0;
	}

	// Get diagonal lengths and return largest
	double l_LenSq1 = l_Pts[1].SubInPlace( l_Pts[0] ).GetLengthSquared();
	double l_LenSq2 = l_Pts[3].SubInPlace( l_Pts[2] ).GetLengthSquared();
	return sqrt( l_LenSq1 > l_LenSq2 ? l_LenSq1 : l_LenSq2 );
}

const CTransformation & BBox::GetTransform() const
{
	return m_transfo;
}

const CTransformation & BBox::GetInverseTransform() const
{
	return m_transfoInv;
}

void BBox::SetTransform( const CTransformation &in_transfo )
{
	m_transfo = in_transfo;
	m_transfoInv.Invert( m_transfo );
}

CVector3 BBox::WorldToBBox( const CVector3 &in_pos ) const
{
	CVector3 result;
	result.MulByTransformation( in_pos, m_transfoInv );
	return result;
}

CVector3 BBox::BBoxToWorld( const CVector3 &in_pos ) const
{
	CVector3 result;
	result.MulByTransformation( in_pos, m_transfo );
	return result;
}
