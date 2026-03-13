//--------------------------------------------------------------------------
// ProjectSelectors.js: This plug-in demonstrates how to use the change 
// project event (siOnChangeProject) in JScript. The plug-in property page 
// lists 3 projects you can select through a radio button control. At this point
// the new selected project is activated and the siOnChangeProject event 
// callback activates a new layout according to the activated project.
//
// For more details see the plug-in help file.
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// XSILoadPlugin: Installs the project selector demo.
//--------------------------------------------------------------------------
function XSILoadPlugin( in_reg )
{
	// Register plugin information
	in_reg.Author = "Softimage Corp.";
	in_reg.Name = "Project Selector plug-in";

	in_reg.Major = 1;
	in_reg.Minor = 0;

	// The change project event	
	in_reg.RegisterEvent( "Change Project", siOnChangeProject );

	// Project selector UI
	in_reg.RegisterProperty( "ProjectSelectorProp" );
	in_reg.RegisterMenu( siMenuMainTopLevelID, "Project Selector", true, false );

	return true;
}

//--------------------------------------------------------------------------
// ChangeProject_OnEvent: Called whenever a change of project occurs
//--------------------------------------------------------------------------
function ChangeProject_OnEvent( ctxt )
{	
	// set the layout according to the new active project
	var newProjectPath = ctxt.GetAttribute("NewProjectPath");
	
	var laytout;
	var defaultProj = BuildPath( InstallationPath(siUserPath), "Default" );
	var animProj = BuildPath( InstallationPath(siUserPath), "Animation" );
	var compProj = BuildPath( InstallationPath(siUserPath), "Compositing" );
	
	if ( newProjectPath == defaultProj )
	{
		desktop.ActiveLayout = desktop.layouts("Default");
	}
	else if ( newProjectPath == animProj )
	{
		desktop.ActiveLayout = desktop.layouts("Dual");
	}
	else if ( newProjectPath == compProj )
	{
		desktop.ActiveLayout = desktop.layouts("Compositing");
	}
}

//--------------------------------------------------------------------------
// GetProjectSelectorProp: Returns the project selector custom property.
//--------------------------------------------------------------------------

function GetProjectSelectorProp( )
{
	var strName = "ProjectSelectorProp";
	var root = ActiveSceneRoot;
	var prop = root.Properties.Item( strName ) ;

	if ( prop == null )
	{
		return root.AddProperty( strName );
	}
	else
	{
		return prop ;
	}
}

//--------------------------------------------------------------------------
// ProjectSelector_Init: Installs the Project Selector menu.
//--------------------------------------------------------------------------

function ProjectSelector_Init( in_ctxt )
{
	var menu = in_ctxt.source;

	menu.AddCallbackItem( "Launch Project Selector", "ShowProjectSelectorProp" );

	return true;
}

function ShowProjectSelectorProp( )
{
	InspectObj( GetProjectSelectorProp( ), "", "", siLock );
}

//--------------------------------------------------------------------------
// ProjectSelectorProp_Define: Defines the Project Selector prop.
//--------------------------------------------------------------------------

function ProjectSelectorProp_Define( ctxt )
{
	var pset;
	pset = ctxt.Source;
	pset.AddParameter2( "RadioBtn",	siInt4,	1, 1, 3, null, null, 0,	siPersistable );
	
	return true;
}

//--------------------------------------------------------------------------
// ProjectSelectorProp_DefineLayout: Defines the Project Selector UI.
//--------------------------------------------------------------------------

function ProjectSelectorProp_DefineLayout( ctxt )
{
	var layout = ctxt.Source;
	layout.Clear();
	
	layout.AddGroup("Select a project");
	var item = layout.AddItem( "RadioBtn", "Projects", siControlRadio ) ;
	item.UIItems = Array(	"Default",		1, 
							"Animation",	2,
							"Compositing",	3  ) ; 
	layout.EndGroup();
	
	return true;
}

//--------------------------------------------------------------------------
// ProjectSelectorProp_RadioBtn_OnChanged: Activate the selected project.
//--------------------------------------------------------------------------

function ProjectSelectorProp_RadioBtn_OnChanged( )
{
	var projectSelected = PPG.RadioBtn.Value;

	var currproj = Application.ActiveProject;
	var projPath; 
	switch( projectSelected )
	{
		case 1:
		{
			// default project
			projPath = BuildPath( InstallationPath(siUserPath), "Default" );
		}
		break;

		case 2:
		{
			// animation project
			projPath = BuildPath( InstallationPath(siUserPath), "Animation" );
		}
		break;

		case 3:
		{
			// compositing project
			projPath = BuildPath( InstallationPath(siUserPath), "Compositing" );
		}
		break;
	};
	
	if ( currproj.FullName != projPath )
	{
		// create (if not done yet) and activate the project
		Application.CreateProject( projPath );
		Application.ActiveProject = projPath;
	}	
}

function BuildPath( )
{
	var strSlash = ( XSIUtils.IsWindowsOS() ) ? "\\" : "/";
	var	strPath = "";
	var nArgs = arguments.length;
	
	for( i = 0; i < nArgs; i++ )
	{
		strPath += arguments[ i ];
		
		if ( strPath.slice( -1 ) != strSlash && nArgs-1 != i)
		{
			strPath += strSlash;
		}
	}
	
	return( strPath );
}
