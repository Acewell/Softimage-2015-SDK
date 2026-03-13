//*****************************************************************************
/*!
   \file xsi_application.h
   \brief Application class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIAPPLICATION_H__
#define __XSIAPPLICATION_H__

#include <xsi_siobject.h>
#include <xsi_value.h>
#include <xsi_status.h>

namespace XSI {

class Selection;
class Dictionary;
class Command;
class CommandArray;
class Project;
class Model;
class Preferences;
class Desktop;
class UIToolkit;
class Plugin;
class UIToolkit;
class Factory;
class ProjectItem;
class ShaderDef;

//*****************************************************************************
/*! \class Application xsi_application.h
	\brief The %Application object represents the running instance of the Softimage application
	and it is the top most entity of the C++ API object hierarchy. %Application contains properties
	that return other Softimage objects such as the active scene root.

	\sa \xm CustomUITest/netview_CustomUITest Custom UI Test \endxm

	Unlike most other C++ API objects, it is not necessary to intialize this object based on a CRef(),
	as soon as you create this object is it ready for use, as shown in the example below.

	\eg Using the Application class
	\code
		using namespace XSI;
		Application app;
		Model root = app.GetActiveSceneRoot();

		CameraRig myCamRig;
		root.AddCameraRig( L"Camera", L"", myCamRig );

		Camera myCam(myCamRig.GetCamera());
		X3DObject myCamInterest(myCam.GetInterest());

		CString strCamName( myCam.GetName() );
		app.LogMessage( L"Camera interest" );
		app.LogMessage( strCamName + L".interest.name: " + myCam.GetInterest().GetName() );

		app.LogMessage( strCamName + L"'s near parameter: " + myCam.GetParameterValue(CString(L"near")).GetAsText() );
		app.LogMessage( strCamName + L"'s far parameter: " +  myCam.GetParameterValue(CString(L"far")).GetAsText() );
		app.LogMessage( strCamName + L"'s orthoheight parameter: " + myCam.GetParameterValue(CString(L"orthoheight")).GetAsText() );
		app.LogMessage( strCamName + L"'s fov parameter: " + myCam.GetParameterValue(CString(L"fov")).GetAsText() );
	\endcode

 */
//*****************************************************************************

class SICPPSDKDECL Application : public SIObject
{
public:
	/*! Default constructor.*/
	Application();

	/*! Default destructor. */
	~Application(){}

	/*! Constructor.  It is not normally necessary to use this version of the constructor,
	because the default constructor also produces an initialized %Application object.
	\param in_ref constant reference object.
	*/
	Application(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	Application(const Application& in_obj);

	/*! Returns true if a given class type is compatible with this API class.
	\param in_ClassID class type.
	\return True if the class is compatible, false otherwise.
	*/
	bool IsA( siClassID in_ClassID) const;

	/*! Returns the type of the API class.
	\return The class type.
	*/
	siClassID GetClassID() const;

	/*! Creates an object from another object. The newly created object is set to
	empty if the input object is not compatible.
	\param in_obj constant class object.
	\return The new Application object.
	*/
	Application& operator=(const Application& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The New Application object.
	*/
	Application& operator=(const CRef& in_ref);

	/*! Returns the Selection object holding the selected objects represented as CRef objects.
	\return Selection object.
	*/
	Selection GetSelection() const;

	/*! Returns a list of FCurve objects with selected keys represented as CRef objects.
	\return Array of references to FCurve objects.
	\since 6.0
	*/
	CRefArray GetFCurveSelection() const;

	/*! Not-implemented.
	\note CRef::Set is the C++ API equivalent of the \xl %Dictionary.GetObject method.
	*/
	Dictionary GetDictionary() const;

	/*! Returns the active Project.
	\return The active project.
	*/
	Project GetActiveProject() const;

	/*! Sets the active Project.
	\param in_Project The path of the project to set.
	\since 5.0
	\return CStatus::OK Success.
	\return CStatus::Fail Failure.
	*/
	CStatus PutActiveProject(const CString& in_Project) const;

	/*! Returns the root model of the active scene of the active project.
	\return The active scene model.
	*/
	Model GetActiveSceneRoot() const;

	/*! Returns an installation path.  The returned paths end with a slash character.
	\param in_pathType Installation path type (one of the ::siInstallationPath values).
	\return The installation path.
	\since 4.0
	*/
	CString GetInstallationPath( siInstallationPath in_pathType ) const;

	/*! Returns the version number of the application (eg, \c 6.5.170.QFE1 or \c XSI_Pioneer_Beta1.234-4.0).
	As of v7.0, the format of the version information is:<br><br>
	\c {ReleaseNumber}.{BuildNumber}.{UpdateNumber}
	<br><br>...where the chunks represent this information:
	\li \c {ReleaseNumber} which can contain alphanumeric characters, as well as decimal points (\c .)<br>
		For released products, this contains \c Major.Minor designation (eg., \c 6.5). <br>
		For pre-release versions, this may be the \c CodeNameMileStone (eg., \c XSI_Pioneer_Beta1).
	\li \c {BuildNumber} which can also contain alphanumeric characters, but cannot contain decimal points (eg., \c 234 or \c 234-4).
	\li \c {UpdateNumber} which can also contain alphanumeric characters, but cannot contain decimal points (eg., \c 1 or \c QFE1).

	Prior to v7.0, the format of the version information is: \c Major.Minor.YYYY.MMDD (eg., \c 6.02.2007.0605).
	\return The version number.
	\since 4.0
	*/
	CString	GetVersion() const;

	/*! Returns the type of license used.
	\return Advanced
	\return Essential
	\return Foundation
	\return Experience
	\since 4.0
	*/
	CString	GetLicense() const;

	/*! Installs an .xsiaddon file in Softimage. An add-on file is a set of customized items (like layout, toolbar, preset, etc.)
	that are packaged in a single file.

	\param in_strFileName File path of the add-on file to install.
	\param in_eInstallDir Destination directory, where the add-on is installed. ::siUserAddonPath and ::siWorkgroupAddonPath are the
		recommended values. If ::siUnknownPath is specified then the add-on will be installed at the default location specified inside
		the add-on file.
		<br><b><i>Note:</i></b> In the case of multiple workgroups, this always installs to the first workgroup in the list.

	\param in_bNoUI Use this optional parameter to avoid displaying the warning message boxes that are shown during the
		installation of certain addons.

	\return CStatus::Ok Success
	\return CStatus::Fail Installation failure
	\since 7.5
	*/
	CStatus InstallAddon( const CString& in_strFileName, siInstallationPath in_eInstallDir, bool in_bNoUI=false );

	/*! Uninstalls an .xsiaddon file from Softimage. This deletes all items that were previously installed by the specified add-on file.

	\param in_strFileName File path of the add-on file to uninstall.

	\return CStatus::Ok Success
	\return CStatus::Fail Installation failure
	\since 7.5
	*/
	CStatus UnInstallAddon( const CString& in_strFileName );

	/*! Creates a new command. The details of the new command are defined by calling the functions on the
	returned Command object. Once completely defined the command is installed by passing the command object
	back to Softimage with a call to Application::AddCommand. If a command already exists by that name then
	this command will fail.

	\note Rather than calling this function, it is recommended that custom commands be defined as part of a
		self-installed plug-in.  See PluginRegistrar::RegisterCommand.
	\param in_CommandName	The unique name identifying the new command. Note that the command is not created
		if one with this name already exists.
	\param in_category		Where (on which Softimage standard menu) the command will appear in the user
		interface. For more information, see the ::siCommandCategory enum documentation.
	\return The newly created Command.
	*/
	Command CreateCommand( const CString& in_CommandName, siCommandCategory in_category = siNoCategory );

	/*! Installs a new Command into the system. This function is called after Application::CreateCommand.
	\note Rather than calling this function, it is recommended that custom commands be defined as part
		of a self-installed plug-in.  See PluginRegistrar::RegisterCommand.
	\param in_Cmd Command object containing the definition of the new command
	\return CStatus::OK Success.
	\return CStatus::Fail Failure.
	\sa Application::CreateCommand
	\since 4.0
	*/
	CStatus AddCommand(const CRef& in_Cmd);

	/*! Removes a command.  This is only called for \xt cus_cmds Custom Commands \endxt.

	To remove a custom command that is defined as part of a self-installed plug-in remove the script file
	or dll rather than calling this function.  Similarly, this function cannot be used to remove custom
	commands that are installed as part of an add-on.

	\param name Name of the Command, not the scripting name of the command.  For example \c Select \c Object
		instead of \c SelectObj
	\return CStatus::OK Success.
	\return CStatus::Fail Failure.
	*/
	CStatus RemoveCommand( const CString& name );

	/*! Returns the CommandArray object representing all the installed commands.
	\return Array of Command objects
	*/
	CommandArray GetCommands() const;

	/*! Returns a command by its scripting name. To return a command by its name use Application::GetCommands
	and  CommandArray::GetItem instead.
	\param scriptingName The scripting name of the command you want to find.
	\return The matching command
	\sa Command::ScriptingName
	\since 5.0
	*/
	Command GetCommandByScriptingName(const CString& scriptingName) const ;

	/*! Executes a specified command identified by its scripting name.
	\param in_name %Command scripting name.
	\param in_args Array of values containing the arguments to pass to the command. If the command is defined
		with output arguments, the array is updated with the new argument values returned by the command.
	\param io_val  The value returned by the command.

	\note If the command has no return value explicitly defined, ExecuteCommand returns all output arguments in
	a CValueArray object. However, if the command defines a return value, you cannot extract any output arguments
	from it. This is because the command is not returning an output argument array, but a specific value. You can
	check the \a Return \a Value section in the \xt ref_intro C# and Scripting Reference \endxt to see whether it
	uses an explicit return value and what that value is.

	\return CStatus::OK Success
	\return CStatus::Fail Failure
	\since 3.5

	\eg Adds a custom property to a sphere and extract the newly created property from the output argument
		returned by the \xl AddProp command.

	\code
		using namespace XSI;

		CValueArray args(3);

		args[0] = CValue(L"Sphere");
		args[1] = CValue(L"MeshSurface");
		args[2] = CValue(L"MySphere");

		Application app;
		CValue valSphere;
		app.ExecuteCommand( L"CreatePrim", args, valSphere );

		args.Resize(5);
		args[0] = L"Annotation";
		args[1] = valSphere;
		args[2] = CValue(); // use default
		args[3] = L"MyAnnotation";
		args[4] = CValue(); // newly created property is returned as output arg

		app.ExecuteCommand( L"AddProp", args, outArg );

		// AddProp return the new property in a CValueArray object stored in the
		// 5th argument.
		CValueArray propArray(args[4]);

		// the property is stored in the first element of the array
		Property prop(propArray[0]);
		app.LogMessage( L"Property name: " + prop.GetFullName() );

		// create a model an get the newly created model from the ouptut argument
		args.Resize(4);
		args[0] = valSphere;
		args[1] = L"MyModel";
		args[2] = CValue(); // optional parent
		args[3] = CValue(); // newly created model

		CValue retVal;
		app.ExecuteCommand( L"SICreateModel", args, retVal );

		Model myModel(args[3]);
		app.LogMessage( L"Model name: " + myModel.GetFullName() );

	\endcode
	*/
	CStatus ExecuteCommand
	(
		const CString&	in_name,
		CValueArray&	in_args,
		CValue&			io_val
	) const;

	/*! Executes a command.
	\note If the command has no return value explicitly defined, ExecuteCommand returns all output arguments in
		a CValueArray object. However, if the command defines a return value, you cannot extract any output arguments
		from it. This is because the command is not returning an output argument array, but a specific value. You can
		check the \a Return \a Value section in the \xt ref_intro C# and Scripting Reference \endxt to see whether it
		uses an explicit return value and what that value is.
	\deprecated 3.5 This version is kept for backward compatibility, please use the new version instead.
	\param in_name %Command scripting name.
	\param in_args Array of values containing the arguments to pass to the command. Because this argument is
		defined as const, the array cannot be updated with the output argument values returned by the command.
		You should use the other version of ExecuteCommand defined with a CValueArray& argument if you need
		to access the output argument values.
	\param io_val  The value returned by the command.
	\return CStatus::OK success
	\return CStatus::Fail failure
	*/

	CStatus ExecuteCommand
	(
		const CString&		in_name,
		const CValueArray&	in_args,
		CValue&				io_val
	) const;

	/*! Executes a script from a file. This function can detect the script language based on the file extension.
	\param in_ScriptFilename A string pointing to the script file to execute.
	\param in_ScriptLanguage Optional. Scripting language (for example, \c VBScript, \c JScript, or \c Python). If empty, the value in
		\a in_ScriptFilename is used to detect the scripting language to use.
	\param in_ScriptProcedure Optional. Name of a procedure in the script code that you want to call.
	\param in_args Optional. An array of arguments to pass to the procedure. Ignored if \c in_ScriptProcedure is not specified.
	\retval out_returnval Optional. Return value from the procedure.  Ignored if \c in_ScriptProcedure is not specified.
	\return If there was a script error this will be set to a failure status code and contain additional error details.
	\sa Command, CComAPIHandler, Application::ExecuteScriptProcedure
	\since 9.0 (2011)
	*/
	CScriptErrorDescriptor ExecuteScript
	(
		const CString &		in_ScriptFilename,
		const CString&		in_ScriptLanguage,
		const CString&		in_ScriptProcedure,
		CValueArray&		in_args,
		CValue&				out_returnval
	) ;

	/*! Executes a string of script code. This is a convenient way to execute script code directly from C++. For
	example, you may want to execute some code that is easy to implement in scripting, but hard to implement in C++.
	Another possible usage is in the context of a CustomDisplayHost-based script editor.

	This function is best suited for small scripts or dynamically generated code. For larger scripts, you may want
	to consider exposing the script as a custom Command.

	\param in_ScriptCode A string of script code to execute.
	\param in_ScriptLanguage Scripting language (for example, \c VBScript, \c JScript, or \c Python).
	\return CScriptErrorDescriptor object.  If there was a script error this will be set to a failure status code and contain additional error details.
	\sa Command, CComAPIHandler, Application::ExecuteCommand
	\since 5.0

	\eg ExecuteScriptCode and ExecuteScriptProcedure demo
	\code
	// Basic usage just executes the text directly
	app.ExecuteScriptCode(L"Logmessage \"Hello from VBScript\"", L"VBScript" ) ;

	// For more advanced usage it is possible to pass values and get a return value
	// by calling a procedure inside the script text

	CScriptErrorDescriptor status ;
	CValueArray fooArgs(1) ;
	fooArgs[0] = L"Argument Sent to Script" ;
	CValue retVal ;

	status = app.ExecuteScriptProcedure(
				L"function foo( x ) \n Logmessage x \n foo = 45 \n end function",
				L"VBScript",
				L"foo",
				fooArgs,
				retVal  ) ;

	// Catch an intentional script error

	status = app.ExecuteScriptProcedure(
			L"sub foo( x ) \n run time error! \n foo = 45 \n end sub",
			L"VBScript",
			L"foo",
			fooArgs,
			retVal ) ;

	// Show the error
	app.LogMessage( status.GetDescription() + CString( L" - " ) + CValue( status.GetErrorLineNumber() ).GetAsText() ) ;

	\endcode
	*/
	CScriptErrorDescriptor ExecuteScriptCode
	(
		const CString & in_ScriptCode,
		const CString&	in_ScriptLanguage
	) ;

	/*!
	This is an alternative to Application::ExecuteScriptCode which supports
	execution of a procedure inside script code.  By calling a procedure it is possible to
	pass arguments into the script code and get a return value back.

	\param in_ScriptCode A string of script code to execute.
	\param in_ScriptLanguage Scripting language (for example, "VBScript", "JScript", or "Python").
	\param in_ScriptProcedure Optional. Name of a procedure in the script code that you want to call.
	\param in_args Optional. An array of arguments to pass to the procedure. Ignored if \c in_ScriptProcedure is not specified.
	\retval out_returnval Optional. Return value from the procedure.  Ignored if \c in_ScriptProcedure is not specified.
	\return CScriptErrorDescriptor object.  If there was a script error this will be set to a failure status code and contain additional error details.

	\sa Application:ExecuteScriptCode
	\since 5.0
	*/

	CScriptErrorDescriptor ExecuteScriptProcedure
	(
		const CString & in_ScriptCode,
		const CString&	in_ScriptLanguage,
		const CString&	in_ScriptProcedure,
		CValueArray&	in_args,
		CValue&			out_returnval
	) ;

	/*! Returns all events currently defined in Softimage.
	\return CRefArray An array of EventInfo objects.
	\since 5.0
	*/
	CRefArray GetEventInfos() const;

	/*! Sends a message to the history logging mechanism. The message appears as a Message Box, in the History
	Window, or on the Status Bar, depending on which \c Severity parameter you used. For more information on these
	options, see the ::siSeverityType enum.
	\param in_Message	Message Text
	\param in_Sev		Severity of the message, the default value is ::siInfoMsg.
	\return CStatus::OK success
	\return CStatus::Fail failure
	*/
	CStatus LogMessage
	(
		const CString& in_Message,
		siSeverityType in_Sev = siInfoMsg
	) const;

	/*! Creates a new project at a specific location.  Existing projects won't be overwritten.
	\param in_ProjectPath	Full path name of the project.  The name of the created project corresponds to
		the leaf folder of the full path.
	\retval out_rProject	NOT SUPPORTED, JUST PASS A DUMMY PROJECT.
	\return CStatus::OK success
	\return CStatus::Fail failure
	*/
	CStatus	CreateProject(
			const CString& in_ProjectPath,
			Project &out_rProject) const;

	/*! Returns the Preferences object. This object is used to manage user preferences in Softimage. You can get
	or set preferences, import or export categories etc.
	\return The Preferences object.
	\since 4.0
	*/
	Preferences GetPreferences() const;

	/*! Returns the Desktop object. This object is used to manage UI objects within Softimage.
	\return The Desktop object.
	\since 4.0
	*/
	Desktop GetDesktop() const;

	/*! Returns the Factory object. This object is used to manage the creation of standalone objects within
	Softimage, such as unconnected scripted operators.
	\return The Factory object.
	\since 4.0
	*/
	Factory GetFactory() const;

	/*! Returns the name of the active tool. Only the following tools from the 3D view are supported: RotateTool,
	ScaleTool and TranslateTool. An empty string is returned if the tool is not recognized.
	\return The name of the active tool.
	\since 4.0
	*/
	CString GetActiveToolName() const;

	/*! Returns the UIToolkit object.
	\return The UIToolkit object.
	*/
	UIToolkit GetUIToolkit() const;

	/*! Returns all native and custom filters currently defined in Softimage.
	\return Array of Filter objects.
	\since 4.0
	*/
	CRefArray GetFilters() const;

	/*! Returns the list of all self-installable plug-ins currently loaded in Softimage.
	\return Array of Plugin objects.
	\since 4.0
	*/
	CRefArray GetPlugins() const;

	/*! Returns true if the application is in interactive mode or false if it is running in batch mode.
	\return True if the application is running in UI mode or false otherwise.
	\since 4.0
	*/
	bool IsInteractive() const;

	/*! Loads a self-installing plug-in file. Files with the following extensions are considered valid:
	\code 	.dllso, .vbs, .js, .pys, .py, .pls, .pl \endcode
	\param in_pluginPath Full path name of the plugin.
	\return Plugin object representing the newly installed plug-in. If the plug-in is already installed,
		the existing plug-in is returned.
	\since 4.0
	*/
	Plugin LoadPlugin( const CString& in_pluginPath );

	/*! Unloads a self-installing plug-in from Softimage. All registered plug-in items are unregistered
	when a plug-in is unloaded; Therefore you will not be able to use these items in Softimage until you
	reload the plug-in.

	Unloaded plug-ins can still be retrieved from Application::GetPlugins. They can be distinguished from
	other plug-ins by using the Plugin::IsLoaded property.  An unloaded plug-in always has no registered
	plug-in items.

	\param in_pluginPath Full path name of the plugin.
	\param in_bRemove Delete the plug-in file on disk if true.

	\return CStatus::OK success
	\return CStatus::False Already unloaded
	\return CStatus::Fail failure
	\since 4.0
	*/
	CStatus UnloadPlugin( const CString& in_pluginPath, bool in_bRemove );

	/*! When invoked Softimage checks each loaded self-installed Plugin file and reloads it if it has changed
	on disk.  It also scans the standard plug-in directories for any new plug-in files. This is identical to
	clicking the Update All button on the Plug-in Manager.
	\return CStatus::OK success
	\return CStatus::Fail failure
	\since 5.0
	*/
	CStatus UpdatePlugins() ;

	/*! Adds a new workgroup and loads any plug-ins found in the workgroup. This function does nothing if the
	workgroup is already part of the workgroup list. Softimage will remember the new workgroup
	as part of the user Preferences.
	\param in_workgroupPath Complete path to root directory of a workgroup
	\return CStatus::OK success
	\return CStatus::Fail failure
	\since 5.0
	*/
	CStatus AddWorkgroup(const CString& in_workgroupPath) ;

	/*! Disconnects Softimage from a workgroup.  Self-installed plug-ins, SPDLs and other content will be unloaded.
	\param in_workgroupPath Complete path to root directory of a workgroup
	\return CStatus::OK success
	\return CStatus::Fail failure
	\since 5.0
	*/
	CStatus RemoveWorkgroup(const CString& in_workgroupPath) ;

	/*! Returns the list of workgroups to which Softimage is actively connected.
	\return Array containing full paths to all active workgroups
	\since 5.0
	*/
	CStringArray GetWorkgroups() ;

	/*! Unloads all workgroup content and reloads it. This process can be time-consuming if the workgroup's
	content is large or the network connection is slow.  Doing this will ensure that any duplicate plug-ins
	are loaded in the correct conflict resolution behavior.  In normal circumstances calling
	Application::AddWorkgroup and Application::RemoveWorkgroup is faster and sufficient.
	\return CStatus::OK success
	\return CStatus::Fail failure
	\since 5.0
	*/
	CStatus RescanWorkgroups() ;

	/*! Activates or deactivates a workgroup.  Deactivating a workgroup is very similar to calling
	Application::RemoveWorkgroup except that Softimage will continue to remember the workgroup path.  This
	makes it easier for users to remember which workgroups they have connected to in the past. Softimage will
	not scan a deactivated workgroup for plug-ins and it will not be included in the list returned by
	Application::GetWorkgroups.

	\note Deactivated plug-ins are still stored in the \c data_management.workgroup_appl_path preference but
		they are prefixed with a \c ! character.
	\param in_workgroupPath Complete path to root directory of a workgroup
	\param in_bActivate True to activate the workgroup; false to deactivate it.
	\return CStatus::OK success
	\return CStatus::Fail failure
	\since 5.0
	*/
	CStatus ActivateWorkgroup( const CString& in_workgroupPath, bool in_bActivate ) ;

	/*! Returns the list of all rendering engines currently loaded in Softimage.
	\return Array of Renderer objects.
	\since 7.0
	*/
	CRefArray GetRenderers( ) ;

	/*! Returns the object whose ID is specified. If there is no object associated to the specified ID, an empty object is returned.
	\param in_nID An object ID.
	\return ProjectItem The object that matches the input ID.
	\sa ProjectItem.GetObjectID
	\since 7.0
	*/
	ProjectItem GetObjectFromID( ULONG in_nID ) const;

	/*! Returns all objects found in the scene that match a class identifier. These identifiers are documented but can also be
	discovered by inspecting Softimage objects with the SDK Explorer. The supported class identifierss are the following:

	\li \ref XSI::siAnnotationID
	\li \ref XSI::siCameraID
	\li \ref XSI::siClusterID
	\li \ref XSI::siClusterPropertyID
	\li \ref XSI::siConstraintID
	\li \ref XSI::siCustomOperatorID
	\li \ref XSI::siCustomPropertyID
	\li \ref XSI::siEnvelopeID
	\li \ref XSI::siEnvelopeWeightID
	\li \ref XSI::siExpressionID
	\li \ref XSI::siGeometryID
	\li \ref XSI::siGroupID
	\li \ref XSI::siICETreeID
	\li \ref XSI::siImageClipID
	\li \ref XSI::siLayerID
	\li \ref XSI::siLightID
	\li \ref XSI::siMaterialID
	\li \ref XSI::siModelID
	\li \ref XSI::siNullID
	\li \ref XSI::siNurbsSurfaceMeshID
	\li \ref XSI::siNurbsCurveListID
	\li \ref XSI::siOperatorID
	\li \ref XSI::siPassID
	\li \ref XSI::siPolygonMeshID
	\li \ref XSI::siPropertyID
	\li \ref XSI::siShaderID
	\li \ref XSI::siShapeKeyID
	\li \ref XSI::siX3DObjectID
	
	\param in_nClassID An object class id as defined in XSI::siClassID.
	\return CSIObjectRefArray Array of objects. 
	\sa Model::FindObjects
	\since 9.5 (2011)

	\eg
	\code
		using namespace XSI;
		Application app;

		// Returns all 3d objects in the scene as X3DObjects objects
		Application app;
		CSIObjectRefArray objArray = app.FindObjects( siX3DObjectID );
		for ( LONG i=0; i<objArray.GetCount(); i++ )
		{
			app.LogMessage( "X3DObject: " + objArray[i].GetFullName() );
		}

		// Returns all lights in the scene as Light 3D objects only
		objArray = app.FindObjects( siLightID );
		for ( LONG i=0; i<objArray.GetCount(); i++ )
		{
			app.LogMessage( "Lights: " + objArray[i].GetFullName() );
		}

		// Returns all nurbs surface in the scene as NurbsSurfaceMesh geometry objects
		objArray = app.FindObjects( siNurbsSurfaceMeshID );
		for ( LONG i=0; i<objArray.GetCount(); i++ )
		{
			app.LogMessage( "NurbsSurfaceMesh: " + objArray[i].GetFullName() );
		}

		// Returns all geometries in the scene as Geometry objects
		objArray = app.FindObjects( siGeometryID );
		for ( LONG i=0; i<objArray.GetCount(); i++ )
		{
			app.LogMessage( "Geometry: " + objArray[i].GetFullName() );
		}
	\endcode

	*/
	CSIObjectRefArray FindObjects( const XSI::siClassID& in_nClsID ) const;

	/*! Returns all objects found in the scene that match a Softimage object \c CLSID. Object CLSID are not documented 
	but can be discovered with XSIUtils.DataRepository or by inspecting Softimage objects with the SDK Explorer.
	
	\param in_sCLSID An object \c CLSID.
	\return CSIObjectRefArray Array of objects.
	\sa Model::FindObjects
	\since 9.5 (2011)

	\eg
	\code
		using namespace XSI;
		Application app;
		// Find all lights in the scene
		CSIObjectRefArray lights = app.FindObjects( "{F3705C30-5204-11D0-8298-00A0243E366B}" );

		for ( LONG i=0; i< lights.GetCount(); i++ )
		{
			app.LogMessage( "Light: " + lights[i].GetFullName() );
		}
	\endcode
	
	*/
	CSIObjectRefArray FindObjects( const CString& in_sCLSID ) const;

	/*! Returns a shader definition by its \c ProgID.
	\param in_progID A shader ProgID.
	\return The matching ShaderDef.
	\since 9.0 (2011)
	*/
	ShaderDef GetShaderDef(	const CString&	in_progID );

	/*! Returns an array of shader definitions loaded in Softimage.
	\return Array of references to ShaderDef objects.
	\since 9.0 (2011)
	*/
	CRefArray GetShaderDefinitions( );

	/*! Registers a new shader family. This shader family can subsequently be used to apply
	to new shaders using the ShaderDef::AddShaderFamily call. The family name should be kept
	reasonably short. The display name is shown to the user if the family is registered, for
	any informative messages and tooltips.

	The \c in_nodeRed, \c in_nodeGreen, and \c in_nodeBlue parameters control the default
	display color of the family when shown in the rendertree. If multiple families are used
	on a given shader, the primary family dictates the color.

	The family can also indicate whether the shader node will support a shaderball by
	default.
	\param in_strName The family's intrinsic name. Used when creating a shader.
	\param in_strDisplayName The family's descriptive name to be used in the UI.
	\param in_strDescription A short description of the family for information purposes.
	\param in_nodeRed The red color component for the node display (\c 0-255).
	\param in_nodeGreen The green color component for the node display (\c 0-255).
	\param in_nodeBlue The blue color component for the node display (\c 0-255).
	\param in_bShaderball A flag indicating whether the shader family is supported by shaderballs.
	\return CStatus::OK success
	\return CStatus::Fail failure
	\since 9.0 (2011)
	\sa ShaderDef::AddShaderFamily, ShaderDef::GetShaderFamilies
	*/
	CStatus RegisterShaderFamily(
		const CString &in_strName,
		const CString &in_strDisplayName,
		const CString &in_strDescription,
		unsigned char in_nodeRed,
		unsigned char in_nodeGreen,
		unsigned char in_nodeBlue,
		bool		in_bShaderball
		);

	/*! Registers a new custom parameter type for shaders. This custom parameter type can
	be used to create new shader parameter definitions that have specific connection
	rules. A shader parameter of a given custom parameter type can only connect to
	another of the same type, unless a custom type filter is specified. This type filter
	is a simple flat list of parameter types, which can be either custom or built-in
	types (see ::siShaderParameterDataType for the list of string representations of the
	built-in types).

	In addition, the custom parameter type can also restrict the type of shaders
	connecting to it, by specifying a list of allowed family types. The family filter
	is applied to all shaders in the sub-tree defined by the shader (the source) being
	connected into the shader parameter of the custom parameter type (the target).

	\param in_strName The port's intrinsic name. Used when creating a shader port.
	\param in_strDisplayName The port's descriptive name to be used in the UI.
	\param in_strDescription A short description of the port for information purposes.
	\param in_nodeRed The red color component for the port display (\c 0-255).
	\param in_nodeGreen The green color component for the port display (\c 0-255).
	\param in_nodeBlue The blue color component for the port display (\c 0-255).
	\param in_typeFilter List of other port types from which this port type allows connections into.
	\param in_familyFilter List of shader families that can connect into this port.
	\return CStatus::OK success
	\return CStatus::Fail failure	
	\since 9.0 (2011)
	\sa ShaderParamDef::GetDataType, ShaderParameter::GetDataType, ShaderParamDefContainer::AddArrayParamDef,
		ShaderParamDefContainer::AddParamDef
	*/
	CStatus RegisterShaderCustomParameterType(
		const CString &in_strName,
		const CString &in_strDisplayName,
		const CString &in_strDescription,
		unsigned char in_portRed,
		unsigned char in_portGreen,
		unsigned char in_portBlue,
		const CStringArray &in_typeFilter,
		const CStringArray &in_familyFilter
		);

	/*! Opens an undo complex. An undo complex can be used to undo/redo multiple undoable commands in one single
	operation. Once an undo complex is opened, all subsequent undoable command calls will be added to this complex.
	The Application::CloseUndo method should be called to close an opened complex. 
	<br>
	OpenUndo is not meant to be used as a replacement for custom commands though but can be used in specific scenarios where
	the use of custom commands is not necessary. For instance, firing a script from a custom menu item could be done 
	with an undo complex without the needs of writing a custom command for undoing the whole script in one go.
	<br>
	<b>Note:</b> Undo complexes left opened due to a missing CloseUndo call may lead to undo/redo 
	problems. However, Softimage will try to close automatically any opened undo complexes when possible.
	
	\param in_sComplexName Name of this complex displayed in the Softimage undo menu.
	\return CStatus::OK success
	\return CStatus::Fail failure
	\since 10.0 (2012)
	\sa Application::CloseUndo

	\eg
	\code
		using namespace XSI;
		Application app;

		app.OpenUndo("my undo complex");

		Model root = app.GetActiveSceneRoot();
		
		X3DObject obj;
		root.AddGeometry( "grid", "MeshSurface", "mygrid", obj );
		root.AddGeometry( "cube", "MeshSurface", "mycube", obj );
		
		app.CloseUndo();
	\endcode
	*/
	CStatus OpenUndo( const CString& in_sComplexName );

	/*! Closes an open undo complex. EndUndo calls are ignored if they don't match a complex previously opened
	with Application::OpenUndo.
	<br>
	<b>Note:</b> Undo complexes left open due to a missing CloseUndo call may lead to undo/redo 
	problems. However, Softimage will try to close automatically any open undo complexes when possible.
	
	\return CStatus::OK success
	\return CStatus::Fail failure
	\since 10.0 (2012)
	\sa Application::OpenUndo

	\eg
	\code
		using namespace XSI;
		Application app;

		app.OpenUndo("my undo complex");

		Model root = app.GetActiveSceneRoot();
		
		X3DObject obj;
		root.AddGeometry( "grid", "MeshSurface", "mygrid", obj );
		root.AddGeometry( "cube", "MeshSurface", "mycube", obj );
		
		app.CloseUndo();
	\endcode
	*/
	CStatus CloseUndo( );

	/*! Returns true if some command is currently undoing or redoing its work.
	\return True if a command is currently undoing or redoing its work.
	\since 10.0 (2012)
	*/
	bool IsUndoing() const;
	
	/*! Returns the Custom Property count for a given type.
	\param in_strType A Custom Property type.
	\return ULONG The Custom Property count.
	\sa ProjectItem.GetObjectID
	\since 11.0 (2013)
	*/
	ULONG GetCustomPropertyCount( const CString& in_strType ) const;

	private:
	Application * operator&() const;
	Application * operator&();
};



};

#endif // __XSIAPPLICATION_H__
