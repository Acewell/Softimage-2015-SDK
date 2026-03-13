//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file FXNode.h
	\brief Defines the CSLFXOperator class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _FXNODE_H
#define _FXNODE_H

#include "Template.h"

class CSLVariantParameter;
class CSLFXOperatorConnection;

/*! \brief This class represents an \xx ftk_XSI_FXOperator XSI_FXOperator \endxx template.

	Representation of an operator in the FX Tree (see the
	\xx ftk_XSI_FXOperator XSI_FXOperator \endxx template reference).
*/
class XSIEXPORT CSLFXOperator
    : public CSLTemplate
{
public:

	//! Describes the various output types
	enum EOutputType
	{
		SI_DEFAULT = 0,	/*!< Default output type */
	};

	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Refered template
		\return an instance of CSLFCOperator
	*/
    CSLFXOperator(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	//! Destructor
    virtual ~CSLFXOperator();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_FXOPERATOR The type of this template
	*/
	ETemplateType Type(){ return XSI_FXOPERATOR; }

	/*! Commits semantic layer data
		\return Whether or not commit was a success
	*/
	SI_Error Synchronize();


	/*! Returns the OutputType
		\return The OutputType
	*/
	EOutputType GetOutputType();

	/*! Sets the OutputType
		\param[in] in_OutputType New output type to use
	*/
	SI_Void SetOutputType( EOutputType in_OutputType );

	/*! Returns the EffectID
		\return Pointer to a string representing the EffectID
	*/
	SI_Char* GetEffectID();

	/*! Sets the EffectID
		\param[in] in_szProgID Pointer to a string representing the EffectID
	*/
	SI_Void SetEffectID( SI_Char* in_szProgID );

	///////////////////////////////////////////////////////////////////////////
	// Parameters Functionality ///////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	/*! Adds a parameter to the parameter list
		\return Pointer to the newly added parameter
	*/
	CSLVariantParameter* AddParameter();

	/*! Removes a parameter from the parameter list
		\param[in] in_nIndex Index of the parameter to remove
		\return Whether or not the parameter could be removed
	*/
	SI_Error RemoveParameter( SI_Int in_nIndex );

	/*! Removes a parameter from the parameter list
		\param[in] in_pToRemove Pointer to the parameter to remove
		\return Whether or not the parameter could be removed
	*/
	SI_Error RemoveParameter( CSLVariantParameter* in_pToRemove );

	/*! Removes all connections points from the parameter list
		\return Whether or not the list could be cleared
	*/
	SI_Error ClearParameters();

	/*! Adds an exisiting parameter to the parameter list
		\param[in] in_pToConnect Pointer to the parameter to add
		\return The added parameter or null if it already exists in the list
	*/
	CSLVariantParameter* ConnectParameter( CSLVariantParameter* in_pToConnect );

	/*! Returns a pointer to the internally-stored parameter pointer list
		\return Pointer to the list
	*/
	CSLVariantParameter** GetParameterList();

	/*! Returns the total number of parameters
		\return Number of parameters
	*/
	SI_Int GetParameterCount();

	/*! Searches for a parameter by name
		\param[in] in_szName Name of the parameter to look for
		\return Pointer to the found parameter or null if not found
	*/
	virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);

	/*! Searches for a parameter by name and type
		\param[in] in_Type Type of the parameter to look for
		\param[in] in_szParameterName Name of the parameter to look for
		\return Pointer to the found parameter or null if not found
	*/
    virtual CSLAnimatableType* ParameterFromType(EFCurveType in_Type, SI_Char *in_szParameterName);

	///////////////////////////////////////////////////////////////////////////
	// Connection points functionality ////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	/*! Adds a connection point to the connection point list
		\return Pointer to the newly added connection point
	*/
	CSLFXOperatorConnection* AddConnectionPoint();

	/*! Removes a connection point from the connection point list
		\param[in] in_nIndex Index of the connection point to remove
		\return Whether or not the connection point could be removed
	*/
	SI_Error RemoveConnectionPoint( SI_Int in_nIndex );

	/*! Removes a connection point from the connection point list
		\param[in] in_pToRemove Pointer to the connection point to remove
		\return Whether or not the connection point could be removed
	*/
	SI_Error RemoveConnectionPoint( CSLFXOperatorConnection* in_pToRemove );

	/*! Removes all connections points from the connection point list
		\return Whether or not the list could be cleared
	*/
	SI_Error ClearConnectionPoints();

	/*! Adds an exisiting connection point to the connection point list
		\param[in] in_pToConnect Pointer to the connection point to add
		\return The added connection point or null if it already exists in the list
	*/
	CSLFXOperatorConnection* ConnectConnectionPoint( CSLFXOperatorConnection* in_pToConnect );

	/*! Returns a pointer to the internally-stored connection point pointer list
		\return Pointer to the list
	*/
	CSLFXOperatorConnection** GetConnectionPointList();

	/*! Returns the total number of connection points
		\return Number of connection points
	*/
	SI_Int GetConnectionPointCount();

private:
    CSLStringProxy m_ProgID;
    CSLEnumProxy<EOutputType, SI_DEFAULT> m_OutputType;
	CSIBCArray<CSLFXOperatorConnection*> m_ConnectionPoints;
	CSIBCArray<CSLVariantParameter*> m_Parameters;

	SI_Void *m_pReserved;
};

#endif
