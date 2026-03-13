//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file SIBCPixMap.h
	\brief Defines the CSIBCPixMap and CSIBCPixMapDriver classes

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

//***************************************************************************************
// Defines
//***************************************************************************************
#ifndef __CSIBCPixMap_H__
#define __CSIBCPixMap_H__

//***************************************************************************************
// Includes
//***************************************************************************************
#include <SIBCUtil.h>
#include <SIBCNode.h>
#include <SIBCString.h>
#include <SIBCSearchPath.h>


class CSIBCPixMap;

/*! \brief Base class for pixel map loader drivers
*/
class XSICOREEXPORT CSIBCPixMapDriver
{
	private:
		SI_Void			*m_pUnused;

	public:

		/*! Constructor
		*/
		CSIBCPixMapDriver();

		/*! Destructor
		*/
		virtual ~CSIBCPixMapDriver();

		/*! Returns whether the extension passed in the string is supported by this driver
		\param in_Filename file name to check
		\return SI_Bool::TRUE if this file is supported
		\return SI_Bool::FALSE if this file is not supported
		*/
		virtual SI_Bool Supported( CSIBCString &in_Filename ) = 0;

		/*! Loads a bitmap file into a CSIBCPixMap object
		\param in_filename bitmap file name
		\param in_PixMap load file into this object
		\return SI_Error::SI_SUCCESS loading has been succesful
		\return SI_Error::SI_ERR_ERROR_MSG loading has failed
		\return SI_Error::SI_FILE_NOT_FOUND the file has not been found
		*/
		virtual SI_Error Load( CSIBCString &in_filename, CSIBCPixMap &in_PixMap ) = 0;

		/*! Loads a memory bitmap file into a CSIBCPixMap object
		\param in_pMemoryBlock memory block
		\param in_lCount memory block size
		\param in_PixMap CSIBCPixMap object to load the file into
		\return SI_Error::SI_SUCCESS loading has been succesful
		\return SI_Error::SI_ERR_ERROR_MSG loading has failed
		\return SI_Error::SI_FILE_NOT_FOUND the file has not been found
		*/
		virtual SI_Error LoadFromMemory( void *in_pMemoryBlock, SI_Int in_lCount, CSIBCPixMap &in_PixMap ) { return SI_FILE_NOT_FOUND; }
};


// Pixel map class
class XSICOREEXPORT CSIBCPixMap : public CSIBCNode
{
public:

	/*! Type of RGBA component
	*/
	enum
	{
		RED,		/*!< Red component.		*/
		GREEN,		/*!< Green component.	*/
		BLUE,		/*!< Blue component.	*/
		ALPHA		/*!< Alpha component. 	*/
	};

	/*! Type of pixmap.
	*/
	enum
	{
		//Types
		RGB,		/*!< RGB		*/
		RGBA,		/*!< RGBA		*/
		PALETIZED	/*!< Paletized	*/
	};

	/*! Texture ID
	*/
	enum
	{
		INVALID_TEXTURE_ID = 0xffffffff /*!< invalid texture ID */
	};

	/*! PixMap resizing method
	*/
	enum
	{
		RESIZE_LOWER,		/*!< Resize Lower		*/
		RESIZE_HIGHER,		/*!< Resize Higher		*/
		RESIZE_NEAREST		/*!< Resize Nearest		*/
	};

	/*! Constructor
	*/
	CSIBCPixMap();

	/*! Destructor
	*/
	virtual ~CSIBCPixMap();

	//Info Retrieval
	/*! Returns the size of the Color LookUp Table (\c CLUT)
	\return the size of the color lookup table
	*/
	SI_Int GetCLUTSize(){return (1<<m_ClutWidth);};

	/*! Returns the width of the image in pixels
	\return the width of the image in pixels
	*/
	SI_Int GetWidth();

	/*! Returns the height of the image in pixels
	\return the height of the image in pixels
	*/
	SI_Int GetHeight();

	/*! Returns the type of image
	\return CSIBCPixMap::RGB RGB image
	\return CSIBCPixMap::RGBA RGBA image
	\return CSIBCPixMap::PALETIZED Paletized image
	*/
	SI_Int GetType();

	//
	/*! Returns the depth of all components
	\return the depth of all components
	*/
	SI_Int GetDepth();

	/*! Returns the depth of a given component
	\param in_lComponent which component to get the depth for
	\return the depth of a specific component
	*/
	SI_Int GetDepth( SI_Int in_lComponent);

	/*! Sets the depth of all components
	\param an array of 4 SI_Int containing the depth for each component
	\return SI_Error::SI_SUCCESS always returned
	*/
	SI_Error SetDepth( SI_Int *i_pDepth);

	/*! Returns the total depth of a pixel in byte
	\return the total depth of a pixel in byte
	*/
    SI_Int GetTotalPixelDepthByte();

	/*! Returns the internal pixel buffer
	\return the buffer pointer
	*/
	SI_UByte *GetMap();

	/*! Returns a pixel at x,y as an array of SI_Int values
	\param x the X coordinate to get the pixel at
	\param y the Y coordinate to get the pixel at
	\retval pVal the pixel values stored in an array of SI_UByte items (ordered as RGBA)
	\return SI_Error::SI_SUCCESS always returned
	*/

	SI_Error GetPixel( SI_Int x, SI_Int y, SI_UByte *pVal );
	/*! Returns a pixel at x,y as a series of SI_Int values
	\param x the X coordinate to get the pixel at
	\param y the Y coordinate to get the pixel at
	\retval r the red value of the pixel
	\retval g the green value of the pixel
	\retval b the blue value of the pixel
	\retval a the alpha value of the pixel
	\return SI_Error::SI_SUCCESS always returned
	*/

	SI_Error GetPixel( SI_Int x, SI_Int y, SI_Int &r, SI_Int &g, SI_Int &b, SI_Int &a );

	/*! Sets a pixel at x,y using the specified array of SI_Int values
	\param x the X coordinate to set the pixel at
	\param y the Y coordinate to set the pixel at
	\param pVal the pixel values to set in an array of SI_UByte items (ordered as RGBA)
	\return SI_Error::SI_SUCCESS always returned
	*/
	SI_Error SetPixel( SI_Int x, SI_Int y, SI_UByte *pVal );

	/*! Sets a pixel at x,y using the specified series of SI_Int values
	\param x the X coordinate to set the pixel at
	\param y the Y coordinate to set the pixel at
	\param r the red value to set
	\param g the green value to set
	\param b the blue value to set
	\param a the alpha value to set
	\return SI_Error::SI_SUCCESS always returned
	*/
	SI_Error SetPixel( SI_Int x, SI_Int y, SI_Int r, SI_Int g, SI_Int b, SI_Int a );

	/*! Sets a pixel color index at x,y
	\param x the X coordinate to get the pixel at
	\param y the Y coordinate to get the pixel at
	\param index the color index of the pixel to set
	\return SI_Error::SI_SUCCESS always returned
	*/
	SI_Error SetPixel( SI_Int x, SI_Int y, SI_Int index );

	/*! Returns the pixel color index at x,y
	\param x the X coordinate to get the pixel at
	\param y the Y coordinate to get the pixel at
	\retval pVal a pointer to the pixel color index value
	\return SI_Error::SI_SUCCESS always returned
	*/
	SI_Error GetPixelColourIndex( SI_Int x, SI_Int y, SI_UByte *pVal );

	/*! Returns the color as an array of RGBA values from the \c CLUT (PALETIZED only) at the specified index
	\param i the color index in the \c CLUT (color lookup table)
	\retval out_pRGBA a pointer to the array of RGBA values
	\return SI_Error::SI_SUCCESS always returned
	*/
	SI_Error GetColour( SI_UByte i, SI_UByte *out_pRGBA );

	/*! Returns the color as a set of RGBA values from the \C CLUT (PALETIZED only) at the specified index
	\param i the color index in the \c CLUT (color lookup table)
	\retval r the red value
	\retval g the green value
	\retval b the blue value
	\retval a the alpha value
	\return SI_Error::SI_SUCCESS always returned
	*/
	SI_Error GetColour( SI_UByte i, SI_Int *r, SI_Int *g, SI_Int *b, SI_Int *a );

	/*! Sets the color in the CLUT (PALETIZED only) at the specified index using an array of RGBA values
	\param i the color index in the \c CLUT (color lookup table)
	\param in_pRGBA array of RGBA values to set
	\return SI_Error::SI_SUCCESS always returned
	*/
	SI_Error SetColour( SI_UByte i, SI_UByte *in_pRGBA );

	/*! Sets the color in the CLUT (PALETIZED only) at the specified index using a set of RGBA values
	\param i the color index in the \c CLUT (color lookup table)
	\param r the red value to set
	\param g the green value to set
	\param b the blue value to set
	\param a the alpha value to set
	\return SI_Error::SI_SUCCESS always returned
	*/
	SI_Error SetColour( SI_UByte i, SI_Int r, SI_Int g, SI_Int b, SI_Int a = 255 );


	/*! Computes the image buffer CRC
	\return the CRC value of the pixmap buffer
	*/
    SI_Int ComputeCRC();

	/*! Turns a set of RGBA values into a packed pixel value
	\param r the red value to pack
	\param g the green value to pack
	\param b the blue value to pack
	\param a the alpha value to pack
	\param pVal a pointer to the the packed pixel value
	*/
	void PackPixel( SI_Int r, SI_Int g, SI_Int b, SI_Int a, SI_UByte *pVal ); // Turns RGBA into a packed pixel value

	/*! Unpacks a set of RGBA values from a packed pixel value
	\retval r the red value to unpack
	\retval g the green value to unpack
	\retval b the blue value to unpack
	\retval a the alpha value to unpack
	\param pVal an array containing the packed pixel value
	*/
	void UnPackPixel( SI_Int &r, SI_Int &g, SI_Int &b, SI_Int &a, SI_UByte *pVal );

	/*! Returns the image buffer index from the specified X,Y pair
	\param x the X coordinate
	\param y the Y coordinate
	\return the index in the image buffer
	*/
	SI_Int Index( SI_Int x, SI_Int y );

	// Deprecated -- do not use
	SI_UInt &TextureID() { return m_TextureID; }

	/*! Initializes the image buffer with a specified width, height, type and depth
	\param i_Width the width of the image
	\param i_Height the height of the image
	\param i_Type the type of the image
	\param i_pDepth an array containing the depth for each channel
	\return SI_Error::SI_SUCCESS always returned
	*/
	SI_Error CreateNew( SI_Int i_Width, SI_Int i_Height,
						SI_Int i_Type, SI_Int *i_pDepth );


	/*! Resizes this pixmap to a width and a height that is a power of 2
	\param method resizing method
	\return SI_Error::SI_SUCCESS always returned
	*/
	SI_Error ResizeToPowerOfTwo( SI_Int method);

	/*! Destroys the image buffer
	\return SI_Error::SI_SUCCESS always returned
	*/
	SI_Error DisposeData();

	/*! Converts this color indexed pixmap to RGBA
	\param in_PixMap the CSIBCPixMap to convert to RGBA
	\return SI_Error::SI_SUCCESS always returned
	*/
	SI_Error ConvertToRGB( CSIBCPixMap & );


	// Memory estimation overridden from CSIBCNode
	/*! Returns the used memory
	\return the used memory
	*/
	virtual SI_UInt UsedMemory();

	/*! Returns the allocated memory
	\return the allocated memory
	*/
	virtual SI_UInt AllocatedMemory();

	/*! Returns the local size
	\return the local size
	*/
	virtual SI_UInt LocalSize();

	//Static members

	/*! Returns the search path for loading bitmaps
	\return instance of CSIBCSearchPath containing all the search paths to load bitmaps from
	\sa CSIBCSearchPath
	*/
	static CSIBCSearchPath *GetSearchPath();														// Search path for textures

	/*! Adds a pixmap loader driver
	\param  the new driver to add
	\return SI_Error::SI_SUCCESS always returned
	\sa CSIBCPixMapDriver
	*/
	static SI_Error AddDriver( CSIBCPixMapDriver * );

	/*! Loads an image from disk into a pixmap
	\param in_Filename the name of the file to load
	\param in_PixMap the pixmap to load into
	\param in_ResizeToPowerOfTwo whether the image should be resized to dimensions of powers of two
	\return SI_Error::SI_SUCCESS load has succeeded
	\return SI_Error::SI_ERR_ERROR_MSG load has failed
	*/
	static SI_Error Load( CSIBCString &in_Filename, CSIBCPixMap &in_PixMap, SI_Bool in_ResizeToPowerOfTwo = TRUE  );

	/*! Loads an image from disk into a pixmap
	\param in_Filename the name of the file to load
	\param in_PixMap the pixmap to load into
	\param in_ResizeToPowerOfTwo whether the image should be resized to dimensions of powers of two
	\return SI_Error::SI_SUCCESS load has succeeded
	\return SI_Error::SI_ERR_ERROR_MSG load has failed
	*/
	static SI_Error Load( const SI_Char *in_Filename, CSIBCPixMap &in_PixMap, SI_Bool in_ResizeToPowerOfTwo = TRUE );

	/*! Loads an image from disk into the specified pixmap
	\param  the name of the file to load
	\param pMemoryBlock memory block
	\param nSize memory block size
	\retval i_OutMap the pixmap to load into
	\return SI_Error::SI_SUCCESS load has succeeded
	\return SI_Error::SI_ERR_ERROR_MSG load has failed
	*/
	static SI_Error Load( CSIBCString &, void *pMemoryBlock, SI_Int nSize, CSIBCPixMap &i_OutMap);

	/*! Loads an image from disk into a pixmap
	\param  the name of the file to load
	\param pMemoryBlock memory block
	\param nSize memory block size
	\retval i_OutMap the pixmap to load into
	\return SI_Error::SI_SUCCESS load has succeeded
	\return SI_Error::SI_ERR_ERROR_MSG load has failed
	*/
	static SI_Error Load( const SI_Char *, void *pMemoryBlock, SI_Int nSize, CSIBCPixMap &i_OutMap);

	/*! Cleans the list of loader drivers
	\return SI_Error::SI_SUCCESS always returned
	\sa CSIBCPixMapDriver
	*/
	static SI_Error Cleanup();

protected:


private:
	SI_Int m_Width;
	SI_Int m_Height;
	SI_Int m_Type;
	SI_Int m_Depth[4];														// Total bit depth of each component
	SI_Int m_TotalDepth;													// Total byte depth of a pixel
	SI_UInt m_TextureID;
	SI_Int m_ClutDepth;														// Total byte depth of a CLUT entry;
	SI_Int m_ClutWidth;														// bits in CLUT index (ie 2 colour = 1, 256 colour = 8);

	SI_UByte *m_pMap;														// pixel map
	SI_UByte *m_pCLUT;														// Colour Lookup Table
	CSIBCString	m_Filename;													// Filename

	//Static members
	static CSIBCSearchPath s_Path;											// the paths to search for an image
	static CSIBCArray< CSIBCPixMapDriver * > s_Drivers;						// the drivers to try when asked to load an image

	SI_Void	*m_pUnused;
};



#endif
// CSIBCPixMap
