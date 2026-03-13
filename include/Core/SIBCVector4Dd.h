//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file SIBCVector4Dd.h
	\brief Defines the CSIBCVector4Dd class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

//******************************************************************************
// Defines
//******************************************************************************
#ifndef _VECTOR4_H_
#define _VECTOR4_H_

//******************************************************************************
// Includes
//******************************************************************************
#include "SIBCMathLib.h"

//******************************************************************************
// Typedefs
//******************************************************************************


//******************************************************************************
// CSIBCVector4Dd | General 3D vector.
//******************************************************************************

/*! \brief General purpose 4D vector class.

	Representation of a 4D vector, defining operations to access, modify and perform calculations
	on 4D vectors. This class uses double precision floating-point numbers for represent its data,
	and in its operations. There are seperate similar classes for 2D and 3D vectors, CSIBCVector2Dd and
	CSIBCVector3Dd, respectively, which also use double precision.

	Furthermore, there is another set of vector classes which use single precision floating-point numbers,
	CSIBCVector2D, CSIBCVector3D and CSIBCVector4D for 2D, 3D and 4D vectors respectively. Quaternions
	represented as 4D vectors are also available in CSIBCQuaternion and CSIBCQuaterniond with
	single precision and double precision, repspectively.
*/
class XSICOREEXPORT CSIBCVector4Dd
{
	// Public members
	public:

		//****************************************
		// IMPLEMENTATION
		//****************************************

		/*!	Default Constructor.
			Constructs a new 4D vector.
		*/
		CSIBCVector4Dd( );

		/*! Constructor.
			Constructs a new 4D vector, with \p in_dX, \p in_dY, \p in_dZ and \p in_dW
			as the X, Y, Z and W component values, respectively.
			\param[in]	in_dX	The value for the X component of the new vector.
			\param[in]	in_dY	The value for the Y component of the new vector.
			\param[in]	in_dZ	The value for the Z component of the new vector.
			\param[in]	in_dW	The value for the W component of the new vector.
		*/
		CSIBCVector4Dd( const double  in_dX, const double in_dY,
			const double  in_dZ, const double in_dW );

		/*! Constructor.
			Constructs a new 4D vector, with the X, Y and Z components taken from \p in_vct,
			and the W component as \p in_dW.
			\param[in]	in_vct	The 3D vector for the X, Y and Z components.
			\param[in]	in_dW	The value of the W component.
		*/
		CSIBCVector4Dd( const CSIBCVector3Dd &in_vct, double in_dW );

		~CSIBCVector4Dd();

		// Individual access to private members:

		/*! Returns the X component of this vector.
			\return	Value of the X component of this vector.
			\sa CSIBCVector4Dd::GetY
			\sa CSIBCVector4Dd::GetZ
			\sa CSIBCVector4Dd::GetW
			\sa CSIBCVector4Dd::SetX
			\sa CSIBCVector4Dd::Get
		*/
		double GetX( void ) const;

		/*! Returns the Y component of this vector.
			\return	Value of the Y component of this vector.
			\sa CSIBCVector4Dd::GetX
			\sa CSIBCVector4Dd::GetZ
			\sa CSIBCVector4Dd::GetW
			\sa CSIBCVector4Dd::SetY
			\sa CSIBCVector4Dd::Get
		*/
		double GetY( void ) const;

		/*! Returns the Z component of this vector.
			\return	Value of the Z component of this vector.
			\sa CSIBCVector4Dd::GetX
			\sa CSIBCVector4Dd::GetY
			\sa CSIBCVector4Dd::GetW
			\sa CSIBCVector4Dd::SetZ
			\sa CSIBCVector4Dd::Get
		*/
		double GetZ( void ) const;

		/*! Returns the W component of this vector.
			\return	Value of the W component of this vector.
			\sa CSIBCVector4Dd::GetX
			\sa CSIBCVector4Dd::GetY
			\sa CSIBCVector4Dd::GetZ
			\sa CSIBCVector4Dd::SetW
			\sa CSIBCVector4Dd::Get
		*/
		double GetW( void ) const;

		/*! Returns the value of the component specified by \p in_nIndex.
			\param[in]	in_nIndex	Index of the component value to get (<TT>0 == X, 1 == Y, 2 == Z, 3 == W</TT>).
			\return	Value of the component specified by \p in_nIndex.
			\sa CSIBCVector4Dd::GetX
			\sa CSIBCVector4Dd::GetY
			\sa CSIBCVector4Dd::GetZ
			\sa CSIBCVector4Dd::GetW
			\sa CSIBCVector4Dd::Set
		*/
		double Get( const int in_nIndex ) const;

		/*! Returns the values of the X, Y, Z and W components of this vector.
			\param[out]	out_dX	Receives the value of the X component
			\param[out]	out_dY	Receives the value of the Y component
			\param[out]	out_dZ	Receives the value of the Z component
			\param[out]	out_dW	Receives the value of the W component
			\sa CSIBCVector4Dd::GetX
			\sa CSIBCVector4Dd::GetY
			\sa CSIBCVector4Dd::GetZ
			\sa CSIBCVector4Dd::GetW
			\sa CSIBCVector4Dd::Set
		*/
		void Get(	double& out_dX, double& out_dY,
					double& out_dZ, double& out_dW	) const;

		/*! Sets the value of the X component of this vector.
			\param[in]	in_dVal	The new value of the X component of this vector.
			\return	Reference to this vector.
			\sa CSIBCVector4Dd::SetY
			\sa CSIBCVector4Dd::SetZ
			\sa CSIBCVector4Dd::SetW
			\sa CSIBCVector4Dd::Set
			\sa CSIBCVector4Dd::GetX
		*/
		CSIBCVector4Dd& SetX ( const double in_dVal );

		/*! Sets the value of the Y component of this vector.
			\param[in]	in_dVal	The new value of the Y component of this vector.
			\return	Reference to this vector.
			\sa CSIBCVector4Dd::SetX
			\sa CSIBCVector4Dd::SetZ
			\sa CSIBCVector4Dd::SetW
			\sa CSIBCVector4Dd::Set
			\sa CSIBCVector4Dd::GetY
		*/
		CSIBCVector4Dd& SetY ( const double in_dVal );

		/*! Sets the value of the Z component of this vector.
			\param[in]	in_dVal	The new value of the Z component of this vector.
			\return	Reference to this vector.
			\sa CSIBCVector4Dd::SetX
			\sa CSIBCVector4Dd::SetY
			\sa CSIBCVector4Dd::SetW
			\sa CSIBCVector4Dd::Set
			\sa CSIBCVector4Dd::GetZ
		*/
		CSIBCVector4Dd& SetZ ( const double in_dVal );

		/*! Sets the value of the W component of this vector.
			\param[in]	in_dVal	The new value of the W component of this vector.
			\return	Reference to this vector.
			\sa CSIBCVector4Dd::SetX
			\sa CSIBCVector4Dd::SetY
			\sa CSIBCVector4Dd::SetZ
			\sa CSIBCVector4Dd::Set
			\sa CSIBCVector4Dd::GetW
		*/
		CSIBCVector4Dd& SetW ( const double in_dVal );

		/*! Sets the component given by \p in_nIndex to \p in_dVal.
			\param[in]	in_nIndex	The index of the component to set (0 == X, 1 == Y, 2 == Z).
			\param[in]	in_dVal		The value to set the component to.
			\return	Reference to this vector.
			\sa CSIBCVector4Dd::Set
			\sa CSIBCVector4Dd::Get
		*/
		CSIBCVector4Dd& Set ( const int in_nIndex, const double in_dVal );

		/*!	Sets the X, Y, Z and W components of the vector.
			\param[in]	in_dX	The value for the X component of the vector.
			\param[in]	in_dY	The value for the Y component of the vector.
			\param[in]	in_dZ	The value for the Z component of the vector.
			\param[in]	in_dW	The value for the W component of the vector.
			\return	Reference to this vector.
			\sa CSIBCVector4Dd::Set
			\sa CSIBCVector4Dd::SetX
			\sa CSIBCVector4Dd::SetY
			\sa CSIBCVector4Dd::SetZ
			\sa CSIBCVector4Dd::SetW
			\sa CSIBCVector4Dd::Get
		*/
		CSIBCVector4Dd& Set( const double in_dX, const double in_dY,
			const double in_dZ, const double in_dW );

		/*! Sets the value of this vector to the value of \p in_vct.
			\param[in]	in_vct	Vector to set this vector equal to.
			\return	Reference to this vector.
			\sa CSIBCVector4Dd::Set
			\sa CSIBCVector4Dd::SetX
			\sa CSIBCVector4Dd::SetY
			\sa CSIBCVector4Dd::SetZ
			\sa CSIBCVector4Dd::Get
		*/
		void Set( const CSIBCVector4Dd& in_vct);

		/*!	Sets all the components of this vector to zero.
			\return	Reference to this vector.
			\sa CSIBCVector4Dd::IsNull
			\sa CSIBCVector4Dd::Set
		*/
		CSIBCVector4Dd& SetNull( void );

		/*!	Determines whether all components of this vector are equal to zero. Since this method
			uses floating-point comparison, a threshhold value of \p in_dEpsilon is used for equality
			comparison.
			\param[in]	in_dEpsilon	Floating-point comparison error range. Defaults to #PICO_EPS.
			\retval true if the vector is null
			\retval false otherwise
			\sa CSIBCVector4Dd::SetNull
			\sa CSIBCVector4Dd::AreAlmostEqual
		*/
		bool IsNull( const double in_dEpsilon=PICO_EPS ) const;

		/*! Sets each component of this vector to be at least \p in_dEpsilon (in absolute value).
			This does not change the sign of the component.
			\param[in]	in_dEpsilon	Value for the minimum absolute value of each component. Defaults to #PICO_EPS.
			\return	Reference to this vector
			\sa CSIBCVector4Dd::Set
		*/
		CSIBCVector4Dd& SetMinimal ( const double in_dEpsilon=PICO_EPS );

		/*! Determines whether all corresponding components of the \p in_vct1 and
			\p in_vct2 are equal. Since this method uses floating-point comparison, a threshhold
			value of \p in_dEpsilon is used for equality comparison.
			\param[in]	in_vct1	First vector for equality comparison.
			\param[in]	in_vct2	Second vector for equality comparison.
			\param[in]	in_dEpsilon	Floating-point comparison error range. Defaults to #PICO_EPS.
			\retval true if the vectors are equal
			\retval false otherwise
			\sa CSIBCVector4Dd::operator==
			\sa CSIBCVector4Dd::operator!=
		*/
		friend  bool AreAlmostEqual( const CSIBCVector4Dd& in_vct1,
			const CSIBCVector4Dd& in_vct2, const double in_dEpsilon = PICO_EPS ) ;

		/*! Determines whether all corresponding components of this vector and \p in_vct are
			exactly equal.
			\param[in]	in_vct	The vector to compare equality with.
			\retval true if the vectors are exactly equal
			\retval false otherwise
			\sa CSIBCVector4Dd::AreAlmostEqual
			\sa CSIBCVector4Dd::operator!=
		*/
		bool operator == ( const CSIBCVector4Dd& in_vct ) const;

		/*! Determines whether any corresponding components of this vector and \p in_vct are
			different.
			\param[in]	in_vct	The vector to compare inequality with.
			\retval true if the vectors differ in any component
			\retval false otherwise
			\sa CSIBCVector4Dd::AreAlmostEqual
			\sa CSIBCVector4Dd::operator==
		*/
		bool operator != ( const CSIBCVector4Dd& in_vct ) const;

		/*!	Sets this vector to the negative of \p in_vct.
			\param[in]	in_vct	Vector containing the negative value for this vector.
			\return	Reference to this vector.
			\sa	CSIBCVector4Dd::Negate
		*/
		CSIBCVector4Dd& Negate( const CSIBCVector4Dd& in_vct );

		/*! Sets this vector to its negative.
			\return	Reference to this vector.
			\sa CSIBCVector4Dd::Negate
		*/
		CSIBCVector4Dd& Negate( void );

		/*! Returns the squared length of this vector.
			\return	The squared length of this vector.
			\sa CSIBCVector4Dd::GetLength
			\sa CSIBCVector4Dd::SetLength
			\sa CSIBCVector4Dd::Normalize
		*/
		double GetSquaredLength( void ) const;

		/*! Returns the length of this vector.
			\return	The squared length of this vector.
			\sa CSIBCVector4Dd::GetSquaredLength
			\sa CSIBCVector4Dd::SetLength
			\sa CSIBCVector4Dd::Normalize
		*/
		double GetLength( void ) const;

		/*!	Sets the length of this vector.
			\param[in]	in_dLength	New length for this vector.
			\retval true if the length was set properly
			\retval false if the length of the current vector is zero
			\sa CSIBCVector4Dd::Normalize
			\sa CSIBCVector4Dd::GetLength
		*/
		bool SetLength( const double in_dLength );

		/*!	Sets the vector to be a unit vector.
			\retval true if the length was set properly
			\retval false if the length of the current vector is zero
			\sa CSIBCVector4Dd::SetLength
			\sa CSIBCVector4Dd::GetLength
		*/
		bool Normalize( void );


		// Efficient arithmetic operations.


		/*! Adds this vector and \p in_vct. The result is stored in this vector.
			\param[in]	in_vct	Vector to add to this vector.
			return	CSIBCVector4Dd&	Reference to this vector.
			\sa CSIBCVector4Dd::Add
			\sa CSIBCVector4Dd::Sub
		*/
		CSIBCVector4Dd& Add( const CSIBCVector4Dd& in_vct  );

		/*! Adds \p in_vct1 and \p in_vct2. The result is stored in this vector.
			\param[in]	in_vct1	First vector in the addition.
			\param[in]	in_vct2	Second vector in the addition.
			\return	Reference to this vector.
			\sa CSIBCVector4Dd::Add
			\sa CSIBCVector4Dd::Sub
		*/
		CSIBCVector4Dd& Add( const CSIBCVector4Dd& in_vct1, const CSIBCVector4Dd& in_vct2);

		/*! Subtracts \p in_vct from this vector. The result is stored in this vector.
			\param[in]	in_vct	Vector to subtract from this vector.
			\return	Reference to this vector.
			\sa CSIBCVector4Dd::Sub
			\sa CSIBCVector4Dd::Add
		*/
		CSIBCVector4Dd& Sub( const CSIBCVector4Dd& in_vct );

		/*! Subtracts \p in_vct2 from \p in_vct1. The result is stored in this vector.
			\param[in]	in_vct1	First vector for the subtraction.
			\param[in]	in_vct2	Second vector for the subtraction.
			\return	Reference to this vector.
			\sa CSIBCVector4Dd::Sub
			\sa CSIBCVector4Dd::Add
		*/
		CSIBCVector4Dd& Sub( const CSIBCVector4Dd& in_vct1, const CSIBCVector4Dd& in_vct2);

		/*! Multiplies each component of this vector by \p in_dFactor. The result is stored
			in this vector.
			\param[in]	in_dFactor	Factor to multiply the components of this vector by.
			\return	Reference to this vector.
			\sa CSIBCVector4Dd::Mul
			\sa CSIBCVector4Dd::Div
			\sa CSIBCVector4Dd::MulComp
			\sa CSIBCVector4Dd::DivComp
		*/
		CSIBCVector4Dd& Mul( const double in_dFactor );

		/*! Multiplies each of the components in \p in_vct by \p in_dFactor. The result
			is stored in this vector.
			\param[in]	in_dFactor	Factor to multiply the components of \p in_vct by.
			\param[in]	in_vct		Vector to multiply.
			\return	Reference to this vector.
			\sa CSIBCVector4Dd::Mul
			\sa CSIBCVector4Dd::Div
			\sa CSIBCVector4Dd::MulComp
			\sa CSIBCVector4Dd::DivComp
		*/
		CSIBCVector4Dd& Mul( const double in_dFactor, const CSIBCVector4Dd& in_vct );

		/*!	Multiplies each of the components in \p in_vct by \p in_dFactor. The result
			is stored in this vector.
			\param[in]	in_vct		Vector to multiply.
			\param[in]	in_dFactor	Factor to multiply the components of \p in_vct by.
			\return	Reference to this vector.
			\sa CSIBCVector4Dd::Mul
			\sa CSIBCVector4Dd::Div
			\sa CSIBCVector4Dd::MulComp
			\sa CSIBCVector4Dd::DivComp
		*/
		CSIBCVector4Dd& Mul( const CSIBCVector4Dd& in_vct, const double in_dFactor );

		/*!	Divides each component of this vector by \p in_dFactor. The result is stored
			in this vector.
			\param[in]	in_dFactor	Factor to divide the components of this vector by.
			\return	Reference to this vector.
			\sa CSIBCVector4Dd::Div
			\sa CSIBCVector4Dd::Mul
			\sa CSIBCVector4Dd::DivComp
			\sa CSIBCVector4Dd::MulComp
		*/
		CSIBCVector4Dd& Div( const double in_dFactor );

		/*!	Divides each component of \p in_vct by \p in_dFactor. The result is stored
			in this vector.
			\param[in]	in_vct		Vector to divide.
			\param[in]	in_dFactor	Factor to divide the components of this vector by.
			\return	Reference to this vector.
			\sa CSIBCVector4Dd::Div
			\sa CSIBCVector4Dd::Mul
			\sa CSIBCVector4Dd::DivComp
			\sa CSIBCVector4Dd::MulComp
		*/
		CSIBCVector4Dd& Div( const CSIBCVector4Dd& in_vct, const double in_dFactor );

		/*!	Multiplies each component of \p in_vct1 by the corresponding component in \p in_vct2.
			The result is stored in this vector.
			\param[in]	in_vct1	First vector to multiply the components of.
			\param[in]	in_vct2	Second vector to multiply the components of.
			\return	Reference to this vector.
			\sa CSIBCVector4Dd::MulComp
			\sa CSIBCVector4Dd::DivComp
			\sa CSIBCVector4Dd::Mul
			\sa CSIBCVector4Dd::Div
		*/
		CSIBCVector4Dd& MulComp( const CSIBCVector4Dd& in_vct1, const CSIBCVector4Dd& in_vct2  );

		/*!	Multiplies each component of \p in_vct by the corresponding component in this vector.
			The result is stored in this vector.
			\param[in]	in_vct	Vector to multiply the components of.
			\return	Reference to this vector.
			\sa CSIBCVector4Dd::MulComp
			\sa CSIBCVector4Dd::DivComp
			\sa CSIBCVector4Dd::Mul
			\sa CSIBCVector4Dd::Div
		*/
		CSIBCVector4Dd& MulComp( const CSIBCVector4Dd& in_vct );

		/*!	Divides each component of this vector by the corresponding component in \p in_vct.
			The result is stored in this vector.
			\param[in]	in_vct	Vector to divide the components of this vector by.
			\return	Reference to this vector.
			\sa CSIBCVector4Dd::DivComp
			\sa CSIBCVector4Dd::MulComp
			\sa CSIBCVector4Dd::Div
			\sa CSIBCVector4Dd::Mul
		*/
		CSIBCVector4Dd& DivComp( const CSIBCVector4Dd& in_vct );

		/*!	Divides each component of \p in_vct1 by the corresponding component in \p in_vct2.
			The result is stored in this vector.
			\param[in]	in_vct1	Vector to be divided by the components of \p in_vct2
			\param[in]	in_vct2	Vector to divide the components of \p in_vct1 by.
			\return	Reference to this vector.
			\sa CSIBCVector4Dd::DivComp
			\sa CSIBCVector4Dd::MulComp
			\sa CSIBCVector4Dd::Div
			\sa CSIBCVector4Dd::Mul
		*/
		CSIBCVector4Dd& DivComp( const CSIBCVector4Dd& in_vct1, const CSIBCVector4Dd& in_vct2 );


		/*! Multiplies a this vector (as a row vector), into a 4x4 matrix
			\p in_mat (this * \p in_mat), and stores the result in this vector.
			\param[in]	in_mat	Matrix to multiply (on the right).
			\return	Reference to this vector.
			\sa CSIBCVector4Dd::Mul
			\sa CSIBCVector4Dd::MulComp
			\sa CSIBCVector4Dd::DivComp
			\sa CSIBCVector4Dd::Div
		*/
		CSIBCVector4Dd& Mul( const CSIBCMatrix44d& in_mat );

		/*! Multiplies a row vector \p in_vct, into a 4x4 matrix \p in_mat
			(\p in_vct * \p in_mat), and stores the result in this vector.
			\param[in]	in_vct	Row vector to multiply (on the left).
			\param[in]	in_mat	Matrix to multiply (on the right).
			\return	Reference to this vector.
			\sa CSIBCVector4Dd::Mul
			\sa CSIBCVector4Dd::MulComp
			\sa CSIBCVector4Dd::DivComp
			\sa CSIBCVector4Dd::Div
		*/
		CSIBCVector4Dd& Mul( const CSIBCVector4Dd& in_vct, const CSIBCMatrix44d& in_mat );

		/*! Multiplies a 4x4 matrix \p in_mat, into a column vector, \p in_vct
			(\p in_mat * \p in_vct), and stores the result in this vector.
			\param[in]	in_mat	Matrix to multiply (on the left).
			\param[in]	in_vct	Column vector to multiply (on the right).
			\return	Reference to this vector.
			\sa CSIBCVector4Dd::Mul
			\sa CSIBCVector4Dd::MulComp
			\sa CSIBCVector4Dd::DivComp
			\sa CSIBCVector4Dd::Div
		*/
		CSIBCVector4Dd& Mul( const CSIBCMatrix44d& in_mat, const CSIBCVector4Dd& in_vct );

		// TODO  Remove set of functions to multiply by CSIBCXfoMatd as soon as
		//       CSIBCXfoMatd and CSIBCMatrix44d will both derived public from a
		//       common base matrix class.

		/*! Multiplies a row vector \p in_vct, into a 4x4 transformation matrix \p in_mat
			(\p in_vct * \p in_mat), and stores the result in this vector.
			\param[in]	in_vct	Row vector to multiply (on the left).
			\param[in]	in_mat	Rotation matrix to multiply (on the right).
			\return	Reference to this vector.
			\sa CSIBCVector4Dd::Mul
			\sa CSIBCVector4Dd::MulComp
			\sa CSIBCVector4Dd::DivComp
			\sa CSIBCVector4Dd::Div
		*/
		CSIBCVector4Dd& Mul( const CSIBCVector4Dd& in_vct, const CSIBCXfoMatd& in_mat );


		/*! Multiplies a 4x4 transformation matrix \p in_mat into a column vector \p in_vct,
			(\p in_mat * \p in_vct), and stores the result in this vector.
			\param[in]	in_mat	Rotation matrix to multiply (on the left).
			\param[in]	in_vct	Column vector to multiply (on the right).
			\return	Reference to this vector.
			\sa CSIBCVector4Dd::Mul
			\sa CSIBCVector4Dd::MulComp
			\sa CSIBCVector4Dd::DivComp
			\sa CSIBCVector4Dd::Div
		*/
		CSIBCVector4Dd& Mul( const CSIBCXfoMatd& in_mat, const CSIBCVector4Dd& in_vct );


		/*!	Computes the dot product between the vectors \p in_vct1 and \p in_vct2.
			\param[in]	in_vct1	First vector in the dot product.
			\param[in]	in_vct2	Second vector in the dot product.
			\return	The dot product between \p in_vct1 and \p in_vct2.
		*/
		friend double GetDot( const CSIBCVector4Dd& in_vct1,
			const CSIBCVector4Dd& in_vct2 );

		/*!	Computes the distance between two points in 3D space given by
			\p in_pnt1 and \p in_pnt2.
			\param[in]	in_pnt1	Starting point for distance calculation.
			\param[in]	in_pnt2	Ending point for distance calculation.
			\return	The scalar distance between the two points, in 3D space.
			\sa CSIBCVector4Dd::GetSquaredDistance
		*/
		friend double GetDistance( const CSIBCVector4Dd& in_pnt1,
			const CSIBCVector4Dd& in_pnt2 );

		/*! Computes the squared distance between two points in 3D space given by
			\p in_pnt1 and \p in_pnt2.
			\param[in]	in_pnt1	Starting point for distance calculation.
			\param[in]	in_pnt2	Ending point for distance calculation.
			\return	The squared scalar distance between the two points, in 3D space.
			\sa CSIBCVector4Dd::GetDistance
		*/
		friend double GetSquaredDistance( const CSIBCVector4Dd& in_pnt1,
			const CSIBCVector4Dd& in_pnt2 );

		/*! Projects this vector onto \p in_vct. The projected vector is stored in this vector.
			\param[in]	in_vct	Vector to project this vector onto.
			\retval true if the vector is projected
			\retval false if the input vector is the null vector, in which case this
				vector keeps its original value.
			\sa CSIBCVector4Dd::SetOrthoProj
		*/
		bool SetProjection ( const CSIBCVector4Dd& in_vct );

	// Private Members
	private:

		//****************************************
		// ATTRIBUTES
		//****************************************
		// double | CSIBCVector4Dd | m_dX | X component of the vector.
		// double | CSIBCVector4Dd | m_dY | Y component of the vector.
		// double | CSIBCVector4Dd | m_dZ | Z component of the vector.
		double  m_dX, m_dY, m_dZ, m_dW;

		// Disable copy constructor and operator =
		// CSIBCVector4Dd		| The copy Constructor
		CSIBCVector4Dd( const CSIBCVector4Dd& in_vct );
		// operator=			| Assigment operator.
		CSIBCVector4Dd& operator = ( const CSIBCVector4Dd& in_vct );

};

//******************************************************************************
//
// Author : Michel Carigan
// Date  : 08/05/96
//
// CSIBCVector4Dd& | CSIBCVector4Dd | SetMinimal |   Sets each component to be at least
//        epsilon (in absolute). A component is changed only if smaller than epsilon.
//
// CSIBCVector4Dd& SetMinimal( const double in_dEpsilon = PICO_EPS )
//
// double | in_dEpsilon | Specify the user minimal value. If not given, the default
//                                        value will be PICO_EPS
//
// A reference on this.
//
//
// This function works like the macro _SI_VCT_EPS in v3.51
// That is, each component are set to eps only if they are less than epsilon.
// In that case the sign is unchanged.
//
//******************************************************************************
inline  CSIBCVector4Dd&
CSIBCVector4Dd::SetMinimal
    (
        const double in_dEpsilon /* = PICO_EPS */
    )
{
    if( fabs(m_dX) < in_dEpsilon )
        m_dX = ( ( m_dX >= 0 ) ? in_dEpsilon : -in_dEpsilon ) ;
    if( fabs(m_dY) < in_dEpsilon )
        m_dY = ( ( m_dY >= 0 ) ? in_dEpsilon : -in_dEpsilon ) ;
    if( fabs(m_dZ) < in_dEpsilon )
        m_dZ = ( ( m_dZ >= 0 ) ? in_dEpsilon : -in_dEpsilon ) ;
    if( fabs(m_dW) < in_dEpsilon )
        m_dW = ( ( m_dW >= 0 ) ? in_dEpsilon : -in_dEpsilon ) ;
    return *this;
}

#endif
