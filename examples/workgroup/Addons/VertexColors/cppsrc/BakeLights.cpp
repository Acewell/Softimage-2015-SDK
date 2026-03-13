// BakeLights.cpp: implementation of the BakeLights class.
//
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BakeLights.h"

#include <assert.h>

#include <xsi_material.h>
#include <xsi_string.h>

inline void DSA2WHelper( LPWSTR out_wcs, LPCSTR in_sz, int in_cch = -1 )
{
	if ( out_wcs != NULL && 0 != in_cch )
	{
		out_wcs[0] = L'\0' ;

		if ( in_sz != NULL )
		{
			// Right now, we can't really test the return value because mbstowcs() is
			// mapped to strcpy() on the Irix o32 build. When this build is not done
			// anymore, the != 0 test should be updated.

			size_t l_iLen = 0;
			l_iLen = ::mbstowcs( out_wcs, in_sz, ( in_cch < 0 ) ? ::strlen(in_sz) + 1 : (size_t) in_cch ) ;
			assert( (int)l_iLen != -1 );

        		if ( in_cch > 0 ) { out_wcs[ in_cch - 1 ] = L'\0'; }
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern HINSTANCE __gInstance;

LRESULT CALLBACK	_bakelight_proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

BakeLights::BakeLights()
{

}

BakeLights::~BakeLights()
{

}

int		BakeLights::Run( XSI::CRefArray in_RefArray )
{

	using namespace XSI;

	X3DObject		x3d = GetSelectedX3DObject();

	assert ( x3d.IsValid() );

	char lm[1024];
	lm[0] = 0;
	int cursel = (int)SendDlgItemMessage ( m_hwnd, IDC_LIGHTINGMODEL, CB_GETCURSEL, 0,0);
	if ( cursel != CB_ERR )
	{
		SendDlgItemMessage ( m_hwnd, IDC_LIGHTINGMODEL, CB_GETLBTEXT, cursel, (LPARAM)lm );
	} else {
		return 0;
	}

	wchar_t	bla[1024];
	DSA2WHelper ( bla,lm );
	//Add a material
	Material myMat;
	x3d.AddMaterial(bla, false, L"", myMat);

	CValueArray args(1);

	args[0] = CValue(L"RenderMap");
	CValue retVal;
	Application app;
    app.ExecuteCommand( L"AddProp", args, retVal );

//maptype

	args.Resize(2);

	CString	obj_name = x3d.GetFullName();
	obj_name += L".RenderMap.maptype";

	args[0] = CValue(obj_name.GetWideString ());
	args[1] = 1l;
	app.ExecuteCommand( L"SetValue", args, retVal ) ;

	obj_name = x3d.GetFullName();
	obj_name += L".RenderMap.vertaveraging";

	args[0] = CValue(obj_name.GetWideString ());
	args[1] = true;
	app.ExecuteCommand( L"SetValue", args, retVal ) ;
	

	XSI::PolygonMesh	mesh = GetSelectedPolygonMesh();

	XSI::ClusterProperty cav;;
	cav = mesh.AddVertexColor();
	cav.PutName( L"BakedLightsResult" );

	args.Resize(3);

	obj_name = x3d.GetFullName();
	obj_name += L".RenderMap.cav";

	args[0] = CValue();	// default
	args[1] = CValue(obj_name.GetWideString ());
	args[2] = CValue(cav.GetName());
		
	app.ExecuteCommand( L"SetInstanceDataValue", args, retVal ) ;

	args.Resize(1);
	obj_name = x3d.GetFullName();
	obj_name += L".RenderMap";
	
	args[0] = CValue(obj_name.GetWideString ());
	app.ExecuteCommand( L"RegenerateMaps", args, retVal ) ;

	app.ExecuteCommand( L"DeleteObj", args, retVal ) ;

	mesh.PutCurrentVertexColor(cav);

	return 0;
}

int		BakeLights::DoInteractive( InteractiveTask* in_pTask )
{
	using namespace XSI;


	
	//Add a material
	Material myMat;
	in_pTask->m_x3d.AddMaterial(L"Phong", false, L"", myMat);

	CValueArray args(1);

	args[0] = CValue(L"RenderMap");
	CValue retVal;
	Application app;
    app.ExecuteCommand( L"AddProp", args, retVal );

//maptype

	args.Resize(2);

	CString	obj_name = in_pTask->m_x3d.GetFullName();
	obj_name += L".RenderMap.maptype";

	args[0] = CValue(obj_name.GetWideString ());
	args[1] = 1l;
	app.ExecuteCommand( L"SetValue", args, retVal ) ;

	XSI::PolygonMesh	mesh = in_pTask->m_PolygonMesh;

	args.Resize(3);

	obj_name = in_pTask->m_x3d.GetFullName();
	obj_name += L".RenderMap.cav";

	args[0] = CValue();	// default
	args[1] = CValue(obj_name.GetWideString ());
	args[2] = CValue(in_pTask->m_ClusterProp.GetName());
		
	app.ExecuteCommand( L"SetInstanceDataValue", args, retVal ) ;

	args.Resize(1);
	obj_name = in_pTask->m_x3d.GetFullName();
	obj_name += L".RenderMap";
	
	args[0] = CValue(obj_name.GetWideString ());
	app.ExecuteCommand( L"RegenerateMaps", args, retVal ) ;

	app.ExecuteCommand( L"DeleteObj", args, retVal ) ;

	mesh.PutCurrentVertexColor(in_pTask->m_ClusterProp);

	return 0;

}


void	BakeLights::Activate ( BOOL in_bActivate)
{
	if ( in_bActivate )
	{
		if ( m_hwnd == NULL )
		{
			m_hwnd = CreateDialog(  __gInstance ,  MAKEINTRESOURCE(IDD_BAKELIGHTS), (HWND)m_hParent, (DLGPROC)_bakelight_proc);
		}

		ShowWindow(m_hwnd, SW_SHOW);

		CVertexColorOperator::Activate ( in_bActivate );
	} else {

		ShowWindow(m_hwnd, SW_HIDE);
	}
	
	UpdateWindow ( m_hwnd );

}

LRESULT CALLBACK	_bakelight_proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
		

		case WM_INITDIALOG:
			{
				SendDlgItemMessage ( hDlg, IDC_LIGHTINGMODEL, CB_ADDSTRING, 0, (LPARAM)"Phong" );
				SendDlgItemMessage ( hDlg, IDC_LIGHTINGMODEL, CB_ADDSTRING, 0, (LPARAM)"Lambert" );
				SendDlgItemMessage ( hDlg, IDC_LIGHTINGMODEL, CB_ADDSTRING, 0, (LPARAM)"Blinn" );
				SendDlgItemMessage ( hDlg, IDC_LIGHTINGMODEL, CB_ADDSTRING, 0, (LPARAM)"Cooktorrance" );
				SendDlgItemMessage ( hDlg, IDC_LIGHTINGMODEL, CB_ADDSTRING, 0, (LPARAM)"Strauss" );
				SendDlgItemMessage ( hDlg, IDC_LIGHTINGMODEL, CB_ADDSTRING, 0, (LPARAM)"Anisotropic" );
				SendDlgItemMessage ( hDlg, IDC_LIGHTINGMODEL, CB_SETCURSEL, 0, 0 );
				return TRUE;

			}

			break;

		case WM_COMMAND:
			{
				switch (HIWORD(wParam))
				{

				case CBN_SELCHANGE:
					{
				
					break;
					}

		
				}
	

		
			}


	}

	return DefWindowProc(hDlg, message, wParam, lParam);
}

