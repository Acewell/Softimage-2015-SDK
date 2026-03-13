//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file TriangleList.h
	\brief Defines the CSLTriangleList class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _TRIANGLELIST_H
#define _TRIANGLELIST_H

#include "Template.h"

class CSLBaseMaterial;

struct SLTriangle
{
	SI_Int	m_iVtx1;
	SI_Int	m_iVtx2;
	SI_Int	m_iVtx3;
};

/*! \brief This class represents an \xx ftk_SI_TriangleList SI_TriangleList \endxx template.

	Describes a list of triangles (see the \xx ftk_SI_TriangleList SI_TriangleList \endxx
	template reference). It may also contain information about normals, UV coordinates and color.

	\tip You can use the GetNormalIndices(), GetUVIndices() and GetColorIndices() to see whether
		or not the return value is non-NULL.
		<BR><BR>
		To get the number of triangles in the list, use GetTriangleCount().

	\sa CSLPolygonList
	\sa CSLTriStripList
*/
class XSIEXPORT CSLTriangleList
	: public CSLTemplate
{
public:
	/*! Proxy class that allows modifying a list of SLTriangle structures like an array.
	*/
	typedef CSLArrayProxy<SLTriangle, SI_Int, 3> CSLTriangleArray;

	CSLTriangleList(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
	virtual ~CSLTriangleList();

	/*!	Returns the number of triangles in this list.
		\return Number of triangles
	*/
	SI_Int					GetTriangleCount() { return m_VertexIndices.GetUsed(); };

	/*!	Returns an array of SI_Int containing the vertex index list.
		\return Array of SI_Int
	*/
	SI_Int*					GetVertexIndicesPtr() { return (SI_Int *) m_VertexIndices.ArrayPtr(); }

	/*! Returns the vertex indices array proxy.
		\return Pointer to an array proxy of vertex indices.
	*/
	CSLTriangleArray*		GetVertexIndices() { return &m_VertexIndices; }

	/*! Creates a normal indices array.
		\return Pointer to the newly created array.
	*/
	CSLTriangleArray*		CreateNormalIndices();

	/*! Returns the normal indices array proxy.
		\return Pointer to an array proxy of normal indices.
	*/
	CSLTriangleArray*		GetNormalIndices() { return m_NormalIndices; }

	/*!	Returns an array of SI_Int containing the normal index list.
		\return Array of SI_Int
	*/
	SI_Int*					GetNormalIndicesPtr();

	/*!	Destroys the normal indices array.
		\return Error code.
	*/
	SI_Error				DestroyNormalIndices();

	/*! Creates a color indices array.
		\return Pointer to the newly created array.
	*/
	CSLTriangleArray*		CreateColorIndices();

	/*! Returns the color indices array proxy.
		\return Pointer to an array proxy of color indices.
	*/
	CSLTriangleArray*		GetColorIndices() { return m_ColorIndices; }

	/*!	Returns an array of SI_Int containing the color index list.
		\return Array of SI_Int
	*/
	SI_Int*					GetColorIndicesPtr();

	/*!	Destroys the color indices array.
		\return Error code.
	*/
	SI_Error				DestroyColorIndices();

	/*! Creates a new UV indices array.
		\return Pointer to the newly created array.
	*/
	CSLTriangleArray*		AddUVArray();

	/*! Returns the number of texture coordinate arrays.
		\return Number of UV arrays.
	*/
	SI_Int					GetUVArrayCount();

	/*!	Returns an array of SI_Int containing the UV index list.
		\param[in] in_nId Identification of the UV index list to retrieve.
		\return Array of SI_Int
	*/
	SI_Int*					GetUVIndicesPtr(SI_Int in_nId);

	/*! Returns the UV indices array proxy.
		\param[in]	in_nId	Identification of the UV array to retrieve.
		\return Pointer to an array proxy of UV indices.
	*/
	CSLTriangleArray*		GetUVIndices(SI_Int in_nId);

	/*! Removes the last UV indices array.
		\return Error code.
	*/
	SI_Error				RemoveUVArray();

	/*! Removes all UV indices array.
		\return Error code.
	*/
	SI_Error				ClearUVArrays();

	/*!	Returns the material object of the triangle list.
		\return Texture projection name.
	*/
	CSLBaseMaterial*		GetMaterial() { return m_pMaterial; }

	/*!	Changes the material object of the triangle list.
		\param[in]	in_pNewMaterial	New material object.
	*/
	SI_Void					SetMaterial(CSLBaseMaterial *in_pNewMaterial) { m_pMaterial = in_pNewMaterial; }

	/*!	Returns the type of this template
		\retval CSLTemplate::SI_TRIANGLE_LIST Template type
	*/
	virtual ETemplateType	Type() { return SI_TRIANGLE_LIST; }
	virtual SI_Error		Synchronize();
    virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);

private:
	CSLBaseMaterial*		m_pMaterial;
	CSLTriangleArray		m_VertexIndices;

	CSLTriangleArray*		m_NormalIndices;
	CSIBCArray<CSLTriangleArray* >	m_UVIndices;
	CSLTriangleArray*		m_ColorIndices;

	SI_Bool 				m_bSingleUV;
	SI_Int					m_iArrayCount;

	void *m_pReserved;	// reserved for future extension
};

#endif
