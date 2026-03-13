//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file SIILJPGFileDriver.h
	\brief Defines the CSIILJPGFileDriver class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

//***************************************************************************************
// Defines
//***************************************************************************************
#ifndef __CSIILJPGFileDriver_H__
#define __CSIILJPGFileDriver_H__

//***************************************************************************************
// Includes
//***************************************************************************************
#include <SIBCPixMap.h>


//***************************************************************************************
// Typedefs
//***************************************************************************************

/*! \brief JPG file loader class
*/
class XSIEXPORT CSIILJPGFileDriver : public CSIBCPixMapDriver
{
public:
	/*! Constructor
	*/
	CSIILJPGFileDriver();

	/*! Destructor
	*/
	virtual ~CSIILJPGFileDriver();

	/*! Returns whether the extension in the specified filename is supported by this driver
	\param in_Filename file name to check
	\return TRUE if this file is supported
	\return FALSE otherwise
	*/
	virtual SI_Bool Supported( CSIBCString &in_Filename );

	/*! Loads a JPEG Interchange Format file into a CSIBCPixMap object
	\param in_filename JPG file name
	\param in_PixMap CSIBCPixMap object to load the file into
	\return SI_Error::SI_SUCCESS loading has been succesful
	\return SI_Error::SI_ERR_ERROR_MSG loading has failed
	\return SI_Error::SI_FILE_NOT_FOUND the file has not been found
	*/
	virtual SI_Error Load( CSIBCString &in_filename, CSIBCPixMap &in_PixMap );

	/*! Returns the global JPG loader instance
	\return instance of loader
	*/
	static CSIILJPGFileDriver *Driver();
private:

	SI_Error ReadPixels(_SI_FILE *filePtr, CSIBCPixMap &);

	// shielding from any lib dependencies
	void	*jpgInfo;
};




#endif // CSIILJPGFileDriver
