//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file LightInfo.h
	\brief Defines the CSLLightInfo class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _LIGHTINFO_H
#define _LIGHTINFO_H

#include "Template.h"

/*! \brief This class represents an \xx ftk_SI_LightInfo SI_LightInfo \endxx template.

Provides additional information regarding a CSLLight (see the \xx ftk_SI_LightInfo SI_LightInfo \endxx
template reference).
*/
class XSIEXPORT CSLLightInfo
    : public CSLTemplate
{
public:

	//! Defines the various fallof modes
	enum EFallofMode
	{
		SI_LINEAR,		/*!< Linear */
		SI_EXPONENT,	/*!< Use exponent type */
	};
	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Refered template
		\return an instance of CSLLightInfo
	*/
    CSLLightInfo(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	/*! Destructor
	*/
    virtual ~CSLLightInfo();

	/*! Returns the type of this template
		\retval CSLTemplate::SI_LIGHT_INFO The type of this template
	*/
	ETemplateType Type(){ return SI_LIGHT_INFO; }

	/*! Returns the parameter specified by name
		\param[in] in_szName Name of the parameter to retrieve
		\return Pointer to the parameter
	*/
    virtual CSLAnimatableType*		ParameterFromName(SI_Char *in_szName);

	/*! Returns the parameter specified by type
		\param[in] in_Type Type of the parameter to retrieve
		\param[in] in_szName Name of the parameter to retrieve (fallback in case we can't find it by type)
		\return Pointer to the parameter
	*/
    virtual CSLAnimatableType*		ParameterFromType(EFCurveType in_Type, SI_Char *in_szName);

	/*! Returns the fallof active state
		\return Whether or not fallof is active
	*/
	SI_Bool GetFallofActive();

	/*! Sets the fallof active state
		\param[in] in_bActive Whether or not fallof is active
	*/
	SI_Void SetFallofActive( SI_Bool in_bActive );

	/*! Returns the fallof mode
		\return The fallof mode
	*/
	EFallofMode GetFallofMode();

	/*! Sets the fallof mode
		\param[in] in_Mode The fallof mode
	*/
	SI_Void SetFallofMode( EFallofMode in_Mode );

	/*! Returns the start frame
		\return the start frame
	*/
	SI_Float GetStart();

	/*! Sets the start frame
		\param[in] in_fStart the start frame
	*/
	SI_Void SetStart( SI_Float in_fStart);

	/*! Returns the end frame
		\return the end frame
	*/
	SI_Float GetEnd();

	/*! Sets the end frame
		\param[in] in_fEnd the end frame
	*/
	SI_Void SetEnd( SI_Float in_fEnd);

	/*! Returns the shadow active state
		\return Whether or not shadow is active
	*/
	SI_Bool GetShadowActive();

	/*! Sets the shadow active state
		\param[in] in_bActive Whether or not shadow is active
	*/
	SI_Void SetShadowActive( SI_Bool in_bActive );

	/*! Returns the Umbra value
		\return The umbra value
	*/
	SI_Float GetUmbra();

	/*! Sets the Umbra value
		\param[in] in_fUmbra The umbra value
	*/
	SI_Void SetUmbra( SI_Float in_fUmbra = 0.75F);

	/*! Returns the light as energy active state
		\return Whether or not light as energy is active
		\note Only values beetween 0 and 1 are valid
	*/
	SI_Bool GetLightAsEnergy();

	/*! Sets the light as energy active state
		\param[in] in_bActive Whether or not light as energy is active
	*/
	SI_Void SetLightAsEnergy( SI_Bool in_bActive );

	/*! Returns the photon factor value
		\return The photon factor value
	*/
	SI_Float GetPhotonFactor();

	/*! Sets the photon factor value
		\note Only values beetween 0 and 100000 are valid
		\param[in] in_fPhotonFactor The photon factor value
	*/
	SI_Void SetPhotonFactor( SI_Float in_fPhotonFactor = 0.75F);

	/*! Returns the Intensity
		\return The Intensity
	*/
	SI_Float GetIntensity();
	/*! Sets the Intensity
		\note Only values beetween 0 and 1.00000 are valid
		\param[in] in_fIntensity The intensity factor
	*/
	SI_Void SetIntensity( SI_Float in_fIntensity );

	CSLBoolProxy*							GetFallofActiveProxy() {return &m_FallofActive; };
    CSLEnumProxy<EFallofMode, SI_EXPONENT>* GetFallofModeProxy() {return &m_FallofMode; };
    CSLFloatProxy*							GetStartProxy() {return &m_Start; };
    CSLFloatProxy*							GetEndProxy() {return &m_End; };
    CSLBoolProxy*							GetShadowsActiveProxy() {return &m_ShadowsActive; };
    CSLFloatProxy*							GetUmbraProxy() {return &m_Umbra; };
    CSLBoolProxy*							GetLightAsEnergyProxy() {return &m_LightAsEnergy; };
    CSLFloatProxy*							GetPhotonFactorProxy() {return &m_PhotonFactor; };
	CSLFloatProxy*							GetIntensityProxy() {return &m_Intensity; };

private:
    CSLBoolProxy m_FallofActive;
    CSLEnumProxy<EFallofMode, SI_EXPONENT> m_FallofMode;
    CSLFloatProxy m_Start;
    CSLFloatProxy m_End;
    CSLBoolProxy m_ShadowsActive;
    CSLFloatProxy m_Umbra;
    CSLBoolProxy m_LightAsEnergy;
    CSLFloatProxy m_PhotonFactor;
	CSLFloatProxy m_Intensity;

	SI_Void* m_pReserved;
};

#endif
