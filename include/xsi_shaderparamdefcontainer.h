//*****************************************************************************
/*!
	\file xsi_shaderparamdefcontainer.h
	\brief ShaderParamDefContainer class declaration.

	Copyright 2009 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSISHADERPARAMDEFCONTAINER_H__
#define __XSISHADERPARAMDEFCONTAINER_H__

#include <xsi_siobject.h>
#include <xsi_shaderparamdef.h>
#include <xsi_shaderparamdefoptions.h>

namespace XSI {

//*****************************************************************************
/*! \brief Represents a set of ShaderParamDef, ShaderArrayParamDef, and/or ShaderStructParamDef objects.

This object allows you to manage the list of input and output parameters defined on a shader definition object
(ShaderDef). Use this object to add and remove members and also access a CRefArray of ShaderParamDef objects
(via the ShaderParamDefContainer::GetDefinitions member) to iterate over the list of parameters.

There are three functions which return a ShaderParamDefContainer:
\li ShaderDef::GetInputParamDefs
\li ShaderDef::GetOutputParamDefs
\li ShaderStructParamDef::GetSubParamDefs

\sa ShaderDef::GetInputParamDefs, ShaderDef::GetOutputParamDefs, ShaderStructParamDef::GetSubParamDefs
	ShaderParamDef, ShaderDef, \xt cus_shaders_Params %Shader %Parameter Definitions \endxt,
	\xm ShaderDefinitions/netview_ShaderDefs Color Sampler example \endxm
\since 9.0 (2011)
 */
//*****************************************************************************

class SICPPSDKDECL ShaderParamDefContainer : public SIObject
{
public:
	/*! Default constructor. */
	ShaderParamDefContainer();

	/*! Default destructor. */
	~ShaderParamDefContainer();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	ShaderParamDefContainer(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	ShaderParamDefContainer(const ShaderParamDefContainer& in_obj);

	/*! Returns true if a given class type is compatible with this API class.
	\param in_ClassID class type.
	\return true if the class is compatible, false otherwise.
	*/
	bool IsA( siClassID in_ClassID) const;

	/*! Returns the type of the API class.
	\return The class type.
	*/
	siClassID GetClassID() const;

	/*! Creates an object from another object. The newly created object is set to
	empty if the input object is not compatible.
	\param in_obj constant class object.
	\return The new ShaderParamDefContainer object.
	\since 9.0 (2011)
	*/
	ShaderParamDefContainer& operator=(const ShaderParamDefContainer& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new ShaderParamDefContainer object.
	\since 9.0 (2011)
	*/
	ShaderParamDefContainer& operator=(const CRef& in_ref);

	/*! Adds a ShaderArrayParamDef to this container. The type of the new parameter must be one of the standard Softimage
	native data types.

	\par Warning:
		You must specify any characteristics such as display name, capabilities, value range, etc.
		for this parameter definition on the ShaderParamDefOptions object before calling this method.
	\param in_name The registered name for the new parameter. On an instance of this parameter definition (ShaderParameter),
		this value will be returned when you call Parameter::GetScriptName.<br><br>To set the label you see in the UI for
		this parameter, use ShaderParamDefOptions::SetLongName.<br><br>To set the value returned by ShaderParamDef::GetDisplayName,
		use ShaderParamDefOptions::SetShortName.
	\param in_dataType The type of shader parameter to create (one of the ::siShaderParameterDataType values).
	\param in_options Options for this shader parameter definition. Use Factory::CreateShaderParamDefOptions to create the
		options as a ShaderParamDefOptions object.
	\return The new array parameter definition.
	\sa ShaderParamDefContainer::AddParamDef \xt cus_shaders_ParamsAdding Adding %Parameter Definitions \endxt
	\since 9.0 (2011)
	*/
	ShaderParamDef AddArrayParamDef( const CString& in_name, siShaderParameterDataType in_dataType, const ShaderParamDefOptions& in_options=CRef() );

	/*! Adds a ShaderArrayParamDef to this container. The type of the new parameter can be one of the standard
	Softimage native data types or a custom data type.

	\par Warning:
		You must specify any characteristics such as display name, capabilities, value range, etc.
		for this parameter definition on the ShaderParamDefOptions object before calling this function.
	\note This function can be used as a shorthand for adding parameter definitions using custom shader port
		types (see Application::RegisterShaderCustomParameterType).
	\param in_name The registered name for the new parameter. On an instance of this parameter definition (ShaderParameter),
		this value will be returned when you call Parameter::GetScriptName.<br><br>To set the label you see in the UI for
		this parameter, use ShaderParamDefOptions::SetLongName.<br><br>To set the value returned by ShaderParamDef::GetDisplayName,
		use ShaderParamDefOptions::SetShortName.
	\param in_dataType The type of shader parameter to create. This can be either the string version of any of the
		::siShaderParameterDataType values or a custom data type that has been registered with
		Application::RegisterShaderCustomParameterType.
	\param in_options Options for this shader parameter definition. Use Factory::CreateShaderParamDefOptions to create the
		options as a ShaderParamDefOptions object.
	\return The new array parameter definition.
	\sa ShaderParamDefContainer::AddParamDef \xt cus_shaders_ParamsAdding Adding %Parameter Definitions \endxt
	\since 9.0 (2011)
	*/
	ShaderParamDef AddArrayParamDef( const CString& in_name, const CString &in_dataType, const ShaderParamDefOptions& in_options=CRef() );

	/*! Adds a ShaderParamDef to this container. The type of the new parameter must be one of the standard Softimage native
	data types.

	\par Warning:
		You must specify any characteristics such as display name, capabilities, value range, etc.
		for this parameter definition on the ShaderParamDefOptions object before calling this function.
	\param in_name The registered name for the new parameter. On an instance of this parameter definition (ShaderParameter),
		this value will be returned when you call Parameter::GetScriptName.<br><br>To set the label you see in the UI for
		this parameter, use ShaderParamDefOptions::SetLongName.<br><br>To set the value returned by ShaderParamDef::GetDisplayName,
		use ShaderParamDefOptions::SetShortName.
	\param in_dataType The type of shader parameter to create (one of the ::siShaderParameterDataType values).
	\param in_options Options for this shader parameter definition. Use Factory::CreateShaderParamDefOptions to create the
		options as a ShaderParamDefOptions object.
	\return The new parameter definition.
	\sa ShaderParamDefContainer::AddArrayParamDef \xt cus_shaders_ParamsAdding Adding %Parameter Definitions \endxt
	\since 9.0 (2011)
	*/
	ShaderParamDef AddParamDef( const CString& in_name, siShaderParameterDataType in_dataType, const ShaderParamDefOptions& in_options=CRef() );

	/*! Adds a ShaderParamDef to this container. The type of the new parameter can be one of the standard Softimage native
	data types or a custom data type.

	\par Warning:
		You must specify any characteristics such as display name, capabilities, value range, etc.
		for this parameter definition on the ShaderParamDefOptions object before calling this function.
	\note This function can be used as a shorthand for adding parameter definitions using custom shader port
		types (see Application::RegisterShaderCustomParameterType).
	\param in_name The registered name for the new parameter. On an instance of this parameter definition (ShaderParameter),
		this value will be returned when you call Parameter::GetScriptName.<br><br>To set the label you see in the UI for
		this parameter, use ShaderParamDefOptions::SetLongName.<br><br>To set the value returned by ShaderParamDef::GetDisplayName,
		use ShaderParamDefOptions::SetShortName.
	\param in_dataType The type of shader parameter to create. This can be either the string version of any of the
		::siShaderParameterDataType values or a custom data type that has been registered with
		Application::RegisterShaderCustomParameterType.
	\param in_options Options for this shader parameter definition. Use Factory::CreateShaderParamDefOptions to create the
		options as a ShaderParamDefOptions object.
	\return The new parameter definition.
	\sa ShaderParamDefContainer::AddArrayParamDef \xt cus_shaders_ParamsAdding Adding %Parameter Definitions \endxt
	\since 9.0 (2011)
	*/
	ShaderParamDef AddParamDef( const CString& in_name, const CString &in_dataType, const ShaderParamDefOptions& in_options=CRef() );

	/*! Returns the list of all parameter definitions (ShaderParamDef objects) for this ShaderParamDefContainer object.
	\return CRefArray of ShaderParamDef objects
	\sa ShaderParamDefContainer::GetParamDefByName
	\since 9.0 (2011)
	*/
	CRefArray GetDefinitions(  );

	/*! Returns the ShaderParamDef that matches the specified name from this container. This is preferable to calling
	ShaderParamDefContainer::GetDefinitions(\c in_parameterName) if you don't need to iterate over the collection.
	\param in_parameterName The registered name of the shader parameter definition to return.
	\return the matching ShaderParamDef
	\sa ShaderParamDefContainer::GetDefinitions
	\since 9.0 (2011)
	*/
	ShaderParamDef GetParamDefByName( const CString& in_parameterName );

	private:
	ShaderParamDefContainer * operator&() const;
	ShaderParamDefContainer * operator&();
};

};

#endif

