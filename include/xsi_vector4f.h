//*****************************************************************************
/*!
   \file xsi_vector4f.h
   \brief CVector4f class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIVECTOR4F_H__
#define __XSIVECTOR4F_H__

#include "sicppsdk.h"
#include "xsi_matrix4f.h"

namespace XSI {

namespace MATH {

//*****************************************************************************
/*! \class CVector4f xsi_vector4f.h
	\brief A 4-element vector that is represented by single floating point x,y,z coordinates. The class is used
	used for implementing custom ICE nodes.

	\sa CVector3f, CMatrix4f
 */
//*****************************************************************************
class SICPPSDKDECL CVector4f
{
public:
	/*! Default constructor. */
	SICPPSDK_INLINE CVector4f();

	/*! Constructor.
	\param in_fX Value of the x component
	\param in_fY Value of the y component
	\param in_fZ Value of the z component
	\param in_fW Value of the w component
	*/
	SICPPSDK_INLINE CVector4f(float in_fX, float in_fY, float in_fZ, float in_fW);

	/*! Copy constructor.
	\param in_vector4 constant class object.
	*/
	SICPPSDK_INLINE CVector4f( const CVector4f& in_vector4);

	/*! Default destructor. */
	SICPPSDK_INLINE ~CVector4f();

	/*! Assignment operator.
	\param in_vector4 constant class object.
	\return A reference to this quaternion.
	*/
	SICPPSDK_INLINE CVector4f & operator=( const CVector4f & in_vector4 );

	/*! Equality operator tests the strict equality of this vector with the specified vector.
	\param in_vector4 Operand vector.
	\return true if equal else false.
	\sa CVector4f::Equals
	*/
	SICPPSDK_INLINE bool operator ==(const CVector4f & in_vector4 )const;

	/*! Inequality operator tests the strict inequality of this vector with the specified vector.
	\param in_vector4 Operand vector.
	\return true if equal else false.
	\sa CVector4f::Equals
	*/
	SICPPSDK_INLINE bool operator !=(const CVector4f & in_vector4 )const;

	/*! Less than operator. Performs a comparison with a specified CVector4f to determine if this CVector4f is
	less than the specified CVector4f. The comparison is arbitrary and not geometrically meaningful, it's only purpose is
	to make CVector4f compliant with stl for sorting operations.
	\param in_vector4 CVector4f to compare.
	\return true if this CVector4f is less than the specified CVector4f, false otherwise.
	\since 7.5
	*/
	SICPPSDK_INLINE bool operator < ( const CVector4f & in_vector4 ) const;

	/*! Negates this vector (this = - this).
	\return A reference to this vector.
	\sa CVector4f::NegateInPlace
	*/
	SICPPSDK_INLINE CVector4f& operator ~();

	/*! Adds the input vector to this one (this = this + in_vector4).
	\param in_vector4 Operand vector.
	\return A reference to this vector.
	\sa CVector4f::AddInPlace
	*/
	SICPPSDK_INLINE CVector4f& operator +=(const CVector4f& in_vector4);

	/*! Subtracts the input vector4 (in_vector4) from this one (this = this - in_vector4).
	\param in_vector4 Operand vector.
	\return A reference to this vector.
	\sa CVector4f::SubInPlace
	*/
	SICPPSDK_INLINE CVector4f& operator -=(const CVector4f & in_vector4);

	/*! Right-multiplies this vector by the matrix m in place. (this = this * m )
	\param in_matrix4 Operand matrix.
	\return A reference to this vector.
	\sa CVector4f::MulByMatrix4InPlace
	*/
	SICPPSDK_INLINE CVector4f& operator *=(const CMatrix4f& in_matrix4);

	/*! Scales this vector by the input scalar (alpha) (this = alpha * this).
	\param in_fAlpha  Scalar multiplicator.
	\return A reference to this vector.
	\sa CVector4f::ScaleInPlace
	*/
	SICPPSDK_INLINE CVector4f& operator *=(const float& in_fAlpha);

	/*! Read-only accessors to the X,Y,Z,W components.
	\param in_sIndex  0,1,2,3 for X,Y,Z and W values.
	\return The value of the specified component. If the index supplied is out of range the function returns DBL_MAX.
	\sa CVector4f::GetX(), CVector4f::GetY(), CVector4f::GetZ(), CVector4f::GetW()
	*/
	SICPPSDK_INLINE float operator[](const short& in_sIndex);

	/*! Right-multiplies this vector by the matrix m in place (this = this * m ).
	\param in_matrix4 Operand matrix.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector4f& MulByMatrix4InPlace(const CMatrix4f& in_matrix4);

	/*! Right-multiplies the vector v by the matrix m and store the result in this vector (this = v * m ).
	\param in_vector4 Operand vector
	\param in_matrix4 Operand matrix.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector4f& MulByMatrix4
	(
		const CVector4f& in_vector4,
		const CMatrix4f& in_matrix4
	);

	/*! Sets this vector to a null vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector4f& SetNull();

	/*! Returns the length of this vector.
	\return Length of this vector.
	*/
	float GetLength()const;

	/*! Returns the squared length of this vector.
	\return Squared length of this vector.
	*/
	float GetLengthSquared()const;

	/*! Normalizes this vector in place.
	\return CStatus::OK if the normalization has been computed,
	*/
	SICPPSDK_INLINE CStatus NormalizeInPlace();

	/*! Sets the value of this vector to the normalization of inputed vector.
	\param in_vector4 vector operand.
	\return CStatus::OK if the normalization has been computed.
	*/
	SICPPSDK_INLINE CStatus Normalize(const CVector4f& in_vector4);

	/*! Returns the dot product of this vector and the input vector.
	\param in_vector4 vector operand.
	\return Dot product of this vector and vector in_vector4.
	*/
	SICPPSDK_INLINE float Dot(const CVector4f& in_vector4)const;

	/*! Sets this vector to the vector cross product of vectors A and B.
	\param in_vector4A vector operand.
	\param in_vector4B vector operand.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector4f& Cross(const CVector4f& in_vector4A, const CVector4f& in_vector4B);

	/*! Sets each component of this vector to its absolute value.
	\return A reference to this vector.
	*/
	CVector4f& AbsoluteInPlace();

	/*! Sets each component of the specified vector to its absolute value and places the modified values into this vector
	\param in_vector4 Vector to make absolute
	\return A reference to this vector.
	*/
	CVector4f& Absolute(const CVector4f& in_vector4);

	/*! Tests the equality of this vector with the vector in_vector3, with a tolerance of Epsilon.
	\param in_vector4 Operand vector.
	\param in_fEpsilon Error margin Possible Values: [0, +INF[ should be a positive value
	\return true if equal else false.
	*/
	bool EpsilonEquals( const CVector4f& in_vector4, float in_fEpsilon) const;

	/*! Tests the strict equality of this vector with the vector in_vector3.
	\param in_vector4 Operand vector.
	\return true if equal else false.
	*/
	SICPPSDK_INLINE bool Equals(const CVector4f& in_vector4)const;

	/*! Sets the value of this vector to the scalar multiplication of itself by s and then adds vector v (this = s*this + v).
	\param in_fS  Scalar multiplicator.
	\param in_vector4 Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector4f& ScaleAddInPlace(float in_fS,const CVector4f& in_vector4);

	/*! Sets the value of this vector to the scalar multiplication of vector A by s and then adds vector B (this = s*v1 + v2).
	\param in_fS  Scalar multiplicator.
	\param in_vector4A Operand vector.
	\param in_vector4B Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector4f& ScaleAdd
	(
		float				in_fS,
		const CVector4f&	in_vector4A,
		const CVector4f&	in_vector4B
	);

	/*! Scales this vector by the input scalar (alpha) (this = alpha * this).
	\param in_fAlpha  Scalar multiplicator.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector4f& ScaleInPlace(float in_fAlpha);

	/*! Scales the input vector (v) by (alpha) store the result into this one (this = alpha * v).
	\param in_fAlpha  Scalar multiplicator.
	\param in_vector4 Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector4f& Scale(float in_fAlpha, const CVector4f& in_vector4);

	/*! Negates this vector (this = - this).
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector4f& NegateInPlace();

	/*! Negates the input vector (v) store the result into this one (this = - v).
	\param in_vector4 Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector4f& Negate(const CVector4f& in_vector4);

	/*! Subtracts the input vector (v) from this one (this = this - v).
	\param in_vector4 Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector4f& SubInPlace(const CVector4f& in_vector4);

	/*! Subtracts the input vector (\c in_vector4B) from the input vector (\c in_vector4A) and stores
	the result into this one (<tt>this = in_vector4A - in_vector4B</tt>).
	\param in_vector4A Operand vector.
	\param in_vector4B Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector4f& Sub(const CVector4f& in_vector4A, const CVector4f& in_vector4B);

	/*! Adds the input vector to this one (this = this + in_vector3).
	\param in_vector4 Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector4f& AddInPlace(const CVector4f& in_vector4);

	/*! Adds both input vectors and store the result in this one (this = A + B).
	\param in_vector4A Operand vector.
	\param in_vector4B Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector4f& Add(const CVector4f& in_vector4A,const CVector4f& in_vector4B);

	/*! Returns the X, Y, Z and W values of the vector.
	\retval out_fX X value to get in the vector.
	\retval out_fY Y value to get in the vector.
	\retval out_fZ Z value to get in the vector.
	\retval out_fW W value to get in the vector.
	*/
	SICPPSDK_INLINE void Get( float& out_fX, float& out_fY,	float& out_fZ, float& out_fW )const;

	/*! Sets the X, Y, Z and W values of the vector.
	\param in_fX X value to set in the vector.
	\param in_fY Y value to set in the vector.
	\param in_fZ Z value to set in the vector.
	\param in_fW W value to set in the vector.
	\return A reference to the vector.
	*/
	SICPPSDK_INLINE CVector4f& Set(float in_fX, float in_fY, float in_fZ, float in_fW);

	/*! Returns the W value of this vector.
	\return W value of this vector.
	*/
	SICPPSDK_INLINE float GetW()const;

	/*! Sets the W value of this vector.
	\param in_fW z value.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector4f& PutW(float in_fW);

	/*! Returns the Z value of this vector.
	\return Z value of this vector.
	*/
	SICPPSDK_INLINE float GetZ()const;

	/*! Sets the Z value of this vector.
	\param in_fZ z value.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector4f& PutZ(float in_fZ);

	/*! Returns the Y value of this vector.
	\return Y value of this vector.
	*/
	SICPPSDK_INLINE float GetY()const;

	/*! Sets the Y value of this vector.
	\param in_fY y value.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector4f& PutY(float in_fY);

	/*! Returns the X value of this vector.
	\return X value of this vector.
	*/
	SICPPSDK_INLINE float GetX()const;

	/*! Sets the X value of this vector.
	\param in_fX x value.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector4f& PutX(float in_fX);

private:
	float m_fX,m_fY,m_fZ,m_fW;
};

SICPPSDK_INLINE CVector4f::CVector4f(): m_fX(0.0),m_fY(0.0),m_fZ(0.0), m_fW(0.0)
{}

SICPPSDK_INLINE CVector4f::CVector4f
(
 float in_fX, float in_fY, float in_fZ, float in_fW
):m_fX(in_fX),m_fY(in_fY),m_fZ(in_fZ), m_fW(in_fW)
{}

SICPPSDK_INLINE CVector4f::~CVector4f()
{}

SICPPSDK_INLINE CVector4f::CVector4f( const CVector4f& in_vct )
{
	in_vct.Get(m_fX,m_fY,m_fZ,m_fW);
}

SICPPSDK_INLINE CVector4f& CVector4f::operator=( const CVector4f & in_vct )
{
	in_vct.Get(m_fX,m_fY,m_fZ,m_fW);
	return (*this);
}

SICPPSDK_INLINE bool CVector4f::operator ==(const CVector4f & in_vector4 )const
{
	return Equals(in_vector4);
}

SICPPSDK_INLINE bool CVector4f::operator !=(const CVector4f & in_vector4 )const
{
	return ! Equals(in_vector4);
}

SICPPSDK_INLINE bool CVector4f::operator < ( const CVector4f& in_vector4 ) const
{
	if ( m_fW != in_vector4.m_fW ) return m_fW < in_vector4.m_fW;
	if ( m_fZ != in_vector4.m_fZ ) return m_fZ < in_vector4.m_fZ;
	if ( m_fY != in_vector4.m_fY ) return m_fY < in_vector4.m_fY;
	if ( m_fX != in_vector4.m_fX ) return m_fX < in_vector4.m_fX;
	return false;
}

SICPPSDK_INLINE CVector4f& CVector4f::operator ~()
{
	return NegateInPlace();
}

SICPPSDK_INLINE CVector4f& CVector4f::operator +=(const CVector4f& in_vector4)
{
	return AddInPlace(in_vector4);
}

SICPPSDK_INLINE CVector4f& CVector4f::operator -=(const CVector4f& in_vector4)
{
	return SubInPlace(in_vector4);
}

SICPPSDK_INLINE CVector4f& CVector4f::operator *=(const CMatrix4f& in_matrix4)
{
	return MulByMatrix4InPlace(in_matrix4);
}

SICPPSDK_INLINE CVector4f& CVector4f::operator *=(const float& in_fAlpha)
{
	return ScaleInPlace(in_fAlpha);
}

SICPPSDK_INLINE CVector4f& CVector4f::MulByMatrix4InPlace
(
	const CMatrix4f& in_matrix4
)
{
	return MulByMatrix4((*this),in_matrix4);
}

SICPPSDK_INLINE CVector4f& CVector4f::MulByMatrix4
(
	const CVector4f& in_vector4,
	const CMatrix4f& in_matrix4
)
{
	float l_fX, l_fY, l_fZ, l_fW;

	l_fX =	in_vector4.GetX() * in_matrix4.GetValue( 0, 0 ) +
			in_vector4.GetY() * in_matrix4.GetValue( 1, 0 ) +
			in_vector4.GetZ() * in_matrix4.GetValue( 2, 0 ) +
			in_vector4.GetW() * in_matrix4.GetValue( 3, 0 );
	l_fY =	in_vector4.GetX() * in_matrix4.GetValue( 0, 1 ) +
			in_vector4.GetY() * in_matrix4.GetValue( 1, 1 ) +
			in_vector4.GetZ() * in_matrix4.GetValue( 2, 1 ) +
			in_vector4.GetW() * in_matrix4.GetValue( 3, 1 );
	l_fZ =	in_vector4.GetX() * in_matrix4.GetValue( 0, 2 ) +
			in_vector4.GetY() * in_matrix4.GetValue( 1, 2 ) +
			in_vector4.GetZ() * in_matrix4.GetValue( 2, 2 ) +
			in_vector4.GetW() * in_matrix4.GetValue( 3, 2 );
	l_fW =	in_vector4.GetX() * in_matrix4.GetValue( 0, 3 ) +
			in_vector4.GetY() * in_matrix4.GetValue( 1, 3 ) +
			in_vector4.GetZ() * in_matrix4.GetValue( 2, 3 ) +
			in_vector4.GetW() * in_matrix4.GetValue( 3, 3 );

	return Set(l_fX, l_fY, l_fZ, l_fW);
}

SICPPSDK_INLINE CVector4f& CVector4f::SetNull()
{
	m_fX = m_fY = m_fZ = m_fW = 0.0;
	return (*this);
}

SICPPSDK_INLINE float CVector4f::Dot(const CVector4f& in_vector4)const
{

	return ( m_fX*in_vector4.GetX() + m_fY*in_vector4.GetY() +
			m_fZ*in_vector4.GetZ() + m_fW*in_vector4.GetW());
}

SICPPSDK_INLINE bool CVector4f::Equals(const CVector4f& in_vector4)const
{
	return (this == &in_vector4) ? true :
			( ( m_fX == in_vector4.GetX() ) &&
			  ( m_fY == in_vector4.GetY() ) &&
			  ( m_fZ == in_vector4.GetZ() ) &&
			  ( m_fW == in_vector4.GetW() ) );
}

SICPPSDK_INLINE CVector4f& CVector4f::ScaleAddInPlace
(
	float in_fScalingFactor,
	const CVector4f& in_vector4
)
{
	ScaleInPlace(in_fScalingFactor);
	return AddInPlace(in_vector4);
}

SICPPSDK_INLINE CVector4f& CVector4f::ScaleAdd
(
	const float in_fScalingFactor,
	const CVector4f& in_vector4A,
	const CVector4f& in_vector4B
)
{
	Scale(in_fScalingFactor, in_vector4A);
	return AddInPlace(in_vector4B);
}

SICPPSDK_INLINE CVector4f& CVector4f::ScaleInPlace(float in_fScalingFactor)
{
	m_fX *= in_fScalingFactor;
	m_fY *= in_fScalingFactor;
	m_fZ *= in_fScalingFactor;
	m_fW *= in_fScalingFactor;
	return (*this);
}

SICPPSDK_INLINE CVector4f& CVector4f::Scale
(
 float in_fScalingFactor,
 const CVector4f& in_vector4
)
{
	m_fX = in_vector4.GetX() * in_fScalingFactor;
	m_fY = in_vector4.GetY() * in_fScalingFactor;
	m_fZ = in_vector4.GetZ() * in_fScalingFactor;
	m_fW = in_vector4.GetW() * in_fScalingFactor;
	return (*this);
}

SICPPSDK_INLINE CVector4f& CVector4f::NegateInPlace()
{
	m_fX = -m_fX;
	m_fY = -m_fY;
	m_fZ = -m_fZ;
	m_fW = -m_fW;
	return (*this);
}

SICPPSDK_INLINE CVector4f& CVector4f::Negate(const CVector4f& in_vector4 )
{
	m_fX = -in_vector4.GetX();
	m_fY = -in_vector4.GetY();
	m_fZ = -in_vector4.GetZ();
	m_fW = -in_vector4.GetW();
	return (*this);
}

SICPPSDK_INLINE CVector4f& CVector4f::SubInPlace(const CVector4f& in_vector4)
{
	m_fX -= in_vector4.GetX();
	m_fY -= in_vector4.GetY();
	m_fZ -= in_vector4.GetZ();
	m_fW -= in_vector4.GetW();
	return (*this);
}

SICPPSDK_INLINE CVector4f& CVector4f::Sub
(
	const CVector4f& in_vector4A,
	const CVector4f& in_vector4B
)
{
	m_fX = in_vector4A.GetX() - in_vector4B.GetX();
	m_fY = in_vector4A.GetY() - in_vector4B.GetY();
	m_fZ = in_vector4A.GetZ() - in_vector4B.GetZ();
	m_fW = in_vector4A.GetW() - in_vector4B.GetW();
	return (*this);
}

SICPPSDK_INLINE CVector4f& CVector4f::AddInPlace(const CVector4f& in_vector4)
{
	m_fX += in_vector4.GetX();
	m_fY += in_vector4.GetY();
	m_fZ += in_vector4.GetZ();
	m_fW += in_vector4.GetW();
	return (*this);
}

SICPPSDK_INLINE CVector4f& CVector4f::Add
(
	const CVector4f& in_vector4A,
	const CVector4f& in_vector4B
)
{
	m_fX = in_vector4A.GetX() + in_vector4B.GetX();
	m_fY = in_vector4A.GetY() + in_vector4B.GetY();
	m_fZ = in_vector4A.GetZ() + in_vector4B.GetZ();
	m_fW = in_vector4A.GetW() + in_vector4B.GetW();
	return (*this);
}

SICPPSDK_INLINE void CVector4f::Get
(
	float& out_rdX,
	float& out_rdY,
	float& out_rdZ,
	float& out_rdW
)const
{
	out_rdX = m_fX;
	out_rdY = m_fY;
	out_rdZ = m_fZ;
	out_rdW = m_fW;
}

SICPPSDK_INLINE CVector4f& CVector4f::Set
(
	float in_fX,
	float in_fY,
	float in_fZ,
	float in_fW
)
{
	m_fX = in_fX;
	m_fY = in_fY;
	m_fZ = in_fZ;
	m_fW = in_fW;
	return (*this);
}

SICPPSDK_INLINE float CVector4f::GetW()const
{
	return m_fW;
}

SICPPSDK_INLINE CVector4f&	CVector4f::PutW(float in_fW)
{
	m_fW = in_fW;
	return (*this);
}

SICPPSDK_INLINE float CVector4f::GetZ()const
{
	return m_fZ;
}

SICPPSDK_INLINE CVector4f&	CVector4f::PutZ(float in_fZ)
{
	m_fZ = in_fZ;
	return (*this);
}

SICPPSDK_INLINE float CVector4f::GetY()const
{
	return m_fY;
}

SICPPSDK_INLINE CVector4f& CVector4f::PutY(float in_fY)
{
	m_fY = in_fY;
	return (*this);
}

SICPPSDK_INLINE float CVector4f::GetX()const
{
	return m_fX;
}

SICPPSDK_INLINE CVector4f& CVector4f::PutX(float in_fX)
{
	m_fX = in_fX;
	return (*this);
}

SICPPSDK_INLINE float CVector4f::operator[](const short& in_sIndex)
{
	assert(in_sIndex >= 0 && in_sIndex < 4);
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
		case 3:
			return m_fW;
			break;
	}
	return FLT_MAX;
}

SICPPSDK_INLINE CVector4f& CVector4f::AbsoluteInPlace()
{
	::fabs(m_fX);
	::fabs(m_fY);
	::fabs(m_fZ);
	::fabs(m_fW);
	return (*this);
}

SICPPSDK_INLINE CVector4f& CVector4f::Absolute(const CVector4f& in_vector4)
{
	float dX, dY, dZ, dW;
	in_vector4.Get(dX, dY, dZ, dW);
	m_fX = ::fabs(dX);
	m_fY = ::fabs(dY);
	m_fZ = ::fabs(dZ);
	m_fW = ::fabs(dW);

	return (*this);
}
SICPPSDK_INLINE bool CVector4f::EpsilonEquals
(
	const CVector4f& in_vector4,
	float in_fEpsilon
)const
{
	return (this == &in_vector4) ? true :
		(fabs( m_fX - in_vector4.GetX() ) < ::fabs(in_fEpsilon) &&
		 fabs( m_fY - in_vector4.GetY() ) < ::fabs(in_fEpsilon) &&
		 fabs( m_fZ - in_vector4.GetZ() ) < ::fabs(in_fEpsilon) &&
		 fabs( m_fW - in_vector4.GetW() ) < ::fabs(in_fEpsilon));
}

SICPPSDK_INLINE float CVector4f::GetLength()const
{
	return sqrt( GetLengthSquared() );
}

SICPPSDK_INLINE float CVector4f::GetLengthSquared()const
{
	 return(m_fX*m_fX + m_fY*m_fY + m_fZ*m_fZ  + m_fW*m_fW);
}

SICPPSDK_INLINE CStatus CVector4f::NormalizeInPlace()
{
	float rLen = GetLength();

	if ( rLen > MicroEPS )
	{
		m_fX /= rLen ;
		m_fY /= rLen ;
		m_fZ /= rLen ;
		m_fW /= rLen ;
		return CStatus::OK;
	}

	return CStatus::Fail;
}

SICPPSDK_INLINE CStatus CVector4f::Normalize(const CVector4f& in_vector4)
{
	float rLen = in_vector4.GetLength();

	if ( rLen > MicroEPS )
	{
		m_fX = in_vector4.GetX() / rLen ;
		m_fY = in_vector4.GetY() / rLen ;
		m_fZ = in_vector4.GetZ() / rLen ;
		m_fW = in_vector4.GetW() / rLen ;
		return CStatus::OK;
	}

	return CStatus::Fail;
}

};
};

#endif // __XSIVECTOR4_H__
