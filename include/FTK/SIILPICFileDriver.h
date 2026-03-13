//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file SIILPICFileDriver.h
	\brief Defines the CSIILPICFileDriver class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

//***************************************************************************************
// Defines
//***************************************************************************************
#ifndef __CSIILPICFileDriver_H__
#define __CSIILPICFileDriver_H__

//***************************************************************************************
// Includes
//***************************************************************************************
#include <SIBCPixMap.h>

//***************************************************************************************
// Typedefs
//***************************************************************************************

/*! \brief Softimage PIC file loader class
*/
class XSIEXPORT CSIILPICFileDriver : public CSIBCPixMapDriver
{
public:


	/*! Constructor
	*/
	CSIILPICFileDriver();

	/*! Destructor
	*/
	virtual ~CSIILPICFileDriver();

	/*! Returns whether the extension in the specified filename is supported by this driver
	\param in_Filename file name to check
	\return TRUE if this file is supported
	\return FALSE otherwise
	*/
	virtual SI_Bool Supported( CSIBCString &in_Filename );

	/*! Loads a Softimage Picture File Format file into a CSIBCPixMap object
	\param in_filename PIC file name
	\param in_PixMap CSIBCPixMap object to load the file into
	\return SI_Error::SI_SUCCESS loading has been succesful
	\return SI_Error::SI_ERR_ERROR_MSG loading has failed
	\return SI_Error::SI_FILE_NOT_FOUND the file has not been found
	*/
	virtual SI_Error Load( CSIBCString &in_filename, CSIBCPixMap &in_PixMap );

	/*! Loads a PIC file from memory into a CSIBCPixMap object
	\param in_pMemoryBlock memory block
	\param in_lCount memory block size
	\param in_PixMap CSIBCPixMap object to load the file into
	\return SI_Error::SI_SUCCESS loading has been succesful
	\return SI_Error::SI_ERR_ERROR_MSG loading has failed
	\return SI_Error::SI_FILE_NOT_FOUND the file has not been found
	*/
	virtual SI_Error LoadFromMemory( void *in_pMemoryBlock, SI_Int in_lCount, CSIBCPixMap &in_PixMap );

	/*! Returns the global PIC loader instance
	\return instance of loader
	*/
	static CSIILPICFileDriver *Driver();
protected:
	SI_Error LoadFromMemoryBlockOrFile( CSIBCString &i_Name, SI_Void *i_pMemoryBlock, SI_Int nMemoryBlockSize, CSIBCPixMap &o_Map);		// Load the specified image into the preallocated CSIBCPixMap.

private:


};




#endif // CSIILPICFileDriver
