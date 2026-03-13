//*****************************************************************************
/*!
   \file xsi_pass.h
   \brief Pass class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIPASS_H__
#define __XSIPASS_H__

#include <xsi_sceneitem.h>

namespace XSI {

class CLongArray;
class Framebuffer;
class Partition;
class RenderChannel;
class Renderer;
class CTime;

//*****************************************************************************
/*! \class Pass xsi_pass.h
	\brief A render pass creates a picture layer of a scene that can be composited with any other pass to create
	a complete image. Passes also allow you to quickly re-render a single layer without re-rendering the entire
	scene. Later you can composite the rendered passes using the Softimage FX Tree, the fully-integrated compositing
	and effects toolset, or another compositing tool of your choice.

	Each scene can contain as many render passes as you need. When you first create a scene in Softimage, it has a
	single pass named \c Default_pass. This is a "beauty pass" that is set to render every element of the scene. You
	can render a single beauty pass or you can render separate passes. Also, you can use preset passes such as matte,
	shadow, toon, and highlight, or you can create your own passes.

	\sa Scene::GetActivePass, Scene::GetPasses, PassContainer::AddPass, Partition
	\sa \xl GetCurrentPass, \xl CreatePass, \xl DeleteCurrentPass
 */
//*****************************************************************************

class SICPPSDKDECL Pass : public SceneItem
{
public:
	/*! Default constructor. */
	Pass();

	/*! Default destructor. */
	~Pass();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	Pass(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	Pass(const Pass& in_obj);

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
	\return The new Pass object.
	*/
	Pass& operator=(const Pass& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new Pass object.
	*/
	Pass& operator=(const CRef& in_ref);


	/*! Returns a list of Framebuffer objects on the pass. The framebuffers control
	which RenderChannel objects the pass will output to disk.
	\return An array of references to the Framebuffer objects on the Pass.
	\since 6.0
	*/
	CRefArray GetFramebuffers( );

	/*! Adds a new framebuffer to the pass based on the named RenderChannel. The
	render channel has to exist, otherwise no framebuffer is added.
	\param in_channelName Name of the render channel to base the new framebuffer on.
	\return The newly created framebuffer.
	\since 6.0
	*/
	Framebuffer CreateFramebuffer( const CString &in_channelName );

	/*! Adds a new framebuffer to the pass based on the specified render channel.
	\param in_renderChannel The RenderChannel object to base the new framebuffer on.
	\return The newly created framebuffer.
	\since 6.0
	*/
	Framebuffer CreateFramebuffer( RenderChannel &in_renderChannel );

	/*! Returns the list of frame numbers that are going to be rendered by this pass. The
	list depends on the \xp %Pass %Pass parameters \endxp \c FrameRangeSource, \c FrameSet,
	\c FrameStep, \c FrameStart, and \c FrameEnd.
	\return An array of integer values or an empty array in case of failure.
	\since 6.01
	*/
	CLongArray GetFrames();


	/*! Takes the output archive path template given in the pass and resolves it to a real
	path name for the specified time.
	See section "Output Path Templates" in the Softimage User Guide for more details.
	\param in_rTime The time at which to resolve the path template. Controls the result of
		the \c [Frame] and \c [Field] tokens.
	\return The resolved archive path template at the given time.
	\sa Framebuffer::GetResolvedPath \xl %XSIUtils.ResolveTokenString
	\since 6.01
	*/
	CString GetResolvedArchivePath( const CTime &in_rTime );

	/*! Takes the output archive path template given in the pass and resolves it to a
	time-independent path, where any instance of \c [Frame] is substituted with the
	a sequence of \c # symbols, that represent the current frame number and padding width.
	See section "Output Path Templates" in the Softimage User Guide for more details.
	\return The time-independent resolved archive path template.
	\sa Framebuffer::GetResolvedPath \xl %XSIUtils.ResolveTokenString
	\since 6.01
	*/
	CString GetResolvedArchivePath( );

	/*! Returns the rendering engine selected for use for this pass.
	\return This pass' rendering engine.
	\since 7.0
	*/
	Renderer GetRenderer( ) const;

	/*! Returns a list of all Partition objects that exist on this pass. This includes all
	object and light partitions, whether they're background or not.
	\return An array of references to the Partition objects on the Pass.
	\since 7.0
	*/
	CRefArray GetPartitions( ) const;

	/*! Creates a new Partition and adds it to this Pass.
	\param in_name The name of the partition to create. If a partition already exists with
	the same name, the new partition's name will be modified to avoid a naming clash.
	\param in_type The type of partition to create.
	\return The newly created Partition.
	\since 7.0
	*/
	Partition CreatePartition( const CString &in_name, XSI::siPartitionType in_type );

	/*! Returns a list of shaders nested under this Pass.
	\return CRefArray of references to the nested Shader objects.
	\since 7.0
	*/
	CRefArray	GetAllShaders() const;

	/*! Returns a list of the image clips nested under this Pass.
	\return CRefArray of references to the nested ImageClip2 objects.
	\sa Light::GetAllImageClips, Camera::GetAllImageClips, Material:GetAllImageClips,
		Shader::GetAllImageClips, Override::GetAllImageClips
	\since 7.0
	*/
	CRefArray	GetAllImageClips() const;

	private:
	Pass * operator&() const;
	Pass * operator&();
};

};

#endif // __XSIPASS_H__
