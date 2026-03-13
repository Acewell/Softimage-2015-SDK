// Shield.h: interface for the Shield class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHIELD_H__80090F9D_4D10_4DB7_B932_11532D31B295__INCLUDED_)
#define AFX_SHIELD_H__80090F9D_4D10_4DB7_B932_11532D31B295__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PowerUp.h"
#include "GameState.h"
#include "dotXSI.h"
#include "ElectricField.h"

class Shield : public CPowerUp  
{
public:
	Shield();
	virtual ~Shield();

	virtual void	Initialize();
	virtual void	Render(float milliseconds);
	virtual void	Shutdown();

	dotXSI*	m_pGeometry;
	float	rot;
	float	rot2;
	float	rot3;

	ElectricField	Bolts[4];
};

#endif // !defined(AFX_SHIELD_H__80090F9D_4D10_4DB7_B932_11532D31B295__INCLUDED_)
