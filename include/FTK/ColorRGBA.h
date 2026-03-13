//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file ColorRGBA.h
	\brief Defines the CSLColorRGBAProxy class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef __COLORRGBA_H__
#define __COLORRGBA_H__

#include "ColorRGB.h"
class CCOLLADATemplate;

/*! \brief Allows modification of an RGBA parameter in a template
*/
class XSIEXPORT CSLColorRGBAProxy : public CSLColorRGBProxy
{
public:
	/*! Constructor
		\param in_pTemplate Template that contains the RGB values
		\param in_lIndexR Index in the template for the red value
		\param in_lIndexG Index in the template for the green value
		\param in_lIndexB Index in the template for the blue value
		\param in_lIndexA Index in the template for the alpha value
	*/
	CSLColorRGBAProxy
	(
		CdotXSITemplate *in_pTemplate,
		SI_Long in_lIndexR,
		SI_Long in_lIndexG,
		SI_Long in_lIndexB,
		SI_Long in_lIndexA
	);

	/*! Sets the RGBA value
		\param in_rColor	The new color
		\return CSLColorRGBAProxy&	Reference to this color
	*/
    CSLColorRGBAProxy& operator =(const CSIBCColorf &in_rColor);

	/*! Conversion operator. Converts the color in this object to a CSIBCColorf object.
	*/
    operator CSIBCColorf();

	/*! Gets the alpha value
		\return CSLFloatProxy Parameter containing the alpha value of this color
	*/
	CSLFloatProxy& A();

	void	Connect ( CdotXSITemplate *in_pTemplate, SI_Long in_lIndexR, SI_Long in_lIndexG, SI_Long in_lIndexB , SI_Long in_lIndexA);
	void	Connect ( CSLTemplate *in_pTemplate, CCOLLADATemplate *in_pOwner, SI_Long in_lIndexR, SI_Long in_lIndexG, SI_Long in_lIndexB , SI_Long in_lIndexA, CSLCOLLADAScene* in_pScene, int in_CurveType[], const char* in_XSIName[]);

private:
	CSLFloatProxy m_fA;
};

#endif //__COLORRGBA_H__
