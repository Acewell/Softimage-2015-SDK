//*****************************************************************************
/*!
   \file xsi_quaternion.h
   \brief CQuaternion class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************
#ifndef __XSIQUATERNION_H__
#define __XSIQUATERNION_H__

#include "sicppsdk.h"
#include "xsi_rotation.h"
#include "xsi_vector3.h"
#include "xsi_vector4.h"

namespace XSI {

namespace MATH {

class CVector3;
class CVector4;

//*****************************************************************************
/*! \class CQuaternion xsi_quaternion.h
	\brief Implementation of a quaternion q=a+bi+cj+dk.

	A quaternion is often noted q=(s,v) where s is a scalar and v is a 3D vector, or either
	noted q=(W,X,Y,Z), where W, X, Y and Z are scalar, and X, Y and Z are the components of
	vector v in previous notation.

	You can set a quaternion using various rotation representation with the help of the
	CRotation class.

	\sa CRotation, CTransformation

	\eg Using CRotation to construct a CQuaternion from various rotation representations.
	\code
		using namespace XSI;
		using namespace MATH;

		CVector3 eulerAngles( PI, PI * 2.0, PI / 2.0 );
		CRotation eulerAnglesRot( eulerAngles, CRotation::siXYZ );
		CQuaternion quat( eulerAnglesRot );

		CVector3 axis( 1.0, 2.0, 3.0 );
		CRotation axisAngleRot( axis, PI );
		quat = axisAngleRot;

		CMatrix3 identityMatrix;
		quat.SetFromRotation( CRotation(identityMatrix) );
		\endcode

		\b Example: Performing linear extrapolation using quaternions
		\code
		// Quaternion linear extrapolation example
		using namespace XSI;
		using namespace MATH;

		Application app;
		Model root = app.GetActiveSceneRoot();

		// define start and end point for rotation
		CQuaternion startQuat;
		CRotation rotationEnd( CVector3( PI, 0.0, 0.0 ) );
		CQuaternion endQuat( rotationEnd );

		// number of interpolation to perform + interpolation increment
		const size_t nbInterpolations = 10;
		const double interpolationIncrement = 1.0 / nbInterpolations;

		CQuaternion interpolatedQuaternion;
		CRotation currentRotation;
		X3DObject currentObject;
		CVector3 rotationAngles;

		// Create cubes rotated using interpolated values
		for ( double i = 0.0; i < 1.0; i += interpolationIncrement )
		{
			// interpolate values
			interpolatedQuaternion.Slerp( startQuat, endQuat, i );

			// create cube
			root.AddGeometry( L"Cube", L"MeshSurface", L"", currentObject );

			// apply interpolated value in X
			currentRotation = interpolatedQuaternion;
			rotationAngles = currentRotation.GetXYZAngles();
			KinematicState globalKS = currentObject.GetKinematics().GetGlobal();
			globalKS.PutParameterValue( L"rotx",
				(double)RadiansToDegrees(rotationAngles.GetX()));
		}
	\endcode
 */
//*****************************************************************************
class SICPPSDKDECL CQuaternion
{
public:
	/*! Default constructor.
	Constructs the identity quaternion.
	\sa CQuaternion::SetIdentity
	*/
	SICPPSDK_INLINE CQuaternion();

	/*! Copy constructor.
	\param in_quaternion constant class object.
	 */
	SICPPSDK_INLINE CQuaternion( const CQuaternion& in_quaternion);

	/*! Default destructor. */
	~CQuaternion() {};

	/*! Assignment operator.
	\param in_quaternion constant class object.
	\return This quaternion
	 */
	SICPPSDK_INLINE CQuaternion & operator=( const CQuaternion & in_quaternion);

	/*! Constructor.
	\param in_dW W component
	\param in_dX X component of the quaternion's vector
	\param in_dY Y component of the quaternion's vector
	\param in_dZ Z component of the quaternion's vector
	*/
	SICPPSDK_INLINE CQuaternion( const double in_dW, const double in_dX,
               const double in_dY, const double in_dZ );

	/*! Constructor.
	\note The W component of the quaternion will be set to 1.0
	\param in_vct Vector containing the X, Y and Z values
	*/
	SICPPSDK_INLINE CQuaternion( const CVector3& in_vct );

	/*! Constructor.
	\param in_vct Vector containing the X, Y, Z and W values
	*/
	SICPPSDK_INLINE CQuaternion( const CVector4& in_vct );

	/*! Constructor (from a rotation).
	\param in_Rot Rotation to construct from
	*/
	SICPPSDK_INLINE CQuaternion( const CRotation& in_Rot );

	/*! Sets the quaternion from a rotation
	\param in_Rot Rotation to set from
	\return This quaternion
	*/
	CQuaternion& operator = ( const CRotation &in_Rot );

	/*! Sets the quaternion from a rotation
	\param in_Rot Rotation to set from
	\return This quaternion
	*/
	CQuaternion& SetFromRotation( const CRotation &in_Rot );

	/*! Returns a rotation that represents the current quaternion
	\return CRotation
	*/
	CRotation GetRotation() const;

	/*! Normalizes the quaternion
	*/
	CQuaternion& Normalize();

	/*! Tests the equality of this quaternion against in_Quat, with a
	tolerance of in_dEpsilon.

	\param in_Quat Quaternion to compare against
	\param in_dEpsilon Tolerance.  Quaternions are considered equal if each
		parameter pair have a difference lower than in_dEpsilon.
	\return true Quaternions are approximately equal
	\return false Quarternions are not equal
	*/
	bool EpsilonEquals( const CQuaternion &in_Quat, double in_dEpsilon ) const;

	/*! Performs an exact comparison of two quaternions.
	\note Each parameter of both quaternions must be exactly the same fora match.
	\param in_Quat Quaternion to compare against
	\sa CQuaternion::EpsilonEquals
	*/
	SICPPSDK_INLINE bool Equals( const CQuaternion &in_Quat ) const;

	/*! Performs a comparison.
	\note Each parameter of both quaternions must be exactly the same for a match.
	\param in_Quat Quaternion to compare against
	\sa CQuaternion::EpsilonEquals, CQuaternion::Equals
	*/
	SICPPSDK_INLINE bool operator == ( const CQuaternion &in_Quat ) const;

	/*!	Performs spherical linear interpolation of two unit quaternions whithin
	this quaternion.
	\param in_Quat1 First quaternion
	\param in_Quat2 Second quaternion
	\param in_dU Interpolation factor within [0.0 .. 1.0].
	\return This quaternion
	*/
	CQuaternion& Slerp( const CQuaternion &in_Quat1, const CQuaternion &in_Quat2, double in_dU);

	/*! Multiplies this quaternion with another one in place.
	\param in_Quat Quaternion to multiply
	\return This quaternion
	\sa CQuaternion::Mul, CQuaternion::MulInPlace
	*/
	SICPPSDK_INLINE CQuaternion& operator *= ( const CQuaternion &in_Quat );

	/*! Multiplies this quaternion with another one in place.
	\param in_Quat Quaternion to multiply
	\return This quaternion
	\sa CQuaternion::Mul
	*/
	SICPPSDK_INLINE CQuaternion& MulInPlace( const CQuaternion &in_Quat );

	/*! Stores the result of the multiplication of two quaternions.
	\param in_Quat1 First quaternion
	\param in_Quat2 Second quaternion
	\return This quaternion
	*/
	SICPPSDK_INLINE CQuaternion& Mul( const CQuaternion &in_Quat1, const CQuaternion &in_Quat2);

	/*! Subtracts a quaternion from the current quaternion in place.
	\param in_Quat Quaternion to subtract
	\return This quaternion
	\sa CQuaternion::SubInPlace, CQuaternion::Sub
	*/
	SICPPSDK_INLINE CQuaternion& operator -= ( const CQuaternion &in_Quat );

	/*! Subtracts a quaternion from the current quaternion in place.
	\param in_Quat Quaternion to subtract
	\return This quaternion
	\sa CQuaternion::Sub
	*/
	SICPPSDK_INLINE CQuaternion& SubInPlace( const CQuaternion &in_Quat );

	/*! Stores the result of the subtraction of two quaternions.
	\param in_Quat1 First quaternion
	\param in_Quat2 Second quaternion
	\return This quaternion
	\sa CQuaternion::SubInPlace
	*/
	SICPPSDK_INLINE CQuaternion& Sub( const CQuaternion &in_Quat1,  const CQuaternion &in_Quat2);

	/*! Negates all the components of this quaternion.
	\return This quaternion
	\sa CQuaternion::Negate
	*/
	SICPPSDK_INLINE CQuaternion& NegateInPlace();

	/*! Stores the result of the negation of a given quaternion without changing it.
	\param in_Quat Quaternion to negate
	\return This quaternion
	\sa CQuaternion::NegateInPlace
	*/
	SICPPSDK_INLINE CQuaternion& Negate( const CQuaternion &in_Quat);

	/*! Returns the squared length of this quaternion.
	\return The squared length
	\sa CQuaternion::GetLength
	*/
	double GetLengthSquared() const;

	/*! Returns the length of this quaternion.
	\return Length of this quaternion
	\sa CQuaternion::GetLengthSquared
	*/
	double GetLength() const;

	/*! Adds a quaternion to this quaternion.
	\param in_Quat Quaternion to add
	\sa CQuaternion::AddInPlace, CQuaternion::Add
	*/
	SICPPSDK_INLINE CQuaternion& operator += ( const CQuaternion &in_Quat);

	/*! Adds a quaternion to this quaternion.
	\param in_Quat Quaternion to add
	\sa CQuaternion::Add
	*/
	SICPPSDK_INLINE CQuaternion& AddInPlace( const CQuaternion &in_Quat );

	/*! Stores the result of the addition of two quaternions.
	\param in_Quat1 First quaternion
	\param in_Quat2 Second quaternion
	\return This quaternion
	\sa CQuaternion::AddInPlace
	*/
	SICPPSDK_INLINE CQuaternion& Add( const CQuaternion &in_Quat1,  const CQuaternion &in_Quat2);

	/*! Conjugates this quaternion.
	\return This quaternion
	\sa CQuaternion::ConjugateInPlace
	*/
	SICPPSDK_INLINE CQuaternion& ConjugateInPlace();

	/*! Stores the conjugate of a quaternion without changing it.
	\param in_Quat Quaternion to conjugate.
	\return This quaternion
	\sa CQuaternion::ConjugateInPlace
	*/
	SICPPSDK_INLINE CQuaternion& Conjugate( const CQuaternion &in_Quat);

	/*! Inverts this quaternion.
	\return This quaternion
	\sa CQuaternion::Invert
	*/
	SICPPSDK_INLINE CQuaternion& InvertInPlace();

	/*! Stores the invert of a quaternion without changing it.
	\param in_Quat Quaternion to invert
	\return This quaternion
	\sa CQuaternion::Invert
	*/
	SICPPSDK_INLINE CQuaternion& Invert( const CQuaternion &in_Quat);

	/*! Sets this quaternion to identity quaternion.
	\return This quaternion
	*/
	SICPPSDK_INLINE CQuaternion& SetIdentity();

	/*! Copies the content of a quaternion.
	\param in_Quat Quaternion to copy
	\return This quaternion
	*/
	SICPPSDK_INLINE CQuaternion&  Copy( const CQuaternion &in_Quat );

	/*! Returns the components of this quaternion.
	\retval out_dW The current value of the W component
	\retval out_dX The current value of the X component
	\retval out_dY The current value of the Y component
	\retval out_dZ The current value of the Z component
	*/
	SICPPSDK_INLINE void Get( double &out_dW, double &out_dX, double &out_dY, double &out_dZ ) const;

	/*! Returns the components of this quaternion.
	\return Vector that holds the values of the X, Y and Z components
	*/
	CVector3 Get() const;

	/*! Returns the components of this quaternion.
	\param io_XYZWVector Vector that holds the values of the X, Y, Z and W components
	*/
	SICPPSDK_INLINE void Get( CVector4 &io_XYZWVector ) const;

	/*! Sets the quaternion's components.
	\param in_dW New value for the W component
	\param in_dX New value for the X component
	\param in_dY New value for the Y component
	\param in_dZ New value for the Z component
	\return This quaternion
	*/
	SICPPSDK_INLINE CQuaternion& Set( double in_dW,  double in_dX,  double in_dY,  double in_dZ);

	/*! Sets the quaternion's components.
	\note The W value is left as is.
	\param in_XYZVector Vector that holds the new values for the X, Y and Z components
	\return This quaternion
	*/
	SICPPSDK_INLINE CQuaternion& Set( const CVector3 &in_XYZVector );

	/*! Sets the quaternion's components.
	\param in_XYZWVector Vector that holds the new values for the X, Y and Z
		components.  The W component is set to 1.0.
	\return This quaternion
	*/
	SICPPSDK_INLINE CQuaternion& Set( const CVector4 &in_XYZWVector );

	/*! Gets the value of a single component.
	\param in_nIndex 0-based index of the component to get.  This value
		can be 0 (W), 1(X), 2(Y) or 3(Z).
	\return The requested value
	\return 0.0 if an invalid index was provided.
	\sa CQuaternion::PutValue
	*/
	SICPPSDK_INLINE double GetValue( short in_nIndex ) const;

	/*! Sets the value of a single component.
	\note The quaternion is unchanged if the provided index is invalid
	\param in_nIndex 0-based index of the component to set.  This value
		can be 0 (W), 1(X), 2(Y) or 3(Z).
	\param newVal new value
	\return This quaternion
	\sa CQuaternion::SetValue
	*/
	SICPPSDK_INLINE CQuaternion& PutValue( short in_nIndex,  double newVal);

	/*! Returns the W component.
	\return The W component
	*/
	SICPPSDK_INLINE double GetW() const;

	/*! Sets the W component.
	\param newVal The new value for the component
	\return This quaternion
	*/
	SICPPSDK_INLINE CQuaternion& PutW( double newVal);

	/*! Returns the Z component.
	\return The Z component
	*/
	SICPPSDK_INLINE double GetZ() const;

	/*! Sets the Z component.
	\param newVal The new value for the component
	\return This quaternion
	*/
	SICPPSDK_INLINE CQuaternion& PutZ( double newVal);

	/*! Returns the Y component.
	\return The Y component
	*/
	SICPPSDK_INLINE double GetY() const;

	/*! Sets the Y component.
	\param newVal The new value for the component
	\return This quaternion
	*/
	SICPPSDK_INLINE CQuaternion& PutY( double newVal);

	/*! Returns the X component.
	\return The X component
	*/
	SICPPSDK_INLINE double GetX() const;

	/*! Sets the X component.
	\param newVal The new value for the component
	\return This quaternion
	*/
	SICPPSDK_INLINE CQuaternion& PutX( double newVal);

	/*! Sets the quaternion using X,Y,Z Euler angles (in radians).
	\param x The Euler X value in radians
	\param y The Euler Y value in radians
	\param z The Euler Z value in radians
	\return This quaternion
	*/
	CQuaternion& SetFromXYZAnglesValues( double x, double y, double z );

	/*! Returns the X,Y,Z Euler angles (in radians) for this quaternion.
	\retval x The Euler X value in radians
	\retval y The Euler Y value in radians
	\retval z The Euler Z value in radians
	*/
	void GetXYZAnglesValues( double& x, double& y, double& z )const;

	/*! Inequality operator (tests the strict inequality of this quaternion
	with the quaternion in_quat).
	\param in_quat Operand quaternion.
	\return true if equal else false.
	\sa CQuaternion::Equals
	 */
	SICPPSDK_INLINE bool operator !=(const CQuaternion & in_quat ) const;

private:
	double m_dX, m_dY, m_dZ, m_dW;
};

//inline functions
SICPPSDK_INLINE CQuaternion::CQuaternion()
{
	SetIdentity();
}

SICPPSDK_INLINE CQuaternion::CQuaternion( const CQuaternion& in_quaternion)
{
	*this = in_quaternion;
}


SICPPSDK_INLINE CQuaternion& CQuaternion::operator=( const CQuaternion & in_Quat )
{
	m_dW = in_Quat.m_dW;
	m_dX = in_Quat.m_dX;
	m_dY = in_Quat.m_dY;
	m_dZ = in_Quat.m_dZ;

	return *this;
}

SICPPSDK_INLINE CQuaternion::CQuaternion( const double in_dW, const double in_dX,
           const double in_dY, const double in_dZ )
{
	Set( in_dW, in_dX, in_dY, in_dZ );
}

SICPPSDK_INLINE CQuaternion::CQuaternion( const XSI::MATH::CVector3& in_vct )
{
	Set( in_vct );
}

SICPPSDK_INLINE CQuaternion::CQuaternion( const XSI::MATH::CVector4& in_vct )
{
	Set( in_vct );
}

SICPPSDK_INLINE bool CQuaternion::Equals( const CQuaternion &in_Quat ) const
{
	return (this == &in_Quat) ? true :
		(m_dW == in_Quat.m_dW &&
		m_dX == in_Quat.m_dX &&
		m_dY == in_Quat.m_dY &&
		m_dZ == in_Quat.m_dZ );
}

SICPPSDK_INLINE bool CQuaternion::operator == ( const CQuaternion &in_Quat ) const
{
	return Equals(in_Quat);
}

SICPPSDK_INLINE bool CQuaternion::operator != ( const CQuaternion &in_Quat ) const
{
	return ! Equals( in_Quat );
}

SICPPSDK_INLINE CQuaternion& CQuaternion::operator *= ( const CQuaternion &in_Quat )
{

	return Mul(*this, in_Quat);
}

SICPPSDK_INLINE CQuaternion& CQuaternion::MulInPlace( const CQuaternion &in_Quat )
{
	return Mul(*this, in_Quat);
}

SICPPSDK_INLINE CQuaternion& CQuaternion::Mul
( 
	const CQuaternion &in_Quat1, 
	const CQuaternion &in_Quat2
)
{
	double dW, dX, dY, dZ;

	dW = in_Quat1.m_dW * in_Quat2.m_dW - in_Quat1.m_dX * in_Quat2.m_dX -
		in_Quat1.m_dY * in_Quat2.m_dY - in_Quat1.m_dZ * in_Quat2.m_dZ ;

	dX = in_Quat1.m_dW * in_Quat2.m_dX + in_Quat2.m_dW * in_Quat1.m_dX +
		in_Quat1.m_dY * in_Quat2.m_dZ - in_Quat2.m_dY * in_Quat1.m_dZ ;

	dY = in_Quat1.m_dW * in_Quat2.m_dY + in_Quat2.m_dW * in_Quat1.m_dY -
		in_Quat1.m_dX * in_Quat2.m_dZ + in_Quat2.m_dX * in_Quat1.m_dZ ;

	dZ = in_Quat1.m_dW * in_Quat2.m_dZ + in_Quat2.m_dW * in_Quat1.m_dZ +
		in_Quat1.m_dX * in_Quat2.m_dY - in_Quat2.m_dX * in_Quat1.m_dY ;

	m_dW = dW; m_dX = dX; m_dY = dY; m_dZ = dZ;

	return *this;
}

SICPPSDK_INLINE CQuaternion& CQuaternion::operator -= ( const CQuaternion &in_Quat )
{
	return Sub(*this, in_Quat );
}

SICPPSDK_INLINE CQuaternion& CQuaternion::SubInPlace( const CQuaternion &in_Quat )
{
	return Sub(*this, in_Quat );
}

SICPPSDK_INLINE CQuaternion& CQuaternion::Sub
( 
	const CQuaternion &in_Quat1,  
	const CQuaternion &in_Quat2
)
{
	m_dW = in_Quat1.m_dW - in_Quat2.m_dW;
	m_dX = in_Quat1.m_dX - in_Quat2.m_dX;
	m_dY = in_Quat1.m_dY - in_Quat2.m_dY;
	m_dZ = in_Quat1.m_dZ - in_Quat2.m_dZ;

	return *this;
}

SICPPSDK_INLINE CQuaternion& CQuaternion::NegateInPlace()
{
   return Negate(*this);
}

SICPPSDK_INLINE CQuaternion& CQuaternion::Negate( const CQuaternion &in_Quat)
{
   m_dW = -(in_Quat.m_dW);
   m_dX = -(in_Quat.m_dX);
   m_dY = -(in_Quat.m_dY);
   m_dZ = -(in_Quat.m_dZ);

   return( *this );
}

SICPPSDK_INLINE double CQuaternion::GetLengthSquared() const
{
	return( m_dW * m_dW + m_dX * m_dX +	m_dY * m_dY + m_dZ * m_dZ );
}

SICPPSDK_INLINE CQuaternion& CQuaternion::operator += ( const CQuaternion &in_Quat)
{
	return Add( *this,  in_Quat );
}

SICPPSDK_INLINE CQuaternion& CQuaternion::AddInPlace( const CQuaternion &in_Quat )
{
	return Add( *this,  in_Quat );
}

SICPPSDK_INLINE CQuaternion& CQuaternion::Add
( 
	const CQuaternion &in_Quat1,  
	const CQuaternion &in_Quat2
)
{
	m_dW = in_Quat1.m_dW + in_Quat2.m_dW;
	m_dX = in_Quat1.m_dX + in_Quat2.m_dX;
	m_dY = in_Quat1.m_dY + in_Quat2.m_dY;
	m_dZ = in_Quat1.m_dZ + in_Quat2.m_dZ;
	return *this;
}

SICPPSDK_INLINE CQuaternion& CQuaternion::ConjugateInPlace()
{
	return Conjugate(*this);
}

SICPPSDK_INLINE CQuaternion& CQuaternion::Conjugate( const CQuaternion &in_Quat)
{
	m_dW = in_Quat.m_dW;
	m_dX = -in_Quat.m_dX;
	m_dY = -in_Quat.m_dY;
	m_dZ = -in_Quat.m_dZ;

	return( *this );
}

SICPPSDK_INLINE CQuaternion& CQuaternion::InvertInPlace()
{
	return Invert(*this);
}

SICPPSDK_INLINE CQuaternion& CQuaternion::Invert( const CQuaternion &in_Quat)
{
	return Conjugate(in_Quat);
}

SICPPSDK_INLINE CQuaternion& CQuaternion::SetIdentity()
{
	m_dW = 1.0;
	m_dX = m_dY = m_dZ = 0.0;

	return( *this );
}

SICPPSDK_INLINE CQuaternion&  CQuaternion::Copy( const CQuaternion &in_Quat )
{
	return *this = in_Quat;
}

SICPPSDK_INLINE void CQuaternion::Get
( 
	double &io_dW, 
	double &io_dX, 
	double &io_dY, 
	double &io_dZ 
) const
{
	io_dW = m_dW;
	io_dX = m_dX;
	io_dY = m_dY;
	io_dZ = m_dZ;
}

SICPPSDK_INLINE void CQuaternion::Get( CVector4 &io_XYZWVector ) const
{
	io_XYZWVector.Set( m_dX, m_dY, m_dZ, m_dW);
}


SICPPSDK_INLINE CQuaternion& CQuaternion::Set
( 
	double in_dW,  
	double in_dX,  
	double in_dY,  
	double in_dZ
)
{
	m_dW = in_dW;
	m_dX = in_dX;
	m_dY = in_dY;
	m_dZ = in_dZ;

	return *this;
}

SICPPSDK_INLINE CQuaternion& CQuaternion::Set( const CVector3 &in_XYZVector )
{
	m_dW = 1.0;
	m_dX = in_XYZVector.GetX();
	m_dY = in_XYZVector.GetY();
	m_dZ = in_XYZVector.GetZ();

	return *this;
}

SICPPSDK_INLINE CQuaternion& CQuaternion::Set( const CVector4 &in_XYZWVector )
{
	m_dW = in_XYZWVector.GetW();
	m_dX = in_XYZWVector.GetX();
	m_dY = in_XYZWVector.GetY();
	m_dZ = in_XYZWVector.GetZ();

	return *this;
}

SICPPSDK_INLINE double CQuaternion::GetValue( short in_nIndex ) const
{
	assert(in_nIndex >= 0 && in_nIndex < 4);

	switch (in_nIndex)
	{
		case 0: return m_dW;
		case 1: return m_dX;
		case 2: return m_dY;
		case 3: return m_dZ;
	}

	return 0.0; // invalid index, return 0.0
}

SICPPSDK_INLINE CQuaternion& CQuaternion::PutValue( short in_nIndex,  double newVal)
{
	assert(in_nIndex >= 0 && in_nIndex < 4);

	switch (in_nIndex)
	{
		case 0:  m_dW = newVal; break;
		case 1:  m_dX = newVal; break;
		case 2:  m_dY = newVal; break;
		case 3:  m_dZ = newVal; break;
		// note: do nothing when invalid index is provided
	}

	return *this;
}

SICPPSDK_INLINE double CQuaternion::GetW() const
{
	return m_dW;
}

SICPPSDK_INLINE CQuaternion& CQuaternion::PutW( double newVal)
{
	m_dW = newVal;

	return *this;
}

SICPPSDK_INLINE double CQuaternion::GetZ() const
{
	return m_dZ;
}

SICPPSDK_INLINE CQuaternion& CQuaternion::PutZ( double newVal)
{
	m_dZ = newVal;
	return *this;
}

SICPPSDK_INLINE double CQuaternion::GetY() const
{
	return m_dY;
}

SICPPSDK_INLINE CQuaternion& CQuaternion::PutY( double newVal)
{
	m_dY = newVal;
	return *this;
}


SICPPSDK_INLINE double CQuaternion::GetX() const
{
	return m_dX;
}

SICPPSDK_INLINE CQuaternion& CQuaternion::PutX( double newVal)
{
	m_dX = newVal;
	return *this;
}

SICPPSDK_INLINE CQuaternion::CQuaternion( const CRotation& in_Rot )
{
	*this = in_Rot;
}


};
};

#endif // __XSIQUATERNION_H__
