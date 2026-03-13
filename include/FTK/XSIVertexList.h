//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSIVertexList.h
	\brief Defines the CSLXSIVertexList class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _XSIVERTEXLIST_H
#define _XSIVERTEXLIST_H

#include "XSISubComponentList.h"


/*! \brief This class represents an \xx ftk_XSI_VertexList XSI_VertexList \endxx template.

	Describes a list of vertices for dotXSI 5.0+ (see the \xx ftk_XSI_VertexList XSI_VertexList \endxx
	template reference). The vertices in this list can have N number of attibutes like postion, etc.

	\tip You can use the parent class (CSLXSISubComponentList) functionality to get the generic attributes index.
*/
class XSIEXPORT CSLXSIVertexList
	: public CSLXSISubComponentList
{
public:
	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Refered template
		\return an instance of CSLXSIVertexList
	*/
	CSLXSIVertexList(CSLScene *in_pScene, CSLModel *in_pModel, CdotXSITemplate *in_pTemplate);

	/*! Destructor
	*/
	virtual ~CSLXSIVertexList();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_VERTEX_LIST The type of this template
	*/
	virtual ETemplateType			Type() { return XSI_VERTEX_LIST; }

	/*! Commits the current template information
		\return Whether or not the commit was successful
	*/
	virtual SI_Error Synchronize();

private:

	void *m_pReserved;	// reserved for future extension
};

#endif
