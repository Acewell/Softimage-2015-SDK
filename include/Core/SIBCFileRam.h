//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file SIBCFileRam.h
	\brief Defines the CSIBCFileRam class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

//***************************************************************************************
// Defines
//***************************************************************************************
#ifndef __CSIBCFileRam_H__
#define __CSIBCFileRam_H__

//***************************************************************************************
// Includes
//***************************************************************************************
#include <SIBCUtil.h>

//***************************************************************************************
// Typedefs
//***************************************************************************************


class CSIBCFileRam;


/*! \brief This class implements a memory file object
*/
class CSIBCFileRam
{
	public
		:
		/*! Constructor
			\return An instance of CSIBCFileRam
		*/
		CSIBCFileRam()
		{
			Init();
		}

		/*! Constructor with user specified parameters
			\param[in] pFileName pointer to a character array storing the file name
			\param[in] pAccessRights file access modes:
			\li \c __SI_FILE_READ_TEXT	: opens a text file in read mode
			\li \c __SI_FILE_READ_BINARY : opens a binary file in read mode
			\li \c __SI_FILE_WRITE_TEXT	: unsupported mode
			\li \c __SI_FILE_WRITE_BINARY : unsupported mode
			\param[in] pMemoryBlock pointer to the read/write memory block to use
			\param[in] nMemorySize size of the memory block
		*/
		CSIBCFileRam(SI_Char *pFileName, _SI_FILE_MODE pAccessRights, void *pMemoryBlock, SI_Int nMemorySize)
		{
			Init();

			Open(pFileName, pAccessRights, pMemoryBlock, nMemorySize);
		}

		/*! Destructor
		*/
		~CSIBCFileRam()
		{
			Close();
		}

		/*! Sets a CSIBCFileRam instance default values
		*/
		SI_Void Init()
		{
			m_pFile = _SI_FILE_NULL;

			m_pMemRoot = NULL;
			m_pMemPos = NULL;
			m_nMemSize = 0;
		}

		/*! Checks if the memory file object is valid
			\retval SI_Bool::TRUE memory file object is valid
			\retval SI_Bool::FALSE memory file object is invalid
		*/
		SI_Bool IsValid()
		{
#if !defined( _PSX2 ) && !defined ( _WIN32_WCE )
			return (m_pMemRoot != (void*)m_pFile);
#else
			return (m_pMemRoot != NULL);
#endif
		}


		/*! Opens a memory file
			\param[in] pFileName Pointer to a character array storing the name of the file.
			\param[in] pAccessRights Pointer to access rights.
			\param[in] pMemoryBlock Pointer to a memory block.
			\param[in] nMemorySize the memory block size.
		*/
		SI_Void Open(SI_Char *pFileName, _SI_FILE_MODE pAccessRights, SI_Void *pMemoryBlock, SI_Int nMemorySize)
		{
			if (pMemoryBlock != NULL)
			{
				m_pMemRoot = (SI_UByte*)pMemoryBlock;
				m_pMemPos = m_pMemRoot;
				m_nMemSize = nMemorySize;
			}
			else
			if (pFileName)
			{
				m_pMemRoot = NULL;
				m_pMemPos = NULL;
				m_nMemSize = 0;

				m_pFile = _SI_FOPEN(pFileName, pAccessRights);
			}
		}

		/*! Close the memory file
		*/
		SI_Void Close()
		{
			if (m_pFile)
			{
				_SI_FCLOSE(m_pFile);
				m_pFile = _SI_FILE_NULL;
			}

			m_pMemRoot = NULL;
			m_pMemPos  = NULL;
			m_nMemSize = 0;
		}

		/*! Read from the open memory file
			\param[in] pDest Pointer to the read buffer
			\param[in] nDestSize size in bytes of the buffer element
			\param[in] nCount counts how many items have been read
			\return The percentage of the file read
		*/
		SI_Int Read(void *pDest, SI_Int nDestSize, SI_Int nCount)
		{
			if (m_pFile != NULL)
			{
				return (SI_Int)_SI_FREAD(pDest, nDestSize, nCount, m_pFile);
			}
			else // Use memory block instead of file pointer.
			{
				SI_Int size = nDestSize * nCount;
				// Since our memory file can't be bigger than 4Gigs (m_nMemSize is a 32 bits)
				// we can cast to a 32 bits without worrying...
				SI_Int ofs = (SI_Int)(m_pMemPos - m_pMemRoot);

				// Make sure we don't read out of bounds.
				if ( (ofs + size) > m_nMemSize)
				{
					size = m_nMemSize - ofs;
				}

				memmove(pDest, m_pMemPos, size );

				m_pMemPos += size;

				assert( (size % nDestSize) == 0);

				return (size / nDestSize);
			}

			return 0;
		}
		// @todo add write function
		SI_Int Write(void *pSrc, SI_Int nSrcSize, SI_Int nCount)
		{
			// Not implemented yet - not needed.
			return 0;
		}
		// @todo add a seek function
		// Seeks somewhere in the stream
		SI_Int Seek()
		{
			return 0;
		}

		// @todo add a tell function
		// Returns the size of the stream
		SI_Int Tell()
		{
			return 0;
		}

	private:
		SI_UByte *m_pMemRoot;
		SI_UByte *m_pMemPos;
		SI_Int    m_nMemSize;

		_SI_FILE  m_pFile;
};


#endif
// CSIBCFileRam
