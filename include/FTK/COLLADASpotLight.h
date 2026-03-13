//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file COLLADASpotLight.h
	\brief Defines the CSLCOLLADASpotLight class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _COLLADASPOTLIGHT_H
#define _COLLADASPOTLIGHT_H

#include "SpotLight.h"

/*! \brief Describes a spot light and its interest.
*/
class XSIEXPORT CSLCOLLADASpotLight
    : public CSLSpotLight
{
public:

	/*! Constructor
	* \param in_pScene scene to add this spotlight to
	* \param in_pModel model to add this light to
	* \param in_pTemplate IO layer template to connect to
	* \return an instance of CSLCOLLADASpotLight
	*/
	CSLCOLLADASpotLight(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	/*! Destructor
	*/
    virtual ~CSLCOLLADASpotLight();

	/*! Synchronizes this light instance with its IO layer representation
	* \return SI_Error
	* \retval SI_SUCCESS this function always returns SI_SUCCESS
	*/
    virtual SI_Error Synchronize();

private:
	void *m_pReserved;	// reserved for future extension
};

#endif
