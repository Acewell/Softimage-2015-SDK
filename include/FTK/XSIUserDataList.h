//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSIUserDataList.h
	\brief Defines the CSLUserDataList class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _XSIUSERDATALIST_H
#define _XSIUSERDATALIST_H

#include "Template.h"

class CSLUserData;
class CSLCluster;

/*! \brief This class represents an \xx ftk_XSI_UserDataList XSI_UserDataList \endxx template.

	Defines a collection of user-defined data (see the \xx ftk_XSI_UserDataList XSI_UserDataList \endxx
	template reference).
	\sa CSLUserData
	\sa CSLCluster
	\since dotXSI 3.6
*/

class XSIEXPORT CSLUserDataList
    : public CSLTemplate
{
public:

	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Refered template
	*/
	CSLUserDataList(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	//! Destructor
	virtual ~CSLUserDataList();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_USER_DATA_LIST The type of this template
	*/
	ETemplateType Type(){ return XSI_USER_DATA_LIST; }

	/*! Commits semantic layer data
		\return Whether or not commit was a success
	*/
	SI_Error Synchronize();

	///////////////////////////////////////////////////////////////////////////
	// User data functionality ///////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	/*! Adds a user data to the user data list
		\return Pointer to the newly added user data
	*/
	CSLUserData* AddUserData();

	/*! Removes a user data from the user data list
		\param[in] in_nIndex Index of the user data to remove
		\return Whether or not the user data could be removed
	*/
	SI_Error RemoveUserData( SI_Int in_nIndex );

	/*! Removes a user data from the user data list
		\param[in] in_pToRemove Pointer to the user data to remove
		\return Whether or not the user data could be removed
	*/
	SI_Error RemoveUserData( CSLUserData* in_pToRemove );

	/*! Removes all connections points from the user data list
		\return Whether or not the list could be cleared
	*/
	SI_Error ClearUserDatas();

	/*! Adds a exisiting user data to the user data list
		\param[in] in_pToConnect Pointer to the user data to add
		\return The added user data or null if it already exists in the list
	*/
	CSLUserData* ConnectUserData( CSLUserData* in_pToConnect );

	/*! Returns a pointer to the internally-stored UserData pointer list
		\return Pointer to the list
	*/
	CSLUserData** GetUserDataList();

	/*! Returns the total number of user datas
		\return Number of user datas
	*/
	SI_Int GetUserDataCount();

	/*! Searches for a given UserData
		\param[in] in_szUserDataName Name of the user data to look for
		\return Pointer to the user data or null if it canot be found
	*/
	CSLUserData* FindUserData( SI_Char* in_szUserDataName );

private:
    CSIBCArray<CSLUserData*> m_UserDatas;

	SI_Void *m_pReserved;
};

#endif
