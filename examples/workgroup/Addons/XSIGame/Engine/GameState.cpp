// GameState.cpp: implementation of the GameState class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GameState.h"
#include "MaterialSystem.h"

#include "Shield.h"
#include "SpeedUp.h"
#include "Level.h"

#define DEG2RAD			0.01745329251994329547f
//#define NOPLAYER

GameState*	g_pZeGameState = NULL;
CSIBCArray<SinglePolygon*>	l_intersectionlist;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GameState::GameState( Display* in_pDisplay ) : 
  m_pPlayer ( NULL )
, m_pLevel  ( NULL )
, m_pCurrentPowerUp ( NULL )
, m_pLevelDef ( NULL )
{

	m_pDisplay = in_pDisplay;

	GetMaterialSystem()->SetDisplay( in_pDisplay );

	m_pCamera = new Camera ( in_pDisplay );
	m_pBBManager = new BillboardManager ( in_pDisplay );

	//m_pEnemy = new Enemy ( in_pDisplay );

#ifndef NOPLAYER
	LoadPlayer();
#endif

	m_SkyBox = new SkyBox ( in_pDisplay );
	m_SkyBox->load ( "tropical");

	m_fRotation = 180.0f;

	m_lScore = 0;
	m_fFallingTime = 0.0f;
	m_fJumpTime = 0.0f;

	m_fNewCamTime = 0;
	m_fEndOfLevelTime = 8000;
	m_fTimeToNextPowerUp = 1000.0f;
	m_fWhiteOutAlpha = 0.0f;
	m_bLevelDone = false;
	m_bExternalCameraControl = false;

	m_fPlayerSpeed = 0.008f;
	m_fFPS = 0.0f;

	m_iCameraType = CAMERA_TYPE_FOLLOW;

	m_bShowSectors = false;
	m_bShowAIGrid = false;

	m_pPowerUpMesh = new dotXSI ();
	m_pPowerUpMesh->Load ( "powerup.xsi", in_pDisplay );

}

GameState::~GameState()
{
	delete m_pCamera;
	m_pCamera = NULL;

	delete m_pBBManager;
	m_pBBManager = NULL;

	if ( m_pLevel )
	{
		delete m_pLevel;
		m_pLevel = NULL;
	}
#ifndef NOPLAYER
	if ( m_pPlayer )
	{
		delete m_pPlayer;
		m_pPlayer = NULL;
	}
#endif

}

void	GameState::SetEnemyPosition ( CSIBCVector3D in_vPosition )
{
	m_vEnemyPosition = in_vPosition;
}

void	GameState::SetPlayerPosition ( CSIBCVector3D in_vPosition )
{
	m_pPlayer->SetPosition ( in_vPosition );
	m_fLastLookAt = in_vPosition.m_fY;

}

void	GameState::SetCameraPosition ( CSIBCVector3D in_vPosition, CSIBCVector3D in_vInterest, bool Smooth )
{
	m_vCameraPosition = in_vPosition;
	m_vCameraInterest = in_vInterest;

	vector3	l_pos;
	vector3	l_int;

	l_pos.x = m_vCameraPosition.m_fX;
	l_pos.y = m_vCameraPosition.m_fY;
	l_pos.z = m_vCameraPosition.m_fZ;

	l_int.x = m_vCameraInterest.m_fX;
	l_int.y = m_vCameraInterest.m_fY;
	l_int.z = m_vCameraInterest.m_fZ;

	if ( Smooth )
	{
		m_pCamera->SmoothLookAt ( l_pos, l_int );
	} else {
		m_pCamera->LookAt ( l_pos, l_int );
	}

}

int	GameState::Tick ( float milliseconds )
{
	if ( m_bLevelDone )
	{
		return DoEndOfLevel( milliseconds );
	}

	m_iTime-=milliseconds;

	m_pPlayer->Tick ( milliseconds );
	m_pDisplay->Tick ( milliseconds );
		
	for (int e=0;e<m_lEnemyList.GetUsed();e++)
	{
		m_lEnemyList[e]->m_pLevel = m_pLevel;
		m_lEnemyList[e]->LearnAboutPlayerPosition ( m_pPlayer->GetPosition() );
		m_lEnemyList[e]->Tick ( milliseconds );
	}

	

	//
	// check for collisions
	//
	
	CSIBCVector3D collisionvector;

	for (int g=0;g<m_pLevelDef->m_AssetGeometry.GetUsed();g++)
	{
		if ( m_pLevelDef->m_AssetGeometry[g]->TestCollision ( m_pPlayer->GetGeometry(), collisionvector) )
		{
			//m_vPlayerPosition.Add( collisionvector );
		}
	}


	if ( !m_bExternalCameraControl )
	{
		if ( m_iCameraType == CAMERA_TYPE_SMART )
		{
			CSIBCArray<vector3*> vectorlist;
			
			vector3 enemypos = vector3 ( m_vEnemyPosition.m_fX, m_vEnemyPosition.m_fY, m_vEnemyPosition.m_fZ);
			vector3 playerpos = vector3 ( m_pPlayer->GetPosition ().m_fX, m_pPlayer->GetPosition ().m_fY - 3.0f, m_pPlayer->GetPosition ().m_fZ );
			
			//vectorlist.Extend(1);
			//vectorlist[vectorlist.GetUsed()-1] = &enemypos;
			
			vectorlist.Extend(1);
			vectorlist[vectorlist.GetUsed()-1] = &playerpos;
			
			bool nonVisitedExist = false;

			int v;

			for (v=0;v<m_pLevel->m_Polygons.GetUsed();v++)
			{
				
				if ( m_pLevel->m_Polygons[v].m_bWalkable && (!m_pLevel->m_Polygons[v].m_bVisited))
				{
					nonVisitedExist = true;
					if ( m_pLevel->m_Polygons[v].v1->position.DistanceSquared ( playerpos ) < 100 )
					{
						vectorlist.Extend(1);
						vectorlist[vectorlist.GetUsed()-1] = &m_pLevel->m_Polygons[v].v1->position;
						vectorlist.Extend(1);
						vectorlist[vectorlist.GetUsed()-1] = &m_pLevel->m_Polygons[v].v2->position;
						vectorlist.Extend(1);
						vectorlist[vectorlist.GetUsed()-1] = &m_pLevel->m_Polygons[v].v3->position;
					}
				}
			}

			//
			// if there remains non-visited polygons but they are far from the
			// current player's position, then add them all to the camera
			// frustum code.
			//

			if ( vectorlist.GetUsed()==1 &&  nonVisitedExist)
			{
				for (v=0;v<m_pLevel->m_Polygons.GetUsed();v++)
				{
					
					if ( m_pLevel->m_Polygons[v].m_bWalkable && (!m_pLevel->m_Polygons[v].m_bVisited))
					{
							vectorlist.Extend(1);
							vectorlist[vectorlist.GetUsed()-1] = &m_pLevel->m_Polygons[v].v1->position;
							vectorlist.Extend(1);
							vectorlist[vectorlist.GetUsed()-1] = &m_pLevel->m_Polygons[v].v2->position;
							vectorlist.Extend(1);
							vectorlist[vectorlist.GetUsed()-1] = &m_pLevel->m_Polygons[v].v3->position;

					}
				}
			
			}


		
			vector3 from, at;
			m_pCamera->GetLookAt ( from, at );
			from.y = 0.0f;

			float Distance2D = from.Distance ( vector3 ( m_pPlayer->GetPosition().m_fX, 0.0f, m_pPlayer->GetPosition().m_fZ ) );

			float gotoHeight = 0.0f;
			if ( Distance2D >= 20.0f )
			{
				gotoHeight = 10.0f;
			} 

			if ( Distance2D <= 14.0f )
			{
				gotoHeight = 2.5f;
			}

			m_pCamera->EnsureAllVectorsVisible (  vectorlist, gotoHeight );	// mimimum height
		}

		if ( m_iCameraType == CAMERA_TYPE_FOLLOW )
		{
			CSIBCVector3D l_vLookAt = GetPlayerPosition();
			if ( ( m_fJumpTime > 0.0f ) || ( m_fFallingTime > 0.0f))
			{
				l_vLookAt.m_fY = m_fLastLookAt;
			} else {
				m_fLastLookAt = l_vLookAt.m_fY;
			}
			m_pCamera->Follow ( m_pLevel, l_vLookAt, m_pPlayer->GetDirection () );
			//m_pCamera->Follow ( m_pLevel, m_lEnemyList[0]->m_vPosition, m_vDirection );
			
		}

		if ( m_iCameraType == CAMERA_TYPE_TURNTABLE )
		{
			m_pCamera->TurnTable ( GetPlayerPosition() );
		}

		if ( m_iCameraType == CAMERA_TYPE_TURNTABLE_ENEMY )
		{
			m_pCamera->TurnTable ( m_lEnemyList[0]->m_vPosition );
		}

		if ( m_iCameraType == CAMERA_TYPE_TURNTABLE )
		{
			m_pCamera->TurnTable ( GetPlayerPosition() );
		}
	}

	m_pCamera->Tick ( m_pLevel,  milliseconds );
	
	vector3	l_vFrom;
	vector3	l_vTo;
	
	m_pCamera->GetLookAt ( l_vFrom, l_vTo );

	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
	
	gluLookAt ( l_vFrom.x, l_vFrom.y, l_vFrom.z,
		l_vTo.x, l_vTo.y, l_vTo.z,
		0.0f,1.0f,0.0f );

	float model[16];
	float proj[16];

	glGetFloatv(GL_MODELVIEW_MATRIX, model);
	glGetFloatv(GL_PROJECTION_MATRIX, proj);


	m_pCamera->m_mCurrentViewMatrix.Set ( model ); 
	m_pCamera->m_mCurrentProjectionMatrix.Set ( proj );
	m_pCamera->UpdateFrustrumPlanes ();

	//
	// handle player movement
	//

	CSIBCVector3D lastPlayerPosition = m_pPlayer->GetPosition ();

	if ( m_pDisplay->Up )
	{
		m_pPlayer->Move (-1.0f);

		/*
		CSIBCMatrix4x4	rotMat;
		rotMat.SetToRotation ( CSIBCVector3D ( 0.0f, m_fRotation*DEG2RAD, 0.0f ));
		rotMat.Multiply ( m_vDirection, CSIBCVector3D(0.0f, 0.0f, 1.0f));

		m_vPlayerPosition.m_fX -= m_vDirection.GetX() * m_fPlayerSpeed * milliseconds;
		m_vPlayerPosition.m_fZ -= m_vDirection.GetZ() * m_fPlayerSpeed * milliseconds;
		*/
	}
	
	if ( m_pDisplay->Down )
	{
		m_pPlayer->Move (1.0f);
		/*
		CSIBCMatrix4x4	rotMat;
		rotMat.SetToRotation ( CSIBCVector3D ( 0.0f, m_fRotation*DEG2RAD, 0.0f ));
		rotMat.Multiply ( m_vDirection, CSIBCVector3D(0.0f, 0.0f, 1.0f));
		
		m_vPlayerPosition.m_fX += m_vDirection.GetX() * m_fPlayerSpeed * milliseconds;
		m_vPlayerPosition.m_fZ += m_vDirection.GetZ() * m_fPlayerSpeed * milliseconds;
		*/
	}
	
	if ( m_pDisplay->Left )
	{
		m_pPlayer->Turn ( 1.0f );
//		m_fRotation += 5.0f;
	}
	
	if ( m_pDisplay->Right )
	{
		m_pPlayer->Turn ( -1.0f );
		//m_fRotation -= 5.0f;
	}

	if ( m_pDisplay->Jump )
	{
		m_pPlayer->Jump();
		m_pDisplay->Jump = 0;
	}

		if ( ( m_pDisplay->Up ) || 
		( m_pDisplay->Down ) || 
		( m_pDisplay->Left )|| 
		( m_pDisplay->Right ))
	{
#ifndef NOPLAYER
		//m_pPlayer->GetGeometry()->SetCurrentShapeTrack ( 1 );
		//m_pPlayer->GetGeometry()->SetFrameRate ( 60.0f );
#endif
	} else {
#ifndef NOPLAYER
		//m_pPlayer->GetGeometry()->SetCurrentShapeTrack ( 0 );
		//m_pPlayer->GetGeometry()->SetFrameRate ( 60.0f );
#endif
	}


	if ( ( m_pDisplay->CamUp ) || 
		( m_pDisplay->CamDown ) || 
		( m_pDisplay->CamLeft ) || 
		( m_pDisplay->CamRight ))
	{
		m_vCameraPosition.m_fY += 2.0f * ( m_pDisplay->CamUp != 0 );
		m_vCameraPosition.m_fY -= 2.0f * ( m_pDisplay->CamDown != 0 );
		m_vCameraPosition.m_fX += 2.0f * ( m_pDisplay->CamLeft != 0 );
		m_vCameraPosition.m_fX -= 2.0f * ( m_pDisplay->CamRight != 0 );

		SetCameraPosition ( m_vCameraPosition, m_vCameraInterest, true );
	}

	l_intersectionlist.DisposeData();

	bool l_bAllPolyVisited = m_pLevel->BuildIntersectionList ( m_pPlayer->GetPosition().m_fX, m_pPlayer->GetPosition().m_fY, m_pPlayer->GetPosition().m_fZ, 
										0.0f, -1.0f, 0.0f, 
										l_intersectionlist );

	//
	// apply gravity
	//
	/*
	if ( m_fJumpTime > 0.0f )
		m_fFallingTime = 0.0f;
		*/
	/*
	float gravity = 2.8f * ( m_fFallingTime * m_fFallingTime);

	m_fForce.m_fY -= gravity;
	m_vPlayerPosition.Add ( m_fForce );
	m_fForce.m_fX = ( 0.0f );
	m_fForce.m_fZ = ( 0.0f );

	if ( ( m_pLevel->m_fLastElevation < -1000.0f ) )
	{
		if ( m_vPlayerPosition.m_fY > m_pLevel->m_fLastElevation )
		{
			m_fFallingTime += milliseconds / 1000.0f;
		} else {
			m_vPlayerPosition = lastPlayerPosition;
			m_fFallingTime = 0.0f;
		}
	} else {

		if ( m_vPlayerPosition.m_fY > m_pLevel->m_fLastElevation )
		{
			m_fFallingTime += milliseconds / 1000.0f;
		} else {
			m_vPlayerPosition.m_fY = m_pLevel->m_fLastElevation + 0.8f;
			m_fFallingTime = 0.0f;
		}
	}

*/
	GivePoints ( l_intersectionlist.GetUsed() * 100 );
	if ( l_bAllPolyVisited )
	{
		m_bLevelDone = true;
#ifndef NOPLAYER
		m_pPlayer->GetGeometry()->SetCurrentAction ( ACTION_DANCE, PLAYBACK_RESET | PLAYBACK_COMPLETE);
		//m_pPlayer->GetGeometry()->SetFrameRate ( 30.0f );
#endif

		//
		// give eol points
		//

		GivePoints(  (m_iTime / 1000) * 10  );

	}

	//
	// do the PowerUp logic
	//

	m_fTimeToNextPowerUp -= milliseconds;
	if ( m_fTimeToNextPowerUp < 0.0f )
	{
		m_fTimeToNextPowerUp = 1000.0f * 15.0f;		// 15 sec delay between potential new power ups!

		if ( m_pCurrentPowerUp != NULL )
		{
			m_pCurrentPowerUp->Shutdown ();
			delete m_pCurrentPowerUp;
			m_pCurrentPowerUp = NULL;
		}


		for (int p=0;p<m_pLevel->m_PowerUps.GetUsed();p++)
		{
			PowerUp* power = &m_pLevel->m_PowerUps[p];

			if ( !power->m_bActive )
			{
				float rn = RANDOM_NUM;
				if ( rn <= (power->m_fRate / 100.0f))
				{
					power->m_bActive = true;	// activate!
				}
				break;
			}
		}

	}

	for (int p=0;p<m_pLevel->m_PowerUps.GetUsed();p++)
	{
		PowerUp* power = &m_pLevel->m_PowerUps[p];
		
		if ( power->m_bActive )
		{
			if ( m_pPlayer->GetPosition ().GetDistanceFrom ( CSIBCVector3D ( power->x, power->y, power->z )) < 2.0f )
			{
				power->m_bActive = false;

				if ( m_pCurrentPowerUp != NULL)
				{
					m_pCurrentPowerUp->Shutdown ();
					delete m_pCurrentPowerUp;
				}

				m_pCurrentPowerUp = new SpeedUp();
				
				m_pCurrentPowerUp->Initialize ();
				m_fTimeToNextPowerUp = 1000.0f * 15.0f;		// 15 sec delay between potential new power ups!
			}

		}
	}
	
	return 1;
}

void	GameState::Render ( float milliseconds )
{

	glPushAttrib ( GL_ENABLE_BIT );
	glEnable ( GL_CULL_FACE );
/*
	glDisable ( GL_DEPTH_TEST );
	glDepthMask ( GL_FALSE );
	glPushMatrix();
	vector3 from, at;
	m_pCamera->GetLookAt ( from, at );
	glTranslatef (from.x, from.y, from.z );
	m_SkyBox->render ();
	glPopMatrix();
	glEnable( GL_DEPTH_TEST );
	glDepthMask ( GL_TRUE);
*/
	
	//////////
	//
	// render reflection
	//
	// 1- Turn on stencil buffer and render mirror into it
	// 2- Render reflection geometry with stencil test on
	// 3- render mirror
	//
	//////////
/*
	glDisable(GL_DEPTH_TEST);
	glDepthMask ( GL_FALSE );
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilFunc(GL_ALWAYS, 1, ~0);
	glColorMask(0,0,0,0);

	glBegin ( GL_TRIANGLES );

	for (int v=0;v<m_pLevel->m_Polygons.GetUsed();v++)
	{
		SinglePolygon *sp = &m_pLevel->m_Polygons[v];
		
		if ( !sp->m_bWalkable )
			continue;
		
		glVertex3f ( sp->v1->position.x, sp->v1->position.y, sp->v1->position.z );
		glVertex3f ( sp->v2->position.x, sp->v2->position.y, sp->v2->position.z );
		glVertex3f ( sp->v3->position.x, sp->v3->position.y, sp->v3->position.z );
	}
	
	glEnd();

	glEnable(GL_DEPTH_TEST);
	glDepthMask ( GL_TRUE );
	glColorMask(1,1,1,1);

	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilFunc(GL_EQUAL, 1, ~0);

#ifndef NOPLAYER	
	glPushMatrix();
	glTranslatef ( m_vPlayerPosition.m_fX, m_vPlayerPosition.m_fY-1.0f, m_vPlayerPosition.m_fZ);
	glRotatef ( m_fRotation, 0.0f, 1.0f, 0.0f );
	glScalef ( 0.2f, 0.2f, 0.2f );
	glColor4f ( 1.0f, 1.0f, 1.0f, 1.0f);
	glScalef ( 1.0f, -1.0f, 1.0f );
	m_pPlayer->Render ();
	glPopMatrix();
#endif

	glPushMatrix();
	glScalef ( 1.0f, -1.0f, 1.0f );
	//m_pEnemy->Render ( 0 );

	for (int g=0;g<m_pLevelDef->m_AssetGeometry.GetUsed();g++)
	{
		m_pLevelDef->m_AssetGeometry[g]->Render();
	}


	glPopMatrix();
	glDisable(GL_STENCIL_TEST);
*/
	m_pLevel->Render ( milliseconds);
	glPopAttrib();

#ifndef NOPLAYER
	
	m_pPlayer->Render();
/*
	glPushMatrix();
	glTranslatef ( m_vPlayerPosition.m_fX, m_vPlayerPosition.m_fY-1.0f, m_vPlayerPosition.m_fZ);
	glRotatef ( m_fRotation, 0.0f, 1.0f, 0.0f );
	glScalef ( 0.2f, 0.2f, 0.2f );
	glColor4f ( 1.0f, 1.0f, 1.0f, 1.0f);
	m_pPlayer->Render ( );
	glPopMatrix();


	CSIBCMatrix4x4 offset;
	offset.SetTranslation ( CSIBCVector3D(m_vPlayerPosition.m_fX, m_vPlayerPosition.m_fY, m_vPlayerPosition.m_fZ));
	//offset.SetRotation ( CSIBCVector3D(0.0f, m_fRotation, 0.0f) );
	offset.SetScaling ( CSIBCVector3D(0.2f, 0.2f, 0.2f) );

	m_pPlayer->OffsetBoundingBox ( offset );
	//m_pPlayer->RenderBoundingBoxList ();
	*/
#endif

	//m_pEnemy->Render ( milliseconds );

	for (int e=0;e<m_lEnemyList.GetUsed();e++)
	{
		m_lEnemyList[e]->Render();
#ifdef _DEBUG
		m_lEnemyList[e]->RenderBoundingBox();
#endif
		
	}

	if ( m_pCurrentPowerUp != NULL )
	{
		m_pCurrentPowerUp->Render ( milliseconds );
	}

	//
	// render all billboards
	//

	m_pBBManager->Render ();

	RenderOverlay();

	RenderStats ( milliseconds);

}


void	GameState::LoadLevel ( Level* in_pLevelDef, char *in_szFilename )
{
	if ( m_pLevel != NULL )
	{
		delete m_pLevel;
		m_pLevel = NULL;
	}

	m_pLevel = new Geometry ( m_pDisplay );
	m_pLevel->Load ( in_szFilename );
	m_pLevel->SetPowerUpMesh ( m_pPowerUpMesh );

	m_pLevelDef = in_pLevelDef;

	//
	// create enemies;
	//

	m_lEnemyList.DisposeData();

	for (int e=0;e<in_pLevelDef->m_iNumEnemies;e++)
	{
		Enemy* l_pEnemy = new Enemy(m_pDisplay);

		l_pEnemy->LearnAboutTheLevel ( m_pLevel );

		m_lEnemyList.Extend(1);
		m_lEnemyList[m_lEnemyList.GetUsed()-1] = l_pEnemy;

	}


}

void	GameState::LoadPlayer()
{
	if ( m_pPlayer != NULL )
	{
		delete m_pPlayer;
		m_pPlayer = NULL;
	}

	m_pPlayer = new Player ( m_pDisplay );
}

void	GameState::ReloadEnemies()
{
	int e;

	for (e=0;e<m_lEnemyList.GetUsed();e++)
	{
		delete m_lEnemyList[e];
	}

	m_lEnemyList.DisposeData();

	if ( m_pLevelDef )
	{
		for (e=0;e<m_pLevelDef->m_iNumEnemies;e++)
		{
			Enemy* l_pEnemy = new Enemy(m_pDisplay);

			l_pEnemy->LearnAboutTheLevel ( m_pLevel );

			m_lEnemyList.Extend(1);
			m_lEnemyList[m_lEnemyList.GetUsed()-1] = l_pEnemy;

		}
	}
}


void	GameState::ResetGeometry()
{
	if ( m_pLevel != NULL )
	{
		delete m_pLevel;
		m_pLevel = NULL;
	}

	m_pLevel = new Geometry ( m_pDisplay );

	m_pLevel->SetPowerUpMesh ( m_pPowerUpMesh );
}


void GameState::RenderStats(float milliseconds )
{
	
	if ( !m_bLevelDone )
		return;

	glPushAttrib( GL_ALL_ATTRIB_BITS );
	
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	
	glDisable(GL_TEXTURE_2D);									
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);							
	glEnable(GL_BLEND);											
	glDisable ( GL_DEPTH_TEST );
	
	float viewport[4];
	glGetFloatv(GL_VIEWPORT,viewport);
	
	float midy = viewport[2] / 2.0f;
	
	glColor4f ( 1.0f, 1.0f, 1.0f, 1.0f);
	m_pDisplay->Print ( midy,viewport[3]/2.0f,FONT_BIG,"TOTAL" );

	glColor4f ( 0.8f, 0.8f, 1.0f, 1.0f);
	if ( m_fEndOfLevelTime < 7000 )
	{
		int minutes = (m_iTime /1000) / 60.0f;
		int seconds = (m_iTime /1000) % 60;
		
		
		m_pDisplay->Print ( midy,viewport[3]/2 - 25.0f,0,"%d:%d * 10         = %d",minutes,seconds, (m_iTime / 1000) * 10  );
	}

	if ( m_fEndOfLevelTime < 6000 )
	{
		m_pDisplay->Print ( midy,viewport[3]/2 - 50.0f,0,"PowerUps * 10     = %d",0 * 10  );
	}

	if ( m_fEndOfLevelTime < 5000 )
	{
		m_pDisplay->Print ( midy,viewport[3]/2 - 75.0f,0,"Bonus             = %d",0  );
	}

	glPopAttrib();

	
	if (m_fEndOfLevelTime < 3000 )
	{
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
		
		m_fWhiteOutAlpha += ( milliseconds / 300.0f);
		glColor4f (1.0f, 1.0f, 1.0f, m_fWhiteOutAlpha );
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
		
		glPopAttrib();
		
	}

}
void GameState::RenderOverlay()
{

	glPushAttrib( GL_ALL_ATTRIB_BITS );
	
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	
	glDisable(GL_TEXTURE_2D);									
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);							
	glEnable(GL_BLEND);											
	glDisable ( GL_DEPTH_TEST );

	float viewport[4];
	glGetFloatv(GL_VIEWPORT,viewport);
	
	float midy = viewport[2] / 2.0f;

	char fps[256];
	sprintf ( fps, "fps: %f", m_fFPS);

	glColor4f ( 1.0f, 1.0f, 1.0f, 1.0f);
	m_pDisplay->Print ( midy,10,0,fps );

	glPopAttrib();

	return;
}

void		GameState::SetPlayerSpeed( float in_fSpeed )
{
	m_pPlayer->SetMaxSpeed ( in_fSpeed );
}

GameState*	GetGameState(Display* in_pDisplay)
{
	if ( g_pZeGameState == NULL )
	{
		g_pZeGameState = new GameState ( in_pDisplay );
	}

	return g_pZeGameState;
}

BillboardManager*	GetBillboardManager()
{
	
	return g_pZeGameState->GetBillboardManager();
}


void		KillGameState()
{
	if ( g_pZeGameState != NULL )
	{
		delete g_pZeGameState;
		g_pZeGameState = NULL;
	}
}


int		GameState::DoEndOfLevel ( float milliseconds )
{
	m_fNewCamTime-= milliseconds;
	m_fEndOfLevelTime -= milliseconds;

	if ( m_fNewCamTime < 0.0f )
	{
		m_EOLCam.m_fX = (RANDOM_NUM - 0.5f) * 2.0f;
		m_EOLCam.m_fY = (RANDOM_NUM - 0.5f) * 2.0f;
		m_EOLCam.m_fZ = (RANDOM_NUM - 0.5f) * 2.0f;

		m_EOLCam = m_EOLCam * 8.0f;

		m_EOLCam = m_EOLCam + m_pPlayer->GetPosition();

		if ( m_EOLCam.m_fY < -2.5f )
			m_EOLCam.m_fY = -2.5f;

		m_fNewCamTime = (2000 * RANDOM_NUM) + 200;

	}


	vector3 pos = vector3(m_EOLCam.m_fX,m_EOLCam.m_fY,m_EOLCam.m_fZ);
	vector3 interest = vector3(m_pPlayer->GetPosition().m_fX,m_pPlayer->GetPosition().m_fY+1.0f,m_pPlayer->GetPosition().m_fZ);
	m_pCamera->SmoothLookAt ( pos, interest );

	m_pCamera->Tick ( m_pLevel, milliseconds );


	vector3	l_vFrom;
	vector3	l_vTo;
	
	m_pCamera->GetLookAt ( l_vFrom, l_vTo );

	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
		
	gluLookAt ( l_vFrom.x, l_vFrom.y, l_vFrom.z,
		l_vTo.x, l_vTo.y, l_vTo.z,
		0.0f,1.0f,0.0f );

	float lpos[]= { 0.0f, 15.0f, -10.0f, 1.0f };
	glLightfv ( GL_LIGHT0,GL_POSITION, lpos);
	glEnable ( GL_LIGHT0);


#ifndef NOPLAYER
		//m_pPlayer->GetGeometry()->SetCurrentShapeTrack ( 2 );
		//m_pPlayer->GetGeometry()->SetFrameRate ( 20.0f );
#endif

	
	return ( m_fEndOfLevelTime < 0.0f ? 0 : 1 );
}


void		GameState::ResetForNextLevel ()
{
	m_fRotation = 180.0f;
	
	m_lScore = 0;
	
	m_fNewCamTime = 0;
	m_fEndOfLevelTime = 8000;
	
	m_bLevelDone = false;

	m_fWhiteOutAlpha = 0.0f;

	m_fTimeToNextPowerUp = 1000.0f;

	m_fPlayerSpeed = 0.028f;

	m_pPlayer->GetGeometry()->GetBoundingBoxList()[0]->m_bTransformed = false;

	
	for (int e=0;e<m_lEnemyList.GetUsed();e++)
	{
		delete m_lEnemyList[e];
	}

	m_lEnemyList.DisposeData();

	m_fFallingTime = 0.0f;
	m_fJumpTime = 0.0f;


	return;
}

bool	GameState::Cull ( CSIBCVector3D& in_vCenter, CSIBCVector3D& in_vExtent )
{
	return m_pCamera->Cull ( in_vCenter, in_vExtent );
}

bool	GameState::Cull ( BoundingBox* in_pBB )
{
	return m_pCamera->Cull ( in_pBB );
}

CSIBCVector3D GameState::GetCameraPosition()
{

	return m_pCamera->GetFrom();

}
