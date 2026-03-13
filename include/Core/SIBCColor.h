//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file SIBCColor.h
	\brief Defines the CSIBCColorb and CSIBCColorf classes

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

//***************************************************************************************
// Defines
//***************************************************************************************
#ifndef __CSIBCColor_H__
#define __CSIBCColor_H__

//***************************************************************************************
// Includes
//***************************************************************************************
#include <math.h>
#include <SIBCUtil.h>

//***************************************************************************************
// CSIBCColorf |
//***************************************************************************************

/*! \brief Represents colours and stores RGBA values as floating point values.

	Member functions with the \c "Alpha" suffix operate on alpha as well as RGB, whereas
	their counterparts operate only on RGB color component values. This class is analogous
	to the CSIBCColorb class, which uses unsigned bytes to represent color components, instead
	of floating-point numbers.
*/
class XSICOREEXPORT CSIBCColorf
{
	public:

		/*! Default constructor.
			Creates a new color object, with uninitialized color values.
		*/
		CSIBCColorf();

		/*! Copy Constructor.
			Creates a new color object, based on the values in the \p i_Color object.
			\param[in]	i_Color	Color object to copy values from for the new object.
		*/
		CSIBCColorf( const CSIBCColorf & i_Color);

		/*! Constructor.
			Creates a new color with the given color component values.
			\param[in]	i_fR	Value to set the red component of the color to.
			\param[in]	i_fB	Value to set the blue component of the color to.
			\param[in]	i_fG	Value to set the green component of the color to.
			\param[in]	i_fA	Value to set the alpha component of the color to (defaults to \c 1.0f).
		*/
		CSIBCColorf(	const SI_Float i_fR,
						const SI_Float i_fB,
						const SI_Float i_fG,
						const SI_Float i_fA = 1.0f );

		~CSIBCColorf();

		// Comparison

		/*! Determines whether the color \p i_Color and this color are equal to each other,
			within a given limit. This is necessary because of floating-point round-off errors.
			\param[in]	i_Color	The color to compare this color with.
			\param[in]	i_Thresh \b Ignored. The comparison uses \c #PICO_EPS for the comparison threshhold.
			\retval SI_Bool::TRUE if all component values of the two colors are no less than \c #PICO_EPS different
			\retval SI_Bool::FALSE otherwise
			\sa CSIBCColorf::operator==
			\sa CSIBCColorf::operator!=
		*/
		SI_Bool IsAlmostEqualTo(const CSIBCColorf& i_Color, const SI_Float i_Thresh) const;

		/*!	Determines whether all component values (\b excluding alpha) of this color are zero.
			Due to floating-point round-off error, \c #PICO_EPS is used for the zero comparison.
			\retval SI_Bool::TRUE if all component values are equal to zero
			\retval SI_Bool::FALSE otherwise
			\sa CSIBCColorf::IsNullAlpha
			\sa CSIBCColorf::SetNull
		*/
		SI_Bool IsNull() const;

		/*!	Determines whether all component values (\b including alpha) of this color are zero.
			Due to floating-point round-off error, \c #PICO_EPS is used for the zero comparison.
			\retval SI_Bool::TRUE if all component values are equal to zero
			\retval SI_Bool::FALSE otherwise
			\sa CSIBCColorf::IsNull
			\sa CSIBCColorf::SetNull
		*/
		SI_Bool IsNullAlpha() const;

		// Computed Info

		/*! Returns the dot-product of this color with another color. This is the sum of the scalar
			multiplication of all corresponding component values in the two colors (\b excluding
			alpha).
			\param[in]	i_Color	Color object to get this object's dot product with.
			\return	Dot product of the two colors.
			\sa CSIBCColorf::GetDotAlpha
		*/
		SI_Float GetDot(const CSIBCColorf& i_Color) const;

		/*! Returns the dot-product of this color with another color. This is the sum of the scalar
			multiplication of all corresponding component values in the two colors (\b including
			alpha).
			\param[in]	i_Color	Color object to get this object's dot product with.
			\return	Dot product of the two colors.
			\sa CSIBCColorf::GetDot
		*/
		SI_Float GetDotAlpha(const CSIBCColorf& i_Color) const;

		/*! Computes the distance between this object's color and \c i_Color in RGB space (i.e \b excluding
			alpha).
			\param[in]	i_Color	Color object to get this object's distance from.
			\return	Distance between the two colors in RGB space.
			\sa CSIBCColorf::GetDistanceFromAlpha
		*/
		SI_Float GetDistanceFrom(const CSIBCColorf& i_Color) const;

		/*! Computes the distance between this object's color and \c i_Color in RGBA space (\b including
			alpha).
			\param[in]	i_Color	Color object to get this object's distance from.
			\return	Distance between the two colors in RGBA space.
			\sa CSIBCColorf::GetDistanceFrom
		*/
		SI_Float GetDistanceFromAlpha(const CSIBCColorf& i_Color) const;

		/*! Computes the length of this object's color vector in RGB space (\b excluding alpha).
			\return	The length of this color in RGB space.
			\sa CSIBCColorf::GetLengthAlpha
			\sa CSIBCColorf::GetSquaredLength
		*/
		SI_Float GetLength() const;

		/*! Computes the length of this object's color vector in RGBA space (\b including alpha).
			\return	The length of this color in RGBA space.
			\sa CSIBCColorf::GetLength
			\sa CSIBCColorf::GetSquaredLengthAlpha
		*/
		SI_Float GetLengthAlpha() const;

		/*! Computes the squared length of this object's color vector in RGB space (\b excluding alpha).
			\return	The length of this color in RGB space.
			\sa CSIBCColorf::GetLength
			\sa CSIBCColorf::GetSquaredLengthAlpha
		*/
		SI_Float GetSquaredLength() const;

		/*! Computes the squared length of this object's color vector in RGBA space (\b including alpha).
			\return	The length of this color in RGBA space.
			\sa CSIBCColorf::GetLengthAlpha
			\sa CSIBCColorf::GetSquaredLength
		*/
		SI_Float GetSquaredLengthAlpha() const;

		/*!	Returns the value and index largest color component (\b excluding alpha).
			\param[in]	i_pIndex	Pointer to a value set to the index of the largest component. Possible values:
					\li \c 0 = Red
					\li \c 1 = Green
					\li \c 2 = Blue
			\return	Value of the largest color component
			\sa	CSIBCColorf::GetMaxComponentAlpha
			\sa CSIBCColorf::GetMinComponent
		*/
		SI_Float GetMaxComponent(SI_Int * i_pIndex) const;

		/*!	Returns the value and index largest color component (\b including alpha).
			\param[in]	i_pIndex	Pointer to a value set to the index of the largest component. Possible values:
				\li \c 0 = Red
				\li \c 1 = Green
				\li \c 2 = Blue
				\li \c 3 = Alpha
			\return	Value of the largest color component
			\sa	CSIBCColorf::GetMaxComponent
			\sa CSIBCColorf::GetMinComponentAlpha
		*/
		SI_Float GetMaxComponentAlpha(SI_Int * i_pIndex) const;

		/*!	Returns the value and index smallest color component (\b excluding alpha).
			\param[in]	i_pIndex	Pointer to a value set to the index of the smallest component. Possible values:
				\li \c 0 = Red
				\li \c 1 = Green
				\li \c 2 = Blue
			\return	Value of the smallest color component
			\sa	CSIBCColorf::GetMinComponentAlpha
			\sa CSIBCColorf::GetMaxComponent
		*/
		SI_Float GetMinComponent(SI_Int * i_pIndex) const;

		/*!	Returns the value and index smallest color component (\b including alpha).
			\param[in]	i_pIndex	Pointer to a value set to the index of the smallest component. Possible values:
				\li \c 0 = Red
				\li \c 1 = Green
				\li \c 2 = Blue
				\li \c 3 = Alpha
			\return	Value of the smallest color component
			\sa	CSIBCColorf::GetMinComponent
			\sa CSIBCColorf::GetMaxComponentAlpha
		*/
		SI_Float GetMinComponentAlpha(SI_Int * i_pIndex) const;

		// Components

		/*! Returns the value of each color component in this color object (\b including alpha).
			\param[out]	o_pR	Red component of this color.
			\param[out]	o_pG	Green component of this color.
			\param[out]	o_pB	Blue component of this color.
			\param[out]	o_pA	Alpha component of this color.
			\sa CSIBCColorf::Set
		*/
		void Get(SI_Float* o_pR, SI_Float* o_pG, SI_Float* o_pB, SI_Float* o_pA) const;

		/*! Returns the value of each color component in this color object (\b excluding alpha).
			\param[out]	o_pR	Red component of this color.
			\param[out]	o_pG	Green component of this color.
			\param[out]	o_pB	Blue component of this color.
			\sa CSIBCColorf::Set
		*/
		void Get(SI_Float* o_pR, SI_Float* o_pG, SI_Float* o_pB) const;

		/*! Sets each of the color components of this color object.
			\param[in]	i_fR	The value to set the Red component to.
			\param[in]	i_fG	The value to set the Green component to.
			\param[in]	i_fB	The value to set the Blue component to.
			\param[in]	i_fA	The value to set the Alpha component to (defaults to \c 1.0f).
			\return	Reference to this object.
			\sa CSIBCColorf::Get
		*/
		CSIBCColorf& Set(SI_Float i_fR, SI_Float i_fG, SI_Float i_fB, SI_Float i_fA = 1.0f );

		// Operations

		/*! Normalizes the RGB color vector of this color.
			\return	Reference to this object.
			\sa CSIBCColorf::NormalizeAlpha
		*/
		CSIBCColorf& Normalize();

		/*! Normalizes the RGBA color vector of this color.
			\return	Reference to this object.
			\sa CSIBCColorf::Normalize
		*/
		CSIBCColorf& NormalizeAlpha();

		/*! Sets the RGB components of this color to zero, and the alpha to \c alpha.
			\param[in]	alpha	Value to set the alpha component of this color to (defaults to \c 1.0f).
			\return	Reference to this object
			\sa CSIBCColorf::IsNull
			\sa CSIBCColorf::IsNullAlpha
		*/
		CSIBCColorf& SetNull( SI_Float alpha = 1.0f );

		/*! Sets the length of the RGB vector (\b excluding alpha) to \c in_dLength
			\param[in]	in_dLength	The new length for the RGB vector.
			\return	Reference to this object.
			\sa CSIBCColorf::SetLengthAlpha
			\sa CSIBCColorf::GetLength
			\sa CSIBCColorf::GetSquaredLength
		*/
		CSIBCColorf& SetLength(const SI_Float in_dLength);

		/*! Sets the length of the RGBA vector (\b including alpha) to \c in_dLength
			\return	Reference to this object.
			\sa CSIBCColorf::SetLength
			\sa CSIBCColorf::GetLengthAlpha
			\sa CSIBCColorf::GetSquaredLengthAlpha
		*/
		CSIBCColorf& SetLengthAlpha(const SI_Float /*!< The new length for the RGBA vector. */ );

		/*! Negates all color component values (\b excluding alpha).
			\return	Reference to this object
			\sa CSIBCColorf::NegateAlpha
		*/
		CSIBCColorf& Negate();

		/*! Negates all color component values (\b including alpha).
			\return	Reference to this object
			\sa CSIBCColorf::Negate
		*/
		CSIBCColorf& NegateAlpha();

		/*! Sets the color components of this object to the sum of its components with the
			components of \c i_Color (\b excluding alpha).
			\param[in]	i_Color	Color object to add color component values from.
			\return	Reference to this object
			\sa CSIBCColorf::AddAlpha
		*/
		CSIBCColorf& Add(const CSIBCColorf& i_Color);

		/*! Sets the color components of this object to the sum of its components with the
			components of \c i_Color (\b including alpha).
			\param[in]	i_Color	Color object to add color component values from.
			\return	Reference to this object
			\sa CSIBCColorf::Add
			\sa CSIBCColorf::operator+
		*/
		CSIBCColorf& AddAlpha(const CSIBCColorf& i_Color);

		/*! Sets the color components of this object to the difference of its components with the
			components of \c i_Color (\b excluding alpha).
			\param[in]	i_Color	Color object to subtract color component values from.
			\return	Reference to this object
			\sa CSIBCColorf::SubAlpha
		*/
		CSIBCColorf& Sub(const CSIBCColorf& i_Color);

		/*! Sets the color components of this object to the difference of its components with the
			components of \c i_Color (\b including alpha).
			\param[in]	i_Color	Color object to subtract color component values from.
			\return	Reference to this object
			\sa CSIBCColorf::Sub
		*/
		CSIBCColorf& SubAlpha(const CSIBCColorf& i_Color);

		/*! Scales the color components of this object by \c i_fFactor (\b excluding alpha).
			\param[in]	i_fFactor	Scaling factor to use.
			\return	Reference to this object
			\sa CSIBCColorf::ScaleAlpha
		*/
		CSIBCColorf& Scale(const SI_Float i_fFactor);

		/*! Scales the color components of this object by \c i_fFactor (\b including alpha).
			\param[in]	i_fFactor	Scaling factor to use.
			\return	Reference to this object
			\sa CSIBCColorf::Scale
			\sa CSIBCColorf::operator*
		*/
		CSIBCColorf& ScaleAlpha(const SI_Float i_fFactor);

		/*! Sets this object's color component values to the product of its original values,
			and the component values in \c i_Color (\b including alpha).
			\param[in]	i_Color	The color to multiply component values with.
			\return	Reference to this object
			\sa CSIBCColorf::DivComp
		*/
		CSIBCColorf& MulComp(const CSIBCColorf& i_Color);

		/*! Sets this object's color component values to the quotient of its original values,
			divided by the component values in \c i_Color (\b including alpha).
			\param[in]	i_Color	The color to divide component values with.
			\return	Reference to this object
			\sa CSIBCColorf::MulComp
		*/
		CSIBCColorf& DivComp(const CSIBCColorf& i_Color);

	    // overloaded operators

		/*! Equality operator. Determines whether each color component of \c i_Color
			is exactly equal to the corresponding color component in this color.
			\param[in]	i_Color	The color to compare equality with.
			\retval	SI_Bool::TRUE if the color components in the objects are identical
			\retval	SI_Bool::FALSE otherwise.
			\sa CSIBCColorf::IsAlmostEqualTo
		*/
		SI_Bool operator == (const CSIBCColorf& i_Color) const;

		/*! Inequality operator. Determines whether any color component of \c i_Color
			are different to the corresponding color component in this color.
			\param[in]	i_Color	The color to compare inequality with.
			\retval	SI_Bool::TRUE if the color components in the objects are not identical
			\retval	SI_Bool::FALSE otherwise.
			\sa CSIBCColorf::IsAlmostEqualTo
		*/
		SI_Bool operator != (const CSIBCColorf& i_Color) const;

		/*! Addition operator. Computes a color object with the color components of this objects, and
			\c i_Color summed.
			\param[in]	i_Color	The color object to sum components with.
			\return	Color object representing the color obtained by summing this object and
					\p i_Color's color components.
			\sa CSIBCColorf::Add
		*/
		CSIBCColorf operator+(const CSIBCColorf & i_Color);

		/*! Scaling operator. Computes a color object whose color components are this object's color
			components multiplied by \c i_fFactor.
			\param[in]	i_fFactor	Scaling factor for color components.
			\return	Color object representing this object's scaled color components.
			\sa CSIBCColorf::ScaleAlpha
		*/
		CSIBCColorf operator*(const SI_Float i_fFactor);

		/*! Member variable representing the value of the Red component of the color. */
		SI_Float	m_fR;

		/*! Member variable representing the value of the Green component of the color. */
		SI_Float	m_fG;

		/*! Member variable representing the value of the Blue component of the color. */
		SI_Float	m_fB;

		/*! Member variable representing the value of the Alpha component of the color. */
		SI_Float	m_fA;

protected:


private:


};

//***************************************************************************************
// CSIBCColorb |
//***************************************************************************************

/*! \brief Represents colours and stores RGBA values as unsigned byte values.

	Member functions with the "Alpha" suffix operate on alpha as well as RGB, whereas
	their counterparts operate only on RGB color component values. This class is analogous
	to the CSIBCColorf class, which uses floating-point numbers to represent color components,
	instead of unsigned bytes.
*/
class XSICOREEXPORT CSIBCColorb
{
	public:

		/*! Default constructor.
			Creates a new color object, with uninitialized color values.
		*/
		CSIBCColorb();

		/*! Copy Constructor.
			Creates a new color object, based on the values in the \c i_Color object.
			\param[in]	i_Color	Color object to copy values from for the new object.
		*/
		CSIBCColorb( const CSIBCColorb & i_Color);

		/*! Constructor.
			Creates a new color with the given color component values.
			\param[in]	i_bR	Value to set the red component of the color to.
			\param[in]	i_bB	Value to set the blue component of the color to.
			\param[in]	i_bG	Value to set the green component of the color to.
			\param[in]	i_bA	Value to set the alpha component of the color to (defaults to 0).
		*/
		CSIBCColorb(	const SI_UByte	i_bR,
						const SI_UByte	i_bG,
						const SI_UByte	i_bB,
						const SI_UByte	i_bA = 0 );

		~CSIBCColorb();								// Default Destructor

		// Comparison

		/*!	Determines whether all component values (\b excluding alpha) of this color are zero.
			\retval SI_Bool::TRUE if all component values are equal to zero
			\retval SI_Bool::FALSE otherwise
			\sa CSIBCColorb::IsNullAlpha
			\sa CSIBCColorb::SetNull
		*/
		SI_Bool IsNull() const;

		/*!	Determines whether all component values (\b including alpha) of this color are zero.
			\retval SI_Bool::TRUE if all component values are equal to zero
			\retval SI_Bool::FALSE otherwise
			\sa CSIBCColorb::IsNull
			\sa CSIBCColorb::SetNull
		*/
		SI_Bool IsNullAlpha() const;

		// Computed Info

		/*! Returns the dot-product of this color with another color. This is the sum of the scalar
			multiplication of all corresponding component values in the two colors (\b excluding alpha).
			\return	Dot product of the two colors.
			\sa CSIBCColorb::GetDotAlpha
		*/
		SI_UByte GetDot(const CSIBCColorb& /*!< Color object to get this object's dot product with. */ ) const;

		/*! Returns the dot-product of this color with another color. This is the sum of the scalar
			multiplication of all corresponding component values in the two colors (\b including alpha).
			\return	Dot product of the two colors.
			\sa CSIBCColorb::GetDot
		*/
		SI_UByte GetDotAlpha(const CSIBCColorb& /*!< Color object to get this object's dot product with. */ ) const;

		/*! Computes the distance between this object's color and \c i_Color in RGB space (\b excluding alpha).
			\return	Distance between the two colors in RGB space.
			\sa CSIBCColorb::GetDistanceFromAlpha
		*/
		SI_Float GetDistanceFrom(const CSIBCColorb& /*!< Color object to get this object's distance from. */ ) const;

		/*! Computes the distance between this object's color and \c i_Color in RGBA space (\b including
			alpha).
			\return	Distance between the two colors in RGBA space.
			\sa CSIBCColorb::GetDistanceFrom
		*/
		SI_Float GetDistanceFromAlpha(const CSIBCColorb& /*!< Color object to get this object's distance from. */ ) const;

		/*! Computes the length of this object's color vector in RGB space (i.e \b excluding alpha).
			\return	The length of this color in RGB space.
			\sa CSIBCColorb::GetLengthAlpha
			\sa CSIBCColorb::GetSquaredLength
		*/
		SI_Float GetLength() const;

		/*! Computes the length of this object's color vector in RGBA space (i.e \b including alpha).
			\return	The length of this color in RGBA space.
			\sa CSIBCColorb::GetLength
			\sa CSIBCColorb::GetSquaredLengthAlpha
		*/
		SI_Float GetLengthAlpha() const;

		/*! Computes the squared length of this object's color vector in RGB space (i.e \b excluding alpha).
			\return	The length of this color in RGB space.
			\sa CSIBCColorb::GetLength
			\sa CSIBCColorb::GetSquaredLengthAlpha
		*/
		SI_Float GetSquaredLength() const;

		/*! Computes the squared length of this object's color vector in RGBA space (i.e \b including alpha).
			\return	The length of this color in RGBA space.
			\sa CSIBCColorb::GetLengthAlpha
			\sa CSIBCColorb::GetSquaredLength
		*/
		SI_Float GetSquaredLengthAlpha() const;

		/*!	Returns the value and index largest color component (\b excluding alpha).
			\param[in] i_pIndex		Pointer to a value set to the index of the largest component. Possible values:
				\li \c 0 = Red
				\li \c 1 = Green
				\li \c 2 = Blue
			\return	Value of the largest color component
			\sa	CSIBCColorb::GetMaxComponentAlpha
			\sa CSIBCColorb::GetMinComponent
		*/
		SI_UByte GetMaxComponent(SI_Int * i_pIndex) const;

		/*!	Returns the value and index largest color component (\b including alpha).
			\param[in] i_pIndex		Pointer to a value set to the index of the largest component. Possible values:
				\li \c 0 = Red
				\li \c 1 = Green
				\li \c 2 = Blue
				\li \c 3 = Alpha
			\return	Value of the largest color component
			\sa	CSIBCColorb::GetMaxComponent
			\sa CSIBCColorb::GetMinComponentAlpha
		*/
		SI_UByte GetMaxComponentAlpha(SI_Int * i_pIndex) const;

		/*!	Returns the value and index smallest color component (\b excluding alpha).
			\param[in] i_pIndex		Pointer to a value set to the index of the smallest component. Possible values:
				\li \c 0 = Red
				\li \c 1 = Green
				\li \c 2 = Blue
			\return	Value of the smallest color component
			\sa	CSIBCColorb::GetMinComponentAlpha
			\sa CSIBCColorb::GetMaxComponent
		*/
		SI_UByte GetMinComponent(SI_Int * i_pIndex) const;

		/*!	Returns the value and index smallest color component (\b including alpha).
			\param[in] i_pIndex		Pointer to a value set to the index of the smallest component. Possible values:
				\li \c 0 = Red
				\li \c 1 = Green
				\li \c 2 = Blue
				\li \c 3 = Alpha
			\return	Value of the smallest color component
			\sa	CSIBCColorb::GetMinComponent
			\sa CSIBCColorb::GetMaxComponentAlpha
		*/
		SI_UByte GetMinComponentAlpha(SI_Int * i_pIndex) const;

		// Components
		/*! Returns the value of each color component in this color object (\b including alpha).
			\param[out]	o_pR	Red component of this color.
			\param[out]	o_pG	Green component of this color.
			\param[out]	o_pB	Blue component of this color.
			\param[out]	o_pA	Alpha component of this color.
			\sa CSIBCColorb::Set
		*/
		void Get(SI_UByte* o_pR, SI_UByte* o_pG, SI_UByte* o_pB, SI_UByte* o_pA) const;


		/*! Returns the value of each color component in this color object (\b excluding alpha).
			\param[out]	o_pR	Red component of this color.
			\param[out]	o_pG	Green component of this color.
			\param[out]	o_pB	Blue component of this color.
			\sa CSIBCColorb::Set
		*/
		void Get(SI_UByte* o_pR, SI_UByte* o_pG, SI_UByte* o_pB) const;


		/*! Sets each of the color components of this color object.
			\param[in]	i_bR	The value to set the Red component to.
			\param[in]	i_bG	The value to set the Green component to.
			\param[in]	i_bB	The value to set the Blue component to.
			\param[in]	i_bA	The value to set the Alpha component to (defaults to \c 255).
			\return	Reference to this object.
			\sa CSIBCColorb::Get
		*/
		CSIBCColorb& Set(SI_UByte i_bR, SI_UByte i_bG, SI_UByte i_bB, SI_UByte i_bA = 255 );

		// Operations

		/*! Normalizes the RGB color vector of this color.
			\return	Reference to this object.
			\sa CSIBCColorb::NormalizeAlpha
		*/
		CSIBCColorb& Normalize();

		/*! Normalizes the RGBA color vector of this color.
			\return	Reference to this object.
			\sa CSIBCColorb::Normalize
		*/
		CSIBCColorb& NormalizeAlpha();

		/*! Sets the RGB components of this color to zero, and the alpha to \p alpha.
			\param[in]	alpha	Value to set the alpha component of this color to (defaults to \c 0).
			\return	Reference to this object
			\sa CSIBCColorb::IsNull
			\sa CSIBCColorb::IsNullAlpha
		*/
		CSIBCColorb& SetNull( SI_UByte alpha = 0 );

		/*! Sets the length of the RGB vector (i.e \b excluding alpha) to \p in_dLength
			\param[in]	in_dLength	The new length for the RGB vector.
			\return	Reference to this object.
			\sa CSIBCColorb::SetLengthAlpha
			\sa CSIBCColorb::GetLength
			\sa CSIBCColorb::GetSquaredLength
		*/
		CSIBCColorb& SetLength(const SI_Float in_dLength);

		/*! Sets the length of the RGBA vector (i.e \b including alpha) to \p in_dLength
			\param[in]	in_dLength	The new length for the RGBA vector.
			\return	Reference to this object.
			\sa CSIBCColorb::SetLength
			\sa CSIBCColorb::GetLengthAlpha
			\sa CSIBCColorb::GetSquaredLengthAlpha
		*/
		CSIBCColorb& SetLengthAlpha(const SI_Float in_dLength);

		/*! Negates all color component values (\b excluding alpha).
			\return	Reference to this object
			\sa CSIBCColorb::NegateAlpha
		*/
		CSIBCColorb& Negate();

		/*! Negates all color component values (\b including alpha).
			\return	Reference to this object
			\sa CSIBCColorb::Negate
		*/
		CSIBCColorb& NegateAlpha();

		/*! Sets the color components of this object to the sum of its components with the
			components of \p i_Color (\b excluding alpha).
			\param[in]	i_Color	Color object to add color component values from.
			\return	Reference to this object
			\sa CSIBCColorb::AddAlpha
		*/
		CSIBCColorb& Add(const CSIBCColorb& i_Color);

		/*! Sets the color components of this object to the sum of its components with the
			components of \p i_Color (\b including alpha).
			\param[in]	i_Color	Color object to add color component values from.
			\return	Reference to this object
			\sa CSIBCColorb::Add
			\sa CSIBCColorb::operator+
		*/
		CSIBCColorb& AddAlpha(const CSIBCColorb& i_Color);

		/*! Sets the color components of this object to the difference of its components with the
			components of \p i_Color (\b excluding alpha).
			\param[in]	i_Color	Color object to subtract color component values from.
			\return	Reference to this object
			\sa CSIBCColorb::SubAlpha
		*/
		CSIBCColorb& Sub(const CSIBCColorb& i_Color);

		/*! Sets the color components of this object to the difference of its components with the
			components of \p i_Color (\b including alpha).
			\param[in]	i_Color	Color object to subtract color component values from.
			\return	Reference to this object
			\sa CSIBCColorb::Sub
		*/
		CSIBCColorb& SubAlpha(const CSIBCColorb& i_Color);

		/*! Scales the color components of this object by \p i_fFactor (\b excluding alpha).
			\param[in]	i_fFactor	Scaling factor to use.
			\return	Reference to this object
			\sa CSIBCColorb::ScaleAlpha
		*/
		CSIBCColorb& Scale(const SI_Float i_fFactor);

		/*! Scales the color components of this object by \p i_fFactor (\b including alpha).
			\param[in]	i_fFactor	Scaling factor to use.
			\return	Reference to this object
			\sa CSIBCColorb::Scale
			\sa CSIBCColorb::operator*
		*/
		CSIBCColorb& ScaleAlpha(const SI_Float i_fFactor);

		/*! Sets this object's color component values to the product of its original values,
			and the component values in \p i_Color (\b including alpha).
			\param[in]	i_Color	The color to multiply component values with.
			\return	Reference to this object
			\sa CSIBCColorb::DivComp
		*/
		CSIBCColorb& MulComp(const CSIBCColorb& i_Color);

		/*! Sets this object's color component values to the quotient of its original values,
			divided by the component values in \p i_Color (\b including alpha).
			\param[in]	i_Color	The color to divide component values with.
			\return	Reference to this object
			\sa CSIBCColorb::MulComp
		*/
		CSIBCColorb& DivComp(const CSIBCColorb& i_Color);

	    // overloaded operators
		/*! Equality operator. Determines whether each color component of \p i_Color
			is equal to the corresponding color component in this color.
			\param[in]	i_Color	The color to compare equality with.
			\retval	SI_Bool::TRUE if the color components in the objects are identical
			\retval	SI_Bool::FALSE otherwise.
		*/
		SI_Bool operator == (const CSIBCColorb& i_Color) const;

		/*! Inequality operator. Determines whether any color component of \p i_Color
			are different to the corresponding color component in this color.
			\param[in]	i_Color	The color to compare inequality with.
			\retval	SI_Bool::TRUE if the color components in the objects are not identical
			\retval	SI_Bool::FALSE otherwise.
		*/
		SI_Bool operator != (const CSIBCColorb& i_Color) const;

		/*! Addition operator. Computes a color object with the color components of this objects, and
			\c i_Color summed.
			\param[in]	i_Color	The color object to sum components with.
			\return	Color object representing the color obtained by summing this object and
					\c i_Color's color components.
			\sa CSIBCColorb::Add
		*/
		CSIBCColorb operator+(const CSIBCColorb & i_Color);

		/*! Member variable representing the value of the Red component of the color.
		*/
		SI_UByte	m_fR;

		/*! Member variable representing the value of the Green component of the color.
		*/
		SI_UByte	m_fG;

		/*! Member variable representing the value of the Blue component of the color.
		*/
		SI_UByte	m_fB;

		/*! Member variable representing the value of the Alpha component of the color.
		*/
		SI_UByte	m_fA;

protected:


private:


};




#endif // CSIBCColor
