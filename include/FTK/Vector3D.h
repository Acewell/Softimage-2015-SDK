//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file Vector3D.h
	\brief Defines the CSLVector3DProxy class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef __VECTOR3D_H__
#define __VECTOR3D_H__

#include "SL_Float.h"	// CSLFloatProxy
#include <SIBCVector.h>	// CSIBCVector3D
class CCOLLADATemplate;
class CSLCOLLADAScene;

/*! \brief This class allows modification of a 3D vector parameter in a template.
*/
class XSIEXPORT CSLVector3DProxy
{
public:
	/*! Constructor
		\param in_pTemplate Template that contains the vector values
		\param in_lIndexX Index in the template for the X value
		\param in_lIndexY Index in the template for the Y value
		\param in_lIndexZ Index in the template for the Z value
	*/
	CSLVector3DProxy
	(
		CdotXSITemplate *in_pTemplate,
		SI_Long in_lIndexX,
		SI_Long in_lIndexY,
		SI_Long in_lIndexZ
	);

	//! Set the 3D vector
    CSLVector3DProxy& operator =(const CSIBCVector3D &in_rVector);

	//! Get the 3D vector
    operator CSIBCVector3D();

	//! Get the X value
	CSLFloatProxy& X();

	//! Get the Y value
	CSLFloatProxy& Y();

	//! Get the Z value
	CSLFloatProxy& Z();

	//! Connect to a template
	void	Connect ( CdotXSITemplate *in_pTemplate,
						SI_Long in_lIndexX,
						SI_Long in_lIndexY,
						SI_Long in_lIndexZ );

	void	Connect ( CSLTemplate *in_pTemplate,
						CCOLLADATemplate *in_pOwner,
						SI_Long in_lIndexX,
						SI_Long in_lIndexY,
						SI_Long in_lIndexZ,
						CSLCOLLADAScene* in_pScene,
						int in_CurveType[],
						const char* in_XSIName[],
						const char* in_zsSuffixX = "X",
						const char* in_zsSuffixY = "Y",
						const char* in_zsSuffixZ = "Z",
						const char* in_szSID = NULL);

protected:
	CSLFloatProxy m_fX;
	CSLFloatProxy m_fY;
	CSLFloatProxy m_fZ;
};

#endif //__VECTOR3D_H__
