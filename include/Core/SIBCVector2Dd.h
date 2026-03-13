//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file SIBCVector2Dd.h
	\brief Defines the CSIBCVector2Dd class

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
#ifndef _VECTOR2_H_
#define _VECTOR2_H_

//******************************************************************************
// Includes
//******************************************************************************
#include "SIBCMathLib.h"

//******************************************************************************
// Typedefs
//******************************************************************************

//******************************************************************************
// CSIBCVector2Dd | General 2D vector.
//******************************************************************************

/*! \brief General purpose 2D vector class.

	Representation of a 2D vector, defining operations to access, modify and perform calculations
	on 2D vectors. This class uses double precision floating-point numbers for represent its data,
	and in its operations. There are seperate similar classes for 3D and 4D vectors, CSIBCVector3Dd and
	CSIBCVector4Dd, respectively, which also use double precision.

	Furthermore, there is another set of vector classes which use single precision floating-point numbers,
	CSIBCVector2D, CSIBCVector3D and CSIBCVector4D for 2D, 3D and 4D vectors respectively. Quaternions
	represented as 4D vectors are also available in CSIBCQuaternion and CSIBCQuaterniond with
	single precision and double precision, repspectively.
*/
class XSICOREEXPORT CSIBCVector2Dd
{
	// Public members
	public:

		//****************************************
		// IMPLEMENTATION

		/*! Default constructor.
			Sets the values of each component of this vector to zero.
		*/
		CSIBCVector2Dd( );

		/*! Constructor.
			Sets the new vector to have \p i_fX and \p i_fY for its X and Y components, respectively.
			\param[in]	in_dX	The value for the X component of the new vector.
			\param[in]	in_dY	The value for the Y component of the new vector.
		*/
		CSIBCVector2Dd( const double  in_dX, const double in_dY );

		/*! Constructor.
			Sets the new vector to have the X and Y values contained in the array \p in_dXY.
			\param[in]	in_dXY	Array containing the X and Y values for the new vector.
		*/
		CSIBCVector2Dd( const double in_dXY[2] );

		/*! Constructor.
			Sets the component determined by \p in_nIndex to \p in_dVal, and the other component to zero.
			\param[in]	in_nIndex	Index of the component to set to \p in_dVal. (<TT>0 == X, 1 == Y</TT>).
			\param[in]	in_dVal		Value to set
		*/
		CSIBCVector2Dd( int in_nIndex, double in_dVal );

		~CSIBCVector2Dd();

		/*! Returns an array containing the X and Y components of the vector. Note that
			the pointer obtained from this call should not be freed. Any modification to
			the values in the array results in a direct modification of this object.
			\return	Array containing the X and Y components of this vector.
			\sa CSIBCVector2Dd::Get
		*/
		const double * GetArray() const;

		/*! Returns the X component of this vector.
			\return	Value of the X component of this vector.
			\sa CSIBCVector2Dd::GetY
			\sa CSIBCVector2Dd::SetX
			\sa CSIBCVector2Dd::Get
		*/
		double GetX( void ) const;

		/*! Returns the Y component of this vector.
			\return	Value of the Y component of this vector.
			\sa CSIBCVector2Dd::GetX
			\sa CSIBCVector2Dd::SetY
			\sa CSIBCVector2Dd::Get
		*/
		double GetY( void ) const;

		/*! Returns the value of the component specified by \p in_nIndex.
			\param[in]	in_nIndex	Index of the component value to get (0 == X, 1 == Y).
			\return	Value of the component specified by \p in_nIndex.
			\sa CSIBCVector2Dd::GetX
			\sa CSIBCVector2Dd::GetY
			\sa CSIBCVector2Dd::Set
		*/
		double Get( const int in_nIndex ) const;

		/*! Returns the values of the X and Y components of this vector.
			\param[out]	out_dX	Receives the value of the X component
			\param[out]	out_dY	Receives the value of the Y component
			\sa CSIBCVector2Dd::GetX
			\sa CSIBCVector2Dd::GetY
			\sa CSIBCVector2Dd::Set
		*/
		void	Get( double& out_dX, double& out_dY ) const;

		/*!	Returns the value of largest component of the vector.
			\param[in]	in_bInAbs	true if comparisons should be made with absolute values,
				false if comparisons should be made without absolute values. Defaults to true.
			\return	The value (or absolute value if \p in_bInAbs is true) of the largest component of the vector.
			\sa CSIBCVector2Dd::GetIndexOfMaxComponent
			\sa CSIBCVector2Dd::GetMinComponent
		*/
		double GetMaxComponent( bool in_bInAbs = true ) const;

		/*!	Returns the value of smallest component of the vector.
			\param[in]	in_bInAbs	true if comparisons should be made with absolute values,
				false if comparisons should be made without absolute values. Defaults to true.
			\return	The value (or absolute value if \p in_bInAbs is true) of the smallest component of the vector.
			\sa CSIBCVector2Dd::GetIndexOfMinComponent
			\sa CSIBCVector2Dd::GetMaxComponent
		*/
		double GetMinComponent( bool in_bInAbs = true ) const;

		/*! Returns the index of the largest component of the vector.
			\param[in]	in_bInAbs	true if comparisons should be made with absolute values,
				false if comparisons should be made without absolute values. Defaults to true.
			\return	Index of the largest component of the vector (<TT>0 == X, 1 == Y</TT>).
			\sa CSIBCVector2Dd::GetMaxComponent
			\sa CSIBCVector2Dd::GetIndexOfMinComponent
		*/
		int GetIndexOfMaxComponent( bool in_bInAbs = true ) const;

		/*! Returns the index of the smallest component of the vector.
			\param[in]	in_bInAbs	true if comparisons should be made with absolute values,
				false if comparisons should be made without absolute values. Defaults to true.
			\return	Index of the smallest component of the vector (<TT>0 == X, 1 == Y</TT>).
			\sa CSIBCVector2Dd::GetMinComponent
			\sa CSIBCVector2Dd::GetIndexOfMaxComponent
		*/
		int GetIndexOfMinComponent( bool in_bInAbs = true ) const;

		/*! Sets the value of the X component of this vector.
			\param[in]	in_dVal	The new value of the X component of this vector.
			\return	Reference to this vector.
			\sa CSIBCVector2Dd::SetY
			\sa CSIBCVector2Dd::Set
			\sa CSIBCVector2Dd::GetX
		*/
		CSIBCVector2Dd& SetX ( const double in_dVal );

		/*! Sets the value of the Y component of this vector.
			\param[in]	in_dVal	The new value of the Y component of this vector.
			\return	Reference to this vector.
			\sa CSIBCVector2Dd::SetX
			\sa CSIBCVector2Dd::Set
			\sa CSIBCVector2Dd::GetY
		*/
		CSIBCVector2Dd& SetY ( const double in_dVal );

		/*! Sets the value of this vector to the value of \p in_vct.
			\param[in]	in_vct	Vector to set this vector equal to.
			\return	Reference to this vector.
			\sa CSIBCVector2Dd::Set
			\sa CSIBCVector2Dd::SetX
			\sa CSIBCVector2Dd::SetY
			\sa CSIBCVector2Dd::Get
		*/
		CSIBCVector2Dd& Set( const CSIBCVector2Dd& in_vct );

		/*! Sets the component given by \p in_nIndex to \p in_dVal.
			\param[in]	in_nIndex	The index of the component to set (<TT>0 == X, 1 == Y</TT>).
			\param[in]	in_dVal		The value to set the component to.
			\return	Reference to this vector.
			\sa CSIBCVector2Dd::Set
			\sa CSIBCVector2Dd::Get
		*/
		CSIBCVector2Dd& Set( const int in_nIndex, const double in_dVal );

		/*!	Sets the X and Y components of the vector.
			\param[in]	in_dX	The value for the X component of the vector.
			\param[in]	in_dY	The value for the Y component of the vector.
			\return	Reference to this vector.
			\sa CSIBCVector2Dd::Set
			\sa CSIBCVector2Dd::GetX
			\sa CSIBCVector2Dd::GetY
			\sa CSIBCVector2Dd::Get
		*/
		CSIBCVector2Dd& Set( const double in_dX, const double in_dY );

		/*!	Sets all the components of this vector to zero.
			\return	Reference to this vector.
			\sa CSIBCVector2Dd::IsNull
			\sa CSIBCVector2Dd::Set
		*/
		CSIBCVector2Dd&	SetNull( void );

		/*!	Determines whether all components of this vector are equal to zero. Since this method uses floating-point
			comparison, a threshhold value of \p in_dEpsilon is used for equality comparison.
			\param[in]	in_dEpsilon	Floating-point comparison error range. Defaults to #PICO_EPS.
			\retval true if the vector is null
			\retval false otherwise
			\sa CSIBCVector2Dd::SetNull
			\sa CSIBCVector2Dd::AreAlmostEqual
		*/
		bool IsNull( const double in_dEpsilon=PICO_EPS ) const;

		/*! Ensures that each of the components of this vector are at least as large as
			\p in_dEpsilon. If not, they are set to \p in_dEpsilon. Note that if
			comparisons are done with absolute values, the sign of the vector components
			does not change, if they are less than \p in_dEpsilon.

			\param[in]	in_bInAbs	true if comparisons are done with absolute values,
				false if comparisons are done without absolute values. Defaults to true.
			\param[in]	in_dEpsilon	Minimal value for components of this vector. Defaults to #PICO_EPS.
			\return	Reference to this vector.
			\sa	CSIBCVector2Dd::SetMinimal
			\sa CSIBCVector2Dd::AreAlmostEqual
		*/
		CSIBCVector2Dd&	SetMinimal ( bool in_bInAbs = true, const double in_dEpsilon=PICO_EPS );

		/*! Ensures that each of the components of this vector are at least as large as
			the components of \p in_vct. If they are not, they are set to be equal to the
			component of \p in_vct. Note that if comparisons are done with absolute values,
			the sign of the vector components does not change, if they are less than the
			corresponding component values in \p in_vct.

			\param[in]	in_vct		Vector containing minimal component values.
			\param[in]	in_bInAbs	true if comparisons are done with absolute values,
					false if comparisons are done without absolute values. Defaults to true.
			\return	Reference to this vector.
			\sa CSIBCVector2Dd::SetMinimal
			\sa CSIBCVector2Dd::AreAlmostEqual
		*/
		CSIBCVector2Dd&	SetMinimal ( const CSIBCVector2Dd & in_vct, bool in_bInAbs = true );


		/*! Determines whether all corresponding components of the \p in_vct1 and
			\p in_vct2 are equal. Since this method uses floating-point comparison, a threshhold
			value of \p in_dEpsilon is used for equality comparison.
			\param[in]	in_vct1	First vector for equality comparison.
			\param[in]	in_vct2	Second vector for equality comparison.
			\param[in]	in_dEpsilon	Floating-point comparison error range. Defaults to #PICO_EPS.
			\retval true if the vectors are equal
			\retval false otherwise
			\sa CSIBCVector2Dd::operator==
			\sa CSIBCVector2Dd::operator!=
		*/
		friend bool	AreAlmostEqual( const CSIBCVector2Dd& in_vct1,
									const CSIBCVector2Dd& in_vct2,
									const double in_dEpsilon = PICO_EPS );


		/*! Determines whether all corresponding components of this vector and \p in_vct are
			exactly equal.
			\param[in]	in_vct	The vector to compare equality with.
			\retval true if the vectors are exactly equal
			\retval false otherwise
			\sa CSIBCVector2Dd::AreAlmostEqual
			\sa CSIBCVector2Dd::operator!=
		*/
		bool operator == ( const CSIBCVector2Dd& in_vct ) const;

		/*! Determines whether any corresponding components of this vector and \p in_vct are
			different.
			\param[in]	in_vct	The vector to compare inequality with.
			\retval true if the vectors differ in any component
			\retval false otherwise
			\sa CSIBCVector2Dd::AreAlmostEqual
			\sa CSIBCVector2Dd::operator==
		*/
		bool operator != ( const CSIBCVector2Dd& in_vct ) const;

		/*!	Sets this vector to the negative of \p in_vct.
			\param	in_vct	Vector containing the negative value for this vector.
			\return Reference to this vector.
			\sa	CSIBCVector2Dd::Negate
		*/
		CSIBCVector2Dd&	Negate( const CSIBCVector2Dd& in_vct );

		/*! Sets this vector to its negative.
			\return	Reference to this vector.
			\sa CSIBCVector2Dd::Negate
		*/
		CSIBCVector2Dd&	Negate( void );

		/*! Gets the squared length of this vector.
			\return The squared length of this vector.
			\sa CSIBCVector2Dd::GetLength
			\sa CSIBCVector2Dd::SetLength
			\sa CSIBCVector2Dd::Normalize
		*/
		double GetSquaredLength( void ) const;

		/*! Returns the length of this vector.
			\return	The squared length of this vector.
			\sa CSIBCVector2Dd::GetSquaredLength
			\sa CSIBCVector2Dd::SetLength
			\sa CSIBCVector2Dd::Normalize
		*/
		double GetLength( void ) const;

		/*!	Sets the length of this vector.
			\param[in]	in_dLength	New length for this vector.
			\retval true if the length was set properly
			\retval false if the length of the current vector is zero
			\sa CSIBCVector2Dd::Normalize
			\sa CSIBCVector2Dd::GetLength
		*/
		bool SetLength( const double in_dLength );

		/*!	Sets the vector to be a unit vector.
			\retval true if the length was set properly
			\retval false if the length of the current vector is zero
			\sa CSIBCVector2Dd::SetLength
			\sa CSIBCVector2Dd::GetLength
		*/
		bool Normalize( void );

		// Efficient arithmetic operations.

		/*! Adds this vector and \p in_vct. The result is stored in this vector.
			\param[in]	in_vct	Vector to add to this vector.
			return	Reference to this vector.
			\sa CSIBCVector2Dd::Add
			\sa CSIBCVector2Dd::Sub
		*/
		CSIBCVector2Dd& Add( const CSIBCVector2Dd&  in_vct	);

		/*! Adds \p in_vct1 and \p in_vct2. The result is stored in this vector.
			\param[in]	in_vct1	First vector in the addition.
			\param[in]	in_vct2	Second vector in the addition.
			\return	Reference to this vector.
			\sa CSIBCVector2Dd::Add
			\sa CSIBCVector2Dd::Sub
		*/
		CSIBCVector2Dd& Add( const CSIBCVector2Dd&  in_vct1, const CSIBCVector2Dd& in_vct2 );

		/*! Subtracts \p in_vct from this vector. The result is stored in this vector.
			\param[in]	in_vct	Vector to subtract from this vector.
			\return	Reference to this vector.
			\sa CSIBCVector2Dd::Sub
			\sa CSIBCVector2Dd::Add
		*/
		CSIBCVector2Dd& Sub( const CSIBCVector2Dd&  in_vct );

		/*! Subtracts \p in_vct2 from \p in_vct1. The result is stored in this vector.
			\param[in]	in_vct1	First vector for the subtraction.
			\param[in]	in_vct2	Second vector for the subtraction.
			\return	Reference to this vector.
			\sa CSIBCVector2Dd::Sub
			\sa CSIBCVector2Dd::Add
		*/
		CSIBCVector2Dd& Sub( const CSIBCVector2Dd&  in_vct1, const CSIBCVector2Dd& in_vct2 );

		/*! Multiplies each component of this vector by \p in_dFactor. The result is stored
			in this vector.
			\param[in]	in_dFactor	Factor to multiply the components of this vector by.
			\return	Reference to this vector.
			\sa CSIBCVector2Dd::Mul
			\sa CSIBCVector2Dd::Div
			\sa CSIBCVector2Dd::MulComp
			\sa CSIBCVector2Dd::DivComp
		*/
		CSIBCVector2Dd& Mul( const double in_dFactor );

		/*! Multiplies each of the components in \p in_vct by \p in_dFactor. The result
			is stored in this vector.
			\param[in]	in_dFactor	Factor to multiply the components of \p in_vct by.
			\param[in]	in_vct		Vector to multiply.
			\return	Reference to this vector.
			\sa CSIBCVector2Dd::Mul
			\sa CSIBCVector2Dd::Div
			\sa CSIBCVector2Dd::MulComp
			\sa CSIBCVector2Dd::DivComp
		*/
		CSIBCVector2Dd& Mul( const double in_dFactor, const CSIBCVector2Dd& in_vct );

		/*!	Multiplies each of the components in \p in_vct by \p in_dFactor. The result
			is stored in this vector.
			\param[in]	in_vct		Vector to multiply.
			\param[in]	in_dFactor	Factor to multiply the components of \p in_vct by.
			\return	Reference to this vector.
			\sa CSIBCVector2Dd::Mul
			\sa CSIBCVector2Dd::Div
			\sa CSIBCVector2Dd::MulComp
			\sa CSIBCVector2Dd::DivComp
		*/
		CSIBCVector2Dd& Mul( const CSIBCVector2Dd& in_vct, const double in_dFactor );

		/*!	Divides each component of this vector by \p in_dFactor. The result is stored
			in this vector.
			\param[in]	in_dFactor	Factor to divide the components of this vector by.
			\return	Reference to this vector.
			\sa CSIBCVector2Dd::Div
			\sa CSIBCVector2Dd::Mul
			\sa CSIBCVector2Dd::DivComp
			\sa CSIBCVector2Dd::MulComp
		*/
		CSIBCVector2Dd& Div( const double in_dFactor );

		/*!	Divides each component of \p in_vct by \p in_dFactor. The result is stored
			in this vector.
			\param[in]	in_vct		Vector to divide.
			\param[in]	in_dFactor	Factor to divide the components of this vector by.
			\return	Reference to this vector.
			\sa CSIBCVector2Dd::Div
			\sa CSIBCVector2Dd::Mul
			\sa CSIBCVector2Dd::DivComp
			\sa CSIBCVector2Dd::MulComp
		*/
		CSIBCVector2Dd& Div( const CSIBCVector2Dd& in_vct, const double in_dFactor );

		/*!	Multiplies each component of \p in_vct1 by the corresponding component in \p in_vct2.
			The result is stored in this vector.
			\param[in]	in_vct1	First vector to multiply the components of.
			\param[in]	in_vct2	Second vector to multiply the components of.
			\return	Reference to this vector.
			\sa CSIBCVector2Dd::MulComp
			\sa CSIBCVector2Dd::DivComp
			\sa CSIBCVector2Dd::Mul
			\sa CSIBCVector2Dd::Div
		*/
		CSIBCVector2Dd& MulComp( const CSIBCVector2Dd& in_vct1, const CSIBCVector2Dd& in_vct2  );

		/*!	Multiplies each component of \p in_vct by the corresponding component in this vector.
			The result is stored in this vector.
			\param[in]	in_vct	Vector to multiply the components of.
			\return	Reference to this vector.
			\sa CSIBCVector2Dd::MulComp
			\sa CSIBCVector2Dd::DivComp
			\sa CSIBCVector2Dd::Mul
			\sa CSIBCVector2Dd::Div
		*/
		CSIBCVector2Dd& MulComp( const CSIBCVector2Dd& in_vct );

		/*!	Divides each component of this vector by the corresponding component in \p in_vct.
			The result is stored in this vector.
			\param[in]	in_vct	Vector to divide the components of this vector by.
			\return	Reference to this vector.
			\sa CSIBCVector2Dd::DivComp
			\sa CSIBCVector2Dd::MulComp
			\sa CSIBCVector2Dd::Div
			\sa CSIBCVector2Dd::Mul
		*/
		CSIBCVector2Dd& DivComp( const CSIBCVector2Dd& in_vct );

		/*!	Divides each component of \p in_vct1 by the corresponding component in \p in_vct2.
			The result is stored in this vector.
			\param[in]	in_vct1	Vector to be divided by the components of \p in_vct2
			\param[in]	in_vct2	Vector to divide the components of \p in_vct1 by.
			\return	Reference to this vector.
			\sa CSIBCVector2Dd::DivComp
			\sa CSIBCVector2Dd::MulComp
			\sa CSIBCVector2Dd::Div
			\sa CSIBCVector2Dd::Mul
		*/
		CSIBCVector2Dd& DivComp( const CSIBCVector2Dd& in_vct1, const CSIBCVector2Dd& in_vct2 );

		// TODO  Remove set of functions to multiply by CSIBCRotMatd as soon as
		//       CSIBCRotMatd and CSIBCMatrix33d will both derived public from a
		//       common base matrix class.

		/*! Multiplies a 3D row vector \p in_vct, into a 3x3 rotation matrix \p in_mat
			(<TT>in_vct * in_mat</TT>), and stores the result in this vector. Since the output
			from this operation would normally be a 3D row vector, only the X and Y components
			of the result are used.
			\param[in]	in_vct	Row vector to multiply (on the left).
			\param[in]	in_mat	Rotation matrix to multiply (on the right).
			\return	Reference to this vector.
			\sa CSIBCVector2Dd::Mul
			\sa CSIBCVector2Dd::MulComp
			\sa CSIBCVector2Dd::DivComp
			\sa CSIBCVector2Dd::Div
		*/
		CSIBCVector2Dd& Mul( const CSIBCVector3Dd&  in_vct, const CSIBCRotMatd& in_mat );

		/*! Multiplies a 3x3 rotation matrix \p in_mat, into a 3D column vector, \p in_vct
			(<TT>in_mat * in_vct</TT>), and stores the result in this vector. Since the output
			from this operation would normally be a 3D column vector, only the X and Y components
			of the result are used.
			\param[in]	in_mat	Rotation matrix to multiply (on the left).
			\param[in]	in_vct	Column vector to multiply (on the right).
			\return	Reference to this vector.
			\sa CSIBCVector2Dd::Mul
			\sa CSIBCVector2Dd::MulComp
			\sa CSIBCVector2Dd::DivComp
			\sa CSIBCVector2Dd::Div
		*/
		CSIBCVector2Dd& Mul( const CSIBCRotMatd& in_mat, const CSIBCVector3Dd& in_vct );

		/*!	Computes the dot product between the vectors \p in_vct1 and \p in_vct2.
			\param[in]	in_vct1	First vector in the dot product.
			\param[in]	in_vct2	Second vector in the dot product.
			\return	The dot product between \p in_vct1 and \p in_vct2.
		*/
		friend double GetDot( const CSIBCVector2Dd& in_vct1, const CSIBCVector2Dd& in_vct2 );

		/*! Projects this vector onto \p in_vct. The projected vector is stored in this vector.
			\param[in]	in_vct	Vector to project this vector onto.
			\retval true if the vector is projected
			\retval false if the input vector is the null vector, in which case this vector keeps its original value
			\sa CSIBCVector2Dd::SetMirror
		*/
		bool SetProjection( const CSIBCVector2Dd& in_vct );

		/*!	Computes <TT>in_vct1 * 2 - in_vct2</TT>, and stores the result in this vector.
			\param[in]	in_vct1		First vector in the computation.
			\param[in]	in_vct2		Second vector in the computation.
			\return Reference to this vector.
			\sa CSIBCVector2Dd::SetProjection
		*/
		CSIBCVector2Dd& SetMirror( const CSIBCVector2Dd& in_vct1,
									const CSIBCVector2Dd& in_vct2 );


		/*!	Computes the distance between two points in 2D space given by
			\p in_pnt1 and \p in_pnt2.
			\param[in]	in_pnt1	Starting point for distance calculation.
			\param[in]	in_pnt2	Ending point for distance calculation.
			\return	The scalar distance between the two points, in 2D space.
			\sa CSIBCVector2Dd::GetSquaredDistance
		*/
		friend double GetDistance( const CSIBCVector2Dd& in_pnt1,
									const CSIBCVector2Dd& in_pnt2 );

		/*! Computes the squared distance between two points in 2D space given by
			\p in_pnt1 and \p in_pnt2.
			\param[in]	in_pnt1	Starting point for distance calculation.
			\param[in]	in_pnt2	Ending point for distance calculation.
			\return	The squared scalar distance between the two points, in 2D space.
			\sa CSIBCVector2Dd::GetDistance
		*/
		friend double GetSquaredDistance( const CSIBCVector2Dd& in_pnt1,
									const CSIBCVector2Dd& in_pnt2 );

		/*!	Determines which 'side' of the vector formed between the points \p in_pntOrigin and
			\p in_pntTip, a point \p in_pnt is on.
			\param[in]	in_pnt			Point to determine which side of the vector it is on.
			\param[in]	in_pntOrigin	Staring point of the vector in the XY plane.
			\param[in]	in_pntTip		Ending point of the vector in the XY plane.
			\retval \c -1 if the point is on the right side
			\retval \c 1 if the point is on the left side
			\sa CSIBCVector2Dd::FSegmentIntersect
		*/
		friend int Get2DPntSide(	const CSIBCVector2Dd& in_pnt,
									const CSIBCVector2Dd& in_pntOrigin,
									const CSIBCVector2Dd& in_pntTip );

		/*!	Determines whether two 2D line segments intersect.
			\param[in]	a0	The starting point of the first line segment.
			\param[in]	a1	The ending point of the first line segment.
			\param[in]	b0	The starting point of the second line segment.
			\param[in]	b1	The ending point of the second line segment.
			\retval true if the line segments intersect
			\retval false otherwise
			\sa CSIBCVector2Dd::Get2DPntSide
		*/
		friend bool FSegmentIntersect(	const CSIBCVector2Dd& a0,
										const CSIBCVector2Dd& a1,
										const CSIBCVector2Dd& b0,
										const CSIBCVector2Dd& b1 );

		/*! Sets this vector to the midpoint between the two points \p in_pnt1 and \p in_pnt2.
			\param[in]	in_pnt1	First point for midpoint determination.
			\param[in]	in_pnt2	Second point for midpoint determination.
			\return	Reference to this vector.
			\sa CSIBCVector2Dd::LinearPositionInterpolate
		*/
		CSIBCVector2Dd& SetMidpoint(	const CSIBCVector2Dd& in_pnt1,
										const CSIBCVector2Dd& in_pnt2 );

		/*! Computes the linear interpolation between the two vectors \p in_vct1 and
			\p in_vct2, at a point \p in_dT between the two vectors.
			\param[in]	in_vct1	Starting point for the interpolation.
			\param[in]	in_vct2	Ending point for the interpolation.
			\param[in]	in_dT	Interpolation point between the vectors, in the range [0.0f, 1.0f].
			\return	Reference to this vector.
			\sa CSIBCVector2Dd::SetMidpoint
		*/
		CSIBCVector2Dd& LinearPositionInterpolate( const CSIBCVector2Dd& in_vct1,
									const CSIBCVector2Dd& in_vct2, const double in_dT );

		/////////////////////////////
		// To be implemented later //
		/////////////////////////////
		// The following methods will be implemented later.

		// Cardinal & Bezier Position Interpolate doens't exist in SI3D3.7
		// What about Linear, Cardinal & Bezier VectorInterpolate

		// SetBounds	| Readjust boundaries (min and max) to contain a given point.
		/*! Not implemented yet. */
		void SetBounds( const CSIBCVector2Dd& in_pnt,/*!< n/a */
									CSIBCVector2Dd& io_min, /*!< n/a */CSIBCVector2Dd& io_max /*!< n/a */);

		// Combine		| Compute this=s1*v1 + s2*v2.
		/*! Not implemented yet. */
		CSIBCVector2Dd& Combine( const CSIBCVector2Dd& in_vct1, /*!< n/a */const double in_dS1,/*!< n/a */
									const CSIBCVector2Dd& in_vct2,/*!< n/a */ const double in_dS2 /*!< n/a */);

		///////////////////////////////
		// To finish implementing.   //
		///////////////////////////////

		// BsplinePositionInterpolate | Interpolates a BSpline position between four 2D vectors.
		/*! Not implemented yet. */
		CSIBCVector2Dd& BsplinePositionInterpolate( const CSIBCVector2Dd& in_vct1,/*!< n/a */
									const CSIBCVector2Dd& in_vct2, /*!< n/a */const CSIBCVector2Dd& in_vct3,/*!< n/a */
									const CSIBCVector2Dd& in_vct4, /*!< n/a */const double in_dT /*!< n/a */);
		// BsplineVectorInterpolate | Interpolates a BSpline vector between four 2D vectors.
		/*! Not implemented yet. */
		CSIBCVector2Dd& BsplineVectorInterpolate( const CSIBCVector2Dd& in_vct1,/*!< n/a */
									const CSIBCVector2Dd& in_vct2,/*!< n/a */ const CSIBCVector2Dd& in_vct3,/*!< n/a */
									const CSIBCVector2Dd& in_vct4, /*!< n/a */const double in_dT /*!< n/a */);

		// ArePntsCollinear	| Verify if three points are collinear.
		/*! Not implemented yet. */
		friend bool ArePntsCollinear( const CSIBCVector2Dd& in_pnt1,/*!< n/a */
										const CSIBCVector2Dd& in_pnt2,/*!< n/a */
										const CSIBCVector2Dd& in_pnt3,/*!< n/a */
										const double in_dEpsilon = PICO_EPS /*!< n/a */);

	// Private Members
	private:

		CSIBCVector2Dd( const CSIBCVector2Dd& in_vct );

		//****************************************
		// ATTRIBUTES
		//****************************************
		// double | CSIBCVector2Dd | m_dX | X component of the vector.
		// double | CSIBCVector2Dd | m_dY | Y component of the vector.
		double  m_dX, m_dY;
};

//******************************************************************************
//
// Author       : Michel Carigan
// Date         : 08/05/96
// Updated by   : Eric Cabot (02/25/97)
//
// Set each component to be at least epsilon (in absolute or not depending on in_bInAbs).
//
// A reference on this.
//
// This function works like the macro _SI_VCT_EPS in v3.51
// That is, each component are set to eps only if they are less than epsilon.
// In that case the sign is unchanged.
//
//
//******************************************************************************
inline CSIBCVector2Dd&
CSIBCVector2Dd::SetMinimal
    (
        bool in_bInAbs,             // Tells if the test is done in absolute value or not (true by default).
        const double in_dEpsilon    // The epsilon to compare with (#PICO_EPS by default).
    )
{

    if( in_bInAbs )
    {

        if( fabs(m_dX) < in_dEpsilon )
            m_dX = ( ( m_dX >= 0 ) ? in_dEpsilon : -in_dEpsilon ) ;
        if( fabs(m_dY) < in_dEpsilon )
            m_dY = ( ( m_dY >= 0 ) ? in_dEpsilon : -in_dEpsilon ) ;
    }
    else
    {
        if( m_dX < in_dEpsilon )
        {
            m_dX = in_dEpsilon;
        }
        if( m_dY < in_dEpsilon )
        {
            m_dY = in_dEpsilon;
        }
    }

    return *this;
}

#endif
