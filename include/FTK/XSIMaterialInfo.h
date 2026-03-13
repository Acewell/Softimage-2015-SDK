//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSIMaterialInfo.h
	\brief Defines the CSLXSIMaterialInfo class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _XSIMATERIALINFO_H
#define _XSIMATERIALINFO_H

#include "Template.h"

class CSLXSIMaterial;

/*! \brief This class represents an \xx ftk_XSI_MaterialInfo XSI_MaterialInfo \endxx template.

	Provides additional information on Materials for dotXSI 6.0+ (see the
	\xx ftk_XSI_MaterialInfo XSI_MaterialInfo \endxx template reference).
	\since dotXSI 3.6
*/
class XSIEXPORT CSLXSIMaterialInfo
    : public CSLTemplate
{
public:

	//! Defines the various wrap types
	enum EWrapType
	{
		SI_CLAMP,	/*!< Clamp texture */
		SI_REPEAT	/*!< Repeat texture */
	};

	/*! Constructor
		\param[in] in_pScene Pointer to the scene
		\param[in] in_pModel Pointer to the model
		\param[in] in_pTemplate Pointer to the parent template
	*/
	CSLXSIMaterialInfo(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

    //! Destructor
	virtual ~CSLXSIMaterialInfo();

	/*! Returns the type of this template
		\return CSLTemplate::XSI_MATERIAL_INFO The type of this template
	*/
	ETemplateType Type(){ return XSI_MATERIAL_INFO; }

    virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);

	/*! Returns the UWrap type
		\return The UWrap type
	*/
	EWrapType GetUWrap();

	/*! Sets the UWrap type
		\param[in] in_Type The type
	*/
	SI_Void SetUWrap( EWrapType in_Type );

	/*! Returns the VWrap type
		\return The VWrap type
	*/
	EWrapType GetVWrap();

	/*! Sets the VWrap type
		\param[in] in_Type The type
	*/
	SI_Void SetVWrap( EWrapType in_Type );

private:
    CSLEnumProxy<EWrapType, SI_REPEAT> m_UWrap;
    CSLEnumProxy<EWrapType, SI_REPEAT> m_VWrap;

	SI_Void *m_pReserved;
};

#endif
