//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file COLLADATriangleList.h
	\brief Defines the CSLCOLLADATriangleList class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _COLLADATRIANGLELIST_H
#define _COLLADATRIANGLELIST_H

#include "XSITriangleList.h"
#include "XSISubComponentList.h"
#include "COLLADATemplate.h"
#include "Material.h"


/*! \brief Describes a list of triangles for dotXSI 5.0+

The polynodes in this list can have N number of attibutes like vertex, normals, UV and color information.

To find out, you may use GetVertexIndices() to get the mendatory vertex index attributes and
the parent class (CSLXSISubComponentList) functionality to get the other generic attributes index.

To get the number of triangles in the list, use GetTriangleCount().

*/
class XSIEXPORT CSLCOLLADATriangleList
	: public CSLXSITriangleList
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
	CSLCOLLADATriangleList(CSLScene *in_pScene,
							CSLModel *in_pModel,
							CdotXSITemplate *in_pTemplate,
							CCOLLADATemplate *in_pCOLLADATemplate,
							CCOLLADATemplate *in_pVertexDef);

	/*! Destructor
	*/
	virtual ~CSLCOLLADATriangleList();

	virtual SI_Error Synchronize();

	/*! Returns all input semantics used by this triangle list
		\return Input semantics
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
