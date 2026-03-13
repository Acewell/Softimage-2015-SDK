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

#ifndef _ANIMATABLEVECTOR_H
#define _ANIMATABLEVECTOR_H

#include <SIBCUtil.h>

class XSIEXPORT CSLAnimatableVector
{
public:
	CSLAnimatableVector() {};
	virtual ~CSLAnimatableVector() {};

	virtual SI_Error Synchronize() = 0;

};

#endif
