//*****************************************************************************
/*!	\file xsi_comapihandler.h
 	\brief CComAPIHandler class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __CCOMAPIHANDLER__H_
#define __CCOMAPIHANDLER__H_

#include <xsi_ref.h>
#include <xsi_string.h>
#include <xsi_value.h>
#include <xsi_status.h>

namespace XSI {

//*****************************************************************************
/*! \class CComAPIHandler xsi_comapihandler.h
 	\brief The CComAPIHandler class implements a C++ wrapper for calling automation objects
 	(scripting objects) or objects implemented using the Softimage Object %Model (formerly
 	called the \a COM \a API).

	Automation objects can be created from C++ using CComAPIHandler::CreateInstance. The handler
	provides access to an automation object's methods and properties via CComAPIHandler::Call,
	CComAPIHandler::GetProperty, CComAPIHandler::PutProperty and CComAPIHandler::Invoke.

	\sa ::ConvertObject

	\eg
	\code
		using namespace XSI;
		CStatus st;

		CComAPIHandler xsiuitoolkit;

		xsiuitoolkit.CreateInstance( L"XSI.UIToolkit");

		CValue return = xsiuitoolkit.GetProperty( L"ProgressBar" );

		// The return contains a pointer to the progressbar
		// that has had its reference count incremented, the destructor of CValue
		// takes care of dereferencing the pointer.
		CComAPIHandler progressbar( return );

		// set min/max
		progressbar.PutProperty( L"Minimum", (LONG)1 );
		progressbar.PutProperty( L"Maximum", (LONG)200 );
		progressbar.PutProperty( L"Value", (LONG)195 );
		progressbar.PutProperty( L"Caption", CValue(L"My Caption") );

		return = progressbar.GetProperty( L"Value" );

		// show the progress bar
		progressbar.PutProperty( L"Visible", true );

		while ( (progressbar.GetProperty( L"CancelPressed" ) == false) &&
			((LONG)return < 200))
		{
			// your code here

			progressbar.Call( L"Increment", return );
		}

		// Just for good measure. If you put break points in the
		// code sometimes the progress dialog doesn't go away.
		progressbar.PutProperty( L"Visible", false );

	\endcode
 */
//*****************************************************************************

class SICPPSDKDECL CComAPIHandler
{
public:
	/*! Flags to specify the context for the CComAPIHandler::Invoke function. */
	enum InvokeFlag
	{
		Method,				/*!< Invokes a Method */
		PropertyGet,		/*!< Invokes getting a Property */
		PropertyPut,		/*!< Invokes setting a Property */
		PropertyPutRef		/*!< Invokes setting a Property with a pointer */
	};

	/*! Default constructor. */
	CComAPIHandler();

	/*! Default destructor. */
	virtual ~CComAPIHandler();

	/*! Constructor.
	\param in_val Contains a reference to a Softimage Object %Model object.

	\eg Demonstrates how it is possible to access properties exposed on Softimage objects using the
		object model interface rather than the C++ API.  This approach is important for accessing
		any method or property that is available in the object model but not the C++ API.

	\code
		using namespace XSI ;
		Application app ;
		Model root = app.GetActiveSceneRoot();

		X3DObject arc;
		root.AddGeometry( L"Arc", L"NurbsCurve", L"AnArc", arc ) ;

		// Construct a CComAPIHandler representing the newly created arc object
		CComAPIHandler omArc( arc.GetRef() );

		// Now we can use the object model to modify the object.
		// In this case we change the name property.
		omArc.PutProperty( L"Name", L"MyArc" ) ;

		// Retrieve the object name using the Name property
		CValue nameFromCOMAPI = omArc.GetProperty( L"Name" ) ;
		app.LogMessage( L"Softimage OM SIObject::Name property returns: " + nameFromCOMAPI.GetAsText() ) ;

		// In this case the same property is available directly from the C++ API
		// so we didn't really need to use CComAPIHandler
		CString nameFromCppAPI = arc.GetName() ;
		app.LogMessage( L"C++ API SIObject::GetName returns: " + nameFromCppAPI ) ;

		// Expected results:
		//'INFO : Softimage OM SIObject::Name property returns: MyArc
		//'INFO : C++ API SIObject::GetName returns: MyArc
	\endcode
	*/
	CComAPIHandler( const CValue& in_val );

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	CComAPIHandler(const CComAPIHandler& in_obj);

	/*! Assignment operator
	\param in_obj CComAPIHandler to copy.
	*/
	CComAPIHandler& operator=( const CComAPIHandler& in_obj);

	/*! Creates an automation object and attaches it to the CComAPIHandler object. If you try to create an
	automation object that doesn't exist an error (CStatus::Fail) occurs.
	\param in_name \c ProgID of the Softimage OM object to create. The ProgID is a string found in the Registry, that
		maps to the \c CLSID of the object.  For example \c XSI.UIToolkit and \c Scripting.FileSystemObject.
	\return CStatus::OK	success
	\return CStatus::Fail other failure
	*/
	CStatus CreateInstance( const CString& in_name );

	/*! Attaches an automation object or Softimage object to the CComAPIHandler object. The CValue can be set
	either with a CRef object or with a pointer to an object model interface. CComAPIHandler takes care of
	handling the reference counting on the underlying Softimate OM object.
	\param in_val CValue to attach
	\return CStatus::OK	Success
	\return CStatus::InvalidArgument Invalid referance object
	\return CStatus::Fail Other failure
	*/
	CStatus Attach( const CValue& in_val );

	/*! Detaches an automation object pointer from the CComAPIHandler object.
	\return CStatus::OK Success
	\return CStatus::Fail Other failure
	*/
	CStatus Detach(void);

	/*! Returns the property value.
	\param in_name The name of the property.
	\return The property value.
	*/
	CValue GetProperty(const CString& in_name ) const;

	/*! Sets the property value. If you try to set a read-only property, an error (CStatus::AccessDenied) occurs.
	If you try to call a method that doesn't exist an error (CStatus::MemberNotFound) occurs.
	\param in_name The name of the property.
	\param in_newval The new property value.
	\return CStatus::OK Success
	\return CStatus::Fail Other failure
	\return CStatus::AccessDenied Trying to set a read-only parameter.
	\return CStatus::MemberNotFound Property does not exist.
	*/
	CStatus PutProperty( const CString& in_name, const CValue& in_newval ) const;

	/*! Calls the object method specified by name. If you try to call a method that doesn't exist an error
	(CStatus::MemberNotFound) occurs.
	\param in_name The name of the method.
	\param io_return The return value.
	\param in_args Array of arguments passed through to the method to call,
	\return CStatus::OK	Success
	\return CStatus::Fail Other failure
	\return CStatus::AccessDenied Trying to set a read-only parameter.
	\return CStatus::MemberNotFound	Method does not exist.
	*/
	CStatus Call(	const CString& in_name,
					CValue& io_return,
					const CValueArray& in_args = CValueArray() ) const;

	/*! Calls the object method specified by name. This version is convenient for calling a method that takes one argument.
	If you try to call a method that doesn't exist an error (CStatus::MemberNotFound) occurs.
	\param in_name The name of the property.
	\param io_return The return value.
	\param in_arg The argument passed through to the method.
	\return CStatus::OK Success
	\return CStatus::Fail Other failure
	\return CStatus::AccessDenied Trying to set a read-only parameter.
	\return CStatus::MemberNotFound Method does not exist.
	*/
	CStatus Call(	const CString& in_name,
					CValue& io_return,
					const CValue& in_arg ) const;

	/*! Calls the object method specified by name. This version is convenient for calling a method that takes two arguments.
	If you try to call a method that doesn't exist an error (CStatus::MemberNotFound) occurs.
	\param in_name The name of the property.
	\param io_return The return value.
	\param in_arg The first argument passed through to the method.
	\param in_arg1 The second argument passed through to the method.
	\return CStatus::OK	Success
	\return CStatus::Fail Other failure
	\return CStatus::AccessDenied Trying to set a read-only parameter.
	\return CStatus::MemberNotFound	Method does not exist.
	*/
	CStatus Call(	const CString& in_name,
					CValue& io_return,
					const CValue& in_arg,
					const CValue& in_arg1 ) const;

	/*! Calls the object method specified by name. This version is convenient for calling a method that takes three arguments.
	If you try to call a method that doesn't exist an error (CStatus::MemberNotFound) occurs.
	\param in_name The name of the property.
	\param io_return The return value.
	\param in_arg The first argument passed through to the method.
	\param in_arg1 The second argument passed through to the method.
	\param in_arg2 The third argument passed through to the method.
	\return CStatus::OK	Success
	\return CStatus::Fail Other failure
	\return CStatus::AccessDenied Trying to set a read-only parameter.
	\return CStatus::MemberNotFound	Method does not exist.
	*/
	CStatus Call(	const CString& in_name,
					CValue& io_return,
					const CValue& in_arg,
					const CValue& in_arg1,
					const CValue& in_arg2 ) const;

	/*! Calls the object method specified by name. This version is convenient for calling a method that takes four arguments.
	If you try to call a method that doesn't exist an error (CStatus::MemberNotFound) occurs.
	\param in_name The name of the property.
	\param io_return The return value.
	\param in_arg The first argument passed through to the method.
	\param in_arg1 The second argument passed through to the method.
	\param in_arg2 The third argument passed through to the method.
	\param in_arg3 The fourth argument passed through to the method.
	\return CStatus::OK	Success
	\return CStatus::Fail Other failure
	\return CStatus::AccessDenied Trying to set a read-only parameter.
	\return CStatus::MemberNotFound	Method does not exist.
	*/
	CStatus Call(	const CString& in_name,
					CValue& io_return,
					const CValue& in_arg,
					const CValue& in_arg1,
					const CValue& in_arg2,
					const CValue& in_arg3 ) const;

	/*! Calls the object method or property specified by name, in the context specified by \c in_flags. If you try to call a
	method or property that doesn't exist an error (CStatus::MemberNotFound) occurs.

	\note A common use of this function is to get a property that uses input parameters; for example, the 'Item' property
		on a collection that needs to specify the index or name of the item to retrieve from the collection.

	\eg This example demonstrates how to use the %CComAPIHandler to browse the list of selected components (since the
		SubComponent class is not fully implemented in the C++ API).

	\code
		// Make sure something is selected
		Selection sel = app.GetSelection();
		LONG lCount = sel.GetCount();
		app.LogMessage(L"Found " + CString(lCount) + L" selected items.");
		if ( lCount < LONG(1) )
		{
			app.LogMessage( L"No components are selected" );
			return CStatus::OK;
		}
		for ( LONG i=0; i<lCount; i++ )
		{
			if ( sel.GetItem(i).GetClassIDName() == L"X3DObject" )
			{
				X3DObject x3dobj(sel.GetItem(i));
				app.LogMessage(L"\titem[" + CString(i) + L"]: " + x3dobj.GetName() );
			}
			else
			{
				app.LogMessage(L"\titem[" + CString(i) + L"]: " + sel.GetItem(i).GetClassIDName() );
			}
		}

		// The collection of selected components exists in the first member
		CComAPIHandler comCollItem( sel.GetItem(0) );
		CComAPIHandler comSubComp( comCollItem.GetProperty(L"SubComponent") );
		CValue subCompType = comSubComp.GetProperty( L"Type" );
		app.LogMessage( L"Type of subcomponent: " + CString(subCompType) );

		// Grab the component collection
		CComAPIHandler comCompColl( comSubComp.GetProperty(L"ComponentCollection") );

		// Now we can iterate over the component collection's members
		LONG lCollCount( comCompColl.GetProperty(L"Count") );
		app.LogMessage(L"Found " + CString(lCollCount) + L" selected components.");
		for ( LONG j=0; j<lCollCount; j++ )
		{
			CValue rtn; 							// output from the Item property
			CValueArray idx; idx.Add(j);			// set the index to use
			comCompColl.Invoke( L"Item", CComAPIHandler::PropertyGet, rtn, idx );

			// From the CRef class, we can convert it to the actual class
			CRef itm(rtn);
			if ( itm.GetClassID() == siVertexID )
			{
				Vertex vtx = Vertex(itm);
				app.LogMessage( L"Found a vertex at index " + CString(vtx.GetIndex()) );
			}
			if ( itm.GetClassID() == siSampleID )
			{
				Sample smp = Sample(itm);
				app.LogMessage( L"Found a sample at index " + CString(smp.GetIndex()) );
			}
			if ( itm.GetClassID() == siEdgeID )
			{
				Edge edg = Edge(itm);
				app.LogMessage( L"Found a edge at index " + CString(edg.GetIndex()) );
			}
			if ( itm.GetClassID() == siControlPointID )
			{
				ControlPoint ctrl = ControlPoint(itm);
				app.LogMessage( L"Found a control point at index " + CString(ctrl.GetIndex()) );
			}
			// etc.
		}

	\endcode

	\param in_name The name of the property or method to invoke
	\param in_flags Specify the context (whether it's calling a method, setting or getting a property). See CComAPIHandler::InvokeFlag.
	\param io_return The return value.
	\param in_args Array of arguments for the method to call.
	\return CStatus::OK	Success
	\return CStatus::Fail Other failure
	\return CStatus::AccessDenied Trying to set a read-only parameter.
	\return CStatus::MemberNotFound	Method or property does not exist.
	*/
	CStatus Invoke(	const CString& in_name,
					LONG in_flags,
					CValue& io_return,
					const CValueArray& in_args = CValueArray() ) const;

	/*! Returns a reference to the automation object attached to the CComAPIHandler.
	\return A reference to an automation object.
	*/
	CValue GetRef(void) const;

private:
	void* m_ptr; // pointer to Softimage OM object
};
};
#endif // __CCOMAPIHANDLER__H_
