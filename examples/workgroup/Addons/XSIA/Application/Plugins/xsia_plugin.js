// +---------------------------------------+
// | This plugin demonstrates the use of   |
// | an asset summary file to transport    |
// | scene information from one to another.|
// +---------------------------------------+
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

// The function called by Softimage when loading the plugin.
function XSILoadPlugin( in_reg )
{
	in_reg.Author = "Helge Mathee";
	in_reg.Name = "XSIA Import/Export Scripted";
	in_reg.Email = "";
	in_reg.URL = "";
	in_reg.Major = 2;
	in_reg.Minor = 1;

 	in_reg.RegisterConverterEvent("XSIAExportEvent",siOnCustomFileExport,"XSIA");
 	in_reg.RegisterConverterEvent("XSIAImportEvent",siOnCustomFileImport,"XSIA");

	in_reg.RegisterCommand("XSIA_Export","XSIA_Export");
	in_reg.RegisterCommand("XSIA_Import","XSIA_Import");
	in_reg.RegisterCommand("XSIA_GetXSIAObject","XSIA_GetXSIAObject");

	in_reg.RegisterMenu( siMenuMainFileExportID, "XSIA_Export_Menu", false );
	in_reg.RegisterMenu( siMenuMainFileImportID, "XSIA_Import_Menu", false );

	return true;
}

// The function called by Softimage when unloading the plugin.
function XSIUnloadPlugin( in_reg )
{
	strPluginName = in_reg.Name;
	Application.LogMessage(strPluginName + " has been unloaded.");
	return true;
}

function  XSIA_Export_Menu_Init( in_ctxt )
{
   var oMenu = in_ctxt.source;
   oMenu.AddCommandItem( "Export XSIA", "XSIA_Export");
}

function  XSIA_Import_Menu_Init( in_ctxt )
{
   var oMenu = in_ctxt.source;
   oMenu.AddCommandItem( "Import XSIA", "XSIA_Import");
}

// Callback for the XSIA Saver Event
function XSIAExportEvent_OnEvent( ctxt )
{
	// Log some diagnostic information
	logMessage("XSIA Export Event called...");
	logMessage("Target: " + ctxt.GetAttribute("Target"));
	logMessage("Filename: " + ctxt.GetAttribute("FileName"));
	
	// if the target is the scene_root then we are saving the full scene
	if(ctxt.GetAttribute("Target")+"" == ActiveSceneRoot+"")
	{
		var allModels = ActiveSceneRoot.models;
		var allPasses = ActiveProject.ActiveScene.Passes;
		var allLayers = ActiveProject.ActiveScene.Layers;
		var allMatLibs = ActiveProject.ActiveScene.MaterialLibraries;
		var objects = new ActiveXObject("XSI.Collection");
		
		// add only models which are children of the sceneroot 
		// (no private models or nested ones)
		for(var i=0;i<allModels.count;i++)
			if(allModels(i).model+"" == ActiveSceneRoot+"")
				objects.Add(allModels(i));
		
		// add all passes except the default pass
		for(var i=0;i<allPasses.count;i++)
			if(allPasses(i).name.toLowerCase()!="default_pass")
				objects.Add(allPasses(i));
				
		// add all layers except the default layer
		for(var i=0;i<allLayers.count;i++)
			if(allLayers(i).name.toLowerCase()!="layer_default")
				objects.Add(allLayers(i));
				
		// add all matlib which are external
		for(var i=0;i<allMatLibs.count;i++)
			if(allMatLibs(i).storage.value!=0)
				objects.Add(allMatLibs(i));
				
		// export the content to the file
		XSIA_Export(objects,ctxt.GetAttribute("FileName"));
	}
	// otherwise we are dealing with a model or delta
	else
	{
		var root = Dictionary.GetObject(ctxt.GetAttribute("Target")+"");
		logmessage(root.type);
		if(root.type=="model_delta")
		{
			// export the content to the file
			XSIA_Export(root,ctxt.GetAttribute("FileName"));
		}
		else
		{
			var allModels = root.models;
			var objects = new ActiveXObject("XSI.Collection");
			
			// add only models which are children of the root 
			// (no private models or nested ones)
			for(var i=0;i<allModels.count;i++)
				if(allModels(i).model+"" == root+"")
					objects.Add(allModels(i));
	
			// export the content to the file
			XSIA_Export(objects,ctxt.GetAttribute("FileName"));
		}
	}
}

// Callback for the XSIA Loader Event
function XSIAImportEvent_OnEvent( ctxt )
{
	// Log some diagnostic information
	logMessage("XSIA Import Event called...");
	logMessage("Target: " + ctxt.GetAttribute("Target"));
	logMessage("Filename: " + ctxt.GetAttribute("FileName"));
	
	// if the target is the scene_root then we are saving the full scene
	if(ctxt.GetAttribute("Target")+"" == ActiveSceneRoot+"")
	{
		// import the XSIA content
		XSIA_Import(ctxt.GetAttribute("FileName"));

		// get rid of the default objects
		try{
			DeleteObj("light");
		}catch(e){}
		try{
			DeleteObj("B:Camera_Root");
		}catch(e){}
			
	}
	// we are dealing with a model
	else
	{
		// import the content "onto" a model
		XSIA_Import(ctxt.GetAttribute("FileName"),Dictionary.GetObject(ctxt.GetAttribute("Target")+""));;
	}
}

// Init function for the XSIA_Export script command.
function XSIA_Export_Init( ctxt )
{
	// Define the command
	var oCmd;
	oCmd = ctxt.Source;
	oCmd.Description = "Export selected items to a XSIA file";
	oCmd.ReturnValue = false;

	// Define the arguments
	var oArgs;
	oArgs = oCmd.Arguments;
	oArgs.AddWithHandler("objects",siArgHandlerCollection);
	oArgs.Add("filename",siArgumentInput);
	return true;
}

// The execution code for the XSIA_Export script command
function XSIA_Export_Execute(objects,filename)
{
	// if the objects argument is not specified,
	// try to use the selection
	if(objects.count==0)
		objects.AddItems(selection);
	
	// if the filename argument was not specified
	// show a browser to browse for the file
	if(!filename)
	{
		if(application.Interactive)
		{
			var fileBrowser = XSIUIToolkit.FileBrowser ;
			fileBrowser.DialogTitle = "Select a file" ;
			fileBrowser.Filter = "XSIA Files (*.xsia)|*.xsia||" ;
			fileBrowser.ShowSave() ; 
			filename = fileBrowser.FilePathName;
			fileBrowser = null;
		}
		else
		{
			logmessage("XSIA_Export: No filename specified in BATCH",siError);
			return false;
		}
	}
	
	// if the filename argument is still not specified
	// (the dialog was aborted) error out.
	if(!filename)
	{
		logmessage("XSIA_Export: No filename. Aborted by user.",siWarning);
		return false;
	}
	
	// create the XSIA object.
	var file = new XSIA();
	
	// loop through all objects and add them
	// to the XSIA description object.
	file.AddItemsFromCollection (objects)

	// write the description of the XSIA to the
	// XML / XSIA file.
	file.WriteToFile(filename);
	
	file.Clear();
	file = null;
	
	return true;
}

// Init function for the XSIA_Export script command.
function XSIA_Import_Init( ctxt )
{
	// Define the command
	var oCmd;
	oCmd = ctxt.Source;
	oCmd.Description = "Import selected items from a XSIA file";
	oCmd.ReturnValue = false;

	// Define the arguments
	var oArgs;
	oArgs = oCmd.Arguments;
	oArgs.Add("filename",siArgumentInput);
	oArgs.AddWithHandler("parent",siArgHandlerSingleObj,ActiveSceneRoot);
	return true;
}

// The execution code for the XSIA_Export script command
function XSIA_Import_Execute(filename,parent)
{
	
	// if the filename argument was not specified
	// show a browser to browse for the file
	if(!filename)
	{
		if(application.Interactive)
		{
			var fileBrowser = XSIUIToolkit.FileBrowser ;
			fileBrowser.DialogTitle = "Select a file" ;
			fileBrowser.Filter = "XSIA Files (*.xsia)|*.xsia||" ;
			fileBrowser.ShowOpen() ; 
			filename = fileBrowser.FilePathName;
		}
		else
		{
			logmessage("XSIA_Import: No filename specified in BATCH",siError);
			return false;
		}
	}
	
	// if the filename argument is still not specified
	// (the dialog was aborted) error out.
	if(!filename)
	{
		logmessage("XSIA_Import: Aborted by user.",siWarning);
		return false;
	}

	// create the XSIA object.
	var file = new XSIA();
	file.ReadFromFile(filename);
	file.BuildInScene(parent);

	file.Clear();
	file = null;
	
	return true;
}

// Init function for the XSIA_Export script command.
function XSIA_GetXSIAObject_Init( ctxt )
{
	// Define the command
	var oCmd;
	oCmd = ctxt.Source;
	oCmd.Description = "Returns an XSIA Javascript object.";
	oCmd.ReturnValue = true;
	return true;
}

// The execution code for the XSIA_Export script command
function XSIA_GetXSIAObject_Execute(objects,filename)
{
	return new XSIA();
}

//=========================================
// XSIA Object
//=========================================
// This object stores information relevant for a XSIA file.

// Constructor function
function XSIA(in_container)
{
	this.container = in_container;
	this.filename = "";
	this.models = XSIFactory.CreateObject("XSI.Collection");
	this.groups = XSIFactory.CreateObject("XSI.Collection");
	this.layers = XSIFactory.CreateObject("XSI.Collection");
	this.passes = XSIFactory.CreateObject("XSI.Collection");
	this.actions = XSIFactory.CreateObject("XSI.Collection");
	this.matlibs = XSIFactory.CreateObject("XSI.Collection");
	this.xsia_includes = XSIFactory.CreateObject("XSI.Collection");
	this.repository = XSIUtils.DataRepository;
	this.name_map = new Array();
	this.type = "XSIA";
		
	// when creating the first XSIA we need to search for all deltas,
	// object_partitions and light_partitions.
	if(!in_container)
	{
		XSIADeltas = FindObjects('','{6D906778-A713-40E3-A5FB-0F5CA3361370}');
		XSIAPartitions = XSIFactory.CreateObject('XSI.Collection');
		XSIAPartitions.AddItems(FindObjects('','{8B291AD2-AAC2-4F09-A027-B47E6C11E4AC}')); // object partitions
		XSIAPartitions.AddItems(FindObjects('','{7A1BB9D6-58A3-49D6-84BA-39429EDAD489}')); // light partitions
		XSIAFXTrees = FindObjects('','{3F7F4AFE-BC8B-4B98-9A16-771119EC3CD9}');
		XSIAFXOutputs = FindObjects('','{9ACB71FF-0E3E-41CC-BB6B-D050B9DACD41}');
	}
}

// Attach all functions to the object
XSIA.prototype.Clear = XSIA_Clear;
XSIA.prototype.AddItemFromScene = XSIA_AddItemFromScene;
XSIA.prototype.AddItemsFromCollection = XSIA_AddItemsFromCollection;
XSIA.prototype.AddItemsFromArray = XSIA_AddItemsFromArray;
XSIA.prototype.WriteToFile = XSIA_WriteToFile;
XSIA.prototype.GetAsText = XSIA_GetAsText;
XSIA.prototype.ReadFromFile = XSIA_ReadFromFile;
XSIA.prototype.BuildInScene = XSIA_BuildInScene;
XSIA.prototype.Tabs = XSIATabs;
XSIA.prototype.CleanPath = XSIACleanPath;
XSIA.prototype.GetXmlToken = XSIAGetXmlToken;
XSIA.prototype.GetXmlClosed = XSIAGetXmlClosed;
XSIA.prototype.GetXmlAttribute = XSIAGetXmlAttribute;

// global variables used in the XSIA constructor
var XSIADeltas = false;
var XSIAPartitions = false;
var XSIAFXTrees = false;
var XSIAFXOutputs = false;

// Adds an object from the scene to the XSIA object description
function XSIA_AddItemFromScene(item)
{
	// if the specified item is a string, try to getobject
	if(typeof item=="string")
	{
		try
		{
			item = Dictionary.GetObject(item);
		}
		catch(e)
		{
			return false;
		}
	}
	
	// if the specified item is not an object, error out.
	if(typeof item!="object")
	{
		logmessage("XSIA.AddItemFromScene: Invalid item.",siError);
		return false;
	}
	
	// get the classID of the object
	var clsID = XSIUtils.Datarepository.GetIdentifier(item,siObjectCLSID);
	
	// for models	
	if(clsID=="{0496EAB0-0ECF-11D1-ABF1-00A02485CECB}")
	{
		var newModel = new XSIAModel(this);
		newModel.SetFromScene(item);
		this.models.Add(newModel);
	}
	// for groups
	else if(clsID=="{9D0673C2-6741-11D1-BE9F-00A024EE478D}")
	{
		var newGroup = new XSIAGroup(this);
		newGroup.groupType = 'group';
		newGroup.SetFromScene(item);
		this.groups.Add(newGroup);
	}
	// for layers
	else if(clsID=="{479F2E10-3900-11D1-B0B3-00A024C79287}")
	{
		var newGroup = new XSIAGroup(this);
		newGroup.groupType = 'layer';
		newGroup.SetFromScene(item);
		this.layers.Add(newGroup);
	}
	// for passes
	else if(clsID=="{BFDAF164-5DD8-4422-9F1E-35527CDC2A02}")
	{
		var newPass = new XSIAPass(this);
		newPass.SetFromScene(item);
		this.passes.Add(newPass);
	}
	// for deltas
	else if(clsID=="{6D906778-A713-40E3-A5FB-0F5CA3361370}")
	{
		for(var i=0;i<item.actionDeltas.count;i++)
		{
			var newAction = new XSIAAction(this);
			newAction.SetFromScene(item.actionDeltas(i));
			this.actions.Add(newAction);
		}
	}
	// for matlibs
	else if(clsID=="{61782E14-9177-412E-BF9B-2B44B9A668DD}")
	{
		var newMatLib = new XSIAMatLib(this);
		newMatLib.SetFromScene(item);
		this.matlibs.Add(newMatLib);
	}
	else
	{
		// otherwise (if not model, layer or pass nor delta)
		logmessage("XSIA.AddItemFromScene: Invalid item "+item+" skipped.",siWarning);
	}
	return true;
}

// adds all objects from a given collection to the XSIA object
function XSIA_AddItemsFromCollection(items)
{
	// if not a collection, error out.
	if(typeof items!="object")
	{
		return false;
	}
	
	// loop through all items and call "AddItemFromScene"
	for(var i=0;i<items.count;i++)
	{
		if(!this.AddItemFromScene(items.item(i)))
		{
			logmessage("XSIA.AddItemsFromCollection: Invalid item.",siError);
			return false;
		}
	}

	return true;
}

// adds all objects from a given javascript array
function XSIA_AddItemsFromArray(items)
{
	// if not an array, error out.
	if(typeof items!="object")
	{
		return false;
	}
	
	// loop through all elements of the array and call AddItemFromScene
	for(var i=0;i<items.length;i++)
	{
		if(!this.AddItem(items[i]))
		{
			logmessage("XSIA.AddItemsFromArray: Invalid item.",siError);
			return false;
		}
	}

	return true;
}

// Clears the XSIA object
function XSIA_Clear()
{
	this.container = null;
	for(var i=0;i<this.models.count;i++)
		this.models(i).Clear();
	this.models.RemoveAll();
	
	for(var i=0;i<this.layers.count;i++)
		this.layers(i).Clear();
	this.layers.RemoveAll();
	
	for(var i=0;i<this.passes.count;i++)
		this.passes(i).Clear();
	this.passes.RemoveAll();
	
	for(var i=0;i<this.xsia_includes.count;i++)
		this.xsia_includes(i).Clear();
	this.xsia_includes.RemoveAll();
	
	for(var i=0;i<this.actions.count;i++)
		this.actions(i).Clear();
	this.actions.RemoveAll();

	for(var i=0;i<this.matlibs.count;i++)
		this.matlibs(i).Clear();
	this.matlibs.RemoveAll();
	
	this.name_map = new Array();
	return true;
}

// Returns the description of the XSIA object as a string
function XSIA_GetAsText(tabs)
{
	var xml = this.Tabs(tabs)+'<?xml version="1.0" encoding="iso-8859-1"?>\n\n';
	xml += this.Tabs(tabs)+'<xsia_file type="AssetSummaryFile" xsi_version="';
	xml += Application.Version();
	xml += '" syntax_version="1.0">\n';

	if(this.matlibs.count>0)
	{
		xml += this.Tabs(tabs+1)+'<matlibs>\n';
		for(var i=0;i<this.matlibs.count;i++)
		{
			xml += this.matlibs(i).GetAsText(tabs+2)+'\n';;
		}
		xml += this.Tabs(tabs+1)+'</matlibs>\n';
	}

	if(this.models.count>0)
	{
		xml += this.Tabs(tabs+1)+'<models>\n';
		for(var i=0;i<this.models.count;i++)
		{
			xml += this.models(i).GetAsText(tabs+2)+'\n';;
		}
		xml += this.Tabs(tabs+1)+'</models>\n';
	}

	if(this.groups.count>0)
	{
		xml += this.Tabs(tabs+1)+'<groups>\n';
		for(var i=0;i<this.groups.count;i++)
		{
			xml += this.groups(i).GetAsText(tabs+2,'group')+'\n';;
		}
		xml += this.Tabs(tabs+1)+'</groups>\n';
	}

	if(this.layers.count>0)
	{
		xml += this.Tabs(tabs+1)+'<layers>\n';
		for(var i=0;i<this.layers.count;i++)
		{
			xml += this.layers(i).GetAsText(tabs+2,'layer')+'\n';;
		}
		xml += this.Tabs(tabs+1)+'</layers>\n';
	}

	if(this.passes.count>0)
	{
		xml += this.Tabs(tabs+1)+'<passes>\n';
		for(var i=0;i<this.passes.count;i++)
		{
			xml += this.passes(i).GetAsText(tabs+2)+'\n';;
		}
		xml += this.Tabs(tabs+1)+'</passes>\n';
	}

	if(this.actions.count>0)
	{
		xml += this.Tabs(tabs+1)+'<actions>\n';
		for(var i=0;i<this.actions.count;i++)
		{
			xml += this.actions(i).GetAsText(tabs+2)+'\n';;
		}
		xml += this.Tabs(tabs+1)+'</actions>\n';
	}

	xml += this.Tabs(tabs)+'</xsia_file>';
	return xml;
}

// Writes the description of the XSIA object to a file (XML)
function XSIA_WriteToFile(filename)
{
	if(!typeof filename=="string")
	{
		return false;
	}
	
	filename= this.CleanPath(filename);

	if(filename.indexOf(XSIUtils.Slash)==-1)
	{
		logmessage("XSIA.WriteToFile: Invalid filename: "+filename,siError);
		return false;
	}
	
	var fso = XSIFactory.CreateObject('Scripting.FileSystemObject');
	var folderPath = filename.substr(0,filename.lastIndexOf(XSIUtils.Slash ));
	if(!fso.FolderExists(folderPath))
	{
		logmessage("XSIA.WriteToFile: Folder "+folderPath+" does not exist!",siError);
		return false;
	}
	
	// cut off the extension
	filename = filename.replace(/\..*$/,'');
	
	var nestCount = 0;
	
	// loop through the direct child xsia files of this one.
	for(var i=0;i<this.xsia_includes.count;i++)
	{
		nestCount++;
		this.xsia_includes(i).WriteToFile(filename+'_xsia_includes_'+nestCount+'.xsia');
		this.xsia_includes(i).filename = filename+'_xsia_includes_'+nestCount+'.xsia';
	}
	
	// through all the groups and export their presets
	for(var i=0;i<this.groups.count;i++)
	{
		SavePreset(this.groups(i).scnPtr, filename+'_group_'+this.groups(i).name+".Preset", null, null, null, false, null);
		this.groups(i).filename = filename+'_group_'+this.groups(i).name+".Preset";
	}

	// through all the layers and export their presets
	for(var i=0;i<this.layers.count;i++)
	{
		SavePreset("Layers."+this.layers(i).name, filename+'_layer_'+this.layers(i).name+".Preset", null, null, null, false, null);
		this.layers(i).filename = filename+'_layer_'+this.layers(i).name+".Preset";
	}

	// through all the passes and export their presets
	for(var i=0;i<this.passes.count;i++)
	{
		SavePreset("Passes."+this.passes(i).name, filename+'_pass_'+this.passes(i).name+".Preset", null, null, null, false, null);
		this.passes(i).filename = filename+'_pass_'+this.passes(i).name+".Preset";
	}

	var fso = XSIFactory.CreateObject('Scripting.FileSystemObject');

	// now save the xml file
	var xml = this.GetAsText(0);	
	var xmlFile = fso.CreateTextFile(filename+".xsia");
	xmlFile.Write(xml);
	xmlFile.Close();
	
	xmlFile = null;
	fso = null;
	
	return true;
}

// reads the content from a xml file and puts it into the object
function XSIA_ReadFromFile(filename)
{
	if(!typeof filename=="string")
	{
		return false;
	}
	
	filename= this.CleanPath(filename);

	if(filename.indexOf(XSIUtils.Slash)==-1)
	{
		logmessage("XSIA.WriteToFile: Invalid filename: "+filename,siError);
		return false;
	}
	
	var fso = XSIFactory.CreateObject('Scripting.FileSystemObject');

	if(!fso.FileExists(filename))
	{
		logmessage("XSIA.ReadFromFile: File "+filename+" does not exist!",siError);
		return false;
	}

	var file = fso.OpenTextFile(filename);
	var line = '';
	while(true)
	{
		try
		{
			line = file.ReadLine();
		}
		catch(e)
		{
			break;			
		}
		
		if(!line)
			continue;
		
		var token = this.GetXmlToken(line);
		
		if(token=="model")
		{
			var newModel = new XSIAModel(this);
			if(!newModel.SetFromTextStream(file,line))
			{
				logmessage("XSIA: ReadFromFile: Syntax error in xml file",siError);
				file.Close();
				return false;
			}
			this.models.Add(newModel);
		}
		else if(token=="matlib")
		{
			var newMatLib = new XSIAMatLib(this);
			if(!newMatLib.SetFromTextStream(file,line))
			{
				logmessage("XSIA: ReadFromFile: Syntax error in xml file",siError);
				file.Close();
				return false;
			}
			this.matlibs.Add(newMatLib);
		}
		else if(token=="group")
		{
			var newLayer = new XSIAGroup(this);
			if(!newLayer.SetFromTextStream(file,line))
			{
				logmessage("XSIA: ReadFromFile: Syntax error in xml file",siError);
				file.Close();
				return false;
			}
			this.layers.Add(newLayer);
		}
		else if(token=="layer")
		{
			var newLayer = new XSIAGroup(this);
			if(!newLayer.SetFromTextStream(file,line))
			{
				logmessage("XSIA: ReadFromFile: Syntax error in xml file",siError);
				file.Close();
				return false;
			}
			this.layers.Add(newLayer);
		}
		else if(token=="pass")
		{
			var newPass = new XSIAPass(this);
			if(!newPass.SetFromTextStream(file,line))
			{
				logmessage("XSIA: ReadFromFile: Syntax error in xml file",siError);
				file.Close();
				return false;
			}
			this.passes.Add(newPass);
		}
		else if(token=="action")
		{
			var newAction = new XSIAAction(this);
			if(!newAction.SetFromTextStream(file,line))
			{
				logmessage("XSIA: ReadFromFile: Syntax error in xml file",siError);
				file.Close();
				return false;
			}
			this.actions.Add(newAction);
		}
		else if(token=="xsia_include")
		{
		}		
	}
	
	file.Close();
	
	return true;
}

// builds the content of the XSIA file in the scene
function XSIA_BuildInScene(parent)
{
	for(var i=0;i<this.matlibs.count;i++)
		if(!this.matlibs(i).BuildInScene(parent))
			return false;

	for(var i=0;i<this.models.count;i++)
		if(!this.models(i).BuildInScene(parent))
			return false;

	for(var i=0;i<this.xsia_includes.count;i++)
		if(!this.xsia_includes(i).BuildInScene(parent))
			return false;

	for(var i=0;i<this.groups.count;i++)
		if(!this.groups(i).BuildInScene(parent))
			return false;

	for(var i=0;i<this.layers.count;i++)
		if(!this.layers(i).BuildInScene(parent))
			return false;

	for(var i=0;i<this.passes.count;i++)
		if(!this.passes(i).BuildInScene(parent))
			return false;

	for(var i=0;i<this.actions.count;i++)
		if(!this.actions(i).BuildInScene(parent))
			return false;
			
	return true;
}

//=========================================
// Model Object
//=========================================
// This object is a representation of a referenced model

// Constructor
function XSIAModel(in_container)
{
	this.container = in_container;
	this.name = "";
	this.active_resolution = -1;
	this.scnPtr = null;
	this.resolutions = XSIFactory.CreateObject("XSI.Collection");
	this.deltas = XSIFactory.CreateObject("XSI.Collection");
	this.type = "XSIAModel";
}
XSIAModel.prototype.Clear = XSIAModel_Clear;
XSIAModel.prototype.SetFromScene = XSIAModel_SetFromScene;
XSIAModel.prototype.GetAsText = XSIAModel_GetAsText;
XSIAModel.prototype.SetFromTextStream = XSIAModel_SetFromTextStream;
XSIAModel.prototype.BuildInScene = XSIAModel_BuildInScene;
XSIAModel.prototype.Tabs = XSIATabs;
XSIAModel.prototype.CleanPath = XSIACleanPath;
XSIAModel.prototype.GetXmlToken = XSIAGetXmlToken;
XSIAModel.prototype.GetXmlClosed = XSIAGetXmlClosed;
XSIAModel.prototype.GetXmlAttribute = XSIAGetXmlAttribute;

// Clears the XSIAModel object
function XSIAModel_Clear()
{
	this.name = "";
	this.active_resolution = -1;
	this.scnPtr = null;
	
	for(var i=0;i<this.resolutions.count;i++)	
		this.resolutions(i).Clear();
	this.resolutions.RemoveAll();
	
	for(var i=0;i<this.deltas.count;i++)	
		this.deltas(i).Clear();
	this.deltas.RemoveAll();
	
	return true;
}

// Sets the model information from a scene model
function XSIAModel_SetFromScene(model)
{
	if(typeof model!='object')
	{
		logmessage("XSIAModel.PutFromScene: Invalid model.",siError);
		return false;
	}
	
	if(XSIUtils.DataRepository.GetIdentifier(model,siObjectCLSID)!="{0496EAB0-0ECF-11D1-ABF1-00A02485CECB}")
	{
		logmessage("XSIAModel.PutFromScene: Invalid model.",siError);
		return false;
	}
	
	this.scnPtr = model;
	this.name = model.name;
	
	//this has to be tried because the model might just be a local one (non-referenced)
	try{
		this.active_resolution = GetValue(this.scnPtr+".active_resolution")+'';
	}catch(e){
		this.active_resolution = 1;
	}
	
	// Get the number of resolutions
	var resCount = 0;
	for(var i=0;i<model.parameters.count;i++)
		if((model.parameters(i)+"").toLowerCase().indexOf('.resolutions.res')>-1)
			resCount++;

	// Add the info of all resolutions
	for(var i=0;i<resCount;i++)
	{
		var newResolution = new XSIAResolution(this);
		newResolution.SetFromScene(i);
		this.resolutions.Add(newResolution);	
	}

	// get all delta objects
	var sceneDeltas = XSIADeltas;
		
	for(var i=0;i<sceneDeltas.count;i++)
	{
		if(sceneDeltas(i).parent.fullname==model.fullname)
		{
			var newDelta = new XSIADelta(this);
			newDelta.SetFromScene(sceneDeltas(i));
			this.deltas.Add(newDelta);
		}
	}

	return true;
}

// returns the model description as a string (xml)
function XSIAModel_GetAsText(tabs)
{
	var xml = this.Tabs(tabs)+'<model name="';
	xml += this.name;
	xml += '" active_resolution="';
	xml += this.active_resolution;
	xml += '">\n';
	if(this.resolutions.count>0)
	{
		xml += this.Tabs(tabs+1)+'<resolutions>\n';
		for(var i=0;i<this.resolutions.count;i++)
		{
			xml += this.resolutions(i).GetAsText(tabs+2)+'\n';
		}
		xml += this.Tabs(tabs+1)+'</resolutions>\n';
	}
	if(this.deltas.count>0)
	{
		xml += this.Tabs(tabs+1)+'<deltas>\n';
		for(var i=0;i<this.deltas.count;i++)
		{
			xml += this.deltas(i).GetAsText(tabs+2)+'\n';
		}
		xml += this.Tabs(tabs+1)+'</deltas>\n';
	}
	
	// check if the model contains any fxtrees
	var trees = [];
	for(var i=0;i<XSIAFXTrees.count;i++)
	{
		var tree = XSIAFXTrees(i);
		if(tree.model+"" == this.name)
			trees[trees.length] = tree;
	}
	if(trees.length>0)
	{
		xml += this.Tabs(tabs+1)+'<fxtrees>\n';
		for(var i=0;i<trees.length;i++)
		{
			xml += this.Tabs(tabs+2)+'<fxtree fullname="'+trees[i]+'">\n';
			// now loop through all output nodes and write the ones below this fxtree
			for(var j=0;j<XSIAFXOutputs.count;j++)
			{
				var op = XSIAFXOutputs(j);
				var address = op.fullname.substr(0,tree.fullname.length);
				if(address == tree.fullname)
				{
					xml += this.Tabs(tabs+3)+'<fxtreeoutput fullname="'+op.fullname+'"></fxtreeoutput>\n';
				}
			}
			xml += this.Tabs(tabs+2)+'</fxtree>\n';
		}
		xml += this.Tabs(tabs+1)+'</fxtrees>\n';
	}

	xml += this.Tabs(tabs)+'</model>';
	return xml;
}

// reads the model information from a file stream
function XSIAModel_SetFromTextStream(file,line)
{
	if(this.GetXmlClosed(line))
		return true;
	var token = this.GetXmlToken(line);
	if(token!="model")
		return false;

	this.Clear();

	this.name = this.GetXmlAttribute(line,'name');
	this.active_resolution = this.GetXmlAttribute(line,'active_resolution');
	
	while(true)
	{
		try
		{
			line = file.ReadLine();
		}
		catch(e)
		{
			break;			
		}
		
		if(!line)
			continue;
		
		var token = this.GetXmlToken(line);
		
		if(token=="model")
		{
			break;
		}
		else if(token=="resolution")
		{
			var newResolution = new XSIAResolution(this);
			if(!newResolution.SetFromTextStream(file,line))
				return false;
			this.resolutions.Add(newResolution);
		}
		else if(token=="delta")
		{
			var newDelta = new XSIADelta(this);
			if(!newDelta.SetFromTextStream(file,line))
				return false;
			this.deltas.Add(newDelta);
		}
	}
	return true;
}

// builds the model in the scene
function XSIAModel_BuildInScene(parent)
{
	// the model has to have a name
	if(!this.name)
		return false;

	// there have to be enough resolutions to match the active_resolution at least
	if(this.resolutions.count-1<eval(this.active_resolution))
		return false;
	
	// let's create an empty ref model
	var model = ImportModel("",parent,true,"",this.name)(1);
	this.scnPtr = model;
	// remove the second resolution
	RemoveRefModelResolution(model, "res1", null);
	
	// Setup the name mapping template
	this.container.name_map[this.name] = model.name;
	this.name = model.name;

	// for all resolution except the offloaded one (first resolution)
	// generate the resolutions...
	for(var i=1;i<this.resolutions.count;i++)
	{
		if(!this.resolutions(i).BuildInScene(model))
			return false;
	}
	
	var fso = XSIFactory.CreateObject('Scripting.FileSystemObject');

	try{
		SetValue(model+".active_resolution", this.active_resolution);
	}catch(e){}

	// generate all the deltas
	for(var i=0;i<this.deltas.count;i++)
	{
		this.deltas(i).BuildInScene(model);
	}	
	
	return true;
}

//=========================================
// Resolution Object
//=========================================
// This object describes a model resolution

// Constructor
function XSIAResolution(in_container)
{
	this.container = in_container;
	this.name = "";
	this.filename = "";
	this.type = "XSIAResolution";
}
XSIAResolution.prototype.Clear = XSIAResolution_Clear;
XSIAResolution.prototype.SetFromScene = XSIAResolution_SetFromScene;
XSIAResolution.prototype.GetAsText = XSIAResolution_GetAsText;
XSIAResolution.prototype.SetFromTextStream = XSIAResolution_SetFromTextStream;
XSIAResolution.prototype.BuildInScene = XSIAResolution_BuildInScene;
XSIAResolution.prototype.Tabs = XSIATabs;
XSIAResolution.prototype.CleanPath = XSIACleanPath;
XSIAResolution.prototype.GetXmlToken = XSIAGetXmlToken;
XSIAResolution.prototype.GetXmlClosed = XSIAGetXmlClosed;
XSIAResolution.prototype.GetXmlAttribute = XSIAGetXmlAttribute;

// Clears / resets the object
function XSIAResolution_Clear()
{
	this.name = "";
	this.filename = "";
	return true;
}

// Sets the resolution description from a resolution in the scene
function XSIAResolution_SetFromScene(resolution_index)
{
	this.name = GetValue(this.container.scnPtr+".resolutions.res"+resolution_index+".name");
	this.filename = GetValue(this.container.scnPtr+".resolutions.res"+resolution_index+".file");
	if(this.filename)
		this.filename = XSIACleanPath(this.filename);
		
	return true;	
}

// Returns the description of the resolutions as a string (xml)
function XSIAResolution_GetAsText(tabs)
{
	var xml = this.Tabs(tabs);
	xml += '<resolution name="';
	if(this.name)
		xml += this.name;
	xml += '" filename="';
	if(this.filename)
		xml += this.CleanPath(this.filename);
	xml += '"></resolution>';
	return xml;
}

// reads the resolution information from a file stream
function XSIAResolution_SetFromTextStream(file,line)
{
	var token = this.GetXmlToken(line);
	if(token!="resolution")
		return false;

	this.name = this.GetXmlAttribute(line,'name');
	this.filename = this.GetXmlAttribute(line,'filename');
	
	return true;
}

// builds the resolution in the scene
function XSIAResolution_BuildInScene(parent)
{
	if(!this.name)
		return false;
		
	if(!this.filename)
		this.filename = "";
		
	AddRefModelResolution(parent, this.name, this.filename);
	
	return true;
}

//=========================================
// Delta Object
//=========================================
// This object describes a model delta.

// Constructor
function XSIADelta(in_container)
{
	this.container = in_container;
	this.name = "";
	this.scnPtr = null;
	this.target = "";
	this.persist_modif = "";
	this.storage = "";
	this.status = "";
	this.filename = "";
	this.type = "XSIADelta";
}
XSIADelta.prototype.Clear = XSIADelta_Clear;
XSIADelta.prototype.SetFromScene = XSIADelta_SetFromScene;
XSIADelta.prototype.GetAsText = XSIADelta_GetAsText;
XSIADelta.prototype.SetFromTextStream = XSIADelta_SetFromTextStream;
XSIADelta.prototype.BuildInScene = XSIADelta_BuildInScene;
XSIADelta.prototype.Tabs = XSIATabs;
XSIADelta.prototype.CleanPath = XSIACleanPath;
XSIADelta.prototype.GetXmlToken = XSIAGetXmlToken;
XSIADelta.prototype.GetXmlClosed = XSIAGetXmlClosed;
XSIADelta.prototype.GetXmlAttribute = XSIAGetXmlAttribute;

// Clears / resets the delta object
function XSIADelta_Clear()
{
	this.name = "";
	this.scnPtr = null;
	this.target = "";
	this.persist_modif = "";
	this.storage = "";
	this.status = "";
	this.filename = "";
	
	return true;
}

// Sets the delta description from a model_delta in the scene
function XSIADelta_SetFromScene(delta)
{
	if(typeof delta!='object')
	{
		logmessage("XSIADelta_SetFromScene : Incorrect delta.",siError);
		return false;
	}
	
	if(delta.type!='model_delta')
	{
		logmessage("XSIADelta_SetFromScene : Incorrect delta.",siError);
		return false;
	}

	this.target = GetValue(delta+".target");

	var deltaFileName = GetValue(delta+".filename");
	if(!deltaFileName)
		deltaFileName = ActiveProject.path+XSIUtils.Slash+"Deltas"+XSIUtils.Slash+delta.fullname.replace(/\./g,'_')+".delta";

	// check if it is a relativ path
	if ( XSIUtils.IsWindowsOS())
	{
		if(deltaFileName.substr(1,1)!=":"&&deltaFileName.substr(1,1)!=XSIUtils.Slash)
			deltaFileName = ActiveProject.path+XSIUtils.Slash+deltaFileName;
	}
	else
	{
		if(deltaFileName.substr(0,1)!=XSIUtils.Slash)
			deltaFileName = ActiveProject.path+XSIUtils.Slash+deltaFileName;
	}

	ExportDelta(delta+"",deltaFileName);

	this.scnPtr = delta;
	this.name = delta.name;
	this.persist_modif = GetValue(delta+".persist_modifications");
	this.storage = GetValue(delta+".storage");
	this.status = GetValue(delta+".status");
	this.filename = this.CleanPath(GetValue(delta+".filename"));
		
	return true;
}

// Returns the description of this model_delta as a string (xml)
function XSIADelta_GetAsText(tabs)
{
	var xml = this.Tabs(tabs);
	xml += '<delta name="';
	if(this.name)
		xml += this.name;
	xml += '" target="';
	if(this.target)
		xml += this.target;
	xml += '" persist_modif="';
	xml += this.persist_modif;
	xml += '" filename="';
	if(this.filename)
		xml += this.filename;
	xml += '" status="';
	xml += this.status;
	xml += '"></delta>';
	return xml;
}

// reads the delta description from a xml text stream
function XSIADelta_SetFromTextStream(file,line)
{
	var token = this.GetXmlToken(line);
	if(token!="delta")
		return false;

	this.name = this.GetXmlAttribute(line,'name');
	this.target = this.GetXmlAttribute(line,'target');
	this.persist_modif = this.GetXmlAttribute(line,'persist_modif');
	this.filename = this.GetXmlAttribute(line,'filename');
	this.status = this.GetXmlAttribute(line,'status');

	return true;
}

// builds the delta in the scene below the model parent
function XSIADelta_BuildInScene(parent)
{
	if(!this.name)
		return false;

	if(!this.filename)
		return false;
		
	var fso = XSIFactory.CreateObject('Scripting.FileSystemObject');

	// check for file existence first
	if(!fso.FileExists(this.filename))
	{
		var project = ActiveProject.ActiveScene.parameters("filename").value;
		project = project.replace(/\\/g,"/");
		project = project.substr(0,project.lastIndexOf('/'));
		project = project.substr(0,project.lastIndexOf('/')+1);

		if(fso.FileExists(project+this.filename))
			this.filename = project + this.filename;
		else
		{			
			logmessage("XSIA_Delta_Build: File does not exist!",siError);
			return false;
		}
	}
	
	var delta = ImportDelta(this.filename, parent,true,false);
	if(delta.name!=this.name)
		SetValue(delta+".Name", this.name);
	this.name = delta.name;
	
	if(this.filename.substr(this.filename.length-5,5).toLowerCase()!="delta")
		SetValue(delta+".Storage", 4);

	this.scnPtr = delta;
	
	// remap the target based on the new name of the models in the scene
	if(this.container.container.name_map[this.target])
		SetValue(delta+".target", this.container.container.name_map[this.target]);
	else
		SetValue(delta+".target", this.target);
		
	SetValue(delta+".persist_modifications", this.persist_modif);
	SetValue(delta+".status", this.status);	
	
	// Apply the delta
	ApplyDelta(delta);

	return true;
}

//=========================================
// Group Object
//=========================================
// This object represents a group, layer or partition

// Constructor
function XSIAGroup(in_container)
{
	this.container = in_container;
	this.name = "";
	this.scnPtr = null;
	this.filename = "";
	this.members = XSIFactory.CreateObject("XSI.Collection");
	this.groupType = "";
	this.type = "XSIAGroup";
}
XSIAGroup.prototype.Clear = XSIAGroup_Clear;
XSIAGroup.prototype.SetFromScene = XSIAGroup_SetFromScene;
XSIAGroup.prototype.GetAsText = XSIAGroup_GetAsText;
XSIAGroup.prototype.SetFromTextStream = XSIAGroup_SetFromTextStream;
XSIAGroup.prototype.BuildInScene = XSIAGroup_BuildInScene;
XSIAGroup.prototype.Tabs = XSIATabs;
XSIAGroup.prototype.CleanPath = XSIACleanPath;
XSIAGroup.prototype.GetXmlToken = XSIAGetXmlToken;
XSIAGroup.prototype.GetXmlClosed = XSIAGetXmlClosed;
XSIAGroup.prototype.GetXmlAttribute = XSIAGetXmlAttribute;

// Clears / resets the group objects
function XSIAGroup_Clear()
{
	this.name = "";
	this.scnPtr = null;
	this.filename = "";
	this.groupType = "";
	if(typeof this.members != 'object')
		this.members = null;
	else
		this.members.RemoveAll();
}

// Sets the group descriptions from a group in the scene
function XSIAGroup_SetFromScene(group)
{
	if(typeof group!='object')
	{
		logmessage('XSIAGroup_SetFromScene: Incorrect group!',siError);
		return false;
	}
	
	this.name = group.name;
	this.members.AddItems(group.members);
	this.scnPtr = group;

	return true;	
}

// returns the description of the group as a string (xml)
function XSIAGroup_GetAsText(tabs,title)
{
	if(!title)
		title="group";
		
	var xml = this.Tabs(tabs)+'<'+title+' name="';
	if(this.name)
		xml += this.name;
	if(this.filename)
		xml += '" filename="'+this.filename;
	xml += '" members="';
	if(this.members.count>0)
		xml += this.members.GetAsText();
	xml += '"></'+title+'>';
	
	return xml;
}

// sets the attributes of a group from a textstream
function XSIAGroup_SetFromTextStream(file,line)
{
	var token = this.GetXmlToken(line);
	if((token!="group")&&(token!="layer")&&(token!="partition"))
		return false;
	
	this.groupType = token.toLowerCase();
	this.name = this.GetXmlAttribute(line,'name');
	this.filename = this.GetXmlAttribute(line,'filename');
	this.members = this.GetXmlAttribute(line,'members');
	
	return true;
}

// builds the group in the scene
function XSIAGroup_BuildInScene(parent)
{
	if(!this.name)
		return false;
		
	this.members = XSIACheckMembers(this.members);
		
	if(this.groupType=='group')
	{
		DeselectAll();
		try
		{
			this.scnPtr = Dictionary.GetObject(parent+"."+this.name);
		}
		catch(e)
		{
			this.scnPtr = parent.AddGroup();
			this.scnPtr.name = this.name;
			this.name = this.scnPtr.name;
		}
		if(this.members)
		{
			// Do the remapping based on the new names of the imported models
			for(var key in this.container.name_map)
			{
				this.members = this.members.replace(new RegExp("^"+key+"\\.","gi"),this.container.name_map[key]+".");
				this.members = this.members.replace(new RegExp(","+key+"\\.","gi"),this.container.name_map[key]+".");
			}
			SIAddToGroup(this.scnPtr,this.members);
		}
	}
	else if(this.groupType=='layer')
	{
		var currentLayer = ActiveProject.ActiveScene.ActiveLayer.FullName;
		DeselectAll();
		try
		{
			this.scnPtr = Dictionary.GetObject('Layers.'+this.name);
		}
		catch(e)
		{
			this.scnPtr = CreateLayer(this.filename?this.filename:null,this.name)(0);
			this.name = this.scnPtr.name;
		}
		if(this.members)
		{
			// Do the remapping based on the new names of the imported models
			for(var key in this.container.name_map)
			{
				this.members = this.members.replace(new RegExp("^"+key+"\\.","gi"),this.container.name_map[key]+".");
				this.members = this.members.replace(new RegExp(","+key+"\\.","gi"),this.container.name_map[key]+".");
			}
			MoveToLayer(this.scnPtr,this.members);
		}
		SetCurrentLayer(currentLayer);
	}
	else if(this.groupType=='partition')
	{
		DeselectAll();
		
		try
		{
			this.scnPtr = Dictionary.GetObject(parent+'.'+this.name);
		}
		catch(e)
		{
			this.scnPtr = CreatePartition(null,this.name)(0);
			this.name = this.scnPtr.name;
		}
		if(this.members)
		{
			var currentMembers = XSIFactory.CreateObject('XSI.Collection');
			currentMembers.AddItems(this.scnPtr.members);
			if(currentMembers.GetAsText().toLowerCase()!=this.members.toLowerCase())
				try
				{
					MoveToPartition(this.scnPtr,this.members);
				}
				catch(e){}
		}
	}
	else
	{
		return false;
	}
	return true;
}

//=========================================
// Pass Object
//=========================================
// This object represents the description of a pass

// Constructor
function XSIAPass(in_container)
{
	this.container = in_container;
	this.name = "";
	this.scnPtr = null;
	this.filename = "";
	this.partitions = XSIFactory.CreateObject("XSI.Collection");
	this.type = "XSIAPass";
}
XSIAPass.prototype.Clear = XSIAPass_Clear;
XSIAPass.prototype.SetFromScene = XSIAPass_SetFromScene;
XSIAPass.prototype.GetAsText = XSIAPass_GetAsText;
XSIAPass.prototype.SetFromTextStream = XSIAPass_SetFromTextStream;
XSIAPass.prototype.BuildInScene = XSIAPass_BuildInScene;
XSIAPass.prototype.Tabs = XSIATabs;
XSIAPass.prototype.CleanPath = XSIACleanPath;
XSIAPass.prototype.GetXmlToken = XSIAGetXmlToken;
XSIAPass.prototype.GetXmlClosed = XSIAGetXmlClosed;
XSIAPass.prototype.GetXmlAttribute = XSIAGetXmlAttribute;

// Clears / resets the pass object
function XSIAPass_Clear()
{
	this.name = "";
	this.scnPtr = null;
	this.filename = "";
	
	for(var i=0;i<this.partitions.count;i++)
		this.partitions(i).Clear();
	this.partitions.RemoveAll();
}

// Sets the pass description from a pass in the scene
function XSIAPass_SetFromScene(pass)
{
	if(typeof pass!='object')
	{
		logmessage('XSIAPass_SetFromScene: Incorrect pass!',siError);
		return false;
	}
	
	if(pass.type!='Pass')
	{
		logmessage('XSIAPass_SetFromScene: Incorrect pass!',siError);
		return false;
	}

	this.name = pass.name;
	this.scnPtr = pass;
	this.filename = '';

	for(var i=0;i<XSIAPartitions.count;i++)
	{
		if(XSIAPartitions(i).parent.fullname == pass.fullname)
		{
			var newPartition = new XSIAGroup(this);
			newPartition.SetFromScene(XSIAPartitions(i));
			this.partitions.Add(newPartition);
		}
	}
	
	return true;
}


// Returns the pass description as a string (xml)
function XSIAPass_GetAsText(tabs)
{
	var xml = this.Tabs(tabs)+'<pass name="';
	if(this.name)
		xml += this.name;
	xml += '" filename="';
	if(this.filename)
		xml += this.filename;
	xml += '">\n';

	xml += this.Tabs(tabs+1)+'<partitions>\n';	
	for(var i=0;i<this.partitions.count;i++)
	{
		xml += this.partitions(i).GetAsText(tabs+2,'partition')+'\n';
	}
	xml += this.Tabs(tabs+1)+'</partitions>\n';	
	
	xml += this.Tabs(tabs)+'</pass>';
	
	return xml;
}

// sets the attributes of a pass from a textstream
function XSIAPass_SetFromTextStream(file,line)
{
	if(this.GetXmlClosed(line))
		return true;
	var token = this.GetXmlToken(line);
	if(token!="pass")
		return false;

	this.Clear();

	this.name = this.GetXmlAttribute(line,'name');
	this.filename = this.GetXmlAttribute(line,'filename');
	
	while(true)
	{
		try
		{
			line = file.ReadLine();
		}
		catch(e)
		{
			break;			
		}
		
		if(!line)
			continue;
		
		var token = this.GetXmlToken(line);
		
		if(token=="pass")
		{
			break;
		}
		else if(token=="partition")
		{
			var newPartition = new XSIAGroup(this);
			if(!newPartition.SetFromTextStream(file,line))
				return false;
			this.partitions.Add(newPartition);
		}
	}
	return true;
}

// builds the path in the scene from its xml description
function XSIAPass_BuildInScene(parent)
{
	if(!this.name)
		return false;
		
	try
	{
		this.scnPtr = CreatePass(this.filename?this.filename:null)(0);
	}
	catch(e)
	{
		logmessage("XSIAPass: BuildInScene: File corrupt/doesn't exist!",siError);
		return false;
	}
	
	this.scnPtr.name = this.name;
	this.name = this.scnPtr.name;
	
	for(var i=0;i<this.partitions.count;i++)
	{
		if(!this.partitions(i).BuildInScene(this.scnPtr))
			return false;
	}
	
	return true;
}

//=========================================
// Action Object
//=========================================
// This object describes an actionDelta.

// Constructor
function XSIAAction(in_container)
{
	this.container = in_container;
	this.scnPtr = null;
	this.type = "XSIAAction";
	this.actionType = "";
	this.items = new ActiveXObject("XSI.Collection");
}
XSIAAction.prototype.Clear = XSIAAction_Clear;
XSIAAction.prototype.SetFromScene = XSIAAction_SetFromScene;
XSIAAction.prototype.GetAsText = XSIAAction_GetAsText;
XSIAAction.prototype.SetFromTextStream = XSIAAction_SetFromTextStream;
XSIAAction.prototype.BuildInScene = XSIAAction_BuildInScene;
XSIAAction.prototype.Tabs = XSIATabs;
XSIAAction.prototype.CleanPath = XSIACleanPath;
XSIAAction.prototype.GetXmlToken = XSIAGetXmlToken;
XSIAAction.prototype.GetXmlClosed = XSIAGetXmlClosed;
XSIAAction.prototype.GetXmlAttribute = XSIAGetXmlAttribute;

// Clears / resets the actiondelta object
function XSIAAction_Clear()
{
	this.scnPtr = null;
	this.actionType = "";
	
	for(var i=0;i<this.items.count;i++)
		this.items(i).Clear();
	this.items.RemoveAll();
	
	return true;
}

// Sets the actiondelta description from a actiondelta in the scene
function XSIAAction_SetFromScene(actionDelta)
{
	if(typeof actionDelta!='object')
	{
		logmessage("XSIAAction_SetFromScene : Incorrect action.",siError);
		return false;
	}
	
	this.scnPtr = actionDelta;
	this.actionType = actionDelta.type;
	
	for(var i=0;i<actionDelta.items.count;i++)
	{
		var newActionItem = new XSIAActionItem(this);
		newActionItem.SetFromScene(actionDelta.items(i));
		this.items.Add(newActionItem);
	}
		
	return true;
}

// Returns the description of this actionDelta as a string (xml)
function XSIAAction_GetAsText(tabs)
{
	var xml = this.Tabs(tabs);
	xml += '<action actionType="';
	if(this.actionType)
		xml += this.actionType;
	xml += '">\n';
	if(this.items.count>0)
	{
		xml += this.Tabs(tabs+1)+'<items>\n';	
		for(var i=0;i<this.items.count;i++)
			xml += this.items(i).GetAsText(tabs+2)+'\n';	
		xml += this.Tabs(tabs+1)+'</items>\n';	
	}
	xml += this.Tabs(tabs)+"</action>";

	return xml;
}

// reads the actiondelta description from a xml text stream
function XSIAAction_SetFromTextStream(file,line)
{
	var token = this.GetXmlToken(line);
	if(token!="action")
		return false;

	this.actionType = this.GetXmlAttribute(line,'actionType');

	while(true)
	{
		try
		{
			line = file.ReadLine();
		}
		catch(e)
		{
			break;			
		}
		
		if(!line)
			continue;
		
		var token = this.GetXmlToken(line);
		
		if(token=="action")
		{
			break;
		}
		else if(token=="actionitem")
		{
			var newItem = new XSIAActionItem(this);
			if(!newItem.SetFromTextStream(file,line))
				return false;
			this.items.Add(newItem);
		}
	}
	
	return true;
}

// builds the actiondelta in the scene below the delta parent
function XSIAAction_BuildInScene(parent)
{
	if(!this.actionType)
		return false;

	var actionDelta = parent.AddAction(eval(this.actionType));	
	
	this.model = parent.model;
	this.scnPtr = actionDelta;
	
	for(var i=0;i<this.items.count;i++)
		this.items(i).BuildInScene(this);
	
	return true;
}

//=========================================
// ActionItem Object
//=========================================
// This object describes an actionDeltaItem.

// Constructor
function XSIAActionItem(in_container)
{
	this.container = in_container;
	this.scnPtr = null;
	this.type = "XSIAActionItem";
	this.target = "";
	this.value = "";
}
XSIAActionItem.prototype.Clear = XSIAActionItem_Clear;
XSIAActionItem.prototype.SetFromScene = XSIAActionItem_SetFromScene;
XSIAActionItem.prototype.GetAsText = XSIAActionItem_GetAsText;
XSIAActionItem.prototype.SetFromTextStream = XSIAActionItem_SetFromTextStream;
XSIAActionItem.prototype.BuildInScene = XSIAActionItem_BuildInScene;
XSIAActionItem.prototype.Tabs = XSIATabs;
XSIAActionItem.prototype.CleanPath = XSIACleanPath;
XSIAActionItem.prototype.GetXmlToken = XSIAGetXmlToken;
XSIAActionItem.prototype.GetXmlClosed = XSIAGetXmlClosed;
XSIAActionItem.prototype.GetXmlAttribute = XSIAGetXmlAttribute;

// Clears / resets the actiondeltaitem object
function XSIAActionItem_Clear()
{
	this.scnPtr = null;
	this.target = "";
	this.value = "";
	
	return true;
}

// Sets the actiondeltaitem description from a actiondeltaitem in the scene
function XSIAActionItem_SetFromScene(actionDeltaItem)
{
	if(typeof actionDeltaItem!='object')
	{
		logmessage("XSIAActionItem_SetFromScene : Incorrect action.",siError);
		return false;
	}
	
	this.scnPtr = actionDeltaItem;
	
	this.target = actionDeltaItem.name;
	
	// static values
	if(actionDeltaItem.type=="siModificationDeltaStaticValue")
	{
		this.value = actionDeltaItem.value+"";
	}
	// fcurves
	else if(actionDeltaItem.type=="siModificationDeltaFCurve")
	{
		var arr = [];
		var keys = actionDeltaItem.value.keys;
		for(var i=0;i<keys.count;i++)
		{
			arr[arr.length] = keys(i).time;
			arr[arr.length] = keys(i).value;
			arr[arr.length] = keys(i).leftTanX;
			arr[arr.length] = keys(i).leftTanY;
			arr[arr.length] = keys(i).rightTanX;
			arr[arr.length] = keys(i).rightTanY;
		}
		this.value = arr.join("|");
	}
	// expressions
	else if(actionDeltaItem.type=="siModificationDeltaExpression")
	{
		this.value = actionDeltaItem.value+"";
		this.value = this.value.split(" = ")[1];
	}
		
	return true;
}

// Returns the description of this actiondeltaitem as a string (xml)
function XSIAActionItem_GetAsText(tabs)
{
	var xml = this.Tabs(tabs);
	xml += '<actionItem target="';
	if(this.target)
		xml += this.target;
	xml += '" value="';
	if(this.value)
		xml += this.value;
	xml += '"></actionItem>';

	return xml;
}

// reads the actiondeltaitem description from a xml text stream
function XSIAActionItem_SetFromTextStream(file,line)
{
	var token = this.GetXmlToken(line);
	if(token!="actionitem")
		return false;

	this.target = this.GetXmlAttribute(line,'target');
	this.value = this.GetXmlAttribute(line,'value');

	return true;
}

// builds the actiondeltaitem in the scene below the actiondelta
function XSIAActionItem_BuildInScene(parent)
{
	if(parent.actionType=="siModificationDeltaStaticValue")
	{
		SetValue(parent.model + "." + this.target,this.value);
	}
	else if(parent.actionType=="siModificationDeltaFCurve")
	{
		var param = Dictionary.GetObject(parent.model + "." + this.target);
		var arr = this.value.split("|");
		for(var i=0;i<arr.length;i+=6)
			SaveKey(param,eval(arr[i]),eval(arr[i+1]));
	}
	else if(parent.actionType=="siModificationDeltaExpression")
	{
		SetExpr(parent.model + "." + this.target,this.value);
	}
	
	
	
	return true;
}

//=========================================
// MatLib Object
//=========================================
// This object describes a MaterialLibrary.

// Constructor
function XSIAMatLib(in_container)
{
	this.container = in_container;
	this.scnPtr = null;
	this.type = "XSIAMatLib";
	this.name = "";
	this.filename = "";
}
XSIAMatLib.prototype.Clear = XSIAMatLib_Clear;
XSIAMatLib.prototype.SetFromScene = XSIAMatLib_SetFromScene;
XSIAMatLib.prototype.GetAsText = XSIAMatLib_GetAsText;
XSIAMatLib.prototype.SetFromTextStream = XSIAMatLib_SetFromTextStream;
XSIAMatLib.prototype.BuildInScene = XSIAMatLib_BuildInScene;
XSIAMatLib.prototype.Tabs = XSIATabs;
XSIAMatLib.prototype.CleanPath = XSIACleanPath;
XSIAMatLib.prototype.GetXmlToken = XSIAGetXmlToken;
XSIAMatLib.prototype.GetXmlClosed = XSIAGetXmlClosed;
XSIAMatLib.prototype.GetXmlAttribute = XSIAGetXmlAttribute;

// Clears / resets the MatLib object
function XSIAMatLib_Clear()
{
	this.scnPtr = null;
	this.filename = "";
	this.name = "";
	
	return true;
}

// Sets the matlib description from a matlib in the scene
function XSIAMatLib_SetFromScene(matlib)
{
	
	if(typeof matlib!='object')
	{
		logmessage("XSIAMatLib_SetFromScene : Incorrect matlib.",siError);
		return false;
	}
	
	this.scnPtr = matlib;
	this.name = matlib.name;
	this.filename = matlib.filename.value;
		
	return true;
}

// Returns the description of this matlib as a string (xml)
function XSIAMatLib_GetAsText(tabs)
{
	var xml = this.Tabs(tabs);
	xml += '<matlib name="';
	if(this.name)
		xml += this.name;
	xml += '" filename="';
	if(this.filename)
		xml += this.filename;
	xml += '"></matlib>';

	return xml;
}

// reads the matlib description from a xml text stream
function XSIAMatLib_SetFromTextStream(file,line)
{
	var token = this.GetXmlToken(line);
	if(token!="matlib")
		return false;

	this.name = this.GetXmlAttribute(line,'name');
	this.filename = this.GetXmlAttribute(line,'filename');

	return true;
}

// builds the matlib in the scene below the scene parent
function XSIAMatLib_BuildInScene(parent)
{
	if(!this.filename)
		return false;

	var fso = new ActiveXObject("Scripting.FileSystemObject");
	
	if(!fso.FileExists(this.filename))
	{
		var project = ActiveProject.ActiveScene.parameters("filename").value;
		project = project.replace(/\\/g,"/");
		project = project.substr(0,project.lastIndexOf('/'));
		project = project.substr(0,project.lastIndexOf('/')+1);
		this.filename = project + this.filename;
	}
	
	var matlib = SIImportMatLib(this.filename, 0, null)(1);
	matlib.name = this.name;
	matlib.storage.value = 1;
	matlib.filename.value = this.filename;

	this.scnPtr = matlib;
	
	return true;
}

//=========================================
// General Functions
//=========================================

// Returns a string composed of "tab" characters for the xml tabbing
function XSIATabs(tabs)
{
	var xml = "";
	for(var i=0;i<tabs;i++)
		xml += "\t";
	return xml;
}

// returns a clean path with legal characters only
function XSIACleanPath(path)
{
	return XSIUtils.ResolvePath(path);
}

// gets the token of a xml string
function XSIAGetXmlToken(text)
{
	var r = new RegExp("<\/*[ ]*([a-z]*)", "i");/**/
	var match = r.exec(text);
	return match?match[1].toLowerCase():false;
}

// returns true if the text is a closing xml token
function XSIAGetXmlClosed(text)
{
	var r = new RegExp("(^<\/|\t<\/)", "i");
	var match = r.exec(text);
	return match?true:false;
}

// returns the value of an attribute in a xml text
function XSIAGetXmlAttribute(text,attribute)
{
	var r = new RegExp(attribute+'=\\"([^"]*)\\"','i');
	var match=r.exec(text);
	return match?match[1]:false;
}

// loops through a memberstring and removes non existent items
function XSIACheckMembers(members){
	var mems = members.split(',');
	var newMembers = new Array();
	for(var i=0;i<mems.length;i++){
		try{
			var obj = Dictionary.GetObject(mems[i]);
			newMembers[newMembers.length] = mems[i];
		}catch(e){}
	}
	return newMembers.join();
}
//======================

