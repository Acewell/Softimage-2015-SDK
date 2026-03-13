// CustomUI.cpp: implementation of the CXSIGameControlPanelUI class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <stdio.h>
#include <assert.h>
#include <tchar.h>
#include <commctrl.h>
#include "XSIGameControlPanelUI.h"

#include "resource.h"

#include <xsi_ref.h>
#include <xsi_viewcontext.h>
#include <xsi_viewnotification.h>

extern HINSTANCE __gInstance;

//
// Helper function to convert a wide char string into ASCII
//

//
// Standard Win32 dialog callback
//
LRESULT CALLBACK	_CXSIGameControlPanelUI_DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXSIGameControlPanelUI::CXSIGameControlPanelUI()
	: m_hWnd(0)
	, m_bIgnoreNotifications(true)
{
}

CXSIGameControlPanelUI::~CXSIGameControlPanelUI()
{
	DestroyWindow ( m_hWnd );
	m_hWnd = NULL;
}


//********************************************************************
// @mfunc	CXSIGameControlPanelUI::Init | Creates the dialog has a child of the
//								window handle specified by the view
//								context.
//********************************************************************
LRESULT	CXSIGameControlPanelUI::Init( XSI::CRef& in_pViewCtx )
{
	XSI::ViewContext l_vViewContext = in_pViewCtx;
	assert ( l_vViewContext.IsValid() );

	//
	// Create a window so that we can control some Window messages like
	// mouse movement and resizing
	//

	m_hWnd = CreateDialog(  __gInstance ,  MAKEINTRESOURCE(IDD_XSIGAMECONTROLPANEL), (HWND)l_vViewContext.GetParentWindowHandle(), (DLGPROC)_CXSIGameControlPanelUI_DialogProc);

	SetWindowLongPtr ( m_hWnd, GWLP_USERDATA, (LONG_PTR)this);

	return S_OK;
}

//********************************************************************
// @mfunc	CXSIGameControlPanelUI::Term | 
//********************************************************************
LRESULT	CXSIGameControlPanelUI::Term( XSI::CRef& in_pViewCtx )
{

	DestroyWindow ( m_hWnd );
	m_hWnd = NULL;

	return S_OK;
}

//********************************************************************
// @mfunc	CXSIGameControlPanelUI::Notify | 
//********************************************************************
LRESULT CXSIGameControlPanelUI::Notify ( XSI::CRef& in_pViewCtx )
{
	using namespace XSI;

	XSI::ViewContext l_vViewContext = in_pViewCtx;
	assert ( l_vViewContext.IsValid() );

	if ( m_bIgnoreNotifications )
		return S_OK;

	XSI::siEventID in_eNotifcation;
	void*	in_pData;

	l_vViewContext.GetNotificationData ( in_eNotifcation, &in_pData );

	return S_OK;
}

//********************************************************************
// @mfunc	_CXSIGameControlPanelUI_DialogProc | 
//********************************************************************
LRESULT CALLBACK	_CXSIGameControlPanelUI_DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	CXSIGameControlPanelUI*	l_pWindow = (CXSIGameControlPanelUI*)GetWindowLongPtr ( hDlg, GWLP_USERDATA );
	
	switch (message)
	{
		case WM_INITDIALOG:
			{
				return TRUE;
			}
			break;

		case WM_SHOWWINDOW:
			{
				ShowWindow ( hDlg, wParam );
				break;
			}
		case WM_CHAR:
			{
				break;
			}
		case WM_KEYDOWN:
			{
				break;
			}
		case WM_CLOSE:

			EndDialog(hDlg, 0);
			break;

		case WM_COMMAND:
			{
				if ( l_pWindow )
				{
					switch (HIWORD(wParam))
					{
						default:
							break;
					}
				}
				break;
			}
		default:
			break;
	}

    return FALSE;
}