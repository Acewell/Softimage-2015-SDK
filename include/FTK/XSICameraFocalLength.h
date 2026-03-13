//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSICameraFocalLength.h
	\brief Defines the CSLXSICameraFocalLength class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _XSICAMERAFOCALLENGTH_H
#define _XSICAMERAFOCALLENGTH_H

#include "Template.h"

/*! \brief This class represents an \xx ftk_XSI_CameraFocalLength XSI_CameraFocalLength \endxx template.

	Base class to handle camera focal length functionality for dotXSI 5.0+ (see the
	\xx ftk_XSI_CameraFocalLength XSI_CameraFocalLength \endxx template reference).
*/
class XSIEXPORT CSLXSICameraFocalLength
	: public CSLTemplate
{
public:

	/*! Constructor
		\param[in] in_pScene	Pointer to the scene containing the Camera
		\param[in] in_pModel	Pointer to the model containing the Camera
		\param[in] in_pTemplate	Pointer to the CdotXSITemplate containing the Camera
		\return an instance of CSLCamera
	*/
	CSLXSICameraFocalLength(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	/*! Destructor
	*/
	virtual ~CSLXSICameraFocalLength();

	/*! Returns the camera projection plane distance.
		\return the camera projection plane distance.
	*/
	SI_Float GetFocalLength();

	/*! Changes the camera projection plane distance.
		\param[in] in_lValue New camera projection plane distance.
	*/
	SI_Void SetFocalLength(SI_Float in_lValue);


	/*! Returns the type of this template
		\retval CSLTemplate::XSI_CAMERA_FOCALLENGTH The type of this template
	*/
	virtual ETemplateType			Type() { return XSI_CAMERA_FOCALLENGTH; }

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
		\param[in] in_szName the name of the parameter to get the handle from (in case type wasn't found)
		\return the handle to the parameter
	*/
    virtual CSLAnimatableType* ParameterFromType(EFCurveType in_Type, SI_Char *in_szName);

	/*!	Returns the name (string) of a specified sub parameter.
		\param[in]	in_pParameter	The sub parameter
		\return Name of the sub parameter.
	*/
    virtual const SI_Char* GetParameterName(CSLAnimatableType* in_pParameter);

	CSLFloatProxy*	GetFocalLengthProxy() { return &m_FocalLength; };

private:

	CSLFloatProxy	m_FocalLength;

	void *m_pReserved;	// reserved for future extension
};

#endif
