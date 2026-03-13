//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file PolygonList.h
	\brief Defines the CSLPolygonList class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _POLYGONLIST_H
#define _POLYGONLIST_H

#include "Template.h"

#ifndef _SL_INT_ARRAY_PROXY_EXPORT_
#define _SL_INT_ARRAY_PROXY_EXPORT_

//XSITEMPLATEEXP template class XSIEXPORT CSLArrayProxy<SI_Int, SI_Int, 1>;

#endif // _SL_INT_ARRAY_PROXY_EXPORT_

class CSLBaseMaterial;

/*! \brief This class represents an \xx ftk_SI_PolygonList SI_PolygonList \endxx template.

	Describes a list of polygons that are made up of N number of vertices (see the
	\xx ftk_SI_PolygonList SI_PolygonList \endxx template reference). The polygons in this list can
	have normals, UV and color information as well.

	\tip You can use the GetNormalIndices(), GetUVIndices() and GetColorIndices() and check
		if the return value is non-NULL.
		<BR><BR>
		You can use GetPolygonCount() to get the number of polygons in the list.
		<BR><BR>
		To find out how many vertices a particular polygon uses, first get the list of polygon vertex
		count using GetPolygonVertexCountList().
*/
class XSIEXPORT CSLPolygonList
	: public CSLTemplate
{
public:
	/*! Proxy class that allows modifying a list of SI_Int like an array.
	*/
	typedef CSLArrayProxy<SI_Int, SI_Int, 1> CSLIntArray;

	/*! Constructor
		\param[in] in_pScene	Pointer to the scene containing the polygon list
		\param[in] in_pModel	Pointer to the model containing the polygon list
		\param[in] in_pTemplate	Pointer to the CdotXSITemplate containing the polygon list
		\return an instance of CSLPolygonList
	*/
	CSLPolygonList(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	/*! Destructor
	*/
	virtual ~CSLPolygonList();

	/*! Returns the number of polygons in this list.
		\return Number of polygons
	*/
	SI_Int			GetPolygonCount () { return m_PolygonVertexCount.GetUsed(); }

	/*! Returns the polygon vertex count array proxy.
		\return Pointer to an array proxy of polygon vertex count.
	*/
	CSLIntArray*	GetPolygonVertexCountList() { return &m_PolygonVertexCount; };

	/*! Returns an array of SI_Int containing the number of vertices for each polygon.
		\return Array of SI_Int
	*/
	SI_Int* 		GetPolygonVertexCountListPtr() { return m_PolygonVertexCount.ArrayPtr(); }

	/*! Returns the number of vertices referred by all polygons in this list.
		\return Number of vertices
	*/
	SI_Int			GetVertexCount () { return m_VertexIndices.GetUsed(); }

	/*! Returns the vertex indices array proxy.
		\return Pointer to an array proxy of vertex indices.
	*/
	CSLIntArray*	GetVertexIndices() { return &m_VertexIndices; };

	/*! Returns an array of SI_Int containing the vertex index list.
		\return Array of SI_Int
	*/
	SI_Int* 		GetVertexIndicesPtr() { return m_VertexIndices.ArrayPtr(); }

	/*! Creates a normal indices array.
		\return Pointer to the newly created array.
	*/
	CSLIntArray*	CreateNormalIndices();

	/*! Returns the normal indices array proxy.
		\return Pointer to an array proxy of normal indices.
	*/
	CSLIntArray*	GetNormalIndices() { return m_NormalIndices; }

	/*! Returns an array of SI_Int containing the normal index list.
		\return Array of SI_Int
	*/
	SI_Int* 		GetNormalIndicesPtr();

	/*!	Destroy the normal indices array.
		\return Error code.
	*/
	SI_Error		DestroyNormalIndices();

	/*! Creates a color indices array.
		\return Pointer to the newly created array.
	*/
	CSLIntArray*	CreateColorIndices();

	/*! Returns the color indices array proxy.
		\return Pointer to an array proxy of color indices.
	*/
	CSLIntArray*	GetColorIndices() { return m_ColorIndices; }

	/*! Returns an array of SI_Int containing the color index list.
		\return Array of SI_Int
	*/
	SI_Int* 		GetColorIndicesPtr();

	/*!	Destroys the color indices array.
		\return Error code.
	*/
	SI_Error		DestroyColorIndices();

	/*! Creates a new UV indices array.
		\return Pointer to the newly created array.
	*/
	CSLIntArray*	AddUVArray();

	/*! Returns the number of texture coordinate arrays.
		\return Number of UV arrays.
	*/
	SI_Int			GetUVArrayCount();

	/*! Returns the UV indices array proxy.
		\param[in]	in_nId	Identification of the UV array to retrieve.
		\return Pointer to an array proxy of UV indices.
	*/
	CSLIntArray*	GetUVIndices(SI_Int in_nId);

	/*! Returns an array of SI_Int containing the UV index list.
		\param[in]	in_nId	Identification of the UV array to retrieve.
		\return Array of SI_Int
	*/
	SI_Int* 		GetUVIndicesPtr(SI_Int in_nId);

	/*! Removes the last UV indices array.
		\return Error code.
	*/
	SI_Error		RemoveUVArray();

	/*! Removes all UV indices array.
		\return Error code.
	*/
	SI_Error		ClearUVArrays();

	/*!	Returns the material object of the polygon list.
		\return Texture projection name.
	*/
	CSLBaseMaterial*	GetMaterial() { return m_pMaterial; }

	/*!	Changes the material object of the polygon list.
		\param[in]	in_pNewMaterial	New material object.
	*/
	SI_Void				SetMaterial(CSLBaseMaterial *in_pNewMaterial) { m_pMaterial = in_pNewMaterial; }

	/*! Updates the template with information from this polygon list
		\return Whether or not the template could be updated
	*/
    virtual SI_Error Synchronize();

	/*! Returns the type of this template
		\retval CSLTemplate::SI_POLYGON_LIST Template type
	*/
	virtual ETemplateType Type() { return SI_POLYGON_LIST; };

	/*! Returns a handle on one of this polygon list's parameters by using its name
		\param[in] in_szName the name of the parameter to get the handle from
		\return the handle to the parameter
	*/
    virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);

private:
	CSLBaseMaterial*		m_pMaterial;
	CSLIntArray 			m_PolygonVertexCount;
	CSLIntArray 			m_VertexIndices;

	CSLIntArray*			m_NormalIndices;
	CSLIntArray*			m_ColorIndices;
	CSIBCArray<CSLIntArray* >	m_UVIndices;

	SI_Bool 				m_bSingleUV;
	SI_Int					m_iArrayCount;

	void *m_pReserved;	// reserved for future extension
};

#endif
