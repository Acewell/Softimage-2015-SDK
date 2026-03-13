//*****************************************************************************
/*!
   \file xsi_graphicsequencer.h
   \brief CGraphicSequencer class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIXSIGRAPHICSEQUENCER_H__
#define __XSIXSIGRAPHICSEQUENCER_H__

#include <xsi_decl.h>
#include <xsi_status.h>
#include <xsi_ref.h>
#include <xsi_material.h>
#include <xsi_graphicdriver.h>
#include <xsi_time.h>
#include <xsi_camera.h>

namespace XSI {

class RendererContext;
class Renderer;

//*****************************************************************************
/*! \class CGraphicSequencer xsi_graphicsequencer.h
	\brief The CGraphicSequencer object offers several services to enable custom rendering passes in the OpenGL viewport.

	You cannot instantiate a CGraphicSequencer object directly. Rather, you receive an instance when your XGS plug-ins
	are called; that is, in a Custom Display callback or a Custom OpenGL %Pass.

	\sa GraphicSequencerContext, ::siViewMode, ::siXGSRenderFlag
	\since 4.0
 */
//*****************************************************************************

class SICPPSDKDECL CGraphicSequencer
{
public:
	/*! Default constructor. */
	CGraphicSequencer();

	/*! Default destructor. */
	~CGraphicSequencer();

	/*! Registers a new Display callback with the OGS.
	\param in_szName				The display callback name
	\param in_lStateFlags			The callback state flags
	\param in_eType					The type of callback (see ::siDisplayCallback)
	\param in_eViewMode				The view mode (see ::siViewMode)
	\param in_szCustomViewModeName	The name to use for the new custom view mode
	\return CStatus::OK if the new display callback was registered
	\return CStatus::Fail if the registration failed
	\deprecated 9.0 (2011) This version is kept for backward compatibility, please use CGraphicSequencer::RegisterViewportCallback instead.
	*/
	CStatus RegisterDisplayCallback  (	const CString&			in_szName,
										const LONG				in_lStateFlags,
										const siDisplayCallback in_eType,
										const siViewMode		in_eViewMode,
										const CString&			in_szCustomViewModeName) const;

	/*! Registers a new %Pass callback with the XGS.
	\warning Not Implemented. Use CGraphicSequencer::RegisterDisplayCallback with the in_eType parameter set to ::siPass instead.
	\param in_szPassName			The pass callback name
	\param in_lStateFlags			The callback state flags
	\param in_lPassFlags			The pass callback flags
	\param in_szRelativePassName	The name of the pass used for relative insertion.
	\return CStatus::OK if the new pass callback was registered
	\return CStatus::Fail if the registration failed
	\deprecated 9.0 (2011) This version is kept for backward compatibility, please use CGraphicSequencer::RegisterViewportMode instead.
	*/
	CStatus RegisterPassCallback  	(	const CString&			in_szPassName,
										const LONG				in_lStateFlags,
										const LONG 				in_lPassFlags,
										const CString&			in_szRelativePassName ) const;

	/*! Renders the scene using the specified legacy mode.
	\param in_eViewMode		The legacy mode to use
	\param in_lRenderFlags	The render flags to use (one of the ::siXGSRenderFlag values)
	\return CStatus::OK if the scene was successfully rendered
	\return CStatus::Fail if the registration failed or if the mode was not found
	\sa ::siXGSRenderFlag
	*/
	CStatus RenderSceneUsingMode		( const siViewMode in_eViewMode, INT in_lRenderFlags) const;

	/*! Renders the scene using the specified Shader material.
	\param in_szShaderName	The name of the Shader to use for rendering
	\param in_lRenderFlags	The render flags to use (one of the ::siXGSRenderFlag values)
	\return CStatus::OK if the scene was successfully rendered
	\return CStatus::Fail if the registration failed or if the material was invalid
	\sa ::siXGSRenderFlag
	*/
	CStatus RenderSceneUsingMaterial	( const CString&	in_szShaderName, INT in_lRenderFlags ) const;

	/*! Renders a list of objects using the specified legacy mode.
	\param in_pObjectList	The list of objects to draw (array of references to objects)
	\param in_eViewMode		The legacy mode to use
	\return CStatus::OK if the list was successfully rendered
	\return CStatus::Fail if the registration failed or if the mode was not found
	*/
	CStatus RenderListUsingMode		( const CRefArray&	in_pObjectList,
										  const siViewMode in_eViewMode ) const;

	/*! Renders a list of objects using a specific Shader material.
	\param in_pObjectList	The list of objects to draw (array of references to objects)
	\param in_szShaderName	The name of the Shader to use for rendering
	\return CStatus::OK if the list was successfully rendered
	\return CStatus::Fail if the registration failed or if the mode was not found
	*/
	CStatus RenderListUsingMaterial		( const CRefArray&	in_pObjectList,
										  const CString&	in_szShaderName ) const;

	/*! Returns the number of states matching the specified type.
	\param in_eType			The state type to count (one of the ::siXGSStateType values)
	\retval out_pNbStates	Pointer to an integer holding the number of states
	\return CStatus::OK on success
	\return CStatus::Fail if the arguments are invalid
	*/
	CStatus GetNbStates		( siXGSStateType in_eType, INT *out_pNbStates) const;

	/*! Deletes a state by its identification (CString).
	\param in_eType	The state type to delete (one of the ::siXGSStateType values)
	\param in_pID 	String identifying the state
	\return CStatus::OK on success
	\return CStatus::Fail if the state was not found
	*/
	CStatus DeleteState		( siXGSStateType in_eType, const CString&	in_pID ) const;

	/*! Creates a new state.
	\param in_eType				The state type to create (one of the ::siXGSStateType values)
	\param in_pID 				String identifying the new state
	\param in_pValuePtr			The state value
	\retval out_pStateHandle	The state handle
	\return CStatus::OK on success
	\return CStatus::Fail if the arguments are invalid
	*/
	CStatus CreateState		( siXGSStateType in_eType, const CString&	in_pID, void* in_pValuePtr, void** out_pStateHandle) const;

	/*! Returns the state handle by its identification (CString).
	\param in_eType				The state type to get (one of the ::siXGSStateType values)
	\param in_pID 				String identifying the state
	\retval out_pStateHandle	The state handle
	\return CStatus::OK on success
	\return CStatus::Fail if the arguments are invalid
	*/
	CStatus GetStateHandle	( siXGSStateType in_eType, const CString&	in_pID, void** out_pStateHandle) const;

	/*! Returns the specified state's value.
	\param in_eType			The state type to get (one of the ::siXGSStateType values)
	\param in_lStateHandle	The handle to the state
	\retval out_pStateValue	Pointer to the state value
	\return CStatus::OK on success
	\return CStatus::Fail if the arguments are invalid
	*/
	CStatus GetStateValue	( siXGSStateType in_eType, void* in_lStateHandle, void* out_pStateValue) const;

	/*! Sets the specified state's value.
	\param in_eType			The state type to set (one of the ::siXGSStateType values)
	\param in_lStateHandle	The handle to the state
	\param in_pStateValue	Pointer to the state value
	\return CStatus::OK on success
	\return CStatus::Fail if the arguments are invalid
	*/
	CStatus SetStateValue	( siXGSStateType in_eType, void* in_lStateHandle, void* in_pStateValue) const;

	/*! Indicates whether the scene has changed since the last frame.
	\retval out_bBool	True if the scene has changed, false otherwise
	\return CStatus::OK on success
	\return CStatus::Fail if the arguments are invalid
	*/
	CStatus GetSceneDirtyFlag	( bool* out_bBool ) const;

	/*! Returns a flag that indicates the context in which the rendering is occuring.
	\retval out_lFlags	The context flags. These are bitwise flags of ::siXGSContextFlag values
	\return CStatus::OK on success
	\return CStatus::Fail if the arguments are invalid
	\sa ::siXGSContextFlag
	\since 4.2
	*/
	CStatus GetContextFlags	( LONG* out_lFlags ) const;

	/*! Returns a list of values describing active framebuffers. The first element in the array is the number
	of framebuffers. The second element is the number of values provided for each framebuffer in the array.
	So the size of the array is <tt>2 + (number of values provided * number of active framebuffers)</tt>.
	\note CValueArray is empty if called while not in hardware rendering mode.
	\return   Each framebuffer is represented in the array by the following values ordered as indicated:
		\li \c CString the name of the framebuffer.
		\li \c CString the output file's resolved path.
		\li \c CValue  the width of the framebuffer.
		\li \c CValue   the height of the framebuffer.
		\li ::siImageBitDepth the bit depth of the framebuffer.
	\sa ::siXGSContextFlag
	\since 9.0 (2011)
	 */

	CValueArray GetFramebufferInfo ( ) const;

	 /*! Writes an array of pixels to a framebuffer
	 \param in_uiFramebufferIndex The index of the framebuffer
	 \param in_ulSizeInBytes The size of the data pointed to by \c in_pData, in bytes
	 \param in_pData The pixel data
	 \return CStatus::OK on success
	 \return CStatus::Fail if the arguments are invalid
	 \return CStatus::Unexpected Not in Hardware Rendering mode
	 \sa ::siXGSContextFlag
	 \since 9.0 (2011)
	 */
	CStatus PutFramebufferData( UINT in_uiFramebufferIndex,
										ULONG in_ulSizeInBytes,
										void* in_pData) const;

	/*! Returns the value of the specified XGS setting (Hardware Rendering mode only). Possible values include:
	\li \c tile_width	Integer representing the width of the tile being rendered.
	\li \c tile_height	Integer representing the height of the tile being rendered.
	\li \c tile_index	Integer representing the zero-based index of the tile being rendered.
	\li \c tile_origin_x	Integer representing the origin of the x-coordinate for the current tile.
	\li \c tile_origin_y	Integer representing the origin of the y-coordinate for the current tile.
	\li \c tile_count	Integer representing the total number of tiles in the current frame.
	\li \c frustum_clip_plane_left	Double representing the left clipping plane of the view frustum.
	\li \c frustum_clip_plane_right	Double representing the right clipping plane of the view frustum.
	\li \c frustum_clip_plane_bottom	Double representing the bottom clipping plane of the view frustum.
	\li \c frustum_clip_plane_top	Double representing the top clipping plane of the view frustum.
	\li \c frustum_clip_plane_near	Double representing the near clipping plane of the view frustum.
	\li \c frustum_clip_plane_far	Double representing the far clipping plane of the view frustum.
	\li \c projection_type	Integer value representing the projection type. 0 = Perspective and 1 = Orthographic.
	\li \c renderer_name	XSI::CString contaning the name of the current renderer.
	\param in_name The name of the setting.
	\return The value of the setting
	\since 9.0 (2011)
	*/
	CValue GetSetting ( XSI::CString in_name ) const;

	/*! Returns the renderer's option property evaluated at a specific time. Which particular property
	instance this is is dependent upon the attribute value passed to the CGraphicSequencerContext.
	\param in_rTime The time to evaluate the property at.
	\return The evaluated renderer option property.
	\since 9.0 (2011)
	*/
	Property GetRendererProperty(const CTime &in_rTime) const;

	/*! Returns the current camera object which is used for the current rendering
	\return CRef A reference to a Camera object
	\since 7.0
	*/
	CRef	GetCamera		() const;

	/*! Registers a new Viewport mode
	\param in_szName				The name of the viewport
	\param in_eAPI					The graphics driver to use for this viewport. Use ::siNullGraphicDriver if
										your viewport will handle its own rendering.
	\param in_lFeatures				These are bitwise flags of ::siViewportFeature values
	\return CStatus::OK if the new viewport was registered
	\return CStatus::Fail if the registration failed
	\since 9.0 (2011)
	*/
	CStatus RegisterViewportMode	  (	const CString&			in_szName,
										const siGraphicDriver	in_eAPI,
										LONG	in_lFeatures
										) const;

	/*! Registers a new Viewport callback
	\param in_szName				The name of the viewport
	\param in_lStateFlags			The callback state flags
	\param in_eType					The type of callback (see ::siDisplayCallback)
	\param in_eDriver				The graphics driver to use for this viewport. Use ::siNullGraphicDriver if
										your viewport will handle its own rendering.
	\param in_eViewMode				The view mode (see ::siViewMode)
	\param in_szCustomViewModeList	The list of names to use for the new custom view mode
	\return CStatus::OK if the new viewport was registered
	\return CStatus::Fail if the registration failed
	\since 9.0 (2011)
	*/
	CStatus RegisterViewportCallback  (	const CString&			in_szName,
										const LONG				in_lStateFlags,
										const siDisplayCallback in_eType,
										const siGraphicDriver	in_eDriver,
										const siViewMode		in_eViewMode,
										const CStringArray&		in_szCustomViewModeList
										) const;

	/*! Returns the current graphic driver
	\return A reference to the current graphic driver
	\since 9.0 (2011)
	*/
	CRef GetGraphicDriver  () const;

	/*! Returns the size of the current viewport
	\retval out_uiStartX 	leftmost position in X (horizontal start position)
	\retval out_uiStartY 	rightmost position in Y (vertical start position)
	\retval out_Width 		width of viewport
	\retval out_Height 		height of viewport
	\return Success/failure
	\since 9.0 (2011)
	*/
	CStatus GetViewportSize  (UINT& out_uiStartX, UINT& out_uiStartY, UINT& out_Width, UINT& out_Height) const;

	/*! Returns true if the scene is currently in playback mode
	\return \c true if the scene is in playback mode
	\return \c false otherwise
	\since 9.0 (2011)
	*/
	bool	IsPlayback();

private:

	CGraphicSequencer * operator&() const;
	CGraphicSequencer * operator&();

	void*	m_pImpl;
};

}

#endif // __XSIXSIGRAPHICSEQUENCER_H__
