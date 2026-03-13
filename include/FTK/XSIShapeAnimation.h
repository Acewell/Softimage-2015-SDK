//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSIShapeAnimation.h
	\brief Defines the CSLXSIShapeAnimation class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _XSISHAPEANIMATION_H
#define _XSISHAPEANIMATION_H

#include "Template.h"
#include "ActionClip.h"

class CSLXSIShape;
class CSLFCurve;

/*! \brief This class represents an \xx ftk_XSI_ShapeAnimation XSI_ShapeAnimation \endxx template.

	Describes a mesh shape animation for dotXSI 5.0+ (see the
	\xx ftk_XSI_ShapeAnimation XSI_ShapeAnimation \endxx template reference).
	\sa CSLAction
*/
class XSIEXPORT CSLXSIShapeAnimation
	: public CSLTemplate
{
public:
	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate referred template
		\param[in] in_Type Default interpolation type
	*/
	CSLXSIShapeAnimation(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate, EFCurveInterpolationType in_Type);
	virtual ~CSLXSIShapeAnimation();

	/*! Adds a new shape at the end of the animation.
		\return Pointer to the newly created shape.
	*/
	CSLXSIShape*				AddXSIShape();

	/*! Inserts a new shape into the animation.
		\note Animation is inserted at the end of the list if the index is out of bounds
		\param[in]	in_nIndex	Index of insertion of the new shape.
		\return Pointer to the newly created shape.
	*/
	CSLXSIShape*				InsertXSIShape(SI_Int in_nIndex);

	/*! Returns the number of shapes in the animation.
		\return Number of shapes.
	*/
	SI_Int						GetXSIShapeCount();

	/*!	Returns an array of all shapes in the animation.
		\return	Pointer to the array of pointers to shape objects.
	*/
	CSLXSIShape**				XSIShapes();

	/*! Removes a single shape from the animation.
		\param[in]	in_nIndex	Index of the shape to remove.
		\retval SI_Error::SI_SUCCESS The animation was removed
		\retval SI_Error::SI_ERR_BAD_ARGUMENT Invalid index
	*/
	SI_Error					RemoveXSIShape(SI_Int in_nIndex);

	/*!	Removes a single shape from the animation.
		\param[in]	in_pObject	Pointer to the shape to remove.
		\retval SI_Error::SI_SUCCESS The animation was removed
		\retval SI_Error::SI_ERR_BAD_ARGUMENT Shape was not found
	*/
	SI_Error					RemoveXSIShape(CSLXSIShape* in_pObject);

	/*!	Removes all shapes from the shape animation.
		\retval	SI_Error::SI_SUCCESS
	*/
	SI_Error					ClearXSIShapes();

	/*!	Returns the fcurve containing the animation of the shape.
		\return Pointer to a fcurve object.
	*/
	CSLFCurve*					Animation();

	/*!	Verifies if we have an animation fcurve, if not, it creates the template of the fcurve,
		creates the semantic layer object of the fcurve and connect it to the template.
		\return Pointer to a fcurve containing the animation of the shape (new or existing one).
	*/
	CSLFCurve*					AddAnimation();

	// Connection functions;
	CSLFCurve*					ConnectAnimation(CSLFCurve *in_pNewAnimation);
	CSLXSIShape*				ConnectXSIShape(CSLXSIShape* in_pNewShape, SI_Int in_nIndex);

	/*!	Returns the first action clip that uses this shape as a source.
		\param[in] in_pShape Shape source for finding action clip
		\return Pointer on the action clip if found, NULL if not.
	*/
	CSLActionClip*				GetFirstActionClipByShape(CSLXSIShape* in_pShape);

	virtual SI_Error Fix();
    virtual SI_Error Synchronize();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_SHAPE_ANIMATION Template type
	*/
    virtual ETemplateType Type() { return XSI_SHAPE_ANIMATION; }

protected:
	virtual CSLXSIShape*		CreateXSIShape();

private:
	CSIBCArray<CSLXSIShape *>	m_XSIShapes;
	CSLFCurve*					m_pAnimation;
	CSLStrEnumProxy<EFCurveInterpolationType, SI_CUBIC>		m_InterpolationType;

	void *m_pReserved;	// reserved for future extension
};

#endif
