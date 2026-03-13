
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

// Softimage
#include <xsi_application.h>
using namespace XSI;

#include "bufferDrawPass.h"

unsigned int bufferDrawPass::mIdCounter = 0;
static bool sGLee_init = false; 

void CheckFramebufferStatus()
{
    GLenum status;
    status = (GLenum) glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
    switch(status) {
        case GL_FRAMEBUFFER_COMPLETE_EXT:
            break;
        case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
            Application().LogMessage("Unsupported framebuffer format\n");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
            Application().LogMessage("Framebuffer incomplete, missing attachment\n");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_DUPLICATE_ATTACHMENT_EXT:
            Application().LogMessage("Framebuffer incomplete, duplicate attachment\n");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
            Application().LogMessage("Framebuffer incomplete, attached images must have same dimensions\n");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
            Application().LogMessage("Framebuffer incomplete, attached images must have same format\n");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
            Application().LogMessage("Framebuffer incomplete, missing draw buffer\n");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
            Application().LogMessage("Framebuffer incomplete, missing read buffer\n");
            break;
    }
}

void RenderBuffer::freeBuffers()
{
	if ( fInitialized ) 
	{ 
		glDeleteFramebuffersEXT( 1, &fFrameBuffer );
		if ( fDepthBuffer )
			glDeleteRenderbuffersEXT( 1, &fDepthBuffer );
		glDeleteTextures( 1, &fTexture );
		if ( fTexture2 )
			glDeleteTextures( 1, &fTexture2 );
		if ( fDepthTexture )
			glDeleteTextures( 1, &fDepthTexture );
		for ( size_t i=0; i<fMipFrameBuffers.size(); ++i )
		{
			GLuint f = fMipFrameBuffers[i];
			glDeleteFramebuffersEXT( 1, &f );
		}
		fMipFrameBuffers.clear();
		fInitialized = false; 
	}	
}

void RenderBuffer::initializeDefault()
{
	fFrameBuffer = 0;
	fDepthBuffer = 0;
	fInitialized = false;
	fTexture2 = 0;
	fDepthTexture = 0;
	fTextureWidth = 1024; 
	fTextureHeight = 1024; 
	fMipFrameBuffers.clear();
}

bool RenderBuffer::bufferOk( 
	unsigned int w, 
	unsigned int h)
{
	if ( w != fTextureWidth || h != fTextureHeight || !fInitialized ) 
	{
		return false; 
	}
	return true; 
}

void RenderBuffer::rebuildBuffer( 
	unsigned int w, 
	unsigned int h,
	bool floatTex,
	bool twoTex,
	bool depthTex )
//
// Description: 
//  Create a new frame buffer for the specifed dimensions. This is where
//  rendered data will be sent. 
// 
{
	freeBuffers(); 
	
	glGenFramebuffersEXT(1, &fFrameBuffer);
	bind(); 

	fInitialized = true; 
	fTextureWidth = w; 
	fTextureHeight = h; 
	
	// init texture
	glGenTextures(1,		&fTexture);
	glBindTexture(GL_TEXTURE_2D, fTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, 
					floatTex ? GL_RGBA32F_ARB : GL_RGBA8,
					fTextureWidth, fTextureHeight, 
					0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	int mw = ( w == 1 ) ? 1 : ( w >> 1 );
	int mh = ( h == 1 ) ? 1 : ( h >> 1 );
	int level = 1;
	int maxmip = 0;
	for (;;)
	{
		glTexImage2D(GL_TEXTURE_2D, level, 
						floatTex ? GL_RGBA32F_ARB : GL_RGBA8,
						mw, mh, 
						0, GL_RGBA, GL_FLOAT, NULL);
		maxmip = level;
		if ( mw == 1 && mh == 1 )
			break;
		mw = ( mw == 1 ) ? 1 : ( mw >> 1 );
		mh = ( mh == 1 ) ? 1 : ( mh >> 1 );
		level += 1;
	}

	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
							  GL_TEXTURE_2D, fTexture, 0);

	if ( twoTex )
	{
		// init texture
		glGenTextures(1,		&fTexture2);
		glBindTexture(GL_TEXTURE_2D, fTexture2);
		glTexImage2D(GL_TEXTURE_2D, 0, 
						floatTex ? GL_RGBA32F_ARB : GL_RGBA8,
						fTextureWidth, fTextureHeight, 
						0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT,
								  GL_TEXTURE_2D, fTexture2, 0);
	}

	if ( depthTex )
	{
		fDepthBuffer = 0;

		// init texture
		glGenTextures(1,		&fDepthTexture);
		glBindTexture(GL_TEXTURE_2D, fDepthTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, 
						GL_DEPTH_COMPONENT24,
						fTextureWidth, fTextureHeight, 
						0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,
								  GL_TEXTURE_2D, fDepthTexture, 0);
	}
	else
	{
		fDepthTexture = 0;

		// initialize render buffer for depth
		glGenRenderbuffersEXT(1,&fDepthBuffer);
		glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, fDepthBuffer);
		glRenderbufferStorageEXT(
			GL_RENDERBUFFER_EXT, 
			GL_DEPTH_COMPONENT24, fTextureWidth, fTextureHeight);

		glFramebufferRenderbufferEXT(
			GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, 
			GL_RENDERBUFFER_EXT, fDepthBuffer);
	}

	glBindTexture( GL_TEXTURE_2D, 0 );

	CheckFramebufferStatus();

	// Unbind the framebuffer
	// 
	unbind();

	for ( int i=1; i<=maxmip; ++i )
	{
		GLuint f;
		glGenFramebuffersEXT( 1, &f );
		glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, f );

		glFramebufferTexture2DEXT( GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
								   GL_TEXTURE_2D, fTexture, i );

		fMipFrameBuffers.push_back( f );

		glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
	}
}

inline unsigned int next_higher_power_of_two( unsigned int k )
{
    int i;
    k--;
    for (i=1; i<sizeof(unsigned int)*8; i=i*2)
        k = k | k >> i;
    return k+1;
}

inline unsigned int make_power_of_two( unsigned int i )
{
    if ( (i & (i-1)) == 0 ) {
        return i;
    }
    return next_higher_power_of_two( i );
}

void RenderBuffer::bind()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fFrameBuffer);
}

void RenderBuffer::unbind()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

bufferDrawPass::bufferDrawPass( 
	bool floatTex,
	bool twoTex,
	bool depthTex,
	bool clearColor,
	bool clearDepth,
	CColor *clearColorValue,
	float *clearDepthValue
	)
	: mFloatTex( floatTex )
	, mTwoTex( twoTex )
	, mDepthTex( depthTex )
{
	mId = mIdCounter ++; 
	mRenderBuffer.initializeDefault();
	
    if ( !sGLee_init ) {
		if( !GLeeInit() ) {
			Application().LogMessage( "unable to load GLee" );
		}
		sGLee_init = true;
	}

	mClearColor = clearColor;
	if( clearColorValue != NULL )
	{
		mClearColorValue = *clearColorValue;
		mClearColorValueOverride = true;
	}
	else
	{
		mClearColorValueOverride = false;
	}

	mClearDepth = clearDepth;
	if( clearDepthValue != NULL )
	{
		mClearDepthValue = *clearDepthValue;
		mClearDepthValueOverride = true;
	}
	else
	{
		mClearDepthValueOverride = false;
	}
}

bufferDrawPass::~bufferDrawPass()
{
	mRenderBuffer.freeBuffers(); 
}
	
void				
bufferDrawPass::beginPass( CGraphicSequencer &sequencer )
{
	unsigned int x, y, w, h; 
	sequencer.GetViewportSize( x, y, w, h ); 
	unsigned int width = w;//make_power_of_two( w ); 
	unsigned int height = h;//make_power_of_two( h ); 
	if ( width > 4096 || height > 4096 ) { 
		Application().LogMessage( "Viewport is too large" ); 
		return; 
	}
	if ( !mRenderBuffer.bufferOk( width, height ) ) { 
		mRenderBuffer.rebuildBuffer( width, height, mFloatTex, mTwoTex, mDepthTex ); 
	}

	mRenderBuffer.bind();
	if ( mTwoTex )
	{
		GLenum buffers[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT };
		glDrawBuffers(2, buffers);
	}
	else
	{
		glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT); 
	}

	if( mClearColorValueOverride || mClearDepthValueOverride )
	{
		glPushAttrib( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		if( mClearColorValueOverride )
		{
			glClearColor( (float)mClearColorValue.r, (float)mClearColorValue.g, (float)mClearColorValue.b, (float)mClearColorValue.a );
		}

		if( mClearDepthValueOverride )
		{
			glClearDepth( mClearDepthValue );
		}
	}

	if( mClearColor ) glClear( GL_COLOR_BUFFER_BIT ); 
	if( mClearDepth ) glClear( GL_DEPTH_BUFFER_BIT ); 
}

void
bufferDrawPass::endPass( )
{
	if( mClearColorValueOverride || mClearDepthValueOverride )
	{
		glPopAttrib();
	}

	mRenderBuffer.unbind();
	glDrawBuffer( GL_BACK );
}
