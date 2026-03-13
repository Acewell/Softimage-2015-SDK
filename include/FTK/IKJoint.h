//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file IKJoint.h
	\brief Defines the CSLIKResolutionPlane and CSLIKJoint classes

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _IKJOINT_H
#define _IKJOINT_H

#include "IK.h"


/*! \brief This class represents an \xx ftk_XSI_IK_ResolutionPlane XSI_IK_ResolutionPlane \endxx template.

	Describes the resolution plane of an IK chain
	(see the \xx ftk_XSI_IK_ResolutionPlane XSI_IK_ResolutionPlane \endxx template reference).
*/
class XSIEXPORT CSLIKResolutionPlane
	: public CSLTemplate
{
public:
	/*! Joint solver types
	*/
	enum EIKResPlaneType
	{
		SI_IKRPTYPE_DEFAULT,			//!< default resolution plane type
		SI_IKRPTYPE_PREFAXIS,			//!< preferred axis
		SI_IKRPTYPE_UPVECTOR,			//!< up vector
	};

	/*! Constructor
		\param[in] in_pScene	Pointer to the scene containing the Resolution Plane
		\param[in] in_pModel	Pointer to the model containing the Resolution Plane
		\param[in] in_pTemplate	Pointer to the CdotXSITemplate containing the Resolution Plane
		\return an instance of CSLIKResolutionPlane
	*/
	CSLIKResolutionPlane(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	/*! Destructor
	*/
	virtual ~CSLIKResolutionPlane();

	/*! Returns the resolution plane type of the joint.
		\return resolution plane type.
	*/
	EIKResPlaneType GetResolutionPlaneType();

	/*! Changes the resolution plane type of the joint.
		\param[in]	in_Type	New resolution plane type.
	*/
	SI_Void SetResolutionPlaneType(EIKResPlaneType in_Type);

	/*! Returns the Roll value of the Resolution Plane.
		\return Roll value.
	*/
	SI_Float GetRoll();

	/*! Changes the Roll value of the Resolution Plane.
		\param[in]	in_fValue	New Roll value.
	*/
	SI_Void SetRoll(SI_Float in_fValue);

	/*! Returns a flag indicating if the preferred rotation in X should be used as the roll angle.
		\return status of the preference.
	*/
	SI_Bool GetPrefRotXAsRoll();

	/*! Changes the flag indicating if the preferred rotation in X should be used as the roll angle.
		\param[in]	in_bValue  new status of the preference.
	*/
	SI_Void SetPrefRotXAsRoll(SI_Bool in_bValue);

	/*! Returns the prefered rotation of the Resolution Plane.
		\return Up Vector value.
	*/
	CSIBCVector3D GetUpVector();

	/*! Changes the Up Vector value of the Resolution Plane.
		\param[in]	in_rValue	New Up Vector value.
	*/
	SI_Void SetUpVector(CSIBCVector3D &in_rValue);

	/*! Returns a flag indicating if the up vector is relative to the IK root.
		\return status of the preference.
	*/
	SI_Bool GetUpVectorRelativeToRoot();

	/*! Changes the flag indicating if the up vector is relative to the IK root.
		\param[in]	in_bValue  new status of the preference.
	*/
	SI_Void SetUpVectorRelativeToRoot(SI_Bool in_bValue);


	/*! Returns the prefered rotation of the Resolution Plane.
		\return Preferred rotation value.
	*/
	CSIBCVector3D GetPreferredRotation();

	/*! Changes the preferred rotation value of the Resolution Plane.
		\param[in]	in_rValue	New preferred rotation value.
	*/
	SI_Void SetPreferredRotation(CSIBCVector3D &in_rValue);

	/*! Returns a flag indicating if the Preferred Rotation is relative to the IK root.
		\return status of the preference.
	*/
	SI_Bool GetPreferredRotationRelativeToRoot();

	/*! Changes the flag indicating if the Preferred Rotation is relative to the IK root.
		\param[in]	in_bValue  new status of the preference.
	*/
	SI_Void SetPreferredRotationRelativeToRoot(SI_Bool in_bValue);

	/*! Synchronizes this IK Resolution Plane instance with its IO layer representation
		\retval SI_Error::SI_SUCCESS this function always returns SI_SUCCESS
	*/
    virtual SI_Error Synchronize();

	/*! Returns the template type of the Resolution Plane
		\retval CSLTemplate::XSI_IK_RESOLUTIONPLANE the template type
	*/
	virtual ETemplateType Type();

	/*! Returns a handle on one of this template's parameters by using its name
		\param[in] in_szName the name of the parameter to get the handle from
		\return the handle to the parameter
	*/
    virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);

	/*! Validates that the parent is of valid type
		\param[in] in_pNewParent the parent to validate against
		\return whether the parent is valid or not
	*/
	virtual SI_Bool ValidateParent(CSLModel *in_pNewParent);

	CSLIntProxy*		GetTypeProxy() { return &m_Type; };
	CSLFloatProxy*		GetRollProxy() { return & m_Roll; };
	CSLBoolProxy*		GetPrefRotXAsRollProxy() { return & m_PrefRotXAsRoll; };
	CSLVector3DProxy*	GetUpVectorProxy() { return & m_UpVector; };
	CSLBoolProxy*		GetUpVectorRelativeToRootProxy() { return & m_UpVectorRelativeToRoot; };
	CSLVector3DProxy*	GetPreferredRotationProxy() { return & m_PreferredRotation; };
	CSLBoolProxy*		GetPrefRotRelativeToRootProxy() { return & m_PrefRotRelativeToRoot; };

private:

	CSLIntProxy m_Type;
	CSLFloatProxy m_Roll;
	CSLBoolProxy m_PrefRotXAsRoll;
	CSLVector3DProxy m_UpVector;
	CSLBoolProxy m_UpVectorRelativeToRoot;
	CSLVector3DProxy m_PreferredRotation;
	CSLBoolProxy m_PrefRotRelativeToRoot;

	void *m_pReserved;	// reserved for future extension
};


/*! \brief This class represents an \xx ftk_SI_IK_Joint SI_IK_Joint \endxx template.

	Describes one joint of an IK chain (see the \xx ftk_SI_IK_Joint SI_IK_Joint \endxx
	template reference).
*/
class XSIEXPORT CSLIKJoint
	: public CSLIK
{
public:
	//! Joint solver types
	enum EJointSolverType
	{
		SI_DEFAULT,			//!< default joint type
		SI_2D,				//!< 2D joint
		SI_3D,				//!< 3D joint
	};

	/*! Constructor
		\param[in] in_pScene	Pointer to the scene containing the joint
		\param[in] in_pModel	Pointer to the model containing the joint
		\param[in] in_pTemplate	Pointer to the CdotXSITemplate containing the joint
		\param[in] in_pRoot	Pointer to the model that is the chain root of that joint
		\return an instance of CSLIKJoint
	*/
	CSLIKJoint(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate, CSLModel* in_pRoot);

	/*! Destructor
	*/
	virtual ~CSLIKJoint();

	/*! Returns the length value of the joint.
		\return Length value.
	*/
	SI_Float GetLength();

	/*! Changes the length value of the joint.
		\param[in]	in_fValue	New length value.
	*/
	SI_Void SetLength(SI_Float in_fValue);

	/*! Returns the prefered rotation of the joint.
		\return Preferred rotation value.
	*/
	CSIBCVector3D GetPreferredRotation();

	/*! Changes the preferred rotation value of the joint.
		\param[in]	in_rValue	New preferred rotation value.
	*/
	SI_Void SetPreferredRotation(CSIBCVector3D &in_rValue);

	/*! Returns a flag indicating if the joint is a pseudo-root.
		\return Pseudo-root status.
	*/
	SI_Bool GetPseudoRoot();

	/*! Changes the flag indicating the joint is a pseudo-root.
		\param[in]	in_bValue New Pseudo-root status.
	*/
	SI_Void SetPseudoRoot(SI_Bool in_bValue);

	/*! Returns the rotation limit activation flag of the joint.
		\return Rrotation limit activation flag.
	*/
	SI_Bool GetRotationLimitActivation();

	/*! Changes the rotation limit activation flag of the joint.
		\param[in]	in_bValue New rotation limit activation flag.
	*/
	SI_Void SetRotationLimitActivation(SI_Bool in_bValue);

	/*! Returns the maximum rotation limit of the joint.
		\return Maximum rotation limit.
	*/
	CSIBCVector3D GetRotationLimitMaximum();

	/*! Changes the maximum rotation limit value of the joint.
		\param[in]	in_rValue	New maximum rotation limit.
	*/
	SI_Void SetRotationLimitMaximum(CSIBCVector3D &in_rValue);

	/*! Returns the minimum rotation limit of the joint.
		\return Minimum rotation limit.
	*/
	CSIBCVector3D GetRotationLimitMinimum();

	/*! Changes the minimum rotation limit value of the joint.
		\param[in]	in_rValue	New minimum rotation limit.
	*/
	SI_Void SetRotationLimitMinimum(CSIBCVector3D &in_rValue);

	/*! Returns the solver type of the joint.
		\return Solver type.
	*/
	EJointSolverType GetSolverType();

	/*! Changes the solver type of the joint.
		\param[in]	in_Type	New solver type.
	*/
	SI_Void SetSolverType(EJointSolverType in_Type);

	/*! Returns the stiffness value of the joint.
		\return Stiffness value.
	*/
	SI_Float GetStiffness();

	/*! Changes the stiffness value of the joint.
		\param[in]	in_fValue	New stiffness value.
	*/
	SI_Void SetStiffness(SI_Float in_fValue);

	/*! Returns the stiffness activation flag of the joint.
		\return Stiffness activation flag.
	*/
	SI_Bool GetStiffnessActivation();

	/*! Changes the stiffness activation flag of the joint.
		\param[in]	in_bValue New stiffness activation flag.
	*/
	SI_Void SetStiffnessActivation(SI_Bool in_bValue);

	/*! Returns the resolution plane of this joint
		\return the resolution plane
	*/
	CSLIKResolutionPlane* GetResolutionPlane();

	/*! Creates the resolution plane of this joint
		\return the resolution plane
	*/
	CSLIKResolutionPlane* CreateResolutionPlane();

	/*! Connects and existing resolution plane to this joint
		\param[in] in_pResPlane the resolution plane to connect to
	*/
	SI_Void ConnectResolutionPlane(CSLIKResolutionPlane *in_pResPlane);

	/*! Synchronizes this IK joint instance with its IO layer representation
		\retval SI_Error::SI_SUCCESS this function always returns SI_SUCCESS
	*/
    virtual SI_Error Synchronize();

	/*! Returns the template type
		\retval CSLTemplate::SI_IK_JOINT the template type of the joint
	*/
	virtual ETemplateType Type();

	/*! Returns a handle on one of this template's parameters by using its name
		\param[in] in_szName the name of the parameter to get the handle from
		\return the handle to the parameter
	*/
    virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);

	/*! Validates that the parent is of valid type
		\param[in] in_pNewParent the parent to validate against
		\return whether the parent is valid or not
	*/
	virtual SI_Bool ValidateParent(CSLModel *in_pNewParent);

	CSLVector3DProxy*	GetPreferredRotationProxy(){ return &m_PreferredRotation;};
	CSLBoolProxy*		GetLimitActivationProxy(){ return &m_RotationLimitActivation;};
	CSLVector3DProxy*	GetRotationLimitMinimumProxy(){ return &m_RotationLimitMinimum;};
	CSLVector3DProxy*	GetRotationLimitMaximumProxy(){ return &m_RotationLimitMaximum;};
	CSLBoolProxy*		GetPseudoRootProxy(){ return &m_PseudoRoot;};
	CSLBoolProxy*		GetStiffnessActivationProxy(){ return &m_StiffnessActivation;};
	CSLFloatProxy*		GetStiffnessProxy(){ return &m_Stiffness;};
	CSLFloatProxy*		GetLengthProxy(){ return &m_Length;};

private:
	CSLStrEnumProxy<EJointSolverType, SI_3D> m_SolverType;
	CSLVector3DProxy m_PreferredRotation;
	CSLBoolProxy m_RotationLimitActivation;
	CSLVector3DProxy m_RotationLimitMinimum;
	CSLVector3DProxy m_RotationLimitMaximum;
	CSLBoolProxy m_PseudoRoot;
	CSLBoolProxy m_StiffnessActivation;
	CSLFloatProxy m_Stiffness;
	CSLFloatProxy m_Length;

	CSLIKResolutionPlane *m_pResolutionPlane;

	void *m_pReserved;	// reserved for future extension
};

#endif
