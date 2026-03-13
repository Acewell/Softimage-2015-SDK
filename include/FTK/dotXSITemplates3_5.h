//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file dotXSITemplates3_5.h
	\brief Defines the registration functions for dotXSI 3.5

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef	DOTXSI_35_DEFINED
#define	DOTXSI_35_DEFINED
#include "dotXSITemplate.h"
#include "dotXSITemplates3_0.h"

//***************************************************************************************
// Defines
//***************************************************************************************
#define XSI_MATERIAL_NB_CONNECTIONS		0
#define XSI_MATERIAL_NUM_PARAMS			1

#define XSI_SHADER_PROGID				0
#define XSI_SHADER_OUTPUT_TYPE			1
#define XSI_SHADER_NB_PARAMETERS		2
#define XSI_SHADER_NB_CONNECTIONS		3
#define XSI_SHADER_NUM_PARAMS			4

#define XSI_SHADER_INSTANCE_TARGET				0
#define XSI_SHADER_INSTANCE_NB_PARAMETERS		1
#define XSI_SHADER_INSTANCE_DATA_NUM_PARAMS		2

//***************************************************************************************
// Registration
//***************************************************************************************
extern	TemplateCreation	RegistrationTable35[];

/*! \addtogroup regfunc_35 Registration functions for dotXSI 3.5
*  @{
*/


/*! \xx ftk_SI_Shape SI_Shape \endxx template registration function for dotXSI 3.5
\return an instance of CdotXSITemplate that supports the \xx ftk_SI_Shape SI_Shape \endxx template
	when using dotXSI 3.5
*/
CdotXSITemplate*	Register_SI_Shape35();

/*! \xx ftk_SI_PolygonList SI_PolygonList \endxx template registration function for dotXSI 3.5
\return an instance of CdotXSITemplate that supports the \xx ftk_SI_PolygonList SI_PolygonList \endxx template
	when using dotXSI 3.5
*/
CdotXSITemplate*	Register_SI_PolygonList35();

/*! \xx ftk_SI_TriangleList SI_TriangleList \endxx template registration function for dotXSI 3.5
\return an instance of CdotXSITemplate that supports the \xx ftk_SI_TriangleList SI_TriangleList \endxx template
	when using dotXSI 3.5
*/
CdotXSITemplate*	Register_SI_TriangleList35();

/*! \xx ftk_SI_TriStrip SI_TriStrip \endxx template registration function for dotXSI 3.5
\return an instance of CdotXSITemplate that supports the \xx ftk_SI_TriStrip SI_TriStrip \endxx template
	when using dotXSI 3.5
*/
CdotXSITemplate*	Register_SI_TriStrip35();

/*! \xx ftk_XSI_Material XSI_Material \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_XSI_Material XSI_Material \endxx template
*/
CdotXSITemplate*	Register_XSI_Material();

/*! \xx ftk_XSI_Shader XSI_Shader \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_XSI_Shader XSI_Shader \endxx template
*/
CdotXSITemplate*	Register_XSI_Shader();

/*! \xx ftk_XSI_ShaderInstanceData XSI_ShaderInstanceData \endxx template registration function
\return an instance of CdotXSITemplate that supports the \xx ftk_XSI_ShaderInstanceData XSI_ShaderInstanceData \endxx template
*/
CdotXSITemplate*	Register_XSI_ShaderInstanceData();

/*! @} */
#endif
