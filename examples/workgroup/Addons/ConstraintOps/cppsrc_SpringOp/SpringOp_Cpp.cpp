//
// SpringOp
// This is an operator written by Michael Isner, January 2001
// ported to C++ Custom Operators by Andrew Skowronski, Nov 2005
//
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

#include <xsi_application.h>
#include <xsi_context.h>
#include <xsi_status.h>

#include <xsi_factory.h>
#include <xsi_model.h>
#include <xsi_kinematics.h>
#include <xsi_kinematicstate.h>
#include <xsi_null.h>
#include <xsi_customoperator.h>
#include <xsi_operatorcontext.h>
#include <xsi_outputport.h>
#include <xsi_inputport.h>
#include <xsi_portgroup.h>
#include <xsi_ppglayout.h>
#include <xsi_pluginregistrar.h>

using namespace XSI; 
using namespace XSI::MATH; 

XSIPLUGINCALLBACK CStatus XSILoadPlugin( PluginRegistrar& in_reg )
{
	in_reg.PutAuthor(L"Softimage");
	in_reg.PutName(L"SpringOp_CppPlugin");
	in_reg.PutVersion(1,0);
	in_reg.RegisterOperator(L"SpringOp_Cpp");

	in_reg.RegisterCommand(L"DemoSpringOp");
	
	//RegistrationInsertionPoint - do not remove this line

	return CStatus::OK;
}


// All state that was global in the vbscript is
// now managed in this struct that acts as user data.
// For even more OO approach we could code the entire operator 
// as methods of a class that is stored in user data
struct SpringOpUserData
{
	MATH::CVector3 B  ;				// Accumating position of end of spring
	MATH::CVector3 spring  ;
	MATH::CVector3 fdelta  ;

	SpringOpUserData()
		: spring( 0.0,0.0,0.0 )
		, fdelta( 0.1,0.1,0.1 )
	{
	}
} ;


void PrintVector( const CString & in_desc, const CVector3& in_v ) ;
void ApplySpringOp( X3DObject & springEnd, X3DObject & springBase ) ;
void get_springforce (SpringOpUserData* io_pOpState, CVector3 & in_del, double in_len, double in_springK, double in_bounce, bool in_compression) ;
void Dampening_check(SpringOpUserData* io_pOpState, const CVector3 & in_A,  double in_dblLength) ;


XSIPLUGINCALLBACK CStatus DemoSpringOp_Execute()
{
	// Create scene elements
	Model root = Application().GetActiveSceneRoot() ;

	X3DObject sphereOut;
	root.AddGeometry(L"Sphere",L"MeshSurface", L"SphereWithSpring", sphereOut);

	X3DObject cubeIn;
	root.AddGeometry(L"Cube",L"MeshSurface", L"Driver", cubeIn);

	KinematicState endPos = sphereOut.GetKinematics().GetGlobal() ;
	KinematicState basePos = cubeIn.GetKinematics().GetGlobal() ;

	CRefArray inputs(1) ;
	inputs[0] = basePos.GetRef() ;

	CustomOperator op = endPos.AddCustomOp( L"SpringOp_Cpp", inputs ) ;


	//
	// Pull the operator
	// 
	KinematicState spherePos = sphereOut.GetKinematics().GetGlobal() ;
	CValue val = spherePos.GetParameterValue( L"posx" ) ;

	// Tip: To demonstrate more visually, move the cube and watch the sphere bounce around
	// under it

	return CStatus::OK ;
}

XSIPLUGINCALLBACK CStatus SpringOp_Cpp_Define( CRef& in_ctxt )
{
	Context ctxt( in_ctxt ) ;
	CustomOperator op = ctxt.GetSource() ;

	//
	// Build parameters
	//

	Parameter newParam ;

	CRef pdef = Application().GetFactory().CreateParamDef( L"SpringScale", CValue::siDouble, 0.05, 0.0, 1.0 );
	op.AddParameter( pdef, newParam ) ;

	pdef = Application().GetFactory().CreateParamDef( L"Length", CValue::siDouble, 3.0, 0.0, 100.0 );
	op.AddParameter( pdef, newParam ) ;

	pdef = Application().GetFactory().CreateParamDef( L"SpringK", CValue::siDouble, 40.0, 0.0, 100.0 );
	op.AddParameter( pdef, newParam ) ;

	pdef = Application().GetFactory().CreateParamDef( L"Mass", CValue::siDouble, 30.0, 0.0, 100.0 );
	op.AddParameter( pdef, newParam ) ;

	pdef = Application().GetFactory().CreateParamDef( L"Gravity", CValue::siDouble, 40.0, 0.0, 100.0 );
	op.AddParameter( pdef, newParam ) ;

	pdef = Application().GetFactory().CreateParamDef( L"Resistance", CValue::siDouble, 10.0, 0.0, 100.0 );
	op.AddParameter( pdef, newParam ) ;

	pdef = Application().GetFactory().CreateParamDef( L"bounce", CValue::siDouble, 0.7, 0.0, 10.0 );
	op.AddParameter( pdef, newParam ) ;

	pdef = Application().GetFactory().CreateParamDef( L"compression", CValue::siBool, true );
	op.AddParameter( pdef, newParam ) ;

	// This is important so that the spring continues to act during playback
	op.PutAlwaysEvaluate(true) ; 

	// This enables debugging output but will slow down the operator
#ifndef NDEBUG
	op.PutDebug( 1 ) ;
#endif

	return CStatus::OK ;
}


XSIPLUGINCALLBACK CStatus SpringOp_Cpp_DefineLayout( CRef& in_ctxt )
{
	PPGLayout layout = Context(in_ctxt).GetSource() ;
	layout.Clear() ;

	layout.AddItem( L"SpringScale" ) ;
	layout.AddItem( L"Length" ) ;
	layout.AddItem( L"SpringK" ) ;
	layout.AddItem( L"Mass" ) ;
	layout.AddItem( L"Gravity" ) ;
	layout.AddItem( L"Resistance" ) ;
	layout.AddItem( L"bounce" ) ;
	layout.AddItem( L"compression" ) ;

	return CStatus::OK ;
}



XSIPLUGINCALLBACK CStatus SpringOp_Cpp_Update( CRef& in_ctxt )
{
	OperatorContext ctxt( in_ctxt ) ;

	KinematicState out = ctxt.GetOutputTarget() ;

	KinematicState in( ctxt.GetInputValue( 0 ) ); // Read the input

	double SpringScale = ctxt.GetParameterValue( L"SpringScale" ) ;
	double Length = ctxt.GetParameterValue( L"Length" ) ;
	double SpringK = ctxt.GetParameterValue( L"SpringK" ) ;
	double mass = ctxt.GetParameterValue( L"Mass" ) ;
	double gravity = ctxt.GetParameterValue( L"Gravity" ) ;
	double resistance = ctxt.GetParameterValue( L"Resistance" ) ;
	double bounce = ctxt.GetParameterValue( L"bounce" ) ;
	bool compression = ctxt.GetParameterValue( L"compression" ) ;

	CValue::siPtrType pUserData = ctxt.GetUserData();
	SpringOpUserData* pOpState = (SpringOpUserData*)pUserData;	

	MATH::CTransformation transform = in.GetTransform() ;
	MATH::CVector3 A = transform.GetTranslation() ;

	if ( pOpState == NULL )
	{
		// First time called
		pOpState = new SpringOpUserData();	
		ctxt.PutUserData( (CValue::siPtrType)pOpState );

		// Init function boils down to this
		pOpState->B.Set( A.GetX(), A.GetY() - Length, A.GetZ() ) ;
	}

	Dampening_check( pOpState, A, Length ) ;

	CVector3 delta ;
	delta.Sub( A, pOpState->B ) ;

	get_springforce( pOpState, delta, Length, SpringK, bounce, compression ) ;

	//calculate resistance / friction
	CVector3 resist( -pOpState->fdelta.GetX() * resistance, 
					-pOpState->fdelta.GetY() * resistance, 
					-pOpState->fdelta.GetZ() * resistance ) ;

	// calculate acceleration
	CVector3 accel( ( pOpState->spring.GetX() + resist.GetX() ) / mass,
					( pOpState->spring.GetY() + resist.GetY() ) / mass - gravity,
					( pOpState->spring.GetZ() + resist.GetZ() ) / mass ) ;

	// set new velocity delta (fdelta)
	pOpState->fdelta = accel ;
	pOpState->fdelta *= SpringScale ;
	
	pOpState->B += pOpState->fdelta ;

	if ( CustomOperator(ctxt.GetSource()).GetDebug() )
	{
		PrintVector( L"B: ", pOpState->B ) ;
	}

	// Put the new position
	// Alternative is to set the posx, posy, posz parameters
	MATH::CTransformation outTransform = out.GetTransform() ;
	outTransform.SetTranslation( pOpState->B ) ;
	out.PutTransform( outTransform ) ;

	return CStatus::OK ;
}

XSIPLUGINCALLBACK CStatus SpringOp_Cpp_Term( CRef& in_ctxt )
{
	// Cleanup the instance data
	CValue::siPtrType pUserData = Context(in_ctxt).GetUserData();
	SpringOpUserData* pOpState = (SpringOpUserData*)pUserData;	
	delete( pOpState ) ;	
	return CStatus::OK ;
}

void Dampening_check(SpringOpUserData* io_pOpState, const CVector3 & in_A,  double in_dblLength)
{
	// if the simulation goes out of range it is 
	// dampened and starts to move back home.

	if ( io_pOpState->spring.GetLength() > 10000.0 ||
		 io_pOpState->fdelta.GetLength() > 100.0 )
	{
		io_pOpState->B.Set( in_A.GetX(), in_A.GetY() - in_dblLength, in_A.GetZ() ) ;		
		io_pOpState->spring.Set( 0.0, 0.0, 0.0 ) ;
		io_pOpState->fdelta.Set( 0.1, 0.1, 0.1 ) ;		
	}
}

void get_springforce (SpringOpUserData* io_pOpState, CVector3 & in_del, double in_len, double in_springK, double in_bounce, bool in_compression)
{
	// Function recalculates this vector
	CVector3 & spring = io_pOpState->spring ;

	//spring force = K * difference between normal length and it current
	double sForce = in_springK * (in_del.GetLength() - in_len) ;
	if ( sForce >= 0.0 || in_compression )
	{
		spring.Set( spring.GetX() * in_bounce + (in_del.GetX() / in_len) * sForce,
					spring.GetY() * in_bounce + (in_del.GetY() / in_len) * sForce, 
					spring.GetZ() * in_bounce + (in_del.GetZ() / in_len) * sForce ) ;
	}
}

void PrintVector( const CString & in_desc, const CVector3& in_v )
{
	CString x = CValue(in_v.GetX()).GetAsText() ;
	CString y = CValue(in_v.GetY()).GetAsText() ;
	CString z = CValue(in_v.GetZ()).GetAsText() ;

	Application().LogMessage( in_desc + L" " + x + L"," + y + L"," + z ) ;
}

