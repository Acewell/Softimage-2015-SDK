// Display.cpp: implementation of the Display class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <stdio.h>
#include "Display.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//***************************************************************************************
// Defines
//***************************************************************************************

#define SOFT_MAGIC    0x5380f634
#define SOFT_PICTID   "PICT"
#define SOFT_VERSION  3.5

#define CHANNEL_RED   0x80
#define CHANNEL_GREEN 0x40
#define CHANNEL_BLUE  0x20
#define CHANNEL_ALPHA 0x10

#define COMPRESSION_NONE      0x00
#define COMPRESSION_RLE       0x01
#define COMPRESSION_MIXED_RLE 0x02

#define SI_Int		int
#define SI_UInt		unsigned int
#define SI_Float	float
#define SI_Char		char
#define SI_UShort	unsigned short
#define SI_UByte	unsigned char
#define SI_ULong	ULONG
#define SI_Bool		BOOL

SI_Float SI_ImageSwapFloat(SI_Float value);


#ifdef _WIN32
#ifndef LITTLE_ENDIAN
#define SWAP_SHORT(n) (((((SI_UShort)(n))&0xff00)>>8)|((((SI_UShort)(n))&0x00ff)<<8))
#define SWAP_LONG(n) ((((SI_ULong)(n))>>24)|(((SI_ULong)(n))>>8&0xff00)|(((SI_ULong)(n))<<8&0xff0000)|(((SI_ULong)(n))<<24))
#define SWAP_FLOAT(n) SI_ImageSwapFloat(n)
#else
#define SWAP_SHORT(n) (n)
#define SWAP_LONG(n) (n)
#define SWAP_FLOAT(n) (n)
#endif
#else
#ifndef LITTLE_ENDIAN
#define SWAP_SHORT(n) (n)
#define SWAP_LONG(n) (n)
#define SWAP_FLOAT(n) (n)
#else
#define SWAP_SHORT(n) (((((SI_UShort)(n))&0xff00)>>8)|((((SI_UShort)(n))&0x00ff)<<8))
#define SWAP_LONG(n) ((((SI_ULong)(n))>>24)|(((SI_ULong)(n))>>8&0xff00)|(((SI_ULong)(n))<<8&0xff0000)|(((SI_ULong)(n))<<24))

#define SWAP_FLOAT(n) SI_ImageSwapFloat(n)
#endif
#endif

enum { NO_FIELD = 0, ODD_FIELD = 1,  EVEN_FIELD = 2, FULL_FRAME = 3 };

struct		HeaderStruct
{
	LONG	magic;		//A predefined magic number: BINARY_MAGIC_NUMBER. It is 5380f634 (in hex.).
	float	version;		//Version of format (float).
	BYTE	comment[ 80 ];	//Prototype description
	BYTE	id[ 4 ];		//"PICT"
	short	width;
	short	height;
	float	ratio;			//Pixel aspect ratio. Corresponds to pixel width / height. In the case of square pixel, this ratio is 1
	short	field;			//Indicates the picture field type (depending on the manner of using video scanline).
	//The fields field can take one of following codes:
	//NO_FIELD 0 No picture 
	//ODD_FIELD 1 Odd scanline 
	//EVEN_FIELD 2 Even scanline 
	//FULL_FRAME 3 Every scanline 
	short	pad;			//Unused. Should be zero.
} m_Header;					// header info on read


enum {   
	UNCOMPRESSED		= 0x00,  MIXED_RUN_LENGTH = 0x02,
		RED_CHANNEL			= 0x80,
		GREEN_CHANNEL		= 0x40,
		BLUE_CHANNEL		= 0x20,
		ALPHA_CHANNEL		= 0x10,
		
		ALL_CHANNEL_MASK	= 0xf0,		// only used for coding convenience
};
struct ChannelStruct
{
	char chained;		//	0 if last packet, 1 if there is another packet after this one.
	char size;			//	Number of bits for each pixel value by channel. Set to 8
	char type;			// Data and encoding type. UNCOMPRESSED 0x00 Image is uncompressed  MIXED_RUN_LENGTH 0x02 Run Length compression 
	BYTE channel;		// Channel code
};

BYTE *ReadLine( ChannelStruct * pChannel, int cChannels, int nWidth, BYTE * _pSrc, BYTE * _pDst, BYTE * pBufferEnd  );



Display::Display()
{
	leftButtonClicked = 0;
	rightButtonClicked =0;
	m_fFOV = m_fTOFOV = 65.0f;
	m_bAutomaticTextureReload = false;
}

Display::~Display()
{

}

void	Display::SetFOV (float in_fFOV)
{
	m_fTOFOV = in_fFOV;

}

void	Display::Tick(float milliseconds)
{
	m_fFOV = m_fFOV + (m_fTOFOV - m_fFOV) * (milliseconds/600.0f);
}

unsigned char*	Display::ReadPIC ( char* in_szFilename, int &width, int& height )
{
	DEBUGENTRY ( "Display::ReadPIC" );

	FILE* fptr = fopen ( in_szFilename, "rb");

	if ( !fptr )
		return NULL;

	fseek ( fptr, 0, SEEK_END );
	LONG dwFileSize = ftell ( fptr );
	fseek ( fptr, 0, SEEK_SET );


	LONG l_dwImageDataSize = 0;
	memset ( &m_Header, sizeof(m_Header), 0);
	
	HeaderStruct l_Header;
	DWORD dwRead = 0;
	dwRead = fread( &l_Header, sizeof(m_Header), 1, fptr);

	l_dwImageDataSize	= dwFileSize - sizeof(m_Header);
	m_Header			= l_Header;
	m_Header.magic		= SWAP_LONG ( l_Header.magic );
	m_Header.version	= SWAP_FLOAT( l_Header.version );
	m_Header.width		= SWAP_SHORT( l_Header.width );
	m_Header.height		= SWAP_SHORT( l_Header.height );
	m_Header.ratio		= SWAP_FLOAT( l_Header.ratio );
	m_Header.field		= SWAP_SHORT( l_Header.field );

	if ( m_Header.magic != SOFT_MAGIC )
	{
		fclose ( fptr );
		return NULL;
	}
	
	width = m_Header.width;
	height= m_Header.height;
	
	int cPixels = m_Header.width*m_Header.height;

	//
	// read entire file into buffer
	fseek ( fptr, 0, SEEK_SET );
	BYTE* bigbuffer = new BYTE [ dwFileSize ];
	fread ( bigbuffer, dwFileSize, 1, fptr );

	BYTE* pFileBuffer = bigbuffer + sizeof(HeaderStruct);

	BYTE * pImageBuffer = new BYTE [ m_Header.width * m_Header.height * 4 ];

	// count channel chunks
	ChannelStruct * pChannel = (ChannelStruct *)pFileBuffer;
	int cChannels = 1;
	BYTE bContainedChannels = pChannel->channel;
	while ( pChannel->chained == 1 && cChannels < 6 )
	{
		cChannels++;
		pChannel++;
		bContainedChannels |= pChannel->channel;
	}

	if ( (bContainedChannels & ALL_CHANNEL_MASK) != ALL_CHANNEL_MASK )
	{	
		// not all channels are there  - blank out the image
		DWORD * pdw = (DWORD*)pImageBuffer;
		for ( int i=0; i < cPixels; i++ )
		{
#ifdef SGI_COMPILER
			pdw[ i ] = 0x000000ff;
#else
			pdw[ i ] = 0xff000000;
#endif
		}
		
	}
	
	BYTE * pSrc = pFileBuffer + cChannels*sizeof(ChannelStruct);
	BYTE * pDst = pImageBuffer;
	BYTE * pBufferEnd = pFileBuffer + l_dwImageDataSize;
	
	// pSrc will be equal to NULL on error from ReadLine	
	for ( int iLine=0;  iLine < m_Header.height && pSrc != NULL; iLine++ )
	{
		pDst = pImageBuffer + m_Header.width*4*(m_Header.height-1-iLine);
		pSrc = ReadLine( (ChannelStruct *)pFileBuffer, cChannels, m_Header.width, pSrc, pDst, pBufferEnd );
	}
	


	/*
	// Read the Softimage PIC file header to gather some information
	fread(&header, sizeof(header), 1, fptr);	
	
	// TODO : MAC PORT ifdef
	//header.magic     = INV_SWAP_LONG(header.magic);
	//header.version   = INV_SWAP_FLOAT(header.version);
	//header.width     = INV_SWAP_SHORT(header.width);
	//header.height    = INV_SWAP_SHORT(header.height);
	//header.ratio     = INV_SWAP_FLOAT(header.ratio);
	//header.fields    = INV_SWAP_SHORT(header.fields);
	//header.completed = INV_SWAP_SHORT(header.completed);
	
	header.magic     = SWAP_LONG(header.magic);
	header.version   = SWAP_FLOAT(header.version);
	header.width     = SWAP_SHORT(header.width);
	header.height    = SWAP_SHORT(header.height);
	header.ratio     = SWAP_FLOAT(header.ratio);
	header.fields    = SWAP_SHORT(header.fields);
	header.completed = SWAP_SHORT(header.completed);
	
	if ( (header.magic != SOFT_MAGIC) ||
		(strncmp(header.id, SOFT_PICTID, 4) != 0) )
	{
		return NULL;
	}
	
	nChunks       = 0;
	global_fields = 0;
	
	do
	{
		fread(&c_chunk, sizeof(c_chunk), 1, fptr);
		
		if ( c_chunk.nb_bits != 8 )
			return NULL;
		
		c_fields[nChunks] = c_chunk.fields;
		c_types [nChunks] = c_chunk.type;
		nChunks++;
		
		global_fields += c_chunk.fields;
	}
	while (c_chunk.chained);
	
	if ( ~(CHANNEL_RED+CHANNEL_GREEN+CHANNEL_BLUE+CHANNEL_ALPHA)&global_fields )
		return NULL;
	
	w = header.width;
	h = header.height;

	width = w;
	height = h;

	bool hasalpha = false;
//	if(global_fields & CHANNEL_ALPHA)
	{
		depth[3] = 8;
		// Allocate image space
		imagebuffer = new unsigned char [ w * h * 4 ];
		hasalpha = true;
	}
//	else
//	{
		// Allocate image space
//		imagebuffer = new unsigned char [ w * h * 3 ];
//	}
	
	
	// Start reading in the content in the pixmap
	
	for(loop = h-1; loop >=0; loop--)
	{
		for (SI_Int i = 0; i < nChunks; i++)
		{
			nb_col = 0;
			if ( c_fields[i]&CHANNEL_RED )
				col[nb_col++] = r;
			if ( c_fields[i]&CHANNEL_GREEN )
				col[nb_col++] = g;
			if ( c_fields[i]&CHANNEL_BLUE )
				col[nb_col++] = b;
			if ( c_fields[i]&CHANNEL_ALPHA )
			{
				col[nb_col++] = a;
				haveAlpha = TRUE;
			}
			
			if ( (c_types[i]&0xf) == COMPRESSION_MIXED_RLE )
			{
				ok = SI_ChannelReadMixed(fptr,w, nb_col, col);
			}
			else
			{
				
				
				
				SI_UByte	tmp_col[4096 * 4];
				SI_Int		nbRead;
				
				nbRead = fread( tmp_col, 1, w * nb_col, fptr);
				
				ok = nbRead == (w*nb_col);
				if (ok)
				{
					SI_Int index = 0;
					
					for ( SI_Int m = 0; m < w; m++ )
						for ( SI_Int n = 0; n < nb_col; n++ )
							col[n][m] = tmp_col[index++];
				}
			}
		}
		
		if ( ok )
		{
			SI_UByte	pixel[4];
			
			for (SI_Int x = 0; x < w; x++)
			{
				pixel[0] = r[x];
				pixel[1] = g[x];
				pixel[2] = b[x];
				pixel[3] = a[x];
				
				LONG stride = 3;
				LONG add = (loop * w * stride) + (x * stride);

				imagebuffer [add] = pixel[0];
				imagebuffer [add+1] = pixel[1];
				imagebuffer [add+2] = pixel[2];
				imagebuffer [add+3] = pixel[3];
			}
		}
	}
*/
	fclose(fptr);
	return pImageBuffer;
}

BYTE *ReadLine( ChannelStruct * pChannel, int cChannels, int nWidth, BYTE * _pSrc, BYTE * _pDst, BYTE * pBufferEnd  )
{
	DEBUGENTRY ( "ReadLine" );

	register BYTE * pSrc = _pSrc;

	int nCount;

	BYTE * pEndOfLine = _pDst + nWidth*4;
	for ( int iChannel=0; iChannel < cChannels; iChannel++ )
	{
		register BYTE * pDst = _pDst;

		while ( pDst < pEndOfLine )
		{
			if ( pSrc >= pBufferEnd  )	// corrupted file
				return NULL; 
			// =========================================
			// explicit support for RGB chunk
			// =========================================
			if ( pChannel[ iChannel ].channel == (RED_CHANNEL | GREEN_CHANNEL | BLUE_CHANNEL) )
			{
				if ( pChannel->type == UNCOMPRESSED )
				{
					for ( int i=0; i < nWidth; i++ )
					{
						*pDst++ = *pSrc++;
						*pDst++ = *pSrc++;
						*pDst++ = *pSrc++;
						pDst++;
					}

				}
				else if ( pChannel[ iChannel ].type == MIXED_RUN_LENGTH )
				{
					nCount =  *pSrc++;
					if ( nCount >= 128 )
					{
						if ( nCount == 128 ) // special case : a LONG run (read another short)
						{
							nCount = (pSrc[ 0 ]*256) + pSrc[ 1 ]; pSrc += 2;
						}
						else
							nCount -= 127;

						if ( nCount <= 0 || nCount > nWidth )
						{
							return NULL;
						}

						for ( int c=0; c < nCount; c++ )
						{
							pDst[ 0 ] = pSrc[ 0 ]; 
							pDst[ 1 ] = pSrc[ 1 ]; 
							pDst[ 2 ] = pSrc[ 2 ]; 
							pDst += 4;
						}

						pSrc += 3;	// advance by 'RGB'
					}
					else	// raw sequence
					{
						nCount++;
						if ( nCount <= 0 || nCount > nWidth )
						{
							return NULL;
						}

						for ( int c=0; c < nCount; c++ )
						{
							*pDst++ = *pSrc++; 
							*pDst++ = *pSrc++; 
							*pDst++ = *pSrc++; 
							pDst++;
						}
					}
				}
				else
				{

					return NULL;
				}

			}
			else	// almost the same code as above; explicit support for Alpha chunk
			if ( pChannel[ iChannel ].channel == ALPHA_CHANNEL )
			{
				// =========================================
				// explicit support for Alpha chunk
				// =========================================

				if ( pChannel->type == UNCOMPRESSED )
				{
					for ( int i=0; i < nWidth; i++ )
					{
						pDst[ 3 ] = *pSrc++;	
						pDst += 4;
					}
				}
				else if ( pChannel[ iChannel ].type == MIXED_RUN_LENGTH )
				{
					nCount =  *pSrc++;
					if ( nCount >= 128 )
					{
						if ( nCount == 128 ) // special case : a LONG run (read another short)
						{
							nCount = (pSrc[ 0 ]*256) + pSrc[ 1 ]; pSrc += 2;
						}
						else
							nCount -= 127;

						if ( nCount <= 0 || nCount > nWidth )
						{
							return NULL;
						}

						for ( int c=0; c < nCount; c++ )
						{
							pDst[ 3 ] = pSrc[ 0 ]; 
							pDst += 4;
						}

						pSrc++;	// advance by 'A'
					}
					else	// raw sequence
					{
						nCount++;
						if ( nCount <= 0 || nCount > nWidth )
						{
							return NULL;
						}

						for ( int c=0; c < nCount; c++ )
						{
							pDst[ 3 ] = *pSrc++; 
							pDst += 4;
						}
					}
				}
				else
				{
					return NULL;
				}
			}
			else
			{	// ====================================
				// non-standard chunk. the generic path
				// ====================================
				if ( pChannel->type == UNCOMPRESSED )
				{
					for ( int i=0; i < nWidth; i++ )
					{
						if ( pChannel[ iChannel ].channel & RED_CHANNEL )
							pDst[ 0 ] = *pSrc++;	
						if ( pChannel[ iChannel ].channel & GREEN_CHANNEL )
							pDst[ 1 ] = *pSrc++;	
						if ( pChannel[ iChannel ].channel & BLUE_CHANNEL )
							pDst[ 2 ] = *pSrc++;	
						if ( pChannel[ iChannel ].channel & ALPHA_CHANNEL )
							pDst[ 3 ] = *pSrc++;	
						pDst += 4;
					}
				}
				else if ( pChannel[ iChannel ].type == MIXED_RUN_LENGTH )
				{
					nCount =  *pSrc++;
					if ( nCount >= 128 )
					{
						if ( nCount == 128 ) // special case : a LONG run (read another short)
						{
							nCount = (pSrc[ 0 ]*256) + pSrc[ 1 ]; pSrc += 2;
						}
						else
							nCount -= 127;

						if ( nCount <= 0 || nCount > nWidth )
						{
							return NULL;
						}

						BYTE * pPos = pSrc;
						for ( int c=0; c < nCount; c++ )
						{
							pPos = pSrc;	// every loop, restart at the run
							if ( pChannel[ iChannel ].channel & RED_CHANNEL )
								pDst[ 0 ] = *pPos++;	
							if ( pChannel[ iChannel ].channel & GREEN_CHANNEL )
								pDst[ 1 ] = *pPos++;	
							if ( pChannel[ iChannel ].channel & BLUE_CHANNEL )
								pDst[ 2 ] = *pPos++;	
							if ( pChannel[ iChannel ].channel & ALPHA_CHANNEL )
								pDst[ 3 ] = *pPos++;	
							pDst += 4;
						}
						pSrc = pPos;
					}
					else	// raw sequence
					{
						nCount++;
						if ( nCount <= 0 || nCount > nWidth )
						{
							return NULL;
						}

						for ( int c=0; c < nCount; c++ )
						{
							if ( pChannel[ iChannel ].channel & RED_CHANNEL )
								pDst[ 0 ] = *pSrc++;	
							if ( pChannel[ iChannel ].channel & GREEN_CHANNEL )
								pDst[ 1 ] = *pSrc++;	
							if ( pChannel[ iChannel ].channel & BLUE_CHANNEL )
								pDst[ 2 ] = *pSrc++;	
							if ( pChannel[ iChannel ].channel & ALPHA_CHANNEL )
								pDst[ 3 ] = *pSrc++;	
							pDst += 4;
						}
					}
				}
				else
				{
					return NULL;
				}
			}
		}
	}

	return pSrc;
}


SI_Float SI_ImageSwapFloat(SI_Float value)
{
    union
    {
        SI_Float f;
        SI_ULong i;
    } u;

    u.f = value;
    u.i = ((u.i)>>24)|((u.i)>>8&0xff00)|((u.i)<<8&0xff0000)|((u.i)<<24);

    return u.f;
}