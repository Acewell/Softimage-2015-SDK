//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file Instance.h
	\brief Defines the CSLInstance class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _INSTANCE_H
#define _INSTANCE_H

#include "Primitive.h"



/*! \brief This class represents an \xx ftk_SI_Instance SI_Instance \endxx template.

	Describes an instance primitive (see the \xx ftk_SI_Instance SI_Instance \endxx
	template reference).
*/
class XSIEXPORT CSLInstance
	: public CSLPrimitive
{
public:
	/*! Constructor
		\param[in] in_pScene	Pointer to the scene containing the instance
		\param[in] in_pModel	Pointer to the model containing the instance
		\param[in] in_pTemplate	Pointer to the CdotXSITemplate containing the instance
		\return an instance of CSLInstance
	*/
	CSLInstance(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	/*! Destructor
	*/
	virtual ~CSLInstance();

	/*!	Returns the reference model of the instance.
		\return Pointer to the reference model.
	*/
	CSLModel* GetReference();

	/*!	Changes the reference model object of the instance.
		\param[in]	in_pModel	New reference model object.
	*/
	SI_Void SetReference(CSLModel* in_pModel);

	/*! Synchronizes this instance with its IO layer representation
		\retval SI_Error::SI_SUCCESS this function always returns SI_SUCCESS
	*/
    virtual SI_Error Synchronize();

	/*! Returns the template type of the instance
		\retval CSLTemplate::SI_INSTANCE the template type
	*/
    virtual ETemplateType Type() { return SI_INSTANCE; }

private:
	CSLModel* m_pReference;

	void *m_pReserved;	// reserved for future extension
};

#endif
