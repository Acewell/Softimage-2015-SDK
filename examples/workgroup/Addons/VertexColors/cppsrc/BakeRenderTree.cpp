// BakeRenderTree.cpp: implementation of the BakeRenderTree class.
//
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BakeRenderTree.h"

#include <assert.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BakeRenderTree::BakeRenderTree()
{

}

BakeRenderTree::~BakeRenderTree()
{

}

int		BakeRenderTree::Run( XSI::CRefArray in_RefArray )
{
	using namespace XSI;

	X3DObject		x3d = GetSelectedX3DObject();

	assert ( x3d.IsValid() );

	CValueArray args(1);

	args[0] = CValue(L"RenderMap");
	CValue retVal;
	Application app;
    app.ExecuteCommand( L"AddProp", args, retVal );

	args.Resize(2);

	CString	obj_name = x3d.GetFullName();
	obj_name += L".RenderMap.maptype";

	args[0] = CValue(obj_name.GetWideString ());
	args[1] = 1l;
	app.ExecuteCommand( L"SetValue", args, retVal ) ;

	
	obj_name = x3d.GetFullName();
	obj_name += L".RenderMap.vertaveraging";

	args[0] = CValue(obj_name.GetWideString ());
	args[1] = true;
	app.ExecuteCommand( L"SetValue", args, retVal ) ;


	XSI::PolygonMesh	mesh = GetSelectedPolygonMesh();

	XSI::ClusterProperty cav;;
	cav = mesh.AddVertexColor();
	cav.PutName ( L"BakedRenderTreeResult" );

	args.Resize(3);

	obj_name = x3d.GetFullName();
	obj_name += L".RenderMap.cav";

	args[0] = CValue();	// default
	args[1] = CValue(obj_name.GetWideString ());
	args[2] = CValue(cav.GetName());
		
	app.ExecuteCommand( L"SetInstanceDataValue", args, retVal ) ;

	args.Resize(1);
	obj_name = x3d.GetFullName();
	obj_name += L".RenderMap";
	
	args[0] = CValue(obj_name.GetWideString ());
	app.ExecuteCommand( L"RegenerateMaps", args, retVal ) ;

	app.ExecuteCommand( L"DeleteObj", args, retVal ) ;

	mesh.PutCurrentVertexColor(cav);

	return 0;

}

void	BakeRenderTree::Activate ( BOOL )
{

}

