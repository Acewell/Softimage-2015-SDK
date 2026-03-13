
//
//	File Name: depthOfFieldView.h
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

#ifndef _DEPTH_OF_FIELD_VIEW_H
#define _DEPTH_OF_FIELD_VIEW_H

// Softimage
#include <xsi_customproperty.h>
namespace XSI {
	class CGraphicSequencer;
}

#if !defined(unix)
#include <windows.h>
#endif

#include <GLee.h>
#include <Cg/cg.h>
#include <Cg/cgGL.h>

class bufferDrawPass;
class frameBuffer;

#define kViewTypeName "depthOfFieldView"
#define kNumMipBuffers 8

class depthOfFieldView
{
public:
	depthOfFieldView( );
	virtual ~depthOfFieldView();

public:
    virtual void        	preMultipleDrawPass( XSI::CGraphicSequencer &sequencer );
    virtual void        	postMultipleDrawPass( XSI::CGraphicSequencer &sequencer );
	void					SetCustomPSet( const XSI::CustomProperty &in_cpset );

private:
	static const char*  className()			{ return "depthOfFieldView"; }

	bufferDrawPass*		fColourPass;
	frameBuffer*		fMipBuffers[ kNumMipBuffers ];

	bool				fCgInit;
	CGcontext           fCgContext;
    CGprofile           fCgVertexProfile;
    CGprofile           fCgFragmentProfile;

	CGprogram           fCgFilterVP;
	CGprogram			fCgFilterFP;
	CGparameter			fCgFilterColourSamp;
	CGparameter			fCgRes;
	CGparameter			fCgInvRes;

	CGprogram           fCgDOFVP;
	CGprogram			fCgDOFFP;
	CGparameter			fCgColourSamp;
	CGparameter			fCgDepthSamp;
	CGparameter			fCgCameraNear;
	CGparameter			fCgCameraFar;
	CGparameter			fCgFocalPlane;
	CGparameter			fCgFocalLength;
	CGparameter			fCgVp;
	CGparameter			fCgCocFactor;
	CGparameter			fCgInvVpWidth;
	CGparameter			fCgInvVpHeight;

	XSI::Parameter		fFocalPlane;
	XSI::Parameter		fFStop;
	XSI::Parameter		fFocusRegionScale;
	XSI::Parameter		fFocalLength;
	XSI::Parameter		fDebug;
	XSI::Parameter		fMaxLevel;
	XSI::Parameter		fUseCameraSettings;
	XSI::Parameter		fEnableDOF;
	XSI::CustomProperty	fCPSet;		

	void				drawPostQuad( XSI::CGraphicSequencer &sequencer );
	void				loadShaders( CGprogram& vp, CGprogram& fp, const char* pVertex, const char* pFragment );
	void				setupCG();
	void				checkForCgError( const char* situation );
	void				setupBuffersAndShaders();
};

#endif // ndef _DEPTH_OF_FIELD_VIEW_H
