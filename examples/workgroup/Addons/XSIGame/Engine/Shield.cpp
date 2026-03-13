// Shield.cpp: implementation of the Shield class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Shield.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Shield::Shield() :
m_pGeometry ( NULL )
{
	rot = rot2 = rot3 = 0.0f;
	
}

Shield::~Shield()
{
	if ( m_pGeometry )
	{
		delete m_pGeometry;
		m_pGeometry = NULL;
	}
}

void	Shield::Initialize()
{
	m_pGeometry = new dotXSI;
	m_pGeometry->Load ( "shield.xsi", GetGameState(NULL)->GetDisplay() );
	m_pGeometry->UseDotXSIMaterials ( false ); // we will override the material settings

	for (int b=0;b<4;b++)
	{
		Bolts[b].SetDisplay ( GetGameState(NULL)->GetDisplay() );
		Bolts[b].SetBoltColor ( CSIBCColorf(1.0f, 1.0f, 1.0f));
		Bolts[b].SetBoltWidth ( 2.0f );
		Bolts[b].SetColorEnd ( CSIBCColorf(1.0f, 0.0f, 0.0f));
		Bolts[b].SetColorStart ( CSIBCColorf(1.0f, 0.5f, 0.1f));

		Bolts[b].SetNoise ( 5.0f );
		Bolts[b].SetParticleCount ( 20 );
		Bolts[b].SetPeriod ( 1.0f );
		Bolts[b].SetSizeStart ( 2.0f );
		Bolts[b].SetSizeEnd ( 2.0f );
		Bolts[b].SetBlendSrc ( GL_SRC_ALPHA );
		Bolts[b].SetBlendDest ( GL_ONE );
	}
}

void	Shield::Render(float milliseconds)
{

	GameState* p_State = GetGameState(NULL);
	
	/*
	if ()
	{
		p_State->GivePoints ( 20 );	// give back the points
		
		CSIBCVector3D playerpos = GetGameState(NULL)->GetPlayerPosition();

		Bolts[0].SetEnd ( playerpos + CSIBCVector3D(-15.0f, 0.0f, -15.0f ));
		Bolts[1].SetEnd ( playerpos + CSIBCVector3D(-15.0f, 0.0f, 15.0f ));
		Bolts[2].SetEnd ( playerpos + CSIBCVector3D(15.0f, 0.0f, 15.0f ));
		Bolts[3].SetEnd (  playerpos + CSIBCVector3D(15.0f, 0.0f, -15.0f ));
		
		for (int b=0;b<4;b++)
		{
			Bolts[b].SetStart ( playerpos );
			Bolts[b].Tick ( 0.02f, NULL );
		}	
		
		
	}
	*/

	glEnable ( GL_BLEND );
	glBlendFunc ( GL_SRC_ALPHA, GL_ONE );

	glPushMatrix();
	glTranslatef ( p_State->GetPlayerPosition().m_fX, 
					p_State->GetPlayerPosition().m_fY+1.0f,
					p_State->GetPlayerPosition().m_fZ );

	glColor4f ( 1.0f, 1.0f, 1.0f, 0.9f);

	glMatrixMode ( GL_TEXTURE );
	glLoadIdentity();
	rot += ( milliseconds / 500.0f );
	rot2 += ( milliseconds / 1000.0f );
	rot3 += ( milliseconds / 1500.0f );

	glTranslatef ( rot, rot2, rot3 );
	glMatrixMode ( GL_MODELVIEW );
	
	m_pGeometry->Tick ( milliseconds);
	m_pGeometry->Render ();

	glMatrixMode ( GL_TEXTURE );
	glLoadIdentity();
	glMatrixMode ( GL_MODELVIEW );

	glPopMatrix();
	
	

	
}

void	Shield::Shutdown()
{

}
