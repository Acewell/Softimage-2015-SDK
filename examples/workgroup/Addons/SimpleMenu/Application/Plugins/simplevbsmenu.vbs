'--------------------------------------------------------------------------
' simplemenu.vbs: This file shows how to implement and registered a simple
' menu plugin with VBScript. 
'
' Note: Look at simplemenu.htm for more details about this sample.
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
	in_reg.Name = "VBScript Simple menu plug-in"

	' set the version number of this plugin
	in_reg.Major = 1
	in_reg.Minor = 0 

	' register a menu plugin under Model|Get|Primitive|Polygon Mesh menu in 
	' the toolbar panel
	in_reg.RegisterMenu siMenuTbGetPrimitivePolygonMeshBasicID, "VBScript Simple Menu"

	' register a help menu for the simple menu
	bDynamic = false
	bDisplayAsSubmenu = false
	in_reg.RegisterMenu siMenuMainHelpID, "VBScript Simple Help Menu", bDisplayAsSubmenu, bDynamic

	Logmessage in_reg.name & " has been installed."

	XSILoadPlugin = true
end Function

'--------------------------------------------------------------------------
' VBScriptSimpleMenu_Init: Entry-point called by Softimage when the menu 
' "VBScript Simple Menu" is opened by the user. This callback is typically
' used for setting the menu properties such as name and filter, and for 
' defining the menu items.
'
' arg in_ctxt: A Context object holding the custom Menu object to define
'
'--------------------------------------------------------------------------
Function VBScriptSimpleMenu_Init( in_ctxt )
	set menu = in_ctxt.source

	menu.name = "&More VBScript..."

	menu.AddCommandItem "Another &Sphere", "Mesh Sphere"
	menu.AddCommandItem "Another &Torus", "Mesh Torus"
	menu.AddSeparatorItem
	menu.AddCallbackItem "Yet another &Cube", "OnCreateCube"

	Logmessage menu.name & " has been initialized."

	VBScriptSimpleMenu_Init = true	
End Function

'--------------------------------------------------------------------------
' OnCreateCube: Entry-point called by Softimage when the menu item is selected.
' This function creates a surface mesh cube.
'
' arg in_ctxt: A Context object holding the custom MenuItem object selected by
' the user.
'
'--------------------------------------------------------------------------
Function OnCreateCube( in_ctxt )	
	CreatePrim "Cube", "MeshSurface"
	OnCreateCube = true
End Function

'--------------------------------------------------------------------------
' VBScriptSimpleHelpMenu_Init: Entry-point called by Softimage when the menu 
' "Simple VBScript Help Menu" is opened by the user. This callback is typically
' used for setting the menu properties and for defining the menu items.
'
' arg in_ctxt: A Context object holding the custom Menu object to define
'
'--------------------------------------------------------------------------
Function VBScriptSimpleHelpMenu_Init( in_ctxt )
	set menu = in_ctxt.source

	menu.AddCallbackItem "VBScript Simple Menu Help", "OnSimpleHelpMenu"

	Logmessage menu.name & " has been initialized."

	VBScriptSimpleHelpMenu_Init = true
End Function

'--------------------------------------------------------------------------
' OnSimpleHelpMenu: Entry-point called by Softimage when the VBScript simple help 
' menu item is selected.The function shows the simple menu help page in netview.
'
' arg in_ctxt: A Context object holding the custom MenuItem object selected by
' the user.
'
'--------------------------------------------------------------------------
Function OnSimpleHelpMenu( in_ctxt )

	' get a netview window if one exists or create a new one
	set layout = Application.Desktop.ActiveLayout

	set netView = layout.Views( "netview" )
	if ClassName(netView) = "" then
		set netView = layout.CreateView( "netview", "netview" )
	end if
	
	' set the net view url with the simeple menu help file and show it
	set plugin = Application.Plugins("VBScript Simple menu plug-in")

	netView.Resize 600, 800 
	netView.SetAttributeValue "url", plugin.Help 
	netView.State = siNormal

	OnSimpleHelpMenu = true

End Function

' optional callbacks 
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
	Logmessage in_reg.name & " has been uninstalled."
	XSIUnloadPlugin = true
end Function

' optional callbacks on the VBScript simple menu
Function VBScriptSimpleHelpMenu_Term( in_ctxt )
	set menu = in_ctxt.source
	
	LogMessage menu.name & " has been terminated."

	VBScriptSimpleHelpMenu_Term = true
End Function

Function VBScriptSimpleHelpMenu_Unload( in_ctxt )
	set menu = in_ctxt.source
	
	LogMessage menu.name & " has been unloaded."

	VBScriptSimpleHelpMenu_Unload = true
End Function

Function VBScriptSimpleHelpMenu_Reload( in_ctxt )
	set menu = in_ctxt.source
	
	LogMessage menu.name & " has been reloaded."

	VBScriptSimpleHelpMenu_Reload = true
End Function
