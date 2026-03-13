//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

function XSILoadPlugin( in_reg )
{
	// CenterOp_Basic
	//
	// Example of an operator connected
	// to a fixed number of inputs
	//
	// This operator sets the output object to the average position
	// of the 3 input objects.  It requires a fixed number of inputs
	// is provided for comparison with the more dynamic "SimpleCenterOp"
	// and "DynamicCenterOp" examples.
	
	
	in_reg.Author = "Softimage";
	in_reg.Name = "CenterOp_Basic Plugin";
	in_reg.Major = 1;
	in_reg.Minor = 0;

	in_reg.RegisterOperator("CenterOp_Basic");
	in_reg.RegisterCommand("DemoCenterOp_Basic","DemoCenterOp_Basic");	
		
	//RegistrationInsertionPoint - do not remove this line

	return true;
}

// CenterOp_Basic operator implementation
// 
function CenterOp_Basic_Update( ctxt )
{
	var avgVec = XSIMath.CreateVector3() ;
	
	// This "basic" implementation is hardcoded to assume 3 input objects

	avgVec.AddInPlace( ctxt.GetInputValue( 0 ).Transform.Translation ) ;
	avgVec.AddInPlace( ctxt.GetInputValue( 1 ).Transform.Translation ) ;
	avgVec.AddInPlace( ctxt.GetInputValue( 2 ).Transform.Translation ) ;

	avgVec.ScaleInPlace( 1/3 ) ;

	if ( ctxt.Source.Debug )
	{
		PrintVector( "New center position: ", gAvgVec ) ;
	}
	
	// Set the new transformation
	var trans = XSIMath.CreateTransform() ;
	trans.Translation = avgVec;
		
	ctxt.OutputTarget.Transform = trans ;
	
	return true;
}

// DemoCenterOp Commmand implementation
//
// This is a demonstration of the CenterOp_Basic

function DemoCenterOp_Basic_Execute(  )
{
	NewScene( null, false ) ;
	
	oSphere1 = ActiveSceneRoot.AddGeometry( "Sphere", "MeshSurface", "Sphere1" ) ;
	oSphere2 = ActiveSceneRoot.AddGeometry( "Sphere", "NurbsSurface", "Sphere2" ) ;	
	oCylinder = ActiveSceneRoot.AddGeometry( "Cylinder", "NurbsSurface", "Cylinder" ) ;
	
	oSphere1.posx =  10 ; oSphere1.posy = -5 ; 
	oSphere2.posx = -12 ; oSphere2.posy = 4 ;
	oCylinder.posx = -4 ; oCylinder.posy = -5 ;

	// This a basic operator that doesn't provide its own custom command
	// to "Apply" the operator. However it is easy to set it up using 
	// Parameter.AddCustomOp

	var oCenterNull = ActiveSceneRoot.AddNull( "Center" ) ;

	var newOp = oCenterNull.Kinematics.Global.AddCustomOp( "CenterOp_Basic", 
						[ oSphere1.Kinematics.Global, 
						  oSphere2.Kinematics.Global, 
						  oCylinder.Kinematics.Global ] ) ;

	
	var oPos = oCenterNull.Kinematics.Global.Transform.Translation ;
	
	//INFO : Position between spheres: -2,-2,0
	PrintVector( "Position between spheres:", oPos ) ;
}

// Helper function
function PrintVector( prefix, vec )
{
	Application.LogMessage( prefix + " " + vec.X + "," + vec.Y + "," + vec.Z ) ;
}

