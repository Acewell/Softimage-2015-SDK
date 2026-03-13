// CustomUITest.cpp : Defines the entry point for the DLL application.
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   


#include "stdafx.h"
#include "CustomUITest.h"
#include "CustomUI.h"

#include <assert.h>

#include <xsi_pluginregistrar.h>
#include <xsi_decl.h>
#include <xsi_viewcontext.h>

#include <commctrl.h>
#include <commdlg.h>

HINSTANCE __gInstance = NULL;

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

	__gInstance = (HINSTANCE)hModule;

	InitCommonControls();

    return TRUE;
}

//********************************************************************
//
// @mfunc	NotificationTest_Init | Called by Softimage when the plugin
//									is first initialized
//
//********************************************************************
XSIPLUGINCALLBACK void	NotificationTest_Init (XSI::CRef in_pViewCtx)
{
	//
	// Make sure the CRef passed to us is in fact a ViewContext object
	//

	assert ( in_pViewCtx.IsA ( XSI::siViewContextID ) );
	XSI::ViewContext l_vViewContext = in_pViewCtx;
	assert ( l_vViewContext.IsValid() );

	CCustomUI* l_pCustomUI = new CCustomUI();

	l_vViewContext.PutUserData ( (void*)l_pCustomUI );
	l_vViewContext.SetFlags ( XSI::siWindowNotifications );

	//
	// Initialize our custom view
	//

	l_pCustomUI->Init ( in_pViewCtx );

	
}

//********************************************************************
//
// @mfunc	NotificationTest_Init | Called by Softimage when the plugin
//									is terminated (when the parent 
//									window is destroyed.
//
//********************************************************************
XSIPLUGINCALLBACK void	NotificationTest_Term (XSI::CRef in_pViewCtx)
{
	//
	// Terminate our custom view
	//

	XSI::ViewContext l_vViewContext = in_pViewCtx;
	assert ( l_vViewContext.IsValid() );

	CCustomUI* l_pCustomUI = (CCustomUI*)((void*)l_vViewContext.GetUserData ());

	assert ( l_pCustomUI != NULL );

	l_pCustomUI->Term ( in_pViewCtx );

	delete l_pCustomUI;
	l_pCustomUI = NULL;

}

//********************************************************************
//
// @mfunc	NotificationTest_Notify | Called by Softimage when something
//									occurs in the scene. Like a
//									parameter change or selection  
//									change.
//
//********************************************************************
XSIPLUGINCALLBACK void	NotificationTest_Notify	( XSI::CRef in_pViewCtx )
{

	//
	// We are being notified by XSI that something has 
	// changed. Pass this info to the custom view
	//

	XSI::ViewContext l_vViewContext = in_pViewCtx;
	assert ( l_vViewContext.IsValid() );
	
	CCustomUI* l_pCustomUI = (CCustomUI*)((void*)l_vViewContext.GetUserData ());
	
	assert ( l_pCustomUI != NULL );


	l_pCustomUI->Notify ( in_pViewCtx );
}

XSIPLUGINCALLBACK void			NotificationTest_SetAttributeValue		(XSI::CRef in_pViewCtx, XSI::CString in_sAttribName, XSI::CValue in_vValue)
{
	XSI::ViewContext l_vViewContext = in_pViewCtx;
	assert ( l_vViewContext.IsValid() );
	
	CCustomUI* l_pCustomUI = (CCustomUI*)((void*)l_vViewContext.GetUserData ());
	assert ( l_pCustomUI != NULL );

	l_pCustomUI->SetAttributeValue( in_sAttribName, in_vValue );

}

XSIPLUGINCALLBACK XSI::CValue	NotificationTest_GetAttributeValue		(XSI::CRef in_pViewCtx, XSI::CString in_sAttribName)
{

	XSI::ViewContext l_vViewContext = in_pViewCtx;
	assert ( l_vViewContext.IsValid() );
	
	CCustomUI* l_pCustomUI = (CCustomUI*)((void*)l_vViewContext.GetUserData ());
	assert ( l_pCustomUI != NULL );

	XSI::CValue l_val;
	l_pCustomUI->GetAttributeValue( in_sAttribName, l_val );

	return l_val;
}



//********************************************************************
//
// @mfunc	XSILoadPlugin | Called by Softimage to register the DLL and
//							the various plugin it hosts.
//							See the SDK documentation for more info.
//
//
//********************************************************************
XSIPLUGINCALLBACK XSI::CStatus XSILoadPlugin( XSI::PluginRegistrar& in_reg )
{
	in_reg.PutAuthor( L"Softimage" );
	in_reg.PutName( L"Custom UI Example - Notification Test" );
	in_reg.PutVersion( 1, 0 );

	in_reg.RegisterCustomDisplay( L"NotificationTest" );

	return XSI::CStatus::OK;	
}

//********************************************************************
//
// @mfunc	XSILoadPlugin | Called by Softimage when it needs to unload the
//							plugin.
//
//
//********************************************************************
XSIPLUGINCALLBACK XSI::CStatus XSIUnloadPlugin( const XSI::PluginRegistrar& in_reg )
{
	return XSI::CStatus::OK;
}