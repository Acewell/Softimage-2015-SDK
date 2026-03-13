//*****************************************************************************
/*!
   \file xsi_matrix4.h
   \brief Matrix4 class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIMATRIX4_H__
#define __XSIMATRIX4_H__

#include "sicppsdk.h"

namespace XSI {
namespace MATH {


//*****************************************************************************
/*! \class CMatrix4 xsi_matrix4.h
	\brief This class represents a double precision floating point 4 by 4 matrix.

 	\eg
	\code
		using namespace XSI::MATH;
		CMatrix4 mat4(	1.0,2.0,3.0,4.0,
						5.0,6.0,7.0,8.0,
						9.0,10.0,11.0,12.0,
						13.0,14.0,15.0,16.0);
		mat4.TransposeInPlace();
		Application app;
		app.LogMessage(CString(L"The transposed matrix is ") +
					   CValue(mat4.GetValue(0,0)).GetAsText() + CString(L", ")+
					   CValue(mat4.GetValue(0,1)).GetAsText() + CString(L", ")+
					   CValue(mat4.GetValue(0,2)).GetAsText() + CString(L", ")+
					   CValue(mat4.GetValue(0,3)).GetAsText() + CString(L", ")+
					   CValue(mat4.GetValue(1,0)).GetAsText() + CString(L", ")+
					   CValue(mat4.GetValue(1,1)).GetAsText() + CString(L", ")+
					   CValue(mat4.GetValue(1,2)).GetAsText() + CString(L", ")+
					   CValue(mat4.GetValue(1,3)).GetAsText() + CString(L", ")+
					   CValue(mat4.GetValue(2,0)).GetAsText() + CString(L", ")+
					   CValue(mat4.GetValue(2,1)).GetAsText() + CString(L", ")+
					   CValue(mat4.GetValue(2,2)).GetAsText() + CString(L", ")+
					   CValue(mat4.GetValue(2,3)).GetAsText() + CString(L", ")+
					   CValue(mat4.GetValue(3,0)).GetAsText() + CString(L", ")+
					   CValue(mat4.GetValue(3,1)).GetAsText() + CString(L", ")+
					   CValue(mat4.GetValue(3,2)).GetAsText() + CString(L", ")+
					   CValue(mat4.GetValue(3,3)).GetAsText());
	\endcode
 */
//*****************************************************************************
class SICPPSDKDECL CMatrix4
{
public:

	/*! Default constructor. */
	SICPPSDK_INLINE CMatrix4();

	/*! Constructor.
	\param in_d00 Value to set to this matrix[0,0].
	\param in_d01 Value to set to this matrix[0,1].
	\param in_d02 Value to set to this matrix[0,2].
	\param in_d03 Value to set to this matrix[0,3].
	\param in_d10 Value to set to this matrix[1,0].
	\param in_d11 Value to set to this matrix[1,1].
	\param in_d12 Value to set to this matrix[1,2].
	\param in_d13 Value to set to this matrix[1,3].
	\param in_d20 Value to set to this matrix[2,0].
	\param in_d21 Value to set to this matrix[2,1].
	\param in_d22 Value to set to this matrix[2,2].
	\param in_d23 Value to set to this matrix[2,3].
	\param in_d30 Value to set to this matrix[3,0].
	\param in_d31 Value to set to this matrix[3,1].
	\param in_d32 Value to set to this matrix[3,2].
	\param in_d33 Value to set to this matrix[3,3].
	 */
	SICPPSDK_INLINE CMatrix4(double in_d00, double in_d01, double in_d02, double in_d03,
			 double in_d10, double in_d11, double in_d12, double in_d13,
			 double in_d20, double in_d21, double in_d22, double in_d23,
			 double in_d30, double in_d31, double in_d32, double in_d33);

	/*! Copy constructor.
	\param in_matrix4 constant class object.
	 */
	SICPPSDK_INLINE CMatrix4( const CMatrix4& in_matrix4);

	/*! Default destructor. */
	SICPPSDK_INLINE ~CMatrix4();

	/*! Assignment operator.
	\param in_matrix4 constant class object.
	\return A reference to this object.
	 */
	SICPPSDK_INLINE CMatrix4  & operator=( const CMatrix4 & in_matrix4 );

	/*! Right-multiplies this CMatrix4 object by the specified matrix and stores the result into this matrix
	(this = this . in_matrix4).
	\param in_matrix4 matrix to be multiplied with.
	\return A reference to this object.
	\sa CTransformation::MulInPlace
	 */
	SICPPSDK_INLINE CMatrix4 & operator*=(const CMatrix4 & in_matrix4);

	/*! Sets this CMatrix4 object to the identity matrix (this = id).
	\return A reference to this object.
	 */
	SICPPSDK_INLINE CMatrix4&	SetIdentity();

	/*! Inverts this CMatrix4 object (if not singular) (this = this^-1).
	\return true if this matrix has been inverted (not singular), else false.
	 */
	bool		InvertInPlace();

	/*! Inverts this CMatrix4 object (if not singular) (this = this^-1).
	\param in_matrix4 matrix to be inverted.
	\return true if this matrix has been inverted (not singular), else false.
	 */
	bool		Invert(const CMatrix4& in_matrix4);

	/*! Sets this CMatrix4 object to the transpose of the inverse of itself (if not singular)
	(this = Transpose(this^-1)).
	\return true if this matrix has been inverted (not singular), else false.
	 */
	bool		TransposeInverseInPlace();

	/*! Sets this CMatrix4 object to the transpose of the inverse of the input matrix (if not singular)
	(this = Transpose(in_matrix4^-1)).
	\param in_matrix4 matrix to be inversed and transposed.
	\return true if this matrix has been inverted (not singular), else false.
	 */
	bool		TransposeInverse(const CMatrix4& in_matrix4);

	/*! Transposes this CMatrix4 object in place (this = Transpose(this)).
	 */
	void		TransposeInPlace();

	/*! Transposes in_matrix and stores the result in this CMatrix4 object (this = Transpose(in_matrix4)).
	\param in_matrix4 matrix to be inversed and transposed.
	 */
	SICPPSDK_INLINE void		Transpose(const CMatrix4& in_matrix4);

	/*! Right-multiplies this matrix by the matrix m and stores the result in this CMatrix4 object
	(this = this . in_matrix4).
	\param in_matrix4 matrix to be multiplied with.
	\return A reference to this object.
	 */
	SICPPSDK_INLINE CMatrix4&		MulInPlace(const CMatrix4& in_matrix4);

	/*! Right-multiplies matrix A by matrix B and stores the result in this CMatrix4 object
	(this = in_matrix4A . in_matrix4B).
	\param in_matrix4A matrix
	\param in_matrix4B matrix
	\return A reference to the object which contains the result of the multiplication.
	 */
	SICPPSDK_INLINE CMatrix4&		Mul(const CMatrix4& in_matrix4A, const CMatrix4& in_matrix4B);

	/*! Gets the 16 components of this matrix.
	\param io_d00 Value of this matrix[0,0].
	\param io_d01 Value of this matrix[0,1].
	\param io_d02 Value of this matrix[0,2].
	\param io_d03 Value of this matrix[0,3].
	\param io_d10 Value of this matrix[1,0].
	\param io_d11 Value of this matrix[1,1].
	\param io_d12 Value of this matrix[1,2].
	\param io_d13 Value of this matrix[1,3].
	\param io_d20 Value of this matrix[2,0].
	\param io_d21 Value of this matrix[2,1].
	\param io_d22 Value of this matrix[2,2].
	\param io_d23 Value of this matrix[2,3].
	\param io_d30 Value of this matrix[3,0].
	\param io_d31 Value of this matrix[3,1].
	\param io_d32 Value of this matrix[3,2].
	\param io_d33 Value of this matrix[3,3].
	 */
	SICPPSDK_INLINE void Get
	(
		double& io_d00, double& io_d01, double& io_d02, double& io_d03,
		double& io_d10, double& io_d11, double& io_d12, double& io_d13,
		double& io_d20, double& io_d21, double& io_d22, double& io_d23,
		double& io_d30, double& io_d31, double& io_d32, double& io_d33
	) const;


	/*! Sets the 16 components of this matrix.
	\param in_d00 Value to set in this matrix[0,0].
	\param in_d01 Value to set in this matrix[0,1].
	\param in_d02 Value to set in this matrix[0,2].
	\param in_d03 Value to set in this matrix[0,3].
	\param in_d10 Value to set in this matrix[1,0].
	\param in_d11 Value to set in this matrix[1,1].
	\param in_d12 Value to set in this matrix[1,2].
	\param in_d13 Value to set in this matrix[1,3].
	\param in_d20 Value to set in this matrix[2,0].
	\param in_d21 Value to set in this matrix[2,1].
	\param in_d22 Value to set in this matrix[2,2].
	\param in_d23 Value to set in this matrix[2,3].
	\param in_d30 Value to set in this matrix[3,0].
	\param in_d31 Value to set in this matrix[3,1].
	\param in_d32 Value to set in this matrix[3,2].
	\param in_d33 Value to set in this matrix[3,3].
	 */
	SICPPSDK_INLINE void	Set(double in_d00, double in_d01, double in_d02, double in_d03,
				double in_d10, double in_d11, double in_d12, double in_d13,
				double in_d20, double in_d21, double in_d22, double in_d23,
				double in_d30, double in_d31, double in_d32, double in_d33);

	/*! Sets the 16 components of this matrix.
	\param in_vals values for the matrix.
	 */
	SICPPSDK_INLINE void Set(const double in_vals[4][4]);

	/*! Returns the (i,j)th value of this CMatrix4 object.
	\param in_sRow access to the i th row
	\param in_sCol access to the j th column
	\return The (i,j)th value of this CMatrix4 object.
	 */
	SICPPSDK_INLINE double		GetValue(short in_sRow,short in_sCol )const;

	/*! Sets the (i,j)th value of this CMatrix4 object.
	\param in_sRow access to the i th row
	\param in_sCol access to the j th column
	\param in_dVal new value
	 */
	SICPPSDK_INLINE void		SetValue(short in_sRow, short in_sCol, double in_dVal );

	/*! Tests the equality of this CMatrix4 object with the specified matrix, with a tolerance of Epsilon.
	\param in_matrix4 Operand matrix.
	\param in_dEpsilon Error margin Possible Values: [0, +INF[ should be a positive value
	\return true if equal else false.
	 */
	bool EpsilonEquals
	(
		const CMatrix4& in_matrix4,
		double in_dEpsilon
	) const;

	/*! Tests the strict equality of this CMatrix4 object with the specified matrix.
	\param in_matrix4 Operand matrix.
	\return true if equal else false.
	 */
	SICPPSDK_INLINE bool Equals(const CMatrix4& in_matrix4) const;

	/*! Equality operator. Tests the strict equality of this CMatrix4 object with the specified matrix.
	\param in_matrix4 Operand matrix4.
	\return true if equal else false.
	\sa CMatrix4::Equals
	 */
	SICPPSDK_INLINE bool operator ==(const CMatrix4 & in_matrix4 ) const;

	/*! Inequality operator. Tests the strict inequality of this CMatrix4 object with the specified matrix.
	\param in_matrix4 Operand matrix.
	\return true if equal else false.
	\sa CMatrix4::Equals
	 */
	SICPPSDK_INLINE bool operator !=(const CMatrix4 & in_matrix4 ) const;
private:
	double m_dMat[4][4];
};

//inline functions
SICPPSDK_INLINE CMatrix4::CMatrix4()
{
	m_dMat[0][0] = 0.0;
	m_dMat[0][1] = 0.0;
	m_dMat[0][2] = 0.0;
	m_dMat[0][3] = 0.0;
	m_dMat[1][0] = 0.0;
	m_dMat[1][1] = 0.0;
	m_dMat[1][2] = 0.0;
	m_dMat[1][3] = 0.0;
	m_dMat[2][0] = 0.0;
	m_dMat[2][1] = 0.0;
	m_dMat[2][2] = 0.0;
	m_dMat[2][3] = 0.0;
	m_dMat[3][0] = 0.0;
	m_dMat[3][1] = 0.0;
	m_dMat[3][2] = 0.0;
	m_dMat[3][3] = 0.0;
}

SICPPSDK_INLINE CMatrix4::CMatrix4
(double in_d00, double in_d01, double in_d02, double in_d03,
 double in_d10, double in_d11, double in_d12, double in_d13,
 double in_d20, double in_d21, double in_d22, double in_d23,
 double in_d30, double in_d31, double in_d32, double in_d33
)
{
	m_dMat[0][0] = in_d00;
	m_dMat[0][1] = in_d01;
	m_dMat[0][2] = in_d02;
	m_dMat[0][3] = in_d03;
	m_dMat[1][0] = in_d10;
	m_dMat[1][1] = in_d11;
	m_dMat[1][2] = in_d12;
	m_dMat[1][3] = in_d13;
	m_dMat[2][0] = in_d20;
	m_dMat[2][1] = in_d21;
	m_dMat[2][2] = in_d22;
	m_dMat[2][3] = in_d23;
	m_dMat[3][0] = in_d30;
	m_dMat[3][1] = in_d31;
	m_dMat[3][2] = in_d32;
	m_dMat[3][3] = in_d33;
}

SICPPSDK_INLINE CMatrix4::CMatrix4(const CMatrix4& in_matrix4)
{
	m_dMat[0][0] = in_matrix4.m_dMat[0][0];
	m_dMat[0][1] = in_matrix4.m_dMat[0][1];
	m_dMat[0][2] = in_matrix4.m_dMat[0][2];
	m_dMat[0][3] = in_matrix4.m_dMat[0][3];
	m_dMat[1][0] = in_matrix4.m_dMat[1][0];
	m_dMat[1][1] = in_matrix4.m_dMat[1][1];
	m_dMat[1][2] = in_matrix4.m_dMat[1][2];
	m_dMat[1][3] = in_matrix4.m_dMat[1][3];
	m_dMat[2][0] = in_matrix4.m_dMat[2][0];
	m_dMat[2][1] = in_matrix4.m_dMat[2][1];
	m_dMat[2][2] = in_matrix4.m_dMat[2][2];
	m_dMat[2][3] = in_matrix4.m_dMat[2][3];
	m_dMat[3][0] = in_matrix4.m_dMat[3][0];
	m_dMat[3][1] = in_matrix4.m_dMat[3][1];
	m_dMat[3][2] = in_matrix4.m_dMat[3][2];
	m_dMat[3][3] = in_matrix4.m_dMat[3][3];
}

SICPPSDK_INLINE CMatrix4::~CMatrix4() 
{}

SICPPSDK_INLINE CMatrix4& CMatrix4::operator=( const CMatrix4 & in_matrix4 )
{
	m_dMat[0][0] = in_matrix4.m_dMat[0][0];
	m_dMat[0][1] = in_matrix4.m_dMat[0][1];
	m_dMat[0][2] = in_matrix4.m_dMat[0][2];
	m_dMat[0][3] = in_matrix4.m_dMat[0][3];
	m_dMat[1][0] = in_matrix4.m_dMat[1][0];
	m_dMat[1][1] = in_matrix4.m_dMat[1][1];
	m_dMat[1][2] = in_matrix4.m_dMat[1][2];
	m_dMat[1][3] = in_matrix4.m_dMat[1][3];
	m_dMat[2][0] = in_matrix4.m_dMat[2][0];
	m_dMat[2][1] = in_matrix4.m_dMat[2][1];
	m_dMat[2][2] = in_matrix4.m_dMat[2][2];
	m_dMat[2][3] = in_matrix4.m_dMat[2][3];
	m_dMat[3][0] = in_matrix4.m_dMat[3][0];
	m_dMat[3][1] = in_matrix4.m_dMat[3][1];
	m_dMat[3][2] = in_matrix4.m_dMat[3][2];
	m_dMat[3][3] = in_matrix4.m_dMat[3][3];
	return *this;
}

SICPPSDK_INLINE CMatrix4& CMatrix4::operator*=(const CMatrix4& in_matrix4)
{
	return MulInPlace(in_matrix4);
}

SICPPSDK_INLINE CMatrix4&	CMatrix4::SetIdentity()
{
	m_dMat[0][0] = 1.0;
	m_dMat[0][1] = 0.0;
	m_dMat[0][2] = 0.0;
	m_dMat[0][3] = 0.0;
	m_dMat[1][0] = 0.0;
	m_dMat[1][1] = 1.0;
	m_dMat[1][2] = 0.0;
	m_dMat[1][3] = 0.0;
	m_dMat[2][0] = 0.0;
	m_dMat[2][1] = 0.0;
	m_dMat[2][2] = 1.0;
	m_dMat[2][3] = 0.0;
	m_dMat[3][0] = 0.0;
	m_dMat[3][1] = 0.0;
	m_dMat[3][2] = 0.0;
	m_dMat[3][3] = 1.0;
	return *this;
}

SICPPSDK_INLINE void CMatrix4::TransposeInPlace()
{
	Transpose(*this);
}

SICPPSDK_INLINE void CMatrix4::Transpose(const CMatrix4& in_matrix4)
{
	double  dTempMat[4][4];
	for(int nR=0; nR<4; nR++)
		for(int nC=0; nC<4; nC++)
			dTempMat[nR][nC] = in_matrix4.m_dMat[nC][nR];
	Set(dTempMat);
}

SICPPSDK_INLINE CMatrix4&	CMatrix4::MulInPlace(const CMatrix4& in_matrix4)
{
	return Mul(*this,in_matrix4);
}

SICPPSDK_INLINE CMatrix4&	CMatrix4::Mul
(
 const CMatrix4& in_matrix4A, 
 const CMatrix4& in_matrix4B
)
{
	double  dTempMat[4][4];

	for(int nR=0; nR<4; nR++)
		for(int nC=0; nC<4; nC++)
			dTempMat[nR][nC] = 
				in_matrix4A.m_dMat[nR][0] * in_matrix4B.m_dMat[0][nC] +
				in_matrix4A.m_dMat[nR][1] * in_matrix4B.m_dMat[1][nC] +
				in_matrix4A.m_dMat[nR][2] * in_matrix4B.m_dMat[2][nC] +
				in_matrix4A.m_dMat[nR][3] * in_matrix4B.m_dMat[3][nC];

	Set(dTempMat);
	return (*this);
}

SICPPSDK_INLINE void CMatrix4::Get
(	
	double& io_d00, double& io_d01, double& io_d02, double& io_d03,
	double& io_d10, double& io_d11, double& io_d12, double& io_d13,
	double& io_d20, double& io_d21, double& io_d22, double& io_d23,
	double& io_d30, double& io_d31, double& io_d32, double& io_d33
) const
{
	
	io_d00 = m_dMat[0][0];
	io_d01 = m_dMat[0][1];
	io_d02 = m_dMat[0][2];
	io_d03 = m_dMat[0][3];
	io_d10 = m_dMat[1][0];
	io_d11 = m_dMat[1][1];	
	io_d12 = m_dMat[1][2];
	io_d13 = m_dMat[1][3];
	io_d20 = m_dMat[2][0];
	io_d21 = m_dMat[2][1];
	io_d22 = m_dMat[2][2];
	io_d23 = m_dMat[2][3];
	io_d30 = m_dMat[3][0];
	io_d31 = m_dMat[3][1];
	io_d32 = m_dMat[3][2];
	io_d33 = m_dMat[3][3];
}

SICPPSDK_INLINE void CMatrix4::Set
(	
	double in_d00, double in_d01, double in_d02, double in_d03,
	double in_d10, double in_d11, double in_d12, double in_d13,
	double in_d20, double in_d21, double in_d22, double in_d23,
	double in_d30, double in_d31, double in_d32, double in_d33
)
{
	m_dMat[0][0] = in_d00;
	m_dMat[0][1] = in_d01;
	m_dMat[0][2] = in_d02;
	m_dMat[0][3] = in_d03;
	m_dMat[1][0] = in_d10;
	m_dMat[1][1] = in_d11;
	m_dMat[1][2] = in_d12;
	m_dMat[1][3] = in_d13;
	m_dMat[2][0] = in_d20;
	m_dMat[2][1] = in_d21;
	m_dMat[2][2] = in_d22;
	m_dMat[2][3] = in_d23;
	m_dMat[3][0] = in_d30;
	m_dMat[3][1] = in_d31;
	m_dMat[3][2] = in_d32;
	m_dMat[3][3] = in_d33;
}

SICPPSDK_INLINE void CMatrix4::Set(const double in_matrix4[4][4])
{
	m_dMat[0][0] = in_matrix4[0][0];
	m_dMat[0][1] = in_matrix4[0][1];
	m_dMat[0][2] = in_matrix4[0][2];
	m_dMat[0][3] = in_matrix4[0][3];
	m_dMat[1][0] = in_matrix4[1][0];
	m_dMat[1][1] = in_matrix4[1][1];
	m_dMat[1][2] = in_matrix4[1][2];
	m_dMat[1][3] = in_matrix4[1][3];
	m_dMat[2][0] = in_matrix4[2][0];
	m_dMat[2][1] = in_matrix4[2][1];
	m_dMat[2][2] = in_matrix4[2][2];
	m_dMat[2][3] = in_matrix4[2][3];
	m_dMat[3][0] = in_matrix4[3][0];
	m_dMat[3][1] = in_matrix4[3][1];
	m_dMat[3][2] = in_matrix4[3][2];
	m_dMat[3][3] = in_matrix4[3][3];
}


SICPPSDK_INLINE double	CMatrix4::GetValue(short in_sRow,short in_sCol ) const
{
	bool l_bValidIndex =  (	in_sRow >=0 && in_sCol >= 0 &&
							in_sRow <=3 && in_sCol <= 3);	
	assert(l_bValidIndex);

	if(l_bValidIndex)
	{
		return m_dMat[in_sRow][in_sCol];
	}
	return 0.0;

}

SICPPSDK_INLINE void CMatrix4::SetValue(short in_sRow, short in_sCol, double in_dVal )
{
	bool l_bValidIndex =  (	in_sRow >=0 && in_sCol >= 0 &&
							in_sRow <=3 && in_sCol <= 3);

	assert(l_bValidIndex);
	if(l_bValidIndex)
	{
		m_dMat[in_sRow][in_sCol] = in_dVal;
	}
}

SICPPSDK_INLINE bool CMatrix4::Equals(const CMatrix4& in_matrix4) const
{
	return (this == &in_matrix4) ? true :
		m_dMat[0][0] == in_matrix4.m_dMat[0][0] &&
		m_dMat[0][1] == in_matrix4.m_dMat[0][1] &&
		m_dMat[0][2] == in_matrix4.m_dMat[0][2] &&
		m_dMat[0][3] == in_matrix4.m_dMat[0][3] &&
		m_dMat[1][0] == in_matrix4.m_dMat[1][0] &&
		m_dMat[1][1] == in_matrix4.m_dMat[1][1] &&
		m_dMat[1][2] == in_matrix4.m_dMat[1][2] &&
		m_dMat[1][3] == in_matrix4.m_dMat[1][3] &&
		m_dMat[2][0] == in_matrix4.m_dMat[2][0] &&
		m_dMat[2][1] == in_matrix4.m_dMat[2][1] &&
		m_dMat[2][2] == in_matrix4.m_dMat[2][2] &&
		m_dMat[2][3] == in_matrix4.m_dMat[2][3] &&
		m_dMat[3][0] == in_matrix4.m_dMat[3][0] &&
		m_dMat[3][1] == in_matrix4.m_dMat[3][1] &&
		m_dMat[3][2] == in_matrix4.m_dMat[3][2] &&
		m_dMat[3][3] == in_matrix4.m_dMat[3][3];
}

SICPPSDK_INLINE bool CMatrix4::operator ==(const CMatrix4 & in_matrix4 ) const
{
	return Equals( in_matrix4 );
}

SICPPSDK_INLINE bool CMatrix4::operator !=(const CMatrix4 & in_matrix4 ) const
{
	return ! Equals( in_matrix4 );
}



};
};

#endif // __XSIMATRIX4_H__
