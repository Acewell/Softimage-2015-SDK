//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

#include "DebrisMesh.h"
#include <assert.h>
#include <math.h>

extern PFNGLBINDBUFFERARBPROC glBindBufferARB ;
extern PFNGLBUFFERDATAARBPROC glBufferDataARB ;
extern PFNGLGENBUFFERSARBPROC glGenBuffersARB ;
extern PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;


#define NUM_DEBRIS_MESH	4

Vec3* gMeshPositions[NUM_DEBRIS_MESH];
Vec3* gMeshNormals[NUM_DEBRIS_MESH];
Vec2* gMeshUV[NUM_DEBRIS_MESH];
Triangle* gPositionIndices[NUM_DEBRIS_MESH];
Triangle* gNormalIndices[NUM_DEBRIS_MESH];
Triangle* gUVIndices[NUM_DEBRIS_MESH];
int TriangleCount[NUM_DEBRIS_MESH];

Vec3 debris1_positions[] = {
			0.000873,-0.582382,-0.000250,
			0.000873,0.584538,-0.000250,
			-0.564040,0.001078,-0.000250,
			0.283330,0.001078,0.488980,
			0.283330,0.001078,-0.489479 };
Vec3 debris1_normals[] = {
			-0.500000,0.000000,0.866025,
			-0.500000,0.000000,0.866025,
			-0.450038,-0.435733,0.779489,
			-0.500000,0.000000,0.866025,
			-0.500000,0.000000,0.866025,
			-0.450038,0.435733,0.779489,
			1.000000,0.000000,0.000000,
			1.000000,0.000000,0.000000,
			0.900076,-0.435733,0.000000,
			1.000000,0.000000,0.000000,
			1.000000,0.000000,0.000000,
			0.900076,0.435733,0.000000,
			-0.500000,0.000000,-0.866025,
			-0.500000,0.000000,-0.866025,
			-0.450038,-0.435733,-0.779489,
			-0.500000,0.000000,-0.866025,
			-0.500000,0.000000,-0.866025,
			-0.450038,0.435733,-0.779489 };

			Vec2	debris1_uv[] = {
			0.613593,0.500000,
			0.250000,0.500000,
			0.750000,0.077979,
			0.250000,0.500000,
			0.613593,0.500000,
			0.750000,0.922021,
			0.886407,0.500000,
			0.613593,0.500000,
			0.750000,0.077979,
			0.613593,0.500000,
			0.886407,0.500000,
			0.750000,0.922021,
			0.250000,0.500000,
			-0.113593,0.500000,
			-0.250000,0.077979,
			0.886407,0.500000,
			1.250000,0.500000,
			0.750000,0.922021 };

			Triangle debris1_pos_indices[] = {
			3,2,0,
			2,3,1,
			4,3,0,
			3,4,1,
			2,4,0,
			4,2,1};

			Triangle debris1_nrm_indices[] = {
			0,1,2,
			3,4,5,
			6,7,8,
			9,10,11,
			12,13,14,
			15,16,17};

			Triangle debris1_uv_indices[] = {
			0,1,2,
			3,4,5,
			6,7,8,
			9,10,11,
			12,13,14,
			15,16,17};

Vec3 debris2_positions[] = {
			0.000873,-0.241122,-0.000250,
			0.000873,0.212072,-0.000250,
			-0.350882,0.001078,-0.061435,
			-0.002949,0.001078,0.438919,
			0.283330,0.001078,-0.489479};
Vec3 debris2_normals[] = {
			-0.566736,-0.723533,0.394094,
			-0.551200,-0.827509,-0.106809,
			-0.551200,-0.827509,-0.106809,
			-0.499458,0.860864,-0.097237,
			-0.524776,0.769055,0.364916,
			-0.499458,0.860864,-0.097237,
			0.955190,0.029285,0.294541,
			0.955190,0.029285,0.294541,
			0.848094,-0.460810,0.261517,
			0.955190,0.029285,0.294541,
			0.955190,0.029285,0.294541,
			0.820859,0.511978,0.253119,
			-0.551200,-0.827509,-0.106809,
			-0.391274,-0.714714,-0.579732,
			-0.551200,-0.827509,-0.106809,
			-0.362932,0.760997,-0.537740,
			-0.499458,0.860864,-0.097237,
			-0.499458,0.860864,-0.097237};

Vec2 debris2_uv[] = {
			0.613593,0.500000,
			0.250000,0.500000,
			0.750000,0.077979,
			0.250000,0.500000,
			0.613593,0.500000,
			0.750000,0.922021,
			0.886407,0.500000,
			0.613593,0.500000,
			0.750000,0.077979,
			0.613593,0.500000,
			0.886407,0.500000,
			0.750000,0.922021,
			0.250000,0.500000,
			-0.113593,0.500000,
			-0.250000,0.077979,
			0.886407,0.500000,
			1.250000,0.500000,
			0.750000,0.922021};

Triangle debris2_pos_indices[] = {
			3,2,0,
			2,3,1,
			4,3,0,
			3,4,1,
			2,4,0,
			4,2,1};

Triangle debris2_nrm_indices[] = {
			0,1,2,
			3,4,5,
			6,7,8,
			9,10,11,
			12,13,14,
			15,16,17};

Triangle debris2_uv_indices[] = {
			0,1,2,
			3,4,5,
			6,7,8,
			9,10,11,
			12,13,14,
			15,16,17};


Vec3 debris3_positions[] = {
			0.000873,-0.241122,-0.000250,
			0.149792,0.019512,-0.063739,
			-0.346618,0.001078,-0.135389,
			-0.002949,0.001078,0.438919,
			0.298711,0.001078,-0.132355,
			-0.156555,0.029420,-0.058910,
			-0.000649,0.040962,0.177252};

Vec3 debris3_normals[] = {
			-0.623790,-0.686693,0.373280,
			-0.623790,-0.686693,0.373280,
			-0.623790,-0.686693,0.373280,
			-0.110493,0.989274,-0.095538,
			0.008857,0.992791,0.119532,
			0.095698,0.991161,-0.091877,
			0.679528,-0.639912,0.358824,
			0.679528,-0.639912,0.358824,
			0.679528,-0.639912,0.358824,
			0.008857,0.992791,0.119532,
			0.128755,0.986278,-0.103333,
			0.016495,0.998314,0.055645,
			0.004117,-0.482735,-0.875757,
			0.004117,-0.482735,-0.875757,
			0.004117,-0.482735,-0.875757,
			0.128755,0.986278,-0.103333,
			-0.110493,0.989274,-0.095538,
			-0.062435,0.994266,-0.086812,
			-0.062435,0.994266,-0.086812,
			-0.062435,0.994266,-0.086812,
			0.016495,0.998314,0.055645,
			0.016495,0.998314,0.055645,
			0.095698,0.991161,-0.091877,
			0.095698,0.991161,-0.091877};

Vec2 debris3_uv[] = {
			0.613593,0.500000,
			0.250000,0.500000,
			0.750000,0.077979,
			0.250000,0.500000,
			0.613593,0.500000,
			0.818204,0.711010,
			0.886407,0.500000,
			0.613593,0.500000,
			0.750000,0.077979,
			0.613593,0.500000,
			0.886407,0.500000,
			0.695664,0.753914,
			0.250000,0.500000,
			-0.113593,0.500000,
			-0.250000,0.077979,
			0.886407,0.500000,
			1.250000,0.500000,
			0.523479,0.730827,
			0.523479,0.730827,
			0.976521,0.730827,
			0.695664,0.753914,
			0.695664,0.753914,
			0.818204,0.711010,
			0.818204,0.711010};


Triangle debris3_pos_indices[] = {
			3,2,0,
			2,3,6,
			2,6,5,
			4,3,0,
			3,4,1,
			3,1,6,
			2,4,0,
			4,2,5,
			4,5,1,
			5,6,1};

Triangle debris3_nrm_indices[] = {
			0,1,2,
			3,4,20,
			3,20,18,
			6,7,8,
			9,10,22,
			9,22,21,
			12,13,14,
			15,16,19,
			15,19,23,
			17,11,5};

Triangle debris3_uv_indices[] = {
			0,1,2,
			3,4,20,
			3,20,18,
			6,7,8,
			9,10,22,
			9,22,21,
			12,13,14,
			15,16,19,
			15,19,23,
			17,11,5};


Vec3 debris4_positions[] = {
			0.000873,-0.241122,-0.000250,
			0.149792,0.215988,-0.063739,
			-0.346618,0.001078,-0.135389,
			-0.002949,0.001078,0.304830,
			0.298711,0.001078,-0.132355,
			-0.156555,0.225896,-0.058910,
			-0.000649,0.237438,0.177252,
			-0.321328,-0.120022,-0.067819,
			-0.149493,-0.120022,0.219335};

Vec3 debris4_normals[] = {
			-0.757894,0.358345,0.545147,
			-0.757894,0.358345,0.545147,
			-0.384281,-0.894119,0.229956,
			-0.757894,0.358345,0.545147,
			-0.757894,0.358345,0.545147,
			0.031155,0.997109,-0.069301,
			0.785398,-0.179611,0.592360,
			0.785398,-0.179611,0.592360,
			0.574865,-0.637327,0.513171,
			0.785398,-0.179611,0.592360,
			0.785398,-0.179611,0.592360,
			0.031155,0.997109,-0.069301,
			0.002627,-0.092945,-0.995668,
			0.002627,-0.092945,-0.995668,
			0.003346,-0.483583,-0.875292,
			0.002627,-0.092945,-0.995668,
			0.002627,-0.092945,-0.995668,
			0.031155,0.997109,-0.069301,
			-0.749308,0.373162,0.547072,
			0.001470,0.313224,-0.949678,
			-0.749308,0.373162,0.547072,
			0.791650,0.324822,0.517476,
			0.791650,0.324822,0.517476,
			0.001470,0.313224,-0.949678,
			-0.766255,0.343422,0.543060,
			0.003346,-0.483583,-0.875292,
			-0.766255,0.343422,0.543060,
			0.574865,-0.637327,0.513171,
			-0.384281,-0.894119,0.229956,
			-0.384281,-0.894119,0.229956};

Vec2 debris4_uv[] = {
			0.613593,0.500000,
			0.250000,0.500000,
			0.750000,0.077979,
			0.250000,0.500000,
			0.613593,0.500000,
			0.818204,0.711010,
			0.886407,0.500000,
			0.613593,0.500000,
			0.750000,0.077979,
			0.613593,0.500000,
			0.886407,0.500000,
			0.695664,0.753914,
			0.250000,0.500000,
			-0.113593,0.500000,
			-0.250000,0.077979,
			0.886407,0.500000,
			1.250000,0.500000,
			0.523479,0.730827,
			0.523479,0.730827,
			0.976521,0.730827,
			0.695664,0.753914,
			0.695664,0.753914,
			0.818204,0.711010,
			0.818204,0.711010,
			0.500000,0.288990,
			0.000000,0.288990,
			0.681796,0.288990,
			0.681796,0.288990,
			0.500000,0.288990,
			0.681796,0.288990};

Triangle debris4_pos_indices[] = {
			3,2,7,
			3,7,8,
			2,3,6,
			2,6,5,
			4,3,8,
			4,8,0,
			3,4,1,
			3,1,6,
			2,4,0,
			2,0,7,
			4,2,5,
			4,5,1,
			5,6,1,
			0,8,7};

Triangle debris4_nrm_indices[] = {
			0,1,24,
			0,24,26,
			3,4,20,
			3,20,18,
			6,7,27,
			6,27,8,
			9,10,22,
			9,22,21,
			12,13,14,
			12,14,25,
			15,16,19,
			15,19,23,
			17,11,5,
			2,29,28};

Triangle debris4_uv_indices[] = {
			0,1,24,
			0,24,26,
			3,4,20,
			3,20,18,
			6,7,27,
			6,27,8,
			9,10,22,
			9,22,21,
			12,13,14,
			12,14,25,
			15,16,19,
			15,19,23,
			17,11,5,
			2,29,28};





DebrisMesh::~DebrisMesh()
{
	if ( mDebrisVertices != NULL )
		delete [] mDebrisVertices ;

	if ( mDebrisIndices != NULL )
		delete [] mDebrisIndices ;

	if ( mDebrisVerticesVBO != NULL )
		delete [] mDebrisVerticesVBO ;

	if ( mDebrisIndicesVBO != NULL )
		delete [] mDebrisIndicesVBO ;

	if ( mDebrisTexture != NULL )
		delete [] mDebrisTexture;

	glDeleteBuffersARB(NUM_DEBRIS_MESH, mDebrisVerticesVBO);
}

DebrisMesh::DebrisMesh()
:mDebrisVertices(NULL)
,mDebrisIndices(NULL)
,mDebrisVerticesVBO(NULL)
,mDebrisIndicesVBO(NULL)
,mDebrisTexture(NULL)
,m_iCurrentMesh (0)
{
	
	gMeshPositions[0]	= debris1_positions;
	gMeshNormals[0]		= debris1_normals;
	gMeshUV[0]			= debris1_uv;
	gPositionIndices[0] = debris1_pos_indices;
	gNormalIndices[0]	= debris1_nrm_indices;
	gUVIndices[0]		= debris1_uv_indices;

	gMeshPositions[1]	= debris2_positions;
	gMeshNormals[1]		= debris2_normals;
	gMeshUV[1]			= debris2_uv;
	gPositionIndices[1] = debris2_pos_indices;
	gNormalIndices[1]	= debris2_nrm_indices;
	gUVIndices[1]		= debris2_uv_indices;

	gMeshPositions[2]	= debris3_positions;
	gMeshNormals[2]		= debris3_normals;
	gMeshUV[2]			= debris3_uv;
	gPositionIndices[2] = debris3_pos_indices;
	gNormalIndices[2]	= debris3_nrm_indices;
	gUVIndices[2]		= debris3_uv_indices;

	gMeshPositions[3]	= debris4_positions;
	gMeshNormals[3]= debris4_normals;
	gMeshUV[3]			= debris4_uv;
	gPositionIndices[3] = debris4_pos_indices;
	gNormalIndices[3]	= debris4_nrm_indices;
	gUVIndices[3]		= debris4_uv_indices;

	TriangleCount[0] = 6;
	TriangleCount[1] = 6;
	TriangleCount[2] = 10;
	TriangleCount[3] = 14;

	// allocate
	mDebrisVertices = new std::vector<Vertex>[ NUM_DEBRIS_MESH ];
	mDebrisVerticesVBO = new unsigned int [ NUM_DEBRIS_MESH ];


	

	for (int m=0;m<NUM_DEBRIS_MESH;m++)
	{
		std::vector<Vertex>         flatten;
		int i=0;
		for (int t=0;t<TriangleCount[m];t++)
		{
			for (int f=0;f<3;f++)
			{
				int pi0 = gPositionIndices[m][t].i[f];
				int ni0 = gNormalIndices[m][t].i[f];
				int ti0 = gUVIndices[m][t].i[f];

				Vertex v;
				v.mPosition[0] = (float)gMeshPositions[m][pi0].p[0];
				v.mPosition[1] = (float)gMeshPositions[m][pi0].p[1];
				v.mPosition[2] = (float)gMeshPositions[m][pi0].p[2];
				v.mNormal[0] = (float)gMeshNormals[m][ni0].p[0];
				v.mNormal[1] = (float)gMeshNormals[m][ni0].p[1];
				v.mNormal[2] = (float)gMeshNormals[m][ni0].p[2];
				v.mTextureCoord0[0] = (float)gMeshUV[m][ti0].p[0];
				v.mTextureCoord0[1] = (float)gMeshUV[m][ti0].p[1];
				mDebrisVertices[m].push_back ( v );
			}
		}

		// make vbo
		// Create the VBOs
		
		if ( sUseVBO )
		{
			glGenBuffersARB(1, &mDebrisVerticesVBO[m]);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, mDebrisVerticesVBO[m]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, mDebrisVertices[m].size() * sizeof(mDebrisVertices[m][0]), &(mDebrisVertices[m][0]), GL_STATIC_DRAW_ARB);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
		}


	}
}

void DebrisMesh::render(LONG id, LONG iLayoutType) const
{
	id = id % NUM_DEBRIS_MESH;

	if ( sUseVBO )
	{
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, mDebrisVerticesVBO[id]);
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (void*)0);
		glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)12);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (void*)24);
	} else {

		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &mDebrisVertices[id][0]);
		glNormalPointer(GL_FLOAT, sizeof(Vertex), &mDebrisVertices[id][0].mNormal[0]);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &mDebrisVertices[id][0].mTextureCoord0[0]);
	}

	glDrawArrays ( GL_TRIANGLES, 0, mDebrisVertices[id].size()  );
	
}

void DebrisMesh::setState(OGLParticleAttributeData* in_pAttributes) const
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

}

void DebrisMesh::unsetState(OGLParticleAttributeData* in_pAttributes) const
{
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	if ( sUseVBO )
	{
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	}
}



