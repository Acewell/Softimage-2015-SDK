//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file SpotLight.h
	\brief Defines the CSLSpotLight class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _SPOTLIGHT_H
#define _SPOTLIGHT_H

#include "Light.h"

/*! \brief Describes a spot light and its interest.
*/
class XSIEXPORT CSLSpotLight
    : public CSLLight
{
public:

	/*! Constructor
		\param[in] in_pScene scene to add this spotlight to
		\param[in] in_pModel model to add this light to
		\param[in] in_pTemplate IO layer template to connect to
		\return an instance of CSLSpotLight
	*/
	CSLSpotLight(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	/*! Destructor
	*/
    virtual ~CSLSpotLight();

	/*! Returns the position of the spotlight interest.
		\return Interest position.
	*/
	CSIBCVector3D GetInterestPosition();

	/*! Changes the position of the spotlight interest.
		\param[in] in_rValue New interest position.
	*/
	SI_Void SetInterestPosition(CSIBCVector3D &in_rValue);

	/*! Returns the cone angle of the spotlight.
		\return Cone angle.
	*/
	SI_Float GetConeAngle();

	/*! Changes the cone angle of the spotlight.
		\param[in] in_fValue New cone angle.
	*/
	SI_Void SetConeAngle(SI_Float in_fValue);

	/*! Returns the spread angle of the spotlight.
		\return Spread angle.
	*/
	SI_Float GetSpreadAngle();

	/*! Changes the spread angle of the spotlight.
		\param[in] in_fValue New spread angle.
	*/
	SI_Void SetSpreadAngle(SI_Float in_fValue);

	/*! Synchronizes this light instance with its IO layer representation
		\retval SI_Error::SI_SUCCESS this function always returns SI_SUCCESS
	*/
    virtual SI_Error Synchronize();

	/*! Returns the template type of the spotlight
		\retval CSLTemplate::SI_SPOT_LIGHT the template type
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

	CSLVector3DProxy* GetInterestPositionProxy() { return &m_InterestPosition;};

protected:
	virtual SI_Bool ConstraintTypeIsValid(CSLConstraint::EConstraintType in_ConstraintType);

private:
    CSLVector3DProxy m_InterestPosition;
    CSLFloatProxy m_ConeAngle;
    CSLFloatProxy m_SpreadAngle;

	void *m_pReserved;	// reserved for future extension
};

#endif
