// Level.cpp: implementation of the Level class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Level.h"
#include "GameState.h"
#include <stdlib.h>
#include <time.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

static float		_cubePositions[] =
{
		-1.0f,	-1.0f,	-1.0f	,
		-1.0f,	 1.0f,	-1.0f	,
		 1.0f,	-1.0f,	-1.0f	,
		 1.0f,	 1.0f,	-1.0f	,

		-1.0f,	-1.0f,	 1.0f	,
		 1.0f,	-1.0f,	 1.0f	,
		-1.0f,	 1.0f,	 1.0f	,
		 1.0f,	 1.0f,	 1.0f	,

		-1.0f,	-1.0f,	-1.0f	,
		 1.0f,	-1.0f,	-1.0f	,
		-1.0f,	-1.0f,	 1.0f	,
		 1.0f,	-1.0f,	 1.0f	,

		-1.0f,	 1.0f,	-1.0f	,
		-1.0f,	 1.0f,	 1.0f	,
		 1.0f,	 1.0f,	-1.0f	,
		 1.0f,	 1.0f,	 1.0f	,

		-1.0f,	-1.0f,	-1.0f	,
		-1.0f,	-1.0f,	 1.0f	,
		-1.0f,	 1.0f,	-1.0f	,
		-1.0f,	 1.0f,	 1.0f	,

		 1.0f,	-1.0f,	-1.0f	,
		 1.0f,	 1.0f,	-1.0f	,
		 1.0f,	-1.0f,	 1.0f	,
		 1.0f,	 1.0f,	 1.0f	,
};

static float		_cubeNorms[] =
{
		  0.0f,	 0.0f,	-1.0f	,
		  0.0f,	 0.0f,	-1.0f	,
		  0.0f,	 0.0f,	-1.0f	,
		  0.0f,	 0.0f,	-1.0f	,

		  0.0f,	 0.0f,	 1.0f	,
		  0.0f,	 0.0f,	 1.0f	,
		  0.0f,	 0.0f,	 1.0f	,
		  0.0f,	 0.0f,	 1.0f	,

		  0.0f,	-1.0f,	 0.0f	,
		  0.0f,	-1.0f,	 0.0f	,
		  0.0f,	-1.0f,	 0.0f	,
		  0.0f,	-1.0f,	 0.0f	,

		  0.0f,	 1.0f,	 0.0f	,
		  0.0f,	 1.0f,	 0.0f	,
		  0.0f,	 1.0f,	 0.0f	,
		  0.0f,	 1.0f,	 0.0f	,

		 -1.0f,	 0.0f,	 0.0f	,
		 -1.0f,	 0.0f,	 0.0f	,
		 -1.0f,	 0.0f,	 0.0f	,
		 -1.0f,	 0.0f,	 0.0f	,

		  1.0f,	 0.0f,	 0.0f	,
		  1.0f,	 0.0f,	 0.0f	,
		  1.0f,	 0.0f,	 0.0f	,
		  1.0f,	 0.0f,	 0.0f	,
};

static float	_cubeTexCoords[] =
{
		  0.0f,	 0.0f	,
		  0.0f,	 1.0f	,
		  1.0f,	 0.0f	,
		  1.0f,	 1.0f	,

		  0.0f,	 0.0f	,
		  0.0f,	 1.0f	,
		  1.0f,	 0.0f	,
		  1.0f,	 1.0f	,

		  0.0f,	 0.0f	,
		  0.0f,	 1.0f	,
		  1.0f,	 0.0f	,
		  1.0f,	 1.0f	,

		  0.0f,	 0.0f	,
		  0.0f,	 1.0f	,
		  1.0f,	 0.0f	,
		  1.0f,	 1.0f	,

		  0.0f,	 0.0f	,
		  0.0f,	 1.0f	,
		  1.0f,	 0.0f	,
		  1.0f,	 1.0f	,

		  0.0f,	 0.0f	,
		  0.0f,	 1.0f	,
		  1.0f,	 0.0f	,
		  1.0f,	 1.0f	,
};

typedef int Tri[3];

static Tri		_cubeFaces[] =
{
	{	0,	1,	2	},
	{	3,	2,	1	},

	{	4,	5,	6	},
	{	7,	6,	5	},

	{	8,	9,	10	},
	{	11,	10,	9	},

	{	12,	13,	14	},
	{	15,	14,	13	},

	{	16,	17,	18	},
	{	19,	18,	17	},

	{	20,	21,	22	},
	{	23,	22,	21	},
};

static const int	_numCubeVerts = sizeof(_cubePositions) / sizeof(*_cubePositions);
static const int	_numCubeFaces = sizeof(_cubeFaces) / sizeof(*_cubeFaces);


int			Level::m_iXSITexture;
int			Level::m_iBlurTexture;

Level::Level( Display* in_pDisplay )
{
	m_pDisplay = in_pDisplay;
	m_bInitialized = false;
	m_fWhiteInTime = 5.0f;
	srand(time(NULL));
	m_iNumEnemies = 1;
	memset ( m_SkyTexture1, 0, MAX_PATH);
	memset ( m_SkyTexture2, 0, MAX_PATH);
}

Level::~Level()
{

}

void Level::Initialize ()
{
	m_fPositionX = 0.0f;
	m_fPositionY = -2.5f;
	m_fPositionZ = -20.0f;
	m_fRotation = 180.0f;

	//
	// Set the GameState for this level
	//

	GameState*	l_pGameState = GetGameState( m_pDisplay );

	l_pGameState->SetCameraPosition ( CSIBCVector3D(0.0f, 10.0, -120.0f),
										CSIBCVector3D( m_fPositionX, m_fPositionY, m_fPositionZ ) );

	l_pGameState->SetPlayerPosition ( CSIBCVector3D(m_fPositionX, m_fPositionY, m_fPositionZ) );
	l_pGameState->SetEnemyPosition ( CSIBCVector3D(0.0f, 11.97f, 13.23f) );
	l_pGameState->LoadLevel ( this, m_szLevelFilename );
	l_pGameState->SetLevelTime ( 1000 * 60 );	// 1 minute;

	for (int a=0;a<m_Assets.GetUsed();a++)
	{
		m_AssetGeometry.Extend(1);
		m_AssetGeometry[m_AssetGeometry.GetUsed()-1] = new dotXSI();
		m_AssetGeometry[m_AssetGeometry.GetUsed()-1]->Load ( m_Assets[a]->GetText(), m_pDisplay);
	}
	
	CreateSky ();

	m_bInitialized = true;

}

void Level::CreateSky ()
{
	GameState*	l_pGameState = GetGameState( m_pDisplay );
	if ( l_pGameState->GetGeometry () == NULL )
		return;
	for (int c=0;c<4;c++) l_pGameState->GetGeometry()->m_vFogColor[c] = m_fFogColor[c];
	strcpy ( l_pGameState->GetGeometry()->m_szSkyTexture1, m_SkyTexture1 );
	strcpy ( l_pGameState->GetGeometry()->m_szSkyTexture2, m_SkyTexture2 );
	l_pGameState->GetGeometry()->m_vFogDistance = m_fFogDistance;
	l_pGameState->GetGeometry()->CreateSky();
}

void Level::SetLevelFilename ( char* in_szString )
{
	memset ( m_szLevelFilename,0,MAX_PATH );
	strcpy ( m_szLevelFilename, in_szString );
}


void Level::Unload()
{

	for (int a=0;a<m_AssetGeometry.GetUsed();a++)
	{
		delete m_AssetGeometry[a];
	}

	m_AssetGeometry.DisposeData();

	m_bInitialized = false;
}


void Level::GetAssets ( CSIBCArray<CSIBCString>& out_assets )
{
	
	for (int a=0;a<m_Assets.GetUsed();a++)
	{
		out_assets.Extend(1);
		out_assets[out_assets.GetUsed()-1] = m_Assets[a]->GetText();
	}

}

void Level::SetAssets ( CSIBCArray<CSIBCString*> * in_assets )
{

	m_Assets.DisposeData();

	for (int a=0;a<in_assets->GetUsed();a++)
	{
		m_Assets.Extend(1);
		m_Assets[m_Assets.GetUsed()-1] = new CSIBCString ( (*in_assets)[a]->GetText() );
	}

}


void Level::DrawCube()
{
	glPushAttrib( GL_ALL_ATTRIB_BITS );


	glEnable ( GL_TEXTURE_2D );
	glEnable ( GL_LIGHTING );
	
	glDisable ( GL_BLEND );
	glEnable ( GL_CULL_FACE );
	glCullFace ( GL_BACK );



	glColor3f ( 1.0f, 1.0f, 1.0f);
	glEnable ( GL_COLOR_MATERIAL );

	glBegin ( GL_TRIANGLES );
	
	int t;
	for (t=0;t<_numCubeFaces;t++)
	{
		int* indices = _cubeFaces[t];
		glNormal3f ( _cubeNorms[indices[0] * 3], _cubeNorms[(indices[0]*3)+1] , _cubeNorms[(indices[0]*3)+2] );
		glTexCoord2f ( _cubeTexCoords[indices[0]*2 ], _cubeTexCoords[(indices[0]*2  )+1] );
		glVertex3f ( _cubePositions[indices[0]*3 ], _cubePositions[(indices[0]*3 )+1] , _cubePositions[(indices[0]*3  )+2] );

		glNormal3f ( _cubeNorms[indices[1]*3], _cubeNorms[(indices[1]*3)+1] , _cubeNorms[(indices[1]*3)+2] );
		glTexCoord2f ( _cubeTexCoords[indices[1]*2 ], _cubeTexCoords[(indices[1]*2  )+1] );
		glVertex3f ( _cubePositions[indices[1]*3], _cubePositions[(indices[1] *3 )+1] , _cubePositions[(indices[1]*3  )+2] );
		
		glNormal3f ( _cubeNorms[indices[2]*3], _cubeNorms[(indices[2]*3)+1] , _cubeNorms[(indices[2]*3)+2] );
		glTexCoord2f ( _cubeTexCoords[indices[2]*2 ], _cubeTexCoords[(indices[2]*2  )+1] );
		glVertex3f ( _cubePositions[indices[2]*3], _cubePositions[(indices[2]*3  )+1] , _cubePositions[(indices[2] *3)+2] );
	}

	glEnd();


	glPopAttrib();
}

void	Level::RenderToTexture()
{
		float viewport[4];
		glGetFloatv ( GL_VIEWPORT, viewport );
		
		glViewport(0,0,128,128);									
		
		DrawCube();

		//DrawLogo();
		
		glBindTexture(GL_TEXTURE_2D,m_iBlurTexture);					
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 0, 0, 128, 128, 0);
		
		glClearColor(0.0f, 0.0f, 0.0f, 0.5);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0 , 0,viewport[2] ,viewport[3]);

}

int	Level::Render ( DWORD milliseconds )
{
	DEBUGENTRY ( "Level::Render" );

	if ( DrawIntroScreen ( milliseconds ) )
		return 1;

	static float tra = 0.0f;

	//
	// set some global gl states
	//

	glDisable ( GL_BLEND );
	glEnable ( GL_LIGHTING );
	glEnable ( GL_CULL_FACE );
	glCullFace ( GL_BACK );
	glEnable ( GL_DEPTH_TEST );
	glDisable ( GL_TEXTURE_2D );
	glDisable( GL_COLOR_MATERIAL );
	
	//
	// run the game logic
	//

	int ContinueLevel = GetGameState ( NULL )->Tick ( milliseconds );


	//
	// render the level
	//

	glPushAttrib( GL_ALL_ATTRIB_BITS );

	glDisable ( GL_COLOR_MATERIAL );
	glDisable ( GL_TEXTURE_2D);

	glEnable ( GL_FOG );
	glFogi (GL_FOG_MODE, GL_LINEAR); 
    glHint (GL_FOG_HINT, GL_FASTEST);  
    glFogf (GL_FOG_START,0.0f);     
	glFogf (GL_FOG_END, m_fFogDistance); 
	glFogfv (GL_FOG_COLOR, m_fFogColor);

	for (int a=0;a<m_Assets.GetUsed();a++)
	{
		m_AssetGeometry[a]->Tick ( milliseconds );
		m_AssetGeometry[a]->Render();
		// m_AssetGeometry[a]->RenderBoundingBoxList();
	}

	glPopAttrib();

	
	// now render the game's geometry (player, enemy, electric fields, etc.)
	GetGameState ( NULL )->Render( milliseconds );

	return ContinueLevel;
}



void Level::DrawBlur(int times, float inc, float transy)
{
	float spost = 0.0f;											
	float alphainc = 0.9f / times;								
	float alpha = 0.2f;

	glPushAttrib( GL_ALL_ATTRIB_BITS );

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	glEnable(GL_TEXTURE_2D);									
	glDisable(GL_DEPTH_TEST);									
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);							
	glEnable(GL_BLEND);											
	glBindTexture(GL_TEXTURE_2D,m_iBlurTexture);					

	alphainc = alpha / times;	
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	
	glOrtho( 0, 640 , 480 , 0, -1, 1 );
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glTranslatef ( 0.0f, transy, 0.0f );
	glBegin(GL_QUADS);											
	for (int num = 0;num < times;num++)						
	{
		glColor4f(1.0f, 1.0f, 1.0f, alpha);					
		glTexCoord2f(0+spost,1-spost);						
		glVertex2f(0,0);									
		
		glTexCoord2f(0+spost,0+spost);						
		glVertex2f(0,480);									
		
		glTexCoord2f(1-spost,0+spost);						
		glVertex2f(640,480);								
		
		glTexCoord2f(1-spost,1-spost);						
		glVertex2f(640,0);									
		
		spost += inc;										
		alpha = alpha - alphainc;							
	}
	glEnd();														

	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	glMatrixMode(GL_MODELVIEW);
	

	glEnable(GL_DEPTH_TEST);									
	glDisable(GL_TEXTURE_2D);									
	glDisable(GL_BLEND);										
	glBindTexture(GL_TEXTURE_2D,0);
	
	glPopAttrib();
}

void Level::AddAsset ( char *in_szString )
{
	m_Assets.Extend(1);
	m_Assets[m_Assets.GetUsed()-1] = new CSIBCString ( in_szString );
	ReloadAsset ( in_szString );
}

void Level::RemoveAsset ( char *in_szString )
{
	for (int v=0;v<m_Assets.GetUsed();v++)
	{
		if ( m_Assets[v]->Compare ( in_szString ) )
		{
			delete m_Assets[v];

			m_Assets.DeleteAt ( v , 1 );
			m_Assets.Pack ();

		}
	}
	ReloadAsset ( NULL );
}


void Level::ReloadAsset ( char *in_szString )
{
	int a;
	for (a=0;a<m_AssetGeometry.GetUsed();a++)
	{
		delete m_AssetGeometry[a];
	}

	m_AssetGeometry.DisposeData();

	for (a=0;a<m_Assets.GetUsed();a++)
	{
		m_AssetGeometry.Extend(1);
		m_AssetGeometry[m_AssetGeometry.GetUsed()-1] = new dotXSI();
		m_AssetGeometry[m_AssetGeometry.GetUsed()-1]->Load ( m_Assets[a]->GetText(), m_pDisplay);
	}
	
}

int Level::DrawIntroScreen( DWORD milliseconds )
{
	if ( m_fWhiteInTime <= -1.0f )
		return 0;

	glPushAttrib( GL_ALL_ATTRIB_BITS );
	
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	
	glDisable(GL_TEXTURE_2D);									
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);							
	glEnable(GL_BLEND);											
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	
	glOrtho( 0, 640 , 480 , 0, -1, 1 );
	
	m_fWhiteInTime -= ( milliseconds / 1000.0f);
	glColor4f (1.0f, 1.0f, 1.0f, m_fWhiteInTime );
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glBegin(GL_QUADS);											
	
	
	glVertex2f(0,0);									
	
	glVertex2f(0,480);									
	
	glVertex2f(640,480);								
	
	glVertex2f(640,0);									
	
	glEnd();														
	
	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	glMatrixMode(GL_MODELVIEW);
	
	
	glEnable(GL_DEPTH_TEST);									
	glDisable(GL_TEXTURE_2D);									
	glDisable(GL_BLEND);										
	glBindTexture(GL_TEXTURE_2D,0);
	
	glColor4f ( 0.2f,
				0.2f,
				0.2f,
				m_fWhiteInTime);

	float viewport[4];
	glGetFloatv(GL_VIEWPORT,viewport);
	
	float midy = viewport[3] / 2.0f;
	
	m_pDisplay->Print ( 0,midy,FONT_CENTERED,"Level %s", m_szLevelFilename );

	glPopAttrib();

	return 1;
}
