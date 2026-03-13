//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file NurbsSurface.h
	\brief Defines the CSLNurbsSurface class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _NURBSSURFACE_H
#define _NURBSSURFACE_H

#include "Geometry.h"


#ifndef _SL_FLOAT_ARRAY_PROXY_EXPORT_
#define _SL_FLOAT_ARRAY_PROXY_EXPORT_

//XSITEMPLATEEXP template class XSIEXPORT CSLArrayProxy<SI_Float, SI_Float, 1>;
//XSITEMPLATEEXP template class XSIEXPORT CSLArrayProxy<CSIBCVector4D, SI_Float, 4>;

#endif // _SL_FLOAT_ARRAY_PROXY_EXPORT_

class CSLNurbsProjection;
class CSLNurbsTrim;


/*! \brief This class represents an \xx ftk_SI_NurbsSurface SI_NurbsSurface \endxx template.

Describes a single NURBS surface (see the \xx ftk_SI_NurbsSurface SI_NurbsSurface \endxx
template reference).
*/
class XSIEXPORT CSLNurbsSurface
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
		\return an instance of CSLNurbsSurface
	*/
	CSLNurbsSurface(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	/*! Destructor
	*/
	virtual ~CSLNurbsSurface();

	/*! Validates the content of this NURBS surface and fixes it if necessary
		\return whether the fix has been successful
	*/
	virtual SI_Error		Fix();

	/*! Synchronizes this NURBS surface instance with its IO layer representation
		\retval SI_Error::SI_SUCCESS this function always returns SI_SUCCESS
	*/
    virtual SI_Error Synchronize();

	/*! Returns the template type of the NURBS surface
		\retval CSLTemplate::SI_NURBS_SURFACE the template type
	*/
    virtual ETemplateType	Type() { return SI_NURBS_SURFACE; }

	/*! Returns the degree of the surface in the U direction.
		\return Degree value in U.
	*/
	SI_Int					GetUDegree();

	/*! Changes the degree of the surface in the U direction.
		\param[in]	in_nValue	New degree value in U.
	*/
	SI_Void					SetUDegree(SI_Int in_nValue);

	/*! Returns the degree of the surface in the V direction.
		\return Degree value in V.
	*/
	SI_Int					GetVDegree();

	/*! Changes the degree of the surface in the V direction.
		\param[in]	in_nValue	New degree value in V.
	*/
	SI_Void					SetVDegree(SI_Int in_nValue);

	/*! Returns the closed flag of the surface in the U direction.
		\return Closed flag in U.
	*/
	SI_Bool					GetUClosedFlag();

	/*! Changes the closed flag of the surface in the U direction.
		\param[in]	in_nValue New closed flag in U.
	*/
	SI_Void					SetUClosedFlag(SI_Bool in_nValue);

	/*! Returns the closed flag of the surface in the V direction.
		\return Closed flag in V.
	*/
	SI_Bool					GetVClosedFlag();

	/*! Changes the closed flag of the surface in the V direction.
		\param[in]	in_nValue New closed flag in V.
	*/
	SI_Void					SetVClosedFlag(SI_Bool in_nValue);

	/*! Returns the parametrization type of the surface.
		\return Parametrization type.
	*/
	EParametrizationType	GetParametrization();

	/*! Changes the parametrization type of the surface.
		\param[in]	in_Type	New parametrization type.
	*/
	SI_Void					SetParametrization(EParametrizationType in_Type);

	/*! Return the number of knots of the surface in the U direction.
		\return Number of knots in U.
	*/
	SI_Int					GetUKnotCount();

	/*! Return the knot values array proxy in the U direction.
		\return Pointer to an array proxy of knots values in U.
	*/
	CSLFloatArray*			GetUKnotList();

	/*! Returns an array of SI_Float containing the knot values in the U direction.
		\return Array of knots values in U.
	*/
	SI_Float*				GetUKnotListPtr();

	/*! Return the number of knots of the surface in the V direction.
		\return Number of knots in V.
	*/
	SI_Int					GetVKnotCount();

	/*! Return the knot values array proxy in the V direction.
		\return Pointer to an array proxy of knots values in V.
	*/
	CSLFloatArray*			GetVKnotList();

	/*! Returns an array of SI_Float containing the knot values in the V direction.
		\return Array of knots values in V.
	*/
	SI_Float*				GetVKnotListPtr();

	/*! Returns the number of control points of the surface in the U direction.
		\return Number of control points in U.
	*/
	SI_Int					GetUControlPointCount();

	/*! Changes the number of control points of the surface in the U direction.
		\param[in]	in_nValue	New number of control points in U.
	*/
	SI_Void					SetUControlPointCount(SI_Int in_nValue);

	/*! Returns the number of control points of the surface in the V direction.
		\return Number of control points in V.
	*/
	SI_Int					GetVControlPointCount();

	/*! Changes the number of control points of the surface in the V direction.
		\param[in]	in_nValue	New number of control points in V.
	*/
	SI_Void					SetVControlPointCount(SI_Int in_nValue);

	/*! Returns the total number of control points of the surface.
		\return Number of knots.
	*/
	SI_Int					GetControlPointCount();

	/*! Returns the control point values array proxy.
		\return Pointer to an array proxy of indexed normals.
	*/
	CSLVector4DArray*		GetControlPointList();

	/*! Returns an array of SI_Float containing the control point values.
		\return Array of control point values.
	*/
	CSIBCVector4D*			GetControlPointListPtr();

	///////////////////////////////////////////////////////////////////////////
	// Nurbs projection functionnality ////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	/*! Adds an nurbs projection to the nurbs surface
		\note The scene must support 3.6 to add a nurbs projection
		\return Pointer to the newly added nurbs projection
	*/
	CSLNurbsProjection* AddNurbsProjection();

	/*! Removes a nurbs projection from the nurbs surface
		\param[in] in_nIndex Index of the nurbs projection to remove
		\return Whether or not the nurbs projection could be removed
	*/
	SI_Error RemoveNurbsProjection( SI_Int in_nIndex );

	/*! Removes an nurbs projection from the nurbs surface
		\param[in] in_pToRemove Pointer to the nurbs projection to remove
		\return Whether or not the nurbs projection could be removed
	*/
	SI_Error RemoveNurbsProjection( CSLNurbsProjection* in_pToRemove );

	/*! Removes all nurbs projections from the nurbs surface
		\return Whether or not the list could be cleared
	*/
	SI_Error ClearNurbsProjections();

	/*! Adds an exisiting nurbs projection to the nurbs surface
		\param[in] in_pToConnect Pointer to the nurbs projection to add
		\return The added nurbs projection or null if it already exists in the list
	*/
	CSLNurbsProjection* ConnectNurbsProjection( CSLNurbsProjection* in_pToConnect );

	/*! Returns an array of all nurbs projection contained on this nurbs surface
		\return Pointer to the list
		\note The scene must support 3.6 to add a nurbs projection
	*/
	CSLNurbsProjection** GetNurbsProjections();

	/*! Returns the total number of nurbs projections
		\return Number of nurbs projections
	*/
	SI_Int GetNurbsProjectionCount();

	/*! Searches for a given nurbs projection
		\param[in] in_szNurbsProjectionName Name of the nurbs projection to look for
		\return Pointer to the nurbs projection or null if it cannot be found
	*/
	CSLNurbsProjection* FindNurbsProjection( SI_Char* in_szNurbsProjectionName );

	///////////////////////////////////////////////////////////////////////////
	// Nurbs trim functionnality //////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	/*! Adds an nurbs trim to the nurbs surface
		\return Pointer to the newly added nurbs trim
	*/
	CSLNurbsTrim* AddNurbsTrim();

	/*! Removes a nurbs trim from the nurbs surface
		\note The scene must support 3.6 to add a nurbs trim
		\param[in] in_nIndex Index of the nurbs trim to remove
		\return Whether or not the nurbs trim could be removed
	*/
	SI_Error RemoveNurbsTrim( SI_Int in_nIndex );

	/*! Removes an nurbs trim from the nurbs surface
		\param[in] in_pToRemove Pointer to the nurbs trim to remove
		\return Whether or not the nurbs trim could be removed
	*/
	SI_Error RemoveNurbsTrim( CSLNurbsTrim* in_pToRemove );

	/*! Removes all nurbs trims from the nurbs surface
		\return Whether or not the list could be cleared
	*/
	SI_Error ClearNurbsTrims();

	/*! Adds an exisiting nurbs trim to the nurbs surface
		\param[in] in_pToConnect Pointer to the nurbs trim to add
		\return The added nurbs trim or null if it already exists in the list
	*/
	CSLNurbsTrim* ConnectNurbsTrim( CSLNurbsTrim* in_pToConnect );

	/*! Returns an array of all nurbs trims contained on this nurbs surface
		\note The scene must support 3.6 to add a nurbs trim
		\return Pointer to the list
	*/
	CSLNurbsTrim** GetNurbsTrims();

	/*! Returns the total number of nurbs trims
		\return Number of nurbs trims
	*/
	SI_Int GetNurbsTrimCount();

	/*! Searches for a given nurbs trim
		\param[in] in_szNurbsTrimName Name of the nurbs trim to look for
		\return Pointer to the nurbs trim or null if it cannot be found
	*/
	CSLNurbsTrim* FindNurbsTrim( SI_Char* in_szNurbsTrimName );

private:
	CSLIntProxy 			m_UDegree;
	CSLIntProxy 			m_VDegree;
	CSLBoolProxy			m_UClosed;
	CSLBoolProxy			m_VClosed;
	CSLEnumProxy<EParametrizationType, SI_CENTRIPETAL>	m_Parametrization;
	CSLIntProxy 			m_NbUControlPoints;
	CSLIntProxy 			m_NbVControlPoints;
	CSLFloatArray			m_UKnots;
	CSLFloatArray			m_VKnots;
	CSLVector4DArray		m_ControlPoints;
	CSIBCArray<CSLNurbsProjection*> m_NurbsProjections;
	CSIBCArray<CSLNurbsTrim*> m_NurbsTrims;

	void *m_pReserved;	// reserved for future extension
};

#endif
