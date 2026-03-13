//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file Ambience.h
	\brief Defines the CSLAmbience class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _AMBIENCE_H
#define _AMBIENCE_H

#include "Template.h"

/*! \brief This class represents the \xx ftk_SI_Ambience SI_Ambience \endxx template.

	Describes the ambient color for the scene (see the \xx ftk_SI_Ambience SI_Ambience \endxx
	template reference).  You can retrieve ambience color information with the CSLScene::Ambience() method.
	\sa CSLScene
*/
class XSIEXPORT CSLAmbience
    : public CSLTemplate
{
public:
    /*!	Constructor
		\param[in] in_pScene Pointer to the scene containing the CSLAmbience
		\param[in] in_pModel Pointer to the model containing the CSLAmbience
		\param[in] in_pTemplate Pointer to the CdotXSITemplate that defines the CSLAmbience
	*/
	CSLAmbience(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
    virtual ~CSLAmbience();

	/*!	Returns the scene's ambient color.
		\return Color representing this object.
	*/
    CSIBCColorf GetColor();

	/*!	Changes the scene's ambient color.
		\param[in] in_rColor a CSIBCColorf containing the new ambient color.
	*/
	SI_Void SetColor(CSIBCColorf &in_rColor);

	/*! Returns the type of this template
		\retval CSLTemplate::SI_AMBIENCE Template type
	*/
	virtual ETemplateType Type();

	CSLAnimatableType* ParameterFromName(SI_Char *in_szName);
    CSLAnimatableType* ParameterFromType(EFCurveType in_Type, SI_Char *in_szParameterName);

	CSLColorRGBProxy*	GetColorProxy() { return &m_Color;};


private:
    CSLColorRGBProxy m_Color;

	void *m_pReserved;	// reserved for future extension
};

#endif
