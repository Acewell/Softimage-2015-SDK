//*****************************************************************************
//
// Author		:  Alain Dessureaux
// Date			:  June 2002
// Updated By	:  
//
// (c) Copyright 2002 Softimage Corporation
//
// This file implements the MouseDevice example plug-in for Softimage in C++ using ATL.
//	(ComCompiler support) 
//
//*****************************************************************************

//////////////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"

#include <assert.h>            
#include <atlbase.h>            // ATL.
#include <windows.h>
#include <xsisdk.h>  // Softimage object model interfaces.
#include <xsisdk.c>  // Softimage object model GUID's.
#ifdef unix
#include <atlimpl.cpp>
ATL_DECLARE_UUIDOF( Application );
#endif

#include <sicppsdk.h>

#ifndef WH_MOUSE_LL
#define WH_MOUSE_LL 14	// For Visual Studio .Net compilation
#endif

//////////////////////////////////////////////////////////////////////////////
// Defines
//////////////////////////////////////////////////////////////////////////////
#define AssertAndReturn( hr ) \
	if (FAILED(hr)) {assert(SUCCEEDED(hr)); return hr; }


static HINSTANCE g_hInstance = NULL;
static HHOOK g_currentHook = NULL;

//////////////////////////////////////////////////////////////////////////////
// CMyDevice class 
//////////////////////////////////////////////////////////////////////////////
UINT	m_idTimer;
class _DeviceInfo
{
public:
	_DeviceInfo::_DeviceInfo()
	{
		m_pChannelX=0;
		m_pChannelY=0;
	}
	_DeviceInfo::~_DeviceInfo()
	{
		m_pChannelX=0;
		m_pChannelY=0;
	}

	CComPtr<Channel>	m_pChannelX;
	CComPtr<Channel>	m_pChannelY;
	CComPtr<Channel>	m_pChannelLB;
	CComPtr<Channel>	m_pChannelMB;
	CComPtr<Channel>	m_pChannelRB;


	int			m_iScreenresX;
	int			m_iScreenresY;

};

// Create a global instance of the device info.
// This will cache the Channel object, so we don't have to get them
// on each mouse message!
static _DeviceInfo g_pDeviceinfo;


//*****************************************************************************
// Author		:  Alain Dessureaux
// Date			:  June 2002
// Updated By	:  
//
// @mfunc		DllMain | Dll initialization 
//
//*****************************************************************************
BOOL APIENTRY DllMain( HINSTANCE hInstance, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	if ( ul_reason_for_call == DLL_PROCESS_ATTACH )
	{
	    g_hInstance = hInstance;
        return( TRUE ) ;
    }
	else
		return ( TRUE ) ;		// OK
}


#ifdef _TIMER_BASED_EXAMPLE	
// This is another way to use a device driver, using a timer.

//*****************************************************************************
// Author		:  Alain Dessureaux
// Date			:  December 2001
// Updated By	:  
//
// @mfunc		fnTimerProc | Timer callback. This get the mouse position and 
//							update the custom pset.
//
//*****************************************************************************
VOID CALLBACK fnTimerProc( HWND /*hwnd*/, UINT /*uMsg*/, UINT /*idEvent*/, DWORD /*dwTime*/ )
{
	ApplicationPtr		l_pApp;
	l_pApp.CreateInstance("XSI.Application");

	//-----------------------------------------------------
	// Get the mouse position 
	//-----------------------------------------------------
	POINT		l_ptClientMousePos;
	::GetCursorPos( &l_ptClientMousePos );

	// Set the X channel
	CComVariant l_varX( (DOUBLE)l_ptClientMousePos.x );
	CComVariant l_varY( (DOUBLE)l_ptClientMousePos.y );

	g_pDeviceinfo.m_pChannelX->put_Value( l_varX );
	g_pDeviceinfo.m_pChannelY->put_Value( l_varY );
}
#endif 

//*****************************************************************************
// Author		:  Alain Dessureaux
// Date			:  June 2002
// Updated By	:  
//
// @mfunc		MyMouseProc | Mouse window hook callback. 
//  This function will trigger the channels in Softimage. 
//
//*****************************************************************************
LRESULT CALLBACK MyMouseProc
(
  int nCode,      // hook code
  WPARAM wParam,  // message identifier
  LPARAM lParam   // mouse coordinates
)
{
#ifdef unix
	CWPSTRUCT *l_sMsg = (CWPSTRUCT*) lParam;
	WPARAM oldParam = wParam;
	wParam = l_sMsg->message;

	if (wParam != WM_MOUSEMOVE && 
		wParam != WM_LBUTTONDOWN && 
		wParam != WM_MBUTTONDOWN &&
		wParam != WM_RBUTTONDOWN )
			return CallNextHookEx(g_currentHook,nCode,wParam,lParam);
	
	// We receive always two messages identical with WH_CALLWNDPROC
	// frobicha x3471
	static BOOL s_bCheck = TRUE;
	
	s_bCheck = !s_bCheck;
		
	if( s_bCheck ) 
	 	return CallNextHookEx(g_currentHook,nCode,wParam,lParam);
		
#endif 

	if (wParam == WM_MOUSEMOVE)
	{
		MOUSEHOOKSTRUCT *l_sMouseInfo = (MOUSEHOOKSTRUCT *)lParam;

		if (g_pDeviceinfo.m_pChannelX)
		{
#ifdef unix
		    POINT       l_ptClientMousePos;
		    ::GetCursorPos( &l_ptClientMousePos );

			DOUBLE l_dX = (DOUBLE)l_ptClientMousePos.x;
			DOUBLE l_dY = (DOUBLE)l_ptClientMousePos.y;
#else
			DOUBLE l_dX = (DOUBLE)l_sMouseInfo->pt.x;
			DOUBLE l_dY = (DOUBLE)l_sMouseInfo->pt.y;
#endif

			// Normalize the values to be from 0 and 1
			l_dX = l_dX / g_pDeviceinfo.m_iScreenresX;
			l_dY = l_dY / g_pDeviceinfo.m_iScreenresY;

			// Set the X an Y channels
			CComVariant l_varX( l_dX );
			CComVariant l_varY( l_dY );

			g_pDeviceinfo.m_pChannelX->put_Value( l_varX );
			g_pDeviceinfo.m_pChannelY->put_Value( l_varY );
		}
	}
	else if (wParam == WM_LBUTTONDOWN)
	{
		if (g_pDeviceinfo.m_pChannelLB)
		{
			// Trigger the command on the Left Button
			g_pDeviceinfo.m_pChannelLB->put_Value( CComVariant(1) );
		}
	}
	else if (wParam == WM_MBUTTONDOWN)
	{
		if (g_pDeviceinfo.m_pChannelMB)
		{
			// Trigger the command on the Middle Button
			g_pDeviceinfo.m_pChannelMB->put_Value( CComVariant(1) );
		}
	}
	else if (wParam == WM_RBUTTONDOWN)
	{
		if (g_pDeviceinfo.m_pChannelRB)
		{
			// Trigger the command on the Right Button
			g_pDeviceinfo.m_pChannelRB->put_Value( CComVariant(1) );
		}
	}

	return CallNextHookEx(g_currentHook,nCode,wParam,lParam);
}

//////////////////////////////////////////////////////////////////////////////
// Entry Points
//////////////////////////////////////////////////////////////////////////////
//*****************************************************************************
// Author		:  Alain Dessureaux
// Date			:  June 2002
// Updated By	:  
//
// @mfunc		XSIDeviceOnInitialize | Device Driver callback.
// This callback is called when the device driver is added in the 
// Device Manager
//
//*****************************************************************************
_SICALLBACK( HRESULT ) XSIDeviceOnInitialize()
{
	// Nothing special to do here for now.
	return S_OK;
}

//*****************************************************************************
// Author		:  Alain Dessureaux
// Date			:  June 2002
// Updated By	:  
//
// @mfunc		XSIDeviceOnUnInitialize | Device Driver callback.
// This callback is called when the device driver is removed from the 
// Device Manager
//
//*****************************************************************************
_SICALLBACK( HRESULT ) XSIDeviceOnUnInitialize()
{
	// Nothing special to do here for now.
	return S_OK;
}

//*****************************************************************************
// Author		:  Alain Dessureaux
// Date			:  June 2002
// Updated By	:  
//
// @mfunc		XSIDeviceOnActivate | Device Driver callback.
// This callback is called when the device driver get activated.
//
//*****************************************************************************
_SICALLBACK( HRESULT ) XSIDeviceOnActivate()
{
	CComPtr<Application> l_pApp;
	HRESULT l_hr;

	l_hr = l_pApp.CoCreateInstance(L"XSI.Application");
	AssertAndReturn(l_hr);

#ifdef DEBUG
	l_pApp->LogMessage(L"MouseExample: Connecting Mouse Device...", siInfo);
#endif 

	//-----------------------------------------------------
	// Get the mouse position 
	//-----------------------------------------------------
	POINT		l_ptClientMousePos;
	::GetCursorPos( &l_ptClientMousePos );

	//-----------------------------------------------------
	//-----------------------------------------------------
	if (g_pDeviceinfo.m_pChannelX == 0 || g_pDeviceinfo.m_pChannelY ==0)
	{
		HRESULT					l_hr;
		CComPtr<XSIApplication>		l_xsiApp;
		CComPtr<DeviceCollection>	l_pDeviceManager;
		CComPtr<ChannelCollection>	l_pChannels;
		CComPtr<Device>				l_pDevice;

		l_hr = l_pApp->QueryInterface( IID_XSIApplication, (LPVOID*)&l_xsiApp);

		// Get the objects
		l_hr = l_xsiApp->get_Devices(&l_pDeviceManager);
		AssertAndReturn(l_hr);

		// Get the device by the device name (from the .xsidevice file)
		l_hr = l_pDeviceManager->get_Item( CComVariant(L"MouseExample"), &l_pDevice );
		AssertAndReturn(l_hr);

		// Get the channel collection from the device
		l_hr = l_pDevice->get_Channels( &l_pChannels );
		AssertAndReturn(l_hr);

/*	A  faster way to get channel by the Channel ID.
		l_hr = l_pDevice->get_Channel( 1, &g_pDeviceinfo.m_pChannelX);
		AssertAndReturn(l_hr);
		l_hr = l_pDevice->get_Channel( 2, &g_pDeviceinfo.m_pChannelY);
		AssertAndReturn(l_hr);
*/

		// Cache each channels.
		l_hr = l_pChannels->get_Item( CComVariant(0), &g_pDeviceinfo.m_pChannelX);
		AssertAndReturn(l_hr);

		l_hr = l_pChannels->get_Item( CComVariant(1), &g_pDeviceinfo.m_pChannelY);
		AssertAndReturn(l_hr);

		l_hr = l_pChannels->get_Item( CComVariant(2), &g_pDeviceinfo.m_pChannelLB);
		AssertAndReturn(l_hr);
		l_hr = l_pChannels->get_Item( CComVariant(3), &g_pDeviceinfo.m_pChannelMB);
		AssertAndReturn(l_hr);
		l_hr = l_pChannels->get_Item( CComVariant(4), &g_pDeviceinfo.m_pChannelRB);
		AssertAndReturn(l_hr);
	}

	//-----------------------------------------------------
	// Get the screen resolution. 
	//-----------------------------------------------------
	g_pDeviceinfo.m_iScreenresX = GetSystemMetrics( SM_CXSCREEN );
	g_pDeviceinfo.m_iScreenresY = GetSystemMetrics( SM_CYSCREEN );

	//-----------------------------------------------------
	// Start a timer  using the parameter named :
	// PollingInterval (20 msec by default)
	//-----------------------------------------------------
#ifdef _TIMER_BASED_EXAMPLE	
	ULONG l_ulPollingInterval = 20;
	m_idTimer = ::SetTimer( NULL, 1, l_ulPollingInterval, (TIMERPROC)fnTimerProc ) ;
#endif 

#ifdef unix
	// WH_MOUSE_LL is not supported with Visual Mainwin 4.02 SP3
	// Use WH_CALLWNDPROC. frobicha x3471
	g_currentHook = SetWindowsHookEx(WH_CALLWNDPROC, (HOOKPROC)MyMouseProc, g_hInstance,0);
#else
	g_currentHook = SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC)MyMouseProc, g_hInstance,0);
#endif

	return S_OK;
}

//*****************************************************************************
// Author		:  Alain Dessureaux
// Date			:  June 2002
// Updated By	:  
//
// @mfunc		XSIDeviceOnDeactivate | Device Driver callback.
// This callback is called when the device driver gets deactivated.
//
//*****************************************************************************
_SICALLBACK( HRESULT ) XSIDeviceOnDeactivate()
{
#ifdef DEBUG
	CComPtr<Application> l_pApp;
	HRESULT l_hr;
	
	l_hr = l_pApp.CoCreateInstance(L"XSI.Application");
	AssertAndReturn(l_hr);

	l_pApp->LogMessage(L"MouseExample: Disconnecting Mouse Device...", siInfo);
#endif 

#ifdef _TIMER_BASED_EXAMPLE	
	//-----------------------------------------------------
	// Stop the timer
	//-----------------------------------------------------
	::KillTimer( NULL, m_idTimer ) ;
#endif 
	
	//-----------------------------------------------------
	// Stop the windows Hook.
	//-----------------------------------------------------
	UnhookWindowsHookEx(g_currentHook);

	//-----------------------------------------------------
	// Release the pointers.
	//-----------------------------------------------------
	g_pDeviceinfo.m_pChannelX = 0;
	g_pDeviceinfo.m_pChannelY = 0;
	g_pDeviceinfo.m_pChannelLB = 0;
	g_pDeviceinfo.m_pChannelMB = 0;
	g_pDeviceinfo.m_pChannelRB = 0;

	return S_OK;
}
