// ICE String Library Plugin

#include <xsi_application.h>
#include <xsi_context.h>
#include <xsi_pluginregistrar.h>
#include <xsi_status.h>

#include <xsi_icenodecontext.h>
#include <xsi_icenodedef.h>
#include <xsi_factory.h>
#include <xsi_longarray.h>
#include <xsi_doublearray.h>
#include <xsi_math.h>
#include <xsi_vector2f.h>
#include <xsi_vector3f.h>
#include <xsi_vector4f.h>
#include <xsi_matrix3f.h>
#include <xsi_matrix4f.h>
#include <xsi_rotationf.h>
#include <xsi_quaternionf.h>
#include <xsi_color4f.h>
#include <xsi_indexset.h>
#include <xsi_dataarray.h>
#include <xsi_dataarray2D.h>
#include <xsi_bitarray.h>
#include <errno.h>

/////////////////////////////////// Softimage Documentation //////////////////////////////////////////////////////
// <node id="StringToArray" label="String to Array" introduced="10.0 (2012)" categories="String">
// <description>
// Builds a 2D array of values given an input string formatted as a comma or whitespace separated list of values. The output array type is inferred 
// at connection-time from the output port type. The types supported are:
// <br/>
// <table>
//					<tr>
//						<th>Type</th>
//						<th>Note</th>
//					</tr>
//					<tr>
//						<th><object idref="siICENodeDataType#siICENodeDataBool"/></th>
//						<th></th>
//					</tr>
//					<tr>
//						<th><object idref="siICENodeDataType#siICENodeDataColor4"/></th>
//						<th>Input string must contain groups of 4 float values.</th>
//					</tr>
//					<tr>
//						<th><object idref="siICENodeDataType#siICENodeDataFloat"/></th>
//						<th></th>
//					</tr>
//					<tr>
//						<th><object idref="siICENodeDataType#siICENodeDataLong"/></th>
//						<th>Values can be specified with a range syntax.</th>
//					</tr>
//					<tr>
//						<th>Example 1</th>
//						<th>Value: 1,2,3-5,6  Result:1 2 3 4 5 6</th>
//					</tr>
//					<tr>
//						<th>Example 2</th>
//						<th>Value: -3-1 2-4 7-5 8-10 -1  Result:-3 -2 -1 0 1 2 3 4 7 6 5 8 9 10 -1</th>
//					</tr>
//					<tr>
//						<th>Example 3</th>
//						<th>Value: -3--1 -5--3  Result:-3 -2 -1 -5 -4 -3</th>
//					</tr>
//					<tr>
//						<th><object idref="siICENodeDataType#siICENodeDataMatrix33"/></th>
//						<th>Input string must contain groups of 9 float values.</th>
//					</tr>
//					<tr>
//						<th><object idref="siICENodeDataType#siICENodeDataMatrix44"/></th>
//						<th>Input string must contain groups of 16 float values.</th>
//					</tr>
//					<tr>
//						<th><object idref="siICENodeDataType#siICENodeDataQuaternion"/></th>
//						<th>Input string must contain groups of 4 float values.</th>
//					</tr>
//					<tr>
//						<th><object idref="siICENodeDataType#siICENodeDataVector2"/></th>
//						<th>Input string must contain groups of 2 float values.</th>
//					</tr>
//					<tr>
//						<th><object idref="siICENodeDataType#siICENodeDataVector3"/></th>
//						<th>Input string must contain groups of 3 float values.</th>
//					</tr>
//					<tr>
//						<th><object idref="siICENodeDataType#siICENodeDataVector4"/></th>
//						<th>Input string must contain groups of 4 float values.</th>
//					</tr>
//					<tr>
//						<th><object idref="siICENodeDataType#siICENodeDataRotation"/></th>
//						<th>Input string must contain groups of 3 float values.</th>
//					</tr>
// </table>
// <b>Note:</b> For complex types array such as siICENodeDataVector3 or siICENodeDataMatrix33, if the number of items in the value string is wrong 
// (e.g. missing Z coordinate), the output list will be empty.
// </description>
// <inputs>
// 	<inputport id="Value" label="Value">
// 		<description>A string containing a comma-separated or whitespace-separated list of values. Each values are converted to the output port type and added to a 2D array.</description>
// 		<type map="-1"><object idref="siICENodeDataType#siICENodeDataString"/></type>
// 		<structure map="-1"><object idref="siICENodeStructureType#siICENodeStructureSingle"/></structure>
// 		<context map="402"><object idref="siICENodeContextType#siICENodeContextAny"/></context>
// 	</inputport>
// </inputs>
// <outputs>
// <outputport id="Result" label="Result">
// 	<description>The 2D array generated from the input string value.</description>
// 	<type map="-1">
//				<object idref="siICENodeDataType#siICENodeDataBool"/> or <br/>
//				<object idref="siICENodeDataType#siICENodeDataLong"/> or <br/>
// 				<object idref="siICENodeDataType#siICENodeDataLong"/> or <br/>
// 				<object idref="siICENodeDataType#siICENodeDataFloat"/> or <br/>
// 				<object idref="siICENodeDataType#siICENodeDataVector2"/> or <br/>
// 				<object idref="siICENodeDataType#siICENodeDataVector3"/> or <br/>
// 				<object idref="siICENodeDataType#siICENodeDataVector4"/> or <br/>
// 				<object idref="siICENodeDataType#siICENodeDataQuaternion"/> or <br/>
// 				<object idref="siICENodeDataType#siICENodeDataRotation"/> or <br/>
// 				<object idref="siICENodeDataType#siICENodeDataMatrix33"/> or <br/>
// 				<object idref="siICENodeDataType#siICENodeDataMatrix44"/> or <br/>
// 				<object idref="siICENodeDataType#siICENodeDataColor4"/>
//	</type>
// 	<structure map="-1"><object idref="siICENodeStructureType#siICENodeStructureArray"/></structure>
// 	<context map="402"><object idref="siICENodeContextType#siICENodeContextAny"/></context>
// </outputport>
// </outputs>
// <seealso>
// <node idref="Concatenate"/>
// <node idref="Find"/>
// <node idref="GetSubString"/>
// <node idref="Split"/>
// <node idref="String"/>
// <node idref="StringFilePath"/>
// <node idref="StringFilePathSequence"/>
// </seealso>
// </node>

// Defines port, group and map identifiers used for registering the ICENode
enum IDs
{
	ID_String = 0,
	ID_G_100 = 100,
	ID_OUT_Result = 200,
	ID_TYPE_CNS = 400,
	ID_STRUCT_CNS,
	ID_CTXT_CNS,
	ID_UNDEF = ULONG_MAX
};

using namespace XSI;

// supported output array types
static const ULONG sStringToArrayType = 
	siICENodeDataBool		|
	siICENodeDataLong		|
	siICENodeDataFloat		|
	siICENodeDataVector2	|
	siICENodeDataVector3	|
	siICENodeDataVector4	|
	siICENodeDataQuaternion	|
	siICENodeDataRotation	|
	siICENodeDataMatrix33	|	
	siICENodeDataMatrix44	|
	siICENodeDataColor4;

CStatus RegisterStringToArray( PluginRegistrar& in_reg )
{
	ICENodeDef nodeDef;
	nodeDef = Application().GetFactory().CreateICENodeDef(L"StringToArray",L"String To Array");

	CStatus st;
	st = nodeDef.PutColor(154,188,102);
	st.AssertSucceeded( ) ;

	// Add input ports and groups.
	st = nodeDef.AddPortGroup(ID_G_100);
	st.AssertSucceeded( ) ;

	st = nodeDef.AddInputPort(	ID_String,ID_G_100,
								siICENodeDataString,siICENodeStructureSingle,siICENodeContextAny,
								L"Value",L"Value",L"",CValue(),CValue(),
								ID_UNDEF,ID_UNDEF,ID_CTXT_CNS);
	st.AssertSucceeded( ) ;

	// Add output ports.
	st = nodeDef.AddOutputPort(	ID_OUT_Result,
								sStringToArrayType,siICENodeStructureArray,siICENodeContextAny,
								L"Result",L"Result",
								ID_UNDEF,ID_UNDEF,ID_CTXT_CNS);
	st.AssertSucceeded( ) ;

	PluginItem nodeItem = in_reg.RegisterICENode(nodeDef);
	nodeItem.PutCategories(L"String");

	return CStatus::OK;
}

static LONG _AdjustElementCount( LONG in_nItems, LONG in_nArrayCount )
{
	if ( in_nArrayCount % in_nItems )
	{
		// Array count and number of expected items is wrong
		return 0;
	}
	
	in_nArrayCount /= in_nItems;
	return in_nArrayCount;
}

static LONG _GetStringTokens( const CString in_sValue, CStringArray& out_sArray )
{	
	// Split the input string with a comma or space separator
	out_sArray = in_sValue.Split( "," );						
	LONG nCount = out_sArray.GetCount();
	
	if (nCount == 1)
	{
		// no comma specified, try with the blank separator
		out_sArray = in_sValue.Split( " " );
		nCount = out_sArray.GetCount();
	}
	return nCount;
}

static LONG _StringToLong( const char* in_pszVal )
{
	// clear errno
	errno = 0;

	LONG n = atol( in_pszVal );

	if (errno == ERANGE)
    {
       Application().LogMessage( "Long value overflow condition occurred in a StringToArray node.", siWarningMsg );
       return 0;
    }

	return n;
}

SICALLBACK StringToArray_Evaluate( ICENodeContext& in_ctxt )
{
	ULONG out_portID = in_ctxt.GetEvaluatedOutputPortID( );

	switch( out_portID )
	{
		case ID_OUT_Result:
		{
			siICENodeDataType out_datatype;
			siICENodeStructureType out_struct;
			siICENodeContextType out_context;
			in_ctxt.GetPortInfo( ID_OUT_Result, out_datatype, out_struct, out_context );			
		
			CDataArrayString valueString( in_ctxt, ID_String );
			CIndexSet indexSet( in_ctxt );
			
			switch( out_datatype )
			{
				case XSI::siICENodeDataLong:
				{
					// This type has a special range pattern support
					CDataArray2D<LONG> outData( in_ctxt );	
					for ( CIndexSet::Iterator it = indexSet.Begin(); it.HasNext(); it.Next() )
					{
						// Tokenize the input value string with the comma or space separator.
						CStringArray sArray;
						LONG nCount = _GetStringTokens( valueString[it], sArray );
						
						// Expand the list by using the range delimiter (-) i.e. 1-3 expands to 1 2 3
						CLongArray elemArray;
						for (LONG i=0; i<nCount; i++)
						{
							CString s = sArray[ i ];							
							
							s.TrimLeft();
							s.TrimRight();

							// Check if we have range delimiters first							
							XSI::CBitArray rangePos(s.Length());
							for ( LONG j=0; j<(LONG)s.Length(); j++ )
							{
								if (s.GetAt(j) == '-')
								{
									rangePos.Set( j, true );
								}
							}
							
							if ( rangePos.GetTrueCount() )
							{								
								if ( rangePos.GetTrueCount() == 1 && rangePos[0] == true )
								{
									// no range but a negative number
									elemArray.Add( _StringToLong( s.GetAsciiString() ) );
								}
								else if ( rangePos.GetTrueCount() <= 3 )
								{
									// valid range patterns: 
									// 1) 1-3 
									// 2) -1-3
									// 3) -3--1
									// 4) 3--1
								
									LONG nRangePos = 0;
									if ( rangePos.GetTrueCount() == 1 )
									{
										// case 1 
										nRangePos = rangePos.GetIterator( );
										rangePos.GetNextTrueBit(nRangePos);
									}
									else if ( rangePos.GetTrueCount() == 3 )
									{
										// case 3 
										nRangePos = rangePos.GetIterator( );
										rangePos.GetNextTrueBit(nRangePos);
										rangePos.GetNextTrueBit(nRangePos);
									}
									else 
									{
										nRangePos = rangePos.GetIterator( );
										rangePos.GetNextTrueBit(nRangePos);
										
										if ( nRangePos == 0 )
										{
											// case 2
											rangePos.GetNextTrueBit(nRangePos);
										}
										else
										{
											// case 4
											;
										}
									}
									
									CString sStart = s.GetSubString( 0, nRangePos );
									CString sEnd = s.GetSubString( nRangePos+1 );
									
									LONG nStart = _StringToLong( sStart.GetAsciiString() );
									LONG nEnd = _StringToLong( sEnd.GetAsciiString() );
									
									if ( nStart <= nEnd )
									{ 
										// normal range specification
										for ( LONG j=nStart; j<nEnd+1; j++ )
										{									
											elemArray.Add( j );
										}
									}
									else
									{
										// inverted range e.g. 5-0
										for ( LONG j=nStart; j>=nEnd; j-- )
										{									
											elemArray.Add( j );
										}
									}
								}
							}
							else 
							{
								// simple element
								elemArray.Add( _StringToLong( s.GetAsciiString() ) );
							}
						}
						
						// Populate output
						nCount = elemArray.GetCount();
						CDataArray2D< LONG >::Accessor outAccessor = outData.Resize( it, nCount );		
						for (LONG i=0; i<nCount; i++)
						{
							outAccessor[i] = elemArray[i];			
						}						
					}
				}					
				break;
			
				case XSI::siICENodeDataBool:
				{
					CDataArray2D<bool> outData( in_ctxt );	
					for ( CIndexSet::Iterator it = indexSet.Begin(); it.HasNext(); it.Next() )
					{
						CStringArray sArray;
						LONG nCount = _GetStringTokens( valueString[it], sArray );

						CDataArray2D< bool >::Accessor outAccessor = outData.Resize( it, nCount );		
						for (LONG i=0; i<nCount; i++)
						{
							CString s = sArray[ i ];
							bool nVal = (bool)(_StringToLong( s.GetAsciiString() ) != 0);
							outAccessor.Set( i, nVal );			
						}
					}
				}					
				break;
			
				case XSI::siICENodeDataFloat:
				{
					CDataArray2D<float> outData( in_ctxt );	
					for ( CIndexSet::Iterator it = indexSet.Begin(); it.HasNext(); it.Next() )
					{
						CStringArray sArray;
						LONG nCount = _GetStringTokens( valueString[it], sArray );
						
						CDataArray2D< float >::Accessor outAccessor = outData.Resize( it, nCount );		
						for (LONG i=0; i<nCount; i++)
						{
							CString s = sArray[ i ];
							float nVal = (float)atof( s.GetAsciiString() );			
							outAccessor[i] = nVal;			
						}
					}
				}					
				break;

				case XSI::siICENodeDataVector2:
				{
					CDataArray2D<MATH::CVector2f> outData( in_ctxt );	
					for ( CIndexSet::Iterator it = indexSet.Begin(); it.HasNext(); it.Next() )
					{
						CStringArray sArray;
						LONG nCount = _GetStringTokens( valueString[it], sArray );
						
						LONG nItems = 2;
						nCount = _AdjustElementCount( nItems, nCount );						
						CDataArray2D< MATH::CVector2f >::Accessor outAccessor = outData.Resize( it, nCount );		
						for (LONG i=0; i<nCount; i++ )
						{
							CString s1 = sArray[ i*nItems ];
							CString s2 = sArray[ (i*nItems)+1 ];
										
							float x = (float)atof( s1.GetAsciiString() );			
							float y = (float)atof( s2.GetAsciiString() );			
							outAccessor[i] = MATH::CVector2f( x, y );
						}
					}
				}					
				break;

				case XSI::siICENodeDataVector3:
				{
					CDataArray2D<MATH::CVector3f> outData( in_ctxt );	
					for ( CIndexSet::Iterator it = indexSet.Begin(); it.HasNext(); it.Next() )
					{
						CStringArray sArray;
						LONG nCount = _GetStringTokens( valueString[it], sArray );
						
						LONG nItems = 3;
						nCount = _AdjustElementCount( nItems, nCount );
						CDataArray2D< MATH::CVector3f >::Accessor outAccessor = outData.Resize( it, nCount );		
						for (LONG i=0; i<nCount; i++ )
						{
							CString s1 = sArray[ i*nItems ];
							CString s2 = sArray[ (i*nItems)+1 ];
							CString s3 = sArray[ (i*nItems)+2 ];
										
							float x = (float)atof( s1.GetAsciiString() );			
							float y = (float)atof( s2.GetAsciiString() );			
							float z = (float)atof( s3.GetAsciiString() );			
							outAccessor[i] = MATH::CVector3f( x, y, z );
						}
					}
				}					
				break;

				case XSI::siICENodeDataVector4:
				{
					CDataArray2D<MATH::CVector4f> outData( in_ctxt );	
					for ( CIndexSet::Iterator it = indexSet.Begin(); it.HasNext(); it.Next() )
					{
						CStringArray sArray;
						LONG nCount = _GetStringTokens( valueString[it], sArray );
						
						LONG nItems = 4;
						nCount = _AdjustElementCount( nItems, nCount );
						CDataArray2D< MATH::CVector4f >::Accessor outAccessor = outData.Resize( it, nCount );		
						for (LONG i=0; i<nCount; i++ )
						{
							CString s1 = sArray[ i*nItems ];
							CString s2 = sArray[ (i*nItems)+1 ];
							CString s3 = sArray[ (i*nItems)+2 ];
							CString s4 = sArray[ (i*nItems)+3 ];
										
							float x = (float)atof( s1.GetAsciiString() );			
							float y = (float)atof( s2.GetAsciiString() );			
							float z = (float)atof( s3.GetAsciiString() );			
							float w = (float)atof( s4.GetAsciiString() );			
							outAccessor[i] = MATH::CVector4f( x, y, z, w );
						}
					}
				}					
				break;

				case XSI::siICENodeDataColor4:
				{
					CDataArray2D<MATH::CColor4f> outData( in_ctxt );	
					for ( CIndexSet::Iterator it = indexSet.Begin(); it.HasNext(); it.Next() )
					{
						CStringArray sArray;
						LONG nCount = _GetStringTokens( valueString[it], sArray );
						
						LONG nItems = 4;
						nCount = _AdjustElementCount( nItems, nCount );
						CDataArray2D< MATH::CColor4f >::Accessor outAccessor = outData.Resize( it, nCount );		
						for (LONG i=0; i<nCount; i++ )
						{
							CString s1 = sArray[ i*nItems ];
							CString s2 = sArray[ (i*nItems)+1 ];
							CString s3 = sArray[ (i*nItems)+2 ];
							CString s4 = sArray[ (i*nItems)+3 ];
										
							float r = (float)atof( s1.GetAsciiString() );			
							float g = (float)atof( s2.GetAsciiString() );			
							float b = (float)atof( s3.GetAsciiString() );			
							float a = (float)atof( s4.GetAsciiString() );			

							outAccessor[i] = MATH::CColor4f( r, g, b, a );
						}
					}
				}					
				break;

				case XSI::siICENodeDataQuaternion:
				{
					CDataArray2D<MATH::CQuaternionf> outData( in_ctxt );	
					for ( CIndexSet::Iterator it = indexSet.Begin(); it.HasNext(); it.Next() )
					{
						CStringArray sArray;
						LONG nCount = _GetStringTokens( valueString[it], sArray );
						
						LONG nItems = 4;
						nCount = _AdjustElementCount( nItems, nCount );
						CDataArray2D< MATH::CQuaternionf >::Accessor outAccessor = outData.Resize( it, nCount );		
						for (LONG i=0; i<nCount; i++ )
						{
							CString s1 = sArray[ i*nItems ];
							CString s2 = sArray[ (i*nItems)+1 ];
							CString s3 = sArray[ (i*nItems)+2 ];
							CString s4 = sArray[ (i*nItems)+3 ];
										
							float w = (float)atof( s1.GetAsciiString() );			
							float x = (float)atof( s2.GetAsciiString() );			
							float y = (float)atof( s3.GetAsciiString() );			
							float z = (float)atof( s4.GetAsciiString() );			
							outAccessor[i] = MATH::CQuaternionf( w, x, y, z );
						}						
					}
				}					
				break;

				case XSI::siICENodeDataRotation:
				{
					CDataArray2D<MATH::CRotationf> outData( in_ctxt );	
					for ( CIndexSet::Iterator it = indexSet.Begin(); it.HasNext(); it.Next() )
					{
						CStringArray sArray;
						LONG nCount = _GetStringTokens( valueString[it], sArray );
						
						LONG nItems = 3;
						nCount = _AdjustElementCount( nItems, nCount );
						CDataArray2D< MATH::CRotationf >::Accessor outAccessor = outData.Resize( it, nCount );		
						for (LONG i=0; i<nCount; i++ )
						{
							CString s1 = sArray[ i*nItems ];
							CString s2 = sArray[ (i*nItems)+1 ];
							CString s3 = sArray[ (i*nItems)+2 ];
										
							float x = (float)atof( s1.GetAsciiString() );			
							float y = (float)atof( s2.GetAsciiString() );			
							float z = (float)atof( s3.GetAsciiString() );			

							// Rotation order is siXYZ (by default)
							outAccessor[i] = MATH::CRotationf( x, y, z );
						}						
					}
				}					
				break;

				case XSI::siICENodeDataMatrix33:
				{
					CDataArray2D<MATH::CMatrix3f> outData( in_ctxt );	
					for ( CIndexSet::Iterator it = indexSet.Begin(); it.HasNext(); it.Next() )
					{
						CStringArray sArray;
						LONG nCount = _GetStringTokens( valueString[it], sArray );
						
						LONG nItems = 9;
						nCount = _AdjustElementCount( nItems, nCount );
						CDataArray2D< MATH::CMatrix3f >::Accessor outAccessor = outData.Resize( it, nCount );		
						for (LONG i=0; i<nCount; i++ )
						{
							CString s1 = sArray[ i*nItems ];
							CString s2 = sArray[ (i*nItems)+1 ];
							CString s3 = sArray[ (i*nItems)+2 ];
							CString s4 = sArray[ (i*nItems)+3 ];
							CString s5 = sArray[ (i*nItems)+4 ];
							CString s6 = sArray[ (i*nItems)+5 ];
							CString s7 = sArray[ (i*nItems)+6 ];
							CString s8 = sArray[ (i*nItems)+7 ];
							CString s9 = sArray[ (i*nItems)+8 ];
										
							float m00 = (float)atof( s1.GetAsciiString() );			
							float m01 = (float)atof( s2.GetAsciiString() );			
							float m02 = (float)atof( s3.GetAsciiString() );			
							float m10 = (float)atof( s4.GetAsciiString() );			
							float m11 = (float)atof( s5.GetAsciiString() );			
							float m12 = (float)atof( s6.GetAsciiString() );			
							float m20 = (float)atof( s7.GetAsciiString() );			
							float m21 = (float)atof( s8.GetAsciiString() );			
							float m22 = (float)atof( s9.GetAsciiString() );			

							outAccessor[i] = MATH::CMatrix3f( m00, m01, m02,  m10, m11, m12,  m20, m21, m22 );
						}										
					}
				}					
				break;

				case XSI::siICENodeDataMatrix44:
				{
					CDataArray2D<MATH::CMatrix4f> outData( in_ctxt );	
					for ( CIndexSet::Iterator it = indexSet.Begin(); it.HasNext(); it.Next() )
					{
						CStringArray sArray;
						LONG nCount = _GetStringTokens( valueString[it], sArray );
						
						LONG nItems = 16;
						nCount = _AdjustElementCount( nItems, nCount );
						CDataArray2D< MATH::CMatrix4f >::Accessor outAccessor = outData.Resize( it, nCount );		
						for (LONG i=0; i<nCount; i++ )
						{
							CString s1 = sArray[ i*nItems ];
							CString s2 = sArray[ (i*nItems)+1 ];
							CString s3 = sArray[ (i*nItems)+2 ];
							CString s4 = sArray[ (i*nItems)+3 ];
							CString s5 = sArray[ (i*nItems)+4 ];
							CString s6 = sArray[ (i*nItems)+5 ];
							CString s7 = sArray[ (i*nItems)+6 ];
							CString s8 = sArray[ (i*nItems)+7 ];
							CString s9 = sArray[ (i*nItems)+8 ];
							CString s10 = sArray[ (i*nItems)+9 ];
							CString s11 = sArray[ (i*nItems)+10 ];
							CString s12 = sArray[ (i*nItems)+11 ];
							CString s13 = sArray[ (i*nItems)+12 ];
							CString s14 = sArray[ (i*nItems)+13 ];
							CString s15 = sArray[ (i*nItems)+14 ];
							CString s16 = sArray[ (i*nItems)+15 ];
										
							float m00 = (float)atof( s1.GetAsciiString() );			
							float m01 = (float)atof( s2.GetAsciiString() );			
							float m02 = (float)atof( s3.GetAsciiString() );			
							float m03 = (float)atof( s4.GetAsciiString() );			
							float m10 = (float)atof( s5.GetAsciiString() );			
							float m11 = (float)atof( s6.GetAsciiString() );			
							float m12 = (float)atof( s7.GetAsciiString() );			
							float m13 = (float)atof( s8.GetAsciiString() );			
							float m20 = (float)atof( s9.GetAsciiString() );			
							float m21 = (float)atof( s10.GetAsciiString() );			
							float m22 = (float)atof( s11.GetAsciiString() );			
							float m23 = (float)atof( s12.GetAsciiString() );			
							float m30 = (float)atof( s13.GetAsciiString() );			
							float m31 = (float)atof( s14.GetAsciiString() );			
							float m32 = (float)atof( s15.GetAsciiString() );			
							float m33 = (float)atof( s16.GetAsciiString() );			

							outAccessor[i] = MATH::CMatrix4f(	m00, m01, m02, m03,
																m10, m11, m12, m13,
																m20, m21, m22, m23,
																m30, m31, m32, m33 );
						}
					}
				}					
				break;
			}
		}
		break;
	};

	return CStatus::OK;
}

