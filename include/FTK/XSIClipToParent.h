//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSIClipToParent.h
	\brief Defines the CSLFileInfo class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _XSICLIPTOPARENT_H
#define _XSICLIPTOPARENT_H

#include "Template.h"

/*! \brief This class represents an \xx ftk_XSI_ClipToParent XSI_ClipToParent \endxx template.

	Base class to define clip to parent properties for dotXSI 5.0+ (see the \xx ftk_XSI_ClipToParent XSI_ClipToParent \endxx
	template reference).
*/
class XSIEXPORT CSLXSIClipToParent
    : public CSLTemplate
{
public:
	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Referred template
	*/
	CSLXSIClipToParent(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	//! Destructor
	virtual ~CSLXSIClipToParent();

    virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);

	virtual CSLAnimatableType* ParameterFromType(EFCurveType in_Type, SI_Char *in_szParameterName);

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_CLIP_TO_PARENT Template type
	*/
	CSLTemplate::ETemplateType Type(){ return CSLTemplate::XSI_CLIP_TO_PARENT; }

	/*! Returns the Start value
		\return Start
	*/
	SI_Bool GetStart();

	/*! Sets the Start value
		\param[in]	in_bValue	new Start value
	*/
	SI_Void SetStart( SI_Bool in_bValue );

    CSLBoolProxy* 	GetStartProxy() { return &m_Start; };

	/*! Returns the End value
		\return End
	*/
	SI_Bool GetEnd();

	/*! Sets the End value
		\param[in]	in_bValue	new End value
	*/
	SI_Void SetEnd( SI_Bool in_bValue );

    CSLBoolProxy* 	GetEndProxy() { return &m_End; };

private:
    CSLBoolProxy	m_Start;
    CSLBoolProxy	m_End;

	SI_Void			*m_pReserved;
};

#endif
