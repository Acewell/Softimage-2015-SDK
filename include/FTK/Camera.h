//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file Camera.h
	\brief Defines the CSLCamera class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _CAMERA_H
#define _CAMERA_H

#include "Primitive.h"
#include "ConstrainableType.h"

/*! \brief This class represents an \xx ftk_SI_Camera SI_Camera \endxx template.

	Describes a camera and its interest (see the \xx ftk_SI_Camera SI_Camera \endxx
	template reference).
*/
class XSIEXPORT CSLCamera
	: public CSLPrimitive, public CSLConstrainableType
{
public:

	/*! Constructor
		\param[in] in_pScene	Pointer to the scene containing the Camera
		\param[in] in_pModel	Pointer to the model containing the Camera
		\param[in] in_pTemplate	Pointer to the CdotXSITemplate containing the Camera
	*/
	CSLCamera(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	/*! Destructor
	*/
	virtual ~CSLCamera();

	/*!	Return the far plane of the camera.
		\return Far plane.
	*/
	SI_Float GetFarPlane();

	/*!	Change the far plane of the camera.
		\param[in]	in_fValue	New far plane. value
	*/
	SI_Void SetFarPlane(SI_Float in_fValue);

	/*!	Return the field of view of the camera.
		\return Field of view.
	*/
	SI_Float GetFieldOfView();

	/*!	Change the field of view of the camera.
		\param[in]	in_fValue	New field of view value.
	*/
	SI_Void SetFieldOfView(SI_Float in_fValue);

	/*!	Return the position of the camera's interest.
		\return Interest position.
	*/
	CSIBCVector3D GetInterestPosition();

	/*!	Change the position of the camera's interest.
		\param[in]	in_rValue	New interest position.
	*/
	SI_Void SetInterestPosition(CSIBCVector3D& in_rValue);

	/*!	Return the position of the camera.
		\return Position.
	*/
	CSIBCVector3D GetPosition();

	/*!	Change the position of the camera.
		\param[in]	in_rValue	New position.
	*/
	SI_Void SetPosition(CSIBCVector3D& in_rValue);

	/*!	Return the near plane of the camera.
		\return Near plane value.
	*/
	SI_Float GetNearPlane();

	/*!	Change the near plane of the camera.
		\param[in]	in_fValue	New near plane value.
	*/
	SI_Void SetNearPlane(SI_Float in_fValue);

	/*!	Return the roll of the camera.
		\return Roll.
	*/
	virtual SI_Float GetRoll();

	/*!	Change the roll of the camera.
		\param[in]	in_fValue	New roll value.
	*/
	virtual SI_Void SetRoll(SI_Float in_fValue);

	/*!	Add a new constraint to the camera.
		\param[in]	in_ConstraintType	Type of constraint to create.
		\return Pointer to the newly created constraint object.
	*/
	CSLConstraint* AddConstraint(CSLConstraint::EConstraintType in_ConstraintType);

    virtual SI_Error Synchronize();

    /* Returns the type of this template
    	\retval CSLTemplate::SI_CAMERA Template type
    */
    virtual ETemplateType Type();
    virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);

	/*!	Returns an AnimatableParameter from a EFCurveType.
		\note	The Camera supports the following FCurve types:
			\li \link CSLTemplate::SI_POSITION_X SI_POSITION_X	\endlink
			\li \link CSLTemplate::SI_POSITION_Y SI_POSITION_Y	\endlink
			\li \link CSLTemplate::SI_POSITION_Z SI_POSITION_Z	\endlink
			\li \link CSLTemplate::SI_INTEREST_X SI_INTEREST_X	\endlink
			\li \link CSLTemplate::SI_INTEREST_Y SI_INTEREST_Y	\endlink
			\li \link CSLTemplate::SI_INTEREST_Z SI_INTEREST_Z	\endlink
			\li \link CSLTemplate::SI_ROLL SI_ROLL		\endlink
			\li \link CSLTemplate::SI_FOV SI_FOV			\endlink
			\li \link CSLTemplate::SI_NEAR SI_NEAR		\endlink
			\li \link CSLTemplate::SI_FAR SI_FAR			\endlink
		\param[in]	in_Type				FCurve Type
		\param[in]	in_szParameterName	The name of the parameter if this FCurve this is unknown.
		\return	Animatable parameter

	\eg Adding FCurves on a Camera
	\code
		CSLFCurve* l_pFCurveX = l_pCamera->CreateFCurve( CSLTemplate::SI_POSITION_X, CSLTemplate::SI_CUBIC );
		CSLFCurve* l_pFCurveY = l_pCamera->CreateFCurve( CSLTemplate::SI_POSITION_Y, CSLTemplate::SI_CUBIC );
		CSLFCurve* l_pFCurveZ = l_pCamera->CreateFCurve( CSLTemplate::SI_POSITION_Z, CSLTemplate::SI_CUBIC );

		CSLFCurve* l_pFCurveRoll = l_pCamera->CreateFCurve( CSLTemplate::SI_ROLL, CSLTemplate::SI_CUBIC );

		// Add the keys etc...

	\endcode
	*/
    virtual CSLAnimatableType* ParameterFromType(EFCurveType in_Type, SI_Char *in_szParameterName);

	CSLVector3DProxy* GetInterestPositionProxy() { return &m_InterestPosition;};
	CSLVector3DProxy* GetPositionProxy() { return &m_Position;};
	CSLFloatProxy* GetRollProxy() { return &m_Roll;};
	CSLFloatProxy* GetFOVProxy() { return &m_FieldOfView;};
	CSLFloatProxy* GetNearPlaneProxy() { return &m_NearPlane;};
	CSLFloatProxy* GetFarPlaneProxy() { return &m_FarPlane;};

private:
	CSLVector3DProxy m_InterestPosition;
	CSLVector3DProxy m_Position;
	CSLFloatProxy m_Roll;
	CSLFloatProxy m_FieldOfView;
	CSLFloatProxy m_NearPlane;
	CSLFloatProxy m_FarPlane;

	void *m_pReserved;	// reserved for future extension
};

#endif
