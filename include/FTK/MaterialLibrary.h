//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file MaterialLibrary.h
	\brief Defines the CSLMaterialLibrary class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _MATERIALLIBRARY_H
#define _MATERIALLIBRARY_H

#include "Template.h"

// Forward declaration
class CSLBaseMaterial;
class CSLMaterial;
class CSLXSIMaterial;


/*! \brief This class represents an \xx ftk_SI_MaterialLibrary SI_MaterialLibrary \endxx template.

	Handles the material library (see the \xx ftk_SI_MaterialLibrary SI_MaterialLibrary \endxx
	template reference). From this class you can add or remove materials that can be used in the scene.
*/
class XSIEXPORT CSLMaterialLibrary
	: public CSLTemplate
{
public:
	CSLMaterialLibrary(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
	virtual ~CSLMaterialLibrary();

	/*!	Adds a new material to the material library.
		\return Pointer to the newly created material object.
	*/
	CSLMaterial* AddMaterial();

	/*!	Adds a new Softimage material to the material library.
		\return Pointer to the newly created Softimage material object.
	*/
	virtual CSLXSIMaterial* AddXSIMaterial();

	/*!	Removes all materials from the material library.
		\return Error code.
	*/
	SI_Error ClearMaterials();

	/*!	Returns an array of all materials in the library.
		\return Array of pointers to material objects.
	*/
	CSLBaseMaterial** GetMaterialList();

	/*!	Returns the number of materials in the library.
		\return Number of materials.
	*/
	SI_Int GetMaterialCount();

	/*!	Removes a single material from the library.
		\param[in]	in_nIndex	Index of the material to remove.
		\return Error code.
	*/
	SI_Error RemoveMaterial(SI_Int in_nIndex);

	/*!	Removes a single material from the library.
		\param[in]	in_pMaterial	Pointer to the material to remove.
		\return Error code.
	*/
	SI_Error RemoveMaterial(CSLBaseMaterial *in_pMaterial);

	CSLBaseMaterial* FindMaterial( const SI_Char* in_szName );

	CSLBaseMaterial* ConnectMaterial(CSLBaseMaterial* in_pNewMaterial);

    virtual SI_Error Synchronize();

	/*!	Returns the type of this template
		\return CSLTemplate::SI_MATERIAL_LIBRARY Template type
	*/
    virtual ETemplateType Type();

protected:
	CSIBCArray<CSLBaseMaterial *> m_Materials;

private:
	void *m_pReserved;	// reserved for future extension
};

#endif
