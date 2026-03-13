// CustomUI.h: interface for the CCustomUI class.
//
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUSTOMUI_H__BFC2FE5E_A859_480A_A1BB_B8CC8ECCE1CA__INCLUDED_)
#define AFX_CUSTOMUI_H__BFC2FE5E_A859_480A_A1BB_B8CC8ECCE1CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <xsi_ref.h>
#include <xsi_viewnotification.h>
#include <xsi_decl.h>
#include <SIBCArray.h>
#include "VertexColorOperator.h"

typedef struct tagDeferredTask {
	XSI::PolygonMesh	mesh;
} DeferredTask;

class CCustomUI
{
public:
	CCustomUI();
	virtual ~CCustomUI();

	virtual char*	GetName() { return "CustomUI Example"; };
		
	virtual LRESULT	Init( XSI::CRef& in_pViewCtx );
	virtual LRESULT	Term( XSI::CRef& in_pViewCtx );
	virtual LRESULT Notify ( XSI::CRef& in_pViewCtx );

	//
	// window
	//

	virtual LRESULT SetWindowSize(int ox, int oy, int cx, int cy);
	
	virtual LRESULT Paint( WPARAM, LPARAM );
	virtual LRESULT MouseMove( WPARAM, LPARAM );

	void	OnSelectionChange	( void* in_pData );
	void	OnValueChange		( void* in_pData );

	CVertexColorOperator*	GetCurrentOperator();
	XSI::CRefArray			GetSelectedProperties();

	void	ExecuteOperator();
	void	SetAsCurrent();
	void	AddLayer();
	void	RemoveLayer();
	void	BrushProperties();
	void	Paint();


	XSI::CRef	m_pCRef;

	void	AddOperator ( CVertexColorOperator* in_pOperator );

	void	Disable     ( BOOL );

	void	UpdateTasks ();

private:

	void	PrintNotification ( char*	in_szMessage );

	void	UpdateVPropCombo ( XSI::CRefArray in_array, BOOL in_bReset = TRUE);
	void	UpdateTaskList ( );
	
private:


	CSIBCArray<CVertexColorOperator*>	m_pOperators;

	HWND	l_hWnd;

	XSI::CRefArray		m_Props;
	
	BOOL	m_bIgnoreNotifications;
	BOOL	m_bDisabled;
	BOOL	m_bPainting;

	CSIBCArray<DeferredTask*>	m_Deferred;
};

typedef struct tagMsg2Name {
	char*	m_szName;
	int		m_iID;
} Msg2Name;




#endif // !defined(AFX_CUSTOMUI_H__BFC2FE5E_A859_480A_A1BB_B8CC8ECCE1CA__INCLUDED_)
