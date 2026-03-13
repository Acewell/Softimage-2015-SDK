#include <xsi_application.h>
#include <xsi_context.h>
#include <xsi_pluginregistrar.h>
#include <xsi_status.h>

#include <xsi_icenodecontext.h>
#include <xsi_icenodedef.h>
#include <xsi_factory.h>
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

XSI::CStatus RegisterSetAttributeValuesFromDataFile( XSI::PluginRegistrar& in_reg );

using namespace XSI; 

// Defines port, group and map identifiers used for registering the ICENode
enum IDs
{
	ID_IN_InFilePath = 0,
	ID_IN_Index,	
	ID_G_100 = 100,
	ID_OUT_OutSizeValue = 200,
	ID_OUT_OutColorValue,
	ID_TYPE_CNS = 400,
	ID_STRUCT_CNS,
	ID_CTXT_CNS,
	ID_UNDEF = ULONG_MAX
};

// Supported attributes
static CDataFileParser::TAttribPair attribPairs[] = 
{
	{ ID_OUT_OutSizeValue, "Size" },
	{ ID_OUT_OutColorValue, "Color" },
};

// The SetAttributeValuesFromDataFile node is used for setting the values of the generated particle attributes. This special node is
// required in order to set the newly generated particles since it cannot be done otherwize with the regular SetData node. That's 
// because the CloudGeneratorFromDataFile node needs to operate on a 'per element' context which is not possible to do so with SetData. 
// Therefore, SetAttributeValuesFromDataFile is designed for setting the generated particle attributes with values found in the data 
// file provided by the 'File Path Sequence' string node. The SetAttributeValuesFromDataFile node is currently implemented to support 
// the size and color attributes only but can be exapanded easily to support more attributes.
CStatus RegisterSetAttributeValuesFromDataFile( PluginRegistrar& in_reg )
{
	ICENodeDef nodeDef;
	nodeDef = Application().GetFactory().CreateICENodeDef(L"SetAttributeValuesFromDataFile",L"SetAttributeValuesFromDataFile");

	CStatus st;
	st = nodeDef.PutColor(150,180,225);
	st.AssertSucceeded( ) ;

	// Add input ports and groups.
	st = nodeDef.AddPortGroup(ID_G_100);
	st.AssertSucceeded( ) ;

	// particle ID used for indexing the data file 
	st = nodeDef.AddInputPort(ID_IN_Index,ID_G_100,siICENodeDataLong,siICENodeStructureSingle,siICENodeContextComponent0D,L"Index",L"Index",0,CValue(),CValue(),ID_UNDEF,ID_UNDEF,ID_CTXT_CNS);
	st.AssertSucceeded( ) ;

	// file path to the data file containing the attribute values
	st = nodeDef.AddInputPort(ID_IN_InFilePath,ID_G_100,siICENodeDataString,siICENodeStructureSingle,siICENodeContextSingleton,L"File Path",L"InFilePath",L"default string",CValue(),CValue(),ID_UNDEF,ID_UNDEF,ID_UNDEF);
	st.AssertSucceeded( ) ;

	// The size attribute output port
	st = nodeDef.AddOutputPort(ID_OUT_OutSizeValue,siICENodeDataFloat,siICENodeStructureSingle,siICENodeContextComponent0D,L"Size",L"OutSizeValue",ID_UNDEF,ID_UNDEF,ID_CTXT_CNS);
	st.AssertSucceeded( ) ;

	// The color attribute output port
	st = nodeDef.AddOutputPort(ID_OUT_OutColorValue,siICENodeDataColor4,siICENodeStructureSingle,siICENodeContextComponent0D,L"Color",L"OutColorValue",ID_UNDEF,ID_UNDEF,ID_CTXT_CNS);
	st.AssertSucceeded( ) ;

	PluginItem nodeItem = in_reg.RegisterICENode(nodeDef);
	nodeItem.PutCategories(L"Custom ICENode Sample");

	return CStatus::OK;
}

// Creates the data file parser 
SICALLBACK SetAttributeValuesFromDataFile_Init( CRef& in_ref )
{
	Context ctxt = in_ref;

	CDataFileParser* pParser = new CDataFileParser;
	
	// Tell the parser that the size and color attributes are required.
	pParser->AddSupportedAttributes( attribPairs, sizeof(attribPairs)/sizeof(CDataFileParser::TAttribPair) );
	
	ctxt.PutUserData( (CValue::siPtrType)pParser );
	
	return CStatus::OK;
}

// Node being deleted, time to release the parser
SICALLBACK SetAttributeValuesFromDataFile_Term( CRef& in_ref )
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

// Set the output port with the attribute value as specified to the file parser.
SICALLBACK SetAttributeValuesFromDataFile_Evaluate( ICENodeContext& in_ctxt )
{
	// The current output port being evaluated...
	ULONG out_portID = in_ctxt.GetEvaluatedOutputPortID( );
  
	switch( out_portID )
	{		
		case ID_OUT_OutSizeValue:
		case ID_OUT_OutColorValue:
		{						
			// Index to the attribute value saved in the data file
			CDataArrayLong indices( in_ctxt, ID_IN_Index );

			// Retrieve the attribute handler for setting the attribute value being evaluated
			CDataFileParser* pParser = (CDataFileParser*)(CValue::siPtrType)in_ctxt.GetUserData( );									
			CDataFileParser::AttributeHandler* pHandler = pParser->GetAttributeHandler( out_portID );

			pHandler->SetValue( in_ctxt, indices );
		}
		break;		
	};

	return CStatus::OK;
}

// Initialize the file parser with the input data file for the frame being evaluated.
SICALLBACK SetAttributeValuesFromDataFile_BeginEvaluate( ICENodeContext& in_ctxt )
{
	in_ctxt.SetAsTimeVarying();
	
	// Get the file path for this frame as provided by the File Path Sequence string node.
	CDataArrayString InFilePathData( in_ctxt, ID_IN_InFilePath );
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
	
	// Initialize the parser with the input data file. Each supported attribute will get initialized with the right data offset 
	// for this data file.
	// Note: We want the parser to support multi-threading, therefore each parser is initialized with the number of threads used 
	// for this evaluation.
	bool bRes = pParser->Init( strFilepath, in_ctxt.GetEvaluationThreadCount() );		
	if ( !bRes )
	{
		Application().LogMessage( CString("SetAttributeValuesFromDataFile_BeginEvaluate: Couldn't initialized the data parser with file ") + strFilepath );
	}
	
	return CStatus::OK;
}

// Terminates the parser but don't delete it as it will be required for subsequent evaluations
SICALLBACK SetAttributeValuesFromDataFile_EndEvaluate( ICENodeContext& in_ctxt )
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

