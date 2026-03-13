//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file COLLADAVertexList.h
	\brief Defines the CSLCOLLADAVertexList class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _COLLADAVERTEXLIST_H
#define _COLLADAVERTEXLIST_H

#include "XSIVertexList.h"


/*!	\brief Describes a list of vertices for dotXSI 5.0+.

The vertices in this list can have \c N number of attributes like position, etc.

To find out, you may use the parent class (CSLXSISubComponentList) functionality
to get the generic attributes index.
*/
class XSIEXPORT CSLCOLLADAVertexList
	: public CSLXSIVertexList
{
public:
	/*! Constructor
		\param[in] in_pScene			Parent scene
		\param[in] in_pModel			Parent model
		\param[in] in_pTemplate			dotXSI template
		\param[in] in_pVerticesTemplate	Referred template
		\return an instance of CSLXSIVertexList
	*/
	CSLCOLLADAVertexList(CSLScene *in_pScene, CSLModel *in_pModel, CdotXSITemplate *in_pTemplate, CdotXSITemplate *in_pVerticesTemplate);

	/*! Destructor
	*/
	virtual ~CSLCOLLADAVertexList();

	/*! Commit the current template information
		\return Whether or not the commit was successful
	*/
	virtual SI_Error Synchronize();

private:


};

#endif
