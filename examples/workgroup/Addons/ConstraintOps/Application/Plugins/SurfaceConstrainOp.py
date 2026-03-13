#-------------------------------------------------------------------------------
# SurfaceConstrainOp.py: This is a Python example which creates an operator 
# that constrains the kinematic global position of a 3D object (the constrained) 
# to a surface. The constrained object position is based on the closest position 
# of an other 3D object (the controller) to the surface object. 
#
#	Copyright 2008 Autodesk, Inc.  All rights reserved.  
#	Use of this software is subject to the terms of the Autodesk license agreement 
#	provided at the time of installation or download, or which otherwise accompanies 
#	this software in either electronic or hard copy form.   
#-------------------------------------------------------------------------------

from win32com.client import constants
from win32com.client.dynamic import Dispatch 

#-------------------------------------------------------------------------------
# XSILoadPlugin: Entry-point called by Softimage when this file gets loaded. All 
# plugin items exposed here must be registered in this function. 
#
# in_reg: PluginRegistrar object required for registering the plugin 
# items and some information about this plugin.
#
# *note* This function is mandatory and must be implemented. The plugin will 
# not be loaded if this function is missing.
#-------------------------------------------------------------------------------

def XSILoadPlugin( in_reg ):

	# register plugin information
	in_reg.Author = "Softimage Corp." ;
	in_reg.Name = "Surface Constrain Operator plug-in";

	# set the version number of this plugin
	in_reg.Major = 1;
	in_reg.Minor = 0 ;

	# register the custom operator
	in_reg.RegisterOperator("SurfConstrainOp");

	# register the command to connect the SurfConstrainOp operator
	in_reg.RegisterCommand("CreateSurfConstrainOp");		
	
	# RegistrationInsertionPoint - do not remove this line

	strPluginName = in_reg.Name
	Application.LogMessage(str(strPluginName) + str(" has been loaded."),constants.siVerbose)

	return True;	


def CreateSurfConstrainOp_Init( ctxt ):

	oCmd = ctxt.Source;
	oCmd.Description = "Create an instance of SurfConstrainOp operator";
	oCmd.ReturnValue = True

	return True


def CreateSurfConstrainOp_Execute( ):

	Application.LogMessage("CreateSurfConstrainOp_Execute called",constants.siVerbose )

	oConstrained = Application.ActiveSceneRoot.AddNull("Constrained");
	oController = Application.ActiveSceneRoot.AddNull("Controller");
	oSphere = Application.ActiveSceneRoot.AddGeometry("Sphere","NurbsSurface","");
	
	# Create/connect the SurfConstrainOp Operator             
	ConnectToSurfConstrainOp( oController, oConstrained, oSphere )
	
	return True


#-------------------------------------------------------------------------------
# ConnectToSurfConstrainOp: Connect objects to Surf constrain operator
#-------------------------------------------------------------------------------
def ConnectToSurfConstrainOp( in_oController, in_oConstrained, in_oSphere ):
	    
	oSurfOp = XSIFactory.CreateObject("SurfConstrainOp")

	oGroup = oSurfOp.AddPortGroup( "Target" )

	oSurfOp.AddOutputPort( in_oConstrained.Kinematics.Global, "Constrained", oGroup.Index )

	oGroup1 = oSurfOp.AddPortGroup( "RefSurf" )

	oSurfOp.AddInputPort( in_oSphere.ActivePrimitive, "Surf", oGroup1.Index)

	oGroup2 = oSurfOp.AddPortGroup( "Controller" )

	oGlobal = in_oController.Kinematics.Global
	oSurfOp.AddInputPort( oGlobal.posx, "gNx", oGroup2.Index )
	oSurfOp.AddInputPort( oGlobal.posy, "gNy", oGroup2.Index )
	oSurfOp.AddInputPort( oGlobal.posz, "gNz", oGroup2.Index )
       
	oSurfOp.Connect()
	

#-------------------------------------------------------------------------------
# SurfConstrainOp_Init: Store math objects in the operator context to maximize
# performance
#-------------------------------------------------------------------------------
def SurfConstrainOp_Init( in_ctxt ):
	
	oDict = Dispatch( "Scripting.Dictionary" )

	oDict[ 'SurfPos' ] = XSIMath.CreateVector3()
	oDict[ 'OutPos' ] = XSIMath.CreateVector3()
	
	in_ctxt.UserData = oDict;
	
	return True
	

#-------------------------------------------------------------------------------
# SurfConstrainOp_Update
#-------------------------------------------------------------------------------
def SurfConstrainOp_Update( in_ctxt ):
	oDict = in_ctxt.UserData
	oKineState = in_ctxt.OutputTarget
	
	oGlobalTrans = oKineState.GetTransform2(None)

	oSurfPrim = in_ctxt.GetInputValue("Surf")
	gNx = in_ctxt.GetInputValue("gNx")
	gNy = in_ctxt.GetInputValue("gNy")
	gNz = in_ctxt.GetInputValue("gNz")
	
	oGeom = oSurfPrim.Geometry
	
	oSurfPos = oDict[ 'SurfPos' ]
	oSurfPos.Set( gNx, gNy, gNz )
	args = oGeom.GetClosestSurfacePosition2( oSurfPos );
	
	oOutPos = oDict[ 'OutPos' ]
	oOutPos.Set( args[4].X, args[4].Y, args[4].Z )
	oGlobalTrans.SetTranslation( oOutPos );
	oKineState.PutTransform2( None, oGlobalTrans );

	return True
	