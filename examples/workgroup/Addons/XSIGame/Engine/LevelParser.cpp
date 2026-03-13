// LevelParser.cpp: implementation of the LevelParser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LevelParser.h"
#include "OpenGLDisplay.h"
#include <io.h>

extern char g_szStaticString[MAX_PATH];
char* FixLevelPath (char* in_szString)
{
	SetCurrentDirectory(OpenGLDisplay::m_szRootPath);
	memset ( g_szStaticString,0,MAX_PATH );
	sprintf ( g_szStaticString, "%s\\data\\levels\\%s", OpenGLDisplay::m_szRootPath, in_szString );
	return g_szStaticString;
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LevelParser::LevelParser()
{
	m_iNumEnemies = 1;
	strcpy ( m_SkyTexture1, "orangesky.bmp");
	strcpy ( m_SkyTexture2, "overcast.bmp");
	m_fFogColor[0] = 0.4f;
	m_fFogColor[1] = 0.6f;
	m_fFogColor[2] = 0.9f;
	m_fFogColor[3] = 1.0f;
	m_fFogDistance = 200.0f;
	m_ShaderName[0] = 0;
}

LevelParser::~LevelParser()
{

}

bool	LevelParser::Parse ( char* in_szFilename )
{
	if ( !strlen(in_szFilename) )
		return false;
	
	FILE* l_fptr = fopen ( FixLevelPath(in_szFilename), "rb" );

	if ( !l_fptr )
		return false;

	fseek(l_fptr, 0, SEEK_END );
	LONG fl = ftell ( l_fptr );
	fseek (l_fptr, 0,SEEK_SET);
	
	char *buffer = new char [fl + 5];

	fread (buffer,fl,sizeof(char),l_fptr);

	buffer[fl] = 'E';
	buffer[fl+1] = 'N';
	buffer[fl+2] = 'D';
	buffer[fl+3] = 0;

	fclose( l_fptr );

	char seps[] = " \t\n\r ";

	char *token = strtok (buffer, seps);

	while ( strcmp( token, "END" ) )
	{ 
		if ( !strcmp ( token, "level" ) )
		{
			token = strtok (NULL, seps);
			memset ( m_LevelFile, 0, MAX_PATH);
			strcpy ( m_LevelFile, token );

		}

		if ( !strcmp ( token, "asset" ) )
		{
			token = strtok (NULL, seps);

			m_Assets.Extend(1);
			m_Assets[m_Assets.GetUsed()-1] = new CSIBCString ( token );
		}

		if ( !strcmp ( token, "enemies" ) )
		{
			token = strtok (NULL, seps);

			m_iNumEnemies = atoi(token);
		}

		if ( !strcmp ( token, "skytexture1" ) )
		{
			token = strtok (NULL, seps);
			strcpy ( m_SkyTexture1, token );

		}
		if ( !strcmp ( token, "skytexture2" ) )
		{
			token = strtok (NULL, seps);
			strcpy ( m_SkyTexture2, token );
		}
		if ( !strcmp ( token, "fogcolor.red" ) )
		{
			token = strtok (NULL, seps);
			m_fFogColor[0] = atof ( token );
		}
		if ( !strcmp ( token, "fogcolor.green" ) )
		{
			token = strtok (NULL, seps);
			m_fFogColor[1] = atof ( token );
		}
		if ( !strcmp ( token, "fogcolor.blue" ) )
		{
			token = strtok (NULL, seps);
			m_fFogColor[2] = atof ( token );
		}
		if ( !strcmp ( token, "fogdistance" ) )
		{
			token = strtok (NULL, seps);
			m_fFogDistance = atof ( token );
		}
		if ( !strcmp ( token, "shader" ) )
		{
			token = strtok (NULL, seps);
			strcpy ( m_ShaderName, token );
		}

		token = strtok (NULL, seps);
	
	}

	delete [] buffer;

	return true;
}

LevelLoader::LevelLoader(Display* in_pDisplay)
{
	LONG	handle;
	int		done;
	
	_finddata_t fileinfo;
	memset(&fileinfo, 0, sizeof(_finddata_t));

	handle = _findfirst(FixLevelPath("*.xgl"), &fileinfo);

	if (handle>=0)
	{
		done = 0;
		while (!done)
		{
		
			LevelParser	parser;
			parser.Parse ( fileinfo.name );

			m_Levels.Extend(1);
			m_Levels[m_Levels.GetUsed()-1] = new Level ( in_pDisplay );

			Level* l_pNewLevel = m_Levels[m_Levels.GetUsed()-1];

			l_pNewLevel->SetAssets ( &parser.m_Assets );
			l_pNewLevel->SetLevelFilename ( parser.m_LevelFile );
			l_pNewLevel->m_iNumEnemies = parser.m_iNumEnemies;
			strcpy ( l_pNewLevel->m_SkyTexture1, parser.m_SkyTexture1 );
			strcpy ( l_pNewLevel->m_SkyTexture2, parser.m_SkyTexture2 );
			strcpy ( l_pNewLevel->m_ShaderName, parser.m_ShaderName );
			
			for (int c=0;c<4;c++) l_pNewLevel->m_fFogColor[c] = parser.m_fFogColor[c];
			l_pNewLevel->m_fFogDistance = parser.m_fFogDistance;


			done = _findnext(handle, &fileinfo);
		}


	}

}

LevelLoader::~LevelLoader()
{
	for (int i=0;i<m_Levels.GetUsed();i++)
	{
		delete m_Levels[i];
	}

	m_Levels.DisposeData();

}
