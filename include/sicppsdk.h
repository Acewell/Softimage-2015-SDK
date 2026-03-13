//*****************************************************************************
/*
   \file sicppsdk.h 
   \brief Defines the initialization routines for the library.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif 


#ifndef __SICPPSDK_H__
#define __SICPPSDK_H__

//********************************************************************
//
// Includes
//
//********************************************************************
#ifdef unix
#include <values.h>
#else
#include <FLOAT.H>
#pragma warning( disable : 4251 )
#pragma warning( disable : 4275 )
#endif

#include <assert.h>
#include <limits.h>

#if defined(unix) && (defined(WIN64) || defined(_WIN64) || defined(__x86_64))
typedef unsigned int ULONG;
typedef int LONG;
#else
typedef unsigned long ULONG;
typedef long LONG;
#endif

typedef int INT;
typedef unsigned int UINT;

typedef short SHORT;
typedef unsigned short USHORT;

typedef USHORT WORD;
typedef ULONG  DWORD;

typedef long long LLONG;
typedef unsigned long long ULLONG;
			 
//********************************************************************
//
// Forward declarations
//
//********************************************************************

//********************************************************************
//
// Typedefs 
//
//********************************************************************

//********************************************************************
//
// Defines
//
//********************************************************************
#ifndef SICPPSDKDECL
	#ifndef unix
		#ifdef SICPPSDKIMPL
			#define SICPPSDKDECL __declspec(dllexport)
		#else
			#define SICPPSDKDECL __declspec(dllimport) 
		#endif
	#else
		#define SICPPSDKDECL
	#endif
#endif

#ifndef XSIPLUGINCALLBACK
	// This is deprecated, use SICALLBACK instead.
	#ifdef unix
		#define XSIPLUGINCALLBACK extern "C"
	#else
		#pragma warning( disable : 4190 ) 
		#define XSIPLUGINCALLBACK extern "C" __declspec(dllexport)
	#endif
#endif

#ifndef SICALLBACK
	// Use this define to properly export C++ API callbacks
	// in your dll, for example XSILoadPlugin()
	// Note for windows developers: Using this define means that you do not need to use a .def file.
	
	#ifdef unix
		#define SICALLBACK extern "C" XSI::CStatus
	#else
		// Softimage C++ API uses C-linkage. Disable the warning that reminds us that CStatus is a C++ object
		#pragma warning( disable : 4190 ) 
		#define SICALLBACK extern "C" __declspec(dllexport) XSI::CStatus _cdecl
	#endif
#endif

#ifndef _SICALLBACK
	// Similar to SICALLBACK but takes an explicit type.	
	#ifdef unix
		#define _SICALLBACK(T) extern "C" T
	#else
		// Softimage C++ API uses C-linkage. 
		#pragma warning( disable : 4190 ) 
		#define _SICALLBACK(T) extern "C" __declspec(dllexport) T _cdecl
	#endif
#endif

#ifndef SICPPSDK_INLINE
	#ifdef unix
		#define SICPPSDK_INLINE inline
	#else
		#define SICPPSDK_INLINE __forceinline
	#endif
#endif

#endif // __SICPPSDK_H__
