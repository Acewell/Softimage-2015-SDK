//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSIParser.h
	\brief Defines the CXSIReturn, CdotXSIDict, and CXSIParser classes, as well as the
		global functions \link Callbacks Callbacks for reading/writing \endlink and
		\link Utility Utility for the parser \endlink

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

//***************************************************************************************
// Defines
//***************************************************************************************
#ifndef __CXSIParser_H__
#define __CXSIParser_H__


//***************************************************************************************
// Includes
//***************************************************************************************
#include <SIBCUtil.h>
#include <SIBCString.h>

#include "dotXSITemplate.h"
#include "CXSIFilter.h"

namespace xercesc_2_7
{
	class SAX2XMLReader;
}
class CCOLLADATemplate;

/*! \addtogroup ParserDefines Parser defines for file formats and modes
	\@{
*/

#define FORMAT_TEXT     0	/*!< Text format */
#define FORMAT_BINARY   1	/*!< Binary format */
#define FORMAT_COLLADA	2	/*!< COLLADA format */

#define OPEN_READ       0	/*!< Read file mode */
#define OPEN_WRITE      1	/*!< Write file mode */

/*! \@}
*/


//***************************************************************************************
// Typedefs
//***************************************************************************************
class CdotXSITemplate;
class CdotXSITemplates;

typedef struct
{
    SI_Int      nLen;
    SI_Char    *pLabel;
} TdotXSIDictEntry;

class CXSIParser;

typedef SI_Void (*SI_READ_CALLBACK_FNC)	( CXSIParser* );

/*! \brief Class used for the return of values from a nested parse if called explictly.
*/
class XSIEXPORT CXSIReturn
{
	public:
		void			*m_pPointer;
		CSIBCString		m_Parameter;
		int				m_Flags;
};


/*! \brief Class used for dictionary entries (binary format).
*/
class XSIEXPORT CdotXSIDict
{
public :
	/*! Constructor
	*/
    CdotXSIDict();
	/*! Destructor
	*/
    ~CdotXSIDict();
	/*! Initializes the dictionary with a preallocated number of elements.
		\param[in] i_nCount	Number of elements
	*/
    SI_Void		Init( SI_Int i_nCount );
	/*! Adds an element (they must be preallocated first).
		\param[in] i_pLabel	New entry
	*/
    SI_Void		Add( SI_Char *i_pLabel );
	/*! Returns the number of elements.
		\return Number of elements
	 */
    SI_Int		GetCount();
	/*! Returns the specified element by index.
		\param[in] i_nInd	Index of the element to retrieve
		\param[out] o_pLabel	Returned label
	*/
    SI_Void		Find( SI_Int i_nInd, SI_Char **o_pLabel );
	/*! Get the specified element by label.
		\param[in] i_pLabel	The label to search for
		\return Index of the element
	*/
    SI_Int		Find( SI_Char *i_pLabel );
	/*! Returns the total number of elements from a file.
		\param[in] i_pFptr	File pointer to read from
	*/
    SI_Void		Read( _SI_FILE i_pFptr );
	/*! Writes the used elements to file.
		\param[in] i_pFptr	File pointer to write to.
	*/
    SI_Void		Write( _SI_FILE i_pFptr );

private :
    SI_Int              m_nTotalCount;
    SI_Int              m_nCount;
    TdotXSIDictEntry   *m_Dict;
};

/*! \brief Main class for the Softimage parser
*/
class XSIEXPORT CXSIParser
{
public:
	CXSIParser();									//!< Default Constructor
	~CXSIParser();									//!< Default Destructor

	/*! Opens the file for either reading or writing
		\param[in] in_filename	File to open
		\return Results of open
	*/
	SI_Error	Open(const CSIBCString &in_filename);
	/*! Tests whether we have reached the end of file
		\retval SI_Bool::TRUE if we are at the end of the file
		\retval SI_Bool::FALSE otherwise
	*/
	SI_Bool		EndOfFile();						// end of file ?
	/*! Closes the file
		\return Whether the file was successfully closed or not
	*/
	SI_Error	Close();							// Closes a file

	/*! Returns the current file name
		\return Filename
	*/
    CSIBCString &FileName() { return m_sFilename; }

	/*! Returns the total number of supported templates.
		\return Number of supported templates
	*/
	SI_Int		GetNbSupportedTemplates();
	/*! Returns the name of a supported template
		\param[in] in_lIndex Index of template to find
		\return Template name
	*/
	SI_Char		*GetSupportedTemplate(SI_Int in_lIndex);

	/*! Returns the next token as a string
		\return Token
	*/
	SI_Char		*GetNextTokenAsCharPtr();
	/*! Returns the next token, turns it into a null-terminated string, and removes quotes
		\return Token
	*/
	SI_Char		*GetNextTokenAsString();
	/*! Returns the next token as a float
		\return Token
	*/
    SI_Float	GetNextTokenAsFloat();
	/*! Returns the next token as an integer
		\return Token
	*/
	SI_Int		GetNextTokenAsInteger();
	/*! Returns the next set of tokens into an array of floats according to the specified criteria
		\param[in] numFloats number of floats to read
		\param[in] fileStepCount number of sequential floats to read first
		\param[in] fileSkipCount number of tokens to skip before reading the next sequence of floats
		\param[in] arrayStepCount number of sequential floats to write to first
		\param[in] arraySkipCount number of array indices to skip before writing the next sequence of floats
		\param[out] i_pArray	array of floats to read.
		\return Success/failure
	*/
	SI_Error	GetNextTokensAsFloatArray(	SI_Int numFloats,
											SI_Int fileStepCount,	//Step = number of sequential floats to read first,
											SI_Int fileSkipCount,	//Skip = number of tokens to skip before reading the next sequence of floats
											SI_Int arrayStepCount,	//Step = number of sequential floats to write to first
											SI_Int arraySkipCount,	//Skip = number of array indices to skip before writing the next sequence of floats
											SI_Float *i_pArray );	//Get the next series of tokens

	/*! Returns the next set of tokens into an array of ints according to the specified criteria
		\param[in] numInts number of ints to read
		\param[in] fileStepCount number of sequential ints to read first
		\param[in] fileSkipCount number of tokens to skip before reading the next sequence of ints
		\param[in] arrayStepCount number of sequential ints to write to first
		\param[in] arraySkipCount number of array indices to skip before writing the next sequence of ints
		\param[out] i_pArray	array of ints to read.
		\return Success/failure
	*/
	SI_Error	GetNextTokensAsIntegerArray(	SI_Int numInts,
												SI_Int fileStepCount,	//Step = number of sequential ints to read first,
												SI_Int fileSkipCount,	//Skip = number of tokens to skip before reading the next sequence of ints
												SI_Int arrayStepCount,	//Step = number of sequential ints to write to first
												SI_Int arraySkipCount,	//Skip = number of array indices to skip before writing the next sequence of ints
												SI_Int *i_pArray );		//Get the next series of tokens

	/*! Returns the next set of tokens into an array of unsigned shorts according to the specified criteria
		\param[in] numUShorts number of unsigned shorts to read
		\param[in] fileStepCount number of sequential unsigned shorts to read first
		\param[in] fileSkipCount number of tokens to skip before reading the next sequence of unsigned shorts
		\param[in] arrayStepCount number of sequential unsigned shorts to write to first
		\param[in] arraySkipCount number of array indices to skip before writing the next sequence of unsigned shorts
		\param[in] i_pArray	array of unsigned shorts to read.
		\return Success/failure
	*/
	SI_Error	GetNextTokensAsUnsignedShortArray(	SI_Int numUShorts,
												SI_Int fileStepCount,	//Step = number of sequential unsigned shorts to read first,
												SI_Int fileSkipCount,	//Skip = number of tokens to skip before reading the next sequence of unsigned shorts
												SI_Int arrayStepCount,	//Step = number of sequential unsigned shorts to write to first
												SI_Int arraySkipCount,	//Skip = number of array indices to skip before writing the next sequence of unsigned shorts
												SI_UShort *i_pArray );	//Get the next series of tokens

	/*! Returns the current token as a char pointer.
		\return Current token.
	*/
	SI_Char		*GetCurrentTokenAsCharPtr();
	/*! Returns the current token as a float.
		\return Current token
	*/
	SI_Float	GetCurrentTokenAsFloat();

	/*! Returns the current token as an integer.
		\return Current token
	*/
	SI_Int		GetCurrentTokenAsInteger();

	/*! Returns the next pair as a floating point number
		\param[in] fX First value
		\param[in] fY Second value
		\return Success/failure
	*/
	SI_Error	GetNextPairAsFloat( SI_Float &fX, SI_Float &fY );

	/*! Returns the next pair as an integer.
		\param[in] nX First value
		\param[in] nY Second value
		\return Success/failure
	*/
	SI_Error 	GetNextPairAsInt( SI_Int &nX, SI_Int &nY );

	/*! Returns the next triplet as a float.
		\param[in] fX First value
		\param[in] fY Second value
		\param[in] fZ Third value
		\return Success/failure
	*/
	SI_Error	GetNextTrippletAsFloat( SI_Float &fX, SI_Float &fY, SI_Float &fZ );

	/*! Returns the next triplet as an integer.
		\param[in] nX First value
		\param[in] nY Second value
		\param[in] nZ Third value
		\return Success/failure
	*/
	SI_Error 	GetNextTrippletAsInt( SI_Int &nX, SI_Int &nY, SI_Int &nZ );

	/*! Sets the Open mode
		\param[in] i_nMode Mode that indicates whether the file is open for reading (OPEN_READ) or writing (OPEN_WRITE)
	*/
    SI_Void     SetOpenMode( SI_Int i_nMode );
	/*! Returns the Open mode
		\retval SI_Int::OPEN_READ Open for reading
		\retval SI_Int::OPEN_WRITE Open for writing
	*/
    SI_Int      GetOpenMode() { return m_nOpenMode; }

    // dotXSIFile support

	/*! Checks the next token to verify whether they are children templates or not
		\param[in] i_pReadString place holder for the token
		\retval SI_Int::TRUE Token is child template
		\retval SI_Int::FALSE Otherwise
	*/
    SI_Int              CheckNextToken( CSIBCString *i_pReadString );
	/*! Returns the the Major dotXSI File Version.
		\return Major version number
	*/
    SI_Long              GetdotXSIFileVersionMajor() { return m_dotXSIFileVersionMajor; }
	/*! Returns the the Minor dotXSI File Version.
		\return Minor version number
	*/
    SI_Long              GetdotXSIFileVersionMinor() { return m_dotXSIFileVersionMinor; }
	/*! Returns the dotXSI file format.
		\retval \c 0 text
		\retval \c 1 binary
	*/
    SI_Int              GetdotXSIFormat() { return m_dotXSIFormat; }					  //@mfunc SI_Int | CXSIParser | GetdotXSIFormat | Gets
	/*! Sets the dotXSI file format.
		\param[in] dotXSIFormat dotXSIFormat. Possible values include:
			\li \c 0 text
			\li \c 1 binary
	*/
    SI_Void             SetdotXSIFormat( SI_Int dotXSIFormat ) { m_dotXSIFormat = dotXSIFormat; } //@mfunc SI_Void | CXSIParser | SetdotXSIFormat | Sets the dotXSI file Formation.
																								  // @parm SI_Int | dotXSIFormat | dotXSI format flag.
	/*! Returns the dotXSI system flags
		\return System flags
	*/
	SI_Int              GetdotXSISystemFlags() { return m_dotXSISystemFlags; }					//@mfunc SI_Int | CXSIParser | GetdotXSISystemFlags | Gets the dotXSI System Flags.
	/*! Sets the dotXSI system flags
		\param[in] dotXSISystemFlags System flags.
	*/
    SI_Void             SetdotXSISystemFlags( SI_Int dotXSISystemFlags ) { m_dotXSISystemFlags = dotXSISystemFlags; }	//@mfunc SI_Void | CXSIParser | SetdotXSISystemFlags | Sets the dotXSI System Flags.
																									// @parm SI_Int | dotXSIFormat | dotXSI format flag.
	/*! Sets the file version
	*/
	SI_Int				SetdotXSIFileVersion( SI_Int/*!< Major version */, SI_Int /*!< Minor version */);

	/*! Returns how many file versions are supported
		\return Number of supported version
	*/

	SI_Int				GetdotXSINumFileVersion();
	/*! Returns the Major and Minor numbers of a supported version
		\return Success/failure
	*/
	SI_Error			GetdotXSIFileVersion( int/*!< Which version number to query */, int* /*!< Major version returned */, int* /*!< Minor version returned */ );

	/*! Reads the file as it was set in the parser.
	*/
    SI_Error            Read();

	/*! Writes the file as specified.
	*/
    SI_Error            Write();

	/*! Reads the templates recursively.
		\param[in] i_sTemplateName Name of template.
		\param[in] i_pParent Parent template.
		\return Success/failure
	*/
    SI_Bool             ReadTemplate( CSIBCString *i_sTemplateName, CdotXSITemplate *i_pParent );
	/*! Recursive function to write out the templates
		\param[in] dotXSITemplates Parent template collection
		\param[in] i_nInd Index of the children (which children in the collection we are exporting)
		\param[in] i_nLevel Indentation (how much to indent to keep the look indented as we nest down).
	*/
    SI_Void             WriteTemplate( CdotXSITemplates *dotXSITemplates, SI_Int i_nInd, SI_Int i_nLevel );
	/*! Returns the template collection of the Parser (only the top-level ones).
		\return Template collection
	*/
    CdotXSITemplates   *dotXSITemplate() { return m_dotXSITemplates; }	//@mfunc CdotXSITemplates* | CXSIParser | dotXSITemplate | Checks for dotXSI templates.
	/*! Returns the template collection supported for the current version
		\return Template collection
	*/
    CdotXSITemplates   *dotXSISupported() { return m_dotXSISupported; } //@mfunc CdotXSITemplates* | CXSIParser | ditXSISupported | Checks for dotXSI support.
	/*! Returns a string as read (should not be used)
		\return Read string
	*/
    SI_Int              GetString();
	/*! Adds an escape character in front of invalid ones (ie. \" )
		\param[in] in_pStr	Input string
		\param[out] out_pStr	Modified string.
		\return Success/failure
	*/
	SI_Error			AddEscapeChar ( const SI_Char *in_pStr, SI_Char *out_pStr );						//@mfunc adds an escape character in front of invalid ones (ie. \" )

    // Read utility functions
	/*! Reads the parameters which are generic (no special cases).

		Reads the parameters into the new template based on the parameter list from the current template.
		This is used by most of the callbacks because most of the templates have some generic parameters
		that can be read in batch.
		\param[in] i_pCurrentTemplate	Current template
		\param[in] i_pNewTemplate		New template (starts out as empty)
		\param[in] i_nNbParam			Number of parameters to read.
		\retval SI_Error::SI_SUCCESS The parameters were read correctly.
		\retval SI_Error::SI_ERR_BAD_ELEMENT There was an error reading a parameter.
	*/
    SI_Error ReadGenericParameters( CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate, SI_Int i_nNbParam );
	/*! Reads the next value into the specified variant. The value to read is based on the type of the variant.
		\param[out] o_vValue			Variant to write the value to
		\param[in] i_nLastInt			Unused.
		\retval SI_Error::SI_SUCCESS The parameter was read correctly.
		\retval SI_Error::SI_ERR_BAD_ELEMENT There was an error reading the parameter.
	*/
    SI_Error ReadParameterValue( SI_TinyVariant *o_vValue, SI_Int i_nLastInt );

	/*! Reads the next value into the specified variant in a COLLADA document. The value to read is
		based on the type of the variant.
		\param[out] o_vValue			Variant to write the value to
		\param[in] in_pStream			Character stream to parse
		\retval SI_Error::SI_SUCCESS The parameter was read correctly.
		\retval SI_Error::SI_ERR_BAD_ELEMENT There was an error reading the parameter.
	*/
	SI_Error ReadCOLLADAParameterValue( SI_TinyVariant *o_vValue, char **in_pStream );


	/*! Reads an array of integers into a named parameter
		\param[in] i_pNewTemplate		Template to add the new parameter to
		\param[in] i_nNbVertices		Number of integers to read
		\param[in] i_sName				Name of the new argument.
		\retval SI_Error::SI_SUCCESS The parameter was read correctly.
		\retval SI_Error::SI_ERR_BAD_ELEMENT There was an error reading the parameter.
	*/

    SI_Error ReadIntegerArray( CdotXSITemplate *i_pNewTemplate, SI_Int i_nNbVertices, SI_Char *i_sName );

	/*! Reads an array of floats into a named parameter
		\param[in] i_pNewTemplate		Template to add the new parameter to
		\param[in] i_nNbVertices		Number of floats to read
		\param[in] i_sName				Name of the new argument.
		\retval SI_Error::SI_SUCCESS The parameter was read correctly.
		\retval SI_Error::SI_ERR_BAD_ELEMENT There was an error reading the parameter.
	*/
    SI_Error ReadFloatArray( CdotXSITemplate *i_pNewTemplate, SI_Int i_nNbVertices, SI_Char *i_sName );

	/*! Reads an array of doubles into a named parameter
		\param[in] i_pNewTemplate		Template to add the new parameter to
		\param[in] i_nNbVertices		Number of doubles to read
		\param[in] i_sName				Name of the new argument.
		\retval SI_Error::SI_SUCCESS The parameter was read correctly.
		\retval SI_Error::SI_ERR_BAD_ELEMENT There was an error reading the parameter.
	*/
    SI_Error ReadDoubleArray( CdotXSITemplate *i_pNewTemplate, SI_Int i_nNbVertices, SI_Char *i_sName );

	// Writes utility functions
	/*! Indents the output by so many levels.
		\param[in] i_nLevel				Number of levels to indent per line of output.
	*/
    SI_Void WriteTabs( SI_Int i_nLevel );
	/*! Writes out the parameters that are generic from a given template
		\param[in] i_pCurrentTemplate	Template to write from
		\param[in] i_nNbParams			Number of parameters to output
		\param[in] i_nLevel				Current level (for indentation).
	*/
    SI_Void WriteGenericParameters( CdotXSITemplate *i_pCurrentTemplate, SI_Int i_nNbParams, SI_Int i_nLevel );
	/*! Generic parameter write. This is used by most of the callbacks because most
		of the templates have some generic parameters that can be written in batch.
		\param[in] i_vValue				Variant holding the value to output
		\param[in] i_nLevel				Current level for indentation
		\param[in] in_nFlag				Unused
	*/
    SI_Void WriteParameterValue( SI_TinyVariant *i_vValue, SI_Int i_nLevel, SI_Int in_nFlag = 0 );
	/*! Registers the supported templates for a given version
		\param[in] i_lMajor				Major version requested
		\param[in] i_lMinor				Minor version requested
		\param[in] i_lFormat			File format (\c FORMAT_TEXT, \c FORMAT_BINARY, \c FORMAT_COLLADA)
	*/
    SI_Void RegisterdotXSINativeTemplates( SI_Long i_lMajor, SI_Long i_lMinor, SI_Int i_lFormat );
	/*! Clears the list of supported templates (this is called prior to RegisterdotXSINativeTemplates).
		\sa RegisterdotXSINativeTemplates
	*/
    SI_Void CleardotXSINativeTemplates();
	/*! Returns the current list of native templates.
		\return Collection of CdotXSITemplate objects
	*/
    CdotXSITemplates* GetdotXSINativeTemplates();

	//
	// New centralized IO functions
	//
	/*! Tests whether we have reached the end of file
		\retval \c 1 if we are at the end of the file
		\retval \c 0 otherwise
	*/
	SI_Int			FTK_Eof ();
	/*! Opens the filter for either reading or writing
		\param[in] in_szName	Filter to open
		\param[in] in_Mode		Whether to read (\c OPEN_READ) or write (\c OPEN_WRITE)
		\return Whether the file was successfully opened or not
	*/
	SI_Int			FTK_Open (SI_Char* in_szName, _SI_FILE_MODE in_Mode );
	/*! Closes the filter when finished
		\return Whether the filter was successfully closed or not
	*/
	SI_Int			FTK_Close ();
	/*! Reads a number of bytes into the buffer passed in.
		\param[out] out_pBuffer	Output buffer
		\param[in] size		Number of bytes to read per object
		\param[in] count	Size of eash object
		\return	number of bytes read.
	*/
	SI_Long			FTK_Read (void *out_pBuffer, SI_Long size, SI_Long count);
	/*! Writes a number of bytes to the filter
		\param[in] in_pBuffer	Input buffer
		\param[in] size			Number of bytes to read per object
		\param[in] count		Size of eash object
		\return number of bytes written
	*/
	SI_Int			FTK_Write (void *in_pBuffer, SI_Long size, SI_Long count);
	/*! Prints an already formatted string as output.
		\param[in] in_szData	Formatted string to print
		\retval \c 0
	*/
	SI_Int			FTK_Printf (SI_Char* in_szData );
	/*! Moves the current position the specified number of bytes according to
		the specified Seek mode.
		\param[in] in_lCount	Number of bytes to move
		\param[in] in_iMode		How to move. Valid values are:
			\li \c SEEK_SET	Relative to start
			\li \c SEEK_CUR	Relative to end
			\li \c SEEK_END	Relative to current
		\return \c 0
	*/
	SI_Int			FTK_Seek (SI_Long in_lCount, SI_Int in_iMode );
	/*! Returns the current position
		\returns Position in the file (0 - beginning)
	*/
	SI_Long			FTK_Tell ();
	/*! Returns the next byte.
		\returns Next byte
	*/
	SI_Int			FTK_FGetc ();
	/*! Returns the next byte. This is just an alias for CXSIParser::FTK_FGetc
		\returns Next byte
	*/
	SI_Int			FTK_Getc ();

	//
	// Warning callback
	//
	/*! Initializes the Warning callback with a user-defined function.
		\param[in] in_pfncCallback	Function pointer to receive all warning messages.
	*/
	SI_Void			SetWarningCallback ( SI_WARNING_CALLBACK_FNC in_pfncCallback );
	/*! Outputs a warning to the callback (or default if not set).
		\param[in] in_szWarning			Warning message
		\param[in] in_iWarningLevel		Type of warning (SI_MESSAGE, SI_WARNING, SI_ERROR)
	*/
	SI_Void			FTK_Warning ( SI_Char *in_szWarning, SI_Int in_iWarningLevel );

	/*! Returns the last error that occurred in the parser.
		\return	The error code indicating the last error that occurred.
	*/
	SI_Error		GetLastError() { return m_nLastError; }

	//
	// read callback
	//
	/*! Initializes the Read callback with a user defined function.
		\param[in] in_pCallback		Callback function to use.
	*/
	SI_Void					SetReadCallback(SI_READ_CALLBACK_FNC in_pCallback);
	/*! Returns the current Read callback
		\return	Read callback
	*/
	SI_READ_CALLBACK_FNC	GetReadCallback();

	/*! Clears the template skip table
	*/
	SI_Void	ClearSkipTable();

	/*! Adds a template name to the skip table. All templates of this name will be skipped when writing the file
	*/
	SI_Void SkipTemplate ( CSIBCString /*!< Name of the template to skip */);

	  // -----------------------------------------------------------------------
    //  Implementations of the SAX DocumentHandler interface
    // -----------------------------------------------------------------------
    void endDocument();

    void endElement( const void* const uri,
					 const void* const localname,
					 const void* const qname);

    void characters(const void* const chars, const unsigned int length);

    void ignorableWhitespace
    (
        const   void* const    chars
        , const unsigned int    length
    );

    void processingInstruction
    (
        const   void* const    target
        , const void* const    data
    );

    void startDocument();

    void startElement(	const   void* const    uri,
						const   void* const    localname,
						const   void* const    qname,
					    const   void*		attributes);

	SI_Char* GetErrors() { return m_csError.GetText (); }


    // -----------------------------------------------------------------------
    //  Implementations of the SAX ErrorHandler interface
    // -----------------------------------------------------------------------
    void warning(const void* exception);
    void error(const void* exception);
    void fatalError(const void* exception);

	CdotXSITemplate*	ResolveTemplateURL ( const SI_Char* in_szLibrary, const SI_Char* in_URL );


protected:
	SI_Error	ParseToken();								// Parse content for next token
	SI_Error	ParseCOLLADAToken(char **in_pStream);		// Parse COLLADA content for next token

	SI_Int		CheckFileType();							// check first few bytes for the file type

private:

	SI_Error			ReadCOLLADA();
	SI_Error			WriteCOLLADA();
	SI_Void             WriteCOLLADATemplate( CdotXSITemplates *dotXSITemplates, SI_Int i_nInd, SI_Int i_nLevel );

	enum
	{
		BUFFER_SIZE = 1024,
		FILE_BUFFER_SIZE = 16384
	};

    CSIBCString m_sFilename;                        // File name
	SI_Char		*m_Buffer;							// File read buffer
	SI_Int		m_BufferSize;
	SI_Char		*m_pCurrentToken;					// Current token
    SI_Int      m_nOpenMode;                        // 0 = READ, 1 = WRITE
	SI_Error	m_nLastError;						// Holds the last error that occurred during parsing.

	SI_Bool		IsInvalidParameterValue();			// Checks the current token, to see if it might not be a valid parameter.
	SI_Error	IncrementParseSpot();
	SI_Error	GetNextByte(SI_Byte *in_pRead);
	void		CreateFilter ();
	SI_Error	ReadDotXSIHeader();
	CXSIFilter*	CreateFilterFromID ( SI_Char* in_szID );

    // dotXSIFile support
    CdotXSITemplates   *m_dotXSITemplates;
    CdotXSITemplates   *m_dotXSISupported;
    CdotXSITemplates   *m_dotXSIUnsupported;

    SI_Long             m_dotXSIFileVersionMajor;
    SI_Long             m_dotXSIFileVersionMinor;
    SI_Int              m_dotXSIFormat;                 // TEXT | BINARY
    SI_Int              m_dotXSISystemFlags;

    CdotXSIDict         m_dotXSIDict;
    CdotXSITemplates    m_dotXSINativeTemplates;
	CSIAccumString		m_szAccumBuffer;
	SI_Long				m_lFilePtr;

	//
	// IO Filter
	//

	CXSIFilter			*m_pParserFilter;
	SI_Int				m_iDataExported;

	//
	// Warning reporting callback
	//
	SI_WARNING_CALLBACK_FNC	m_pfncWarningCallback;

	// read callback
	SI_READ_CALLBACK_FNC m_pReadCallback;

	//
	// COLLADA Specific
	//
	xercesc_2_7::SAX2XMLReader		*m_pXMLParser;
	CSIBCString			m_XMLBuffer;
	CSIBCString			m_csError;
	CCOLLADATemplate    *m_pParentTemplate;
	CdotXSITemplate*	RecurseResolveURL ( CdotXSITemplate* in_pTemplate, const SI_Char* libID, const SI_Char* in_URL );

	CSIBCArray<CSIBCString>	m_SkipTable;
	SI_Int					m_iIsInsideExtra;
	bool					m_bNoTyping;
};


//***************************************************************************************
// Global Functions
//***************************************************************************************
/*! \addtogroup Utility Utility for the parser
	\@{

	Returns whether the char is a separator or not.
	\param[in] i_Char char to check
	\retval SI_Bool::TRUE if a separator.
*/
extern SI_Bool IsSeparator( SI_Char i_Char );

/* \@}
*/


/*! \addtogroup Callbacks Callbacks for reading/writing
	\@{
*/

/*! Reads a generic template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\return Success/failure
*/
SI_Error dotXSICB_ReadGeneric( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate );
/*! Reads a cluster template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\return Success/failure
*/
SI_Error dotXSICB_ReadCluster( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate );
/*! Reads a constraint template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\return Success/failure
*/
SI_Error dotXSICB_ReadConstraint( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate );
/*! Reads a CustomPset template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\return Success/failure
*/
SI_Error dotXSICB_ReadCustomPSet( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate );
/*! Reads a Envelope template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\return Success/failure
*/
SI_Error dotXSICB_ReadEnvelope( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate );
/*! Reads a FCurve template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\return Success/failure
*/
SI_Error dotXSICB_ReadFCurve( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate );
/*! Reads a FileInfo template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\return Success/failure
*/
SI_Error dotXSICB_ReadFileInfo( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate );
/*! Reads a IKRoot template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\return Success/failure
*/
SI_Error dotXSICB_ReadIKRoot( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate );
/*! Reads a ImageClip template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\return Success/failure
*/
SI_Error dotXSICB_ReadImageClip( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate );
/*! Reads a Light template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\return Success/failure
*/
SI_Error dotXSICB_ReadLight( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate );
/*! Reads a NurbsSurface template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\return Success/failure
*/
SI_Error dotXSICB_ReadNurbsSurface( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate );
/*! Reads a NurbsCurve template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\return Success/failure
*/
SI_Error dotXSICB_ReadNurbsCurve( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate );
/*! Reads a PatchSurface template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\return Success/failure
*/
SI_Error dotXSICB_ReadPatchSurface( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate );
/*! Reads a PolygonList template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\return Success/failure
*/
SI_Error dotXSICB_ReadPolygonList( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate );
/*! Reads a Scene template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\return Success/failure
*/
SI_Error dotXSICB_ReadScene( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate );
/*! Reads a Shape template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\return Success/failure
*/
SI_Error dotXSICB_ReadShape( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate );
/*! Reads a TriangleList template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\return Success/failure
*/
SI_Error dotXSICB_ReadTriangleList( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate );
/*! Reads a TriStrip template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\return Success/failure
*/
SI_Error dotXSICB_ReadTriStrip( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate );

/*! Writes a Generic template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\param[in] i_nLevel					Depth
	\return Success/failure
*/
SI_Error dotXSICB_WriteGeneric( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate, SI_Int i_nLevel );
/*! Writes a Cluster template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\param[in] i_nLevel					Depth
	\return Success/failure
*/
SI_Error dotXSICB_WriteCluster( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate, SI_Int i_nLevel );
/*! Writes a Constraint template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\param[in] i_nLevel					Depth
	\return Success/failure
*/
SI_Error dotXSICB_WriteConstraint( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate, SI_Int i_nLevel );
/*! Writes a CustomPSet template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\param[in] i_nLevel					Depth
	\return Success/failure
*/
SI_Error dotXSICB_WriteCustomPSet( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate, SI_Int i_nLevel );
/*! Writes a Envelope template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\param[in] i_nLevel					Depth
	\return Success/failure
*/
SI_Error dotXSICB_WriteEnvelope( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate, SI_Int i_nLevel );
/*! Writes a FCurve template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\param[in] i_nLevel					Depth
	\return Success/failure
*/
SI_Error dotXSICB_WriteFCurve( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate, SI_Int i_nLevel );
/*! Writes a FileInfo template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\param[in] i_nLevel					Depth
	\return Success/failure
*/
SI_Error dotXSICB_WriteFileInfo( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate, SI_Int i_nLevel );
/*! Writes a IKRoot template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\param[in] i_nLevel					Depth
	\return Success/failure
*/
SI_Error dotXSICB_WriteIKRoot( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate, SI_Int i_nLevel );
/*! Writes a ImageClip template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\param[in] i_nLevel					Depth
	\return Success/failure
*/
SI_Error dotXSICB_WriteImageClip( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate, SI_Int i_nLevel );
/*! Writes a NurbsSurface template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\param[in] i_nLevel					Depth
	\return Success/failure
*/
SI_Error dotXSICB_WriteNurbsSurface( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate, SI_Int i_nLevel );
/*! Writes a NurbsCurve template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\param[in] i_nLevel					Depth
	\return Success/failure
*/
SI_Error dotXSICB_WriteNurbsCurve( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate, SI_Int i_nLevel );
/*! Writes a PatchSurface template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\param[in] i_nLevel					Depth
	\return Success/failure
*/
SI_Error dotXSICB_WritePatchSurface( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate, SI_Int i_nLevel );
/*! Writes a PolygonList template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\param[in] i_nLevel					Depth
	\return Success/failure
*/
SI_Error dotXSICB_WritePolygonList( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate, SI_Int i_nLevel );
/*! Writes a Shape template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\param[in] i_nLevel					Depth
	\return Success/failure
*/
SI_Error dotXSICB_WriteShape( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate, SI_Int i_nLevel );
/*! Writes a TriangleList template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\param[in] i_nLevel					Depth
	\return Success/failure
*/
SI_Error dotXSICB_WriteTriangleList( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate, SI_Int i_nLevel );
/*! Writes a TriStrip template
	\param[in] i_pParser				Parser used
	\param[in] i_pCurrentTemplate		Parent Template
	\param[in] i_pNewTemplate			New child template
	\param[in] i_nLevel					Depth
	\return Success/failure
*/
SI_Error dotXSICB_WriteTriStrip( CXSIParser *i_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate, SI_Int i_nLevel );

/* \@}
*/

#endif // CXSIParser
