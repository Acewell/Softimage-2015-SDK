//*****************************************************************************
/*!
   \file xsi_light.h
   \brief Light class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSILIGHT_H__
#define __XSILIGHT_H__

#include <xsi_directed.h>

namespace XSI {

class OGLLight;

//*****************************************************************************
/*! \class Light xsi_light.h
	\brief The Light object represents a Softimage light, such as a point light or a spot light.

	You can create lights with X3DObject::AddLight. To get an existing light from a LightRig, you can
	use LightRig::GetLight.

	\sa OGLLight

  	\eg
	\code
		using namespace XSI;
		Application app;
		Model root = app.GetActiveSceneRoot();

		Light myPointLight;
		root.AddLight( L"Point", false,L"MyLight" ,myPointLight );

		app.LogMessage( L"Light name: " + myPointLight.GetName() );
	\endcode
 */
//*****************************************************************************
class SICPPSDKDECL Light : public Directed
{
public:
	/*! Constructs a Light object. */
	Light();

	/*! Destroys a Light object. */
	~Light();

	/*! Constructs a Light object from a CRef object.
	\param in_ref A reference to a light.
	*/
	Light(const CRef& in_ref);

	/*! Constructs a new Light object from an existing Light object.
	\param in_obj An existing Light object to copy into this Light object.
	*/
	Light(const Light& in_obj);

	/*! Returns True if this object supports the functionality of a specified class. For example,
	a Light is a type of X3DObject, so a Light object supports X3DObject functionality.
	\param in_ClassID Test if this object supports this class.
	\return True if this object supports the specified class, and false otherwise.
	*/
	bool IsA( siClassID in_ClassID) const;

	/*! Returns the class ID for this object.
	\return The class ID.
	*/
	siClassID GetClassID() const;

	/*! Assigns a Light object to an existing Light object.
	\param in_obj A Light object to be copied into this object.
	\return The reinitialized Light object.
	*/
	Light& operator=(const Light& in_obj);

	/*! Assigns a CRef to this Light object. The Light object is cleared
	if the CRef is not a reference to an object that supports the Light class.
	\param in_ref A reference to an object that supports the Light class.
	\return The reinitialized Light object.
	*/
	Light& operator=(const CRef& in_ref);

	/*! Returns an array of references to the Shader objects connected to this light.
	\return An array of references to shader objects.
	\sa CRefArray, Shader
	*/
	CRefArray	GetShaders() const;

	/*! Returns the OGLLight for this light. The OGLLight object holds the light rendering
	information used by OpenGL. 

	\note The behavior of this method changed in Softimage 2013. 
	Previously, OGLLight was being re-evaluated for each data request.
	As of Softimage 2013, a snapshot of the OGLLight parameters is taken when calling  Light.GetOGLLight().
	This means that Light.GetOGLLight() needs to be called again when parameters affecting the OGLLight are modified.

	\return The OGLLight for this light.
	*/
	OGLLight	GetOGLLight() const;

	/*! Returns the input type of a light parameter. Before you connect a shader to the parameter, use
	Parameter::GetCapabilities to make sure that the parameter supports the ::siTexturable capability.
	\param in_paramscriptname The script name of a parameter.
	\return The shader input type. If the parameter cannot be connected to a shader, ::siUnknownParameterType is returned.
	\since 5.0
	*/
	siShaderParameterType GetShaderInputType(const CString& in_paramscriptname) const;

	/*! Returns all shaders that match a filter. For example, you can write a custom Filter that matches shaders with
	texturespace and colormap parameters, and then use this custom filter with this function.
	\param in_filtername The name of a shader Filter (for example, ::siShaderFilter).
	\return An array of shaders that match the filter.
	\since 5.0
	*/
	CRefArray FindShaders(const CString& in_filtername) const;

	/*! Returns a list of shaders nested under this Light.
	\return CRefArray of references to the nested Shader objects.
	\since 7.0
	*/
	CRefArray	GetAllShaders() const;

	/*! Returns a list of the image clips nested under this Light.
	\return CRefArray of references to the nested ImageClip2 objects.
	\sa Camera::GetAllImageClips, Material::GetAllImageClips, Pass:GetAllImageClips,
		Shader::GetAllImageClips, Override::GetAllImageClips
	\since 7.0
	*/
	CRefArray	GetAllImageClips() const;

	private:
	Light * operator&() const;
	Light * operator&();

};

};

#endif // __XSILIGHT_H__
