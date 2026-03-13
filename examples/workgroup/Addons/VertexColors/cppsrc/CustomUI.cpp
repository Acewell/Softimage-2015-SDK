// CustomUI.cpp: implementation of the CCustomUI class.
//
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <stdio.h>
#include <assert.h>
#include <commctrl.h>
#include "CustomUI.h"

#include "resource.h"

#include <xsi_application.h>
#include <xsi_model.h>
#include <xsi_camera.h>
#include <xsi_ref.h>
#include <xsi_viewnotification.h>
#include <xsi_x3dobject.h>
#include <xsi_siobject.h>
#include <xsi_viewcontext.h>
#include <xsi_polygonmesh.h>
#include <xsi_primitive.h>


extern HINSTANCE __gInstance;


void DSW2AHelper( LPSTR out_sz, LPCWSTR in_wcs, int in_cch = -1);

LRESULT CALLBACK	_view_proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

UINT guiTimer = 0;


CCustomUI*	g_this = NULL;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomUI::CCustomUI() :
m_bIgnoreNotifications (FALSE )
{
	g_this = this;
	m_bPainting = false;
	
}

CCustomUI::~CCustomUI()
{
	for (int v=0;v<m_pOperators.GetUsed();v++)
	{
		delete m_pOperators[v];
	}

	m_pOperators.DisposeData();

	m_Props.Clear();

	DestroyWindow ( l_hWnd );
	l_hWnd = NULL;

	for (int d=0;d<m_Deferred.GetUsed();d++)
	{
		delete m_Deferred[d];
	}

	m_Deferred.DisposeData();


}

LRESULT	CCustomUI::Init( XSI::CRef& in_pViewCtx )
{
	XSI::ViewContext l_vViewContext = in_pViewCtx;
	assert ( l_vViewContext.IsValid() );


	l_hWnd = CreateDialog(  __gInstance ,  MAKEINTRESOURCE(IDD_CUSTOMUI_EXAMPLE), (HWND)l_vViewContext.GetParentWindowHandle(), (DLGPROC)_view_proc);

	SetWindowLongPtr ( l_hWnd, GWLP_USERDATA, (LONG_PTR)this);

	for (int c=0;c<m_pOperators.GetUsed();c++)
	{
		m_pOperators[c]->SetParent ( l_hWnd );
		SendDlgItemMessage ( l_hWnd, IDC_OPERATORS, CB_ADDSTRING, 0, (LPARAM)m_pOperators[c]->GetName() );


	}

	
	return S_OK;
}

LRESULT	CCustomUI::Term( XSI::CRef& in_pViewCtx )
{

	DestroyWindow ( l_hWnd );
	l_hWnd = NULL;

	
	return S_OK;
}

LRESULT CCustomUI::Notify ( XSI::CRef& in_pViewCtx )
{
	using namespace XSI;

	XSI::ViewContext l_vViewContext = in_pViewCtx;
	assert ( l_vViewContext.IsValid() );

	XSI::siEventID in_eNotifcation;
	void*	in_pData;

	if ( m_bIgnoreNotifications )
		return S_OK;

	l_vViewContext.GetNotificationData ( in_eNotifcation, &in_pData );


	switch ( in_eNotifcation )
	{
	case siOnSelectionChange:
		{
			OnSelectionChange ( in_pData );

			break;
			
		}
	case siOnValueChange:
		{
			OnValueChange ( in_pData );

			break;
		}

/*
	case siOnTimeChange:
		{
			XSI::CTimeChangeEvent* l_pTimeChange = (XSI::CTimeChangeEvent*)in_pData;
			
			XSI::CString	l_szMessage;
			l_szMessage = L"XSI_TIME_CHANGE_CV";
		
			char *l_szMessChar = new char [ l_szMessage.Length() + 1 ];
			DSW2AHelper ( l_szMessChar, l_szMessage.GetWideString() );
			PrintNotification ( l_szMessChar );
			delete [] l_szMessChar;
			
			break;
		}

	case siOnValueChange:
		{
			XSI::CString	l_szMessage;
			l_szMessage = L"XSI_SET_VALUE_CV ";
		
			XSI::CValueChangeEvent* l_pData = (XSI::CValueChangeEvent*) in_pData;

			XSI::CString l_csCIDName = l_pData->GetOwner().GetClassIDName();

			l_szMessage += l_csCIDName;
			l_szMessage += L" [ ";
			l_szMessage += l_pData->GetComponentName();
			l_szMessage += L" ]";
				
			char *l_szMessChar = new char [ l_szMessage.Length() + 1 ];
			DSW2AHelper ( l_szMessChar, l_szMessage.GetWideString() );
			PrintNotification ( l_szMessChar );
			delete [] l_szMessChar;
			
			break;

		}
*/
	}


	return S_OK;
}

void	CCustomUI::OnValueChange	( void* in_pData )
{
	XSI::CValueChangeNotification	*l_pEventData = (XSI::CValueChangeNotification*)in_pData;
	
	XSI::siClassID	l_ClassID = l_pEventData->GetOwner().GetClassID();

	switch ( l_ClassID )
	{
	case XSI::siPrimitiveID:
			{
				XSI::CRef l_pSelectedCRef = l_pEventData->GetOwner();
				
				if ( !l_pSelectedCRef.IsValid() )
					break;
				
				XSI::Primitive	myPrimitive( l_pSelectedCRef );
				
				if ( !myPrimitive.IsValid() )
				{
					//
					// perhaps it's a X3DObject
					//
					
					XSI::X3DObject	myx3DObject ( l_pSelectedCRef );
					
					assert ( myx3DObject.IsValid() );
					
					
					myPrimitive = myx3DObject.GetActivePrimitive();
					
				}
				
				assert ( myPrimitive.IsValid() );
				
				if ( !myPrimitive.IsValid() )
					break;
				
				XSI::PolygonMesh	myMesh = myPrimitive.GetGeometry();
				
				bool found = false;

				for (int d=0;d<m_Deferred.GetUsed();d++)
				{
					if ( m_Deferred[d]->mesh == myMesh )
					{
						found = true;
						break;
					}
				}

				if (!found)
				{
					DeferredTask *def = new DeferredTask;
					def->mesh = myMesh;

					m_Deferred.Extend(1);
					m_Deferred[m_Deferred.GetUsed()-1] = def;
				}
				
				XSI::CRefArray rarray;
				rarray = myMesh.GetVertexColors();

				UpdateVPropCombo ( rarray );

				break;
			}
	
	}
}

void	CCustomUI::OnSelectionChange	( void* in_pData )
{
	SendDlgItemMessage ( l_hWnd, IDC_VPROPLIST, LB_RESETCONTENT, 0,0 );
	m_Props.Clear();

	XSI::CSelectionChangeNotification	*l_pEventData = (XSI::CSelectionChangeNotification*)in_pData;

	XSI::CRefArray l_selList = l_pEventData->GetSelectionList();
	if ( !l_selList.GetCount() )
		return;

	XSI::CRef l_pSelectedCRef = l_selList.GetItem(0);

	if ( !l_pSelectedCRef.IsValid() )
		return;

	XSI::Primitive	myPrimitive( l_pSelectedCRef );

	if ( !myPrimitive.IsValid() )
	{
		//
		// perhaps it's a X3DObject
		//
		
		XSI::X3DObject	myx3DObject ( l_pSelectedCRef );

		if ( !myx3DObject.IsValid() )
			return;


		myPrimitive = myx3DObject.GetActivePrimitive();

	}

	assert ( myPrimitive.IsValid() );

	if ( !myPrimitive.IsValid() )
		return;

	XSI::PolygonMesh	myMesh = myPrimitive.GetGeometry();


	XSI::CRefArray rarray;
	rarray = myMesh.GetVertexColors();

	UpdateVPropCombo ( rarray );


				//m_Global = m_Camera.GetKinematics().GetGlobal();
//				m_X = m_Global.GetParameters().GetItem( L"posx" );
//				m_Y = m_Global.GetParameters().GetItem( L"posy" );
//				m_Z = m_Global.GetParameters().GetItem( L"posz" );

				//m_iX = m_Camera.GetInterest().GetKinematics().GetGlobal().GetParameters().GetItem( L"posx" );
				//m_iY = m_Camera.GetInterest().GetKinematics().GetGlobal().GetParameters().GetItem( L"posy" );
				//m_iZ = m_Camera.GetInterest().GetKinematics().GetGlobal().GetParameters().GetItem( L"posz" );

}

LRESULT CCustomUI::SetWindowSize(int ox, int oy, int cx, int cy)
{

	SetWindowPos( l_hWnd,NULL,ox,oy,cx,cy,SWP_NOZORDER); 

	return S_OK;
}

	
LRESULT CCustomUI::Paint( WPARAM, LPARAM )
{
	
	return S_OK;
}

LRESULT CCustomUI::MouseMove( WPARAM, LPARAM )
{

	return S_OK;
}

void	CCustomUI::AddOperator ( CVertexColorOperator* in_pOperator )
{
	m_pOperators.Extend(1);
	m_pOperators[m_pOperators.GetUsed()-1] = in_pOperator;

}
/*
void	CCustomUI::UpdateTaskList ( )
{
	SendDlgItemMessage ( l_hWnd, IDC_TASKS, LB_RESETCONTENT, 0,0 );


	for (int t=0;t<m_pOperators[0]->GetTaskList().GetUsed();t++)
	{
		char *l_name = new char [ m_pOperators[0]->GetTaskList()[t]->m_PolygonMesh.GetName().Length() + 1 ];
		DSW2AHelper ( l_name, m_pOperators[0]->GetTaskList()[t]->m_PolygonMesh.GetName().GetWideString() );

		char *l_clustername = new char [ m_pOperators[0]->GetTaskList()[t]->m_ClusterProp.GetName().Length() + 1 ];
		DSW2AHelper ( l_clustername, m_pOperators[0]->GetTaskList()[t]->m_ClusterProp.GetName().GetWideString() );

		char fulltext[1024];
		sprintf ( fulltext, "%s.%s.%s",l_name, l_clustername, m_pOperators[0]->GetTaskList()[t]->m_pOperator->GetName() );

		SendDlgItemMessage ( l_hWnd, IDC_TASKS, LB_ADDSTRING, 0,(LPARAM)fulltext );

		delete [] l_name;
		delete [] l_clustername;

	}
}
*/

void	CCustomUI::UpdateVPropCombo ( XSI::CRefArray in_array, BOOL in_bReset  )
{
	if ( in_bReset )
		SendDlgItemMessage ( l_hWnd, IDC_VPROPLIST, LB_RESETCONTENT, 0,0 );

	XSI::PolygonMesh	mesh = m_pOperators[0]->GetSelectedPolygonMesh();

	XSI::ClusterProperty	l_pCurrentProp;
	if ( mesh.IsValid() )
	{
		l_pCurrentProp = mesh.GetCurrentVertexColor();
	}

	for (LONG v=0;v<in_array.GetCount();v++)
	{
		XSI::ClusterProperty l_pProp ( in_array[v] );

		if ( l_pProp.IsValid() )
		{
			char *l_name = new char [ l_pProp.GetName().Length() + 1 ];

			DSW2AHelper ( l_name, l_pProp.GetName().GetWideString() );

			char fulltext[1024];
			sprintf ( fulltext, "%s",l_name );
			
			if ( in_bReset )
			{
				SendDlgItemMessage ( l_hWnd, IDC_VPROPLIST, LB_ADDSTRING, 0,(LPARAM)fulltext );
			
			} else {

				SendDlgItemMessage ( l_hWnd, IDC_VPROPLIST, LB_DELETESTRING, v,0 );
				SendDlgItemMessage ( l_hWnd, IDC_VPROPLIST, LB_INSERTSTRING, v,(LPARAM)fulltext );


			}

			delete [] l_name;

		}
	}

	m_Props.Clear();
	m_Props = in_array;


}

void	CCustomUI::ExecuteOperator()
{
	
	CVertexColorOperator*	l_pOp = GetCurrentOperator();

	if ( l_pOp == NULL )
		return;

	int l_iReq = l_pOp->GetNumRequiredProperties ();


	XSI::CRefArray l_pPropList = GetSelectedProperties();

	if ( l_iReq )
	{
		if ( l_pPropList.GetCount() != l_iReq )
		{
			char mess[1024];
			sprintf ( mess, "The %s operator works on %d clusters only", l_pOp->GetName (), l_iReq );
			MessageBox ( l_hWnd, mess, "Wrong number of properties selected", MB_OK );
			return;
		}
	}

	m_bIgnoreNotifications = TRUE;

	l_pOp->Run ( l_pPropList );

	m_bIgnoreNotifications = FALSE;

	//
	// update the combo
	//

	XSI::Application app;

	XSI::CRef l_pSelectedCRef = app.GetSelection()[0];
				
	if ( !l_pSelectedCRef.IsValid() )
		return;
				
	XSI::Primitive	myPrimitive( l_pSelectedCRef );
	
	if ( !myPrimitive.IsValid() )
	{
		//
		// perhaps it's a X3DObject
		//
		
		XSI::X3DObject	myx3DObject ( l_pSelectedCRef );
		
		assert ( myx3DObject.IsValid() );
		
		
		myPrimitive = myx3DObject.GetActivePrimitive();
		
	}
	
	assert ( myPrimitive.IsValid() );
	
	if ( !myPrimitive.IsValid() )
		return;
	
	XSI::PolygonMesh	myMesh = myPrimitive.GetGeometry();
	
	
	XSI::CRefArray rarray;
	rarray = myMesh.GetVertexColors();
	
	UpdateVPropCombo ( rarray );

	//UpdateTaskList();
	

}

CVertexColorOperator*	CCustomUI::GetCurrentOperator()
{

	//
	// Get current operator
	//

	char current_operator[1024];
	current_operator[0] = 0;

	int cursel = (int)SendDlgItemMessage ( l_hWnd, IDC_OPERATORS, CB_GETCURSEL, 0, 0 );

	if ( cursel != CB_ERR )
	{
		SendDlgItemMessage ( l_hWnd, IDC_OPERATORS, CB_GETLBTEXT, cursel, (LPARAM)current_operator );
	}

	for (int o=0;o<m_pOperators.GetUsed();o++)
	{
		if (!strcmp(current_operator, m_pOperators[o]->GetName() ))
		{
			return 	m_pOperators[o];
		}
	}

	return NULL;
}

XSI::CRefArray			CCustomUI::GetSelectedProperties()
{
	XSI::CRefArray	ref;

	int count = (int)SendDlgItemMessage ( l_hWnd, IDC_VPROPLIST, LB_GETCOUNT, 0,0 );

	for (int c=0;c<count;c++)
	{
		int sel = (int)SendDlgItemMessage ( l_hWnd, IDC_VPROPLIST, LB_GETSEL, c,0 );

		if ( sel )
		{
			ref.Add ( m_Props[c] );
		}
	}

	return ref;

}

void	CCustomUI::SetAsCurrent()
{
	XSI::CRefArray l_array = GetSelectedProperties();

	if (!l_array.GetCount() )
	{
		return;
	}

	XSI::PolygonMesh mesh = m_pOperators[0]->GetSelectedPolygonMesh();

	if ( !mesh.IsValid() )
		return;

	XSI::ClusterProperty cav ( l_array[0] );

	mesh.PutCurrentVertexColor(cav);

	CVertexColorOperator*	l_pOp = GetCurrentOperator();

	if ( l_pOp == NULL )
		return;

	for (int o=0;o<m_pOperators.GetUsed();o++)
	{
		if ( l_pOp != m_pOperators[o] )
			m_pOperators[o]->Activate(FALSE);
	}


	l_pOp->Activate ( TRUE );
}

void	CCustomUI::Paint ()
{
	XSI::Application app;

	XSI::CValueArray args(1);
	XSI::CValue outArg;
	args[0] = XSI::CValue ();

	app.ExecuteCommand ( L"PaintVertexColorTool",args, outArg );


}

void	CCustomUI::AddLayer()
{
	XSI::PolygonMesh mesh = m_pOperators[0]->GetSelectedPolygonMesh();

	if ( !mesh.IsValid() )
		return;

	m_bIgnoreNotifications = TRUE;

	XSI::ClusterProperty cav;
	cav = mesh.AddVertexColor();
	
	mesh.PutCurrentVertexColor(cav);

	XSI::CRefArray rarray;
	rarray = mesh.GetVertexColors();
				
	UpdateVPropCombo ( rarray );

	m_bIgnoreNotifications = FALSE;

}

void	CCustomUI::BrushProperties()
{

	XSI::Application app;

	XSI::CValueArray args(1);
	XSI::CValue outArg;
	args[0] = XSI::CValue ( L"BrushProperties" );

	
	app.ExecuteCommand ( L"InspectObj",args, outArg );
}


void	CCustomUI::RemoveLayer()
{
	XSI::CRefArray l_pPropList = GetSelectedProperties();

	if ( !l_pPropList.GetCount() )
		return;
	
	XSI::PolygonMesh mesh = m_pOperators[0]->GetSelectedPolygonMesh();

	if ( !mesh.IsValid() )
		return;

	m_bIgnoreNotifications = TRUE;


	XSI::CValueArray args(1);
	XSI::CValue outArg;
	args[0] = l_pPropList;

	XSI::Application app;
	app.ExecuteCommand( L"DeleteObj", args, outArg);

	XSI::CRefArray rarray;
	rarray = mesh.GetVertexColors();

	UpdateVPropCombo ( rarray );

	if ( rarray.GetCount() )
	{
		XSI::ClusterProperty cav ( rarray[0] );
		mesh.PutCurrentVertexColor(cav);

	}

	m_bIgnoreNotifications = FALSE;

}

void CCustomUI::Disable ( BOOL in_bDisable )
{
	m_bIgnoreNotifications = in_bDisable;

}
/*
void	CCustomUI::UpdateTasks ()
{
	//
	// check to see if we have dependant tasks
	//
	m_bIgnoreNotifications = TRUE;

	for (int d=0;d<m_Deferred.GetUsed();d++)
	{

		for (int t=0;t<m_pOperators[0]->GetTaskList().GetUsed();t++)
		{
			if ( m_pOperators[0]->GetTaskList()[t]->m_PolygonMesh == m_Deferred[d]->mesh )
			{
				//
				// yup, run the task 
				//

				m_pOperators[0]->GetTaskList()[t]->m_pOperator->DoInteractive ( m_pOperators[0]->GetTaskList()[t] );

			}

		}

		delete m_Deferred[d];
	}

	m_Deferred.DisposeData();

	m_bIgnoreNotifications = FALSE;
}

*/
LRESULT CALLBACK	_view_proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	CCustomUI*	l_pWindow = (CCustomUI*)GetWindowLongPtr ( hDlg, GWLP_USERDATA );
	
	switch (message)
	{
		

		case WM_INITDIALOG:
			{
			
				return TRUE;

			}

			break;

		case WM_SHOWWINDOW:
			{
				if ( l_pWindow )
					l_pWindow->Disable ( !wParam );
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
						
					case CBN_SELCHANGE:
						{
							l_pWindow->SetAsCurrent();
							break;
						}
						
						
					}
					
					
					switch (LOWORD(wParam) )
					{
					case IDC_RUN:
						l_pWindow->ExecuteOperator();
						break;
						
					case IDC_ADD:
						l_pWindow->AddLayer();
						break;
						
					case IDC_REMOVE:
						l_pWindow->RemoveLayer();
						break;
					case IDC_BRUSHPROPS:
						l_pWindow->BrushProperties();
						break;
					case IDC_PAINT:
						l_pWindow->Paint();
						break;
						
					}
				}
			}


	}

    return FALSE;
}


void DSW2AHelper( LPSTR out_sz, LPCWSTR in_wcs, int in_cch )
{
	if ( out_sz != NULL && 0 != in_cch )
	{
		out_sz[0] = '\0' ;

		if ( in_wcs != NULL )
		{
			// Right now, we can't really test the return value because wcstombs() is
			// mapped to strcpy() on the Irix o32 build. When this build is not done
			// anymore, the != 0 test should be updated.

			size_t l_iLen = 0;
			l_iLen = ::wcstombs( out_sz, in_wcs, ( in_cch < 0 ) ? ::wcslen(in_wcs) + 1 : (size_t) in_cch ) ;

			if ( in_cch > 0 ) { out_sz[ in_cch - 1 ] = '\0'; }
		}
	}
}



