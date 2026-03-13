//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

#pragma once
#include "Mesh.h"

class QuadMesh :
	public Mesh
{
public:
	QuadMesh(void);
public:
	virtual ~QuadMesh(void);
	
	virtual void render(LONG id, LONG iLayoutType) const;
	virtual void setState(OGLParticleAttributeData* in_pAttributes) const;
	virtual void unsetState(OGLParticleAttributeData* in_pAttributes) const;
};
 