//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

#include "CubeMesh.h"

#include <assert.h>
#include <math.h>

CubeMesh::CubeMesh()
{
    
	int index_list[36];
	float fCubeSize = 0.1f;

	Vertex vertices[] = {
		{{-fCubeSize, fCubeSize,-fCubeSize}, {0.0f, 0.0f,-1.0f}, {0.01f, 0.01f}}, 
		{{fCubeSize, fCubeSize,-fCubeSize}, {0.0f, 0.0f,-1.0f}, {0.99f, 0.01f}}, 
		{{fCubeSize,-fCubeSize,-fCubeSize}, {0.0f, 0.0f,-1.0f}, {0.99f, 0.99f}},
		{{-fCubeSize,-fCubeSize,-fCubeSize}, {0.0f, 0.0f,-1.0f}, {0.01f, 0.99f}},

    // Back face
		{{-fCubeSize, fCubeSize, fCubeSize}, {0.0f, 0.0f,1.0f}, {0.99f, 0.01f}},
		{{-fCubeSize,-fCubeSize, fCubeSize}, {0.0f, 0.0f,1.0f}, {0.99f, 0.99f}},
		{{fCubeSize,-fCubeSize, fCubeSize}, {0.0f, 0.0f,1.0f}, {0.01f, 0.99f}},
		{{fCubeSize, fCubeSize, fCubeSize}, {0.0f, 0.0f,1.0f}, {0.01f, 0.01f}},

    // Top face
		{{-fCubeSize, fCubeSize, fCubeSize}, {0.0f, 1.0f,0.0f}, {0.01f, 0.01f}},
		{{fCubeSize, fCubeSize, fCubeSize}, {0.0f, 1.0f,0.0f}, {0.99f, 0.01f}},
		{{fCubeSize, fCubeSize,-fCubeSize}, {0.0f, 1.0f,0.0f}, {0.99f, 0.99f}},
		{{-fCubeSize, fCubeSize,-fCubeSize}, {0.0f, 1.0f,0.0f}, {0.01f, 0.99f}},

    // Bottom face
		{{-fCubeSize,-fCubeSize, fCubeSize}, {0.0f,-1.0f,0.0f}, {0.01f, 0.99f}},
		{{-fCubeSize,-fCubeSize,-fCubeSize}, {0.0f,-1.0f,0.0f}, {0.01f, 0.01f}},
		{{fCubeSize,-fCubeSize,-fCubeSize}, {0.0f,-1.0f,0.0f}, {0.99f, 0.01f}},
		{{fCubeSize,-fCubeSize, fCubeSize}, {0.0f,-1.0f,0.0f}, {0.99f, 0.99f}},

    // Right face
		{{fCubeSize, fCubeSize,-fCubeSize}, {1.0f,0.0f,0.0f}, {0.01f, 0.01f}},
		{{fCubeSize, fCubeSize, fCubeSize}, {1.0f,0.0f,0.0f}, {0.99f, 0.01f}},
		{{fCubeSize,-fCubeSize, fCubeSize}, {1.0f,0.0f,0.0f}, {0.99f, 0.99f}},
		{{fCubeSize,-fCubeSize,-fCubeSize}, {1.0f,0.0f,0.0f}, {0.01f, 0.99f}}, 

    // Left face
		{{-fCubeSize, fCubeSize,-fCubeSize}, {-1.0f,0.0f,0.0f}, {0.99f, 0.01f}},
		{{-fCubeSize,-fCubeSize,-fCubeSize}, {-1.0f,0.0f,0.0f}, {0.99f, 0.99f}},
		{{-fCubeSize,-fCubeSize, fCubeSize}, {-1.0f,0.0f,0.0f}, {0.01f, 0.99f}},
		{{-fCubeSize, fCubeSize, fCubeSize}, {-1.0f,0.0f,0.0f}, {0.01f, 0.01f}}};


    // Set up the indices for the cube
    index_list[0] =  0+0;   index_list[1] =  0+1;   index_list[2] =  0+2;
    index_list[3] =  0+2;   index_list[4] =  0+3;   index_list[5] =  0+0;

    index_list[6] =  4+0;   index_list[7] =  4+1;   index_list[8] =  4+2;
    index_list[9] =  4+2;   index_list[10] =  4+3;  index_list[11] =  4+0;

    index_list[12] =  8+0;  index_list[13] =  8+1;  index_list[14] =  8+2;
    index_list[15] =  8+2;  index_list[16] =  8+3;  index_list[17] =  8+0;

    index_list[18] = 12+0;  index_list[19] = 12+1;  index_list[20] = 12+2;
    index_list[21] = 12+2;  index_list[22] = 12+3;  index_list[23] = 12+0;

    index_list[24] = 16+0;  index_list[25] = 16+1;  index_list[26] = 16+2;
    index_list[27] = 16+2;  index_list[28] = 16+3;  index_list[29] = 16+0;
    index_list[30] = 20+0;  index_list[31] = 20+1;  index_list[32] = 20+2;
    index_list[33] = 20+2;  index_list[34] = 20+3;  index_list[35] = 20+0;

	int i;
	for(i=0; i<24; i++)
	{
		mVertices.push_back(vertices[i]);
	}

	for(i=0; i<36; i++)
	{
		mIndices.push_back(index_list[i]);
	}

	UploadVBO();
}
