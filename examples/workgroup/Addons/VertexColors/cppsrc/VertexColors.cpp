// CustomUITest.cpp : Defines the entry point for the DLL application.
//
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

#include "stdafx.h"
#include "VertexColors.h"
#include "CustomUI.h"

#include <assert.h>

#include <xsi_pluginregistrar.h>
#include <xsi_decl.h>
#include <xsi_viewcontext.h>

#include <commctrl.h>
#include <commdlg.h>

HINSTANCE __gInstance = NULL;

//
// Operators
//

#include "Collapse.h"
#include "BakeLights.h"
#include "BakeRenderTree.h"
#include "Mix2Colors.h"
#include "ColorCorrection.h"

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


XSIPLUGINCALLBACK void	VertexColorsSDKExample_Init (XSI::CRef in_pViewCtx)
{
	assert ( in_pViewCtx.IsA ( XSI::siViewContextID ) );
	XSI::ViewContext l_vViewContext = in_pViewCtx;
	assert ( l_vViewContext.IsValid() );

	CCustomUI* l_pCustomUI = new CCustomUI();

	l_vViewContext.PutUserData ( (void*)l_pCustomUI );

	//
	// Add vertex color operators
	//

	l_pCustomUI->AddOperator ( new CCollapse() );
	l_pCustomUI->AddOperator ( new BakeLights() );
	l_pCustomUI->AddOperator ( new BakeRenderTree() );
	l_pCustomUI->AddOperator ( new CMix2Colors() );

	l_pCustomUI->Init ( in_pViewCtx );

	
}

XSIPLUGINCALLBACK void	VertexColorsSDKExample_Term (XSI::CRef in_pViewCtx)
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

XSIPLUGINCALLBACK void	VertexColorsSDKExample_Notify	( XSI::CRef in_pViewCtx )
{
	
	//
	// We are being notified by Softimage that something has 
	// changed. Pass this info to the custom view
	//

	XSI::ViewContext l_vViewContext = in_pViewCtx;
	assert ( l_vViewContext.IsValid() );
	
	CCustomUI* l_pCustomUI = (CCustomUI*)((void*)l_vViewContext.GetUserData ());
	
	assert ( l_pCustomUI != NULL );


	l_pCustomUI->Notify ( in_pViewCtx );
}

XSIPLUGINCALLBACK XSI::CStatus XSILoadPlugin( XSI::PluginRegistrar& in_reg )
{
	in_reg.PutAuthor( L"Softimage" );

	// A compiled version of this plug-in ships with Softimage
	// To avoid conflict this has been renamed but
	// otherwise is exactly the same
	in_reg.PutName( L"VertexColors SDKExample" );
	in_reg.PutVersion( 1, 0 );

	// As above, the display was renamed to avoid conflicts
	in_reg.RegisterCustomDisplay( L"VertexColorsSDKExample" );

	return XSI::CStatus::OK;	
}

XSIPLUGINCALLBACK XSI::CStatus XSIUnloadPlugin( const XSI::PluginRegistrar& in_reg )
{
	return XSI::CStatus::OK;
}