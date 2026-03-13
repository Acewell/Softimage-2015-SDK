/*******************************************************************************
 * 
 * Media Illusion "Mix" UFO
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
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>

#include "ufoFunctions.h"
#include "ufoProcess.h"


/* enumerations for identifying inputs, outputs, parameters, parameter groups
 * and parameter values, respectively
 */

enum {
    INPUT1_, 
    INPUT2_, 
    N_RASTER_IN_
};

enum {
    OUTPUT_, 
    N_RASTER_OUT_
};

enum {
    MIX_LEVEL_, 
    MIX_TYPE_, 
    RANDOM_SCALE_, 
    N_PARAM_
};

enum {
    MIX_GROUP_, 
    N_PARAM_GROUP_
};

enum {
    MIX_UP_, 
    MIX_DOWN_, 
    MIX_RANDOM_UP_, 
    MIX_RANDOM_DOWN_, 
    N_MIX_TYPES_
};



/* structure ProcessUserData - used for storing commonly used values
 * derived from current parameter values
 */
typedef struct {
    double	mix1_;
    double	mix2_;
    int		opt_mix1_;
    int		opt_mix2_;
    int		is_random_;
    double	random_scale_;
} ProcessUserData;


/* "random" look up table 
 */
enum {
    TABLE_BITS_	    = 12, 
    TABLE_SIZE_	    = 1 << TABLE_BITS_, 
    TABLE_MOD_MASK_ = TABLE_SIZE_-1
};

static int	y_to_random_offset[TABLE_SIZE_];
static double	random_table[TABLE_SIZE_];
static int	random_table_set = 0;

/* UFO process definition
 */
ufoProcess ufoProcessDefine(void)
{    
    ufoProcess process_instance;

    /* create pixel combination arrays */
    const int	    number_combinations = 1;
    ufoPixelType    input_combinations[N_RASTER_IN_][1] = 
		    {
			{ufoRGB8PixelType}, 
			{ufoRGB8PixelType}, 
		    };
    
    ufoPixelType    output_combinations[N_RASTER_OUT_][1] = 
		    {
			{ufoRGB8PixelType}, 
		    };
		    
    char *mix_type_enum_table[N_MIX_TYPES_];    
    
    /* build enum param table for enum type definition */
    mix_type_enum_table[MIX_UP_]	    = "Mix Up";
    mix_type_enum_table[MIX_DOWN_]	    = "Mix Down";
    mix_type_enum_table[MIX_RANDOM_UP_]	    = "Mix Random Up";
    mix_type_enum_table[MIX_RANDOM_DOWN_]   = "Mix Random Down";
    
    
    process_instance =	ufoProcessCreate(
				"Mix",			/* process title */
				N_RASTER_IN_,		/* number of inputs */
				N_RASTER_OUT_,		/* number of outputs */
				N_PARAM_,		/* number of parameters */
				N_PARAM_GROUP_);	/* number of parameter groups */


    ufoProcessRasterInDefine(   process_instance,	/* definition process instance */
				INPUT1_,		/* raster index */
				"Input1",		/* raster id */
				"Input 1",		/* raster title */
				ufoRGBCompComb);	/* works on RGB input */
				
    ufoProcessRasterInDefine(   process_instance,	/* definition process instance */
				INPUT2_,		/* raster index */
				"Input2",		/* raster id */
				"Input 2",		/* raster title */
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

    /* set default animation for mix level */
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
    /* set nimation to be auto transitional */
    ufoProcessSetParamAutoTransition(
				process_instance,	/* definition process instance */
				MIX_LEVEL_, 		/* param index */
				1);			/* auto transition on */
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

    /* define un-used float to test interface */
    ufoProcessParamDefine(
				process_instance,	/* definition process instance */
				RANDOM_SCALE_,		/* param index */
				MIX_GROUP_,		/* param group */
				"RandomScale",		/* param id */
				"Random Scale",		/* param title */
				ufoFloatParam);

    /* set limits */
    ufoProcessSetParamLimits(
				process_instance,	/* definition process instance */
				RANDOM_SCALE_,		/* param index */
				0,			/* channel index */
				0.01, 10,		/* set range */
				ufoLimitsClampMin);	/* clamp min value only */

    /* set default value */
    ufoProcessSetParamDefaultValue(
				process_instance,	/* definition process instance */
				RANDOM_SCALE_,		/* param index */
				0,			/* channel index */
				1.0);


    ufoProcessSetPixelTypeCombinations(
				process_instance,
				number_combinations, 
				&input_combinations[0][0],
				&output_combinations[0][0], 
				0);
    
    return process_instance;
}




/* UFO user data copy - not actually required, but included for example
 */
void* ufoProcessCopyUserData(
		    void	*process_instance, 
		    void	*user_data)
{
    /* make a copy of the user data structure if it is set in the process - if it is set */
    /* shouldn't need to do this as data is only attatched before and after rendering */
    ProcessUserData *new_data = 0;
    if(user_data)
    {
	new_data =  (ProcessUserData *)malloc(sizeof(ProcessUserData));
	memcpy(new_data, user_data, sizeof(ProcessUserData));
    }
    
    return (void *)new_data;
}




/* UFO user data deletion - not actually required, but included for example
 */
void ufoProcessDeleteUserData(
		    void	*process_instance, 
		    void	*user_data)
{
    /* free up user data - if it has been set */
    /* shouldn't need to do this as data is only attatched before and after rendering */
    if(user_data)
	free(user_data);
}

/* UFO function used to determine avoidance of rendering
 */
int ufoProcessHasEffect(
		    void	*process_instance)
{
    /* get mix parameter value to check if process has effect */
    double	    mix_level;
    int		    mix_type;

    mix_level = ufoProcessGetParamValue(process_instance, MIX_LEVEL_, ufoDefaultChannelIndex);
    mix_type  = (int)ufoProcessGetParamValue(process_instance, MIX_TYPE_, ufoDefaultChannelIndex);

    if(mix_type == MIX_DOWN_ || mix_type == MIX_RANDOM_DOWN_)
	mix_level = 1.0 - mix_level;

    if(mix_level < 0.00001)
	return 0;
    else
	return 1;
}

/* UFO function called before rendering a frame 
 * setup commonly used values
 * derived from current parameter values
 * Creates temporary user data block
 */
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
	user_data = (ProcessUserData *)ufoMalloc(sizeof(ProcessUserData));
	ufoProcessSetUserData(process_instance, (void*)user_data);
    }
    
    /* set user data values to be used when rendering */

    mix_level = ufoProcessGetParamValue(process_instance, MIX_LEVEL_, ufoDefaultChannelIndex);
    mix_type  = (int)ufoProcessGetParamValue(process_instance, MIX_TYPE_, ufoDefaultChannelIndex);
    
    user_data->random_scale_ = ufoProcessGetParamValue(process_instance, RANDOM_SCALE_, ufoDefaultChannelIndex);
    user_data->random_scale_ /= 10.0;
    user_data->random_scale_ *= 1.0 - fabs(1 - 2*mix_level);
    
    if(mix_type == MIX_DOWN_ || mix_type == MIX_UP_)
	user_data->is_random_ = 0;
    else
	user_data->is_random_ = 1;
    
    if(mix_type == MIX_DOWN_ || mix_type == MIX_RANDOM_DOWN_)
	user_data->mix1_ = mix_level;
    else
	user_data->mix1_ = 1 - mix_level;
    
    user_data->mix2_ = 1 - user_data->mix1_;
    
    /* calculate interger versions of floating point values read */
    user_data->opt_mix1_ = (int)rint(user_data->mix1_ *(ufoComp8Max+1));
    user_data->opt_mix2_ = (int)rint(user_data->mix2_ *(ufoComp8Max+1));
    
    
    /* setup random table */
    if(!random_table_set)
    {
	int i;
	/* get table of random values in range (-0.5 to 0.5) */
	for(i = 0; i < TABLE_SIZE_; i++)
	    random_table[i] = ((double)rand())/((double)(1 << 15)) - 0.5;
	    
	for(i = 0; i < TABLE_SIZE_; i++)
	    y_to_random_offset[i] = rand() >> (15 - TABLE_BITS_);
	
	random_table_set = 1;
    }
}

/* UFO function called after rendering a frame 
 * delete previously allocated temporary user data block
 */
void ufoProcessPostRender(
		    void	*process_instance)
{
    ProcessUserData *user_data;
    
    user_data = (ProcessUserData *)ufoProcessGetUserData(process_instance);
    if(user_data)
    {
	/* free temporary user data*/
	ufoFree((void*)user_data);
	ufoProcessSetUserData(process_instance, (void*)NULL);
    }
}


/* UFO render function called every line
 */
void ufoProcessRenderLine(
		    void	*process_instance, 
		    int		x1, 
		    int		x2, 
		    int		y)
{
    ufoRaster raster_in1  = ufoProcessGetRasterIn(process_instance,  INPUT1_);
    ufoRaster raster_in2  = ufoProcessGetRasterIn(process_instance,  INPUT2_);
    ufoRaster raster_out  = ufoProcessGetRasterOut(process_instance, OUTPUT_);
    ProcessUserData *user_data;
    
    int	      x;
    
    double r1, g1, b1;
    double r2, g2, b2;
    int opt;
    ufoPixelType raster_in_type1, raster_in_type2;
    ufoPixelType raster_out_type;
    int		 rand_table_offset = y_to_random_offset[((unsigned int)y) & TABLE_MOD_MASK_];

    /* get user data with parameter values */
    user_data = (ProcessUserData *)ufoProcessGetUserData(process_instance);
        
    /* attempt to perform optimised render on RGB 8 bit or RGBA 8 bit
     * get input and output raster types
     */
    opt = 0;
    raster_in_type1  = ufoRasterGetPixelType(raster_in1);
    raster_in_type2  = ufoRasterGetPixelType(raster_in2);
    raster_out_type  = ufoRasterGetPixelType(raster_out);
    
    if(raster_in_type1 == raster_out_type &&
       raster_in_type1 == raster_in_type2 && 
       raster_in_type1 == ufoRGB8PixelType)
    {
	/* get pointers for input and output rasters at start of line;
	 * NB see ufoRaster.h for ufoPixelRGB8 definition
	 */
	ufoPixelRGB8 *in_pixel_ptr1  = (ufoPixelRGB8 *)ufoRasterGetPixelAddress(raster_in1, x1, y);
	ufoPixelRGB8 *in_pixel_ptr2  = (ufoPixelRGB8 *)ufoRasterGetPixelAddress(raster_in2, x1, y);
	ufoPixelRGB8 *out_pixel_ptr  = (ufoPixelRGB8 *)ufoRasterGetPixelAddress(raster_out, x1, y);

	if(!user_data->is_random_)
	{
	    for (x = x1; x <= x2; x++)
	    {
		/* perform integer based mix calculation directly into output pixel buffer */
		out_pixel_ptr->red_   = (in_pixel_ptr1->red_*user_data->opt_mix1_   + in_pixel_ptr2->red_  *user_data->opt_mix2_) >> ufoComp8Bits;
		out_pixel_ptr->green_ = (in_pixel_ptr1->green_*user_data->opt_mix1_ + in_pixel_ptr2->green_*user_data->opt_mix2_) >> ufoComp8Bits;
		out_pixel_ptr->blue_  = (in_pixel_ptr1->blue_*user_data->opt_mix1_  + in_pixel_ptr2->blue_ *user_data->opt_mix2_) >> ufoComp8Bits;
		
		in_pixel_ptr1++;
		in_pixel_ptr2++;
		out_pixel_ptr++;
	    }
	}
	else
	{
	    int mix1, mix2;
	    double random_value;
	    for (x = x1; x <= x2; x++)
	    {
		random_value = random_table[(((unsigned int)x) + rand_table_offset) & TABLE_MOD_MASK_];
		mix1 = user_data->opt_mix1_ + (int)(user_data->random_scale_*random_value*(ufoComp8Max+1));
		mix2 = (ufoComp8Max+1) - mix1;

		out_pixel_ptr->red_   = (in_pixel_ptr1->red_  *mix1 + in_pixel_ptr2->red_  *mix2) >> ufoComp8Bits;
		out_pixel_ptr->green_ = (in_pixel_ptr1->green_*mix1 + in_pixel_ptr2->green_*mix2) >> ufoComp8Bits;
		out_pixel_ptr->blue_  = (in_pixel_ptr1->blue_ *mix1 + in_pixel_ptr2->blue_ *mix2) >> ufoComp8Bits;
		
		in_pixel_ptr1++;
		in_pixel_ptr2++;
		out_pixel_ptr++;
	    }
	    
	}
    
	opt = 1;
    }
    
    if(!opt)
    {
	/* NB THIS SHOULD NOT HAPPEN
	 * THE FUNCTION ufoProcessSetPixelTypeCombinations() was used to set up 
	 * two supported pixel type combinations.
	 * Before rendering routines are called the input and output rasters would
	 * have been converted to one of the two combinations
	 */
	if(!user_data->is_random_)
	{
	    for (x = x1; x <= x2; x++)
	    {
		ufoRasterGetPixelCol(raster_in1,  x, y, &r1, &g1, &b1);
		ufoRasterGetPixelCol(raster_in2,  x, y, &r2, &g2, &b2);
		r1 = user_data->mix1_*r1 + user_data->mix2_*r2;
		g1 = user_data->mix1_*g1 + user_data->mix2_*g2;
		b1 = user_data->mix1_*b1 + user_data->mix2_*b2;
		ufoRasterSetPixelCol(raster_out,  x, y, r1, g1, b1);
	    }
	}
	else
	{
	    double mix1, mix2;
	    double random_value;
	    for (x = x1; x <= x2; x++)
	    {
		random_value = random_table[(((unsigned int)x) + rand_table_offset) & TABLE_MOD_MASK_];
		mix1 = user_data->mix1_ + user_data->random_scale_*random_value;
		mix2 = (ufoComp8Max+1) - mix1;
		ufoRasterGetPixelCol(raster_in1,  x, y, &r1, &g1, &b1);
		ufoRasterGetPixelCol(raster_in2,  x, y, &r2, &g2, &b2);
		r1 = mix1*r1 + mix2*r2;
		g1 = mix1*g1 + mix2*g2;
		b1 = mix1*b1 + mix2*b2;
		ufoRasterSetPixelCol(raster_out,  x, y, r1, g1, b1);
	    
	    }
	}
    }
}

