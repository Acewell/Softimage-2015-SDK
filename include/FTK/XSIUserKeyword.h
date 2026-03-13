//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSIUserKeyword.h
	\brief Defines the CSLXSIUserKeyword class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _XSIUSERKEYWORD_H
#define _XSIUSERKEYWORD_H

#include "Template.h"


/*! \brief This class represents an \xx ftk_XSI_UserKeyword XSI_UserKeyword \endxx template.

	Stores the list of user keywords for the Material and the Image Clip (see the
	\xx ftk_XSI_UserKeyword XSI_UserKeyword \endxx template reference).
	\since dotXSI 6.0
*/
class XSIEXPORT CSLXSIUserKeyword
    : public CSLTemplate
{
public:
	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Refered template
	*/
	CSLXSIUserKeyword(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	//! Destructor
	virtual ~CSLXSIUserKeyword();

	/*! Returns the type of this template
		\return CSLTemplate::XSI_USER_KEYWORD The type of this template
	*/
	ETemplateType Type(){ return XSI_USER_KEYWORD; }

	/*! Returns the user keyword string list
		\return UserKeyword
	*/
    SI_Char* GetList();

	/*! Sets the user keyword string list value
		\param[in]	in_pValue	new UserKeyword value
	*/
	SI_Void SetList( SI_Char* in_pValue);

    CSLStringProxy* 									GetListProxy() { return &m_List; };

private:
    CSLStringProxy	m_List;

	SI_Void *m_pReserved;
};

#endif
