//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   
#include "VertexColorHelper.h"

#define siMAX(a,b) ((a)<(b) ? (b):(a))
#define siMIN(a,b) ((a)>(b) ? (b):(a))

inline int siRndDown(double a)	        {return (((a)<0) ? (((a)==(int)(a))?((int)(a)):((int)((a)-1))) : ((int)(a)));}

void RGBA2HLSA ( double r, 
					double g, 
					double b, 
					double a, 
					double* hue,
					double* lum,
					double* sat,
					double* alpha )

{
	double l_dfHue, l_dfLum, l_dfSat;

	double l_dfMax   = siMAX(siMAX(r,g),b);
	double l_dfMin   = siMIN(siMIN(r,g),b);
	double l_dfDelta = l_dfMax - l_dfMin;

	// calculate Luminance
	l_dfLum = (l_dfMin + l_dfMax) / 2.0;

	// calculate Saturation
	if (l_dfDelta == 0.0)
	{
		l_dfSat = 0.0;
	}
	else
	{
		if (l_dfLum <= 0.5)
		{
			l_dfSat = l_dfDelta / (l_dfMin + l_dfMax);
		}
		else
		{
			l_dfSat = l_dfDelta / (2.0 - (l_dfMin + l_dfMax));
		}
	}

	// calculate Hue
	if (l_dfSat == 0.0)
	{
		l_dfHue = 0; // achromatic case; hue is undefined
	}
	else // chromatic case
	{
		if (r == l_dfMax)
		{
			l_dfHue = (g-b)/l_dfDelta;
		}
		else if (g == l_dfMax)
		{
			l_dfHue = 2+(b-r)/l_dfDelta;
		}
		else // if (m_dfBlue == l_dfMax)
		{
			l_dfHue = 4+(r-g)/l_dfDelta;
		}

		l_dfHue *= 60; // put hue in degrees

		// make the angle non-negative
		if (l_dfHue < 0)
		{
			l_dfHue += 360.0;
		}
	}

	// Return required values
	if (0 != hue)
	{
		*hue = l_dfHue / 360.0; // Hue is normalized (meid 05/04/97 : divide by 360 insted of 359)
	}
	if (0 != lum)
	{
		*lum = l_dfLum;
	}
	if (0 != sat)
	{
		*sat = l_dfSat;
	}
	if (0 != alpha)
	{
		*alpha = a;
	}
}

void HLSA2RGBA ( double hue, 
				double lum, 
				double sat, 
				double alpha, 
				double *r,
				double *g,
				double *b,
				double *a )
{
	double l_dfHue = hue;
	double l_dfLum = lum;
	double l_dfSat = sat;
	double l_dfMax = 0.0; // maximum component value out of R, G, or B

	if (l_dfLum <= 0.5)
	{
		l_dfMax = l_dfLum * (1.0 + l_dfSat);
	}
	else
	{
		l_dfMax = l_dfLum + l_dfSat - (l_dfLum * l_dfSat);
	}

	if (l_dfMax == 0)
	{
		*r   = 0.0;
		*g   = 0.0;
		*b	 = 0.0;
	}
	else
	{
		l_dfHue *= 360.0/60.0;

		unsigned int  l_ulHueI = (unsigned int)siRndDown(l_dfHue);
		double l_dfHueF = l_dfHue - l_ulHueI;

		double l_dfMin  = 2.0*l_dfLum - l_dfMax; // minimum component value out of R, G, or B
		double l_dfQ    = l_dfMax - ((l_dfMax-l_dfMin)*l_dfHueF);
		double l_dfT    = l_dfMin + ((l_dfMax-l_dfMin)*l_dfHueF);

		switch (l_ulHueI)
		{
			case 0 :
			case 6 : *r   = l_dfMax;
					 *g = l_dfT;
					 *b  = l_dfMin;
					 break;

			case 1 : *r   = l_dfQ;
					 *g = l_dfMax;
					 *b  = l_dfMin;
					 break;

			case 2 : *r   = l_dfMin;
					 *g = l_dfMax;
					 *b  = l_dfT;
					 break;

			case 3 : *r   = l_dfMin;
					 *g = l_dfQ;
					 *b  = l_dfMax;
					 break;

			case 4 : *r   = l_dfT;
					 *g = l_dfMin;
					 *b  = l_dfMax;
					 break;

			case 5 : *r   = l_dfMax;
					 *g = l_dfMin;
					 *b  = l_dfQ;
					 break;
		}
	}

	*a = alpha;
	
}