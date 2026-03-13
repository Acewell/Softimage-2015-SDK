//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file PatchSurface.h
	\brief Defines the CSLPatchSurface class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _PATCHSURFACE_H
#define _PATCHSURFACE_H

#include "Geometry.h"

/*! \brief This class represents an \xx ftk_SI_PatchSurface SI_PatchSurface \endxx template.

Implements a patch surface (see the \xx ftk_SI_PatchSurface SI_PatchSurface \endxx
template reference).
*/
class XSIEXPORT CSLPatchSurface
    : public CSLGeometry
{

//@START_USER2
//@END_USER2

// Members
private:

protected:

public:

// Methods
private:

protected:

public:

	/*! Constructor
	* \param in_pScene	Pointer to the scene containing the Geometry
	* \param in_pModel	Pointer to the model containing the Geometry
	* \param in_pTemplate	Pointer to the CdotXSITemplate containing the Geometry
	* \return an instance of CSLPatchSurface
	*/
	CSLPatchSurface(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate) :
	  CSLGeometry(in_pScene, in_pModel, in_pTemplate) {};

	/*! Destructor
	*/
    virtual ~CSLPatchSurface();
};

#endif


#ifdef CB_INLINES
#ifndef _PATCHSURFACE_H_INLINES
#define _PATCHSURFACE_H_INLINES

//@START_USER3
//@END_USER3

#endif
#endif
