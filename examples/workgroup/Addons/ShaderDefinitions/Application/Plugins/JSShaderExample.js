// This callback registers the shader definition, assigning it a ClassName and version 
// number in the call to PluginRegistrar.RegisterShader. Together with the name of the
// plug-in, this sets up a ProgID of "JSShaders.JSModelMap.1.0", for example.
function XSILoadPlugin( in_reg )
{
	in_reg.Author = "SDK Documentation";
	in_reg.Name = "JSShaders";
	in_reg.Major = 1;
	in_reg.Minor = 0;

	in_reg.RegisterShader("JSModelMap", 1, 0);			// creates drop-down list + tspace + cav lookup
	in_reg.RegisterShader("JSEnvBlur", 1, 0);			// creates reference:shader type						
	in_reg.RegisterShader("JSColorSampler", 1, 0);		// creates output lightmap + tspace + image lookup	
	in_reg.RegisterShader("JSBionicVolume", 1, 0);		// creates input struct + array of structs			
	return true;
}


/* 
	-----------------------------------------------------------------
*/
// Here the Category and DisplayName are set. Without these, the shader definition won't 
// appear in the render tree's preset manager. The Category you assign will match what
// appears in the preset manager. This example uses a single custom category, but you 
// could position it in one of the standard Softimage categories with a special string
// (eg., "Texture@100/Example/@300"). For more information see the ShaderDef.Category page
function JSShaders_JSModelMap_1_0_DefineInfo( in_ctxt ) 
{
	in_ctxt.SetAttribute("Category", "Example Shaders");
	in_ctxt.SetAttribute("DisplayName", "JS Model Map");
}

// This is where the shader really gets fleshed out: the parameters, renderer, attributes, 
// etc. are defined on the ShaderDef object, which is available from the Context object via 
// the Definition attribute. This callback fires as soon as this shader is instantiated.
function JSShaders_JSModelMap_1_0_Define( in_ctxt ) 
{
	// Get the ShaderDef object from the Definition attribute	
	var oShaderDef = in_ctxt.GetAttribute("Definition");
	
	// Define the shader family for this definition. The shader family determines whether there 
	// are any restrictions on connecting nodes and each family can display its own color 
	oShaderDef.AddShaderFamily(siShaderFamilyTexture);
	
	
	//
	//	PARAMETER DEFINITIONS
	//
	// Set up shader parameter definition options to use with new input parameter. You define the
	// display name and capabilities of the parameter using the options. Without a display name
	// the parameter will not appear in the shader node, so you must set up your parameter 
	// definition options before calling the AddParamDef method.
	var oParamDefOptions = XSIFactory.CreateShaderParamDefOptions();
	oParamDefOptions.SetTexturable(false);								// PPGLayout only
	oParamDefOptions.SetInspectable(true);
	oParamDefOptions.SetHardLimit(0, 3);
	oParamDefOptions.SetDefaultValue(0);
	
	// Add Type input parameter to definition
	var oInputParams = oShaderDef.InputParamDefs;
	oInputParams.AddParamDef("Type", siShaderDataTypeInteger, oParamDefOptions);
	
	// Add TextureSpace input parameter to definition
	oInputParams = oShaderDef.InputParamDefs;
	oInputParams.AddParamDef("TextureSpace", siShaderDataTypeProperty, oParamDefOptions);
	
	// Add NormalMap input parameter to definition
	oParamDefOptions.SetTexturable(true)								// connectable
	oInputParams = oShaderDef.InputParamDefs;
	oInputParams.AddParamDef("NormalMap", siShaderDataTypeColor4, oParamDefOptions);
	
	// Add VertexColor input parameter to definition
	oParamDefOptions.SetTexturable(false);								// PPGLayout only
	oParamDefOptions.SetInspectable(true);
	oParamDefOptions.SetAttribute(siPropertyFilterAttribute, siCAVPropertyFilter);
	oInputParams = oShaderDef.InputParamDefs;
	oInputParams.AddParamDef("VertexColor", siShaderDataTypeProperty, oParamDefOptions);
	
	
	// Add output parameter to definition
	oParamDefOptions = XSIFactory.CreateShaderParamDefOptions();		// reset options for output
	var oOutputParams = oShaderDef.OutputParamDefs;
	oOutputParams.AddParamDef("out", siShaderDataTypeColor4, oParamDefOptions);
	
	
	// Set up the layout on the associated property page, including a combo box for the Mapping Type values
	var oPPGLayout = oShaderDef.PPGLayout;
	oPPGLayout.Clear();
	var aOptions = new Array("Normals", "0", "Normals in Tangent Space", "1", "Tangents", "2", "Binormals", "3");
	oPPGLayout.AddEnumControl("Type", aOptions, "Mapping Type");
	oPPGLayout.AddItem("TextureSpace", "Texture Space");
	oPPGLayout.AddItem("VertexColor", "Vertex Color");
	
	
	//
	//	RENDERER DEFINITIONS
	//
	// You need to set up at least one renderer definition for each shader definition.
	// Renderer definitions are available via the ShaderDef.RendererDefs property and
	// allow you to tell Softimage which renderer to use, which procedure to call, how
	// to set any renderer options, etc.
	oRendererDef = oShaderDef.AddRendererDef("mental ray");
	oRendererDef.SymbolName = "XSIModelMap";
	oRendererDef.CodePath = "{LIBS}/xsibase.{EXT}";
	
	// Set the version option
	oRendererOpts = oRendererDef.RendererOptions;
	oRendererOpts.Set("version", 1);
	
	
	//
	//	SHADERBALL OPTIONS 
	//
	oShaderballOpts = oShaderDef.ShaderballOpts;
	oShaderballOpts.Dimension = siShaderballDimSpatial;
}



/* 
	-----------------------------------------------------------------
*/
function JSShaders_JSBionicVolume_1_0_DefineInfo( in_ctxt )
{
	in_ctxt.SetAttribute("Category", "Example Shaders");
	in_ctxt.SetAttribute("DisplayName", "JS Fast Volume Effects");
}

function JSShaders_JSBionicVolume_1_0_Define( in_ctxt )
{
	var oShaderDef = in_ctxt.GetAttribute("Definition");
	oShaderDef.AddShaderFamily(siShaderFamilyVolume);
	
	// PARAMETERS
	var oParamDefOpts = XSIFactory.CreateShaderParamDefOptions();

	// Input
	var oInParamDefs = oShaderDef.InputParamDefs;
	oParamDefOpts.SetTexturable(false);
	var oStructParamDef = oInParamDefs.AddParamDef("si_default", siShaderDataTypeStructure, oParamDefOpts);
	var oSubParamDefs = oStructParamDef.SubParamDefs;

		// SubStructs
		oParamDefOpts = XSIFactory.CreateShaderParamDefOptions();
		oParamDefOpts.SetTexturable(false);
		oParamDefOpts.SetDefaultValue(5.0);
		oSubParamDefs.AddParamDef("start", siShaderDataTypeScalar, oParamDefOpts);
		oParamDefOpts.SetDefaultValue(100.0);
		oSubParamDefs.AddParamDef("stop", siShaderDataTypeScalar, oParamDefOpts);
		oParamDefOpts.SetDefaultValue(1.0);
		oSubParamDefs.AddParamDef("rate", siShaderDataTypeScalar, oParamDefOpts);
		oParamDefOpts.SetDefaultValue(0.5);
		oSubParamDefs.AddParamDef("transmit", siShaderDataTypeColor4, oParamDefOpts);
		oParamDefOpts.SetDefaultValue(false);
		oSubParamDefs.AddParamDef("lightrays", siShaderDataTypeBoolean, oParamDefOpts);

	oParamDefOpts = XSIFactory.CreateShaderParamDefOptions();
	oParamDefOpts.SetTexturable(false);
	oParamDefOpts.SetInspectable(true);
	// Persistable = true?
	oParamDefOpts.SetAttribute(siReferenceFilterAttribute, siLightReferenceFilter);
	oInParamDefs.AddArrayParamDef("Lights", siShaderDataTypeReference, oParamDefOpts);
	
	oParamDefOpts = XSIFactory.CreateShaderParamDefOptions();
	oParamDefOpts.SetTexturable(false);
	oParamDefOpts.SetDefaultValue(0.5);
	oParamDefOpts.SetHardLimit(0, 1000);
	oParamDefOpts.SetSoftLimit(0, 1);
	// flags = 1
	oInParamDefs.AddParamDef("Step", siShaderDataTypeScalar, oParamDefOpts);
	
	oParamDefOpts.SetDefaultValue(20.0);
	oParamDefOpts.SetSoftLimit(0, 100);
	oInParamDefs.AddParamDef("Maximum_Length", siShaderDataTypeScalar, oParamDefOpts);
	
	oParamDefOpts = XSIFactory.CreateShaderParamDefOptions();
	oParamDefOpts.SetTexturable(false);
	oParamDefOpts.SetDefaultValue(false);
	// flags = 1
	oInParamDefs.AddParamDef("Smoke_On", siShaderDataTypeBoolean, oParamDefOpts);
	
	oParamDefOpts.SetDefaultValue(2);
	oInParamDefs.AddParamDef("Smoke_Complexity", siShaderDataTypeInteger, oParamDefOpts);
	
	oParamDefOpts.SetDefaultValue(1.0);
	oParamDefOpts.SetHardLimit(0, 1000);
	oParamDefOpts.SetSoftLimit(0, 20);
	oInParamDefs.AddParamDef("Smoke_Scale", siShaderDataTypeScalar, oParamDefOpts);
	
	oParamDefOpts.SetDefaultValue(0.5);
	oParamDefOpts.SetHardLimit(0, 1);
	oParamDefOpts.SetSoftLimit(0, 1);
	oInParamDefs.AddParamDef("Smoke_Amount", siShaderDataTypeScalar, oParamDefOpts);
	
	oParamDefOpts.SetDefaultValue(1.0);
	oParamDefOpts.SetHardLimit(0, 1000);
	oParamDefOpts.SetSoftLimit(0, 10);
	oInParamDefs.AddParamDef("Smoke_Speed", siShaderDataTypeScalar, oParamDefOpts);
	
	oParamDefOpts = XSIFactory.CreateShaderParamDefOptions();
	oParamDefOpts.SetTexturable(false);
	oParamDefOpts.SetDefaultValue(false);
	// flags = 1
	oInParamDefs.AddParamDef("Fade_On", siShaderDataTypeBoolean, oParamDefOpts);
	
	oParamDefOpts.SetAnimatable(false);
	oParamDefOpts.SetInspectable(false);
	// flags = 1
	// readable = off
	// writable = off
	oParamDefOpts.SetDefaultValue(0);
	oInParamDefs.AddParamDef("Instance1", siShaderDataTypeInteger, oParamDefOpts);
	
	oInParamDefs.AddParamDef("Instance2", siShaderDataTypeInteger, oParamDefOpts);

	oParamDefOpts = XSIFactory.CreateShaderParamDefOptions();
	oParamDefOpts.SetTexturable(false);
	oParamDefOpts.SetDefaultValue(false);
	// flags = 1
	oInParamDefs.AddParamDef("Smoke_3D", siShaderDataTypeBoolean, oParamDefOpts);
	
	// Output
	var oOutParamDefs = oShaderDef.OutputParamDefs;
	var oStructParamDef = oOutParamDefs.AddParamDef("out", siShaderDataTypeColor4, oParamDefOpts);
	
	// PPGLayout
	var oPPGLayout = oShaderDef.PPGLayout;
	oPPGLayout.AddTab("Bionic Volumic");
		oPPGLayout.AddItem("si_default", "Default Parameters");
	oPPGLayout.AddTab("Volumic");
		oPPGLayout.AddGroup("Lights");
			oPPGLayout.AddItem("Lights", "Lights light list");
		oPPGLayout.EndGroup();
		oPPGLayout.AddGroup("Sampling");
			oPPGLayout.AddItem("Step", "Feature Size");
			oPPGLayout.AddItem("Maximum_Length", "Maximum Ray Length");
		oPPGLayout.EndGroup();
	oPPGLayout.AddTab("Smoke");
			oPPGLayout.AddItem("Smoke_On", "Smoke");
			oPPGLayout.AddItem("Fade_On", "Depth Fading");
			oPPGLayout.AddItem("Smoke_3D", "3D Smoke");
			oPPGLayout.AddItem("Smoke_Scale", "Scale");
			oPPGLayout.AddItem("Smoke_Amount", "Intensity");
			oPPGLayout.AddItem("Smoke_Speed", "Animation Speed");
	
	// RENDERERS
	var oRenderer = oShaderDef.AddRendererDef("mental ray");
	oRenderer.SymbolName = "Bionic_Volume";
	oRenderer.CodePath = "{LIBS}/legacy.{EXT}";
	var oRendOpts = oRenderer.RendererOptions;
	oRendOpts.Set("trace", true);
	oRendOpts.Set("version", 1);
}


/* 
	-----------------------------------------------------------------
*/
function JSShaders_JSColorSampler_1_0_DefineInfo( in_ctxt )
{
	in_ctxt.SetAttribute("Category", "Example Shaders");
	in_ctxt.SetAttribute("DisplayName", "JS Color Sampler");
}

function JSShaders_JSColorSampler_1_0_Define( in_ctxt )
{
	var oShaderDef = in_ctxt.GetAttribute("Definition");
	oShaderDef.AddShaderFamily(siShaderFamilyLightmap);
	
	// PARAMETERS
	var oParamDefOpts = XSIFactory.CreateShaderParamDefOptions();
	
	// Input
	var oInParamDefs = oShaderDef.InputParamDefs;
	oParamDefOpts.SetTexturable(true);
	oParamDefOpts.SetInspectable(false);
	var oParamDef = oInParamDefs.AddParamDef("texture", siShaderDataTypeImage, oParamDefOpts);
	
	// Mark the image wanted as having to be writable, otherwise Softimage
	// will only give us a reference to a read-only image.
	oParamDef.Attributes.Set(siWritableImageAttribute, true);
	
	oParamDefOpts = XSIFactory.CreateShaderParamDefOptions();
	oParamDefOpts.SetAttribute(siPropertyFilterAttribute, siUVPropertyFilter);
	oParamDefOpts.SetLongName("Texture Space");
	oInParamDefs.AddParamDef("sample_space", siShaderDataTypeProperty, oParamDefOpts);
	
	oParamDefOpts = XSIFactory.CreateShaderParamDefOptions();
	oParamDefOpts.SetAttribute(siReferenceFilterAttribute, siShaderReferenceFilter);
	oParamDefOpts.SetTexturable(true);
	oParamDefOpts.SetInspectable(false);
	oInParamDefs.AddParamDef("input", siShaderDataTypeReference, oParamDefOpts);
	
	// Output
	oParamDefOpts = XSIFactory.CreateShaderParamDefOptions();
	oParamDefOpts.SetAttribute(siCustomTypeNameAttribute, "mrLmap");
	var oOutParamDefs = oShaderDef.OutputParamDefs;
	oOutParamDefs.AddParamDef("out", siShaderDataTypeCustom, oParamDefOpts);
	
	// Lightmap shaders need to define what data they need from the geometry
	// in order to generate the lightmap. The data are listed as a list of 
	// comma separated name/type pairs.
	oShaderDef.Attributes.Set("mrOutStructDef", "point=vector,normal=vector,text=vector");

	// RENDERERS
	var oRenderer = oShaderDef.AddRendererDef("mental ray");
	oRenderer.SymbolName = "sib_lightmap_color_sampler";
	oRenderer.CodePath = "{LIBS}/sibase.{EXT}";
	var oRendOpts = oRenderer.RendererOptions;
	oRendOpts.Set("version", 1);
}


/* 
	-----------------------------------------------------------------
*/
function JSShaders_JSEnvBlur_1_0_DefineInfo( in_ctxt )
{
	in_ctxt.SetAttribute("Category", "Example Shaders");
	in_ctxt.SetAttribute("DisplayName", "JS Environment Blur");
}

function JSShaders_JSEnvBlur_1_0_Define( in_ctxt )
{
	var oShaderDef = in_ctxt.GetAttribute("Definition");
	oShaderDef.AddShaderFamily(siShaderFamilyEnvironment);
	oShaderDef.AddShaderFamily(siShaderFamilyTexture, false);
	
	// PARAMETERS
	var oParamDefOpts = XSIFactory.CreateShaderParamDefOptions();
	
	// Input
	oParamDefOpts.SetTexturable(true);
	oParamDefOpts.SetInspectable(false);
	oParamDefOpts.SetAttribute(siShaderFamilyAttribute, siShaderReferenceFilter);
	var oInParamDefs = oShaderDef.InputParamDefs;
	oInParamDefs.AddParamDef("environment", siShaderDataTypeReference, oParamDefOpts);
	
	oParamDefOpts = XSIFactory.CreateShaderParamDefOptions();
	oParamDefOpts.SetLongName("Blur Amount");
	oParamDefOpts.SetTexturable(true);
	oParamDefOpts.SetDefaultValue(0.0);
	oParamDefOpts.SetHardLimit(0.0, null);
	oParamDefOpts.SetSoftLimit(0.0, 10.0);
	oInParamDefs.AddParamDef("blur", siShaderDataTypeScalar, oParamDefOpts);

	oParamDefOpts = XSIFactory.CreateShaderParamDefOptions();
	oParamDefOpts.SetTexturable(false);
	oParamDefOpts.SetInspectable(false);
	oParamDefOpts.SetDefaultValue(true);
	oInParamDefs.AddParamDef("mia_material_blur", siShaderDataTypeBoolean, oParamDefOpts);

	oParamDefOpts = XSIFactory.CreateShaderParamDefOptions();
	oParamDefOpts.SetLongName("Image Resolution");
	oParamDefOpts.SetDefaultValue(200);
	oParamDefOpts.SetHardLimit(0, null);
	oParamDefOpts.SetSoftLimit(0, 1000);
	oInParamDefs.AddParamDef("resolution", siShaderDataTypeInteger, oParamDefOpts);
	
	// Output
	oParamDefOpts = XSIFactory.CreateShaderParamDefOptions();
	var oOutParamDefs = oShaderDef.OutputParamDefs;
	oOutParamDefs.AddParamDef("out", siShaderDataTypeColor4, oParamDefOpts);

	// RENDERERS
	var oRenderer = oShaderDef.AddRendererDef("mental ray");
	oRenderer.SymbolName = "mia_envblur";
	oRenderer.CodePath = "{LIBS}/architectural.{EXT}";
	var oRendOpts = oRenderer.RendererOptions;
	oRendOpts.Set("version", 1);
}
