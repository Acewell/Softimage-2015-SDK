// Enemy.cpp: implementation of the Enemy class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Enemy.h"
#include "GameState.h"
#include <set>
#include <time.h>
#include <stdio.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define ACTION_WALK 0
#define ACTION_FIRE 1
Enemy::Enemy(Display* in_pDisplay)
{
	m_pDisplay = in_pDisplay;

	m_lGeometry.Load ( _T("skeleton.xsi"), m_pDisplay );
	m_lGeometry.SetFrameRate ( 30.0f );
	m_lGeometry.SetCurrentAction (1);
	
	Bolt.SetDisplay ( in_pDisplay );
	Bolt.SetBoltColor ( CSIBCColorf(1.0f, 1.0f, 1.0f));
	Bolt.SetBoltWidth ( 2.0f );
	Bolt.SetColorEnd ( CSIBCColorf(1.0f, 1.0f, 1.0f));
	Bolt.SetColorStart ( CSIBCColorf(1.0f, 1.0f, 1.0f));

	Bolt.SetNoise ( 2.0f );
	Bolt.SetParticleCount ( 10 );
	Bolt.SetPeriod ( 2.0f );
	Bolt.SetSizeStart ( 1.0f );
	Bolt.SetSizeEnd ( 1.0f );
	Bolt.SetBlendSrc ( GL_SRC_ALPHA );
	Bolt.SetBlendDest ( GL_ONE );

	m_iFlareTexture = in_pDisplay->AddTexture ( _T("flare.bmp") );
}	

Enemy::~Enemy()
{

}

void Enemy::LearnAboutPlayerPosition ( CSIBCVector3D in_vector )
{
	m_vLastPlayerPosition = in_vector;
	m_fDistanceToPlayer = m_vPosition.GetDistanceFrom ( in_vector );

	if (  m_vEnemyPosition.GetDistanceFrom ( in_vector ) > 5.0f )
	{
		m_vEnemyPosition = in_vector;

		AStarNode* target;
		if ( m_pLevel->FindPath ( m_vPosition, m_vEnemyPosition, &target ) )
		{
			m_vWaypoints.DisposeData();
			std::set<AStarNode*>	pathList;
			m_vWaypoints.Extend(1);
			m_vWaypoints[m_vWaypoints.GetUsed()-1] = CSIBCVector3D(target->x,0.0f, target->z);
			while ( target->parent )
			{
				pathList.insert ( target );

				m_vWaypoints.Extend(1);
				m_vWaypoints[m_vWaypoints.GetUsed()-1] = CSIBCVector3D(target->x,0.0f, target->z);
				target = target->parent;

				if ( pathList.find ( target ) != pathList.end() )
				{
					//
					// found a circular dependancy!
					//
					break;
				}
			}
		}
	}

}

void Enemy::Tick ( float milliseconds )
{
	m_lGeometry.Tick ( milliseconds  );

	
	bool canfire = true;
	
	if ( GetGameState(m_pDisplay)->IsLevelDone())
		canfire = false;

	//
	// move forward
	//
	if ( !m_vWaypoints.GetUsed() )
	{
		rotMat.SetIdentity();
		rotMat.SetToRotation ( CSIBCVector3D(0.0f, m_vRotation * 0.0174533f, 0.0f) );
	} else {
		CSIBCVector3D l_pos;
		l_pos.m_fX = m_vPosition.m_fX;
		l_pos.m_fZ = m_vPosition.m_fZ;

		float d = l_pos.GetDistanceFrom ( m_vWaypoints[m_vWaypoints.GetUsed()-1]);

		if ( d < 2.0f )
		{
			m_vWaypoints.DeleteAt ( m_vWaypoints.GetUsed()-1, 1);
		}

		if ( m_vWaypoints.GetUsed() )
		{
			Goto ( m_vWaypoints[m_vWaypoints.GetUsed()-1]);
		}

	}


	if ( m_lGeometry.GetCurrentAction () != ACTION_FIRE )
	{
		CSIBCVector3D l_vForwardVector;
		rotMat.Multiply ( l_vForwardVector, CSIBCVector3D(0.0f, 0.0f, milliseconds));

		m_vPosition.Add ( l_vForwardVector.Scale (0.005f) );


		m_lGeometry.OffsetBoundingBox ( m_vPosition );

		if ( !m_pLevel->GetElevationFast ( m_vPosition, m_vPosition.m_fY) )
		{
			m_vRotation += 180.0f;
		}
	}
	
}

void Enemy::Render ()
{

	glPushMatrix();
	glTranslatef ( m_vPosition.m_fX, m_vPosition.m_fY, m_vPosition.m_fZ );
	glRotatef (m_vRotation, 0.0f, 1.0f, 0.0f );
	m_lGeometry.Render ();
	glPopMatrix();


	GetBillboardManager()->AddBillboard ( m_vPosition, 2.0f, CSIBCVector4D( 1.0f, 0.0f, 0.0f, 0.2f )); 

	if (m_fDistanceToPlayer<5.0f)
	{
		m_lGeometry.SetCurrentAction ( ACTION_FIRE );
		Bolt.SetStart ( CSIBCVector3D(m_vPosition.m_fX,m_vPosition.m_fY+2.0f, m_vPosition.m_fZ ));
		Bolt.SetEnd ( CSIBCVector3D(m_vLastPlayerPosition.m_fX, m_vLastPlayerPosition.m_fY+2.0f, m_vLastPlayerPosition.m_fZ));

		Bolt.Tick ( 0.02f, NULL );
		GetGameState(m_pDisplay)->GivePoints ( -20 );
	} else {
		m_lGeometry.SetCurrentAction ( ACTION_WALK );
	}
}

void Enemy::RenderBoundingBox()
{
//	m_lGeometry.RenderBoundingBoxList ();
}

void	Enemy::LearnAboutTheLevel ( Geometry* in_pLevel )
{
	//
	// choose a random spawn position
	//

	LONG l_iNumVertex = in_pLevel->m_Vertices.GetUsed();
	LONG l_rPos = rand () % l_iNumVertex;

	srand(time(NULL));
	m_vRotation = rand() % 360;

	m_vPosition = CSIBCVector3D ( in_pLevel->m_Vertices[l_rPos].position.x,
									0.0f,
									in_pLevel->m_Vertices[l_rPos].position.z );

	AStarNode* l_pClosest = in_pLevel->FindClosestNode ( m_vPosition );

	if ( l_pClosest )
	{
		m_vPosition.m_fX = l_pClosest->x;
		m_vPosition.m_fZ = l_pClosest->z;
	}

	m_pLevel = in_pLevel;

}

void Enemy::Goto ( CSIBCVector3D in_point )
{
	
	CSIBCVector3D toTarget = in_point - m_vPosition;
	float angle = atan2(toTarget.m_fX , toTarget.m_fZ );
	angle *= 57.29577951308232286465f;
	//angle = 270.0f;
	//if ( angle < 0 )
	//	angle += 360.0f;

	rotMat.SetIdentity();
	rotMat.SetToRotation ( CSIBCVector3D(0.0f, angle * 0.0174533f, 0.0f) );

	m_vRotation = ( angle );
}
