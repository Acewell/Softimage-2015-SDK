//*****************************************************************************
/*!	\file xsi_pluginregistrar.h
	\brief PluginRegistrar class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIPLUGINREGISTRAR_H__
#define __XSIPLUGINREGISTRAR_H__

#include <xsi_siobject.h>
#include <xsi_pluginitem.h>

namespace XSI {

class ICENodeDef;

//*****************************************************************************
/*! \class PluginRegistrar xsi_pluginregistrar.h
	\brief This class provides functions for registering a PluginItem in Softimage.

	PluginRegistrar instances are created by Softimage and contain information such as the directory
	where the plug-in is being loaded/unloaded along with the filename of the plug-in. When Softimage
	starts up, a PluginRegistrar object is created for each plug-in to load and passed to the
	\xt cb_XSILoadPlugin XSILoadPlugin \endxt function entry point exposed by the plug-in. The information
	gathered by Softimage is used for creating each PluginItem when required by the Softimage user. When a
	plug-in is unloaded, a PluginRegistrar object is created for this particular plug-in and passed to the
	optional \xt cb_XSIUnloadPlugin XSIUnloadPlugin \endxt function entry point exposed by the plug-in. The
	information registered by the plug-in can be accessed through the Plugin class.

	\since 4.0

	\eg %Sample \xt cb_XSILoadPlugin registration callback \endxt for a filter and a command

	\code
		XSI::CStatus XSILoadPlugin( XSI::PluginRegistrar& io_reg )
		{
			io_reg.PutAuthor( L"XYZ" );
			io_reg.PutName( L"XYZ simple plugin" );
			io_reg.PutVersion( 1, 0 );

			io_reg.RegisterFilter( L"Simple Command Filter", siFilterObject );
			io_reg.RegisterCommand( L"Simple Command", L"SimpleCommand );

			return XSI::CStatus::OK;
		}

	\endcode
 */
//*****************************************************************************

class SICPPSDKDECL PluginRegistrar : public SIObject
{
public:
	/*! Default constructor. */
	PluginRegistrar();

	/*! Default destructor. */
	~PluginRegistrar();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	PluginRegistrar(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	PluginRegistrar(const PluginRegistrar& in_obj);

	/*! Returns true if a given class type is compatible with this API class.
	\param in_ClassID class type.
	\return true if the class is compatible, false otherwise.
	*/
	bool IsA( siClassID in_ClassID) const;

	/*! Returns the type of the API class.
	\return the class type.
	*/
	siClassID GetClassID() const;

	/*! Creates an object from another object. The newly created object is set to
	empty if the input object is not compatible.
	\param in_obj constant class object.
	\return New PluginRegistrar object.
	*/
	PluginRegistrar& operator=(const PluginRegistrar& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return New PluginRegistrar object.
	*/
	PluginRegistrar& operator=(const CRef& in_ref);

	/*! Registers a Filter.
	\param in_strName The name of the custom filter.
		<br><br>
		The first character in a filter name must be a letter or an underscore (\c _).
		Subsequent characters can be letters, numbers, underscore (\c _) characters, or spaces.
		<br><br>
		The filter name is used to name the filter callback functions such as Match and Subset.
		For example, the Match callback for a filter named \c "My3DObjectFilter" is \c "My3DObjectFilter_Match".
		If a filter name contains spaces (for example, \c "My 3D Object Filter"), the callback function names
		must omit the spaces (for example, \c "My3DObjectFilter_Match").
		<br><br>
		The filter name also appears in the Softimage user interface, and is the name you use to reference the
		filter in scripting or C++ code. If the filter name contains spaces, you must replace the spaces with
		underscores to use the filter with commands or the object model.
	\param in_type The type of filter to register.
	\return The PluginItem object for the filter.
	 */
	PluginItem RegisterFilter( const CString& in_strName, siFilterType in_type );

	/*! Registers a custom display.
	\param in_strName The name of the custom display.
		<br><br>
		The first character in a custom display name must be a letter or an underscore (\c _).
		Subsequent characters can be letters, numbers, underscore (\c _) characters, or spaces.
		<br><br>
		The custom display name is used to name the callback functions such as \xt cb_CustomDisplay_Init Init \endxt
		and \xt cb_CustomDisplay_Notify Notify \endxt. For example, the Notify callback for a custom display
		named \c "MyCustomDisplay" is \c "MyCustomDisplay_Notify". If the name contains spaces (for example,
		\c "My Custom Display"), the callback function names must omit the spaces (for example, \c "MyCustomDisplay_Notify").
	\return The PluginItem object for the custom display.
	 */
	PluginItem RegisterCustomDisplay( const CString& in_strName );

	/*! Registers a new type of CustomProperty. To create instances of this %CustomProperty, use
	SceneItem::AddProperty.
	\param in_strName The name of the property (actually, the name of the PluginItem object created for
		this property). Instances of the property have this name as their SIObject::Type.
		<br><br>
		The first character in a property name must be a letter or an underscore (\c _).
		Subsequent characters can be letters, numbers, underscore (\c _) characters, or spaces.
		If a property name contains spaces (for example, \c "My Custom Property"), the callback
		function names must omit the spaces (for example, \c "MyCustomProperty_DefineLayout").
		<br><br>
		Property names must be unique. To avoid naming conflicts, we recommend using a prefix
		based on your company name or the plug-in name.(for example, \c "ACME_TornadoKit_Configuration").
	\return The PluginItem object created for this property.
	\sa SceneItem::AddProperty, PPGLayout

	\eg Example of a C++ self-installing property. To try out this example, compile it and copy the DLL/SO
		to the Plugins folder of a workgroup. Then use the Plug-in Manager to load the plug-in (for example,
		by clicking Update All). To create an instance of the property, go to the Plug-in Tree, right-click
		the property, and choose Create Instance).

	\code
		#include <xsi_application.h>
		#include <xsi_context.h>
		#include <xsi_pluginregistrar.h>
		#include <xsi_status.h>
		#include <xsi_customproperty.h>
		#include <xsi_ppglayout.h>
		#include <xsi_ppgeventcontext.h>
		#include <xsi_selection.h>
		using namespace XSI;

		XSIPLUGINCALLBACK CStatus XSILoadPlugin( PluginRegistrar& in_reg )
		{
			in_reg.PutAuthor(L"Softimage SDK Team");
			in_reg.PutName(L"MySimplePropertyPlugin");
			in_reg.PutEmail(L"");
			in_reg.PutURL(L"");
			in_reg.PutVersion(1,0);
			in_reg.RegisterProperty(L"MySimpleProperty");
			//RegistrationInsertionPoint - do not remove this line

			return CStatus::OK;
		}

		XSIPLUGINCALLBACK CStatus XSIUnloadPlugin( const PluginRegistrar& in_reg )
		{
			CString strPluginName = in_reg.GetName();
			Application().LogMessage(strPluginName + L" has been unloaded.");
			return CStatus::OK;
		}

		XSIPLUGINCALLBACK CStatus MySimpleProperty_Define( CRef& in_ctxt )
		{
			Context ctxt( in_ctxt );
			CustomProperty oCustomProperty;
			Parameter oParam;
			oCustomProperty = ctxt.GetSource();
			oCustomProperty.AddParameter(L"U",CValue::siDouble,siPersistable,L"",L"",0l,0l,1l,0l,1l,oParam);
			oCustomProperty.AddParameter(L"V",CValue::siDouble,siPersistable,L"",L"",0l,0l,1l,0l,1l,oParam);
			oCustomProperty.AddParameter(L"LockUV",CValue::siBool,siPersistable,L"",L"",true,CValue(),CValue(),CValue(),CValue(),oParam);
			oCustomProperty.AddParameter(L"ShowInfo",CValue::siBool,siPersistable,L"",L"",true,CValue(),CValue(),CValue(),CValue(),oParam);

		// Some static text we will show optionally on the screen
			CString strInfo(L"This is a Softimage SDK example showing \r\n"
							  L"a Custom Property implemented as a \r\n"
							  L"self-installing plug-in.\r\n");

			oCustomProperty.AddParameter(L"InfoStatic",CValue::siString,siPersistable,L"",L"",L"",oParam);
			//oParam.PutCapabilityFlag( siNotInspectable, true ) ;
			oParam.PutValue( strInfo ) ;

			return CStatus::OK;
		}

		XSIPLUGINCALLBACK CStatus MySimpleProperty_DefineLayout( CRef& in_ctxt )
		{
			Context ctxt( in_ctxt );
			PPGLayout oLayout;
			PPGItem oItem;
			oLayout = ctxt.GetSource();
			oLayout.Clear();

			oLayout.AddGroup( L"Data" ) ;

			oLayout.AddRow() ;

			oItem = oLayout.AddItem(L"U");
			oItem.PutAttribute( siUIThumbWheel, true ) ;
			// The label is a single character, so to make sure it doesn't
			// get too much horizontal space, we set a small LabelPercentage
			// so that the MinPixels takes priority
			oItem.PutLabelPercentage(1);
			oItem.PutLabelMinPixels(20);

			oItem = oLayout.AddItem(L"V");
			oItem.SetAttribute( siUITreadmill, true ) ;
			oItem.PutLabelPercentage(1);
			oItem.PutLabelMinPixels(20);

			oLayout.EndRow() ;

			oLayout.AddItem(L"LockUV", L"Lock UV");

			oLayout.EndGroup();

			oLayout.AddGroup() ;

			// The InfoStatic is always in the layout,
			// but it is hidden if the siNotInspected
			// capability is set to False
			oItem = oLayout.AddItem( L"InfoStatic", L"", siControlStatic ) ;

			oLayout.AddItem( L"ShowInfo", L"Show Info" ) ;
			oLayout.EndGroup() ;

			oLayout.AddButton( L"Done" ) ;

			return CStatus::OK;
		}

		XSIPLUGINCALLBACK CStatus MySimpleProperty_PPGEvent( const CRef& in_ctxt )
		{
			// This callback is called when events happen in the user interface
			// This is where you implement the "logic" code.

			// If the value of a parameter changes but the UI is not shown then this
			// code will not execute.  Also this code is not re-entrant, so any changes
			// to parameters inside this code will not result in further calls to this function

			Application app ;

			// The context object is used to determine exactly what happened
			// We don't use the same "PPG" object that is used from Script-based logic code
			// but through the C++ API we can achieve exactly the same functionality.
			PPGEventContext ctxt( in_ctxt ) ;

			PPGEventContext::PPGEvent eventID = ctxt.GetEventID() ;

			if ( eventID == PPGEventContext::siOnInit )
			{
				// This event meant that the UI was just created.
				// It gives us a chance to set some parameter values.
				// We could even change the layout completely at this point.

				// For this event Source() of the event is the CustomProperty object

				CustomProperty prop = ctxt.GetSource() ;

				app.LogMessage( L"OnInit called for " + prop.GetFullName() ) ;

				// If you regenerate the layout then call this:
				ctxt.PutAttribute(L"Refresh",true);

			}
			else if ( eventID == PPGEventContext::siOnClosed )
			{
				// This event meant that the UI was just closed by the user.

				// For this event Source() of the event is the CustomProperty object

				CustomProperty prop = ctxt.GetSource() ;

				app.LogMessage( L"OnClosed called for " + prop.GetFullName() ) ;
			}
			else if ( eventID == PPGEventContext::siButtonClicked )
			{

				CustomProperty prop = ctxt.GetSource() ;

				// If there are multiple buttons
				// we can use this attribute to figure out which one was clicked.
				CValue scriptNameOfButton = ctxt.GetAttribute( L"Button" ) ;

				if ( scriptNameOfButton.GetAsText() == L"Done" )
				{
					// See the scripting documentation for
					// PPG.Close for more info about this
					// technique.

					// Self destruct the property page

					CValueArray args( 1 ) ;
					args[0] = prop ;
					CValue retval ;
					app.ExecuteCommand( L"DeleteObj", args, retval ) ;

					// Tell the context that we want the
					// the property page closed
					ctxt.PutAttribute( L"Close", true ) ;
				}
				else
				{
					// We only have a single button so this case is unexpected
				}
			}
			else if ( eventID == PPGEventContext::siTabChange )
			{
				// We will be called when the PPG is first opened
				// and every time the tab changes

				// Retrieve the label of the tab that is now active
				CValue tabLabel = ctxt.GetAttribute( L"Tab" ) ;

				app.LogMessage( L"Tab changed to: " + tabLabel .GetAsText() ) ;
			}
			else if ( eventID == PPGEventContext::siParameterChange )
			{
				// For this event the Source of the event is the parameter
				// itself
				Parameter changed = ctxt.GetSource() ;
				CustomProperty prop = changed.GetParent() ;

				if ( changed.GetName() == L"ShowInfo" )
				{
					// Toggle the visibility of the static text
					Parameter infoStatic = prop.GetParameters().GetItem( L"InfoStatic" ) ;
					infoStatic.PutCapabilityFlag( siNotInspectable, changed.GetValue() == false ) ;

					// It isn't strictly necessary to call this for
					// simple cases of hiding and showing controls,
					// but it ensures that the property page is fully
					// redrawn and resized.
					ctxt.PutAttribute( L"Refresh", true ) ;
				}
				else if ( changed.GetName() == L"U" )
				{
					bool IsLocked = prop.GetParameterValue( L"LockUV" ) ;
					if ( IsLocked )
					{
						// Note: Changing the value from
						// within the logic code will not
						// result in PPGEvent
						// being called again.  So there is
						// minimal risk of infinite loops.
						prop.PutParameterValue( L"V", prop.GetParameterValue( L"U" ) );
					}
				}
				else if ( changed.GetName() == L"V" )
				{
					bool IsLocked = prop.GetParameterValue( L"LockUV" ) ;
					if ( IsLocked )
					{
						prop.PutParameterValue( L"U", prop.GetParameterValue( L"V" ) );
					}

				}
				else if ( changed.GetName() == L"LockUV" )
				{
					bool IsLocked = prop.GetParameterValue( L"LockUV" ) ;
					if ( IsLocked )
					{
						// When locking is enabled make sure
						// that the two values snap to the same,
						// value.

						double avg = ( (double)prop.GetParameterValue( L"U" ) +
										(double)prop.GetParameterValue( L"V" ) ) / 2.0 ;

						prop.PutParameterValue( L"U", avg );
						prop.PutParameterValue( L"V", avg );
					}
				}
			}

			return CStatus::OK ;
		}
	 \endcode

	 */
	PluginItem RegisterProperty( const CString& in_strName );

	/*! Registers a Graphic Sequencer display callback.
	 \param in_strName The name of the display callback.
		<br><br>
		The first character in a display callback name must be a letter or an underscore (\c _). Subsequent
		characters can be letters, numbers, underscore (\c _) characters, or spaces.
		<br><br>
		The display callback name is used to name the callback functions such as \xt cb_XGS_Init Init \endxt
		and \xt cb_XGS_Execute Execute \endxt. For example, the \c Execute callback for a custom display
		named \c "MyDisplayPass" is \c "MyDisplayPass_Execute". If the name contains spaces (for example,
		\c "My Display Pass"), the callback function names must omit the spaces (for example,
		\c "MyDisplayPass_Execute").
	 \return The PluginItem object for the display callback.
	 */
	PluginItem RegisterDisplayCallback( const CString& in_strName );

	/*! Registers a Graphic Sequencer display pass.
	\param in_strName The name of the display pass.
		<br><br>
		The first character in a display pass name must be a letter or an underscore (\c _). Subsequent characters
		can be letters, numbers, underscore (\c _) characters, or spaces.
		<br><br>
		The display pass name is used to name the callback functions such as \xt cb_XGS_Init Init \endxt and
		\xt cb_XGS_Execute Execute \endxt. For example, the \c Execute callback for a custom display named
		\c "MyDisplayCallback" is \c "MyDisplayCallback_Execute". If the name contains spaces (for example,
		\c "My Display Callback"), the callback function names must omit the spaces (for example,
		\c "MyDisplayCallback_Execute").
	 \return The PluginItem object for the display pass.
	*/
	PluginItem RegisterDisplayPass( const CString& in_strName );

	/*! Registers a custom Menu. The menu is loaded and initialized only when the user opens it from the UI. The
	location of a menu is specified by an anchor points (see \link siMenuAnchorPoints \endlink for a complete list).
	You can register the same menu at multiple locations, and multiple menus at the same location. A menu can be a
	submenu or a flat list of items. A menu can also be dynamic or static: a dynamic menu is rebuilt every time it
	is displayed, while a static menu is built once only.

	See the Menu reference page for details about creating a custom menu.

	\param in_anchorID Specifies the location of the menu.
	\param in_menuName The name of the menu.
		<br><br>
		The first character in a menu name must be a letter or an underscore (\c _). Subsequent characters can be
		letters, numbers, underscore (\c _) characters, or spaces. If a menu name contains spaces (for example,
		\c "My Custom Menu"), the names of the menu callback functions must omit the spaces (for example,
		\c "MyCustomMenu_Init").
		<br><br>
		If the menu is a submenu (\c in_bDisplayAsSubmenu \c == \c true), or if the menu is added to the top-level
		of the Softimage main menubar (\c n_anchorID \c == ::siMenuMainTopLevelID), then the menu name is used as
		the menu caption.
		<br><br>
		You cannot change the caption of a top-level menu. For all other menus, you can change the caption by
		calling Menu::PutName in the \xt cb_Menu_Init Init \endxt callback.
	\param in_bDisplayAsSubmenu Display the custom menu as a submenu.
	\param in_bDynamicMenu Sets the menu as dynamic or static: a dynamic menu is always rebuilt before the menu opens
		whereas static menus are only built once.
	\return The PluginItem object created for the menu.
	*/
	PluginItem RegisterMenu(	siMenuAnchorPoints	in_anchorID,
								const CString&		in_menuName,
								bool				in_bDisplayAsSubmenu=true,
								bool				in_bDynamicMenu=true );

	/*! Registers a regular custom Command in Softimage. The command will not register if a name clash occurs with another
	command.  Using a consistent prefix or other naming convention can help avoid any conflicts with other commands. For
	example, \c "iy_Help" is less likely to be a duplicate than \c "Help".

	\param in_commandScriptName The scripting name of the command.
		<br><br>
		To allow users to easily execute the command in scripts or in compiled code, the first character in the scripting
		name must be a letter. Subsequent characters can be letters, numbers, or underscore (\c _) characters.
		<br><br>
		Otherwise, if you use a scripting name like \c "123DoIt" or \c "Do It", the only way to execute the command
		is with Command::Execute and Application::ExecuteCommand. Note also that a scripting name like \c "_DoIt" will
		not work in VBScript, because VBScript does not allow the underscore as the first character in an identifier.

	\return The PluginItem object for the command.
	\since 5.1
	*/
	PluginItem RegisterCommand( const CString&	in_commandScriptName );

	/*! Registers a custom Command in Softimage. This variation makes it possible to provide a different command name and
	command scripting name. This approach can cause some confusion and is no longer recommended. Instead it is better to
	set a descriptive label on the menu or toolbar itself.

	\param in_commandName The name of the custom command. The first character in a command name must be a letter or an
		underscore (\c _). Subsequent characters can be letters, numbers, underscore (\c _) characters, or spaces.
		<br><br>
		The command name is used to name the command callback functions such as \xt cb_Command_Execute Execute \endxt
		and \xt cb_Command_Init Init \endxt. For example, the \c Execute callback for a command named \c "MyCommand"
		is \c "MyCommand_Execute". If a command name contains spaces (for example, \c "My Simple Command"), then you
		remove the spaces in the callback function names (for example, \c "MySimpleCommand_Init" and
		\c "MySimpleCommand_Execute").
		<br><br>
		The command name also appears in the Softimage user interface, and is the name of the command in the CommandArray
		returned by Application::GetCommands. It is also the name you use when you call Menu::AddCommandItem.
		<br><br>
		Command names must be unique. To avoid naming conflicts, we recommend using a prefix based on your company name
		or the plug-in name (for example, \c "ACME_TornadoKit_Apply").

	\param in_commandScriptName The scripting name of the command.
		<br><br>
		To allow users to easily execute the command in scripts or in compiled code, the first character in the scripting
		name must be a letter. Subsequent characters can be letters, numbers, or underscore (\c _) characters.
		<br><br>
		Otherwise, if you use a scripting name like \c "123DoIt" or \c "Do It", the only way to execute the command is with
		Command::Execute and Application::ExecuteCommand. Note also that a scripting name like \c "_DoIt" will not work in
		VBScript, because VBScript does not allow the underscore as the first character in an identifier.

	\return The PluginItem object for the command.
	*/

	PluginItem RegisterCommand(	const CString&	in_commandName,
								const CString&	in_commandScriptName );

	/*! Registers a custom Event.

	\param in_eventName The name of the event.
		<br><br>
		The first character in an event name must be a letter or an underscore (\c _). Subsequent characters can be
		letters, numbers, underscore (\c _) characters, or spaces.
		<br><br>
		The event name is used to name the \xt cb_Event_OnEvent OnEvent \endxt callback function. For example, the
		\c OnEvent callback for an event named \c "MySelectionChange" is \c "MySelectionChange_OnEvent". If an event
		name contains spaces (for example, \c "My Selection Change"), the \c OnEvent callback function name must omit
		the spaces (for example, \c "MySelectionChange_OnEvent").
		<br><br>
		This name is also the name of the event in the array returned by Application::GetEventInfos.
	\param in_eventID Type of event to register.
	\note The following identifiers are valid but not supported: \c siOnWindowEvent, \c siOnTimer.
	\return Newly created event PluginItem object.
	\since 5.0
	*/
	PluginItem RegisterEvent( const CString& in_eventName, const siEventID in_eventID );

	/*! Registers a TimerEvent. A %TimerEvent invokes an event callback at specific timed intervals. You can also
	specify the delay time at which the event callback is called for the first time. This function doesn't require
	an event type argument as the event created is of type ::siOnTimer.

	\param in_eventName The name of the event.
		<br><br>
		The first character in an event name must be a letter or an underscore (\c _). Subsequent characters can be
		letters, numbers, underscore (\c _) characters, or spaces.
		<br><br>
		The event name is used to name the \xt cb_Event_OnEvent OnEvent \endxt callback function. For example, the
		\c OnEvent callback for an event named \c "MyTimer" is \c "MyTimer_OnEvent". If an event name contains spaces
		(for example, \c "My timer Change"), the OnEvent callback function name must omit the spaces (for example,
		\c "MyTimer_OnEvent").
		<br><br>
		This name is also the name of the event in the array returned by Application::GetEventInfos.

	\param in_nInterval The interval time value in milliseconds. This value specifies the amount of time to wait between
		each callback invocation. If the value is 0, the event timer is stopped (muted) after the first invocation. The
		timer can be restarted again by un-muting the event. If the value > 0, the timer will elapse indefinitely.

	\param in_nDelay The delay value, in milliseconds, is the amount of time to wait until the callback is first invoked.
		By default, the delay time is 0 and the timer starts immediately.

	\return Newly created timer event PluginItem object.

	\sa EventInfo::PutMute, ::siOnTimer
	\since 5.1
	*/
	PluginItem RegisterTimerEvent(	const CString&	in_eventName,
									LONG			in_nInterval,
									LONG			in_nDelay=0 );

	/*! Registers a ConverterEvent. A %ConverterEvent's callback is invoked whenever a file using a custom-defined file
	type has to be imported or exported.

	\param in_eventName The name of the event.
		<br><br>
		The first character in an event name must be a letter or an underscore (\c _). Subsequent characters can be letters,
		numbers, underscore (_) characters, or spaces.
		<br><br>
		The event name is used to name the \xt cb_Event_OnEvent OnEvent \endxt callback function. For example, the \c OnEvent
		callback for an event named \c "MyConverter" is \c "MyConverter_OnEvent". If an event name contains spaces (for example,
		\c "My Converter"), the OnEvent callback function name must omit the spaces (for example, \c "MyConverter_OnEvent").
		<br><br>
		This name is also the name of the event in the array returned by Application::GetEventInfos.
	\param in_eventID Type of event to register. Allowed IDs are ::siOnCustomFileImport and ::siOnCustomFileExport.
	\param in_eventExtension The file Extension to register the converter event for. The Extension should not contain any
		delimiters and be uppercase, so \c "TXT" for example is the extension for a file like \c "myfile.txt".

	\return Newly created converter event PluginItem object.
	\sa PPGEventContext
	\since 6.0
	*/
	PluginItem RegisterConverterEvent(	const CString&	in_eventName,
										const siEventID	in_eventID,
										const CString&	in_eventExtension );

	/*! Registers a custom Operator as a PluginItem object.

	\param in_name User-defined name of the operator to register.
		<br><br>
		The first character in an operator name must be a letter or an underscore (\c _). Subsequent characters can be letters,
		numbers, underscore (\c _) characters, or spaces.
		<br><br>
		The operator name is used to name the operator callback functions. For example, the \xt cb_Operator_Update Update \endxt
		callback for an operator named \c "Shake" is \c "Shake_Update". If an operator name contains spaces (for example,
		\c "Shake And Roll"), the Update callback function name must omit the spaces (for example, \c "ShakeAndRoll_Update").

	\return Newly created custom operator PluginItem object.
	\since 5.1
	*/
	PluginItem RegisterOperator( const CString& in_name );

	/*! Registers a custom Renderer as a PluginItem object.

	\param in_name User-defined name of the renderer to register.
		<br><br>
		The first character in an renderer name must be a letter or an underscore (\c _). Subsequent characters can be letters,
		numbers, underscore (\c _) characters, or spaces.
		<br><br>
		The renderer name is used to name the renderer callback functions. For example, the \xt cb_Renderer_Init Init \endxt
		callback for a renderer named \c "Fiesta" is \c "Fiesta_Init". If a renderer name contains spaces (for example,
		\c "Awesome Renderer"), the \c Init callback function name must omit the spaces (for example, \c "AwesomeRenderer_Init").

	\return Newly created custom renderer PluginItem object.
	\sa RendererContext
	\since 6.0
	*/
	PluginItem RegisterRenderer( const CString& in_name );

	/*! Registers a custom ICENode as a PluginItem object.
	\param in_nodedef An ICENodeDef object describing the new node.
		<br><br>
		The first character in an ICENode name must be a letter or an underscore (\c _). Subsequent characters can be letters,
		numbers, underscore (\c _) characters, or spaces.
		<br><br>
		The ICENode name is used to name the ICENode callback functions. For example, the \xt cb_ICENode_Evaluate Evaluate \endxt
		callback for an ICENode named \c "Drip" is \c "Drip_Evaluate". If an ICENode name contains spaces (for example,
		\c "Chilly Bean"), the \c Evaluate callback function name must omit the spaces (for example, \c "ChillyBean_Evaluate").

	\return Newly created custom %ICENode PluginItem object.
	\sa ICENodeContext
	\since 7.0
	*/
	PluginItem RegisterICENode( const ICENodeDef& in_nodedef );

	/*! Registers a custom primitive type.
	\param in_name User-defined name of the new primitive type.
		<br><br>
		The first character in a custom primitive name must be a letter or an underscore (\c _). Subsequent characters can be
		letters, numbers, underscore (\c _) characters, or spaces.
		<br><br>
		The primitive type name must be unique.
	\return Newly created custom primitive type PluginItem object.
	\since 12.0 (2014)
	*/
	PluginItem RegisterPrimitive( const CString& in_name );

	/*! Registers a shader language parser as a PluginItem object.
	\param in_strParserName The name of the Parser to Register.
	\return Newly created custom shader language parser PluginItem object.
	\sa \xt cb_shaderparser Definition Callbacks for Shader Language Parsers \endxt
	\sa \xt cus_shaders_CreatingShaderParsers Creating Shader Language Parsers \endxt
	\since 9.0 (2011)
	*/
	PluginItem RegisterShaderLanguageParser( const CString& in_strParserName );

	/*! Registers a custom shader as a PluginItem object.
	\param in_strShaderClassName The class name of the ShaderDef to Register. This defines the classname part of the shader progid.
	\param in_ulMajorVersion The major version of the ShaderDef to Register. This defines the major version part of the shader progid.
	\param in_ulMinorVersion The minor version of the ShaderDef to Register. This defines the minor version part of the shader progid.
	\return Newly created custom shader language parser PluginItem object.
	\note The shader ProgID will be build from the PluginName, ShaderClassName and Major and Minor versions.
	\sa \xt cb_shader Definition Callbacks for Shaders \endxt
	\sa \xt cus_shaders_CreatingDefPlugins Creating Shader Definition Plug-ins \endxt
	\since 9.0 (2011)
	*/
	PluginItem RegisterShader( const CString& in_strShaderClassName, ULONG in_ulMajorVersion, ULONG in_ulMinorVersion );

	/*! Registers a custom tool. When the tool is registered a custom script command of the same name
	is registered which is used to invoke the tool or can be assigned to a keyboard shortcut in the
	keyboard mapping dialog.

	See the ToolContext reference page for details about creating a custom tool.

	\param in_name The name of the tool.
		<br><br>
		The first character in a tool name must be a letter or an underscore (\c _). Subsequent characters can be
		letters, numbers, underscore (\c _) characters.
		<br><br>
		The tool name must be unique.
	\return The PluginItem object created for the tool.
	\since 10.0 (2012)
	*/
	PluginItem RegisterTool( const CString& in_name );

	/*!	Returns the name of the plug-in author.
	\return CString
	 */
	CString GetAuthor() const;

	/*! Returns the URL path that can be used to link to a help page for the
	plug-in (for example, the web site of the plug-in's author).
	\return CString
	 */
	CString GetURL() const;

	/*! Returns the email address of the plug-in (for example, the email address
	of the plug-in's author).
	\return CString
	 */
	CString GetEmail() const;

	/*! Returns the plug-in version.

	\retval out_major Major version number.
	\retval out_minor Minor version number.

	\return CStatus OK if successful.
	 */
	CStatus GetVersion( LONG& out_major, LONG& out_minor ) const;

	/*!	Returns the name of the language used to implement the plug-in. \c VBScript,
	\c JScript, \c Python, \c C# and \c C++ are all valid languages.

	\return CString
	*/
	CString GetLanguage() const;

	/*!	Returns the filename of the plug-in.
	\return CString
	*/
	CString GetFilename() const;

	/*! Sets the name of the author of the plug-in.
	\param in_strName The name of the plug-in's author.
	\return CStatus OK if successful
	*/
	CStatus PutAuthor( const CString& in_strName );

	/*! Sets the author's URL path (for example, the URL to your company's website).
	\param in_strURL The URL path.
	\return CStatus OK if successful
	*/
	CStatus PutURL( const CString& in_strURL );

	/*! Sets the author's email address (for example, a support contact).
	\param in_strEmail The email address.
	\return CStatus OK if successful
	*/
	CStatus PutEmail( const CString& in_strEmail );

	/*! Sets the plug-in version.
	\param in_major Major version number.
	\param in_minor Minor version number.
	\return CStatus OK if successful.
	*/
	CStatus PutVersion( LONG in_major, LONG in_minor );

	/*! Sets the help path for the plug-in being registered.

	By default, Softimage looks for a plug-in help file in the "doc" subfolder of the plug-in 
	installation folder. Softimage assumes the help file has the same name as the plug-in. For example, 
	if the plug-in MyPlugin.dll is located in the folder "C:\MyWorkgroup\Application\Plugins" 
	then Softimage looks in the folder "C:\MyWorkgroup\Application\Plugins\Doc" for a help file named 
	MyPlugin.html or MyPlugin.htm.

	If a plug-in help file has a different name or location, you can call this method
	to specify the name of help file and, optionally, its location.

	\param in_strHelp The help path
	\return CStatus OK if successful
	\return CStatus Fail if not successful
	*/
	CStatus PutHelp( const CString& in_strHelp );

	/*! Returns the help button file replacing the factory "?" button for all plug-in items
	of this plug-in which support a property page.

	\return The help button file of the plug-in. An empty string is returned if the plug-in has no help button file.
	\since 13.0 (2015)
	*/
	CString GetHelpButton() const;

	/*! Sets the help button file replacing the factory "?" button in the property pages of the plug-in items
	of this plug-in being registered.

	The help button will be shown in a plug-in item property page only if there is a help file
	associated with the plug-in item.
	
	The plug-in help button file must be a BMP file with a height of 18 pixels and a width no wider than 100 pixels.
	If the help button file doesn't respect the criteria, the factory "?" button will be displayed in the plug-in items property pages.

	By default, Softimage looks for a plug-in help button file in the "doc" subfolder of the plug-in 
	installation folder. Softimage assumes the help button file has the same name as the plug-in, with
	the "_HelpButton" string appended to it. For example, if the plug-in MyPlugin.dll is located in 
	the folder "C:\MyWorkgroup\Application\Plugins" then Softimage looks in the folder 
	"C:\MyWorkgroup\Application\Plugins\Doc" for a help button file named MyPlugin_HelpButton.bmp.

	If a plug-in help button file has a different name or location, you can call this method
	to specify the name of help button file and, optionally, its location.
	
	\param in_strHelpButton The help button path.
	\return CStatus::OK if successful.
	\return CStatus::Fail if not successful.
	\since 13.0 (2015)
	*/
	CStatus PutHelpButton( const CString& in_strHelpButton );

	/*! Sets the categories for the plug-in being registered.
	\param in_strCat A comma-separated string representing the user-defined
		categories of the plug-in.
	\return CStatus OK if successful
	*/
	CStatus PutCategories( const CString& in_strCat );

	/*! Stores a CValue inside the plug-in object being registered. Softimage does not care about the content or meaning of the data.
	Once created, the data remains active as long as Softimage is running or until you manually unload the plug-in.

	You can use this to store a value to be accessed locally in the plug-in module or accessed globally by other plug-ins. The
	user data is not persisted.
	\warning In the case where a pointer is stored, the object should be destroyed during the \xt cb_Plugin_Unload UnloadPlugin \endxt callback.

	\param in_userdata User data to set.
	\sa \xl Plugin.UserData, Plugin::PutUserData
	\return CStatus::OK success
	\return CStatus::Fail failure.
	\since 8.0 (2010)
	*/
	CStatus PutUserData( const CValue& in_userdata ) ;

	/*! Returns the user data stored in the plug-in referred by this PluginRegistrar object.
	\return The user data value.
	\since 8.0 (2010)
	*/
	CValue GetUserData( ) const;

	private:
	PluginRegistrar * operator&() const;
	PluginRegistrar * operator&();
};

};

#endif // __XSIPluginRegistrar_H__
