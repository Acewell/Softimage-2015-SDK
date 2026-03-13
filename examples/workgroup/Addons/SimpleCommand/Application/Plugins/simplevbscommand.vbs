'--------------------------------------------------------------------------
' simplecommand.vbs: This file shows how to implement and registered a simple
' command plugin in VBScript. 
'
' Note: Look at simplecommand.htm for more details about this sample.
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
	in_reg.Name = "VBScript simple command plug-in"

	' set the version number of this plugin
	in_reg.Major = 1
	in_reg.Minor = 0 

	' register a regular command plugin item
	in_reg.RegisterCommand "SimpleVBSCommand"

	LogMessage in_reg.name & " has been loaded."

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
' SimpleVBSCommand_Init: This callback is called when your custom command 
' is first requested by Softimage. This function is optional and is usually used to 
' define the custom command arguments.
'
' in_context: Command context. The context contains the command to define.
'
'--------------------------------------------------------------------------
Function SimpleVBSCommand_Init( in_ctxt )
	set cmd = in_ctxt.Source

	LogMessage "Defining " & cmd.Name

	cmd.ReturnValue = true
	cmd.Arguments.Add "arg0", siArgumentInput, "Default value"

end Function

'--------------------------------------------------------------------------
' SimpleVBSCommand_Execute: Callback implementing the simple command 
' plug-in
'
'--------------------------------------------------------------------------
Function SimpleVBSCommand_Execute( in_arg0 )

	LogMessage "Executing VBScriptSimpleCommand"
	LogMessage "arg 0 value: " & in_arg0


	' For this example we return true.
	VBScriptSimpleCommand_Execute = true
end Function

'Optional
Function SimpleVBSCommand_Term( in_ctxt )
	set f = in_ctxt.Source

	LogMessage "Terminating: " & f.Name 
End Function

'Optional
Function SimpleVBSCommand_Unload( in_ctxt )
	set f = in_ctxt.Source

	LogMessage "Unloading: " & f.Name 

End Function

'Optional
Function SimpleVBSCommand_Reload( in_ctxt )
	set f = in_ctxt.Source

	LogMessage "Reloading: " & f.Name 

End Function

