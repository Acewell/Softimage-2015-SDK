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
// <node id="Find" label="Find In String" introduced="9.0 (2011)" categories="String">
// <description>
// Searches a string value from the left for the first occurence of a sub-string. If found, the node returns the index of
// the sub-string in the string value. The search is case-sensitive by default and can also be started from the right.
// </description>
// <inputs>
// <portgroup id="100" instances="1">
// 	<inputport id="Value" label="Value">
// 		<description>The string to search for.</description>
// 		<type map="-1"><object idref="siICENodeDataType#siICENodeDataString"/></type>
// 		<structure map="0"><object idref="siICENodeStructureType#siICENodeStructureSingle"/></structure>
// 		<context map="0"><object idref="siICENodeContextType#siICENodeContextAny"/></context>
// 	</inputport>
// </portgroup>
// <portgroup id="100" instances="1">
// 	<inputport id="SubString" label="To Find">
// 		<description>The string to search for.</description>
// 		<type map="-1"><object idref="siICENodeDataType#siICENodeDataString"/></type>
// 		<structure map="0"><object idref="siICENodeStructureType#siICENodeStructureSingle"/></structure>
// 		<context map="0"><object idref="siICENodeContextType#siICENodeContextAny"/></context>
// 	</inputport>
// </portgroup>
// <portgroup id="100" instances="1">
// 	<inputport id="SubStringStart" label="Start">
// 		<description>Index in the string value where the search begins.</description>
// 		<type map="-1"><object idref="siICENodeDataType#siICENodeDataLong"/></type>
// 		<structure map="-1"><object idref="siICENodeStructureType#siICENodeStructureSingle"/></structure>
// 		<context map="402"><object idref="siICENodeContextType#siICENodeContextAny"/></context>
// 	</inputport>
// </portgroup>
// <portgroup id="100" instances="1">
// 	<inputport id="CaseSensitive" label="Case">
// 		<description>Set the search string comparison as case-sensitive (default) or not case-sensitive.</description>
// 		<type map="-1"><object idref="siICENodeDataType#siICENodeDataBool"/></type>
// 		<structure map="-1"><object idref="siICENodeStructureType#siICENodeStructureSingle"/></structure>
// 		<context map="402"><object idref="siICENodeContextType#siICENodeContextAny"/></context>
// 	</inputport>
// </portgroup>
// <portgroup id="100" instances="1">
// 	<inputport id="Find Sub String From Right" label="From Right">
// 		<description>Set the direction of the search from the right (default to false). When the searh starts from the right,
//		you want to make sure to set the start position to -1 if you want the search to start from the very end.</description>
// 		<type map="-1"><object idref="siICENodeDataType#siICENodeDataBool"/></type>
// 		<structure map="-1"><object idref="siICENodeStructureType#siICENodeStructureSingle"/></structure>
// 		<context map="402"><object idref="siICENodeContextType#siICENodeContextAny"/></context>
// 	</inputport>
// </portgroup>
// </inputs>
// <outputs>
// <outputport id="Result" label="Result">
// 	<description>The index in the string value where the sub-string starts.</description>
// 	<type map="-1"><object idref="siICENodeDataType#siICENodeDataString"/></type>
// 	<structure map="-1"><object idref="siICENodeStructureType#siICENodeStructureSingle"/></structure>
// 	<context map="402"><object idref="siICENodeContextType#siICENodeContextAny"/></context>
// </outputport>
// </outputs>
// <seealso>
// <node idref="Concatenate"/>
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
	ID_IN_String = 0,
	ID_IN_SubString = 1,
	ID_IN_SubStringStart = 2,
	ID_IN_CaseSensitive = 3,
	ID_IN_FindFromRight = 4,
	ID_G_100 = 100,
	ID_OUT_Result = 200,
	ID_TYPE_CNS = 400,
	ID_STRUCT_CNS,
	ID_CTXT_CNS,
	ID_UNDEF = ULONG_MAX
};

using namespace XSI;

CStatus RegisterFindString( PluginRegistrar& in_reg )
{
	ICENodeDef nodeDef;
	nodeDef = Application().GetFactory().CreateICENodeDef(L"Find",L"Find In String");

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

	st = nodeDef.AddInputPort(	ID_IN_SubString,ID_G_100,
								siICENodeDataString,siICENodeStructureSingle,siICENodeContextAny,
								L"To Find",L"SubString",L"",CValue(),CValue(),
								ID_UNDEF,ID_UNDEF,ID_CTXT_CNS);
	st.AssertSucceeded( ) ;

	st = nodeDef.AddInputPort(	ID_IN_SubStringStart,ID_G_100,
								siICENodeDataLong,siICENodeStructureSingle,siICENodeContextAny,
								L"Start",L"SubStringStart",0,0,10,
								ID_UNDEF,ID_UNDEF,ID_CTXT_CNS);
	st.AssertSucceeded( ) ;

	st = nodeDef.AddInputPort(	ID_IN_CaseSensitive,ID_G_100,
								siICENodeDataBool,siICENodeStructureSingle,siICENodeContextAny,
								L"Case",L"CaseSensitive",true,CValue(),CValue(),
								ID_UNDEF,ID_UNDEF,ID_CTXT_CNS);
	st.AssertSucceeded( ) ;

	st = nodeDef.AddInputPort(	ID_IN_FindFromRight,ID_G_100,
								siICENodeDataBool,siICENodeStructureSingle,siICENodeContextAny,
								L"From Right",L"Find Sub String From Right",false,CValue(),CValue(),
								ID_UNDEF,ID_UNDEF,ID_CTXT_CNS);
	st.AssertSucceeded( ) ;

	// Add output ports.
	st = nodeDef.AddOutputPort(	ID_OUT_Result,
								siICENodeDataLong,siICENodeStructureSingle,siICENodeContextAny,
								L"Result",L"Result",
								ID_UNDEF,ID_UNDEF,ID_CTXT_CNS);
	st.AssertSucceeded( ) ;

	PluginItem nodeItem = in_reg.RegisterICENode(nodeDef);
	nodeItem.PutCategories(L"String");

	return CStatus::OK;
}

SICALLBACK Find_Evaluate( ICENodeContext& in_ctxt )
{
	ULONG out_portID = in_ctxt.GetEvaluatedOutputPortID( );

	switch( out_portID )
	{
		case ID_OUT_Result:
		{
			CDataArrayLong outData( in_ctxt );
			CDataArrayString valueString( in_ctxt, ID_IN_String );
			CDataArrayString subString( in_ctxt, ID_IN_SubString );
			CDataArrayLong subStringStart( in_ctxt, ID_IN_SubStringStart );
			bool bFromRight = CDataArrayBool( in_ctxt, ID_IN_FindFromRight )[0];
			bool bLower = CDataArrayBool( in_ctxt, ID_IN_CaseSensitive )[0] == false;

			CIndexSet indexSet( in_ctxt );
			for ( CIndexSet::Iterator it = indexSet.Begin(); it.HasNext(); it.Next() )
			{
				CString str(valueString[it]);
				CString strSub(subString[it]);

				if ( bLower )
				{
					str.Lower();
					strSub.Lower();
				}

				if ( bFromRight )
				{
					outData[it] = str.ReverseFindString( strSub, subStringStart[it] );
				}
				else
				{
					outData[it] = str.FindString( strSub, subStringStart[it] );
				}
			}
		}
		break;
	};

	return CStatus::OK;
}

