//*****************************************************************************
/*!
   \file xsi_matrix3f.h
   \brief CMatrix3f class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIMATRIX3F_H__
#define __XSIMATRIX3F_H__

#include "sicppsdk.h"
#include "xsi_math.h"

namespace XSI {
namespace MATH {

class CVector3f;

//*****************************************************************************
/*! \class CMatrix3f xsi_matrix3f.h
	\brief A class to represent a single precision floating point 3 by 3 matrix. This class is typically used for
	implementing custom ICE nodes.
 */
//*****************************************************************************
class SICPPSDKDECL CMatrix3f
{
public:

	/*! Default constructor. */
	SICPPSDK_INLINE CMatrix3f();

	/*! Constructor.
	\param in_00 Value to set in this matrix[0,0].
	\param in_01 Value to set in this matrix[0,1].
	\param in_02 Value to set in this matrix[0,2].
	\param in_10 Value to set in this matrix[1,0].
	\param in_11 Value to set in this matrix[1,1].
	\param in_12 Value to set in this matrix[1,2].
	\param in_20 Value to set in this matrix[2,0].
	\param in_21 Value to set in this matrix[2,1].
	\param in_22 Value to set in this matrix[2,2].
	*/
	SICPPSDK_INLINE CMatrix3f(	float in_00, float in_01, float in_02,
								float in_10, float in_11, float in_12,
								float in_20, float in_21, float in_22);

	/*! Copy constructor.
	\param in_matrix3 constant class object.
	*/
	SICPPSDK_INLINE CMatrix3f( const CMatrix3f& in_matrix3);

	/*! Default destructor. */
	SICPPSDK_INLINE ~CMatrix3f();

	/*! Assignment operator.
		\param in_matrix3& constant class object.
	*/
	SICPPSDK_INLINE CMatrix3f  & operator=( const CMatrix3f & in_matrix3 );

	/*! Right-multiplies this CMatrix3f object by in_matrix3 and stores the result in the same CMatrix3f object (this = this * in_matrix3)
	\param in_matrix3 Matrix to be multiplied with.
	\return A reference to this CMatrix3f object.
	\sa CMatrix3f::MulInPlace
	 */
	SICPPSDK_INLINE CMatrix3f & operator*=(const CMatrix3f & in_matrix3 );

	/*! Sets this CMatrix3f object to the identity matrix (this = id).
	\return A reference to this CMatrix3f object.
	 */
	SICPPSDK_INLINE CMatrix3f& SetIdentity();

	/*! Inverts this CMatrix3f object (if not singular) (this = this^-1).
	\param in_matrix3 Matrix to be inverted.
	\return true if this CMatrix3f object has been inverted (not singular), else false.
	 */
	SICPPSDK_INLINE bool Invert(const CMatrix3f& in_matrix3);

	/*! Sets this CMatrix3f object to the transpose of the inverse of itself (if not singular) (this = Transpose(this^-1)).
	\return true if this CMatrix3f object has been inverted (not singular), else false.
	 */
	SICPPSDK_INLINE bool TransposeInverseInPlace();

	/*! Sets this CMatrix3f object to the transpose of the inverse of the input matrix (if not singular)
	(this = Transpose(in_matrix3^-1)).
	\param in_matrix3 CMatrix3f object to be inversed and transposed.
	\return true if this CMatrix3f object has been inverted (not singular), else false.
	 */
	SICPPSDK_INLINE bool TransposeInverse(const CMatrix3f& in_matrix3);

	/*! Transposes this CMatrix3f object in place (this = Transpose(this)).
	 */
	SICPPSDK_INLINE void TransposeInPlace();

	/*! Transposes the specified matrix and stores the result in this CMatrix3f object (this = Transpose(in_matrix3)).
	\param in_matrix3 matrix to be inversed and transposed.
	 */
	SICPPSDK_INLINE void Transpose(const CMatrix3f& in_matrix3);

	/*! Right-multiplies this CMatrix3f object by in_matrix3 and stores the result in this CMatrix3f object	(this = this * in_matrix3).
	\param in_matrix3 matrix to be multiplied with.
	\return A reference to the CMatrix3f object.
	 */
	SICPPSDK_INLINE CMatrix3f& MulInPlace(const CMatrix3f& in_matrix3);

	/*! Right-multiplies in_matrix3A by in_matrix3B and stores the result in this CMatrix3f object
	(this = in_matrix3A * in_matrix3B).
	\param in_matrix3A matrix
	\param in_matrix3B matrix
	\return CMatrix3f& A reference to the CMatrix3f object which contains the result of the multiplication.
	 */
	SICPPSDK_INLINE CMatrix3f& Mul(const CMatrix3f& in_matrix3A, const CMatrix3f& in_matrix3B);

	/*! Returns the 9 components of this CMatrix3f object.
	\param io_00 Value of this matrix[0,0].
	\param io_01 Value of this matrix[0,1].
	\param io_02 Value of this matrix[0,2].
	\param io_10 Value of this matrix[1,0].
	\param io_11 Value of this matrix[1,1].
	\param io_12 Value of this matrix[1,2].
	\param io_20 Value of this matrix[2,0].
	\param io_21 Value of this matrix[2,1].
	\param io_22 Value of this matrix[2,2].
	 */
	SICPPSDK_INLINE void Get(	float& io_00, float& io_01, float& io_02,
								float& io_10, float& io_11, float& io_12,
								float& io_20, float& io_21, float& io_22) const;

	/*! Sets the 9 components of this CMatrix3f object.
	\param in_00 Value to set to this matrix[0,0].
	\param in_01 Value to set to this matrix[0,1].
	\param in_02 Value to set to this matrix[0,2].
	\param in_10 Value to set to this matrix[1,0].
	\param in_11 Value to set to this matrix[1,1].
	\param in_12 Value to set to this matrix[1,2].
	\param in_20 Value to set to this matrix[2,0].
	\param in_21 Value to set to this matrix[2,1].
	\param in_22 Value to set to this matrix[2,2].
	 */
	SICPPSDK_INLINE void Set(	float in_00, float in_01, float in_02,
								float in_10, float in_11, float in_12,
								float in_20, float in_21, float in_22);

	/*! Sets the 9 components of this CMatrix3f object.
	\param in_Val A 3x3 array of float values.
	 */
	SICPPSDK_INLINE void Set(const float in_Val[3][3]);

	/*! Gets a pointer to the internal matrix.
	\return Pointer to matrix.
	 */
	SICPPSDK_INLINE float* Get();

	/*! Returns the (i,j)th value of this CMatrix3f object.
	\param in_sRow access to the i th row
	\param in_sCol access to the j th column
	\return The (i,j)th value of this CMatrix3f object.
	 */
	SICPPSDK_INLINE float GetValue(short in_sRow,short in_sCol )const;

	/*! Sets the (i,j)th value of this CMatrix3f object.
	\param in_sRow access to the i th row
	\param in_sCol access to the j th column
	\param in_Val new value
	 */
	SICPPSDK_INLINE void SetValue(short in_sRow, short in_sCol, float in_Val );

	/*! Tests the equality of this CMatrix3f object with the specified matrix, with a tolerance of Epsilon.
	\param in_matrix3 Operand matrix.
	\param in_Epsilon Error margin Possible Values: [0, +INF[ should be a positive value
	\return true if equal else false.
	 */
	bool EpsilonEquals( const CMatrix3f& in_matrix3, float in_Epsilon ) const;

	/*! Tests the strict equality of this CMatrix3f object with the specified matrix.
	\param in_matrix3 Operand matrix.
	\return true if equal else false.
	 */
	SICPPSDK_INLINE bool Equals(const CMatrix3f& in_matrix3) const;

	/*! Equality operator. Tests the strict equality of this CMatrix3f object with the specified matrix.
	\param in_matrix3 Operand matrix3.
	\return true if equal else false.
	\sa CMatrix3f::Equals
	 */
	SICPPSDK_INLINE bool operator ==(const CMatrix3f & in_matrix3 ) const;

	/*! Inequality operator. Tests the strict inequality of this CMatrix3f object with the specified matrix.
	\param in_matrix3 Operand matrix.
	\return true if equal else false.
	\sa CMatrix3f::Equals
	 */
	SICPPSDK_INLINE bool operator !=(const CMatrix3f & in_matrix3 ) const;

	/*! Less than operator. Performs a comparison with a specified CMatrix3f to determine if this CMatrix3f is
	less than the specified CMatrix3f. The comparison is arbitrary and not geometrically meaningful, it's only purpose is
	to make CMAtrix3ff compliant with stl for sorting operations.
	\param in_matrix3 CMatrix3f to compare.
	\return true if this CMatrix3f is less than the specified CMatrix3f, false otherwise.
	\since 7.5
	*/
	SICPPSDK_INLINE bool operator < (const CMatrix3f& in_matrix3 )const;

	/*! Gets a pointer to the const version of the internal matrix.
	\return Pointer to const matrix.	
	\since 11.0 (2013)
	 */
	SICPPSDK_INLINE const float* Get() const;

private:
	float m_Mat[3][3];

	SICPPSDK_INLINE void ComputeDetAndDetSize
	(
		const float in_fMat[3][3],
		float &out_fDet,
		float &out_fDetSize
	);
	SICPPSDK_INLINE void ComputeAdjoint
	(
		const float in_fMat[3][3],
		float out_fAdj[3][3]
	);
	SICPPSDK_INLINE bool ComputeInverse
	(
		const float in_fMat[3][3],
		float out_fInv[3][3],
		const bool in_bTransposeResult = false,
		const float in_fEps = MicroEPS
	);
};

SICPPSDK_INLINE CMatrix3f::CMatrix3f()
{
	m_Mat[0][0] = 0.0;
	m_Mat[0][1] = 0.0;
	m_Mat[0][2] = 0.0;
	m_Mat[1][0] = 0.0;
	m_Mat[1][1] = 0.0;
	m_Mat[1][2] = 0.0;
	m_Mat[2][0] = 0.0;
	m_Mat[2][1] = 0.0;
	m_Mat[2][2] = 0.0;
}

SICPPSDK_INLINE CMatrix3f::CMatrix3f
(
	float in_00, float in_01, float in_02,
	float in_10, float in_11, float in_12,
	float in_20, float in_21, float in_22
)
{
	m_Mat[0][0] = in_00;
	m_Mat[0][1] = in_01;
	m_Mat[0][2] = in_02;
	m_Mat[1][0] = in_10;
	m_Mat[1][1] = in_11;
	m_Mat[1][2] = in_12;
	m_Mat[2][0] = in_20;
	m_Mat[2][1] = in_21;
	m_Mat[2][2] = in_22;
}

SICPPSDK_INLINE CMatrix3f::CMatrix3f(const CMatrix3f& in_matrix3)
{
	m_Mat[0][0] = in_matrix3.m_Mat[0][0];
	m_Mat[0][1] = in_matrix3.m_Mat[0][1];
	m_Mat[0][2] = in_matrix3.m_Mat[0][2];
	m_Mat[1][0] = in_matrix3.m_Mat[1][0];
	m_Mat[1][1] = in_matrix3.m_Mat[1][1];
	m_Mat[1][2] = in_matrix3.m_Mat[1][2];
	m_Mat[2][0] = in_matrix3.m_Mat[2][0];
	m_Mat[2][1] = in_matrix3.m_Mat[2][1];
	m_Mat[2][2] = in_matrix3.m_Mat[2][2];
}

SICPPSDK_INLINE CMatrix3f::~CMatrix3f()
{}

SICPPSDK_INLINE CMatrix3f& CMatrix3f::operator=( const CMatrix3f & in_matrix3 )
{
	Set(in_matrix3.m_Mat);
	return *this;
}

SICPPSDK_INLINE CMatrix3f& CMatrix3f::operator *=(const CMatrix3f& in_matrix3)
{
	return MulInPlace(in_matrix3);
}

SICPPSDK_INLINE CMatrix3f&	CMatrix3f::SetIdentity()
{
	m_Mat[0][0] =  1.0;
	m_Mat[0][1] =  0.0;
	m_Mat[0][2] =  0.0;
	m_Mat[1][0] =  0.0;
	m_Mat[1][1] =  1.0;
	m_Mat[1][2] =  0.0;
	m_Mat[2][0] =  0.0;
	m_Mat[2][1] =  0.0;
	m_Mat[2][2] =  1.0;
	return *this;
}

SICPPSDK_INLINE bool CMatrix3f::Invert(const CMatrix3f& in_matrix3)
{
	float Inv[3][3];

	if (ComputeInverse(in_matrix3.m_Mat, Inv))
	{
		Set( Inv);
		return true;
	}
	else // singular matrix
	{
		return false;
	}
}

SICPPSDK_INLINE bool CMatrix3f::TransposeInverseInPlace()
{
	return TransposeInverse(*this);
}

SICPPSDK_INLINE bool CMatrix3f::TransposeInverse(const CMatrix3f& in_matrix3)
{
	float TransInv[3][3];

	if(ComputeInverse(in_matrix3.m_Mat, TransInv, true))
	{
		Set(TransInv);
		return true;
	}
	else // singular matrix
	{
		return false;
	}
}

SICPPSDK_INLINE void CMatrix3f::TransposeInPlace()
{
	Transpose(*this);
}

SICPPSDK_INLINE void CMatrix3f::Transpose(const CMatrix3f& in_matrix3)
{
   float  fTempMat[3][3];

   for(int nR=0; nR<3; nR++)
   {
	   for(int nC=0; nC<3; nC++)
	   {
         fTempMat[nR][nC] = in_matrix3.m_Mat[nC][nR];
	   }
   }

	Set(fTempMat);
}

SICPPSDK_INLINE CMatrix3f&	CMatrix3f::MulInPlace(const CMatrix3f& in_matrix3)
{
	return Mul(*this,in_matrix3);
}

SICPPSDK_INLINE CMatrix3f& CMatrix3f::Mul
(
	const CMatrix3f& in_matrix3A,
	const CMatrix3f& in_matrix3B
)
{
	float  fTempMat[3][3];

	for(int nR=0; nR<3; nR++)
	{
		for(int nC=0; nC<3; nC++)
		{
			fTempMat[nR][nC] =
				in_matrix3A.m_Mat[nR][0] * in_matrix3B.m_Mat[0][nC] +
				in_matrix3A.m_Mat[nR][1] * in_matrix3B.m_Mat[1][nC] +
				in_matrix3A.m_Mat[nR][2] * in_matrix3B.m_Mat[2][nC];
		}
	}
	Set(fTempMat);
	return *this;
}

SICPPSDK_INLINE void CMatrix3f::Get
(
	float& io_00, float& io_01, float& io_02,
	float& io_10, float& io_11, float& io_12,
	float& io_20, float& io_21, float& io_22
) const
{
	io_00 = m_Mat[0][0];
	io_01 = m_Mat[0][1];
	io_02 = m_Mat[0][2];
	io_10 = m_Mat[1][0];
	io_11 = m_Mat[1][1];
	io_12 = m_Mat[1][2];
	io_20 = m_Mat[2][0];
	io_21 = m_Mat[2][1];
	io_22 = m_Mat[2][2];
}

SICPPSDK_INLINE void CMatrix3f::Set
(
	float in_00, float in_01, float in_02,
	float in_10, float in_11, float in_12,
	float in_20, float in_21, float in_22
)
{
	m_Mat[0][0] = in_00;
	m_Mat[0][1] = in_01;
	m_Mat[0][2] = in_02;
	m_Mat[1][0] = in_10;
	m_Mat[1][1] = in_11;
	m_Mat[1][2] = in_12;
	m_Mat[2][0] = in_20;
	m_Mat[2][1] = in_21;
	m_Mat[2][2] = in_22;
}

SICPPSDK_INLINE void CMatrix3f::Set(const float in_Val[3][3])
{
	m_Mat[0][0] = in_Val[0][0];
	m_Mat[0][1] = in_Val[0][1];
	m_Mat[0][2] = in_Val[0][2];
	m_Mat[1][0] = in_Val[1][0];
	m_Mat[1][1] = in_Val[1][1];
	m_Mat[1][2] = in_Val[1][2];
	m_Mat[2][0] = in_Val[2][0];
	m_Mat[2][1] = in_Val[2][1];
	m_Mat[2][2] = in_Val[2][2];
}

SICPPSDK_INLINE float* CMatrix3f::Get()
{
	return &m_Mat[0][0];
}

SICPPSDK_INLINE const float* CMatrix3f::Get() const
{
	return &m_Mat[0][0];
}

SICPPSDK_INLINE float CMatrix3f::GetValue(short in_sRow,short in_sCol ) const
{
	bool l_bValidIndex =  (	in_sRow >=0 && in_sCol >= 0 && in_sRow <=2 && in_sCol <= 2);
	assert(l_bValidIndex);

	if(l_bValidIndex)
	{
		return m_Mat[in_sRow][in_sCol];
	}
	return 0.0;
}

SICPPSDK_INLINE void CMatrix3f::SetValue(short in_sRow, short in_sCol, float in_Val )
{
	bool l_bValidIndex =  (	in_sRow >=0 && in_sCol >= 0 &&
							in_sRow <=2 && in_sCol <= 2);
	assert(l_bValidIndex);

	if(l_bValidIndex)
	{
		m_Mat[in_sRow][in_sCol] = in_Val;
	}
}

SICPPSDK_INLINE bool CMatrix3f::Equals(const CMatrix3f& in_matrix3) const
{
	return (this == &in_matrix3) ? true :
		m_Mat[0][0] == in_matrix3.m_Mat[0][0] &&
		m_Mat[0][1] == in_matrix3.m_Mat[0][1] &&
		m_Mat[0][2] == in_matrix3.m_Mat[0][2] &&
		m_Mat[1][0] == in_matrix3.m_Mat[1][0] &&
		m_Mat[1][1] == in_matrix3.m_Mat[1][1] &&
		m_Mat[1][2] == in_matrix3.m_Mat[1][2] &&
		m_Mat[2][0] == in_matrix3.m_Mat[2][0] &&
		m_Mat[2][1] == in_matrix3.m_Mat[2][1] &&
		m_Mat[2][2] == in_matrix3.m_Mat[2][2];
}

SICPPSDK_INLINE bool CMatrix3f::operator ==(const CMatrix3f & in_matrix3 ) const
{
	return Equals( in_matrix3 );
}

SICPPSDK_INLINE bool CMatrix3f::operator !=(const CMatrix3f & in_matrix3 ) const
{
	return ! Equals( in_matrix3 );
}

SICPPSDK_INLINE bool CMatrix3f::operator < (const CMatrix3f& in_matrix3 )const
{
	if ( m_Mat[0][0] != in_matrix3.m_Mat[0][0] ) return m_Mat[0][0] < in_matrix3.m_Mat[0][0];
	if ( m_Mat[0][1] != in_matrix3.m_Mat[0][1] ) return m_Mat[0][1] < in_matrix3.m_Mat[0][1];
	if ( m_Mat[0][2] != in_matrix3.m_Mat[0][2] ) return m_Mat[0][2] < in_matrix3.m_Mat[0][2];
	if ( m_Mat[1][0] != in_matrix3.m_Mat[1][0] ) return m_Mat[1][0] < in_matrix3.m_Mat[1][0];
	if ( m_Mat[1][1] != in_matrix3.m_Mat[1][1] ) return m_Mat[1][1] < in_matrix3.m_Mat[1][1];
	if ( m_Mat[1][2] != in_matrix3.m_Mat[1][2] ) return m_Mat[1][2] < in_matrix3.m_Mat[1][2];
	if ( m_Mat[2][0] != in_matrix3.m_Mat[2][0] ) return m_Mat[2][0] < in_matrix3.m_Mat[2][0];
	if ( m_Mat[2][1] != in_matrix3.m_Mat[2][1] ) return m_Mat[2][1] < in_matrix3.m_Mat[2][1];
	if ( m_Mat[2][2] != in_matrix3.m_Mat[2][2] ) return m_Mat[2][2] < in_matrix3.m_Mat[2][2];
	return false;
}

SICPPSDK_INLINE void CMatrix3f::ComputeDetAndDetSize
(
	const float in_fMat[3][3],
	float &out_fDet,
	float &out_fDetSize
)
{
	float fTemp;
	out_fDet = 0.0;
	out_fDetSize = 0.0;

	fTemp =  in_fMat[0][0] * in_fMat[1][1] * in_fMat[2][2];
	out_fDet += fTemp;
	out_fDetSize += fabs(fTemp);

	fTemp =  in_fMat[0][1] * in_fMat[1][2] * in_fMat[2][0];
	out_fDet += fTemp;
	out_fDetSize += fabs(fTemp);

	fTemp =  in_fMat[0][2] * in_fMat[1][0] * in_fMat[2][1];
	out_fDet += fTemp;
	out_fDetSize += fabs(fTemp);

	fTemp = -in_fMat[0][2] * in_fMat[1][1] * in_fMat[2][0];
	out_fDet += fTemp;
	out_fDetSize += fabs(fTemp);

	fTemp = -in_fMat[0][1] * in_fMat[1][0] * in_fMat[2][2];
	out_fDet += fTemp;
	out_fDetSize += fabs(fTemp);

	fTemp = -in_fMat[0][0] * in_fMat[1][2] * in_fMat[2][1];
	out_fDet += fTemp;
	out_fDetSize += fabs(fTemp);
}

SICPPSDK_INLINE void CMatrix3f::ComputeAdjoint
(
	const float in_fMat[3][3],
	float out_fAdj[3][3]
)
{
	out_fAdj[0][0] = (in_fMat[1][1]*in_fMat[2][2] - in_fMat[1][2]*in_fMat[2][1]);
	out_fAdj[0][1] = - (in_fMat[0][1]*in_fMat[2][2] - in_fMat[0][2]*in_fMat[2][1]);
	out_fAdj[0][2] = (in_fMat[0][1]*in_fMat[1][2] - in_fMat[0][2]*in_fMat[1][1]);

	out_fAdj[1][0] = - (in_fMat[1][0]*in_fMat[2][2] - in_fMat[1][2]*in_fMat[2][0]);
	out_fAdj[1][1] = (in_fMat[0][0]*in_fMat[2][2] - in_fMat[0][2]*in_fMat[2][0]);
	out_fAdj[1][2] = - (in_fMat[0][0]*in_fMat[1][2] - in_fMat[0][2]*in_fMat[1][0]);

	out_fAdj[2][0] = (in_fMat[1][0]*in_fMat[2][1] - in_fMat[1][1]*in_fMat[2][0]);
	out_fAdj[2][1] = - (in_fMat[0][0]*in_fMat[2][1] - in_fMat[0][1]*in_fMat[2][0]);
	out_fAdj[2][2] = (in_fMat[0][0]*in_fMat[1][1] - in_fMat[0][1]*in_fMat[1][0]);
}

SICPPSDK_INLINE bool CMatrix3f::ComputeInverse
(
	const float in_fMat[3][3],
	float out_fInv[3][3],
	const bool in_bTransposeResult,
	const float in_fEps
)
{
	float fAdj[3][3];
	float fDet=0.0, fDetSize=0.0, fInvDet;

	ComputeDetAndDetSize(in_fMat, fDet, fDetSize);
	if(fDetSize != 0.0 && fabs(fDet/fDetSize) >= in_fEps)
	{
		ComputeAdjoint(in_fMat, fAdj);
		fInvDet = 1.0f/fDet;
		if(in_bTransposeResult)
		{
			for(int nR=0; nR<3; nR++)
			{
				for(int nC=0; nC<3; nC++)
				{
					out_fInv[nC][nR] = fAdj[nR][nC] * fInvDet;
				}
			}
		}
		else
		{
			for(int nR=0; nR<3; nR++)
			{
				for(int nC=0; nC<3; nC++)
				{
					out_fInv[nR][nC] = fAdj[nR][nC] * fInvDet;
				}
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

};
};

#endif // __XSIMATRIX3F_H__
