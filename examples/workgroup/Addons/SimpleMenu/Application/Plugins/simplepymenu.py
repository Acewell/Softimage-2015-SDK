#--------------------------------------------------------------------------
# simplepymenu.py: This file shows how to implement and registered a simple
# menu plugin with Python. 
#
# Note: Look at netview_SimpleMenu.htm for more details about this sample.
#
#	Copyright 2008 Autodesk, Inc.  All rights reserved.  
#	Use of this software is subject to the terms of the Autodesk license agreement 
#	provided at the time of installation or download, or which otherwise accompanies 
#	this software in either electronic or hard copy form.   
#--------------------------------------------------------------------------
from win32com.client import constants
from win32com.client import Dispatch

null = None
true = 1
false = 0

#--------------------------------------------------------------------------
# XSILoadPlugin: Entry-point called by Softimage when this file gets loaded. All 
# plugin items exposed here must be registered in this function. 
#
# in_reg: PluginRegistrar object required for registering the plugin 
# items and some information about this plugin.
#
# *note* This function is mandatory and must be implemented. The plugin will 
# not be loaded if this function is missing.
#--------------------------------------------------------------------------

def XSILoadPlugin( in_reg ):

	# register plugin information
	in_reg.Author = "Softimage Corp." ;
	in_reg.Name = "Python Simple menu plug-in";

	# set the version number of this plugin
	in_reg.Major = 1;
	in_reg.Minor = 0 ;

	# register a menu plugin under Model|Get|Primitive|Polygon Mesh menu in 
	# the toolbar panel
	in_reg.RegisterMenu(	constants.siMenuTbGetPrimitivePolygonMeshBasicID, 
							"Python Simple Menu" );

	# register a help menu for the simple menu
	bDynamic = false;
	bDisplayAsSubmenu = false;
	in_reg.RegisterMenu(	constants.siMenuMainHelpID, 
							"Python Simple Help Menu", 
							bDisplayAsSubmenu, bDynamic );

	# register a top level menu 
	bDynamic = true;
	bDisplayAsSubmenu = false;	
	in_reg.RegisterMenu(	constants.siMenuMainTopLevelID, 
							"PythonTopLevelMenu", 
							bDisplayAsSubmenu, bDynamic );
		
	strPluginName = in_reg.Name
	Application.LogMessage(str(strPluginName) + str(" has been loaded."),constants.siVerbose)

	return true;

#--------------------------------------------------------------------------
# XSIUnloadPlugin: Entry-point called by Softimage when this file gets unloaded. 
# All plugin items registered by this plugin are automatically unregistered 
# by Softimage. Use this function to perform internal cleanup.
#
# arg in_reg: PluginRegistrar object.
#
# *note* This function is optional.
#--------------------------------------------------------------------------

def XSIUnloadPlugin( in_reg ):

	strPluginName = in_reg.Name
	Application.LogMessage(str(strPluginName) + str(" has been unloaded."),constants.siVerbose)

	return true


#--------------------------------------------------------------------------
# PythonSimpleMenu_Init: Entry-point called by Softimage when the menu 
# "Simple Python Menu" is opened by the user. This callback is typically
# used for setting the menu properties such as name and filter, and for 
# defining the menu items.
#
# arg in_ctxt: A Context object holding the custom Menu object to define
#
#--------------------------------------------------------------------------
def PythonSimpleMenu_Init( in_ctxt ):

	menu = in_ctxt.Source;
	menu.Name = "&More Python ...";

	menu.AddCommandItem( "Another &Sphere", "Mesh Sphere" );
	menu.AddCommandItem( "Another &Torus", "Mesh Torus" );
	menu.AddSeparatorItem();
	menu.AddCallbackItem( "Yet another &Cube", "OnCreateCube" );

	return true;


#--------------------------------------------------------------------------
# OnCreateCube: Entry-point called by Softimage when the menu item is selected.
# This function creaes a surface mesh cube.
#
# arg in_ctxt: A Context object holding the custom MenuItem object selected by
# the user.
#
#--------------------------------------------------------------------------
def OnCreateCube( in_ctxt ):

	Application.CreatePrim( "Cube", "MeshSurface" );
	
	return true;


#--------------------------------------------------------------------------
# PythonSimpleHelpMenu_Init: Entry-point called by Softimage when the menu 
# "Python Simple Menu Help" is opened by the user. This callback is typically
# used for setting the menu properties such as name and filter, and for 
# defining the menu items.
#
# arg in_ctxt: A Context object holding the custom Menu object to define
#
#--------------------------------------------------------------------------
def PythonSimpleHelpMenu_Init( in_ctxt ):

	menu = in_ctxt.Source;
	
	menu.AddCallbackItem( "Python Simple Menu Help", "OnSimpleHelpMenu" );

	return true;

#--------------------------------------------------------------------------
# OnSimpleHelpMenu: Display this plug-in help page in a NetView
#--------------------------------------------------------------------------
def OnSimpleHelpMenu( in_ctxt ):

	# get a netview window if one exists or create a new one
	layout = Application.Desktop.ActiveLayout;

	netView = layout.Views( "netview" );
	if ( Application.ClassName(netView) == "" ):
	
		netView = layout.CreateView( "netview", "netview" );
	
	
	# set the net view url with the simple menu help file and show it
	plugin = Application.Plugins("Python Simple menu plug-in");

	netView.Resize( 600, 800 );
	netView.SetAttributeValue( "url", plugin.Help );
	netView.State = constants.siNormal

	return true;


#--------------------------------------------------------------------------
# PythonTopLevelMenu_Init: This menu is used to demonstrate the usage of 
# the MenuItem.Enabled and MenuItem.Filter properties. 
#
# Note: For this example to work properly, the toplevel menu must have been 
# registered as a dynamic menu.
#
# arg in_ctxt: A Context object holding the custom Menu object to define
#
#--------------------------------------------------------------------------
def PythonTopLevelMenu_Init( in_ctxt ):

	menu = in_ctxt.Source;

	menuitem = menu.AddCallbackItem( "This menu is set with the PolygonMesh filter and is only enabled when a mesh is selected", "OnMenuItem" );
	menuitem.Filter = Application.Filters("PolygonMesh");

	menuitem = menu.AddCallbackItem( "This menu is enabled when no object is selected", "OnMenuItem" );
	if (Application.Selection.Count):
		menuitem.Enabled = False;

	menuitem = menu.AddCallbackItem( "This menu is enabled when no object is selected but can also be enabled if a mesh is selected", "OnMenuItem" );
	if (Application.Selection.Count):
		menuitem.Filter = Application.Filters("PolygonMesh");
	else:
		menuitem.Enabled = True;		

	submenu = menu.AddSubMenu( "This sub-menu is enabled when a mesh is selected" );
	submenu.Filter = Application.Filters("PolygonMesh");

	# Note: Sometimes Python cannot figured out automation objects by himself, we need to give him a hand
	menuitem = submenu.AddCallbackItem( "This menu is always disabled", "OnMenuItem" );
	menuitem.Enabled = False;

	menuitem = submenu.AddCallbackItem( "This menu is always enabled", "OnMenuItem" );

	menuitem = submenu.AddCallbackItem( "This menu is only enabled for small objects (<50 points)", "OnMenuItem" );
	selected = Application.Selection(0);
	if ( selected != None and selected.IsClassOf( constants.siX3DObjectID ) ):
		geom = selected.ActivePrimitive.Geometry;
		if (geom != None and geom.Points.Count >= 50):
				menuitem.Enabled = False;
	
	return true;
	
def OnMenuItem( in_ctxt ):
	Application.LogMessage( in_ctxt.source.name + "menu has been clicked!" );
	return true;