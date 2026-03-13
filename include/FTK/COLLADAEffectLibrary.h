//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file COLLADAEffectLibrary.h
	\brief Defines the CSLCOLLADAEffectLibrary class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef COLLADAEFFECTLIBRARY_H
#define COLLADAEFFECTLIBRARY_H

#include "COLLADATemplate.h"
#include "COLLADAEffect.h"

/*! \brief COLLADA Effect Library class definition
*/
class XSIEXPORT CSLCOLLADAEffectLibrary : public CSLTemplate
{
public:
	CSLCOLLADAEffectLibrary(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
	virtual ~CSLCOLLADAEffectLibrary();

	/*!	Adds a new Effect to the Effect library.
		\return	Pointer to the newly created Effect object.
	*/
	CSLCOLLADAFX* AddEffect();

	/*!	Removes all Effects from the Effect library.
		\return	Error code.
	*/
	SI_Error ClearEffects();

	/*!	Returns an array of all Effects in the library.
		\return	Array of pointers to Effect objects.
	*/
	CSLCOLLADAFX** GetEffectList();

	/*!	Returns the number of Effects in the library.
		\return	Number of Effects.
	*/
	SI_Int GetEffectCount();

	/*!	Removes a single Effect from the library.
		\param[in]	in_nIndex	Index of the Effect to remove.
		\return	Error code.
	*/
	SI_Error RemoveEffect(SI_Int in_nIndex);

	/*!	Removes a single Effect from the library.
		\param[in]	in_pEffect	Pointer to the Effect to remove.
		\return	Error code.
	*/
	SI_Error RemoveEffect(CSLCOLLADAFX *in_pEffect);

	CSLCOLLADAFX* FindEffect( const SI_Char* in_szName );

	CSLCOLLADAFX* ConnectEffect(CSLCOLLADAFX* in_pNewEffect);

    virtual SI_Error Synchronize();

	/*!	Returns the type of this template
		\retval	CSLTemplate::COLLADA_EFFECT_LIBRARY Template type
	*/
	virtual ETemplateType Type();

private:
	CSIBCArray<CSLCOLLADAFX *>	m_Effects;

	void*							m_pReserved;
};


#endif // COLLADAEFFECTLIBRARY_H

