// BillboardManager.cpp: implementation of the BillboardManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BillboardManager.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BillboardManager::BillboardManager(Display* in_pDisplay)
{
	m_iFlareTexture = in_pDisplay->AddTexture ( _T("flare.bmp") );
}

BillboardManager::~BillboardManager()
{

}

void	BillboardManager::AddBillboard(CSIBCVector3D& in_vPosition, 
								float in_fSize,
								CSIBCVector4D& in_vColor)
{
	DEBUGENTRY ( "BillboardManager::AddBillboard");

	Billboard* l_vNB = new Billboard;
	l_vNB->m_vPosition = in_vPosition;
	l_vNB->m_vColor  = in_vColor;
	l_vNB->m_fSize = in_fSize;

	m_BillboardList.Extend(1);
	m_BillboardList[m_BillboardList.GetUsed()-1] = l_vNB;
}	

void	BillboardManager::Render()
{

	DEBUGENTRY ( "BillboardManager::Render");

	glPushAttrib ( GL_ALL_ATTRIB_BITS );
	
	glDepthMask ( GL_FALSE );
	glDisable( GL_DEPTH_TEST );
	glBlendFunc(GL_SRC_ALPHA ,GL_ONE);
	
	glDisable (GL_LIGHTING);
	glEnable (GL_BLEND);
	glDisable (GL_FOG);
	glDisable (GL_DITHER);
	glHint ( GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST );
	glDisable( GL_CULL_FACE );
	
	glEnable ( GL_TEXTURE_2D );
	glBindTexture (GL_TEXTURE_2D, m_iFlareTexture);

	GLfloat camera[16];
	glMatrixMode ( GL_MODELVIEW );
	glGetFloatv(GL_MODELVIEW_MATRIX, camera);
	
	CSIBCMatrix4x4	l_ModelView ( camera );
	CSIBCVector4D	z ( 0.0f,0.0f,0.0f,1.0f );
	
	l_ModelView.Set(3,0, 0.0f);
	l_ModelView.Set(3,1, 0.0f);
	l_ModelView.Set(3,2, 0.0f);
	l_ModelView.Set(3,3, 1.0f);
	
	for (int b=0;b<m_BillboardList.GetUsed();b++)
	{
		float l_fSize = m_BillboardList[b]->m_fSize;
		CSIBCVector3D p1 ( l_fSize * 1.0f, l_fSize * 1.0f, 0.0f );
		CSIBCVector3D p2 ( -l_fSize * 1.0f, l_fSize * 1.0f, 0.0f );
		CSIBCVector3D p3 ( l_fSize * 1.0f, -l_fSize * 1.0f, 0.0f );
		CSIBCVector3D p4 ( -l_fSize * 1.0f, -l_fSize * 1.0f, 0.0f );
		
		CSIBCVector3D rp1, rp2, rp3, rp4;
		
		MultMatrix ( l_ModelView, p1, rp1 );
		MultMatrix ( l_ModelView, p2, rp2 );
		MultMatrix ( l_ModelView, p3, rp3 );
		MultMatrix ( l_ModelView, p4, rp4 );
		
		glColor4f(m_BillboardList[b]->m_vColor.m_fX,
					m_BillboardList[b]->m_vColor.m_fY,
					m_BillboardList[b]->m_vColor.m_fZ,
					m_BillboardList[b]->m_vColor.m_fW );
			
		glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(1.0f, 1.0f); 
		glVertex3f( rp1.m_fX + m_BillboardList[b]->m_vPosition.m_fX, rp1.m_fY + m_BillboardList[b]->m_vPosition.m_fY + 1, rp1.m_fZ + m_BillboardList[b]->m_vPosition.m_fZ);
		
		glTexCoord2f(0.0f, 1.0f); 
		glVertex3f( rp2.m_fX + m_BillboardList[b]->m_vPosition.m_fX, rp2.m_fY + m_BillboardList[b]->m_vPosition.m_fY + 1, rp2.m_fZ + m_BillboardList[b]->m_vPosition.m_fZ);
		
		glTexCoord2f(1.0f, 0.0f); 
		glVertex3f( rp3.m_fX + m_BillboardList[b]->m_vPosition.m_fX, rp3.m_fY + m_BillboardList[b]->m_vPosition.m_fY + 1, rp3.m_fZ + m_BillboardList[b]->m_vPosition.m_fZ);
		
		glTexCoord2f(0.0f, 0.0f); 
		glVertex3f( rp4.m_fX + m_BillboardList[b]->m_vPosition.m_fX, rp4.m_fY + m_BillboardList[b]->m_vPosition.m_fY + 1, rp4.m_fZ + m_BillboardList[b]->m_vPosition.m_fZ);
		glEnd();

		delete m_BillboardList[b];
	}

	glPopAttrib();

	m_BillboardList.DisposeData();
	
}
