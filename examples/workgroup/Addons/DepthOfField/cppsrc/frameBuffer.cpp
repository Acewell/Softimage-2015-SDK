
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

#include "frameBuffer.h"

extern void CheckFramebufferStatus();


frameBuffer::frameBuffer()
: fFrameBuffer( 0 )
, fTexture( 0 )
, fWidth( 0 )
, fHeight( 0 )
{
}

frameBuffer::~frameBuffer()
{
	deleteObjects();
}

void	frameBuffer::deleteObjects()
{
	if ( fFrameBuffer )
		glDeleteFramebuffersEXT( 1, &fFrameBuffer );
	if ( fTexture )
		glDeleteTextures( 1, &fTexture );

	fFrameBuffer = 0;
	fTexture = 0;
}

void	frameBuffer::bind( int w, int h )
{
	if ( w != fWidth || h != fHeight )
	{
		deleteObjects();

		fWidth = w;
		fHeight = h;

		glGenFramebuffersEXT( 1, &fFrameBuffer );
		glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, fFrameBuffer );
		
		// init texture
		glGenTextures( 1, &fTexture );
		glBindTexture( GL_TEXTURE_2D, fTexture );
		glTexImage2D( GL_TEXTURE_2D, 0, 
						GL_RGBA8,
						w, h, 
						0, GL_RGBA, GL_FLOAT, NULL );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

		glFramebufferTexture2DEXT( GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
								   GL_TEXTURE_2D, fTexture, 0 );

		CheckFramebufferStatus();

		glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
		glBindTexture( GL_TEXTURE_2D, 0 );
	}

	glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, fFrameBuffer );
	glDrawBuffer( GL_COLOR_ATTACHMENT0_EXT );
}

void	frameBuffer::unbind()
{
	glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
	glDrawBuffer( GL_BACK );
}
