//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSIImageFX2.h
	\brief Defines the CSLImageFX2 class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _XSIIMAGEFX2_H
#define _XSIIMAGEFX2_H

#include "Template.h"
class CSLImage;

/*! \brief This class represents an \xx ftk_XSI_ImageFX2 XSI_ImageFX2 \endxx template.

	Base class to define more image effects for dotXSI 5.0+ (see the \xx ftk_XSI_ImageFX2 XSI_ImageFX2 \endxx
	template reference).
	\since dotXSI 6.0
*/
class XSIEXPORT CSLImageFX2
    : public CSLTemplate
{
public:
	//! Defines the various scaling types
	enum EImageDefinitionType
	{
		SI_LOAD_IN_MEMORY,	/*!< 0-Load in memory */
		SI_USE_FROM_DISK,	/*!< 1-Use from disk */
		SI_BROADCAST,		/*!< 2-Broadcast */
	};

	/*! Defines the kind of optimization that will be used to smooth
	textures that are far from or near to the camera (OGL MipMapping).
	*/
	enum EOglFilter
	{
		SI_UNINTERPOLATED_PIXEL = 9728,							/*!< Uninterpolated pixel (quickest but lowest-quality optimization) */
		SI_INTERPOLATED_PIXEL = 9729,							/*!< Interpolated pixel (slowest but best-quality optimization for Texture Magnification Filter (Near) */
		SI_UNINTERPOLATED_PIXEL_NEAREST_MIPMAP = 9984,			/*!< Uninterpolated pixel using Nearest MipMap resolution. \note Only available for Texture Minification (Far) */
		SI_INTERPOLATED_PIXEL_NEAREST_MIPMAP = 9985,			/*!< Interpolated pixel using Nearest MipMap resolution. \note Only available for Texture Minification (Far) */
		SI_UNINTERPOLATED_PIXEL_INTERPOLATED_MIPMAP = 9986,		/*!< Uninterpolated pixel using Interpolated MipMap resolution. \note Only available for Texture Minification (Far) */
		SI_INTERPOLATED_PIXEL_INTERPOLATED_MIPMAP = 9987		/*!< Interpolated pixel using Interpolated MipMap resolution (slowest but best-quality optimization). \note Only available for Texture Minification (Far) */
	};

	//! Specifies the field order for video images clips.
	enum EFieldType
	{
		SI_NONE,	/* None */
		SI_ODD,		/* Upper Field First / Odd (PAL and HD Formats) */
		SI_EVEN		/* Lower Field First / Even (NTSC and DVFormats) */
	};

	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Refered template
	*/
	CSLImageFX2(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	//! Destructor
	virtual ~CSLImageFX2();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_IMAGE_FX2 The type of this template
	*/
	ETemplateType Type(){ return XSI_IMAGE_FX2; }

    virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);

	virtual CSLAnimatableType* ParameterFromType(EFCurveType in_Type, SI_Char *in_szParameterName);



	/*! Returns the Exposure value
		\return Exposure
	*/
	SI_Float GetExposure();

	/*! Sets the Exposure value
		\param[in]	in_fValue	new Exposure value
	*/
	SI_Void SetExposure( SI_Float in_fValue );

	/*! Returns the DisplayGamma value
		\return DisplayGamma
	*/
	SI_Float GetDisplayGamma();

	/*! Sets the DisplayGamma value
		\param[in]	in_fValue	new DisplayGamma value
	*/
	SI_Void SetDisplayGamma( SI_Float in_fValue );

	/*! Returns the DisplayGammaAffectsRendering value
		\return DisplayGammaAffectsRendering
	*/
	SI_Bool GetDisplayGammaAffectsRendering();

	/*! Sets the DisplayGammaAffectsRendering value
		\param[in]	in_bValue	new DisplayGammaAffectsRendering value
	*/
	SI_Void SetDisplayGammaAffectsRendering( SI_Bool in_bValue );

	/*! Returns the RenderColorProfile value
		\return RenderColorProfile
	*/
    SI_Char* GetRenderColorProfile();

	/*! Sets the RenderColorProfile value
		\param[in]	in_pValue	new RenderColorProfile value
	*/
	SI_Void SetRenderColorProfile( SI_Char* in_pValue);

	/*! Returns the RenderGamma value
		\return RenderGamma
	*/
    SI_Float GetRenderGamma();

	/*! Sets the RenderGamma value
		\param[in]	in_fValue	new RenderGamma value
	*/
	SI_Void SetRenderGamma( SI_Float in_fValue );

	/*! Returns the ImageDefinitionType value
		\return ImageDefinitionType
	*/
	EImageDefinitionType GetImageDefinitionType();

	/*! Sets the ImageDefinitionType value
		\param[in]	in_Value	new ImageDefinitionType value
	*/
	SI_Void SetImageDefinitionType( EImageDefinitionType in_Value );

	/*! Returns the EnableMipMap radius value
		\return EnableMipMap
	*/
	SI_Bool GetEnableMipMap();

	/*! Sets the EnableMipMap radius value
		\param[in]	in_bValue	new EnableMipMap value
	*/
	SI_Void SetEnableMipMap( SI_Bool in_bValue );

	/*! Returns the MipMapScale value
		\return MipMapScale
	*/
	SI_Float GetMipMapScale();

	/*! Sets the MipMapScale value
		\param[in]	in_fValue	new MipMapScale value
	*/
	SI_Void SetMipMapScale( SI_Float in_fValue );

	/*! Returns the OglMaxSize value
		\return OglMaxSize
	*/
	SI_Int GetOglMaxSize();

	/*! Sets the OglMaxSize value
		\param[in]	in_nValue	new OglMaxSize value
	*/
	SI_Void SetOglMaxSize( SI_Int in_nValue );

	/*! Returns the OglMipMap
		\return OglMipMap
	*/
	SI_Bool GetOglMipMap();

	/*! Sets the OglMipMap value
		\param[in]	in_Value the new OglMipMap value
	*/
	SI_Void SetOglMipMap( SI_Bool in_Value );

	/*! Returns the OglMinFilter value
		\return OglMinFilter
	*/
	EOglFilter GetOglMinFilter();

	/*! Sets the OglMinFilter value
		\param[in] in_Value	OglMinFilter
	*/
	SI_Void SetOglMinFilter( EOglFilter in_Value );

	/*! Returns the OglMagFilter value
		\return OglMagFilter value
	*/
	EOglFilter GetOglMagFilter();

	/*! Sets the OglMagFilter value
		\param[in] in_Value	OglMagFilter
	*/
	SI_Void SetOglMagFilter( EOglFilter in_Value );

	/*! Returns the FieldType value
		\return FieldType value
	*/
	EFieldType GetFieldType();

	/*! Sets the FieldType value
		\param[in] in_Value	new FieldType value
	*/
	SI_Void SetFieldType( EFieldType in_Value );

	/*! Returns the SourceTrack value
		\return SourceTrack value
	*/
	SI_Int GetSourceTrack();

	/*! Sets the SourceTrack value
		\param[in] in_bValue	new SourceTrack value
	*/
	SI_Void SetSourceTrack( SI_Int in_bValue );


    CSLFloatProxy*										GetExposureProxy() { return &m_Exposure; };
    CSLFloatProxy*										GetDisplayGammaProxy() { return &m_DisplayGamma; };
    CSLBoolProxy* 										GetDisplayGammaAffectsRenderingProxy() { return &m_DisplayGammaAffectsRendering; };

    CSLStringProxy* 									GetRenderColorProfileProxy() { return &m_RenderColorProfile; };
    CSLFloatProxy* 										GetRenderGammaProxy() { return &m_RenderGamma; };

	CSLEnumProxy<EImageDefinitionType, SI_BROADCAST>*	GetImageDefinitionTypeProxy() { return &m_ImageDefinitionType; };
    CSLBoolProxy* 										GetEnableMipMapProxy() { return &m_EnableMipMap; };
    CSLFloatProxy* 										GetMipMapScaleProxy() { return &m_MipMapScale; };

	CSLIntProxy*															GetOglMaxSizeProxy() { return &m_OglMaxSize; };
    CSLBoolProxy*															GetOglMipMapProxy() { return &m_OglMipMap; };
    CSLEnumProxy<EOglFilter, SI_INTERPOLATED_PIXEL_INTERPOLATED_MIPMAP>*	GetOglMinFilterProxy() { return &m_OglMinFilter; };
    CSLEnumProxy<EOglFilter, SI_INTERPOLATED_PIXEL>*						GetOglMagFilterProxy() { return &m_OglMagFilter; };

	CSLEnumProxy<EFieldType, SI_EVEN>* 					GetFieldTypeProxy() { return &m_FieldType; };
    CSLIntProxy* 										GetSourceTrackProxy() { return &m_SourceTrack; };

private:
	CSLFloatProxy	m_Exposure;
    CSLFloatProxy	m_DisplayGamma;
    CSLBoolProxy	m_DisplayGammaAffectsRendering;

    CSLStringProxy	m_RenderColorProfile;
    CSLFloatProxy	m_RenderGamma;

	CSLEnumProxy<EImageDefinitionType, SI_BROADCAST>	m_ImageDefinitionType;
    CSLBoolProxy										m_EnableMipMap;
    CSLFloatProxy										m_MipMapScale;

	CSLIntProxy																m_OglMaxSize;
    CSLBoolProxy															m_OglMipMap;
    CSLEnumProxy<EOglFilter, SI_INTERPOLATED_PIXEL_INTERPOLATED_MIPMAP>		m_OglMinFilter;
    CSLEnumProxy<EOglFilter, SI_INTERPOLATED_PIXEL>							m_OglMagFilter;

	CSLEnumProxy<EFieldType, SI_EVEN>	m_FieldType;
    CSLIntProxy							m_SourceTrack;

	SI_Void *m_pReserved;
};

#endif
