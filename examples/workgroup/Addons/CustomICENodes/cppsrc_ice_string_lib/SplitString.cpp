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

/////////////////////////////////// Softimage Documentation //////////////////////////////////////////////////////
// <node id="Split" label="Split String" introduced="9.0 (2011)" categories="String">
// <description>
// Parses the input string value and returns an array of sub-strings delimited by a given string.
// </description>
// <inputs>
// <portgroup id="100" instances="1">
// 	<inputport id="Value" label="Value">
// 		<description>The string to split.</description>
// 		<type map="-1"><object idref="siICENodeDataType#siICENodeDataString"/></type>
// 		<structure map="-1"><object idref="siICENodeStructureType#siICENodeStructureSingle"/></structure>
// 		<context map="402"><object idref="siICENodeContextType#siICENodeContextAny"/></context>
// 	</inputport>
// </portgroup>
// <portgroup id="100" instaces="1">
// 	<inputport id="StringDelimiter" label="Delimiter">
// 		<description>The string delimiter.</description>
// 		<type map="-1"><object idref="siICENodeDataType#siICENodeDataString"/></type>
// 		<structure map="-1"><object idref="siICENodeStructureType#siICENodeStructureSingle"/></structure>
// 		<context map="402"><object idref="siICENodeContextType#siICENodeContextAny"/></context>
// 	</inputport>
// </portgroup>
// </inputs>
// <outputs>
// <outputport id="Result" label="Result">
// 	<description>An array of string values.</description>
// 	<type map="-1"><object idref="siICENodeDataType#siICENodeDataString"/></type>
// 	<structure map="-1"><object idref="siICENodeStructureType#siICENodeStructureArray"/></structure>
// 	<context map="402"><object idref="siICENodeContextType#siICENodeContextAny"/></context>
// </outputport>
// </outputs>
// <seealso>
// <node idref="Concatenate"/>
// <node idref="Find"/>
// <node idref="GetSubString"/>
// <node idref="String"/>
// <node idref="StringFilePath"/>
// <node idref="StringFilePathSequence"/>
// <node idref="StringToArray"/>
// </seealso>
// </node>

// Defines port, group and map identifiers used for registering the ICENode
enum IDs
{
	ID_IN_String = 0,
	ID_IN_StringDelimiter = 1,
	ID_G_100 = 100,
	ID_OUT_Result = 200,
	ID_TYPE_CNS = 400,
	ID_STRUCT_CNS,
	ID_CTXT_CNS,
	ID_UNDEF = ULONG_MAX
};

using namespace XSI;

CStatus RegisterSplitString( PluginRegistrar& in_reg )
{
	ICENodeDef nodeDef;
	nodeDef = Application().GetFactory().CreateICENodeDef(L"Split",L"Split String");

	CStatus st;
	st = nodeDef.PutColor(154,188,102);
	st.AssertSucceeded( ) ;

	// Add input ports and groups.
	st = nodeDef.AddPortGroup(ID_G_100);
	st.AssertSucceeded( ) ;

	st = nodeDef.AddInputPort(	ID_IN_String,ID_G_100,
								siICENodeDataString,siICENodeStructureSingle,siICENodeContextAny,
								L"Value",L"Value",L"",CValue(),CValue(),
								ID_UNDEF,ID_UNDEF,ID_CTXT_CNS);
	st.AssertSucceeded( ) ;

	st = nodeDef.AddInputPort(	ID_IN_StringDelimiter,ID_G_100,
								siICENodeDataString,siICENodeStructureSingle,siICENodeContextAny,
								L"Delimiter",L"StringDelimiter",L"",CValue(),CValue(),
								ID_UNDEF,ID_UNDEF,ID_CTXT_CNS);
	st.AssertSucceeded( ) ;

	// Add output ports.
	st = nodeDef.AddOutputPort(	ID_OUT_Result,
								siICENodeDataString,siICENodeStructureArray,siICENodeContextAny,
								L"Result",L"Result",
								ID_UNDEF,ID_UNDEF,ID_CTXT_CNS);
	st.AssertSucceeded( ) ;

	PluginItem nodeItem = in_reg.RegisterICENode(nodeDef);
	nodeItem.PutCategories(L"String");

	return CStatus::OK;
}

SICALLBACK Split_Evaluate( ICENodeContext& in_ctxt )
{
	ULONG out_portID = in_ctxt.GetEvaluatedOutputPortID( );

	switch( out_portID )
	{
		case ID_OUT_Result:
		{
			CDataArray2DString outData( in_ctxt );

			CDataArrayString valueString( in_ctxt, ID_IN_String );
			CDataArrayString stringDelimiter( in_ctxt, ID_IN_StringDelimiter );

			CIndexSet indexSet( in_ctxt );
			for ( CIndexSet::Iterator it = indexSet.Begin(); it.HasNext(); it.Next() )
			{
				CStringArray strArray = valueString[it].Split( stringDelimiter[it] );

				CDataArray2DString::Accessor splitAcc = outData.Resize( it, strArray.GetCount() );
				for ( LONG i=0; i<strArray.GetCount(); i++ )
				{
					splitAcc.SetData( i, strArray[i] );
				}
			}
		}
		break;
	};

	return CStatus::OK;
}

