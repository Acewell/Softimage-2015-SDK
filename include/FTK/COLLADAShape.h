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

#ifndef _COLLADASHAPE_H
#define _COLLADASHAPE_H

#include "Template.h"
#include "Logger.h"
#include "Scene.h"
#include "COLLADATemplate.h"
#include "Model.h"
#include "XSIShape.h"
#include "COLLADAScene.h"
#include "COLLADASubComponentAttributeList.h"

/** 
* CSLCOLLADAShape Class
* 
*/
class CSLCOLLADAMesh;

class XSIEXPORT CSLCOLLADAShape : public CSLXSIShape
{
public:
	///////////////////////////////////////////////////////////////////////////
	// Construction/destruction
	///////////////////////////////////////////////////////////////////////////
	CSLCOLLADAShape(CSLScene* in_pScene, 
					CSLModel *in_pModel, 
					CdotXSITemplate* in_pTemplate, 
					CCOLLADATemplate* in_pVerticesDecl,
					CdotXSITemplates* in_pInputSemantics);
	virtual ~CSLCOLLADAShape();

	virtual SI_Error Synchronize();

	virtual CSLXSISubComponentAttributeList*	AddAttributeList(CSLXSISubComponentAttributeList::EAttributeType in_AttributeType);

	virtual void			SetParentMesh(CSLCOLLADAMesh* in_pCOLLADAMesh);
	virtual CSLCOLLADAMesh*	GetParentMesh();
protected:

	CCOLLADATemplate*	m_pVerticesDecl;

private:
	CSLCOLLADAMesh*		m_pParentMesh;
	bool				m_bSynchronized;

public:

};

#endif
