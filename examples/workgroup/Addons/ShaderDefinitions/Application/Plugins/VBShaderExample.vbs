' VBShaders - tests various parameter types in JScript

function XSILoadPlugin( in_reg )
	in_reg.Author = "SDK Documentation"
	in_reg.Name = "VBShaders"
	in_reg.Major = 1
	in_reg.Minor = 0

	in_reg.RegisterShader "VBBionicVolume", 1, 0		' tests input struct + array of structs			
	XSILoadPlugin = true
end function

sub VBShaders_VBBionicVolume_1_0_DefineInfo( in_ctxt )
	in_ctxt.SetAttribute "Category", "Example Shaders"
	in_ctxt.SetAttribute "DisplayName", "VBS Fast Volume Effects"
end sub

sub VBShaders_VBBionicVolume_1_0_Define( in_ctxt )
	set oShaderDef = in_ctxt.GetAttribute("Definition")
	oShaderDef.AddShaderFamily siShaderFamilyVolume
	
	' PARAMETERS
	set oInParamDefs = oShaderDef.InputParamDefs
	set oOutParamDefs = oShaderDef.OutputParamDefs

	' Input
	set oParamDefOpts = XSIFactory.CreateShaderParamDefOptions()
	oParamDefOpts.SetTexturable false
	oParamDefOpts.SetInspectable true
	set oStructParamDef = oInParamDefs.AddParamDef("si_default", siShaderDataTypeStructure, oParamDefOpts)
	set oSubParamDefs = oStructParamDef.SubParamDefs

		' SubStructs
		set oParamDefOpts = XSIFactory.CreateShaderParamDefOptions()
		oParamDefOpts.SetTexturable false
		oParamDefOpts.SetInspectable true
		oParamDefOpts.SetDefaultValue 5.0
		oSubParamDefs.AddParamDef "start", siShaderDataTypeScalar, oParamDefOpts
		oParamDefOpts.SetDefaultValue 100.0
		oSubParamDefs.AddParamDef "stop", siShaderDataTypeScalar, oParamDefOpts
		oParamDefOpts.SetDefaultValue 1.0
		oSubParamDefs.AddParamDef "rate", siShaderDataTypeScalar, oParamDefOpts
		oParamDefOpts.SetDefaultValue 0.5
		oSubParamDefs.AddParamDef "transmit", siShaderDataTypeColor4, oParamDefOpts
		oParamDefOpts.SetDefaultValue false
		oSubParamDefs.AddParamDef "lightrays", siShaderDataTypeBoolean, oParamDefOpts

	set oParamDefOpts = XSIFactory.CreateShaderParamDefOptions()
	oParamDefOpts.SetTexturable false
	oParamDefOpts.SetInspectable true
	oParamDefOpts.SetAttribute siReferenceFilterAttribute, siLightReferenceFilter
	oInParamDefs.AddArrayParamDef "Lights", siShaderDataTypeReference, oParamDefOpts
	
	set oParamDefOpts = XSIFactory.CreateShaderParamDefOptions()
	oParamDefOpts.SetTexturable false
	oParamDefOpts.SetDefaultValue 0.5
	oParamDefOpts.SetHardLimit 0, 1000
	oParamDefOpts.SetSoftLimit 0, 1
	oInParamDefs.AddParamDef "Step", siShaderDataTypeScalar, oParamDefOpts
	
	oParamDefOpts.SetDefaultValue 20.0
	oParamDefOpts.SetSoftLimit 0, 100
	oInParamDefs.AddParamDef "Maximum_Length", siShaderDataTypeScalar, oParamDefOpts
	
	set oParamDefOpts = XSIFactory.CreateShaderParamDefOptions()
	oParamDefOpts.SetTexturable false
	oParamDefOpts.SetDefaultValue false
	oInParamDefs.AddParamDef "Smoke_On", siShaderDataTypeBoolean, oParamDefOpts
	
	oParamDefOpts.SetDefaultValue 2
	oInParamDefs.AddParamDef "Smoke_Complexity", siShaderDataTypeInteger, oParamDefOpts
	
	oParamDefOpts.SetDefaultValue 1.0
	oParamDefOpts.SetHardLimit 0, 1000
	oParamDefOpts.SetSoftLimit 0, 20
	oInParamDefs.AddParamDef "Smoke_Scale", siShaderDataTypeScalar, oParamDefOpts
	
	oParamDefOpts.SetDefaultValue 0.5
	oParamDefOpts.SetHardLimit 0, 1
	oParamDefOpts.SetSoftLimit 0, 1
	oInParamDefs.AddParamDef "Smoke_Amount", siShaderDataTypeScalar, oParamDefOpts
	
	oParamDefOpts.SetDefaultValue 1.0
	oParamDefOpts.SetHardLimit 0, 1000
	oParamDefOpts.SetSoftLimit 0, 10
	oInParamDefs.AddParamDef "Smoke_Speed", siShaderDataTypeScalar, oParamDefOpts
	
	set oParamDefOpts = XSIFactory.CreateShaderParamDefOptions()
	oParamDefOpts.SetTexturable false
	oParamDefOpts.SetDefaultValue false
	' flags = 1
	oInParamDefs.AddParamDef "Fade_On", siShaderDataTypeBoolean, oParamDefOpts
	
	oParamDefOpts.SetAnimatable false
	oParamDefOpts.SetInspectable false
	oParamDefOpts.SetDefaultValue 0
	oInParamDefs.AddParamDef "Instance1", siShaderDataTypeInteger, oParamDefOpts
	
	oInParamDefs.AddParamDef "Instance2", siShaderDataTypeInteger, oParamDefOpts

	set oParamDefOpts = XSIFactory.CreateShaderParamDefOptions()
	oParamDefOpts.SetTexturable false
	oParamDefOpts.SetDefaultValue false
	oInParamDefs.AddParamDef "Smoke_3D", siShaderDataTypeBoolean, oParamDefOpts
	
	' Output
	set oParamDefOpts = XSIFactory.CreateShaderParamDefOptions()
	oParamDefOpts.SetTexturable true
	set oStructParamDef = oOutParamDefs.AddParamDef("out", siShaderDataTypeColor4, oParamDefOpts)
	
	' PPGLayout
	set oPPGLayout = oShaderDef.PPGLayout
	oPPGLayout.AddTab "Bionic Volumic"
		oPPGLayout.AddItem "si_default", "Default Parameters"
	oPPGLayout.AddTab "Volumic"
		oPPGLayout.AddGroup "Lights"
			oPPGLayout.AddItem "Lights", "Lights light list"
		oPPGLayout.EndGroup 
		oPPGLayout.AddGroup "Sampling"
			oPPGLayout.AddItem "Step", "Feature Size"
			oPPGLayout.AddItem "Maximum_Length", "Maximum Ray Length"
		oPPGLayout.EndGroup 
	oPPGLayout.AddTab "Smoke"
			oPPGLayout.AddItem "Smoke_On", "Smoke"
			oPPGLayout.AddItem "Fade_On", "Depth Fading"
			oPPGLayout.AddItem "Smoke_3D", "3D Smoke"
			oPPGLayout.AddItem "Smoke_Scale", "Scale"
			oPPGLayout.AddItem "Smoke_Amount", "Intensity"
			oPPGLayout.AddItem "Smoke_Speed", "Animation Speed"
	
	' RENDERERS
	set oRenderer = oShaderDef.AddRendererDef("mental ray")
	oRenderer.SymbolName = "Bionic_Volume"
	oRenderer.CodePath = "{LIBS}/legacy.{EXT}"
	set oRendOpts = oRenderer.RendererOptions
	oRendOpts.Set "trace", true
	oRendOpts.Set "version", 1
end sub
