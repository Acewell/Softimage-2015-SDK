/*

Custom Deform Operator
SDK Example

This example demonstrates how to create a scripted operator that is
built on the fly.  

The example is written as a self-installed plugin, which provides two custom commands.  
The first command "DemoCustomDeformExample" demonstrates the plugin.  
The second command, "ApplyCustomDeformExample" applies the new operator to the 
selected objects.

The second custom command appears as a menu entry in the Model\Deform menu so can
be used with the same sort of workflow as built-in deformations.

There is no SPDL file for the operator.  Instead it is created on the fly using the
Object Model (see ApplyCustomDeformExample_Execute).  The implementation of the operator
is the CustomDeformOp_Update method.

The operator has no parameters.  Instead the user controls it
by working with a custom property that is connected to the operator.
This allows the user interface for the plugin to use new features like the FCurve
parameter type.  There is no SPDL file for the custom property, instead it is defined
entirely in this script file.  An instance of the custom property is created whenever
the operator is applied and can be found nested underneath the Polygon Mesh object.

Notes on workflow used to create this example: 

1) Used custom property wizard to establish this file and the custom property.
Initially it only had two fcurve parameters.

2)Renamed name of the plugin and the filename.  Used plugin manager dialog update button 
to reload the new file.
 
3) Added the two custom commands, initial testing and fix syntax errors

4) Rather than continually use the Plugin Manager dialog to reload the script,
then execute my command manually, I decided to write a 2-line script
that I would run each time I want to test a update to my script:

Application.UpdatePlugins();
DemoCustomDeformExample(); 

I dragged this script to a toolbar so that each time I changed the script 
I could click a single button and see the results.  In effect I created a little "macro".

Note: In v5.0 self-installed plugin scripts are automatically unloaded/reloaded
each time you save it in the script editor.  So the first line of the
Macro above is not necessary if you use the Script Editor to develop your plugins.

5) Worked on the code to apply the operator to the correct objects, sending in an empty
implementation of CustomDeformOp_Update.  Used SDK explorer to verify that the operator 
was established as expected.  I used the CustomOperator topic in the reference extensively
and found an example under CustomOperator.AddIOPort that was close to what I wanted to do.
Note: I did not use the Script Operator editor at all to create this operator.

6) Started on the implementation of CustomDeformOp.  First I established local variables for all the 
objects I wanted to actually use: the Geometry, the FCurves etc.  I used LogMessage() a few
times to verify that I had the correct OM objects in those variable.

7) Implement the basic algorithm.  I referred to the Geometry object in the Object Model 
reference to find out how to set points, and the FCurve object to find out how to evaluate a
curve.

8) I tweaked the Custom Property.  I added two new parameters (amplitude and Z axis)
by modifying the script in this file.  I also modified the layout to show these parameters.  
When I was tweaking the layout code (see CustomDeformParams_DefineLayout) 
I would use the "Refresh" option in the context menu of the PPG to see my changes.

9) Next I finished the algorithm, fixing it so that it used a bounding box 
to convert between the fcurve range (0 to 100) and the points on the object.

10) Finally I added a menu entry for the custom command so that this new deformation
appears like the built-in deform operators.

The summarize: Once I had established a simple demo command and button to reload my plugin
I was able to make iterative changes to all aspects of the plugin - user interface,
algorithm, etc, without hastle.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   

*/

function XSILoadPlugin( in_reg )
{
	in_reg.Author = "Softimage";
	in_reg.Name = "CustomDeformExample";
	in_reg.Major = 1;
	in_reg.Minor = 1;
	
	in_reg.RegisterProperty( "CustomDeformParams" );	
	in_reg.RegisterCommand( "DemoCustomDeformExample" );
	in_reg.RegisterCommand( "ApplyCustomDeformExample" );
	in_reg.RegisterMenu( siMenuTbDeformID, "Custom Deform Example", false ) ;
	
	return true;
}

// Implementation of the DemoCustomDeformExample custom command
function DemoCustomDeformExample_Execute()
{
	// Set up an demo scene that shows the operator in action
	NewScene( null,false ) ;
	
	var oGrid = ActiveSceneRoot.AddGeometry( "Grid", "MeshSurface", "DemoGrid" ) ;
	var oSphere = ActiveSceneRoot.AddGeometry( "Sphere", "MeshSurface", "DemoSphere" ) ;
	
	var oObjs = new ActiveXObject( "XSI.Collection" );
	oObjs.Add( oGrid );
	oObjs.Add( oSphere );
	
	var oNewOps = ApplyCustomDeformExample( oObjs );
	
	for ( var i = 0 ; i < oNewOps.Count ; i++ )
	{
		Logmessage( "New operator has been created: " + oNewOps.Item(i).FullName ) ;
	}
	
	// For convenience show the Property Page for controlling the operator on the sphere
	// (there is also a custom property underneath the grid that can be viewed)
	InspectObj( oSphere + ".CustomDeformParams" ); 
}

// Definition of the ApplyCustomDeformExample custom command
function ApplyCustomDeformExample_Init( io_Context )
{
	var cmd = io_Context.Source ;
	cmd.ReturnValue = true ; // We will return the newly created operator objects

	// Our command will expect a collection of objects to apply.  If no
    // argument is specified explicitly then the handler
	// will pass the current Selection to ApplyCustomDeformExample_Execute
	cmd.Arguments.AddWithHandler("destobjs", siArgHandlerCollection);
}

// Implementation of the ApplyCustomDeformExample custom command
function ApplyCustomDeformExample_Execute( destobjs )
{
	// We will return newly created operator objects inside an XSICollection
	var oNewOperators = new ActiveXObject( "XSI.Collection" );

	try
	{
		// Apply the operator and custom property to each
		// polygon mesh in the input (which we expect to be an XSICollection
		// or Selection object)
		for ( i = 0 ; i < destobjs.Count ; i++ )
		{
			var oDestObj = destobjs.Item(i) ;
			
			if ( oDestObj.Type != "polymsh" )
			{
				LogMessage( oDestObj.FullName + 
                           " is not a suitable object for this operator", 
                           siError ) ;			
				continue ;
			}

			// Input and Output will be the Primitive (not directly the geometry)			
			var oPrim = oDestObj.ActivePrimitive ;
			
			// User configuration will come from this input
			var oCustomProperty = oDestObj.AddProperty( "CustomDeformParams", false ) ;
			
			var oNewOp = XSIFactory.CreateScriptedOp( 
							"CustomDeformOp", 
							CustomDeformOp_Update.toString(), 
							"Jscript" ) ;

			oNewOp.AddIOPort( oPrim ) ;	
			oNewOp.AddInputPort( oCustomProperty ) ;
			
			oNewOp.Connect( oDestObj, siConstructionModeDefault) ;
			
			oNewOperators.Add( oNewOp ) ;
		}
	}
	catch( e )
	{
		LogMessage( "Error applying operator:" + e.description, siError ) ;
	}

	return oNewOperators ;
}

// Implementation of the Scripted Operator.
// This function code is "stuffed" into the runtime scripted operator
// (see the call to XSIFactory.CreatedScriptedOp inside 
// ApplyCustomDeformExample_Execute)
function CustomDeformOp_Update( in_ctxt, out, in_geom, in_props  )
{
	//LogMessage( "Update called" ) ;

	// Create local variables with all the inputs and outputs	
	var oCustomProperty = in_props.Value ;
	
	var oXCurve = oCustomProperty.Parameters( "X_Curve" ).Value ;
	var oYCurve = oCustomProperty.Parameters( "Y_Curve" ).Value ;
	var oZCurve = oCustomProperty.Parameters( "Z_Curve" ).Value ;

	var amplitude = oCustomProperty.Parameters( "amplitude" ).Value ;

	var oInputGeom = in_geom.Value.Geometry ;	
	var oOutputGeom = out.Value.Geometry ;
		
	var aPos = oInputGeom.Points.PositionArray.toArray();

	var arrayPos = 0 ;
	var arraySize = aPos.length ;
				
	// Calculated bounding box
	var min_x = 1000, min_y = 1000, min_z = 1000 ;
	var max_x = -1000, max_y = -1000, max_z = -1000 ;
	
	while ( arrayPos < arraySize )
	{
		var x = aPos[arrayPos] ;
		var y = aPos[arrayPos+1] ;
		var z = aPos[arrayPos+2] ;

		if ( x < min_x ) min_x = x ;
		if ( x > max_x ) max_x = x ;
		if ( y < min_y ) min_y = y ;
		if ( y > max_y ) max_y = y ;
		if ( z < min_z ) min_z = z ;
		if ( z > max_z ) max_z = z ;		
	
		arrayPos += 3 ; 	
	}	
		
	var xlen = max_x - min_x ;
	var ylen = max_y - min_y ;
	var zlen = max_z - min_z ;
			
	// Avoid division by zero - flat objects
	// would hit this case
	if ( xlen < 0.0001 ) xlen = 0.0001 ; 
	if ( ylen < 0.0001 ) ylen = 0.0001 ; 
	if ( zlen < 0.0001 ) zlen = 0.0001 ; 
		
	// Calculate new positions	
	arrayPos = 0 ;
	while ( arrayPos < arraySize )
	{
		var x = aPos[arrayPos] ;
		var y = aPos[arrayPos+1] ;
		var z = aPos[arrayPos+2] ;
	
		// Use the bounding box to map each axis into the range
		// 0-100 
		
		var xpercent = ( 100 * ( x - min_x )) / xlen ;
		var ypercent = ( 100 * ( y - min_y )) / ylen ;
		var zpercent = ( 100 * ( z - min_z )) / zlen ;
		
		//logmessage( xpercent + " " + ypercent + " " + zpercent ) ;		
		
		aPos[arrayPos] = x + ( amplitude * oXCurve.Eval( xpercent ) ) ;
		aPos[arrayPos+1] = y + ( amplitude * oYCurve.Eval( ypercent ) ) ;
		aPos[arrayPos+2] = z + ( amplitude * oZCurve.Eval( zpercent ) );

		arrayPos += 3 ; 	
	}

	// Set the modified points back to the geometry	
	oOutputGeom.Points.PositionArray = aPos; 			
}


// Definition of the CustomDeformExample menu
function CustomDeformExample_Init( in_oCtxt )
{
	var menu = in_oCtxt.Source
	menu.Name = "&Custom Deform Example" ;
	menu.AddCommandItem( "&Apply Custom Deform", "ApplyCustomDeformExample" ) ;
}


//************************************************************
// CustomDeformParams - this is a custom property that
// controls the operator.  It holds 3 fcurves parameters
// and an amplitude parameter
//************************************************************

function CustomDeformParams_Define( io_Context )
{
	var oCustomProperty;
	oCustomProperty = io_Context.Source;
	var oParam = oCustomProperty.AddFCurveParameter( "X_Curve" );
	AddDefaultCurve( oParam ) ;
	
	oParam = oCustomProperty.AddFCurveParameter( "Y_Curve" );
	AddDefaultCurve( oParam ) ;
		
	oParam = oCustomProperty.AddFCurveParameter( "Z_Curve" );		
	AddDefaultCurve( oParam ) ;
	
	oCustomProperty.AddParameter2( "Amplitude", siDouble, 1, -100, 100, 0, 5 ) ;
}

// Helper function for CustomDeformParams_Define
function AddDefaultCurve( oParam )
{
	// When ever you create an fcurve parameter a simple
	// curve is added by default.
	// However for this example we want the curve to range in
	// value from 0 to 1
	
	var oCurve = oParam.Value ;
	
	oCurve.BeginEdit() ;
	oCurve.RemoveKeys() ;
	oCurve.AddKey( 0, 0 ) ;
	oCurve.AddKey( 25, 0.5 ) ;
	oCurve.AddKey( 50, 0.0 ) ;
	oCurve.AddKey( 75, 0.75 ) ;
	oCurve.AddKey( 100, 0.0 ) ;
	
	oCurve.EndEdit() ;
}

function CustomDeformParams_DefineLayout( io_Context )
{
	var oLayout,oItem;
	oLayout = io_Context.Source;
	oLayout.Clear(  );
	oLayout.AddItem( "amplitude" ); 
	AddFCurve( oLayout, "X_Curve" ) ;
	AddFCurve( oLayout, "Y_Curve" ) ;
	AddFCurve( oLayout, "Z_Curve" ) ;
}

// Helper function for _DefineLayout
function AddFCurve( oPPGLayout, strFCurveParamName )
{
	oPPGLayout.AddGroup( strFCurveParamName );
	oItem = oPPGLayout.AddItem( strFCurveParamName );
	oItem.SetAttribute( siUIValueOnly,true );
	oItem.SetAttribute( siUICX, 300 ) ;
	oItem.SetAttribute( siUICY, 200 ) ;	
	oPPGLayout.EndGroup(  );

}

