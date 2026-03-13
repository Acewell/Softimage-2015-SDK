//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file InfiniteLight.h
	\brief Defines the CSLInfiniteLight class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _INFINITELIGHT_H
#define _INFINITELIGHT_H

#include "Light.h"



/*! \brief Describes an infinite light.
*/
class XSIEXPORT CSLInfiniteLight
    : public CSLLight
{
public:
	/*! Constructor
		\param[in] in_pScene scene to add this infinite light to
		\param[in] in_pModel model to add this light to
		\param[in] in_pTemplate IO layer template to connect to
		\return an instance of CSLInfiniteLight
	*/
    CSLInfiniteLight(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	/*! Destructor
	*/
    virtual ~CSLInfiniteLight();

	/*! Synchronizes this light instance with its IO layer representation
		\retval SI_Error::SI_SUCCESS this function always returns SI_SUCCESS
	*/
    virtual SI_Error Synchronize();

	/*! Returns the template type of the light
		\retval CSLTemplate::SI_INFINITE_LIGHT the template type
	*/
    virtual ETemplateType Type();


protected:
	virtual SI_Bool ConstraintTypeIsValid(CSLConstraint::EConstraintType in_ConstraintType);

private:
	void *m_pReserved;	// reserved for future extension
};

#endif
