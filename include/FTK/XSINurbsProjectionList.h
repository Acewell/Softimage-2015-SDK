//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSINurbsProjectionList.h
	\brief Defines the CSLNurbsProjection class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _XSINURBSPROJECTIONLIST_H
#define _XSINURBSPROJECTIONLIST_H

#include "Template.h"

class CSLCurveList;

/*! \brief This class represents an \xx ftk_XSI_NurbsProjection XSI_NurbsProjection \endxx template.

	Describes a Nurbs Projection List (see the \xx ftk_XSI_NurbsProjection XSI_NurbsProjection \endxx template reference).
	\sa CSLCurveList
	\since dotXSI 3.6
*/
class XSIEXPORT CSLNurbsProjection
    : public CSLTemplate
{
public:
	//! Define projection types
	enum EProjectionType
	{
		SI_UV,		/*!< UV Space */
		SI_WORLD	/*!< World Space */
	};

	/*! Commits semantic layer data
		\return SI_Error Whether or not commit was a success
	*/
	SI_Error Synchronize();

	SI_Error Fix();

    /*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Refered template
	*/
    CSLNurbsProjection(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	//! Destructor
	virtual ~CSLNurbsProjection();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_NURBS_TRIM_LIST The type of this template
	*/
	ETemplateType Type(){ return XSI_NURBS_PROJECTION; }

	/*! Returns the projection type
		\return EProjectionType The type of projection
	*/
	EProjectionType GetProjectionType();

	/*! Returns the projection type
		\param[in] in_Type The type of projection
	*/
	SI_Void SetProjectionType( EProjectionType in_Type );

	///////////////////////////////////////////////////////////////////////////
	// Projection Functionality /////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	/*!	Returns the curve list describing this projection.
		\return	CSLCurveList*	Pointer to a curve list object.
	*/
	CSLCurveList* CurveList();

	CSLCurveList* ConnectCurveList( CSLCurveList* in_pNewCurveList );

private:
    CSLCurveList* m_pProjCurveList;
    CSLEnumProxy<EProjectionType, SI_WORLD> m_Projection;

	SI_Void *m_pReserved;
};

#endif
