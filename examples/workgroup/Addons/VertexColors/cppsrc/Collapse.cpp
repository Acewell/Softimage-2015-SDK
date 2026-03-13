// Collapse.cpp: implementation of the CCollapse class.
//
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <assert.h>
#include "Collapse.h"
#include <math.h>
#include <xsi_vertexcolor.h>
#include <xsi_application.h>
#include <xsi_selection.h>

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
#include <xsi_clusterproperty.h>
#include <xsi_doublearray.h>

extern HINSTANCE __gInstance;


double g_current_alpha = 0.0;

typedef double		(*OPERATION) ( double r1, double r2, double w1 );

double Alpha ( double r1, double r2, double w1 );
double Decal ( double r1, double r2, double w1 );
double RGBModulate ( double r1, double r2, double w1 );
double Mix ( double r1, double r2, double w1 );
double HideReveal ( double r1, double r2, double w1 );
double HideRevealBound ( double r1, double r2, double w1 );
double Add ( double r1, double r2, double w1 );
double AddCompensate ( double r1, double r2, double w1 );
double AddBound ( double r1, double r2, double w1 );
double Lighter ( double r1, double r2, double w1 );
double Darker ( double r1, double r2, double w1 );
double Difference ( double r1, double r2, double w1 );


OPERATION	OperationMap[] = {
Alpha,
Decal,
RGBModulate,
Mix,
HideReveal,
HideRevealBound,
Add,
AddCompensate,
AddBound,
Lighter,
Darker,
Difference
};




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LRESULT CALLBACK	_collapse_proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

CCollapse::CCollapse()
{
	
}

CCollapse::~CCollapse()
{

}

void	CCollapse::Activate ( BOOL in_bActivate )
{
	if ( in_bActivate )
	{
		if ( m_hwnd == NULL )
		{
			m_hwnd = CreateDialog(  __gInstance ,  MAKEINTRESOURCE(IDD_COLLAPSEOPTIONS), (HWND)m_hParent, (DLGPROC)_collapse_proc);
		}

		ShowWindow(m_hwnd, SW_SHOW);

		CVertexColorOperator::Activate ( in_bActivate );
	} else {

		ShowWindow(m_hwnd, SW_HIDE);
	}
	
	UpdateWindow ( m_hwnd );

	
}


int		CCollapse::Run( XSI::CRefArray in_RefArray )
{

	int sel = (int)SendDlgItemMessage ( m_hwnd, IDC_OP, CB_GETCURSEL,0,0 );

	if ( sel == CB_ERR )
		return 0;


	/*
		ClusterProperty vertexColor(myGridMesh.AddVertexColor());
	UTASSERT( vertexColor.IsValid() );

	

	// put the color
	UTASSERT( vertexColor.GetElements().PutArray(colorsArray) == CStatus::OK );
	UTASSERT( myGridMesh.PutCurrentVertexColor(vertexColor) == CStatus::OK );
	*/
	XSI::ClusterProperty	l_array1 ( in_RefArray[0] );
	XSI::ClusterProperty	l_array2 ( in_RefArray[1] );
	

	XSI::PolygonMesh	mesh = GetSelectedPolygonMesh();

	if ( !mesh.IsValid())
		return 0;
	
	XSI::ClusterProperty cav;;
	cav = mesh.AddVertexColor();
	cav.PutName ( L"CollapseResult" );

	XSI::CDoubleArray colorsArray1(l_array1.GetElements().GetArray());
	XSI::CDoubleArray colorsArray2(l_array2.GetElements().GetArray());
	XSI::CDoubleArray resultArray(cav.GetElements().GetArray());

	ULONG j;
	for(j = 0; j < colorsArray1.GetCount(); j+=4)
	{
		g_current_alpha = resultArray[j+3];

		resultArray[j] = OperationMap[sel] ( colorsArray1[j], colorsArray2[j], 0.5 );
		resultArray[j+1] = OperationMap[sel] ( colorsArray1[j+1], colorsArray2[j+1], 0.5 );
		resultArray[j+2] = OperationMap[sel] ( colorsArray1[j+2], colorsArray2[j+2], 0.5 );
		resultArray[j+3] = OperationMap[sel] ( colorsArray1[j+3], colorsArray2[j+3], 0.5 );

	}

	cav.GetElements().PutArray(resultArray);

	int keep = (int)SendDlgItemMessage ( m_hwnd, IDC_KEEPLAYERS, BM_GETCHECK,0,0 );

	if ( !keep )
	{
		
		XSI::CValueArray args(1);
		XSI::CValue outArg;
		args[0] = in_RefArray;

		XSI::Application app;
		app.ExecuteCommand( L"DeleteObj", args, outArg);

	}

	mesh.PutCurrentVertexColor(cav);

	return 0;
}


LRESULT CALLBACK	_collapse_proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
		

		case WM_INITDIALOG:
			{
				SendDlgItemMessage ( hDlg, IDC_OP, CB_ADDSTRING, 0, (LPARAM)"Alpha" );
				SendDlgItemMessage ( hDlg, IDC_OP, CB_ADDSTRING, 0, (LPARAM)"Decal" );
				SendDlgItemMessage ( hDlg, IDC_OP, CB_ADDSTRING, 0, (LPARAM)"RGB Modulate" );
				SendDlgItemMessage ( hDlg, IDC_OP, CB_ADDSTRING, 0, (LPARAM)"Mix" );
				SendDlgItemMessage ( hDlg, IDC_OP, CB_ADDSTRING, 0, (LPARAM)"Hide/Reveal(Multiply)" );
				SendDlgItemMessage ( hDlg, IDC_OP, CB_ADDSTRING, 0, (LPARAM)"Hide/Reveal Bound (Multiply)");
				SendDlgItemMessage ( hDlg, IDC_OP, CB_ADDSTRING, 0, (LPARAM)"Add");
				SendDlgItemMessage ( hDlg, IDC_OP, CB_ADDSTRING, 0, (LPARAM)"Add Compensate (Blend)");
				SendDlgItemMessage ( hDlg, IDC_OP, CB_ADDSTRING, 0, (LPARAM)"Add Bound");
				SendDlgItemMessage ( hDlg, IDC_OP, CB_ADDSTRING, 0, (LPARAM)"Lighter");
				SendDlgItemMessage ( hDlg, IDC_OP, CB_ADDSTRING, 0, (LPARAM)"Darker");
				SendDlgItemMessage ( hDlg, IDC_OP, CB_ADDSTRING, 0, (LPARAM)"Difference (Subtract)");
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


double Alpha ( double r1, double r2, double w1 )
{
	return r1 * ( 1.0-w1*r2 ) + r2 * w1 * g_current_alpha;
	
}

double Decal ( double r1, double r2, double w1 )
{

	return r1*(1.0-w1)+r2*w1;
				
}

double RGBModulate ( double r1, double r2, double w1 )
{

	return 	r1 * r2 * w1;
}

double Mix ( double r1, double r2, double w1 )
{

	return r1*(1.0-w1)+r2*w1;
}

double HideReveal ( double r1, double r2, double w1 )
{

	return 	r1  * r2 * w1;
	
}

double HideRevealBound ( double r1, double r2, double w1 )
{

	double r = r1  * r2 * w1;
	if ( r < 0.0 ) r = 0.0;
	if ( r > 1.0 ) r = 1.0;

	return r;

}

double Add ( double r1, double r2, double w1 )
{

	return r1 + r2*w1;
	}

double AddCompensate ( double r1, double r2, double w1 )
{
	return r1 *(1.0-r2*w1)+r2*w1;
}

double AddBound ( double r1, double r2, double w1 )
{
	double r = r1 + r2*w1;
	if ( r < 0.0 ) r = 0.0;
	if ( r > 1.0 ) r = 1.0;

	return r;
}

double Lighter ( double r1, double r2, double w1 )
{
	double r = max(r1,r2*w1);

	return r;
}

double Darker ( double r1, double r2, double w1 )
{

	return min(r1,r2*w1);;
}

double Difference ( double r1, double r2, double w1 )
{
	return fabs(r1-r2*w1);

}
