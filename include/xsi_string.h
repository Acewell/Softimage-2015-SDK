//*****************************************************************************
/*!
   \file xsi_string.h
   \brief CString and CStringArray class declarations.

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSISTRING_H__
#define __XSISTRING_H__

#include "sicppsdk.h"
#include <stdlib.h>

namespace XSI {

class CStatus;
class CValue;
class CStringArray;

//*****************************************************************************
/*! \class CString xsi_string.h
	\brief Character strings in the Softimage SDK are represented with the %CString class. %CString consist of a
	variable-length sequence of characters. The %CString class can store either wide characters (16-bit values)
	or ASCII ("char") characters (8-bit values).

	Using wide characters allows unicode strings to be represented in the SDK. Therefore you must use the \c L
	character before a character or a string constant to designate the wide character type constant.

	The string type of a %CString object is generally immutable. Once you create a %CString object as wide, the type
	remains as such	until an assignment operation is performed with an ASCII string; likewise when creating an ASCII
	%CString object. The %CString class provides methods to perform wide and ASCII operations. Mixing wide and ASCII
	operations is possible but would trigger internal string conversions on the method arguments which could lead to
	performance issues.

	\sa CStringArray

	\eg Using the \c L character to designate the wide-character type constant
	\code
		using namespace XSI;
		CString myString(L"Mystring");
	\endcode

	\eg The default constructor creates a wide-character CString object.
	\code
		using namespace XSI;
		CString myWideString();

		myWideString = L"Wide String";

		// This will change the CString type from wide to ASCII.
		myWideString = "ASCII String";
	\endcode

	\eg Passing a common char string will create an ASCII-character CString object.
	\code
		using namespace XSI;
		CString myAsciiString( "MyString" );

		// This will change the CString type from ASCII to wide.
		myAsciiString = L"Wide String";

	\endcode

 */
//*****************************************************************************

class SICPPSDKDECL CString
{
public:
	/*! Default constructor. The newly created CString stores a sequence of wide characters. */
	CString();

	/*! Default destructor. */
	virtual ~CString();

	/*! Constructs a CString object from another CString object. The contents of the string are duplicated.
	\param in_str constant CString reference object.
	*/
	CString(const CString& in_str);

	/*! Constructs a CString object from a null-terminated wide character string. The contents of the input
	string are duplicated inside the CString.
	\param in_str constant wchar_t* reference pointer.
	*/
	CString(const wchar_t * in_str );

	/*! Constructs a CString object by copying the first \c in_nCount characters from a null-terminated wide character string.
	\param in_str constant wchar_t* reference pointer.
	\param in_nCount Number of characters to copy from the \c in_str argument starting from position 0.
	\since 9.0 (2011)
	*/
	CString(const wchar_t* in_str, ULONG in_nCount );

	/*! Constructs a CString object from a null-terminated ASCII character string. The contents of the input
	string are duplicated inside the CString.
	\param in_str constant char* reference pointer.
	\since 7.5
	*/
	CString( const char* in_str );

	/*! Constructs a CString object by copying the first \c in_nCount characters from a null-terminated ascii character string.
	\param in_str constant char* reference pointer.
	\param in_nCount Number of characters to copy from the \c in_str argument starting from position 0.
	\since 9.0 (2011)
	*/
	CString(const char* in_str, ULONG in_nCount );

	/*! Constructs a CString object from a CValue object. This constructor allows you to initialize a CString
	object with the string representation of a CValue object.
	\param in_val constant reference to a CValue object.
	\sa CValue::GetAsText

	\eg
	\code
		using namespace XSI;

		// Old way of converting a LONG to a CString object
		CString str = CValue((LONG)myLong).GetAsText();

		// New way
		CString str2 = CValue((LONG)10);

	\endcode
	*/
	explicit CString( const CValue& in_val );

	/*! Accessor to a null-terminated, wide character representation of the string. This buffer cannot be modified.
	\note String duplication could take place if the CString object is an ASCII string.
	\return The wide char representation for this string.

	\eg
	\code
		using namespace XSI;
		CString q( L"Data" ) ;

		// Get read-only access to the internal string buffer
		const wchar_t* l_pBuffer = q.GetWideString() ;

		// We can now call normal C runtime library string functions
		if ( 0==wcscmp( l_pBuffer, L"Data" ) )
		{
			// As expected
		}

	\endcode
	*/
	const wchar_t * GetWideString() const ;

	/*! Accessor to a null-terminated, ASCII character representation of the string. This buffer is temporary and
	cannot be modified. It should not be accessed after the content of the original CString object changes or is destroyed.

	\note String duplication could take place if the CString object is a wide string.

	\return The ASCII char representation for this string.
	\since 5.0

	\eg
	\code
		using namespace XSI;
		CString q( L"Data" ) ;

		// Get read-only access to the internal string buffer
		const char* l_pBuffer = q.GetAsciiString() ;

		// We can now call normal C runtime library string functions
		if ( 0==strcmp( l_pBuffer, "Data" ) )
		{
			// As expected
		}

	\endcode
	*/
	const char* GetAsciiString() const ;

	/*! Sets the CString object with a null-terminated ASCII character string. The contents of the specified string is
	duplicated inside the CString.

	\note This method is obsolete. Use \c CString( const char* ) to create an ASCII-character CString object or
		\c CString::operator = (const char* ) to assign an ASCII string.

	\param in_pszStr constant char* reference pointer. The string is set to an empty string if the input string is empty or NULL.

	\return CStatus::OK success
	\return CStatus::False String set to empty.

	\sa CString::GetAsciiString
	\since 5.0

	\eg
	\code
		using namespace XSI;
		CString q;

		q.PutAsciiString( "Data" ) ;

		// Get read-only access to the internal string buffer
		const char* l_pBuffer = q.GetAsciiString() ;

		// We can now call normal C runtime library string functions
		if ( 0==strcmp( l_pBuffer, "Data" ) )
		{
			// As expected
		}

	\endcode
	*/
	CStatus PutAsciiString(const char* in_pszStr);

	/*! Returns the number of characters in the string.  Does not include the null-termination character.  This is not
	the number of bytes required to hold a wide-character string because each character is 2 bytes long.
	\return The number of characters in the string.
	*/
	ULONG Length() const ;

	/*! Tests whether the string is empty.
	\return true if the string is empty; false otherwise.
	*/
	bool IsEmpty() const ;

	/*! Clears the string's contents.
	*/
	void Clear() ;

	/*! Assignment operator.  The contents of the string are duplicated. This operation can change the type of this CString.
	\param in_rhs CString object that we want to assign.
	\return A reference to the newly created object.
	*/
	CString& operator=(const CString& in_rhs) ;

	/*! Assignment operator  The contents of the string are duplicated. This operation can change the type of this CString.
	\param in_rhs wide character string that we want to assign.
	\return A reference to the newly created object.
	*/
	CString& operator=(const wchar_t * in_rhs) ;

	/*! Assignment operator  The contents of the string are duplicated. This operation can change the type of this CString.
	\param in_rhs ASCII character string that we want to assign.
	\return A reference to the newly created object.
	\since 7.5
	*/
	CString& operator=(const char* in_rhs) ;

	/*! Equality operator.  Tests whether one string has the same contents as another.
	\note Comparison is case-sensitive.
	\param in_refStr CString with which we want to compare.
	\return true if all characters are the same; false if some or all of the characters are different.
	*/
	bool operator==(const CString& in_refStr) const;

	/*! Equality operator.  Tests whether the CString has the same contents as a wide character string.
	\param in_pwstr Pointer to a string with which we want to compare.
	\return true if all characters are the same; false if some or all characters are different.
	*/
	bool operator==(const wchar_t* in_pwstr) const;

	/*! Equality operator.  Tests whether the CString has the same contents as an ASCII character string.
	\param in_pstr Pointer to a string with which we want to compare.
	\return true if all characters are the same; false if some or all characters are different.
	\since 7.5
	*/
	bool operator==(const char* in_pstr) const;

	/*! Case-insensitive comparison.
	\param in_rhs CString with which we want to compare.
	\return true if the strings are the same; false otherwise.

	\eg
	\code
		using namespace XSI;
		CString A( L"A" ) ;
		CString a( L"a" ) ;

		A == a ;					// False
		A.IsEqualNoCase( a ) ;		// True
		A.IsEqualNoCase( L" a" ) ;	// False
	\endcode

	*/
	bool IsEqualNoCase( const CString& in_rhs ) const ;

	/*! Case insensitive comparison.  Tests whether one string has the same contents as another without regard to the case.
	\param in_pwstr Wide character string we want to compare.
	\return true if the strings are the same; false otherwise.
	*/
	bool IsEqualNoCase( const wchar_t* in_pwstr ) const ;

	/*! Case insensitive comparison.  Tests whether this CString object has the same contents as an ASCII character string
	without regard to the case.
	\param in_pstr ASCII character string we want to compare.
	\return true if the strings are the same; false otherwise.
	\since 7.5
	*/
	bool IsEqualNoCase( const char* in_pstr ) const ;

	/*! Parses the string and returns the sub-strings delimited by a given string. If the delimiter is empty the space
	character is used. If the string is empty, the function returns an empty array.
	\param in_strDel String delimiter.
	\return CStringArray Array constaining the sub-strings.
	\since 5.1
	*/
	CStringArray Split( const CString& in_strDel ) const;

	/*! Inequality operator.  Tests whether two CStrings have different contents.
	\note Comparison is case-sensitive.
	\param in_refStr Pointer to a string with which we want to compare.
	\return true if some or all characters are different; false if all characters are the same.
	*/
	bool operator!=(const CString& in_refStr) const;

	/*! Inequality operator.  Tests whether a CString has different contents than a wide character string.
	\note Comparison is case-sensitive.
	\param in_pwstr Pointer to a string with which we want to compare.
	\return true if some or all characters are different; false if all characters are the same.
	*/
	bool operator!=(const wchar_t* in_pwstr) const;

	/*! Inequality operator.  Tests whether a CString has different contents than an ASCII character string.
	\note Comparison is case-sensitive.
	\param in_pstr Pointer to a string with which we want to compare.
	\return true if some or all characters are different; false if all characters are the same.
	\since 7.5
	*/
	bool operator!=(const char* in_pstr) const;

	/*! Concatenation operator.
	\param in_refStr Pointer to a string that we want to add to the end.
	\return A reference to this string after it has been modified.

	\eg
	\code
		CString a( L"A" ) ;
		CString b( L"b" ) ;

		a += b ;
		// String now contains L"Ab"
	\endcode
	*/
	CString& operator+=(const CString& in_refStr);

	/*! Concatenation operator.
	\param in_pwstr Wide character string that we want to append.
	\return A reference to this string after it has been modified.
	*/
	CString& operator+=(const wchar_t* in_pwstr);

	/*! Concatenation operator.
	\param in_pstr ASCII character string that we want to append.
	\return A reference to this string after it has been modified.
	\since 7.5
	*/
	CString& operator+=(const char* in_pstr);

	/*! Concatenation operator.
	\param in_wchar concatenate a single character at the end.
	\return A reference to this string after it has been modified.
	*/
	CString& operator+=(const wchar_t in_wchar);

	/*! Concatenation operator.
	\param in_char concatenate a single ASCII character at the end.
	\return A reference to this string after it has been modified.
	\since 7.5
	*/
	CString& operator+=(const char in_char);

	/*! Addition operator.
	\param in_refStr string to add together with this string
	\return A new string that contains the concatenation of this string and in_refStr.
	*/
	CString operator+(const CString& in_refStr) const;

	/*! Addition operator.
	\param in_pwstr wide character string to add together with this string
	\return A new string that contains the concatenation of this string and in_pwstr.
	*/
	CString operator+(const wchar_t* in_pwstr) const;

	/*! Addition operator.
	\param in_pstr ASCII character string to add together with this string
	\return A new string that contains the concatenation of this string and in_pstr.
	\since 7.5
	*/
	CString operator+(const char* in_pstr) const;

	/*! Addition operator.
	\param in_wchar a single wide character to add together with this string
	\return A new string that contains the concatenation of this string and in_wchar.
	*/
	CString operator+(const wchar_t in_wchar) const;

	/*! Addition operator.
	\param in_char a single ASCII character to add together with this string
	\return A new string that contains the concatenation of this string and in_char.
	\since 7.5
	*/
	CString operator+(const char in_char) const;

	/*! Array element operator. Returns a single wide character contained in the string at a given position.
	\note String conversion may occur if this object is an ASCII character string, which could lead to
	performance issues.
	\param in_index 0-based position in the array.
	\return A wide character.
	\return 0xffff if the position is invalid.
	\sa CString::GetAt
	*/
	wchar_t operator [] (ULONG in_index) const;

	/*! Returns a single ASCII character contained in the string at a given position.
	\note String conversion may occur if this CString is a wide character string, which could lead to
		performance issues.
	\param in_index position in the 0-based array.
	\return ASCII character.
	\return 0xffff if the position is invalid.
	\sa CString::operator []
	\since 7.5
	*/
	char GetAt(ULONG in_index) const;

	/*! Less-than operator. Performs a case-sensitive comparison with the contents of a specified CString to determine
	if this CString is lexicographically less than the specified CString. This is useful for sorting operations with \c stl maps.
	\param in_str CString we want to test.
	\return true if this CString is less than the specified CString, false otherwise.
	\since 7.5
	*/
	bool operator < ( const CString& in_str) const;

	/*! Greater-than operator. Performs a case-sensitive comparison with the contents of a specified CString to determine
	if this CString is lexicographically greater than the specified CString.
	\param in_str CString we want to test.
	\return true if this CString is greater than the specified CString, false otherwise.
	\since 7.5
	*/
	bool operator > ( const CString& in_str) const;

	/*! Searches this string instance in the forward direction for the first occurrence of the specified string.
	\param in_str The string to look for.
	\param in_nOffset Index of the position at which the search is to begin. The default position is \c 0.
	\return The position of the sub-string searched when successful. If no sub-string is found, the function returns \c UINT_MAX.

	\sa CString::ReverseFindString, CString::GetSubString
	\since 7.5

	\eg Demonstrates a number of options for forward string searching
	\code
		CString str( "0123456789" ) ;

		// Returns 0 for an exact match
		ULONG npos = str.FindString( str );

		// Returns 0 for an empty string
		npos = str.FindString( CString() );

		// Returns 1 if "12" is found
		npos = str.FindString( CString("12") );

		// Returns UINT_MAX if "777" is not found
		npos = str.FindString( CString("777") );

		// Returns UINT_MAX if "12" is not found
		npos = str.FindString( CString("12"), str.Length() );

		// Returns the specified search position (i.e. 10) for an empty string
		npos = str.FindString( CString(), 10 );

		// Returns UINT_MAX if the specified search position exceeds the string size
		npos = str.FindString( CString("12"), str.Length()+1 );
	\endcode
	*/
	ULONG FindString( const CString& in_str, ULONG in_nOffset = 0 ) const;

	/*! Searches this string instance in the backward direction for the first occurrence of the specified string.
	\param in_str The string to look for.
	\param in_nOffset Index of the position at which the search is to begin. The default position is \c UINT_MAX which is
		equivalent to the position of the last character in this string.
	\return The position of the sub-string searched when successful. If no sub-string is found, the function returns \c UINT_MAX.

	\sa CString::FindString, CString::GetSubString
	\since 7.5

	\eg Demonstrates a number of options for backward string searching
	\code
		CString str( "0123456789" ) ;

		// Returns 0 for an exact match
		ULONG npos = str.ReverseFindString( str );

		// Returns str length (i.e. 10) for an empty string
		npos = str.ReverseFindString( CString() );

		// Returns 1 if "12" is found
		npos = str.ReverseFindString( CString("12") );

		// Returns UINT_MAX if "777" is not found
		npos = str.ReverseFindString( CString("777") );

		// Returns UINT_MAX if "12" is not found
		npos = str.ReverseFindString( CString("12"), 0 );

		// Returns str length if the specified search position exceeds the string size
		npos = str.ReverseFindString( CString("12"), str.Length()+10 );
	\endcode
	*/
	ULONG ReverseFindString( const CString& in_str, ULONG in_nOffset = UINT_MAX ) const;

	/*! Returns a sub-string from this instance beginning at a specified character position. If no arguments are passed, the
	function returns a copy of this %CString.
	\param in_nOffset Index of the position at which the search is to begin. The default position is \c 0. This function
		returns an empty string if the index position exceeds this %CString size.
	\param in_nCount The number of characters to copy. The default value is \c UINT_MAX, which is equivalent to the number
		of characters for this CString. This parameter is set to \c UINT_MAX if the value exceeds the number of characters
		for this %CString.
	\return A %CString object that is a copy of the elements of this instance beginning at the position specified by the first argument.

	\sa CString::FindString, CString::ReverseFindString
	\since 7.5

	\eg Demonstrates a number of options for extracting sub-strings from a %CString instance
	\code
		CString str( "0123456789" ) ;

		// Returns "0123456789" by default
		CString substr = str.GetSubString( );

		// Returns "01234"
		substr = str.GetSubString( 0, 5 );

		// Returns empty string if the search position exeeds the str length
		substr = str.GetSubString( str.Length() + 10, 5 );

		// Returns "6789", str.length is used as 2nd argument if the requested number of characters exeeds str length.
		substr = str.GetSubString( 7, str.Length() + 10 );
	\endcode
	*/
	CString GetSubString( ULONG in_nOffset = 0, ULONG in_nCount = UINT_MAX ) const;

	/*! Convert this string to a lower-case character string.
	\sa CString::Upper
	\since 9.0 (2011)
	*/
	void Lower();

	/*! Convert this string to an upper-case character string.
	\sa CString::Lower
	\since 9.0 (2011)
	*/
	void Upper();

	/*! Removes a character or a group of characters from the beginning of this string. When called with no
	argument, the method removes newline, space and tab characters.
	\sa CString::TrimRight
	\since 11.0 (2013)
	\eg Demonstrates TrimLeft usage.
	\code
		Application app;
		CString str( "\n\n\t \t 0123456789   \n" ) ;

		// Trim blank characters
		str.TrimLeft( );
		app.LogMessage( str );
		// INFO: "0123456789   \n"

		// Trim "01234" characters
		str = "0123456789";
		str.TrimLeft( "42130" );
		app.LogMessage( str );
		// INFO: "56789"

		// Trim " *** \t" characters
		str = " *** \t0123456789";
		str.TrimLeft( " *\t" );
		app.LogMessage( str );
		// INFO: "0123456789"

	\endcode

	*/
	void TrimLeft( const CString& in_target = CString() );

	/*! Removes a character or a group of characters at the end of this string. When called with no
	argument, the method removes newline, space and tab characters.
	\sa CString::TrimLeft
	\since 11.0 (2013)

	\eg Demonstrates TrimRight usage.
	\code
		Application app;
		CString str( "\n\n\t \t 0123456789   \n" ) ;

		// Trim blank characters
		str.TrimRight( );
		app.LogMessage( str );
		// INFO: "\n\n\t \t 0123456789"

		// Trim "789" characters
		str = "0123456789";
		str.TrimRight( "978" );
		app.LogMessage( str );
		// INFO: "0123456"

		// Trim " *** \t" characters
		str = "0123456789 *** \t";
		str.TrimRight( " *\t" );
		app.LogMessage( str );
		// INFO: "0123456789"
	\endcode

	*/
	void TrimRight( const CString& in_target = CString() );

private:

	//*************************************************************************
	/*! \struct StringData xsi_string.h
		\brief Private class used for holding the CString data. Not available
		outside this class.
	*/
	//*************************************************************************
	struct StringData
	{
		void * m_pImpl ;

		//! CString content.
		/*!
			These data members point to the content of CString and are typically
			used to inspect a CString instance from the debugger.
		*/
		wchar_t* m_pWDebugStr;
		char* m_pDebugStr;
	};
	/*! CString data.*/
	StringData* m_pData;
};

/*! Addition operator
\return A new string that contains the concatenation of the two arguments.
*/
SICPPSDKDECL CString operator+( const wchar_t* in_pwstr, const CString& in_refStr ) ;

/*! Addition operator
\return A new string that contains the concatenation of the two arguments.
*/
SICPPSDKDECL CString operator+( const wchar_t in_wchar, const CString& in_refStr ) ;

/*! Addition operator
\return A new string that contains the concatenation of the two arguments.
\since 7.5
*/
SICPPSDKDECL CString operator+( const char* in_pstr, const CString& in_refStr ) ;

/*! Addition operator
\return A new string that contains the concatenation of the two arguments.
\since 7.5
*/
SICPPSDKDECL CString operator+( const char in_char, const CString& in_refStr ) ;

//*************************************************************************
/*! \class CStringArray xsi_string.h
	\brief The CStringArray is an uni-dimensional array of CString objects.

	The array is zero-based, which means that the first item index is 0 and the largest index is one less than
	the number of elements contained in the array.

	\sa CString, CRefArray::Filter, X3DObject::FindChild, X3DObject::FindChildren
*/
//*************************************************************************
class SICPPSDKDECL CStringArray
{
public:
	/*! Constructs a CStringArray and optionally initializes the array to a known size.
	\param in_size Initial size of array, defaults to 0.  If you know the exact number of items
		you want to save in the array, it can be more efficient to specify the value using this
		argument, rather than calling CStringArray::Add() many times.
	*/
	CStringArray( LONG in_size=0);

	/*! Constructs a CStringArray object from another CStringArray object.
	\param in_array read-only CStringArray object.
	*/
	CStringArray(const CStringArray& in_array );

	/*! Default destructor. */
	~CStringArray();

	/*! Assignment operator. Current contents of this array are replaced by a copy of in_array's contents.
	\param in_array read-only class object.
	\return A reference to this array.
	 */
	CStringArray& operator=( const CStringArray& in_array );

	/*! Returns the number of items in this CStringArray
	\return The number of items in the array.
	*/
	LONG GetCount() const;

	/*! Adds a CString at the end of this array's.  This increases the size of the Array. The CString is copied.
	\param in_item New item to be added at the end of the array.
	\return CStatus::OK success
	*/
	CStatus Add( const CString& in_item );

	/*! Erases all elements contained in the array.
	\return CStatus::OK success
	*/
	CStatus Clear();

	/*! Reallocates memory for the array.  Existing contents are preserved, except for items at the end of the
	array if the new size is smaller than the existing size.
	\param in_size New size of the array.
	\return CStatus::OK success
	\return CStatus::InvalidArgument in_size < 0
	*/
	CStatus Resize( LONG in_size);

	/*! Accessor to elements at a given index. The returned value is read-only.
	\param in_index index in this zero-based array.  The index must be greater or equal to zero
		and smaller than the number of elements in the array, otherwise the results are unpredictable.
	\return A read-only reference to the indexed item.
	*/
	const CString& operator[]( LONG in_index ) const;

	/*! Accessor to elements at a given index.
	\param in_index index in this zero-based array.  The index must be greater or equal to zero
		and smaller than the number of elements in the array, otherwise the results are unpredictable.
	\return A reference to the indexed item.
	*/
	CString& operator[]( LONG in_index );

	/*! Equality operator.
	\param in_array CStringArray to compare with.
	\return true if in_array contains the same number of elements as this array and if all members
		of in_array are equal to the corresponding one contained in this array.
	*/
	bool operator==(const CStringArray& in_array) const;

	/*! Inequality operator.
	\param in_array
	\return true if any member of in_array is different from the corresponding members in this
		array or if the arrays are not of the same size.
	*/
	bool operator!=(const CStringArray& in_array) const;

private:
	void* m_ptr;
};

};

#endif // __XSISTRING_H__
