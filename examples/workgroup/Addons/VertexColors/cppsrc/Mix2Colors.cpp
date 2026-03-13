// Mix2Colors.cpp: implementation of the CMix2Colors class.
//
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <assert.h>
#include "Mix2Colors.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern HINSTANCE __gInstance;

CMix2Colors	*__gthis = NULL;

LRESULT CALLBACK	_mix2colors_proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

CMix2Colors::CMix2Colors()
{
	__gthis = this;
}

CMix2Colors::~CMix2Colors()
{

}

int		CMix2Colors::Run( XSI::CRefArray in_RefArray )
{

	using namespace XSI;
	X3DObject		x3d = GetSelectedX3DObject();

	assert ( x3d.IsValid() );

	Material myMat;
	x3d.AddMaterial(L"Phong", false, L"", myMat);

	
	CValueArray args(3);

	args[0] = CValue();
	args[1] = CValue(L"Shaders\\Texture\\Mixers\\Mix_2colors.Preset");
	args[2] = CValue(L"TransientObjectContainer");

	CValue retVal;
	Application app;
    app.ExecuteCommand( L"CopyPaste", args, retVal );

	args.Resize(2);

	CString	obj_name = myMat.GetFullName();
	obj_name += L".Phong.diffuse";

	args[0] = CValue(L"TransientObjectContainer.Mix_2colors");
	args[1] = CValue(obj_name);
	app.ExecuteCommand( L"SIConnectShaderToCnxPoint", args, retVal ) ;

	//
	// Get 1st Vertex_RGBA preset
	//

	args.Resize(3);
	args[0] = CValue();
	args[1] = CValue(L"Shaders\\Texture\\Vertex_rgba.Preset");
	args[2] = CValue(L"TransientObjectContainer");

    app.ExecuteCommand( L"CopyPaste", args, retVal );

	args.Resize(2);
	obj_name = myMat.GetFullName();
	obj_name += L".Phong.Mix_2colors.base_color";
	args[0] = CValue(L"TransientObjectContainer.Vertex_rgba");
	args[1] = CValue(obj_name);
	app.ExecuteCommand( L"SIConnectShaderToCnxPoint", args, retVal ) ;

	obj_name = myMat.GetFullName();
	obj_name += L".Phong.Mix_2colors.Vertex_rgba.vprop";

	XSI::ClusterProperty	l_array1 ( in_RefArray[0] );

	args.Resize(3);
	args[0] = CValue();	// default
	args[1] = CValue(obj_name.GetWideString ());
	args[2] = CValue(l_array1.GetName());
		
	app.ExecuteCommand( L"SetInstanceDataValue", args, retVal ) ;


	//
	// Get 1st Vertex_RGBA preset
	//

	args.Resize(3);
	args[0] = CValue();
	args[1] = CValue(L"Shaders\\Texture\\Vertex_rgba.Preset");
	args[2] = CValue(L"TransientObjectContainer");

    app.ExecuteCommand( L"CopyPaste", args, retVal );

	args.Resize(2);
	obj_name = myMat.GetFullName();
	m_szMixPropertyName = obj_name;
	obj_name += L".Phong.Mix_2colors.color1";
	args[0] = CValue(L"TransientObjectContainer.Vertex_rgba");
	args[1] = CValue(obj_name);
	app.ExecuteCommand( L"SIConnectShaderToCnxPoint", args, retVal ) ;

	obj_name = myMat.GetFullName();
	obj_name += L".Phong.Mix_2colors.Vertex_rgba1.vprop";

	XSI::ClusterProperty	l_array2 ( in_RefArray[1] );

	args.Resize(3);
	args[0] = CValue();	// default
	args[1] = CValue(obj_name.GetWideString ());
	args[2] = CValue(l_array2.GetName());
		
	app.ExecuteCommand( L"SetInstanceDataValue", args, retVal ) ;

	args.Resize(2);
	args[0] = CValue(L"Camera");
	args[1] = CValue(L"Cg");
	app.ExecuteCommand( L"SetDisplayMode", args, retVal ) ;
	
	m_szMixPropertyName += L".Phong.Mix_2colors.mode1";

	//SetValue "Sources.Materials.DefaultLib.Material1.Phong.Mix_2colors.mode1", 1

	return 0;


}

void	CMix2Colors::Activate ( BOOL in_bActive )
{

	if ( in_bActive )
	{
		if ( m_hwnd == NULL )
		{
			m_hwnd = CreateDialog(  __gInstance ,  MAKEINTRESOURCE(IDD_MIX2COLORS), (HWND)m_hParent, (DLGPROC)_mix2colors_proc);
		}

		ShowWindow(m_hwnd, SW_SHOW);

		CVertexColorOperator::Activate ( in_bActive );
	} else {

		ShowWindow(m_hwnd, SW_HIDE);
	}
	
	UpdateWindow ( m_hwnd );


}


LRESULT CALLBACK	_mix2colors_proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
		

		case WM_INITDIALOG:
			{
				SendDlgItemMessage ( hDlg, IDC_OP, CB_ADDSTRING, 0, (LPARAM)"Add Compensate (Blend)" );
				SendDlgItemMessage ( hDlg, IDC_OP, CB_ADDSTRING, 0, (LPARAM)"Mix"	);
				SendDlgItemMessage ( hDlg, IDC_OP, CB_ADDSTRING, 0, (LPARAM)"Add"			);
				SendDlgItemMessage ( hDlg, IDC_OP, CB_ADDSTRING, 0, (LPARAM)"Add Bound"	);
				SendDlgItemMessage ( hDlg, IDC_OP, CB_ADDSTRING, 0, (LPARAM)"Hide/Reveal Bound (Multiply)"	);
				SendDlgItemMessage ( hDlg, IDC_OP, CB_ADDSTRING, 0, (LPARAM)"Hide/Reveal(Multiply)"	);
				SendDlgItemMessage ( hDlg, IDC_OP, CB_ADDSTRING, 0, (LPARAM)"RGB Intensity"	);
				SendDlgItemMessage ( hDlg, IDC_OP, CB_ADDSTRING, 0, (LPARAM)"Darker"		);
				SendDlgItemMessage ( hDlg, IDC_OP, CB_ADDSTRING, 0, (LPARAM)"Lighter"		);
				SendDlgItemMessage ( hDlg, IDC_OP, CB_ADDSTRING, 0, (LPARAM)"Difference (Subtract)"	);
				SendDlgItemMessage ( hDlg, IDC_OP, CB_ADDSTRING, 0, (LPARAM)"Hard Light");
				SendDlgItemMessage ( hDlg, IDC_OP, CB_ADDSTRING, 0, (LPARAM)"Hue Offset (Overlay)");
				SendDlgItemMessage ( hDlg, IDC_OP, CB_ADDSTRING, 0, (LPARAM)"Screen");
				SendDlgItemMessage ( hDlg, IDC_OP, CB_ADDSTRING, 0, (LPARAM)"Soft Light");
				SendDlgItemMessage ( hDlg, IDC_OP, CB_ADDSTRING, 0, (LPARAM)"Decal"	);
				SendDlgItemMessage ( hDlg, IDC_OP, CB_ADDSTRING, 0, (LPARAM)"Alpha"	);
				SendDlgItemMessage ( hDlg, IDC_OP, CB_ADDSTRING, 0, (LPARAM)"RGB Modulate");
				return TRUE;
				
			}
			break;

		case WM_COMMAND:
			{
				// Get index of selected item.
				int cursel = (int)SendDlgItemMessage ( hDlg, IDC_OP, CB_GETCURSEL,0,0);

				if ( cursel != CB_ERR )
				{
					if ( 	__gthis->m_szMixPropertyName.Length() > 0 )
					{
						XSI::CValueArray args(2);
						
						args[0] = XSI::CValue(__gthis->m_szMixPropertyName);
						args[1] = XSI::CValue((LONG)cursel);
											
						XSI::CValue retVal;
						XSI::Application app;
						app.ExecuteCommand( L"SetValue", args, retVal );


					}

				}
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

