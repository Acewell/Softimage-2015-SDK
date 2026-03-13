//*****************************************************************************
/*
	\file simplefilter.cpp 
	\brief Implementation of the SDK Simple Filter example
	\author Marc-André Belzile

	Note: Look at simplefilter.htm for more details about this sample.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   

*/
//*****************************************************************************


#include <xsi_ref.h>
#include <xsi_value.h>
#include <xsi_status.h>
#include <xsi_pluginregistrar.h>
#include <xsi_pluginitem.h>
#include <xsi_x3dobject.h>
#include <xsi_application.h>
#include <xsi_primitive.h>
#include <xsi_geometry.h>
#include <xsi_context.h>
#include <xsi_decl.h>
#include <xsi_layout.h>
#include <xsi_view.h>
#include <xsi_desktop.h>
#include <xsi_point.h>
#include <xsi_plugin.h>
#include <xsi_pluginitem.h>
#include <xsi_filter.h>

using namespace XSI;

/*!
	Entry-point called by Softimage when this file gets loaded. All plugin items 
	exposed here must be registered in this function. 

	\param in_reg: PluginRegistrar object required for registering the plugin 
	items and some information about this plugin.

	*note* This function is mandatory and must be implemented. The plugin will 
	not be loaded if this function is missing.
*/
XSIPLUGINCALLBACK CStatus XSILoadPlugin( XSI::PluginRegistrar& in_reg )
{
	in_reg.PutAuthor( L"Softimage Corp" );
	in_reg.PutName( L"C++ Simple Filter Plug-in" );
	in_reg.PutVersion( 1, 0 );

	// register a 3D object filter plugin item.
	// note: the custom filter will be loaded automatically in the filter menu 
	// located in the main command panel
	in_reg.RegisterFilter( L"SimpleFilter", siFilter3DObject );

	return XSI::CStatus::OK;	
}

/*!
	Entry-point called by Softimage when this file gets unloaded. All plugin items 
	registered by this plugin are automatically unregistered by Softimage. Use this 
	function to perform internal cleanup.

	\param in_reg PluginRegistrar object.

	*note* This function is optional.
*/
XSIPLUGINCALLBACK XSI::CStatus XSIUnloadPlugin( const XSI::PluginRegistrar& in_reg )
{
	Application app;
	app.LogMessage( in_reg.GetName() + L" has been unloaded.");

	return XSI::CStatus::OK;
}

// helper to get an X3DObject
static XSI::X3DObject Get3DObject( const XSI::CRef& in_object )
{
	XSI::X3DObject obj;
	if (in_object.IsA( siX3DObjectID ))
	{
		obj = in_object;
	}
	else if ( in_object.IsA( siPrimitiveID ) )
	{
		obj = SIObject(in_object).GetParent();
	}

	return obj;
}

/*!	SimpleFilter_Match: Returns true if the object is a polygon mesh with less 
	than 50 points.

	\param in_context Filter context. The context contains these specific 
	attributes:
		Input: Object to filter.

	*note* This function is mandatory and must be implemented.
*/
XSIPLUGINCALLBACK bool SimpleFilter_Match( const XSI::CRef& in_context )
{
	Context ctx(in_context);
	CRef in_object = ctx.GetAttribute( L"Input" );

	X3DObject obj = Get3DObject( in_object );
	if ( !obj.IsValid() )
	{
		return false;
	}

	return obj.GetActivePrimitive().GetGeometry().GetPoints().GetCount() > 50;
}

/*!	SimpleFilter_Applicable: Returns true if the filter is applicable with the
	input object.

	\param in_context Filter context. The context contains these specific 
	attributes:
		Input: Object to filter.

	*note* This function is not mandatory.
*/
XSIPLUGINCALLBACK bool SimpleFilter_Applicable( const XSI::CRef& in_context )
{
	Context ctx(in_context);
	CRef in_object = ctx.GetAttribute( L"Input" );

	return Get3DObject( in_object ).IsValid() == true;
}

/*!	SimpleFilter_Subset: Returns a subset of the input array. 

	\param in_objects Array of objects to filter.
	\param out_objects Array of objects from the original array that match 
	the filter criterias.

	\param in_context Filter context. The context contains these specific 
	attributes:
		Input: Objects to filter.
		Output: Filtered objects. This attribute must be set with a CRefArray
		containing the objects that match the filter criterias.

	*note* This function is not mandatory.
*/
XSIPLUGINCALLBACK bool SimpleFilter_Subset( const XSI::CRef& in_context )
{	
	Context ctx(in_context);
	CRefArray in_objects = ctx.GetArrayAttribute( L"Input" );

	CRefArray out_objects;
	for (LONG i=0; i<in_objects.GetCount(); i++)
	{
		if ( SimpleFilter_Match(in_objects[i]) )
		{
			out_objects.Add(in_objects[i]);
		}
	}
	ctx.PutArrayAttribute( L"Output", out_objects );

	return out_objects.GetCount() > 0;
}

class MyCounter
{
	public:
	MyCounter() : m_count(0) {}

	CString print() 
	{
		CString strCount(L"My count = ");
		strCount += CValue((LONG)m_count).GetAsText();
		return strCount;
	}

	LONG m_count;
};

XSIPLUGINCALLBACK XSI::CStatus SimpleFilter_Init( const XSI::CRef& in_context )
{
	Application app;
	Context ctxt(in_context);

	Filter filter = ctxt.GetSource();

	app.LogMessage( L"Initializing C++ Simple filter: " + filter.GetName() );

	// allocate memory for user data
	CValue val = (CValue::siPtrType) new MyCounter();
	ctxt.PutUserData( val );

	return CStatus::OK;
}

XSIPLUGINCALLBACK XSI::CStatus SimpleFilter_Unload( const XSI::CRef& in_context )
{
	Application app;
	Context ctxt(in_context);

	Filter filter = ctxt.GetSource();

	app.LogMessage( L"Unloading C++ Simple filter: " + filter.GetName() );
	
	// Important: The function must clean up the memory allocated for the user 
	// data before Softimage unloads the plug-in. This is important because Softimage will 
	// get rid of any user data stored in the Context object after this 
	// function returns.
	CValue val = ctxt.GetUserData();
	MyCounter* p = (MyCounter*)(CValue::siPtrType)val;
	delete p;

	return CStatus::OK;
}

XSIPLUGINCALLBACK XSI::CStatus SimpleFilter_Reload( const XSI::CRef& in_context )
{
	Application app;
	Context ctxt(in_context);

	Filter filter = ctxt.GetSource();

	app.LogMessage( L"Reloading C++ Simple filter: " + filter.GetName() );

	// create the user data 
	CValue val = (CValue::siPtrType) new MyCounter();
	ctxt.PutUserData( val );

	MyCounter* p = (MyCounter*)(CValue::siPtrType)val;

	p->m_count++;
	app.LogMessage( p->print() );

	return CStatus::OK;
}

XSIPLUGINCALLBACK XSI::CStatus SimpleFilter_Term( const XSI::CRef& in_context )
{
	Application app;
	Context ctxt(in_context);

	Filter filter = ctxt.GetSource();

	app.LogMessage( L"Terminating C++ Simple filter: " + filter.GetName() );

	// release memory for user data
	CValue val = ctxt.GetUserData();			 
	MyCounter* p = (MyCounter*)(CValue::siPtrType)val;
	delete p;

	return CStatus::OK;
}

