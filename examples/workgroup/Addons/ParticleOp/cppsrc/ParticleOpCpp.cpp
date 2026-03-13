//////////////////////////////////////////////////////////////////////////////
//
// ParticleOpCpp.cpp
//
//
// This file implements the ExampleParticleOp example plug-in for Softimage in C++ using
// the Softimage C++ API.  It implements the communication with Softimage and the core algorithm
// of the example.
//
// Note: The associated SPDL file defines the parameters and the update function which 
// is implemented here.
//
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   
//////////////////////////////////////////////////////////////////////////////

#include <xsi_parameter.h>
#include <xsi_customoperator.h>
#include <xsi_operatorcontext.h>
#include <xsi_particlecloudprimitive.h>
#include <xsi_pluginregistrar.h>
#include <xsi_command.h>
#include <xsi_argument.h>
#include <xsi_application.h>
#include <xsi_selection.h>
#include <xsi_factory.h>
#include <xsi_ppglayout.h>



#include <math.h>       // sqrt
#include <time.h>		// srand
#include <assert.h>

using namespace XSI;
using namespace MATH;


// A simple vector structure for convenience.
// Alternatively I could have used the Vector3 class from Softimage SDK
// which also provides convenient vector manipulation methods
struct ParticleVector
{
	double x ;
	double y ;
	double z ;
} ;

// This structure contains the global simulation settings.  These values are exposed
// to the user as the Parameters on the operator.  Changing these values totally changes 
// the behavior of the particles
struct SimulationParams
{
	SimulationParams()
	{
		// Note: These values will be overwritten by GetParameters()
		// To change the default that the user sees you can
		// modify the "Value" attribute of the spdl file.
		FlockInfluence = 0.25 ;
		FlockDistanceSquared = 4.0 ;
		RepulsiveDistanceSquared = 1.0 ;
		MaxVelocity = 1.0 ;
		VelocityVariance = 0.3 ;
		BoundaryLength = 4 ;
		SimulationCenter[0] = 0.0 ;
		SimulationCenter[1] = 0.0 ;
		SimulationCenter[2] = 0.0 ;
	}

	double FlockInfluence ;
	double FlockDistanceSquared ;
	double RepulsiveDistanceSquared ;
	double MaxVelocity ;
	double VelocityVariance ;
	double BoundaryLength ;     // Radius of the sphere
	double SimulationCenter[3] ;
} ;

// Forward declarations

static CStatus InitializeData( const SimulationParams & in_Params,ParticleCloudPrimitive& in_Particles, ParticleVector * io_pData ) ;
static CStatus Evaluate( const SimulationParams & in_Params, ParticleCloudPrimitive& io_pParticles, ParticleVector * io_pData ) ;
static void EvaluateParticle
( 
	LONG in_id,							// Which particle am I?
	LONG in_cntItems,					// Total number of particles
	ParticleVector * io_aPos,			// Array of position vectors for all particles
	ParticleVector * io_aVel,			// Array of velocity vectors for all particles
	const SimulationParams & in_Params	// Global simluation rules
) ;
static void GetParameters( 
	OperatorContext & in_Ctx,
	SimulationParams & out_Params ) ;

//////////////////////////////////////////////////////////////////////////////
// Entry Points
//////////////////////////////////////////////////////////////////////////////
XSIPLUGINCALLBACK CStatus XSILoadPlugin( PluginRegistrar& in_reg )
{
	in_reg.PutAuthor(L"Softimage");
	in_reg.PutName(L"ParticleOpPlugin");
	in_reg.PutEmail(L"");
	in_reg.PutVersion(2,0);

	in_reg.RegisterCommand(L"ApplyParticleOp");

	in_reg.RegisterOperator(L"ParticleOp");

	//RegistrationInsertionPoint - do not remove this line

	return CStatus::OK;
}

XSIPLUGINCALLBACK CStatus ApplyParticleOp_Init( CRef& in_ctxt )
{
	Context ctxt( in_ctxt );
	Command oCmd;
	oCmd = ctxt.GetSource();

	ArgumentArray oArgs = oCmd.GetArguments();

	// The argument handler takes care of passing the
	// Selection when the command is invoked from the 
	// menu
	oArgs.AddWithHandler(L"in_Target",siArgHandlerSingleObj);
	return CStatus::OK;
}

XSIPLUGINCALLBACK CStatus ApplyParticleOp_Execute( CRef& in_ctxt )
{
	Context ctxt( in_ctxt );
	Application app ;

	CValueArray args = ctxt.GetAttribute(L"Arguments");
	ParticleCloudPrimitive in_Target(args[0]);

	if ( !in_Target.IsValid() )
		if ( app.GetSelection().GetCount() > 0 )
			in_Target = app.GetSelection().GetItem(0) ;

	if ( !in_Target.IsValid() )
	{
		app.LogMessage( L"ApplyParticleOp - Invalid argument, expect a Particle Cloud Primitive", XSI::siErrorMsg ) ;
		return CStatus::InvalidArgument ;
	}

	// Build the Custom Operator

	CustomOperator op = in_Target.AddCustomOp( L"ParticleOp" ) ;

	//Note: the AddCustomOp call is a convenient equivalent to
	//this code:
	//Factory fact = app.GetFactory() ;
	//CustomOperator op = fact.CreateObject( L"ParticleOp" ) ; 
	//op.AddOutputPort( in_Target ) ;
	//op.Connect();
	
	// Return the newly created operator
	ctxt.PutAttribute( L"ReturnValue", (CRef)op ) ;

	return CStatus::OK;
}

XSIPLUGINCALLBACK CStatus ParticleOp_Define
(
	CRef&	in_ctx
)
{
	CustomOperator op = Context(in_ctx).GetSource() ;
	Factory fact = Application().GetFactory() ;

	Parameter dummy ;

	op.AddParameter(  fact.CreateParamDef( 
							L"FlockInfluence",  //ScriptName
							CValue::siDouble,   //Type
							siAnimatable,       // (siPersistable is automatic)
							L"Flock Influence", L"", // Name, description
							0.25,				// Default
							-2.0, 2.0,  // Min Max
							0.0, 1.0    // UIMin UIMax
							), dummy );

	op.AddParameter(  fact.CreateParamDef( 
							L"FlockDistance",  //ScriptName
							CValue::siDouble,   //Type
							siAnimatable,       // (siPersistable is automatic)
							L"Flock Distance", L"", // Name, description
							2.0,				// Default
							0.0, 100.0,   // Min Max
							0.0, 100.0    // UIMin UIMax
							), dummy );

	op.AddParameter(  fact.CreateParamDef( 
							L"RepulsiveDistance",  //ScriptName
							CValue::siDouble,   //Type
							siAnimatable,       // (siPersistable is automatic)
							L"Repulsive Distance", L"", // Name, description
							1.0,				// Default
							0.01, 100.0,   // Min Max
							0.01, 100.0    // UIMin UIMax
							), dummy );

	op.AddParameter(  fact.CreateParamDef( 
							L"Velocity",  //ScriptName
							CValue::siDouble,   //Type
							siAnimatable,       // (siPersistable is automatic)
							L"Velocity", L"", // Name, description
							0.5,				// Default
							0.01, 10.0,   // Min Max
							0.01, 10.0    // UIMin UIMax
							), dummy );
	op.AddParameter(  fact.CreateParamDef( 
							L"DirectionVariance",  //ScriptName
							CValue::siDouble,   //Type
							siAnimatable,       // (siPersistable is automatic)
							L"Direction Variance", L"", // Name, description
							0.1,				// Default
							0.0, 10.0,   // Min Max
							0.0, 10.0    // UIMin UIMax
							), dummy );
	op.AddParameter(  fact.CreateParamDef( 
							L"BoundaryLength",  //ScriptName
							CValue::siDouble,   //Type
							siAnimatable,       // (siPersistable is automatic)
							L"Bounding Sphere Radius", L"", // Name, description
							6.0,				// Default
							0.01, 1000.0,   // Min Max
							0.01, 100.0    // UIMin UIMax
							), dummy );
	
	op.AddParameter(  fact.CreateParamDef( 
							L"x",  //ScriptName
							CValue::siDouble,   //Type
							siAnimatable,       // (siPersistable is automatic)
							L"x", L"", // Name, description
							0.0,				// Default
							0.0, 100.0,   // Min Max
							0.0, 100.0    // UIMin UIMax
							), dummy );

	op.AddParameter(  fact.CreateParamDef( 
							L"y",  //ScriptName
							CValue::siDouble,   //Type
							siAnimatable,       // (siPersistable is automatic)
							L"y", L"", // Name, description
							0.0,				// Default
							0.0, 100.0,   // Min Max
							0.0, 100.0    // UIMin UIMax
							), dummy );

	op.AddParameter(  fact.CreateParamDef( 
							L"z",  //ScriptName
							CValue::siDouble,   //Type
							siAnimatable,       // (siPersistable is automatic)
							L"z", L"", // Name, description
							0.0,				// Default
							0.0, 100.0,   // Min Max
							0.0, 100.0    // UIMin UIMax
							), dummy );

	// As this is a simulation we need to be evaluated even if the parameters don't change
	op.PutAlwaysEvaluate( true ) ;

	return CStatus::OK ;
}

XSIPLUGINCALLBACK CStatus ParticleOp_DefineLayout
(
	CRef&	in_ctx
)
{
	PPGLayout layout = Context(in_ctx).GetSource() ;
	layout.Clear() ;
	layout.AddGroup( L"Behavior" ) ;

		// Note: we don't specify any label because the Parameters
		// already have suitable names in their definitions
		layout.AddItem( L"FlockInfluence" ) ;
		layout.AddItem( L"FlockDistance" ) ;
		layout.AddItem( L"RepulsiveDistance" ) ;
		layout.AddItem( L"Velocity" ) ;
		layout.AddItem( L"DirectionVariance" ) ;

	layout.EndGroup() ;

	layout.AddGroup( L"Particle Boundary" ) ;
		layout.AddItem( L"BoundaryLength" ) ;
	layout.EndGroup() ;

	layout.AddGroup( L"Centre of Simulation" ) ;
		layout.AddItem( L"X" ) ;
		layout.AddItem( L"Y" ) ;
		layout.AddItem( L"Z" ) ;
	layout.EndGroup() ;

	return CStatus::OK ;
}

//
// 'Update' Entry Point, called by Softimage when the operator must evaluate the
// output of the ExampleParticleOp plug-in.
// This is only called when the inputs ports or parameter types change
//
// Because we are running a simulation we can animate one of our parameters
// to force the evaluation with each frame change.

XSIPLUGINCALLBACK CStatus ParticleOp_Update
(
	CRef&	in_ctx
)
{
	CStatus hr = CStatus::OK ; 
	OperatorContext ctxt( in_ctx ) ;

	try 
	{
		// Get OM pointer to our output particle collection
		ParticleCloudPrimitive outCloudPrim(ctxt.GetOutputTarget()); 

		// We read the simulation parameters at each evaluation.  
		// This allows users to interactively tweek the behavior
		SimulationParams l_Params ;
		GetParameters( ctxt, l_Params ) ;

		// Check if we have set the operator User Data yet.
		CValue userData = ctxt.GetUserData();
		ParticleVector * pData = NULL ;

		if ( userData.m_t == CValue::siPtr )  // It would be siEmpty is we haven't set any user data yet
		{
			pData = (ParticleVector*)(void*) userData ;
		}		

		if ( pData == NULL )
		{
			// This is the first time we have been called
			// Rather than using ExampleParticleOp_Init we initialize now.

			// We allocate a buffer that is large enough to store both position and velocity
			// vectors for each particle.  This we will save as the "UserData" of this
			// instance of the operator, so that we can access and update it again whenever 
			// we get re-evaluated

			// Warning: this technique assumes that the size of the cloud will never change.
			// to make it robust we would have to store cntItems as part of our buffer.

			LONG cntItems = outCloudPrim.GetCount() ;
			pData = (ParticleVector*) ::malloc( cntItems * sizeof( ParticleVector ) * 2 ) ; 
			InitializeData( l_Params, outCloudPrim, pData ) ;
			ctxt.PutUserData(XSI::CValue(pData)) ;
		}
		else
		{
			// Evaluate a "tick"
			hr = Evaluate( l_Params, outCloudPrim, pData ) ;
		}
	}
	catch ( ... ) 
	{
		// Catch and swallow any exceptions that occur in our plugin
		// For this ever to be excercised indicates a serious bug in the
		// plugin.  
		assert( !"Exception in ExampleParticleOp_Update" ) ;
	}

	return CStatus::OK ;
}

// This function is called whenever an operator is being removed from the scene,
// for example if Softimage is shutting down or if the object is deleted.
// We use this to clean our private data.
XSIPLUGINCALLBACK CStatus ParticleOp_Term(
				CRef& in_rCtx,
				LONG			   /*in_bOffloading */ )
{	
	// Erase the state of this operator
	Context rCtx( in_rCtx ) ;
	ParticleVector * pData = (ParticleVector*)(void*)rCtx.GetUserData();
	::free( pData ) ;

	// just to be sure:
	rCtx.PutUserData(XSI::CValue((void*)NULL)) ;

	return CStatus::OK;
}


static CStatus InitializeData
( 
	const SimulationParams & in_Params, 
	ParticleCloudPrimitive& in_Particles, 
	ParticleVector * io_pData
)
{
	// Random numbers are used to introduce variation in the
	// movement of the particles.  This makes sure the simulation is
	// different each time we run it.
	srand( (unsigned)time( NULL ) );	

	LONG cntItems = in_Particles.GetCount() ;

	// Our memory layout is straightfoward.  In a single 
	// large buffer we first store all the particle positions, 
	// then all the particle velocities

	ParticleVector * aPos = io_pData ;

	// Particle velocities follow the particle positions
	ParticleVector * aVel = &(aPos[ cntItems ]) ;

	for ( LONG i = 0 ; i < cntItems ; i++ )
	{
		// We read the initial position from the particle cloud itself.  This is
		// not the position at any particular stage in our simulation, it is the initial position of
		// the particle cloud before the operator was applied.  To accurately set this information
		// another custom operator could be applied before this operator, which would set the default
		// position
		// Alternatively at this point we could force the particles into a interesting initial
		// position outselves.

		Particle particle = in_Particles.GetParticle(i) ;

		MATH::CVector3 vec = particle.GetPosition() ;

		aPos[i].x = vec.GetX() ;
		aPos[i].y = vec.GetY() ;
		aPos[i].z = vec.GetZ() ;

		// Pick a random initial velocity within the maximum velocity
		// Each axis gets a random value from [-MaxVelocity...+MaxVelocity]
		
		int rnd = rand() ;
		aVel[i].x = ( 2 * in_Params.MaxVelocity * rand() ) / RAND_MAX - in_Params.MaxVelocity ;
		aVel[i].y = ( 2 * in_Params.MaxVelocity * rand() ) / RAND_MAX - in_Params.MaxVelocity ;
		aVel[i].z = ( 2 * in_Params.MaxVelocity * rand() ) / RAND_MAX - in_Params.MaxVelocity ;
	}

	return CStatus::OK ;
}


CStatus Evaluate
( 
	const SimulationParams & in_Params, 
	ParticleCloudPrimitive& io_Particles, 
	ParticleVector * io_pData 
)
{
	LONG cntItems = io_Particles.GetCount() ;

	ParticleVector * aPos = io_pData ;

	// Particle velocities follow the particle positions
	ParticleVector * aVel = &(aPos[ cntItems ]) ;

	// This is a O( n squared ) algorithm - each particle
	// is influenced by every other particle. To avoid transfering this 
	// data in and out of the Object Model with many many allocations
	// of temporary buffers, we copy the data locally with a single pass

	// For the moment each particle moves immediately, which means that
	// later particles will see the moved location, not the location
	// at the start of the round.  An alternative to permit them
	// to all "think" at once would be to make another copy of the memory

	CDoubleArray posValues( cntItems * 3 ) ;

	for ( LONG i = 0 ; i < cntItems ; i++ )
	{
		// Determine the new particle velocity and position
		// Upon return aPos[i] and aVel[i] will have been updated
		EvaluateParticle( i, cntItems, aPos, aVel, in_Params ) ;

		// only at this point do we need to offset by the actual Simulation Center
		posValues[ i * 3 ]	  = in_Params.SimulationCenter[0] + aPos[i].x ;
		posValues[ i * 3 + 1] = in_Params.SimulationCenter[1] + aPos[i].y ;
		posValues[ i * 3 + 2] = in_Params.SimulationCenter[2] + aPos[i].z ;
	}

	// Note: we don't need to save the velocity in the cloud because
	// we are running our own simulation 

	io_Particles.PutPositionArray( posValues ) ;

	return CStatus::OK ;
}

static double VectorLength( const ParticleVector & in_Vec )
{
	return sqrt( in_Vec.x * in_Vec.x + 
				 in_Vec.y * in_Vec.y + 
				 in_Vec.z * in_Vec.z ) ;
}

static void ScaleVector( ParticleVector & io_Vec, double in_ScaleFactor )
{
	io_Vec.x *= in_ScaleFactor ;
	io_Vec.y *= in_ScaleFactor ;
	io_Vec.z *= in_ScaleFactor ;
}

// Update the velocity and position of a particle.
// Notice how no Softimage access is required - 
// we have all the necessary simulation information in
// our inmemory structures.

static void EvaluateParticle
( 
	LONG in_id,							// Which particle am I?
	LONG in_cntItems,					// Total number of particles
	ParticleVector * io_aPos,			// Array of position vectors for all particles
	ParticleVector * io_aVel,			// Array of velocity vectors for all particles
	const SimulationParams & in_Params	// Global simluation rules
)
{
	LONG cntCloseParticles = 0 ;

	// Avg is used to calculate the average location of the close particles, 
	// which is used to decide on a attraction vector
	ParticleVector Avg ;
	Avg.x=Avg.y=Avg.z = 0.0 ;

	ParticleVector& thisPos = io_aPos[ in_id ] ;
	ParticleVector& thisVel = io_aVel[ in_id ] ;

	// Search all other particles for close particles
	for ( LONG j = 0 ; j < in_cntItems ; j++ )
	{	
		if ( in_id == j ) 
		{
			continue ; // Ignore myself
		}

		ParticleVector & otherPos = io_aPos[j] ;
		ParticleVector & otherVel = io_aVel[j] ;

		double x_diff = otherPos.x - thisPos.x ;
		double y_diff = otherPos.y - thisPos.y ;	
		double z_diff = otherPos.z - thisPos.z ;	

		double distance_squared = x_diff * x_diff + y_diff * y_diff + z_diff * z_diff ;

		if ( distance_squared < in_Params.RepulsiveDistanceSquared )
		{
			cntCloseParticles++ ;

			// Because the other guy is too close, consider it a turn off
			// and pretend we are attacted to a particle in the opposite direction
			Avg.x += 2 * thisPos.x - otherPos.x ;
			Avg.y += 2 * thisPos.y - otherPos.y ;
			Avg.z += 2 * thisPos.z - otherPos.z ;
		}
		else if ( distance_squared < in_Params.FlockDistanceSquared )
		{
			// Other particle is close enough that we should consider it

			cntCloseParticles++ ;

			Avg.x += otherPos.x ;
			Avg.y += otherPos.y ;
			Avg.z += otherPos.z ;
		}				
	}

	// Determine a random change in velocity - this
	// jiggle helps particles find each other when they are wandering
	// and also introduces some "escape" potential for flocking particles

	thisVel.x += ( in_Params.VelocityVariance * rand() ) / RAND_MAX - ( in_Params.VelocityVariance / 2.0 );
	thisVel.y += ( in_Params.VelocityVariance * rand() ) / RAND_MAX - ( in_Params.VelocityVariance / 2.0 );
	thisVel.z += ( in_Params.VelocityVariance * rand() ) / RAND_MAX - ( in_Params.VelocityVariance / 2.0 );

	if ( cntCloseParticles > 0 )
	{
		// We are in a flock

		Avg.x /= cntCloseParticles ;
		Avg.y /= cntCloseParticles ;
		Avg.z /= cntCloseParticles ;

		// We change direction but not speed to the average position of 
		// the flock
		ParticleVector Attraction ;

		Attraction.x = Avg.x - thisPos.x ;
		Attraction.y = Avg.y - thisPos.y ;
		Attraction.z = Avg.z - thisPos.z ;

		double LenCurrent = VectorLength( thisVel ) ;
		double LenAttraction = VectorLength( Attraction ) ;

		if ( LenAttraction == 0.0 ) 
			LenAttraction = 0.1 ;

		// Determine how much the attraction towards to center of other particles
		// will affect the movement of the particles
		double ScaleFactor = in_Params.FlockInfluence * LenCurrent / LenAttraction ;

		thisVel.x = thisVel.x + ScaleFactor * Attraction.x ;
		thisVel.y = thisVel.y + ScaleFactor * Attraction.y ;
		thisVel.z = thisVel.z + ScaleFactor * Attraction.z ;

		// New velocity needs to be scaled to same speed as original

		double LenNew = VectorLength( thisVel ) ;

		if ( LenNew == 0.0 ) 
			LenNew = 0.1 ;

		double ScaleFactor2 = LenCurrent / LenNew ;
		
		ScaleVector( thisVel, ScaleFactor2 ) ;
	}

	// Avoid the particle getting too fast.
	// (Alternatively we would be more accurate to 
	// scale according to the actual length of the vector)

	if ( thisVel.x > in_Params.MaxVelocity )
		thisVel.x = in_Params.MaxVelocity ;

	if ( thisVel.x < -in_Params.MaxVelocity )
		thisVel.x = -in_Params.MaxVelocity ;

	if ( thisVel.y > in_Params.MaxVelocity )
		thisVel.y = in_Params.MaxVelocity ;

	if ( thisVel.y < -in_Params.MaxVelocity )
		thisVel.y = -in_Params.MaxVelocity ;
	
	if ( thisVel.z > in_Params.MaxVelocity )
		thisVel.z = in_Params.MaxVelocity ;

	if ( thisVel.z < -in_Params.MaxVelocity )
		thisVel.z = -in_Params.MaxVelocity ;

	// Move the position ahead by the velocity (so in effect
	// our velocity value is velocity per-frame)

	thisPos.x += thisVel.x ;
	thisPos.y += thisVel.y ;
	thisPos.z += thisVel.z ;

	// Some simple drastic measures are taken when a wall is hit
	// These gives a bouncing behavior. It would be nicer to 
	// look ahead and do an avoidance algorithm.

	double distanceFromCentre = VectorLength( thisPos ) ;

	if (( distanceFromCentre > in_Params.BoundaryLength ) && 
		( distanceFromCentre != 0 ))
	{
		// Move the particle back to the bounding sphere
		ScaleVector( thisVel, in_Params.BoundaryLength / distanceFromCentre  ) ;

		// Mix the current velocity vector with the vector that points back
		// towards the centre
		double LenOld = VectorLength( thisVel ) ;		

		thisVel.x = 0.25 * thisVel.x + ( 0.75 * -thisPos.x ) ;
		thisVel.y = 0.25 * thisVel.y + ( 0.75 * -thisPos.y ) ;
		thisVel.z = 0.25 * thisVel.z + ( 0.75 * -thisPos.z ) ;

		// Restore the old speed
		double LenNew = VectorLength( thisVel ) ;

		if ( LenNew > 0 )
		{
			ScaleVector( thisVel, LenOld / LenNew ) ;
		}
	}
}


// Fill in the simulation rules based on the operators parameters
static void GetParameters( 
	OperatorContext & in_ctx,
	SimulationParams & out_Params )
{
	out_Params.FlockInfluence = in_ctx.GetParameterValue( L"FlockInfluence" ) ;
	out_Params.FlockDistanceSquared = in_ctx.GetParameterValue( L"FlockDistance" ) ;
	out_Params.FlockDistanceSquared *= out_Params.FlockDistanceSquared ;

	out_Params.RepulsiveDistanceSquared = in_ctx.GetParameterValue( L"RepulsiveDistance") ;
	out_Params.RepulsiveDistanceSquared *= out_Params.RepulsiveDistanceSquared ;

	out_Params.MaxVelocity = in_ctx.GetParameterValue( L"Velocity" ) ; 

	// Transform MaxVelocity from absolute length to equivalent length along any particular
	// axis (because we treat each axis separately when calculating velocity)
	out_Params.MaxVelocity = sqrt( out_Params.MaxVelocity * out_Params.MaxVelocity / 3 ) ;

	out_Params.VelocityVariance = in_ctx.GetParameterValue( L"DirectionVariance" ) ;
	out_Params.BoundaryLength = in_ctx.GetParameterValue( L"BoundaryLength" ) ;		

	out_Params.SimulationCenter[0] = in_ctx.GetParameterValue( L"x" ) ;	
	out_Params.SimulationCenter[1] = in_ctx.GetParameterValue( L"y" ) ;	
	out_Params.SimulationCenter[2] = in_ctx.GetParameterValue( L"z" ) ;
}




