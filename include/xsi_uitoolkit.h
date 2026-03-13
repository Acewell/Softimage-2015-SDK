//*****************************************************************************
/*!
   \file xsi_uitoolkit.h
   \brief UIToolkit class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIUITOOLKIT_H__
#define __XSIUITOOLKIT_H__

#include <xsi_base.h>
#include <xsi_value.h>
#include <xsi_status.h>

#ifdef _MSC_VER
#pragma warning(disable:4251)
#endif

namespace XSI {

class ProgressBar;

//*****************************************************************************
/*! \class UIToolkit xsi_uitoolkit.h
	\brief Provides access to Softimage user interface tools such as the ProgressBar object and
	the MsgBox function.

	\sa Application::GetUIToolkit
*/
//*****************************************************************************

class SICPPSDKDECL UIToolkit : public CBase
{
public:
	/*! Default constructor. */
	UIToolkit();

	/*! Default destructor. */
	~UIToolkit();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	UIToolkit(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	UIToolkit(const UIToolkit& in_obj);

	/*! Returns true if a given class type is compatible with this API class.
	\param in_ClassID class type.
	\return true if the class is compatible, false otherwise.
	*/
	bool IsA( siClassID in_ClassID) const;

	/*! Returns the type of the API class.
	\return The class type.
	*/
	siClassID GetClassID() const;

	/*! Creates an object from another object. The newly created object is set to empty
	if the input object is not compatible.
	\param in_obj constant class object.
	\return The new UIToolkit object.
	*/
	UIToolkit& operator=(const UIToolkit& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new UIToolkit object.
	*/
	UIToolkit& operator=(const CRef& in_ref);

	/*! Returns an instance of a ProgressBar object.
	\return Instance of a ProgressBar object.
	*/
	ProgressBar GetProgressBar() const;

	/*! This is identical to the Win32 MessageBox function and provides the ability to pop
	up a simple modal message window in Softimage. The application is frozen and the user is
	forced to click a button to dismiss the window.

	By default only an OK button is displayed, but flags like ::siMsgAbortRetryIgnore and
	::siMsgYesNo are supported to change this behavior. By default no icon is displayed, but
	flags like ::siMsgQuestion can be used to help indicate the nature and importance of the
	message (see ::siMsgBoxFlags).

	This function does not block execution of scripts in batch mode. When Softimage runs in
	batch mode the routine returns immediately with the default button as the returned value.
	By default the first button is considered the default button, but this can be changed by
	specifying the flag ::siMsgDefaultButton2 or ::siMsgDefaultButton3.

	For further details please refer the Win32 documentation on MessageBox.

	\param in_strMsg Message to display on the screen.
	\param in_Flags Flags to control the appearance of the dialog (see ::siMsgBoxFlags).
	\param in_strCaption Text to show in the title of the Message Box. Often this is used to
		describe the source of the message box, for example the name of a plug-in or perhaps
		a script filename. By default the standard Softimage title is used.
	\retval out_result The button pressed as defined in ::siMsgButtonPressed.

	\return CStatus::OK success
	\return CStatus::Fail failure
	*/
	CStatus MsgBox( const CString& in_strMsg, LONG in_Flags,
		const CString& in_strCaption, LONG& out_result );

	private:
	UIToolkit * operator&() const;
	UIToolkit * operator&();
};

};
#endif // __XSIUITOOLKIT_H__
