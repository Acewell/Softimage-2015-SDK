//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSISubComponentAttributeList.h
	\brief Defines the CSLXSISubComponentAttributeList class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _XSISUBCOMPONENTATTRIBUTELIST_H
#define _XSISUBCOMPONENTATTRIBUTELIST_H

#include "Template.h"


/*! \brief This class represents an \xx ftk_XSI_SubComponentAttributeList XSI_SubComponentAttributeList \endxx template.

	Describes a sub-component attribute list for dotXSI 5.0+ (see the
	\xx ftk_XSI_SubComponentAttributeList XSI_SubComponentAttributeList \endxx template reference).

	This class holds a list of values for a specific attribute of a given type and semantic. It allows
	an attribute (position, normal, color, texcoord, etc.) to be associated with vertices or polynodes.
*/
class XSIEXPORT CSLXSISubComponentAttributeList
	: public CSLTemplate
{
public:
	/*! Proxy class that allows modifying a list of SI_Int like an array.
	*/
	typedef CSLArrayProxy<SI_Float, SI_Float, 1> CSLFloatArray;

	enum EAttributeType
	{
		FLOAT = 1,
		FLOAT2 = 2,
		FLOAT3 = 3,
		FLOAT4 = 4,
		FLOAT5 = 5,
	};

	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Refered template
		\return an instance of CSLXSISubComponentAttributeList
	*/
	CSLXSISubComponentAttributeList(CSLScene *in_pScene, CSLModel *in_pModel, CdotXSITemplate *in_pTemplate);

	/*! Destructor
	*/
	virtual ~CSLXSISubComponentAttributeList();

	/*! Returns the number of values in the attribute list.
		\return Number of attribute values.
	*/
	SI_Int							GetCount();

	/*! Returns the semantic of the attribute list.
		\return The semantic.
	*/
	virtual SI_Char*						GetSemantic() { return m_Semantic; }

	/*! Sets the semantic of the attribute list.
		\param[in]	in_Semantic	The semantic.
	*/
	virtual SI_Void 						SetSemantic(SI_Char* in_Semantic) { m_Semantic = in_Semantic; }

	/*! Returns the type of the attribute value.
		\return Type of the attribute value.
	*/
	EAttributeType					GetAttributeType() { return m_AttributeType; }

	/*! Sets the type of the attribute value.
		\param[in]	in_AttributeType	Type of the attribute value.
	*/
	virtual SI_Void							SetAttributeType(EAttributeType in_AttributeType);

	/*! Returns the the attribute value array so that the values can be edited.
		\return The attribute value array.
	*/
	CSLFloatArray*					GetAttributeArray() { return &m_AttributeArray; }

	/*! Returns the template type
		\retval CSLTemplate::XSI_SUB_COMPONENT_ATTRIBUTE_LIST the template type of the sub-component attribute list
	*/
	virtual ETemplateType			Type() { return XSI_SUB_COMPONENT_ATTRIBUTE_LIST; }

	/*! Commits the current template information
		\return Whether or not the commit was successful
	*/
	virtual SI_Error Synchronize();

private:
	CSLFloatArray					m_AttributeArray;
	CSLStringProxy					m_Semantic;
	EAttributeType					m_AttributeType;

	void *m_pReserved;	// reserved for future extension
};

#endif
