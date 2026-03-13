//*****************************************************************************
/*!
   \file xsi_quaternionf.h
   \brief CQuaternionf class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************
#ifndef __XSIQUATERNIONF_H__
#define __XSIQUATERNIONF_H__

#include "sicppsdk.h"
#include "xsi_vector4f.h"
#include "xsi_vector3f.h"

namespace XSI {

namespace MATH {

class CRotation3f;

//*****************************************************************************
/*! \class CQuaternionf xsi_quaternionf.h
	\brief Implementation of a float quaternion q=a+bi+cj+dk. This class is typically used for
	implementing custom ICE nodes.

	A quaternion is often noted q=(s,v) where s is a scalar and v is a 3D vector, or either
	noted q=(W,X,Y,Z), where W, X, Y and Z are scalar, and X, Y and Z are the components of
	vector v in previous notation.

	\sa CRotation3f
 */
//*****************************************************************************
class SICPPSDKDECL CQuaternionf
{
public:
	/*! Default constructor.
	Constructs the identity quaternion.
	\sa CQuaternionf::SetIdentity
	*/
	SICPPSDK_INLINE CQuaternionf();

	/*! Copy constructor.
	\param in_quaternion constant class object.
	 */
	SICPPSDK_INLINE CQuaternionf( const CQuaternionf& in_quaternion );

	/*! Default destructor. */
	~CQuaternionf() {};

	/*! Assignment operator.
	\param in_quaternion constant class object.
	\return This quaternion
	 */
	SICPPSDK_INLINE CQuaternionf & operator=( const CQuaternionf & in_quaternion);

	/*! Constructor.
	\param in_W W component
	\param in_X X component of the quaternion's vector
	\param in_Y Y component of the quaternion's vector
	\param in_Z Z component of the quaternion's vector
	*/
	SICPPSDK_INLINE CQuaternionf( const float in_W, const float in_X, const float in_Y, const float in_Z );

	/*! Constructor.
	\note The W component of the quaternion will be set to 1.0
	\param in_vct Vector containing the X, Y and Z values
	*/
	SICPPSDK_INLINE CQuaternionf( const CVector3f& in_vct );

	/*! Constructor.
	\param in_vct Vector containing the X, Y, Z and W values
	*/
	SICPPSDK_INLINE CQuaternionf( const CVector4f& in_vct );

	/*! Performs an exact comparison of two quaternions.
	\note Each parameter of both quaternions must be exactly the same fora match.
	\param in_Quat Quaternion to compare against
	\sa CQuaternionf::EpsilonEquals
	*/
	SICPPSDK_INLINE bool Equals( const CQuaternionf &in_Quat ) const;

	/*! Performs comparison between this quaternion and the \c in_quat1 quaternion within the specified epsilon value.
	\param in_quat Quaternion to compare against.
	\param in_fEpsilon Tolerance value (validity domain: <TT>[0, +INF[</TT>)
	\sa CQuaternionf::Equals
	*/
	SICPPSDK_INLINE bool EpsilonEquals( const CQuaternionf& in_quat, const float in_fEpsilon ) const;

	/*! Performs a comparison.
	\note Each parameter of both quaternions must be exactly the same for a match.
	\param in_Quat Quaternion to compare against
	\sa CQuaternionf::EpsilonEquals, CQuaternionf::Equals
	*/
	SICPPSDK_INLINE bool operator == ( const CQuaternionf &in_Quat ) const;

	/*! Less than operator. Performs a comparison with a specified CQuaternionf to determine if this CQuaternionf is
	less than the specified CQuaternionf. The comparison is arbitrary and not geometrically meaningful, it's only purpose is
	to make CQuaternionf compliant with stl for sorting operations.
	\param in_Quat CQuaternionf to compare.
	\return true if this CQuaternionf is less than the specified CQuaternionf, false otherwise.
	\since 7.5
	*/
	SICPPSDK_INLINE bool operator < ( const CQuaternionf& in_Quat ) const;

	/*! Multiplies this quaternion with another one in place.
	\param in_Quat Quaternion to multiply
	\return This quaternion
	\sa CQuaternionf::Mul, CQuaternionf::MulInPlace
	*/
	SICPPSDK_INLINE CQuaternionf& operator *= ( const CQuaternionf &in_Quat );

	/*! Multiplies this quaternion with another one in place.
	\param in_Quat Quaternion to multiply
	\return This quaternion
	\sa CQuaternionf::Mul
	*/
	SICPPSDK_INLINE CQuaternionf& Mul( const CQuaternionf &in_Quat );

	/*! Stores the result of the multiplication of two quaternions.
	\param in_Quat1 First quaternion
	\param in_Quat2 Second quaternion
	\return This quaternion
	*/
	SICPPSDK_INLINE CQuaternionf& Mul( const CQuaternionf &in_Quat1, const CQuaternionf &in_Quat2);

	/*! Performs the dot product between this quaternion and the one specified in \c in_quat1.
	\param in_quat1 Quaternion operand.
	\return This quaternion
	*/
	SICPPSDK_INLINE float Dot( const CQuaternionf& in_quat1 ) const;

	/*! Performs the spherical linear interpolation of two unit quaternions into this one for u between 0 and 1.
	\param in_quatStart Starting unitary quaternion.
	\param in_quatEnd Ending unitary quaternion.
	\param in_fU Interpolation factor (validity domain: <TT>[0.0, 1.0]</TT>)
	\return This quaternion.
	*/
	SICPPSDK_INLINE CQuaternionf& Slerp( const CQuaternionf& in_quatStart, const CQuaternionf& in_quatEnd, const float in_fU );

	/*! Subtracts a quaternion from the current quaternion in place.
	\param in_Quat Quaternion to subtract
	\return This quaternion
	\sa CQuaternionf::SubInPlace, CQuaternionf::Sub
	*/
	SICPPSDK_INLINE CQuaternionf& operator -= ( const CQuaternionf &in_Quat );

	/*! Subtracts a quaternion from the current quaternion in place.
	\param in_Quat Quaternion to subtract
	\return This quaternion
	\sa CQuaternionf::Sub
	*/
	SICPPSDK_INLINE CQuaternionf& SubInPlace( const CQuaternionf &in_Quat );

	/*! Stores the result of the subtraction of two quaternions.
	\param in_Quat1 First quaternion
	\param in_Quat2 Second quaternion
	\return This quaternion
	\sa CQuaternionf::SubInPlace
	*/
	SICPPSDK_INLINE CQuaternionf& Sub( const CQuaternionf &in_Quat1,  const CQuaternionf &in_Quat2);

	/*! Negates all the components of this quaternion.
	\return This quaternion
	\sa CQuaternionf::Negate
	*/
	SICPPSDK_INLINE CQuaternionf& NegateInPlace();

	/*! Stores the result of the negation of a given quaternion without changing it.
	\param in_Quat Quaternion to negate
	\return This quaternion
	\sa CQuaternionf::NegateInPlace
	*/
	SICPPSDK_INLINE CQuaternionf& Negate( const CQuaternionf &in_Quat);

	/*! Returns the squared length of this quaternion.
	\return The squared length
	\sa CQuaternionf::GetLength
	*/
	SICPPSDK_INLINE float GetSquaredLength() const;

	/*! Returns the length of this quaternion.
	\return Length of this quaternion
	\sa CQuaternionf::GetSquaredLength
	*/
	SICPPSDK_INLINE float GetLength() const;

	/*! Adds a quaternion to this quaternion.
	\param in_Quat Quaternion to add
	\sa CQuaternionf::AddInPlace, CQuaternionf::Add
	*/
	SICPPSDK_INLINE CQuaternionf& operator += ( const CQuaternionf &in_Quat);

	/*! Adds a quaternion to this quaternion.
	\param in_Quat Quaternion to add
	\sa CQuaternionf::Add
	*/
	SICPPSDK_INLINE CQuaternionf& AddInPlace( const CQuaternionf &in_Quat );

	/*! Stores the result of the addition of two quaternions.
	\param in_Quat1 First quaternion
	\param in_Quat2 Second quaternion
	\return This quaternion
	\sa CQuaternionf::AddInPlace
	*/
	SICPPSDK_INLINE CQuaternionf& Add( const CQuaternionf &in_Quat1,  const CQuaternionf &in_Quat2);

	/*! Conjugates this quaternion.
	\return This quaternion
	\sa CQuaternionf::ConjugateInPlace
	*/
	SICPPSDK_INLINE CQuaternionf& ConjugateInPlace();

	/*! Stores the conjugate of a quaternion without changing it.
	\param in_Quat Quaternion to conjugate.
	\return This quaternion
	\sa CQuaternionf::ConjugateInPlace
	*/
	SICPPSDK_INLINE CQuaternionf& Conjugate( const CQuaternionf &in_Quat);

	/*! Inverts this quaternion.
	\return This quaternion
	\sa CQuaternionf::Invert
	*/
	SICPPSDK_INLINE CQuaternionf& InvertInPlace();

	/*! Stores the invert of a quaternion without changing it.
	\param in_Quat Quaternion to invert
	\return This quaternion
	\sa CQuaternionf::Invert
	*/
	SICPPSDK_INLINE CQuaternionf& Invert( const CQuaternionf &in_Quat);

	/*! Sets this quaternion to identity quaternion.
	\return This quaternion
	*/
	SICPPSDK_INLINE CQuaternionf& SetIdentity();

	/*! Copies the content of a quaternion.
	\param in_Quat Quaternion to copy
	\return This quaternion
	*/
	SICPPSDK_INLINE CQuaternionf& Copy( const CQuaternionf &in_Quat );

	/*! Normalizes the quaternion in place.
	\return CStatus::OK if the normalization has been computed.
	*/
	SICPPSDK_INLINE CQuaternionf& NormalizeInPlace();

	/*! Returns the components of this quaternion.
	\retval out_W The current value of the W component
	\retval out_X The current value of the X component
	\retval out_Y The current value of the Y component
	\retval out_Z The current value of the Z component
	*/
	SICPPSDK_INLINE void Get( float &out_W, float &out_X, float &out_Y, float &out_Z ) const;

	/*! Returns the components of this quaternion.
	\return CVector3f that holds the values of the X, Y and Z components.
	*/
	SICPPSDK_INLINE CVector3f GetVector3() const;

	/*! Returns the components of this quaternion.
	\return CVector4f that holds the values of the X, Y, Z, W components.
	*/
	SICPPSDK_INLINE CVector4f GetVector4() const;

	/*! Returns the components of this quaternion.
	\param io_XYZWVector Vector that holds the values of the X, Y, Z and W components
	*/
	SICPPSDK_INLINE void Get( CVector4f &io_XYZWVector ) const;

	/*! Sets the quaternion's components.
	\param in_W New value for the W component
	\param in_X New value for the X component
	\param in_Y New value for the Y component
	\param in_Z New value for the Z component
	\return This quaternion
	*/
	SICPPSDK_INLINE CQuaternionf& Set( float in_W,  float in_X,  float in_Y,  float in_Z);

	/*! Sets the quaternion's components.
	\note The W value is left as is.
	\param in_XYZVector Vector that holds the new values for the X, Y and Z components
	\return This quaternion
	*/
	SICPPSDK_INLINE CQuaternionf& Set( const CVector3f &in_XYZVector );

	/*! Sets the quaternion's components.
	\param in_XYZWVector Vector that holds the new values for the X, Y and Z
		components.  The W component is set to 1.0.
	\return This quaternion
	*/
	SICPPSDK_INLINE CQuaternionf& Set( const CVector4f &in_XYZWVector );

	/*! Gets the value of a single component.
	\param in_nIndex 0-based index of the component to get.  This value	can be 0 (W), 1(X), 2(Y) or 3(Z).
	\return The requested value
	\return 0.0 if an invalid index was provided.
	\sa CQuaternionf::SetValue
	*/
	SICPPSDK_INLINE float GetValue( short in_nIndex ) const;

	/*! Sets the value of a single component.
	\note The quaternion is unchanged if the provided index is invalid
	\param in_nIndex 0-based index of the component to set.  This value	can be 0 (W), 1(X), 2(Y) or 3(Z).
	\param newVal new value
	\return This quaternion
	\sa CQuaternionf::SetValue
	*/
	SICPPSDK_INLINE CQuaternionf& SetValue( short in_nIndex, float newVal);

	/*! Returns the W component.
	\return The W component
	*/
	SICPPSDK_INLINE float GetW() const;

	/*! Sets the W component.
	\param newVal The new value for the component
	\return This quaternion
	*/
	SICPPSDK_INLINE CQuaternionf& PutW( float newVal);

	/*! Returns the Z component.
	\return The Z component
	*/
	SICPPSDK_INLINE float GetZ() const;

	/*! Sets the Z component.
	\param newVal The new value for the component
	\return This quaternion
	*/
	SICPPSDK_INLINE CQuaternionf& PutZ( float newVal);

	/*! Returns the Y component.
	\return The Y component
	*/
	SICPPSDK_INLINE float GetY() const;

	/*! Sets the Y component.
	\param newVal The new value for the component
	\return This quaternion
	*/
	SICPPSDK_INLINE CQuaternionf& PutY( float newVal);

	/*! Returns the X component.
	\return The X component
	*/
	SICPPSDK_INLINE float GetX() const;

	/*! Sets the X component.
	\param newVal The new value for the component
	\return This quaternion
	*/
	SICPPSDK_INLINE CQuaternionf& PutX( float newVal);

	/*! Inequality operator (tests the strict inequality of this quaternion
	with the quaternion in_quat).
	\param in_quat Operand quaternion.
	\return true if equal else false.
	\sa CQuaternionf::Equals
	 */
	SICPPSDK_INLINE bool operator !=(const CQuaternionf & in_quat ) const;

private:
	float m_W, m_X, m_Y, m_Z;
};

//inline functions
SICPPSDK_INLINE CQuaternionf::CQuaternionf()
{
	SetIdentity();
}

SICPPSDK_INLINE CQuaternionf::CQuaternionf( const CQuaternionf& in_quaternion)
{
	*this = in_quaternion;
}

SICPPSDK_INLINE CQuaternionf& CQuaternionf::operator=( const CQuaternionf & in_Quat )
{
	m_W = in_Quat.m_W;
	m_X = in_Quat.m_X;
	m_Y = in_Quat.m_Y;
	m_Z = in_Quat.m_Z;

	return *this;
}

SICPPSDK_INLINE CQuaternionf::CQuaternionf( const float in_W, const float in_X, const float in_Y, const float in_Z )
{
	Set( in_W, in_X, in_Y, in_Z );
}

SICPPSDK_INLINE CQuaternionf::CQuaternionf( const XSI::MATH::CVector3f& in_vct )
{
	Set( in_vct );
}

SICPPSDK_INLINE CQuaternionf::CQuaternionf( const XSI::MATH::CVector4f& in_vct )
{
	Set( in_vct );
}

SICPPSDK_INLINE bool CQuaternionf::Equals( const CQuaternionf &in_Quat ) const
{
	return (this == &in_Quat) ? true :
		(m_W == in_Quat.m_W &&
		m_X == in_Quat.m_X &&
		m_Y == in_Quat.m_Y &&
		m_Z == in_Quat.m_Z );
}

SICPPSDK_INLINE bool CQuaternionf::operator == ( const CQuaternionf &in_Quat ) const
{
	return Equals(in_Quat);
}

SICPPSDK_INLINE bool CQuaternionf::operator < ( const CQuaternionf& in_Quat) const
{
	if ( m_W != in_Quat.m_W ) return m_W < in_Quat.m_W;
	if ( m_Z != in_Quat.m_Z ) return m_Z < in_Quat.m_Z;
	if ( m_Y != in_Quat.m_Y ) return m_Y < in_Quat.m_Y;
	if ( m_X != in_Quat.m_X ) return m_X < in_Quat.m_X;
	return false;
}

SICPPSDK_INLINE bool CQuaternionf::operator != ( const CQuaternionf &in_Quat ) const
{
	return ! Equals( in_Quat );
}

SICPPSDK_INLINE CQuaternionf& CQuaternionf::operator *= ( const CQuaternionf &in_Quat )
{

	return Mul(*this, in_Quat);
}

SICPPSDK_INLINE CQuaternionf& CQuaternionf::Mul( const CQuaternionf &in_Quat )
{
	return Mul(*this, in_Quat);
}

SICPPSDK_INLINE CQuaternionf& CQuaternionf::Mul
(
	const CQuaternionf &in_Quat1,
	const CQuaternionf &in_Quat2
)
{
	float dW, dX, dY, dZ;

	dW = in_Quat1.m_W * in_Quat2.m_W - in_Quat1.m_X * in_Quat2.m_X -
		in_Quat1.m_Y * in_Quat2.m_Y - in_Quat1.m_Z * in_Quat2.m_Z ;

	dX = in_Quat1.m_W * in_Quat2.m_X + in_Quat2.m_W * in_Quat1.m_X +
		in_Quat1.m_Y * in_Quat2.m_Z - in_Quat2.m_Y * in_Quat1.m_Z ;

	dY = in_Quat1.m_W * in_Quat2.m_Y + in_Quat2.m_W * in_Quat1.m_Y -
		in_Quat1.m_X * in_Quat2.m_Z + in_Quat2.m_X * in_Quat1.m_Z ;

	dZ = in_Quat1.m_W * in_Quat2.m_Z + in_Quat2.m_W * in_Quat1.m_Z +
		in_Quat1.m_X * in_Quat2.m_Y - in_Quat2.m_X * in_Quat1.m_Y ;

	m_W = dW; m_X = dX; m_Y = dY; m_Z = dZ;

	return *this;
}

SICPPSDK_INLINE CQuaternionf& CQuaternionf::operator -= ( const CQuaternionf &in_Quat )
{
	return Sub(*this, in_Quat );
}

SICPPSDK_INLINE CQuaternionf& CQuaternionf::SubInPlace( const CQuaternionf &in_Quat )
{
	return Sub(*this, in_Quat );
}

SICPPSDK_INLINE CQuaternionf& CQuaternionf::Sub
(
	const CQuaternionf &in_Quat1,
	const CQuaternionf &in_Quat2
)
{
	m_W = in_Quat1.m_W - in_Quat2.m_W;
	m_X = in_Quat1.m_X - in_Quat2.m_X;
	m_Y = in_Quat1.m_Y - in_Quat2.m_Y;
	m_Z = in_Quat1.m_Z - in_Quat2.m_Z;

	return *this;
}

SICPPSDK_INLINE CQuaternionf& CQuaternionf::NegateInPlace()
{
   return Negate(*this);
}

SICPPSDK_INLINE CQuaternionf& CQuaternionf::Negate( const CQuaternionf &in_Quat)
{
   m_W = -(in_Quat.m_W);
   m_X = -(in_Quat.m_X);
   m_Y = -(in_Quat.m_Y);
   m_Z = -(in_Quat.m_Z);

   return( *this );
}

SICPPSDK_INLINE float CQuaternionf::GetSquaredLength() const
{
	return( m_W * m_W + m_X * m_X +	m_Y * m_Y + m_Z * m_Z );
}

SICPPSDK_INLINE float CQuaternionf::GetLength() const
{
	return( sqrt( GetSquaredLength() ) );
}

SICPPSDK_INLINE CQuaternionf& CQuaternionf::operator += ( const CQuaternionf &in_Quat)
{
	return Add( *this,  in_Quat );
}

SICPPSDK_INLINE CQuaternionf& CQuaternionf::AddInPlace( const CQuaternionf &in_Quat )
{
	return Add( *this,  in_Quat );
}

SICPPSDK_INLINE CQuaternionf& CQuaternionf::Add
(
	const CQuaternionf &in_Quat1,
	const CQuaternionf &in_Quat2
)
{
	m_W = in_Quat1.m_W + in_Quat2.m_W;
	m_X = in_Quat1.m_X + in_Quat2.m_X;
	m_Y = in_Quat1.m_Y + in_Quat2.m_Y;
	m_Z = in_Quat1.m_Z + in_Quat2.m_Z;
	return *this;
}

SICPPSDK_INLINE CQuaternionf& CQuaternionf::ConjugateInPlace()
{
	return Conjugate(*this);
}

SICPPSDK_INLINE CQuaternionf& CQuaternionf::Conjugate( const CQuaternionf &in_Quat)
{
	m_W = in_Quat.m_W;
	m_X = -in_Quat.m_X;
	m_Y = -in_Quat.m_Y;
	m_Z = -in_Quat.m_Z;

	return( *this );
}

SICPPSDK_INLINE CQuaternionf& CQuaternionf::InvertInPlace()
{
	return Invert(*this);
}

SICPPSDK_INLINE CQuaternionf& CQuaternionf::Invert( const CQuaternionf &in_Quat)
{
	return Conjugate(in_Quat);
}

SICPPSDK_INLINE CQuaternionf& CQuaternionf::SetIdentity()
{
	m_W = 1.0;
	m_X = m_Y = m_Z = 0.0;

	return( *this );
}

SICPPSDK_INLINE CQuaternionf&  CQuaternionf::Copy( const CQuaternionf &in_Quat )
{
	return *this = in_Quat;
}

SICPPSDK_INLINE CVector3f CQuaternionf::GetVector3( ) const
{
	return CVector3f( m_X, m_Y, m_Z);
}

SICPPSDK_INLINE CVector4f CQuaternionf::GetVector4( ) const
{
	return CVector4f( m_X, m_Y, m_Z, m_W);
}

SICPPSDK_INLINE void CQuaternionf::Get
(
	float &io_W,
	float &io_X,
	float &io_Y,
	float &io_Z
) const
{
	io_W = m_W;
	io_X = m_X;
	io_Y = m_Y;
	io_Z = m_Z;
}

SICPPSDK_INLINE void CQuaternionf::Get( CVector4f &io_XYZWVector ) const
{
	io_XYZWVector.Set( m_X, m_Y, m_Z, m_W);
}

SICPPSDK_INLINE CQuaternionf& CQuaternionf::Set
(
	float in_W,
	float in_X,
	float in_Y,
	float in_Z
)
{
	m_W = in_W;
	m_X = in_X;
	m_Y = in_Y;
	m_Z = in_Z;

	return *this;
}

SICPPSDK_INLINE CQuaternionf& CQuaternionf::Set( const CVector3f &in_XYZVector )
{
	m_W = 1.0;
	m_X = in_XYZVector.GetX();
	m_Y = in_XYZVector.GetY();
	m_Z = in_XYZVector.GetZ();

	return *this;
}

SICPPSDK_INLINE CQuaternionf& CQuaternionf::Set( const CVector4f &in_XYZWVector )
{
	m_W = in_XYZWVector.GetW();
	m_X = in_XYZWVector.GetX();
	m_Y = in_XYZWVector.GetY();
	m_Z = in_XYZWVector.GetZ();

	return *this;
}

SICPPSDK_INLINE float CQuaternionf::GetValue( short in_nIndex ) const
{
	assert(in_nIndex >= 0 && in_nIndex < 4);

	switch (in_nIndex)
	{
		case 0: return m_W;
		case 1: return m_X;
		case 2: return m_Y;
		case 3: return m_Z;
	}

	return 0.0; // invalid index, return 0.0
}

SICPPSDK_INLINE CQuaternionf& CQuaternionf::SetValue( short in_nIndex,  float newVal)
{
	assert(in_nIndex >= 0 && in_nIndex < 4);

	switch (in_nIndex)
	{
		case 0:  m_W = newVal; break;
		case 1:  m_X = newVal; break;
		case 2:  m_Y = newVal; break;
		case 3:  m_Z = newVal; break;
		// note: do nothing when invalid index is provided
	}

	return *this;
}

SICPPSDK_INLINE float CQuaternionf::GetW() const
{
	return m_W;
}

SICPPSDK_INLINE CQuaternionf& CQuaternionf::PutW( float newVal)
{
	m_W = newVal;

	return *this;
}

SICPPSDK_INLINE float CQuaternionf::GetZ() const
{
	return m_Z;
}

SICPPSDK_INLINE CQuaternionf& CQuaternionf::PutZ( float newVal)
{
	m_Z = newVal;
	return *this;
}

SICPPSDK_INLINE float CQuaternionf::GetY() const
{
	return m_Y;
}

SICPPSDK_INLINE CQuaternionf& CQuaternionf::PutY( float newVal)
{
	m_Y = newVal;
	return *this;
}


SICPPSDK_INLINE float CQuaternionf::GetX() const
{
	return m_X;
}

SICPPSDK_INLINE CQuaternionf& CQuaternionf::PutX( float newVal)
{
	m_X = newVal;
	return *this;
}

SICPPSDK_INLINE CQuaternionf& CQuaternionf::NormalizeInPlace()
{
   float rLen = GetSquaredLength();

   if( fabs( rLen - 1.0f ) >= PicoEPS )
   {
      if( rLen < PicoEPS )
      {
         m_X = m_Y = m_Z = 0.0;
         m_W = 1.0;
      }
      else
      {
         rLen = 1.0f / sqrt( rLen );
         m_W *= rLen;
         m_X *= rLen;
         m_Y *= rLen;
         m_Z *= rLen;

		 LimitValue( m_W, -1.0, 1.0 );
      }
   }
   else
   {
		LimitValue( m_W, -1.0, 1.0 );
   }

   return( *this );
}

SICPPSDK_INLINE CQuaternionf& CQuaternionf::Slerp
(
	const CQuaternionf& in_quatStart,
	const CQuaternionf& in_quatEnd,
	const float			in_fU
)
{
   float fDot, fScale1, fScale2;
   bool bNegate = false;

   fDot = in_quatStart.Dot( in_quatEnd );
   if ( fDot < 0.0 )
   {
      fDot = -fDot;
      bNegate = true;
   }

   if( fDot >= ( 1.0f - MicroEPS ) )
   {
      fScale1 = 1.0f - in_fU;
      fScale2 = in_fU;
   }
   else
   {
      float fAngle, fFactor;

      LimitValue( fDot, -1.0, 1.0 );
      fAngle = acos( fDot );
      fFactor = 1.0f / sin( fAngle );

      fScale1 = sin( (1.0f - in_fU) * fAngle ) * fFactor;
      fScale2 = sin( in_fU * fAngle ) * fFactor;
   }

   if( bNegate == true )
      fScale2 = -fScale2;

   m_W = fScale1 * in_quatStart.m_W + fScale2 * in_quatEnd.m_W;
   m_X = fScale1 * in_quatStart.m_X + fScale2 * in_quatEnd.m_X;
   m_Y = fScale1 * in_quatStart.m_Y + fScale2 * in_quatEnd.m_Y;
   m_Z = fScale1 * in_quatStart.m_Z + fScale2 * in_quatEnd.m_Z;

   return( *this );
}

SICPPSDK_INLINE float CQuaternionf::Dot( const CQuaternionf& in_quat ) const
{
   return( GetW() * in_quat.GetW() +
           GetX() * in_quat.GetX() +
           GetY() * in_quat.GetY() +
           GetZ() * in_quat.GetZ() );
}

SICPPSDK_INLINE bool CQuaternionf::EpsilonEquals( const CQuaternionf& in_quat, const float in_fEpsilon ) const
{
   return( fabs( GetW() - in_quat.GetW() ) < in_fEpsilon &&
           fabs( GetX() - in_quat.GetX() ) < in_fEpsilon &&
           fabs( GetY() - in_quat.GetY() ) < in_fEpsilon &&
           fabs( GetZ() - in_quat.GetZ() ) < in_fEpsilon );
}

};
};

#endif // __XSIQUATERNIONF_H__
