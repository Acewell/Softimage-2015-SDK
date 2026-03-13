//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file Transform.h
	\brief Defines the CSLTransform class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "Template.h"

/*! \brief This class represents an \xx ftk_SI_Transform SI_Transform \endxx template.

	This class handles the transformation matrix of a model (see the
	\xx ftk_SI_Transform SI_Transform \endxx template reference). It provides functions to set
	the local scaling, rotation and position of the model and also provides easy and fast
	access to the model's global tranform.
*/
class XSIEXPORT CSLTransform
    : public CSLTemplate
{
public:
    CSLTransform(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
    virtual ~CSLTransform();

	/*!	Returns the transformation matrix.
		\return Transformation matrix.
	*/
	CSIBCMatrix4x4 GetMatrix();

	/*!	Changes the transformation matrix.
		\param[in]	in_rValue	New Transformation matrix.
	*/
	SI_Void SetMatrix(CSIBCMatrix4x4 &in_rValue);

	/*!	Returns the actual rotation in euler representation.
		\return Rotation value.
	*/
	CSIBCVector3D GetEulerRotation();

	/*!	Changes the rotation value in euler representation.
		\param[in]	in_rValue	New rotation value
	*/
	SI_Void SetEulerRotation(CSIBCVector3D &in_rValue);

	/*!	Returns the actual scale.
		\return Scale value.
	*/
	CSIBCVector3D GetScale();

	/*!	Changes the scale value.
		\param[in]	in_rValue	New scale value
	*/
	SI_Void SetScale(CSIBCVector3D &in_rValue);

	/*!	Returns the actual translation.
		\return Translation value.
	*/
	CSIBCVector3D GetTranslation();

	/*!	Changes the translation value.
		\param[in]	in_rValue	New translation value
	*/
	SI_Void SetTranslation(CSIBCVector3D &in_rValue);

	/*!	Computes this CSLTransform's local matrix.
	\return	Error code
	*/
	SI_Error ComputeLocalMatrix();

	/*!	Computes this CSLTransform's global matrix.
	\return	Error code
	*/
	SI_Error ComputeGlobalMatrix();

	/*!	Returns the global matrix
		\return The global matrix
	*/
	CSIBCMatrix4x4 &GetGlobalMatrix();

	/*!	Sets the global transformation matrix.
		\param[in]	in_rValue	New Transformation matrix.
	*/
	SI_Void SetGlobalMatrix(CSIBCMatrix4x4 &in_rValue);

	virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);
    virtual CSLAnimatableType* ParameterFromType(EFCurveType in_Type, SI_Char *in_szParameterName);

    /*! Returns the type of this template
    	\retval CSLTemplate::SI_TRANSFORM Template type
    */
    virtual ETemplateType Type();

private:
    CSLVector3DProxy m_Scale;
    CSLVector3DProxy m_Rotation;
    CSLVector3DProxy m_Translation;
	CSIBCMatrix4x4 m_TransformMatrix;
	CSIBCMatrix4x4 m_GlobalMatrix;

	void *m_pReserved;	// reserved for future extension
};

#endif
