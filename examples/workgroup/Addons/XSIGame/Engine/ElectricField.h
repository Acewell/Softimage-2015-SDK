// ElectricField.h: interface for the ElectricField class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ELECTRICFIELD_H__5D8931E0_385C_4B8F_B20A_C4D81E65D132__INCLUDED_)
#define AFX_ELECTRICFIELD_H__5D8931E0_385C_4B8F_B20A_C4D81E65D132__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#pragma warning (disable : 4786)
#pragma warning (disable : 4251)	// cf http://support.microsoft.com/support/kb/articles/Q134/9/80.asp

#include <map>
#include <vector>

#include <SIBCUtil.h>
#include <SIBCVector.h>
#include <SIBCColor.h>
#include "Display.h"

typedef struct
{
	float		m_lSR;
	float		m_lSG;
	float		m_lSB;
	float		m_lSA;
	float		m_lER;
	float		m_lEG;
	float		m_lEB;
	float		m_lEA;
	
	float		m_fSX;
	float		m_fSY;
	float		m_fSZ;
	float		m_fEX;
	float		m_fEY;
	float		m_fEZ;

	float		m_fSizeStart;
	float		m_fSizeEnd;
	
	LONG		m_iAmount;

	float		m_fPeriod;
	float		m_fRange;

	float		m_fNoise;

	LONG		m_lBlendSrc;
	LONG		m_lBlendDest;

	float		m_lBR;
	float		m_lBG;
	float		m_lBB;
	float		m_lBA;

	float		m_fBoltWidth;

	float		m_fSpeed;

	LONG		m_iModifier;
	

} ElectricParam;


class ElectricField;

class ElectricPoint
{
public:
	ElectricPoint( );
	~ElectricPoint();

	void	Tick ( ElectricField* in_pParent, SI_Float in_fDelta, void *in_pPtr);
	void	Init ( ElectricField* in_pParent, SI_Float in_fLife );

	CSIBCVector3D	m_vPosition;
	CSIBCVector3D	m_vOriginalPosition;
	float			m_fSize;
	float			m_fLife;
	float			m_fInitialLife;

};

class ElectricField  
{
public:
	ElectricField();
	virtual ~ElectricField();

	void	SetDisplay ( Display* in_pDisplay ) { m_pDisplay = in_pDisplay;};

	void	SetStart ( CSIBCVector3D	in_vStart ) { m_vStart = in_vStart; };
	void	SetEnd	 ( CSIBCVector3D	in_vEnd ) { m_vEnd = in_vEnd; };

	void	SetSizeStart ( SI_Float in_fStart ) { m_fSizeStart = in_fStart; };
	void	SetSizeEnd	 ( SI_Float in_fEnd ) { m_fSizeEnd = in_fEnd; };

	void	SetColorStart ( CSIBCColorf in_cStart ) { m_cColorStart = in_cStart; };
	void	SetColorEnd	 ( CSIBCColorf in_cEnd ) { m_cColorEnd = in_cEnd; };

	CSIBCVector3D	GetStart () { return m_vStart; };
	CSIBCVector3D	GetEnd () { return m_vEnd; };

	SI_Float	GetSizeStart () { return m_fSizeStart; };
	SI_Float	GetSizeEnd () { return m_fSizeEnd; };

	CSIBCColorf	GetColorStart() { return m_cColorStart; };
	CSIBCColorf	GetColorEnd() { return m_cColorEnd; };

	void		SetParticleCount( SI_Int in_iCount );

	void		Tick ( SI_Float in_fDelta, void *in_pPtr );

	void		Fnc  ( SI_Int in_iFncNb );

	void		SetPeriod ( SI_Float in_fPeriod ) { m_fPeriod = in_fPeriod; };
	void		SetRange  ( SI_Float in_fRange  ) { m_fRange = in_fRange; };
	void		SetNoise  ( SI_Float in_fNoise  ) { m_fNoise = in_fNoise; };

	SI_Float	GetPeriod () { return m_fPeriod; };
	SI_Float	GetRange () { return m_fRange; };
	SI_Float	GetNoise () { return m_fNoise; };

	void		SetBlendSrc		( SI_Int in_iSrc ) { m_lBlendSrc = in_iSrc; };
	void		SetBlendDest	( SI_Int in_iDest ) { m_lBlendDest = in_iDest; };
	
	SI_Int		GetBlendSrc		() { return m_lBlendSrc; };
	SI_Int		GetBlendDest	() { return m_lBlendDest; };

	void		SetBoltColor	( CSIBCColorf in_cColor ) { m_cBoltColor = in_cColor; };
	void		SetBoltWidth	( SI_Float in_fWidth ) { m_fBoltWidth = in_fWidth; };

	void		SetModifier		( SI_Int in_iModifier ) { m_iModifier = in_iModifier; };
	SI_Int		GetModifier		() { return m_iModifier ; };


private:

	CSIBCVector3D	m_vStart;
	CSIBCVector3D	m_vEnd;

	SI_Float		m_fSizeStart;
	SI_Float		m_fSizeEnd;

	CSIBCColorf		m_cColorStart;
	CSIBCColorf		m_cColorEnd;

	CSIBCColorf		m_cBoltColor;

	SI_Float		m_fBoltWidth;

	SI_Int			m_iParticleCount;

	ElectricPoint	*m_pParticles;

	SI_Int			m_iFnc;

	SI_Float		m_fPeriod;
	SI_Float		m_fRange;
	SI_Float		m_fNoise;

	SI_Int			m_lBlendSrc;
	SI_Int			m_lBlendDest;

	SI_Int			m_iModifier;

	Display*	m_pDisplay;
	
	int				m_iTexture;


};

#endif // !defined(AFX_ELECTRICFIELD_H__5D8931E0_385C_4B8F_B20A_C4D81E65D132__INCLUDED_)
