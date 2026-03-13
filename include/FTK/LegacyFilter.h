//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file LegacyFilter.h
	\brief Defines the CLegacyFilter class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _LEGACYFILTER_H_
#define _LEGACYFILTER_H_

#include <SIBCUtil.h>
#include <SIBCString.h>

#include "CXSIFilter.h"

#define BUFFER_FILTER_NAME	"Buffer"
#define BUFFER_FILTER_ID		"buf"

#define	BUFFER_SIZE				(128 * 1024)

/*! \brief Legacy filter where we read the entire scene in (used only for binary 3.0)

	\note This class is used only for legacy reading.
*/
class CLegacyFilter : public CXSIFilter
{
public:
	/*! Constructor
	*/
	CLegacyFilter();
	/*! Destructor
	*/
	virtual ~CLegacyFilter();

	/*! Opens the file for either reading or writing
	\param in_szFilename	file to open
	\param in_Mode	whether to read or write
	\return Whether the file was successfully opened or not
	*/
	int	Open ( CSIBCString in_szFilename,  _SI_FILE_MODE in_Mode );
	/*! Closes the file when finished
	\return Whether the file was successfully closed or not
	*/
	int	Close ();

	/*! Reads a number of bytes into the buffer passed in.
	\retval out_pBuffer	output buffer
	\param in_lSize	number of bytes to read
	\return	number of bytes read.
	*/
	int Read ( SI_Char * out_pBuffer, SI_Long in_lSize );
	/*! Writes a number of bytes to the file
	\param in_pBuffer	input buffer
	\param in_lSize	number of bytes to write
	\return number of bytes written
	*/
	int Write( SI_Char * in_pBuffer,  SI_Long in_lSize );


	/*! Tests whether we have reached the end of file
	\return \c 1 if we are at the end of the file
	\return \c 0 otherwise
	*/
	int Eof();
	/*! Returns the current position in the file.
	\returns position in the file (0 - beginning)
	*/
	int Tell();
private:
	void	Flush();

	CSIAccumString		m_szAccumBuffer;

};

#endif
