//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file SL_ULong.h
	\brief Defines the CSLULongProxy class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _ULONG_H
#define _ULONG_H

#include "AnimatableType.h" // CSLAnimatableType
class CCOLLADATemplate;
class CSLCOLLADAScene;

/*! \brief Class that allows modification of a ULong parameter in a template
*/
class XSIEXPORT CSLULongProxy : public CSLAnimatableType
{
public:
	/*! Constructor. Connects to a parameter in the parent template
		\param[in] in_pTemplate Pointer to the parent template
		\param[in] in_nIndex Index of the parameter in the template
	*/
	CSLULongProxy(CdotXSITemplate *in_pTemplate, SI_Int in_nIndex );

	/*! Assignment operator. Assigns \p in_Value to the parameter referred by this proxy.
		\param[in]	in_Value	The new value
		\return Reference to the current object.
	*/
    CSLULongProxy& operator =(const CSLULongProxy &in_Value);

	/*! Assignment operator. Assigns \p in_Value to the parameter referred by this proxy.
		\param[in]	in_Value	The new value
		\return Reference to the current object.
	*/
    CSLULongProxy& operator =(const SI_ULong &in_Value);

    /*! Comparison operator. Compares \p in_ToCompare with the value of the parameter referred by this proxy.
		\param[in]	in_ToCompare	The instance to compare values with
		\return	Whether or not the referred parameter and \p in_ToCompare are equal
	*/

	SI_Bool operator ==(const CSLULongProxy &in_ToCompare);

	/*! Comparison operator. Compares \p in_ToCompare with the value of the parameter referred by this proxy.
		\param[in]	in_ToCompare	The instance to compare values with
		\return	Whether or not the referred parameter and \p in_ToCompare are equal
	*/
	SI_Bool operator ==(const SI_ULong &in_ToCompare);

	//! Conversion operator
    operator SI_ULong();

	/*! Returns the animatable type of this class
		\retval CSLAnimatableType::SI_ULONG_TYPE Animatable type
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

	/*! Connects the proxy to the IO layer parameter
		\param[in] in_pTemplate the template that owns the parameter to connect to
		\param[in] in_iIndex the index of the parameter
		\return The proxy was succesfully connected or not
	*/
	virtual SI_Error Connect ( CdotXSITemplate* in_pTemplate, SI_Int in_iIndex);

private:
	CSLULongProxy( CSLULongProxy &in_pBasicType ){}
    SI_ULong* m_pValue;
};


#endif
