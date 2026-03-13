#include <string.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>

#include <xsi_math.h>
#include <xsi_vector3f.h>
#include <xsi_color4f.h>
#include <xsi_string.h>
#include <xsi_icenodecontext.h>
#include <xsi_dataarray.h>
#include <xsi_indexset.h>

// Thread safe parser used by the CloudGeneratorFromDataFile and SetAttributeValuesFromDataFile nodes for reading the simulation 
// data saved by the mycache event plugin sample. The parser supports the concept of attribute handlers for extracting the attribute 
// values from the file and for setting the attribute values being evaluated. Each custom nodes must specify which attributes are 
// required. 
//
class CDataFileParser 
{
	public:

	struct TAttribPair
	{
		int nPortID;
		char szName[64];	
	};

	class AttributeHandler
	{
		public:
		AttributeHandler(CDataFileParser* p, TAttribPair* p2) : 
			m_pParser(p), 
			m_nDataOffset(0),
			m_nElementCount(0)
		{
			m_pAttribInfo = new TAttribPair( );
			size_t nSize = strlen(p2->szName);
			strncpy( m_pAttribInfo->szName, p2->szName, nSize > 64 ? 64 : nSize );
			m_pAttribInfo->nPortID = p2->nPortID;			
		}
		
		~AttributeHandler()
		{
			Term();
		}
		
		void SetValue
		( 
			XSI::ICENodeContext& in_ctxt, 
			XSI::CDataArrayLong& in_indices
		)
		{				
			XSI::siICENodeDataType dataType;
			XSI::siICENodeStructureType dataStruct;
			XSI::siICENodeContextType dataContext;			
			in_ctxt.GetPortInfo( m_pAttribInfo->nPortID, dataType, dataStruct, dataContext );
			
			switch( dataType )
			{	
				case XSI::siICENodeDataFloat:
				{
					XSI::CDataArrayFloat outData( in_ctxt );
					SetValue( in_ctxt, in_indices, outData );
				}
				break;
				
				case XSI::siICENodeDataVector3:	
				{
					XSI::CDataArrayVector3f outData( in_ctxt );
					SetValue( in_ctxt, in_indices, outData );
				}
				break;

				case XSI::siICENodeDataColor4:	
				{
					XSI::CDataArrayColor4f outData( in_ctxt );
					SetValue( in_ctxt, in_indices, outData );
				}
				break;
				
				// Add other types as needed
			}		
		}

		void Init( ULONG in_nDataOffset, ULONG in_nElementCount )
		{
			m_nDataOffset = in_nDataOffset;
			m_nElementCount = in_nElementCount;
		}
			
		void Term();
		
		ULONG GetElementCount( )
		{
			return m_nElementCount;
		}

		ULONG GetDataOffset( )
		{
			return m_nDataOffset;
		}

		private:
		template< class T >
		void SetValue
		( 
			XSI::ICENodeContext&	in_ctxt, 
			XSI::CDataArrayLong&	in_indices, 
			XSI::CDataArray<T>&		outData
		)
		{		
			ULONG nThreadID = in_ctxt.GetCurrentThreadIndex();
			
			XSI::CIndexSet indexSet( in_ctxt );		
			for(XSI::CIndexSet::Iterator it = indexSet.Begin(); it.HasNext(); it.Next())
			{								
				ULONG nIndex = in_indices[it];	
				m_pParser->GetData( nThreadID, nIndex, m_nDataOffset, outData[ it ] );
			}
		}
		
		CDataFileParser*	m_pParser;
		TAttribPair*		m_pAttribInfo;
		ULONG				m_nDataOffset;
		ULONG				m_nElementCount;
	};
	
	CDataFileParser( )
	{
	}
	
	~CDataFileParser( )
	{
		Term();	
		for ( std::map< ULONG, AttributeHandler* >::iterator it = m_attribHandlers.begin();	it != m_attribHandlers.end(); ++it )
		{
			delete (*it).second;				
		}	
	}
	
	bool Init( const XSI::CString& in_strFile, ULONG in_nThreadCount) ;		
	bool Init( const XSI::CString& in_strFile, const TAttribPair& in_attribPair, ULONG in_nThreadCount) ;		
	void Term();
	
	void AddSupportedAttributes( TAttribPair* in_pAttribPairs, ULONG in_nCount );
	AttributeHandler* GetAttributeHandler( );
	AttributeHandler* GetAttributeHandler( ULONG in_portID );
	AttributeHandler* GetAttributeHandlerByName( const XSI::CString& in_StrName );
	
	void GetData( ULONG in_nThreadID, ULONG in_nIndex, ULONG in_nOffset, XSI::MATH::CVector3f& out_v3f );
	void GetData( ULONG in_nThreadID, ULONG in_nIndex, ULONG in_nOffset, XSI::MATH::CColor4f& out_c4f );
	void GetData( ULONG in_nThreadID, ULONG in_nIndex, ULONG in_nOffset, float& out_f );
		
	private:	
	std::ifstream* GetFileStream( ULONG in_nThreadID )
	{
		if ( m_perThreadStreams.size() > 0 )
		{
			return m_perThreadStreams[ in_nThreadID ];
		}
		return NULL;
	}
	
	// The multi-thread file support is achieved by storing a file stream object per evaluation thread.
	std::vector< std::ifstream* >								m_perThreadStreams;
	
	// Attribute handlers
	std::map< ULONG /*output port id*/, AttributeHandler* >		m_attribHandlers;
	std::map< XSI::CString /*attrib name*/, AttributeHandler* >	m_attribHandlersByName;
};
