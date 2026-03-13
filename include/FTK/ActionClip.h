//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file ActionClip.h
	\brief Defines the CSLActionClip class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _ACTIONCLIP_H
#define _ACTIONCLIP_H

#include "Template.h"

// Forward declaration
class CSLTimeControl;
class CSLAction;

/*! This class represents an \xx ftk_XSI_ActionClip XSI_ActionClip \endxx template.

An action clip is an instance of an action source (CSLAction) that can be
used in an animation mixer (CSLMixer) track (CSLTrack) (see the
\xx ftk_XSI_ActionClip XSI_ActionClip \endxx template reference).  You can
create an action clip with the CSLTrack::AddActionClip method.

\note CSLActionClip is not supported by SI3D.

\sa CSLAction
\sa CSLMixer
\sa CSLTimeControl
\sa CSLTrack
*/
class XSIEXPORT CSLActionClip
    : public CSLTemplate
{
public:

	/*! Constructor
		\param[in] in_pScene	Pointer to the scene containing the ActionClip
		\param[in] in_pModel	Pointer to the model containing the ActionClip
		\param[in] in_pTemplate	Pointer to the CdotXSITemplate defining the ActionClip
	*/
    CSLActionClip(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	/*! Destructor
	*/
    virtual ~CSLActionClip();

	SI_Error Synchronize();

	/*! Returns the type of this template
		\return CSLTemplate::XSI_ACTIONCLIP Template type
	*/
	CSLTemplate::ETemplateType Type(){ return CSLTemplate::XSI_ACTIONCLIP; }

	/*! Returns the active flag that determines whether the clip contributes to the animation or not.
		\retval true The clip contributes to the animation
		\retval false The clip does \b not contribute to the animation
	*/
    SI_Bool GetActive();

	/*! Sets whether the clip contributes to the animation or not
		\param[in] in_bNew true to contribute, false otherwise
	*/
	SI_Void SetActive( SI_Bool in_bNew );

    /*! Returns the length of the clip
		\return Duration
	*/
	SI_Float GetDuration();

	/*! Sets the the length of the clip
		\param[in] in_fNew New Duration
	*/
	SI_Void SetDuration( SI_Float in_fNew );

	/*! Returns the fill action flag
		\retval true The clip is a fill action
		\retval false The clip is \b not a fill action
		\note Fill actions determine parameter values only when there is no
			non-fill action driving particular parameters. They can be used to
			set parameters to reference values between action clips. Fill
			actions are not mixed with other clips.
	*/
    SI_Bool GetFillAction();

	/*! Sets the fill action flag
		\param[in] in_bNew True to enable fill action, false otherwise
		\note Fill actions determine parameter values only when there is no
			non-fill action driving particular parameters. They can be used to
			set parameters to reference values between action clips. Fill
			actions are not mixed with other clips.
	*/
	SI_Void SetFillAction( SI_Bool in_bNew );

	/*! Returns the priority of the fill action
		\note If two fill actions drive the same parameter at a given frame,
			the one with the higher priority is used.
		\return Fill priority value
	*/
    SI_Int GetFillPriority();

	/*! Sets the priority of the fill action
		\note If two fill actions drive the same parameter at a given frame,
			the one with the higher priority is used.
		\param[in] in_nNew New fill priority value
	*/
	SI_Void SetFillPriority( SI_Int in_nNew );

	/*! Returns the start time of the clip
		\return Start time
	*/
	SI_Float GetStartTime();

	/*! Sets the start time of the clip
		\param[in] in_fNew New start time
	*/
	SI_Void SetStartTime( SI_Float in_fNew );

	/*! Returns the relative weight of the action clip when it is mixed with other clips that affect the same parameters or clusters at the same frames.
		\return Weight
	*/
	SI_Float GetWeight();

	/*! Sets the relative weight of the action clip when it is mixed with other clips that affect the same parameters or clusters at the same frames.
		\param[in] in_fNew New weight
	*/
	SI_Void SetWeight( SI_Float in_fNew );

	// action functionality ///////////////////////////////////////////////////

	/*! Returns the action source
		\return Pointer to the action source
		\return NULL No action source was set, this should never happen unless
			it was ovverriden by mistake by CSLActionClip::SetReference.
	*/
	CSLAction* GetReference();

	/*! Sets the action source
		\param[in] in_pAction Pointer to the new Referred action
		\note The internal action source pointer will be replaced by the one
			provided.  This is perfectly normal because there can/will be other
			CSLActionClips instanciating it.
	*/
	SI_Void SetReference( CSLAction* in_pAction );

	SI_Char* GetReferenceXSIPath();
	SI_Void SetReferenceXSIPath( SI_Char* in_szPath );

	// time control functionality /////////////////////////////////////////////

	/*! Add a new time control
		\return Pointer to the newly allocated time control
	*/
	CSLTimeControl* AddTimeControl();

	/*! Add a previously allocated time control
		\param[in] in_pTimeControl Pointer to the time control to add
		\return Pointer to added time control or null if already present
	*/
	CSLTimeControl* ConnectTimeControl( CSLTimeControl *in_pTimeControl );

	/*! Removes a specific time control
		\param[in] in_nIndex Index of the control to remove
		\retval SI_Error::SI_SUCCESS The element was removed
		\retval SI_Error::SI_ERR_BAD_ARGUMENT Invalid index
	*/
	SI_Error RemoveTimeControl( SI_Int in_nIndex );

	/*! Removes a specific time control
		\param[in] in_pTimeControl Pointer of the control to remove
		\retval SI_Error::SI_SUCCESS The element was removed
		\retval SI_Error::SI_ERR_BAD_ARGUMENT Could not find the element to remove
	*/
	SI_Error RemoveTimeControl( CSLTimeControl *in_pTimeControl );

	/*! Returns the list of all time controls
		\return Pointer to the list of time control pointers
	*/
	CSLTimeControl** GetTimeControlList();

	/*! Returns the time control count
		\return Number of time control in the list
	*/
	SI_Int GetTimeControlCount();

	/*! Frees all time controls
		\retval SI_Error::SI_SUCCESS
	*/
	SI_Error ClearTimeControls();


	CSLFloatProxy*		GetStartTimeProxy(){return &m_StartTime;};
    CSLFloatProxy*		GetDurationProxy(){return &m_Duration;};
    CSLBoolProxy*		GetActiveProxy(){return &m_Active;};
    CSLFloatProxy*		GetWeightProxy(){return &m_Weight;};
    CSLBoolProxy*		GetFillActionProxy(){return &m_FillAction;};
    CSLIntProxy*		GetFillPriorityProxy(){return &m_FillPriority;};
	CSLStringProxy*		GetReferencePathProxy(){return &m_ReferencePath;};

	virtual CSLAnimatableType*	ParameterFromName(SI_Char *in_szName);
	virtual CSLAnimatableType*	ParameterFromType(EFCurveType in_Type, SI_Char *in_szParameterName);

private:
    CSLFloatProxy m_StartTime;
    CSLFloatProxy m_Duration;
    CSLBoolProxy m_Active;
    CSLFloatProxy m_Weight;
    CSLBoolProxy m_FillAction;
    CSLIntProxy m_FillPriority;
	CSLStringProxy m_ReferencePath;
	CSLAction* m_pReference;
    CSIBCArray<CSLTimeControl *> m_TimeControls;
	SI_Void *m_pReserved;
};

#endif
