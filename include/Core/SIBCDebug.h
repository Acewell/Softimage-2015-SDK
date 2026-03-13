//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file SIBCDebug.h
	\brief Defines the CSIDebug class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef __CSIBCDebug_H__
#define __CSIBCDebug_H__

///**************************************************************************************
// Includes
///**************************************************************************************
#ifndef _WIN32_WCE
#include <assert.h>
#else
#endif

#include "SIBCArray.h"
#include "SIBCString.h"


//**************************************************************************************
// @class CSIDebug | Debug mechanism.
//**************************************************************************************

#if defined( DEBUG ) && defined( _PSX2 )

/*! \brief Debug mechanism.
*/
class CSIDebug
{
public:
	/*! Default constructor
	*/
	CSIDebug();
	/*! Destructor
	*/
	~CSIDebug();
	/*! Dumps debugging information (prints out all labels).
	*/
	void Dump();
	/*! Registers a label.
	\param in_sLabel		Label
	\param in_sDescription	Description
	\param in_bSet			Set
	\return Number of used labels
	*/
	int RegisterLabel( char * in_sLabel, char * in_sDescription, bool in_bSet );
	/*! Returns label index
	\param in_sLabel		Label
	\return Label index
	*/
	int LookupLabel( char * in_sLabel );
	/*! Checks to see if label exists
	\param in_iLabel		Label
	\return Whether or not label exists
	*/
	bool CheckLabel( int in_iLabel );
	/*! Prints out debugging information.
	\param in_iLabel		Label
	\param char				Character string (format)
	\param ...				Argument list
	\return \c 0 if there is no information
	*/
	int Printf( int in_iLabel, char *, ... );
	/*! Parses arguments
	\param in_nArgs			Number of I/O arguments
	\param in_asArgs		I/O arguments
	*/
	void ParseArguments( int * in_nArgs, char ** in_asArgs );
	/*! Activates the label
	\param in_sLabel		Label
	*/
	void Set( int in_sLabel );

private:
	CSIBCArray < CSIBCString >	m_LabelArray;
	CSIBCArray < CSIBCString >	m_DescriptionArray;
	CSIBCArray < bool >	m_ValueArray;
};

extern int			g_iVerbose;
extern CSIDebug	* 	g_pSIDebug;

///**************************************************************************************
// Defines
///**************************************************************************************
#define CSIDebugRegisterLabel( v, l, d ) v = g_pSIDebug->RegisterLabel( l, d, false )
#define CSIDebugLookupLabel( l ) g_pSIDebug->CheckLabel( i )
#define CSIDebugCheck( i ) g_pSIDebug->CheckLabel( i )
#define CSIDebugDump( i ) g_pSIDebug->Dump()
#define CSIDebugPrintf g_pSIDebug->Printf
#define CSIDebugPrintf0( i, f ) g_pSIDebug->Printf( i, f )
#define CSIDebugPrintf1( i, f, a ) g_pSIDebug->Printf( i, f, a )
#define CSIDebugPrintf2( i, f, a, b ) g_pSIDebug->Printf( i, f, a, b )
#define CSIDebugPrintf3( i, f, a, b, c ) g_pSIDebug->Printf( i, f, a, b, c )
#define CSIDebugPrintf4( i, f, a, b, c, d ) g_pSIDebug->Printf( i, f, a, b, c, d )
#define CSIDebugLabel( name ) static int name
#define CSIDebugParseArguments( n, a ) g_pSIDebug->ParseArguments( n, a )
#define CSIDebugDeclare() CSIDebug	* g_pSIDebug
#define CSIDebugInit() g_pSIDebug = new CSIDebug()
#define CSIDebugCleanUp() delete g_pSIDebug
#define CSIDebugSet( i ) g_pSIDebug->Set( i );
#else
#define CSIDebugRegisterLabel( v, l, d ) 0
#define CSIDebugLookupLabel( l ) 0
#define CSIDebugCheck( i ) 0
#define CSIDebugDump( i )
#define CSIDebugSet( i )
#define CSIDebugPrintf This shouldnt compile
#define CSIDebugPrintf0( i, f )
#define CSIDebugPrintf1( i, f, a )
#define CSIDebugPrintf2( i, f, a, b )
#define CSIDebugPrintf3( i, f, a, b, c )
#define CSIDebugPrintf4( i, f, a, b, c, d )
#define CSIDebugLabel( name )
void CSIDebugParseArguments( int * in_nArgs, char ** in_asArgs );
#define CSIDebugDeclare()
#define CSIDebugInit()
#define CSIDebugCleanUp()
#endif

///**************************************************************************************
// Inline code
///**************************************************************************************





#endif // __CSIBCDebug_H__
