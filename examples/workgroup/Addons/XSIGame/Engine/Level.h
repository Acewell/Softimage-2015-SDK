// Level.h: interface for the Level class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEVEL_H__E19A2770_95CC_45D4_9724_1F335E16554B__INCLUDED_)
#define AFX_LEVEL_H__E19A2770_95CC_45D4_9724_1F335E16554B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "engine.h"
#include "Display.h"
#include "Camera.h"
#include "dotXSI.h"
#include "Enemy.h"

class ENGINE_API Level  
{
public:
	Level( Display* in_pDisplay );
	virtual ~Level();

	virtual void	Initialize ();
	virtual void	Unload();

	virtual int Render( DWORD milliseconds );
	virtual void RenderToTexture ();
	virtual void DrawBlur(int times, float inc, float transy);

	virtual void DrawCube();

	virtual bool IsInitialized () { return m_bInitialized; };

	virtual void SetAssets ( CSIBCArray<CSIBCString*>* in_assets );
	virtual void GetAssets ( CSIBCArray<CSIBCString>& out_assets );
	virtual void	ReloadAsset ( char *in_szString );
	virtual void	AddAsset ( char *in_szString );
	virtual void	RemoveAsset ( char *in_szString );
	
	virtual void SetLevelFilename ( char* in_szString );
	virtual	int DrawIntroScreen( DWORD milliseconds );

	virtual void CreateSky();

	Display*	m_pDisplay;
	
	static int			m_iXSITexture;
	static int			m_iBlurTexture;

	Camera*		m_pCamera;

	bool		m_bInitialized;
	float		m_fWhiteInTime;

	CSIBCArray<CSIBCString*> m_Assets;
	char					m_szLevelFilename[MAX_PATH];
	CSIBCArray<dotXSI*>		m_AssetGeometry;

	float	m_fPositionX;
	float	m_fPositionY;
	float	m_fPositionZ;
	float	m_fRotation;

	int		m_iNumEnemies;
				
	char	m_SkyTexture1[MAX_PATH];
	char	m_SkyTexture2[MAX_PATH];
	char	m_ShaderName[MAX_PATH];
	float	m_fFogColor[4];
	float	m_fFogDistance;

};

#endif // !defined(AFX_LEVEL_H__E19A2770_95CC_45D4_9724_1F335E16554B__INCLUDED_)
