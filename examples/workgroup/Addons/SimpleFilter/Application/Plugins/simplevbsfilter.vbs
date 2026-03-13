'--------------------------------------------------------------------------
' simplefilter.vbs: This file shows how to implement and registered a simple
' filter plugin in VBScript. The plugin is used for filtering polygon mesh 
' geometries that contain more than 50 points.
'
' Note: Look at simplefilter.htm for more details about this sample.
'	Copyright 2008 Autodesk, Inc.  All rights reserved.  
'	Use of this software is subject to the terms of the Autodesk license agreement 
'	provided at the time of installation or download, or which otherwise accompanies 
'	this software in either electronic or hard copy form.   

'--------------------------------------------------------------------------

'--------------------------------------------------------------------------
' XSILoadPlugin: Entry-point called by Softimage when this file gets loaded. All 
' plugin items exposed here must be registered in this function. 
'
' arg in_reg: PluginRegistrar object required for registering the plugin 
' items and some information about this plugin.
'
' *note* This function is mandatory and must be implemented. The plugin will 
' not be loaded if this function is missing.
'--------------------------------------------------------------------------
Function XSILoadPlugin( in_reg )
	' register plugin information
	in_reg.Author = "Softimage Corp." 
	in_reg.Name = "VBScript Simple filter plug-in"

	' set the version number of this plugin
	in_reg.Major = 1
	in_reg.Minor = 0 

	' register filter plugin item
	in_reg.RegisterFilter "VBScript Simple Filter", siFilter3DObject

	XSILoadPlugin = true
end Function

'--------------------------------------------------------------------------
' XSIUnloadPlugin: Entry-point called by Softimage when this file gets unloaded. 
' All plugin items registered by this plugin are automatically unregistered 
' by Softimage. Use this function to perform internal cleanup.
'
' arg in_reg: PluginRegistrar object.
'
' *note* This function is optional.
'--------------------------------------------------------------------------
Function XSIUnloadPlugin( in_reg )
	Logmessage in_reg.name & " has been unloaded."
	XSIUnloadPlugin = true
end Function

'--------------------------------------------------------------------------
' VBScriptSimpleFilter_Match: Returns true if the object is a polygon mesh with 
' more than 50 points.
'
' in_context: Filter context. The context contains this specific attribute:
'	Input: Object to filter.
'
' *note* This function is mandatory and must be implemented.
'--------------------------------------------------------------------------
Function VBScriptSimpleFilter_Match( in_context )
	VBScriptSimpleFilter_Match = false

	set in_object = in_context.GetAttribute( "Input" )

	set obj = Get3DObject( in_object )
	if not ClassName(obj) = "X3DObject" then
		exit Function
	end if

	VBScriptSimpleFilter_Match = obj.ActivePrimitive.Geometry.Points.Count > 50
end Function


Function VBScriptSimpleFilter_Init( in_ctxt )
	set f = in_ctxt.Source

	LogMessage "Initializing VBScript Simple filter: " & f.Name 

End Function

Function VBScriptSimpleFilter_Term( in_ctxt )
	set f = in_ctxt.Source

	LogMessage "Terminating VBScript Simple filter: " & f.Name 
End Function

Function VBScriptSimpleFilter_Unload( in_ctxt )
	set f = in_ctxt.Source

	LogMessage "Unload VBScript Simple filter: " & f.Name 

End Function

Function VBScriptSimpleFilter_Reload( in_ctxt )
	set f = in_ctxt.Source

	LogMessage "Reload VBScript Simple filter: " & f.Name 

End Function

'helper to get an X3DObject
Function Get3DObject( in_object )
	set Get3DObject = Nothing
	objClass = ClassName(in_object)
	if objClass = "X3DObject" then	
		set Get3DObject = in_object		
	elseif objClass = "Primitive" then
		set Get3DObject = in_object.Parent
	end if
end Function

