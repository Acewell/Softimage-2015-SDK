// SpeedUp.cpp: implementation of the SpeedUp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SpeedUp.h"
#include "GameState.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SpeedUp::SpeedUp()
{

}

SpeedUp::~SpeedUp()
{

}

void	SpeedUp::Initialize()
{
	GetGameState(NULL)->SetPlayerSpeed ( 30.0f );
	GetGameState(NULL)->GetDisplay()->SetFOV ( 120.0f );
}

void	SpeedUp::Render(float milliseconds)
{
	GetBillboardManager()->AddBillboard ( GetGameState(NULL)->GetPlayerPosition(), 5.0f, CSIBCVector4D( 0.0f, 0.0f, 1.0f, 0.5f )); 
}

void	SpeedUp::Shutdown()
{
	GetGameState(NULL)->SetPlayerSpeed ( 10.0f );
	GetGameState(NULL)->GetDisplay()->SetFOV ( 65.0f );
}

