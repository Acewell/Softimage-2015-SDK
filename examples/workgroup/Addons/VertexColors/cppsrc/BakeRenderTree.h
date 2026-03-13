// BakeRenderTree.h: interface for the BakeRenderTree class.
//
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BAKERENDERTREE_H__00CB56D4_B042_4D5E_A345_825FDC0CAE8F__INCLUDED_)
#define AFX_BAKERENDERTREE_H__00CB56D4_B042_4D5E_A345_825FDC0CAE8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VertexColorOperator.h"

class BakeRenderTree : public CVertexColorOperator  
{
public:
	BakeRenderTree();
	virtual ~BakeRenderTree();

	virtual	char*	GetName() { return "Bake Current RenderTree"; };
	virtual int		GetNumRequiredProperties() { return 0; };
	virtual int		Run( XSI::CRefArray in_RefArray );
	virtual void	Activate ( BOOL );

};

#endif // !defined(AFX_BAKERENDERTREE_H__00CB56D4_B042_4D5E_A345_825FDC0CAE8F__INCLUDED_)
