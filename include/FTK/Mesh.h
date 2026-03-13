//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file Mesh.h
	\brief Defines the CSLMesh class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _MESH_H
#define _MESH_H

#include "Geometry.h"

class CSLPolygonList;
class CSLTriangleList;
class CSLTriangleStripList;
class CSLBaseShape;


/*! \brief Describes a mesh primitive (see the \xx ftk_SI_Mesh SI_Mesh \endxx template reference).

The CSLMesh class is used to manipulate the polygon, tiangle or tri-strip lists.
*/
class XSIEXPORT CSLMesh
	: public CSLGeometry
{
public:
	CSLMesh(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
	virtual ~CSLMesh();

	/*!	Clears the entire list of polygon lists
		\return Error code
	*/
	SI_Error						ClearPolygonLists();

	/*!	Clears the entire list of triangle lists
		\return Error code
	*/
	SI_Error						ClearTriangleLists();

	/*!	Clears the entire list of triangle strip lists
		\return Error code
	*/
	SI_Error						ClearTriangleStripLists();

	/*!	Returns the number of polygon lists for this mesh
		\return Number of polygon lists
	*/
	SI_Int							GetPolygonListCount();

	/*!	Returns the number of triangle lists for this mesh
		\return Number of triangle lists
	*/
	SI_Int							GetTriangleListCount();

	/*!	Returns the number of triangle strip lists for this mesh
		\return Number of triangle strip lists
	*/
	SI_Int							GetTriangleStripListCount();

	/*!	Returns the list of polygon lists used by this mesh
		\return A list of CSLPolygonList
	*/
	CSLPolygonList**				PolygonLists();

	/*!	Returns the list of triangle lists used by this mesh
		\return A list of CSLTriangleList
	*/
	CSLTriangleList**				TriangleLists();

	/*!	Returns the list of triangle strip lists used by this mesh
		\return A list of CSLTriangleStripList
	*/
	CSLTriangleStripList**			TriangleStripLists();

	/*!	Adds a new polygon list to the mesh.
		\return Pointer to the newly created polygon list object.
	*/
	CSLPolygonList* 				AddPolygonList();

	/*!	Adds a new triangle list to the mesh.
		\return Pointer to the newly created triangle list object.
	*/
	CSLTriangleList*				AddTriangleList();

	/*!	Adds a new triangle strip list to the mesh.
		\return Pointer to the newly created triangle strip list object.
	*/
	CSLTriangleStripList*			AddTriangleStripList();

	/*!	Removes a single polygon list from the mesh.
		\param[in]	l_nIndex	Index of the polygon list to remove.
		\return Error code.
	*/
	SI_Error						RemovePolygonList(SI_Int l_nIndex);

	/*!	Removes a single triangle list from the mesh.
		\param[in]	l_nIndex	Index of the triangle list to remove.
		\return Error code.
	*/
	SI_Error						RemoveTriangleList(SI_Int l_nIndex);

	/*!	Removes a single triangle strip list from the mesh.
		\param[in]	l_nIndex	Index of the triangle strip list to remove.
		\return Error code.
	*/
	SI_Error						RemoveTriangleStripList(SI_Int l_nIndex);

	/*!	Removes a single polygon list from the mesh.
		\param[in]	in_pObject	Pointer to the polygon list to remove.
		\return Error code.
	*/
	SI_Error						RemovePolygonList(CSLPolygonList* in_pObject);

	/*!	Removes a single triangle list from the mesh.
		\param[in]	in_pObject	Pointer to the triangle list to remove.
		\return Error code.
	*/
	SI_Error						RemoveTriangleList(CSLTriangleList* in_pObject);

	/*!	Removes a single triangle strip list from the mesh.
		\param[in]	in_pObject	Pointer to the triangle strip list to remove.
		\return Error code.
	*/
	SI_Error						RemoveTriangleStripList(CSLTriangleStripList* in_pObject);

	/*!	Returns the shape object of the mesh.
		\return Pointer to a shape object.
	*/
	CSLBaseShape*					Shape() { return m_pShape; };

	// Connection functions
	CSLBaseShape*					ConnectShape(CSLBaseShape*);
	CSLPolygonList* 				ConnectPolygonList(CSLPolygonList*);
	CSLTriangleList*				ConnectTriangleList(CSLTriangleList*);
	CSLTriangleStripList*			ConnectTriangleStripList(CSLTriangleStripList*);

	virtual SI_Error				Synchronize();
	virtual SI_Error				Fix();

	/*! Returns the type of this template
		\retval CSLTemplate::SI_MESH Template type
	*/
	virtual ETemplateType			Type() { return SI_MESH; };
    virtual CSLAnimatableType*		ParameterFromName(SI_Char *in_szName);

private:
	CSLBaseShape* m_pShape;
	CSIBCArray<CSLPolygonList *> m_PolygonLists;
	CSIBCArray<CSLTriangleList *> m_TriangleLists;
	CSIBCArray<CSLTriangleStripList *> m_TriangleStripLists;

	void *m_pReserved;	// reserved for future extension
};

#endif
