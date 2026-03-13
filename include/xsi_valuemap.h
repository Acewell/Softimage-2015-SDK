//*****************************************************************************
/*!
	\file xsi_valuemap.h
	\brief ValueMap class declaration.

	Copyright 2009 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIATTRIBUTEMAP_H__
#define __XSIATTRIBUTEMAP_H__

#include <xsi_siobject.h>

namespace XSI {

//*****************************************************************************
/*! \brief Represents a special container to hold key-value pairs, similar to an associative array.

A value map is set of name-value pairs defined for a ShaderDef, a ShaderParamDef, a ShaderArrayParamDef, or a MetaShaderRendererDef.
This is the equivalent of a dictionary or associative array.

\tip There is no GetCount function implemented on this object, but you can use the ValueMap::GetAll function which returns the list
of names and the list of values defined in this ValueMap.

\sa ShaderDef::GetAttributes, ShaderParamDef::GetAttributes, ShaderArrayParamDef::GetItemInitialValues,
	MetaShaderRendererDef::GetRendererOptions, \xm ShaderDefinitions/netview_ShaderDefs Color Sampler example \endxm
\since 9.0 (2011)
 */
//*****************************************************************************

class SICPPSDKDECL ValueMap : public SIObject
{
public:
	/*! Default constructor. */
	ValueMap();

	/*! Default destructor. */
	~ValueMap();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	ValueMap(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	ValueMap(const ValueMap& in_obj);

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
	\return The new ValueMap object.
	*/
	ValueMap& operator=(const ValueMap& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new ValueMap object.
	*/
	ValueMap& operator=(const CRef& in_ref);


	/*! Returns the value that matches the specified name.

	\par Warning:
		If the value is undefined, this method throws an error. You can work around this limitation
		by accessing the names and values array using the same index.
	\param in_name the name of the value to retrieve.
	\return the value matching the specified name
	\sa ValueMap::Set, ValueMap::GetAll
	\since 9.0 (2011)
	*/
	CValue Get( const CString& in_name ) const;

	/*! Returns the lists of all names and all values defined in this ValueMap in two separate output arrays.
	\param out_names array of names
	\param out_values array of values
	\return Success/failure
	\sa ValueMap::Set, ValueMap::Get, ValueMap::Remove
	\since 9.0 (2011)
	*/
	CStatus GetAll( CValueArray& out_names, CValueArray& out_values ) const;

	/*! Removes the value that matches the specified name. If no item matches that name, nothing happens.
	\param in_name The name of the value to remove.
	\return Success/failure
	\sa ValueMap::GetAll
	\since 9.0 (2011)
	*/
	CStatus Remove( const CString& in_name );

	/*! Sets the value that matches the specified name. If no entry exists matching this name, it automatically
	adds the name-value pair. If an entry matching that name already exists, the value is updated.
	\param in_name The name of the value to set.
	\param in_value The value to set.
	\return Success/failure
	\sa ValueMap::Get, ValueMap::GetAll
	\since 9.0 (2011)
	*/
	CStatus Set( const CString& in_name, const CValue& in_value );

	private:
	ValueMap * operator&() const;
	ValueMap * operator&();
};

};

#endif

