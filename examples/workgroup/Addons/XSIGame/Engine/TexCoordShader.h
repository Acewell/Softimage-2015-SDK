#pragma once
#include "Engine.h"
#include "Shader.h"
#include <VariantParameter.h>



class ENGINE_API TexCoordShader :
	public Shader
{
public:
	TexCoordShader(CSLXSIShader* in_pShader, Display* in_pDisplay );
	virtual ~TexCoordShader(void);

	virtual void execute ();
	virtual void enable ( bool );

	int	m_iUVType;
	int	m_iNbComponents;
	int uwrap;
	int vwrap;
	int wwrap;
	int Transform;
	CSLVariantParameter* trsx;
	CSLVariantParameter* trsy;
	CSLVariantParameter* trsz;
	CSLVariantParameter* rotx;
	CSLVariantParameter* roty;
	CSLVariantParameter* rotz;
	CSLVariantParameter* sclx;
	CSLVariantParameter* scly;
	CSLVariantParameter* sclz;


};
