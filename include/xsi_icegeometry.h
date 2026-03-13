//*****************************************************************************
/*!
	\file xsi_icegeometry.h
	\brief CICEGeometry class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIICEGEOMETRY_H__
#define __XSIICEGEOMETRY_H__

namespace XSI {

class MATH::CMatrix4f;
class CLongArray;
class CDoubleArray;
class ICENodeContext;

//*****************************************************************************
/*! \class CICEGeometry xsi_icegeometry.h
	\brief Provides a read-only API for accessing the data of a geometry object connected to a custom ICE node.

	\idx dirty states:checking for geometry changes \endidx
	The following geometry types are supported:
		\li CICEGeometry::siMeshSurfaceType: mesh surface.
		\li CICEGeometry::siNurbsSurfaceType: nurbs surface.
		\li CICEGeometry::siNurbsCurveType: nurbs curve.
		\li CICEGeometry::siPointCloudType: point cloud.
		\li CICEGeometry::siGroupType: grouped geometries.

	This API can handle single geometries or a composite of multiple, or \a grouped, geometries. For grouped
	geometries, CICEGeometry virtually unifies the sub-geometries as one single geometry which allows data to be
	accessed as if it were actually a single geometry. For instance, calling CICEGeometry::GetPointPositionCount
	on a grouped geometry returns the total number of points for all sub-geometries.

	\note Geometries can be grouped together with the \xl GroupGeometryNode or by adding them to a Group in	the Softimage scene.

	CICEGeometry is typically used in the \xt cb_ICENode_BeginEvaluate BeginEvaluate \endxt callback but can also be used in all
	custom \xt cb_icenodes ICENode evaluation callbacks \endxt. However, it cannot be used from an \xt cb_ICENode_Evaluate Evaluate \endxt
	callback in multi-thread mode with a non-singleton context. Calls to CICEGeometry methods will just return default values in
	this context. Also, CICEGeometry can only be used with specific geometry ports defined with the following types:

		\li type: ::siICENodeDataGeometry
		\li structure: ::siICENodeStructureSingle
		\li context: ::siICENodeContextSingleton

	The CICEGeometry class can also be used to interrogate connected geometries about their states. The states supported are:
		\li CICEGeometry::siTransformationDirtyState: This state is true when the transformation of the geometry has been changed
			(translation, rotation or scaling).
		\li CICEGeometry::siPointPositionDirtyState: This state is true when the point position of the geometry has been changed.
		\li CICEGeometry::siTopologyDirtyState: This state is true when the topology of the geometry has been changed. When
			\c siTopologyDirtyState is true, it implies that \c siPointPositionDirtyState is also true.
		\li CICEGeometry::siGeometryTypeDirtyState: This state is true when the type of geometry has been changed. When this state
			is true all other states are also true.

	CICEGeometry only supports geometry-centric states. Use CICEPortState to query for the low-level port states of connected geometries.

	\note CICEGeometry::siAnyDirtyState can be used to test if at least one state is dirty.

	\since 8.0 (2010)

	\eg Simple example to demonstrate the %CICEGeometry API. For a more detailed example see the
		\xm CustomICENodes/netview_CustomICENodes PointGeneratorFromGeometry custom ICE node \endxm example
	\code
	XSIPLUGINCALLBACK CStatus Sample_RegisterNode( ICENodeContext& in_ctxt )
	{
		ICENodeDef nodeDef = Application().GetFactory().CreateICENodeDef(L"Sample",L"Sample");

		nodeDef.AddInputPort(	ID_IN_GeometryPortID, ID_G_100,
								siICENodeDataGeometry,siICENodeStructureSingle,siICENodeContextSingleton,
								L"geometry input", L"geometry input" );

		// Rest of the code omitted for brievity ...

		return CStatus::OK;
	}

	XSIPLUGINCALLBACK CStatus Sample_BeginEvaluate( ICENodeContext& in_ctxt )
	{
		CICEGeometry geom( in_ctxt, ID_IN_GeometryPortID  );

		// Geometry data are provided as a flat list of values
		CDoubleArray points;
		geom.GetPointPositions( points ) ;

		XSI::MATH::CMatrix4f transfo;
		geom.GetTransformation( transfo );

		std::vector< MATH::CVector3f >* pUserData = new std::vector< MATH::CVector3f >;

		ULONG nCount = geom.GetPolygonCount();

		CLongArray sizes;	// sizes holds the number of points per polygon
		CLongArray indices;	// indices holds the polygon indices and are used for indexing the point values
		geom.GetPolygonIndices( sizes, indices );

		// Compute the center point of all polygons and save the result in a user data.
		ULONG nOffset = 0;
		for (ULONG i=0; i<nCount; i++)
		{
			MATH::CVector3f vTotal;
			for (ULONG j=0; j<(ULONG)sizes[i]; j++, nOffset++)
			{
				MATH::CVector3f v(	(float)points[ indices[nOffset]*3 ],
									(float)points[ indices[nOffset]*3+1 ],
									(float)points[ indices[nOffset]*3+2 ] );
				vTotal += v;
			}

			vTotal *= 1.0f/sizes[i];

			// The points are relative to the geometry and must be converted to global coordinates.
			vTotal.MulByMatrix4InPlace( transfo );
			pUserData->push_back( vTotal );
		}

		return CStatus::OK;
	}

	XSIPLUGINCALLBACK CStatus Sample_Evaluate( ICENodeContext& in_ctxt )
	{
		ULONG out_portID = in_ctxt.GetEvaluatedOutputPortID( );

		switch( out_portID )
		{
			case ID_OUT_Sample_Points:
			{
				// Retrieve the points computed in Sample_BeginEvaluate
				std::vector<MATH::CVector3f>* pUserData = (std::vector<MATH::CVector3f>*)(CValue::siPtrType)in_ctxt.GetUserData( );

				CDataArrayVector3f outData( in_ctxt );

				CIndexSet indexSet( in_ctxt );
				for(CIndexSet::Iterator it = indexSet.Begin(); it.HasNext(); it.Next())
				{
					// Note: The output buffer is relative to the 'batch' data therefore the batch can be
					// indexed with the iterator directly. As for the user data vector, pUSerData must be
					// indexed with the 'batch' global index i.e. CIndexSet::Iterator::GetAbsoluteIndex()
					outData[it] = (*pUserData)[ it.GetAbsoluteIndex() ];
				}
			}
			break;
		};

		return CStatus::OK;
	}

	XSIPLUGINCALLBACK CStatus Sample_EndEvaluate( ICENodeContext& in_ctxt )
	{
		// Release the memory allocated for the user data

		CValue userData = in_ctxt.GetUserData( );
		if (userData.IsEmpty())
		{
			return CStatus::OK;
		}

		std::vector<MATH::CVector3f>* pUserData = (std::vector<MATH::CVector3f>*)(CValue::siPtrType)userData;

		if (pUserData)
			delete pUserData;

		in_ctxt.PutUserData( CValue() );

		return CStatus::OK;
	}

	\endcode

	\eg Example to demonstrate querying the geometry states on geometries connected to a custom node. For a more detailed example
		see the \xm CustomICENodes/netview_CustomICENodes PortStateObserver custom ICE node \endxm example.
	\code
	static void _LogGeometryStates( CICEGeometry& in_geom, const CString& in_portName, double in_dCurrentFrame, bool in_bClearState )
	{
		if ( in_geom.IsDirty( CICEGeometry::siAnyDirtyState ) )
		{
			bool bTypeDirtyState = in_geom.IsDirty( CICEGeometry::siGeometryTypeDirtyState );
			bool bTransfoDirtyState = in_geom.IsDirty( CICEGeometry::siTransformationDirtyState );
			bool bPointsDirtyState = in_geom.IsDirty( CICEGeometry::siPointPositionDirtyState );
			bool bTopologyDirtyState = in_geom.IsDirty( CICEGeometry::siTopologyDirtyState );

			if ( in_bClearState )
			{
				in_geom.ClearState();
			}

			Application app;

			// Don't log redundant information:
			// bTypeDirtyState always implies bTransfoDirtyState + bPointsDirtyState + bTopologyDirtyState
			// bTopologyDirtyState always implies bPointsDirtyState

			if ( bTypeDirtyState)
			{
				app.LogMessage( ">>> Port " + in_portName + " siGeometryTypeDirtyState at frame " + CString(in_dCurrentFrame) + " is dirty" );
			}
			else
			{
				if ( bTransfoDirtyState)
				{
					app.LogMessage( ">>> Port " + in_portName + " siTransformationDirtyState at frame " + CString(in_dCurrentFrame) + " is dirty" );
				}

				if ( bTopologyDirtyState)
				{
					app.LogMessage( ">>> Port " + in_portName + " siTopologyDirtyState at frame " + CString(in_dCurrentFrame) + " is dirty" );
				}
				else if ( bPointsDirtyState)
				{
					app.LogMessage( ">>> Port " + in_portName + " siPointPositionDirtyState at frame " + CString(in_dCurrentFrame) + " is dirty" );
				}
			}
		}
	}

	static void LogGeometryStates( CICEGeometry& in_geom, const CString& in_portName, double in_dCurrentFrame )
	{
		CICEGeometry::Type geomtype = in_geom.GetGeometryType();
		switch( geomtype )
		{
			case CICEGeometry::siGroupType:
			{
				// Note: ClearState on sub-geometries will clear the states for the entire group geometry. It's
				// recommended to call ClearState only on the group geometry to avoid inconsistencies.
				_LogGeometryStates( in_geom, in_portName, in_dCurrentFrame, false );

				for (ULONG i=0; i<in_geom.GetSubGeometryCount(); i++)
				{
					CICEGeometry subgeom = in_geom.GetSubGeometry(i);
					_LogGeometryStates( subgeom, in_portName + CString(i), in_dCurrentFrame, false );
				}
				in_geom.ClearState();
			}
			break;

			default:
			{
				_LogGeometryStates( in_geom, in_portName, in_dCurrentFrame, true );
			}
		}
	}

	XSIPLUGINCALLBACK CStatus Port_State_Observer_BeginEvaluate( ICENodeContext& in_ctxt )
	{
		CICEGeometry geomGroup( in_ctxt, ID_IN_GeometryGroup );
		CICEGeometry geomCurve( in_ctxt, ID_IN_NurbsCurve );
		CICEGeometry geomMesh( in_ctxt, ID_IN_MeshSurf );
		CICEGeometry geomNurbsSurf( in_ctxt, ID_IN_NurbsSurf );
		CICEGeometry geomCloud( in_ctxt, ID_IN_PointCloud );

		double dCurrentFrame = in_ctxt.GetTime();
		LogGeometryStates( geomGroup, L"GeometryGroup", dCurrentFrame );
		LogGeometryStates( geomCurve, L"NurbsCurve", dCurrentFrame );
		LogGeometryStates( geomMesh, L"MeshSurf", dCurrentFrame );
		LogGeometryStates( geomNurbsSurf, L"NurbsSurf", dCurrentFrame );
		LogGeometryStates( geomCloud, L"PointCloud", dCurrentFrame );

		return CStatus::OK;
	}

	\endcode
 */
//*****************************************************************************

class SICPPSDKDECL CICEGeometry
{
	public:
	friend class ICENodeContext;

	/*! Defines the geometry types supported by CICEGeometry.
	*/
	enum Type
	{
		siNoneType			=0,	/*!< No geometry */
		siGroupType			=1,	/*!< %Group of geometries */
		siMeshSurfaceType	=2,	/*!< Mesh surface geometry */
		siNurbsSurfaceType	=3,	/*!< Nurbs surface geometry */
		siNurbsCurveType	=4,	/*!< Nurbs curve geometry */
		siPointCloudType	=5	/*!< %Point cloud geometry */
	};

	/*! Defines the supported dirty geometry state types.
	*/
	enum DirtyState
	{
		siGeometryTypeDirtyState	= 1<<0, /*!< This state is true when the type of geometry has been changed.
													When this state is true all other states are also true. */
		siTransformationDirtyState	= 1<<1, /*!< This state is true when the transformation of the geometry has been changed
													(translation, rotation or scaling). */
		siPointPositionDirtyState	= 1<<2, /*!< This state is true when the point position of the geometry has been changed. */
		siTopologyDirtyState		= 1<<3,	/*!< This state is true when the topology of the geometry has been changed. When
													\c siTopologyDirtyState is true, it implies that \c siPointPositionDirtyState
													is also true. */
		siAnyDirtyState				= siGeometryTypeDirtyState|
									  siTransformationDirtyState|
									  siPointPositionDirtyState|
									  siTopologyDirtyState /*!< This state is true if any one of the states have changed. */
	};

	/*! Constructor for creating and initializing an instance of CICEGeometry.
	\param in_ctxt ICENode evaluation context.
	\param in_nInputPortID Input port identifier.
	\param in_nInstanceIndex The group instance of the port. Defaults to \c 0.
	*/
	CICEGeometry( ICENodeContext& in_ctxt, ULONG in_nInputPortID, ULONG in_nInstanceIndex=0 ) ;

	/*! Copy Constructor.
	*/
	CICEGeometry( const CICEGeometry& in_geom );

	/*! Default Constructor. Creates an invalid CICEGeometry object of type Type::siNoneType.
	*/
	CICEGeometry( );

	/*! Destructor.
	*/
	~CICEGeometry();

	/*! Returns true if the object is valid. Unless the object is not set properly, IsValid always return true. IsValid cannot be used
	to detect if a geometry is connected or not. The rational behind is that it's not guaranteed that all connected geometries have
	data, therefore having geometries always set as valid allows users to write generic code. For instance, unconnected geometries,
	empty polygon geometries and empty point clouds will all return 0 for CICEGeometry::GetPointPositionCount.

	In general it's not recommended for a custom node to check for valid port connections. For instance, a custom node could be
	connected to a passthrough node which could be potentially not connected to any node. If you want to optimize things based on the
	port state then it is recommended to use the CICEPortState class and perform actions based on specific notifications.

	\return True if valid, false otherwise.
	*/
	bool IsValid() const;

	/*! Returns the geometry type. The type is set to Type::siNoneType when the object is not properly defined.
	\return The geometry type.
	*/
	Type GetGeometryType() const;

	/*! Equality operator. Tests if two geometries are the same; the function is just comparing the
	internal pointer objects.
	\param in_geom CICEGeometry instance to compare to this instance.
	\return true if both geometries are he same, false if different.
	*/
	bool operator == (const CICEGeometry& in_geom) const;

	/*! Inequality operator. Tests whether two geometries are different; the function is just comparing the
	internal pointer objects.
	\param in_geom CICEGeometry instance to compare to this instance.
	\return true if both geometries are different, false otherwise.
	*/
	bool operator != (const CICEGeometry& in_geom) const;

	/*! Assignment operator. Assign this geometry to another geometry. This operation is a simple object
	assignment. The content of the geometry is not duplicated.
	\param in_geom CICEGeometry object to assign.
	\return A reference to new CICEGeometry.
	*/
	CICEGeometry& operator = (const CICEGeometry& in_geom) ;

	/*! Returns the number of sub-geometries contained by this geometry.
	\return Number of sub-geometries.
	*/
	ULONG GetSubGeometryCount() const;

	/*! Returns the sub-geometry at the position identified by \c in_index. The CICEGeometry instance
	returned is invalid if \c in_index is out of bounds.
	\return CICEGeometry instance.
	*/
	CICEGeometry GetSubGeometry( ULONG in_index ) const;

	/*! Returns the number of point positions on the current geometry.
	\return Number of point positions.
	*/
	ULONG GetPointPositionCount() const;

	/*! Returns an array of double values containing the point positions (\c xyz) of the entire geometry.
	The positions are stored as a flat list and can be indexed using the indices returned by
	CICEGeometry::GetPolygonIndices, CICEGeometry::GetTrianglePointIndices or CICEGeometry::GetSegmentIndices.

	The array is formatted as: \code {x0,y0,z0, ... xN,yN,zN} \endcode

	\retval out_points Array of point positions.
	\return CStatus::OK Success.
	\return CStatus::AccessDenied Object is invalid or method called from invalid context.

	\eg Example to demonstrate how to access the points of a geometry.
	\code
	CICEGeometry geom( in_ctxt, ID_IN_geometry );

	CDoubleArray points;
	geom.GetPointPositions( points ) ;

	ULONG nCount = geom.GetPolygonCount();

	CLongArray sizes;
	CLongArray indices;
	geom.GetPolygonIndices( sizes, indices );

	ULONG nOffset = 0;
	std::vector< MATH::CVector3f > v3fArray;
	for (ULONG i=0; i<nCount; i++)
	{
		for (ULONG j=0; j<(ULONG)sizes[i]; j++, nOffset++)
		{
			MATH::CVector3f v(	(float)points[ indices[nOffset]*3 ],
								(float)points[ indices[nOffset]*3+1 ],
								(float)points[ indices[nOffset]*3+2 ] );
			v3fArray.push_back( v );
		}
	}
	\endcode
	*/
	CStatus GetPointPositions( CDoubleArray& out_points ) const;

	/*! Returns the number of triangles in the geometry.
	\return %Triangle count.
	*/
	ULONG GetTriangleCount() const;

	/*! Returns an array containing the point indices for each triangulated polygon. The point indices are stored in
	the array as a flat list of values grouped in triplets, the first triplet being the points of triangle \c 0, etc.
	The triangle indices are numbered based on the order of creation of the triangles.

	The array is formatted as: \code {t0<p0,p1,p2>, t1<p0,p1,p2>... tN<p0,p1,p2>} \endcode

	\note This method performs a triangulation of the current geometry before returning the data.

	\retval out_indices Array of triangle point indices.
	\return CStatus::OK Success.
	\return CStatus::AccessDenied Object is invalid or method called from invalid context.

	\eg Example to demonstrate how to access the triangle points of a geometry.
	\code
	CICEGeometry geom( in_ctxt, ID_IN_geometry );

	CDoubleArray points;
	geom.GetPointPositions( points ) ;

	ULONG nCount = geom.GetTriangleCount();

	CLongArray indices;
	geom.GetTrianglePointIndices( indices );

	ULONG nOffset = 0;
	std::vector< MATH::CVector3f > v3fArray;
	for (ULONG i=0; i<nCount; i++)
	{
		for (ULONG j=0; j<3; j++, nOffset++)
		{
			MATH::CVector3f v(	(float)points[ indices[nOffset]*3 ],
								(float)points[ indices[nOffset]*3+1 ],
								(float)points[ indices[nOffset]*3+2 ] );
			v3fArray.push_back( v );
		}
	}
	\endcode
	*/
	CStatus GetTrianglePointIndices( CLongArray& out_indices ) const;

	/*! Returns the number of polygons of the geometry.
	\return Polygon count.
	*/
	ULONG GetPolygonCount() const;

	/*! Returns the size and point indices for all polygons on the geometry.

	\retval out_sizes Array containing the point count for each polygon.
	\retval out_indices Array containing the point indices for each Polygon. The vertices are stored
		as a flat list and ordered by polygons, the first group being the points for polygon \c 0, etc.
		<br/><br/>The array is formatted as: \code {poly0<v0,v1..vN>, poly1<v0,v1..vN>... polyN<v0,v1..vN>} \endcode

	\return CStatus::OK Success.
	\return CStatus::AccessDenied Object is invalid or method called from invalid context.

	\eg Example to demonstrate how to access the polygon points of a geometry.
	\code
	CICEGeometry geom( in_ctxt, ID_IN_geometry );

	CDoubleArray points;
	geom.GetPointPositions( points ) ;

	ULONG nCount = geom.GetPolygonCount();

	CLongArray sizes;
	CLongArray indices;
	geom.GetPolygonIndices( sizes, indices );

	ULONG nOffset = 0;
	std::vector< MATH::CVector3f > v3fArray;
	for (ULONG i=0; i<nCount; i++)
	{
		for (ULONG j=0; j<(ULONG)sizes[i]; j++, nOffset++)
		{
			MATH::CVector3f v(	(float)points[ indices[nOffset]*3 ],
								(float)points[ indices[nOffset]*3+1 ],
								(float)points[ indices[nOffset]*3+2 ] );
			v3fArray.push_back( v );
		}
	}
	\endcode
	*/
	CStatus GetPolygonIndices( CLongArray& out_sizes, CLongArray& out_indices ) const;

	/*! Returns the number of segments for the geometry. %Segment is a generic term to describe 1D geometry
	components such as edges for mesh surfaces and control points for nurbs surfaces.
	\return %Segment count.
	*/
	ULONG GetSegmentCount() const;

	/*! Returns an array of segment indices. %Segment is a generic term to describe 1D geometry components
	such as edges for mesh surfaces and control points for nurbs surfaces. The array contains a sequence of
	pairs describing the segment indices:	\code {s0<id0,id1>, ...sN<id0,id1>} \endcode

	The indices can be used with CICEGeometry::GetPointPositions to get the segment points.

	\retval out_indices Array of edge indices.

	\return CStatus::OK Succeeded.
	\return CStatus::AccessDenied Object is invalid or method called from invalid context.

	\eg Example to demonstrate how to access the segment points of a geometry.
	\code
	CICEGeometry geom( in_ctxt, ID_IN_geometry );

	CDoubleArray points;
	geom.GetPointPositions( points ) ;

	ULONG nCount = geom.GetSegmentCount();

	CLongArray indices;
	geom.GetSegmentIndices( sizes, indices );

	ULONG nOffset = 0;
	std::vector< MATH::CVector3f > v3fArray;
	for (ULONG i=0; i<nCount; i++)
	{
		for (ULONG j=0; j<2; j++, nOffset++)
		{
			MATH::CVector3f v(	(float)points[ indices[nOffset]*3 ],
								(float)points[ indices[nOffset]*3+1 ],
								(float)points[ indices[nOffset]*3+2 ] );
			v3fArray.push_back( v );
		}
	}
	\endcode
	*/
	CStatus GetSegmentIndices( CLongArray& out_indices ) const;

	/*! Returns the global transformation matrix of this geometry.
	\note %Geometry points are returned in local coordinates; use the geometry transformation matrix to convert
		the points to global coordinates.

	\retval out_mat44 Transformation matrix.
	\return CStatus::OK Succeeded.
	\return CStatus::AccessDenied Object is invalid or method called from invalid context.
	*/
	CStatus GetTransformation( XSI::MATH::CMatrix4f& out_mat44 ) const;

	/*! Returns the dirty state of this geometry for a given state type as defined in the CICEGeometry::DirtyState enumerator.
	By default, IsDirty returns true if at least one of the geometry states is dirty.
	\note Changing the transformation on a sub-geometry object will force a CICEGeometry::siPointPositionDirtyState
		change on the grouped geometry. However, no CICEGeometry::siTransformationDirtyState will be generated for
		the group geometry.
	\param in_flag State type.
	\return true if the object is dirty, false otherwise.
	*/
	bool IsDirty( unsigned short in_flag=siAnyDirtyState ) const;

	/*! Clears the geometry states.
	\note ClearState on sub-geometries will clear the states for the entire group geometry. It is recommended to call ClearState
		only on the group geometry to avoid inconsistencies.
	*/
	void ClearState( );

	private:
	CStatus Init( const ICENodeContext& in_ctxt, ULONG in_nInputPortID, ULONG in_nInstanceIndex );

	Type	m_geomType;
	ULONG	m_nInputPortID;
	ULONG	m_nID;
	void*	m_pParent;
	void*	m_pGeom;
	void*	m_pCtxt;
};

};

#endif // __XSIICEGEOMETRY_H__
