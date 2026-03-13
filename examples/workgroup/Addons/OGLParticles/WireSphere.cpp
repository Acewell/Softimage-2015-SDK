//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

#include "WireSphere.h"

#include <assert.h>
#include <math.h>

static const float PI = 3.14159265358979f;
static const int gSpherePnts = 12;

extern PFNGLBINDBUFFERARBPROC glBindBufferARB ;
extern PFNGLBUFFERDATAARBPROC glBufferDataARB ;
extern PFNGLGENBUFFERSARBPROC glGenBuffersARB ;


WireSphereMesh::WireSphereMesh()
{
	Vertex vertices[ gSpherePnts ];

	// Pre-calculate the circle points
	for( UINT j = 0; j < gSpherePnts; j++ ) {
		vertices[ j ].mPosition[0] = (float)cos( ( j / (double)gSpherePnts ) * 2.0 * PI ) * 0.2f;
		vertices[ j ].mPosition[1] = (float)sin( ( j / (double)gSpherePnts ) * 2.0 * PI ) * 0.2f;
	}
	
	UINT l;
	unsigned short index=0;
	unsigned short sindex =0;
	for( l = 0; l < gSpherePnts; l++ ) 
	{
		Vertex v;
		v.mPosition[0] = vertices[ l ].mPosition[0];
		v.mPosition[1] = vertices[ l ].mPosition[1];
		v.mPosition[2] = 0.0f;
		mVertices.push_back(v);
		mIndices.push_back(index++);
	}

	mIndices.push_back(sindex);
	
	
	sindex=index;
	for( l = 0; l < gSpherePnts; l++ ) 
	{
		Vertex v;
		v.mPosition[0] = vertices[ l ].mPosition[0];
		v.mPosition[1] = 0.0f;
		v.mPosition[2] = vertices[ l ].mPosition[1];
		mVertices.push_back(v);
		mIndices.push_back(index++);
	}
	mIndices.push_back(sindex);
	sindex=index;
	
	UploadVBO();

}

void WireSphereMesh::render(LONG id, LONG iLayoutType) const
{
	glDisable (GL_TEXTURE_2D);
	if ( sUseVBO )
	{
		glDrawElements(GL_LINE_LOOP, (GLsizei)mIndices.size(), GL_UNSIGNED_SHORT, 0);
	} else {
		glDrawElements(GL_LINE_LOOP, (GLsizei)mIndices.size(), GL_UNSIGNED_SHORT,  &mIndices[0]);
	}
}

void WireSphereMesh::setState(VOID*  in_pGeometry) const
{

	assert(0);
	/*
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, mVerticesVBO);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, mIndicesVBO);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (void*)0);
	glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)12);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (void*)24);



	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	*/
}

void WireSphereMesh::unsetState(VOID*  in_pGeometry) const
{
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	if ( sUseVBO )
	{
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
	}

}