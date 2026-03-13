#include <xsi_application.h>
#include <xsi_context.h>
#include <xsi_pluginregistrar.h>
#include <xsi_status.h>
#include <xsi_factory.h>
#include <xsi_shaderdef.h>
#include <xsi_shaderparamdefoptions.h>
#include <xsi_shaderparamdefcontainer.h>
#include <xsi_metashaderrendererdef.h>
#include <xsi_valuemap.h>
using namespace XSI; 

SICALLBACK XSILoadPlugin( PluginRegistrar& in_reg )
{
	in_reg.PutAuthor(L"belzilm");
	in_reg.PutName(L"HWShaderPlugin");
	in_reg.PutVersion(1,0);
	in_reg.RegisterShader( "SimpleHWShader", 1, 0 );
	//RegistrationInsertionPoint - do not remove this line

	return CStatus::OK;
}

SICALLBACK XSIUnloadPlugin( const PluginRegistrar& in_reg )
{
	CString strPluginName;
	strPluginName = in_reg.GetName();
	Application().LogMessage(strPluginName + L" has been unloaded.",siVerboseMsg);
	return CStatus::OK;
}

SICALLBACK HWShaderPlugin_SimpleHWShader_1_0_DefineInfo( const CRef& in_ctxt )
{
	Context ctxt(in_ctxt);

	ctxt.PutAttribute("Category", "Realtime@200/Softimage Examples/HWShader" );	
	ctxt.PutAttribute("DisplayName", "SimpleHWShader" );
	
	return CStatus::OK;
}

SICALLBACK HWShaderPlugin_SimpleHWShader_1_0_Define( const CRef& in_ctxt )
{
	Context ctxt(in_ctxt);
	Application app;
	Factory fact = app.GetFactory();

	// Shader definition
	ShaderDef shaderDef = (XSI::CRef)ctxt.GetAttribute("Definition");	
	shaderDef.AddShaderFamily(siShaderFamilyRTShader);
	
	// Parameter definitions	
	ShaderParamDef paramDef;
	ShaderParamDefOptions paramOptions;
	ShaderParamDefContainer inParams = shaderDef.GetInputParamDefs();
	ShaderParamDefContainer outParams = shaderDef.GetOutputParamDefs();	
	
	// Input Parameter: input
	paramOptions = fact.CreateShaderParamDefOptions();
	paramOptions.SetLongName("input");
	paramOptions.SetAnimatable(true);
	paramOptions.SetTexturable(true);
	paramOptions.SetInspectable(true);	
	paramOptions.SetHardLimit(0, 1);
	paramOptions.SetSoftLimit(0, 1);
	paramOptions.SetDefaultValue(0);
	
	inParams.AddParamDef( "input", siShaderDataTypeScalar, paramOptions );	
	
	// Output Parameter: out
	paramOptions = fact.CreateShaderParamDefOptions();
	paramOptions.SetLongName("out");
	
	paramDef = outParams.AddParamDef( "out", siHWShaderPortType, paramOptions );
	paramDef.PutMainPort( false );	
	
	// Renderer definition
	MetaShaderRendererDef rendererDef = shaderDef.AddRendererDef( "OpenGL" );
	rendererDef.PutSymbolName( "SimpleHWShader" );
	rendererDef.PutCodePath( "" );
	
	ValueMap rendererDefOptions = rendererDef.GetRendererOptions();	
	rendererDefOptions.Set(siHWShaderVersionAttribute, CValue(siHWShaderV1) );
	
	return CStatus::OK;
}
