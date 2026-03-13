//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

#include "QuadMesh.h"



QuadMesh::~QuadMesh(void)
{
}

QuadMesh::QuadMesh(void)
{

}


void QuadMesh::render(LONG id, LONG iLayoutType) const
{


	id = abs(id % (iLayoutType*2));

	float baseUV = 1.0f / iLayoutType;
	float offsetU = 0;
	float offsetV = 0;

	offsetU = (id % iLayoutType) * baseUV;
	offsetV = (id / iLayoutType) * baseUV;

	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(baseUV + offsetU, baseUV + offsetV); 
	glVertex3f( 0.5f, 0.0f, 0.5f );

	glTexCoord2f(offsetU, baseUV + offsetV); 
	glVertex3f( -0.5f, 0.0f, 0.5f );

	glTexCoord2f(baseUV + offsetU, offsetV); 
	glVertex3f( 0.5f, 0.0f, -0.5f );

	glTexCoord2f(offsetU, offsetV); 
	glVertex3f( -0.5f, 0.0f, -0.5f );
	glEnd();



}

void QuadMesh::setState(OGLParticleAttributeData* in_pAttributes) const
{}

void QuadMesh::unsetState(OGLParticleAttributeData* in_pAttributes) const
{}
