#include <xsi_application.h>
#include <xsi_context.h>
#include <xsi_pluginregistrar.h>
#include <xsi_status.h>

using namespace XSI; 

extern XSI::CStatus RegisterConcatString( XSI::PluginRegistrar& in_reg );
extern XSI::CStatus RegisterFindString( XSI::PluginRegistrar& in_reg );
extern XSI::CStatus RegisterSplitString( XSI::PluginRegistrar& in_reg );
extern XSI::CStatus RegisterGetSubString( PluginRegistrar& in_reg );
extern XSI::CStatus RegisterStringToArray( PluginRegistrar& in_reg );
extern XSI::CStatus RegisterBuildArrayFromSet( PluginRegistrar& in_reg );

SICALLBACK XSILoadPlugin( PluginRegistrar& in_reg )
{
	in_reg.PutAuthor(L"Autodesk");
	in_reg.PutName(L"ICE String Library");
	in_reg.PutVersion(2,1);

	RegisterConcatString( in_reg );
	RegisterFindString( in_reg );
	RegisterGetSubString( in_reg );
	RegisterSplitString( in_reg );
	RegisterStringToArray( in_reg );
	RegisterBuildArrayFromSet( in_reg );	

	//RegistrationInsertionPoint - do not remove this line

	return CStatus::OK;
}