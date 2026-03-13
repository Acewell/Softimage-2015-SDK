// BakeLights.h: interface for the BakeLights class.
//
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BAKELIGHTS_H__3308271D_44A1_4633_BC49_91F2441114BE__INCLUDED_)
#define AFX_BAKELIGHTS_H__3308271D_44A1_4633_BC49_91F2441114BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VertexColorOperator.h"

class BakeLights : public CVertexColorOperator 
{
public:
	BakeLights();
	virtual ~BakeLights();

	virtual	char*	GetName() { return "Bake Lights"; };
	virtual int		GetNumRequiredProperties() { return 0; };
	virtual int		Run( XSI::CRefArray in_RefArray );
	virtual void	Activate ( BOOL );
	virtual int		DoInteractive( InteractiveTask*  );
};

#endif // !defined(AFX_BAKELIGHTS_H__3308271D_44A1_4633_BC49_91F2441114BE__INCLUDED_)
