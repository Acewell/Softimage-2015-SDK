//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file SL_Bool.h
	\brief Defines the CSLBoolProxy class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _BOOL_H
#define _BOOL_H

#include "AnimatableType.h"		// CSLAnimatableType
class CCOLLADATemplate;
class CSLCOLLADAScene;

/*! \brief Class that allows modification of a boolean parameter in a template
*/
class XSIEXPORT CSLBoolProxy : public CSLAnimatableType
{
public:
	/*! Constructor. Connects to a boolean parameter in a template
		\param[in] in_pTemplate Pointer to the template
		\param[in] in_nIndex Index of the parameter in the template
	 */
    CSLBoolProxy(CdotXSITemplate *in_pTemplate, SI_Int in_nIndex );

	/*! Assignment operator. Assigns \p in_Value to the parameter referred by this proxy.
		\param[in]	in_Value	The new value
		\return Reference to the current object.
	*/
    CSLBoolProxy& operator =(const CSLBoolProxy &in_Value);

	/*! Assignment operator. Assigns \p in_Value to the parameter referred by this proxy.
		\param[in]	in_Value	The new value
		\return Reference to the current object.
	*/
    CSLBoolProxy& operator =(const SI_Bool &in_Value);

	/*! Comparison operator. Compares \p in_ToCompare with the value of the parameter referred by this proxy.
		\param[in]	in_ToCompare	The instance to compare values with
		\return	Whether or not the referred parameter and \p in_ToCompare are equal
	*/
    SI_Bool operator ==(const CSLBoolProxy &in_ToCompare);

	/*! Comparison operator. Compares \p in_ToCompare with the value of the parameter referred by this proxy.
		\param[in]	in_ToCompare	The instance to compare values with
		\return	Whether or not the referred parameter and \p in_ToCompare are equal
	*/
    SI_Bool operator ==(const SI_Bool &in_ToCompare);

	/*! Conversion operator.
	*/
    operator SI_Bool();

	/*! Returns the animatable type of this class
		\return CSLAnimatableType::SI_BOOL_TYPE Animatable type
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
	CSLBoolProxy( CSLBoolProxy &in_pBasicType ){}
    SI_Bool* m_pValue;
};

#endif
