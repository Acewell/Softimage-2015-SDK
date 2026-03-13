//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSIImage.h
	\brief Defines the CSLImage class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _XSIIMAGE_H
#define _XSIIMAGE_H

#include "Template.h"

class CSLImageData;
class CSLImageFX;
class CSLImageFX2;
class CSLImageLibrary;
class CSLTimeControl;

/*! \brief This class represents an \xx ftk_XSI_Image XSI_Image \endxx template.

	Base class to describe an image for dotXSI 5.0+ (see the \xx ftk_XSI_Image XSI_Image \endxx
	template reference).
	\since dotXSI 3.6
*/
class XSIEXPORT CSLImage
    : public CSLTemplate
{
public:
	//! Defines the number of channels of an image
	enum EChannels
	{
		SI_RGB = 3,		//!< red, green and blue channels>
		SI_RGBA = 4		//!< red, green, blue and alpha channels>
	};

	//! Defines the supported color depths for images
	enum EColorDepth
	{
		SI_24BITS = 24,	//!< 24 bits>
		SI_32BITS = 32	//!< 32 bits>
	};

	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Refered template
	*/
	CSLImage(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	//! Destructor
	virtual ~CSLImage();

	/*! Commits Semantic Layer data
		\return Whether or not commit was a success
	*/
	SI_Error Synchronize();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_IMAGE Template type
	*/
	ETemplateType Type(){ return XSI_IMAGE; }

    virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);

	virtual CSLAnimatableType* ParameterFromType(EFCurveType in_Type, SI_Char *in_szParameterName);

	/*! Returns the filename of the image
		\return Filename
	*/
	SI_Char* GetSourceFile();

	/*! Sets the filename of the image
		\param[in] in_szFilename Filename
	*/
	SI_Void SetSourceFile( const SI_Char* in_szFilename );

	/*! Returns the horizontal resolution of the image
		\return Size
		\note A source file name and the internally stored CSLImageData class are mutually exclusive.  Setting the source file therefore deletes the image data on your behalf.
	*/
	SI_Int GetWidth();

	/*! Sets the horizontal resolution of the image
		\param[in] in_nSize Size
	*/
	SI_Void SetWidth( SI_Int in_nSize );

	/*! Returns the vertical resolution of the image
		\return Size
	*/
	SI_Int GetHeight();

	/*! Sets the vertical resolution of the image
		\param[in] in_nSize Size
	*/
	SI_Void SetHeight( SI_Int in_nSize );

	/*! Returns the number of channels for a pixel
		\return Number of channels
	*/
	EChannels GetChannels();

	/*! Sets the number of channels for a pixel
		\param[in] in_Channel Number of channels
	*/
	SI_Void SetChannels( EChannels in_Channel );

	/*! Returns the color depth of the image
		\return Color depth
	*/
	EColorDepth GetColorDepth();

	/*! Sets the color depth of the image
		\param[in] in_Depth Color depth
	*/
	SI_Void SetColorDepth( EColorDepth in_Depth );

	/*! Returns the minimum horizontal crop value
		\return Crop value
	*/
	SI_Float GetCropMinX();

	/*! Sets the minimum horizontal crop value
		\param[in] in_fCrop Crop value
	*/
	SI_Void SetCropMinX( SI_Float in_fCrop );

	/*! Returns the maximum horizontal crop value
		\return Crop value
	*/
	SI_Float GetCropMaxX();

	/*! Sets the maximum horizontal crop value
		\param[in] in_fCrop Crop value
	*/
	SI_Void SetCropMaxX( SI_Float in_fCrop );

	/*! Returns the minimum vertical crop value
		\return Crop value
	*/
	SI_Float GetCropMinY();

	/*! Sets the minimum vertical crop value
		\param[in] in_fCrop Crop value
	*/
	SI_Void SetCropMinY( SI_Float in_fCrop );

	/*! Returns the maximum vertical crop value
		\return Crop value
	*/
	SI_Float GetCropMaxY();

	/*! Sets the maximum vertical crop value
		\param[in] in_fCrop Crop value
	*/
	SI_Void SetCropMaxY( SI_Float in_fCrop );

	/*! Returns the frame rate
		\return Actual frame rate
		\note A frame rate of 0 refers to the scene frame rate
	*/
	SI_Float GetFrameRate();

	/*! Sets the frame rate
		\param[in] in_nRate Actual frame rate
		\note A frame rate of 0 refers to the scene frame rate
	*/
	SI_Void SetFrameRate( SI_Float in_nRate = 0.0 );

	/*! Returns the first frame
		\return Frame number
	*/
	SI_Int GetFirstFrame();

	/*! Sets the first frame
		\param[in] in_nFrame Frame number
	*/
	SI_Void SetFirstFrame( SI_Int in_nFrame );

	/*! Returns the last frame
		\return Frame number
	*/
	SI_Int GetLastFrame();

	/*! Sets the last frame
		\param[in] in_nFrame Frame number
	*/
	SI_Void SetLastFrame( SI_Int in_nFrame );

	///////////////////////////////////////////////////////////////////////////
	// Image data functionality ///////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	/*! Allocates and connect a new image data
		\return Newly allocated image data.  Null if there was already one.
	*/
	CSLImageData* CreateImageData();

	/*! Use a preallocated image data
		\param[in] in_pImageData Pointer to the image data to use
		\note A source file name and the internally stored CSLImageData class are mutually
			exclusive.  Setting an image data therefore clears the source file name.
		\return Pointer to the added data or null if there's already one
	*/

	/*! Destroys the Image Data
		\return Whether or not the image data could be destroyed
	*/
	SI_Error DestroyImageData();

	/*! Connects the image data
		\note A source file name and the internally stored CSLImageData class are mutually
			exclusive.  Setting an image data therefore clears the source file name.
		\param[in] in_pImageData New image data to use
	*/
	CSLImageData* ConnectImageData( CSLImageData* in_pImageData );

	/*! Returns the image data
		\note A source file name and the internally stored CSLImageData class are mutually
			exclusive.  Setting an image data therefore clears the source file name.
		\return Image data
	*/
	CSLImageData* ImageData();

	CSLTimeControl* TimeControl();
	CSLTimeControl* AddTimeControl();
	CSLTimeControl* ConnectTimeControl(CSLTimeControl* in_pNewTimeControl);

	///////////////////////////////////////////////////////////////////////////
	// Image FX Functionality /////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	/*! Creates a new Image FX
		\return The new ImageFX or null if there's already one
	*/
	CSLImageFX* CreateImageFX();

	/*! Destroys the Image FX
		\return Whether or not the ImageFX could be destroyed
	*/
	SI_Error DestroyImageFX();

	/*! Connects an exisiting Image FX
		\param[in] in_pToConnect Pointer to the ImageFX to use
		\return The added ImageFX or null if there's already one
	*/
	CSLImageFX* ConnectImageFX( CSLImageFX* in_pToConnect );

	/*! Returns a pointer to the Image FX
		\return Pointer to the Image FX
	*/
	CSLImageFX* ImageFX();

	CSLStringProxy* SourceFile() { return &m_SourceFile;};

	CSLIntProxy * SizeX() { return &m_SizeX;};
	CSLIntProxy * SizeY() { return &m_SizeY;};
	CSLIntProxy * Channels() { return &m_Channels;};
	CSLFloatProxy * CropMinX() { return &m_CropMinX;};
	CSLFloatProxy * CropMaxX() { return &m_CropMaxX;};
	CSLFloatProxy * CropMinY() { return &m_CropMinY;};
	CSLFloatProxy * CropMaxY() { return &m_CropMaxY;};
	CSLFloatProxy * FrameRate() { return &m_FrameRate;};
	CSLIntProxy * FrameCount() { return &m_FrameCount;};
	CSLIntProxy * FirstFrame() { return &m_FirstFrame;};
	CSLIntProxy * LastFrame() { return &m_LastFrame;};
	CSLIntProxy * BitsPerPixel() { return &m_BitsPerPixel;};

	///////////////////////////////////////////////////////////////////////////
	// Image FX 2 Functionality /////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	/*! Creates a new Image FX 2
		\return The new ImageFX2 or null if there's already one
	*/
	CSLImageFX2* CreateImageFX2();

	/*! Destroys the Image FX 2
		\return Whether or not the ImageFX2 could be destroyed
	*/
	SI_Error DestroyImageFX2();

	/*! Connects an exisiting Image FX 2
		\param[in] in_pToConnect Pointer to the ImageFX2 to use
		\return The added ImageFX2 or null if there's already one
	*/
	CSLImageFX2* ConnectImageFX2( CSLImageFX2* in_pToConnect );

	/*! Returns a pointer to the Image FX 2
		\return Pointer to the Image FX 2
	*/
	CSLImageFX2* ImageFX2();

private:
	CSLStringProxy m_SourceFile;
    CSLIntProxy m_SizeX;
    CSLIntProxy m_SizeY;
    CSLIntProxy m_Channels;
    CSLIntProxy m_BitsPerPixel;
    CSLFloatProxy m_CropMinX;
    CSLFloatProxy m_CropMaxX;
    CSLFloatProxy m_CropMinY;
    CSLFloatProxy m_CropMaxY;
    CSLFloatProxy m_FrameRate;
    CSLIntProxy m_FrameCount;
    CSLIntProxy m_FirstFrame;
    CSLIntProxy m_LastFrame;
	CSLImageData *m_pImageData;
	CSLImageFX *m_pImageFX;
	CSLImageFX2 *m_pImageFX2;
	CSLTimeControl* m_pTimeControl;

	SI_Void *m_pReserved;
};

#endif
