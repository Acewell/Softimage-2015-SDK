//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file UVCoordArray.h
	\brief Defines the CSLUVCoordArray class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _UVCOORDARRAY_H
#define _UVCOORDARRAY_H

#include "BaseShape.h"

/*! \brief Represents an array of UV coordinates.
\sa CSLShape_35
*/
class XSIEXPORT CSLUVCoordArray
{
public:
	CSLUVCoordArray(CdotXSITemplate *in_pTemplate, SI_Int in_nFirstIndex, CSLBaseShape::EShapeType in_Type);
	virtual ~CSLUVCoordArray();

	/*! Returns the number of texture coordinates.
		\return Number of UV.
	*/
	SI_Int									GetUVCoordCount();

	/*! Returns the texture coordinate array proxy.
		\return Pointer to an array proxy of UV.
	*/
	CSLBaseShape::CSLVector2DArray* 		GetUVCoordList();

	/*! Returns an array of CSIBCVector2D that describes the texture coordinates for this mesh.
		\return Array of texture coordinates
	*/
	CSIBCVector2D*							GetUVCoordListPtr();

	/*! Return the indexed texture coordinate array proxy.
		\return Pointer to an array proxy of indexed UV.
	*/
	CSLBaseShape::CSLIndexedVector2DArray*	GetIndexedUVCoordList();

	/*! Returns an array of SLIndexedVector2D that describes the indexed texture coordinates for this mesh.
		\return Array of indexed texture coordinates
	*/
	SLIndexedVector2D*						GetIndexedUVCoordListPtr();

	/*!	Returns the name of the texture projection.
		\return Texture projection name.
	*/
	SI_Char*								GetTextureProjection();

	/*!	Changes the name of the texture projection.
		\param[in]	in_szValue	New texture projection name.
	*/
	SI_Void 								SetTextureProjection(SI_Char* in_szValue);

	/*!	Synchronizes will all data in the FTK is up to date.
		\return Error code
	*/
	SI_Error								Synchronize();

private:
	CSLIntProxy								m_NbUVCoords;
	CSLStringProxy							m_TextureProjection;
	CSLBaseShape::CSLVector2DArray*			m_pUVCoords;
	CSLBaseShape::CSLIndexedVector2DArray*	m_pIndexedUVCoords;

	void *m_pReserved;	// reserved for future extension
    CSIBCVector2D*									GetUVCoords();
};

#endif
