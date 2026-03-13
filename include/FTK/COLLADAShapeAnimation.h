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

#ifndef _COLLADASHAPEANIMATION_H
#define _COLLADASHAPEANIMATION_H

#include "Template.h"
#include "Logger.h"
#include "Scene.h"
#include "COLLADATemplate.h"
#include "Model.h"
#include "XSIShapeAnimation.h"
#include "COLLADAScene.h"
#include "COLLADASubComponentAttributeList.h"

/** 
* CSLCOLLADAShapeAnimation Class
* 
*/

class XSIEXPORT CSLCOLLADAShapeAnimation : public CSLXSIShapeAnimation
{
public:
	///////////////////////////////////////////////////////////////////////////
	// Construction/destruction
	///////////////////////////////////////////////////////////////////////////
	CSLCOLLADAShapeAnimation(CSLScene* in_pScene, 
								CSLModel *in_pModel, 
								CdotXSITemplate* in_pTemplate,
								EFCurveInterpolationType in_Type);
	virtual ~CSLCOLLADAShapeAnimation();

	virtual SI_Error Synchronize();

protected:
	virtual CSLXSIShape* CreateXSIShape();
};

#endif
