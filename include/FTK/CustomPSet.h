//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file CustomPSet.h
	\brief Defines the CSLCustomPSet class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _CUSTOMPSET_H
#define _CUSTOMPSET_H

#include "Template.h"

// Forward declaration
class CSLVariantParameter;
class CSLXSICustomParamInfo;

/*! \brief This class represents an \xx ftk_XSI_CustomPSet XSI_CustomPSet \endxx template.

Class representing customer parameter sets (see the \xx ftk_XSI_CustomPSet XSI_CustomPSet \endxx
template reference)
*/
class XSIEXPORT CSLCustomPSet
    : public CSLTemplate
{
public:
	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Referred template
		\return an instance of CSLCustomPSet
	*/
    CSLCustomPSet(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	//! Destructor
    virtual ~CSLCustomPSet();

	/*! Commit the current template information
		\return Whether or not the commit was successful
	*/
    virtual SI_Error Synchronize();

	/*! Returns the type of this template
		\retval ETemplateType::SI_CUSTOM_PSET Template type
	*/
    virtual ETemplateType Type() { return SI_CUSTOM_PSET; }

	//! Defines the various propagation types
	enum EPropagationType
	{
		SI_BRANCH,		/*!< Branch propagation */
		SI_NODE,		/*!< Node propagation */
		SI_INHERITED	/*!< Inherited propagation */
	};

	/*! Returns the propagation type
		\return The propagation type
	*/
	EPropagationType GetPropagationType();

	/*! Sets the propagation type
		\param[in] in_PropagationType New type of propagation tp use
	*/
	SI_Void SetPropagationType( EPropagationType in_PropagationType );

	///////////////////////////////////////////////////////////////////////////
	// Parameters Functionality ///////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	/*! Adds a parameter to the parameter list
		\return Pointer to the newly added parameter
	*/
	CSLVariantParameter* AddParameter();

	/*! Removes a parameter from the parameter list
		\param[in] in_nIndex Index of the parameter to remove
		\return Whether or not the parameter could be removed
	*/
	SI_Error RemoveParameter( SI_Int in_nIndex );

	/*! Removes a parameter from the parameter list
		\param[in] in_pToRemove Pointer to the parameter to remove
		\return Whether or not the parameter could be removed
	*/
	SI_Error RemoveParameter( CSLVariantParameter* in_pToRemove );

	/*! Removes all connections points from the parameter list
		\return Whether or not the list could be cleared
	*/
	SI_Error ClearParameters();

	/*! Adds an exisiting parameter to the parameter list
		\param[in] in_pToConnect Pointer to the parameter to add
		\return The added parameter or null if it already exists in the list
	*/
	CSLVariantParameter* ConnectParameter( CSLVariantParameter* in_pToConnect );

	/*! Returns a pointer to the internally-stored parameter pointer list
		\return Pointer to the list
	*/
	CSLVariantParameter** GetParameterList();

	/*! Returns the total number of parameters
		\return Number of parameters
	*/
	SI_Int GetParameterCount();

	/*! Searches for a parameter by name
		\param[in] in_szName Name of the parameter to look for
		\return Pointer to the found parameter or null if not found
	*/
	virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);

	/*! Searches for a parameter by name and type
		\param[in] in_Type Type of the parameter to look for
		\param[in] in_szParameterName Name of the parameter to look for
		\return Pointer to the found parameter or null if not found
	*/
    virtual CSLAnimatableType* ParameterFromType(EFCurveType in_Type, SI_Char *in_szParameterName);

	///////////////////////////////////////////////////////////////////////////
	// Custom parameter information
	///////////////////////////////////////////////////////////////////////////

	/*! Creates a new custom parameter information
		\param[in] in_nIndex Index of the parameter where to attach the new custom parameter information
		\return Pointer to the new custom parameter information or null creation could not be done
		\since dotXSI 3.6
	*/
	CSLXSICustomParamInfo* CreateCustomParamInfo( SI_Int in_nIndex );

	/*! Creates a new custom parameter information
		\param[in] in_pParam Pointer to the parameter object on which to attach the new custom parameter information. It is the
			caller's responsibility to ensure that the parameter pointer points to a parameter from this PSet. If you are unsure,
		    then use CreateCustomParamInfo( SI_Int in_nIndex )
		\return CSLXSICustomParamInfo Pointer to the new custom parameter information or null if creation could not be done
		\since dotXSI 3.6
	*/
	CSLXSICustomParamInfo* CreateCustomParamInfo( CSLVariantParameter * in_pParam );

	/*! Connects custom parameter information
		\param[in] in_pToConnect Pointer to the custom parameter information
		\return CSLXSICustomParamInfo Pointer to the newly connected parameter information or null if the refered parameter does not exist or if there's already a custom parameter information
		\since dotXSI 3.6
	*/
	CSLXSICustomParamInfo* ConnectCustomParamInfo( CSLXSICustomParamInfo *in_pToConnect );

	/*! Returns the custom parameter information type
		\return char* NULL if there is no type. NULL if the file is < 5.0
		\since dotXSI 5.0
	*/
	char *GetType();

	/*! Sets the custom parameter information type. Note, this only works with 5.0 files
		\param[in] in_pType The new type
		\return void
		\since dotXSI 5.0
	*/
	void SetType(char *in_pType);

private:
	CSLStrEnumProxy<EPropagationType, SI_INHERITED>  m_PropagationType;
    CSIBCArray<CSLVariantParameter*> m_Parameters;

	SI_Void *m_pReserved;	// Reserved for future use
};

#endif
