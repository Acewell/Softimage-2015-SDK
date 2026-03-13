//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file FileInfo.h
	\brief Defines the CSLFileInfo class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _FILEINFO_H
#define _FILEINFO_H

#include "Template.h"

/*! \brief This class represents an \xx ftk_SI_FileInfo SI_FileInfo \endxx template.

	Used to set some information about the user and software that generated the scene
	(see the \xx ftk_SI_FileInfo SI_FileInfo \endxx template reference).
*/
class XSIEXPORT CSLFileInfo
    : public CSLTemplate
{
public:
	/*! Constructor
		\param in_pScene Parent scene
		\param in_pModel Parent model
		\param in_pTemplate Parent Template
		\return an instance of CSLFileInfo
	*/
    CSLFileInfo(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	/*! Destructor
	*/
    virtual ~CSLFileInfo();

	/*! Returns the originating software
		\return Originating software or null if not available
	*/
    char* GetOriginator() ;

	/*! Sets the originating software
		\param in_szOriginator Originating software
		\return void
	*/
	void SetOriginator( char* in_szOriginator );

	/*! Returns the name of the project
		\return Name of the project or null if not available
	*/
    char* GetProjectName() ;

	/*! Sets the name of the project
		\param in_szProjectName Name of the project
		\return void
	*/
    void SetProjectName( char* in_szProjectName );

	/*! Returns the user name.
		\return Name of the user or null if not available
	*/
    char* GetUsername() ;

	/*! Sets the user name.
		\param in_szUserName Name of the user
		\return void
	*/
    void SetUsername( char* in_szUserName );

	/*! Returns the save date time.
		\return Save date time
	*/
    char* GetSaveDateTime() ;

	/*! Sets the save date time.
		\param in_szSaveDateTime Save date time
		\return void
	*/
    void SetSaveDateTime( char* in_szSaveDateTime );

	/*! Returns the type of this template
		\return CSLTemplate::FILE_INFO Template type
	*/
	ETemplateType Type();

	/*! Updates template with current information
		\return SI_Error Specify if we could update the information or not
	*/
	SI_Error Synchronize();

	CSLStringProxy* GetProjectNameProxy() { return &m_ProjectName; };
	CSLStringProxy* GetUserNameProxy() { return &m_UserName;};
	CSLStringProxy* GetOriginatorProxy() { return &m_Originator;};
	CSLStringProxy* GetSaveDateTimeProxy() { return &m_SaveDateTime;};

private:
    CSLStringProxy m_ProjectName;
    CSLStringProxy m_UserName;
    CSLStringProxy m_Originator;
    CSLStringProxy m_SaveDateTime;

	// reserved for future use
	SI_Void *m_pReserved;
};

#endif

