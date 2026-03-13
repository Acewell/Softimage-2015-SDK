// interface for the CXSIGameInterfaceUI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUSTOMUI_H__BFC2FE5E_A859_480A_A1BB_B8CC8ECCE1CA__INCLUDED_)
#define AFX_CUSTOMUI_H__BFC2FE5E_A859_480A_A1BB_B8CC8ECCE1CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <xsi_ref.h>
#include <xsi_decl.h>
#include <xsi_x3dobject.h>
#include <xsi_camera.h>
#include <xsi_model.h>
#include <xsi_cluster.h>
#include <xsi_clusterproperty.h>

#include "Level.h"

typedef struct tagControlPanelStruct 
{
	HWND m_hControlPanel;
	HWND m_hLevel;
	HWND m_hActor;
} ControlPanelStruct;

typedef struct tagPowerUpMap
{
	XSI::X3DObject	m_object;
	int				m_index;
} PowerUpMap;

typedef struct tagAssetEditing
{
	CSIBCString m_szName;
	XSI::Model  m_mModel;
} AssetEditing;

class CXSIGameInterfaceUI
{
public:
	CXSIGameInterfaceUI();
	virtual ~CXSIGameInterfaceUI();

	virtual char*	GetName() { return "CustomUI Example"; };
		
	virtual LRESULT	Init( XSI::CRef& in_pViewCtx );
	virtual LRESULT	Term( XSI::CRef& in_pViewCtx );
	virtual LRESULT Notify ( XSI::CRef& in_pViewCtx );

	//
	// window
	//

	virtual HWND	CreateMainWindow ( HINSTANCE in_hInstance, HWND in_hParent, int x, int y );
	virtual LRESULT SetWindowSize(int ox, int oy, int cx, int cy);
	
	virtual LRESULT Paint( WPARAM, LPARAM );
	virtual LRESULT MouseMove( WPARAM, LPARAM );

	void Render();

	//
	// Softimage Connection
	//

	void					EditFrictionMap();
	XSI::ClusterProperty	GetFrictionMap();

	void	UpdateXSI();
	void	UpdateLevel ( XSI::Primitive in_pPrimitive, bool in_bForceFullUpdate = false);
	void	UpdateLights ();
	void	SyncCamera ( XSI::Camera );
	void	SetCameraType ( int in_iType );

	void	AddPowerUp ( XSI::X3DObject );
	void	SyncPowerUp ( XSI::X3DObject );

	bool	m_bLevelUpdateDone;
	bool	m_bSuspendNotifications;

	void	NextLevel();

	void	SetAutoUpdate ( bool b )  { m_bAutoUpdate = b; };
	bool	GetAutoUpdate () { return m_bAutoUpdate ; };
    
	void	SetPause ( bool b )  { m_bPause = b; };
	bool	GetPause () { return m_bPause; };

	void	SetShowSectors ( bool in_Value );
	void	SetShowAIGrid ( bool in_Value );


	XSI::X3DObject GetX3D() { return m_x3dObject; };

	Level*	GetCurrentLevel() { return m_pLevels[m_iCurrentLevel]; };

	void	EditPlayer();
	void	EditEnnemy();
	void	EditAsset( char* in_szAsset );
	void	UpdateAsset( char* in_szAsset );

	void	AddLevel  ( char* in_szFilename );
	void	AddAsset  ( char* in_szFilename );
	void	RemoveAsset  ( char* in_szFilename );
	void	SaveLevelDef ();

	void	ReloadEnemies ();
	void	ReloadPlayer ();

	void	ReloadSky ();
	XSI::X3DObject m_x3dObject;

	HWND	m_hLevelEditing;
	HWND	m_hActorEditing;

private:

	void	PrintNotification ( char*	in_szMessage );


private:
	HWND	l_hWnd;
	HWND	m_hControlPanel;

	CSIBCArray<Level*>	m_pLevels;
	Display	* m_pDisplay;
	UINT	m_uiTimer;


	DWORD	m_uiLasttickCount;
	DWORD	m_dwTickCount;
	int		m_iCurrentLevel;

	

	CSIBCArray<PowerUpMap>	m_PowerUps;
	CSIBCArray<AssetEditing> m_AssetEdits;

	float	m_fExternalCameraControlTime;

	bool m_bAutoUpdate;
	bool m_bPause;

	
};

typedef struct tagMsg2Name {
	char*	m_szName;
	int		m_iID;
} Msg2Name;



#endif // !defined(AFX_CUSTOMUI_H__BFC2FE5E_A859_480A_A1BB_B8CC8ECCE1CA__INCLUDED_)
