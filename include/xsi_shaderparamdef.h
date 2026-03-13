//*****************************************************************************
/*!
	\file xsi_shaderparamdef.h
	\brief ShaderParamDef class declaration.

	Copyright 2009 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSISHADERPARAMDEF_H__
#define __XSISHADERPARAMDEF_H__

#include <xsi_valuemap.h>
#include <xsi_siobject.h>

namespace XSI {

//*****************************************************************************
/*! \brief Represents the definition of a ShaderParameter object.

%Shader parameter definitions are stored on the ShaderDef object in a special ShaderParamDefContainer object,
which allows you to access existing parameter definitions or add new ones. To access the ShaderParamDefContainer
object, call ShaderDef::GetInputParamDefs or ShaderDef::GetOutputParamDefs. From the ShaderParamDefContainer you
can add new parameter definitions by calling ShaderParamDefContainer::AddParamDef or
ShaderParamDefContainer::AddArrayParamDef with a set of ShaderParamDefOptions.

To access a specific shader parameter definition from an instantiated shader definition, use the
ShaderParamDefContainer::GetParamDefByName function. To iterate over the entire list of input or output parameter
definitions for an instantiated shader definition, use ShaderParamDefContainer::GetDefinitions.

To access existing shader parameter definitions from a ShaderParameter instance, use ShaderParameter::GetDefinition.

To add an array parameter (ShaderArrayParamDef), use ShaderParamDefContainer::AddArrayParamDef. For all other
parameter types, use ShaderParamDefContainer::AddParamDef.

\note This object is a generic interface. There are special accessors on the specializations of this class for the
	array and struct parameter types. See the ShaderArrayParamDef and ShaderStructParamDef reference pages for more
	details on these specializations.

\sa ShaderParamDefContainer::AddParamDef, ShaderParamDefContainer::AddArrayParamDef, ShaderParameter::GetDefinition,
 	ShaderParamDefContainer, \xt cus_shaders_Params %Shader %Parameter Definitions \endxt,
 	\xm ShaderDefinitions/netview_ShaderDefs Color Sampler example \endxm
\since 9.0 (2011)
 */
//*****************************************************************************

class SICPPSDKDECL ShaderParamDef : public SIObject
{
public:
	/*! Default constructor. */
	ShaderParamDef();

	/*! Default destructor. */
	~ShaderParamDef();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	ShaderParamDef(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	ShaderParamDef(const ShaderParamDef& in_obj);

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
	\return The new ShaderParamDef object.
	*/
	ShaderParamDef& operator=(const ShaderParamDef& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new ShaderParamDef object.
	*/
	ShaderParamDef& operator=(const CRef& in_ref);


	/*! Returns the list of attributes available on this parameter.
	\return attribute list
	\sa ShaderDef::GetAttributes
	\since 9.0 (2011)
	*/
	ValueMap GetAttributes(  ) const;

	/*! Returns a number (see ::siCapabilities) which is a bitfield of all the parameter's capabilities.
	For convenience, the texturable capability is exposed directly as ShaderParamDef::GetTexturable.

	To set the texturable, inspectable, and animatable capabilities on the shader parameter definition,
	you need to set them on the ShaderParamDefOptions object before calling the ShaderParamDefContainer::AddParamDef
	or ShaderParamDefContainer::AddArrayParamDef methods. For the texturable capability, the convenience
	method ShaderParamDef::SetTexturable is also available.
	\return the capability flags
	\sa ShaderParamDef::GetTexturable, ShaderParamDef::SetTexturable, Parameter::PutCapabilityFlag,
		Parameter::GetCapabilities, ShaderParamDefOptions::SetAnimatable, ShaderParamDefOptions::SetTexturable,
		ShaderParamDefOptions::SetInspectable
	\since 9.0 (2011)
	*/
	LONG GetCapabilities(  ) const;

	/*! Returns the default value for this parameter.
	\return the default value
	\since 9.0 (2011)
	*/
	CValue GetDefaultValue(  ) const;

	/*! Sets the default value for this parameter.
	\return the default value
	\sa ShaderParamDef::HasDefaultValue, ShaderParamDefOptions::SetDefaultValue, Parameter::GetValue, Parameter::PutValue
	\since 9.0 (2011)
	*/
	 CStatus SetDefaultValue( const CValue& in_value );

	/*! Returns the short name for this parameter definition. This is the name that appears in the %Scene Explorer
	(with the <tt>%View &gt; Use Script Names</tt> option turned \c OFF). It is also the same value that the
	SIObject::GetName property returns on the instance (ShaderParameter).

	\return the port display name.
	\sa ShaderParamDefOptions::SetShortName, SIObject::GetName
	\since 9.0 (2011)
	*/
	CString GetDisplayName(  ) const;

	/*! Indicates whether or not the parameter has a default value.
	\return true if the parameter has a default value
	\return false otherwise
	\sa ShaderParamDef::GetDefaultValue, ShaderParamDef::SetDefaultValue, ShaderParamDefOptions::SetDefaultValue,
		Parameter::GetValue, Parameter::PutValue
	\since 9.0 (2011)
	*/
	bool HasDefaultValue(  ) const;

	/*! Indicates whether or not the parameter is an array parameter (defined as ShaderArrayParamDef, or ShaderArrayParameter
	when instantiated). This is a convenience method for testing the following:

	\code ShaderParamDef::GetDataType == siShaderDataTypeArray \endcode
	\return true if the parameter is an array parameter
	\return false otherwise
	\sa ShaderArrayParamDef, ShaderParamDefContainer::AddArrayParamDef, ShaderArrayParameter
	\since 9.0 (2011)
	*/
	bool IsArray(  ) const;

	// Not implemented
	bool IsArrayItem(  ) const;

	/*! Indicates whether or not the parameter is an input parameter.
	\return true if the parameter is an input parameter
	\return false otherwise
	\sa ShaderDef::GetInputParamDefs, ShaderParamDef::IsOutput
	\since 9.0 (2011)
	*/
	bool IsInput(  ) const;

	/*! Indicates whether or not the parameter is an output parameter.
	\return true if the parameter is an output parameter
	\return false otherwise
	\sa ShaderDef::GetOutputParamDefs, ShaderParamDef::IsInput
	\since 9.0 (2011)
	*/
	bool IsOutput(  ) const;

	/*! Indicates whether or not the parameter is a structure parameter (true if it is). This is a
	convenience method for testing the following:

	\code ShaderParamDef::GetDataType == siShaderDataTypeStructure \endcode
	\return true if the parameter is a structure parameter.
	\return false otherwise
	\sa ShaderStructParamDef
	\since 9.0 (2011)
	*/
	bool IsStructure(  ) const;

	/*! Indicates whether or not the port is the main port.
	\return true if the port is the main port
	\return false otherwise
	\since 9.0 (2011)
	*/
	bool GetMainPort(  ) const;

	/*! Sets this port as the main port.
	\param in_main true if the port is the main port; false otherwise
	\since 9.0 (2011)
	*/
	CStatus PutMainPort( bool in_main );

	/*! Returns the maximum allowable value for this parameter.
	\return the maximum value
	\sa ShaderParamDefOptions::SetHardLimit, ShaderParamDef::SetMaxValue, ShaderParamDef::GetMinValue,
		ShaderParamDef::GetSuggestedMaxValue, Parameter::GetMax
	\since 9.0 (2011)
	*/
	CValue GetMaxValue(  ) const;

	/*! Sets the maximum allowable value for this parameter.
	\param in_value the maximum value
	\return Success/failure
	\sa ShaderParamDefOptions::SetHardLimit, ShaderParamDef::GetMaxValue, ShaderParamDef::SetMinValue,
		ShaderParamDef::SetSuggestedMaxValue, Parameter::GetMax
	\since 9.0 (2011)
	*/
	 CStatus SetMaxValue( const CValue& in_value );

	/*! Returns the minimum allowable value for this parameter.
	\return the minimum value
	\sa ShaderParamDefOptions::SetHardLimit, ShaderParamDef::SetMinValue, ShaderParamDef::GetMaxValue,
		ShaderParamDef::GetSuggestedMinValue, Parameter::GetMin
	\since 9.0 (2011)
	*/
	CValue GetMinValue(  ) const;

	/*! Sets the minimum allowable value for this parameter.
	\param in_value the minimum value
	\return Success/failure
	\sa ShaderParamDefOptions::SetHardLimit, ShaderParamDef::GetMinValue, ShaderParamDef::SetMaxValue,
		ShaderParamDef::SetSuggestedMinValue, Parameter::GetMin
	\since 9.0 (2011)
	*/
	 CStatus SetMinValue( const CValue& in_value );

	/*! Returns one of the ::siShaderParameterDataType enum values corresponding to this shader parameter's type.
	\return the data type
	\sa ShaderParameter::GetDataType
	\since 9.0 (2011)
	*/
	siShaderParameterDataType GetDataType(  ) const;

	/*! Returns the suggested maximum value for this parameter.
	\return the suggested maximum value.
	\sa ShaderParamDefOptions::SetSoftLimit, ShaderParamDef::SetSuggestedMaxValue, ShaderParamDef::GetSuggestedMinValue,
		ShaderParamDef::GetMaxValue, Parameter::GetSuggestedMax
	\since 9.0 (2011)
	*/
	CValue GetSuggestedMaxValue(  ) const;

	/*! Sets the suggested maximum value for this parameter.
	\param in_value the suggested maximum value
	\return Success/failure
	\sa ShaderParamDefOptions::SetSoftLimit, ShaderParamDef::GetSuggestedMaxValue, ShaderParamDef::SetSuggestedMinValue,
		ShaderParamDef::SetMaxValue, Parameter::GetSuggestedMax
	\since 9.0 (2011)
	*/
	 CStatus SetSuggestedMaxValue( const CValue& in_value );

	/*! Returns the suggested minimum value for this parameter.
	\return the suggested minimum value
	\sa ShaderParamDefOptions::SetSoftLimit, ShaderParamDef::SetSuggestedMinValue, ShaderParamDef::GetSuggestedMaxValue,
		ShaderParamDef::GetMinValue, Parameter::GetSuggestedMin
	\since 9.0 (2011)
	*/
	CValue GetSuggestedMinValue(  ) const;

	/*! Sets the suggested minimum value for this parameter.
	\param in_value the suggested minimum value
	\return Success/failure
	\sa ShaderParamDefOptions::SetSoftLimit, ShaderParamDef::GetSuggestedMinValue, ShaderParamDef::SetSuggestedMaxValue,
		ShaderParamDef::SetMinValue, Parameter::GetSuggestedMin
	\since 9.0 (2011)
	*/
	 CStatus SetSuggestedMinValue( const CValue& in_value );

	/*! Indicates whether or not the texturable capability (see ::siCapabilities) is set. This is a convenience for accessing
	it using ShaderParamDef::GetCapabilities.

	\note When a shader parameter is texturable, it can be connected to other shader ports in the render tree.
	\return the texturable flag.
	\sa ShaderParamDef::GetCapabilities, Parameter::GetCapabilities, Parameter::PutCapabilityFlag
	\since 9.0 (2011)
	*/
	bool GetTexturable(  ) const;

	/*! Sets whether or not the texturable capability (see ::siCapabilities) is set. This is a convenience for accessing
	it using ShaderParamDef::GetCapabilities.

	\note Making a shader parameter texturable means that it can connect to other shader ports in the render tree.
	\return Success/failure
	\sa ShaderParamDefOptions::SetTexturable, ShaderParamDef::GetCapabilities, Parameter::PutCapabilityFlag
	\since 9.0 (2011)
	*/
	CStatus SetTexturable( bool in_value );

	/*! Sets the short name for this parameter definition. This is the name that appears in the %Scene Explorer
	(with the <tt>%View &gt; Use Script Names</tt> option turned \c OFF). 

	\sa ShaderParamDefOptions::SetShortName, SIObject::GetName	
	*/
	CStatus SetDisplayName( const CString &in_str );

	private:
	ShaderParamDef * operator&() const;
	ShaderParamDef * operator&();
};

};

#endif

