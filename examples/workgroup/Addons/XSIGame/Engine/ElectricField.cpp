// ElectricField.cpp: implementation of the ElectricField class.
//
//////////////////////////////////////////////////////////////////////

//#ifndef _XBOX
#include "StdAfx.h"
//#endif

#include "ElectricField.h"
#include "SIBCMatrix.h"
//#include "MatrixHelper.h"
#include <GL/gl.h>

void MultMat ( CSIBCMatrix4x4& in_mat, CSIBCVector3D& src, CSIBCVector3D& dst );
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ElectricField::ElectricField() :
m_iParticleCount (0),
m_fSizeStart(0),
m_fSizeEnd(0),
m_pParticles (NULL),
m_iTexture(-1)
{

}

ElectricField::~ElectricField()
{
	if ( m_pParticles )
		delete [] m_pParticles;


}

void ElectricField::SetParticleCount( SI_Int in_iCount )
{
	if ( m_iParticleCount != in_iCount )
	{

		//
		// Initialize a new list of particles
		//

		if ( m_pParticles )
			delete [] m_pParticles;

		m_pParticles = new ElectricPoint [ in_iCount ];

		m_iParticleCount = in_iCount;

		for (int i=0;i<m_iParticleCount;i++)
		{
			m_pParticles[i].Init ( this, (SI_Float) ((SI_Float)i / (SI_Float)m_iParticleCount)) ;
		}
		
	}

}

void ElectricField::Tick ( SI_Float in_fDelta, void *in_pPtr )
{

	if ( m_iTexture == -1 )
	{
		m_iTexture = m_pDisplay->AddTexture ( _T("flare.bmp") );
	}

	glPushAttrib ( GL_ALL_ATTRIB_BITS );

	glEnable ( GL_TEXTURE_2D );
	glBindTexture (GL_TEXTURE_2D, m_iTexture);
		 
	
	for (int i=0;i<m_iParticleCount;i++)
	{
		m_pParticles[i].Tick ( this, in_fDelta, in_pPtr );
	}
	
	
	glColor4f ( m_cBoltColor.m_fR, m_cBoltColor.m_fG, m_cBoltColor.m_fB, m_cBoltColor.m_fA );
	
	glLineWidth ( m_fBoltWidth );
	
	glDisable ( GL_LIGHTING );
	glEnable ( GL_BLEND );
	glDepthMask ( GL_FALSE );
	glEnable( GL_DEPTH_TEST );
	
	glDisable ( GL_TEXTURE_2D );
	
	
	glBegin ( GL_LINES );
	
	
	for (int l=0;l<m_iParticleCount-1;l++)
	{
		glVertex3f ( m_pParticles[l].m_vPosition.m_fX, m_pParticles[l].m_vPosition.m_fY, m_pParticles[l].m_vPosition.m_fZ );
		glVertex3f ( m_pParticles[l+1].m_vPosition.m_fX, m_pParticles[l+1].m_vPosition.m_fY, m_pParticles[l+1].m_vPosition.m_fZ );
	}
	
	
	
	glEnd();
	
	glPopAttrib();

}

void ElectricField::Fnc  ( SI_Int in_iFncNb )
{
	m_iFnc = in_iFncNb;
}


//////////////////////////////////////////////////////////
//
// ElectricPoint
//
//////////////////////////////////////////////////////////

ElectricPoint::ElectricPoint() :
m_fSize(0.0f),
m_fLife(0.0f)
{}

ElectricPoint::~ElectricPoint()
{}

void ElectricPoint::Tick ( ElectricField* in_pParent, SI_Float in_fDelta, void *in_pPtr )
{
	//
	// Determine the position
	//

	CSIBCVector3D	l_vNormalized = in_pParent->GetEnd () - in_pParent->GetStart();

	l_vNormalized = l_vNormalized * m_fInitialLife;

	m_vPosition = in_pParent->GetStart() + l_vNormalized;

	CSIBCColorf	l_cNormalized = in_pParent->GetColorEnd ();
	l_cNormalized.m_fR -= in_pParent->GetColorStart().m_fR;
	l_cNormalized.m_fG -= in_pParent->GetColorStart().m_fG;
	l_cNormalized.m_fB -= in_pParent->GetColorStart().m_fB;
	l_cNormalized.m_fA -= in_pParent->GetColorStart().m_fA;

	l_cNormalized.m_fR *= m_fInitialLife;
	l_cNormalized.m_fG *= m_fInitialLife;
	l_cNormalized.m_fB *= m_fInitialLife;
	l_cNormalized.m_fA *= m_fInitialLife;

	l_cNormalized.m_fR += in_pParent->GetColorStart().m_fR;
	l_cNormalized.m_fG += in_pParent->GetColorStart().m_fG;
	l_cNormalized.m_fB += in_pParent->GetColorStart().m_fB;
	l_cNormalized.m_fA += in_pParent->GetColorStart().m_fA;

	SI_Float		l_fSize = fabs(in_pParent->GetSizeEnd () - in_pParent->GetSizeStart ());
	l_fSize *= m_fInitialLife;

	m_fSize = l_fSize + in_pParent->GetSizeEnd ();

	m_fLife += in_fDelta;

	if ( m_fLife > 1.0f )
	{
		m_fLife = m_fLife - 1.0f;
	}

	if ( m_fLife < 0.0f )
	{
		m_fLife = 1.0f;
	}

	
	//
	// Apply modifier 
	//

	if ( in_pParent->GetModifier () == 0 )
	{
		m_vPosition.m_fY += sin ( m_fLife * 3.1415926f * (in_pParent->GetPeriod() / 10.0f) ) * (in_pParent->GetRange () / 10.0f);
		m_vPosition.m_fZ += cos ( m_fLife * 3.1415926f * (in_pParent->GetPeriod() / 10.0f) ) * (in_pParent->GetRange () / 10.0f);
		m_vPosition.m_fX += sin ( m_fLife * 3.1415926f * (in_pParent->GetPeriod() / 10.0f) ) * (in_pParent->GetRange () / 10.0f);

		SI_Float r1 = RANDOM_NUM;
		SI_Float issigned = RANDOM_NUM;

		r1 *= ( in_pParent->GetNoise () / 10.0f );

		if ( issigned > 0.5f )
		{
			r1 *= -1.0f;
		}

		m_vPosition.m_fY += r1;
	} else {
		

		CSIBCVector3D	l_vNormalized2 = in_pParent->GetEnd () - in_pParent->GetStart();
		l_vNormalized2 = l_vNormalized2 * m_fLife;
		m_vPosition = in_pParent->GetStart() + l_vNormalized2;
		
		SI_Float r1 = RANDOM_NUM;
		SI_Float issigned = RANDOM_NUM;

		r1 *= ( in_pParent->GetNoise () / 10.0f );

		if ( issigned > 0.5f )
		{
			r1 *= -1.0f;
		}

		m_vPosition.m_fY += r1;
	}

	if (( m_fInitialLife == 0.0f ) || ( m_fInitialLife >= 1.0f ) )
	{
		m_vPosition = in_pParent->GetStart() + l_vNormalized;
	}




		glPushAttrib ( GL_ALL_ATTRIB_BITS );

		//
		// Disable ZBuffer updates
		//

		//
		// IMPORTANT: 
		// Here we disable the ZBuffer write operations but keep the read operation active. This is because
		// we need to zbuffer the whole particle system against the world, but not against itself!

		glDepthMask ( GL_FALSE );
		glEnable( GL_DEPTH_TEST );

		glBlendFunc(in_pParent->GetBlendSrc(),in_pParent->GetBlendDest());

		glDisable (GL_LIGHTING);
		glEnable (GL_BLEND);
		glDisable (GL_FOG);
		glDisable (GL_DITHER);
		glHint ( GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST );
		glDisable( GL_CULL_FACE );

		//
		// Get modelview matrix
		//

		GLfloat camera[16];
		
		glMatrixMode ( GL_MODELVIEW );

		glGetFloatv(GL_MODELVIEW_MATRIX, camera);

		CSIBCMatrix4x4	l_ModelView ( camera );
		CSIBCVector4D	z ( 0.0f,0.0f,0.0f,1.0f );
		
		l_ModelView.Set(3,0, 0.0f);
		l_ModelView.Set(3,1, 0.0f);
		l_ModelView.Set(3,2, 0.0f);
		l_ModelView.Set(3,3, 1.0f);
		
		CSIBCVector3D p1 ( m_fSize * 1.0f, m_fSize * 1.0f, 0.0f );
		CSIBCVector3D p2 ( -m_fSize * 1.0f, m_fSize * 1.0f, 0.0f );
		CSIBCVector3D p3 ( m_fSize * 1.0f, -m_fSize * 1.0f, 0.0f );
		CSIBCVector3D p4 ( -m_fSize * 1.0f, -m_fSize * 1.0f, 0.0f );

		CSIBCVector3D rp1, rp2, rp3, rp4;

		MultMat ( l_ModelView, p1, rp1 );
		MultMat ( l_ModelView, p2, rp2 );
		MultMat ( l_ModelView, p3, rp3 );
		MultMat ( l_ModelView, p4, rp4 );

		glColor4f(l_cNormalized.m_fR, l_cNormalized.m_fG, l_cNormalized.m_fB, l_cNormalized.m_fA );

		glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2f(1.0f, 1.0f); 
			glVertex3f( rp1.m_fX + m_vPosition.m_fX, rp1.m_fY + m_vPosition.m_fY, rp1.m_fZ + m_vPosition.m_fZ);

			glTexCoord2f(0.0f, 1.0f); 
			glVertex3f( rp2.m_fX + m_vPosition.m_fX, rp2.m_fY + m_vPosition.m_fY, rp2.m_fZ + m_vPosition.m_fZ);

			glTexCoord2f(1.0f, 0.0f); 
			glVertex3f( rp3.m_fX + m_vPosition.m_fX, rp3.m_fY + m_vPosition.m_fY, rp3.m_fZ + m_vPosition.m_fZ);

			glTexCoord2f(0.0f, 0.0f); 
			glVertex3f( rp4.m_fX + m_vPosition.m_fX, rp4.m_fY + m_vPosition.m_fY, rp4.m_fZ + m_vPosition.m_fZ);
		glEnd();
		

		glPopAttrib();




}

void ElectricPoint::Init ( ElectricField* in_pParent, SI_Float in_fLife )
{
	m_fInitialLife = m_fLife = in_fLife;
	
}

void MultMat ( CSIBCMatrix4x4& in_mat, CSIBCVector3D& src, CSIBCVector3D& dst )
{
	
	float w = (
		src.GetX() * in_mat.Get(3,0) +
		src.GetY() * in_mat.Get(3,1) +
		src.GetZ() * in_mat.Get(3,2) +
		in_mat.Get(3,3)          );
	
	float rx, ry, rz;
	
	dst.m_fX  = (
		src.GetX() * in_mat.Get(0,0) +
		src.GetY() * in_mat.Get(0,1) + 
		src.GetZ() * in_mat.Get(0,2) + 
		in_mat.Get(0,3)          ) / w;
	dst.m_fY  = (
		src.GetX() * in_mat.Get(1,0) +
		src.GetY() * in_mat.Get(1,1) +
		src.GetZ() * in_mat.Get(1,2) +
		in_mat.Get(1,3)          ) / w;
	dst.m_fZ  = (
		src.GetX() * in_mat.Get(2,0) +
		src.GetY() * in_mat.Get(2,1) +
		src.GetZ() * in_mat.Get(2,2) +
		in_mat.Get(2,3)          ) / w;
	
	
}
