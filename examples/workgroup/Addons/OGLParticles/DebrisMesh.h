//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

#pragma once
#include "Mesh.h"

class DebrisMesh :
	public Mesh
{
public:
	DebrisMesh(void);
public:
	virtual ~DebrisMesh(void);

	virtual void render(LONG id, LONG iLayoutType) const;
	virtual void setState(OGLParticleAttributeData* in_pAttributes) const;
	virtual void unsetState(OGLParticleAttributeData* in_pAttributes) const;

	std::vector<Vertex>         *mDebrisVertices;
	std::vector<unsigned short> *mDebrisIndices;
	unsigned int                *mDebrisVerticesVBO;
	unsigned int                *mDebrisIndicesVBO;
	unsigned int                *mDebrisTexture;
	int							m_iCurrentMesh;
};
