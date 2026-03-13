//*****************************************************************************
/*!
   \file xsi_renderercontext.h
   \brief RendererContext class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIRENDERERCONTEXT_H__
#define __XSIRENDERERCONTEXT_H__

#include <xsi_base.h>
#include <xsi_value.h>
#include <xsi_context.h>
#include <xsi_time.h>

namespace XSI {

class Framebuffer;
class Property;

/*! \class RendererImageFragment xsi_renderercontext.h
	\brief This abstract class needs to be implemented by the rendering engine to provide image fragments
	to Softimage. The fragment should be contained fully within the crop window given in the RenderContext
	object's attribute list.
	\since 6.01
*/

class RendererImageFragment
{
public:
	/*! Returns the offset of the fragment's bottom-left corner from the
	left-hand side of the output frame.
	\return The horizontal offset of the fragment.
	*/
	virtual unsigned int GetOffsetX( ) const = 0;

	/*! Returns the offset of the fragment's bottom-left corner from the bottom of
	the output frame.
	\return The vertical offset of the fragment.
	*/
	virtual unsigned int GetOffsetY( ) const = 0;

	/*! Returns the width of the fragment in pixels.
	\return The fragment's width.
	*/
	virtual unsigned int GetWidth( ) const = 0;

	/*! Returns the height of the fragment in pixels.
	\return The fragment's height.
	*/
	virtual unsigned int GetHeight( ) const = 0;

	/*! Returns a single fragment scanline. The row is relative to the bottom of the fragment, going up. The caller
	can request different bit depths of the image data. By default, ::siImageBitDepthInteger8 is assumed to be supported.
	The renderer can declare explicit bit depth support through the ::siRenderQueryDisplayBitDepths query code in the
	\xt cb_Renderer_Query Query \endxt callback. The bit depth requested is the same as returned by
	Framebuffer::GetDisplayBitDepth, from RendererContext::GetDisplayFramebuffer.

	The data is laid out in RGBA format, where the red value comes first, followed by green, then blue and finally alpha.

	The scanline data buffer passed contains enough space to hold the equal to the fragment's width times four (for the
	RGBA components) times the bit depth divided by eight. For bit depths larger than a byte, the values should be given
	in little endian format.

	\param in_uiRow The scanline row to return, counting from the bottom of the fragment.
	\param in_eBitDepth The requested bit depth of the color components to be returned.
	\retval out_pScanline The buffer where the scanline data should be written.
	\return True if the data was successfully written; false in the case of a failure
		(for example, unsupported bit depth, invalid row number, etc.)
	*/
	virtual bool GetScanlineRGBA( unsigned int in_uiRow, siImageBitDepth in_eBitDepth, unsigned char *out_pScanline ) const = 0;
};


//*****************************************************************************
/*! \class RendererContext xsi_renderercontext.h
	\brief This object is provided as the context object in the %Renderer callbacks for a Plugin-based
	\xt cus_render Custom %Renderer \endxt object.

	\sa PluginRegistrar::RegisterRenderer
	\since 6.0
*/
//*****************************************************************************

class SICPPSDKDECL RendererContext : public Context
{
public:

	/*! Default constructor. */
	RendererContext();

	/*! Default destructor. */
	~RendererContext();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	RendererContext(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	RendererContext(const RendererContext& in_obj);

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
	\return The new RendererContext object.
	*/
	RendererContext& operator=(const RendererContext& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new RendererContext object.
	*/
	RendererContext& operator=(const CRef& in_ref);

	/*! Returns the time at which the render process is occurring. The renderer should use
	this to set the evaluation time for the scene data being rendered. In the case of field
	rendering, or motion blurring, this time should be used as the base for which to derive
	other time stops.
	\return The time at which the current frame is being rendered.
	\since 6.01
	*/
	CTime GetTime() const;

	/*! Returns the zero-based index of the frame being rendered within the rendered sequence.
	The sequence starts at zero and counts in ascending order. For single-frame renders, this
	function always returns zero. For sequence renders the highest value is always one less
	than the return value of RendererContext::GetSequenceLength.
	\return The sequence index of the current frame.
	\since 6.01
	*/
	unsigned int GetSequenceIndex( ) const;

	/*! Returns the length of the sequence being rendered. For single frames, this function
	always returns 1.
	\return The number of frames in the sequence currently being rendered.
	\since 6.01
	*/
	unsigned int GetSequenceLength( ) const;

	/*! Notifies %XSI as to what the current status of the rendering process is.
	\param in_strProgressShort Short progress message (when using the small progress bar).
	\param in_strProgressLong Longer progress message (when using the big progress bar or
		the render viewer).
	\param in_iPercentage The percentage of the job done, if it can be indicated, or -1
	\return CStatus::OK
	\since 6.01
	*/
	CStatus ProgressUpdate( const CString &in_strProgressShort, const CString &in_strProgressLong, int in_iPercentage );

	/*! Notifies the render manager that a new frame is about to be sent to whichever render
	viewer might be listening for frame fragments. In the case of field rendering, both
	frames should be sent to the viewer.
	\param in_uiWidth The width of the new frame (needs to be the same as the value of the
		\c ImageWidth context parameter).
	\param in_uiHeight The height of the new frame (needs to be the same as the value of the
		\c ImageHeight context parameter).
	\return CStatus::OK
	\since 6.01
	*/
	CStatus NewFrame( unsigned int in_uiWidth, unsigned int in_uiHeight );

	/*! Passes back a new frame fragment to the render manager. See RenderImageFragment for more details.
	\retval in_fragment The new RenderImageFragment
	\return CStatus::OK
	\since 6.01
	*/
	CStatus NewFragment( const RendererImageFragment &in_fragment );

	/*! Triggers a specific render event. At the moment only ::siOnBeginFrame, ::siOnEndFrame,
	::siOnBeginSequence, ::siOnEndSequence and ::siOnRenderAbort are supported.
	\param in_eEventID The event being called.
	\param in_eRenderingType The type of rendering being performed.
	\param in_rTime The time at which the render event is occurring. Only relevant for ::siOnBeginFrame and ::siOnEndFrame.
	\param in_filenames The list of filenames being rendered out. In case of ::siOnBeginSequence and ::siOnEndSequence
		these should be time-independent filenames, which can be accessed by calling Framebuffer::GetResolvedPath with no parameters.
	\param in_eFieldType The field being rendered, or ::siRenderFieldNone if not rendering fields.
	\param siRenderingErrorType The type of error for ::siOnRenderAbort, defaults to siRenderNoError.
	
	\return CStatus::OK The event was sent successfully.
	\return CStatus::Abort The render was aborted while the event was being processed or the event
		requested an abort. The render should abort immediately at this point with a status code
		of CStatus::Fail.
	\since 6.01
	*/
	CStatus TriggerEvent( siEventID in_eEventID, siRenderingType in_eRenderingType, const CTime &in_rTime, const CStringArray &in_filenames, siRenderFieldType in_eFieldType, siRenderingErrorType in_eRenderErrorType );

	// For back-comp.
	CStatus TriggerEvent( siEventID in_eEventID, siRenderingType in_eRenderingType, const CTime &in_rTime, const CStringArray &in_filenames, siRenderFieldType in_eFieldType );

	/*! Returns the renderer's option property evaluated at a specific time. Which particular property
	instance this is, is dependent upon who triggered the render (pass, region, shaderballs, etc.)
	\param in_rTime The time to evaluate the property at.
	\return The evaluated renderer option property.
	\since 6.01
	*/
	Property GetRendererProperty( const CTime &in_rTime );

	/*! Returns the Framebuffer object whose contents should be sent back as an image fragment to the
	render manager via RendererContext::NewFragment. If the %Framebuffer object is not valid then no
	fragments are needed for viewing (for example when doing a command-line render or archive export).
	The display framebuffer also dictates the bit depth which the RenderImageFragment object should
	return its fragment data as. The object returned by this function is not guaranteed to
	be found in the list of %Framebuffer objects returned by GetFramebuffers.
	\return The Framebuffer object selected for viewing.
	\since 6.01
	*/
	Framebuffer GetDisplayFramebuffer( );

	/*! Returns all Framebuffer objects that should be rendered for the current frame.
	\return An array of references to Framebuffer objects.
	\since 6.01
	*/
	CRefArray GetFramebuffers( );

	/*! Marks the given object from the dirty list as being clean. This only affects the
	next call to the renderer's \xt cb_Renderer_Process Process \endxt callback, if the render
	got aborted and restarted. It does not update the copy of the dirty list, retrieved from
	Context::GetAttribute. It's up to the caller to ensure they stay synchronised during the
	callback.

	This call is used to ensure that if the render gets restarted, for example due to a
	parameter values change, that the renderer does not have to re-update its copy of scene
	data that it considers 'clean'. The dirty list is cleared by Softimage upon the completion
	of a successful render.

	\note If the renderer gets called with a 'full' list (i.e. the "DirtyList" attribute is
	not defined), then the renderer should call this with an empty CRef object once the scene
	has been syncrhonised. Any attempts to clear out individual items with a "full" list will
	otherwise result in a "full" list still being given on next render. It is up to the renderer
	in this case to keep a map of which objects it has synchronised with, perhaps using the
	"RenderID" attribute to associate a synchronisation map with the current render.

	\note If an object was changed by the user during the Process callback, it will show up
	in the next call, whether it got marked clean or not.
	\param in_ref The object to mark as clean and remove from the dirty list for the next
		call to the \xt cb_Renderer_Process Process \endxt callback.
	\since 9.0 (2011)
	*/
	CStatus SetObjectClean( const CRef& in_ref );


	private:
	RendererContext * operator&() const;
	RendererContext * operator&();
};

};
#endif // __XSIRENDERERCONTEXT_H__
