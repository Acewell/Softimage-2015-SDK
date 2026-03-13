#include "MaterialSystem.h"
#include "OpenGLDisplay.h"

MaterialSystem* g_pMaterialSystem = NULL;

MaterialSystem* GetMaterialSystem()
{
	if ( g_pMaterialSystem == NULL )
	{
		g_pMaterialSystem = new MaterialSystem();
	}

	return g_pMaterialSystem;
}

void			ShutdownMaterialSystem()
{

	if ( g_pMaterialSystem != NULL )
	{
		delete g_pMaterialSystem;
		g_pMaterialSystem = NULL;
	}
}


MaterialSystem::MaterialSystem(void)
{


	

}

MaterialSystem::~MaterialSystem(void)
{
	Purge();
}

GameShader*	MaterialSystem::AddMaterial ( CSLXSIMaterial* in_pMaterial )
{
	int l_nCount = in_pMaterial->GetShaderCount();
	CSLXSIShader **l_ppShaders = in_pMaterial->GetShaderList();

	GameShader* l_pGameShader = new GameShader;

	strcpy ( l_pGameShader->m_szName , in_pMaterial->Name().GetText());
	for (int s=l_nCount-1;s>=0;s--)
	{
		if ( !strcmp ( l_ppShaders[s]->GetProgID (), "Softimage.OGL13Texture.1"))
		{
			TextureShader* l_pShader = new TextureShader ( l_ppShaders[s], m_pDisplay );
			l_pGameShader->m_pShaderNodes.Add ( l_pShader );
		}

		if ( !strcmp ( l_ppShaders[s]->GetProgID (), "Softimage.OGL13CubicTexture.1"))
		{
			CubicTextureShader* l_pShader = new CubicTextureShader ( l_ppShaders[s], m_pDisplay );
			l_pGameShader->m_pShaderNodes.Add ( l_pShader );
		}

		/*if ( !strcmp ( l_ppShaders[s]->GetProgID (), "Softimage.CgProgram.1"))
		{
			CgProgramShader* l_pShader = new CgProgramShader ( l_ppShaders[s], m_pDisplay );
			l_pGameShader->m_pShaderNodes.Add ( l_pShader );
		}*/

		if ( !strcmp ( l_ppShaders[s]->GetProgID (), "Softimage.OGL13TexCoord.1"))
		{
			TexCoordShader* l_pShader = new TexCoordShader ( l_ppShaders[s], m_pDisplay );
			l_pGameShader->m_pShaderNodes.Add ( l_pShader );
		}

		//
		// check the plugins!
		//

		for (int p=0;p<m_pShaderPlugins.GetUsed();p++)
		{
			if ( !strcmp ( l_ppShaders[s]->GetProgID (), m_pShaderPlugins[p]->GetProgID()))
			{
				//
				// we found a plugin to handle this shader!
				//

				Shader* l_pHandler = m_pShaderPlugins[p]->CreateInstance ( l_ppShaders[s], m_pDisplay );
				l_pGameShader->m_pShaderNodes.Add ( l_pHandler ); 

			}

		}
	}

	m_pShaderList.Add ( l_pGameShader );

	return l_pGameShader;
}
void		MaterialSystem::SetDisplay ( Display* in_pDisplay )
{
	 m_pDisplay = in_pDisplay;

	 	//
	// The only shader plugin available now
	// is the Cg shader. This is hardcoded for now.
	// 

	ShaderPlugin* l_pShader = new ShaderPlugin;
	l_pShader->CreateInstance = NULL;
	l_pShader->GetProgID = NULL;

	SetCurrentDirectory(OpenGLDisplay::m_szRootPath);
	HMODULE hDLL = LoadLibrary ( ".\\bin\\CgShaderHandler.dll");

	if ( hDLL )
	{
		l_pShader->GetProgID = (PROGIDFNC) GetProcAddress ( hDLL, "GetHandlerProgID");
		l_pShader->CreateInstance  = (FACTORYFNC) GetProcAddress ( hDLL, "CreateShader");
	}

	if ( ( l_pShader->GetProgID == NULL ) && ( l_pShader->CreateInstance == NULL ))
	{
		delete l_pShader;

		MessageBox ( NULL, "This game requires the nVidia Cg Toolkit installed but was not detected.\nAs a result some shaders will be disabled.\n\nPlease visit nVidia's website to obtain the toolkit.", "Softimage Game WARNING", MB_OK | MB_ICONINFORMATION);
	} else {

		m_pShaderPlugins.Add ( l_pShader );
	}
}

GameShader*		MaterialSystem::FindShader ( char *in_szShaderName )
{

	for (int c=0;c<m_pShaderList.GetUsed();c++)
	{
		if (!strcmp ( m_pShaderList[c]->m_szName, in_szShaderName ))
		{
			return m_pShaderList[c];
		}
	}

	return NULL;

}

void	MaterialSystem::AddMaterialLibrary ( char* in_szMatlibName )
{
	CSLScene* l_pScene = new CSLScene;

	if(l_pScene->Open( in_szMatlibName) == SI_SUCCESS)
	{
		l_pScene->Read();
	} else {

		delete l_pScene;
		return;
	}

	CSLMaterialLibrary* matLib =  l_pScene->GetMaterialLibrary();
	if ( matLib )
	{
		for (int c=0;c<matLib->GetMaterialCount();c++)
		{
			CSLBaseMaterial* l_pMat = matLib->GetMaterialList()[c];
			if ( l_pMat->Type() == CSLTemplate::XSI_MATERIAL )
			{
				AddMaterial ( (CSLXSIMaterial*)l_pMat );
			}

		}
	}

	m_pMatLibs.Add ( l_pScene );
}

int	MaterialSystem::ExecuteShader ( GameShader* in_pShader)
{
	int UVCount = 0;
	for (int s=0;s<in_pShader->m_pShaderNodes.GetUsed();s++)
	{
		in_pShader->m_pShaderNodes[s]->execute();
		UVCount += in_pShader->m_pShaderNodes[s]->UVstages();
	}

	return UVCount;
}

void	MaterialSystem::ShutdownShader ( GameShader* in_pShader)
{
	for (int s=0;s<in_pShader->m_pShaderNodes.GetUsed();s++)
	{
		in_pShader->m_pShaderNodes[s]->enable ( false );
	}

}

void	MaterialSystem::Purge()
{
	for (int s=0;s<m_pShaderList.GetUsed();s++)
	{
		delete m_pShaderList[s];
	}
	m_pShaderList.DisposeData ();

	for (int m=0;m<m_pMatLibs.GetUsed();m++)
	{
		m_pMatLibs[m]->Close();
		delete m_pMatLibs[m];
	}

	m_pMatLibs.DisposeData ();

	for (int p=0;p<m_pShaderPlugins.GetUsed();p++)
	{
		delete m_pShaderPlugins[p];
	}
	m_pShaderPlugins.DisposeData();
}
