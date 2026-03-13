//*****************************************************************************
/*!
   \file xsi_vector3.h
   \brief CVector3 and CVector3Array class declarations.

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIVECTOR3_H__
#define __XSIVECTOR3_H__

#include "sicppsdk.h"
#include "xsi_status.h"
#include "xsi_matrix3.h"
#include "xsi_matrix4.h"
#include <math.h>

// uncomment this if you want the debug version of your plugin to catch uninitialized CVector3
// #define _DEBUG_NonInitialized_CVector3

#ifdef _DEBUG_NonInitialized_CVector3
#define MAGIC_DEBUG_VALUE ((double)0x5555555555555555)
#define XSI_DEBUG_VECTOR3 SelfDebug();
#else
#define XSI_DEBUG_VECTOR3
#endif


namespace XSI {

namespace MATH {

class CTransformation;
class CMatrix3;
class CMatrix4;

//*****************************************************************************
/*! \class CVector3 xsi_vector3.h
	\brief A 3-element vector that is represented by double precision floating point x,y,z coordinates.

	In this API vectors are considered as row vectors as described in [Foley, J., and A. van Dam,
	Fundamentals of Interactive Computer Graphics, Addison-Wesley, Reading, MA, 1982]. This is
	important when you multiply a CVector3 by a CMatrix3 or a CMatrix4.

	\sa CMatrix3, CMatrix4, CTransformation

  	\eg
	\code
		using namespace XSI;
		using namespace MATH;
		Application app;
		Model root = app.GetActiveSceneRoot();

		X3DObject myCube;
		root.AddGeometry( L"Cube", L"MeshSurface",L"",myCube );

		KinematicState  globalKinematicState = myCube.GetKinematics().GetGlobal();
		globalKinematicState.PutParameterValue(L"posy", 4.0);
		globalKinematicState.PutParameterValue(L"posx", 2.0);

		X3DObject myCube2;
		myCube.AddGeometry( L"Cube", L"MeshSurface",L"",myCube2);

		globalKinematicState = myCube2.GetKinematics().GetGlobal();
		globalKinematicState.PutParameterValue(L"posz",3.0);
		globalKinematicState.PutParameterValue(L"rotx",45.0);

		CTransformation localTransformation =
								myCube.GetKinematics().GetLocal().GetTransform();
		CTransformation globalTransformation = globalKinematicState.GetTransform();

		CVector3 translation(localTransformation.GetTranslation());

		app.LogMessage(L"The translation of the cube relative to its parent: x " +
						CValue(translation.GetX()).GetAsText() +
						L" y " +
						CValue(translation.GetY()).GetAsText() +
						L" z " +
						CValue(translation.GetZ()).GetAsText());

		MapObjectPoseToWorldSpace(	globalTransformation, localTransformation);

		translation = localTransformation.GetTranslation();

		app.LogMessage(L"The translation of the cube relative to the origin of the universe: x " +
					  CValue(translation.GetX()).GetAsText() +
					  L" y " + CValue(translation.GetY()).GetAsText() +
					  L" z " + CValue(translation.GetZ()).GetAsText());
	\endcode
 */
//*****************************************************************************
class SICPPSDKDECL CVector3
{
public:
	/*! Default constructor. */
	SICPPSDK_INLINE CVector3();

	/*! Constructor.
	\param in_dX Value of the x component
	\param in_dY Value of the y component
	\param in_dZ Value of the z component
	*/
	SICPPSDK_INLINE CVector3(double in_dX, double in_dY, double in_dZ);

	/*! Copy constructor.
	\param in_vector3 constant class object.
	*/
	SICPPSDK_INLINE CVector3( const CVector3& in_vector3);

	/*! Default destructor. */
	SICPPSDK_INLINE ~CVector3();

	/*! Assignment operator.
	\param in_vector3 constant class object.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3 & operator=( const CVector3 & in_vector3 );

	/*! Equality operator tests the strict equality of this CVector3 with the specified vector3.
	\param in_vector3 Operand vector.
	\return true if equal else false.
	\sa CVector3::Equals
	*/
	SICPPSDK_INLINE bool operator ==(const CVector3 & in_vector3 )const;

	/*! Inequality operator tests the strict inequality of this CVector3 with the specified vector3.
	\param in_vector3 Operand vector.
	\return true if equal else false.
	\sa CVector3::Equals
	*/
	SICPPSDK_INLINE bool operator !=(const CVector3 & in_vector3 )const;

	/*! Negates this vector (this = - this).
	\return A reference to this vector.
	\sa CVector3::NegateInPlace
	*/
	SICPPSDK_INLINE CVector3& operator ~();

	/*! Adds the input vector to this one (this = this + in_vector3)
	\param in_vector3 Operand vector..
	\return A reference to this vector.
	\sa CVector3::AddInPlace
	*/
	SICPPSDK_INLINE CVector3& operator +=(const CVector3& in_vector3);

	/*! Subtracts the input vector (in_vector3) from this one (this = this - in_vector3).
	\param in_vector3 Operand vector.
	\return A reference to this vector.
	\sa CVector3::SubInPlace
	*/
	SICPPSDK_INLINE CVector3& operator -=(const CVector3 & in_vector3);


	/*! Right-multiplies this vector by the matrix m in place (this = this . m ).
	\param in_matrix3 Operand matrix.
	\return A reference to this vector.
	\sa CVector3::MulByMatrix3InPlace
	*/
	SICPPSDK_INLINE CVector3& operator *=(const CMatrix3& in_matrix3);

	/*! Right-multiplies this vector by the matrix m in place (this = this . m ).
	\param in_matrix4 Operand matrix.
	\return A reference to this vector.
	\sa CVector3::MulByMatrix4InPlace
	*/
	SICPPSDK_INLINE CVector3& operator *=(const CMatrix4& in_matrix4);

	/*! Right-multiplies this vector by the transformation t in place (this = this . t).
	\param in_transformation transformation operand.
	\return A reference to this vector.
	\sa CVector3::MulByTransformationInPlace
	*/
	SICPPSDK_INLINE CVector3& operator *=(const CTransformation& in_transformation);

	/*! Scales this vector by the input scalar (alpha) (this = alpha * this).
	\param in_dAlpha  Scalar multiplicator.
	\return A reference to this vector.
	\sa CVector3::ScaleInPlace
	*/
	SICPPSDK_INLINE CVector3& operator *=(const double& in_dAlpha);

	/*! Read-only accessors to the X,Y,Z components.
	\param in_sIndex  0,1,2 for X,Y and Z values.
	\return The value of the specified component. If the index supplied is out of range the function returns DBL_MAX.
	\sa CVector3::GetX(), CVector3::GetY(), CVector3::GetZ()
	*/
	SICPPSDK_INLINE double operator[](const short& in_sIndex);

	/*! Right-multiplies this vector by the matrix m in place (this = this . m ).
	\param in_matrix3 Operand matrix.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3& MulByMatrix3InPlace(const CMatrix3& in_matrix3);

	/*! Right-multiplies the vector v by the matrix m and store the result in this vector (this = v . m ).
	\param in_vector3 Operand vector
	\param in_matrix3 Operand matrix.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3& MulByMatrix3
	(
		const CVector3& in_vector3,
		const CMatrix3& in_matrix3
	);

	/*! Right-multiplies this vector by the matrix m in place (this = this . m ).
	\param in_matrix4 Operand matrix.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3& MulByMatrix4InPlace(const CMatrix4& in_matrix4);

	/*! Right-multiplies the vector v by the matrix m and store the result in this vector (this = v . m ).
	\param in_vector3 Operand vector
	\param in_matrix4 Operand matrix.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3& MulByMatrix4
	(
		const CVector3& in_vector3,
		const CMatrix4& in_matrix4
	);

	/*! Right-multiplies this vector by the transformation t in place (this = this . t).
	\param in_transformation transformation operand.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3& MulByTransformationInPlace
	(
		const CTransformation& in_transformation
	);

	/*! Right-multiplies the vector v by the transformation t and stores the result in this vector (this = v . t ).
	\param in_vector3 transformation operand.
	\param in_transformation transformation operand.
	\return A reference to this vector.
	*/
	CVector3& MulByTransformation
	(
		const CVector3&			in_vector3,
		const CTransformation&	in_transformation
	);

	/*! Sets this vector to a null vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3& PutNull();

	/*! Returns the index of the maximum component of this vector.
	\return Index of the maximum component of this vector.
	*/
	SICPPSDK_INLINE short GetMaxComponentIndex()const;

	/*! Returns the maximum component value of this vector.
	\return Maximum component value of this vector.
	*/
	SICPPSDK_INLINE double GetMaxComponent()const;

	/*! Returns the index of the minimum component of this vector.
	\return Index of the minimum component of this vector.
	*/
	SICPPSDK_INLINE short GetMinComponentIndex()const;

	/*! Returns the minimum component value of this vector.
	\return Minimum component value of this vector.
	*/
	SICPPSDK_INLINE double GetMinComponent()const;

	/*! Returns the length of this vector.
	\return Length of this vector.
	*/
	SICPPSDK_INLINE double GetLength()const;

	/*! Returns the squared length of this vector.
	\return Squared length of this vector.
	*/
	SICPPSDK_INLINE double GetLengthSquared()const;

	/*! Normalizes this vector in place.
	\return CStatus::OK if the normalization has been computed,
	*/
	CStatus NormalizeInPlace();

	/*! Sets the value of this vector to the normalization of inputed vector.
	\param in_vector3 vector operand.
	\return CStatus::OK if the normalization has been computed.
	*/
	CStatus Normalize(const CVector3& in_vector3);

	/*! Returns the dot product of this vector and the inputed vector.
	\param in_vector3 vector operand.
	\return Dot product of this vector and vector in_vector3.
	*/
	SICPPSDK_INLINE double Dot(const CVector3& in_vector3)const;


	/*! Sets this vector to the vector cross product of vectors A and B.
	\param in_vector3A vector operand.
	\param in_vector3B vector operand.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3& Cross(const CVector3& in_vector3A, const CVector3& in_vector3B);

	/*! Returns the angle (in radians) between this vector and the inputed vector.
	\param in_vector3 vector operand.
	\return Angle (in radians) between this vector and the inputed vector.
	*/
	double GetAngle(const CVector3& in_vector3 )const;

	/*! Linearly interpolates between vectors A and B and places the result into this vector:
	this = (1-alpha)*A + alpha*B.
	\param in_vector3A vector operand.
	\param in_vector3B vector operand.
	\param in_dAlpha Scalar interpolator \n
	\b Possible \b Values: [0.0, 1.0] Domain of validity
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3& LinearlyInterpolate
	(
		const CVector3& in_vector3A,
		const CVector3& in_vector3B,
		double in_dAlpha
	);

	/*! Sets each component of this vector3 to its absolute value.
	\return A reference to this vector.
	*/
	CVector3& AbsoluteInPlace();

	/*! Sets each component of the specified MATH::CVector3 to its absolute value and places the
	modified values into this vector.
	\param in_vector3 Vector to convert to absolute
	\return A reference to this vector.
	*/
	CVector3& Absolute(const CVector3& in_vector3);

	/*! Clamps this vector3's components to the range [MinValue, MaxValue].
	\param in_dMinValue Lower bound of the clamping domain.
	\param in_dMaxValue Higher bound of the clamping domain.
	\return A reference to this vector.
	*/
	CVector3& ClampInPlace(double in_dMinValue, double in_dMaxValue);

	/*! Clamps the specified vector3's components to the range [MinValue, MaxValue] and places the
	values into this vector3.
	\param in_dMinValue Lower bound of the clamping domain.
	\param in_dMaxValue Higher bound of the clamping domain.
	\param in_vector3 Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3& Clamp
	(
		double			in_dMinValue,
		double			in_dMaxValue,
		const CVector3& in_vector3
	);

	/*! Tests the equality of this vector3 with the specified vector3, with a tolerance of Epsilon.
	\param in_vector3 Operand vector.
	\param in_dEpsilon Error margin \n
	\b Possible \b Values: [0, +INF[ should be a positive value
	\return true if equal else false.
	*/
	SICPPSDK_INLINE bool EpsilonEquals
	(
		const CVector3& in_vector3,
		double in_dEpsilon
	)const;

	/*! Tests the strict equality of this vector3 with the specified vector3.
	\param in_vector3 Operand vector.
	\return true if equal else false.
	*/
	SICPPSDK_INLINE bool Equals(const CVector3& in_vector3)const;


	/*! Sets the value of this vector to the scalar multiplication of itself by s and then adds
	vector3 v. (this = s*this + v)
	\param in_dS  Scalar multiplicator.
	\param in_vector3 Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3& ScaleAddInPlace(double in_dS,const CVector3& in_vector3);

	/*! Sets the value of this vector3 to the scalar multiplication of vector3 A by s and then
	adds vector3 B. (this = s*v1 + v2).
	\param in_dS  Scalar multiplicator.
	\param in_vector3A Operand vector.
	\param in_vector3B Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3& ScaleAdd
	(
		double			in_dS,
		const CVector3& in_vector3A,
		const CVector3&	in_vector3B
	);

	/*! Scales this vector by the input scalar (alpha) (this = alpha * this).
	\param in_dAlpha  Scalar multiplicator.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3& ScaleInPlace(double in_dAlpha);

	/*! Scales the input vector (v) by (alpha) store the result into this one (this = alpha * v).
	\param in_dAlpha  Scalar multiplicator.
	\param in_vector3 Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3& Scale(double in_dAlpha, const CVector3& in_vector3);

	/*! Negates this vector (this = - this).
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3& NegateInPlace();

	/*! Negates the input vector (v) store the result into this one (this = - v).
	\param in_vector3 Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3& Negate(const CVector3& in_vector3);

	/*! Subtracts the input vector3 (v) from this one (this = this - v).
	\param in_vector3 Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3& SubInPlace(const CVector3&in_vector3);

	/*! Subtracts the input vector3 (\c in_vector3B) from the input vector3 (\c in_vector3A)
	and stores the result in this one (<tt>this = A - B</tt>).
	\param in_vector3A Operand vector.
	\param in_vector3B Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3& Sub(const CVector3& in_vector3A, const CVector3& in_vector3B);

	/*! Adds the input vector to this one (this = this + in_vector3).
	\param in_vector3 Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3& AddInPlace(const CVector3& in_vector3);

	/*! Adds both input vectors and stores the result in this one. (this = A + B)
	\param in_vector3A Operand vector.
	\param in_vector3B Operand vector.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3& Add(const CVector3& in_vector3A,const CVector3& in_vector3B);

	/*! Returns the X, Y and Z values of the vector.
	\param io_dX X value to get in the vector.
	\param io_dY Y value to get in the vector.
	\param io_dZ Z value to get in the vector.
	*/
	void Get(double& io_dX, double& io_dY, double& io_dZ)const;

	/*! Sets the X, Y and Z values of the vector.
	\param in_dX X value to set in the vector.
	\param in_dY Y value to set in the vector.
	\param in_dZ Z value to set in the vector.
	\return A reference to the vector.
	*/
	SICPPSDK_INLINE CVector3& Set(double in_dX, double in_dY, double in_dZ);

	/*! Returns the Z value of this vector.
	\return Z value of this vector.
	*/
	SICPPSDK_INLINE double GetZ()const;

	/*! Sets the Z value of this vector.
	\param in_dZ z value.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3& PutZ(double in_dZ);

	/*! Returns the Y value of this vector.
	\return Y value of this vector.
	*/
	SICPPSDK_INLINE double GetY()const;

	/*! Sets the Y value of this vector.
	\param in_dY y value.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3& PutY(double in_dY);

	/*! Returns the X value of this vector.
	\return X value of this vector.
	*/
	SICPPSDK_INLINE double GetX()const;

	/*! Sets the X value of this vector.
	\param in_dX x value.
	\return A reference to this vector.
	*/
	SICPPSDK_INLINE CVector3& PutX(double in_dX);

#ifdef _DEBUG_NonInitialized_CVector3
	void DoDebugInit()
	{
		m_dX = MAGIC_DEBUG_VALUE;  // 64 bits of alternating 010101010101...
		m_dY = MAGIC_DEBUG_VALUE;  // 64 bits of alternating 010101010101...
		m_dZ = MAGIC_DEBUG_VALUE;  // 64 bits of alternating 010101010101...
	}


	void SelfDebug() const
	{
		assert( m_dX != MAGIC_DEBUG_VALUE && m_dY != MAGIC_DEBUG_VALUE && m_dZ != MAGIC_DEBUG_VALUE );
	}
#endif

private:
	double m_dX,m_dY,m_dZ;
};

//inline functions
SICPPSDK_INLINE CVector3::CVector3()
{
#ifdef _DEBUG_NonInitialized_CVector3
	DoDebugInit(); // This method sets the debug values
#else
	m_dX = 0;
	m_dY = 0;
	m_dZ = 0;
#endif
}

SICPPSDK_INLINE CVector3::CVector3( const CVector3& in_vct )
{
	in_vct.Get(m_dX,m_dY,m_dZ);
}

SICPPSDK_INLINE CVector3::CVector3
(
 double in_dX, double in_dY, double in_dZ
):m_dX(in_dX),m_dY(in_dY),m_dZ(in_dZ)
{}

SICPPSDK_INLINE CVector3::~CVector3()
{}

SICPPSDK_INLINE CVector3& CVector3::operator=( const CVector3 & in_vct )
{
	in_vct.Get(m_dX,m_dY,m_dZ);
	return (*this);
}

SICPPSDK_INLINE bool CVector3::operator ==(const CVector3 & in_vector3 )const
{
	return Equals(in_vector3);
}


SICPPSDK_INLINE bool CVector3::operator !=(const CVector3 & in_vector3 )const
{
	return ! Equals(in_vector3);
}

SICPPSDK_INLINE CVector3& CVector3::operator ~()
{
	return NegateInPlace();
}

SICPPSDK_INLINE CVector3& CVector3::operator +=(const CVector3& in_vector3)
{
	return AddInPlace(in_vector3);
}

SICPPSDK_INLINE CVector3& CVector3::operator -=(const CVector3& in_vector3)
{
	return SubInPlace(in_vector3);
}

SICPPSDK_INLINE CVector3& CVector3::operator *=(const CMatrix3& in_matrix3)
{
	return MulByMatrix3InPlace(in_matrix3);
}

SICPPSDK_INLINE CVector3& CVector3::operator *=(const CMatrix4& in_matrix4)
{
	return MulByMatrix4InPlace(in_matrix4);
}

SICPPSDK_INLINE CVector3& CVector3::operator *=(const CTransformation& in_transformation)
{
	return MulByTransformationInPlace(in_transformation);
}

SICPPSDK_INLINE CVector3& CVector3::operator *=(const double& in_dAlpha)
{
	return ScaleInPlace(in_dAlpha);
}

SICPPSDK_INLINE double CVector3::operator[](const short& in_sIndex)
{
	XSI_DEBUG_VECTOR3;
	assert(in_sIndex >= 0 && in_sIndex < 3);
	switch(in_sIndex)
	{
	case 0:
		return m_dX;
		break;
	case 1:
		return m_dY;
		break;
	case 2:
		return m_dZ;
		break;
	}
	return DBL_MAX;
}

SICPPSDK_INLINE CVector3& CVector3::MulByMatrix3InPlace
(
	const CMatrix3& in_matrix3
)
{
	XSI_DEBUG_VECTOR3;
	return MulByMatrix3((*this),in_matrix3);
}

SICPPSDK_INLINE CVector3& CVector3::MulByMatrix3
(
	const CVector3& in_vector3,
	const CMatrix3& in_matrix3
)
{
	double l_dX, l_dY,l_dZ;
	l_dX = in_vector3.GetX() * in_matrix3.GetValue(0,0) +
		   in_vector3.GetY() * in_matrix3.GetValue(1,0) +
		   in_vector3.GetZ() * in_matrix3.GetValue(2,0);
	l_dY = in_vector3.GetX() * in_matrix3.GetValue(0,1) +
		   in_vector3.GetY() * in_matrix3.GetValue(1,1) +
		   in_vector3.GetZ() * in_matrix3.GetValue(2,1);
	l_dZ = in_vector3.GetX() * in_matrix3.GetValue(0,2) +
		   in_vector3.GetY() * in_matrix3.GetValue(1,2) +
		   in_vector3.GetZ() * in_matrix3.GetValue(2,2);

	return Set(l_dX,l_dY,l_dZ);
}

SICPPSDK_INLINE CVector3& CVector3::MulByMatrix4InPlace
(
	const CMatrix4& in_matrix4
)
{
	XSI_DEBUG_VECTOR3;
	return MulByMatrix4((*this),in_matrix4);
}


SICPPSDK_INLINE CVector3& CVector3::MulByMatrix4
(
	const CVector3& in_vector3,
	const CMatrix4& in_matrix4
)
{
	double l_dX, l_dY, l_dZ, l_dW;

	l_dX =	in_vector3.GetX() * in_matrix4.GetValue( 0, 0 ) +
			in_vector3.GetY() * in_matrix4.GetValue( 1, 0 ) +
			in_vector3.GetZ() * in_matrix4.GetValue( 2, 0 ) +
			in_matrix4.GetValue( 3, 0 );
	l_dY =	in_vector3.GetX() * in_matrix4.GetValue( 0, 1 ) +
			in_vector3.GetY() * in_matrix4.GetValue( 1, 1 ) +
			in_vector3.GetZ() * in_matrix4.GetValue( 2, 1 ) +
			in_matrix4.GetValue( 3, 1 );
	l_dZ =	in_vector3.GetX() * in_matrix4.GetValue( 0, 2 ) +
			in_vector3.GetY() * in_matrix4.GetValue( 1, 2 ) +
			in_vector3.GetZ() * in_matrix4.GetValue( 2, 2 ) +
			in_matrix4.GetValue( 3, 2 );
	l_dW =	in_vector3.GetX() * in_matrix4.GetValue( 0, 3 ) +
			in_vector3.GetY() * in_matrix4.GetValue( 1, 3 ) +
			in_vector3.GetZ() * in_matrix4.GetValue( 2, 3 ) +
			in_matrix4.GetValue( 3, 3 );

	return Set(l_dX/l_dW, l_dY/l_dW, l_dZ/l_dW);
}


SICPPSDK_INLINE CVector3& CVector3::MulByTransformationInPlace
(
	const CTransformation& in_crTrans
)
{
	XSI_DEBUG_VECTOR3;
	return MulByTransformation((*this), in_crTrans);;
}


SICPPSDK_INLINE CVector3& CVector3::PutNull()
{
	m_dX = m_dY = m_dZ = 0.0;
	return (*this);
}

SICPPSDK_INLINE short CVector3::GetMaxComponentIndex()const
{
	XSI_DEBUG_VECTOR3;
	if( m_dX > m_dY )
	{
		return (short)(( m_dX > m_dZ ) ? 0 : 2);
	}
	else
	{
		return (short)(( m_dY > m_dZ ) ? 1 : 2);
	}
}

SICPPSDK_INLINE double CVector3::GetMaxComponent()const
{
	XSI_DEBUG_VECTOR3;
	if( m_dX > m_dY )
	{
		return ( m_dX > m_dZ ) ? m_dX : m_dZ;
	}
	else
	{
		return ( m_dY > m_dZ ) ? m_dY : m_dZ;
	}
}

SICPPSDK_INLINE short CVector3::GetMinComponentIndex()const
{
	XSI_DEBUG_VECTOR3;
	if( m_dX < m_dY )
	{
		return (short)(( m_dX < m_dZ ) ? 0 : 2);
	}
	else
	{
		return (short)(( m_dY < m_dZ ) ? 1 : 2);
	}
}

SICPPSDK_INLINE double CVector3::GetMinComponent()const
{
	XSI_DEBUG_VECTOR3;
	if( m_dX < m_dY )
	{
		return ( m_dX < m_dZ ) ? m_dX : m_dZ;
	}
	else
	{
		return ( m_dY < m_dZ ) ? m_dY : m_dZ;
	}
}

SICPPSDK_INLINE double CVector3::GetLength()const
{
	XSI_DEBUG_VECTOR3;
	return sqrt( GetLengthSquared() );
}

SICPPSDK_INLINE double CVector3::GetLengthSquared()const
{
	XSI_DEBUG_VECTOR3;
	return(m_dX*m_dX + m_dY*m_dY + m_dZ*m_dZ );
}

SICPPSDK_INLINE double	CVector3::Dot(const CVector3& io_vec3)const
{
	XSI_DEBUG_VECTOR3;
	return ( m_dX*io_vec3.GetX() + m_dY*io_vec3.GetY() + m_dZ*io_vec3.GetZ() );
}

SICPPSDK_INLINE CVector3& CVector3::Cross
(
	const CVector3& in_vec3A,
	const CVector3& in_vec3B
)
{
	double dX, dY, dZ;

	dX =	in_vec3A.GetY() * in_vec3B.GetZ() -
			in_vec3A.GetZ() * in_vec3B.GetY();
	dY =   -in_vec3A.GetX() * in_vec3B.GetZ() +
			in_vec3A.GetZ() * in_vec3B.GetX();
	dZ =	in_vec3A.GetX() * in_vec3B.GetY() -
			in_vec3A.GetY() * in_vec3B.GetX();

   return( Set( dX, dY, dZ ) );
}

SICPPSDK_INLINE CVector3& CVector3::LinearlyInterpolate
(
 const CVector3&	in_vec3A,
 const CVector3&	in_vec3B,
 const double		in_dAlpha
)
{
	m_dX = (1 - in_dAlpha) * in_vec3A.GetX() + in_dAlpha * in_vec3B.GetX();
	m_dY = (1 - in_dAlpha) * in_vec3A.GetY() + in_dAlpha * in_vec3B.GetY();
	m_dZ = (1 - in_dAlpha) * in_vec3A.GetZ() + in_dAlpha * in_vec3B.GetZ();

	return (*this);
}

SICPPSDK_INLINE bool CVector3::EpsilonEquals
(
	const CVector3& in_cVec3,
	double in_dEpsilon
)const
{
	XSI_DEBUG_VECTOR3;
	return (this == &in_cVec3) ? true :
		(fabs( m_dX - in_cVec3.GetX() ) < ::fabs(in_dEpsilon) &&
		   fabs( m_dY - in_cVec3.GetY() ) < ::fabs(in_dEpsilon) &&
		   fabs( m_dZ - in_cVec3.GetZ() ) < ::fabs(in_dEpsilon) );
}


SICPPSDK_INLINE bool CVector3::Equals(const CVector3& in_vec3)const
{
	XSI_DEBUG_VECTOR3;
	return (this == &in_vec3) ? true :
		( ( m_dX == in_vec3.GetX() ) &&
		  ( m_dY == in_vec3.GetY() ) &&
		  ( m_dZ == in_vec3.GetZ() ) );
}

SICPPSDK_INLINE CVector3& CVector3::ScaleAddInPlace
(
	double in_dScalingFactor,
	const CVector3& in_vec3
)
{
	ScaleInPlace(in_dScalingFactor);
	return AddInPlace(in_vec3);
}


SICPPSDK_INLINE CVector3& CVector3::ScaleAdd
(
	const double in_dScalingFactor,
	const CVector3& in_vec3A,
	const CVector3& in_vec3B
)
{
	Scale(in_dScalingFactor, in_vec3A);
	return AddInPlace(in_vec3B);
}

SICPPSDK_INLINE CVector3& CVector3::ScaleInPlace(double in_dScalingFactor)
{
	XSI_DEBUG_VECTOR3;
	m_dX *= in_dScalingFactor;
	m_dY *= in_dScalingFactor;
	m_dZ *= in_dScalingFactor;
	return (*this);
}

SICPPSDK_INLINE CVector3& CVector3::Scale
(
 double in_dScalingFactor,
 const CVector3& in_vec3
)
{
	m_dX = in_vec3.GetX() * in_dScalingFactor;
	m_dY = in_vec3.GetY() * in_dScalingFactor;
	m_dZ = in_vec3.GetZ() * in_dScalingFactor;
	return (*this);
}

SICPPSDK_INLINE CVector3& CVector3::NegateInPlace()
{
	XSI_DEBUG_VECTOR3;
	m_dX = -m_dX;
	m_dY = -m_dY;
	m_dZ = -m_dZ;
	return (*this);
}

SICPPSDK_INLINE CVector3& CVector3::Negate(const CVector3& in_vec3 )
{
	m_dX = -in_vec3.GetX();
	m_dY = -in_vec3.GetY();
	m_dZ = -in_vec3.GetZ();
	return (*this);
}

SICPPSDK_INLINE CVector3& CVector3::SubInPlace(const CVector3& in_vec3)
{
	XSI_DEBUG_VECTOR3;
	m_dX -= in_vec3.GetX();
	m_dY -= in_vec3.GetY();
	m_dZ -= in_vec3.GetZ();
	return (*this);
}

SICPPSDK_INLINE CVector3& CVector3::Sub
(
	const CVector3& in_vec3A,
	const CVector3& in_vec3B
)
{
	m_dX = in_vec3A.GetX() - in_vec3B.GetX();
	m_dY = in_vec3A.GetY() - in_vec3B.GetY();
	m_dZ = in_vec3A.GetZ() - in_vec3B.GetZ();
	return (*this);
}

SICPPSDK_INLINE CVector3& CVector3::AddInPlace(const CVector3& in_vec3)
{
	XSI_DEBUG_VECTOR3;
	m_dX += in_vec3.GetX();
	m_dY += in_vec3.GetY();
	m_dZ += in_vec3.GetZ();
	return (*this);
}

SICPPSDK_INLINE CVector3& CVector3::Add
(
	const CVector3& in_vec3A,
	const CVector3& in_vec3B
)
{
	m_dX = in_vec3A.GetX() + in_vec3B.GetX();
	m_dY = in_vec3A.GetY() + in_vec3B.GetY();
	m_dZ = in_vec3A.GetZ() + in_vec3B.GetZ();
	return (*this);
}


SICPPSDK_INLINE void CVector3::Get(double& io_rdX, double& io_rdY, double& io_rdZ)const
{
	XSI_DEBUG_VECTOR3;
	io_rdX = m_dX;
	io_rdY = m_dY;
	io_rdZ = m_dZ;
}

SICPPSDK_INLINE CVector3& CVector3::Set(double in_dX, double in_dY, double in_dZ)
{
	m_dX = in_dX;
	m_dY = in_dY;
	m_dZ = in_dZ;
	return (*this);
}

SICPPSDK_INLINE double CVector3::GetZ()const
{
	XSI_DEBUG_VECTOR3;
	return m_dZ;
}

SICPPSDK_INLINE CVector3&	CVector3::PutZ(double in_dZ)
{
	m_dZ = in_dZ;
	return (*this);
}

SICPPSDK_INLINE double CVector3::GetY()const
{
	XSI_DEBUG_VECTOR3;
	return m_dY;
}

SICPPSDK_INLINE CVector3& CVector3::PutY(double in_dY)
{
	m_dY = in_dY;
	return (*this);
}

SICPPSDK_INLINE double CVector3::GetX()const
{
	XSI_DEBUG_VECTOR3;
	return m_dX;
}

SICPPSDK_INLINE CVector3& CVector3::PutX(double in_dX)
{
	m_dX = in_dX;
	return (*this);
}

//*************************************************************************
/*! \class CVector3Array xsi_vector3.h
	\brief The CVector3Array is an uni-dimensional array of CVector3.

	The array is zero-based, which means that the first item index is 0 and the larger index is one
	less that the number of elements contained in the array.

	\sa MATH::CVector3, CFacetRefArray::GetNormalArray, CPointRefArray::GetPositionArray,
		CPointRefArray::PutPositionArray, CPointRefArray::GetNormalArray, CPolygonFaceRefArray::GetNormalArray,
		PolygonMesh::Get, PolygonMesh::Set, CSegmentRefArray::GetNormalArray, Triangle::GetPositionArray,
		Triangle::GetPolygonNodeNormalArray, CTriangleRefArray::GetPositionArray,
		CTriangleRefArray::GetPolygonNodeNormalArray, CTriangleVertexRefArray::GetPositionArray,
		CTriangleVertexRefArray::GetNormalArray, X3DObject::AddPolygonMesh
*/
//*************************************************************************
class SICPPSDKDECL CVector3Array
{
public:
	/*! Constructs a CVector3Array and optionally initializes the array to a known size.
	\param in_size Size of array, defaults to 0.
	*/
	CVector3Array( LONG in_size=0);

	/*! Constructs a CVector3Array object from another CVector3Array object.
	\param in_Array constant CVector3Array object.
	*/
	CVector3Array(const CVector3Array& in_Array);

	/*! Default destructor. */
	~CVector3Array();

	/*! Assignment operator.
	\param in_array constant class object.
	\return A reference to this array.
	*/
	CVector3Array& operator=( const CVector3Array& in_array );

	/*! Returns the number of items in this CVector3Array
	\return The number of items in the array.
	*/
	LONG GetCount() const;

	/*! Adds a LONG at the end of this array's.
	\param in_item New item to be added at the end of the array.
	\return CStatus::OK success
	*/
	CStatus Add( const CVector3& in_item );

	/*! Erases all elements contained in the array.
	\return CStatus::OK success
	*/
	CStatus Clear();

	/*! Reallocates memory for the array, preserves its contents if the new size is larger than existing size.
	\param in_size New size of the array.
	\return CStatus::OK success
	\return CStatus::InvalidArgument in_size < 0
	*/
	CStatus Resize( LONG in_size);

	/*! Accessor to elements at a given index. This function can only be
	called by constant objects, the returned value is read-only.
	\param in_index index in this zero based array.  The index must be greater or equal to zero
		and smaller than the number of element in the array, otherwise the results are unpredictable.
	\return A read-only reference to the indexed item.
	*/
	const CVector3& operator[]( LONG in_index ) const;

	/*! Accessor to elements at a given index.
	\param in_index index in this zero based array.  The index must be greater or equal to zero
		and smaller than the number of element in the array, otherwise the results are unpredictable.
	\return A reference to the indexed item.
	*/
	CVector3& operator[]( LONG in_index );

	/*! Equality operator.
	\param in_array CVector3Array to compare with.
	\return true if in_array contains the same number of elements as this array and if all members
		of in_array are equal to the corresponding one contained in this array.
	*/
	bool operator==(const CVector3Array& in_array) const;

	/*! Inequality operator.
	\param in_array
	\return true if one member of in_array is different from the corresponding members in this
		array or if the arrays are not of the same size.
	*/
	bool operator!=(const CVector3Array& in_array) const;


private:

	void* m_ptr;
};

};
};

#endif // __XSIVECTOR3_H__
