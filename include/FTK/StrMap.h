//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file StrMap.h
	\brief Defines the SI_StrMap class and the StrLessPred structure

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************


#ifndef __STRMAP_H__
#define __STRMAP_H__

// Disable "identifier was truncated to '255' characters in the debug information" warning.
#if defined(_WIN32) || defined(_WIN32_WCE) || defined(_XBOX)
#pragma warning( disable : 4786 )
#endif // defined(_WIN32) || defined(_WIN32_WCE) || defined(_XBOX)

#ifdef FTK_KERNEL
#include <map>			// map
#endif // FTK_KERNEL

#include <SIBCUtil.h>	// SI_Char, _SI_STRCMP

/*! \brief String less predicate function object

	This functor can be used in STL algorithms or associative containers to sort strings.

	\eg Usage example
	\code
	set<SI_Char*, StrLessPred> l_MySet;
	\endcode
*/
struct StrLessPred
{
	/*!	Determines if in_psz1 is less than in_psz2
	\param in_psz1 First string
	\param in_psz2 Second string
	\return true if in_psz1 is less than in_psz2
	*/
	inline bool operator () ( const SI_Char* in_psz1, const SI_Char* in_psz2 ) const
	{
		return (_SI_STRCMP(in_psz1, in_psz2) < 0);
	}
};

/*! \brief Template specialization of an STL map using SI_Char* as the key type.

	\param ValueType The reference type

	\eg
	\code
	SI_StrMap<ValueType> l_MyMap;

	// is equivalent to:

	map<SI_Char*,ValueType,StrLessPred> l_MyMap;
	\endcode
*/
#ifdef FTK_KERNEL
template <class ValueType>
class SI_StrMap : public std::map<const SI_Char*, ValueType, StrLessPred>
{
};

#endif // FTK_KERNEL
#endif //__STRMAP_H__
