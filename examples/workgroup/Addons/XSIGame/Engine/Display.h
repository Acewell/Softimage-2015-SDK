// Display.h: interface for the Display class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISPLAY_H__86E9A983_EC88_40FF_8191_1E906D19AADE__INCLUDED_)
#define AFX_DISPLAY_H__86E9A983_EC88_40FF_8191_1E906D19AADE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include "engine.h"
#include <SIBCString.h>

#define FONT_CENTERED		1 << 1
#define FONT_BIG			1 << 2

// ripped from MS so it works on other plateforms
typedef struct BMPFILEHEADER_t { 
  unsigned short    bfType; 
  ULONG		bfSize; 
  unsigned short    bfReserved1; 
  unsigned short    bfReserved2; 
  ULONG		bfOffBits; 
 
} BMPFILEHEADER;


typedef struct BMPINFOHEADER_t {    
    ULONG  biSize;          // size of structure, in bytes
    ULONG  biWidth;         // bitmap width, in pixels
    ULONG  biHeight;        // bitmap height, in pixels
    unsigned short   biPlanes;        // see below
    unsigned short   biBitCount;      // see below
    ULONG  biCompression;   // see below
    ULONG  biSizeImage;     // see below
    ULONG  biXPelsPerMeter; // see below
    ULONG  biYPelsPerMeter; // see below
    ULONG  biClrUsed;       // see below
    ULONG  biClrImportant;  // see below
} BMPINFOHEADER;

typedef struct bmp_palette_entry_t
{
	char r;
	char g;
	char b;
	char a;

} bmp_palette_entry;

class ENGINE_API Display  
{
public:
	Display();
	virtual ~Display();

	virtual void	Initialize	( HINSTANCE in_hInstance, HWND in_hParent, DWORD in_dwStyle, DWORD in_dwExtendedStyle, void* in_pUserData ) {};
	virtual void	Shutdown	() {};
	virtual void	Resize ( int in_wWidth, int in_wHeight ) {};
	virtual HWND	GetWindow() { return NULL; };

	virtual	void	BeginRender	() {};
	virtual	void	Render	() {};
	virtual void	EndRender () {};

	virtual int		AddTexture ( TCHAR*	in_szPath, int ID = -1 ) { return 0; } ;
	virtual int		AddTexture ( TCHAR*	in_szPath, LONG modulation ) { return 0; } ;
	virtual int		RemoveTexture ( int ID ) { return 0; } ;
	virtual int		AddCubicTexture( CSIBCString in_szPath[6]   ) {return 0;};
	virtual void	GetMousePosition ( int *x, int *y ) {};
	virtual void	SetMousePosition ( int x, int y ) {};
	virtual	void	GetButtonsStates ( int *left, int *right ) {*left = leftButtonClicked; leftButtonClicked = 0; *right =rightButtonClicked; rightButtonClicked = 0;};

	virtual	int		Print (int x, int y, LONG flags, TCHAR* in_szString, ...) { return 0;};
	virtual float	GetFOV () { return m_fFOV; };
	virtual void	SetFOV (float in_fFOV);
	virtual unsigned char*	ReadPIC ( char* in_szFilename, int &width, int& height );
	virtual void	AutomaticTextureReload ( bool in_Value ) { m_bAutomaticTextureReload = in_Value; };
	virtual void	MultiTexCoord ( int in_iStage, float u, float v ) {} ;
	virtual void	Tick(float milliseconds);

	int		leftButtonClicked;
	int		rightButtonClicked;
	int				Up;
	int				Down;
	int				Left;
	int				Right;
	int				Jump;

	int				CamUp;
	int				CamDown;
	int				CamLeft;
	int				CamRight;

protected:

	float	m_fTOFOV;
	float	m_fFOV;
	int		mouseX;
	int		mouseY;
	bool	m_bAutomaticTextureReload;
};

#endif // !defined(AFX_DISPLAY_H__86E9A983_EC88_40FF_8191_1E906D19AADE__INCLUDED_)
