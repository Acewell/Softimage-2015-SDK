//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSICamera.h
	\brief Defines the CSLXSICamera class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _XSICAMERA_H
#define _XSICAMERA_H

#include "Primitive.h"

class CSLXSICameraFocalLength;

/*! \brief This class represents an \xx ftk_XSI_Camera XSI_Camera \endxx template.

	Base class to handle camera functionality for dotXSI 5.0+ (see the \xx ftk_XSI_Camera XSI_Camera \endxx
	template reference).
*/
class XSIEXPORT CSLXSICamera
	: public CSLPrimitive
{
public:

	/*! Constructor
		\param[in] in_pScene	Pointer to the scene containing the Camera
		\param[in] in_pModel	Pointer to the model containing the Camera
		\param[in] in_pTemplate	Pointer to the CdotXSITemplate containing the Camera
		\return an instance of CSLCamera
	*/
	CSLXSICamera(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	/*! Destructor
	*/
	virtual ~CSLXSICamera();

	/*! Returns the camera field of view dominance.
		\return the camera field of view dominance.
	*/
	SI_Int GetStandard();

	/*! Changes the camera field of view dominance.
		\param[in] in_lValue New camera field of view dominance.
	*/
	SI_Void SetStandard(SI_Int in_lValue);

	/*! Returns the camera picture ratio.
		\return the camera picture ratio.
	*/
	SI_Float GetPictureRatio();

	/*! Changes the camera picture ratio.
		\param[in] in_lValue New camera picture ratio.
	*/
	SI_Void SetPictureRatio(SI_Float in_lValue);

	/*! Returns the camera field of view.
		\return the camera field of view.
	*/
	SI_Float GetFieldOfView();

	/*! Changes the camera field of view.
		\param[in] in_lValue New camera field of view.
	*/
	SI_Void SetFieldOfView(SI_Float in_lValue);

	/*! Returns the camera field of view dominance.
		\return the camera field of view dominance.
	*/
	SI_Int GetFieldOfViewType();

	/*! Changes the camera field of view dominance.
		\param[in] in_lValue New camera field of view dominance.
	*/
	SI_Void SetFieldOfViewType(SI_Int in_lValue);

	/*! Returns the camera projection type.
		\return the camera projection type.
	*/
	SI_Int GetProjectionType();

	/*! Changes the camera projection type.
		\param[in] in_lValue New camera projection type.
	*/
	SI_Void SetProjectionType(SI_Int in_lValue);

	/*! Returns the camera orthographic height.
		\return the camera orthographic height.
	*/
	SI_Float GetOrthoHeight();

	/*! Changes the camera orthographic height.
		\param[in] in_lValue New camera orthographic height.
	*/
	SI_Void SetOrthoHeight(SI_Float in_lValue);

	/*! Returns the camera interest distance.
		\return the camera interest distance.
	*/
	SI_Float GetInterestDistance();

	/*! Changes the camera interest distance.
		\param[in] in_lValue New camera interest distance.
	*/
	SI_Void SetInterestDistance(SI_Float in_lValue);

	/*! Returns the camera near clipping plane.
		\return the camera near clipping plane.
	*/
	SI_Float GetNearPlane();

	/*! Changes the camera near clipping plane.
		\param[in] in_lValue New camera near clipping plane.
	*/
	SI_Void SetNearPlane(SI_Float in_lValue);

	/*! Returns the camera far clipping plane.
		\return the camera far clipping plane.
	*/
	SI_Float GetFarPlane();

	/*! Changes the camera far clipping plane.
		\param[in] in_lValue New camera far clipping plane.
	*/
	SI_Void SetFarPlane(SI_Float in_lValue);

	/*! Returns the camera projection plane.
		\return the camera projection plane.
	*/
	SI_Bool GetProjectionPlaneEnable();

	/*! Changes the camera projection plane.
		\param[in] in_lValue New camera projection plane.
	*/
	SI_Void SetProjectionPlaneEnable(SI_Bool in_lValue);

	/*! Returns the camera projection plane width.
		\return the camera projection plane width.
	*/
	SI_Float GetProjPlaneWidth();

	/*! Changes the camera projection plane width.
		\param[in] in_lValue New camera projection plane width.
	*/
	SI_Void SetProjPlaneWidth(SI_Float in_lValue);

	/*! Returns the camera projection plane height.
		\return the camera projection plane height.
	*/
	SI_Float GetProjPlaneHeight();

	/*! Changes the camera projection plane height.
		\param[in] in_lValue New camera projection plane height.
	*/
	SI_Void SetProjPlaneHeight(SI_Float in_lValue);

	/*! Return the camera projection plane offset X.
		\return the camera projection plane offset X.
	*/
	SI_Float GetProjPlaneOffsetX();

	/*! Changes the camera projection plane offset X.
		\param[in] in_lValue New camera projection plane offset X.
	*/
	SI_Void SetProjPlaneOffsetX(SI_Float in_lValue);

	/*! Returns the camera projection plane offset Y.
		\return the camera projection plane offset Y.
	*/
	SI_Float GetProjPlaneOffsetY();

	/*! Changes the camera projection plane offset Y.
		\param[in] in_lValue New camera projection plane offset Y.
	*/
	SI_Void SetProjPlaneOffsetY(SI_Float in_lValue);

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_CAMERA The type of this template
	*/
	virtual ETemplateType			Type() { return XSI_CAMERA; }

	/*! Synchronizes this Camera instance with its IO layer representation
		\retval SI_Error::SI_SUCCESS this function always returns SI_SUCCESS
	*/
    virtual SI_Error Synchronize();

	/*! Returns a handle on one of this Camera's parameters by using its name
		\param[in] in_szName the name of the parameter to get the handle from
		\return the handle to the parameter
	*/
    virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);

	/*! Returns a handle on one of this Camera's parameters by using its type
		\param[in] in_Type the type of the parameter to get the handle from
		\param[in] in_szName the name of the parameter to get the handle from (in case type is not found)
		\return the handle to the parameter
	*/
    virtual CSLAnimatableType* ParameterFromType(EFCurveType in_Type, SI_Char *in_szName);

	/*!	Returns the name (string) of a specified sub parameter.
		\param[in]	in_pParameter	The sub parameter
		\return Name of the sub parameter.
	*/
    virtual const SI_Char* GetParameterName(CSLAnimatableType* in_pParameter);

	CSLIntProxy*	GetStandardProxy() { return &m_Standard;};
	CSLFloatProxy*	GetPictureRatioProxy() { return &m_PictureAspect;};
	CSLFloatProxy*	GetFieldOfViewProxy() { return &m_Fov;};
	CSLIntProxy*	GetFieldOfViewTypeProxy() { return &m_FovType;};
	CSLIntProxy*	GetProjectionTypeProxy() { return &m_ProjType;};
	CSLFloatProxy*	GetOrthoHeightProxy() { return &m_OrthoHeight;};
	CSLFloatProxy*	GetInterestDistanceProxy() { return &m_InterestDistance;};
	CSLFloatProxy*	GetNearPlaneProxy() { return &m_NearPlane;};
	CSLFloatProxy*	GetFarPlaneProxy() { return &m_FarPlane;};
	CSLBoolProxy*	GetProjectionPlaneEnableProxy() { return &m_useProjPlane;};
	CSLFloatProxy*	GetProjPlaneWidthProxy() { return &m_ProjPlaneWidth;};
	CSLFloatProxy*	GetProjPlaneHeightProxy() { return &m_ProjPlaneHeight;};
	CSLFloatProxy*	GetProjPlaneOffsetXProxy() { return &m_ProjPlaneOffsetX;};
	CSLFloatProxy*	GetProjPlaneOffsetYProxy() { return &m_ProjPlaneOffsetY;};

	CSLXSICameraFocalLength*	CreateXSICameraFocalLength();
	CSLXSICameraFocalLength*	GetXSICameraFocalLength();
	CSLXSICameraFocalLength*	ConnectXSICameraFocalLength(CSLXSICameraFocalLength* in_pToConnect);

private:

	CSLIntProxy		m_Standard;
	CSLFloatProxy	m_PictureAspect;
	CSLFloatProxy	m_Fov;
	CSLIntProxy		m_FovType;
	CSLIntProxy		m_ProjType;
	CSLFloatProxy	m_OrthoHeight;
	CSLFloatProxy	m_InterestDistance;
	CSLFloatProxy	m_NearPlane;
	CSLFloatProxy	m_FarPlane;
	CSLBoolProxy	m_useProjPlane;
	CSLFloatProxy	m_ProjPlaneWidth;
	CSLFloatProxy	m_ProjPlaneHeight;
	CSLFloatProxy	m_ProjPlaneOffsetX;
	CSLFloatProxy	m_ProjPlaneOffsetY;
	CSLXSICameraFocalLength*	m_pXSICameraFocalLength;

	void *m_pReserved;	// reserved for future extension
};

#endif
