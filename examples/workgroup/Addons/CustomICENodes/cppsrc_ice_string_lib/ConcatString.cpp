// ICE String Library Plugin

#include <xsi_application.h>
#include <xsi_context.h>
#include <xsi_pluginregistrar.h>
#include <xsi_status.h>

#include <xsi_icenodecontext.h>
#include <xsi_icenodedef.h>
#include <xsi_command.h>
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
#include <xsi_shape.h>
#include <xsi_icegeometry.h>
#include <xsi_iceportstate.h>
#include <xsi_indexset.h>
#include <xsi_dataarray.h>
#include <xsi_dataarray2D.h>

#include <string.h>

/////////////////////////////////// Softimage Documentation //////////////////////////////////////////////////////
// <node id="Concatenate" label="Concatenate String" introduced="9.0 (2011)" categories="String">
// <description>
// Node to concatenate multiple string values. The input value can be specified as a single value or array of values.
// </description>
// <inputs>
// <portgroup id="100" instances="1..N">
// 	<inputport id="Value" label="Value">
// 		<description>The string to concatenate.</description>
// 		<type map="-1"><object idref="siICENodeDataType#siICENodeDataString"/></type>
// 		<structure map="401"><object idref="siICENodeStructureType#siICENodeStructureAny"/></structure>
// 		<context map="402"><object idref="siICENodeContextType#siICENodeContextAny"/></context>
// 	</inputport>
// </portgroup>
// </inputs>
// <outputs>
// <outputport id="Result" label="Result">
// 	<description>The new string built from the input values.</description>
// 	<type map="-1"><object idref="siICENodeDataType#siICENodeDataString"/></type>
// 	<structure map="401"><object idref="siICENodeStructureType#siICENodeStructureAny"/></structure>
// 	<context map="402"><object idref="siICENodeContextType#siICENodeContextAny"/></context>
// </outputport>
// </outputs>
// <seealso>
// <node idref="Find"/>
// <node idref="GetSubString"/>
// <node idref="Split"/>
// <node idref="String"/>
// <node idref="StringFilePath"/>
// <node idref="StringFilePathSequence"/>
// <node idref="StringToArray"/>
// </seealso>
// </node>

// Defines port, group and map identifiers used for registering the ICENode
enum IDs
{
	ID_IN_Value = 0,
	ID_G_100 = 100,
	ID_OUT_Result = 200,
	ID_TYPE_CNS = 400,
	ID_STRUCT_CNS,
	ID_CTXT_CNS,
	ID_UNDEF = ULONG_MAX
};

using namespace XSI;

CStatus RegisterConcatString( PluginRegistrar& in_reg )
{
	ICENodeDef nodeDef;
	nodeDef = Application().GetFactory().CreateICENodeDef(L"Concatenate",L"Concatenate String");

	CStatus st;
	st = nodeDef.PutColor(154,188,102);
	st.AssertSucceeded( ) ;

	// Add input ports and groups.
	st = nodeDef.AddPortGroup(ID_G_100, 1, ULONG_MAX);
	st.AssertSucceeded( ) ;

	st = nodeDef.AddInputPort(	ID_IN_Value,ID_G_100,
								siICENodeDataString,siICENodeStructureAny,siICENodeContextAny,
								L"Value",L"Value",L"",CValue(),CValue(),
								ID_UNDEF,ID_STRUCT_CNS,ID_CTXT_CNS);
	st.AssertSucceeded( ) ;

	// Add output ports.
	st = nodeDef.AddOutputPort(	ID_OUT_Result,
								siICENodeDataString,siICENodeStructureAny,siICENodeContextAny,
								L"Result",L"Result",
								ID_UNDEF,ID_STRUCT_CNS,ID_CTXT_CNS);
	st.AssertSucceeded( ) ;

	PluginItem nodeItem = in_reg.RegisterICENode(nodeDef);
	nodeItem.PutCategories(L"String");

	return CStatus::OK;
}

SICALLBACK Concatenate_Evaluate( ICENodeContext& in_ctxt )
{
	ULONG out_portID = in_ctxt.GetEvaluatedOutputPortID( );

	switch( out_portID )
	{
		case ID_OUT_Result:
		{
			XSI::siICENodeDataType dataType;
			XSI::siICENodeStructureType dataStruct;
			XSI::siICENodeContextType dataContext;
			in_ctxt.GetPortInfo( ID_OUT_Result, dataType, dataStruct, dataContext );

			if ( dataStruct == siICENodeStructureSingle )
			{
				CDataArrayString outData( in_ctxt );

				ULONG nInstCount;
				in_ctxt.GetGroupInstanceCount(ID_G_100, nInstCount);

				// Recycle output buffer to get first input value
				outData.CopyFrom( ID_IN_Value, 0 );

				CIndexSet indexSet( in_ctxt );
				for ( CIndexSet::Iterator it = indexSet.Begin(); it.HasNext(); it.Next() )
				{
					for (ULONG i=1; i<nInstCount; i++)
					{
						CDataArrayString valueString( in_ctxt, ID_IN_Value, i);

						wchar_t* pszVal = NULL;
						ULONG nValSize;
						valueString.GetData( it, &pszVal, nValSize );

						if ( nValSize )
						{
							wchar_t* pszRes = NULL;
							ULONG nResSize;
							outData.GetData( it, &pszRes, nResSize );

							pszRes = outData.Resize( it, nResSize+nValSize );

							memcpy( pszRes+nResSize, pszVal, nValSize * sizeof(wchar_t) );
						}
					}
				}
			}
			else if ( dataStruct == siICENodeStructureArray )
			{
				CDataArray2DString outData( in_ctxt );

				ULONG nInstCount;
				in_ctxt.GetGroupInstanceCount(ID_G_100, nInstCount);

				// Compute number of strings for output array
				ULONG nMinValueSize = ULONG_MAX;
				for (ULONG nInstID=0; nInstID<nInstCount; nInstID++)
				{
					CDataArray2DString valueArray( in_ctxt, ID_IN_Value, nInstID);
					CDataArray2DString::Accessor valueAcc = valueArray[ nInstID ];

					if ( valueAcc.GetCount() < nMinValueSize )
					{
						nMinValueSize = valueAcc.GetCount();
					}
				}

				CIndexSet indexSet( in_ctxt );
				for ( CIndexSet::Iterator it = indexSet.Begin(); it.HasNext(); it.Next() )
				{
					CDataArray2DString::Accessor resultAcc = outData.Resize( it, nMinValueSize );

					for (ULONG i=0; i<nInstCount; i++)
					{
						CDataArray2DString valueArray( in_ctxt, ID_IN_Value, i);
						CDataArray2DString::Accessor valueAcc = valueArray[ it ];

						for ( ULONG j=0; j<nMinValueSize; j++ )
						{
							wchar_t* pszSubVal = NULL;
							ULONG nSubValSize;
							valueAcc.GetData( j, &pszSubVal, nSubValSize );

							if ( nSubValSize )
							{
								wchar_t* pszSubResult = NULL;
								ULONG nResSubArraySize;
								resultAcc.GetData( j, &pszSubResult, nResSubArraySize );
								pszSubResult = resultAcc.Resize( j, nResSubArraySize + nSubValSize );

								memcpy( pszSubResult+nResSubArraySize, pszSubVal, nSubValSize * sizeof(wchar_t) );
							}
						}
					}
				}
			}
		}
		break;
	};

	return CStatus::OK;
}

