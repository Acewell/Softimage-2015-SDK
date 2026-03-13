//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file Shape.h
	\brief Defines the CSLShape class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _SHAPE_H
#define _SHAPE_H

#include "BaseShape.h"

/*! \brief This class represents an \xx ftk_SI_Shape SI_Shape \endxx template.

	Describes a mesh shape (see the \xx ftk_SI_Shape SI_Shape \endxx template reference).
	The CSLShape holds the mesh's vertex positions, normals, texture coordinates and color
	information.
*/
class XSIEXPORT CSLShape
	: public CSLBaseShape
{
public:

	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Referred template
		\param[in] in_Type the type of shape to construct
		\return an instance of CSLShape
	*/
	CSLShape(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate, EShapeType in_Type);

	/*! Destructor
	*/
	virtual ~CSLShape();

	/*! Creates a texture coordinates array.
		\return Pointer to the newly created array.
	*/
	CSLVector2DArray*				CreateUVCoords();

	/*! Creates an indexed texture coordinates array.
		\return Pointer to the newly created indexed array.
	*/
	CSLIndexedVector2DArray*		CreateIndexedUVCoords();

	/*! Returns the number of texture coordinates.
		\return Number of UV.
	*/
	SI_Int							GetUVCoordCount();

	/*! Returns the texture coordinate array proxy.
		\return Pointer to an array proxy of UV.
	*/
	CSLVector2DArray*				GetUVCoordList();

	/*! Returns an array of CSIBCVector2D that describes the texture coordinates for this mesh.
		\return Array of texture coordinates
	*/
	CSIBCVector2D*					GetUVCoordListPtr();

	/*! Returns the indexed texture coordinate array proxy.
		\return Pointer to an array proxy of indexed UV.
	*/
	CSLIndexedVector2DArray*		GetIndexedUVCoordList();

	/*! Returns an array of SLIndexedVector2D that describes the indexed texture coordinates for this mesh.
		\return Array of indexed texture coordinates
	*/
	SLIndexedVector2D*				GetIndexedUVCoordListPtr();

	/*!	Destroys the texture coordinates array.
		\return Error code.
	*/
	SI_Error						DestroyUVCoords();

	/*! Returns the template type
		\retval CSLTemplate::SI_SHAPE the template type of the shape surface
	*/
	virtual ETemplateType			Type() { return SI_SHAPE; };

	/*! Synchronizes this shape instance with its IO layer representation
		\retval SI_Error::SI_SUCCESS this function always returns SI_SUCCESS
	*/
	virtual SI_Error				Synchronize();

private:
	CSLVector2DArray*				m_pUVCoords;
	CSLIndexedVector2DArray*		m_pIndexedUVCoords;
	CSLIntProxy*					m_iNbUVCoords;
	CSLStringProxy* 				m_pUVStringProxy;

	void *m_pReserved;	// reserved for future extension
};

#endif

