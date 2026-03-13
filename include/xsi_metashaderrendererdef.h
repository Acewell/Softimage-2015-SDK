//*****************************************************************************
/*!
	\file xsi_metashaderrendererdef.h
	\brief MetaShaderRendererDef class declaration.

	Copyright 2009 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIMETASHADERRENDERERDEF_H__
#define __XSIMETASHADERRENDERERDEF_H__

#include <xsi_valuemap.h>
#include <xsi_siobject.h>

namespace XSI {

//*****************************************************************************
/*! \brief Represents a custom renderer definition.

The MetaShaderRendererDef identifies the implementation of the shader for each of the renderers
capable of using the shader, including the file location and name of the handler, and any renderer
options (for example, the version number). Every ShaderDef must have at least one %MetaShaderRendererDef
defined (see ShaderDef::AddRendererDef).

\sa ShaderDef::AddRendererDef, ShaderDef::RemoveRendererDef, ShaderDef::GetRendererDefByName, Renderer,
	\xm ShaderDefinitions/netview_ShaderDefs Color Sampler example \endxm
\since 9.0 (2011)
*/
//*****************************************************************************

class SICPPSDKDECL MetaShaderRendererDef : public SIObject
{
public:
	/*! Default constructor. */
	MetaShaderRendererDef();

	/*! Default destructor. */
	~MetaShaderRendererDef();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	MetaShaderRendererDef(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	MetaShaderRendererDef(const MetaShaderRendererDef& in_obj);

	/*! Returns true if a given class type is compatible with this API class.
	\param in_ClassID class type.
	\return true if the class is compatible, false otherwise.
	*/
	bool IsA( siClassID in_ClassID) const;

	/*! Returns the type of the API class.
	\return The class type.
	*/
	siClassID GetClassID() const;

	/*! Creates an object from another object. The newly created object is set to
	empty if the input object is not compatible.
	\param in_obj constant class object.
	\return The new MetaShaderRendererDef object.
	\since 9.0 (2011)
	*/
	MetaShaderRendererDef& operator=(const MetaShaderRendererDef& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new MetaShaderRendererDef object.
	\since 9.0 (2011)
	*/
	MetaShaderRendererDef& operator=(const CRef& in_ref);


	/*! Returns the file path of the shader code to execute (for example,
	<tt>"\Application\bin\nt-x86-64\sibase.dll"</tt> or <tt>"{LIBS}/sibase.{EXT}"</tt>. This is the
	same information as specified in the \c FileName entry under the <tt>MetaShader &gt; %Renderer</tt>
	section in a SPDL file.

	\note If the file path hasn't been set then an empty string is returned.
	\return the code path.
	\sa MetaShaderRendererDef::GetCodeText, Shader::GetCodePath
	\since 9.0 (2011)
	*/
	CString GetCodePath(  );

	/*! Sets the file path of the shader code to execute (for example,
	<tt>"\Application\bin\nt-x86-64\sibase.dll"</tt> or <tt>"{LIBS}/sibase.{EXT}"</tt>. This is the
	same information as specified in the \c FileName entry under the <tt>MetaShader &gt; %Renderer</tt>
	section in a SPDL file.
	\param in_codepath the code path.
	\return CStatus
	\sa MetaShaderRendererDef::GetCodeText, Shader::GetCodePath
	\since 9.0 (2011)
	*/
	CStatus PutCodePath( const CString& in_codepath );

	/*! Returns the text of the shader code to execute. This is the same as the embedded shader code
	specified between the \c "BeginText" and \c "EndText" block of the <tt>MetaShader &gt; %Renderer</tt>
	section in a SPDL file.

	\note If the text hasn't been set then an empty string is returned.
	\return the code text.
	\sa MetaShaderRendererDef::GetCodePath, Shader::GetCodeText
	\since 9.0 (2011)
	*/
	CString GetCodeText(  );

	/*! Sets the text of the shader code to execute. This is the same as the embedded shader code specified
	between the \c "BeginText" and \c "EndText" block of the <tt>MetaShader &gt; %Renderer</tt> section in
	a SPDL file.

	\param in_codetext the code text.
	\return Success/failure
	\sa MetaShaderRendererDef::GetCodePath, Shader::GetCodeText
	\since 9.0 (2011)
	*/
	CStatus PutCodeText( const CString& in_codetext );

	/*! Returns the renderer's options as a ValueMap. This is the same information as specified in the
	\c Options entry under the <tt>MetaShader &gt; %Renderer</tt> section in a SPDL file.
	\return the renderer's options.
	\sa Shader::GetRendererOption
	\since 9.0 (2011)
	*/
	ValueMap GetRendererOptions(  );

	/*! Returns the symbol name of the shader code to execute. The symbol name is the name of the procedure
	to execute (for example, \c "material-phong_cg" is the symbol name for the Softimage Phong shader's Cg
	renderer). This is the same information as specified in the \c Name entry under the
	<tt>MetaShader &gt; %Renderer</tt> section in a SPDL file. The returned object is typically used for
	adding extra information to a shader renderer such as the version of a hardware shader (see ::siHWShaderVersionID).

	\note If the symbol name hasn't been set then an empty string is returned.
	\return the symbol name.
	\sa Shader::GetSymbolName
	\since 9.0 (2011)
	*/
	CString GetSymbolName(  );

	/*! Sets the symbol name of the shader code to execute. The symbol name is the name of the procedure to
	execute (for example, \c "material-phong_cg" is the symbol name for the Softimage Phong shader's Cg
	renderer). This is the same information as specified in the \c Name entry under the
	<tt>MetaShader &gt; %Renderer</tt> section in a SPDL file.

	\param in_symbolname the symbol name.
	\return Success/failure
	\sa Shader::GetSymbolName
	\since 9.0 (2011)
	*/
	CStatus PutSymbolName( const CString& in_symbolname );

	private:
	MetaShaderRendererDef * operator&() const;
	MetaShaderRendererDef * operator&();
};

};

#endif

