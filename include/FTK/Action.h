//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file Action.h
	\brief Defines the CSLAction class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _ACTION_H
#define _ACTION_H

#include "Template.h"

class CSLActionFCurve;
class CSLStaticValue;
class CSLXSIShapeReference;

/*! \brief This class represents an \xx ftk_XSI_Action XSI_Action \endxx template.

Actions, also known as action sources, are reusable animation segments (see the
\xx ftk_XSI_Action XSI_Action \endxx template reference). They can be created with the
CSLMixer::AddAction method and instantiated in the mixer's tracks (CSLTrack) as action
clips (CSLActionClip).

\note Actions are not supported by SI3D

\sa CSLActionClip
\sa CSLActionFCurve
\sa CSLMixer
\sa CSLShapeAnimation
\sa CSLStaticValue
*/
class XSIEXPORT CSLAction
    : public CSLTemplate
{
public:
	/*! Constructor
		\param[in] in_pScene	Pointer to the scene containing the CSLAction
		\param[in] in_pModel	Pointer to the model containing the CSLAction
		\param[in] in_pTemplate	Pointer to the CdotXSITemplate defining the CSLAction data
	*/
    CSLAction(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	/*! Destructor
	*/
    virtual ~CSLAction();

	//! Enumeration of all possible action types
	enum EActionType
	{
		SI_AT_FCURVE,			/*!< Fcurve action source item */
		SI_AT_STATICVALUE,		/*!< Static value source  */
		SI_AT_EXPRESSION,		/*!< Expression source */
		SI_AT_CLUSTERKEY,		/*!< Cluster key source */
		SI_AT_CONSTRAINT,		/*!< Constraint source */
		SI_AT_COMPOUND,			/*!< Compound Action item source. */
		SI_AT_SHAPECOMPOUND,	/*!< Shape compound Action item source. */
		SI_AT_NONE,				/*!< No flagged source */
	};

	/*! Synchronizes internal data to be coherent with the IO layer
		\return success or failure
	*/
	virtual SI_Error Synchronize();

	/*! Returns the type of this template
		\return CSLTemplate::XSI_ACTION Template type
	*/
	CSLTemplate::ETemplateType Type(){ return CSLTemplate::XSI_ACTION; }

	/*! Returns the action type
		\return The action type
	*/
    EActionType GetActionType();

	/*! Sets the action type
		\param[in] in_Type The action type
	*/
	SI_Void  SetActionType( EActionType in_Type );

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

	// Animation functionality //////////////////////////////////////////////////

	/*! Removes an animation
		\param[in] in_nIndex Index of the animation to remove
		\retval SI_Error::SI_SUCCESS The animation was removed
		\retval SI_Error::SI_ERR_BAD_ARGUMENT Invalid index
	*/
	SI_Error RemoveAnimation( SI_Int in_nIndex );

	/*! Removes an animation
		\param[in,out]	io_pToRemove Pointer to the animation to remove
		\retval	SI_Error::SI_SUCCESS The animation was removed
		\retval	SI_Error::SI_ERR_BAD_ARGUMENT Animation was not found
	*/
	SI_Error RemoveAnimation( CSLActionFCurve *io_pToRemove );

	/*! Returns the list of all animations
		\return Pointer to the list of pointer of all animations
	*/
	CSLActionFCurve** GetAnimationList();

	/*! Get the total number of Animations
		\return The number of Animations
	*/
	SI_Int GetAnimationCount();

	/*! Adds a new animation with default interpolation ( constant interpolation )
		\return Pointer to the newly added Animation
	*/
	virtual CSLActionFCurve* AddAnimation();

	/*! Adds a new animation
		\param[in] in_InterpolationType FCurve interpolation type
		\return Pointer to the newly added Animation
	*/
	virtual CSLActionFCurve* AddAnimation( EFCurveInterpolationType in_InterpolationType );

	/*! Removes all animations
		\return SI_Error::SI_SUCCESS
	*/
	SI_Error ClearAnimations();

	/*! Adds a preallocated animation to the animation list
		\param[in]	in_pNewAnimation Pointer to the animation to add
		\return The newly added Animation or null if it was already added
	*/
	CSLActionFCurve* ConnectAnimation(CSLActionFCurve* in_pNewAnimation);

	// Static Values functionality //////////////////////////////////////////////////

	/*! Removes a static value
		\param[in]	in_nIndex Index of the static value to remove
		\retval SI_Error::SI_SUCCESS The static value was removed
		\retval SI_Error::SI_ERR_BAD_ARGUMENT Invalid index
	*/
	SI_Error RemoveStaticValue( SI_Int in_nIndex );

	/*! Removes a static value
		\param[in,out]	io_pToRemove Pointer to the static value to remove
		\retval SI_Error::SI_SUCCESS The static value was removed
		\retval SI_Error::SI_ERR_BAD_ARGUMENT static value was not found
	*/
	SI_Error RemoveStaticValue( CSLStaticValue *io_pToRemove );

	/*! Returns the list of all static values
		\return Pointer to the list of pointer of all static values
	*/
	CSLStaticValue** GetStaticValueList();

	/*! Returns the total number of static values
		\return The number of static values
	*/
	SI_Int GetStaticValueCount();

	/*! Adds a new static value
		\return Pointer to the newly added static value
	*/
	CSLStaticValue* AddStaticValue();

	/*! Removes all static values
		\return SI_Error::SI_SUCCESS
	*/
	SI_Error ClearStaticValues();

	/*! Adds a preallocated static value to the static value list
		\param[in] in_pNewStaticValue Pointer to the static value to add
		\return The newly added static value or null if it was already added
	*/
	CSLStaticValue* ConnectStaticValue(CSLStaticValue* in_pNewStaticValue);

	CSLFloatProxy*	GetStartTimeProxy() {return &m_StartTime;};
	CSLFloatProxy*	GetEndTimeProxy() {return &m_EndTime;};
	CSLEnumProxy<EActionType, SI_AT_NONE>* GetActionTypeProxy() { return &m_ActionType;};

	/*! Adds a new shape reference
		\return Pointer to the shape
	*/
	CSLXSIShapeReference* AddXSIShapeReference();

	/*! Returns the associated shape
		\return Pointer to the shape
	*/
	CSLXSIShapeReference* GetXSIShapeReference();

	/*! Removes the associated shape
		\return SI_Error::SI_SUCCESS
	*/
	SI_Error ClearXSIShapeReference();

	/*! ConnectS a preallocated shape to the action shape parameter
		\param[in] in_pNewXSIShape Pointer to the shape to connect
		\return The newly added shape or null if it was already added
	*/
	CSLXSIShapeReference* ConnectXSIShapeReference(CSLXSIShapeReference* in_pNewXSIShape);

private:
    CSLFloatProxy m_StartTime;
    CSLFloatProxy m_EndTime;
    CSLEnumProxy<EActionType, SI_AT_NONE> m_ActionType;
    CSIBCArray<CSLActionFCurve*> m_Animations;
    CSIBCArray<CSLStaticValue*> m_StaticValues;
	CSLXSIShapeReference *m_pXSIShapeReference;
};
#endif
