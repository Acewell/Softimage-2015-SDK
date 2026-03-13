#pragma once

#include "Engine.h"
#include "dotXSI.h"
#include "Display.h"

#define ACTION_RUN	0
#define ACTION_IDLE	1
#define ACTION_DANCE 1	

class ENGINE_API Player
{
public:
	Player(Display* in_pDisplay);
	~Player(void);

	void	Tick ( float milliseconds );
	void	Render ();

	void	Move ( float in_fUnits );
	void	Turn ( float in_fUnits );
	void	Jump ();

	CSIBCVector3D& GetPosition () { return m_vPosition; };
	CSIBCVector3D& GetDirection () { return m_vStraight; };

	void SetPosition ( CSIBCVector3D& in ) { m_vPosition = in; };
	dotXSI*			GetGeometry() { return m_pGeometry;};
	void			SetMaxSpeed ( float in_fSpeed ) { MAX_SPEED = in_fSpeed; };

private:

	void	ApplyForce			( float in_fDelta );
	void	Integrate			( float in_fDelta );
	void	ResolveCollisions	( float in_fDelta );

	Display*	m_pDisplay;
	dotXSI*		m_pGeometry;

	CSIBCVector3D	m_vVelocity;
	CSIBCVector3D	m_vForce;
	CSIBCVector3D	m_vStraight;
	CSIBCVector3D	m_vRotation;
	CSIBCVector3D	m_vPosition;
	CSIBCMatrix4x4	m_mOrientation;
	CSIBCVector3D	m_vLastGoodPosition;

	bool			m_bIsOnGround;
	float			m_fFallTime;

	float			m_fPlayerSpeed;
	float			m_fCurrentSpeed;
	float			m_fCurrentFriction;
	float			MAX_SPEED;

};
