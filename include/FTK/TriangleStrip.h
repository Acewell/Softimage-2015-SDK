//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file TriangleStrip.h
	\brief Defines the CSLTriangleStrip class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _TRIANGLESTRIP_H
#define _TRIANGLESTRIP_H

#include "Template.h"

class CSLTriangleStripList;

#ifndef _SL_INT_ARRAY_PROXY_EXPORT_
#define _SL_INT_ARRAY_PROXY_EXPORT_
#endif

/*! \brief This class represents an \xx ftk_SI_TriStrip SI_TriStrip \endxx template.

	Describes a triangle strip (see the \xx ftk_SI_TriStrip SI_TriStrip \endxx template reference).
	The triangles in this list can have normals, UV and color information as well.

	\tip You can use the GetNormalIndices(), GetUVIndices() and GetColorIndices() to see whether
		the return value is non-NULL.

	\sa CSLTriangleStripList
	\sa CSLTriangleList
	\sa CSLPolygonList
*/
class XSIEXPORT CSLTriangleStrip
    : public CSLTemplate
{
public:
	/*! Proxy class that allows modifying a list of SI_Int like an array.
	*/
	typedef CSLArrayProxy<SI_Int, SI_Int, 1> CSLIntArray;

	CSLTriangleStrip(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate, CSLTriangleStripList* in_pTriStripList);
	virtual ~CSLTriangleStrip();

	/*!	Returns the number of vertices in this strip.
		\return Number of vertices.
	*/
	SI_Int					GetVertexCount () { return m_VertexIndices.GetUsed(); }

	/*! Returns the vertex indices array proxy.
		\return Pointer to an array proxy of vertex indices.
	*/
	CSLIntArray*			GetVertexIndices() { return &m_VertexIndices; }

	/*! Returns an array of SI_Int containing the vertex index list.
		\return Array of SI_Int
	*/
	SI_Int*					GetVertexIndicesPtr() { return m_VertexIndices.ArrayPtr(); }

	/*! Creates a normal indices array.
		\return Pointer to the newly created array.
	*/
	CSLIntArray*			CreateNormalIndices();

	/*! Returns the normal indices array proxy.
		\return Pointer to an array proxy of normal indices.
	*/
	CSLIntArray*			GetNormalIndices() { return m_NormalIndices; }

	/*! Returns an array of SI_Int containing the normal index list.
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
	CSLIntArray*			CreateColorIndices();

	/*! Returns the color indices array proxy.
		\return Pointer to an array proxy of color indices.
	*/
	CSLIntArray*			GetColorIndices() { return m_ColorIndices; }

	/*! Returns an array of SI_Int containing the color index list.
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
	CSLIntArray*			AddUVArray();

	/*! Returns the number of texture coordinate arrays.
		\param[in] in_nId	Number of UV arrays.
		\return Pointer to the newly created array.
	*/
	CSLIntArray*			GetUVIndices(SI_Int in_nId);

	/*! Returns the UV indices array proxy.
		\param[in]	in_nId	Identification of the UV array to retrieve.
		\return Pointer to an array proxy of UV indices.
	*/
	SI_Int*					GetUVIndicesPtr(SI_Int in_nId);

	/*! Returns an array of SI_Int containing the UV index list.
		\return Array of SI_Int
	*/
	SI_Error				RemoveUVArray();

	/*! Removes the last UV indices array.
		\return Error code.
	*/
	SI_Error				ClearUVArrays();

	/*! Removes all UV indices array.
		\return Error code.
	*/
	SI_Int					GetUVArrayCount();

	/*! Returns the type of this template
		\retval CSLTemplate::SI_TRIANGLE_STRIP Template type
	*/
	virtual ETemplateType	Type() { return SI_TRIANGLE_STRIP; }
	virtual SI_Error		Synchronize();

private:
	CSLIntArray				m_VertexIndices;

	CSLIntArray*			m_NormalIndices;
	CSIBCArray<CSLIntArray* >	m_UVIndices;
	CSLIntArray*			m_ColorIndices;

	SI_Bool 				m_bSingleUV;
	SI_Int					m_iArrayCount;

	void *m_pReserved;	// reserved for future extension
};

#endif
