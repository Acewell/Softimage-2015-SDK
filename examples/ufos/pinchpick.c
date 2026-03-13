/****************************************************************************
 *
 * Media Illusion "PinchPick" UFO
 * 
 * Copyright (c) 3 Space Software Ltd. 1994, 1995.
 * Copyright 2008 Autodesk, Inc.  All rights reserved.  
 * Use of this software is subject to the terms of the Autodesk license agreement 
 * provided at the time of installation or download, or which otherwise accompanies 
 * this software in either electronic or hard copy form.   
 *
 ***************************************************************************/


#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#pragma warning(disable:4244)
	#pragma warning(disable:4761)
#endif
#include <GL/gl.h>
#include <GL/glu.h>

#include "ufoFunctions.h"
#include "ufoProcess.h"
#include "ufoEditor.h"

#define MAX(a,b)	    ((a)<(b) ? (b) : (a))
#define MIN(a,b)	    ((a)>(b) ? (b) : (a))
#define ILIMIT(a, x, b)    (MIN(b, MAX(a, x)))
#define  MAXIMUM(a, b, c)  ((a > b) ? ((a > c) ? a : c ) : ((b > c) ? b : c ))


enum {
    INPUT_, 
    N_RASTER_IN_
};

enum {
    OUTPUT_, 
    N_RASTER_OUT_
};

enum {
    PINCH_AMOUNT_,
    PINCH_CENTRE_,
    PINCH_RADIUS_, 
    PINCH_INTERPOLATE_,
    PINCH_COLOUR_, 
    N_PARAM_
};

enum {
    PINCH_GROUP_, 
    N_PARAM_GROUP_
};

static int number_of_instances = 0;

typedef struct {
    float x_centre, y_centre, x_effect_scaling, y_effect_scaling, amount, radius;
    float r, g, b;
} ProcessUserData;


/* code for interpolating pixels */

void GetInterpolatedPixelAlpha(ufoRaster    raster, 
			       double	    x,
			       double	    y,
			       double	    *r, 
			       double	    *g, 
			       double	    *b, 
			       double	    *a)
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
     *		0 1
     *		2 3
     */
     r0+=x*(r1-r0);r2+=x*(r3-r2);*r=r0+y*(r2-r0);
     g0+=x*(g1-g0);g2+=x*(g3-g2);*g=g0+y*(g2-g0);
     b0+=x*(b1-b0);b2+=x*(b3-b2);*b=b0+y*(b2-b0);
     a0+=x*(a1-a0);a2+=x*(a3-a2);*a=a0+y*(a2-a0);
     return;
}     
     
void GetInterpolatedPixel     (ufoRaster    raster, 
			       double	    x,
			       double	    y,
			       double	    *r, 
			       double	    *g, 
			       double	    *b)
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
     *		0 1
     *		2 3
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
				"Pinch Pick",		
				N_RASTER_IN_,		
				N_RASTER_OUT_,		
				N_PARAM_,		
				N_PARAM_GROUP_);	
								
    ufoProcessParamGroupDefine(	process_instance, 
				PINCH_GROUP_,
				"UFOPinch_PinchGroup", 
				"Pinch");


    ufoProcessRasterInDefine(   process_instance,	/* definition process instance */
				INPUT_,			/* raster index */
				"Input",		/* raster id */
				"Input",		/* raster title */
				ufoAnyCompComb);	/* works on any input */

     ufoProcessSetRasterInEdgeMode(  process_instance,	/* definition process instance */
				    INPUT_,		/* raster index */
				    ufoEdgeNoClamp);	/* don't clamp the output to the input */

     ufoProcessRasterOutDefine(  process_instance,	/* definition process instance */
				OUTPUT_,		/* raster index */
				"Output",		/* raster id */
				"Output",		/* raster title */
				ufoAnyCompComb);	/* works on any input */

    ufoProcessParamDefine(
				process_instance,	
				PINCH_AMOUNT_,		
				PINCH_GROUP_,		
				"UFOPinchAmount",		
				"Amount",		
				ufoFloatParam);

    ufoProcessSetParamLimits(
				process_instance,	/* definition process instance */
				PINCH_AMOUNT_,		/* param index */
				(ufoChannelIndex)0,			/* channel index */
				-1,1,			/* set range */
				ufoLimitsClampBoth);	/* clamp both */

    ufoProcessSetParamDefaultValue(
				process_instance,	/* definition process instance */
				PINCH_AMOUNT_,		/* param index */
				(ufoChannelIndex)0,	/* channel  */
				0.0);

    ufoProcessParamDefine(
				process_instance,	
				PINCH_RADIUS_,		
				PINCH_GROUP_,		
				"UFOPinchDiameter",		
				"Diameter",		
				ufoFloatParam);

    ufoProcessSetParamLimits(
				process_instance,	/* definition process instance */
				PINCH_RADIUS_,		/* param index */
				(ufoChannelIndex)0,	/* channel index */
				0,1,			/* set range */
				ufoLimitsClampMin);	/* clamp both */

    ufoProcessSetParamDefaultValue(
				process_instance,	/* definition process instance */
				PINCH_RADIUS_,		/* param index */
				(ufoChannelIndex)0,	/* channel  */
				1.0);


    ufoProcessParamDefine(
				process_instance, 
				PINCH_INTERPOLATE_, 
				PINCH_GROUP_, 
				"UFOPINCHInterpolate", 
				"Interpolate", 
				ufoBooleanParam);
    ufoProcessParamDefine(
				process_instance, 
				PINCH_COLOUR_, 
				PINCH_GROUP_, 
				"UFOPINCHColour", 
				"Colour", 
				ufoColourRGBParam);
				
   ufoProcessSetParamDefaultValue(
				process_instance,	/* definition process instance */
				PINCH_INTERPOLATE_,	/* param index */
				(ufoChannelIndex)0,	/* channel  */
				0.0);
				
    ufoProcessSetParamAnimAllow(
				process_instance,
				PINCH_INTERPOLATE_, 
				0);	
    
    ufoProcessParamDefine(
				process_instance,	
				PINCH_CENTRE_,		
				PINCH_GROUP_,		
				"UFOPinchCentre",		
				"Centre",		
				ufoPos3dParam);
    
    default_pos[0]=0.5;
    default_pos[1]=0.5;
    default_pos[2]=0;
    
    ufoProcessSetParamDefaultValues(
				process_instance,	/* definition process instance */
				PINCH_CENTRE_,		/* param index */
				default_pos);
   return process_instance;
}

void* ufoProcessCopyUserData(
		    void	*process_instance, 
		    void	*user_data)
{
    /* make a copy of the user data structure if it is set in the process - if it is set */
    ProcessUserData *new_data = 0;
    if(user_data)
    {
	new_data =  (ProcessUserData *)malloc(sizeof(ProcessUserData));
	memcpy(new_data, user_data, sizeof(ProcessUserData));
    }
    
    return (void *)new_data;
}

void ufoProcessDeleteUserData(
		    void	*process_instance, 
		    void	*user_data)
{
    /* free up user data - if it has been set */
    if(user_data)
	free(user_data);
}

void ufoPinchSetUpData(
    void *process_instance, 
    int	 in_editor)
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

    if(!in_editor)
	ufoProcessGetRenderScale(process_instance, &x_scale, &y_scale);
    else
    {
	x_scale = y_scale = 1;
    }
    
    R_xMin*=x_scale;
    R_xMax*=x_scale;
    R_yMin*=y_scale;
    R_yMax*=y_scale;
    
    temp_x = ufoProcessGetParamValue(process_instance, PINCH_CENTRE_, ufoPos3dChannelX);
    temp_y = ufoProcessGetParamValue(process_instance, PINCH_CENTRE_, ufoPos3dChannelY);
    
    user_data->x_centre = R_xMin + temp_x * (R_xMax - R_xMin);
    user_data->y_centre = R_yMin + temp_y * (R_yMax - R_yMin);

    temp_x=(R_yMax-R_yMin)/2;
    temp_y=(R_yMax-R_yMin)/2; /* could change this if worried about aspect ratio */
    
    user_data->radius = ufoProcessGetParamValue(process_instance, PINCH_RADIUS_, 
						ufoDefaultChannelIndex);
    
    user_data->amount = ufoProcessGetParamValue(process_instance, PINCH_AMOUNT_, 
						ufoDefaultChannelIndex);
    
    user_data->r = ufoProcessGetParamValue(process_instance, PINCH_COLOUR_, 
						ufoColourRGBChannelIndexR);
    user_data->g = ufoProcessGetParamValue(process_instance, PINCH_COLOUR_, 
						ufoColourRGBChannelIndexG);
    user_data->b = ufoProcessGetParamValue(process_instance, PINCH_COLOUR_, 
						ufoColourRGBChannelIndexB);
    
    if (fabs(user_data->radius)<1e-4) 
    {
	user_data->amount=0;
	user_data->radius=1;
    }
    user_data->x_effect_scaling=1.0/(temp_x*user_data->radius);
    user_data->y_effect_scaling=1.0/(temp_y*user_data->radius);
}

void ufoPinchDisplacement(ProcessUserData *user_data, int x, int y, float *xx, float *yy)
{
    float delta_x, delta_y, distance2, scale;
    float scaled_delta_x, scaled_delta_y;
    delta_x=x-user_data->x_centre;
    delta_y=y-user_data->y_centre;
    scaled_delta_x=delta_x*user_data->x_effect_scaling;
    scaled_delta_y=delta_y*user_data->y_effect_scaling;
   
    distance2=scaled_delta_x*scaled_delta_x+scaled_delta_y*scaled_delta_y;
    if (distance2>0 && distance2>=1)
    {
	*xx=x;
	*yy=y;
	return;
    }
    distance2=sqrt(distance2);
    if (user_data->amount<0)
	scale=1/(1-user_data->amount*(1-distance2)*distance2);
    else
	scale=1/(1-user_data->amount*(1-distance2)*(1-distance2));
	    
    *xx=user_data->x_centre+delta_x*scale;
    *yy=user_data->y_centre+delta_y*scale;
}

void GrowRect(int x, int y, ufoRectangle *rect)
{
    if (x<rect->x1) rect->x1=x;
    if (x>rect->x2) rect->x2=x;
    if (y<rect->y1) rect->y1=y;
    if (y>rect->y2) rect->y2=y;
}   

void ufoProcessCalcNeedRectangles(  void		*process_instance, 
				    ufoRectangle	*outputRect, 
				    ufoRectangle	*needRect)
{
    int x, y;
    int x1, x2, y1, y2;
    double x_scale, y_scale;
    ProcessUserData *user_data;
   
    ufoPinchSetUpData(process_instance, 0);
    
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
	
	ufoPinchDisplacement(user_data, x, y1, &xx, &yy);
	GrowRect((xx*x_scale)+(x_scale-1), yy*y_scale, needRect);
	
	ufoPinchDisplacement(user_data, x, y2, &xx, &yy);
	GrowRect((xx*x_scale)+(x_scale-1), yy*y_scale, needRect);
    }
    
    for (y=y1;y<=y2;y++)
    {
	float xx, yy;
	
	ufoPinchDisplacement(user_data, x1, y, &xx, &yy);
	GrowRect(xx*x_scale, (yy*y_scale)+(y_scale-1), needRect);
	
	ufoPinchDisplacement(user_data, x2, y, &xx, &yy);
	GrowRect(xx*x_scale, (yy*y_scale)+(y_scale-1), needRect);
    }
}

void ufoProcessCalcDefinedRectangle(void		*process_instance, 
				    ufoRectangle	*inputRect, 
				    ufoRectangle	*haveRect)
{
    int R_xMin, R_xMax, R_yMin, R_yMax;
    ufoProcessGetFullRenderRectangle(process_instance, &R_xMin,&R_yMin, &R_xMax, &R_yMax);
    
    haveRect->x1=R_xMin;
    haveRect->x2=R_xMax;
    haveRect->y1=R_yMin;
    haveRect->y2=R_yMax;
}


void ufoProcessPreRender(
                    void        *process_instance,
                    int         a,
                    int         b,
                    int         c,
                    int         d)
{
    ufoPinchSetUpData(process_instance, 0);
}

void ufoProcessRenderLine(
		    void	*process_instance, 
		    int		x1, 
		    int		x2, 
		    int		y)
{

    ufoRaster raster_in  = ufoProcessGetRasterIn(process_instance,  0);
    ufoRaster raster_out = ufoProcessGetRasterOut(process_instance,  0);
    
    int	      x;
    double amount;
    double r,g,b,a;
    int x_min, x_max, y_min, y_max;
    double x_centre,y_centre,x_effect_scaling,scaled_delta_y_squared;
    float delta_y;
    int interpolate;	   
    ProcessUserData *user_data;
    
    user_data = (ProcessUserData *)ufoProcessGetUserData(process_instance);
   
    ufoRasterGetLimits(raster_in,&x_min, &y_min, &x_max, &y_max);
    interpolate = ufoProcessGetParamValue(process_instance, PINCH_INTERPOLATE_, ufoDefaultChannelIndex);
        
    amount = user_data->amount;
         
    /* process all the pixels on the line */

    if (fabs(amount)<1e-4) 
    {
	/* 
	 * do (safe) straight copy if amount approximately zero 
	 * (saves time,  ensures no distanceortion)
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

    delta_y=y-user_data->y_centre;
    scaled_delta_y_squared=(delta_y*user_data->y_effect_scaling)*(delta_y*user_data->y_effect_scaling);
    x_centre=user_data->x_centre;
    y_centre=user_data->y_centre;
    x_effect_scaling=user_data->x_effect_scaling;
    
    for(x = x1; x <= x2; x++)
    {
    	float delta_x, scaled_delta_x;
	float distance2, scale;
	float xx,yy;
	
	delta_x=x-x_centre; 
	scaled_delta_x=delta_x*x_effect_scaling;

	distance2=scaled_delta_x*scaled_delta_x+scaled_delta_y_squared;
	if (distance2>0 && distance2<1) 
	{
	    /*
	     * only distanceort inside the unit disk.
	     * 
	     * also,  we tend to have problems at the central pixel 'cos
	     * of possible divide by zero errors. As the central pixel will
	     * always stay the same,  we just skip the distanceort
	     * 
	     */
	     
	    distance2=sqrt(distance2);
	    if (amount<0)
		scale=1/(1-amount*(1-distance2)*distance2);
	    else
		scale=1/(1-amount*(1-distance2)*(1-distance2));
	    
	    /*
	     * formulas for scale are *entirely* adhoc. In these types of distanceortion
	     * filter, the main thing is to ensure the perturbed values for x, y
	     * (xx, yy) don't go outside the unit circle. In other words,  we need
	     * distance2 * scale <=1.
	     */
	    
            xx=x_centre+delta_x*scale;
       	    yy=y_centre+delta_y*scale;
	   
	    if (xx<x_min) xx=x_min;
	    if (xx>x_max) xx=x_max;
	    if (yy<y_min) yy=y_min;
	    if (yy>y_max) yy=y_max;
	    
	    if (interpolate)       
		GetInterpolatedPixelAlpha(raster_in,  xx, yy, &r, &g, &b, &a);
	    else
	        ufoRasterGetPixelColAlpha(raster_in,  xx+.5, yy+.5, &r, &g, &b, &a);
		
	    r = distance2*user_data->r + (1-distance2)*r;         
	    g = distance2*user_data->g + (1-distance2)*g;         
	    b = distance2*user_data->b + (1-distance2)*b;
	}
	else
	    ufoRasterGetPixelColAlpha(raster_in,  x, y, &r, &g, &b, &a);
	
	         
        ufoRasterSetPixelColAlpha(raster_out,  x, y, r, g, b, a);         
    }
}

/****************************************************************************
 * Screen interaction and editor draw code
 ****************************************************************************/


typedef struct {
    int boxing;
    float x_start, y_start, x_current, y_current;
} EditorUserData;


void* ufoEditorCreate(
                ufoEditor       editor_instance, 
		void*		parent_window, 
		int*		screen_interact_groups, 
		int*		gui_groups)
{
    /*This UFO has no X Motif GUI*/
    return NULL;
}


void ufoEditorOverlayDraw(
                ufoEditor       editor_instance,
		ufoProcess      process_instance)
{
    ProcessUserData *user_data;
    EditorUserData *editor_data;  
    double v1,  v2, rx1, rx2;
    double vert[2];
    double x_size, y_size;
    GLUquadricObj *qobj; 
    
    glClearIndex(0);
//    glClear(GL_COLOR_BUFFER_BIT);
    glIndexf(ufoEditorGetOverlayIndex(editor_instance, 1));
    glColor3f(1, 1, 0);
    
    ufoPinchSetUpData(process_instance, 1);
    
    user_data = (ProcessUserData *)ufoProcessGetUserData(process_instance);
    editor_data = (EditorUserData *)ufoEditorGetUserData(editor_instance);
    
    v1=user_data->x_centre;
    v2=user_data->y_centre;
    rx1 = 20;
    rx2 = 10;
    
    ufoEditorGetPixelSize(editor_instance, &x_size, &y_size);
    rx1 /= x_size;
    rx2 /= x_size;

    /* Draw drag bounding box */   
    if(editor_data && editor_data->boxing)
    {
	glBegin(GL_LINE_LOOP);
	vert[0] = editor_data->x_start;
	vert[1] = editor_data->y_start;
	glVertex2dv(vert);
	vert[0] = editor_data->x_current;
	vert[1] = editor_data->y_start;
	glVertex2dv(vert);
	vert[0] = editor_data->x_current;
	vert[1] = editor_data->y_current;
	glVertex2dv(vert);
	vert[0] = editor_data->x_start;
	vert[1] = editor_data->y_current;
	glVertex2dv(vert);
	glEnd();
    }

    /* draw cross hair */
    glBegin(GL_LINE_LOOP);
    vert[0] = v1 -rx1;
    vert[1] = v2;
    glVertex2dv(vert);
    vert[0] = v1 +rx1;
    vert[1] = v2;
    glVertex2dv(vert);
    glEnd();

    glBegin(GL_LINE_LOOP);
    vert[0] = v1;
    vert[1] = v2 -rx1;
    glVertex2dv(vert);
    vert[0] = v1;
    vert[1] = v2 +rx1;
    glVertex2dv(vert);
    glEnd();

    /* draw circle !! */
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_SILHOUETTE);
    glPushMatrix();
    glTranslatef(v1, v2,  0.);
    gluDisk( qobj, 0., rx2, 32, 1);
    glPopMatrix();
    gluDeleteQuadric(qobj);
}


void ufoPinchPick(
                ufoEditor	    editor_instance,
		ufoProcess	    process_instance, 
		ufoEditorEventType  event_type)
{
    EditorUserData *user_data = (EditorUserData*)ufoEditorGetUserData(editor_instance);
    int n_pixels ;
    int pick_ok = 0;
    int x1, y1, x2, y2;
    double x_scale, y_scale;
    double r_agg = 0, g_agg = 0, b_agg = 0;
    int x, y;
    double r, g, b;
    
    if(event_type == ufoEditorRelease)
    {
	/*get average of all pixels in picked raster*/
	ufoRaster raster = ufoEditorGetRasterViewed(editor_instance);
	if(raster)
	{
	    
	    ufoProcessGetRenderScale(process_instance, &x_scale, &y_scale);
	    
	    x1 = (int)(floor(user_data->x_start*x_scale));
	    y1 = (int)(floor(user_data->y_start*y_scale));
	    x2 = (int)(ceil(user_data->x_current*x_scale));
	    y2 = (int)(ceil(user_data->y_current*y_scale));
	
	    if(ufoRasterClipLimits(raster, &x1, &y1, &x2, &y2))
	    {
		for(y = y1; y <= y2; y++)
		    for(x = x1; x <= x2; x++)
		    {
			ufoRasterGetPixelCol(raster, x, y, &r, &g, &b);
			r_agg += r; g_agg += g; b_agg += b;
		    }
		n_pixels = (x2-x1+1)*(y2-y1+1);
		r_agg /= n_pixels;
		b_agg /= n_pixels;
		g_agg /= n_pixels;
		
		ufoProcessSetParamValue(process_instance, PINCH_COLOUR_, ufoColourRGBChannelIndexR, r_agg);
		ufoProcessSetParamValue(process_instance, PINCH_COLOUR_, ufoColourRGBChannelIndexG, g_agg);
		ufoProcessSetParamValue(process_instance, PINCH_COLOUR_, ufoColourRGBChannelIndexB, b_agg);

		pick_ok = 1;
	    }
	}
    }
    ufoEditorDraw(editor_instance);
    
    if(pick_ok)
    {
	int edited_params[1];
	edited_params[0] = PINCH_COLOUR_;
	ufoEditorNotifyEdited(editor_instance, edited_params, 1, event_type);
    }
}



void ufoEditorMouseDown(
                ufoEditor       editor_instance,
		ufoProcess			a, 
		double				x, 
		double				y, 
		ufoMouseEvent*		b)
{
    EditorUserData *user_data;
    
    user_data = (EditorUserData *)malloc(sizeof(EditorUserData));
	
    ufoEditorSetUserData(editor_instance, (void*)user_data);
    user_data->x_start  =  x;
    user_data->y_start  =  y;
    user_data->x_current  =  x;
    user_data->y_current  =  y;
    user_data->boxing  =  1;
    
}


void ufoEditorMouseUp(
                ufoEditor       editor_instance,
		ufoProcess      process_instance, 
		double				x, 
		double				y, 
		ufoMouseEvent*		a)
{
    EditorUserData *user_data;
    user_data = (EditorUserData *)ufoEditorGetUserData(editor_instance);

    user_data->x_current  =  x;
    user_data->y_current  =  y;
    user_data->boxing	  =  0;
    
    ufoPinchPick(editor_instance, process_instance, ufoEditorRelease);

    /*reset user data*/
    free(user_data);
    
}


void ufoEditorMouseDrag(
                ufoEditor       editor_instance,
		ufoProcess      process_instance, 
		double			x, 
		double			y, 
		ufoMouseEvent*	a)
{
    EditorUserData *user_data;
    user_data = (EditorUserData *)ufoEditorGetUserData(editor_instance);

    user_data->x_current    =  x;
    user_data->y_current    =  y;

    ufoPinchPick(editor_instance, process_instance, ufoEditorDrag);
}


/*******************************************************************************
 * End of file pinchpick.c
 ******************************************************************************/

