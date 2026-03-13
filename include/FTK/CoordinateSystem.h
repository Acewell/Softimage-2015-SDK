//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file CoordinateSystem.h
	\brief Defines the CSLCoordinateSystem class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _COORDINATESYSTEM_H
#define _COORDINATESYSTEM_H

#include "Template.h"


/*! \brief This class represents an \xx ftk_SI_CoordinateSystem SI_CoordinateSystem \endxx template.

	Specifies the coordinate system in which transformations are expressed (see the
	\xx ftk_SI_CoordinateSystem SI_CoordinateSystem \endxx template reference).
*/
class XSIEXPORT CSLCoordinateSystem
	: public CSLTemplate
{
public:
	/*! This enum lists the possible hand rotation for the coordinate system.
	*/
	enum EHandRotation
	{
		SI_LEFT_HANDED,		//!<Left handed coordinate system
		SI_RIGHT_HANDED,	//!<Right handed coordinate system
	};

	/*! This enum lists the possible U axis orientation for the coordinate system.
	*/
	enum EUOrientation
	{
		SI_RIGHT_U,			//!<Positive U goes right
		SI_LEFT_U,			//!<Positive U goes left
	};

	/*! This enum lists the possible V axis orientation for the coordinate system.
	*/
	enum EVOrientation
	{
		SI_DOWN_V,			//!<Positive V goes down
		SI_UP_V,			//!<Positive V goes up
	};

	/*! This enum lists the possible X, Y & Z axis orientation for the coordinate system.
	*/
	enum EAxisOrientation
	{
		SI_RIGHT,			//!<Positive X goes right
		SI_LEFT,			//!<Positive X goes left
		SI_UP,				//!<Positive Y goes up
		SI_DOWN,			//!<Positive Y goes down
		SI_IN,				//!<Positive Z goes in
		SI_OUT,				//!<Positive Z goes out
	};

	/*! This enum lists all coordinate system style the class can recognize.
	*/
	enum ECoordinateSystemStyle
	{
		SI_SOFTIMAGE_3D,
		SI_D3D,
		SI_PLAYSTATION,
		SI_NINTENDO,
	};

	/*! Constructor
		\param[in] in_pScene	Pointer to the scene containing the coordinate system
		\param[in] in_pModel	Pointer to the model containing the coordinate system
		\param[in] in_pTemplate	Pointer to the CdotXSITemplate containing the coordinate system
		\return an instance of CSLCoordinateSystem
	*/
	CSLCoordinateSystem(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	/*! Destructor
	*/
	virtual ~CSLCoordinateSystem();

	/*! Returns the hand rotation of the coordinate system.
		\return Hand rotation.
	*/
	EHandRotation			GetHandRotation() { return m_HandRotation; }

	/*! Changes the hand rotation of the coordinate system.
		\param[in]	in_Type	New hand rotation.
	*/
	SI_Void					SetHandRotation(EHandRotation in_Type) { m_HandRotation = in_Type; }

	/*! Returns the orientation of the U axis for texture coordinates.
		\return Orientation of the U axis.
	*/
	EUOrientation			GetUAxisOrientation() { return m_UAxis; }

	/*! Changes the orientation of the U axis for texture coordinates.
		\param[in]	in_Type	New orientation of the U axis.
	*/
	SI_Void					SetUAxisOrientation(EUOrientation in_Type) { m_UAxis = in_Type; }

	/*! Returns the orientation of the V axis for texture coordinates.
		\return Orientation of the V axis.
	*/
	EVOrientation			GetVAxisOrientation() { return m_VAxis; }

	/*! Changes the orientation of the V axis for texture coordinates.
		\param[in]	in_Type	New orientation of the V axis.
	*/
	SI_Void					SetVAxisOrientation(EVOrientation in_Type) { m_VAxis = in_Type; }

	/*! Returns the orientation of the X axis in the coordinate system.
		\return Orientation of the X axis.
	*/
	EAxisOrientation		GetXAxisOrientation() { return m_XAxis; }

	/*! Changes the orientation of the X axis in the coordinate system.
		\param[in]	in_Type	New orientation of the X axis.
	*/
	SI_Void					SetXAxisOrientation(EAxisOrientation in_Type) { m_XAxis = in_Type; }

	/*! Returns the orientation of the Y axis in the coordinate system.
		\return Orientation of the Y axis.
	*/
	EAxisOrientation		GetYAxisOrientation() { return m_YAxis; }

	/*! Changes the orientation of the Y axis in the coordinate system.
		\param[in]	in_Type	New orientation of the Y axis.
	*/
	SI_Void					SetYAxisOrientation(EAxisOrientation in_Type) { m_YAxis = in_Type; }

	/*! Returns the orientation of the Z axis in the coordinate system.
		\return Orientation of the Z axis.
	*/
	EAxisOrientation		GetZAxisOrientation() { return m_ZAxis; }

	/*! Changes the orientation of the Z axis in the coordinate system.
		\param[in]	in_Type	New orientation of the Z axis.
	*/
	SI_Void					SetZAxisOrientation(EAxisOrientation in_Type) { m_ZAxis = in_Type; }

	/*! Changes the coordinate system to reflect a certain 3D environment.
		\param[in] in_Style	New coordinate system style.
	*/
	SI_Void					SetCoordinateSystemStyle(ECoordinateSystemStyle in_Style);

	/*! Returns the template type of the coordinate system
		\return CSLTemplate::SI_COORDINATE_SYSTEM the template type
	*/
	virtual ETemplateType	Type() { return SI_COORDINATE_SYSTEM; }

private:
	CSLEnumProxy<EHandRotation, SI_RIGHT_HANDED>	m_HandRotation;
	CSLEnumProxy<EUOrientation, SI_LEFT>			m_UAxis;
	CSLEnumProxy<EVOrientation, SI_UP>				m_VAxis;
	CSLEnumProxy<EAxisOrientation, SI_OUT>			m_XAxis;
	CSLEnumProxy<EAxisOrientation, SI_OUT>			m_YAxis;
	CSLEnumProxy<EAxisOrientation, SI_OUT>			m_ZAxis;
};

#endif
