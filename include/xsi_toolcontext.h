//*****************************************************************************
/*!
   \file xsi_toolcontext.h
   \brief ToolContext class declaration.

	Copyright 2010 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSITOOLCONTEXT_H__
#define __XSITOOLCONTEXT_H__

#include <xsi_context.h>
#include <xsi_line.h>
#include <xsi_plane.h>
#include <xsi_image.h>
#include <xsi_camera.h>
#include <xsi_kinematicstate.h>
#include <xsi_pickbuffer.h>

namespace XSI {

//*****************************************************************************
/*! \class ToolContext xsi_toolcontext.h
	\brief %ToolContext is used for accessing/handling tool data. Instances
	of this object can pass information to the C++ API callbacks that implement
	the custom tool plug-in item.

	A custom tool must be registered at startup time using PluginRegistrar::RegisterTool.
	A scripting command with the same name as the custom tool is also registered.
	Calling this command will invoke the tool. A custom shortcut key may also be
	assigned to the tool using the keyboard mapping dialog.

	\par Tool Callbacks

	\par
	All tool callbacks are optional so tools only need to implement the callbacks they are interested in
	receiving.

	\par
	Callback names must be formatted as \code {plugin_item_name}_{callback_name} \endcode
	where \c plugin_item_name is the string passed to PluginRegistrar::RegisterTool to identify
	the tool plug-in item and \c callback_name is the name of the callback.

	\par
	Each callback receives a reference to the ToolContext which is used to retrieve callback
	specific information and change the tool state.

	\par
	Note: Callbacks that require a return value will be documented in the callback description.
	Return values for all other callbacks are ignored.

	\par Setup
	\code
	CStatus MyTool_Setup( ToolContext &in_context )
	\endcode

	\par
	This callback is called when the tool is created and can be used to setup initial tool state.

	\par Cleanup
	\code
	CStatus MyTool_Cleanup( ToolContext &in_context )
	\endcode

	\par
	This callback is called when the tool is destroyed and can be used to free up memory or
	release drawing resources like textures.

	\par Activate
	\code
	CStatus MyTool_Activate( ToolContext &in_context )
	\endcode

	\par
	This callback is called when the tool takes control of the view. Tools can be temporarily
	deactivated when another tool is invoked by holding down a (supra) hotkey. The original tool
	will be reactivated when the hotkey is released.

	\par Deactivate
	\code
	CStatus MyTool_Deactivate( ToolContext &in_context )
	\endcode

	\par
	This callback is called when another tool takes control of the view. Tools can be temporarily
	deactivated when another tool is invoked by holding down a (supra) hotkey. The original tool
	will be reactivated when the hotkey is released.

	\par Draw
	\code
	CStatus MyTool_Draw( ToolContext &in_context )
	\endcode

	\par
	This callback is called when the view is drawn and the tool can perform its 
	own drawing in this callback. The default drawing coordinates are world-space
	but tools can draw in 2D screen-space by calling ToolContext::BeginViewDraw
	and ToolContext::EndViewDraw.

	\par
	The callback will be called once for each visible view that needs to be redrawn.
	If the tool only wants to draw in a single view or during interaction then
	ToolContext::IsActiveView and ToolContext::IsInteracting can be used to detect
	these conditions. A tool can also be asked to draw when the user is 
	interacting with a camera tool in supra mode and ToolContext::IsNavigating
	will return true when this happens.

	\par MouseDown
	\code
	CStatus MyTool_MouseDown( ToolContext &in_context )
	\endcode

	\par
	This callback is called when a mouse button is pressed on a 3D view.

	\par
	Mouse position and button/modifier key state can be accessed through the
	tool context. The tool can then convert the mouse coordinates to 3D using
	the ToolContext coordinate conversion methods. 

	\par
	The tool must return CStatus::OK if it wants to proceed with the interaction.
	If any other value is returned then the interaction will be aborted and no
	subsequent MouseDrag or MouseUp events will be received.

	\par MouseDrag
	\code
	CStatus MyTool_MouseDrag( ToolContext &in_context )
	\endcode

	\par
	This callback is called when the user is dragging with a mouse button is pressed in a 3D view.

	\par MouseUp
	\code
	CStatus MyTool_MouseUp( ToolContext &in_context )
	\endcode

	\par
	This callback is called when the user releases a mouse button to end interaction in a 3D view.
	
	\par
	If ToolContext::WasAborted is true then the tool interaction was aborted because the user
	pressed Esc or the interaction was interrupted.

	\par MouseMove
	\code
	CStatus MyTool_MouseMove( ToolContext &in_context )
	\endcode

	\par
	This callback is called when the user moves the mouse cursor in a 3D view and no mouse buttons 
	are pressed. This could be used to highlight on-screen controls or provide feedback on
	what is under the cursor.

	\par MouseEnter
	\code
	CStatus MyTool_MouseEnter( ToolContext &in_context )
	\endcode

	\par
	This callback is called when the mouse cursor enters a 3D view. 

	\par MouseLeave
	\code
	CStatus MyTool_MouseLeave( ToolContext &in_context )
	\endcode

	\par
	This callback is called when the mouse cursor leaves a 3D view. 

	\par ModifierChanged
	\code
	CStatus MyTool_ModifierChanged( ToolContext &in_context )
	\endcode

	\par
	This callback is called when a mouse modifier key changes.
	ToolContext::IsShiftKeyDown and ToolContext::IsControlKeyDown
	can be used to determine the current state of the modifier keys.

	\par SelectionChanged
	\code
	CStatus MyTool_SelectionChanged( ToolContext &in_context )
	\endcode

	\par
	This callback is called when the selection changes.

	\par SnapValid
	\code
	CStatus MyTool_SnapValid( ToolContext &in_context )
	\endcode

	\par
	This callback is called during snapping to allow the tool to reject unsuitable
	snap candidates. For example, when translating an object you would generally not
	want to snap to the object being moved.

	\par
	For this callback to be triggered the tool must enable snapping and call
	one of ToolContext::GetWorldPosition or ToolContext::GetWorldRay. Alternatively,
	the tool may call ToolContext::Snap directly.
	
	\par
	Information about the snap candidate can be accessed using ToolContext::GetSnapType,
	ToolContext::GetSnapObject and ToolContext::GetSnapComponent. Note: These methods may also
	be called from the mouse callbacks to get the overall result of the latest snap
	operation.
	
	\par
	Note: This callback can be called numerous times during a single snap operation so it should try to 
	minimize the amount of work it does and test the snap type first before attempting to
	access the object or components.

	\par
	If the callback returns CStatus::OK the snap candidate will be allowed.
	Otherwise, the snap candidate will be ignored for snapping purposes.

	\par KeyDown
	\code
	CStatus MyTool_KeyDown( ToolContext &in_context )
	\endcode

	\par
	This callback is called on key down for shortcuts keys registered
	by the tool using ToolContext::RegisterShortcutKey.

	\par
	Key information can be accessed using ToolContext::GetShortcutKey and
	ToolContext::GetShortcutKeyModifiers. Alternatively, the state of 
	registered shortcut keys can be tested in other callbacks
	using ToolContext::IsShortcutKeyDown.

	\par KeyUp
	\code
	CStatus MyTool_KeyUp( ToolContext &in_context )
	\endcode

	\par
	This callback is called on key up for shortcuts keys registered
	by the tool using ToolContext::RegisterShortcutKey.

	\par
	Key information can be accessed using ToolContext::GetShortcutKey and
	ToolContext::GetShortcutKeyModifiers. Alternatively, the state of 
	registered shortcut keys can be tested in other callbacks using
	ToolContext::IsShortcutKeyDown.

	\par MenuInit
	\code
	CStatus MyTool_MenuInit( ToolContext &in_context )
	\endcode

	\par
	This callback is called by ToolContext::ShowContextMenu to set the contents
	of the menu. The Menu is accessed within the callback using Context::GetSource.

	\eg Simple plugin tool that uses picking to identify the object under the cursor.
	For a more detailed example see the \xm CustomTools/netview_CustomTools SpotLightCreateTool custom tool \endxm example
	Tools can also be created from the Plugin Manager by flicking the File button and then chosing New > Tool.
	\code
	#ifndef linux
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h> // Needed for OpenGL on windows
	#endif
	#include <GL/gl.h>
	#include <xsi_status.h>
	#include <xsi_argument.h>
	#include <xsi_toolcontext.h>
	#include <xsi_pluginregistrar.h>
	#include <xsi_math.h>
	
	using namespace XSI; 
	using namespace XSI::MATH; 
	
	class MyPickInfoTool {
	private: // Data
		LONG		m_cursorX;
		LONG 		m_cursorY;
		CRefArray	m_picked;
	
	public: // Methods
		MyPickInfoTool() {}
	
		~MyPickInfoTool() {}
	
		CStatus MouseMove( ToolContext& in_ctxt )
		{
			m_picked.Clear();
			in_ctxt.GetMousePosition( m_cursorX, m_cursorY );
	
			CLongArray l_points;
			l_points.Add( m_cursorX );
			l_points.Add( m_cursorY );
	
			// Check for object under the cursor
			in_ctxt.Pick( l_points, siPickSingleObject, siPickRaycast, L"", CRefArray(), m_picked );
			in_ctxt.Redraw( false );
			return CStatus::OK;
		}
	
		CStatus Draw( ToolContext& in_ctxt )
		{
			if ( in_ctxt.IsActiveView() && m_picked.GetCount() > 0 )
			{
				CString l_Str = m_picked.GetAsText();
				if ( l_Str.Length() > 0 )
				{
					in_ctxt.BeginViewDraw();
	
					LONG width = 0, height = 0, descent = 0;
					in_ctxt.GetTextSize( l_Str, width, height, descent );
					GLint x = (GLint)m_cursorX - width/2, y = (GLint)m_cursorY + 20;
	
					// Draw text
					glColor3d( 0, 0, 0 );
					glRasterPos2i( x, y );
					in_ctxt.DrawTextString( l_Str );
				}
			}
			return CStatus::OK;
		}
	};
		
	SICALLBACK XSILoadPlugin( PluginRegistrar& in_reg )
	{
		in_reg.PutAuthor(L"Autodesk Ltd");
		in_reg.PutName(L"Simple Tool Plugin");
		in_reg.PutVersion(1, 0);
		in_reg.RegisterTool(L"MyPickInfoTool");
		//RegistrationInsertionPoint - do not remove this line
		return CStatus::OK;
	}

	SICALLBACK MyPickInfoTool_Init( CRef& in_ctxt )
	{
		ToolContext l_ctxt( in_ctxt );
		PickInfoTool *l_pTool = new PickInfoTool;
		if ( !l_pTool ) return CStatus::Fail;
		l_ctxt.PutUserData( CValue((CValue::siPtrType)l_pTool) );
		return CStatus::OK;
	}
	
	SICALLBACK MyPickInfoTool_Term( CRef& in_ctxt )
	{
		ToolContext l_ctxt( in_ctxt );
		PickInfoTool *l_pTool = (PickInfoTool *)(CValue::siPtrType)l_ctxt.GetUserData();
		if ( !l_pTool ) return CStatus::Fail;
		delete l_pTool;
		l_ctxt.PutUserData( CValue((CValue::siPtrType)NULL) ); // Clear user data
		return CStatus::OK;
	}
	
	#define DECLARE_TOOL_CALLBACK(TOOL,CALLBACK) \
	SICALLBACK TOOL##_##CALLBACK( ToolContext& in_ctxt ) { \
		TOOL *l_pTool = (TOOL *)(CValue::siPtrType)in_ctxt.GetUserData(); \
		return ( l_pTool ? l_pTool->CALLBACK( in_ctxt ) : CStatus::Fail ); }
	
	DECLARE_TOOL_CALLBACK( MyPickInfoTool, MouseMove );
	DECLARE_TOOL_CALLBACK( MyPickInfoTool, Draw );
	\endcode

	\sa PluginRegistrar::RegisterTool
	\since 10.0 (2012)
*/
//*****************************************************************************

class SICPPSDKDECL ToolContext : public Context
{
public:
	/*! Default constructor. */
	ToolContext();

	/*! Default destructor. */
	~ToolContext();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	ToolContext(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	ToolContext(const ToolContext& in_obj);

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
	\return The new ToolContext object.
	*/
	ToolContext& operator=(const ToolContext& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new ToolContext object.
	*/
	ToolContext& operator=(const CRef& in_ref);

	//*****************************************************************************
	/*!	\name Mouse and Keyboard Methods
	 */
	/*@{*/

	/*! Returns the mouse coordinates relative to the current view
	\param x mouse X coordinate in pixels.
	\param y mouse Y coordinate in pixels.
	\return CStatus::OK success.
	\return CStatus::Fail Unavailable in current callback.
	*/
	CStatus GetMousePosition( LONG &x, LONG &y ) const;

	/*! Returns left mouse button state.
	*/
	bool IsLeftButtonDown() const;

	/*! Returns middle mouse button state.
	*/
	bool IsMiddleButtonDown() const;

	/*! Returns right mouse button state.
	*/
	bool IsRightButtonDown() const;

	/*! Returns whether mouse button was double clicked
	*/
	bool IsDoubleClick() const;

	/*! Returns shift key state.
	*/
	bool IsShiftKeyDown() const;

	/*! Returns control key state.
	*/
	bool IsControlKeyDown() const;

	/*! Register a tool keyboard shortcut.
	\param in_virtualKeycode Virtual keycode for the keyboard shortcut.
	\param in_description Shortcut key description.
	\param in_modifiers. ::siKeyboardState modifier for the keyboard shortcut
	\param in_repeats. If true key events will be continuously sent while the key is held down.
	\return CStatus::OK success.
	\return CStatus::Fail error.
	*/
	CStatus RegisterShortcutKey( ULONG in_virtualKeycode, const CString &in_description, ULONG in_modifiers = 0, bool in_repeats = false );

	/*! Unregister a tool keyboard shortcut.
	\param in_virtualKeycode Virtual keycode for the keyboard shortcut.
	\param in_modifiers. ::siKeyboardState modifier for the keyboard shortcut
	\return CStatus::OK success.
	\return CStatus::Fail error.
	*/
	CStatus UnRegisterShortcutKey( ULONG in_virtualKeycode, ULONG in_modifiers = 0 );
	/*@}*/

	/*! Get current state of tool keyboard shortcut.
	\param in_virtualKeycode Virtual keycode for the keyboard shortcut.
	\param in_modifiers. ::siKeyboardState modifier for the keyboard shortcut
	\return True if shortcut key is pressed.
	*/
	bool IsShortcutKeyDown( ULONG in_virtualKeycode, ULONG in_modifiers = 0 ) const;

	/*! Get virtual keycode for the key being processed in KeyUp/KeyDown callback.
	\return Virtual keycode or 0 if called from outside KeyUp/KeyDown callbacks.
	*/
	ULONG GetShortcutKey() const;

	/*! Get modifiers for the key being processed in KeyUp/KeyDown callback.
	\return Modifier flags or 0 if called from outside KeyUp/KeyDown callbacks.
	*/
	ULONG GetShortcutKeyModifiers() const;
	/*@}*/

	//*****************************************************************************
	/*! \name View Methods
	 */
	/*@{*/

	/*! Returns the size of the view in pixel coordinates.
	\param width width of view in pixels
	\param height height of view in pixels
	\return CStatus::OK success.
	\return CStatus::Fail Unavailable in current callback.
	*/
	CStatus GetViewSize( LONG &width, LONG &height ) const;

	/*! Returns the 3D viewport in pixel coordinates.
	The 3D viewport can be a subset of the actual view size.
	\param x horizontal offset in pixels
	\param y vertical offset in pixels
	\param width width of viewport in pixels
	\param height height of viewport in pixels
	\return CStatus::OK success.
	\return CStatus::Fail Unavailable in current callback.
	*/
	CStatus GetViewport( LONG &x, LONG &y, LONG &width, LONG &height ) const;

	/*! Returns true if a MouseDown/MouseDrag/MouseUp is in progress.
	*/
	bool IsInteracting() const;

	/*! Returns true if the view being drawn is the last view under the cursor.
	*/
	bool IsActiveView() const;

	/*! Returns true if tool is being drawn and camera tool is currently active in supra mode.
	*/
	bool IsNavigating() const;

	/*! Get index of current view. The view index may be used by the tool identify the view
	but the caller should not assume the index corresponds directly to the view manager (A/B/C/D) panes.
	\return Returns view index (greater or equal than zero) or -1 if the information is unavailable in current callback.
	*/
	LONG GetViewIndex() const;

	/*! Return the camera for the current view
	\return Camera or invalid reference if unavailable in current callback.
	*/
	Camera GetCamera() const;

	/*@}*/

	//*****************************************************************************
	/*!	\name Tool State Methods
	 */
	/*@{*/

	/*! Set tool cursor
	\param in_cursorId Predefined cursor to use. Default is ::siArrowCursor.
	\return CStatus::OK success.
	\return CStatus::Fail Unavailable in current callback.
	*/
	CStatus SetCursor( siToolCursor in_cursorId );

	/*! Set tool description
	\param in_message Tool message string with newlines separating description/left/middle/right message sections.
	\return CStatus::OK success.
	\return CStatus::Fail Unavailable in current callback.
	*/
	CStatus SetToolDescription( const CString &in_message );

	/*! Enable standard tool snapping behaviour
	\param in_enable Enable standard control key snapping behaviour for this tool.
	\return CStatus::OK success.
	\return CStatus::Fail Unavailable in current callback.
	*/
	CStatus EnableSnapping( bool in_enable );

	/*! Get view plane
	\param out_plane Get view aligned manipulation plane in this view.
	\return CStatus::OK success.
	\return CStatus::Fail Unavailable in current callback.
	*/
	CStatus GetViewPlane( MATH::CPlane &out_plane ) const;

	/*! Get grid plane
	\param out_plane Get visible grid plane in this view.
	\return CStatus::OK success.
	\return CStatus::Fail Unavailable in current callback.
	*/
	CStatus GetGridPlane( MATH::CPlane &out_plane ) const;

	/*! Set projection plane
	\param in_plane New projection plane.
	\return CStatus::OK success.
	\return CStatus::Fail Unavailable in current callback.
	*/
	CStatus SetManipulationPlane( const MATH::CPlane &in_plane );

	/*! Restore projection plane to default setting
	\return CStatus::OK success.
	\return CStatus::Fail Unavailable in current callback.
	*/
	CStatus ClearManipulationPlane();

	/*! Returns true if user pressed Escape to end mouse drag.
	*/
	bool WasAborted() const;

	/*! Schedule this tool for termination
	\return CStatus::OK success.
	\return CStatus::Fail Unavailable in current callback.
	*/
	CStatus ExitTool();

	/*! Returns the state of one of the various flags that affects tool behavior.
	You can set the value of a flag with ToolContext::SetFlag.
	\param in_flag Value from the ::siToolCapabilities enum
	*/
	bool GetFlag( LONG in_flag ) const;

	/*! Sets the state of one of the various flags that affects tool behavior.
	You can test the value of these flags with ToolContext::GetFlag.
	\param in_flag Value from the ::siToolCapabilities enum
	\param in_enable True to enable the flag and false to disable it.
	\return CStatus::OK success.
	\return CStatus::Fail Unrecognized flag.
	*/
	CStatus SetFlag( LONG in_flag, bool in_enable );
	/*@}*/

	/*! \name Coordinate Conversion Methods
	 */
	/*@{*/ 

	/*! Get 3D world-space point by projecting the 2D input point onto the current manipulation plane.
	If snapping is enabled and active then snapping will be applied to the resulting point.
	Detailed information about the snap target can be obtained using the 
	snapping access methods such as ToolContext::GetSnapType following this call.
	\param x view X coordinate in pixels.
	\param y view Y coordinate in pixels.
	\param out_world 3D world-space position.
	\return CStatus::OK Projection succeeded.
	\return CStatus::Fail Unavailable in current callback or point does not intersect the projection plane.
	*/
	CStatus GetWorldPosition( LONG x, LONG y, MATH::CVector3 &out_world ) const;

	/*! Get 3D world-space ray through the 2D input point.
	If snapping is enabled and active then snapping will be applied to the resulting ray.
	Detailed information about the snap target can be obtained using the 
	snapping access methods such as ToolContext::GetSnapType following this call.
	\param x view X coordinate in pixels.
	\param y view Y coordinate in pixels.
	\param out_ray 3D world-space ray.
	\return CStatus::OK Projection succeeded.
	\return CStatus::Fail Unavailable in current callback.
	*/
	CStatus GetWorldRay( LONG x, LONG y, MATH::CLine &out_ray ) const;

	/*! Convert a 3D world-space point to 2D pixel coordinates with depth.
	No snapping is applied to points. The X & Y coordinates of the output
	point represent 2D view coordinates while the Z component represents
	the depth.
	\param in_world world-space input point
	\param out_view view-space output point
	\return CStatus::OK Succeeded.
	\return CStatus::Fail Unavailable in current callback.
	*/
	CStatus WorldToView( const MATH::CVector3 &in_world, MATH::CVector3 &out_view ) const;

	/*! Convert a 2D pixel coordinate with depth to a 3D world-space point.
	No snapping is applied to points.
	\param in_view view-space input point
	\param out_view world-space output point
	\return CStatus::OK Succeeded.
	\return CStatus::Fail Unavailable in current callback.
	*/
	CStatus ViewToWorld( const MATH::CVector3 &in_view, MATH::CVector3 &out_world ) const;

	/*! Convert a 3D world-space point to 3D camera-space point.
	No snapping is applied to points.
	\param in_world world-space input point
	\param out_camera camera-space output point
	\return CStatus::OK Succeeded.
	\return CStatus::Fail Unavailable in current callback.
	*/
	CStatus WorldToCamera( const MATH::CVector3 &in_world, MATH::CVector3 &out_camera ) const;

	/*! Convert a 3D camera-space point to a 3D world-space point.
	No snapping is applied to points.
	\param in_camera camera-space input point
	\param out_world world-space output point
	\return CStatus::OK Succeeded.
	\return CStatus::Fail Unavailable in current callback.
	*/
	CStatus CameraToWorld( const MATH::CVector3 &in_view, MATH::CVector3 &out_world ) const;

	/*! Return matrix used to transform 3D world-space points to 2D pixel coordinates with depth.
	\param out_worldToview world-to-view 4x4 matrix
	\return CStatus::OK Succeeded.
	\return CStatus::Fail Unavailable in current callback.
	*/
	CStatus GetWorldToViewMatrix( MATH::CMatrix4 &out_worldToView ) const;

	/*! Return matrix used to transform 3D world-space points to 3D camera-space points.
	\param out_worldToCamera world-to-camera 4x4 matrix
	\return CStatus::OK Succeeded.
	\return CStatus::Fail Unavailable in current callback.
	*/
	CStatus GetWorldToCameraMatrix( MATH::CMatrix4 &out_worldToCamera ) const;
	/*@}*/ 

	/*! \name Drawing and Text Methods
	 */
	/*@{*/

	/*! Request redraw. In most cases the redraw happens automatically so the only place this is needed
	is to trigger redraw based on mouse move events. (when no mouse buttons are pressed)
	\param in_allViews If true redraw all views. If false redraw current view only.
	\return CStatus::OK Success.
	\return CStatus::Fail Unavailable in current callback.
	*/
	CStatus Redraw( bool in_allViews = true );

	/*! Draw text at current raster position and with the specified alignment. Only valid during drawing.
	\param in_str Text string to display.
	\param in_hPos Horizontal text position relative to the current raster position. Default is ::siLeftAlign.
	\param in_vPos Vertical text position relative to the current raster position. Default is ::siBottomAlign.
	\return CStatus::OK Success.
	\return CStatus::Fail Called from outside drawing.
	*/
	CStatus DrawTextString( const CString &in_str, siAlignment in_hPos = siLeftAlign, siAlignment in_vPos = siBottomAlign );

	/*! Get size of text in 2D pixel coordinates. Only valid during drawing.
	\param in_str Text string to measure.
	\param out_width Width of text string in pixels.
	\param out_height Height of text string in pixels.
	\param out_descent Number of pixels the font extends below the baseline for the font.
	\return CStatus::OK Success.
	\return CStatus::Fail Called from outside drawing.
	*/
	CStatus GetTextSize( const CString &in_str, LONG &out_width, LONG &out_height, LONG &out_descent ) const;

	/*! Display in-place text editing field at the specified 2D pixel coordinates. Only valid during mouse up.
	\param io_str Text string to modify.
	\param x left view coordinate of text editing box in pixels
	\param y bottom view coordinate of text editing box in pixels
	\param width width of text editing box in pixels
	\param height height of text editing box in pixels
	\return CStatus::OK Success.
	\return CStatus::False User cancelled editing.
	\return CStatus::Fail Called from outside the mouse up callback.
	*/
	CStatus EditTextString( CString &io_str, LONG x, LONG y, LONG width, LONG height );

	/*! Change drawing to 2D pixel coordinates. Only valid during drawing/picking.
	\return CStatus::OK Success.
	\return CStatus::Fail Called from outside drawing/picking.
	*/
	CStatus BeginViewDraw();

	/*! Change drawing back to 3D world-space coordinates. Only valid during drawing/picking.
	\return CStatus::OK Success.
	\return CStatus::Fail Called from outside drawing/picking.
	*/
	CStatus EndViewDraw();

	/*! Returns true if view drawing is active.
	*/
	bool IsViewDraw() const;

	/*! Setup drawing for OpenGL picking. 
	The pick region is centered on the specified x/y coordinates.
	Only valid during mouse callbacks.
	\param x horizontal view coordinate of pick region in pixels
	\param y vertical view coordinate of pick region in pixels
	\param width width of pick region in pixels
	\param height height of pick region in pixels
	\return CStatus::OK Success.
	\return CStatus::Fail Called from outside mouse callbacks.
	*/
	CStatus BeginPickDraw( LONG x, LONG y, LONG width, LONG height);

	/*! Restore drawing to original state. Only valid during mouse callbacks.
	\return CStatus::OK Success.
	\return CStatus::Fail Called from outside mouse callbacks.
	*/
	CStatus EndPickDraw();

	/*! Returns true if pick drawing is active.
	*/
	bool IsPickDraw() const;
	/*@}*/

	//*****************************************************************************
	/*! \name Interactive Data Update Methods
	 */
	/*@{*/

	/*! Start an interaction update on a parameter.
	At the end of interaction a single undo event will be logged.
	\param in_param	The parameter to update.
	\param in_time Time defaults to the current frame if \c in_time is set with \c DBL_MAX.
	\return CStatus::OK Success.
	\return CStatus::Fail Unavailable in current callback or other failure.
	*/
	CStatus BeginParameterUpdate(const Parameter &in_param, double in_time = DBL_MAX);

	/*! Update value of parameter during interaction.
	At the end of interaction a single undo event will be logged.
	\param in_param	The parameter to set.
	\param in_value New value for parameter.
	\return CStatus::OK Success.
	\return CStatus::Fail Unavailable in current callback or other failure.
	\return CStatus::InvalidArgument Invalid argument.
	*/
	CStatus UpdateParameter(const Parameter &in_param, const CValue &in_value);

	/*! Stop updating parameter and log undo event.
	At the end of interaction a single undo event will be logged.
	\param in_param	The parameter to stop updating.
	\return CStatus::OK Success.
	\return CStatus::Fail Unavailable in current callback or other failure.
	\return CStatus::InvalidArgument Invalid argument.
	*/
	CStatus EndParameterUpdate(const Parameter &in_param);

	/*! Start an interaction update on a kinematic state.
	At the end of interaction a single undo event will be logged.
	\param in_kine	The kinematic state to update.
	\param in_time Time defaults to the current frame if \c in_time is set with \c DBL_MAX.
	\return CStatus::OK Success.
	\return CStatus::Fail Unavailable in current callback or other failure.
	\return CStatus::InvalidArgument Invalid argument.
	*/
	CStatus BeginKinematicStateUpdate(const KinematicState &in_kine, double in_time = DBL_MAX);

	/*! Update value of kinematic state during interaction.
	At the end of interaction a single undo event will be logged.
	\param in_kine	The kinematic state to set.
	\param in_value New value for the kinematic state.
	\return CStatus::OK Success.
	\return CStatus::Fail Unavailable in current callback or other failure.
	\return CStatus::InvalidArgument Invalid argument.
	*/
	CStatus UpdateKinematicState(const KinematicState &in_kine, const MATH::CTransformation &in_value);

	/*! Stop updating kinematic state and log undo event.
	At the end of interaction a single undo event will be logged.
	\param in_kine	The kinematic state to stop updating.
	\return CStatus::OK Success.
	\return CStatus::Fail Unavailable in current callback or other failure.
	\return CStatus::InvalidArgument Invalid argument.
	*/
	CStatus EndKinematicStateUpdate(const KinematicState &in_kine);

	/*! Start an interaction update on a list of objects or components.
	At the end of interaction a single undo event will be logged.
	\param in_objects List of objects or components to update.
	\param in_time Time defaults to the current frame if \c in_time is set with \c DBL_MAX.
	\return CStatus::OK Success.
	\return CStatus::Fail Unavailable in current callback or other failure.
	\return CStatus::InvalidArgument Invalid argument.
	*/
	CStatus BeginTransformUpdate(const CRefArray &in_objects, double in_time = DBL_MAX);

	/*! Update value of objects or components during interaction.
	At the end of interaction a single undo event will be logged.
	\param in_objects List of objects or components to update.
	\param in_value New transform values.
	\param in_srt Type of transform that will be applied.
	\param in_refMode Reference mode to use for the transform. Default is ::siLocal.
	\param in_delta Relative or absolute transform. Default is ::siRelative.
	\param in_axesFilter Used with ::siAbsolute to specify which transform axes to modify. Default is ::siXYZ.
	\param in_usePivot Perform transform relative to a pivot. Default is false.
	\param in_pivot Global pivot location. Default pivot is world-space origin.
	\param in_reference Reference-to-world transform to use with ::siObjCtr. Default is identity which is world-space.
	\return CStatus::OK Success.
	\return CStatus::Fail Unavailable in current callback or other failure.
	\return CStatus::InvalidArgument Invalid argument.
	*/
	CStatus UpdateTransform(
		const CRefArray &				in_objects,
		const MATH::CTransformation &	in_value,
		siTransformFilter				in_srt,
		siRefMode						in_refMode		= siLocal,
		siDeltaMode						in_delta		= siRelative,
		siAxesFilter					in_axesFilter	= siXYZ,
		bool							in_usePivot		= false,
		const MATH::CVector3 &			in_pivot		= MATH::CVector3(),
		const MATH::CTransformation &	in_reference	= MATH::CTransformation()
	);

	/*! Stop updating objects or components and log an undo event.
	At the end of interaction a single undo event will be logged.
	\param in_objects List of objects or components to update.
	\return CStatus::OK Success.
	\return CStatus::Fail Unavailable in current callback or other failure.
	\return CStatus::InvalidArgument Invalid argument.
	*/
	CStatus EndTransformUpdate(const CRefArray &in_objects);
	/*@}*/

	//*****************************************************************************
	/*! \name Snapping Methods
	 */
	/*@{*/

	/*! Return the ::siSnapType from the last snap operation or the current snap
	candidate if called from within the SnapValid callback. ::siSnapNone is
	returned if nothing was snapped or if this information is unavailable in
	the current callback.
	*/
	siSnapType GetSnapType() const;

	/*! Return the last snapped object or the current snap
	candidate object if called from within the SnapValid callback.
	Some snap types like ::siSnapNone and ::siSnapGrid do not have an associated 
	object and in this case the returned reference will be invalid.
	*/
	CRef GetSnapObject() const;

	/*! Return the last snapped component or the current snap
	candidate if called from within the SnapValid callback.
	Some snap types are not associated with a component and in
	that case the returned reference will be invalid.
	*/
	CRef GetSnapComponent() const;

	/*! Get 3D world-space point by snapping the 2D input point using the specified snap settings.
	Detailed information about the snap target can be obtained using the 
	snapping access methods such as ToolContext::GetSnapType following this call.
	\param x View X coordinate in pixels.
	\param y View Y coordinate in pixels.
	\param size Size of snap region in pixels.
	\param in_snaptype Mask of ::siSnapType flags used to specify what types of snap targets will be considered. For example pass ::siSnapPoint|::siSnapGrid to enable both point and grid snapping.
	\param in_families An array of families defined by ::siFamily or an empty array if none are required. The families
		are used for narrowing down the search, the array can contain X3DObject families like si3DObjectFamily or primitive
		families such as siNurbsSurfaceMeshFamily and siNullPrimitiveFamily. Only the children objects that match one of the
		supplied families are considered. If primitive families are supplied then only the objects defined with a primitive
		that belongs to one of them are considered. The list of valid families are the following:
		\code
						si3DObjectFamily						siLatticeFamily
						siCameraFamily							siLightPrimitiveFamily
						siChainElementFamily					siMeshFamily
						siControlObjectFamily					siNullPrimitiveFamily
						siCurveFamily							siNurbsCurveListFamily
						siGeometryFamily						siNurbsSurfaceMeshFamily
						siGeometryShaderFamily					siSurfaceCurveFamily
						siImplicitGeometryFamily				siSurfaceFamily
		\endcode
	\param in_objects List of objects to snap to. If empty then the entire scene will be used.
	\param out_world 3D world-space position.
	\return CStatus::OK Snap succeeded.
	\return CStatus::Fail Unavailable in current callback.
	\return CStatus::InvalidArgument Invalid argument specified.
	*/
	CStatus Snap( LONG x, LONG y, LONG size, ULONG in_snaptype, const CStringArray& in_families, const CRefArray &in_objects, MATH::CVector3 &out_world ) const;
	/*@}*/

	//*****************************************************************************
	/*! \name Picking Methods
	 */
	/*@{*/

	/*! Perform a pick operation on the view and return the list of objects or components that match.
	\param in_points Points to use for picking. The array size should be a multiple of 2
		with each pair of values representing a single 2D view point.
		The number of points required depends on the picking mode.
		For ::siPickRaycast a single point is required.
		For ::siPickRectangle and ::siPickRectangleRaycast two points are needed.
		For ::siPickLasso and ::siPickFreeform can use an arbitrary number of points which define a path.
	\param in_pickMode Picking mode. For objects use ::siPickSingleObject or ::siPickMultipleObjects
		and for subcomponents use ::siPickSingleSubComponent or ::siPickMultipleSubComponents.
	\param in_pickType Defines the type of picking used. One of ::siPickRectangle, ::siPickRaycast,
		::siPickLasso, ::siPickFreeform or ::siPickRectangleRaycast.
	\param in_filter A filter to use for picking. For object picking this can be empty but must be supplied for
		subcomponent picking to identify the subcomponent to pick.
		The list of valid filters are the following:
		\code
						siCameraFilter							siBoundaryFilter
						siChainElementFilter					siEdgeFilter
						siControlFilter							siIsopointFilter
						siCurveFilter							siKnotFilter
						siEffectorFilter						siPointFilter
						siGeometryFilter						siPolygonFilter
						siGroupFilter							siUIsolineFilter
						siImplicitFilter						siVIsolineFilter
						siLatticeFilter							siUKnotCurveFilter
						siLightFilter							siVKnotCurveFilter
						siModelFilter
						siNullFilter
						siPointCloudFilter
						siPolyMeshFilter
						siPrimitiveFilter
						siSkeletonJointFilter
						siSubSurfaceFilter
						siSurfaceCurveFilter
						siSurfaceMeshFilter
						siTextureControlFilter
						siTrimCurveFilter
		\endcode
	\param in_objects List of objects to pick.
		When picking objects this list is optional and if empty the entire scene will be used.
		When picking subcomponents the list must supplied and non-empty. 
	\param out_picked List of picked objects.
	\return CStatus::OK Pick succeeded.
	\return CStatus::Fail Unavailable in current callback.
	\return CStatus::InvalidArgument Invalid argument specified.
	*/
	CStatus Pick( const CLongArray &in_points, siPickMode in_pickMode, siPickType in_pickType, const CString &in_filter, const CRefArray &in_objects, CRefArray &out_picked ) const;

	/*! Low-level picking operation that returns a buffer that can be used to map view coordinates to objects and component indices.
	The pick buffer acts like a snapshot taken at the time of the call and once it has been generated objects and component indices
	can be retrieved from the pick buffer without any additional overhead. The pick buffer will only return information about the
	closest object or component and cannot return information for objects and components that are hidden behind other objects or components.
	Passing an empty pick region (0,0,0,0) will generate a pick buffer that covers the entire view.
	\param x Left view coordinate of picking region.
	\param y Bottom view coordinate of picking region.
	\param width Width of picking region in view coordinates.
	\param height Height of picking region in view coordinates.
	\param in_filter A filter to use for picking. For object picking this can be empty but must be supplied for
		subcomponent picking to identify the subcomponent to pick.
		The list of valid filters are the following:
		\code
						siObjectFilter
						siPointFilter
						siEdgeFilter
						siPolygonFilter
		\endcode
	\param in_objects List of objects to pick.
		When picking objects this list is optional and if empty the entire scene will be used.
		When picking subcomponents the list must supplied and non-empty. 
	\param in_viewMode ::siViewMode to use when generating the pick buffer.
		Passing ::siAll will use the current display mode. Default is ::siShaded.
		The list of valid view modes are the following:
		\code
						siAll (current view mode)
						siWireframe
						siShaded (default)
		\endcode
	\return PickBuffer. If unavailable in the current callback or any arguments are invalid then the resulting PickBuffer will be invalid.
	*/
	PickBuffer GetPickBuffer( LONG x, LONG y, LONG width, LONG height, const CString &in_filter, const CRefArray &in_objects, siViewMode in_viewMode = siShaded ) const;
	/*@}*/

	//*****************************************************************************
	/*! \name Context Menu Methods
	 */
	/*@{*/

	/*! Show a tool context menu using the specified position/alignment. Only valid during mouse down or mouse up.
	The context menu needs to be defined by the MenuInit callback in the tool.
	\param x View X coordinate in pixels.
	\param y View Y coordinate in pixels.
	\param in_hPos Horizontal menu position relative to the input position. Default is ::siLeftAlign.
	\param in_vPos Vertical menu position relative to the input position. Default is ::siTopAlign.
	\return CStatus::OK Success.
	\return CStatus::False Nothing selected from menu or no menu to display.
	\return CStatus::Fail Called from outside mouse down or mouse up callback.
	*/
	CStatus ShowContextMenu( LONG x, LONG y, siAlignment in_hPos = siLeftAlign, siAlignment in_vPos = siTopAlign );
	/*@}*/

	//*****************************************************************************
	/*! \name Utility Methods
	 */
	/*@{*/

	/*! Load an image from a file.
	\param in_filename Filename of image to load.
	\param in_relativePath If true in_filename is relative to plugin location.
	\return Requested Image.
	*/
	Image LoadImageFromFile( const CString &in_filename, bool in_relativePath = true );
	/*@}*/

private:
	ToolContext * operator&() const;
	ToolContext * operator&();
};

};
#endif // __XSITOOLCONTEXT_H__
