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

//***************************************************************************************
// Defines
//***************************************************************************************
#ifndef __CSIBCStringTable_H__
#define __CSIBCStringTable_H__

#ifdef _DEBUG
#include <assert.h>
#define _SI_ASSERT(x) assert(x)	
#else
#define _SI_ASSERT(exp)
#endif

#include "SIBCUtil.h"
#include "SIBCArray.h"
#include "SIBCString.h"
#include <string.h>

// Disable "identifier was truncated to '255' characters in the debug information" warning.
#if defined(_WIN32) || defined(_WIN32_WCE) || defined( _XBOX )
#pragma warning( disable : 4786 )
#endif

struct SKeyStringPair
{
	SI_UInt		key;
	CSIBCString	value;
};

struct SKeyStringArray : public CSIBCArray<SKeyStringPair>
{
	inline SKeyStringArray() : CSIBCArray<SKeyStringPair>(1)
	{
	}
};

struct SKeyStringTable : public CSIBCArray<SKeyStringArray>
{
	inline SKeyStringTable(SI_Int size) : CSIBCArray<SKeyStringArray>(size)
	{
	}
};

class XSICOREEXPORT CSIBCStringTable 
{
public:
	// size is configured to be close to the number 
	// of elements expected
	inline CSIBCStringTable(SI_Int size = 256) : m_table(size)
	{
	}

	virtual ~CSIBCStringTable();
	SI_UInt Insert( const SI_Char* value );
	SI_UInt GetKey( const SI_Char* value );
	const char* Get( SI_UInt key );

private :
	SKeyStringTable m_table;
		  
	SI_UInt Index(SI_UInt key);
	SI_UInt Key(const char* csBlock);
	
};

#endif // ALREADY_INCLUDED_CSIBCStringTable
