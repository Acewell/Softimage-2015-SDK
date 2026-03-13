//*****************************************************************************
/*!
	\file xsi_shaderarrayparamdef.h
	\brief ShaderArrayParamDef class declaration.

	Copyright 2009 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSISHADERARRAYPARAMDEF_H__
#define __XSISHADERARRAYPARAMDEF_H__

#include <xsi_shaderparamdef.h>

namespace XSI {

//*****************************************************************************
/*! \brief Represents a definition for a shader parameter (an instance a ShaderArrayParameter object).

This class allows you to set and get the array elements contained by this shader parameter via
ShaderArrayParamDef::GetItemInitialValues, which returns a ValueMap object that you can populate or query.

To create a %ShaderArrayParamDef object, use the ShaderParamDefContainer::AddArrayParamDef method when
adding a new parameter definition to the shader parameter definition container.

\sa ShaderParamDefContainer::AddParamDef, ShaderParamDefContainer::AddArrayParamDef, ShaderParameter::GetDefinition,
	ShaderParamDefContainer, ShaderStructParamDef, \xm ShaderDefinitions/netview_ShaderDefs Color Sampler example \endxm
\since 9.0 (2011)
 */
//*****************************************************************************

class SICPPSDKDECL ShaderArrayParamDef : public ShaderParamDef
{
public:
	/*! Default constructor. */
	ShaderArrayParamDef();

	/*! Default destructor. */
	~ShaderArrayParamDef();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	ShaderArrayParamDef(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	ShaderArrayParamDef(const ShaderArrayParamDef& in_obj);

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
	\return The new ShaderArrayParamDef object.
	\since 9.0 (2011)
	*/
	ShaderArrayParamDef& operator=(const ShaderArrayParamDef& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new ShaderArrayParamDef object.
	\since 9.0 (2011)
	*/
	ShaderArrayParamDef& operator=(const CRef& in_ref);


	/*! Returns the underlying ShaderParamDef or ShaderStructParamDef object for this array item.

	You can use this when you want to query an existing shader definition to find out information
	about its parameter definitions. For example, if you are writing a tool to find a parameter
	defined as an array of booleans.
	\return the parameter definition for the array item.
	\sa ShaderArrayParameter
	\since 9.0 (2011)
	*/
	ShaderParamDef GetItemDef(  ) const;

	/*! Returns number of array items that will be instantiated when the shader is connected.
	\return the array item's initial count.
	\sa ShaderArrayParamDef::GetItemName, ShaderArrayParamDef::PutItemName, ShaderArrayParamDef::PutItemName,
		ShaderArrayParamDef::GetItemInitialValues, ShaderArrayParameter
	\since 9.0 (2011)
	*/
	ULONG GetItemInitialCount(  ) const;

	/*! Sets the number of array items that will be instantiated when the shader is connected.
	\param in_count the array item's initial count.
	\return Success/failure
	\sa ShaderArrayParamDef::GetItemName, ShaderArrayParamDef::PutItemName, ShaderArrayParamDef::PutItemName,
		ShaderArrayParamDef::GetItemInitialValues, ShaderArrayParameter
	\since 9.0 (2011)
	*/
	CStatus PutItemInitialCount( ULONG in_count );

	/*! Returns the array item's initial values as a ValueMap. These values will be instantiated on
	the array items by default when the shader is connected.
	\return the array item's initial values.
	\sa ShaderArrayParamDef::GetItemName, ShaderArrayParamDef::PutItemName, ShaderArrayParamDef::GetItemInitialCount,
		ShaderArrayParamDef::PutItemInitialCount, ShaderArrayParameter
	\since 9.0 (2011)
	*/
	ValueMap GetItemInitialValues(  ) const;

	/*! Returns the array item's base name. When more than one array item based on this definition is
	instantiated, the base name is suffixed with an index ID. For example, if this property is set to
	\c "West", the first instance will be \c "West", the second will be \c "West[1]", the third \c "West[2]"
	and so on.

	\note This function has no effect on the display name (see ShaderParamDef::GetDisplayName).
	\return the array item's name.
	\sa ShaderArrayParamDef::GetItemInitialCount, ShaderArrayParamDef::PutItemInitialCount,
		ShaderArrayParamDef::GetItemInitialValues, ShaderArrayParameter, SIObject::GetName, Parameter::GetScriptName
	\since 9.0 (2011)
	*/
	CString GetItemName(  ) const;

	/*! Sets the array item's base name. When more than one array item based on this definition is instantiated,
	the base name is suffixed with an index ID. For example, if this property is set to \c "West", the first
	instance will be \c "West", the second will be \c "West[1]", the third \c "West[2]" and so on.

	\param in_name the Array Item's Name.
	\return Success/failure
	\sa ShaderArrayParamDef::GetItemInitialCount, ShaderArrayParamDef::PutItemInitialCount,
		ShaderArrayParamDef::GetItemInitialValues, ShaderArrayParameter, SIObject::GetName, Parameter::GetScriptName
	\since 9.0 (2011)
	*/
	CStatus PutItemName( const CString& in_name );

	/*! Returns whether the array can be resized or not.
	\return false if the array can be resized
	\return true otherwise
	\sa ShaderArrayParameter
	\since 9.0 (2011)
	*/
	bool GetStaticArray(  ) const;

	/*! Sets whether the array can be resized or not.
	\param in_static true for static array; false for dynamic.
	\return Success/failure
	\sa ShaderArrayParameter
	\since 9.0 (2011)
	*/
	CStatus PutStaticArray( bool in_static );

	private:
	ShaderArrayParamDef * operator&() const;
	ShaderArrayParamDef * operator&();
};

};

#endif

