//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSINurbsTrimList.h
	\brief Defines the CSLNurbsTrim class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _XSINURBSTRIMLIST_H
#define _XSINURBSTRIMLIST_H

#include "Template.h"

class CSLCurveList;

/*! \brief This class represents an \xx ftk_XSI_NurbsTrim XSI_NurbsTrim \endxx template.

	Describes a Nurbs Trim List (see the \xx ftk_XSI_NurbsTrim XSI_NurbsTrim \endxx template reference).
	\sa CSLCurveList
	\since dotXSI 3.6
*/
class XSIEXPORT CSLNurbsTrim
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
		\return Whether or not commit was a success
	*/
	SI_Error Synchronize();

    /*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Refered template
	*/
    CSLNurbsTrim(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	//! Destructor
	virtual ~CSLNurbsTrim();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_NURBS_TRIM_LIST The type of this template
	*/
	ETemplateType Type(){ return XSI_NURBS_TRIM; }

	/*! Returns the boundary flag
		\return The type of boundary
	*/
	SI_Bool GetBoundaryFlag();

	/*! Sets the boundary flag
		\param[in] in_Flag The type of boundary
	*/
	SI_Void SetBoundaryFlag( SI_Bool in_Flag );

	/*! Returns the projection type
		\return The type of projection
	*/
	EProjectionType GetProjectionType();

	/*! Sets the projection type
		\param[in] in_Type The type of projection
	*/
	SI_Void SetProjectionType( EProjectionType in_Type );


	///////////////////////////////////////////////////////////////////////////
	// Trim Functionality /////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	/*!	Returns the curve list describing this trim.
		\return Pointer to a curve list object.
	*/
	CSLCurveList* CurveList() { return m_pTrimCurveList; };

	// Connection functions
	CSLCurveList* ConnectCurveList(CSLCurveList*);
	virtual SI_Error Fix();

private:
    CSLCurveList*	m_pTrimCurveList;
    CSLBoolProxy	m_Boundary;
    CSLEnumProxy<EProjectionType, SI_WORLD> m_Projection;

	SI_Void *m_pReserved;
};

#endif
