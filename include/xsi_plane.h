//*****************************************************************************
/*!
   \file xsi_plane.h
   \brief CPlane class declaration.

	Copyright 2010 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIPLANE_H__
#define __XSIPLANE_H__

#include "sicppsdk.h"
#include "xsi_status.h"
#include "xsi_vector3.h"
#include "xsi_line.h"
#include <math.h>

namespace XSI {

namespace MATH {

//*****************************************************************************
/*! \class CPlane xsi_plane.h
	\brief A parametric 3D plane. 

	\sa CVector3, CPlane

  	\eg
	\code
	\endcode
 */
//*****************************************************************************
class SICPPSDKDECL CPlane
{
public:
	/*! Default constructor. */
	SICPPSDK_INLINE CPlane();

	/*! Construct a plane through a point with the given normal.
	\param in_point Point on the plane
	\param in_normal Normal vector
	*/
	SICPPSDK_INLINE CPlane( const CVector3 &in_point, const CVector3 &in_normal );

	/*! Construct a plane through a point with the given tangents.
	\param in_point Point on the plane
	\param in_tangentU First tangent vector
	\param in_tangentV Second tangent vector
	*/
	SICPPSDK_INLINE CPlane( const CVector3 &in_point, const CVector3 &in_tangentU, const CVector3 &in_tangentV );

	/*! Copy constructor.
	\param in_plane Line to copy
	*/
	SICPPSDK_INLINE CPlane( const CPlane &in_plane );

	/*! Default destructor. */
	SICPPSDK_INLINE ~CPlane();

	/*! Assignment operator.
	\param in_plane Line to copy
	\return A reference to this plane.
	*/
	SICPPSDK_INLINE CPlane & operator=( const CPlane & in_plane );

	/*! Equality operator tests the strict equality of this CPlane with the specified plane.
	\param in_plane Operand plane.
	\return true if equal else false.
	\sa CPlane::Equals
	*/
	SICPPSDK_INLINE bool operator ==(const CPlane &in_plane )const;

	/*! Inequality operator tests the strict inequality of this CPlane with the specified plane.
	\param in_plane Operand plane.
	\return true if equal else false.
	\sa CPlane::Equals
	*/
	SICPPSDK_INLINE bool operator !=(const CPlane &in_plane )const;

	/*! Tests the equality of this plane with the specified plane, with a tolerance of Epsilon.
	\param in_plane Operand plane.
	\param in_dEpsilon Error margin \n
	\b Possible \b Values: [0, +INF[ should be a positive value
	\return true if equal else false.
	*/
	SICPPSDK_INLINE bool EpsilonEquals(const CPlane &in_plane, double in_dEpsilon)const;

	/*! Tests the strict equality of this plane with the specified plane.
	\param in_plane Operand plane.
	\return true if equal else false.
	*/
	SICPPSDK_INLINE bool Equals(const CPlane &in_plane)const;

	/*! Tests whether two planes are parallel.
	\param in_plane Operand plane.
	\return true if equal else false.
	*/
	bool Parallel(const CPlane &in_plane)const;

	/*! Tests whether two planes are coplanar.
	\param in_plane Operand plane.
	\return true if equal else false.
	*/
	bool Coplanar(const CPlane &in_plane)const;

	/*! Return distance fromt the plane to the given point.
	\return Distance to input point
	*/
	SICPPSDK_INLINE double GetDistance(const CVector3 &in_point)const;

	/*! Return position on plane for given parameters.
	\param in_U First parameter.
	\param in_V Second parameter.
	\return Position corresponding to input parameter
	*/
	SICPPSDK_INLINE CVector3 GetPosition(double in_U, double inV)const;

	/*! Return parameter on plane closest to input point.
	\param out_U First projection parameter.
	\param out_V Second projection parameter.
	*/
	void GetParameters(const CVector3 &in_point, double &out_U, double &out_V)const;

	/*! Return intersection of this plane with the given line.
	\param in_line Line to intersect.
	\param out_point Closest point of intersection on plane.
	\return true if line intersects the plane else false.
	*/
	bool Intersect(const CLine &in_line, CVector3 &out_point)const;

	/*! Return projection of this point on to the plane.
	\return Closest point on the plane
	*/
	SICPPSDK_INLINE CVector3 Project(const CVector3 &in_point)const;

	/*! Return reflection of this point across the plane.
	\return Reflected point
	*/
	SICPPSDK_INLINE CVector3 Reflect(const CVector3 &in_point)const;

	/*! Return projection of line on the plane.
	\return Projection of input line on the plane
	*/
	SICPPSDK_INLINE CLine ProjectLine(const CLine &in_line)const;

	/*! Return reflection of line across the plane.
	\return Reflected line
	*/
	SICPPSDK_INLINE CLine ReflectLine(const CLine &in_line)const;

	/*! Return CMatrix4 that transforms points across this plane.
	\param out_matrix4 Matrix.
	\return Reference to output matrix
	*/
	CMatrix4 & GetMirrorTransform(CMatrix4 &out_matrix4)const;

	/*! Return origin of the plane.
	\return Reference to origin.
	*/
	SICPPSDK_INLINE const CVector3 &GetOrigin()const;

	/*! Return normal for the plane.
	\return Reference to normal.
	*/
	SICPPSDK_INLINE const CVector3 &GetNormal()const;

	/*! Return first tangent for the plane.
	\return Reference to tangent.
	*/
	SICPPSDK_INLINE const CVector3 &GetTangentU()const;

	/*! Return second tangent for the plane.
	\return Reference to tangent.
	*/
	SICPPSDK_INLINE const CVector3 &GetTangentV()const;

	/*! Set origin of the plane.
	\param in_point Point on the plane
	\return A reference to this plane.
	*/
	SICPPSDK_INLINE CPlane &SetOrigin(const CVector3 &in_point);

	/*! Set normal for the plane.
	\param in_normal Normal vector.
	\return A reference to this plane.
	*/
	CPlane &SetNormal(const CVector3 &in_normal);

	/*! Set direction of the plane.
	\param in_U First tangent vector.
	\param in_V Second tangent vector.
	\return A reference to this plane.
	*/
	CPlane &SetTangents(const CVector3 &in_U, const CVector3 &in_V);

	/*! Set origin and normal of the plane.
	\param in_point Point on the plane
	\param in_direction Normal vector.
	\return A reference to this plane.
	*/
	SICPPSDK_INLINE CPlane &Set(const CVector3 &in_point, const CVector3 &in_normal);

	/*! Set origin and tangents of the plane.
	\param in_point Point on the plane
	\param in_U First tangent vector.
	\param in_V Second tangent vector.
	\return A reference to this plane.
	*/
	SICPPSDK_INLINE CPlane &Set(const CVector3 &in_point, const CVector3 &in_U, const CVector3 &in_V);

	/*! Right-multiplies this plane by the matrix m in place (this = this . m ).
	\param in_matrix3 Operand matrix.
	\return A reference to this plane.
	\sa CPlane::MulByMatrix3InPlace
	*/
	SICPPSDK_INLINE CPlane& operator *=(const CMatrix3& in_matrix3);

	/*! Right-multiplies this plane by the matrix m in place (this = this . m ).
	\param in_matrix4 Operand matrix.
	\return A reference to this plane.
	\sa CPlane::MulByMatrix4InPlace
	*/
	SICPPSDK_INLINE CPlane& operator *=(const CMatrix4& in_matrix4);

	/*! Right-multiplies this plane by the transformation t in place (this = this . t).
	\param in_transformation transformation operand.
	\return A reference to this plane.
	\sa CPlane::MulByTransformationInPlace
	*/
	SICPPSDK_INLINE CPlane& operator *=(const CTransformation& in_transformation);

	/*! Right-multiplies this plane by the matrix m in place (this = this . m ).
	\param in_matrix3 Operand matrix.
	\return A reference to this plane.
	*/
	SICPPSDK_INLINE CPlane& MulByMatrix3InPlace(const CMatrix3& in_matrix3);

	/*! Right-multiplies the plane l by the matrix m and store the result in this plane (this = l . m ).
	\param in_plane Operand plane
	\param in_matrix3 Operand matrix.
	\return A reference to this plane.
	*/
	SICPPSDK_INLINE CPlane& MulByMatrix3(const CPlane &in_plane, const CMatrix3 &in_matrix3);

	/*! Right-multiplies this plane by the matrix m in place (this = this . m ).
	\param in_matrix4 Operand matrix.
	\return A reference to this plane.
	*/
	SICPPSDK_INLINE CPlane& MulByMatrix4InPlace(const CMatrix4& in_matrix4);

	/*! Right-multiplies the plane l by the matrix m and store the result in this plane (this = l . m ).
	\param in_plane Operand plane
	\param in_matrix4 Operand matrix.
	\return A reference to this plane.
	*/
	SICPPSDK_INLINE CPlane& MulByMatrix4(const CPlane &in_plane, const CMatrix4 &in_matrix4);

	/*! Right-multiplies this plane by the transformation t in place (this = this . t).
	\param in_transformation transformation operand.
	\return A reference to this plane.
	*/
	SICPPSDK_INLINE CPlane& MulByTransformationInPlace(const CTransformation &in_transformation);

	/*! Right-multiplies the plane l by the transformation t and stores the result in this plane (this = l . t ).
	\param in_plane Operand plane.
	\param in_transformation transformation operand.
	\return A reference to this plane.
	*/
	SICPPSDK_INLINE CPlane& MulByTransformation(const CPlane &in_plane, const CTransformation &in_transformation);

private:
	CVector3	m_vOrigin;
	CVector3	m_vNormal;
	CVector3	m_vTangentU;
	CVector3	m_vTangentV;
};

//inline functions
SICPPSDK_INLINE CPlane::CPlane()
: m_vOrigin(0.0, 0.0, 0.0), m_vTangentU(1.0, 0.0, 0.0), m_vTangentV(0.0, 1.0, 0.0), m_vNormal( 0.0, 0.0, 1.0 )
{
}

SICPPSDK_INLINE CPlane::CPlane( const CPlane& in_plane )
: m_vOrigin(in_plane.m_vOrigin), m_vTangentU(in_plane.m_vTangentU), m_vTangentV(in_plane.m_vTangentV), m_vNormal(in_plane.m_vNormal)
{
}

SICPPSDK_INLINE CPlane::~CPlane()
{}

SICPPSDK_INLINE CPlane::CPlane( const CVector3 &in_pt, const CVector3 &in_normal )
: m_vOrigin(in_pt)
{
	SetNormal( in_normal );
}

SICPPSDK_INLINE CPlane::CPlane( const CVector3 &in_pt, const CVector3 &in_U, const CVector3 &in_V )
: m_vOrigin(in_pt)
{
	SetTangents( in_U, in_V );
}

SICPPSDK_INLINE CPlane& CPlane::operator=( const CPlane & in_plane )
{
	m_vOrigin   = in_plane.m_vOrigin;
	m_vNormal   = in_plane.m_vNormal;
	m_vTangentU = in_plane.m_vTangentU;
	m_vTangentV = in_plane.m_vTangentV;
	return *this;
}

SICPPSDK_INLINE const CVector3 &CPlane::GetOrigin()const
{
	return m_vOrigin;
}

SICPPSDK_INLINE const CVector3 &CPlane::GetNormal()const
{
	return m_vNormal;
}

SICPPSDK_INLINE const CVector3 &CPlane::GetTangentU()const
{
	return m_vTangentU;
}

SICPPSDK_INLINE const CVector3 &CPlane::GetTangentV()const
{
	return m_vTangentV;
}

SICPPSDK_INLINE CPlane & CPlane::Set(const CVector3 &in_point, const CVector3 &in_normal)
{
	return SetOrigin( in_point ).SetNormal( in_normal );
}

SICPPSDK_INLINE CPlane & CPlane::Set(const CVector3 &in_point, const CVector3 &in_U, const CVector3 &in_V)
{
	return SetOrigin( in_point ).SetTangents( in_U, in_V );
}

SICPPSDK_INLINE bool CPlane::EpsilonEquals(const CPlane& in_plane, double in_dEpsilon)const
{
	return (this == &in_plane ? true :
			(m_vOrigin.EpsilonEquals(in_plane.m_vOrigin, in_dEpsilon) &&
			 m_vNormal.EpsilonEquals(in_plane.m_vNormal, in_dEpsilon) &&
			 m_vTangentU.EpsilonEquals(in_plane.m_vTangentU, in_dEpsilon) &&
			 m_vTangentV.EpsilonEquals(in_plane.m_vTangentV, in_dEpsilon)));
}


SICPPSDK_INLINE bool CPlane::Equals(const CPlane& in_plane)const
{
	return (this == &in_plane ? true :
			(m_vOrigin.Equals(in_plane.m_vOrigin) &&
			 m_vNormal.Equals(in_plane.m_vNormal) &&
			 m_vTangentU.Equals(in_plane.m_vTangentU) &&
			 m_vTangentV.Equals(in_plane.m_vTangentV)));
}

SICPPSDK_INLINE bool CPlane::operator ==(const CPlane & in_plane )const
{
	return Equals(in_plane);
}

SICPPSDK_INLINE bool CPlane::operator !=(const CPlane & in_plane )const
{
	return !Equals(in_plane);
}

SICPPSDK_INLINE CVector3 CPlane::GetPosition(double in_u, double in_v)const
{
	CVector3 l_Tmp, l_Result( m_vOrigin );
	l_Result.AddInPlace( l_Tmp.Scale( in_u, m_vTangentU ) );
	l_Result.AddInPlace( l_Tmp.Scale( in_v, m_vTangentV ) );
	return l_Result;
}

SICPPSDK_INLINE CPlane & CPlane::SetOrigin(const CVector3 &in_point)
{
	m_vOrigin = in_point;
	return *this;
}

SICPPSDK_INLINE CVector3 CPlane::Project(const CVector3 &in_point)const
{
	double l_dU = 0.0, l_dV = 0.0;
	GetParameters( in_point, l_dU, l_dV );
	return GetPosition(l_dU, l_dV);
}

SICPPSDK_INLINE CVector3 CPlane::Reflect(const CVector3 &in_point)const
{
	return Project(in_point).ScaleInPlace(2.0).SubInPlace(in_point);
}

SICPPSDK_INLINE CLine CPlane::ProjectLine(const CLine &in_line)const
{
	CVector3 l_Origin  = Project( in_line.GetOrigin() );
	CVector3 l_Tangent = Project( in_line.GetPosition( 1.0 ) ).SubInPlace( l_Origin );
	return CLine( l_Origin, l_Tangent );
}

SICPPSDK_INLINE CLine CPlane::ReflectLine(const CLine &in_line)const
{
	CVector3 l_Origin  = Reflect( in_line.GetOrigin() );
	CVector3 l_Tangent = Reflect( in_line.GetPosition( 1.0 ) ).SubInPlace( l_Origin );
	return CLine( l_Origin, l_Tangent );
}

SICPPSDK_INLINE double CPlane::GetDistance(const CVector3 &in_point)const
{
	return Project(in_point).SubInPlace(in_point).GetLength();
}

SICPPSDK_INLINE CPlane& CPlane::MulByMatrix3(const CPlane& in_plane, const CMatrix3& in_matrix3)
{
	CVector3 l_NewOrigin, l_NewU, l_NewV;
	l_NewOrigin.MulByMatrix3(in_plane.m_vOrigin, in_matrix3);
	l_NewU.Add(in_plane.m_vOrigin, in_plane.m_vTangentU).MulByMatrix3InPlace(in_matrix3).SubInPlace(l_NewOrigin);
	l_NewV.Add(in_plane.m_vOrigin, in_plane.m_vTangentV).MulByMatrix3InPlace(in_matrix3).SubInPlace(l_NewOrigin);
	return Set(l_NewOrigin, l_NewU, l_NewV);
}

SICPPSDK_INLINE CPlane& CPlane::MulByMatrix4(const CPlane& in_plane, const CMatrix4& in_matrix4)
{
	CVector3 l_NewOrigin, l_NewU, l_NewV;
	l_NewOrigin.MulByMatrix4(in_plane.m_vOrigin, in_matrix4);
	l_NewU.Add(in_plane.m_vOrigin, in_plane.m_vTangentU).MulByMatrix4InPlace(in_matrix4).SubInPlace(l_NewOrigin);
	l_NewV.Add(in_plane.m_vOrigin, in_plane.m_vTangentV).MulByMatrix4InPlace(in_matrix4).SubInPlace(l_NewOrigin);
	return Set(l_NewOrigin, l_NewU, l_NewV);
}

SICPPSDK_INLINE CPlane& CPlane::MulByTransformation(const CPlane &in_plane, const CTransformation &in_transformation)
{
	CVector3 l_NewOrigin, l_NewU, l_NewV;
	l_NewOrigin.MulByTransformation(in_plane.m_vOrigin, in_transformation);
	l_NewU.Add(in_plane.m_vOrigin, in_plane.m_vTangentU).MulByTransformationInPlace(in_transformation).SubInPlace(l_NewOrigin);
	l_NewV.Add(in_plane.m_vOrigin, in_plane.m_vTangentV).MulByTransformationInPlace(in_transformation).SubInPlace(l_NewOrigin);
	return Set(l_NewOrigin, l_NewU, l_NewV);
}

SICPPSDK_INLINE CPlane& CPlane::MulByMatrix3InPlace(const CMatrix3& in_matrix3)
{
	return MulByMatrix3(*this, in_matrix3);
}

SICPPSDK_INLINE CPlane& CPlane::MulByMatrix4InPlace(const CMatrix4& in_matrix4)
{
	return MulByMatrix4(*this, in_matrix4);
}

SICPPSDK_INLINE CPlane& CPlane::MulByTransformationInPlace(const CTransformation& in_crTrans)
{
	return MulByTransformation(*this, in_crTrans);
}

SICPPSDK_INLINE CPlane& CPlane::operator *=(const CMatrix3& in_matrix3)
{
	return MulByMatrix3InPlace(in_matrix3);
}

SICPPSDK_INLINE CPlane& CPlane::operator *=(const CMatrix4& in_matrix4)
{
	return MulByMatrix4InPlace(in_matrix4);
}

SICPPSDK_INLINE CPlane& CPlane::operator *=(const CTransformation& in_transformation)
{
	return MulByTransformationInPlace(in_transformation);
}

};
};

#endif // __XSIPLANE_H__
