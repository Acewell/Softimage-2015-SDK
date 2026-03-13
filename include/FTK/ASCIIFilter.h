//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file ASCIIFilter.h
	\brief Defines the CASCIIFilter class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _ASCIIFILTER_H_
#define _ASCIIFILTER_H_

#include <SIBCUtil.h>
#include <SIBCString.h>

#include "CXSIFilter.h"

#define ASCII_FILTER_NAME	"Text"
#define ASCII_FILTER_ID		"txt"

/*! \brief This is the ascii class, it just takes the data as is and passes it down the subfilter.

	This class allows the buffering to happen by channeling all the output through here which
	then goes to the subfilter.
 */
class CASCIIFilter : public CXSIFilter
{
public:
	/*! Constructor
	*/
	CASCIIFilter();
	/*! Destructor
	*/
	virtual ~CASCIIFilter();

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
#ifdef	_PSX2
	bool	m_bEof;
#endif

};

#endif
