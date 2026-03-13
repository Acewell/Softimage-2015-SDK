#include <xsi_application.h>
#include <xsi_context.h>
#include <xsi_status.h>
#include <xsi_command.h>
#include <xsi_menu.h>
#include <xsi_utils.h>
#include <xsi_x3dobject.h>
#include <xsi_model.h>
#include <xsi_project.h>
#include <xsi_property.h>

using namespace XSI; 

// Helpers used to setup the simulation scene/data required for demoing the use of the File Path Sequence string node with custom nodes 
// for importing the simulation data into an ICE tree.
void NewScene( void )
{
	CValueArray args(2);
	CValue retval;
	args[1] = false;

	Application().ExecuteCommand( L"NewScene", args, retval );

	return;
}

CValue CreatePrim( const CString& in_presetobj, const CString& in_geometrytype, const CString& in_name, const CString& in_parent )
{
	CValueArray args(4);
	CValue retval;

	args[0]= in_presetobj;
	args[1]= in_geometrytype;
	args[2]= in_name;
	args[3]= in_parent;

	Application().ExecuteCommand( L"CreatePrim", args, retval );

	return retval;
}

CValue EmitPointsFromObject( const CValue& in_inputobj )
{
	CValueArray args(1);
	CValue retval;

	args[0]= in_inputobj;

	Application().ExecuteCommand( L"EmitPointsFromObject", args, retval );

	return retval;
}

CValue SetValue( const CString& in_target, const CValue& in_value, const CValue&  in_time )
{
	CValueArray args(3);
	CValue retval;

	args[0]= in_target;
	args[1]= in_value;
	args[2]= in_time;

	Application().ExecuteCommand( L"SetValue", args, retval );

	return retval;
}

void CacheObjectsIntoFile( const CValue&  in_objectstocache, const CValue& /*number*/ in_pathid, const CValue& /*number*/ in_firstframe, const CValue& /*number*/ in_lastframe, const CValue& /*number*/ in_framesperstep, bool in_overwrite, bool in_showprogressbar, const CString& in_attributes, const CString& in_version, const CString& in_alternativepath )
{
	CValueArray args(10);
	CValue retval;

	args[0]= in_objectstocache;
	args[1]= in_pathid;
	args[2]= in_firstframe;
	args[3]= in_lastframe;
	args[4]= in_framesperstep;
	args[5]= in_overwrite;
	args[6]= in_showprogressbar;
	args[7]= in_attributes;
	args[8]= in_version;
	args[9]= in_alternativepath;

	Application().ExecuteCommand( L"CacheObjectsIntoFile", args, retval );

	return;
}

void OpenScene( const CValue&  in_scenefilename, bool in_applyauxiliarydata )
{
	CValueArray args(2);
	CValue retval;

	args[0]= in_scenefilename;
	args[2]= in_applyauxiliarydata;

	Application().ExecuteCommand( L"OpenScene", args, retval );

	return;
}

// Menu call back for generating the simulation data files used in this demo.
XSIPLUGINCALLBACK XSI::CStatus OnGenerateData( XSI::CRef& in_ref )
{	
	Application app;

	// Load the simulation scene used for generating the data
	CString scenepath = CUtils::BuildPath( "[env XSISDK_ROOT]", "examples", "workgroup", "Addons", "CustomICENodes", "Data", "Project", "Scenes" );
	scenepath = CUtils::BuildPath( scenepath, "EmitParticles.scn" );

	OpenScene(scenepath, false);

	// Save the simulation data by exporting the PointPosition/Size/Color attributes from the ICEtree contained in EmitParticles.scn.
	CString userpath = app.GetInstallationPath( siUserPath );
	CString cachepath = CUtils::BuildPath( userpath, "Data", "PointCloudGeneratorFromFile_Cache" );

	Property playControl = Application().GetActiveProject().GetProperties().GetItem( L"Play Control" );	
	playControl.PutParameterValue( "Out", (LONG)200 );

	Property writeAnimCache = Application().GetActiveProject().GetProperties().GetItem( L"Write Animation Cache" );
	writeAnimCache.PutParameterValue( "FilePath", cachepath );
	writeAnimCache.PutParameterValue( "FileName", CString("data_##") );
	writeAnimCache.PutParameterValue( "FileType", (LONG)2 );
	
	// Note: the '.mycache' file extension will trigger the mycache event plugin to save the attributes.
	writeAnimCache.PutParameterValue( "FileTypeString", CString(".mycache") );

	CString filepathseq = writeAnimCache.GetParameterValue( "ResolvedFilePath" );
	
	// Save the attribute values for frames 1 to 200.
	CValue pointCloud = app.GetActiveSceneRoot().GetChildren().GetItem("PointCloud");	
	CacheObjectsIntoFile( pointCloud, 5, 1, 200, 1, true, true, "PointPosition,Color,Size", "", filepathseq);
	
	NewScene();
	
	return CStatus::OK;	
}

// Menu callback used for loading the PointCloudGeneratorFromFile1.scn demo scene. The scene uses the CloudGeneratorFromDataFile 
// custom node to set the cloud points and a SetAttributeValuesFromDataFile custom node to set all imported attribute values.
XSIPLUGINCALLBACK XSI::CStatus OnLoadDemoScene1( XSI::CRef& in_ref )
{	
	CString scenepath = CUtils::BuildPath( "[env XSISDK_ROOT]", "examples", "workgroup", "Addons", "CustomICENodes", "Data", "Project", "Scenes" );
	scenepath = CUtils::BuildPath( scenepath, "PointCloudGeneratorFromFile1.scn" );

	OpenScene(scenepath, false);
	
	// Set the 'File Path Sequence' string node to use the data files generated by the OnGenerateData menu callback
	CString cachepath = CUtils::BuildPath( Application().GetInstallationPath( siUserPath ), "Data", "PointCloudGeneratorFromFile_Cache" );	
	SetValue("pointcloud.pointcloud.ICETree.StringFilePathSequenceNode.value_filepathseq", cachepath, "");
	
	CString filename = "data_##.mycache";
	SetValue( "pointcloud.pointcloud.ICETree.StringFilePathSequenceNode.value_filename", filename, "");

	return CStatus::OK;	
}

// Menu callback used for loading the PointCloudGeneratorFromFile2.scn demo scene. This scene is similar to PointCloudGeneratorFromFile1.scn but
// uses a SetAttributeValueFromDataFile custom node instance per imported attribute to set the values.
XSIPLUGINCALLBACK XSI::CStatus OnLoadDemoScene2( XSI::CRef& in_ref )
{	
	CString scenepath = CUtils::BuildPath( "[env XSISDK_ROOT]", "examples", "workgroup", "Addons", "CustomICENodes", "Data", "Project", "Scenes" );
	scenepath = CUtils::BuildPath( scenepath, "PointCloudGeneratorFromFile2.scn" );

	OpenScene(scenepath, false);
	
	// Set the 'File Path Sequence' string node to use the data files generated by the OnGenerateData menu callback
	CString cachepath = CUtils::BuildPath( Application().GetInstallationPath( siUserPath ), "Data", "PointCloudGeneratorFromFile_Cache" );	
	SetValue("pointcloud.pointcloud.ICETree.StringFilePathSequenceNode.value_filepathseq", cachepath, "");
	
	CString filename = "data_##.mycache";
	SetValue( "pointcloud.pointcloud.ICETree.StringFilePathSequenceNode.value_filename", filename, "");

	return CStatus::OK;	
}

// Creates a menu for generating the simulation data and for loading the demo scene.
XSIPLUGINCALLBACK XSI::CStatus CloudGeneratorFromDataFileDemo_Init( XSI::CRef& in_ref )
{
	Context ctxt = in_ref;
	Menu menu = ctxt.GetSource();

	MenuItem item;
	menu.AddCallbackItem( L"Generate Simulation Data Files", L"OnGenerateData", item );
	menu.AddCallbackItem( L"Load Demo Scene 1", L"OnLoadDemoScene1", item );
	menu.AddCallbackItem( L"Load Demo Scene 2", L"OnLoadDemoScene2", item );

	return CStatus::OK;		
};
