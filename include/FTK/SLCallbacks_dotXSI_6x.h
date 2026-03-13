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

#ifndef _SLCALLBACKS_DOTXSI_6X_H
#define _SLCALLBACKS_DOTXSI_6X_H

#include "Template.h"
#include "Scene.h"

// registration function

XSIEXPORT SI_Error Register_dotXSI_6x(CSLScene *in_pScene);

// Load callbacks

XSIEXPORT CSLTemplate *XSIIKResolutionPlaneCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSICameraCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIPolymatricksCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSITranslateCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIRotateCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIScaleCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIShearCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSILookatCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIMatrixCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIShapeReferenceCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIActionClipContainerCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIIndexListCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSICameraFocalLengthCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIShaderMultiPortConnectionCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIImageFX2Callback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSITextureLayerCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSITextureLayerPortCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIUserKeywordCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIClipToParentCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIShaderCompoundCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIShaderCompoundPortCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);

// Post load callbacks
XSIEXPORT SI_Error XSIShapeReferencePostLoadCallback(SLContext *in_pContext);
XSIEXPORT SI_Error XSIActionClipContainerPostLoadCallback(SLContext *in_pContext);
XSIEXPORT SI_Error XSIShaderCompoundPostLoadCallback(SLContext *in_pContext);


#endif