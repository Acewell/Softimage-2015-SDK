//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file ActionClipContainer.h
	\brief Defines the CSLActionClipContainer class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _ACTIONCLIPCONTAINER_H
#define _ACTIONCLIPCONTAINER_H

#include "Template.h"
#include "ActionClip.h"

// Forward declaration

class CSLAction;
class CSLTrack;

/*! \brief This class represents an \xx ftk_XSI_ActionClipContainer XSI_ActionClipContainer \endxx template.

An action clip container is a specialisation of the action clip (CSLActionClip) (see the
\xx ftk_XSI_ActionClipContainer XSI_ActionClipContainer \endxx template reference). It's an
action clip that can contain a list of tracks (CSLTrack). You can create an action clip with
the CSLTrack::AddActionClip method.

\sa CSLActionClip
\sa CSLAction
\sa CSLMixer
\sa CSLTimeControl
\sa CSLTrack
*/
class XSIEXPORT CSLActionClipContainer
    : public CSLActionClip
{
public:
	/*! Constructor
		\param[in] in_pScene	Pointer to the scene containing the mixer
		\param[in] in_pModel	Pointer to the model containing the mixer
		\param[in] in_pTemplate	Pointer to the CdotXSITemplate containing the mixer
	*/
    CSLActionClipContainer(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
    virtual ~CSLActionClipContainer();

	/*! Synchronizes internal data to be coherent with the IO layer
		\return success or failure
	*/
	virtual SI_Error Synchronize();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_ACTIONCLIPCONTAINER Template type
	*/
	CSLTemplate::ETemplateType Type(){ return CSLTemplate::XSI_ACTIONCLIPCONTAINER; }

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

	/*! Get the total number of tracks
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

private:
    CSIBCArray<CSLTrack *> m_Tracks;

	SI_Void *m_pReserved;
};

#endif // _ACTIONCLIPCONTAINER_H
