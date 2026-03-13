// CubicTextureShader.h: interface for the CubicTextureShader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUBICTEXTURESHADER_H__CB7BE8CA_59D7_4AA2_9606_0A14AD958154__INCLUDED_)
#define AFX_CUBICTEXTURESHADER_H__CB7BE8CA_59D7_4AA2_9606_0A14AD958154__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Engine.h"
#include "Shader.h"


class ENGINE_API CubicTextureShader  : public Shader
{
public:
	CubicTextureShader(CSLXSIShader* in_pShader, Display* in_pDisplay );
	virtual ~CubicTextureShader();

	virtual void execute ();
	virtual void enable ( bool );

private:
	int	m_iTextureObject;
	int m_iTextureTarget;
};

#endif // !defined(AFX_CUBICTEXTURESHADER_H__CB7BE8CA_59D7_4AA2_9606_0A14AD958154__INCLUDED_)
