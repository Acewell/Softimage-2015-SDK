//***************************************************************************************
//
// File supervisor: Crosswalk team
//
// Copyright 2008 Autodesk, Inc.  All rights reserved.  
// Use of this software is subject to the terms of the Autodesk license agreement 
// provided at the time of installation or download, or which otherwise accompanies 
// this software in either electronic or hard copy form.
//
//***************************************************************************************

/*! \file COLLADAEffect.h
/*!
	COLLADA Effect class definition
*/

#ifndef COLLADAEFFECT_H
#define COLLADAEFFECT_H
#include "Template.h"
#include "COLLADATemplate.h"

/**************************************************************************************
Complex types classes
****************************************************************************************/
/**************************************************************************************
COMMON Profile classes
****************************************************************************************/

class XSIEXPORT CSLCOLLADAFXCommonFloat : public CSLTemplate
{
public:
	CSLCOLLADAFXCommonFloat(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
	virtual ~CSLCOLLADAFXCommonFloat();

	float			GetValue();
	void			SetValue(float in_fValue);
	CSLFloatProxy*	GetValueProxy() { return &m_FloatValue;};
	virtual CSLTemplate::ETemplateType	Type();
	virtual SI_Error Fix();

private: 
	CSLFloatProxy	m_FloatValue;
};

class XSIEXPORT CSLCOLLADAFXCommonParam : public CSLTemplate
{
public:
	CSLCOLLADAFXCommonParam(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
	virtual ~CSLCOLLADAFXCommonParam();

	CSLTemplate*	GetReference();
	void			SetReference(CSLTemplate *in_pRefTemplate);

	virtual CSLTemplate::ETemplateType	Type();
	virtual SI_Error Synchronize();
	virtual SI_Error Fix();
private:
	
	CSLTemplate*	m_pReference;
};

class XSIEXPORT CSLCOLLADAFXCommonColor : public CSLTemplate
{
public:
	CSLCOLLADAFXCommonColor(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
	virtual ~CSLCOLLADAFXCommonColor();

	CSIBCColorf			GetColor();
	void				SetColor(CSIBCColorf in_Value);
	CSLColorRGBAProxy*	GetColorProxy() { return &m_Color; };

	virtual CSLTemplate::ETemplateType	Type();
	virtual SI_Error Fix();

private: 
	CSLColorRGBAProxy	m_Color;
};

class XSIEXPORT CSLCOLLADAFXCommonTexture : public CSLTemplate
{
public:
	CSLCOLLADAFXCommonTexture(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
	virtual ~CSLCOLLADAFXCommonTexture();

	CSLTemplate*	GetTexture();
	void			SetTexture(CSLTemplate* in_pTexture);

	unsigned char*	GetTexCoord();
	void			SetTexCoord(unsigned char *in_pTexCoord);

	char*			GetSurfaceInit();
	char*			GetSamplerSource();

	virtual CSLTemplate::ETemplateType	Type();
	virtual SI_Error Fix();

private: 
	SI_Error		ResolveTextureImage();
	CSLTemplate*	m_pTexture;

	CCOLLADATemplate *m_pSurfaceNewParam;
	CCOLLADATemplate *m_pSamplerNewParam;
};


class XSIEXPORT CSLCOLLADAFXCommonFloatParam : public CSLTemplate
{
public:
	CSLCOLLADAFXCommonFloatParam(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
	virtual ~CSLCOLLADAFXCommonFloatParam();

	CSLCOLLADAFXCommonParam*	GetParam();
	CSLCOLLADAFXCommonParam*	CreateParam();
	bool						IsParam();

	CSLCOLLADAFXCommonFloat*	GetFloat();
	CSLCOLLADAFXCommonFloat*	CreateFloat();
	bool						IsFloat();

	virtual CSLTemplate::ETemplateType	Type();
	virtual	SI_Error Synchronize();

private:
	CSLCOLLADAFXCommonFloat*	m_pFloat;
	CSLCOLLADAFXCommonParam*	m_pParam;
};


class XSIEXPORT CSLCOLLADAFXCommonColorTexture : public CSLTemplate
{
public:
	CSLCOLLADAFXCommonColorTexture(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
	virtual ~CSLCOLLADAFXCommonColorTexture();

	CSLCOLLADAFXCommonParam*	GetParam();
	CSLCOLLADAFXCommonParam*	CreateParam();
	bool						IsParam();

	CSLCOLLADAFXCommonColor*	GetColor();
	CSLCOLLADAFXCommonColor*	CreateColor();
	bool						IsColor();

	CSLCOLLADAFXCommonTexture*	GetTexture();
	CSLCOLLADAFXCommonTexture*	CreateTexture();
	bool						IsTexture();

	void						SetOpaque(CSIBCString in_value);

	virtual CSLTemplate::ETemplateType	Type();
	virtual	SI_Error Synchronize();

private:
	CSLCOLLADAFXCommonColor*	m_pColor;
	CSLCOLLADAFXCommonParam*	m_pParam;
	CSLCOLLADAFXCommonTexture*	m_pTexture;
	bool						m_OpaqueInitialized;
	CSIBCString					m_Opaque;
};

class XSIEXPORT CSLCOLLADAFXCommonShader : public CSLTemplate
{
public:
	enum eCOLLADAFXCommonProfileShading
	{
		CFXCP_CONSTANT,
		CFXCP_LAMBERT,
		CFXCP_PHONG,
		CFXCP_BLINN
	};

	CSLCOLLADAFXCommonShader(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate, eCOLLADAFXCommonProfileShading in_ShadingType);
	virtual ~CSLCOLLADAFXCommonShader();

	CSLCOLLADAFXCommonColorTexture*		GetEmission();
	CSLCOLLADAFXCommonColorTexture*		GetAmbient();
	CSLCOLLADAFXCommonColorTexture*		GetDiffuse();
	CSLCOLLADAFXCommonColorTexture*		GetSpecular();
	CSLCOLLADAFXCommonColorTexture*		GetReflective();
	CSLCOLLADAFXCommonColorTexture*		GetTransparent();
	CSLCOLLADAFXCommonFloatParam*		GetShininess();
	CSLCOLLADAFXCommonFloatParam*		GetReflectivity();
	CSLCOLLADAFXCommonFloatParam*		GetTransparency();
	CSLCOLLADAFXCommonFloatParam*		GetIndexOfRefraction();	

	void	ConnectEmission(CCOLLADATemplate* in_pParam);
	void	ConnectAmbient(CCOLLADATemplate* in_pParam);
	void	ConnectDiffuse(CCOLLADATemplate* in_pParam);
	void	ConnectSpecular(CCOLLADATemplate* in_pParam);
	void	ConnectReflective(CCOLLADATemplate* in_pParam);
	void	ConnectTransparent(CCOLLADATemplate* in_pParam);
	void	ConnectShininess(CCOLLADATemplate* in_pParam);
	void	ConnectReflectivity(CCOLLADATemplate* in_pParam);
	void	ConnectTransparency(CCOLLADATemplate* in_pParam);
	void	ConnectIndexOfRefraction(CCOLLADATemplate* in_pParam);

	virtual SI_Error Fix();
	virtual CSLTemplate::ETemplateType	Type();
	virtual	SI_Error Synchronize();

	CSLCOLLADAFXCommonShader::eCOLLADAFXCommonProfileShading		GetShadingType();

private:
	CSLCOLLADAFXCommonColorTexture*		m_pEmission;
	CSLCOLLADAFXCommonColorTexture*		m_pAmbient;
	CSLCOLLADAFXCommonColorTexture*		m_pDiffuse;
	CSLCOLLADAFXCommonColorTexture*		m_pSpecular;
	CSLCOLLADAFXCommonColorTexture*		m_pReflective;
	CSLCOLLADAFXCommonColorTexture*		m_pTransparent;
	CSLCOLLADAFXCommonFloatParam*		m_pReflectivity;
	CSLCOLLADAFXCommonFloatParam*		m_pShininess;
	CSLCOLLADAFXCommonFloatParam*		m_pTransparency;
	CSLCOLLADAFXCommonFloatParam*		m_pIndexOfReflection;
	eCOLLADAFXCommonProfileShading		m_ShadingType;
};

class XSIEXPORT CSLCOLLADAFXCommonProfile : public CSLTemplate
{
public:

	CSLCOLLADAFXCommonProfile(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
	virtual ~CSLCOLLADAFXCommonProfile();
	
	CSLCOLLADAFXCommonShader*			GetShader();
	CSLCOLLADAFXCommonShader*			CreateShader(CSLCOLLADAFXCommonShader::eCOLLADAFXCommonProfileShading in_pShadingType);
	CSLCOLLADAFXCommonShader*			ConnectShader(CCOLLADATemplate *in_pTemplate);


	virtual CSLTemplate::ETemplateType	Type();
	virtual SI_Error Fix();



private:
	CCOLLADATemplate*					m_pDefaultTechnique;
	CSLCOLLADAFXCommonShader*			m_pShader;
};

/**************************************************************************************
CG Profile classes
****************************************************************************************/



/**************************************************************************************
Generic effect class
****************************************************************************************/
class XSIEXPORT CSLCOLLADAFX : public CSLTemplate
{
public:
	CSLCOLLADAFX(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
	virtual ~CSLCOLLADAFX();

	CSLCOLLADAFXCommonProfile*	GetCommonProfile();
	CSLCOLLADAFXCommonProfile*	CreateCommonProfile();
	void						ConnectCommonProfile(CSLCOLLADAFXCommonProfile* in_pProfile);

	virtual CSLTemplate::ETemplateType	Type();

private:

	CSLCOLLADAFXCommonProfile*	m_pCommonProfile;
	

};

#endif // COLLADAEFFECT_H
