// OpenGLDisplay.cpp: implementation of the OpenGLDisplay class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <tchar.h>
#include <stdio.h>
#include "OpenGLDisplay.h"

char OpenGLDisplay::m_szRootPath[MAX_PATH];


//
// local functions
//

LRESULT CALLBACK	_view_proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
FILETIME GetFileLastWriteAccess( TCHAR *in_csFilePath );
extern char g_szStaticString[MAX_PATH];
char* FixTexturePath (char* in_szString)
{
	SetCurrentDirectory(OpenGLDisplay::m_szRootPath);
	memset ( g_szStaticString,0,MAX_PATH );
	sprintf ( g_szStaticString, "%s\\data\\textures\\%s", OpenGLDisplay::m_szRootPath, in_szString );
	return g_szStaticString;
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

OpenGLDisplay::OpenGLDisplay()
{
	m_fAspect = 1.0f;	

}

OpenGLDisplay::~OpenGLDisplay()
{

	if ( m_bAutomaticTextureReload )
	{
		KillTimer ( m_hWnd, 1 );
	}
}


void	OpenGLDisplay::Initialize	( HINSTANCE in_hInstance, HWND in_hParent, DWORD in_dwStyle, DWORD in_dwExtendedStyle, void* in_pUserData )
{
	GLuint		PixelFormat;									
	WNDCLASS	wc;												
	DWORD		dwExStyle;										
	DWORD		dwStyle;
	RECT		WindowRect;

	//
	// Set the root path
	//
	char l_szPath[MAX_PATH];
	char drive[MAX_PATH];
	char directory[MAX_PATH];
	GetModuleFileName ( in_hInstance, l_szPath, MAX_PATH );
	_splitpath ( l_szPath, drive, directory, NULL, NULL );

	// Remove the Application path if present
	// This is when the plugin is running in Softimage
	char *l_cResult = strstr(directory, "\\Application\\");
	if (l_cResult!=0)
	{
		*l_cResult = '\0';
	}
	else
	{
		// Here we are running the game which is under the 
		// bin directory.
		char *l_cResult = strstr(directory, "\\bin\\");
		if (l_cResult!=0)
			*l_cResult = '\0';
	}
	
	char l_szFileLocation[MAX_PATH];
	sprintf ( l_szFileLocation, "%s%s", drive, directory );

	// Get the location path from the file that we set from the control panel
	strcat ( l_szFileLocation, "\\datalocation.txt");
	FILE *f;
	f = fopen ( l_szFileLocation, "r" );
	if (f)
	{
		fscanf( f, "%s", m_szRootPath);
		fclose(f);
	}
	else
		sprintf ( m_szRootPath, "%s%s", drive, directory );


	if ( m_szRootPath[ strlen(m_szRootPath) - 1 ] == '\\' )
	{
		m_szRootPath[ strlen(m_szRootPath) - 1 ]  = 0;
	}


	////////////////////////////
	GetClientRect (in_hParent, &WindowRect);
	
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	
	wc.lpfnWndProc		= (WNDPROC) _view_proc;					
	wc.cbClsExtra		= 0;									
	wc.cbWndExtra		= 0;									
	wc.hInstance		= in_hInstance;							
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			
	wc.hbrBackground	= NULL;									
	wc.lpszMenuName		= NULL;									
	wc.lpszClassName	= "OpenGL";								

	RegisterClass(&wc);

	
	dwExStyle=in_dwExtendedStyle;			
	dwStyle=in_dwStyle;		

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);	

	if (!(m_hWnd=CreateWindowEx(	dwExStyle,
								"OpenGL",
								"engine",
								dwStyle |
								WS_CLIPSIBLINGS |
								WS_CLIPCHILDREN,
								0, 0,
								WindowRect.right-WindowRect.left,
								WindowRect.bottom-WindowRect.top,
								in_hParent,
								NULL,
								in_hInstance,
								NULL)))
	{
		Shutdown();
		return;
	}

	SetWindowLong ( m_hWnd, GWL_USERDATA, (LONG)this);

	static	PIXELFORMATDESCRIPTOR pfd=							
	{
		sizeof(PIXELFORMATDESCRIPTOR),							
		1,														
		PFD_DRAW_TO_WINDOW |									
		PFD_SUPPORT_OPENGL |									
		PFD_DOUBLEBUFFER,										
		PFD_TYPE_RGBA,											
		32,													
		0, 0, 0, 0, 0, 0,										
		0,														
		0,														
		0,														
		0, 0, 0, 0,												
		16,														
		1,														
		0,														
		PFD_MAIN_PLANE,											
		0,														
		0, 0, 0													
	};
	
	if (!(hDC=GetDC(m_hWnd)))
	{
		Shutdown();	
		return;
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))
	{
		Shutdown();	
		return;
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))
	{
		Shutdown();
		return;
	}

	if (!(hRC=wglCreateContext(hDC)))
	{
		Shutdown();
		return;
	}	

	if(!wglMakeCurrent(hDC,hRC))
	{
		Shutdown();
		return;
	}

	ShowWindow(m_hWnd,SW_SHOW);
	Resize(WindowRect.right-WindowRect.left, WindowRect.bottom-WindowRect.top );

	//
	// init GL

	glClearColor(0.0f, 0.0f, 0.0f,0.0f );
	glDisable  ( GL_LIGHTING );
	glEnable ( GL_CULL_FACE );
	glCullFace ( GL_BACK );

	if ( m_bAutomaticTextureReload )
	{
		SetTimer ( m_hWnd, 1, 3000, NULL );
	}

	glMultiTexCoord2f          = (PFNGLMULTITEXCOORD2FPROC)wglGetProcAddress("glMultiTexCoord2f");

}

int		OpenGLDisplay::Print (int x, int y, LONG flags, TCHAR* in_szString, ...)
{
	TCHAR		text[256];									
	va_list		ap;
	int fwidth = 0;

	void* fontType = GLUT_BITMAP_8_BY_13;

	if ( flags & FONT_BIG )
	{
		fontType = GLUT_BITMAP_TIMES_ROMAN_24;
	}

	if (in_szString == NULL)										
		return 0;
		
	va_start(ap, in_szString);										
	    _vstprintf(text, in_szString, ap);							
	va_end(ap);												

	
	glPushAttrib( GL_ALL_ATTRIB_BITS );
	
	//glColor3f ( 1.0f, 1.0f, 1.0f );
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	float viewport[4];
	glGetFloatv(GL_VIEWPORT,viewport);

	gluOrtho2D(0, viewport[2],0, viewport[3]);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	int length = _tcslen ( text );

	
	int i;

	
	glPixelZoom(2,2);
	if ( flags & FONT_CENTERED )
	{
		int cwidth = glutBitmapLength  ( fontType, (unsigned char*)text ); 
		
		float wpos = viewport[2] /2.0f;
		wpos -= (float)cwidth / 2.0f;

		fwidth = wpos;
		glRasterPos3f (wpos,y,0.0f);
	} else {
		glRasterPos3f (x,y,0.0f);
	}




	for (i = 0; i < length; i++)
		glutBitmapCharacter (fontType, text[i]);
	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	glMatrixMode(GL_MODELVIEW);
	
	glPopAttrib();
	return fwidth ;
}

void	OpenGLDisplay::Shutdown	()
{
	glDeleteLists(m_iListBase,256);

	wglMakeCurrent(NULL,NULL);
	wglDeleteContext(hRC);
	ReleaseDC(m_hWnd,hDC);
	DestroyWindow(m_hWnd);
}

void	OpenGLDisplay::Resize ( int in_wWidth, int in_wHeight )
{
	SetWindowPos ( m_hWnd, NULL,0,0,in_wWidth, in_wHeight, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOREPOSITION |SWP_NOZORDER );
	wglMakeCurrent(hDC,hRC);

	glViewport(0,0,in_wWidth,in_wHeight);							

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();		

	m_fAspect = (float)(in_wWidth) / (float)(in_wHeight);
	gluPerspective(m_fFOV, m_fAspect, 1.0f, 2000.0);


	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();

}

void	OpenGLDisplay::BeginRender	()
{
	Up = GetAsyncKeyState( VK_UP );
	Down = GetAsyncKeyState( VK_DOWN );
	Left = GetAsyncKeyState( VK_LEFT );
	Right = GetAsyncKeyState( VK_RIGHT );
	Jump = GetAsyncKeyState( VK_SHIFT );

	CamUp = GetAsyncKeyState( VK_NUMPAD8 );
	CamDown= GetAsyncKeyState( VK_NUMPAD2 );
	CamLeft= GetAsyncKeyState( VK_NUMPAD4 );
	CamRight= GetAsyncKeyState( VK_NUMPAD6 );

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();		
	gluPerspective(m_fFOV, m_fAspect, 1.0f, 2000.0);
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
	
}

void	OpenGLDisplay::Render	()
{
	wglMakeCurrent(hDC,hRC);

	glClearStencil ( 0 );
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
}

void	OpenGLDisplay::EndRender ()
{
	SwapBuffers ( hDC );
}

void	OpenGLDisplay::GetMousePosition ( int *x, int *y )
{
	*x = mouseX;
	*y = mouseY;
}

void	OpenGLDisplay::SetMousePosition ( int x, int y )
{
	mouseX = x;
	mouseY = y;
}

int		OpenGLDisplay::RemoveTexture ( int ID  )
{
	//
	// check against the cache
	//
	
	for (int c=0;c<m_TextureCache.GetUsed();c++)
	{
		if ( m_TextureCache[c].m_iID == ID )
		{
			glDeleteTextures ( 1, (const unsigned int *)&m_TextureCache[c].m_iID );
			m_TextureCache[c].m_szName = "unloaded";
		}
	}
	
	return 0;
}

int	OpenGLDisplay::AddCubicTexture( CSIBCString in_szPath[6] )
{
	unsigned char* data = NULL;

	int bpp,width,height,components,format;

	GLuint gl_id = -1;
	glGenTextures( 1, &gl_id );

	
	glBindTexture(GL_TEXTURE_CUBE_MAP_ARB,gl_id);


	for (int a=0;a<6;a++)
	{
		char fname[MAX_PATH];
		char extension[MAX_PATH];
		
		_splitpath ( in_szPath[a].GetText(), NULL, NULL, fname, extension );
		sprintf ( fname, "%s%s", fname, extension );

		if ( strstr ( extension, "pic" ) || strstr ( extension, "PIC" ))
		{
			data = ReadPIC ( FixTexturePath(in_szPath[a].GetText()), width, height);
			components = 4;
			format = GL_RGBA;

		} else {



			//
			// Load the BMP file
			//

			BMPFILEHEADER bmfh;
			BMPINFOHEADER bmih;

			FILE *f;

			bool has_palette = false;
			bmp_palette_entry *palette;


			f = fopen ( FixTexturePath(fname), "rb" );

			if ( f == NULL )
				return 0;

			fread ( &bmfh.bfType , sizeof ( unsigned short ), 1, f );
			fread ( &bmfh.bfSize , sizeof ( ULONG ), 1, f );
			fread ( &bmfh.bfReserved1 , sizeof ( unsigned short ), 1, f );
			fread ( &bmfh.bfReserved2 , sizeof ( unsigned short ), 1, f );
			fread ( &bmfh.bfOffBits  , sizeof ( ULONG ), 1, f );

			 
			fread ( &bmih.biSize, sizeof ( ULONG ), 1, f );
			fread ( &bmih.biWidth, sizeof ( ULONG ), 1, f );
			fread ( &bmih.biHeight, sizeof ( ULONG ), 1, f );
			fread ( &bmih.biPlanes, sizeof ( unsigned short ), 1, f );
			fread ( &bmih.biBitCount, sizeof ( unsigned short ), 1, f );
			fread ( &bmih.biCompression, sizeof ( ULONG ), 1, f );
			fread ( &bmih.biSizeImage, sizeof ( ULONG ), 1, f );
			fread ( &bmih.biXPelsPerMeter, sizeof ( ULONG ), 1, f );
			fread ( &bmih.biYPelsPerMeter, sizeof ( ULONG ), 1, f );
			fread ( &bmih.biClrUsed, sizeof ( ULONG ), 1, f );
			fread ( &bmih.biClrImportant, sizeof ( ULONG ), 1, f );


			// Check filetype signature
			if (bmfh.bfType!='MB') 
			{
				fclose ( f );
				return 0;
			}
			

			bpp = bmih.biBitCount;
			width =bmih.biWidth;
			height = bmih.biHeight;
			
			int BytesPerRow = width * bpp / 8;
			BytesPerRow += (4-BytesPerRow%4) % 4;	// integer alignment

			if ( bpp != 24 )
			{
				if ( bpp != 8 )
				{
					fclose (f);
					return 0;
				}

				has_palette = true;
				int num_entries = 1 << bpp;

				palette = new bmp_palette_entry [ num_entries ];

				int g= sizeof (RGBQUAD);

				fread ( palette, sizeof (bmp_palette_entry), num_entries,f );
			
			}

			fseek ( f, bmfh.bfOffBits, SEEK_SET );

			data = new unsigned char [BytesPerRow*height];

			fread ( data, BytesPerRow*height,sizeof(unsigned char),f );
			
			if ( has_palette )
			{
				unsigned char *convert = new unsigned char [ width * height * 3 ];

				LONG p_index = 0;

				int num_pixels = BytesPerRow*height;

				for (int p=0;p<num_pixels;p++)
				{
					convert[p_index] = palette [ data[p] ].r;
					p_index++;

					convert[p_index] = palette [ data[p] ].g;
					p_index++;

					convert[p_index] = palette [ data[p] ].b;
					p_index++;

				}

				bpp = 24;
				
				delete [] data;
				delete [] palette;

				data = convert;

			} 
			
			LONG nb = (BytesPerRow*height) / 3;

			LONG index = 0;

			for ( LONG i=0;i<nb;i++)
			{
				char tmp = data[index];

				data[index] = data[index + 2];
				data[index+2] = tmp;
				index+=3;


			}

			components = 3;
			format = GL_RGB;
			fclose (f);
		}

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB + a, 0, components, width, height, 0, format, GL_UNSIGNED_BYTE, data);

		delete [] data;
	}

	return gl_id;

}
int		OpenGLDisplay::AddTexture ( TCHAR*	in_szPath, int ID  )
{

	unsigned char* data = NULL;

	int bpp,width,height,components,format;

	if ( in_szPath == NULL )
		return 0;

	if ( strlen ( in_szPath ) == 0 )
		return 0;

	char fname[MAX_PATH];
	char extension[MAX_PATH];

	_splitpath ( in_szPath, NULL, NULL, fname, extension );
	sprintf ( fname, "%s%s", fname, extension );


	//
	// check against the cache
	//

	if ( ID == -1 )
	{
		for (int c=0;c<m_TextureCache.GetUsed();c++)
		{
			if ( m_TextureCache[c].m_szName == fname )
			{
				return m_TextureCache[c].m_iID;
			}
		}
	}

	//
	// make sure our OpenGL is current since this can get called by Softimage
	// directly
	//

	wglMakeCurrent(hDC,hRC);

	if ( strstr ( extension, "pic" ) || strstr ( extension, "PIC" ))
	{
		data = ReadPIC ( FixTexturePath(fname), width, height);
		components = 4;
		format = GL_RGBA;

	} else {



		//
		// Load the BMP file
		//

		BMPFILEHEADER bmfh;
		BMPINFOHEADER bmih;

		FILE *f;

		bool has_palette = false;
		bmp_palette_entry *palette;


		f = fopen ( FixTexturePath(fname), "rb" );

		if ( f == NULL )
			return 0;

		fread ( &bmfh.bfType , sizeof ( unsigned short ), 1, f );
		fread ( &bmfh.bfSize , sizeof ( ULONG ), 1, f );
		fread ( &bmfh.bfReserved1 , sizeof ( unsigned short ), 1, f );
		fread ( &bmfh.bfReserved2 , sizeof ( unsigned short ), 1, f );
		fread ( &bmfh.bfOffBits  , sizeof ( ULONG ), 1, f );

		 
		fread ( &bmih.biSize, sizeof ( ULONG ), 1, f );
		fread ( &bmih.biWidth, sizeof ( ULONG ), 1, f );
		fread ( &bmih.biHeight, sizeof ( ULONG ), 1, f );
		fread ( &bmih.biPlanes, sizeof ( unsigned short ), 1, f );
		fread ( &bmih.biBitCount, sizeof ( unsigned short ), 1, f );
		fread ( &bmih.biCompression, sizeof ( ULONG ), 1, f );
		fread ( &bmih.biSizeImage, sizeof ( ULONG ), 1, f );
		fread ( &bmih.biXPelsPerMeter, sizeof ( ULONG ), 1, f );
		fread ( &bmih.biYPelsPerMeter, sizeof ( ULONG ), 1, f );
		fread ( &bmih.biClrUsed, sizeof ( ULONG ), 1, f );
		fread ( &bmih.biClrImportant, sizeof ( ULONG ), 1, f );


		// Check filetype signature
		if (bmfh.bfType!='MB') 
		{
			fclose ( f );
			return 0;
		}
		

		bpp = bmih.biBitCount;
		width =bmih.biWidth;
		height = bmih.biHeight;
		
		int BytesPerRow = width * bpp / 8;
		BytesPerRow += (4-BytesPerRow%4) % 4;	// integer alignment

		if ( bpp != 24 )
		{
			if ( bpp != 8 )
			{
				fclose (f);
				return 0;
			}

			has_palette = true;
			int num_entries = 1 << bpp;

			palette = new bmp_palette_entry [ num_entries ];

			int g= sizeof (RGBQUAD);

			fread ( palette, sizeof (bmp_palette_entry), num_entries,f );
		
		}

		fseek ( f, bmfh.bfOffBits, SEEK_SET );

		data = new unsigned char [BytesPerRow*height];

		fread ( data, BytesPerRow*height,sizeof(unsigned char),f );
		
		if ( has_palette )
		{
			unsigned char *convert = new unsigned char [ width * height * 3 ];

			LONG p_index = 0;

			int num_pixels = BytesPerRow*height;

			for (int p=0;p<num_pixels;p++)
			{
				convert[p_index] = palette [ data[p] ].r;
				p_index++;

				convert[p_index] = palette [ data[p] ].g;
				p_index++;

				convert[p_index] = palette [ data[p] ].b;
				p_index++;

			}

			bpp = 24;
			
			delete [] data;
			delete [] palette;

			data = convert;

		} 
		
		LONG nb = (BytesPerRow*height) / 3;

		LONG index = 0;

		for ( LONG i=0;i<nb;i++)
		{
			char tmp = data[index];

			data[index] = data[index + 2];
			data[index+2] = tmp;
			index+=3;


		}

		components = 3;
		format = GL_RGB;
		fclose (f);
	}

	


	GLuint gl_id = ID;

	if ( ID == -1 )
	{
		glGenTextures( 1, &gl_id );
	}
	glBindTexture( GL_TEXTURE_2D, gl_id );

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 

	glTexImage2D( GL_TEXTURE_2D, 
						0, 
						components, 
						width,
						height,
						0,
						format,
						GL_UNSIGNED_BYTE,
						data);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 
							components, 
							width,
							height, 
							format, 
							GL_UNSIGNED_BYTE, 
							(const void *)data);
	

	delete [] data;

	m_TextureCache.Extend(1);
	m_TextureCache[m_TextureCache.GetUsed()-1].m_szName = fname;
	m_TextureCache[m_TextureCache.GetUsed()-1].m_iID = gl_id;
	m_TextureCache[m_TextureCache.GetUsed()-1].m_lastModified = GetFileLastWriteAccess( FixTexturePath(fname));

	return gl_id;
}

int		OpenGLDisplay::AddTexture ( TCHAR*	in_szPath, LONG modulation )
{

	return AddTexture ( in_szPath, -1 );
}


void	OpenGLDisplay::CheckForTextureChanges()
{
	for (int t=0;t<m_TextureCache.GetUsed();t++)
	{
		WIN32_FILE_ATTRIBUTE_DATA	l_fileAttribut;

		if ( GetFileAttributesEx(FixTexturePath(m_TextureCache[t].m_szName.GetText()), GetFileExInfoStandard , &l_fileAttribut) == TRUE)
		{
			if ( CompareFileTime ( &l_fileAttribut.ftLastWriteTime, &m_TextureCache[t].m_lastModified ) != 0 )
			{
				//
				// This texture has changed
				//
				AddTexture ( m_TextureCache[t].m_szName.GetText(), m_TextureCache[t].m_iID );

			}

		}

	}

}

void	OpenGLDisplay::MultiTexCoord ( int in_iStage, float u, float v )
{
	glMultiTexCoord2f ( in_iStage, u, v );
}

LRESULT CALLBACK	_view_proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	OpenGLDisplay	* l_pDisplay = (OpenGLDisplay*)GetWindowLong ( hDlg, GWL_USERDATA );

	switch (message)
	{
		case WM_TIMER:
		{
			l_pDisplay->CheckForTextureChanges();
			break;
		}

	
		case WM_INITDIALOG:
			{
			
				return TRUE;
			}

		case WM_MOUSEMOVE:
			{
				if ( l_pDisplay )
				{
					l_pDisplay->SetMousePosition (LOWORD(lParam),HIWORD(lParam) );
				}
				break;
			}

		case WM_LBUTTONUP:
			{
				if ( l_pDisplay )
				{
					l_pDisplay->leftButtonClicked = 1;
				}
				break;
			}
		case WM_RBUTTONUP:
			{
				if ( l_pDisplay )
				{
					l_pDisplay->rightButtonClicked = 1;
				}
				break;
			}
			
	}

    return DefWindowProc(hDlg,message,wParam,lParam);
}


FILETIME GetFileLastWriteAccess( TCHAR *in_csFilePath )
{

	WIN32_FILE_ATTRIBUTE_DATA	l_fileAttribut;
	
	if ( GetFileAttributesEx(in_csFilePath, GetFileExInfoStandard , &l_fileAttribut) == TRUE)
	{
		return l_fileAttribut.ftLastWriteTime;
	}
	else
	{
		return FILETIME();
	}
}