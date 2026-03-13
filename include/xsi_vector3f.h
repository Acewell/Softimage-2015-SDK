//*****************************************************************************
/*!
   \file xsi_vector3f.h
   \brief CVector3f class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIVECTOR3F_H__
#define __XSIVECTOR3F_H__

#include "sicppsdk.h"
#include <xsi_math.h>
#include <xsi_matrix3f.h>
#include <xsi_matrix4f.h>

namespace XSI {

namespace MATH {

//*****************************************************************************
/*! \class CVector3f xsi_vector3f.h
	\brief A 3-element vector that is represented by single floating point x,y,z coordinates. The class is used
	used for implementing custom ICE nodes.

	\sa CVector2f, CVector4f, CMatrix3f, CMatrix4f, CQuaternionf, CRotationf, CColor4f,
 */
//*****************************************************************************
class CVector3f
{
public:
	/*! Default constructor. */
	SICPPSDK_INLINE CVector3f();

	/*! Constructor.
	\param in_fX Value of the x component
	\param in_fY Value of the y component
	\param in_fZ Value of the z component
	*/
	SICPPSDK_INLINE CVector3f(float in_fX, float in_fY, float in_fZ);

	/*! Copy constructor.
	\param in_vector3 constant class object.
	*/
	SICPPSDK_INLINE CVector3f( const CVector3f& in_vector3);

	/*! Default destructor. */
	SICPPSDK_INLINE ~CVector3f();

	/*! Assignment operator.
	\param in_vector3 constant class object.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3f & operator=( const CVector3f & in_vector3 );

	/*! Equality operator tests the strict equality of this CVector3f with the specified vector3.
	\param in_vector3 Operand vector.
	\return true if equal else false.
	\sa CVector3f::Equals
	*/
	SICPPSDK_INLINE bool operator ==(const CVector3f & in_vector3 )const;

	/*! Inequality operator tests the strict inequality of this CVector3f with the specified vector3.
	\param in_vector3 Operand vector.
	\return true if equal else false.
	\sa CVector3f::Equals
	*/
	SICPPSDK_INLINE bool operator !=(const CVector3f & in_vector3 )const;

	/*! Negates this vector (this = - this).
	\return A reference to this vector.
	\sa CVector3f::NegateInPlace
	*/
	SICPPSDK_INLINE CVector3f& operator ~();

	/*! Adds the input vector to this one (this = this + in_vector3)
	\param in_vector3 Operand vector..
	\return A reference to this vector.
	\sa CVector3f::AddInPlace
	*/
	SICPPSDK_INLINE CVector3f& operator +=(const CVector3f& in_vector3);

	/*! Subtracts the input vector (in_vector3) from this one (this = this - in_vector3).
	\param in_vector3 Operand vector.
	\return A reference to this vector.
	\sa CVector3f::SubInPlace
	*/
	SICPPSDK_INLINE CVector3f& operator -=(const CVector3f & in_vector3);

	/*! Right-multiplies this vector by the matrix m in place (this = this * m ).
	\param in_matrix3 Operand matrix.
	\return A reference to this vector.
	\sa CVector3f::MulByMatrix3InPlace
	*/
	SICPPSDK_INLINE CVector3f& operator *=(const CMatrix3f& in_matrix3);

	/*! Right-multiplies this vector by the matrix m in place (this = this * m ).
	\param in_matrix4 Operand matrix.
	\return A reference to this vector.
	\sa CVector3f::MulByMatrix4InPlace
	*/
	SICPPSDK_INLINE CVector3f& operator *=(const CMatrix4f& in_matrix4);

	/*! Scales this vector by the input scalar (alpha) (this = alpha * this).
	\param in_fAlpha  Scalar multiplicator.
	\return A reference to this vector.
	\sa CVector3f::ScaleInPlace
	*/
	SICPPSDK_INLINE CVector3f& operator *=(const float in_fAlpha);

	/*! Read-only accessors to the X,Y,Z components.
	\param in_sIndex  0,1,2 for X,Y and Z values.
	\return The value of the specified component. If the index supplied is out of range the function returns FLT_MAX.
	\sa CVector3f::GetX(), CVector3f::GetY(), CVector3f::GetZ()
	*/
	SICPPSDK_INLINE float operator[](const short& in_sIndex) const;

	/*! Accessor to the X,Y,Z components.
	\param in_sIndex  0,1,2 for X,Y and Z values.
	\return The value of the specified component. If the index supplied is out of range the function returns FLT_MAX.
	\sa CVector3f::GetX(), CVector3f::GetY(), CVector3f::GetZ()
	*/
	SICPPSDK_INLINE float& operator[](const short& in_sIndex);

	/*! Less than operator. Performs a comparison with a specified CVector3f to determine if this CVector3f is
	less than the specified CVector3f. The comparison is arbitrary and not geometrically meaningful, it's only purpose is
	to make CVector3f compliant with stl for sorting operations.
	\param in_vector3 CVector3f to compare.
	\return true if this CVector3f is less than the specified CVector3f, false otherwise.
	\since 7.5
	*/
	SICPPSDK_INLINE bool operator < ( const CVector3f & in_vector3 ) const;

	/*! Right-multiplies this vector by the matrix m in place (this = this * m ).
	\param in_matrix3 Operand matrix.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3f& MulByMatrix3InPlace(const CMatrix3f& in_matrix3);

	/*! Right-multiplies the vector v by the matrix m and store the result in this vector (this = v * m ).
	\param in_vector3 Operand vector
	\param in_matrix3 Operand matrix.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3f& MulByMatrix3( const CVector3f& in_vector3, const CMatrix3f& in_matrix3 );

	/*! Right-multiplies this vector by the matrix m in place (this = this * m ).
	\param in_matrix4 Operand matrix.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3f& MulByMatrix4InPlace(const CMatrix4f& in_matrix4);

	/*! Right-multiplies the vector v by the matrix m and store the result in this vector (this = v * m ).
	\param in_vector3 Operand vector
	\param in_matrix4 Operand matrix.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3f& MulByMatrix4( const CVector3f& in_vector3, const CMatrix4f& in_matrix4 );

	/*! Sets this vector to a null vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3f& SetNull();

	/*! Returns true if the vector is a null vector
	\param in_fEpsilon Tolerance value
	\return Bool value.
	*/
	SICPPSDK_INLINE bool IsNull(const float in_fEpsilon = MicroEPS);

	/*! Returns the index of the maximum component of this vector.
	\return Index of the maximum component of this vector.
	*/
	SICPPSDK_INLINE short GetMaxComponentIndex()const;

	/*! Returns the maximum component value of this vector.
	\return Maximum component value of this vector.
	*/
	SICPPSDK_INLINE float GetMaxComponent()const;

	/*! Returns the index of the minimum component of this vector.
	\return Index of the minimum component of this vector.
	*/
	SICPPSDK_INLINE short GetMinComponentIndex()const;

	/*! Returns the minimum component value of this vector.
	\return Minimum component value of this vector.
	*/
	SICPPSDK_INLINE float GetMinComponent()const;

	/*! Returns the length of this vector.
	\return Length of this vector.
	*/
	SICPPSDK_INLINE float GetLength()const;

	/*! Scales the vector to set its length.
	\param in_val Length to set
	*/
	SICPPSDK_INLINE void SetLength( const float in_val );

	/*! Returns the squared length of this vector.
	\return Squared length of this vector.
	*/
	SICPPSDK_INLINE float GetLengthSquared()const;

	/*! Normalizes this vector in place.
	\return CStatus::OK if the normalization has been computed,
	*/
	SICPPSDK_INLINE CStatus NormalizeInPlace();

	/*! Sets the value of this vector to the normalization of input vector.
	\param in_vector3 vector operand.
	\return CStatus::OK if the normalization has been computed.
	*/
	SICPPSDK_INLINE CStatus Normalize(const CVector3f& in_vector3);

	/*! Returns the dot product of this vector and the input vector.
	\param in_vector3 vector operand.
	\return Dot product of this vector and vector in_vector3.
	*/
	SICPPSDK_INLINE float Dot(const CVector3f& in_vector3)const;

	/*! Sets this vector to the vector cross product of vectors A and B.
	\param in_vector3A vector operand.
	\param in_vector3B vector operand.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3f& Cross(const CVector3f& in_vector3A, const CVector3f& in_vector3B);

	/*! Returns the angle (in radians) between this vector and the input vector.
	\param in_vector3 vector operand.
	\return Angle (in radians) between this vector and the input vector.
	*/
	SICPPSDK_INLINE float GetAngle(const CVector3f& in_vector3 )const;

	/*! Linearly interpolates between vectors A and B and places the result into this vector:
	this = (1-alpha)*A + alpha*B.
	\param in_vector3A vector operand.
	\param in_vector3B vector operand.
	\param in_fAlpha Scalar interpolator \n
	\b Possible \b Values: [0.0, 1.0] Domain of validity
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3f& LinearlyInterpolate
	(
		const CVector3f& in_vector3A,
		const CVector3f& in_vector3B,
		const float in_fAlpha
	);

	/*! Sets each component of this CVector3 to its absolute value.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3f& AbsoluteInPlace();

	/*! Sets each component of the specified vector to its absolute value and places the
	modified values into this vector.
	\param in_vector3 Vector to make absolute
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3f& Absolute(const CVector3f& in_vector3);

	/*! Clamps this vector's components to the range [MinValue, MaxValue].
	\param in_fMinValue Lower bound of the clamping domain.
	\param in_fMaxValue Higher bound of the clamping domain.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3f& ClampInPlace(const float in_fMinValue, const float in_fMaxValue);

	/*! Clamps the specified vector's components to the range [MinValue, MaxValue] and places the
	values into this vector3.
	\param in_fMinValue Lower bound of the clamping domain.
	\param in_fMaxValue Higher bound of the clamping domain.
	\param in_vector3 Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3f& Clamp
	(
		const float			in_fMinValue,
		const float			in_fMaxValue,
		const CVector3f&	in_vector3
	);

	/*! Tests the equality of this vector with the specified vector3, with a tolerance of Epsilon.
	\param in_vector3 Operand vector.
	\param in_fEpsilon Error margin (validity domain: <TT>[0, +INF[</TT>)
	\return true if equal else false.
	*/
	SICPPSDK_INLINE bool EpsilonEquals
	(
		const CVector3f& in_vector3,
		const float in_fEpsilon
	)const;

	/*! Tests the strict equality of this vector with the specified vector3.
	\param in_vector3 Operand vector.
	\return true if equal else false.
	*/
	SICPPSDK_INLINE bool Equals(const CVector3f& in_vector3)const;

	/*! Sets the value of this vector to the scalar multiplication of itself by s and then adds
	vector3 v. (<TT>this = s*this + v</TT>)
	\param in_fS  Scalar multiplicator.
	\param in_vector3 Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3f& ScaleAddInPlace(const float in_fS,const CVector3f& in_vector3);

	/*! Sets the value of this vector to the scalar multiplication of vector3 A by s and then
	adds vector3 B. (<TT>this = s*v1 + v2</TT>).
	\param in_fS  Scalar multiplicator.
	\param in_vector3A Operand vector.
	\param in_vector3B Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3f& ScaleAdd
	(
		const float				in_fS,
		const CVector3f&		in_vector3A,
		const CVector3f&		in_vector3B
	);

	/*! Scales this vector by the input scalar (alpha) (this = alpha * this).
	\param in_fAlpha  Scalar multiplicator.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3f& ScaleInPlace(const float in_fAlpha);

	/*! Scales the input vector (v) by (alpha) store the result into this one (this = alpha * v).
	\param in_fAlpha Scalar multiplicator.
	\param in_vector3 Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3f& Scale(const float in_fAlpha, const CVector3f& in_vector3);

	/*! Negates this vector (this = - this).
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3f& NegateInPlace();

	/*! Negates the input vector (v) store the result into this one (this = - v).
	\param in_vector3 Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3f& Negate(const CVector3f& in_vector3);

	/*! Subtracts the input vector3 (v) from this one (this = this - v).
	\param in_vector3 Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3f& SubInPlace(const CVector3f&in_vector3);

	/*! Subtracts the input vector3 (\c in_vector3B) from the input vector3 (\c in_vector3A) and
	stores the result into this one (<tt>this = A - B</tt>).
	\param in_vector3A Operand vector.
	\param in_vector3B Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3f& Sub(const CVector3f& in_vector3A, const CVector3f& in_vector3B);

	/*! Adds the input vector to this one (this = this + in_vector3).
	\param in_vector3 Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3f& AddInPlace(const CVector3f& in_vector3);

	/*! Adds both input vectors and stores the result in this one. (this = A + B)
	\param in_vector3A Operand vector.
	\param in_vector3B Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3f& Add(const CVector3f& in_vector3A,const CVector3f& in_vector3B);

	/*! Accessor to the X,Y,Z components.
	\param in_sIndex  0,1,2 for X,Y and Z values.
	\return The value of the specified component. If the index supplied is out of range the function returns FLT_MAX.
	\sa CVector3f::GetX(), CVector3f::GetY(), CVector3f::GetZ()
	*/
	SICPPSDK_INLINE float Get(const short& in_sIndex)const;

	/*! Accessor to the X,Y,Z components.
	\param in_sIndex  0,1,2 for X,Y and Z values.
	\param in_val The value of the specified component.
	\sa CVector3f::Get(), CVector3f::GetY(), CVector3f::GetZ()
	*/
	SICPPSDK_INLINE void Set(const short& in_sIndex, const float in_val );

	/*! Returns the X, Y and Z values of the vector.
	\param io_fX X value to get in the vector.
	\param io_fY Y value to get in the vector.
	\param io_fZ Z value to get in the vector.
	*/
	SICPPSDK_INLINE void Get(float& io_fX, float& io_fY, float& io_fZ)const;

	/*! Sets the X, Y and Z values of the vector.
	\param in_fX X value to set in the vector.
	\param in_fY Y value to set in the vector.
	\param in_fZ Z value to set in the vector.
	\return A reference to the vector.
	*/
	SICPPSDK_INLINE CVector3f& Set(const float in_fX, const float in_fY, const float in_fZ);

	/*! Returns the Z value of this vector.
	\return Z value of this vector.
	*/
	SICPPSDK_INLINE float GetZ()const;

	/*! Sets the Z value of this vector.
	\param in_fZ z value.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3f& PutZ(const float in_fZ);

	/*! Returns the Y value of this vector.
	\return Y value of this vector.
	*/
	SICPPSDK_INLINE float GetY()const;

	/*! Sets the Y value of this vector.
	\param in_fY y value.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3f& PutY(const float in_fY);

	/*! Returns the X value of this vector.
	\return X value of this vector.
	*/
	SICPPSDK_INLINE float GetX()const;

	/*! Sets the X value of this vector.
	\param in_fX x value.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3f& PutX(const float in_fX);

private:
	float m_fX,m_fY,m_fZ;
};

//inline functions
SICPPSDK_INLINE CVector3f::CVector3f()
{
	m_fX = 0;
	m_fY = 0;
	m_fZ = 0;
}

SICPPSDK_INLINE CVector3f::CVector3f( const CVector3f& in_vct )
{
	in_vct.Get(m_fX,m_fY,m_fZ);
}

SICPPSDK_INLINE CVector3f::CVector3f
(
 float in_fX, float in_fY, float in_fZ
):m_fX(in_fX),m_fY(in_fY),m_fZ(in_fZ)
{}

SICPPSDK_INLINE CVector3f::~CVector3f()
{}

SICPPSDK_INLINE CVector3f& CVector3f::operator=( const CVector3f & in_vct )
{
	in_vct.Get(m_fX,m_fY,m_fZ);
	return (*this);
}

SICPPSDK_INLINE bool CVector3f::operator ==(const CVector3f & in_vector3 )const
{
	return Equals(in_vector3);
}

SICPPSDK_INLINE bool CVector3f::operator !=(const CVector3f & in_vector3 )const
{
	return ! Equals(in_vector3);
}

SICPPSDK_INLINE CVector3f& CVector3f::operator ~()
{
	return NegateInPlace();
}

SICPPSDK_INLINE CVector3f& CVector3f::operator +=(const CVector3f& in_vector3)
{
	return AddInPlace(in_vector3);
}

SICPPSDK_INLINE CVector3f& CVector3f::operator -=(const CVector3f& in_vector3)
{
	return SubInPlace(in_vector3);
}

SICPPSDK_INLINE CVector3f& CVector3f::operator *=(const CMatrix3f& in_matrix3)
{
	return MulByMatrix3InPlace(in_matrix3);
}

SICPPSDK_INLINE CVector3f& CVector3f::operator *=(const CMatrix4f& in_matrix4)
{
	return MulByMatrix4InPlace(in_matrix4);
}

SICPPSDK_INLINE CVector3f& CVector3f::operator *=(const float in_fAlpha)
{
	return ScaleInPlace(in_fAlpha);
}

SICPPSDK_INLINE float CVector3f::operator[](const short& in_sIndex) const
{
	assert(in_sIndex >= 0 && in_sIndex < 3);
	switch(in_sIndex)
	{
		case 0:
			return m_fX;
			break;
		case 1:
			return m_fY;
			break;
		case 2:
			return m_fZ;
			break;
	}
	return FLT_MAX;
}

SICPPSDK_INLINE float& CVector3f::operator[](const short& in_sIndex)
{
	assert(in_sIndex >= 0 && in_sIndex < 3);
	switch(in_sIndex)
	{
		case 0:
			return m_fX;
			break;
		case 1:
			return m_fY;
			break;
		case 2:
			return m_fZ;
			break;
	}
	static float fMAX = FLT_MAX;
	return fMAX;
}

SICPPSDK_INLINE bool CVector3f::operator < ( const CVector3f& in_v3f) const
{
	if ( m_fZ != in_v3f.m_fZ ) return m_fZ < in_v3f.m_fZ;
	if ( m_fY != in_v3f.m_fY ) return m_fY < in_v3f.m_fY;
	if ( m_fX != in_v3f.m_fX ) return m_fX < in_v3f.m_fX;
	return false;
}

SICPPSDK_INLINE float CVector3f::Get(const short& in_sIndex) const
{
	assert(in_sIndex >= 0 && in_sIndex < 3);
	switch(in_sIndex)
	{
		case 0:
			return m_fX;
			break;
		case 1:
			return m_fY;
			break;
		case 2:
			return m_fZ;
			break;
	}
	return FLT_MAX;
}

SICPPSDK_INLINE void CVector3f::Set(const short& in_sIndex, const float in_value )
{
	assert(in_sIndex >= 0 && in_sIndex < 3);
	switch(in_sIndex)
	{
		case 0:
			m_fX = in_value;
			break;
		case 1:
			m_fY = in_value;
			break;
		case 2:
			m_fZ = in_value;
			break;
	}
}

SICPPSDK_INLINE CVector3f& CVector3f::MulByMatrix3InPlace(const CMatrix3f& in_matrix3)
{
	return MulByMatrix3((*this),in_matrix3);
}

SICPPSDK_INLINE CVector3f& CVector3f::MulByMatrix3
(
	const CVector3f& in_vector3,
	const CMatrix3f& in_matrix3
)
{
	float l_fX, l_fY,l_fZ;
	l_fX = in_vector3.GetX() * in_matrix3.GetValue(0,0) +
		   in_vector3.GetY() * in_matrix3.GetValue(1,0) +
		   in_vector3.GetZ() * in_matrix3.GetValue(2,0);
	l_fY = in_vector3.GetX() * in_matrix3.GetValue(0,1) +
		   in_vector3.GetY() * in_matrix3.GetValue(1,1) +
		   in_vector3.GetZ() * in_matrix3.GetValue(2,1);
	l_fZ = in_vector3.GetX() * in_matrix3.GetValue(0,2) +
		   in_vector3.GetY() * in_matrix3.GetValue(1,2) +
		   in_vector3.GetZ() * in_matrix3.GetValue(2,2);

	return Set(l_fX,l_fY,l_fZ);
}

SICPPSDK_INLINE CVector3f& CVector3f::MulByMatrix4InPlace(const CMatrix4f& in_matrix4)
{
	return MulByMatrix4((*this),in_matrix4);
}

SICPPSDK_INLINE CVector3f& CVector3f::MulByMatrix4
(
	const CVector3f& in_vector3,
	const CMatrix4f& in_matrix4
)
{
	float l_fX, l_fY, l_fZ, l_fW;

	l_fX =	in_vector3.GetX() * in_matrix4.GetValue( 0, 0 ) +
			in_vector3.GetY() * in_matrix4.GetValue( 1, 0 ) +
			in_vector3.GetZ() * in_matrix4.GetValue( 2, 0 ) +
			in_matrix4.GetValue( 3, 0 );
	l_fY =	in_vector3.GetX() * in_matrix4.GetValue( 0, 1 ) +
			in_vector3.GetY() * in_matrix4.GetValue( 1, 1 ) +
			in_vector3.GetZ() * in_matrix4.GetValue( 2, 1 ) +
			in_matrix4.GetValue( 3, 1 );
	l_fZ =	in_vector3.GetX() * in_matrix4.GetValue( 0, 2 ) +
			in_vector3.GetY() * in_matrix4.GetValue( 1, 2 ) +
			in_vector3.GetZ() * in_matrix4.GetValue( 2, 2 ) +
			in_matrix4.GetValue( 3, 2 );
	l_fW =	in_vector3.GetX() * in_matrix4.GetValue( 0, 3 ) +
			in_vector3.GetY() * in_matrix4.GetValue( 1, 3 ) +
			in_vector3.GetZ() * in_matrix4.GetValue( 2, 3 ) +
			in_matrix4.GetValue( 3, 3 );

	return Set(l_fX/l_fW, l_fY/l_fW, l_fZ/l_fW);
}

SICPPSDK_INLINE CVector3f& CVector3f::SetNull()
{
	m_fX = m_fY = m_fZ = 0.0;
	return (*this);
}

SICPPSDK_INLINE bool CVector3f::IsNull( const float in_fEpsilon )
{
	return( fabs(m_fX) <= in_fEpsilon && fabs(m_fY)<= in_fEpsilon && fabs(m_fZ)<= in_fEpsilon );
}

SICPPSDK_INLINE short CVector3f::GetMaxComponentIndex()const
{
	if( m_fX > m_fY )
	{
		return (short)(( m_fX > m_fZ ) ? 0 : 2);
	}
	else
	{
		return (short)(( m_fY > m_fZ ) ? 1 : 2);
	}
	return 0;
}

SICPPSDK_INLINE float CVector3f::GetMaxComponent()const
{
	if( m_fX > m_fY )
	{
		return ( m_fX > m_fZ ) ? m_fX : m_fZ;
	}
	else
	{
		return ( m_fY > m_fZ ) ? m_fY : m_fZ;
	}
	return 0.0;
}

SICPPSDK_INLINE short CVector3f::GetMinComponentIndex()const
{
	if( m_fX < m_fY )
	{
		return (short)(( m_fX < m_fZ ) ? 0 : 2);
	}
	else
	{
		return (short)(( m_fY < m_fZ ) ? 1 : 2);
	}
	return 0;
}

SICPPSDK_INLINE float CVector3f::GetMinComponent()const
{
	if( m_fX < m_fY )
	{
		return ( m_fX < m_fZ ) ? m_fX : m_fZ;
	}
	else
	{
		return ( m_fY < m_fZ ) ? m_fY : m_fZ;
	}
	return 0.0;
}

SICPPSDK_INLINE float CVector3f::GetLength()const
{
	return sqrt( GetLengthSquared() );
}

SICPPSDK_INLINE void CVector3f::SetLength(const float in_val)
{
	float rLen = GetLength();

	if ( rLen > MicroEPS )
	{
		ScaleInPlace( in_val / rLen );
	}
}

SICPPSDK_INLINE float CVector3f::GetLengthSquared()const
{
	return(m_fX*m_fX + m_fY*m_fY + m_fZ*m_fZ );
}

SICPPSDK_INLINE float CVector3f::Dot(const CVector3f& io_vec3)const
{
	return ( m_fX*io_vec3.GetX() + m_fY*io_vec3.GetY() + m_fZ*io_vec3.GetZ() );
}

SICPPSDK_INLINE CVector3f& CVector3f::Cross
(
	const CVector3f& in_vec3A,
	const CVector3f& in_vec3B
)
{
	float dX, dY, dZ;

	dX =	in_vec3A.GetY() * in_vec3B.GetZ() -
			in_vec3A.GetZ() * in_vec3B.GetY();
	dY =   -in_vec3A.GetX() * in_vec3B.GetZ() +
			in_vec3A.GetZ() * in_vec3B.GetX();
	dZ =	in_vec3A.GetX() * in_vec3B.GetY() -
			in_vec3A.GetY() * in_vec3B.GetX();

   return( Set( dX, dY, dZ ) );
}

SICPPSDK_INLINE CVector3f& CVector3f::LinearlyInterpolate
(
	const CVector3f&	in_vec3A,
	const CVector3f&	in_vec3B,
	const float			in_fAlpha
)
{
	m_fX = (1 - in_fAlpha) * in_vec3A.GetX() + in_fAlpha * in_vec3B.GetX();
	m_fY = (1 - in_fAlpha) * in_vec3A.GetY() + in_fAlpha * in_vec3B.GetY();
	m_fZ = (1 - in_fAlpha) * in_vec3A.GetZ() + in_fAlpha * in_vec3B.GetZ();

	return (*this);
}

SICPPSDK_INLINE bool CVector3f::EpsilonEquals
(
	const CVector3f& in_cVec3,
	const float in_fEpsilon
)const
{
	return (this == &in_cVec3) ? true :
		(fabs( m_fX - in_cVec3.GetX() ) < ::fabs(in_fEpsilon) &&
		   fabs( m_fY - in_cVec3.GetY() ) < ::fabs(in_fEpsilon) &&
		   fabs( m_fZ - in_cVec3.GetZ() ) < ::fabs(in_fEpsilon) );
}


SICPPSDK_INLINE bool CVector3f::Equals(const CVector3f& in_vec3)const
{
	return (this == &in_vec3) ? true :
		( ( m_fX == in_vec3.GetX() ) &&
		  ( m_fY == in_vec3.GetY() ) &&
		  ( m_fZ == in_vec3.GetZ() ) );
}

SICPPSDK_INLINE CVector3f& CVector3f::ScaleAddInPlace
(
	const float in_fScalingFactor,
	const CVector3f& in_vec3
)
{
	ScaleInPlace(in_fScalingFactor);
	return AddInPlace(in_vec3);
}


SICPPSDK_INLINE CVector3f& CVector3f::ScaleAdd
(
	const float in_fScalingFactor,
	const CVector3f& in_vec3A,
	const CVector3f& in_vec3B
)
{
	Scale(in_fScalingFactor, in_vec3A);
	return AddInPlace(in_vec3B);
}

SICPPSDK_INLINE CVector3f& CVector3f::ScaleInPlace(const float in_fScalingFactor)
{
	m_fX *= in_fScalingFactor;
	m_fY *= in_fScalingFactor;
	m_fZ *= in_fScalingFactor;
	return (*this);
}

SICPPSDK_INLINE CVector3f& CVector3f::Scale
(
	const float in_fScalingFactor,
	const CVector3f& in_vec3
)
{
	m_fX = in_vec3.GetX() * in_fScalingFactor;
	m_fY = in_vec3.GetY() * in_fScalingFactor;
	m_fZ = in_vec3.GetZ() * in_fScalingFactor;
	return (*this);
}

SICPPSDK_INLINE CVector3f& CVector3f::NegateInPlace()
{
	m_fX = -m_fX;
	m_fY = -m_fY;
	m_fZ = -m_fZ;
	return (*this);
}

SICPPSDK_INLINE CVector3f& CVector3f::Negate(const CVector3f& in_vec3 )
{
	m_fX = -in_vec3.GetX();
	m_fY = -in_vec3.GetY();
	m_fZ = -in_vec3.GetZ();
	return (*this);
}

SICPPSDK_INLINE CVector3f& CVector3f::SubInPlace(const CVector3f& in_vec3)
{
	m_fX -= in_vec3.GetX();
	m_fY -= in_vec3.GetY();
	m_fZ -= in_vec3.GetZ();
	return (*this);
}

SICPPSDK_INLINE CVector3f& CVector3f::Sub
(
	const CVector3f& in_vec3A,
	const CVector3f& in_vec3B
)
{
	m_fX = in_vec3A.GetX() - in_vec3B.GetX();
	m_fY = in_vec3A.GetY() - in_vec3B.GetY();
	m_fZ = in_vec3A.GetZ() - in_vec3B.GetZ();
	return (*this);
}

SICPPSDK_INLINE CVector3f& CVector3f::AddInPlace(const CVector3f& in_vec3)
{
	m_fX += in_vec3.GetX();
	m_fY += in_vec3.GetY();
	m_fZ += in_vec3.GetZ();
	return (*this);
}

SICPPSDK_INLINE CVector3f& CVector3f::Add
(
	const CVector3f& in_vec3A,
	const CVector3f& in_vec3B
)
{
	m_fX = in_vec3A.GetX() + in_vec3B.GetX();
	m_fY = in_vec3A.GetY() + in_vec3B.GetY();
	m_fZ = in_vec3A.GetZ() + in_vec3B.GetZ();
	return (*this);
}

SICPPSDK_INLINE void CVector3f::Get(float& io_rfX, float& io_rfY, float& io_rfZ)const
{
	io_rfX = m_fX;
	io_rfY = m_fY;
	io_rfZ = m_fZ;
}

SICPPSDK_INLINE CVector3f& CVector3f::Set(const float in_fX, const float in_fY, const float in_fZ)
{
	m_fX = in_fX;
	m_fY = in_fY;
	m_fZ = in_fZ;
	return (*this);
}

SICPPSDK_INLINE float CVector3f::GetZ()const
{
	return m_fZ;
}

SICPPSDK_INLINE CVector3f&	CVector3f::PutZ(const float in_fZ)
{
	m_fZ = in_fZ;
	return (*this);
}

SICPPSDK_INLINE float CVector3f::GetY()const
{
	return m_fY;
}

SICPPSDK_INLINE CVector3f& CVector3f::PutY(const float in_fY)
{
	m_fY = in_fY;
	return (*this);
}

SICPPSDK_INLINE float CVector3f::GetX()const
{
	return m_fX;
}

SICPPSDK_INLINE CVector3f& CVector3f::PutX(const float in_fX)
{
	m_fX = in_fX;
	return (*this);
}

SICPPSDK_INLINE CStatus CVector3f::NormalizeInPlace()
{
	float rLen = GetLength();

	if ( rLen > MicroEPS )
	{
		m_fX /= rLen ;
		m_fY /= rLen ;
		m_fZ /= rLen ;
		return CStatus::OK;
	}

	return CStatus::Fail;
}

SICPPSDK_INLINE CStatus CVector3f::Normalize(const CVector3f& in_vec3)
{
	float rLen = in_vec3.GetLength();

	if ( rLen > MicroEPS )
	{
		m_fX = in_vec3.GetX() / rLen ;
		m_fY = in_vec3.GetY() / rLen ;
		m_fZ = in_vec3.GetZ() / rLen ;
		return CStatus::OK;
	}

	return CStatus::Fail;
}

SICPPSDK_INLINE float CVector3f::GetAngle( const CVector3f& in_vec3 ) const
{
	float fCosAngle, fLen;

	fLen = GetLength();
	fLen *= in_vec3.GetLength();
	if( fLen < MicroEPS )
	{
		return( 0.0 );
	}
	else
	{
		fCosAngle = ( m_fX*in_vec3.GetX() + m_fY*in_vec3.GetY() + m_fZ*in_vec3.GetZ() ) / fLen;
		LimitValue( fCosAngle, -1.0, 1.0 );
		return( acos( fCosAngle ) );
	}
	return( 0.0 );
}

SICPPSDK_INLINE CVector3f& CVector3f::AbsoluteInPlace()
{
	float l_fX, l_fY, l_fZ;
	Get(l_fX, l_fY, l_fZ);
	Set(::fabs(l_fX), ::fabs(l_fY), ::fabs(l_fZ));
	return (*this);
}

SICPPSDK_INLINE CVector3f& CVector3f::Absolute(const CVector3f& in_rCVec3)
{
	float l_fX, l_fY, l_fZ;
	in_rCVec3.Get(l_fX, l_fY, l_fZ);
	m_fX = ::fabs(l_fX);
	m_fY = ::fabs(l_fY);
	m_fZ = ::fabs(l_fZ);

	return (*this);
}

SICPPSDK_INLINE CVector3f& CVector3f::ClampInPlace(const float in_fMin, const float in_fMax)
{
	float l_fX, l_fY, l_fZ;

	Get( l_fX, l_fY, l_fZ );

	LimitValue( l_fX, in_fMin, in_fMax );
	LimitValue( l_fY, in_fMin, in_fMax );
	LimitValue( l_fZ, in_fMin, in_fMax );

	Set( l_fX, l_fY, l_fZ );

	return (*this);
}

};
};

#endif // __XSIVECTOR3F_H__
