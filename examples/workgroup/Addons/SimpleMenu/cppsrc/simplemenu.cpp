//*****************************************************************************
/*
	\file simplemenu.cpp 
	\brief Implementation of the SDK Simple Menu example
	\author Marc-André Belzile

	Note: Look at simplemenu.htm for more details about this sample.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   

*/
//*****************************************************************************


#include <xsi_ref.h>
#include <xsi_value.h>
#include <xsi_status.h>
#include <xsi_pluginregistrar.h>
#include <xsi_pluginitem.h>
#include <xsi_plugin.h>
#include <xsi_menuitem.h>
#include <xsi_menu.h>
#include <xsi_x3dobject.h>
#include <xsi_application.h>
#include <xsi_primitive.h>
#include <xsi_geometry.h>
#include <xsi_context.h>
#include <xsi_decl.h>
#include <xsi_layout.h>
#include <xsi_view.h>
#include <xsi_desktop.h>
#include <xsi_selection.h>

using namespace XSI;

/*!
	Entry-point called by Softimage when this file gets loaded. All plugin items 
	exposed here must be registered in this function. 

	\param in_reg: PluginRegistrar object required for registering the plugin 
	items and some information about this plugin.

	*note* This function is mandatory and must be implemented. The plugin will    
	not be loaded if this function is missing.
*/
XSIPLUGINCALLBACK CStatus XSILoadPlugin( XSI::PluginRegistrar& in_reg )
{
	in_reg.PutAuthor( L"Softimage Corp" );
	in_reg.PutName( L"C++ Simple Menu Plug-in" );
	in_reg.PutVersion( 1, 0 );

	bool bDisplayAsSubmenu = true;
	bool bDynamic = true;

	// register filters which are going to be used by the Simple Menu
	in_reg.RegisterFilter( L"SimpleMeshFilter", siFilterObject );
	in_reg.RegisterFilter( L"SimpleMaterialFilter", siFilterObject );

	bDisplayAsSubmenu = false;
	bDynamic = false;

	// register a save menu plugin 
	in_reg.RegisterMenu(	siMenuMainFileSceneID, 
							L"Simple Save Scene Menu", 
							bDisplayAsSubmenu, 
							bDynamic );

	// register a load project menu plugin 
	in_reg.RegisterMenu(	siMenuMainFileProjectID, 
							L"Simple Load Project Menu", 
							bDisplayAsSubmenu, 
							bDynamic );

	// register an export menu plugin 
	in_reg.RegisterMenu(	siMenuMainFileExportID, 
							L"Simple Export Menu", 
							bDisplayAsSubmenu, 
							bDynamic );

	// register an import menu plugin 
	in_reg.RegisterMenu(	siMenuMainFileImportID, 
							L"Simple Import Menu", 
							bDisplayAsSubmenu, 
							bDynamic );

	// register a window menu plugin 
	in_reg.RegisterMenu(	siMenuMainWindowID, 
							L"Simple Window Menu", 
							bDisplayAsSubmenu, 
							bDynamic );

	// register a menu plug-in to be used by both the Scene Explorer's 
	// cluster and 3DView's cluster contextual menu
	in_reg.RegisterMenu(	siMenuSEClusterContextID, 
							L"Simple Cluster Menu", 
							bDisplayAsSubmenu, 
							bDynamic );

	in_reg.RegisterMenu(	siMenu3DViewClusterContextID, 
							L"Simple Cluster Menu", 
							bDisplayAsSubmenu, 
							bDynamic );

	// register help menu plugin 
	in_reg.RegisterMenu(	siMenuMainHelpID, 
							L"Simple Help Menu", 
							bDisplayAsSubmenu, 
							bDynamic );

	// register a top level menu 
	bDisplayAsSubmenu = true;
	bDynamic = true;
	in_reg.RegisterMenu(	siMenuTbDeformID, 
							L"Simple Menu", 
							bDisplayAsSubmenu, 
							bDynamic );

	return XSI::CStatus::OK;	
}

/*!
	Entry-point called by Softimage when this file gets unloaded. All plugin items 
	registered by this plugin are automatically unregistered by Softimage. Use this 
	function to perform internal cleanup.

	\param in_reg PluginRegistrar object.

	*note* This function is optional.
*/
XSIPLUGINCALLBACK XSI::CStatus XSIUnloadPlugin( const XSI::PluginRegistrar& in_reg )
{
	Application app;
	app.LogMessage( in_reg.GetName() + L" has been unloaded.");

	return XSI::CStatus::OK;
}

/*! 
	Entry-point called by Softimage when the simple window menu is opened by the user.
	This callback is typically used for defining the menu items and for setting 
	the menu properties such as the name and filter.

	\param in_ref Context object holding the Menu object being defined
*/
// in_ref
XSIPLUGINCALLBACK XSI::CStatus SimpleWindowMenu_Init( XSI::CRef& in_ref )
{
	Context ctxt = in_ref;
	Menu menu = ctxt.GetSource();

	// adds a calback menu item: the supplied callback function is called
	// by Softimage when the user selects the menu item.
	MenuItem item;
	CStatus st = menu.AddCallbackItem( L"Cascade", L"OnCascadeMenu", item );
	if (st != CStatus::OK) return st;

	return CStatus::OK;	
}

XSIPLUGINCALLBACK XSI::CStatus SimpleWindowMenu_Term( XSI::CRef& in_ref )
{
	Context ctxt = in_ref;
	Menu menu = ctxt.GetSource();

	Application app;
	app.LogMessage( menu.GetName() + L" has been terminated.");

	return CStatus::OK;	
}

XSIPLUGINCALLBACK XSI::CStatus SimpleWindowMenu_Unload( XSI::CRef& in_ref )
{
	Context ctxt = in_ref;
	Menu menu = ctxt.GetSource();

	Application app;
	app.LogMessage( menu.GetName() + L" has been unloaded.");

	return CStatus::OK;	
}

XSIPLUGINCALLBACK XSI::CStatus SimpleWindowMenu_Reload( XSI::CRef& in_ref )
{
	Context ctxt = in_ref;
	Menu menu = ctxt.GetSource();

	Application app;
	app.LogMessage( menu.GetName() + L" has been reloaded.");

	return CStatus::OK;	
}

/*
	Entry-point called by Softimage when the user has selected the cascade menu item.
	The cascade callback arranges all open views in overlapping windows.

	\param in_ref Context object holding the selected MenuItem object.
*/

XSIPLUGINCALLBACK XSI::CStatus OnCascadeMenu( XSI::CRef& )
{	
	Application app;

	Layout layout = app.GetDesktop().GetActiveLayout();

	// position for the first view to cascade
	LONG px = 50;
	LONG py = 20;

	// delta between each view
	LONG dx = 20;
	LONG dy = 20;

	CRefArray views = layout.GetViews();
	for ( LONG i=0; i<views.GetCount() ; i++)
	{
		View vw = views[i];
		if( vw.GetFloating() )
		{
			vw.Move( px, py );
			vw.Resize( 400, 400 );
			px += dx;
			py += dy;
			vw.PutState( siNormal ); // put view at the top so far
		}
	}

	return CStatus::OK;	
}

XSIPLUGINCALLBACK XSI::CStatus SimpleHelpMenu_Init( XSI::CRef& in_ref )
{
	Context ctxt = in_ref;
	Menu menu = ctxt.GetSource();

	CStatus st;
	MenuItem item;
	st = menu.AddCallbackItem( L"C++ Simple Menu Help", L"OnSimpleHelpMenu", 
		item );
	if (st != CStatus::OK) return st;

	return CStatus::OK;	
}

// help menu item callback
XSIPLUGINCALLBACK XSI::CStatus OnSimpleHelpMenu( XSI::CRef& )
{	
	Application app;

	// get a netview window if one exists or create a new one
	Layout layout = app.GetDesktop().GetActiveLayout();

	View netView = layout.GetViews().GetItem( L"netview" );
	if (!netView.IsValid())
	{
		 CStatus st = layout.CreateView( L"netview", L"netview", netView );
		 if (!st.Succeeded())
		 {
			return st.GetCode();
		 }
	}
	
	// show the simple menu help file in net view 
	Plugin plugin = app.GetPlugins().GetItem(L"C++ Simple Menu Plug-in");
	netView.Resize( 600, 800 );
	netView.PutAttributeValue( L"url", plugin.GetHelp() );
	netView.PutState( siNormal );

	return CStatus::OK;	
}

XSIPLUGINCALLBACK XSI::CStatus SimpleSaveSceneMenu_Init( XSI::CRef& in_ref )
{
	Context ctxt = in_ref;
	Menu menu = ctxt.GetSource();

	MenuItem item;
	CStatus st = menu.AddCallbackItem( L"Simple Save Scene", 
		L"OnSimpleMenuItem", item );
	if (st != CStatus::OK) return st;

	return CStatus::OK;	
}

XSIPLUGINCALLBACK XSI::CStatus SimpleLoadProjectMenu_Init( XSI::CRef& in_ref )
{
	Context ctxt = in_ref;
	Menu menu = ctxt.GetSource();

	CStatus st;
	MenuItem item;
	st = menu.AddCallbackItem( L"Simple Load Project", L"OnSimpleMenuItem", 
		item );
	if (st != CStatus::OK) return st;

	return CStatus::OK;	
}

XSIPLUGINCALLBACK XSI::CStatus SimpleExportMenu_Init( XSI::CRef& in_ref )
{
	Context ctxt = in_ref;
	Menu menu = ctxt.GetSource();

	CStatus st;
	MenuItem item;
	st = menu.AddCallbackItem( L"Simple Export", L"OnSimpleMenuItem", item );
	if (st != CStatus::OK) return st;

	return CStatus::OK;	
}

XSIPLUGINCALLBACK XSI::CStatus SimpleImportMenu_Init( XSI::CRef& in_ref )
{
	Context ctxt = in_ref;
	Menu menu = ctxt.GetSource();

	CStatus st;
	MenuItem item;
	st = menu.AddCallbackItem( L"Simple Import", L"OnSimpleMenuItem", item );
	if (st != CStatus::OK) return st;

	return CStatus::OK;	
}

XSIPLUGINCALLBACK XSI::CStatus SimpleClusterMenu_Init( XSI::CRef& in_ref )
{
	Context ctxt = in_ref;
	Menu menu = ctxt.GetSource();

	// this menu will appear in the cluster menu only if the target object is 
	// a cluster polygon
	menu.PutFilter( L"Polygon" );

	CStatus st;
	MenuItem item;
	st = menu.AddCallbackItem(L"Log Cluster Polygon", L"OnSimpleMenuItem", item);
	if (st != CStatus::OK) return st;

	return CStatus::OK;	
}

// generic callback which logs the menu item being selected
XSIPLUGINCALLBACK XSI::CStatus OnSimpleMenuItem( XSI::CRef& in_ref )
{	
	Context ctxt = in_ref;
	MenuItem menuItem = ctxt.GetSource();

	Menu menu = menuItem.GetParent();

	Application app;
	CString strMsg(menu.GetName());

	strMsg += L":";
	strMsg += menuItem.GetName();
	strMsg += L":OnSimpleMenuItem";

	app.LogMessage(strMsg);

	// get the context array object if the menu item is part of a contextual
	// menu
	CValue target = ctxt.GetAttribute( L"Target" );
	if (target.m_t == CValue::siArray)
	{
		// log target objects
		CValueArray targets = target;
		for (LONG i=0; i<targets.GetCount(); i++)
		{
			SIObject siObj(targets[i]);
			app.LogMessage( strMsg + L":" + targets[i].GetAsText() + L":" + 
				siObj.GetName());			
		}
	}

	return CStatus::OK;	
}

// apply deformers on the first selected object
XSIPLUGINCALLBACK XSI::CStatus OnTwistBendItem( XSI::CRef& in_ref )
{	
	Context ctxt = in_ref;
	MenuItem menuItem = ctxt.GetSource();

	// log some message
	Application app;
	app.LogMessage( menuItem.GetName() + L": OnTwistBendItem");

	// apply deformers on the first selected object
	CValue retVal;
	CValueArray args(5);
	args[0] = L"Twist";
	args[1] = app.GetSelection()[0];
	app.ExecuteCommand( L"ApplyOp", args, retVal );	

	args[0] = L"Bend";
	app.ExecuteCommand( L"ApplyOp", args, retVal );	

	return CStatus::OK;	
}

// Polygon mesh filter implementation. Returns true if the geometry of the 
// input object is a mesh
XSIPLUGINCALLBACK bool SimpleMeshFilter_Match( const XSI::CRef& in_ctxt )
{	
	X3DObject obj;
	Context ctxt = in_ctxt;
	CRef ref = ctxt.GetAttribute( L"Input" );	

	if (ref.IsA( siX3DObjectID ))
	{
		obj = ref;
	}
	else if (ref.IsA( siPrimitiveID ))
	{
		obj = SIObject(ref).GetParent();
	}
	else 
	{
		return false;
	}

	return obj.GetActivePrimitive().GetGeometry().IsA( siPolygonMeshID )== true;
}

// Material filter implementation. Returns true if the input object is a 
// material.
XSIPLUGINCALLBACK bool SimpleMaterialFilter_Match( const XSI::CRef& in_ctxt )
{	
	X3DObject obj;
	Context ctxt = in_ctxt;
	CRef ref = ctxt.GetAttribute( L"Input" );	

	return ref.IsA( siMaterialID );
}

XSIPLUGINCALLBACK XSI::CStatus SimpleMenu_Init( XSI::CRef& in_ref )
{
	Context ctxt = in_ref;
	Menu menu = ctxt.GetSource();

	// set the filter for this menu, the menu items are enabled only if one 
	// or more polygon mesh objects are selected
	menu.PutFilter( L"SimpleMeshFilter" );

	// 1st menu item: callback which applies a twist and a bend deformer to
	// the selected object
	MenuItem item;
	CStatus st = menu.AddCallbackItem(	L"Twist + Bend", 
										L"OnTwistBendItem", 
										item );
	if (st != CStatus::OK) return st;

	menu.AddSeparatorItem();

	// 2nd menu item: create a submenu 	
	Menu subMenu = menu.AddSubMenu( L"More..." );
	if (subMenu.IsValid() != true) return CStatus::Fail;

	// 1st submenu item: adds a Bulge command which will be called when the item 
	// is selected
	st = subMenu.AddCommandItem( L"&Bulge", L"Bulge", item );
	if (st != CStatus::OK) return st;

	// 2nd submenu item: adds a Shear command which will be called when the item 
	// is selected
	st = subMenu.AddCommandItem( L"&Shear", L"Shear", item );
	if (st != CStatus::OK) return st;

	menu.AddSeparatorItem();

	MenuItem matMenuItem;
	st = menu.AddCallbackItem(	L"Log Material", 
								L"OnLogMaterialName", 
								matMenuItem );
	if (st != CStatus::OK) return st;

	// Set the "Log Material" menu item with the material filter, the item 
	// will be enable only if the selected object is a material
	matMenuItem.PutFilter( L"SimpleMaterialFilter" );
	
	return CStatus::OK;	
}

// Log Material menu item callback
XSIPLUGINCALLBACK XSI::CStatus OnLogMaterialName( XSI::CRef& in_ref )
{	
	Application app;
	app.LogMessage(	CString(L"Material name: ") + 
					SIObject(app.GetSelection()[0]).GetFullName() );
	return CStatus::OK;	
}

