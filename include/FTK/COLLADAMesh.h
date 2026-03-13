//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file COLLADAMesh.h
	\brief Defines the CSLCOLLADAMesh class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _COLLADAMESH_H
#define _COLLADAMESH_H

#include "Template.h"
#include "Logger.h"
#include "Scene.h"
#include "COLLADATemplate.h"
#include "Model.h"
#include "XSIMesh.h"
#include "COLLADAShape.h"
#include "COLLADAScene.h"
#include "COLLADAVertexList.h"

/*!	\brief This class represents a mesh for COLLADA.
*/
class XSIEXPORT CSLCOLLADAMesh : public CSLXSIMesh
{
public:
	///////////////////////////////////////////////////////////////////////////
	// Construction/destruction
	///////////////////////////////////////////////////////////////////////////
	CSLCOLLADAMesh(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
	virtual ~CSLCOLLADAMesh();

	virtual CSLXSITriangleList*				AddXSITriangleList();
	virtual CSLXSIPolygonList* 				AddXSIPolygonList();

	SI_Error	CreateXSITriangleList(CCOLLADATemplate* in_pContainer);
	SI_Error	CreateXSIPolygonList(CCOLLADATemplate* in_pContainer);

	/*! Creates a new shape animation for the geometry.
	\param[in]	in_Type	Type of interpolation for the new shape animation.
	\return Pointer to the newly created shape animation.
	*/
	virtual CSLXSIShapeAnimation*	CreateXSIShapeAnimation(EFCurveInterpolationType in_Type);

	virtual SI_Error				Fix();
	virtual SI_Error				Synchronize();

protected:

	CCOLLADATemplate*	m_pMeshContainerTemplate;
	CCOLLADATemplate*	m_pVerticesTemplate;
	CdotXSIParam*		m_pVertexIDParam;
	CdotXSIParam*		m_pSourceParam;
public:

};

#endif
