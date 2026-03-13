//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file StaticValue.h
	\brief Defines the CSLStaticValue class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _STATICVALUE_H
#define _STATICVALUE_H

#include "Template.h"

/*! \brief This class represents an \xx ftk_SI_ShapeAnimation SI_ShapeAnimation \endxx template.

	Stores a pose (static action--see the \xx ftk_SI_ShapeAnimation SI_ShapeAnimation \endxx
	template reference).  You can create a CSLStaticValue with the CSLAction::AddStaticValue method.
	\sa CSLAction
*/
class XSIEXPORT CSLStaticValue
    : public CSLTemplate
{
public:
	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Referred template
	*/
    CSLStaticValue(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
    virtual ~CSLStaticValue();

	/*! Returns the type of the template
		\retval CSLTemplate::XSI_STATIC_VALUES The type of this template
	*/
	CSLTemplate::ETemplateType Type(){ return XSI_STATIC_VALUES; }

	/*! Returns whether or not the parameter is active.
		\return Value of the flag
	*/
	SI_Bool GetActive();

	/*! Sets whether or not the parameter is active.
		\param[in] in_bActive Value of the flag
	*/
	SI_Void SetActive( SI_Bool in_bActive );

	/*! Returns the name of the parameter
		\return Name of the parameter
	*/
	SI_Char* GetParameterName();

	/*! Sets the name of the parameter
		\param[in] in_szName Name of the parameter
	*/
	SI_Void SetParameterName( SI_Char* in_szName );

	/*! Returns the value of the parameter
		\return Value of the parameter
	*/
	SI_Float GetValue();

	/*! Sets the value of the parameter
		\param[in] in_fValue Value of the parameter
	*/
	SI_Void SetValue( SI_Float in_fValue );

private:
    CSLBoolProxy m_Active;
    CSLStringProxy m_ParameterName;
    CSLDoubleProxy m_Value;

	SI_Void *m_pReserved;
};

#endif
