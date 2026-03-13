//*****************************************************************************
/*!
	\file xsi_shaderparameter.h
	\brief ShaderParameter class declaration.

	Copyright 2009 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSISHADERPARAMETER_H__
#define __XSISHADERPARAMETER_H__

#include <xsi_parameter.h>
#include <xsi_shaderparamdef.h>

namespace XSI {

//*****************************************************************************
/*! \brief Represents a shader parameter as a specialization of the Parameter interface on a Shader.

	This interface also has its own specialization for shader array parameters: ShaderArrayParameter.
	\sa Shader, Parameter
	\since 9.0 (2011)
 */
//*****************************************************************************

class SICPPSDKDECL ShaderParameter : public Parameter
{
public:
	/*! Default constructor. */
	ShaderParameter();

	/*! Default destructor. */
	~ShaderParameter();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	ShaderParameter(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	ShaderParameter(const ShaderParameter& in_obj);

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
	\return The new ShaderParameter object.
	*/
	ShaderParameter& operator=(const ShaderParameter& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new ShaderParameter object.
	*/
	ShaderParameter& operator=(const CRef& in_ref);


	/*! Returns the shader parameter definition as a ShaderParamDef object.
	\return the ShaderParamDef object
	\since 9.0 (2011)
	*/
	ShaderParamDef GetDefinition(  ) const;

	/*! Returns one of the ::siShaderParameterDataType enum values corresponding to this shader parameter's data type.
	\return Data type for this shader parameter
	\sa ShaderParamDef::GetDataType
	\since 9.0 (2011)
	*/
	siShaderParameterDataType GetDataType(  ) const;

	/*! Returns the shader parameter targets connected to this parameter.
	\return Array of references to the targets
	\since 9.0 (2011)
	*/
	CRefArray GetTargets(  ) const;

	private:
	ShaderParameter * operator&() const;
	ShaderParameter * operator&();
};

};

#endif

