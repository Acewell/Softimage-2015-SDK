
'
'	Copyright 2008 Autodesk, Inc.  All rights reserved.  
'	Use of this software is subject to the terms of the Autodesk license agreement 
'	provided at the time of installation or download, or which otherwise accompanies 
'	this software in either electronic or hard copy form.   

function XSILoadPlugin( in_reg )
	'Called on Softimage startup to establish that we contain a Custom Property
	'called SimpleProperty.

	in_reg.Author = "Softimage" 
	in_reg.Name = "SimpleProperty SDK Example"

	' Note: we don't specify a specific value for the
	' PluginRegistrar Help property, because Softimage will automatically
	' find and use ....\PPGDemos\netview_PPGDemos.htm	
	
	in_reg.url = "http://www.softimage.com"

	in_reg.Major = 1
	in_reg.Minor = 1

	in_reg.RegisterProperty "SimpleProperty"

	'Ability to create this property will be exposed in the
	'Softimage menu system.  This makes it as easy for a user to attach this
	'property to an object as it is for internal objects
	in_reg.RegisterMenu siMenuTbGetPropertyPSetID, "SimpleProperty_Menu", false, false

	XSILoadPlugin = true 
end function

function SimpleProperty_Define( io_Context )
	'Called when a new custom property is created
	'of type SimpleProperty
	'This is your chance to add the parameters
	'(See the CustomProperty reference for details)

	set oCustomProperty = io_Context.Source

	oCustomProperty.AddParameter3 "Zeta_R", siDouble, 0.3, 0.0, 1.0 
	oCustomProperty.AddParameter3 "Zeta_G", siDouble, 0.75, 0.0, 1.0 
	oCustomProperty.AddParameter3 "Zeta_B", siDouble, 0.3, 0.0, 1.0 
	oCustomProperty.AddParameter3 "Omega", siInt4, 256, 0, 66535 
	oCustomProperty.AddParameter3 "Flags", siInt2, 16
	set oFCurveParam = oCustomProperty.AddFCurveParameter("Kappa")
	set oGridParam = oCustomProperty.AddGridParameter( "Omnikron" )

	'There is a default curve created automatically 
	'but we want these specific default values
	set oFCurve = oFCurveParam.Value
	oFCurve.SetKeys( Array(0, 20.0, 10, 50.0, 20, -20.0, 40, 0.0 ))

	set oGrid = oGridParam.Value

	oGrid.SetColumnLabel 0, "A" 
	oGrid.SetColumnLabel 1, "B" 
	oGrid.SetColumnLabel 2, "C" 
	oGrid.SetColumnLabel 3, "D" 

	ResetGrid oGrid
end function

sub ResetGrid( io_Grid )
	'(See the GridData reference for details)
	'Establish the default 4x4 matrix
	dim m(3,3)  
	m(0, 0) = 1 : m(1, 0) = 0 : m(2, 0) = 0.25 : m(3,0) = 0
	m(0, 1) = 0 : m(1, 1) = 0 : m(2, 1) = 0.33 : m(3,1) = 0.5
	m(0, 2) = 1 : m(1, 2) = 0 : m(2, 2) = 0.10 : m(3,2) = 0.25
	m(0, 3) = 0 : m(1, 3) = 0 : m(2, 3) = 0.00 : m(3,3) = 0

	io_Grid.Data = m
end sub

function SimpleProperty_DefineLayout( io_Context )
	'This is called only once each time you run Softimage to determine
	'the UI layout for all the property pages of type SimpleProperty

	'(You can force it to be called with XSIUtils.Reload)

	'(See the PPGLayout reference for details)

	set oPPGLayout = io_Context.Source

	'Important first step is to erase any existing contents
	oPPGLayout.Clear

	oPPGLayout.AddItem "Omega"
	oPPGLayout.AddColor "Zeta_R", "Zeta", false 

	'Example bitfield with data for the game engine
	oPPGLayout.AddEnumControl "Flags", _
		Array( "Disable epsilon", 1, "Attach", 8, "X", 16 ),,siControlCheck

	set oPPGItem = oPPGLayout.AddItem( "Kappa", ,siControlFCurve )
	oPPGItem.SetAttribute siUIValueOnly, true

	
	oPPGLayout.AddGroup "Omnikron Matrix"

	set oPPGItem = oPPGLayout.AddItem( "Omnikron", , siControlGrid )
	oPPGItem.SetAttribute siUIValueOnly, true 
	oPPGItem.SetAttribute siUIGridHideRowHeader, true 
	oPPGItem.SetAttribute siUIGridColumnWidths, 85

	oPPGLayout.AddButton "ResetGrid", "Reset Grid"
	
	oPPGLayout.EndGroup
end function

'
' Logic Code
'

function SimpleProperty_OnInit()
	LogMessage "Someone is inspecting the CustomProperty " & PPG.Inspected(0).FullName
	set oGridData = PPG.Omnikron.Value

	'Enforce the value of some of the cells whenever the PPG is opened
	oGridData.SetCell 0, 0, 0.99
	oGridData.SetCell 1, 2, 0.45
end function

function SimpleProperty_ResetGrid_OnClicked
	ResetGrid PPG.Omnikron.Value
end function

'Example validation of the parameters
'Warn the user when the turn on a flag that might not apply
function SimpleProperty_Flags_OnChanged	
	if ( PPG.Omega.Value < 512 ) then
		if (( PPG.Flags AND 8 ) = 8 ) then
			MsgBox "Warning: The Attach flag is ignored when the value of Omega is too small"
		end if
	end if
end function

'
' Menu code to add the entry
'

function SimpleProperty_Menu_Init( io_Context )
	'There will be a single menu item, hooked up to
	'the callback routine defined below
	set menu = io_Context.Source
	menu.AddCallbackItem "&SimpleProperty", "OnSimplePropertyMenuClicked" 
end function

function OnSimplePropertyMenuClicked( io_Context )
	on error resume next

	'Create a new instance of the custom property
	'defined in this file
	
	if (Selection.Count = 0 ) then
		set prop = ActiveSceneRoot.AddProperty( "SimpleProperty")
		InspectObj prop
	else
	
		for each oSel in Selection
			set prop = oSel.AddProperty( "SimpleProperty")
			InspectObj prop		
			'Not all objects support custom properties
			'for example you can't nest custom properties
			if err <> 0 then
				logmessage "Failed to create new property under " & oSel
			end if
		next
	end if
end function
