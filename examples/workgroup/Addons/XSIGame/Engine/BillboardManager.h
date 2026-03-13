// BillboardManager.h: interface for the BillboardManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BILLBOARDMANAGER_H__02CF03EF_B2D9_4256_93E7_5C144EA27947__INCLUDED_)
#define AFX_BILLBOARDMANAGER_H__02CF03EF_B2D9_4256_93E7_5C144EA27947__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "engine.h"
#include <SemanticLayer.h>
#include "Display.h"
#include "Geometry.h"

typedef struct tagBillboard
{
	CSIBCVector3D	m_vPosition;
	float			m_fSize;
	CSIBCVector4D	m_vColor;
} Billboard;

class ENGINE_API BillboardManager  
{
public:
	BillboardManager(Display* in_pDisplay );
	virtual ~BillboardManager( );

	void	AddBillboard(CSIBCVector3D& in_vPosition, 
								float in_fSize,
								CSIBCVector4D& in_vColor);
	void	Render();

private:
	CSIBCArray<Billboard*> m_BillboardList;

	int			m_iFlareTexture;
};

#endif // !defined(AFX_BILLBOARDMANAGER_H__02CF03EF_B2D9_4256_93E7_5C144EA27947__INCLUDED_)
