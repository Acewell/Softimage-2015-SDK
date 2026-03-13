//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file SL_Byte.h
	\brief Defines the CSLByteProxy class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _SL_BYTE_H
#define _SL_BYTE_H

#include "AnimatableType.h" // CSLAnimatableType
class CCOLLADATemplate;
class CSLCOLLADAScene;

/*! \brief Class that allows modification of a byte parameter in a template
*/
class XSIEXPORT CSLByteProxy : public CSLAnimatableType
{
public:
	/*! Constructor. Connects to a byte parameter in a template
		\param[in] in_pTemplate Pointer to the template
		\param[in] in_nIndex Index of the parameter in the template
	 */
	CSLByteProxy(CdotXSITemplate *in_pTemplate, SI_Int in_nIndex );

    /*! Assignment operator. Assigns \p in_Value to the parameter referred by this proxy.
		\param[in]	in_Value	The new value
		\return Reference to the current object.
	*/
	CSLByteProxy& operator =(const CSLByteProxy &in_Value);

	/*! Assignment operator. Assigns \p in_Value to the parameter referred by this proxy.
		\param[in]	in_Value	The new value
		\return Reference to the current object.
	*/
    CSLByteProxy& operator =(const SI_Byte &in_Value);

	/*! Comparison operator. Compares \p in_ToCompare with the value of the parameter referred by this proxy.
		\param[in]	in_ToCompare	The instance to compare values with
		\return	Whether or not the referred parameter and \p in_ToCompare are equal
	*/
    SI_Bool operator ==(const CSLByteProxy &in_ToCompare);

	/*! Comparison operator. Compares \p in_ToCompare with the value of the parameter referred by this proxy.
		\param[in]	in_ToCompare	The instance to compare values with
		\return	Whether or not the referred parameter and \p in_ToCompare are equal
	*/
    SI_Bool operator ==(const SI_Byte &in_ToCompare);

	//! Conversion operator
    operator SI_Byte();

	/*! Returns the animatable type of this class
		\retval CSLAnimatableType::SI_BYTE_TYPE Animatable type
	*/
	virtual EElementType Type();

	/*! Converts the value of the referred parameter to float
		\return The converted value
	*/
	virtual SI_Float GetFloatValue();

	/*! Sets the value of the referred parameter from a float
		\param[in] in_fValue The float value used to set the parameter
	*/
	virtual SI_Void SetFloatValue(SI_Float in_fValue);

	/*! Connects the proxy to a parameter of a template
		\param[in] in_pTemplate Parent template
		\param[in] in_nIndex Index of the parameter in the parent template
		\retval SI_Error::SI_SUCCESS
	*/
	virtual SI_Error Connect (CdotXSITemplate *in_pTemplate, SI_Int in_nIndex );

private:
	CSLByteProxy( CSLByteProxy &in_pBasicType ){}
    SI_Byte* m_pValue;
};

///////////////////////////////////////////////////////////////////////////////

//! Class that allows modification of a usigned byte parameter in a template
class XSIEXPORT CSLUByteProxy : public CSLAnimatableType
{
public:
	/*! Constructor. Connects to an unsigned byte parameter in a template
		\param[in] in_pTemplate Pointer to the template
		\param[in] in_nIndex Index of the parameter in the template
	 */
	CSLUByteProxy(CdotXSITemplate *in_pTemplate, SI_Int in_nIndex );

    /*! Assignment operator. Assigns \p in_Value to the parameter referred by this proxy.
		\param[in]	in_Value	The new value
		\return Reference to the current object.
	*/
	CSLUByteProxy& operator =(const CSLUByteProxy &in_Value);

	/*! Assignment operator. Assigns \p in_Value to the parameter referred by this proxy.
		\param[in]	in_Value	The new value
		\return Reference to the current object.
	*/
    CSLUByteProxy& operator =(const SI_UByte &in_Value);

	/*! Comparison operator. Compares \p in_ToCompare with the value of the parameter referred by this proxy.
		\param[in]	in_ToCompare	The instance to compare values with
		\return	Whether or not the referred parameter and \p in_ToCompare are equal
	*/
    SI_Bool operator ==(const CSLUByteProxy &in_ToCompare);

	/*! Comparison operator. Compares \p in_ToCompare with the value of the parameter referred by this proxy.
		\param[in]	in_ToCompare	The instance to compare values with
		\return	Whether or not the referred parameter and \p in_ToCompare are equal
	*/
    SI_Bool operator ==(const SI_UByte &in_ToCompare);

	//! Conversion operator
    operator SI_UByte();

	/*! Returns the animatable type of this class
		\retval CSLAnimatableType::SI_UBYTE_TYPE Animatable type
	*/
	virtual EElementType Type();

	/*! Converts the value of the referred parameter to float
		\return The converted value
	*/
	virtual SI_Float GetFloatValue();

	/*! Sets the value of the referred parameter from a float
		\param[in] in_fValue The float value used to set the parameter
	*/
	virtual SI_Void SetFloatValue(SI_Float in_fValue);

	/*! Connects the proxy to a parameter of a template
		\param[in] in_pTemplate Parent template
		\param[in] in_nIndex Index of the parameter in the parent template
		\retval SI_SUCCESS
	*/
	virtual SI_Error Connect (CdotXSITemplate *in_pTemplate, SI_Int in_nIndex );

private:
	CSLUByteProxy( CSLUByteProxy &in_pBasicType ){}
    SI_UByte* m_pValue;
};

#endif
