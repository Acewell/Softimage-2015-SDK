//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file dotXSITemplates6_0.h
	\brief Defines the registration functions for dotXSI 6.0

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//**************************************************************************************

#ifndef	DOTXSI_60_DEFINED
#define	DOTXSI_60_DEFINED
#include "dotXSITemplate.h"
#include "dotXSITemplates3_5.h"
#include "dotXSITemplates3_6.h"
#include "dotXSITemplates5_0.h"


//***************************************************************************************
// Defines
//***************************************************************************************

#define XSI_IK_RESPLANE_TYPE			0
#define XSI_IK_RESPLANE_ROLL			1
#define XSI_IK_RESPLANE_PREFROTX_ROLL	2
#define XSI_IK_RESPLANE_UPX				3
#define XSI_IK_RESPLANE_UPY				4
#define XSI_IK_RESPLANE_UPZ				5
#define XSI_IK_RESPLANE_UPVCTRELROOT	6
#define XSI_IK_RESPLANE_PREFX			7
#define XSI_IK_RESPLANE_PREFY			8
#define XSI_IK_RESPLANE_PREFZ			9
#define XSI_IK_RESPLANE_PREFRELROOT		10
#define XSI_IK_RESPLANE_NUM_PARAMS		11

#define XSI_CAMERA_PRESET					0
#define XSI_CAMERA_PICTURE_RATIO			1
#define XSI_CAMERA_FIELD_OF_VIEW			2
#define XSI_CAMERA_FIELD_OF_VIEW_TYPE		3
#define XSI_CAMERA_PROJECTION_TYPE			4
#define XSI_CAMERA_ORTHO_HEIGHT				5
#define XSI_CAMERA_INTEREST_DISTANCE		6
#define XSI_CAMERA_NEAR_PLANE				7
#define XSI_CAMERA_FAR_PLANE				8
#define XSI_CAMERA_PROJ_PLANE_ENABLE		9
#define XSI_CAMERA_FILM_APERTURE_X			10
#define XSI_CAMERA_FILM_APERTURE_Y			11
#define XSI_CAMERA_OPTICAL_CENTER_SHIFT_X	12
#define XSI_CAMERA_OPTICAL_CENTER_SHIFT_Y	13
#define XSI_CAMERA_NUM_PARAMS				14

#define XSI_TRANSLATE_X						0
#define XSI_TRANSLATE_Y						1
#define XSI_TRANSLATE_Z						2
#define XSI_TRANSLATE_NUM_PARAMS			3

#define XSI_SCALE_X							0
#define XSI_SCALE_Y							1
#define XSI_SCALE_Z							2
#define XSI_SCALE_NUM_PARAMS				3

#define XSI_ROTATE_X						0
#define XSI_ROTATE_Y						1
#define XSI_ROTATE_Z						2
#define XSI_ROTATE_ANGLE					3
#define XSI_ROTATE_NUM_PARAMS				4

#define XSI_SHEAR_X1						0
#define XSI_SHEAR_Y1						1
#define XSI_SHEAR_Z1						2
#define XSI_SHEAR_X2						3
#define XSI_SHEAR_Y2						4
#define XSI_SHEAR_Z2						5
#define XSI_SHEAR_ANGLE						6
#define XSI_SHEAR_NUM_PARAMS				7

#define XSI_LOOKAT_PX						0
#define XSI_LOOKAT_PY						1
#define XSI_LOOKAT_PZ						2
#define XSI_LOOKAT_IX						3
#define XSI_LOOKAT_IY						4
#define XSI_LOOKAT_IZ						5
#define XSI_LOOKAT_UX						6
#define XSI_LOOKAT_UY						7
#define XSI_LOOKAT_UZ						8
#define XSI_LOOKAT_NUM_PARAMS				9

#define XSI_MATRIX_00						0
#define XSI_MATRIX_01						1
#define XSI_MATRIX_02						2
#define XSI_MATRIX_03						3
#define XSI_MATRIX_10						4
#define XSI_MATRIX_11						5
#define XSI_MATRIX_12						6
#define XSI_MATRIX_13						7
#define XSI_MATRIX_20						8
#define XSI_MATRIX_21						9
#define XSI_MATRIX_22						10
#define XSI_MATRIX_23						11
#define XSI_MATRIX_30						12
#define XSI_MATRIX_31						13
#define XSI_MATRIX_32						14
#define XSI_MATRIX_33						15
#define XSI_MATRIX_NUM_PARAMS				16

#define XSI_SHAPEREFERENCE_REFERENCE		0
#define XSI_SHAPEREFERENCE_NUM_PARAMS		1

#define XSI_INDEX_LIST_NBATTRIBUTES		0
#define XSI_INDEX_LIST_ARRAY			1
#define	XSI_INDEX_LIST_NUM_PARAMS		1

#define XSI_CAMERA_FOCALLENGTH_FOCALLENGTH			0
#define XSI_CAMERA_FOCALLENGTH_NUM_PARAMS			1

#define XSI_SHADER_MULTI_PORT_NBPORTS		0
#define XSI_SHADER_MULTI_PORT_PORT_NAME_ARRAY	1
#define XSI_SHADER_MULTI_PORT_PORT_TYPE_ARRAY	2
#define XSI_SHADER_MULTI_PORT_NUM_PARAMS	1

#define XSI_SHADER_MULTI_PORT_CONNECTION_PARAMETER	0
#define XSI_SHADER_MULTI_PORT_CONNECTION_PORT_NAME	1
#define XSI_SHADER_MULTI_PORT_CONNECTION_NUM_PARAMS	2

#define	XSI_IMAGE_FX2_EXPOSURE							0
#define	XSI_IMAGE_FX2_DISPLAY_GAMMA						1
#define	XSI_IMAGE_FX2_DISPLAY_GAMMA_AFFECTS_RENDERING	2
#define	XSI_IMAGE_FX2_RENDER_COLOR_PROFILE				3
#define	XSI_IMAGE_FX2_RENDER_GAMMA						4
#define	XSI_IMAGE_FX2_IMAGE_DEFINITION_TYPE				5
#define	XSI_IMAGE_FX2_ENABLE_MIPMAP						6
#define	XSI_IMAGE_FX2_MIPMAP_SCALE						7
#define	XSI_IMAGE_FX2_OGL_MAXSIZE						8
#define	XSI_IMAGE_FX2_OGL_MIPMAP						9
#define	XSI_IMAGE_FX2_OGL_MINFILTER						10
#define	XSI_IMAGE_FX2_OGL_MAGFILTER						11
#define	XSI_IMAGE_FX2_FIELD_TYPE						12
#define	XSI_IMAGE_FX2_SOURCE_TRACK						13
#define	XSI_IMAGE_FX2_NUM_PARAMS						14

#define	XSI_TEXTURE_LAYER_ORDER							0
#define	XSI_TEXTURE_LAYER_MUTE							1
#define	XSI_TEXTURE_LAYER_SOLO							2
#define	XSI_TEXTURE_LAYER_COLOR_CONNECTION				3
#define	XSI_TEXTURE_LAYER_R								4
#define	XSI_TEXTURE_LAYER_G								5
#define	XSI_TEXTURE_LAYER_B								6
#define	XSI_TEXTURE_LAYER_A								7
#define	XSI_TEXTURE_LAYER_COLOR_PREMULTIPLIED			8
#define	XSI_TEXTURE_LAYER_IGNORE_COLOR_ALPHA			9
#define	XSI_TEXTURE_LAYER_INVERT_COLOR_ALPHA			10
#define	XSI_TEXTURE_LAYER_ALPHA_COLOR					11
#define	XSI_TEXTURE_LAYER_MASK_CONNECTION				12
#define	XSI_TEXTURE_LAYER_MASK							13
#define	XSI_TEXTURE_LAYER_INVERT_MASK					14
#define	XSI_TEXTURE_LAYER_MASK_MODE						15
#define	XSI_TEXTURE_LAYER_MASK_THRESHOLD				16
#define	XSI_TEXTURE_LAYER_WEIGHT						17
#define	XSI_TEXTURE_LAYER_MODE							18
#define	XSI_TEXTURE_LAYER_NUM_PARAMS					19

#define	XSI_TEXTURE_LAYER_PORT_TARGET					0
#define	XSI_TEXTURE_LAYER_PORT_MUTE						1
#define	XSI_TEXTURE_LAYER_PORT_SCALE					2
#define	XSI_TEXTURE_LAYER_PORT_COLOR_SOURCE				3
#define	XSI_TEXTURE_LAYER_PORT_INVERT					4
#define	XSI_TEXTURE_LAYER_PORT_NUM_PARAMS				5

#define	XSI_USER_KEYWORD_LIST							0
#define	XSI_USER_KEYWORD_NUM_PARAMS						1

#define	XSI_CLIP_TO_PARENT_START						0
#define	XSI_CLIP_TO_PARENT_END							1
#define	XSI_CLIP_TO_PARENT_NUM_PARAMS					2

#define	XSI_SHADER_COMPOUND_CATEGORY					0
#define	XSI_SHADER_COMPOUND_DESCRIPTION					1
#define	XSI_SHADER_COMPOUND_AUTHOR						2
#define	XSI_SHADER_COMPOUND_DATE						3
#define	XSI_SHADER_COMPOUND_VERSION_TAG					4
#define	XSI_SHADER_COMPOUND_VERSION_MAJOR				5
#define	XSI_SHADER_COMPOUND_VERSION_MINOR				6
#define	XSI_SHADER_COMPOUND_PPG_LOGIC					7
#define	XSI_SHADER_COMPOUND_PPG_LOGIC_LANGUAGE			8
#define	XSI_SHADER_COMPOUND_BACKGROUND_COLOR			9
#define	XSI_SHADER_COMPOUND_NUM_PARAMS					10

#define	XSI_SHADER_COMPOUND_PORT_PORTTYPE				0
#define	XSI_SHADER_COMPOUND_PORT_DISPLAY_NAME			1
#define	XSI_SHADER_COMPOUND_PORT_PPG_MIN_VALUE			2
#define	XSI_SHADER_COMPOUND_PORT_PPG_MAX_VALUE			3
#define	XSI_SHADER_COMPOUND_PORT_PPG_ENUM_VALUES		4
#define	XSI_SHADER_COMPOUND_PORT_PPG_LAYOUT_VISIBLE		5
#define	XSI_SHADER_COMPOUND_PORT_PPG_LAYOUT_GROUP		6
#define	XSI_SHADER_COMPOUND_PORT_PPG_LAYOUT_TAB			7
#define	XSI_SHADER_COMPOUND_PORT_RT_LAYOUT_VISIBLE		8
#define	XSI_SHADER_COMPOUND_PORT_RT_LAYOUT_GROUP		9
#define	XSI_SHADER_COMPOUND_PORT_SOURCE_SHADER			10
#define	XSI_SHADER_COMPOUND_PORT_NUM_PARAMS				11

//***************************************************************************************
// Registration
//***************************************************************************************

extern	TemplateCreation	RegistrationTable60[];

/*! \addtogroup regfunc_60 Registration functions for dotXSI 6.0
*  @{
*/

/*! \xx ftk_XSI_IK_ResolutionPlane XSI_IK_ResolutionPlane \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_XSI_IK_ResolutionPlane XSI_IK_ResolutionPlane \endxx template
*/
CdotXSITemplate*	Register_XSI_IK_ResolutionPlane();

/*! \xx ftk_XSI_Camera XSI_Camera \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_XSI_Camera XSI_Camera \endxx template
*/
CdotXSITemplate*	Register_XSI_Camera();

/*! XSI \xx ftk_Polymatricks Polymatricks \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_Polymatricks Polymatricks \endxx template
*/
CdotXSITemplate*	Register_XSI_Polymatricks();

/*! XSI \xx ftk_translate translate \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_translate translate \endxx template
*/
CdotXSITemplate*	Register_XSI_Translate();

/*! XSI \xx ftk_Rotate Rotate \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_Rotate Rotate \endxx template
*/
CdotXSITemplate*	Register_XSI_Rotate();

/*! XSI \xx ftk_Scale Scale \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_Scale Scale \endxx template
*/
CdotXSITemplate*	Register_XSI_Scale();

/*! XSI \xx ftk_Shear Shear \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_Shear Shear \endxx template
*/
CdotXSITemplate*	Register_XSI_Shear();

/*! XSI \xx ftk_Lookat Lookat \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_Lookat Lookat \endxx template
*/
CdotXSITemplate*	Register_XSI_Lookat();

/*! XSI \xx ftk_Matrix Matrix \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_Matrix Matrix \endxx template
*/
CdotXSITemplate*	Register_XSI_Matrix();

/*! XSI Shape \xx ftk_Reference Reference \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_Reference Reference \endxx template
*/
CdotXSITemplate*	Register_XSI_ShapeReference();

/*! XSI Action Clip \xx ftk_Container Container \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_Container Container \endxx template
*/
CdotXSITemplate*	Register_XSI_ActionClipContainer();

/*! \xx ftk_XSI_IndexList XSI_IndexList \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_XSI_IndexList XSI_IndexList \endxx template
*/
CdotXSITemplate*	Register_XSI_IndexList();
/*! \xx ftk_XSI_CameraFocalLength XSI_CameraFocalLength \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_XSI_CameraFocalLength XSI_CameraFocalLength \endxx template
*/
CdotXSITemplate*	Register_XSI_CameraFocalLength();

/*! \xx ftk_XSI_ShaderMultiPortConnection XSI_ShaderMultiPortConnection \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_XSI_ShaderMultiPortConnection XSI_ShaderMultiPortConnection \endxx template
*/
CdotXSITemplate*	Register_XSI_ShaderMultiPortConnection();

/*! \xx ftk_XSI_ImageFX2 XSI_ImageFX2 \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_XSI_ImageFX2 XSI_ImageFX2 \endxx template
*/
CdotXSITemplate*	Register_XSI_ImageFX2();

/*! \xx ftk_XSI_TextureLayer XSI_TextureLayer \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_XSI_TextureLayer XSI_TextureLayer \endxx template
*/
CdotXSITemplate*	Register_XSI_TextureLayer();

/*! \xx ftk_XSI_TextureLayerPort XSI_TextureLayerPort \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_XSI_TextureLayerPort XSI_TextureLayerPort \endxx template
*/
CdotXSITemplate*	Register_XSI_TextureLayerPort();

/*! \xx ftk_XSI_UserKeyword XSI_UserKeyword \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_XSI_UserKeyword XSI_UserKeyword \endxx template
*/
CdotXSITemplate*	Register_XSI_UserKeyword();

/*! \xx ftk_XSI_ClipToParent XSI_ClipToParent \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_XSI_ClipToParent XSI_ClipToParent \endxx template
*/
CdotXSITemplate*	Register_XSI_ClipToParent();

/*! \xx ftk_XSI_ShaderCompound XSI_ShaderCompound \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_XSI_ShaderCompound XSI_ShaderCompound \endxx template
*/
CdotXSITemplate*	Register_XSI_ShaderCompound();

/*! \xx ftk_XSI_ShaderCompoundPort XSI_ShaderCompoundPort \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_XSI_ShaderCompoundPort XSI_ShaderCompoundPort \endxx template
*/
CdotXSITemplate*	Register_XSI_ShaderCompoundPort();

/*! @} */

#endif //DOTXSI_60_DEFINED
