//*****************************************************************************
//
// File supervisor : Dominic Laflamme
// Date :
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   
//
// @doc INTERNAL
//
// @module GPUProgramGLSL.cpp
//*****************************************************************************

#ifndef unix
#include <windows.h>
#endif
#include <assert.h>
#include <malloc.h>
#include "GPUProgramGLSL.h"

#ifdef unix
#include <GL/glx.h>
#define XSI_BIND_FUNC(x,y,z)	x = (y) glXGetProcAddressARB((const GLubyte*)(z))
#else
#define XSI_BIND_FUNC(x,y,z)	x = (y) wglGetProcAddress(z)
#endif

PFNGLATTACHOBJECTARBPROC			glAttachObjectARB =NULL;
PFNGLCOMPILESHADERARBPROC			glCompileShaderARB =NULL;
PFNGLCREATEPROGRAMOBJECTARBPROC		glCreateProgramObjectARB =NULL;
PFNGLCREATESHADEROBJECTARBPROC glCreateShaderObjectARB =NULL;
PFNGLDELETEOBJECTARBPROC glDeleteObjectARB =NULL;
PFNGLDETACHOBJECTARBPROC glDetachObjectARB =NULL;
PFNGLGETACTIVEUNIFORMARBPROC glGetActiveUniformARB =NULL;
PFNGLGETATTACHEDOBJECTSARBPROC glGetAttachedObjectsARB =NULL;
PFNGLGETHANDLEARBPROC glGetHandleARB =NULL;
PFNGLGETINFOLOGARBPROC glGetInfoLogARB =NULL;
PFNGLGETOBJECTPARAMETERFVARBPROC glGetObjectParameterfvARB =NULL;
PFNGLGETOBJECTPARAMETERIVARBPROC glGetObjectParameterivARB =NULL;
PFNGLGETSHADERSOURCEARBPROC glGetShaderSourceARB =NULL;
PFNGLGETUNIFORMLOCATIONARBPROC glGetUniformLocationARB =NULL;
PFNGLGETUNIFORMFVARBPROC glGetUniformfvARB =NULL;
PFNGLGETUNIFORMIVARBPROC glGetUniformivARB =NULL;
PFNGLLINKPROGRAMARBPROC glLinkProgramARB =NULL;
PFNGLSHADERSOURCEARBPROC glShaderSourceARB =NULL;
PFNGLUNIFORM1FARBPROC glUniform1fARB =NULL;
PFNGLUNIFORM1FVARBPROC glUniform1fvARB =NULL;
PFNGLUNIFORM1IARBPROC glUniform1iARB =NULL;
PFNGLUNIFORM1IVARBPROC glUniform1ivARB =NULL;
PFNGLUNIFORM2FARBPROC glUniform2fARB =NULL;
PFNGLUNIFORM2FVARBPROC glUniform2fvARB =NULL;
PFNGLUNIFORM2IARBPROC glUniform2iARB =NULL;
PFNGLUNIFORM2IVARBPROC glUniform2ivARB =NULL;
PFNGLUNIFORM3FARBPROC glUniform3fARB =NULL;
PFNGLUNIFORM3FVARBPROC glUniform3fvARB =NULL;
PFNGLUNIFORM3IARBPROC glUniform3iARB =NULL;
PFNGLUNIFORM3IVARBPROC glUniform3ivARB =NULL;
PFNGLUNIFORM4FARBPROC glUniform4fARB =NULL;
PFNGLUNIFORM4FVARBPROC glUniform4fvARB =NULL;
PFNGLUNIFORM4IARBPROC glUniform4iARB =NULL;
PFNGLUNIFORM4IVARBPROC glUniform4ivARB =NULL;
PFNGLUNIFORMMATRIX2FVARBPROC glUniformMatrix2fvARB =NULL;
PFNGLUNIFORMMATRIX3FVARBPROC glUniformMatrix3fvARB =NULL;
PFNGLUNIFORMMATRIX4FVARBPROC glUniformMatrix4fvARB =NULL;
PFNGLUSEPROGRAMOBJECTARBPROC glUseProgramObjectARB =NULL;
PFNGLVALIDATEPROGRAMARBPROC glValidateProgramARB =NULL;

void printInfoLog(GLhandleARB object);

void A2WHelper( wchar_t* out_wcs, const char* in_sz, int in_cch = -1 );

#define A2W2(out_wcs, in_sz) \
	if (NULL == (const char *)(in_sz)) \
		*(out_wcs) = NULL; \
	else \
	{ \
		*(out_wcs) = (wchar_t*)alloca((strlen((in_sz)) + 1) * sizeof(wchar_t)); \
		A2WHelper(*(out_wcs), (in_sz)); \
	}

void A2WHelper( wchar_t* out_wcs, const char* in_sz, int in_cch )
{
	if ( out_wcs != NULL && 0 != in_cch )
	{
		out_wcs[0] = L'\0' ;

		if ( in_sz != NULL )
		{
			size_t l_iLen = 0;
			l_iLen = ::mbstowcs( out_wcs, in_sz, ( in_cch < 0 ) ? ::strlen(in_sz) + 1 : (size_t) in_cch ) ;
			assert( (int)l_iLen != -1 );

        		if ( in_cch > 0 ) { out_wcs[ in_cch - 1 ] = L'\0'; }
		}
	}
}

//*****************************************************************************
// Author : Dominic Laflamme
// Date   : 03/02/2006
//
//*****************************************************************************
CGPUProgramGLSL::CGPUProgramGLSL(VOID* in_pOwner)
: fragmentShader(0)
, m_szCodeBuffer(0)
{
	

	XSI_BIND_FUNC( glAttachObjectARB, PFNGLATTACHOBJECTARBPROC, "glAttachObjectARB");
	XSI_BIND_FUNC( glCompileShaderARB, PFNGLCOMPILESHADERARBPROC, "glCompileShaderARB");
	XSI_BIND_FUNC( glCreateProgramObjectARB, PFNGLCREATEPROGRAMOBJECTARBPROC, "glCreateProgramObjectARB");
	XSI_BIND_FUNC( glCreateShaderObjectARB, PFNGLCREATESHADEROBJECTARBPROC, "glCreateShaderObjectARB");
	XSI_BIND_FUNC( glDeleteObjectARB, PFNGLDELETEOBJECTARBPROC, "glDeleteObjectARB");
	XSI_BIND_FUNC( glDetachObjectARB, PFNGLDETACHOBJECTARBPROC, "glDetachObjectARB");
	XSI_BIND_FUNC( glGetActiveUniformARB, PFNGLGETACTIVEUNIFORMARBPROC, "glGetActiveUniformARB");
	XSI_BIND_FUNC( glGetAttachedObjectsARB, PFNGLGETATTACHEDOBJECTSARBPROC, "glGetAttachedObjectsARB");
	XSI_BIND_FUNC( glGetHandleARB, PFNGLGETHANDLEARBPROC, "glGetHandleARB");
	XSI_BIND_FUNC( glGetInfoLogARB, PFNGLGETINFOLOGARBPROC, "glGetInfoLogARB");
	XSI_BIND_FUNC( glGetObjectParameterfvARB, PFNGLGETOBJECTPARAMETERFVARBPROC, "glGetObjectParameterfvARB");
	XSI_BIND_FUNC( glGetObjectParameterivARB, PFNGLGETOBJECTPARAMETERIVARBPROC, "glGetObjectParameterivARB");
	XSI_BIND_FUNC( glGetShaderSourceARB, PFNGLGETSHADERSOURCEARBPROC, "glGetShaderSourceARB");
	XSI_BIND_FUNC( glGetUniformLocationARB, PFNGLGETUNIFORMLOCATIONARBPROC, "glGetUniformLocationARB");
	XSI_BIND_FUNC( glGetUniformfvARB, PFNGLGETUNIFORMFVARBPROC, "glGetUniformfvARB");
	XSI_BIND_FUNC( glGetUniformivARB, PFNGLGETUNIFORMIVARBPROC, "glGetUniformivARB");
	XSI_BIND_FUNC( glLinkProgramARB, PFNGLLINKPROGRAMARBPROC, "glLinkProgramARB");
	XSI_BIND_FUNC( glShaderSourceARB, PFNGLSHADERSOURCEARBPROC, "glShaderSourceARB");
	XSI_BIND_FUNC( glUniform1fARB, PFNGLUNIFORM1FARBPROC, "glUniform1fARB");
	XSI_BIND_FUNC( glUniform1fvARB, PFNGLUNIFORM1FVARBPROC, "glUniform1fvARB");
	XSI_BIND_FUNC( glUniform1iARB, PFNGLUNIFORM1IARBPROC, "glUniform1iARB");
	XSI_BIND_FUNC( glUniform1ivARB, PFNGLUNIFORM1IVARBPROC, "glUniform1ivARB");
	XSI_BIND_FUNC( glUniform2fARB, PFNGLUNIFORM2FARBPROC, "glUniform2fARB");
	XSI_BIND_FUNC( glUniform2fvARB, PFNGLUNIFORM2FVARBPROC, "glUniform2fvARB");
	XSI_BIND_FUNC( glUniform2iARB, PFNGLUNIFORM2IARBPROC, "glUniform2iARB");
	XSI_BIND_FUNC( glUniform2ivARB, PFNGLUNIFORM2IVARBPROC, "glUniform2ivARB");
	XSI_BIND_FUNC( glUniform3fARB, PFNGLUNIFORM3FARBPROC, "glUniform3fARB");
	XSI_BIND_FUNC( glUniform3fvARB, PFNGLUNIFORM3FVARBPROC, "glUniform3fvARB");
	XSI_BIND_FUNC( glUniform3iARB, PFNGLUNIFORM3IARBPROC, "glUniform3iARB");
	XSI_BIND_FUNC( glUniform3ivARB, PFNGLUNIFORM3IVARBPROC, "glUniform3ivARB");
	XSI_BIND_FUNC( glUniform4fARB, PFNGLUNIFORM4FARBPROC, "glUniform4fARB");
	XSI_BIND_FUNC( glUniform4fvARB, PFNGLUNIFORM4FVARBPROC, "glUniform4fvARB");
	XSI_BIND_FUNC( glUniform4iARB, PFNGLUNIFORM4IARBPROC, "glUniform4iARB");
	XSI_BIND_FUNC( glUniform4ivARB, PFNGLUNIFORM4IVARBPROC, "glUniform4ivARB");
	XSI_BIND_FUNC( glUniformMatrix2fvARB, PFNGLUNIFORMMATRIX2FVARBPROC, "glUniformMatrix2fvARB");
	XSI_BIND_FUNC( glUniformMatrix3fvARB, PFNGLUNIFORMMATRIX3FVARBPROC, "glUniformMatrix3fvARB");
	XSI_BIND_FUNC( glUniformMatrix4fvARB, PFNGLUNIFORMMATRIX4FVARBPROC, "glUniformMatrix4fvARB");
	XSI_BIND_FUNC( glUseProgramObjectARB, PFNGLUSEPROGRAMOBJECTARBPROC, "glUseProgramObjectARB");
	XSI_BIND_FUNC( glValidateProgramARB, PFNGLVALIDATEPROGRAMARBPROC, "glValidateProgramARB");


	ProgramObjectVTX = 0;
	ProgramObjectFRAG = 0;
	
}

//*****************************************************************************
// Author : Dominic Laflamme
// Date   : 03/02/2006
//
//*****************************************************************************
CGPUProgramGLSL::~CGPUProgramGLSL(void)
{
	

}

bool	CGPUProgramGLSL::Create		(const char* in_szCode, eProgramLocation in_eLocation)
{
	
	
	ProgramObjectVTX = glCreateProgramObjectARB();
	ProgramObjectFRAG = ProgramObjectVTX;

	m_location = in_eLocation;

	const char* l_szCode = in_szCode;

	if ( m_location == File )
	{
		l_szCode = GetCodeFromFile (in_szCode);
	} 

	bool retval = true;
	retval = CompileAndLink ( l_szCode )?true:false;
	

	return retval;
}

BOOL	CGPUProgramGLSL::CompileAndLink ( const char* in_szCode )
{
	if ( !in_szCode )
		return FALSE;

	if ( fragmentShader )
	{
		glDetachObjectARB(ProgramObjectFRAG, fragmentShader);
		glDeleteObjectARB ( fragmentShader );
	}

	fragmentShader = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	glAttachObjectARB(ProgramObjectFRAG, fragmentShader);

	glShaderSourceARB(fragmentShader, 1, (const char **)&in_szCode, NULL);
	glCompileShaderARB(fragmentShader);

	GLint compiled = 0;
	glGetObjectParameterivARB(fragmentShader, GL_OBJECT_COMPILE_STATUS_ARB, &compiled);
	if ( !compiled )
	{
		printInfoLog ( fragmentShader );
		return FALSE;
	}
	
	glLinkProgramARB(ProgramObjectFRAG);

	GLint linked = 0;
	glGetObjectParameterivARB(ProgramObjectFRAG, GL_OBJECT_LINK_STATUS_ARB, &linked);
	if ( !linked )
	{
		printInfoLog ( ProgramObjectFRAG );
		return FALSE;
	}

	return TRUE;
}


//*****************************************************************************
// Author : Dominic Laflamme
// Date   : 03/02/2006
//
//*****************************************************************************
bool	CGPUProgramGLSL::Create		(const char* in_szVtxCode, const char* in_szFragCode)
{
	

	if ( glCreateProgramObjectARB == NULL )
		return false;

	if ( in_szVtxCode != NULL )
	{
	    ProgramObjectVTX = glCreateProgramObjectARB();
        vertexShader = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);

        glShaderSourceARB(vertexShader, 1, &in_szVtxCode, NULL);
        glCompileShaderARB(vertexShader);

		GLint compiled = 0;
		glGetObjectParameterivARB(vertexShader, GL_OBJECT_COMPILE_STATUS_ARB, &compiled);
		if ( !compiled )
		{
			printInfoLog ( vertexShader );
			return false;
		}

        glAttachObjectARB(ProgramObjectVTX, vertexShader);
        glLinkProgramARB(ProgramObjectVTX);

		GLint linked = 0;
		glGetObjectParameterivARB(ProgramObjectVTX, GL_OBJECT_LINK_STATUS_ARB, &linked);
		if ( !linked )
		{
			printInfoLog ( ProgramObjectVTX );
			return false;
		}
	}

	if ( in_szFragCode != NULL )
	{
		if ( ProgramObjectVTX == 0 )
		{
			ProgramObjectFRAG = glCreateProgramObjectARB();
		} else {
			ProgramObjectFRAG = ProgramObjectVTX;
		}

        fragmentShader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);

        glShaderSourceARB(fragmentShader, 1, &in_szFragCode, NULL);
        glCompileShaderARB(fragmentShader);

		GLint compiled = 0;
		glGetObjectParameterivARB(fragmentShader, GL_OBJECT_COMPILE_STATUS_ARB, &compiled);
		if ( !compiled )
		{
			printInfoLog ( fragmentShader );
			return false;
		}
        glAttachObjectARB(ProgramObjectFRAG, fragmentShader);
        glLinkProgramARB(ProgramObjectFRAG);

		GLint linked = 0;
		glGetObjectParameterivARB(ProgramObjectFRAG, GL_OBJECT_LINK_STATUS_ARB, &linked);
		if ( !linked )
		{
			printInfoLog ( ProgramObjectFRAG );
			return false;
		}

	}
	
	return true;
}

//*****************************************************************************
// Author : Dominic Laflamme
// Date   : 03/02/2006
//
//*****************************************************************************
bool	CGPUProgramGLSL::Activate		( bool in_eActivate )
{
	
	if (!glUseProgramObjectARB)
		return false;

	if ( in_eActivate )
	{
//#if 0
		if ( m_location == File )
		{
			if ( IsFilenameDirty() )
			{
				CompileAndLink(GetCodeFromFile(m_szFilename));
			}
		}
//#endif
		if ( ProgramObjectVTX )
			glUseProgramObjectARB(ProgramObjectVTX);

		if ( ProgramObjectFRAG )
			glUseProgramObjectARB(ProgramObjectFRAG);
	} else {
		 glUseProgramObjectARB(0);
	}

	return false;
}

//*****************************************************************************
// Author : Dominic Laflamme
// Date   : 03/02/2006
//
//*****************************************************************************
bool	CGPUProgramGLSL::SetUniforms	(IRTSExecutionState				* in_pExecState)
{
	
	if (!glUniform1iARB)
		return false;

	GLSLParameterMapIter it = m_ParamMap.begin();

	while ( it != m_ParamMap.end() )
	{
		GLSLUniform *l_pUniform = (*it).second;
		switch ( l_pUniform->m_iSize )
		{
		case 0: glUniform1iARB (l_pUniform->m_iID, l_pUniform->m_uiID); break;
		case 1: glUniform1fvARB(l_pUniform->m_iID, 1, l_pUniform->m_data); break;
		case 2: glUniform2fvARB(l_pUniform->m_iID, 2, l_pUniform->m_data); break;
		case 3: glUniform3fvARB(l_pUniform->m_iID, 3, l_pUniform->m_data); break;
		case 4: glUniform4fARB(l_pUniform->m_iID, l_pUniform->m_data[0], l_pUniform->m_data[1], l_pUniform->m_data[2], l_pUniform->m_data[3] ); break;
		case 16: glUniformMatrix4fvARB(l_pUniform->m_iID, 1, GL_FALSE, l_pUniform->m_data); break;
		}
		it++;
	}

	// set uniforms that are connected to us in the rendre tree

	unsigned long nbUniforms = in_pExecState->GetNbUniforms();
	XSI_RTS_Uniform** puList = in_pExecState->GetUniformList();

	for (unsigned long u=0;u<nbUniforms;u++)
	{
		XSI_RTS_Uniform* def = puList[u];
		void* vData = def->GetData();

		GLint loc = glGetUniformLocationARB(ProgramObjectFRAG, def->GetName() );
		if ( loc >= 0 )
		{
			switch ( def->GetType() )
			{
			case XSI_RTS_Uniform::Float :
				{
					float* fData = (float*)vData;
					switch ( def->GetSize() )
					{
						//case 0: glUniform1iARB (l_pUniform->m_iID, l_pUniform->m_uiID); break;
						case 1: glUniform1fARB(loc,fData[0]); break;
						case 2: glUniform2fARB(loc,fData[0],fData[1]); break;
						case 3: glUniform3fARB(loc,fData[0],fData[1],fData[2] ); break;
						case 4: glUniform4fARB(loc,fData[0],fData[1],fData[2],fData[3] ); break;
						case 16: glUniformMatrix4fvARB(loc, 1, GL_FALSE,fData); break;
					}
					break;
				}
			case XSI_RTS_Uniform::Int :
				{
					int* fData = (int*)vData;
					switch ( def->GetSize() )
					{
						//case 0: glUniform1iARB (l_pUniform->m_iID, l_pUniform->m_uiID); break;
						case 1: glUniform1iARB(loc,fData[0]); break;
						case 2: glUniform2iARB(loc,fData[0],fData[1]); break;
						case 3: glUniform3iARB(loc,fData[0],fData[1],fData[2] ); break;
						case 4: glUniform4iARB(loc,fData[0],fData[1],fData[2],fData[3] ); break;
						default: assert(0); break; //illegal size
					}
					break;
				}
			case XSI_RTS_Uniform::Texture :
				{
					int* fData = (int*)vData;
					switch ( def->GetSize() )
					{
						case 4: glUniform1iARB(loc,fData[0]); break;
						default: assert(0); break; //illegal size for GLSL
					}
					break;
				}

			default: assert(0);
			}

		}

	}

	in_pExecState->ClearUniforms();

	return true;
}

bool	CGPUProgramGLSL::DefineMatrixUniform (const char* in_szName, int in_iMatrixCount, float* in_pData, eProgramtype in_eType )
{
	

	GLSLParameterMapIter it = m_ParamMap.find (  in_szName );
	if ( it == m_ParamMap.end() )
	{
		GLSLUniform* l_pUniform = new GLSLUniform;
		l_pUniform->m_iSize = 16;
		l_pUniform->m_iID = glGetUniformLocationARB(ProgramObjectFRAG, in_szName);
		l_pUniform->m_iMatrixCount = in_iMatrixCount;
		l_pUniform->m_data = new float [16*in_iMatrixCount];
		memcpy ( l_pUniform->m_data, in_pData, sizeof(float)*16*in_iMatrixCount);
		m_ParamMap[in_szName] = l_pUniform;

	} else {

		GLSLUniform *l_pUniform = (*it).second;
		l_pUniform->m_iMatrixCount = in_iMatrixCount;
		delete [] l_pUniform->m_data;
		l_pUniform->m_data = new float [16*in_iMatrixCount];
		memcpy ( l_pUniform->m_data, in_pData, sizeof(float)*16*in_iMatrixCount);

	}
	return true;
}

bool	CGPUProgramGLSL::DefineMatrixUniform (const char* in_szName, int in_iMatrixCount, double* in_pData, eProgramtype in_eType )
{
	

	GLSLParameterMapIter it = m_ParamMap.find ( in_szName );
	if ( it == m_ParamMap.end() )
	{
		GLSLUniform* l_pUniform = new GLSLUniform;
		l_pUniform->m_iSize = 16;
		l_pUniform->m_iID = glGetUniformLocationARB(ProgramObjectFRAG, in_szName);
		l_pUniform->m_iMatrixCount = in_iMatrixCount;
		l_pUniform->m_data = new float [16*in_iMatrixCount];
		for (int v=0;v<16;v++)
			l_pUniform->m_data[v] = (float)in_pData[v];
		m_ParamMap[in_szName] = l_pUniform;

	} else {

		GLSLUniform *l_pUniform = (*it).second;
		l_pUniform->m_iMatrixCount = in_iMatrixCount;
		delete [] l_pUniform->m_data;
		l_pUniform->m_data = new float [16*in_iMatrixCount];
		for (int v=0;v<16;v++)
			l_pUniform->m_data[v] = (float)in_pData[v];

	}
	return true;

}

bool	CGPUProgramGLSL::DefineUniform (const char* in_szName, unsigned int in_uiValue, eProgramtype in_eType )
{
	

	GLSLParameterMapIter it = m_ParamMap.find ( in_szName );
	if ( it == m_ParamMap.end() )
	{
		GLSLUniform* l_pUniform = new GLSLUniform;
		l_pUniform->m_iSize = 0;
		l_pUniform->m_iID = glGetUniformLocationARB(ProgramObjectFRAG, in_szName);
		l_pUniform->m_uiID = in_uiValue;
		m_ParamMap[in_szName] = l_pUniform;

	} else {

		GLSLUniform *l_pUniform = (*it).second;
		l_pUniform->m_uiID = in_uiValue;

	}
	return true;
}

//*****************************************************************************
// Author : Dominic Laflamme
// Date   : 03/02/2006
//
//*****************************************************************************
bool	CGPUProgramGLSL::DefineUniform(const char* in_szName, int in_lSize, float* in_pData, eProgramtype in_eType )
{
	

	GLSLParameterMapIter it = m_ParamMap.find ( in_szName );
	if ( it == m_ParamMap.end() )
	{
		GLSLUniform* l_pUniform = new GLSLUniform;
		l_pUniform->m_iSize = in_lSize;
		l_pUniform->m_iID = glGetUniformLocationARB(in_eType == VertexProgram ? ProgramObjectVTX : ProgramObjectFRAG, in_szName);
		l_pUniform->m_data = new float [in_lSize];
		memcpy ( l_pUniform->m_data, in_pData, sizeof(float)*in_lSize);
		m_ParamMap[in_szName] = l_pUniform;

	} else {

		GLSLUniform *l_pUniform = (*it).second;
		delete [] l_pUniform->m_data;
		l_pUniform->m_data = new float [in_lSize];
		memcpy ( l_pUniform->m_data, in_pData, sizeof(float)*in_lSize);

	}
	return true;
	
}

//*****************************************************************************
// Author : Dominic Laflamme
// Date   : 03/09/2006
//
//*****************************************************************************
void*	CGPUProgramGLSL::GetUniform ( const char* in_szName )
{
	

	GLSLParameterMapIter it = m_ParamMap.find ( in_szName );
	if ( it == m_ParamMap.end() )
	{
		GLSLUniform* l_pUniform = new GLSLUniform;
		l_pUniform->m_iSize = 1;
		l_pUniform->m_iID = glGetUniformLocationARB(ProgramObjectFRAG, in_szName);
		l_pUniform->m_data = new float [1];
		m_ParamMap[in_szName] = l_pUniform;

		return &l_pUniform->m_iID;

	} else {

		GLSLUniform *l_pUniform = (*it).second;

		return &l_pUniform->m_iID;
	}

	return NULL;
}


void printInfoLog(GLhandleARB object)
{
	
    int maxLength = 0;
    glGetObjectParameterivARB(object, GL_OBJECT_INFO_LOG_LENGTH_ARB, &maxLength);

    char *infoLog = new char[maxLength];
    glGetInfoLogARB(object, maxLength, &maxLength, infoLog);


#ifndef unix
    OutputDebugString ( infoLog );
    OutputDebugString ( "\n");
#endif

	delete [] infoLog;
	
}


const char*			CGPUProgramGLSL::GetCodeFromFile( const char* in_szFilename )
{
	strcpy ( m_szFilename,in_szFilename);
#ifndef unix
	HANDLE hFile; 
	
	hFile = CreateFile(in_szFilename,GENERIC_READ|GENERIC_WRITE, 
						FILE_SHARE_READ,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL); 
	
	GetFileTime ( hFile,NULL,NULL,&m_LastAccessTime);

	CloseHandle(hFile); 
#else
	// Unix equivalent
#endif

	FILE* f = fopen ( in_szFilename, "rb" );
	assert (f);

	if ( !f )
		return NULL;

	fseek ( f,0,SEEK_END );
	long fsize = ftell(f);
	fseek ( f,0,SEEK_SET );

	if ( m_szCodeBuffer )
	{
		delete [] m_szCodeBuffer;
		m_szCodeBuffer = NULL;
	}

	m_szCodeBuffer = new char [fsize+1];
	memset ( m_szCodeBuffer,0,fsize+1 );

	fread ( m_szCodeBuffer, fsize,sizeof(char), f );

	fclose(f);

	return m_szCodeBuffer;

}

bool	CGPUProgramGLSL::IsFilenameDirty ()
{
#ifndef unix
	HANDLE hFile; 
	
	hFile = CreateFile(m_szFilename,GENERIC_READ|GENERIC_WRITE, 
						FILE_SHARE_READ,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL); 
	
	FILETIME accessTime;
	GetFileTime ( hFile,NULL,NULL,&accessTime);
	CloseHandle(hFile); 

	int r = CompareFileTime ( &accessTime, &m_LastAccessTime );

	if ( r )
	{
		return true;
	}
	
	return false;
#else
	// Unix equivalent
	return false;
#endif
}
