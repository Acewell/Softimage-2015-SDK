//*****************************************************************************
/*!
	\file xsi_hardwaresurface.h
	\brief HardwareSurface class declaration.

	Copyright 2010 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIHARDWARESURFACE_H__
#define __XSIHARDWARESURFACE_H__

#include <xsi_siobject.h>

namespace XSI {

class ImageClip2 ;

//*****************************************************************************
/*!
	\class HardwareSurface xsi_hardwaresurface.h
	\brief HardwareSurface class used for encapsulating a 2D shader texture surface.

	\since 9.0 (2011)
 */
//*****************************************************************************
class SICPPSDKDECL HardwareSurface : public SIObject
{
public:
	/*! Default constructor. */
	HardwareSurface();

	/*! Default destructor. */
	~HardwareSurface();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	HardwareSurface(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	HardwareSurface(const HardwareSurface& in_obj);

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
	\return The new HardwareSurface object.
	*/
	HardwareSurface& operator=(const HardwareSurface& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new HardwareSurface object.
	*/
	HardwareSurface& operator=(const CRef& in_ref);

	/*! Returns a void* which represents the interface to the Graphics API.	For OpenGL, the returned
		pointer should be casted to a GLuint which represents the texture object. For DirectX9, it
		should be casted to a IDirectX9Texture.
		\return Graphic API interface pointer.
	*/
	void* GetInterface();

	//*************************************************************************
	/*! \class Options xsi_hardwaresurface.h
		\brief This class represents the options used for creating HardwareSurface objects.

		\sa HardwareSurface
		\since 9.0 (2011)
	*/
	//*************************************************************************

	class SICPPSDKDECL Options
	{
		public:
			friend class HardwareSurface;
			friend class HardwareShaderContext;
			friend class ImageClip2;

			/*! Constructor. */
			Options();

			/*! Destructor. */
			~Options();

			/*! Set the new hardware surface format according to the values defined in D3DFORMAT. The list of supported formats is the
			following:

				"R8G8B8"
				"A8R8G8B8"
				"X8R8G8B8"
				"R5G6B5"
				"X1R5G5B5"
				"A1R5G5B5"
				"A4R4G4B4"
				"R3G3B2"
				"A8"
				"A8R3G3B2"
				"X4R4G4B4"
				"A2B10G10R10"
				"A8B8G8R8"
				"X8B8G8R8"
				"A2R10G10B10"
				"A16B16G16R16"
				"A32B32G32R32F"
				"A16B16G16R16F"
				"D16"
				"D32"
				"D15S1"
				"D24S8"
				"D24S8_SHADOWMAP"
				"D24X8"

			The default format is "A8R8G8B8".

			\param in_format Surface format as defined by D3DFORMAT.
			\return CStatus::OK Success
			*/
			CStatus PutFormat( const CString& in_format );

			/*! Set the width of the new hardware shader surface.
			\param in_nWidth Display surface width.
			\return CStatus::OK Success.
			*/
			CStatus PutWidth( UINT in_nWidth );

			/*! Set the height of the new hardware shader surface.
			\param in_nHeight Display surface height.
			\return CStatus::OK Success.
			*/
			CStatus PutHeight( UINT in_nHeight );

			/*! Set the graphic driver type for the new hardware shader surface.
			\param in_eGraphicDriver Graphic driver type. Defaults to siOpenGL20.
			\return CStatus::OK Success.
			*/
			CStatus PutGraphicDriver( siGraphicDriver in_eGraphicDriver );

			/*! Set the resource sharing type for the new hardware shader surface.
			\param in_eShareCap Resource sharing capability. Defaults to siSharedResource.
			\return CStatus::OK Success.
			*/
			CStatus PutSharing( siResourceSharing in_eShareCap );

			/*! Set the dimension of the new hardware shader surface.
			\param in_eDimension Dimension type. Defaults to siDefaultDimension.
			\return CStatus::OK Success.
			*/
			CStatus PutDimension( siHardwareSurfaceDimension in_eDimension );

			// internal
			CStatus PutFlags( LONG in_lFlags );

		protected:
			void* m_pImpl;
	};

	private:
	HardwareSurface * operator&() const;
	HardwareSurface * operator&();
};

};

#endif

