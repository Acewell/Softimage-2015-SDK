//*****************************************************************************
/*
	\file simplecommand.cpp 
	\brief Implementation of the SDK Simple Command example
	\author Marc-André Belzile

	Note: Look at simplecommand.htm for more details about this sample.

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
#include <xsi_application.h>
#include <xsi_context.h>
#include <xsi_decl.h>
#include <xsi_layout.h>
#include <xsi_view.h>
#include <xsi_desktop.h>
#include <xsi_plugin.h>
#include <xsi_pluginitem.h>
#include <xsi_command.h>
#include <xsi_argument.h>

using namespace XSI;

/*!
	Entry-point called by Softimage when this file gets loaded. All plugin items 
	exposed here must be registered in this function. 

	\param in_reg: PluginRegistrar object required for registering the plugin 
	items and some information about this plugin.

	*note* This function is mandatory and must be implemented. The plugin will 
	not be loaded if this function is missing.
*/
XSIPLUGINCALLBACK CStatus XSILoadPlugin( PluginRegistrar& in_reg )
{
	in_reg.PutAuthor( L"Softimage Corp" );
	in_reg.PutName( L"C++ Simple Command Plug-in" );
	in_reg.PutVersion( 1, 0 );

	// register a command plugin item.
	in_reg.RegisterCommand( L"SimpleCPPCommand" );

	return CStatus::OK;	
}

/*!
	Entry-point called by Softimage when this file gets unloaded. All plugin items 
	registered by this plugin are automatically unregistered by Softimage. Use this 
	function to perform internal cleanup.

	\param in_reg PluginRegistrar object.

	*note* This function is optional.
*/
XSIPLUGINCALLBACK CStatus XSIUnloadPlugin( const PluginRegistrar& in_reg )
{
	Application app;
	app.LogMessage( in_reg.GetName() + L" has been unloaded.");

	return CStatus::OK;
}

class MyCounter
{
	public:
	MyCounter() : m_count(0) {}

	CString print() 
	{
		CString strCount(L"SimpleCPPCommand execution count = ");
		strCount += CValue((LONG)m_count).GetAsText();
		return strCount;
	}

	LONG m_count;
};

/*!	CPPSimpleCommand_Init: This callback is used for defining the simple command, 
	you can use this callback to define the command arguments for instance. 
	This callback is called when the command is first requested by Softimage.

	\param in_context Command context. The context contains the command object
	to define.

	*note* This function is not mandatory.
*/

XSIPLUGINCALLBACK CStatus SimpleCPPCommand_Init( const CRef& in_context )
{
	Context ctx(in_context);
	Command cmd(ctx.GetSource());

	Application app;
	app.LogMessage( L"Defining: " + cmd.GetName() );

	ArgumentArray args = cmd.GetArguments();

	args.Add( L"arg0", L"Default value" );
	args.Add( L"arg1", L"Default value2" );

	// allocate memory for storing the user data
	CValue val = (CValue::siPtrType) new MyCounter();
	ctx.PutUserData( val );

	return CStatus::OK;
}

/*!	CPPSimpleCommand_Execute: This callback is used to implement the simple command.

	\param in_context Command context. The context contains the following
	attributes:
		Source: The Command object.
		Arguments: CValueArray containing the argument values.
		ReturnValue: The command return value

	*note* This function is mandatory and must be implemented.
*/
XSIPLUGINCALLBACK CStatus SimpleCPPCommand_Execute( CRef& in_context )
{
	Application app;
	Context ctxt(in_context);
	CValueArray args = ctxt.GetAttribute( L"Arguments" );

	for (LONG i=0; i<args.GetCount(); i++)
	{
		app.LogMessage( L"Arg" + CValue(i).GetAsText() + L": " + 
			args[i].GetAsText() );			
	}

	// set the return value
	CValue val = ctxt.GetUserData();
	MyCounter* p = (MyCounter*)(CValue::siPtrType)val;
	p->m_count++;

	ctxt.PutAttribute( L"ReturnValue", p->print() );

	return CStatus::OK;
}

XSIPLUGINCALLBACK CStatus SimpleCPPCommand_Unload( const CRef& in_context )
{
	Application app;
	Context ctxt(in_context);

	Command command = ctxt.GetSource();

	app.LogMessage( L"Unloading: " + command.GetName() );
	
	// Important: The function must clean up the memory allocated for the user 
	// data before Softimage unloads the plug-in. This is important because Softimage will 
	// get rid of any user data stored in the Context object after this 
	// function returns.
	CValue val = ctxt.GetUserData();
	MyCounter* p = (MyCounter*)(CValue::siPtrType)val;
	delete p;
	return CStatus::OK;
}

XSIPLUGINCALLBACK CStatus SimpleCPPCommand_Reload( const CRef& in_context )
{
	Application app;
	Context ctxt(in_context);

	Command command = ctxt.GetSource();

	app.LogMessage( L"Reloading: " + command.GetName() );

	// create the user data 
	CValue val = (CValue::siPtrType) new MyCounter();
	ctxt.PutUserData( val );

	MyCounter* p = (MyCounter*)(CValue::siPtrType)val;

	p->m_count++;
	app.LogMessage( p->print() );

	return CStatus::OK;
}

XSIPLUGINCALLBACK CStatus SimpleCPPCommand_Term( const CRef& in_context )
{
	Application app;
	Context ctxt(in_context);

	Command command = ctxt.GetSource();

	app.LogMessage( L"Terminating: " + command.GetName() );
							
	// release memory for user data
	CValue val = ctxt.GetUserData();
	MyCounter* p = (MyCounter*)(CValue::siPtrType)val;
	delete p;

	return CStatus::OK;
}

