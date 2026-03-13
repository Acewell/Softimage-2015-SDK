//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file ConnectionPoint.h
	\brief Defines the CSLConnectionPoint class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _CONNECTIONPOINT_H
#define _CONNECTIONPOINT_H

#include "Template.h"
#include "Scene.h"
#include <dotXSIParam.h>	// CdotXSIParam

// Forward declaration
class CSLXSIShader;

/*! \brief Represents connection points.
*/
class XSIEXPORT CSLConnectionPoint
{
	friend class CSLScene;
public:
	/*! Constructor
	* \param in_pTemplate Parent Template
	* \param in_nValueIndex Index
	* \return an instance of CSLConnectionPoint
	*/
	CSLConnectionPoint
	(
		CdotXSITemplate *in_pTemplate,
		SI_Int in_nValueIndex
	);

	/*! Destructor
	*/
    virtual ~CSLConnectionPoint();

	/*! Set the name of the connection point
	* \param in_szName Name of the connection point
	* \return SI_Void
	*/
	SI_Void SetName( SI_Char *in_szName );

	/*! Gets the name of the connection point
	* \return SI_Char Name of the connection point
	*/
	SI_Char* GetName();

	/*! Gets the value of the connection point
	* \return SI_TinyVariant Value of the connection point
	*/
	SI_TinyVariant* GetValue();

	/*! Set the shader of the connection point
	* \param in_pShader Pointer to the shader to connect
	* \return SI_Void
	*/
	SI_Void SetShader( CSLXSIShader *in_pShader );

	/*! Get the shader of the connection point
	* \return Pointer to the shader
	*/
	CSLXSIShader* GetShader();

	/*! Synchronizes this connection point instance with its IO layer representation
	* \return SI_Error
	* \retval SI_SUCCESS this function always returns SI_SUCCESS
	*/
	virtual SI_Error Synchronize();

	/*! Gets the parameter that holds the name of the connection point
	* \return CdotXSIParam* Pointer to the param that holds the name of the connection point
	*/
	CdotXSIParam* GetParam()
	{
		return m_pParam;
	}

protected:
	CdotXSIParam *m_pParam;

	CSLXSIShader *m_pShader;
};

#endif
