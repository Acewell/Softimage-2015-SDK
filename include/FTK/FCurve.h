//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file FCurve.h
	\brief Defines the CSLFCurve class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _FCURVE_H
#define _FCURVE_H

#include "BaseFCurve.h"
#include "SL_Enum.h"

extern XSIEXPORT CEnumDictionary<CSLTemplate::EFCurveType, CSLTemplate::SI_INTENSITY> g_FCurveTypeDictionary;

XSIEXPORT	CEnumDictionary<CSLTemplate::EFCurveType, CSLTemplate::SI_INTENSITY>* GetFCurveEnumDictionary();

/*! \brief This class represents an \xx ftk_SI_FCurve SI_FCurve \endxx template.

	Defines an FCurve (see the \xx ftk_SI_FCurve SI_FCurve \endxx
	template reference)
*/
class XSIEXPORT CSLFCurve
    : public CSLBaseFCurve
{
public:
	typedef CSLStrEnumProxy<EFCurveType, SI_INTENSITY> EFCurveTypeProxy;

	/*! Constructor
		\param[in] in_pScene	Pointer to the scene containing the fcurve
		\param[in] in_pModel	Pointer to the model containing the fcurve
		\param[in] in_pTemplate	Pointer to the CdotXSITemplate containing the fcurve
		\param[in] in_Type	Type of fcurve
		\param[in] in_InterpolationType	Interpolation type for this fcurve
		\return an instance of CSLFCurve
	*/
    CSLFCurve
	(
		CSLScene* in_pScene,
		CSLModel *in_pModel,
		CdotXSITemplate* in_pTemplate,
		EFCurveType in_Type,
		EFCurveInterpolationType in_InterpolationType
	);

	/*! Destructor
	*/
    virtual ~CSLFCurve();

	/*! Returns the model to which this fcurve belongs
		\return the model to which this fcurve belongs
	*/
    CSLModel* Reference();

	/*! Returns the type of fcurve
		\return the type of the fcurve
	*/
    EFCurveType GetFCurveType();

	/*! Returns the fcurve type as a string value
		\return the type of the fcurve in formatted in a string
	*/
	const SI_Char* GetFCurveTypeAsString();

	/*! Synchronizes this fcurve instance with its IO layer representation
		\retval SI_Error::SI_SUCCESS this function always returns SI_SUCCESS
	*/
    virtual SI_Error Synchronize();

	/*! Returns the template type
		\retval CSLTemplate::SI_FCURVE type of this fcurve
	*/
    virtual ETemplateType Type();

private:
   EFCurveType m_FCurveType;

	void *m_pReserved;	// reserved for future extension
};

#endif
