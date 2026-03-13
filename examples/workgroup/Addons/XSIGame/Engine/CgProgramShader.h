// CgProgramShader.h: interface for the CgProgramShader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CGPROGRAMSHADER_H__32113F04_6978_4794_9C6D_8635C17710E1__INCLUDED_)
#define AFX_CGPROGRAMSHADER_H__32113F04_6978_4794_9C6D_8635C17710E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Engine.h"
#include "Shader.h"
#include <cg\cg.h>
#include <cg\cggl.h>

#define CG_NB_LIGHTS	7

typedef struct tagCgLightTrackerBind
{
	LONG			LightID;
	LONG			Type; 
	CGparameter		Constant_Register_Type;
	LONG			Diffuse; 
	CGparameter		Constant_Register_Diffuse;
	LONG			Specular; 
	CGparameter		Constant_Register_Specular;
	LONG			Ambient; 
	CGparameter		Constant_Register_Ambient;
	LONG			Position; 
	CGparameter		Constant_Register_Position;
	LONG			Direction; 
	CGparameter		Constant_Register_Direction;
	LONG			Falloff; 
	CGparameter		Constant_Register_Falloff;
	LONG			Attenuation; 
	CGparameter		Constant_Register_Attenuation;
	LONG			Cone; 
	CGparameter		Constant_Register_Cone;
} CgLightTrackerBind;

typedef struct tagCgMatrixBind
{
	CGparameter	variable;
	LONG		matrix;
	LONG		cgType;
	LONG		transpose;
	LONG		invert;
	float		*manual_matrix;
} CgMatrixBind;

typedef struct tagCgAutoLightTracking
{
	CGparameter		silighttype;
	CGparameter		silightambient;
	CGparameter		silightdiffuse;
	CGparameter		silightspecular;
	CGparameter		silightposition;
	CGparameter		silightdirection;
	CGparameter		silightfalloff;
	CGparameter		silightattenuation;
	CGparameter		silightcone;
} CgAutoLightTracking;

class ENGINE_API CgProgramShader : public Shader  
{
public:
	CgProgramShader(CSLXSIShader* in_pShader, Display* in_pDisplay );
	virtual ~CgProgramShader();

	virtual void execute ();
	virtual void enable ( bool );

private:
	CGcontext   m_cgContext;
	CGprogram	m_cgProgram;
	CGprofile   m_cgProfile;

	CGparameter				siviewportsize;
	CGparameter				simodelviewproj;
	CGparameter				simodelviewprojI;
	CGparameter				simodelviewprojT;
	CGparameter				simodelviewprojIT;
	CGparameter				simodelview;
	CGparameter				simodelviewI;
	CGparameter				simodelviewT;
	CGparameter				simodelviewIT;
	CGparameter				siprojection;
	CGparameter				siprojectionI;
	CGparameter				siprojectionT;
	CGparameter				siprojectionIT;
	CGparameter				siview;
	CGparameter				siviewI;
	CGparameter				siviewT;
	CGparameter				siviewIT;
	CGparameter				simodel;
	CGparameter				simodelI;
	CGparameter				simodelT;
	CGparameter				simodelIT;
	CGparameter				sieyepos;
	CgAutoLightTracking		silight[CG_NB_LIGHTS];
};

#endif // !defined(AFX_CGPROGRAMSHADER_H__32113F04_6978_4794_9C6D_8635C17710E1__INCLUDED_)
