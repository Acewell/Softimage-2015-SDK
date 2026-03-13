// InstallInternationalPSetUIDict.js
//
// This example shows how to compile and deploy a translation dictionary.
// It implements two custom commands to install and uninstall the specified translation dictionary.
// - InstallXSIUIDict[ in_dictxmlFileName ] : Compile and deploy a translation dictionary.
// - UninstallXSIUIDict[ in_dictName ] : Uninstall a translation dictionary.
// Note: 
// 1. The file name of this plugin has "_" prefix in order to make sure this plugin is loaded and
// the translation dictionary is compiled and deployed(See XSILoadPlugin function) before loading other plugins
// in the same directory. In the real practice, think about your approach to recompile and deploy the dictionary.
// 2. The translation dictionary must be deployed into [factory]\Application\Dictionary\[languageFolder]. 

//	Copyright 2013 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.  
//  
function XSILoadPlugin( in_reg )
{
	// register plugin information
	in_reg.Author = "Autodesk, Inc.";
	in_reg.Name = "InstallInternationPSetUIDict";

	// var the version number of this plugin
	in_reg.Major = 1;
	in_reg.Minor = 0 ;

	in_reg.RegisterCommand("InstallXSIUIDict", "InstallXSIUIDict");
	in_reg.RegisterCommand("UninstallXSIUIDict", "UninstallXSIUIDict");

	// Compile and install the .dict file into installed directory.
	var fso = XSIFactory.CreateActiveXObject("Scripting.FileSystemObject");
	var dictInputFile = XSIUtils.BuildPath(fso.GetParentFolderName(in_reg.FileName), "InternationalPSetUIDemo.dictxml");
	InstallDictFile(dictInputFile);

	//RegistrationInsertionPoint - do not remove this line
}

function XSIUnloadPlugin(in_reg)
{
	return true;
}

//
// Help function to compile the specified .dictxml file into a translation dictionary
//
function InstallDictFile( in_FileName ) {

	var fso = XSIFactory.CreateActiveXObject("Scripting.FileSystemObject");
	if (!fso.FileExists(in_FileName)) {
		LogMessage("Please specify a .dictxml to parse", siError)
	}
	else {
		// xsiDictParser.pl is used to compile the dictxml file into a translation dictionary. 
		// Run "xsiDictParser.pl -help" in Softimage command prompt to see the usage documentation.
		var parserFile = XSIUtils.BuildPath(Application.InstallationPath(siFactoryPath), "Application", "bin", "xsiDictParser.pl");

		// The translation dictionary must be deployed into [factory]\Application\Dictionary\[languageFolder]
		// Note: It's required the write permission the factory directory.
		var dictOutDir = XSIUtils.BuildPath(Application.InstallationPath(siFactoryPath), "Application", "Dictionary");

		var cmd = "perl  \"" + parserFile + "\" -dictdir  \"" + dictOutDir + "\" " + " -inputfile \"" + in_FileName;
		LogMessage("This command line will be executed:\n" + cmd, siVerbose);

		// Specify true for the blocking argument so that our script waits until compilation
		// has finished before trying to read the output file
		XSIUtils.LaunchProcess(cmd, true);

		// Verify the output
		var dictName = fso.GetBaseName(in_FileName);
		var dictEnFile = XSIUtils.BuildPath(dictOutDir, "en", dictName + ".dict");
		if (!fso.FileExists(dictEnFile))
			LogMessage("Failed to comple the translation dictionary\"" + dictEnFile + "\"", siError);

		var dictJPFile = XSIUtils.BuildPath(dictOutDir, "jp", dictName + ".dict");
		if (!fso.FileExists(dictJPFile))
			LogMessage("Failed to comple the translation dictionary\"" + dictJPFile + "\"", siError);

	}
}

//
// Help function to remove a translation dictionary away from factory folders.
//
function UninstallDictFile( in_DictName ) {
	if (in_DictName == "")
		LogMessage("Please specify a translation dictionary( without the .dict extension) to uninstall", siError);
	else {
		// Remove the dict files specified.
		var dictOutDir = XSIUtils.BuildPath(Application.InstallationPath(siFactoryPath), "Application", "Dictionary");
		var dictEnFile = XSIUtils.BuildPath(dictOutDir, "en", in_DictName + ".dict");
		var dictJPFile = XSIUtils.BuildPath(dictOutDir, "jp", in_DictName + ".dict");
		try {
			var fso = XSIFactory.CreateActiveXObject("Scripting.FileSystemObject");

			fso.DeleteFile(dictEnFile);
			if (fso.FileExists(dictEnFile))
				LogMessage("Failed to delete\"" + dictEnFile + "\"", siError);

			fso.DeleteFile(dictJPFile);
			if (fso.FileExists(dictJPFile))
				LogMessage("Failed to delete\"" + dictJPFile + "\"", siError);
		}
		catch (e) {
			LogMessage("Exception while deleting the" + in_DictName + " translation dictionary: " + e.Description, siError)
		}
	}
}

//
// Custom command to compile and install a translation dictionary.
// parameters:
// string | FileName | Specify the file full name of .dictxml resource file that would be compiled.
//
function InstallXSIUIDict_Init(in_ctxt)
{
	var oCmd;
	oCmd = in_ctxt.Source;
	oCmd.Description = "";
	oCmd.Tooltip = "Compile and install a translation dictionary";
	oCmd.SetFlag(siSupportsKeyAssignment,false);
	oCmd.ReturnValue = true;

	var oArgs;
	oArgs = oCmd.Arguments;
	oArgs.Add("FileName", siArgumentInput, "");
	return true;
}

function InstallXSIUIDict_Execute(in_FileName)
{
	InstallDictFile(in_FileName);

	return true;
}

//
// Custom command to uninstall a translation dictionary.
// parameters:
// string | DictName | Specify a name of the translation dictionary without .dict extension.
//
function UninstallXSIUIDict_Init(in_ctxt)
{
	var oCmd;
	oCmd = in_ctxt.Source;
	oCmd.Description = "";
	oCmd.Tooltip = "Uninstall a translation dictionary";
	oCmd.SetFlag(siSupportsKeyAssignment, false);
	oCmd.ReturnValue = true;

	var oArgs;
	oArgs = oCmd.Arguments;
	oArgs.Add("DictName", siArgumentInput, "");
	return true;
}

function UninstallXSIUIDict_Execute( DictName )
{
	UninstallDictFile(DictName);
	return true;
}

