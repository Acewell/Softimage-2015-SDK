//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file COLLADAMixer.h
	\brief Defines the CSLCOLLADAMixer class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _COLLADAMIXER_H
#define _COLLADAMIXER_H

#include "Mixer.h"

// Forward declaration
class CSLAction;
class CSLTrack;

/*! \brief This class represents the mixed for COLLADA.

	The animation mixer provides high-level control over animation.  The
	mixer contains a database of short animations called action sources
	(CSLAction).  An action source can be instantiated in the form of an
	action clip (CSLActionClip) in tracks (CSLTrack) to compose complex
	animation.  You can create an animation mixer with the
	CSLModel::CreateMixer method.

	\note This template is not supported by SI3D.

	\sa CSLAction
	\sa CSLActionClip
	\sa CSLModel
	\sa CSLTrack
*/
class XSIEXPORT CSLCOLLADAMixer
    : public CSLMixer
{
public:
	/*! Constructor
		\param in_pScene	Pointer to the scene containing the mixer
		\param in_pModel	Pointer to the model containing the mixer
		\param in_pTemplate	Pointer to the CdotXSITemplate containing the mixer
	*/
    CSLCOLLADAMixer(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
    virtual ~CSLCOLLADAMixer();

	/*! Adds a new action
		\return CSLAction Pointer to the newly added action
	*/
	virtual CSLAction* AddAction();
private:

	SI_Void *m_pReserved;

};


#endif _COLLADAMIXER_H