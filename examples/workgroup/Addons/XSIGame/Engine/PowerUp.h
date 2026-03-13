// PowerUp.h: interface for the CPowerUp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POWERUP_H__872DAD1D_3F0E_401B_9C59_03C271F0C11C__INCLUDED_)
#define AFX_POWERUP_H__872DAD1D_3F0E_401B_9C59_03C271F0C11C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPowerUp  
{
public:
	CPowerUp();
	virtual ~CPowerUp();

	virtual void	Initialize() {};
	virtual void	Render(float milliseconds) {};
	virtual void	Shutdown() {};

};

#endif // !defined(AFX_POWERUP_H__872DAD1D_3F0E_401B_9C59_03C271F0C11C__INCLUDED_)
