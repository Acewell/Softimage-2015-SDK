//*****************************************************************************
/*!
   \file xsi_view.h
   \brief View class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIVIEW_H__
#define __XSIVIEW_H__

#include <xsi_uipersistable.h>
#include <xsi_value.h>
#include <xsi_status.h>

#ifdef _MSC_VER
#pragma warning(disable:4251)
#endif

namespace XSI {

class View;

//*****************************************************************************
/*! \class View xsi_view.h
	\brief The View object represents an instance of a view in Softimage.

	Views are accessible from Layout::GetViews or View::GetViews if the view is a
	relational view. View objects are created with Layout::CreateView.

	With view objects, you can:
	\li Change the view state such as closed and minimized state.
	\li Change the view position and size.
	\li Hide/unhide the view.
	\li Access to specific view attributes such as the Explorer scope and NetView URL.
	\li Edit view attributes in bulk mode to avoid the UI to flicker.
	\li Iterate over the sub views of a relational view.

	\since 4.0

	\eg This example restores and cascades all floating views except the script editor.
	\code
		Application app;

		// Creates some sample views
		Layout layout = app.GetDesktop().GetActiveLayout();

		View v;
		layout.CreateView( L"Explorer", L"My Explorer", v );
		layout.CreateView( L"Browser", L"My Browser", v );
		layout.CreateView( L"NetView", L"My NetView", v );

		// position for the first view to cascade
		LONG px = 50;
		LONG py = 20;

		// delta between each view
		LONG dx = 20;
		LONG dy = 20;

		CRefArray views = layout.GetViews();
		for ( LONG i=0; i<views.GetCount() ; i++)
		{
			View vw = views[i];
			if( vw.GetFloating() && vw.GetName() != L"script_editor" )
			{
				vw.Move( px, py );
				px += dx;
				py += dy;
				vw.PutState( siNormal ); // put view at the top so far
			}
		}

	\endcode
*/
//*****************************************************************************

class SICPPSDKDECL View : public UIPersistable
{
public:
	/*! Default constructor. */
	View();

	/*! Default destructor. */
	~View();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	View(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	View(const View& in_obj);

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
	\return The new View object.
	*/
	View& operator=(const View& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new View object.
	*/
	View& operator=(const CRef& in_ref);

	/*! Returns an array of View objects defined for this View. A View can have
	sub views if it was defined as a relational view.
	\return Array of View objects.
	*/
	CRefArray GetViews() const;

	/*! Finds a view in this layout from a specific view name. 

	\param in_strViewName The name of the view to find.
	\return The newly created view object.
	*/
	View FindView( const CString& in_strViewName );

	/*! Returns the state of a view. View states are mutually exclusive.
	\return The View state value.
	*/
	siViewState GetState() const;

	/*! Sets the state of a view. View states are mutually exclusive.
	\param in_lState View state value.
	\return CStatus::OK success
	\return CStatus::Fail failure
	*/
	CStatus PutState( siViewState in_lState );

	/*! Returns true if the view is visible or false otherwise.
	\return true if the view is visible; false otherwise.
	*/
	bool GetVisible() const;

	/*! Make the view visible if the flag is true or hidden otherwise.
	\param in_bFlag Visible flag.
	\return CStatus::OK success
	\return CStatus::Fail failure
	*/
	CStatus PutVisible( bool in_bFlag );

	/*! Returns true if the view is floating or false if the view is embedded
	inside another one.
	\return true if the view is floating; false if embedded inside another one.
	*/
	bool GetFloating() const;

	/*! Returns a view specific attribute value.
	\param in_strParamName Name of the attribute.
	\return The Attribute value.
	*/
	CValue GetAttributeValue( const CString& in_strParamName ) const;

	/*! Sets a view specific attribute value.
	\param in_strParamName Name of the attribute.
	\param in_value The new attribute value.
	\return CStatus::OK success
	\return CStatus::Fail failure
	*/
	CStatus PutAttributeValue( const CString& in_strParamName,
		const CValue& in_value );

	/*! Puts the view in edit mode. The edit mode allows you to change several
	view attributes in bulk without affecting the current UI. Call the
	View::EndEdit method to quit the edit mode.
	\return CStatus::OK success
	\return CStatus::Fail failure
	*/
	CStatus BeginEdit();

	/*! Requests an end to an edit operation on this View. This function updates
	the view with the attribute changes performed so far. This has no effect
	if the view is not in edit mode.
	\return CStatus::OK success
	\return CStatus::Fail failure
	*/
	CStatus EndEdit();

	/*! Moves a view to the specified global screen coordinate.
	\param in_x Position in X.
	\param in_y Position in Y.
	\return CStatus::OK success
	\return CStatus::Fail failure
	*/
	CStatus Move( LONG in_x, LONG in_y );

	/*! Changes the size of a view.
	\param in_w New width.
	\param in_h New height
	\return CStatus::OK success
	\return CStatus::Fail failure
	*/
	CStatus Resize( LONG in_w, LONG in_h );

	/*! Returns the rectangle of a view in screen coordinates.
	\retval out_lLeft	Returns the left screen coordinate of a view.
	\retval out_lTop	Returns the top screen coordinate of a view.
	\retval out_lRight	Returns the right screen coordinate of a view.
	\retval out_lBottom	Returns the bottom screen coordinate of a view.
	\return CStatus::OK success
	\return CStatus::Fail failure
	\since 9.0 (2011)
	*/
	CStatus GetRectangle( LONG& out_lLeft, LONG& out_lTop, LONG& out_lRight, LONG& out_lBottom ) const;

	/*! Refreshes the underlying view. This function is supported on views such as "Preset Manager" and "Render Tree".

	\return CStatus::OK Success.
	\return CStatus::NotImpl Not implemented on this view.
	\return CStatus::Fail Failure.
	\since 9.0 (2011)
	*/
	CStatus Refresh( );

	/*! Rearrange the selected nodes. If no nodes selected, rearrange all nodes. This function is supported on views such as 
	"ICE Tree" and "Render Tree".

	\return CStatus::OK Success.
	\return CStatus::NotImpl Not implemented on this view.
	\return CStatus::Fail Failure.
	\since 10.0 (2012)
	*/
	CStatus Rearrange( );

	/*! Returns an array of MemoCamera objects for a view.
	\return Array of MemoCamera objects.
	\since 10.5 (2012)
	*/
	CRefArray GetMemoCameras( ) const;

	private:
	View * operator&() const;
	View * operator&();
};

};
#endif // __XSIVIEW_H__
