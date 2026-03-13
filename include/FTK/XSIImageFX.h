//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSIImageFX.h
	\brief Defines the CSLImageFX class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _XSIIMAGEFX_H
#define _XSIIMAGEFX_H

#include "Template.h"
class CSLImage;

/*! \brief This class represents an \xx ftk_XSI_ImageFX XSI_ImageFX \endxx template.

	Base class to define image transformation effects for dotXSI 5.0+ (see the \xx ftk_XSI_ImageFX XSI_ImageFX \endxx
	template reference).
	\note This template was introduced in dotXSI Version 3.6
*/
class XSIEXPORT CSLImageFX
    : public CSLTemplate
{
public:
	//! Defines the various scaling types
	enum EScalingType
	{
		SI_NONE,	/*!< 0-none */
		SI_FULL,	/*!< 1-fullsize */
		SI_HALF,	/*!< 2-halfsize */
		SI_QUARTER,	/*!< 3-quartersize */
		SI_128,		/*!< 4-128 X 128 */
		SI_256,		/*!< 5-256 X 256 */
		SI_512,		/*!< 6-512 X 512 */
		SI_CUSTOM,	/*!< 7- Custom (use scale X and scale Y) */
	};

	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Refered template
	*/
	CSLImageFX(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	//! Destructor
	virtual ~CSLImageFX();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_IMAGE_FX Template type
	*/
	ETemplateType Type(){ return XSI_IMAGE_FX; }

    virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);

	virtual CSLAnimatableType* ParameterFromType(EFCurveType in_Type, SI_Char *in_szParameterName);

	/*! Returns the Hue value
		\return Hue
	*/
	SI_Float GetHue();

	/*! Sets the Hue value
		\param[in]	in_fValue	new Hue value
	*/
	SI_Void SetHue( SI_Float in_fValue );

	/*! Returns the Gain value
		\return Gain
	*/
	SI_Float GetGain();

	/*! Sets the Gain value
		\param[in]	in_fValue	new Gain value
	*/
	SI_Void SetGain( SI_Float in_fValue );

	/*! Returns the Saturation value
		\return Saturation
	*/
	SI_Float GetSaturation();

	/*! Sets the Saturation value
		\param[in]	in_fValue	new Saturation value
	*/
	SI_Void SetSaturation( SI_Float in_fValue );

	/*! Returns the Brightness value
		\return Brightness
	*/
	SI_Float GetBrightness();

	/*! Sets the Brightness value
		\param[in]	in_fValue	new Brightness value
	*/
	SI_Void SetBrightness( SI_Float in_fValue );

	/*! Returns the Blur radius value
		\return Blur radius
	*/
	SI_Float GetBlurRadius();

	/*! Sets the Blur radius value
		\param[in]	in_fValue	new Blur radius value
	*/
	SI_Void SetBlurRadius( SI_Float in_fValue );

	/*! Returns the Blur amount value
		\return Blur amount
	*/
	SI_Float GetBlurAmount();

	/*! Sets the Blur amount value
		\param[in]	in_fValue	new Blur amount value
	*/
	SI_Void SetBlurAmount( SI_Float in_fValue );

	/*! Returns the Blur alpha value
		\return Blur alpha
	*/
	SI_Bool GetBlurAlpha();

	/*! Sets the Blur Alpha value
		\param[in]	in_bValue	new Blur Alpha value
	*/
	SI_Void SetBlurAlpha( SI_Bool in_bValue );

	/*! Returns the scaling type
		\return scaling type
	*/
	EScalingType GetScalingType();

	/*! Sets the Scaling type value
		\param[in]	in_Type the new scaling type
	*/
	SI_Void SetScalingType( EScalingType in_Type );

	/*! Returns the horizontal scale value
		\return horizontal scale
	*/
	SI_Float GetHorizontalScale();

	/*! Sets the horizontal scale value
		\param[in] in_fValue	horizontal scale
	*/
	SI_Void SetHorizontalScale( SI_Float in_fValue );

	/*! Returns the vertical scale value
		\return vertical scale
	*/
	SI_Float GetVerticalScale();

	/*! Sets the vertical scale value
		\param[in] in_fValue	vertical scale
	*/
	SI_Void SetVerticalScale( SI_Float in_fValue );

	/*! Returns a value indicating wether the image is horizontally flipped
		\return Horizontal flip value
	*/
	SI_Bool GetFlipHorizontal();

	/*! Sets a value indicating wether the image is horizontally flipped
		\param[in] in_bValue	Horizontal flip value
	*/
	SI_Void SetFlipHorizontal( SI_Bool in_bValue );

	/*! Returns a value indicating wether the image is vertically flipped
		\return Vertical flip value
	*/
	SI_Bool GetFlipVertical();

	/*! Sets a value indicating wether the image is vertically flipped
		\param[in] in_bValue	Vertical flip value
	*/
	SI_Void SetFlipVertical( SI_Bool in_bValue );

	/*! Returns a value indicating wether the image is converted to grayscale
		\return converted to grayscale
	*/
	SI_Bool GetRGBA2Greyscale();

	/*! Sets a value indicating wether the image is converted to grayscale
		\param[in] in_bValue	converted to grayscale
	*/
	SI_Void SetRGBA2Greyscale( SI_Bool in_bValue );

	/*! Returns a value indicating wether the image is converted to 16bit
		\return converted to 16bit
	*/
	SI_Bool GetConvertTo16Bits();

	/*! Sets a value indicating wether the image is converted to 16bit
		\param[in] in_bValue	converted to 16bit
	*/
	SI_Void SetConvertTo16Bits( SI_Bool in_bValue );

	CSLFloatProxy*							GetHueProxy() { return &m_Hue; };
    CSLFloatProxy*							GetGainProxy() { return &m_Gain; };
    CSLFloatProxy*							GetSaturationProxy() { return &m_Saturation; };
    CSLFloatProxy* 							GetBrightnessProxy() { return &m_Brightness; };
    CSLFloatProxy* 							GetBlurRadiusProxy() { return &m_BlurRadius; };
    CSLFloatProxy* 							GetBlurAmountProxy() { return &m_BlurAmount; };
    CSLBoolProxy*							GetBlurAlphaProxy() { return &m_BlurAlpha; };
    CSLEnumProxy<EScalingType, SI_CUSTOM>*	GetScalingTypeProxy() { return &m_ScalingType; };
    CSLFloatProxy*							GetScaleXProxy() { return &m_ScaleX; };
    CSLFloatProxy*							GetScaleYProxy() { return &m_ScaleY; };
    CSLBoolProxy* 							GetFlipHorizontalProxy() { return &m_FlipHorizontal; };
    CSLBoolProxy* 							GetFlipVerticalProxy() { return &m_FlipVertical; };
    CSLBoolProxy* 							GetRGBA2GreyscaleProxy() { return &m_RGBA2Greyscale; };
    CSLBoolProxy* 							GetBitsPerChannelProxy() { return &m_BitsPerChannel; };

private:
	CSLFloatProxy m_Hue;
    CSLFloatProxy m_Gain;
    CSLFloatProxy m_Saturation;
    CSLFloatProxy m_Brightness;
    CSLFloatProxy m_BlurRadius;
    CSLFloatProxy m_BlurAmount;
    CSLBoolProxy m_BlurAlpha;
    CSLEnumProxy<EScalingType, SI_CUSTOM> m_ScalingType;
    CSLFloatProxy m_ScaleX;
    CSLFloatProxy m_ScaleY;
    CSLBoolProxy m_FlipHorizontal;
    CSLBoolProxy m_FlipVertical;
    CSLBoolProxy m_RGBA2Greyscale;
    CSLBoolProxy m_BitsPerChannel;

	SI_Void *m_pReserved;
};

#endif
