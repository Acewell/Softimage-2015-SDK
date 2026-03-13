//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file Envelope.h
	\brief Defines the CSLEnvelope class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _ENVELOPE_H
#define _ENVELOPE_H

#include "Template.h"



//! Describes the weight of a vertex.
struct SLVertexWeight
{
	SI_Float m_fVertexIndex;
	SI_Float m_fWeight;
};

#ifndef _SL_VERTEX_WEIGHT_ARRAY_PROXY_EXPORT_
#define _SL_VERTEX_WEIGHT_ARRAY_PROXY_EXPORT_

//XSITEMPLATEEXP template class XSIEXPORT CSLArrayProxy<SLVertexWeight, SI_Float, 2>;

#endif // _SL_VERTEX_WEIGHT_ARRAY_PROXY_EXPORT_



/*! \brief This class represents an \xx ftk_SI_Envelope SI_Envelope \endxx template.

	Describes an envelope (see the \xx ftk_SI_Envelope SI_Envelope \endxx
	template reference).
*/
class XSIEXPORT CSLEnvelope
	: public CSLTemplate
{
public:
	/*! Proxy class that allows modifying a list of SLVertexWeight like an array.
	*/
	typedef CSLArrayProxy<SLVertexWeight, SI_Float, 2> CSLVertexWeightArray;

	/*! Constructor
		\param[in] in_pScene	Pointer to the scene containing the envelope
		\param[in] in_pModel	Pointer to the model containing the envelope
		\param[in] in_pTemplate	Pointer to the CdotXSITemplate containing the envelope
		\return an instance of CSLEnvelope
	*/
	CSLEnvelope(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	/*! Destructor
	*/
	virtual ~CSLEnvelope();

	/*!	Returns the model that deforms this envelope.
		\return Pointer to the deformer model.
	*/
	CSLModel* GetDeformer();

	/*!	Changes the model deforming the envelope.
		\param[in]	in_pNewDeformer	New deforming model object.
	*/
	SI_Void SetDeformer(CSLModel* in_pNewDeformer);

	/*!	Returns the model that represent this envelope.
		\return Pointer to the enveloped model.
	*/
	CSLModel* GetEnvelope();

	/*!	Changes the model represented by the envelope.
		\param[in]	in_pNewEnvelope	New envelope model object.
	*/
	SI_Void SetEnvelope(CSLModel* in_pNewEnvelope);

	/*! Returns the number of vertex weights.
		\return Number of vertex weights.
	*/
	SI_Int GetVertexWeightCount();

	/*! Returns the vertex weights in an array proxy.
		\return Pointer to an array proxy of vertex weights.
	*/
	CSLVertexWeightArray* GetVertexWeightList();

	/*!	Returns an array of SLVertexWeight containing the vertex weights.
		\return Array of vertex weights.
	*/
	SLVertexWeight* GetVertexWeightListPtr();

	/*! Synchronizes this envelope instance with its IO layer representation
		\retval SI_Error::SI_SUCCESS this function always returns SI_SUCCESS
	*/
    virtual SI_Error Synchronize();

	/*! Returns the template type of the envelope
		\return CSLTemplate::SI_ENVELOPE the template type
	*/
	virtual ETemplateType Type() { return SI_ENVELOPE; }

private:
	CSLModel* m_pEnvelope;
	CSLModel* m_pDeformer;
	CSLVertexWeightArray m_VertexWeights;

	void *m_pReserved;	// reserved for future extension
};

#endif

