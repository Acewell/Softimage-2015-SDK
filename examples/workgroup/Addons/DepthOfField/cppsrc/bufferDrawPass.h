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
#ifndef __bufferDrawPass_h 
#define __bufferDrawPass_h

#if !defined(unix)
#include <windows.h>
#endif

#include "GLee.h"
#include "Cg/cg.h"
#include <Cg/cgGL.h>
#include <vector>

#include <xsi_color.h>
#include <xsi_graphicsequencer.h>

class M3dView; 

extern void CheckFramebufferStatus();

struct RenderBuffer
{
    GLuint                  fFrameBuffer;
    GLuint                  fDepthBuffer;
    GLuint                  fTexture;
    GLuint                  fTexture2;
    GLuint                  fDepthTexture;
    GLuint                  fTextureWidth;
    GLuint                  fTextureHeight;
	std::vector<GLuint>		fMipFrameBuffers;

	bool					fInitialized;

    void                    unbind();
    void                    bind();
    void                    freeBuffers();
    void                    initializeDefault();
    bool                    bufferOk( unsigned int w, unsigned int h );
    void                    rebuildBuffer( unsigned int w,
                                           unsigned int h,
										   bool floatTex,
										   bool twoTex,
										   bool depthTex );
};

class bufferDrawPass
{ 
public: 
	bufferDrawPass( bool floatTex, bool twoTex, bool depthTex, bool clearColor, bool clearDepth,
		XSI::CColor *clearColorValue = NULL, float *clearDepthValue = NULL );
	virtual ~bufferDrawPass(); 
	
	unsigned int		passId() const; 

	RenderBuffer &		renderBuffer(); 
	
	void				beginPass( XSI::CGraphicSequencer & );
	void				endPass( );

private: 

	bufferDrawPass();
	
	RenderBuffer		mRenderBuffer;
	static unsigned int	mIdCounter;

	CGparameter			mFragmentParamTexture;
	CGparameter			mFragmentParamDepth;
	
	unsigned int		mId;
	bool				mFloatTex;
	bool				mTwoTex;
	bool				mDepthTex;
	bool				mClearColor;
	bool				mClearDepth;
	XSI::CColor			mClearColorValue;
	float				mClearDepthValue;
	bool				mClearColorValueOverride;
	bool				mClearDepthValueOverride;
};

inline unsigned int bufferDrawPass::passId() const
{
	return mId; 
}

inline RenderBuffer& bufferDrawPass::renderBuffer( ) 
{
	return mRenderBuffer; 
}
#endif 
