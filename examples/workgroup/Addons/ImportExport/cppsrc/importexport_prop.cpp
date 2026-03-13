//*****************************************************************************
/*!	\file importexport_prop.cpp
 	\brief Defines the callbacks that define the layout and behavior of the 
 	Import Export Demo property page.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
 
 */
//*****************************************************************************

#include <xsi_application.h>
#include <xsi_model.h>
#include <xsi_customproperty.h>
#include <xsi_parameter.h>
#include <xsi_string.h>
#include <xsi_griddata.h>
#include <xsi_value.h>
#include <xsi_ppglayout.h>
#include <xsi_ppgeventcontext.h>

#define LABEL_MIN 140
#define LABEL_RATIO 40

//*****************************************************************************
/*!	Helper function for accessing the Import Export Demo custom property.
 */
//*****************************************************************************
XSI::CustomProperty GetImportExportProp()
{	
	XSI::Application app;
	XSI::Model root = app.GetActiveSceneRoot();
	XSI::CustomProperty prop = root.GetProperties().GetItem(L"DemoImportExportProp");
	if (!prop.IsValid())
	{
		prop = root.AddProperty( L"DemoImportExportProp" );
	}
	return prop;
}

//*****************************************************************************
/*!	Helper function for getting a parameter from the custom property.
	\param in_strName Name of the option to get.
 */
//*****************************************************************************
XSI::Parameter GetImportExportOption( const XSI::CString& in_strName )
{
	XSI::CustomProperty pset = GetImportExportProp();
	if (!pset.IsValid()) return XSI::CRef();
	
	XSI::Parameter param = pset.GetParameters().GetItem(in_strName);
	
	if (!param.IsValid())
	{	
		pset.AddParameter(
			in_strName,
			XSI::CValue::siInt4,
			XSI::siReadOnly,
			L"",
			L"",
			(LONG)0,
			(LONG)0,
			(LONG)100,
			(LONG)0,
			(LONG)100,
			param);	
	}
	return param;
}

//*****************************************************************************
/*!	Callback that defines the parameters (options) of the custom property.
	\param in_ctxt The context that encapsulates the custom property to initialize.
 */
//*****************************************************************************

XSIPLUGINCALLBACK
XSI::CStatus DemoImportExportProp_Define( XSI::CRef& in_ctxt )
{
	XSI::Context ctxt( in_ctxt );
	XSI::CustomProperty pset( ctxt.GetSource() );
	
	XSI::Parameter param;
	pset.AddParameter(L"ConstMode",XSI::CValue::siInt4,XSI::siPersistable,L"",L"",(LONG)0,(LONG)0,(LONG)4,(LONG)0,(LONG)4,param);
	pset.AddParameter(L"Subd_level",XSI::CValue::siInt4,XSI::siPersistable,L"",L"",(LONG)0,(LONG)0,(LONG)6,(LONG)0,(LONG)6,param);
	pset.AddParameter(L"Subd_type",XSI::CValue::siInt4,XSI::siPersistable,L"",L"",(LONG)0,(LONG)0,(LONG)3,(LONG)0,(LONG)3,param);
	pset.AddParameter(L"DiscAngle",XSI::CValue::siDouble,XSI::siPersistable,L"",L"",(LONG)0,(LONG)0,(LONG)360,(LONG)0,(LONG)360,param);
	pset.AddParameter(L"UseDisc",XSI::CValue::siBool, XSI::siPersistable, L"", L"", false, param );	
	pset.AddParameter(L"MeshChunkSize",XSI::CValue::siInt4,XSI::siPersistable,L"",L"",(LONG)100,param);

	pset.AddParameter(L"ExportFile",XSI::CValue::siString, XSI::siPersistable, L"", L"", L"", param );

	XSI::Application app;
	XSI::CString strDefaultFile( app.GetInstallationPath( XSI::siUserPath ) );
#ifdef unix
	strDefaultFile += L"/demo_mesh_data.txt";
#else
	strDefaultFile += L"\\demo_mesh_data.txt";
#endif
	param.PutValue( strDefaultFile );
	
	pset.AddParameter(L"ImportFile",XSI::CValue::siString, XSI::siPersistable, L"", L"", L"", param );
	param.PutValue( strDefaultFile );	

	return XSI::CStatus::OK;
}

//*****************************************************************************
/*!	Callback that defines the layout of controls on the property page.
	\param in_ctxt The context that encapsulates the custom property layout to 
	initialize.
 */
//*****************************************************************************
XSIPLUGINCALLBACK
XSI::CStatus DemoImportExportProp_DefineLayout( XSI::CRef& in_ctxt )
{	
	XSI::Context ctxt(in_ctxt);
	XSI::PPGLayout ppg = ctxt.GetSource() ;

	ppg.Clear();

	// define the export section
	ppg.AddGroup(L"Export");
	
	LONG labelMinPixels = LABEL_MIN;
	LONG labelPercentage = LABEL_RATIO;

	XSI::CValueArray uiModeItems(10) ;
	uiModeItems[0] = L"Modeling" ; 
	uiModeItems[1] = (LONG)XSI::siConstructionModeModeling;
	uiModeItems[2] = L"Primary Shape" ; 
	uiModeItems[3] = (LONG)XSI::siConstructionModePrimaryShape;
	uiModeItems[4] = L"Animation" ; 
	uiModeItems[5] = (LONG)XSI::siConstructionModeAnimation;
	uiModeItems[6] = L"Secondary Shape" ; 
	uiModeItems[7] = (LONG)XSI::siConstructionModeSecondaryShape;
	uiModeItems[8] = L"Default" ; 
	uiModeItems[9] = (LONG)XSI::siConstructionModeDefault;

	XSI::PPGItem item = ppg.AddEnumControl(
		L"ConstMode",
		uiModeItems,
		L"Choice",
		XSI::siControlCombo ) ;
	item.PutLabel(L"Construction Mode");

	item.PutLabelMinPixels( labelMinPixels );
 	item.PutLabelPercentage( labelPercentage );
	
	item = ppg.AddItem( L"Subd_level" ) ;
	item.PutLabel(L"Subdivision level");
	
	item.PutLabelMinPixels( labelMinPixels );
 	item.PutLabelPercentage( labelPercentage );

	XSI::CValueArray uiSubdTypeItems(6) ;
	uiSubdTypeItems[0] = L"Catmull-Clark" ; 
	uiSubdTypeItems[1] = (LONG)XSI::siCatmullClark;
	uiSubdTypeItems[2] = L"XSI-Doo-Sabin" ; 
	uiSubdTypeItems[3] = (LONG)XSI::siXSIDooSabin;
	uiSubdTypeItems[4] = L"Linear" ; 
	uiSubdTypeItems[5] = (LONG)XSI::siLinearSubdivision;

	item = ppg.AddEnumControl(
		L"Subd_type",
		uiSubdTypeItems,
		L"Choice",
		XSI::siControlCombo ) ;
	item.PutLabel(L"Subdivision Rule Type");
		
	item.PutLabelMinPixels( labelMinPixels );
 	item.PutLabelPercentage( labelPercentage );

	item = ppg.AddItem( L"DiscAngle" ) ;
	item.PutLabel(L"Discontinuity Angle");
	item.PutLabelMinPixels( labelMinPixels );
 	item.PutLabelPercentage( labelPercentage );

	item = ppg.AddItem( L"UseDisc" ) ;
	item.PutLabel(L"Use Discontinuity");
	item.PutLabelMinPixels( labelMinPixels );
 	item.PutLabelPercentage( labelPercentage );

	ppg.AddRow();
	item = ppg.AddButton( L"ExportMeshButton", L"Export" ) ;
	item.PutAttribute( XSI::siUICX, (LONG)100 );

	item = ppg.AddItem( L"ExportFile" ) ;
	item.PutAttribute( XSI::siUINoLabel, true );	
	item.PutLabelMinPixels( labelMinPixels );
 	item.PutLabelPercentage( labelPercentage );
	
	ppg.EndRow();
	
	ppg.EndGroup();
	
	// define the import section
	ppg.AddGroup(L"Import");

	item = ppg.AddItem( L"MeshChunkSize" ) ;
	item.PutLabel(L"Chunk size");	
	item.PutAttribute( XSI::siUINoSlider, true );	
	item.PutAttribute( XSI::siUICX, (LONG)100  );
	item.PutLabelMinPixels( labelMinPixels );
 	item.PutLabelPercentage( labelPercentage );
	
	ppg.AddRow();
	item = ppg.AddButton( L"ImportPolygonMeshButton", L"Import Polygons" ) ;
	item.PutAttribute( XSI::siUICX, (LONG)100  );

	item = ppg.AddButton( L"ImportTriangleMeshButton", L"Import Triangles" ) ;
	item.PutAttribute( XSI::siUICX, (LONG)100  );

	item = ppg.AddItem( L"ImportFile" ) ;
	item.PutAttribute( XSI::siUINoLabel, true );	
	item.PutLabelMinPixels( labelMinPixels );
 	item.PutLabelPercentage( labelPercentage );
	
	ppg.EndRow();
	
	ppg.EndGroup();
	
	return XSI::CStatus::OK;
}

//*****************************************************************************
/*!	Callback that handles UI events (such as button clicks) on property page.
	page.
	\param in_ctxt The context that encapsulates the custom property property
	page event.
 */
//*****************************************************************************

XSIPLUGINCALLBACK
XSI::CStatus DemoImportExportProp_PPGEvent( const XSI::CRef& in_ctxt )
{	
	XSI::Application app ;

	XSI::PPGEventContext ctxt( in_ctxt ) ;

	XSI::PPGEventContext::PPGEvent eventID = ctxt.GetEventID() ;
	if ( eventID == XSI::PPGEventContext::siButtonClicked )
	{
		XSI::CValue buttonPressed = ctxt.GetAttribute( L"Button" ) ;	
		
		if ( buttonPressed.GetAsText() == L"ExportMeshButton" )
		{
			XSI::CustomProperty in_pset = ctxt.GetSource();
			
			XSI::CValueArray args(3);
			args[0] = in_pset.GetParameterValue( L"ConstMode" );
			args[1] = in_pset.GetParameterValue( L"Subd_type" );
			args[2] = in_pset.GetParameterValue( L"Subd_level" );
			
			XSI::CValue retVal;
			XSI::Application app;
			app.ExecuteCommand( L"DemoExportMesh", args, retVal ) ;				
		}
		else if ( buttonPressed.GetAsText() == L"ImportPolygonMeshButton" )
		{	
			XSI::CValueArray noarg;
			XSI::CValue noret;
			app.ExecuteCommand( L"DemoImportPolygonMesh", noarg, noret ) ;
		}
		else if ( buttonPressed.GetAsText() == L"ImportTriangleMeshButton" )
		{	
			XSI::CValueArray noarg;
			XSI::CValue noret;
			app.ExecuteCommand( L"DemoImportTriangleMesh", noarg, noret ) ;
		}				
	}

	return XSI::CStatus::OK ;
}
