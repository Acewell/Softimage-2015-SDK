//*****************************************************************************
/*!
	\file xsi_shaderstructparamdef.h
	\brief ShaderStructParamDef class declaration.

	Copyright 2009 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSISHADERSTRUCTPARAMDEF_H__
#define __XSISHADERSTRUCTPARAMDEF_H__

#include <xsi_shaderparamdef.h>
#include <xsi_shaderparamdefcontainer.h>

namespace XSI {

//*****************************************************************************
/*! \brief Represents the Structure specialization of a shader parameter definition.

This object allows you to access the sub-elements contained by this shader parameter (ShaderStructParamDef::GetSubParamDefs,
which returns a list of sub parameter definitions in a ShaderParamDefContainer).

To create a ShaderStructParamDef object, specify the ::siShaderDataTypeStructure shader parameter type in the call to
ShaderParamDefContainer::AddParamDef or ShaderParamDefContainer::AddArrayParamDef.

\sa ShaderParamDefContainer::AddParamDef, ShaderParamDefContainer::AddArrayParamDef, ShaderParameter::GetDefinition,
	ShaderParamDefContainer, ShaderArrayParamDef, \xm ShaderDefinitions/netview_ShaderDefs Color Sampler example \endxm
\since 9.0 (2011)
 */
//*****************************************************************************

class SICPPSDKDECL ShaderStructParamDef : public ShaderParamDef
{
public:
	/*! Default constructor. */
	ShaderStructParamDef();

	/*! Default destructor. */
	~ShaderStructParamDef();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	ShaderStructParamDef(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	ShaderStructParamDef(const ShaderStructParamDef& in_obj);

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
	\return The new ShaderStructParamDef object.
	*/
	ShaderStructParamDef& operator=(const ShaderStructParamDef& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new ShaderStructParamDef object.
	*/
	ShaderStructParamDef& operator=(const CRef& in_ref);

	/*! Returns a ShaderParamDefContainer containing the sub parameter definitions for this struct parameter,
	which you can use to add new sub-parameters.
	\return Container for sub ShaderParamDef objects
	\sa ShaderParamDefContainer::AddParamDef, ShaderParamDefContainer::AddArrayParamDef
	\since 9.0 (2011)
	*/
	ShaderParamDefContainer GetSubParamDefs(  ) const;

	private:
	ShaderStructParamDef * operator&() const;
	ShaderStructParamDef * operator&();
};

};

#endif

