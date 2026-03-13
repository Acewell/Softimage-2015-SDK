#ifndef BOX_TRANSFORM_TOOL_DELEGATE_INCLUDED
#define BOX_TRANSFORM_TOOL_DELEGATE_INCLUDED
///////////////////////////////////////////////////////////////////////////
//
// File: BoxTransformToolDelegate.h
//
// Description: Box transform tool interface.
//
// Copyright 2010 Autodesk, Inc. All rights reserved.
// Use of this software is subject to the terms of the Autodesk license
// agreement provided at the time of installation or download, or which
// otherwise accompanies this software in either electronic or hard copy
// form.
//
///////////////////////////////////////////////////////////////////////////
#include "Constants.h"
#include "BBox.h"
#include <xsi_ref.h>
#include <xsi_math.h>

using namespace XSI; 
using namespace XSI::MATH; 

////////////////////////////////////////////////////////////////////////////////
//
// BoxTransformToolDelegate interface
//
////////////////////////////////////////////////////////////////////////////////

class BoxTransformToolDelegate {
public: // Interface methods
	virtual const BBox &	GetBBox() = 0;
	virtual CVector3		GetCenter() = 0;
	virtual CRefArray		GetTargets() = 0;
	virtual void			SelectToolButton( ToolHandleID in_HandleID ) = 0;
	virtual void			UpdateBBoxOrientation( const CRotation & ) = 0;
};

#endif // BOX_TRANSFORM_TOOL_DELEGATE_INCLUDED
