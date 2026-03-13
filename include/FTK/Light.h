//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file Light.h
	\brief Defines the CSLLight class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _LIGHT_H
#define _LIGHT_H

#include "Primitive.h"
#include "ConstrainableType.h"
#include "LightInfo.h"

/*! \brief This class represents an \xx ftk_SI_Light SI_Light \endxx template.

Base class for lights (see the \xx ftk_SI_Light SI_Light \endxx
template reference).
*/
class XSIEXPORT CSLLight
	: public CSLPrimitive
	, public CSLConstrainableType
{
public:

	/*! Synchronizes this light instance with its IO layer representation
	* \return SI_Error
	* \retval SI_SUCCESS this function always returns SI_SUCCESS
	*/
    virtual SI_Error Synchronize();

	/*! Gets a handle on one of this light's parameters by using its name
	* \param in_szName the name of the parameter to get the handle from
	* \return CSLAnimatableType* the handle to the parameter
	*/
    virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);

	/*! Gets a handle on one of this light's parameters by using its name and type
	* \param in_szParameterName the name of the parameter to get the handle from
	* \param in_Type the type of the parameter to get the handle from
	* \return CSLAnimatableType* the handle to the parameter
	*/
	virtual CSLAnimatableType* ParameterFromType(EFCurveType in_Type, SI_Char *in_szParameterName);

	/*! Destructor
	*/
	virtual ~CSLLight();

	/*! Return the color of the light.
	* \return CSIBCColorf Light color.
	*/
	CSIBCColorf GetColor();

	/*! Change the color of the light.
	* \param in_rColor New light color.
	* \return SI_Void
	*/
	SI_Void SetColor(CSIBCColorf &in_rColor);

	/*! Return the position of the light.
	* \return CSIBCVector3D Light position.
	*/
	CSIBCVector3D GetPosition();

	/*! Change the position of the light.
	* \param in_rValue New light position.
	* \return SI_Void
	*/
	SI_Void SetPosition(CSIBCVector3D &in_rValue);

	/*! Add a new constraint to the light.
	* \param in_ConstraintType Type of constraint to create.
	* \return CSLConstraint* Pointer to the newly created constraint object.
	*/
	CSLConstraint* AddConstraint(CSLConstraint::EConstraintType in_ConstraintType);

	///////////////////////////////////////////////////////////////////////////
	// light info Functionality /////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	/*! Creates a new light info
	* \return CSLLightInfo* The new light info or null if there's already one
	*/
	CSLLightInfo* CreateLightInfo();

	/*! Destroys the light info
	* \return SI_Error Whether or not the light info could be destroyed
	*/
	SI_Error DestroyLightInfo();

	/*! Connects an exisiting light info
	* \param in_pToConnect Pointer to the light info to use
	* \return CSLLightInfo* The added light info or null if there's already one
	*/
	CSLLightInfo* ConnectLightInfo( CSLLightInfo* in_pToConnect );

	/*! Gets a pointer to the light info
	* \return CSLLightInfo* Pointer to the light info
	*/
	CSLLightInfo* LightInfo();

	CSLColorRGBProxy* GetColorProxy() { return &m_Color;};
    CSLVector3DProxy* GetPositionProxy() { return &m_Position;};

protected:
	CSLLight(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	virtual SI_Bool ConstraintTypeIsValid(CSLConstraint::EConstraintType in_ConstraintType) = 0;

private:
	CSLColorRGBProxy m_Color;
    CSLVector3DProxy m_Position;
	CSLLightInfo *m_pLightInfo;

	void *m_pReserved;	// reserved for future extension
};

#endif
