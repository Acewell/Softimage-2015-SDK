'
'	Copyright 2008 Autodesk, Inc.  All rights reserved.  
'	Use of this software is subject to the terms of the Autodesk license agreement 
'	provided at the time of installation or download, or which otherwise accompanies 
'	this software in either electronic or hard copy form.   

 function XSILoadPlugin( in_reg )
  in_reg.name = "MyTextConverter"
  
 	in_reg.RegisterConverterEvent "myCustomTextLoader",siOnCustomFileImport,"TXT"
 	in_reg.RegisterConverterEvent "myCustomTextSaver",siOnCustomFileExport,"TXT"
 
 	XSILoadPlugin = true
 end function
 
 function XSIUnloadPlugin( in_reg )
 	dim strPluginName
 	strPluginName = in_reg.Name
 	Application.LogMessage strPluginName & " has been unloaded.",16
 	XSIUnloadPlugin = true
 end function
 
 ' Callback for the siOnCustomFileImport event.
 function myCustomTextLoader_OnEvent( ctxt )
 
 	' log some diag info
 	logMessage "myCustomTextLoader Event called..."
 	logMessage "Target: " & ctxt.GetAttribute("Target")
 	logMessage "Filename: " & ctxt.GetAttribute("FileName")
 	
 	' retrieve the filename
 	filename = ctxt.GetAttribute("FileName")
 	
 	' create the filesystemobject
 	set fso = CreateObject("Scripting.FileSystemObject")
 	
 	' check if the file exists
 	if not fso.FileExists(filename) then
 		logmessage "File does not exist!",siError
 	else
 		
 		' get the target from the scene
 		set target = ctxt.GetAttribute("Target")
 		
 		' open the text file
 		set stream = fso.OpenTextFile(filename)
 		
 		' code for models
 		if target.type = "#model" then
 
 		    ' read all lines
 		    do while not stream.atEndOfStream
 			    values = split(stream.readline(),"|")
 			    set nul = target.AddNull(values(0))
 			    SetValue nul & ".kine.local.posx",values(1)
 			    SetValue nul & ".kine.local.posy",values(2)
 			    SetValue nul & ".kine.local.posz",values(3)
 		    loop
        
        ' code for deltas
        elseif target.type = "model_delta" then
        
            ' not implemented yet
            
        ' code for actions
        elseif target.type = "Action" then
        
            ' not implemented yet
            
        end if
         		
 		' close the stream again
 		stream.close
 	end if
 
 	' Return value is ignored as this event can not be aborted.
 	myCustomTextLoader_OnEvent = true
 end function
 
 ' Callback for the siOnCustomFileExport event.
 function myCustomTextSaver_OnEvent( ctxt )
 
 	' log some diag info
 	logMessage "myCustomTextSaver Event called..."
 	logMessage "Target: " & ctxt.GetAttribute("Target")
 	logMessage "Filename: " & ctxt.GetAttribute("FileName")
 	
 	' retrieve the filename
 	filename = ctxt.GetAttribute("FileName")
 	
 	' get the filesystemobject
 	set fso = CreateObject("Scripting.FileSystemObject")
 	
 	' create a text file
 	set stream = fso.CreateTextFile(filename)
 
 	' if the text has not been created, error out
 	if NOT isObject(stream) then
 		logmessage "File could not be created",siError
 	else
 		' get the target from the scene
 		set target = ctxt.GetAttribute("Target")
 		
 		' code for models
 		if target.type = "#model" then
 
	 		' loop through all children
	 		for each child in target.children
	 			line = child.name
	 			line = line & "|" & child.kinematics.local.parameters("posx").value
	 			line = line & "|" & child.kinematics.local.parameters("posy").value
	 			line = line & "|" & child.kinematics.local.parameters("posz").value
	 			stream.writeline line
	 		next

        ' code for deltas	 		
		elseif target.type = "model_delta" then
			
			' not implemented yet
			
        ' code for actions
        elseif target.type = "Action" then
        
            ' not implemented yet
            
		end if 		
		
 		' close the stream again
 		stream.close
 	end if 
 
 	' Return value is ignored as this event can not be aborted.
 	myCustomTextSaver_OnEvent = true
 end function
