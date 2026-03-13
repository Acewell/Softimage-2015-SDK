// CPPShaderExample
//
// This example demonstrates how to create a self-installing shaders
// definition plug-in that implements a lightmap as output and uses
// a tspace and an image lookup widget
//

// Standard plug-in includes
#include <xsi_application.h>
#include <xsi_context.h>
#include <xsi_pluginregistrar.h>
#include <xsi_status.h>

// Includes specific to this Shader Definition
#include <xsi_factory.h>
#include <xsi_shaderdef.h>
#include <xsi_shaderparamdefoptions.h>
#include <xsi_shaderparamdefcontainer.h>
#include <xsi_metashaderrendererdef.h>
#include <xsi_valuemap.h>

using namespace XSI;

SICALLBACK XSILoadPlugin( PluginRegistrar& in_reg )
{
	in_reg.PutAuthor(L"SDK Documentation");
	in_reg.PutName(L"CPPShaders");
	in_reg.PutVersion(1, 0);

	in_reg.RegisterShader(L"CPPColorSampler", 1, 0);

	return CStatus::OK;
}

SICALLBACK CPPShaders_CPPColorSampler_1_0_DefineInfo( const CRef& in_ctxt )
{
	Context ctxt(in_ctxt);

	ctxt.PutAttribute(L"Category", CValue(L"Example Shaders"));
	ctxt.PutAttribute(L"DisplayName", CValue(L"CPP Color Sampler"));

	return CStatus::OK;
}

SICALLBACK CPPShaders_CPPColorSampler_1_0_Define( const CRef& in_ctxt )
{
	Context ctxt(in_ctxt);
	Application app;

	ShaderDef sdef(ctxt.GetAttribute(L"Definition"));
	sdef.AddShaderFamily(siShaderFamilyLightmap, true);

	// PARAMETERS
	Factory fact = app.GetFactory();
	ShaderParamDefContainer inpdefs = sdef.GetInputParamDefs();
	ShaderParamDefContainer outpdefs = sdef.GetOutputParamDefs();

	// Input
	CRef popts = fact.CreateShaderParamDefOptions();
	ShaderParamDefOptions opts = ShaderParamDefOptions(popts);

	// Mark the image wanted as having to be writable, otherwise Softimage
	// will only give us a reference to a read-only image.
	opts.SetAttribute(siWritableImageAttribute,true);
	opts.SetTexturable(true);
	opts.SetInspectable(false);
	inpdefs.AddParamDef(L"texture", siShaderDataTypeImage, popts);


	CRef popts1 = fact.CreateShaderParamDefOptions();
	ShaderParamDefOptions opts1 = ShaderParamDefOptions(popts1);
	opts1.SetAttribute(siPropertyFilterAttribute, siUVPropertyFilter);
	opts1.SetLongName(L"Texture Space");
	inpdefs.AddParamDef(L"sample_space", siShaderDataTypeProperty, popts1);

	CRef popts2 = fact.CreateShaderParamDefOptions();
	ShaderParamDefOptions opts2 = ShaderParamDefOptions(popts2);
	opts2.SetAttribute(siReferenceFilterAttribute, siShaderReferenceFilter);
	opts2.SetTexturable(true);
	opts2.SetInspectable(false);
	inpdefs.AddParamDef(L"input", siShaderDataTypeReference, popts2);

	// Output
	CRef poutopts = fact.CreateShaderParamDefOptions();
	ShaderParamDefOptions outopts = ShaderParamDefOptions(poutopts);
	outopts.SetAttribute(CString(siCustomTypeNameAttribute), CValue(L"mrLmap"));
	outpdefs.AddParamDef(L"out", siShaderDataTypeCustom, poutopts);

	// Lightmap shaders need to define what data they need from the geometry
	// in order to generate the lightmap. The data are listed as a list of 
	// comma separated name/type pairs.
	sdef.GetAttributes().Set( 
		"mrOutStructDef", 
		L"point=vector,normal=vector,text=vector" );

	// RENDERERS
	MetaShaderRendererDef rend = sdef.AddRendererDef(L"mental ray");
	rend.PutSymbolName(L"sib_lightmap_color_sampler");
	rend.PutCodePath(L"{LIBS}/sibase.{EXT}");
	ValueMap ropts = rend.GetRendererOptions();
	ropts.Set(L"version", CValue(1));

	return CStatus::OK;
}

