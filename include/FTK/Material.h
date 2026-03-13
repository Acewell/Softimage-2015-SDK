//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file Material.h
	\brief Defines the CSLBaseMaterial and CSLMaterial classes

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "Template.h"

// Forward declaration
class CSLTexture2D;


/*! \brief The CSLBaseMaterial defines a base material.

From this base material, cast it in the
overridden class either CSLMaterial or CSLXSIMaterial using GetType().
*/
class XSIEXPORT CSLBaseMaterial
	: public CSLTemplate
{
public:
    virtual SI_Error Synchronize();

	virtual SI_Error GetCapabilities ( SI_Int in_iFeature, SI_Void* out_pValue );

protected:

	/*! Constructor
		\param[in] in_pScene	Pointer to the scene containing the BaseMaterial
		\param[in] in_pModel	Pointer to the model containing the BaseMaterial
		\param[in] in_pTemplate	Pointer to the CdotXSITemplate containing the BaseMaterial
	*/
    CSLBaseMaterial(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

private:
	void *m_pReserved;	// reserved for future extension
};

/*! \brief This class represents an \xx ftk_SI_Material SI_Material \endxx template.

	Defines a legacy SI_Material (see the \xx ftk_SI_Material SI_Material \endxx
	template reference).
*/
class XSIEXPORT CSLMaterial
    : public CSLBaseMaterial
{
public:
	/*! This enum lists possible shading models for a material.
	*/
	enum EShadingModel
	{
		CONSTANT,		/*!< Constant shading*/
		LAMBERT,		/*!< Lambert shading*/
		PHONG,			/*!< Phong shading*/
		BLINN,			/*!< Blinn shading*/
		SHADOW_OBJECT,	/*!< Shawdow object*/
		VERTEX_COLOR,	/*!< Vertex color lighting*/
	};

	/*! Constructor
		\param[in] in_pScene	Pointer to the scene containing the Material
		\param[in] in_pModel	Pointer to the model containing the Material
		\param[in] in_pTemplate	Pointer to the CdotXSITemplate containing the Material
	*/
    CSLMaterial(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

    /*! Destructor
	*/
	virtual ~CSLMaterial();

	/*!	Returns the ambient color of the material.
		\return Ambient color.
	*/
	CSIBCColorf GetAmbientColor();

	/*!	Changes the ambient color of the material.
		\param[in]	in_rColor	New ambient color.
	*/
	SI_Void SetAmbientColor(CSIBCColorf &in_rColor);

	/*!	Returns the diffuse color of the material.
		\return Diffuse color.
	*/
	CSIBCColorf GetDiffuseColor();

	/*!	Changes the diffuset color of the material.
		\param[in]	in_rColor	New diffuse color.
	*/
	SI_Void SetDiffuseColor(CSIBCColorf &in_rColor);

	/*!	Returns the emissive color of the material.
		\return emissive color.
	*/
	CSIBCColorf GetEmissiveColor();

	/*!	Changes the emissive color of the material.
		\param[in]	in_rColor	New emissive color.
	*/
	SI_Void SetEmissiveColor(CSIBCColorf &in_rColor);

	/*!	Returns the shading model of the material.
		\return Shading model.
	*/
	EShadingModel GetShadingModel();

	/*!	Changes the shading model of the material.
		\param[in]	in_Value	New shading model.
	*/
	SI_Void SetShadingModel(EShadingModel in_Value);

	/*!	Returns the specular color of the material.
		\return Specular color.
	*/
	CSIBCColorf GetSpecularColor();

	/*!	Changes the specular color of the material.
		\param[in]	in_rColor	New specular color
	*/
	SI_Void SetSpecularColor(CSIBCColorf &in_rColor);

	/*!	Returns the specular decay of the material.
		\return Specular decay.
	*/
	SI_Float GetSpecularDecay();

	/*!	Changes the specular decay of the material.
		\param[in]	in_fValue	New Specular decay.
	*/
	SI_Void SetSpecularDecay(SI_Float in_fValue);

	/*!	Returns the 2D texture of the material.
		\return Pointer to a texture 2D object.
	*/
    CSLTexture2D* Texture2D();

	/*!	Create a new texture 2D for the material.
		\return Newly creates texture 2D object.
	*/
    CSLTexture2D* CreateTexture2D();

	/*!	Destroys the texture 2D of the material.
		\return Error code.
	*/
	SI_Error DestroyTexture2D();

    CSLTexture2D* ConnectTexture2D(CSLTexture2D* in_pNewTexture2D);

    virtual SI_Error Synchronize();

    /*! Returns the type of this template
    	\retval CSLTemplate::SI_MATERIAL Template type
    */
    virtual ETemplateType Type();
    virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);
    virtual CSLAnimatableType* ParameterFromType(EFCurveType in_Type, SI_Char *in_szParameterName);

	CSLColorRGBAProxy*							GetDiffuseColorProxy(){ return  &m_DiffuseColor;};
    CSLFloatProxy*								GetSpecularDecayProxy(){ return  &m_SpecularDecay;};
    CSLColorRGBProxy*							GetSpecularColorProxy(){ return  &m_SpecularColor;};
    CSLColorRGBProxy*							GetEmissiveColorProxy(){ return  &m_EmissiveColor;};
    CSLEnumProxy<EShadingModel, VERTEX_COLOR>*	GetShadingModelProxy(){ return  &m_ShadingModel;};
    CSLColorRGBProxy *							GetAmbientColorProxy(){ return  &m_AmbientColor;};

private:
    CSLColorRGBAProxy m_DiffuseColor;
    CSLFloatProxy m_SpecularDecay;
    CSLColorRGBProxy m_SpecularColor;
    CSLColorRGBProxy m_EmissiveColor;
    CSLEnumProxy<EShadingModel, VERTEX_COLOR> m_ShadingModel;
    CSLColorRGBProxy m_AmbientColor;
    CSLTexture2D *m_pTexture2D;

	void *m_pReserved;	// reserved for future extension
};

#endif
