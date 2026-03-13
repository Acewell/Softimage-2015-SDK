//*****************************************************************************
/*!
   \file xsi_geometry.h
   \brief Geometry class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIGEOMETRY_H__
#define __XSIGEOMETRY_H__

#include <xsi_siobject.h>
#include <xsi_math.h>
#include <xsi_longarray.h>
#include <xsi_doublearray.h>
#include <xsi_cluster.h>
#include <xsi_clusterproperty.h>
#include <xsi_pointlocatordata.h>
#include <xsi_vector3.h>

namespace XSI {

class CFacetRefArray;
class CSegmentRefArray;
class CPointRefArray;
class CSampleRefArray;
class CRefArray;
class CTriangleRefArray;
class ICEAttribute;

namespace MATH {
class CTransformation;
};

//*****************************************************************************
/*! \class Geometry xsi_geometry.h
	\brief The Geometry class gives access to a X3DObject's geometry. Geometry is the base class for specific geometry
	classes such as PolygonMesh and NurbsSurfaceMesh.

	\sa Cluster, ClusterProperty, Facet, Segment, Point, NurbsSurfaceMesh, NurbsSurface, PolygonMesh,
		PolygonFace, Edge, Vertex

	\eg
	\code
		using namespace XSI;
		Application app;
		Model root = app.GetActiveSceneRoot();

		X3DObject myGrid;
		root.AddGeometry( L"Grid", L"MeshSurface", L"", myGrid );

		Geometry geom( myGrid.GetActivePrimitive().GetGeometry(0) );

		CPointRefArray points( geom.GetPoints() );

		app.LogMessage( L"Number of points: " +
						CValue(points.GetCount()).GetAsText() );
	\endcode
 */
//*****************************************************************************

class SICPPSDKDECL Geometry : public SIObject
{
public:
	/*! Default constructor. */
	Geometry();

	/*! Default destructor. */
	~Geometry();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	Geometry(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	Geometry(const Geometry& in_obj);

	/*! Returns true if a given class type is compatible with this API class.
	\param in_ClassID class type.
	\return true if the class is compatible, false otherwise.
	*/
	bool IsA( siClassID in_ClassID) const;

	/*! Returns the type of the API class.
	\return The class type.
	*/
	siClassID GetClassID() const;

	/*! Creates an object from another object. The newly created object is set to
	empty if the input object is not compatible.
	\param in_obj constant class object.
	\return The new Geometry object.
	*/
	Geometry& operator=(const Geometry& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new Geometry object.
	*/
	Geometry& operator=(const CRef& in_ref);

	/*! Returns an array of Facet objects on this geometry.
	\return Array of references to Facet objects
	\sa Facet, Geometry::GetPoints, Geometry::GetSegments, Geometry
	*/
	CFacetRefArray		GetFacets() const;

	/*! Returns an array of Segment objects on this geometry.
	\return Array of references to Segment objects
	\sa Segment, Geometry::GetPoints, Geometry::GetFacets, Geometry
	*/
	CSegmentRefArray	GetSegments() const;

	/*! Returns an array of Point objects on this geometry.
	\return Array of references to Point objects.
	\sa Point
	*/
	CPointRefArray		GetPoints() const;

	/*! Returns an array of Sample objects on this geometry.
	\return Array of references to Sample objects.
	\sa Sample, Facet::GetSamples
	*/
	CSampleRefArray		GetSamples() const;

	/*! Returns an array of Cluster objects on this geometry.
	\return Array of references to Cluster objects.
	\sa Cluster
	*/
	CRefArray			GetClusters() const;

	/*! Returns an array of Triangle objects on this geometry.
	\return Array of references to Triangle objects.
	\sa Facet, Geometry::GetPoints, Geometry::GetSegments, Geometry::GetFacets,
	*/
	CTriangleRefArray	GetTriangles() const;

	/*! Creates and adds a partial or complete cluster to this geometry.
	\param in_type Type of cluster, such as ::siVertexCluster, ::siEdgeCluster, etc.  See the ::ClusterTypes enum for a complete list.
	\param in_name Name of the new cluster
	\param in_indices Array of cluster indices.  If an empty array is sent then a complete cluster is created. A complete cluster
		represents all the elements of the geometry and will remain complete even as new elements are added to the geometry. It is
		not possible to remove elements from such a cluster.
	\param io_cluster Newly created Cluster
	\return CStatus::OK success
	\return CStatus::Fail failure
	\sa ::ClusterTypes, Cluster
	*/
	CStatus	AddCluster(	const CString& in_type,
						const CString& in_name,
						const CLongArray& in_indices,
						Cluster& io_cluster);

	/*! Creates and adds an empty cluster to this geometry.
	\param in_type Type of cluster
	\param in_name Name of the new cluster
	\param io_cluster Newly created Cluster
	\return CStatus::OK success
	\return CStatus::Fail failure
	\sa ClusterTypes, Cluster
	*/
	CStatus	AddEmptyCluster(
						const CString& in_type,
						const CString& in_name,
						Cluster& io_cluster);

	/*! Creates a PointLocatorData containing surface locations corresponding to the specified Points of the geometry (or all Points
	if not specified).

	In the case of a NurbsSurfaceMesh, there is no direct relationship between the points (control vertices) and the surface. In that
	case, the returned point locators correspond to the surface locations most influenced by each input control vertex.

	\note The returned point locators can be evaluated on any %Geometry instance having the same topology.

	\param in_nbPoints Number of points indices passed in in_pPoints. To specify all points in geometry, use \c -1. In that case,
		the \c in_pPoints argument will be ignored.
	\param in_pPoints %Point indices (not used if in_pPoints is -1)
	\return A new PointLocatorData object (CRef::IsValid == false if failed)

	\sa PolygonMesh::ConstructPointLocators, NurbsSurfaceMesh::ConstructPointLocators
	\since 5.0

	\eg This example uses point locators to place a null positioned and oriented to a surface location corresponding to each
		control vertex of the NURBS sphere.

	\code
		void CreateNullsAtPointLocations( X3DObject& inObj, const PointLocatorData& inPointLocators )
		{
			Geometry geom( inObj.GetActivePrimitive().GetGeometry() );

			std::vector<double> posData, normData;
			posData.resize(inPointLocators.GetCount()*3);
			normData.resize(inPointLocators.GetCount()*3);

			geom.EvaluatePositions(inPointLocators, -1, 0, &posData.front());
			geom.EvaluateNormals(inPointLocators, siInterpolatedVertexGeometricNormals, -1, 0, &normData.front());

			MATH::CVector3 trans;
			MATH::CRotation rot;

			LONG i;
			for (i = 0; i < (LONG)posData.size(); i+=3)
			{
				Null nullObj;
				inObj.AddNull(L"",nullObj);

				trans.Set(posData[i], posData[i+1], posData[i+2]);
				nullObj.PutLocalTranslation(trans);

				trans.Set(normData[i], normData[i+1], normData[i+2]);
				rot.SetFromXYZAxes( trans, trans, trans );
				nullObj.PutLocalRotation(rot);
			}
		}

		void main()
		{
			Application app;
			Model root = app.GetActiveSceneRoot();

			X3DObject meshSphereObj;
			root.AddGeometry( L"Sphere", L"MeshSurface", L"", meshSphereObj );
			PolygonMesh meshSphereGeom( meshSphereObj.GetActivePrimitive().GetGeometry() );

			PointLocatorData pointLocatorsFromSpherePoints = meshSphereGeom.GetSurfacePointLocatorsFromPoints();

			CreateNullsAtPointLocations(meshSphereObj, pointLocatorsFromSpherePoints);
		}
	\endcode
	*/
	PointLocatorData GetSurfacePointLocatorsFromPoints
	(
		LONG in_nbPoints = -1,
		const LONG* in_pPoints = NULL
	) const;

	/*! Creates a PointLocatorData object containing the closest surface locations from the specified input positions. By default,
	input positions have to be defined in the object's local space reference.

	Some aspects of the closest locations computation such as the reference pose or the method (closest surface, closest vertex or
	knot, ...) can be set up using Geometry::SetupPointLocatorQueries. This setup will affect all subsequent calls to
	Geometry::GetClosestLocations, Geometry::GetClosestLocationsWithinRadius or Geometry::GetRaycastIntersections.

	When you call this function an acceleration cache is automatically created. See Geometry::SetupPointLocatorQueries for
	more information.

	\note The "closest distance" relationship may change relative to the spatial reference of the geometry and the input
		positions. See Geometry::SetupPointLocatorQueries for more information.

	\tip The returned point locators can be evaluated on any %Geometry instance having the same topology.

	\param in_nbPositions Number of positions (XYZ triplets) specified in in_pPositions
	\param in_pPositions Positions (packed XYZ) from which the spatial search will be initiated.
	\return A new PointLocatorData object containing in_nbPositions point locators (CRef::IsValid == false if failed)

	\sa Geometry::GetClosestLocationsWithinRadius, Geometry::SetupPointLocatorQueries
	\since 5.0

	\eg Demonstrates using the PointLocatorData to find the closest mesh sphere vertex from a Null

	\code
		using namespace XSI;
		Application app;
		Model root = app.GetActiveSceneRoot();
		Null nullObj;
		root.AddNull( L"myNull", nullObj );

		CValueArray args(8);
		CValue outArg;
		args[0] = CValue(nullObj.GetRef());
		args[1] = CValue(L"-2.0");
		args[2] = CValue(L"8.0");
		args[3] = CValue(L"5.0");
		args[4] = CValue(L"siRelative");
		args[5] = CValue(L"siView");
		args[6] = CValue(L"siObj");
		args[7] = CValue(L"siXYZ");
		app.ExecuteCommand( L"Translate", args, outArg );

		X3DObject meshSphereObj;
		root.AddGeometry( L"Sphere", L"MeshSurface", L"", meshSphereObj );
		PolygonMesh meshSphereGeom( meshSphereObj.GetActivePrimitive().GetGeometry() );

		PointLocatorData closestPointLocator = meshSphereGeom.GetClosestLocations(1, (double*)&(nullObj.GetKinematics().GetGlobal().GetTransform().GetTranslation()));

		double pos[3];
		LONG triVtx[3];
		float triWei[3];

		meshSphereGeom.EvaluatePositions(closestPointLocator, -1, 0, pos);
		meshSphereGeom.GetTriangleVertexIndexArray(closestPointLocator, -1, 0, triVtx);
		meshSphereGeom.GetTriangleWeightArray(closestPointLocator, -1, 0, triWei);

		app.LogMessage(CString(L"The closest position on the mesh sphere from the Null is (")
				+ CString(CValue(pos[0])) + L", " + CString(CValue(pos[1])) + L", " + CString(CValue(pos[2])) + L")");
		app.LogMessage(CString(L"which corresponds to the triangle made of vertices (")
				+ CString(CValue(triVtx[0])) + L", " + CString(CValue(triVtx[1])) + L", " + CString(CValue(triVtx[2])) + L").");
		app.LogMessage(CString(L"The barycentric weight relatively to each triangle vertex is (")
				+ CString(CValue(triWei[0])) + L", " + CString(CValue(triWei[1])) + L", " + CString(CValue(triWei[2])) + L").");
		//INFO : The closest position on the mesh sphere from the Null is (-0.695969, 3.28837, 1.85179)
		//INFO : which corresponds to the triangle made of vertices (14, 21, 22).
		//INFO : The barycentric weight relatively to each triangle vertex is (0.347985, 0.121569, 0.530446).
	\endcode

	\eg Demonstrates using the PointLocatorData to shrink-wrap a sphere to a cube, and then push the sphere along the cube's normals.

	\code
		Application app;
		Model root = app.GetActiveSceneRoot();

		X3DObject meshCubeObj;
		root.AddGeometry( L"Cube", L"MeshSurface", L"", meshCubeObj );
		PolygonMesh meshCubeGeom( meshCubeObj.GetActivePrimitive().GetGeometry() );

		X3DObject meshSphereObj;
		root.AddGeometry( L"Sphere", L"MeshSurface", L"", meshSphereObj );
		PolygonMesh meshSphereGeom( meshSphereObj.GetActivePrimitive().GetGeometry() );

		meshSphereObj.PutParameterValue(L"subdivu", 24l);
		meshSphereObj.PutParameterValue(L"subdivv", 24l);

		// We must freeze it, otherwise setting its position array will be forbidden:
		CValueArray args(3);
		CValue outArg;
		args[0] = meshSphereObj.GetRef();
		app.ExecuteCommand(L"FreezeObj",args, outArg);

		MATH::CVector3Array posArray = meshSphereGeom.GetPoints().GetPositionArray();
		PointLocatorData sphereOnCubePointLocators = meshCubeGeom.GetClosestLocations(posArray.GetCount(), (double*)&posArray[0]);

		MATH::CVector3Array normArray;
		normArray.Resize(posArray.GetCount());

		meshCubeGeom.EvaluatePositions(sphereOnCubePointLocators, -1, 0, (double*)&posArray[0]);
		meshCubeGeom.EvaluateNormals(sphereOnCubePointLocators, siInterpolatedVertexGeometricNormals, -1, 0, (double*)&normArray[0]);

		LONG i;
		for (i = 0; i < posArray.GetCount(); i++)
		{
			posArray[i].PutX(posArray[i].GetX()+normArray[i].GetX()*3);
			posArray[i].PutY(posArray[i].GetY()+normArray[i].GetY()*3);
			posArray[i].PutZ(posArray[i].GetZ()+normArray[i].GetZ()*3);
		}
		meshSphereGeom.GetPoints().PutPositionArray(posArray);
	\endcode
	*/

	PointLocatorData GetClosestLocations
	(
		LONG			in_nbPositions,
		const double*	in_pPositions
	) const;

	/*! Creates a PointLocatorData object containing the surface locations where the specified input rays intersect with the surface.
	By default, input positions and directions that define those rays have to be defined in the object's local space reference.

	Although raycasting usually implies a semi line vs surface intersection, one can request an infinite line vs surface or finite line
	(segment) vs surface intersection by specifying \c siLineIntersection or \c siSegmentIntersection respectively for the argument
	\c in_eLineType (default = \c siSemiLineIntersection). In the case of \c siSegmentIntersection the length of each vector found in
	\c in_pRays will be used to determine where each segment ends.

	Some aspects of the raycast intersection computation such as the reference pose for \c in_pPositions and \c in_pRays or the method
	(closest surface, closest vertex or knot, etc.) can be set up using Geometry::SetupPointLocatorQueries. This setup affects all
	subsequent calls to Geometry::GetClosestLocations, Geometry::GetClosestLocationsWithinRadius or Geometry::GetRaycastIntersections.
	The closest method is necessary in the case where you pass true for \c in_bClosestSurfaceOtherwise

	\tip The returned point locators can be evaluated on any %Geometry instance having the same topology.

	\param in_nbPositions Number of rays (XYZ triplets) specified in \c in_pPositions and \c in_pRays.
	\param in_pPositions Rays' starting positions (packed XYZ).
	\param in_pRays Rays' directions.  The length of these vectors is important in the case of
		\c in_eLineType \c == \c siSegmentIntersection
	\param in_eLineType The type of line. Possible values include:
		\li \c siLineIntersection Infinite
		\li \c siSemiLineIntersection Infinite in positive direction
		\li \c siSegmentIntersection Finite in both directions

	\return A new PointLocatorData object containing \c in_nbPositions point locators (\c CRef::IsValid \c == \c false if failed)
	\sa Geometry::SetupPointLocatorQueries
	\since 6.0

	\eg Demonstrates using the PointLocatorData to find the intersection of a sphere and a line segment starting at a null and ending
		at the sphere center.

	\code
		using namespace XSI;
		Application app;
		Model root = app.GetActiveSceneRoot();
		Null nullObj;
		root.AddNull( L"myNull", nullObj );

		CValueArray args(8);
		CValue outArg;
		args[0] = CValue(nullObj.GetRef());
		args[1] = CValue(L"-2.0");
		args[2] = CValue(L"8.0");
		args[3] = CValue(L"5.0");
		args[4] = CValue(L"siRelative");
		args[5] = CValue(L"siView");
		args[6] = CValue(L"siObj");
		args[7] = CValue(L"siXYZ");
		app.ExecuteCommand( L"Translate", args, outArg );

		X3DObject meshSphereObj;
		root.AddGeometry( L"Sphere", L"MeshSurface", L"", meshSphereObj );
		PolygonMesh meshSphereGeom( meshSphereObj.GetActivePrimitive().GetGeometry() );

		CVector3 nullPos = nullObj.GetKinematics().GetGlobal().GetTransform().GetTranslation();
		CVector3 sphereCenter = meshSphereObj.GetKinematics().GetGlobal().GetTransform().GetTranslation();
		CVector3 ray;

		ray.Sub( sphereCenter, nullPos );

		PointLocatorData closestPointLocator = meshSphereGeom.GetRaycastIntersections( 1, (double*)&nullPos, (double*)&ray, siSegmentIntersection );

		double pos[3];
		LONG triVtx[3];
		float triWei[3];

		meshSphereGeom.EvaluatePositions(closestPointLocator, -1, 0, pos);
		meshSphereGeom.GetTriangleVertexIndexArray(closestPointLocator, -1, 0, triVtx);
		meshSphereGeom.GetTriangleWeightArray(closestPointLocator, -1, 0, triWei);

		app.LogMessage(CString(L"The mesh sphere intersects with the ray coming from the Null at (")
				+ CString(CValue(pos[0])) + L", " + CString(CValue(pos[1])) + L", " + CString(CValue(pos[2])) + L")");
		app.LogMessage(CString(L"which corresponds to the triangle made of vertices (")
				+ CString(CValue(triVtx[0])) + L", " + CString(CValue(triVtx[1])) + L", " + CString(CValue(triVtx[2])) + L").");
		app.LogMessage(CString(L"The barycentric weight relatively to each triangle vertex is (")
				+ CString(CValue(triWei[0])) + L", " + CString(CValue(triWei[1])) + L", " + CString(CValue(triWei[2])) + L").");
		//INFO : The mesh sphere intersects with the ray coming from the NULL at (-0.695969, 3.28837, 1.85179)
		//INFO : which corresponds to the triangle made of vertices (14, 21, 22).
		//INFO : The barycentric weight relatively to each triangle vertex is (0.347985, 0.121569, 0.530446).

	\endcode
	*/

	PointLocatorData GetRaycastIntersections
	(
		LONG					in_nbPositions,
		const double*			in_pPositions,
		const double*			in_pRays,
		siLineIntersectionType	in_eLineType = siSemiLineIntersection
	) const;

	/*! Constructs a PointLocatorData containing closest surface locations from the input position within a search sphere of a specific
	radius. By default, the input positions have to be defined in the object's local space reference. Optionally, the search can be
	restricted to return a maximum number of locations. In order to avoid volumetric restrictions, simply specify a very large radius.

	Some aspects of the closest locations's computation such as the reference pose or the method (closest surface, closest vertex or
	knot, ...) can be set up using Geometry::SetupPointLocatorQueries. This setup will affect all subsequent calls to
	GetClosestLocationsWithinRadius, Geometry::GetClosestLocations and to Geometry::GetRaycastIntersections.

	If the search was set up with Geometry::SetupPointLocatorQueries to be a closest surface or smoothed closest surface search, then
	it returns one point locator per connected island for PolygonMeshes. Such connected islands are defined so that you cannot walk
	between 2 returned point locators without leaving the search radius (this walking is through polygon adjacency, not vertex adjacency).
	For NurbsSurfaceMesh geometries, it returns at most one point locator.

	When you call this function an acceleration cache is automatically created. See Geometry::SetupPointLocatorQueries for more
	information.

	\note The "closest distance" relationship may change relative to the spatial reference of the geometry and the input positions.
		See Geometry::SetupPointLocatorQueries for more information.

	\tip The returned point locators can be evaluated on any %Geometry instance having the same topology.

	\param in_position Position from which the spatial search will be initiated.
	\param in_radius Maximum distance (cutoff) from in_PositionToSearchFrom
	\param in_nbToSearch Maximum number of point locators to find (no maximum if -1)
	\return A new PointLocatorData object containing a  point locators (.IsValid() == false if failed)

	\sa Geometry::GetClosestLocations, Geometry::SetupPointLocatorQueries, Geometry::GetRaycastIntersections
	\since 5.0

	\eg For an example using this function, see PointLocatorData::GetCount.
	*/
	PointLocatorData GetClosestLocationsWithinRadius
	(
		const MATH::CVector3&		in_position,
		double				in_radius,
		LONG				in_nbToSearch = -1
	) const;

	/*! Sets up how subsequent calls to Geometry::GetClosestLocations, Geometry::GetClosestLocationsWithinRadius
	and Geometry::GetRaycastIntersections will operate.

	An acceleration cache is built either on the first call to this function or to Geometry::GetClosestLocations,
	Geometry::GetClosestLocationsWithinRadius or Geometry::GetRaycastIntersections. The cache assumes that the geometry
	will not be deformed before any subsequent call to those functions. If that is not the case, you should get the
	geometry again or force a rebuild of the acceleration cache by calling this function, otherwise you may get wrong results.

	If you want to reuse the same cache in subsequent calls to SetupPointLocatorQueries on the same geometry but with a different
	instance of the %Geometry object (in an operator's update function for instance) make sure to call PutCache before calling
	this function.

	\note In general setting up the closest location calls with the right transformation is important since the "closest distance"
		relationship may change relative to the spatial reference of the geometry and the input positions. For instance, if you
		copy closest locations of an object's points onto another one, you will generally have different results if you scale both
		of them non-uniformly or if you add some shearing to the pose. In such case, computing the closest locations in local space
		will lead to different results from computing the closest locations in global space.

	\tip Specifying a subset of facets as targets of the search allows faster searches and a lower memory usage for the acceleration cache.

	\param in_method Method to use when searching the closest location (see ::siClosestLocationMethod for possible values).
	\param in_pTransfo Reference transformation in which the input positions will be interpreted, and in which the search
		will be executed.  Pass NULL if you dont have such a transformation.
	\param in_nbFacetsToRestrictSearch Number of facets on which the search will be restricted (or -1 for no restriction)
	\param in_pFacetsToRestrictSearch Facet indices (size = in_nbFacetsToRestrictSearch). Not used if
		\c in_nbFacetsToRestrictSearch is set to -1.
	\param in_nbLocatorsToBeQueried Approximate number of point locators that will be queried next, pass -1 if you dont know.
		\c This argument is useful to achieve better performance in the queries that will follow the setup.
	\return CStatus::OK success
	\return CStatus::Fail failure

	\sa Geometry::GetClosestLocations, Geometry::GetClosestLocationsWithinRadius, Geometry::GetRaycastIntersections
	\since 5.0

	\eg Demonstrates using the PointLocatorData to shrink-wrap a sphere on only two faces of a cube
	\code
		using namespace XSI;
		Application app;
		Model root = app.GetActiveSceneRoot();

		X3DObject meshCubeObj;
		root.AddGeometry( L"Cube", L"MeshSurface", L"", meshCubeObj );
		PolygonMesh meshCubeGeom( meshCubeObj.GetActivePrimitive().GetGeometry() );

		X3DObject meshSphereObj;
		root.AddGeometry( L"Sphere", L"MeshSurface", L"", meshSphereObj );
		PolygonMesh meshSphereGeom( meshSphereObj.GetActivePrimitive().GetGeometry() );

		meshSphereObj.PutParameterValue(L"subdivu", 24l);
		meshSphereObj.PutParameterValue(L"subdivv", 24l);

		// We must freeze it, otherwise setting its position array will be forbidden:
		CValueArray args(3);
		CValue outArg;
		args[0] = meshSphereObj.GetRef();
		app.ExecuteCommand(L"FreezeObj",args, outArg);

		LONG facets[2] = {2,3};
		meshCubeGeom.SetupPointLocatorQueries(siClosestSurface,0,2,facets,-1);

		MATH::CVector3Array posArray = meshSphereGeom.GetPoints().GetPositionArray();
		PointLocatorData sphereOnCubePointLocators = meshCubeGeom.GetClosestLocations(posArray.GetCount(), (double*)&posArray[0]);
		meshCubeGeom.EvaluatePositions(sphereOnCubePointLocators, -1, 0, (double*)&posArray[0]);
		meshSphereGeom.GetPoints().PutPositionArray(posArray);
	\endcode
	*/
	CStatus	SetupPointLocatorQueries
	(
		siClosestLocationMethod in_method,
		MATH::CTransformation* in_pTransfo,
		LONG in_nbFacetsToRestrictSearch,
		const LONG* in_pFacetsToRestrictSearch,
		LONG in_nbLocatorsToBeQueried
	);

	/*! This function has been deprecated because it does not allow you to specify the approximate number of locators
	that will be queried next after the call. This number is important to achieve better performance.
	\param in_method Method to use when searching the closest location (see ::siClosestLocationMethod for possible values).
	\param in_pTransfo Reference transformation in which the input positions will be interpreted, and in which the search
		will be executed.  Pass NULL if you dont have such a transformation.
	\param in_nbFacetsToRestrictSearch Number of facets on which the search will be restricted (or -1 for no restriction)
	\param in_pFacetsToRestrictSearch Facet indices (size = in_nbFacetsToRestrictSearch). Not used if
		\c in_nbFacetsToRestrictSearch is set to -1.
	\sa Geometry::SetupPointLocatorQueries
	\since 5.0
	\deprecated 6.0 Use the other overloaded version of this function where the argument \c in_nbLocatorsToBeQueried is present.
	*/
	CStatus	SetupClosestLocationQueries
	(
		siClosestLocationMethod in_method = siClosestSurface,
		MATH::CTransformation* in_pTransfo = NULL,
		LONG in_nbFacetsToRestrictSearch = -1,
		const LONG* in_pFacetsToRestrictSearch = NULL
	)
	{
		return SetupPointLocatorQueries( in_method, in_pTransfo, in_nbFacetsToRestrictSearch, in_pFacetsToRestrictSearch, -1 );
	}

	/*! Evaluates the positions at the surface locations defined by the input point locator data. The returned positions
	are in the geometry's local space reference.

	\param in_ptLocators Contains the point locations to be evaluated.
	\param in_nbPointLocatorsIndices Number of point locators to be evaluated (-1 if all)
	\param in_pPointLocatorsIndices %Point locator indices to be evaluated (not used if in_nbPointLocatorsIndices is -1)
	\retval out_pPositions Returns evaluated positions' packed XYZ. Size must be \c in_ptLocators::GetCount()*3 if
		\c in_nbPointLocatorsIndices is set to -1; otherwise, size must be \c in_nbPointLocatorsIndices*3 .
	\return CStatus::OK success
	\return CStatus::Fail failure

	\sa Geometry::EvaluateNormals, Geometry::EvaluateClusterProperty
	\since 5.0

	\eg For an example using this function, see Geometry::GetClosestLocations or Geometry::GetRaycastIntersections
	*/
	CStatus EvaluatePositions
	(
		const PointLocatorData& in_ptLocators,
		LONG in_nbPointLocatorsIndices, //-1 if all
		const LONG* in_pPointLocatorsIndices, // 0 if all
		double* out_pPositions
	) const;

	/*! Evaluates the surface normals at the surface locations defined by the input point locator data. The returned normals are in
	the geometry's local space reference. In the case of PolygonMesh, various computation methods are available.

	\param in_ptLocators Contains the point locations to be evaluated.
	\param in_ComputationMethod Used method in order to compute the normals (only revelant to PolygonMesh geometries)
	\param in_nbPointLocatorsIndices Number of point locators to be evaluated (-1 if all)
	\param in_pPointLocatorsIndices %Point locator indices to be evaluated (not used if in_nbPointLocatorsIndices is -1)
	\retval out_pNormals Returns evaluated normals' packed XYZ. Size must be \c in_ptLocators::GetCount()*3 if
		\c in_nbPointLocatorsIndices is set to -1; otherwise, size must be \c in_nbPointLocatorsIndices*3
	\return CStatus::OK success
	\return CStatus::Fail failure

	\sa Geometry::EvaluatePositions, Geometry::EvaluateClusterProperty
	\since 5.0

	\eg For an example using this function, see Geometry::GetClosestLocations.
	*/
	CStatus EvaluateNormals
	(
		const PointLocatorData& in_ptLocators,
		siNormalComputationMethod in_ComputationMethod,
		LONG in_nbPointLocatorsIndices, //-1 if all
		const LONG* in_pPointLocatorsIndices, // 0 if all
		double* out_pNormals
	) const;

	/*! Evaluates the cluster property data at the surface locations defined by the point locator data.

	The size of the returned array depends on the cluster property type, which can be queried using ClusterProperty::GetValueSize.

	If a point locator doesn't correspond exactly to a component defining a value for the cluster property (for example,
	sampled point for UVs), then the value will be interpolated between adjacent components. In the case of NurbsSurfaceMesh,
	the returned values will be smoothed according to the NURBS surface mathematical equation since some properties are defined
	on control vertices (for example, weight maps) while point locators are defined on the surface.

	If a point locator corresponds to a discontinuity in property space, the returned value will be an arbitrary one among the
	many values corresponding to that location.

	\note The parent cluster is required in addition to the cluster property even if it is unambiguous to get the parent cluster
		from the cluster property. The reason is that, in the context of a custom operator, both the cluster and the cluster
		property must come from the value of an input port, otherwise evaluation errors will occur.

	\param in_ptLocators Contains the point locations to be evaluated.
	\param in_nbPointLocatorsIndices Number of point locators to be evaluated (-1 if all)
	\param in_pPointLocatorsIndices %Point locator indices to be evaluated (not used if in_nbPointLocatorsIndices is -1)
	\param in_parentCluster The parent cluster of the cluster property to be evaluated.
	\param in_clusterProperty The cluster property to be evaluated.
	\retval out_pData Returns evaluated cluster property's packed data. Size must be
		\c in_ptLocators::GetCount() \c * \c in_clusterProperty::GetValueSize() if \c in_nbPointLocatorsIndices is -1;
		otherwise, \c in_nbPointLocatorsIndices \c * \c in_clusterProperty::GetValueSize().
	\return CStatus::OK success
	\return CStatus::Fail failure

	\sa Geometry::EvaluatePositions, Geometry::EvaluateNormals
	\since 5.0

	\eg For an example using this function, see PointLocatorData.
	*/
	CStatus EvaluateClusterProperty
	(
		const PointLocatorData& in_ptLocators,
		LONG in_nbPointLocatorsIndices, //-1 if all
		const LONG* in_pPointLocatorsIndices, // 0 if all
		const Cluster& in_parentCluster,
		const ClusterProperty& in_clusterProperty,
		float* out_pData
	) const;

	/*! Provides cache data for the geometry to use in various calls like SetupPointLocatorQueries,
	GetClosestLocations, and GetRaycastIntersections to speed up the execution time.

	Usually this call is not necessary as the cache data is already stored in the Geometry instance
	and automatically reused in subsequent calls to functions like SetupPointLocatorQueries on the
	same %Geometry.

	But in some cases the instance of the %Geometry object changes, like in subsequent calls to an
	operator's update function for instance, even though the geometry is the same. In those cases, a
	call to PutCache becomes necessary since the new instance of the Geometry object doesn't have
	the cache data that the old instance had. A call to GetCache should be made before the instance
	of the Geometry object is about to be released (for example, at the end of an operator's update
	function) so you can keep it around until you call PutCache again with a new instance of the
	Geometry object (for example, next time the operator's update function is called).

	\param in_Cache The cache data
	\return CStatus::OK success
	\return CStatus::Fail failure

	\sa Geometry::SetupPointLocatorQueries, Geometry::GetCache
	\since 6.0

	\eg This example shows how to use PutCache and GetCache to have the ultimate speed in using
	the point locator API in an operator's update function.  In this example not using the cache
	would mean having a big setup cost at every frame to rebuild the internal cache over and over.
	Just copy an paste the following C++ code, load the DLL as a plugin, and execute the
	ApplyMyCacheOp method in the plugin manager.

	\code

	// MyCacheOpPlugin
	// Initial code generated by XSI SDK Wizard
	// Executed Tue Sep 12 11:12:34 EDT 2006 by ecabot
	//
	//
	// Tip: You need to compile the generated code before you can load the plug-in.
	// After you compile the plug-in, you can load it by clicking Update All in the Plugin Manager.
	#include <xsi_application.h>
	#include <xsi_context.h>
	#include <xsi_pluginregistrar.h>
	#include <xsi_status.h>
	#include <xsi_customoperator.h>
	#include <xsi_operatorcontext.h>
	#include <xsi_ppglayout.h>
	#include <xsi_ppgeventcontext.h>
	#include <xsi_selection.h>
	#include <xsi_point.h>
	#include <xsi_primitive.h>
	#include <xsi_command.h>
	#include <xsi_factory.h>
	#include <xsi_geometry.h>
	#include <xsi_model.h>
	#include <xsi_x3dobject.h>
	#include <xsi_kinematics.h>
	#include <xsi_outputport.h>
	#include <xsi_transformation.h>
	using namespace XSI;
	using namespace MATH;

	XSIPLUGINCALLBACK CStatus XSILoadPlugin( PluginRegistrar& in_reg )
	{
		in_reg.PutAuthor(L"ecabot");
		in_reg.PutName(L"MyCacheOpPlugin");
		in_reg.PutEmail(L"");
		in_reg.PutURL(L"");
		in_reg.PutVersion(1,0);
		in_reg.RegisterOperator(L"MyCacheOp");
		in_reg.RegisterCommand(L"ApplyMyCacheOp");
		//RegistrationInsertionPoint - do not remove this line

		return CStatus::OK;
	}

	XSIPLUGINCALLBACK CStatus XSIUnloadPlugin( const PluginRegistrar& in_reg )
	{
		CString strPluginName;
		strPluginName = in_reg.GetName();
		Application().LogMessage(strPluginName + L" has been unloaded.");
		return CStatus::OK;
	}

	XSIPLUGINCALLBACK CStatus ApplyMyCacheOp_Init( CRef& in_ctxt )
	{
		Context ctxt( in_ctxt );
		Command oCmd;
		oCmd = ctxt.GetSource();
		oCmd.PutDescription(L"Create an instance of MyCacheOp operator");
		oCmd.SetFlag(siNoLogging,false);

		// TODO: You may want to add some arguments to this command so that the operator
		// can be applied to objects without depending on their specific names.
		// Tip: the Collection ArgumentHandler is very useful
		return CStatus::OK;
	}

	XSIPLUGINCALLBACK CStatus ApplyMyCacheOp_Execute( CRef& in_ctxt )
	{
		Context ctxt( in_ctxt );

		using namespace XSI;
		Application app;
		Model root = app.GetActiveSceneRoot();

		// Let's create an arc curve that we will shrink wrap over a sphere
		X3DObject arcObj;
		root.AddGeometry( L"Arc", L"NurbsCurve", L"arc", arcObj );

		// Let's create a hires sphere that we will use for the shrink wrap target
		X3DObject meshSphereObj;
		root.AddGeometry( L"Sphere", L"MeshSurface", L"sphere", meshSphereObj );

		CValue outArg;

		// Let's make this sphere hires 200x200
		CValueArray args(3);
		args[0] = CValue(meshSphereObj.GetFullName() + L".polymsh.geom.subdivu" );
		args[1] = CValue(L"200");
		args[2] = CValue();
		app.ExecuteCommand( L"SetValue", args, outArg );
		args[0] = CValue(meshSphereObj.GetFullName() + L".polymsh.geom.subdivv" );
		app.ExecuteCommand( L"SetValue", args, outArg );

		//
		// Note: The AddCustomOp command is an alternative way to build the operator
		CustomOperator newOp = Application().GetFactory().CreateObject(L"MyCacheOp");

		CRef obj;
		obj.Set(L"arc.crvlist");
		newOp.AddOutputPort(obj);
		obj.Set(L"arc.crvlist");
		newOp.AddInputPort(obj);

		newOp.AddInputPort(arcObj.GetKinematics().GetGlobal());

		obj.Set(L"sphere.polymsh");
		newOp.AddInputPort(obj);
		newOp.AddInputPort(meshSphereObj.GetKinematics().GetGlobal());
		newOp.Connect();
		ctxt.PutAttribute( L"ReturnValue", newOp.GetRef() );

		// Now animate the Z position of the curve

		// frame 1, XYZ = 4,0,0
		args.Resize(8);
		args[0] = CValue(arcObj.GetFullName());
		args[1] = CValue(L"4.0");
		args[2] = CValue(L"0.0");
		args[3] = CValue(L"0.0");
		args[4] = CValue(L"siRelative");
		args[5] = CValue(L"siLocal");
		args[6] = CValue(L"siObj");
		args[7] = CValue(L"siXYZ");
		app.ExecuteCommand( L"Translate", args, outArg );

		// Save a key at frame 1
		args.Resize(4);
		args[0] = CValue(arcObj.GetFullName()+L".kine.local.posz");
		args[1] = CValue((LONG)1);
		args[2] = CValue();
		args[3] = CValue();
		app.ExecuteCommand( L"SaveKey", args, outArg );

		// frame 100, XYZ = 4,0,4
		args.Resize(8);
		args[0] = CValue(arcObj.GetFullName());
		args[1] = CValue(L"0.0");
		args[2] = CValue(L"0.0");
		args[3] = CValue(L"4.0");
		args[4] = CValue(L"siRelative");
		args[5] = CValue(L"siLocal");
		args[6] = CValue(L"siObj");
		args[7] = CValue(L"siXYZ");
		app.ExecuteCommand( L"Translate", args, outArg );

		// save a key at frame 100
		args.Resize(4);
		args[0] = CValue(arcObj.GetFullName()+L".kine.local.posz");
		args[1] = CValue((LONG)100);
		args[2] = CValue();
		args[3] = CValue();
		app.ExecuteCommand( L"SaveKey", args, outArg );

		Application().LogMessage(L"ApplyMyCacheOp_Execute called");

		return CStatus::OK;
	}

	XSIPLUGINCALLBACK CStatus MyCacheOp_Define( CRef& in_ctxt )
	{
		Context ctxt( in_ctxt );
		CustomOperator oCustomOperator;
		Parameter oParam;
		CRef oPDef;
		Factory oFactory = Application().GetFactory();
		oCustomOperator = ctxt.GetSource();

		oCustomOperator.PutAlwaysEvaluate(false);
		oCustomOperator.PutDebug(1);
		return CStatus::OK;
	}

	XSIPLUGINCALLBACK CStatus MyCacheOp_Init( CRef& in_ctxt )
	{
		OperatorContext ctxt( in_ctxt );
		Application().LogMessage(L"MyCacheOp_Init called",siVerboseMsg);
		return CStatus::OK;
	}

	XSIPLUGINCALLBACK CStatus MyCacheOp_Term( CRef& in_ctxt )
	{
		OperatorContext ctxt( in_ctxt );
		Application().LogMessage(L"MyCacheOp_Term called",siVerboseMsg);
		return CStatus::OK;
	}

	XSIPLUGINCALLBACK CStatus MyCacheOp_Update( CRef& in_ctxt )
	{
		CStatus st;
		OperatorContext ctxt( in_ctxt );
		Primitive io_Curve = ctxt.GetInputValue(0);
		KinematicState in_CurveG = ctxt.GetInputValue(1);
		CTransformation xCurveG = in_CurveG.GetTransform();

		Primitive in_Target = ctxt.GetInputValue(2);
		KinematicState in_TargetG = ctxt.GetInputValue(3);
		CTransformation xTargetG = in_TargetG.GetTransform();

		Application().LogMessage(L"MyCacheOp_Update called",siVerboseMsg);

		//
		// TODO: The Operator changes the Softimage scene by changing the state of this variable
		//
		Primitive output = ctxt.GetOutputTarget();

		Geometry xTargetGeo = in_Target.GetGeometry();

		CValue CacheVal = ctxt.GetUserData();

		if( ! CacheVal.IsEmpty() )
		{
			xTargetGeo.PutCache(CacheVal);
		}

		xTargetGeo.SetupPointLocatorQueries( siClosestSurface, &xTargetG, -1, NULL, -1 );

		Geometry xCurveGeo = io_Curve.GetGeometry();

		MATH::CVector3Array & xPoints = xCurveGeo.GetPoints().GetPositionArray();

		CDoubleArray WorldPoints;

		WorldPoints.Resize( 3*xPoints.GetCount(), false );

		LONG offset = 0;

		for( LONG i = 0; i < xPoints.GetCount(); ++i )
		{
			CVector3 vPos = xPoints[i];
			vPos.MulByTransformationInPlace(xCurveG);

			WorldPoints[offset+0] = vPos.GetX();
			WorldPoints[offset+1] = vPos.GetY();
			WorldPoints[offset+2] = vPos.GetZ();

			offset += 3;
		}

		PointLocatorData ptLocators = xTargetGeo.GetClosestLocations( xPoints.GetCount(), WorldPoints.GetArray() );

		double * PLoc = new double [ptLocators.GetCount()*3];

		xTargetGeo.EvaluatePositions( ptLocators, -1, NULL, PLoc );

		Geometry outGeo = output.GetGeometry();
		MATH::CVector3Array & xOutPoints = outGeo.GetPoints().GetPositionArray();

		CTransformation xCurveInvG;
		xCurveInvG.Invert(xCurveG);

		CTransformation xFromTargetToCurveG;
		xFromTargetToCurveG.Mul(xTargetG,xCurveInvG);

		for( i = 0; i < ptLocators.GetCount(); ++i )
		{
			CVector3 vPos;
			vPos.Set( PLoc[3*i], PLoc[3*i+1], PLoc[3*i+2] );
			vPos.MulByTransformationInPlace(xFromTargetToCurveG);

			xOutPoints[i] = vPos;
		}

		delete [] PLoc;

		outGeo.GetPoints().PutPositionArray(xOutPoints);

		// Let's keep the cache around for next time we are evaluated

		CacheVal = xTargetGeo.GetCache();

		if( ! CacheVal.IsEmpty() )
		{
			ctxt.PutUserData(CacheVal);
		}

		return CStatus::OK;
	}

	\endcode

	*/
	CStatus PutCache
	(
		CValue & in_Cache
	);

	/*! Returns the cache data currently used by the geometry.

	The cache can be stored until a new instance of the same geometry is created at which time the new
	cache can be set using Geometry::PutCache. This saves the geometry from recreating all the internal
	data structures so that you don't lose any performance benefits.

	\return The cache data
	\return empty CValue if the call fails

	\sa Geometry::PutCache
	\since 6.01

	*/

	CValue GetCache();

	/*! Calculates and returns bounding box information
	\retval out_centerx  Returns the x coordinate of the center of the bounding box.
	\retval out_centery  Returns the y coordinate of the center of the bounding box.
	\retval out_centerz  Returns the z coordinate of the center of the bounding box.
	\retval out_extentx  Returns the extent of the bounding box in the X axis.
	\retval out_extenty  Returns the extent of the bounding box in the Y axis.
	\retval out_extentz  Returns the extent of the bounding box in the Z axis.
	\param in_XfoObjectToBBoxSpace  Contains a transform (if desired) between the object and the global coordinate axes. This
		can be used to more tightly orient a bounding box around the object.
	\return CStatus::OK success
	\return CStatus::Fail failure
	\sa Geometry::GetBoundingSphere, Geometry::GetBoundingCapsule, Geometry::PutCache
	\since 5.0
	*/
	CStatus GetBoundingBox
	(
	   double                & out_centerx,
	   double                & out_centery,
	   double                & out_centerz,
	   double                & out_extentx,
	   double                & out_extenty,
	   double                & out_extentz,
	   const MATH::CTransformation & in_XfoObjectToBBoxSpace
	) const;


	/*! Calculates and returns bounding sphere information
	\retval out_centerx  Returns the x coordinate of the center of the bounding sphere.
	\retval out_centery  Returns the y coordinate of the center of the bounding sphere.
	\retval out_centerz  Returns the z coordinate of the center of the bounding sphere.
	\retval out_radius  Returns the radius of the bounding sphere.
	\param in_centerMethod Specifies the technique used to calculate the center of the bounding sphere
	\param in_XfoObjectToBSphereSpace  Contains a transform (if desired) between the object and the global coordinate axes. This
		can be used to more tightly orient a bounding sphere around the object.
	\return CStatus::OK success
	\return CStatus::Fail failure
	\sa Geometry::GetBoundingBox, Geometry::GetBoundingCapsule
	\since 5.0
	*/
	CStatus GetBoundingSphere
	(
	   double                      & out_centerx,
	   double                      & out_centery,
	   double                      & out_centerz,
	   double                      & out_radius,
	   siVolumeCenterMethod          in_centerMethod,
	   const MATH::CTransformation & in_XfoObjectToBSphereSpace
    );

	/*! Calculates and returns bounding capsule (swept sphere) information
	\retval out_centerx  Returns the x coordinate of the center of the bounding capsule.
	\retval out_centery  Returns the y coordinate of the center of the bounding capsule.
	\retval out_centerz  Returns the z coordinate of the center of the bounding capsule.
	\retval out_length  Returns the length of the bounding capsule (not including the radii of the capping hemispheres).
	\retval out_radius  Returns the cylindrical radius of the bounding capsule.
	\param in_centerMethod Specifies the technique used to calculate the center of the bounding capsule
	\param in_axisMethod Specifies the technique used to calculate the long axis of the bounding capsule
	\param in_XfoObjectToBCapsuleSpace  Contains a transform (if desired) between the object and the global coordinate axes. This
		can be used to more tightly orient a bounding capsule around the object
	\return CStatus::OK success
	\return CStatus::Fail failure
	\sa Geometry::GetBoundingBox, Geometry::GetBoundingSphere
	\since 5.0
	*/
	CStatus GetBoundingCapsule
	(
	    double                        & out_centerx,
		double                        & out_centery,
		double                        & out_centerz,
		double                        & out_length,
		double                        & out_radius,
		siVolumeCenterMethod            in_centerMethod,
		siBoundingCapsuleMethod         in_axisMethod,
		const MATH::CTransformation   & in_XfoObjectToBCapsuleSpace
	) ;

	/*! Returns all attributes defined for this geometry.
	\return Array of references to the ICEAttribute objects.
	\sa ProjectItem::GetICEAttributes
	\since 7.0
	*/
	CRefArray GetICEAttributes() const;

	/*! Returns the attribute data matching a specific name as an ICEAttribute object.
	\param in_name Name of the attribute to find.
	\return The new ICEAttribute object.
	\sa ProjectItem::GetICEAttributeFromName
	\since 7.0

	\eg %This example shows how to access the PointPosition attribute by name.
	\code
		CValue CreatePrim( const CString& in_presetobj, const CString& in_geometrytype, const CString& in_name, const CString& in_parent );

		template < class T >
		class CICEAttributeDataLogger
		{
			public:
			static void Log( ICEAttribute& attr )
			{
				CICEAttributeDataArray< T > data;
				attr.GetDataArray( data );

				Application xsi;
				for( ULONG i=0; i<data.GetCount( ); i++ )
				{
					xsi.LogMessage( CString( data[ i ] ) );
				}
			}
		};

		Application xsi;

		X3DObject grid = CreatePrim( L"Grid", L"MeshSurface", L"", L"");

		ICEAttribute attr = grid.GetActivePrimitive().GetGeometry().GetICEAttributeFromName( L"PointPosition" );

		xsi.LogMessage( L"*******************************************************************" );
		xsi.LogMessage( L"Name: " + attr.GetName() );
		xsi.LogMessage( L"DataType: " + CString(attr.GetDataType()) );
		xsi.LogMessage( L"StructType: " + CString(attr.GetStructureType()) );
		xsi.LogMessage( L"ContextType: " + CString(attr.GetContextType()) );
		xsi.LogMessage( L"IsConstant: " + CString(attr.IsConstant()) );
		xsi.LogMessage( L"Readonly: " + CString(attr.IsReadonly()) );
		xsi.LogMessage( L"Category: " + CString(attr.GetCategory()) );
		xsi.LogMessage( L"Element count: " + CString(attr.GetElementCount()) );

		CICEAttributeDataLogger<XSI::MATH::CVector3f>::Log( attr );

		// Helper
		CValue CreatePrim( const CString& in_presetobj, const CString& in_geometrytype, const CString& in_name, const CString& in_parent )
		{
			CValueArray args(4);
			CValue retval;
			args[0]= in_presetobj;
			args[1]= in_geometrytype;
			args[2]= in_name;
			args[3]= in_parent;

			Application app;
			app.ExecuteCommand( L"CreatePrim", args, retval );
			return retval;
		}

	\endcode
	*/
	ICEAttribute GetICEAttributeFromName( const CString& in_name ) const;

	/*! Adds a new <object idref="ICEAttribute"/> object to this geometry and returns this object. If the attribute is already defined, this attribute is returned instead.
	\param in_name Name of the attribute to create.
	\param in_DataType The attribute data type.
	\param in_StructureType The attribute structure type.
	\param in_ContextType The attribute context type.
	\return The newly created ICEAttribute object or the existing attribute if already defined.
	\sa Geometry::RemoveICEAttribute
	\sa ProjectItem::AddICEAttribute
	\sa ProjectItem::RemoveICEAttribute
	\since 11.0 (2013)
	*/
	ICEAttribute AddICEAttribute( const CString& in_name, XSI::siICENodeDataType in_DataType, XSI::siICENodeStructureType in_StructureType, XSI::siICENodeContextType in_ContextType );

	/*! Removes the attribute identified with in_name from this geometry. The attribute is removed only if it is not a built-in attribute and not required by an ICETree.
	\param in_name Name of the attribute to remove.
	\return CStatus::OK success
	\return CStatus::Fail Failure. This can occur when the ICE attribute doesn't exist or cannot be removed (probably because it is still used).
	\sa ProjectItem::AddICEAttribute
	\sa ProjectItem::RemoveICEAttribute
	\since 11.0 (2013)
	*/
	CStatus RemoveICEAttribute( const CString& in_name );

	private:
	Geometry * operator&() const;
	Geometry * operator&();
};

};

#endif // __XSIGEOMETRY_H__
