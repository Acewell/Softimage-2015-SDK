// XSIGameInterface.cpp : Defines the entry points for the DLL.
//
// This file contains the callbacks for two Custom Displays: 
// XSIGame and XSIGameControlPanel
#include "stdafx.h"
#include "XSIGameInterfaceUI.h"
#include "resource.h"
#include <assert.h>

#include <xsi_pluginregistrar.h>
#include <xsi_decl.h>
#include <xsi_viewcontext.h>
#include <xsi_application.h>

#include <commctrl.h>
#include <commdlg.h>

HINSTANCE __gInstance = NULL;
char __gGameApplicationPath[MAX_PATH];
char __gGameDataRootPath[MAX_PATH];
void RemoveBorder ( HWND in_hWnd );
extern LRESULT CALLBACK ControlPanelProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

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

    return TRUE;
}

//********************************************************************
//
// @mfunc	SetGameApplicationPath | Determine and save in memory
//			the path of the Game application.
//			Note: This should not be needed...
//
//********************************************************************
bool SetGameApplicationPath(char *io_path)
{
	char l_szPath[MAX_PATH];
	char drive[MAX_PATH];
	char directory[MAX_PATH];

	GetModuleFileName ( __gInstance, l_szPath, MAX_PATH );
	_splitpath ( l_szPath, drive, directory, NULL, NULL );

	// Remove the Application path if present
	char *l_cResult = strstr(directory, "Application\\");
	if (l_cResult!=0)
	{
		*l_cResult = '\0';
	}
	
	sprintf ( io_path, "%s%s", drive, directory );

	return true;
}

//********************************************************************
//
// @mfunc	SetGameApplicationPath | Determine and save in memory
//			the path of the Game Data
//
//********************************************************************
bool SetGameDataPath(char *io_path )
{
	XSI::Application	app;
	XSI::CValue			ret1;
	XSI::CString		l_csPath;

	if ( app.ExecuteCommand(L"XSIGame_GetDataLocation",0,ret1) != XSI::CStatus::OK)
	{
		SetGameApplicationPath( io_path );
		return false;
	}

	l_csPath = (XSI::CString)ret1;
	const char   *l_sPath = l_csPath.GetAsciiString();
	strncpy( io_path, l_sPath, MAX_PATH );

	// Remove the last slash
	if ( io_path[ strlen(io_path) - 1 ] == '\\' )
	{
		io_path[ strlen(io_path) - 1 ]  = 0;
	}

	return true;
}

//********************************************************************
//
// @mfunc	XSIGameInterface_Init | Called by Softimage when the plugin
//									is first initialized
//
//********************************************************************
XSIPLUGINCALLBACK void XSIGame_Init (XSI::CRef in_pViewCtx)
{
	//
	// Set the game paths
	//
	SetGameDataPath(__gGameDataRootPath);
	SetGameApplicationPath(__gGameApplicationPath);

	if ( !strlen(__gGameDataRootPath))
	{
		strcpy ( __gGameDataRootPath, __gGameApplicationPath);
	}

	//
	// Make sure the CRef passed to us is in fact a ViewContext object
	//

	assert ( in_pViewCtx.IsA ( XSI::siViewContextID ) );
	XSI::ViewContext l_vViewContext = in_pViewCtx;
	assert ( l_vViewContext.IsValid() );

	//
	// Create the CXSIGameInterfaceUI object which contains the implementation
	// of the hosted window.
	// 
	CXSIGameInterfaceUI* l_pCustomUI = new CXSIGameInterfaceUI();

	// Remember it as user data so that it can be cleaned up in the XSIGame_Term
	l_vViewContext.PutUserData ( (void*)l_pCustomUI );

	l_pCustomUI->Init ( in_pViewCtx );
}

//********************************************************************
//
// @mfunc	XSIGame_Term | Called by Softimage when the plugin
//									is terminated (when the parent 
//									window is destroyed.
//
//********************************************************************
XSIPLUGINCALLBACK void XSIGame_Term (XSI::CRef in_pViewCtx)
{
	//
	// Terminate our custom view
	//

	XSI::ViewContext l_vViewContext = in_pViewCtx;
	assert ( l_vViewContext.IsValid() );

	CXSIGameInterfaceUI* l_pCustomUI = (CXSIGameInterfaceUI*)((void*)l_vViewContext.GetUserData ());

	assert ( l_pCustomUI != NULL );

	l_pCustomUI->Term ( in_pViewCtx );

	delete l_pCustomUI;
	l_pCustomUI = NULL;

}

//********************************************************************
//
// @mfunc	XSIGame_Notify | Called by Softimage when something
//									occurs in the scene. Like a
//									parameter change or selection  
//									change.
//
//********************************************************************
XSIPLUGINCALLBACK void XSIGame_Notify	( XSI::CRef in_pViewCtx )
{

	//
	// We are being notified by Softimage that something has 
	// changed. Pass this info to the custom view
	//

	XSI::ViewContext l_vViewContext = in_pViewCtx;
	assert ( l_vViewContext.IsValid() );
	
	CXSIGameInterfaceUI* l_pCustomUI = (CXSIGameInterfaceUI*)((void*)l_vViewContext.GetUserData ());
	
	assert ( l_pCustomUI != NULL );


	l_pCustomUI->Notify ( in_pViewCtx );
}

//********************************************************************
//
// @mfunc	XSIGameControlPanel_Init
//
//********************************************************************
XSIPLUGINCALLBACK void XSIGameControlPanel_Init (XSI::CRef in_pViewCtx)
{
	
	//
	// Make sure the CRef passed to us is in fact a ViewContext object
	//

	assert ( in_pViewCtx.IsA ( XSI::siViewContextID ) );
	XSI::ViewContext l_vViewContext = in_pViewCtx;
	assert ( l_vViewContext.IsValid() );

	// This structure will hold the window handles
	ControlPanelStruct *l_pWindows = new ControlPanelStruct;

	// Create the dialogs that make up the panel
	l_pWindows->m_hControlPanel = CreateDialog(__gInstance, MAKEINTRESOURCE(IDD_CONTROL_PANEL), (HWND)l_vViewContext.GetParentWindowHandle(), (DLGPROC)ControlPanelProc);
	
	// Remember the structure as user data on the dialog
	SetWindowLong ( l_pWindows->m_hControlPanel, GWL_USERDATA, (LONG)l_pWindows);

	// These dialogs are the separate tabs
	l_pWindows->m_hLevel = CreateDialog(__gInstance, MAKEINTRESOURCE(IDD_LEVELEDITING), GetDlgItem (l_pWindows->m_hControlPanel, IDC_TABCONTROL), (DLGPROC)ControlPanelProc);
	l_pWindows->m_hActor = CreateDialog(__gInstance, MAKEINTRESOURCE(IDD_ACTOREDITING), GetDlgItem (l_pWindows->m_hControlPanel, IDC_TABCONTROL), (DLGPROC)ControlPanelProc);

	SetWindowPos ( l_pWindows->m_hLevel,	HWND_TOP, 5,25,0,0,SWP_NOSIZE | SWP_NOZORDER);
	SetWindowPos ( l_pWindows->m_hActor,	HWND_TOP, 5,25,0,0,SWP_NOSIZE | SWP_NOZORDER);
	
	RemoveBorder ( l_pWindows->m_hLevel );
	RemoveBorder ( l_pWindows->m_hActor );

	ShowWindow ( l_pWindows->m_hLevel, SW_HIDE );
	ShowWindow ( l_pWindows->m_hActor, SW_HIDE );
	ShowWindow ( l_pWindows->m_hLevel, SW_SHOWNORMAL );

	// Store the structure as user data so that the window handles are available 
	// for cleanup in XSIGameControlPanel_Term
	l_vViewContext.PutUserData ( (void*)l_pWindows );
}

//********************************************************************
//
// @mfunc	XSIGameControlPanel_Init | Called by Softimage when the plugin
//									is terminated (when the parent 
//									window is destroyed.
//
//********************************************************************
XSIPLUGINCALLBACK void	XSIGameControlPanel_Term (XSI::CRef in_pViewCtx)
{
	//
	// Terminate our custom view
	//

	XSI::ViewContext l_vViewContext = in_pViewCtx;
	assert ( l_vViewContext.IsValid() );

	ControlPanelStruct *l_pWindows = (ControlPanelStruct *)((void*)l_vViewContext.GetUserData ());

	assert ( l_pWindows != NULL );
	DestroyWindow ( l_pWindows->m_hControlPanel );
	DestroyWindow ( l_pWindows->m_hLevel );
	DestroyWindow ( l_pWindows->m_hActor );
	delete l_pWindows;
	l_pWindows = NULL;

}

//********************************************************************
//
// @mfunc	XSIGameControlPanel_Notify 
//
//********************************************************************
XSIPLUGINCALLBACK void	XSIGameControlPanel_Notify	( XSI::CRef in_pViewCtx )
{

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
	in_reg.PutName( L"Softimage Game Interface" );
	in_reg.PutVersion( 1, 0 );

	in_reg.RegisterCustomDisplay( L"XSIGame" );
	in_reg.RegisterCustomDisplay( L"XSIGameControlPanel" );

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


//********************************************************************
//
// @mfunc	RemoveBorder | Edit's a window's style by removing it's
//							border
//							
//********************************************************************
void RemoveBorder ( HWND in_hWnd )
{
	LONG l_Style;
	l_Style = GetWindowLong ( in_hWnd, GWL_STYLE );
	l_Style &= ~WS_BORDER; 
	SetWindowLong ( in_hWnd, GWL_STYLE, l_Style);
}