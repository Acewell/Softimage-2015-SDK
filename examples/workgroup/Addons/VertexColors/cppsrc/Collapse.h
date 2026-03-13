// Collapse.h: interface for the CCollapse class.
//
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLLAPSE_H__65DC8D78_92CD_4DFB_BD1C_3A4D61CBF8E4__INCLUDED_)
#define AFX_COLLAPSE_H__65DC8D78_92CD_4DFB_BD1C_3A4D61CBF8E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VertexColorOperator.h"

class CCollapse : public CVertexColorOperator  
{
public:
	CCollapse();
	virtual ~CCollapse();

	virtual	char*	GetName() { return "Collapse 2 layers"; };
	virtual int		Run( XSI::CRefArray in_RefArray );
	virtual int		GetNumRequiredProperties() { return 2; };

	virtual void	Activate ( BOOL );

};

#endif // !defined(AFX_COLLAPSE_H__65DC8D78_92CD_4DFB_BD1C_3A4D61CBF8E4__INCLUDED_)
