// SplatterCppPlugin
//
// This Plug-in contains the C++ implementation of 
// the splatter algorithm.  It contains the operator
// itself and a custom command "ApplySplatter"
// for creating the operator
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

#include <xsi_application.h>
#include <xsi_context.h>
#include <xsi_pluginregistrar.h>
#include <xsi_status.h>
#include <xsi_argument.h>
#include <xsi_command.h>
#include <xsi_primitive.h>
#include <xsi_geometry.h>
#include <xsi_point.h>
#include <xsi_customoperator.h>
#include <xsi_operatorcontext.h>
#include <xsi_x3dobject.h>
#include <xsi_factory.h>
#include <xsi_ppglayout.h>
#include <xsi_menu.h>
#include <xsi_portgroup.h>
#include <xsi_math.h>
#include <xsi_kinematics.h>
#include <xsi_kinematicstate.h>
#include <xsi_selection.h>
using namespace XSI; 
using namespace MATH; 

XSIPLUGINCALLBACK CStatus XSILoadPlugin( PluginRegistrar& in_reg )
{
	in_reg.PutAuthor(L"Softimage");
	in_reg.PutName(L"Splatter Cpp Plugin");
	in_reg.PutEmail(L"");
	in_reg.PutURL(L"");
	in_reg.PutVersion(2,0);

	in_reg.RegisterOperator(L"SplatterCpp");

	// Menu to make it easy to call the ApplySplatterCpp command
	in_reg.RegisterMenu(siMenuTbDeformID,L"ApplySplatterCpp_Menu",false,false);

	//RegistrationInsertionPoint - do not remove this line

	return CStatus::OK;
}

XSIPLUGINCALLBACK XSI::CStatus ApplySplatterCpp_Menu_Init( XSI::CRef& in_ref )
{
	Context ctxt = in_ref;
	Menu menu = ctxt.GetSource();

	// Use built-in filter so that menu is greyed out if selection isn't a geometry
	menu.PutFilter( siGeometryFilter ) ;

	MenuItem item;
	
	// Unlike the JScript version we have created a specific 
	// custom command for creating the C++ Splatter.
	// The results are almost the same.
	CStatus st = menu.AddCallbackItem( L"Splatter (C++)", L"ApplySplatterCpp", item );

	return st ;
}


XSIPLUGINCALLBACK CStatus ApplySplatterCpp( CRef& in_ctxt )
{
	Context ctxt( in_ctxt );
	Application app ;
	
	Selection selection = app.GetSelection() ;

	// User should have selected object(s) to deform
	if ( selection.GetCount() == 0 )
		return CStatus::InvalidArgument ;

	for ( LONG i = 0 ; i < selection.GetCount() ; i++ )
	{
		X3DObject oObject = (CRef) selection[i] ;

		// Note: for robust code we could test the type of object
		// here.  However because there is a filter on the menu the
		// extra error handling is skipped


		// Build the Custom Operator		
		
		// define inputs 
		CRefArray inputs(2) ;

		// Because this is a deform it is critical that we have both 
		// input and output connections to this Primitive
		inputs[0] = oObject.GetActivePrimitive() ; 

		Parameter posy = oObject.GetKinematics().GetGlobal().GetParameters().GetItem( L"posy" ) ;
		inputs[1] = posy ;

		// Easiest way to create the operator is like this: 
		//
		//    oObject.GetActivePrimitive().AddCustomOp( L"SplatterCpp", inputs ) ;
		//
		// However if we call the ADdCustomOp command we get the advantage of 
		// having the menu action logged in the script history:

		CValueArray aAddCustomOpArgs(5) ;
		aAddCustomOpArgs[0] = L"SplatterCpp" ;
		aAddCustomOpArgs[1] = oObject.GetActivePrimitive() ; // Outputs
		aAddCustomOpArgs[2] = inputs ;  
		CValue retOp ;

		app.ExecuteCommand( L"AddCustomOp", aAddCustomOpArgs, retOp ) ;
	}
	
	return CStatus::OK;
}


XSIPLUGINCALLBACK CStatus SplatterCpp_Define( CRef& in_ctxt )
{
	Context ctxt( in_ctxt ) ;
	CustomOperator op = ctxt.GetSource() ;

	CRef pdef = Application().GetFactory().CreateParamDef( L"SquishFactor", CValue::siDouble, 0.5, (LONG)0, (LONG)1 );

	Parameter newParam ;
	op.AddParameter(pdef, newParam);

	return CStatus::OK ;
}


// Use a custom layout to hide the debug and AlwaysEvaluate parameters
XSIPLUGINCALLBACK CStatus SplatterCpp_DefineLayout( CRef& in_ctxt )
{
	PPGLayout layout = Context(in_ctxt).GetSource();
	layout.Clear() ;
	layout.AddItem( L"SquishFactor" ) ;
	layout.AddItem( L"Mute" ) ;
	return CStatus::OK ;
}

XSIPLUGINCALLBACK CStatus SplatterCpp_Update( CRef& in_ctxt )
{
	OperatorContext ctxt( in_ctxt );

	// Get the squish factor.
	double dSquishFactor = ctxt.GetParameterValue(L"SquishFactor");

	///////////////////////////////////////////////////////////////
	// Inputs
	///////////////////////////////////////////////////////////////
	// Get the array of point positions. 
	Primitive inPrim( ctxt.GetInputValue( (LONG)0 ) );
	Geometry inGeom(inPrim.GetGeometry());

	if ( !inGeom.IsValid() )
	{
		return CStatus::InvalidArgument;
	}

	CVector3Array posArray(inGeom.GetPoints().GetPositionArray());

	// Get the object's global Y position.(ORIGINAL)
	double dGPosYObj = ctxt.GetInputValue( (LONG)1 ) ;

	///////////////////////////////////////////////////////////////
	// Splat!
	///////////////////////////////////////////////////////////////
	// Get the points from Vector3Array i.e. an posArray of CVector3 values
			
	for (long i=0; i<posArray.GetCount(); ++i )
	{		
		// Get the point's global Y position by adding the point's 
		// local Y position to the object's global Y position.
		double dGPosPoint = posArray[i].GetY() + dGPosYObj;

		// If the point's global Y position is less than zero...
		if (dGPosPoint < 0.0)
		{
			// Calculate the squish to apply to the point.
			double dSquish = 1.0 - dGPosPoint * dSquishFactor;

			// Squish the point.
			posArray[i].Set( posArray[i].GetX() * dSquish,
				-dGPosYObj, posArray[i].GetZ() * dSquish );
		}
	}

	///////////////////////////////////////////////////////////////
	// Output
	///////////////////////////////////////////////////////////////

	// Update the object's point position
	Primitive outPrim = ctxt.GetOutputTarget() ;
	Geometry outGeom(outPrim.GetGeometry());

	CStatus st;

	if ( (st=outGeom.GetPoints().PutPositionArray(posArray)) != CStatus::OK )
	{
		return st;
	}

	return CStatus::OK;
}

