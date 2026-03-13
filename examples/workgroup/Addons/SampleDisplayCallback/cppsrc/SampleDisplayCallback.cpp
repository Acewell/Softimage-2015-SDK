//***************************************************************************************
//
// File supervisor: Dominic Laflamme
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   
//***************************************************************************************

#include "StdAfx.h"
#include "SampleDisplayCallback.h"

#ifndef unix
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}
#endif

//
// Softimage SDK Entry Points
//

XSI::CStatus XSILoadPlugin( XSI::PluginRegistrar& in_reg )
{
	in_reg.PutAuthor( L"Softimage" );
	in_reg.PutName( L"Example Display Callbacks" );
	in_reg.PutVersion( 1, 0 );

	//
	// Here we tell the Plugin Registrar that this DLL exports 
	// a display callback Called MyClearScreenBuffer
	//
	in_reg.RegisterDisplayCallback( L"MyClearScreenBuffer" );
	
	//
	// Tell the Plugin Registrar to look for a custom Display pass
	// exported by this DLL
	//

	in_reg.RegisterDisplayPass( L"MyCustomPass" );

	return XSI::CStatus::OK;	
}

XSI::CStatus XSIUnloadPlugin( const XSI::PluginRegistrar& in_reg )
{

	return XSI::CStatus::OK;
}
