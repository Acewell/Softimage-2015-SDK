// CustomPrimitives example
//
//	Copyright 2012 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   
//
//	File:	CustomCapsule.cpp
//
//	Description:
//
//		Defines a capsule primitive that is defined by 4 floating-point
//		values reprensenting radius along each XYZ axis and internal
//		cylindrical height.
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

#define kMinHeight 0.0
#define kMaxHeight 1000

#define kRadiusXScriptName L"RadiusX"
#define kRadiusYScriptName L"RadiusY"
#define kRadiusZScriptName L"RadiusZ"

#define kRadiusXUIName L"Radius X"
#define kRadiusYUIName L"Radius Y"
#define kRadiusZUIName L"Radius Z"

#define kRadiusMin 0.000001
#define kRadiusMax DBL_MAX
#define kRadiusSoftMin 0.001
#define kRadiusSoftMax 100

#define kRadiusDef 1.0

#define kParamCaps	(siAnimatable | siPersistable | siKeyable)

#define kDivName L"Subdivisions"

#define kDivMin 4
#define kDivMax 24

#define kDivU 8
#define kDivV 8

extern GLUquadric* g_quadric;

SICALLBACK Capsule_Define( const CRef& in_ref )
{
	Context in_ctxt( in_ref );
	CustomPrimitive in_prim( in_ctxt.GetSource() );
	if( in_prim.IsValid() )
	{
		Factory l_fact = Application().GetFactory();
		CRef l_heightDef = l_fact.CreateParamDef( kHeightName, CValue::siDouble, kHeightDef, kMinHeight, kMaxHeight );
		CRef l_radiusXDef = l_fact.CreateParamDef( kRadiusXScriptName, CValue::siDouble, kParamCaps, kRadiusXUIName, L"", kRadiusDef, kRadiusMin, kRadiusMax, kRadiusSoftMin, kRadiusSoftMax );
		CRef l_radiusYDef = l_fact.CreateParamDef( kRadiusYScriptName, CValue::siDouble, kParamCaps, kRadiusYUIName, L"", kRadiusDef, kRadiusMin, kRadiusMax, kRadiusSoftMin, kRadiusSoftMax );
		CRef l_radiusZDef = l_fact.CreateParamDef( kRadiusZScriptName, CValue::siDouble, kParamCaps, kRadiusZUIName, L"", kRadiusDef, kRadiusMin, kRadiusMax, kRadiusSoftMin, kRadiusSoftMax );
		CRef l_divDef = l_fact.CreateParamDef( kDivName, CValue::siInt4, kDivU, kDivMin, kDivMax );

		Parameter l_height;
		Parameter l_rx;
		Parameter l_ry;
		Parameter l_rz;
		Parameter l_div;
		in_prim.AddParameter( l_heightDef, l_height );
		in_prim.AddParameter( l_radiusXDef, l_rx );
		in_prim.AddParameter( l_radiusYDef, l_ry );
		in_prim.AddParameter( l_radiusZDef, l_rz );
		in_prim.AddParameter( l_divDef, l_div );
	}
	return CStatus::OK;
}

SICALLBACK Capsule_Draw( const CRef& in_ref )
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

	double CapHeight = params.GetValue( kHeightName );
	double CapHalfHeight = 0.5 * CapHeight;

	double CapRX = params.GetValue( kRadiusXScriptName );
	double CapRY = params.GetValue( kRadiusYScriptName );
	double CapRZ = params.GetValue( kRadiusZScriptName );

	double oneOverCapRY = 1.0 / CapRY;

	int CapDiv = params.GetValue( kDivName );

    // Note: the custom primitive API doesn't protect the OpenGL state
    //       for performance reasons. It is the duty of the custom primitive
    //       to leave the OpenGL state as it was on entry.

	if( g_quadric )
	{
		::glMatrixMode( GL_MODELVIEW );
		::glPushMatrix();

		// Draw cylinder
		//
		::glTranslated( 0.0, CapHalfHeight, 0.0 );
		::glScaled( CapRX, 1.0, CapRZ );
		::glRotated( 90.0, 1.0, 0.0, 0.0 );
		::gluCylinder( g_quadric, 1.0, 1.0, CapHeight, CapDiv, 1 );
		::glRotated( -90.0, 1.0, 0.0, 0.0 );

		// Align half-sphere start point (-1, 0, 0) to cylinder start point (0, 0, 1)
		//
		::glRotated( 90.0, 0.0, 1.0, 0.0 );

		// Draw half-sphers
		//
		double rotStep = 360.0 / (double) CapDiv;
		for( int i = 0; i < CapDiv; i++ )
		{
			::glScaled( 1.0, CapRY, 1.0 );
			::gluPartialDisk( g_quadric, 1.0, 1.0, kDivV, 1, -90.0, 90.0 );
			::glScaled( 1.0, oneOverCapRY, 1.0 );
			::glRotated( rotStep, 0.0, 1.0, 0.0 );
		}
		::glTranslated( 0.0, -CapHeight, 0.0 );
		for( int i = 0; i < CapDiv; i++ )
		{
			::glScaled( 1.0, CapRY, 1.0 );
			::gluPartialDisk( g_quadric, 1.0, 1.0, kDivV, 1, -90.0, -90.0 );
			::glScaled( 1.0, oneOverCapRY, 1.0 );
			::glRotated( rotStep, 0.0, 1.0, 0.0 );
		}

		::glPopMatrix();
	}

	return CStatus::OK;
}

SICALLBACK Capsule_BoundingBox( const CRef& in_ref )
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

	double CapHeight = params.GetValue( kHeightName );
	double CapHalfHeight = 0.5 * CapHeight;

	double CapRX = params.GetValue( kRadiusXScriptName );
	double CapRY = params.GetValue( kRadiusYScriptName );
	double CapRZ = params.GetValue( kRadiusZScriptName );

	CapRY += CapHalfHeight;

	in_ctxt.PutAttribute( "LowerBoundX", -CapRX );
	in_ctxt.PutAttribute( "LowerBoundY", -CapRY );
	in_ctxt.PutAttribute( "LowerBoundZ", -CapRZ );
	in_ctxt.PutAttribute( "UpperBoundX", CapRX );
	in_ctxt.PutAttribute( "UpperBoundY", CapRY );
	in_ctxt.PutAttribute( "UpperBoundZ", CapRZ );

	return CStatus::OK;
}

SICALLBACK OnCustomCapsuleMenuItem( CRef& in_ref )
{
	Context ctxt( in_ref );
	MenuItem menuItem = ctxt.GetSource();

    Application app;
	CValue out_arg;
	CValueArray in_args;
	in_args.Add( L"Capsule" );
	app.ExecuteCommand( "GetPrim", in_args, out_arg );

    return CStatus::OK;
}
