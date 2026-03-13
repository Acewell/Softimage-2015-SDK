//*****************************************************************************
/*!
   \file xsi_hardwareattribute.h
   \brief CHardwareAttribute and CHardwareAttributeArray class declarations.

	Copyright 2010 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIHARDWAREATTRIBUTE_H__
#define __XSIHARDWAREATTRIBUTE_H__

#include "sicppsdk.h"
#include "xsi_ref.h"
#include "xsi_value.h"
#include "xsi_string.h"

namespace XSI {

class CHardwareAttributeArray;

//*****************************************************************************
/*! \class CHardwareAttribute xsi_hardwareattribute.h

	\brief Represents an attribute defined by hardware shaders a.k.a real-time shaders.
	CHardwareAttribute is typically used for defining standard vertex semantics (siHardwareInputSemantic)
	used in shader languages such as CgFX and HLSL. CHardwareAttribute can also be used for
	defining shader parameters of siShaderParameterType type.

	Hardware attributes are defined through the hardware shader's GetAttributeList callback.
	\since 9.0 (2011)
*/
//*****************************************************************************

class SICPPSDKDECL CHardwareAttribute
{
public:

	/*! Default constructor. */
	CHardwareAttribute();

	/*! Default destructor. */
	virtual ~CHardwareAttribute();

	/*! Constructor.
	\param valSrc CHardwareAttribute object
	*/
	CHardwareAttribute(const CHardwareAttribute& valSrc);

	/*! Assignment
	\param valSrc CHardwareAttribute value
	*/
	CHardwareAttribute& operator=(const CHardwareAttribute& valSrc);

	/*! Comparison
	\param valSrc CHardwareAttribute value
	*/
	bool operator==(const CHardwareAttribute& valSrc) const;

	/*! Inequality
	\param valSrc CHardwareAttribute value
	*/
	bool operator!=(const CHardwareAttribute& valSrc) const;

	/*! Put the value for the selected semantic
	\parma inSemantic	siHardwareInputSemantic semantic
	\param valSrc CValue value
	*/
	CStatus	PutSemanticValue ( const siHardwareInputSemantic inSemantic, const CValue& valSrc);

	/*! Gets the semantic
	*/
	XSI::siHardwareInputSemantic GetSemantic() const;

	/*! Gets the value
	*/
	XSI::CValue GetSemanticValue () const;

	/*! set the attribute data and type
	*/
	CStatus SetAttributeData (XSI::CValue in_data, XSI::siShaderParameterType in_type, ULONG in_ulArraySize );

	/*! Get the attribute data
	*/
	XSI::CValue GetAttributeData ();

	/*! Get the attribute data
	*/
	XSI::siShaderParameterType GetAttributeType ();

	/*! Get the size of the array (returns 1 if the data is not an array)
	*/
	ULONG GetAttributeArraySize();

	void*	m_pImpl;

};

//*************************************************************************
/*! \class CHardwareAttributeArray xsi_hardwareattribute.h
	\brief The CHardwareAttributeArray is an uni-dimensional array of CHardwareAttribute.

	The array is zero-based, which means that the first item index is 0 and the larger index
	is one less that the number of elements contained in the array.

	\sa CHardwareAttribute
*/
//*************************************************************************
class SICPPSDKDECL CHardwareAttributeArray
{
public:
	/*! Constructs a CHardwareAttributeArray and optionally initializes the array to a known size.
	\param in_size Size of array, defaults to 0.
	*/
	CHardwareAttributeArray(LONG in_size=0);

	/*! Constructs a CHardwareAttributeArray object from another CHardwareAttributeArray object.
	\param in_array constant CHardwareAttributeArray object.
	*/
	CHardwareAttributeArray(const CHardwareAttributeArray& in_array);

	/*! Default destructor. */
	~CHardwareAttributeArray();

	/*! Assignment operator.
	\param in_array constant class object.
	\return A reference to this array.
	*/
	CHardwareAttributeArray& operator=( const CHardwareAttributeArray& in_array );

	/*! Returns the number of items in this CHardwareAttributeArray
	\return The number of items in the array.
	*/
	LONG GetCount() const;

	/*! Adds a CHardwareAttribute at the end of this array's.
	\param in_item New item to be added at the end of the array.
	\return CStatus::OK success
	*/
	CStatus Add( const CHardwareAttribute& in_item );

	/*! Erases all elements contained in the array.
	\return CStatus::OK success
	*/
	CStatus Clear();

	/*! Reallocates memory for the array, preserves its contents if the new size is larger
	than existing size.
	\param in_size New size of the array.
	\return CStatus::OK success
	\return CStatus::InvalidArgument in_size < 0
	*/
	CStatus Resize( LONG in_size);

	/*! Accessor to elements at a given index. This function can only be called by constant
	objects, the returned value is read-only.
	\param in_index index in this zero-based array.  The index must be greater or equal to zero
		and smaller than the number of element in the array, otherwise the results are unpredictable.
	\return A read-only reference to the indexed item.
	*/
	const CHardwareAttribute& operator[]( LONG in_index ) const;

	/*! Accessor to elements at a given index.
	\param in_index index in this zero-based array.  The index must be greater or equal to zero
		and smaller than the number of element in the array, otherwise the results are unpredictable.
	\return A reference to the indexed item.
	*/
	CHardwareAttribute& operator[]( LONG in_index );

	/*! Equality operator.
	\param in_array CHardwareAttributeArray to compare with.
	\return true if in_array contains the same number of elements as this array and if all members
		of in_array are equal to the corresponding one contained in this array.
	*/
	bool operator==(const CHardwareAttributeArray& in_array) const;

	/*! Inequality
	\param in_array
	\return true if one member of in_array is different from the corresponding members in this
		array or if the arrays are not of the same size.
	*/
	bool operator!=(const CHardwareAttributeArray& in_array) const;


private:

	void* m_ptr;
};


};

#endif // __XSIHARDWAREATTRIBUTE_H__
