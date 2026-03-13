// GridDataExampleCPP
//
//	Copyright 2012 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

#include <xsi_application.h>
#include <xsi_context.h>
#include <xsi_pluginregistrar.h>
#include <xsi_status.h>
#include <xsi_customproperty.h>
#include <xsi_ppglayout.h>
#include <xsi_command.h>
#include <xsi_model.h>
#include <xsi_griddata.h>
#include <xsi_color.h>
#include <xsi_material.h>
#include <xsi_ppgeventcontext.h>
#include <xsi_eventinfo.h>
#include <xsi_gridwidget.h>
#include <xsi_griddata.h>
#include <xsi_imageclip.h>
#include <xsi_scene.h>
#include <xsi_project.h>
#include <xsi_materiallibrary.h>

#include <vector>
#include <set>
#include <map>

using namespace XSI; 

// Cell ID set
typedef std::set< LONG > CellIds;
typedef std::set< LONG >::iterator CellIdsIterator;

#define GD_PARAM_NAME "Data"
enum GDCPP_ColumnTypeEnum {
	GDCPP_siColumnStandard = 0,
	GDCPP_siColumnBool,
	GDCPP_siColumnCombo,
	GDCPP_siColumnInt,
	GDCPP_siColumnFloat,
	GDCPP_siColumnImageClip,
	GDCPP_siColumnColor,
	GDCPP_siColumnButton,
	GDCPP_siColumnVector,
	GDCPP_siColumnFile,
	GDCPP_siColumnShaderBall,
	GDCPP_siColumnMultiLine,
	GDCPP_siColumnCount
};


// Forward declarations
void PopulateGrid();
void UpdateSums();
GridData GetGD( CString in_csName );

SICALLBACK XSILoadPlugin( PluginRegistrar &in_reg )
{
	in_reg.PutAuthor(L"Autodesk");
	in_reg.PutName(L"GridDataExampleCPP");
	in_reg.PutVersion(1,0);

	in_reg.RegisterProperty("GDE_CPPGrid");
	in_reg.RegisterCommand("GDE_CreateCPPGrid", "GDE_CreateCPPGrid");

	return CStatus::OK;
}

SICALLBACK XSIUnloadPlugin( const PluginRegistrar &in_reg )
{
	return CStatus::OK;
}

SICALLBACK GDE_CPPGrid_Define( CRef &in_ctxt )
{
	Context ctxt( in_ctxt );
	CustomProperty oCustomProperty = ctxt.GetSource();
	oCustomProperty.AddGridParameter( GD_PARAM_NAME );
	return true;
}

SICALLBACK GDE_CPPGrid_DefineLayout( CRef &in_ctxt )
{
	Context ctxt( in_ctxt );
	PPGLayout oLayout = ctxt.GetSource();
	PPGItem item = oLayout.AddItem( GD_PARAM_NAME );
	item.PutAttribute(siUIGridThumbnailSize, 64);
	oLayout.AddButton("Dump_Data");
	return true;
}

SICALLBACK GDE_CPPGrid_PPGEvent( CRef &in_context )
{
	PPGEventContext ctxt( in_context );

	CValueArray xParams = ctxt.GetAttribute("ExtraParams");
	PPGEventContext::PPGEvent eEventID = ctxt.GetEventID();
	switch ( eEventID ) {
		case PPGEventContext::siGridDataOnBeginValueChange:
		{
			CValueArray retArr;
			CValueArray colRow = xParams[0];
			retArr.Resize( colRow.GetCount() / 2 );
			for ( LONG i = 0; i < colRow.GetCount() / 2; ++i ) {
				LONG col = colRow[i*2];
				LONG row = colRow[i*2+1];
				if ( row == 4 ) {
					// Prevent modification of the "sum" row
					retArr[i] = false;
				} else {
					retArr[i] = true;
				}
			}
			ctxt.PutAttribute( "Return", retArr );
			break;
		}
		case PPGEventContext::siGridDataOnEndValueChange:
			UpdateSums();
			break;
		case PPGEventContext::siGridDataOnBeginSelectionChange:
			break;
		case PPGEventContext::siGridDataOnEndSelectionChange:
			break;
		case PPGEventContext::siGridDataOnButtonClicked:
		{
			CValueArray colRow = xParams[0];
			for ( LONG i = 0; i < colRow.GetCount() / 2; ++i ) {
				LONG col = colRow[i*2];
				LONG row = colRow[i*2+1];
				
				if ( GDCPP_siColumnButton == col && row != 4 ) { // Do not touch the "sum" row
					// Set the row bg color
					Parameter param( ctxt.GetSource() );
					GridData gd( param.GetValue() );

					LONG newColor = gd.GetCell(GDCPP_siColumnColor, row);
					CColor rowColor = gd.GetRowBackgroundColor( row );
					rowColor.r = newColor & 0xFF;
					rowColor.g = (newColor & 0xFF00) >> 8;
					rowColor.b = (newColor & 0xFF0000) >> 16;
					rowColor.a = (newColor & 0xFF000000) >> 24;
					gd.SetRowBackgroundColor( row, rowColor );
				}
			}
			break;
		}
		case PPGEventContext::siGridDataOnHeaderDoubleClick:
			break;
		case PPGEventContext::siGridDataOnContextMenuInit:
			break;
		case PPGEventContext::siGridDataOnContextMenuSelected:
			break;
		case PPGEventContext::siButtonClicked:
		{
			CString buttonName = ctxt.GetAttribute( "Button" );
			if ( buttonName == "Dump_Data" ) {
				CustomProperty prop( ctxt.GetSource() );
				Parameter param = prop.GetParameter( GD_PARAM_NAME );
				GridData gd( param.GetValue() );
				for ( LONG r = 0; r < gd.GetRowCount(); ++r ) {
					CString trace = "row ";
					trace += CString( CValue( r ) );
					trace += ": ";

					for ( LONG c = 0; c < gd.GetColumnCount(); ++c ) {
						if ( c != 0 ) {
							trace += "|";

							siGridWidgetColumnType type = gd.GetColumnType( c );
							CValue data = gd.GetCell( c, r );
							if ( type == siColumnColor ) {
								LONG color = data;
								trace += CString( CValue( color & 0xFF ) ); trace += ","; // r
								trace += CString( CValue( ( color & 0xFF00 ) >> 8 ) ); trace += ","; // g
								trace += CString( CValue( ( color & 0xFF0000 ) >> 16 ) ); trace += ","; // b
								trace += CString( CValue( ( color & 0xFF000000 ) >> 24 ) ); trace += ","; // a
							} else if ( type == siColumnImageClip ) {
								ImageClip clip( data );
								trace += clip.GetName();
							} else if ( type == siColumnShaderBall ) {
								Material mat( data );
								trace += mat.GetName();
							} else {
								trace += CString( data );
							}
						}
					}
					Application().LogMessage( trace );
				}
			}
		}
	}
	
	return CStatus::OK;
}

CustomProperty GetGDPropertyOrNone()
{
	return Application().GetActiveSceneRoot().GetProperties().GetItem( "GDE_CPPGrid" ) ;
}

CustomProperty GetOrCreateGDProperty()
{
	CustomProperty siProperty = GetGDPropertyOrNone();
	if ( !siProperty.IsValid() ) {
		siProperty = Application().GetActiveSceneRoot().AddProperty( "GDE_CPPGrid" ) ;
	}

	return siProperty;
}

GridData GetGD( CString in_csName )
{
	CString propManagerName = "GDE_CPPGrid";
	CustomProperty siProperty = GetOrCreateGDProperty();

	GridData grid( siProperty.GetParameter(in_csName).GetValue() );

	assert( grid.IsValid() );
	return grid;
}

SICALLBACK GDE_CreateCPPGrid_Init( CRef &in_ctxt )
{
	Context ctxt( in_ctxt );
	Command oCmd = ctxt.GetSource();
	oCmd.PutDescription( "" );
	oCmd.EnableReturnValue( true );
	return true;
}

SICALLBACK GDE_CreateCPPGrid_Execute(  )
{
	PopulateGrid();

	CValueArray args;
	CValue retVal;
	args.Add( GetGDPropertyOrNone().GetRef() );

	Application().ExecuteCommand( "InspectObj", args, retVal );

	return true;
}

void PopulateGrid() 
{
	GridData gd = GetGD( GD_PARAM_NAME );

	if ( gd.GetRowCount() != 0 ) {
		Application().LogMessage( "GridData already populated. Please delete the Custom PSet before populating", siErrorMsg );
		return;
	}

	// Create columns
	gd.PutColumnCount( GDCPP_siColumnCount );

	// Create an arbitrary nb of rows
	gd.PutRowCount( 5 );

	// Set column definitions first
	// siColumnStandard
	gd.PutColumnLabel( GDCPP_siColumnStandard, "siColumnStandard" );
	gd.PutColumnType( GDCPP_siColumnStandard, siColumnStandard );

	// siColumnBool
	gd.PutColumnLabel( GDCPP_siColumnBool, "siColumnBool" );
	gd.PutColumnType( GDCPP_siColumnBool, siColumnBool );

	// siColumnCombo
	gd.PutColumnLabel( GDCPP_siColumnCombo, "siColumnCombo" );
	CValueArray arr;
	arr.Add( CValue("First") ); arr.Add( CValue(0) );
	arr.Add( CValue("Second") ); arr.Add( CValue(1) );
	arr.Add( CValue("Third") ); arr.Add( CValue(2) );
	arr.Add( CValue("Fourth") ); arr.Add( CValue(3) );
	gd.PutColumnComboItems( GDCPP_siColumnCombo, arr );

	// siColumnInt
	gd.PutColumnLabel( GDCPP_siColumnInt, "siColumnInt" );
	gd.SetIntColumnDef( GDCPP_siColumnInt, -50, 50, 2 );

	// siColumnFloat
	gd.PutColumnLabel( GDCPP_siColumnFloat, "siColumnFloat" );
	gd.SetFloatColumnDef( GDCPP_siColumnFloat, -40, 40, 3, 4 );

	// siColumnImageClip
	gd.PutColumnLabel( GDCPP_siColumnImageClip, "siColumnImageClip" );
	gd.SetImageClipColumnDef( GDCPP_siColumnImageClip, 64 );

	// siColumnColor
	gd.PutColumnLabel( GDCPP_siColumnColor, "siColumnColor" );
	gd.PutColumnType( GDCPP_siColumnColor, siColumnColor );

	// siColumnVector
	gd.PutColumnLabel( GDCPP_siColumnVector, "siColumnVector" );
	gd.SetVectorColumnDef( GDCPP_siColumnVector, 3, -30, 30, 5, 2 );

	// siColumnButton
	gd.PutColumnLabel( GDCPP_siColumnButton, "siColumnButton" );
	gd.PutColumnType( GDCPP_siColumnButton, siColumnButton );

	// siColumnFile
	gd.PutColumnLabel( GDCPP_siColumnFile, "siColumnFile" );
	gd.SetFileColumnDef( GDCPP_siColumnFile, "Folder", "\\", ""  );

	// siColumnShaderBall
	gd.PutColumnLabel( GDCPP_siColumnShaderBall, "siColumnShaderBall" );
	gd.SetShaderBallColumnDef( GDCPP_siColumnShaderBall, 32 );

	// siColumnMultiLine
	gd.PutColumnLabel( GDCPP_siColumnMultiLine, "siColumnMultiLine" );
	gd.PutColumnType( GDCPP_siColumnMultiLine, siColumnMultiLine );

	// Populate with data
	Scene scene = Application().GetActiveProject().GetActiveScene();
	MaterialLibrary matlib( scene.GetActiveMaterialLibrary() );
	CRefArray mats = matlib.GetItems();

	for ( LONG i = 0; i < 4; ++i ) {
		gd.PutRowLabel( i, CString(CValue(i)) );
		// siColumnStandard
		gd.PutCell( GDCPP_siColumnStandard, i, CString("Standard") + CString(" ") + CString(CValue(i)) );

		// siColumnBool
		gd.PutCell( GDCPP_siColumnBool, i, i %2 == 0 ? true : false );

		// siColumnCombo
		gd.PutCell( GDCPP_siColumnCombo, i, i );

		// siColumnInt
		gd.PutCell( GDCPP_siColumnInt, i, i );

		// siColumnFloat
		gd.PutCell( GDCPP_siColumnFloat, i, i );

		// siColumnImageClip
		if ( mats.GetCount() > 0 ) {
			Material mat = mats[i % mats.GetCount()];
			CRefArray clips = mat.GetAllImageClips();
			if ( clips.GetCount() > 0 ) {
				ImageClip clip = clips[ i % clips.GetCount() ];
				gd.PutCell( GDCPP_siColumnImageClip, i, CValue(clip) );
			}
		}

		// siColumnColor
		LONG lColor;
		switch ( i % 3 ) {
			case 0:
				// red
				lColor = 255;
				break;
			case 1:
				// green
				lColor = 255 << 8;
				break;
			case 2:
				// blue
				lColor = 255 << 16;
				break;
		}
		gd.PutCell( GDCPP_siColumnColor, i, lColor );

		// siColumnVector
		CValueArray arr;
		arr.Add(i);arr.Add(i);arr.Add(i);
		gd.PutCell( GDCPP_siColumnVector, i, arr );

		// siColumnButton
		gd.PutCell( GDCPP_siColumnButton, i, CString("SetBG") + CString(" ") + CString(CValue(i)) );

		// siColumnFile
		gd.PutCell( GDCPP_siColumnFile, i, CString("\\PleaseDblClickToSetValidFolder") + CString(" ") + CString(CValue(i)) );

		// siColumnShaderBall
		if ( mats.GetCount() > 0 ) {
			Material mat = mats[i % mats.GetCount()];
			gd.PutCell( GDCPP_siColumnShaderBall, i, CValue( mat ) );
		}

		// siColumnMultiLine
		gd.PutCell( GDCPP_siColumnMultiLine, i, CString("Multiline") + CString(" ") + CString(CValue(i)) );
	}

	// Last row is a "sum" row
	gd.PutRowLabel( 4, "Sum");

	UpdateSums();
}

void UpdateSums() 
{
	GridData gd = GetGD( GD_PARAM_NAME );
	gd.PutRowLabel( 4, "Sum");

	for ( LONG col = 0; col < GDCPP_siColumnCount; ++col ) {
		// The default sum value is the value that is in row 0
		CValue sum = gd.GetCell(col, 0);

		// Sum up with the remaining rows
		for ( LONG line = 1; line < 4; ++ line ) {
			CValue currValue = gd.GetCell(col, line);
			switch ( col ) {
			case GDCPP_siColumnStandard:
			case GDCPP_siColumnMultiLine:
				// concatenate text
				sum = CString(sum) + CString(",") + CString( currValue );
				break;
			case GDCPP_siColumnInt:
				// Addition of all the values
				sum = (int) sum + (int) currValue;
				break;
			case GDCPP_siColumnFloat:
				// Addition of all the values
				sum = (float) sum + (float) currValue;
				break;

			case GDCPP_siColumnColor: {
				// Just add the components and wrap up. Not really 
				// useful but demonstrates how to get the color components
				// from the grid data
				LONG sumColor = (LONG) sum;
				unsigned char sumR = sumColor & 0xFF;
				unsigned char sumG = (sumColor & 0xFF00) >> 8;
				unsigned char sumB = (unsigned char) ((sumColor & 0xFF0000) >> 16);
				unsigned char sumA = (sumColor & 0xFF000000) >> 24;

				LONG currColor = (LONG) currValue;
				unsigned char currR = currColor & 0xFF;
				unsigned char currG = (currColor & 0xFF00) >> 8;
				unsigned char currB = (unsigned char) ((currColor & 0xFF0000) >> 16);
				unsigned char currA = (currColor & 0xFF000000) >> 24;

				sumR = (sumR + currR) % 256;
				sumG = (sumG + currG) % 256;
				sumB = (sumB + currB) % 256;
				sumA = (sumA + currA) % 256;

				sum = CValue((LONG) (sumR + (sumG << 8) + (sumB << 16) + (sumA << 24) ) );

				break;
			}
			case GDCPP_siColumnVector: {
				// Sum of the components
				CValueArray arrSum( (CValueArray &) sum );
				CValueArray arrCurr( (CValueArray &) currValue );
				arrSum[0] = (float) arrSum[0] + (float) arrCurr[0];
				arrSum[1] = (float) arrSum[1] + (float) arrCurr[1];
				arrSum[2] = (float) arrSum[2] + (float) arrCurr[2];
				sum = arrSum;
				break;
			}
			case GDCPP_siColumnBool:
			case GDCPP_siColumnCombo:
			case GDCPP_siColumnImageClip:
			case GDCPP_siColumnButton:
			case GDCPP_siColumnFile:
			case GDCPP_siColumnShaderBall:
				// No sum for these columns. Simply use the value in row 0
				break;
			}
		}
		if ( !sum.IsEmpty() ) {
			gd.PutCell( col, 4, sum );
		}
	}
}
