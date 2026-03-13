//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file PointLight.h
	\brief Defines the CSLPointLight class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _POINTLIGHT_H
#define _POINTLIGHT_H

#include "Light.h"



/*! \brief Describes a point light.
*/
class XSIEXPORT CSLPointLight
    : public CSLLight
{
public:

	/*! Constructor
		\param[in] in_pScene scene to add this point light to
		\param[in] in_pModel model to add this light to
		\param[in] in_pTemplate IO layer template to connect to
		\return an instance of CSLPointLight
	*/
    CSLPointLight(CSLScene *in_pScene, CSLModel *in_pModel, CdotXSITemplate *in_pTemplate);

	/*! Destructor
	*/
    virtual ~CSLPointLight();

	/*! Synchronizes this light instance with its IO layer representation
		\retval SI_Error::SI_SUCCESS this function always returns SI_SUCCESS
	*/
    virtual SI_Error Synchronize();

	/*! Returns the template type of the light
		\retval CSLTemplate::SI_POINT_LIGHT the template type
	*/
    virtual ETemplateType Type();

protected:
	virtual SI_Bool ConstraintTypeIsValid(CSLConstraint::EConstraintType in_ConstraintType);

private:
	void *m_pReserved;	// reserved for future extension
};

#endif

