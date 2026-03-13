//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file COLLADAInstance.h
	\brief Defines the CSLCOLLADAInstance class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _COLLADAINSTANCE_H
#define _COLLADAINSTANCE_H

#include <Instance.h>

/*! \brief Describes an instance primitive..
*/
class XSIEXPORT CSLCOLLADAInstance
	: public CSLInstance
{
public:
	/*! Constructor
	* \param in_pScene	Pointer to the scene containing the instance
	* \param in_pModel	Pointer to the model containing the instance
	* \param in_pTemplate	Pointer to the CdotXSITemplate containing the instance
	* \return an instance of CSLInstance
	*/
	CSLCOLLADAInstance(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate) : CSLInstance(in_pScene, in_pModel, in_pTemplate){};

	/*! Destructor
	*/
	virtual ~CSLCOLLADAInstance() {};

	/*! Synchronizes this instance with its IO layer representation
	* \return SI_Error
	* \retval SI_SUCCESS this function always returns SI_SUCCESS
	*/
    virtual SI_Error Synchronize();

private:

	void *m_pReserved;	// reserved for future extension
};

#endif //_COLLADAINSTANCE_H