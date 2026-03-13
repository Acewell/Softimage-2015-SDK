//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file SIILTGAFileDriver.h
	\brief Defines the CSIILTGAFileDriver class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

//***************************************************************************************
// Defines
//***************************************************************************************
#ifndef __CSIILTGAFileDriver_H__
#define __CSIILTGAFileDriver_H__

//***************************************************************************************
// Includes
//***************************************************************************************
#include <SIBCPixMap.h>

//***************************************************************************************
// Typedefs
//***************************************************************************************

/*! \brief TGA file loader class
*/
class XSIEXPORT CSIILTGAFileDriver : public CSIBCPixMapDriver
{
public:
	/*! Constructor
	*/
	CSIILTGAFileDriver();

	/*! Destructor
	*/
	virtual ~CSIILTGAFileDriver();

	/*! Returns whether the extension in the specified filename is supported by this driver
	\param in_Filename file name to check
	\return TRUE if this file is supported
	\return FALSE otherwise
	*/
	virtual SI_Bool Supported( CSIBCString &in_Filename );

	/*! Loads a TARGA File Format file into a CSIBCPixMap object
	\param in_filename TGA file name
	\param in_PixMap CSIBCPixMap object to load the file into
	\return SI_Error::SI_SUCCESS loading has been succesful
	\return SI_Error::SI_ERR_ERROR_MSG loading has failed
	\return SI_Error::SI_FILE_NOT_FOUND the file has not been found
	*/
	virtual SI_Error Load( CSIBCString &in_filename, CSIBCPixMap &in_PixMap );

	/*! Returns the global TGA loader instance
	\return instance of loader
	*/
	static CSIILTGAFileDriver *Driver();
protected:


private:


};


#endif // CSIILTGAFileDriver
