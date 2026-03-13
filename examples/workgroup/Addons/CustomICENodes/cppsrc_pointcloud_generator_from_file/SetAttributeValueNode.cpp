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

#include "DataFileParser.h"

// Defines port, group and map identifiers used for registering the ICENode
enum IDs
{
	ID_IN_InFilePath = 0,
	ID_IN_Index = 1,	
	ID_IN_AttribName = 2,	
	ID_G_100 = 100,
	ID_OUT_OutAttribValue = 200,
	ID_TYPE_CNS = 400,
	ID_STRUCT_CNS,
	ID_CTXT_CNS,
	ID_UNDEF = ULONG_MAX
};

XSI::CStatus RegisterSetAttributeValueFromDataFile( XSI::PluginRegistrar& in_reg );

using namespace XSI; 

// SetAttributeValue node: This node is an alternative approach to SetAtributeValues which is designed to set the values of attributes by hardcoding 
// the supported attributes. The SetAttributeValue node on the other hand is more generic and allows setting a value by specifying the attribute name
// an input. This can be handy when one needs to build a graph dynamically by discovering the attribute names to set from the data file itself, in 
// this case a node instance is required for each attribute to set.
CStatus RegisterSetAttributeValueFromDataFile( PluginRegistrar& in_reg )
{
	ICENodeDef nodeDef;
	nodeDef = Application().GetFactory().CreateICENodeDef(L"SetAttributeValueFromDataFile",L"SetAttributeValueFromDataFile");

	CStatus st;
	st = nodeDef.PutColor(100,111,146);
	st.AssertSucceeded( ) ;

	// Add input ports and groups.
	st = nodeDef.AddPortGroup(ID_G_100);
	st.AssertSucceeded( ) ;

	st = nodeDef.AddInputPort(ID_IN_Index,ID_G_100,siICENodeDataLong,siICENodeStructureSingle,siICENodeContextComponent0D,L"Index",L"Index",0,CValue(),CValue(),ID_UNDEF,ID_UNDEF,ID_CTXT_CNS);
	st.AssertSucceeded( ) ;

	st = nodeDef.AddInputPort(ID_IN_InFilePath,ID_G_100,siICENodeDataString,siICENodeStructureSingle,siICENodeContextSingleton,L"File Path",L"InFilePath",L"default string",CValue(),CValue(),ID_UNDEF,ID_UNDEF,ID_UNDEF);
	st.AssertSucceeded( ) ;

	st = nodeDef.AddInputPort(ID_IN_AttribName,ID_G_100,siICENodeDataString,siICENodeStructureSingle,siICENodeContextSingleton,L"Attribute",L"AttribName",L"default string",CValue(),CValue(),ID_UNDEF,ID_UNDEF,ID_UNDEF);
	st.AssertSucceeded( ) ;

	// Add output ports.
	st = nodeDef.AddOutputPort(ID_OUT_OutAttribValue,siICENodeOutputDataAny,siICENodeStructureSingle,siICENodeContextComponent0D,L"Value",L"OutAttribValue",ID_UNDEF,ID_UNDEF,ID_CTXT_CNS);
	st.AssertSucceeded( ) ;

	PluginItem nodeItem = in_reg.RegisterICENode(nodeDef);
	nodeItem.PutCategories(L"Custom ICENode Sample");

	return CStatus::OK;
}

// Creates the data file parser 
SICALLBACK SetAttributeValueFromDataFile_Init( CRef& in_ref )
{
	Context ctxt = in_ref;

	CDataFileParser* pParser = new CDataFileParser;		
	ctxt.PutUserData( (CValue::siPtrType)pParser );
	
	return CStatus::OK;
}

// Node being deleted, time to release the parser
SICALLBACK SetAttributeValueFromDataFile_Term( CRef& in_ref )
{
	Context ctxt = in_ref;
	CValue userData = ctxt.GetUserData( );
	if ( userData.IsEmpty() )
	{
		return CStatus::OK;
	}

	CDataFileParser* pParser = (CDataFileParser*)(CValue::siPtrType)ctxt.GetUserData( );
	if ( pParser )
	{
		delete pParser;
	}

	// Clear user data; 
	ctxt.PutUserData( CValue() );
	
	return CStatus::OK;
}

SICALLBACK SetAttributeValueFromDataFile_Evaluate( ICENodeContext& in_ctxt )
{
	// The current output port being evaluated...
	ULONG out_portID = in_ctxt.GetEvaluatedOutputPortID( );
  
	switch( out_portID )
	{		
		case ID_OUT_OutAttribValue: 
		{						
			// Index to the attribute value saved in the data file
			CDataArrayLong indices( in_ctxt, ID_IN_Index );

			// Retrieve the attribute handler for setting the attribute value being evaluated
			CDataFileParser* pParser = (CDataFileParser*)(CValue::siPtrType)in_ctxt.GetUserData( );									
			CDataFileParser::AttributeHandler* pHandler = pParser->GetAttributeHandler( );
			pHandler->SetValue( in_ctxt, indices );
		}
		break;		
	};

	return CStatus::OK;
}

// Supported attribute struct required by the parser
static CDataFileParser::TAttribPair attribPair;

SICALLBACK SetAttributeValueFromDataFile_BeginEvaluate( ICENodeContext& in_ctxt )
{
	in_ctxt.SetAsTimeVarying();
	
	// Get the input data buffers for each port
	CDataArrayString InFilePathData( in_ctxt, ID_IN_InFilePath );
	CDataArrayString InAttribName( in_ctxt, ID_IN_AttribName );

	CString strFilepath = InFilePathData[0];
	
	Application().LogMessage( CString("Opening data file: ") + strFilepath, siVerboseMsg );
	
	CValue userData = in_ctxt.GetUserData( );
	if ( userData.IsEmpty() )
	{
		// something's wrong
		return CStatus::False;
	}

	CDataFileParser* pParser = (CDataFileParser*)(CValue::siPtrType)in_ctxt.GetUserData( );
	if ( !pParser )
	{
		// something's wrong
		return CStatus::False;
	}
	
	// Initialize the parser with the input data file and an attribute name. The supported attribute will bet match with an attribute handler which 
	// will get initialized with the right data offset in this data file.
	// Note: We want the parser to support multi-threading, therefore each parser is initialized with the number of threads used 
	// for this evaluation.
	CString strAttribName = InAttribName[0];
	strcpy( attribPair.szName, strAttribName.GetAsciiString() );
	attribPair.nPortID = ID_OUT_OutAttribValue;
	bool bRes = pParser->Init( strFilepath, attribPair, in_ctxt.GetEvaluationThreadCount() );		
	if ( !bRes )
	{
		Application().LogMessage( CString("SetAttributeValueFromDataFile_BeginEvaluate: Couldn't initialize the data parser with file ") + strFilepath );
	}
	
	return CStatus::OK;
}

// Terminates the parser but don't delete it as it will be required for subsequent evaluations
SICALLBACK SetAttributeValueFromDataFile_EndEvaluate( ICENodeContext& in_ctxt )
{
	// Close the file parser streams
	CValue userData = in_ctxt.GetUserData( );
	if ( userData.IsEmpty() )
	{
		return CStatus::OK;
	}

	CDataFileParser* pParser = (CDataFileParser*)(CValue::siPtrType)in_ctxt.GetUserData( );
	if ( pParser )
	{
		pParser->Term( );
	}

	return CStatus::OK;
}