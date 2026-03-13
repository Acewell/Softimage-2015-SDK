// interface for the CXSIGameControlPanelUI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_XSIGAMECONTROLPANELUI__INCLUDED_)
#define _XSIGAMECONTROLPANELUI__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <xsi_ref.h>
#include <xsi_decl.h>

class CXSIGameControlPanelUI
{
public:
	CXSIGameControlPanelUI();
	virtual ~CXSIGameControlPanelUI();

	virtual char*	GetName() { return "XSIGameControlPanel1"; }
		
	virtual LRESULT	Init( XSI::CRef& in_pViewCtx );
	virtual LRESULT	Term( XSI::CRef& in_pViewCtx );
	virtual LRESULT Notify ( XSI::CRef& in_pViewCtx );

private:
	HWND	m_hWnd;
	bool	m_bIgnoreNotifications;

};

#endif // !defined(_XSIGAMECONTROLPANELUI__INCLUDED_)
