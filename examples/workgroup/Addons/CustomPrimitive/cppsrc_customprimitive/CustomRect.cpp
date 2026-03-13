// CustomPrimitives example
//
//	Copyright 2012 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   
//
//	File:	CustomRect.cpp
//
//	Description:
//
//		Defines a rectangle primitive that is defined by 2 floating-point
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

using namespace XSI; 

// Defines
//
#define kWidthName L"HalfWidth"
#define kHeightName L"HalfHeight"

#define kMinWidth 0.1
#define kMaxWidth 100.0

#define kMinHeight 0.1
#define kMaxHeight 100.0

SICALLBACK Rect_Define( const CRef& in_ref )
{
	Context in_ctxt( in_ref );
	CustomPrimitive in_prim( in_ctxt.GetSource() );
	if( in_prim.IsValid() )
	{
		Factory l_fact = Application().GetFactory();
		CRef l_widthDef = l_fact.CreateParamDef( kWidthName, CValue::siDouble, 2.0, kMinWidth, kMaxWidth );
		CRef l_heightDef = l_fact.CreateParamDef( kHeightName, CValue::siDouble, 1.5, kMinHeight, kMaxHeight );
		Parameter l_width;
		Parameter l_height;
		in_prim.AddParameter( l_widthDef, l_width );
		in_prim.AddParameter( l_heightDef, l_height );
	}
	return CStatus::OK;
}

SICALLBACK Rect_Draw( const CRef& in_ref )
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

	double RectHalfWidth = params.GetValue( kWidthName );
	double RectHalfHeight = params.GetValue( kHeightName );

    // Note: the custom primitive API doesn't protect the OpenGL state
    //       for performance reasons. It is the duty of the custom primitive
    //       to leave the OpenGL state as it was on entry.

	// Draw Rect
	//
	double RectMinPt[3];
	double RectMaxPt[3];

	RectMinPt[0] = -RectHalfWidth;
	RectMinPt[1] = -RectHalfHeight;
	RectMinPt[2] = 0.0;

	RectMaxPt[0] = RectHalfWidth;
	RectMaxPt[1] = RectHalfHeight;
	RectMaxPt[2] = 0.0;

	GLdouble l_Verts[4][3];

	l_Verts[0][0] = RectMinPt[0];
	l_Verts[0][1] = RectMinPt[1];
	l_Verts[0][2] = 0.0;

	l_Verts[1][0] = RectMaxPt[0];
	l_Verts[1][1] = RectMinPt[1];
	l_Verts[1][2] = 0.0;

	l_Verts[2][0] = RectMaxPt[0];
	l_Verts[2][1] = RectMaxPt[1];
	l_Verts[2][2] = 0.0;

	l_Verts[3][0] = RectMinPt[0];
	l_Verts[3][1] = RectMaxPt[1];
	l_Verts[3][2] = 0.0;

	::glBegin( GL_LINE_STRIP );
	::glVertex3dv( l_Verts[0] );
	::glVertex3dv( l_Verts[1] );
	::glVertex3dv( l_Verts[2] );
	::glVertex3dv( l_Verts[3] );
	::glVertex3dv( l_Verts[0] );
	::glEnd();

	return CStatus::OK;
}

SICALLBACK Rect_BoundingBox( const CRef& in_ref )
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

	double RectHalfWidth = params.GetValue( kWidthName );
	double RectHalfHeight = params.GetValue( kHeightName );

	in_ctxt.PutAttribute( "LowerBoundX", -RectHalfWidth );
	in_ctxt.PutAttribute( "LowerBoundY", -RectHalfHeight );
	in_ctxt.PutAttribute( "LowerBoundZ", 0.0 );
	in_ctxt.PutAttribute( "UpperBoundX", RectHalfWidth );
	in_ctxt.PutAttribute( "UpperBoundY", RectHalfHeight );
	in_ctxt.PutAttribute( "UpperBoundZ", 0.0 );

	return CStatus::OK;
}

SICALLBACK OnCustomRectMenuItem( CRef& in_ref )
{
	Context ctxt( in_ref );
	MenuItem menuItem = ctxt.GetSource();

    Application app;
	CValue out_arg;
	CValueArray in_args;
	in_args.Add( L"Rect" );
	app.ExecuteCommand( "GetPrim", in_args, out_arg );

    return CStatus::OK;
}
