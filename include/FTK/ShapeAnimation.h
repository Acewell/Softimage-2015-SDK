//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file ShapeAnimation.h
	\brief Defines the CSLShapeAnimation class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _SHAPEANIMATION_H
#define _SHAPEANIMATION_H

#include "Template.h"

class CSLBaseShape;
class CSLFCurve;

/*! \brief This class represents an \xx ftk_SI_ShapeAnimation SI_ShapeAnimation \endxx template.

	Describes a mesh, surface or curve shape animation (see the
	\xx ftk_SI_ShapeAnimation SI_ShapeAnimation \endxx template reference).
	\sa CSLAction
*/
class XSIEXPORT CSLShapeAnimation
	: public CSLTemplate
{
public:
	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate referred template
		\param[in] in_Type Default interpolation type
	*/
	CSLShapeAnimation(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate, EFCurveInterpolationType in_Type);
	virtual ~CSLShapeAnimation();

	/*! Adds a new shape at the end of the animation.
		\return Pointer to the newly created shape.
	*/
	CSLBaseShape*				AddShape();

	/*! Inserts a new shape into the animation.
		\note Animation is inserted at the end of the list if the index is out of bounds
		\param[in]	in_nIndex	Index of insertion of the new shape.
		\return Pointer to the newly created shape.
	*/
	CSLBaseShape*				InsertShape(SI_Int in_nIndex);

	/*! Returns the number of shapes in the animation.
		\return Number of shapes.
	*/
	SI_Int						GetShapeCount();

	/*!	Returns an array of all shapes in the animation.
		\return	Pointer to the array of pointers to shape objects.
	*/
	CSLBaseShape**				Shapes();

	/*! Removes a single shape from the animation.
		\param[in]	in_nIndex	Index of the shape to remove.
		\retval SI_Error::SI_SUCCESS The animation was removed
		\retval SI_Error::SI_ERR_BAD_ARGUMENT Invalid index
	*/
	SI_Error					RemoveShape(SI_Int in_nIndex);

	/*!	Removes a single shape from the animation.
		\param[in]	in_pObject	Pointer to the shape to remove.
		\retval SI_Error::SI_SUCCESS The animation was removed
		\retval SI_Error::SI_ERR_BAD_ARGUMENT Shape was not found
	*/
	SI_Error					RemoveShape(CSLBaseShape* in_pObject);

	/*!	Removes all shapes from the shape animation.
		\retval SI_Error::SI_SUCCESS
	*/
	SI_Error					ClearShapes();

	/*!	Returns the fcurve containing the animation of the shape.
		\return Pointer to a fcurve object.
	*/
	CSLFCurve*					Animation();

	// Connection functions;
	CSLFCurve*					ConnectAnimation(CSLFCurve *in_pNewAnimation);
	CSLBaseShape*				ConnectShape(CSLBaseShape* in_pNewShape, SI_Int in_nIndex);

	virtual SI_Error Fix();
    virtual SI_Error Synchronize();

	/*! Returns the type of this template
		\retval CSLTemplate::SI_SHAPE_ANIMATION Template type
	*/
    virtual ETemplateType Type() { return SI_SHAPE_ANIMATION; }

protected:
	CSLBaseShape*				CreateShape();

private:
	CSIBCArray<CSLBaseShape *>	m_Shapes;
	CSLFCurve*					m_pAnimation;
	CSLStrEnumProxy<EFCurveInterpolationType, SI_CUBIC>		m_InterpolationType;

	void *m_pReserved;	// reserved for future extension
};

#endif
