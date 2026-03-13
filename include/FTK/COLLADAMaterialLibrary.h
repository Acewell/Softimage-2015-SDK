//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file COLLADAMaterialLibrary.h
	\brief Defines the CSLCOLLADAMaterialLibrary class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef COLLADAMATERIALLIBRARY_H
#define COLLADAMATERIALLIBRARY_H

#include "MaterialLibrary.h"


class CSLCOLLADAMaterial;
class CSLCOLLADAFX;

/*! \brief Handles the material library.

	From this class you can add or remove materials that can be used in the scene.
*/

class XSIEXPORT CSLCOLLADAMaterialLibrary : public CSLMaterialLibrary
{
public:
	///////////////////////////////////////////////////////////////////////////
	// Construction/destruction
	///////////////////////////////////////////////////////////////////////////
	CSLCOLLADAMaterialLibrary(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
	virtual ~CSLCOLLADAMaterialLibrary();

	/*!	Adds a new material object to the material library.
	\return	Pointer to the newly created material object.
	*/
	virtual CSLXSIMaterial* AddXSIMaterial();

};


#endif // COLLADAMATERIALLIBRARY_H
