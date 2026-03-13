// CustomUI.cpp: implementation of the CXSIGameInterfaceUI class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <stdio.h>
#include <Commdlg.h>
#include <assert.h>
#include "XSIGameInterfaceUI.h"

#include "resource.h"

#include <xsi_ref.h>
#include <xsi_viewnotification.h>
#include <xsi_x3dobject.h>
#include <xsi_siobject.h>
#include <xsi_viewcontext.h>
#include <xsi_application.h>
#include <xsi_model.h>
#include <xsi_primitive.h>
#include <xsi_geometry.h>
#include <xsi_point.h>
#include <xsi_cluster.h>
#include <xsi_triangle.h>
#include <xsi_kinematicstate.h>
#include <xsi_kinematics.h>
#include <xsi_customproperty.h>
#include <xsi_polygonmesh.h>
#include <xsi_material.h>
#include <xsi_ogltexture.h>
#include <xsi_polygonnode.h>
#include <xsi_vertex.h>
#include <xsi_imageclip2.h>
#include <xsi_light.h>
#include <xsi_ogllight.h>
#include <xsi_oglmaterial.h>
#include <xsi_selection.h>
#include <xsi_geometryaccessor.h>
#include <xsi_clusterpropertybuilder.h>
#include <xsi_meshbuilder.h>
#include <xsi_doublearray.h>
#include <xsi_bitarray.h>

//
// GAME SPECIFIC
//

#include <OpenGLDisplay.h>
#include <GameState.h>
#include <DiskGameFlow.h>
#include <LevelParser.h>
#include <Level.h>
#include <debug.h>

extern HINSTANCE __gInstance;
extern char __gGameApplicationPath[MAX_PATH];
extern char __gGameDataRootPath[MAX_PATH];

LRESULT CALLBACK ControlPanelProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

//
// Helper function to convert a wide char string into ASCII
//

void W2AHelper( LPSTR out_sz, LPCWSTR in_wcs, int in_cch = -1);
bool FindCustomPSet(XSI::X3DObject &node, const XSI::CString& name, XSI::CustomProperty &prop);
void GiveMeAFile( HWND hWnd,HINSTANCE hInst, char* specname, char *extensions, char *filename, int save);
void GiveMeAColor(HWND hdlg, HINSTANCE hInst, float *r, float *g, float *b);

void A2WHelper( wchar_t* out_wcs, const char* in_sz, int in_cch = -1 );

#define A2W(out_wcs, in_sz) \
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

CXSIGameInterfaceUI*	g_PSingletonGame = NULL;

void CALLBACK RenderGame(
HWND hwnd, 
UINT uMsg, 
UINT idEvent, 
DWORD dwTime );

//
// Standard Win32 dialog callback
//

LRESULT CALLBACK	_std_view_proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

void SetXSIValue ( XSI::CString in_szString , LONG in_lValue );
void SetXSIValue ( XSI::CString in_szString , float in_fValue );

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXSIGameInterfaceUI::CXSIGameInterfaceUI()
{
	g_PSingletonGame = this;
	m_iCurrentLevel = 0;
	m_fExternalCameraControlTime = 0.0f;
	m_bLevelUpdateDone = false;
	m_bSuspendNotifications = false;
	m_hControlPanel = 0;
	m_bAutoUpdate = true;
	m_bPause = false;
}

CXSIGameInterfaceUI::~CXSIGameInterfaceUI()
{
	g_PSingletonGame = NULL;
}

HWND	CXSIGameInterfaceUI::CreateMainWindow (HINSTANCE in_hInstance, HWND in_hParent, int x, int y)
{
	HWND		hWnd;
	WNDCLASS	wc;												
	DWORD		dwExStyle;										
	DWORD		dwStyle;										
	RECT		WindowRect;										
	WindowRect.left=(LONG)0;									
	WindowRect.right=(LONG)x;								
	WindowRect.top=(LONG)0;										
	WindowRect.bottom=(LONG)y;

	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	
	wc.lpfnWndProc		= (WNDPROC) _std_view_proc;					
	wc.cbClsExtra		= 0;									
	wc.cbWndExtra		= 0;									
	wc.hInstance		= in_hInstance;
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			
	wc.hbrBackground	= NULL;									
	wc.lpszMenuName		= NULL;									
	wc.lpszClassName	= "XSIgame";								

	RegisterClass(&wc);	// dont care if it fails.
	
	dwExStyle=0;
	dwStyle=WS_CHILD;

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);	

	
	if (!(hWnd=CreateWindowEx(	dwExStyle,
								"SoftimageGame",
								"Softimage Game Demo - Softimage Integrated",
								dwStyle |						
								WS_CLIPSIBLINGS |				
								WS_CLIPCHILDREN,				
								0, 0,							
								WindowRect.right-WindowRect.left,	
								WindowRect.bottom-WindowRect.top,	
								in_hParent,							
								NULL,							
								in_hInstance,
								NULL)))							
	{
		return NULL;
	}

	ShowWindow ( hWnd, SW_SHOWNORMAL );
	UpdateWindow ( hWnd );
	return hWnd;

}

//********************************************************************
//
// @mfunc	CXSIGameInterfaceUI::Init | Creates the dialog has a child of the
//								window handle specified by the view
//								context.
//		Called when the Custom Display is created.
//********************************************************************
LRESULT	CXSIGameInterfaceUI::Init( XSI::CRef& in_pViewCtx )
{
	XSI::ViewContext l_vViewContext = in_pViewCtx;
	assert ( l_vViewContext.IsValid() );

	SetCurrentDirectory(__gGameApplicationPath);

	//
	// Create a window so that we can control some Window messages like
	// mouse movement and resizing
	//

	l_hWnd = CreateMainWindow ( __gInstance, (HWND)l_vViewContext.GetParentWindowHandle(), 640,480 );

	//
	// OpenGLDisplay is part of the XSIGame Engine
	// and provides the nested OpenGL window
	//
	
	m_pDisplay = (OpenGLDisplay*) (new OpenGLDisplay());

	//
	// Initialize the display
	//

	m_pDisplay->AutomaticTextureReload ( TRUE );
	m_pDisplay->Initialize ( __gInstance, l_hWnd, WS_CHILD, 0, NULL );
	SetWindowLong ( l_hWnd, GWL_USERDATA, (LONG)m_pDisplay);

	//
	// Get the global GameState object
	// Note: We don't need the returned pointer but this also has the effect of 
	// performing initialization

	GetGameState ( m_pDisplay );


	//
	LevelLoader* loader;
	loader = new LevelLoader ( m_pDisplay );

	m_pLevels.Extend ( loader->m_Levels.GetUsed() + 1 );

	// Level 0 is actually the "Welcome Screen"
	m_pLevels[0] = new DiskGameFlow ( m_pDisplay );

	// Remember the true levels
	for (int c=1;c<loader->m_Levels.GetUsed()+1;c++)
	{
		m_pLevels[c] = loader->m_Levels[c-1];
	}


	m_uiLasttickCount = GetTickCount ();
	

	// Create a timer that will update the game
	// every 30 milliseconds. 
	// Reduce this value to get more performance out of the game at
	// the expense of reducing Softimage's responsiveness
	m_uiTimer = SetTimer ( NULL, 0, 30, RenderGame );	

	return S_OK;
}

void CXSIGameInterfaceUI::Render()
{
	DEBUGENTRY ( "CXSIGameInterfaceUI::Render");

	static int l_iFramesRendered = 0;
	static float l_fAverageFPS = 0;

	m_dwTickCount = GetTickCount ();
	
	m_pDisplay->BeginRender ();
	m_pDisplay->Render ();
	if ( !m_pLevels[m_iCurrentLevel]->IsInitialized () )
	{
		// Block notifications while the Game modifies Softimage content
		m_bSuspendNotifications = true;

		SetCurrentDirectory(__gGameDataRootPath);
		m_pLevels[m_iCurrentLevel]->Initialize ();

		//
		// Send the level to Softimage!
		//

		UpdateXSI();

		m_bSuspendNotifications = false;
	}

	m_fExternalCameraControlTime -= (m_dwTickCount - m_uiLasttickCount);

	if ( m_fExternalCameraControlTime < 0.0f )
	{
		// give the game back the control of the camera
		GetGameState(m_pDisplay)->ExternalCameraControl ( false );
	}


	int result = m_pLevels[m_iCurrentLevel]->Render ( m_dwTickCount - m_uiLasttickCount );
	
	m_pDisplay->EndRender ();
	
	l_iFramesRendered++;
	l_fAverageFPS += ( 1.0f / ( (m_dwTickCount - m_uiLasttickCount) / 1000.0f));

	if ( l_iFramesRendered == 10 )
	{
		GetGameState(m_pDisplay)->SetFPS(l_fAverageFPS/10.0f);
		l_fAverageFPS = 0;
		l_iFramesRendered = 0;

	}

	m_uiLasttickCount = m_dwTickCount;
	
	if ( !result )
	{
	
	
		NextLevel();
		
	
	}
	

}

void	CXSIGameInterfaceUI::UpdateLights ()
{

	DEBUGENTRY ( "CXSIGameInterfaceUI::UpdateLights");

	Geometry* l_pLevel = GetGameState( m_pDisplay )->GetGeometry();

	if ( !l_pLevel )
		return;

	l_pLevel->m_Lights.DisposeData();


	XSI::Application app;
	XSI::Model root = app.GetActiveSceneRoot();

	XSI::CRefArray childArray = root.FindChildren(L"",XSI::siLightPrimType,XSI::CStringArray());

	glMatrixMode ( GL_MODELVIEW );

	glPushMatrix();

	glLoadIdentity();

	for (int o=0;o<GL_MAX_LIGHTS;o++)
	{
		glDisable ( GL_LIGHT0 + o );
	}

	
	for (int l=0;l<childArray.GetCount();l++)
	{
		XSI::Light light( childArray[l] );
		XSI::OGLLight ogllight = light.GetOGLLight();
		XSI::MATH::CTransformation lightXfo = light.GetKinematics().GetGlobal().GetTransform();
		double x,y,z;
		lightXfo.GetTranslationValues(x,y,z);
		int lID = GL_LIGHT0 + l;

		glEnable ( lID );
		float values[4];
		float inte[4];
		float color[4];
		XSI::CColor lcolor = ogllight.GetColor();

		color[0] = (float)lcolor.r;
		color[1] = (float)lcolor.g;
		color[2] = (float)lcolor.b;
		color[3] = 1.0f;

		switch ( ogllight.GetType() )
		{

		case XSI::siLightPoint:
			values[3] = 1.0f;
			break;
		case XSI::siLightInfinite:
		case XSI::siLightSun:
			lightXfo.GetRotationFromXYZAnglesValues(x,y,z);
			values[3] = 0.0f;
			break;

		case XSI::siLightSpot:
			{
				XSI::MATH::CVector3 interest = ogllight.GetLightInterestPosition();
				inte[0] = (float)interest.GetX();
				inte[1] = (float)interest.GetY();
				inte[2] = (float)interest.GetZ();
				glLightfv ( lID, GL_SPOT_DIRECTION, inte);
				break;
			}
		}

		values[0] = (float)x;
		values[1] = (float)y;
		values[2] = (float)z;

		glLightfv ( lID, GL_POSITION, values );
		glLightfv ( lID, GL_DIFFUSE, color );
		glLightfv ( lID, GL_SPECULAR, color );

		l_pLevel->m_Lights.Extend(1);
		GameLight* ll= &l_pLevel->m_Lights[l_pLevel->m_Lights.GetUsed()-1];

		ll->x = (float)x;
		ll->y = (float)y;
		ll->z = (float)z;
		ll->r = color[0];
		ll->g = color[1];
		ll->b = color[2];
		
	}

	glPopMatrix();
}

// Push Level data from the Game into Softimage
void	CXSIGameInterfaceUI::UpdateXSI()
{
	DEBUGENTRY ( "CXSIGameInterfaceUI::UpdateXSI");

	XSI::Application app;

	//
	// First delete the previous level (if it is valid)

	if ( m_x3dObject.IsValid() )
	{
		XSI::CValueArray args1(1);
		args1[0] = m_x3dObject;
		XSI::CValue ret1;
		app.ExecuteCommand(L"DeleteObj",args1,ret1);

		//
		// delete the material
		args1[0] = XSI::CString( L"Sources.Materials.DefaultLib.Material" );
		app.ExecuteCommand(L"DeleteObj",args1,ret1);

		// 
		// delete the clip
		args1[0] = XSI::CString( L"Clips.CubeMat" );
		app.ExecuteCommand(L"DeleteObj",args1,ret1);

		// 
		// delete the assets being edited

		for (int a=0;a<m_AssetEdits.GetUsed();a++)
		{
			XSI::CRefArray childArray = m_AssetEdits[a].m_mModel.FindChildren(L"",L"",XSI::CStringArray());
			childArray.Add ( m_AssetEdits[a].m_mModel );
			args1[0] = childArray;
			app.ExecuteCommand(L"DeleteObj",args1,ret1);

		}

		m_AssetEdits.DisposeData();

		for (int c=0;c<m_PowerUps.GetUsed();c++)
		{
			args1[0] = m_PowerUps[c].m_object;
			app.ExecuteCommand(L"DeleteObj",args1,ret1);
		}

	}

	XSI::Model root = app.GetActiveSceneRoot();
	XSI::CRefArray childArray = root.FindChildren(L"",XSI::siLightPrimType,XSI::CStringArray());

	int v;
	for (v=0;v<childArray.GetCount();v++)
	{
		XSI::CValueArray args1(1);
		args1[0] = childArray[v];
		XSI::CValue ret1;
		app.ExecuteCommand(L"DeleteObj",args1,ret1);

	}

	

	
	//
	// Get the geometry from the gamestate

	Geometry* l_pLevel = GetGameState( m_pDisplay )->GetGeometry();
	
	if ( l_pLevel )	// l_pLevel can be NULL in the case of opening and closing screens
	{
		// create an empty mesh object first
		XSI::Model Root = app.GetActiveSceneRoot();
		
		XSI::CMeshBuilder mb;
		Root.AddPolygonMesh( L"GameLevel", m_x3dObject, mb );
				
		// Add the mesh vertices 
		LONG nVertexCount = l_pLevel->m_Vertices.GetUsed();		
		double* pVertices = (double*)malloc( sizeof(double) * nVertexCount * 3 );
		
		LONG c, i=0;
		for ( c=0; c<nVertexCount; c++ )
		{
			pVertices[i++] = l_pLevel->m_Vertices[c].position.x;
			pVertices[i++] = l_pLevel->m_Vertices[c].position.y;
			pVertices[i++] = l_pLevel->m_Vertices[c].position.z;
		}
		
		mb.AddVertices( nVertexCount, pVertices ); 
		delete [] pVertices;
				
		// Add the polygon triangless to the mesh
		LONG nPolyCount = l_pLevel->m_Polygons.GetUsed();
		LONG* pVertexIndices = (LONG*)malloc( sizeof(LONG) * nPolyCount * 3 );
		
		// Create the vertex indices for each polygon
		XSI::CLongArray	walkable;
		for ( i=0, c=0 ; c<nPolyCount; c++ )
		{
			pVertexIndices[i++] = l_pLevel->GetIndex ( l_pLevel->m_Polygons[c].v1 );
			pVertexIndices[i++] = l_pLevel->GetIndex ( l_pLevel->m_Polygons[c].v2 );
			pVertexIndices[i++] = l_pLevel->GetIndex ( l_pLevel->m_Polygons[c].v3 );

			if ( l_pLevel->m_Polygons[c].m_bWalkable )
			{
				// Remember that this polygon should be part of the walkable cluster
				walkable.Add ( c );
			}
		}		

		mb.AddTriangles( nPolyCount, pVertexIndices ); 
		delete [] pVertexIndices;
		
		// Once the vertices and polygons are defined we are ready to build the 
		// mesh
		mb.Build(false /* no undo */ );
		
		if ( walkable.GetCount() )
		{
			//
			// create the walkable polygon cluster
			//

			XSI::Cluster myCls ;
			m_x3dObject.GetActivePrimitive().GetGeometry().AddCluster(XSI::siPolygonCluster, L"Walkable", walkable, myCls ) ;
		}

		// Add the material	property
		XSI::Material l_matMaterial;
		m_x3dObject.AddMaterial(L"Phong", true, L"CubeMat", l_matMaterial);
							
		// add a UV property
		XSI::PolygonMesh polymesh(m_x3dObject.GetActivePrimitive().GetGeometry());		
		XSI::CClusterPropertyBuilder cpb = polymesh.GetClusterPropertyBuilder();
		XSI::ClusterProperty UVWProp = cpb.AddUV();
		
		// Add the game texture to the mesh
		XSI::Application	app;
		XSI::CValueArray	args(4);
		XSI::CValue			outArg;
		XSI::CStatus		st;
		
		args[0] = XSI::CValue( XSI::CString(L"Image") );
		args[1] = XSI::CValue(m_x3dObject.GetRef());
		args[2] = XSI::CValue((short)1);
		args[3] = XSI::CValue(false);
		st = app.ExecuteCommand( L"BlendInPresets", args, outArg );
		
		XSI::CValueArray clipargs(3);
		XSI::ImageClip2 l_pClip;
				
		// All textures are stored relative to the GameDataRootPath
		char fulltexturename[MAX_PATH];
		sprintf ( fulltexturename, "%s\\data\\textures\\%s", __gGameDataRootPath, l_pLevel->m_szLevelTextureFilename );
		LPWSTR l_wszClipName;
		A2W(&l_wszClipName,fulltexturename);
		
		clipargs[0] = XSI::CValue( XSI::CString(l_wszClipName) );
		clipargs[1] = XSI::CValue( XSI::CString(L"CubeMat") );
		clipargs[2] = XSI::CValue(l_pClip.GetRef());
		app.ExecuteCommand( L"SICreateImageClip", clipargs, outArg );
		
		XSI::CString l_szImageNode = L"Sources.Materials.DefaultLib.Material.CubeMat.ambient_blend.Image.tex";
		XSI::CString l_szFullclipname = L"Clips.CubeMat";
				
		XSI::CValueArray	clipargs2(2);
		clipargs2[0] = XSI::CValue( XSI::CString(l_szFullclipname) );
		clipargs2[1] = XSI::CValue( XSI::CString(l_szImageNode) );
		
		app.ExecuteCommand( L"SIConnectShaderToCnxPoint", clipargs2, outArg );

		{
			// Set UV values for the texture with the UV values inside the Level
	
			// allocate array for storing the UV values	
			XSI::CGeometryAccessor ga = polymesh.GetGeometryAccessor();
			
			XSI::CLongArray nodeIndices;
			ga.GetNodeIndices( nodeIndices );
			
			LONG nUVElementCount = nodeIndices.GetCount();			
			float* pUVValues = (float*)malloc(sizeof(float)*nUVElementCount*3);
			
			XSI::CLongArray vtxIndices;
			ga.GetVertexIndices( vtxIndices );
			
			LONG nPolygonCount = ga.GetPolygonCount();
			
			// loop over the polygons and set the texture coordinates
			for ( LONG i=0; i<nPolygonCount; i++ )
			{
				// set the uv associated to this polygon nodes
				for ( LONG j=0; j<3; j++ )
				{
					LONG polyOffset = i*3+j;					
					LONG vtxIndex = vtxIndices[polyOffset];					
					LONG uvIndex = nodeIndices[polyOffset] * 3;
			
					// get the level uv corresponding to this polygon vertex		
					pUVValues[ uvIndex   ] = l_pLevel->m_Vertices[vtxIndex].uv.x;
					pUVValues[ uvIndex+1 ] = l_pLevel->m_Vertices[vtxIndex].uv.y;
					pUVValues[ uvIndex+2 ] = 0.0f;
				}				
			}	
	
			// Set the new UV values			
			UVWProp.SetValues( pUVValues, nodeIndices.GetCount() );
			delete [] pUVValues;
		}

		//
		// add the power ups
		//

		for (c=0;c<l_pLevel->m_PowerUps.GetUsed();c++)
		{
			//
			// create an implcit object that will represent the power up

			XSI::X3DObject l_x3dPowerUp;
			Root.AddGeometry(L"Sphere", L"", L"PowerUp", l_x3dPowerUp);

			//
			// add the custom property

			XSI::CustomProperty Poweru;
			XSI::Parameter rate;
			l_x3dPowerUp.AddCustomProperty(L"PowerUp",0,Poweru );
			
			Poweru.AddParameter(L"rate", XSI::CValue::DataType::siDouble, XSI::siAnimatable , L"rate", L"rate",(float)l_pLevel->m_PowerUps[c].m_fRate, (float)0.0f,(float)100.0f, (float)0.0f , (float)100.0f, rate);
		
			//
			// move it to its location
			XSI::KinematicState l_Global = l_x3dPowerUp.GetKinematics().GetGlobal();

			((XSI::Parameter)(l_Global.GetParameters().GetItem( L"posx" ))).PutValue( l_pLevel->m_PowerUps[c].x );
			((XSI::Parameter)(l_Global.GetParameters().GetItem( L"posy" ))).PutValue( l_pLevel->m_PowerUps[c].y );
			((XSI::Parameter)(l_Global.GetParameters().GetItem( L"posz" ))).PutValue( l_pLevel->m_PowerUps[c].z );

			//
			// make it smaller
			((XSI::Parameter)(l_Global.GetParameters().GetItem( L"sclx" ))).PutValue( 0.1 );
			((XSI::Parameter)(l_Global.GetParameters().GetItem( L"scly" ))).PutValue( 0.1 );
			((XSI::Parameter)(l_Global.GetParameters().GetItem( L"sclz" ))).PutValue( 0.1 );
				

			//
			// add this powerup to our list
			m_PowerUps.Extend(1);
			m_PowerUps[m_PowerUps.GetUsed()-1].m_object = l_x3dPowerUp;
			m_PowerUps[m_PowerUps.GetUsed()-1].m_index = c;
			
		}

		//
		// create the lights
		//

		for (v=0;v<l_pLevel->m_Lights.GetUsed();v++)
		{
			XSI::Light light;
			root.AddLight( L"Point", false, L"LevelLight", light);

			XSI::MATH::CTransformation lightXfo;
			lightXfo.SetTranslationFromValues( l_pLevel->m_Lights[v].x, 
											l_pLevel->m_Lights[v].y,
											l_pLevel->m_Lights[v].z );
			
			light.GetKinematics().GetGlobal().PutTransform(lightXfo);

			XSI::CString vpath = light.GetName() + L".light.soft_light.color.";

			XSI::CValueArray	args(2);
			XSI::CValue			outArg;
			args[0] = XSI::CValue( vpath + L"red" );
			args[1] = XSI::CValue(l_pLevel->m_Lights[v].r);
			app.ExecuteCommand( L"SetValue", args, outArg );

			args[0] = XSI::CValue( vpath + L"green" );
			args[1] = XSI::CValue(l_pLevel->m_Lights[v].g);
			app.ExecuteCommand( L"SetValue", args, outArg );

			args[0] = XSI::CValue( vpath + L"blue" );
			args[1] = XSI::CValue(l_pLevel->m_Lights[v].b);
			app.ExecuteCommand( L"SetValue", args, outArg );
		}
		
	}
}

void	CXSIGameInterfaceUI::NextLevel()
{
	
	m_bSuspendNotifications = true;

	m_pLevels[m_iCurrentLevel]->Unload();
		
	//
	// reset game state
	GetGameState ( m_pDisplay )->ResetForNextLevel();
	
	m_iCurrentLevel++;
	
	if ( m_iCurrentLevel == m_pLevels.GetUsed() )
	{
		m_iCurrentLevel = 0;
	}

	m_bSuspendNotifications = false;
	
}


void	CXSIGameInterfaceUI::UpdateLevel ( XSI::Primitive in_pPrimitive, bool in_bForceFullUpdate )
{
	DEBUGENTRY ( "CXSIGameInterfaceUI::UpdateLevel");

	if ( m_bLevelUpdateDone )
		return;

	if ( !GetAutoUpdate() )
		return;

	if ( g_PSingletonGame->GetPause ())
		return;
	//
	// Get the geometry from the gamestate
	Geometry* l_pLevel = GetGameState( m_pDisplay )->GetGeometry();

	if ( !l_pLevel )
		return;

	//
	// pause the game to avoid rendering a frame
	// during an update
	//

	g_PSingletonGame->SetPause ( true );

	//
	// first check if the number of points has changed

	XSI::Geometry geomObj = in_pPrimitive.GetGeometry();
	LONG nPoints = geomObj.GetPoints().GetCount();

	bool l_bRequireFullUpdate = false;

	if ( l_pLevel->m_Vertices.GetUsed() != nPoints )
	{
		l_bRequireFullUpdate = true;
	}

	//
	// Check if the number of triangles jhas changed
	
	XSI::CTriangleRefArray tris = geomObj.GetTriangles();

	LONG triCount = tris.GetCount();
	if(tris.GetCount() != l_pLevel->m_Polygons.GetUsed())
	{
		l_bRequireFullUpdate = true;
	}

	if ( in_bForceFullUpdate )
	{
		l_bRequireFullUpdate = true;
	}

	if ( l_bRequireFullUpdate )
		m_bLevelUpdateDone = true;

	CSIBCArray<LONG> WalkablePolygons;

	if ( !l_bRequireFullUpdate)
	{
		//
		// just update the position of the vertices

		XSI::CPointRefArray pointCollection = geomObj.GetPoints();
		XSI::ClusterProperty frictionMap = GetFrictionMap();

		XSI::CFloatArray frictionArray;
		frictionMap.GetValues( frictionArray );

		for (LONG p=0;p<nPoints;p++)
		{
			XSI::Point pnt = pointCollection[p];
			XSI::MATH::CVector3 pos = pnt.GetPosition();

			l_pLevel->m_Vertices[p].position.x = (float)pos.GetX();
			l_pLevel->m_Vertices[p].position.y = (float)pos.GetY();
			l_pLevel->m_Vertices[p].position.z = (float)pos.GetZ();
			l_pLevel->m_Vertices[p].friction = frictionArray[p];

		}


	} else {

		//
		// build a list of polygon IDs that are part of the walkable cluster
		//
		
		XSI::PolygonMesh polygonmesh(geomObj);
		XSI::CRefArray		allClusters;
		polygonmesh.GetClusters().Filter(L"poly",XSI::CStringArray(),L"",allClusters);
		
		//
		// Always use cluster 0 as the walkable cluster
		//

		XSI::Cluster Thecluster = allClusters[0];
		XSI::CClusterElementArray clusterElementArray = Thecluster.GetElements();
		XSI::CLongArray values(clusterElementArray.GetArray());
		LONG countPolyIndices = values.GetCount();
		for (LONG v=0;v<countPolyIndices;v++)
		{
			WalkablePolygons.Extend(1);
			WalkablePolygons[WalkablePolygons.GetUsed()-1] = values[v];
		}
		
		//
		// Tell the GameState to zap the current geometry; we will rebuild it from sratch

		GetGameState( m_pDisplay )->ResetGeometry();
		l_pLevel = GetGameState( m_pDisplay )->GetGeometry();

		//
		// add the vertices
		XSI::CPointRefArray pointCollection = geomObj.GetPoints();
		XSI::ClusterProperty frictionMap = GetFrictionMap();
		XSI::CFloatArray frictionArray;
		frictionMap.GetValues( frictionArray );

		for (LONG p=0;p<nPoints;p++)
		{
			bool l_bValid;
			XSI::Point pnt = pointCollection[p];
			XSI::MATH::CVector3 pos = pnt.GetPosition();
			XSI::MATH::CVector3 nrm = pnt.GetNormal(l_bValid);
			float friction = 0.0f;
			if ( frictionMap.IsValid() )
			{
				friction = frictionArray[p];
			}
			l_pLevel->AddVertex ((float)pos.GetX(), (float)pos.GetY(), (float)pos.GetZ(), 
								(float)nrm.GetX(), (float)nrm.GetY(), (float)nrm.GetZ(), 
								0.0f, 0.0f, friction);
		}
		
		//
		// add the polygons
		for (LONG t=0;t<tris.GetCount();t++)
		{
			XSI::Triangle tri = tris[t];
			XSI::CUVArray UVArray = tri.GetUVArray();
			XSI::MATH::CVector3Array l_PosArray = tri.GetPositionArray();
			tri.GetIndexArray();
			/*
			LONG v1 = l_pLevel->GetIndex ( l_PosArray[0].GetX(), l_PosArray[0].GetY(), l_PosArray[0].GetZ() );
			LONG v2 = l_pLevel->GetIndex ( l_PosArray[1].GetX(), l_PosArray[1].GetY(), l_PosArray[1].GetZ() );
			LONG v3 = l_pLevel->GetIndex ( l_PosArray[2].GetX(), l_PosArray[2].GetY(), l_PosArray[2].GetZ() );
			*/
			LONG v1 = tri.GetIndexArray()[0];
			LONG v2 = tri.GetIndexArray()[1];
			LONG v3 = tri.GetIndexArray()[2];

			assert ( v1 >= 0 );
			assert ( v2 >= 0 );
			assert ( v3 >= 0 );

			l_pLevel->m_Vertices[v1].uv.x = (float)UVArray[0].u;
			l_pLevel->m_Vertices[v1].uv.y = (float)UVArray[0].v;

			l_pLevel->m_Vertices[v2].uv.x = (float)UVArray[1].u;
			l_pLevel->m_Vertices[v2].uv.y = (float)UVArray[1].v;

			l_pLevel->m_Vertices[v3].uv.x = (float)UVArray[2].u;
			l_pLevel->m_Vertices[v3].uv.y = (float)UVArray[2].v;
			//
			// walkable or not?
			LONG polyID = tri.GetPolygonIndex();
			bool walkable = false;

			for (LONG c=0;c<WalkablePolygons.GetUsed();c++)
			{
				if ( WalkablePolygons[c] == polyID )
				{
					walkable = true;

					XSI::MATH::CVector3Array normalArray = tri.GetPolygonNodeNormalArray();
					XSI::MATH::CVector3 normal;
					normal += normalArray[0];
					normal += normalArray[1];
					normal += normalArray[2];
					normal *= ( 1.0f / 3.0f );

					l_pLevel->m_Vertices[v1].normal.x = (float)normal.GetX();
					l_pLevel->m_Vertices[v1].normal.y = (float)normal.GetY();
					l_pLevel->m_Vertices[v1].normal.z = (float)normal.GetZ();

					l_pLevel->m_Vertices[v2].normal.x = (float)normal.GetX();
					l_pLevel->m_Vertices[v2].normal.y = (float)normal.GetY();
					l_pLevel->m_Vertices[v2].normal.z = (float)normal.GetZ();

					l_pLevel->m_Vertices[v3].normal.x = (float)normal.GetX();
					l_pLevel->m_Vertices[v3].normal.y = (float)normal.GetY();
					l_pLevel->m_Vertices[v3].normal.z = (float)normal.GetZ();

					break;
				}
			}

			l_pLevel->AddPolygon ( &l_pLevel->m_Vertices[v1], 
									&l_pLevel->m_Vertices[v2],
									&l_pLevel->m_Vertices[v3], walkable);

		}

	}

	XSI::Material mat = m_x3dObject.GetMaterial();
	XSI::OGLMaterial oglmat = mat.GetOGLMaterial();

	XSI::CColor c1 = oglmat.GetDiffuse();
	XSI::CColor c2 = oglmat.GetSpecular();
	XSI::CColor c3 = oglmat.GetAmbient();
	double		decay = oglmat.GetDecay();

	l_pLevel->ambient[0] = (float)c3.r;
	l_pLevel->ambient[1] = (float)c3.g;
	l_pLevel->ambient[2] = (float)c3.b;
	l_pLevel->ambient[3] = (float)c3.a;

	l_pLevel->diffuse[0] = (float)c1.r;
	l_pLevel->diffuse[1] = (float)c1.g;
	l_pLevel->diffuse[2] = (float)c1.b;
	l_pLevel->diffuse[3] = (float)c1.a;

	l_pLevel->specular[0] = (float)c2.r;
	l_pLevel->specular[1] = (float)c2.g;
	l_pLevel->specular[2] = (float)c2.b;
	l_pLevel->specular[3] = (float)c2.a;
	l_pLevel->shininess = (float)decay;
	


	XSI::OGLTexture ogltexture = mat.GetOGLTexture();
	if ( ogltexture.IsValid() )
	{
		XSI::CString fullname = ogltexture.GetFullName();
		char *pName = new char [ fullname.Length() + 1 ];
		W2AHelper ( pName, fullname.GetWideString() );

		char fname[MAX_PATH];
		char extension[MAX_PATH];
		_splitpath ( pName, NULL, NULL, fname, extension );

		sprintf ( fname, "%s%s", fname, extension );

		if ( strcmp ( fname, l_pLevel->m_szLevelTextureFilename ) )
		{
			strcpy ( l_pLevel->m_szLevelTextureFilename, fname );

			if ( l_pLevel->m_iLevelTexture )
			{
				glDeleteTextures ( 1, (const unsigned int *)&l_pLevel->m_iLevelTexture);
			}
			l_pLevel->m_iLevelTexture = m_pDisplay->AddTexture ( fname );
		}
	}

	l_pLevel->BuildAjdacentList();

	UpdateLights();

	GetCurrentLevel()->CreateSky ();

	l_pLevel->Save ( m_pLevels[m_iCurrentLevel]->m_szLevelFilename );

	g_PSingletonGame->SetPause ( false );

}

void	CXSIGameInterfaceUI::SyncPowerUp ( XSI::X3DObject in_power )
{
	DEBUGENTRY ( "CXSIGameInterfaceUI::SyncPowerUp");

	Geometry* l_pLevel = GetGameState(m_pDisplay)->GetGeometry ();

	if ( l_pLevel )
	{
		for (int p=0;p<m_PowerUps.GetUsed();p++)
		{
			if ( m_PowerUps[p].m_object == in_power )
			{
				XSI::KinematicState l_Global = in_power.GetKinematics().GetGlobal();

				l_pLevel->m_PowerUps[m_PowerUps[p].m_index].x = ((XSI::Parameter)(l_Global.GetParameters().GetItem( L"posx" ))).GetValue();
				l_pLevel->m_PowerUps[m_PowerUps[p].m_index].y = ((XSI::Parameter)(l_Global.GetParameters().GetItem( L"posy" ))).GetValue();
				l_pLevel->m_PowerUps[m_PowerUps[p].m_index].z = ((XSI::Parameter)(l_Global.GetParameters().GetItem( L"posz" ))).GetValue();

				XSI::CustomProperty customProp;
				FindCustomPSet ( in_power, L"PowerUp", customProp);

				if ( customProp.IsValid() )
				{
					XSI::Parameter param = customProp.GetParameters()[1];
					l_pLevel->m_PowerUps[m_PowerUps[p].m_index].m_fRate = param.GetValue();

				}

				l_pLevel->Save ( m_pLevels[m_iCurrentLevel]->m_szLevelFilename );
				
				break;
			}
		}

	}

}

void	CXSIGameInterfaceUI::SyncCamera ( XSI::Camera in_Camera)
{
	DEBUGENTRY ( "CXSIGameInterfaceUI::SyncCamera");

	Geometry* l_pLevel = GetGameState(m_pDisplay)->GetGeometry ();

	if ( l_pLevel )
	{
		XSI::KinematicState l_Global = in_Camera.GetKinematics().GetGlobal();

		CSIBCVector3D from;
		CSIBCVector3D to;

		from.m_fX = ((XSI::Parameter)(l_Global.GetParameters().GetItem( L"posx" ))).GetValue();
		from.m_fY = ((XSI::Parameter)(l_Global.GetParameters().GetItem( L"posy" ))).GetValue();
		from.m_fZ = ((XSI::Parameter)(l_Global.GetParameters().GetItem( L"posz" ))).GetValue();

		to.m_fX = ((XSI::Parameter)(in_Camera.GetInterest().GetKinematics().GetGlobal().GetParameters().GetItem( L"posx" ))).GetValue();
		to.m_fY = ((XSI::Parameter)(in_Camera.GetInterest().GetKinematics().GetGlobal().GetParameters().GetItem( L"posy" ))).GetValue();
		to.m_fZ = ((XSI::Parameter)(in_Camera.GetInterest().GetKinematics().GetGlobal().GetParameters().GetItem( L"posz" ))).GetValue();

		GetGameState(m_pDisplay)->SetCameraPosition ( from, to, true );
		GetGameState(m_pDisplay)->ExternalCameraControl ( true );
		m_fExternalCameraControlTime = 1000.0f * 10.0f;	// keep the control of the camera for 10 seconds
	}

}

void	CXSIGameInterfaceUI::SetCameraType ( int in_iType )
{
	GetGameState(m_pDisplay)->SetCameraType ( in_iType );
}


void	CXSIGameInterfaceUI::AddPowerUp ( XSI::X3DObject in_PowerUp )
{
	Geometry* l_pLevel = GetGameState(m_pDisplay)->GetGeometry();

	if ( l_pLevel )
	{
		PowerUp power;
		memset ( &power, 0, sizeof(PowerUp));
		int index = l_pLevel->AddPowerUp (&power);

		m_PowerUps.Extend(1);
		m_PowerUps[m_PowerUps.GetUsed()-1].m_object = in_PowerUp;
		m_PowerUps[m_PowerUps.GetUsed()-1].m_index = index;

		l_pLevel->Save (m_pLevels[m_iCurrentLevel]->m_szLevelFilename);
		

	}
}

void	CXSIGameInterfaceUI::ReloadEnemies ()
{
	GetGameState( m_pDisplay )->ReloadEnemies ();
}

void	CXSIGameInterfaceUI::ReloadPlayer ()
{
	GetGameState( m_pDisplay )->LoadPlayer ();
}

void	CXSIGameInterfaceUI::ReloadSky ()
{
	
}


//********************************************************************
//
// @mfunc	CXSIGameInterfaceUI::Term | Destroys the dialog
//
//********************************************************************
LRESULT	CXSIGameInterfaceUI::Term( XSI::CRef& in_pViewCtx )
{
	DEBUGENTRY ( "CXSIGameInterfaceUI::Term");

	KillGameState();

	KillTimer( NULL, m_uiTimer );

	m_pDisplay->Shutdown ();
	delete m_pDisplay;

	DestroyWindow ( l_hWnd );
	l_hWnd = NULL;

	return S_OK;
}

//********************************************************************
//
// @mfunc	CXSIGameInterfaceUI::Notify | Handles Softimage notifications
//
//********************************************************************
LRESULT CXSIGameInterfaceUI::Notify ( XSI::CRef& in_pViewCtx )
{
	DEBUGENTRY ( "CXSIGameInterfaceUI::Notify");

	using namespace XSI;

	if ( m_bSuspendNotifications )
		return S_OK;

	//
	// Convert the CRef into a ViewContext
	//

	XSI::ViewContext l_vViewContext = in_pViewCtx;
	assert ( l_vViewContext.IsValid() );

	//
	// Retrieve the notification information from the view context
	//

	XSI::siEventID in_eNotifcation;
	void*	in_pData;

	l_vViewContext.GetNotificationData ( in_eNotifcation, &in_pData );

	switch ( in_eNotifcation )
	{
	case siOnSelectionChange:
		{
			//
			// The selection list has changed. Cast the notification data
			// into a CSelectionChangeNotification pointer to get at the
			// details.
			//

			XSI::CSelectionChangeNotification* l_pSelection = (XSI::CSelectionChangeNotification*)in_pData;

			break;
			
		}

	case siOnValueChange:
		{
			//
			// Something has changed in the scene.
			//

			XSI::CString	l_szMessage;
			l_szMessage = L"XSI_SET_VALUE_CV ";
		
			XSI::CValueChangeNotification* l_pData = (XSI::CValueChangeNotification*) in_pData;

			//
			// Get the object that generated the notification
			XSI::CRef cRef = l_pData->GetOwner();
			
			XSI::X3DObject l_x3d(cRef);

			if ( l_x3d == m_x3dObject )
			{
				//
				// the level has changed in some way
			}
			
			LONG objClassID = cRef.GetClassID();
			switch (objClassID)
			{
			case XSI::siCustomPropertyID:
				{
					//
					// power up being created
					//

					XSI::CustomProperty	customProp (cRef);

					AddPowerUp ( customProp.GetOwners()[0] );
					break;

				}

				case XSI::siPrimitiveID:
				{
					XSI::Primitive primObj(cRef);
					if ( primObj.GetOwners().GetItem(0) == m_x3dObject )
					{
						UpdateLevel( primObj );
					}

					LONG objClassIDParent =  primObj.GetOwners().GetItem(0).GetClassID();

					if ( objClassIDParent == XSI::siLightID )
					{
						UpdateLights();
					}

					if ( objClassIDParent == XSI::siMaterialID )
					{
						UpdateLevel( primObj );

					}


					//l_szMessage += L": Number of points: " + CValue(nPoints).GetAsText();
				}
				break;

				case XSI::siKinematicStateID:
				{
					XSI::KinematicState kinestate(cRef);

					// get the owner, see if it's a camera
					XSI::Kinematics l_cKinematics = kinestate.GetParent();

					LONG objClassIDParent =  l_cKinematics.GetOwners()[0].GetClassID();
					if ( objClassIDParent == XSI::siCameraID )
					{
						//
						// camera has moved, sync with it
						//
						SyncCamera ( l_cKinematics.GetOwners()[0] );
					}

					if ( objClassIDParent == XSI::siLightID )
					{
						//
						// camera has moved, sync with it
						//
						UpdateLights();
					}

					if ( objClassIDParent == XSI::siX3DObjectID )
					{
						//
						// a powerup is moving
						//
						SyncPowerUp ( l_cKinematics.GetOwners()[0] );
					}
				}
				break;

				case XSI::siParameterID:
				{
					XSI::Parameter paramObj(cRef);
					XSI::CustomProperty paramParent = paramObj.GetParent();
					//SyncPowerUp ( paramParent.GetOwners()[0] );

				}
				break;

				case XSI::siClusterID:
				case XSI::siMaterialID:
				{
					XSI::Cluster clustObj(cRef);
					XSI::CClusterElementArray elemArray = clustObj.GetElements();
					
					
					//
					// a cluster has changed, check if the owner is the level
					// is so, force an update
					//

					
					LONG objClassIDParent =  clustObj.GetOwners()[0].GetClassID();

					if ( ( clustObj.GetName() != XSI::CString ( L"default_Polygon")))
					{
						UpdateLevel(  m_x3dObject.GetActivePrimitive(), true );
					}
					
				}
				break;

				case XSI::siClusterPropertyID:
					{
						XSI::ClusterProperty prop ( cRef );
						OutputDebugString ( prop.GetName().GetAsciiString());
					}
					break;

			}

			break;

		}

	}


	return S_OK;
}

//********************************************************************
//
// @mfunc	CXSIGameInterfaceUI::SetWindowSize | It is important to handle this 
//										message or else the window
//										will end up in the wrong place
//										in the Softimage UI.
//
//********************************************************************
LRESULT CXSIGameInterfaceUI::SetWindowSize(int ox, int oy, int cx, int cy)
{

	SetWindowPos( l_hWnd,NULL,ox,oy,cx,cy,SWP_NOZORDER); 

	return S_OK;
}

	
LRESULT CXSIGameInterfaceUI::Paint( WPARAM, LPARAM )
{
	
	return S_OK;
}

LRESULT CXSIGameInterfaceUI::MouseMove( WPARAM, LPARAM )
{

	return S_OK;
}

void	CXSIGameInterfaceUI::UpdateAsset( char* in_szAsset )
{
	DEBUGENTRY ( "CXSIGameInterfaceUI::UpdateAsset");

	char l_szFullPath[MAX_PATH];
	sprintf ( l_szFullPath, "%s\\data\\models\\%s",__gGameDataRootPath, in_szAsset );

	
	XSI::Model modeltoexport;
	for (int a=0;a<m_AssetEdits.GetUsed();a++)
	{
		if ( m_AssetEdits[a].m_szName == l_szFullPath )
		{
			XSI::Application app;
			
			SetXSIValue ( L"dotXSIExportOptions.output_file_format_version", 360L );
			SetXSIValue ( L"dotXSIExportOptions.animall", 1L );
			SetXSIValue ( L"dotXSIExportOptions.tesselation", 1L );
			SetXSIValue ( L"dotXSIExportOptions.animplot", 0L );
			SetXSIValue ( L"dotXSIExportOptions.envelope", 1L );
			SetXSIValue ( L"dotXSIExportOptions.output_file_format", 1L );
			SetXSIValue ( L"dotXSIExportOptions.textures", 1L );
			SetXSIValue ( L"dotXSIExportOptions.txtformat", 1L );
			
			//app.GetSelection().Clear();
			//app.GetSelection().Add(m_AssetEdits[a].m_mModel);


			XSI::CValueArray args(2);
			LPWSTR l_wszFilename;
			A2W(&l_wszFilename,l_szFullPath);
			args[1] = XSI::CValue(l_wszFilename);
			args[0] = m_AssetEdits[a].m_mModel;
			XSI::CValue retVal;
			app.ExecuteCommand( L"SIExportDotXSIFile", args, retVal );
			
			GetCurrentLevel()->ReloadAsset ( in_szAsset );

		}

	}


}

void	CXSIGameInterfaceUI::EditEnnemy()
{
	char l_szFullPath[MAX_PATH];
	sprintf ( l_szFullPath, "%s\\data\\project\\scenes\\Samurai.scn",__gGameDataRootPath );

	
	XSI::Application app;
	XSI::CValueArray args(5);

	LPWSTR l_wszFilename;
	A2W(&l_wszFilename,l_szFullPath);
	args[0] = XSI::CString(l_wszFilename);
	args[1] = args[2] = args[3] = args[4] = XSI::CString(L"");
	XSI::CValue retVal;

	app.ExecuteCommand( L"MergeScene", args, retVal );
}

void	CXSIGameInterfaceUI::EditPlayer()
{
	char l_szFullPath[MAX_PATH];
	sprintf ( l_szFullPath, "%s\\data\\project\\scenes\\player.scn",__gGameDataRootPath );

	
	XSI::Application app;
	XSI::CValueArray args(5);

	LPWSTR l_wszFilename;
	A2W(&l_wszFilename,l_szFullPath);
	args[0] = XSI::CString(l_wszFilename);
	args[1] = args[2] = args[3] = args[4] = XSI::CString(L"");
	XSI::CValue retVal;

	app.ExecuteCommand( L"MergeScene", args, retVal );

}

void	CXSIGameInterfaceUI::EditAsset( char* in_szAsset )
{
	DEBUGENTRY ( "CXSIGameInterfaceUI::EditAsset");

	XSI::Application app;
	XSI::Model root = app.GetActiveSceneRoot();

	XSI::Model newmodel;
	root.AddModel(XSI::CRefArray(), L"AssetEditing", newmodel);

	
	char l_szFullPath[MAX_PATH];
	sprintf ( l_szFullPath, "%s\\data\\models\\%s",__gGameDataRootPath, in_szAsset );

	m_AssetEdits.Extend(1);
	m_AssetEdits[m_AssetEdits.GetUsed()-1].m_szName = l_szFullPath;
	m_AssetEdits[m_AssetEdits.GetUsed()-1].m_mModel = newmodel;

	XSI::Selection selection = app.GetSelection();
	selection.Clear();
	selection.Add ( newmodel );

	// First checkout the file
	{
		XSI::CValueArray args(1);

		LPWSTR l_wszFilename;
		A2W(&l_wszFilename,l_szFullPath);
		args[0] = XSI::CValue(l_wszFilename);
		XSI::CValue retVal;

		app.ExecuteCommand( L"XSIGame_Checkout", args, retVal );
	}
	// Now import the dotXSI.
	{
		XSI::CValueArray args(1);

		LPWSTR l_wszFilename;
		A2W(&l_wszFilename,l_szFullPath);
		args[0] = XSI::CValue(l_wszFilename);
		XSI::CValue retVal;

		app.ExecuteCommand( L"SIImportDotXSIFile", args, retVal );
	}
}

void	CXSIGameInterfaceUI::AddLevel  ( char* in_szFilename )
{
	DEBUGENTRY ( "CXSIGameInterfaceUI::AddLevel ");

	m_pLevels.Extend(1);
	m_pLevels[m_pLevels.GetUsed()-1] = new Level ( m_pDisplay );
	
	char fname[MAX_PATH];
	_splitpath ( in_szFilename, NULL, NULL, fname, NULL);

	sprintf ( fname, "%s.lvl", fname );
	m_pLevels[m_pLevels.GetUsed()-1]->SetLevelFilename ( fname );

	//
	// Ask if the user want to add it to ALienbrain
	//
	{
		XSI::Application app;
		XSI::CValueArray args(1);

		LPWSTR l_wszFilename;
		A2W(&l_wszFilename,fname);
		args[0] = XSI::CValue(l_wszFilename);
		XSI::CValue retVal;

		app.ExecuteCommand( L"XSIGame_AddToAB", args, retVal );
	}

	//
	// clean up current level
	//
	NextLevel();

	//
	// jump to the new level
	//

	m_iCurrentLevel = m_pLevels.GetUsed()-1;

}

void	CXSIGameInterfaceUI::RemoveAsset  ( char* in_szFilename )
{
	m_pLevels[m_iCurrentLevel]->RemoveAsset ( in_szFilename );
	char fname[MAX_PATH];
	_splitpath ( m_pLevels[m_iCurrentLevel]->m_szLevelFilename, NULL, NULL, fname, NULL );

	sprintf ( fname, "%s.xgl", fname );

	FILE* f = fopen ( FixLevelPath ( fname ), "wt" );
	if ( !f )
		return; // perhaps level def is read only

	fprintf ( f, "level %s\n", m_pLevels[m_iCurrentLevel]->m_szLevelFilename );

	CSIBCArray<CSIBCString> assets;
	m_pLevels[m_iCurrentLevel]->GetAssets ( assets );

	for (int a=0;a<assets.GetUsed();a++)
	{
		fprintf ( f, "asset %s\n", assets[a].GetText() );
	}

	fclose(f);



}

void	CXSIGameInterfaceUI::AddAsset  ( char* in_szFilename )
{
	m_pLevels[m_iCurrentLevel]->AddAsset ( in_szFilename );
	
	SaveLevelDef();


}

void	CXSIGameInterfaceUI::SaveLevelDef ()
{
	char fname[MAX_PATH];
	_splitpath ( m_pLevels[m_iCurrentLevel]->m_szLevelFilename, NULL, NULL, fname, NULL );

	sprintf ( fname, "%s.xgl", fname );

	FILE* f = fopen ( FixLevelPath ( fname ), "wt" );
	if ( !f )
		return;	// perhaps level def file is read only

	fprintf ( f, "level %s\n", m_pLevels[m_iCurrentLevel]->m_szLevelFilename );

	CSIBCArray<CSIBCString> assets;
	m_pLevels[m_iCurrentLevel]->GetAssets ( assets );

	for (int a=0;a<assets.GetUsed();a++)
	{
		fprintf ( f, "asset %s\n", assets[a].GetText() );
	}

	fprintf ( f, "skytexture1 %s\n", GetCurrentLevel()->m_SkyTexture1 );
	fprintf ( f, "skytexture2 %s\n", GetCurrentLevel()->m_SkyTexture2 );
	fprintf ( f, "fogdistance %f\n", GetCurrentLevel()->m_fFogDistance );
	fprintf ( f, "fogcolor.red %f\n", GetCurrentLevel()->m_fFogColor[0] );
	fprintf ( f, "fogcolor.green %f\n", GetCurrentLevel()->m_fFogColor[1] );
	fprintf ( f, "fogcolor.blue %f\n", GetCurrentLevel()->m_fFogColor[2] );
	
	fclose(f);
}

void	CXSIGameInterfaceUI::SetShowSectors ( bool in_Value )
{
	GameState* l_pGameState = GetGameState ( m_pDisplay );
	l_pGameState->SetShowSectors ( in_Value );
}

void	CXSIGameInterfaceUI::SetShowAIGrid ( bool in_Value )
{
	GameState* l_pGameState = GetGameState ( m_pDisplay );
	l_pGameState->SetShowAIGrid ( in_Value );

}
void	CXSIGameInterfaceUI::EditFrictionMap()
{
	XSI::ClusterProperty frictionMap = GetFrictionMap();

	if ( !frictionMap.IsValid() )
	{
		//
		// add a new friction map using the new cluster builder object
		//

		m_bSuspendNotifications = true;
		XSI::PolygonMesh			l_XSIMesh = (XSI::PolygonMesh)m_x3dObject.GetActivePrimitive().GetGeometry();
		XSI::CClusterPropertyBuilder l_XSIClusterPropBuilder = l_XSIMesh.GetClusterPropertyBuilder();
		frictionMap = l_XSIClusterPropBuilder.AddWeightMap(XSI::CString(L"FrictionMap"), XSI::CString(L"FrictionMap"));
		m_bSuspendNotifications = false;
	}

}

XSI::ClusterProperty CXSIGameInterfaceUI::GetFrictionMap()
{
	m_bSuspendNotifications = true;
	XSI::ClusterProperty frictionMap;
	XSI::PolygonMesh			l_XSIMesh = (XSI::PolygonMesh)m_x3dObject.GetActivePrimitive().GetGeometry();
	XSI::CGeometryAccessor	l_XSIMeshAccessor;
	l_XSIMeshAccessor = l_XSIMesh.GetGeometryAccessor(XSI::siConstructionModeModeling,(XSI::siSubdivisionRuleType)0,0,0);

	XSI::CRefArray weightMaps = l_XSIMeshAccessor.GetWeightMaps();

	for (int w=0;w<weightMaps.GetCount();w++)
	{
		XSI::ClusterProperty prop = (XSI::ClusterProperty)weightMaps[w];

		if ( prop.GetName() == XSI::CString ( L"FrictionMap"))
		{
			frictionMap = prop;
			break;
		}

	}
	m_bSuspendNotifications = false;

	return frictionMap;
}

LRESULT CALLBACK	_std_view_proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	DEBUGENTRY ( "_std_view_proc");

	Display	* l_pDisplay = (Display*)GetWindowLong ( hDlg, GWL_USERDATA );

	switch (message)
	{
		

		case WM_INITDIALOG:
			{
			
				return TRUE;

			}
		
		
		case WM_SIZE:
		{
			if ( l_pDisplay )
			{
				RECT r;
				GetClientRect ( hDlg, &r );
				l_pDisplay->Resize (r.right, r.bottom);
			}
			break;
		}
		
		case WM_SHOWWINDOW:
			{
				//
				// Very important that we hide the window when we receive this message
				//
				ShowWindow ( hDlg, wParam );

				break;
			}
			break;

		case WM_CLOSE:

			EndDialog(hDlg, 0);
			break;
	}

    return DefWindowProc(hDlg, message, wParam, lParam);
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


void CALLBACK RenderGame(
HWND hwnd, 
UINT uMsg, 
UINT idEvent, 
DWORD dwTime )
{
	DEBUGENTRY ( "RenderGame");
	if ( !g_PSingletonGame->GetPause() )
	{
		g_PSingletonGame->m_bLevelUpdateDone = false;

		glMatrixMode ( GL_MODELVIEW );
		glLoadIdentity();
		g_PSingletonGame->Render();
	}
}



bool FindCustomPSet(XSI::X3DObject &node, const XSI::CString& name, XSI::CustomProperty &prop)
{
	DEBUGENTRY ( "FindCustomPSet");

	XSI::CRefArray properties = node.GetProperties();
	int j;

	if(properties.GetCount() > 0)
	{
		for(j = 0; j < properties.GetCount(); j++)
		{
			prop = properties[j];
			
			if(prop.GetName() == name)
				return true;
		}
	}

	return false;
}


LRESULT CALLBACK ControlPanelProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	DEBUGENTRY ( "ControlPanelProc");

	ControlPanelStruct *l_pWindows = (ControlPanelStruct*)GetWindowLong ( hDlg, GWL_USERDATA );

	switch (message)
	{
		case WM_INITDIALOG:
			{
				SendDlgItemMessage ( hDlg, IDC_AUTOUPDATE, BM_SETCHECK, BST_CHECKED, 0 );
				SendDlgItemMessage ( hDlg, IDC_CAMERATYPE, CB_ADDSTRING, 0, (LPARAM)"Smart" );
				SendDlgItemMessage ( hDlg, IDC_CAMERATYPE, CB_ADDSTRING, 0, (LPARAM)"Follow");
				SendDlgItemMessage ( hDlg, IDC_CAMERATYPE, CB_ADDSTRING, 0, (LPARAM)"Turntable Player" );
				SendDlgItemMessage ( hDlg, IDC_CAMERATYPE, CB_ADDSTRING, 0, (LPARAM)"Turntable Enemy" );
				SendDlgItemMessage ( hDlg, IDC_CAMERATYPE, CB_SETCURSEL, 0, 0 );
				
				if ( g_PSingletonGame )
				{
					SetDlgItemText ( hDlg, IDC_SKY1, g_PSingletonGame->GetCurrentLevel()->m_SkyTexture1 );
					SetDlgItemText ( hDlg, IDC_SKY2, g_PSingletonGame->GetCurrentLevel()->m_SkyTexture2 );
				}

				TC_ITEM	item;
				memset ( &item, 0, sizeof(TC_ITEM));
				item.mask = TCIF_TEXT ;
				item.pszText = "Level Edit";
				item.iImage = -1;

				int a = TabCtrl_InsertItem( GetDlgItem (hDlg, IDC_TABCONTROL),0,&item);

				item.pszText = "Actor Edit";
				a = TabCtrl_InsertItem( GetDlgItem ( hDlg, IDC_TABCONTROL),1,&item);

				return TRUE;
			}

		case WM_NOTIFY:
			{
				NMHDR FAR *tem=(NMHDR FAR *)lParam;

				if (tem->code== TCN_SELCHANGE)
				{
					int num=TabCtrl_GetCurSel(tem->hwndFrom);

					ShowWindow ( l_pWindows->m_hLevel, SW_HIDE );
					ShowWindow ( l_pWindows->m_hActor, SW_HIDE );

					switch ( num )
					{
					case 0: ShowWindow ( l_pWindows->m_hLevel, SW_SHOWNORMAL); break;
					case 1: ShowWindow ( l_pWindows->m_hActor, SW_SHOWNORMAL); break;
					}
				}
			}
			break;

		case WM_COMMAND:

			if ( g_PSingletonGame )
			{
				if (HIWORD(wParam) == CBN_SELCHANGE)
				{
					int sel = SendDlgItemMessage ( hDlg, IDC_CAMERATYPE, CB_GETCURSEL, 0, 0 );
					g_PSingletonGame->SetCameraType ( sel );

				}
				
				switch ( LOWORD(wParam) )
				{

				case IDC_FRICTIONMAP:
					{
						g_PSingletonGame->EditFrictionMap();
						break;
					}

				case IDC_SETMESH:
					{
						XSI::Application app;
						XSI::Selection sel = app.GetSelection();

						XSI::X3DObject x3d = sel.GetItem(0);

						if ( x3d.IsValid())
						{
							g_PSingletonGame->m_x3dObject = x3d;
							g_PSingletonGame->UpdateLevel(  g_PSingletonGame->m_x3dObject.GetActivePrimitive(), true );
						}
						break;
					}
				case IDC_RELOADENEMY:
					{
						g_PSingletonGame->ReloadEnemies();
						break;

					}
				case IDC_RELOADPLAYER:
					{
						g_PSingletonGame->ReloadPlayer();
						break;
					}


				case IDC_CREATENEW:
					{
						char filename[MAX_PATH];
						GiveMeAFile( hDlg,__gInstance, "XSI Game Level", "*.xgl", filename, 1);
						if ( strlen ( filename ) > 0 )
						{

							char fname[MAX_PATH];
							_splitpath ( filename, NULL, NULL, fname, NULL);
							
							sprintf ( fname, "%s.lvl", fname );

							FILE *t = fopen ( filename, "rb" );
							if ( t )
							{
								fclose(t);
								MessageBox ( hDlg, "There is already a level by that name, please choose another name", "ERROR", MB_OK );
								break;
							}

							FILE *f = fopen ( filename, "wt" );
							fprintf ( f, "level %s\n", fname);
							fclose ( f );

							g_PSingletonGame->AddLevel ( filename );
						}

						break;

					}

				case IDC_NEXTLEVEL:
					{
						g_PSingletonGame->NextLevel();
						
						if ( g_PSingletonGame )
						{
							CSIBCArray<CSIBCString> stringList;
							g_PSingletonGame->GetCurrentLevel()->GetAssets(stringList);
							SendDlgItemMessage ( hDlg, IDC_LIST1, LB_RESETCONTENT, 0, 0 );
							for (int s=0;s<stringList.GetUsed();s++)
							{
								SendDlgItemMessage(hDlg,IDC_LIST1,LB_ADDSTRING,0,(LPARAM)stringList[s].GetText());
							}
							SetDlgItemText ( hDlg, IDC_SKY1, g_PSingletonGame->GetCurrentLevel()->m_SkyTexture1 );
							SetDlgItemText ( hDlg, IDC_SKY2, g_PSingletonGame->GetCurrentLevel()->m_SkyTexture2 );
							char distance[MAX_PATH];
							sprintf (distance, "%f", g_PSingletonGame->GetCurrentLevel()->m_fFogDistance );
							SetDlgItemText ( hDlg, IDC_DISTANCE, distance );
							
						}
						
						
						return TRUE;
					}
				case IDC_REFRESH:
					{
						if ( g_PSingletonGame )
						{
							CSIBCArray<CSIBCString> stringList;
							g_PSingletonGame->GetCurrentLevel()->GetAssets(stringList);
							SendDlgItemMessage ( hDlg, IDC_LIST1, LB_RESETCONTENT, 0, 0 );
							for (int s=0;s<stringList.GetUsed();s++)
							{
								SendDlgItemMessage(hDlg,IDC_LIST1,LB_ADDSTRING,0,(LPARAM)stringList[s].GetText());
							}
						}
						break;
					}
				case IDC_FORCEUPDATE:
					{
						bool l_bAutoUpdate = g_PSingletonGame->GetAutoUpdate ();

						g_PSingletonGame->SetAutoUpdate ( true );
						g_PSingletonGame->UpdateLights ();
						g_PSingletonGame->UpdateLevel ( g_PSingletonGame->GetX3D().GetActivePrimitive(), true );

						g_PSingletonGame->SetAutoUpdate ( l_bAutoUpdate );

						break;


					}
				case IDC_FOGCOLOR:
					{
						float r,g,b;

						GiveMeAColor ( hDlg,__gInstance, &r, &g, &b );
						g_PSingletonGame->GetCurrentLevel ()->m_fFogColor[0] = r;
						g_PSingletonGame->GetCurrentLevel ()->m_fFogColor[1] = g;
						g_PSingletonGame->GetCurrentLevel ()->m_fFogColor[2] = b;
						g_PSingletonGame->GetCurrentLevel()->CreateSky ();
						g_PSingletonGame->SaveLevelDef();
						break;

					}

				case IDC_BROWSE1:
					{
						char filename[MAX_PATH];
						GiveMeAFile( hDlg,__gInstance, "Textures", "*.bmp", filename, 0);
						if ( strlen ( filename ) > 0 )
						{
							char fname[MAX_PATH];
							char extension[MAX_PATH];
							_splitpath ( filename, NULL, NULL, fname, extension );
							sprintf ( fname, "%s%s", fname, extension);
							strcpy ( g_PSingletonGame->GetCurrentLevel ()->m_SkyTexture1, fname );
							SetDlgItemText ( hDlg, IDC_SKY1, g_PSingletonGame->GetCurrentLevel()->m_SkyTexture1 );
							g_PSingletonGame->GetCurrentLevel()->CreateSky ();
							g_PSingletonGame->SaveLevelDef();
						}

						break;
					}
				case IDC_BROWSE2:
					{
						char filename[MAX_PATH];
						GiveMeAFile( hDlg,__gInstance, "Textures", "*.bmp", filename, 0);
						if ( strlen ( filename ) > 0 )
						{
							char fname[MAX_PATH];
							char extension[MAX_PATH];
							_splitpath ( filename, NULL, NULL, fname, extension );
							sprintf ( fname, "%s%s", fname, extension);
							strcpy ( g_PSingletonGame->GetCurrentLevel ()->m_SkyTexture2, fname );
							SetDlgItemText ( hDlg, IDC_SKY2, g_PSingletonGame->GetCurrentLevel()->m_SkyTexture2 );
							g_PSingletonGame->GetCurrentLevel()->CreateSky ();
							g_PSingletonGame->SaveLevelDef();
							
						}

						break;
					}

				case IDC_ADDASSET:
					{
						char filename[MAX_PATH];
						GiveMeAFile( hDlg,__gInstance, "dotXSI Files", "*.xsi", filename, 0);
						if ( strlen ( filename ) > 0 )
						{
							char fname[MAX_PATH];
							_splitpath ( filename, NULL, NULL, fname, NULL );
							sprintf ( fname, "%s.xsi", fname );

							g_PSingletonGame->AddAsset ( fname );
						}

						break;
					}

				case IDC_EDITASSET:
					{
						int Selection;
						char select[MAX_PATH];
						Selection = SendDlgItemMessage(hDlg, IDC_LIST1,LB_GETCURSEL,0,0);
						
						if (Selection != LB_ERR)
						{
							SendDlgItemMessage(hDlg, IDC_LIST1,LB_GETTEXT,Selection,(LPARAM)select);
							g_PSingletonGame->EditAsset ( select );
						}

						break;
					}
				case IDC_UPDATE:
					{
						int Selection;
						char select[MAX_PATH];
						Selection = SendDlgItemMessage(hDlg, IDC_LIST1,LB_GETCURSEL,0,0);
						
						if (Selection != LB_ERR)
						{
							SendDlgItemMessage(hDlg, IDC_LIST1,LB_GETTEXT,Selection,(LPARAM)select);
							g_PSingletonGame->UpdateAsset ( select );
						}
						
						
						

						break;
					}
				case IDC_REMOVEASSET:
					{
						int Selection;
						char select[MAX_PATH];
						Selection = SendDlgItemMessage(hDlg, IDC_LIST1,LB_GETCURSEL,0,0);

						if (Selection != LB_ERR)
						{
							SendDlgItemMessage(hDlg, IDC_LIST1,LB_GETTEXT,Selection,(LPARAM)select);
						}

						g_PSingletonGame->RemoveAsset ( select );


						break;
					}
				case IDC_EDITPLAYER:
					{
						g_PSingletonGame->EditPlayer();
						break;
					}
				case IDC_EDITENEMY:
					{
						g_PSingletonGame->EditEnnemy();
						break;
					}




				case IDC_SHOWSECTORS:
				case IDC_SHOWAIGRID:
				case IDC_AUTOUPDATE:
				case IDC_PAUSEGAME:
					g_PSingletonGame->SetShowSectors ( SendDlgItemMessage(hDlg,IDC_SHOWSECTORS, BM_GETCHECK ,0 ,0) == BST_CHECKED ? true : false );
					g_PSingletonGame->SetShowAIGrid ( SendDlgItemMessage(hDlg,IDC_SHOWAIGRID, BM_GETCHECK ,0 ,0) == BST_CHECKED ? true : false );
					g_PSingletonGame->SetAutoUpdate ( SendDlgItemMessage(hDlg,IDC_AUTOUPDATE, BM_GETCHECK ,0 ,0) == BST_CHECKED ? true : false );
					g_PSingletonGame->SetPause ( SendDlgItemMessage(hDlg,IDC_PAUSEGAME, BM_GETCHECK ,0 ,0) == BST_CHECKED ? true : false );
					break;
				}

				}
			break;
	}
    return FALSE;
}

void SetXSIValue ( XSI::CString in_szString , LONG in_lValue )
{
	XSI::CValueArray	args(2);
	XSI::CValue			outArg;
	args[0] = XSI::CValue( in_szString );
	args[1] = XSI::CValue(in_lValue);
		
	XSI::Application	app;
	app.ExecuteCommand( L"SetValue", args, outArg );
}

void SetXSIValue ( XSI::CString in_szString , float in_fValue )
{
	XSI::CValue			outArg;
	XSI::CValueArray	args(2);

	args[0] = XSI::CValue( in_szString );
	args[1] = XSI::CValue(in_fValue);
		
	XSI::Application	app;
	app.ExecuteCommand( L"SetValue", args, outArg );
}
static COLORREF	customColors[16];
void GiveMeAColor(HWND hdlg, HINSTANCE hInst, float *r, float *g, float *b)
{

	CHOOSECOLOR choosencolor;
	COLORREF	init_value;

	init_value = RGB((int)(*r * 255.0), (int)(*g * 255.0), (int)(*b * 255.0));

	memset(&choosencolor, 0, sizeof(choosencolor));

	choosencolor.lStructSize       = sizeof(choosencolor);
    choosencolor.hwndOwner         = hdlg;
    choosencolor.hInstance         = (HWND)hInst;
    choosencolor.lpfnHook 		   = NULL;
	choosencolor.lpTemplateName    = NULL;
    choosencolor.Flags             = CC_ANYCOLOR | CC_FULLOPEN | CC_RGBINIT;
	choosencolor.lpCustColors		= customColors;
	choosencolor.rgbResult			= init_value;

	ChooseColor(&choosencolor);

	*r = (float)GetRValue(choosencolor.rgbResult) / 256.0f;
	*g = (float)GetGValue(choosencolor.rgbResult) / 256.0f;
	*b = (float)GetBValue(choosencolor.rgbResult) / 256.0f;
}

void GiveMeAFile( HWND hWnd,HINSTANCE hInst, char* specname, char *extensions, char *filename, int save)
{
	OPENFILENAME OpenFileName;
	char exten[MAX_PATH];
	char initdir[MAX_PATH];

	int len;
	char *ptr;

	if (filename==NULL) return;
	
	SetCurrentDirectory(__gGameDataRootPath);
	strcpy(initdir,__gGameDataRootPath);
	
	//filename
	filename[0] = 0;

	sprintf(exten,"%s",specname);

	len = strlen(exten);

	exten[len] = 0;

	ptr = &exten[len+1];

	strcpy(ptr,extensions);

	len = strlen(ptr);
	ptr[len] = 0;
	ptr[len+1] = 0;


	// Fill in the OPENFILENAME structure to support a template and hook.
	memset(&OpenFileName, 0, sizeof(OPENFILENAME));

	OpenFileName.lStructSize       = sizeof(OPENFILENAME);
    OpenFileName.hwndOwner         = hWnd;
    OpenFileName.hInstance         = hInst;
    OpenFileName.lpstrFilter       = exten;
    OpenFileName.lpstrCustomFilter = NULL;
    OpenFileName.nMaxCustFilter    = 0;
    OpenFileName.nFilterIndex      = 0;
    OpenFileName.lpstrFile         = filename;
    OpenFileName.nMaxFile          = MAX_PATH;
    OpenFileName.lpstrFileTitle    = NULL;
    OpenFileName.nMaxFileTitle     = 0;
    OpenFileName.lpstrInitialDir   = initdir;
    OpenFileName.lpstrTitle        = "Select a file";
    OpenFileName.nFileOffset       = 0;
    OpenFileName.nFileExtension    = 0;
    OpenFileName.lpstrDefExt       = NULL;
    OpenFileName.lCustData         = NULL;
	OpenFileName.lpfnHook 		   = NULL;

	// Call the common dialog function.
	int retval;

	if (save)
	{

		retval = GetSaveFileName(&OpenFileName);
	} else {
		OpenFileName.Flags = OFN_FILEMUSTEXIST;
		retval = GetOpenFileName(&OpenFileName);
	}


	if (retval)
	{

		char ext[256];
		ext[0] = 0;

		_splitpath( filename, NULL,NULL, NULL, ext);

		if (strlen(ext)==0)
		{
			char *extension = strchr( extensions, '.');
			strcat( filename, extension );
		}


		
	} 
}