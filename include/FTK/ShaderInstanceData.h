//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file ShaderInstanceData.h
	\brief Defines the CSLShaderInstanceData class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _SHADER_INSTANCE_DATA_H
#define _SHADER_INSTANCE_DATA_H

#include "Template.h"

class CSLVariantParameter;

/*! \brief This class represents an \xx ftk_XSI_ShaderInstanceData XSI_ShaderInstanceData \endxx template.

	Defines how a shader is shared beetween models (see the
	\xx ftk_XSI_ShaderInstanceData XSI_ShaderInstanceData \endxx template reference)
*/
class XSIEXPORT CSLShaderInstanceData
    : public CSLTemplate
{
public:

	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Refered template
		\return an instance of CSLShaderInstanceData
	*/
	CSLShaderInstanceData
	(
		CSLScene* in_pScene,
		CSLModel *in_pModel,
		CdotXSITemplate* in_pTemplate
	);

	/*! Destructor
	*/
	~CSLShaderInstanceData();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_SHADER_INSTANCE_DATA The type of this template
	*/
    inline ETemplateType Type();

	/*! Commits semantic layer data to the dotXSI template
		\return Whether or not data was commited correctly
	*/
	SI_Error Synchronize();

	// Reference Functionality ////////////////////////////////////////////////////

	/*! Returns the referenced Model
		\return Pointer to referenced Model or null if there's none
	*/
    CSLModel* GetReference();

	/*! Sets the referenced Model
		\param[in] in_pReferedModel Pointer to refered Model.
	*/
	SI_Void SetReference( CSLModel* in_pReferedModel);


	// Parameters Functionality ///////////////////////////////////////////////

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

	/*! Removes all parameters from the parameter list
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
	* \return Number of parameters
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
	CSLAnimatableType* ParameterFromType(EFCurveType in_Type, SI_Char *in_szParameterName);

private:
	CSLModel *m_pReferedModel;
	CSIBCArray<CSLVariantParameter *> m_Parameters;

	SI_Void *m_pReserved;	// reserved for future extension
};


#endif // _SHADER_INSTANCE_DATA_H
