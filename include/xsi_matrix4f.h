//*****************************************************************************
/*!
   \file xsi_matrix4f.h
   \brief Matrix4f class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIMATRIX4F_H__
#define __XSIMATRIX4F_H__

#include "sicppsdk.h"
#include "xsi_math.h"

namespace XSI {
namespace MATH {

//*****************************************************************************
/*! \class CMatrix4f xsi_matrix4f.h
	\brief A class to represent a single precision floating point 4 by 4 matrix. This class is typically used for
	implementing custom ICE nodes.
 */
//*****************************************************************************
class SICPPSDKDECL CMatrix4f
{
public:

	/*! Default constructor. */
	SICPPSDK_INLINE CMatrix4f();

	/*! Constructor.
	\param in_f00 Value to set to this matrix[0,0].
	\param in_f01 Value to set to this matrix[0,1].
	\param in_f02 Value to set to this matrix[0,2].
	\param in_f03 Value to set to this matrix[0,3].
	\param in_f10 Value to set to this matrix[1,0].
	\param in_f11 Value to set to this matrix[1,1].
	\param in_f12 Value to set to this matrix[1,2].
	\param in_f13 Value to set to this matrix[1,3].
	\param in_f20 Value to set to this matrix[2,0].
	\param in_f21 Value to set to this matrix[2,1].
	\param in_f22 Value to set to this matrix[2,2].
	\param in_f23 Value to set to this matrix[2,3].
	\param in_f30 Value to set to this matrix[3,0].
	\param in_f31 Value to set to this matrix[3,1].
	\param in_f32 Value to set to this matrix[3,2].
	\param in_f33 Value to set to this matrix[3,3].
	 */
	SICPPSDK_INLINE CMatrix4f(float in_f00, float in_f01, float in_f02, float in_f03,
			 float in_f10, float in_f11, float in_f12, float in_f13,
			 float in_f20, float in_f21, float in_f22, float in_f23,
			 float in_f30, float in_f31, float in_f32, float in_f33);

	/*! Copy constructor.
	\param in_matrix4 constant class object.
	 */
	SICPPSDK_INLINE CMatrix4f( const CMatrix4f& in_matrix4 );

	/*! Default destructor. */
	SICPPSDK_INLINE ~CMatrix4f();

	/*! Assignment operator.
	\param in_matrix4 constant class object.
	\return A reference to this object.
	 */
	SICPPSDK_INLINE CMatrix4f & operator=( const CMatrix4f & in_matrix4 );

	/*! Right-multiplies this CMatrix4f object by the specified matrix and stores the result into this matrix
	(this = this * in_matrix4).
	\param in_matrix4 matrix to be multiplied with.
	\return A reference to this object.
	 */
	SICPPSDK_INLINE CMatrix4f & operator*=(const CMatrix4f & in_matrix4);

	/*! Sets this CMatrix4f object to the identity matrix (this = id).
	\return A reference to this object.
	 */
	SICPPSDK_INLINE CMatrix4f&	SetIdentity();

	/*! Inverts this CMatrix4f object (if not singular) (this = this^-1).
	\return true if this matrix has been inverted (not singular), else false.
	 */
	SICPPSDK_INLINE bool InvertInPlace();

	/*! Inverts this CMatrix4f object (if not singular) (this = this^-1).
	\param in_matrix4 matrix to be inverted.
	\return true if this matrix has been inverted (not singular), else false.
	 */
	SICPPSDK_INLINE bool Invert(const CMatrix4f& in_matrix4);

	/*! Sets this CMatrix4f object to the transpose of the inverse of itself (if not singular)
	(this = Transpose(this^-1)).
	\return true if this matrix has been inverted (not singular), else false.
	 */
	SICPPSDK_INLINE bool TransposeInverseInPlace();

	/*! Sets this CMatrix4f object to the transpose of the inverse of the input matrix (if not singular)
	(this = Transpose(in_matrix4^-1)).
	\param in_matrix4 matrix to be inversed and transposed.
	\return true if this matrix has been inverted (not singular), else false.
	 */
	SICPPSDK_INLINE bool TransposeInverse(const CMatrix4f& in_matrix4);

	/*! Transposes this CMatrix4f object in place (this = Transpose(this)).
	 */
	SICPPSDK_INLINE void TransposeInPlace();

	/*! Transposes in_matrix and stores the result in this CMatrix4f object (this = Transpose(in_matrix4)).
	\param in_matrix4 matrix to be inversed and transposed.
	 */
	SICPPSDK_INLINE void Transpose(const CMatrix4f& in_matrix4);

	/*! Right-multiplies this matrix by the matrix m and stores the result in this CMatrix4f object
	(this = this * in_matrix4).
	\param in_matrix4 matrix to be multiplied with.
	\return A reference to this object.
	 */
	SICPPSDK_INLINE CMatrix4f& MulInPlace(const CMatrix4f& in_matrix4);

	/*! Right-multiplies matrix A by matrix B and stores the result in this CMatrix4f object
	(this = in_matrix4A . in_matrix4B).
	\param in_matrix4A matrix
	\param in_matrix4B matrix
	\return A reference to the object which contains the result of the multiplication.
	 */
	SICPPSDK_INLINE CMatrix4f& Mul(const CMatrix4f& in_matrix4A, const CMatrix4f& in_matrix4B);

	/*! Gets the 16 components of this matrix.
	\param io_f00 Value of this matrix[0,0].
	\param io_f01 Value of this matrix[0,1].
	\param io_f02 Value of this matrix[0,2].
	\param io_f03 Value of this matrix[0,3].
	\param io_f10 Value of this matrix[1,0].
	\param io_f11 Value of this matrix[1,1].
	\param io_f12 Value of this matrix[1,2].
	\param io_f13 Value of this matrix[1,3].
	\param io_f20 Value of this matrix[2,0].
	\param io_f21 Value of this matrix[2,1].
	\param io_f22 Value of this matrix[2,2].
	\param io_f23 Value of this matrix[2,3].
	\param io_f30 Value of this matrix[3,0].
	\param io_f31 Value of this matrix[3,1].
	\param io_f32 Value of this matrix[3,2].
	\param io_f33 Value of this matrix[3,3].
	 */
	SICPPSDK_INLINE void Get
	(
		float& io_f00, float& io_f01, float& io_f02, float& io_f03,
		float& io_f10, float& io_f11, float& io_f12, float& io_f13,
		float& io_f20, float& io_f21, float& io_f22, float& io_f23,
		float& io_f30, float& io_f31, float& io_f32, float& io_f33
	) const;

	/*! Sets the 16 components of this matrix.
	\param in_f00 Value to set in this matrix[0,0].
	\param in_f01 Value to set in this matrix[0,1].
	\param in_f02 Value to set in this matrix[0,2].
	\param in_f03 Value to set in this matrix[0,3].
	\param in_f10 Value to set in this matrix[1,0].
	\param in_f11 Value to set in this matrix[1,1].
	\param in_f12 Value to set in this matrix[1,2].
	\param in_f13 Value to set in this matrix[1,3].
	\param in_f20 Value to set in this matrix[2,0].
	\param in_f21 Value to set in this matrix[2,1].
	\param in_f22 Value to set in this matrix[2,2].
	\param in_f23 Value to set in this matrix[2,3].
	\param in_f30 Value to set in this matrix[3,0].
	\param in_f31 Value to set in this matrix[3,1].
	\param in_f32 Value to set in this matrix[3,2].
	\param in_f33 Value to set in this matrix[3,3].
	 */
	SICPPSDK_INLINE void Set(	float in_f00, float in_f01, float in_f02, float in_f03,
								float in_f10, float in_f11, float in_f12, float in_f13,
								float in_f20, float in_f21, float in_f22, float in_f23,
								float in_f30, float in_f31, float in_f32, float in_f33);

	/*! Gets a pointer to the internal matrix.
	\return Pointer to matrix.
	 */
	SICPPSDK_INLINE float* Get();
		
	/*! Sets the 16 components of this matrix.
	\param in_vals values for the matrix.
	 */
	SICPPSDK_INLINE void Set(const float in_vals[4][4]);

	/*! Returns the (i,j)th value of this CMatrix4f object.
	\param in_sRow access to the i th row
	\param in_sCol access to the j th column
	\return The (i,j)th value of this CMatrix4f object.
	 */
	SICPPSDK_INLINE float GetValue(short in_sRow,short in_sCol )const;

	/*! Sets the (i,j)th value of this CMatrix4f object.
	\param in_sRow access to the i th row
	\param in_sCol access to the j th column
	\param in_fVal new value
	 */
	SICPPSDK_INLINE void SetValue(short in_sRow, short in_sCol, float in_fVal );

	/*! Tests the equality of this CMatrix4f object with the specified matrix, with a tolerance of Epsilon.
	\param in_matrix4 Operand matrix.
	\param in_fEpsilon Error margin Possible Values: [0, +INF[ should be a positive value
	\return true if equal else false.
	 */
	SICPPSDK_INLINE bool EpsilonEquals
	(
		const CMatrix4f& in_matrix4,
		float in_fEpsilon
	) const;

	/*! Tests the strict equality of this CMatrix4f object with the specified matrix.
	\param in_matrix4 Operand matrix.
	\return true if equal else false.
	 */
	SICPPSDK_INLINE bool Equals(const CMatrix4f& in_matrix4) const;

	/*! Equality operator. Tests the strict equality of this CMatrix4f object with the specified matrix.
	\param in_matrix4 Operand matrix4.
	\return true if equal else false.
	\sa CMatrix4f::Equals
	 */
	SICPPSDK_INLINE bool operator ==(const CMatrix4f & in_matrix4 ) const;

	/*! Inequality operator. Tests the strict inequality of this CMatrix4f object with the specified matrix.
	\param in_matrix4 Operand matrix.
	\return true if equal else false.
	\sa CMatrix4f::Equals
	 */
	SICPPSDK_INLINE bool operator !=(const CMatrix4f & in_matrix4 ) const;

	/*! Less than operator. Performs a comparison with a specified CMatrix4f to determine if this CMatrix4f is
	less than the specified CMatrix4f. The comparison is arbitrary and not geometrically meaningful, it's only purpose is
	to make CMatrix4f compliant with stl for sorting operations.
	\return true if this CMatrix4f is less than the specified CMatrix4f, false otherwise.
	\since 7.5
	*/
	SICPPSDK_INLINE bool operator < (const CMatrix4f& in_matrix4 )const;

	/*! Gets a pointer to the internal matrix. Const version
	\return Pointer to const matrix.
	\since 11.0 (2013)
	 */
	SICPPSDK_INLINE const float* Get() const;

private:
	float m_fMat[4][4];
	unsigned char m_maskInfo;
	
	SICPPSDK_INLINE bool ComputeInverse
	(
		const float in_fMat[4][4],
		float out_fInv[4][4],
		const bool bTransposeResult = false
	);
};

//inline functions
SICPPSDK_INLINE CMatrix4f::CMatrix4f() : m_maskInfo(0)
{
	m_fMat[0][0] = 0.0;
	m_fMat[0][1] = 0.0;
	m_fMat[0][2] = 0.0;
	m_fMat[0][3] = 0.0;
	m_fMat[1][0] = 0.0;
	m_fMat[1][1] = 0.0;
	m_fMat[1][2] = 0.0;
	m_fMat[1][3] = 0.0;
	m_fMat[2][0] = 0.0;
	m_fMat[2][1] = 0.0;
	m_fMat[2][2] = 0.0;
	m_fMat[2][3] = 0.0;
	m_fMat[3][0] = 0.0;
	m_fMat[3][1] = 0.0;
	m_fMat[3][2] = 0.0;
	m_fMat[3][3] = 0.0;
}

SICPPSDK_INLINE CMatrix4f::CMatrix4f
(
	float in_f00, float in_f01, float in_f02, float in_f03,
	float in_f10, float in_f11, float in_f12, float in_f13,
	float in_f20, float in_f21, float in_f22, float in_f23,
	float in_f30, float in_f31, float in_f32, float in_f33
) : m_maskInfo(0)
{
	m_fMat[0][0] = in_f00;
	m_fMat[0][1] = in_f01;
	m_fMat[0][2] = in_f02;
	m_fMat[0][3] = in_f03;
	m_fMat[1][0] = in_f10;
	m_fMat[1][1] = in_f11;
	m_fMat[1][2] = in_f12;
	m_fMat[1][3] = in_f13;
	m_fMat[2][0] = in_f20;
	m_fMat[2][1] = in_f21;
	m_fMat[2][2] = in_f22;
	m_fMat[2][3] = in_f23;
	m_fMat[3][0] = in_f30;
	m_fMat[3][1] = in_f31;
	m_fMat[3][2] = in_f32;
	m_fMat[3][3] = in_f33;
}

SICPPSDK_INLINE CMatrix4f::CMatrix4f(const CMatrix4f& in_matrix4)
{
	m_fMat[0][0] = in_matrix4.m_fMat[0][0];
	m_fMat[0][1] = in_matrix4.m_fMat[0][1];
	m_fMat[0][2] = in_matrix4.m_fMat[0][2];
	m_fMat[0][3] = in_matrix4.m_fMat[0][3];
	m_fMat[1][0] = in_matrix4.m_fMat[1][0];
	m_fMat[1][1] = in_matrix4.m_fMat[1][1];
	m_fMat[1][2] = in_matrix4.m_fMat[1][2];
	m_fMat[1][3] = in_matrix4.m_fMat[1][3];
	m_fMat[2][0] = in_matrix4.m_fMat[2][0];
	m_fMat[2][1] = in_matrix4.m_fMat[2][1];
	m_fMat[2][2] = in_matrix4.m_fMat[2][2];
	m_fMat[2][3] = in_matrix4.m_fMat[2][3];
	m_fMat[3][0] = in_matrix4.m_fMat[3][0];
	m_fMat[3][1] = in_matrix4.m_fMat[3][1];
	m_fMat[3][2] = in_matrix4.m_fMat[3][2];
	m_fMat[3][3] = in_matrix4.m_fMat[3][3];
	m_maskInfo = in_matrix4.m_maskInfo;
}

SICPPSDK_INLINE CMatrix4f::~CMatrix4f()
{}

SICPPSDK_INLINE CMatrix4f& CMatrix4f::operator=( const CMatrix4f & in_matrix4 )
{
	m_fMat[0][0] = in_matrix4.m_fMat[0][0];
	m_fMat[0][1] = in_matrix4.m_fMat[0][1];
	m_fMat[0][2] = in_matrix4.m_fMat[0][2];
	m_fMat[0][3] = in_matrix4.m_fMat[0][3];
	m_fMat[1][0] = in_matrix4.m_fMat[1][0];
	m_fMat[1][1] = in_matrix4.m_fMat[1][1];
	m_fMat[1][2] = in_matrix4.m_fMat[1][2];
	m_fMat[1][3] = in_matrix4.m_fMat[1][3];
	m_fMat[2][0] = in_matrix4.m_fMat[2][0];
	m_fMat[2][1] = in_matrix4.m_fMat[2][1];
	m_fMat[2][2] = in_matrix4.m_fMat[2][2];
	m_fMat[2][3] = in_matrix4.m_fMat[2][3];
	m_fMat[3][0] = in_matrix4.m_fMat[3][0];
	m_fMat[3][1] = in_matrix4.m_fMat[3][1];
	m_fMat[3][2] = in_matrix4.m_fMat[3][2];
	m_fMat[3][3] = in_matrix4.m_fMat[3][3];
	m_maskInfo = in_matrix4.m_maskInfo;
	return *this;
}

SICPPSDK_INLINE CMatrix4f& CMatrix4f::operator*=(const CMatrix4f& in_matrix4)
{
	return MulInPlace(in_matrix4);
}

SICPPSDK_INLINE CMatrix4f& CMatrix4f::SetIdentity()
{
	m_fMat[0][0] = 1.0;
	m_fMat[0][1] = 0.0;
	m_fMat[0][2] = 0.0;
	m_fMat[0][3] = 0.0;
	m_fMat[1][0] = 0.0;
	m_fMat[1][1] = 1.0;
	m_fMat[1][2] = 0.0;
	m_fMat[1][3] = 0.0;
	m_fMat[2][0] = 0.0;
	m_fMat[2][1] = 0.0;
	m_fMat[2][2] = 1.0;
	m_fMat[2][3] = 0.0;
	m_fMat[3][0] = 0.0;
	m_fMat[3][1] = 0.0;
	m_fMat[3][2] = 0.0;
	m_fMat[3][3] = 1.0;
	return *this;
}

SICPPSDK_INLINE bool CMatrix4f::InvertInPlace()
{
	return Invert(*this);
}

SICPPSDK_INLINE bool CMatrix4f::Invert(const CMatrix4f& in_matrix4)
{
	float fInv[4][4];

	if (ComputeInverse(in_matrix4.m_fMat, fInv))
	{
		Set(fInv);
		return true;
	}
	else // singular matrix
	{
		return false;
	}
}

SICPPSDK_INLINE bool CMatrix4f::TransposeInverseInPlace()
{
	return TransposeInverse(*this);
}

SICPPSDK_INLINE bool CMatrix4f::TransposeInverse(const CMatrix4f& in_matrix4)
{
	float fTransInv[4][4];

	if(ComputeInverse(in_matrix4.m_fMat, fTransInv, true))
	{
		Set(fTransInv);
		return true;
	}
	else // singular matrix
	{
		return false;
	}
}

SICPPSDK_INLINE void CMatrix4f::TransposeInPlace()
{
	Transpose(*this);
}

SICPPSDK_INLINE void CMatrix4f::Transpose(const CMatrix4f& in_matrix4)
{
	float  dTempMat[4][4];
	for(int nR=0; nR<4; nR++)
		for(int nC=0; nC<4; nC++)
			dTempMat[nR][nC] = in_matrix4.m_fMat[nC][nR];
	Set(dTempMat);
}

SICPPSDK_INLINE CMatrix4f&	CMatrix4f::MulInPlace(const CMatrix4f& in_matrix4)
{
	return Mul(*this,in_matrix4);
}

SICPPSDK_INLINE CMatrix4f&	CMatrix4f::Mul
(
 const CMatrix4f& in_matrix4A,
 const CMatrix4f& in_matrix4B
)
{
	float  dTempMat[4][4];

	for(int nR=0; nR<4; nR++)
		for(int nC=0; nC<4; nC++)
			dTempMat[nR][nC] =
				in_matrix4A.m_fMat[nR][0] * in_matrix4B.m_fMat[0][nC] +
				in_matrix4A.m_fMat[nR][1] * in_matrix4B.m_fMat[1][nC] +
				in_matrix4A.m_fMat[nR][2] * in_matrix4B.m_fMat[2][nC] +
				in_matrix4A.m_fMat[nR][3] * in_matrix4B.m_fMat[3][nC];

	Set(dTempMat);
	return (*this);
}

SICPPSDK_INLINE void CMatrix4f::Get
(
	float& io_f00, float& io_f01, float& io_f02, float& io_f03,
	float& io_f10, float& io_f11, float& io_f12, float& io_f13,
	float& io_f20, float& io_f21, float& io_f22, float& io_f23,
	float& io_f30, float& io_f31, float& io_f32, float& io_f33
) const
{

	io_f00 = m_fMat[0][0];
	io_f01 = m_fMat[0][1];
	io_f02 = m_fMat[0][2];
	io_f03 = m_fMat[0][3];
	io_f10 = m_fMat[1][0];
	io_f11 = m_fMat[1][1];
	io_f12 = m_fMat[1][2];
	io_f13 = m_fMat[1][3];
	io_f20 = m_fMat[2][0];
	io_f21 = m_fMat[2][1];
	io_f22 = m_fMat[2][2];
	io_f23 = m_fMat[2][3];
	io_f30 = m_fMat[3][0];
	io_f31 = m_fMat[3][1];
	io_f32 = m_fMat[3][2];
	io_f33 = m_fMat[3][3];
}

SICPPSDK_INLINE void CMatrix4f::Set
(
	float in_f00, float in_f01, float in_f02, float in_f03,
	float in_f10, float in_f11, float in_f12, float in_f13,
	float in_f20, float in_f21, float in_f22, float in_f23,
	float in_f30, float in_f31, float in_f32, float in_f33
)
{
	m_fMat[0][0] = in_f00;
	m_fMat[0][1] = in_f01;
	m_fMat[0][2] = in_f02;
	m_fMat[0][3] = in_f03;
	m_fMat[1][0] = in_f10;
	m_fMat[1][1] = in_f11;
	m_fMat[1][2] = in_f12;
	m_fMat[1][3] = in_f13;
	m_fMat[2][0] = in_f20;
	m_fMat[2][1] = in_f21;
	m_fMat[2][2] = in_f22;
	m_fMat[2][3] = in_f23;
	m_fMat[3][0] = in_f30;
	m_fMat[3][1] = in_f31;
	m_fMat[3][2] = in_f32;
	m_fMat[3][3] = in_f33;
}

SICPPSDK_INLINE void CMatrix4f::Set(const float in_matrix4[4][4])
{
	m_fMat[0][0] = in_matrix4[0][0];
	m_fMat[0][1] = in_matrix4[0][1];
	m_fMat[0][2] = in_matrix4[0][2];
	m_fMat[0][3] = in_matrix4[0][3];
	m_fMat[1][0] = in_matrix4[1][0];
	m_fMat[1][1] = in_matrix4[1][1];
	m_fMat[1][2] = in_matrix4[1][2];
	m_fMat[1][3] = in_matrix4[1][3];
	m_fMat[2][0] = in_matrix4[2][0];
	m_fMat[2][1] = in_matrix4[2][1];
	m_fMat[2][2] = in_matrix4[2][2];
	m_fMat[2][3] = in_matrix4[2][3];
	m_fMat[3][0] = in_matrix4[3][0];
	m_fMat[3][1] = in_matrix4[3][1];
	m_fMat[3][2] = in_matrix4[3][2];
	m_fMat[3][3] = in_matrix4[3][3];
}

SICPPSDK_INLINE float* CMatrix4f::Get()
{
	return &m_fMat[0][0];
}

SICPPSDK_INLINE const float* CMatrix4f::Get() const
{
	return &m_fMat[0][0];
}

SICPPSDK_INLINE float CMatrix4f::GetValue(short in_sRow,short in_sCol ) const
{
	bool l_bValidIndex =  (	in_sRow >=0 && in_sCol >= 0 &&
							in_sRow <=3 && in_sCol <= 3);
	assert(l_bValidIndex);

	if(l_bValidIndex)
	{
		return m_fMat[in_sRow][in_sCol];
	}
	return 0.0;
}

SICPPSDK_INLINE void CMatrix4f::SetValue(short in_sRow, short in_sCol, float in_fVal )
{
	bool l_bValidIndex =  (	in_sRow >=0 && in_sCol >= 0 && in_sRow <=3 && in_sCol <= 3);

	assert(l_bValidIndex);
	if(l_bValidIndex)
	{
		m_fMat[in_sRow][in_sCol] = in_fVal;
	}
}

SICPPSDK_INLINE bool CMatrix4f::EpsilonEquals
(
	const CMatrix4f& in_matrix4,
	float in_fEpsilon
) const
{
	return (this == &in_matrix4) ? true :
		::fabs(m_fMat[0][0] - in_matrix4.m_fMat[0][0]) < ::fabs(in_fEpsilon) &&
		::fabs(m_fMat[0][1] - in_matrix4.m_fMat[0][1]) < ::fabs(in_fEpsilon) &&
		::fabs(m_fMat[0][2] - in_matrix4.m_fMat[0][2]) < ::fabs(in_fEpsilon) &&
		::fabs(m_fMat[0][3] - in_matrix4.m_fMat[0][3]) < ::fabs(in_fEpsilon) &&
		::fabs(m_fMat[1][0] - in_matrix4.m_fMat[1][0]) < ::fabs(in_fEpsilon) &&
		::fabs(m_fMat[1][1] - in_matrix4.m_fMat[1][1]) < ::fabs(in_fEpsilon) &&
		::fabs(m_fMat[1][2] - in_matrix4.m_fMat[1][2]) < ::fabs(in_fEpsilon) &&
		::fabs(m_fMat[1][3] - in_matrix4.m_fMat[1][3]) < ::fabs(in_fEpsilon) &&
		::fabs(m_fMat[2][0] - in_matrix4.m_fMat[2][0]) < ::fabs(in_fEpsilon) &&
		::fabs(m_fMat[2][1] - in_matrix4.m_fMat[2][1]) < ::fabs(in_fEpsilon) &&
		::fabs(m_fMat[2][2] - in_matrix4.m_fMat[2][2]) < ::fabs(in_fEpsilon) &&
		::fabs(m_fMat[2][3] - in_matrix4.m_fMat[2][3]) < ::fabs(in_fEpsilon) &&
		::fabs(m_fMat[3][0] - in_matrix4.m_fMat[3][0]) < ::fabs(in_fEpsilon) &&
		::fabs(m_fMat[3][1] - in_matrix4.m_fMat[3][1]) < ::fabs(in_fEpsilon) &&
		::fabs(m_fMat[3][2] - in_matrix4.m_fMat[3][2]) < ::fabs(in_fEpsilon) &&
		::fabs(m_fMat[3][3] - in_matrix4.m_fMat[3][3]) < ::fabs(in_fEpsilon);
}

SICPPSDK_INLINE bool CMatrix4f::Equals(const CMatrix4f& in_matrix4) const
{
	return (this == &in_matrix4) ? true :
		m_fMat[0][0] == in_matrix4.m_fMat[0][0] &&
		m_fMat[0][1] == in_matrix4.m_fMat[0][1] &&
		m_fMat[0][2] == in_matrix4.m_fMat[0][2] &&
		m_fMat[0][3] == in_matrix4.m_fMat[0][3] &&
		m_fMat[1][0] == in_matrix4.m_fMat[1][0] &&
		m_fMat[1][1] == in_matrix4.m_fMat[1][1] &&
		m_fMat[1][2] == in_matrix4.m_fMat[1][2] &&
		m_fMat[1][3] == in_matrix4.m_fMat[1][3] &&
		m_fMat[2][0] == in_matrix4.m_fMat[2][0] &&
		m_fMat[2][1] == in_matrix4.m_fMat[2][1] &&
		m_fMat[2][2] == in_matrix4.m_fMat[2][2] &&
		m_fMat[2][3] == in_matrix4.m_fMat[2][3] &&
		m_fMat[3][0] == in_matrix4.m_fMat[3][0] &&
		m_fMat[3][1] == in_matrix4.m_fMat[3][1] &&
		m_fMat[3][2] == in_matrix4.m_fMat[3][2] &&
		m_fMat[3][3] == in_matrix4.m_fMat[3][3];
}

SICPPSDK_INLINE bool CMatrix4f::operator ==(const CMatrix4f & in_matrix4 ) const
{
	return Equals( in_matrix4 );
}

SICPPSDK_INLINE bool CMatrix4f::operator !=(const CMatrix4f & in_matrix4 ) const
{
	return ! Equals( in_matrix4 );
}

SICPPSDK_INLINE bool CMatrix4f::operator < (const CMatrix4f& in_matrix4 )const
{
	if ( m_fMat[0][0] != in_matrix4.m_fMat[0][0] ) return m_fMat[0][0] < in_matrix4.m_fMat[0][0];
	if ( m_fMat[0][1] != in_matrix4.m_fMat[0][1] ) return m_fMat[0][1] < in_matrix4.m_fMat[0][1];
	if ( m_fMat[0][2] != in_matrix4.m_fMat[0][2] ) return m_fMat[0][2] < in_matrix4.m_fMat[0][2];
	if ( m_fMat[0][3] != in_matrix4.m_fMat[0][3] ) return m_fMat[0][3] < in_matrix4.m_fMat[0][3];
	if ( m_fMat[1][0] != in_matrix4.m_fMat[1][0] ) return m_fMat[1][0] < in_matrix4.m_fMat[1][0];
	if ( m_fMat[1][1] != in_matrix4.m_fMat[1][1] ) return m_fMat[1][1] < in_matrix4.m_fMat[1][1];
	if ( m_fMat[1][2] != in_matrix4.m_fMat[1][2] ) return m_fMat[1][2] < in_matrix4.m_fMat[1][2];
	if ( m_fMat[1][3] != in_matrix4.m_fMat[1][3] ) return m_fMat[1][3] < in_matrix4.m_fMat[1][3];
	if ( m_fMat[2][0] != in_matrix4.m_fMat[2][0] ) return m_fMat[2][0] < in_matrix4.m_fMat[2][0];
	if ( m_fMat[2][1] != in_matrix4.m_fMat[2][1] ) return m_fMat[2][1] < in_matrix4.m_fMat[2][1];
	if ( m_fMat[2][2] != in_matrix4.m_fMat[2][2] ) return m_fMat[2][2] < in_matrix4.m_fMat[2][2];
	if ( m_fMat[2][3] != in_matrix4.m_fMat[2][3] ) return m_fMat[2][3] < in_matrix4.m_fMat[2][3];
	if ( m_fMat[3][0] != in_matrix4.m_fMat[3][0] ) return m_fMat[3][0] < in_matrix4.m_fMat[3][0];
	if ( m_fMat[3][1] != in_matrix4.m_fMat[3][1] ) return m_fMat[3][1] < in_matrix4.m_fMat[3][1];
	if ( m_fMat[3][2] != in_matrix4.m_fMat[3][2] ) return m_fMat[3][2] < in_matrix4.m_fMat[3][2];
	if ( m_fMat[3][3] != in_matrix4.m_fMat[3][3] ) return m_fMat[3][3] < in_matrix4.m_fMat[3][3];
	return false;
}

SICPPSDK_INLINE bool CMatrix4f::ComputeInverse
(
	const float in_fMat[4][4],
	float out_fInv[4][4],
	const bool bTransposeResult
)
{
	int		i, j, k;
	float	fSys[4][8];
	float	fTemp;

	// Initialize fSys matrix:
	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			fSys[i][j] = in_fMat[i][j];
			fSys[i][j+4] = (float) (i==j);
		}
	}
	// Compute inverse:
	for(j=0; j<4; j++)
	{
		if(fabs(fSys[j][j]) < MicroEPS)
		{
			for(i=j + 1; (i<4) && (fabs(fSys[i][j]) < MicroEPS ); i++)
			{};
			if(i==4)
			{
				return(false);
			}
			else
			{
				for(k=0; k<8; k++)
				{
					fTemp = fSys[i][k];
					fSys[i][k] = fSys[j][k];
					fSys[j][k] = fTemp;
				}
			}
		}
		fTemp = 1.0f / fSys[j][j];
		for(i=0; i<8; i++)
		{
			fSys[j][i] *= fTemp;
		}
		for(i=0; i<4; i++)
		{
			if(i != j)
			{
				fTemp = - fSys[i][j];
				for(k=0; k<8; k++)
				{
					fSys[i][k] += fSys[j][k] * fTemp;
				}
			}
		}
	}

	// Copy result from fSys to out_fInv:
	if(bTransposeResult)
	{
		for(i=0; i<4; i++)
		{
			for(j=0; j<4; j++)
			{
				out_fInv[j][i] = fSys[i][j + 4];
			}
		}
	}
	else
	{
		for(i=0; i<4; i++)
		{
			for(j=0; j<4; j++)
			{
				out_fInv[i][j] = fSys[i][j + 4];
			}
		}
	}
	return(true);
}

};
};

#endif // __XSIMATRIX4_H__
