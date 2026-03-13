// Splatter Plugin
// This is the Jscript Self-Installed Custom Operator version of Splatter.
// Unlike a runtime version, each instance of the splatter operator shares the
// same source code from this plug-in file.
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

function XSILoadPlugin( in_reg )
{
	in_reg.Author = "Softimage";
	in_reg.Name = "Splatter JScript Plugin";
	in_reg.Major = 1;
	in_reg.Minor = 0;

	in_reg.RegisterOperator("JScriptSplatter");	
	in_reg.RegisterMenu(siMenuTbDeformID,"ApplySplatterPlugin_Menu",false,false);

	//RegistrationInsertionPoint - do not remove this line

	return true;
}

function ApplySplatterPlugin_Menu_Init( ctxt )
{
	var oMenu;
	oMenu = ctxt.Source;
	oMenu.Filter = siGeometryFilter ;

	// We use a menu callback to create the Splatter operator.
	// An alternative way would be to create a specific 
	// "ApplySplatter" custom command, similar to the approach shown in the C++
	// version
	oMenu.AddCallbackItem("Splatter (JScript Plugin)","ApplySplatterMenu");	
	
	return true;
}

function ApplySplatterMenu( ctxt )
{
	// This function is called when the "Splatter (JScript Plugin)" menu
	// is clicked.

	var oTargets = Application.Selection
	
	// Loop so that we build a separate operator for each 
	// selected object
	for ( i = 0 ; i < oTargets.Count ; i++ )
	{
		oObject = oTargets.Item(i) ;

		// Note: for robust code we could test the type of object
		// here.  However because there is a filter on the menu the
		// extra error handling is skipped
		
		// This will be an input/output connection
		oObjectPrimitive = oObject.ActivePrimitive ;
		
		// This will be an input connection		
		oObjectPosYParam = oObject.kinematics.global.posy ;
		
		// Rather than build the connections using the methods
		// of the CustomOperator object, we use this convenient command.
							
		AddCustomOp( "JScriptSplatter",					// Type
					oObjectPrimitive,  				    // Output
					[ oObjectPrimitive,oObjectPosYParam ],  // Inputs
					"MySplatter" ) ;					// Name
				
	}		
}


// define parameters for Splatter
function JScriptSplatter_Define( ctx )
{
	op = ctx.Source ;
	var pdef = XSIFactory.CreateParamDef2( "SquishFactor", siDouble, 0.5, 0, 1 );
	op.addparameter(pdef);
}

function JScriptSplatter_DefineLayout( ctx )
{
	layout = ctx.Source
	layout.Clear() ;
	layout.AddItem( "SquishFactor" ) ;
	
	// We don't need to show the
	// Debug and AlwaysEvaluate parameters
	// but the Mute parameter is useful
	layout.AddItem( "Mute" ) ;	
}

// This is the Jscript implementation of the Splatter operator
function JScriptSplatter_Update( ctx )
{
	// Declare variables.
	var dSquishPnt,  i;

	// Get the squish factor.
	var dSquish = ctx.GetParameterValue("SquishFactor")

	// Get the array of point positions.
	var oInputPrimitive = ctx.GetInputValue( 0 ) ;
	var aPnts = oInputPrimitive.Geometry.Points.PositionArray.toArray();

	// Get the object//s global Y position.
	var dGPosYObj = ctx.GetInputValue( 1 );

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

	// Update the object//s point positions.
	ctx.OutputTarget.Geometry.Points.PositionArray = aPnts;

	return;
}


