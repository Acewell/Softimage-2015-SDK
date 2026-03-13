//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file dotXSINativeTemplateReadWrite5_0.h
	\brief Defines non-generic read/write functions for dotXSI 5.0

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef	DOTXSIRW_50_DEFINED
#define	DOTXSIRW_50_DEFINED

#include "XSIParser.h"
#include "dotXSIDefines.h"
#include "dotXSINativeTemplateReadWrite3_5.h"
#include "dotXSINativeTemplateReadWrite3_6.h"

/*! \addtogroup rwfunc_50 Non-generic read/write functions for dotXSI 5.0
*  @{
*/

/*! Reading callback for \xx ftk_XSI_SubComponentAttributeList XSI_SubComponentAttributeList \endxx
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_ReadXSI_SubComponentAttributeList(	CXSIParser			*i_pParser,
														CdotXSITemplate		*i_pCurrentTemplate,
														CdotXSITemplate		*i_pNewTemplate );

/*! Writing callback for \xx ftk_XSI_SubComponentAttributeList XSI_SubComponentAttributeList \endxx
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\param i_nLevel the level of recursion (used to write tabs in ascii format)
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_WriteXSI_SubComponentAttributeList(	CXSIParser			*i_pParser,
														CdotXSITemplate		*i_pCurrentTemplate,
														CdotXSITemplate		*i_pNewTemplate,
														SI_Int				i_nLevel );

/*! Reading callback for \xx ftk_XSI_VertexList XSI_VertexList \endxx
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_ReadXSI_VertexList(	CXSIParser			*i_pParser,
										CdotXSITemplate		*i_pCurrentTemplate,
										CdotXSITemplate		*i_pNewTemplate );

/*! Writing callback for \xx ftk_XSI_VertexList XSI_VertexList \endxx
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\param i_nLevel the level of recursion (used to write tabs in ascii format)
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_WriteXSI_VertexList(	CXSIParser			*i_pParser,
										CdotXSITemplate		*i_pCurrentTemplate,
										CdotXSITemplate		*i_pNewTemplate,
										SI_Int				i_nLevel );


/*! Reading callback for \xx ftk_XSI_TriangleList XSI_TriangleList \endxx
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_ReadXSI_TriangleList(	CXSIParser			*i_pParser,
										CdotXSITemplate		*i_pCurrentTemplate,
										CdotXSITemplate		*i_pNewTemplate );

/*! Writing callback for \xx ftk_XSI_TriangleList XSI_TriangleList \endxx
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\param i_nLevel the level of recursion (used to write tabs in ascii format)
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_WriteXSI_TriangleList(	CXSIParser			*i_pParser,
											CdotXSITemplate		*i_pCurrentTemplate,
											CdotXSITemplate		*i_pNewTemplate,
											SI_Int				i_nLevel );


/*! Reading callback for \xx ftk_XSI_PolygonList XSI_PolygonList \endxx
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_ReadXSI_PolygonList(	CXSIParser			*i_pParser,
										CdotXSITemplate		*i_pCurrentTemplate,
										CdotXSITemplate		*i_pNewTemplate );

/*! Writing callback for \xx ftk_XSI_PolygonList XSI_PolygonList \endxx
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\param i_nLevel the level of recursion (used to write tabs in ascii format)
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_WriteXSI_PolygonList(	CXSIParser			*i_pParser,
										CdotXSITemplate		*i_pCurrentTemplate,
										CdotXSITemplate		*i_pNewTemplate,
										SI_Int				i_nLevel );


/*! Reading callback for \xx ftk_XSI_TriangleStripList XSI_TriangleStripList \endxx
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_ReadXSI_TriangleStripList(	CXSIParser			*i_pParser,
												CdotXSITemplate		*i_pCurrentTemplate,
												CdotXSITemplate		*i_pNewTemplate );

/*! Writing callback for \xx ftk_XSI_TriangleStripList XSI_TriangleStripList \endxx
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\param i_nLevel the level of recursion (used to write tabs in ascii format)
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_WriteXSI_TriangleStripList(	CXSIParser			*i_pParser,
												CdotXSITemplate		*i_pCurrentTemplate,
												CdotXSITemplate		*i_pNewTemplate,
												SI_Int				i_nLevel );


/*! Reading callback for \xx ftk_XSI_UserDataBlob XSI_UserDataBlob \endxx
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_ReadXSI_UserDataBlob(	CXSIParser			*i_pParser,
												CdotXSITemplate		*i_pCurrentTemplate,
												CdotXSITemplate		*i_pNewTemplate );

/*! Writing callback for \xx ftk_XSI_UserDataBlob XSI_UserDataBlob \endxx
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\param i_nLevel the level of recursion (used to write tabs in ascii format)
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_WriteXSI_UserDataBlob(	CXSIParser			*i_pParser,
												CdotXSITemplate		*i_pCurrentTemplate,
												CdotXSITemplate		*i_pNewTemplate,
												SI_Int				i_nLevel );

/*! Reading callback for \xx ftk_XSI_CustomPSet XSI_CustomPSet \endxx
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_ReadXSI_CustomPSet50(	CXSIParser			*i_pParser,
												CdotXSITemplate		*i_pCurrentTemplate,
												CdotXSITemplate		*i_pNewTemplate );

/*! Writing callback for \xx ftk_XSI_CustomPSet XSI_CustomPSet \endxx
\param i_pParser a pointer to the parser that calls this function
\param i_pCurrentTemplate a pointer to the current template
\param i_pNewTemplate a pointer to the new template
\param i_nLevel the level of recursion (used to write tabs in ascii format)
\return SI_Error::SI_SUCCESS the read has been successful
\return SI_Error::SI_ERR_ERROR_MSG the read has failed
*/
SI_Error dotXSICB_WriteXSI_CustomPSet50(	CXSIParser			*i_pParser,
												CdotXSITemplate		*i_pCurrentTemplate,
												CdotXSITemplate		*i_pNewTemplate,
												SI_Int				i_nLevel );
/*! @} */
#endif // DOTXSIRW_50_DEFINED