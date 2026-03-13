//--------------------------------------------------------------------------
// simplefilter.js: This file shows how to implement and registered a simple
// filter plugin in JScript. The plugin is used for filtering polygon mesh geometries that
// contain more than 50 points.
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
// arg in_reg: PluginRegistrar object required for registering the plugin 
// items and some information about this plugin.
//
// *note* This function is mandatory and must be implemented. The plugin will 
// not be loaded if this function is missing.
//--------------------------------------------------------------------------
function XSILoadPlugin( in_reg )
{
	// register plugin information
	in_reg.Author = "Softimage Corp.";
	in_reg.Name = "JScript Simple filter plug-in";

	// var the version number of this plugin
	in_reg.Major = 1;
	in_reg.Minor = 0 ;

	// register filter plugin item
	in_reg.RegisterFilter( "JScript Simple Filter", siFilter3DObject );

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
// JScriptSimpleFilter_Match: Returns true if the object is a polygon mesh with more 
// than 50 points.
//
// in_context: Filter context. The context contains this specific attribute:
//	Input: Object to filter.
//
// *note* This function is mandatory and must be implemented.
//--------------------------------------------------------------------------
function JScriptSimpleFilter_Match( in_context )
{
	var in_object = in_context.GetAttribute( "Input" );

	var obj = Get3DObject( in_object );
	if( ClassName(obj) != "X3DObject" )
	{
		return false;
	}

	return obj.ActivePrimitive.Geometry.Points.Count > 50;
}

function JScriptSimpleFilter_Init( in_ctxt )
{
	var filter = in_ctxt.Source;

	LogMessage( "Initializing JScript Simple filter: " + filter.Name );
}

function JScriptSimpleFilter_Term( in_ctxt )
{
	var filter = in_ctxt.Source;

	LogMessage( "Terminating JScript Simple filter: " + filter.Name );
}


//helper to get an X3DObject
function Get3DObject( in_object )
{
	var obj;
	var objClass = ClassName(in_object);
	if (objClass == "X3DObject")
	{
		obj = in_object;
	}
	else if ( objClass == "Primitive" )
	{
		obj = in_object.Parent;
	}

	return obj;
}


