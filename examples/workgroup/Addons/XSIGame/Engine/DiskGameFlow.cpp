// DiskGameFlow.cpp: implementation of the DiskGameFlow class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DiskGameFlow.h"

#include <gl/gl.h>
#include <stdlib.h>
#include <tchar.h>

static float ra = 0.0f;
static float rang = 0.0f;
int inverse = 1;


static float		_cubePositions[] =
{
		-1.0f,	-1.0f,	-1.0f	,
		-1.0f,	 1.0f,	-1.0f	,
		 1.0f,	-1.0f,	-1.0f	,
		 1.0f,	 1.0f,	-1.0f	,

		-1.0f,	-1.0f,	 1.0f	,
		 1.0f,	-1.0f,	 1.0f	,
		-1.0f,	 1.0f,	 1.0f	,
		 1.0f,	 1.0f,	 1.0f	,

		-1.0f,	-1.0f,	-1.0f	,
		 1.0f,	-1.0f,	-1.0f	,
		-1.0f,	-1.0f,	 1.0f	,
		 1.0f,	-1.0f,	 1.0f	,

		-1.0f,	 1.0f,	-1.0f	,
		-1.0f,	 1.0f,	 1.0f	,
		 1.0f,	 1.0f,	-1.0f	,
		 1.0f,	 1.0f,	 1.0f	,

		-1.0f,	-1.0f,	-1.0f	,
		-1.0f,	-1.0f,	 1.0f	,
		-1.0f,	 1.0f,	-1.0f	,
		-1.0f,	 1.0f,	 1.0f	,

		 1.0f,	-1.0f,	-1.0f	,
		 1.0f,	 1.0f,	-1.0f	,
		 1.0f,	-1.0f,	 1.0f	,
		 1.0f,	 1.0f,	 1.0f	,
};

static float		_cubeNorms[] =
{
		  0.0f,	 0.0f,	-1.0f	,
		  0.0f,	 0.0f,	-1.0f	,
		  0.0f,	 0.0f,	-1.0f	,
		  0.0f,	 0.0f,	-1.0f	,

		  0.0f,	 0.0f,	 1.0f	,
		  0.0f,	 0.0f,	 1.0f	,
		  0.0f,	 0.0f,	 1.0f	,
		  0.0f,	 0.0f,	 1.0f	,

		  0.0f,	-1.0f,	 0.0f	,
		  0.0f,	-1.0f,	 0.0f	,
		  0.0f,	-1.0f,	 0.0f	,
		  0.0f,	-1.0f,	 0.0f	,

		  0.0f,	 1.0f,	 0.0f	,
		  0.0f,	 1.0f,	 0.0f	,
		  0.0f,	 1.0f,	 0.0f	,
		  0.0f,	 1.0f,	 0.0f	,

		 -1.0f,	 0.0f,	 0.0f	,
		 -1.0f,	 0.0f,	 0.0f	,
		 -1.0f,	 0.0f,	 0.0f	,
		 -1.0f,	 0.0f,	 0.0f	,

		  1.0f,	 0.0f,	 0.0f	,
		  1.0f,	 0.0f,	 0.0f	,
		  1.0f,	 0.0f,	 0.0f	,
		  1.0f,	 0.0f,	 0.0f	,
};

static float	_cubeTexCoords[] =
{
		  0.0f,	 0.0f	,
		  0.0f,	 1.0f	,
		  1.0f,	 0.0f	,
		  1.0f,	 1.0f	,

		  0.0f,	 0.0f	,
		  0.0f,	 1.0f	,
		  1.0f,	 0.0f	,
		  1.0f,	 1.0f	,

		  0.0f,	 0.0f	,
		  0.0f,	 1.0f	,
		  1.0f,	 0.0f	,
		  1.0f,	 1.0f	,

		  0.0f,	 0.0f	,
		  0.0f,	 1.0f	,
		  1.0f,	 0.0f	,
		  1.0f,	 1.0f	,

		  0.0f,	 0.0f	,
		  0.0f,	 1.0f	,
		  1.0f,	 0.0f	,
		  1.0f,	 1.0f	,

		  0.0f,	 0.0f	,
		  0.0f,	 1.0f	,
		  1.0f,	 0.0f	,
		  1.0f,	 1.0f	,
};

typedef int Tri[3];

static Tri		_cubeFaces[] =
{
	{	0,	1,	2	},
	{	3,	2,	1	},

	{	4,	5,	6	},
	{	7,	6,	5	},

	{	8,	9,	10	},
	{	11,	10,	9	},

	{	12,	13,	14	},
	{	15,	14,	13	},

	{	16,	17,	18	},
	{	19,	18,	17	},

	{	20,	21,	22	},
	{	23,	22,	21	},
};

static const int	_numCubeVerts = sizeof(_cubePositions) / sizeof(*_cubePositions);
static const int	_numCubeFaces = sizeof(_cubeFaces) / sizeof(*_cubeFaces);

#define WELCOMEMESSAGE _T("Softimage - Custom Display Host Demo")
#define WELCOMEMESSAGE2 _T("Click Anywhere to Start!")


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DiskGameFlow::DiskGameFlow(Display* in_pDisplay) : Level ( in_pDisplay )
{
	m_pDisplay = in_pDisplay;
	m_iXSITexture = 0;
	m_bWelcomeScreen = false;
	m_fFontAlpha = m_fFontAlpha2 = 1.0f;
	m_bDoWhiteOut = false;
	m_fWhiteOutAlpha = 0.0f;

	Init();
}

DiskGameFlow::~DiskGameFlow()
{
	glDeleteTextures ( 1, (unsigned int*)&m_iBlurTexture );
	glDeleteTextures ( 1, (unsigned int*)&m_iXSITexture  );
	glDeleteTextures ( 1, (unsigned int*)&m_iNewGame );
	glDeleteTextures ( 1, (unsigned int*)&m_iQuitGame );
	
	
}

void DiskGameFlow::Unload()
{
	m_bWelcomeScreen = true;
	m_fFontAlpha = m_fFontAlpha2 = 1.0f;
	m_bDoWhiteOut = false;
	m_fWhiteOutAlpha = 0.0f;
	ra = 0.0f;
	rang = 0.0f;
	m_bInitialized = false;
}

void DiskGameFlow::Initialize()
{
	m_bInitialized = true;
}


int DiskGameFlow::Render( DWORD milliseconds )
{
	DEBUGENTRY ( "DiskGameFlow::Render" );

	static float direction = -1.0f;
	static float direction2 = -1.0f;

	int left, right;

	m_pDisplay->GetButtonsStates ( &left, &right );
	if ( !left && ( m_bWelcomeScreen))
	{
		RenderToTexture();

		DrawCube();

		DrawBlur(25,0.02f,0.0f);

		float viewport[4];
		glGetFloatv(GL_VIEWPORT,viewport);
		
		float midx = viewport[2] / 2.0f;
		float midy = viewport[3] / 2.0f;

		glScalef (2.0f, 2.0f, 2.0f);
		glColor4f ( 0.8f, 0.8f, 0.75,m_fFontAlpha );
		fwidth0 = m_pDisplay->Print ( midx - (midx / 2.0f ),midy, FONT_CENTERED, WELCOMEMESSAGE);

		glColor4f ( 0.8f, 0.8f, 0.9,m_fFontAlpha2 );
		fwidth1 = m_pDisplay->Print ( midx - (midx / 2.0f ) + 60,midy-30,FONT_CENTERED, WELCOMEMESSAGE2);

		glFlush ();
		glPopMatrix();

		ra+= (float)(milliseconds) / 10.0f;

		rang+= (float)(milliseconds) / 30.0f;
	
		rang = ((float)(rand() % 100)) / 10.0f;
	
		m_fFontAlpha += ( milliseconds / 800.0f) * direction;
		m_fFontAlpha2 += ( milliseconds / 500.0f) * direction2;

		if ( m_fFontAlpha <= 0.0f )
		{
			direction = 1.0f;
		} else if ( m_fFontAlpha >= 2.0f )
		{
			direction = -1.0f;
		}

		if ( m_fFontAlpha2 <= 0.0f )
		{
			direction2 = 1.0f;
		} else if ( m_fFontAlpha2 >= 1.0f )
		{
			direction2 = -1.0f;
		}
	} else {

		static float divider = 10.0f;

		m_bWelcomeScreen = 0;

		RenderToTexture();

		DrawCube();

		DrawBlur(25,0.02f,0.0f);

		ra+= (float)(milliseconds) / divider;

		divider -= (float)(milliseconds) / 500.0f;
		
		if ( (divider <= 0.3f) || m_bDoWhiteOut )
		{
			m_bDoWhiteOut = true;

			divider = 0.1f;
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
			
			m_fWhiteOutAlpha += ( milliseconds / 300.0f);
			glColor4f (1.0f, 1.0f, 1.0f, m_fWhiteOutAlpha );
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
			
			glPopAttrib();

			if ( m_fWhiteOutAlpha >= 1.0f )
			{
				return 0;	// stop welcome screen
			}
		}
	}

	return 1; // continue;

}

void DiskGameFlow::Init()
{
	DEBUGENTRY ( "DiskGameFlow::Init" );

	m_bWelcomeScreen = true;
	
	if ( !m_iXSITexture )
	{
		m_iXSITexture = m_pDisplay->AddTexture ( "xsi.bmp" );
		m_iNewGame = m_pDisplay->AddTexture ( "newgame.bmp" );
		m_iQuitGame = m_pDisplay->AddTexture ( "quit.bmp" );

		GLuint txtnumber;											
		unsigned int* data;	
	
		data = (unsigned int*)new GLuint[((128 * 128)* 4 * sizeof(unsigned int))];
		ZeroMemory(data,((128 * 128)* 4 * sizeof(unsigned int)));	

		glGenTextures(1, &txtnumber);								
		glBindTexture(GL_TEXTURE_2D, txtnumber);					
		glTexImage2D(GL_TEXTURE_2D, 0, 4, 128, 128, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, data);						
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		delete [] data;												

		m_iBlurTexture = (int)txtnumber;

	}



}



void	DiskGameFlow::DrawLogo ()
{
	DEBUGENTRY ( "DiskGameFlow::DrawLogo" );
		//
		// draw the Softimage logo
		//

		glPushAttrib( GL_ALL_ATTRIB_BITS );
		
		glColor3f ( 1.0f, 1.0f, 1.0f );
		glDisable(GL_LIGHTING);
		
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(-1, 1, -1, 1);
		
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		
		// reset our texture matrix
		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();
		glEnable(GL_TEXTURE_2D);
		glDisable ( GL_LIGHTING );
		glDisable ( GL_DEPTH_TEST );
		glDisable ( GL_ALPHA_TEST );
		glDisable ( GL_BLEND );
		glDisable ( GL_CULL_FACE );
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
		glDisable(GL_TEXTURE_GEN_R);
		glDisable(GL_TEXTURE_GEN_Q);
		glDisable ( GL_FOG );
		
		glMatrixMode(GL_MODELVIEW);
		
		glBindTexture(GL_TEXTURE_2D, m_iXSITexture);
		
		glBegin(GL_QUADS);
		glTexCoord2f(0,0);
		glVertex2f(-1,-1);
		
		glTexCoord2f(0,1);
		glVertex2f(-1, 1);
		
		glTexCoord2f(1,1);
		glVertex2f( 1, 1);
		
		glTexCoord2f(1,0);
		glVertex2f( 1,-1);
		glEnd();
		
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		
		glMatrixMode(GL_MODELVIEW);
		
		glPopAttrib();
	

}


void	DiskGameFlow::DrawCube()
{
	DEBUGENTRY ( "DiskGameFlow::DrawCube" );

	glPushAttrib( GL_ALL_ATTRIB_BITS );

	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();

	glPushMatrix();

		float pos[]= { 10.0f, 10.0f, 10.0f, 1.0f };
	glLightfv ( GL_LIGHT0,GL_POSITION, pos );
	glEnable ( GL_LIGHT0);

	gluLookAt ( 0.0f, 2.0f, -5.0f, 
				0.0f,0.0f,0.0f,
				0.0f,1.0f,0.0f );

	glPushMatrix();
	glRotatef(ra/2.0f,1,0,0);								// Rotate By angle/2 On The X-Axis
	glRotatef(ra/3.0f,0,1,0);								// Rotate By angle/3 On The Y-Axis


	glEnable ( GL_TEXTURE_2D );
	glEnable ( GL_LIGHTING );
	glBindTexture(GL_TEXTURE_2D, m_iXSITexture);
	glDisable ( GL_BLEND );
	glEnable ( GL_CULL_FACE );
	glCullFace ( GL_BACK );



	glColor3f ( 1.0f, 1.0f, 1.0f);
	glEnable ( GL_COLOR_MATERIAL );

	glBegin ( GL_TRIANGLES );
	
	int t;
	for (t=0;t<_numCubeFaces;t++)
	{
		int* indices = _cubeFaces[t];
		glNormal3f ( _cubeNorms[indices[0] * 3], _cubeNorms[(indices[0]*3)+1] , _cubeNorms[(indices[0]*3)+2] );
		glTexCoord2f ( _cubeTexCoords[indices[0]*2 ], _cubeTexCoords[(indices[0]*2  )+1] );
		glVertex3f ( _cubePositions[indices[0]*3 ], _cubePositions[(indices[0]*3 )+1] , _cubePositions[(indices[0]*3  )+2] );

		glNormal3f ( _cubeNorms[indices[1]*3], _cubeNorms[(indices[1]*3)+1] , _cubeNorms[(indices[1]*3)+2] );
		glTexCoord2f ( _cubeTexCoords[indices[1]*2 ], _cubeTexCoords[(indices[1]*2  )+1] );
		glVertex3f ( _cubePositions[indices[1]*3], _cubePositions[(indices[1] *3 )+1] , _cubePositions[(indices[1]*3  )+2] );
		
		glNormal3f ( _cubeNorms[indices[2]*3], _cubeNorms[(indices[2]*3)+1] , _cubeNorms[(indices[2]*3)+2] );
		glTexCoord2f ( _cubeTexCoords[indices[2]*2 ], _cubeTexCoords[(indices[2]*2  )+1] );
		glVertex3f ( _cubePositions[indices[2]*3], _cubePositions[(indices[2]*3  )+1] , _cubePositions[(indices[2] *3)+2] );
	}

	glEnd();

	glPopMatrix();

	if ( m_bWelcomeScreen )
	{
		float viewport[4];
		glGetFloatv(GL_VIEWPORT,viewport);
		
		float midx = viewport[2] / 2.0f;
		float midy = viewport[3] / 2.0f;
		

		glColor4f ( 1.0f, 1.0f, 1.0f, m_fFontAlpha );
		m_pDisplay->Print ( midx - (midx / 3.0f ),midy,0, WELCOMEMESSAGE);
		glColor4f ( 0.8f, 0.8f, 0.75,m_fFontAlpha2 );
		m_pDisplay->Print ( midx - (midx / 3.0f) + 60,midy-30,0, WELCOMEMESSAGE2);
	}

	glPopAttrib();
}
