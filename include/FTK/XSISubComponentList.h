//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSISubComponentList.h
	\brief Defines the CSLXSISubComponentList class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _XSISUBCOMPONENTLIST_H
#define _XSISUBCOMPONENTLIST_H

#include "Template.h"

/*! \brief This class represents an \xx ftk_XSI_SubComponentList XSI_SubComponentList \endxx template.

Describes a subcomponent list base class for dotXSI 5.0+ (see the
	\xx ftk_XSI_SubComponentList XSI_SubComponentList \endxx template reference).

	This class holds a list of attribute references. Each attributes list is referenced by name and a
	corresponding indices array matches the sub component node with the attribute value.

	CSLXSISubComponentList allows an element composed of sub-component (vertex list, polygon list, etc.)
	to referenced attributes (position, normal, colors, etc.) for its nodes, by name. A corresponding indices
	array is associated to each attribute reference to match the subcomponent node with the attribute value.
*/
class XSIEXPORT CSLXSISubComponentList
	: public CSLTemplate
{
public:
	/*! Proxy class that allows modifying a list of SI_Int like an array.
	*/
	typedef CSLArrayProxy<SI_Int, SI_Int, 1> CSLIntArray;

	/*! Proxy class that allows modifying a list of SI_Char* like an array.
	*/
	typedef CSLArrayProxy<SI_Char*, SI_Char*, 1> CSLStringArray;

	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Refered template
		\return an instance of CSLXSISubComponentList
	*/
	CSLXSISubComponentList(CSLScene *in_pScene, CSLModel *in_pModel, CdotXSITemplate *in_pTemplate);

	/*! Destructor
	*/
	virtual ~CSLXSISubComponentList();

	/*! Returns the number of node (polynode/vertex/etc.) in this sub component list.
		\return Number of sub component node.
	*/
	SI_Int								GetCount();

	/*! Sets the number of node (polynode/vertex/etc.) in this sub component list.
		\return Error code.
	*/
	virtual SI_Error					SetCount(SI_Int /*!< Number of nodes in this subcomponent list */);

	/*!	Returns the number of attribute accessors.
		\return Number of attribute accessors.
	*/
	SI_Int								GetAttributeCount();

	/*! Creates a new attribute accessor element.
		\return The index of the newly created attribute elements.
	*/
	SI_Int								AddAttribute(SI_Char* /*!< Name for new attribute */);

	/*!	Removes the last attribute accessor.
		\return Error code.
	*/
	SI_Error							RemoveAttribute();

	/*!	Removes all the attribute accessors.
		\return Error code.
	*/
	SI_Error							ClearAttribute();

	/*! Returns the attribute indices.
		\param[in] in_iIndex	Index of attribute index to find
		\return Attribute indices.
	*/
	CSLIntArray*						GetAttributeIndices(SI_Int in_iIndex);

	/*! Returns the attribute indices array.
		\return Attribute indices array.
	*/
	CSIBCArray<CSLIntArray*>*			GetAttributeIndicesArray();

	/*! Returns the attribute name array.
		\return Attribute name array.
	*/
	CSLStringArray*						GetAttributeNameArray();

	/*! Returns the index of the first attribute with the specified name from the array.
		\param[in] in_pName	Name of attribute to find
		\return The attribute indices array of the attibute with the specified name.
	*/
	CSLArrayProxy<SI_Int, SI_Int, 1>*	GetAttributeByName(const SI_Char* in_pName);

	/*! Returns the associated semantic
		\param[in] in_iIndx	Index of semantic to find
		\return The semantic
	*/
	CSIBCString&						GetSemantic(int in_iIndx);

	/*! Sets the associated semantic
		\param[in] in_iIndx			Index of source to set
		\param[in] in_szSemantic	Semantic to set
	*/
	SI_Void								SetSemantic( int in_iIndx, CSIBCString in_szSemantic);

	/*! Returns the associated Source
		\param[in] in_iIndx	Index of source to find
		\return The Source
	*/
	CSIBCString&						GetSource(int in_iIndx);

	/*! Sets the associated Source
		\param[in] in_iIndx		Index of source to set
		\param[in] in_szSource	Source to set
	*/
	SI_Void								SetSource( int in_iIndx, CSIBCString in_szSource);

protected:
	SI_Int	m_iCount; // number of node

	CSIBCArray<CSLIntArray*>	m_AttributeIndicesArray;
	CSLStringArray			m_AttributeNameArray;

	CSIBCArray<CSIBCString>		m_szSemantic;
	CSIBCArray<CSIBCString>		m_szSource;

	void *m_pReserved;	// reserved for future extension
};

#endif
