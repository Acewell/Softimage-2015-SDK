// InternationalPSetUI.js
//
// This example shows how to internationalize the PPG.
// The codes to create the UI dialogs are same to the PSetUIDemo SDK example.  
//  
// In this example, following steps for the internationalization are involved:
// 1.  Internationalize the PPG
//		 Set the siUIDictionary attribute supported on PPGLayout if necessary. 
//       By default all labels, combo box items and other visible strings on a PPG are automatically translated 
//		 if that string is found in the XSISPDLFILE string dictionary. 
//       To turn off all translation set this attribute to "None". 
//		 To specify a different dictionary set this attribute to the name of the dictionary (without the .dict extension) 
// 2.  Internationalize the menu labels.
// 3.  Internationalize the message box.
// 4.  Internationalize the log messages.

// The same example is also available as a C++ API based Custom Property
// as a SPDL based Custom Property and as a Real Time Shader
//
//	Copyright 2013 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.  
//  
function XSILoadPlugin( in_reg )
{
	// register plug-in information
	in_reg.Author = "Autodesk, Inc.";
	in_reg.Name = "InternationalPSetUI JScript Version";

	// var the version number of this plug-in 
	in_reg.Major = 1;
	in_reg.Minor = 0 ;

	in_reg.RegisterProperty( "InternationalPSetUIJScript" );
	
	// For convenience we also install a menu entry that will allow the user
	// to easily create instances of this custom property
	in_reg.RegisterMenu( siMenuTbGetPropertyPSetID,"InternationalPSetUIJScript_Menu",false,false );	
}

function XSIUnloadPlugin(in_reg)
{
	return true;
}

function InternationalPSetUIJScript_Define( io_Context )
{
	// Here is where we add all the parameters to the 
	// Custom Property.  This will be called each time 
	// an new instance of the Custom Property is called.
	// It is not called when an persisted Custom Property is loaded.
	
	var oPSet;
	oPSet = io_Context.Source;
	
	// Capability used for most of the numeric parameters
	// (siPersistable is actually optional)
	animcaps = siAnimatable | siPersistable ;

	//	
	// Parameters on the "Numbers" tab
	//	
	// Often no UI range is specified, in which case the min/max is used
	
						// ScriptName,				vartype   	dft  	min  	max  	suggmin,suggmax,class,caps		,name
	oPSet.AddParameter2( "NoSliderDemo", 			siDouble,	1.05, 	0, 		100, 	null,	null,	0,	  animcaps );
	oPSet.AddParameter2( "ThumbWheelDemo", 			siFloat,	99.9, 	-1000.0,1000.0,	null,	null,	0,	  animcaps );
	oPSet.AddParameter2( "NoLabelDemo", 			siUByte,	15, 	10, 	20, 	null,	null,	0,	  animcaps );
	oPSet.AddParameter2( "NoLabelNotAnimatable", 	siInt2,	    230, 	200, 	300, 	null,	null,	0,	  siPersistable );
	
	oPSet.AddParameter2( "ValueOnlyDemo", 			siInt2,		215, 	200, 	300, 	null,	null,	0,	  animcaps );
	oPSet.AddParameter2( "NormalSlider", 			siDouble,	50, 	0, 		100, 	null,	null,	0,	  animcaps );					
	oPSet.AddParameter2( "LogarithmicSliderDemo",	siDouble,	50, 	0, 		100, 	null,	null,	0,	  animcaps );

	//
	// Parameters on the "File Controls" tab
	//	
	// As far as the Custom Property is concerned these 
	// are just normal string parameters but the
	// layout turns them into more powerful controls.
	//
	// Note: for ImportFileName we specify a name different from the Scripting name
	// For the others we provide a label when we call AddItem in InternationalPSetUIJScript_DefineLayout
	
	oPSet.AddParameter2( "ExportFilename",			siString ) ;
	oPSet.AddParameter2( "ImportFilename",			siString,	null, 	null, 	null, 	null,	null,	0,		0,		"Import Filename");		
	oPSet.AddParameter2( "ImportImage",				siString ) ;
	oPSet.AddParameter2( "FolderPicker",			siString ) ;	

	//			
	// Parameters on the "Text" tab
	//	
	oPSet.AddParameter2( "MultiLine",				siString ) ;
	oPSet.AddParameter2( "EnableEdit",				siBool,		true,		0,	-1 ) ;
	oPSet.AddParameter2( "CurrentPass",				siString,	null, 	null, 	null, 	null,	null,	0,siPersistable|siReadonly ) ;

	//
	// Parameters on the "Colors" tab		
	//
	
	
	//Each color contains 3 or 4 parameters, one for each channel
	//These must be defined IN ORDER.
	//You can specify a min/max that is outside the range 0,1 but the
	//UI range must always be 0 to 1
	
						// ScriptName,				vartype   	dft  	min  	max  	suggmin,suggmax,class,caps		,name	
	oPSet.AddParameter2( "MyRGBAColorR",			siDouble,	0, 	-1000.0, 	1000.0,		0,	1,		0,	  animcaps, "MyRGBAColor" ); 
	oPSet.AddParameter2( "MyRGBAColorG",			siDouble,	0, 	-1000.0, 	1000.0,		0,	1,		0,	  animcaps ); 
	oPSet.AddParameter2( "MyRGBAColorB",			siDouble,	0, 	-1000.0, 	1000.0,		0,	1,		0,	  animcaps ); 
	oPSet.AddParameter2( "MyRGBAColorA",			siDouble,	0, 	-1000.0, 	1000.0,		0,	1,		0,	  animcaps ); 
	oPSet.AddParameter2( "MyRGBColorR",				siFloat,	0.4,	  0,		 1,		0,	1,		0,	  animcaps, "MyRGBColor" ); 
	oPSet.AddParameter2( "MyRGBColorG",				siFloat,	0.3,	  0,		 1,		0,	1,		0,	  animcaps ); 
	oPSet.AddParameter2( "MyRGBColorB",				siFloat,	0.3,	  0,		 1,		0,	1,		0,	  animcaps ); 
	
	// 
	// Parameters on the "Options" tab
	//
	
	
						// ScriptName,				vartype   	dft  	min  	max  	suggmin,suggmax,class,caps			,name		
	oPSet.AddParameter2( "ComboDemo",				siInt4,		5, 		5, 		10,		null,	null,	0,	animcaps ) ;
	oPSet.AddParameter2( "DynamicCombo",			siString ) ;
	oPSet.AddParameter2( "RadioBtnDemo", 			siInt4,		11,		0, 		222,	null,	null,	0,	animcaps )
	oPSet.AddParameter2( "BitMaskDemo", 			siInt4,		1,		0,		64 ) ;
	oPSet.AddParameter2( "ListBoxDemo", 			siInt4,		null,	null,	null,	null,	null,	0,	animcaps ) ;
	
	// Read-only in the UI, but the value will be set by Logic code
	oPSet.AddParameter2( "Selection",				siBool,		null,	0,		-1,		null,	null,	0,	siPersistable|siReadonly ) ;

	// Parameters on the "Check Boxes" tab
	//
	// Booleans are a bit funny in scripting, because "true" has the value -1
	// hence CheckB is on by default, others are off.

						// ScriptName,				vartype   	dft  	min  	max  	suggmin,suggmax,class,caps		,name		
	oPSet.AddParameter2( "Check1",					siBool,		0 ) ;
	oPSet.AddParameter2( "Check2",					siBool,		0 ) ;
	oPSet.AddParameter2( "CheckA",					siBool,		0 ) ;
	oPSet.AddParameter2( "CheckB",					siBool,		-1) ;

	oPSet.AddParameter2( "CheckButton",				siBool ) ;

	// Parameters on the "Images" tab
	oPSet.AddParameter2( "ImageClipControl",			siString, "Clips.noIcon_pic" ) ;
	oPSet.AddParameter2( "ImageClipControlClipHidden",	siString, "Clips.noIcon_pic" ) ;
	oPSet.AddParameter2( "StaticBitmapControl",			siString ) ;
}

function InternationalPSetUIJScript_DefineLayout( io_Context )
{
	// Softimage will call this to define the visual appearance of the CustomProperty
	// The layout is shared between all instances of the CustomProperty
	// and is cached.  You can force the code to re-execute by using the 
	// XSIUtils.Refresh feature.

	var oLayout,oItem;
	oLayout = io_Context.Source;

	var oItem ;
	oLayout.Clear() ;

	// By default, all labels, combo box items and other visible strings on a PPG are automatically translated
	// if that string is found in the XSISPDLFILE translation dictionary. 
	//To specify a different dictionary, set "DictNamespace" parameter to the name of the dictionary without the .dict
	// extension.
	oLayout.SetAttribute( siUIDictionary, "InternationalPSetUIDemo" );
	
	// The code indentation matches the nesting inside the layout.
	oLayout.AddTab( "Numbers" ) ;

		oLayout.AddGroup() ;
			oLayout.AddRow() ;
				// To save space turn off the slider and just show an edit control			
				oItem = oLayout.AddItem( "NoSliderDemo" ) ;
					oItem.SetAttribute( siUINoSlider, true ) ;
					
				// A potentially better way to save space
				oItem = oLayout.AddItem( "ThumbwheelDemo", "Thumbwheel" ) ;
					oItem.SetAttribute( siUIThumbWheel, true ) ;

			oLayout.EndRow() ;
		oLayout.EndGroup() ;

		oLayout.AddGroup( "NoLabel and ValueOnly" ) ;
			// Shows how to hide the divot or label
			oItem = oLayout.AddItem( "NoLabelDemo" ) ;
				oItem.SetAttribute( siUINoLabel, true );

			oItem = oLayout.AddItem( "NoLabelNotAnimatable" ); 
				oItem.SetAttribute( siUINoLabel, true );

			oItem = oLayout.AddItem( "ValueOnlyDemo" ) ;
				oItem.SetAttribute( siUIValueOnly, true );
			
		oLayout.EndGroup() ;

		oItem = oLayout.AddItem( "NormalSlider" ) ;
			oItem.SetAttribute( "Decimals", 1 );

		oItem = oLayout.AddItem( "LogarithmicSliderDemo", "Logarithmic Slider Demo" ) ;
			oItem.SetAttribute( siUILogarithmic, true );
			oItem.SetAttribute( siUISyncSlider, true );	// Already true by default
			oItem.SetAttribute( siUINoSlider, false );	// Already false by default
			oItem.SetAttribute( siUIDecimals, 5 );

	oLayout.AddTab( "File Controls" ) ;

		oItem = oLayout.AddItem( "ExportFilename","Export Filename",siControlFilePath ) ;
			// Export is the default option, so this control will give an "overwrite?" warning if
			// the file already exists.
			// Other attributes exist that are not demonstrated,
			// See the siPPGItemAttribute enum documentation for more info

			// If the parameter value is empty that the browser will open in the Models
			// subdirectory of the current project
			oItem.SetAttribute( siUIInitialDir, "project" ) ;
			oItem.SetAttribute( siUISubFolder, "Models" ) ;
			
			// This decides what file extensions to display			
			oItem.SetAttribute( siUIFileFilter, "Text files (*.txt)|*.txt|All Files (*.*)|*.*||" ) ;

		oItem = oLayout.AddItem( "ImportFilename","",siControlFilePath ) ;		
			oItem.SetAttribute( siUIFileFilter, 
							"spdl files (*.spdl)|*.spdl|" +
							"xsiaddon files (*.xsiaddon)|*.xsiaddon|" +
							"All Files (*.*)|*.*||" );
			oItem.SetAttribute( siUIOpenFile, true ) ;
			oItem.SetAttribute( siUIFileMustExist, true );			
			
			if ( Application.Platform == "Win32" )
			{
				oItem.SetAttribute( siUIInitialDir, "c:\\temp" ) ;
			}
			else
			{
				oItem.SetAttribute( siUIInitialDir, "/var/tmp" ) ;			
			}
		oItem = oLayout.AddItem( "ImportImage","Import Image",siControlFilePath ) ;		
			// Rather than a huge long, hardcoded file filter just specify this to get all supported image formats
			oItem.SetAttribute( siUIImageFile, true ) ;
			oItem.SetAttribute( siUIOpenFile, true ) ;
			oItem.SetAttribute( siUIFileMustExist, true );			

		// Rather than picking a file, this control lets you pick a directory
		oItem = oLayout.AddItem( "FolderPicker", "Pick Folder", siControlFolder ) ;
			oItem.SetAttribute( siUIInitialDir, "user" ) ;
			oItem.SetAttribute( siUIInitialDir, "Application/spdl" ) ;

	oLayout.AddTab( "Text" ) ;
		oLayout.AddGroup( "Multi-Line Edit" );
			// Make it 180 pixels tall
			oItem = oLayout.AddString( "MultiLine", "",true, 180 ) ;
				oItem.SetAttribute( siUINoLabel, true );

			oItem = oLayout.AddItem( "EnableEdit", "Enable Edit" ) ;
		oLayout.EndGroup() ;

		oLayout.AddGroup("Current Pass Info");
			// Use a row to put both the edit and the button on the same line		
			oLayout.AddRow() ;
				// The value of this disabled control will be filled 
				// in by the logic when the button is pressed			
				oItem = oLayout.AddItem( "CurrentPass" ) ;
					// Specify a larger value so that the button does not take
					// an unfair share of the width
					oItem.WidthPercentage = 80

				oItem = oLayout.AddButton( "MyButton","Find pass" ) ;
					oItem.WidthPercentage = 20
			oLayout.EndRow() ;
		oLayout.EndGroup() ;

	oLayout.AddTab( "Colors" ) ;
		// Starting with v4.2 we have static text support
		// directly on the PPGLayout
		oItem = oLayout.AddStaticText( "Each color channel is a separate parameter:" ) ;

		// Note how we only mention the first parameter of our
		// group of 4 parameters that make up the color
		oLayout.AddColor( "MyRGBAColorR", "", true ) ;
		oLayout.AddColor( "MyRGBColorR", "", false ) ;

	oLayout.AddTab( "Options" ) ;
		oLayout.AddGroup();
			// The layout code to deal with Combo Boxes, Radios, Bitmasks and ListBoxes
		    // is practically identical		
			oItem = oLayout.AddItem( "ComboDemo" ); 
				oItem.UIItems = Array( "Item 1", 5, 
										"Item 2", 6, 
										"Item 3", 8 ) ; 
				oItem.Type = siControlCombo ; //Also can be specified as 3rd arg to AddItem
			
			oItem = oLayout.AddItem( "DynamicCombo","",siControlCombo ); 
				oItem.UIItems = Array( "Default", "Default");
		
			oItem = oLayout.AddItem( "RadioBtnDemo", "Radio Button", siControlRadio ) ;
				oItem.UIItems = Array( "Val 0", 0, 
									   "Val 11", 11,
									   "Val 222", 222  ) ; 

			var items = Array( "Item 1", 1, "Item 2", 2, "Item 3", 3 ) ;			
			oItem = oLayout.AddEnumControl( "ListBoxDemo", items, "", siControlListBox ) ;
				oItem.SetAttribute( siUICY, 80 ) ;
				oItem.SetAttribute( siUIStyle, 0x0101 ) ;
										
		oLayout.EndGroup() ; 

		oLayout.AddGroup( "Bitmask Demo" );
			oLayout.AddRow() ;
				oItem = oLayout.AddItem( "BitMaskDemo","", siControlCheck ) ;
					oItem.LabelPercentage = 80 ;
					oItem.LabelMinPixels = 50 ;
					oItem.SetAttribute( siUIValueOnly, true ) ;
					oItem.UIItems = Array( "Flag 1", 1, 
										   "Flag 4", 4, 
										   "Flag 16", 16 ) ; 

				// Show this explanation text next to the control
				// "\r\n" is used to split the static text onto multiple lines
				// (If necessary you could also tweak the size of the static control,
				// by setting siUICX, and siUICY)
					oLayout.AddStaticText( XSIUtils.Translate(1, "InternationalPSetUIDemo") );
					
			oLayout.EndRow() ;
		oLayout.EndGroup() ; 

		// Put a blank line between the groups
		oLayout.AddSpacer() ;

		oLayout.AddGroup( "Spdl logic controlled" ) ;
			oItem = oLayout.AddItem( "Selection", "Selection?" ) ;
		oLayout.EndGroup() ; 


	oLayout.AddTab( "Check Boxes" ) ;

		// Show how to put 2 groups side by side with
		// unequal distribution
		oLayout.AddRow() ;
			oLayout.AddGroup( "Letter", true, 40 ) ;
				oLayout.AddItem( "Check1","1") ;
				oLayout.AddItem( "Check2","2") ;
			oLayout.EndGroup() ; 
			oLayout.AddGroup( "Number", true, 60 ) ;
				oLayout.AddItem( "CheckA","A" ) ;			
				oLayout.AddItem( "CheckB","B" ) ;
			oLayout.EndGroup() ; 
		oLayout.EndRow() ;	
				
		// This is a useful trick for saving space
		// It is a boolean parameter but
		// it displays itself as a button, so there is
		// no space wasted by a label
		oItem = oLayout.AddItem( "CheckButton", "", "dscontrol" ) ;
			oItem.SetAttribute( "class", "button" ) ;
			oItem.SetAttribute( siUICX, 120 ) ;
			oItem.SetAttribute( siUICaption, "Invert" ) ;
			// The style is based on these Windows style codes
			// #define BS_AUTOCHECKBOX     0x00000003L
			// #define BS_PUSHLIKE         0x00001000L
			oItem.SetAttribute( siUIStyle, 0x00001003 ) ;
			oItem.SetAttribute( siUINoLabel, true ) ;								


	oLayout.AddTab( "Images" ) ;
	
		oLayout.AddGroup( "Image Clips Demo" );
			oItem = oLayout.AddItem( "ImageClipControl", "Image Clip 1", siControlImageClip ) ;
			oItem = oLayout.AddItem( "ImageClipControlClipHidden", "Image Clip 2", siControlImageClip ) ;
				oItem.SetAttribute( siUIShowClip, false ) ;
		oLayout.EndGroup() ;
		
		oLayout.AddGroup( "Static Bitmap Demo" );
		oItem = oLayout.AddItem("StaticBitmapControl", "Static Bitmap", siControlBitmap);
			var strLogoFileName = XSIUtils.BuildPath(Application.InstallationPath(siFactoryPath), "XSISDK/examples/workgroup/Addons/InternationalPSetUI/Data/Bitmaps/logo.bmp" );
			oItem.SetAttribute(siUIFilePath, strLogoFileName);
		oLayout.EndGroup() ;
}

function InternationalPSetUIJScript_OnInit()
{
	/*
	By creating a OnInit() routine we can perform some scripting at the time 
	the dialog shows itself

	The "ppg" object that we access is a global object that is
	available only inside the spdl logic.  (It is also available by its old
	name "pset") It corresponds to the UI of the property set, not the 
	underlying Custom Property object. 

	It offers access to the individual controls by referring to them by the
	parameter name.

	Each of these control supports the Value and Enable property.

	See the PPG object in the SDK Object Model reference for further info.

	In this case we set the selection check box if there
	is a current selection
	*/
	PPG.Selection.Value = ( Application.Selection.Count > 0 ) ;

	/*
	The pset object also provides access to the underlying inspected object(s)

	The following code will provide an Object Model pointer
	to the actual Custom Property objects that are being inspected
	*/
	
	for ( i = 0 ; i < PPG.Inspected.Count ; i++ )
	{
		var oItem = PPG.Inspected.Item(i);
		Application.Logmessage( XSIUtils.Translate(2, "InternationalPSetUIDemo", oItem.Name, oItem.Parameters.Count.toString()) );
		Application.LogMessage(oItem.Name + " is nested underneath " + oItem.Parent.FullName ) ;		
	}
	
	//Demonstrate how to fill in some initial data into the multiline edit control
	PPG.MultiLine.Value = "From scripting use \\r\\n\r\nto break a string into multiple lines." +
							"\r\n\r\n\t\\t is useful too\r\n" +
							"Use \\ character to include other special characters like \" and \'" ;			
							
		
	//Demonstrate how to use the PPGLayout to populate the items inside the ComboBox
	var oPPGItem = PPG.PPGLayout.Item("DynamicCombo");

	//Replacing the Default string that was originally defined at the Parameter level
	aComboItem = new Array("StringLabel1","StringValue1","StringLabel2","StringValue2");
	oPPGItem.UIItems = aComboItem;

	//Setting the value for the DynamicCombo to the second value "StringValue2"
	//This could also have been written this way: PPG.DynamicCombo.value = "StringValue2"
	PPG.Inspected(0).Parameters("DynamicCombo").Value = "StringValue2";

	//Redraw the PPG to show the new combo items
	PPG.Refresh();
													
}

/*Callback routines can be added according to the convention 
  <propertyname>_<parametername>_OnChanged(), 
  <propertyname>_<buttonname>_OnClicked()
  <propertyname>_<tablabelwithoutspaces>_OnTab()
*/

function InternationalPSetUIJScript_MyButton_OnClicked()
{
	//We can execute code when the button is pressed
	//In this case we call an Softimage Command "GetCurrentPass"

	strCurrentPass = GetCurrentPass();

	LogMessage(XSIUtils.Translate(3, "InternationalPSetUIDemo", strCurrentPass));
	
	//This updates the value of the "read-only" string
	//parameter
	PPG.CurrentPass.Value = strCurrentPass
} 

function InternationalPSetUIJScript_NoSliderDemo_OnChanged()
{
	//You can provide custom reaction code when an parameter changes
	Logmessage(XSIUtils.Translate(5, "InternationalPSetUIDemo", PPG.NoSliderDemo.Value));
}

function InternationalPSetUIJScript_EnableEdit_OnChanged()
{
	//Controls can be dynamically disabled and enabled
	PPG.MultiLine.Enable( PPG.EnableEdit.Value ) ;

	logmessage( PPG.EnableEdit.Value ) ;
}

function InternationalPSetUIJScript_MyRGBColorG_OnChanged()
{
	//The scripting for dealing with colors is basically the same
	//as any other parameter - we just handle each channel of the
	//color as separate parameters

	//In this case we force the blue to follow to green
	PPG.MyRGBColorB.Value = PPG.MyRGBColorG.Value ;
}

//Starting with v4.0 you can also get called when
//tabs change.  The callback name is based on the tab label
//with all spaces removed.
//Note: this callback is not called if the PSet is set
//to display in list mode.
function InternationalPSetUIJScript_FileControls_OnTab()
{
	Logmessage( XSIUtils.Translate(4, "InternationalPSetUIDemo") );
}

function InternationalPSetUIJScript_Menu_Init( io_Context )
{
	var oMenu;
	oMenu = io_Context.Source;
	oMenu.AddCallbackItem(XSIUtils.Translate("InternationalPSetUI - &JScript Version", "InternationalPSetUIDemo"), "OnInternationalPSetUIJScriptMenuClicked");
}

function OnInternationalPSetUIJScriptMenuClicked( io_Context )
{
	var oProp,oParent;
	if (Selection.Count == 0)
	{
		XSIUIToolkit.MsgBox( XSIUtils.Translate("Please select something and try again", "InternationalPSetUIDemo") ); 
		return;
	}
	oParent = Selection.Item( 0 );
	oProp = oParent.AddProperty( "InternationalPSetUIJScript" );
	InspectObj( oProp );
	return 1;
}

