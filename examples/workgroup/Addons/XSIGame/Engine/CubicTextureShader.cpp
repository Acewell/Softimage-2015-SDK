// CubicTextureShader.cpp: implementation of the CubicTextureShader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CubicTextureShader.h"
#include <Scene.h>
#include <ConnectionPoint.h>
#include <ShaderConnectionPoint.h>
#include <XSIImageLibrary.h>
#include <XSIImage.h>
#include <VariantParameter.h>

#include "OpenGLDisplay.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CubicTextureShader::CubicTextureShader(CSLXSIShader* in_pShader, Display* in_pDisplay ) : Shader ( in_pShader,in_pDisplay  )
{

	CSLImage * l_pImages[6];
	CSIBCString l_szPaths[6];
	for (int i=0;i<6;i++)
	{
		l_pImages[i] = in_pShader->Scene ()->GetImageLibrary ()->FindImage ( in_pShader->GetConnectionPointList ()[i+1]->GetImage () );
		
		l_szPaths[i] = l_pImages[i]->GetSourceFile ();
	}

	m_iTextureObject = in_pDisplay->AddCubicTexture ( l_szPaths );

	m_iTextureTarget = in_pShader->GetParameterList()[1]->GetValue ()->lVal;

}

CubicTextureShader::~CubicTextureShader()
{

}

void CubicTextureShader::execute ()
{
	glActiveTextureARB ( GL_TEXTURE0_ARB + m_iTextureTarget );
	glDisable ( GL_TEXTURE_2D );
	glEnable ( GL_TEXTURE_CUBE_MAP_ARB );
	glBindTexture ( GL_TEXTURE_CUBE_MAP_ARB, m_iTextureObject );


}

void CubicTextureShader::enable ( bool in_bEnable )
{
	glActiveTextureARB ( GL_TEXTURE0_ARB + m_iTextureTarget );
	glBindTexture ( GL_TEXTURE_CUBE_MAP_ARB, NULL );
	glActiveTextureARB ( GL_TEXTURE0_ARB );
	
}

