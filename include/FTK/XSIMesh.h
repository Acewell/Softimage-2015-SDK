//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSIMesh.h
	\brief Defines the CSLXSIMesh class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

/******************************************************************************\
*
* File: 		 XSIMesh.h
* Creation date: January 17, 2005
* Purpose:		 Declaration of class 'CSLXSIMesh'
*
\******************************************************************************/
#ifndef _XSIMESH_H
#define _XSIMESH_H

#include "XSIGeometry.h"

class CSLXSIVertexList;
class CSLXSIPolygonList;
class CSLXSITriangleList;
class CSLXSITriangleStripList;
class CSLXSIShape;


/*! \brief This class represents an \xx ftk_XSI_Mesh XSI_Mesh \endxx template.

	Base class to describe a mesh primitive for dotXSI 5.0+ (see the
	\xx ftk_XSI_Mesh XSI_Mesh \endxx template reference).
*/
class XSIEXPORT CSLXSIMesh
	: public CSLXSIGeometry
{
public:
	CSLXSIMesh(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
	virtual ~CSLXSIMesh();

	/*!	Clears the entire list of polygon lists
		\return Error code
	*/
	SI_Error						ClearXSIPolygonLists();

	/*!	Clears the entire list of triangle lists
		\return Error code
	*/
	SI_Error						ClearXSITriangleLists();

	/*!	Clears the entire list of triangle strip lists
		\return Error code
	*/
	SI_Error						ClearXSITriangleStripLists();

	/*!	Returns the number of polygon lists for this mesh
		\return Number of polygon lists
	*/
	SI_Int							GetXSIPolygonListCount();

	/*!	Returns the number of triangle lists for this mesh
		\return Number of triangle lists
	*/
	SI_Int							GetXSITriangleListCount();

	/*!	Returns the number of triangle strip lists for this mesh
		\return Number of triangle strip lists
	*/
	SI_Int							GetXSITriangleStripListCount();

	/*!	Returns the list of polygon lists used by this mesh
		\return A list of CSLXSIPolygonList
	*/
	CSLXSIPolygonList**				XSIPolygonLists();

	/*!	Returns the list of triangle lists used by this mesh
		\return A list of CSLXSITriangleList
	*/
	CSLXSITriangleList**			XSITriangleLists();

	/*!	Returns the list of triangle strip lists used by this mesh
		\return A list of CSLXSITriangleStripList
	*/
	CSLXSITriangleStripList**		XSITriangleStripLists();

	/*!	Adds a new polygon list to the mesh.
		\return Pointer to the newly created polygon list object.
	*/
	virtual CSLXSIPolygonList* 				AddXSIPolygonList();

	/*!	Adds a new triangle list to the mesh.
		\return Pointer to the newly created triangle list object.
	*/
	virtual CSLXSITriangleList*				AddXSITriangleList();

	/*!	Adds a new triangle strip list to the mesh.
		\return Pointer to the newly created triangle strip list object.
	*/
	CSLXSITriangleStripList*		AddXSITriangleStripList();

	/*!	Removes a single polygon list from the mesh.
		\param[in]	l_nIndex	Index of the polygon list to remove.
		\return Error code.
	*/
	SI_Error						RemoveXSIPolygonList(SI_Int l_nIndex);

	/*!	Removes a single triangle list from the mesh.
		\param[in]	l_nIndex	Index of the triangle list to remove.
		\return Error code.
	*/
	SI_Error						RemoveXSITriangleList(SI_Int l_nIndex);

	/*!	Removes a single triangle strip list from the mesh.
		\param[in]	l_nIndex	Index of the triangle strip list to remove.
		\return Error code.
	*/
	SI_Error						RemoveXSITriangleStripList(SI_Int l_nIndex);

	/*!	Removes a single polygon list from the mesh.
		\param[in]	in_pObject	Pointer to the polygon list to remove.
		\return Error code.
	*/
	SI_Error						RemoveXSIPolygonList(CSLXSIPolygonList* in_pObject);

	/*!	Removes a single triangle list from the mesh.
		\param[in]	in_pObject	Pointer to the triangle list to remove.
		\return Error code.
	*/
	SI_Error						RemoveXSITriangleList(CSLXSITriangleList* in_pObject);

	/*!	Removes a single triangle strip list from the mesh.
		\param[in]	in_pObject	Pointer to the triangle strip list to remove.
		\return Error code.
	*/
	SI_Error						RemoveXSITriangleStripList(CSLXSITriangleStripList* in_pObject);

	/*!	Returns the shape object of the mesh.
		\return Pointer to a shape object.
	*/
	CSLXSIShape*					XSIShape() { return m_pXSIShape; };

	/*!	Returns the vertex list object of the mesh.
		\return Pointer to a vertex list object.
	*/
	CSLXSIVertexList*				XSIVertexList() { return m_pXSIVertexList; };

	/*! Connects a shape
		\return The connected shape
	*/
	CSLXSIShape*					ConnectXSIShape(CSLXSIShape* /*!< the shape to connect */);

	/*! Connects a vertex list
		\return The connected vertex list
	*/
	CSLXSIVertexList* 				ConnectXSIVertexList(CSLXSIVertexList* /*!< the vertex list to connect */);

	/*! Connects a polygon list
		\return The connected polygon list
	*/
	CSLXSIPolygonList* 				ConnectXSIPolygonList(CSLXSIPolygonList* /*!< the polygon list to connect */);

	/*! Connects a triangle list
		\return The connected triangle list
	*/
	CSLXSITriangleList*				ConnectXSITriangleList(CSLXSITriangleList* /*!< the triangle list to connect */);

	/*! Connects a triangle strip list
		\return The connected triangle strip list
	*/
	CSLXSITriangleStripList*		ConnectXSITriangleStripList(CSLXSITriangleStripList* /*!< the triangle strip list to connect */);

	/*! Synchronizes this Softimage mesh instance with its IO layer representation
		\return Error code.
	*/
	virtual SI_Error				Synchronize();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_MESH The type of this template
	*/
	virtual ETemplateType			Type() { return XSI_MESH; };

	virtual SI_Error				Fix();
    virtual CSLAnimatableType*		ParameterFromName(SI_Char *in_szName);

protected:
	CSLXSIShape* m_pXSIShape;
	CSLXSIVertexList *m_pXSIVertexList;
	CSIBCArray<CSLXSIPolygonList *> m_XSIPolygonLists;
	CSIBCArray<CSLXSITriangleList *> m_XSITriangleLists;
	CSIBCArray<CSLXSITriangleStripList *> m_XSITriangleStripLists;

	void *m_pReserved;	// reserved for future extension
};

#endif
