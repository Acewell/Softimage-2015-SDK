//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file COLLADAIndexList.h
	\brief Defines the CSLCOLLADAIndexList class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _COLLADAINDEXLIST_H
#define _COLLADAINDEXLIST_H

#include "COLLADATemplate.h"
#include "XSIIndexList.h"


/*! \brief Describes an index list

The CSLXSIIndexList holds a list of polygon indices values.
This class allows an attribute (position, normal, color, texcoord, etc.) to be associated with vertices or polynodes.
*/
class XSIEXPORT CSLCOLLADAIndexList
	: public CSLXSIIndexList
{
public:

	CSLCOLLADAIndexList(CSLScene *in_pScene, CSLModel *in_pModel, CdotXSITemplate *in_pTemplate);

	/*! Destructor
	*/
	virtual ~CSLCOLLADAIndexList();

	virtual SI_Error	Synchronize();

private:

};

#endif
