#include "skybox.h"
#include <gl/gl.h>

SkyBox::SkyBox(Display* in_pDisplay)
{
	m_pDisplay = in_pDisplay;
}

SkyBox::~SkyBox(void)
{
}

void	SkyBox::load ( char* in_szSkyBoxName )
{
	CSIBCString l_szName;

	l_szName = in_szSkyBoxName;
	l_szName.Concat ( "bk.bmp" );
    m_iSkyBoxTextures[0] = m_pDisplay->AddTexture ( l_szName.GetText() );

	l_szName = in_szSkyBoxName;
	l_szName.Concat ( "dn.bmp" );
    m_iSkyBoxTextures[1] = m_pDisplay->AddTexture ( l_szName.GetText() );

	l_szName = in_szSkyBoxName;
	l_szName.Concat ( "ft.bmp" );
    m_iSkyBoxTextures[2] = m_pDisplay->AddTexture ( l_szName.GetText() );

	l_szName = in_szSkyBoxName;
	l_szName.Concat ( "lf.bmp" );
    m_iSkyBoxTextures[3] = m_pDisplay->AddTexture ( l_szName.GetText() );

	l_szName = in_szSkyBoxName;
	l_szName.Concat ( "rt.bmp" );
    m_iSkyBoxTextures[4] = m_pDisplay->AddTexture ( l_szName.GetText() );

	l_szName = in_szSkyBoxName;
	l_szName.Concat ( "up.bmp" );
    m_iSkyBoxTextures[5] = m_pDisplay->AddTexture ( l_szName.GetText() );
}


void SkyBox::render ()
{
static const GLint faces[6][4] =
  {
   
    {5, 1, 2, 6}, // back
    {5, 4, 0, 1}, // bottom
    {0, 4, 7, 3}, // front
    {4, 5, 6, 7}, // right 
    {1, 0, 3, 2}, // left  
    {2, 3, 7, 6}  // top
  };

	glPushAttrib ( GL_ENABLE_BIT );
	glDisable ( GL_LIGHTING );
	glEnable ( GL_TEXTURE_2D);
	glDisable ( GL_BLEND );
	glEnable ( GL_COLOR_MATERIAL );


  GLfloat v[8][3];
  GLint i;

  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;  // min x
  v[4][0] = v[5][0] = v[6][0] = v[7][0] =  1;  // max x
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;  // min y
  v[2][1] = v[3][1] = v[6][1] = v[7][1] =  1;  // max y
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = -1;  // min z
  v[1][2] = v[2][2] = v[5][2] = v[6][2] =  1;  // max z

  glColor3f ( 1.0f, 1.0f, 1.0f );
  for (i = 5; i >= 0; i--) 
  {
    glBindTexture(GL_TEXTURE_2D, m_iSkyBoxTextures[i]);
    glBegin(GL_QUADS);
    {
      glTexCoord2f(0,1);  glVertex3fv(&v[faces[i][0]][0]);
      glTexCoord2f(1,1);  glVertex3fv(&v[faces[i][1]][0]);
      glTexCoord2f(1,0);  glVertex3fv(&v[faces[i][2]][0]);
      glTexCoord2f(0,0);  glVertex3fv(&v[faces[i][3]][0]);
    }
    glEnd();
  }

  glPopAttrib();
}
