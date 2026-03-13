//--------------------------------------------------------------------------
// lightfilter.js: This example shows how to implement a custom filter as a 
// self-installing plug-in that handles light objects. The Light filter plug-in 
// is installed when the example workgroup is installed and automatically added 
// to the filter menu of the Scene Explorer view. The light filter plug-in 
// provides two filters: LightOnFilter and LightOffFilter. When the 
// LightOnFilter is the active selection filter, the Scene Explorer will only 
// display the light objects that have the intensity parameter value > 0. 
// When the LightOffFilter is the active selection filter, the Scene Explorer 
// will only display the light objects that have the intensity parameter value 
// set to 0. 
//
// For more details see the plug-in help file.
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// XSILoadPlugin: Installs the light filter plug-in.
//--------------------------------------------------------------------------
function XSILoadPlugin( in_reg )
{
	in_reg.Author = "Softimage Corp.";
	in_reg.Name = "Light Filter Plug-in";
	in_reg.Email = "";
	in_reg.URL = "";
	in_reg.Major = 1;
	in_reg.Minor = 0;

	in_reg.RegisterFilter("LightOnFilter",siFilter3DObject);
	in_reg.RegisterFilter("LightOffFilter",siFilter3DObject);
	//RegistrationInsertionPoint - do not remove this line

	return true;
}

//--------------------------------------------------------------------------
// IsALight: Returns true if the input object is a light.
//--------------------------------------------------------------------------
function IsALight( obj )
{
	return obj.IsClassOf( siLightID );
}

//--------------------------------------------------------------------------
// IsLightOn: Returns true if the input light object has the intensity parameter
// > 0.
//--------------------------------------------------------------------------
function IsLightOn( obj )
{
	var softLight = obj.Shaders("soft_light");
	var intensity = softLight.Intensity;
	if ( intensity.Value > 0 )
	{
		return true;
	}

	return false;
}

//--------------------------------------------------------------------------
// LightOnFilter_Match: Returns true if the input light object is ON (i.e.
// intensity parameter > 0).
//--------------------------------------------------------------------------
function LightOnFilter_Match( ctxt )
{
	Application.LogMessage("LightOnFilter_Match called");
	
	var light = ctxt.GetAttribute("Input");

	return IsALight( light ) && IsLightOn( light );
}

//--------------------------------------------------------------------------
// LightOffFilter_Match: Returns true if the input light object is OFF (i.e.
// intensity parameter = 0).
//--------------------------------------------------------------------------
function LightOffFilter_Match( ctxt )
{
	Application.LogMessage("LightOffFilter_Match called");

	var light = ctxt.GetAttribute("Input");
	
	return IsALight( light ) && !IsLightOn( light );
}
