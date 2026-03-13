//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSIIndexList.h
	\brief Defines the CSLXSIIndexList class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _XSIINDEXLIST_H
#define _XSIINDEXLIST_H

#include "Template.h"


/*! \brief This class represents an \xx ftk_XSI_IndexList XSI_IndexList \endxx template.

	Represents an index list for dotXSI 6.0+ (see the \xx ftk_XSI_IndexList XSI_IndexList \endxx template reference).
	This class holds a list of values for a specific attribute of a given type and semantic. It also allows an attribute
	(position, normal, color, texcoord, etc.) to be associated with vertices or polynodes.
*/
class XSIEXPORT CSLXSIIndexList
	: public CSLTemplate
{
public:
	/*! Proxy class that allows modifying a list of SI_Int like an array.
	*/
	typedef CSLArrayProxy<SI_Int, SI_Int, 1> CSLIntArray;

	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Refered template
		\return an instance of CSLXSIIndexList
	*/
	CSLXSIIndexList(CSLScene *in_pScene, CSLModel *in_pModel, CdotXSITemplate *in_pTemplate);

	/*! Destructor
	*/
	virtual ~CSLXSIIndexList();

	/*! Returns the number of values in the attribute list.
		\return Number of attribute values.
	*/
	SI_Int							GetCount();

	/*! Returns the the attribute value array so that the values can be edited.
		\return The attribute value array.
	*/
	CSLIntArray*					GetIndexArray() { return &m_IndexArray; }

	/*! Returns the template type
		\retval CSLTemplate::XSI_INDEX_LIST the template type of the index list
	*/
	virtual ETemplateType			Type() { return XSI_INDEX_LIST; }

	/*! Commits the current template information
		\return Whether or not the commit was successful
	*/
	virtual SI_Error Synchronize();

private:
	CSLIntArray						m_IndexArray;

	void *m_pReserved;	// reserved for future extension
};

#endif
