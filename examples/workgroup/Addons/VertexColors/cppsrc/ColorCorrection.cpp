// ColorCorrection.cpp: implementation of the CColorCorrection class.
//
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ColorCorrection.h"
#include <commctrl.h>
#include "VertexColorHelper.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern HINSTANCE __gInstance;


CColorCorrection*	__CCThis = NULL;

LRESULT CALLBACK	_cc_proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

CColorCorrection::CColorCorrection()
{
	__CCThis = this;
}

CColorCorrection::~CColorCorrection()
{

}

int		CColorCorrection::Run( XSI::CRefArray in_RefArray )
{
	for (int c=0;c<in_RefArray.GetCount();c++)
	{
	XSI::ClusterProperty	l_array ( in_RefArray[c] );
	

	XSI::PolygonMesh	mesh = GetSelectedPolygonMesh();

	if ( !mesh.IsValid())
		return 0;
	
	
	XSI::CDoubleArray colorsArray1(l_array.GetElements().GetArray());
	
	ULONG j;
	for(j = 0; j < colorsArray1.GetCount(); j+=4)
	{
		double r,g,b,a;
	
		r = colorsArray1[j];
		g = colorsArray1[j+1];
		b = colorsArray1[j+2];
		a = colorsArray1[j+3];

		double h,s,l,alpha;

		RGBA2HLSA ( r,g,b,a, &h, &s, &l, &alpha );
		
		h += m_hue / 100.0f;
		s += m_sat / 100.0f;
		l += m_lum / 100.0f;

		HLSA2RGBA ( h,s,l,alpha,&r,&g,&b,&a);

		colorsArray1[j] = r;
		colorsArray1[j+1] = g;
		colorsArray1[j+2] = b;
		colorsArray1[j+3] = a;
	}

	l_array.GetElements().PutArray(colorsArray1);

	}



	return 0;
}

void	CColorCorrection::Activate ( BOOL in_bActivate )
{
	if ( in_bActivate )
	{
		if ( m_hwnd == NULL )
		{
			m_hwnd = CreateDialog(  __gInstance ,  MAKEINTRESOURCE(IDD_COLOR_CORRECTION), (HWND)m_hParent, (DLGPROC)_cc_proc);
		}

		ShowWindow(m_hwnd, SW_SHOW);

		CVertexColorOperator::Activate ( in_bActivate );
	} else {

		ShowWindow(m_hwnd, SW_HIDE);
	}
	
	UpdateWindow ( m_hwnd );

}

void CColorCorrection::SetColorCorrectionValues ( int hue, int sat, int lum )
{
	m_hue = hue;
	m_sat = sat;
	m_lum = lum;

	ColorCorrect();

}

void CColorCorrection::ColorCorrect ()
{

	
}


LRESULT CALLBACK	_cc_proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
		

		case WM_INITDIALOG:
			{
				SendDlgItemMessage ( hDlg, IDC_HUE, TBM_SETRANGEMIN, TRUE, -100 );
				SendDlgItemMessage ( hDlg, IDC_HUE, TBM_SETRANGEMAX, TRUE, 100 );
				SendDlgItemMessage ( hDlg, IDC_HUE, TBM_SETPOS, TRUE, 0 );

				SendDlgItemMessage ( hDlg, IDC_SAT, TBM_SETRANGEMIN, TRUE, -100 );
				SendDlgItemMessage ( hDlg, IDC_SAT, TBM_SETRANGEMAX, TRUE, 100 );
				SendDlgItemMessage ( hDlg, IDC_SAT, TBM_SETPOS, TRUE, 0 );

				SendDlgItemMessage ( hDlg, IDC_LUM, TBM_SETRANGEMIN, TRUE, -100 );
				SendDlgItemMessage ( hDlg, IDC_LUM, TBM_SETRANGEMAX, TRUE, 100 );
				SendDlgItemMessage ( hDlg, IDC_LUM, TBM_SETPOS, TRUE, 0 );
				

				return TRUE;

			}

			break;

		case WM_HSCROLL:
			{
			int hue = (int)SendDlgItemMessage ( hDlg, IDC_HUE, TBM_GETPOS, 0, 0 );
			int sat = (int)SendDlgItemMessage ( hDlg, IDC_SAT, TBM_GETPOS, 0, 0 );
			int lum = (int)SendDlgItemMessage ( hDlg, IDC_LUM, TBM_GETPOS, 0, 0 );
			__CCThis->SetColorCorrectionValues ( hue, sat, lum );
			break;
			}

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
