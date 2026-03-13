// Game.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <OpenGLDisplay.h>
#include <GameState.h>
#include <DiskGameFlow.h>
#include <LevelParser.h>

//
// local functions
//

HWND	CreateMainWindow (HINSTANCE in_hInstance, int x, int y);

LRESULT CALLBACK WndProc(	HWND	hWnd,						
							UINT	uMsg,						
							WPARAM	wParam,						
							LPARAM	lParam);


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	MSG		msg;												
	BOOL	UserWantsToQuit=FALSE;
	DWORD	lasttickCount;
	CSIBCArray<Level*>	m_pLevels;

	static int l_iFramesRendered = 0;
	static float l_fAverageFPS = 0;

	//
	// First create the main window. This window will
	// hold the display
	//

	HWND l_hMainWnd = CreateMainWindow(hInstance, 640,480);


	//
	// Create an OpenGL display
	//
	
	Display	* m_pDisplay = (OpenGLDisplay*) (new OpenGLDisplay());

	//
	// Initialize the display
	//

	m_pDisplay->Initialize ( hInstance, l_hMainWnd, WS_CHILD, 0, NULL );
	SetWindowLong ( l_hMainWnd, GWL_USERDATA, (LONG)m_pDisplay);

	//
	// Get the global GameState object
	//

	GameState* l_pGameState = GetGameState ( m_pDisplay );

	//
	// now create a new welcome screen object to use 
	// the display we have just created
	//

	LevelLoader* loader;
	loader = new LevelLoader ( m_pDisplay );

	if (loader->m_Levels.GetUsed() ==0)
	{
		MessageBox( 0,"No level available", "", MB_OK);
		return -1;
	}

	m_pLevels.Extend ( loader->m_Levels.GetUsed() + 1 );



	m_pLevels[0] = new DiskGameFlow ( m_pDisplay );

	for (int c=1;c<loader->m_Levels.GetUsed()+1;c++)
	{
		m_pLevels[c] = loader->m_Levels[c-1];
	}



	//
	// Enter a standard Windows loop that dispatches messages
	// and runs the game when no messages are pending.
	//

	lasttickCount = GetTickCount ();
	DWORD tickCount;
	int	l_iCurrentLevel = 0;

	while(!UserWantsToQuit)												
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))				
		{
			if (msg.message==WM_QUIT)
			{
				UserWantsToQuit=TRUE;
			}
			else												
			{
				TranslateMessage(&msg);	
				DispatchMessage(&msg);
			}
		}
		else													
		{
			tickCount = GetTickCount ();
			
			m_pDisplay->BeginRender ();
			m_pDisplay->Render ();
			if ( !m_pLevels[l_iCurrentLevel]->IsInitialized () )
			{
				m_pLevels[l_iCurrentLevel]->Initialize ();
			}

			if ( ( tickCount - lasttickCount) > 2000 )
			{
				lasttickCount = tickCount;
			}

			
			int result = m_pLevels[l_iCurrentLevel]->Render ( tickCount - lasttickCount );

			m_pDisplay->EndRender ();

			l_iFramesRendered++;
			l_fAverageFPS += ( 1.0f / ( (tickCount - lasttickCount) / 1000.0f));

			if ( l_iFramesRendered == 10 )
			{
				l_pGameState->SetFPS(l_fAverageFPS/10.0f);
				l_fAverageFPS = 0;
				l_iFramesRendered = 0;

			}

			lasttickCount = tickCount;

			if ( !result )
			{
				//
				// unload level
				//
				m_pLevels[l_iCurrentLevel]->Unload();

				//
				// reset game state
				l_pGameState->ResetForNextLevel();

				// increment levels
				//
				l_iCurrentLevel++;

				if ( l_iCurrentLevel == m_pLevels.GetUsed() )
				{
					l_iCurrentLevel = 0;
				}

			}

		}
	}

	KillGameState();

	m_pDisplay->Shutdown ();
	delete m_pDisplay;

	return 0;
}

HWND	CreateMainWindow (HINSTANCE in_hInstance, int x, int y)
{
	HWND		hWnd;
	WNDCLASS	wc;												
	DWORD		dwExStyle;										
	DWORD		dwStyle;										
	RECT		WindowRect;										
	WindowRect.left=(LONG)0;									
	WindowRect.right=(LONG)x;								
	WindowRect.top=(LONG)0;										
	WindowRect.bottom=(LONG)y;

	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	
	wc.lpfnWndProc		= (WNDPROC) WndProc;					
	wc.cbClsExtra		= 0;									
	wc.cbWndExtra		= 0;									
	wc.hInstance		= in_hInstance;
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			
	wc.hbrBackground	= NULL;									
	wc.lpszMenuName		= NULL;									
	wc.lpszClassName	= "XSIgame";								

	RegisterClass(&wc);	// dont care if it fails.
	
	dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			
	dwStyle=WS_OVERLAPPEDWINDOW;							

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);	

	
	if (!(hWnd=CreateWindowEx(	dwExStyle,
								"SoftimageGame",
								"Softimage Game Demo - StandAlone Version",
								dwStyle |						
								WS_CLIPSIBLINGS |				
								WS_CLIPCHILDREN,				
								0, 0,							
								WindowRect.right-WindowRect.left,	
								WindowRect.bottom-WindowRect.top,	
								NULL,							
								NULL,							
								in_hInstance,
								NULL)))							
	{
		return NULL;
	}

	ShowWindow ( hWnd, SW_SHOWNORMAL );
	UpdateWindow ( hWnd );
	return hWnd;

}


LRESULT CALLBACK WndProc(	HWND	hWnd,						
							UINT	uMsg,						
							WPARAM	wParam,						
							LPARAM	lParam)						
{
	Display	* l_pDisplay = (Display*)GetWindowLong ( hWnd, GWL_USERDATA );

	switch (uMsg)												
	{

		case WM_CLOSE:											
		{
			PostQuitMessage(0);									
			return 0;											
		}

		case WM_MOUSEMOVE:
			{
				int a = 10;
				break;
			}


		case WM_SIZE:
		{
			if ( l_pDisplay )
			{
				RECT r;
				GetClientRect ( hWnd, &r );
				l_pDisplay->Resize (r.right, r.bottom);
			}
		}

	
	}

	return DefWindowProc(hWnd,uMsg,wParam,lParam);				
}