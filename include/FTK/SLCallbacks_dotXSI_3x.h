//***************************************************************************************
//
// File supervisor: Crosswalk team
//
// Copyright 2008 Autodesk, Inc.  All rights reserved.  
// Use of this software is subject to the terms of the Autodesk license agreement 
// provided at the time of installation or download, or which otherwise accompanies 
// this software in either electronic or hard copy form.
//
//***************************************************************************************

#ifndef _SLCALLBACKS_DOTXSI_3X_H
#define _SLCALLBACKS_DOTXSI_3X_H

#include "Template.h"
#include "Scene.h"

// registration function

XSIEXPORT SI_Error Register_dotXSI_3x(CSLScene *in_pScene);

// Load callbacks

XSIEXPORT CSLTemplate *SIAmbienceCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SIAngleCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SICameraCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SIClusterCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SIConstraintCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SICurveListCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SIEnvelopeCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SIEnvelopeListCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SIFCurveCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SIFileInfoCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SIGlobalMaterialCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SIIKEffectorCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SIIKJointCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SIIKRootCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SIInstanceCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SILightCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SIMaterialCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SIMaterialLibraryCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SIMeshCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SIModelCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SINurbsCurveCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SINurbsSurfaceCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SIPolygonListCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SIShape35Callback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SIShapeAnimationCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SIShapeCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SITransformCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SITriangleListCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SITriangleStripCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SITriangleStripListCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SISceneInfoCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SISurfaceMeshCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SIVisibilityCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIShaderCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIShaderInstanceDataCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIMaterialCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);	
XSIEXPORT CSLTemplate *XSICustomPSetCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);

XSIEXPORT CSLTemplate *XSIStaticValueCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSITrackCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIMixerCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSITimeControlCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIExtrapolationCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIActionClipCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIActionCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);

XSIEXPORT CSLTemplate *SICoordinateSystemCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SIFogCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SINullCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SITexture2DCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);

XSIEXPORT CSLTemplate *XSIImageLibraryCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIImageCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIImageDataCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIImageFXCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *SILightInfoCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIMaterialInfoCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSINurbsProjectionCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSINurbsTrimCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSICustomParamInfoCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIFXTreeCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIFXOperatorCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIUserDataCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIUserDataListCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);


// Post load callbacks
XSIEXPORT SI_Error DefaultPostChildrenCallback(CSLTemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT SI_Error SIClusterPostLoadCallback(SLContext *in_pContext);
XSIEXPORT SI_Error SIConstraintPostLoadCallback(SLContext *in_pContext);
XSIEXPORT SI_Error SIEnvelopePostLoadCallback(SLContext *in_pContext);
XSIEXPORT SI_Error SIFCurvePostLoadCallback(SLContext *in_pContext);
XSIEXPORT SI_Error SIGlobalMaterialPostLoadCallback(SLContext *in_pContext);
XSIEXPORT SI_Error SIIKRootPostLoadCallback(SLContext *in_pContext);
XSIEXPORT SI_Error SIInstancePostLoadCallback(SLContext *in_pContext);
XSIEXPORT SI_Error SIMaterialPostLoadCallback(SLContext *in_pContext);
XSIEXPORT SI_Error SIPolygonListPostLoadCallback(SLContext *in_pContext);
XSIEXPORT SI_Error SITriangleListPostLoadCallback(SLContext *in_pContext);
XSIEXPORT SI_Error SITriangleStripListPostLoadCallback(SLContext *in_pContext);
XSIEXPORT SI_Error XSIShaderPostLoadCallback(SLContext *in_pContext);
XSIEXPORT SI_Error XSIShaderInstanceDataPostLoadCallback(SLContext *in_pContext);
XSIEXPORT SI_Error XSIMaterialPostLoadCallback(SLContext *in_pContext);
XSIEXPORT SI_Error XSIFXTreePostLoadCallback(SLContext *in_pContext);
XSIEXPORT SI_Error XSIActionClipPostLoadCallback(SLContext *in_pContext);

#endif