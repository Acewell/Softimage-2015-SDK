// CustomPrimitives example
//
//	Copyright 2012 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

#ifndef linux
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h> // Needed for OpenGL on windows
#endif
#include <GL/gl.h>
#include <GL/glu.h>

#include <xsi_application.h>
#include <xsi_context.h>
#include <xsi_pluginregistrar.h>
#include <xsi_status.h>
#include <xsi_menu.h>

using namespace XSI; 

extern GLUquadric* g_quadric = NULL;

SICALLBACK XSILoadPlugin( PluginRegistrar& in_reg )
{
	in_reg.PutAuthor(L"Autodesk");
	in_reg.PutName(L"CustomPrimitives Plug-in");
	in_reg.PutVersion(1,0);

	// Sample primitives
	//
	in_reg.RegisterPrimitive( "Tri" );
	in_reg.RegisterPrimitive( "Rect" );
	in_reg.RegisterPrimitive( "Quad" );
	in_reg.RegisterPrimitive( "Box" );
	in_reg.RegisterPrimitive( "QuadPrism" );
	in_reg.RegisterPrimitive( "Pyramid" );
	in_reg.RegisterPrimitive( "Capsule" );
	in_reg.RegisterPrimitive( "Test" );
	in_reg.RegisterPrimitive( "CustomCylinder" );

	// Event used to update the box primitive cache.
	//
	in_reg.RegisterEvent( "BoxCacheObjectRemoved", siOnObjectRemoved );
	in_reg.RegisterEvent( "BoxCacheSceneOpen", siOnBeginSceneOpen );

	in_reg.RegisterMenu(siMenuTbGetPrimitiveImplicitID, L"CustomPrimitivesMenu", false, true );
	in_reg.RegisterMenu(siMenuTbGetPrimitivePolygonMeshID, L"CustomPrimitivesMeshMenu", false, true );

	// Init generic GLU quadric for use in this plug-in
	//
	if( g_quadric != NULL )
	{
		::gluDeleteQuadric( g_quadric );
		g_quadric = NULL;
	}
	g_quadric = ::gluNewQuadric();
	if( !g_quadric )
	{
		return CStatus::Fail;
	}
	::gluQuadricDrawStyle( g_quadric, GLU_LINE );

	//RegistrationInsertionPoint - do not remove this line

	Application().LogMessage(L"CustomPrimitives Plug-in has been loaded.",siInfoMsg);
	return CStatus::OK;
}

SICALLBACK XSIUnloadPlugin( const PluginRegistrar& in_reg )
{
	// Delete generic GLU quadric
	//
	if( g_quadric != NULL )
	{
		::gluDeleteQuadric( g_quadric );
		g_quadric = NULL;
	}

	CString strPluginName;
	strPluginName = in_reg.GetName();
	Application().LogMessage(strPluginName + L" has been unloaded.",siInfoMsg);
	return CStatus::OK;
}

SICALLBACK CustomPrimitivesMenu_Init( const CRef& in_ref )
{
	// retrieve the menu object to build
    Menu menu = Context( in_ref ).GetSource();

    // set the menu caption
    menu.PutName( L"&Custom Primitives" );

    // adds other menu items and attach a function callback
	MenuItem menuItem;
	menu.AddCallbackItem( L"Box", L"OnCustomBoxMenuItem", menuItem );
	menu.AddCallbackItem( L"Tri", L"OnCustomTriMenuItem", menuItem );
	menu.AddCallbackItem( L"Capsule", L"OnCustomCapsuleMenuItem", menuItem );
	menu.AddCallbackItem( L"Rect", L"OnCustomRectMenuItem", menuItem );
	menu.AddCallbackItem( L"Quad", L"OnCustomQuadMenuItem", menuItem );
	menu.AddCallbackItem( L"QuadPrism", L"OnCustomQuadPrismMenuItem", menuItem );
	menu.AddCallbackItem( L"Pyramid", L"OnCustomPyramidMenuItem", menuItem );
	menu.AddCallbackItem( L"Cylinder", L"OnCustomCylinderMenuItem", menuItem );

    return CStatus::OK;
}

SICALLBACK CustomPrimitivesMeshMenu_Init( const CRef& in_ref )
{
	// retrieve the menu object to build
	Menu menu = Context( in_ref ).GetSource();

	// set the menu caption
	menu.PutName( L"&Custom Mesh Primitives" );

	// adds other menu items and attach a function callback
	MenuItem menuItem;
	menu.AddCallbackItem( L"Tri", L"OnCustomTriMeshMenuItem", menuItem );
	menu.AddCallbackItem( L"Box", L"OnCustomBoxMeshMenuItem", menuItem );

	return CStatus::OK;
}



