//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file Null.h
	\brief Defines the CSLNull class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _NULL_H
#define _NULL_H

#include "Template.h"
#include "Primitive.h"

/*! \brief This class represents an \xx ftk_SI_Null SI_Null \endxx template.

	Describes a null object (see the \xx ftk_SI_Null SI_Null \endxx
	template reference).
*/
class XSIEXPORT CSLNull
    : public CSLPrimitive
{
public:
	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Template containing the null
		\return an instance of CSLNull
	*/
    CSLNull(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	//! Destructor
    virtual ~CSLNull();


	/*! Synchronizes this null instance with its IO layer representation
		\retval SI_Error::SI_SUCCESS this function always returns SI_SUCCESS
	*/
    virtual SI_Error Synchronize();

	/*! Returns the template type of the null
		\retval CSLTemplate::SI_NULL_OBJECT the template type
	*/
	CSLTemplate::ETemplateType Type();

};

#endif
