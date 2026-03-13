//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file ShaderConnectionPoint.h
	\brief Defines the CSLShaderConnectionPoint class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _SHADERCONENCTIONPOINT_H
#define _SHADERCONENCTIONPOINT_H

#include "ConnectionPoint.h"

/*! \brief Represents shader connection points.
*/
class XSIEXPORT CSLShaderConnectionPoint
    : public CSLConnectionPoint
{
public:
	/*! Constructor
		\param[in] in_pTemplate Parent Template
		\param[in] in_nValueIndex Index
	*/
	CSLShaderConnectionPoint
	(
		CdotXSITemplate *in_pTemplate,
		SI_Int in_nValueIndex
	);

	//! Destructor
    virtual ~CSLShaderConnectionPoint();

	//! Type of connection point
	enum EConnectionType
	{
		SI_SHADER,	/*!< Shader connection */
		SI_IMAGE,	/*!< Image connection */
		SI_NONE,	/*!< No connection */
	};

	/*! Returns the type of the connection point
		\return The type of connection
	*/
	EConnectionType GetConnectionType();

	/*! Sets the name of the source image
		\param[in] in_szName Name of the source image
		\return Error types. This function fails if the connection type is different than SI_IMAGE
	*/
	SI_Error SetImage( SI_Char* in_szName );

	/*! Returns the name of the source image
		\return Name of the source image or null if there's no source image
	*/
	SI_Char* GetImage();

	virtual SI_Error Synchronize();

private:
	CSLStringProxy m_ConnectionType;
	CSIBCString m_ImageName;
};

#endif
