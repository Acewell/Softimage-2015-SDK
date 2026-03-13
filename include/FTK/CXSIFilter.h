//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file CXSIFilter.h
	\brief Defines the CXSIFilter.h class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _CXSIFILTER_H_
#define _CXSIFILTER_H_

#include <SIBCUtil.h>
#include <SIBCString.h>

#define	SI_MEMORY_FILE_NAME		"3DMEMORYBUFFER"

/*! \brief Base class for filters.

	This base class defines the basis for all filters in the system. A filter will
	be used both for reading and writing to/from a file. Filters can be chained so we
	can create constructs like, BUFFERING | ASCII  or COMPRESS for example.
*/
class CXSIFilter
{
public:

	/*! Constructor
	*/
	CXSIFilter();
	/*! Destructor
	*/
	virtual ~CXSIFilter();


	/*! Sets the name of the file to be used, needed because the Crosswalk SDK receives the
	name, but it is the last filter that will open the file, so it has to be passed down from
	filter  to filter.
	\param in_szName		Name of the filter.
	*/
	void			SetName ( const CSIBCString & in_szName );

	/*! Returns the name of the file used
	\return name of the file.
	*/
	CSIBCString		GetName () ;

	/*! Sets the ID for the filter. This ID will appear inside the dotXSI header
	\param in_szID string ID. Valid values include:
		\li \c "txt"
		\li \c "bin"
	*/
	void			SetID ( const CSIBCString & in_szID );
	/*! Returns the current ID
	\return current ID
	*/
	CSIBCString&	GetID () ;

	/*! Sets the \xx ftk_FileHeader file header \endxx to be used (for example, \c "xsi 0360txt")
	\param in_szHeader string to use for the file header
	*/
	virtual void			SetHeader ( CSIBCString in_szHeader );

	/*! Returns the current \xx ftk_FileHeader file header \endxx
	\return current header
	*/
	CSIBCString		GetHeader () ;
	/*! Writes out the \xx ftk_FileHeader file header \endxx, called when we are about to write the
	file, to make sure the header is the first thing written in the file.
	*/
	virtual void	WriteHeader();

	/*! Opens the file for either reading or writing
	\param in_szFilename	filename
	\param in_Mode		mode
	*/
	virtual int	Open ( CSIBCString in_szFilename, _SI_FILE_MODE in_Mode );
	/*! Closes the file when finished
	*/
	virtual int	Close ();


	/*! Reads the specified number of bytes into the buffer passed in.
	\retval out_pBuffer	output buffer
	\param in_lSize	number of bytes to read
	\return	number of bytes read
	*/
	virtual int Read ( SI_Char * out_pBuffer, SI_Long in_lSize );
	/*! Writes the specified number of bytes to the file
	\param in_pBuffer	input buffer
	\param in_lSize	number of bytes to write
	\return number of bytes written
	*/
	virtual int Write( SI_Char * in_pBuffer,  SI_Long in_lSize );

	/*! Tests to see if we have reached the end of file
	\return \c 1 if we are at the end of the file
	\return \c 0 otherwise
	*/
	virtual int Eof();

	/*! Returns the current position in the file.
	\returns position in the file (0 - beginning)
	*/
	virtual int Tell();

	/*! Sets the sub filter, used during construction.
	\param in_pSub	sub filter to use.
	*/
	void		SetSubFilter ( CXSIFilter *in_pSub ) { m_pSubFilter = in_pSub;} ;
	/*! Returns the current subfilter
	\return current subfilter
	*/
	CXSIFilter *GetSubFilter () { return m_pSubFilter ; };

	int FillBuffer ( CSIBCString in_szFilename );
protected:

	_SI_FILE	m_pStream;
	CSIBCString	m_szHeader;
	CSIBCString	m_szName;
	CSIBCString	m_szID;
	CXSIFilter	*m_pSubFilter;
	SI_Long		m_FileSize;
	SI_Char		*m_pBuffer;
	SI_Long		m_lSubFilterPos;
	SI_Bool		m_bEof;

};

#endif
