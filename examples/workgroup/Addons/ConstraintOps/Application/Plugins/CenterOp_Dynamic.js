//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

// Constants to make the code more readable
OUTPUT_PORTGROUP =0 ;
INPUT_PORTGROUP  =1 ;

function XSILoadPlugin( in_reg )
{
	// CenterOp_DynamicPlugin
	
	//
	// Example of an operator that has a dynamic number of input 
	// objects.  It is a more sophisticated version of 
	// the CenterOp example because it allows additional input objects
	// to be connected even after the operator has been created.
	// 
	
	// Demonstrated methods include: Operator.ConnectToGroup,
	// OperatorContext.OutputTarget, OperatorContext.GetInputValue,
	// CustomOperator.AddOutputPortByClassID and
	// CustomOperator.AddInputPortByClassID 


	in_reg.Author = "Softimage";
	in_reg.Name = "CenterOp_DynamicPlugin";
	in_reg.Major = 1;
	in_reg.Minor = 0;

	in_reg.RegisterOperator("CenterOp_Dynamic");

	in_reg.RegisterCommand("DemoCenterOp_Dynamic");		
	in_reg.RegisterCommand("ApplyCenterOp_Dynamic");	
	in_reg.RegisterCommand("AddInputsToCenterOp");
	
	//RegistrationInsertionPoint - do not remove this line

	return true;
}

// CenterOp_Dynamic operator implementation
// 
// There are no parameters for this operator so we do not
// implement the _Define callback

function CenterOp_Dynamic_Init( ctxt )
{
	// Create global math objects.
	// This is a performance enhancement to
	// avoid creating many temporary math objects
	// during the Update callback
	
	gAvgVec = XSIMath.CreateVector3() ;
	gTrans = XSIMath.CreateTransform() ;

}

function CenterOp_Dynamic_Update( ctxt )
{	
	gAvgVec.Set(0,0,0) ;

	// We use the CustomOperator to find out how many inputs
	// are connected
	var oOp = ctxt.Source ;	
	var cntInputs = oOp.GetNumInstancesInGroup(INPUT_PORTGROUP) ;

	// Add all the input objects positions
	for ( var i = 0 ; i < cntInputs ; i++ )
	{
		var oInputKinematicState = ctxt.GetInputValue( 
									0 /* port */, 
									INPUT_PORTGROUP, 
									i /* instance */ ) ;
		
		gAvgVec.AddInPlace( oInputKinematicState.Transform.Translation ) ;										
	}
	
	if ( cntInputs > 0 )
	{
		gAvgVec.ScaleInPlace( 1 / cntInputs ) ;
	}
	
	if ( oOp.Debug )
	{
		PrintVector( "New center position: ", gAvgVec ) ;
	}
	
	// Set the new transformation
	gTrans.Translation = gAvgVec;
		
	output = ctxt.OutputTarget;	
	output.Transform = gTrans;
	
	return true;
}

// ApplyCenterOp_Dynamic command
//
// Creates an instance of the CenterOp_Dynamic
// operator and connects it to a newly created Null.
//
// It also attaches the input objects
//
// The input argument is optional because further
// inputs can be added at any time by calling AddInputsToCenterOp

function ApplyCenterOp_Dynamic_Init( ctxt )
{
	var oCmd;
	oCmd = ctxt.Source;
	oCmd.Description = "Create an instance of CenterOp_Dynamic operator";
	oCmd.SetFlag(siNoLogging,false);

	var oArgs;
	oArgs = oCmd.Arguments;
	oArgs.AddWithHandler("InitialInputs","Collection");

	return true;
}

function ApplyCenterOp_Dynamic_Execute( oInitialInputs )
{
	var oCenterNull = ActiveSceneRoot.AddNull( "Center" ) ;

	var newOp = XSIFactory.CreateObject("CenterOp_Dynamic");

	// Operator definition phase

	//Enable this line to see additional debugging information
	//newOp.Debug = 1 ; 
	
	newOp.AddPortGroup( "Output" ) ;
	newOp.AddOutputPortByClassID(siKinematicStateId, OUTPUT_PORTGROUP);
	
	// We only have a single input port, but we will allow up to 10,000 objects to connect to it.
	// Each connected object will appear as a separate instance of the "inputs" port group
	newOp.AddPortGroup( "Inputs", 0, 10000 ) ;
	newOp.AddInputPortByClassID(siKinematicStateId, INPUT_PORTGROUP);


	// Connection phase

	newOp.ConnectToGroup(OUTPUT_PORTGROUP, 
						 Dictionary.GetObject(oCenterNull.Kinematics.Global.FullName) );

	AddInputsToCenterOp_Execute( newOp, oInitialInputs ) ;
	
	return newOp;
}


// AddInputsToCenterOp command implementation
//
// This command adds additional inputs to the existing operator

function AddInputsToCenterOp_Init( ctxt )
{
	var oCmd;
	oCmd = ctxt.Source;
	oCmd.ReturnValue = false;

	var oArgs;
	oArgs = oCmd.Arguments;
	oArgs.Add("Op",siArgumentInput);
	oArgs.AddWithHandler("Inputs","Collection");
	return true;
}

function AddInputsToCenterOp_Execute( inOp, inInputs )
{
	for ( var i = 0 ; i < inInputs.Count ; i++ )
	{
		inInput = inInputs.Item(i) ;
		if ( inInput.IsClassOf( siX3DObjectId )) 
		{
			inInput = inInput.Kinematics.Global ;
		}
		
		if ( !inInput.IsClassOf( siKinematicStateId )) 
		{
			Application.LogMessage( "Ignoring invalid input object " + inInput.FullName ) ;
			continue ;
		}
	
		oKine = Dictionary.GetObject( inInput.FullName )	;	
		inOp.ConnectToGroup( 1 /* index of inputs portgroup */, oKine) ;
	}
}


// DemoCenterOp_Dynamic Commmand implementation
//
// This is a demonstration of the plug-in in action

function DemoCenterOp_Dynamic_Execute(  )
{
	NewScene( null, false ) ;
	
	oSphere1 = ActiveSceneRoot.AddGeometry( "Sphere", "MeshSurface", "Sphere1" ) ;
	oSphere2 = ActiveSceneRoot.AddGeometry( "Sphere", "NurbsSurface", "Sphere2" ) ;	
	
	oSphere1.posx =  10 ; oSphere1.posy = -5 ; 
	oSphere2.posx = -12 ; oSphere2.posy = 4 ;

	var oOp = ApplyCenterOp_Dynamic( [ oSphere1, oSphere2 ] ) ;

	// Retrieve the Null that is driven by the operator
	var oCenterNull = oOp.PortAt(0,OUTPUT_PORTGROUP,0).Target2 ;	

	var oPos = oCenterNull.Transform.Translation ;
	
	//INFO : Position between spheres: -1,-0.5,0	
	PrintVector( "Position between spheres:", oPos ) ;
	

	// Now demonstrate the dynamic nature of the operator
	// We can create a 3rd object and connect it up to the existing
	// operator
	
	oCylinder = ActiveSceneRoot.AddGeometry( "Cylinder", "NurbsSurface", "Cylinder" ) ;
	oCylinder.posx = -4 ; oCylinder.posy = -5 ;
			
	AddInputsToCenterOp( oOp, oCylinder ) ;
			
	oPos = oCenterNull.Transform.Translation ;
	
	//INFO : Position between spheres and cylinder: -2,-2,0	
	PrintVector( "Position between spheres and cylinder:", oPos ) ;
			
			
	// To try out the demo scene just move one of the spheres or cylinder
	// and watch the null move to remain in the center between the 3 objects
			
	return true;
}

// Helper function
function PrintVector( prefix, vec )
{
	Application.LogMessage( prefix + " " + vec.X + "," + vec.Y + "," + vec.Z ) ;
}

