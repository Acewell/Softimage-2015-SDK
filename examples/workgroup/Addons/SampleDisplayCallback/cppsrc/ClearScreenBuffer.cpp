//***************************************************************************************
//
// File supervisor: Dominic Laflamme
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   
//***************************************************************************************

#include "StdAfx.h"
#include "SampleDisplayCallback.h"
#include <xsi_graphicsequencercontext.h>
#include <assert.h>

#include <GL/gl.h>

void	MyClearScreenBuffer_Init			( XSI::CRef in_pSequencerContext, LPVOID *in_pUserData )
{
	//
	// Softimage's plugin registrar calls this to initialize the display callback.
	// Now, we must register the display callback with the Graphic Sequencer
	//
	// This simple example clears the frame buffer to custom color.
	// The parameter XSI::siAll means that this callback affects all display modes, even custom ones
	//
	
	// cast the CRef into a GraphicSequencerContext SDK object
	XSI::GraphicSequencerContext l_vGraphicSequencerContext = in_pSequencerContext;

	// make sure the cast succeeded
	assert ( l_vGraphicSequencerContext.IsValid() );

	// get the sequencer from the context object
	XSI::CGraphicSequencer in_pSequencer = l_vGraphicSequencerContext.GetGraphicSequencer ();

	// use the sequencer to register the callback
	in_pSequencer.RegisterDisplayCallback ( L"MyClearScreenBuffer", 0, XSI::siPostBeginFrame, XSI::siCustom, L"MyCustomPass");

}

void	MyClearScreenBuffer_Execute			( XSI::CRef in_pSequencerContext, LPVOID *in_pUserData )
{
	//
	// Call OpenGL to clear the frame buffer
	//

	::glClearColor ( 0.2f, 0.3f, 0.4f, 1.0f );
	::glClear ( GL_COLOR_BUFFER_BIT );

}

void	MyClearScreenBuffer_Term			( XSI::CRef in_pSequencerContext, LPVOID *in_pUserData )
{
	// 
	// You should free user data and local memory here. 
	//
	
}

void	MyClearScreenBuffer_InitInstance	( XSI::CRef in_pSequencerContext, LPVOID *in_pUserData )
{
}

void	MyClearScreenBuffer_TermInstance	( XSI::CRef in_pSequencerContext, LPVOID *in_pUserData )
{
}
