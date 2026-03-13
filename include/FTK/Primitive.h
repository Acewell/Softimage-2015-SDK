//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file Primitive.h
	\brief Defines the CSLPrimitive class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _PRIMITIVE_H
#define _PRIMITIVE_H

#include "Template.h"

/*! \brief Base class for primitive objects
*/
class XSIEXPORT CSLPrimitive
    : public CSLTemplate
{
public:

	/*! Destructor
	*/
    virtual ~CSLPrimitive();

	/*! Validate a parent for this primitive
	* \param in_pNewParent the parent to validate
	* \return SI_Bool whether the parent is valid or not
	*/
	virtual SI_Bool ValidateParent(CSLModel *in_pNewParent);

protected:

	/*! Constructor
	* \param in_pScene	Pointer to the scene containing the Primitive
	* \param in_pModel	Pointer to the model containing the Primitive
	* \param in_pTemplate	Pointer to the CdotXSITemplate containing the Primitive
	* \return an instance of CSLPrimitive
	*/
    CSLPrimitive(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
};

#endif
