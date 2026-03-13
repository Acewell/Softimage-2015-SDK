// LevelParser.h: interface for the LevelParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEVELPARSER_H__7A79DFBB_5911_4831_8960_45DD86021FF8__INCLUDED_)
#define AFX_LEVELPARSER_H__7A79DFBB_5911_4831_8960_45DD86021FF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "engine.h"
#include "level.h"
#include "display.h"
#include <stdio.h>
#include <string.h>
#include <SIBCArray.h>
#include <SIBCString.h>

ENGINE_API char* FixLevelPath (char* in_szString);

class ENGINE_API LevelParser  
{
public:
	LevelParser();
	virtual ~LevelParser();

	bool	Parse ( char * in_szFilename );

	char					m_LevelFile[MAX_PATH];
	CSIBCArray<CSIBCString*>	m_Assets;
	int						m_iNumEnemies;
	char					m_SkyTexture1[MAX_PATH];
	char					m_SkyTexture2[MAX_PATH];
	float					m_fFogColor[4];
	float					m_fFogDistance;
	char					m_ShaderName[MAX_PATH];
};

class ENGINE_API LevelLoader  
{
public:
	LevelLoader(Display* in_pDisplay);
	virtual ~LevelLoader();

	CSIBCArray<Level*>	m_Levels;
};

#endif // !defined(AFX_LEVELPARSER_H__7A79DFBB_5911_4831_8960_45DD86021FF8__INCLUDED_)
