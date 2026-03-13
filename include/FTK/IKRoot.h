//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file IKRoot.h
	\brief Defines the CSLIKRoot class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _IKROOT_H
#define _IKROOT_H

#include "IK.h"

// Forward declaration
class CSLIKJoint;
class CSLIKEffector;


/*! \brief This class represents an \xx ftk_SI_IK_Root SI_IK_Root \endxx template.

	Describes the root of an IK chain (see the \xx ftk_SI_IK_Root SI_IK_Root \endxx
	template reference).
*/
class XSIEXPORT CSLIKRoot
	: public CSLIK
{
public:
	/*! Constructor
		\param[in] in_pScene	Pointer to the scene containing the root
		\param[in] in_pModel	Pointer to the model containing the root
		\param[in] in_pTemplate	Pointer to the CdotXSITemplate containing the root
		\return an instance of CSLIKRoot
	*/
	CSLIKRoot(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	/*! Destructor
	*/
	virtual ~CSLIKRoot();

	/*!	Returns the effector of the IK chain.
		\return Pointer to a texture 2D object.
	*/
	CSLModel* GetEffector();

	/*!	Returns an array of all joints in the IK chain.
		\return Array of pointers to IK joint objects.
	*/
	CSLModel** GetJointList();

	/*!	Returns the number of joints in the IK chain.
		\return Number of joint.
	*/
	SI_Int GetJointCount();

	/*! Connects a joint to this IK root
		\param[in] in_pNewJoint the joint to connect
		\return the joint to connect
	*/
	CSLModel* ConnectJoint(CSLModel* in_pNewJoint);

	/*! Connects an effector to this IK root
		\param[in] in_pNewEffector the effector to connect
		\return the effector to connect
	*/
	CSLModel* ConnectEffector(CSLModel* in_pNewEffector);

	/*! Synchronizes this IK root instance with its IO layer representation
		\retval SI_Error::SI_SUCCESS this function always returns SI_SUCCESS
	*/
    virtual SI_Error Synchronize();

	/*! Returns the template type
		\return CSLTemplate::SI_IK_ROOT the template type of the IK root
	*/
	virtual ETemplateType Type();


private:
	CSIBCArray<CSLModel *> m_Joints;
	CSLModel* m_pEffector;

	void *m_pReserved;	// reserved for future extension
};

#endif
