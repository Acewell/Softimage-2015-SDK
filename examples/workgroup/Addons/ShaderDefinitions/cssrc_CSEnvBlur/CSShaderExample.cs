// CSShaderExample
// 
// Tip: You need to compile the generated code before you can load the plug-in.
// After you compile the plug-in, you can load it by clicking Update All in the Plugin Manager.

using System;
using Softimage.XSIOM; // Softimage object model
using Softimage.XSIMath;
using Softimage.XSIUtil;

public class Base
{
	CXSIApplicationClass m_xsi;
	CXSIFactoryClass m_fact;
	CXSIUtilsClass m_utils;

	protected Base()
	{
		m_xsi = new CXSIApplicationClass();
		m_fact = new CXSIFactoryClass();
		m_utils = new CXSIUtilsClass();
	}
	protected bool Log(String str)
	{
		m_xsi.LogMessage(str, siSeverity.siVerbose);
		return true;
	}

	protected bool Info(String str)
	{
		m_xsi.LogMessage(str, siSeverity.siInfo);
		return true;
	}

	protected bool Error(String str)
	{
		m_xsi.LogMessage(str, siSeverity.siError);
		return true;
	}

	protected XSIApplication GetXSI()
	{
		return m_xsi;
	}

	protected XSIFactory GetFactory()
	{
		return m_fact;
	}

	protected XSIUtils GetUtils()
	{
		return m_utils;
	}	
}


public class XSIPlugin : Base
{
	public bool Load( PluginRegistrar in_reg )
	{
		in_reg.Author = "SDK Documentation";
		in_reg.Name = "CSShaderExample";
		in_reg.Major = 1;
		in_reg.Minor = 0;

        in_reg.RegisterShader("CSEnvBlur", 1, 0);

		return true;
	}

	public bool Unload( PluginRegistrar in_reg )
	{
		String strPluginName = null;
		strPluginName = in_reg.Name;
		Log(strPluginName + " has been unloaded.");
		return true;
	}
}

public class CSShaderExample_CSEnvBlur_1_0 : Base
{
    public bool DefineInfo(Context in_ctxt)
    {
        in_ctxt.SetAttribute("Category", "Example Shaders");
        in_ctxt.SetAttribute("DisplayName", "CS Environment Blur");

        return true;
    }

    public bool Define(Context in_ctxt)
    {
        CXSIFactoryClass oFactory = new CXSIFactoryClass();
        ShaderDef oShaderDef = (ShaderDef)in_ctxt.GetAttribute("Definition");
        oShaderDef.AddShaderFamily(StringModule.siShaderFamilyEnvironment, true);
        oShaderDef.AddShaderFamily(StringModule.siShaderFamilyTexture, false);

        // PARAMETERS
        ShaderParamDefOptions oParamDefOpts = oFactory.CreateShaderParamDefOptions();
        ShaderParamDefContainer oInParamDefs = oShaderDef.InputParamDefs;
        ShaderParamDefContainer oOutParamDefs = oShaderDef.OutputParamDefs;

        // Input
        oParamDefOpts.SetTexturable(true);
        oParamDefOpts.SetInspectable(false);
        oParamDefOpts.SetAttribute(StringModule.siShaderFamilyAttribute, 
            siShaderReferenceFilterType.siShaderReferenceFilter);
        oInParamDefs.AddParamDef("environment", siShaderParameterDataType.siShaderDataTypeReference, 
            oParamDefOpts);

        oParamDefOpts = oFactory.CreateShaderParamDefOptions();
        oParamDefOpts.SetLongName("Blur Amount");
        oParamDefOpts.SetTexturable(true);
        oParamDefOpts.SetDefaultValue(0.0);
        oParamDefOpts.SetHardLimit(0.0, null);
        oParamDefOpts.SetSoftLimit(0.0, 10.0);
        oInParamDefs.AddParamDef("blur", siShaderParameterDataType.siShaderDataTypeScalar, 
            oParamDefOpts);

        oParamDefOpts = oFactory.CreateShaderParamDefOptions();
        oParamDefOpts.SetTexturable(false);
        oParamDefOpts.SetInspectable(false);
        oParamDefOpts.SetDefaultValue(true);
        oInParamDefs.AddParamDef("mia_material_blur", siShaderParameterDataType.siShaderDataTypeBoolean, 
            oParamDefOpts);

        oParamDefOpts = oFactory.CreateShaderParamDefOptions();
        oParamDefOpts.SetLongName("Image Resolution");
        oParamDefOpts.SetDefaultValue(200);
        oParamDefOpts.SetHardLimit(0, null);
        oParamDefOpts.SetSoftLimit(0, 1000);
        oInParamDefs.AddParamDef("resolution", siShaderParameterDataType.siShaderDataTypeInteger, 
            oParamDefOpts);

        // Output
        oParamDefOpts = oFactory.CreateShaderParamDefOptions();
        oOutParamDefs.AddParamDef("out", siShaderParameterDataType.siShaderDataTypeColor4, oParamDefOpts);

        // RENDERERS
        MetaShaderRendererDef oRenderer = oShaderDef.AddRendererDef("mental ray");
        oRenderer.SymbolName = "mia_envblur";
        oRenderer.CodePath = "{LIBS}/architectural.{EXT}";
        ValueMap oRendOpts = oRenderer.RendererOptions;
        oRendOpts.Set("version", 1);

        return true;
    }
}
