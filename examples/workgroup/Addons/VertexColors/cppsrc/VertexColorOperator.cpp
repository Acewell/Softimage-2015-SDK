// VertexColorOperator.cpp: implementation of the CVertexColorOperator class.
//
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VertexColorOperator.h"
#include <assert.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSIBCArray<InteractiveTask*>	CVertexColorOperator::m_pTasks;

CVertexColorOperator::CVertexColorOperator()
{
	m_hwnd = NULL;
	
}

void	CVertexColorOperator::SetParent ( HWND in_hParent )
{

	m_hParent = in_hParent;
}


CVertexColorOperator::~CVertexColorOperator()
{
	for (int t=0;t<m_pTasks.GetUsed();t++)
	{
		delete m_pTasks[t];
	}

}

XSI::X3DObject		CVertexColorOperator::GetSelectedX3DObject()
{
	
	XSI::Application app;
	XSI::Selection l_sel = app.GetSelection();
	XSI::X3DObject	myx3DObject;

	if ( !l_sel.GetCount() ) // this shouldnt happen, but whatever...
		return myx3DObject;

	XSI::CRef l_cref = l_sel[0];
	
	XSI::X3DObject x3d ( l_cref );

	myx3DObject = x3d;

	return myx3DObject;

	
}


XSI::PolygonMesh	CVertexColorOperator::GetSelectedPolygonMesh()
{

	XSI::PolygonMesh	myMesh;
	XSI::Application app;
	XSI::Selection l_sel = app.GetSelection();

	if ( !l_sel.GetCount() ) // this shouldnt happen, but whatever...
		return myMesh;

	XSI::CRef l_cref = l_sel[0];
	
	XSI::Primitive	myPrimitive( l_cref );

	if ( !myPrimitive.IsValid() )
	{
		//
		// perhaps it's a X3DObject
		//
		
		XSI::X3DObject	myx3DObject ( l_cref );

		if ( !myx3DObject.IsValid() )
			return myMesh;


		myPrimitive = myx3DObject.GetActivePrimitive();

	}

	assert ( myPrimitive.IsValid() );

	if ( !myPrimitive.IsValid() )
		return myMesh;

	myMesh = myPrimitive.GetGeometry();

	return myMesh;


}

void	CVertexColorOperator::Activate ( BOOL in_bActivate )
{
	MoveWindow ( m_hwnd, 250,80,300,300,TRUE );
}

void	CVertexColorOperator::AddInteractiveTask ( XSI::ClusterProperty in_prop, CVertexColorOperator* in_op )
{
	InteractiveTask*	l_ptask = new InteractiveTask;

	l_ptask->m_ClusterProp = in_prop;
	l_ptask->m_pOperator = in_op;
	l_ptask->m_x3d = GetSelectedX3DObject();
	l_ptask->m_PolygonMesh = GetSelectedPolygonMesh();
	
	m_pTasks.Extend(1);
	m_pTasks[m_pTasks.GetUsed()-1] = l_ptask;

}
