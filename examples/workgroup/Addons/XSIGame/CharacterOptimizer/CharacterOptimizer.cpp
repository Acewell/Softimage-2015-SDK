/* -----------------------------------------------------------------------------------------------------

 Version v1.0
 Description: Plugin to export a complex character to an optimized dotXSI file.

 Usage :   Create a character driven by a rig constructed with the Buiped Guide. Make
			sure that a NULL shadow rig is attached to the Rig (see Biped Guide for
			further reading on shadow rigs).
			After animating the character, branch select the NULL Shadow Rig and plot
			all transformations to an action.
			To export the optimized character, goto File->Export->Optimized Character.
            			
 Author: Dominic Laflamme ( Softimage )
 Email: dolaflam@softimage.com
 
-------------------------------------------------------------------------------------------------------- */

#include "stdafx.h"
#include <SIBCArray.h>
#include <SemanticLayer.h>
#include "CharacterOptimizer.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

namespace XSI
{

const FLOAT g_RADTODEG = 57.29577951308232286465f; // Radians to Degrees

typedef struct tagOptimizedTriangle
{
	int m_iIndices[3];
	int m_iIndicesNormals[3];
	int	m_iMaterialIndex;
	int m_iIndicesUVs[2][3];

} OptimizedTriangle;

typedef struct tagOptimizedDeformer
{

	XSI::X3DObject	m_pNode;
	CSLModel*		m_pOptimizedNode;

} OptimizedDeformer;

typedef struct _HierarchicalLevel
{
	int m_iLevelsDeep;
	XSI::CRef m_cref;
} HierarchicalLevel;

void W2AHelper( LPSTR out_sz, LPCWSTR in_wcs, int in_cch = -1);

void A2WHelper( wchar_t* out_wcs, const char* in_sz, int in_cch = -1 );

#define A2W2(out_wcs, in_sz) \
	if (NULL == (const char *)(in_sz)) \
		*(out_wcs) = NULL; \
	else \
	{ \
		*(out_wcs) = (wchar_t*)alloca((strlen((in_sz)) + 1) * sizeof(wchar_t)); \
		A2WHelper(*(out_wcs), (in_sz)); \
	}

void A2WHelper( wchar_t* out_wcs, const char* in_sz, int in_cch )
{
	if ( out_wcs != NULL && 0 != in_cch )
	{
		out_wcs[0] = L'\0' ;

		if ( in_sz != NULL )
		{
			size_t l_iLen = 0;
			l_iLen = ::mbstowcs( out_wcs, in_sz, ( in_cch < 0 ) ? ::strlen(in_sz) + 1 : (size_t) in_cch ) ;
			assert( (int)l_iLen != -1 );

        		if ( in_cch > 0 ) { out_wcs[ in_cch - 1 ] = L'\0'; }
		}
	}
}


void	BuildModelArray (XSI::CRefArray in_RefArray);
void	BuildOptimizedDeformerList();
void	BuildAnimations();
void	MuteAllConstraints(bool);
void	ProcessAllClips( int LODLevel );

void	ExportMaterial ( XSI::Material );
void	ExportShader(CRef in_XSIParent, CSLTemplate *in_pFTKParent, CRef *io_pXSIModel, CSLTemplate **io_pFTKModel);
void	ExportImage(CRef io_pXSIModel);

CSLShaderConnectionPoint 	*FTKUConnectShader(CSLXSIShader *in_pSource, CSLXSIShader *in_pDestination, XSI::CString in_pConnection);
CSLConnectionPoint 			*FTKUConnectShader(CSLXSIShader *in_pSource, CSLXSIMaterial *in_pDestination, XSI::CString in_cConnection);
CSLShaderConnectionPoint 	*FTKUConnectImage(CSLImage *in_pSource, CSLXSIShader *in_pDestination, char *in_pConnection);
CSLVariantParameter			*FTKUSetShaderParameterValue(CSLXSIShader *in_pShader, char *in_pName, float in_fValue);
CSLVariantParameter			*FTKUSetShaderParameterValue(CSLXSIShader *in_pShader, char *in_pName, int in_lValue);
CSLVariantParameter			*FTKUSetShaderParameterValue(CSLXSIShader *in_pShader, char *in_pName, LONG in_lValue);
CSLVariantParameter			*FTKUSetShaderParameterValue(CSLXSIShader *in_pShader, char *in_pName, bool in_bValue);
CSLVariantParameter			*FTKUSetShaderParameterValue(CSLXSIShader *in_pShader, char *in_pName, char *in_pValue);

void	AnalyzeSkeleton ();
bool	IsChildOf ( XSI::SceneItem children, XSI::SceneItem obj );

void	DoExport();
void	ExportOptimizedMesh ();
int		GetUVIndex ( CSLUVCoordArray*, float, float );

CSIBCArray<XSI::CRef>	g_pEnvelopeArray;
CSIBCArray<XSI::CRef>	g_pX3DArray;
CSIBCArray<XSI::Constraint>	g_Constraints;
CSLScene* g_pScene = NULL;
CSLModel* g_pRootModel = NULL;
CSLModel* g_pEnvelope = NULL;
XSI::CRef g_cSkeletonRoot;
char	g_szFilename[MAX_PATH];


CSIBCArray<XSI::Material> g_GlobaMatList;
CSIBCArray<OptimizedDeformer> g_Deformers;

void LogThis ( XSI::CString in_cstr )
{
	XSI::Application app;
	app.LogMessage ( in_cstr, XSI::siWarningMsg );
}

#ifdef unix
extern "C"
#endif
CStatus XSILoadPlugin( XSI::PluginRegistrar& in_reg )
{
	in_reg.PutAuthor( L"Softimage Corp" );
	in_reg.PutName( L"Character Optimizer Plug-in" );	in_reg.PutVersion( 1, 0 );

	// register property
	in_reg.RegisterProperty( L"CharacterOptimizerProperty" );	//
	// register the menu for the import and export
	
	in_reg.RegisterMenu(siMenuMainFileExportID, L"CharacterOptimizer", false, false);

	return XSI::CStatus::OK;	
}

#ifdef unix
extern "C"
#endif
XSI::CStatus CharacterOptimizer_Init( XSI::CRef& in_ref )
{
	Context ctxt = in_ref;
	Menu menu = ctxt.GetSource();

	CStatus st;
	MenuItem item;
	menu.AddCallbackItem(L"Export Optimized Character...", L"OnCharacterOptimizerMenu", item);
	
	
	return CStatus::OK;	
}


#ifdef unix
extern "C"
#endif
XSI::CStatus XSIUnloadPlugin( const XSI::PluginRegistrar& in_reg )
{

	return XSI::CStatus::OK;
}


#ifdef unix
extern "C"
#endif
XSI::CStatus OnCharacterOptimizerMenu( XSI::CRef& in_ref )
{

	DoExport();

	return CStatus::OK;
}


#ifdef unix
extern "C"
#endif
CStatus CharacterOptimizerProperty_Define( const CRef & in_Ctx )
{
	Application app ;
	CustomProperty prop = Context(in_Ctx).GetSource() ;
	Parameter param ;

	// Default capabilities for most of these parameters
	int caps = siPersistable  ;
	CValue dft ;	// Used for arguments we don't want to set

	prop.AddParameter(	L"Filename",CValue::siString, caps, 
						L"Filename", L"", 
						dft, param ) ;
		
	prop.AddParameter(	L"AnimationType",CValue::siUInt4 , caps, 
						L"Animation Source", L"", 
						CValue(0L), param ) ;	

	prop.AddParameter(	L"DisableConstraints",CValue::siBool, caps, 
						L"Temporarly Disable Constraints On Deformers", L"", 
						(bool)-1, param ) ;	

	prop.AddParameter(	L"LODLevel",CValue::siUInt4, caps, 
						L"LOD Levels", L"", 
						CValue(0L), param ) ;	

	prop.AddParameter(	L"MAXRatio",CValue::siDouble, caps, 
						L"Max Reduction Ratio", L"", 
						CValue(90.0), param ) ;


	return CStatus::OK;	
}

#ifdef unix
extern "C"
#endif
CStatus CharacterOptimizerProperty_DefineLayout( const CRef & in_Ctx )
{
	PPGLayout oLayout = Context( in_Ctx ).GetSource() ;

	PPGItem item ;

	oLayout.Clear() ;


	item = oLayout.AddItem( L"CharacterOptimizerProperty" ) ;

	oLayout.AddGroup(L"File") ;
		oLayout.AddRow() ;
				
		item = oLayout.AddItem( L"Filename",L"Export File",siControlFilePath ) ;
			item.PutAttribute( siUINoLabel, true ) ;
			item.PutAttribute( siUIFileFilter, L"Optimized Character dotXSI Files (*.xsi)|*.xsi|All Files (*.*)|*.*||" ) ;
		oLayout.EndRow() ;
	oLayout.EndGroup() ;

	oLayout.AddGroup( L"Options" ) ;
		oLayout.AddRow();
			CValueArray comboItems( 4 ) ;
			comboItems[0] = L"Shadow Rig Mixer";  comboItems[1] = CValue(0L); ;
			comboItems[2] = L"Current"; comboItems[3] = CValue(1L) ;
			item = oLayout.AddEnumControl( L"AnimationType", comboItems, L"", siControlCombo ) ;
			item.PutWidthPercentage( 25 );
			item.PutLabelPercentage( 100 );
		oLayout.EndRow();
		oLayout.AddRow();
			item = oLayout.AddItem( L"DisableConstraints" );
		oLayout.EndRow();
	oLayout.EndGroup() ;

	oLayout.AddGroup( L"LOD" ) ;
			oLayout.AddRow();
			item = oLayout.AddItem( L"LODLevel" );
			item.PutWidthPercentage( 25 );
			item.PutLabelPercentage( 100 );
		oLayout.EndRow();
		oLayout.AddRow();
			item = oLayout.AddItem( L"MAXRatio" );
			item.PutWidthPercentage( 25 );
			item.PutLabelPercentage( 100 );
		oLayout.EndRow();
	oLayout.EndGroup() ;

	return CStatus::OK;	
}

void	BuildModelArray (XSI::CRefArray in_RefArray)
{
	g_pEnvelopeArray.DisposeData();
	g_pX3DArray.DisposeData();

	for (int c=0;c<in_RefArray.GetCount();c++)
	{
		
		XSI::SceneItem item = (XSI::SceneItem)in_RefArray[c];
		
		if ( item.IsValid() )
		{
			XSI::CRefArray l_pEnvelopes = item.GetEnvelopes();
			
			for (int e=0;e<l_pEnvelopes.GetCount();e++)
			{
				g_pX3DArray.Extend(1);
				g_pX3DArray[g_pX3DArray.GetUsed()-1] = in_RefArray[c];

				g_pEnvelopeArray.Extend(1);
				g_pEnvelopeArray[g_pEnvelopeArray.GetUsed()-1] = l_pEnvelopes[e];
			}
			
			
		}
		
		
		
	}
}

void	DoExport()
{
	XSI::Application	app;
	XSI::Model root = app.GetActiveSceneRoot();
	
	CStatus	st;

	Property prop;
	prop = app.GetActiveSceneRoot().GetProperties().GetItem( L"CharacterOptimizerProperty" );
	if (!prop.IsValid())
		prop = app.GetActiveSceneRoot().AddProperty( L"CharacterOptimizerProperty" ) ;

	CValueArray args(5);
	args[0] = prop;
	args[1] = L"";
	args[2] = L"CharacterOptimizerProperty";
	args[3] = (LONG)4;
	args[4] = true;
	CValue ret;
	st = app.ExecuteCommand(L"InspectObj",args,ret);
	
	if ( CStatus::OK != st ) return;

			//
	memset ( g_szFilename,0, sizeof (char) * MAX_PATH );

	Parameter parm = prop.GetParameters().GetItem(L"Filename" );
	CString	str = parm.GetValue();
	const wchar_t	* p = str.GetWideString();
	wcstombs( g_szFilename, p, wcslen (p));

	//
	// get the number of LOD levels to generate
	//
	
	parm = prop.GetParameters().GetItem(L"LODLevel");
	LONG LODLevels = (LONG) parm.GetValue();

	for (int LOD = 0; LOD < LODLevels + 1; LOD++ )
	{
		
		g_pX3DArray.DisposeData();
		g_pEnvelopeArray.DisposeData();
		g_Constraints.DisposeData();
		g_pScene = NULL;
		g_pRootModel = NULL;
		g_pEnvelope = NULL;
		g_GlobaMatList.DisposeData();
		g_Deformers.DisposeData();
		
		//
		//
		// First find all meshes that are enveloped.
		//
		
		BuildModelArray ( root.FindChildren(L"",XSI::siPolyMeshType,CStringArray()) );
		
		if ( g_pEnvelopeArray.GetUsed() == 0 )
		{
			app.LogMessage ( L"Envelopped mesh not found", XSI::siErrorMsg );
			return;
		}
		
		if ( g_pEnvelopeArray.GetUsed() > 1 )
		{
			app.LogMessage ( L"Too many envelopped mesh found. Not sure which one I should use.", XSI::siErrorMsg );
			return;
		}
		
		
		char l_szFixedName[MAX_PATH];

		strcpy ( l_szFixedName, g_szFilename );
		if ( LOD > 0 )
		{
			if ( LOD == 1 )
			{
				//
				// apply the polygon reduction operator
				//
				CValueArray args(4);
				CValue outArg;
				
				args[0] = XSI::CString ( L"PolygonReduction" );
				args[1] = g_pX3DArray[0];
				args[2] = XSI::CValue ( (LONG)XSI::siUnspecified );
				args[3] = XSI::CValue ( (LONG)XSI::siPersistentOperation );
				
				Application app;
				app.ExecuteCommand( L"ApplyTopoOp", args, outArg);


				//ApplyTopoOp "PolygonReduction", "polymsh", siUnspecified, siPersistentOperation
				//SetValue "polymsh.polymsh.polygonreductionop.ratio", 0

			} 

			CValueArray args(2);
			CValue outArg;
			
			float ratio = ( LOD * 90.0f ) / LODLevels;

			args[0] = XSI::CString ( XSI::X3DObject( g_pX3DArray[0]).GetFullName() + L".polymsh.polygonreductionop.ratio");
			args[1] = XSI::CValue( (float) ( ratio ));
			
			Application app;
			app.ExecuteCommand( L"SetValue", args, outArg);
			
			sprintf ( l_szFixedName, "%s_LOD%d", g_szFilename, LOD );
		}

		g_pScene = new CSLScene;
		g_pScene->Create(l_szFixedName, 3, 60);
		// Angle
		CSLAngle *l_pAngle = g_pScene->Angle();
		if ( !l_pAngle)
		{
			app.LogMessage ( L"Error opening file for writing.");
			return;
		}

		l_pAngle->SetAngleType(CSLAngle::SI_DEGREES);
		
		// Coordinate system
		g_pScene->CoordinateSystem()->SetCoordinateSystemStyle(CSLCoordinateSystem::SI_SOFTIMAGE_3D);
		
		// File Info
		CSLFileInfo *l_pFileInfo = g_pScene->FileInfo();
		l_pFileInfo->SetOriginator( "SOFTIMAGE Character Optimizer Export" );
		l_pFileInfo->SetProjectName( "XSIGame" );
		l_pFileInfo->SetUsername( "Dominic Laflamme" );
		
		// Scene Info
		CSLSceneInfo *l_pSceneInfo = g_pScene->SceneInfo();
		l_pSceneInfo->SetEnd( 100 );
		l_pSceneInfo->SetStart(0);
		l_pSceneInfo->SetFrameRate(30);
		l_pSceneInfo->SetTimingType(CSLSceneInfo::SI_FRAMES);
		
		ExportOptimizedMesh ();
		
		BuildOptimizedDeformerList();
		
		AnalyzeSkeleton();
		
		MuteAllConstraints( true );
		
		ProcessAllClips( LOD );
		
		MuteAllConstraints( false );
		
		g_pScene->Write();
		delete g_pScene;
		g_pScene = NULL;
	}

	//
	// remove the polygon reduction operator if it was added
	//
	
	if ( LODLevels > 0 )
	{
		CValueArray args(1);
		CValue outArg;
		
		args[0] = XSI::CString(((XSI::X3DObject)(g_pX3DArray[0])).GetFullName() + L".polymsh.polygonreductionop");
		
		Application app;
		app.ExecuteCommand( L"DeleteObj", args, outArg);
		
		
	}
	
}


void ExportOptimizedMesh ()
{
	XSI::Envelope env ( g_pEnvelopeArray[0] );

	env.PutMute ( true );

	XSI::X3DObject x3d ( g_pX3DArray[0] );

	XSI::Geometry geom(x3d.GetActivePrimitive().GetGeometry());
	XSI::PolygonMesh polygonmesh(geom);
	XSI::CPointRefArray points = polygonmesh.GetPoints();
	XSI::CTriangleRefArray triarray = polygonmesh.GetTriangles();
	XSI::CPolygonFaceRefArray polyarray = polygonmesh.GetPolygons();
	XSI::CPolygonNodeRefArray Nodes = polygonmesh.GetNodes();

	XSI::CRefArray samplePoints;
	geom.GetClusters().Filter(XSI::siSampledPointCluster, XSI::CStringArray(), L"", 
		samplePoints );
	
	XSI::Cluster cluster(samplePoints.GetItem(0));
	XSI::CRefArray properties = cluster.GetProperties();
	XSI::ClusterProperty clusterProp = properties[0];	
	XSI::ClusterProperty prop ( properties[0] );
	XSI::CClusterPropertyElementArray uvwElementArray(prop.GetElements());
	
	XSI::CDoubleArray uvwArray1(uvwElementArray.GetArray());
	LONG arrayCount = uvwArray1.GetCount();

	XSI::ClusterProperty clusterProp2 = properties[1];	
	XSI::ClusterProperty prop2 ( properties[1] );
	XSI::CClusterPropertyElementArray uvwElementArray2(prop2.GetElements());


	XSI::CDoubleArray uvwArray2(uvwElementArray2.GetArray());
	XSI::ClusterProperty clusterPropc = polygonmesh.GetCurrentVertexColor();
	XSI::CClusterPropertyElementArray colorElementArray(clusterPropc.GetElements());
	XSI::CDoubleArray colorArray(colorElementArray.GetArray());

	int NumUVs = 0;
	int	NumVerts = points.GetCount();
	int	NumFaces = triarray.GetCount();
	int NumNodes = Nodes.GetCount();

	if ( prop.IsValid() ) 
		NumUVs++;

	if ( prop2.IsValid() ) 
		NumUVs++;

	////////////////////////////////////////////////////////
	// Create the mesh
	////////////////////////////////////////////////////////

	g_pRootModel = g_pScene->Root()->AddModel();
	g_pRootModel->SetName ( "CharacterModel" );
	g_pRootModel->Transform()->SetScale ( CSIBCVector3D(1.0f, 1.0f, 1.0f) );
	g_pRootModel->Visibility()->SetVisibility ( true );

	CSLModel *l_pMeshModel = g_pRootModel->AddMesh();	
	g_pEnvelope = l_pMeshModel;

	l_pMeshModel->SetName("Character");
	l_pMeshModel->Visibility()->SetVisibility(SI_TRUE);

	
	////////////////////////////////////////////////////////
	// Handle the transform
	////////////////////////////////////////////////////////
	{
		XSI::KinematicState xfo = x3d.GetKinematics().GetGlobal();
		XSI::MATH::CTransformation T = xfo.GetTransform();
		
		double sx,sy,sz;
		T.GetScalingValues(sx,sy,sz);
		
		double rx,ry,rz;
		T.GetRotationFromXYZAnglesValues(rx,ry,rz);
		
		double tx,ty,tz;
		T.GetTranslationValues(tx,ty,tz);
		
		l_pMeshModel->Transform()->SetScale ( CSIBCVector3D((float)sx, (float)sy, (float)sz ));
		l_pMeshModel->Transform()->SetEulerRotation ( CSIBCVector3D((float)rx, (float)ry, (float)rz ));
		l_pMeshModel->Transform()->SetTranslation ( CSIBCVector3D((float)tx, (float)ty, (float)tz ));
	
	}

	////////////////////////////////////////////////////////
	// Static KineState ( basepose )
	////////////////////////////////////////////////////////

	if ( x3d.HasStaticKinematicState() )
	{
		XSI::StaticKinematicState basepose = x3d.GetStaticKinematicState();
		XSI::MATH::CTransformation T = basepose.GetTransform();
		l_pMeshModel->CreateBasePose();
		CSLTransform *l_pBP = l_pMeshModel->GetBasePose();

		double sx,sy,sz;
		T.GetScalingValues(sx,sy,sz);

		double rx,ry,rz;
		T.GetRotationFromXYZAnglesValues(rx,ry,rz);

		double tx,ty,tz;
		T.GetTranslationValues(tx,ty,tz);

		l_pBP->SetScale ( CSIBCVector3D((float)sx, (float)sy, (float)sz ));
		l_pBP->SetEulerRotation ( CSIBCVector3D((float)rx * g_RADTODEG, (float)ry * g_RADTODEG, (float)rz  * g_RADTODEG));
		l_pBP->SetTranslation ( CSIBCVector3D((float)tx, (float)ty, (float)tz ));
	}

	
	
	CSLMesh *l_pMesh = (CSLMesh *) l_pMeshModel->Primitive();
	CSLBaseShape *l_pShape = l_pMesh->Shape();


	////////////////////////////////////////////////////////
	// Create cluster map to materials.
	////////////////////////////////////////////////////////
	
	g_GlobaMatList.DisposeData();
	g_GlobaMatList.Extend(1);
	g_GlobaMatList[0] = x3d.GetMaterial();

	int DefaultMaterial = 0;
	CSIBCArray<LONG>	TriangleMaterialMap;
	TriangleMaterialMap.Extend( polyarray.GetCount() );

	for (LONG v=0;v<polyarray.GetCount();v++)
	{
		TriangleMaterialMap[v] = DefaultMaterial;
	}

	////////////////////////////////////////////////////////
	// get all polygon clusters on mesh
	////////////////////////////////////////////////////////

	XSI::CRefArray		allClusters;
	polygonmesh.GetClusters().Filter(L"poly",XSI::CStringArray(),L"",allClusters);
	
	for (int c=0;c<allClusters.GetCount();c++)
	{
		////////////////////////////////////////////////////////
		// get this cluster's material
		////////////////////////////////////////////////////////

		XSI::Cluster Thecluster = allClusters[c];
		XSI::Material l_pMat = Thecluster.GetMaterial();

		g_GlobaMatList.Extend(1);
		g_GlobaMatList[g_GlobaMatList.GetUsed()-1] = l_pMat;
		int ClusterMaterialIndex = g_GlobaMatList.GetUsed() - 1;
	
		////////////////////////////////////////////////////////
		// update the triangle map to point all tris using this material
		// to the correct index
		////////////////////////////////////////////////////////

		XSI::CClusterElementArray clusterElementArray = Thecluster.GetElements();
		XSI::CLongArray values(clusterElementArray.GetArray());
		LONG countPolyIndices = values.GetCount();

		for (LONG v=0;v<countPolyIndices;v++)
		{
			TriangleMaterialMap[values[v]] = ClusterMaterialIndex;
		}
	}

	////////////////////////////////////////////////////////
	// Create Materials
	////////////////////////////////////////////////////////

	for (int m=0;m<g_GlobaMatList.GetUsed();m++)
	{
		ExportMaterial ( g_GlobaMatList[m] );
	}

	l_pMeshModel->AddGlobalMaterial();
	l_pMeshModel->GlobalMaterial()->SetPropagationType(CSLGlobalMaterial::SI_BRANCH);
	l_pMeshModel->GlobalMaterial()->SetMaterial( g_pScene->GetMaterialLibrary()->GetMaterialList()[0]);


	//
	// VERTICES
	//
	
	CSLBaseShape::CSLVector3DArray *l_Vertices = l_pShape->GetVertexList();
	l_Vertices->Resize(NumVerts);
	
	// Add some normal coordinates.
	CSLBaseShape::CSLVector3DArray &l_Normals = *l_pShape->CreateNormals();
	l_Normals.Resize(NumVerts);

	CSLUVCoordArray* l_p35UVArray[2];

	for (int uvc=0;uvc<NumUVs;uvc++)
	{
		l_p35UVArray[uvc] = ((CSLShape_35*)l_pShape)->AddUVCoordArray();
		CSIBCString l_szTpName = "Texture_Projection";

		l_p35UVArray[uvc]->SetTextureProjection ( "Texture_Projection" );
		CSLBaseShape::CSLVector2DArray &l_UVs = *(l_p35UVArray[uvc])->GetUVCoordList();

		l_UVs.Resize(NumNodes);

	}

	int p;
	for( p=0; p< NumVerts; p++)
	{
		bool valid;
		XSI::MATH::CVector3 thev ( ((XSI::Point)points[p]).GetPosition() );
		XSI::MATH::CVector3 then ( ((XSI::Point)points[p]).GetNormal(valid) );
		(*l_Vertices)[p].Set ( (float)thev.GetX(), (float)thev.GetY(), (float)thev.GetZ() );
		l_Normals[p].Set ( (float)then.GetX(), (float)then.GetY(), (float)then.GetZ() );

	}

	for( p=0; p< NumNodes; p++)
	{
		if ( NumUVs )
		{
			float u = (float)uvwArray1[p*3];
			float v = (float)uvwArray1[(p*3)+1];
			
			CSLBaseShape::CSLVector2DArray &l_UVs = *(l_p35UVArray[0])->GetUVCoordList();
			
			l_UVs[p].Set ( u,v );
		}
		
		if ( NumUVs > 1)
		{
			float u = (float)uvwArray2[p*3];
			float v = (float)uvwArray2[(p*3)+1];
			
			CSLBaseShape::CSLVector2DArray &l_UVs = *(l_p35UVArray[1])->GetUVCoordList();
			
			l_UVs[p].Set ( u,v );
		}
		
		
	}

	// 
	// TRIANGLES
	//

	CSIBCArray<OptimizedTriangle>	l_pTriangleList;

	for (int t=0;t<NumFaces;t++)
	{
		XSI::Triangle tri = (XSI::Triangle)triarray.GetItem(t);
		XSI::TriangleVertex v;
		XSI::PolygonFace polyFace = polyarray[tri.GetPolygonIndex()];
		XSI::CVertexRefArray facevertArray = polyFace.GetVertices();

		l_pTriangleList.Extend(1);
		OptimizedTriangle* l_pCurrentTri = &l_pTriangleList[l_pTriangleList.GetUsed()-1];

		XSI::CLongArray triIndices = tri.GetIndexArray();
		l_pCurrentTri->m_iIndices[0] = triIndices[0];
		l_pCurrentTri->m_iIndices[1] = triIndices[1];
		l_pCurrentTri->m_iIndices[2] = triIndices[2];
		l_pCurrentTri->m_iIndicesNormals[0] = triIndices[0];
		l_pCurrentTri->m_iIndicesNormals[1] = triIndices[1];
		l_pCurrentTri->m_iIndicesNormals[2] = triIndices[2];
		l_pCurrentTri->m_iMaterialIndex = TriangleMaterialMap[tri.GetPolygonIndex()];
		for (int u=0;u<NumUVs;u++)
		{
			for (int g=0;g<3;g++)
			{
				LONG IndexOfVertexInTheMesh = tri.GetIndexArray()[g];
				//LONG UVID;
				//cluster.FindIndex ( NodeID, UVID);
				//l_pCurrentTri->m_iIndicesUVs[u][g] = UVID;
				XSI::CPolygonNodeRefArray  pNodeArray = polyFace.GetNodes();

				for (int f=0;f<facevertArray.GetCount();f++)
				{
					XSI::Vertex vert = facevertArray[f];
					if ( vert.GetIndex() == IndexOfVertexInTheMesh )
					{
						XSI::PolygonNode l_node = pNodeArray[f];
						int iIndex = l_node.GetIndex();
						l_pCurrentTri->m_iIndicesUVs[u][g] = iIndex;
					}

				}
			}
		}

	}

	for (int l=0;l<g_GlobaMatList.GetUsed();l++)
	{
		CSLTriangleList* l_Poly = l_pMesh->AddTriangleList();
		l_Poly->SetMaterial ( g_pScene->GetMaterialLibrary()->GetMaterialList()[l] );
		
		l_Poly->GetVertexIndices()->Resize( NumFaces );
		
		
		CSLTriangleList::CSLTriangleArray* l_pNormalArray = l_Poly->CreateNormalIndices();
		l_pNormalArray->Resize(NumFaces);

		SI_Int* pUVInd[2];

		for (int u=0;u<NumUVs;u++)
		{
			CSLTriangleList::CSLTriangleArray* uvIndices = l_Poly->AddUVArray();
			uvIndices->Resize(NumFaces);
			pUVInd[u] = l_Poly->GetUVIndicesPtr(u);
		}


		SI_Int *l_pnDataArray = l_Poly->GetVertexIndicesPtr();
		SI_Int *l_normalDataArray = l_Poly->GetNormalIndicesPtr();
		
		for (int i=0;i<l_pTriangleList.GetUsed();i++)
		{
			l_pnDataArray[i * 3] = l_pTriangleList[i].m_iIndices[0];
			l_pnDataArray[(i * 3) + 1]= l_pTriangleList[i].m_iIndices[1];
			l_pnDataArray[(i * 3) + 2]= l_pTriangleList[i].m_iIndices[2];

			l_normalDataArray[i * 3] = l_pTriangleList[i].m_iIndicesNormals[0];
			l_normalDataArray[(i * 3) + 1]= l_pTriangleList[i].m_iIndicesNormals[1];
			l_normalDataArray[(i * 3) + 2]= l_pTriangleList[i].m_iIndicesNormals[2];

			for (int u=0;u<NumUVs;u++)
			{
				pUVInd[u][i*3] = l_pTriangleList[i].m_iIndicesUVs[u][0];
				pUVInd[u][(i*3)+1] = l_pTriangleList[i].m_iIndicesUVs[u][1];
				pUVInd[u][(i*3)+2] = l_pTriangleList[i].m_iIndicesUVs[u][2];

			}

		}

		
		
	}
	
	env.PutMute ( false );
}

int		GetUVIndex ( CSLUVCoordArray* in_pArray, float u, float v )
{
	CSLBaseShape::CSLVector2DArray &l_UVs = *(in_pArray)->GetUVCoordList();

	for (int c=0;c<l_UVs.GetUsed();c++)
	{
		if ( l_UVs[c] == CSIBCVector2D ( u,v ) )
		{
			return c;
		}
	}

	return 0;
}

void	BuildOptimizedDeformerList()
{
	g_Deformers.DisposeData();

	XSI::Envelope env = g_pEnvelopeArray[0];

	if ( !env.IsValid() )
	{
		return;
	}

	XSI::CRefArray l_pDeformers = env.GetDeformers();

	CSLEnvelopeList* l_pEnvelopeList = g_pScene->CreateEnvelopeList();

	for (int d=0;d<l_pDeformers.GetCount();d++)
	{
		XSI::X3DObject node = XSI::X3DObject ( l_pDeformers[d] );

		XSI::CDoubleArray l_pWeights = env.GetDeformerWeights ( node,0 );
		XSI::CClusterElementArray l_cElements = env.GetElements(0);
		XSI::CLongArray indexArray = l_cElements.GetArray();
		
		LONG weightCount = 0;
		int w;
		for (w=0;w<l_pWeights.GetCount();w++)
		{
			if ( l_pWeights[w] > 0.00001f ) // TODO XSI: use min??
			{
				weightCount++;
				
			}
			
		}

		if ( !weightCount )
			continue;

		g_Deformers.Extend(1);
		g_Deformers[g_Deformers.GetUsed()-1].m_pNode = node;

		CSLModel* l_pNull = g_pRootModel->AddNull();
		
		g_Deformers[g_Deformers.GetUsed()-1].m_pOptimizedNode = l_pNull;

		l_pNull->Visibility()->SetVisibility(SI_TRUE);
		l_pNull->AddGlobalMaterial();
		l_pNull->GlobalMaterial()->SetPropagationType(CSLGlobalMaterial::SI_BRANCH);
		l_pNull->GlobalMaterial()->SetMaterial( g_pScene->GetMaterialLibrary()->GetMaterialList()[0]);


		// name
		XSI::CString fullname = node.GetName();
		char *pName = new char [ fullname.Length() + 1 ];
		W2AHelper ( pName, fullname.GetWideString() );
		l_pNull->Name().SetText ( pName );
		l_pNull->Primitive()->Name().SetText ( pName );

		delete [] pName;

		// transform
		XSI::KinematicState xfo = node.GetKinematics().GetGlobal();
		XSI::MATH::CTransformation T = xfo.GetTransform();
		double sx,sy,sz;
		T.GetScalingValues(sx,sy,sz);
		
		double rx,ry,rz;
		T.GetRotationFromXYZAnglesValues(rx,ry,rz);
		
		double tx,ty,tz;
		T.GetTranslationValues(tx,ty,tz);
		
		l_pNull->Transform()->SetScale ( CSIBCVector3D((float)sx, (float)sy, (float)sz ));
		l_pNull->Transform()->SetEulerRotation ( CSIBCVector3D((float)rx* g_RADTODEG, (float)ry* g_RADTODEG, (float)rz* g_RADTODEG ));
		l_pNull->Transform()->SetTranslation ( CSIBCVector3D((float)tx, (float)ty, (float)tz ));

		// basepose
		if ( node.HasStaticKinematicState() )
		{
			XSI::StaticKinematicState basepose = node.GetStaticKinematicState();
			XSI::MATH::CTransformation T = basepose.GetTransform();
			l_pNull->CreateBasePose();
			CSLTransform *l_pBP = l_pNull->GetBasePose();
			
			double sx,sy,sz;
			T.GetScalingValues(sx,sy,sz);
			
			double rx,ry,rz;
			T.GetRotationFromXYZAnglesValues(rx,ry,rz);
			
			double tx,ty,tz;
			T.GetTranslationValues(tx,ty,tz);
			
			l_pBP->SetScale ( CSIBCVector3D((float)sx, (float)sy, (float)sz ));
			l_pBP->SetEulerRotation ( CSIBCVector3D((float)rx * g_RADTODEG, (float)ry * g_RADTODEG, (float)rz  * g_RADTODEG));
			l_pBP->SetTranslation ( CSIBCVector3D((float)tx, (float)ty, (float)tz ));
		}

		CSLEnvelope*	l_pEnvelope = l_pEnvelopeList->AddEnvelope();
		l_pEnvelope->SetEnvelope ( g_pEnvelope );
		l_pEnvelope->SetDeformer ( l_pNull );

	

		CSLEnvelope::CSLVertexWeightArray* l_aWeightList = l_pEnvelope->GetVertexWeightList();
		l_aWeightList->Extend ( weightCount );

		weightCount = 0;
		for (w=0;w<l_pWeights.GetCount();w++)
		{
			if ( l_pWeights[w] > 0.00001f ) // TODO XSI: use min??
			{
				int VertIndex = indexArray[w];
				
				SLVertexWeight*	l_pCurrentWeight = &(*l_aWeightList)[weightCount];
				l_pCurrentWeight->m_fVertexIndex = VertIndex;
				l_pCurrentWeight->m_fWeight = l_pWeights[w];
				weightCount++;
								
			}
			
		}
		
	}
	
	
}




void W2AHelper( LPSTR out_sz, LPCWSTR in_wcs, int in_cch )
{
	if ( out_sz != NULL && 0 != in_cch )
	{
		out_sz[0] = '\0' ;

		if ( in_wcs != NULL )
		{
			size_t l_iLen = 0;
			l_iLen = ::wcstombs( out_sz, in_wcs, ( in_cch < 0 ) ? ::wcslen(in_wcs) + 1 : (size_t) in_cch ) ;

			if ( in_cch > 0 ) { out_sz[ in_cch - 1 ] = '\0'; }
		}
	}
}

void AnalyzeSkeleton ()
{

	CSIBCArray<HierarchicalLevel*> m_pHRLevels;	
	//
	// first start building a list of all deformers and 
	// find a common root for all these bones.
	// Everything lower in the hierarchy than that bone
	// will be considered a bone.
	//

	XSI::Application app;
	XSI::Model root = app.GetActiveSceneRoot();

	int highest = 9999;
	XSI::SceneItem highestobject;

	int n;
	for (n=0;n<g_Deformers.GetUsed();n++)
	{
		XSI::SceneItem item ( g_Deformers[n].m_pNode );

			
			int levels = 0;
			
			while ( item.GetParent() != root )
			{
				item = item.GetParent();
				levels++;
			}
			
			if ( levels < highest )
			{
				highest = levels;
				highestobject = g_Deformers[n].m_pNode;
			}
			m_pHRLevels.Extend(1);
			m_pHRLevels[m_pHRLevels.GetUsed()-1] = new HierarchicalLevel;
			m_pHRLevels[m_pHRLevels.GetUsed()-1]->m_iLevelsDeep = levels;
			m_pHRLevels[m_pHRLevels.GetUsed()-1]->m_cref = g_Deformers[n].m_pNode;
	}

	//
	// count the number of bones that share the highest hierarhical level
	//

	int l_iCount = 0;

	CSIBCArray<HierarchicalLevel*> l_pHighest;
	for (n=0;n<m_pHRLevels.GetUsed();n++)
	{
		if ( m_pHRLevels[n]->m_iLevelsDeep == highest )
		{
			l_iCount++;

			LogThis ( XSI::SceneItem ( m_pHRLevels[n]->m_cref ).GetName() + L" is at highest level" );

			l_pHighest.Extend(1);
			l_pHighest[l_pHighest.GetUsed()-1] = m_pHRLevels[n];
		}
	}

	if ( l_iCount == 0 )
	{
		//
		// no bones in scene...
		//

		return;
	}

	if ( l_iCount == 1 )
	{
		// one common root for every bone in the hierarchy
		//
		g_cSkeletonRoot = highestobject;
	} else {

		//
		// multiple bones have the same hierarchical level.
		// so they share a common root.
		//

		//
		// Find the first common grandparent
		//

		XSI::SceneItem firstparent = XSI::SceneItem( l_pHighest[0]->m_cref ).GetParent();

		while ( firstparent != root )
		{
			int sharecount = 0;
			for (int i=1;i<l_pHighest.GetUsed();i++)
			{
				if ( IsChildOf ( XSI::SceneItem ( l_pHighest[i]->m_cref ), firstparent ))
				{
					sharecount++;
				}

			}

			if ( sharecount == l_pHighest.GetUsed() -1 )
			{
				// found our guy
				//

				g_cSkeletonRoot = firstparent;
				break;
			}

			firstparent = firstparent.GetParent();
		}
		
		

		g_cSkeletonRoot = firstparent;
	}


	LogThis ( XSI::CString(L"Setting ") + XSI::SceneItem ( g_cSkeletonRoot ).GetName() + L" as top level bone" );


}



//********************************************************************
//
// @mfunc	IsChildOf | This function returns true if children is
//						part of obj's hierarchy
//							
//********************************************************************
bool	IsChildOf ( XSI::SceneItem children, XSI::SceneItem obj )
{
	XSI::Application app;
	XSI::Model root = app.GetActiveSceneRoot();

	while ( children != XSI::SceneItem(root) )
	{

		if ( children.GetParent() == obj )
		{
			return true;
		}

		children = children.GetParent();
	}

	return false;
}

void	MuteAllConstraints(bool in_bMute )
{

	XSI::X3DObject x3droot ( g_cSkeletonRoot );
	XSI::Application app;
	
	CStringArray emptyArray;
	CRefArray cRefArray = x3droot.FindChildren( L"", L"", emptyArray, true );

	for (int i=0;i<cRefArray.GetCount();i++)
	{
		XSI::X3DObject obj ( cRefArray[i] );
		XSI::CRefArray cnsArray = obj.GetKinematics().GetConstraints();

		for (int c=0;c<cnsArray.GetCount();c++)
		{
			XSI::Constraint cns ( cnsArray[c] );
			XSI::CString parameterPath = cns.GetFullName();
			parameterPath += XSI::CString ( L".active" );
			
			CValueArray args(2);
			CValue outArg;
			
			args[0] = parameterPath;
			args[1] = !in_bMute;

			Application app;
			app.ExecuteCommand( L"SetValue", args, outArg);


		}


	}
}

void	ProcessAllClips(int LODLevel)
{

	XSI::Application	app;
	XSI::Model root = app.GetActiveSceneRoot();
	XSI::Property PlayControl = app.GetActiveProject().GetProperties().GetItem(L"Play Control");
	
	float l_fStart = PlayControl.GetParameterValue(L"in");
	float l_fEnd = PlayControl.GetParameterValue(L"out");
	
	XSI::UIToolkit kit = app.GetUIToolkit();
	XSI::ProgressBar	m_pBar = kit.GetProgressBar();
				
	m_pBar.PutMaximum( 100 );
	m_pBar.PutMinimum( 1 );
	m_pBar.PutStep( 1 );
	m_pBar.PutValue( 1 );
	m_pBar.PutCaption( L"..." );
	m_pBar.PutStatusText( L"" );
	m_pBar.PutVisible( true );
		
	//
	// First find the mixer which contains the clips.
	//

	XSI::SceneItem scn ( g_cSkeletonRoot );

	XSI::SceneItem parent = scn.GetParent();

	while (( parent.IsValid()) && ( !parent.IsA ( XSI::siModelID )))
	{
		parent = parent.GetParent();
	}

	int sourceCount = ((XSI::Model)parent).GetSources().GetCount();

	CSLMixer* l_pMixer = NULL;

	if ( sourceCount )
	{
		l_pMixer = g_pRootModel->CreateMixer();

	}
	
	for (int s=0;s<sourceCount;s++) 
	{
		XSI::ActionSource Source = ((XSI::Model)parent).GetSources()[s];
		m_pBar.PutCaption( XSI::CString (L"Processing Action Clip: " + Source.GetName() ));

		CValueArray args(5);
		CValue outArg;
		
		args[0] = parent.GetName();
		args[1] = XSI::CString(L"Sources.") + parent.GetName() + XSI::CString(L".") + Source.GetName();
		args[2] = XSI::CString(L"");
		args[3] = parent.GetName() + XSI::CString(L".Mixer.Mixer_Anim_Track");
		args[4] = XSI::CValue(0L);
		
		Application app;
		app.ExecuteCommand( L"AddClip", args, outArg);

		//
		// Add a new action to the semantic layer
		//

		CSLAction* l_pAction = l_pMixer->AddAction();
		
		XSI::CString fullname = Source.GetName();
		char *pName = new char [ fullname.Length() + 1 ];
		W2AHelper ( pName, fullname.GetWideString() );
		l_pAction->SetName ( pName);
		delete [] pName;
		
		l_pAction->SetActionType ( CSLAction::SI_AT_FCURVE );
		l_pAction->SetStartTime ( 0.033367 );	// I have no clue what these numbers mean. :)
		l_pAction->SetEndTime ( 0.967633 );

		for (int g=0;g<g_Deformers.GetUsed();g++)
		{
			int progress_value = (LONG)(((float)g / (float)g_Deformers.GetUsed()) * 100.0f);
			m_pBar.PutValue ( progress_value );

			OptimizedDeformer* l_pDeformer = &g_Deformers[g];
			CSLActionFCurve* l_pFCurveRotX = l_pAction->AddAnimation( CSLTemplate::SI_LINEAR );
			CSLActionFCurve* l_pFCurveRotY = l_pAction->AddAnimation( CSLTemplate::SI_LINEAR );
			CSLActionFCurve* l_pFCurveRotZ = l_pAction->AddAnimation( CSLTemplate::SI_LINEAR );

			CSLActionFCurve* l_pFCurvePosX = l_pAction->AddAnimation( CSLTemplate::SI_LINEAR );
			CSLActionFCurve* l_pFCurvePosY = l_pAction->AddAnimation( CSLTemplate::SI_LINEAR );
			CSLActionFCurve* l_pFCurvePosZ = l_pAction->AddAnimation( CSLTemplate::SI_LINEAR );

			CSIBCString l_szName = l_pDeformer->m_pOptimizedNode->GetName();
			CSIBCString l_szPath;
			
			l_szPath = l_szName;
			l_szPath.Concat ( ".kine.local.rotx" );
			l_pFCurveRotX->SetParameterXSIPath (l_szPath.GetText());

			l_szPath = l_szName;
			l_szPath.Concat ( ".kine.local.roty" );
			l_pFCurveRotY->SetParameterXSIPath (l_szPath.GetText());

			l_szPath = l_szName;
			l_szPath.Concat ( ".kine.local.rotz" );
			l_pFCurveRotZ->SetParameterXSIPath (l_szPath.GetText());

			l_szPath = l_szName;
			l_szPath.Concat ( ".kine.local.posx" );
			l_pFCurvePosX->SetParameterXSIPath (l_szPath.GetText());

			l_szPath = l_szName;
			l_szPath.Concat ( ".kine.local.posy" );
			l_pFCurvePosY->SetParameterXSIPath (l_szPath.GetText());

			l_szPath = l_szName;
			l_szPath.Concat ( ".kine.local.posz" );
			l_pFCurvePosZ->SetParameterXSIPath (l_szPath.GetText());

			l_pFCurveRotX->GetLinearKeyList()->Resize((LONG)( l_fEnd - l_fStart));
			l_pFCurveRotY->GetLinearKeyList()->Resize((LONG)( l_fEnd - l_fStart));
			l_pFCurveRotZ->GetLinearKeyList()->Resize((LONG)( l_fEnd - l_fStart));
			l_pFCurvePosX->GetLinearKeyList()->Resize((LONG)( l_fEnd - l_fStart));
			l_pFCurvePosY->GetLinearKeyList()->Resize((LONG)( l_fEnd - l_fStart));
			l_pFCurvePosZ->GetLinearKeyList()->Resize((LONG)( l_fEnd - l_fStart));

			int i = 0;
			for (int t = (int)l_fStart; t < (int)l_fEnd; t++)
			{
				XSI::MATH::CTransformation T = l_pDeformer->m_pNode.GetKinematics().GetGlobal().GetTransform ( (float)t );

				double	tx, ty, tz;
				T.GetTranslationValues (tx,ty,tz);
				double rx,ry,rz;
				T.GetRotationFromXYZAnglesValues(rx,ry,rz);
				rx *= g_RADTODEG;
				ry *= g_RADTODEG;
				rz *= g_RADTODEG;

				(*l_pFCurveRotX->GetLinearKeyList() )[i].m_fTime = (float) t;
				(*l_pFCurveRotX->GetLinearKeyList() )[i].m_fValue = (float) rx;

				(*l_pFCurveRotY->GetLinearKeyList() )[i].m_fTime = (float) t;
				(*l_pFCurveRotY->GetLinearKeyList() )[i].m_fValue = (float) ry;

				(*l_pFCurveRotZ->GetLinearKeyList() )[i].m_fTime = (float) t;
				(*l_pFCurveRotZ->GetLinearKeyList() )[i].m_fValue = (float) rz;

				(*l_pFCurvePosX->GetLinearKeyList() )[i].m_fTime = (float) t;
				(*l_pFCurvePosX->GetLinearKeyList() )[i].m_fValue = (float) tx;

				(*l_pFCurvePosY->GetLinearKeyList() )[i].m_fTime = (float) t;
				(*l_pFCurvePosY->GetLinearKeyList() )[i].m_fValue = (float) ty;

				(*l_pFCurvePosZ->GetLinearKeyList() )[i].m_fTime = (float) t;
				(*l_pFCurvePosZ->GetLinearKeyList() )[i].m_fValue = (float) tz;			
				
				i++;


			}

		}
		
		
	}




}


void	ExportMaterial ( XSI::Material in_pXSIMaterial )
{
	XSI::Application app;

	Material l_XSIMaterial = in_pXSIMaterial;
	CSLMaterialLibrary *l_pFTKLibrary = g_pScene->GetMaterialLibrary();

	if(l_XSIMaterial.IsValid())
	{
		// Let's add a new material to the material library
		CSLXSIMaterial *l_pFTKMaterial = l_pFTKLibrary->AddXSIMaterial();

		// let's convert the name of the material

		XSI::CString matname = l_XSIMaterial.GetName();
		char *pName = new char [ matname.Length() + 1 ];
		W2AHelper ( pName, matname.GetWideString() );
		l_pFTKMaterial->SetName(pName);
		delete [] pName;

		// then the extra material info
		CValue l_WrapU, l_WrapV;

		CValue retVal;
		CValueArray	arg(2);

		arg[0] = l_XSIMaterial.GetFullName() + CString(L".wrapu");
		arg[1] = 1l;
		app.ExecuteCommand(L"GetValue", arg, retVal);
		l_WrapU = retVal;

		arg[0] = l_XSIMaterial.GetFullName() + CString(L".wrapv");
		arg[1] = 1l;
		app.ExecuteCommand(L"GetValue", arg, retVal);
		l_WrapV = retVal;

		CSLXSIMaterialInfo *l_pMaterialInfo = l_pFTKMaterial->CreateMaterialInfo();
		l_pMaterialInfo->SetUWrap((((LONG) l_WrapU) == 10497) ? CSLXSIMaterialInfo::SI_CLAMP : CSLXSIMaterialInfo::SI_REPEAT);
		l_pMaterialInfo->SetVWrap((((LONG) l_WrapV) == 10497) ? CSLXSIMaterialInfo::SI_CLAMP : CSLXSIMaterialInfo::SI_REPEAT);

		// grab it's custom psets
//		CCustomPSetFromXSI l_CustomPSetConverter;
//		CRef l_MaterialCRef = l_XSIMaterial;
//		_XSI_CALL(l_CustomPSetConverter.Execute(in_pContext, in_XSIParent, in_pFTKParent, &l_MaterialCRef, io_pFTKModel), L"Failed to convert custom pset");

		// let's add all the unique shaders
		int loop;
		CRefArray l_ShaderCollection = l_XSIMaterial.GetShaders();
		CRefArray l_ParameterCollection = l_XSIMaterial.GetParameters();

		for(loop = 0; loop < l_ShaderCollection.GetCount(); loop++)
		{
			CRef l_Shader = l_ShaderCollection.GetItem(loop);

			CSLTemplate *l_pNewShader;
			ExportShader(l_XSIMaterial, l_pFTKMaterial, &l_Shader, &l_pNewShader);

		}

		// let's add the connections now
		for(loop = 0; loop < l_ParameterCollection.GetCount(); loop++)
		{
			Parameter parameter = l_ParameterCollection.GetItem(loop);
			Shader l_Shader = parameter.GetSource();

			if(l_Shader.IsValid())
			{
				int loop2;
				CSLXSIShader *l_pShader = NULL;

				for(loop2 = 0; loop2 < l_pFTKMaterial->GetShaderCount(); loop2++)
				{
					XSI::CString shadername = l_Shader.GetName();
					char *pName = new char [ shadername.Length() + 1 ];
					W2AHelper ( pName, shadername.GetWideString() );
						
					if(strcmp(l_pFTKMaterial->GetShaderList()[loop2]->GetName(), pName) == 0)
					{
						l_pShader = l_pFTKMaterial->GetShaderList()[loop2];
						delete [] pName;
						break;
					}

					delete [] pName;

				}

				if(l_pShader != NULL)
				{
					CSLConnectionPoint *l_pConnectionPoint = FTKUConnectShader(l_pShader, l_pFTKMaterial, parameter.GetScriptName());
				}
				else
				{
					LogThis(L"Shader not found in connection creation");
				}
			}
		}
	}

}



CSLShaderConnectionPoint 	*FTKUConnectShader(CSLXSIShader *in_pSource, CSLXSIShader *in_pDestination, XSI::CString in_cConnection)
{
	char *in_pConnection = new char [ in_cConnection.Length() + 1 ];
	W2AHelper ( in_pConnection, in_cConnection.GetWideString() );
	
	
	// allocate 2 empty params
	CdotXSIParam *l_pNewParam = new CdotXSIParam("", SI_VT_PCHAR);
	CdotXSIParam *l_pNewParam2 = new CdotXSIParam("", SI_VT_PCHAR);

	// add the params to the param list

	// insert right after the last parameter
	in_pDestination->Template()->Params().Add( l_pNewParam, -1 );
	in_pDestination->Template()->Params().Add( l_pNewParam2, -1 );
	SI_TinyVariant l_Value;
	l_Value.variantType = SI_VT_PCHAR;
	l_Value.p_cVal = "SHADER";
	in_pDestination->Template()->Params().Item(in_pDestination->Template()->Params().GetCount()-1)->SetValue(l_Value);
	
	// allocate a new variant parameter
	SI_Int l_nIndex = (2 * in_pDestination->GetConnectionPointCount()) + (in_pDestination->GetParameterCount()) + 4;
	CSLShaderConnectionPoint *l_pNew = 0;
	_SI_NEW(l_pNew, CSLShaderConnectionPoint(in_pDestination->Template(), l_nIndex ) );

	l_pNew->SetShader(in_pSource);
	l_pNew->SetName(in_pConnection);
	// add it to the list of connection points of the material

	delete [] in_pConnection;
	return in_pDestination->ConnectConnectionPoint(l_pNew);
}

CSLConnectionPoint 	*FTKUConnectShader(CSLXSIShader *in_pSource, CSLXSIMaterial *in_pDestination, XSI::CString in_cConnection)
{	
	char *in_pConnection = new char [ in_cConnection.Length() + 1 ];
	W2AHelper ( in_pConnection, in_cConnection.GetWideString() );

	CSLConnectionPoint *l_pConnection;
	l_pConnection = in_pDestination->AddConnectionPoint();
	l_pConnection->SetName(in_pConnection);
	l_pConnection->SetShader(in_pSource);
	delete [] in_pConnection;

	return l_pConnection;

}

CSLShaderConnectionPoint 	*FTKUConnectImage(CSLImage *in_pSource, CSLXSIShader *in_pDestination, char *in_pConnection)
{
	// allocate 2 empty params
	CdotXSIParam *l_pNewParam = new CdotXSIParam("", SI_VT_PCHAR);
	CdotXSIParam *l_pNewParam2 = new CdotXSIParam("", SI_VT_PCHAR);

	// add the params to the param list

	// insert right after the last parameter
	in_pDestination->Template()->Params().Add( l_pNewParam, -1 );
	in_pDestination->Template()->Params().Add( l_pNewParam2, -1 );
	
	SI_TinyVariant l_Value;
	l_Value.variantType = SI_VT_PCHAR;
	l_Value.p_cVal = "IMAGE";
	in_pDestination->Template()->Params().Item(in_pDestination->Template()->Params().GetCount()-1)->SetValue(l_Value);

	// allocate a new variant parameter
	SI_Int l_nIndex = (2 * in_pDestination->GetConnectionPointCount()) + (in_pDestination->GetParameterCount()) + 4;
	CSLShaderConnectionPoint *l_pNew = 0;
	_SI_NEW(l_pNew, CSLShaderConnectionPoint(in_pDestination->Template(), l_nIndex ) );

	l_pNew->SetImage(in_pSource->Name().GetText());
	l_pNew->SetName(in_pConnection);
	// add it to the list of connection points of the material
	return in_pDestination->ConnectConnectionPoint(l_pNew);

}

void	ExportShader(CRef in_XSIParent, CSLTemplate *in_pFTKParent, CRef *io_pXSIModel, CSLTemplate **io_pFTKModel)
{
	CStatus status = CStatus::OK;

	Material		l_XSIMaterial = (Material) in_XSIParent;
	Shader			l_XSIShader = (Shader) *io_pXSIModel;
	CSLXSIMaterial	*l_pFTKMaterial = (CSLXSIMaterial *) in_pFTKParent;
	int				loop;

	if(l_XSIShader.IsValid())
	{
		// First let's see if our shader is already in the material shader list
		CSLXSIShader *l_pFTKShader = NULL;

		for(loop = 0; loop < l_pFTKMaterial->GetShaderCount(); loop++)
		{
			wchar_t*l_ShaderName = NULL;
			A2W2(&l_ShaderName, l_pFTKMaterial->GetShaderList()[loop]->GetName());

			if(l_XSIShader.GetName() == l_ShaderName)
			{
				return;
			}
		}

		// Let's add a new shader to the material
		l_pFTKShader = l_pFTKMaterial->AddShader();
		*io_pFTKModel = l_pFTKShader;
		
		// let's convert the name of the shader
		char l_Name[2048];

		wcstombs(l_Name, l_XSIShader.GetName().GetWideString(), 2048);
		l_pFTKShader->SetName(l_Name);
		
		XSI::CString progID = l_XSIShader.GetProgID();
		char *pName = new char [ progID.Length() + 1 ];
		W2AHelper ( pName, progID.GetWideString() );
		l_pFTKShader->SetProgID(pName);
		delete [] pName;

		l_pFTKShader->SetOutputType((CSLXSIShader::EOutputType) l_XSIShader.GetOutputType2());

		// grab it's custom psets
//		CCustomPSetFromXSI l_CustomPSetConverter;
//		CRef l_ShaderCRef = l_XSIShader;
//		_XSI_CALL(l_CustomPSetConverter.Execute(in_pContext, in_XSIParent, in_pFTKParent, &l_ShaderCRef, io_pFTKModel), L"Failed to convert custom pset");

		// let's add all the unique shaders
		CRefArray l_ShaderCollection = l_XSIShader.GetShaders();
		CRefArray l_ParameterCollection = l_XSIShader.GetParameters();

		for(loop = 0; loop < l_ShaderCollection.GetCount(); loop++)
		{
			CRef l_Shader = l_ShaderCollection.GetItem(loop);

			CSLTemplate *l_pFTKShader;
			ExportShader(l_XSIMaterial, l_pFTKMaterial, &l_Shader, &l_pFTKShader);
		}

		// let's add the connections and the parameters now
		for(loop = 0; loop < l_ParameterCollection.GetCount(); loop++)
		{
			Parameter parameter = l_ParameterCollection.GetItem(loop);
			Shader l_Shader = parameter.GetSource();
			CRef l_SomethingElse = parameter.GetSource();
			wcstombs(l_Name, parameter.GetScriptName().GetWideString(), 2048);

			// the parameter is connected to a shader
			if(l_Shader.IsValid())
			{
				int loop2;
				CSLXSIShader *l_pShader = NULL;

				for(loop2 = 0; loop2 < l_pFTKMaterial->GetShaderCount(); loop2++)
				{
					XSI::CString ShaderName = l_Shader.GetName();
					char *pName = new char [ ShaderName.Length() + 1 ];
					W2AHelper ( pName, ShaderName.GetWideString() );
					
					if(strcmp(l_pFTKMaterial->GetShaderList()[loop2]->GetName(), pName) == 0)
					{
						l_pShader = l_pFTKMaterial->GetShaderList()[loop2];
						delete [] pName;
						break;
					}
					delete [] pName;
				}

				if(l_pShader != NULL)
				{
					CSLShaderConnectionPoint *l_pConnectionPoint = FTKUConnectShader(l_pShader, l_pFTKShader, parameter.GetScriptName());
				}
				else
				{
					LogThis(L"Shader not found in connection creation");
				}
			}
			// the parameter is connected to something else
			else if(l_SomethingElse.IsValid())
			{
				ImageClip2 l_XSIImage = (ImageClip2) l_SomethingElse;
				if(l_XSIImage.IsValid())
				{
					if ( g_pScene->GetImageLibrary()==NULL)
					{
						g_pScene->CreateImageLibrary();
					}
					
					if(g_pScene->GetImageLibrary()!=NULL)
					{
						XSI::CString ImageName = l_XSIImage.GetName();
						char *pName = new char [ ImageName.Length() + 1 ];
						W2AHelper ( pName, ImageName.GetWideString() );

						//
						// export the image to the semantic layer
						//
						ExportImage(l_XSIImage);

						// find the imageclip with the same name and connect
						CSLImage *l_pFTKImageClip = g_pScene->GetImageLibrary()->FindImage(pName);
						if(l_pFTKImageClip)
						{
							CSLShaderConnectionPoint *l_pConnectionPoint = FTKUConnectImage(l_pFTKImageClip, l_pFTKShader, l_Name);
						}
						delete [] pName;

					}
				}
			}
			// the parameter is not connected
			else
			{
				int					l_ParamCount = 1;
				CRefArray			l_SubParameterCollection;
				Parameter			l_CurrentParameter = parameter;
				int					loop2;
				bool				l_IsCompound = false;

				// check if we are not dealing with a compound parameter
				// NOTE: we only support one level of nesting here
				if(wcscmp(parameter.GetType().GetWideString(), L"CompoundParameter") == 0)
				{
					l_IsCompound = true;
					l_SubParameterCollection = parameter.GetParameters();
					l_ParamCount = l_SubParameterCollection.GetCount();
				}

				for(loop2 = 0; loop2 < l_ParamCount; loop2++)
				{
					CString l_ParameterName = parameter.GetScriptName();

					if(l_IsCompound)
					{
						l_CurrentParameter = l_SubParameterCollection.GetItem(loop2);
						l_ParameterName += CString(L".");
						l_ParameterName += l_CurrentParameter.GetScriptName();
						wcstombs(l_Name, l_ParameterName.GetWideString(), 2048);
					}

					// Set the parameter value according to the type
					switch(l_CurrentParameter.GetValueType())
					{
						case CValue::siInt1 :
						case CValue::siInt2 :
						case CValue::siInt4 :
						case CValue::siUInt1 :
						case CValue::siUInt2 :
						case CValue::siUInt4 :
						{
							CValue l_ParamValue;
							LONG l_Value = 0;

							l_ParamValue = l_CurrentParameter.GetValue();
							l_Value = l_ParamValue;
							FTKUSetShaderParameterValue(l_pFTKShader, l_Name, l_Value);

						}
						break;

						case CValue::siBool :
						{
							CValue l_ParamValue = l_CurrentParameter.GetValue();
							bool l_Value = l_ParamValue;
							FTKUSetShaderParameterValue(l_pFTKShader, l_Name, l_Value);
						}
						break;

						case CValue::siFloat :
						case CValue::siDouble :
						{
							CValue l_ParamValue = l_CurrentParameter.GetValue();
							float l_Value = l_ParamValue;
							FTKUSetShaderParameterValue(l_pFTKShader, l_Name, l_Value);
						}
						break;

						case CValue::siString :
						{
							CValue l_ParamValue = l_CurrentParameter.GetValue();
							CString l_XSIString = l_ParamValue;
							char *l_pAnsiString = (char *) calloc(sizeof(char), wcslen(l_XSIString.GetWideString()) + 1);
							wcstombs(l_pAnsiString, l_XSIString.GetWideString(), wcslen(l_XSIString.GetWideString()));
							FTKUSetShaderParameterValue(l_pFTKShader, l_Name, l_pAnsiString);
							free(l_pAnsiString);
						}
						break;
						default: LogThis(XSI::CString(L"Unable to export this parameter : ")  + l_CurrentParameter.GetFullName());
						break;
					}
				}
			}
		}		
	}

	return;
}

CSLVariantParameter		*FTKUSetShaderParameterValue(CSLXSIShader *in_pShader, char *in_pName, float in_fValue)
{
	CSLVariantParameter *l_pParameter = in_pShader->AddParameter();
	SI_TinyVariant	l_Value;

	l_pParameter->SetName(in_pName);
	l_Value.variantType = SI_VT_FLOAT;
	l_Value.fVal = in_fValue;
	l_pParameter->SetValue(&l_Value);

	return l_pParameter;
}

CSLVariantParameter		*FTKUSetShaderParameterValue(CSLXSIShader *in_pShader, char *in_pName, int in_lValue)
{
	CSLVariantParameter *l_pParameter = in_pShader->AddParameter();
	SI_TinyVariant	l_Value;

	l_pParameter->SetName(in_pName);
	l_Value.variantType = SI_VT_INT;
	l_Value.nVal = in_lValue;
	l_pParameter->SetValue(&l_Value);

	return l_pParameter;
}

CSLVariantParameter		*FTKUSetShaderParameterValue(CSLXSIShader *in_pShader, char *in_pName, LONG in_lValue)
{
	CSLVariantParameter *l_pParameter = in_pShader->AddParameter();
	SI_TinyVariant	l_Value;

	l_pParameter->SetName(in_pName);
	l_Value.variantType = SI_VT_LONG;
	l_Value.lVal = in_lValue;
	l_pParameter->SetValue(&l_Value);

	return l_pParameter;
}

CSLVariantParameter		*FTKUSetShaderParameterValue(CSLXSIShader *in_pShader, char *in_pName, bool in_bValue)
{
	CSLVariantParameter *l_pParameter = in_pShader->AddParameter();
	SI_TinyVariant	l_Value;

	l_pParameter->SetName(in_pName);
	l_Value.variantType = SI_VT_BOOL;
	l_Value.boolVal = in_bValue ? 1 : 0;
	l_pParameter->SetValue(&l_Value);

	return l_pParameter;
}

CSLVariantParameter		*FTKUSetShaderParameterValue(CSLXSIShader *in_pShader, char *in_pName, char *in_pValue)
{
	CSLVariantParameter *l_pParameter = in_pShader->AddParameter();
	SI_TinyVariant	l_Value;

	l_pParameter->SetName(in_pName);
	l_Value.variantType = SI_VT_PCHAR;
	l_Value.p_cVal = in_pValue;
	l_pParameter->SetValue(&l_Value);

	return l_pParameter;
}

void	ExportImage(CRef io_pXSIModel)
{
	CStatus status = CStatus::OK;

	ImageClip2 l_ImageClip = (ImageClip2) io_pXSIModel;
	CSLImage *l_pFTKImageClip = NULL;

	// if it doesn't exist we create it
	if(l_pFTKImageClip == NULL)
	{
		CSLImageLibrary *l_pFTKImageLibrary = g_pScene->GetImageLibrary();
		l_pFTKImageClip = l_pFTKImageLibrary->AddImage();
		
		XSI::CString fullname = l_ImageClip.GetName();
		char *pName = new char [ fullname.Length() + 1 ];
		W2AHelper ( pName, fullname.GetWideString() );
		l_pFTKImageClip->SetName(pName);
		delete [] pName;
		
		// get the image
		Image l_XSIImage;
		l_XSIImage = l_ImageClip.GetImage();

		// get the source
		Source l_XSISource;
		l_XSISource = l_ImageClip.GetSource();

		// set the image info

		


		CString l_SourceFileName = l_XSISource.GetParameter(CString(L"path")).GetValue();
		pName = new char [ l_SourceFileName.Length() + 1 ];
		W2AHelper ( pName, l_SourceFileName.GetWideString() );
		l_pFTKImageClip->SetSourceFile(pName);
		delete [] pName;

		// set the image dimension

		l_pFTKImageClip->SetWidth((LONG)l_XSISource.GetParameter(CString(L"XRes")).GetValue());
		l_pFTKImageClip->SetHeight((LONG)l_XSISource.GetParameter(CString(L"YRes")).GetValue());

		// set the image depth and color space
		l_pFTKImageClip->SetChannels((l_XSIImage.GetNumChannels() == 3) ? CSLImage::SI_RGB : CSLImage::SI_RGBA);

		int l_ColorDepth = l_XSIImage.GetChannelSize() * l_XSIImage.GetNumChannels();

		if(l_ColorDepth == 24)
		{
			l_pFTKImageClip->SetColorDepth(CSLImage::SI_24BITS);
		}
		else if(l_ColorDepth == 32)
		{
			l_pFTKImageClip->SetColorDepth(CSLImage::SI_32BITS);
		}
		// set sequence info
		l_pFTKImageClip->SetFirstFrame((LONG) l_ImageClip.GetParameter(CString(L"FrameStart")).GetValue());
		l_pFTKImageClip->SetLastFrame((LONG) l_ImageClip.GetParameter(CString(L"FrameEnd")).GetValue());
		l_pFTKImageClip->SetFrameRate((float)((double) l_ImageClip.GetParameter(CString(L"FrameRate")).GetValue()));


		// set cropping and effects
		bool l_EffectsDisabled = l_ImageClip.GetParameter(CString(L"ImageDefinitionType")).GetValue();

		if(!l_EffectsDisabled)
		{
			l_pFTKImageClip->SetCropMinX((float)((double) l_ImageClip.GetParameter(CString(L"Xmin")).GetValue()));
			l_pFTKImageClip->SetCropMaxX((float)((double) l_ImageClip.GetParameter(CString(L"Xmax")).GetValue()));
			l_pFTKImageClip->SetCropMinY((float)((double) l_ImageClip.GetParameter(CString(L"Ymin")).GetValue()));
			l_pFTKImageClip->SetCropMaxY((float)((double) l_ImageClip.GetParameter(CString(L"Ymax")).GetValue()));

			// let's create our image fx template now
			CSLImageFX *l_pImageFX = l_pFTKImageClip->CreateImageFX();
			l_pImageFX->SetBlurAlpha((bool) l_ImageClip.GetParameter(CString(L"BlurAlpha")).GetValue());
			l_pImageFX->SetBlurAmount((float) ((double) l_ImageClip.GetParameter(CString(L"Amount")).GetValue()));
			l_pImageFX->SetBlurRadius((float) ((double) l_ImageClip.GetParameter(CString(L"Radius")).GetValue()));
			l_pImageFX->SetBrightness((float) ((double) l_ImageClip.GetParameter(CString(L"Brightness")).GetValue()));
			l_pImageFX->SetConvertTo16Bits((bool) l_ImageClip.GetParameter(CString(L"SixteenBitsPerChannel")).GetValue());
			l_pImageFX->SetFlipHorizontal((bool) l_ImageClip.GetParameter(CString(L"FlipX")).GetValue());
			l_pImageFX->SetFlipVertical((bool) l_ImageClip.GetParameter(CString(L"FlipY")).GetValue());
			l_pImageFX->SetGain((float) ((double) l_ImageClip.GetParameter(CString(L"Gain")).GetValue()));


			l_pImageFX->SetHue((float)((double) l_ImageClip.GetParameter(CString(L"Hue")).GetValue()));
			l_pImageFX->SetRGBA2Greyscale((bool) l_ImageClip.GetParameter(CString(L"GrayScale")).GetValue());
			l_pImageFX->SetSaturation((float)((double) l_ImageClip.GetParameter(CString(L"Saturation")).GetValue()));

			l_pImageFX->SetScalingType((CSLImageFX::EScalingType)((LONG) l_ImageClip.GetParameter(CString(L"Type")).GetValue()));

			float xscale = (float) ((double) l_ImageClip.GetParameter(CString(L"ResX")).GetValue());
			float yscale = (float) ((double) l_ImageClip.GetParameter(CString(L"ResY")).GetValue());

			xscale /= (float) l_pFTKImageClip->GetWidth();
			yscale /= (float) l_pFTKImageClip->GetHeight();

			l_pImageFX->SetHorizontalScale(xscale); 
			l_pImageFX->SetVerticalScale(yscale); 		
		}
		else
		{
			l_pFTKImageClip->SetCropMinX(0.0f);
			l_pFTKImageClip->SetCropMaxX(1.0f);
			l_pFTKImageClip->SetCropMinY(0.0f);
			l_pFTKImageClip->SetCropMaxY(1.0f);
		}
	}

	return;
}
}


