/*******************************************************************************
 * 
 * Media Illusion "New Colour Mix" UFO
 * 
 * Dominic Jackson
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

#include "ufoFunctions.h"
#include "ufoProcess.h"



enum {
    INPUT_, 
    N_RASTER_IN_
};

enum {
    OUTPUT_, 
    N_RASTER_OUT_
};

enum {
    MIX_COLOUR_, 
    MIX_LEVEL_, 
    MIX_TYPE_, 
    MIX_FLOAT_, 
    N_PARAM_
};

enum {
    COLOUR_GROUP_, 
    MIX_GROUP_, 
    N_PARAM_GROUP_
};

enum {
    MIX_UP_, 
    MIX_DOWN_, 
    MIX_RANDOM_, 
    N_MIX_TYPES_
};




typedef struct {
    double	mix_col_[3];
    double	mix1_;
    double	mix2_;
    int		opt_r_;
    int		opt_g_;
    int		opt_b_;
    int		opt_mix1_;
    int		opt_mix2_;
} ProcessUserData;


static int number_of_instances = 0;



ufoProcess ufoProcessDefine(void)
{    
    ufoProcess process_instance;
    double default_colour[3];

    /* create pixel combination arrays */
    const int	    number_combinations = 2;
    ufoPixelType    input_combinations[N_RASTER_IN_][2] = 
		    {
			{ufoRGB8PixelType, ufoRGBA8PixelType}, 
		    };
    
    ufoPixelType    output_combinations[N_RASTER_OUT_][2] = 
		    {
			{ufoRGB8PixelType, ufoRGBA8PixelType}, 
		    };
		    
    char *mix_type_enum_table[N_MIX_TYPES_];    
    
    /* build enum param table for enum type definition */
    mix_type_enum_table[MIX_UP_]     = "Mix Up";
    mix_type_enum_table[MIX_DOWN_]   = "Mix Down";
    mix_type_enum_table[MIX_RANDOM_] = "Mix Random";
    
    
    process_instance =	ufoProcessCreate(
				"Colour Mix",		/* process title */
				N_RASTER_IN_,		/* number of inputs */
				N_RASTER_OUT_,		/* number of outputs */
				N_PARAM_,		/* number of parameters */
				N_PARAM_GROUP_);	/* number of parameter groups */

    ufoProcessParamGroupDefine(	process_instance, 
				COLOUR_GROUP_, 
				"UFOColourMix_Colour", 
				"Mix Colour");
	
    ufoProcessParamGroupDefine(	process_instance, 
				MIX_GROUP_, 
				"UFOColourMix_Setup", 
				"Mix Setup");

    ufoProcessRasterInDefine(   process_instance,	/* definition process instance */
				INPUT_,			/* raster index */
				"Input",		/* raster id */
				"Input",		/* raster title */
				ufoRGBCompComb);	/* works on RGB input */
				
    ufoProcessRasterOutDefine(  process_instance,	/* definition process instance */
				OUTPUT_,		/* raster index */
				"Output",		/* raster id */
				"Output",		/* raster title */
				ufoRGBCompComb);	/* works on RGB input */

    /* define mix level */
    ufoProcessParamDefine(
				process_instance,	/* definition process instance */
				MIX_LEVEL_,		/* param index */
				MIX_GROUP_,		/* param group */
				"MixLevel",		/* param id */
				"Mix Level",		/* param title */
				ufoNormalisedParam);

    /* set default animation */
    ufoProcessSetParamDefaultKey(
				process_instance,	/* definition process instance */
				MIX_LEVEL_,		/* param index */
				0,			/* channel index */
				0.0,			/* key value */
				1);			/* time */
    ufoProcessSetParamDefaultKey(
				process_instance,	/* definition process instance */
				MIX_LEVEL_,		/* param index */
				0,			/* channel index */
				1.0,			/* key value */
				10);			/* time */

    /* define enumerated parameter for mix type */
    ufoProcessEnumParamDefine(
				process_instance,	/* definition process instance */
				MIX_TYPE_,		/* param index */
				MIX_GROUP_,		/* param group */
				"MixType",		/* param id */
				"Mix Type",		/* param title */
				N_MIX_TYPES_,		/* number of values in enumeration */
				mix_type_enum_table);	/* enumeration text table */

    /* dont allow animation of mix type */
    ufoProcessSetParamAnimAllow(
				process_instance,	/* definition process instance */
				MIX_TYPE_,		/* param index */
				0);

    /* define mix colour */
    ufoProcessParamDefine(
				process_instance,	/* definition process instance */
				MIX_COLOUR_,		/* param index */
				COLOUR_GROUP_,		/* param group */
				"MixColour",		/* param id */
				"Mix Colour",		/* param title */
				ufoColourRGBParam);

    /* set a default purple-ish colour */
    default_colour[0] = 0.8;
    default_colour[1] = 0.2;
    default_colour[2] = 1.0;
    ufoProcessSetParamDefaultValues(
				process_instance,	/* definition process instance */
				MIX_COLOUR_,		/* param index */
				default_colour);

    /* define un-used float to test interface */
    ufoProcessParamDefine(
				process_instance,	/* definition process instance */
				MIX_FLOAT_,		/* param index */
				MIX_GROUP_,		/* param group */
				"MixFloat",		/* param id */
				"Mix Float",		/* param title */
				ufoFloatParam);

    /* set limits */
    ufoProcessSetParamLimits(
				process_instance,	/* definition process instance */
				MIX_FLOAT_,		/* param index */
				0,			/* channel index */
				0.01, 10,		/* set range */
				ufoLimitsClampMin);	/* clamp min value only */

    /* set default value */
    ufoProcessSetParamDefaultValue(
				process_instance,	/* definition process instance */
				MIX_FLOAT_,		/* param index */
				0,			/* channel index */
				1.0);
    
    /* set up two supported pixel type conbinations:
     * the first to support RGB 8 bit on the input and output
     * the second to support RGBA 8 bit on the input and output
     */


    ufoProcessSetPixelTypeCombinations(
				process_instance,
				number_combinations, 
				&input_combinations[0][0],
				&output_combinations[0][0], 
				0);
				
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


void ufoProcessPreRender(
		    void	*process_instance, 
		    int		x1, 
		    int		y1, 
		    int		x2, 
		    int		y2)
{
    /* get parameter values into local storage to save on calculating each line */
    ProcessUserData *user_data;
    double	    mix_level;
    int		    mix_type;
    
    user_data = (ProcessUserData *)ufoProcessGetUserData(process_instance);
    if(!user_data)
    {
	/* user data has not been set yet - so construct it and set it*/
	user_data = (ProcessUserData *)malloc(sizeof(ProcessUserData));
	ufoProcessSetUserData(process_instance, (void*)user_data);
    }
    
    /* set user data values to be used when rendering */

    mix_level = ufoProcessGetParamValue(process_instance, MIX_LEVEL_, ufoDefaultChannelIndex);
    mix_type  = (int)ufoProcessGetParamValue(process_instance, MIX_TYPE_, ufoDefaultChannelIndex);
    
    ufoProcessGetParamValues(process_instance, MIX_COLOUR_, user_data->mix_col_);
    
    switch (mix_type)
    {
	case MIX_DOWN_:
	    user_data->mix1_ = 1 - mix_level;
	    break;
	case MIX_UP_:
	default:
	    user_data->mix1_ = mix_level;
	    break;
    }
    user_data->mix2_ = 1 - user_data->mix1_;
    
    /* calculate interger versions of floating point values read */
    user_data->opt_r_    = (int)rint(user_data->mix_col_[0] * ufoComp8Max);
    user_data->opt_g_    = (int)rint(user_data->mix_col_[1] * ufoComp8Max);
    user_data->opt_b_    = (int)rint(user_data->mix_col_[2] * ufoComp8Max);
    user_data->opt_mix1_ = (int)rint(user_data->mix1_ *(ufoComp8Max+1));
    user_data->opt_mix2_ = (int)rint(user_data->mix2_ *(ufoComp8Max+1));
    
}




void ufoProcessRenderLine(
		    void	*process_instance, 
		    int		x1, 
		    int		x2, 
		    int		y)
{
    ufoRaster raster_in  = ufoProcessGetRasterIn(process_instance,  0);
    ufoRaster raster_out = ufoProcessGetRasterOut(process_instance,  0);
    ProcessUserData *user_data;
    
    int	      x;
    
    double r, g, b;
    int opt;
    ufoPixelType raster_in_type;
    ufoPixelType raster_out_type;

    /* get user data with parameter values */
    user_data = (ProcessUserData *)ufoProcessGetUserData(process_instance);
        
    /* attempt to perform optimised render on RGB 8 bit or RGBA 8 bit
     * get input and output raster types
     */
    opt = 0;
    raster_in_type  = ufoRasterGetPixelType(raster_in);
    raster_out_type = ufoRasterGetPixelType(raster_out);
    
    if(raster_in_type == raster_out_type)
    {
	if(raster_in_type == ufoRGB8PixelType)
	{
	    /* get pointers for input and output rasters at start of line;
	     * NB see ufoRaster.h for ufoPixelRGB8 definition
	     */
	    ufoPixelRGB8 *in_pixel_ptr  = (ufoPixelRGB8 *)ufoRasterGetPixelAddress(raster_in, x1, y);
	    ufoPixelRGB8 *out_pixel_ptr = (ufoPixelRGB8 *)ufoRasterGetPixelAddress(raster_out, x1, y);

	    for (x = x1; x <= x2; x++)
	    {
		/* perform integer based mix calculation directly into output pixel buffer */
		out_pixel_ptr->red_   = (user_data->opt_r_*user_data->opt_mix1_ + in_pixel_ptr->red_  *user_data->opt_mix2_) >> ufoComp8Bits;
		out_pixel_ptr->green_ = (user_data->opt_g_*user_data->opt_mix1_ + in_pixel_ptr->green_*user_data->opt_mix2_) >> ufoComp8Bits;
		out_pixel_ptr->blue_  = (user_data->opt_b_*user_data->opt_mix1_ + in_pixel_ptr->blue_ *user_data->opt_mix2_) >> ufoComp8Bits;
		
		in_pixel_ptr++;
		out_pixel_ptr++;
	    }
	
	    opt = 1;
	}
	else if(raster_in_type == ufoRGBA8PixelType)
	{
	    /* get pointers for input and output rasters at start of line;
	     * NB see ufoRaster.h for ufoPixelRGB8 definition
	     */
	    ufoPixelRGBA8 *in_pixel_ptr  = (ufoPixelRGBA8 *)ufoRasterGetPixelAddress(raster_in, x1, y);
	    ufoPixelRGBA8 *out_pixel_ptr = (ufoPixelRGBA8 *)ufoRasterGetPixelAddress(raster_out, x1, y);

	    for (x = x1; x <= x2; x++)
	    {
		/* perform integer based mix calculation directly into output pixel buffer */
		out_pixel_ptr->red_   = (user_data->opt_r_*user_data->opt_mix1_ + in_pixel_ptr->red_  *user_data->opt_mix2_) >> ufoComp8Bits;
		out_pixel_ptr->green_ = (user_data->opt_g_*user_data->opt_mix1_ + in_pixel_ptr->green_*user_data->opt_mix2_) >> ufoComp8Bits;
		out_pixel_ptr->blue_  = (user_data->opt_b_*user_data->opt_mix1_ + in_pixel_ptr->blue_ *user_data->opt_mix2_) >> ufoComp8Bits;
		out_pixel_ptr->alpha_ = in_pixel_ptr->alpha_;
		
		in_pixel_ptr++;
		out_pixel_ptr++;
	    }
	
	    opt = 1;
	}
    }
    
    if(!opt)
    {
	/* NB THIS SHOULD NOT HAPPEN
	 * THE FUNCTION ufoProcessSetPixelTypeCombinations() was used to set up 
	 * two supported pixel type combinations.
	 * Before rendering routines are called the input and output rasters would
	 * have been converted to one of the two combinations
	 */
	for (x = x1; x <= x2; x++)
	{
	    ufoRasterGetPixelCol(raster_in,  x, y, &r, &g, &b);
	    r = user_data->mix1_*user_data->mix_col_[0] + user_data->mix2_*r;
	    g = user_data->mix1_*user_data->mix_col_[1] + user_data->mix2_*g;
	    b = user_data->mix1_*user_data->mix_col_[2] + user_data->mix2_*b;
	    ufoRasterSetPixelCol(raster_out,  x, y, r, g, b);
	}
    }
}


