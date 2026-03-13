//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

#ifndef _GLSLSHADERS_H_
#define _GLSLSHADERS_H_

enum eShader
{
	GLSL_PSEUDO_INSTANCING =0,
};

const char*	GetShaderCode ( eShader in_eShader );

#endif

