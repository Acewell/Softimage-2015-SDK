//*****************************************************************************
/*!
   \file xsi_customprimitivecontext.h
   \brief CustomPrimitiveContext class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __CUSTOMPRIMITIVECONTEXT_H__
#define __CUSTOMPRIMITIVECONTEXT_H__

#include <xsi_base.h>
#include <xsi_value.h>
#include <xsi_time.h>
#include <xsi_context.h>

namespace XSI {

//*****************************************************************************
/*! \class CustomPrimitiveContext xsi_customprimitivecontext.h
	\brief This class is provided as the context object in the CustomPrimitive ConvertToGeom
	callback for a CustomPrimitive object (see PluginRegistrar::RegisterCustomPrimitive).

	The Context::GetUserData and Context::PutUserData functions provide a convenient way
	to store non-persisted, per-instance state information for the custom primitive.  A common pattern
	is to use user data to store a pointer to C++ objects that actually implement the custom primitive
	algorithm and store its state.

	\sa CustomPrimitive, PluginRegistrar
	\since 12.0 (2014)
*/
//*****************************************************************************

class SICPPSDKDECL CustomPrimitiveContext : public Context
{
public:

	/*! Default constructor. */
	CustomPrimitiveContext();

	/*! Default destructor. */
	~CustomPrimitiveContext();

	/*! Constructor.
	\param in_ref Constant reference object.
	*/
	CustomPrimitiveContext(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj Constant class object.
	*/
	CustomPrimitiveContext(const CustomPrimitiveContext& in_obj);

	/*! Returns true if a given class type is compatible with this API class.
	\param in_ClassID Class type.
	\return True if the class is compatible, false otherwise.
	*/
	bool IsA( siClassID in_ClassID) const;

	/*! Returns the type of the API class.
	\return The class type.
	*/
	siClassID GetClassID() const;

	/*! Creates an object from another object.
	\param in_obj Constant class object.
	\return The new CustomPrimitiveContext object.
	*/
	CustomPrimitiveContext& operator=(const CustomPrimitiveContext& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref Constant class object.
	\return The new CustomPrimitiveContext object.
	*/
	CustomPrimitiveContext& operator=(const CRef& in_ref);

	/*! Returns the output geometry during the ConvertToGeom callback. This will only be valid during
	the ConvertToGeom callback. The callback can then populate the geometry as necessary to complete
	the conversion.

	\return A reference to the %XSI object being written
	*/
	CRef GetGeometry() const;

	private:
	CustomPrimitiveContext * operator&() const;
	CustomPrimitiveContext * operator&();
};

};
#endif // __CUSTOMPRIMITIVECONTEXT_H__
