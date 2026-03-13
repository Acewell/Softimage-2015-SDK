//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

function XSILoadPlugin( in_reg )
{
	// register plugin information
	in_reg.Author = "Softimage Corp.";
	in_reg.Name = "Softimage PPG Layout Demos";

	// var the version number of this plugin
	in_reg.Major = 1;
	in_reg.Minor = 1 ;

	// register commands implemented in this file
	in_reg.RegisterCommand( "PPGConfigSlider" );
	in_reg.RegisterCommand( "PPGFilePicker" );
	in_reg.RegisterCommand( "PPGFileView" );
	in_reg.RegisterCommand( "PPGBuildChain" );
	in_reg.RegisterCommand( "PPGFCurveBasic" );
	in_reg.RegisterCommand( "PPGFCurveUserData" );
	in_reg.RegisterCommand( "PPGGridTester" );
	in_reg.RegisterCommand( "PPGProxyParam" );
	in_reg.RegisterCommand( "PPGLists" );
	in_reg.RegisterCommand( "PPGInView" );	
	in_reg.RegisterCommand( "PPGTextEditor" );	

	return true;
}

// allows plugin to unload from factory (debug only)
function can_unload()
{
	return true;
}



//**************************************************************
//
// EXAMPLE from PPGLayout reference
//
//**************************************************************


function PPGConfigSlider_Execute()
{

	// 
	// A demonstration of the Number Control on a Custom Property Set.
	// The number control normally appears as a 
	// [Animation Divot] [Label] [Edit+Slider Control]
	// but this example demonstrates how this appearance can be controlled.
	// It also shows how to change the range of a parameter.
	// All these changes can be made dynamically.
	//

	newscene( null, false ) ;

	var oCustomProperty = ActiveSceneRoot.AddProperty( 
				"CustomProperty", false, "NumberControlTester" ) ;

	// Add a parameter of type double.  
	// It has the min/max values of -1000 to 1000,
	// default value of -1.0, and ui range -100 to 100
	var oGridParam = oCustomProperty.AddParameter2( "number", siDouble, 
			-1.0, -1000.0, 1000.0, -100.0, 100.0, siClassifUnknown, 
			siPersistable | siAnimatable ) ;

	// Add the Edit boxes and other controls that will
	// be used to get information from the user

	oCustomProperty.AddParameter3( "setLabel", siString, "NewLabel" ) ;
	oCustomProperty.AddParameter3( "setNoLabel", siBool, false,null,null,false) ;
	oCustomProperty.AddParameter3( "setValueOnly", siBool, false,null,null,false) ;
	oCustomProperty.AddParameter3( "setNoSlider", siBool, false,null,null,false) ;
	oCustomProperty.AddParameter3( "setDecimals", siInt4, 3,0,10,false) ;
	oCustomProperty.AddParameter3( "setLabelMinPixels", siInt4, 10,0,300,false) ;
	oCustomProperty.AddParameter3( "setLabelPercentage", siInt4, 30,0,100,false) ;

	oCustomProperty.AddParameter3( "setUIMin", siDouble, -100,-10000,10000,false) ;
	oCustomProperty.AddParameter3( "setUIMax", siDouble, 100,-10000,10000,false) ;
	oCustomProperty.AddParameter3( "setMin", siDouble, -1000,-10000,10000,false) ;
	oCustomProperty.AddParameter3( "setMax", siDouble, 1000,-10000,10000,false) ;

	//
	// Build the layout for the test property page
	// 

	var oLayout = oCustomProperty.PPGLayout

	oLayout.AddGroup( "Test Number Parameter" ) ;
		//The logic code will set all the detailed attributes
		oLayout.AddItem( "number" ) ;
	oLayout.EndGroup() ;

	oLayout.AddGroup( "Display Attributes" ) ;
		oLayout.AddItem( "setLabel","Label" ) ;
		oLayout.AddItem( "setNoLabel","NoLabel" ) ;
		oLayout.AddItem( "setNoSlider","NoSlider" ) ;
		oLayout.AddItem( "setDecimals","Decimals" ) ;

		oLayout.AddItem( "setLabelMinPixels","Label Pixels (Min)" ) ;
		oLayout.AddItem( "setLabelPercentage","Label %" ) ;

		oLayout.AddButton( "Update" ) ;
	oLayout.EndGroup() ;

	// These values actually fundamentally affect the
	// parameter itself.
	// Note:You could potentially change the script name
	// but that would break the logic code that depends
	// on the scripting name
	// Note:You can't change the type of a parameter.
	// Instead you could delete and recreate a new parameter
	// dynamically but that is not part of this example

	oLayout.AddGroup( "Parameter Attributes" ) ;
		oLayout.AddItem( "setMin" ) ;
		oLayout.AddItem( "setMax" ) ;

		oLayout.AddItem( "setUIMin" ) ;
		oLayout.AddItem( "setUIMax" ) ;

		oLayout.AddButton( "PDefUpdate","Update" ) ;
	oLayout.EndGroup() ;

	oLayout.Language = "Jscript" ;
	oLayout.Logic = NumberControlTester_Update_OnClicked.toString() + 
			NumberControlTester_PDefUpdate_OnClicked.toString();
	oLayout.SetAttribute( "LogicPrefix", "NumberControlTester_" ) ;


	InspectObj( oCustomProperty ) ;


	return true;
}

//
// This is the logic code
// 

function NumberControlTester_Update_OnClicked()
{
	var oCustomProperty = PSet.Inspected(0) ;
	var oLayout = oCustomProperty.PPGLayout

	var oPPGItem = oLayout.Item( "number" ) ;

	// Based on the property page items, set the attributes
	// of the control
	oPPGItem.Label = oCustomProperty.setLabel.Value ;
	oPPGItem.SetAttribute( "NoLabel", oCustomProperty.setNoLabel.Value ) ;
	oPPGItem.SetAttribute( "ValueOnly", oCustomProperty.setValueOnly.Value ) ;
	oPPGItem.SetAttribute( "NoSlider", oCustomProperty.setNoSlider.Value ) ;
	oPPGItem.SetAttribute( "Decimals", oCustomProperty.setDecimals.Value ) ;

	oPPGItem.LabelMinPixels = oCustomProperty.setLabelMinPixels.Value ;
	oPPGItem.LabelPercentage = oCustomProperty.setLabelPercentage.Value ;

	// (There is also a logithmic attribute 
	// but it only works for integer parameters)

	// You need to rebuild the PPG contents to see the changes
	PSet.Refresh() ;
}

function NumberControlTester_PDefUpdate_OnClicked()
{
	var oCustomProperty = PSet.Inspected(0) ;
	var oLayout = oCustomProperty.PPGLayout

	var newUIMin = oCustomProperty.setUIMin.Value ;
	var newUIMax = oCustomProperty.setUIMax.Value ;
	var newMin = oCustomProperty.setMin.Value ;
	var newMax = oCustomProperty.setMax.Value ;

	if ( newUIMin > newUIMax )
	{
		Logmessage( "UIMin must be less than UIMax!" ) ;
		return ;
	}

	if ( newMax < newUIMax )
	{
		Logmessage( "UIMax can't be bigger than Max!" ) ;
		return ;		
	}

	if ( newMin > newUIMin )
	{
		Logmessage( "UIMin can't be smaller than Min!" ) ;
		return ;		
	}

	// Call the command with the new parameter ranges
	EditParameterDefinition( oCustomProperty.number.FullName, null, null, 
				newMin, newMax, 
				newUIMin, newUIMax ) ;

	// You need to rebuild the PPG contents to see the changes
	PSet.Refresh() ;
}



//**************************************************************
//
// EXAMPLE from PPGItem reference
//
//**************************************************************

function PPGFilePicker_Execute()
{
	//Jscript example building a layout with two Controls for selecting a 
	//filepath and one for selecting a folder.
	var oPSet=ActiveSceneRoot.AddProperty("CustomProperty",false,"Demo") ;

	oPSet.AddParameter3( "ExportFile", siString ) ;
	oPSet.AddParameter3( "ImportFile", siString ) ;
	oPSet.AddParameter3( "FolderPicker", siString ) ;

	var oPPGLayout = oPSet.PPGLayout ;
	var oItem = oPPGLayout.AddItem( "ExportFile","Export Filename",siControlFilePath ) ;
	// You can use the string directly, or the typdef siUIInitialDir (see siPPGItemAttribute enum)
	oItem.SetAttribute( "initialdir", "project" ) ;
	oItem.SetAttribute( siUIFileFilter, "Text files (*.txt)|*.txt|All Files (*.*)|*.*||" ) ;

	var oItem = oPPGLayout.AddItem( "ImportFile","",siControlFilePath ) ;
	oItem.SetAttribute( siUIFileFilter, 
					"spdl files (*.spdl)|*.spdl|" +
					"xsiaddon files (*.xsiaddon)|*.xsiaddon|" +
					"All Files (*.*)|*.*||" );
	oItem.SetAttribute( siUIOpenFile, true ) ;
	oItem.SetAttribute( siUIInitialDir, "factory" ) ;
	oItem.SetAttribute( siUISubFolder, "Application/spdl" ) ;
	oItem.SetAttribute( siUIFileMustExist, true );

	var oItem = oPPGLayout.AddItem( "FolderPicker", "", "Folder" );
	oItem.SetAttribute( siUIInitialDir, "user" ) ;

	InspectObj( oPSet );


}


//**************************************************************
//
// EXAMPLE from PPG.PPGLayout reference
//
//**************************************************************

// JScript Custom Property example demonstrating how to
// build a simple Script viewer by using the
// siControlFolder, siControlCombo and multi-line string
// control.
//
// Note: This example could be extended: for example by adding a 
// "Save" and "New" button.

function PPGFileView_Execute()
{
	var oCustomProperty = ActiveSceneRoot.AddProperty( 
	                          "CustomProperty", false,
	                          "Script View" ) ;


	oCustomProperty.AddParameter3( "Dir", siString ) ;
	oCustomProperty.AddParameter3( "Scripts", siString ) ;
	oCustomProperty.AddParameter3( "File", siString ) ;

	var oLayout = oCustomProperty.PPGLayout

	oLayout.AddGroup( "Script Directory" ) ;

	var oItem = oLayout.AddItem( "Dir", "Directory", "Folder" ) ;	
	oItem.SetAttribute( "NoLabel", true ) ;	

	oLayout.EndGroup() ;

	oLayout.AddGroup( "Script File" ) ;

	var oItem = oLayout.AddEnumControl( "Scripts", Array(),
		             "", siControlCombo ) ;
	oItem.SetAttribute( "NoLabel", true ) ;	

	oLayout.EndGroup();

	oLayout.AddGroup( "File Contents" ) ;

	var oItem = oLayout.AddString( "File", "", true, 200 ) ;
	oItem.SetAttribute( "NoLabel", true ) ;	

	oLayout.EndGroup() ;

	oLayout.Language = "Jscript" ;
	oLayout.Logic = FileView_OnInit.toString() +
		             FileView_PopulateCombo.toString() +
		             FileView_Dir_OnChanged.toString() +
		             FileView_Scripts_OnChanged.toString();
	oLayout.SetAttribute( "LogicPrefix", "FileView_" ) ;
		             

	strDefaultDir = Application.InstallationPath( siUserPath ) + 
	                     "/Data/Scripts" ;
	oCustomProperty.Dir = strDefaultDir ;	

	InspectObj( oCustomProperty );
}

//
// The remaining code is event code which
// is injected into the PPG layout.
//

function FileView_OnInit()
{
	FileView_PopulateCombo() ;	
}

function FileView_Dir_OnChanged()
{
	FileView_PopulateCombo() ;
	PSet.File.Value = "" ;
}

function FileView_Scripts_OnChanged()
{
	strDir = PSet.Dir.Value 
	strScript = PSet.Scripts.Value 

	if ( strDir == "" || strScript == "" )
	{
		PSet.File.Value = "" ;
		return ;
	}

	try
	{
		var oFSO = new ActiveXObject( "Scripting.FileSystemObject" ) ;		
		var oFile = oFSO.OpenTextFile( strDir + "/" + strScript ) ;

		PSet.File.Value = oFile.ReadAll() ;
	}
	catch( e )
	{
		PSet.File.Value = "" ;
		logmessage ( "Error reading file " + 
		             strDir + "/" + strScript + 
		             "(" + e.Description + ")" ) ;
	}
}

function FileView_PopulateCombo()
{
	strDir = PSet.Dir.Value ;

	// If you close and reopen the PPG
	// and don't w	ant to lose this setting
	strOldValue = PSet.Scripts.Value ; 

	oCombo = PSet.Inspected(0).PPGLayout.Item( "Scripts" ) ;

	if ( strDir == "" )
	{
		//Flush any contents
		oCombo.UIItems = null ;
		PSet.Scripts.Value = "" ;
	}
	else
	{
		var oFSO = new ActiveXObject( "Scripting.FileSystemObject" ) ;		
		var oItems = new Array() ;

		try
		{
			bFoundOldValue = false ;

			var oFolder = oFSO.GetFolder( strDir ) ;

		   fc = new Enumerator(oFolder.files);
		   for (; !fc.atEnd(); fc.moveNext())
		   {
		   		var oFile = fc.item() ;

		   		if ( -1 != oFile.Name.indexOf( ".vbs" ) ||
			   		  -1 != oFile.Name.indexOf( ".js" ) ||
			   		  -1 != oFile.Name.indexOf( ".pys" ) ||
			   		  -1 != oFile.Name.indexOf( ".pls" ) )
			   	{			   		 		   		
			   		// Both label and value will be the string name
			   		oItems.push( oFile.Name ) ;
		   			oItems.push( oFile.Name ) ;

		   			if ( strOldValue == oFile.Name )
		   			{
		   				bFoundOldValue = true ;
		   			}
		   		}
		   }

			oCombo.UIItems = oItems ;

			if ( bFoundOldValue )
			{
				PSet.Scripts.Value = strOldValue ;
			}
			else
			{
				// We leave the value empty
				// so that the user actually 
				// picks a script file
				// before we load anything
				PSet.Scripts.Value = "" ;
			}
		}
		catch( e )
		{
			logmessage( "Error finding script files" +
		           " in specified directory: " + e.Description );
		}
	}	

	// Necessary to make sure the updated Combo is drawn
	PSet.Refresh() ;
}

//**************************************************************
//
// EXAMPLE from PPGLayout.Logic reference
//
//**************************************************************


// This script demonstrates how it is possible to create a 
// modal dialog box from scripting to ask a user a question.  
// It then generates a simple skeleton based on the number of
// bones and positions requested by the user.
//
// Key points of this example:
//
// -Advantage of Object Model API over SPDL files.  Because "for" loops can be
// used to dynamically add as many parameters are necessary it is easy to
// handle a variable number of options.  E.g. This example can be changed
// to support 10 bone skeletons instead of 5 bone skeletons by changing
// a single variable.
// 
// -Single script file takes care the entire plug-in
//
// -Logic code can be added to dynamically change the layout in response
// to the user's actions.  This replaced the need for "spdl logic".
//
// -JScript's ability to get the source code associated with a function
// using the toString() property.


g_maxbones = 5 ;

function PPGBuildChain_Execute()
{	
	var oPSet = BuildChain_CreatePSet() ;

	//We're going to take some of the routines in the script and 
	//inject the code into the PPG layout, using the convenient
	//toString() method of JScript
	//Alternatively we could have saved that code as a separate 
	//file

	var oLayout = oPSet.PPGLayout
	oLayout.SetAttribute( "LogicPrefix", "BuildChain_" ) ;
	
	oLayout.Logic = BuildChain_OnInit.toString() +
	                BuildChain_BoneNumber_OnChanged.toString() + 
	                BuildChain_CreateLayout.toString() + 
	                BuildChain_AddXYZRow.toString() ;

	oLayout.Language = "JScript" ;

	if ( !InspectObj( oPSet, null, null, siModal, false ) )
	{
		BuildChain_CreateBones( oPSet ) ;
	}

	// Erase the temporary pset
	DeleteObj( oPSet ) ;
}

function BuildChain_CreatePSet()
{
	var oPSet = ActiveSceneRoot.AddProperty( 
	                             "CustomProperty", 
	                             false, 
	                             "Create_Bones_SDK_Example" ) ;

	// Default number of bones is three
	oPSet.AddParameter3( "BoneNumber", siInt4, 3 ) ;

	oPSet.AddParameter3( "origin_x", siDouble, 0 ) ;
	oPSet.AddParameter3( "origin_y", siDouble, 0 ) ;
	oPSet.AddParameter3( "origin_z", siDouble, 0 ) ;

	// Start bone numbering at "1" instead of 0 for usability
	for ( i = 1 ; i <= g_maxbones ; i++ )
	{
		// We use a simple naming scheme.  
		// e.g. "b4_x" is the "x" axis of bone 4.	
		oPSet.AddParameter3( "b" + i.toString() + "_x", siDouble, i ) ;					
		oPSet.AddParameter3( "b" + i.toString() + "_y", siDouble, i ) ;
		oPSet.AddParameter3( "b" + i.toString() + "_z", siDouble, i ) ;	
	}

	// None of the parameters are animatable - we are only using them
	// temporarily for the UI

	for ( i = 0 ; i < oPSet.Parameters.Count ; i++ )
	{
		oPSet.Parameters(i).Animatable = false ;
	}


	return oPSet ;
}

// Do the work based on the values the user has entered in the 
// Custom Property
function BuildChain_CreateBones( oPSet )
{
	//There must always be at least 1 bone
	oChainRoot = ActiveSceneRoot.Add3DChain( Array( oPSet.origin_x.Value, 
	                                                oPSet.origin_y.Value, 
	                                                oPSet.origin_z.Value ),														
											Array( oPSet.b1_x.Value, 
												   oPSet.b1_y.Value, 
	                                                oPSet.b1_z.Value ) ) ;

	//Create a variable number of additional bones
	for ( i = 2 ; i <= oPSet.BoneNumber.Value ; i++ )
	{	
		strBoneName = "b" + i.toString() ;	
		oChainRoot.AddBone( Array( oPSet.Parameters( strBoneName + "_x" ).Value,
	                               oPSet.Parameters( strBoneName + "_y" ).Value,
	                               oPSet.Parameters( strBoneName + "_z" ).Value ) ) ;
	}
}


// Event logic section - this code gets injected as part of the layout
// Hence it can't rely on any global variables or other functions.

function BuildChain_OnInit()
{	
	// Create the initial layout, based on the
	// default number of bones

	BuildChain_BoneNumber_OnChanged()
}

function BuildChain_BoneNumber_OnChanged()
{
	// Redraw the UI, showing only controls
	// relevant to the number of Bones selected in the drop down
	BuildChain_CreateLayout(PSet.Inspected(0), PSet.BoneNumber.Value );	
	PSet.Refresh() ;
}

function BuildChain_CreateLayout( in_oPSet, in_cntBones )
{
	var oLayout = in_oPSet.PPGLayout ;

	oLayout.Clear() ; // Flush old layout

	var oItem = oLayout.AddEnumControl( 
	                    "BoneNumber", 
	                    Array( "One", 1, 
	                           "Two", 2, 
	                           "Three", 3, 
	                           "Four", 4, 
	                            "Five", 5 ),
	                    siControlCombo )
	oItem.Label = "Number of Bones" ;

	oLayout.AddGroup( "Bone Positions" );

		BuildChain_AddXYZRow( oLayout, "Origin", "origin_x", "origin_y", "origin_z" ) ;

		for ( i = 1 ; i <= in_cntBones ; i++ )
		{
			strOfI = i.toString() ;

			BuildChain_AddXYZRow( 
			    oLayout, 
			    "Bone " + strOfI, 
			    "b" + strOfI + "_x", 
			    "b" + strOfI + "_y", 
			    "b" + strOfI + "_z" ) ;
		}

	oLayout.EndGroup() ;

}

// Add a XYZ vector of parameters to the layout
function BuildChain_AddXYZRow( in_Layout, in_Label, in_xName, in_yName, in_zName )
{
	in_Layout.AddGroup( in_Label ) ;
		in_Layout.AddRow();								
			oItem = in_Layout.AddItem( in_xName ) ;
			oItem.SetAttribute( siUIValueOnly, true ) ;								
			oItem.SetAttribute( siUINoSlider, true ) ;

			oItem = in_Layout.AddItem( in_yName ) ;
			oItem.SetAttribute( siUIValueOnly, true ) ;					
			oItem.SetAttribute( siUINoSlider, true ) ;

			oItem = in_Layout.AddItem( in_zName ) ;
			oItem.SetAttribute( siUIValueOnly, true ) ;					
			oItem.SetAttribute( siUINoSlider, true ) ;				
		in_Layout.EndRow() ;		
	in_Layout.EndGroup() ;
}

//**************************************************************
//
// EXAMPLE from PPGLayout.AddFCurve reference
//
//**************************************************************

// Example showing how an FCurve can 
// be stored on a Custom Property
// and UI tools can be added via the PPGLayout
// object

function PPGFCurveBasic_Execute()
{	
	newscene( null, false ) ;

	var oCustomProperty = ActiveSceneRoot.AddProperty( 
			"CustomProperty", 
			false, 
			"DataTemplate" ) ;
	oCustomProperty.AddFCurveParameter( "Curve" ) ;

	// Create read-only parameters that will be updated by the logic
	oCustomProperty.AddParameter3( "KeyCount", siInt4,null,null,null,false,true ) ;
	oCustomProperty.AddParameter3( "MaxY", siInt4,null,null,null,false,true ) ;

	// Build the Layout
	var oLayout = oCustomProperty.PPGLayout		
	var oLayoutItem = oLayout.AddFCurve( "Curve", 150 );

	oLayout.AddGroup( "Info" ) ;	
	oLayout.AddRow() ;
	oLayout.AddItem( "KeyCount" ) ;
	oLayout.AddItem( "MaxY" ) ;	
	oLayout.EndRow() ;
	oLayout.EndGroup() ;

	oLayout.AddRow() ;
	oLayout.AddButton( "Randomize" ) ;
	oLayout.AddButton( "Reframe" ) ;
	oLayout.EndRow() ;

	oLayout.Language = "JScript" ;
	oLayout.SetAttribute( "LogicPrefix", "FCurveBasic_" ) ;
	oLayout.Logic = FCurveBasic_OnInit.toString() +
		FCurveBasic_Randomize_OnClicked.toString() +
		FCurveBasic_Reframe_OnClicked.toString() +
		FCurveBasic_ReCalcInfo.toString() +
		FCurveBasic_Curve_OnChanged.toString() ;

	InspectObj( oCustomProperty ) ;
}

//
// The following code is Logic code for the Property Page
//

function FCurveBasic_Randomize_OnClicked()
{
	// Get access to the curve
	var oFCurve = PSet.Curve.Value;

	oFCurve.BeginEdit();

	oFCurve.RemoveKeys();

	var maxKeys = 10.0 ;
	var maxX = 100.0 ;
	var maxY = 100.0 ;

	var keys = Math.round( maxKeys * Math.random() ) ;

	for ( var i = 0 ; i < keys ; i++ )
	{
		var keyFrame = Math.round( maxX * Math.random() )
		oFCurve.AddKey( keyFrame,
							maxY * Math.random() ) ;
	}

	// Always end back at zero
	oFCurve.AddKey( 0, 0 ) ;
	oFCurve.AddKey( maxX, 0 ) ;

	oFCurve.EndEdit() ;	

	FCurveBasic_ReCalcInfo() ;
}

function FCurveBasic_Reframe_OnClicked()
{
	//Redraw, which will reframe the new pset
	PSet.Refresh() ;
}

function FCurveBasic_ReCalcInfo()
{
	// Show the number of keys and maximum
	// Y value for the curves

	var oFCurve = PSet.Curve.Value;
	PSet.KeyCount.Value = oFCurve.Keys.Count

	var maxYFound = 0 ;
	for ( var i = 0 ; i < oFCurve.Keys.Count ; i++ )
	{
		var y = oFCurve.GetKeyValue(i) ;	
		if ( y > maxYFound ) 
		{
			maxYFound = y ;
		}
	}

	PSet.MaxY.Value = maxYFound ;
}

function FCurveBasic_Curve_OnChanged()
{
	// Called when every the user changes the FCurve from the user interface.
	FCurveBasic_ReCalcInfo();
}

function FCurveBasic_OnInit()
{
	// Called when PPG is first draw, use the opportunity to calculate the initial
	// FCurve values
	FCurveBasic_ReCalcInfo() ;
}
 
//**************************************************************
//
// EXAMPLE from CustomProperty.BinaryData reference
//
//**************************************************************

// Example showing how FCurves 
// can be stored inside a UserDataMap,
// and edited via a Custom Property

// It demonstrates:
// -Creation of a single script plugin 
// -Use of templated UserDataMap object to store data on points
// -Use of CustomProperty.BinaryData to store and retrieve FCurves 
//		represented as strings.
// -Use of PPGLayout to build dynamic user interfaces (with no SPDL)


function PPGFCurveUserData_Execute()
{	
	newscene( null, false ) ;

	var oGrid = ActiveSceneRoot.AddGeometry( 
						"Grid", 
						"MeshSurface", 
						"GridWithUserData" ) ;

	oGrid.subdivu = 1 ;
	oGrid.subdivv = 1 ;

	var oCluster = oGrid.ActivePrimitive.Geometry.AddCluster( "pnt" ) ;
	var oUserDataMap = oCluster.AddProperty( "UserDataMap", 
					false, 
					"FCurveData" ) ;

	var oCustomProperty = PPGFCurveUserData_CreateUserDataTemplate( oCluster )	 ;
	oUserDataMap.Template = oCustomProperty ;

	InspectObj( oCustomProperty ) ;

	SelectObj(oGrid, null, true);
	SetSelFilter("Point");
}

function PPGFCurveUserData_CreateUserDataTemplate( in_oCluster )
{
	var oCustomProperty = in_oCluster.AddProperty( 
			"CustomProperty", 
			false, 
			"DataTemplate" ) ;
	oCustomProperty.AddFCurveParameter( "CurveData" ) ;

	var oLayout = oCustomProperty.PPGLayout	

	var oLayoutItem = oLayout.AddFCurve( "CurveData", 150 );

	oLayout.AddRow() ;
	oLayout.AddButton( "ReadFromSelection", "Read from selected Point" ) ;
	oLayout.AddButton( "SaveFromSelection", "Save on selected Point(s)" ) ;
	oLayout.AddButton( "Instructions" ) ;
	oLayout.EndRow() ;

	oLayout.Language = "JScript" ;
	oLayout.SetAttribute( "LogicPrefix", "PPGFCurveUserData_" ) ;	
	oLayout.Logic = PPGFCurveUserData_ReadFromSelection_OnClicked.toString() + 
			PPGFCurveUserData_SaveFromSelection_OnClicked.toString() +
			PPGFCurveUserData_Instructions_OnClicked.toString() +
			PPGFCurveUserData_GetSelectedPoints.toString() + 
			PPGFCurveUserData_GetUserDataMap.toString() ;

	return oCustomProperty ;
}

//
// The following code is Logic code for the Property Page
//

function PPGFCurveUserData_GetSelectedPoints()
{
	// Find out what points are selected
	// They are returned as an array of Cluster Indices
	// (-1 is returned in the array if the selected point is not
	// part of the cluster)

	var oSubComp = null ;

	for ( var i = 0 ; i < Selection.Count ; i++ )
	{
		var oObj = Selection(i) ;	
		if ( oObj.Type == "pntSubComponent" )
		{
			oSubComp = oObj.SubComponent
			break ;
		}
	}

	if ( oSubComp == null )
	{
		logmessage( "Please select the point to read from" ) ;
		return null ;
	}

	// (We could also double check that the points are selected on the
	// right object using the parent property!)

	var aVBSelectedElements = new VBArray( oSubComp.ElementArray ) ;
	var aGeometryIndices = aVBSelectedElements.toArray() ;

	// Index on a cluster is not necessarily identical to a 
	// geometry index.  Use the Cluster object to do a lookup	

	var oThisCustomProperty = PSet.Inspected.Item(0);
	var oCluster = oThisCustomProperty.Parent
			.ActivePrimitive.Geometry.Clusters("Point") ;		

	for ( i = 0 ; i < aGeometryIndices.length ; i++ )
	{
		aGeometryIndices[i] = oCluster.FindIndex( aGeometryIndices[i] ) ;
	}

	return aGeometryIndices ;	
}

function PPGFCurveUserData_GetUserDataMap()
{
	// Find the UserDataMap associated with this Custom Property
	// We know they are both nested under the same Cluster
	// and what the name of the User Data Map is
	var oThisCustomProperty = PSet.Inspected.Item(0);
	var oCluster = oThisCustomProperty.Parent
			.ActivePrimitive.Geometry.Clusters("Point") ;		
	return oCluster.Properties.Item( "FCurveData" ) ;
}

function PPGFCurveUserData_ReadFromSelection_OnClicked()
{
	var aSelectedElements = PPGFCurveUserData_GetSelectedPoints() ;
	if ( aSelectedElements == null || 
		 aSelectedElements.length == 0 )
	{
		return ;
	}

	// If more than one item is selected 
	// we only look at the first one
	var clusterIndex  = aSelectedElements[0] ;	

	if ( clusterIndex == -1 ) 
	{
		logmessage( "The selected index is not part of the cluster" ) ;
		return ;
	}


	var oUserDataMap = PPGFCurveUserData_GetUserDataMap() ;

	if ( oUserDataMap.IsEmpty( clusterIndex ) )
	{
		logmessage( "There is not user data stored on this item yet" ) ;
		return ; 
	}

	// Transfer the data from the UserDataMap
	// to the ClusterProperty

	var oThisCustomProperty = PSet.Inspected.Item(0);
	oThisCustomProperty.BinaryData = oUserDataMap.ItemValue( clusterIndex ) ;
}

function PPGFCurveUserData_SaveFromSelection_OnClicked()
{
	var aSelectedElements = PPGFCurveUserData_GetSelectedPoints() ;

	var oThisCustomProperty = PSet.Inspected.Item(0);	
	binarySnapShotOfCustomProperty = oThisCustomProperty.BinaryData ;

	var oUserDataMap = PPGFCurveUserData_GetUserDataMap() ;

	for ( i = 0 ; i < aSelectedElements.length ; i++ )
	{
		if ( aSelectedElements[i] != -1 )
		{
			oUserDataMap.ItemValue( aSelectedElements[i] ) = 
						binarySnapShotOfCustomProperty ;
		}
	}			
}

function PPGFCurveUserData_Instructions_OnClicked()
{
	// There are lots of different ways to show information
	// to a user, for example poping up netview, 
	// 	showing a message box, or putting static text right
	// on the dialog.

	// For demonstration purposes we create a temporary custom pset 
	// with a multiline edit box, which we fill with text. 
	// This doesn't have ideal usability but 
	// shows some of the potential for doing totally dynamic UI

	var oInfoPSet = ActiveSceneRoot.AddProperty( "CustomProperty", false, "Info" ) ;
	var oParameter = oInfoPSet.AddParameter3( "Info", siString ) ;
	oParameter.ReadOnly = true ;

	oParameter.Value = "Plug-in Instructions\r\n\r\n" +						
	  "This example demonstrates how to store FCurves as User Data.\r\n" +
	  "Each of the 4 vertices of the Grid can store a different Curve\r\n\r\n" +
	  "To view the FCurve on a vertex, select it and press the \r\n" +
	  "'Read from Selected Point' button.\r\n\r\n" +
	  "To set the fcurve, change the fcurve in the view, " +
	  "select one or more points\r\n" +
	  "and then press the 'Save on selected Point(s)' button"  	  

	var oLayoutItem = oInfoPSet.PPGLayout.AddString( "Info", "", true, 300 ) ;
	oLayoutItem.SetAttribute( "ValueOnly", true ) ;

	InspectObj( oInfoPSet,null,null,siModal, false ) ;
	DeleteObj( oInfoPSet );

}




//**************************************************************
//
// EXAMPLE from GridData reference
//
//**************************************************************


function PPGGridTester_Execute()
{
	// 
	// A demonstration of the Grid Control on a Custom Property Set.
	// Controls on the Property Page demonstrate the OM API that 
	// can be used to change the values and even size of the Grid Control
	// based on Property Page Logic code.
	//
	var oPSet = ActiveSceneRoot.AddProperty( "CustomProperty", false, "GridTester" ) ;
	var oGridParam = oPSet.AddGridParameter( "TestGrid" ) ;

	// Set up some initial size
	oGridParam.Value.RowCount = 3 ;
	oGridParam.Value.ColumnCount = 2 ;

	// Add the Edit boxes and other controls that will
	// be used to get information from the user
	oPSet.AddParameter3( "DimRows", siInt2, 3,null,null,false ) ;
	oPSet.AddParameter3( "DimCols", siInt2, 2,null,null,false ) ;

	oPSet.AddParameter3( "CellRow", siInt2, 0,null,null,false ) ;
	oPSet.AddParameter3( "CellCol", siInt2, 0,null,null,false ) ;
	oPSet.AddParameter3( "CellValue", siString, "New Value" ) ;

	oPSet.AddParameter3( "RowToChange", siInt2, 0,null,null,false ) ;
	oPSet.AddParameter3( "RowValue", siString, "New Value" ) ;

	oPSet.AddParameter3( "ColToChange", siInt2, 0,null,null,false ) ;
	oPSet.AddParameter3( "ColValue", siString, "New Value" ) ;

	oPSet.AddParameter3( "RowLabelToChange", siInt2, 0,null,null,false ) ;
	oPSet.AddParameter3( "RowLabel", siString, "New Row Label" ) ;

	oPSet.AddParameter3( "ColLabelToChange", siInt2, 0,null,null,false ) ;
	oPSet.AddParameter3( "ColLabel", siString, "New Column Label" ) ;

	oPSet.AddParameter3( "Batch", siBool,false,null,null,false ) ;

	oPSet.AddParameter3( "ColHeaderMode", siInt2) ;
	oPSet.AddParameter3( "RowHeaderMode", siInt2) ;

	oPSet.AddParameter3( "Width", siInt4 ) ;
	oPSet.AddParameter3( "Height", siInt4 ) ;
	oPSet.AddParameter3( "ColWidths", siString, "45;30;50" ) ;

	// Organize the controls on the PPG
	var oLayout = oPSet.PPGLayout
	var oPPGItem = oLayout.AddItem( "TestGrid", "",siControlGrid ) ;
	oPPGItem.SetAttribute( "NoLabel", true  ) ;

	oLayout.AddGroup( "Change Contents Via OM" ) ;

		oLayout.AddGroup( "Dimensions" ) ;
		oLayout.AddRow() ;
			AddNonSliderItem( oLayout, "DimRows", "Rows" ) ;
			AddNonSliderItem( oLayout, "DimCols", "Columns" ) ;
			oLayout.AddButton( "DimUpdate", "Update" ) ;
		oLayout.EndRow() ;
		oLayout.EndGroup();

		oLayout.AddGroup( "Cell value" ) ;
		oLayout.AddRow() ;
			AddNonSliderItem( oLayout, "CellRow", "Row" ) ;
			AddNonSliderItem( oLayout, "CellCol", "Column" ) ;
			oLayout.AddItem( "CellValue", "Value" ) ;
			oLayout.AddButton( "CellValueUpdate", "Update" ) ;
		oLayout.EndRow() ;
		oLayout.EndGroup();

		oLayout.AddGroup( "Row Values" ) ;
		oLayout.AddRow() ;
			AddNonSliderItem( oLayout, "RowToChange", "Row" ) ;
			oLayout.AddItem( "RowValue", "Value" ) ;
			oLayout.AddButton( "RowUpdate", "Update" ) ;
		oLayout.EndRow() ;
		oLayout.EndGroup();

		oLayout.AddGroup( "Column Values" ) ;
		oLayout.AddRow() ;
			AddNonSliderItem( oLayout, "ColToChange", "Column" ) ;
			oLayout.AddItem( "ColValue", "Value" ) ;
			oLayout.AddButton( "ColUpdate", "Update" ) ;
		oLayout.EndRow() ;
		oLayout.EndGroup();

		oLayout.AddGroup( "Row Label" ) ;
		oLayout.AddRow() ;
			AddNonSliderItem( oLayout, "RowLabelToChange", "Row" ) ;
			oLayout.AddItem( "RowLabel", "Label" ) ;
			oLayout.AddButton( "RowLabelUpdate", "Update" ) ;
		oLayout.EndRow() ;
		oLayout.EndGroup();

		oLayout.AddGroup( "Column Label" ) ;
		oLayout.AddRow() ;
			AddNonSliderItem( oLayout, "ColLabelToChange", "Column" ) ;
			oLayout.AddItem( "ColLabel", "Label" ) ;
			oLayout.AddButton( "ColLabelUpdate", "Update" ) ;
		oLayout.EndRow() ;
		oLayout.EndGroup();

		AddPushButton( oLayout, "Batch", "Batch Edit" ) ;

	oLayout.EndGroup();

	oLayout.AddGroup( "Change Layout" ) ;
		oLayout.AddRow() ;
			var headerModes = new Array( "Normal", 0, "None", 1, "Locked", 2) ;					
			oLayout.AddEnumControl( "ColHeaderMode", headerModes ) ;
			oLayout.AddEnumControl( "RowHeaderMode", headerModes ) ;
		oLayout.EndRow();			

		AddNonSliderItem( oLayout, "Height" ) ;
		AddNonSliderItem( oLayout, "Width" ) ;

		oLayout.AddItem( "ColWidths" ) ;

		oLayout.AddButton( "Refresh", "Full Refresh" ) ;
	oLayout.EndGroup();

	// Inject the event code
	oLayout.Language = "JScript" ;	
	oLayout.SetAttribute( "LogicPrefix", "GridTester_" )
	oLayout.Logic = GridTester_OnInit.toString() +	
			GridTester_TestGrid_OnChanged.toString() +	
			GridTester_DimUpdate_OnClicked.toString() +
			GridTester_CellValueUpdate_OnClicked.toString() +
			GridTester_RowUpdate_OnClicked.toString() +
			GridTester_ColUpdate_OnClicked.toString() +
			GridTester_RowLabelUpdate_OnClicked.toString() +
			GridTester_ColLabelUpdate_OnClicked.toString() +
			GridTester_Height_OnChanged.toString() +
			GridTester_Width_OnChanged.toString() +
			GridTester_Batch_OnChanged.toString() +
			GridTester_ColHeaderMode_OnChanged.toString() +
			GridTester_RowHeaderMode_OnChanged.toString() +
			GridTester_Refresh_OnClicked.toString() + 
			GridTester_ColWidths_OnChanged.toString();

	InspectObj( oPSet ) ;
}

//Helper function to create a button rather than a check box
//for showing a boolean parameter
function AddPushButton( in_oLayout, in_ParamName, in_Label )
{
	var oPPGItem = in_oLayout.AddItem( in_ParamName, "", "dscontrol" ) ;
	oPPGItem.SetAttribute( "Caption", in_ParamName );
	oPPGItem.SetAttribute( "Class", "Button" );
	oPPGItem.SetAttribute( "CX", 200 );		
	oPPGItem.SetAttribute( "Style", 0x00001003 );//(BS_AUTOCHECKBOX|BS_PUSHLIKE)
	oPPGItem.SetAttribute( "NoLabel", true ) ;
}

// By default numeric params have a slider, but
// if we hide the slider the control takes up less horizontal space
function AddNonSliderItem( in_oLayout, in_strParamName, in_strLabel )
{
	var oPPGItem = in_oLayout.AddItem( in_strParamName, in_strLabel ) ;
	oPPGItem.SetAttribute( siUINoSlider, true ) ;
}


//Logic Code for GridTester

function GridTester_OnInit()
{
//Force the logic code to run for setting the Column Widths to the 
//default values
	GridTester_ColWidths_OnChanged()
}

function GridTester_TestGrid_OnChanged()
{
	// This is never called if the change to the grid
	// if provoked by changes to the grid caused
	// by the logic code itself.  It is only called
	// if the cell contents are changed manually or by
	// an external script that uses the Object Model.

	logmessage( "Callback called for contents of TestGrid changing" ) ;

	var oGridData = PSet.TestGrid.value ;

	//Update the dimensions items based on the current size
	PSet.DimRows.Value = oGridData.RowCount ;
	PSet.DimCols.Value = oGridData.ColumnCount ;
}

function GridTester_DimUpdate_OnClicked()
{
	var oGridData = PSet.TestGrid.value ;

	//Bracket with BeginEdit/EndEdit 
	//so we only do a single update
	oGridData.BeginEdit() ;
	oGridData.RowCount = DimRows ;
	oGridData.ColumnCount = DimCols ;
	oGridData.EndEdit() ;

	Logmessage( "Calling GridData.RowCount = " + DimRows ) ;
	Logmessage( "Calling GridData.ColumnCount = " + DimCols ) ;

	// Notice that no call to PSet.Refresh is necessary
}

function GridTester_CellValueUpdate_OnClicked()
{
	var oGridData = PSet.TestGrid.value ;

	oGridData.SetCell( 
				PSet.CellCol.Value, 
				PSet.CellRow.Value, 
				PSet.CellValue.Value ) ;

	Logmessage( "Calling GridData.SetCell" ) ;
}

function GridTester_RowUpdate_OnClicked()
{
	var oGridData = PSet.TestGrid.value ;

	//All items in the row will have the same value
	var newValue = PSet.RowValue.Value ;
	var aRowValues = new Array( oGridData.ColumnCount ) ;

	for ( var i = 0 ; i < aRowValues.length ; i++ )
	{
		aRowValues[i] = newValue ;
	}

	oGridData.SetRowValues( PSet.RowToChange.Value, aRowValues ) ;

	Logmessage( "Calling GridData.SetRowValues" ) ;
}

function GridTester_ColUpdate_OnClicked()
{
	var oGridData = PSet.TestGrid.value

	var newValue = PSet.ColValue.Value ;
	var aColValues = new Array( oGridData.RowCount ) ;

	for ( var i = 0 ; i < aColValues.length ; i++ )
	{
		aColValues[i] = newValue ;
	}

	oGridData.SetColumnValues( PSet.ColToChange.Value, aColValues ) ;

	Logmessage( "Calling GridData.SetColumnValues" ) ;
}

function GridTester_RowLabelUpdate_OnClicked()
{
	var oGridData = PSet.TestGrid.value ;	
	oGridData.SetRowLabel( PSet.RowLabelToChange.Value, PSet.RowLabel ) ;

	Logmessage( "Calling GridData.SetRowLabel" ) ;
}

function GridTester_ColLabelUpdate_OnClicked()
{
	var oGridData = PSet.TestGrid.value ;
	oGridData.SetColumnLabel( PSet.ColLabelToChange.Value, PSet.ColLabel ) ;

	Logmessage( "Calling GridData.SetColumnLabel" ) ;
}

function GridTester_Batch_OnChanged()
{
	var oGridData = PSet.TestGrid.value ;

	// Demonstrate the ability to do multiple
	// updates without forcing a refresh

	if ( PSet.Batch.Value == 0 )
	{
		logmessage( "Calling GridData.EndEdit" ) ;
		oGridData.EndEdit() ;
	}
	else
	{
		// Button pushed in
		logmessage( "Calling GridData.BeginEdit" ) ;
		oGridData.BeginEdit() ;
	}
}

function GridTester_Refresh_OnClicked()
{
	// Does a complete refresh of the Property Page
	// Normal updates to the Grid should not require this
	PSet.Refresh() ;

	Logmessage( "Calling PSet.Refresh" ) ;
}

function GridTester_Height_OnChanged()
{
	var oLayout = PSet.Inspected(0).PPGLayout
	var oPPGItem = oLayout.Item( "TestGrid" )

	if ( PSet.Height.Value != 0 ) 
	{
		oPPGItem.SetAttribute( "CY", PSet.Height.Value ) ;
	}
	else
	{
		// When no attribute is set control will resize to fit the data
		oPPGItem.SetAttribute( "CY", null ) ;
	}

	// Attribute changes don't appear until there is a complete refresh
	PSet.Refresh() ;
}

function GridTester_Width_OnChanged()
{
	var oLayout = PSet.Inspected(0).PPGLayout
	var oPPGItem = oLayout.Item( "TestGrid" )

	if ( PSet.Width.Value != 0 ) 
	{
		oPPGItem.SetAttribute( "CX", PSet.Width.Value ) ;
	}
	else
	{
		oPPGItem.SetAttribute( "CX", null ) ;
	}

	PSet.Refresh() ;
}

function GridTester_ColWidths_OnChanged()
{
	var oLayout = PSet.Inspected(0).PPGLayout
	var oPPGItem = oLayout.Item( "TestGrid" )

	if ( PSet.ColWidths.Value != "" )
	{
		oPPGItem.SetAttribute( "ColumnWidths", PSet.ColWidths.Value ) ;
	}
	else
	{
		oPPGItem.SetAttribute( "ColumnWidths", null ) ;
	}

	PSet.Refresh() ;	
}

function GridTester_ColHeaderMode_OnChanged()
{
	var oLayout = PSet.Inspected(0).PPGLayout
	var oPPGItem = oLayout.Item( "TestGrid" )

	//Locked only makes sense if you set an explicit Height to the control
	oPPGItem.SetAttribute( "LockColumnHeader", PSet.ColHeaderMode.Value == 2 ) ;
	oPPGItem.SetAttribute( "HideColumnHeader", PSet.ColHeaderMode.Value == 1 ) ;

	PSet.Refresh()

	if ( PSet.ColHeaderMode.Value == 2 )
	{
		Logmessage( "Setting LockColumnHeader attribute on Layout" ) ;
	}
	else if (  PSet.ColHeaderMode.Value == 1 )
	{
		Logmessage( "Setting HideColumnHeader attribute on Layout" ) ;
	}

}

function GridTester_RowHeaderMode_OnChanged()
{
	var oLayout = PSet.Inspected(0).PPGLayout
	var oPPGItem = oLayout.Item( "TestGrid" )

	oPPGItem.SetAttribute( "LockRowHeader", PSet.RowHeaderMode.Value == 2 ) ;
	oPPGItem.SetAttribute( "HideRowHeader", PSet.RowHeaderMode.Value == 1 ) ;

	PSet.Refresh()

	if ( PSet.RowHeaderMode.Value == 2 )
	{
		Logmessage( "Setting LockRowHeader attribute on Layout" ) ;
	}
	else if (  PSet.RowHeaderMode.Value == 1 )
	{
		Logmessage( "Setting HideRowHeader attribute on Layout" ) ;
	}
}


//**************************************************************
//
// EXAMPLE from PPGLayout.AddColor reference
//
//**************************************************************

function PPGProxyParam_Execute()
{


	// Proxy Parameters are an useful way to centralize parameters from
	// different objects on the same property, or even to build a simplified
	// version of a property page.

	// This example demonstrates creation of a custom property set
	// that only shows a few items of the Shader that it controls,
	// but maintains a pleasing layout.

	newscene( null, false ) ;
	var oSphere = ActiveSceneRoot.AddGeometry( "Sphere", "MeshSurface" ) ;
	oSphere.AddMaterial( "Phong"  );

	var oPhongShader = oSphere.Material.Shaders(0) ;

	// This is a Boolean for enabling diffuse
	var oDiffuseEnable = oPhongShader.Parameters( "diffuse_inuse" ) ;

	// These are CompoundParameters, each with R,G,B sub-parameters
	var oAmbientParam = oPhongShader.Parameters( "ambient" ) ;
	var oDiffuseParam = oPhongShader.Parameters( "diffuse" ) ;

	var oCustomProperty = oSphere.AddProperty("CustomProperty",false,"Proxies");

	AddProxyParam(oCustomProperty, oDiffuseEnable, "");

	AddProxyParam(oCustomProperty, oDiffuseParam.FullName + ".red", "");
	AddProxyParam(oCustomProperty, oDiffuseParam.FullName + ".green", "");
	AddProxyParam(oCustomProperty, oDiffuseParam.FullName + ".blue", "");


	AddProxyParam(oCustomProperty, oAmbientParam.FullName + ".red", "");
	AddProxyParam(oCustomProperty, oAmbientParam.FullName + ".green", "");
	AddProxyParam(oCustomProperty, oAmbientParam.FullName + ".blue", "");

	// If we inspect the object now we would see 4 separate sliders,
	// each controlling a different component, and with very long
	// name like "sphere_Material_Phong_ambient_red"
	// We can create a custom layout to clean up the display

	var oLayout = oCustomProperty.PPGLayout

	oLayout.AddGroup( "Phong Diffuse" )

		oLayout.AddItem( "sphere_Material_Phong_diffuse_inuse", "Enable" ) ;

		// Just for fun, show the ambient before the diffuse, which
		// is the opposite of the normal Phong Property Page
		oLayout.AddColor( "sphere_Material_Phong_ambient_red", "Ambient", false ) ;
		oLayout.AddColor( "sphere_Material_Phong_diffuse_red", "Diffuse", false ) ;

	oLayout.EndGroup() ;

	oLayout.Logic = sphere_Material_Phong_diffuse_inuse_OnChanged.toString() ;
	oLayout.Language = "JScript" ;

	// Show both dialogs.  You will see that both items
	// are identical.
	InspectObj ( oCustomProperty, null, null, siLock ) ;
	InspectObj ( oPhongShader, null, null, siLock ) ;
}

function sphere_Material_Phong_diffuse_inuse_OnChanged()
{
	// A little Property Page event code to properly
	// grey out the color controls if the Disable checkbox is
	// clicked

	bEnable = PSet.sphere_Material_Phong_diffuse_inuse.Value ;

	// To disable the color control we just disable the proxy
	// parameter representing the "red" component
	PSet.sphere_Material_Phong_ambient_red.Enable( bEnable ) ;
	PSet.sphere_Material_Phong_diffuse_red.Enable( bEnable ) ;	
}

//**************************************************************
//
// EXAMPLE from PPGItem.UIItems reference
//
//**************************************************************

function PPGLists_Execute()
{
	// Create a simple custom property set
	var oCustomProperty = ActiveSceneRoot.AddProperty( 
			"CustomProperty", 
			false, 
			"ObjectList" ) ;

	oCustomProperty.AddParameter( "AllObjects", siString ) ;
	oCustomProperty.AddParameter( "SelObjects", siString ) ;

	// Establish the layout
	// Which will be two list controls with 2 buttons 
	// in between

	var oLayout = oCustomProperty.PPGLayout

	oLayout.AddRow() ;

	  oLayout.AddGroup( "", false, 45) ;
		PPGLists_AddListBox( oLayout, "AllObjects" ) ;
	  oLayout.EndGroup() ;

	  oLayout.AddGroup( "", false, 10) ;
	    oLayout.Addbutton( "Add", ">>" ) ;
	    oLayout.Addbutton( "Remove", "<<" ) ;        
	  oLayout.EndGroup() ;

	  oLayout.AddGroup( "", false, 45) ;
		PPGLists_AddListBox( oLayout, "SelObjects" ) ;
	  oLayout.EndGroup() ;

	oLayout.EndRow() ;

	oLayout.Language = "JScript" ;
	oLayout.SetAttribute( "LogicPrefix", "PPGLists_" )	
	oLayout.Logic = PPGLists_Add_OnClicked.toString() + 
			PPGLists_Remove_OnClicked.toString() + 
			PPGLists_MoveSelected.toString() ;


	// Populate the "AllObjects" list control
	PPGLists_AddSceneItemsToList( oLayout, "AllObjects" ) ;

	// Let the user play with the UI
	if ( !InspectObj( oCustomProperty, null,null ,siModal, false ) )
	{
		PPGLists_DoSomethingWithSelectedObjects( oCustomProperty ) ;
	}

	// Cleanup
	DeleteObj( oCustomProperty ) ;	
}

function PPGLists_AddListBox( in_oLayout, in_Name )
{
	// Insert a ListBox into the layout
	var oItem = in_oLayout.AddItem( in_Name, "", "ListBox" ) ;
	oItem.SetAttribute( "CY", 100 ) ;
	oItem.SetAttribute( "NoLabel", true ) ;
}

function PPGLists_AddSceneItemsToList( in_oLayout, in_Name )
{
	// Populate the specified list with the
	// names of objects in the scene

	var oSceneItems = ActiveSceneRoot.FindChildren() ;

	var aItems = new Array( oSceneItems.Count * 2 ) ;

	for ( i = 0 ; i < oSceneItems.Count ; i++ )
	{
		// Both label and value will be the same string
		aItems[i * 2] = oSceneItems.Item(i).Name ;
		aItems[i * 2 + 1] = oSceneItems.Item(i).Name ;			
	}

	var oItem = in_oLayout.Item(in_Name);

	oItem.UIItems = aItems ;
}

function PPGLists_DoSomethingWithSelectedObjects( in_oPSet )
{
	oPPGItem = in_oPSet.PPGLayout.Item( "SelObjects" ) ;

	// This is bit of an unusual scenario:
	// Rather than using the Parameter Value, which is
	// equal to the last Selected item in the list,
	// we are interested in the entire list of items in the 
	// layout.  Note: because this data is part of the layout,
	// not the Parameter, it is not persisted as part of
	// the scene and is shared by all instances.

	var vbItems = new VBArray(oPPGItem.UIItems);
	var aItems = vbItems.toArray();

	for ( i = 0 ; i < aItems.length ; i+= 2 )
	{
		logmessage( "Object " + aItems[i] + " was selected" ) ;
	}
}


//Property Page Event code - this code executes
//as the script logic of the Property Page.

function PPGLists_Add_OnClicked()
{
	PPGLists_MoveSelected( "AllObjects", "SelObjects" ) ;
}

function PPGLists_Remove_OnClicked()
{
	PPGLists_MoveSelected( "SelObjects", "AllObjects" ) ;
}

function PPGLists_MoveSelected( in_FromList, in_ToList )
{
	// Figure out what was selected by the user

	strSel = PPG.Inspected(0).Parameters(in_FromList).Value ;

	if ( strSel.length == 0 )
	{	
		logmessage( "Please select an item" ) ;
		return ;
	}

	var oLayout = PPG.PPGLayout ;

	var oToList = oLayout.Item( in_ToList ) ;
	var oFromList = oLayout.Item( in_FromList ) ;


	// Add the string to the "ToList"	

	var vbItems = new VBArray(oToList.UIItems);
	var aItems = vbItems.toArray();

	// Check if the item is already in the list
	for ( i = 0 ; i < aItems.length ; i+=2 )
	{
		if ( aItems[i] == strSel )
		{
			logmessage( strSel + " is already in the list" ) ;
			return ;
		}
	}

	// Push the item to end of the list
	var cntExistingItems = aItems.length

	aItems[cntExistingItems] = strSel ; // Label
	aItems[cntExistingItems+1] = strSel ; // Value

	oToList.UIItems = aItems ;

	// Remove the item from the "FromList"

	vbItems = new VBArray(oFromList.UIItems);
	var aCurrentItems = vbItems.toArray() ;
	var aNewItems = new Array() ;

	// Fill in the new array with everything except
	// for the selected item
	for ( i = 0 ; i < aCurrentItems.length; i++ )
	{
		if ( aCurrentItems[i] != strSel )
		{
			aNewItems[aNewItems.length] = aCurrentItems[i] ;
		}		
	}

	oFromList.UIItems = aNewItems ;

	// Reset the selection
	if ( aNewItems.length > 0 )
	{
		PPG.Inspected(0).Parameters(in_FromList).Value = aNewItems[0] ;
	}
	else
	{
		PPG.Inspected(0).Parameters(in_FromList).Value = "" ;
	}

	// A refresh is required to show the change
	PPG.Refresh() ;
}


//**************************************************************
//
// EXAMPLE from View reference
//
//**************************************************************

function PPGInView_Execute()
{
	// Demonstrate how we can host a Custom Property inside
	// a view.  
	//
	// This has some advantages over the InspectObj command:
	//
	// -we can specify the exact size and positioning of the window
	// -the view is exposed in the Layout.Views collection so we can
	// find out if the property page is already being "inspected".
	//
	// However it does not support the "Modal" mode supported by
	// InspectObj.

	// Step 1: Create the custom property

	var oPSet = ActiveSceneRoot.AddProperty( "CustomProperty",false, "MyProp" )
	oPSet.AddParameter3( "textparam", siString ) ;
	oPSet.AddFCurveParameter( "MyFCurve" ) ;

	var oLayout = oPSet.PPGLayout ;
	oLayout.Clear() ;
	oLayout.AddItem("textparam");
	oLayout.AddItem("MyFCurve");

	oLayout.AddRow()
	oLayout.AddButton( "MoveView", "Move View" ) ;
	oLayout.AddButton( "Close" ) ;
	oLayout.EndRow()

	oLayout.Language = "JScript"
	oLayout.SetAttribute( "LogicPrefix", "PPGInView_" )		
	oLayout.Logic = PPGInView_MoveView_OnClicked.toString()
		+ PPGInView_Close_OnClicked.toString() ;


	// Step 2: Show the custom property in a view

	var oActiveLayout = Application.Desktop.ActiveLayout
	var oNewView = oActiveLayout.CreateView( "Property Panel", "MyPropView" )

	oNewView.BeginEdit();
	oNewView.Move( 10, 10 )
	oNewView.Resize( 340, 340 )
	oNewView.SetAttributeValue( "targetcontent", oPSet.FullName )
	oNewView.EndEdit();
}

// Logic code used by the buttons on the Custom Property

function PPGInView_MoveView_OnClicked()
{
	// We can't get to the view directly from the PPG object,
	// but we can find it indirectly by searching through
	// the open views

	var thisCustomProp = PPG.Inspected.Item(0).FullName

	var oActiveLayout = Application.Desktop.ActiveLayout

	for ( i = 0 ; i < oActiveLayout.Views.Count ; i++ )
	{
		var oView = oActiveLayout.Views(i) ;

		if ( oView.Type == "Property Panel" )
		{
			if ( oView.GetAttributeValue( "targetcontent" ) == thisCustomProp )
			{
				// found it!		
				oView.Move( 250, 250 ) ;
				return ;
			}
		}
	}
}

function PPGInView_Close_OnClicked()
{
	// Self destruction of the custom property
	DeleteObj( PPG.Inspected.Item(0) ) ;

	PPG.Close() ;
}


//**************************************************************
//
// EXAMPLE of the Text Editor Widget
//
// This example shows the various features of the new text editor 
// widget. It creates multiple instances of the widget each having
// different properties.
//
//**************************************************************


function PPGTextEditor_Execute()
{
    var oPSet = ActiveSceneRoot.AddProperty( "CustomProperty", false, "Text Editor Widget" ) ;
    oPSet.AddParameter3( "Text1",siString, "This is a text widget with folding capability\n{\n\n fold me up!\n\n}") ;
    oPSet.AddParameter3( "Text2",siString, "This is another text editor widget with a black background. Notice that the scrollbars have been disabled and that lines of text too long to fit in the window like this one automatically wraps to the next line.") ;
    oPSet.AddParameter3( "Text3",siString, "//this text editor shows formatted text in c++ fashion.\n#preprocessor test\n\n class MyClass { highlighted word }") ;
    
    // Customize the text editor widgets
    var oLayout = oPSet.PPGLayout;
    oLayout.Clear();
    oLayout.AddGroup( "siControlTextEditor Widgets" );	
    oItem = oLayout.AddItem( "Text1", "Text1", siControlTextEditor );
    
    // Set this editor to be 200 pixels high, have line numbers appear
    // on the left margin, enable text folding and use Tahoma as a font.
    oItem.SetAttribute( siUIHeight, 200 ) ;
    oItem.SetAttribute( siUILineNumbering, true ) ;
    oItem.SetAttribute( siUIFolding, true ) ;
    oItem.SetAttribute( siUIMarginWidth, 3 ) ;
    oItem.SetAttribute( siUIFont, "Tahoma" ) ;
    
    // This editor will look and behave quite differently than the one above. 
    // Here we remove its scroll bars, make the text wrap when lines
    // are too long to fit (siUILineWrap) and change the background and
    // text colors.
    oItem = oLayout.AddItem( "Text2", "Text2", siControlTextEditor );
    oItem.SetAttribute( siUIHeight, 150 ) ;
    oItem.SetAttribute( siUILineNumbering, false ) ;
    oItem.SetAttribute( siUIFolding, false ) ;
    oItem.SetAttribute( siUIMarginWidth, 0 ) ;
    oItem.SetAttribute( siUIHorizontalScroll, false ) ;
    oItem.SetAttribute( siUIVerticalScroll, false ) ;
    oItem.SetAttribute( siUILineWrap, true ) ;
    oItem.SetAttribute( siUIFont, "Arial" ) ;
    oItem.SetAttribute( siUIFontSize, 18 ) ;
    oItem.SetAttribute( siUIBackgroundColor,  0x000000 );
    oItem.SetAttribute( siUIForegroundColor,  0xCCCCCC );
    
    // This editor shows off the syntax highlighting capabilities.
    // We specify the language code we want to use. In this case,
    // we use "cpp". This will highlight all reserved words for the 
    // C++ language and will colorize special statements such as
    // comments, preprocessor directives such as include and define.
    // We also add our own list of keywords that should be highlighted.
    oItem = oLayout.AddItem( "Text3", "Text3", siControlTextEditor );
    oItem.SetAttribute( siUIHeight, 400 ) ;
    oItem.SetAttribute( siUILineNumbering, true ) ;
    oItem.SetAttribute( siUIMarginWidth, 6 ) ;
    oItem.SetAttribute( siUIFont, "Tahoma" ) ;
    oItem.SetAttribute( siUICommentFont, "Comic Sans MS" ) ;
    oItem.SetAttribute( siUILanguage,  "cpp" );
    oItem.SetAttribute( siUIKeywords,  "highlighted word" );
    
    oLayout.EndGroup();
    InspectObj( oPSet ) ;
}

