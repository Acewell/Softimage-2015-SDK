// CustomPrimitives example
//
//	Copyright 2012 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   
//
//	File:	CustomPyramid.cpp
//
//	Description:
//
//		Defines a pyramid primitive that is defined by 3 floating-point
//		half-extents representing height, width and length.
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

using namespace XSI; 

// Defines
//
#define kWidthName L"HalfWidth"
#define kHeightName L"HalfHeight"
#define kLengthName L"HalfLength"

#define kMinWidth 0.1
#define kMaxWidth 10.0

#define kMinHeight 0.1
#define kMaxHeight 10.0

#define kMinLength 0.1
#define kMaxLength 10.0

SICALLBACK Pyramid_Define( const CRef& in_ref )
{
	Context in_ctxt( in_ref );
	CustomPrimitive in_prim( in_ctxt.GetSource() );
	if( in_prim.IsValid() )
	{
		Factory l_fact = Application().GetFactory();
		CRef l_widthDef = l_fact.CreateParamDef( kWidthName, CValue::siDouble, 1.0, kMinWidth, kMaxWidth );
		CRef l_heightDef = l_fact.CreateParamDef( kHeightName, CValue::siDouble, 1.0, kMinHeight, kMaxHeight );
		CRef l_lengthDef = l_fact.CreateParamDef( kLengthName, CValue::siDouble, 1.0, kMinLength, kMaxLength );
		Parameter l_width;
		Parameter l_height;
		Parameter l_length;
		in_prim.AddParameter( l_widthDef, l_width );
		in_prim.AddParameter( l_heightDef, l_height );
		in_prim.AddParameter( l_lengthDef, l_length );
	}
	return CStatus::OK;
}

SICALLBACK Pyramid_Draw( const CRef& in_ref )
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

	double pyrHalfWidth = params.GetValue( kWidthName );
	double pyrHalfHeight = params.GetValue( kHeightName );
	double pyrHalfLength = params.GetValue( kLengthName );

    // Note: the custom primitive API doesn't protect the OpenGL state
    //       for performance reasons. It is the duty of the custom primitive
    //       to leave the OpenGL state as it was on entry.

	// Draw pyramid
	//
	double pyrBaseMinPt[3];
	double pyrBaseMaxPt[3];
	double pyrPinnaclePt[3];

	pyrBaseMinPt[0] = -pyrHalfWidth;
	pyrBaseMinPt[1] = -pyrHalfHeight;
	pyrBaseMinPt[2] = -pyrHalfLength;

	pyrBaseMaxPt[0] = pyrHalfWidth;
	pyrBaseMaxPt[1] = -pyrHalfHeight;
	pyrBaseMaxPt[2] = pyrHalfLength;

	pyrPinnaclePt[0] = 0.0;
	pyrPinnaclePt[1] = pyrHalfHeight;
	pyrPinnaclePt[2] = 0.0;

	GLdouble l_Verts[5][3];

	l_Verts[0][0] = pyrBaseMinPt[0];
	l_Verts[0][1] = pyrBaseMinPt[1];
	l_Verts[0][2] = pyrBaseMinPt[2];

	l_Verts[1][0] = pyrBaseMinPt[0];
	l_Verts[1][1] = pyrBaseMinPt[1];
	l_Verts[1][2] = pyrBaseMaxPt[2];

	l_Verts[2][0] = pyrBaseMaxPt[0];
	l_Verts[2][1] = pyrBaseMaxPt[1];
	l_Verts[2][2] = pyrBaseMaxPt[2];

	l_Verts[3][0] = pyrBaseMaxPt[0];
	l_Verts[3][1] = pyrBaseMaxPt[1];
	l_Verts[3][2] = pyrBaseMinPt[2];

	l_Verts[4][0] = pyrPinnaclePt[0];
	l_Verts[4][1] = pyrPinnaclePt[1];
	l_Verts[4][2] = pyrPinnaclePt[2];


	::glBegin( GL_LINE_STRIP );
	::glVertex3dv( l_Verts[0] );
	::glVertex3dv( l_Verts[1] );
	::glVertex3dv( l_Verts[2] );
	::glVertex3dv( l_Verts[3] );
	::glVertex3dv( l_Verts[0] );
	::glVertex3dv( l_Verts[4] );
	::glVertex3dv( l_Verts[2] );
	::glEnd();

	::glBegin( GL_LINE_STRIP );
	::glVertex3dv( l_Verts[3] );
	::glVertex3dv( l_Verts[4] );
	::glVertex3dv( l_Verts[1] );
	::glEnd();

	return CStatus::OK;
}

SICALLBACK Pyramid_BoundingBox( const CRef& in_ref )
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

	double pyrHalfWidth = params.GetValue( kWidthName );
	double pyrHalfHeight = params.GetValue( kHeightName );
	double pyrHalfLength = params.GetValue( kLengthName );

	in_ctxt.PutAttribute( "LowerBoundX", -pyrHalfWidth );
	in_ctxt.PutAttribute( "LowerBoundY", -pyrHalfHeight );
	in_ctxt.PutAttribute( "LowerBoundZ", -pyrHalfLength );
	in_ctxt.PutAttribute( "UpperBoundX", pyrHalfWidth );
	in_ctxt.PutAttribute( "UpperBoundY", pyrHalfHeight );
	in_ctxt.PutAttribute( "UpperBoundZ", pyrHalfLength );

	return CStatus::OK;
}

SICALLBACK OnCustomPyramidMenuItem( CRef& in_ref )
{
	Context ctxt( in_ref );
	MenuItem menuItem = ctxt.GetSource();

    Application app;
	CValue out_arg;
	CValueArray in_args;
	in_args.Add( L"Pyramid" );
	app.ExecuteCommand( "GetPrim", in_args, out_arg );

    return CStatus::OK;
}
