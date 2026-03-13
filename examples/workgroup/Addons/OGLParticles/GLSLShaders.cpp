//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

#include "GLSLShaders.h"

const char *gShaders[] = {
	// GLSL Pseudo Instancing Shader.
	// Pseudo instancing is a relatively new approach to rendering
	// large amounts of primitives. The idea is to eliminate expensive
	// calls to glMultMatrix, glTranslate, etc by instead passing
	// particles attributes using texture coordinates.
	// Calling glMultiTexCoord is very cheap.
	// The particle is then positions, colored, stretched ,etc on the GPU
"uniform float velocityStretch;						\n"
"void main(void)									\n"
"{													\n"
"vec4 positionWorld;								\n"
"mat4 orientationMat = mat4(1.0);					\n"
"vec3 zaxis = -gl_MultiTexCoord2.xyz;				\n"
"mat4 VelocityMatrix = mat4(1.0);					\n"
"if ( velocityStretch > 0.0 )						\n"
"{													\n"
"	float pVelocity = length(zaxis);				\n"
"	pVelocity = clamp(pVelocity,1.0, 25.0);			\n"
"	VelocityMatrix[2][2]= pVelocity * velocityStretch;	\n"
"}													\n"
"	if ( length(zaxis) < 0.00001 )						\n"
"		zaxis = vec3(0.0,1.0,0.0);					\n"
"	zaxis = normalize(zaxis);						\n"
"vec3 upvector = vec3(0.0, 1.0,0.0);				\n"
"vec3 xaxis = cross( upvector,zaxis );		\n"
"if (length(xaxis)< 0.000001)						\n"
"{													\n"
"	xaxis = cross( vec3(1.0,0.0,0.0),zaxis );		\n"
"}													\n"
"vec3 yaxis = cross( zaxis, xaxis );				\n"
"xaxis = normalize(xaxis);							\n"
"yaxis = normalize(yaxis);							\n"
"orientationMat[0][0] = xaxis.x;					\n"
"orientationMat[1][0] = xaxis.y;					\n"
"orientationMat[2][0] = xaxis.z;					\n"
"orientationMat[3][0] = 0.0;						\n"
"orientationMat[0][1] = yaxis.x;					\n"
"orientationMat[1][1] = yaxis.y;					\n"
"orientationMat[2][1] = yaxis.z;					\n"
"orientationMat[3][1] = 0.0;						\n"
"orientationMat[0][2] = zaxis.x;					\n"
"orientationMat[1][2] = zaxis.y;					\n"
"orientationMat[2][2] = zaxis.z;					\n"
"orientationMat[3][2] = 0;							\n"
"orientationMat[0][3] = gl_MultiTexCoord1.x;		\n"
"orientationMat[1][3] = gl_MultiTexCoord1.y;		\n"
"orientationMat[2][3] = gl_MultiTexCoord1.z;		\n"
"orientationMat[3][3] = 1.0;						\n"
"positionWorld = gl_Vertex * VelocityMatrix * orientationMat ;				\n"
"positionWorld = gl_ModelViewMatrix * positionWorld ;						\n"
"gl_FrontColor = gl_MultiTexCoord3;											\n"
"gl_TexCoord[0]  = gl_MultiTexCoord0;										\n"
"gl_Position = gl_ProjectionMatrix * positionWorld ;						\n"
"}																			\n",
0 
};


const char*	GetShaderCode ( eShader in_eShader )
{
	return gShaders[(int)in_eShader];
}
