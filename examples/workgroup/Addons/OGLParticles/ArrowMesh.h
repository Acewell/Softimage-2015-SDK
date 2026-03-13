//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

#pragma once
#include "Mesh.h"

class ArrowMesh :
	public Mesh
{
public:
	ArrowMesh(void);
public:
	virtual ~ArrowMesh(void);

	virtual void render(LONG id, LONG iLayoutType) const;
};
