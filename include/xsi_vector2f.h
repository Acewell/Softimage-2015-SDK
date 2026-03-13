//*****************************************************************************
/*!
   \file xsi_vector2f.h
   \brief CVector2f class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIVECTOR2F_H__
#define __XSIVECTOR2F_H__

#include "sicppsdk.h"
#include <math.h>

namespace XSI {

namespace MATH {

//*****************************************************************************
/*! \class CVector2f xsi_vector2f.h
	\brief A 2-element vector represented by single floating point x,y coordinates. This class is typically used for
	implementing custom ICE nodes.

	\sa CVector3f, CVector4f
 */
//*****************************************************************************
class CVector2f
{
public:
	/*! Default constructor. */
	SICPPSDK_INLINE CVector2f();

	/*! Constructor.
	\param in_X Value of the x component
	\param in_Y Value of the y component
	*/
	SICPPSDK_INLINE CVector2f(float in_X, float in_Y );

	/*! Copy constructor.
	\param in_vector2 constant class object.
	*/
	SICPPSDK_INLINE CVector2f( const CVector2f& in_vector2);

	/*! Default destructor. */
	~CVector2f() {}

	/*! Assignment operator.
	\param in_vector2 constant class object.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector2f & operator=( const CVector2f & in_vector2 );

	/*! Equality operator tests the strict equality of this CVector2f with the specified vector2.
	\param in_vector2 Operand vector.
	\return true if equal else false.
	\sa CVector2f::Equals
	*/
	SICPPSDK_INLINE bool operator ==(const CVector2f & in_vector2 )const;

	/*! Inequality operator tests the strict inequality of this CVector2f with the specified vector2.
	\param in_vector2 Operand vector.
	\return true if equal else false.
	\sa CVector2f::Equals
	*/
	SICPPSDK_INLINE bool operator !=(const CVector2f & in_vector2 )const;

	/*! Less than operator. Performs a comparison with a specified CVector2f to determine if this CVector2f is
	less than the specified CVector2f. The comparison is arbitrary and not geometrically meaningful, it's only purpose is
	to make CVector2f compliant with stl for sorting operations.
	\param in_vector2 CVector2f to compare.
	\return true if this CVector2f is less than the specified CVector2f, false otherwise.
	\since 7.5
	*/
	SICPPSDK_INLINE bool operator < ( const CVector2f & in_vector2 ) const;

	/*! Negates this vector (this = - this).
	\return A reference to this vector.
	\sa CVector2f::NegateInPlace
	*/
	SICPPSDK_INLINE CVector2f& operator ~();

	/*! Adds the input vector to this one (this = this + in_vector2)
	\param in_vector2 Operand vector..
	\return A reference to this vector.
	\sa CVector2f::AddInPlace
	*/
	SICPPSDK_INLINE CVector2f& operator +=(const CVector2f& in_vector2);

	/*! Subtracts the input vector (in_vector2) from this one (this = this - in_vector2).
	\param in_vector2 Operand vector.
	\return A reference to this vector.
	\sa CVector2f::SubInPlace
	*/
	SICPPSDK_INLINE CVector2f& operator -=(const CVector2f & in_vector2);

	/*! Scales this vector by the input scalar (alpha) (this = alpha * this).
	\param in_dAlpha  Scalar multiplicator.
	\return A reference to this vector.
	\sa CVector2f::ScaleInPlace
	*/
	SICPPSDK_INLINE CVector2f& operator *=(const float& in_dAlpha);

	/*! Sets this vector to a null vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector2f& SetNull();

	/*! Returns the length of this vector.
	\return Length of this vector.
	*/
	SICPPSDK_INLINE float GetLength()const;

	/*! Returns the squared length of this vector.
	\return Squared length of this vector.
	*/
	SICPPSDK_INLINE float GetLengthSquared()const;

	/*! Tests the strict equality of this vector2 with the specified vector2.
	\param in_vector2 Operand vector.
	\return true if equal else false.
	*/
	SICPPSDK_INLINE bool Equals(const CVector2f& in_vector2)const;

	/*! Tests the equality of this vector with in_vector, with a tolerance of Epsilon.
	\param in_vector Operand vector.
	\param in_fEpsilon Error margin \n
	\b Possible \b Values: [0, +INF[ should be a positive value
	\return true if equal else false.
	*/
	SICPPSDK_INLINE bool EpsilonEquals
	(
		const CVector2f& in_vector,
		const float in_fEpsilon
	)const;

	/*! Sets the value of this vector to the scalar multiplication of itself by s and then adds
	vector2 v. (this = s*this + v)
	\param in_dS  Scalar multiplicator.
	\param in_vector2 Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector2f& ScaleAddInPlace(float in_dS,const CVector2f& in_vector2);

	/*! Sets the value of this vector2 to the scalar multiplication of vector2 A by s and then
	adds vector2 B. (this = s*v1 + v2).
	\param in_dS  Scalar multiplicator.
	\param in_vector3A Operand vector.
	\param in_vector3B Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector2f& ScaleAdd
	(
		float				in_dS,
		const CVector2f&	in_vector3A,
		const CVector2f&	in_vector3B
	);

	/*! Scales this vector by the input scalar (alpha) (this = alpha * this).
	\param in_dAlpha  Scalar multiplicator.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector2f& ScaleInPlace(float in_dAlpha);

	/*! Scales the input vector (v) by (alpha) store the result into this one (this = alpha * v).
	\param in_Alpha  Scalar multiplicator.
	\param in_vector2 Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector2f& Scale(float in_Alpha, const CVector2f& in_vector2);

	/*! Negates this vector (this = - this).
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector2f& NegateInPlace();

	/*! Negates the input vector (v) store the result into this one (this = - v).
	\param in_vector2 Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector2f& Negate(const CVector2f& in_vector2);

	/*! Subtracts the input vector2 (v) from this one (this = this - v).
	\param in_vector2 Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector2f& SubInPlace(const CVector2f& in_vector2);

	/*! Subtracts the input vector2 (\c in_vector3B) from the input vector2 (\c in_vector3A) and stores
	the result in this one (<tt>this = A - B</tt>).
	\param in_vector3A Operand vector.
	\param in_vector3B Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector2f& Sub(const CVector2f& in_vector3A, const CVector2f& in_vector3B);

	/*! Adds the input vector to this one (this = this + in_vector2).
	\param in_vector2 Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector2f& AddInPlace(const CVector2f& in_vector2);

	/*! Adds both input vectors and stores the result in this one. (this = A + B)
	\param in_vector3A Operand vector.
	\param in_vector3B Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector2f& Add(const CVector2f& in_vector3A, const CVector2f& in_vector3B);

	/*! Returns the Y value of this vector.
	\return Y value of this vector.
	*/
	SICPPSDK_INLINE float GetY()const;

	/*! Sets the Y value of this vector.
	\param in_X y value.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector2f& PutY(float in_X);

	/*! Returns the X value of this vector.
	\return X value of this vector.
	*/
	SICPPSDK_INLINE float GetX()const;

	/*! Sets the X value of this vector.
	\param in_X x value.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector2f& PutX(float in_X);

private:
	float m_X,m_Y;
};

//inline functions
SICPPSDK_INLINE CVector2f::CVector2f()
{
	m_X = 0;
	m_Y = 0;
}

SICPPSDK_INLINE CVector2f::CVector2f( const CVector2f& in_vct )
{
	*this = in_vct;
}

SICPPSDK_INLINE CVector2f::CVector2f(float in_X, float in_Y):m_X(in_X),m_Y(in_Y){}


SICPPSDK_INLINE CVector2f& CVector2f::operator=( const CVector2f & in_vct )
{
	m_X = in_vct.m_X;
	m_Y = in_vct.m_Y;
	return (*this);
}

SICPPSDK_INLINE bool CVector2f::operator ==(const CVector2f & in_vector2 )const
{
	return Equals(in_vector2);
}

SICPPSDK_INLINE bool CVector2f::operator !=(const CVector2f & in_vector2 )const
{
	return ! Equals(in_vector2);
}

SICPPSDK_INLINE bool CVector2f::operator < ( const CVector2f& in_vector2 ) const
{
	if ( m_X != in_vector2.m_X ) return m_X < in_vector2.m_X;
	if ( m_Y != in_vector2.m_Y ) return m_Y < in_vector2.m_Y;
	return false;
}

SICPPSDK_INLINE CVector2f& CVector2f::operator ~()
{
	return NegateInPlace();
}

SICPPSDK_INLINE CVector2f& CVector2f::operator +=(const CVector2f& in_vector2)
{
	return AddInPlace(in_vector2);
}

SICPPSDK_INLINE CVector2f& CVector2f::operator -=(const CVector2f& in_vector2)
{
	return SubInPlace(in_vector2);
}

SICPPSDK_INLINE CVector2f& CVector2f::operator *=(const float& in_dAlpha)
{
	return ScaleInPlace(in_dAlpha);
}

SICPPSDK_INLINE CVector2f& CVector2f::SetNull()
{
	m_X = m_Y = 0.0;
	return (*this);
}

SICPPSDK_INLINE float CVector2f::GetLength()const
{
	return sqrt( GetLengthSquared() );
}

SICPPSDK_INLINE float CVector2f::GetLengthSquared()const
{
	return(m_X*m_X + m_Y*m_Y );
}

SICPPSDK_INLINE bool CVector2f::Equals(const CVector2f& in_vec)const
{
	return (this == &in_vec) ? true : ( ( m_X == in_vec.GetX() ) && ( m_Y == in_vec.GetY() ) );
}

SICPPSDK_INLINE bool CVector2f::EpsilonEquals
(
	const CVector2f& in_cVec2,
	const float in_fEpsilon
)const
{
	return (this == &in_cVec2) ? true :
		(	fabs( m_X - in_cVec2.GetX() ) < ::fabs(in_fEpsilon) &&
			fabs( m_Y - in_cVec2.GetY() ) < ::fabs(in_fEpsilon)	);
}

SICPPSDK_INLINE CVector2f& CVector2f::ScaleAddInPlace
(
	float in_ScalingFactor,
	const CVector2f& in_vec
)
{
	ScaleInPlace(in_ScalingFactor);
	return AddInPlace(in_vec);
}

SICPPSDK_INLINE CVector2f& CVector2f::ScaleAdd
(
	const float in_ScalingFactor,
	const CVector2f& in_vec3A,
	const CVector2f& in_vec3B
)
{
	Scale(in_ScalingFactor, in_vec3A);
	return AddInPlace(in_vec3B);
}

SICPPSDK_INLINE CVector2f& CVector2f::ScaleInPlace(float in_dScalingFactor)
{
	m_X *= in_dScalingFactor;
	m_Y *= in_dScalingFactor;
	return (*this);
}

SICPPSDK_INLINE CVector2f& CVector2f::Scale
(
	float in_dScalingFactor,
	const CVector2f& in_vec
)
{
	m_X = in_vec.GetX() * in_dScalingFactor;
	m_Y = in_vec.GetY() * in_dScalingFactor;
	return (*this);
}

SICPPSDK_INLINE CVector2f& CVector2f::NegateInPlace()
{
	m_X = -m_X;
	m_Y = -m_Y;
	return (*this);
}

SICPPSDK_INLINE CVector2f& CVector2f::Negate(const CVector2f& in_vec )
{
	m_X = -in_vec.GetX();
	m_Y = -in_vec.GetY();
	return (*this);
}

SICPPSDK_INLINE CVector2f& CVector2f::SubInPlace(const CVector2f& in_vec)
{
	m_X -= in_vec.GetX();
	m_Y -= in_vec.GetY();
	return (*this);
}

SICPPSDK_INLINE CVector2f& CVector2f::Sub
(
	const CVector2f& in_vec3A,
	const CVector2f& in_vec3B
)
{
	m_X = in_vec3A.GetX() - in_vec3B.GetX();
	m_Y = in_vec3A.GetY() - in_vec3B.GetY();
	return (*this);
}

SICPPSDK_INLINE CVector2f& CVector2f::AddInPlace(const CVector2f& in_vec)
{
	m_X += in_vec.GetX();
	m_Y += in_vec.GetY();
	return (*this);
}

SICPPSDK_INLINE CVector2f& CVector2f::Add
(
	const CVector2f& in_vec3A,
	const CVector2f& in_vec3B
)
{
	m_X = in_vec3A.GetX() + in_vec3B.GetX();
	m_Y = in_vec3A.GetY() + in_vec3B.GetY();
	return (*this);
}

SICPPSDK_INLINE float CVector2f::GetY()const
{
	return m_Y;
}

SICPPSDK_INLINE CVector2f& CVector2f::PutY(float in_Y)
{
	m_Y = in_Y;
	return (*this);
}

SICPPSDK_INLINE float CVector2f::GetX()const
{
	return m_X;
}

SICPPSDK_INLINE CVector2f& CVector2f::PutX(float in_X)
{
	m_X = in_X;
	return (*this);
}

};
};

#endif // __XSIVECTOR2F_H__
