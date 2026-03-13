# This callback registers the shader definition, assigning it a ClassName and version 
# number in the call to PluginRegistrar.RegisterShader. Together with the name of the
# plug-in, this sets up a ProgID of "PYSShaders.PYSModelMap.1.0".
def XSILoadPlugin( in_reg ) :
	in_reg.Author = "SDK Documentation"
	in_reg.Name = "PYSShaders"
	in_reg.Major = 1
	in_reg.Minor = 0

	in_reg.RegisterShader("PYSModelMap", 1, 0)
	return True


# Here the Category and DisplayName are set. Without these, the shader definition won't 
# appear in the render tree's preset manager. The Category you assign will match what
# appears in the preset manager. This example uses a single custom category, but you 
# could position it in one of the standard Softimage categories with a special string
# (eg., "Texture@100/Example/@300"). For more information see the ShaderDef.Category page
def PYSShaders_PYSModelMap_1_0_DefineInfo( in_ctxt ) :
	in_ctxt.SetAttribute("Category", "Example Shaders")
	in_ctxt.SetAttribute("DisplayName", "PYS Model Map")


# This is where the shader really gets fleshed out: the parameters, renderer, attributes, 
# etc. are defined on the ShaderDef object, which is available from the Context object via 
# the Definition attribute. This callback fires as soon as this shader is instantiated.
def PYSShaders_PYSModelMap_1_0_Define( in_ctxt ) :
	from win32com.client import constants as si
	
	# Get the ShaderDef object from the Definition attribute	
	oShaderDef = in_ctxt.GetAttribute("Definition")
	
	# Define the shader family for this definition. The shader family determines whether there 
	# are any restrictions on connecting nodes and each family can display its own color 
	oShaderDef.AddShaderFamily(si.siShaderFamilyTexture)
	
	
	#
	#	PARAMETER DEFINITIONS
	#
	# Get the ShaderParamDefContainer representing the input parameters
	oInputParams = oShaderDef.InputParamDefs

	# Set up shader parameter definition options to use with new input parameter. You define any
	# characteristics (eg., display name, default values, where and if it appears) of the parameter 
	# using these options, but you must set up your parameter definition options before calling the 
	# AddParamDef method since they are passed into the method and can't be modified afterwards. 
	oShaderInParamDefOptions = XSIFactory.CreateShaderParamDefOptions()
	oShaderInParamDefOptions.SetTexturable(False)			# will be associated parameter
	oShaderInParamDefOptions.SetHardLimit(0, 3)				# values 0 .. 3 will be mapped to combo box options
	oShaderInParamDefOptions.SetDefaultValue(0)				# first option will be selected by default

	# Add Type input parameter to definition using the options we already specified
	oParamDef = oInputParams.AddParamDef("Type", si.siShaderDataTypeInteger, oShaderInParamDefOptions)
	
	# Add TextureSpace input parameter to definition
	oShaderInParamDefOptions = XSIFactory.CreateShaderParamDefOptions()
	oShaderInParamDefOptions.SetTexturable(False)			# will be associated parameter
	oInputParams.AddParamDef("TextureSpace", si.siShaderDataTypeProperty, oShaderInParamDefOptions)
	
	# Add NormalMap input parameter to definition
	oShaderInParamDefOptions = XSIFactory.CreateShaderParamDefOptions()
	oShaderInParamDefOptions.SetTexturable(True)			# make it a connectable port
	oInputParams.AddParamDef("NormalMap", si.siShaderDataTypeColor4, oShaderInParamDefOptions)
	
	# Add VertexColor input parameter to definition
	oShaderInParamDefOptions = XSIFactory.CreateShaderParamDefOptions()
	oShaderInParamDefOptions.SetTexturable(False)			# will be associated parameter
	oShaderInParamDefOptions.SetAttribute(si.siPropertyFilterAttribute, si.siCAVPropertyFilter)	# CAV lookup property
	oInputParams.AddParamDef("VertexColor", si.siShaderDataTypeProperty, oShaderInParamDefOptions)
	
	
	# Add output parameter to definition
	oShaderOutParamDefOptions = XSIFactory.CreateShaderParamDefOptions()
	oOutputParams = oShaderDef.OutputParamDefs
	oOutputParams.AddParamDef("out", si.siShaderDataTypeColor4, oShaderOutParamDefOptions)
	
	
	# Set up the UI layout, including a combo box for the Mapping Type values (combo box options are
	# specified using a flat array of label-value pairs)
	aComboItems = ["Normals", "0", "Normals in Tangent Space", "1", "Tangents", "2", "Binormals", "3"]
	oPPGLayout = oShaderDef.PPGLayout
	oPPGLayout.Clear()
	oPPGLayout.AddEnumControl("Type", aComboItems, "Mapping Type")
	oPPGLayout.AddItem("TextureSpace", "Texture Space")
	oPPGLayout.AddItem("VertexColor", "Vertex Color")
	
	
	#
	#	RENDERER DEFINITIONS
	#
	# You need to set up at least one renderer definition for each shader definition.
	# Renderer definitions are available via the ShaderDef.RendererDefs property and
	# allow you to tell Softimage which renderer to use, which procedure to call, how
	# to set any renderer options, etc.
	oRendererDef = oShaderDef.AddRendererDef("mental ray")
	oRendererDef.SymbolName = "XSIModelMap"
	oRendererDef.CodePath = "{LIBS}/xsibase.{EXT}"
	
	# Set the version option
	oRendererOpts = oRendererDef.RendererOptions
	oRendererOpts.Set("version", 1)
	
	
	#
	#	SHADERBALL OPTIONS 
	#
	oShaderballOpts = oShaderDef.ShaderballOpts
	oShaderballOpts.Dimension = si.siShaderballDimSpatial
	
