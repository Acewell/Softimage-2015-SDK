//***************************************************************************************
//
// (c) Copyright 2008 Autodesk, Inc. All rights reserved.
//
//***************************************************************************************

//***************************************************************************************
/*!
   \file XSI_rtshaders.h
   \brief Realtime Shaders API v3.0 documentation

   Copyright 2009 Autodesk, Inc.  All rights reserved.

   Use of this software is subject to the terms of the Autodesk license agreement provided
   at the time of installation or download, or which otherwise accompanies this software in
   either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef XSI_RTSHADERS_H
#define XSI_RTSHADERS_H

#include <GL/gl.h>
#include <assert.h>
#ifdef linux
 #undef GL_VERSION_1_2
 #undef GL_VERSION_1_3
 #undef __glext_h_
 #undef GL_ARB_multitexture
 #undef GL_ATI_vertex_array_object

 #if defined(__x86_64)
  typedef unsigned long ULONG_PTR;
  #ifndef ULONG
   typedef unsigned int ULONG;
  #endif
  #ifndef UINT
   typedef unsigned int UINT;
  #endif
  #ifndef LONG
   typedef int LONG;
  #endif
 #else // defined(__x86_64)
  typedef unsigned long ULONG_PTR;
  #ifndef ULONG
   typedef unsigned long ULONG;
  #endif
  #ifndef LONG
   typedef long LONG;
  #endif
 #endif //__x86_64
 #define _strnicmp strncasecmp
 #define _stricmp  strcasecmp
 #ifdef XSI_USE_INTERNAL_GLEXT
  #include <glh/glext.h>
 #else
  #include <GL/glext.h>
 #endif
 #include <limits.h>
#else
 #include <glh/glext.h>
#endif // linux

#include <assert.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <SIBCArray.h>
#include <string.h>
#include <xsi_decl.h>
#ifdef linux
#define _strnicmp strncasecmp
#define _stricmp  strcasecmp
#endif

// Extra extensions added for Softimage 6.0
typedef char GLcharARB;
typedef unsigned int GLhandleARB;
typedef void (APIENTRY * PFNGLDELETEFRAMEBUFFERSEXTPROC) (GLsizei n, const GLuint* framebuffers);
typedef void (APIENTRY * PFNGLDELETERENDERBUFFERSEXTPROC) (GLsizei n, const GLuint* renderbuffers);
typedef void (APIENTRY * PFNGLGENFRAMEBUFFERSEXTPROC) (GLsizei n, GLuint* framebuffers);
typedef void (APIENTRY * PFNGLGENRENDERBUFFERSEXTPROC) (GLsizei n, GLuint* renderbuffers);
typedef void (APIENTRY * PFNGLDELETEBUFFERSARBPROC) (GLsizei n, const GLuint* buffers);
typedef void (APIENTRY * PFNGLGENBUFFERSARBPROC) (GLsizei n, GLuint* buffers);
typedef GLuint (APIENTRY * PFNGLCREATEPROGRAMOBJECTARBPROC) (void);
typedef void (APIENTRY * PFNGLDELETEOBJECTARBPROC) (GLuint obj);
typedef void (APIENTRY * PFNGLBINDFRAMEBUFFEREXTPROC) (GLenum target, GLuint framebuffer);
typedef void (APIENTRY * PFNGLBINDBUFFERARBPROC) (GLenum target, GLuint buffer);
typedef void (APIENTRY * PFNGLBUFFERDATAARBPROC) (GLenum target, GLsizeiptrARB size, const GLvoid* data, GLenum usage);
typedef GLboolean (APIENTRY * PFNGLISBUFFERARBPROC) (GLuint buffer);
typedef GLvoid * (APIENTRY * PFNGLMAPBUFFERARBPROC) (GLenum target, GLenum access);
typedef GLboolean (APIENTRY * PFNGLUNMAPBUFFERARBPROC) (GLenum target);
typedef void (APIENTRY * PFNGLGETBUFFERPARAMETERIVARBPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRY * PFNGLATTACHOBJECTARBPROC) (GLhandleARB containerObj, GLhandleARB obj);
typedef void (APIENTRY * PFNGLCOMPILESHADERARBPROC) (GLhandleARB shaderObj);
typedef GLhandleARB (APIENTRY * PFNGLCREATEPROGRAMOBJECTARBPROC) (void);
typedef GLhandleARB (APIENTRY * PFNGLCREATESHADEROBJECTARBPROC) (GLenum shaderType);
typedef void (APIENTRY * PFNGLDELETEOBJECTARBPROC) (GLhandleARB obj);
typedef void (APIENTRY * PFNGLDETACHOBJECTARBPROC) (GLhandleARB containerObj, GLhandleARB attachedObj);
typedef void (APIENTRY * PFNGLGETACTIVEUNIFORMARBPROC) (GLhandleARB programObj, GLuint index, GLsizei maxLength, GLsizei* length, GLint *size, GLenum *type, GLcharARB *name);
typedef void (APIENTRY * PFNGLGETATTACHEDOBJECTSARBPROC) (GLhandleARB containerObj, GLsizei maxCount, GLsizei* count, GLhandleARB *obj);
typedef GLhandleARB (APIENTRY * PFNGLGETHANDLEARBPROC) (GLenum pname);
typedef void (APIENTRY * PFNGLGETINFOLOGARBPROC) (GLhandleARB obj, GLsizei maxLength, GLsizei* length, GLcharARB *infoLog);
typedef void (APIENTRY * PFNGLGETOBJECTPARAMETERFVARBPROC) (GLhandleARB obj, GLenum pname, GLfloat* params);
typedef void (APIENTRY * PFNGLGETOBJECTPARAMETERIVARBPROC) (GLhandleARB obj, GLenum pname, GLint* params);
typedef void (APIENTRY * PFNGLGETSHADERSOURCEARBPROC) (GLhandleARB obj, GLsizei maxLength, GLsizei* length, GLcharARB *source);
typedef GLint (APIENTRY * PFNGLGETUNIFORMLOCATIONARBPROC) (GLhandleARB programObj, const GLcharARB* name);
typedef void (APIENTRY * PFNGLGETUNIFORMFVARBPROC) (GLhandleARB programObj, GLint location, GLfloat* params);
typedef void (APIENTRY * PFNGLGETUNIFORMIVARBPROC) (GLhandleARB programObj, GLint location, GLint* params);
typedef void (APIENTRY * PFNGLLINKPROGRAMARBPROC) (GLhandleARB programObj);
typedef void (APIENTRY * PFNGLSHADERSOURCEARBPROC) (GLhandleARB shaderObj, GLsizei count, const GLcharARB ** string, const GLint *length);
typedef void (APIENTRY * PFNGLUNIFORM1FARBPROC) (GLint location, GLfloat v0);
typedef void (APIENTRY * PFNGLUNIFORM1FVARBPROC) (GLint location, GLsizei count, const GLfloat* value);
typedef void (APIENTRY * PFNGLUNIFORM1IARBPROC) (GLint location, GLint v0);
typedef void (APIENTRY * PFNGLUNIFORM1IVARBPROC) (GLint location, GLsizei count, const GLint* value);
typedef void (APIENTRY * PFNGLUNIFORM2FARBPROC) (GLint location, GLfloat v0, GLfloat v1);
typedef void (APIENTRY * PFNGLUNIFORM2FVARBPROC) (GLint location, GLsizei count, const GLfloat* value);
typedef void (APIENTRY * PFNGLUNIFORM2IARBPROC) (GLint location, GLint v0, GLint v1);
typedef void (APIENTRY * PFNGLUNIFORM2IVARBPROC) (GLint location, GLsizei count, const GLint* value);
typedef void (APIENTRY * PFNGLUNIFORM3FARBPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (APIENTRY * PFNGLUNIFORM3FVARBPROC) (GLint location, GLsizei count, const GLfloat* value);
typedef void (APIENTRY * PFNGLUNIFORM3IARBPROC) (GLint location, GLint v0, GLint v1, GLint v2);
typedef void (APIENTRY * PFNGLUNIFORM3IVARBPROC) (GLint location, GLsizei count, const GLint* value);
typedef void (APIENTRY * PFNGLUNIFORM4FARBPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (APIENTRY * PFNGLUNIFORM4FVARBPROC) (GLint location, GLsizei count, const GLfloat* value);
typedef void (APIENTRY * PFNGLUNIFORM4IARBPROC) (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (APIENTRY * PFNGLUNIFORM4IVARBPROC) (GLint location, GLsizei count, const GLint* value);
typedef void (APIENTRY * PFNGLUNIFORMMATRIX2FVARBPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (APIENTRY * PFNGLUNIFORMMATRIX3FVARBPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (APIENTRY * PFNGLUNIFORMMATRIX4FVARBPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (APIENTRY * PFNGLUSEPROGRAMOBJECTARBPROC) (GLhandleARB programObj);
typedef void (APIENTRY * PFNGLVALIDATEPROGRAMARBPROC) (GLhandleARB programObj);
typedef GLboolean (APIENTRY * PFNGLISPROGRAMARBPROC) (GLuint program);
typedef void (APIENTRY * PFNGLGENQUERIESARBPROC) (GLsizei n, GLuint *ids);
typedef void (APIENTRY * PFNGLDELETEQUERIESARBPROC) (GLsizei n, const GLuint *ids);
typedef GLboolean (APIENTRY  * PFNGLISQUERYARBPROC) (GLuint id);
typedef void (APIENTRY * PFNGLBEGINQUERYARBPROC) (GLenum target, GLuint id);
typedef void (APIENTRY * PFNGLENDQUERYARBPROC) (GLenum target);
typedef void (APIENTRY * PFNGLGETQUERYIVARBPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRY * PFNGLGETQUERYOBJECTIVARBPROC) (GLuint id, GLenum pname, GLint *params);
typedef void (APIENTRY * PFNGLGETQUERYOBJECTUIVARBPROC) (GLuint id, GLenum pname, GLuint *params);


#ifdef linux
#define _strnicmp strncasecmp
#define _stricmp  strcasecmp
#endif

//***************************************************************************************
// Versioning
//***************************************************************************************

/*! \defgroup Versioning Versioning Define
	Realtime Shader protocol version.
	\sa \ref RTS_GetVersion "RTS_GetVersion"
@{
*/
#define XSI_RTSHADER_VERSION	300		//!< XSI_RTSHADER_VERSION Realtime shader protocol version 3.00
/*!
@}
*/

//***************************************************************************************
// Application IDs
//***************************************************************************************

// Application_IDs Application ID Defines (identifies the various Softimage applications.)
#define	APPID_XSI					0x00000000	//! The host application is Softimage
#define	APPID_XSI_OGL				0x00000001	//! The host application is Softimage and is running in OpenGL mode (Always)
#define	APPID_XSIVIEWER				0x00000100	//! The host application is the XSI Viewer
#define	APPID_XSIVIEWER_OGL			0x00000101	//! The host application is the XSI Viewer and is running with the OpenGL driver
#define	APPID_XSIVIEWER_D3D			0x00000102	//! The host application is the XSI Viewer and is running with the DirectX driver
#define	APPID_XSIVIEWER_XBOX		0x00000103	//! The host application is the XSI Viewer and is running on the XBOX
#define	APPID_XSIVIEWER_PS2GL		0x00000104	//! The host application is the XSI Viewer and is running on the PS2


//***************************************************************************************
// Shader flags
//***************************************************************************************

/*! \defgroup Shader_flags Shader Flag Defines
	Flags used by the XSI_RTS_SystemParams::m_lShaderFlags member.
	\sa XSI_RTS_SystemParams::m_lShaderFlags member.
@{
*/
#define RTS_SHADER_FLAG_NONE			0x00000000	//!< Nothing interesting happened since the last refresh.
#define RTS_SHADER_FLAG_PARAM_CHANGE	0x00000001	//!< A parameter of the shader has changed.
#define RTS_SHADER_FLAG_FIRST			0x00000002  //!< Not implemented. The shader is the first node in the shader tree (the first node executed).
#define RTS_SHADER_FLAG_LAST			0x00000004	//!< Not implemented. The shader is the last node in the shader tree (the last shader executed).
#define RTS_SHADER_FLAG_TREE_CHANGE		0x00000008	//!< The topology of the shader tree on the owner material has changed since the last refresh. For example, a node was connected or disconnected.
/*!
@}
*/

//***************************************************************************************
// Object flags
//***************************************************************************************

/*! \defgroup Object_flags Object Flag Defines
	Flags used by the XSI_RTS_SystemParams::m_lObjectFlags member.
	\sa XSI_RTS_SystemParams::m_lObjectFlags member.
@{
*/
#define RTS_OBJECT_FLAG_NONE			0x00000000	//!< Nothing interesting happened since the last refresh.
#define RTS_OBJECT_FLAG_TOPO			0x00000001	//!< The object's topology has changed since the last refresh.
#define RTS_OBJECT_FLAG_DEFORM			0x00000002	//!< The object was deformed but it’s topology is the same since the last refresh.
/*!
@}
*/


//***************************************************************************************
// Lights and camera enums
//***************************************************************************************

/*! \defgroup eXSI_RTS_LightType eXSI_RTS_LightType Enum
	Types of lights.
	\sa tagXSI_RTS_Light::m_eType
@{
*/
enum eXSI_RTS_LightType
{
	RTS_LIGHT_POINT,		//!< A point light
	RTS_LIGHT_INFINITE,		//!< An infinite (or parallel) light
	RTS_LIGHT_SPOT			//!< A spot light
};
/*!
@}
*/

/*! \defgroup eXSI_RTS_CameraType eXSI_RTS_CameraType Enum
	Types of cameras.
	\sa tagXSI_RTS_Camera::m_eCameraType
@{
*/
enum eXSI_RTS_CameraType
{
	RTS_ORTHOGRAPHIC,		//!< Orthographic
	RTS_PERSPECTIVE			//!< Perspective
};
/*!
@}
*/

/*! \defgroup eXSI_RTS_RequirementType eXSI_RTS_RequirementType Enum
	Requirement types for the RTS API.
	\sa tagXSI_RTS_SystemParams, \ref GetRequirements "GetRequirements"
@{
*/
enum eXSI_RTS_RequirementType
{
	RTS_REQUIRE_ZSORT			=	0,		//!< The shader requires the object to be zsorted
	RTS_REQUIRE_RESERVED			=	1,		//!< Obsolete and no longer supported
	RTS_REQUIRE_OBJECTHANDLE		=	2,		//!< \deprecated 7.0. For v3.0 shaders you can get the object directly via IRTSExecutionState::GetPrimitive
	RTS_REQUIRE_MATERIALHANDLE		=	3,		//!< \deprecated 7.0. For v3.0 shaders you can get the material directly via IRTSExecutionState::GetMaterial
	RTS_REQUIRE_LIGHTHANDLE			=	4,		//!< The shader requires the light handle
	RTS_REQUIRE_PRIMARYINITUIGUID		=	5,		//!< This is the GUID of the parameter that will trigger a call to \ref InitUI "InitUI"
	RTS_REQUIRE_SECONDARYINITUIGUID		=	6,		//!< This is the GUID of the parameter that will trigger a call to \ref InitUI "InitUI"
	RTS_REQUIRE_DYNAMIC_ATTRIBUTE_LIST	=	7,		//!< Whether or not the list of vertex attributes returned by GetAttributeList from this shader might change at every frame.
	RTS_REQUIRE_UNUSED			=   0xffffffff		//!< Unused
};
/*!
@}
*/

/*! \defgroup eXSI_RTS_TriangleListType eXSI_RTS_TriangleListType Enum
	Types of triangle lists. Provided only for backward compatibility.
	\deprecated 7.0. Triangles lists are an obsolete concept in RTS API v3.0 shaders.
	\sa tagXSI_RTS_TriangleList,
@{
*/
enum eXSI_RTS_TriangleListType
{
	RTS_TL_SINGLE_INDEX_ARRAY,	//!< Arrays define positions, normals, UV and colors and a single index is used
	RTS_TL_BYREF,				//!< Positions, normals, UVs and colors are accessed by pointers, everything is in float
	RTS_TL_BYREF_POSD,			//!< Positions, normals, UVs and colors are accessed by pointers, everything is in float, except position which is double
	RTS_TL_PACKED_ARRAY			//!< Arrays are tightly packed and stored in order
};
/*!
@}
*/

/*! \defgroup eXSI_RTS_PrimitiveType eXSI_RTS_PrimitiveType Enum
	Types of primitives.
	\sa tagXSI_RTS_Primitive::m_Type
@{
*/
enum eXSI_RTS_PrimitiveType
{
	RTS_PT_PARTICLE_CLOUD,		//!< Particle cloud primitive
	RTS_PT_TRIANGLE_MESH		//!< Triangle mesh primitive
};
/*!
@}
*/

//***************************************************************************************
// Dynamic load library stuff
//***************************************************************************************

#if !defined(linux)

// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the RTShader_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// RTSHADER_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.

#ifdef SHADERS_EXPORTS
	#ifndef _XBOX
		#define RTSHADER_API __declspec(dllexport)
	#else
		#define RTSHADER_API
	#endif
#else
	#ifdef XSI_STATIC_LINK
		#define RTSHADER_API
	#else
		#define RTSHADER_API __declspec(dllimport)
	#endif
#endif

#else

// Although Linux figures the shared library import and exports, it does not define any of the
// standard windows types, such as LPVOID, BOOL, etc. Since this file uses them, and files that
// use this file use them aswell, they are defined here.
#define RTSHADER_API

#endif

//***************************************************************************************
// Types
//***************************************************************************************

/*! \typedef size_t
	Identifier for Realtime Shader context.
	\sa tagXSI_RTS_SystemParams
*/
typedef size_t RTSContext;									//! 32/64 bits identifier for RTS context.

// All structures that are used to construct a PPG must be compiled without padding
// between struct fields.  This is because a pointer to the PPG struct will be initialized
// directly by type casting a void pointer as in the following:
//
//   MyPPG * my_ppg = (MyPPG*) in_pVoid;
//
#pragma pack(push, 1)

typedef char* XSI_RTS_Semantic;

/*! \page RTS_DataTypes Data Types for Realtime Shaders
	The following data types are supported for RTS API v3.0:
	<BR>
	<BR>
	<TABLE BORDER="0">
	<TR><TD>&nbsp;</TD>		<TD>tagXSI_RTS_Vector2</TD>		<TD>2D Vector</TD></TR>
	<TR><TD>&nbsp;</TD>		<TD>tagXSI_RTS_Vector3</TD>		<TD>3D Vector</TD></TR>
	<TR><TD>&nbsp;</TD>		<TD>tagXSI_RTS_Vector3d</TD>	<TD>Double precision 3D Vector</TD></TR>
	<TR><TD>&nbsp;</TD>		<TD>tagXSI_RTS_Vector4</TD>		<TD>4D Vector</TD></TR>
	<TR><TD>&nbsp;</TD>		<TD>tagXSI_RTS_ColorRGB</TD>	<TD>RGB Color</TD></TR>
	<TR><TD>&nbsp;</TD>		<TD>tagXSI_RTS_ColorRGBf</TD>	<TD>Normalized RGB Color</TD></TR>
	<TR><TD>&nbsp;</TD>		<TD>tagXSI_RTS_ColorRGBA</TD>	<TD>RGBA Color</TD></TR>
	<TR><TD>&nbsp;</TD>		<TD>tagXSI_RTS_ColorRGBAf</TD>	<TD>Normalized RGBA Color</TD></TR>
	<TR><TD>&nbsp;</TD>		<TD>tagXSI_RTS_ColorARGB</TD>	<TD>ARGB Color</TD></TR>
	<TR><TD>&nbsp;</TD>		<TD>tagXSI_RTS_Texture</TD>		<TD>Texture</TD></TR>
	</TABLE>
*/

/*! \struct tagXSI_RTS_Vector2
	The XSI_RTS_Vector2 structure represents the 2D Vector data type.
*/
typedef struct tagXSI_RTS_Vector2
{														/*! The X component	*/
	float	m_x;										/*! The Y component	*/
	float	m_y;
} XSI_RTS_Vector2;


/*! \struct tagXSI_RTS_Vector3d
	The XSI_RTS_Vector3d structure represents the Double precision 3D Vector data type.
*/
typedef struct tagXSI_RTS_Vector3d
{														/*! The X component	*/
	double	m_x;										/*! The Y component	*/
	double	m_y;										/*! The Z component	*/
	double	m_z;
} XSI_RTS_Vector3d;

/*! \struct tagXSI_RTS_Vector3
	The XSI_RTS_Vector3 structure represents the 3D Vector data type.
*/
typedef struct tagXSI_RTS_Vector3
{														/*! The X component	*/
	float	m_x;										/*! The Y component	*/
	float	m_y;										/*! The Z component	*/
	float	m_z;
} XSI_RTS_Vector3;


/*! \struct tagXSI_RTS_Vector4
	The XSI_RTS_Vector4 structure represents the 4D Vector data type.
*/
typedef struct tagXSI_RTS_Vector4
{														/*! The X component	*/
	float	m_x;										/*! The Y component	*/
	float	m_y;										/*! The Z component	*/
	float	m_z;										/*! The W component	*/
	float	m_w;
} XSI_RTS_Vector4;

/*! \struct tagXSI_RTS_ColorRGB
	The XSI_RTS_ColorRGB structure represents the RGB color data type.
*/
typedef struct tagXSI_RTS_ColorRGB
{														/*!< The red component		*/
	unsigned char	m_red;								/*!< The green component	*/
	unsigned char	m_green;							/*!< The blue component		*/
	unsigned char	m_blue;
} XSI_RTS_ColorRGB;


/*! \struct tagXSI_RTS_ColorRGBf
	The XSI_RTS_ColorRGBf structure represents the normalized RGB color data type.
*/
typedef struct tagXSI_RTS_ColorRGBf
{														/*! The red component		*/
	float			m_red;								/*! The green component		*/
	float			m_green;							/*! The blue component		*/
	float			m_blue;
} XSI_RTS_ColorRGBf;

/*! \struct tagXSI_RTS_ColorRGBAf
	The XSI_RTS_ColorRGBAf structure represents the normalized RGBA color data type.
*/
typedef struct tagXSI_RTS_ColorRGBAf
{														/*! The red component		*/
	float			m_red;								/*! The green component		*/
	float			m_green;							/*! The blue component		*/
	float			m_blue;								/*! The alpha component		*/
	float			m_alpha;
} XSI_RTS_ColorRGBAf;

/*! \struct tagXSI_RTS_ColorRGBA
	The XSI_RTS_ColorRGBA structure represents the RGBA color data type.
*/
typedef struct tagXSI_RTS_ColorRGBA
{														/*! The red component		*/
	unsigned char	m_red;								/*! The green component		*/
	unsigned char	m_green;							/*! The blue component		*/
	unsigned char	m_blue;								/*! The alpha component		*/
	unsigned char	m_alpha;
} XSI_RTS_ColorRGBA;

/*! \struct tagXSI_RTS_ColorARGB
	The XSI_RTS_ColorARGB structure represents the ARGB color data type.
*/
typedef struct tagXSI_RTS_ColorARGB
{														/*! The alpha component		*/
	unsigned char	m_alpha;							/*! The red component		*/
	unsigned char	m_red;								/*! The green component		*/
	unsigned char	m_green;							/*! The blue component		*/
	unsigned char	m_blue;
} XSI_RTS_ColorARGB;

typedef struct tagXSI_RTS_Attribute1D
{
	XSI_RTS_Semantic	m_semantic;
	float				m_attribute;
}	XSI_RTS_Attribute1D;

typedef struct tagXSI_RTS_Attribute2D
{
	XSI_RTS_Semantic	m_semantic;
	XSI_RTS_Vector2		m_attribute;
}	XSI_RTS_Attribute2D;

typedef struct tagXSI_RTS_Attribute3D
{
	XSI_RTS_Semantic	m_semantic;
	XSI_RTS_Vector3		m_attribute;
}	XSI_RTS_Attribute3D;

typedef struct tagXSI_RTS_Attribute4D
{
	XSI_RTS_Semantic	m_semantic;
	XSI_RTS_Vector4		m_attribute;
}	XSI_RTS_Attribute4D;

/*! \struct tagXSI_RTS_Texture
	The XSI_RTS_Texture structure represents a texture.
*/
typedef struct tagXSI_RTS_Texture
{													/*! The path of the image for this texture			*/
	char				*m_pchPath;					/*! The width of the image							*/
	ULONG				m_lWidth;					/*! The height of the image							*/
	ULONG				m_lHeight;					/*! The number of channels							*/
	ULONG				m_lNbChannels;				/*! The type of pixel								*/
	ULONG				m_lPixelType;				/*! The size of the pixel buffer					*/
	ULONG				m_lBufferSize;				/*! The pixel buffer								*/
	unsigned char		*m_pBuffer;					/*! The texture is dirty and should be refreshed	*/
	ULONG				m_lDirty;
} XSI_RTS_Texture;

/*! \class XSI_RTS_Uniform XSI_rtshaders.h
	\brief The XSI_RTS_Uniform object defines a special parameter for a Realtime Shader chain.

	A \a uniform \a parameter is a value that is defined by the Realtime Shader but intended to be used inside a vertex
	or a fragment shader. For example, a real-time shader node can use this method to define a single float parameter
	called \c foobar. When the real-time shader node responsible for calling the vertex or fragment shader (GLSLProgram
	or HLSLProgram) is called, it retrieves the list of uniform parameters defined and passes them to the vertex and
	fragment shader.

	\sa IRTSExecutionState::DefineUniform, IRTSExecutionState::ClearUniforms, IRTSExecutionState::GetNbUniforms,
		IRTSExecutionState::GetUniformList
	\since 7.0
*/
class XSI_RTS_Uniform
{
public:
	/*! \enum eUniformType
		Data type for the uniform parameter.
	*/
	enum eUniformType
	{						/*! Float data type		*/
		Float = 0,			/*! Integer data type	*/
		Int,				/*! Texture data type	*/
		Texture
	};

	/*! Constructs an %XSI_RTS_Uniform object from the specified information.
		\param in_eType	Data type for the new uniform parameter (one of the eUniformType enum values)
		\param in_szName	Name for the uniform parameter
		\param in_uiSize	Size of the data for the uniform parameter
		\param in_pData	Pointer to the data to store in the uniform parameter
	*/
	XSI_RTS_Uniform( eUniformType in_eType, const char* in_szName, unsigned int in_uiSize, void* in_pData )
	{
		m_eType = in_eType;
		m_szName = strdup ( in_szName );
		m_uiSize = in_uiSize;
		switch ( in_eType )
		{
			case Float:	m_pfData = new float [ m_uiSize ]; memcpy ( m_pfData, in_pData, sizeof(float)*in_uiSize); break;
			case Int:	m_piData = new int [ m_uiSize ]; memcpy ( m_piData, in_pData, sizeof(int)*in_uiSize); break;
			case Texture: m_pcTextureData = new char [ m_uiSize ]; memcpy ( m_pcTextureData, in_pData, sizeof(char)*in_uiSize); break;
		}

	}

	/*! Default destructor.
	*/
	virtual ~XSI_RTS_Uniform()
	{
		free(m_szName);
		switch ( m_eType )
		{
			case Float:	delete [] m_pfData ; break;
			case Int:	delete [] m_piData ; break;
			case Texture: delete [] m_pcTextureData; break;
		}
	}

	/*! Returns the name of the uniform parameter.
		\return The name of the uniform parameter
	*/
	const char*		GetName() { return m_szName; };

	/*! Returns the size of the data for the uniform parameter.
		\return The size of the data
	*/
	unsigned int	GetSize() { return m_uiSize; };

	/*! Returns the data type of the uniform parameter.
		\return One of the XSI_RTS_Uniform::eUniformType enum values representing the data type
	*/
	eUniformType	GetType() { return m_eType; };

	/*! Returns the data stored in the uniform parameter.
		\return A pointer to the stored data
	*/
	void*			GetData() { return (void*)m_piData; };

	size_t			GetDynamicMemSize() const
	{
		size_t l_lSize = (m_szName?strlen(m_szName)+1:0);
		switch ( m_eType )
		{
			case Float:	l_lSize += m_uiSize*sizeof(float); break;
			case Int:	l_lSize += m_uiSize*sizeof(int); break;
			case Texture: l_lSize += m_uiSize*sizeof(char); break;
		}
		return l_lSize;
	}

private:

	char*		m_szName;				//! The name of the uniform parameter
	unsigned int	m_uiSize;			//! The size of the data
	eUniformType	m_eType;

	union
	{
		int*		m_piData;			//! Int data
		float*		m_pfData;			//! Float data
		char*		m_pcTextureData;	//! Texture data
	};
};

//***************************************************************************************
// OpenGL extensions wrappers
//***************************************************************************************

/*! \struct tagXGSExtensionsGL
	\brief GraphicSequencer GL extensions structure.

	This structure is used by the tagXSI_RTS_SystemParams structure to query whether a particular OpenGL extension
	is used. For example, if you want to test whether your hardware supports the \c GL_ARB_multitexture extension,
	check whether \c m_pGLExt->_GL_ARB_multitexture \c == \c true.
	\deprecated 7.0. Not used for RTS API v3.0.
	\sa tagXSI_RTS_SystemParams, \xt cus_graphicsequencer GraphicSequencer
*/
typedef struct tagXGSExtensionsGL
{													/*! Version */
	int  version;									/*! Size */
	int  size;
													/*! ARB multitexture */
	bool _GL_ARB_multitexture ;						/*! ARB transpose matrix */
	bool _GL_ARB_transpose_matrix ;					/*! ARB multisample */
	bool _GL_ARB_multisample ;						/*! ARB texture env add */
	bool _GL_ARB_texture_env_add ;					/*! ARB texture cube map */
	bool _GL_ARB_texture_cube_map ;					/*! ARB texture compression */
	bool _GL_ARB_texture_compression ;				/*! ARB texture border clamp */
	bool _GL_ARB_texture_border_clamp ;				/*! ARB point parameters */
	bool _GL_ARB_point_parameters ;					/*! ARB vertex blend */
	bool _GL_ARB_vertex_blend ;						/*! ARB matrix palette */
	bool _GL_ARB_matrix_palette ;					/*! ARB texture env combine */
	bool _GL_ARB_texture_env_combine ;				/*! ARB texture env crossbar */
	bool _GL_ARB_texture_env_crossbar ;				/*! ARB texture env dot3 */
	bool _GL_ARB_texture_env_dot3 ;					/*! ARB texture mirrored repeat */
	bool _GL_ARB_texture_mirrored_repeat ;			/*! ARB depth texture */
	bool _GL_ARB_depth_texture ;					/*! ARB shadow */
	bool _GL_ARB_shadow ;							/*! ARB shadow ambient */
	bool _GL_ARB_shadow_ambient ;					/*! ARB window pos */
	bool _GL_ARB_window_pos ;						/*! ARB vertex program */
	bool _GL_ARB_vertex_program ;					/*! ARB fragment program */
	bool _GL_ARB_fragment_program ;					/*! EXT abgr */
	bool _GL_EXT_abgr ;								/*! EXT blend color */
	bool _GL_EXT_blend_color ;						/*! EXT polygon offset */
	bool _GL_EXT_polygon_offset ;					/*! EXT texture */
	bool _GL_EXT_texture ;							/*! EXT texture3D */
	bool _GL_EXT_texture3D ;						/*! SGIS texture filter4 */
	bool _GL_SGIS_texture_filter4 ;					/*! EXT subtexture */
	bool _GL_EXT_subtexture ;						/*! EXT copy texture */
	bool _GL_EXT_copy_texture ;						/*! EXT histogram */
	bool _GL_EXT_histogram ;						/*! EXT convolution */
	bool _GL_EXT_convolution ;						/*! SGI color matrix */
	bool _GL_SGI_color_matrix ;						/*! SGI color table */
	bool _GL_SGI_color_table ;						/*! SGIS pixel texture */
	bool _GL_SGIS_pixel_texture ;					/*! SGIX pixel texture */
	bool _GL_SGIX_pixel_texture ;					/*! SGIS texture4D */
	bool _GL_SGIS_texture4D ;						/*! SGI texture color table */
	bool _GL_SGI_texture_color_table ;				/*! EXT cmyka */
	bool _GL_EXT_cmyka ;							/*! EXT texture object */
	bool _GL_EXT_texture_object ;					/*! SGIS detail texture */
	bool _GL_SGIS_detail_texture ;					/*! SGIS sharpen texture */
	bool _GL_SGIS_sharpen_texture ;					/*! EXT packed pixels */
	bool _GL_EXT_packed_pixels ;					/*! SGIS texture lod */
	bool _GL_SGIS_texture_lod ;						/*! SGIS multisample */
	bool _GL_SGIS_multisample ;						/*! EXT rescale normal */
	bool _GL_EXT_rescale_normal ;					/*! EXT vertex array */
	bool _GL_EXT_vertex_array ;						/*! EXT misc attribute */
	bool _GL_EXT_misc_attribute ;					/*! SGIS generate mipmap */
	bool _GL_SGIS_generate_mipmap ;					/*! SGIX clipmap */
	bool _GL_SGIX_clipmap ;							/*! SGIX shadow */
	bool _GL_SGIX_shadow ;							/*! SGIS texture edge clamp */
	bool _GL_SGIS_texture_edge_clamp ;				/*! SGIS texture border clamp */
	bool _GL_SGIS_texture_border_clamp ;			/*! EXT blend minmax */
	bool _GL_EXT_blend_minmax ;						/*! EXT blend subtract */
	bool _GL_EXT_blend_subtract ;					/*! EXT blend logic op */
	bool _GL_EXT_blend_logic_op ;					/*! SGIX interlace */
	bool _GL_SGIX_interlace ;						/*! SGIS texture select */
	bool _GL_SGIS_texture_select ;					/*! SGIX sprite */
	bool _GL_SGIX_sprite ;							/*! SGIX texture multi buffer */
	bool _GL_SGIX_texture_multi_buffer ;			/*! EXT point parameters */
	bool _GL_EXT_point_parameters ;					/*! SGIX instruments */
	bool _GL_SGIX_instruments ;						/*! SGIX texture scale bias */
	bool _GL_SGIX_texture_scale_bias ;				/*! SGIX framezoom */
	bool _GL_SGIX_framezoom ;						/*! SGIX tag sample buffer */
	bool _GL_SGIX_tag_sample_buffer ;				/*! SGIX reference plane */
	bool _GL_SGIX_reference_plane ;					/*! SGIX flush raster */
	bool _GL_SGIX_flush_raster ;					/*! SGIX depth texture */
	bool _GL_SGIX_depth_texture ;					/*! SGIS fog function */
	bool _GL_SGIS_fog_function ;					/*! SGIX fog offset */
	bool _GL_SGIX_fog_offset ;						/*! HP image transform */
	bool _GL_HP_image_transform ;					/*! HP convolution border modes */
	bool _GL_HP_convolution_border_modes ;			/*! SGIX texture add env */
	bool _GL_SGIX_texture_add_env ;					/*! EXT color subtable */
	bool _GL_EXT_color_subtable ;					/*! PGI vertex hints */
	bool _GL_PGI_vertex_hints ;						/*! PGI misc hints */
	bool _GL_PGI_misc_hints ;						/*! EXT paletted texture */
	bool _GL_EXT_paletted_texture ;					/*! EXT clip volume hint */
	bool _GL_EXT_clip_volume_hint ;					/*! SGIX list priority */
	bool _GL_SGIX_list_priority ;					/*! SGIX ir instrument1 */
	bool _GL_SGIX_ir_instrument1 ;					/*! SGIX texture lod bias */
	bool _GL_SGIX_texture_lod_bias ;				/*! SGIX shadow ambient */
	bool _GL_SGIX_shadow_ambient ;					/*! EXT index texture */
	bool _GL_EXT_index_texture ;					/*! EXT index material */
	bool _GL_EXT_index_material ;					/*! EXT index func */
	bool _GL_EXT_index_func ;						/*! EXT index array formats */
	bool _GL_EXT_index_array_formats ;				/*! EXT compiled vertex array */
	bool _GL_EXT_compiled_vertex_array ;			/*! EXT cull vertex */
	bool _GL_EXT_cull_vertex ;						/*! SGIX ycrcb */
	bool _GL_SGIX_ycrcb ;							/*! EXT fragment lighting */
	bool _GL_EXT_fragment_lighting ;				/*! IBM rasterpos clip */
	bool _GL_IBM_rasterpos_clip ;					/*! HP texture lighting */
	bool _GL_HP_texture_lighting ;					/*! EXT draw range elements */
	bool _GL_EXT_draw_range_elements ;				/*! WIN phong shading */
	bool _GL_WIN_phong_shading ;					/*! WIN specular fog */
	bool _GL_WIN_specular_fog ;						/*! EXT light texture */
	bool _GL_EXT_light_texture ;					/*! SGIX blend alpha minmax */
	bool _GL_SGIX_blend_alpha_minmax ;				/*! EXT scene marker */
	bool _GL_EXT_scene_marker ;						/*! SGIX pixel texture bits */
	bool _GL_SGIX_pixel_texture_bits ;				/*! EXT bgra */
	bool _GL_EXT_bgra ;								/*! SGIX async */
	bool _GL_SGIX_async ;							/*! SGIX async pixel */
	bool _GL_SGIX_async_pixel ;						/*! SGIX async histogram */
	bool _GL_SGIX_async_histogram ;					/*! INTEL texture scissor */
	bool _GL_INTEL_texture_scissor ;				/*! INTEL parallel arrays */
	bool _GL_INTEL_parallel_arrays ;				/*! HP occlusion test */
	bool _GL_HP_occlusion_test ;					/*! EXT pixel transform */
	bool _GL_EXT_pixel_transform ;					/*! EXT pixel transform color table */
	bool _GL_EXT_pixel_transform_color_table ;		/*! EXT shared texture palette */
	bool _GL_EXT_shared_texture_palette ;			/*! EXT separate specular color */
	bool _GL_EXT_separate_specular_color ;			/*! EXT secondary color */
	bool _GL_EXT_secondary_color ;					/*! EXT texture env */
	bool _GL_EXT_texture_env ;						/*! EXT texture perturb normal */
	bool _GL_EXT_texture_perturb_normal ;			/*! EXT multi draw arrays */
	bool _GL_EXT_multi_draw_arrays ;				/*! EXT fog coord */
	bool _GL_EXT_fog_coord ;						/*! REND screen coordinates */
	bool _GL_REND_screen_coordinates ;				/*! EXT coordinate frame */
	bool _GL_EXT_coordinate_frame ;					/*! EXT texture env combine */
	bool _GL_EXT_texture_env_combine ;				/*! APPLE specular vector */
	bool _GL_APPLE_specular_vector ;				/*! APPLE transform hint */
	bool _GL_APPLE_transform_hint ;					/*! SUNX constant data */
	bool _GL_SUNX_constant_data ;					/*! SUN global alpha */
	bool _GL_SUN_global_alpha ;						/*! SUN triangle list */
	bool _GL_SUN_triangle_list ;					/*! SUN vertex */
	bool _GL_SUN_vertex ;							/*! EXT blend func separate */
	bool _GL_EXT_blend_func_separate ;				/*! INGR color clamp */
	bool _GL_INGR_color_clamp ;						/*! INGR interlace read */
	bool _GL_INGR_interlace_read ;					/*! EXT stencil wrap */
	bool _GL_EXT_stencil_wrap ;						/*! EXT 422 pixels */
	bool _GL_EXT_422_pixels ;						/*! NV texgen reflection */
	bool _GL_NV_texgen_reflection ;					/*! SGIX texture range */
	bool _GL_SGIX_texture_range ;					/*! SUN convolution border modes */
	bool _GL_SUN_convolution_border_modes ;			/*! EXT texture env add */
	bool _GL_EXT_texture_env_add ;					/*! EXT texture lod bias */
	bool _GL_EXT_texture_lod_bias ;					/*! EXT texture filter anisotropic */
	bool _GL_EXT_texture_filter_anisotropic ;		/*! EXT vertex weighting */
	bool _GL_EXT_vertex_weighting ;					/*! NV light max exponent */
	bool _GL_NV_light_max_exponent ;				/*! NV vertex array range */
	bool _GL_NV_vertex_array_range ;				/*! NV register combiners */
	bool _GL_NV_register_combiners ;				/*! NV fog distance */
	bool _GL_NV_fog_distance ;						/*! NV texgen emboss */
	bool _GL_NV_texgen_emboss ;						/*! NV blend square */
	bool _GL_NV_blend_square ;						/*! NV texture env combine4 */
	bool _GL_NV_texture_env_combine4 ;				/*! MESA resize buffers */
	bool _GL_MESA_resize_buffers ;					/*! MESA window pos */
	bool _GL_MESA_window_pos ;						/*! EXT texture compression s3tc */
	bool _GL_EXT_texture_compression_s3tc ;			/*! IBM cull vertex */
	bool _GL_IBM_cull_vertex ;						/*! IBM multimode draw arrays */
	bool _GL_IBM_multimode_draw_arrays ;			/*! IBM vertex array lists */
	bool _GL_IBM_vertex_array_lists ;				/*! 3DFX texture compression FXT1 */
	bool _GL_3DFX_texture_compression_FXT1 ;		/*! 3DFX multisample */
	bool _GL_3DFX_multisample ;						/*! 3DFX tbuffer */
	bool _GL_3DFX_tbuffer ;							/*! SGIX vertex preclip */
	bool _GL_SGIX_vertex_preclip ;					/*! SGIX resample */
	bool _GL_SGIX_resample ;						/*! SGIS texture color mask */
	bool _GL_SGIS_texture_color_mask ;				/*! EXT texture env dot3 */
	bool _GL_EXT_texture_env_dot3 ;					/*! ATI texture mirror once */
	bool _GL_ATI_texture_mirror_once ;				/*! NV fence */
	bool _GL_NV_fence ;								/*! IBM static data */
	bool _GL_IBM_static_data ;						/*! IBM texture mirrored repeat */
	bool _GL_IBM_texture_mirrored_repeat ;			/*! NV evaluators */
	bool _GL_NV_evaluators ;						/*! NV packed depth stencil */
	bool _GL_NV_packed_depth_stencil ;				/*! NV register combiners2 */
	bool _GL_NV_register_combiners2 ;				/*! NV texture compression vtc */
	bool _GL_NV_texture_compression_vtc ;			/*! NV texture rectangle */
	bool _GL_NV_texture_rectangle ;					/*! NV texture shader */
	bool _GL_NV_texture_shader ;					/*! NV texture shader2 */
	bool _GL_NV_texture_shader2 ;					/*! NV vertex array range2 */
	bool _GL_NV_vertex_array_range2 ;				/*! NV vertex program */
	bool _GL_NV_vertex_program ;					/*! SGIX texture coordinate clamp */
	bool _GL_SGIX_texture_coordinate_clamp ;		/*! OML interlace */
	bool _GL_OML_interlace ;						/*! OML subsample */
	bool _GL_OML_subsample ;						/*! OML resample */
	bool _GL_OML_resample ;							/*! NV copy depth to color */
	bool _GL_NV_copy_depth_to_color ;				/*! ATI envmap bumpmap */
	bool _GL_ATI_envmap_bumpmap ;					/*! ATI fragment shader */
	bool _GL_ATI_fragment_shader ;					/*! ATI pn triangles */
	bool _GL_ATI_pn_triangles ;						/*! ATI vertex array object */
	bool _GL_ATI_vertex_array_object ;				/*! EXT vertex shader */
	bool _GL_EXT_vertex_shader ;					/*! ATI vertex streams */
	bool _GL_ATI_vertex_streams ;					/*! ATI element array */
	bool _GL_ATI_element_array ;					/*! SUN mesh array */
	bool _GL_SUN_mesh_array ;						/*! SUN slice accum */
	bool _GL_SUN_slice_accum ;						/*! NV multisample filter hint */
	bool _GL_NV_multisample_filter_hint ;			/*! NV depth clamp */
	bool _GL_NV_depth_clamp ;						/*! NV occlusion query */
	bool _GL_NV_occlusion_query ;					/*! NV point sprite */
	bool _GL_NV_point_sprite ;						/*! NV texture shader3 */
	bool _GL_NV_texture_shader3 ;					/*! NV vertex program1 1 */
	bool _GL_NV_vertex_program1_1 ;					/*! EXT shadow funcs */
	bool _GL_EXT_shadow_funcs ;						/*! EXT stencil two side */
	bool _GL_EXT_stencil_two_side ;					/*! ATI text fragment shader */
	bool _GL_ATI_text_fragment_shader ;				/*! APPLE client storage */
	bool _GL_APPLE_client_storage ;					/*! APPLE element array */
	bool _GL_APPLE_element_array ;					/*! APPLE fence */
	bool _GL_APPLE_fence ;							/*! APPLE vertex array object */
	bool _GL_APPLE_vertex_array_object ;			/*! APPLE vertex array range */
	bool _GL_APPLE_vertex_array_range ;				/*! APPLE ycbcr 422 */
	bool _GL_APPLE_ycbcr_422 ;						/*! ARB vertex buffer object */
	bool _GL_ARB_vertex_buffer_object ;				/*! S3 s3tc */
	bool _GL_S3_s3tc ;								/*! ATI draw buffers */
	bool _GL_ATI_draw_buffers ;						/*! ATI texture env combine3 */
	bool _GL_ATI_texture_env_combine3 ;				/*! ATI texture float */
	bool _GL_ATI_texture_float ;					/*! NV float buffer */
	bool _GL_NV_float_buffer ;						/*! NV fragment program */
	bool _GL_NV_fragment_program ;					/*! NV half float */
	bool _GL_NV_half_float ;						/*! NV pixel data range */
	bool _GL_NV_pixel_data_range ;					/*! NV primitive restart */
	bool _GL_NV_primitive_restart ;					/*! NV texture expand normal */
	bool _GL_NV_texture_expand_normal ;				/*! NV vertex program2 */
	bool _GL_NV_vertex_program2 ;					/*! ATI map object buffer */
	bool _GL_ATI_map_object_buffer ;				/*! ATI separate stencil */
	bool _GL_ATI_separate_stencil ;					/*! ATI vertex attrib array object */
	bool _GL_ATI_vertex_attrib_array_object ;		/*! Framebuffer object */
	bool _GL_framebuffer_object;					/*! ARB pixel buffer object */
	bool _GL_ARB_pixel_buffer_object;

} XGSExtensionsGL;

/*! \struct tagXGSGLExtensionsFuncs
	\brief GraphicSequencer GL extensions functions.

	This the structure for storing the OpenGL extension wrapper functions. For example, if you want to call the
	\c glClientActiveTextureARB extension function, just use \c m_pGLExtFuncs->glClientActiveTextureARB.
	\sa tagXSI_RTS_SystemParams, \xt cus_graphicsequencer GraphicSequencer
	\deprecated 7.0. Not used for RTS API v3.0.
*/
typedef struct tagXGSGLExtensionsFuncs
{																																	/*! Version			*/
	int  																version;													/*! Size			*/
	int  																size;
																																	/*! BlendColor OGL function	*/
	PFNGLBLENDCOLORPROC													glBlendColor;												/*! BlendEquation OGL function	*/
	PFNGLBLENDEQUATIONPROC												glBlendEquation;											/*! DrawRangeElements OGL function	*/
	PFNGLDRAWRANGEELEMENTSPROC											glDrawRangeElements;										/*! ColorTable OGL function	*/
	PFNGLCOLORTABLEPROC													glColorTable;												/*! ColorTableParameterfv OGL function	*/
	PFNGLCOLORTABLEPARAMETERFVPROC										glColorTableParameterfv;									/*! ColorTableParameteriv OGL function	*/
	PFNGLCOLORTABLEPARAMETERIVPROC										glColorTableParameteriv;									/*! CopyColorTable OGL function	*/
	PFNGLCOPYCOLORTABLEPROC												glCopyColorTable;											/*! GetColorTable OGL function	*/
	PFNGLGETCOLORTABLEPROC												glGetColorTable;											/*! GetColorTableParameterfv OGL function	*/
	PFNGLGETCOLORTABLEPARAMETERFVPROC									glGetColorTableParameterfv;									/*! GetColorTableParameteriv OGL function	*/
	PFNGLGETCOLORTABLEPARAMETERIVPROC									glGetColorTableParameteriv;									/*! ColorSubTable OGL function	*/
	PFNGLCOLORSUBTABLEPROC												glColorSubTable;											/*! CopyColorSubTable OGL function	*/
	PFNGLCOPYCOLORSUBTABLEPROC											glCopyColorSubTable;										/*! ConvolutionFilter1D OGL function	*/
	PFNGLCONVOLUTIONFILTER1DPROC										glConvolutionFilter1D;										/*! ConvolutionFilter2D OGL function	*/
	PFNGLCONVOLUTIONFILTER2DPROC										glConvolutionFilter2D;										/*! ConvolutionParameterf OGL function	*/
	PFNGLCONVOLUTIONPARAMETERFPROC										glConvolutionParameterf;									/*! ConvolutionParameterfv OGL function	*/
	PFNGLCONVOLUTIONPARAMETERFVPROC										glConvolutionParameterfv;									/*! ConvolutionParameteri OGL function	*/
	PFNGLCONVOLUTIONPARAMETERIPROC										glConvolutionParameteri;									/*! ConvolutionParameteriv OGL function	*/
	PFNGLCONVOLUTIONPARAMETERIVPROC										glConvolutionParameteriv;									/*! CopyConvolutionFilter1D OGL function	*/
	PFNGLCOPYCONVOLUTIONFILTER1DPROC									glCopyConvolutionFilter1D;									/*! CopyConvolutionFilter2D OGL function	*/
	PFNGLCOPYCONVOLUTIONFILTER2DPROC									glCopyConvolutionFilter2D;									/*! GetConvolutionFilter OGL function	*/
	PFNGLGETCONVOLUTIONFILTERPROC										glGetConvolutionFilter;										/*! GetConvolutionParameterfv OGL function	*/
	PFNGLGETCONVOLUTIONPARAMETERFVPROC									glGetConvolutionParameterfv;								/*! GetConvolutionParameteriv OGL function	*/
	PFNGLGETCONVOLUTIONPARAMETERIVPROC									glGetConvolutionParameteriv;								/*! GetSeparableFilter OGL function	*/
	PFNGLGETSEPARABLEFILTERPROC											glGetSeparableFilter;										/*! SeparableFilter2D OGL function	*/
	PFNGLSEPARABLEFILTER2DPROC											glSeparableFilter2D;										/*! GetHistogram OGL function	*/
	PFNGLGETHISTOGRAMPROC												glGetHistogram;												/*! GetHistogramParameterfv OGL function	*/
	PFNGLGETHISTOGRAMPARAMETERFVPROC									glGetHistogramParameterfv;									/*! GetHistogramParameteriv OGL function	*/
	PFNGLGETHISTOGRAMPARAMETERIVPROC									glGetHistogramParameteriv;									/*! GetMinmax OGL function	*/
	PFNGLGETMINMAXPROC													glGetMinmax;												/*! GetMinmaxParameterfv OGL function	*/
	PFNGLGETMINMAXPARAMETERFVPROC										glGetMinmaxParameterfv;										/*! GetMinmaxParameteriv OGL function	*/
	PFNGLGETMINMAXPARAMETERIVPROC										glGetMinmaxParameteriv;										/*! Histogram OGL function	*/
	PFNGLHISTOGRAMPROC													glHistogram;												/*! Minmax OGL function	*/
	PFNGLMINMAXPROC														glMinmax;													/*! ResetHistogram OGL function	*/
	PFNGLRESETHISTOGRAMPROC												glResetHistogram;											/*! ResetMinmax OGL function	*/
	PFNGLRESETMINMAXPROC												glResetMinmax;												/*! TexImage3D OGL function	*/
	PFNGLTEXIMAGE3DPROC													glTexImage3D;												/*! TexSubImage3D OGL function	*/
	PFNGLTEXSUBIMAGE3DPROC												glTexSubImage3D;											/*! CopyTexSubImage3D OGL function	*/
	PFNGLCOPYTEXSUBIMAGE3DPROC											glCopyTexSubImage3D;
																																	/*! ActiveTexture OGL function	*/
	PFNGLACTIVETEXTUREPROC												glActiveTexture;											/*! ClientActiveTexture OGL function	*/
	PFNGLCLIENTACTIVETEXTUREPROC										glClientActiveTexture;										/*! MultiTexCoord1d OGL function	*/
	PFNGLMULTITEXCOORD1DPROC											glMultiTexCoord1d;											/*! MultiTexCoord1dv OGL function	*/
	PFNGLMULTITEXCOORD1DVPROC											glMultiTexCoord1dv;											/*! MultiTexCoord1f OGL function	*/
	PFNGLMULTITEXCOORD1FPROC											glMultiTexCoord1f;											/*! MultiTexCoord1fv OGL function	*/
	PFNGLMULTITEXCOORD1FVPROC											glMultiTexCoord1fv;											/*! MultiTexCoord1i OGL function	*/
	PFNGLMULTITEXCOORD1IPROC											glMultiTexCoord1i;											/*! MultiTexCoord1iv OGL function	*/
	PFNGLMULTITEXCOORD1IVPROC											glMultiTexCoord1iv;											/*! MultiTexCoord1s OGL function	*/
	PFNGLMULTITEXCOORD1SPROC											glMultiTexCoord1s;											/*! MultiTexCoord1sv OGL function	*/
	PFNGLMULTITEXCOORD1SVPROC											glMultiTexCoord1sv;											/*! MultiTexCoord2d OGL function	*/
	PFNGLMULTITEXCOORD2DPROC											glMultiTexCoord2d;											/*! MultiTexCoord2dv OGL function	*/
	PFNGLMULTITEXCOORD2DVPROC											glMultiTexCoord2dv;											/*! MultiTexCoord2f OGL function	*/
	PFNGLMULTITEXCOORD2FPROC											glMultiTexCoord2f;											/*! MultiTexCoord2fv OGL function	*/
	PFNGLMULTITEXCOORD2FVPROC											glMultiTexCoord2fv;											/*! MultiTexCoord2i OGL function	*/
	PFNGLMULTITEXCOORD2IPROC											glMultiTexCoord2i;											/*! MultiTexCoord2iv OGL function	*/
	PFNGLMULTITEXCOORD2IVPROC											glMultiTexCoord2iv;											/*! MultiTexCoord2s OGL function	*/
	PFNGLMULTITEXCOORD2SPROC											glMultiTexCoord2s;											/*! MultiTexCoord2sv OGL function	*/
	PFNGLMULTITEXCOORD2SVPROC											glMultiTexCoord2sv;											/*! MultiTexCoord3d OGL function	*/
	PFNGLMULTITEXCOORD3DPROC											glMultiTexCoord3d;											/*! MultiTexCoord3dv OGL function	*/
	PFNGLMULTITEXCOORD3DVPROC											glMultiTexCoord3dv;											/*! MultiTexCoord3f OGL function	*/
	PFNGLMULTITEXCOORD3FPROC											glMultiTexCoord3f;											/*! MultiTexCoord3fv OGL function	*/
	PFNGLMULTITEXCOORD3FVPROC											glMultiTexCoord3fv;											/*! MultiTexCoord3i OGL function	*/
	PFNGLMULTITEXCOORD3IPROC											glMultiTexCoord3i;											/*! MultiTexCoord3iv OGL function	*/
	PFNGLMULTITEXCOORD3IVPROC											glMultiTexCoord3iv;											/*! MultiTexCoord3s OGL function	*/
	PFNGLMULTITEXCOORD3SPROC											glMultiTexCoord3s;											/*! MultiTexCoord3sv OGL function	*/
	PFNGLMULTITEXCOORD3SVPROC											glMultiTexCoord3sv;											/*! MultiTexCoord4d OGL function	*/
	PFNGLMULTITEXCOORD4DPROC											glMultiTexCoord4d;											/*! MultiTexCoord4dv OGL function	*/
	PFNGLMULTITEXCOORD4DVPROC											glMultiTexCoord4dv;											/*! MultiTexCoord4f OGL function	*/
	PFNGLMULTITEXCOORD4FPROC											glMultiTexCoord4f;											/*! MultiTexCoord4fv OGL function	*/
	PFNGLMULTITEXCOORD4FVPROC											glMultiTexCoord4fv;											/*! MultiTexCoord4i OGL function	*/
	PFNGLMULTITEXCOORD4IPROC											glMultiTexCoord4i;											/*! MultiTexCoord4iv OGL function	*/
	PFNGLMULTITEXCOORD4IVPROC											glMultiTexCoord4iv;											/*! MultiTexCoord4s OGL function	*/
	PFNGLMULTITEXCOORD4SPROC											glMultiTexCoord4s;											/*! MultiTexCoord4sv OGL function	*/
	PFNGLMULTITEXCOORD4SVPROC											glMultiTexCoord4sv;											/*! LoadTransposeMatrixf OGL function	*/
	PFNGLLOADTRANSPOSEMATRIXFPROC										glLoadTransposeMatrixf;										/*! LoadTransposeMatrixd OGL function	*/
	PFNGLLOADTRANSPOSEMATRIXDPROC										glLoadTransposeMatrixd;										/*! MultTransposeMatrixf OGL function	*/
	PFNGLMULTTRANSPOSEMATRIXFPROC										glMultTransposeMatrixf;										/*! MultTransposeMatrixd OGL function	*/
	PFNGLMULTTRANSPOSEMATRIXDPROC										glMultTransposeMatrixd;										/*! SampleCoverage OGL function	*/
	PFNGLSAMPLECOVERAGEPROC												glSampleCoverage;											/*! CompressedTexImage3D OGL function	*/
	PFNGLCOMPRESSEDTEXIMAGE3DPROC										glCompressedTexImage3D;										/*! CompressedTexImage2D OGL function	*/
	PFNGLCOMPRESSEDTEXIMAGE2DPROC										glCompressedTexImage2D;										/*! CompressedTexImage1D OGL function	*/
	PFNGLCOMPRESSEDTEXIMAGE1DPROC										glCompressedTexImage1D;										/*! CompressedTexSubImage3D OGL function	*/
	PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC									glCompressedTexSubImage3D;									/*! CompressedTexSubImage2D OGL function	*/
	PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC									glCompressedTexSubImage2D;									/*! CompressedTexSubImage1D OGL function	*/
	PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC									glCompressedTexSubImage1D;									/*! GetCompressedTexImage OGL function	*/
	PFNGLGETCOMPRESSEDTEXIMAGEPROC										glGetCompressedTexImage;
																																	/*! ActiveTextureARB OGL function	*/
	PFNGLACTIVETEXTUREPROC												glActiveTextureARB;											/*! ClientActiveTextureARB OGL function	*/
	PFNGLCLIENTACTIVETEXTUREARBPROC										glClientActiveTextureARB;									/*! MultiTexCoord1dARB OGL function	*/
	PFNGLMULTITEXCOORD1DARBPROC											glMultiTexCoord1dARB;										/*! MultiTexCoord1dvARB OGL function	*/
	PFNGLMULTITEXCOORD1DVARBPROC										glMultiTexCoord1dvARB;										/*! MultiTexCoord1fARB OGL function	*/
	PFNGLMULTITEXCOORD1FARBPROC											glMultiTexCoord1fARB;										/*! MultiTexCoord1fvARB OGL function	*/
	PFNGLMULTITEXCOORD1FVARBPROC										glMultiTexCoord1fvARB;										/*! MultiTexCoord1iARB OGL function	*/
	PFNGLMULTITEXCOORD1IARBPROC											glMultiTexCoord1iARB;										/*! MultiTexCoord1ivARB OGL function	*/
	PFNGLMULTITEXCOORD1IVARBPROC										glMultiTexCoord1ivARB;										/*! MultiTexCoord1sARB OGL function	*/
	PFNGLMULTITEXCOORD1SARBPROC											glMultiTexCoord1sARB;										/*! MultiTexCoord1svARB OGL function	*/
	PFNGLMULTITEXCOORD1SVARBPROC										glMultiTexCoord1svARB;										/*! MultiTexCoord2dARB OGL function	*/
	PFNGLMULTITEXCOORD2DARBPROC											glMultiTexCoord2dARB;										/*! MultiTexCoord2dvARB OGL function	*/
	PFNGLMULTITEXCOORD2DVARBPROC										glMultiTexCoord2dvARB;										/*! MultiTexCoord2fARB OGL function	*/
	PFNGLMULTITEXCOORD2FARBPROC											glMultiTexCoord2fARB;										/*! MultiTexCoord2fvARB OGL function	*/
	PFNGLMULTITEXCOORD2FVARBPROC										glMultiTexCoord2fvARB;										/*! MultiTexCoord2iARB OGL function	*/
	PFNGLMULTITEXCOORD2IARBPROC											glMultiTexCoord2iARB;										/*! MultiTexCoord2ivARB OGL function	*/
	PFNGLMULTITEXCOORD2IVARBPROC										glMultiTexCoord2ivARB;										/*! MultiTexCoord2sARB OGL function	*/
	PFNGLMULTITEXCOORD2SARBPROC											glMultiTexCoord2sARB;										/*! MultiTexCoord2svARB OGL function	*/
	PFNGLMULTITEXCOORD2SVARBPROC										glMultiTexCoord2svARB;										/*! MultiTexCoord3dARB OGL function	*/
	PFNGLMULTITEXCOORD3DARBPROC											glMultiTexCoord3dARB;										/*! MultiTexCoord3dvARB OGL function	*/
	PFNGLMULTITEXCOORD3DVARBPROC										glMultiTexCoord3dvARB;										/*! MultiTexCoord3fARB OGL function	*/
	PFNGLMULTITEXCOORD3FARBPROC											glMultiTexCoord3fARB;										/*! MultiTexCoord3fvARB OGL function	*/
	PFNGLMULTITEXCOORD3FVARBPROC										glMultiTexCoord3fvARB;										/*! MultiTexCoord3iARB OGL function	*/
	PFNGLMULTITEXCOORD3IARBPROC											glMultiTexCoord3iARB;										/*! MultiTexCoord3ivARB OGL function	*/
	PFNGLMULTITEXCOORD3IVARBPROC										glMultiTexCoord3ivARB;										/*! MultiTexCoord3sARB OGL function	*/
	PFNGLMULTITEXCOORD3SARBPROC											glMultiTexCoord3sARB;										/*! MultiTexCoord3svARB OGL function	*/
	PFNGLMULTITEXCOORD3SVARBPROC										glMultiTexCoord3svARB;										/*! MultiTexCoord4dARB OGL function	*/
	PFNGLMULTITEXCOORD4DARBPROC											glMultiTexCoord4dARB;										/*! MultiTexCoord4dvARB OGL function	*/
	PFNGLMULTITEXCOORD4DVARBPROC										glMultiTexCoord4dvARB;										/*! MultiTexCoord4fARB OGL function	*/
	PFNGLMULTITEXCOORD4FARBPROC											glMultiTexCoord4fARB;										/*! MultiTexCoord4fvARB OGL function	*/
	PFNGLMULTITEXCOORD4FVARBPROC										glMultiTexCoord4fvARB;										/*! MultiTexCoord4iARB OGL function	*/
	PFNGLMULTITEXCOORD4IARBPROC											glMultiTexCoord4iARB;										/*! MultiTexCoord4ivARB OGL function	*/
	PFNGLMULTITEXCOORD4IVARBPROC										glMultiTexCoord4ivARB;										/*! MultiTexCoord4sARB OGL function	*/
	PFNGLMULTITEXCOORD4SARBPROC											glMultiTexCoord4sARB;										/*! MultiTexCoord4svARB OGL function	*/
	PFNGLMULTITEXCOORD4SVARBPROC										glMultiTexCoord4svARB;
																																	/*! LoadTransposeMatrixfARB OGL function	*/
	PFNGLLOADTRANSPOSEMATRIXFARBPROC									glLoadTransposeMatrixfARB;									/*! LoadTransposeMatrixdARB OGL function	*/
	PFNGLLOADTRANSPOSEMATRIXDARBPROC									glLoadTransposeMatrixdARB;									/*! MultTransposeMatrixfARB OGL function	*/
	PFNGLMULTTRANSPOSEMATRIXFARBPROC									glMultTransposeMatrixfARB;									/*! MultTransposeMatrixdARB OGL function	*/
	PFNGLMULTTRANSPOSEMATRIXDARBPROC									glMultTransposeMatrixdARB;
																																	/*! SampleCoverageARB OGL function	*/
	PFNGLSAMPLECOVERAGEARBPROC											glSampleCoverageARB;
																																	/*! CompressedTexImage3DARB OGL function	*/
	PFNGLCOMPRESSEDTEXIMAGE3DARBPROC									glCompressedTexImage3DARB;									/*! CompressedTexImage2DARB OGL function	*/
	PFNGLCOMPRESSEDTEXIMAGE2DARBPROC									glCompressedTexImage2DARB;									/*! CompressedTexImage1DARB OGL function	*/
	PFNGLCOMPRESSEDTEXIMAGE1DARBPROC									glCompressedTexImage1DARB;									/*! CompressedTexSubImage3DARB OGL function	*/
	PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC									glCompressedTexSubImage3DARB;								/*! CompressedTexSubImage2DARB OGL function	*/
	PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC									glCompressedTexSubImage2DARB;								/*! CompressedTexSubImage1DARB OGL function	*/
	PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC									glCompressedTexSubImage1DARB;								/*! GetCompressedTexImageARB OGL function	*/
	PFNGLGETCOMPRESSEDTEXIMAGEARBPROC									glGetCompressedTexImageARB;
																																	/*! PointParameterfARB OGL function	*/
	PFNGLPOINTPARAMETERFARBPROC											glPointParameterfARB;										/*! PointParameterfvARB OGL function	*/
	PFNGLPOINTPARAMETERFVARBPROC										glPointParameterfvARB;
																																	/*! WeightbvARB OGL function	*/
	PFNGLWEIGHTBVARBPROC												glWeightbvARB;												/*! WeightsvARB OGL function	*/
	PFNGLWEIGHTSVARBPROC												glWeightsvARB;												/*! WeightivARB OGL function	*/
	PFNGLWEIGHTIVARBPROC												glWeightivARB;												/*! WeightfvARB OGL function	*/
	PFNGLWEIGHTFVARBPROC												glWeightfvARB;												/*! WeightdvARB OGL function	*/
	PFNGLWEIGHTDVARBPROC												glWeightdvARB;												/*! WeightubvARB OGL function	*/
	PFNGLWEIGHTUBVARBPROC												glWeightubvARB;												/*! WeightusvARB OGL function	*/
	PFNGLWEIGHTUSVARBPROC												glWeightusvARB;												/*! WeightuivARB OGL function	*/
	PFNGLWEIGHTUIVARBPROC												glWeightuivARB;												/*! WeightPointerARB OGL function	*/
	PFNGLWEIGHTPOINTERARBPROC											glWeightPointerARB;											/*! VertexBlendARB OGL function	*/
	PFNGLVERTEXBLENDARBPROC												glVertexBlendARB;

																																	/*! CurrentPaletteMatrixARB OGL function	*/
	PFNGLCURRENTPALETTEMATRIXARBPROC									glCurrentPaletteMatrixARB;									/*! MatrixIndexubvARB OGL function	*/
	PFNGLMATRIXINDEXUBVARBPROC											glMatrixIndexubvARB;										/*! MatrixIndexusvARB OGL function	*/
	PFNGLMATRIXINDEXUSVARBPROC											glMatrixIndexusvARB;										/*! MatrixIndexuivARB OGL function	*/
	PFNGLMATRIXINDEXUIVARBPROC											glMatrixIndexuivARB;										/*! MatrixIndexPointerARB OGL function	*/
	PFNGLMATRIXINDEXPOINTERARBPROC										glMatrixIndexPointerARB;
																																	/*! WindowPos2dARB OGL function	*/
	PFNGLWINDOWPOS2DARBPROC												glWindowPos2dARB;											/*! WindowPos2dvARB OGL function	*/
	PFNGLWINDOWPOS2DVARBPROC											glWindowPos2dvARB;											/*! WindowPos2fARB OGL function	*/
	PFNGLWINDOWPOS2FARBPROC												glWindowPos2fARB;											/*! WindowPos2fvARB OGL function	*/
	PFNGLWINDOWPOS2FVARBPROC											glWindowPos2fvARB;											/*! WindowPos2iARB OGL function	*/
	PFNGLWINDOWPOS2IARBPROC												glWindowPos2iARB;											/*! WindowPos2ivARB OGL function	*/
	PFNGLWINDOWPOS2IVARBPROC											glWindowPos2ivARB;											/*! WindowPos2sARB OGL function	*/
	PFNGLWINDOWPOS2SARBPROC												glWindowPos2sARB;											/*! WindowPos2svARB OGL function	*/
	PFNGLWINDOWPOS2SVARBPROC											glWindowPos2svARB;											/*! WindowPos3dARB OGL function	*/
	PFNGLWINDOWPOS3DARBPROC												glWindowPos3dARB;											/*! WindowPos3dvARB OGL function	*/
	PFNGLWINDOWPOS3DVARBPROC											glWindowPos3dvARB;											/*! WindowPos3fARB OGL function	*/
	PFNGLWINDOWPOS3FARBPROC												glWindowPos3fARB;											/*! WindowPos3fvARB OGL function	*/
	PFNGLWINDOWPOS3FVARBPROC											glWindowPos3fvARB;											/*! WindowPos3iARB OGL function	*/
	PFNGLWINDOWPOS3IARBPROC												glWindowPos3iARB;											/*! WindowPos3ivARB OGL function	*/
	PFNGLWINDOWPOS3IVARBPROC											glWindowPos3ivARB;											/*! WindowPos3sARB OGL function	*/
	PFNGLWINDOWPOS3SARBPROC												glWindowPos3sARB;											/*! WindowPos3svARB OGL function	*/
	PFNGLWINDOWPOS3SVARBPROC											glWindowPos3svARB;
																																	/*! BlendColorEXT OGL function	*/
	PFNGLBLENDCOLOREXTPROC												glBlendColorEXT;
																																	/*! PolygonOffsetEXT OGL function	*/
	PFNGLPOLYGONOFFSETEXTPROC											glPolygonOffsetEXT;
																																	/*! TexImage3DEXT OGL function	*/
	PFNGLTEXIMAGE3DEXTPROC												glTexImage3DEXT;											/*! TexSubImage3DEXT OGL function	*/
	PFNGLTEXSUBIMAGE3DEXTPROC											glTexSubImage3DEXT;
																																	/*! GetTexFilterFuncSGIS OGL function	*/
	PFNGLGETTEXFILTERFUNCSGISPROC										glGetTexFilterFuncSGIS;										/*! TexFilterFuncSGIS OGL function	*/
	PFNGLTEXFILTERFUNCSGISPROC											glTexFilterFuncSGIS;
																																	/*! TexSubImage1DEXT OGL function	*/
	PFNGLTEXSUBIMAGE1DEXTPROC											glTexSubImage1DEXT;											/*! TexSubImage2DEXT OGL function	*/
	PFNGLTEXSUBIMAGE2DEXTPROC											glTexSubImage2DEXT;
																																	/*! CopyTexImage1DEXT OGL function	*/
	PFNGLCOPYTEXIMAGE1DEXTPROC											glCopyTexImage1DEXT;										/*! CopyTexImage2DEXT OGL function	*/
	PFNGLCOPYTEXIMAGE2DEXTPROC											glCopyTexImage2DEXT;										/*! CopyTexSubImage1DEXT OGL function	*/
	PFNGLCOPYTEXSUBIMAGE1DEXTPROC										glCopyTexSubImage1DEXT;										/*! CopyTexSubImage2DEXT OGL function	*/
	PFNGLCOPYTEXSUBIMAGE2DEXTPROC										glCopyTexSubImage2DEXT;										/*! CopyTexSubImage3DEXT OGL function	*/
	PFNGLCOPYTEXSUBIMAGE3DEXTPROC										glCopyTexSubImage3DEXT;
																																	/*! GetHistogramEXT OGL function	*/
	PFNGLGETHISTOGRAMEXTPROC											glGetHistogramEXT;											/*! GetHistogramParameterfvEXT OGL function	*/
	PFNGLGETHISTOGRAMPARAMETERFVEXTPROC									glGetHistogramParameterfvEXT;								/*! GetHistogramParameterivEXT OGL function	*/
	PFNGLGETHISTOGRAMPARAMETERIVEXTPROC									glGetHistogramParameterivEXT;								/*! GetMinmaxEXT OGL function	*/
	PFNGLGETMINMAXEXTPROC												glGetMinmaxEXT;												/*! GetMinmaxParameterfvEXT OGL function	*/
	PFNGLGETMINMAXPARAMETERFVEXTPROC									glGetMinmaxParameterfvEXT;									/*! GetMinmaxParameterivEXT OGL function	*/
	PFNGLGETMINMAXPARAMETERIVEXTPROC									glGetMinmaxParameterivEXT;									/*! HistogramEXT OGL function	*/
	PFNGLHISTOGRAMEXTPROC												glHistogramEXT;												/*! MinmaxEXT OGL function	*/
	PFNGLMINMAXEXTPROC													glMinmaxEXT;												/*! ResetHistogramEXT OGL function	*/
	PFNGLRESETHISTOGRAMEXTPROC											glResetHistogramEXT;										/*! ResetMinmaxEXT OGL function	*/
	PFNGLRESETMINMAXEXTPROC												glResetMinmaxEXT;
																																	/*! ConvolutionFilter1DEXT OGL function	*/
	PFNGLCONVOLUTIONFILTER1DEXTPROC										glConvolutionFilter1DEXT;									/*! ConvolutionFilter2DEXT OGL function	*/
	PFNGLCONVOLUTIONFILTER2DEXTPROC										glConvolutionFilter2DEXT;									/*! ConvolutionParameterfEXT OGL function	*/
	PFNGLCONVOLUTIONPARAMETERFEXTPROC									glConvolutionParameterfEXT;									/*! ConvolutionParameterfvEXT OGL function	*/
	PFNGLCONVOLUTIONPARAMETERFVEXTPROC									glConvolutionParameterfvEXT;								/*! ConvolutionParameteriEXT OGL function	*/
	PFNGLCONVOLUTIONPARAMETERIEXTPROC									glConvolutionParameteriEXT;									/*! ConvolutionParameterivEXT OGL function	*/
	PFNGLCONVOLUTIONPARAMETERIVEXTPROC									glConvolutionParameterivEXT;								/*! CopyConvolutionFilter1DEXT OGL function	*/
	PFNGLCOPYCONVOLUTIONFILTER1DEXTPROC									glCopyConvolutionFilter1DEXT;								/*! CopyConvolutionFilter2DEXT OGL function	*/
	PFNGLCOPYCONVOLUTIONFILTER2DEXTPROC									glCopyConvolutionFilter2DEXT;								/*! GetConvolutionFilterEXT OGL function	*/
	PFNGLGETCONVOLUTIONFILTEREXTPROC									glGetConvolutionFilterEXT;									/*! GetConvolutionParameterfvEXT OGL function	*/
	PFNGLGETCONVOLUTIONPARAMETERFVEXTPROC								glGetConvolutionParameterfvEXT;								/*! GetConvolutionParameterivEXT OGL function	*/
	PFNGLGETCONVOLUTIONPARAMETERIVEXTPROC								glGetConvolutionParameterivEXT;								/*! GetSeparableFilterEXT OGL function	*/
	PFNGLGETSEPARABLEFILTEREXTPROC										glGetSeparableFilterEXT;									/*! SeparableFilter2DEXT OGL function	*/
	PFNGLSEPARABLEFILTER2DEXTPROC										glSeparableFilter2DEXT;
																																	/*! ColorTableSGI OGL function	*/
	PFNGLCOLORTABLESGIPROC												glColorTableSGI;											/*! ColorTableParameterfvSGI OGL function	*/
	PFNGLCOLORTABLEPARAMETERFVSGIPROC									glColorTableParameterfvSGI;									/*! ColorTableParameterivSGI OGL function	*/
	PFNGLCOLORTABLEPARAMETERIVSGIPROC									glColorTableParameterivSGI;									/*! CopyColorTableSGI OGL function	*/
	PFNGLCOPYCOLORTABLESGIPROC											glCopyColorTableSGI;										/*! GetColorTableSGI OGL function	*/
	PFNGLGETCOLORTABLESGIPROC											glGetColorTableSGI;											/*! GetColorTableParameterfvSGI OGL function	*/
	PFNGLGETCOLORTABLEPARAMETERFVSGIPROC								glGetColorTableParameterfvSGI;								/*! GetColorTableParameterivSGI OGL function	*/
	PFNGLGETCOLORTABLEPARAMETERIVSGIPROC								glGetColorTableParameterivSGI;
																																	/*! PixelTexGenSGIX OGL function	*/
	PFNGLPIXELTEXGENSGIXPROC											glPixelTexGenSGIX;
																																	/*! PixelTexGenParameteriSGIS OGL function	*/
	PFNGLPIXELTEXGENPARAMETERISGISPROC									glPixelTexGenParameteriSGIS;								/*! PixelTexGenParameterivSGIS OGL function	*/
	PFNGLPIXELTEXGENPARAMETERIVSGISPROC									glPixelTexGenParameterivSGIS;								/*! PixelTexGenParameterfSGIS OGL function	*/
	PFNGLPIXELTEXGENPARAMETERFSGISPROC									glPixelTexGenParameterfSGIS;								/*! PixelTexGenParameterfvSGIS OGL function	*/
	PFNGLPIXELTEXGENPARAMETERFVSGISPROC									glPixelTexGenParameterfvSGIS;								/*! GetPixelTexGenParameterivSGIS OGL function	*/
	PFNGLGETPIXELTEXGENPARAMETERIVSGISPROC								glGetPixelTexGenParameterivSGIS;							/*! GetPixelTexGenParameterfvSGIS OGL function	*/
	PFNGLGETPIXELTEXGENPARAMETERFVSGISPROC								glGetPixelTexGenParameterfvSGIS;
																																	/*! TexImage4DSGIS OGL function	*/
	PFNGLTEXIMAGE4DSGISPROC												glTexImage4DSGIS;											/*! TexSubImage4DSGIS OGL function	*/
	PFNGLTEXSUBIMAGE4DSGISPROC											glTexSubImage4DSGIS;
																																	/*! AreTexturesResidentEXT OGL function	*/
	PFNGLARETEXTURESRESIDENTEXTPROC										glAreTexturesResidentEXT;									/*! BindTextureEXT OGL function	*/
	PFNGLBINDTEXTUREEXTPROC												glBindTextureEXT;											/*! DeleteTexturesEXT OGL function	*/
	PFNGLDELETETEXTURESEXTPROC											glDeleteTexturesEXT;										/*! GenTexturesEXT OGL function	*/
	PFNGLGENTEXTURESEXTPROC												glGenTexturesEXT;											/*! IsTextureEXT OGL function	*/
	PFNGLISTEXTUREEXTPROC												glIsTextureEXT;												/*! PrioritizeTexturesEXT OGL function	*/
	PFNGLPRIORITIZETEXTURESEXTPROC										glPrioritizeTexturesEXT;
																																	/*! DetailTexFuncSGIS OGL function	*/
	PFNGLDETAILTEXFUNCSGISPROC											glDetailTexFuncSGIS;										/*! GetDetailTexFuncSGIS OGL function	*/
	PFNGLGETDETAILTEXFUNCSGISPROC										glGetDetailTexFuncSGIS;
																																	/*! SharpenTexFuncSGIS OGL function	*/
	PFNGLSHARPENTEXFUNCSGISPROC											glSharpenTexFuncSGIS;										/*! GetSharpenTexFuncSGIS OGL function	*/
	PFNGLGETSHARPENTEXFUNCSGISPROC										glGetSharpenTexFuncSGIS;
																																	/*! SampleMaskSGIS OGL function	*/
	PFNGLSAMPLEMASKSGISPROC												glSampleMaskSGIS;											/*! SamplePatternSGIS OGL function	*/
	PFNGLSAMPLEPATTERNSGISPROC											glSamplePatternSGIS;
																																	/*! ArrayElementEXT OGL function	*/
	PFNGLARRAYELEMENTEXTPROC											glArrayElementEXT;											/*! ColorPointerEXT OGL function	*/
	PFNGLCOLORPOINTEREXTPROC											glColorPointerEXT;											/*! DrawArraysEXT OGL function	*/
	PFNGLDRAWARRAYSEXTPROC												glDrawArraysEXT;											/*! EdgeFlagPointerEXT OGL function	*/
	PFNGLEDGEFLAGPOINTEREXTPROC											glEdgeFlagPointerEXT;										/*! GetPointervEXT OGL function	*/
	PFNGLGETPOINTERVEXTPROC												glGetPointervEXT;											/*! IndexPointerEXT OGL function	*/
	PFNGLINDEXPOINTEREXTPROC											glIndexPointerEXT;											/*! NormalPointerEXT OGL function	*/
	PFNGLNORMALPOINTEREXTPROC											glNormalPointerEXT;											/*! TexCoordPointerEXT OGL function	*/
	PFNGLTEXCOORDPOINTEREXTPROC											glTexCoordPointerEXT;										/*! VertexPointerEXT OGL function	*/
	PFNGLVERTEXPOINTEREXTPROC											glVertexPointerEXT;
																																	/*! BlendEquationEXT OGL function	*/
	PFNGLBLENDEQUATIONEXTPROC											glBlendEquationEXT;
																																	/*! SpriteParameterfSGIX OGL function	*/
	PFNGLSPRITEPARAMETERFSGIXPROC										glSpriteParameterfSGIX;										/*! SpriteParameterfvSGIX OGL function	*/
	PFNGLSPRITEPARAMETERFVSGIXPROC										glSpriteParameterfvSGIX;									/*! SpriteParameteriSGIX OGL function	*/
	PFNGLSPRITEPARAMETERISGIXPROC										glSpriteParameteriSGIX;										/*! SpriteParameterivSGIX OGL function	*/
	PFNGLSPRITEPARAMETERIVSGIXPROC										glSpriteParameterivSGIX;
																																	/*! PointParameterfEXT OGL function	*/
	PFNGLPOINTPARAMETERFEXTPROC											glPointParameterfEXT;										/*! PointParameterfvEXT OGL function	*/
	PFNGLPOINTPARAMETERFVEXTPROC										glPointParameterfvEXT;
																																	/*! PointParameterfSGIS OGL function	*/
	PFNGLPOINTPARAMETERFSGISPROC										glPointParameterfSGIS;										/*! PointParameterfvSGIS OGL function	*/
	PFNGLPOINTPARAMETERFVSGISPROC										glPointParameterfvSGIS;
																																	/*! GetInstrumentsSGIX OGL function	*/
	PFNGLGETINSTRUMENTSSGIXPROC											glGetInstrumentsSGIX;										/*! InstrumentsBufferSGIX OGL function	*/
	PFNGLINSTRUMENTSBUFFERSGIXPROC										glInstrumentsBufferSGIX;									/*! PollInstrumentsSGIX OGL function	*/
	PFNGLPOLLINSTRUMENTSSGIXPROC										glPollInstrumentsSGIX;										/*! ReadInstrumentsSGIX OGL function	*/
	PFNGLREADINSTRUMENTSSGIXPROC										glReadInstrumentsSGIX;										/*! StartInstrumentsSGIX OGL function	*/
	PFNGLSTARTINSTRUMENTSSGIXPROC										glStartInstrumentsSGIX;										/*! StopInstrumentsSGIX OGL function	*/
	PFNGLSTOPINSTRUMENTSSGIXPROC										glStopInstrumentsSGIX;
																																	/*! FrameZoomSGIX OGL function	*/
	PFNGLFRAMEZOOMSGIXPROC												glFrameZoomSGIX;
																																	/*! TagSampleBufferSGIX OGL function	*/
	PFNGLTAGSAMPLEBUFFERSGIXPROC										glTagSampleBufferSGIX;
																																	/*! DeformationMap3dSGIX OGL function	*/
	PFNGLDEFORMATIONMAP3DSGIXPROC										glDeformationMap3dSGIX;										/*! DeformationMap3fSGIX OGL function	*/
	PFNGLDEFORMATIONMAP3FSGIXPROC										glDeformationMap3fSGIX;										/*! DeformSGIX OGL function	*/
	PFNGLDEFORMSGIXPROC													glDeformSGIX;												/*! LoadIdentityDeformationMapSGIX OGL function	*/
	PFNGLLOADIDENTITYDEFORMATIONMAPSGIXPROC								glLoadIdentityDeformationMapSGIX;
																																	/*! ReferencePlaneSGIX OGL function	*/
	PFNGLREFERENCEPLANESGIXPROC											glReferencePlaneSGIX;
																																	/*! FlushRasterSGIX OGL function	*/
	PFNGLFLUSHRASTERSGIXPROC											glFlushRasterSGIX;
																																	/*! FogFuncSGIS OGL function	*/
	PFNGLFOGFUNCSGISPROC												glFogFuncSGIS;												/*! GetFogFuncSGIS OGL function	*/
	PFNGLGETFOGFUNCSGISPROC												glGetFogFuncSGIS;
																																	/*! ImageTransformParameteriHP OGL function	*/
	PFNGLIMAGETRANSFORMPARAMETERIHPPROC									glImageTransformParameteriHP;								/*! ImageTransformParameterfHP OGL function	*/
	PFNGLIMAGETRANSFORMPARAMETERFHPPROC									glImageTransformParameterfHP;								/*! ImageTransformParameterivHP OGL function	*/
	PFNGLIMAGETRANSFORMPARAMETERIVHPPROC								glImageTransformParameterivHP;								/*! ImageTransformParameterfvHP OGL function	*/
	PFNGLIMAGETRANSFORMPARAMETERFVHPPROC								glImageTransformParameterfvHP;								/*! GetImageTransformParameterivHP OGL function	*/
	PFNGLGETIMAGETRANSFORMPARAMETERIVHPPROC								glGetImageTransformParameterivHP;							/*! GetImageTransformParameterfvHP OGL function	*/
	PFNGLGETIMAGETRANSFORMPARAMETERFVHPPROC								glGetImageTransformParameterfvHP;
																																	/*! ColorSubTableEXT OGL function	*/
	PFNGLCOLORSUBTABLEEXTPROC											glColorSubTableEXT;											/*! CopyColorSubTableEXT OGL function	*/
	PFNGLCOPYCOLORSUBTABLEEXTPROC										glCopyColorSubTableEXT;
																																	/*! HintPGI OGL function	*/
	PFNGLHINTPGIPROC													glHintPGI;
																																	/*! ColorTableEXT OGL function	*/
	PFNGLCOLORTABLEEXTPROC												glColorTableEXT;											/*! GetColorTableEXT OGL function	*/
	PFNGLGETCOLORTABLEEXTPROC											glGetColorTableEXT;											/*! GetColorTableParameterivEXT OGL function	*/
	PFNGLGETCOLORTABLEPARAMETERIVEXTPROC								glGetColorTableParameterivEXT;								/*! GetColorTableParameterfvEXT OGL function	*/
	PFNGLGETCOLORTABLEPARAMETERFVEXTPROC								glGetColorTableParameterfvEXT;
																																	/*! GetListParameterfvSGIX OGL function	*/
	PFNGLGETLISTPARAMETERFVSGIXPROC										glGetListParameterfvSGIX;									/*! GetListParameterivSGIX OGL function	*/
	PFNGLGETLISTPARAMETERIVSGIXPROC										glGetListParameterivSGIX;									/*! ListParameterfSGIX OGL function	*/
	PFNGLLISTPARAMETERFSGIXPROC											glListParameterfSGIX;										/*! ListParameterfvSGIX OGL function	*/
	PFNGLLISTPARAMETERFVSGIXPROC										glListParameterfvSGIX;										/*! ListParameteriSGIX OGL function	*/
	PFNGLLISTPARAMETERISGIXPROC											glListParameteriSGIX;										/*! ListParameterivSGIX OGL function	*/
	PFNGLLISTPARAMETERIVSGIXPROC										glListParameterivSGIX;
																																	/*! IndexMaterialEXT OGL function	*/
	PFNGLINDEXMATERIALEXTPROC											glIndexMaterialEXT;
																																	/*! IndexFuncEXT OGL function	*/
	PFNGLINDEXFUNCEXTPROC												glIndexFuncEXT;
																																	/*! LockArraysEXT OGL function	*/
	PFNGLLOCKARRAYSEXTPROC												glLockArraysEXT;											/*! UnlockArraysEXT OGL function	*/
	PFNGLUNLOCKARRAYSEXTPROC											glUnlockArraysEXT;
																																	/*! CullParameterdvEXT OGL function	*/
	PFNGLCULLPARAMETERDVEXTPROC											glCullParameterdvEXT;										/*! CullParameterfvEXT OGL function	*/
	PFNGLCULLPARAMETERFVEXTPROC											glCullParameterfvEXT;
																																	/*! FragmentColorMaterialSGIX OGL function	*/
	PFNGLFRAGMENTCOLORMATERIALSGIXPROC									glFragmentColorMaterialSGIX;								/*! FragmentLightfSGIX OGL function	*/
	PFNGLFRAGMENTLIGHTFSGIXPROC											glFragmentLightfSGIX;										/*! FragmentLightfvSGIX OGL function	*/
	PFNGLFRAGMENTLIGHTFVSGIXPROC										glFragmentLightfvSGIX;										/*! FragmentLightiSGIX OGL function	*/
	PFNGLFRAGMENTLIGHTISGIXPROC											glFragmentLightiSGIX;										/*! FragmentLightivSGIX OGL function	*/
	PFNGLFRAGMENTLIGHTIVSGIXPROC										glFragmentLightivSGIX;										/*! FragmentLightModelfSGIX OGL function	*/
	PFNGLFRAGMENTLIGHTMODELFSGIXPROC									glFragmentLightModelfSGIX;									/*! FragmentLightModelfvSGIX OGL function	*/
	PFNGLFRAGMENTLIGHTMODELFVSGIXPROC									glFragmentLightModelfvSGIX;									/*! FragmentLightModeliSGIX OGL function	*/
	PFNGLFRAGMENTLIGHTMODELISGIXPROC									glFragmentLightModeliSGIX;									/*! FragmentLightModelivSGIX OGL function	*/
	PFNGLFRAGMENTLIGHTMODELIVSGIXPROC									glFragmentLightModelivSGIX;									/*! FragmentMaterialfSGIX OGL function	*/
	PFNGLFRAGMENTMATERIALFSGIXPROC										glFragmentMaterialfSGIX;									/*! FragmentMaterialfvSGIX OGL function	*/
	PFNGLFRAGMENTMATERIALFVSGIXPROC										glFragmentMaterialfvSGIX;									/*! FragmentMaterialiSGIX OGL function	*/
	PFNGLFRAGMENTMATERIALISGIXPROC										glFragmentMaterialiSGIX;									/*! FragmentMaterialivSGIX OGL function	*/
	PFNGLFRAGMENTMATERIALIVSGIXPROC										glFragmentMaterialivSGIX;									/*! GetFragmentLightfvSGIX OGL function	*/
	PFNGLGETFRAGMENTLIGHTFVSGIXPROC										glGetFragmentLightfvSGIX;									/*! GetFragmentLightivSGIX OGL function	*/
	PFNGLGETFRAGMENTLIGHTIVSGIXPROC										glGetFragmentLightivSGIX;									/*! GetFragmentMaterialfvSGIX OGL function	*/
	PFNGLGETFRAGMENTMATERIALFVSGIXPROC									glGetFragmentMaterialfvSGIX;								/*! GetFragmentMaterialivSGIX OGL function	*/
	PFNGLGETFRAGMENTMATERIALIVSGIXPROC									glGetFragmentMaterialivSGIX;								/*! LightEnviSGIX OGL function	*/
	PFNGLLIGHTENVISGIXPROC												glLightEnviSGIX;
																																	/*! DrawRangeElementsEXT OGL function	*/
	PFNGLDRAWRANGEELEMENTSEXTPROC										glDrawRangeElementsEXT;
																																	/*! ApplyTextureEXT OGL function	*/
	PFNGLAPPLYTEXTUREEXTPROC											glApplyTextureEXT;											/*! TextureLightEXT OGL function	*/
	PFNGLTEXTURELIGHTEXTPROC											glTextureLightEXT;											/*! TextureMaterialEXT OGL function	*/
	PFNGLTEXTUREMATERIALEXTPROC											glTextureMaterialEXT;
																																	/*! AsyncMarkerSGIX OGL function	*/
	PFNGLASYNCMARKERSGIXPROC											glAsyncMarkerSGIX;											/*! FinishAsyncSGIX OGL function	*/
	PFNGLFINISHASYNCSGIXPROC											glFinishAsyncSGIX;											/*! PollAsyncSGIX OGL function	*/
	PFNGLPOLLASYNCSGIXPROC												glPollAsyncSGIX;											/*! GenAsyncMarkersSGIX OGL function	*/
	PFNGLGENASYNCMARKERSSGIXPROC										glGenAsyncMarkersSGIX;										/*! DeleteAsyncMarkersSGIX OGL function	*/
	PFNGLDELETEASYNCMARKERSSGIXPROC										glDeleteAsyncMarkersSGIX;									/*! IsAsyncMarkerSGIX OGL function	*/
	PFNGLISASYNCMARKERSGIXPROC											glIsAsyncMarkerSGIX;
																																	/*! VertexPointervINTEL OGL function	*/
	PFNGLVERTEXPOINTERVINTELPROC										glVertexPointervINTEL;										/*! NormalPointervINTEL OGL function	*/
	PFNGLNORMALPOINTERVINTELPROC										glNormalPointervINTEL;										/*! ColorPointervINTEL OGL function	*/
	PFNGLCOLORPOINTERVINTELPROC											glColorPointervINTEL;										/*! TexCoordPointervINTEL OGL function	*/
	PFNGLTEXCOORDPOINTERVINTELPROC										glTexCoordPointervINTEL;
																																	/*! PixelTransformParameteriEXT OGL function	*/
	PFNGLPIXELTRANSFORMPARAMETERIEXTPROC								glPixelTransformParameteriEXT;								/*! PixelTransformParameterfEXT OGL function	*/
	PFNGLPIXELTRANSFORMPARAMETERFEXTPROC								glPixelTransformParameterfEXT;								/*! PixelTransformParameterivEXT OGL function	*/
	PFNGLPIXELTRANSFORMPARAMETERIVEXTPROC								glPixelTransformParameterivEXT;								/*! PixelTransformParameterfvEXT OGL function	*/
	PFNGLPIXELTRANSFORMPARAMETERFVEXTPROC								glPixelTransformParameterfvEXT;
																																	/*! SecondaryColor3bEXT OGL function	*/
	PFNGLSECONDARYCOLOR3BEXTPROC										glSecondaryColor3bEXT;										/*! SecondaryColor3bvEXT OGL function	*/
	PFNGLSECONDARYCOLOR3BVEXTPROC										glSecondaryColor3bvEXT;										/*! SecondaryColor3dEXT OGL function	*/
	PFNGLSECONDARYCOLOR3DEXTPROC										glSecondaryColor3dEXT;										/*! SecondaryColor3dvEXT OGL function	*/
	PFNGLSECONDARYCOLOR3DVEXTPROC										glSecondaryColor3dvEXT;										/*! SecondaryColor3fEXT OGL function	*/
	PFNGLSECONDARYCOLOR3FEXTPROC										glSecondaryColor3fEXT;										/*! SecondaryColor3fvEXT OGL function	*/
	PFNGLSECONDARYCOLOR3FVEXTPROC										glSecondaryColor3fvEXT;										/*! SecondaryColor3iEXT OGL function	*/
	PFNGLSECONDARYCOLOR3IEXTPROC										glSecondaryColor3iEXT;										/*! SecondaryColor3ivEXT OGL function	*/
	PFNGLSECONDARYCOLOR3IVEXTPROC										glSecondaryColor3ivEXT;										/*! SecondaryColor3sEXT OGL function	*/
	PFNGLSECONDARYCOLOR3SEXTPROC										glSecondaryColor3sEXT;										/*! SecondaryColor3svEXT OGL function	*/
	PFNGLSECONDARYCOLOR3SVEXTPROC										glSecondaryColor3svEXT;										/*! SecondaryColor3ubEXT OGL function	*/
	PFNGLSECONDARYCOLOR3UBEXTPROC										glSecondaryColor3ubEXT;										/*! SecondaryColor3ubvEXT OGL function	*/
	PFNGLSECONDARYCOLOR3UBVEXTPROC										glSecondaryColor3ubvEXT;									/*! SecondaryColor3uiEXT OGL function	*/
	PFNGLSECONDARYCOLOR3UIEXTPROC										glSecondaryColor3uiEXT;										/*! SecondaryColor3uivEXT OGL function	*/
	PFNGLSECONDARYCOLOR3UIVEXTPROC										glSecondaryColor3uivEXT;									/*! SecondaryColor3usEXT OGL function	*/
	PFNGLSECONDARYCOLOR3USEXTPROC										glSecondaryColor3usEXT;										/*! SecondaryColor3usvEXT OGL function	*/
	PFNGLSECONDARYCOLOR3USVEXTPROC										glSecondaryColor3usvEXT;									/*! SecondaryColorPointerEXT OGL function	*/
	PFNGLSECONDARYCOLORPOINTEREXTPROC									glSecondaryColorPointerEXT;
																																	/*! TextureNormalEXT OGL function	*/
	PFNGLTEXTURENORMALEXTPROC											glTextureNormalEXT;
																																	/*! MultiDrawArraysEXT OGL function	*/
	PFNGLMULTIDRAWARRAYSEXTPROC											glMultiDrawArraysEXT;										/*! MultiDrawElementsEXT OGL function	*/
	PFNGLMULTIDRAWELEMENTSEXTPROC										glMultiDrawElementsEXT;
																																	/*! FogCoordfEXT OGL function	*/
	PFNGLFOGCOORDFEXTPROC												glFogCoordfEXT;												/*! FogCoordfvEXT OGL function	*/
	PFNGLFOGCOORDFVEXTPROC												glFogCoordfvEXT;											/*! FogCoorddEXT OGL function	*/
	PFNGLFOGCOORDDEXTPROC												glFogCoorddEXT;												/*! FogCoorddvEXT OGL function	*/
	PFNGLFOGCOORDDVEXTPROC												glFogCoorddvEXT;											/*! FogCoordPointerEXT OGL function	*/
	PFNGLFOGCOORDPOINTEREXTPROC											glFogCoordPointerEXT;
																																	/*! Tangent3bEXT OGL function	*/
	PFNGLTANGENT3BEXTPROC												glTangent3bEXT;												/*! Tangent3bvEXT OGL function	*/
	PFNGLTANGENT3BVEXTPROC												glTangent3bvEXT;											/*! Tangent3dEXT OGL function	*/
	PFNGLTANGENT3DEXTPROC												glTangent3dEXT;												/*! Tangent3dvEXT OGL function	*/
	PFNGLTANGENT3DVEXTPROC												glTangent3dvEXT;											/*! Tangent3fEXT OGL function	*/
	PFNGLTANGENT3FEXTPROC												glTangent3fEXT;												/*! Tangent3fvEXT OGL function	*/
	PFNGLTANGENT3FVEXTPROC												glTangent3fvEXT;											/*! Tangent3iEXT OGL function	*/
	PFNGLTANGENT3IEXTPROC												glTangent3iEXT;												/*! Tangent3ivEXT OGL function	*/
	PFNGLTANGENT3IVEXTPROC												glTangent3ivEXT;											/*! Tangent3sEXT OGL function	*/
	PFNGLTANGENT3SEXTPROC												glTangent3sEXT;												/*! Tangent3svEXT OGL function	*/
	PFNGLTANGENT3SVEXTPROC												glTangent3svEXT;											/*! Binormal3bEXT OGL function	*/
	PFNGLBINORMAL3BEXTPROC												glBinormal3bEXT;											/*! Binormal3bvEXT OGL function	*/
	PFNGLBINORMAL3BVEXTPROC												glBinormal3bvEXT;											/*! Binormal3dEXT OGL function	*/
	PFNGLBINORMAL3DEXTPROC												glBinormal3dEXT;											/*! Binormal3dvEXT OGL function	*/
	PFNGLBINORMAL3DVEXTPROC												glBinormal3dvEXT;											/*! Binormal3fEXT OGL function	*/
	PFNGLBINORMAL3FEXTPROC												glBinormal3fEXT;											/*! Binormal3fvEXT OGL function	*/
	PFNGLBINORMAL3FVEXTPROC												glBinormal3fvEXT;											/*! Binormal3iEXT OGL function	*/
	PFNGLBINORMAL3IEXTPROC												glBinormal3iEXT;											/*! Binormal3ivEXT OGL function	*/
	PFNGLBINORMAL3IVEXTPROC												glBinormal3ivEXT;											/*! Binormal3sEXT OGL function	*/
	PFNGLBINORMAL3SEXTPROC												glBinormal3sEXT;											/*! Binormal3svEXT OGL function	*/
	PFNGLBINORMAL3SVEXTPROC												glBinormal3svEXT;											/*! TangentPointerEXT OGL function	*/
	PFNGLTANGENTPOINTEREXTPROC											glTangentPointerEXT;										/*! BinormalPointerEXT OGL function	*/
	PFNGLBINORMALPOINTEREXTPROC											glBinormalPointerEXT;
																																	/*! FinishTextureSUNX OGL function	*/
	PFNGLFINISHTEXTURESUNXPROC											glFinishTextureSUNX;
																																	/*! GlobalAlphaFactorbSUN OGL function	*/
	PFNGLGLOBALALPHAFACTORBSUNPROC										glGlobalAlphaFactorbSUN;									/*! GlobalAlphaFactorsSUN OGL function	*/
	PFNGLGLOBALALPHAFACTORSSUNPROC										glGlobalAlphaFactorsSUN;									/*! GlobalAlphaFactoriSUN OGL function	*/
	PFNGLGLOBALALPHAFACTORISUNPROC										glGlobalAlphaFactoriSUN;									/*! GlobalAlphaFactorfSUN OGL function	*/
	PFNGLGLOBALALPHAFACTORFSUNPROC										glGlobalAlphaFactorfSUN;									/*! GlobalAlphaFactordSUN OGL function	*/
	PFNGLGLOBALALPHAFACTORDSUNPROC										glGlobalAlphaFactordSUN;									/*! GlobalAlphaFactorubSUN OGL function	*/
	PFNGLGLOBALALPHAFACTORUBSUNPROC										glGlobalAlphaFactorubSUN;									/*! GlobalAlphaFactorusSUN OGL function	*/
	PFNGLGLOBALALPHAFACTORUSSUNPROC										glGlobalAlphaFactorusSUN;									/*! GlobalAlphaFactoruiSUN OGL function	*/
	PFNGLGLOBALALPHAFACTORUISUNPROC										glGlobalAlphaFactoruiSUN;
																																	/*! ReplacementCodeuiSUN OGL function	*/
	PFNGLREPLACEMENTCODEUISUNPROC										glReplacementCodeuiSUN;										/*! ReplacementCodeusSUN OGL function	*/
	PFNGLREPLACEMENTCODEUSSUNPROC										glReplacementCodeusSUN;										/*! ReplacementCodeubSUN OGL function	*/
	PFNGLREPLACEMENTCODEUBSUNPROC										glReplacementCodeubSUN;										/*! ReplacementCodeuivSUN OGL function	*/
	PFNGLREPLACEMENTCODEUIVSUNPROC										glReplacementCodeuivSUN;									/*! ReplacementCodeusvSUN OGL function	*/
	PFNGLREPLACEMENTCODEUSVSUNPROC										glReplacementCodeusvSUN;									/*! ReplacementCodeubvSUN OGL function	*/
	PFNGLREPLACEMENTCODEUBVSUNPROC										glReplacementCodeubvSUN;									/*! ReplacementCodePointerSUN OGL function	*/
	PFNGLREPLACEMENTCODEPOINTERSUNPROC									glReplacementCodePointerSUN;
																																	/*! Color4ubVertex2fSUN OGL function	*/
	PFNGLCOLOR4UBVERTEX2FSUNPROC										glColor4ubVertex2fSUN;										/*! Color4ubVertex2fvSUN OGL function	*/
	PFNGLCOLOR4UBVERTEX2FVSUNPROC										glColor4ubVertex2fvSUN;										/*! Color4ubVertex3fSUN OGL function	*/
	PFNGLCOLOR4UBVERTEX3FSUNPROC										glColor4ubVertex3fSUN;										/*! Color4ubVertex3fvSUN OGL function	*/
	PFNGLCOLOR4UBVERTEX3FVSUNPROC										glColor4ubVertex3fvSUN;										/*! Color3fVertex3fSUN OGL function	*/
	PFNGLCOLOR3FVERTEX3FSUNPROC											glColor3fVertex3fSUN;										/*! Color3fVertex3fvSUN OGL function	*/
	PFNGLCOLOR3FVERTEX3FVSUNPROC										glColor3fVertex3fvSUN;										/*! Normal3fVertex3fSUN OGL function	*/
	PFNGLNORMAL3FVERTEX3FSUNPROC										glNormal3fVertex3fSUN;										/*! Normal3fVertex3fvSUN OGL function	*/
	PFNGLNORMAL3FVERTEX3FVSUNPROC										glNormal3fVertex3fvSUN;										/*! Color4fNormal3fVertex3fSUN OGL function	*/
	PFNGLCOLOR4FNORMAL3FVERTEX3FSUNPROC									glColor4fNormal3fVertex3fSUN;								/*! Color4fNormal3fVertex3fvSUN OGL function	*/
	PFNGLCOLOR4FNORMAL3FVERTEX3FVSUNPROC								glColor4fNormal3fVertex3fvSUN;								/*! TexCoord2fVertex3fSUN OGL function	*/
	PFNGLTEXCOORD2FVERTEX3FSUNPROC										glTexCoord2fVertex3fSUN;									/*! TexCoord2fVertex3fvSUN OGL function	*/
	PFNGLTEXCOORD2FVERTEX3FVSUNPROC										glTexCoord2fVertex3fvSUN;									/*! TexCoord4fVertex4fSUN OGL function	*/
	PFNGLTEXCOORD4FVERTEX4FSUNPROC										glTexCoord4fVertex4fSUN;									/*! TexCoord4fVertex4fvSUN OGL function	*/
	PFNGLTEXCOORD4FVERTEX4FVSUNPROC										glTexCoord4fVertex4fvSUN;									/*! TexCoord2fColor4ubVertex3fSUN OGL function	*/
	PFNGLTEXCOORD2FCOLOR4UBVERTEX3FSUNPROC								glTexCoord2fColor4ubVertex3fSUN;							/*! TexCoord2fColor4ubVertex3fvSUN OGL function	*/
	PFNGLTEXCOORD2FCOLOR4UBVERTEX3FVSUNPROC								glTexCoord2fColor4ubVertex3fvSUN;							/*! TexCoord2fColor3fVertex3fSUN OGL function	*/
	PFNGLTEXCOORD2FCOLOR3FVERTEX3FSUNPROC								glTexCoord2fColor3fVertex3fSUN;								/*! TexCoord2fColor3fVertex3fvSUN OGL function	*/
	PFNGLTEXCOORD2FCOLOR3FVERTEX3FVSUNPROC								glTexCoord2fColor3fVertex3fvSUN;							/*! TexCoord2fNormal3fVertex3fSUN OGL function	*/
	PFNGLTEXCOORD2FNORMAL3FVERTEX3FSUNPROC								glTexCoord2fNormal3fVertex3fSUN;							/*! TexCoord2fNormal3fVertex3fvSUN OGL function	*/
	PFNGLTEXCOORD2FNORMAL3FVERTEX3FVSUNPROC								glTexCoord2fNormal3fVertex3fvSUN;							/*! TexCoord2fColor4fNormal3fVertex3fSUN OGL function	*/
	PFNGLTEXCOORD2FCOLOR4FNORMAL3FVERTEX3FSUNPROC						glTexCoord2fColor4fNormal3fVertex3fSUN;						/*! TexCoord2fColor4fNormal3fVertex3fvSUN OGL function	*/
	PFNGLTEXCOORD2FCOLOR4FNORMAL3FVERTEX3FVSUNPROC						glTexCoord2fColor4fNormal3fVertex3fvSUN;					/*! TexCoord4fColor4fNormal3fVertex4fSUN OGL function	*/
	PFNGLTEXCOORD4FCOLOR4FNORMAL3FVERTEX4FSUNPROC						glTexCoord4fColor4fNormal3fVertex4fSUN;						/*! TexCoord4fColor4fNormal3fVertex4fvSUN OGL function	*/
	PFNGLTEXCOORD4FCOLOR4FNORMAL3FVERTEX4FVSUNPROC						glTexCoord4fColor4fNormal3fVertex4fvSUN;					/*! ReplacementCodeuiVertex3fSUN OGL function	*/
	PFNGLREPLACEMENTCODEUIVERTEX3FSUNPROC								glReplacementCodeuiVertex3fSUN;								/*! ReplacementCodeuiVertex3fvSUN OGL function	*/
	PFNGLREPLACEMENTCODEUIVERTEX3FVSUNPROC								glReplacementCodeuiVertex3fvSUN;							/*! ReplacementCodeuiColor4ubVertex3fSUN OGL function	*/
	PFNGLREPLACEMENTCODEUICOLOR4UBVERTEX3FSUNPROC						glReplacementCodeuiColor4ubVertex3fSUN;						/*! ReplacementCodeuiColor4ubVertex3fvSUN OGL function	*/
	PFNGLREPLACEMENTCODEUICOLOR4UBVERTEX3FVSUNPROC						glReplacementCodeuiColor4ubVertex3fvSUN;					/*! ReplacementCodeuiColor3fVertex3fSUN OGL function	*/
	PFNGLREPLACEMENTCODEUICOLOR3FVERTEX3FSUNPROC						glReplacementCodeuiColor3fVertex3fSUN;						/*! ReplacementCodeuiColor3fVertex3fvSUN OGL function	*/
	PFNGLREPLACEMENTCODEUICOLOR3FVERTEX3FVSUNPROC						glReplacementCodeuiColor3fVertex3fvSUN;						/*! ReplacementCodeuiNormal3fVertex3fSUN OGL function	*/
	PFNGLREPLACEMENTCODEUINORMAL3FVERTEX3FSUNPROC						glReplacementCodeuiNormal3fVertex3fSUN;						/*! ReplacementCodeuiNormal3fVertex3fvSUN OGL function	*/
	PFNGLREPLACEMENTCODEUINORMAL3FVERTEX3FVSUNPROC						glReplacementCodeuiNormal3fVertex3fvSUN;					/*! ReplacementCodeuiColor4fNormal3fVertex3fSUN OGL function	*/
	PFNGLREPLACEMENTCODEUICOLOR4FNORMAL3FVERTEX3FSUNPROC				glReplacementCodeuiColor4fNormal3fVertex3fSUN;				/*! ReplacementCodeuiColor4fNormal3fVertex3fvSUN OGL function	*/
	PFNGLREPLACEMENTCODEUICOLOR4FNORMAL3FVERTEX3FVSUNPROC				glReplacementCodeuiColor4fNormal3fVertex3fvSUN;				/*! ReplacementCodeuiTexCoord2fVertex3fSUN OGL function	*/
	PFNGLREPLACEMENTCODEUITEXCOORD2FVERTEX3FSUNPROC						glReplacementCodeuiTexCoord2fVertex3fSUN;					/*! ReplacementCodeuiTexCoord2fVertex3fvSUN OGL function	*/
	PFNGLREPLACEMENTCODEUITEXCOORD2FVERTEX3FVSUNPROC					glReplacementCodeuiTexCoord2fVertex3fvSUN;					/*! ReplacementCodeuiTexCoord2fNormal3fVertex3fSUN OGL function	*/
	PFNGLREPLACEMENTCODEUITEXCOORD2FNORMAL3FVERTEX3FSUNPROC				glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN;			/*! ReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN OGL function	*/
	PFNGLREPLACEMENTCODEUITEXCOORD2FNORMAL3FVERTEX3FVSUNPROC			glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN;			/*! ReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN OGL function	*/
	PFNGLREPLACEMENTCODEUITEXCOORD2FCOLOR4FNORMAL3FVERTEX3FSUNPROC		glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN;	/*! ReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN OGL function	*/
	PFNGLREPLACEMENTCODEUITEXCOORD2FCOLOR4FNORMAL3FVERTEX3FVSUNPROC		glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN;
																																	/*! BlendFuncSeparateEXT OGL function	*/
	PFNGLBLENDFUNCSEPARATEEXTPROC										glBlendFuncSeparateEXT;										/*! BlendFuncSeparateINGR OGL function	*/
	PFNGLBLENDFUNCSEPARATEINGRPROC										glBlendFuncSeparateINGR;
																																	/*! VertexWeightfEXT OGL function	*/
	PFNGLVERTEXWEIGHTFEXTPROC											glVertexWeightfEXT;											/*! VertexWeightfvEXT OGL function	*/
	PFNGLVERTEXWEIGHTFVEXTPROC											glVertexWeightfvEXT;										/*! VertexWeightPointerEXT OGL function	*/
	PFNGLVERTEXWEIGHTPOINTEREXTPROC										glVertexWeightPointerEXT;
																																	/*! FlushVertexArrayRangeNV OGL function	*/
	PFNGLFLUSHVERTEXARRAYRANGENVPROC									glFlushVertexArrayRangeNV;									/*! VertexArrayRangeNV OGL function	*/
	PFNGLVERTEXARRAYRANGENVPROC											glVertexArrayRangeNV;
																																	/*! CombinerParameterfvNV OGL function	*/
	PFNGLCOMBINERPARAMETERFVNVPROC										glCombinerParameterfvNV;									/*! CombinerParameterfNV OGL function	*/
	PFNGLCOMBINERPARAMETERFNVPROC										glCombinerParameterfNV;										/*! CombinerParameterivNV OGL function	*/
	PFNGLCOMBINERPARAMETERIVNVPROC										glCombinerParameterivNV;									/*! CombinerParameteriNV OGL function	*/
	PFNGLCOMBINERPARAMETERINVPROC										glCombinerParameteriNV;										/*! CombinerInputNV OGL function	*/
	PFNGLCOMBINERINPUTNVPROC											glCombinerInputNV;											/*! CombinerOutputNV OGL function	*/
	PFNGLCOMBINEROUTPUTNVPROC											glCombinerOutputNV;											/*! FinalCombinerInputNV OGL function	*/
	PFNGLFINALCOMBINERINPUTNVPROC										glFinalCombinerInputNV;										/*! GetCombinerInputParameterfvNV OGL function	*/
	PFNGLGETCOMBINERINPUTPARAMETERFVNVPROC								glGetCombinerInputParameterfvNV;							/*! GetCombinerInputParameterivNV OGL function	*/
	PFNGLGETCOMBINERINPUTPARAMETERIVNVPROC								glGetCombinerInputParameterivNV;							/*! GetCombinerOutputParameterfvNV OGL function	*/
	PFNGLGETCOMBINEROUTPUTPARAMETERFVNVPROC								glGetCombinerOutputParameterfvNV;							/*! GetCombinerOutputParameterivNV OGL function	*/
	PFNGLGETCOMBINEROUTPUTPARAMETERIVNVPROC								glGetCombinerOutputParameterivNV;							/*! GetFinalCombinerInputParameterfvNV OGL function	*/
	PFNGLGETFINALCOMBINERINPUTPARAMETERFVNVPROC							glGetFinalCombinerInputParameterfvNV;						/*! GetFinalCombinerInputParameterivNV OGL function	*/
	PFNGLGETFINALCOMBINERINPUTPARAMETERIVNVPROC							glGetFinalCombinerInputParameterivNV;
																																	/*! ResizeBuffersMESA OGL function	*/
	PFNGLRESIZEBUFFERSMESAPROC											glResizeBuffersMESA;
																																	/*! WindowPos2dMESA OGL function	*/
	PFNGLWINDOWPOS2DMESAPROC											glWindowPos2dMESA;											/*! WindowPos2dvMESA OGL function	*/
	PFNGLWINDOWPOS2DVMESAPROC											glWindowPos2dvMESA;											/*! WindowPos2fMESA OGL function	*/
	PFNGLWINDOWPOS2FMESAPROC											glWindowPos2fMESA;											/*! WindowPos2fvMESA OGL function	*/
	PFNGLWINDOWPOS2FVMESAPROC											glWindowPos2fvMESA;											/*! WindowPos2iMESA OGL function	*/
	PFNGLWINDOWPOS2IMESAPROC											glWindowPos2iMESA;											/*! WindowPos2ivMESA OGL function	*/
	PFNGLWINDOWPOS2IVMESAPROC											glWindowPos2ivMESA;											/*! WindowPos2sMESA OGL function	*/
	PFNGLWINDOWPOS2SMESAPROC											glWindowPos2sMESA;											/*! WindowPos2svMESA OGL function	*/
	PFNGLWINDOWPOS2SVMESAPROC											glWindowPos2svMESA;											/*! WindowPos3dMESA OGL function	*/
	PFNGLWINDOWPOS3DMESAPROC											glWindowPos3dMESA;											/*! WindowPos3dvMESA OGL function	*/
	PFNGLWINDOWPOS3DVMESAPROC											glWindowPos3dvMESA;											/*! WindowPos3fMESA OGL function	*/
	PFNGLWINDOWPOS3FMESAPROC											glWindowPos3fMESA;											/*! WindowPos3fvMESA OGL function	*/
	PFNGLWINDOWPOS3FVMESAPROC											glWindowPos3fvMESA;											/*! WindowPos3iMESA OGL function	*/
	PFNGLWINDOWPOS3IMESAPROC											glWindowPos3iMESA;											/*! WindowPos3ivMESA OGL function	*/
	PFNGLWINDOWPOS3IVMESAPROC											glWindowPos3ivMESA;											/*! WindowPos3sMESA OGL function	*/
	PFNGLWINDOWPOS3SMESAPROC											glWindowPos3sMESA;											/*! WindowPos3svMESA OGL function	*/
	PFNGLWINDOWPOS3SVMESAPROC											glWindowPos3svMESA;											/*! WindowPos4dMESA OGL function	*/
	PFNGLWINDOWPOS4DMESAPROC											glWindowPos4dMESA;											/*! WindowPos4dvMESA OGL function	*/
	PFNGLWINDOWPOS4DVMESAPROC											glWindowPos4dvMESA;											/*! WindowPos4fMESA OGL function	*/
	PFNGLWINDOWPOS4FMESAPROC											glWindowPos4fMESA;											/*! WindowPos4fvMESA OGL function	*/
	PFNGLWINDOWPOS4FVMESAPROC											glWindowPos4fvMESA;											/*! WindowPos4iMESA OGL function	*/
	PFNGLWINDOWPOS4IMESAPROC											glWindowPos4iMESA;											/*! WindowPos4ivMESA OGL function	*/
	PFNGLWINDOWPOS4IVMESAPROC											glWindowPos4ivMESA;											/*! WindowPos4sMESA OGL function	*/
	PFNGLWINDOWPOS4SMESAPROC											glWindowPos4sMESA;											/*! WindowPos4svMESA OGL function	*/
	PFNGLWINDOWPOS4SVMESAPROC											glWindowPos4svMESA;
																																	/*! MultiModeDrawArraysIBM OGL function	*/
	PFNGLMULTIMODEDRAWARRAYSIBMPROC										glMultiModeDrawArraysIBM;									/*! MultiModeDrawElementsIBM OGL function	*/
	PFNGLMULTIMODEDRAWELEMENTSIBMPROC									glMultiModeDrawElementsIBM;
																																	/*! ColorPointerListIBM OGL function	*/
	PFNGLCOLORPOINTERLISTIBMPROC										glColorPointerListIBM;										/*! SecondaryColorPointerListIBM OGL function	*/
	PFNGLSECONDARYCOLORPOINTERLISTIBMPROC									glSecondaryColorPointerListIBM;							/*! EdgeFlagPointerListIBM OGL function	*/
	PFNGLEDGEFLAGPOINTERLISTIBMPROC										glEdgeFlagPointerListIBM;									/*! FogCoordPointerListIBM OGL function	*/
	PFNGLFOGCOORDPOINTERLISTIBMPROC										glFogCoordPointerListIBM;									/*! IndexPointerListIBM OGL function	*/
	PFNGLINDEXPOINTERLISTIBMPROC										glIndexPointerListIBM;										/*! NormalPointerListIBM OGL function	*/
	PFNGLNORMALPOINTERLISTIBMPROC										glNormalPointerListIBM;										/*! TexCoordPointerListIBM OGL function	*/
	PFNGLTEXCOORDPOINTERLISTIBMPROC										glTexCoordPointerListIBM;									/*! VertexPointerListIBM OGL function	*/
	PFNGLVERTEXPOINTERLISTIBMPROC										glVertexPointerListIBM;
																																	/*! TbufferMask3DFX OGL function	*/
	PFNGLTBUFFERMASK3DFXPROC											glTbufferMask3DFX;
																																	/*! SampleMaskEXT OGL function	*/
	PFNGLSAMPLEMASKEXTPROC												glSampleMaskEXT;											/*! SamplePatternEXT OGL function	*/
	PFNGLSAMPLEPATTERNEXTPROC											glSamplePatternEXT;
																																	/*! TextureColorMaskSGIS OGL function	*/
	PFNGLTEXTURECOLORMASKSGISPROC										glTextureColorMaskSGIS;
																																	/*! IglooInterfaceSGIX OGL function	*/
	PFNGLIGLOOINTERFACESGIXPROC											glIglooInterfaceSGIX;
																																	/*! DeleteFencesNV OGL function	*/
	PFNGLDELETEFENCESNVPROC												glDeleteFencesNV;											/*! GenFencesNV OGL function	*/
	PFNGLGENFENCESNVPROC												glGenFencesNV;												/*! IsFenceNV OGL function	*/
	PFNGLISFENCENVPROC													glIsFenceNV;												/*! TestFenceNV OGL function	*/
	PFNGLTESTFENCENVPROC												glTestFenceNV;												/*! GetFenceivNV OGL function	*/
	PFNGLGETFENCEIVNVPROC												glGetFenceivNV;												/*! FinishFenceNV OGL function	*/
	PFNGLFINISHFENCENVPROC												glFinishFenceNV;											/*! SetFenceNV OGL function	*/
	PFNGLSETFENCENVPROC													glSetFenceNV;
																																	/*! MapControlPointsNV OGL function	*/
	PFNGLMAPCONTROLPOINTSNVPROC											glMapControlPointsNV;										/*! MapParameterivNV OGL function	*/
	PFNGLMAPPARAMETERIVNVPROC											glMapParameterivNV;											/*! MapParameterfvNV OGL function	*/
	PFNGLMAPPARAMETERFVNVPROC											glMapParameterfvNV;											/*! GetMapControlPointsNV OGL function	*/
	PFNGLGETMAPCONTROLPOINTSNVPROC										glGetMapControlPointsNV;									/*! GetMapParameterivNV OGL function	*/
	PFNGLGETMAPPARAMETERIVNVPROC										glGetMapParameterivNV;										/*! GetMapParameterfvNV OGL function	*/
	PFNGLGETMAPPARAMETERFVNVPROC										glGetMapParameterfvNV;										/*! GetMapAttribParameterivNV OGL function	*/
	PFNGLGETMAPATTRIBPARAMETERIVNVPROC									glGetMapAttribParameterivNV;								/*! GetMapAttribParameterfvNV OGL function	*/
	PFNGLGETMAPATTRIBPARAMETERFVNVPROC									glGetMapAttribParameterfvNV;								/*! EvalMapsNV OGL function	*/
	PFNGLEVALMAPSNVPROC													glEvalMapsNV;
																																	/*! CombinerStageParameterfvNV OGL function	*/
	PFNGLCOMBINERSTAGEPARAMETERFVNVPROC									glCombinerStageParameterfvNV;								/*! GetCombinerStageParameterfvNV OGL function	*/
	PFNGLGETCOMBINERSTAGEPARAMETERFVNVPROC								glGetCombinerStageParameterfvNV;
																																	/*! AreProgramsResidentNV OGL function	*/
	PFNGLAREPROGRAMSRESIDENTNVPROC										glAreProgramsResidentNV;									/*! BindProgramNV OGL function	*/
	PFNGLBINDPROGRAMNVPROC												glBindProgramNV;											/*! DeleteProgramsNV OGL function	*/
	PFNGLDELETEPROGRAMSNVPROC											glDeleteProgramsNV;											/*! ExecuteProgramNV OGL function	*/
	PFNGLEXECUTEPROGRAMNVPROC											glExecuteProgramNV;											/*! GenProgramsNV OGL function	*/
	PFNGLGENPROGRAMSNVPROC												glGenProgramsNV;											/*! GetProgramParameterdvNV OGL function	*/
	PFNGLGETPROGRAMPARAMETERDVNVPROC									glGetProgramParameterdvNV;									/*! GetProgramParameterfvNV OGL function	*/
	PFNGLGETPROGRAMPARAMETERFVNVPROC									glGetProgramParameterfvNV;									/*! GetProgramivNV OGL function	*/
	PFNGLGETPROGRAMIVNVPROC												glGetProgramivNV;											/*! GetProgramStringNV OGL function	*/
	PFNGLGETPROGRAMSTRINGNVPROC											glGetProgramStringNV;										/*! GetTrackMatrixivNV OGL function	*/
	PFNGLGETTRACKMATRIXIVNVPROC											glGetTrackMatrixivNV;										/*! GetVertexAttribdvNV OGL function	*/
	PFNGLGETVERTEXATTRIBDVNVPROC										glGetVertexAttribdvNV;										/*! GetVertexAttribfvNV OGL function	*/
	PFNGLGETVERTEXATTRIBFVNVPROC										glGetVertexAttribfvNV;										/*! GetVertexAttribivNV OGL function	*/
	PFNGLGETVERTEXATTRIBIVNVPROC										glGetVertexAttribivNV;										/*! GetVertexAttribPointervNV OGL function	*/
	PFNGLGETVERTEXATTRIBPOINTERVNVPROC									glGetVertexAttribPointervNV;								/*! IsProgramNV OGL function	*/
	PFNGLISPROGRAMNVPROC												glIsProgramNV;												/*! LoadProgramNV OGL function	*/
	PFNGLLOADPROGRAMNVPROC												glLoadProgramNV;											/*! ProgramParameter4dNV OGL function	*/
	PFNGLPROGRAMPARAMETER4DNVPROC										glProgramParameter4dNV;										/*! ProgramParameter4dvNV OGL function	*/
	PFNGLPROGRAMPARAMETER4DVNVPROC										glProgramParameter4dvNV;									/*! ProgramParameter4fNV OGL function	*/
	PFNGLPROGRAMPARAMETER4FNVPROC										glProgramParameter4fNV;										/*! ProgramParameter4fvNV OGL function	*/
	PFNGLPROGRAMPARAMETER4FVNVPROC										glProgramParameter4fvNV;									/*! ProgramParameters4dvNV OGL function	*/
	PFNGLPROGRAMPARAMETERS4DVNVPROC										glProgramParameters4dvNV;									/*! ProgramParameters4fvNV OGL function	*/
	PFNGLPROGRAMPARAMETERS4FVNVPROC										glProgramParameters4fvNV;									/*! RequestResidentProgramsNV OGL function	*/
	PFNGLREQUESTRESIDENTPROGRAMSNVPROC									glRequestResidentProgramsNV;								/*! TrackMatrixNV OGL function	*/
	PFNGLTRACKMATRIXNVPROC												glTrackMatrixNV;											/*! VertexAttribPointerNV OGL function	*/
	PFNGLVERTEXATTRIBPOINTERNVPROC										glVertexAttribPointerNV;									/*! VertexAttrib1dNV OGL function	*/
	PFNGLVERTEXATTRIB1DNVPROC											glVertexAttrib1dNV;											/*! VertexAttrib1dvNV OGL function	*/
	PFNGLVERTEXATTRIB1DVNVPROC											glVertexAttrib1dvNV;										/*! VertexAttrib1fNV OGL function	*/
	PFNGLVERTEXATTRIB1FNVPROC											glVertexAttrib1fNV;											/*! VertexAttrib1fvNV OGL function	*/
	PFNGLVERTEXATTRIB1FVNVPROC											glVertexAttrib1fvNV;										/*! VertexAttrib1sNV OGL function	*/
	PFNGLVERTEXATTRIB1SNVPROC											glVertexAttrib1sNV;											/*! VertexAttrib1svNV OGL function	*/
	PFNGLVERTEXATTRIB1SVNVPROC											glVertexAttrib1svNV;										/*! VertexAttrib2dNV OGL function	*/
	PFNGLVERTEXATTRIB2DNVPROC											glVertexAttrib2dNV;											/*! VertexAttrib2dvNV OGL function	*/
	PFNGLVERTEXATTRIB2DVNVPROC											glVertexAttrib2dvNV;										/*! VertexAttrib2fNV OGL function	*/
	PFNGLVERTEXATTRIB2FNVPROC											glVertexAttrib2fNV;											/*! VertexAttrib2fvNV OGL function	*/
	PFNGLVERTEXATTRIB2FVNVPROC											glVertexAttrib2fvNV;										/*! VertexAttrib2sNV OGL function	*/
	PFNGLVERTEXATTRIB2SNVPROC											glVertexAttrib2sNV;											/*! VertexAttrib2svNV OGL function	*/
	PFNGLVERTEXATTRIB2SVNVPROC											glVertexAttrib2svNV;										/*! VertexAttrib3dNV OGL function	*/
	PFNGLVERTEXATTRIB3DNVPROC											glVertexAttrib3dNV;											/*! VertexAttrib3dvNV OGL function	*/
	PFNGLVERTEXATTRIB3DVNVPROC											glVertexAttrib3dvNV;										/*! VertexAttrib3fNV OGL function	*/
	PFNGLVERTEXATTRIB3FNVPROC											glVertexAttrib3fNV;											/*! VertexAttrib3fvNV OGL function	*/
	PFNGLVERTEXATTRIB3FVNVPROC											glVertexAttrib3fvNV;										/*! VertexAttrib3sNV OGL function	*/
	PFNGLVERTEXATTRIB3SNVPROC											glVertexAttrib3sNV;											/*! VertexAttrib3svNV OGL function	*/
	PFNGLVERTEXATTRIB3SVNVPROC											glVertexAttrib3svNV;										/*! VertexAttrib4dNV OGL function	*/
	PFNGLVERTEXATTRIB4DNVPROC											glVertexAttrib4dNV;											/*! VertexAttrib4dvNV OGL function	*/
	PFNGLVERTEXATTRIB4DVNVPROC											glVertexAttrib4dvNV;										/*! VertexAttrib4fNV OGL function	*/
	PFNGLVERTEXATTRIB4FNVPROC											glVertexAttrib4fNV;											/*! VertexAttrib4fvNV OGL function	*/
	PFNGLVERTEXATTRIB4FVNVPROC											glVertexAttrib4fvNV;										/*! VertexAttrib4sNV OGL function	*/
	PFNGLVERTEXATTRIB4SNVPROC											glVertexAttrib4sNV;											/*! VertexAttrib4svNV OGL function	*/
	PFNGLVERTEXATTRIB4SVNVPROC											glVertexAttrib4svNV;										/*! VertexAttrib4ubNV OGL function	*/
	PFNGLVERTEXATTRIB4UBNVPROC											glVertexAttrib4ubNV;										/*! VertexAttrib4ubvNV OGL function	*/
	PFNGLVERTEXATTRIB4UBVNVPROC											glVertexAttrib4ubvNV;										/*! VertexAttribs1dvNV OGL function	*/
	PFNGLVERTEXATTRIBS1DVNVPROC											glVertexAttribs1dvNV;										/*! VertexAttribs1fvNV OGL function	*/
	PFNGLVERTEXATTRIBS1FVNVPROC											glVertexAttribs1fvNV;										/*! VertexAttribs1svNV OGL function	*/
	PFNGLVERTEXATTRIBS1SVNVPROC											glVertexAttribs1svNV;										/*! VertexAttribs2dvNV OGL function	*/
	PFNGLVERTEXATTRIBS2DVNVPROC											glVertexAttribs2dvNV;										/*! VertexAttribs2fvNV OGL function	*/
	PFNGLVERTEXATTRIBS2FVNVPROC											glVertexAttribs2fvNV;										/*! VertexAttribs2svNV OGL function	*/
	PFNGLVERTEXATTRIBS2SVNVPROC											glVertexAttribs2svNV;										/*! VertexAttribs3dvNV OGL function	*/
	PFNGLVERTEXATTRIBS3DVNVPROC											glVertexAttribs3dvNV;										/*! VertexAttribs3fvNV OGL function	*/
	PFNGLVERTEXATTRIBS3FVNVPROC											glVertexAttribs3fvNV;										/*! VertexAttribs3svNV OGL function	*/
	PFNGLVERTEXATTRIBS3SVNVPROC											glVertexAttribs3svNV;										/*! VertexAttribs4dvNV OGL function	*/
	PFNGLVERTEXATTRIBS4DVNVPROC											glVertexAttribs4dvNV;										/*! VertexAttribs4fvNV OGL function	*/
	PFNGLVERTEXATTRIBS4FVNVPROC											glVertexAttribs4fvNV;										/*! VertexAttribs4svNV OGL function	*/
	PFNGLVERTEXATTRIBS4SVNVPROC											glVertexAttribs4svNV;										/*! VertexAttribs4ubvNV OGL function	*/
	PFNGLVERTEXATTRIBS4UBVNVPROC										glVertexAttribs4ubvNV;
																																	/*! TexBumpParameterivATI OGL function	*/
	PFNGLTEXBUMPPARAMETERIVATIPROC										glTexBumpParameterivATI;									/*! TexBumpParameterfvATI OGL function	*/
	PFNGLTEXBUMPPARAMETERFVATIPROC										glTexBumpParameterfvATI;									/*! GetTexBumpParameterivATI OGL function	*/
	PFNGLGETTEXBUMPPARAMETERIVATIPROC									glGetTexBumpParameterivATI;									/*! GetTexBumpParameterfvATI OGL function	*/
	PFNGLGETTEXBUMPPARAMETERFVATIPROC									glGetTexBumpParameterfvATI;
																																	/*! GenFragmentShadersATI OGL function	*/
	PFNGLGENFRAGMENTSHADERSATIPROC										glGenFragmentShadersATI;									/*! BindFragmentShaderATI OGL function	*/
	PFNGLBINDFRAGMENTSHADERATIPROC										glBindFragmentShaderATI;									/*! DeleteFragmentShaderATI OGL function	*/
	PFNGLDELETEFRAGMENTSHADERATIPROC									glDeleteFragmentShaderATI;									/*! BeginFragmentShaderATI OGL function	*/
	PFNGLBEGINFRAGMENTSHADERATIPROC										glBeginFragmentShaderATI;									/*! EndFragmentShaderATI OGL function	*/
	PFNGLENDFRAGMENTSHADERATIPROC										glEndFragmentShaderATI;										/*! PassTexCoordATI OGL function	*/
	PFNGLPASSTEXCOORDATIPROC											glPassTexCoordATI;											/*! SampleMapATI OGL function	*/
	PFNGLSAMPLEMAPATIPROC												glSampleMapATI;												/*! ColorFragmentOp1ATI OGL function	*/
	PFNGLCOLORFRAGMENTOP1ATIPROC										glColorFragmentOp1ATI;										/*! ColorFragmentOp2ATI OGL function	*/
	PFNGLCOLORFRAGMENTOP2ATIPROC										glColorFragmentOp2ATI;										/*! ColorFragmentOp3ATI OGL function	*/
	PFNGLCOLORFRAGMENTOP3ATIPROC										glColorFragmentOp3ATI;										/*! AlphaFragmentOp1ATI OGL function	*/
	PFNGLALPHAFRAGMENTOP1ATIPROC										glAlphaFragmentOp1ATI;										/*! AlphaFragmentOp2ATI OGL function	*/
	PFNGLALPHAFRAGMENTOP2ATIPROC										glAlphaFragmentOp2ATI;										/*! AlphaFragmentOp3ATI OGL function	*/
	PFNGLALPHAFRAGMENTOP3ATIPROC										glAlphaFragmentOp3ATI;										/*! SetFragmentShaderConstantATI OGL function	*/
	PFNGLSETFRAGMENTSHADERCONSTANTATIPROC								glSetFragmentShaderConstantATI;
																																	/*! PNTrianglesiATI OGL function	*/
	PFNGLPNTRIANGLESIATIPROC											glPNTrianglesiATI;											/*! PNTrianglesfATI OGL function	*/
	PFNGLPNTRIANGLESFATIPROC											glPNTrianglesfATI;
																																	/*! NewObjectBufferATI OGL function	*/
	PFNGLNEWOBJECTBUFFERATIPROC											glNewObjectBufferATI;										/*! IsObjectBufferATI OGL function	*/
	PFNGLISOBJECTBUFFERATIPROC											glIsObjectBufferATI;										/*! UpdateObjectBufferATI OGL function	*/
	PFNGLUPDATEOBJECTBUFFERATIPROC										glUpdateObjectBufferATI;									/*! GetObjectBufferfvATI OGL function	*/
	PFNGLGETOBJECTBUFFERFVATIPROC										glGetObjectBufferfvATI;										/*! GetObjectBufferivATI OGL function	*/
	PFNGLGETOBJECTBUFFERIVATIPROC										glGetObjectBufferivATI;										/*! FreeObjectBufferATI OGL function	*/
	PFNGLFREEOBJECTBUFFERATIPROC										glFreeObjectBufferATI;										/*! ArrayObjectATI OGL function	*/
	PFNGLARRAYOBJECTATIPROC												glArrayObjectATI;											/*! GetArrayObjectfvATI OGL function	*/
	PFNGLGETARRAYOBJECTFVATIPROC										glGetArrayObjectfvATI;										/*! GetArrayObjectivATI OGL function	*/
	PFNGLGETARRAYOBJECTIVATIPROC										glGetArrayObjectivATI;										/*! VariantArrayObjectATI OGL function	*/
	PFNGLVARIANTARRAYOBJECTATIPROC										glVariantArrayObjectATI;									/*! GetVariantArrayObjectfvATI OGL function	*/
	PFNGLGETVARIANTARRAYOBJECTFVATIPROC									glGetVariantArrayObjectfvATI;								/*! GetVariantArrayObjectivATI OGL function	*/
	PFNGLGETVARIANTARRAYOBJECTIVATIPROC									glGetVariantArrayObjectivATI;
																																	/*! BeginVertexShaderEXT OGL function	*/
	PFNGLBEGINVERTEXSHADEREXTPROC										glBeginVertexShaderEXT;										/*! EndVertexShaderEXT OGL function	*/
	PFNGLENDVERTEXSHADEREXTPROC											glEndVertexShaderEXT;										/*! BindVertexShaderEXT OGL function	*/
	PFNGLBINDVERTEXSHADEREXTPROC										glBindVertexShaderEXT;										/*! GenVertexShadersEXT OGL function	*/
	PFNGLGENVERTEXSHADERSEXTPROC										glGenVertexShadersEXT;										/*! DeleteVertexShaderEXT OGL function	*/
	PFNGLDELETEVERTEXSHADEREXTPROC										glDeleteVertexShaderEXT;									/*! ShaderOp1EXT OGL function	*/
	PFNGLSHADEROP1EXTPROC												glShaderOp1EXT;												/*! ShaderOp2EXT OGL function	*/
	PFNGLSHADEROP2EXTPROC												glShaderOp2EXT;												/*! ShaderOp3EXT OGL function	*/
	PFNGLSHADEROP3EXTPROC												glShaderOp3EXT;												/*! SwizzleEXT OGL function	*/
	PFNGLSWIZZLEEXTPROC													glSwizzleEXT;												/*! WriteMaskEXT OGL function	*/
	PFNGLWRITEMASKEXTPROC												glWriteMaskEXT;												/*! InsertComponentEXT OGL function	*/
	PFNGLINSERTCOMPONENTEXTPROC											glInsertComponentEXT;										/*! ExtractComponentEXT OGL function	*/
	PFNGLEXTRACTCOMPONENTEXTPROC										glExtractComponentEXT;										/*! GenSymbolsEXT OGL function	*/
	PFNGLGENSYMBOLSEXTPROC												glGenSymbolsEXT;											/*! SetInvariantEXT OGL function	*/
	PFNGLSETINVARIANTEXTPROC											glSetInvariantEXT;											/*! SetLocalConstantEXT OGL function	*/
	PFNGLSETLOCALCONSTANTEXTPROC										glSetLocalConstantEXT;										/*! VariantbvEXT OGL function	*/
	PFNGLVARIANTBVEXTPROC												glVariantbvEXT;												/*! VariantsvEXT OGL function	*/
	PFNGLVARIANTSVEXTPROC												glVariantsvEXT;												/*! VariantivEXT OGL function	*/
	PFNGLVARIANTIVEXTPROC												glVariantivEXT;												/*! VariantfvEXT OGL function	*/
	PFNGLVARIANTFVEXTPROC												glVariantfvEXT;												/*! VariantdvEXT OGL function	*/
	PFNGLVARIANTDVEXTPROC												glVariantdvEXT;												/*! VariantubvEXT OGL function	*/
	PFNGLVARIANTUBVEXTPROC												glVariantubvEXT;											/*! VariantusvEXT OGL function	*/
	PFNGLVARIANTUSVEXTPROC												glVariantusvEXT;											/*! VariantuivEXT OGL function	*/
	PFNGLVARIANTUIVEXTPROC												glVariantuivEXT;											/*! VariantPointerEXT OGL function	*/
	PFNGLVARIANTPOINTEREXTPROC											glVariantPointerEXT;										/*! EnableVariantClientStateEXT OGL function	*/
	PFNGLENABLEVARIANTCLIENTSTATEEXTPROC								glEnableVariantClientStateEXT;								/*! DisableVariantClientStateEXT OGL function	*/
	PFNGLDISABLEVARIANTCLIENTSTATEEXTPROC								glDisableVariantClientStateEXT;								/*! BindLightParameterEXT OGL function	*/
	PFNGLBINDLIGHTPARAMETEREXTPROC										glBindLightParameterEXT;									/*! BindMaterialParameterEXT OGL function	*/
	PFNGLBINDMATERIALPARAMETEREXTPROC									glBindMaterialParameterEXT;									/*! BindTexGenParameterEXT OGL function	*/
	PFNGLBINDTEXGENPARAMETEREXTPROC										glBindTexGenParameterEXT;									/*! BindTextureUnitParameterEXT OGL function	*/
	PFNGLBINDTEXTUREUNITPARAMETEREXTPROC								glBindTextureUnitParameterEXT;								/*! BindParameterEXT OGL function	*/
	PFNGLBINDPARAMETEREXTPROC											glBindParameterEXT;											/*! IsVariantEnabledEXT OGL function	*/
	PFNGLISVARIANTENABLEDEXTPROC										glIsVariantEnabledEXT;										/*! GetVariantBooleanvEXT OGL function	*/
	PFNGLGETVARIANTBOOLEANVEXTPROC										glGetVariantBooleanvEXT;									/*! GetVariantIntegervEXT OGL function	*/
	PFNGLGETVARIANTINTEGERVEXTPROC										glGetVariantIntegervEXT;									/*! GetVariantFloatvEXT OGL function	*/
	PFNGLGETVARIANTFLOATVEXTPROC										glGetVariantFloatvEXT;										/*! GetVariantPointervEXT OGL function	*/
	PFNGLGETVARIANTPOINTERVEXTPROC										glGetVariantPointervEXT;									/*! GetInvariantBooleanvEXT OGL function	*/
	PFNGLGETINVARIANTBOOLEANVEXTPROC									glGetInvariantBooleanvEXT;									/*! GetInvariantIntegervEXT OGL function	*/
	PFNGLGETINVARIANTINTEGERVEXTPROC									glGetInvariantIntegervEXT;									/*! GetInvariantFloatvEXT OGL function	*/
	PFNGLGETINVARIANTFLOATVEXTPROC										glGetInvariantFloatvEXT;									/*! GetLocalConstantBooleanvEXT OGL function	*/
	PFNGLGETLOCALCONSTANTBOOLEANVEXTPROC								glGetLocalConstantBooleanvEXT;								/*! GetLocalConstantIntegervEXT OGL function	*/
	PFNGLGETLOCALCONSTANTINTEGERVEXTPROC								glGetLocalConstantIntegervEXT;								/*! GetLocalConstantFloatvEXT OGL function	*/
	PFNGLGETLOCALCONSTANTFLOATVEXTPROC									glGetLocalConstantFloatvEXT;
																																	/*! VertexStream1sATI OGL function	*/
	PFNGLVERTEXSTREAM1SATIPROC											glVertexStream1sATI;										/*! VertexStream1svATI OGL function	*/
	PFNGLVERTEXSTREAM1SVATIPROC											glVertexStream1svATI;										/*! VertexStream1iATI OGL function	*/
	PFNGLVERTEXSTREAM1IATIPROC											glVertexStream1iATI;										/*! VertexStream1ivATI OGL function	*/
	PFNGLVERTEXSTREAM1IVATIPROC											glVertexStream1ivATI;										/*! VertexStream1fATI OGL function	*/
	PFNGLVERTEXSTREAM1FATIPROC											glVertexStream1fATI;										/*! VertexStream1fvATI OGL function	*/
	PFNGLVERTEXSTREAM1FVATIPROC											glVertexStream1fvATI;										/*! VertexStream1dATI OGL function	*/
	PFNGLVERTEXSTREAM1DATIPROC											glVertexStream1dATI;										/*! VertexStream1dvATI OGL function	*/
	PFNGLVERTEXSTREAM1DVATIPROC											glVertexStream1dvATI;										/*! VertexStream2sATI OGL function	*/
	PFNGLVERTEXSTREAM2SATIPROC											glVertexStream2sATI;										/*! VertexStream2svATI OGL function	*/
	PFNGLVERTEXSTREAM2SVATIPROC											glVertexStream2svATI;										/*! VertexStream2iATI OGL function	*/
	PFNGLVERTEXSTREAM2IATIPROC											glVertexStream2iATI;										/*! VertexStream2ivATI OGL function	*/
	PFNGLVERTEXSTREAM2IVATIPROC											glVertexStream2ivATI;										/*! VertexStream2fATI OGL function	*/
	PFNGLVERTEXSTREAM2FATIPROC											glVertexStream2fATI;										/*! VertexStream2fvATI OGL function	*/
	PFNGLVERTEXSTREAM2FVATIPROC											glVertexStream2fvATI;										/*! VertexStream2dATI OGL function	*/
	PFNGLVERTEXSTREAM2DATIPROC											glVertexStream2dATI;										/*! VertexStream2dvATI OGL function	*/
	PFNGLVERTEXSTREAM2DVATIPROC											glVertexStream2dvATI;										/*! VertexStream3sATI OGL function	*/
	PFNGLVERTEXSTREAM3SATIPROC											glVertexStream3sATI;										/*! VertexStream3svATI OGL function	*/
	PFNGLVERTEXSTREAM3SVATIPROC											glVertexStream3svATI;										/*! VertexStream3iATI OGL function	*/
	PFNGLVERTEXSTREAM3IATIPROC											glVertexStream3iATI;										/*! VertexStream3ivATI OGL function	*/
	PFNGLVERTEXSTREAM3IVATIPROC											glVertexStream3ivATI;										/*! VertexStream3fATI OGL function	*/
	PFNGLVERTEXSTREAM3FATIPROC											glVertexStream3fATI;										/*! VertexStream3fvATI OGL function	*/
	PFNGLVERTEXSTREAM3FVATIPROC											glVertexStream3fvATI;										/*! VertexStream3dATI OGL function	*/
	PFNGLVERTEXSTREAM3DATIPROC											glVertexStream3dATI;										/*! VertexStream3dvATI OGL function	*/
	PFNGLVERTEXSTREAM3DVATIPROC											glVertexStream3dvATI;										/*! VertexStream4sATI OGL function	*/
	PFNGLVERTEXSTREAM4SATIPROC											glVertexStream4sATI;										/*! VertexStream4svATI OGL function	*/
	PFNGLVERTEXSTREAM4SVATIPROC											glVertexStream4svATI;										/*! VertexStream4iATI OGL function	*/
	PFNGLVERTEXSTREAM4IATIPROC											glVertexStream4iATI;										/*! VertexStream4ivATI OGL function	*/
	PFNGLVERTEXSTREAM4IVATIPROC											glVertexStream4ivATI;										/*! VertexStream4fATI OGL function	*/
	PFNGLVERTEXSTREAM4FATIPROC											glVertexStream4fATI;										/*! VertexStream4fvATI OGL function	*/
	PFNGLVERTEXSTREAM4FVATIPROC											glVertexStream4fvATI;										/*! VertexStream4dATI OGL function	*/
	PFNGLVERTEXSTREAM4DATIPROC											glVertexStream4dATI;										/*! VertexStream4dvATI OGL function	*/
	PFNGLVERTEXSTREAM4DVATIPROC											glVertexStream4dvATI;										/*! NormalStream3bATI OGL function	*/
	PFNGLNORMALSTREAM3BATIPROC											glNormalStream3bATI;										/*! NormalStream3bvATI OGL function	*/
	PFNGLNORMALSTREAM3BVATIPROC											glNormalStream3bvATI;										/*! NormalStream3sATI OGL function	*/
	PFNGLNORMALSTREAM3SATIPROC											glNormalStream3sATI;										/*! NormalStream3svATI OGL function	*/
	PFNGLNORMALSTREAM3SVATIPROC											glNormalStream3svATI;										/*! NormalStream3iATI OGL function	*/
	PFNGLNORMALSTREAM3IATIPROC											glNormalStream3iATI;										/*! NormalStream3ivATI OGL function	*/
	PFNGLNORMALSTREAM3IVATIPROC											glNormalStream3ivATI;										/*! NormalStream3fATI OGL function	*/
	PFNGLNORMALSTREAM3FATIPROC											glNormalStream3fATI;										/*! NormalStream3fvATI OGL function	*/
	PFNGLNORMALSTREAM3FVATIPROC											glNormalStream3fvATI;										/*! NormalStream3dATI OGL function	*/
	PFNGLNORMALSTREAM3DATIPROC											glNormalStream3dATI;										/*! NormalStream3dvATI OGL function	*/
	PFNGLNORMALSTREAM3DVATIPROC											glNormalStream3dvATI;										/*! ClientActiveVertexStreamATI OGL function	*/
	PFNGLCLIENTACTIVEVERTEXSTREAMATIPROC								glClientActiveVertexStreamATI;								/*! VertexBlendEnviATI OGL function	*/
	PFNGLVERTEXBLENDENVIATIPROC											glVertexBlendEnviATI;										/*! VertexBlendEnvfATI OGL function	*/
	PFNGLVERTEXBLENDENVFATIPROC											glVertexBlendEnvfATI;
																																	/*! ElementPointerATI OGL function	*/
	PFNGLELEMENTPOINTERATIPROC											glElementPointerATI;										/*! DrawElementArrayATI OGL function	*/
	PFNGLDRAWELEMENTARRAYATIPROC										glDrawElementArrayATI;										/*! DrawRangeElementArrayATI OGL function	*/
	PFNGLDRAWRANGEELEMENTARRAYATIPROC									glDrawRangeElementArrayATI;
																																	/*! DrawMeshArraysSUN OGL function	*/
	PFNGLDRAWMESHARRAYSSUNPROC											glDrawMeshArraysSUN;
																																	/*! GenOcclusionQueriesNV OGL function	*/
	PFNGLGENOCCLUSIONQUERIESNVPROC										glGenOcclusionQueriesNV;									/*! DeleteOcclusionQueriesNV OGL function	*/
	PFNGLDELETEOCCLUSIONQUERIESNVPROC									glDeleteOcclusionQueriesNV;									/*! IsOcclusionQueryNV OGL function	*/
	PFNGLISOCCLUSIONQUERYNVPROC											glIsOcclusionQueryNV;										/*! BeginOcclusionQueryNV OGL function	*/
	PFNGLBEGINOCCLUSIONQUERYNVPROC										glBeginOcclusionQueryNV;									/*! EndOcclusionQueryNV OGL function	*/
	PFNGLENDOCCLUSIONQUERYNVPROC										glEndOcclusionQueryNV;										/*! GetOcclusionQueryivNV OGL function	*/
	PFNGLGETOCCLUSIONQUERYIVNVPROC										glGetOcclusionQueryivNV;									/*! GetOcclusionQueryuivNV OGL function	*/
	PFNGLGETOCCLUSIONQUERYUIVNVPROC										glGetOcclusionQueryuivNV;
																																	/*! PointParameteriNV OGL function	*/
	PFNGLPOINTPARAMETERINVPROC											glPointParameteriNV;										/*! PointParameterivNV OGL function	*/
	PFNGLPOINTPARAMETERIVNVPROC											glPointParameterivNV;
																																	/*! ActiveStencilFaceEXT OGL function	*/
	PFNGLACTIVESTENCILFACEEXTPROC										glActiveStencilFaceEXT;
																																	/*! DrawBuffersATI OGL function	*/
	PFNGLDRAWBUFFERSATIPROC												glDrawBuffersATI;
																																	/*! ProgramNamedParameter4fNV OGL function	*/
	PFNGLPROGRAMNAMEDPARAMETER4FNVPROC									glProgramNamedParameter4fNV;								/*! ProgramNamedParameter4dNV OGL function	*/
	PFNGLPROGRAMNAMEDPARAMETER4DNVPROC									glProgramNamedParameter4dNV;								/*! ProgramNamedParameter4fvNV OGL function	*/
	PFNGLPROGRAMNAMEDPARAMETER4FVNVPROC									glProgramNamedParameter4fvNV;								/*! ProgramNamedParameter4dvNV OGL function	*/
	PFNGLPROGRAMNAMEDPARAMETER4DVNVPROC									glProgramNamedParameter4dvNV;								/*! GetProgramNamedParameterfvNV OGL function	*/
	PFNGLGETPROGRAMNAMEDPARAMETERFVNVPROC								glGetProgramNamedParameterfvNV;								/*! GetProgramNamedParameterdvNV OGL function	*/
	PFNGLGETPROGRAMNAMEDPARAMETERDVNVPROC								glGetProgramNamedParameterdvNV;
																																	/*! Vertex2hNV OGL function	*/
	PFNGLVERTEX2HNVPROC													glVertex2hNV;												/*! Vertex2hvNV OGL function	*/
	PFNGLVERTEX2HVNVPROC												glVertex2hvNV;												/*! Vertex3hNV OGL function	*/
	PFNGLVERTEX3HNVPROC													glVertex3hNV;												/*! Vertex3hvNV OGL function	*/
	PFNGLVERTEX3HVNVPROC												glVertex3hvNV;												/*! Vertex4hNV OGL function	*/
	PFNGLVERTEX4HNVPROC													glVertex4hNV;												/*! Vertex4hvNV OGL function	*/
	PFNGLVERTEX4HVNVPROC												glVertex4hvNV;												/*! Normal3hNV OGL function	*/
	PFNGLNORMAL3HNVPROC													glNormal3hNV;												/*! Normal3hvNV OGL function	*/
	PFNGLNORMAL3HVNVPROC												glNormal3hvNV;												/*! Color3hNV OGL function	*/
	PFNGLCOLOR3HNVPROC													glColor3hNV;												/*! Color3hvNV OGL function	*/
	PFNGLCOLOR3HVNVPROC													glColor3hvNV;												/*! Color4hNV OGL function	*/
	PFNGLCOLOR4HNVPROC													glColor4hNV;												/*! Color4hvNV OGL function	*/
	PFNGLCOLOR4HVNVPROC													glColor4hvNV;												/*! TexCoord1hNV OGL function	*/
	PFNGLTEXCOORD1HNVPROC												glTexCoord1hNV;												/*! TexCoord1hvNV OGL function	*/
	PFNGLTEXCOORD1HVNVPROC												glTexCoord1hvNV;											/*! TexCoord2hNV OGL function	*/
	PFNGLTEXCOORD2HNVPROC												glTexCoord2hNV;												/*! TexCoord2hvNV OGL function	*/
	PFNGLTEXCOORD2HVNVPROC												glTexCoord2hvNV;											/*! TexCoord3hNV OGL function	*/
	PFNGLTEXCOORD3HNVPROC												glTexCoord3hNV;												/*! TexCoord3hvNV OGL function	*/
	PFNGLTEXCOORD3HVNVPROC												glTexCoord3hvNV;											/*! TexCoord4hNV OGL function	*/
	PFNGLTEXCOORD4HNVPROC												glTexCoord4hNV;												/*! TexCoord4hvNV OGL function	*/
	PFNGLTEXCOORD4HVNVPROC												glTexCoord4hvNV;											/*! MultiTexCoord1hNV OGL function	*/
	PFNGLMULTITEXCOORD1HNVPROC											glMultiTexCoord1hNV;										/*! MultiTexCoord1hvNV OGL function	*/
	PFNGLMULTITEXCOORD1HVNVPROC											glMultiTexCoord1hvNV;										/*! MultiTexCoord2hNV OGL function	*/
	PFNGLMULTITEXCOORD2HNVPROC											glMultiTexCoord2hNV;										/*! MultiTexCoord2hvNV OGL function	*/
	PFNGLMULTITEXCOORD2HVNVPROC											glMultiTexCoord2hvNV;										/*! MultiTexCoord3hNV OGL function	*/
	PFNGLMULTITEXCOORD3HNVPROC											glMultiTexCoord3hNV;										/*! MultiTexCoord3hvNV OGL function	*/
	PFNGLMULTITEXCOORD3HVNVPROC											glMultiTexCoord3hvNV;										/*! MultiTexCoord4hNV OGL function	*/
	PFNGLMULTITEXCOORD4HNVPROC											glMultiTexCoord4hNV;										/*! MultiTexCoord4hvNV OGL function	*/
	PFNGLMULTITEXCOORD4HVNVPROC											glMultiTexCoord4hvNV;										/*! FogCoordhNV OGL function	*/
	PFNGLFOGCOORDHNVPROC												glFogCoordhNV;												/*! FogCoordhvNV OGL function	*/
	PFNGLFOGCOORDHVNVPROC												glFogCoordhvNV;												/*! SecondaryColor3hNV OGL function	*/
	PFNGLSECONDARYCOLOR3HNVPROC											glSecondaryColor3hNV;										/*! SecondaryColor3hvNV OGL function	*/
	PFNGLSECONDARYCOLOR3HVNVPROC										glSecondaryColor3hvNV;										/*! VertexWeighthNV OGL function	*/
	PFNGLVERTEXWEIGHTHNVPROC											glVertexWeighthNV;											/*! VertexWeighthvNV OGL function	*/
	PFNGLVERTEXWEIGHTHVNVPROC											glVertexWeighthvNV;											/*! VertexAttrib1hNV OGL function	*/
	PFNGLVERTEXATTRIB1HNVPROC											glVertexAttrib1hNV;											/*! VertexAttrib1hvNV OGL function	*/
	PFNGLVERTEXATTRIB1HVNVPROC											glVertexAttrib1hvNV;										/*! VertexAttrib2hNV OGL function	*/
	PFNGLVERTEXATTRIB2HNVPROC											glVertexAttrib2hNV;											/*! VertexAttrib2hvNV OGL function	*/
	PFNGLVERTEXATTRIB2HVNVPROC											glVertexAttrib2hvNV;										/*! VertexAttrib3hNV OGL function	*/
	PFNGLVERTEXATTRIB3HNVPROC											glVertexAttrib3hNV;											/*! VertexAttrib3hvNV OGL function	*/
	PFNGLVERTEXATTRIB3HVNVPROC											glVertexAttrib3hvNV;										/*! VertexAttrib4hNV OGL function	*/
	PFNGLVERTEXATTRIB4HNVPROC											glVertexAttrib4hNV;											/*! VertexAttrib4hvNV OGL function	*/
	PFNGLVERTEXATTRIB4HVNVPROC											glVertexAttrib4hvNV;										/*! VertexAttribs1hvNV OGL function	*/
	PFNGLVERTEXATTRIBS1HVNVPROC											glVertexAttribs1hvNV;										/*! VertexAttribs2hvNV OGL function	*/
	PFNGLVERTEXATTRIBS2HVNVPROC											glVertexAttribs2hvNV;										/*! VertexAttribs3hvNV OGL function	*/
	PFNGLVERTEXATTRIBS3HVNVPROC											glVertexAttribs3hvNV;										/*! VertexAttribs4hvNV OGL function	*/
	PFNGLVERTEXATTRIBS4HVNVPROC											glVertexAttribs4hvNV;
																																	/*! PixelDataRangeNV OGL function	*/
	PFNGLPIXELDATARANGENVPROC											glPixelDataRangeNV;											/*! FlushPixelDataRangeNV OGL function	*/
	PFNGLFLUSHPIXELDATARANGENVPROC										glFlushPixelDataRangeNV;
																																	/*! PrimitiveRestartNV OGL function	*/
	PFNGLPRIMITIVERESTARTNVPROC											glPrimitiveRestartNV;										/*! PrimitiveRestartIndexNV OGL function	*/
	PFNGLPRIMITIVERESTARTINDEXNVPROC									glPrimitiveRestartIndexNV;
																																	/*! MapObjectBufferATI OGL function	*/
	PFNGLMAPOBJECTBUFFERATIPROC											glMapObjectBufferATI;										/*! UnmapObjectBufferATI OGL function	*/
	PFNGLUNMAPOBJECTBUFFERATIPROC										glUnmapObjectBufferATI;
																																	/*! StencilOpSeparateATI OGL function	*/
	PFNGLSTENCILOPSEPARATEATIPROC										glStencilOpSeparateATI;										/*! StencilFuncSeparateATI OGL function	*/
	PFNGLSTENCILFUNCSEPARATEATIPROC										glStencilFuncSeparateATI;
																																	/*! VertexAttribArrayObjectATI OGL function	*/
	PFNGLVERTEXATTRIBARRAYOBJECTATIPROC									glVertexAttribArrayObjectATI;								/*! GetVertexAttribArrayObjectfvATI OGL function	*/
	PFNGLGETVERTEXATTRIBARRAYOBJECTFVATIPROC							glGetVertexAttribArrayObjectfvATI;							/*! GetVertexAttribArrayObjectivATI OGL function	*/
	PFNGLGETVERTEXATTRIBARRAYOBJECTIVATIPROC							glGetVertexAttribArrayObjectivATI;

	// FBO																															/*! BindFramebufferEXT OGL function	*/
	PFNGLBINDFRAMEBUFFEREXTPROC											glBindFramebufferEXT;										/*! DeleteFramebuffersEXT OGL function	*/
	PFNGLDELETEFRAMEBUFFERSEXTPROC										glDeleteFramebuffersEXT;									/*! DeleteRenderbuffersEXT OGL function	*/
	PFNGLDELETERENDERBUFFERSEXTPROC										glDeleteRenderbuffersEXT;									/*! GenFramebuffersEXT OGL function	*/
	PFNGLGENFRAMEBUFFERSEXTPROC											glGenFramebuffersEXT;										/*! GenRenderbuffersEXT OGL function	*/
	PFNGLGENRENDERBUFFERSEXTPROC										glGenRenderbuffersEXT;

	// VBO / PBO																													/*! GetBufferPointervARB OGL function	*/
	PFNGLGETBUFFERPOINTERVARBPROC										glGetBufferPointervARB;										/*! BindBufferARB OGL function	*/
	PFNGLBINDBUFFERARBPROC												glBindBufferARB;											/*! BufferDataARB OGL function	*/
	PFNGLBUFFERDATAARBPROC												glBufferDataARB;											/*! DeleteBuffersARB OGL function	*/
	PFNGLDELETEBUFFERSARBPROC											glDeleteBuffersARB;											/*! GenBuffersARB OGL function	*/
	PFNGLGENBUFFERSARBPROC												glGenBuffersARB;											/*! IsBufferARB OGL function	*/
	PFNGLISBUFFERARBPROC												glIsBufferARB;												/*! MapBufferARB OGL function	*/
	PFNGLMAPBUFFERARBPROC												glMapBufferARB;												/*! UnmapBufferARB OGL function	*/
	PFNGLUNMAPBUFFERARBPROC												glUnmapBufferARB;											/*! GetBufferParameterivARB OGL function	*/
	PFNGLGETBUFFERPARAMETERIVARBPROC									glGetBufferParameterivARB;

	// GLSL																															/*! AttachObjectARB OGL function	*/
	PFNGLATTACHOBJECTARBPROC											glAttachObjectARB;											/*! CompileShaderARB OGL function	*/
	PFNGLCOMPILESHADERARBPROC											glCompileShaderARB;											/*! CreateProgramObjectARB OGL function	*/
	PFNGLCREATEPROGRAMOBJECTARBPROC										glCreateProgramObjectARB;									/*! CreateShaderObjectARB OGL function	*/
	PFNGLCREATESHADEROBJECTARBPROC										glCreateShaderObjectARB;									/*! DeleteObjectARB OGL function	*/
	PFNGLDELETEOBJECTARBPROC											glDeleteObjectARB;											/*! DetachObjectARB OGL function	*/
	PFNGLDETACHOBJECTARBPROC											glDetachObjectARB;											/*! GetActiveUniformARB OGL function	*/
	PFNGLGETACTIVEUNIFORMARBPROC										glGetActiveUniformARB;										/*! GetAttachedObjectsARB OGL function	*/
	PFNGLGETATTACHEDOBJECTSARBPROC										glGetAttachedObjectsARB;									/*! GetHandleARB OGL function	*/
	PFNGLGETHANDLEARBPROC												glGetHandleARB;												/*! GetInfoLogARB OGL function	*/
	PFNGLGETINFOLOGARBPROC												glGetInfoLogARB;											/*! GetObjectParameterfvARB OGL function	*/
	PFNGLGETOBJECTPARAMETERFVARBPROC									glGetObjectParameterfvARB;									/*! GetObjectParameterivARB OGL function	*/
	PFNGLGETOBJECTPARAMETERIVARBPROC									glGetObjectParameterivARB;									/*! GetShaderSourceARB OGL function	*/
	PFNGLGETSHADERSOURCEARBPROC											glGetShaderSourceARB;										/*! GetUniformLocationARB OGL function	*/
	PFNGLGETUNIFORMLOCATIONARBPROC										glGetUniformLocationARB;									/*! GetUniformfvARB OGL function	*/
	PFNGLGETUNIFORMFVARBPROC											glGetUniformfvARB;											/*! GetUniformivARB OGL function	*/
	PFNGLGETUNIFORMIVARBPROC											glGetUniformivARB;											/*! LinkProgramARB OGL function	*/
	PFNGLLINKPROGRAMARBPROC												glLinkProgramARB;											/*! ShaderSourceARB OGL function	*/
	PFNGLSHADERSOURCEARBPROC											glShaderSourceARB;											/*! Uniform1fARB OGL function	*/
	PFNGLUNIFORM1FARBPROC												glUniform1fARB;												/*! Uniform1fvARB OGL function	*/
	PFNGLUNIFORM1FVARBPROC												glUniform1fvARB;											/*! Uniform1iARB OGL function	*/
	PFNGLUNIFORM1IARBPROC												glUniform1iARB;												/*! Uniform1ivARB OGL function	*/
	PFNGLUNIFORM1IVARBPROC												glUniform1ivARB;											/*! Uniform2fARB OGL function	*/
	PFNGLUNIFORM2FARBPROC												glUniform2fARB;												/*! Uniform2fvARB OGL function	*/
	PFNGLUNIFORM2FVARBPROC												glUniform2fvARB;											/*! Uniform2iARB OGL function	*/
	PFNGLUNIFORM2IARBPROC												glUniform2iARB;												/*! Uniform2ivARB OGL function	*/
	PFNGLUNIFORM2IVARBPROC												glUniform2ivARB;											/*! Uniform3fARB OGL function	*/
	PFNGLUNIFORM3FARBPROC												glUniform3fARB;												/*! Uniform3fvARB OGL function	*/
	PFNGLUNIFORM3FVARBPROC												glUniform3fvARB;											/*! Uniform3iARB OGL function	*/
	PFNGLUNIFORM3IARBPROC												glUniform3iARB;												/*! Uniform3ivARB OGL function	*/
	PFNGLUNIFORM3IVARBPROC												glUniform3ivARB;											/*! Uniform4fARB OGL function	*/
	PFNGLUNIFORM4FARBPROC												glUniform4fARB;												/*! Uniform4fvARB OGL function	*/
	PFNGLUNIFORM4FVARBPROC												glUniform4fvARB;											/*! Uniform4iARB OGL function	*/
	PFNGLUNIFORM4IARBPROC												glUniform4iARB;												/*! Uniform4ivARB OGL function	*/
	PFNGLUNIFORM4IVARBPROC												glUniform4ivARB;											/*! UniformMatrix2fvARB OGL function	*/
	PFNGLUNIFORMMATRIX2FVARBPROC										glUniformMatrix2fvARB;										/*! UniformMatrix3fvARB OGL function	*/
	PFNGLUNIFORMMATRIX3FVARBPROC										glUniformMatrix3fvARB;										/*! UniformMatrix4fvARB OGL function	*/
	PFNGLUNIFORMMATRIX4FVARBPROC										glUniformMatrix4fvARB;										/*! UseProgramObjectARB OGL function	*/
	PFNGLUSEPROGRAMOBJECTARBPROC										glUseProgramObjectARB;										/*! ValidateProgramARB OGL function	*/
	PFNGLVALIDATEPROGRAMARBPROC											glValidateProgramARB;										/*! IsProgramARB OGL function	*/
	PFNGLISPROGRAMARBPROC												glIsProgramARB;
																																	/*! GenQueriesARB OGL function	*/
	PFNGLGENQUERIESARBPROC												glGenQueriesARB;											/*! DeleteQueriesARB OGL function	*/
	PFNGLDELETEQUERIESARBPROC											glDeleteQueriesARB;											/*! IsQueryARB OGL function	*/
	PFNGLISQUERYARBPROC													glIsQueryARB;												/*! BeginQueryARB OGL function	*/
	PFNGLBEGINQUERYARBPROC												glBeginQueryARB;											/*! EndQueryARB OGL function	*/
	PFNGLENDQUERYARBPROC												glEndQueryARB;												/*! GetQueryivARB OGL function	*/
	PFNGLGETQUERYIVARBPROC												glGetQueryivARB;											/*! GetQueryObjectivARB OGL function	*/
	PFNGLGETQUERYOBJECTIVARBPROC										glGetQueryObjectivARB;										/*! GetQueryObjectuivARB OGL function	*/
	PFNGLGETQUERYOBJECTUIVARBPROC										glGetQueryObjectuivARB;


} XGSGLExtensionsFuncs;

//***************************************************************************************
// Forward decls
//***************************************************************************************
class IRTSExecutionState ;

//***************************************************************************************
// Structures
//***************************************************************************************

/*! \struct tagXSI_RTS_Light
	\brief The XSI_RTS_Light structure.

	Holds information about a single light source. Used by the legacy tagXSI_RTS_SceneData structure
	which is accessed via the tagXSI_RTS_SystemParams::m_SceneData member.
	\sa tagXSI_RTS_SystemParams::m_pLights, \xc Light
*/
typedef struct tagXSI_RTS_Light
{														/*! Light red value				*/
	float					m_fRed;						/*! Light green value			*/
	float					m_fGreen;					/*! Light blue value			*/
	float					m_fBlue;					/*! Light alpha value			*/
	float					m_fAlpha;
														/*! Light X position			*/
	float					m_fPosX;					/*! Light Y position			*/
	float					m_fPosY;					/*! Light Z position			*/
	float					m_fPosZ;					/*! Light W position			*/
	float					m_fPosW;
														/*! Light X direction			*/
	float					m_fDirX;					/*! Light Y direction			*/
	float					m_fDirY;					/*! Light Z direction			*/
	float					m_fDirZ;
														/*! Spot light cone angle		*/
	float					m_fConeAngle;
														/*! OpenGL light ID				*/
	int						m_iID;						/*! Light handle				*/
	char*					m_pchID;
														/*! Light type					*/
	eXSI_RTS_LightType		m_eType;
														/*! Light casts shadows			*/
	bool					m_bCastsShadows;
														/*! Light object is visible		*/
	bool					m_bVisible;

} XSI_RTS_Light;

/*! \struct tagXSI_RTS_Camera
	\brief The XSI_RTS_Camera structure.

	Holds information about a camera. Used by the legacy tagXSI_RTS_SceneData structure
	which is accessed via the tagXSI_RTS_SystemParams::m_SceneData member.
	\sa tagXSI_RTS_SystemParams::m_sCamera, IRTSExecutionState::GetCamera, \xc Camera
*/
typedef struct tagXSI_RTS_Camera
{															/*! The camera matrix							*/
	float					m_mMatrix[16];					/*! The type of camera (ortho, perspective)		*/
	eXSI_RTS_CameraType		m_eCameraType;
															/*! Frustum right								*/
	float					m_fRight;						/*! Frustum left								*/
	float					m_fLeft;						/*! Frustum top									*/
	float					m_fTop;							/*! Frustum bottom								*/
	float					m_fBottom;
															/*! Near plane									*/
	float					m_fNear;						/*! Far plane									*/
	float					m_fFar;
															/*! Field of view								*/
	float					m_fFOV;
															/*! Aspect ratio								*/
	float					m_fAspect;
} XSI_RTS_Camera;


/*! \struct tagXSI_RTS_SceneData
	\brief The XSI_RTS_SceneData structure.

	Holds scene information about the lights in the scene, the current camera and the current time.
	This is a legacy structure returned by the tagXSI_RTS_SystemParams::m_SceneData member.
	\sa tagXSI_RTS_SystemParams::m_SceneData, tagXSI_RTS_Camera, tagXSI_RTS_Light,
		\xt cus_rtshad_CommunicatingwithXSI Communicating with Softimage \endxt
*/
typedef struct tagXSI_RTS_SceneData
{															/*! Number of lights					*/
	int							m_iNbLights;				/*! Array of XSI_RTS_Light structures	*/
	XSI_RTS_Light*				m_pLights;
															/*! The current camera					*/
	XSI_RTS_Camera				m_sCamera;
															/*! Current time						*/
	double						m_fCurrentTime;
} XSI_RTS_SceneData;

/*! \struct tagXSI_RTS_SystemParams
	\brief The XSI_RTS_SystemParams structure.

	Holds the system parameters to be passed to all shader callbacks. This is a legacy structure
	returned by the IRTSExecutionState::GetSystemParams function.
	\param m_lNbParams Number of parameters
	\param m_lAppID Application ID
	\param m_lRTSVersion Realtime shader protocol version.
	\param m_lContext Uniquely identifies the viewport during a Softimage session. Each viewport (regular
		or object view) has an XGS context associated with it. \c m_lContext is a handle to the context
		object cast to a \c LONG
	\param m_pShaderHandle Shader instance handle (\xc CRef handle to the \xc Shader object). You can use
		the C++ API to access it.
	\param m_pObjectHandle \b Deprecated v7.0. For RTS v3.0 shaders you can get the object directly via IRTSExecutionState::GetPrimitive
	\param m_pMaterialHandle \b Deprecated v7.0. For RTS v3.0 shaders you can get the material directly via IRTSExecutionState::GetMaterial
	\param m_pGS Handle to the graphic system (\xc CRef handle to the \xc GraphicSequencer object). You can
		use the C++ API to access it.
	\param m_pGLExt The OpenGL extension wrapper flags indicate whether a particular OpenGL extension is used.
		Simply test the appropriate field in that structure. For example, if you want to test whether your
		hardware supports the \c GL_ARB_multitexture extension, then simply check if \c m_pGS->_GL_ARB_multitexture
		is set to TRUE.
	\param m_pGLExtFuncs The OpenGL extension wrapper functions can be called directly from that structure.
		For example, if you want to call the \c glClientActiveTextureARB extension function, just use
		\c m_pGLExtFuncs->glClientActiveTextureARB.
	\param m_lShaderFlags Shader flags. See \link Shader_flags Shader Flag Defines \endlink.
	\param m_lObjectFlags Object flags. See \link Object_flags Object Flag Defines \endlink.
	\param m_m4x4ObjectPose The object pose is a 4x4 matrix containing the global transformation of the object.
	\param m_SceneData The scene data is a structure that contains camera and light information. See tagXSI_RTS_SceneData.
	\sa IRTSExecutionState::GetSystemParams, IRTSExecutionState, \link Versioning Define \endlink,
		\xt cus_rtshad_SystemParameters System Parameters \endxt
*/
typedef struct tagXSI_RTS_SystemParams
{															/*! Number of parameters							*/
	ULONG						m_lNbParams;
															/*! Application ID									*/
	ULONG						m_lAppID;					/*! Realtime shader protocol version				*/
	ULONG						m_lRTSVersion;				/*! Context											*/
	RTSContext					m_lContext;
															/*! Shader instance handle (CRef)					*/
	void						*m_pShaderHandle;			/*! Owner object handle (CRef)						*/
	void						*m_pObjectHandle;			/*! Owner material handle (CRef)					*/
	void						*m_pMaterialHandle;
															/*! Handle to the graphic system (CRef)				*/
	void						*m_pGS;						/*! Softimage OpenGL extension wrapper flags		*/
	XGSExtensionsGL				*m_pGLExt;					/*! Softimage OpenGL extension wrapper functions	*/
	XGSGLExtensionsFuncs		*m_pGLExtFuncs;
															/*! Shader flags									*/
	ULONG						m_lShaderFlags;				/*! Object flags									*/
	ULONG						m_lObjectFlags;
															/*! Object's transformation matrix					*/
	float						m_m4x4ObjectPose[16];
															/*! Scene Data										*/
	XSI_RTS_SceneData			*m_SceneData;
} XSI_RTS_SystemParams;

/*! \struct tagXSI_RTS_TriangleList
	\brief The XSI_RTS_TriangleList structure. Provided only for backward compatibility.

	Triangles are packed into lists. Each list can either be a single triangle strip or a list
	of unconnected triangles. The triangle list contains the triangle lists themselves.

	\note The \c m_pReserved fields are added in order for the tagXSI_RTS_TriangleList to
		use the same amount of memory as a \c C3DStrip<TvCoord, TNormal, TColor, TTCCord>
		object.  This enables you to cast an array of one type into an array of another
		type without problems.  For example, this is used in the following:
	\code C3DDrawObject<TVcoord, TNormal, TColor, TTcoord>::RealtimeShaderDraw \endcode
	\deprecated 7.0. Prior to v7.0, this structure was used by the \c tagXSI_RTS_TriangulatedGeometry
		structure which was used to store the geometry. Now you can use the _XSI_RTS_Attribute
		structure to define which type of data on the mesh or point cloud to be used in
		rendering and return it from the \ref GetAttributeList "GetRequirements" callback function.
	\sa \ref GetAttributeList "GetRequirements", _XSI_RTS_Attribute
*/
typedef struct tagXSI_RTS_TriangleList
{												/*! Starting offset of the triangle list									*/
	ULONG			m_lOffset;					/*! Number of vertices for the triangle list								*/
	ULONG			m_lNbVertices;				/*! Type of triangle list (strip, list, fan : Mapped with OGL constants)	*/
	ULONG			m_lType;					/*! Minimum index used for this triangle list								*/
	ULONG			m_lMinIndex;				/*! Maximum index used for this triangle list								*/
	ULONG			m_lMaxIndex;

	// The following fields are added in order for the XSI_RTS_TriangleList to
	// use the same amound of memory as a C3DStrip<TvCoord, TNormal, TColor, TTCCord>
	// object.  This enables to cast a array of one type into a array of the other
	// type without problems.  This is used in C3DDrawObject<TVcoord, TNormal, TColor, TTcoord>::RealtimeShaderDraw
	// for example.
												/*! Reserved 0	*/
	void *			m_pReserved0;				/*! Reserved 1	*/
	void *			m_pReserved1;				/*! Reserved 2	*/
	void *			m_pReserved2;				/*! Reserved 3	*/
	ULONG			m_lReserved3;
} XSI_RTS_TriangleList;

/*! \struct tagXSI_RTS_Primitive
	\brief The XSI_RTS_Primitive structure.

	This structure is available from the IRTSExecutionState::GetPrimitive function. You use it to pass
	information to the IRTSExecutionState::DrawGeometry function about the geometry to draw.
	\sa IRTSExecutionState::GetPrimitive, IRTSExecutionState::DrawGeometry, \xc X3DObject
	\since 7.0
*/
typedef struct tagXSI_RTS_Primitive
{													/*! The type of primitive									*/
	eXSI_RTS_PrimitiveType	m_Type;					/*! The triangle indices									*/
	void*					m_pIndices;				/*! The size of the indices (4=UINT, 2=USHORT, 1=UBYTE)		*/
	int						m_iIndicesWidth;		/*! Number of indices										*/
	ULONG					m_ulNbIndices;			/*! Offset into the list of indices							*/
	ULONG					m_ulBaseOffset;			/*! Total number of vertices								*/
	ULONG					m_NbVertices;
} XSI_RTS_Primitive;

typedef struct tagXSI_RTS_SasCamera
{
    float m_WorldToView[4][4];
    float m_Projection[4][4];
    float m_NearFarClipping[2];
    float m_Position[3];
} XSI_RTS_SasCamera;

typedef struct tagXSI_RTS_SasAmbientLight
{
    float m_Color[3];         // default: {0, 0, 0}
} XSI_RTS_SasAmbientLight;

typedef struct tagXSI_RTS_SasDirectionalLight
{
    float m_Color[3];         // default: {0, 0, 0}
    float m_Direction[3];     // default: {0, 0, 0}
} XSI_RTS_SasDirectionalLight;

typedef struct tagXSI_RTS_SasPointLight
{
    float m_Color[3];         // default: {0, 0, 0}
    float m_Position[3];      // default: {0, 0, 0}
    float m_Range;            // default: 0
} XSI_RTS_SasPointLight;

typedef struct tagXSI_RTS_SasSpotLight
{
    float m_Color[3];         // default: {0, 0, 0}
    float m_Position[3];      // default: {0, 0, 0}
    float m_Direction[3];     // default: {0, 0, 0}
    float m_Range;            // default: 0
    float m_Theta;            // default: 0
    float m_Phi;              // default: 0
} XSI_RTS_SasSpotLight;

#define MAX_SAS_LIGHTS	256

typedef struct tagXSI_RTS_FXSemantics
{
	// the matrices
	float	m_World[4][4];
	float	m_WorldI[4][4];
	float	m_WorldT[4][4];
	float	m_WorldIT[4][4];

	float	m_WorldView[4][4];
	float	m_WorldViewI[4][4];
	float	m_WorldViewT[4][4];
	float	m_WorldViewIT[4][4];

	float	m_WorldViewProj[4][4];
	float	m_WorldViewProjI[4][4];
	float	m_WorldViewProjT[4][4];
	float	m_WorldViewProjIT[4][4];

	float	m_View[4][4];
	float	m_ViewI[4][4];
	float	m_ViewT[4][4];
	float	m_ViewIT[4][4];

	float	m_Proj[4][4];
	float	m_ProjI[4][4];
	float	m_ProjT[4][4];
	float	m_ProjIT[4][4];

	// vectors
	float	m_CameraPos[4];
	float	m_CameraNearFar[4];

	// scalars
	float	m_TimeNow[1];
	float	m_TimeLast[1];
	float	m_TimeFrameNumber[1];
	float	m_NumAmbientLights[1];
	float	m_NumDirectionalLights[1];
	float	m_NumPointLights[1];
	float	m_NumSpotLights[1];

	// structures
	XSI_RTS_SasCamera				m_SasCamera[1];
	XSI_RTS_SasAmbientLight			m_AmbientLights[MAX_SAS_LIGHTS];
	XSI_RTS_SasDirectionalLight		m_DirectionalLights[MAX_SAS_LIGHTS];
	XSI_RTS_SasPointLight			m_PointLights[MAX_SAS_LIGHTS];
	XSI_RTS_SasSpotLight			m_SpotLights[MAX_SAS_LIGHTS];
/*
	int		m_MaxAmbientLights;
	int		m_MaxDirectionalLights;
	int		m_MaxPointLights;
	int		m_MaxSpotLights;
*/
} XSI_RTS_FXSemantics;

typedef struct tagXSI_RTS_FXSemantics_Param
{
	void*	m_pSourceParam;
	void*	m_pDestParam;
} XSI_RTS_FXSemantics_Param;

typedef struct tagXSI_RTS_FXSemantics_inuse
{
	// the matrices
	bool	m_World;
	bool	m_WorldI;
	bool	m_WorldT;
	bool	m_WorldIT;

	bool	m_WorldView;
	bool	m_WorldViewI;
	bool	m_WorldViewT;
	bool	m_WorldViewIT;

	bool	m_WorldViewProj;
	bool	m_WorldViewProjI;
	bool	m_WorldViewProjT;
	bool	m_WorldViewProjIT;

	bool	m_View;
	bool	m_ViewI;
	bool	m_ViewT;
	bool	m_ViewIT;

	bool	m_Proj;
	bool	m_ProjI;
	bool	m_ProjT;
	bool	m_ProjIT;

	// vectors
	bool	m_CameraPos;
	bool	m_CameraNearFar;

	// scalars
	bool	m_TimeNow;
	bool	m_TimeLast;
	bool	m_TimeFrameNumber;
	bool	m_NumAmbientLights;
	bool	m_NumDirectionalLights;
	bool	m_NumPointLights;
	bool	m_NumSpotLights;

	// structures
	bool	m_SasCamera;
	bool	m_AmbientLights;
	bool	m_DirectionalLights;
	bool	m_PointLights;
	bool	m_SpotLights;

	// last time
	float	m_LastTime;

	// table of parameters to bind
	CSIBCArray<XSI_RTS_FXSemantics_Param>	m_Params;

} XSI_RTS_FXSemantics_inuse;

/*! \defgroup eErrorType eErrorType Enum
	Possible types of errors that can be raised using the IRTSExecutionState::RaiseError function.
	\sa IRTSExecutionState::RaiseError, \xc siSeverityType
	\since 7.0
@{
*/
enum eErrorType
{
	Info = 0,	//!< Log an information message.
	Warning,	//!< An error has occurred but is recoverable.
	Error		//!< An error has occurred; possibly leading to data loss.
};
/*!
@}
*/

//***************************************************************************************
// Entry points
//***************************************************************************************

//***************************************************************************************
//	PostFix		: _Init
//	Called		: when the shader is created
//  Mandatory	: No
//
//***************************************************************************************
typedef 	RTSHADER_API bool (*RTS_Shader2_Init)
(
	XSI_RTS_SystemParams			*in_pSysParams,					//! The system parameters
	void							*in_pParams,					//! The property page parameters
	void							**io_pShaderInstanceData		//! The shader instance data
);

//***************************************************************************************
//	PostFix		: _Term
//	Called		: when the shader is deleted
//  Mandatory	: No
//
//***************************************************************************************
typedef 	RTSHADER_API bool (*RTS_Shader2_Term)
(
	XSI_RTS_SystemParams			*in_pSysParams,					//! The system parameters
	void							*in_pParams,					//! The property page parameters
	void							**io_pShaderInstanceData		//! The shader instance data
);

//***************************************************************************************
//	PostFix		: _GetRequirements
//	Called		: At various places
//  Mandatory	: No
//
//***************************************************************************************
typedef 	RTSHADER_API bool (*RTS_Shader2_GetRequirements)
(
	XSI_RTS_SystemParams			*in_pSysParams,					//! The system parameters
	void							*in_pParams,					//! The property page parameters
	XSI_RTS_Primitive				*in_pGeom,						//! The geometry information
	void							**io_pShaderInstanceData,		//! The shader instance data
	ULONG					in_lRequirement,				//! The requirement identifier
	ULONG					*out_pRequirementValue			//! The returned requirement value
);

//***************************************************************************************
//	PostFix		: _Execute
//	Called		: on every refresh for every object that own the shader
//  Mandatory	: Yes
//
//***************************************************************************************
typedef 	RTSHADER_API bool (*RTS_Shader2_Execute)
(
	XSI_RTS_SystemParams			*in_pSysParams,					//! The system parameters
	void							*in_pParams,					//! The property page parameters
	void							*in_pBackcomp,					//! The geometry information
	void							**io_pShaderInstanceData		//! The shader instance data
);

//***************************************************************************************
//	Called		: one per DLL
//  Mandatory	: Yes
//
//***************************************************************************************
/*! \page RTS_GetVersion RTS_GetVersion Callback Reference
	\code
	RTSHADER_API ULONG RTS_GetVersion()
	{
		return XSI_RTSHADER_VERSION;
	}
	\endcode
	Each dynamic library needs to implement the RTS_GetVersion callback function. This tells Softimage
	which version of the Realtime Shader API this shader was compiled with.
	\note This callback is mandatory
	\return Softimage version number
	\sa \ref RTS_Callbacks, \link XSI_RTSHADER_VERSION \endlink
*/
typedef 	RTSHADER_API ULONG (*RTS_Shader2_GetVersion)();

enum XSI_RTS_PPG_TYPES
{
	XSI_RTS_SCALAR,
	XSI_RTS_STRING,
	XSI_RTS_IMAGE,
	XSI_RTS_TSPACE,
	XSI_RTS_CSPACE,
};

typedef struct
{
	char				*m_pName;
	XSI_RTS_PPG_TYPES	m_type;
} ShaderParamDefinition;

typedef struct
{
	char					*m_pProgID;
	char					*m_pModule;
	char					*m_pPrefix;
	int						m_pNbParams;
	ShaderParamDefinition	*m_ShaderParams;
} ShaderDefinition;

typedef		RTSHADER_API int (*RTS2_GetNumberOfShadersFunc)();
typedef		RTSHADER_API ShaderDefinition * (*RTS2_GetShaderDefinitionFunc)(int in_nIndex);


//***************************************************************************************
// Inlined functionality
//***************************************************************************************

#define XSI_RTS_EPS  	1.0e-3

inline void   XSI_RTS_MatrixTranspose(float in_pSrcM4x4[4][4], float in_pDstM4x4[4][4])
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

inline bool   XSI_RTS_MatrixInvert(float in_pSrcM4x4[4][4], float in_pDstM4x4[4][4])
{

	float   sys[ 4 ][ 8 ] =
	{
		1,0,0,0,1,0,0,0,
		0,1,0,0,0,1,0,0,
		0,0,1,0,0,0,1,0,
		0,0,0,1,0,0,0,1
	};

	int		i,  j,  k;
	float   temp;


	memcpy(sys[0], in_pSrcM4x4[0], sizeof(float) * 4);
	memcpy(sys[1], in_pSrcM4x4[1], sizeof(float) * 4);
	memcpy(sys[2], in_pSrcM4x4[2], sizeof(float) * 4);
	memcpy(sys[3], in_pSrcM4x4[3], sizeof(float) * 4);

	for( j = 0; j < 4; j++ )
	{
		if( fabs( sys[ j ][ j ] ) < XSI_RTS_EPS )
		{
			for( i = j + 1; ( i < 4 ) && ( fabs ( sys[ i ][ j ] ) < XSI_RTS_EPS ); i++ );

			if( i == 4 )
				return( false );
			else
				for( k = 0; k < 8; k++ )
				{
					temp = sys[ i ][ k ];
					sys[ i ][ k ] = sys[ j ][ k ];
					sys[ j ][ k ] = temp;
				}
		}

		temp = 1.0f / sys[ j ][ j ];

		for( i = 0; i < 8; i++ )
			sys[ j ][ i ] *= temp;

		for( i = 0; i < 4; i++ )
		{
			if( i != j )
			{
				temp = - sys[ i ][ j ];
				for( k = 0; k < 8; k++ )
				{
					sys[ i ][ k ] += sys[ j ][ k ] * temp;
				}
			}
		}
	}

	memcpy(in_pDstM4x4[0], &(sys[0][4]), sizeof(float) * 4);
	memcpy(in_pDstM4x4[1], &(sys[1][4]), sizeof(float) * 4);
	memcpy(in_pDstM4x4[2], &(sys[2][4]), sizeof(float) * 4);
	memcpy(in_pDstM4x4[3], &(sys[3][4]), sizeof(float) * 4);

	return true;
}

inline void	XSI_RTS_MatrixMultiply(float in_pSrc1M4x4[4][4], float in_pSrc2M4x4[4][4], float in_pDstM4x4[4][4])
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

inline void XSI_RTS_InitializeSemantics_inuse(XSI_RTS_FXSemantics_inuse& in_Data)
{
	memset(&in_Data, 0, sizeof(XSI_RTS_FXSemantics_inuse) - sizeof(in_Data.m_Params));
	in_Data.m_Params.DisposeData();
}

inline void XSI_RTS_InitializeSemantics(XSI_RTS_FXSemantics& in_Data)
{
	memset(&in_Data, 0, sizeof(XSI_RTS_FXSemantics));
}


inline bool XSI_RTS_RegisterSemanticParam
(
	XSI_RTS_FXSemantics_inuse&	in_SemanticInUse,
	void*						in_pSrcParam,
	void*						in_pDstParam,
	bool&						in_pComputeFlag
)
{
	LONG index;

	in_SemanticInUse.m_Params.Extend(1);
	index = in_SemanticInUse.m_Params.GetUsed()-1;
	in_SemanticInUse.m_Params[index].m_pSourceParam = in_pSrcParam;
	in_SemanticInUse.m_Params[index].m_pDestParam = in_pDstParam;
	in_pComputeFlag = true;
	return true;
}

inline bool XSI_RTS_RegisterSemantics
(
	XSI_RTS_FXSemantics&		in_SemanticData,
	XSI_RTS_FXSemantics_inuse&	in_SemanticInUse,
	char*						in_pSemanticName,
	void*						in_pParameterHandle
)
{
	bool l_bRetValue = true;
/*
	in_SemanticData.m_MaxAmbientLights = 0;
	in_SemanticData.m_MaxDirectionalLights = 0;
	in_SemanticData.m_MaxPointLights = 0;
	in_SemanticData.m_MaxSpotLights = 0;
*/

	// big if cascade, should be easy to add stuff in there

	if(_strnicmp(in_pSemanticName, "Sas.Skeleton.MeshToJointToWorld", strlen("Sas.Skeleton.MeshToJointToWorld")) == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_World, in_pParameterHandle, in_SemanticInUse.m_World);
	}
	else if(_stricmp(in_pSemanticName, "world") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_World, in_pParameterHandle, in_SemanticInUse.m_World);
	}
	else if(_stricmp(in_pSemanticName, "worldi") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldI, in_pParameterHandle, in_SemanticInUse.m_WorldI);
	}
	else if(_stricmp(in_pSemanticName, "worldt") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldT, in_pParameterHandle, in_SemanticInUse.m_WorldT);
	}
	else if(_stricmp(in_pSemanticName, "worldit") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldIT, in_pParameterHandle, in_SemanticInUse.m_WorldIT);
	}
	else if(_stricmp(in_pSemanticName, "worldinverse") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldI, in_pParameterHandle, in_SemanticInUse.m_WorldI);
	}
	else if(_stricmp(in_pSemanticName, "worldtranspose") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldT, in_pParameterHandle, in_SemanticInUse.m_WorldT);
	}
	else if(_stricmp(in_pSemanticName, "worldinversetranspose") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldIT, in_pParameterHandle, in_SemanticInUse.m_WorldIT);
	}
	else if(_stricmp(in_pSemanticName, "model") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_World, in_pParameterHandle, in_SemanticInUse.m_World);
	}
	else if(_stricmp(in_pSemanticName, "modeli") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldI, in_pParameterHandle, in_SemanticInUse.m_WorldI);
	}
	else if(_stricmp(in_pSemanticName, "modelt") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldT, in_pParameterHandle, in_SemanticInUse.m_WorldT);
	}
	else if(_stricmp(in_pSemanticName, "modelit") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldIT, in_pParameterHandle, in_SemanticInUse.m_WorldIT);
	}
	else if(_stricmp(in_pSemanticName, "modelinverse") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldI, in_pParameterHandle, in_SemanticInUse.m_WorldI);
	}
	else if(_stricmp(in_pSemanticName, "modeltranspose") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldT, in_pParameterHandle, in_SemanticInUse.m_WorldT);
	}
	else if(_stricmp(in_pSemanticName, "modelinversetranspose") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldIT, in_pParameterHandle, in_SemanticInUse.m_WorldIT);
	}
	else if(_stricmp(in_pSemanticName, "simodel") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_World, in_pParameterHandle, in_SemanticInUse.m_World);
	}
	else if(_stricmp(in_pSemanticName, "simodeli") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldI, in_pParameterHandle, in_SemanticInUse.m_WorldI);
	}
	else if(_stricmp(in_pSemanticName, "simodelt") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldT, in_pParameterHandle, in_SemanticInUse.m_WorldT);
	}
	else if(_stricmp(in_pSemanticName, "simodelit") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldIT, in_pParameterHandle, in_SemanticInUse.m_WorldIT);
	}
	else if(_stricmp(in_pSemanticName, "view") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_View, in_pParameterHandle, in_SemanticInUse.m_View);
	}
	else if(_stricmp(in_pSemanticName, "viewi") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_ViewI, in_pParameterHandle, in_SemanticInUse.m_ViewI);
	}
	else if(_stricmp(in_pSemanticName, "viewt") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_ViewT, in_pParameterHandle, in_SemanticInUse.m_ViewT);
	}
	else if(_stricmp(in_pSemanticName, "viewit") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_ViewIT, in_pParameterHandle, in_SemanticInUse.m_ViewIT);
	}
	else if(_stricmp(in_pSemanticName, "viewinverse") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_ViewI, in_pParameterHandle, in_SemanticInUse.m_ViewI);
	}
	else if(_stricmp(in_pSemanticName, "viewtranspose") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_ViewT, in_pParameterHandle, in_SemanticInUse.m_ViewT);
	}
	else if(_stricmp(in_pSemanticName, "viewinversetranspose") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_ViewIT, in_pParameterHandle, in_SemanticInUse.m_ViewIT);
	}
	else if(_stricmp(in_pSemanticName, "siview") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_View, in_pParameterHandle, in_SemanticInUse.m_View);
	}
	else if(_stricmp(in_pSemanticName, "siviewi") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_ViewI, in_pParameterHandle, in_SemanticInUse.m_ViewI);
	}
	else if(_stricmp(in_pSemanticName, "siviewt") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_ViewT, in_pParameterHandle, in_SemanticInUse.m_ViewT);
	}
	else if(_stricmp(in_pSemanticName, "siviewit") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_ViewIT, in_pParameterHandle, in_SemanticInUse.m_ViewIT);
	}
	else if(_stricmp(in_pSemanticName, "Sas.Camera.Projection") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_Proj, in_pParameterHandle, in_SemanticInUse.m_Proj);
	}
	else if(_stricmp(in_pSemanticName, "projection") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_Proj, in_pParameterHandle, in_SemanticInUse.m_Proj);
	}
	else if(_stricmp(in_pSemanticName, "projectioni") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_ProjI, in_pParameterHandle, in_SemanticInUse.m_ProjI);
	}
	else if(_stricmp(in_pSemanticName, "projectiont") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_ProjT, in_pParameterHandle, in_SemanticInUse.m_ProjT);
	}
	else if(_stricmp(in_pSemanticName, "projectionit") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_ProjIT, in_pParameterHandle, in_SemanticInUse.m_ProjIT);
	}
	else if(_stricmp(in_pSemanticName, "projectioninverse") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_ProjI, in_pParameterHandle, in_SemanticInUse.m_ProjI);
	}
	else if(_stricmp(in_pSemanticName, "projectiontranspose") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_ProjT, in_pParameterHandle, in_SemanticInUse.m_ProjT);
	}
	else if(_stricmp(in_pSemanticName, "projectioninversetranspose") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_ProjIT, in_pParameterHandle, in_SemanticInUse.m_ProjIT);
	}
	else if(_stricmp(in_pSemanticName, "siproj") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_Proj, in_pParameterHandle, in_SemanticInUse.m_Proj);
	}
	else if(_stricmp(in_pSemanticName, "siproji") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_ProjI, in_pParameterHandle, in_SemanticInUse.m_ProjI);
	}
	else if(_stricmp(in_pSemanticName, "siprojt") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_ProjT, in_pParameterHandle, in_SemanticInUse.m_ProjT);
	}
	else if(_stricmp(in_pSemanticName, "siprojit") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_ProjIT, in_pParameterHandle, in_SemanticInUse.m_ProjIT);
	}
	else if(_stricmp(in_pSemanticName, "Sas.Camera.WorldToView") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldView, in_pParameterHandle, in_SemanticInUse.m_WorldView);
	}
	else if(_stricmp(in_pSemanticName, "worldview") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldView, in_pParameterHandle, in_SemanticInUse.m_WorldView);
	}
	else if(_stricmp(in_pSemanticName, "worldviewi") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewI, in_pParameterHandle, in_SemanticInUse.m_WorldViewI);
	}
	else if(_stricmp(in_pSemanticName, "worldviewt") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewT, in_pParameterHandle, in_SemanticInUse.m_WorldViewT);
	}
	else if(_stricmp(in_pSemanticName, "worldviewit") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewIT, in_pParameterHandle, in_SemanticInUse.m_WorldViewIT);
	}
	else if(_stricmp(in_pSemanticName, "worldviewinverse") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewI, in_pParameterHandle, in_SemanticInUse.m_WorldViewI);
	}
	else if(_stricmp(in_pSemanticName, "worldviewtranspose") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewT, in_pParameterHandle, in_SemanticInUse.m_WorldViewT);
	}
	else if(_stricmp(in_pSemanticName, "worldviewinversetranspose") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewIT, in_pParameterHandle, in_SemanticInUse.m_WorldViewIT);
	}
	else if(_stricmp(in_pSemanticName, "modelview") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldView, in_pParameterHandle, in_SemanticInUse.m_WorldView);
	}
	else if(_stricmp(in_pSemanticName, "modelviewi") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewI, in_pParameterHandle, in_SemanticInUse.m_WorldViewI);
	}
	else if(_stricmp(in_pSemanticName, "modelviewt") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewT, in_pParameterHandle, in_SemanticInUse.m_WorldViewT);
	}
	else if(_stricmp(in_pSemanticName, "modelviewit") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewIT, in_pParameterHandle, in_SemanticInUse.m_WorldViewIT);
	}
	else if(_stricmp(in_pSemanticName, "modelviewinverse") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewI, in_pParameterHandle, in_SemanticInUse.m_WorldViewI);
	}
	else if(_stricmp(in_pSemanticName, "modelviewtranspose") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewT, in_pParameterHandle, in_SemanticInUse.m_WorldViewT);
	}
	else if(_stricmp(in_pSemanticName, "modelviewinversetranspose") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewIT, in_pParameterHandle, in_SemanticInUse.m_WorldViewIT);
	}
	else if(_stricmp(in_pSemanticName, "simodelview") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldView, in_pParameterHandle, in_SemanticInUse.m_WorldView);
	}
	else if(_stricmp(in_pSemanticName, "simodelviewi") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewI, in_pParameterHandle, in_SemanticInUse.m_WorldViewI);
	}
	else if(_stricmp(in_pSemanticName, "simodelviewt") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewT, in_pParameterHandle, in_SemanticInUse.m_WorldViewT);
	}
	else if(_stricmp(in_pSemanticName, "simodelviewit") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewIT, in_pParameterHandle, in_SemanticInUse.m_WorldViewIT);
	}
	else if(_stricmp(in_pSemanticName, "worldviewprojection") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewProj, in_pParameterHandle, in_SemanticInUse.m_WorldViewProj);
	}
	else if(_stricmp(in_pSemanticName, "worldviewprojectioni") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewProjI, in_pParameterHandle, in_SemanticInUse.m_WorldViewProjI);
	}
	else if(_stricmp(in_pSemanticName, "worldviewprojectiont") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewProjT, in_pParameterHandle, in_SemanticInUse.m_WorldViewProjT);
	}
	else if(_stricmp(in_pSemanticName, "worldviewprojectionit") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewProjIT, in_pParameterHandle, in_SemanticInUse.m_WorldViewProjIT);
	}
	else if(_stricmp(in_pSemanticName, "worldviewprojectioninverse") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewProjI, in_pParameterHandle, in_SemanticInUse.m_WorldViewProjI);
	}
	else if(_stricmp(in_pSemanticName, "worldviewprojectiontranspose") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewProjT, in_pParameterHandle, in_SemanticInUse.m_WorldViewProjT);
	}
	else if(_stricmp(in_pSemanticName, "worldviewprojectioninversetranspose") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewProjIT, in_pParameterHandle, in_SemanticInUse.m_WorldViewProjIT);
	}
	else if(_stricmp(in_pSemanticName, "modelviewprojection") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewProj, in_pParameterHandle, in_SemanticInUse.m_WorldViewProj);
	}
	else if(_stricmp(in_pSemanticName, "modelviewprojectioni") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewProjI, in_pParameterHandle, in_SemanticInUse.m_WorldViewProjI);
	}
	else if(_stricmp(in_pSemanticName, "modelviewprojectiont") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewProjT, in_pParameterHandle, in_SemanticInUse.m_WorldViewProjT);
	}
	else if(_stricmp(in_pSemanticName, "modelviewprojectionit") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewProjIT, in_pParameterHandle, in_SemanticInUse.m_WorldViewProjIT);
	}
	else if(_stricmp(in_pSemanticName, "modelviewprojectioninverse") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewProjI, in_pParameterHandle, in_SemanticInUse.m_WorldViewProjI);
	}
	else if(_stricmp(in_pSemanticName, "modelviewprojectiontranspose") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewProjT, in_pParameterHandle, in_SemanticInUse.m_WorldViewProjT);
	}
	else if(_stricmp(in_pSemanticName, "modelviewprojectioninversetranspose") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewProjIT, in_pParameterHandle, in_SemanticInUse.m_WorldViewProjIT);
	}
	else if(_stricmp(in_pSemanticName, "simodelviewproj") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewProj, in_pParameterHandle, in_SemanticInUse.m_WorldViewProj);
	}
	else if(_stricmp(in_pSemanticName, "simodelviewproji") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewProjI, in_pParameterHandle, in_SemanticInUse.m_WorldViewProjI);
	}
	else if(_stricmp(in_pSemanticName, "simodelviewprojt") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewProjT, in_pParameterHandle, in_SemanticInUse.m_WorldViewProjT);
	}
	else if(_stricmp(in_pSemanticName, "simodelviewprojit") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_WorldViewProjIT, in_pParameterHandle, in_SemanticInUse.m_WorldViewProjIT);
	}
	else if(_stricmp(in_pSemanticName, "cameraposition") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_CameraPos, in_pParameterHandle, in_SemanticInUse.m_CameraPos);
	}
	else if(_stricmp(in_pSemanticName, "sieyepos") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_CameraPos, in_pParameterHandle, in_SemanticInUse.m_CameraPos);
	}
	else if(_stricmp(in_pSemanticName, "sas.camera.position") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_CameraPos, in_pParameterHandle, in_SemanticInUse.m_CameraPos);
	}
	else if(_stricmp(in_pSemanticName, "sas.camera.nearfarclipping") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_CameraNearFar, in_pParameterHandle, in_SemanticInUse.m_CameraNearFar);
	}
	else if(_stricmp(in_pSemanticName, "sas.time.now") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_TimeNow, in_pParameterHandle, in_SemanticInUse.m_TimeNow);
	}
	else if(_stricmp(in_pSemanticName, "sas.time.last") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_TimeLast, in_pParameterHandle, in_SemanticInUse.m_TimeLast);
	}
	else if(_stricmp(in_pSemanticName, "sas.time.framenumber") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_TimeFrameNumber, in_pParameterHandle, in_SemanticInUse.m_TimeFrameNumber);
	}
	else if(_stricmp(in_pSemanticName, "sas.numambientlights") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_NumAmbientLights, in_pParameterHandle, in_SemanticInUse.m_NumAmbientLights);
	}
	else if(_stricmp(in_pSemanticName, "sas.numdirectionallights") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_NumDirectionalLights, in_pParameterHandle, in_SemanticInUse.m_NumDirectionalLights);
	}
	else if(_stricmp(in_pSemanticName, "sas.numpointlights") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_NumPointLights, in_pParameterHandle, in_SemanticInUse.m_NumPointLights);
	}
	else if(_stricmp(in_pSemanticName, "sas.numspotlights") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_NumSpotLights, in_pParameterHandle, in_SemanticInUse.m_NumSpotLights);
	}
	else if(_stricmp(in_pSemanticName, "sas.camera") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_SasCamera, in_pParameterHandle, in_SemanticInUse.m_SasCamera);
	}
	else if(_stricmp(in_pSemanticName, "sas.ambientlight") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_AmbientLights, in_pParameterHandle, in_SemanticInUse.m_AmbientLights);
	}
	else if(_strnicmp(in_pSemanticName, "sas.ambientlight", strlen("sas.ambientlight")) == 0)
	{
		char l_IndexText[256];
		char *l_pAddress = NULL;

		l_pAddress = strchr(in_pSemanticName, '[');
		if(l_pAddress)
		{
			int l_Index, l_DstIndex = 0;

			l_pAddress ++;
			while((*l_pAddress != 0) && (*l_pAddress >= '0') && (*l_pAddress <= '9'))
			{
				l_IndexText[l_DstIndex ++] = *l_pAddress;
				l_pAddress++;
			}
			l_IndexText[l_DstIndex ++] = 0;

			l_pAddress = strchr(l_pAddress, '.');
			if(l_pAddress)
				l_pAddress++;

			l_Index = atol(l_IndexText);
//			in_SemanticData.m_MaxAmbientLights = max(in_SemanticData.m_MaxAmbientLights, l_Index);

			if(l_pAddress == NULL)
			{
				XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_AmbientLights, in_pParameterHandle, in_SemanticInUse.m_AmbientLights);
			}
			else if(_stricmp(l_pAddress, "color") == 0)
			{
				XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_AmbientLights[l_Index].m_Color, in_pParameterHandle, in_SemanticInUse.m_AmbientLights);
			}
		}
	}
	else if(_stricmp(in_pSemanticName, "sas.directionallight") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_DirectionalLights, in_pParameterHandle, in_SemanticInUse.m_DirectionalLights);
	}
	else if(_strnicmp(in_pSemanticName, "sas.directionallight", strlen("sas.directionallight")) == 0)
	{
		char l_IndexText[256];
		char *l_pAddress = NULL;

		l_pAddress = strchr(in_pSemanticName, '[');
		if(l_pAddress)
		{
			int l_Index, l_DstIndex = 0;

			l_pAddress ++;
			while((*l_pAddress != 0) && (*l_pAddress >= '0') && (*l_pAddress <= '9'))
			{
				l_IndexText[l_DstIndex ++] = *l_pAddress;
				l_pAddress++;
			}
			l_IndexText[l_DstIndex ++] = 0;

			l_pAddress = strchr(l_pAddress, '.');
			if(l_pAddress)
				l_pAddress++;

			l_Index = atol(l_IndexText);
//			in_SemanticData.m_MaxDirectionalLights = max(in_SemanticData.m_MaxDirectionalLights, l_Index);


			if(l_pAddress == NULL)
			{
				XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_DirectionalLights[l_Index], in_pParameterHandle, in_SemanticInUse.m_DirectionalLights);
			}
			else if(_stricmp(l_pAddress, "color") == 0)
			{
				XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_DirectionalLights[l_Index].m_Color, in_pParameterHandle, in_SemanticInUse.m_DirectionalLights);
			}
			else if(_stricmp(l_pAddress, "direction") == 0)
			{
				XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_DirectionalLights[l_Index].m_Direction, in_pParameterHandle, in_SemanticInUse.m_DirectionalLights);
			}
		}
	}
	else if(_stricmp(in_pSemanticName, "sas.pointlight") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_PointLights, in_pParameterHandle, in_SemanticInUse.m_PointLights);
	}
	else if(_strnicmp(in_pSemanticName, "sas.pointlight", strlen("sas.pointlight")) == 0)
	{
		char l_IndexText[256];
		char *l_pAddress = NULL;

		l_pAddress = strchr(in_pSemanticName, '[');
		if(l_pAddress)
		{
			int l_Index, l_DstIndex = 0;

			l_pAddress ++;
			while((*l_pAddress != 0) && (*l_pAddress >= '0') && (*l_pAddress <= '9'))
			{
				l_IndexText[l_DstIndex ++] = *l_pAddress;
				l_pAddress++;
			}
			l_IndexText[l_DstIndex ++] = 0;

			l_pAddress = strchr(l_pAddress, '.');
			if(l_pAddress)
				l_pAddress++;

			l_Index = atol(l_IndexText);
//			in_SemanticData.m_MaxPointLights = max(in_SemanticData.m_MaxPointLights, l_Index);


			if(l_pAddress == NULL)
			{
				XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_PointLights[l_Index], in_pParameterHandle, in_SemanticInUse.m_PointLights);
			}
			else if(_stricmp(l_pAddress, "color") == 0)
			{
				XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_PointLights[l_Index].m_Color, in_pParameterHandle, in_SemanticInUse.m_PointLights);
			}
			else if(_stricmp(l_pAddress, "position") == 0)
			{
				XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_PointLights[l_Index].m_Position, in_pParameterHandle, in_SemanticInUse.m_PointLights);
			}
			else if(_stricmp(l_pAddress, "range") == 0)
			{
				XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_PointLights[l_Index].m_Range, in_pParameterHandle, in_SemanticInUse.m_PointLights);
			}
		}
	}
	else if(_stricmp(in_pSemanticName, "sas.spotlight") == 0)
	{
		XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_SpotLights, in_pParameterHandle, in_SemanticInUse.m_SpotLights);
	}
	else if(_strnicmp(in_pSemanticName, "sas.spotlight", strlen("sas.spotlight")) == 0)
	{
		char l_IndexText[256];
		char *l_pAddress = NULL;

		l_pAddress = strchr(in_pSemanticName, '[');
		if(l_pAddress)
		{
			int l_Index, l_DstIndex = 0;

			l_pAddress ++;
			while((*l_pAddress != 0) && (*l_pAddress >= '0') && (*l_pAddress <= '9'))
			{
				l_IndexText[l_DstIndex ++] = *l_pAddress;
				l_pAddress++;
			}
			l_IndexText[l_DstIndex ++] = 0;

			l_pAddress = strchr(l_pAddress, '.');
			if(l_pAddress)
				l_pAddress++;

			l_Index = atol(l_IndexText);
//			in_SemanticData.m_MaxSpotLights = max(in_SemanticData.m_MaxSpotLights, l_Index);


			if(l_pAddress == NULL)
			{
				XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_SpotLights[l_Index], in_pParameterHandle, in_SemanticInUse.m_SpotLights);
			}
			else if(_stricmp(l_pAddress, "color") == 0)
			{
				XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_SpotLights[l_Index].m_Color, in_pParameterHandle, in_SemanticInUse.m_SpotLights);
			}
			else if(_stricmp(l_pAddress, "position") == 0)
			{
				XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_SpotLights[l_Index].m_Position, in_pParameterHandle, in_SemanticInUse.m_SpotLights);
			}
			else if(_stricmp(l_pAddress, "direction") == 0)
			{
				XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_SpotLights[l_Index].m_Direction, in_pParameterHandle, in_SemanticInUse.m_SpotLights);
			}
			else if(_stricmp(l_pAddress, "range") == 0)
			{
				XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_SpotLights[l_Index].m_Range, in_pParameterHandle, in_SemanticInUse.m_SpotLights);
			}
			else if(_stricmp(l_pAddress, "phi") == 0)
			{
				XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_SpotLights[l_Index].m_Phi, in_pParameterHandle, in_SemanticInUse.m_SpotLights);
			}
			else if(_stricmp(l_pAddress, "theta") == 0)
			{
				XSI_RTS_RegisterSemanticParam(in_SemanticInUse, &in_SemanticData.m_SpotLights[l_Index].m_Theta, in_pParameterHandle, in_SemanticInUse.m_SpotLights);
			}
		}
	}
	else if(_strnicmp(in_pSemanticName, "sasglobal", strlen("sasglobal")) == 0)
	{

	}
	else
	{
		l_bRetValue = false;
	}

	return l_bRetValue;
}

typedef 	void (*RTS_BindSemanticCallback)
(
	void*		in_pContext,
	void*		in_pParameterHandle,
	void*		in_pValue
);

inline void XSI_RTS_BindCommonSemantics
(
	XSI_RTS_FXSemantics&		in_SemanticData,
	XSI_RTS_FXSemantics_inuse&	in_SemanticInUse,
	XSI_RTS_SystemParams*		in_pSysParams,
	void*						in_pContext,
	RTS_BindSemanticCallback	fnBind
)
{

	memcpy(in_SemanticData.m_ViewI, in_pSysParams->m_SceneData->m_sCamera.m_mMatrix, sizeof(in_SemanticData.m_ViewI));
	XSI_RTS_MatrixInvert(in_SemanticData.m_ViewI, in_SemanticData.m_View);

	memcpy(in_SemanticData.m_World, in_pSysParams->m_m4x4ObjectPose, sizeof(in_SemanticData.m_World));

	// compute these matrices
	XSI_RTS_MatrixMultiply(in_SemanticData.m_World, in_SemanticData.m_View, in_SemanticData.m_WorldView);
	XSI_RTS_MatrixMultiply(in_SemanticData.m_WorldView, in_SemanticData.m_Proj, in_SemanticData.m_WorldViewProj);

	if(in_SemanticInUse.m_WorldI)
	{
		XSI_RTS_MatrixInvert(in_SemanticData.m_World, in_SemanticData.m_WorldI);
	}

	if(in_SemanticInUse.m_WorldT)
	{
		XSI_RTS_MatrixTranspose(in_SemanticData.m_World, in_SemanticData.m_WorldT);
	}

	if(in_SemanticInUse.m_WorldIT)
	{
		XSI_RTS_MatrixInvert(in_SemanticData.m_World, in_SemanticData.m_WorldI);
		XSI_RTS_MatrixTranspose(in_SemanticData.m_WorldI, in_SemanticData.m_WorldIT);
	}

	if(in_SemanticInUse.m_ViewT)
	{
		XSI_RTS_MatrixTranspose(in_SemanticData.m_View, in_SemanticData.m_ViewT);
	}

	if(in_SemanticInUse.m_ViewIT)
	{
		XSI_RTS_MatrixTranspose(in_SemanticData.m_ViewI, in_SemanticData.m_ViewIT);
	}

	if(in_SemanticInUse.m_ProjI)
	{
		XSI_RTS_MatrixInvert(in_SemanticData.m_Proj, in_SemanticData.m_ProjI);
	}

	if(in_SemanticInUse.m_ProjT)
	{
		XSI_RTS_MatrixTranspose(in_SemanticData.m_Proj, in_SemanticData.m_ProjT);
	}

	if(in_SemanticInUse.m_ProjIT)
	{
		XSI_RTS_MatrixInvert(in_SemanticData.m_Proj, in_SemanticData.m_ProjI);
		XSI_RTS_MatrixTranspose(in_SemanticData.m_ProjI, in_SemanticData.m_ProjIT);
	}


	if(in_SemanticInUse.m_WorldViewI)
	{
		XSI_RTS_MatrixInvert(in_SemanticData.m_WorldView, in_SemanticData.m_WorldViewI);
	}

	if(in_SemanticInUse.m_WorldViewT)
	{
		XSI_RTS_MatrixTranspose(in_SemanticData.m_WorldView, in_SemanticData.m_WorldViewT);
	}

	if(in_SemanticInUse.m_WorldViewIT)
	{
		XSI_RTS_MatrixInvert(in_SemanticData.m_WorldView, in_SemanticData.m_WorldViewI);
		XSI_RTS_MatrixTranspose(in_SemanticData.m_WorldViewI, in_SemanticData.m_WorldViewIT);
	}

	if(in_SemanticInUse.m_WorldViewProjI)
	{
		XSI_RTS_MatrixInvert(in_SemanticData.m_WorldViewProj, in_SemanticData.m_WorldViewProjI);
	}

	if(in_SemanticInUse.m_WorldViewProjT)
	{
		XSI_RTS_MatrixTranspose(in_SemanticData.m_WorldViewProj, in_SemanticData.m_WorldViewProjT);
	}

	if(in_SemanticInUse.m_WorldViewProjIT)
	{
		XSI_RTS_MatrixInvert(in_SemanticData.m_WorldViewProj, in_SemanticData.m_WorldViewProjI);
		XSI_RTS_MatrixTranspose(in_SemanticData.m_WorldViewProjI, in_SemanticData.m_WorldViewProjIT);
	}

	if( in_SemanticInUse.m_CameraPos )
	{
		if(!in_SemanticInUse.m_ViewI)
		{
			XSI_RTS_MatrixInvert(in_SemanticData.m_View, in_SemanticData.m_ViewI);
		}

		memcpy(in_SemanticData.m_CameraPos, in_SemanticData.m_ViewI[3], sizeof(in_SemanticData.m_CameraPos));
	}

	if( in_SemanticInUse.m_CameraNearFar )
	{
		in_SemanticData.m_CameraNearFar[0] = in_pSysParams->m_SceneData->m_sCamera.m_fNear;
		in_SemanticData.m_CameraNearFar[1] = in_pSysParams->m_SceneData->m_sCamera.m_fFar;
	}

	if( in_SemanticInUse.m_TimeNow )
	{
		in_SemanticData.m_TimeNow[0] = (float) in_pSysParams->m_SceneData->m_fCurrentTime;
	}

	if( in_SemanticInUse.m_TimeLast )
	{
		in_SemanticData.m_TimeLast[0] = in_SemanticInUse.m_LastTime;
	}

	if( in_SemanticInUse.m_TimeFrameNumber )
	{
		in_SemanticData.m_TimeFrameNumber[0] = (float)in_pSysParams->m_SceneData->m_fCurrentTime * 30.0f; // hard coded for 30 fps
	}

	if( in_SemanticInUse.m_NumAmbientLights )
	{
		in_SemanticData.m_NumAmbientLights[0] = 1;
	}

	if( in_SemanticInUse.m_SasCamera )
	{
		if(!in_SemanticInUse.m_ViewI)
		{
			XSI_RTS_MatrixInvert(in_SemanticData.m_View, in_SemanticData.m_ViewI);
		}

		in_SemanticData.m_SasCamera[0].m_NearFarClipping[0] = in_pSysParams->m_SceneData->m_sCamera.m_fNear;
		in_SemanticData.m_SasCamera[0].m_NearFarClipping[1] = in_pSysParams->m_SceneData->m_sCamera.m_fFar;
		memcpy(in_SemanticData.m_SasCamera[0].m_Position, in_SemanticData.m_ViewI[3], sizeof(in_SemanticData.m_SasCamera[0].m_Position));
		memcpy(in_SemanticData.m_SasCamera[0].m_Projection, in_SemanticData.m_Proj,  sizeof(in_SemanticData.m_SasCamera[0].m_Projection));
		memcpy(in_SemanticData.m_SasCamera[0].m_WorldToView, in_SemanticData.m_WorldView,  sizeof(in_SemanticData.m_SasCamera[0].m_WorldToView));
	}

	if( in_SemanticInUse.m_AmbientLights )
	{
		in_SemanticData.m_AmbientLights[0].m_Color[0] = 0.3f;
		in_SemanticData.m_AmbientLights[0].m_Color[1] = 0.3f;
		in_SemanticData.m_AmbientLights[0].m_Color[2] = 0.3f;
		in_SemanticData.m_AmbientLights[0].m_Color[3] = 1.0f;
	}

	int loop;

	int l_NumDirectionalLights = 0;
	int l_NumPointLights = 0;
	int l_NumSpotLights = 0;

	in_SemanticData.m_NumDirectionalLights[0] = 0;
	in_SemanticData.m_NumPointLights[0] = 0;
	in_SemanticData.m_NumSpotLights[0] = 0;


	bool bConvertToPointLights =		in_SemanticInUse.m_PointLights && !in_SemanticInUse.m_DirectionalLights && !in_SemanticInUse.m_SpotLights;
	bool bConvertToDirectionalLights =	!in_SemanticInUse.m_PointLights && in_SemanticInUse.m_DirectionalLights && !in_SemanticInUse.m_SpotLights;

	if( (in_SemanticInUse.m_PointLights) || (in_SemanticInUse.m_DirectionalLights) || (in_SemanticInUse.m_SpotLights))
	{
		for(loop = 0; loop < in_pSysParams->m_SceneData->m_iNbLights; loop++)
		{
			XSI_RTS_Light& sceneLight( in_pSysParams->m_SceneData->m_pLights[loop] );
			
			if( sceneLight.m_eType == RTS_LIGHT_POINT )
			{
				if( bConvertToDirectionalLights )
				{
					XSI_RTS_SasDirectionalLight& dirLight(in_SemanticData.m_DirectionalLights[l_NumDirectionalLights]);

					memcpy( dirLight.m_Color, &sceneLight.m_fRed, 4*sizeof(float) );

					dirLight.m_Direction[0] = -sceneLight.m_fPosX; // Heuristic light pointing at the origin
					dirLight.m_Direction[1] = -sceneLight.m_fPosY; // Heuristic light pointing at the origin
					dirLight.m_Direction[2] = -sceneLight.m_fPosZ; // Heuristic light pointing at the origin
					dirLight.m_Direction[3] = 1.0f;  // Heuristic light pointing at the origin

					// Normalize
					float fNorm = sqrtf( dirLight.m_Direction[0]*dirLight.m_Direction[0] + dirLight.m_Direction[1]*dirLight.m_Direction[1] + dirLight.m_Direction[2]*dirLight.m_Direction[2] );
					dirLight.m_Direction[0] /= fNorm;
					dirLight.m_Direction[1] /= fNorm;
					dirLight.m_Direction[2] /= fNorm;

					l_NumDirectionalLights++;
					in_SemanticData.m_NumDirectionalLights[0]++;
				}
				else // Normal Point Light
				{
					tagXSI_RTS_SasPointLight& pointLight(in_SemanticData.m_PointLights[l_NumPointLights]);

					memcpy( pointLight.m_Color, &sceneLight.m_fRed, 4*sizeof(float) );
					memcpy( pointLight.m_Position, &sceneLight.m_fPosX, 4*sizeof(float) );

					pointLight.m_Range = FLT_MAX;

					l_NumPointLights++;
					in_SemanticData.m_NumPointLights[0]++;
				}
				
			}
			else if(in_pSysParams->m_SceneData->m_pLights[loop].m_eType == RTS_LIGHT_INFINITE)
			{
				if( bConvertToPointLights )
				{
					tagXSI_RTS_SasPointLight& pointLight(in_SemanticData.m_PointLights[l_NumPointLights]);

					memcpy( pointLight.m_Color, &sceneLight.m_fRed, 4*sizeof(float) );
					
					// Guess what the directionnal position is encoded in the direction. This helps us convert it to a point light.
					pointLight.m_Position[0] = sceneLight.m_fDirX; 
					pointLight.m_Position[1] = sceneLight.m_fDirY; 
					pointLight.m_Position[2] = sceneLight.m_fDirZ; 
					pointLight.m_Position[3] = 1.0f;  

					pointLight.m_Range = FLT_MAX;

					l_NumPointLights++;
					in_SemanticData.m_NumPointLights[0]++;
				}
				else
				{
					XSI_RTS_SasDirectionalLight& dirLight(in_SemanticData.m_DirectionalLights[l_NumDirectionalLights]);

					memcpy( dirLight.m_Color, &sceneLight.m_fRed, 4*sizeof(float) );

					dirLight.m_Direction[0] = -sceneLight.m_fPosX;
					dirLight.m_Direction[1] = -sceneLight.m_fPosY;
					dirLight.m_Direction[2] = -sceneLight.m_fPosZ;
					dirLight.m_Direction[3] = sceneLight.m_fPosW;

					l_NumDirectionalLights++;
					in_SemanticData.m_NumDirectionalLights[0]++;
				}
			}
			else if(in_pSysParams->m_SceneData->m_pLights[loop].m_eType == RTS_LIGHT_SPOT)
			{
				if( bConvertToPointLights )
				{
					tagXSI_RTS_SasPointLight& pointLight(in_SemanticData.m_PointLights[l_NumPointLights]);

					memcpy( pointLight.m_Color, &sceneLight.m_fRed, 4*sizeof(float) );
					memcpy( pointLight.m_Position, &sceneLight.m_fPosX, 4*sizeof(float) );

					pointLight.m_Range = FLT_MAX;

					l_NumPointLights++;
					in_SemanticData.m_NumPointLights[0]++;
				}
				else if( bConvertToDirectionalLights )
				{
					XSI_RTS_SasDirectionalLight& dirLight(in_SemanticData.m_DirectionalLights[l_NumDirectionalLights]);

					memcpy( dirLight.m_Color, &sceneLight.m_fRed, 4*sizeof(float) );
					memcpy( dirLight.m_Direction, &sceneLight.m_fDirX, 3*sizeof(float) );

					l_NumDirectionalLights++;
					in_SemanticData.m_NumDirectionalLights[0]++;
				}
				else
				{
					XSI_RTS_SasSpotLight& spotLight( in_SemanticData.m_SpotLights[l_NumSpotLights] );

					memcpy( spotLight.m_Color, &sceneLight.m_fRed, 4*sizeof(float) );
					memcpy( spotLight.m_Position, &sceneLight.m_fPosX, 4*sizeof(float) );

					
					memcpy( spotLight.m_Direction, &sceneLight.m_fDirX, 3*sizeof(float) );
					spotLight.m_Direction[3] = 1.0f;


					spotLight.m_Range	= FLT_MAX;
					spotLight.m_Phi		= sceneLight.m_fConeAngle;
					spotLight.m_Theta	= sceneLight.m_fConeAngle;

					l_NumSpotLights++;
					in_SemanticData.m_NumSpotLights[0]++;
				}
			}
		}
	}

	// now bind everything
	for(loop = 0; loop < in_SemanticInUse.m_Params.GetUsed(); loop++)
	{
		fnBind(in_pContext, in_SemanticInUse.m_Params[loop].m_pDestParam, in_SemanticInUse.m_Params[loop].m_pSourceParam);
	}

}

//////////////////////////////////////////////////////////////////////////////////
//
// RTS 3.0
//
//////////////////////////////////////////////////////////////////////////////////

/*! \defgroup eRenderMode eRenderMode Enum
	Enumerates the different modes in which a realtime shader can be asked to render.
	\sa IRTSExecutionState::GetRenderMode
	\since 7.0
@{
*/
enum eRenderMode {
		RenderMode_Render = 0,
		RenderMode_Picking
};

/*!
@}
*/


/*!
@}
*/

/*! \defgroup eChannel eChannel Enum
	Rendering channels.
	\sa IRTSExecutionState::GetChannel
	\since 7.0
@{
*/
enum eChannel {
	Channel_None = 0,		//!< No channel active
	Composite,			//!< Final, composite
	Albedo,				//!< Color
	Normal,				//!< Normal
	Specular,			//!< Specular term
	Reflection,			//!< Reflection term
	AmbientOcclusion,	//!< Ambient occlusion term
	EyePosition,		//!< Eye position
	Custom				//!< User-defined
};
/*!
@}
*/

/*! \defgroup eStandardVertexAttribute eStandardVertexAttribute Enum
	\brief Standard vertex attributes.
	\sa ::GetStandardVertexAttributeName, ::GetStandardVertexAttributeComponents,
		::GetStandardVertexAttributeDefaultXSIName, ::GetStandardVertexAttributeFromXSIName
	\since 7.0
@{
*/
enum eStandardVertexAttribute
{
	ePOSITION=0,			//!< passed using glVertex
	eNORMAL,			//!< passed using glNormal
	eCOLOR0,			//!< passed using glColor
	eCOLOR1,			//!< passed using glSecondaryColor
	eTEXCOORD0,			//!< passed using glMultiTexCoord
	eTEXCOORD1,			//!< passed using glMultiTexCoord
	eTEXCOORD2,			//!< passed using glMultiTexCoord
	eTEXCOORD3,			//!< passed using glMultiTexCoord
	eTEXCOORD4,			//!< passed using glMultiTexCoord
	eTEXCOORD5,			//!< passed using glMultiTexCoord
	eTEXCOORD6,			//!< passed using glMultiTexCoord
	eTEXCOORD7,			//!< passed using glMultiTexCoord
	eTEXCOORD8,			//!< passed using glMultiTexCoord
	eTEXCOORD9,			//!< passed using glMultiTexCoord
	eTEXCOORD10,			//!< passed using glMultiTexCoord
	eTEXCOORD11,			//!< passed using glMultiTexCoord
	eTEXCOORD12,			//!< passed using glMultiTexCoord
	eTEXCOORD13,			//!< passed using glMultiTexCoord
	eTEXCOORD14,			//!< passed using glMultiTexCoord
	eTEXCOORD15,			//!< passed using glMultiTexCoord
	eATTR0,				//!< passed using glVertexAttribute
	eATTR1,				//!< passed using glVertexAttribute
	eATTR2,				//!< passed using glVertexAttribute
	eATTR3,				//!< passed using glVertexAttribute
	eATTR4,				//!< passed using glVertexAttribute
	eATTR5,				//!< passed using glVertexAttribute
	eATTR6,				//!< passed using glVertexAttribute
	eATTR7,				//!< passed using glVertexAttribute
	eATTR8,				//!< passed using glVertexAttribute
	eATTR9,				//!< passed using glVertexAttribute
	eATTR10,			//!< passed using glVertexAttribute
	eATTR11,			//!< passed using glVertexAttribute
	eATTR12,			//!< passed using glVertexAttribute
	eATTR13,			//!< passed using glVertexAttribute
	eATTR14,			//!< passed using glVertexAttribute
	eATTR15,			//!< passed using glVertexAttribute
	eFOGCOORD,			//!< passed using glFogCoord
	ePSIZE,				//!< passed using glPointSize
	eTANGENT,			//!< passed using glMultiTexCoord[6]
	eBINORMAL,			//!< passed using glMultiTexCoord[7]
	eWEIGHT,			//!< DirectX only (D3DDECLUSAGE_BLENDWEIGHT)
    	eINDICE,			//!< DirectX only (D3DDECLUSAGE_BLENDINDICES)
   	eTESSFACTOR,			//!< DirectX only (D3DDECLUSAGE_TESSFACTOR)
	eDEPTH,				//!< DirectX only (D3DDECLUSAGE_DEPTH)
    	eSAMPLE,			//!< DirectX only (D3DDECLUSAGE_SAMPLE)
	eMAX_STANDARD_VERTEX_ATTRIBUTE		// must always remain last enum
};
/*!
@}
*/

/*! \page GlobalFunctions Global Functions
	The following global functions are available in version 3.0 of the RTS API:
	<BR>
	<BR>
	<TABLE BORDER="0">
	<TR><TD>&nbsp;</TD>		<TD>::GetStandardVertexAttributeName:</TD>			<TD>Returns the friendly name for the specified \link eStandardVertexAttribute \endlink</TD></TR>
	<TR><TD>&nbsp;</TD>		<TD>::GetStandardVertexAttributeComponents</TD>		<TD>Returns a string enumerating the components for the specified \link eStandardVertexAttribute \endlink.</TD></TR>
	<TR><TD>&nbsp;</TD>		<TD>::GetStandardVertexAttributeDefaultXSIName</TD>	<TD>Returns the Softimage name matching the specified \link eStandardVertexAttribute \endlink.</TD></TR>
	<TR><TD>&nbsp;</TD>		<TD>::GetStandardVertexAttributeFromXSIName</TD>	<TD>Returns the vertex attribute matching the specified Softimage name.</TD></TR>
	<TR><TD>&nbsp;</TD>		<TD>::GetSizeOfAttribute</TD>						<TD>Returns the size (in bytes) of the specified \link eXSI_Attribute_Size \endlink enum value.</TD></TR>
	</TABLE>
*/

/*! Returns the friendly name for the specified \link eStandardVertexAttribute \endlink.
	\param in_eAttribute The vertex attribute to translate
	\return "attr[0..15]"
	\return "binormal"
	\return "color[0..1]"
	\return "depth"
	\return "fogcoord"
	\return "indice"
	\return "normal"
	\return "position"
	\return "psize"
	\return "sample"
	\return "tangent"
	\return "tessfactor"
	\return "texcoord[0..15]"
	\return "weight"
	\return "undefined"
	\sa ::eStandardVertexAttribute, \ref GlobalFunctions
	\since 7.0
*/
inline const char* GetStandardVertexAttributeName ( eStandardVertexAttribute in_eAttribute )
{
	switch ( in_eAttribute )
	{
	case ePOSITION: return "position"; break;
	case eNORMAL: return "normal"; break;
	case eCOLOR0: return "color0"; break;
	case eCOLOR1: return "color1"; break;
	case eTEXCOORD0: return "texcoord0"; break;
	case eTEXCOORD1: return "texcoord1"; break;
	case eTEXCOORD2: return "texcoord2"; break;
	case eTEXCOORD3: return "texcoord3"; break;
	case eTEXCOORD4: return "texcoord4"; break;
	case eTEXCOORD5: return "texcoord5"; break;
	case eTEXCOORD6: return "texcoord6"; break;
	case eTEXCOORD7: return "texcoord7"; break;
	case eTEXCOORD8: return "texcoord8"; break;
	case eTEXCOORD9: return "texcoord9"; break;
	case eTEXCOORD10: return "texcoord10"; break;
	case eTEXCOORD11: return "texcoord11"; break;
	case eTEXCOORD12: return "texcoord12"; break;
	case eTEXCOORD13: return "texcoord13"; break;
	case eTEXCOORD14: return "texcoord14"; break;
	case eTEXCOORD15: return "texcoord15"; break;
	case eATTR0: return "attr0"; break;
	case eATTR1: return "attr1"; break;
	case eATTR2: return "attr2"; break;
	case eATTR3: return "attr3"; break;
	case eATTR4: return "attr4"; break;
	case eATTR5: return "attr5"; break;
	case eATTR6: return "attr6"; break;
	case eATTR7: return "attr7"; break;
	case eATTR8: return "attr8"; break;
	case eATTR9: return "attr9"; break;
	case eATTR10: return "attr10"; break;
	case eATTR11: return "attr11"; break;
	case eATTR12: return "attr12"; break;
	case eATTR13: return "attr13"; break;
	case eATTR14: return "attr14"; break;
	case eATTR15: return "attr15"; break;
	case eFOGCOORD: return "fogcoord"; break;
	case ePSIZE: return "psize"; break;
	case eTANGENT: return "tangent"; break;
	case eBINORMAL: return "binormal"; break;
	case eWEIGHT: return "weight"; break;
	case eINDICE: return "indice"; break;
	case eTESSFACTOR: return "tessfactor"; break;
	case eDEPTH: return "depth"; break;
	case eSAMPLE: return "sample"; break;
	case eMAX_STANDARD_VERTEX_ATTRIBUTE: return "undefined"; break;
	//default: assert(0);
	}
	return NULL;
};

/*! Returns a string enumerating the components for the specified \link eStandardVertexAttribute \endlink.
	\param in_eAttribute The vertex attribute to translate
	\return "rgba"
	\return "x"
	\return "xyz"
	\return "xyzw"
	\sa ::eStandardVertexAttribute, \ref GlobalFunctions
	\since 7.0
*/
inline const char* GetStandardVertexAttributeComponents ( eStandardVertexAttribute in_eAttribute )
{
	switch ( in_eAttribute )
	{
	case ePOSITION: return "xyz"; break;
	case eNORMAL: return "xyz"; break;
	case eCOLOR0: return "rgba"; break;
	case eCOLOR1: return "rgba"; break;
	case eTEXCOORD0: return "xyzw"; break;
	case eTEXCOORD1: return "xyzw"; break;
	case eTEXCOORD2: return "xyzw"; break;
	case eTEXCOORD3: return "xyzw"; break;
	case eTEXCOORD4: return "xyzw"; break;
	case eTEXCOORD5: return "xyzw"; break;
	case eTEXCOORD6: return "xyzw"; break;
	case eTEXCOORD7: return "xyzw"; break;
	case eTEXCOORD8: return "xyzw"; break;
	case eTEXCOORD9: return "xyzw"; break;
	case eTEXCOORD10: return "xyzw"; break;
	case eTEXCOORD11: return "xyzw"; break;
	case eTEXCOORD12: return "xyzw"; break;
	case eTEXCOORD13: return "xyzw"; break;
	case eTEXCOORD14: return "xyzw"; break;
	case eTEXCOORD15: return "xyzw"; break;
	case eATTR0: return "xyzw"; break;
	case eATTR1: return "xyzw"; break;
	case eATTR2: return "xyzw"; break;
	case eATTR3: return "xyzw"; break;
	case eATTR4: return "xyzw"; break;
	case eATTR5: return "xyzw"; break;
	case eATTR6: return "xyzw"; break;
	case eATTR7: return "xyzw"; break;
	case eATTR8: return "xyzw"; break;
	case eATTR9: return "xyzw"; break;
	case eATTR10: return "xyzw"; break;
	case eATTR11: return "xyzw"; break;
	case eATTR12: return "xyzw"; break;
	case eATTR13: return "xyzw"; break;
	case eATTR14: return "xyzw"; break;
	case eATTR15: return "xyzw"; break;
	case eFOGCOORD: return "x"; break;
	case ePSIZE: return "x"; break;
	case eTANGENT: return "xyzw"; break;	// Softimage encode tangents into a 4-float RGBA vertex color
	case eBINORMAL: return "xyzw"; break;
	case eWEIGHT: return "xyzw"; break;
	case eINDICE: return "xyzw"; break;
	case eTESSFACTOR: return "x"; break;
	case eDEPTH: return "x"; break;
	case eSAMPLE: return "xyzw"; break;
	case eMAX_STANDARD_VERTEX_ATTRIBUTE: return "xyz"; break;
	//default: assert(0);
	}
	return NULL;
};

/*! \defgroup XSI_RTS_ATTRIBUTE_ XSI_RTS_ATTRIBUTE String Constants
	A list of default Softimage names for the most common vertex attributes.
	\sa ::GetStandardVertexAttributeDefaultXSIName, ::GetStandardVertexAttributeFromXSIName
	\since 7.0
@{
*/
#define XSI_RTS_ATTRIBUTE_POSITION		"PointPosition"			//!< Point position
#define XSI_RTS_ATTRIBUTE_NORMAL		"PointNormal"			//!< Point normal
#define XSI_RTS_ATTRIBUTE_COLOR			"Vertex_Color"			//!< Vertex color
#define XSI_RTS_ATTRIBUTE_TANGENT		"Tangents"			//!< Tangent
#define XSI_RTS_ATTRIBUTE_BINORMAL		"Binormals"			//!< Binormal
#define XSI_RTS_ATTRIBUTE_TEXUVW		"Texture_Projection"		//!< Texture projection
#define XSI_RTS_ATTRIBUTE_WEIGHTMAP		"weightmap"			//!< Weight map
#define XSI_RTS_ATTRIBUTE_VELOCITY		"PointVelocity"			//!< Point velocity
#define XSI_RTS_ATTRIBUTE_ORIENTATION		"Orientation"			//!< Orientation
#define XSI_RTS_ATTRIBUTE_AGE			"Age"				//!< Age
#define XSI_RTS_ATTRIBUTE_SIZE			"radius"			//!< Radius
#define XSI_RTS_ATTRIBUTE_ID			"ID"				//!< ID
#define XSI_RTS_ATTRIBUTE_FOG			"Fog"				//!< Fog
#define XSI_RTS_ATTRIBUTE_WEIGHT		"Weight"			//!< Weight
#define XSI_RTS_ATTRIBUTE_INDICE		"Indice"			//!< Index
#define XSI_RTS_ATTRIBUTE_TESSFACTOR		"Tessfactor"			//!< Tesselation factor
#define XSI_RTS_ATTRIBUTE_DEPTH			"Depth"				//!< Depth
#define XSI_RTS_ATTRIBUTE_SAMPLE		"Sample"			//!< Sample

#define XSI_RTS_ATTRIBUTE_AUTOCREATE	"SIAUTOCREATE"		//!< Let Softimage handle the creation of the attribute (useful for tangents and binormals)
/*!
@}
*/

/*! Returns the Softimage name matching the specified \link eStandardVertexAttribute \endlink.
	\param in_eAttribute The vertex attribute to translate (one of the \link eStandardVertexAttribute \endlink values)
	\sa ::eStandardVertexAttribute, ::GetStandardVertexAttributeFromXSIName, \ref GlobalFunctions
	\since 7.0
*/
inline const char* GetStandardVertexAttributeDefaultXSIName ( eStandardVertexAttribute in_eAttribute )
{
	switch ( in_eAttribute )
	{
	case ePOSITION: return XSI_RTS_ATTRIBUTE_POSITION; break;
	case eNORMAL: return XSI_RTS_ATTRIBUTE_NORMAL; break;
	case eCOLOR0: return XSI_RTS_ATTRIBUTE_COLOR; break;
	case eCOLOR1: return XSI_RTS_ATTRIBUTE_COLOR; break;
	case eTEXCOORD0: return XSI_RTS_ATTRIBUTE_TEXUVW; break;
	case eTEXCOORD1: return XSI_RTS_ATTRIBUTE_TEXUVW; break;
	case eTEXCOORD2: return XSI_RTS_ATTRIBUTE_TEXUVW; break;
	case eTEXCOORD3: return XSI_RTS_ATTRIBUTE_TEXUVW; break;
	case eTEXCOORD4: return XSI_RTS_ATTRIBUTE_TEXUVW; break;
	case eTEXCOORD5: return XSI_RTS_ATTRIBUTE_TEXUVW; break;
	case eTEXCOORD6: return XSI_RTS_ATTRIBUTE_TEXUVW; break;
	case eTEXCOORD7: return XSI_RTS_ATTRIBUTE_TEXUVW; break;
	case eTEXCOORD8: return XSI_RTS_ATTRIBUTE_TEXUVW; break;
	case eTEXCOORD9: return XSI_RTS_ATTRIBUTE_TEXUVW; break;
	case eTEXCOORD10: return XSI_RTS_ATTRIBUTE_TEXUVW; break;
	case eTEXCOORD11: return XSI_RTS_ATTRIBUTE_TEXUVW; break;
	case eTEXCOORD12: return XSI_RTS_ATTRIBUTE_TEXUVW; break;
	case eTEXCOORD13: return XSI_RTS_ATTRIBUTE_TEXUVW; break;
	case eTEXCOORD14: return XSI_RTS_ATTRIBUTE_TEXUVW; break;
	case eTEXCOORD15: return XSI_RTS_ATTRIBUTE_TEXUVW; break;
	case eATTR0: return XSI_RTS_ATTRIBUTE_TEXUVW; break;
	case eATTR1: return XSI_RTS_ATTRIBUTE_TEXUVW; break;
	case eATTR2: return XSI_RTS_ATTRIBUTE_TEXUVW; break;
	case eATTR3: return XSI_RTS_ATTRIBUTE_TEXUVW; break;
	case eATTR4: return XSI_RTS_ATTRIBUTE_TEXUVW; break;
	case eATTR5: return XSI_RTS_ATTRIBUTE_TEXUVW; break;
	case eATTR6: return XSI_RTS_ATTRIBUTE_TEXUVW; break;
	case eATTR7: return XSI_RTS_ATTRIBUTE_TEXUVW; break;
	case eATTR8: return XSI_RTS_ATTRIBUTE_TEXUVW; break;
	case eATTR9: return XSI_RTS_ATTRIBUTE_TEXUVW; break;
	case eATTR10: return XSI_RTS_ATTRIBUTE_TEXUVW; break;
	case eATTR11: return XSI_RTS_ATTRIBUTE_TEXUVW; break;
	case eATTR12: return XSI_RTS_ATTRIBUTE_TEXUVW; break;
	case eATTR13: return XSI_RTS_ATTRIBUTE_TEXUVW; break;
	case eATTR14: return XSI_RTS_ATTRIBUTE_TEXUVW; break;
	case eATTR15: return XSI_RTS_ATTRIBUTE_TEXUVW; break;
	case ePSIZE: return XSI_RTS_ATTRIBUTE_SIZE; break;
	case eFOGCOORD: return XSI_RTS_ATTRIBUTE_FOG; break;
	case eTANGENT: return XSI_RTS_ATTRIBUTE_TANGENT; break;
	case eBINORMAL: return XSI_RTS_ATTRIBUTE_BINORMAL; break;
	case eWEIGHT: return XSI_RTS_ATTRIBUTE_WEIGHT; break;
	case eINDICE: return XSI_RTS_ATTRIBUTE_INDICE; break;
	case eTESSFACTOR: return XSI_RTS_ATTRIBUTE_TESSFACTOR; break;
	case eDEPTH: return XSI_RTS_ATTRIBUTE_DEPTH; break;
	case eSAMPLE: return XSI_RTS_ATTRIBUTE_SAMPLE; break;
	}
	return "undefined";
};

/*! Returns the vertex attribute matching the specified Softimage name.
	\param in_szName The name to convert to its corresponding \link eStandardVertexAttribute \endlink value.
	\sa ::eStandardVertexAttribute, ::GetStandardVertexAttributeDefaultXSIName, \ref GlobalFunctions
	\since 7.0
*/
inline eStandardVertexAttribute GetStandardVertexAttributeFromXSIName ( const char* in_szName )
{
	if ( !strcmp ( in_szName, XSI_RTS_ATTRIBUTE_POSITION ) )
		return ePOSITION;
	if ( !strcmp ( in_szName, XSI_RTS_ATTRIBUTE_NORMAL ) )
		return eNORMAL;
	if ( !strcmp ( in_szName, XSI_RTS_ATTRIBUTE_COLOR ) )
		return eCOLOR0;
	if ( !strcmp ( in_szName, XSI_RTS_ATTRIBUTE_TEXUVW ) )
		return eTEXCOORD0;
	if ( !strcmp ( in_szName, XSI_RTS_ATTRIBUTE_FOG ) )
		return eFOGCOORD;
	if ( !strcmp ( in_szName, XSI_RTS_ATTRIBUTE_SIZE ) )
		return ePSIZE;
	if ( !strcmp ( in_szName, XSI_RTS_ATTRIBUTE_WEIGHT ) )
		return eWEIGHT;
	if ( !strcmp ( in_szName, XSI_RTS_ATTRIBUTE_INDICE ) )
		return eINDICE;
	if ( !strcmp ( in_szName, XSI_RTS_ATTRIBUTE_TESSFACTOR ) )
		return eTESSFACTOR;
	if ( !strcmp ( in_szName, XSI_RTS_ATTRIBUTE_DEPTH ) )
		return eDEPTH;
	if ( !strcmp ( in_szName, XSI_RTS_ATTRIBUTE_SAMPLE ) )
		return eSAMPLE;

	if ( strlen(in_szName) >= 7 )
	{
		if ( !strncmp ( in_szName, "TANGENT",7 ) )
			return eTANGENT;
	}
	if ( strlen(in_szName) >= 8 )
	{
		if ( !strncmp ( in_szName, "BINORMAL",8 ) )
			return eBINORMAL;
	}

	return eMAX_STANDARD_VERTEX_ATTRIBUTE;
};

/*! \defgroup eXSI_Attribute_Size eXSI_Attribute_Size Enum
	Enumeration of all possible sizes for RTS elements.
	\sa _tXSI_RTS_Attribute_Size, ::GetSizeOfAttribute, IRTSExecutionState::DrawGeometry
	\since 7.0
@{
*/
enum eXSI_Attribute_Size
{
	XSI_RTS_ZERO = 0,				//!< Zero
	XSI_RTS_LONG,					//!< Long
	XSI_RTS_LONG_2,					//!< Long 2
	XSI_RTS_LONG_3,					//!< Long 3
	XSI_RTS_LONG_4,					//!< Long 4
	XSI_RTS_FLOAT,					//!< Float
	XSI_RTS_FLOAT_2,				//!< Float 2
	XSI_RTS_FLOAT_3,				//!< Float 3
	XSI_RTS_FLOAT_4,				//!< Float 4
	XSI_RTS_FLOAT_QUATERNION_WXYZ,			//!< Float Quaternion WXYZ
	XSI_RTS_DOUBLE,					//!< Double
	XSI_RTS_DOUBLE_2,				//!< Double 2
	XSI_RTS_DOUBLE_3,				//!< Double 3
	XSI_RTS_DOUBLE_4,				//!< Double 4
	XSI_RTS_DOUBLE_QUATERNION_WXYZ,			//!< Double Quaternion WXYZ
	XSI_RTS_MATRIX_3x3,				//!< Matrix 3X3
	XSI_RTS_MATRIX_3x4,				//!< Matrix 3X4
	XSI_RTS_MATRIX_4x4				//!< Matrix 4X4
};
/*!
@}
*/

/*! \struct _tXSI_RTS_Attribute_Size
	\brief The XSI_RTS_Attribute_Size structure.

	This structure is available from the IRTSExecutionState::GetPrimitive function. You use it to pass
	information to the IRTSExecutionState::DrawGeometry function about the geometry to draw.
	\sa IRTSExecutionState::GetPrimitive, IRTSExecutionState::DrawGeometry, \ref Execute "Execute", \xc X3DObject
	\since 7.0
*/
typedef struct _tXSI_RTS_Attribute_Size
{												/*! Size of data elements in attributes array	*/
	eXSI_Attribute_Size		m_eSize;			/*! Length of array								*/
	ULONG					m_iArrayCount;

	size_t GetDynamicMemSize() const { return 0; }
} XSI_RTS_Attribute_Size;

/*! Returns the size (in bytes) of the specified ::eXSI_Attribute_Size enum value.
	\param in_eAttrib The ::eXSI_Attribute_Size enum value for which to calculate the size
	\sa ::eXSI_Attribute_Size, \ref GlobalFunctions
	\since 7.0
*/
inline size_t GetSizeOfAttribute ( eXSI_Attribute_Size in_eAttrib )
{
	size_t retval = 0;

	switch ( in_eAttrib )
	{
		case XSI_RTS_ZERO: retval=0; break;
		case XSI_RTS_LONG: retval=sizeof(LONG); break;
		case XSI_RTS_LONG_2: retval=sizeof(LONG)*2; break;
		case XSI_RTS_LONG_3: retval=sizeof(LONG)*3; break;
		case XSI_RTS_LONG_4: retval=sizeof(LONG)*4; break;
		case XSI_RTS_FLOAT: retval=sizeof(float); break;
		case XSI_RTS_FLOAT_2: retval=sizeof(float)*2; break;
		case XSI_RTS_FLOAT_3: retval=sizeof(float)*3; break;
		case XSI_RTS_FLOAT_4: retval=sizeof(float)*4; break;
		case XSI_RTS_FLOAT_QUATERNION_WXYZ: retval=sizeof(float)*4; break;
		case XSI_RTS_DOUBLE: retval=sizeof(double); break;
		case XSI_RTS_DOUBLE_2: retval=sizeof(double)*2; break;
		case XSI_RTS_DOUBLE_3: retval=sizeof(double)*3; break;
		case XSI_RTS_DOUBLE_4: retval=sizeof(double)*4; break;
		case XSI_RTS_DOUBLE_QUATERNION_WXYZ: retval=sizeof(double)*4; break;
		case XSI_RTS_MATRIX_3x3: retval=sizeof(float)*9; break;
		case XSI_RTS_MATRIX_3x4: retval=sizeof(float)*12; break;
		case XSI_RTS_MATRIX_4x4: retval=sizeof(float)*16; break;
	}
	return retval;
}

/*! \struct _XSI_RTS_Attribute XSI_rtshaders.h
	\brief Defines the attributes to consider when rendering geometry data. These %XSI_RTS_Attribute structs
	are returned in the \ref GetAttributeList "GetAttributeList" callback function.

	This structure holds the name of a single vertex attribute and optionally, its standard vertex attribute
	hardware slot.
	\param m_szName The name of the attribute
	\param m_eVertexAttrib The standard vertex attribute hardware slot
	\sa ::eStandardVertexAttribute, \ref GetAttributeList "GetAttributeList", IRTSExecutionState::DrawGeometry,
		IRTSExecutionState::GetAttributeDescriptorFromMapping, \xt cus_rtshad_GeometryData Geometry Data \endxt,
		\xt cus_rtshad_ExecutionFlow Execution Flow \endxt
*/
typedef struct _XSI_RTS_Attribute
{															/*! Name of a vertex attribute 					*/
	char*							m_szName;				/*! Standard vertex attribute hardware slot 	*/
	eStandardVertexAttribute		m_eVertexAttrib;
} XSI_RTS_Attribute;

/////////////////////////////////////////////////////////////////////////////////////////
// RTS 3.0 Entry points
/////////////////////////////////////////////////////////////////////////////////////////

/*! \page RTS_Callbacks Realtime Shader Callbacks
	Each shader may implement the following callback functions:
	<BR>
	<BR>
	<TABLE BORDER="0">
	<TR><TD>&nbsp;</TD>		<TD>\ref Init "Init"</TD>							<TD>Called the first time the shader is instantiated</TD></TR>
	<TR><TD>&nbsp;</TD>		<TD>\ref InitUI "InitUI"</TD>						<TD>Called when the shader connections change, or one of the specified parameters is changed</TD></TR>
	<TR><TD>&nbsp;</TD>		<TD>\ref Term "Term"</TD>							<TD>Enables the shader to clean up after itself</TD></TR>
	<TR><TD>&nbsp;</TD>		<TD>\ref GetRequirements "GetRequirements"</TD>		<TD>Sets whether any of the requirements listed in the eXSI_RTS_RequirementType enum are required or not </TD></TR>
	<TR><TD>&nbsp;</TD>		<TD>\ref GetAttributeList "GetAttributeList"</TD>	<TD>Enables a shader to tell Softimage which attribute it needs in order to perform rendering</TD></TR>
	<TR><TD>&nbsp;</TD>		<TD>\ref Execute "Execute"</TD>						<TD>Main entry point for rendering the realtime shader</TD></TR>
	</TABLE>

	\note The \ref Init "Init", \ref GetAttributeList "GetAttributeList", and
		\ref Execute "Execute" callbacks are mandatory.

	You may prefix the name of the shader as identified in the SPDL file to the function name
	or any other string. For example, if the shader is named \c OGL13Shade, then you could use
	\c OGL13Shade_Init and \c OGL13Shade_Execute, etc. If you choose not to use a prefix, the
	function name must begin with an underscore (for example,  \c _Init, \c _Execute, etc.).

	Each entry point gets a pointer to an instance of an IRTSExecutionState object. This object gives
	you access to scene data such as the current Camera object. You can also use the IRTSExecutionState
	object to access the legacy tagXSI_RTS_SystemParams by calling IRTSExecutionState::GetSystemParams.
	See the IRTSExecutionState reference page for more information.

	\tip These functions return TRUE if successful; otherwise FALSE. All functions take the
		execution state object, the property page parameters, and the shader instance user data as
		arguments. Shader instance user data is useful if you want to pass instance data to the
		\ref Term "Term", \ref Execute "Execute" \ref GetRequirements "GetRequirements" entry points.

	\note The property page parameters are passed into each callback function as a pointer to a
		C structure. The order of parameters matches exactly the order in which they were defined in
		the SPDL file with the exception of texture parameters, which always appear last in the struct.

	\sa \xt cus_rtshad_ExecutionFlow Execution Flow \endxt
	\since 7.0
*/

/*! \page Init Init Callback Reference
	\code
	RTSHADER_API bool (*RTS_Shader3_Init)
	{
		IRTSExecutionState	*in_pExecState,
		void				*in_pParams,
		void				**io_pShaderInstanceData
	}
	\endcode
	The Init callback function is called the first time the shader is instantiated.
	\note This callback is mandatory
	\param in_pExecState The execution state interface
	\param in_pParams The shader property page parameters
	\retval io_pShaderInstanceData Pointer to the shader's instance user data
	\return Success/failure
	\sa IRTSExecutionState, \ref RTS_Callbacks, \xt cus_rtshad_ExecutionFlow Execution Flow \endxt
*/
typedef 	RTSHADER_API bool (*RTS_Shader3_Init)
(
	IRTSExecutionState	*in_pExecState,					//! The execution state interface
	void				*in_pParams,					//! The property page parameters
	void				**io_pShaderInstanceData		//! The shader instance data
);

/*! \page InitUI InitUI Callback Reference
	\code
	RTSHADER_API bool (*RTS_Shader3_InitUI)
	{
		IRTSExecutionState	*in_pExecState,
		void				*in_pParams,
		void				**io_pShaderInstanceData
	}
	\endcode
	The InitUI callback function is called when the shader connections change, or one of the specified
	parameters is changed. This function receives the execution state, the property page parameters,
	and the shader instance user data.

	The parameters that trigger a call to this callback are defined
	by returning an answer to the \ref GetRequirements "GetRequirements" function with the two requirement
	types: \c RTS_REQUIRE_PRIMARYINITUIGUID and \c RTS_REQUIRE_SECONDARYINITUIGUID.

	\param in_pExecState The execution state interface
	\param in_pParams The shader property page parameters
	\retval io_pShaderInstanceData Pointer to the shader's instance user data
	\return Success/failure
	\sa IRTSExecutionState, \ref RTS_Callbacks, \xt cus_rtshad_ExecutionFlow Execution Flow \endxt
*/
typedef 	RTSHADER_API bool (*RTS_Shader3_InitUI)
(
	IRTSExecutionState	*in_pExecState,						//! The execution state interface
	void				*in_pParams,						//! The property page parameters
	void				**io_pShaderInstanceData			//! The shader instance data
);

/*! \page Term Term Callback Reference
	\code
	RTSHADER_API bool (*RTS_Shader3_Term)
	{
		IRTSExecutionState	*in_pExecState,
		void				*in_pParams,
		void				**io_pShaderInstanceData
	}
	\endcode
	The Term callback enables the shader to clean up after itself (for example, shader instance data).
	\param in_pExecState The execution state interface
	\param in_pParams The shader property page parameters
	\retval io_pShaderInstanceData Pointer to the shader's instance user data
	\return Success/failure
	\sa IRTSExecutionState, \ref RTS_Callbacks, \xt cus_rtshad_ExecutionFlow Execution Flow \endxt
*/
typedef 	RTSHADER_API bool (*RTS_Shader3_Term)
(
	IRTSExecutionState	*in_pExecState,					//! The execution state interface
	void			*in_pParams,					//! The property page parameters
	void			**io_pShaderInstanceData			//! The shader instance data
);

/*! \page GetRequirements GetRequirements Callback Reference
	\code
	RTSHADER_API bool (*RTS_Shader3_GetRequirements)
	{
		IRTSExecutionState	*in_pExecState,
		void				*in_pParams,
		XSI_RTS_Primitive	*in_pGeom,
		void				**io_pShaderInstanceData,
		ULONG				in_lRequirement,
		ULONG				*out_pRequirementValue
	}
	\endcode
	Use this callback to set whether any of the requirements listed in the \link eXSI_RTS_RequirementType \endlink
	enum are required or not by returning true or false in the \c out_pRequirementValue parameter.
	\param in_pExecState The execution state interface
	\param in_pParams The shader property page parameters
	\param in_pGeom The geometry information
	\retval io_pShaderInstanceData Pointer to the shader's instance user data
	\param in_lRequirement The requirement identifier
	\retval out_pRequirementValue The returned requirement value
	\return Success/failure
	\sa IRTSExecutionState, \ref RTS_Callbacks, \xt cus_rtshad_ExecutionFlow Execution Flow \endxt
*/
typedef 	RTSHADER_API bool (*RTS_Shader3_GetRequirements)
(
	IRTSExecutionState	*in_pExecState,					//! The execution state interface
	void			*in_pParams,					//! The property page parameters
	XSI_RTS_Primitive	*in_pGeom,					//! The geometry information
	void			**io_pShaderInstanceData,			//! The shader instance data
	ULONG			in_lRequirement,				//! The requirement identifier
	ULONG			*out_pRequirementValue				//! The returned requirement value
);

/*! \page GetAttributeList GetAttributeList Callback Reference
	\code
	RTSHADER_API XSI_RTS_Attribute* (*RTS_Shader3_GetAttributeList)
	{
		IRTSExecutionState	*in_pExecState,
		void				*in_pParams,
		void				**io_pShaderInstanceData
	}
	\endcode
	Enables a shader to tell Softimage which attribute it needs in order to perform rendering. The attributes are
	returned as an array of _XSI_RTS_Attribute elements.

	The _XSI_RTS_Attribute structure works together with a set of helper functions to enable shaders to request
	any type of data on the mesh or point cloud to be used in rendering. Each attribute is defined by an
	_XSI_RTS_Attribute structure which holds the name of the attribute and optionally an enum indicating which
	hardware register will hold the data (only needed when using the rendering functions exposed by the
	IRTSExecutionState). Each shader must export the \ref GetAttributeList "GetAttributeList" callback which
	notifies Softimage of which attributes the shader needs.
	\param in_pExecState The execution state interface
	\param in_pParams The shader property page parameters
	\retval io_pShaderInstanceData Pointer to the shader's instance user data
	\return Array of _XSI_RTS_Attribute structures.
	\eg In this example, the Realtime Shader responds to the GetAttributeList call by first checking the value
		of a parameter on its property page. If the value of \c useColor is true, it tells Softimage that it needs the
		position, normal, 2 vertex colors and an attribute called \c Foobar to do its rendering. If it's false,
		it doesn't ask for vertex colors.
	\code
	XSI_RTS_Attribute __gAttributesWithColor [] =
	{
		XSI_RTS_ATTRIBUTE_POSITION,	ePOSITION,
		XSI_RTS_ATTRIBUTE_NORMAL,	eNORMAL,
		XSI_RTS_ATTRIBUTE_COLOR,	eCOLOR0,
		XSI_RTS_ATTRIBUTE_COLOR,	eCOLOR1,
		"Foobar",					eTEXCOORD0
	};

	XSI_RTS_Attribute __gAttributesWithoutColor [] =
	{
		XSI_RTS_ATTRIBUTE_POSITION,	ePOSITION,
		XSI_RTS_ATTRIBUTE_NORMAL,	eNORMAL,
		"Foobar",					eTEXCOORD0
	};

	struct ShaderPPG
	{
		bool useColor;
	};

	RTSHADER_API XSI_RTS_Attribute* MyShader_GetAttributeList
	(
		IRTSExecutionState	*in_pExecState,
		void				*in_pParams,
		void				**io_pInstanceData
	)
	{
		ShaderPPG* options = (ShaderPPG*)in_pParams;

		if (options->useColor)
		{
			return __gAttributesWithColor;
		} else {
			return __gAttributesWithoutColor;
		}
	}
	\endcode
	\sa IRTSExecutionState, \ref RTS_Callbacks, \xt cus_rtshad_GeometryData Geometry Data \endxt,
		\xt cus_rtshad_ExecutionFlow Execution Flow \endxt
	\since 7.0
*/
typedef 	RTSHADER_API XSI_RTS_Attribute* (*RTS_Shader3_GetAttributeList)
(
	IRTSExecutionState	*in_pExecState,					//! The execution state interface
	void				*in_pParams,					//! The property page parameters
	void				**io_pShaderInstanceData		//! The shader instance data);
);

/*! \page Execute Execute Callback Reference
	\code
	RTSHADER_API bool (*RTS_Shader3_Execute)
	{
		IRTSExecutionState			*in_pExecState,
		void						*in_pParams,
		XSI_RTS_Primitive			*in_pPrimitive,
		void						*in_pAttributes,
		XSI_RTS_Attribute_Size		*in_pAttributesSize,
		void						**io_pShaderInstanceData
	}
	\endcode
	Once the shader has responded to \ref GetAttributeList "GetAttributeList" with its list of attributes, Softimage will
	package the values for these attributes and will pass them to the \c Execute function along with an array describing
	each attribute's size and format. Note that if an attribute was not found or was not defined on the mesh or point
	cloud, Softimage will pass a null pointer.
	\note This callback is mandatory
	\param in_pExecState The execution state interface
	\param in_pParams The shader property page parameters
	\param in_pPrimitive The geometry information
	\param in_pAttributes The Softimage RTS Attribute data
	\param in_pAttributesSize The sizes of the attributes
	\param io_pShaderInstanceData Pointer to This shader instance user data
	\return Success/failure
	\eg This example builds on the one on the \ref GetAttributeList "GetAttributeList" page. Here's what the %Execute
		function might look like for the example shader described:
	\code
	RTSHADER_API bool MyShader_Execute
	(
		IRTSExecutionState		*in_pExecState,
		void					*in_pParams,
		XSI_RTS_Primitive		*in_pPrimitive,
		void					*in_pAttributes,
		eXSI_Attribute_Size		*in_pAttributesSize,
		void					**io_pInstanceData
	)
	{
		ShaderPPG* options = (ShaderPPG*)in_pParams;

		if (options->useColor)
		{
			float* pfPositions 	= ((float**)in_pAttributes)[0];
			float* pfNormals 	= ((float**)in_pAttributes)[1];
			float* pfColors0 	= ((float**)in_pAttributes)[2];
			float* pfColors1 	= ((float**)in_pAttributes)[3];
			float* pfFoobars 	= ((float**)in_pAttributes)[4];
			...
		} else {
			float* pfPositions 	= ((float**)in_pAttributes)[0];
			float* pfNormals 	= ((float**)in_pAttributes)[1];
			float* pfFoobars 	= ((float**)in_pAttributes)[2];
			...
		}

		...
	}
	\endcode
	\sa IRTSExecutionState, \ref RTS_Callbacks, \xt cus_rtshad_GeometryData Geometry Data \endxt,
		\xt cus_rtshad_ExecutionFlow Execution Flow \endxt
*/
typedef 	RTSHADER_API bool (*RTS_Shader3_Execute)
(
	IRTSExecutionState		*in_pExecState,					//! The execution state interface
	void					*in_pParams,					//! The property page parameters
	XSI_RTS_Primitive		*in_pPrimitive,					//! The geometry information
	void					*in_pAttributes,				//! The Softimage RTS Attribute data
	XSI_RTS_Attribute_Size	*in_pAttributesSize,			//! The sizes of the attributes
	void					**io_pShaderInstanceData		//! The shader instance data
);

/*! \class CRTSState XSI_rtshaders.h
	\brief The CRTSState object holds information about a state

	During the execution of a material, each shader is called sequentially. These shaders can then add their own
	\a states associated with custom data to the execution state list. These states can then be retrieved by
	shaders which are executed next in the material tree.

	\note The state list is automatically cleared by Softimage before the execution of the realtime shader tree is done.
	\sa IRTSExecutionState::GetStateList, CRTSStateList::RemoveState
	\since 7.0
 */
class CRTSState
{
public:
	/*! Default constructor
		\param in_szName	Name of state
		\param in_pData 	Data attached to the state
		\param in_ID	ID for state
		\sa CRTSState::GetName, CRTSState::GetData, CRTSState::GetID
	*/
	CRTSState(const char* in_szName, void* in_pData, unsigned long in_ID =0)
	{
		assert ( in_szName != NULL );
		m_szName = strdup ( in_szName );
		m_pData = in_pData ;
		m_bIsValid = true;
		m_ID = in_ID;
	}

	~CRTSState()
	{
		if ( m_szName )
		{
			free(m_szName);
			m_szName = NULL;
		}
	}

	/*! Returns whether the state is valid (\c m_bIsValid == true) or not.
		\return True if this state is valid; false otherwise
		\sa CRTSState::Validate, CRTSState::Invalidate
	*/
	bool	IsValid () { return m_bIsValid; };

	/*! Sets the valid flag for this state to true.
		\sa CRTSState::IsValid, CRTSState::Invalidate
	*/
	void	Validate() { m_bIsValid = true;};

	/*! Sets the valid flag for this state to false.
		\sa CRTSState::IsValid, CRTSState::Validate
	*/
	void	Invalidate() { m_bIsValid = false;};

	/*! Returns the state name.
		\return Name of the state
		\sa CRTSState::GetID
	*/
	const char*		GetName() { return m_szName; };

	/*! Returns the data attached to the state.
		\return A pointer to the data.
	*/
	void*			GetData() { return m_pData; };

	/*! Returns the state ID.
		\return ID of the state
		\sa CRTSState::GetName
	*/
	unsigned long	GetID() { return m_ID; };

private:
	unsigned long 	m_ID;
	char*			m_szName;
	void*			m_pData;
	bool			m_bIsValid;
};


/*! \class CRTSStateList
	\brief The CRTSStateList class holds information about a list of shader states.

	This class represents a collection of CRTSState objects.
	\sa CRTSState, IExecuteState, IRTSExecutionState::GetStateList
	\since 7.0
*/
class CRTSStateList
{
public:
	CRTSStateList() {};
	~CRTSStateList()
	{
		for (int a=0;a<m_Array.GetUsed();a++)
		{
			delete m_Array[a];
		}

		m_Array.DisposeData();
	}

	/*! Returns the number of states in the list.
		\return Size of this %CRTSStateList.
	*/
	int		GetNbStates ()
	{
		return m_Array.GetUsed();
	}

	/*! Returns the state object at the specified index in the list.
		\param in_Idx Index at which to retrieve the state object.
		\return A pointer to the CRTSState object
		\sa CRTSStateList::GetStateByName, CRTSStateList::GetStateByID, CRTSStateList::GetNbStates
	*/
	CRTSState*	GetState ( unsigned int in_Idx )
	{
		assert ( (int)in_Idx < m_Array.GetUsed() );
		return m_Array[in_Idx];
	}

	/*! Returns the state object matching the specified name.
		\param in_szName Name of state object to retrieve
		\return A pointer to the CRTSState object
		\sa CRTSStateList::GetState, CRTSStateList::GetStateByID, CRTSState::GetName
	*/
	CRTSState* GetStateByName( const char* in_szName )
	{
		for (int a=0;a<m_Array.GetUsed();a++)
		{
			if ( !strcmp ( in_szName, m_Array[a]->GetName()) )
				return m_Array[a];
		}

		return NULL;
	}

	/*! Returns the state object matching the specified ID.
		\param in_ID ID of state object to retrieve
		\return A pointer to the CRTSState object
		\sa CRTSStateList::GetState, CRTSStateList::GetStateByName, CRTSState::GetID
	*/
	CRTSState* GetStateByID( unsigned long  in_ID )
	{
		for (int a=0;a<m_Array.GetUsed();a++)
		{
			if ( in_ID == m_Array[a]->GetID() )
				return m_Array[a];
		}

		return NULL;
	}

	/*! Adds a new state to the list.
		\param in_szName Name for the new state
		\param in_pData Pointer to the data to attach
		\param in_ID ID for the new state
		\return A pointer to the newly created CRTSState object
		\sa CRTSStateList::RemoveState
	*/
	CRTSState* AddState( const char* in_szName, void* in_pData, unsigned long in_ID = 0 )
	{
		assert ( in_szName != NULL );
		CRTSState* l_pNewState = new CRTSState(in_szName,in_pData, in_ID);
		m_Array.Add ( l_pNewState );
		return l_pNewState;
	}

	/*! Removes a state from the list.
		\param in_pState Pointer to the state to remove
		\sa CRTSStateList::AddState
	*/
	void RemoveState ( CRTSState* in_pState )
	{
		assert ( in_pState != NULL );
		for (int a=0;a<m_Array.GetUsed();a++)
		{
			if ( m_Array[a] == in_pState )
			{
				delete m_Array[a];
				m_Array.DeleteAt ( a ,1);
				m_Array.Pack();
				break;
			}
		}
	}

private:
	CSIBCArray<CRTSState*>	m_Array;
};

//*****************************************************************************
/*! \class IRTSExecutionState XSI_rtshaders.h
	\brief The IRTSExecutionState object offers several methods to access various objects during a call
	to real-time shaders.

	You can use this object to access the following scene data (the pointer will be cached and returned to you):
	\li the current \xc Camera object (see IRTSExecutionState::GetCamera)
	\li the \xc Material (see IRTSExecutionState::GetMaterial)
	\li the \xc Shader (see IRTSExecutionState::GetShader) and its parameters (IRTSExecutionState::GetShaderParameters)

	You can also use this object to:
	\li access the legacy tagXSI_RTS_SystemParams object (see IRTSExecutionState::GetSystemParams)
	\li manage uniform parameters for vertex and fragment shaders (IRTSExecutionState::DefineUniform,
		IRTSExecutionState::ClearUniforms, IRTSExecutionState::GetUniformList, etc.)
	\li render geometry during a real-time shader call using either OpenGL or DirectX (see IRTSExecutionState::GetChannel,
		IRTSExecutionState::DrawGeometry)
	\li raise errors and warnings back to Softimage

	\note You cannot instantiate a IRTSExecutionState object directly. You can access an instance via one of
		the \ref RTS_Callbacks functions.

	\sa tagXSI_RTS_SystemParams, CRTSStateList, XSI_RTS_Uniform, eGraphicsAPI, tagXSI_RTS_Primitive, _XSI_RTS_Attribute,
		\ref RTS_Callbacks, \xt cus_rtshad_ExecutionFlow Execution Flow \endxt
	\since 7.0
 */
//*****************************************************************************
class IRTSExecutionState
{
public:

	/*! Returns a pointer to the legacy system parameters.
		\return A pointer to the tagXSI_RTS_SystemParams structure
	*/
	virtual XSI_RTS_SystemParams*	GetSystemParams() = 0;

	/*! Returns the list of executions states
		\return A pointer to the CRTSStateList structure
		\sa CRTSState
	*/
	virtual CRTSStateList*			GetStateList() = 0 ;

	/*! Returns a pointer to the SDK shader object.
		\return A pointer to the \xc Shader object
		\sa IRTSExecutionState::GetShaderParameters
	*/
	virtual void*					GetShader()								= 0;

	/*! Returns a pointer to the user data attached to this shader instance.
		\return A pointer to the shader instance data
		\sa IRTSExecutionState::SetShaderInstanceData
	*/
	virtual void*					GetShaderInstanceData()					= 0;

	/*! Attaches user data to this instance of the shader.
		\param in_pData A pointer to the shader instance data
		\sa IRTSExecutionState::GetShaderInstanceData
	*/
	virtual void					SetShaderInstanceData( void* in_pData ) = 0;

	/*! Returns a pointer to the shader parameters (ie. the PPG values)
		\return A pointer to the \xc Parameter objects
		\sa IRTSExecutionState::GetShader
	*/
	virtual void*					GetShaderParameters()					= 0;

	/*! Returns a unique identifier for this instance of the shader
		\return The shader ID
	*/
	virtual long					GetShaderUniqueID()						= 0;

	/*! Returns the \xc RenderChannel information associated to the specified \xc Framebuffer object.
		\param in_iBuffer Index of the \xc Framebuffer object. If not specified, the current buffer will be used.
		\return A value corresponding to one of the \link eChannel enum values \endlink
	*/
	virtual eChannel				GetChannel(int in_iBuffer) = 0 ;

	/*! Returns a pointer to the SDK material object.
		\return A pointer to the \xc Material object
	*/
	virtual void*					GetMaterial()	= 0;

	/*! Returns a pointer to the SDK primitive object.
		\return A pointer to the \xc X3DObject object
	*/
	virtual void*					GetPrimitive()	= 0;

	/*! Returns a pointer to the current SDK camera object
		\return A pointer to the \xc Camera object
	*/
	virtual void*					GetCamera()		= 0;

	/*! Defines a single uniform parameter to be used in the Realtime Shader chain.
		\param in_eType	Type of the uniform parameter
		\param in_szName	Name of the uniform parameter
		\param in_uiSize	Size of the uniform parameter
		\param in_pData	Pointer to the data for the uniform parameter
		\return Success/failure
		\sa XSI_RTS_Uniform, IRTSExecutionState::ClearUniforms, IRTSExecutionState::GetNbUniforms, IRTSExecutionState::GetUniformList
	*/
	virtual bool					DefineUniform (  XSI_RTS_Uniform::eUniformType in_eType, const char* in_szName, unsigned int in_uiSize, void* in_pData ) = 0;


	/*! Removes all uniform parameters defined for this Realtime Shader chain.
		\return Success/failure
		\sa XSI_RTS_Uniform, IRTSExecutionState::DefineUniform, IRTSExecutionState::GetNbUniforms, IRTSExecutionState::GetUniformList
	*/
	virtual bool					ClearUniforms () = 0;

	/*! Returns the number of uniform parameters defined for this Realtime Shader chain.
		\return Size of uniform parameter list
		\sa XSI_RTS_Uniform, IRTSExecutionState::DefineUniform, IRTSExecutionState::ClearUniforms, IRTSExecutionState::GetUniformList
	*/
	virtual	unsigned long			GetNbUniforms () = 0;

	/*! Returns the array of uniform parameters defined for this Realtime Shader chain.
		\return A pointer to the list of uniform parameters
		\sa XSI_RTS_Uniform, IRTSExecutionState::DefineUniform, IRTSExecutionState::ClearUniforms, IRTSExecutionState::GetUniformList
	*/
	virtual XSI_RTS_Uniform**		GetUniformList () = 0;

	/*! Draws the geometry using a list of attributes. You may explicitly suggest a graphics API to use for
		rendering (OpenGL20, OpenGL30, DirectX10); however, if the current viewport mode does not match your
		request, no rendering will occur.

		\tip To avoid this and to be certain that your rendering call will succeed, you may use the enum value
			::Any. This tells Softimage to use the viewport's current driver to render the geometry.

		\param in_eDriver		The graphics API to use for rendering
		\param in_pGeometry		Pointer to the geometry to draw
		\param in_pAttributes	Pointer to the attributes to use
		\param in_pAttribData	Pointer to the attribute data
		\param in_pAttributesSize	Pointer to the size of the attributes
		\return Success/failure
		\sa ::eGraphicsAPI, tagXSI_RTS_Primitive, _XSI_RTS_Attribute, eXSI_Attribute_Size,
			\xt cus_rtshad_GeometryData Geometry Data \endxt
	*/
	virtual bool DrawGeometry ( XSI::siGraphicDriver in_eDriver,
				    XSI_RTS_Primitive		*in_pGeometry,
				    XSI_RTS_Attribute 		*in_pAttributes,
				    void*			in_pAttribData,
				    XSI_RTS_Attribute_Size	*in_pAttributesSize) = 0;

	/*! Draws the geometry using a custom mapping of attributes to hardware registers.

		\tip To avoid this and to be certain that your rendering call will succeed, you may use the enum value
		::Any. This tells Softimage to use the viewport's current driver to render the geometry.

		\param in_eAPI		The graphics API to use for rendering
		\param in_pGeometry		Pointer to the geometry to draw
		\param in_szMapping		Custom mapping to use
		\param in_pAttribData	Pointer to the attribute data
		\param in_pAttributesSize	Pointer to the size of the attributes
		\return Success/failure
		\sa ::eGraphicsAPI, tagXSI_RTS_Primitive, eXSI_Attribute_Size, \xt cus_rtshad_GeometryData Geometry Data \endxt
	*/
	virtual	bool DrawGeometry ( XSI::siGraphicDriver in_eDriver,
				    XSI_RTS_Primitive		*in_pGeometry,
				    const char* 		in_szMapping,
				    void*			in_pAttribData,
				    XSI_RTS_Attribute_Size	*in_pAttributesSize) = 0;

	/*! Returns a list of attributes specified in the mapping.
		\param in_szMapping		Custom mapping to use
		\return A pointer to the attributes list
		\sa eGraphicsAPI, _XSI_RTS_Attribute
	*/
	virtual XSI_RTS_Attribute* GetAttributeDescriptorFromMapping( const char* in_szMapping ) = 0;

	/*! Notifies Softimage to raise an error.
		\param in_szError		The error message to display
		\param in_eErrorType	The severity of the error to raise (similar to
		\sa eErrorType
	*/
	virtual void RaiseError( const char* in_szError, eErrorType in_eErrorType) = 0;

	/*! Notifies Softimage to raise an error. Use this function to define a parameter
		\param in_szError		The error message to display
		\param in_eErrorType	The severity of the error to raise (similar to
		\param in_Parameter		??
		\param in_lData		??
		\sa \link eErrorType \endlink
	*/
	virtual void RaiseError( const char* in_szError, eErrorType in_eErrorType, int in_Parameter, ULONG_PTR in_lData ) = 0;

	/*! Saves all states (currently only vertex and fragment shaders)
		\sa IRTSExecutionState::PopExecutionState
	*/
	virtual void PushExecutionState() = 0;

	/*! Restores previously pushed states (currently only vertex and fragment shaders)
		\sa IRTSExecutionState::PushExecutionState
	*/
	virtual void PopExecutionState	() = 0;

	/*! Returns an interface to the specified graphics. API as follows:
		\param in_eAPI The graphics API to use for rendering
		\return for OpenGL, it returns a pointer to the main HGLRC
		\return for DirectX_9, it returns a pointer to a IDirect3DDevice9
		\return for DirectX_10, it returns a pointer to a ID3D10Device
		\sa ::eGraphicsAPI
	*/
	virtual void* GetGraphicsAPI(XSI::siGraphicDriver in_eDriver) = 0;


	/*! Returns the current render mode
		\return the render mode
		\sa ::eRenderMode
		\since 7.0
	*/
	virtual eRenderMode GetRenderMode() = 0;
};

#pragma pack(pop)

#endif // XSI_RTSHADERS_H
