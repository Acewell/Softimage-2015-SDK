//*****************************************************************************
/*!
	\file xsi_shaderdef.h
	\brief ShaderDef class declaration.

	Copyright 2009 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSISHADERDEF_H__
#define __XSISHADERDEF_H__

#include <xsi_valuemap.h>
#include <xsi_metashaderrendererdef.h>
#include <xsi_shaderballoptions.h>
#include <xsi_shaderparamdefcontainer.h>
#include <xsi_siobject.h>
#include <xsi_ppglayout.h>

namespace XSI {

//*****************************************************************************
/*!
	\brief Represents a custom shader definition.

	A shader definition is similar to a preset in that it stores a snapshot of a shader, often in a
	file on disk. However, a traditional Softimage <tt>.preset</tt> file is a binary file built from a SPDL,
	whereas a shader definition can be created and/or modified in several ways, including via a
	self-installing plug-in, a special XML file saved on disk (<tt>.xsishaderdef</tt>), or by coding on the fly.

	To create a self-installing, plug-in based shader definition you need to implement the
	\xt cb_Shader_Define Define \endxt and \xt cb_Shader_DefineInfo DefineInfo \endxt callbacks.
	For more information, see \xt cus_shaders Custom Shaders \endxt

	To create a shader definition on the fly, you can use Factory::CreateShaderDef and then populate
	the definition using the returned ShaderDef object.

	Saving shader definitions to a <tt>.xsishaderdef</tt> file is the most reliable way to manage shader versions.
	You can then use the \xl ReplaceShadersDefinition command to upgrade a specific list of shaders to a new shader
	definition.

	To get a list of all shader definitions in the current session of Softimage, use the Application::GetShaderDefinitions
	function. You can also access a specific shader definition by \c ProgID by using the Application::GetShaderDef function

	\sa Application::GetShaderDef, Factory::CreateShaderDef, Shader::GetShaderDef, Factory::RemoveShaderDef,
		\xt cb_shader %Shader callbacks \endxt, \xt cus_shaders Custom Shaders \endxt

	\since 9.0 (2011)
 */
//*****************************************************************************
class SICPPSDKDECL ShaderDef : public SIObject
{
public:
	/*! Default constructor.
	\since 9.0 (2011)
	*/
	ShaderDef();

	/*! Default destructor.
	\since 9.0 (2011)
	*/
	~ShaderDef();

	/*! Constructor.
	\param in_ref constant reference object.
	\since 9.0 (2011)
	*/
	ShaderDef(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	\since 9.0 (2011)
	*/
	ShaderDef(const ShaderDef& in_obj);

	/*! Returns true if a given class type is compatible with this API class.
	\param in_ClassID class type.
	\return true if the class is compatible, false otherwise.
	\since 9.0 (2011)
	*/
	bool IsA( siClassID in_ClassID) const;

	/*! Returns the type of the API class.
	\return The class type.
	\since 9.0 (2011)
	*/
	siClassID GetClassID() const;

	/*! Creates an object from another object. The newly created object is set to
	empty if the input object is not compatible.
	\param in_obj constant class object.
	\return The new ShaderDef object.
	\since 9.0 (2011)
	*/
	ShaderDef& operator=(const ShaderDef& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new ShaderDef object.
	\since 9.0 (2011)
	*/
	ShaderDef& operator=(const CRef& in_ref);


	/*! Adds a MetaShaderRendererDef definition and returns it. Every ShaderDef must have
	at least one renderer defined in order to know how to render. This is equivalent to having
	a \c MetaShader section in a SPDL file.

	The newly created object is set to empty if the renderer definition is already present.
	\param in_renderer The name of the renderer. This is the equivalent of the string identifying
		each \c %Renderer section under the \c MetaShader section in a SPDL file.
	\return The new MetaShaderRendererDef object.
	\sa ShaderDef::RemoveRendererDef, ShaderDef::GetRendererDefByName, ShaderDef::GetRendererDefs

	\since 9.0 (2011)
	*/
	MetaShaderRendererDef AddRendererDef( const CString& in_renderer );

	/*! Returns the list of attributes available on this shader definition as a ValueMap.
	\return A new ValueMap object.
	\sa ShaderParamDef::GetAttributes
	\since 9.0 (2011)
	*/
	ValueMap GetAttributes(  ) const;

	/*! Returns the category for this shader definition. The category is used to determine where the
	shader preset will appear in the preset manager in the render tree. For example, the native
	Softimage \xp Softimage_mib_texture_checkerboard_1_0 Checkerboard shader \endxp appears under the
	\c %Texture category.

	\return The category name.
	\sa \xt cus_shaders_PresetMgr Populating the Preset Manager \endxt
	\since 9.0 (2011)
	*/
	CString GetCategory(  ) const;

	/*! Sets the category for this shader definition. The category is used to determine where the
	shader preset will appear in the preset manager in the render tree. For example, the native
	Softimage \xp Softimage_mib_texture_checkerboard_1_0 Checkerboard shader \endxp appears under the
	\c %Texture category.

	\note If you do not specify a category, your shader definition will not appear in the preset manager.
		For more information, see \xt cus_shaders_PresetMgr Populating the Preset Manager \endxt
	\param in_category The category name.
	\return Success/failure
	\sa \xt cus_shaders_PresetMgr Populating the Preset Manager \endxt
	\since 9.0 (2011)
	*/
	CStatus PutCategory( const CString& in_category );

	/*! Returns the definition path for this shader definition. The definition path is where the shader was
	defined, so for parser-based definitions, this means that the file that was parsed (for example,
	<tt>&lt;factory_path&gt;\Application\Shaders\cgfx\check3d.cgfx</tt>), whereas the plug-in based definition
	paths refer to the plug-in file where the definition was implemented (for example,
	<tt>&lt;workgroup_path&gt;\Application\Plugins\MyShader.dll</tt>), and the spdl-based definition paths
	point to the SPDL files (for example, <tt>&lt;factory_path&gt;\Application\Shaders\spdl\sitoon\sitoon_paint.spdl</tt>).
	\return The definition path.
	\sa ShaderDef::GetPlugin, ShaderDef::GetPluginFilename, \xt cus_shaders_GettingStarted Understanding Softimage Custom Shaders \endxt
	\since 9.0 (2011)
	*/
	CString GetDefinitionPath(  ) const;

	/*! Sets the definition path for this shader definition. The definition path is where the shader was
	defined, so for parser-based definitions, this means that the file that was parsed (for example,
	<tt>&lt;factory_path&gt;\Application\Shaders\cgfx\check3d.cgfx</tt>), whereas the plug-in based definition
	paths refer to the plug-in file where the definition was implemented (for example,
	<tt>&lt;workgroup_path&gt;\Application\Plugins\MyShader.dll</tt>), and the spdl-based definition paths
	point to the SPDL files (for example, <tt>&lt;factory_path&gt;\Application\Shaders\spdl\sitoon\sitoon_paint.spdl</tt>).

	\param in_path The definition path. You can modify it to include more information or make the path relative.
	\return Success/failure
	\sa ShaderDef::GetPlugin, ShaderDef::GetPluginFilename, \xt cus_shaders_GettingStarted Understanding Softimage Custom Shaders \endxt
	\since 9.0 (2011)
	*/
	CStatus PutDefinitionPath( const CString& in_path );

	/*! Sets the name that appears in the preset manager. When creating a plug-in based shader definition, set
	this using the \c DisplayName attribute in the \xt cb_Shader_DefineInfo DefineInfo \endxt callback. When
	creating a definition via a shader language parser plug-in, set this using the \c DisplayName attribute in
	the \xt cb_ShaderParser_ParseInfo ParseInfo \endxt callback.
	\return The display name.
	\sa \xt cus_shaders_PresetMgr Populating the Preset Manager \endxt
	\since 9.0 (2011)
	*/
	CString GetDisplayName(  ) const;

	/*! Returns the name that appears in the preset manager. The display name tells the Preset Manager which name
	to display for the shader. It is also used when as the default name for new shaders.

	\param in_name The display name.
	\return Success/failure
	\sa \xt cus_shaders_PresetMgr Populating the Preset Manager \endxt
	\since 9.0 (2011)
	*/
	CStatus PutDisplayName( const CString& in_name );

	/*! Returns the MetaShaderRendererDef that matches the specified name. This is the equivalent to calling
	ShaderDef::GetRendererDefs(\c in_str).
	\param in_renderer The name of the renderer to return. This is the equivalent of the string
		identifying each \c %Renderer section under the \c MetaShader section in a SPDL file.
	\return The matching MetaShaderRendererDef object
	\return An invalid object if not found
	\sa ShaderDef::AddRendererDef, ShaderDef::RemoveRendererDef, ShaderDef::GetRendererDefs
	\since 9.0 (2011)
	*/
	MetaShaderRendererDef GetRendererDefByName( const CString& in_renderer ) const;

	/*! Returns a ShaderParamDefContainer containing the input parameter definitions for this shader definition.
	You can use this container to iterate over input parameter definitions or add new input parameter definitions
	to the shader definition while creating it.
	\return A ShaderParamDefContainer object representing the input parameters.
	\sa ShaderDef::GetOutputParamDefs, \xt cus_shaders_Params %Shader %Parameter Definitions \endxt,
		\xt cus_shaders_ParamsAdding Adding %Parameter Definitions \endxt
	\since 9.0 (2011)
	*/
	ShaderParamDefContainer GetInputParamDefs(  ) const;

	/*! Returns a ShaderParamDefContainer containing the output parameter definitions for this shader definition.
	You can use this container to iterate over output parameter definitions or add new output parameter definitions
	to the shader definition while creating it.
	\return A ShaderParamDefContainer object representing the output parameters.
	\sa ShaderDef::GetInputParamDefs, \xt cus_shaders_Params %Shader %Parameter Definitions \endxt,
		\xt cus_shaders_ParamsAdding Adding %Parameter Definitions \endxt
	\since 9.0 (2011)
	*/
	ShaderParamDefContainer GetOutputParamDefs(  ) const;

	/*! Indicates whether or not the shader was parsed. See ShaderDef::GetParserBased for a description of how shader
	definitions can be created by parsing files and ShaderDef::GetPluginBased for a description of how shader definitions
	can be created from self-installing plug-ins.
	\return true if the shader definition was parsed
	\return false otherwise
	\sa ShaderDef::GetParserBased, ShaderDef::GetParser,
		\xt cus_shaders_CreatingShaderParsers Creating %Shader Language Parser Definitions \endxt
	\since 9.0 (2011)
	*/
	bool GetParsed(  ) const;

	/*! Indicates whether or not the shader was parsed. See ShaderDef::GetParserBased for a description of how shader
	definitions can be created by parsing files and ShaderDef::GetPluginBased for a description of how shader definitions
	can be created from self-installing plug-ins.
	\note This only affects shader definitions that are parser based.
	\param in_parsed true to force the shader definition to be parsed again
	\return Success/failure
	\sa ShaderDef::GetParserBased, ShaderDef::GetParser,
		\xt cus_shaders_CreatingShaderParsers Creating %Shader Language Parser Definitions \endxt
	\since 9.0 (2011)
	*/
	CStatus PutParsed( bool in_parsed );

	/*! Returns the the name of the parser. This is the name you specified for the parser you created with the
	PluginRegistrar::RegisterShaderLanguageParser function. It is used, along with the class name and version number,
	to create the shader definition's \c ProgID.
	\note See ShaderDef::GetParserBased for a description of how shader definitions can be created by parsing files
		with a specific shader language parser.
	\return the parser name
	\sa ShaderDef::GetParserBased, ShaderDef::GetParsed, ShaderDef::GetPlugin,
		\xt cus_shaders_CreatingShaderParsers Creating %Shader Language Parser Definitions \endxt,
		\xt cus_shaders_ProgID Instantiating %Shader Definitions and the ProgID \endxt
	\since 9.0 (2011)
	*/
	CString GetParser(  ) const;

	/*! Changes the parser name. The parser name is normally set by calling PluginRegistrar::RegisterShaderLanguageParser;
	however, changing the parser name can be useful if you have 2 parsers for the same file extension. A ShaderDef must have
	a non-empty ParserName or a PluginName in order to build a valid ProgID.

	For plugin-based shader definitions, this method is meaningless (use ShaderDef::PutPlugin instead).
	\note See ShaderDef::GetParserBased for a description of how shader definitions can be created by parsing files
		with a specific shader language parser.
	\param in_parser the parser name
	\return Success/failure
	\sa ShaderDef::GetParserBased, ShaderDef::GetParsed, ShaderDef::GetPlugin,
		\xt cus_shaders_CreatingShaderParsers Creating %Shader Language Parser Definitions \endxt,
		\xt cus_shaders_ProgID Instantiating %Shader Definitions and the ProgID \endxt
	\since 9.0 (2011)
	*/
	CStatus PutParser( const CString& in_parser );

	/*! Returns whether or not the definition was generated from a parsed file by checking if ShaderDef::GetParser returns
	an empty string. Softimage can create shader definitions by extracting the list of parameters, categories, attributes, etc.
	from one of the standard text file shader formats, such as <tt>.mi</tt> or <tt>.cgfx</tt>, or a custom text file format. Softimage
	ships with several built-in parsers to create shader definitions from several file formats (including <tt>.fx</tt>, <tt>.cgfx</tt>, etc.)
	but you can also create your own shader language parser plug-in using the PluginRegistrar::RegisterShaderLanguageParser
	function. See the \xt cus_shaders_CreatingShaderParsers Creating %Shader Language Parser Definitions \endxt topic for more
	details.
	\return true if the shader definition was defined from a parsed file
	\return false otherwise
	\sa ShaderDef::GetPluginBased, ShaderDef::GetParsed, ShaderDef::GetParser,
		\xt cus_shaders_CreatingShaderParsers Creating %Shader Language Parser Definitions \endxt
	\since 9.0 (2011)
	*/
	bool GetParserBased(  ) const;

	/*! Returns the name of the plug-in. This is the name specified in the PluginRegistrar::RegisterShader method for the
	plug-in containing this shader definition. The plug-in name is used, along with the class name and version number, to
	create the shader definition's \c ProgID.
	\return the plugin name
	\sa ShaderDef::GetProgID, ShaderDef::GetPluginBased, ShaderDef::GetPluginFilename, ShaderDef::GetParser,
		\xt cus_shaders_CreatingDefPlugins Creating %Shader Definition Plug-ins \endxt,
		\xt cus_shaders_ProgID Instantiating %Shader Definitions and the ProgID \endxt
	\since 9.0 (2011)
	*/
	CString GetPlugin(  ) const;

	/*! Changes the plug-in name. The plug-in name is normally set by by calling PluginRegistrar::RegisterShader. It is used,
	along with the class name and version number, to create the shader definition's \c ProgID.

	For parser-based shader definitions, this method is meaningless (use ShaderDef::PutParser instead).
	\param in_plugin the plugin name
	\return Success/failure
	\sa ShaderDef::GetProgID, ShaderDef::GetPluginBased, ShaderDef::GetPluginFilename, ShaderDef::GetParser,
		\xt cus_shaders_CreatingDefPlugins Creating %Shader Definition Plug-ins \endxt,
		\xt cus_shaders_ProgID Instantiating %Shader Definitions and the ProgID \endxt
	\since 9.0 (2011)
	*/
	CStatus PutPlugin( const CString& in_plugin );

	/*! Returns whether or not the definition is plug-in-based by checking if ShaderDef::GetPlugin returns an empty string.
	Shader definitions can be created in a self-installing plug-in using the PluginRegistrar::RegisterShader function. The
	\xt cb_Shader_DefineInfo DefineInfo \endxt and \xt cb_Shader_Define Define \endxt callbacks give you access to the ShaderDef
	object so you can populate it with the list of parameters, categories, attributes, etc. See the
	\xt cus_shaders_CreatingDefPlugins Creating %Shader Definition Plug-ins \endxt topic for more details.
	\return true if the definition is plug-in based
	\return false otherwise
	\sa ShaderDef::GetParserBased, ShaderDef::GetPlugin,
		\xt cus_shaders_CreatingDefPlugins Creating %Shader Definition Plug-ins \endxt
	\since 9.0 (2011)
	*/
	bool GetPluginBased(  ) const;

	/*! Returns the location of the plug-in file that defines this shader.
	\return Returns the full path to the plug-in or an empty string.
	\sa ShaderDef::GetPlugin, ShaderDef::GetDefinitionPath,
		\xt cus_shaders_CreatingDefPlugins Creating %Shader Definition Plug-ins \endxt
	\since 9.0 (2011)
	*/
	CString GetPluginFilename(  ) const;

	/*! Returns the unique shader \c ProgID, which can be used to instantiate shaders to be used in the render tree. For more
	information, see \xt cus_shaders_ProgID Instantiating %Shader Definitions and the ProgID \endxt. The ProgID is a
	formatted string built from these components separated by periods:
	\li PluginName or ParserName
	\li ClassName
	\li MajorVersion
	\li MinorVersion

	\tip %Shader definitions built by the legacy SPDL parser use \c Softimage as the PluginName.
	\note This property returns exactly the same string as calling both the SIObject::GetName and SIObject::GetFullName functions.
	\return the \c ProgID
	\sa Shader::GetProgID, Parameter::ConnectFromProgID, \xt cus_shaders_ProgID Instantiating %Shader Definitions and the ProgID \endxt
	\since 9.0 (2011)
	*/
	CString GetProgID(  ) const;

	/*! Removes the specified renderer definition from the shader definition.
	\param in_rendererdef The MetaShaderRendererDef to remove.
	\return Success/failure
	\sa ShaderDef::AddRendererDef, ShaderDef::GetRendererDefByName, ShaderDef::GetRendererDefs
	\since 9.0 (2011)
	*/
	CStatus RemoveRendererDef( const MetaShaderRendererDef& in_rendererdef );

	/*! Returns a list of MetaShaderRendererDef object(s) associated with this shader definition. MetaShaderRendererDef objects can be
	added with ShaderDef::AddRendererDef and accessed with ShaderDef::GetRendererDefByName.
	\return list of references to MetaShaderRendererDef object(s)
	\sa ShaderDef::AddRendererDef, ShaderDef::RemoveRendererDef, ShaderDef::GetRendererDefByName
	\since 9.0 (2011)
	*/
	CRefArray GetRendererDefs(  ) const;

	/*! Returns the number of shader instances in the scene are using this ShaderDef.
	\return shader instance count
	\sa ShaderDef::GetShaderInstances
	\since 9.0 (2011)
	*/
	ULONG GetShaderInstanceCount(  ) const;

	/*! Returns a list containing all shader instances for this shader definition.
	\return list of references to Shader object(s)
	\sa ShaderDef::GetShaderInstanceCount
	\since 9.0 (2011)
	*/
	CRefArray GetShaderInstances(  ) const;

	/*! Returns the shaderball options.
	\return the shaderball options
	\since 9.0 (2011)
	*/
	ShaderballOptions GetShaderballOptions(  ) const;

	/*! Adds a new shader family. %Shader families specify the context in which the shader can be used (for example, you cannot connect a
	light shader to a material node for a scene item). In the UI, the context is identified by color: for example, Surface %Material
	(\c mrSurfaceMat) appears as green, Volume (\c mrVolume) appears as violet, Realtime shaders (\c xgsRealTimeShader) appear as light blue, etc.

	A shader definition must have at least one shader family defined but may also have one or more secondary families. One of these families
	is designated as the \a primary family, and it is that family that determines what color the node displays in the UI. Softimage uses
	pre-defined families for mental ray and realtime shaders, but you can also define your own shader family with the
	Application::RegisterShaderFamily function.

	\note You cannot remove a shader family once it has been added.

	\param in_type The new shader family. The native shader families that ship with Softimage are described in
		\xt cus_shaders_FamiliesNative Native Softimage %Shader Families \endxt. You can also register custom shader families in Softimage
		and add them using this method. For more information, see \xt cus_shaders_FamiliesCustom Creating Custom %Shader Families \endxt.
	\param in_bPrimary true if this family is the primary shader family for the shader definition
	\return CStatus::OK if the type was a valid type
	\return CStatus::Fail otherwise
	\sa ShaderDef::IsShaderFamily, ShaderDef::GetPrimaryShaderFamily, ShaderDef::GetShaderFamilies, Application::RegisterShaderFamily,
		\xt cus_shaders_Families %Shader Families \endxt
	\since 9.0 (2011)
	*/
	CStatus AddShaderFamily( const CString& in_type, bool in_bPrimary = false );

	/*! Checks whether this shader definition belongs to the specified shader family or not. See ShaderDef::AddShaderFamily for more
	information about shader families.
	\param in_type The shader family to check. See \xt cus_shaders_FamiliesNative Native Softimage %Shader Families \endxt for a list
		of supported families for Softimage native shaders.
	\return true if the specified shader family is supported.
	\sa ShaderDef::AddShaderFamily, ShaderDef::GetPrimaryShaderFamily, ShaderDef::GetShaderFamilies,
		\xt cus_shaders_Families %Shader Families \endxt
	\since 9.0 (2011)
	*/
	bool IsShaderFamily( const CString& in_type ) const;

	/*! Returns the name of the primary shader family this shader definition belongs to. See the \xt cus_shaders_Families %Shader Families \endxt
	topic for more information about shader families.
	\return primary shader family name
	\sa ShaderDef::AddShaderFamily, ShaderDef::IsShaderFamily, ShaderDef::GetShaderFamilies, Application::RegisterShaderFamily,
		\xt cus_shaders_Families %Shader Families \endxt
	\since 9.0 (2011)
	*/
	CString GetPrimaryShaderFamily( );

	/*! Returns the list of shader families for this shader definition. See the \xt cus_shaders_Families %Shader Families \endxt topic
	for more information about shader families.
	\return array of names representing each shader family supported by this shader definition
	\sa ShaderDef::AddShaderFamily, ShaderDef::IsShaderFamily, ShaderDef::GetPrimaryShaderFamily, Application::RegisterShaderFamily,
		\xt cus_shaders_Families %Shader Families \endxt
	\since 9.0 (2011)
	*/
	CStringArray GetShaderFamilies() const;

	/*! Returns a PPGLayout object representing the parameters associated to this shader definition. Getting the PPGLayout object using
	this function allows you customize the property page that is displayed when the user double-clicks the shader node in the render tree.
	\return PPGLayout representing the property page layout
	\sa ShaderDef::GetRenderTreeLayout, \xt cus_shaders_ParamsControls Refining UI Controls for %Parameter Definitions \endxt
	\since 9.0 (2011)
	*/
	PPGLayout GetPPGLayout() const;

	/*! Returns the PPGLayout for the shader node associated with this shader definition. Getting the PPGLayout object using this
	function allows you customize how the ports appear on the shader node in the render tree. For example, this allows you to group
	some ports together.
	\return PPGLayout representing the render tree layout
	\sa ShaderDef::GetPPGLayout, \xt cus_shaders_ParamsControls Refining UI Controls for %Parameter Definitions \endxt
	\since 9.0 (2011)
	*/
	PPGLayout GetRenderTreeLayout() const;

	private:
	ShaderDef * operator&() const;
	ShaderDef * operator&();
};

};

#endif

