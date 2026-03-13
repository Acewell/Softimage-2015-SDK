//*****************************************************************************
/*!	\file xsi_framebuffer.h
	\brief Framebuffer class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSI_FRAMEBUFFER_H__
#define __XSI_FRAMEBUFFER_H__

#include <xsi_projectitem.h>

namespace XSI {

class RenderChannel;
class CTime;
class CLongArray;

//*****************************************************************************
/*! \class Framebuffer xsi_framebuffer.h
	\brief The Framebuffer object controls the file output of a RenderChannel object.
	It can be created using the Pass::CreateFramebuffer function.

	The framebuffer format can be selected from the list of formats provided by the rendering
	engine selected on the framebuffer's Pass object.

	\sa RenderChannel SceneRenderProperty Pass
	\since 6.0

	\eg This example demonstrates how to list all framebuffers from
		all passes and the resolved paths they point to.
	\code
		#include <xsi_project.h>
		#include <xsi_scene.h>
		#include <xsi_pass.h>
		#include <xsi_passcontainer.h>
		#include <xsi_framebuffer.h>
		#include <xsi_parameter.h>
		#include <xsi_time.h>
		using namespace XSI;

		// Helpers
		void ListPasses()
		{
			Application xsi = Application();
			CRefArray passes = xsi.GetActiveProject().GetActiveScene().GetPasses();
			xsi.LogMessage(L"# of passes found: "+CString(passes.GetCount()));
			for ( LONG i=0; i<passes.GetCount(); i++ )
			{
				Pass oPass = Pass(CRef(passes[i]));
				xsi.LogMessage( L"Pass '"  + oPass.GetName() + L"': " );

				CRefArray buffers = oPass.GetFramebuffers();
				xsi.LogMessage(L"# of buffers found: "+CString(buffers.GetCount()));
				for( LONG j=0; j<buffers.GetCount(); j++ )
				{
					Framebuffer oFramebuffer = Framebuffer(CRef(buffers[j]));
					xsi.LogMessage( L"Framebuffer '" + oFramebuffer.GetName() + L"' writes to '" +
						oFramebuffer.GetResolvedPath(CTime()) + L"'" );
				}
			}
		}

		CValue NewScene( const CString& in_ProjectPathName, const bool& in_Confirm )
		{
			CValueArray args(2);
			CValue retval;

			args[0]= in_ProjectPathName;
			args[1]= in_Confirm;

			Application app;
			CStatus st = app.ExecuteCommand( L"NewScene", args, retval );

			return retval;
		}

		Application app = Application();
		NewScene( L"", false );
		Scene oScene = app.GetActiveProject().GetActiveScene();
		Pass oNewPass = oScene.GetPassContainer().AddPass( L"", L"" );
		Framebuffer oDiffuseBuffer = oNewPass.CreateFramebuffer( L"Diffuse" );
		oDiffuseBuffer.PutParameterValue(L"FileName", L"diffuse.[Frame #4]");

		// Invoke the ListPasses( ) function
		ListPasses( );

		// Expected results:
		// INFO : Pass 'Default_Pass':
		// INFO : Framebuffer 'Main' writes to '<factorypath>\Data\XSI_SAMPLES\Render_Pictures\Default_Pass_Main.1.pic'

	\endcode
 */
//*****************************************************************************

class SICPPSDKDECL Framebuffer : public ProjectItem
{
public:
	/*! Default constructor. */
	Framebuffer();

	/*! Default destructor. */
	~Framebuffer();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	Framebuffer(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	Framebuffer(const Framebuffer& in_obj);

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
	\return The new Framebuffer object.
	*/
	Framebuffer& operator=(const Framebuffer& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new Framebuffer object.
	*/
	Framebuffer& operator=(const CRef& in_ref);

	/*! Returns the RenderChannel this Framebuffer represents. All rendering
	takes place in a render channel and is output to disk by the framebuffer object.
	\return The RenderChannel object.
	\sa RenderChannel \link siRenderChannelType \endlink
	*/
	RenderChannel GetRenderChannel( );

	/*! Takes the output file name path template given in the framebuffer and resolves it,
	for the specified time, into a real path name and returns it as a CString. 
	See section "Output Path Templates" in the Softimage User Guide for more details.

	The \c in_rTime parameter controls the result of the \c  [Frame] and \c  [Field] tokens.
	\param in_rTime The time to resolve the path template at.
	\return The resolved file name path template at the given time.
	\sa Pass::GetResolvedArchivePath \xl %XSIUtils.ResolveTokenString	
	\since 6.01
	*/
	CString GetResolvedPath( const CTime &in_rTime );

	/*! Takes the output file name path template given in the framebuffer and resolves it
	into a time-independent path, where any instance of \c [Frame] is substituted with the
	a sequence of \c '#' symbols, that represent the current frame number and padding width.
	See section "Output Path Templates" in the Softimage User Guide for more details.
	\return The time-independent resolved file name path template.
	\sa Pass::GetResolvedArchivePath \xl %XSIUtils.ResolveTokenString
	\since 6.01
	*/
	CString GetResolvedPath( );

	/*! Returns a list of the available image output file formats that can be set for this
	framebuffer. The format selection is dependent on the current rendering engine and the
	channel type of the RenderChannel object represented by this framebuffer.
	\return A list of format extensions corresponding to the image file formats available
		to this framebuffer.
	\sa RenderChannel \link siRenderChannelType \endlink
	*/
	CStringArray GetFormats();

	/*! Returns a list of the available output data types for the image output file format
	selected for this framebuffer.
	\return An array of data types for the selected image output format. Although the data
		type can be any string, many of them are predefined in \link siImageDataType \endlink.
	\sa RenderChannel \link siRenderChannelType \endlink \link siImageDataType \endlink
	*/
	CStringArray GetDataTypes();

	/*! Returns a list of the available bit depths for the selected output data type for
	this framebuffer.
	\return A list of \link siImageBitDepth \endlink values available for the selected output data type.
	\sa RenderChannel \link siRenderChannelType \endlink \link siImageDataType \endlink \link siImageBitDepth \endlink
	*/
	CLongArray GetBitDepths();

	/*! Returns the bit depth to use for returning color data back to Softimage for display
	at render time. This value will be passed to RendererImageFragment::GetScanlineRGBA when
	Softimage asks for image fragment data.
	\return A color bit depth for display data.
	\sa RendererImageFragment
	\since 7.0
	*/
	XSI::siImageBitDepth GetDisplayBitDepth( );

	/*! Takes the output file name path template given in the framebuffer and resolves it,
	for the specified time, into a real path name and returns it as a CString. 
	See section "Output Path Templates" in the Softimage User Guide for more details.

	The \c in_rTime parameter controls the result of the \c  [Frame] and \c  [Field] tokens.
	\param in_rTime The time to resolve the path template at.
	\param in_rCtx The renderer context given, used to resolve context specific tokens such as the current camera used
	\return The resolved file name path template at the given time.
	\sa Pass::GetResolvedArchivePath \xl %XSIUtils.ResolveTokenString	
	\since 12.0 (2014)
	*/
	CString GetResolvedPath( const CTime &in_rTime, const CRef& in_rCtx );

	/*! Takes the output file name path template given in the framebuffer and resolves it
	into a time-independent path, where any instance of \c [Frame] is substituted with the
	a sequence of \c '#' symbols, that represent the current frame number and padding width.
	See section "Output Path Templates" in the Softimage User Guide for more details.
	\param in_rCtx The renderer context given, used to resolve context specific tokens such as the current camera used
	\return The time-independent resolved file name path template.
	\sa Pass::GetResolvedArchivePath \xl %XSIUtils.ResolveTokenString
	\since 12.0 (2014)
	*/
	CString GetResolvedPath( const CRef& in_rCtx );
private:
	Framebuffer * operator&() const;
	Framebuffer * operator&();
};

};

#endif // __XSI_FRAMEBUFFER_H__
