//--------------------------------------------------------------------------
// simplemenu.js: This file shows how to implement and registered a simple
// menu plugin with JScript. 
//
// Note: Look at simplemenu.htm for more details about this sample.
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// XSILoadPlugin: Entry-point called by Softimage when this file gets loaded. All 
// plugin items exposed here must be registered in this function. 
//
// in_reg: PluginRegistrar object required for registering the plugin 
// items and some information about this plugin.
//
// *note* This function is mandatory and must be implemented. The plugin will 
// not be loaded if this function is missing.
//--------------------------------------------------------------------------

function XSILoadPlugin( in_reg )
{
	// register plugin information
	in_reg.Author = "Softimage Corp." ;
	in_reg.Name = "JScript Simple menu plug-in";

	// set the version number of this plugin
	in_reg.Major = 1;
	in_reg.Minor = 0 ;

	// register a menu plugin under Model|Get|Primitive|Polygon Mesh menu in 
	// the toolbar panel
	in_reg.RegisterMenu( siMenuTbGetPrimitivePolygonMeshBasicID, 
		"JScript Simple Menu" );

	// register a help menu for the simple menu
	bDynamic = false;
	bDisplayAsSubmenu = false;
	in_reg.RegisterMenu( siMenuMainHelpID, "JScript Simple Help Menu", 
		bDisplayAsSubmenu, bDynamic );

	return true;
}

//--------------------------------------------------------------------------
// XSIUnloadPlugin: Entry-point called by Softimage when this file gets unloaded. 
// All plugin items registered by this plugin are automatically unregistered 
// by Softimage. Use this function to perform internal cleanup.
//
// arg in_reg: PluginRegistrar object.
//
// *note* This function is optional.
//--------------------------------------------------------------------------
function XSIUnloadPlugin( in_reg )
{
	Logmessage( in_reg.name + " has been unloaded." );
	return true;
}

//--------------------------------------------------------------------------
// JScriptSimpleMenu_Init: Entry-point called by Softimage when the menu 
// "Simple JScript Menu" is opened by the user. This callback is typically
// used for setting the menu properties such as name and filter, and for 
// defining the menu items.
//
// arg in_ctxt: A Context object holding the custom Menu object to define
//
//--------------------------------------------------------------------------
function JScriptSimpleMenu_Init( in_ctxt )
{
	var menu = in_ctxt.source;

	menu.name = "&More JScript ...";

	menu.AddCommandItem( "Another &Sphere", "Mesh Sphere" );
	menu.AddCommandItem( "Another &Torus", "Mesh Torus" );
	menu.AddSeparatorItem();
	menu.AddCallbackItem( "Yet another &Cube", "OnCreateCube" );

	return true;
}

//--------------------------------------------------------------------------
// OnCreateCube: Entry-point called by Softimage when the menu item is selected.
// This function creaes a surface mesh cube.
//
// arg in_ctxt: A Context object holding the custom MenuItem object selected by
// the user.
//
//--------------------------------------------------------------------------
function OnCreateCube( in_ctxt )	
{
	CreatePrim( "Cube", "MeshSurface" );
	return true;
}

function JScriptSimpleHelpMenu_Init( in_ctxt )
{
	var menu = in_ctxt.source;

	menu.AddCallbackItem( "JScript Simple Menu Help", "OnSimpleHelpMenu" );

	return true;
}

function OnSimpleHelpMenu( in_ctxt )
{
	// get a netview window if one exists or create a new one
	var layout = Application.Desktop.ActiveLayout;

	var netView = layout.Views( "netview" );
	if ( ClassName(netView) == "" )
	{
		netView = layout.CreateView( "netview", "netview" );
	}
	
	// set the net view url with the simeple menu help file and show it
	var plugin = Application.Plugins("JScript Simple menu plug-in");

	netView.Resize( 600, 800 );
	netView.SetAttributeValue( "url", plugin.Help );
	netView.State = siNormal

	return true;
}