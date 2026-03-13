// OGLParticles.cpp
// *******************************************************************
// File Supervisor  : Dominic Laflamme x3208
// Created          : Avril 2007
// Last Updated     : 
// *******************************************************************
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   
// *******************************************************************

#define __CSISTATMANAGER_H__
#define __DONTINCLUDSISTRING_HACKHACK__

#ifdef _WIN32
#include <windows.h>
#endif
#include <string>
#define SHADERS_EXPORTS
#include "OGLParticle.h"
#include "MatrixHelper.h"
#include "Mesh.h"
#include "SphereMesh.h"
#include "CubeMesh.h"
#include "WireSphere.h"
#include "SnowflakeMesh.h"
#include "DebrisMesh.h"
#include "QuadMesh.h"
#include "ArrowMesh.h"
#include "SphereMesh.h"
#include "GPUProgramGLSL.h"
#include "GLSLShaders.h"

#include <XSI_rtshaders.h>
//#include <XSI_OGLHelper.h>
 
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define POINT_SPRITE_ARB                               0x8861
#define COORD_REPLACE_ARB                              0x8862
#define DEG_TO_RAD( deg ) ((deg)*M_PI/180.0)

bool	gPseudoInstancingSupported = false;

typedef struct _PerInstanceData
{
	_PerInstanceData()
	{
		m_pDensityCache = NULL;
		m_ulDensityCacheSize = 0;
		m_pGLSL = NULL;
	};

	~_PerInstanceData()
	{
		if ( m_pGLSL != NULL )
			delete m_pGLSL;

		if ( m_pDensityCache != NULL )
			delete [] m_pDensityCache;
	}

	float				*m_pDensityCache;
	ULONG				m_ulDensityCacheSize;
	CGPUProgramGLSL*	m_pGLSL;
	std::string			m_FragmentShaderCode;

} PerInstanceData;

Mesh*	gMeshes[8];


PFNGLMULTITEXCOORD2FVARBPROC       g_glMultiTexCoord2f[8];



pfRenderParticleCloud	gShaderRenderFuntion[] = {
	NULL,	// primitive, see gPrimitiveRenderFuntions
	RenderHWAcceleratedSprites,
	RenderBillboardSprites,
	VelocityVectors,
	DensityField,
	LineTrails
};

pfRenderParticleCloud	gPrimitiveRenderFunctions[] = {
	RenderPoints,
	RenderPrimitiveUsingPseudoInstancing,
	RenderPrimitiveUsingPseudoInstancing,
	RenderPrimitiveUsingPseudoInstancing,
	RenderPrimitiveUsingPseudoInstancing,
	RenderPrimitiveUsingPseudoInstancing,
	RenderPrimitiveUsingPseudoInstancing,
	RenderPrimitiveUsingPseudoInstancing
};

XSI_RTS_Attribute gOGLParticleEPAttributes[] = 
{
	XSI_RTS_ATTRIBUTE_POSITION, ePOSITION, 
	"color", eCOLOR0,
	XSI_RTS_ATTRIBUTE_VELOCITY, eNORMAL,
	XSI_RTS_ATTRIBUTE_ORIENTATION, eTEXCOORD0,
	XSI_RTS_ATTRIBUTE_SIZE,eTEXCOORD1,
	XSI_RTS_ATTRIBUTE_ID, eTEXCOORD2,
	0, eMAX_STANDARD_VERTEX_ATTRIBUTE
};

XSI_RTS_Attribute gOGLParticleLineTrailsAttributes[] = 
{
	XSI_RTS_ATTRIBUTE_POSITION, ePOSITION, 
	"Color", eCOLOR0,
	"TipColor", eCOLOR1,
	"StrandPosition", eTEXCOORD2,
	"StrandColor", eTEXCOORD3,
	0, eMAX_STANDARD_VERTEX_ATTRIBUTE
};

// Attribute structure
typedef struct tagOGLLineTrailData
{
	float*	m_pPositions;
	float*	m_pColors;
	float*	m_pTipColors;
	float*	m_pTrailPositions;
	float*	m_pTrailColors;

} OGLLineTrailData;

//*****************************************************************************
// Author : Dominic Laflamme
// Date   : April 2007
// @func  return RTS Version number (3.0)
//
//*****************************************************************************
extern "C" RTSHADER_API ULONG RTS_GetVersion()
{
	return XSI_RTSHADER_VERSION;	
}

//*****************************************************************************
// Author : Dominic Laflamme
// Date   : April 2007
// @func  returns the attribute list we are interested in drawing
//
//*****************************************************************************
extern "C" RTSHADER_API XSI_RTS_Attribute* OGLParticleEP_GetAttributeList
(
 	IRTSExecutionState				*in_pExecState,					//! The execute state
	OGLParticle_t					*in_pParams,
	void							**io_pInstanceData
)
{
	if ( in_pParams->Type == 5)
	{
		return gOGLParticleLineTrailsAttributes;
	}
	return gOGLParticleEPAttributes;	
}

//*****************************************************************************
// Author : Dominic Laflamme
// Date   : April 2007
// @func  Main execution entry point
//
//*****************************************************************************
extern "C" RTSHADER_API bool
OGLParticleEP_Execute
(
	IRTSExecutionState				*in_pExecState,					//! The execute state
	OGLParticle_t		*in_pParams,		// The property page parameters
	XSI_RTS_Primitive	*in_pPrimitive,		// The geometry information
	void				*in_pAttributes,	// The attribute data
	XSI_RTS_Attribute_Size	*in_pAttributesSize,	// the sizes
	void				**io_pInstanceData	// The shader instance data
	)
{

	PerInstanceData *pThisData = (PerInstanceData*)*io_pInstanceData;

	OGLParticleAttributeData* l_pAttribs = (OGLParticleAttributeData*)in_pAttributes;

	if ( in_pPrimitive->m_Type != RTS_PT_PARTICLE_CLOUD)	// we can only render particles
		return false;

	if ( l_pAttribs->m_pPositions == NULL )	// cant render without positions
		return false;	
#ifdef _WIN32
	if (in_pParams->GPUInstancing && in_pExecState->GetSystemParams()->m_pGLExtFuncs->glCreateShaderObjectARB)
	{
		gPrimitiveRenderFunctions[1] = RenderPrimitiveUsingPseudoInstancing;
		gPrimitiveRenderFunctions[2] = RenderPrimitiveUsingPseudoInstancing;
		gPrimitiveRenderFunctions[3] = RenderPrimitiveUsingPseudoInstancing;
		gPrimitiveRenderFunctions[4] = RenderPrimitiveUsingPseudoInstancing;
		gPrimitiveRenderFunctions[5] = RenderPrimitiveUsingPseudoInstancing;
		gPrimitiveRenderFunctions[6] = RenderPrimitiveUsingPseudoInstancing;
		gPrimitiveRenderFunctions[7] = RenderPrimitiveUsingPseudoInstancing;
	} else 
#endif
{
		gPrimitiveRenderFunctions[1] = RenderPrimitiveSlow;
		gPrimitiveRenderFunctions[2] = RenderPrimitiveSlow;
		gPrimitiveRenderFunctions[3] = RenderPrimitiveSlow;
		gPrimitiveRenderFunctions[4] = RenderPrimitiveSlow;
		gPrimitiveRenderFunctions[5] = RenderPrimitiveSlow;
		gPrimitiveRenderFunctions[6] = RenderPrimitiveSlow;
		gPrimitiveRenderFunctions[7] = RenderPrimitiveSlow;
	
}




	if ( in_pParams->CustomFragmentShader )
	{
		if ( in_pParams->FragmentShader )
		{
			if ( strlen(in_pParams->FragmentShader) > 1 )
			{
				if ( pThisData->m_FragmentShaderCode.compare ( in_pParams->FragmentShader))
				{
					//
					// strings are different, refresh the GLSL program
					pThisData->m_FragmentShaderCode = in_pParams->FragmentShader;
					if (pThisData->m_pGLSL)
					{
						delete pThisData->m_pGLSL;
						pThisData->m_pGLSL = NULL;
					}
				}
			}
		}
		
	} else {

		if ( pThisData->m_FragmentShaderCode.size() )
		{
			// need to delete the GLSL shader
			pThisData->m_FragmentShaderCode.clear();
			if (pThisData->m_pGLSL)
			{
				delete pThisData->m_pGLSL;
				pThisData->m_pGLSL = NULL;
			}
		}
	}

	if ( pThisData->m_pGLSL == NULL )
	{
#ifdef _WIN32
		pThisData->m_pGLSL = new CGPUProgramGLSL(NULL);

		gPseudoInstancingSupported = pThisData->m_pGLSL->Create ( in_pParams->GPUInstancing ? GetShaderCode ( GLSL_PSEUDO_INSTANCING) : NULL , pThisData->m_FragmentShaderCode.size() > 0 ? pThisData->m_FragmentShaderCode.c_str() : NULL );
#endif

	}


	glPushAttrib ( GL_ENABLE_BIT );

	glBlendFunc(in_pParams->BlendSrc,in_pParams->BlendDest);
	if ( in_pParams->Blending )
	{
		glEnable (GL_BLEND);
	} else {
		glDisable(GL_BLEND);
	}

	if ( in_pParams->OGLLighting )
	{
		glEnable ( GL_LIGHTING );
	} else {
		glDisable ( GL_LIGHTING );
	}

	if ( in_pParams->AlphaTest )
	{
		glAlphaFunc ( in_pParams->AlphaFunc, in_pParams->AlphaRef);
		glEnable ( GL_ALPHA_TEST );
	}
	
	if ( in_pParams->Type == 0 )
	{

		glEnable( GL_DEPTH_TEST );
			glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
		if ( !in_pParams->Textured )
		{
			glDisable ( GL_TEXTURE_2D );
		} else {
			glEnable ( GL_TEXTURE_2D );
		}
		(gPrimitiveRenderFunctions[in_pParams->PrimitiveType]) (in_pExecState,in_pExecState->GetSystemParams(),in_pParams, in_pPrimitive,in_pAttributes, in_pAttributesSize, io_pInstanceData);

	} else {
		
		(gShaderRenderFuntion[in_pParams->Type]) (in_pExecState,in_pExecState->GetSystemParams(),in_pParams, in_pPrimitive,in_pAttributes, in_pAttributesSize, io_pInstanceData);
	}

	
glPopAttrib();

	return false;
}

//*****************************************************************************
// Author : Dominic Laflamme
// Date   : April 2007
// @func  Initialize the shader
//
//*****************************************************************************
extern "C" RTSHADER_API bool
OGLParticleEP_Init
(
	IRTSExecutionState				*in_pExecState,					//! The execute state
	OGLParticle_t		*in_pParams,		// The property page parameters
	void				**io_pInstanceData	// The shader instance data
	)
{
	for (int m=0;m<8;m++)
		gMeshes[m] = 0;

	PerInstanceData *pThisData = new PerInstanceData();
	*io_pInstanceData = pThisData;

	return( true );
}

//*****************************************************************************
// Author : Dominic Laflamme
// Date   : April 2007
// @func  Clean up
//
//*****************************************************************************
extern "C" RTSHADER_API bool
OGLParticleEP_Term
(
	IRTSExecutionState				*in_pExecState,					//! The execute state
	OGLParticle_t		*in_pParams,		// The property page parameters
	void				**io_pInstanceData	// The shader instance data
	)
{
	for (int m=0;m<8;m++)
	{
		if ( gMeshes[m] != NULL )
		{
			delete gMeshes[m];
			gMeshes[m] = NULL;
		}
	}

	PerInstanceData *pThisData = (PerInstanceData*)*io_pInstanceData;
	delete pThisData;

	return( true );
}

//*****************************************************************************
// Author : Dominic Laflamme
// Date   : April 2007
// @func  Render cloud as array of colored points. 
//
//*****************************************************************************
bool RenderPoints(IRTSExecutionState				* in_pExecState,
										XSI_RTS_SystemParams *in_pSysParams, 
										void *in_pParams, 
										XSI_RTS_Primitive	*in_pPrimitive,
										void				*in_pAttributes,
										XSI_RTS_Attribute_Size	*in_pAttributesSize,
										void	**io_pShaderInstanceData )
{

	OGLParticle_t* l_pPPGParams = (OGLParticle_t*)in_pParams;
	OGLParticleAttributeData* l_pAttribs = (OGLParticleAttributeData*)in_pAttributes;

	glDisable ( GL_TEXTURE_2D);

	if ( l_pPPGParams->PointSize < 0.1f )
		l_pPPGParams->PointSize = 0.1f;

	glPointSize ( l_pPPGParams->PointSize );

	if ( l_pPPGParams->PointSmooth )
	{
		glEnable ( GL_POINT_SMOOTH );
	} else {
		glDisable( GL_POINT_SMOOTH );
	}

	glDisable (GL_LIGHTING);

	glEnableClientState( GL_VERTEX_ARRAY );
	if ( l_pAttribs->m_pColors )
	{
		glEnableClientState( GL_COLOR_ARRAY );
	} else {
		glColor3f(0.0f,0.0f,0.0f);
		glDisableClientState( GL_COLOR_ARRAY );
	}

	glDisableClientState ( GL_NORMAL_ARRAY );
	glDisableClientState ( GL_TEXTURE_COORD_ARRAY );
	glDisableClientState ( GL_INDEX_ARRAY );


	glVertexPointer(3, GL_FLOAT,0,l_pAttribs->m_pPositions);
	glColorPointer(4, GL_FLOAT,0,l_pAttribs->m_pColors);

	glDrawArrays ( GL_POINTS, 0, in_pPrimitive->m_NbVertices );

	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_COLOR_ARRAY );

		
	return true;
}

//*****************************************************************************
// Author : Dominic Laflamme
// Date   : April 2007
// @func  Render a primitive using "pseudo-instancing", that instances are
//			completely transformed on the GPU.
//
//*****************************************************************************
bool RenderPrimitiveUsingPseudoInstancing(IRTSExecutionState				* in_pExecState,
										XSI_RTS_SystemParams *in_pSysParams, 
										void *in_pParams, 
										XSI_RTS_Primitive	*in_pPrimitive,
										void				*in_pAttributes,
										XSI_RTS_Attribute_Size	*in_pAttributesSize,
										void	**io_pShaderInstanceData )
{
	
	PerInstanceData *pThisData = (PerInstanceData*)*io_pShaderInstanceData;

	OGLParticle_t* l_pPPGParams = (OGLParticle_t*)in_pParams;
	OGLParticleAttributeData* l_pAttribs = (OGLParticleAttributeData*)in_pAttributes;
	glEnable( GL_DEPTH_TEST );

	if ( gMeshes[ l_pPPGParams->PrimitiveType ] == NULL )
	{
		switch ( l_pPPGParams->PrimitiveType )
		{
		case 0: assert(0);	// illegal
		case 1: gMeshes[ l_pPPGParams->PrimitiveType ] = new CubeMesh(); break;
		case 2: gMeshes[ l_pPPGParams->PrimitiveType ] = new SphereMesh(8,8); break;
		case 3: gMeshes[ l_pPPGParams->PrimitiveType ] = new WireSphereMesh(); break;
		case 4: gMeshes[ l_pPPGParams->PrimitiveType ] = new SnowflakeMesh(); break;
		case 5: gMeshes[ l_pPPGParams->PrimitiveType ] = new DebrisMesh(); break;
		case 6: gMeshes[ l_pPPGParams->PrimitiveType ] = new QuadMesh(); break;
		case 7: gMeshes[ l_pPPGParams->PrimitiveType ] = new ArrowMesh(); break;
		default:	assert ( 0 );
		}
	}

	if ( pThisData->m_pGLSL != NULL && gPseudoInstancingSupported)
	{
		pThisData->m_pGLSL->DefineMatrixUniform ("viewMatrix",1,in_pSysParams->m_SceneData->m_sCamera.m_mMatrix, CGPUProgramGLSL::VertexProgram );
		float strecth = l_pPPGParams->VelocityStretch ? 1.0f : 0.0f;
		pThisData->m_pGLSL->DefineUniform ("velocityStretch",1,&strecth, CGPUProgramGLSL::VertexProgram );
	}

	

	gMeshes[ l_pPPGParams->PrimitiveType ]->setState((OGLParticleAttributeData*)in_pAttributes);

	if ( pThisData->m_pGLSL != NULL && gPseudoInstancingSupported)
	{
		pThisData->m_pGLSL->Activate ( true );
		pThisData->m_pGLSL->SetUniforms (in_pExecState);
	}

	float* pPositions = l_pAttribs->m_pPositions;
	float* pVelocities = l_pAttribs->m_pVelocities;
	float* pColors = l_pAttribs->m_pColors;
	float* pIDs = l_pAttribs->m_pID;

	float dcolor[] = {0.70f, 0.70f, 0.70f, 1.0f };	// default color
	int iColInc = 4;
	if ( !pColors )
	{
		pColors = &dcolor[0];
		iColInc = 0;
	}

	float pDefaultVelocity[] = {0,1.0f,0,0};
	int iVelInc = 3;
	if (!pVelocities)
	{
		pVelocities = pDefaultVelocity;
		iVelInc = 0;
	}
	float pDefaultID = 0.0f;
	int iIDInc = 1;
	if ( pIDs == NULL )
	{
		pIDs = &pDefaultID;
		iIDInc=0;
	}

	for(ULONG i = 0; i < in_pPrimitive->m_NbVertices; i ++)
	{
		Mesh::glMultiTexCoord3fv (GL_TEXTURE1, pPositions );
		Mesh::glMultiTexCoord3fv (GL_TEXTURE2, pVelocities );
		Mesh::glMultiTexCoord4fv (GL_TEXTURE3, pColors );
		

		gMeshes[ l_pPPGParams->PrimitiveType ]->render ((LONG)*pIDs,1);
		pIDs+=iIDInc;

		pPositions += 3;
		pVelocities += iVelInc;
		pColors += iColInc;
	}

	gMeshes[ l_pPPGParams->PrimitiveType ]->unsetState ((OGLParticleAttributeData*)in_pAttributes);
	if ( pThisData->m_pGLSL != NULL && gPseudoInstancingSupported)
	{
		pThisData->m_pGLSL->Activate ( false );
	}
	return true;
}

//*****************************************************************************
// Author : Dominic Laflamme
// Date   : April 2007
// @func  Renders a primitive using traditional method of transforming
//		  instances on the CPU 
//
//*****************************************************************************
bool RenderPrimitiveSlow(IRTSExecutionState				* in_pExecState,
										XSI_RTS_SystemParams *in_pSysParams, 
										void *in_pParams, 
										XSI_RTS_Primitive	*in_pPrimitive,
										void				*in_pAttributes,
										XSI_RTS_Attribute_Size	*in_pAttributesSize,
										void	**io_pShaderInstanceData )
{
	
	OGLParticle_t* l_pPPGParams = (OGLParticle_t*)in_pParams;
	OGLParticleAttributeData* l_pAttribs = (OGLParticleAttributeData*)in_pAttributes;
	glEnable( GL_DEPTH_TEST );

	if ( gMeshes[ l_pPPGParams->PrimitiveType ] == NULL )
	{
		switch ( l_pPPGParams->PrimitiveType )
		{
		case 0: assert(0);	// illegal
		case 1: gMeshes[ l_pPPGParams->PrimitiveType ] = new CubeMesh(); break;
		case 2: gMeshes[ l_pPPGParams->PrimitiveType ] = new SphereMesh(8,8); break;
		case 3: gMeshes[ l_pPPGParams->PrimitiveType ] = new WireSphereMesh(); break;
		case 4: gMeshes[ l_pPPGParams->PrimitiveType ] = new SnowflakeMesh(); break;
		case 5: gMeshes[ l_pPPGParams->PrimitiveType ] = new DebrisMesh(); break;
		case 6: gMeshes[ l_pPPGParams->PrimitiveType ] = new QuadMesh(); break;
		case 7: gMeshes[ l_pPPGParams->PrimitiveType ] = new ArrowMesh(); break;
		default:	assert ( 0 );
		}
	}

	gMeshes[ l_pPPGParams->PrimitiveType ]->setState((OGLParticleAttributeData*)in_pAttributes);

	float* pPositions = l_pAttribs->m_pPositions;
	float* pVelocities = l_pAttribs->m_pVelocities;
	float* pColors = l_pAttribs->m_pColors;
	float* pIDs = l_pAttribs->m_pID;

	float dcolor[] = {0.70f, 0.70f, 0.70f, 1.0f };	// default color
	int iColInc = 4;
	if ( !pColors )
	{
		pColors = &dcolor[0];
		iColInc = 0;
	}

	float pDefaultVelocity[] = {0,1.0f,0,0};
	int iVelInc = 3;
	if (!pVelocities)
	{
		pVelocities = pDefaultVelocity;
		iVelInc = 0;
	}

	float pDefaultID = 0.0f;
	int iIDInc = 1;
	if ( pIDs == NULL )
	{
		pIDs = &pDefaultID;
		iIDInc=0;
	}

	glMatrixMode ( GL_MODELVIEW );

	for(ULONG i = 0; i < in_pPrimitive->m_NbVertices; i ++)
	{
		glPushMatrix ();

		matrix4f ori;

		if ( vec3f(pVelocities[0],pVelocities[1],pVelocities[2] ).length() < 0.00001f )
		{
			pVelocities[0] = 1.0f;
		}

		ori.look_at ( vec3f(0,0,0), vec3f(pVelocities[0],pVelocities[1],pVelocities[2] ),vec3f(0,1,0) );

		if ( l_pPPGParams->VelocityStretch )
		{
			matrix4f stretch;
			stretch.set_scale ( vec3f(1.0f,vec3f(pVelocities[0],pVelocities[1],pVelocities[2] ).length(),1.0f) );
			ori = ori.mult_left ( stretch );
		}

		matrix4f trans;
		trans.set_translate ( vec3f(pPositions[0],pPositions[1],pPositions[2]));
		ori = ori.mult_left ( trans );

		glMultMatrixf ( ori.m );
		glColor4fv ( pColors );

		gMeshes[ l_pPPGParams->PrimitiveType ]->render ((LONG)*pIDs,1);
		pIDs += iIDInc;

		pPositions += 3;
		pVelocities += iVelInc;
		pColors += iColInc;

		glPopMatrix();
	}

	gMeshes[ l_pPPGParams->PrimitiveType ]->unsetState ((OGLParticleAttributeData*)in_pAttributes);

	return true;
}


//*****************************************************************************
// Author : Dominic Laflamme
// Date   : April 2007
// @func  Render billboard using point sprite OGL extension
//
//*****************************************************************************
bool RenderHWAcceleratedSprites(IRTSExecutionState				* in_pExecState,
										XSI_RTS_SystemParams *in_pSysParams, 
										void *in_pParams, 
										XSI_RTS_Primitive	*in_pPrimitive,
										void				*in_pAttributes,
										XSI_RTS_Attribute_Size	*in_pAttributesSize,
										void	**io_pShaderInstanceData ) 
{
	OGLParticle_t* l_pPPGParam = (OGLParticle_t*)in_pParams;
	OGLParticleAttributeData* l_pAttribs = (OGLParticleAttributeData*)in_pAttributes;

	glDepthMask ( GL_FALSE );
	glEnable( GL_DEPTH_TEST );
	glDisable ( GL_LIGHTING );

	if ( l_pPPGParam->PointSize < 0.1f )
		l_pPPGParam->PointSize = 0.1f;

	float att[3] = {l_pPPGParam->Attx, l_pPPGParam->Atty, l_pPPGParam->Attz};

	glPointSize ( l_pPPGParam->PointSize );

	glEnable ( POINT_SPRITE_ARB );
	glDisable ( GL_POINT_SMOOTH );

	glDisable (GL_LIGHTING);
	glEnable ( GL_TEXTURE_2D);
	glDepthMask ( GL_FALSE );
	glTexEnvi(POINT_SPRITE_ARB,COORD_REPLACE_ARB, TRUE );

	if ( in_pSysParams->m_pGLExtFuncs->glPointParameterfEXT )
	{
		in_pSysParams->m_pGLExtFuncs->glPointParameterfEXT(GL_POINT_SIZE_MIN, l_pPPGParam->PointSizeMin);
		in_pSysParams->m_pGLExtFuncs->glPointParameterfEXT(GL_POINT_SIZE_MAX, l_pPPGParam->PointSizeMax);
		in_pSysParams->m_pGLExtFuncs->glPointParameterfvEXT(GL_POINT_DISTANCE_ATTENUATION, att);
		in_pSysParams->m_pGLExtFuncs->glPointParameterfEXT(GL_POINT_FADE_THRESHOLD_SIZE, l_pPPGParam->FadeThreshold );
	}

	glEnableClientState( GL_VERTEX_ARRAY );
	if ( l_pAttribs->m_pColors )
		glEnableClientState( GL_COLOR_ARRAY );

	glDisableClientState ( GL_NORMAL_ARRAY );
	glDisableClientState ( GL_TEXTURE_COORD_ARRAY );
	glDisableClientState ( GL_INDEX_ARRAY );


	glVertexPointer(3, GL_FLOAT,0,l_pAttribs->m_pPositions);
	glColorPointer(4, GL_FLOAT,0,l_pAttribs->m_pColors);

	glDrawArrays ( GL_POINTS, 0, in_pPrimitive->m_NbVertices );

	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_COLOR_ARRAY );
	glDisable ( POINT_SPRITE_ARB );
	glDepthMask ( GL_TRUE );

	return true;
}

//*****************************************************************************
// Author : Dominic Laflamme
// Date   : April 2007
// @func  Render billboards aligned using the CPU
//
//*****************************************************************************
bool RenderBillboardSprites(IRTSExecutionState				* in_pExecState,
										XSI_RTS_SystemParams *in_pSysParams, 
										void *in_pParams, 
										XSI_RTS_Primitive	*in_pPrimitive,
										void				*in_pAttributes,
										XSI_RTS_Attribute_Size	*in_pAttributesSize,
										void	**io_pShaderInstanceData )
{
	OGLParticle_t* l_pPPGParam = (OGLParticle_t*)in_pParams;
	OGLParticleAttributeData* l_pAttribs = (OGLParticleAttributeData*)in_pAttributes;

	if ( !l_pPPGParam->AlphaTest )
	{
		glDepthMask ( GL_FALSE );
	} else {
		glEnable( GL_DEPTH_TEST );
		glAlphaFunc ( l_pPPGParam->AlphaFunc, l_pPPGParam->AlphaRef);
		glEnable ( GL_ALPHA_TEST );
	}

	// make a billboard matrix
	GLfloat camera[16];
	glMatrixMode ( GL_MODELVIEW );
	glGetFloatv(GL_MODELVIEW_MATRIX, camera);
	matrix4f	l_ModelView ( camera );

	vec4f	z ( 0.0f,0.0f,0.0f,1.0f );
	l_ModelView.set_column ( 3, z );

	glDisable ( GL_LIGHTING );
	glEnable ( GL_TEXTURE_2D );
	glBlendFunc(l_pPPGParam->BlendSrc,l_pPPGParam->BlendDest);

	float baseUV = 1.0f / l_pPPGParam->TextureUnitCount;

	for(UINT i = 0; i < in_pPrimitive->m_NbVertices; i++)
	{
		float * ptr = &l_pAttribs->m_pPositions[i*3];
		float * col = NULL;
		float * IDs = NULL;
		float * SpriteAngle = NULL;
		float * Sizes = l_pAttribs->m_pSize;

		if ( l_pAttribs->m_pColors )
			col = &l_pAttribs->m_pColors[i*4];

		float pSize = 1.0f;
		float offsetU = 0;
		float offsetV = 0;

		// which texture unit should we use?
		if ( IDs )
		{
			LONG texUnit = (LONG)(*IDs);
			texUnit = abs(texUnit % (l_pPPGParam->TextureUnitCount*2));

			offsetU = (texUnit % l_pPPGParam->TextureUnitCount) * baseUV;
			offsetV = (texUnit / l_pPPGParam->TextureUnitCount) * baseUV;
		}

		if ( Sizes )
			pSize = (*Sizes);

		vec3f p1 ( pSize , pSize , 0.0f );
		vec3f p2 ( -pSize , pSize , 0.0f ); 
		vec3f p3 ( pSize , -pSize, 0.0f );
		vec3f p4 ( -pSize , -pSize , 0.0f );

		vec3f rp1, rp2, rp3, rp4;

		matrix4f	l_postrot;
		if ( SpriteAngle)
		{
			l_postrot.set_rotation ( vec3f(0.0f,0.0f,(float)DEG_TO_RAD((*SpriteAngle))));
		}

		l_postrot.mult_right (l_ModelView);
		l_postrot.mult_vec_matrix ( p1, rp1 );
		l_postrot.mult_vec_matrix ( p2, rp2 );
		l_postrot.mult_vec_matrix ( p3, rp3 );
		l_postrot.mult_vec_matrix ( p4, rp4 );

		glBegin(GL_TRIANGLE_STRIP);

		if ( col )
			glColor4f ( col[0],col[1],col[2],col[3] );

		glTexCoord2f(baseUV + offsetU, baseUV + offsetV); 
		glVertex3f( rp1[0] + ptr[0], rp1[1] + ptr[1], rp1[2] + ptr[2]);

		glTexCoord2f(offsetU, baseUV + offsetV); 
		glVertex3f( rp2[0] + ptr[0], rp2[1] + ptr[1], rp2[2] + ptr[2]);

		glTexCoord2f(baseUV + offsetU, offsetV); 
		glVertex3f( rp3[0] + ptr[0], rp3[1] + ptr[1], rp3[2] + ptr[2]);

		glTexCoord2f(offsetU, offsetV); 
		glVertex3f( rp4[0] + ptr[0], rp4[1] + ptr[1], rp4[2] + ptr[2]);
		glEnd();

		if ( IDs )
			IDs+=3;
		if ( SpriteAngle )
			SpriteAngle+=3;
		if ( Sizes )
			Sizes+=3;

	}

	return true;
}

//*****************************************************************************
// Author : Dominic Laflamme
// Date   : April 2007
// @func  Renders the cloud using lines showing the velocity with alpha gradient
//
//*****************************************************************************
bool VelocityVectors(IRTSExecutionState				* in_pExecState,
					 XSI_RTS_SystemParams *in_pSysParams, 
					 void *in_pParams, 
					 XSI_RTS_Primitive	*in_pPrimitive,
					 void				*in_pAttributes,
					 XSI_RTS_Attribute_Size	*in_pAttributesSize,
					 void	**io_pShaderInstanceData )
{

	OGLParticle_t* l_pPPGParam = (OGLParticle_t*)in_pParams;
	OGLParticleAttributeData* l_pAttribs = (OGLParticleAttributeData*)in_pAttributes;

	//glDepthMask ( GL_FALSE );
	glEnable( GL_DEPTH_TEST );

	if ( !l_pPPGParam->Textured )
	{
		glDisable ( GL_TEXTURE_2D );
	}

	float * ptr = l_pAttribs->m_pPositions;
	float veli[] = {0,1,0};
	float *vel = &veli[0];
	int incvel = 0;
	int inccol = 0;

	if ( l_pAttribs->m_pVelocities )
	{
		vel = l_pAttribs->m_pVelocities;
		incvel = 3;
	}

	float dcol[] = { 0.0f,0.0f,0.0f,1.0f };

	float * col = NULL;
	if ( l_pAttribs->m_pColors )
	{
		col = l_pAttribs->m_pColors;
		inccol = 4;
	} else {
		col = &dcol[0];
		inccol = 0;
	}
	
	for(UINT i = 0; i < in_pPrimitive->m_NbVertices ; i++)
	{

		glBegin ( GL_LINES );

		glColor4f ( col[0],col[1],col[2],col[3] );
		glTexCoord1f(0.0f);
		glVertex3f( ptr[0], ptr[1], ptr[2] );

		glColor4f ( col[0],col[1],col[2],0.0f );
		glTexCoord1f(1.0f);
		glVertex3f( ptr[0] - vel[0], ptr[1]- vel[1], ptr[2]- vel[2] );

		glEnd();

		ptr+=3;
		vel+=incvel;
		col+=inccol;
		
	}

	return true;
}

//*****************************************************************************
// Author : Dominic Laflamme
// Date   : April 2007
// @func  Renders the clouds using points showing the density encoded in color
// @warning Shader using brute force approach to calculate neighboring distances
//			so, it doesn't scale very well when rendering lots of points :(
//
//*****************************************************************************
bool DensityField(IRTSExecutionState				* in_pExecState,
				  XSI_RTS_SystemParams *in_pSysParams, 
										void *in_pParams, 
										XSI_RTS_Primitive	*in_pPrimitive,
										void				*in_pAttributes,
										XSI_RTS_Attribute_Size	*in_pAttributesSize,
										void	**io_pShaderInstanceData )
{

	OGLParticle_t* l_pPPGParams = (OGLParticle_t*)in_pParams;
	OGLParticleAttributeData* l_pAttribs = (OGLParticleAttributeData*)in_pAttributes;
	PerInstanceData *pThisData = (PerInstanceData*)*io_pShaderInstanceData;	

	glDisable ( GL_TEXTURE_2D);

	if ( l_pPPGParams->PointSize < 0.1f )
		l_pPPGParams->PointSize = 0.1f;

	glPointSize ( l_pPPGParams->PointSize );

	if ( l_pPPGParams->PointSmooth )
	{
		glEnable ( GL_POINT_SMOOTH );
	} else {
		glDisable( GL_POINT_SMOOTH );
	}

	glDisable (GL_LIGHTING);

	glEnableClientState( GL_VERTEX_ARRAY );

	if ( !l_pAttribs->m_pColors )
	{
		if ( pThisData->m_ulDensityCacheSize < in_pPrimitive->m_NbVertices )
		{
			if ( pThisData->m_pDensityCache )
				delete [] pThisData->m_pDensityCache;
		
			long lCacheSize = (long)( (float)in_pPrimitive->m_NbVertices * 0.2f) + in_pPrimitive->m_NbVertices;

			pThisData->m_pDensityCache = new float [ lCacheSize * 4 ];
			pThisData->m_ulDensityCacheSize = lCacheSize;
		}

		l_pAttribs->m_pColors = pThisData->m_pDensityCache;
	} 

	glEnableClientState( GL_COLOR_ARRAY );

	// encode density into colors
	float m_szFactor = 0.0f;
	float m_szSquaredDistance = l_pPPGParams->DensityFalloff;

	for (ULONG u=0;u<in_pPrimitive->m_NbVertices;u++)
	{
		float *t = &l_pAttribs->m_pPositions[u*3];
		float *oc = &l_pAttribs->m_pColors[u*4];
		m_szFactor = 0.0f;

		for (ULONG i=0;i<in_pPrimitive->m_NbVertices;i++)
		{
			float *o = &l_pAttribs->m_pPositions[i*3];

			float r[3];
			r[0] = t[0] - o[0];
			r[1] = t[1] - o[1];
			r[2] = t[2] - o[2];

			r[0] *= r[0];
			r[1] *= r[1];
			r[2] *= r[2];
			float d = m_szSquaredDistance - ( r[0] + r[1] + r[2] );
			if ( d > 0 )
				m_szFactor += d / m_szSquaredDistance;
		}

		float temp = m_szFactor / (float)l_pPPGParams->MaximumDensity;
		if ( temp > 1.0f )
			temp = 1.0f;

		oc[0] = (l_pPPGParams->SparseColor_R*(1.0f-temp)+l_pPPGParams->DenseColor_R*temp);
		oc[1] = (l_pPPGParams->SparseColor_G*(1.0f-temp)+l_pPPGParams->DenseColor_G*temp);
		oc[2] = (l_pPPGParams->SparseColor_B*(1.0f-temp)+l_pPPGParams->DenseColor_B*temp);
		oc[3] = (l_pPPGParams->SparseColor_A*(1.0f-temp)+l_pPPGParams->DenseColor_A*temp);
	}
	glDisableClientState ( GL_NORMAL_ARRAY );
	glDisableClientState ( GL_TEXTURE_COORD_ARRAY );
	glDisableClientState ( GL_INDEX_ARRAY );


	glVertexPointer(3, GL_FLOAT,0,l_pAttribs->m_pPositions);
	glColorPointer(4, GL_FLOAT,0,l_pAttribs->m_pColors);

	glDrawArrays ( GL_POINTS, 0, in_pPrimitive->m_NbVertices );

	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_COLOR_ARRAY );

	return false;
}


//*****************************************************************************
// Author : Dominic Laflamme
// Date   : April 2007
//
//*****************************************************************************
bool LineTrails(IRTSExecutionState				* in_pExecState,
				XSI_RTS_SystemParams *in_pSysParams, 
										void *in_pParams, 
										XSI_RTS_Primitive	*in_pPrimitive,
										void				*in_pAttributes,
										XSI_RTS_Attribute_Size	*in_pAttributesSize,
										void	**io_pShaderInstanceData )
{

	OGLParticle_t		*in_pPPG = (OGLParticle_t*)in_pParams;

	OGLLineTrailData* l_pData = (OGLLineTrailData*) in_pAttributes;
	PerInstanceData *pThisData = (PerInstanceData*)*io_pShaderInstanceData;

	float dcol[] = { 0.0f,0.0f,0.0f,1.0f };
	float tcol[] = { 0.0f,0.0f,0.0f,1.0f };

	float * col = NULL;
	int inccol=0;
	if ( l_pData->m_pColors )
	{
		col = l_pData->m_pColors;
		inccol = 4;
	} else {
		col = &dcol[0];
		inccol = 0;
	}

	if ( in_pPPG->CustomFragmentShader )
	{
		if (pThisData->m_pGLSL)
		{
			pThisData->m_pGLSL->Activate ( true );
			pThisData->m_pGLSL->SetUniforms (in_pExecState);

			
		}
	}

	ULONG arrayCount = in_pAttributesSize[3].m_iArrayCount;


	for(UINT i = 0; i < in_pPrimitive->m_NbVertices ; i++)
	{

		glBegin ( GL_LINE_STRIP );

		glColor4fv ( col );
		glTexCoord2f(0.0f,0.0f);

		glVertex3fv( l_pData->m_pPositions );

		float U = 1.0f / (float)arrayCount;
		float currentU = U;
		for (ULONG s=0;s<(ULONG)arrayCount;s++)
		{
			glTexCoord2f(currentU,0.0f);
			if (l_pData->m_pTrailColors)
			{
				glColor4fv ( l_pData->m_pTrailColors );
				l_pData->m_pTrailColors+=4;
			}
			glVertex3fv( l_pData->m_pTrailPositions );
			l_pData->m_pTrailPositions+=3;
			currentU+=U;
		}
		glEnd();
		l_pData->m_pPositions+=3;
		col+=inccol;
		
	}

	if ( in_pPPG->CustomFragmentShader )
	{
		if (pThisData->m_pGLSL)
		{
			pThisData->m_pGLSL->Activate ( false );
		}
	}

	return false;
}
