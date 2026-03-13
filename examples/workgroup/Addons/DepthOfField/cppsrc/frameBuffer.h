//-
// ==========================================================================
// Copyright 2009 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk
// license agreement provided at the time of installation or download,
// or which otherwise accompanies this software in either electronic
// or hard copy form.
// ==========================================================================
//+
#ifndef __frameBuffer_h 
#define __frameBuffer_h 

#if !defined(unix)
#include <windows.h>
#endif

#include "GLee.h"


class frameBuffer
{
public:
	frameBuffer();
	~frameBuffer();

    void					bind( int w, int h );
    void					unbind();

	GLuint					texture() const		{ return fTexture; }

private:
    GLuint                  fFrameBuffer;
    GLuint                  fTexture;

    GLuint                  fWidth;
    GLuint                  fHeight;

	void					deleteObjects();

};

#endif	// __frameBuffer_h 
