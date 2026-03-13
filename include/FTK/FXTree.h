//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file FXTree.h
	\brief Defines the CSLFXTree class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _FXTREE_H
#define _FXTREE_H

#include "Template.h"

class CSLFXOperator;

/*! This class represents an \xx ftk_XSI_FXTree XSI_FXTree \endxx template.

	Representation of a Softimage Illusion (FX) Tree (see the \xx ftk_XSI_FXTree XSI_FXTree \endxx
	template reference)
*/
class XSIEXPORT CSLFXTree
    : public CSLTemplate
{
public:

	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Refered template
		\return an instance of CSLFXTree
	*/
    CSLFXTree(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	//! Destructor
    virtual ~CSLFXTree();

	/*! Commits semantic layer data
		\return Whether or not commit was a success
	*/
	SI_Error Synchronize();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_FXTREE The type of this template
	*/
	ETemplateType Type(){ return XSI_FXTREE; }

	/*! Returns a parameter handle by name
		\param[in] in_szName the name of the parameter to get
		\return the found parameter
	*/
    virtual CSLAnimatableType*		ParameterFromName(SI_Char *in_szName);

	///////////////////////////////////////////////////////////////////////////
	// FXOperators Functionality //////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	/*! Adds a FXOperator to the FXOperator list
		\return Pointer to the newly added FXOperator
	*/
	CSLFXOperator* AddFXOperator();

	/*! Removes a FXOperator from the FXOperator list
		\param[in] in_nIndex Index of the FXOperator to remove
		\return Whether or not the FXOperator could be removed
	*/
	SI_Error RemoveFXOperator( SI_Int in_nIndex );

	/*! Removes a FXOperator from the FXOperator list
		\param[in] in_pToRemove Pointer to the FXOperator to remove
		\return Whether or not the FXOperator could be removed
	*/
	SI_Error RemoveFXOperator( CSLFXOperator* in_pToRemove );

	/*! Removes all operators from the FXOperator list
		\return Whether or not the list could be cleared
	*/
	SI_Error ClearFXOperators();

	/*! Adds an exisiting FXOperator to the FXOperator list
		\param[in] in_pToConnect Pointer to the FXOperator to add
		\return The added FXOperator or null if it already exists in the list
	*/
	CSLFXOperator* ConnectFXOperator( CSLFXOperator* in_pToConnect );

	/*! Returns a pointer to the internally-stored FXOperator pointer list
		\return Pointer to the list
	*/
	CSLFXOperator** GetFXOperatorList();

	/*! Returns the total number of FXOperators
		\return Number of FXOperators
	*/
	SI_Int GetFXOperatorCount();

	/*! Searches for a FXOperator by name
		\param[in] in_szName Name of the FXOperator to look for
		\return Pointer to the found FXOperator or null if not found
	*/
	virtual CSLFXOperator* FindFXOperator(SI_Char *in_szName);

private:
    CSIBCArray<CSLFXOperator*> m_FXOperators;

	SI_Void *m_pReserved;
};

#endif
