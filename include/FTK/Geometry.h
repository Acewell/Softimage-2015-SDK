//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file Geometry.h
	\brief Defines the CSLGeometry class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _GEOMETRY_H
#define _GEOMETRY_H

#include "Primitive.h"

// Forward declaration
class CSLShapeAnimation;

/*! \brief Class representing Geometry
*/
class XSIEXPORT CSLGeometry
	: public CSLPrimitive
{
public:

	/*! Constructor
		\param[in] in_pScene	Pointer to the scene containing the Geometry
		\param[in] in_pModel	Pointer to the model containing the Geometry
		\param[in] in_pTemplate	Pointer to the CdotXSITemplate containing the Geometry
		\return an instance of CSLGeometry
	*/
	CSLGeometry(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	/*! Destructor
	*/
	virtual ~CSLGeometry();

	/*! Create a new shape animation for the geometry.
		\param[in]	in_Type	Type of interpolation for the new shape animation.
		\return Pointer to the newly created shape animation.
	*/
	CSLShapeAnimation* CreateShapeAnimation(EFCurveInterpolationType in_Type);

	/*! Return the shape animation of the geometry.
		\return Pointer to the shape animation.
	*/
	CSLShapeAnimation* ShapeAnimation();

	/*! Destroy an existing shape animation on the geometry.
		\return Error code.
	*/
	SI_Error DestroyShapeAnimation();

	/*! Connects a shape animation
		\param[in] in_pNewShapeAnim* the shape animation to connect
		\return The connected shape animation
	*/
	CSLShapeAnimation* ConnectShapeAnimation(CSLShapeAnimation* in_pNewShapeAnim);

	/*! Synchronizes this geometry instance with its IO layer representation
		\retval SI_Error::SI_SUCCESS this function always returns SI_SUCCESS
	*/
    virtual SI_Error Synchronize();

	/*! Returns a handle on one of this geometry's parameters by using its name
		\param[in] in_szName the name of the parameter to get the handle from
		\return the handle to the parameter
	*/
    virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);

private:
	CSLShapeAnimation* m_pShapeAnimation;

	void *m_pReserved;	// reserved for future extension
};

#endif
