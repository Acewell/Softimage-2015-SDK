// TextureShader.cpp: implementation of the TextureShader class.
//
//////////////////////////////////////////////////////////////////////


#include "TextureShader.h"
#include <Scene.h>
#include <ConnectionPoint.h>
#include <ShaderConnectionPoint.h>
#include <XSIImageLibrary.h>
#include <XSIImage.h>
#include <VariantParameter.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
int	TextureShader::m_iTextureStage = 0;


TextureShader::TextureShader(CSLXSIShader* in_pShader, Display* in_pDisplay ) : Shader ( in_pShader,in_pDisplay  )
{
	
	//
	// find the connection index to the image
	//

	int l_iIndex = 0;

	while ( in_pShader->GetConnectionPointList ()[l_iIndex]->GetImage () == NULL )
	{
		l_iIndex++;
	}

	
	CSLImage * l_pImage = in_pShader->Scene ()->GetImageLibrary ()->FindImage ( in_pShader->GetConnectionPointList ()[l_iIndex]->GetImage () );

	m_iTextureObject = in_pDisplay->AddTexture ( l_pImage->GetSourceFile () );

	m_iTextureTarget = in_pShader->GetParameterList()[1]->GetValue ()->lVal;

	m_iModulation = in_pShader->GetParameterList()[11]->GetValue ()->lVal;
}

TextureShader::~TextureShader()
{

}
int	 TextureShader::UVstages()
{
	return 1;
}
void TextureShader::execute ()
{	
	glActiveTextureARB ( GL_TEXTURE0_ARB + m_iTextureTarget );
	glEnable ( GL_TEXTURE_2D );
	glBindTexture ( GL_TEXTURE_2D, m_iTextureObject );

	switch(m_iModulation)
	{
		case	0: 	glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
					break;
		case	1: 	glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL );
					break;
		case	2: 	glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND );
					break;
		case	3: 	glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
					break;
	}

	m_iTextureStage++;

}

void TextureShader::enable ( bool in_bEnable )
{
	glActiveTextureARB ( GL_TEXTURE0_ARB + m_iTextureTarget );
	glBindTexture ( GL_TEXTURE_2D, NULL );
	glActiveTextureARB ( GL_TEXTURE0_ARB );
	m_iTextureStage = 0;
}