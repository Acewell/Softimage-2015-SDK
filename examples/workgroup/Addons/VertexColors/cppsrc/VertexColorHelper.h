//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

#ifndef _VERTEX_COLOR_HELPER_H_
#define _VERTEX_COLOR_HELPER_H_

void RGBA2HLSA ( double r, 
					double g, 
					double b, 
					double a, 
					double* hue,
					double* lum,
					double* sat,
					double* alpha );



void HLSA2RGBA ( double hue, 
				double lum, 
				double sat, 
				double alpha, 
				double *r,
				double *g,
				double *b,
				double *a );
#endif
