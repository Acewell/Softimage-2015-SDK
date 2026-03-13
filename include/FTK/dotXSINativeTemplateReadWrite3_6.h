//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file dotXSINativeTemplateReadWrite3_6.h
	\brief Defines non-generic read/write functions for dotXSI 3.6

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef	DOTXSIRW_36_DEFINED
#define	DOTXSIRW_36_DEFINED

#include "XSIParser.h"
#include "dotXSIDefines.h"
#include "dotXSINativeTemplateReadWrite3_5.h"


/*! \addtogroup rwfunc_36 Non-generic read/write functions for dotXSI 3.6
*  @{
*/

/*! Reading callback for \xx ftk_XSI_UserData XSI_UserData \endxx
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_ReadUserData(			CXSIParser			*i_pParser,
										CdotXSITemplate		*i_pCurrentTemplate,
										CdotXSITemplate		*i_pNewTemplate );

/*! Writing callback for \xx ftk_XSI_UserData XSI_UserData \endxx
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\param i_nLevel the level of recursion (used to write tabs in ascii format)
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_WriteUserData(		CXSIParser			*i_pParser,
										CdotXSITemplate		*i_pCurrentTemplate,
										CdotXSITemplate		*i_pNewTemplate,
										SI_Int				i_nLevel );

/*! Reading callback for \xx ftk_XSI_ImageData XSI_ImageData \endxx
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_ReadImageData(		CXSIParser			*i_pParser,
										CdotXSITemplate		*i_pCurrentTemplate,
										CdotXSITemplate		*i_pNewTemplate );

/*! Writing callback for \xx ftk_XSI_ImageData XSI_ImageData \endxx
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\param i_nLevel the level of recursion (used to write tabs in ascii format)
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_WriteImageData(		CXSIParser			*i_pParser,
										CdotXSITemplate		*i_pCurrentTemplate,
										CdotXSITemplate		*i_pNewTemplate,
										SI_Int				i_nLevel );

SI_Error dotXSICB_ReadCustomParamInfo(	CXSIParser			*i_pParser,
										CdotXSITemplate		*i_pCurrentTemplate,
										CdotXSITemplate		*i_pNewTemplate );

SI_Error dotXSICB_WriteCustomParamInfo(	CXSIParser			*i_pParser,
										CdotXSITemplate		*i_pCurrentTemplate,
										CdotXSITemplate		*i_pNewTemplate,
										SI_Int				i_nLevel );

/*! @} */
#endif //DOTXSIRW_36_DEFINED
