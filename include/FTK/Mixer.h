//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file Mixer.h
	\brief Defines the CSLMixer class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _MIXER_H
#define _MIXER_H

#include "Template.h"

// Forward declaration
class CSLAction;
class CSLTrack;

/*! \brief This class represents an \xx ftk_XSI_Mixer XSI_Mixer \endxx template.

The animation mixer provides high-level control over animation (see the \xx ftk_XSI_Mixer XSI_Mixer \endxx
template reference). The mixer contains a database of short animations called action sources (CSLAction).  An
action source can be instantiated in the form of an action clip (CSLActionClip) in tracks (CSLTrack) to compose
complex animation. You can create an animation mixer with the CSLModel::CreateMixer method.

\note This template is not supported by SI3D.

\sa CSLAction
\sa CSLActionClip
\sa CSLModel
\sa CSLTrack
*/
class XSIEXPORT CSLMixer
    : public CSLTemplate
{
public:
	/*! Constructor
		\param[in] in_pScene	Pointer to the scene containing the mixer
		\param[in] in_pModel	Pointer to the model containing the mixer
		\param[in] in_pTemplate	Pointer to the CdotXSITemplate containing the mixer
	*/
    CSLMixer(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
    virtual ~CSLMixer();

	/*! Synchronizes internal data to be coherent with the IO layer
		\return success or failure
	*/
	virtual SI_Error Synchronize();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_MIXER Template type
	*/
	CSLTemplate::ETemplateType Type(){ return CSLTemplate::XSI_MIXER; }

	/*! Determines if the animation mixer is active or not
		\return Value of the flag
	*/
    SI_Bool GetActive();

	/*! Toggles the animation mixer evaluation
		\param[in] in_bNew Value of the flag
	*/
	SI_Void SetActive( SI_Bool in_bNew );

	/*! Determines if inter-clip interpolation is enabled or not
		\return Value of the flag
	*/
    SI_Bool GetAutoTransition();

	/*! Toggles inter-clip interpolation
		\param[in] in_bNew Value of the flag
	*/
	SI_Void SetAutoTransition( SI_Bool in_bNew );

	/*! Returns the Maintain Continuity Flag
		\note When you select Quaternion for Rotation Mixing, this option
			generates more continuous rotation curves, especially for operations
			such as plotting/freezing rotation parameters driven by the animation
			mixer.
		\retval true Maintain Continuity is enabled
		\retval false Maintain Continuity is disabled
	*/
    SI_Bool GetMaintainContinuity();

	/*! Sets the Maintain Continuity Flag
		\note When you select Quaternion for Rotation Mixing, this option
			generates more continuous rotation curves, especially for operations
			such as plotting/freezing rotation parameters driven by the animation
			mixer.
		\warning This flag is ignored unless QuaternionMixing is enabled.
		\param[in] in_bNew True to enable, false to disable
		\sa CSLMixer::SetQuaternionMixing
	*/
	SI_Void SetMaintainContinuity( SI_Bool in_bNew );

	/*! Returns how the mix is calculated
		\retval true Mixes are a weighted averages. The results are mixes that
			fall in-between the values of the separate clips.
		\retval false mixes are additive. The values of the separate clips are
			added on top of each other.
	*/
    SI_Bool GetNormalize();

	/*! Sets how the mix is calculated
		\note When set to \b True, mixes are a weighted averages. The results
			are mixes that fall in-between the values of the separate clips.  When
			set to \b False, mixes are additive. The values of the separate clips
			are added on top of each other.
		\param[in] in_bNew Value of the flag
	*/
	SI_Void SetNormalize( SI_Bool in_bNew );

	/*! Returns the Quaternion Mixing Flag
		\note Quaternions usually result in smoother rotations; however, if you are
			mixing two or more rotations and using Quaternion, there may be some
			unexpected flips in the animation. Using Euler will probably solve this
			problem.
		\retval true Rotation values are mixed according to their Quaternion values
		\retval false Rotation values are mixed according to their Euler values
	*/
    SI_Bool GetQuaternionMixing();

	/*! Sets the Quaternion Mixing Flag
		\note Controls whether rotation values are mixed according to their Quaternion
			values (\b True) or their Euler values (\b False). Quaternions usually result
			in smoother rotations; however, if you are mixing two or more rotations and
			using Quaternion, there may be some unexpected flips in the animation.
			Using Euler will probably solve this problem.
		\param[in] in_bNew Value of the flag
	*/
	SI_Void SetQuaternionMixing( SI_Bool in_bNew );

	/*! Returns the Remove Spins Flag
		\return Value of the flag
	*/
    SI_Bool GetRemoveSpins();

	/*! Sets the Remove Spins Flag
		\note When set to \b True, this option removes extra spinning that may occur in a rotation so that
			the object's rotation values are only between -180 and 180. For example, you
			can sometimes get rotation values with extra "spins," such as
			[-591, 1015, 15]. This option gives you the same rotation but without the
			spins.
		\warning This flag is ignored unless Quaternion Mixing is disabled.
		\param[in] in_bNew Value of the flag
		\sa CSLMixer::SetQuaternionMixing
	*/
	SI_Void SetRemoveSpins( SI_Bool in_bNew );

	// Actions functionality //////////////////////////////////////////////////

	/*! Removes an action
		\param[in] in_nIndex Index of the CSLAction to remove
		\retval SI_Error::SI_SUCCESS The element was removed
		\retval SI_Error::SI_ERR_BAD_ARGUMENT Invalid index
	*/
    SI_Error RemoveAction( SI_Int in_nIndex );

	/*! Removes an action
		\param[in] in_pToRemove Pointer to the action to remove
		\retval SI_Error::SI_SUCCESS The element was removed
		\retval SI_Error::SI_ERR_BAD_ARGUMENT The element could not be found
	*/
	SI_Error RemoveAction( CSLAction *in_pToRemove );

	/*! Returns the list of all actions
		\return Pointer to the list of pointer of all actions
	*/
	CSLAction** GetActionList();

	/*! Returns the total number of actions
		\return The number of actions
	*/
	SI_Int GetActionCount();

	/*! Adds a new action
		\return Pointer to the newly added action
	*/
	virtual CSLAction* AddAction();

	/*! Removes all actions
		\return Whether or not removal was successful
	*/
	SI_Error ClearActions();

	/*! Adds a preallocated action to the action list
		\param[in] in_pNewAction Pointer to the action to add
		\return The newly added action or null if it was already added
	*/
	CSLAction* ConnectAction(CSLAction* in_pNewAction);

	/*! Searches for an action with the specifed name in the action list
		\param[in] in_pActionName The action name we're looking for
		\return The action found or NULL
	*/
	CSLAction* FindAction(SI_Char* in_pActionName);

	// Tracks functionality //////////////////////////////////////////////////

	/*! Removes a track
		\param[in] in_nIndex Index of the track to remove
		\retval SI_Error::SI_SUCCESS The element was removed
		\retval SI_Error::SI_ERR_BAD_ARGUMENT Invalid index
	*/
	SI_Error RemoveTrack( SI_Int in_nIndex );

	/*! Removes a track
		\param[in,out] io_pToRemove Pointer to the track to remove
		\retval SI_Error::SI_SUCCESS The element was removed
		\retval SI_Error::SI_ERR_BAD_ARGUMENT The element could not be found
	*/
	SI_Error RemoveTrack( CSLTrack *io_pToRemove );

	/*! Returns the list of all tracks
		\return Pointer to the list of pointer of all tracks
	*/
    CSLTrack** GetTrackList();

	/*! Returns the total number of tracks
		\return The number of tracks
	*/
	SI_Int GetTrackCount();

	/*! Adds a new track
		\return Pointer to the newly added track
	*/
	CSLTrack* AddTrack();

	/*! Removes all Tracks
		\return Whether or not removal was successful
	*/
	SI_Error ClearTracks();

	/*! Adds a preallocated Track to the Track list
		\param[in] in_pNewTrack Pointer to the Track to add
		\return The newly added Track or null if it was already added
	*/
	CSLTrack* ConnectTrack(CSLTrack* in_pNewTrack);

	CSLBoolProxy* GetAutoTransitionProxy() { return &m_AutoTransition; };
    CSLBoolProxy* GetActiveProxy() { return &m_Active; };
    CSLBoolProxy* GetNormalizeProxy() { return &m_Normalize; };
    CSLBoolProxy* GetQuaternionMixingProxy() { return &m_QuaternionMixing; };
    CSLBoolProxy* GetRemoveSpinsProxy() { return &m_RemoveSpins; };
    CSLBoolProxy* GetMaintainContinuityProxy() { return &m_MaintainContinuity; };

private:
    CSLBoolProxy m_AutoTransition;
    CSLBoolProxy m_Active;
    CSLBoolProxy m_Normalize;
    CSLBoolProxy m_QuaternionMixing;
    CSLBoolProxy m_RemoveSpins;
    CSLBoolProxy m_MaintainContinuity;
    CSIBCArray<CSLAction *> m_Actions;
    CSIBCArray<CSLTrack *> m_Tracks;

	SI_Void *m_pReserved;
};

#endif // _MIXER_H
