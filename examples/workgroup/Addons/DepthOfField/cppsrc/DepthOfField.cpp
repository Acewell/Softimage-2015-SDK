//-
// ==========================================================================
// Copyright 2011 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk
// license agreement provided at the time of installation or download,
// or which otherwise accompanies this software in either electronic
// or hard copy form.
// ==========================================================================
//+

// Local includes
#include "depthOfFieldView.h"

// Softimage includes
#include <xsi_pluginregistrar.h>
#include <xsi_application.h>
#include <xsi_graphicsequencercontext.h>
#include <xsi_model.h>
using namespace XSI; 

// Globals
static depthOfFieldView *gWorkerObject = NULL;

SICALLBACK XSILoadPlugin( PluginRegistrar& in_reg )
{
	in_reg.PutAuthor(L"Autodesk");
	in_reg.PutName(L"DepthOfField");
	in_reg.PutVersion(1,0);

	in_reg.RegisterDisplayCallback( "DOF_Begin" );
	in_reg.RegisterDisplayCallback( "DOF_End" );
	
	return CStatus::OK;
}

SICALLBACK XSIUnloadPlugin( const PluginRegistrar& in_reg )
{
	CString strPluginName;
	strPluginName = in_reg.GetName();
	Application().LogMessage(strPluginName + L" has been unloaded.",siVerboseMsg);
	return CStatus::OK;
}

////////////
// Pre-draw
////////////
XSIPLUGINCALLBACK void DOF_Begin_Init
( 
	CRef in_context,
	void **in_pUserData 
)
{
	GraphicSequencerContext ctxt( in_context );
	CGraphicSequencer sequencer = ctxt.GetGraphicSequencer();

	CStringArray acsCustomViewModeList;
	acsCustomViewModeList.Add( CString("DOF_Begin") );
	CStatus status = sequencer.RegisterViewportCallback(	"DOF_Begin", 
															0,
															siBeginFrame,
															siNullGraphicDriver,
															siAll,
															acsCustomViewModeList );
	// Make sure there is no worker object yet
	if ( NULL != gWorkerObject ) {
		assert( NULL == gWorkerObject );
		delete gWorkerObject;
		gWorkerObject = NULL;
	}
}

XSIPLUGINCALLBACK void DOF_Begin_Execute
( 
	CRef in_context,
	void **in_pUserData 
)
{
	// First we make sure the custom property exists in the scene
	CustomProperty cpset = Application().GetActiveSceneRoot().GetProperties().GetItem("DOFSettings");
	if ( !cpset.IsValid() ) {
		return;
	}

	GraphicSequencerContext ctxt( in_context );
	CGraphicSequencer sequencer = ctxt.GetGraphicSequencer();

	// Create the worker object
	if ( NULL == gWorkerObject ) {
		gWorkerObject = new depthOfFieldView( );
	}
	// Update the cpset (The user might have replaced the pset)
	// We want to work with the one that is in the scene.
	gWorkerObject->SetCustomPSet( cpset );
	gWorkerObject->preMultipleDrawPass( sequencer );
}

XSIPLUGINCALLBACK void DOF_Begin_Term
( 
	CRef in_context,
	void **in_pUserData 
)
{
	delete gWorkerObject;
	gWorkerObject = NULL;
}


/////////////
// Post-draw
/////////////
XSIPLUGINCALLBACK void DOF_End_Init
( 
	CRef in_context,
	void **in_pUserData 
)
{
	GraphicSequencerContext ctxt( in_context );
	CGraphicSequencer sequencer = ctxt.GetGraphicSequencer();

	CStringArray acsCustomViewModeList;
	acsCustomViewModeList.Add( CString("DOF_End") );
	CStatus status = sequencer.RegisterViewportCallback(	"DOF_End", 
															0,
															siPreEndFrame,
															siNullGraphicDriver,
															siAll,
															acsCustomViewModeList );
}

XSIPLUGINCALLBACK void DOF_End_Execute
( 
	CRef in_context,
	void **in_pUserData 
)
{
	// First we make sure the custom property exists in the scene
	CustomProperty cpset = Application().GetActiveSceneRoot().GetProperties().GetItem("DOFSettings");
	if ( !cpset.IsValid() ) {
		return;
	}

	GraphicSequencerContext ctxt( in_context );
	CGraphicSequencer sequencer = ctxt.GetGraphicSequencer();

	assert( gWorkerObject );
	if ( gWorkerObject ) {
		gWorkerObject->postMultipleDrawPass( sequencer );
	}
}

XSIPLUGINCALLBACK void DOF_End_Term
( 
	CRef in_context,
	void **in_pUserData 
)
{
}