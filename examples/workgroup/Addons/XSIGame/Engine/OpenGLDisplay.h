// OpenGLDisplay.h: interface for the OpenGLDisplay class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPENGLDISPLAY_H__FFA97099_9423_4FE8_A5FA_5E109B8C8363__INCLUDED_)
#define AFX_OPENGLDISPLAY_H__FFA97099_9423_4FE8_A5FA_5E109B8C8363__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <gl/gl.h>
#include "Display.h"
#include "SIBCArray.h"
#include "SIBCString.h"

typedef struct tagTextureCache
{
	CSIBCString m_szName;
	int			m_iID;
	FILETIME	m_lastModified;
} TextureCache;

#define GL_NORMAL_MAP_ARB                 0x8511
#define GL_REFLECTION_MAP_ARB             0x8512
#define GL_TEXTURE_CUBE_MAP_ARB           0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP_ARB   0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB 0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB 0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB 0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB 0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB 0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB 0x851A
#define GL_PROXY_TEXTURE_CUBE_MAP_ARB     0x851B
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE_ARB  0x851C

typedef void (APIENTRY * PFNGLMULTITEXCOORD2FPROC) (GLenum target, GLfloat s, GLfloat t);

class ENGINE_API OpenGLDisplay : public Display  
{
public:
	OpenGLDisplay();
	virtual ~OpenGLDisplay();

	virtual void	Initialize	( HINSTANCE in_hInstance, HWND in_hParent, DWORD in_dwStyle, DWORD in_dwExtendedStyle, void* in_pUserData );
	virtual void	Shutdown	();
	virtual void	Resize ( int in_wWidth, int in_wHeight );
	virtual HWND	GetWindow() { return m_hWnd; };

	virtual	void	BeginRender	();
	virtual	void	Render	();
	virtual void	EndRender ();

	virtual int		AddTexture ( TCHAR*	in_szPath , int ID = -1);
	virtual int		AddTexture ( TCHAR*	in_szPath, LONG modulation );

	virtual int		RemoveTexture ( int ID  );
	virtual int		AddCubicTexture( CSIBCString in_szPath[6] );

	virtual void	GetMousePosition ( int *x, int *y );
	virtual void	SetMousePosition ( int x, int y );

	virtual	int		Print (int x, int y, LONG flags, TCHAR* in_szString, ...);
	virtual void	CheckForTextureChanges();
	virtual void	MultiTexCoord ( int in_iStage, float u, float v );

	static char		m_szRootPath[MAX_PATH];

protected:

	HWND	m_hWnd;
	HDC		hDC;
	HGLRC	hRC;
	float	m_fAspect;

	GLuint	m_iFontTexture;
	GLuint	m_iListBase;

	CSIBCArray<TextureCache>	m_TextureCache;

	PFNGLMULTITEXCOORD2FPROC											glMultiTexCoord2f;

	

};

#endif // !defined(AFX_OPENGLDISPLAY_H__FFA97099_9423_4FE8_A5FA_5E109B8C8363__INCLUDED_)
