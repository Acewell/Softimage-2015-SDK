// Enemy.h: interface for the Enemy class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMY_H__14EA81D2_FC31_45E9_88D2_FA3840200B55__INCLUDED_)
#define AFX_ENEMY_H__14EA81D2_FC31_45E9_88D2_FA3840200B55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dotXSILOD.h"
#include "Display.h"
#include "ElectricField.h"
#include "Geometry.h"

class Enemy  
{
public:
	Enemy( Display* in_pDisplay);
	virtual ~Enemy();

	void	Tick ( float milliseconds );
	void	Render ( );
	void	RenderBoundingBox ( );
	void	LearnAboutTheLevel ( Geometry* in_pLevel );
	void	LearnAboutPlayerPosition ( CSIBCVector3D );
	void	Goto ( CSIBCVector3D );

	Geometry*	m_pLevel;
	Display*	m_pDisplay;
	dotXSILOD		m_lGeometry;
	CSIBCVector3D	m_vPosition;
	float			m_vRotation;
	CSIBCVector3D	m_vEnemyPosition;
	CSIBCArray<CSIBCVector3D> m_vWaypoints;
	CSIBCMatrix4x4 rotMat;

	ElectricField	Bolt;

	int				m_iFlareTexture;
	float			m_fDistanceToPlayer;
	CSIBCVector3D	m_vLastPlayerPosition;

};

#endif // !defined(AFX_ENEMY_H__14EA81D2_FC31_45E9_88D2_FA3840200B55__INCLUDED_)
