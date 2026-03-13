//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file SurfaceMesh.h
	\brief Defines the CSLSurfaceMesh class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _SURFACEMESH_H
#define _SURFACEMESH_H

#include "Primitive.h"


class CSLNurbsSurface;

/*! \brief Describes a list of NURBS surfaces.
	\sa CSLPrimitive
*/
class XSIEXPORT CSLSurfaceMesh
	: public CSLPrimitive
{
public:
	CSLSurfaceMesh(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
	virtual ~CSLSurfaceMesh();

	/*!	Adds a new surface to the list.
		\return Pointer to the newly created surface.
	*/
	CSLNurbsSurface* AddSurface();

	/*!	Returns the number of surfaces in the list.
		\return Number of surfaces.
	*/
	SI_Int GetSurfaceCount();

	/*!	Returns an array of all surfaces in the list.
		\return Array of pointers to surface objects.
	*/
	CSLNurbsSurface **Surfaces();

	/*!	Removes a single surface from the list.
		\param[in]	in_nIndex	Index of the surface to remove.
		\return Error code.
	*/
	SI_Error RemoveSurface(SI_Int in_nIndex);

	/*!	Removes a single surface from the list.
		\param[in]	in_pSurface	Pointer to the surface to remove.
		\return Error code.
	*/
	SI_Error RemoveSurface(CSLNurbsSurface* in_pSurface);

	/*!	Removes all surfaces from the list.
		\return Error code.
	*/
	SI_Error ClearSurfaces();

	// Connection functions.
	CSLNurbsSurface* ConnectSurface(CSLNurbsSurface* in_pNewSurface);

    virtual SI_Error Synchronize();

    /*! Returns the template type
    	\retval CSLTemplate::SI_SURFACE_MESH Type of this template
    */
    virtual ETemplateType Type();

private:
	CSIBCArray<CSLNurbsSurface *> m_Surfaces;

	void *m_pReserved;	// reserved for future extension
};

#endif
