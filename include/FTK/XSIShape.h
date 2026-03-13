//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSIShape.h
	\brief Defines the CSLXSIShape class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _XSISHAPE_H
#define _XSISHAPE_H

#include "Template.h"
#include "Scene.h"
#include "Model.h"
#include "XSISubComponentAttributeList.h"



/*! \brief Describes a Mesh Shape for dotXSI 5.0+ (see the \xx ftk_XSI_Shape XSI_Shape \endxx
	template reference).

	This class holds a generic sub component attribute list that describes vertex or polynode attributes.
	It implements helpers for the following attributes: vertex positions, multiple normals, multiple
	texture coordinates and multiple colors.
*/
class XSIEXPORT CSLXSIShape
	: public CSLTemplate
{
public:
	/*! Types of shapes
	*/
	enum EXSIShapeType
	{
		XSI_ORDERED,	/*!< The shape is of ordered type */
		XSI_INDEXED,	/*!< The shape is of indexed type */
	};

	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Refered template
		\param[in] in_Type the type of shape to construct
		\return an instance of CSLShape
	*/
	CSLXSIShape(CSLScene *in_pScene, CSLModel *in_pModel, CdotXSITemplate *in_pTemplate, EXSIShapeType in_Type);

	/*! Destructor
	*/
	virtual ~CSLXSIShape();

	/*!	Adds a new sub component attribute list.
		\param[in] in_AttributeType Type of attribute list to add
		\return Pointer to the newly created list.
	*/
	virtual CSLXSISubComponentAttributeList*	AddAttributeList(CSLXSISubComponentAttributeList::EAttributeType in_AttributeType);

	/*!	Returns the number of sub component attribute lists.
		\return Number of sub component attribute lists.
	*/
	SI_Int								GetAttributeListCount();

	/*!	Returns the number of sub component attribute lists with the given semantic.
		\param[in] in_pSemantic Semantic to find
		\return Number of sub component attribute lists with the given semantic.
	*/
	SI_Int								GetAttributeListCountBySemantic(SI_Char* in_pSemantic);

	/*!	Returns an array of all sub component attribute list.
		\return Array of pointers to sub component attribute list.
	*/
	CSIBCArray<CSLXSISubComponentAttributeList*>*	AttributeLists();

	/*!	Removes the last sub component attribute list.
		\return Error code.
	*/
	SI_Error							RemoveAttributeList();

	/*!	Removes the specified sub component attribute list.
		\param[in] in_pAttributeList Attribute list to remove
		\return Error code.
	*/
	SI_Error	RemoveAttributeList( CSLXSISubComponentAttributeList* in_pAttributeList );

	/*!	Removes the specified sub component attribute list.
		\param[in] in_iIndex Index of list to remove
		\return Error code.
	*/
	SI_Error	RemoveAttributeList( SI_Int in_iIndex );

	/*!	Removes all sub component attribute list.
		\return Error code.
	*/
	SI_Error							ClearAttributeLists();

	/*!	Removes all sub component attribute list that has the given semantic.
		\param[in] in_pSemantic Semantic to find
		\return Error code.
	*/
	SI_Error							ClearAttributeListsBySemantic(SI_Char *in_pSemantic);

	/*!	Connects a new sub component attribute list.
		\param[in] in_pNewXSISubComponentAttributeList New sub component attribute list
		\return The newly connected sub component attribute list.
	*/
	CSLXSISubComponentAttributeList*	ConnectAttributeList( CSLXSISubComponentAttributeList* in_pNewXSISubComponentAttributeList );

	/*!	Returns the first sub component attribute list with the corresponding semantic.
		\param[in] in_pSemantic Semantic to find
		\return Pointer to the first sub component attribute list with the corresponding semantic.
	*/
	CSLXSISubComponentAttributeList* GetFirstAttributeListBySemantic( SI_Char* in_pSemantic );

	/*!	Returns the next sub component attribute list with the corresponding semantic.
		\param[in] in_pSemantic Semantic to find
		\return Pointer to the next sub component attribute list with the corresponding semantic.
	*/
	CSLXSISubComponentAttributeList* GetNextAttributeListBySemantic( SI_Char* in_pSemantic );

	//**********************************************************************************
	// Vertex position attribute helper (always only one vertex position attibute list)
	//**********************************************************************************

	/*!	Adds a new POSITION attribute list.
		\return Pointer to the newly created POSITION attribute list.
	*/
	CSLXSISubComponentAttributeList*	AddVertexPositionList();

	/*!	Returns the POSITION attribute list.
		\return Pointer to the POSITION attribute list.
	*/
	CSLXSISubComponentAttributeList*	GetVertexPositionList();

	/*!	Removes the last POSITION attribute list.
		\return Error code.
	*/
	SI_Error							RemoveVertexPositionList();

	//**********************************************************************************
	// Normal attribute helper
	//**********************************************************************************

	/*!	Adds a new NORMAL attribute list.
		\return Pointer to the newly created NORMAL attribute list.
	*/
	CSLXSISubComponentAttributeList*	AddNormalList();

	/*!	Returns the first NORMAL attribute list.
		\return Pointer to the first NORMAL attribute list.
	*/
	CSLXSISubComponentAttributeList*	GetFirstNormalList();

	/*!	Returns the next NORMAL attribute list.
		\return Pointer to the next NORMAL attribute list.
	*/
	CSLXSISubComponentAttributeList*	GetNextNormalList();

	/*!	Returns the number of NORMAL attribute list.
		\return The number of NORMAL attribute list.
	*/
	SI_Int								GetNormalListCount();

	/*!	Removes the last NORMAL attribute list.
		\return Error code.
	*/
	SI_Error							RemoveNormalList();

	/*!	Clears all the NORMAL attribute list.
		\return Error code.
	*/
	SI_Error							ClearNormalLists();

	//**********************************************************************************
	// Color attribute helper
	//**********************************************************************************

	/*!	Adds a new COLOR attribute list.
		\return Pointer to the newly created COLOR attribute list.
	*/
	CSLXSISubComponentAttributeList*	AddColorList();

	/*!	Returns the first COLOR attribute list.
		\return Pointer to the first COLOR attribute list.
	*/
	CSLXSISubComponentAttributeList*	GetFirstColorList();

	/*!	Returns the next COLOR attribute list.
		\return Pointer to the next COLOR attribute list.
	*/
	CSLXSISubComponentAttributeList*	GetNextColorList();

	/*!	Returns the number of COLOR attribute list.
		\return The number of COLOR attribute list.
	*/
	SI_Int								GetColorListCount();

	/*!	Removes the last COLOR attribute list.
		\return Error code.
	*/
	SI_Error							RemoveColorList();

	/*!	Clears all the COLOR attribute list.
		\return Error code.
	*/
	SI_Error							ClearColorLists();

	//**********************************************************************************
	// TexCoord attribute helper
	//**********************************************************************************

	/*!	Adds a new TEXCOORD attribute list.
		\return Pointer to the newly created TEXCOORD attribute list.
	*/
	CSLXSISubComponentAttributeList*	AddTexCoordList();

	/*!	Returns the first TEXCOORD attribute list.
		\return Pointer to the first TEXCOORD attribute list.
	*/
	CSLXSISubComponentAttributeList*	GetFirstTexCoordList();

	/*!	Returns the next TEXCOORD attribute list.
		\return Pointer to the next TEXCOORD attribute list.
	*/
	CSLXSISubComponentAttributeList*	GetNextTexCoordList();

	/*!	Returns the number of TEXCOORD attribute list.
		\return The number of TEXCOORD attribute list.
	*/
	SI_Int								GetTexCoordListCount();

	/*!	Removes the last TEXCOORD attribute list.
		\return Error code.
	*/
	SI_Error							RemoveTexCoordList();

	/*!	Clears all the TEXCOORD attribute list.
		\return Error code.
	*/
	SI_Error							ClearTexCoordLists();

	//**********************************************************************************
	// WeightMap attribute helper
	//**********************************************************************************

	/*!	Adds a new WEIGHTMAP attribute list.
		\return Pointer to the newly created WEIGHTMAP attribute list.
	*/
	CSLXSISubComponentAttributeList*	AddWeightMapList();

	/*!	Returns the first WEIGHTMAP attribute list.
		\return Pointer to the first WEIGHTMAP attribute list.
	*/
	CSLXSISubComponentAttributeList*	GetFirstWeightMapList();

	/*!	Returns the next WEIGHTMAP attribute list.
		\return Pointer to the next WEIGHTMAP attribute list.
	*/
	CSLXSISubComponentAttributeList*	GetNextWeightMapList();

	/*!	Returns the number of WEIGHTMAP attribute list.
		\return The number of WEIGHTMAP attribute list.
	*/
	SI_Int								GetWeightMapListCount();

	/*!	Removes the last WEIGHTMAP attribute list.
		\return Error code.
	*/
	SI_Error							RemoveWeightMapList();

	/*!	Clears all the WEIGHTMAP attribute list.
		\return Error code.
	*/
	SI_Error							ClearWeightMapLists();

	//**********************************************************************************
	// Tangent attribute helper
	//**********************************************************************************

	/*!	Adds a new Tangent attribute list.
		\return Pointer to the newly created Tangent attribute list.
	*/
	CSLXSISubComponentAttributeList*	AddTangentList();

	/*!	Returns the first Tangent attribute list.
		\return Pointer to the first Tangent attribute list.
	*/
	CSLXSISubComponentAttributeList*	GetFirstTangentList();

	/*!	Returns the next Tangent attribute list.
		\return Pointer to the next Tangent attribute list.
	*/
	CSLXSISubComponentAttributeList*	GetNextTangentList();

	/*!	Returns the number of Tangent attribute list.
		\return The number of Tangent attribute list.
	*/
	SI_Int								GetTangentListCount();

	/*!	Removes the last Tangent attribute list.
		\return Error code.
	*/
	SI_Error							RemoveTangentList();

	/*!	Clears all the Tangent attribute list.
		\return Error code.
	*/
	SI_Error							ClearTangentLists();

	//**********************************************************************************
	// Binormal attribute helper
	//**********************************************************************************

	/*!	Adds a new Binormal attribute list.
		\return Pointer to the newly created Binormal attribute list.
	*/
	CSLXSISubComponentAttributeList*	AddBinormalList();

	/*!	Returns the first Binormal attribute list.
		\return Pointer to the first Binormal attribute list.
	*/
	CSLXSISubComponentAttributeList*	GetFirstBinormalList();

	/*!	Returns the next Binormal attribute list.
		\return Pointer to the next Binormal attribute list.
	*/
	CSLXSISubComponentAttributeList*	GetNextBinormalList();

	/*!	Returns the number of Binormal attribute list.
		\return The number of Binormal attribute list.
	*/
	SI_Int								GetBinormalListCount();

	/*!	Removes the last Binormal attribute list.
		\return Error code.
	*/
	SI_Error							RemoveBinormalList();

	/*!	Clears all the Binormal attribute list.
		\return Error code.
	*/
	SI_Error							ClearBinormalLists();

	/*! Returns the template type of the shape surface
		\retval CSLTemplate::XSI_SHAPE the template type
	*/
	virtual ETemplateType				Type() { return XSI_SHAPE; };

	/*! Returns the shape type
		\return The type of the shape surface (XSI_ORDERED or XSI_INDEXED)
	*/
	EXSIShapeType						GetShapeType() { return m_eShapeType; }

	/*! Sets the shape type
		\param[in] in_eShapeType	The new shape type
	*/
	void								SetShapeType(EXSIShapeType in_eShapeType) { m_eShapeType = in_eShapeType; }

	/*! Commits the current template information
		\return Whether or not the commit was successful
	*/
	virtual SI_Error Synchronize();

protected:
	CSIBCArray<CSLXSISubComponentAttributeList *>	m_AttributeLists;
	SI_Int											m_iCurrentAttributeListIndex;

	EXSIShapeType									m_eShapeType;

	void *m_pReserved;	// reserved for future extension
};

#endif
