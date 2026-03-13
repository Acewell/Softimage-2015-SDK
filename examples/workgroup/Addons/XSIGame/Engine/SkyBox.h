#pragma once

#include "Engine.h"
#include "Display.h"
class ENGINE_API SkyBox
{
public:
	SkyBox(Display* in_pDisplay);
	virtual ~SkyBox(void);

	void	load ( char* in_szSkyBoxName );
	void	render ();

private:
	
	int			m_iSkyBoxTextures[6];
	Display*	m_pDisplay;
};
