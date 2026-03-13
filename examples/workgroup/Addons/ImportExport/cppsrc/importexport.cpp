//*****************************************************************************
/*!	\file importexport.cpp
 	\brief Defines the entry point required for loading the DemoImportExport
 	plug-in.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
 
 */
//*****************************************************************************

#include <xsi_pluginregistrar.h>
#include <xsi_status.h>
#include <xsi_decl.h>

using namespace XSI; 

//*****************************************************************************
/*!	Register the commands, menus, and properties that implement this plug-in.
	\param in_reg The PluginRegistrar created by Softimage for this plug-in.
 */
//*****************************************************************************

XSIPLUGINCALLBACK CStatus XSILoadPlugin( PluginRegistrar& in_reg )
{
	in_reg.PutAuthor(L"Softimage Corp");
	in_reg.PutName(L"Import Export Demo Plug-in");
	in_reg.PutVersion(1,0);
	
	// Register commands for importing and exporting a polygon mesh
	in_reg.RegisterCommand(L"DemoExportMesh");
	in_reg.RegisterCommand(L"DemoImportPolygonMesh");
	in_reg.RegisterCommand(L"DemoImportTriangleMesh");

	// Install a top-level menu for the import/export tool
	in_reg.RegisterMenu(siMenuMainTopLevelID, L"Demo Tool", false,false);

	// Register a custom property to use as the import/export UI	
	in_reg.RegisterProperty(L"DemoImportExportProp");

	return CStatus::OK;
}

XSIPLUGINCALLBACK CStatus XSIUnloadPlugin( const PluginRegistrar& in_reg )
{
	return CStatus::OK;
}
