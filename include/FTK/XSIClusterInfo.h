//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSIClusterInfo.h
	\brief Defines the CSLXSIClusterInfo class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _XSICLUSTERINFO_H
#define _XSICLUSTERINFO_H

#include "Template.h"

/*! \brief This class represents an \xx ftk_XSI_ClusterInfo XSI_ClusterInfo \endxx template.

Base class to store the cluster type information for dotXSI 5.0+ (see the \xx ftk_XSI_ClusterInfo XSI_ClusterInfo \endxx
template reference).
*/
class XSIEXPORT CSLXSIClusterInfo
	: public CSLTemplate
{
// Methods
public:

	//! Defines the various types of clusters
	enum EClusterType
	{
		SI_POLYGON,				/*!< Polygon type */
		SI_FACE,				/*!< Face type */
		SI_SURFACE_CURVE,		/*!< Surface Curve type */
		SI_KNOT_CURVE_U,		/*!< Knot Curve U type */
		SI_KNOT_CURVE_V,		/*!< Knot Curve V type */
		SI_BOUNDARY,			/*!< Boundary type */
		SI_VERTEX,				/*!< Vertex type */
		SI_EDGE,				/*!< Edge type */
		SI_POLYGON_NODE,		/*!< Polygon Node type */
		SI_SAMPLED_POINT,		/*!< Sampled Point type */
		SI_KNOT,				/*!< Knot type */
		SI_TRIM_CURVE,			/*!< Trim curVE type */
		SI_ISO_LINE_U,			/*!< ISO Line U type */
		SI_ISO_LINE_V,			/*!< ISO Line V type */
		SI_ISO_POINT,			/*!< ISO Point type */
		SI_ISO_LINE,			/*!< ISO Line type */
		SI_SUB_SURFACE,			/*!< SUB Surface type */
		SI_SUB_CURVE,			/*!< SUB Curve type */
	};

	/*! Constructor
		\param[in] in_pScene Pointer to the scene
		\param[in] in_pModel Pointer to the model
		\param[in] in_pTemplate Pointer to the parent template
		\param[in] in_DefaultEClusterType Cluster type to use
	*/
    CSLXSIClusterInfo
	(
		CSLScene* in_pScene,
		CSLModel* in_pModel,
		CdotXSITemplate *in_pTemplate,
		EClusterType in_DefaultEClusterType = SI_VERTEX
	);

	//! Destructor
    virtual ~CSLXSIClusterInfo();

	/*! Sets the cluster type
		\param[in] in_Type New cluster type
	*/
    void SetClusterType( EClusterType in_Type ) { m_ClusterType = in_Type; };

	/*! Returns the cluster type
		\return Current cluster type
	*/
    EClusterType GetClusterType();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_CLUSTER_INFO Template type
	*/
    virtual CSLTemplate::ETemplateType Type();

	virtual SI_Error Synchronize();

	// Members
private:
    CSLStrEnumProxy<EClusterType, SI_SUB_CURVE> m_ClusterType;

	// This member is here to allow future improvement of the class.
	SI_Void *m_pReserved;
};

#endif

