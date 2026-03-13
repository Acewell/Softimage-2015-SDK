//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file Shape_35.h
	\brief Defines the CSLShape_35 class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _SHAPE_35_H
#define _SHAPE_35_H

#include "BaseShape.h"

class CSLUVCoordArray;

/*! \brief This class represents an \xx ftk_SI_Shape SI_Shape \endxx template.

	Describes a Mesh Shape for dotXSI 3.5+ (see the \xx ftk_SI_Shape SI_Shape \endxx
	template reference). The CSLShape holds the mesh's vertex positions, normals, texture
	coordinates and color information.

	This class allows a shape to contain more than one array of texture coordinates.
	Also, each array contains information about its texture projetion.
*/
class XSIEXPORT CSLShape_35
	: public CSLBaseShape
{
public:
	/*! Constructor
		\param in_pScene Parent scene
		\param in_pModel Parent model
		\param in_pTemplate Refered template
		\param in_Type the type of shape to construct
		\return an instance of CSLShape
	*/
	CSLShape_35(CSLScene *in_pScene, CSLModel *in_pModel, CdotXSITemplate *in_pTemplate, EShapeType in_Type);

	/*! Destructor
	*/
	virtual ~CSLShape_35();

	/*!	Adds a new texture coordinate array.
		\return Pointer to the newly created array.
	*/
	CSLUVCoordArray*				AddUVCoordArray();

	/*!	Returns the number of texture coordinate arrays.
		\return Number of UV arrays.
	*/
	SI_Int							GetUVCoordArrayCount();

	/*!	Returns an array of all texture coordinate arrays.
		\return Array of pointers to UV array.
	*/
	CSLUVCoordArray**				UVCoordArrays();

	/*!	Removes the last texture coordinate array.
		\return Error code.
	*/
	SI_Error						RemoveUVCoordArray();

	/*!	Removes all texture coordinate arrays.
		\return Error code.
	*/
	SI_Error						ClearUVCoordArrays();

	/*! Returns the template type of the shape surface
		\retval CSLTemplate::SI_SHAPE35 the template type
	*/
	virtual ETemplateType			Type() { return SI_SHAPE35; };

	/*! Synchronizes this shape instance with its IO layer representation
		\retval SI_Error::SI_SUCCESS this function always returns SI_SUCCESS
	*/
	virtual SI_Error				Synchronize();

private:
	CSIBCArray<CSLUVCoordArray *>	m_UVCoordArrays;

	void *m_pReserved;	// reserved for future extension
};

#endif
