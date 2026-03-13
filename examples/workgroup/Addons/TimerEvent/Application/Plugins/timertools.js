//--------------------------------------------------------------------------
// timertools.js: This file shows how to register and implement timer events
// in JScript. The plug-in contains the following demo features:
//
//	Auto Save Scene: Automatically saves the current scene every 15 seconds.
// 
//	Auto Script Editor Backup: Dumps the content of the script editor in a 
//	backup file.  Helps prevent loss of work if the computer crashes or 
//  code is accidentally erased.
//
//	Sub-component extruder: This sample combines an event timer with the key 
//	up and key down events to extrude any selected geometry sub-components. 
//	If you hit the F2 key, the selected sub-components is extruded and an event 
//	timer is started. While you keep the F2 key pressed, the timer callback 
//	kicks in and increases the length parameter of the extrusion operator by 1 
//	unit every 50 milliseconds. The timer stops as soon as you release the F2 
//	key.
//	
//  Auto Freeze Modeling: Freezes the selected object modeling operator every 20 secs.
//
//	Show Banner: Opens Netview with a banner file 5 seconds after 
//	the Show Banner timer has been enabled (unmuted). This demo uses a single 
//	timer (i.e. no interval time) which only fires once at delay time. A single 
//	timer disables itself after it executes for the first time.
//
//	For more details see the plug-in help file.
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// XSILoadPlugin: Installs all demo timers and the timer tools UI.
//--------------------------------------------------------------------------
function XSILoadPlugin( in_reg )
{
	// Register plugin information
	in_reg.Author = "Softimage Corp.";
	in_reg.Name = "Timer Tools plug-in";

	in_reg.Major = 1;
	in_reg.Minor = 0;
	
	// Register the save scene timer (disabled by default)
	// The timer elapses every 15 secs.
	in_reg.RegisterTimerEvent( "Auto Save Scene Timer", 15000 );
	var evTimer = Application.EventInfos( "Auto Save Scene Timer" );
	evTimer.Mute = true;

	// Register the save script timer (disabled by default)
	// The timer elapses every 10 secs.
	in_reg.RegisterTimerEvent( "Auto Script Backup Timer", 10000 );
	evTimer = Application.EventInfos( "Auto Script Backup Timer" );
	evTimer.Mute = true;

	// Register the show banner timer (disabled by default)
	// The timer elapses only once, 5 secs after being unmuted.
	in_reg.RegisterTimerEvent( "Show Banner Timer", 0, 5000 );
	evTimer = Application.EventInfos( "Show Banner Timer" );
	evTimer.Mute = true;

	// Register the extrusion timer (disabled by default)
	// The timer elapses every 50 millisecs.
	in_reg.RegisterTimerEvent( "Auto Extrusion Timer", 50 );
	evTimer = Application.EventInfos( "Auto Extrusion Timer" );
	evTimer.Mute = true;
	
	// Keyboard events used for extrusion processing
	in_reg.RegisterEvent( "Start Auto Extrusion", siOnKeyDown );	
	var kbEvent = Application.EventInfos( "Start Auto Extrusion" );
	kbEvent.Mute = true;
	
	in_reg.RegisterEvent( "Stop Auto Extrusion", siOnKeyUp );
	kbEvent = Application.EventInfos( "Stop Auto Extrusion" );
	kbEvent.Mute = true;

	// Register the auto freeze modeling timer (disabled by default)
	// The timer elapses every 20 secs.
	in_reg.RegisterTimerEvent( "Auto Freeze Modeling Timer", 20000 );
	evTimer = Application.EventInfos( "Auto Freeze Modeling Timer" );
	evTimer.Mute = true;

	// Timer tools UI
	in_reg.RegisterProperty( "TimerToolProp" );
	in_reg.RegisterMenu( siMenuMainTopLevelID, "Timer Tools", true, false );
	in_reg.RegisterCommand("ShowTimerTools","ShowTimerTools");

	return true;
}

//--------------------------------------------------------------------------
// AutoSaveSceneTimer_OnEvent: Timer callback which saves the current scene 
// automatically every 15 secs.
//--------------------------------------------------------------------------
function AutoSaveSceneTimer_OnEvent( ctxt )
{		
	// Save current scene
	Application.SaveScene( );
	
	// Log time
	var strFileName = ActiveProject.ActiveScene.Parameters("Filename").Value;

	if ( XSIUtils.IsWindowsOS() )
	{
		// toDateString is only available on windows
		var today = new Date();
		var strTime = today.toDateString();
		strTime += ", " + today.toTimeString();

		Application.LogMessage( "<"+strFileName+">" + " saved on " + strTime );
	}
	else
	{
		Application.LogMessage( "<"+strFileName+"> saved." );
	}
		
	// Do not mute the timer
	return false;
}

//--------------------------------------------------------------------------
// AutoScriptBackupTimer_OnEvent: Timer callback dumps the content of the 
// script editor to a file each time the event goes off.  
//
// Note: For the purpose of this example the script is fairly basic.
// However this code could be extended using existing SDK functionality into 
// a more sophisticated backup system, e.g.
// -Adding a menu option in the script editor context menu to recover the file
// -Only saving a file if the buffer has actually changed
// -Auto-cleanup of really old backup files
// -More configuration of location and file naming convention
//--------------------------------------------------------------------------
function AutoScriptBackupTimer_OnEvent( ctxt )
{
	// Scripts are commonly edited in either Text Editor view
	// (e.g. TDE) or Script Editor
	var oEditors = Desktop.ActiveLayout.Views.Filter( "Text Editor" ) ;	
	for ( i = 0 ; i < oEditors .count ; i++ )	
		BackupScriptViewContent( oEditors.Item(i) ) ;

	oEditors = Desktop.ActiveLayout.Views.Filter( "Script Editor" ) ;
	for ( i = 0 ; i < oEditors.count ; i++ )	
		BackupScriptViewContent( oEditors.Item(i) ) ;

	// Do not mute the timer
	return false;
}

// Helper function for AutoScriptBackupTimer
function BackupScriptViewContent( in_view )
{
	// Do nothing is view is not visible,
	// for example if TDE layout is active we only backup the active panel
	if ( !in_view.Visible )
		return ;

	text = in_view.GetAttributeValue("text");
	
	if ( text.length == 0 )
	{
		return ;
	}

	var fso = new ActiveXObject("Scripting.FileSystemObject");

	// Use the name of the file being edited as the basis for the 
	// backup filename.
	scriptfile = in_view.GetAttributeValue("filename");
	if ( scriptfile == "" )
	{
		// File has never been saved.
		
		scriptfile = "untitled" ;
		
		// Pick a name based on current script language
		strLang = GetValue( "preferences.scripting.language" )
	
		if ( strLang == "VBScript" || strLang == "VB Script Language" )
			scriptfile += ".vbs" ;
		else if ( strLang == "JScript" || strLang == "JScript Language" )
			scriptfile += ".js" ;			
		else if ( strLang == "Python" || strLang == "Python ActiveX Scripting Engine" )
			scriptfile += ".py" ;						
	}
	else
	{
		// remove the path
		var f = fso.GetFile(scriptfile);		
		scriptfile = f.Name ; 
	}

	// Get the backup file path
	strBackupPath = XSIUtils.BuildPath( Application.InstallationPath( siUserPath ), 
								"ScriptBackups" ) ;		
	XSIUtils.EnsureFolderExists( strBackupPath ) ;
			
	// Determine current time
	var today = new Date();

	// Use the time as part of the file name, to ensure that
	// older files don't get overwritten.  Eventually the backups could
	// take a lot of disk space but it is convenient to be able to retrieve
	// the script at any point in its history.
	var strTimePrefix = today.getFullYear() + "." 
					+ (1 + today.getMonth() ) + "." 
					+ today.getDate() + "." 
					+ today.getHours() + "." 
					+ today.getMinutes() + "." 
					+ today.getSeconds() + "." ;

	var strFilename = strBackupPath + XSIUtils.Slash + strTimePrefix + scriptfile ;
	
	if ( fso.FileExists( strFilename ) )
	{
		// It is an edge case, but a conflict could occur if there are multiple 
		// untitled files actively being edited. The code could detect that and
		// try to figure out a better unique name
		return ;
	}
	
	// Dump to backup file
	var file = fso.CreateTextFile( strFilename, true );
	file.WriteLine( text );
	file.Close();

	// Log the backup info
	if ( XSIUtils.IsWindowsOS() )
	{
		// toDateString is only available on windows
		var strTime = today.toDateString();
		strTime += ", " + today.toTimeString();
		Application.LogMessage( "Script editor saved to <"+strFilename+"> on " + strTime );
	}
	else
	{
		Application.LogMessage( "Script editor saved to <"+strFilename+">" );
	}
}

//--------------------------------------------------------------------------
// ShowBannerTimer_OnEvent: Pops-up Netview with a banner file. This 
// is done only once as the Show Banner timer is a single shot timer.
//--------------------------------------------------------------------------
function ShowBannerTimer_OnEvent( ctxt )
{
	// Ccreate a new Netview window
	var layout = Application.Desktop.ActiveLayout;
	var netView = layout.CreateView( "netview", "Timer Tools" );

	// Set the url with this banner file
	var strBanner = XSIUtils.BuildPath( 
					Application.Plugins("Timer tools plug-in").OriginPath,
					"banner.htm" ) ;	
	
	netView.Resize( 700, 200 );
	netView.SetAttributeValue( "url", strBanner );
	netView.State = siNormal		
	
	// do not mute the timer
	return false;
}

//--------------------------------------------------------------------------
// StopAutoExtrusion_OnEvent: Stops the auto extrusion operation when the F2 
// key is released.
//--------------------------------------------------------------------------
function StopAutoExtrusion_OnEvent( in_ctxt )
{
	var keyCode = in_ctxt.GetAttribute("KeyCode");

	switch( keyCode )
	{
		case 113: // F2 
		{			
			SetGlobal( "ExtrusionLengthParam", null );

			// Disable the extrusion timer
			var autoExtTimer = Application.EventInfos( "Auto Extrusion Timer" );
			autoExtTimer.Mute = true;
			
			// 	Tells Softimage the event have been consumed.
			in_ctxt.SetAttribute( "Consumed",true );			
		}
		break
	};

	// Do not abort
	return false;
}

//--------------------------------------------------------------------------
// AutoExtrusionTimer_OnEvent: Increases the newly added extrusion lentgh 
// parameter by 1 unit.
//--------------------------------------------------------------------------

function AutoExtrusionTimer_OnEvent( ctxt )
{
	var lenParam = GetGlobal( "ExtrusionLengthParam" );
	
	if ( lenParam != null )
	{
		var prop = GetTimerToolProp();
		var inc = prop.Parameters("Auto_Extrusion_Increment").Value;
		lenParam.value += inc;
	}
	return false;
}

//--------------------------------------------------------------------------
// StartAutoExtrusion_OnEvent: Applies an extrusion operator along axis to the
// selected geometry sub-component(s) if F2 is depressed. The auto extrusion
// timer is unmuted which allows the length parameter to increase while the
// F2 key is down.
//--------------------------------------------------------------------------

function StartAutoExtrusion_OnEvent( in_ctxt )
{
	var keyCode = in_ctxt.GetAttribute("KeyCode");

	switch( keyCode )
	{
		case 113: // F2 
		{
			SetGlobal( "ExtrusionLengthParam", null );
			
			// extrude current selection
			var ops = ApplyTopoOp(	"ExtrudeComponentAxis", 
									getvalue("SelectionList"), 
									siUnspecified, 
									siPersistentOperation, 
									null);
			
			// store the length parameter so it can be accessed by the 
			// extrusion timer
			var lenParam = ops(0).length;			
			SetGlobal( "ExtrusionLengthParam", lenParam );
			
			// enable the extrusion timer
			var autoExtTimer = Application.EventInfos( "Auto Extrusion Timer" );
			autoExtTimer.Mute = false;						

			// 	Tells Softimage the event have been consumed.
			in_ctxt.SetAttribute( "Consumed",true );			
		}
		break
	};
	
	return false;
}

//--------------------------------------------------------------------------
// AutoFreezeModelingTimer_OnEvent: Freeze the modeling operators of the 
// selected objects every 5 secs.
//--------------------------------------------------------------------------   
function AutoFreezeModelingTimer_OnEvent( ctxt )
{
	FreezeModeling( );
		
	// do not mute the timer
	return false;
}

//--------------------------------------------------------------------------
// GetTimerToolProp: Returns the timer tool custom property.
//--------------------------------------------------------------------------

function GetTimerToolProp( )
{
	var strName = "TimerToolProp";
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
// TimerTools_Init: Installs the Timer Tools menu.
//--------------------------------------------------------------------------

function TimerTools_Init( in_ctxt )
{
	var menu = in_ctxt.source;

	menu.AddCommandItem( "Launch Timer Tools", "ShowTimerTools" );

	return true;
}

function ShowTimerTools_Execute(  )
{
	InspectObj( GetTimerToolProp( ), "", "", siLock );
	return true ;
}


//--------------------------------------------------------------------------
// TimerToolProp_Define: Defines the Timer Tools prop.
//--------------------------------------------------------------------------

function TimerToolProp_Define( ctxt )
{
	var pset;
	pset = ctxt.Source;
	pset.AddParameter2("Auto_Save_Scene",siBool,false,null,null,null,null,0,siPersistable);
	pset.AddParameter2("Auto_Save_Scene_Interval",siInt4,15,0,50,null,null,0,siPersistable);
	pset.AddParameter2("Auto_Save_Scene_Delay",siInt4,0,0,50,null,null,0,siPersistable);
	
	pset.AddParameter2("Auto_Script_Editor_Backup",siBool,false,null,null,null,null,0,siPersistable);
	pset.AddParameter2("Auto_Script_Editor_Backup_Interval",siInt4,60,5,120,null,null,0,siPersistable);
	pset.AddParameter2("Auto_Script_Editor_Backup_Delay",siInt4,0,0,50,null,null,0,siPersistable);

	pset.AddParameter2("Show_Banner",siBool,false,null,null,null,null,0,siPersistable);
	pset.AddParameter2("Show_Banner_Interval",siInt4,0,0,50,null,null,0,siPersistable);
	pset.AddParameter2("Show_Banner_Delay",siInt4,5,0,50,null,null,0,siPersistable);

	// Show the backup directory, but because this Property is not persisted
	// this is read-only.  (This could be stored in a custom preference to give flexibility to
	// change it)

	strFullFilename = XSIUtils.BuildPath( Application.InstallationPath( siUserPath ), "ScriptBackups" ) ;
	
	pset.AddParameter2("Auto_Script_Editor_Backup_Dir",siString,strFullFilename,null,null,null,null,0,siPersistable|siReadOnly);

	pset.AddParameter2("Auto_Extrusion",siBool,false,null,null,null,null,0,siPersistable);
	pset.AddParameter2("Auto_Extrusion_Increment",siDouble,1,.01,5,null,null,0,siPersistable);
	
	pset.AddParameter2("Auto_Freeze_Modeling",siBool,false,null,null,null,null,0,siPersistable);
	pset.AddParameter2("Auto_Freeze_Modeling_Interval",siInt4,20,0,50,null,null,0,siPersistable);
	pset.AddParameter2("Auto_Freeze_Modeling_Delay",siInt4,0,0,50,null,null,0,siPersistable);
	
	return true;
}

//--------------------------------------------------------------------------
// TimerToolProp_DefineLayout: Defines the Timer Tools UI.
//--------------------------------------------------------------------------

function TimerToolProp_DefineLayout( ctxt )
{
	var layout,oItem;
	layout = ctxt.Source;
	layout.Clear();
	
	layout.AddGroup("Auto Save Scene");
	layout.AddItem("Auto_Save_Scene", "Enable" );
	layout.AddItem("Auto_Save_Scene_Interval", "Interval (secs)" );
	layout.AddItem("Auto_Save_Scene_Delay", "Delay (secs)" );
	layout.AddButton( "Auto_Save_Scene_Reset","Reset Timer" ) ;
	layout.EndGroup();
	
	layout.AddGroup("Script Editor Backup");
	layout.AddItem("Auto_Script_Editor_Backup", "Enable" );
	layout.AddItem("Auto_Script_Editor_Backup_Dir", "Backup Location");
	layout.AddItem("Auto_Script_Editor_Backup_Interval", "Interval (secs)" );
	layout.AddItem("Auto_Script_Editor_Backup_Delay", "Delay (secs)" );
	layout.AddButton( "Auto_Script_Editor_Backup_Reset","Reset Timer" ) ;	
	layout.EndGroup();
	
	layout.AddGroup("Auto Extrusion (F2)");	
	layout.AddItem("Auto_Extrusion", "Enable" );
	layout.AddItem("Auto_Extrusion_Increment", "Increments" );
	layout.EndGroup();
	
	layout.AddGroup("Auto Freeze Modeling");	
	layout.AddItem("Auto_Freeze_Modeling", "Enable" );
	layout.AddItem("Auto_Freeze_Modeling_Interval", "Interval (secs)" );
	layout.AddItem("Auto_Freeze_Modeling_Delay", "Delay (secs)" );
	layout.AddButton( "Auto_Freeze_Modeling_Reset","Reset Timer" ) ;	
	layout.EndGroup();

	layout.AddGroup("Show Banner");
	layout.AddItem("Show_Banner", "Enable" );
	layout.AddItem("Show_Banner_Interval", "Interval (secs)" );
	layout.AddItem("Show_Banner_Delay", "Delay (secs)" );
	layout.AddButton( "Show_Banner_Reset","Reset Timer" ) ;	
	layout.EndGroup();
	
	return true;
}

//--------------------------------------------------------------------------
// TimerToolProp_Auto_Save_Scene_OnChanged: Changes the mute state of the 
// Auto Save Scene timer.
//--------------------------------------------------------------------------

function TimerToolProp_Auto_Save_Scene_OnChanged( )
{
	var param;
	param = PPG.Auto_Save_Scene;
	var paramVal;
	paramVal = param.Value;
	
	var evTimer = Application.EventInfos( "Auto Save Scene Timer" );
	evTimer.Mute = paramVal==false;
}

//--------------------------------------------------------------------------
// Restart the Auto Save Scene timer with new values
//--------------------------------------------------------------------------
function TimerToolProp_Auto_Save_Scene_Reset_OnClicked()
{
	var p = PPG.Auto_Save_Scene_Interval;
	var interval = p.Value * 1000;

	p = PPG.Auto_Save_Scene_Delay;
	var delay = p.Value * 1000;
	
	var evTimer = Application.EventInfos( "Auto Save Scene Timer" );
	evTimer.Reset( interval, delay );

	// update the UI
	PPG.Auto_Save_Scene.Value = true;	
} 

//--------------------------------------------------------------------------
// TimerToolProp_Auto_Script_Editor_Backup_OnChanged: Changes the mute state 
// of the Auto Script Editor Backup timer.
//--------------------------------------------------------------------------
function TimerToolProp_Auto_Script_Editor_Backup_OnChanged( )
{
	var param;
	param = PPG.Auto_Script_Editor_Backup;
	var paramVal;
	paramVal = param.Value;

	var evTimer = Application.EventInfos( "Auto Script Backup Timer" );
	evTimer.Mute = paramVal==false;
}

//--------------------------------------------------------------------------
// Restart the Auto Script Editor backup timer with new values
//--------------------------------------------------------------------------

function TimerToolProp_Auto_Script_Editor_Backup_Reset_OnClicked()
{
	var p = PPG.Auto_Script_Editor_Backup_Interval;
	var interval = p.Value * 1000;

	p = PPG.Auto_Script_Editor_Backup_Delay;
	var delay = p.Value * 1000;
	
	var evTimer = Application.EventInfos( "Auto Script Backup Timer" );
	evTimer.Reset( interval, delay );

	// update the UI
	PPG.Auto_Script_Editor_Backup.Value = true;		
}

//--------------------------------------------------------------------------
// TimerToolProp_Show_Banner_OnChanged: Changes the mute state 
// of the Show Banner timer.
//--------------------------------------------------------------------------
function TimerToolProp_Show_Banner_OnChanged( )
{
	var param;
	param = PPG.Show_Banner;
	var paramVal;
	paramVal = param.Value;

	var evTimer = Application.EventInfos( "Show Banner Timer" );
	evTimer.Mute = paramVal==false;
}

//--------------------------------------------------------------------------
// Restart the Auto Script Editor backup timer with new values
//--------------------------------------------------------------------------
function TimerToolProp_Show_Banner_Reset_OnClicked()
{
	var p = PPG.Show_Banner_Interval;
	var interval = p.Value * 1000;

	p = PPG.Show_Banner_Delay;
	var delay = p.Value * 1000;
	
	var evTimer = Application.EventInfos( "Show Banner Timer" );
	evTimer.Reset( interval, delay );

	// update the UI
	PPG.Show_Banner.Value = true;		
}

//--------------------------------------------------------------------------
// TimerToolProp_Auto_Extrusion_OnChanged: Changes the mute state of the 
// Start/Stop Auto Extrusion keyboard events.
//--------------------------------------------------------------------------
function TimerToolProp_Auto_Extrusion_OnChanged( )
{
	var param;
	param = PPG.Auto_Extrusion;
	var paramVal;
	paramVal = param.Value;

	var kbEvent = Application.EventInfos( "Start Auto Extrusion" );
	kbEvent.Mute = paramVal==false;

	kbEvent = Application.EventInfos( "Stop Auto Extrusion" );
	kbEvent.Mute = paramVal==false;	
}

//--------------------------------------------------------------------------
// TimerToolProp_Auto_Freeze_Modeling_OnChanged: Changes the mute state of 
// the Auto Freeze Modeling timer.
//--------------------------------------------------------------------------
function TimerToolProp_Auto_Freeze_Modeling_OnChanged( )
{
	var param;
	param = PPG.Auto_Freeze_Modeling;
	var paramVal;
	paramVal = param.Value;

	var evTimer = Application.EventInfos( "Auto Freeze Modeling Timer" );
	evTimer.Mute = paramVal==false;
}

//--------------------------------------------------------------------------
// Restart the Auto Freeze Modeling timer with new values
//--------------------------------------------------------------------------

function TimerToolProp_Auto_Freeze_Modeling_Reset_OnClicked( )
{
	var p = PPG.Auto_Freeze_Modeling_Interval;
	var interval = p.Value * 1000;

	p = PPG.Auto_Freeze_Modeling_Delay;
	var delay = p.Value * 1000;
	
	var evTimer = Application.EventInfos( "Auto Freeze Modeling Timer" );
	evTimer.Reset( interval, delay );

	// update the UI
	PPG.Auto_Freeze_Modeling.Value = true;	
}






