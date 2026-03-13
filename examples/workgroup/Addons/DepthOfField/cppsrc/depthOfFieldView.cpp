
//	File Name: depthOfFieldView.cpp
//
//	Description:
//		An MPx3dModelView-derived class to support viewport Depth Of Field.
//

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

#include "depthOfFieldView.h"
#include "bufferDrawPass.h"
#include "frameBuffer.h"

#include <xsi_application.h>
using namespace XSI;

#include <math.h>
#include <stdlib.h>

enum WhichTex { kColourTex, kColourTex2, kDepthTex };
static void draw2dQuadWithBuffer( CGraphicSequencer &sequencer, bufferDrawPass* lPass, GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2, WhichTex which );
static void debugDrawTexture( GLuint tex, GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2 );

#if 0
// for reference
// http://www.derekbradley.ca/CourseProjects/cs514.pdf
static float CoCinPixels( float focalLength, float fstop, float focalPlane, float objectDistance,
							float viewportW, float nearPlane, float frustumW )
{
	float vu = focalLength * objectDistance / ( objectDistance - focalLength );
	float vp = focalLength * focalPlane / ( focalPlane - focalLength );
	float coc = 0.5f * fabsf( vu - vp ) * focalLength / ( fstop * vu );
	return coc * viewportW * nearPlane / ( frustumW * vp );
}
#endif

depthOfFieldView::depthOfFieldView( )
: fCgInit( false )
, fColourPass( NULL )
{
	for ( int i=0; i<kNumMipBuffers; ++i )
		fMipBuffers[ i ] = NULL;
}

void depthOfFieldView::SetCustomPSet( const XSI::CustomProperty &in_cpset )
{
	fCPSet = in_cpset;

	assert( fCPSet.IsValid() );
	fDebug				= fCPSet.GetParameter("Debug");				assert( fDebug.IsValid() );
	fUseCameraSettings	= fCPSet.GetParameter("UseCameraSettings");	assert( fUseCameraSettings.IsValid() );
	fFocalPlane			= fCPSet.GetParameter("FocalPlane");		assert( fFocalPlane.IsValid() );
	fFStop				= fCPSet.GetParameter("FStop");				assert( fFStop.IsValid() );
	fFocusRegionScale	= fCPSet.GetParameter("FocusRegionScale");	assert( fFocusRegionScale.IsValid() );
	fFocalLength		= fCPSet.GetParameter("FocalLength");		assert( fFocalLength.IsValid() );
	fMaxLevel			= fCPSet.GetParameter("MaxLevel");			assert( fMaxLevel.IsValid() );
	fEnableDOF			= fCPSet.GetParameter("EnableDOF");			assert( fEnableDOF.IsValid() );
}

void	depthOfFieldView::setupBuffersAndShaders()
{
	fColourPass = new bufferDrawPass( false, false, true, true, true );

	for ( int i=0; i<kNumMipBuffers; ++i )
		fMipBuffers[ i ] = new frameBuffer();

#define GET_PARAM( fp, p, n )						\
	p = cgGetNamedParameter( fp, n );				\
	if ( !cgIsParameter( p ) )						\
		Application().LogMessage( "Didn't get " n );

	loadShaders( fCgFilterVP, fCgFilterFP,
// VERTEX PROGRAM
"void main(	float2 position : POSITION,"
"			float2 texCoord : TEXCOORD0,"
"			out float4 oPosition : POSITION,"
"			out float2 oTexCoord : TEXCOORD0 )"
"{"
"  oPosition = float4( position, 0, 1 );"
"  oTexCoord = texCoord;"
"}"
				,
// FRAGMENT PROGRAM
"uniform sampler2D colorTexture;\n"
"uniform float2 resolution;\n"
"uniform float2 inverseResolution;\n"
"\n"
"void main(\n"
"        in  float2 texCoord : TEXCOORD0, \n"
"        out float4 outColor : COLOR )\n"
"{\n"
"		const float4 color00 = tex2D(colorTexture, texCoord.st + float2(-1.0, -1.0) * inverseResolution);\n"
"		const float4 color01 = tex2D(colorTexture, texCoord.st + float2( 0.0, -1.0) * inverseResolution);\n"
"		const float4 color02 = tex2D(colorTexture, texCoord.st + float2( 1.0, -1.0) * inverseResolution);\n"
"		const float4 color10 = tex2D(colorTexture, texCoord.st + float2(-1.0,  0.0) * inverseResolution);\n"
"		const float4 color11 = tex2D(colorTexture, texCoord.st + float2( 0.0,  0.0) * inverseResolution);\n"
"		const float4 color12 = tex2D(colorTexture, texCoord.st + float2( 1.0,  0.0) * inverseResolution);\n"
"		const float4 color20 = tex2D(colorTexture, texCoord.st + float2(-1.0,  1.0) * inverseResolution);\n"
"		const float4 color21 = tex2D(colorTexture, texCoord.st + float2( 0.0,  1.0) * inverseResolution);\n"
"		const float4 color22 = tex2D(colorTexture, texCoord.st + float2( 1.0,  1.0) * inverseResolution);\n"
"\n"
"		outColor.rgb = (\n"
"						color00 + color01 + color02 +\n"
"						color10 + color11 + color12 +\n"
"						color20 + color21 + color22) * (0.11111111);\n"
"		outColor.a = 1.0;\n"
"}\n"
				);

	GET_PARAM( fCgFilterFP, fCgFilterColourSamp, "colorTexture" )
	GET_PARAM( fCgFilterFP, fCgRes, "resolution" )
	GET_PARAM( fCgFilterFP, fCgInvRes, "inverseResolution" )

	loadShaders( fCgDOFVP, fCgDOFFP,
// VERTEX PROGRAM
"void main(	float2 position : POSITION,"
"			float2 texCoord : TEXCOORD0,"
"			out float4 oPosition : POSITION,"
"			out float2 oTexCoord : TEXCOORD0 )"
"{"
"  oPosition = float4( 2*position, 0, 1 );"
"  oTexCoord = texCoord;"
"}"
				,
// FRAGMENT PROGRAM
"uniform sampler2D colorTexture;\n"
"uniform sampler2D depthTexture;\n"
"uniform float cameraNear;\n"
"uniform float cameraFar;\n"
"uniform float focalPlane;\n"
"uniform float focalLength;\n"
"uniform float vp;\n"
"uniform float cocFactor;\n"
"uniform float invVpWidth;\n"
"uniform float invVpHeight;\n"
"\n"
"float unprojectDepth(const sampler2D depthTexture, const float2 texCoord) {\n"
"	const float deptBufferValue = tex2D(depthTexture, texCoord).x;\n"
"	return cameraFar * cameraNear / (deptBufferValue * (cameraFar - cameraNear) - cameraFar);\n"
"}\n"
"\n"
"void main(\n"
"        in  float2 texCoord : TEXCOORD0, \n"
"        out float4 outColor : COLOR )\n"
"{\n"
"	float z = unprojectDepth( depthTexture, texCoord );\n"
"	z = -z;\n"
"	float vu = focalLength * z / ( z - focalLength );\n"
"	float cocpixels  = cocFactor * abs( vu - vp ) / vu;\n"
"	cocpixels = ( z > focalLength ) ? cocpixels : cocFactor;\n"
"	float pixels = max( 0.0, cocpixels - 1.0 );\n"
"	float mx = pixels * invVpWidth;\n"
"	float my = pixels * invVpHeight;\n"
"	float2 dx = float2( mx, 0 );\n"
"	float2 dy = float2( 0, my );\n"
"	const float4 inputTexel = tex2D( colorTexture, texCoord, dx, dy );\n"
"	outColor = inputTexel;\n"
"}\n"
				);

	GET_PARAM( fCgDOFFP, fCgColourSamp, "colorTexture" )
	GET_PARAM( fCgDOFFP, fCgDepthSamp, "depthTexture" )
	GET_PARAM( fCgDOFFP, fCgCameraNear, "cameraNear" )
	GET_PARAM( fCgDOFFP, fCgCameraFar, "cameraFar" )
	GET_PARAM( fCgDOFFP, fCgFocalPlane, "focalPlane" )
	GET_PARAM( fCgDOFFP, fCgFocalLength, "focalLength" )
	GET_PARAM( fCgDOFFP, fCgVp, "vp" )
	GET_PARAM( fCgDOFFP, fCgCocFactor, "cocFactor" )
	GET_PARAM( fCgDOFFP, fCgInvVpWidth, "invVpWidth" )
	GET_PARAM( fCgDOFFP, fCgInvVpHeight, "invVpHeight" )
}

depthOfFieldView::~depthOfFieldView()
{
	if ( fCgInit )
	{
		if ( cgIsProgram( fCgFilterVP ) )
			cgDestroyProgram( fCgFilterVP );
		if ( cgIsProgram( fCgFilterFP ) )
			cgDestroyProgram( fCgFilterFP );
		if ( cgIsProgram( fCgDOFVP ) )
			cgDestroyProgram( fCgDOFVP );
		if ( cgIsProgram( fCgDOFFP ) )
			cgDestroyProgram( fCgDOFFP );
		if ( cgIsContext( fCgContext ) )
			cgDestroyContext( fCgContext );
	}

	delete fColourPass;
	for ( int i=0; i<kNumMipBuffers; ++i )
		delete fMipBuffers[ i ];
}

void depthOfFieldView::preMultipleDrawPass( CGraphicSequencer &sequencer )
{
	// if DOF is turned off, bail out
	if ( !fEnableDOF.GetValue() )
		return;

	if ( fColourPass == NULL )
	{
		// this setup is deferred to here to guarantee we're working with a properly
		// initialised OpenGL/Cg/etc.
		setupBuffersAndShaders();
	}

	fColourPass->beginPass( sequencer );
}

void depthOfFieldView::postMultipleDrawPass( CGraphicSequencer &sequencer )
{
	// if DOF is turned off, bail out
	if ( !fEnableDOF.GetValue() )
		return;

	fColourPass->endPass( );

	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();
	glPushAttrib( GL_VIEWPORT_BIT );

	glEnable( GL_TEXTURE_2D );
	glDisable( GL_LIGHTING );

	int w = fColourPass->renderBuffer().fTextureWidth;
	int h = fColourPass->renderBuffer().fTextureHeight;

	const int maxmip = (int)fColourPass->renderBuffer().fMipFrameBuffers.size();

	for ( int i=0; i<kNumMipBuffers; ++i )
	{
		if ( i == maxmip )
			break;

		const int tw = w;
		const int th = h;
		w = ( w == 1 ) ? 1 : ( w >> 1 );
		h = ( h == 1 ) ? 1 : ( h >> 1 );

		fMipBuffers[i]->bind( w, h );
		glViewport( 0, 0, w, h );
		GLuint tex;
		if ( i == 0 )
		{
			tex = fColourPass->renderBuffer().fTexture;
		}
		else
		{
			tex = fMipBuffers[i-1]->texture();
		}
		glBindTexture( GL_TEXTURE_2D, tex );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

		cgGLBindProgram( fCgFilterVP );				checkForCgError( "binding vertex program" );
		cgGLEnableProfile( fCgVertexProfile );		checkForCgError( "enabling vertex profile" );

		cgGLBindProgram( fCgFilterFP );				checkForCgError( "binding fragment program" );
		cgGLEnableProfile( fCgFragmentProfile );	checkForCgError( "enable fragment profile" );

		cgGLSetTextureParameter( fCgFilterColourSamp, tex );			checkForCgError( "setting colour texture parameter" );
		cgGLEnableTextureParameter( fCgFilterColourSamp );				checkForCgError( "enabling colour texture parameter" );

		cgGLSetParameter2f( fCgRes, (float)tw, (float)th );				checkForCgError( "setting res parameter" );
		cgGLSetParameter2f( fCgInvRes, 1.0f/tw, 1.0f/th );				checkForCgError( "setting invres parameter" );

		glColor3f( 1.0f, 1.0f, 1.0f );
		glBegin(GL_QUADS);
		{   
			glTexCoord2f( 0.0f, 0.0f ); 
			glVertex2f( -1.0f, -1.0f );
            
			glTexCoord2f( 1.0f, 0.0f );
			glVertex2f( 1.0f, -1.0f );
            
			glTexCoord2f( 1.0f, 1.0f );
			glVertex2f( 1.0f, 1.0f );
            
			glTexCoord2f( 0.0f, 1.0f );
			glVertex2f( -1.0f, 1.0f );
		}
		glEnd();

		cgGLDisableProfile( fCgVertexProfile );			checkForCgError( "disabling vertex profile" );
		cgGLDisableProfile( fCgFragmentProfile );		checkForCgError( "disable fragment profile" );

		cgGLDisableTextureParameter( fCgFilterColourSamp );	checkForCgError( "disabling colour texture" );

		fMipBuffers[i]->unbind();

		glBindTexture( GL_TEXTURE_2D, fMipBuffers[i]->texture() );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

		glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, fColourPass->renderBuffer().fMipFrameBuffers[i] );
		glDrawBuffer( GL_COLOR_ATTACHMENT0_EXT );

		glBegin(GL_QUADS);
		{   
			glTexCoord2f( 0.0f, 0.0f ); 
			glVertex2f( -1.0f, -1.0f );
            
			glTexCoord2f( 1.0f, 0.0f );
			glVertex2f( 1.0f, -1.0f );
            
			glTexCoord2f( 1.0f, 1.0f );
			glVertex2f( 1.0f, 1.0f );
            
			glTexCoord2f( 0.0f, 1.0f );
			glVertex2f( -1.0f, 1.0f );
		}
		glEnd();

		glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
		glDrawBuffer( GL_BACK );
		glBindTexture( GL_TEXTURE_2D, 0 );
	}

	// limit mipmap selection to those we've populated
	float maxLod = kNumMipBuffers;
	if ( (float) fMaxLevel.GetValue() < (float) kNumMipBuffers ) {
		maxLod = (float) fMaxLevel.GetValue();
	} 

	glBindTexture( GL_TEXTURE_2D, fColourPass->renderBuffer().fTexture );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, maxLod );
	glBindTexture( GL_TEXTURE_2D, 0 );

	glDisable( GL_TEXTURE_2D );

	glMatrixMode( GL_PROJECTION );
	glPopMatrix(); 
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();
	glPopAttrib();

	if ( fDebug.GetValue() == 1 )
	{
		glDisable( GL_LIGHTING );
		glBindTexture( GL_TEXTURE_2D, fColourPass->renderBuffer().fTexture );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		draw2dQuadWithBuffer( sequencer, fColourPass,  -0.5f, 0.0f, -0.5f, 0.0f, kColourTex );
		draw2dQuadWithBuffer( sequencer, fColourPass,  0.0f, 0.5f, -0.5f, 0.0f, kDepthTex );
		glBindTexture( GL_TEXTURE_2D, 0 );
	}
	else if ( fDebug.GetValue() == 2 )
	{
		const float dy = 2.0f/kNumMipBuffers;
		float y = -1.0f;
		for ( int i=0; i<kNumMipBuffers; ++i )
		{
			debugDrawTexture( fMipBuffers[i]->texture(), -1.0f, 1.0f, y, y+0.99f*dy );
			y += dy;
		}
	}
	drawPostQuad( sequencer );
}

static void	prepareProjectionMatrix()
{   
    double projMatrix[4][4]; 

    // Initialize the identity matrix.
    //
    projMatrix[0][0] = projMatrix[1][1] =
        projMatrix[2][2] = projMatrix[3][3] = 1.0;
    projMatrix[0][1] = projMatrix[0][2] =
        projMatrix[0][3] = projMatrix[1][0] =
        projMatrix[1][2] = projMatrix[1][3] =
        projMatrix[2][0] = projMatrix[2][1] =
        projMatrix[2][3] = projMatrix[3][0] =
        projMatrix[3][1] = projMatrix[3][2] = 0.0;
    
    // Now constructor the orthographic projection matrix.
    // left = -0.5, right = 0.5; diffRL = 1; diffTB = 1; 
    //
    projMatrix[0][0] = 2.0;
    projMatrix[1][1] = 2.0;
    projMatrix[2][2] = -1.0; 
    
    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
    glLoadMatrixd( projMatrix[0] );
}   
    
static void	popProjectionMatrix()
{   
    glMatrixMode( GL_PROJECTION );
    glPopMatrix(); 
}       

void draw2dQuadWithBuffer( CGraphicSequencer &sequencer, bufferDrawPass* lPass, GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2, WhichTex which )
{
	unsigned int vx, vy, width, height;
	sequencer.GetViewportSize( vx, vy, width, height );
	RenderBuffer &buffer = lPass->renderBuffer();
    GLfloat tw = (GLfloat)width / (GLfloat)buffer.fTextureWidth;
    GLfloat th = (GLfloat)height / (GLfloat)buffer.fTextureHeight;

    prepareProjectionMatrix();

    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    glLoadIdentity();
		switch ( which )
		{
		default:
		case kColourTex:
			glBindTexture(GL_TEXTURE_2D, buffer.fTexture);
			break;
		case kColourTex2:
			glBindTexture(GL_TEXTURE_2D, buffer.fTexture2);
			break;
		case kDepthTex:
			glBindTexture(GL_TEXTURE_2D, buffer.fDepthTexture);
			break;
		}
        glEnable(GL_TEXTURE_2D);
		glDisable( GL_LIGHTING );
        
        glColor3f( 1.0f, 1.0f, 1.0f );
        glBegin(GL_QUADS);
        {   
            glTexCoord2f(0, 0); 
            glVertex2f(x1, y1);
            
            glTexCoord2f(tw, 0);
            glVertex2f(x2, y1);
            
            glTexCoord2f(tw, th);
            glVertex2f(x2, y2);
            
            glTexCoord2f(0, th);
            glVertex2f(x1, y2);
        }
        glEnd();
        glDisable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, 0 );
        
    glPopMatrix();
        
    popProjectionMatrix();  
            
    glMatrixMode( GL_MODELVIEW );
}

void debugDrawTexture( GLuint tex, GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2 )
{
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();

	glBindTexture( GL_TEXTURE_2D, tex );
	glEnable( GL_TEXTURE_2D );
	glDisable( GL_LIGHTING );

	glBegin(GL_QUADS);
    {   
        glTexCoord2f( 0.0f, 0.0f );
        glVertex2f( x1, y1 );
        
        glTexCoord2f( 1.0f, 0.0f );
        glVertex2f( x2, y1 );
        
        glTexCoord2f( 1.0f, 1.0f );
        glVertex2f( x2, y2 );
        
        glTexCoord2f( 0.0f, 1.0f );
        glVertex2f( x1, y2 );
    }
    glEnd();

	glDisable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, 0 );

	glMatrixMode( GL_PROJECTION );
	glPopMatrix(); 
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix(); 
}

void	depthOfFieldView::drawPostQuad( CGraphicSequencer &sequencer )
{
	unsigned int vx, vy, width, height;
	sequencer.GetViewportSize( vx, vy, width, height );
	
	RenderBuffer& colourRb = fColourPass->renderBuffer();
	
    // It is possible that are texture size is bigger than the viewable
    // area. To establish the proper texture coordinates we need to
    // find this ratio.  We also need to share this ratio with the
    // the shader, which must determine the exact location in pixel
    // space.
    //
    GLfloat tw = (GLfloat)width / (GLfloat)colourRb.fTextureWidth;
    GLfloat th = (GLfloat)height / (GLfloat)colourRb.fTextureHeight;

    // Compute the drawing rectange based on viewport information.
    //
    GLfloat x1, x2, y1, y2;
	if ( fDebug.GetValue() )
	{
		x1 = -0.5f;
		x2 = 0.0f;
		y1 = 0.0f;
		y2 = 0.5f;
	}
	else
	{
		x1 = (GLfloat)(vx)/(GLfloat)width - (GLfloat)0.5;
		x2 = (GLfloat)(vx+width)/(GLfloat)width - (GLfloat)0.5;
		y1 = (GLfloat)(vy)/(GLfloat)height - (GLfloat)0.5;
		y2 = (GLfloat)(vy+height)/(GLfloat)height - (GLfloat)0.5;
	}

	Camera camera = sequencer.GetCamera();
	CParameterRefArray cameraParams = camera.GetParameters();

	GLfloat nearPlane = cameraParams.GetValue("near");
	GLfloat farPlane = cameraParams.GetValue("far");

	double aspect = (double)width/(double)height;
	double left, right, top, bottom;

	camera.GetFrustum( left, right, bottom, top );
	const double frustumW = ( right - left );

	double focusDistance, fstop, focalLength;

	if ( fUseCameraSettings.GetValue() )
	{
		///////////////////////////////
		// This value is available in Maya, but not in Softimage. We use the CPSet value
		focusDistance = fFocalPlane.GetValue();

		// The Maya plug-in does it this way
		//		focusDistance = camera.focusDistance();									// cm
		///////////////////////////////

		///////////////////////////////
		// This value is available in Maya through computation, but not in Softimage. We use the CPSet value
		fstop = (double) fFStop.GetValue() * (double) fFocusRegionScale.GetValue();

		// The Maya plug-in does it this way
		// 		double frscale = camera.findPlug( "focusRegionScale" ).asDouble();		// unitless
		// 		fstop = camera.fStop();													// unitless
		// 		fstop *= frscale;														// apply focusRegionScale as per mental ray
		///////////////////////////////

		focalLength = cameraParams.GetValue("projplanedist");					// mm
		focalLength *= 0.1;														// to cm
	}
	else
	{
		focusDistance = fFocalPlane.GetValue();
		fstop = (double) fFStop.GetValue() * (double) fFocusRegionScale.GetValue();
		focalLength = fFocalLength.GetValue();
		focalLength *= 0.1;														// to cm
	}

	GLfloat focalPlane = (GLfloat)focusDistance;
	GLfloat vp = (GLfloat)( focalLength * focusDistance / ( focusDistance - focalLength ) );
	GLfloat cocFactor = (GLfloat)( 0.5 * width * nearPlane * focalLength / ( fstop * frustumW * vp ) );

    cgGLBindProgram( fCgDOFVP );				checkForCgError( "binding vertex program" );
    cgGLEnableProfile( fCgVertexProfile );		checkForCgError( "enabling vertex profile" );

    cgGLBindProgram( fCgDOFFP );				checkForCgError( "binding fragment program" );
    cgGLEnableProfile( fCgFragmentProfile );	checkForCgError( "enable fragment profile" );

	glBindTexture( GL_TEXTURE_2D, colourRb.fTexture );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );

	glBindTexture( GL_TEXTURE_2D, colourRb.fDepthTexture );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

	cgGLSetTextureParameter( fCgColourSamp, colourRb.fTexture );	checkForCgError( "setting colour texture parameter" );
	cgGLEnableTextureParameter( fCgColourSamp );					checkForCgError( "enabling colour texture parameter" );

	cgGLSetTextureParameter( fCgDepthSamp, colourRb.fDepthTexture );	checkForCgError( "setting depth texture parameter" );
	cgGLEnableTextureParameter( fCgDepthSamp );							checkForCgError( "enabling depth texture parameter" );

	cgGLSetParameter1f( fCgCameraNear, nearPlane );						checkForCgError( "setting near parameter" );
	cgGLSetParameter1f( fCgCameraFar, farPlane );						checkForCgError( "setting far parameter" );
	cgGLSetParameter1f( fCgFocalPlane, focalPlane );					checkForCgError( "setting focal plane parameter" );
	cgGLSetParameter1f( fCgFocalLength, (GLfloat)focalLength );			checkForCgError( "setting focal length parameter" );
	cgGLSetParameter1f( fCgVp, vp );									checkForCgError( "setting vp parameter" );
	cgGLSetParameter1f( fCgCocFactor, cocFactor );						checkForCgError( "setting coc factor parameter" );
	cgGLSetParameter1f( fCgInvVpWidth, 1.0f/width );					checkForCgError( "setting inv vp width parameter" );
	cgGLSetParameter1f( fCgInvVpHeight, 1.0f/height );					checkForCgError( "setting inv vp height parameter" );

	prepareProjectionMatrix();
	
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
		glLoadIdentity();
		glBegin( GL_QUADS ); 
		{
			glTexCoord2f(0, 0);
			glVertex2f(x1, y1);

			glTexCoord2f(tw, 0);
			glVertex2f(x2, y1);

			glTexCoord2f(tw, th);
			glVertex2f(x2, y2);

			glTexCoord2f(0, th);
			glVertex2f(x1, y2);
		}
		glEnd(); 
	glPopMatrix(); 

	// 	Pop the projection matrix. 
	popProjectionMatrix(); 

	// The prior call does not return to the model view matrix. Do it 
	// here.
	//
	glMatrixMode(GL_MODELVIEW); 

    cgGLDisableProfile( fCgVertexProfile );			checkForCgError( "disabling vertex profile" );
    cgGLDisableProfile( fCgFragmentProfile );		checkForCgError( "disable fragment profile" );

	cgGLDisableTextureParameter( fCgColourSamp );	checkForCgError( "disabling colour texture" );
	cgGLDisableTextureParameter( fCgDepthSamp );	checkForCgError( "disabling depthtexture" );

	glBindTexture( GL_TEXTURE_2D, 0 );
}

void	depthOfFieldView::loadShaders( CGprogram& vp, CGprogram& fp, const char* pVertex, const char* pFragment )
{
	setupCG(); 
	
	if ( !fCgInit )
	{ 
		Application().LogMessage( "Unable to setup CG!\n" );
		return;
	}

	vp = 
		cgCreateProgram(
			fCgContext,
			CG_SOURCE,
			pVertex,
			fCgVertexProfile, 
			"main",
			NULL );
	checkForCgError( "creating context" );
		
	if ( cgIsProgram( vp ) ) { 
		cgGLLoadProgram( vp ); 
		checkForCgError( "loading program" );
	}

	fp = 
		cgCreateProgram(
			fCgContext,
			CG_SOURCE,
			pFragment,
			fCgFragmentProfile,
			"main",
			NULL );
	checkForCgError( "creating fragment program from file" );

	if ( cgIsProgram( fp ) ) { 
		cgGLLoadProgram( fp );
		checkForCgError( "loading fragment program" );
	}

//	refresh();
}

void	depthOfFieldView::setupCG()
//
// Description:
//  Initializes the CG shaders for pixel drawing. This should
//  only occur once.
//
{
    if ( fCgInit )
		return;

    fCgContext = cgCreateContext();
	if ( cgIsContext( fCgContext ) )
	{ 
		fCgVertexProfile = cgGLGetLatestProfile( CG_GL_VERTEX );
		cgGLSetOptimalOptions( fCgVertexProfile );

		fCgFragmentProfile = cgGLGetLatestProfile( CG_GL_FRAGMENT );
		cgGLSetOptimalOptions( fCgFragmentProfile ); 
		fCgInit = true;
	}
}

void	depthOfFieldView::checkForCgError( const char* situation )
{
    CGerror error;
    const char *str_err = cgGetLastErrorString(&error);
   
    if (error != CG_NO_ERROR)
	{
		Application().LogMessage( CString( str_err ) + " : " + situation );
        if (error == CG_COMPILER_ERROR)
		{
            Application().LogMessage(cgGetLastListing(fCgContext));
        }
    }
}
