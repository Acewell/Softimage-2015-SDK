//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSIPolygonList.h
	\brief Defines the CSLXSIPolygonList class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _XSIPOLYGONLIST_H
#define _XSIPOLYGONLIST_H

#include "XSISubComponentList.h"
#include "Material.h"
#include "Scene.h"
#include "Model.h"
#include "XSIIndexList.h"

/*! \brief This class represents an \xx ftk_XSI_PolygonList XSI_PolygonList \endxx template.

	Describes a list of n-sided polygons for dotXSI 5.0+ (see the \xx ftk_XSI_PolygonList XSI_PolygonList \endxx template reference).
	The polynodes in this list can have \c n number of attibutes like vertex, normals, UV and color information.

	\tip You can use GetVertexIndices() to get the mandatory vertex index attributes and the parent class (CSLXSISubComponentList)
		functionality to get the other generic attributes index.
		<BR><BR>
		You can use GetPolygonCount() to get the number of polygons in the list.
		<BR><BR>
		To find out how many vertices a particular polygon uses, use GetPolygonNodeCountArray() to get the list of polygon vertices.
*/
class XSIEXPORT CSLXSIPolygonList
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
		\return an instance of CSLXSIPolygonList
	*/
	CSLXSIPolygonList(CSLScene *in_pScene, CSLModel *in_pModel, CdotXSITemplate *in_pTemplate);

	/*! Destructor
	*/
	virtual ~CSLXSIPolygonList();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_POLYGON_LIST The type of this template
	*/
	virtual ETemplateType			Type() { return XSI_POLYGON_LIST; }

	/*!	Returns the material object of the polygon list.
		\return Material object.
	*/
	CSLBaseMaterial*				GetMaterial() { return m_pMaterial; }

	/*! Returns the material object name of the polygon list or an empty string if there's none.
		\return 		Material object name.
	*/
	CSIBCString						GetMaterialName();

	/*!	Changes the material object of the polygon list.
		\param[in]	in_pNewMaterial	New material object.
	*/
	SI_Void							SetMaterial(CSLBaseMaterial *in_pNewMaterial);

	/*!	Changes the material object name of the polygon list. Should ONLY be called if we don't export the material.
		\param[in]	in_szNewMaterialName	New material object name.
	*/
	SI_Void							SetMaterialName(const CSIBCString& in_szNewMaterialName);

	/*! Returns the number of polygon.
		\return Number of polygon.
	*/
	SI_Int							GetPolygonCount();

	/*! Returns the polygon count array.
		\return Array of polygon node count.
	*/
	CSLIntArray*					GetPolygonNodeCountArray();

	/*! Returns the polynode vertex indices array.
		\return Array of polynode vertex indices.
	*/
	CSLIntArray*					GetVertexIndices();

	/*! Commits the current template information
		\return Whether or not the commit was successful
	*/
	SI_Error Synchronize();

	/*! Sets the number of polynode in this polygon list.
		\return Error code.
	*/
	virtual SI_Error					SetCount(SI_Int);

	//**********************************************************************************
	// Index position helper (always only one index position list)
	//**********************************************************************************

	/*!	Connects a new index list.
		\param[in] in_pNewXSIIndexList Index position list to connect
		\return The newly connected index list.
	*/
	CSLXSIIndexList*	ConnectIndexList( CSLXSIIndexList* in_pNewXSIIndexList );

	/*!	Adds a new index list. If an index list already exists, it will be deleted, and replaced.
		\return Pointer to the newly created index list.
	*/
	virtual CSLXSIIndexList*	AddIndexList();

	/*!	Returns the index list. May return NULL if it does not exist.
		\return Pointer to the index list.
	*/
	CSLXSIIndexList*	GetIndexList();

	/*!	Removes the index list.
		\return Error code.
	*/
	SI_Error							RemoveIndexList();

private:
	CSLIntArray						m_PolygonNodeCountArray;

	CSLIntArray						m_VertexIndices;

	CSLBaseMaterial*				m_pMaterial;

	CSIBCString						m_szMaterialName;

	CSLXSIIndexList *				m_IndexList;

	void *m_pReserved;	// reserved for future extension
};

#endif
