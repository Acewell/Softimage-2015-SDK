//*****************************************************************************
/*!
   \file xsi_scenerenderproperty.h
   \brief SceneRenderProperty class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSI_SCENERENDERPROPERTY_H__
#define __XSI_SCENERENDERPROPERTY_H__

#include <xsi_property.h>

namespace XSI {

class RenderChannel;
class Renderer;

//*****************************************************************************
/*! \class SceneRenderProperty xsi_scenerenderproperty.h
	\brief This object represents a scene render property.
	The scene render property controls common render settings for
	all passes in the scene and the render region. The property allows
	to quickly change a common set of options, such as the rendering
	engine, field rendering, motion blur and resolution, that will
	apply to all rendering options that derive from it. The property
	is a singleton and is only found under "Passes.RenderOptions".

	The scene render property also lists the current set of render
	channels applicable to the system. RenderChannel objects can be
	listed, added and removed using the property's methods. Framebuffer
	objects can be created from render channels in order to output
	them to disk. Render channels can also be directly viewed in the
	render region.

	\sa Framebuffer RenderChannel Pass Property Scene
	\since 6.0
 */
//*****************************************************************************

class SICPPSDKDECL SceneRenderProperty : public Property
{
public:
	/*! Default constructor. */
	SceneRenderProperty();

	/*! Default destructor. */
	~SceneRenderProperty();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	SceneRenderProperty(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	SceneRenderProperty(const SceneRenderProperty& in_obj);

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
	\return The new SceneRenderProperty object.
	*/
	SceneRenderProperty& operator=(const SceneRenderProperty& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new SceneRenderProperty object.
	*/
	SceneRenderProperty& operator=(const CRef& in_ref);

	/*! Returns all the render channels currently available in the scene.
	\return Array of references to each RenderChannel object.
	\sa Framebuffer RenderChannel Pass Scene
	*/
	CRefArray GetRenderChannels();

	/*! Creates a new render channel. The render channel is immediately visible to the
	render region but requires a Framebuffer to be created from it in order to be
	available to a Pass.
	\param in_Name The name for the new channel. If the name already exists, it will
		be modified and the new channel will have the modified name.
	\param in_eType The type of render channel to create.
	\return The newly created render channel.
	\sa Framebuffer RenderChannel Pass
	*/
	RenderChannel CreateRenderChannel( const CString &in_Name, siRenderChannelType in_eType );

	/*! Removes an already existing user-defined render channel by name. If the channel
	doesn't exist the function returns CStatus::InvalidArgument.
	\warning It is not possible to remove channels provided by the renderer (if
		RenderChannel::GetUserDefined returns \c false ).
	\param in_channelName The name of the render channel to remove.
	\return CStatus::OK Succeeded
	\return CStatus::InvalidArgument No channel exists with the name given.
	\return CStatus::AccessDenied Couldn't remove render channel because it is not
		user-defined.
	\sa RenderChannel::GetUserDefined Framebuffer RenderChannel Pass
	*/
	CStatus RemoveRenderChannel( const CString &in_channelName );

	/*! Removes the input user-defined RenderChannel object.
	\warning It is not possible to remove channels provided by the renderer (if
		RenderChannel::GetUserDefined returns \c false ).
	\param in_renderChannel The render channel to remove.
	\return CStatus::OK Succeeded
	\return CStatus::AccessDenied Couldn't remove render channel because it is not
		user-defined.
	\sa RenderChannel::GetUserDefined Framebuffer RenderChannel Pass
	*/
	CStatus RemoveRenderChannel( RenderChannel &in_renderChannel );

	/*! Returns the rendering engine selected for the scene.
	\return The scene global rendering engine.
	\since 7.0
	*/
	Renderer GetRenderer( );

private:
	SceneRenderProperty * operator&() const;
	SceneRenderProperty * operator&();
};

};

#endif // __XSI_SCENERENDERPROPERTY_H__
