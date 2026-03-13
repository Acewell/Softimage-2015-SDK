//*****************************************************************************
/*!
	\file xsi_shaderparamdefoptions.h
	\brief ShaderParamDefOptions class declaration.

	Copyright 2009 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSISHADERPARAMDEFOPTIONS_H__
#define __XSISHADERPARAMDEFOPTIONS_H__

#include <xsi_siobject.h>

namespace XSI {

//*****************************************************************************
/*! \brief Represents the advanced options for a shader parameter definition (ShaderParamDef) object.

	This object provides a convenient way to specify certain characteristics for each shader parameter definition
	(for example, display name, default values, capabilities, etc.). You can use the same ShaderParamDefOptions object
	for multiple parameters, changing only the display name (and any other characteristics you need to).

	The Factory::CreateShaderParamDefOptions function creates a new ShaderParamDefOptions object which you need to pass
	to the ShaderParamDefContainer::AddParamDef or ShaderParamDefContainer::AddArrayParamDef when adding parameter definitions.

	\sa Factory::CreateShaderParamDefOptions, ShaderParamDefContainer::AddParamDef,
		ShaderParamDefContainer::AddArrayParamDef, ShaderParamDef,
		\xt cus_shaders_ParamsAdding Adding %Parameter Definitions \endxt,
		\xm ShaderDefinitions/netview_ShaderDefs Color Sampler example \endxm
	\since 9.0 (2011)
 */
//*****************************************************************************

class SICPPSDKDECL ShaderParamDefOptions : public SIObject
{
public:
	/*! Default constructor. */
	ShaderParamDefOptions();

	/*! Default destructor. */
	~ShaderParamDefOptions();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	ShaderParamDefOptions(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	ShaderParamDefOptions(const ShaderParamDefOptions& in_obj);

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
	\return The new ShaderParamDefOptions object.
	\since 9.0 (2011)
	*/
	ShaderParamDefOptions& operator=(const ShaderParamDefOptions& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new ShaderParamDefOptions object.
	\since 9.0 (2011)
	*/
	ShaderParamDefOptions& operator=(const CRef& in_ref);


	/*! Sets whether or not this shader parameter can be animated.
	\param in_v true if animatable
	\return Success/failure
	\sa ShaderParamDefOptions::SetTexturable, ShaderParamDefOptions::SetInspectable,
		ShaderParamDef::GetCapabilities, ::siCapabilities, Parameter::PutCapabilityFlag,
		Parameter::GetCapabilities
	\since 9.0 (2011)
	*/
	CStatus SetAnimatable( bool in_v );

	/*! Sets the default value for this parameter definition. This defines the value that will
	be set on the instantiated ShaderParameter (Parameter::GetDefault).
	\param in_v Default value to use.
	\return Success/failure
	\sa ShaderParamDef::HasDefaultValue, ShaderParamDef::GetDefaultValue, ShaderParamDef::SetDefaultValue,
		Parameter::GetDefault, Parameter::PutValue
	\since 9.0 (2011)
	*/
	CStatus SetDefaultValue( const CValue& in_v );

	/*! Sets the minimum and maximum values for this parameter definition. This defines the valid value
	range when instantiated (Parameter::GetMin and Parameter::GetMax).
	\param in_vMin Minimum allowable value.
	\param in_vMax Maximum allowable value.
	\return Success/failure
	\sa ShaderParamDefOptions::SetSoftLimit, Parameter::GetMin, Parameter::GetMax
	\since 9.0 (2011)
	*/
	CStatus SetHardLimit( const CValue& in_vMin, const CValue& in_vMax );

	/*! Sets whether or not this parameter definition will appear on the property page associated with the
	instantiated Shader.
	\param in_v true if inspectable (will appear on the property page).
	\return Success/failure
	\sa ShaderParamDefOptions::SetAnimatable, ShaderParamDefOptions::SetTexturable, ::siCapabilities,
		Parameter::PutCapabilityFlag, Parameter::GetCapabilities
	\since 9.0 (2011)
	*/
	CStatus SetInspectable( bool in_v );

	/*! Sets the a user-friendly version of the parameter name that will appear in the UI. This is the value
	that the Parameter::GetScriptName function returns on the instance (ShaderParameter).

	\note If you don't set this option, the name you pass to the ShaderParamDefContainer::AddParamDef or
		ShaderParamDefContainer::AddArrayParamDef function when adding the ShaderParamDef will appear in
		the UI instead. Alternatively, you could also specify the UI name when you add this parameter as
		a PPGItem on the property page or render tree layout via the PPGLayout::AddItem function.
	\param in_str parameter name to be displayed in the UI (either on the shader node or on the associated property page).
	\return Success/failure
	\sa ShaderParamDefOptions::SetShortName, PPGLayout::AddItem,
		\xt cus_shaders_ParamsControls Refining UI Controls for %Parameter Definitions \endxt
	\since 9.0 (2011)
	*/
	CStatus SetLongName( const CString& in_str );

	/*! Sets the short version of the parameter name (the ShaderParamDef::GetDisplayName). This is the name that
	appears in the %Scene Explorer (with the <tt>%View &gt; Use Script Names</tt> option turned \c OFF). It is also
	the same value that SIObject::GetName returns on the instance (ShaderParameter).

	\note If you don't set this option, the name you pass to the ShaderParamDefContainer::AddParamDef or
		ShaderParamDefContainer::AddArrayParamDef function when adding the ShaderParamDef will be used instead.
	\param in_str The \c DisplayName as it will appear in the %Scene Explorer
	\return Success/failure
	\sa ShaderParamDef::GetDisplayName, SIObject::GetName, ShaderParamDefOptions::SetLongName
	\since 9.0 (2011)
	*/
	CStatus SetShortName( const CString& in_str );

	/*! Sets the suggested minimum and maximum values for this parameter definition. This defines the value range
	that is displayed in the property page when instantiated (Parameter::GetSuggestedMin and Parameter::GetSuggestedMax).
	\param in_vMin Minimum suggested value.
	\param in_vMax Maximum suggested value.
	\return Success/failure
	\sa ShaderParamDefOptions::SetHardLimit, Parameter::GetSuggestedMin, Parameter::GetSuggestedMax
	\since 9.0 (2011)
	*/
	CStatus SetSoftLimit( const CValue& in_vMin, const CValue& in_vMax );

	/*! Sets whether or not this parameter definition will be a shader node port when instantiated (supports being
	connected to a rendering node).
	\param in_v true if texturable.
	\return Success/failure
	\sa ShaderParamDef::SetTexturable, ShaderParamDefOptions::SetAnimatable, ShaderParamDefOptions::SetInspectable,
		::siCapabilities, Parameter::PutCapabilityFlag, Parameter::GetCapabilities
	\since 9.0 (2011)
	*/
	CStatus SetTexturable( bool in_v );

	/*! Sets an attribute by name. The attribute can be named anything and can contain any value. A list of attributes
	that Softimage understands can be found in \ref siShaderParameterAttribute "siShaderParameterAttribute".
	\param in_name Name of the attribute to set. Can be one of the \ref siShaderParameterAttribute "siShaderParameterAttribute"
		string constants or a string that you define, such as \c "version".
	\param in_value Value to set. This could be one of the Softimage shader string constants (::siShaderReferenceFilterType,
		::siShaderPropertyFilterType, \ref siShaderCustomDataType "siShaderCustomDataType"), or a custom value.
	\return CStatus::OK
	\sa ::siShaderReferenceFilterType, ::siShaderPropertyFilterType, \ref siShaderCustomDataType "siShaderCustomDataType",
		\xt cus_shaders_Params %Shader %Parameter Definitions \endxt
	\since 9.0 (2011)
	*/
	CStatus SetAttribute( const CString &in_name, const CValue &in_value );

	/*! Sets the ReadOnly capability.
	\param in_v true if texturable.
	\return Success/failure
	\sa ShaderParamDef::SetTexturable, ShaderParamDefOptions::SetAnimatable, ShaderParamDefOptions::SetInspectable,
		::siCapabilities, Parameter::PutCapabilityFlag, Parameter::GetCapabilities
	\since 11.0 (2013)
	*/
	CStatus SetReadOnly( bool in_v );

	private:
	ShaderParamDefOptions * operator&() const;
	ShaderParamDefOptions * operator&();
};

};

#endif

