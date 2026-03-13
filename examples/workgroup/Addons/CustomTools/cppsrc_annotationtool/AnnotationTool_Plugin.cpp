////////////////////////////////////////////////////////////////////////////////
//
//	File: CustomToolExamples_Plugin.cpp
//
//	Description: Custom tool plugin examples
//
////////////////////////////////////////////////////////////////////////////////
#include <xsi_context.h>
#include <xsi_pluginregistrar.h>
#include <xsi_status.h>

using namespace XSI; 

SICALLBACK XSILoadPlugin( PluginRegistrar& in_reg )
{
	in_reg.PutAuthor( L"Autodesk Consulting" );
	in_reg.PutName( L"Annotation Tool Plugin" );
	in_reg.PutVersion( 1, 0 );

	in_reg.RegisterTool(L"AnnotationTool" );

	//RegistrationInsertionPoint - do not remove this line

	return CStatus::OK;
}

SICALLBACK XSIUnloadPlugin( const PluginRegistrar& in_reg )
{
	return CStatus::OK;
}

