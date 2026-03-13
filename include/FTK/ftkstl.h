//***************************************************************************************
//
// File supervisor: Crosswalk team
//
// Copyright 2008 Autodesk, Inc.  All rights reserved.  
// Use of this software is subject to the terms of the Autodesk license agreement 
// provided at the time of installation or download, or which otherwise accompanies 
// this software in either electronic or hard copy form.
//
//***************************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

//*********************************************************************************************
//
//
//*********************************************************************************************

#ifndef __DSSTLMFC_H__
#define __DSSTLMFC_H__

// resolve min/max conflict between windef.h and STL
#ifdef min
	#undef min
	#define MIN_WAS_DEFINED
#endif
#ifdef max
	#undef max
	#define MAX_WAS_DEFINED
#endif

// To avoid including <bool.h>
#ifndef _BOOL
#define _BOOL
#endif

// C++ header files
#include <new.h>
#include <iostream.h>
#include <fstream.h>


//******************************************************************************
//
// Use the SGI Adapted Port STL Implementation
//
//******************************************************************************

#include <algorithm>
#include <deque>
#include <functional>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

// some backwards compatibility
#define __BEGIN_STL_NAMESPACE	__STL_BEGIN_NAMESPACE 
#define __END_STL_NAMESPACE		__STL_END_NAMESPACE 

// use only with the unix STL
#ifdef sgi
// A more user friendly define for the namespace name
# define _STL             std
// They changed the namespace define from std to __STD
# define __STL            __STD
# define std  __STD
#endif

// warning, an "#include <math.h>" unref the macros min and max
#define max(a,b)		(((a) > (b)) ? (a) : (b))
#define min(a,b)		(((a) < (b)) ? (a) : (b))

// Done include STL headers
#define __STL_OUTERMOST_HEADER_ID 0

#endif /* __DSSTLMFC_H__ */
