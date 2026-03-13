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

#include <GL/gl.h>

#include <xsi_graphicsequencercontext.h>
#include <xsi_application.h>
#include <xsi_selection.h>

#include <assert.h>

void	MyCustomPass_Init			( XSI::CRef in_pSequencerContext, LPVOID *in_pUserData )
{
	//
	// Softimage's plugin registrar calls this to initialize the display pass.
	// Now, we must register the display pass with the Graphic Sequencer
	//
	
	XSI::GraphicSequencerContext l_vGraphicSequencerContext = in_pSequencerContext;

	// make sure the cast succeeded
	assert ( l_vGraphicSequencerContext.IsValid() );

	// get the sequencer from the context object
	XSI::CGraphicSequencer in_pSequencer = l_vGraphicSequencerContext.GetGraphicSequencer ();


	in_pSequencer.RegisterDisplayCallback ( L"MyCustomPass", 0, XSI::siPass, XSI::siCustom, L"MyCustomPass" );

}

void	MyCustomPass_Execute			( XSI::CRef in_pSequencerContext, LPVOID *in_pUserData )
{
	XSI::GraphicSequencerContext l_vGraphicSequencerContext = in_pSequencerContext;
	assert ( l_vGraphicSequencerContext.IsValid() );
	XSI::CGraphicSequencer in_pSequencer = l_vGraphicSequencerContext.GetGraphicSequencer ();

	//
	// Grab the current selection list
	//
	
	using namespace XSI;
	Application app;
	Selection sel = app.GetSelection();
	CRefArray array(sel.GetArray());

	//
	// Render the scene in hidden line
	//

	in_pSequencer.RenderSceneUsingMode ( siHiddenLineRemoval, siRenderDefault );

	//
	// Now render over the selection list using the material attached to the realtime port
	//

	in_pSequencer.RenderListUsingMode ( array, siRealtimePortMaterial );

	//
	// Note that for the sake of simplicity, we are rendering the object using built in passes 
	// (HiddenLine and RealtimePort).But you have much more flexibility when using RenderSceneUsingMaterial 
	// and provide your own shader ie: in_pSequencer->RenderSceneUsingMaterial ( L"MySuperShader", siRenderDefault );
	//

	//
	// Using Custom Display passes become very interesting when they are use in conjuncture with pixel buffers
	// (ie. accelerated offscreen OpenGL buffers). You can create your pbuffer, make it the current rendering
	// context and use the Sequencer to render the scene. Then, you can composite this pbuffer with other 
	// buffers, use multipass, blur them. etc. etc.
	//
	// Using this technique, you can do stuff like realtime shadows, reflections or other scene-wide effects.
	//

	return;
}

void	MyCustomPass_Term			( XSI::CRef in_pSequencerContext, LPVOID *in_pUserData )
{
}

void	MyCustomPass_InitInstance	( XSI::CRef in_pSequencerContext, LPVOID *in_pUserData )
{
}

void	MyCustomPass_TermInstance	( XSI::CRef in_pSequencerContext, LPVOID *in_pUserData )
{
}
