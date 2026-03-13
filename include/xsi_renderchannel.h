//*****************************************************************************
/*!	\file xsi_renderchannel.h
	\brief RenderChannel class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSI_RENDERCHANNEL_H__
#define __XSI_RENDERCHANNEL_H__

#include <xsi_siobject.h>

namespace XSI {

//*****************************************************************************
/*! \class RenderChannel xsi_renderchannel.h
	\brief A render channel is a container for rendered image data output. The
	channel describes what kind of data can be recorded into it.

	There are two types of channels:

	\li \a renderer-provided \n
	The renderer-provided type consists of channels that are explicitly provided
	by the rendering engine (such as the main render output and a depth output).

	\li \a user-defined \n
	User-defined channels are used in conjunction with shaders which can be
	set to record any data into those channels, depending on their
	channel type, or any other mechanism that the rendering engine provides.

	\since 6.0
 */
//*****************************************************************************

class SICPPSDKDECL RenderChannel : public SIObject
{
public:
	/*! Default constructor. */
	RenderChannel();

	/*! Default destructor. */
	~RenderChannel();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	RenderChannel(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	RenderChannel(const RenderChannel& in_obj);

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
	\return The new RenderChannel object.
	*/
	RenderChannel& operator=(const RenderChannel& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new RenderChannel object.
	*/
	RenderChannel& operator=(const CRef& in_ref);

	/*! Returns the basic data type which the render channel will consist of. The basic
	data type indicates also how the data will be interpreted by %XSI for display purposes
	and which image output formats will be available on any Framebuffer object that
	derives from this render channel.
	\return The data type of the render channel.
	\sa Framebuffer \link siRenderChannelType \endlink
	*/
	siRenderChannelType GetChannelType( );

	/*! Indicates whether this channel was created by the user and can be deleted or that
	it was created by the rendering engine and is permanent.

	User-defined channels are also used in the render tree for piping render data into.
	\return True if user-defined; false if provided by the renderer.
	\sa Framebuffer
	*/
	bool GetUserDefined( );

private:
	RenderChannel * operator&() const;
	RenderChannel * operator&();
};

};

#endif // __XSI_RENDERCHANNEL_H__
