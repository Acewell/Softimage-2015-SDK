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

#ifndef _SLCALLBACKS_DOTXSI_5X_H
#define _SLCALLBACKS_DOTXSI_5X_H

#include "Template.h"
#include "Scene.h"

// registration function

XSIEXPORT SI_Error Register_dotXSI_5x(CSLScene *in_pScene);

// Load callback

XSIEXPORT CSLTemplate *XSIUserDataBlobCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSITransformCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIBasePoseCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSILimitCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIMeshCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIShapeCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIShapeAnimationCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIPolygonListCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSITriangleListCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSITriangleStripListCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIVertexListCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSISubComponentAttributeListCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
XSIEXPORT CSLTemplate *XSIClusterInfoCallback(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);

// Post load callbacks

XSIEXPORT SI_Error XSIPolygonListPostLoadCallback(SLContext *in_pContext);
XSIEXPORT SI_Error XSITriangleListPostLoadCallback(SLContext *in_pContext);
XSIEXPORT SI_Error XSITriangleStripListPostLoadCallback(SLContext *in_pContext);

#endif