//*****************************************************************************
/*!
   \file xsi_customprimitive.h
   \brief CustomPrimitive class declaration.

	Copyright 2012 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSICUSTOMPRIMITIVE_H__
#define __XSICUSTOMPRIMITIVE_H__

#include <xsi_primitive.h>
#include <xsi_status.h>

namespace XSI {

//*****************************************************************************
/*! \class CustomPrimitive xsi_customprimitive.h
	\brief The CustomPrimitive class represents a custom primitive object. A custom primitive object is an implicit primitive 
	where the representation is fully defined by user. Defining the representation is done via the callbacks (_Define, _DefineLayout, _PPGEvent, _Draw, _BoundingBox, _ConvertToGeom) for Custom Primitive.  

	A custom primitive object can be created using the GetPrim command. It can be converted into a PolygonMesh using the SIConvert command if the ConvertToGeom callback is specified.

	See the custom primitive example in the SDK workgroup for examples on how to define a custom primitive object.

	\sa PluginRegistrar::RegisterPrimitive, Primitive

	\since 12.0 (2014)
 */
//*****************************************************************************

class SICPPSDKDECL CustomPrimitive : public Primitive
{
public:
	/*! Default constructor. */
	CustomPrimitive();

	/*! Default destructor. */
	~CustomPrimitive();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	CustomPrimitive(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	CustomPrimitive(const CustomPrimitive& in_obj);

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
	\return The new CustomPrimitive object.
	*/
	CustomPrimitive& operator=(const CustomPrimitive& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new CustomPrimitive object.
	*/
	CustomPrimitive& operator=(const CRef& in_ref);

	/*! Adds a new parameter to the custom primitive object.
	\param  in_paramdef The parameter definition (created via Factory::CreateParamDef)
	\param  io_parameter Returns the new Parameter object.
	\return CStatus::OK success
	\return CStatus::Fail failure
	\since 12.0 (2014)
	*/
	CStatus AddParameter(
		const CRef& in_paramdef,
		Parameter&	io_parameter );

	/*! Removes the specified parameter from the custom primitive.
	\param  in_param Parameter to remove.
	\return CStatus::OK success
	\return CStatus::Fail failure
	\since 12.0 (2014)
	*/
	CStatus RemoveParameter( const Parameter& in_param );


};

};

#endif // __XSICUSTOMPIMITIVE_H__
