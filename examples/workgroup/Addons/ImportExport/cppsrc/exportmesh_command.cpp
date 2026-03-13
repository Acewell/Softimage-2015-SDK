//*****************************************************************************
/*!	\file exportmesh_command.cpp
	\brief Implementation of the DemoExportMesh command. DemoExportMesh uses 
	CGeoemtryAccessor to extract data from the selected geometry, and exports 
	the extracted data to a text file.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#include <xsi_application.h>
#include <xsi_context.h>
#include <xsi_pluginregistrar.h>
#include <xsi_status.h>
#include <xsi_string.h>
#include <xsi_argument.h>
#include <xsi_command.h>
#include <xsi_menu.h>
#include <xsi_model.h>
#include <xsi_parameter.h>
#include <xsi_x3dobject.h>
#include <xsi_selection.h>
#include <xsi_primitive.h>
#include <xsi_polygonmesh.h>
#include <xsi_geometryaccessor.h>
#include <xsi_longarray.h>
#include <xsi_floatarray.h>
#include <xsi_doublearray.h>
#include <xsi_bitarray.h>
#include <xsi_envelopeweight.h>
#include <xsi_customproperty.h>
#include <xsi_griddata.h>
#include <xsi_clusterproperty.h>
#include <xsi_material.h>
#include <xsi_ppglayout.h>
#include <xsi_userdatamap.h>
#include <xsi_imageclip2.h>
#include <xsi_source.h>
#include <xsi_texture.h>
#include <xsi_math.h>
#include <xsi_progressbar.h>
#include <xsi_uitoolkit.h>

#include "helper.h"

extern XSI::CustomProperty GetImportExportProp();
extern XSI::Parameter GetImportExportOption( const XSI::CString& in_strName );

// helper functions for exporting mesh components

void OutputPolygons( CMeshFileWriter& in_mfw, XSI::CGeometryAccessor& );
void OutputPolygonVertices( CMeshFileWriter& in_mfw, XSI::CGeometryAccessor& );
void OutputPolygonNodes( CMeshFileWriter& in_mfw, XSI::CGeometryAccessor& );
void OutputMaterials( CMeshFileWriter& in_mfw, XSI::CGeometryAccessor& in_ga );
void OutputUserData( CMeshFileWriter& in_mfw, XSI::CGeometryAccessor& in_ga );
void OutputTriangles( CMeshFileWriter& in_mfw, XSI::CGeometryAccessor& );
void OutputPolygonEdges( CMeshFileWriter& in_mfw, XSI::CGeometryAccessor& );
void OutputClusterProperties( CMeshFileWriter& in_mfw, XSI::CGeometryAccessor& );
void OutputPolygonComponents( CMeshFileWriter& in_mfw, XSI::CLongArray&, XSI::CLongArray& );
void OutputClusterPropertyValues( CMeshFileWriter& in_mfw, XSI::CGeometryAccessor&, const XSI::CString&, XSI::CRefArray& );
void OutputUserDataValues( CMeshFileWriter& in_mfw, const XSI::CString&, XSI::CRefArray& );

void OutputHeader( CMeshFileWriter& in_mfw, XSI::X3DObject& in_xobj );

template< class T >
void OutputArray( CMeshFileWriter& in_mfw, T& in_array, LONG in_nDims )
{	
	XSI::Application app;
	
	if (!in_nDims)
	{
		return;
	}
		
	LONG nVals = in_array.GetCount()/in_nDims;

	for ( LONG i=0, nCurrent=0; i<nVals; i++ )
	{
		XSI::CString str;
		str += XSI::CString(in_array[nCurrent]);
		for (LONG j=1; j<in_nDims; j++)
		{
			str += L" ";
			str += XSI::CString(in_array[nCurrent+j]);
		}

		in_mfw.Write( i );
		in_mfw.Write( L" : " );
		in_mfw.Write( str );
		in_mfw.EOL();
		
		nCurrent += in_nDims;
	}
}

void OutputPolygons( CMeshFileWriter& in_mfw, XSI::CGeometryAccessor& in_ga )
{
	LONG nPolyCount = in_ga.GetPolygonCount();
	LONG nVtxCount = in_ga.GetVertexCount();
	LONG nEdgeCount = in_ga.GetEdgeCount();
	LONG nNodeCount = in_ga.GetNodeCount();
	LONG nTriangleCount = in_ga.GetTriangleCount();
	
	in_mfw.Header( L"Geometry Component Count" );	
	in_mfw.Write( L"Polygon: " );
	in_mfw.Write( (LONG)nPolyCount );
	in_mfw.EOL();
	
	in_mfw.Write( L"Vertex: " );
	in_mfw.Write( (LONG)nVtxCount );
	in_mfw.EOL();

	in_mfw.Write( L"Edge: " );
	in_mfw.Write( (LONG)nEdgeCount );
	in_mfw.EOL();

	in_mfw.Write( L"Node: " );
	in_mfw.Write( (LONG)nNodeCount );
	in_mfw.EOL();

	in_mfw.Write( L"Triangle: " );
	in_mfw.Write( (LONG)nTriangleCount );
	in_mfw.EOL();
	in_mfw.EOL();	
	in_mfw.Footer();
	
	XSI::CLongArray polySizeArray;
	XSI::CStatus st = in_ga.GetPolygonVerticesCount(polySizeArray);
	st.AssertSucceeded( L"GetPolygonVerticesCount" );
		
	in_mfw.Header( L"Polygon vertex count" );	
	OutputArray( in_mfw, polySizeArray, 1 );
	in_mfw.Footer();
}

void OutputTriangles( CMeshFileWriter& in_mfw, XSI::CGeometryAccessor& in_ga )
{
	// polygon triangle vertex indices
	XSI::CLongArray triVtxIdxArray;
	XSI::CStatus st = in_ga.GetTriangleVertexIndices(triVtxIdxArray);
	st.AssertSucceeded( L"GetTriangleVertexIndices" );

	XSI::CLongArray triSizeArray(in_ga.GetTriangleCount());
	{
		for (LONG i=0;i<triSizeArray.GetCount();i++) triSizeArray[i]=3;
	}

	in_mfw.Header( L"Triangle Vertex Indices" );
	OutputPolygonComponents(in_mfw, triVtxIdxArray, triSizeArray);
	in_mfw.Footer();

	// polygon triangle node indices
	XSI::CLongArray triNodeIdxArray;
	st = in_ga.GetTriangleNodeIndices(triNodeIdxArray);
	st.AssertSucceeded( L"GetTriangleNodeIndices" );

	in_mfw.Header( L"Triangle Node Indices" );
	OutputPolygonComponents(in_mfw, triNodeIdxArray, triSizeArray);		
	in_mfw.Footer();

	// dump polygon indices from triangle indices	
	XSI::CLongArray ptIndices;
	st = in_ga.GetPolygonTriangleIndices(ptIndices);
	st.AssertSucceeded( L"GetPolygonTriangleIndices" );

	in_mfw.Header( L"Polygon Triangle Index array mapping" );	

	LONG nTriangles = ptIndices.GetCount();

	for (LONG i=0; i<nTriangles; i++)
	{	
		XSI::CString str(i);
		str += XSI::CString(L" : ") + XSI::CString(ptIndices[i]) + XSI::CString(L"\n");
		in_mfw.Write( str );	
	}	
}

void OutputPolygonVertices( CMeshFileWriter& in_mfw, XSI::CGeometryAccessor& in_ga )
{
	// polygon vertex indices
	XSI::CLongArray polyVtxIdxArray;
	XSI::CStatus st = in_ga.GetVertexIndices(polyVtxIdxArray);
	st.AssertSucceeded( L"GetVertexIndices" );

	XSI::CLongArray polySizeArray;
	st = in_ga.GetPolygonVerticesCount(polySizeArray);

	in_mfw.Header( L"Polygon Vertex Indices" );
	OutputPolygonComponents(in_mfw, polyVtxIdxArray, polySizeArray);		
	in_mfw.Footer();

	// polygon vertex positions
	XSI::CDoubleArray vtxPosArray;
	st = in_ga.GetVertexPositions(vtxPosArray);
	st.AssertSucceeded( L"GetVertexPositions" );
	
	in_mfw.Header( L"Vertex Positions" );
	OutputArray( in_mfw, vtxPosArray, 3 );		
	in_mfw.Footer();

	// vertex crease values
	XSI::CFloatArray vtxCreaseValues;
	st = in_ga.GetVertexCreaseValues(vtxCreaseValues);
	st.AssertSucceeded( L"GetVertexCreaseValues" );
	
	in_mfw.Header( L"Vertex Creases" );
	OutputArray( in_mfw, vtxCreaseValues, 1 );
	in_mfw.Footer();
}

void OutputPolygonNodes( CMeshFileWriter& in_mfw, XSI::CGeometryAccessor& in_ga )
{
	// polygon node indices
	XSI::CLongArray polyNodeIdxArray;
	XSI::CStatus st = in_ga.GetNodeIndices(polyNodeIdxArray);
	st.AssertSucceeded( L"GetNodeIndices" );
	
	XSI::CLongArray polySizeArray;
	st = in_ga.GetPolygonVerticesCount(polySizeArray);
	st.AssertSucceeded( L"GetPolygonVerticesCount" );

	in_mfw.Header( L"Polygon Node Indices" );
	OutputPolygonComponents(in_mfw, polyNodeIdxArray, polySizeArray);		
	in_mfw.Footer();

	// polygon node normals
	XSI::CFloatArray nodeArray;
	st = in_ga.GetNodeNormals(nodeArray);
	st.AssertSucceeded( L"GetNodeNormals" );
	
	in_mfw.Header( L"Node Normals" );
	OutputArray( in_mfw, nodeArray, 3 );
	in_mfw.Footer();
}

void OutputPolygonEdges( CMeshFileWriter& in_mfw, XSI::CGeometryAccessor& in_ga )
{
	// polygon edge indices
	XSI::CLongArray polyEdgeIdxArray;
	XSI::CStatus st = in_ga.GetEdgeIndices(polyEdgeIdxArray);
	st.AssertSucceeded( L"GetEdgeIndices" );
	
	XSI::CLongArray polySizeArray;
	st = in_ga.GetPolygonVerticesCount(polySizeArray);
	st.AssertSucceeded( L"GetPolygonVerticesCount" );

	in_mfw.Header( L"Polygon Edge Indices" );
	OutputPolygonComponents(in_mfw, polyEdgeIdxArray, polySizeArray);		
	in_mfw.Footer();

	// edge crease values
	XSI::CFloatArray edgeCreaseValues;
	st = in_ga.GetEdgeCreaseValues(edgeCreaseValues);
	st.AssertSucceeded( L"GetEdgeCreaseValues" );
	
	in_mfw.Header( L"Edge Creases" );
	OutputArray( in_mfw, edgeCreaseValues, 1 );
	in_mfw.Footer();
		
	// hard edge values
	XSI::CBitArray hardEdgeArray;
	st = in_ga.GetHardEdges(hardEdgeArray);
	st.AssertSucceeded( L"GetHardEdges" );
	
	in_mfw.Header( L"Hard Edges" );
	OutputArray( in_mfw, hardEdgeArray, 1 );
	in_mfw.Footer();
}

void OutputClusterProperties( CMeshFileWriter& in_mfw, XSI::CGeometryAccessor& in_ga )
{	
	// env weight props: siClusterPropertyEnvelopWeightType	
	XSI::CRefArray envwProps = in_ga.GetEnvelopeWeights();
	OutputClusterPropertyValues( in_mfw, in_ga, L"Envelop Weights", envwProps );
	
	// uv props: siClusterPropertyUVType
	XSI::CRefArray uvProps = in_ga.GetUVs();
	OutputClusterPropertyValues( in_mfw, in_ga, L"UVs", uvProps );
	
	// vertex color props: siClusterPropertyVertexColorType
	XSI::CRefArray vtxColorProps = in_ga.GetVertexColors();
	OutputClusterPropertyValues( in_mfw, in_ga, L"Vertex colors", vtxColorProps );
		
	// user normal props: siClusterPropertyUserNormalType
	XSI::CRefArray userNormals = in_ga.GetUserNormals();	
	OutputClusterPropertyValues( in_mfw, in_ga, L"User normals", userNormals );

	// user motion props: siClusterPropertyUserMotionType
	XSI::CRefArray userMotions = in_ga.GetUserMotions();	
	OutputClusterPropertyValues( in_mfw, in_ga, L"User motions", userMotions );
		
	// shape key props: siClusterPropertyShapeKeyType
	XSI::CRefArray shapeKeys = in_ga.GetShapeKeys();
	OutputClusterPropertyValues( in_mfw, in_ga, L"Shape keys", shapeKeys );
		
	// weight map props: siClusterPropertyShapeKeyType
	XSI::CRefArray wmaps = in_ga.GetWeightMaps();
	OutputClusterPropertyValues( in_mfw, in_ga, L"weights", wmaps );	
}

void OutputUserData( CMeshFileWriter& in_mfw, XSI::CGeometryAccessor& in_ga )
{	
	XSI::CRefArray UDProps = in_ga.GetUserDataMaps(XSI::siClusterVertexType);
	OutputUserDataValues( in_mfw, L"Vertex user data", UDProps );

	UDProps = in_ga.GetUserDataMaps(XSI::siClusterNodeType);
	OutputUserDataValues( in_mfw, L"Node user data", UDProps );

	UDProps = in_ga.GetUserDataMaps(XSI::siClusterEdgeType);
	OutputUserDataValues( in_mfw, L"Edge user data", UDProps );

	UDProps = in_ga.GetUserDataMaps(XSI::siClusterPolygonType);
	OutputUserDataValues( in_mfw, L"Polygon user data", UDProps );	
}

void OutputMaterials( CMeshFileWriter& in_mfw, XSI::CGeometryAccessor& in_ga )
{
	in_mfw.Header( L"Materials" );	
	XSI::CRefArray mats = in_ga.GetMaterials();
	
	LONG nVals = mats.GetCount();
	
	for ( LONG i=0; i<nVals; i++ )
	{		
		XSI::Material mat(mats[i]);
		
		XSI::CParameterRefArray params;
		XSI::CRefArray clsProps = mat.GetConnectedClusterProperties(params);
		
		XSI::CString str(mat.GetName());				
		
		for (LONG j=0; j<clsProps.GetCount(); j++)
		{			
			str += L"\n\t";		
						
			XSI::ClusterProperty cp(clsProps[j]);
			
			str += cp.GetName();
			str += L" type:" + XSI::CString((LONG)cp.GetPropertyType());
			str += L" data type:" + XSI::CString((LONG)cp.GetInternalType());
			str += L" elem count:" + XSI::CString(cp.GetValueSize());
			
			// connection point parameter
			XSI::Parameter param = params[j];
			
			str += L"\n\tParameter path: ";
			str += param.GetFullName();
			str += L"\n";
			
			XSI::Texture txt(param.GetParent());
			str += L"\tParameter parent: ";
			str += txt.GetFullName();
			
			XSI::ImageClip2 clip(txt.GetImageClip());

			//retreiving the image source
			XSI::Source clipSource(clip.GetSource());
			XSI::CValue fileName = clipSource.GetParameterValue( L"path");
			str += L"\tTexture image: ";
			str += XSI::CString(fileName);						
		}				
		
		in_mfw.Write( i );
		in_mfw.Write( L" : " );
		in_mfw.Write( str );
		in_mfw.EOL();
	}
	in_mfw.Footer();
	
	// material used by polygons	
	XSI::CLongArray polyMatIndices;	
	XSI::CStatus st = in_ga.GetPolygonMaterialIndices(polyMatIndices);
	st.AssertSucceeded( L"GetPolygonMaterialIndices" );
	
	in_mfw.Header( L"Polygon materials" );
	OutputArray( in_mfw, polyMatIndices, 1 );
	in_mfw.Footer();
}

void OutputClusterPropertyValues
( 
	CMeshFileWriter& in_mfw,
	XSI::CGeometryAccessor& in_ga,
	const XSI::CString& in_strTitle,
	XSI::CRefArray& in_array
)
{	
	in_mfw.Header( in_strTitle );
	in_mfw.EOL();
	in_mfw.EOL();	
		
	LONG nVals = in_array.GetCount();

	XSI::MATH::CTransformation transfo = in_ga.GetTransform();
	
	for ( LONG i=0; i<nVals; i++ )
	{		
		XSI::ClusterProperty cp(in_array[i]);

		XSI::CFloatArray valueArray;
		XSI::CBitArray flags;		
		cp.GetValues( valueArray, flags );
		
		XSI::CString strTime(cp.GetName());
		strTime += L" values: ";
				
		XSI::CString str(cp.GetName());
		str += L" type:" + XSI::CString((LONG)cp.GetPropertyType());
		str += L" data type:" + XSI::CString((LONG)cp.GetInternalType());
		str += L" elem count:" + XSI::CString(cp.GetValueSize());

		XSI::EnvelopeWeight envwProp(cp);
		
		if (envwProp.IsValid())
		{
			XSI::CRefArray deformers(envwProp.GetDeformers());
			
			in_mfw.Write( L"Deformers:\n" );
			OutputArray( in_mfw, deformers, 1 );			
			in_mfw.Write( L"\n" );
		}
		
		LONG nValueSize = cp.GetValueSize();
		
		XSI::CString strValues = str;
		for ( LONG j=0, g=0; j<valueArray.GetCount(); j += nValueSize, g++ )
		{
			strValues += L"\n\t";
			strValues += L"(";
			strValues += XSI::CString(flags[g]); // geometry pos state flag
			strValues += L")\t";			
			strValues += XSI::CString(valueArray[j]);
			
			for ( LONG k=1; k<nValueSize; k++ )
			{
				strValues += L" " + XSI::CString(valueArray[j+k]);
			}
		}

		in_mfw.Write( i );
		in_mfw.Write( L" : " );
		in_mfw.Write( strValues );		
		in_mfw.EOL();
	}
	in_mfw.Footer();
}

void OutputUserDataValues
( 
	CMeshFileWriter& in_mfw,
	const XSI::CString& in_strTitle,
	XSI::CRefArray& in_array
)
{	
	in_mfw.Header( in_strTitle );
	in_mfw.EOL();
	in_mfw.EOL();
		
	LONG nVals = in_array.GetCount();

	for ( LONG i=0; i<nVals; i++ )
	{		
		XSI::UserDataMap udm(in_array[i]);		
		XSI::CUserDataArray valueArray;
		XSI::CBitArray flags;
		
		udm.GetValues( valueArray, flags );
		
		XSI::CString strTime(udm.GetName());
		strTime += L" values: ";
		
		XSI::CString strValues = udm.GetName();
		for ( LONG j=0; j<valueArray.GetCount(); j++ )
		{			
			strValues += L"\n\t";
			strValues += L"(";
			strValues += XSI::CString(flags[j]); // geometry pos state flag
			strValues += L")\t";
			strValues += XSI::CString(valueArray[j].m_pData!=NULL);
			strValues += L" ";
			strValues += XSI::CString((LONG)valueArray[j].m_nSize);
		}

		in_mfw.Write( i );
		in_mfw.Write( L" : " );
		in_mfw.Write( strValues );		
		in_mfw.EOL();
	}
	in_mfw.Footer();	
}

void OutputPolygonComponents
( 
	CMeshFileWriter&	in_mfw, 
	XSI::CLongArray&	in_indexArray,
	XSI::CLongArray&	in_polySizeArray
)
{
	for (LONG i=0, offset=0; i<in_polySizeArray.GetCount(); i++)
	{	
		XSI::CString strVertices;
		strVertices += XSI::CString(in_indexArray[offset]);
		for (LONG j=1; j<in_polySizeArray[i]; j++)
		{
			strVertices += L" ";
			strVertices += XSI::CString(in_indexArray[offset+j]);						
		}

		in_mfw.Write( i );
		in_mfw.Write( L" : " );
		in_mfw.Write( strVertices );
		in_mfw.EOL();
		
		offset += in_polySizeArray[i];
	}
}

void OutputHeader( CMeshFileWriter& in_mfw, XSI::X3DObject& in_xobj )
{
	in_mfw.Write( L"***************\n" );
	in_mfw.Write( L"Object name: " );
	in_mfw.Write( in_xobj.GetName() );
	in_mfw.EOL();
	
	in_mfw.Write( L"Subdivison level: " );
	in_mfw.Write( GetImportExportOption( L"Subd_level" ).GetValue() );
	in_mfw.EOL();

	XSI::CustomProperty prop = GetImportExportProp();
	XSI::PPGLayout ppg = prop.GetPPGLayout();

	XSI::PPGItem comboBox = ppg.GetItem( L"ConstMode" );
	XSI::CValueArray items = comboBox.GetUIItems();

	LONG nItem = GetImportExportOption( L"ConstMode" ).GetValue();
	XSI::CString strConstMode;
	for (LONG i=0; i<items.GetCount(); i++)
	{
		if (items[i*2+1] == nItem)
		{
			strConstMode = items[i*2];
			break;
		}
	}			

	in_mfw.Write( L"Construction Mode: " );	
	in_mfw.Write( strConstMode );
	in_mfw.EOL();

	comboBox = ppg.GetItem( L"Subd_type" );
	items = comboBox.GetUIItems();
	
	nItem = GetImportExportOption( L"Subd_type" ).GetValue();
	XSI::CString strSubdType;
	for (LONG i=0; i<items.GetCount(); i++)
	{
		if (items[i*2+1] == nItem)
		{
			strSubdType = items[i*2];
			break;
		}
	}			
	in_mfw.Write( L"Subdivison type: " );	
	in_mfw.Write( strSubdType );
	in_mfw.EOL();
	
	in_mfw.Write( L"Discontinuity Angle: " );
	in_mfw.Write( GetImportExportOption( L"DiscAngle" ).GetValue() );
	in_mfw.EOL();
	in_mfw.Write( L"Use Discontinuity Angle: " );
	in_mfw.Write( GetImportExportOption( L"UseDisc" ).GetValue() );
	in_mfw.EOL();
	in_mfw.EOL();
}

//*****************************************************************************
/*!	Specify the arguments and return value of the DemoExportMesh command. 
	\param in_ctxt The context that encapsulates the command to initialize.
 */
//*****************************************************************************

XSIPLUGINCALLBACK XSI::CStatus DemoExportMesh_Init( XSI::CRef& in_ctxt )
{
	XSI::Context ctxt( in_ctxt );
	XSI::Command oCmd;
	oCmd = ctxt.GetSource();
	
	// Specify that the command returns a value
	oCmd.EnableReturnValue(true);

	// Add arguments to the command
	XSI::ArgumentArray oArgs;
	oArgs = oCmd.GetArguments();

	// Construction Mode. By default, siConstructionModeModeling
	oArgs.Add(L"ConstMode",(LONG)XSI::siConstructionModeModeling);
	
	// Subdivision algorithm to use. By default, CatmullClark
	oArgs.Add(L"Subd_type",(LONG)XSI::siCatmullClark);
	
	// Subdivision level
	oArgs.Add(L"Subd_level", (LONG)0);

	return XSI::CStatus::OK;
}

//*****************************************************************************
/*!	Implementation of the DemoExportMesh command. This command uses the 
	CGeometryAccessor to extract the data from the geometry to export.
	\param in_ctxt The context that encapsulates the command to execute.
 */
//*****************************************************************************

XSIPLUGINCALLBACK XSI::CStatus DemoExportMesh_Execute( XSI::CRef& in_ctxt )
{
	// Unpack the command argument values
	XSI::Context ctxt( in_ctxt );
	XSI::CValueArray args = ctxt.GetAttribute(L"Arguments");

	// A 3d object with a mesh geometry must be selected
	XSI::Application app;	
	XSI::X3DObject xobj(app.GetSelection()[0]);
	if (!xobj.IsValid()) return XSI::CStatus::False;

	// Get a geometry accessor from the selected object	
	XSI::Primitive prim = xobj.GetActivePrimitive();
	XSI::PolygonMesh mesh = prim.GetGeometry();
	if (!mesh.IsValid()) return XSI::CStatus::False;

	XSI::siConstructionMode constMode = (XSI::siConstructionMode)(LONG)args[0];
	
	XSI::siSubdivisionRuleType subdType = (XSI::siSubdivisionRuleType)(LONG)args[1];
	
	LONG subdLevel = args[2];
	
	XSI::CGeometryAccessor ga = mesh.GetGeometryAccessor( constMode, subdType, subdLevel );

	// prepare the output text file
	XSI::CString strOut = GetImportExportOption( L"ExportFile" ).GetValue();		
	
	CMeshFileWriter mfw;
	XSI::CStatus st = mfw.Init(strOut);
	if (st!=XSI::CStatus::OK)
	{
		return st;
	}	

	// Setup the progress bar
	XSI::UIToolkit kit = app.GetUIToolkit();
	XSI::ProgressBar bar = kit.GetProgressBar();

	bar.PutMaximum( 40000 );
	bar.PutStep( 5000 );
	bar.PutVisible( true );
	bar.PutCaption( L"Exporting..." );

	OutputHeader( mfw, xobj );
			
	// output the data
	
	bar.PutStatusText( L"polygons" );
	OutputPolygons( mfw, ga );
	if (bar.IsCancelPressed()) return XSI::CStatus::False;
	bar.Increment();
	
	bar.PutStatusText( L"polygon vertices" );
	OutputPolygonVertices( mfw, ga );
	if (bar.IsCancelPressed()) return XSI::CStatus::False;
	bar.Increment();
	
	bar.PutStatusText( L"polygon nodes" );
	OutputPolygonNodes( mfw, ga );
	if (bar.IsCancelPressed()) return XSI::CStatus::False;
	bar.Increment();
	
	bar.PutStatusText( L"polygon edges" );
	OutputPolygonEdges( mfw, ga );
	if (bar.IsCancelPressed()) return XSI::CStatus::False;
	bar.Increment();
	
	bar.PutStatusText( L"polygon triangles" );
	OutputTriangles( mfw, ga );
	if (bar.IsCancelPressed()) return XSI::CStatus::False;
	bar.Increment();
	
	bar.PutStatusText( L"cluster properties" );
	OutputClusterProperties( mfw, ga );	
	if (bar.IsCancelPressed()) return XSI::CStatus::False;
	bar.Increment();
	
	bar.PutStatusText( L"user data properties" );
	OutputUserData( mfw, ga );	
	if (bar.IsCancelPressed()) return XSI::CStatus::False;
	bar.Increment();
	
	bar.PutStatusText( L"materials" );
	OutputMaterials( mfw, ga );
	if (bar.IsCancelPressed()) return XSI::CStatus::False;
	bar.Increment();
	
	return XSI::CStatus::OK;
}
