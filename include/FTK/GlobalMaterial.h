//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file GlobalMaterial.h
	\brief Defines the CSLGlobalMaterial class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _GLOBALMATERIAL_H
#define _GLOBALMATERIAL_H

#include "Template.h"

// Forward declaration
class CSLBaseMaterial;

/*! \brief This class represents an \xx ftk_SI_GlobalMaterial SI_GlobalMaterial \endxx template.

	Identifies the global material of a model (see the \xx ftk_SI_GlobalMaterial SI_GlobalMaterial \endxx
	template reference).
*/
class XSIEXPORT CSLGlobalMaterial
    : public CSLTemplate
{
public:
	//! Defines the various propagation types
	enum EPropagationType
	{
		SI_BRANCH,		/*!< Branch propagation */
		SI_NODE,		/*!< Node propagation */
		SI_INHERITED	/*!< Inherited propagation */
	};

	/*! Constructor
		\note If the file contains an invalid propagation type, NODE is assumed.
		\param[in] in_pScene Parent Scene
		\param[in] in_pModel Parent Model
		\param[in] in_pTemplate Parent Template
		\return an instance of CSLGlobalMaterial
	*/
	CSLGlobalMaterial
	(
		CSLScene* in_pScene,
		CSLModel *in_pModel,
		CdotXSITemplate* in_pTemplate
	);

	//! Destructor
    ~CSLGlobalMaterial();

	/*! Returns the referenced material
		\return Pointer to referenced material or null if there's none
	*/
    CSLBaseMaterial* GetMaterial();

	/*! Returns the referenced material name
		\return The name of the referenced material or an empty string if there's none
	*/
	CSIBCString GetMaterialName();

	/*! Sets the referenced material
		\param[in] in_pNewMaterial Pointer to new refered material.
	*/
	SI_Void SetMaterial( CSLBaseMaterial*  in_pNewMaterial );

	/*! Sets the referenced material name. Should ONLY be called if we don't export the material.
		\param[in] in_szNewMaterialName The new refered material name.
	*/
	SI_Void SetMaterialName( const CSIBCString&  in_szNewMaterialName );

    /*! Returns the propagation type
		\return The propagation type
	*/
	EPropagationType GetPropagationType();

	/*! Sets the propagation type
		\param[in] in_PropagationType New type of propagation tp use
	*/
	SI_Void SetPropagationType( EPropagationType in_PropagationType );

	/*! Returns the type of this template
		\retval CSLTemplate::SI_GLOBAL_MATERIAL The type of this template
	*/
	CSLTemplate::ETemplateType Type();

	/*! Synchronize with the parent template data
		\return Whether or not data could be updated
	*/
	SI_Error Synchronize();

private:
    CSLBaseMaterial* m_pMaterial;
	CSIBCString	m_szMaterialName;
    CSLStrEnumProxy<EPropagationType, SI_INHERITED>  m_PropagationType;

	// reserved for future use
	SI_Void *m_pReserved;
};

#endif
