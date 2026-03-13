// GameState.h: interface for the GameState class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMESTATE_H__9ECCCE29_34F9_4561_83D8_88CED8B6D095__INCLUDED_)
#define AFX_GAMESTATE_H__9ECCCE29_34F9_4561_83D8_88CED8B6D095__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Camera.h"
#include "Enemy.h"
#include "Display.h"
#include "Geometry.h"
#include "PowerUp.h"
#include "Level.h"
#include "BillboardManager.h"
#include "SkyBox.h"
#include "Player.h"
#include "dotXSI.h"

#define CAMERA_TYPE_SMART			0
#define CAMERA_TYPE_FOLLOW			1
#define CAMERA_TYPE_TURNTABLE		2
#define CAMERA_TYPE_TURNTABLE_ENEMY	3

class ENGINE_API GameState  
{
public:
	GameState( Display* in_pDisplay );
	virtual ~GameState();

	void	SetEnemyPosition ( CSIBCVector3D in_vPosition );
	void	SetPlayerPosition ( CSIBCVector3D in_vPosition );
	void	SetCameraPosition ( CSIBCVector3D in_vPosition, CSIBCVector3D in_vInterest, bool Smooth = false );
	CSIBCVector3D GetPlayerPosition() { return m_pPlayer->GetPosition(); };

	void	Reset();

	int		Tick ( float milliseconds );
	void	Render ( float milliseconds );

	void	ReloadEnemies();
	void	LoadPlayer();
	void	LoadLevel ( Level* in_pLevelDef, char *in_szFilename );

	void	SetLevelTime ( LONG int_iTime ) { m_iTime = int_iTime;};

	void	GivePoints	( LONG points ) { m_lScore += points;} ;

	int		DoEndOfLevel ( float milliseconds );

	void	ResetForNextLevel ();

	bool	IsLevelDone() { return m_bLevelDone;};

	Geometry* GetGeometry() { return m_pLevel; };
	void	ResetGeometry();

	void	ExternalCameraControl ( bool in_State ) { m_bExternalCameraControl = in_State;};

	Display*	GetDisplay() { return m_pDisplay;};
	
	Enemy*	GetEnemy ( int in_iIdx ) { return m_lEnemyList[in_iIdx]; };
	int		GetNumEnemies() { return m_lEnemyList.GetUsed();};

	float		GetPlayerSpeed() { return m_fPlayerSpeed; };
	void		SetPlayerSpeed( float in_fSpeed );
	bool		Cull ( BoundingBox* );
	bool		Cull ( CSIBCVector3D&, CSIBCVector3D&  );

	BillboardManager* GetBillboardManager() { return m_pBBManager; };

	void		SetCameraType (int in_iType ) { m_iCameraType = in_iType; };
	
	CSIBCVector3D GetCameraPosition();

	void		SetShowSectors ( bool in_bValue ) { m_bShowSectors = in_bValue; };
	bool		GetShowSectors () { return m_bShowSectors; };

	void		SetShowAIGrid ( bool in_bValue ) { m_bShowAIGrid = in_bValue; };
	bool		GetShowAIGrid () { return m_bShowAIGrid; };

	void		SetFPS ( float in_fps ) { m_fFPS = in_fps; };

private:

	void RenderOverlay();
	void RenderStats(float milliseconds );

	CSIBCVector3D	m_vEnemyPosition;
	
	CSIBCVector3D	m_vCameraPosition;
	CSIBCVector3D	m_vCameraInterest;

	CSIBCArray<Enemy*>	m_lEnemyList;
	CPowerUp*		m_pCurrentPowerUp;

	Geometry*		m_pLevel;
	Display*		m_pDisplay;
	Camera*			m_pCamera;
	BillboardManager*	m_pBBManager;
	Player*			m_pPlayer;
	Level*			m_pLevelDef;
	SkyBox*			m_SkyBox;
	

	float			m_fNewCamTime;
	float			m_fEndOfLevelTime;

	bool			m_bLevelDone;

	LONG			m_lScore;
	LONG			m_iTime;
	float			m_fRotation;	// initiale rotation

	float			m_fWhiteOutAlpha;
	float			m_fTimeToNextPowerUp;

	bool			m_bExternalCameraControl;

	float			m_fPlayerSpeed;
	float			m_fFallingTime;
	float			m_fJumpTime;
	
	CSIBCVector3D	m_fForce;

	CSIBCVector3D	m_EOLCam;

	int				m_iCameraType;
	float			m_fLastLookAt;
	float			m_fFPS;

	dotXSI*			m_pPowerUpMesh;

	//
	// debugging
	//
	bool			m_bShowSectors;
	bool			m_bShowAIGrid;

};

GameState*	GetGameState( Display* in_pDisplay );
BillboardManager* GetBillboardManager();

void		KillGameState();

#endif // !defined(AFX_GAMESTATE_H__9ECCCE29_34F9_4561_83D8_88CED8B6D095__INCLUDED_)
