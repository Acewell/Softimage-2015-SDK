// CgProgramShader.cpp: implementation of the CgProgramShader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CgProgramShader.h"
#include <Scene.h>
#include <ConnectionPoint.h>
#include <ShaderConnectionPoint.h>
#include <XSIImageLibrary.h>
#include <XSIImage.h>
#include <VariantParameter.h>
#include <CustomPSet.h>

void	Cg_BindMatrix(CgMatrixBind *in_pBindingData);
void	Cg_BindLight(CgLightTrackerBind *in_pBindingData);
void	MatrixTranspose(float in_pSrcM4x4[4][4], float in_pDstM4x4[4][4]);
bool	MatrixInvert(float in_pSrcM4x4[4][4], float in_pDstM4x4[4][4]);
void	MatrixTrackWorld(float in_pDstM4x4[4][4]);
void	MatrixTrackView(float in_pDstM4x4[4][4]);
void	MatrixMultiply(float in_pSrc1M4x4[4][4], float in_pSrc2M4x4[4][4], float in_pDstM4x4[4][4]);


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CgProgramShader::CgProgramShader(CSLXSIShader* in_pShader, Display* in_pDisplay ) : Shader ( in_pShader,in_pDisplay  )
{
	m_cgProfile = CG_PROFILE_UNKNOWN;

	switch(in_pShader->GetParameterList()[3]->GetValue ()->lVal)
	{
		case	0: 	m_cgProfile = CG_PROFILE_ARBVP1; break;
		case	1: 	m_cgProfile = CG_PROFILE_ARBFP1; break;
		case	2: 	m_cgProfile = CG_PROFILE_VP30; break;
		case	3: 	m_cgProfile = CG_PROFILE_FP30; break;
		case	4: 	m_cgProfile = CG_PROFILE_VP20; break;
		case	5: 	m_cgProfile = CG_PROFILE_FP20; break;
	}

	m_cgContext = cgCreateContext();


	char* l_szProgramString = in_pShader->GetParameterList()[4]->GetValue ()->p_cVal;
	m_cgProgram = cgCreateProgram(m_cgContext, CG_SOURCE,l_szProgramString, m_cgProfile, NULL,NULL);

	cgGLLoadProgram(m_cgProgram);

			//
	// Get all uniform parameters
	//

			siviewportsize = cgGetNamedParameter(m_cgProgram, "siviewportsize");
		simodelviewproj = cgGetNamedParameter(m_cgProgram, "simodelviewproj");
		simodelviewprojI = cgGetNamedParameter(m_cgProgram, "simodelviewprojI");
		simodelviewprojT = cgGetNamedParameter(m_cgProgram, "simodelviewprojT");
		simodelviewprojIT = cgGetNamedParameter(m_cgProgram, "simodelviewprojIT");
		simodelview = cgGetNamedParameter(m_cgProgram, "simodelview");
		simodelviewI = cgGetNamedParameter(m_cgProgram, "simodelviewI");
		simodelviewT = cgGetNamedParameter(m_cgProgram, "simodelviewT");
		simodelviewIT = cgGetNamedParameter(m_cgProgram, "simodelviewIT");
		siprojection = cgGetNamedParameter(m_cgProgram, "siprojection");
		siprojectionI = cgGetNamedParameter(m_cgProgram, "siprojectionI");
		siprojectionT = cgGetNamedParameter(m_cgProgram, "siprojectionT");
		siprojectionIT = cgGetNamedParameter(m_cgProgram, "siprojectionIT");
		siview = cgGetNamedParameter(m_cgProgram, "siview");
		siviewI = cgGetNamedParameter(m_cgProgram, "siviewI");
		siviewT = cgGetNamedParameter(m_cgProgram, "siviewT");
		siviewIT = cgGetNamedParameter(m_cgProgram, "siviewIT");
		simodel = cgGetNamedParameter(m_cgProgram, "simodel");
		simodelI = cgGetNamedParameter(m_cgProgram, "simodelI");
		simodelT = cgGetNamedParameter(m_cgProgram, "simodelT");
		simodelIT = cgGetNamedParameter(m_cgProgram, "simodelIT");
		sieyepos = cgGetNamedParameter(m_cgProgram, "sieyepos");

		int loop;
		for(loop = 0; loop < CG_NB_LIGHTS; loop++)
		{
			char	paramName[1024];

			sprintf(paramName, "silighttype_%d", loop);
			silight[loop].silighttype = cgGetNamedParameter(m_cgProgram, paramName);

			sprintf(paramName, "silightambient_%d", loop);
			silight[loop].silightambient = cgGetNamedParameter(m_cgProgram, paramName);

			sprintf(paramName, "silightdiffuse_%d", loop);
			silight[loop].silightdiffuse = cgGetNamedParameter(m_cgProgram, paramName);

			sprintf(paramName, "silightspecular_%d", loop);
			silight[loop].silightspecular = cgGetNamedParameter(m_cgProgram, paramName);

			sprintf(paramName, "silightdirection_%d", loop);
			silight[loop].silightdirection = cgGetNamedParameter(m_cgProgram, paramName);

			sprintf(paramName, "silightposition_%d", loop);
			silight[loop].silightposition = cgGetNamedParameter(m_cgProgram, paramName);

			sprintf(paramName, "silightfalloff_%d", loop);
			silight[loop].silightfalloff = cgGetNamedParameter(m_cgProgram, paramName);

			sprintf(paramName, "silightattenuation_%d", loop);
			silight[loop].silightattenuation = cgGetNamedParameter(m_cgProgram, paramName);

			sprintf(paramName, "silightcone_%d", loop);
			silight[loop].silightcone = cgGetNamedParameter(m_cgProgram, paramName);
		}


}

CgProgramShader::~CgProgramShader()
{

}

void CgProgramShader::execute ()
{

		cgSetErrorCallback(NULL);
		cgGLEnableProfile(m_cgProfile);	
		cgGLBindProgram(m_cgProgram);	

	


		// push viewport size as float4v

		float				l_fvViewport[4];
		CgLightTrackerBind	l_lightBind;
		CgMatrixBind		l_matrixBind;

		glGetFloatv ( GL_VIEWPORT, l_fvViewport );

		if(siviewportsize)
			cgGLSetParameter4fv(siviewportsize, (const float *) l_fvViewport);

		if(simodelviewproj)
		{
			l_matrixBind.variable		= simodelviewproj;
			l_matrixBind.cgType			= 15;
			l_matrixBind.matrix			= 0;
			l_matrixBind.transpose		= FALSE;
			l_matrixBind.invert			= FALSE;
			l_matrixBind.manual_matrix	= NULL;

			Cg_BindMatrix(&l_matrixBind);
		}

		if(simodelviewprojI)
		{
			l_matrixBind.variable		= simodelviewprojI;
			l_matrixBind.cgType			= 15;
			l_matrixBind.matrix			= 0;
			l_matrixBind.transpose		= FALSE;
			l_matrixBind.invert			= TRUE;
			l_matrixBind.manual_matrix	= NULL;

			Cg_BindMatrix(&l_matrixBind);
		}

		if(simodelviewprojT)
		{
			l_matrixBind.variable		= simodelviewprojT;
			l_matrixBind.cgType			= 15;
			l_matrixBind.matrix			= 0;
			l_matrixBind.transpose		= TRUE;
			l_matrixBind.invert			= FALSE;
			l_matrixBind.manual_matrix	= NULL;

			Cg_BindMatrix(&l_matrixBind);
		}

		if(simodelviewprojIT)
		{
			l_matrixBind.variable		= simodelviewprojIT;
			l_matrixBind.cgType			= 15;
			l_matrixBind.matrix			= 0;
			l_matrixBind.transpose		= TRUE;
			l_matrixBind.invert			= TRUE;
			l_matrixBind.manual_matrix	= NULL;

			Cg_BindMatrix(&l_matrixBind);
		}
		
		if(simodelview)
		{
			l_matrixBind.variable		= simodelview;
			l_matrixBind.cgType			= 15;
			l_matrixBind.matrix			= 1;
			l_matrixBind.transpose		= FALSE;
			l_matrixBind.invert			= FALSE;
			l_matrixBind.manual_matrix	= NULL;

			Cg_BindMatrix(&l_matrixBind);
		}

		if( simodelviewI)
		{
			l_matrixBind.variable		=  simodelviewI;
			l_matrixBind.cgType			= 15;
			l_matrixBind.matrix			= 1;
			l_matrixBind.transpose		= FALSE;
			l_matrixBind.invert			= TRUE;
			l_matrixBind.manual_matrix	= NULL;

			Cg_BindMatrix(&l_matrixBind);
		}

		if( simodelviewT)
		{
			l_matrixBind.variable		=  simodelviewT;
			l_matrixBind.cgType			= 15;
			l_matrixBind.matrix			= 1;
			l_matrixBind.transpose		= TRUE;
			l_matrixBind.invert			= FALSE;
			l_matrixBind.manual_matrix	= NULL;

			Cg_BindMatrix(&l_matrixBind);
		}

		if( simodelviewIT)
		{
			l_matrixBind.variable		=  simodelviewIT;
			l_matrixBind.cgType			= 15;
			l_matrixBind.matrix			= 1;
			l_matrixBind.transpose		= TRUE;
			l_matrixBind.invert			= TRUE;
			l_matrixBind.manual_matrix	= NULL;

			Cg_BindMatrix(&l_matrixBind);
		}

		if( siprojection)
		{
			l_matrixBind.variable		=  siprojection;
			l_matrixBind.cgType			= 15;
			l_matrixBind.matrix			= 2;
			l_matrixBind.transpose		= FALSE;
			l_matrixBind.invert			= FALSE;
			l_matrixBind.manual_matrix	= NULL;

			Cg_BindMatrix(&l_matrixBind);
		}

		if( siprojectionI)
		{
			l_matrixBind.variable		=  siprojectionI;
			l_matrixBind.cgType			= 15;
			l_matrixBind.matrix			= 2;
			l_matrixBind.transpose		= FALSE;
			l_matrixBind.invert			= TRUE;
			l_matrixBind.manual_matrix	= NULL;

			Cg_BindMatrix(&l_matrixBind);
		}

		if( siprojectionT)
		{
			l_matrixBind.variable		=  siprojectionT;
			l_matrixBind.cgType			= 15;
			l_matrixBind.matrix			= 2;
			l_matrixBind.transpose		= TRUE;
			l_matrixBind.invert			= FALSE;
			l_matrixBind.manual_matrix	= NULL;

			Cg_BindMatrix(&l_matrixBind);
		}

		if( siprojectionIT)
		{
			l_matrixBind.variable		=  siprojectionIT;
			l_matrixBind.cgType			= 15;
			l_matrixBind.matrix			= 2;
			l_matrixBind.transpose		= TRUE;
			l_matrixBind.invert			= TRUE;
			l_matrixBind.manual_matrix	= NULL;

			Cg_BindMatrix(&l_matrixBind);
		}

		if( siview)
		{
			l_matrixBind.variable		=  siview;
			l_matrixBind.cgType			= 15;
			l_matrixBind.matrix			= 3;
			l_matrixBind.transpose		= FALSE;
			l_matrixBind.invert			= FALSE;
			l_matrixBind.manual_matrix	= NULL;

			Cg_BindMatrix(&l_matrixBind);
		}

		if( siviewI)
		{
			l_matrixBind.variable		=  siviewI;
			l_matrixBind.cgType			= 15;
			l_matrixBind.matrix			= 3;
			l_matrixBind.transpose		= FALSE;
			l_matrixBind.invert			= TRUE;
			l_matrixBind.manual_matrix	= NULL;

			Cg_BindMatrix(&l_matrixBind);
		}

		if( siviewT)
		{
			l_matrixBind.variable		=  siviewT;
			l_matrixBind.cgType			= 15;
			l_matrixBind.matrix			= 3;
			l_matrixBind.transpose		= TRUE;
			l_matrixBind.invert			= FALSE;
			l_matrixBind.manual_matrix	= NULL;

			Cg_BindMatrix(&l_matrixBind);
		}

		if( siviewIT)
		{
			l_matrixBind.variable		=  siviewIT;
			l_matrixBind.cgType			= 15;
			l_matrixBind.matrix			= 3;
			l_matrixBind.transpose		= TRUE;
			l_matrixBind.invert			= TRUE;
			l_matrixBind.manual_matrix	= NULL;

			Cg_BindMatrix(&l_matrixBind);
		}

		if( simodel)
		{
			l_matrixBind.variable		=  simodel;
			l_matrixBind.cgType			= 15;
			l_matrixBind.matrix			= 4;
			l_matrixBind.transpose		= FALSE;
			l_matrixBind.invert			= FALSE;
			l_matrixBind.manual_matrix	= NULL;

			Cg_BindMatrix(&l_matrixBind);
		}

		if( simodelI)
		{
			l_matrixBind.variable		=  simodelI;
			l_matrixBind.cgType			= 15;
			l_matrixBind.matrix			= 4;
			l_matrixBind.transpose		= FALSE;
			l_matrixBind.invert			= TRUE;
			l_matrixBind.manual_matrix	= NULL;

			Cg_BindMatrix(&l_matrixBind);
		}

		if( simodelT)
		{
			l_matrixBind.variable		=  simodelT;
			l_matrixBind.cgType			= 15;
			l_matrixBind.matrix			= 4;
			l_matrixBind.transpose		= TRUE;
			l_matrixBind.invert			= FALSE;
			l_matrixBind.manual_matrix	= NULL;

			Cg_BindMatrix(&l_matrixBind);
		}

		if( simodelIT)
		{
			l_matrixBind.variable		=  simodelIT;
			l_matrixBind.cgType			= 15;
			l_matrixBind.matrix			= 4;
			l_matrixBind.transpose		= TRUE;
			l_matrixBind.invert			= TRUE;
			l_matrixBind.manual_matrix	= NULL;

			Cg_BindMatrix(&l_matrixBind);
		}
		
		
		if( sieyepos)
		{
		//	cgGLSetParameter4fv( sieyepos, (const float *) &in_pSysParams->m_SceneData->m_sCamera.m_mMatrix[12]);		
		}

		int loop;
		for(loop = 0; loop < CG_NB_LIGHTS; loop++)
		{
			if( silight[loop].silighttype)
			{
				l_lightBind.Type = TRUE;
				l_lightBind.Constant_Register_Type =  silight[loop].silighttype;
			}
			else
			{
				l_lightBind.Type = FALSE;
			}

			if( silight[loop].silightambient)
			{
				l_lightBind.Ambient = TRUE;
				l_lightBind.Constant_Register_Ambient =  silight[loop].silightambient;
			}
			else
			{
				l_lightBind.Ambient = FALSE;
			}

			if( silight[loop].silightdiffuse)
			{
				l_lightBind.Diffuse = TRUE;
				l_lightBind.Constant_Register_Diffuse =  silight[loop].silightdiffuse;
			}
			else
			{
				l_lightBind.Diffuse = FALSE;
			}

			if( silight[loop].silightspecular)
			{
				l_lightBind.Specular = TRUE;
				l_lightBind.Constant_Register_Specular =  silight[loop].silightspecular;
			}
			else
			{
				l_lightBind.Specular = FALSE;
			}

			if( silight[loop].silightdirection)
			{
				l_lightBind.Direction = TRUE;
				l_lightBind.Constant_Register_Direction =  silight[loop].silightdirection;
			}
			else
			{
				l_lightBind.Direction = FALSE;
			}

			if( silight[loop].silightposition)
			{
				l_lightBind.Position = TRUE;
				l_lightBind.Constant_Register_Position =  silight[loop].silightposition;
			}
			else
			{
				l_lightBind.Position = FALSE;
			}

			if( silight[loop].silightfalloff)
			{
				l_lightBind.Falloff = TRUE;
				l_lightBind.Constant_Register_Falloff =  silight[loop].silightfalloff;
			}
			else
			{
				l_lightBind.Falloff = FALSE;
			}

			if( silight[loop].silightattenuation)
			{
				l_lightBind.Attenuation = TRUE;
				l_lightBind.Constant_Register_Attenuation =  silight[loop].silightattenuation;
			}
			else
			{
				l_lightBind.Attenuation = FALSE;
			}

			if( silight[loop].silightcone)
			{
				l_lightBind.Cone = TRUE;
				l_lightBind.Constant_Register_Cone =  silight[loop].silightcone;
			}
			else
			{
				l_lightBind.Cone = FALSE;

			}

			l_lightBind.LightID = loop;
			Cg_BindLight(&l_lightBind);
		}

		//
		// handle uniform parameters
		//

		for (int v=0;v<m_pShader->GetCustomPSetCount();v++)
		{
			CSLCustomPSet* l_pPset = m_pShader->GetCustomPSetList()[v];

			for (int c=0;c<l_pPset->GetParameterCount();c++)
			{
				CSLVariantParameter* l_pVar = l_pPset->GetParameterList()[c];
				CGparameter Param;

				char fullname[MAX_PATH];
				char* psetName = NULL;
				strcpy ( fullname, l_pPset->GetName() );
				psetName = strrchr ( fullname, '.' );

				if ( psetName == NULL )
				{
					psetName = fullname;
				} else {

					psetName++;
				}

				sprintf ( fullname,"%s_%s", psetName, l_pVar->GetName());

				Param = cgGetNamedParameter(m_cgProgram, fullname);
				float fValue = l_pVar->GetValue()->dVal;
				cgGLSetParameter1f(Param, fValue);
			}
		
		}
}

void CgProgramShader::enable ( bool in_bEnable )
{
	if ( !in_bEnable )
	{
		cgGLDisableProfile(m_cgProfile);
	}

}


void			Cg_BindMatrix(CgMatrixBind *in_pBindingData)
{
	if(in_pBindingData->variable != NULL)
	{
		CGGLenum	matrixType;
		CGGLenum	transform = CG_GL_MATRIX_IDENTITY;

		float	finalMatrix[4][4];

		switch(in_pBindingData->matrix)
		{
			case 0: matrixType = CG_GL_MODELVIEW_PROJECTION_MATRIX; break;
			case 1: matrixType = CG_GL_MODELVIEW_MATRIX; break;
			case 2: matrixType = CG_GL_PROJECTION_MATRIX; break;

			case 3:	MatrixTrackView(finalMatrix);
					break;
			case 4:	MatrixTrackWorld(finalMatrix);
					break;

		}

		if(in_pBindingData->invert)
		{
			transform = CG_GL_MATRIX_INVERSE;
		}

		if(in_pBindingData->transpose)
		{
			if(in_pBindingData->invert)
			{
				transform = CG_GL_MATRIX_INVERSE_TRANSPOSE;
			}
			else
			{
				transform = CG_GL_MATRIX_TRANSPOSE;
			}
		}

		if(in_pBindingData->matrix < 3)
		{
			cgGLSetStateMatrixParameter(in_pBindingData->variable, matrixType, transform);
		}
		else
		{	
			if(in_pBindingData->invert)
				MatrixInvert(finalMatrix, finalMatrix);

			if(in_pBindingData->transpose)
				MatrixTranspose(finalMatrix, finalMatrix);

			float	matrix[16];
			int		x,y;

			switch(in_pBindingData->cgType)
			{
				case 0	: x = 1; y = 1;break;
				case 1	: x = 1; y = 2;break;
				case 2	: x = 1; y = 3;break;
				case 3	: x = 1; y = 4;break;
				case 4	: x = 2; y = 1;break;
				case 5	: x = 2; y = 2;break;
				case 6	: x = 2; y = 3;break;
				case 7	: x = 2; y = 4;break;
				case 8	: x = 3; y = 1;break;
				case 9	: x = 3; y = 2;break;
				case 10	: x = 3; y = 3;break;
				case 11	: x = 3; y = 4;break;
				case 12	: x = 4; y = 1;break;
				case 13	: x = 4; y = 2;break;
				case 14	: x = 4; y = 3;break;
				case 15	: x = 4; y = 4;break;
			}

			int loopx,loopy;

			for(loopy = 0; loopy < y; loopy++)
			{
				for(loopx = 0; loopx < x; loopx++)
				{
					matrix[loopx + (loopy * x)] = finalMatrix[loopy][loopx];
				}
			}

			cgGLSetMatrixParameterfr(in_pBindingData->variable, matrix);
		}
	}
}

void			Cg_BindLight(CgLightTrackerBind *in_pBindingData)
{
	float	fValues[4];
	float	pvector[4];
	int		type;
	float	direction[4];

	int		id = 0, idcheck = 0;
	bool	enabled = FALSE;

	// let's scan the for a light that is enabled

	for(id = 0; id < 7; id++)
	{
		if(glIsEnabled(GL_LIGHT0 + id))			
		{	
			if(idcheck == in_pBindingData->LightID)
			{
				break;
			}
			else
			{
				idcheck ++;
			}
		}
	}


	if(id < 7)
	{
		enabled = glIsEnabled(GL_LIGHT0 + id) ? TRUE : FALSE;
	}
	else
	{
		enabled = FALSE;
	}

	// track ambient
	if(in_pBindingData->Ambient && in_pBindingData->Constant_Register_Ambient)
	{
		if(enabled)
		{
			glGetLightfv(GL_LIGHT0 + id, GL_AMBIENT, fValues);
		}
		else
		{
			fValues[0] = fValues[1] = fValues[2] = fValues[3] = 0.0f;			
		}
		cgGLSetParameter4fv(in_pBindingData->Constant_Register_Ambient, fValues);
	}

	// track diffuse 
	if(in_pBindingData->Diffuse && in_pBindingData->Constant_Register_Diffuse)
	{
		if(enabled)
		{
			glGetLightfv(GL_LIGHT0 + id, GL_DIFFUSE, fValues);
		}
		else
		{
			fValues[0] = fValues[1] = fValues[2] = fValues[3] = 0.0f;			
		}
		cgGLSetParameter4fv(in_pBindingData->Constant_Register_Diffuse, fValues);
	}

	// track specular
	if(in_pBindingData->Specular && in_pBindingData->Constant_Register_Specular)
	{
		if(enabled)
		{
			glGetLightfv(GL_LIGHT0 + id, GL_SPECULAR, fValues);
		}
		else
		{
			fValues[0] = fValues[1] = fValues[2] = fValues[3] = 0.0f;			
		}
		cgGLSetParameter4fv(in_pBindingData->Constant_Register_Specular, fValues);
	}

	// track position (and type)
	glGetLightfv(GL_LIGHT0 + id, GL_POSITION, pvector);

	if(pvector[3] == 0.0f)
	{
		type = 0; // DIRECTIONAL

		// track direction for directional light
		if(in_pBindingData->Direction && in_pBindingData->Constant_Register_Direction)
		{
			cgGLSetParameter4fv(in_pBindingData->Constant_Register_Direction, pvector);
		}
	}
	else
	{
		// track position for other lights
		if(in_pBindingData->Position && in_pBindingData->Constant_Register_Position)
		{
			cgGLSetParameter4fv(in_pBindingData->Constant_Register_Position, pvector);
		}

		// track cutoff (and type)
		glGetLightfv(GL_LIGHT0 + id, GL_SPOT_CUTOFF, fValues);

		if(fValues[0] >= 180.0f)
		{
			type = 1; // POINT
		}
		else
		{
			type = 2; // SPOT

			// track spot direction
			glGetLightfv(GL_LIGHT0 + id, GL_SPOT_DIRECTION, direction);

			// track direction for directional light
			if(in_pBindingData->Direction && in_pBindingData->Constant_Register_Direction)
			{
				cgGLSetParameter4fv(in_pBindingData->Constant_Register_Direction, direction);
			}

			// track falloff
			if(in_pBindingData->Falloff && in_pBindingData->Constant_Register_Falloff)
			{
				glGetLightfv(GL_LIGHT0 + id, GL_SPOT_EXPONENT, fValues);
				cgGLSetParameter4fv(in_pBindingData->Constant_Register_Falloff, fValues);
			}

			// track cone
			if(in_pBindingData->Cone && in_pBindingData->Constant_Register_Cone)
			{
				glGetLightfv(GL_LIGHT0 + id, GL_SPOT_CUTOFF, fValues);
				cgGLSetParameter4fv(in_pBindingData->Constant_Register_Cone, fValues);
			}
		}
	}

	if(in_pBindingData->Type && in_pBindingData->Constant_Register_Type)
	{
		fValues[0] = fValues[1] = fValues[2] = fValues[3] = (float) type;
		cgGLSetParameter4fv(in_pBindingData->Constant_Register_Type, fValues);
	}

	if(in_pBindingData->Attenuation && in_pBindingData->Constant_Register_Attenuation)
	{
		glGetLightfv(GL_LIGHT0 + id, GL_CONSTANT_ATTENUATION, &fValues[0]);
		glGetLightfv(GL_LIGHT0 + id, GL_LINEAR_ATTENUATION, &fValues[1]);
		glGetLightfv(GL_LIGHT0 + id, GL_QUADRATIC_ATTENUATION, &fValues[2]);
		cgGLSetParameter4fv(in_pBindingData->Constant_Register_Attenuation, fValues);
	}

}

void   MatrixTranspose(float in_pSrcM4x4[4][4], float in_pDstM4x4[4][4])
{
	float	tmpMatrix[4][4];

	memcpy(tmpMatrix, in_pSrcM4x4, sizeof(float) * 16);
	in_pDstM4x4[0][0] = tmpMatrix[0][0];
	in_pDstM4x4[0][1] = tmpMatrix[1][0];
	in_pDstM4x4[0][2] = tmpMatrix[2][0];
	in_pDstM4x4[0][3] = tmpMatrix[3][0];

	in_pDstM4x4[1][0] = tmpMatrix[0][1];
	in_pDstM4x4[1][1] = tmpMatrix[1][1];
	in_pDstM4x4[1][2] = tmpMatrix[2][1];
	in_pDstM4x4[1][3] = tmpMatrix[3][1];

	in_pDstM4x4[2][0] = tmpMatrix[0][2];
	in_pDstM4x4[2][1] = tmpMatrix[1][2];
	in_pDstM4x4[2][2] = tmpMatrix[2][2];
	in_pDstM4x4[2][3] = tmpMatrix[3][2];

	in_pDstM4x4[3][0] = tmpMatrix[0][3];
	in_pDstM4x4[3][1] = tmpMatrix[1][3];
	in_pDstM4x4[3][2] = tmpMatrix[2][3];
	in_pDstM4x4[3][3] = tmpMatrix[3][3];
}

bool   MatrixInvert(float in_pSrcM4x4[4][4], float in_pDstM4x4[4][4])
{
   double   sys[ 4 ][ 8 ];
   int		i,  j,  k;
   double   temp;

   for( i = 0; i < 4; i++ )
      for( j = 0; j < 4; j++ )
      {
         sys[ i ][ j ] = in_pSrcM4x4[i][j];
         sys[ i ][ j + 4 ] = (float) ( i == j );
      }
   
   for( j = 0; j < 4; j++ )
   {
      if( fabs( sys[ j ][ j ] ) < SI_HEXA_EPS )
      {
         for( i = j + 1; 
	      ( i < 4 ) && ( fabs ( sys[ i ][ j ] ) < SI_HEXA_EPS );
	       i++ ) {};
	       
         if( i == 4 )
            return( FALSE );
         else
            for( k = 0; k < 8; k++ )
            {
               temp = sys[ i ][ k ];
               sys[ i ][ k ] = sys[ j ][ k ];
               sys[ j ][ k ] = temp;
            }
      }
      temp = 1.0 / sys[ j ][ j ];
      for( i = 0; i < 8; i++ )
         sys[ j ][ i ] *= temp;
      for( i = 0; i < 4; i++ )
         if( i != j )
         {
            temp = - sys[ i ][ j ];
            for( k = 0; k < 8; k++ )
               sys[ i ][ k ] += sys[ j ][ k ] * temp;
         }
   }

   for( i = 0; i < 4; i++ )
      for( j = 0; j < 4; j++ )
         in_pDstM4x4[i][j] = (float)sys[ i ][ j + 4];

	return TRUE;
}

void	MatrixTrackWorld(float in_pDstM4x4[4][4])
{
	float l_mWorldMatrix[4][4];
	float l_mInvView[4][4];
	float l_mView[4][4];

	// track the world matrix
	glGetFloatv(GL_MODELVIEW_MATRIX, (float*) l_mWorldMatrix);

	MatrixTrackView(l_mView);
	MatrixInvert(l_mView, l_mInvView);

	// now compute the local world matrix
	MatrixMultiply(l_mWorldMatrix, l_mInvView, in_pDstM4x4);
}

void	MatrixTrackView(float in_pDstM4x4[4][4])
{
	float	l_mCurrMatrix[4][4];

	// This is Softimage specific

	glMatrixMode(GL_MODELVIEW);
	glGetFloatv(GL_MODELVIEW_MATRIX, (float*) l_mCurrMatrix);
	glPopMatrix();
	glGetFloatv(GL_MODELVIEW_MATRIX, (float*) in_pDstM4x4);
	glPushMatrix();
	glLoadMatrixf((float*) l_mCurrMatrix);
}

void MatrixMultiply(float in_pSrc1M4x4[4][4], float in_pSrc2M4x4[4][4], float in_pDstM4x4[4][4])
{
	float *a = (float*)in_pSrc2M4x4,*b = (float*)in_pSrc1M4x4,*c = (float*)in_pDstM4x4;

	*c = b[0]*a[0] + b[1]*a[4] + b[2]*a[8] + b[3]*a[12];   c++;
	*c = b[0]*a[1] + b[1]*a[5] + b[2]*a[9] + b[3]*a[13];   c++;
	*c = b[0]*a[2] + b[1]*a[6] + b[2]*a[10] + b[3]*a[14];   c++;
	*c = b[0]*a[3] + b[1]*a[7] + b[2]*a[11] + b[3]*a[15];   c++;
	
	*c = b[4]*a[0] + b[5]*a[4] + b[6]*a[8] + b[7]*a[12];   c++;
	*c = b[4]*a[1] + b[5]*a[5] + b[6]*a[9] + b[7]*a[13];   c++;
	*c = b[4]*a[2] + b[5]*a[6] + b[6]*a[10] + b[7]*a[14];   c++;
	*c = b[4]*a[3] + b[5]*a[7] + b[6]*a[11] + b[7]*a[15];   c++;
	
	*c = b[8]*a[0] + b[9]*a[4] + b[10]*a[8] + b[11]*a[12];   c++;
	*c = b[8]*a[1] + b[9]*a[5] + b[10]*a[9] + b[11]*a[13];   c++;
	*c = b[8]*a[2] + b[9]*a[6] + b[10]*a[10] + b[11]*a[14];   c++;
	*c = b[8]*a[3] + b[9]*a[7] + b[10]*a[11] + b[11]*a[15];   c++;
	
	*c = b[12]*a[0] + b[13]*a[4] + b[14]*a[8] + b[15]*a[12];   c++;
	*c = b[12]*a[1] + b[13]*a[5] + b[14]*a[9] + b[15]*a[13];   c++;
	*c = b[12]*a[2] + b[13]*a[6] + b[14]*a[10] + b[15]*a[14];   c++;
	*c = b[12]*a[3] + b[13]*a[7] + b[14]*a[11] + b[15]*a[15];   

}
