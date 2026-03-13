//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file Extrapolation.h
	\brief Defines the CSLExtrapolation class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _EXTRAPOLATION_H
#define _EXTRAPOLATION_H

#include "Template.h"

/*! brief This class represents an \xx ftk_XSI_Extrapolation XSI_Extrapolation \endxx template.

	Determines how an action clip (CSLActionClip) contributes to the animation outside of
	the frames on which it is defined (see the \xx ftk_XSI_Extrapolation XSI_Extrapolation \endxx
	template reference).  You can create an instance of this class with the
	CSLTimeControl::CreateExtrapolation method.
	\note CSLExtrapolation is not supported by SI3D
	\sa CSLActionClip
	\sa CSLTimeControl
*/
class XSIEXPORT CSLExtrapolation
    : public CSLTemplate
{
public:

	/*! Defines the type of extrapolation to perform
	*/
	enum EExtrapolationType
	{
		SI_NO_CONTRIBUTION,		//!< Results in no extrapolation. Use this to delete an extrapolation.
		SI_HOLD,				//!< Results in the first or last values being held for the number of frames specified by CSLExtrapolation::GetValue.
		SI_CYCLE,				//!< Repeats the clip for the number of times specified by CSLExtrapolation::GetValue.
		SI_BOUNCE,				//!< Repeats the clip forward, then backward, and so on for the number of times specified by CSLExtrapolation::GetValue.
	};

	/*! Constructor
		\param[in] in_pScene The scene containing this template
		\param[in] in_pModel The parent model containing this template
		\param[in] in_pTemplate The actual template the defines the extrapolation type
		\param[in] in_Type Default extrapolation type to use
	*/
	CSLExtrapolation
	(
		CSLScene* in_pScene,
		CSLModel* in_pModel,
		CdotXSITemplate* in_pTemplate,
		EExtrapolationType in_Type = CSLExtrapolation::SI_NO_CONTRIBUTION
	);

    virtual ~CSLExtrapolation();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_EXTRAPOLATION Template type
	*/
	CSLTemplate::ETemplateType Type(){ return CSLTemplate::XSI_EXTRAPOLATION; }

	/*! Returns the extrapolation type
		\return Type of extrapolation
	*/
	EExtrapolationType GetExtrapolationType();

	/*! Sets the extrapolation type
		\param[in] in_Type New type of extrapolation
	*/
	SI_Void SetExtrapolationType( CSLExtrapolation::EExtrapolationType in_Type );

	/*! Returns the extrapolation value
		\note The meaning of the value changes according to the extrapolation type
		\return Extrapolation value
		\sa CSLExtrapolation::EExtrapolationType
	*/

	SI_Float GetValue();

	/*! Sets the extrapolation value
		\note The meaning of the value changes according to the extrapolation type.
		\param[in] in_fValue New extrapolation value
		\sa CSLExtrapolation::EExtrapolationType
	*/
	SI_Void SetValue( SI_Float in_fValue );

	CSLFloatProxy*	GetValueProxy() { return &m_Value; };

private:
    CSLStrEnumProxy<EExtrapolationType, SI_BOUNCE> m_ExtrapolationType;
    CSLFloatProxy m_Value;

	SI_Void* m_pReserved;
};

#endif
