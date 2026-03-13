// Shader.cpp: implementation of the Shader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Shader.h"

PFNGLACTIVETEXTUREPROC glActiveTextureARB;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Shader::Shader(CSLXSIShader* in_pShader, Display* in_pDisplay )
{
	glActiveTextureARB		= (PFNGLACTIVETEXTUREPROC)::wglGetProcAddress( "glActiveTextureARB" );
	m_pShader = in_pShader;
}

Shader::~Shader()
{

}
