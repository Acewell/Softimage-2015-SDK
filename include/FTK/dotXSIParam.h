//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file dotXSIParam.h
	\brief Defines the CdotXSIParam class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

//***************************************************************************************
// Defines
//***************************************************************************************
#ifndef __DOTXSIPARAM_H
#define __DOTXSIPARAM_H

//***************************************************************************************
// Includes
//***************************************************************************************
#include "SIBCNode.h"
#include "SIBCString.h"

//***************************************************************************************
// CdotXSIParam | holds a prameter value of all the supported types (SI_TinyVariant)
// public | CSIBCNode
//***************************************************************************************

/*! \brief Class representing a parameter within a CdotXSITemplate.

	A CdotXSIParam object is the interface used to access type, value, and tweaking information
	for a parameter within a CdotXSITemplate. The class provides accessor and mutator functions
	that use the SI_TinyVariant structure.
*/
class XSIEXPORT CdotXSIParam : public CSIBCNode
{
public:

	enum
	{
		UNFORMATTED = 1
	};

	/*! Default constructor.
	Sets the parameter to a dummy type, and initializes its value.
	*/
	CdotXSIParam();

	/*! Constructor.
	Sets the parameter name to the string specified by \c i_sName and the parameter type
	specified by \c i_nVariantType. The constructor then initializes the parameter value
	to its default value, based on the type given. See the defines in @link vptypes_group
	Variant Parameter types@endlink	for information on which values this parameter can take on.

	\param[in]	i_sName			Name of the new parameter.
	\param[in]	i_nVariantType	Type of the new parameter. (See @link vptypes_group Variant Parameter types@endlink).
	*/
	CdotXSIParam( CSIBCString *i_sName, SI_Int i_nVariantType );

	/*! Constructor.
	Sets the parameter name to the string specified by \c i_sName and the parameter type
	specified by \c i_nVariantType. The constructor then initializes the parameter value
	to its default value, based on the type given. See the defines in @link vptypes_group
	Variant Parameter types@endlink	for information on which values this parameter can take on.

	\param[in]	i_sName			Name of the new parameter.
	\param[in]	i_nVariantType	Type of the new parameter. (See @link vptypes_group Variant Parameter types@endlink).
	*/
	CdotXSIParam( SI_Char *i_sName, SI_Int i_nVariantType );

	/*! Constructor.
	Sets the parameter name to the string specified by \c i_sName, the parameter type
	specified by \c i_nVariantType, and the Tweak type specified by \c i_nTweakType. The constructor
	then initializes the parameter value to its default value, based on the type given. See the
	defines in @link vptypes_group Variant Parameter types@endlink for information on which values
	this parameter can take on. See the defines in @link vtwktypes_group Variant Parameter Tweak types@endlink
	for information on wihch values this parameter can take on.

	\param[in]	i_sName			Name of the new parameter.
	\param[in]	i_nVariantType	Type of the new parameter. (See @link vptypes_group Variant Parameter types@endlink).
	\param[in]	i_nTweakType	Type of tweaking control. (See @link vtwktypes_group Variant Parameter Tweak types@endlink).
	*/
	CdotXSIParam( CSIBCString *i_sName, SI_Int i_nVariantType, SI_Int i_nTweakType );

	/*! Constructor.
	Sets the parameter name to the string specified by \c i_sName, the parameter type
	specified by \c i_nVariantType, and the Tweak type specified by \c i_nTweakType. The constructor
	then initializes the parameter value to its default value, based on the type given. See the
	defines in @link vptypes_group Variant Parameter types@endlink for information on which values
	this parameter can take on. See the defines in @link vtwktypes_group Variant Parameter Tweak types@endlink
	for information on wihch values this parameter can take on.

	\param[in]	i_sName			Name of the new parameter.
	\param[in]	i_nVariantType	Type of the new parameter. (See @link vptypes_group Variant Parameter types@endlink).
	\param[in]	i_nTweakType	Type of tweaking control. (See @link vtwktypes_group Variant Parameter Tweak types@endlink).
	*/
	CdotXSIParam( SI_Char *i_sName, SI_Int i_nVariantType, SI_Int i_nTweakType );

	/*! Constructor.
	Sets the parameter name to the string specified by \c i_sName. The parameter type, tweak type, and
	number of elements for the parameter is copied from the \c i_vValue parameter. The constructor
	then initializes the parameter value to its default value, based on the type in \c i_vValue.
	\note The values from \c i_vValue are \b not copied from the \c i_vValue parameter.

	\param[in]	i_sName			Name of the new parameter.
	\param[in]	i_vValue		Parameter value to use the type, tweak type and number of elements information from.
	*/
	CdotXSIParam( CSIBCString *i_sName, SI_TinyVariant i_vValue );

	/*! Constructor.
	Sets the parameter name to the string specified by \c i_sName. The parameter type, tweak type, and
	number of elements for the parameter is copied from the \c i_vValue parameter. The constructor
	then initializes the parameter value to its default value, based on the type in \c i_vValue.
	\note The values from \c i_vValue are \b not copied from the \c i_vValue parameter.

	\param[in]	i_sName			Name of the new parameter.
	\param[in]	i_vValue		Parameter value to use the type, tweak type and number of elements information from.
	*/
	CdotXSIParam( SI_Char *i_sName, SI_TinyVariant i_vValue );

	/*! Destructor
	Clears the variant parameter. This destructor frees the arrays located within its parameters's value.
	*/
	virtual ~CdotXSIParam();

	/*! Returns the value of this parameter in the \c o_vValue output parameter
	\param[out]	o_vValue	Pointer to receive the value of this parameter.
	*/
    SI_Void GetValue( SI_TinyVariant *o_vValue );

	/*! Sets the value of this parameter to the value of the parameter specified by \c i_vValue.
	\param[in]	i_vValue	Contains the new value for this parameter (includes type, tweak type, and number of elements).
	*/
	SI_Void SetValue( SI_TinyVariant i_vValue );

	/*! Returns a pointer to the SI_TinyVariant structure that contains the type and value
	information for this parameter.
	\return	Pointer to the structure that contains type and value information.
	*/
	SI_TinyVariant* GetVariantPtr(){ return &m_vValue; }								// Get Ptr to the stored variant.

    /*! Initializes this parameter's value and type information with the information contained
	in the \c i_pValue parameter (includes type, tweak type, and number of elements).
	\param[in]	i_pValue	Pointer to the structure containing type and value information to set.
	*/
    SI_Void InitializeVarValue( SI_TinyVariant *i_pValue );

	/*! Initializes this parameter's value to the default value, based on the type of the parameter.
	In general, the default value is zero (or equivalent for pointer types).
	*/
	SI_Void InitializeDefaultVarValue();

	CdotXSIParam*	Clone();
	void			Serialize(CSIBCString& in_szBuffer);
	void			UnSerialize(CSIBCString& in_szBuffer);

private:
	SI_Void ClearVariant();										// Clears the content of the variant

	SI_TinyVariant  m_vValue;
};

//***************************************************************************************
// Global Functions
//***************************************************************************************
XSIEXPORT CdotXSIParam* CreatedotXSIParam();								// Allocate a CdotXSIParam
XSIEXPORT void			AllocateLocalXSIArray(SI_TinyVariant*, SI_Long);	// Allocate a Val array in the biven TinyVariant
CSIBCString				GetNextSerializedToken ( CSIBCString &in_szString );
#endif // __DOTXSIPARAM_H
