// ColorCorrection.h: interface for the CColorCorrection class.
//
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLORCORRECTION_H__74A1E184_3082_4C7A_B0C5_3833C50501B4__INCLUDED_)
#define AFX_COLORCORRECTION_H__74A1E184_3082_4C7A_B0C5_3833C50501B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VertexColorOperator.h"

class CColorCorrection : public CVertexColorOperator  
{
public:
	CColorCorrection();
	virtual ~CColorCorrection();

	virtual	char*	GetName() { return "Color Correction"; };
	virtual int		GetNumRequiredProperties() { return 0; };
	virtual int		Run( XSI::CRefArray in_RefArray );
	virtual void	Activate ( BOOL );
	
	void			SetColorCorrectionValues ( int hue, int sat, int lum );
	void			ColorCorrect();

	int m_hue;
	int m_sat;
	int m_lum;
	
	 XSI::CRefArray	m_cache;
};

#endif // !defined(AFX_COLORCORRECTION_H__74A1E184_3082_4C7A_B0C5_3833C50501B4__INCLUDED_)
