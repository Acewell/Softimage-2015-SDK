// GenericLevel.cpp: implementation of the GenericLevel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GenericLevel.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GenericLevel::GenericLevel(Display* in_pDisplay) : Level ( in_pDisplay )
{
	m_fWhiteInTime = 5.0f;
	m_iLevel = 0;
	srand(time(NULL));
}

GenericLevel::~GenericLevel()
{

}

int GenericLevel::Render( DWORD milliseconds )
{

	return 1;
}

int GenericLevel::DrawIntroScreen( DWORD milliseconds )
{
	if ( m_fWhiteInTime <= -1.0f )
		return 0;

	glPushAttrib( GL_ALL_ATTRIB_BITS );
	
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	
	glDisable(GL_TEXTURE_2D);									
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);							
	glEnable(GL_BLEND);											
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	
	glOrtho( 0, 640 , 480 , 0, -1, 1 );
	
	m_fWhiteInTime -= ( milliseconds / 1000.0f);
	glColor4f (1.0f, 1.0f, 1.0f, m_fWhiteInTime );
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glBegin(GL_QUADS);											
	
	
	glVertex2f(0,0);									
	
	glVertex2f(0,480);									
	
	glVertex2f(640,480);								
	
	glVertex2f(640,0);									
	
	glEnd();														
	
	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	glMatrixMode(GL_MODELVIEW);
	
	
	glEnable(GL_DEPTH_TEST);									
	glDisable(GL_TEXTURE_2D);									
	glDisable(GL_BLEND);										
	glBindTexture(GL_TEXTURE_2D,0);
	
	glColor4f ( 0.2f,
				0.2f,
				0.2f,
				m_fWhiteInTime);

	float viewport[4];
	glGetFloatv(GL_VIEWPORT,viewport);
	
	float midy = viewport[3] / 2.0f;
	
	m_pDisplay->Print ( 0,midy,FONT_CENTERED,"Level %d", m_iLevel );

	glPopAttrib();

	return 1;
}


void GenericLevel::ChooseNewCameraPosition ( float ix, float iy, float iz, 
											float* ox, float* oy, float* oz )
{

	if ( fabs ( *oz - iz ) < 10.0f )
	{
		*oz -= 8.0f;
		
	} else if ( fabs ( *oz - iz ) > 20.0f )
	{
		*oz += 5.0f;
		
	}

	*ox = ((float)(rand() % 100) / 100.0f) * 7.0f;
	*ox *= rand() % 2 ? 1.0f : -1.0f;

}
