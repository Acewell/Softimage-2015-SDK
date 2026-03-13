'Example of a custom property containing a synoptic widget
'
'This plug-in depends on additional files in the "synoptic" directory
'
'	Copyright 2008 Autodesk, Inc.  All rights reserved.  
'	Use of this software is subject to the terms of the Autodesk license agreement 
'	provided at the time of installation or download, or which otherwise accompanies 
'	this software in either electronic or hard copy form.   

function XSILoadPlugin( in_reg )
	in_reg.Author = "Softimage"
	in_reg.Name = "Embedded Synoptic Plugin"
	in_reg.Major = 1
	in_reg.Minor = 0

	in_reg.RegisterProperty "EmbeddedSynoptic"	
	
	'Provide a command that adds the custom property to an object
	'You could also provide a menu callback to do the same thing
	in_reg.RegisterCommand "ApplyEmbeddedSynoptic"
	
	'Provide an easy way to demonstrate this example
	in_reg.RegisterCommand "DemoEmbeddedSynoptic"
	
	'RegistrationInsertionPoint - do not remove this line

	XSILoadPlugin = true
end function

function EmbeddedSynoptic_Define( ctxt )
	dim oCustomProperty
	set oCustomProperty = ctxt.Source

	oCustomProperty.AddParameter2 "path",siString,"",,,,,0,siPersistable
	oCustomProperty.AddParameter2 "Increment",siDouble,1.0,0.0,10.0
	
	'The "path" parameter associated with the synoptic control
	'specifies the full path of the synoptic html file.
	'To avoid hard-coding an absolute path, we determine the path 
	'relative to this script file.
	set oThisPlugin = Application.Plugins( "Embedded Synoptic Plugin" )
	oCustomProperty.path.Value = oThisPlugin.OriginPath & ".." & XSIUtils.Slash & _
							 "synoptic" & XSIUtils.Slash & "embeddedsynoptic.htm"
	
	EmbeddedSynoptic_Define = true
end function

function EmbeddedSynoptic_DefineLayout( ctxt )
	dim oLayout,oItem
	set oLayout = ctxt.Source
	oLayout.Clear 

	'UI text that explains how to use the synoptic view
	oLayout.AddStaticText _
		"Click the sphere to translate the parent object by the specified increment." & _
                vbCRLF & "Click the large cone to reset the translations.", _
                400
	
	'Create the synoptic widget, which loads the synoptic view specified by the path parameter
	set oItem = oLayout.AddItem("path", "", siControlSynoptic)
	oItem.setattribute siUINoLabel,true
	
	oLayout.AddSpacer
	
	'A normal numeric slider
	oLayout.AddItem "increment"
	
	EmbeddedSynoptic_DefineLayout = true
end function

'Set the UI text using the name of the parent object
function EmbeddedSynoptic_OnInit()

	sUIText = "Click a sphere to translate " & _ 
		  PPG.Inspected(0).Parent & _
		  " by the specified increment." & _
		  vbCRLF & "Click the large cone to reset the translations."
		  
	PPG.PPGLayout.Item(0).Label = sUIText
	
end function


function ApplyEmbeddedSynoptic_Init( ctxt )
	dim oCmd
	set oCmd = ctxt.Source
	oCmd.Description = ""
	oCmd.ReturnValue = true

	dim oArgs
	set oArgs = oCmd.Arguments
	
	'The Collection arg handler gives us the current selection 
	'if no argument is explicitly specified
	oArgs.AddWithHandler "target","Collection"
	
	ApplyEmbeddedSynoptic_Init = true
end function

function ApplyEmbeddedSynoptic_Execute( target )

	'Error handling of the input argument	
	if target = "" then
		Logmessage "Invalid argument to ApplyEmbeddedSynoptic", siError
		exit function		
	elseif target.Type = "XSICollection" then
		'target may be a collection of items, such as the current selection	
		dim oItem 
		for each oItem in target
			if NOT oItem.IsClassOf( siX3DObjectID ) then			
				Logmessage "Invalid argument " & oItem.FullName & " to ApplyEmbeddedSynoptic", siError			
				exit function
			end if
		next
	elseif NOT target.IsClassOf( siX3DObjectID ) then
		Logmessage "Invalid argument " & oItem.FullName & " to ApplyEmbeddedSynoptic", siError				
	end if 

	'Create the custom property
	dim properties		
	SIAddProp "EmbeddedSynoptic",target,,,properties
	
	'Show the custom property in the property panel	
	if  Application.Interactive then
		set view = desktop.activelayout.createview("property panel","Synoptic")	
		view.setattributevalue "targetcontent",properties(0).fullname
		
		'We use a Property Panel view instead of InspectObj because
		'we can resize the view to better fit the synoptic view
		view.resize 500,420
	end if
	
	ApplyEmbeddedSynoptic_Execute = true
end function


'For demonstration purposes,  create an object and add the custom property
function DemoEmbeddedSynoptic_Execute()
	set target = ActiveSceneRoot.AddGeometry( "Cone", "MeshSurface", "DemoCone" )
	ApplyEmbeddedSynoptic( target )
	
	DemoEmbeddedSynoptic_Execute = true
end function



