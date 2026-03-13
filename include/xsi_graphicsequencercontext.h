//*****************************************************************************
/*!
   \file xsi_graphicsequencercontext.h
   \brief GraphicSequencerContext class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIGRAPHICSEQUENCERCONTEXT_H__
#define __XSIGRAPHICSEQUENCERCONTEXT_H__

#include <xsi_base.h>
#include <xsi_value.h>
#include <xsi_graphicsequencer.h>

namespace XSI {

//*****************************************************************************
/*! \class GraphicSequencerContext xsi_graphicsequencercontext.h
	\brief This class represents the plug-in context for the Graphic Sequencer (CGraphicSequencer).

	\sa Context, CGraphicSequencer
	\since 4.0
*/
//*****************************************************************************

class SICPPSDKDECL GraphicSequencerContext : public CBase
{
public:

	/*! Default constructor. */
	GraphicSequencerContext();

	/*! Default destructor. */
	~GraphicSequencerContext();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	GraphicSequencerContext(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	GraphicSequencerContext(const GraphicSequencerContext& in_obj);

	/*! Returns true if a given class type is compatible with this API class.
	\param in_ClassID class type.
	\return true if the class is compatible, false otherwise.
	*/
	bool IsA( siClassID in_ClassID) const;

	/*! Returns the type of the API class.
	\return The class type.
	*/
	siClassID GetClassID() const;

	/*! Creates an object from another object.
	\param in_obj constant class object.
	\return The new Context object.
	*/
	GraphicSequencerContext& operator=(const GraphicSequencerContext& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new Context object.
	*/
	GraphicSequencerContext& operator=(const CRef& in_ref);

	/*! Returns the user data stored in the context.
	\warning This function is not implemented.
	\return The raw user data.
	*/
	CValue		GetUserData();

	/*! Allows you to store a CValue inside the context object. This is called \a User \a Data because %XSI does not care about the
	content or meaning of the data.  This information is not persisted.  A common use for this feature is to store a pointer to a
	newly allocated C++ object during an \c Init callback,and then to use Context::GetUserData to retrieve the pointer when other
	callbacks are made.
	\warning This function is not implemented.
	\note In the case of storing a pointer in the \c Init callback, the pointer should be destroyed in the \c Term callback.
	\param in_val User data to be set for the operator instance.
	\return CStatus::OK success
	\return CStatus::Fail failure.
	 */
	CStatus 	PutUserData(const CValue& in_val);

	/*! Returns the graphic sequencer object (CGraphicSequencer).
	\return The CGraphicSequencer object.
	*/
	CGraphicSequencer	GetGraphicSequencer();

	/*! Sets a single attribute value on the context.  This is a way to pass additional information or capability
	to Softimage. Supported attributes are documented along with the \xt cb_graphicsequencer %Graphic %Sequencer \endxt
	callbacks of each PluginItem. If the attribute does not exist it is added; otherwise the existing value is replaced
	by the new value.
	\param in_AttributeName The name of the attribute to set.
	\param in_val The attribute value to set.
	\return CStatus::OK
	\return CStatus::Fail
	\since 9.0 (2011)
	*/
	CStatus PutAttribute( const CString& in_AttributeName, const CValue& in_val ) ;

	/*! Returns an attribute on the context.  Attributes are used to provide additional context information or capability.
	Supported attributes, if any, are documented along with the \xt cb_graphicsequencer %Graphic %Sequencer \endxt
	callbacks of each PluginItem.
	\param in_AttributeName The name of the attribute to get.
	\return The attribute value.
	\since 9.0 (2011)
	*/
	CValue GetAttribute( const CString& in_AttributeName ) ;


	private:
	GraphicSequencerContext * operator&() const;
	GraphicSequencerContext * operator&();
};

};
#endif // __XSIGRAPHICSEQUENCERCONTEXT_H__
