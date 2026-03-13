//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file ActionFCurve.h
	\brief Defines the CSLActionFCurve class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _ACTIONFCURVE_H
#define _ACTIONFCURVE_H

#include "BaseFCurve.h"

/*! \brief This class represents an \xx ftk_SI_FCurve SI_FCurve \endxx template.

	Wraps all functionality for an FCurve used in a mixer.
	\sa CSLMixer
	\sa CSLAction
*/
class XSIEXPORT CSLActionFCurve
    : public CSLBaseFCurve
{
public:

	/*! Constructor
		\param[in] in_pScene	Pointer to the scene containing the ActionFCurve
		\param[in] in_pModel	Pointer to the model containing the ActionFCurve
		\param[in] in_pTemplate	Pointer to the CdotXSITemplate containing the ActionFCurve
		\param[in] in_InterpolationType	FCurve interpolation type
	*/
    CSLActionFCurve(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate, EFCurveInterpolationType in_InterpolationType);

	virtual ~CSLActionFCurve();

	/*! Returns the Softimage path of the animated parameter
		\return The Softimage Path of the animated parameter
	*/
	SI_Char* GetParameterXSIPath();

	/*! Sets the Softimage path of the animated parameter
		\param[in] in_szPath The Softimage Path of the animated parameter
	*/
	SI_Void SetParameterXSIPath( SI_Char *in_szPath );

	/*! Synchronizes internal data to be coherent with the IO layer
		\return success or failure
	*/
	virtual SI_Error Synchronize();

	/*! Returns the type of this template
		\retval CSLTemplate::SI_ACTION_FCURVE Template type
	*/
    ETemplateType Type() { return SI_ACTION_FCURVE; }

	/*! Sets Parameter
		\param[in] in_pParameter Pointer to the parameter to use
	*/
	SI_Void SetParameter( CSLAnimatableType *in_pParameter );

	/*! Returns the active flag
		\return The active state of the fcurve
	*/
	SI_Bool GetActive();

	/*! Sets the active flag
		\param[in] in_bNew The new active state of the fcurve
	*/
	SI_Void SetActive( SI_Bool in_bNew );

	CSLStringProxy*		GetXSIPath() {return &m_XSIPath;};

private:
    CSLStringProxy m_XSIPath;
	SI_Bool m_bActive;

	SI_Void *m_pReserved;
};

#endif
