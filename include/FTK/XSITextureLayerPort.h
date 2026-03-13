//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSITextureLayerPort.h
	\brief Defines the CSLXSITextureLayerPort class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************
#ifndef _XSITEXTURELAYERPORT_H
#define _XSITEXTURELAYERPORT_H

#include "Template.h"

/*! \brief This class represents an \xx ftk_XSI_TextureLayerPort XSI_TextureLayerPort \endxx template.

	Defines texture layer port (see the \xx ftk_XSI_TextureLayerPort XSI_TextureLayerPort \endxx template reference).
	\since dotXSI 6.0
*/
class XSIEXPORT CSLXSITextureLayerPort
    : public CSLTemplate
{
public:
	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Refered template
	*/
	CSLXSITextureLayerPort(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	//! Destructor
	virtual ~CSLXSITextureLayerPort();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_TEXTURE_LAYER_PORT The type of this template
	*/
	ETemplateType Type(){ return XSI_TEXTURE_LAYER_PORT; }

    virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);

	virtual CSLAnimatableType* ParameterFromType(EFCurveType in_Type, SI_Char *in_szParameterName);


	/*! Returns the Target value
		\return Target
	*/
	SI_Char* GetTarget();

	/*! Sets the Target value
		\param[in]	in_pValue	new Target value
	*/
	SI_Void SetTarget( SI_Char* in_pValue );

	/*! Returns the Mute value
		\return Exposure
	*/
	SI_Bool GetMute();

	/*! Sets the Mute value
		\param[in]	in_bValue	new Mute value
	*/
	SI_Void SetMute( SI_Bool in_bValue );

	/*! Returns the Scale value
		\return Scale
	*/
	SI_Float GetScale();

	/*! Sets the Scale value
		\param[in]	in_fValue	new Scale value
	*/
	SI_Void SetScale( SI_Float in_fValue );

	/*! Returns the ColorSource value
		\return ColorSource
	*/
	SI_Int GetColorSource();

	/*! Sets the ColorSource value
		\param[in]	in_nValue	new ColorSource value
	*/
	SI_Void SetColorSource( SI_Int in_nValue );

	/*! Returns the Invert value
		\return Invert
	*/
    SI_Bool GetInvert();

	/*! Sets the Invert value
		\param[in]	in_bValue	new RenderColorProfile value
	*/
	SI_Void SetInvert( SI_Bool in_bValue);


	CSLStringProxy* 									GetTargetProxy()		{ return &m_Target; };
	CSLBoolProxy* 										GetMuteProxy()			{ return &m_Mute; };
    CSLFloatProxy* 										GetScaleProxy()			{ return &m_Scale; };
	CSLIntProxy*										GetColorSourceProxy()	{ return &m_ColorSource; };
    CSLBoolProxy*										GetInvertProxy()		{ return &m_Invert; };

private:
    CSLStringProxy	m_Target;
    CSLBoolProxy	m_Mute;
    CSLFloatProxy	m_Scale;
	CSLIntProxy		m_ColorSource;
    CSLBoolProxy	m_Invert;

	SI_Void *m_pReserved;
};

#endif
