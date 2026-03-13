//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file COLLADASubComponentAttributeList.h
	\brief Defines the CSLCOLLADASubComponentAttributeList class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _COLLADASUBCOMPONENTATTRIBUTELIST_H
#define _COLLADASUBCOMPONENTATTRIBUTELIST_H

#include "COLLADATemplate.h"
#include "XSISubComponentAttributeList.h"


/*! \brief Describes a sub-component attribute list for dotXSI 5.0+

The CSLXSISubComponentAttributeList holds a list of values for a specific attribute of a given type and semantic.
This class allows an attribute (position, normal, color, texcoord, etc.) to be associated with vertices or polynodes.
*/
class XSIEXPORT CSLCOLLADASubComponentAttributeList
	: public CSLXSISubComponentAttributeList
{
public:

	/*! Constructor
		\param[in]	in_pScene		Parent scene
		\param[in]	in_pModel		Parent model
		\param[in]	in_pTemplate	dotXSI template
	*/
	CSLCOLLADASubComponentAttributeList(CSLScene *in_pScene, CSLModel *in_pModel, CdotXSITemplate *in_pTemplate);

	/*! Destructor
	*/
	virtual ~CSLCOLLADASubComponentAttributeList();

	/*! Sets attribute type
		\param[in]	in_AttributeType	Type of attribute to set
	*/
	virtual SI_Void		SetAttributeType(EAttributeType in_AttributeType);
	virtual SI_Char*	GetSemantic() { return m_szSemantic.GetText(); };

	/*! Sets semantic
		\param[in]	in_Semantic	Semantic text to set
	*/
	virtual SI_Void		SetSemantic(SI_Char* in_Semantic) { m_szSemantic.SetText(in_Semantic);};
	virtual SI_Char*	GetSource() { return m_pMainID->GetVariantPtr()->p_cVal; };

	virtual SI_Error	Synchronize();

	SI_Void	SetVerticesDeclarationTemplate( CCOLLADATemplate* in_pDecl );
	SI_Void SetInputSemantics ( CdotXSITemplates* in_pTemplates );

private:
	CCOLLADATemplate* m_pAttributeArrayTemplate;
	CCOLLADATemplate *m_accessor ;
	CCOLLADATemplate*	m_pVertexDeclarationTemplate;
	CSIBCString m_szSemantic;

	CdotXSIParam*	m_pCountAttribute;
	CdotXSIParam*	m_pIDAttribute;

	CdotXSIParam*	m_pInnerCountAttribute;
	CdotXSIParam*	m_pStrideCountAttribute;
	CdotXSIParam*	m_pSourceIDAttribute;

	CdotXSIParam*	m_pMainID;
	CdotXSIParam*	m_pAttribArray;
};

#endif
