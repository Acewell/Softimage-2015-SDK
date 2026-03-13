// Splatter Plugin
// This is the Run-time operator version.
//
// Unlike the Self-installed plug-in version, each 
// copy of the Splatter operator that is created 
// has its own copy of the source code
//
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

function XSILoadPlugin( in_reg )
{
	in_reg.Author = "Softimage";
	in_reg.Name = "Splatter JScript Runtime";
	in_reg.Major = 1;
	in_reg.Minor = 0;

	in_reg.RegisterCommand("ApplySplatterRuntime");
	in_reg.RegisterMenu(siMenuTbDeformID,"ApplySplatter_Menu",false,false);
	//RegistrationInsertionPoint - do not remove this line

	return true;
}

function ApplySplatter_Menu_Init( ctxt )
{
	var oMenu;
	oMenu = ctxt.Source;
	oMenu.Filter = siGeometryFilter ;
	
	oMenu.AddCommandItem("ApplySplatter (JScript Runtime)","ApplySplatterRuntime");	
	
	return true;
}

function ApplySplatterRuntime_Init( ctxt )
{
	var oCmd;
	oCmd = ctxt.Source;
	oCmd.ReturnValue = false;

	var oArgs;
	oArgs = oCmd.Arguments;
	oArgs.AddWithHandler("Targets","Collection");
			
	return true;
}

function ApplySplatterRuntime_Execute( in_Targets )
{	
	// Caller should pass or select object(s) to deform
	if ( in_Targets.Count == 0 )
		throw new Error( 0, "Need objects to apply operator to" );

	
	// Operator should be connected to all selected objects	
	for ( var i = 0 ; i < in_Targets.Count ; i++ )
	{
		oObject = in_Targets.Item(i) ;	

		// Note: for robust code we could test the type of object
		// here.  However because there is a filter on the menu the
		// extra error handling is skipped

		
		// Build the Custom Operator "on-the-fly"

		var op = XSIFactory.CreateScriptedOp( "MySplatter", 
								MySplatter_Update.toString(), 
								"JScript" );

		// define connections
		var ioport = op.addioport( oObject.activeprimitive, "Geom");
		var inport = op.addinputport( oObject.kinematics.global.posy, "InGPosY" );

		// define parameters
		var pdef = XSIFactory.CreateParamDef2( "SquishFactor", siDouble, 0.5, 0, 1 );

		op.addparameter(pdef);

		// connect operator	
		op.connect();
	}
}

// This is the Jscript implementation of the Splatter operator
function MySplatter_Update( ctx, out, InGeom, InGPosY )
{
	// Declare variables.
	var dSquishPnt,  i;

	// Get the squish factor.
	var dSquish = ctx.Parameters("SquishFactor").Value

	// Get the array of point positions.
	var aPnts = InGeom.Value.Geometry.Points.PositionArray.toArray();

	// Get the object//s global Y position.
	var dGPosYObj = InGPosY.Value;

	// For each point...
	for ( var i = 0; i < aPnts.length / 3; i++ )
	{
		// Compute the point's global Y position.
		var dGPosYPnt = aPnts[1 + (i*3)] + dGPosYObj;

		// If the point is below the Y=0 plane...
		if ( dGPosYPnt < 0 ) 
		{
			// Compute the squish factor for the point.
			var dSquishPnt = 1.0 - dGPosYPnt * dSquish;

			// Squish the point.
			aPnts[0 + (i*3)] = aPnts[0 + (i*3)] * dSquishPnt;
			aPnts[1 + (i*3)] = - dGPosYObj;
			aPnts[2 + (i*3)] = aPnts[2 + (i*3)] * dSquishPnt;
		}
	}

	// Update the object's point positions.
	out.Value.Geometry.Points.PositionArray = aPnts;

	return;
}


