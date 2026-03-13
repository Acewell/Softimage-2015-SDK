#pragma once
#include "Engine.h"
#include <Scene.h>
#include <XSIShader.h>
#include <XSIMaterial.h>
#include <MaterialLibrary.h>
#include "Shader.h"
//
// Shader handlers
//

#include "Shader.h"
#include "TextureShader.h"
#include "CubicTextureShader.h"
//#include "CgProgramShader.h"
#include "TexCoordShader.h"

typedef struct tagGameShader
{
	tagGameShader() {};
	~tagGameShader()
	{
		for (int i=0;i<m_pShaderNodes.GetUsed();i++)
		{
			delete m_pShaderNodes[i];
		}
		m_pShaderNodes.DisposeData();
	}

	char						m_szName[MAX_PATH];
	CSIBCArray<Shader*>			m_pShaderNodes;
} GameShader;

class ENGINE_API MaterialSystem
{
public:
	MaterialSystem(void);
	virtual ~MaterialSystem(void);

	void		SetDisplay ( Display* in_pDisplay );

	GameShader*	AddMaterial ( CSLXSIMaterial* in_pMaterial);
	void		AddMaterialLibrary ( char* in_szMatlibName );

	int		ExecuteShader ( GameShader* );
	void	ShutdownShader ( GameShader* );
	void	Purge();
	GameShader*		FindShader ( char *in_szShaderName );


private:

	CSIBCArray<CSLScene*>		m_pMatLibs;
	CSIBCArray<GameShader*>		m_pShaderList;
	CSIBCArray<ShaderPlugin*>	m_pShaderPlugins;
	Display* m_pDisplay;

};

MaterialSystem* GetMaterialSystem();
void			ShutdownMaterialSystem();
