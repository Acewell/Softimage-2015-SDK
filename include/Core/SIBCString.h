//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file SIBCString.h
	\brief Defines the CSIBCString and CSIAccumString classes

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

//***************************************************************************************
// Defines
//***************************************************************************************
#ifndef __CSIBCString_H__
#define __CSIBCString_H__

//***************************************************************************************
// Includes
//***************************************************************************************
#include <SIBCUtil.h>


//***************************************************************************************
// CSIBCString | General purpose string class
//***************************************************************************************

/*! \brief General purpose string class

	This class is used throughout the Crosswalk SDK as a standard method in dealing with strings.
	The strings are NULL-terminated strings. It supports many methods that perform useful
	string operations.
*/
class XSICOREEXPORT CSIBCString
{
public:

	/*! Default Constructor.
		Constructs an empty string (length zero).
	*/
	CSIBCString();

	/*! Copy Constructor.
		Constructs a string idential to \p in_pString
		\param[in]	in_pString	String to duplicate. Must not be of zero length.
	*/
	CSIBCString( const CSIBCString &in_pString );


	/*! Constructor
		Constructs a string object containing the NULL-terminated character string
		pointer to by \p in_pString.
		\param[in] in_pString Pointer to the string to use for the new string. Cannot be NULL.
	*/
	CSIBCString(const SI_Char *in_pString );			// Constructor

	~CSIBCString();										// Default Destructor

	/*! Returns the length of the string.
		\return length of the string.
	*/
	SI_Int GetLength();

	/*! Returns a character buffer with the contents of the string. This buffer should
		not be modified, and does not need to be freed after use. This function is generally
		used to output the text contained within the string.
		\return Pointer to a character buffer containing the string text.

		\eg Demonstrating good and bad usage of GetText
		\code
		SIBCString * t_pMyString = new SIBCString("Crosswalk SDK");

		// This is OK.
		printf("I think that %s is the best!\n", t_pMyString->GetText());

		// This is wrong.
		printf("I think that %s is the best!\n", t_pMyString);
		\endcode
	*/
	SI_Char *GetText();

	/*! Deletes the internal character buffer of the string, and sets the length to zero.
	*/
	void Clear();

	/*! Concatenate \p in_pString to the end of this string.
		\param[in] in_pString Pointer to the string to concatenate.
		\retval SI_Error::SI_SUCCESS The string was concatenated properly.
	*/
	SI_Error Concat(CSIBCString *in_pString);

	/*! Concatenate \p in_pString to the end of this string.
		\param[in] in_pString	Pointer to a character buffer to concatenate.
		\retval SI_Error::SI_SUCCESS The string was concatenated properly.
	*/
	SI_Error Concat(const SI_Char *in_pString);			// Concatenate to the string

	/*! Concatenate \p in_lInt to the end of this string, in string format.
		\param[in] in_lInt Integer to concatenate to the end of this string.
		\retval SI_Error::SI_SUCCESS The string was concatenated properly.
		\eg Demonstrates how to concatenate integers with a string
		\code
		SIBCString * t_pMyString = SIBCString("Crosswalk v");
		t_pMyString->Concat(3);
		t_pMyString->Concat(".");
		t_pMyString->Concat(6);
		printf("This is %s\n", t_pMyString.GetText());

		// output is "This is Crosswalk v3.6"
		\endcode
	*/
	SI_Error Concat(const SI_Int in_lInt);

	/*! Concatenate \p in_fFloat to the end of this string, in string format.
		\param[in] in_fFloat Floating-point number to concatenate to the end of this string.
		\retval SI_Error::SI_SUCCESS The string was concatenated properly.
		\eg Demonstrates how to concatenate floats with a string
		\code
		SIBCString * t_pMyString = SIBCString("Crosswalk v");
		t_pMyString->Concat(3.6f);
		printf("This is %s\n", t_pMyString.GetText());

		// output is "This is Crosswalk v3.6"
		\endcode
	*/
	SI_Error Concat(const SI_Float in_fFloat);			// Concatenate to the string

	/*! Assigns the value contained in the string \p in_pString to this string.
		\param[in] in_pString	String containing data to assign to this string.
		\retval SI_Error::SI_SUCCESS The string was assigned properly.
	*/
	SI_Error SetText(CSIBCString *in_pString);			// Assign to the string

	/*! Assigns the NULL-terminated string contained in the character buffer \p in_pString
		to this string.
		\param[in] in_pString	Pointer to the character buffer containing the
			NULL-terminated string to assign.
		\retval SI_Error::SI_SUCCESS The string was assigned properly.
	*/
	SI_Error SetText(const SI_Char *in_pString);		// Assign to the string

	/*! Assigns the string representation of \p in_lInt to this string.
		\param[in] in_lInt	Integer whose string representation should be assigned to this string
		\retval SI_Error::SI_SUCCESS The string was assigned properly.
	*/
	SI_Error SetText(const SI_Int in_lInt);				// Assign to the string

	/*! Assigns the string representation of \p in_fFloat to this string.
		\param[in] in_fFloat	Floating-point number whose string representation should be
			assigned to this string
		\retval SI_Error::SI_SUCCESS The string was assigned properly.
	*/
	SI_Error SetText(const SI_Float in_fFloat);			// Assign to the string

	/*! Returns a value indicating the lexicographic difference between this string and
		\p in_pString. Negative values indicate this string is less than \p in_pString,
		Positive values indicate this string is greater than \p in_pString, and zero values
		indicate the strings are the same.
		\param[in] in_pString	The string to compare this string with.
		\retval \c &lt;positive_integer_value&gt; indicating the difference when this string is
			greater than \p in_pString
		\retval \c &lt;negative_integer_value&gt; indicating the difference when this string is
			less than \p in_pString
		\retval \c 0 if \p in_pString and this string are the same (including when both
			buffers are NULL)
		\retval \c 1 if \p in_pString's buffer is NULL and this string's buffer is not NULL
		\retval \c -1 if this string's buffer is NULL and \p in_pString's buffer is not NULL
	*/
	SI_Int Compare(CSIBCString *in_pString);

	/*! Returns a value indicating the lexicographic difference between this string and
		\p in_pString. Negative values indicate this string is less than \p in_pString,
		Positive values indicate this string is greater than \p in_pString, and zero values
		indicate the strings are the same.
		\param[in] in_pString	The string to compare this string with.
		\retval \c &lt;positive_integer_value&gt; indicating the difference when this string is
			greater than \p in_pString
		\retval \c &lt;negative_integer_value&gt; indicating the difference when this string is
			less than \p in_pString
		\retval \c 0 if \p in_pString and this string are the same (including when both
			buffers are NULL)
		\retval \c 0 if \p in_pString and this string's buffers are NULL
		\retval \c 1 if \p in_pString's buffer is NULL and this string's buffer is not NULL
		\retval \c -1 if this string's buffer is NULL and \p in_pString's buffer is not NULL
	*/
	SI_Int Compare(const SI_Char *in_pString);			// Compare with the string

	/*! Returns a value indicating the differences between this string and the string
		representation of \p in_lInt.
		\param[in] in_lInt The integer value whose string representation is compared with this string.
		\retval \c &lt;positive_integer_value&gt; indicating the difference when this string is
			greater than \p in_lInt
		\retval \c &lt;negative_integer_value&gt; indicating the difference when this string is
			less than \p in_lInt
		\retval \c 0 if \p in_lInt and this string are the same
	*/
	SI_Int Compare(const SI_Int in_lInt);				// Compare with the string

	/*! Returns a value indicated the differences between this string and the string representation of \p in_fFloat.
		\param[in] in_fFloat The floating-pointer number whose string representation is compared with this string.
		\retval \c &lt;positive_integer_value&gt; indicating the difference when this string is
			greater than \p in_fFloat
		\retval \c &lt;negative_integer_value&gt; indicating the difference when this string is
			less than \p in_fFloat
		\retval \c 0 if \p in_fFloat and this string are the same
	*/
	SI_Int Compare(const SI_Float in_fFloat);			// Compare with the string

	/*! Converts all alphabetic characters contained within this string to lower-case characters.
		\retval SI_Error::SI_SUCCESS The string was assigned properly.
	*/
	SI_Error LowerCase();

	/*! Converts all alphabetic characters contained within this string to upper-case characters.
		\retval SI_Error::SI_SUCCESS The string was assigned properly.
	*/
	SI_Error UpperCase();								// Turns all characters in string to upper case

	/*! Removes all characters considered illegal by Softimage
		\return success/failure
	*/
	SI_Error RemoveIllegalXSICharacters();

	/*! Returns whether the string is a legal Softimage name
		\retval SI_Bool::TRUE if the string is legal
		\retval SI_Bool::FALSE otherwise
	*/
	SI_Bool IsXSILegalName();


	/*! Assignment operator. Copies the value of \p i_pString into this string.
		\param[in]	i_pString	String whose value is copied into this string.
		\return	Reference to this string.
	*/
	CSIBCString &operator = ( const CSIBCString & i_pString);

	/*! Assignment operator. Copies the value of \p i_pString into this string.
		\param[in]	i_pString	Pointer to the character buffer containing a NULL-terminated string
			whose value is copied into this string.
		\return	Reference to this string.
	*/
	CSIBCString &operator = ( const SI_Char * i_pString);

	/*! Equality operator. Determines whether \p i_pString and this string contain the same text.
		\param[in] i_pString	Reference to the string to compare to.
		\retval true if strings contain the same text
		\retval false otherwise
	*/
	bool operator == (CSIBCString & i_pString);

	/*! Equality operator. Determines whether \p i_pString and this string contain the same text.
		\param[in] i_pString	Pointer to the character buffer containing the NULL-terminated string
			to compare to.
		\retval true if strings contain the same text
		\retval false otherwise
	*/
	bool operator == (const SI_Char * i_pString);

	/*! Inequality operator. Determines whether \p i_pString and this string contain different text.
		\param[in] i_pString	Reference to the string to compare to.
		\retval true if string contain different text
		\retval false otherwise
	*/
	bool operator != (CSIBCString & i_pString);					// Tests to see if strings are not equal

	/*!	Outputs debugging information for this string. This includes the address of the string,
		the length and contents of the string buffer.
	*/
	void Dump();

	/*! Returns the amount of memory used by the string. This does not include the size of the
		SIBCString class, only the data contained in its character buffer. In SIBCString (but not
		necessarily in other classes) SIBCString::UsedMemory is equivalent to SIBCString::AllocatedMemory.
		\return	Amount of memory used by this string (in bytes).
	*/
	SI_UInt UsedMemory();								// returns the amount of used memory

	/*! Returns the amount of memory allocated by the string. This does not include the size of the
		SIBCString class, only the data contained in its character buffer. In SIBCString (but not
		necessarily in other classes) SIBCString::AllocatedMemory is equivalent to SIBCString::UsedMemory.
		\return	Amount of memory used by this string (in bytes).
	*/
	SI_UInt AllocatedMemory();							// returns the amount of allocated memory.

protected:


private:

	SI_Int		m_lLength;								// Length of the string
	SI_Char		*m_pBuffer;								// Internal SI_Char buffer
};

//***************************************************************************************
// CSIAccumString | Optimized string class.
//***************************************************************************************

/*! \brief This string class is optimized to accumulate bytes at the end efficiently.

	When used below to read unsupported templates, it makes a BIG difference in performance
	since we simply do not recalculate the string length every time. CSIBCString will do up to
	three runs through the whole buffer when resizing, which gets extremely time consuming on long runs.
*/
class XSICOREEXPORT CSIAccumString
{
	enum {eAllocSize = 0x100};
public:

	/*! Default constructor.
		Allocates an initial block of memory for string storage, and sets the
		string data empty.
	*/
	CSIAccumString()
	{
		m_AllocSize = eAllocSize;
		m_Buffer = (SI_Char*) malloc(m_AllocSize);
		m_BufferEnd = m_Buffer;
		*m_BufferEnd = 0;
	}

	~CSIAccumString()
	{
		free( m_Buffer );
	}

	/*! Deletes the internal character buffer of the string, and resets the allocated
		size to a default initial buffer size.
	*/
	void Clear()
	{
		free( m_Buffer );
		m_AllocSize = eAllocSize;
		m_Buffer = (SI_Char*) malloc(m_AllocSize);
		m_BufferEnd = m_Buffer;
		*m_BufferEnd = 0;
	}

	/*! Contenates an SI_Byte to the current string.
		\param[in] in_Byte	SI_Byte to concatenate to the current string.
	*/
	void ConcatByte( SI_Byte in_Byte )
	{
		SI_Int l_iCurrDelta = (SI_Int)(m_BufferEnd - m_Buffer);
		if ( l_iCurrDelta > ( m_AllocSize - 2 ) )
		{
			// Array doubling... Good enough.
			m_AllocSize <<= 1;
			m_Buffer = (SI_Char*) realloc(m_Buffer,m_AllocSize);
			m_BufferEnd = m_Buffer + l_iCurrDelta;
		}
		*m_BufferEnd = in_Byte;
		++m_BufferEnd;
		*m_BufferEnd = 0;
	}

	/*! Returns the length of the string.
		\return The length of the string.
	*/
	SI_Int GetLength() const { return (SI_Int)(m_BufferEnd - m_Buffer); }

	/*! Returns a character buffer with the contents of the string. This buffer should
		not be modified, and does not need to be freed after use. This function is generally
		used to output the text contained within the string. (See SIBCString::GetText).
		\return Pointer to a character buffer containing the string text.
	*/
	SI_Char *GetText() const { return m_Buffer; }

private:

	// No copy semantics needed. Play safe.
	CSIAccumString(const CSIAccumString&);
	const CSIAccumString& operator=( const CSIAccumString &);

	SI_Char*		m_Buffer;
	SI_Char*		m_BufferEnd;
	SI_Int			m_AllocSize;
};

#endif
// CSIBCString
