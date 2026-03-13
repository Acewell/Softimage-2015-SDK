//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file EnvelopeList.h
	\brief Defines the CSLEnvelopeList class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _ENVELOPELIST_H
#define _ENVELOPELIST_H

#include "Template.h"

// Forward declaration
class CSLEnvelope;

/*! \brief This class represents an \xx ftk_SI_EnvelopeList SI_EnvelopeList \endxx template.

	Describes the envelope list (see the \xx ftk_SI_EnvelopeList SI_EnvelopeList \endxx
	template reference).
*/
class XSIEXPORT CSLEnvelopeList
	: public CSLTemplate
{
public:
	/*! Constructor
		\param[in] in_pScene	Pointer to the scene containing the envelope
		\param[in] in_pModel	Pointer to the model containing the envelope
		\param[in] in_pTemplate	Pointer to the CdotXSITemplate containing the envelope
		\return an instance of CSLEnvelope
	*/
	CSLEnvelopeList(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	/*! Destructor
	*/
	virtual ~CSLEnvelopeList();

	/*!	Adds a new envelope to the list.
		\return Pointer to the newly created envelope object.
	*/
	virtual CSLEnvelope* AddEnvelope();

	/*!	Returns the number of envelopes in the list.
		\return Number of envelopes.
	*/
	SI_Int GetEnvelopeCount();

	/*!	Returns an array of all envelopes in the list.
		\return Array of pointers to envelope objects.
	*/
	CSLEnvelope** Envelopes();

	/*!	Removes a single envelope from the list.
		\param[in]	in_nIndex	Index of the envelope to remove.
		\return Error code.
	*/
	SI_Error RemoveEnvelope(SI_Int in_nIndex);

	/*!	Removes a single envelope from the list.
		\param[in]	in_pEnvelope	Pointer to the envelope to remove.
		\return Error code.
	*/
	SI_Error RemoveEnvelope(CSLEnvelope* in_pEnvelope);

	/*!	Removes all envelopes from the list.
		\return Error code.
	*/
	SI_Error ClearEnvelopes();

	// Connection functions
	/*! Connects a new envelope
		\param[in] in_pNewEnvelope the envelope to connect
		\return the connected envelope
	*/
	CSLEnvelope* ConnectEnvelope(CSLEnvelope* in_pNewEnvelope);

	/*! Synchronizes this envelope list instance with its IO layer representation
		\retval SI_Error::SI_SUCCESS this function always returns SI_SUCCESS
	*/
    virtual SI_Error Synchronize();

	/*! Returns the template type of the envelope list
		\return CSLTemplate::SI_ENVELOPE_LIST the template type
	*/
	virtual ETemplateType Type() { return SI_ENVELOPE_LIST; }

private:
	CSIBCArray<CSLEnvelope *> m_Envelopes;

	void *m_pReserved;	// reserved for future extension
};

#endif
