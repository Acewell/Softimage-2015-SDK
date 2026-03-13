// CustomUI.h: interface for the CCustomUI class.
//
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

#if !defined(AFX_CUSTOMUI_H__BFC2FE5E_A859_480A_A1BB_B8CC8ECCE1CA__INCLUDED_)
#define AFX_CUSTOMUI_H__BFC2FE5E_A859_480A_A1BB_B8CC8ECCE1CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <xsi_ref.h>
#include <xsi_decl.h>

class CCustomUI
{
public:
	CCustomUI();
	virtual ~CCustomUI();

	virtual char*	GetName() { return "CustomUI Example"; };
		
	virtual LRESULT	Init( XSI::CRef& in_pViewCtx );
	virtual LRESULT	Term( XSI::CRef& in_pViewCtx );
	virtual LRESULT Notify ( XSI::CRef& in_pViewCtx );

	virtual LRESULT SetAttributeValue ( XSI::CString& in_cString, XSI::CValue& in_vValue );
	virtual LRESULT GetAttributeValue ( XSI::CString& in_cString, XSI::CValue& out_vValue );

	//
	// window
	//

	virtual LRESULT SetWindowSize(int ox, int oy, int cx, int cy);
	
	virtual LRESULT Paint( WPARAM, LPARAM );
	virtual LRESULT MouseMove( WPARAM, LPARAM );


private:

	void	PrintNotification ( char*	in_szMessage );


private:
	HWND	l_hWnd;
};

typedef struct tagMsg2Name {
	char*	m_szName;
	int		m_iID;
} Msg2Name;



#endif // !defined(AFX_CUSTOMUI_H__BFC2FE5E_A859_480A_A1BB_B8CC8ECCE1CA__INCLUDED_)
