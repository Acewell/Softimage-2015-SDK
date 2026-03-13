//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file COLLADAEnvelopeList.h
	\brief Defines the CSLCOLLADAEnvelopeList class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _COLLADAENVELOPELIST_H
#define _COLLADAENVELOPELIST_H

#include "EnvelopeList.h"
#include "COLLADAEnvelope.h"

typedef CSIBCArray<CSLCOLLADAEnvelope*>	EnvelopeGroup;

/*! \brief Describes the envelope list.
*/
class XSIEXPORT CSLCOLLADAEnvelopeList
	: public CSLEnvelopeList
{
public:
	/*! Constructor
	* \param in_pScene	Pointer to the scene containing the envelope
	* \param in_pModel	Pointer to the model containing the envelope
	* \param in_pTemplate	Pointer to the CdotXSITemplate containing the envelope
	* \return an instance of CSLEnvelope
	*/
	CSLCOLLADAEnvelopeList(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	/*! Destructor
	*/
	virtual ~CSLCOLLADAEnvelopeList();

	/*!	Add a new envelope to the list.
	* \return	CSLEnvelope*	Pointer to the newly created envelope object.
	*/
	CSLEnvelope* AddEnvelope();

	/*! Synchronizes this envelope list instance with its IO layer representation
	* \return SI_Error
	* \retval SI_SUCCESS this function always returns SI_SUCCESS
	*/
    virtual SI_Error Synchronize();

private:

	SI_Void	ExportGroup ( EnvelopeGroup* in_pGroup );

	CSIBCArray<EnvelopeGroup> m_Groups;
};

#endif
