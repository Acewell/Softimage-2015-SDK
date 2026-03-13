//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSITriangleList.h
	\brief Defines the CSLXSITriangleList class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _XSITRIANGLELIST_H
#define _XSITRIANGLELIST_H

#include "XSISubComponentList.h"
#include "Material.h"


/*! \brief This class represents an \xx ftk_XSI_TriangleList XSI_TriangleList \endxx template.

	Describes a list of triangles for dotXSI 5.0+ (see the \xx ftk_XSI_TriangleList XSI_TriangleList \endxx
	template reference). The polynodes in this list can have N number of attibutes like vertex, normals, UV and
	color information.

	\tip You can use GetVertexIndices() to get the mandatory vertex index attributes and the parent class
		(CSLXSISubComponentList) functionality to get the other generic attributes index.
		<BR><BR>
		You can use GetTriangleCount() to get the number of triangles in the list.
*/
class XSIEXPORT CSLXSITriangleList
	: public CSLXSISubComponentList
{
public:
	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Refered template
		\return an instance of CSLXSITriangleList
	*/
	CSLXSITriangleList(CSLScene *in_pScene, CSLModel *in_pModel, CdotXSITemplate *in_pTemplate);

	/*! Destructor
	*/
	virtual ~CSLXSITriangleList();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_TRIANGLE_LIST The type of this template
	*/
	virtual ETemplateType			Type() { return XSI_TRIANGLE_LIST; }

	/*!	Returns the material object of the triangle list.
		\return Material object.
	*/
	CSLBaseMaterial*				GetMaterial() { return m_pMaterial; }

	/*!	Returns the material object name of the triangle list or an empty string if there's none.
		\return Material object name.
	*/
	CSIBCString 					GetMaterialName();

	/*!	Changes the material object of the triangle list.
		\param[in]	in_pNewMaterial	New material object.
	*/
	SI_Void							SetMaterial(CSLBaseMaterial *in_pNewMaterial);

	/*!	Changes the material object name of the triangle list. Should ONLY be called if we don't export the material.
		\param[in]	in_szNewMaterialName	New material object name.
	*/
	SI_Void							SetMaterialName(const CSIBCString& in_szNewMaterialName);

	/*! Returns the polynode vertex indices array.
		\return Array of polynode vertex indices.
	*/
	CSLIntArray*					GetVertexIndices();

	/*! Returns the number of triangle.
		\return Number of triangle.
	*/
	SI_Int							GetTriangleCount();

	/*! Sets the number of polynode in this triangle list.
		\return Error code.
	*/
	virtual SI_Error				SetCount(SI_Int);

	/*! Commits the current template information
		\return Whether or not the commit was successful
	*/
	virtual SI_Error Synchronize();

private:
	CSLIntArray						m_VertexIndices;

	CSLBaseMaterial*				m_pMaterial;

	CSIBCString						m_szMaterialName;

	void *m_pReserved;	// reserved for future extension
};

#endif
