//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

#if defined(_WIN32)
#  include <windows.h>
#endif

#include "SphereMesh.h"

#include <assert.h>
#include <math.h>

static const float PI = 3.14159265358979f;

extern PFNGLBINDBUFFERARBPROC glBindBufferARB ;
extern PFNGLBUFFERDATAARBPROC glBufferDataARB ;
extern PFNGLGENBUFFERSARBPROC glGenBuffersARB ;

SphereMesh::SphereMesh(int rows, int columns)
{
  assert(rows > 0);
  assert(columns > 0);

  int    i, j;
  float  theta, phi;
  Vertex v;

  if((rows == 2) && (columns == 2))
    {
      Vertex vertices[] = {{{-0.2f, -0.2f, 0.0f}, {0.0f, 0.0f,  1.0f}, {0.0f, 0.0f}},
                           {{ 0.2f, -0.2f, 0.0f}, {0.0f, 0.0f,  1.0f}, {1.0f, 0.0f}},
                           {{ 0.0f,  0.2f, 0.0f}, {0.0f, 0.0f,  1.0f}, {0.2f, 1.0f}},
                           {{-0.2f, -0.2f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
                           {{ 0.0f,  0.2f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.2f, 1.0f}},
                           {{ 0.2f, -0.2f, 0.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}}};
      int indices[] = {0, 1, 2, 3, 4, 5};

      for(i=0; i<6; i++)
        {
          mVertices.push_back(vertices[i]);
        }

      for(i=0; i<6; i++)
        {
          mIndices.push_back(indices[i]);
        }

    }
  else
    {
      // Create the vertices
      for(i=0; i<rows; i++)
        {
          phi = (-PI / 2.0f) + (float(i) / float(rows - 1)) * PI;

          for(j=0; j<columns; j++)
            {
              theta = float(j) / float(columns - 1) * 2.0f * PI; 

              v.mPosition[0] = cos(phi) * cos(theta) * 0.2f;
              v.mPosition[1] = cos(phi) * sin(theta) * 0.2f;
              v.mPosition[2] = sin(phi) * 0.2f;

              v.mNormal[0] = v.mPosition[0];
              v.mNormal[1] = v.mPosition[1];
              v.mNormal[2] = v.mPosition[2];

              v.mTextureCoord0[0] = ((float)j / (columns - 1));
              v.mTextureCoord0[1] = ((float)i / (rows - 1));
          
              mVertices.push_back(v);
            }
        }

      // Create the indices
      for(i=0; i<(rows - 1); i++)
        {
          for(j=0; j<(columns - 1); j++)
            {
              mIndices.push_back((j + 0) + (i + 0) * columns);
              mIndices.push_back((j + 1) + (i + 0) * columns);
              mIndices.push_back((j + 1) + (i + 1) * columns);

              mIndices.push_back((j + 0) + (i + 0) * columns);
              mIndices.push_back((j + 1) + (i + 1) * columns);
              mIndices.push_back((j + 0) + (i + 1) * columns);
            }
        }
    }

	UploadVBO();

}
