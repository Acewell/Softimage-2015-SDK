//*****************************************************************************
/*!
   \file xsi_arrayparameter.h
   \brief ShaderArrayParameter class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSI_SHADERARRAYPARAMETER_H__
#define __XSI_SHADERARRAYPARAMETER_H__

#include <xsi_status.h>
#include <xsi_shaderparameter.h>

namespace XSI {

// *******************************************************************
/*! \brief Represents an array parameter for a Shader.

	An array parameter is a specialization of the ShaderParameter class which contains a set of %ShaderParameter
	objects. These types of parameters are useful for supporting a dynamic number of instances of parameters.
	For example, the \xp Softimage_March_Fractal_vol_1_0 Volume Effects \endxp shader defines an array parameter
	of light references labeled \c scatter_lights_input that allows you to add any number of lights.

	It can contain any number of sub-parameters, all of the same type. Its contents can be moved around, new
	parameters added and old ones removed.

	These type of parameters can be defined using the ShaderArrayParamDef interface.

	\sa ArrayParameter, ShaderParameter
    \since 9.0 (2011)
*/
// *******************************************************************

class SICPPSDKDECL ShaderArrayParameter : public ShaderParameter
{
public:
	/*! Constructs an ShaderArrayParameter object. */
	ShaderArrayParameter( );

	/*! Destroys an ShaderArrayParameter object. */
	~ShaderArrayParameter( );

	/*! Constructs an ShaderArrayParameter object from a reference to another ShaderArrayParameter object.
	\param in_ref A reference to a group.
	*/
	ShaderArrayParameter(const CRef& in_ref);

	/*! Constructs a new ShaderArrayParameter object from an existing ShaderArrayParameter object.
	\param in_obj An existing Group object to copy into this Group object.
	*/
	ShaderArrayParameter(const ShaderArrayParameter& in_obj);

	/*! Returns true if this object supports the functionality of a specified class. For example,
	an ShaderArrayParameter is a type of ShaderParameter, so an ShaderArrayParameter object supports
	ShaderParameter functionality.
	\param in_ClassID Test if this object supports this class.
	\return True if this object supports the specified class, and false otherwise.
	*/
	bool IsA( siClassID in_ClassID) const;

	/*! Returns the class ID for this object.
	\return The class ID.
	*/
	siClassID GetClassID() const;

	/*! Assigns an ShaderArrayParameter object to an existing ShaderArrayParameter object.
	\param in_obj An ShaderArrayParameter object to be copied into this object.
	\return The reinitialized ShaderArrayParameter object.
	*/
	ShaderArrayParameter& operator=(const ShaderArrayParameter& in_obj);

	/*! Assigns a CRef to this ShaderArrayParameter object. The ShaderArrayParameter object is cleared if the CRef is not
	a reference to an object that supports the ShaderArrayParameter class.
	\param in_ref A reference to an object that supports the ShaderArrayParameter class.
	\return The reinitialized ShaderArrayParameter object.
	*/
	ShaderArrayParameter& operator=(const CRef& in_ref);

	/*! Returns the parameter at a given index. If the index is out of bounds, this operator returns an
	empty, invalid ShaderParameter object.
	\param in_index Integer index of the parameter to get.
	\return The parameter at the given index
	\return Empty parameter if the index is out of bounds
	*/
	ShaderParameter operator[]( LONG in_index );

	/*! Returns the size of the array. If the array is empty or invalid, \c 0 is returned.
	\return The number of parameters in the array.
	\since 9.0 (2011)
	*/
	LONG GetCount( ) const;

	/*! Appends a new parameter to this array. The type of the new parameter is determined by the definition
	of the array parameter. This corresponds to clicking the \b Add button for the shader array parameter
	section on the shader's property page.

	\return The new parameter. If the array is static, an invalid ShaderParameter object is returned.
	\sa ShaderArrayParamDef, ShaderArrayParameter::Remove
	\since 9.0 (2011)
	*/
	ShaderParameter Add( );

	/*! Removes the item from this array that matches the specified index. This corresponds to choosing \b Remove
	from an item's context menu in the UI.
	\param in_lIndex The index of the parameter to remove.
	\return CStatus::OK if succeeded.
	\return CStatus::Fail if the index is out of bounds.
	\sa ShaderArrayParameter::Add
	\since 9.0 (2011)
	*/
	CStatus Remove( LONG in_lIndex );

	/*! Removes the specified item from this array. This corresponds to choosing \b Remove from an item's context
	menu in the UI.
	\param in_parameter ShaderParameter to remove.
	\return CStatus::OK if successful.
	\return CStatus::Fail if the parameter is not a member of the array.
	\sa ShaderArrayParameter::Add
	\since 9.0 (2011)
	*/
	CStatus Remove( const ShaderParameter &in_parameter );

	/*! Removes all items from this array. This corresponds to clicking the \b Clear button for the shader array
	parameter section on the shader's property page.
	\return CStatus::OK if successful.
	\since 9.0 (2011)
	*/
	CStatus Clear( );

	/*! Moves a parameter up or down in the array relative to its current position. The new position of
	the parameter is calculated by adding \c in_lUpDown to the current index and clamping the result to
	the array boundaries (0 to ShaderArrayParameter::GetCount - 1).
	\param in_lIndex The index of the parameter to move.
	\param in_lUpDown Positive or negative amount to move the parameter.
	\return CStatus::OK if successful.
	\return CStatus::Fail if the index is out of bounds.
	\since 9.0 (2011)
	*/
	CStatus Move( LONG in_lIndex, LONG in_lUpDown );

	/*! Moves a given parameter up or down in the array relative to its current position. The new position
	of the parameter is calculated by adding \c in_lUpDown to the current index and clamping the result to
	the array boundaries (0 to ShaderArrayParameter::GetCount - 1).
	\param in_parameter The parameter to move.
	\param in_lUpDown Positive or negative amount to move the parameter.
	\return CStatus::OK if successful.
	\return CStatus::Fail if the given parameter is not a member of the array.
	\since 9.0 (2011)
	*/
	CStatus Move( const ShaderParameter &in_parameter, LONG in_lUpDown );

private:
	ShaderArrayParameter* operator&() const;
	ShaderArrayParameter* operator&();

};

};

#endif // __XSI_SHADERARRAYPARAMETER_H__
