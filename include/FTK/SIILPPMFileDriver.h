//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file SIILPPMFileDriver.h
	\brief Defines the CSIILPPMFileDriver class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

//***************************************************************************************
// Defines
//***************************************************************************************
#ifndef __CSIILPPMFileDriver_H__
#define __CSIILPPMFileDriver_H__

//***************************************************************************************
// Includes
//***************************************************************************************
#include <SIBCPixMap.h>

//***************************************************************************************
// Typedefs
//***************************************************************************************

/*! \brief PPM file loader class
*/
class XSIEXPORT CSIILPPMFileDriver : public CSIBCPixMapDriver
{
public:
	/*! Constructor
	*/
	CSIILPPMFileDriver();

	/*! Destructor
	*/
	virtual ~CSIILPPMFileDriver();

	/*! Returns whether the extension in the specified filename is supported by this driver
	\param in_Filename file name to check
	\return TRUE if this file is supported
	\return FALSE otherwise
	*/
	virtual SI_Bool Supported( CSIBCString &in_Filename );

	/*! Loads a Portable Pixmap file into a CSIBCPixMap object
	\param in_filename PPM file name
	\param in_PixMap CSIBCPixMap object to load the file into
	\return SI_Error::SI_SUCCESS loading has been succesful
	\return SI_Error::SI_ERR_ERROR_MSG loading has failed
	\return SI_Error::SI_FILE_NOT_FOUND the file has not been found
	*/
	virtual SI_Error Load( CSIBCString &in_filename, CSIBCPixMap &in_PixMap );

	/*! Returns the global PPM loader instance
	\return instance of loader
	*/
	static CSIILPPMFileDriver *Driver();

protected:
	SI_Bool raw;

    static SI_Int readChar( _SI_FILE fp );
    static SI_Int readInt( _SI_FILE fp );

private:


};


#endif // CSIILPPMFileDriver
