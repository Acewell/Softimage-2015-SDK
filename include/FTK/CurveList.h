//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file CurveList.h
	\brief Defines the CSLCurveList class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _CURVELIST_H
#define _CURVELIST_H

#include "Primitive.h"

// Forward declaration
class CSLNurbsCurve;

/*! \brief This class represents an \xx ftk_XSI_CurveList XSI_CurveList \endxx template.

	Describes a list of NURBS curves (see the \xx ftk_XSI_CurveList XSI_CurveList \endxx
	template reference).
*/
class XSIEXPORT CSLCurveList
	: public CSLPrimitive
{
public:

	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Refered template
		\return an instance of CSLCurveList
	*/
	CSLCurveList(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	/*! Destructor
	*/
	virtual ~CSLCurveList();

	/*!	Adds a new curve to the list.
		\return Pointer to the newly created curve.
	*/
	CSLNurbsCurve* AddCurve();

	/*!	Returns the number of curves in the list.
		\return Number of curves.
	*/
	SI_Int GetCurveCount();

	/*!	Returns an array of all curves in the list.
		\return Array of pointers to curve objects.
	*/
	CSLNurbsCurve** Curves();

	/*!	Removes a single curve from the list.
		\param[in]	in_nIndex	Index of the curve to remove.
		\return Error code.
	*/
	SI_Error RemoveCurve(SI_Int in_nIndex);

	/*!	Removes a single curve from the list.
		\param[in]	in_pCurve	Pointer to the curve to remove.
		\return Error code.
	*/
	SI_Error RemoveCurve(CSLNurbsCurve* in_pCurve);

	/*!	Removes all curves from the list.
		\return Error code.
	*/
	SI_Error ClearCurves();

	/*! Connects a NURBS curve to this curve list
		\param[in] in_pNewCurve the new NURBS curve to connect
		\return the connected NURBS curve
	*/
	CSLNurbsCurve* ConnectCurve(CSLNurbsCurve* in_pNewCurve);

	/*! Synchronizes this curve list instance with its IO layer representation
		\retval SI_Error::SI_SUCCESS this function always returns SI_SUCCESS
	*/
    virtual SI_Error Synchronize();

	/*! Returns the template type of the curve list
		\return CSLTemplate::SI_CURVE_LIST the template type
	*/
    virtual ETemplateType Type();

private:
	CSIBCArray<CSLNurbsCurve *> m_Curves;

	void *m_pReserved;	// reserved for future extension
};

#endif
