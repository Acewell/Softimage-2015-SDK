// dotXSILOD.h: interface for the dotXSILOD class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOTXSILOD_H__C83BAC21_EB6A_4B56_8038_00229E75AE9B__INCLUDED_)
#define AFX_DOTXSILOD_H__C83BAC21_EB6A_4B56_8038_00229E75AE9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Engine.h"
#include "dotXSI.h"
#include "Display.h"

#include <SIBCArray.h>

class ENGINE_API dotXSILOD  
{
public:
	dotXSILOD();
	virtual ~dotXSILOD();

	virtual void Load ( char* in_szPath, Display* in_pDisplay );
	virtual void Tick ( DWORD milliseconds );
	virtual void Render ();
	virtual void OffsetBoundingBox ( CSIBCMatrix4x4& in_offMatrix );
	virtual void OffsetBoundingBox ( CSIBCVector3D& in_offVector );
	virtual void SetFrameRate ( float in_fFrameRate);
	virtual void RenderBoundingBoxList ();
	virtual void SetCurrentAction(int in_iActionIdx);
	virtual int	GetCurrentAction ();


private:
	CSIBCArray<dotXSI*>	m_pLODList;
	int					m_iCurrentLOD;
	CSIBCVector3D		m_vLastOffset;
	Display*			m_pDisplay;

};

#endif // !defined(AFX_DOTXSILOD_H__C83BAC21_EB6A_4B56_8038_00229E75AE9B__INCLUDED_)
