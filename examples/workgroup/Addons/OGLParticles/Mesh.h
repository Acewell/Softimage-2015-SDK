//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

#ifndef OGL_PARTICLES_MESH_H
#define OGL_PARTICLES_MESH_H

/////////////////////////////////////////////////////////////////
//
// [pzion 20080604] EVIL HACK WARNING
//
// This is to avoid a symbol name conflict on Linux64
// Without this, the Linux64 shared library loader binds the
// constructor/destructor to those of another class called Mesh

#define Mesh OGLParticlesMesh

/////////////////////////////////////////////////////////////////

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>

#define __CSISTATMANAGER_H__
#define __DONTINCLUDSISTRING_HACKHACK__

#include <XSI_rtshaders.h>
#include "OGLParticle.h"
#include <vector>

typedef ptrdiff_t GLsizeiptrARB;
typedef ptrdiff_t GLintptrARB;

#define GL_RGBA32F_ARB 0x8814
#define GL_RGB32F_ARB 0x8815
#define GL_ALPHA32F_ARB 0x8816
#define GL_INTENSITY32F_ARB 0x8817
#define GL_LUMINANCE32F_ARB 0x8818
#define GL_LUMINANCE_ALPHA32F_ARB 0x8819
#define GL_RGBA16F_ARB 0x881A
#define GL_RGB16F_ARB 0x881B
#define GL_ALPHA16F_ARB 0x881C
#define GL_INTENSITY16F_ARB 0x881D
#define GL_LUMINANCE16F_ARB 0x881E
#define GL_LUMINANCE_ALPHA16F_ARB 0x881F
#define GL_TEXTURE_RED_TYPE_ARB 0x8C10
#define GL_TEXTURE_GREEN_TYPE_ARB 0x8C11
#define GL_TEXTURE_BLUE_TYPE_ARB 0x8C12
#define GL_TEXTURE_ALPHA_TYPE_ARB 0x8C13
#define GL_TEXTURE_LUMINANCE_TYPE_ARB 0x8C14
#define GL_TEXTURE_INTENSITY_TYPE_ARB 0x8C15
#define GL_TEXTURE_DEPTH_TYPE_ARB 0x8C16
#define GL_UNSIGNED_NORMALIZED_ARB 0x8C17

// FBO Stuff
#define GL_INVALID_FRAMEBUFFER_OPERATION_EXT 0x0506
#define GL_MAX_RENDERBUFFER_SIZE_EXT 0x84E8
#define GL_FRAMEBUFFER_BINDING_EXT 0x8CA6
#define GL_RENDERBUFFER_BINDING_EXT 0x8CA7
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_EXT 0x8CD0
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_EXT 0x8CD1
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_EXT 0x8CD2
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_EXT 0x8CD3
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET_EXT 0x8CD4
#define GL_FRAMEBUFFER_COMPLETE_EXT 0x8CD5
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT 0x8CD6
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT 0x8CD7
#define GL_FRAMEBUFFER_INCOMPLETE_DUPLICATE_ATTACHMENT_EXT 0x8CD8
#define GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT 0x8CD9
#define GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT 0x8CDA
#define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT 0x8CDB
#define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT 0x8CDC
#define GL_FRAMEBUFFER_UNSUPPORTED_EXT 0x8CDD
#define GL_FRAMEBUFFER_STATUS_ERROR_EXT 0x8CDE
#define GL_MAX_COLOR_ATTACHMENTS_EXT 0x8CDF
#define GL_COLOR_ATTACHMENT0_EXT 0x8CE0
#define GL_COLOR_ATTACHMENT1_EXT 0x8CE1
#define GL_COLOR_ATTACHMENT2_EXT 0x8CE2
#define GL_COLOR_ATTACHMENT3_EXT 0x8CE3
#define GL_COLOR_ATTACHMENT4_EXT 0x8CE4
#define GL_COLOR_ATTACHMENT5_EXT 0x8CE5
#define GL_COLOR_ATTACHMENT6_EXT 0x8CE6
#define GL_COLOR_ATTACHMENT7_EXT 0x8CE7
#define GL_COLOR_ATTACHMENT8_EXT 0x8CE8
#define GL_COLOR_ATTACHMENT9_EXT 0x8CE9
#define GL_COLOR_ATTACHMENT10_EXT 0x8CEA
#define GL_COLOR_ATTACHMENT11_EXT 0x8CEB
#define GL_COLOR_ATTACHMENT12_EXT 0x8CEC
#define GL_COLOR_ATTACHMENT13_EXT 0x8CED
#define GL_COLOR_ATTACHMENT14_EXT 0x8CEE
#define GL_COLOR_ATTACHMENT15_EXT 0x8CEF
#define GL_DEPTH_ATTACHMENT_EXT 0x8D00
#define GL_STENCIL_ATTACHMENT_EXT 0x8D20
#define GL_FRAMEBUFFER_EXT 0x8D40
#define GL_RENDERBUFFER_EXT 0x8D41
#define GL_RENDERBUFFER_WIDTH_EXT 0x8D42
#define GL_RENDERBUFFER_HEIGHT_EXT 0x8D43
#define GL_RENDERBUFFER_INTERNAL_FORMAT_EXT 0x8D44
#define GL_STENCIL_INDEX_EXT 0x8D45
#define GL_STENCIL_INDEX1_EXT 0x8D46
#define GL_STENCIL_INDEX4_EXT 0x8D47
#define GL_STENCIL_INDEX8_EXT 0x8D48
#define GL_STENCIL_INDEX16_EXT 0x8D49

// PBO stuff
#define GL_PIXEL_PACK_BUFFER_ARB 0x88EB
#define GL_PIXEL_UNPACK_BUFFER_ARB 0x88EC
#define GL_PIXEL_PACK_BUFFER_BINDING_ARB 0x88ED
#define GL_PIXEL_UNPACK_BUFFER_BINDING_ARB 0x88EF

// VBO stuff
#define GL_BUFFER_SIZE_ARB 0x8764
#define GL_BUFFER_USAGE_ARB 0x8765
#define GL_ARRAY_BUFFER_ARB 0x8892
#define GL_ELEMENT_ARRAY_BUFFER_ARB 0x8893
#define GL_ARRAY_BUFFER_BINDING_ARB 0x8894
#define GL_ELEMENT_ARRAY_BUFFER_BINDING_ARB 0x8895
#define GL_VERTEX_ARRAY_BUFFER_BINDING_ARB 0x8896
#define GL_NORMAL_ARRAY_BUFFER_BINDING_ARB 0x8897
#define GL_COLOR_ARRAY_BUFFER_BINDING_ARB 0x8898
#define GL_INDEX_ARRAY_BUFFER_BINDING_ARB 0x8899
#define GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING_ARB 0x889A
#define GL_EDGE_FLAG_ARRAY_BUFFER_BINDING_ARB 0x889B
#define GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING_ARB 0x889C
#define GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING_ARB 0x889D
#define GL_WEIGHT_ARRAY_BUFFER_BINDING_ARB 0x889E
#define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING_ARB 0x889F
#define GL_READ_ONLY_ARB 0x88B8
#define GL_WRITE_ONLY_ARB 0x88B9
#define GL_READ_WRITE_ARB 0x88BA
#define GL_BUFFER_ACCESS_ARB 0x88BB
#define GL_BUFFER_MAPPED_ARB 0x88BC
#define GL_BUFFER_MAP_POINTER_ARB 0x88BD
#define GL_STREAM_DRAW_ARB 0x88E0
#define GL_STREAM_READ_ARB 0x88E1
#define GL_STREAM_COPY_ARB 0x88E2
#define GL_STATIC_DRAW_ARB 0x88E4
#define GL_STATIC_READ_ARB 0x88E5
#define GL_STATIC_COPY_ARB 0x88E6
#define GL_DYNAMIC_DRAW_ARB 0x88E8
#define GL_DYNAMIC_READ_ARB 0x88E9
#define GL_DYNAMIC_COPY_ARB 0x88EA

typedef void (APIENTRY * PFNGLBINDBUFFERARBPROC) (GLenum target, GLuint buffer);
typedef void (APIENTRY * PFNGLBUFFERDATAARBPROC) (GLenum target, GLsizeiptrARB size, const GLvoid* data, GLenum usage);
typedef void (APIENTRY * PFNGLBUFFERSUBDATAARBPROC) (GLenum target, GLintptrARB offset, GLsizeiptrARB size, const GLvoid* data);
typedef void (APIENTRY * PFNGLDELETEBUFFERSARBPROC) (GLsizei n, const GLuint* buffers);
typedef void (APIENTRY * PFNGLGENBUFFERSARBPROC) (GLsizei n, GLuint* buffers);
typedef void (APIENTRY * PFNGLGETBUFFERPARAMETERIVARBPROC) (GLenum target, GLenum pname, GLint* params);
typedef void (APIENTRY * PFNGLGETBUFFERPOINTERVARBPROC) (GLenum target, GLenum pname, GLvoid** params);
typedef void (APIENTRY * PFNGLGETBUFFERSUBDATAARBPROC) (GLenum target, GLintptrARB offset, GLsizeiptrARB size, GLvoid* data);
typedef GLboolean (APIENTRY * PFNGLISBUFFERARBPROC) (GLuint buffer);
typedef GLvoid * (APIENTRY * PFNGLMAPBUFFERARBPROC) (GLenum target, GLenum access);
typedef GLboolean (APIENTRY * PFNGLUNMAPBUFFERARBPROC) (GLenum target);

typedef void (APIENTRY * PFNGLDRAWBUFFERSARBPROC) (GLsizei n, const GLenum* bufs);
typedef void (APIENTRY * PFNGLACTIVETEXTUREARBPROC) (GLenum texture);
typedef void (APIENTRY * PFNGLBINDFRAMEBUFFEREXTPROC) (GLenum target, GLuint framebuffer);
typedef void (APIENTRY * PFNGLBINDRENDERBUFFEREXTPROC) (GLenum target, GLuint renderbuffer);
typedef GLenum (APIENTRY * PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC) (GLenum target);
typedef void (APIENTRY * PFNGLDELETEFRAMEBUFFERSEXTPROC) (GLsizei n, const GLuint* framebuffers);
typedef void (APIENTRY * PFNGLDELETERENDERBUFFERSEXTPROC) (GLsizei n, const GLuint* renderbuffers);
typedef void (APIENTRY * PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (APIENTRY * PFNGLFRAMEBUFFERTEXTURE1DEXTPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (APIENTRY * PFNGLFRAMEBUFFERTEXTURE2DEXTPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (APIENTRY * PFNGLFRAMEBUFFERTEXTURE3DEXTPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
typedef void (APIENTRY * PFNGLGENFRAMEBUFFERSEXTPROC) (GLsizei n, GLuint* framebuffers);
typedef void (APIENTRY * PFNGLGENRENDERBUFFERSEXTPROC) (GLsizei n, GLuint* renderbuffers);
typedef void (APIENTRY * PFNGLGENERATEMIPMAPEXTPROC) (GLenum target);
typedef void (APIENTRY * PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC) (GLenum target, GLenum attachment, GLenum pname, GLint* params);
typedef void (APIENTRY * PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC) (GLenum target, GLenum pname, GLint* params);
typedef GLboolean (APIENTRY * PFNGLISFRAMEBUFFEREXTPROC) (GLuint framebuffer);
typedef GLboolean (APIENTRY * PFNGLISRENDERBUFFEREXTPROC) (GLuint renderbuffer);
typedef void (APIENTRY * PFNGLRENDERBUFFERSTORAGEEXTPROC) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRY * PFNGLCLIENTACTIVETEXTUREPROC) (GLenum texture);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1DPROC) (GLenum target, GLdouble s);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1DVPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1FPROC) (GLenum target, GLfloat s);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1FVPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1IPROC) (GLenum target, GLint s);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1IVPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1SPROC) (GLenum target, GLshort s);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1SVPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2DPROC) (GLenum target, GLdouble s, GLdouble t);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2DVPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2FPROC) (GLenum target, GLfloat s, GLfloat t);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2FVPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2IPROC) (GLenum target, GLint s, GLint t);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2IVPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2SPROC) (GLenum target, GLshort s, GLshort t);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2SVPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3DPROC) (GLenum target, GLdouble s, GLdouble t, GLdouble r);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3DVPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3FPROC) (GLenum target, GLfloat s, GLfloat t, GLfloat r);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3FVPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3IPROC) (GLenum target, GLint s, GLint t, GLint r);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3IVPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3SPROC) (GLenum target, GLshort s, GLshort t, GLshort r);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3SVPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4DPROC) (GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4DVPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4FPROC) (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4FVPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4IPROC) (GLenum target, GLint s, GLint t, GLint r, GLint q);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4IVPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4SPROC) (GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4SVPROC) (GLenum target, const GLshort *v);


struct Triangle {
	unsigned short i[3];
};

struct Vec3 {
	double p[3];
};
struct Vec2 {
	double p[2];
};

struct Vertex
{
	float mPosition[3];
	float mNormal[3];
	float mTextureCoord0[2];
};

class Mesh
{
public:
	Mesh(void);
	~Mesh(void);


	std::vector<Vertex>         mVertices;
	std::vector<unsigned short> mIndices;
	unsigned int                mVerticesVBO;
	unsigned int                mIndicesVBO;
	unsigned int                mTexture0;

	virtual void render(LONG id, LONG iLayoutType) const;
	virtual void setState(OGLParticleAttributeData* in_pAttributes) const;
	int  triangleCount(void) const;
	virtual void unsetState(OGLParticleAttributeData* in_pAttributes) const;

	static PFNGLBINDFRAMEBUFFEREXTPROC			glBindFramebufferEXT;
	static PFNGLBINDRENDERBUFFEREXTPROC			glBindRenderbufferEXT;
	static PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC	glCheckFramebufferStatusEXT ;
	static PFNGLDELETEFRAMEBUFFERSEXTPROC		glDeleteFramebuffersEXT ;
	static PFNGLDELETERENDERBUFFERSEXTPROC		glDeleteRenderbuffersEXT;
	static PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC	glFramebufferRenderbufferEXT ;
	static PFNGLFRAMEBUFFERTEXTURE1DEXTPROC		glFramebufferTexture1DEXT ;
	static PFNGLFRAMEBUFFERTEXTURE2DEXTPROC		glFramebufferTexture2DEXT ;
	static PFNGLFRAMEBUFFERTEXTURE3DEXTPROC		glFramebufferTexture3DEXT ;
	static PFNGLGENFRAMEBUFFERSEXTPROC			glGenFramebuffersEXT;
	static PFNGLGENRENDERBUFFERSEXTPROC			glGenRenderbuffersEXT;
	static PFNGLGENERATEMIPMAPEXTPROC			glGenerateMipmapEXT ;
	static PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC	glGetFramebufferAttachmentParameterivEXT;
	static PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC			glGetRenderbufferParameterivEXT ;
	static PFNGLISFRAMEBUFFEREXTPROC						glIsFramebufferEXT;
	static PFNGLISRENDERBUFFEREXTPROC						glIsRenderbufferEXT ;
	static PFNGLRENDERBUFFERSTORAGEEXTPROC					glRenderbufferStorageEXT;
	static PFNGLDRAWBUFFERSARBPROC	glDrawBuffers;
	static PFNGLACTIVETEXTUREARBPROC glActiveTexture;
	static PFNGLMULTITEXCOORD2FPROC glMultiTexCoord2f;
	static PFNGLMULTITEXCOORD3FPROC glMultiTexCoord3f;
	static PFNGLMULTITEXCOORD4FPROC glMultiTexCoord4f;
	static PFNGLMULTITEXCOORD2FVPROC glMultiTexCoord2fv;
	static PFNGLMULTITEXCOORD3FVPROC glMultiTexCoord3fv;
	static PFNGLMULTITEXCOORD4FVPROC glMultiTexCoord4fv;
	static PFNGLBINDBUFFERARBPROC glBindBufferARB ;
	static PFNGLBUFFERDATAARBPROC glBufferDataARB ;
	static PFNGLBUFFERSUBDATAARBPROC glBufferSubDataARB ;
	static PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;
	static PFNGLGENBUFFERSARBPROC glGenBuffersARB;
	static PFNGLGETBUFFERPARAMETERIVARBPROC glGetBufferParameterivARB ;
	static PFNGLGETBUFFERPOINTERVARBPROC glGetBufferPointervARB ;
	static PFNGLGETBUFFERSUBDATAARBPROC glGetBufferSubDataARB ;
	static PFNGLISBUFFERARBPROC glIsBufferARB ;
	static PFNGLMAPBUFFERARBPROC glMapBufferARB ;
	static PFNGLUNMAPBUFFERARBPROC glUnmapBufferARB ;

protected:
	void UploadVBO();
	static bool sUseVBO;

};

#endif
