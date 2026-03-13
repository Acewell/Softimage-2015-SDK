//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file Texture2D.h
	\brief Defines the CSLTexture2D class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _TEXTVRE2D_H
#define _TEXTVRE2D_H

#include "Template.h"


/*! \brief This class represents an \xx ftk_SI_Texture2D SI_Texture2D \endxx template.

	Describes a 2D texture (see the \xx ftk_SI_Texture2D SI_Texture2D \endxx
	template reference).
*/
class XSIEXPORT CSLTexture2D
	: public CSLTemplate
{
public:
	/*! This enum lists all mapping type supported by the texture 2D.
	*/
	enum EMappingType
	{
		SI_XY_PROJECTION,				/*!< XY Projection */
		SI_XZ_PROJECTION,				/*!< XZ Projection */
		SI_YZ_PROJECTION,				/*!< YZ Projection */
		SI_UV_MAP,						/*!< UV Map */
		SI_UV_MAP_WRAPPED,				/*!< UV Map Wrapped */
		SI_CYLINDRICAL_PROJECTION,		/*!< Cylindrical Projection */
		SI_SPHERICAL_PROJECTION,		/*!< Spherical Projection */
		SI_REFLECTION_MAP,				/*!< Reflection Map */
	};

	/*! This enum lists all blending type supported by the texture 2D.
	*/
	enum EBlendingType
	{
		SI_ALPHA_MASK,					/*!< Alpha Mask */
		SI_INTENSITY_MASK,				/*!< Intensity Mask */
		SI_NO_MASK,						/*!< No Mask */
		SI_RGB_MODULATION,				/*!< RGB Modulation */
	};

	CSLTexture2D(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
	virtual ~CSLTexture2D();

	/*! Returns the name of the texture's image file.
		\return Image file name.
	*/
	SI_Char*			GetImageFileName() { return m_ImageName; }

	/*! Changes the name of the texture's image file.
		\param[in]	in_szValue	New image file name.
	*/
	SI_Void 			SetImageFileName(SI_Char* in_szValue) { m_ImageName = in_szValue; }

	/*! Returns the mapping type of the texture.
		\return Mapping type.
	*/
	EMappingType		GetMappingType() { return m_MappingType; }

	/*! Changes the mapping type of the texture.
		\param[in]	in_Type	New mapping type.
	*/
	SI_Void 			SetMappingType(EMappingType in_Type) { m_MappingType = in_Type; }

	/*! Returns the width in pixel of the image.
		\return Image width.
	*/
	SI_Int				GetImageWidth() { return m_Width; }

	/*! Changes the width of the image.
		\param[in]	in_nValue	New image width.
	*/
	SI_Void 			SetImageWidth(SI_Int in_nValue) { m_Width = in_nValue; }

	/*! Returns the height in pixel of the image.
		\return Image height.
	*/
	SI_Int				GetImageHeight() { return m_Height; }

	/*! Changes the height of the image.
		\param[in]	in_nValue	New image height.
	*/
	SI_Void 			SetImageHeight(SI_Int in_nValue) { m_Height = in_nValue; }

	/*! Returns the start of the cropping region in V.
		\return Start of the cropping region in V.
	*/
	SI_Int				GetCropUMin() { return m_CropUMin; }

	/*! Changes the start of the cropping region in V.
		\param[in]	in_nValue	New start of the cropping region in V.
	*/
	SI_Void 			SetCropUMin(SI_Int in_nValue) { m_CropUMin = in_nValue; }

	/*! Returns the end of the cropping region in V.
		\return End of the cropping region in V.
	*/
	SI_Int				GetCropUMax() { return m_CropUMax; }

	/*! Changes the end of the cropping region in V.
		\param[in]	in_nValue	New end of the cropping region in V.
	*/
	SI_Void 			SetCropUMax(SI_Int in_nValue) { m_CropUMax = in_nValue; }

	/*! Returns the start of the cropping region in V.
		\return Start of the cropping region in V.
	*/
	SI_Int				GetCropVMin() { return m_CropVMin; }

	/*! Changes the start of the cropping region in V.
		\param[in]	in_nValue	New start of the cropping region in V.
	*/
	SI_Void 			SetCropVMin(SI_Int in_nValue) { m_CropVMin = in_nValue; }

	/*! Returns the end of the cropping region in V.
		\return End of the cropping region in V.
	*/
	SI_Int				GetCropVMax() { return m_CropVMax; }

	/*! Changes the end of the cropping region in V.
		\param[in]	in_nValue	New end of the cropping region in V.
	*/
	SI_Void 			SetCropVMax(SI_Int in_nValue) { m_CropVMax = in_nValue; }

	/*! Indicates if the U and V orientations are swapped.
		\return UV swap state.
	*/
	SI_Bool 			GetUVSwapFlag() { return m_UVSwap; }

	/*! Changes the U and V orientations swapping state.
		\param[in]	in_bState New UV swap state.
	*/
	SI_Void 			SetUVSwapFlag(SI_Bool in_bState) { m_UVSwap = in_bState; }

	/*! Returns the number of horizontal repetitions of the image.
		\return Number of horizontal repetitions.
	*/
	SI_Int				GetURepeat() { return m_URepeat; }

	/*! Changes the number of horizontal repetitions of the image.
		\param[in]	in_nValue	New number of horizontal repetitions.
	*/
	SI_Void 			SetURepeat(SI_Int in_nValue) { m_URepeat = in_nValue; }

	/*! Returns the number of vertical repetitions of the image.
		\return Number of vertical repetitions.
	*/
	SI_Int				GetVRepeat() { return m_VRepeat; }

	/*! Changes the number of vertical repetitions of the image.
		\param[in]	in_nValue	New number of vertical repetitions.
	*/
	SI_Void 			SetVRepeat(SI_Int in_nValue) { m_VRepeat = in_nValue; }

	/*! Returns the flag that indicates if the texture is mirrored horizontally.
		\return U alternate state.
	*/
	SI_Bool 			GetUAlternate() { return m_UAlternate; }

	/*! Changes the flag that indicates if the texture is mirrored horizontally.
		\param[in]	in_bState New U alternate state.
	*/
	SI_Void 			SetUAlternate(SI_Bool in_bState) { m_UAlternate = in_bState; }

	/*! Returns the flag that indicates if the texture is mirrored horizontally.
		\return V alternate state.
	*/
	SI_Bool 			GetVAlternate() { return m_VAlternate; }

	/*! Changes the flag that indicates if the texture is mirrored horizontally.
		\param[in]	in_bState New V alternate state.
	*/
	SI_Void 			SetVAlternate(SI_Bool in_bState) { m_VAlternate = in_bState; }

	/*! Returns the scaling of image in U.
		\return Scaling of image in U.
	*/
	SI_Float			GetUScale() { return m_UScale; }

	/*! Changes the scaling of image in U.
		\param[in]	in_fValue	New scaling of image in U.
	*/
	SI_Void 			SetUScale(SI_Float in_fValue) { m_UScale = in_fValue; }

	/*! Returns the scaling of image in V.
		\return Scaling of image in V.
	*/
	SI_Float			GetVScale() { return m_VScale; }

	/*! Changes the scaling of image in V.
		\param[in]	in_fValue	New scaling of image in V.
	*/
	SI_Void 			SetVScale(SI_Float in_fValue) { m_VScale = in_fValue; }

	/*! Returns the offset of image in U.
		\return Offset of image in U.
	*/
	SI_Float			GetUOffset() { return m_UOffset; }

	/*! Changes the offset of image in U.
		\param[in]	in_fValue	New offset of image in U.
	*/
	SI_Void 			SetUOffset(SI_Float in_fValue) { m_UOffset = in_fValue; }

	/*! Returns the offset of image in V.
		\return Offset of image in V.
	*/
	SI_Float			GetVOffset() { return m_VOffset; }

	/*! Changes the offset of image in V.
		\param[in]	in_fValue	New offset of image in V.
	*/
	SI_Void 			SetVOffset(SI_Float in_fValue) { m_VOffset = in_fValue; }

	/*! Returns the projection matrix of the texture.
		\return projection matrix.
	*/
	CSIBCMatrix4x4		GetProjectionMatrix() { return m_ProjectionMatrix; }

	/*! Changes the projection matrix of the texture.
		\param[in]	in_Value New projection matrix.
	*/
	SI_Void 			SetProjectionMatrix(CSIBCMatrix4x4& in_Value) { m_ProjectionMatrix = in_Value; }

	/*! Returns the type of blending between texture and material attributes.
		\return Blending type.
	*/
	EBlendingType		GetBlendingType() { return m_BlendingType; }

	/*! Changes the type of blending between texture and material attributes.
		\param[in]	in_Type	New blending type.
	*/
	SI_Void 			SetBlendingType(EBlendingType in_Type) { m_BlendingType = in_Type; }

	/*! Returns the normalized contribution of texture attributes (ambient, diffuse, specular, transparency, reflectivity).
		\return Contribution of texture attributes.
	*/
	SI_Float			GetBlending() { return m_Blending; }

	/*! Changes the normalized contribution of texture attributes.
		\param[in]	in_fValue	New contribution of texture attributes.
	*/
	SI_Void 			SetBlending(SI_Float in_fValue) { m_Blending = in_fValue; }

	/*! Returns the normalized contribution of texture pixel colors to the material ambient color.
		\return Contribution of texture.
	*/
	SI_Float			GetAmbient() { return m_Ambient; }

	/*! Changes the normalized contribution of texture pixel colors to the material ambient color.
		\param[in]	in_fValue	New contribution of texture.
	*/
	SI_Void 			SetAmbient(SI_Float in_fValue) { m_Ambient = in_fValue; }

	/*! Returns the normalized contribution of texture pixel colors to the material diffuse color.
		\return Contribution of texture.
	*/
	SI_Float			GetDiffuse() { return m_Diffuse; }

	/*! Changes the normalized contribution of texture pixel colors to the material diffuse color.
		\param[in]	in_fValue	New contribution of texture.
	*/
	SI_Void 			SetDiffuse(SI_Float in_fValue) { m_Diffuse = in_fValue; }

	/*! Returns the normalized contribution of texture pixel colors to the material specular color.
		\return Contribution of texture.
	*/
	SI_Float			GetSpecular() { return m_Specular; }

	/*! Changes the normalized contribution of texture pixel colors to the material specular color.
		\param[in]	in_fValue	New contribution of texture.
	*/
	SI_Void 			SetSpecular(SI_Float in_fValue) { m_Specular = in_fValue; }

	/*! Returns the normalized contribution of texture pixel colors to the material transparency level.
		\return Contribution of texture.
	*/
	SI_Float			GetTransparency() { return m_Transparency; }

	/*! Changes the normalized contribution of texture pixel colors to the material transparency level.
		\param[in]	in_fValue	New contribution of texture.
	*/
	SI_Void 			SetTransparency(SI_Float in_fValue) { m_Transparency = in_fValue; }

	/*! Returns the normalized contribution of texture pixel colors to the material reflectivity level.
		\return Contribution of texture.
	*/
	SI_Float			GetReflectivity() { return m_Reflectivity; }

	/*! Changes the normalized contribution of texture pixel colors to the material reflectivity level.
		\param[in]	in_fValue	New contribution of texture.
	*/
	SI_Void 			SetReflectivity(SI_Float in_fValue) { m_Reflectivity = in_fValue; }

	/*! Returns the bump mapping intensity and/or displacement of geometry along surface normals.
		\return Bump mapping intensity.
	*/
	SI_Float			GetRoughness() { return m_Roughness; }

	/*! Changes the bump mapping intensity.
		\param[in]	in_fValue	New bump mapping intensity.
	*/
	SI_Void 			SetRoughness(SI_Float in_fValue) { m_Roughness = in_fValue; }

	/*! Returns the type of this template
		\retval CSLTemplate::SI_TEXTURE_2D Template type
	*/
	virtual ETemplateType Type() { return SI_TEXTURE_2D; }

private:
	CSLStringProxy		m_ImageName;
    CSLEnumProxy<EMappingType, SI_REFLECTION_MAP>	m_MappingType;
	CSLIntProxy 		m_Width;
	CSLIntProxy 		m_Height;
	CSLIntProxy 		m_CropUMin;
	CSLIntProxy 		m_CropUMax;
	CSLIntProxy 		m_CropVMin;
	CSLIntProxy 		m_CropVMax;
	CSLBoolProxy		m_UVSwap;
	CSLIntProxy 		m_URepeat;
	CSLIntProxy 		m_VRepeat;
	CSLBoolProxy		m_UAlternate;
	CSLBoolProxy		m_VAlternate;
	CSLFloatProxy		m_UScale;
	CSLFloatProxy		m_VScale;
	CSLFloatProxy		m_UOffset;
	CSLFloatProxy		m_VOffset;
	CSLMatrix4x4Proxy	m_ProjectionMatrix;
    CSLEnumProxy<EBlendingType, SI_RGB_MODULATION>	m_BlendingType;
	CSLFloatProxy		m_Blending;
	CSLFloatProxy		m_Ambient;
	CSLFloatProxy		m_Diffuse;
	CSLFloatProxy		m_Specular;
	CSLFloatProxy		m_Transparency;
	CSLFloatProxy		m_Reflectivity;
	CSLFloatProxy		m_Roughness;

	void *m_pReserved;	// reserved for future extension
};

#endif
