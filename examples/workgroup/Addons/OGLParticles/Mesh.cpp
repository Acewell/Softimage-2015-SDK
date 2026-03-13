//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

#if defined(_WIN32)
#  include <windows.h>
#endif


#include "Mesh.h"

#include <assert.h>

#ifdef unix
#include <GL/glx.h>
#define XSI_BIND_FUNC(x,y,z)	x = (y) glXGetProcAddressARB((const GLubyte*)(z))
#else
#define XSI_BIND_FUNC(x,y,z)	x = (y) wglGetProcAddress(z)
#endif

PFNGLBINDFRAMEBUFFEREXTPROC Mesh::glBindFramebufferEXT = NULL;
PFNGLBINDRENDERBUFFEREXTPROC Mesh::glBindRenderbufferEXT = NULL;
PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC Mesh::glCheckFramebufferStatusEXT  = NULL;
PFNGLDELETEFRAMEBUFFERSEXTPROC Mesh::glDeleteFramebuffersEXT  = NULL;
PFNGLDELETERENDERBUFFERSEXTPROC Mesh::glDeleteRenderbuffersEXT = NULL;
PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC Mesh::glFramebufferRenderbufferEXT  = NULL;
PFNGLFRAMEBUFFERTEXTURE1DEXTPROC Mesh::glFramebufferTexture1DEXT  = NULL;
PFNGLFRAMEBUFFERTEXTURE2DEXTPROC Mesh::glFramebufferTexture2DEXT  = NULL;
PFNGLFRAMEBUFFERTEXTURE3DEXTPROC Mesh::glFramebufferTexture3DEXT  = NULL;
PFNGLGENFRAMEBUFFERSEXTPROC Mesh::glGenFramebuffersEXT = NULL;
PFNGLGENRENDERBUFFERSEXTPROC Mesh::glGenRenderbuffersEXT = NULL;
PFNGLGENERATEMIPMAPEXTPROC Mesh::glGenerateMipmapEXT  = NULL;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC Mesh::glGetFramebufferAttachmentParameterivEXT = NULL;
PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC Mesh::glGetRenderbufferParameterivEXT  = NULL;
PFNGLISFRAMEBUFFEREXTPROC Mesh::glIsFramebufferEXT = NULL;
PFNGLISRENDERBUFFEREXTPROC Mesh::glIsRenderbufferEXT  = NULL;
PFNGLRENDERBUFFERSTORAGEEXTPROC Mesh::glRenderbufferStorageEXT = NULL;
PFNGLDRAWBUFFERSARBPROC	Mesh::glDrawBuffers = NULL;
PFNGLACTIVETEXTUREARBPROC Mesh::glActiveTexture = NULL;
PFNGLMULTITEXCOORD2FPROC Mesh::glMultiTexCoord2f = NULL;
PFNGLMULTITEXCOORD3FPROC Mesh::glMultiTexCoord3f = NULL;
PFNGLMULTITEXCOORD4FPROC Mesh::glMultiTexCoord4f = NULL;
PFNGLMULTITEXCOORD2FVPROC Mesh::glMultiTexCoord2fv = NULL;
PFNGLMULTITEXCOORD3FVPROC Mesh::glMultiTexCoord3fv = NULL;
PFNGLMULTITEXCOORD4FVPROC Mesh::glMultiTexCoord4fv = NULL;

PFNGLBINDBUFFERARBPROC Mesh::glBindBufferARB  = NULL;
PFNGLBUFFERDATAARBPROC Mesh::glBufferDataARB  = NULL;
PFNGLBUFFERSUBDATAARBPROC Mesh::glBufferSubDataARB  = NULL;
PFNGLDELETEBUFFERSARBPROC Mesh::glDeleteBuffersARB = NULL;
PFNGLGENBUFFERSARBPROC Mesh::glGenBuffersARB = NULL;
PFNGLGETBUFFERPARAMETERIVARBPROC Mesh::glGetBufferParameterivARB  = NULL;
PFNGLGETBUFFERPOINTERVARBPROC Mesh::glGetBufferPointervARB  = NULL;
PFNGLGETBUFFERSUBDATAARBPROC Mesh::glGetBufferSubDataARB  = NULL;
PFNGLISBUFFERARBPROC Mesh::glIsBufferARB  = NULL;
PFNGLMAPBUFFERARBPROC Mesh::glMapBufferARB  = NULL;
PFNGLUNMAPBUFFERARBPROC Mesh::glUnmapBufferARB  = NULL;

bool Mesh::sUseVBO = false;

Mesh::Mesh(void)
{
  mVerticesVBO = 0;
  mIndicesVBO = 0;
  mTexture0 = 0;

  XSI_BIND_FUNC( glActiveTexture,PFNGLACTIVETEXTUREARBPROC, "glActiveTextureARB");
	XSI_BIND_FUNC( glBindFramebufferEXT, PFNGLBINDFRAMEBUFFEREXTPROC, "glBindFramebufferEXT");
	XSI_BIND_FUNC( glBindRenderbufferEXT, PFNGLBINDRENDERBUFFEREXTPROC, "glBindRenderbufferEXT");
	XSI_BIND_FUNC( glCheckFramebufferStatusEXT , PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC, "glCheckFramebufferStatusEXT");
	XSI_BIND_FUNC( glDeleteFramebuffersEXT , PFNGLDELETEFRAMEBUFFERSEXTPROC, "glDeleteFramebuffersEXT");
	XSI_BIND_FUNC( glDeleteRenderbuffersEXT, PFNGLDELETERENDERBUFFERSEXTPROC, "glDeleteRenderbuffersEXT");
	XSI_BIND_FUNC( glFramebufferRenderbufferEXT , PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC, "glFramebufferRenderbufferEXT");
	XSI_BIND_FUNC( glFramebufferTexture1DEXT , PFNGLFRAMEBUFFERTEXTURE1DEXTPROC, "glFramebufferTexture1DEXT");
	XSI_BIND_FUNC( glFramebufferTexture2DEXT , PFNGLFRAMEBUFFERTEXTURE2DEXTPROC, "glFramebufferTexture2DEXT");
	XSI_BIND_FUNC( glFramebufferTexture3DEXT , PFNGLFRAMEBUFFERTEXTURE3DEXTPROC, "glFramebufferTexture3DEXT");
	XSI_BIND_FUNC( glGenFramebuffersEXT, PFNGLGENFRAMEBUFFERSEXTPROC, "glGenFramebuffersEXT");
	XSI_BIND_FUNC( glGenRenderbuffersEXT, PFNGLGENRENDERBUFFERSEXTPROC, "glGenRenderbuffersEXT");
	XSI_BIND_FUNC( glGenerateMipmapEXT , PFNGLGENERATEMIPMAPEXTPROC, "glGenerateMipmapEXT");
	XSI_BIND_FUNC( glGetFramebufferAttachmentParameterivEXT, PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC, "glGetFramebufferAttachmentParameterivEXT");
	XSI_BIND_FUNC( glGetRenderbufferParameterivEXT , PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC, "glGetRenderbufferParameterivEXT");
	XSI_BIND_FUNC( glIsFramebufferEXT, PFNGLISFRAMEBUFFEREXTPROC, "glIsFramebufferEXT");
	XSI_BIND_FUNC( glIsRenderbufferEXT , PFNGLISRENDERBUFFEREXTPROC, "glIsRenderbufferEXT");
	XSI_BIND_FUNC( glRenderbufferStorageEXT, PFNGLRENDERBUFFERSTORAGEEXTPROC, "glRenderbufferStorageEXT");
	XSI_BIND_FUNC( glDrawBuffers, PFNGLDRAWBUFFERSARBPROC, "glDrawBuffers");
	XSI_BIND_FUNC( glMultiTexCoord2f, PFNGLMULTITEXCOORD2FPROC, "glMultiTexCoord2f");
	XSI_BIND_FUNC( glMultiTexCoord3f, PFNGLMULTITEXCOORD3FPROC, "glMultiTexCoord3f");
	XSI_BIND_FUNC( glMultiTexCoord4f, PFNGLMULTITEXCOORD4FPROC, "glMultiTexCoord4f");
	XSI_BIND_FUNC( glMultiTexCoord2fv, PFNGLMULTITEXCOORD2FVPROC, "glMultiTexCoord2fv");
	XSI_BIND_FUNC( glMultiTexCoord3fv, PFNGLMULTITEXCOORD3FVPROC, "glMultiTexCoord3fv");
	XSI_BIND_FUNC( glMultiTexCoord4fv, PFNGLMULTITEXCOORD4FVPROC, "glMultiTexCoord4fv");

	XSI_BIND_FUNC( glBindBufferARB, PFNGLBINDBUFFERARBPROC, "glBindBufferARB");
	XSI_BIND_FUNC( glBufferDataARB, PFNGLBUFFERDATAARBPROC, "glBufferDataARB");
	XSI_BIND_FUNC( glBufferSubDataARB, PFNGLBUFFERSUBDATAARBPROC, "glBufferSubDataARB");
	XSI_BIND_FUNC( glDeleteBuffersARB, PFNGLDELETEBUFFERSARBPROC, "glDeleteBuffersARB");
	XSI_BIND_FUNC( glGenBuffersARB, PFNGLGENBUFFERSARBPROC, "glGenBuffersARB");
	XSI_BIND_FUNC( glGetBufferParameterivARB, PFNGLGETBUFFERPARAMETERIVARBPROC, "glGetBufferParameterivARB");
	XSI_BIND_FUNC( glGetBufferPointervARB, PFNGLGETBUFFERPOINTERVARBPROC, "glGetBufferPointervARB");
	XSI_BIND_FUNC( glGetBufferSubDataARB, PFNGLGETBUFFERSUBDATAARBPROC, "glGetBufferSubDataARB");
	XSI_BIND_FUNC( glIsBufferARB, PFNGLISBUFFERARBPROC, "glIsBufferARB");
	XSI_BIND_FUNC( glMapBufferARB, PFNGLMAPBUFFERARBPROC, "glMapBufferARB");
	XSI_BIND_FUNC( glUnmapBufferARB, PFNGLUNMAPBUFFERARBPROC, "glUnmapBufferARB");

	sUseVBO = glGenBuffersARB != NULL;
	sUseVBO = false;

}

Mesh::~Mesh(void)
{

	if ( sUseVBO )
	{
		if(mVerticesVBO > 0)
		{
			glDeleteBuffersARB(1, &mVerticesVBO);
		}

		if(mIndicesVBO > 0)
		{
			glDeleteBuffersARB(1, &mIndicesVBO);
		}
	}

}

void Mesh::render(LONG id, LONG iLayoutType) const
{

	if ( sUseVBO )
	{
		glDrawElements(GL_TRIANGLES, (GLsizei)mIndices.size(), GL_UNSIGNED_SHORT, 0);
	} else {

		glDrawElements(GL_TRIANGLES, (GLsizei)mIndices.size(), GL_UNSIGNED_SHORT, &mIndices[0]);
	}


}

void Mesh::setState(OGLParticleAttributeData* in_pAttributes) const
{
	if ( sUseVBO )
	{
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, mVerticesVBO);
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, mIndicesVBO);
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (void*)0);
		glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)12);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (void*)24);
	} else {

		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &mVertices[0]);
		glNormalPointer(GL_FLOAT, sizeof(Vertex), &mVertices[0].mNormal[0]);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &mVertices[0].mTextureCoord0[0]);

	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

int Mesh::triangleCount(void) const
{
  assert((mIndices.size() % 3) == 0);
  
  return(int(mIndices.size()) / 3);
}

void Mesh::unsetState(OGLParticleAttributeData* in_pAttributes) const
{
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);

  if(sUseVBO)
    {
      glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
      glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
    }
}

void Mesh::UploadVBO()
{

	if (!sUseVBO)
		return;
	
	 // Create the VBOs
  glGenBuffersARB(1, &mVerticesVBO);
  glGenBuffersARB(1, &mIndicesVBO);

  glBindBufferARB(GL_ARRAY_BUFFER_ARB, mVerticesVBO);
  glBufferDataARB(GL_ARRAY_BUFFER_ARB, mVertices.size() * sizeof(mVertices[0]), &(mVertices[0]), GL_STATIC_DRAW_ARB);
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

  glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, mIndicesVBO);
  glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, mIndices.size() * sizeof(mIndices[0]), &(mIndices[0]), GL_STATIC_DRAW_ARB);
  glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
}
