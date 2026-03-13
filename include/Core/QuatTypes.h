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

/**** QuatTypes.h - Basic type declarations ****/
#ifndef _H_QuatTypes
#define _H_QuatTypes
/*** Definitions ***/
typedef struct {float x, y, z, w;} Quat; /* Quaternion */
enum QuatPart {X, Y, Z, W};
typedef float HMatrix[4][4]; /* Right-handed, for column vectors */
typedef Quat EulerAngles;    /* (x,y,z)=ang 1,2,3, w=order code  */
#endif

