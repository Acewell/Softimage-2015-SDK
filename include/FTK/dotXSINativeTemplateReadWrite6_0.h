//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file dotXSINativeTemplateReadWrite6_0.h
	\brief Defines non-generic read/write functions for dotXSI 6.0

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef	DOTXSIRW_60_DEFINED
#define	DOTXSIRW_60_DEFINED

#include "XSIParser.h"
#include "dotXSIDefines.h"
#include "dotXSINativeTemplateReadWrite3_5.h"
#include "dotXSINativeTemplateReadWrite3_6.h"
#include "dotXSINativeTemplateReadWrite5_0.h"

/*! \addtogroup rwfunc_60 Non-generic read/write functions for dotXSI 6.0
*  @{
*/

/*! Reading callback for \xx ftk_XSI_IndexList XSI_IndexList \endxx
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_ReadXSI_IndexList(	CXSIParser			*i_pParser,
														CdotXSITemplate		*i_pCurrentTemplate,
														CdotXSITemplate		*i_pNewTemplate );

/*! Writing callback for \xx ftk_XSI_IndexList XSI_IndexList \endxx
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\param i_nLevel the level of recursion (used to write tabs in ascii format)
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_WriteXSI_IndexList(	CXSIParser			*i_pParser,
														CdotXSITemplate		*i_pCurrentTemplate,
														CdotXSITemplate		*i_pNewTemplate,
														SI_Int				i_nLevel );

/*! @} */
#endif // DOTXSIRW_60_DEFINED