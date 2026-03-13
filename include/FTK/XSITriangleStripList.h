//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSITriangleStripList.h
	\brief Defines the CSLXSITriangleStripList class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _XSITRIANGLESTRIPLIST_H
#define _XSITRIANGLESTRIPLIST_H

#include "XSISubComponentList.h"
#include "Material.h"

/*! \brief This class represents an \xx ftk_XSI_TriangleStripList XSI_TriangleStripList \endxx template.

	Describes a list of triangle strips that are made up of N number of vertices for dotXSI 5.0+ (see the
	\xx ftk_XSI_TriangleStripList XSI_TriangleStripList \endxx template reference). The polynodes in this list
	can have N number of attibutes like vertex, normals, UV and color information.

	\tip You can use GetVertexIndices() to get the mandatory vertex index attributes and the parent class
	(CSLXSISubComponentList) functionality to get the other generic attributes index.
	<BR><BR>
	You can use GetTriangleStripCount() to get the number of triangle strips in the list.
	<BR><BR>
	To find out how many vertices a particular triangle strip uses, get the list of triangle strip vertex
	count using GetTriangleStripNodeCountArray().
*/
class XSIEXPORT CSLXSITriangleStripList
	: public CSLXSISubComponentList
{
public:
	/*! Proxy class that allows modifying a list of SI_Int like an array.
	*/
	typedef CSLArrayProxy<SI_Int, SI_Int, 1> CSLIntArray;

	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Refered template
		\return an instance of CSLXSITriangleStripList
	*/
	CSLXSITriangleStripList(CSLScene *in_pScene, CSLModel *in_pModel, CdotXSITemplate *in_pTemplate);

	/*! Destructor
	*/
	virtual ~CSLXSITriangleStripList();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_TRIANGLE_STRIP_LIST The type of this template
	*/
	virtual ETemplateType			Type() { return XSI_TRIANGLE_STRIP_LIST; }

	/*!	Returns the material object of the triangle strip list.
		\return Material object.
	*/
	CSLBaseMaterial*				GetMaterial() { return m_pMaterial; }

	/*!	Returns the material object name of the triangle strip list or an empty string if there's none.
		\return Material object name.
	*/
	CSIBCString						GetMaterialName();

	/*!	Changes the material object of the triangle strip list.
		\param[in]	in_pNewMaterial	New material object.
	*/
	SI_Void							SetMaterial(CSLBaseMaterial *in_pNewMaterial);

	/*!	Changes the material object name of the triangle strip list. Should ONLY be called if we don't export the material.
		\param[in]	in_szNewMaterialName	New material object name.
	*/
	SI_Void							SetMaterialName(const CSIBCString& in_szNewMaterialName);

	/*! Returns the number of triangle strip.
		\return Number of triangle strip.
	*/
	SI_Int							GetTriangleStripCount();

	/*! Returns the triangle strip node count array.
		\return Array of triangle strip node count.
	*/
	CSLXSITriangleStripList::CSLIntArray*	GetTriangleStripNodeCountArray();

	/*! Returns the polynode vertex indices array.
		\return Array of polynode vertex indices.
	*/
	CSLIntArray*					GetVertexIndices();

	/*! Sets the number of polynode in this triangle strip list.
		\return Error code.
	*/
	virtual SI_Error				SetCount(SI_Int);

	/*! Commits the current template information
		\return Whether or not the commit was successful
	*/
	SI_Error Synchronize();

private:
	CSLIntArray						m_TriangleStripNodeCountArray;

	CSLIntArray						m_VertexIndices;

	CSLBaseMaterial*				m_pMaterial;

	CSIBCString						m_szMaterialName;

	void *m_pReserved;	// reserved for future extension
};

#endif
