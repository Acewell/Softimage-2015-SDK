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

#ifndef _SLCALLBACKS_COLLADA_1_4X_H
#define _SLCALLBACKS_COLLADA_1_4X_H

#include "Template.h"
#include "Scene.h"

// registration function

XSIEXPORT SI_Error Register_COLLADA_1_4x(CSLScene *in_pScene);

// scene Load callbacks
XSIEXPORT CSLTemplate *COLLADALightCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *COLLADANodeCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *COLLADAMeshCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *COLLADAControllerCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *COLLADAEnvelopeCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *COLLADAShapeAnimationCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext, CCOLLADATemplate *in_pMorphTemplate = NULL);
XSIEXPORT CSLTemplate *COLLADAModelCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *COLLADACameraCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *COLLADAAnimationLibraryNodeCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *COLLADAImageLibraryCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *COLLADAImageCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *COLLADAMaterialLibraryCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *COLLADAMaterialCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *COLLADAEffectLibraryCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *COLLADAEffectCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *COLLADAFXCommonProfileCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *COLLADAFXCommonShaderCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *COLLADASetParamCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *COLLADATranslateCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *COLLADARotateCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *COLLADAScaleCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *COLLADAShearCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *COLLADALookatCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *COLLADAMatrixCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *COLLADAXSIParamCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *COLLADAInstanceCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *COLLADAAnimationClipCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);

// node Post load callbacks
XSIEXPORT SI_Error	    COLLADAPostChildrenModelCallback(CSLTemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT SI_Error		COLLADAMaterialPostChildrenCallback(CSLTemplate *in_pTemplate, SLContext *in_pContext);

// scene Post load callbacks
XSIEXPORT SI_Error		COLLADAAnimationLibraryCallback(SLContext *in_pContext);
XSIEXPORT SI_Error		COLLADAControllerLibraryCallback(SLContext *in_pContext);
XSIEXPORT SI_Error		COLLADAMaterialLibraryPostCallback(SLContext *in_pContext);
XSIEXPORT SI_Error		COLLADAMaterialLibraryPostLoadCallback(SLContext *in_pContext);
XSIEXPORT SI_Error		COLLADADotXSIFixupPostCallback(SLContext *in_pContext);
XSIEXPORT SI_Error		COLLADAInstancePostCallback(SLContext *in_pContext);

#endif