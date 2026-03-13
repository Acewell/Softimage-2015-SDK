//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file DirectionalLight.h
	\brief Defines the CSLDirectionalLight class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _DIRECTIONALLIGHT_H
#define _DIRECTIONALLIGHT_H

#include "Light.h"

/*! \brief Describes a point light.
*/
class XSIEXPORT CSLDirectionalLight
    : public CSLLight
{
public:
	/*! Constructor
		\param[in] in_pScene scene to add this point light to
		\param[in] in_pModel model to add this light to
		\param[in] in_pTemplate IO layer template to connect to
		\return an instance of CSLPointLight
	*/
    CSLDirectionalLight(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

    /*! Destructor
	*/
	virtual ~CSLDirectionalLight();

	/*! Return the direction of the light.
		\return Light direction.
	*/
	CSIBCVector3D GetDirection();

	/*! Changes the direction of the light.
		\param[in]	in_rValue	New light direction.
	*/
	SI_Void SetDirection(CSIBCVector3D &in_rValue);

	/*! Synchronizes this directional light instance with its IO layer representation
		\retval SI_Error::SI_SUCCESS
	*/
    virtual SI_Error Synchronize();

	/*! Returns the template type of the directional light
		\return CSLTemplate::SI_DIRECTIONAL_LIGHT the template type
	*/
    virtual ETemplateType Type();

	/*! Returns a handle on one of this light's parameters by using its name
		\param[in] in_szName the name of the parameter to get the handle from
		\return the handle to the parameter
	*/
    virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);

	/*! Returns a handle on one of this light's parameters by using its name and type
		\param[in] in_Type the type of the parameter to get the handle from
		\param[in] in_szParameterName the name of the parameter to get the handle from
		\return the handle to the parameter
	*/
	virtual CSLAnimatableType* ParameterFromType(EFCurveType in_Type, SI_Char *in_szParameterName);

	CSLVector3DProxy* GetDirectionProxy() { return &m_Direction;};

protected:
	virtual SI_Bool ConstraintTypeIsValid(CSLConstraint::EConstraintType in_ConstraintType);

private:
    CSLVector3DProxy m_Direction;

	void *m_pReserved;	// reserved for future extension
};

#endif
