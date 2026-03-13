//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

function XSILoadPlugin( in_reg )
{
	// CenterOp_Simple
	//
	// Example of an operator connects
	// to a variable number of inputs.
	//
	// This operator is more sophisticated than the
	// CenterOp_Basic example because it can connect 
	// to any number of inputs.  However,
	// once the operator is created it is not possible to
	// add additional inputs objects.  For many
	// operators this is a suitable limitation, otherwise
	// use the techniques demonstrated in the "DynamicCenterOp" example
	// 
	// Demonstrated methods include: Parameter.AddCustomOp,
	// OperatorContext.OutputTarget, OperatorContext.GetInputValue
	// Operator.GetNumPortsInGroup

	in_reg.Author = "Softimage";
	in_reg.Name = "CenterOp_Simple Plugin";
	in_reg.Major = 1;
	in_reg.Minor = 0;

	in_reg.RegisterOperator("CenterOp_Simple");

	in_reg.RegisterCommand("DemoCenterOp_Simple","DemoCenterOp_Simple");	
	
	in_reg.RegisterCommand("ApplyCenterOp_Simple");	
	
	//RegistrationInsertionPoint - do not remove this line

	return true;
}

// CenterOp_Simple operator implementation
// 
// There are no parameters for this operator so we do not
// implement the _Define callback

function CenterOp_Simple_Init( ctxt )
{
	// Create global math objects.
	// This is a performance enhancement to
	// avoid creating many temporary math objects
	// during the Update callback
	
	gAvgVec = XSIMath.CreateVector3() ;
	gTrans = XSIMath.CreateTransform() ;

}

function CenterOp_Simple_Update( ctxt )
{
	
	gAvgVec.Set(0,0,0) ;

	// We use the CustomOperator to find out how many inputs
	// are connected
	var oOp = ctxt.Source ;	
	
	// There is only one port group, containing all the inputs and
	// the single output
	var cntInputs = oOp.GetNumPortsInGroup(0) - 1 ;
	
	
	// Add all the input objects positions
	for ( var i = 0 ; i < cntInputs ; i++ )
	{
		var oInputKinematicState = ctxt.GetInputValue( i /* port */, 0, 0) ;
		
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

// ApplyCenterOp_Simple command
//
// Creates an instance of the CenterOp_Simple
// operator and connects it to a newly created Null and connects all the inputs
//
// Although not demonstrated in the example, this command 
// is suitable as a custom menu entry because it uses
// the Collection argument handler to get the current
// selection if nothing is explicitly passed to the command.

function ApplyCenterOp_Simple_Init( ctxt )
{
	var oCmd;
	oCmd = ctxt.Source;
	oCmd.Description = "Create an instance of CenterOp_Simple operator";
	oCmd.SetFlag(siNoLogging,false);

	var oArgs;
	oArgs = oCmd.Arguments;
	oArgs.AddWithHandler("InitialInputs","Collection");

	return true;
}

function ApplyCenterOp_Simple_Execute( oInputs )
{
	var oCenterNull = ActiveSceneRoot.AddNull( "Center" ) ;

	// Validate the input collection
	// We want to connect to the specific KinematicState
	// but we can accept X3DObjects so that the caller
	// doesn't need to worry about that detail
	
	aValidInputs = [] ;
	
	for ( var i = 0 ; i < oInputs.Count ; i++ )
	{
		var oInputCandidate = oInputs.Item(i) ;
		
		if ( oInputCandidate.IsClassOf( siX3DObjectID ) )
		{
			oInputCandidate = oInputCandidate.Kinematics.Global ;
		}
		
		if ( !oInputCandidate.IsClassOf( siKinematicStateID ) )
		{
			continue ;
		}
		
		aValidInputs[aValidInputs.length] = oInputCandidate ;
	}
	

	var newOp = oCenterNull.Kinematics.Global.AddCustomOp( "CenterOp_Simple", aValidInputs ) ;

	return newOp;
}


// DemoCenterOp Commmand implementation
//
// This is a demonstration of the plug-in in action

function DemoCenterOp_Simple_Execute(  )
{
	NewScene( null, false ) ;
	
	oSphere1 = ActiveSceneRoot.AddGeometry( "Sphere", "MeshSurface", "Sphere1" ) ;
	oSphere2 = ActiveSceneRoot.AddGeometry( "Sphere", "NurbsSurface", "Sphere2" ) ;	
	oCylinder = ActiveSceneRoot.AddGeometry( "Cylinder", "NurbsSurface", "Cylinder" ) ;

	
	oSphere1.posx =  10 ; oSphere1.posy = -5 ; 
	oSphere2.posx = -12 ; oSphere2.posy = 4 ;
	oCylinder.posx = -4 ; oCylinder.posy = -5 ;

	var oOp = ApplyCenterOp_Simple( [ oSphere1, oSphere2, oCylinder ] ) ;

	// Retrieve the Null that is driven by the operator
	var oCenterNull = oOp.OutputPorts.Item(0).Target2 ;	

	// Pull the output of the operator
	var oPos = oCenterNull.Transform.Translation ;
	
	//INFO : Position between spheres: -2,-2,0	
	PrintVector( "Position between spheres:", oPos ) ;
}

// Helper function
function PrintVector( prefix, vec )
{
	Application.LogMessage( prefix + " " + vec.X + "," + vec.Y + "," + vec.Z ) ;
}

