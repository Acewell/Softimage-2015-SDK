//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file Angle.h
	\brief Defines the CSLAngle class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _ANGLE_H
#define _ANGLE_H

#include "Template.h"

/*! \brief This class represents an \xx ftk_SI_Angle SI_Angle \endxx template.

	Defines the way angles are expressed in the scene (see the \xx ftk_SI_Angle SI_Angle \endxx
	template reference).  You can retrieve the angle type with the CSLScene:Angle method.
	\note This template is ignored when imported into Autodesk Softimage, although
		a warning appears if the angle is not expressed in degrees.
	\sa CSLScene
*/
class XSIEXPORT CSLAngle
    : public CSLTemplate
{
public:

	//! Angle units
	enum EAngleType
	{
		SI_DEGREES,	/*!< Angles are expressed in degrees */
		SI_RADIANS	/*!< Angles are expressed in radians */
	};

	/*! Constructor
		\param[in] in_pScene Pointer to the scene containing the CSLAngle
		\param[in] in_pModel Pointer to the model containing the CSLAngle
		\param[in] in_pTemplate Pointer to the CdotXSITemplate defining the CSLAngle
	*/
	CSLAngle
	(
		CSLScene* in_pScene,
		CSLModel *in_pModel,
		CdotXSITemplate* in_pTemplate
	);

	~CSLAngle();

	/*! Returns the angle type
		\return The angle type
	*/
    EAngleType GetAngleType();

	/*! Sets the angle type
		\param[in] in_Type The angle type
	*/
    void SetAngleType( EAngleType in_Type );

	/*! Returns the type of this template
		\retval CSLTemplate::SI_ANGLE Template type
	*/
    inline ETemplateType Type();

	CSLEnumProxy<EAngleType, SI_RADIANS>* GetAngleProxy() { return &m_Angle;};

private:
    CSLEnumProxy<EAngleType, SI_RADIANS> m_Angle;
	SI_Void *in_pReserved;	// reserved for future extension
};

#endif
