#include "DataFileParser.h"
#include "xsi_application.h"
#include "sys/stat.h"

#define _CHECKSTATMODE( st, in_mode ) ((st.st_mode & in_mode) == in_mode)

static int _GetFileStat( char* pszPath, struct stat& out_st )
{
	int res = stat( pszPath, &out_st );
	size_t nLast = strlen( pszPath )-1;
	char lastCh = pszPath[ nLast ];

	if (res != 0)
	{
		// Failed
		// note: except for drives e.g. 'c:\', stat doesn't like paths ending with a file separator, so make sure to remove it 
		// if there is one
		if ( lastCh == 92 || lastCh == 47 )
		{
			pszPath[ nLast ] = '\0';

			// Check again
			res = stat( pszPath, &out_st );
		}
	}
	pszPath[ nLast ] = lastCh;
	return res;
}

static XSI::CStatus _ValidateFilePath( const XSI::CString& in_strPath )
{	
	struct stat st;
	char* pszPath = (char*)in_strPath.GetAsciiString();
	bool bOK = _GetFileStat( pszPath, st ) == 0;

	// Make sure the path is not a folder first
	if ( bOK && _CHECKSTATMODE( st, S_IFDIR ) )
	{
		return XSI::CStatus::InvalidArgument;
	}
	
	// Check if the file exist
	if ( bOK && !_CHECKSTATMODE( st, S_IFREG ) )
	{
		return XSI::CStatus::InvalidArgument;
	}
		
	return bOK ? XSI::CStatus::OK : XSI::CStatus::False ;
}

// Close the streams 	
void CDataFileParser::Term()
{
	for (ULONG i=0; i<m_perThreadStreams.size(); i++)
	{
		m_perThreadStreams[i]->close( );
		delete m_perThreadStreams[i];
	}
	m_perThreadStreams.clear();
}

void CDataFileParser::AddSupportedAttributes( TAttribPair* in_pAttribPairs, ULONG in_nCount )
{
	for ( ULONG i = 0; i<in_nCount; i++ )
	{
		m_attribHandlers[ in_pAttribPairs[i].nPortID ] = new AttributeHandler( this, &in_pAttribPairs[i] );
		m_attribHandlersByName[ XSI::CString(in_pAttribPairs[i].szName) ] = m_attribHandlers[ in_pAttribPairs[i].nPortID ];
	}
}

CDataFileParser::AttributeHandler* CDataFileParser::GetAttributeHandler( )
{
	return (*m_attribHandlers.begin()).second;
}

CDataFileParser::AttributeHandler* CDataFileParser::GetAttributeHandler( ULONG in_portID )
{
	std::map<ULONG, AttributeHandler*>::iterator it = m_attribHandlers.find(in_portID);
	
	if ( it == m_attribHandlers.end() )
	{
		return NULL;
	}
	
	return (*it).second;
}

CDataFileParser::AttributeHandler* CDataFileParser::GetAttributeHandlerByName( const XSI::CString& in_strName )
{
	std::map<XSI::CString, AttributeHandler*>::iterator it = m_attribHandlersByName.find(in_strName);
	
	if ( it == m_attribHandlersByName.end() )
	{
		return NULL;
	}
	
	return (*it).second;
}

bool CDataFileParser::Init( const XSI::CString& in_strFile, ULONG in_nThreadCount ) 
{
	XSI::CStatus st = _ValidateFilePath( in_strFile );
	if ( st != XSI::CStatus::OK )
	{
		return false;
	}

	bool bRes = true;	
	for(ULONG i = 0; i < in_nThreadCount; i++)
	{
		// Creates a file stream object for each thread			  
		std::ifstream* p = new std::ifstream;
		p->open( in_strFile.GetAsciiString(), std::ifstream::ios_base::in | std::ifstream::ios_base::binary );
		if ( !p->is_open() )
		{
			bRes = false;
		}
		else
		{
			if ( m_perThreadStreams.size() == 0 )
			{
				// Computes the data offset for each attribute handler. We do that for the first thread only since the data offset
				// and element count will be the same in all threads.
				p->seekg( 0, std::ifstream::ios_base::beg );

				// The attribute data format used by the mycache event plugin example is the following:
				//
				// [number of attributes]
				// [attribute name character count][attribute name]
				// [data element count][byte count per element]
				// [element data block ]
				//				
				ULONG nElementCount = 0;
				ULONG nAttribCount;
				p->read( (char*)&nAttribCount, sizeof(ULONG) );

				ULONG nDataOffset = sizeof(ULONG);				
				for (ULONG i=0; i<nAttribCount; i++ )
				{
					// number of characters stored for an attribute
					ULONG nCharCount;
					p->read( (char*)&nCharCount, sizeof(ULONG) );

					// attribute name
					char szAttrib[64];
					p->read( szAttrib, sizeof(char)*nCharCount );
					szAttrib[nCharCount] = 0;

					// number of data element
					p->read( (char*)&nElementCount, sizeof(ULONG) );							
					
					// number of bytes required foe an attribute data type
					ULONG nByteCount;
					p->read( (char*)&nByteCount, sizeof(ULONG) );							
					
					// Data block is stored after the attribute header info 
					nDataOffset += sizeof(ULONG)				// nCharCount
								+ sizeof(char)*nCharCount	// attrib name
								+ sizeof(ULONG)				// number of elements
								+ sizeof(ULONG);			// number of bytes per lement

					std::map< XSI::CString, AttributeHandler* >::iterator it = m_attribHandlersByName.find( XSI::CString(szAttrib) );
					if ( it != m_attribHandlersByName.end() )
					{
						it->second->Init( nDataOffset, nElementCount );
					}
					
					nDataOffset += (nByteCount * nElementCount);

					// skip data block
					p->seekg( nByteCount * nElementCount, std::ifstream::ios_base::cur );
				}
			}
		}
		m_perThreadStreams.push_back( p );
	}
	return bRes;
}

// Init with specific attribute
bool CDataFileParser::Init( const XSI::CString& in_strFile, const TAttribPair& in_AttribPair, ULONG in_nThreadCount ) 
{
	bool bRes = true;	

	XSI::CStatus st = _ValidateFilePath( in_strFile );
	if ( st != XSI::CStatus::OK )
	{
		return false;
	}
	
	TAttribPair* pAttribPair = (TAttribPair*)&in_AttribPair;
	XSI::CString strAttrib( in_AttribPair.szName );
	ULONG nPortID = in_AttribPair.nPortID;
	
	for(ULONG i = 0; i < in_nThreadCount; i++)
	{
		// Creates a file stream object for each thread			  
		std::ifstream* p = new std::ifstream;
		p->open( in_strFile.GetAsciiString(), std::ifstream::ios_base::in | std::ifstream::ios_base::binary );
		if ( !p->is_open() )
		{
			bRes = false;
		}
		else
		{
			if ( m_perThreadStreams.size() == 0 )
			{
				// Computes the data offset for each attribute handler. We do that for the first thread only since the data offset
				// and element count will be the same in all threads.
				p->seekg( 0, std::ifstream::ios_base::beg );

				// The attribute data format used by the mycache event plugin example is the following:
				//
				// [number of attributes]
				// [attribute name character count][attribute name]
				// [data element count][byte count per element]
				// [element data block ]
				//				
				ULONG nElementCount = 0;
				ULONG nAttribCount;
				p->read( (char*)&nAttribCount, sizeof(ULONG) );

				ULONG nDataOffset = sizeof(ULONG);				
				for (ULONG i=0; i<nAttribCount; i++ )
				{
					// number of characters stored for an attribute
					ULONG nCharCount;
					p->read( (char*)&nCharCount, sizeof(ULONG) );

					// attribute name
					char szAttrib[64];
					p->read( szAttrib, sizeof(char)*nCharCount );
					szAttrib[nCharCount] = 0;

					// number of data element
					p->read( (char*)&nElementCount, sizeof(ULONG) );							
					
					// number of bytes required foe an attribute data type
					ULONG nByteCount;
					p->read( (char*)&nByteCount, sizeof(ULONG) );							
					
					// Data block is stored after the attribute header info 
					nDataOffset += sizeof(ULONG)				// nCharCount
								+ sizeof(char)*nCharCount	// attrib name
								+ sizeof(ULONG)				// number of elements
								+ sizeof(ULONG);			// number of bytes per lement

					if ( strAttrib == szAttrib )
					{
						AttributeHandler* pHandler = GetAttributeHandlerByName( strAttrib );
						if ( !pHandler )
						{
							pHandler = new AttributeHandler( this, pAttribPair );						
							m_attribHandlers[ nPortID ] = pHandler;
							m_attribHandlersByName[ strAttrib ] = m_attribHandlers[ nPortID ];
						}
						pHandler->Init( nDataOffset, nElementCount );

						break;
					}
					
					nDataOffset += (nByteCount * nElementCount);

					// skip data block
					p->seekg( nByteCount * nElementCount, std::ifstream::ios_base::cur );
				}
			}
		}
		m_perThreadStreams.push_back( p );
	}
	return bRes;
}

// Reads a CVector3f attribute value in a specific thread and at a specific index
void CDataFileParser::GetData( ULONG in_nThreadID, ULONG in_nIndex, ULONG in_nOffset, XSI::MATH::CVector3f& out_v3f )
{	
	std::ifstream* p = GetFileStream( in_nThreadID );
	if (!p || !p->is_open())
	{
		out_v3f = XSI::MATH::CVector3f();
		return;
	}
	
	p->seekg( in_nIndex*sizeof(float)*3 + in_nOffset, std::ifstream::ios_base::beg );
	
	float f[3];
	p->read( (char*)f, sizeof(float)*3 );
	out_v3f = XSI::MATH::CVector3f( f[0], f[1], f[2] );
}

// Reads a CColor4f attribute value in a specific thread and at a specific index
void CDataFileParser::GetData( ULONG in_nThreadID, ULONG in_nIndex, ULONG in_nOffset, XSI::MATH::CColor4f& out_c4f )
{
	std::ifstream* p = GetFileStream( in_nThreadID );
	if (!p || !p->is_open())
	{
		out_c4f = XSI::MATH::CColor4f();
		return;
	}
	
	p->seekg( in_nIndex*sizeof(float)*4 + in_nOffset, std::ifstream::ios_base::beg );
	
	float f[4];
	p->read( (char*)f, sizeof(float) * 4 );
	out_c4f = XSI::MATH::CColor4f( f[0], f[1], f[2], f[3] );
}

// Reads a float attribute value in a specific thread and at a specific index
void CDataFileParser::GetData( ULONG in_nThreadID, ULONG in_nIndex, ULONG in_nOffset, float& out_f )
{
	std::ifstream* p = GetFileStream( in_nThreadID );
	if (!p || !p->is_open())
	{
		out_f = 0.;
		return;
	}
	
	p->seekg( in_nIndex*sizeof(float) + in_nOffset, std::ifstream::ios_base::beg );
	
	float f;
	p->read( (char*)&f, sizeof(float) );
	out_f = f;
}

void CDataFileParser::AttributeHandler::Term()
{
	m_nDataOffset = 0;
	m_nElementCount = 0;	
	delete m_pAttribInfo;
	m_pAttribInfo = NULL;
}