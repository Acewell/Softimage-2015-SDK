//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file Track.h
	\brief Defines the CSLTrack class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _TRACK_H
#define _TRACK_H

#include "Template.h"
class CSLActionClip;
class CSLActionClipContainer;

/*! \brief This class represents an \xx ftk_XSI_Track XSI_Track \endxx template.

	Tracks are containers of action clips (CSLActionClip--see the
	\xx ftk_XSI_Track XSI_Track \endxx template reference). They can be
	added to an animation mixer using the CSLMixer::AddTrack method.

	\note CSLTrack is not supported by SI3D

	\sa CSLAction
	\sa CSLActionClip
	\sa CSLActionClipContainer
	\sa CSLMixer
*/
class XSIEXPORT CSLTrack
    : public CSLTemplate
{
public:
	/*! Constructor
		\param[in] in_pScene	Pointer to the scene containing the CSLTrack
		\param[in] in_pModel	Pointer to the model containing the CSLTrack
		\param[in] in_pTemplate	Pointer to the CdotXSITemplate defining the CSLTrack data
	*/
    CSLTrack(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
    virtual ~CSLTrack();

	SI_Error Synchronize();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_TRACK The type of this template
	*/
	CSLTemplate::ETemplateType Type(){ return XSI_TRACK; }

	/*! Returns the value of the mute flag
		\retval true The track contributes to the animation.
		\retval false The track \b does \b not contribute to the animation.

	*/
    SI_Bool GetMute();

	/*! Sets the value of the mute flag
		\note When set to \b False, the track contributes to the animation.
		\param[in] in_bNew New value
	*/
	SI_Void SetMute( SI_Bool in_bNew );

	/*! Returns the value of the ripple flag
		\note Adding new tracks will always ripple existing clips if necessary.
		\retval true A moved clip will push the next or previous clips along
			the track if necessary so that clips do not overlap on the same track.
		\retval false Clips cannot be moved past the position of the next or
			previous clip.
	*/
	SI_Bool GetRipple();

	/*! Sets the value of the ripple flag
		\param[in] in_bNew New value
		\note When set to \b True, moved clips will push the next or previous
		clips along the track if necessary so that clips do not overlap on the
		same track.
		\note A \b False value can be used so clips cannot be moved past the
		position of the next or previous clip.
	*/
	SI_Void SetRipple( SI_Bool in_bNew );

	/*! Returns the value of the solo flag
		\retval true Only this track contributes to the animation.
		\retval false Other tracks might contribute to the animation.
	*/
    SI_Bool GetSolo();

	/*! Sets the value of the solo flag
		\param[in] in_bNew New value for the flat
		\note Set this flag to \b True if you want this track to be the sole contributor to the animation.
	*/
	SI_Void SetSolo( SI_Bool in_bNew );


	// action clip functionality //////////////////////////////////////////////

	/*! Removes an action clip
		\param[in] in_nIndex Index of the action clip to remove
		\retval SI_Error::SI_SUCCESS The element was removed
		\retval SI_Error::SI_ERR_BAD_ARGUMENT Invalid index
	*/
	SI_Error RemoveActionClip( SI_Int in_nIndex );

	/*! Removes an action clip
		\param[in,out] io_pToRemove Pointer to the action clip to remove
		\retval SI_Error::SI_SUCCESS The element was removed
		\retval SI_Error::SI_ERR_BAD_ARGUMENT The element could not be found
	*/
	SI_Error RemoveActionClip( CSLActionClip *io_pToRemove );

	/*! Returns the list of all action clips
		\return Pointer to the list of pointer of all action clips
	*/
	CSLActionClip** GetActionClipList();

	/*! Returns the total number of action clips
		\return The number of action clips
	*/
	SI_Int GetActionClipCount();

	/*! Adds a new ActionClip
		\return Pointer to the newly added action clip
	*/
	CSLActionClip* AddActionClip();

	/*! Adds a new ActionClipContainer
		\return Pointer to the newly added action clip container
	*/
	CSLActionClipContainer* AddActionClipContainer();

	/*! Removes all action clips
		\return SI_Error::SI_SUCCESS
	*/
	SI_Error ClearActionClips();

	/*! Adds a preallocated ActionClip to the action clip list
		\param[in] in_pNewActionClip Pointer to the action clip to add
		\return The newly added action clip or null if it was already added
	*/
	CSLActionClip* ConnectActionClip(CSLActionClip* in_pNewActionClip);

private:
    CSLBoolProxy m_Ripple;
    CSLBoolProxy m_Mute;
    CSLBoolProxy m_Solo;
    CSIBCArray<CSLActionClip *> m_ActionClips;

	SI_Void *m_pReserved;

};

#endif
