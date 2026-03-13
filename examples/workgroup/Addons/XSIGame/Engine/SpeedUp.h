// SpeedUp.h: interface for the SpeedUp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPEEDUP_H__5749D631_6A83_4D84_82D9_0052185E1A05__INCLUDED_)
#define AFX_SPEEDUP_H__5749D631_6A83_4D84_82D9_0052185E1A05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PowerUp.h"

class SpeedUp : public CPowerUp  
{
public:
	SpeedUp();
	virtual ~SpeedUp();

	virtual void	Initialize();
	virtual void	Render(float milliseconds);
	virtual void	Shutdown();

	float	m_fOldSpeed;

};

#endif // !defined(AFX_SPEEDUP_H__5749D631_6A83_4D84_82D9_0052185E1A05__INCLUDED_)
