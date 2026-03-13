//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file Fog.h
	\brief Defines the CSLFog class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _FOG_H
#define _FOG_H

#include "Template.h"

/*! \brief This class represents an \xx ftk_SI_Fog SI_Fog \endxx template.

	Describes the fog (depth fading) in a scene (see the \xx ftk_SI_Fog SI_Fog \endxx
	template reference).
*/
class XSIEXPORT CSLFog
	: public CSLTemplate
{
public:
	/*! This enum list the possible type for the fog.
	*/
	enum EFogType
	{
		SI_VERTEX,	//!< per vertex fog
		SI_PIXEL,	//!< per pixel fog
	};

	/*! This enum list the possible interpolation type for the fog.
	*/
	enum EFogInterpolationType
	{
		SI_LINEAR,				//!< Fog linear interpolation
		SI_EXPONENTIAL,			//!< Fog Exponential interpolation
	};

	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Parent Template
		\return an instance of CSLFog
	*/
	CSLFog(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	/*! Destructor
	*/
	virtual ~CSLFog();

	/*! Returns the type of the fog.
		\return Type of fog.
	*/
	EFogType				GetFogType() { return m_Type; }

	/*! Changes the type of the fog.
		\param[in]	in_Type	New fog type.
	*/
	SI_Void 				SetFogType(EFogType in_Type) { m_Type = in_Type; }

	/*! Returns the type of interpolation of the fog.
		\return Type of fog interpolation.
	*/
	EFogInterpolationType	GetFogInterpolationType() { return m_InterpolationType; }

	/*! Changes the type of interpolation of the fog.
		\param[in]	in_Type	New fog interpolation type.
	*/
	SI_Void 				SetFogInterpolationType(EFogInterpolationType in_Type) { m_InterpolationType = in_Type; }

	/*!	Returns the color of the fog.
		\return Fog color.
	*/
	CSIBCColorf 			GetColor() { return m_Color; }

	/*!	Changes the color of the fog.
		\param[in]	in_rColor	New fog color.
	*/
	SI_Void 				SetColor(CSIBCColorf& in_rColor) { m_Color = in_rColor; }

	/*!	Returns the distance at which fog starts.
		\return Start distance.
	*/
	SI_Float				GetNear() { return m_Near; }

	/*!	Changes the distance at which fog starts.
		\param[in]	in_fValue	New start distance.
	*/
	SI_Void 				SetNear(SI_Float in_fValue) { m_Near = in_fValue; }

	/*!	Returns the distance at which fog stops.
		\return Stop distance.
	*/
	SI_Float				GetFar() { return m_Far; }

	/*!	Changes the distance at which fog stops.
		\param[in]	in_fValue	New stop distance.
	*/
	SI_Void 				SetFar(SI_Float in_fValue) { m_Far = in_fValue; }

	/*! Returns a handle on one of this fog's parameters by using its name
		\param[in] in_szName the name of the parameter to get the handle from
		\return the handle to the parameter
	*/
	virtual CSLAnimatableType*	ParameterFromName(SI_Char *in_szName);

	/*! Returns a handle on one of this fog's parameters by using its name and type
		\param[in] in_szParameterName the name of the parameter to get the handle from
		\param[in] in_Type the type of the parameter to get the handle from
		\return the handle to the parameter
	*/
	virtual CSLAnimatableType*	ParameterFromType(EFCurveType in_Type, SI_Char *in_szParameterName);

	/*! Returns the type of this template
		\retval CSLTemplate::SI_FOG The type of this template
	*/
	virtual ETemplateType		Type() { return SI_FOG; }

	CSLColorRGBProxy*	GetColorProxy(){ return &m_Color; };
	CSLFloatProxy*		GetNearProxy(){ return &m_Near; };
	CSLFloatProxy*		GetFarProxy(){ return &m_Far; };

private:
	CSLEnumProxy<EFogType, SI_FOG>						m_Type;
	CSLEnumProxy<EFogInterpolationType, SI_EXPONENTIAL> m_InterpolationType;

	CSLColorRGBProxy	m_Color;
	CSLFloatProxy		m_Near;
	CSLFloatProxy		m_Far;
};

#endif
