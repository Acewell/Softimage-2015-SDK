//*****************************************************************************
/*!
   \file xsi_pickbuffer.h
   \brief PickBuffer class declaration.

	Copyright 2011 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIPICKBUFFER_H__
#define __XSIPICKBUFFER_H__
#include <xsi_base.h>

namespace XSI {

//*****************************************************************************
/*! \class PickBuffer xsi_pickbuffer.h
	\brief This class provides access to a picking buffer returned from ToolContent::GetPickBuffer.

	\sa ToolContext::GetPickBuffer
    \since 10.0 (2012)
 */
//*****************************************************************************
class SICPPSDKDECL PickBuffer : public CBase
{
public:
	/*! Default constructor. */
	PickBuffer();

	/*! Default destructor. */
	~PickBuffer();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	PickBuffer(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	PickBuffer(const PickBuffer& in_obj);

	/*! Returns true if a given class type is compatible with this API class.
	\param in_ClassID class type.
	\return true if the class is compatible, false otherwise.
	*/
	bool IsA(siClassID in_ClassID) const;

	/*! Returns the type of the API class.
	\return The class type.
	*/
	siClassID GetClassID() const;

	/*! Creates an object from another object. The newly created object is set to
	empty if the input object is not compatible.
	\param in_obj constant class object.
	\return The new Image object.
	*/
	PickBuffer& operator=(const PickBuffer& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new Image object.
	*/
	PickBuffer& operator=(const CRef& in_ref);

	/*! Retrieve object at the specified view coordinates.
	\param x View X coordinate in pixels.
	\param y View Y coordinate in pixels.
	\return Object at specified view coordinates. If no object is found an invalid reference is returned.
	*/
	CRef GetObjectAtPosition( LONG x, LONG y ) const;

	/*! Retrieve component index at the specified view coordinates. For a pick buffer
	generated using ::siObjectFilter the component index will return 0 if there is an
	object at the specified location. This can be used as a quick way to test for
	objects.
	\param x View X coordinate in pixels.
	\param y View Y coordinate in pixels.
	\return Component index or -1 if no component at specified coordinates.
	*/
	LONG GetComponentIndexAtPosition( LONG x, LONG y ) const;

	private:
	PickBuffer * operator&() const;
	PickBuffer * operator&();
};

};

#endif // __XSIPICKBUFFER_H__
