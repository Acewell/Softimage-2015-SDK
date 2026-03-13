//*****************************************************************************
/*!
   \file xsi_line.h
   \brief CLine class declaration.

	Copyright 2010 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSILINE_H__
#define __XSILINE_H__

#include "sicppsdk.h"
#include "xsi_status.h"
#include "xsi_vector3.h"
#include <math.h>

namespace XSI {

namespace MATH {

//*****************************************************************************
/*! \class CLine xsi_line.h
	\brief A parametric 3D line.

	\sa CVector3, CPlane

  	\eg
	\code
	\endcode
 */
//*****************************************************************************
class SICPPSDKDECL CLine
{
public:
	/*! Default constructor. */
	SICPPSDK_INLINE CLine();

	/*! Construct a line through given point in given direction.
	\param in_point Point on the line
	\param in_tangent Tangent direction vector
	*/
	SICPPSDK_INLINE CLine( const CVector3 &in_point, const CVector3 &in_tangent );

	/*! Copy constructor.
	\param in_line Line to copy
	*/
	SICPPSDK_INLINE CLine( const CLine &in_line );

	/*! Default destructor. */
	SICPPSDK_INLINE ~CLine();

	/*! Assignment operator.
	\param in_line Line to copy
	\return A reference to this line.
	*/
	SICPPSDK_INLINE CLine & operator=( const CLine & in_line );

	/*! Equality operator tests the strict equality of this CLine with the specified line.
	\param in_line Operand line.
	\return true if equal else false.
	\sa CLine::Equals
	*/
	SICPPSDK_INLINE bool operator ==(const CLine &in_line )const;

	/*! Inequality operator tests the strict inequality of this CLine with the specified line.
	\param in_line Operand line.
	\return true if equal else false.
	\sa CLine::Equals
	*/
	SICPPSDK_INLINE bool operator !=(const CLine &in_line )const;

	/*! Tests the equality of this line with the specified line, with a tolerance of Epsilon.
	\param in_line Operand line.
	\param in_dEpsilon Error margin \n
	\b Possible \b Values: [0, +INF[ should be a positive value
	\return true if equal else false.
	*/
	SICPPSDK_INLINE bool EpsilonEquals(const CLine &in_line, double in_dEpsilon)const;

	/*! Tests the strict equality of this line with the specified line.
	\param in_line Operand line.
	\return true if equal else false.
	*/
	SICPPSDK_INLINE bool Equals(const CLine &in_line)const;

	/*! Tests whether two lines are parallel.
	\param in_line Operand line.
	\return true if equal else false.
	*/
	bool Parallel(const CLine &in_line)const;

	/*! Tests whether two lines are collinear.
	\param in_line Operand line.
	\return true if equal else false.
	*/
	bool Collinear(const CLine &in_line)const;

	/*! Return projection of given point on this line.
	\return Closest point on the line
	*/
	SICPPSDK_INLINE CVector3 Project(const CVector3 &in_point)const;

	/*! Return closest point on the the line to the given line.
	\return Closest point on the line
	*/
	SICPPSDK_INLINE CVector3 GetClosestPoint(const CLine &in_line)const;

	/*! Return distance fromt the line to the given point.
	\return Distance to input point
	*/
	SICPPSDK_INLINE double GetDistance(const CVector3 &in_point)const;

	/*! Return distance fromt the line to the given line.
	\return Distance to input line
	*/
	SICPPSDK_INLINE double GetDistance(const CLine &in_line)const;

	/*! Return position on line for given parameter.
	\param in_param Parameter on line.
	\return Position corresponding to input parameter
	*/
	SICPPSDK_INLINE CVector3 GetPosition(double in_param)const;

	/*! Return parameter on line closest to input point.
	\return Position corresponding to input parameter
	*/
	double GetParameter(const CVector3 &in_point)const;

	/*! Return intersection of this line with the given line.
	\param in_line Line to intersect.
	\param out_point Closest point of intersection on line.
	\return true if lines intersect at a single point else false.
	*/
	bool Intersect(const CLine &in_line, CVector3 &out_point)const;

	/*! Return origin of the line.
	\return Reference to origin.
	*/
	SICPPSDK_INLINE const CVector3 &GetOrigin()const;

	/*! Return tangent direction of the line.
	\return Reference to tangent.
	*/
	SICPPSDK_INLINE const CVector3 &GetTangent()const;

	/*! Set origin of the line.
	\param in_point Point on the line
	\return A reference to this line.
	*/
	SICPPSDK_INLINE CLine &SetOrigin(const CVector3 &in_point);

	/*! Set tangent direction of the line.
	\param in_tangent Tangent direction vector.
	\return A reference to this line.
	*/
	SICPPSDK_INLINE CLine &SetTangent(const CVector3 &in_tangent);

	/*! Set origin and tangent direction of the line.
	\param in_point Point on the line
	\param in_tangent Tangent direction vector.
	\return A reference to this line.
	*/
	SICPPSDK_INLINE CLine &Set(const CVector3 &in_point, const CVector3 &in_tangent);

	/*! Right-multiplies this line by the matrix m in place (this = this . m ).
	\param in_matrix3 Operand matrix.
	\return A reference to this line.
	\sa CLine::MulByMatrix3InPlace
	*/
	SICPPSDK_INLINE CLine& operator *=(const CMatrix3& in_matrix3);

	/*! Right-multiplies this line by the matrix m in place (this = this . m ).
	\param in_matrix4 Operand matrix.
	\return A reference to this line.
	\sa CLine::MulByMatrix4InPlace
	*/
	SICPPSDK_INLINE CLine& operator *=(const CMatrix4& in_matrix4);

	/*! Right-multiplies this line by the transformation t in place (this = this . t).
	\param in_transformation transformation operand.
	\return A reference to this line.
	\sa CLine::MulByTransformationInPlace
	*/
	SICPPSDK_INLINE CLine& operator *=(const CTransformation& in_transformation);

	/*! Right-multiplies this line by the matrix m in place (this = this . m ).
	\param in_matrix3 Operand matrix.
	\return A reference to this line.
	*/
	SICPPSDK_INLINE CLine& MulByMatrix3InPlace(const CMatrix3& in_matrix3);

	/*! Right-multiplies the line l by the matrix m and store the result in this line (this = l . m ).
	\param in_line Operand line
	\param in_matrix3 Operand matrix.
	\return A reference to this line.
	*/
	SICPPSDK_INLINE CLine& MulByMatrix3(const CLine &in_line, const CMatrix3 &in_matrix3);

	/*! Right-multiplies this line by the matrix m in place (this = this . m ).
	\param in_matrix4 Operand matrix.
	\return A reference to this line.
	*/
	SICPPSDK_INLINE CLine& MulByMatrix4InPlace(const CMatrix4& in_matrix4);

	/*! Right-multiplies the line l by the matrix m and store the result in this line (this = l . m ).
	\param in_line Operand line
	\param in_matrix4 Operand matrix.
	\return A reference to this line.
	*/
	SICPPSDK_INLINE CLine& MulByMatrix4(const CLine &in_line, const CMatrix4 &in_matrix4);

	/*! Right-multiplies this line by the transformation t in place (this = this . t).
	\param in_transformation transformation operand.
	\return A reference to this line.
	*/
	SICPPSDK_INLINE CLine& MulByTransformationInPlace(const CTransformation &in_transformation);

	/*! Right-multiplies the line l by the transformation t and stores the result in this line (this = l . t ).
	\param in_line Operand line.
	\param in_transformation transformation operand.
	\return A reference to this line.
	*/
	SICPPSDK_INLINE CLine& MulByTransformation(const CLine &in_line, const CTransformation &in_transformation);

private:
	CVector3	m_vOrigin;
	CVector3	m_vTangent;
};

//inline functions
SICPPSDK_INLINE CLine::CLine()
: m_vOrigin(0.0, 0.0, 0.0), m_vTangent(1.0, 0.0, 0.0)
{
}

SICPPSDK_INLINE CLine::CLine( const CLine& in_line )
: m_vOrigin(in_line.m_vOrigin), m_vTangent(in_line.m_vTangent)
{
}

SICPPSDK_INLINE CLine::CLine( const CVector3 &in_pt, const CVector3 &in_dir )
: m_vOrigin(in_pt), m_vTangent(in_dir)
{}

SICPPSDK_INLINE CLine::~CLine()
{}

SICPPSDK_INLINE CLine& CLine::operator=( const CLine & in_line )
{
	m_vOrigin = in_line.m_vOrigin;
	m_vTangent = in_line.m_vTangent;
	return *this;
}

SICPPSDK_INLINE const CVector3 &CLine::GetOrigin()const
{
	return m_vOrigin;
}

SICPPSDK_INLINE const CVector3 &CLine::GetTangent()const
{
	return m_vTangent;
}

SICPPSDK_INLINE bool CLine::EpsilonEquals(const CLine& in_line, double in_dEpsilon)const
{
	return (this == &in_line ? true :
			(m_vOrigin.EpsilonEquals(in_line.m_vOrigin, in_dEpsilon) &&
			 m_vTangent.EpsilonEquals(in_line.m_vTangent, in_dEpsilon)));
}


SICPPSDK_INLINE bool CLine::Equals(const CLine& in_line)const
{
	return (this == &in_line ? true :
			(m_vOrigin.Equals(in_line.m_vOrigin) &&
			 m_vTangent.Equals(in_line.m_vTangent)));
}

SICPPSDK_INLINE bool CLine::operator ==(const CLine & in_line )const
{
	return Equals(in_line);
}

SICPPSDK_INLINE bool CLine::operator !=(const CLine & in_line )const
{
	return !Equals(in_line);
}

SICPPSDK_INLINE CVector3 CLine::GetPosition(double in_param)const
{
	CVector3 l_Result;
	l_Result.ScaleAdd( in_param, m_vTangent, m_vOrigin );
	return l_Result;
}

SICPPSDK_INLINE CLine & CLine::SetOrigin(const CVector3 &in_point)
{
	m_vOrigin = in_point;
	return *this;
}

SICPPSDK_INLINE CLine &CLine::SetTangent(const CVector3 &in_tangent)
{
	m_vTangent = in_tangent;
	return *this;
}

SICPPSDK_INLINE CLine & CLine::Set(const CVector3 &in_point, const CVector3 &in_tangent)
{
	m_vOrigin = in_point;
	m_vTangent = in_tangent;
	return *this;
}

SICPPSDK_INLINE CVector3 CLine::Project(const CVector3 &in_point)const
{
	return GetPosition(GetParameter(in_point));
}

SICPPSDK_INLINE CVector3 CLine::GetClosestPoint(const CLine &in_line)const
{
	CVector3 l_Closest;
	Intersect( in_line, l_Closest );
	return l_Closest;
}

SICPPSDK_INLINE double CLine::GetDistance(const CVector3 &in_point)const
{
	return Project(in_point).SubInPlace(in_point).GetLength();
}

SICPPSDK_INLINE double CLine::GetDistance(const CLine &in_line)const
{
	CVector3 l_Tmp;
	return ( Intersect( in_line, l_Tmp ) ? 0.0 : GetDistance( in_line.m_vOrigin ) );
}

SICPPSDK_INLINE CLine& CLine::MulByMatrix3(const CLine& in_line, const CMatrix3& in_matrix3)
{
	CVector3 l_NewOrigin, l_NewTangent;
	l_NewOrigin.MulByMatrix3(in_line.m_vOrigin, in_matrix3);
	l_NewTangent.Add(in_line.m_vOrigin, in_line.m_vTangent);
	l_NewTangent.MulByMatrix3InPlace(in_matrix3);
	l_NewTangent.SubInPlace(l_NewOrigin);
	return Set(l_NewOrigin, l_NewTangent);
}

SICPPSDK_INLINE CLine& CLine::MulByMatrix4(const CLine& in_line, const CMatrix4& in_matrix4)
{
	CVector3 l_NewOrigin, l_NewTangent;
	l_NewOrigin.MulByMatrix4(in_line.m_vOrigin, in_matrix4);
	l_NewTangent.Add(in_line.m_vOrigin, in_line.m_vTangent);
	l_NewTangent.MulByMatrix4InPlace(in_matrix4);
	l_NewTangent.SubInPlace(l_NewOrigin);
	return Set(l_NewOrigin, l_NewTangent);
}

SICPPSDK_INLINE CLine& CLine::MulByTransformation(const CLine &in_line, const CTransformation &in_transformation)
{
	CVector3 l_NewOrigin, l_NewTangent;
	l_NewOrigin.MulByTransformation(in_line.m_vOrigin, in_transformation);
	l_NewTangent.Add(in_line.m_vOrigin, in_line.m_vTangent);
	l_NewTangent.MulByTransformationInPlace(in_transformation);
	l_NewTangent.SubInPlace(l_NewOrigin);
	return Set(l_NewOrigin, l_NewTangent);
}

SICPPSDK_INLINE CLine& CLine::MulByMatrix3InPlace(const CMatrix3& in_matrix3)
{
	return MulByMatrix3(*this, in_matrix3);
}

SICPPSDK_INLINE CLine& CLine::MulByMatrix4InPlace(const CMatrix4& in_matrix4)
{
	return MulByMatrix4(*this, in_matrix4);
}

SICPPSDK_INLINE CLine& CLine::MulByTransformationInPlace(const CTransformation& in_crTrans)
{
	return MulByTransformation(*this, in_crTrans);
}

SICPPSDK_INLINE CLine& CLine::operator *=(const CMatrix3& in_matrix3)
{
	return MulByMatrix3InPlace(in_matrix3);
}

SICPPSDK_INLINE CLine& CLine::operator *=(const CMatrix4& in_matrix4)
{
	return MulByMatrix4InPlace(in_matrix4);
}

SICPPSDK_INLINE CLine& CLine::operator *=(const CTransformation& in_transformation)
{
	return MulByTransformationInPlace(in_transformation);
}

};
};

#endif // __XSILINE_H__
