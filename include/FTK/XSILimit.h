//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSILimit.h
	\brief Defines the CSLXSILimit class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _LIMIT_H
#define _LIMIT_H

#include "Template.h"



/*!	\brief This class represents an \xx ftk_XSI_Limit XSI_Limit \endxx template.

	Encapsulates the minimum and maximum limits for dotXSI 5.0+ (see the \xx ftk_XSI_Limit XSI_Limit \endxx
	template reference).
	\sa CSLAnimatableType
	\sa CSLTemplate
*/
class XSIEXPORT CSLXSILimit
	: public CSLTemplate
{
public:
	/*! Constructor
		\param[in] in_pScene	Pointer to the scene
		\param[in] in_pModel	Pointer to the model
		\param[in] in_pTemplate	Pointer to the CdotXSITemplate
	*/
	CSLXSILimit
	(
		CSLScene* in_pScene,
		CSLModel *in_pModel,
		CdotXSITemplate* in_pTemplate
	);
	//! Destructor
	virtual ~CSLXSILimit();

	/*!	Returns the type of this template
		\retval CSLTemplate::XSI_LIMIT Template type
	*/
	ETemplateType Type(){ return XSI_LIMIT; }

	/*!	Returns the parameter connected to this limit.
		\return Pointer to a parameter proxy.
	*/
	CSLAnimatableType* GetParameter();

	/*! Connects a previously allocated parameter
		\param[in]	in_pNewParameter	Parameter to connect
		\return The connected parameter (\p in_pNewParameter) or NULL if a
			parameter was already connected.
	*/
	CSLAnimatableType* ConnectParameter(CSLAnimatableType* in_pNewParameter);

	/*! Returns the minimum value
		\return the minimum value
	*/
	virtual SI_Float	GetMinimum();

	/*! Sets the minimum value
		\param[in] in_fMin	The minimum value.
	*/
	virtual SI_Void		SetMinimum(SI_Float in_fMin);

	/*! Returns the maximum value
		\return the maximum value
	*/
	virtual SI_Float	GetMaximum();

	/*! Sets the maximum value
		\param[in] in_fMax	The maximum value.
	*/
	virtual SI_Void		SetMaximum(SI_Float in_fMax);

	/*! Returns the Minimum active value
		\return the minimum active value
	*/
	virtual SI_Bool	GetMinimumActive();

	/*! Sets the Minimum active value
		\param[in] in_bActive	Activeness.
	*/
	virtual SI_Void		SetMinimumActive(SI_Bool in_bActive);

	/*! Returns the Maximum active value
		\return the maximum active value
	*/
	virtual SI_Bool	GetMaximumActive();

	/*! Sets the Maximum active value
		\param[in] in_bActive	Activeness.
	*/
	virtual SI_Void		SetMaximumActive(SI_Bool in_bActive);

	/*! Returns the name of the parameter
		\return The name.
	*/
	SI_Char* GetParameterName();

	/*! Sets the name of the parameter
		\param[in] in_szParameterName	The name.
	*/
	SI_Void SetParameterName(SI_Char *in_szParameterName);

	/*!	Returns the name (string) of a specified sub parameter.
		\param[in]	in_pParameter	The sub parameter
		\return Name of the sub parameter.
	*/
    virtual const SI_Char* GetParameterName(CSLAnimatableType* in_pParameter);

	/*! Searches for a parameter by name
		\param[in] in_szName Name of the parameter to look for
		\return Pointer to the found parameter or null if not found
	*/
	virtual CSLAnimatableType *ParameterFromName(SI_Char *in_szName);

	/*! Searches for a parameter by name and type
		\param[in] in_Type Type of the parameter to look for
		\param[in] in_szParameterName Name of the parameter to look for
		\return Pointer to the found parameter or null if not found
	*/
	virtual CSLAnimatableType *ParameterFromType(EFCurveType in_Type, SI_Char *in_szParameterName);

	/*! Evaluates this limit
		\retval SI_Error::SI_SUCCESS on success
		\retval SI_Error::SI_ERROR if the parameter is not connected
	*/
	virtual SI_Error	Evaluate();


private:

	CSLAnimatableType*	m_pParameter;
	CSLStringProxy		m_szParameterName;
	CSLFloatProxy		m_fMin;
	CSLFloatProxy		m_fMax;
	CSLBoolProxy		m_bMinActive;
	CSLBoolProxy		m_bMaxActive;

	void *m_pReserved;	// reserved for future extension
};

#endif
