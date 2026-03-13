/*******************************************************************************
 * 
 * Media Illusion "Swirl" UFO
 * 
 * David Franklin 23/5/95
 * 
 * Copyright (c) 3 Space Software Ltd. 1994, 1995.
 * Copyright 2008 Autodesk, Inc.  All rights reserved.  
 * Use of this software is subject to the terms of the Autodesk license agreement 
 * provided at the time of installation or download, or which otherwise accompanies 
 * this software in either electronic or hard copy form.   
 * 
 ******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>

#ifdef WIN32
	#pragma warning(disable:4244)
	#pragma warning(disable:4761)
#endif

#include "ufoFunctions.h"
#include "ufoProcess.h"

#define MAX(a,b)			((a)<(b) ? (b) : (a))
#define MIN(a,b)			((a)>(b) ? (b) : (a))
#define ILIMIT(a, x, b)    (MIN(b, MAX(a, x)))
#define  MAXIMUM(a, b, c)  ((a > b) ? ((a > c) ? a : c ) : ((b > c) ? b : c ))

#define TABLESIZE 1024		/* size of sin lookup table. MUST be a power of 2 */

enum {
	INPUT_, 
	N_RASTER_IN_
};

enum {
	OUTPUT_, 
	N_RASTER_OUT_
};

enum {
	SWIRL_AMOUNT_,
	SWIRL_CENTRE_,
	SWIRL_RADIUS_, 
	SWIRL_INTERPOLATE_, 
	N_PARAM_
};

enum {
	SWIRL_GROUP_, 
	N_PARAM_GROUP_
};

typedef struct {
	float x_centre, y_centre, x_effect_scaling, y_effect_scaling, amount, radius;
} ProcessUserData;

static int number_of_instances = 0;

static double *sinTable = NULL; 

void GetInterpolatedPixelAlpha(ufoRaster	raster, 
							   double		x,
							   double		y,
							   double		*r, 
							   double		*g, 
							   double		*b, 
							   double		*a)
{
	double r0, r1, r2, r3, g0, g1, g2, g3;
	double b0, b1, b2, b3, a0, a1, a2, a3;
	int ix, iy;
	
	ix=floor(x);x-=ix;
	iy=floor(y);y-=iy;
	
	if (x<.0001 && y<.0001)
	{
		/*
		 * no need to interpolate
		 */
		ufoRasterGetPixelColAlpha(raster, ix, iy, r, g, b, a);
		return;
	}
	
	ufoRasterGetPixelColAlpha(raster, ix, iy, &r0, &g0, &b0, &a0);						   
	ufoRasterGetPixelColAlpha(raster, ix+1, iy, &r1, &g1, &b1, &a1);					   
	ufoRasterGetPixelColAlpha(raster, ix, iy+1, &r2, &g2, &b2, &a2);					   
	ufoRasterGetPixelColAlpha(raster, ix+1, iy+1, &r3, &g3, &b3, &a3);					   
	/*
	 * r0, r1, r2, r3 are red values at corners of pixel,  arranged
	 * like 
	 *			0 1
	 *			2 3
	 */
	 r0+=x*(r1-r0);r2+=x*(r3-r2);*r=r0+y*(r2-r0);
	 g0+=x*(g1-g0);g2+=x*(g3-g2);*g=g0+y*(g2-g0);
	 b0+=x*(b1-b0);b2+=x*(b3-b2);*b=b0+y*(b2-b0);
	 a0+=x*(a1-a0);a2+=x*(a3-a2);*a=a0+y*(a2-a0);
	 return;
}	  
	 
void GetInterpolatedPixel	  (ufoRaster	raster, 
							   double		x,
							   double		y,
							   double		*r, 
							   double		*g, 
							   double		*b)
{
	double r0, r1, r2, r3, g0, g1, g2, g3;
	double b0, b1, b2, b3;
	int ix, iy;
	
	ix=floor(x);x-=ix;
	iy=floor(y);y-=iy;
	
	if (x<.0001 && y<.0001)
	{
		/*
		 * no need to interpolate
		 */
		ufoRasterGetPixelCol(raster, ix, iy, r, g, b);
		return;
	}
	
	ufoRasterGetPixelCol(raster, ix, iy, &r0, &g0, &b0);						   
	ufoRasterGetPixelCol(raster, ix+1, iy, &r1, &g1, &b1);						   
	ufoRasterGetPixelCol(raster, ix, iy+1, &r2, &g2, &b2);						   
	ufoRasterGetPixelCol(raster, ix+1, iy+1, &r3, &g3, &b3);					   
	/*
	 * r0, r1, r2, r3 are red values at corners of pixel,  arranged
	 * like 
	 *			0 1
	 *			2 3
	 */
	 r0+=x*(r1-r0);r2+=x*(r3-r2);*r=r0+y*(r2-r0);
	 g0+=x*(g1-g0);g2+=x*(g3-g2);*g=g0+y*(g2-g0);
	 b0+=x*(b1-b0);b2+=x*(b3-b2);*b=b0+y*(b2-b0);
	 return;
}	


ufoProcess ufoProcessDefine(void)
{	 
	ufoProcess process_instance;
	double default_pos[3];

   process_instance =	ufoProcessCreate(
								"Swirl",				
								N_RASTER_IN_,			
								N_RASTER_OUT_,			
								N_PARAM_,				
								N_PARAM_GROUP_);		
								
	ufoProcessParamGroupDefine( process_instance, 
								SWIRL_GROUP_,
								"UFOSwirl_SwirlGroup", 
								"Swirl");

	ufoProcessRasterInDefine(	process_instance,		/* definition process instance */
								INPUT_, 				/* raster index */
								"Input",				/* raster id */
								"Input",				/* raster title */
								ufoAnyCompComb);		/* works on any input */
								
	ufoProcessSetRasterInEdgeMode(	process_instance,	/* definition process instance */
									INPUT_, 			/* raster index */
									ufoEdgeNoClamp);	/* don't clamp the output to the input */
								
	ufoProcessRasterOutDefine(	process_instance,		/* definition process instance */
								OUTPUT_,				/* raster index */
								"Output",				/* raster id */
								"Output",				/* raster title */
								ufoAnyCompComb);		/* works on any input */

	/* Direction is in degrees - this should be a dial on the interface */

	ufoProcessParamDefine(
								process_instance,		
								SWIRL_AMOUNT_,			
								SWIRL_GROUP_,			
								"UFOSwirlAmount",				
								"Amount",				
								ufoFloatParam);

	ufoProcessSetParamLimits(
								process_instance,		/* definition process instance */
								SWIRL_AMOUNT_,			/* param index */
								0,						/* channel index */
								-1,1,					/* set range */
								ufoLimitsClampNone);	/* don't clamp */

	ufoProcessSetParamDefaultValue(
								process_instance,		/* definition process instance */
								SWIRL_AMOUNT_,			/* param index */
								0,						/* channel	*/
								0.0);					/* value */

	ufoProcessParamDefine(
								process_instance,		
								SWIRL_RADIUS_,			
								SWIRL_GROUP_,			
								"UFOSwirlRadius",				
								"Radius",				
								ufoFloatParam);

	ufoProcessSetParamLimits(
								process_instance,		/* definition process instance */
								SWIRL_RADIUS_,			/* param index */
								0,						/* channel index */
								0,1,					/* set range */
								ufoLimitsClampMin); 	/* clamp min */

	ufoProcessSetParamDefaultValue(
								process_instance,		/* definition process instance */
								SWIRL_RADIUS_,			/* param index */
								0,						/* channel	*/
								1.0);					/* value */

	ufoProcessParamDefine(
								process_instance, 
								SWIRL_INTERPOLATE_, 
								SWIRL_GROUP_, 
								"UFOSwirlInterpolate", 
								"Interpolate", 
								ufoBooleanParam);
								
	ufoProcessSetParamAnimAllow(
								process_instance,
								SWIRL_INTERPOLATE_, 
								0); 					/* can't animate intepolation */
						

	
	ufoProcessParamDefine(
								process_instance,		
								SWIRL_CENTRE_,			
								SWIRL_GROUP_,			
								"UFOSwirlCentre",				
								"Centre",				
								ufoPos3dParam);
	
	default_pos[0]=0.5;
	default_pos[1]=0.5;
	default_pos[2]=0;
	
	ufoProcessSetParamDefaultValues(
								process_instance,		/* definition process instance */
								SWIRL_CENTRE_,			/* param index */
								default_pos);
   return process_instance;
}

void* ufoProcessCopyUserData(
					void		*process_instance, 
					void		*user_data)
{
	/* make a copy of the user data structure if it is set in the process - if it is set */
	ProcessUserData *new_data = 0;
	if(user_data)
	{
		new_data =	(ProcessUserData *)malloc(sizeof(ProcessUserData));
		memcpy(new_data, user_data, sizeof(ProcessUserData));
	}
	
	return (void *)new_data;
}

void ufoProcessDeleteUserData(
					void		*process_instance, 
					void		*user_data)
{
	/* free up user data - if it has been set */
	if(user_data)
		free(user_data);
}

/*
 * ufoSwirlSetUpData creates all the scaling variables for rendering the
 * effect, as well as getting all the parameter values for this frame.
 * 
 * It also creates the sin lookup table,  if it doesn't already exist.
 */

void ufoSwirlSetUpData(void *process_instance)
{
	ProcessUserData *user_data;
	double x_scale, y_scale;
	int R_xMin, R_xMax, R_yMin, R_yMax;
	float temp_x, temp_y;
	
	
	user_data = (ProcessUserData *)ufoProcessGetUserData(process_instance);
	if(!user_data)
	{
		/* user data has not been set yet - so construct it and set it*/
		user_data = (ProcessUserData *)malloc(sizeof(ProcessUserData));
		ufoProcessSetUserData(process_instance, (void*)user_data);
	}
	ufoProcessGetFullRenderRectangle(process_instance, &R_xMin,&R_yMin, &R_xMax, &R_yMax);
	ufoProcessGetRenderScale(process_instance, &x_scale, &y_scale);
	
	R_xMin*=x_scale;
	R_xMax*=x_scale;
	R_yMin*=y_scale;
	R_yMax*=y_scale;
	
	temp_x = ufoProcessGetParamValue(process_instance, SWIRL_CENTRE_, ufoPos3dChannelX);
	temp_y = ufoProcessGetParamValue(process_instance, SWIRL_CENTRE_, ufoPos3dChannelY);
	
	user_data->x_centre = R_xMin + temp_x * (R_xMax - R_xMin);
	user_data->y_centre = R_yMin + temp_y * (R_yMax - R_yMin);

	temp_x=(R_yMax-R_yMin)/2;
	temp_y=(R_yMax-R_yMin)/2; /* could change this if worried about aspect ratio */
	
	user_data->radius = ufoProcessGetParamValue(process_instance, SWIRL_RADIUS_, 
												ufoDefaultChannelIndex);
	
	user_data->amount = ufoProcessGetParamValue(process_instance, SWIRL_AMOUNT_, 
												ufoDefaultChannelIndex)*TABLESIZE;
	
	if (fabs(user_data->radius)<1e-4) 
	{
		user_data->amount=0;
		user_data->radius=1;
	}
	   
	user_data->x_effect_scaling=1.0/(temp_x*user_data->radius);
	user_data->y_effect_scaling=1.0/(temp_y*user_data->radius);
	
	/*
	 * ensure the sinTable exists
	 */
	 
	if (!sinTable)
	{
		int i;
		
		sinTable=(double *)malloc(sizeof(double)*(TABLESIZE+1));
			
		/* construct sin look up table */
		for (i=0;i<TABLESIZE+1;i++) 
			sinTable[i]=sin(2*i*M_PI/TABLESIZE);
   }
}

void ufoProcessPreRender(
					void		*process_instance,
					int 		x1,
					int 		y1,
					int 		x2,
					int 		y2)
{
	ufoSwirlSetUpData(process_instance);
}		

/*
 * ufoSwirlDisplacement calculates the displaced coords (xx, yy) for the input
 * coords (x, y). It's only used for calculating the bounding rectangles;
 * a slightly faster method using the fact that y is constant is used for the
 * scan line rendering. 
 * 
 * Note that the effect is rendered using the "map from destination to source"
 * paradigm, so Output(x, y)=Input(xx, yy).
 */
 
void ufoSwirlDisplacement(ProcessUserData *user_data, int x, int y, float *xx, float *yy)
{
	float delta_x, delta_y, distance2, rotan, interp, s, c;
	float scaled_delta_x, scaled_delta_y;
	int index;
	delta_x=x-user_data->x_centre;
	delta_y=y-user_data->y_centre;
	scaled_delta_x=delta_x*user_data->x_effect_scaling;
	scaled_delta_y=delta_y*user_data->y_effect_scaling;
   
	distance2=scaled_delta_x*scaled_delta_x+scaled_delta_y*scaled_delta_y;
	if (distance2>=1)
	{
		*xx=x;
		*yy=y;
		return;
	}
	distance2=1.0-sqrt(distance2);
	rotan=user_data->amount*distance2*distance2;
	index=floor(rotan); interp=rotan-index;
	
	index=index & (TABLESIZE-1);
	s=sinTable[index]+interp*(sinTable[index+1]-sinTable[index]);
	
	index=(index+TABLESIZE/4) & (TABLESIZE-1);
	c=sinTable[index]+interp*(sinTable[index+1]-sinTable[index]);
	
	*xx=user_data->x_centre+delta_x*c-delta_y*s;
	*yy=user_data->y_centre+delta_y*c+delta_x*s; 
}

/*
 * GrowRect grows rect (if necessary) so that it contains the point
 * (x, y).
 */
void GrowRect(int x, int y, ufoRectangle *rect)
{
	if (x<rect->x1) rect->x1=x;
	if (x>rect->x2) rect->x2=x;
	if (y<rect->y1) rect->y1=y;
	if (y>rect->y2) rect->y2=y;
}

/*
 * ufoProcessCalcNeedRectangles calculates the needed rectangle by finding the 
 * minimum rectangle that holds the pre-image of the boundary of outputRect under
 * the effect. 
 */

void ufoProcessCalcNeedRectangles(	void				*process_instance, 
									ufoRectangle		*outputRect, 
									ufoRectangle		*needRect)
{
	int x, y;
	int x1, x2, y1, y2;
	double x_scale, y_scale;
	ProcessUserData *user_data;
   
	ufoSwirlSetUpData(process_instance);
	
	user_data = (ProcessUserData *)ufoProcessGetUserData(process_instance);
	ufoProcessGetRenderScale(process_instance, &x_scale, &y_scale);
	x1=outputRect->x1*x_scale;
	x2=outputRect->x2*x_scale;
	y1=outputRect->y1*y_scale;
	y2=outputRect->y2*y_scale;
  
	needRect->x1=1e9;
	needRect->x2=-1e9;
	needRect->y1=1e9;
	needRect->y2=-1e9;
	
	x_scale=1/x_scale;
	y_scale=1/y_scale;
	
	for (x=x1;x<=x2;x++)
	{
		float xx, yy;
		
		ufoSwirlDisplacement(user_data, x, y1, &xx, &yy);
		GrowRect((xx*x_scale)+(x_scale-1), yy*y_scale, needRect);
		
		ufoSwirlDisplacement(user_data, x, y2, &xx, &yy);
		GrowRect((xx*x_scale)+(x_scale-1), yy*y_scale, needRect);
	}
	
	for (y=y1;y<=y2;y++)
	{
		float xx, yy;
		
		ufoSwirlDisplacement(user_data, x1, y, &xx, &yy);
		GrowRect(xx*x_scale, (yy*y_scale)+(y_scale-1), needRect);
		
		ufoSwirlDisplacement(user_data, x2, y, &xx, &yy);
		GrowRect(xx*x_scale, (yy*y_scale)+(y_scale-1), needRect);
	}
	
   return;	 
}

/*
 * ufoProcessCalcNeedRectangles calculates the defined rectangle by finding the 
 * minimum rectangle that holds the post-image of the boundary of inputRect 
 * under the distortion.
 */
void ufoProcessCalcDefinedRectangle(void				*process_instance, 
									ufoRectangle		*inputRect, 
									ufoRectangle		*haveRect)
{
	/*
	 * the inverse of the swirl UFO is just the normal process but with
	 * amount -> -amount. So this is essentially the same as for ...NeedRectangles
	 * after reversing amount...
	 */
	 
	float temp_amount;
	ProcessUserData *user_data;
	int x, y;
	int x1, x2, y1, y2;
	double x_scale, y_scale;
	
	ufoSwirlSetUpData(process_instance);
	user_data = (ProcessUserData *)ufoProcessGetUserData(process_instance);
	temp_amount=user_data->amount;
	user_data->amount=-temp_amount; /* lie (for now) about what the amount is */
	
	ufoProcessGetRenderScale(process_instance, &x_scale, &y_scale);
	x1=inputRect->x1*x_scale;
	x2=inputRect->x2*x_scale;
	y1=inputRect->y1*y_scale;
	y2=inputRect->y2*y_scale;
  
	haveRect->x1=1e9;
	haveRect->x2=-1e9;
	haveRect->y1=1e9;
	haveRect->y2=-1e9;
	
	x_scale=1/x_scale;
	y_scale=1/y_scale;
	
	for (x=x1;x<=x2;x++)
	{
		float xx, yy;
		
		ufoSwirlDisplacement(user_data, x, y1, &xx, &yy);
		GrowRect((xx*x_scale)+(x_scale-1), yy*y_scale, haveRect);
		
		ufoSwirlDisplacement(user_data, x, y2, &xx, &yy);
		GrowRect((xx*x_scale)+(x_scale-1), yy*y_scale, haveRect);
	}
	
	for (y=y1;y<=y2;y++)
	{
		float xx, yy;
		
		ufoSwirlDisplacement(user_data, x1, y, &xx, &yy);
		GrowRect(xx*x_scale, (yy*y_scale)+(y_scale-1), haveRect);
		
		ufoSwirlDisplacement(user_data, x2, y, &xx, &yy);
		GrowRect(xx*x_scale, (yy*y_scale)+(y_scale-1), haveRect);
	}
	
	user_data->amount=temp_amount; /* reset the amount to the correct value */
	
	return; 	 
}

								
								
 
void ufoProcessRenderLine(
					void		*process_instance, 
					int 		x1, 
					int 		x2, 
					int 		y)
{

	ufoRaster raster_in  = ufoProcessGetRasterIn(process_instance,	0);
	ufoRaster raster_out = ufoProcessGetRasterOut(process_instance,  0);
	 
	int 	  x;
	double amount;
	double r,g,b,a;
	ProcessUserData *user_data;
	double *sinTab=sinTable;
	int x_min, x_max, y_min, y_max;
	double x_centre,y_centre, x_effect_scaling, scaled_delta_y_squared;
	float delta_y;
	int interpolate;
	
	user_data = (ProcessUserData *)ufoProcessGetUserData(process_instance);
	
	ufoRasterGetLimits(raster_in,&x_min, &y_min, &x_max, &y_max);
	interpolate = ufoProcessGetParamValue(process_instance, SWIRL_INTERPOLATE_, ufoDefaultChannelIndex);
   
	amount = user_data->amount;
	
	/* process all the pixels on the line */

   
	if (fabs(amount)<1e-4) 
	{
		/* 
		 * do straight copy if amount approximately zero 
		 * (saves time,  ensures no distortion)
		 */
		
		if (y<y_min || y>y_max) 
		{
			for (x=x1;x<=x2;x++) ufoRasterSetPixelColAlpha(raster_out, x, y, 0, 0, 0, 0);
			return;
		}
		
		for (x=x1;x<x_min;x++) ufoRasterSetPixelColAlpha(raster_out, x, y, 0, 0, 0, 0);
		for (x=x_max+1;x<=x2;x++) ufoRasterSetPixelColAlpha(raster_out, x, y, 0, 0, 0, 0);
		
		if (x1<x_min) x1=x_min;
		if (x2>x_max) x2=x_max;
		for (x = x1; x <= x2; x++)
		{
			ufoRasterGetPixelColAlpha(raster_in,  x, y, &r, &g, &b, &a);
			ufoRasterSetPixelColAlpha(raster_out,  x, y, r, g, b, a);  
		}
		return;
	}
	
	/*
	 * if we've got to here,  we have to do the swirl calculations...
	 */
	
	delta_y=y-user_data->y_centre;
	scaled_delta_y_squared=(delta_y*user_data->y_effect_scaling)*(delta_y*user_data->y_effect_scaling);
	x_centre=user_data->x_centre;
	y_centre=user_data->y_centre;
	x_effect_scaling=user_data->x_effect_scaling;


	for(x = x1; x <= x2; x++)
	{
		float delta_x;
		double scaled_delta_x,s,c;
		float distance2, rotan, interp;
		int index;
		float xx,yy;
		
		delta_x=x-x_centre; 
		scaled_delta_x=delta_x*x_effect_scaling;

		distance2=scaled_delta_x*scaled_delta_x+scaled_delta_y_squared;
		if (distance2<1) /* only swirl inside the unit disk */
		{
			distance2=1.0-sqrt(distance2);
			rotan=amount*distance2*distance2;
			index=floor(rotan); interp=rotan-index;
			
			index=index & (TABLESIZE-1);
			s=sinTab[index]+interp*(sinTab[index+1]-sinTab[index]);
			
			index=(index+TABLESIZE/4) & (TABLESIZE-1);
			c=sinTab[index]+interp*(sinTab[index+1]-sinTab[index]);
			
			xx=x_centre+delta_x*c-delta_y*s;
			yy=y_centre+delta_y*c+delta_x*s;
			if (xx<x_min) xx=x_min;
			if (xx>x_max) xx=x_max;
			if (yy<y_min) yy=y_min;
			if (yy>y_max) yy=y_max;
			
			if (interpolate)	   
				GetInterpolatedPixelAlpha(raster_in,  xx, yy, &r, &g, &b, &a);
			else
				ufoRasterGetPixelColAlpha(raster_in,  xx+.5, yy+.5, &r, &g, &b, &a);
		}
		else	
		{
			if ( x < x_min || x > x_max || y < y_min || y > y_max )
			{
				r = g = b = a = 0.0;
			}
			else
				ufoRasterGetPixelColAlpha(raster_in,  x, y, &r, &g, &b, &a);
		}
		
		ufoRasterSetPixelColAlpha(raster_out,  x, y, r, g, b, a);		   
	}
}

