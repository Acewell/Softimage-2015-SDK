//*****************************************************************************
/*!
	\file xsi_graphicdriver.h
	\brief GraphicDriver class declaration.

	Copyright 2010 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIGRAPHICDRIVER_H__
#define __XSIGRAPHICDRIVER_H__

#include <xsi_siobject.h>

namespace XSI {

//*****************************************************************************
/*!
	\class GraphicDriver xsi_graphicdriver.h
	\brief The GraphicDriver class encapsulates the graphic driver currently set for
	drawing hardware shaders.

	\sa HardwareShaderContext
	\since 9.0 (2011)
 */
//*****************************************************************************
class SICPPSDKDECL GraphicDriver : public SIObject
{
public:
	/*! Default constructor. */
	GraphicDriver();

	/*! Default destructor. */
	~GraphicDriver();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	GraphicDriver(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	GraphicDriver(const GraphicDriver& in_obj);

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
	\return The new GraphicDriver object.
	*/
	GraphicDriver& operator=(const GraphicDriver& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new GraphicDriver object.
	*/
	GraphicDriver& operator=(const CRef& in_ref);

	/*! Returns a siGraphicDriver enum indicating the type of graphic driver.
	\return	The graphic driver type.
	*/
	siGraphicDriver	GetGraphicDriverType();

	/*! Returns a void* which represents the interface to the underlying Graphics API.
		for OpenGL, this simple returns a HGLRC. For DirectX based divers,
		you get an IUnknown which can be used to retrieved the DirectX device.
		\return Pointer to the hardware graphic interface.
	*/
	void* GetHardwareInterface();

	/*! Adds a resource to the driver. The implementation and meaning of this method differs
		from driver to driver. For DirectX9, the parameter is a pointer to an IUnknown. You should
		use this function when you create a resource that is not automatically managed by the DirectX
		driver and that needs to be manually restored when the DirectX device is reset. For example,
		if you create a HLSL shader (ID3DXEffect) in your plugin, you must pass the IUnknown pointer of
		this effect using AddDriverResource. The driver will then take care of managing the states when
		the device is released.

		\param Pointer to a resource for a given graphic API type.
		\return CStatus::OK for success
	*/
	CStatus AddDriverResource( void* in_pRes );

	private:
	GraphicDriver * operator&() const;
	GraphicDriver * operator&();
};

};

#endif

