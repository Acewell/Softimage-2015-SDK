//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file SIILUtil.h
	\brief Defines the ::SI_ImageSwapFloat global function

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

//***************************************************************************************
// Defines
//***************************************************************************************
#ifndef __SIILUTIL_H__
#define __SIILUTIL_H__

//***************************************************************************************
// Includes
//***************************************************************************************
#include <SIBCUtil.h>


//***************************************************************************************
// Defines
//***************************************************************************************
#ifdef _WIN32

#ifndef LITTLE_ENDIAN
#define SWAP_SHORT(n) (((((SI_UShort)(n))&0xff00)>>8)|((((SI_UShort)(n))&0x00ff)<<8))
#define SWAP_LONG(n) ((((SI_ULong)(n))>>24)|(((SI_ULong)(n))>>8&0xff00)|(((SI_ULong)(n))<<8&0xff0000)|(((SI_ULong)(n))<<24))
#define SWAP_FLOAT(n) SI_ImageSwapFloat(n)
#define INV_SWAP_SHORT(n) (n)
#define INV_SWAP_LONG(n) (n)
#define INV_SWAP_FLOAT(n) (n)
#else
#define SWAP_SHORT(n) (n)
#define SWAP_LONG(n) (n)
#define SWAP_FLOAT(n) (n)
#define INV_SWAP_SHORT(n) (((((SI_UShort)(n))&0xff00)>>8)|((((SI_UShort)(n))&0x00ff)<<8))
#define INV_SWAP_LONG(n) ((((SI_ULong)(n))>>24)|(((SI_ULong)(n))>>8&0xff00)|(((SI_ULong)(n))<<8&0xff0000)|(((SI_ULong)(n))<<24))
#define INV_SWAP_FLOAT(n) SI_ImageSwapFloat(n)
#endif

#else

#ifndef BYTE_ORDER

#ifndef LITTLE_ENDIAN
#define SWAP_SHORT(n) (n)
#define SWAP_LONG(n) (n)
#define SWAP_FLOAT(n) (n)
#define INV_SWAP_SHORT(n) (((((SI_UShort)(n))&0xff00)>>8)|((((SI_UShort)(n))&0x00ff)<<8))
#define INV_SWAP_LONG(n) ((((SI_ULong)(n))>>24)|(((SI_ULong)(n))>>8&0xff00)|(((SI_ULong)(n))<<8&0xff0000)|(((SI_ULong)(n))<<24))
#define INV_SWAP_FLOAT(n) SI_ImageSwapFloat(n)
#else
#define SWAP_SHORT(n) (((((SI_UShort)(n))&0xff00)>>8)|((((SI_UShort)(n))&0x00ff)<<8))
#define SWAP_LONG(n) ((((SI_ULong)(n))>>24)|(((SI_ULong)(n))>>8&0xff00)|(((SI_ULong)(n))<<8&0xff0000)|(((SI_ULong)(n))<<24))
#define SWAP_FLOAT(n) SI_ImageSwapFloat(n)
#define INV_SWAP_SHORT(n) (n)
#define INV_SWAP_LONG(n) (n)
#define INV_SWAP_FLOAT(n) (n)
#endif

#else

#if ( BYTE_ORDER == LITTLE_ENDIAN )
#define SWAP_SHORT(n) (n)
#define SWAP_LONG(n) (n)
#define SWAP_FLOAT(n) (n)
#define INV_SWAP_SHORT(n) (((((SI_UShort)(n))&0xff00)>>8)|((((SI_UShort)(n))&0x00ff)<<8))
#define INV_SWAP_LONG(n) ((((SI_ULong)(n))>>24)|(((SI_ULong)(n))>>8&0xff00)|(((SI_ULong)(n))<<8&0xff0000)|(((SI_ULong)(n))<<24))
#define INV_SWAP_FLOAT(n) SI_ImageSwapFloat(n)
#else
#define SWAP_SHORT(n) (((((SI_UShort)(n))&0xff00)>>8)|((((SI_UShort)(n))&0x00ff)<<8))
#define SWAP_LONG(n) ((((SI_ULong)(n))>>24)|(((SI_ULong)(n))>>8&0xff00)|(((SI_ULong)(n))<<8&0xff0000)|(((SI_ULong)(n))<<24))
#define SWAP_FLOAT(n) SI_ImageSwapFloat(n)
#define INV_SWAP_SHORT(n) (n)
#define INV_SWAP_LONG(n) (n)
#define INV_SWAP_FLOAT(n) (n)
#endif

#endif

#endif


//***************************************************************************************
// Global Function
//***************************************************************************************
/*! Byte-swaps the specified float value
\param value float value to byte-swap
\return byte-swapped float value
*/
extern SI_Float SI_ImageSwapFloat(SI_Float value);


#endif // __SIILUTIL_H__
