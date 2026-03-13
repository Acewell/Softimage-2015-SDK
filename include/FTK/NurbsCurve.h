//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file NurbsCurve.h
	\brief Defines the CSLNurbsCurve class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _NURBSCURVE_H
#define _NURBSCURVE_H

#include "Geometry.h"

#ifndef _SL_FLOAT_ARRAY_PROXY_EXPORT_
#define _SL_FLOAT_ARRAY_PROXY_EXPORT_

//XSITEMPLATEEXP template class XSIEXPORT CSLArrayProxy<SI_Float, SI_Float, 1>;
//XSITEMPLATEEXP template class XSIEXPORT CSLArrayProxy<CSIBCVector4D, SI_Float, 4>;

#endif // _SL_FLOAT_ARRAY_PROXY_EXPORT_


/*! \brief This class represents an \xx ftk_SI_NurbsCurve SI_NurbsCurve \endxx template.

Describes a single NURBS curve (see the \xx ftk_SI_NurbsCurve SI_NurbsCurve \endxx
template reference).
*/
class XSIEXPORT CSLNurbsCurve
	: public CSLGeometry
{
public:
	/*! Proxy class that allows modifying a list of SI_Float like an array.
	*/
	typedef CSLArrayProxy<SI_Float, SI_Float, 1>		CSLFloatArray;

	/*! Proxy class that allows modifying a list of CSIBCVector4D objects like an array.
	*/
	typedef CSLArrayProxy<CSIBCVector4D, SI_Float, 4> 	CSLVector4DArray;

	/*! The EParametrizationType enum contains possible types for knot parametrization
	*/
	enum EParametrizationType
	{
		SI_UNIFORM,			//!< Uniform parametrization
		SI_NON_UNIFORM,		//!< Non-uniform parametrization
		SI_CHORD_LENGTH,	//!< Chord length parametrization
		SI_CENTRIPETAL,		//!< Centripetal parametrization
	};

	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Refered template
		\return an instance of CSLNurbsCurve
	*/
	CSLNurbsCurve(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	/*! Destructor
	*/
	virtual ~CSLNurbsCurve();

	/*! Returns the degree of the curve.
		\return Degree value.
	*/
	SI_Int					GetDegree();

	/*! Changes the degree of the curve.
		\param[in]	in_nValue	New degree value.
	*/
	SI_Void					SetDegree(SI_Int in_nValue);

	/*! Returns the closed flag of the curve.
		\return Closed flag.
	*/
	SI_Bool					GetClosedFlag();

	/*! Changes the closed flag of the curve.
		\param[in]	in_bValue New closed flag.
	*/
	SI_Void					SetClosedFlag(SI_Bool in_bValue);

	/*! Returns the parametrization type of the curve.
		\return Parametrization type.
	*/
	EParametrizationType	GetParametrization();

	/*! Changes the parametrization type of the curve.
		\param[in]	in_Type	New parametrization type.
	*/
	SI_Void					SetParametrization(EParametrizationType in_Type);

	/*! Returns the number of knots of the curve.
		\return Number of knots.
	*/
	SI_Int					GetKnotCount();

	/*! Returns the knot values array proxy.
		\return Pointer to an array proxy of knots values.
	*/
	CSLFloatArray*			GetKnotList();

	/*! Returns an array of SI_Float containing the knot values.
		\return Array of knots values.
	*/
	SI_Float*				GetKnotListPtr();

	/*! Return the number of control points of the curve.
		\return Number of control points.
	*/
	SI_Int					GetControlPointCount();

	/*! Return the control point values array proxy.
		\return Pointer to an array proxy of control point values.
	*/
	CSLVector4DArray*		GetControlPointList();

	/*! Returns an array of SI_Float containing the control point values.
		\return Array of control point values.
	*/
	CSIBCVector4D*			GetControlPointListPtr();

	/*! Synchronizes this NURBS curve instance with its IO layer representation
		\retval SI_Error::SI_SUCCESS
	*/
    virtual SI_Error Synchronize();

	/*! Returns the template type of the NURBS curve
		\retval CSLTemplate::SI_NURBS_CURVE the template type
	*/
    virtual ETemplateType	Type() { return SI_NURBS_CURVE; }

private:
	CSLIntProxy				m_Degree;
	CSLBoolProxy			m_Closed;
	CSLEnumProxy<EParametrizationType, SI_CENTRIPETAL>	m_Parametrization;
	CSLFloatArray			m_Knots;
	CSLVector4DArray		m_ControlPoints;

	void *m_pReserved;	// reserved for future extension
};

#endif

