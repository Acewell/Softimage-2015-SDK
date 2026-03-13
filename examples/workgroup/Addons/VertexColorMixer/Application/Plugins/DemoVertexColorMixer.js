// DemoVertexColorMixerPlugin
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

function XSILoadPlugin( in_reg )
{
	in_reg.Author = "Softimage";
	in_reg.Name = "DemoVertexColorMixerPlugin";
	in_reg.Major = 1;
	in_reg.Minor = 0;

	in_reg.RegisterCommand("DemoVertexColorMixer");	
	//RegistrationInsertionPoint - do not remove this line

	return true;
}

function DemoVertexColorMixer_Execute(  )
{
	//Demo Script for the vertex color mixer SDK Example 
	//(cpp version)
	//
	//Creates a simple scene and applies the operator
	//Requires that you have compiled and installed
	//the plugin

	var OpName = "vertexcolormixer_cpp";

	newscene( null, false );
	var oSphere = ActiveSceneRoot.AddGeometry( "Sphere", "MeshSurface" ) ;

	var oMixedResults = CreateVertexColorSupport(null, "Vertex_MixedResults", oSphere).Item(0);

	var oInputs = new ActiveXObject( "XSI.Collection" ) ;
	oInputs.Add( CreateVertexColorSupport(null, "Vertex_Color1", oSphere).Item(0) );
	oInputs.Add( CreateVertexColorSupport(null, "Vertex_Color2", oSphere).Item(0) );	
	
	SetDisplayMode("Camera", "constant");

	//Actually apply the operator, by calling the custom command
	//defined as part of this example
	try
	{
		var op = ApplyVertexColorMixer( OpName, oMixedResults,oInputs );
	}
	catch( e )
	{
		Logmessage( "Failed to apply " + OpName + " operator. " +
			"Please make sure it has been installed" ) ;
		throw e ;
	}

	// Paint some values on the input maps
	MakeLocal("sphere.Scene_Material", siDefaultPropagation);
	SetInstanceDataValue("sphere", "sphere.Scene_Material.CAV", "Vertex_Color1");
	SelectObj("sphere", null, true);
	PaintVertexColorTool(null, null, null);


	//Paint the three different maps with different colors
	var c1 = -16776961;
	var c2 = 2031615;


	PaintVertexColors("sphere", 
				Array(35, 38, 39, 41, 43, 45, 47, 49, 54), 
				Array(c1, c1, c1, c1, c1, c1, c1, c1, c1), 1, null);


	SetInstanceDataValue(null, "sphere.Scene_Material.CAV", "Vertex_Color2");
	PaintVertexColors("sphere", 
				Array(67, 69, 70, 71, 73, 75, 78, 79, 83, 85, 88), 
				Array(c2, c2, c2, c2, c2, c2, c2, c2, c2, c2, c2), 1, null);


	// Show the mixed results
	SetInstanceDataValue(null, "sphere.Scene_Material.CAV", "Vertex_MixedResults");


	// Advanced Note: This is a dynamic operator
	// so we can add more vertex color properties to it at any time,
	// by adding another instance of the input group
	oInput3 = CreateVertexColorSupport(null, "Vertex_Color3", oSphere).Item(0) ;
	op.ConnectToGroup( 1 /* index of the input group */, oInput3 ) ;
	
	// And similarily we can use op.DisconnectGroup to remove 
	// vertex color properties
	
	return true;
}

