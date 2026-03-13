// DiskGameFlow.h: interface for the DiskGameFlow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISKGAMEFLOW_H__6EFD4B36_154D_44E2_AD44_F5788240ECF3__INCLUDED_)
#define AFX_DISKGAMEFLOW_H__6EFD4B36_154D_44E2_AD44_F5788240ECF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "engine.h"
#include "Display.h"
#include "Level.h"

class ENGINE_API DiskGameFlow : public Level
{
public:
	DiskGameFlow( Display* in_pDisplay );
	virtual ~DiskGameFlow();
	
	virtual int Render( DWORD milliseconds );
	virtual void	Initialize ();

private:

	virtual		void Unload();
	

	void		Init();
	void		DrawLogo();
	void		DrawCube();
	
	bool		m_bWelcomeScreen;
	bool		m_bDoWhiteOut;
	int			m_iNewGame;
	int			m_iQuitGame;
	
	float		m_fFontAlpha;
	float		m_fFontAlpha2;

	double		m_fNewGameMinX;
	double		m_fNewGameMinY;
	double		m_fNewGameMinZ;

	double		m_fNewGameMaxX;
	double		m_fNewGameMaxY;
	double		m_fNewGameMaxZ;

	float fwidth0;
	float fwidth1;

	float m_fWhiteOutAlpha;
};

#endif // !defined(AFX_DISKGAMEFLOW_H__6EFD4B36_154D_44E2_AD44_F5788240ECF3__INCLUDED_)
