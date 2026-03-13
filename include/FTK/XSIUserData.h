//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSIUserData.h
	\brief Defines the CSLUserData and CSLUserDataBlob classes

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _XSIUSERDATA_H
#define _XSIUSERDATA_H

#include "Template.h"

#ifndef _SL_INT_ARRAY_PROXY_EXPORT_
#define _SL_INT_ARRAY_PROXY_EXPORT_

//XSITEMPLATEEXP template class XSIEXPORT CSLArrayProxy<SI_Int, SI_Int, 1>;

#endif // _SL_INT_ARRAY_PROXY_EXPORT_

#ifndef _SL_UBYTE_ARRAY_PROXY_EXPORT_
#define _SL_UBYTE_ARRAY_PROXY_EXPORT_

//XSITEMPLATEEXP template class XSIEXPORT CSLArrayProxy<SI_UByte, SI_UByte, 1>;

#endif // _SL_UBYTE_ARRAY_PROXY_EXPORT_

class CSLUserDataList;

/*! \brief This class represents an \xx ftk_XSI_UserData XSI_UserData \endxx template.

	Defines user-defined data (see the \xx ftk_XSI_UserData XSI_UserData \endxx template reference).
	\sa CSLUserDataList
	\since dotXSI 3.6
*/
class XSIEXPORT CSLUserData
    : public CSLTemplate
{
public:

	//! Unsigned Byte array proxy class that works like an array of SI_UByte
	typedef CSLArrayProxy<SI_UByte, SI_UByte, 1> CSLUByteArray;

	//! Int array proxy class that works like an array of SI_Int
	typedef CSLArrayProxy<SI_Int, SI_Int, 1> CSLIntArray;

	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Referred template
	*/
	CSLUserData(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	//! Destructor
	virtual ~CSLUserData();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_USER_DATA The type of this template
	*/
	ETemplateType Type(){ return XSI_USER_DATA; }

	/*! Commits semantic layer data
		\return Whether or not commit was a success
	*/
	SI_Error Synchronize();

	///////////////////////////////////////////////////////////////////////////
	// User data //////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	/*! Returns pointer the user data array
		\return Pointer to the array containing the user data
	*/
	SI_UByte* GetUserDataListPtr();

	/*! Returns the user data array
		\return Array of user data
	*/
	CSLUByteArray* GetUserDataList();

	/*! Returns the size of the user data array
		\return Size of the user data
	*/
	SI_Int GetUserDataCount();

	///////////////////////////////////////////////////////////////////////////
	// Sub element access /////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	/*! Returns a pointer to the sub element array
		\return Pointer to the array containing indices for all affected vertices/edges/polygons
	*/
	SI_Int* GetSubElementListPtr();

	/*! Returns the sub element array
		\return Pointer to the array containing indices for all affected vertices/edges/polygons
	*/
	CSLIntArray* GetSubElementList();

	/*! Returns the number of sub elements
		\return Number of sub elements indices
	*/
	SI_Int GetSubElementCount();

private:
	CSLIntProxy m_DataSize;
    CSLUByteArray m_UserData;
    CSLIntArray m_SubElements;

	SI_Void* m_pReserved;
};

/*! \brief This class represents an \xx ftk_XSI_UserDataBlob XSI_UserDataBlob \endxx template.

	Defines user-defined data (see the \xx ftk_XSI_UserDataBlob XSI_UserDataBlob \endxx
	template reference).
	\sa CSLUserDataBlob
	\since dotXSI 5.0
*/
class XSIEXPORT CSLUserDataBlob
    : public CSLTemplate
{
public:

	//! Unsigned Byte array proxy class that works like an array of SI_UByte
	typedef CSLArrayProxy<SI_UByte, SI_UByte, 1> CSLUByteArray;

	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Referred template
		\param[in] in_pAttachTo	Template to attach to
	*/
	CSLUserDataBlob(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate, CSLTemplate* in_pAttachTo = NULL);

	//! Destructor
	virtual ~CSLUserDataBlob();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_USER_DATA_BLOB The type of this template
	*/
	ETemplateType Type(){ return XSI_USER_DATA_BLOB; }

	/*! Commits semantic layer data
		\return Whether or not commit was a success
	*/
	SI_Error Synchronize();

	///////////////////////////////////////////////////////////////////////////
	// User data //////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	/*! Returns pointer the user data array
		\return Pointer to the array containing the user data
	*/
	SI_UByte* GetUserDataPtr();

	/*! Returns the user data array
		\return Array of user data
	*/
	CSLUByteArray* GetUserData();

	/*! Returns the size of the user data array
		\return Size of the user data
	*/
	SI_Int GetUserDataSize();


private:
	CSLIntProxy		m_DataSize;
    CSLUByteArray	m_UserData;
	CSLTemplate*		m_pOwner;

	SI_Void* m_pReserved;
};


#endif
