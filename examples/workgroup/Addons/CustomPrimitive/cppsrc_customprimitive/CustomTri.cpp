// CustomPrimitives example
//
//	Copyright 2012 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   
//
//	File:	CustomTri.cpp
//
//	Description:
//
//		Defines a triangle primitive that is defined by 2 floating-point
//		half-extents reprensenting width and height in the XY plane.
//

#ifndef linux
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h> // Needed for OpenGL on windows
#endif
#include <GL/gl.h>

#include <xsi_application.h>
#include <xsi_context.h>
#include <xsi_pluginregistrar.h>
#include <xsi_status.h>
#include <xsi_menu.h>
#include <xsi_customprimitive.h>
#include <xsi_factory.h>
#include <xsi_parameter.h>
#include <xsi_geometry.h>
#include <xsi_polygonmesh.h>
#include <xsi_vector3.h>
#include <xsi_longarray.h>
#include <xsi_customprimitivecontext.h>

using namespace XSI; 

// Defines
//
static const CString kWidthName = L"HalfWidth";
static const CString kWidthNiceName = L"Half Width";
static const CString kWidthDesc = L"Half-width of the triangle";
static const CString kHeightName = L"HalfHeight";
static const CString kHeightNiceName = L"Half Height";
static const CString kHeightDesc = L"Half-height of the triangle";

static const double kMinWidth = 0.1;
static const double kMaxWidth = 100.0;

static const double kMinHeight = 0.1;
static const double kMaxHeight = 100.0;


SICALLBACK Tri_Define( const CRef& in_ref )
{
	Context in_ctxt( in_ref );
	CustomPrimitive in_prim( in_ctxt.GetSource() );
	if( in_prim.IsValid() )
	{
		Factory l_fact = Application().GetFactory();

        CRef l_widthDef = l_fact.CreateParamDef(
            kWidthName, CValue::siDouble,
            siClassifTopo,
            siAnimatable | siPersistable, kWidthNiceName, kWidthDesc,
            1.0, kMinWidth, kMaxWidth, kMinWidth, kMaxWidth );
		Parameter l_width;
		in_prim.AddParameter( l_widthDef, l_width );

		CRef l_heightDef = l_fact.CreateParamDef(
            kHeightName, CValue::siDouble,
            siClassifTopo,
            siAnimatable | siPersistable, kHeightNiceName, kHeightDesc,
            1.0, kMinHeight, kMaxHeight, kMinHeight, kMaxHeight );
		Parameter l_height;
		in_prim.AddParameter( l_heightDef, l_height );
	}
	return CStatus::OK;
}

SICALLBACK Tri_Draw( const CRef& in_ref )
{
	Context in_ctxt( in_ref );
	CustomPrimitive in_prim( in_ctxt.GetSource() );
	if( !in_prim.IsValid() )
	{
		return CStatus::Fail;
	}

    // Use GetParameters() when there are multiple parameters to optimize
    // access and augment performance.

    CParameterRefArray& params = in_prim.GetParameters();

	double TriHalfWidth = params.GetValue( kWidthName );
	double TriHalfHeight = params.GetValue( kHeightName );

    // Note: the custom primitive API doesn't protect the OpenGL state
    //       for performance reasons. It is the duty of the custom primitive
    //       to leave the OpenGL state as it was on entry.

	// Draw Tri
	//
	double TriBaseMinPt[3];
	double TriBaseMaxPt[3];
	double TriTopPt[3];

	TriBaseMinPt[0] = -TriHalfWidth;
	TriBaseMinPt[1] = -TriHalfHeight;
	TriBaseMinPt[2] = 0.0;

	TriBaseMaxPt[0] = TriHalfWidth;
	TriBaseMaxPt[1] = -TriHalfHeight;
	TriBaseMaxPt[2] = 0.0;

	TriTopPt[0] = 0.0;
	TriTopPt[1] = TriHalfHeight;
	TriTopPt[2] = 0.0;

	GLdouble l_Verts[3][3];

	l_Verts[0][0] = TriBaseMinPt[0];
	l_Verts[0][1] = TriBaseMinPt[1];
	l_Verts[0][2] = TriBaseMinPt[2];

	l_Verts[1][0] = TriBaseMaxPt[0];
	l_Verts[1][1] = TriBaseMaxPt[1];
	l_Verts[1][2] = TriBaseMaxPt[2];

	l_Verts[2][0] = TriTopPt[0];
	l_Verts[2][1] = TriTopPt[1];
	l_Verts[2][2] = TriTopPt[2];

	::glBegin( GL_LINE_STRIP );
	::glVertex3dv( l_Verts[0] );
	::glVertex3dv( l_Verts[1] );
	::glVertex3dv( l_Verts[2] );
	::glVertex3dv( l_Verts[0] );
	::glEnd();

	return CStatus::OK;
}

SICALLBACK Tri_BoundingBox( const CRef& in_ref )
{
	Context in_ctxt( in_ref );
	CustomPrimitive in_prim( in_ctxt.GetSource() );
	if( !in_prim.IsValid() )
	{
		return CStatus::Fail;
	}

    // Use GetParameters() when there are multiple parameters to optimize
    // access and augment performance.

    CParameterRefArray& params = in_prim.GetParameters();

	double TriHalfWidth = params.GetValue( kWidthName );
	double TriHalfHeight = params.GetValue( kHeightName );

	in_ctxt.PutAttribute( "LowerBoundX", -TriHalfWidth );
	in_ctxt.PutAttribute( "LowerBoundY", -TriHalfHeight );
	in_ctxt.PutAttribute( "LowerBoundZ", 0.0 );
	in_ctxt.PutAttribute( "UpperBoundX", TriHalfWidth );
	in_ctxt.PutAttribute( "UpperBoundY", TriHalfHeight );
	in_ctxt.PutAttribute( "UpperBoundZ", 0.0 );

	return CStatus::OK;
}

SICALLBACK Tri_ConvertToGeom( const CRef& in_ref )
{
	CustomPrimitiveContext in_ctxt( in_ref );
	CustomPrimitive in_prim( in_ctxt.GetSource() );

	if( !in_prim.IsValid() )
	{
		return CStatus::Fail;
	}

	CString primCls = in_prim.GetClassIDName();

    // Use GetParameters() when there are multiple parameters to optimize
    // access and augment performance.

    CParameterRefArray& params = in_prim.GetParameters();

	double TriHalfWidth = params.GetValue( kWidthName );
	double TriHalfHeight = params.GetValue( kHeightName );

	Geometry out_geo = in_ctxt.GetGeometry();

	// PolygonMesh support
	//
	PolygonMesh out_mesh( out_geo );
	if( out_mesh.IsValid() )
	{
		// Convert to polygon.
		MATH::CVector3Array out_verts;
		CLongArray out_faces;

		int depth = (int) TriHalfWidth;

		for ( int i = 0 ; i < depth ; i++ )
		{
			MATH::CVector3 baseMinPt( -1.0, -TriHalfHeight, (double)i );
			MATH::CVector3 baseMaxPt( 1.0, -TriHalfHeight, (double)i );
			MATH::CVector3 topPt( 0.0, TriHalfHeight, (double)i );

			out_verts.Add( baseMinPt );
			out_verts.Add( baseMaxPt );
			out_verts.Add( topPt );

			out_faces.Add( 3 ); // Vertex count for tri
			out_faces.Add( i*3 + 0 );
			out_faces.Add( i*3 + 1 );
			out_faces.Add( i*3 + 2 );
		}

		return out_mesh.Set( out_verts, out_faces );
	}

	return CStatus::OK;
}

SICALLBACK OnCustomTriMenuItem( CRef& in_ref )
{
	Context ctxt( in_ref );
	MenuItem menuItem = ctxt.GetSource();

    Application app;
	CValue out_arg;
	CValueArray in_args;
	in_args.Add( L"Tri" );
	app.ExecuteCommand( "GetPrim", in_args, out_arg );

    return CStatus::OK;
}

SICALLBACK OnCustomTriMeshMenuItem( CRef& in_ref )
{
	Context ctxt( in_ref );
	MenuItem menuItem = ctxt.GetSource();

    Application app;
	CValue out_arg;
	CValueArray in_args;
	in_args.Add( L"Tri" );
	in_args.Add( L"MeshSurface" );
	app.ExecuteCommand( "CreatePrim", in_args, out_arg );

    return CStatus::OK;
}
