#include <windows.h>
#include <gl/gl.h>
#include "Player.h"
#include "GameState.h"


#define DEG2RAD			0.01745329251994329547f


Player::Player(Display* in_pDisplay)
{
	m_bIsOnGround = false;

	m_pGeometry = new dotXSI;
	m_pGeometry->Load ( "player.xsi", in_pDisplay );
	m_pGeometry->SetCurrentAction ( ACTION_IDLE );
	m_pGeometry->SetFrameRate (30.0f) ;
	m_pDisplay = in_pDisplay;
	m_fCurrentSpeed = 0;

	m_vStraight = CSIBCVector3D ( 0.0f, 0.0f, -1.0f );

	m_fPlayerSpeed = 1.7f;
	MAX_SPEED = 10.0f;

}

Player::~Player(void)
{
	delete m_pGeometry;
}

void	Player::Render ()
{ 
	float lpos[]= { m_vPosition.m_fX, m_vPosition.m_fY+5.0f, m_vPosition.m_fZ, 1.0f };
	glLightfv ( GL_LIGHT0,GL_POSITION, lpos); 
	glEnable ( GL_LIGHT0);
	glDisable ( GL_LIGHTING );
	glPushMatrix();
	glTranslatef ( m_vPosition.m_fX, m_vPosition.m_fY, m_vPosition.m_fZ);
	glRotatef ( m_vRotation.m_fY, 0.0f, 1.0f, 0.0f );
//	glScalef ( 0.2f, 0.2f, 0.2f );
	glColor4f ( 1.0f, 1.0f, 1.0f, 1.0f);
	m_pGeometry->Render ( );
	glPopMatrix();


	CSIBCMatrix4x4 offset;
	offset.SetTranslation ( CSIBCVector3D(m_vPosition.m_fX, m_vPosition.m_fY, m_vPosition.m_fZ));
//	offset.SetScaling ( CSIBCVector3D(0.2f, 0.2f, 0.2f) );

	m_pGeometry->OffsetBoundingBox ( offset );

}


void	Player::Tick ( float milliseconds )
{
	m_pGeometry->Tick ( (DWORD)milliseconds );

	milliseconds /= 1000.0f;

	ApplyForce			( milliseconds );
	Integrate			( milliseconds );
	ResolveCollisions	( milliseconds );

	m_vLastGoodPosition = m_vPosition;

	m_pGeometry->SetCurrentAction ( ACTION_IDLE );
	m_pGeometry->SetFrameRate (23.0f) ;
}

void	Player::Move ( float in_fUnits )
{
	//if ( !m_bIsOnGround)
	//	return;

	m_fCurrentSpeed += m_fPlayerSpeed;

	if ( m_fCurrentSpeed > MAX_SPEED )
	{
		m_fCurrentSpeed = MAX_SPEED;
	}

	m_mOrientation.Multiply ( m_vStraight, CSIBCVector3D(0.0f, 0.0f, -in_fUnits * (MAX_SPEED / 10.0f)));

	m_pGeometry->SetCurrentAction ( ACTION_RUN );
	m_pGeometry->SetFrameRate (50.0f) ;

}

void	Player::Turn ( float in_fUnits )
{
	in_fUnits *=10.0f;

	m_vRotation.m_fY += in_fUnits;

	m_mOrientation.SetIdentity();
	m_mOrientation.SetToRotation ( CSIBCVector3D( 0.0f, m_vRotation.m_fY * DEG2RAD, 0.0f) );
//	m_mOrientation.Multiply ( m_vStraight, CSIBCVector3D(0.0f, 0.0f, 1.0f));

	m_vVelocity.Scale ( m_fCurrentFriction );
	m_pGeometry->SetCurrentAction ( ACTION_RUN );
}

void Player::Jump ()
{
	//m_vVelocity.m_fY += 100.0f;
	m_pGeometry->SetCurrentAction ( ACTION_DANCE, PLAYBACK_RESET | PLAYBACK_COMPLETE );
	m_pGeometry->SetFrameRate (60.0f) ;
}

void Player::ApplyForce ( float in_fDelta )
{
	//
	// Gravity
	//

	CSIBCVector3D s = m_vStraight;

	m_vVelocity = s.Scale (m_fCurrentSpeed * in_fDelta);

	m_vForce = CSIBCVector3D (0.0f, -1.0f, 0.0f );
	m_vForce.Scale (m_fFallTime * m_fFallTime);
	//m_vVelocity.m_fY += m_vForce.m_fY * in_fDelta;

}

void	Player::Integrate			( float in_fDelta )
{
}

void	Player::ResolveCollisions	( float in_fDelta )
{

	CSIBCVector3D newPosition = m_vPosition;
	newPosition.Add ( m_vVelocity );
	//m_vPosition.Add ( m_vVelocity );

	Geometry* l_pLevel = GetGameState(m_pDisplay)->GetGeometry ();

	float elevation;
	CSIBCVector3D normal;
	bool success = l_pLevel->GetElevationFast ( newPosition,  elevation, &normal, &m_fCurrentFriction);

	float MAX_FRICTION = 70.0f;
	float domain = 100.0f - MAX_FRICTION;
	float m_fFrictionC = ((m_fCurrentFriction * 100.0f) * domain) / 100.0f;
	m_fFrictionC += MAX_FRICTION;
	m_fFrictionC /= 100.0f;

	
	m_fCurrentSpeed *=  m_fFrictionC;
	if ( !success )
	{
		elevation = m_vPosition.m_fY;
	}

	if ( newPosition.m_fY <= elevation )
	{
		//
		// collision has occured, resolve
		//
		
		normal = normal.Normalize ();

		float dotP = normal.GetDot ( CSIBCVector3D (0.0f, 1.0f, 0.0f));
		
		newPosition.m_fY = elevation;

		if ( fabs(dotP) < 0.6f )
		{
			//
			// terrain is too steep
			//

			//m_vPosition = m_vLastGoodPosition;
			m_vPosition = newPosition;
		} else {
			m_vPosition = newPosition;
		}


		m_vPosition.m_fY = elevation;

		m_bIsOnGround = true;
		m_fFallTime = 0.0f;

	} else {

		m_vPosition = newPosition;
		m_vPosition.m_fY = elevation;
		/*
		if (( newPosition.m_fY - elevation ) > 1.0f)
		{
			OutputDebugString("FALLING!\n");
			m_bIsOnGround = false;
			//m_fFallTime += (in_fDelta + 1.0f);
			m_vPosition = newPosition;
			m_vPosition.m_fY = elevation;
		} else {
			m_vPosition.m_fY = elevation;
		}
		*/
		

	}

}


