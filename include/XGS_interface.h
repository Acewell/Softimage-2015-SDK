#ifndef _XGS_INTERFACE_H_
#define _XGS_INTERFACE_H_

#include <GL/gl.h>

#ifdef _WIN32
#include <gl/wglext.h>
#endif

#include <si_stl_ext.h>
#include <CAdaptCComPtr.h>
#include <dsvarian.h>
#include <vector>
#include <XGS_consts.h>
#include <xsi_decl.h>
#include <xsi_value.h>
#include <XSI_rtshaders.h>	// Used for enums
#include <sistring.h>
//******************************************************************************
//
// Forward references
//
//******************************************************************************
namespace XSI
{
	class CGraphicSequencer;
}

class		GPUResource;
class		CXGSContext;

interface	I3DList;
interface	I3DMaterial;
interface	I3DObject;
interface	ISIPluginHost;
interface	I3DDrawData;
interface	I3DImageClip;
interface	IDSImage;

typedef struct tagDSTIME DSTIME;
class CSIString;
class CDSTime;
template< class CElemType > class TChunkArray;

typedef void* (*GETINTERFACE)();

//******************************************************************************
//
// Typedefs
//
//******************************************************************************
interface	I3DRenderer;
interface	I3DRenderOptions;
interface	IXGSHardwareSurface;
class CXSIObjectBuilder;
class CFramebufferData;
class C3DXGSRenderer;

// RT shader type enum (internal use only)
enum TRTShaderType
{
	eFxShaderType = 0,
	eHWShaderType = 1,
	eGLSLShaderType = 2,
	eMSLShaderType = 3,
	// used for keeping the number of types, new types should be inserted above and the count updated 
	eRTShaderTypeCount = eMSLShaderType+1,
	eUndefinedRTShaderType = eRTShaderTypeCount+1
};

struct tHardwareRenderingDrawData
{
	tHardwareRenderingDrawData()
	{
		m_bShaderBallRendering = false;
		m_pGeomList = NULL;
		m_eMode = 0 ;
		m_lRenderFlags = 0;
		m_tcsRenderer = _T("");
		m_pTime = NULL;
		m_pLightList= NULL;
		m_pCameraObj= NULL;
		m_pViewData= NULL;
		m_uiOffX = 0;
		m_uiOffY = 0;
		m_uiWidth =0;
		m_uiHeight= 0;
		m_uiFrameWidth = 0;
		m_uiFrameHeight = 0;
		m_eComponents = GL_RGBA;
		m_eComponentSize = GL_UNSIGNED_BYTE;
		m_pRenderer = NULL;
		m_pRenderOptions = NULL;
		out_framebuffers =	NULL;
		m_bShaderBallRendering = false;
	};
	bool							m_bShaderBallRendering;
	I3DList*						m_pGeomList;
	int								m_eMode;
	int								m_lRenderFlags;
	LPTSTR							m_tcsRenderer;
	DSTIME	*						m_pTime;
	I3DList*						m_pLightList;
	I3DObject *						m_pCameraObj;
	LPVOID							m_pViewData;
	UINT 							m_uiOffX;
	UINT 							m_uiOffY;
	UINT 							m_uiWidth;
	UINT 							m_uiHeight;
	UINT 							m_uiFrameWidth;
	UINT 							m_uiFrameHeight;
	GLenum 							m_eComponents;
	GLenum 							m_eComponentSize;
	I3DRenderer*					m_pRenderer;
	I3DRenderOptions*				m_pRenderOptions;
	std::vector<CFramebufferData*>* out_framebuffers;
};

//! XGS WGL extensions structure
/*! The is the structure for keeping WGL extension support status
*/

typedef struct tagXGSExtensionsWGL
{
	int	 version;
	int  size;

	bool _WGL_ARB_buffer_region ;
	bool _WGL_ARB_extensions_string ;
	bool _WGL_ARB_pixel_format ;
	bool _WGL_ARB_make_current_read ;
	bool _WGL_ARB_pbuffer ;
	bool _WGL_ARB_render_texture ;
	bool _WGL_EXT_display_color_table ;
	bool _WGL_EXT_extensions_string ;
	bool _WGL_EXT_make_current_read ;
	bool _WGL_EXT_pixel_format ;
	bool _WGL_EXT_pbuffer ;
	bool _WGL_EXT_swap_control ;
	bool _WGL_EXT_depth_float ;
	bool _WGL_EXT_multisample ;
	bool _WGL_OML_sync_control ;
	bool _WGL_I3D_digital_video_control ;
	bool _WGL_I3D_gamma ;
	bool _WGL_I3D_genlock ;
	bool _WGL_I3D_image_buffer ;
	bool _WGL_I3D_swap_frame_lock ;
	bool _WGL_I3D_swap_frame_usage ;
	bool _WGL_NV_render_depth_texture ;
	bool _WGL_NV_render_texture_rectangle ;
	bool _WGL_ATI_pixel_format_float ;

} XGSExtensionsWGL;

//! XGS WGL extensions functions
/*! The is the structure for keeping WGL extension functions
*/

typedef struct tagXGSWGLExtensionsFuncs
{																				
	int	 version;
	int  size;	

	PFNWGLCREATEBUFFERREGIONARBPROC							wglCreateBufferRegionARB;							
	PFNWGLDELETEBUFFERREGIONARBPROC							wglDeleteBufferRegionARB;							
	PFNWGLSAVEBUFFERREGIONARBPROC							wglSaveBufferRegionARB;							
	PFNWGLRESTOREBUFFERREGIONARBPROC						wglRestoreBufferRegionARB;								

	PFNWGLGETEXTENSIONSSTRINGARBPROC						wglGetExtensionsStringARB;

	PFNWGLGETPIXELFORMATATTRIBIVARBPROC						wglGetPixelFormatAttribivARB;								
	PFNWGLGETPIXELFORMATATTRIBFVARBPROC						wglGetPixelFormatAttribfvARB;								
	PFNWGLCHOOSEPIXELFORMATARBPROC							wglChoosePixelFormatARB;							

	PFNWGLMAKECONTEXTCURRENTARBPROC							wglMakeContextCurrentARB;
	PFNWGLGETCURRENTREADDCARBPROC							wglGetCurrentReadDCARB;

	PFNWGLCREATEPBUFFERARBPROC								wglCreatePbufferARB;						
	PFNWGLGETPBUFFERDCARBPROC								wglGetPbufferDCARB;						
	PFNWGLRELEASEPBUFFERDCARBPROC							wglReleasePbufferDCARB;							
	PFNWGLDESTROYPBUFFERARBPROC								wglDestroyPbufferARB;						
	PFNWGLQUERYPBUFFERARBPROC								wglQueryPbufferARB;						

	PFNWGLBINDTEXIMAGEARBPROC								wglBindTexImageARB;						
	PFNWGLRELEASETEXIMAGEARBPROC							wglReleaseTexImageARB;							
	PFNWGLSETPBUFFERATTRIBARBPROC							wglSetPbufferAttribARB;							

	PFNWGLCREATEDISPLAYCOLORTABLEEXTPROC					wglCreateDisplayColorTableEXT;									
	PFNWGLLOADDISPLAYCOLORTABLEEXTPROC						wglLoadDisplayColorTableEXT;								
	PFNWGLBINDDISPLAYCOLORTABLEEXTPROC						wglBindDisplayColorTableEXT;								
	PFNWGLDESTROYDISPLAYCOLORTABLEEXTPROC					wglDestroyDisplayColorTableEXT;									

	PFNWGLGETEXTENSIONSSTRINGEXTPROC						wglGetExtensionsStringEXT;

	PFNWGLMAKECONTEXTCURRENTEXTPROC							wglMakeContextCurrentEXT;
	PFNWGLGETCURRENTREADDCEXTPROC							wglGetCurrentReadDCEXT;

	PFNWGLCREATEPBUFFEREXTPROC								wglCreatePbufferEXT;						
	PFNWGLGETPBUFFERDCEXTPROC								wglGetPbufferDCEXT;						
	PFNWGLRELEASEPBUFFERDCEXTPROC							wglReleasePbufferDCEXT;							
	PFNWGLDESTROYPBUFFEREXTPROC								wglDestroyPbufferEXT;						
	PFNWGLQUERYPBUFFEREXTPROC								wglQueryPbufferEXT;						

	PFNWGLGETPIXELFORMATATTRIBIVEXTPROC						wglGetPixelFormatAttribivEXT;								
	PFNWGLGETPIXELFORMATATTRIBFVEXTPROC						wglGetPixelFormatAttribfvEXT;								
	PFNWGLCHOOSEPIXELFORMATEXTPROC							wglChoosePixelFormatEXT;							

	PFNWGLSWAPINTERVALEXTPROC								wglSwapIntervalEXT;						
	PFNWGLGETSWAPINTERVALEXTPROC							wglGetSwapIntervalEXT;							

	PFNWGLALLOCATEMEMORYNVPROC								wglAllocateMemoryNV;
	PFNWGLFREEMEMORYNVPROC									wglFreeMemoryNV;

	PFNWGLGETSYNCVALUESOMLPROC								wglGetSyncValuesOML;						
	PFNWGLGETMSCRATEOMLPROC									wglGetMscRateOML;					
	PFNWGLSWAPBUFFERSMSCOMLPROC								wglSwapBuffersMscOML;						
	PFNWGLSWAPLAYERBUFFERSMSCOMLPROC						wglSwapLayerBuffersMscOML;								
	PFNWGLWAITFORMSCOMLPROC									wglWaitForMscOML;					
	PFNWGLWAITFORSBCOMLPROC									wglWaitForSbcOML;					

	PFNWGLGETDIGITALVIDEOPARAMETERSI3DPROC					wglGetDigitalVideoParametersI3D;									
	PFNWGLSETDIGITALVIDEOPARAMETERSI3DPROC					wglSetDigitalVideoParametersI3D;									

	PFNWGLGETGAMMATABLEPARAMETERSI3DPROC					wglGetGammaTableParametersI3D;									
	PFNWGLSETGAMMATABLEPARAMETERSI3DPROC					wglSetGammaTableParametersI3D;									
	PFNWGLGETGAMMATABLEI3DPROC								wglGetGammaTableI3D;						
	PFNWGLSETGAMMATABLEI3DPROC								wglSetGammaTableI3D;						

	PFNWGLENABLEGENLOCKI3DPROC								wglEnableGenlockI3D;						
	PFNWGLDISABLEGENLOCKI3DPROC								wglDisableGenlockI3D;						
	PFNWGLISENABLEDGENLOCKI3DPROC							wglIsEnabledGenlockI3D;							
	PFNWGLGENLOCKSOURCEI3DPROC								wglGenlockSourceI3D;						
	PFNWGLGETGENLOCKSOURCEI3DPROC							wglGetGenlockSourceI3D;							
	PFNWGLGENLOCKSOURCEEDGEI3DPROC							wglGenlockSourceEdgeI3D;							
	PFNWGLGETGENLOCKSOURCEEDGEI3DPROC						wglGetGenlockSourceEdgeI3D;								
	PFNWGLGENLOCKSAMPLERATEI3DPROC							wglGenlockSampleRateI3D;							
	PFNWGLGETGENLOCKSAMPLERATEI3DPROC						wglGetGenlockSampleRateI3D;								
	PFNWGLGENLOCKSOURCEDELAYI3DPROC							wglGenlockSourceDelayI3D;							
	PFNWGLGETGENLOCKSOURCEDELAYI3DPROC						wglGetGenlockSourceDelayI3D;								
	PFNWGLQUERYGENLOCKMAXSOURCEDELAYI3DPROC					wglQueryGenlockMaxSourceDelayI3D;									

	PFNWGLCREATEIMAGEBUFFERI3DPROC							wglCreateImageBufferI3D;							
	PFNWGLDESTROYIMAGEBUFFERI3DPROC							wglDestroyImageBufferI3D;							
	PFNWGLASSOCIATEIMAGEBUFFEREVENTSI3DPROC					wglAssociateImageBufferEventsI3D;									
	PFNWGLRELEASEIMAGEBUFFEREVENTSI3DPROC					wglReleaseImageBufferEventsI3D;									

	PFNWGLENABLEFRAMELOCKI3DPROC							wglEnableFrameLockI3D;							
	PFNWGLDISABLEFRAMELOCKI3DPROC							wglDisableFrameLockI3D;							
	PFNWGLISENABLEDFRAMELOCKI3DPROC							wglIsEnabledFrameLockI3D;							
	PFNWGLQUERYFRAMELOCKMASTERI3DPROC						wglQueryFrameLockMasterI3D;								

	PFNWGLGETFRAMEUSAGEI3DPROC								wglGetFrameUsageI3D;						
	PFNWGLBEGINFRAMETRACKINGI3DPROC							wglBeginFrameTrackingI3D;							
	PFNWGLENDFRAMETRACKINGI3DPROC							wglEndFrameTrackingI3D;							
	PFNWGLQUERYFRAMETRACKINGI3DPROC							wglQueryFrameTrackingI3D;			
	
} XGSWGLExtensionsFuncs;

enum	eResourceUsage
{
	ResourceUsage_Default = 0,
	ResourceUsage_Static,
	ResourceUsage_Dynamic
};

enum	eResourceType
{
	ResourceType_Texture=0,
	ResourceType_RenderTarget,
	ResourceType_DepthStencil,
	ResourceType_MSAATarget
};


struct tImageDesc
{
	tImageDesc()
	{
		m_uiWidth = 0;
		m_uiHeight = 0;
		m_uiDepth = 0;
		m_eDimensions = XSI::siDefaultDimension;
		m_uiMipLevels = 1;
		m_uiFormat = 0;
		m_uiNbComponents = 0;
		m_uiDataType = 0;
		m_eUsage = ResourceUsage_Default;
		m_eType = ResourceType_Texture;
		m_flags = 0;
		m_MSAALevel = 0;
	};

	UINT								m_uiWidth; 
	UINT								m_uiHeight; 
	UINT								m_uiDepth; 
	XSI::siHardwareSurfaceDimension		m_eDimensions;
	UINT								m_uiMipLevels; 
	UINT 								m_uiFormat;
	UINT 								m_uiNbComponents;
	UINT 								m_uiDataType;
	eResourceUsage						m_eUsage;
	eResourceType						m_eType;
	UINT								m_flags;
	UINT								m_MSAALevel; // Only for render buffers
};

struct tCaptureDesc
{
	tCaptureDesc()
	{
		m_rect.top = 0;
		m_rect.bottom = 0;
		m_rect.right = 0;
		m_rect.left = 0;
		m_channels = XSI::siImageRGBAChannelType;
		m_bitdepth = XSI::siImageBitDepthInteger8;
		m_pPixels = 0;
		m_sizeOfData = 0;
		m_outPixelFormat = GL_RGBA;
	};

	RECT						m_rect;
	XSI::siImageChannelType	m_channels;
	XSI::siImageBitDepth		m_bitdepth;
	GLenum						m_outPixelFormat;
	long		m_sizeOfData;
	void*		m_pPixels;
};

typedef si_hash_map< CSIString, CAdaptCComPtr<IXGSHardwareSurface> > TXGSMapNamedSurfaces;
typedef si_hash_map< CSIString, std::vector<CDSVariant> > TXGSMapNamedParameters;

//! XGS OGL Managed Resource
/*! A class that defines an OGL resource that is managed by the XGS
*/
// Setting tokens
#define	XGS_TILE_WIDTH			"tile_width"
#define	XGS_TILE_HEIGHT			"tile_height"
#define XGS_TILE_INDEX			"tile_index"
#define XGS_TILE_COUNT			"tile_count"
#define XGS_TILE_ORIGIN_X		"tile_origin_x"
#define XGS_TILE_ORIGIN_Y		"tile_origin_y"
#define XGS_FRUSTUM_CLIP_LEFT	"frustum_clip_plane_left"
#define XGS_FRUSTUM_CLIP_RIGHT	"frustum_clip_plane_right"
#define XGS_FRUSTUM_CLIP_BOTTOM	"frustum_clip_plane_bottom"
#define XGS_FRUSTUM_CLIP_TOP	"frustum_clip_plane_top"
#define XGS_FRUSTUM_CLIP_NEAR	"frustum_clip_plane_near"
#define XGS_FRUSTUM_CLIP_FAR	"frustum_clip_plane_far"
#define XGS_PROJECTION_TYPE		"projection_type"
#define XGS_RENDERER_NAME		"renderer_name"


/////////////////////////////////////////////////////////////////////////////
//
// @interface IXGSOGLRenderTarget | Graphic Sequencer OpenGL render target.
//
// @base public | IUnknown
//
/////////////////////////////////////////////////////////////////////////////

#undef  INTERFACE
#define INTERFACE IXGSOGLRenderTarget

DECLARE_INTERFACE_( IXGSOGLRenderTarget, IUnknown )
{
	/////////////////////////////////////////////////////////////////////////////
	// IUnknown methods
	/////////////////////////////////////////////////////////////////////////////
	
	STDMETHOD( QueryInterface )(  REFIID, LPVOID FAR * ) PURE;
	STDMETHOD_( ULONG, AddRef )(  ) PURE;
	STDMETHOD_( ULONG, Release )(  ) PURE;

	/////////////////////////////////////////////////////////////////////////////
	// Interface Specific Methods
	/////////////////////////////////////////////////////////////////////////////
	STDMETHOD( GetDC) ( HDC *out_hdc) PURE;
	STDMETHOD( GetOpenGLContext) ( HGLRC *out_hglrc) PURE;
	STDMETHOD( GetName ) ( TCHAR **out_pName) PURE;
} ;

interface IXGSHardwareSurface : public IUnknown
{
	STDMETHOD( QueryInterface )(  REFIID, LPVOID FAR * ) PURE;
	STDMETHOD_( ULONG, AddRef )(  ) PURE;
	STDMETHOD_( ULONG, Release )(  ) PURE;

	STDMETHOD ( Init ) ( const tImageDesc& in_image,
							void*	in_pData
							) PURE;

	STDMETHOD ( Init ) ( const tImageDesc& in_image,
							XSI::siImageChannelType		in_eChannelType,
							XSI::siImageBitDepth		in_eBitDepth,
							void*	in_pData
							) PURE;
	STDMETHOD ( InitFromSource ) ( I3DImageClip* in_pSource,
									UINT in_uiWidth, 
									UINT in_uiHeight, 
									XSI::siHardwareSurfaceDimension in_eDimension,
									bool in_bMipMaps,
									UINT in_uiNbComponents,
									XSI::siImageBitDepth	in_eBitDepth
									)PURE;

	STDMETHOD_(bool,IsCompatible) ( eResourceType in_eType, 
									XSI::siGraphicDriver in_eGraphicsDriver,
									XSI::siHardwareSurfaceDimension in_eDimension = XSI::siDefaultDimension,
									int in_bMipMaps = -1,
									UINT	in_uiNbCompoments = 0,
									XSI::siImageBitDepth	in_eBitDepth = XSI::siImageBitDepthUnknown,
									UINT	in_uiWidth = 0,
									UINT	in_uiHeight = 0 ) PURE;

	STDMETHOD  (SetDirty)			() PURE;

	STDMETHOD_ (void*, GetInterface ) () PURE;

	STDMETHOD_ (UINT, GetWidth)		() PURE;
	STDMETHOD_ (UINT, GetHeight)		() PURE;
	STDMETHOD_ (eResourceType,	GetType) () PURE;
	STDMETHOD	(GetName)	( CSIString& out_Name ) PURE;

	STDMETHOD_(XSI::siHardwareSurfaceDimension,GetDimension)() PURE;

	// Cube maps have 6 faces.
	// 3D textures are defined with multiple 2D images.
	STDMETHOD(SetCurrentSurface)( UINT in_uiSurface ) PURE;
	STDMETHOD_(UINT, GetCurrentSurface)() PURE;
	STDMETHOD_(UINT, GetSurfaceCount)() PURE;

	// For animated sources
	STDMETHOD(SetCurrentTime)( const CDSTime& in_rTime ) PURE;
	STDMETHOD(SetCurrentFrame)( UINT in_uiTime ) PURE;
	STDMETHOD_(UINT, GetFrameFromTime)( const CDSTime& in_rTime ) PURE;
	STDMETHOD_(UINT, GetFrameCount)() PURE;
} ;

interface IXGSGraphicsDriver : public IUnknown
{
	STDMETHOD( QueryInterface )(  REFIID, LPVOID FAR * ) PURE;
	STDMETHOD_( ULONG, AddRef )(  ) PURE;
	STDMETHOD_( ULONG, Release )(  ) PURE;

	STDMETHOD ( DrawMappedGeometry ) ( void* in_pGraphicInterface,
										XSI_RTS_Primitive	*in_pGeometry, 
												void	*in_pMap,
												XSI_RTS_Attribute_Size	*in_pAttributesSize) PURE;

	STDMETHOD_ (void*, CreateInterface ) (HWND in_parent) PURE;
	STDMETHOD (ReleaseInterface ) (void* in_pInterface) PURE;
	STDMETHOD_ (void*, GetCurrentInterface ) () PURE;

	STDMETHOD  ( SetRenderTarget )				( UINT in_uiDrawBufferIndex, IXGSHardwareSurface* in_pHardwareSurface ) PURE;
	STDMETHOD  ( SetRenderDepthStencilTarget )	( IXGSHardwareSurface* in_pHardwareSurface ) PURE;

	STDMETHOD  ( DrawScreenAlignedQuad ) () PURE;
	STDMETHOD_ (XSI::siGraphicDriver, GetGraphicDriverType)	() PURE;
	STDMETHOD	(Capture)	(tCaptureDesc& out_desc) PURE;
	STDMETHOD_ (LONG,GetDirtyStampID ) ( void* in_pInterface ) PURE;
	STDMETHOD	(AddDriverResource)	( void* in_pResource ) PURE;

	// Reset given device.
	// return HRESULT S_OK: success. S_FALSE: no reset required. Other value: failure.
	STDMETHOD( Reset )( void* in_pDevice ) PURE;

	STDMETHOD  ( GetRenderTarget )				( UINT in_uiDrawBufferIndex, IXGSHardwareSurface** out_ppHardwareSurface ) PURE;
	STDMETHOD  ( GetRenderDepthStencilTarget )	( IXGSHardwareSurface** out_ppHardwareSurface ) PURE;
	STDMETHOD  ( CopySurfaces ) ( IXGSHardwareSurface* in_pSrc, IXGSHardwareSurface* in_pDest ) PURE;
} ;


/*! An XGS managed resource. Things can be copied to here from COGLManagedResource as 
	needed.
*/
interface IXGSManagedResource
{
	enum eResourceType
	{
		Texture=0,
		FBO,
		VBO,
		PBO,
		DisplayList,
		RenderBuffer,
		Shader,
		RAMArray
	};

	enum eSharing
	{
		Shared,
		SharedOwner,
		Exclusive
	};

	virtual UINT			AddRef		(IUnknown* in_Owner) = 0;
	virtual UINT			Release		(IUnknown* in_Owner) = 0;

	virtual GLuint			GetResource( ) = 0;
	virtual TChunkArray<unsigned char>	*	GetArrayResource( ) = 0;
	virtual const char*		GetCode		( ) const = 0;

	virtual void			SetGPUObject( GPUResource*	in_pGPUObject ) = 0;
	virtual GPUResource*	GetGPUObject( ) = 0;
};


/////////////////////////////////////////////////////////////////////////////
//
// @interface IXGSDisplayContextManager | Graphic Sequencer Context Manager.
//
// @base public | IUnknown
//
/////////////////////////////////////////////////////////////////////////////

interface IXGSDisplayContextManager :
	public IUnknown
{
	/////////////////////////////////////////////////////////////////////////////
	// IUnknown methods
	/////////////////////////////////////////////////////////////////////////////
	
	STDMETHOD( QueryInterface )(  REFIID, LPVOID FAR * ) PURE;
	STDMETHOD_( ULONG, AddRef )(  ) PURE;
	STDMETHOD_( ULONG, Release )(  ) PURE;

	/////////////////////////////////////////////////////////////////////////////
	// Interface Specific Methods
	/////////////////////////////////////////////////////////////////////////////

	// context management
	STDMETHOD( CreateContext )(  ULONG in_pID, TCHAR *in_pRenderTargetID ) PURE ;
	STDMETHOD( SetCurrentContext )(  ULONG in_pID ) PURE ;
	STDMETHOD( FreeContext )(  ULONG in_pID ) PURE ;
	STDMETHOD( UpdateContextList )(  ) PURE ;
	STDMETHOD( RefreshContextList )(  ) PURE ;
	STDMETHOD( SetContextViewMode )(  ULONG in_pID, unsigned int in_uiViewMode, TCHAR *in_szViewModeName, bool in_bHQV ) PURE;
	STDMETHOD( SetContextRenderTarget ) (  ULONG in_contextID, TCHAR *in_rtID ) PURE;
	STDMETHOD( SetViewportMapping ) (  ULONG, ULONG ) PURE;
	STDMETHOD( GetContextIDFromViewport ) ( ULONG in_uiViewportID, ULONG *out_puiContextID ) PURE;
	STDMETHOD( IsValidDisplayMode ) (  TCHAR* in_viewname, XSI::siGraphicDriver* out_driver ) PURE;
	STDMETHOD( CleanupOGL ) ( ) PURE;
	

	// Display locking (for non-ui thread access)
	STDMETHOD( AcquireExclusiveDisplay )( ) PURE;
	STDMETHOD( ReleaseExclusiveDisplay )( ) PURE;
		
	// callback management
	STDMETHOD( ExecuteCallbacks )(  ULONG in_pID, XSI::siDisplayCallback in_eFrom, XSI::siDisplayCallback in_eTo ) PURE ;
	STDMETHOD( ExecutePasses	)(  ULONG in_pID ) PURE ;

	// render target management
	STDMETHOD( CreateRenderTarget )(  unsigned int in_lType, TCHAR *in_pID, void *in_pFormat, HWND in_hWnd) PURE ;
	STDMETHOD( GetRenderTargetFromContext )(  ULONG in_pID, IXGSOGLRenderTarget **out_pRenderTarget) PURE;
	STDMETHOD( GetRenderTargetByName )(  TCHAR *in_pID, IXGSOGLRenderTarget **out_pRenderTarget) PURE;

	// states management (Generic)
	STDMETHOD( GetNbStates )(  int in_lType, int *out_pNbStates) PURE;
	STDMETHOD( DeleteState )(  int in_lType, TCHAR *in_pID ) PURE;
	STDMETHOD( CreateState )(  int in_lType, TCHAR *in_pID, LPVOID in_pValuePtr, LPVOID *out_pStateHandle) PURE;
	STDMETHOD( GetStateHandle )(  int in_lType, TCHAR *in_pID, LPVOID *out_pStateHandle) PURE;
	STDMETHOD( GetStateValue )(  int in_lType, LPVOID in_lStateHandle, LPVOID out_pStateValue) PURE;
	STDMETHOD( SetStateValue )(  int in_lType, LPVOID in_lStateHandle, LPVOID in_pStateValue) PURE;

	// notifications
	STDMETHOD( NotifyHostUnloading )(  ISIPluginHost* ) PURE ;
	
	// data extraction for realtime shaders
	STDMETHOD( ExtractLightInfo )(  ) PURE ;
	STDMETHOD( ExtractCameraInfo )(  I3DObject* ) PURE ;

	// rendering
	STDMETHOD( RenderSceneUsingMode )(  int in_eMode, int in_lRenderFlags, I3DObject* in_pCameraOverride=NULL ) PURE ;
	STDMETHOD( RenderSceneUsingMaterial) (  TCHAR* in_szMaterialName, int in_lRenderFlags, I3DObject* in_pCameraOverride=NULL ) PURE ;

	STDMETHOD( RenderListUsingMode )( I3DDrawData* in_pData,  I3DList* in_pI3DList, int in_eMode, int in_lRenderFlags = XSI::siRenderDefault ) PURE ;
	STDMETHOD( RenderListUsingMaterial )(  I3DList* in_pI3DList, const TCHAR *in_szMaterialName, int in_lRenderFlags = XSI::siRenderDefault, I3DObject* in_pCameraOverride=NULL ) PURE ;

	// capabilities and extensions
	STDMETHOD( GetOpenGLExtensions )		(  XGSExtensionsGL* ) PURE ;
	STDMETHOD( GetOpenGLExtensionsFuncs )	(  XGSGLExtensionsFuncs* ) PURE ;
	STDMETHOD( GetWGLExtensions )			(  XGSExtensionsWGL* ) PURE ;
	STDMETHOD( GetWGLExtensionsFuncs )		(  XGSWGLExtensionsFuncs* ) PURE ;

	// scene data access
	STDMETHOD( GetSceneData )				(  XSI_RTS_SceneData** ) PURE;

	// plugin host
	STDMETHOD( GetGraphicSequencer )		(  XSI::CGraphicSequencer** ) PURE;

	STDMETHOD( GetSceneDirtyFlag )			(  bool* ) PURE;
	
	STDMETHOD( RenderNotification )			(  ULONG in_pID, XSI::siDisplayCallback notif ) PURE;
	STDMETHOD( SetPixelFormatAttributes )	(  int* ) PURE;
	STDMETHOD( GetPixelFormatAttributes )	(  int** ) PURE;

	STDMETHOD( NotifyHostLoading )(  ISIPluginHost* ) PURE ;

	STDMETHOD( SetSceneDirty )				(  ) PURE;
	
	STDMETHOD( GetContextFlags )			(  LONG* ) PURE;
	STDMETHOD( SetContextFlags )			(  LONG ) PURE;
	
	STDMETHOD( PopulateLightIDs )			(  ) PURE;
	STDMETHOD( ReleaseLightIDs )			(  ) PURE;

	// InitializeGhostContext must be called at least once before RenderListUsingModeEx, from a convenient place that works... currently, refreshview of view A!
	STDMETHOD ( RenderListUsingModeEx )	  ( tHardwareRenderingDrawData* in_pRenderingData ) PURE;
	// Above these sizes, and RenderListUsingModeEx will perform multiple renders to achieve the result.
	STDMETHOD ( GetRenderToTextureSingleRenderLimit ) ( UINT *out_pMaxX, UINT *out_pMaxY ) PURE;
	// InitializeGhostContext must be called at least once before RenderListUsingModeEx, from a convenient place that works... currently, refreshview of view A!
	STDMETHOD( InitializeGhostContext ) () PURE;
	STDMETHOD_(eChannel, GetChannel ) (int in_iBuffer) PURE;

	// Returns the XGS Master Context. This is the context that contains the OpenGL sharing list.
	STDMETHOD( GetMasterRenderTarget )( IXGSOGLRenderTarget **out_pRenderTarget) PURE;

	STDMETHOD( SetCurrentOGLResourceClient )		(  LONG in_lID ) PURE;
	STDMETHOD_( BOOL, GetManagedResource )			(  LONG in_lSize, 
												UINT in_uiNbElements,
												GLenum in_eDimension,
												GLuint in_uiType, 
												IXGSManagedResource::eResourceType in_eResType, 
												IXGSManagedResource::eSharing in_eShareType, 
												IUnknown*	in_pOwner,
												IXGSManagedResource** ) PURE;

	STDMETHOD_( BOOL, GetManagedResource )			(  GUID in_gID,
														IXGSManagedResource::eResourceType in_eResType, 
														IXGSManagedResource::eSharing in_eShareType, 
														IUnknown*	in_pOwner,
														IXGSManagedResource** ) PURE;

	STDMETHOD_( BOOL, GetManagedResource )			( IDSImage* in_pImage,
														IXGSManagedResource::eSharing in_eShareType, 
														IUnknown*	in_pOwner,
														IXGSManagedResource** ) PURE;

	STDMETHOD( ReleaseManagedResource )			(  IXGSManagedResource* in_pResource, IUnknown*  in_lOwnwer) PURE;

	STDMETHOD_ (bool, GPUEnabled)	(  ) PURE;
	STDMETHOD_ (bool, VBOsPermitted )	(  ) PURE;
	STDMETHOD( SetVBOsPermitted )( bool ) PURE;

	STDMETHOD_( LONG, GetNbExperiments )		(  ) PURE;
	STDMETHOD_( ULONG, BeginTimingExperiment )	(  ) PURE;
	STDMETHOD( EndTimingExperiment )			(  ULONG ) PURE;
	STDMETHOD( AddGPUTimeToExperiments )		(  double ) PURE;
	STDMETHOD_( ULONG, BeginSubExperiment)		(  TCHAR* in_szName )PURE;
	STDMETHOD( EndSubExperiment)				(  ULONG in_ulID ) PURE;

	STDMETHOD( BeginSubGPUExperiment)			(  )PURE;
	STDMETHOD( EndSubGPUExperiment)				(  )PURE;
	
	STDMETHOD_( eGraphicsCard, GetGraphicsCardVendor )		(  ) PURE;
	STDMETHOD ( GetGraphicsCardFeature )					(  eGraphicsCardFeature in_feature, VOID* out_feature) PURE;
	STDMETHOD_ (bool, IsFeatureSupported)					(  eGraphicsCardFeature in_feature ) PURE;

	STDMETHOD ( DumpCurrentOGLContext )					(  ) PURE;
	
	//	RTS 3.0
	
	STDMETHOD_ (IXGSGraphicsDriver*, GetGraphicsDriver) (  XSI::siGraphicDriver in_eDriver) PURE;
	STDMETHOD_ (IXGSGraphicsDriver*, GetCurrentGraphicDriver) () PURE;

	STDMETHOD ( DrawGeometry ) (  XSI::siGraphicDriver in_eDriver,
									XSI_RTS_Primitive	*in_pGeometry, 
									XSI_RTS_Attribute *in_pAttributes,
									void*	in_pAttribData,
									XSI_RTS_Attribute_Size			*in_pAttributesSize) PURE;

	STDMETHOD ( DrawGeometry ) (  XSI::siGraphicDriver in_eDriver,
									XSI_RTS_Primitive	*in_pGeometry, 
									const char* in_szMapping, 
									void*	in_pAttribData,
									XSI_RTS_Attribute_Size			*in_pAttributesSize) PURE;

	STDMETHOD ( DrawScreenAlignedQuad ) (  XSI::siGraphicDriver in_eDriver ) PURE;

	STDMETHOD_ (XSI_RTS_Attribute*,	GetAttributeDescriptorFromMapping)(  const char* in_szMapping ) PURE;

	STDMETHOD ( GetCurrentCamera )  ( I3DObject** out_Camera ) PURE;

	STDMETHOD( SetActiveChannels ) ( THIS_ int* in_pChannels, int in_iNbChannels) PURE;
	STDMETHOD( PushExecutionState ) ( THIS ) PURE;
	STDMETHOD( PopExecutionState ) ( THIS ) PURE;
	STDMETHOD( EnsureValidOpenGLContext ) ( THIS ) PURE;
	STDMETHOD( SetPickMode )	(REFCATID in_PickMode ) PURE;	// see drawdata
	STDMETHOD( GetPickMode)		(CATID * out_pPickMode) PURE;	// see drawdata
	STDMETHOD( GetCurrentDrawData ) ( I3DDrawData** out_pDrawData ) PURE; 

	STDMETHOD( GetHardwareSurfaceFromImageClip ) ( XSI::siGraphicDriver in_eDriver, 
													I3DImageClip* in_pClip, 
													UINT	in_uiWidth,
													UINT	in_uiHeight,
													XSI::siHardwareSurfaceDimension	in_eDimension,
													bool	in_bMipMaps,
													UINT	in_uiNbComponents,
													XSI::siImageBitDepth in_eBitDepth,
													IXGSHardwareSurface** out_pHardwareSurface ) PURE;
	
	STDMETHOD( CreateHardwareSurface)			(  XSI::siGraphicDriver in_eDriver, 
													const char *in_szSurfaceFormat,
													UINT	in_uiWidth,
													UINT	in_uiHeight,
													XSI::siHardwareSurfaceDimension	in_eDimension,
													bool	in_bMipMaps,
													XSI::siResourceSharing in_eSharing,
													IXGSHardwareSurface** out_pHardwareSurface ) PURE;

	STDMETHOD ( ReleaseHardwareSurface)			( IXGSHardwareSurface* in_pHardwareSurface ) PURE;

	STDMETHOD (SetRenderTarget)					( XSI::siGraphicDriver in_eDriver, UINT in_uiDrawBufferIndex, IXGSHardwareSurface* in_pHardwareSurface ) PURE;
	STDMETHOD (SetRenderDepthStencilTarget)		( XSI::siGraphicDriver in_eDriver, IXGSHardwareSurface* in_pHardwareSurface ) PURE;
	STDMETHOD (GetManagedResourceOwner)			( void* pInterface, IUnknown** out_punk) PURE;
	STDMETHOD_(ULONG, GetCurrentViewportID)		() PURE;
	STDMETHOD_(CXGSContext*, GetCurrentContext)	() PURE;

	STDMETHOD_( bool, IsDrawing )	() PURE;
	// Returns the number of registered display callbacks
	STDMETHOD_( long, GetNbCallbacks )			() PURE;

	// Returns packed framebuffer information
	STDMETHOD (GetFramebuffers)			( SAFEARRAY** out_pFramebuffers ) PURE;
	// Puts pixels into a framebuffer
	STDMETHOD (PutFramebufferData) 		( UINT in_uiFramebufferIndex, 
										ULONG in_ulSizeInBytes,
										void* in_pData ) PURE;
	// Returns a setting specified by name
	STDMETHOD (GetSetting)				( const CSIString& in_name, VARIANT* out_pVal ) PURE;

	STDMETHOD (SetHWRenderer)			( const C3DXGSRenderer* in_pHWRenderer ) PURE;
	STDMETHOD_ (const C3DXGSRenderer*, GetHWRenderer)			() PURE;

	virtual HRESULT GetRendererOptions(
		const CDSTime	&in_rTime,
		const IID		&in_rIID,
		void			**out_ppRendererOptions
		) = 0;


	STDMETHOD (GetCustomRendererPropertyList) ( std::vector< CSIString >& out_InstalledCustomOptions ) = 0;

	STDMETHOD (GetValueFromPass ) (ULONG in_ulCtxId, TCHAR* in_pValueName, DSTIME	*in_pTime , XSI::CValue& out_Value) PURE;



	STDMETHOD ( DirtyAllViewports ) () PURE;
	STDMETHOD ( BeginHardwareRendering ) (CSIString& in_csViewportMode) PURE;
	STDMETHOD ( EndHardwareRendering ) () PURE;
	STDMETHOD	( PushDrawData ) ( I3DDrawData*,I3DList* ) PURE;
	STDMETHOD	( PopDrawData ) ( I3DDrawData* ) PURE;
	STDMETHOD_(bool,IsPlayback) () PURE;


	// Shadow Surfaces Management
	STDMETHOD ( SetShadowSurfaces ) ( I3DList* in_listShadowSurfaces, I3DList* in_listShadowLights ) PURE;
	STDMETHOD ( GetShadowSurfaces ) ( I3DList** out_listShadowSurfaces, I3DList** out_listShadowLights ) PURE;
	
	STDMETHOD ( ResetDirectX ) ( ) PURE;
	
	// Keep count on the RT shaders in the scene
	STDMETHOD ( UpdateRTShaderCount ) ( TRTShaderType in_nType, bool in_bIncrement ) PURE;
	STDMETHOD_ ( ULONG, GetRTShaderCount ) ( TRTShaderType in_nType ) PURE;	

	// Named Surfaces Management
	STDMETHOD ( SetNamedSurface ) ( const CSIString& in_strSurfaceName, IXGSHardwareSurface* in_pSurface ) PURE;
	STDMETHOD ( GetNamedSurface ) ( const CSIString& in_strSurfaceName, IXGSHardwareSurface** out_ppSurface ) PURE;
	STDMETHOD ( GetNamedSurfaces ) ( TXGSMapNamedSurfaces& out_map ) PURE;
	STDMETHOD ( ClearNamedSurfaces ) () PURE;

	// Named Parameters Management
	STDMETHOD ( SetNamedParameter ) ( const CSIString& in_strParamName, const std::vector<CDSVariant>& in_value ) PURE;
	STDMETHOD ( GetNamedParameter ) ( const CSIString& in_strParamName, std::vector<CDSVariant>& out_value ) PURE;
	STDMETHOD ( GetNamedParameters ) ( TXGSMapNamedParameters& out_map ) PURE;
	STDMETHOD ( ClearNamedParameters ) () PURE;

	// Material Cache
	STDMETHOD ( CreateMaterialFromPreset ) ( const CSIString& in_strPresetName, I3DMaterial** out_ppMaterial ) PURE;
};


#endif //_XGS_INTERFACE_H_
