// TextureShader.h: interface for the TextureShader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTURESHADER_H__BFF7DE4B_0FA6_4F24_8231_5691A298CF74__INCLUDED_)
#define AFX_TEXTURESHADER_H__BFF7DE4B_0FA6_4F24_8231_5691A298CF74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shader.h"
#include "Engine.h"



class ENGINE_API TextureShader : public Shader  
{
public:
	TextureShader(CSLXSIShader* in_pShader, Display* in_pDisplay );
	virtual ~TextureShader();

	virtual void execute ();
	virtual void enable ( bool );
	virtual int	 UVstages();

private:

	Display*	m_pDisplay;
	int			m_iTextureObject;
	int			m_iTextureTarget;
	static	int	m_iTextureStage;
	int			m_iModulation;

};

#endif // !defined(AFX_TEXTURESHADER_H__BFF7DE4B_0FA6_4F24_8231_5691A298CF74__INCLUDED_)
