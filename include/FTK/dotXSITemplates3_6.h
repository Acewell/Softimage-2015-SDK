//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file dotXSITemplates3_6.h
	\brief Defines the registration functions for dotXSI 3.6

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef	DOTXSI_36_DEFINED
#define	DOTXSI_36_DEFINED
#include "dotXSITemplate.h"
#include "dotXSITemplates3_5.h"

//***************************************************************************************
// Defines
//***************************************************************************************

#define	XSI_IMAGE_LIBRARY_NB_IMAGE		0
#define	XSI_IMAGE_LIBRARY_NUM_PARAMS	1

#define	XSI_NURBS_TRIM_BOUNDARY			0
#define	XSI_NURBS_TRIM_PROJECTIONTYPE	1
#define	XSI_NURBS_TRIM_NUM_PARAMS		2

#define	XSI_NURBS_PROJECTION_PROJECTIONTYPE		0
#define	XSI_NURBS_PROJECTION_NUM_PARAMS			1

#define	XSI_IMAGE_FILE_NAME				0
#define	XSI_IMAGE_SIZE_X				1
#define	XSI_IMAGE_SIZE_Y				2
#define	XSI_IMAGE_NUM_CHANNELS			3
#define	XSI_IMAGE_BITS_PER_PIXEL		4
#define	XSI_IMAGE_CROP_MIN_X			5
#define	XSI_IMAGE_CROP_MAX_X			6
#define	XSI_IMAGE_CROP_MIN_Y			7
#define	XSI_IMAGE_CROP_MAX_Y			8
#define	XSI_IMAGE_FRAME_RATE			9
#define	XSI_IMAGE_NUM_FRAMES			10
#define	XSI_IMAGE_FIRST_FRAME			11
#define	XSI_IMAGE_LAST_FRAME			12
#define	XSI_IMAGE_NUM_PARAMS			13

#define XSI_IMAGE_DATA_NUM_ENTRIES		0
#define	XSI_IMAGE_DATA_COMPRESS			1
#define	XSI_IMAGE_DATA_STREAM			2
#define	XSI_IMAGE_DATA_NUM_PARAMS		3

#define	XSI_IMAGE_FX_HUE				0
#define	XSI_IMAGE_FX_GAIN				1
#define	XSI_IMAGE_FX_SATURATION			2
#define	XSI_IMAGE_FX_BRIGHTNESS			3
#define	XSI_IMAGE_FX_RADIUS				4
#define	XSI_IMAGE_FX_AMOUNT				5
#define	XSI_IMAGE_FX_BLUR_ALPHA			6
#define	XSI_IMAGE_FX_SCALING_TYPE		7
#define	XSI_IMAGE_FX_SCALE_X			8
#define	XSI_IMAGE_FX_SCALE_Y			9
#define	XSI_IMAGE_FX_FLIP_HORIZONTAL	10
#define	XSI_IMAGE_FX_FLIP_VERTICAL		11
#define	XSI_IMAGE_FX_RGBA_2_GREYSCALE	12
#define	XSI_IMAGE_FX_8_BITS_2_16_BITS	13
#define	XSI_IMAGE_FX_NUM_PARAMS			14

#define SI_LIGHT_INFO_FALLOFF_ACTIVE	0
#define SI_LIGHT_INFO_MODE				1
#define SI_LIGHT_INFO_START				2
#define SI_LIGHT_INFO_END				3
#define SI_LIGHT_INFO_SHADOWS_ACTIVE	4
#define SI_LIGHT_INFO_UMBRA				5
#define SI_LIGHT_INFO_LIGHT_AS_ENERGY	6
#define SI_LIGHT_INFO_FACTOR			7
#define SI_LIGHT_INFO_INTENSITY			8
#define	SI_LIGHT_INFO_NUM_PARAMS		9

#define	XSI_MATERIAL_INFO_U_WRAP		0
#define	XSI_MATERIAL_INFO_V_WRAP		1
#define	XSI_MATERIAL_INFO_NUM_PARAMS	2

#define	XSI_CUSTOM_PARAM_INFO_MIN_VALUE		0
#define	XSI_CUSTOM_PARAM_INFO_MAX_VALUE		1
#define	XSI_CUSTOM_PARAM_INFO_CAPABILITIES	2
#define	XSI_CUSTOM_PARAM_INFO_NUM_PARAMS	3

#define	XSI_USERDATA_LIST_NUM_ENTRIES		0
#define	XSI_USERDATA_LIST_LITTLE_ENDIAN  	1
#define	XSI_USERDATA_LIST_NUM_PARAMS		2

#define	XSI_USERDATA_SIZE					0
#define	XSI_USERDATA_NUM_ENTITIES			1
#define	XSI_USERDATA_DATA_STREAM			2
#define	XSI_USERDATA_ENTITIES				3
#define	XSI_USERDATA_NUM_PARAMS				4

#define	XSI_FXTREE_NUM_ENTITIES				0
#define	XSI_FXTREE_NUM_PARAMS				1

#define XSI_FXOPERATOR_NAME					0
#define	XSI_FXOPERATOR_OUTPUT_TYPE			1
#define	XSI_FXOPERATOR_NUMBER_PARAMS		2
#define	XSI_FXOPERATOR_NUM_CONNECTIONS		3
#define	XSI_FXOPERATOR_NUM_PARAMS			4

#define	XSI_CLUSTERINFO_TYPE				0
#define	XSI_CLUSTERINFO_NUM_PARAMS			1

//***************************************************************************************
// Registration
//***************************************************************************************

extern	TemplateCreation	RegistrationTable36[];

/*! \addtogroup regfunc_36 Registration functions for dotXSI 3.6
*  @{
*/

/*! \xx ftk_XSI_ImageLibrary XSI_ImageLibrary \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_XSI_ImageLibrary XSI_ImageLibrary \endxx template
*/
CdotXSITemplate*	Register_XSI_ImageLibrary();

/*! \xx ftk_XSI_NurbsProjection XSI_NurbsProjection \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_XSI_NurbsProjection XSI_NurbsProjection \endxx template
*/
CdotXSITemplate*	Register_XSI_NurbsProjection();

/*! \xx ftk_XSI_NurbsTrim XSI_NurbsTrim \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_XSI_NurbsTrim XSI_NurbsTrim \endxx template
*/
CdotXSITemplate*	Register_XSI_NurbsTrim();

/*! \xx ftk_XSI_Image XSI_Image \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_XSI_Image XSI_Image \endxx template
*/
CdotXSITemplate*	Register_XSI_Image();

/*! \xx ftk_XSI_ImageData XSI_ImageData \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_XSI_ImageData XSI_ImageData \endxx template
*/
CdotXSITemplate*	Register_XSI_ImageData();

/*! \xx ftk_XSI_ImageFX XSI_ImageFX \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_XSI_ImageFX XSI_ImageFX \endxx template
*/
CdotXSITemplate*	Register_XSI_ImageFX();

/*! \xx ftk_SI_LightInfo SI_LightInfo \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_SI_LightInfo SI_LightInfo \endxx template
*/
CdotXSITemplate*	Register_SI_LightInfo();

/*! \xx ftk_XSI_MaterialInfo XSI_MaterialInfo \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_XSI_MaterialInfo XSI_MaterialInfo \endxx template
*/
CdotXSITemplate*	Register_XSI_MaterialInfo();

/*! \xx ftk_XSI_CustomParamInfo XSI_CustomParamInfo \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_XSI_CustomParamInfo XSI_CustomParamInfo \endxx template
*/
CdotXSITemplate*	Register_XSI_CustomParamInfo();

/*! \xx ftk_XSI_UserDataList XSI_UserDataList \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_XSI_UserDataList XSI_UserDataList \endxx template
*/
CdotXSITemplate*	Register_XSI_UserDataList();

/*! \xx ftk_XSI_UserData XSI_UserData \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_XSI_UserData XSI_UserData \endxx template
*/
CdotXSITemplate*	Register_XSI_UserData();

/*! \xx ftk_XSI_FxTree XSI_FxTree \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_XSI_FxTree XSI_FxTree \endxx template
*/
CdotXSITemplate*	Register_XSI_FxTree();

/*! \xx ftk_XSI_FxOperator XSI_FxOperator \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_XSI_FxOperator XSI_FxOperator \endxx template
*/
CdotXSITemplate*	Register_XSI_FxOperator();

/*! \xx ftk_XSI_ClusterInfo XSI_ClusterInfo \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_XSI_ClusterInfo XSI_ClusterInfo \endxx template
*/
CdotXSITemplate*	Register_XSI_ClusterInfo();

/*! @} */

#endif
