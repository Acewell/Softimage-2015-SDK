//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file TriangleStripList.h
	\brief Defines the CSLTriangleStripList class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _TRIANGLESTRIPLIST_H
#define _TRIANGLESTRIPLIST_H

#include "Template.h"

class CSLTriangleStrip;
class CSLBaseMaterial;


/*! \brief This class represents an \xx ftk_SI_TriStripList SI_TriStripList \endxx template.

	Describes a list of CSLTriangleStrips (see the \xx ftk_SI_TriStripList SI_TriStripList \endxx template reference).
	A mesh can be made up of 3 types of polygons. N-sided polygons (CSLPolygonList), Triangles (CSLTriangleList) and Tri-Strips
	(CSLTriangleStrip). The CSLTriangleStripList is simply a container of CSLTriangleStrips that share the same material. To
	access the triangle strips from a CSLMesh object (or to add new ones), you should use this class instead of working with
	the CSLTriangleStrip class directly.
*/
class XSIEXPORT CSLTriangleStripList
	: public CSLTemplate
{
public:
	CSLTriangleStripList(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
	virtual ~CSLTriangleStripList();

	/*!	Adds a new triangle strip to the list.
		\return Pointer to the newly created triangle strip object.
	*/
	CSLTriangleStrip*				AddTriangleStrip();

	/*!	Returns the number of triangle strips in this list
		\return Number of triangle strips
	*/
	SI_Int							GetTriangleStripCount();

	/*!	Returns the list of triangle strips in the object.
		\return A list of pointers to triangle strips objects.
	*/
	CSLTriangleStrip**				TriangleStrips();

	/*!	Removes a single triangle strip from the list.
		\param[in]	in_nIndex	Index of the triangle strip to remove.
		\return Error code.
	*/
	SI_Error						RemoveTriangleStrip(SI_Int in_nIndex);

	/*!	Removes a single triangle strip from the list.
		\param[in]	in_pTriangleStrip	Pointer to the triangle strip to remove.
		\return Error code.
	*/
	SI_Error						RemoveTriangleStrip(CSLTriangleStrip *in_pTriangleStrip);

	/*!	Clears the entire list of triangle strips
		\return Error code
	*/
	SI_Error						ClearTriangleStrips();

	/*!	Returns the material object of the triangle strip list.
		\return Texture projection name.
	*/
	CSLBaseMaterial*				GetMaterial() { return m_pMaterial; }

	/*!	Changes the material object of the triangle strip list.
		\param[in]	in_pNewMaterial	New material object.
	*/
	SI_Void							SetMaterial(CSLBaseMaterial *in_pNewMaterial) { m_pMaterial = in_pNewMaterial; }

	// Connection functions
	CSLTriangleStrip*				ConnectTriangleStrip(CSLTriangleStrip* in_pNewTriStrip);

	/*!	Returns the type of this template.
		\retval CSLTemplate::SI_TRIANGLE_STRIP_LIST Template type
	*/
	virtual ETemplateType			Type() { return SI_TRIANGLE_STRIP_LIST; }
	virtual SI_Error				Synchronize();
    virtual CSLAnimatableType*		ParameterFromName(SI_Char *in_szName);

private:
	CSIBCArray<CSLTriangleStrip* >	m_TriangleStrips;
	CSLBaseMaterial*				m_pMaterial;

	void *m_pReserved;	// reserved for future extension
};

#endif
