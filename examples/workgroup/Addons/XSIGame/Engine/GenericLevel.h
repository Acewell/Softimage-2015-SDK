// GenericLevel.h: interface for the GenericLevel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENERICLEVEL_H__6D02B06F_3E76_45F5_807D_8692CD3A81E2__INCLUDED_)
#define AFX_GENERICLEVEL_H__6D02B06F_3E76_45F5_807D_8692CD3A81E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Level.h"
#include "Geometry.h"
#include "GameState.h"


class GenericLevel : public Level  
{
public:
	GenericLevel( Display* in_pDisplay );
	virtual ~GenericLevel();

	virtual void	Initialize () {};
	virtual void	Unload() {};

	virtual int Render( DWORD milliseconds );


	virtual void ChooseNewCameraPosition ( float ix, float iy, float iz, 
											float* ox, float* oy, float* oz );

protected:

	virtual	int DrawIntroScreen( DWORD milliseconds );
	float	m_fWhiteInTime;
	int		m_iLevel;

//	Geometry	m_Geometry;

};

#endif // !defined(AFX_GENERICLEVEL_H__6D02B06F_3E76_45F5_807D_8692CD3A81E2__INCLUDED_)
