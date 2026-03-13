#--------------------------------------------------------------------------
# simplepycommand.py: This file shows how to implement and registered a simple
# command plugin in Python. 
#
# Note: Look at simplecommand.htm for more details about this sample.
#
#	Copyright 2008 Autodesk, Inc.  All rights reserved.  
#	Use of this software is subject to the terms of the Autodesk license agreement 
#	provided at the time of installation or download, or which otherwise accompanies 
#	this software in either electronic or hard copy form.   
#--------------------------------------------------------------------------
from win32com.client import constants

null = None
true = 1
false = 0

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
	in_reg.Name = "Python simple command plug-in";
	
	# We don't need to specify the Help property
	# because Softimage will automatically find the 
	# netview_SimpleCommand.htm file

	# var the version number of this plugin
	in_reg.Major = 1;
	in_reg.Minor = 0 ;

	# register command plugin item
	in_reg.RegisterCommand( "SimplePYCommand" );

	LogMessage( in_reg.Name + " has been loaded." );

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
# SimplePYCommand_Init: This callback is called when your custom command 
# is first requested by Softimage. This function is optional and is usually used to 
# define the custom command arguments.
# 
# in_context: Command context. The context contains the command to define.
# 
# --------------------------------------------------------------------------
def SimplePYCommand_Init( ctxt ):
	oCmd = ctxt.Source
	oCmd.ReturnValue = true
	oCmd.Arguments.Add( "arg0", constants.siArgumentInput, "Default value" )

	return true

#--------------------------------------------------------------------------
# SimplePYCommand_Execute: Callback implementing the simple command 
# plug-in
#
#--------------------------------------------------------------------------
def SimplePYCommand_Execute( in_arg0 ):

	Application.LogMessage( "Executing SimplePYCommand" );
	Application.LogMessage( "arg 0 value: " + in_arg0 );

	# For this example the return value will be TRUE.	
	return true;


# optional callback called when the SimplePYCommand is deleted
def SimplePYCommand_Term( in_ctxt ):
	oCmd = in_ctxt.Source

	msg = 'Terminating '
	msg += oCmd.Name
	Application.LogMessage( msg )
	
	return true
