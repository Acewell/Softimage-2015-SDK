//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file dotXSINativeTemplateReadWrite3_5.h
	\brief Defines non-generic read/write functions for dotXSI 3.5

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef	DOTXSIRW_35_DEFINED
#define	DOTXSIRW_35_DEFINED

#include "XSIParser.h"
#include "dotXSIDefines.h"

/*! \addtogroup rwfunc_35 Non-generic read/write functions for dotXSI 3.5
*  @{
*/

/*! Reading callback for \xx ftk_SI_Shape SI_Shape \endxx in dotXSI 3.5
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_ReadShape35(			CXSIParser			*i_pParser,
										CdotXSITemplate		*i_pCurrentTemplate,
										CdotXSITemplate		*i_pNewTemplate );

/*! Writing callback for \xx ftk_SI_Shape SI_Shape \endxx in dotXSI 3.5
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\param i_nLevel the level of recursion (used to write tabs in ascii format)
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_WriteShape35(			CXSIParser			*i_pParser,
										CdotXSITemplate		*i_pCurrentTemplate,
										CdotXSITemplate		*i_pNewTemplate,
										SI_Int				i_nLevel );

/*! Reading callback for \xx ftk_SI_PolygonList SI_PolygonList \endxx in dotXSI 3.5
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_ReadPolygonList35(	CXSIParser			*i_pParser,
										CdotXSITemplate		*i_pCurrentTemplate,
										CdotXSITemplate		*i_pNewTemplate );

/*! Writing callback for \xx ftk_SI_PolygonList SI_PolygonList \endxx in dotXSI 3.5
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\param i_nLevel the level of recursion (used to write tabs in ascii format)
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_WritePolygonList35(	CXSIParser			*i_pParser,
										CdotXSITemplate		*i_pCurrentTemplate,
										CdotXSITemplate		*i_pNewTemplate,
										SI_Int				i_nLevel );

/*! Reading callback for \xx ftk_SI_TriangleList SI_TriangleList \endxx in dotXSI 3.5
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_ReadTriangleList35(	CXSIParser			*i_pParser,
										CdotXSITemplate		*i_pCurrentTemplate,
										CdotXSITemplate		*i_pNewTemplate );

/*! Writing callback for \xx ftk_SI_TriangleList SI_TriangleList \endxx in dotXSI 3.5
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\param i_nLevel the level of recursion (used to write tabs in ascii format)
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_WriteTriangleList35(	CXSIParser			*i_pParser,
										CdotXSITemplate		*i_pCurrentTemplate,
										CdotXSITemplate		*i_pNewTemplate,
										SI_Int				i_nLevel );

/*! Reading callback for \xx ftk_SI_TriStrip SI_TriStrip \endxx in dotXSI 3.5
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_ReadTriStrip35(		CXSIParser			*i_pParser,
										CdotXSITemplate		*i_pCurrentTemplate,
										CdotXSITemplate		*i_pNewTemplate );

/*! Writing callback for \xx ftk_SI_TriStrip SI_TriStrip \endxx in dotXSI 3.5
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\param i_nLevel the level of recursion (used to write tabs in ascii format)
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_WriteTriStrip35(		CXSIParser			*i_pParser,
										CdotXSITemplate		*i_pCurrentTemplate,
										CdotXSITemplate		*i_pNewTemplate,
										SI_Int				i_nLevel );

/*! Reading callback for \xx ftk_XSI_Material XSI_Material \endxx
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_ReadXSI_Material(		CXSIParser			*i_pParser,
										CdotXSITemplate		*i_pCurrentTemplate,
										CdotXSITemplate		*i_pNewTemplate );

/*! Writing callback for \xx ftk_XSI_Material XSI_Material \endxx
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\param i_nLevel the level of recursion (used to write tabs in ascii format)
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_WriteXSI_Material(	CXSIParser			*i_pParser,
										CdotXSITemplate		*i_pCurrentTemplate,
										CdotXSITemplate		*i_pNewTemplate,
										SI_Int				i_nLevel );

/*! Reading callback for \xx ftk_XSI_Shader XSI_Shader \endxx
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_ReadXSI_Shader(		CXSIParser			*i_pParser,
										CdotXSITemplate		*i_pCurrentTemplate,
										CdotXSITemplate		*i_pNewTemplate );

/*! Writing callback for \xx ftk_XSI_Shader XSI_Shader \endxx
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\param i_nLevel the level of recursion (used to write tabs in ascii format)
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_WriteXSI_Shader(		CXSIParser			*i_pParser,
										CdotXSITemplate		*i_pCurrentTemplate,
										CdotXSITemplate		*i_pNewTemplate,
										SI_Int				i_nLevel );

/*! Reading callback for \xx ftk_XSI_ShaderInstanceData XSI_ShaderInstanceData \endxx
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_ReadXSI_ShaderInstanceData(	CXSIParser			*i_pParser,
												CdotXSITemplate		*i_pCurrentTemplate,
												CdotXSITemplate		*i_pNewTemplate );

/*! SI_SUCESS callback for \xx ftk_XSI_ShaderInstanceData XSI_ShaderInstanceData \endxx
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\param i_nLevel the level of recursion (used to write tabs in ascii format)
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_WriteXSI_ShaderInstanceData(	CXSIParser			*i_pParser,
												CdotXSITemplate		*i_pCurrentTemplate,
												CdotXSITemplate		*i_pNewTemplate,
												SI_Int				i_nLevel );

/*! @} */
#endif //DOTXSIRW_35_DEFINED
