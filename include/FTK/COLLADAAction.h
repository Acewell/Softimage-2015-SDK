//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file COLLADAAction.h
	\brief Defines the CSLCOLLADAAction and CSLCOLLADAActionFCurve classes

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _COLLADAACTION_H
#define _COLLADAACTION_H

#include "Action.h"
#include "ActionFCurve.h"

/*! \brief This class represents an action source for COLLADA.

	Actions, also known as action sources, are reusable animation segments.
	They can be created with the CSLMixer::AddAction method and instanciated
	in the mixer's tracks (CSLTrack) as action clips (CSLActionClip).

	\note Actions are not supported by SI3D

	\sa CSLActionClip
	\sa CSLActionFCurve
	\sa CSLMixer
	\sa CSLShapeAnimation
	\sa CSLStaticValue
*/
class XSIEXPORT CSLCOLLADAAction
    : public CSLAction
{
public:
	/*! Constructor
		\param[in] in_pScene	Pointer to the scene containing the CSLAction
		\param[in] in_pModel	Pointer to the model containing the CSLAction
		\param[in] in_pTemplate	Pointer to the CdotXSITemplate defining the CSLAction data
	*/
    CSLCOLLADAAction(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	/*! Destructor
	*/
    virtual ~CSLCOLLADAAction();

	/*! Synchronizes internal data to be coherent with the IO layer
		\return success or failure
	*/
	virtual SI_Error Synchronize();

	/*! Fixes internal data to be coherent with the IO layer at creation time
		\return success or failure
	*/
	virtual SI_Error Fix();

	/*! Returns the end time
		\return The end time
	*/
	virtual SI_Float GetEndTime();

	/*! Sets the end time of the action
		\param[in] in_fTime The end time
	*/
	virtual SI_Void SetEndTime( SI_Float in_fTime );

	/*! Returns the start time of the action
		\return The start time
	*/
	virtual SI_Float GetStartTime();

	/*! Sets the start time of the action
		\param[in] in_fTime The new start time
	*/
	virtual SI_Void SetStartTime( SI_Float in_fTime );

	/*! Adds a new animation with default interpolation ( constant interpolation )
		\return Pointer to the newly added Animation
	*/
	virtual CSLActionFCurve* AddAnimation();

	/*! Adds a new animation
		\param[in] in_InterpolationType FCurve interpolation type
		\return Pointer to the newly added Animation
	*/
	virtual CSLActionFCurve* AddAnimation( EFCurveInterpolationType in_InterpolationType );

private:

	SI_Void *m_pReserved;
	CdotXSIParam *m_pStart;
	CdotXSIParam *m_pEnd;

};

#include "BaseFCurve.h"

/*! \brief This class represents an action fcurbe for COLLADA.

	Wraps all functionality for an FCurve used in a mixer.
	\sa CSLMixer
	\sa CSLAction
*/
class XSIEXPORT CSLCOLLADAActionFCurve
    : public CSLActionFCurve
{
public:

	/*! Constructor
		\param[in] in_pScene	Pointer to the scene containing the ActionFCurve
		\param[in] in_pModel	Pointer to the model containing the ActionFCurve
		\param[in] in_pTemplate	Pointer to the CdotXSITemplate containing the ActionFCurve
		\param[in] in_InterpolationType	FCurve interpolation type
	*/
    CSLCOLLADAActionFCurve(CSLScene* in_pScene,
						 CSLModel *in_pModel,
						 CdotXSITemplate* in_pTemplate,
						 EFCurveInterpolationType in_InterpolationType);

	/*! Destructor
	*/
	virtual ~CSLCOLLADAActionFCurve();

	/*! Synchronizes internal data to be coherent with the IO layer
		\return success or failure
	*/
	virtual SI_Error Synchronize();

	/*! Connects an existing COLLADA animation template
		\param[in] in_pChannel	Template to connect
		\param[in] in_offset	Offset when reading data. Needed to synchronized with stride attribut
		\return Error code
	*/
    virtual SI_Error ConnectCOLLADAAnimation( CCOLLADATemplate* in_pChannel, const int in_offset = 0);

	/*! Returns the parameter reference
	* \return the parameter reference
	*/

	virtual CSLAnimatableType* ParameterReference();

private:

	SI_Void		GetFloatArrayFromCurve ( CSIBCArray<float>& inout_Array, int in_iElement );
	SI_Void		AddSource ( CCOLLADATemplate* in_pAnimation,
							int in_iElement,
							SI_Char* in_szPrefix,
							SI_Char* in_szID,
							SI_Char* in_szOutput,
							CCOLLADATemplate* in_pSampler);

	CSLAnimatableType *m_pParamReference;
	SI_Void *m_pReserved;
};


#endif _COLLADAACTION_H