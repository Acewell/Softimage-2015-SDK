// CustomPrimitives example
//
//	Copyright 2012 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   
//
//	File:	BPT_Cylinder.cpp
//
//	Description:
//
//		Defines a cylinder primitive that is defined by 2 floating-point
//		values: height and radius.
//

#ifndef linux
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h> // Needed for OpenGL on windows
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <cfloat>

#include <xsi_application.h>
#include <xsi_context.h>
#include <xsi_pluginregistrar.h>
#include <xsi_status.h>
#include <xsi_menu.h>
#include <xsi_customprimitive.h>
#include <xsi_factory.h>
#include <xsi_parameter.h>

using namespace XSI; 

// Defines
//
#define kHeightName L"Height"

#define kHeightDef 1.0

#define kHeightMin 0.000001
#define kHeightMax DBL_MAX
#define kHeightSoftMin 0.001
#define kHeightSoftMax 100.0

#define kRadiusScriptName L"Radius"
#define kRadiusUIName L"Radius"

#define kRadiusMin 0.0
#define kRadiusMax DBL_MAX
#define kRadiusSoftMin 0.0
#define kRadiusSoftMax 100.0

#define kRadiusDef 1.0

#define kParamCaps	(siAnimatable | siPersistable | siKeyable)

#define kDivName L"Subdivisions"

#define kDivMin 4
#define kDivMax 24

#define kDivU 8
#define kDivV 8

extern GLUquadric* g_quadric;

SICALLBACK CustomCylinder_Define( const CRef& in_ref )
{
	Context in_ctxt( in_ref );
	CustomPrimitive in_prim( in_ctxt.GetSource());
	if( in_prim.IsValid() )
	{
		Factory l_fact = Application().GetFactory();
		CRef l_heightDef = l_fact.CreateParamDef( kHeightName, CValue::siDouble, kParamCaps, kHeightName, L"", kHeightDef, kHeightMin, kHeightMax, kHeightSoftMin, kHeightSoftMax );
		CRef l_radiusDef = l_fact.CreateParamDef( kRadiusScriptName, CValue::siDouble, kParamCaps, kRadiusUIName, L"", kRadiusDef, kRadiusMin, kRadiusMax, kRadiusSoftMin, kRadiusSoftMax );
		CRef l_divDef = l_fact.CreateParamDef( kDivName, CValue::siInt4, kDivU, kDivMin, kDivMax );

		Parameter l_height;
		Parameter l_r;
		Parameter l_div;
		in_prim.AddParameter( l_heightDef, l_height );
		in_prim.AddParameter( l_radiusDef, l_r );
		in_prim.AddParameter( l_divDef, l_div );
	}
	return CStatus::OK;
}

SICALLBACK CustomCylinder_Draw( const CRef& in_ref )
{
	Context in_ctxt( in_ref );
	CustomPrimitive in_prim( in_ctxt.GetSource());
	if( !in_prim.IsValid() )
	{
		return CStatus::Fail;
	}

    // Use GetParameters() when there are multiple parameters to optimize
    // access and augment performance.

    CParameterRefArray& params = in_prim.GetParameters();

	double cylHeight = params.GetValue( kHeightName );
	double cylHalfHeight = 0.5 * cylHeight;
	double cylRadius = params.GetValue( kRadiusScriptName );
	int cylDiv = params.GetValue( kDivName );

    // Note: the custom primitive API doesn't protect the OpenGL state
    //       for performance reasons. It is the duty of the custom primitive
    //       to leave the OpenGL state as it was on entry.

	if( g_quadric )
	{
		::glMatrixMode( GL_MODELVIEW );
		::glPushMatrix();

		// Draw cylinder
		//
		::glRotated( -90.0, 1.0, 0.0, 0.0 );
		::gluCylinder( g_quadric, cylRadius, cylRadius, cylHeight, cylDiv, 1 );

		::glPopMatrix();
	}

	return CStatus::OK;
}

SICALLBACK CustomCylinder_BoundingBox( const CRef& in_ref )
{
	Context in_ctxt( in_ref );
	CustomPrimitive in_prim(in_ctxt.GetSource());
	if( !in_prim.IsValid() )
	{
		return CStatus::Fail;
	}

    // Use GetParameters() when there are multiple parameters to optimize
    // access and augment performance.

    CParameterRefArray& params = in_prim.GetParameters();

	double cylHeight = params.GetValue( kHeightName );
	double cylHalfHeight = 0.5 * cylHeight;
	double cylRadius = params.GetValue( kRadiusScriptName );

	in_ctxt.PutAttribute( "LowerBoundX", -cylRadius );
	in_ctxt.PutAttribute( "LowerBoundY", 0.0 );
	in_ctxt.PutAttribute( "LowerBoundZ", -cylRadius );
	in_ctxt.PutAttribute( "UpperBoundX", cylRadius );
	in_ctxt.PutAttribute( "UpperBoundY", cylHeight );
	in_ctxt.PutAttribute( "UpperBoundZ", cylRadius );

	return CStatus::OK;
}

SICALLBACK OnCustomCylinderMenuItem( CRef& in_ref )
{
	Context ctxt( in_ref );
	MenuItem menuItem = ctxt.GetSource();

    Application app;
	CValue out_arg;
	CValueArray in_args;
	in_args.Add( L"CustomCylinder" );
	app.ExecuteCommand( "GetPrim", in_args, out_arg );

    return CStatus::OK;
}
