//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSIImageLibrary.h
	\brief Defines the CSLImageLibrary class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _XSIIMAGELIBRARY_H
#define _XSIIMAGELIBRARY_H

#include "Template.h"

class CSLImage;

/*! \brief This class represents an \xx ftk_XSI_ImageLibrary XSI_ImageLibrary \endxx template.

	Base class to define a collection of images for dotXSI 5.0+ (see the \xx ftk_XSI_ImageLibrary XSI_ImageLibrary \endxx
	template reference).
	\since dotXSI 3.6
*/
class XSIEXPORT CSLImageLibrary
    : public CSLTemplate
{
public:
	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Refered template
	*/
	CSLImageLibrary(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	//! Destructor
	virtual ~CSLImageLibrary();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_IMAGE_LIBRARY The type of this template
	*/
	ETemplateType Type(){ return XSI_IMAGE_LIBRARY; }

	/*! Commits semantic layer data
		\return Whether or not commit was a success
	*/
	SI_Error Synchronize();

    virtual CSLAnimatableType*		ParameterFromName(SI_Char *in_szName);

	///////////////////////////////////////////////////////////////////////////
	// Image Functionality /////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	/*! Adds an Image to the Image list
		\return Pointer to the newly added Image
	*/
	CSLImage* AddImage();

	/*! Removes an Image from the Image list
		\param[in] in_nIndex Index of the Image to remove
		\return Whether or not the Image could be removed
	*/
	SI_Error RemoveImage( SI_Int in_nIndex );

	/*! Removes an Image from the Image list
		\param[in] in_pToRemove Pointer to the Image to remove
		\return Whether or not the Image could be removed
	*/
	SI_Error RemoveImage( CSLImage* in_pToRemove );

	/*! Removes all connections points from the Image list
		\return Whether or not the list could be cleared
	*/
	SI_Error ClearImages();

	/*! Adds an exisiting Image to the Image list
		\param[in] in_pToConnect Pointer to the Image to add
		\return The added Image or null if it already exists in the list
	*/
	CSLImage* ConnectImage( CSLImage* in_pToConnect );

	/*! Returns a pointer to the internally-stored Image pointer list
		\return Pointer to the list
	*/
	CSLImage** GetImageList();

	/*! Returns the total number of Images
		\return Number of Images
	*/
	SI_Int GetImageCount();

	/*! Searches for a given Image
		\param[in] in_szImageName Name of the Image to look for
		\return Pointer to the Image or null if it cannot be found
	*/
	CSLImage* FindImage( const SI_Char* in_szImageName );

private:
    CSIBCArray<CSLImage*> m_Images;

	SI_Void *m_pReserved;
};

#endif
