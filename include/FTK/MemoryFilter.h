//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file MemoryFilter.h
	\brief Defines the CMemoryFilter class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _MEMORYFILTER_H_
#define _MEMORYFILTER_H_

#include <SIBCUtil.h>
#include <SIBCString.h>
#include "SIBCArray.h"

#include "CXSIFilter.h"

#define MEMORY_FILTER_NAME		"MEMORY"
#define MEMORY_FILTER_ID		"mem"

#define	BUFFER_SIZE				(128 * 1024)

/*! \brief Memory filter.

	This class will gather up to a certain size of data until it calls its subfilter to
	write or it will read up to a certain size in one go and answer to request until it
	has exhausted the data at which point it will ask its subfilter for more data.
*/
class CMemoryFilter : public CXSIFilter
{
public:
	/*! Constructor
	*/
	CMemoryFilter();
	/*! Destructor
	*/
	virtual ~CMemoryFilter();

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

	void WriteHeader();
	void			SetHeader ( CSIBCString in_szHeader );
	CSIBCString		GetHeader () { return GetLastHeader(); }
static				CSIBCString GetLastHeader();
private:
	void	Flush();
	void	FillBuffer();

	char	*m_pBuffer;
	int	m_lPosition;
	SI_Long	m_lSizeRead;
	bool	m_bHeaderSkipped;
	bool	m_bReadMode;
static		SI_Char					m_cHeader[17];
static		CSIBCArray<SI_Char*>	m_blocks;
static		CSIBCArray<SI_Int>		m_blockSize;
	SI_Long	m_lBufIndex;
};

#endif
