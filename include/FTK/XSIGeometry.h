//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSIGeometry.h
	\brief Defines the CSLXSIGeometry class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _XSIGEOMETRY_H
#define _XSIGEOMETRY_H

#include "Primitive.h"

// Forward declaration
class CSLXSIShapeAnimation;

/*! \brief This class represents an \xx ftk_XSI_Geometry XSI_Geometry \endxx template.

	Base class to handle geometry data for dotXSI 5.0+ (see the \xx ftk_XSI_Geometry XSI_Geometry \endxx
	template reference).
*/
class XSIEXPORT CSLXSIGeometry
	: public CSLPrimitive
{
public:

	/*! Constructor
		\param[in] in_pScene	Pointer to the scene containing the Geometry
		\param[in] in_pModel	Pointer to the model containing the Geometry
		\param[in] in_pTemplate	Pointer to the CdotXSITemplate containing the Geometry
		\return an instance of CSLGeometry
	*/
	CSLXSIGeometry(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	/*! Destructor
	*/
	virtual ~CSLXSIGeometry();

	/*! Creates a new shape animation for the geometry.
		\param[in]	in_Type	Type of interpolation for the new shape animation.
		\return Pointer to the newly created shape animation.
	*/
	virtual CSLXSIShapeAnimation* CreateXSIShapeAnimation(EFCurveInterpolationType in_Type);

	/*! Returns the shape animation of the geometry.
		\return Pointer to the shape animation.
	*/
	virtual CSLXSIShapeAnimation* XSIShapeAnimation();

	/*! Destroys an existing shape animation on the geometry.
		\return Error code.
	*/
	virtual SI_Error DestroyXSIShapeAnimation();

	/*! Connects a shape animation
		\param[in] in_pNewXSIShapeAnim the shape animation to connect
		\return The connected shape animation
	*/
	virtual CSLXSIShapeAnimation* ConnectXSIShapeAnimation(CSLXSIShapeAnimation* in_pNewXSIShapeAnim);

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
	CSLXSIShapeAnimation* m_pXSIShapeAnimation;

	void *m_pReserved;	// reserved for future extension
};

#endif
