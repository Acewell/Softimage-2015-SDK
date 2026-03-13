//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file COLLADAEnvelope.h
	\brief Defines the CSLCOLLADAEnvelope class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _COLLADAENVELOPE_H
#define _COLLADAENVELOPE_H

#include "Envelope.h"




/*! \brief Describes an envelope for COLLADA.
*/
class XSIEXPORT CSLCOLLADAEnvelope
	: public CSLEnvelope
{
public:
	/*! Constructor
	* \param in_pScene	Pointer to the scene containing the envelope
	* \param in_pModel	Pointer to the model containing the envelope
	* \param in_pTemplate	Pointer to the CdotXSITemplate containing the envelope
	* \return an instance of CSLEnvelope
	*/
	CSLCOLLADAEnvelope(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	/*! Destructor
	*/
	virtual ~CSLCOLLADAEnvelope();

	/*! Synchronizes this envelope instance with its IO layer representation
	* \return SI_Error
	* \retval SI_SUCCESS this function always returns SI_SUCCESS
	*/
    virtual SI_Error Synchronize();

};

#endif

