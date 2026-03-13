//////////////////////////////////////////////////////////////////////////////
//
// This file implements the VertexColorMixer example plug-in for Softimage in C++ using
// the CPP API SDK feature.
//
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   
//////////////////////////////////////////////////////////////////////////////

#include <sicppsdk.h>
#include <xsi_decl.h>
#include <xsi_value.h>
#include <xsi_customoperator.h>
#include <xsi_clusterproperty.h>
#include <xsi_outputport.h>
#include <xsi_inputport.h>
#include <xsi_operatorcontext.h>
#include <xsi_pluginregistrar.h>
#include <xsi_command.h>
#include <xsi_argument.h>
#include <xsi_application.h>
#include <xsi_factory.h>

// This example demonstrates the use of assert to 
// aid in the quick development and debugging of 
// C++ API code.  At strategic places in the debug
// build the "assumptions" in the code are tested
#include <assert.h>

using namespace XSI;

//////////////////////////////////////////////////////////////////////////////
// CVertexColorMixer operator declaration
// This demonstrates how to implement an instance based operator.  There
// will be a separate instance of this class for each instance of the operator.
//
// We create an instance of the class in the Init() function and put the pointer
// to the instance into the updatecontext userdata. This can then be retrieve
// in the update() and term() functions.
//
// This approach is most useful if each instance of the data needs its own 
// transitive or cached member data.
//////////////////////////////////////////////////////////////////////////////
class CVertexColorMixer
{
public:
	CVertexColorMixer() {}
	~CVertexColorMixer() {}

	CStatus Update(OperatorContext&);
protected:
	CStatus Mix(ClusterProperty&,const CRefArray&);
};


//////////////////////////////////////////////////////////////////////////////
// DLL Entry Points
//////////////////////////////////////////////////////////////////////////////

XSIPLUGINCALLBACK CStatus XSILoadPlugin( PluginRegistrar& in_reg )
{
	in_reg.PutAuthor(L"Softimage");
	in_reg.PutName(L"Vertex Color Mixer - SDK Example");
	in_reg.PutVersion(2,0);

	in_reg.RegisterOperator(L"VertexColorMixer");
	in_reg.RegisterCommand(L"ApplyVertexColorMixer");
	//RegistrationInsertionPoint - do not remove this line

	return CStatus::OK;
}

// A Custom Command, ApplyVertexColorMixer, is provided to take
// care of creation of the operator.  This is necessary because
// the AddCustomOp command does not support advanced operators with 
// multiple groups.  It would also be possible to create the operator
// from within a menu callback or even in scripting, but it is most
// versatile to offer a specific custom command that does the job
//
// The command creates the operator and connects it to an output cluster
// property and to the initial input cluster properties.  All the cluster
// properties are expected to exist.  This was done for simplicity, 
// but the command could be enhanced to support automatic creation 
// of the output cluster property, use of PickElement command to pick 
// input cluster properties and use of argument handlers to process 
// string input or the current selection.

XSIPLUGINCALLBACK CStatus ApplyVertexColorMixer_Init( CRef& in_ctxt )
{
	Context ctxt( in_ctxt );
	Command oCmd;
	oCmd = ctxt.GetSource();
	oCmd.PutDescription(L"Create an Operator that blends vertex color properties");
	oCmd.EnableReturnValue(true);

	ArgumentArray oArgs;
	oArgs = oCmd.GetArguments();
	
	// Three mandatory arguments
	oArgs.Add(L"OpName");
	oArgs.Add(L"OutProp");
	oArgs.Add(L"InProps");

	return CStatus::OK;
}

XSIPLUGINCALLBACK CStatus ApplyVertexColorMixer_Execute( CRef& in_ctxt )
{
	Context ctxt( in_ctxt );
	CValueArray args = ctxt.GetAttribute(L"Arguments");
	assert( args.GetCount() == 3 ) ;

	CString opName = args[0] ;

	CRef refoutProp = args[1];

	if (!refoutProp.IsValid() )
	{
		// This wasn't a valid Softimage object, maybe a string
		return CStatus::InvalidArgument ;
	}

	ClusterProperty outProp( refoutProp ) ;

	if (!outProp.IsValid() || outProp.GetType() != L"vertexcolor" )
	{
		return CStatus::InvalidArgument ;
	}

	CValueArray inProps = args[2];

	if ( inProps.GetCount() < 1 )
	{
		// Input argument, we expect at least 1 input to mix
		return CStatus::InvalidArgument ;
	}

	Application().LogMessage(L"ApplyVertexColorMixer_Execute called");

	CustomOperator newOp = Application().GetFactory().CreateObject( L"VertexColorMixer" ) ;
	assert( newOp.IsValid() ) ; 

	if ( !opName.IsEmpty() )
		newOp.PutName( opName ) ;

	// Define the output port in its own group
	newOp.AddPortGroup( L"Group_0", 1, 1 );
	newOp.AddOutputPortByClassID( siClusterPropertyID, L"OutVC", 0 /* index of group 0 */) ;

	// This group will allow between 1 and 1000 input vertex
	newOp.AddPortGroup( L"Group_1", 1, 1000 );

	// We don't specify any specific object yet, because there 
	// is a whole array of inputs to connect to this port
	newOp.AddInputPortByClassID( siClusterPropertyID, L"InVC", 1 /* index of group 1 */ ) ;

	// Connection time, which is done by group (ie., index of new port group instance) 
	LONG instance ;

	// Connect the output to Group_0
	newOp.ConnectToGroup( 0 /* index of group 0 */, refoutProp, instance ) ;

	// Connect all the inputs to Group_1
	for ( LONG i = 0 ; i < inProps.GetCount() ; i++ )
	{
		// Error check that inputs really are ClusterProperties
		ClusterProperty clusterProp( inProps[i] );
		if ( !clusterProp.IsValid() || clusterProp.GetType() != L"vertexcolor" )
		{
			newOp.Disconnect(false) ;	//Cleanup
			return CStatus::InvalidArgument;
		}

		CRef l_ref(clusterProp.GetRef());
		CStatus st( newOp.ConnectToGroup(  (LONG)1/* index of group 1 */, l_ref, instance ) );

		// Each connection creates a new instance of the group
		assert( st.Succeeded() ) ;		
		assert( instance == i ) ; 
	}

	ctxt.PutAttribute( L"ReturnValue", newOp.GetRef() );

	// Return CStatus::Fail if you want to raise a script error
	return CStatus::OK;
}


//
// 'Update' Entry Point, called by Softimage when the operator must evaluate the
// output of the VertexColorMixer plug-in.
//

XSIPLUGINCALLBACK CStatus VertexColorMixer_Init( CRef& in_ctxt )
{
	CVertexColorMixer* pThis = new CVertexColorMixer();	

	OperatorContext opCtxt( in_ctxt ) ;
	opCtxt.PutUserData( (CValue::siPtrType)pThis );
	return CStatus::OK;
}

XSIPLUGINCALLBACK CStatus VertexColorMixer_Term( CRef& in_ctxt )
{
	OperatorContext opCtxt( in_ctxt ) ;
	CValue::siPtrType p = opCtxt.GetUserData();
	CVertexColorMixer* pThis = (CVertexColorMixer*) p ;

	assert( pThis != NULL ) ; 

	delete (CVertexColorMixer*)pThis;
	return CStatus::OK;
}


XSIPLUGINCALLBACK CStatus VertexColorMixer_Update( CRef& in_ctxt )
{
	OperatorContext opCtxt( in_ctxt ) ;
	CValue::siPtrType p = opCtxt.GetUserData();
	CVertexColorMixer* pThis = (CVertexColorMixer*) p ;

	assert( pThis != NULL ) ;  // Should have been set in Init

	//Delegate implementation to the instance class
	return pThis->Update(opCtxt);
}

// Note: there are no parameters on this operator,
// so we do not implement _Define callback or _DefineLayout


//////////////////////////////////////////////////////////////////////////////
// CVertexColorMixer implementation
//////////////////////////////////////////////////////////////////////////////

CStatus CVertexColorMixer::Update
(
	OperatorContext&	ctx
)
{
	// Output
	ClusterProperty vc = ctx.GetOutputTarget() ;
	assert( vc.IsValid() ) ; 

	// Inputs
	CRefArray vc_array ;

	Operator op(ctx.GetSource());
	LONG cntInputWeightMaps = op.GetNumInstancesInGroup( 1 ) ;

	assert( cntInputWeightMaps > 0 ) ; 

	for ( LONG i = 0 ; i < cntInputWeightMaps ; i++ )
	{
		// Read the different instances of the input port 
		// to get each cluster property
		ClusterProperty clsprop( ctx.GetInputValue( 
										0, /* Index of InVC port */
										1, /* Index of Group_1 */
										i  /* Port Instance */ ) );

		assert( clsprop.IsValid() ) ; 

		vc_array.Add( clsprop );
	}

	return Mix( vc, vc_array );
}

CStatus CVertexColorMixer::Mix( ClusterProperty& vc, const CRefArray& vc_array )
{
	CDoubleArray aresult;

	double default_r = 0.7529411764705882;
	double default_g = 0.7529411764705882;
	double default_b = 0.7529411764705882;
	double default_a = 1;

	assert( vc_array.GetCount() > 0 ) ;

	for ( LONG i = 0; i < vc_array.GetCount(); i++ )
	{
		ClusterProperty clsprop(vc_array[i]); 
		CDoubleArray avc =  clsprop.GetElements().GetArray();
		
		for ( LONG j = 0; j < avc.GetCount(); j=j+4 )
		{
			if ( i==0 ) 
			{
				aresult.Add( default_r );
				aresult.Add( default_g );
				aresult.Add( default_b );
				aresult.Add( default_a );
			}

			if ( avc[j+0] != default_r )
				aresult[j+0] = avc[j+0];

			if ( avc[j+1] != default_g )
				aresult[j+1] = avc[j+1];

			if ( avc[j+2] != default_b )
				aresult[j+2] = avc[j+2];
			
			if ( avc[j+3] != default_a )
				aresult[j+3] = avc[j+3];
		}
	}

	return vc.GetElements().PutArray( aresult );
}

