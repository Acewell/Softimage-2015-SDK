//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file VariantParameter.h
	\brief Defines the CSLVariantParameter and CSLCustomParameter classes

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _VARIANTPARAMETER_H
#define _VARIANTPARAMETER_H

#include "Template.h"

class CSLXSICustomParamInfo;
class CSLCOLLADAScene;

/*! \brief Represents variant parameters.
\sa CSLCustomPSet
*/
class XSIEXPORT CSLVariantParameter : public CSLAnimatableType
{
public:
	/*! Constructor
		\param[in] in_pTemplate		Parent Template
		\param[in] in_nValueIndex	Index
	*/
	CSLVariantParameter
	(
		CdotXSITemplate *in_pTemplate,
		SI_Int in_nValueIndex
	);

	//! Destructor
	virtual ~CSLVariantParameter();

	/*! Constructor
		\return The type stored in the variant
	*/
	CSLAnimatableType::EElementType ValueType();


	SI_TinyVariant* GetValue();

	/*! Sets the stored value
		\param[in] in_pNewVal Pointer to the new value to store
	*/
	SI_Void SetValue( SI_TinyVariant* in_pNewVal );

	/*! Returns the animatable type of this element
		\retval CSLVariantParameter::SI_VARIANT_TYPE Type of this element
	*/
	virtual CSLVariantParameter::EElementType Type(){ return CSLVariantParameter::SI_VARIANT_TYPE; }

	/*! Returns custom parameter information
		\note A CSLVariantParameter cannot contain custom parameter information.
		\retval NULL
	*/
	virtual CSLXSICustomParamInfo* CustomParamInfo(){ return (CSLXSICustomParamInfo *)NULL; }

	/*! Converts the value of the referred parameter to float
		\return The converted value
	*/
	virtual SI_Float GetFloatValue();

	/*! Sets the value of the referred parameter from a float
		\param[in] in_fValue The float value used to set the parameter
	*/
	virtual SI_Void SetFloatValue(SI_Float in_fValue);
};


/*! \brief Defines parameters in custom presets

\sa CSLCustomPSet
\note this class was introduced in dotXSI version 3.6
*/
class XSIEXPORT CSLCustomParameter :
	public CSLVariantParameter
{
public:
	/*! Constructor
		\param[in] in_pTemplate		Parent Template
		\param[in] in_nValueIndex	Index
	*/
	CSLCustomParameter
	(
		CdotXSITemplate *in_pTemplate,
		SI_Int in_nValueIndex
	);

	//! Destructor
	virtual ~CSLCustomParameter();

	///////////////////////////////////////////////////////////////////////////
	// Custom parameter information
	///////////////////////////////////////////////////////////////////////////

	/*! Returns custom parameter information
		\return Pointer to the custom parameter information or null if there's none
	*/
	CSLXSICustomParamInfo* CustomParamInfo();

	/*! Connects custom parameter information
		\param[in] in_pCustomParamInfo Pointer to the custom parameter information or null if there's none
	*/
	CSLXSICustomParamInfo* ConnectCustomParamInfo( CSLXSICustomParamInfo *in_pCustomParamInfo );

private:
	CSLXSICustomParamInfo *m_pCustomParamInfo;
};

#endif
