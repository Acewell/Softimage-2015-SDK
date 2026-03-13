//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSIShaderCompoundPort.h
	\brief Defines the CSLXSIShaderCompoundPort class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _XSISHADERCOMPOUNDPORT_H
#define _XSISHADERCOMPOUNDPORT_H

#include "Template.h"

class CSLXSIShader;

/*! \brief This class represents an \xx ftk_XSI_ShaderCompoundPort XSI_ShaderCompoundPort \endxx template.

	Defines a shader compound port (see the \xx ftk_XSI_ShaderCompoundPort XSI_ShaderCompoundPort \endxx template reference).
	\since dotXSI 6.0
*/
class XSIEXPORT CSLXSIShaderCompoundPort
    : public CSLTemplate
{
public:
	//! Defines the various port types
	enum EPortType
	{
		SI_INPUT_PORT,	/*!< 0-Input Port */
		SI_OUTPUT_PORT,	/*!< 1-Output Port */
	};

	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Refered template
	*/
	CSLXSIShaderCompoundPort(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	//! Destructor
	virtual ~CSLXSIShaderCompoundPort();

	/*! Commits the current template information
		\return Whether or not the commit was successful
	*/
	SI_Error Synchronize();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_SHADER_COMPOUND_PORT The type of this template
	*/
	ETemplateType Type(){ return XSI_SHADER_COMPOUND_PORT; }

	/*! Returns the PortType value
		\return Port Type
	*/
	EPortType GetPortType();

	/*! Sets the PortType value
		\param[in]	in_eValue	new PortType value
	*/
	SI_Void SetPortType( EPortType in_eValue );

	/*! Returns the DisplayName value
		\return DisplayName
	*/
	SI_Char* GetDisplayName();

	/*! Sets the DisplayName value
		\param[in]	in_pValue	new DisplayName value
	*/
	SI_Void SetDisplayName( SI_Char* in_pValue );

	/*! Returns the PPGMinValue value
		\return PPGMinValue
	*/
	SI_Char* GetPPGMinValue();

	/*! Sets the PPGMinValue value
		\param[in]	in_pValue	new PPGMinValue value
	*/
	SI_Void SetPPGMinValue( SI_Char* in_pValue );

	/*! Returns the PPGMaxValue value
		\return PPGMaxValue
	*/
	SI_Char* GetPPGMaxValue();

	/*! Sets the PPGMaxValue value
		\param[in]	in_pValue	new PPGMaxValue value
	*/
	SI_Void SetPPGMaxValue( SI_Char* in_pValue );

	/*! Returns the PPGEnumValues value
		\return PPGEnumValues
	*/
	SI_Char* GetPPGEnumValues();

	/*! Sets the PPGEnumValues value
		\param[in]	in_pValue	new PPGEnumValues value
	*/
	SI_Void SetPPGEnumValues( SI_Char* in_pValue );

	/*! Returns the PPGLayoutVisible value
		\return PPGLayoutVisible
	*/
	SI_Bool GetPPGLayoutVisible();

	/*! Sets the PPGLayoutVisible value
		\param[in]	in_nValue	new PPGLayoutVisible value
	*/
	SI_Void SetPPGLayoutVisible ( SI_Bool in_nValue );

	/*! Returns the PPGLayoutGroup value
		\return PPGLayoutGroup
	*/
	SI_Char* GetPPGLayoutGroup();

	/*! Sets the PPGLayoutGroup value
		\param[in]	in_pValue	new PPGLayoutGroup value
	*/
	SI_Void SetPPGLayoutGroup( SI_Char* in_pValue );

	/*! Returns the PPGLayoutTab value
		\return PPGLayoutTab
	*/
	SI_Char* GetPPGLayoutTab();

	/*! Sets the PPGLayoutTab value
		\param[in]	in_pValue	new PPGLayoutTab value
	*/
	SI_Void SetPPGLayoutTab( SI_Char* in_pValue );

	/*! Returns the RTLayoutVisible value
		\return RTLayoutVisible
	*/
	SI_Bool GetRTLayoutVisible();

	/*! Sets the RTLayoutVisible value
		\param[in]	in_pValue		new RTLayoutVisible value
	*/
	SI_Void SetRTLayoutVisible( SI_Bool in_pValue );

	/*! Returns the RTLayoutGroup  value
		\return RTLayoutGroup
	*/
	SI_Char* GetRTLayoutGroup ();

	/*! Sets the RTLayoutGroup  value
		\param[in]	in_pValue	new RTLayoutGroup  value
	*/
	SI_Void SetRTLayoutGroup ( SI_Char* in_pValue );

	/*! Returns the Source Shader
		\return the Source Shader
	*/
	CSLXSIShader* GetSourceShader ();

	/*! Sets the Source Shader
		\param[in]	in_pSourceShader	new Source Shader
	*/
	SI_Void SetSourceShader ( CSLXSIShader* in_pSourceShader );

	CSLEnumProxy<EPortType, SI_OUTPUT_PORT>*	GetPortTypeProxy()			{ return &m_PortType; };
	CSLStringProxy* 							GetDisplayNameProxy()		{ return &m_DisplayName; };
	CSLStringProxy* 							GetPPGMinValueProxy()		{ return &m_PPGMinValue; };
	CSLStringProxy* 							GetPPGMaxValueProxy()		{ return &m_PPGMaxValue; };
	CSLStringProxy* 							GetPPGEnumValuesProxy()		{ return &m_PPGEnumValues; };
	CSLBoolProxy* 								GetPPGLayoutVisibleProxy()	{ return &m_PPGLayoutVisible; };
	CSLStringProxy* 							GetPPGLayoutGroupProxy()	{ return &m_PPGLayoutGroup; };
	CSLStringProxy* 							GetPPGLayoutTabProxy()		{ return &m_PPGLayoutTab; };
	CSLBoolProxy* 								GetRTLayoutVisibleProxy()	{ return &m_RTLayoutVisible; };
	CSLStringProxy* 							GetRTLayoutGroupProxy()		{ return &m_RTLayoutGroup; };

private:
    CSLEnumProxy<EPortType, SI_OUTPUT_PORT>		m_PortType;
	CSLStringProxy								m_DisplayName;
	CSLStringProxy								m_PPGMinValue;
	CSLStringProxy								m_PPGMaxValue;
	CSLStringProxy								m_PPGEnumValues;
	CSLBoolProxy								m_PPGLayoutVisible;
	CSLStringProxy								m_PPGLayoutGroup;
	CSLStringProxy								m_PPGLayoutTab;
	CSLBoolProxy								m_RTLayoutVisible;
	CSLStringProxy								m_RTLayoutGroup;
	CSLXSIShader* 								m_pSourceShader;

	SI_Void *m_pReserved;
};

#endif
