//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file BINFilter.h
	\brief Defines the CBINFilter class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _BINFILTER_H_
#define _BINFILTER_H_

#include <SIBCUtil.h>
#include <SIBCString.h>

#include "CXSIFilter.h"

#define BIN_FILTER_NAME	"Binary"
#define BIN_FILTER_ID		"bin"
#define GROW_BUFFER_MULTIPLIER		0.1f
#define GROW_BUFFER_BYTE_AMOUNT		14

/*! \brief This class supports both the legacy and the new binary format.

	This supports 3.0 compression (entire file at once) and 3.5 and up where we compress
	one chunk at a time therefore reducing the overall memory usage
*/
class CBINFilter : public CXSIFilter
{
public:
	/*! Constructor
	\param in_bLegacy (in legacy mode (3.0), we have to read the ENTIRE file in before we can decompress)...
	*/
	CBINFilter( bool in_bLegacy );
	/*! Destructor
	*/
	virtual ~CBINFilter();

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
	void ReadBlock();

	void AdjustBuffer( SI_Long in_lSize );

	SI_UByte	* m_pBytes;
	SI_UByte	* m_pCompressedBuffer;
	SI_Long		m_lCompressedBufferSize;
	SI_Long		m_lPosition, m_lSize;
	bool		m_bLegacy;
	bool		m_bEof;
};

#endif
