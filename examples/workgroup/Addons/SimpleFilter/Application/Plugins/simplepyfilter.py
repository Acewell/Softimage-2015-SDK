#--------------------------------------------------------------------------
# simplepyfilter.py: This file shows how to implement and registered a simple
# filter plugin in Python. The plugin is used for filtering polygon mesh geometries that
# contain more than 50 points.
#
#
#	Copyright 2008 Autodesk, Inc.  All rights reserved.  
#	Use of this software is subject to the terms of the Autodesk license agreement 
#	provided at the time of installation or download, or which otherwise accompanies 
#	this software in either electronic or hard copy form.   
#--------------------------------------------------------------------------
from win32com.client import constants

#--------------------------------------------------------------------------
# XSILoadPlugin: Entry-point called by Softimage when this file gets loaded. All 
# plugin items exposed here must be registered in this function. 
#
# arg in_reg: PluginRegistrar object required for registering the plugin 
# items and some information about this plugin.
#
# *note* This function is mandatory and must be implemented. The plugin will 
# not be loaded if this function is missing.
#--------------------------------------------------------------------------
def XSILoadPlugin( in_reg ):

	# register plugin information
	in_reg.Author = "Softimage Corp.";
	in_reg.Name = "Python Simple filter plug-in";

	# var the version number of this plugin
	in_reg.Major = 1;
	in_reg.Minor = 0 ;

	# register filter plugin item
	in_reg.RegisterFilter( "Python Simple Filter", constants.siFilter3DObject );
	in_reg.RegisterProperty("PythonFilterProp")
	in_reg.RegisterMenu(	constants.siMenuMainTopLevelID, 
							"PythonFilterMenu",
							False,False)

	strPluginName = in_reg.Name
	Application.LogMessage(str(strPluginName) + str(" has been loaded."),constants.siVerbose)
	
	return True;


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
	return True;


#--------------------------------------------------------------------------
# PythonSimpleFilter_Match: Returns true if the object is a polygon mesh with 
# the number of points set by the python filter PPG.
#
# in_ctxt: Filter context. The context contains this specific attribute:
#   Input: Object to filter.
#
# *note* This function is mandatory and must be implemented.
#--------------------------------------------------------------------------
def PythonSimpleFilter_Match( in_ctxt ):

	in_object = in_ctxt.GetAttribute( "Input" );

	obj = Get3DObject( in_object );
	if ( Application.ClassName(obj) != "X3DObject" ):
		return false;
	
	nPoints = obj.ActivePrimitive.Geometry.Points.Count
	Application.LogMessage( "nb selected points " + str(nPoints), constants.siVerbose )
	
	filterProp = GetFilterProp( )
	nFilteredPoints = filterProp.NPoints.Value;
	Application.LogMessage( "nd points to filter " + str(nFilteredPoints), constants.siVerbose )
	
	return nPoints > nFilteredPoints;

#--------------------------------------------------------------------------
# Show Filter PPG when the filter gets created
#--------------------------------------------------------------------------
def PythonSimpleFilter_Init( in_ctxt ):

	filter = in_ctxt.Source;

	Application.LogMessage( "Initializing : " + filter.Name, constants.siVerbose );		


#--------------------------------------------------------------------------
#Optional callback to perform cleanup when the filter is delted
#--------------------------------------------------------------------------
def PythonSimpleFilter_Term( in_ctxt ):

	filter = in_ctxt.Source;

	Application.LogMessage( "Terminating : " + filter.Name, constants.siVerbose );


#--------------------------------------------------------------------------
# Helper to get an X3DObject
#--------------------------------------------------------------------------
def Get3DObject( in_object ):

	objClass = Application.ClassName(in_object);
	if (objClass == "X3DObject"):	
		obj = in_object;	
	elif ( objClass == "Primitive" ):	
		obj = in_object.Parent;
	
	return obj;

#--------------------------------------------------------------------------
# PythonFilterProp_Define: Defines the custom property for Python Simple Filter
#--------------------------------------------------------------------------

def PythonFilterProp_Define( ctxt ):
	oCustomProperty = ctxt.Source
	oCustomProperty.AddParameter2("NPoints",constants.siInt4,50,10,1000000,10,100,0,constants.siPersistable)
	return True;

def PythonFilterProp_DefineLayout( ctxt ):
	oLayout = ctxt.Source
	oLayout.Clear()
	oLayout.AddItem("NPoints", "Min. Filter Points")
	return True;

#--------------------------------------------------------------------------
# GetFilterProp: Helper to return the filter custom property.
#--------------------------------------------------------------------------
def GetFilterProp( ):

	strName = "PythonFilterProp"
	root = Application.ActiveSceneRoot;
	
	try:
		prop = root.Properties[ strName ];
		Application.LogMessage( "found existing prop: " + prop.Name, constants.siVerbose )
	except:
		prop = root.AddProperty( strName );
		Application.LogMessage( "new prop: " + prop.Name, constants.siVerbose )
	
	return prop ;

#--------------------------------------------------------------------------
# Display the Python Filter property page
#--------------------------------------------------------------------------
def ShowFilterProp( ):
	Application.InspectObj( GetFilterProp( ), "", "", constants.siLock );

#--------------------------------------------------------------------------
# PythonFilterMenu_Init: This menu opens the filter python PPG. 
#
# arg in_ctxt: A Context object holding the custom Menu object to define
#--------------------------------------------------------------------------
def PythonFilterMenu_Init( in_ctxt ):

	menu = in_ctxt.Source;

	menuitem = menu.AddCallbackItem( "Open PPG", "OnMenuItem" );

	return True;
	
def OnMenuItem( in_ctxt ):
	ShowFilterProp();
	return True;	
