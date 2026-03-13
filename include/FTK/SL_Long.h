//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file SL_Long.h
	\brief Defines the CSLLongProxy class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _LONG_H
#define _LONG_H

#include "AnimatableType.h" // CSLAnimatableType
class CCOLLADATemplate;
class CSLCOLLADAScene;

/*! \brief Class that allows modification of a LONG parameter in a template
*/
class XSIEXPORT CSLLongProxy : public CSLAnimatableType
{
public:
	/*! Constructor. Connects to a parameter in the parent template
		\param[in] in_pTemplate Pointer to the parent template
		\param[in] in_nIndex Index of the parameter in the template
	 */
	CSLLongProxy(CdotXSITemplate *in_pTemplate, SI_Int in_nIndex );

	/*! Assignment operator. Assigns \p in_Value to the parameter referred by this proxy.
		\param[in]	in_Value	The new value
		\return Reference to the current object.
	*/
    CSLLongProxy& operator =(const CSLLongProxy &in_Value);

	/*! Assignment operator. Assigns \p in_Value to the parameter referred by this proxy.
		\param[in]	in_Value	The new value
		\return Reference to the current object.
	*/
    CSLLongProxy& operator =(const SI_Long &in_Value);

    /*! Comparison operator. Compares \p in_ToCompare with the value of the parameter referred by this proxy.
		\param[in]	in_ToCompare	The instance to compare values with
		\return	Whether or not the referred parameter and \p in_ToCompare are equal
	*/
	SI_Bool operator ==(const CSLLongProxy &in_ToCompare);

	/*! Comparison operator. Compares \p in_ToCompare with the value of the parameter referred by this proxy.
		\param[in]	in_ToCompare	The instance to compare values with
		\return	Whether or not the referred parameter and \p in_ToCompare are equal
	*/
	SI_Bool operator ==(const SI_Long &in_ToCompare);

	//! Conversion operator
    operator SI_Long();

	/*! Returns the animatable type of this class
		\retval CSLAnimatableType::SI_LONG_TYPE Animatable type
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
	virtual SI_Error	Connect (CdotXSITemplate *in_pTemplate, SI_Int in_nIndex );

private:
	CSLLongProxy( CSLLongProxy &in_pBasicType ){}
    SI_Long* m_pValue;
};


#endif
