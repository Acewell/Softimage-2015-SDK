//*****************************************************************************
/*!
   \file xsi_hardwareshadercontext.h
   \brief HardwareShaderContext class declaration.

	Copyright 2010 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIHARDWARESHADERCONTEXT_H__
#define __XSIHARDWARESHADERCONTEXT_H__

#include <xsi_base.h>
#include <xsi_value.h>
#include <xsi_context.h>
#include <xsi_time.h>
#include <xsi_material.h>
#include <xsi_x3dobject.h>
#include <xsi_hardwaresurface.h>
#include <xsi_hardwareattribute.h>

namespace XSI {

class Shader;
class Camera;

//*****************************************************************************
/*! \class HardwareShaderContext xsi_hardwareshadercontext.h
	\brief This object is provided as the context object in the execution callback
	of a hardware shader.

	\sa PluginRegistrar::RegisterShader
	\since 9.0 (2011)
*/
//*****************************************************************************

class SICPPSDKDECL HardwareShaderContext : public Context
{
public:

	/*! Default constructor. */
	HardwareShaderContext();

	/*! Default destructor. */
	~HardwareShaderContext();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	HardwareShaderContext(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	HardwareShaderContext(const HardwareShaderContext& in_obj);

	/*! Returns true if a given class type is compatible with this API class.
	\param in_ClassID class type.
	\return true if the class is compatible, false otherwise.
	*/
	bool IsA( siClassID in_ClassID) const;

	/*! Returns the type of the API class.
	\return The class type.
	*/
	siClassID GetClassID() const;

	/*! Creates an object from another object.
	\param in_obj constant class object.
	\return The new HardwareShaderContext object.
	*/
	HardwareShaderContext& operator=(const HardwareShaderContext& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new HardwareShaderContext object.
	*/
	HardwareShaderContext& operator=(const CRef& in_ref);

	/*! Returns the Shader object which is being drawn in the viewport.
	\return The Shader object being drawn in the viewport.
	*/
	Shader GetShader( );

	/*! Returns the Shader object which is being drawn in the viewport.
		Use this method if you plan to access parameters with a time
		different than the current time (causing an evaluation)
	\return The Shader object being drawn in the viewport.
	*/
	Shader GetShaderForAnimation( );

	/*! Returns the Camera object which is associated with the viewport currently being refreshed.
	\return The Camera object.
	\since 9.0 (2011)
	*/
	Camera GetCamera( );

	/*! Returns the parent Material object.
	\return The Material parent object of the hardware shader.
	*/
	Material GetMaterial( );

	/*! Returns the X3DObject associated with the shader.
	\return The X3DObject object. Returns an invalid object if called outside the Execute phase.
	*/
	X3DObject GetX3DObject( );

	/*! Returns an array of all XSI::Light objects contained in the scene.
	\return CRefArray Array of XSI::Light objects.
	*/
	CRefArray GetLights();

	/*! Returns a unique identifier for the hardware shader.
	\return Unique identifier.
	*/
	ULONG GetShaderUniqueID ();

	/*! Returns the time at which the viewport redraw is occurring. The shader should use
	this to set the evaluation time for the scene data being drawn.
	\return The time at which the current frame is being drawn.
	*/
	CTime GetTime() const;

	/*! Get the index list making up the triangles for this object. The type is defined by GetIndexWidth.
	\return A list of triangle indices as defined by the XSI_RTS_Primitive::m_pIndices.
	*/
	void* GetTriangleIndices();

	/*! The size of each index (4=UINT, 2=USHORT, 1=UBYTE) returned by GetTriangleIndices.
	\return Array of triangle indices.
	*/
	UINT GetIndexWidth();

	/*! The total number of indices returned by GetTriangleIndices. Divide the returned value by 3 if you want to
	get the number of triangles.
	\return Array of indices.
	*/
	ULONG GetNbIndices();

	/*! Get the base offset.
	*/
	ULONG GetBaseOffset();

	/*! Get the number of unique vertices making up the geometry
	\return Array of vertex indices.
	*/
	ULONG GetNbVertices();

	/*! Return the hardware attribute array associated to a given context.
	*/
	CHardwareAttributeArray	GetHardwareAttributeArray();

	/*! Returns true if the geometry has changed since the last time the frame was drawn.
	\return Returns true if the geometry has changed, false otherwise.
	*/
	bool IsGeometryDirty() const;

	/*! Returns the transformation of the object, or the current instance of the object being drawn.
	\return The Transformation object.
	*/
	MATH::CTransformation GetTransform() const;

	/*! Must be called by the hardware shader for drawing the primitive as triangle elements.
	\param in_eDriver The graphic driver to use for drawing.
	*/
	void DrawPrimitive( siGraphicDriver in_eDriver ) const;

	/*! Must be called by the hardware shader for drawing the primitive as 4 points polygon.
	\param in_eDriver The graphic driver to use for drawing.
	*/
	void DrawScreenAlignedQuad( siGraphicDriver in_eDriver ) const;

	/*! Creates a new hardware surface object.
	\param in_options Options for creating the hardware surface.
	\return New hardware surface
	*/
	HardwareSurface CreateHardwareSurface( HardwareSurface::Options& in_options );

	/*! Sets the current render target for the specified draw buffer index.
	\param in_nDrawBufferIndex Draw buffer index.
	\param in_surface The hardware surface to use as target.
	*/
	void SetRenderTarget( UINT in_nDrawBufferIndex, HardwareSurface& in_surface );

	/*! Sets the current render depth/stencil target
	*/
	void SetRenderDepthStencilTarget( HardwareSurface& in_surface );

	/*! Return the current graphic driver .
	\return The current graphic driver
	*/
	CRef GetGraphicDriver() const;

	/*! Returns an array of XSI::HardwareSurface representing the Screen Space Shadow Maps.
		A Screen Space Shadow map can be used by a realtime shaders by doing a screen space lookup.
		A single shadow map can store the shadow intensity for up to 4 lights in individual color components.
		The out_lights parameter returns a list of lights that uses each shadow map color component.
		For example, if 5 lights cast shadows, the method will return 2 HardwareSurface with 5 lights in out_lights.
		The red, green, blue and alpha components in the first HardwareSurface map to the shadow intensity of the first 4 lights.
		The red component of the second HardwareSurface maps to fifth light.
		The shadow map is in screen space, so a simple texture lookup is enough to retreive the shadow intensity for 4 lights at a time.
	\param out_lights Light list ordered by shadow map component. 
	\return CRefArray Array of XSI::HardwareSurface objects or an Empty array if no shadow surfaces were computed.
	*/
	CRefArray GetShadowSurfaces( XSI::CRefArray& out_lights ) const;

	/*! Returns the parameters from the render tree which values have changed since the last shader evaluation. These parameters are 
	available for the next evaluation only. The shader renderer must be set with the XSI::siHWShaderPropertyUpdateAttribute option to enable this mechanism.
	\return Parameter objects.
	\sa XSI::siHWShaderPropertyUpdateAttribute
	\since 10.5 (2012)
	*/
	CParameterRefArray GetDirtyParameters() const;

	private:
	HardwareShaderContext * operator&() const;
	HardwareShaderContext * operator&();
};

};
#endif // __XSIRENDERERCONTEXT_H__
