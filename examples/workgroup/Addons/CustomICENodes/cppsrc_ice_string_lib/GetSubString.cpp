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
// <node id="GetSubString" label="Get Sub String" introduced="9.0 (2011)" categories="String">
// <description>
// Returns a sub-string from a string value beginning at a specified character position.
// returns the position of the sub-string. The search is case-sensitive by default and can also be specified in the
// backward direction.
// </description>
// <inputs>
// <portgroup id="100" instances="1">
// 	<inputport id="Value" label="Value">
// 		<description>The string to extract the sub-string position from.</description>
// 		<type map="-1"><object idref="siICENodeDataType#siICENodeDataString"/></type>
// 		<structure map="0"><object idref="siICENodeStructureType#siICENodeStructureSingle"/></structure>
// 		<context map="0"><object idref="siICENodeContextType#siICENodeContextAny"/></context>
// 	</inputport>
// </portgroup>
// <portgroup id="100" instances="1">
// 	<inputport id="SubStringStart" label="Start">
// 		<description>Index in the string value where to extract the sub-string.</description>
// 		<type map="-1"><object idref="siICENodeDataType#siICENodeDataLong"/></type>
// 		<structure map="-1"><object idref="siICENodeStructureType#siICENodeStructureSingle"/></structure>
// 		<context map="402"><object idref="siICENodeContextType#siICENodeContextAny"/></context>
// 	</inputport>
// </portgroup>
// <portgroup id="100" instances="1">
// 	<inputport id="CharacterCount" label="N Char Copy">
// 		<description>Number of chracters to extract.</description>
// 		<type map="-1"><object idref="siICENodeDataType#siICENodeDataBool"/></type>
// 		<structure map="-1"><object idref="siICENodeStructureType#siICENodeStructureSingle"/></structure>
// 		<context map="402"><object idref="siICENodeContextType#siICENodeContextAny"/></context>
// 	</inputport>
// </portgroup>
// </inputs>
// <outputs>
// <outputport id="Result" label="Result">
// 	<description>The sub-string extracted from the input string value.</description>
// 	<type map="-1"><object idref="siICENodeDataType#siICENodeDataString"/></type>
// 	<structure map="-1"><object idref="siICENodeStructureType#siICENodeStructureAny"/></structure>
// 	<context map="402"><object idref="siICENodeContextType#siICENodeContextAny"/></context>
// </outputport>
// </outputs>
// <seealso>
// <node idref="Concatenate"/>
// <node idref="Find"/>
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
	ID_IN_String = 0,
	ID_IN_SubStringStart = 1,
	ID_IN_CharacterCount = 2,
	ID_G_100 = 100,
	ID_OUT_Result = 200,
	ID_TYPE_CNS = 400,
	ID_STRUCT_CNS,
	ID_CTXT_CNS,
	ID_UNDEF = ULONG_MAX
};

using namespace XSI;

CStatus RegisterGetSubString( PluginRegistrar& in_reg )
{
	ICENodeDef nodeDef;
	nodeDef = Application().GetFactory().CreateICENodeDef(L"GetSubString",L"Get Sub String");

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

	st = nodeDef.AddInputPort(	ID_IN_SubStringStart,ID_G_100,
								siICENodeDataLong,siICENodeStructureSingle,siICENodeContextAny,
								L"Start",L"SubStringStart",0,CValue(),CValue(),
								ID_UNDEF,ID_UNDEF,ID_CTXT_CNS);
	st.AssertSucceeded( ) ;

	st = nodeDef.AddInputPort(	ID_IN_CharacterCount,ID_G_100,
								siICENodeDataLong,siICENodeStructureSingle,siICENodeContextAny,
								L"N Char Copy",L"CharacterCount",-1 /*all*/,CValue(),CValue(),
								ID_UNDEF,ID_UNDEF,ID_CTXT_CNS);
	st.AssertSucceeded( ) ;

	// Add output ports.
	st = nodeDef.AddOutputPort(	ID_OUT_Result,
								siICENodeDataString,siICENodeStructureSingle,siICENodeContextAny,
								L"Result",L"Result",
								ID_UNDEF,ID_UNDEF,ID_CTXT_CNS);
	st.AssertSucceeded( ) ;

	PluginItem nodeItem = in_reg.RegisterICENode(nodeDef);
	nodeItem.PutCategories(L"String");

	return CStatus::OK;
}

SICALLBACK GetSubString_Evaluate( ICENodeContext& in_ctxt )
{
	ULONG out_portID = in_ctxt.GetEvaluatedOutputPortID( );

	switch( out_portID )
	{
		case ID_OUT_Result:
		{
			CDataArrayString outData( in_ctxt );

			CDataArrayString valueString( in_ctxt, ID_IN_String );
			CDataArrayLong subStringStart( in_ctxt, ID_IN_SubStringStart );
			CDataArrayLong characterCount( in_ctxt, ID_IN_CharacterCount );

			CIndexSet indexSet( in_ctxt );
			for ( CIndexSet::Iterator it = indexSet.Begin(); it.HasNext(); it.Next() )
			{
				CString strSubString = valueString[it].GetSubString( subStringStart[it], characterCount[it] );
				outData.Resize( it, strSubString.Length() );
				outData.SetData( it, strSubString );
			}
		}
		break;
	};

	return CStatus::OK;
}

