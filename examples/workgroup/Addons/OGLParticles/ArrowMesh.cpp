//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

#include "ArrowMesh.h"

ArrowMesh::ArrowMesh(void)
{
	float fRelSize = 0.1f;

	Vertex vertices[] = {
		{{2.000000,-0.000000,0.000000}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
		{{0.000000,-0.000000,-3.000000}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
		{{-2.000000,-0.000000,0.000000}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
		{{-1.000000,-0.000000,0.000000}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
		{{-1.000000,-0.000000,3.000000}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
		{{1.000000,-0.000000,3.000000}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
		{{1.000000,-0.000000,0.000000}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}}};

	// filled arrow (triangles
	/*
	mIndices.push_back(4);
	mIndices.push_back(5);
	mIndices.push_back(6);
	mIndices.push_back(6);
	mIndices.push_back(0);
	mIndices.push_back(1);
	mIndices.push_back(1);
	mIndices.push_back(2);
	mIndices.push_back(3);
	mIndices.push_back(1);
	mIndices.push_back(3);
	mIndices.push_back(4);
	mIndices.push_back(1);
	mIndices.push_back(4);
	mIndices.push_back(6);
	*/

	// line loop
	mIndices.push_back(0);
	mIndices.push_back(1);
	mIndices.push_back(2);
	mIndices.push_back(3);
	mIndices.push_back(4);
	mIndices.push_back(5);
	mIndices.push_back(6);
	int i;
	for(i=0; i<7; i++)
	{
		vertices[i].mPosition[0] *= fRelSize;
		vertices[i].mPosition[1] *= fRelSize;
		vertices[i].mPosition[2] *= fRelSize;
		
		mVertices.push_back(vertices[i]);
	}
	UploadVBO();
}

void ArrowMesh::render(LONG id, LONG iLayoutType) const
{
	if ( sUseVBO )
	{
		glDrawElements(GL_LINE_LOOP, (GLsizei)mIndices.size(), GL_UNSIGNED_SHORT, 0);
	} else {
		glDrawElements(GL_LINE_LOOP, (GLsizei)mIndices.size(), GL_UNSIGNED_SHORT,  &mIndices[0]);
	}
}
ArrowMesh::~ArrowMesh(void)
{
}
