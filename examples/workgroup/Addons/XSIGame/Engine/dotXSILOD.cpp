// dotXSILOD.cpp: implementation of the dotXSILOD class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dotXSILOD.h"
#include "GameState.h"

#include <io.h>

#define MAX_LOD_DISTANCE	40.0f
#define MIN_LOD_DISTANCE	10.0f

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

dotXSILOD::dotXSILOD()
{
	m_iCurrentLOD = 0;
}

dotXSILOD::~dotXSILOD()
{

}

void dotXSILOD::Load ( char* in_szPath, Display* in_pDisplay )
{

	m_pDisplay = in_pDisplay;

	//
	// Load LOD 0
	//

	dotXSI* l_pLODLevel = new dotXSI();
	m_pLODList.Extend(1);
	m_pLODList[m_pLODList.GetUsed()-1] = l_pLODLevel;
	l_pLODLevel->Load ( in_szPath, in_pDisplay );


	//
	// Handle all other LODs
	//

	LONG	handle;
	int		done;
	
	_finddata_t fileinfo;
	memset(&fileinfo, 0, sizeof(_finddata_t));

	char filespec[MAX_PATH];
	sprintf ( filespec, "..\\data\\models\\%s*", in_szPath );

	handle = _findfirst(filespec, &fileinfo);

	if (handle>=0)
	{
		done = 0;
		while (!done)
		{
			if ( strcmp(fileinfo.name, in_szPath))
			{
				l_pLODLevel = new dotXSI();
				m_pLODList.Extend(1);
				m_pLODList[m_pLODList.GetUsed()-1] = l_pLODLevel;
				l_pLODLevel->Load ( fileinfo.name, in_pDisplay );
			}
			
			done = _findnext(handle, &fileinfo);
		}
	}

}

void dotXSILOD::Tick ( DWORD milliseconds )
{
	//
	// choose new LOD for next frame
	//

	float distance = GetGameState(m_pDisplay)->GetCameraPosition ().GetDistanceFrom ( m_vLastOffset );

	float Adjusted = distance - MIN_LOD_DISTANCE;
	float Ratio = ( Adjusted * m_pLODList.GetUsed()-1 ) / (MAX_LOD_DISTANCE - MIN_LOD_DISTANCE);

	Ratio = floor(Ratio + 0.5f);

	if ( Ratio < 0 )
		Ratio = 0;

	if ( Ratio > m_pLODList.GetUsed()-1 )
		Ratio = m_pLODList.GetUsed()-1;


	if ( ((int)Ratio) != m_iCurrentLOD )
	{
		//
		// synchronize next lod to reducing LOD popping

		m_pLODList[Ratio]->SetTime ( m_pLODList[m_iCurrentLOD]->GetTime());
	//	m_pLODList[Ratio]->OffsetBoundingBox ( m_vLastOffset );
	//	m_pLODList[Ratio]->Tick ( 0 );
	//		m_pLODList[Ratio]->Tick ( milliseconds );
	}
	
	m_iCurrentLOD = Ratio;


	m_pLODList[m_iCurrentLOD]->Tick(milliseconds);
}

void dotXSILOD::Render ()
{
	m_pLODList[m_iCurrentLOD]->Render();
}

void dotXSILOD::OffsetBoundingBox ( CSIBCMatrix4x4& in_offMatrix )
{
	m_pLODList[m_iCurrentLOD]->OffsetBoundingBox ( in_offMatrix );
	
	in_offMatrix.GetTranslation(m_vLastOffset);

}

void dotXSILOD::OffsetBoundingBox ( CSIBCVector3D& in_offVector )
{
	m_pLODList[m_iCurrentLOD]->OffsetBoundingBox ( in_offVector );

	m_vLastOffset = in_offVector;
}
void dotXSILOD::SetCurrentAction(int in_iActionIdx)
{
	m_pLODList[m_iCurrentLOD]->SetCurrentAction ( in_iActionIdx );
}

int	dotXSILOD::GetCurrentAction ()
{
	return m_pLODList[m_iCurrentLOD]->GetCurrentAction();
}

void dotXSILOD::SetFrameRate ( float in_fFrameRate)
{
	for (int l=0;l<m_pLODList.GetUsed();l++)
	{
		m_pLODList[l]->SetFrameRate ( in_fFrameRate );
	}
}
void dotXSILOD::RenderBoundingBoxList ()
{
	m_pLODList[m_iCurrentLOD]->RenderBoundingBoxList();
}