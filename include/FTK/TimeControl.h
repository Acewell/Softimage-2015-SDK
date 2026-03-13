//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file TimeControl.h
	\brief Defines the CSLTimeControl class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _TIMECONTROL_H
#define _TIMECONTROL_H

#include "Template.h"
#include "Extrapolation.h"
#include "XSIClipToParent.h"

/*! \brief This class represents an \xx ftk_XSI_TimeControl XSI_TimeControl \endxx template.

	Stores the clipping and offset parameters of an action clip (CSLActionClip--see the
	\xx ftk_XSI_TimeControl XSI_TimeControl \endxx template reference). You can add a CSLTimeControl
	with the CSLActionClip::AddTimeControl method.
	\note CSLTimeControl is not supported by SI3D.
	\sa CSLActionClip
	\sa CSLExtrapolation
*/
class XSIEXPORT CSLTimeControl
    : public CSLTemplate
{
public:

	//! Specifies where extrapolation occures while processing an CSLActionClip
	enum EExtrapolationPos
	{
		SI_BEFORE,	//!< Extrapolation performed \b before the CSLActionClip
		SI_AFTER	//!< Extrapolation performed \b after the CSLActionClip
	};

	/*! Constructor
		\param[in] in_pScene	Pointer to the scene containing the CSLTimeControl
		\param[in] in_pModel	Pointer to the model containing the CSLTimeControl
		\param[in] in_pTemplate	Pointer to the CdotXSITemplate containing the CSLTimeControl data
	*/
    CSLTimeControl(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
    virtual ~CSLTimeControl();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_TIMECONTROL Template type
	*/
	CSLTemplate::ETemplateType Type(){ return CSLTemplate::XSI_TIMECONTROL; }
	SI_Error Synchronize();

	/*! Returns the first frame of the source that is used by the clip.
		\return Frame number
	*/
	SI_Float GetIn();

	/*! Sets the first frame of the source that is used by the clip.
		\param[in] in_fNew Frame number
	*/
	SI_Void SetIn( SI_Float in_fNew );

	/*! Returns the last frame of the source that is used by the clip.
		\return Frame number
	*/
	SI_Float GetOut();

	/*! Sets the last frame of the source that is used by the clip.
		\param[in] in_fNew Frame number
	*/
	SI_Void SetOut( SI_Float in_fNew );

	/*! Returns the scaling of the clip in time.
		\return The scale value
	*/
	SI_Float GetScale();

	/*! Sets The scaling of the clip in time.
		\param[in] in_fNew Scale factor
		\note Increasing this value speeds up the relative time of the clip, decreasing the duration.
	*/
	SI_Void SetScale( SI_Float in_fNew );

	/*! Returns the frame where the clip starts in the local time of the CSLActionClip.
		\return The start offset
	*/
	SI_Float GetStartOffset();

	/*! Sets he frame where the clip starts in the local time of the CSLActionClip.
		\param[in] in_fNew The new start offset value
	*/
	SI_Void SetStartOffset( SI_Float in_fNew );

	// extrapolation functionality ////////////////////////////////////////////

	/*! Creates a new extrapolation and connect it
		\param[in] in_Pos Specifies where the extrapolation must be performed
		\param[in] in_Type Type of extrapolation to create
		\return Pointer to the newly created extrapolation or NULL if an extrapolation
			at \p in_Pos already exists.
	*/
    CSLExtrapolation* CreateExtrapolation( EExtrapolationPos in_Pos, CSLExtrapolation::EExtrapolationType in_Type = CSLExtrapolation::SI_NO_CONTRIBUTION );

	/*! Returns one of the extrapolation
		\param[in] in_Pos Specifies the extrapolation position to get
		\return Pointer to the requested extrapolation or NULL if there is no
			extrapolation at the requested position
	*/
	CSLExtrapolation* GetExtrapolation( EExtrapolationPos in_Pos );

	/*! Sets one of the extrapolation position
		\param[in] in_Pos The extrapolation position to set.
		\param[in] in_pExtrapolation The extrapolation to put at the requested position
		\warning This method overwrites any existing extrapolation and might cause
		leaks.  You either have to free previously allocated extrapolation or use
		the non-destructive CSLTimeControl::ConnectExtrapolation method instead.
		\sa CSLTimeControl::ConnectExtrapolation
	*/
	SI_Void SetExtrapolation( EExtrapolationPos in_Pos, CSLExtrapolation *in_pExtrapolation );

	/*! Sets one of the extrapolation values if not already set
		\param[in] in_Pos Specifies the extrapolation position to set
		\param[in] in_pExtrapolation Extrapolation to connect
		\sa CSLTimeControl::SetExtrapolation
	*/
	CSLExtrapolation* ConnectExtrapolation( EExtrapolationPos in_Pos, CSLExtrapolation* in_pExtrapolation );

	// ClipToParent functionality ////////////////////////////////////////////

	/*! Creates a new ClipToParent and connect it
		\return Pointer to the newly created ClipToParent or NULL if a
			ClipToParent already exists.
	*/
    CSLXSIClipToParent* CreateClipToParent();

	/*! Returns the ClipToParent
		\return Pointer to the ClipToParent or NULL if is none
	*/
	CSLXSIClipToParent* GetClipToParent();

	/*! Sets one of the extrapolation position
		\param[in] in_pXSIClipToParent The ClipToParent to set
		\warning This method overwrites existing ClipToParent and might cause
			leaks.  You either have to free the previously allocated ClipToParent or use
			the non-destructive CSLTimeControl::ConnectExtrapolation method instead.
		\sa CSLTimeControl::ConnectClipToParent
	*/
	SI_Void SetClipToParent( CSLXSIClipToParent *in_pXSIClipToParent );

	/*! Sets the ClipToParent values if not already set
		\param[in] in_pClipToParent ClipToParent to connect
		\sa CSLTimeControl::SetClipToParent
	*/
	CSLXSIClipToParent* ConnectClipToParent( CSLXSIClipToParent* in_pClipToParent );

private:
    CSLFloatProxy m_In;
    CSLFloatProxy m_Out;
    CSLFloatProxy m_StartOffset;
    CSLFloatProxy m_Scale;
    CSLExtrapolation* m_pExtrapolationBefore;
    CSLExtrapolation* m_pExtrapolationAfter;
	CSLXSIClipToParent* m_pClipToParent;
};

#endif
