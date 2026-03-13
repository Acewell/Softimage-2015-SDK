//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file COLLADAPolygonList.h
	\brief Defines the CSLCOLLADAPolygonList class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _COLLADAPOLYGONLIST_H
#define _COLLADAPOLYGONLIST_H

#include "XSIPolygonList.h"
#include "XSISubComponentList.h"
#include "COLLADATemplate.h"
#include "Material.h"


/*! \brief This class represents a polygon list for COLLADA.
*/
class XSIEXPORT CSLCOLLADAPolygonList
	: public CSLXSIPolygonList
{
public:
	/*! Constructor
		\param[in] in_pScene			Parent scene
		\param[in] in_pModel			Parent model
		\param[in] in_pTemplate			dotXSI template
		\param[in] in_pCOLLADATemplate	Referred template
		\param[in] in_pVertexDef		Vertex definition template
		\return an instance of CSLXSITriangleList
	*/
	CSLCOLLADAPolygonList(CSLScene *in_pScene,
							CSLModel *in_pModel,
							CdotXSITemplate *in_pTemplate,
							CCOLLADATemplate *in_pCOLLADATemplate,
							CCOLLADATemplate *in_pVertexDef);

	/*! Destructor
	*/
	virtual ~CSLCOLLADAPolygonList();

	/*!	Adds a new index list. If one already exists, it is deleted and replaced.
	* \return Pointer to the newly created index list.
	*/
	virtual CSLXSIIndexList*	AddIndexList();

	virtual SI_Error Synchronize();

	/*! Returns all input semantics used by this polylist
	* \return Input semantics
	*/
	virtual CdotXSITemplates* GetInputSemantics();

protected:

	CCOLLADATemplate	*m_szTemplate;
	CCOLLADATemplate	*m_szSemantic;
	CdotXSIParam*		m_pSource;
	CdotXSIParam*		m_pCount;
	CdotXSIParam*		m_pAttribMaterial;
};

#endif
