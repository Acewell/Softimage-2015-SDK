//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file IKEffector.h
	\brief Defines the CSLIKEffector class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _IKEFFECTOR_H
#define _IKEFFECTOR_H

#include "IK.h"


/*! \brief This class represents an \xx ftk_SI_IK_Effector SI_IK_Effector \endxx template.

	Describes the effector of an IK chain (see the \xx ftk_SI_IK_Effector SI_IK_Effector \endxx
	template reference).
*/
class XSIEXPORT CSLIKEffector
	: public CSLIK
{
public:

	/*! Constructor
		\param[in] in_pScene	Pointer to the scene containing the effector
		\param[in] in_pModel	Pointer to the model containing the effector
		\param[in] in_pTemplate	Pointer to the CdotXSITemplate containing the effector
		\param[in] in_pRoot	Pointer to the root of the chain
		\return an instance of CSLIKEffector
	*/
	CSLIKEffector(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate, CSLModel* in_pRoot);

	/*! Destructor
	*/
	virtual ~CSLIKEffector();

	/*! Return the inherit rotation flag of the effector.
		\return Inherit rotation flag.
	*/
	SI_Bool GetRotationFlag();

	/*! Change the inherit rotation flag of the joint.
		\param[in]	in_bValue New inherit rotation flag.
	*/
	SI_Void SetRotationFlag(SI_Bool in_bValue);

	/*! Synchronizes this IK effector instance with its IO layer representation
		\retval SI_Error::SI_SUCCESS this function always returns SI_SUCCESS
	*/
    virtual SI_Error Synchronize();

	/*! Returns the template type of the effector
		\retval CSLTemplate::SI_IK_EFFECTOR the template type
	*/
	virtual ETemplateType Type();

	/*! Returns a handle on one of this light's parameters by using its name
		\param[in] in_szName the name of the parameter to get the handle from
		\return the handle to the parameter
	*/
    virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);

	/*! Validate that the parent is of valid type
		\param[in] in_pNewParent the parent to validate against
		\return whether the parent is valid or not
	*/
	virtual SI_Bool ValidateParent(CSLModel *in_pNewParent);

	CSLIntProxy*	GetRotationFlagProxy() { return &m_RotationFlag; };

private:
	CSLIntProxy m_RotationFlag;

	void *m_pReserved;	// reserved for future extension
};

#endif
