//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file COLLADAFCurve.h
	\brief Defines the CSLCOLLADAFCurve class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _COLLADAFCURVE_H
#define _COLLADAFCURVE_H

#include "FCurve.h"
#include "SL_Enum.h"

#define ELEM_TIME		0
#define ELEM_VALUE		1
#define ELEM_IN_TAN		2
#define ELEM_OUT_TAN	3
#define ELEM_INTERP		4


/*! \brief This class represents an fcurve for COLLADA.
*/
class XSIEXPORT CSLCOLLADAFCurve
    : public CSLFCurve
{
public:
	/*! Constructor
		\param[in] in_pScene	Pointer to the scene containing the fcurve
		\param[in] in_pModel	Pointer to the model containing the fcurve
		\param[in] in_pTemplate	Pointer to the CdotXSITemplate containing the fcurve
		\param[in] in_Type	Type of fcurve
		\param[in] in_InterpolationType	Interpolation type for this fcurve
		\return an instance of CSLFCurve
	*/
    CSLCOLLADAFCurve
	(
		CSLScene* in_pScene,
		CSLModel *in_pModel,
		CdotXSITemplate* in_pTemplate,
		EFCurveType in_Type,
		EFCurveInterpolationType in_InterpolationType
	);

	/*! Destructor
	*/
    virtual ~CSLCOLLADAFCurve();

	/*! Synchronizes this fcurve instance with its IO layer representation
		\retval SI_Error::SI_SUCCESS this function always returns SI_SUCCESS
	*/
    virtual SI_Error Synchronize();

	/*! Connects an existing COLLADA animation template
		\param[in] in_pChannel	Pointer to template
		\param[in] in_offset	Offset when reading data. Needed to synchronized with stride attribut
		\return Error code
	*/
    virtual SI_Error ConnectCOLLADAAnimation( CCOLLADATemplate* in_pChannel, const int in_offset = 0);

private:

	SI_Void		GetFloatArrayFromCurve ( CSIBCArray<float>& inout_Array, int in_iElement );
	SI_Void		AddSource ( CCOLLADATemplate* in_pAnimation,
							int in_iElement,
							SI_Char* in_szPrefix,
							SI_Char* in_szID,
							SI_Char* in_szOutput,
							CCOLLADATemplate* in_pSampler);

};

#endif
