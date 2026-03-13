#include <xsi_hardwareshadercontext.h>
#include <xsi_application.h>
#include <xsi_shader.h>

_SICALLBACK(bool) SimpleHWShader_opengl_Init( XSI::CRef in_ctx, void** io_pInstanceData )
{
	XSI::Application app;
	XSI::HardwareShaderContext hwsCtxt( in_ctx );
	XSI::Shader hwShader = hwsCtxt.GetShader();	

	app.LogMessage( "Initializing: " + hwShader.GetName() );

	return true;
}

_SICALLBACK(bool) SimpleHWShader_opengl_Execute( XSI::CRef in_ctx, void** io_pInstanceData )
{
	XSI::Application app;
	XSI::HardwareShaderContext hwsCtxt( in_ctx );
	XSI::Shader hwShader = hwsCtxt.GetShader();	

	app.LogMessage( "Drawing: " + hwShader.GetName() );
	
	hwsCtxt.DrawPrimitive( XSI::siOpenGL20 );

	return true;
}

_SICALLBACK(bool) SimpleHWShader_opengl_Term( void** io_pInstanceData )
{
	XSI::Application app;
	
	app.LogMessage( "Terminating: SimpleHWShader" );

	return true;
}

_SICALLBACK(bool) SimpleHWShader_opengl_GetAttributeList( XSI::CRef in_ctx, XSI::CHardwareAttributeArray& out_attribArray, void **io_pInstanceData )
{
	XSI::Application app;
	XSI::HardwareShaderContext hwsCtxt( in_ctx );
	XSI::Shader hwShader = hwsCtxt.GetShader();	

	app.LogMessage( "Getting attributes for: " + hwShader.GetName() );
	
	XSI::CHardwareAttribute hwAttrib;
	hwAttrib.PutSemanticValue( XSI::siHardwareSemanticPosition, XSI::siHardwareVertexPosition );
	out_attribArray.Add( hwAttrib );

	return true;
}
