//*****************************************************************************
/*!
   \file xsi_renderer.h
   \brief Renderer class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIRENDERER_H__
#define __XSIRENDERER_H__

#include <xsi_status.h>
#include <xsi_longarray.h>

namespace XSI {

//*****************************************************************************
/*! \class Renderer xsi_renderer.h
	\brief This object is provided as the source object available from the
	RendererContext for a Plugin-based \xt cus_render Custom %Renderer \endxt object.

	\sa PluginRegistrar::RegisterRenderer
	\since 6.01
*/
//*****************************************************************************

class SICPPSDKDECL Renderer : public SIObject
{
public:

	/*! Default constructor. */
	Renderer();

	/*! Default destructor. */
	~Renderer();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	Renderer(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	Renderer(const Renderer& in_obj);

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
	\return The new Renderer object.
	*/
	Renderer& operator=(const Renderer& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new Renderer object.
	*/
	Renderer& operator=(const CRef& in_ref);


	/*! Sets the types of processes this rendering engine can handle as a list of ::siRenderProcessType
	enumeration values.
	\note This function should only be called from the renderer's \xt cb_Renderer_Init Init \endxt
		callback. In any other callback it has no effect.
	\param in_types List of process types supported by this renderer.
	\return CStatus::OK Process types set successfully
	\return CStatus::Fail No valid process types given.
	\return CStatus::AccessDenied Not in initialization mode.
	*/
	CStatus PutProcessTypes( const CLongArray &in_types );

	/*! Returns all the process types that this renderer supports as a list of ::siRenderProcessType
	enumeration values.
	\return List of process types supported by this renderer.
	*/
	CLongArray GetProcessTypes( );

	/*! Returns true if this renderer supports a specific process types.
	\param in_eProcessType The process type to query (one of the ::siRenderProcessType enum values)
	\return Boolean indicating whether the given process type is supported.
	*/
	bool HasProcessType( siRenderProcessType in_eProcessType );

	/*! Sets the name of the scene archive format and the default extension if the renderer
	supports scene render archives. The caller can also indicate whether the scene archive
	format supports multi-frame output to a single archive file.
	\note This function should only be called from the renderer's
		\xt cb_Renderer_Init Init \endxt callback. In any other callback
		it has no effect.
	\param in_strName The name of the format to use. This is used for display
		purposes, such as browsing.
	\param in_strExtension The standard file extension used for the format. This
		is appended automatically when creating archive output file paths from the
		archive filename template.
	\param in_bMultiFrame True if the archive format supports multiple frames in a
		single file. Otherwise %XSI always writes out separate files for each frame.
	\return CStatus::OK Archive settings set successfully.
	\return CStatus::AccessDenied Not in initialization mode.
	*/
	CStatus PutArchiveFormat( const CString &in_strName, const CString &in_strExtension, bool in_bMultiFrame );

	/*! Returns the name, file extension and multi-frame capability of the scene archive
	format used by this renderer.
	\note This function should only be called if the renderer supports the siRenderProcessExportArchive
		process type.
	\retval out_strName The name of the scene archive format.
	\retval out_strExtension The filename extension that's used for the format.
	\retval out_bMultiFrame True if the archive supports multiple frames in a single file.
	\return CStatus::OK Archive settings retrieved successfully.
	\return CStatus::Fail The renderer does not support the siRenderProcessExportArchive
		process type.
	*/
	CStatus GetArchiveFormat( CString &out_strName, CString &out_strExtension, bool &out_bMultiFrame );

	/*! Sets the name of the object archive format and the default extension if the renderer
	supports object render archives. The caller can also indicate whether the object archive
	format supports multi-frame output to a single archive file; and whether the archive
	export can generate images representing the contents of the object archive, for display
	purposes.
	\note This function should only be called from the renderer's
		\xt cb_Renderer_Init Init \endxt callback. In any other callback
		it has no effect.
	\param in_strName The name of the format to use. This is used for display
		purposes, such as browsing.
	\param in_strExtension The standard file extension used for the format. This
		is appended automatically when creating archive output file paths from the
		archive filename template.
	\param in_bMultiFrame True if the archive format supports multiple frames in a
		single file. Otherwise %XSI always writes out separate files for each frame.
	\param in_bDisplayProxy True if the archive export can generate low-resolution proxy
		images for a viewport display of the object archive. There should be three
		images, projected on the XY, XZ and YZ axes, and covering the entire bounding box
		of the object archive's contents.
	\return CStatus::OK Archive settings set successfully.
	\return CStatus::AccessDenied Not in initialization mode.
	*/
	CStatus PutObjectArchiveFormat( const CString &in_strName, const CString &in_strExtension, bool in_bMultiFrame, bool in_bDisplayProxy );

	/*! Returns the name, file extension, multi-frame and display proxy capability of the
		object archive format used by this renderer.
	\note This function should only be called if the renderer supports the siRenderProcessExportObjectArchive
		process type.
	\retval out_strName The name of the scene archive format.
	\retval out_strExtension The filename extension that's used for the format.
	\retval out_bMultiFrame True if the archive supports multiple frames in a single file.
	\retval out_bDisplayProxy True if the renderer can generate display proxies with the archive.
	\return CStatus::OK Archive settings retrieved successfully.
	\return CStatus::Fail The renderer does not support the siRenderProcessExportObjectArchive
		process type.
	*/
	CStatus GetObjectArchiveFormat( CString &out_strName, CString &out_strExtension, bool &out_bMultiFrame, bool &out_bDisplayProxy );

	/*! Adds a new property that should be created for the specified type. The last property
	added for a specified type will be the one used.
	\note This function should only be called from the renderer's
		\xt cb_Renderer_Init Init \endxt callback. In any other callback
		it has no effect.
	\param in_eType The type of render property associated with the property given.
	\param in_strName The name of the property to create for the render property type.
	\return CStatus::OK Property type added successfully.
	\return CStatus::AccessDenied Not in initialization mode.
	*/
	CStatus AddProperty( siRenderPropertyType in_eType, const CString &in_strName );

	/*! Returns the object or scripting name of the given renderer property. This can be
	used with SceneItem.GetProperties to get the appropriate property from the Pass, PassContainer
	and others.
	\param in_eType Specific renderer property name to retrieve.
	\param in_bScriptingName Whether to get the scripting name or not.
	\return The name of the property.
	*/
	CString GetPropertyName( siRenderPropertyType in_eType, bool in_bScriptingName = false );

	/*! Adds a new output image format that is supported by this renderer. The
	format will be available to the user to select for controlling which output
	format to write the rendered framebuffers out as. Used with Renderer::AddOutputImageFormatSubType
	to create a complete output image format description.
	\note This function should only be called from the renderer's
		\xt cb_Renderer_Init Init \endxt callback. In any other callback
		it has no effect.
	\param in_strName The name of the format as shown to the user.
	\param in_strExtension The format's extension.
	\return CStatus::OK Image format definition begin accepted.
	\return CStatus::AccessDenied Not in initialization mode.
	*/
	CStatus AddOutputImageFormat( const CString &in_strName, const CString &in_strExtension );

	/*! Returns all output image formats registered by this renderer as a pair of equal-sized
	lists, containing the format name and the associated filename extension. Items
	at the same index on the two lists should be taken together.
	\retval out_names The names of the output image formats.
	\retval out_extensions The filename extensions used for the output iamage formats.
	\return CStatus::OK
	*/
	CStatus GetOutputImageFormats( CStringArray &out_names, CStringArray &out_extensions );

	/*! Adds a new sub-type to the image format. The sub-type is based on a render channel type
	and controls which formats, and sub-types thereof, will be offered to the user based on the
	render channel type of the render channel on which a framebuffer is based.
	\note This function should only be called from the renderer's
		\xt cb_Renderer_Init Init \endxt callback. In any other callback
		it has no effect.
	\param in_eChannelType Render channel type to associate this image format sub-type with.
	\param in_strDataType The data type being output from the render channel.
	\param in_eBitDepth The resolution of each individual component of the data type.
	\return CStatus::OK Sub-type successfully added.
	\return CStatus::AccessDenied Not in initialization mode or an output image format has not
		been added yet.
	*/
	CStatus AddOutputImageFormatSubType( siRenderChannelType in_eChannelType, const CString &in_strDataType, siImageBitDepth in_eBitDepth );

	/*! Returns all image format sub-types for a given output image format. Either the format
	name or its extension can be used to look up the sub-type data. The sub-types are returned
	as three lists of equal size containing the channel type the sub-type applies to, the
	data type and the bitdepth the image format can be written out as for the given channel type.
	Items on each list at the same index should be taken together.
	\param in_strName Either the name or the filename extension of a registered output image
		format for this renderer.
	\retval out_channelTypes The channel types list.
	\retval out_dataTypes The data types list.
	\retval out_bitDepths The resolution of each individual component of the data type.
	*/
	CStatus GetOutputImageFormatSubTypes( const CString &in_strName, CLongArray &out_channelTypes, CStringArray &out_dataTypes, CLongArray &out_bitDepths );

	/*! Adds a new default channel for this renderer. A default channel is a render channel
	which is automatically filled in by the renderer if it has been added with a framebuffer
	to a given pass.
	\note This function should only be called from the renderer's
		\xt cb_Renderer_Init Init \endxt callback. In any other callback
		it has no effect.
	\param in_strName The name of the default channel being added.
	\param in_eChannelType The channel type of the default channel being added.
	\return CStatus::OK Default channel successfully added.
	\return CStatus::AccessDenied Not in initialization mode.
	*/
	CStatus AddDefaultChannel( const CString &in_strName, siRenderChannelType in_eChannelType );

	/*! Returns all default channels registered by this renderer as a pair of equal-sized lists,
	containing the channel name and the channel type. Items at the same index on the two lists
	should be taken together.
	\retval out_names The names of the default channels.
	\retval out_channelTypes The channel types of the respective default channels.
	\return CStatus::OK
	*/
	CStatus GetDefaultChannels( CStringArray &out_names, CLongArray &out_channelTypes );

	/*! Get the renderer's version identifier. The version identifier has no specific format
		and should only be used to disambiguate different versions of the renderer. This is
		useful to keep separate the plugin's and the rendering engine's version identifiers.
		\note If a custom renderer does not support the version query callback, this
			will return the plugin's major.minor version instead.
		\return The renderer's version identifier.
	*/
	CString GetVersionString( );

	/*! Locks the scene data from modification while the render data is being pushed. It is very
	important that this function be called before any other SDK access function is called, otherwise
	other running threads could potentially modify the data while the rendering thread is trying
	to access it.

	If the function returns CStatus::Abort the render callback should return with CStatus::Abort to
	indicate to the render controller that an abort has been successfully received. In that case
	Renderer::UnlockSceneData should not be called, since the lock has been rejected anyway.
	\note This function should only be called from the renderer's
		\xt cb_Renderer_Process Process \endxt and \xt cb_Renderer_Cleanup Cleanup \endxt  
		callbacks. In any other callback it has no effect.
	\return CStatus::OK The scene data is locked.
	\return CStatus::Abort The rendering engine is being aborted and should return immediately.
	\return CStatus::AccessDenied Not rendering.
	*/
	CStatus LockSceneData( );

	/*! Unlocks the scene data after locking. It is important that Renderer::LockSceneData
	be paired with this function, otherwise the scene database could be left locked after the
	render process is done, leaving %XSI in a locked up state.
	\note This function should only be called from the renderer's
		\xt cb_Renderer_Process Process \endxt and \xt cb_Renderer_Cleanup Cleanup \endxt  
		callbacks. In any other callback it has no effect.
	\return CStatus:OK The scene data is now unlocked.
	\return CStatus::AccessDenied Not rendering.
	*/
	CStatus UnlockSceneData( );

	private:
	Renderer * operator&() const;
	Renderer * operator&();
};

};
#endif // __XSIRENDERER_H__
