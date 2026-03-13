// Mix2Colors.h: interface for the CMix2Colors class.
//
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIX2COLORS_H__57825601_E037_4BAB_82F7_DA67713FF86E__INCLUDED_)
#define AFX_MIX2COLORS_H__57825601_E037_4BAB_82F7_DA67713FF86E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VertexColorOperator.h"

#include <xsi_material.h>
#include <xsi_string.h>


class CMix2Colors : public CVertexColorOperator  
{
public:
	CMix2Colors();
	virtual ~CMix2Colors();

	virtual	char*	GetName() { return "Preview 2 layers"; };
	virtual int		GetNumRequiredProperties() { return 2; };
	virtual int		Run( XSI::CRefArray in_RefArray );
	virtual void	Activate ( BOOL );

	XSI::CString	m_szMixPropertyName;
};

#endif // !defined(AFX_MIX2COLORS_H__57825601_E037_4BAB_82F7_DA67713FF86E__INCLUDED_)
