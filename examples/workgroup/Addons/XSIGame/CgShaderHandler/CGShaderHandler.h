// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the CGSHADERHANDLER_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// CGSHADERHANDLER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef CGSHADERHANDLER_EXPORTS
#define CGSHADERHANDLER_API __declspec(dllexport)
#else
#define CGSHADERHANDLER_API __declspec(dllimport)
#endif

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

extern "C"	CGSHADERHANDLER_API const char*	GetHandlerProgID();
extern "C"	CGSHADERHANDLER_API Shader*		CreateShader(CSLXSIShader* in_pShader, Display* in_pDisplay);

class CGSHADERHANDLER_API	CGShader : public Shader
{
public:
	CGShader ( CSLXSIShader* in_pShader, Display* in_pDisplay );
	virtual ~CGShader();

	virtual void execute ();
	virtual void enable ( bool );
	virtual int	 UVstages(); 

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

