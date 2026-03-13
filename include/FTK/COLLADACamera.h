//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file COLLADACamera.h
	\brief Defines the CSLCOLLADACamera class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _COLLADACAMERA_H
#define _COLLADACAMERA_H

#include "Camera.h"

/*! \brief This class represents a camera in COLLADA.

	Describes a camera and its interest.
*/
class XSIEXPORT CSLCOLLADACamera
	: public CSLCamera
{
public:

	/*! Constructor
		\param[in] in_pScene	Pointer to the scene containing the Camera
		\param[in] in_pModel	Pointer to the model containing the Camera
		\param[in] in_pTemplate	Pointer to the CdotXSITemplate containing the Camera
	*/
	CSLCOLLADACamera(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	/*! Destructor
	*/
	virtual ~CSLCOLLADACamera();

	/*!	Return the roll of the camera.
		\return Roll.
	*/
	virtual SI_Float GetRoll();

	/*!	Change the roll of the camera.
		\param[in]	in_fValue	New roll value.
	*/
	virtual SI_Void SetRoll(SI_Float in_fValue);

	virtual SI_Error Synchronize();

	CSLVector3DProxy* GetVectorUpProxy() { return &m_VectorUp;};

private:

	CSLVector3DProxy m_VectorUp;
	void *m_pReserved;	// reserved for future extension
};

#endif
