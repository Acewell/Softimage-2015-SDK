//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file Visibility.h
	\brief Defines the CSLVisibility class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _VISIBILITY_H
#define _VISIBILITY_H

#include "Template.h"

/*! \brief This class represents an \xx ftk_SI_Visibility SI_Visibility \endxx template.

	Describes the visibility of a model (see the \xx ftk_SI_Visibility SI_Visibility \endxx
	template reference). The Visibility of a model can be switched on and off using this template.
*/
class XSIEXPORT CSLVisibility
    : public CSLTemplate
{
public:
    CSLVisibility(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
    virtual ~CSLVisibility();

	/*!	Returns the visibility value.
		\return Visibility value.
	*/
	SI_Bool GetVisibility();

	/*!	Changes the visibility value.
		\param[in]	in_rValue	New visibility value.
	*/
	SI_Void SetVisibility(SI_Bool in_rValue);

	CSLBoolProxy*	GetVisibilityProxy() { return &m_Visiblility;};

    virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);
    virtual CSLAnimatableType* ParameterFromType(EFCurveType in_Type, SI_Char *in_szParameterName);

    /*! Returns the type of this template
    	\retval CSLTemplate::SI_VISIBILITY Template type
    */
    virtual ETemplateType Type();

private:
    CSLBoolProxy m_Visiblility;

	void *m_pReserved;	// reserved for future extension
};

#endif
