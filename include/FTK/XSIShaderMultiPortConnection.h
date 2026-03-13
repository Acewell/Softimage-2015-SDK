//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSIShaderMultiPortConnection.h
	\brief Defines the CSLXSIShaderMultiPortConnection class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _XSISHADERMULTIPORTCONNECTION_H
#define _XSISHADERMULTIPORTCONNECTION_H

#include "Template.h"

class CSLVariantParameter;

/*! \brief This class represents an \xx ftk_XSI_ShaderMultiPortConnection XSI_ShaderMultiPortConnection \endxx template.

	Describes to which port a given shader parameter is connected on a multiple output port shader
	(see the \xx ftk_XSI_ShaderMultiPortConnection XSI_ShaderMultiPortConnection \endxx template reference).

	\sa CSLXSIShader
	\sa CSLXSIShaderMultiPort
*/
class XSIEXPORT CSLXSIShaderMultiPortConnection
    : public CSLTemplate
{
public:

	/*! Constructor
		\param[in] in_pScene	Pointer to the scene containing the CSLXSIShaderMultiPortConnection
		\param[in] in_pModel	Pointer to the model containing the CSLXSIShaderMultiPortConnection
		\param[in] in_pTemplate	Pointer to the CdotXSITemplate defining the CSLXSIShaderMultiPortConnection
	*/
    CSLXSIShaderMultiPortConnection(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	/*! Destructor
	*/
    virtual ~CSLXSIShaderMultiPortConnection();

	SI_Error Synchronize();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_SHADER_MULTI_PORT_CONNECTION Template type
	*/
	CSLTemplate::ETemplateType Type(){ return CSLTemplate::XSI_SHADER_MULTI_PORT_CONNECTION; }

	/*! Returns the name of the parameter to which this CSLXSIShaderMultiPortConnection applies to
		\retval SI_Char The name of the parameter
	*/
	SI_Char* GetParameter();

	/*! Sets the name of the parameter to which this CSLXSIShaderMultiPortConnection applies to
		\param[in] in_pParameter The name of the parameter
	*/
	SI_Void				SetParameter(SI_Char* in_pParameter);

	/*! Returns the parameter name proxy
		\return Pointer to parameter name proxy
	*/
	CSLStringProxy*		GetParameterProxy(){return &m_szParameter;};

	/*! Returns the name of the port connected to the parameter
		\return The name of the port
	*/
	SI_Char*			GetPortName();

	/*! Sets the name of the port connected to the parameter
		\param[in] in_pPortName The name of the port connected to the parameter
	*/
	SI_Void				SetPortName( SI_Char* in_pPortName );

	/*! Returns the port name proxy
		\return Pointer to port name proxy
	*/
	CSLStringProxy*		GetPortNameProxy(){return &m_szPortName;};

private:
	CSLStringProxy m_szParameter;
	CSLStringProxy m_szPortName;
	SI_Void *m_pReserved;
};

#endif // XSISHADERMULTIPORTCONNECTION
