// VertexColorOperator.h: interface for the CVertexColorOperator class.
//
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VERTEXCOLOROPERATOR_H__55B6023B_FB7A_4C99_BAA5_546BEFCCFAAF__INCLUDED_)
#define AFX_VERTEXCOLOROPERATOR_H__55B6023B_FB7A_4C99_BAA5_546BEFCCFAAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>

#include "resource.h"

#include <SIBCArray.h>

#include <xsi_ref.h>
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

class CVertexColorOperator;

typedef struct tagInteractiveTask
{
	XSI::ClusterProperty	m_ClusterProp;
	XSI::PolygonMesh		m_PolygonMesh;
	XSI::X3DObject			m_x3d;
	CVertexColorOperator*	m_pOperator;

} InteractiveTask;

class CVertexColorOperator  
{
public:
	CVertexColorOperator();
	virtual ~CVertexColorOperator();

	virtual	char*	GetName() { return NULL; };
	virtual int		GetNumRequiredProperties() { return 0; };
	virtual int		Run( XSI::CRefArray in_RefArray ) { return 0; };
	virtual void	Activate ( BOOL );
	virtual int		DoInteractive( InteractiveTask* ) { return 0; };

	virtual void	AddInteractiveTask ( XSI::ClusterProperty in_prop, CVertexColorOperator* in_op );

	void	SetParent ( HWND in_hParent );

	CSIBCArray<InteractiveTask*>&	GetTaskList() { return m_pTasks; };

	XSI::PolygonMesh	GetSelectedPolygonMesh();
	XSI::X3DObject		GetSelectedX3DObject();

	HWND	m_hwnd;

	HWND	m_hParent;

	static CSIBCArray<InteractiveTask*>	m_pTasks;
	
};

#endif // !defined(AFX_VERTEXCOLOROPERATOR_H__55B6023B_FB7A_4C99_BAA5_546BEFCCFAAF__INCLUDED_)
