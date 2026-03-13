//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSIImageData.h
	\brief Defines the CSLImageData class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _XSIIMAGEDATA_H
#define _XSIIMAGEDATA_H

#include "Template.h"
#include "XSIImage.h"

#ifndef _SL_INT_ARRAY_PROXY_EXPORT_
#define _SL_INT_ARRAY_PROXY_EXPORT_

#endif

/*! \brief This class represents an \xx ftk_XSI_ImageData XSI_ImageData \endxx template.

	Base class to define the raw pixel information of an image for dotXSI 5.0+ (see the \xx ftk_XSI_ImageData XSI_ImageData \endxx
	template reference).
	\since dotXSI 3.6
*/
class XSIEXPORT CSLImageData
    : public CSLTemplate
{
public:

	/*! Proxy class that allows modifying a list of SI_Int like an array.
	*/
	typedef CSLArrayProxy<SI_Int, SI_Int, 1> CSLIntArray;

	//! Defines the various compression types
	enum ECompressionType
	{
		SI_UNCOMPRESSED = 0,	/*!< No compression */
	};

	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Refered template
	*/
	CSLImageData(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	//! Destructor
	virtual ~CSLImageData();

	/*! Commits Semantic Layer data
		\return Whether or not commit was a success
	*/
	SI_Error Synchronize();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_IMAGE_DATA The type of this template
	*/
	ETemplateType Type(){ return XSI_IMAGE_DATA; }

	/*! Sets the raw color information of the image
		\param[in] in_Data Array containing the raw color information
	*/
	SI_Void SetImageData( CSIBCArray<SI_Int> &in_Data );

	/*! Returns the size of the image data color information
		\return size of the image data color information
	*/
	SI_Int GetImageDataCount();

	/*! Returns the color information array
		\return Array of color information
	*/
	CSLIntArray* GetImageDataList();

	/*! Returns a pointer to the raw color information of the image
		\return Pointer to the array containing the color information
	*/
	SI_Int* GetImageDataListPtr();

	/*! Returns the compression type of the image
		\return The type of compression
	*/
	ECompressionType GetCompressionType();

	/*! Sets the compression type of the image
		\param[in] in_Type The type of compression
	*/
	SI_Void SetCompressionType( ECompressionType in_Type );

private:
    CSLEnumProxy<ECompressionType, SI_UNCOMPRESSED> m_CompressionType;
    CSLIntArray m_ImageData;

	SI_Void *m_pReserved;
};

#endif
