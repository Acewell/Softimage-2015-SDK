//*****************************************************************************
/*!
	\file xsi_shaderballoptions.h
	\brief ShaderballOptions class declaration.

	Copyright 2009 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSISHADERBALLOPTIONS_H__
#define __XSISHADERBALLOPTIONS_H__

#include <xsi_siobject.h>

namespace XSI {

//*****************************************************************************
/*! \brief Represents the options for a shaderball view.

	This object represents the options available to tweak the initial appearance of the shaderball
	node/window in the RenderTree. You can access this object via ShaderDef::GetShaderballOptions.

    \sa ShaderDef::GetShaderballOptions
    \since 9.0 (2011)
 */
//*****************************************************************************
class SICPPSDKDECL ShaderballOptions : public SIObject
{
public:
	/*! Default constructor. */
	ShaderballOptions();

	/*! Default destructor. */
	~ShaderballOptions();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	ShaderballOptions(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	ShaderballOptions(const ShaderballOptions& in_obj);

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
	\return The new ShaderballOptions object.
	*/
	ShaderballOptions& operator=(const ShaderballOptions& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new ShaderballOptions object.
	*/
	ShaderballOptions& operator=(const CRef& in_ref);


	/*! Returns the background to use by default.
	\return the shaderball background name.
	\since 9.0 (2011)
	*/
	CString GetDefaultBackground(  ) const;

	/*! Sets the background to use.
	\param in_background the shaderball background name.
	\return Success/failure
	\since 9.0 (2011)
	*/
	CStatus PutDefaultBackground( const CString& in_background );

	/*! Returns the model to use for the shaderball by default.
	\return the name of the model
	\sa Model
	\since 9.0 (2011)
	*/
	CString GetDefaultModel(  ) const;

	/*! Sets the model to use for the shaderball by default.
	\param in_model the name of the model
	\return Success/failure
	\sa Model
	\since 9.0 (2011)
	*/
	CStatus PutDefaultModel( const CString& in_model );

	/*! Returns one of the ::siShaderballDimension enum values that determines what
	dimensions the shaderball supports.
	\return supported dimension
	\since 9.0 (2011)
	*/
	siShaderballDimension GetDimension(  ) const;

	/*! Sets one of the ::siShaderballDimension enum values that determines what
	dimensions the shaderball supports.
	\param in_dimension supported dimension
	\return Success/failure
	\since 9.0 (2011)
	*/
	CStatus PutDimension( siShaderballDimension in_dimension );

	/*! Indicates whether or not the shaderball was initialized.
	\return true if it was initialized
	\return false otherwise
	\sa ShaderballOptions::Reset
	\since 9.0 (2011)
	*/
	bool GetInit(  ) const;

	/*! Returns the shaderball options to the uninitialized state.
	\return Success/failure
	\sa ShaderballOptions::GetInit
	\since 9.0 (2011)
	*/
	CStatus Reset(  );

	/*! Returns a Boolean value describing whether or not to show the shaderball by default.
	\return true to show the shaderball by default
	\return false otherwise
	\since 9.0 (2011)
	*/
	bool GetShowByDefault(  ) const;

	/*! Sets a Boolean value describing whether or not to show the shaderball by default.
	\param in_show true to show the shaderball by default; false otherwise
	\return Success/failure
	\since 9.0 (2011)
	*/
	CStatus PutShowByDefault( bool in_show );

	private:
	ShaderballOptions * operator&() const;
	ShaderballOptions * operator&();
};

};

#endif

