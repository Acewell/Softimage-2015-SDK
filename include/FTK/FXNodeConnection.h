//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file FXNodeConnection.h
	\brief Defines the CSLFXOperatorConnection class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _FXOPERATORCONNECTION_H
#define _FXOPERATORCONNECTION_H

#include "Template.h"
#include "Scene.h"

class CSLFXOperator;

//! This class represents a connection in the FX Tree.
class XSIEXPORT CSLFXOperatorConnection
{
public:

	/*! Defines the various types of connection
	*/
	enum EConnectionType
	{
		SI_NONE,			//!<not connected
		SI_FXOPERATOR,		//!<connected to an effect operator
	};

	/*! Constructor
	* \param in_pTemplate Parent Template
	* \param in_nValueIndex Index
	* \return an instance of CSLFCOperatorConnection
	*/
	CSLFXOperatorConnection
	(
		CdotXSITemplate *in_pTemplate,
		SI_Int in_nValueIndex
	);

	/*! Commits semantic layer data
	* \return SI_Error Whether or not commit was a success
	*/
	SI_Error Synchronize();

	/*! Gets the name of the connection
	* \return SI_Char Name of the connection
	*/
	SI_Char* GetName();

	/*! Sets the name of the connection
	* \param in_szName The name of the connection
	*/
	SI_Void SetName( SI_Char* in_szName );

	/*! Gets the refered node
	* \return CSLFXOperator Pointer to the refered node or null if none
	*/
	CSLFXOperator* GetFXOperator();

	/*! Sets the refered node
	* \param in_pNode Pointer to the refered node or null if none
	*/
	SI_Void SetFXOperator( CSLFXOperator *in_pNode);

	/*! Gets the connection type
	* \return EConnectionType Type of connection
	*/
	EConnectionType GetConnectionType();

	/*! Sets the connection type
	* \param in_Type New type of connection
	*/
	SI_Void SetConnectionType( EConnectionType in_Type );

	//! Destructor
    virtual ~CSLFXOperatorConnection();

	SI_Char* GetFXOperatorName();

private:

    CSLFXOperator *m_pReferedNode;
	EConnectionType m_ConnectionType;
	CdotXSIParam *m_pNameParam;
	CdotXSIParam *m_pTypeParam;

	SI_Void *m_pReserved;

};

#endif
