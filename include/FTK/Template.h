//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file Template.h
	\brief Defines the CSLTemplate class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _TEMPLATE_H
#define _TEMPLATE_H

#if defined(_WIN32) || defined(_WIN32_WCE) || defined(_XBOX)

// Disable "identifier was truncated to '255' characters in the debug information" warning.
#pragma warning( disable : 4786 )

// Disable warnings on extern before template instantiation.
#pragma warning( disable : 4231 )

#endif // defined(_WIN32) || defined(_WIN32_WCE)  || defined(_XBOX)

// Include files
#include "SLTypes.h"
#include <XSIParser.h>
#include <dotXSIDefines.h>


// Forward class declaration
class CSLScene;
class CSLModel;
class CSLCustomPSet;
class CSLUserDataBlob;
class CSLFCurve;
class CSLXSIUserKeyword;

/*! \brief Describes a dotXSI template.

	The CSLTemplate class is the base class for all classes in the
	semantic layer that describes a specific dotXSI template.

	The class contains generic data manipulation, such as FCurve
	manipulation, custom parameter set manipulation and I/O synchronization.

	This class is pure virtual, meaning you can't instantiate it directly.
	However, since you can obtain a pointer to a CSLTemplate, if you want
	to know which derived class was instantied, use the function Type.
*/
class XSIEXPORT CSLTemplate : public CSIBCNode
{
public:
	/*! This enum lists all templates supported by the semantic layer.
	*/
	enum ETemplateType
	{
		SI_ACTION_FCURVE,							/*!< Action FCurve template */
		SI_ANGLE,									/*!< \xx ftk_SI_Angle SI_Angle \endxx template */
		SI_AMBIENCE,								/*!< \xx ftk_SI_Ambience SI_Ambience \endxx template */
		SI_BASE_SHAPE,								/*!< Base Shape template */
		SI_CAMERA,									/*!< \xx ftk_SI_Camera SI_Camera \endxx template */
		SI_CLUSTER,									/*!< \xx ftk_SI_Cluster SI_Cluster \endxx template */
		SI_CONSTRAINT,								/*!< \xx ftk_SI_Constraint SI_Constraint \endxx template */
		SI_COORDINATE_SYSTEM,						/*!< \xx ftk_SI_CoordinateSystem SI_CoordinateSystem \endxx template */
		SI_CURVE_LIST,								/*!< \xx ftk_XSI_CurveList XSI_CurveList \endxx template */
		SI_CUSTOM_PSET,								/*!< \xx ftk_XSI_CustomPSet XSI_CustomPSet \endxx template */
		SI_CUSTOM_PARAM_INFO,						/*!< \xx ftk_XSI_CustomPSetInfo XSI_CustomPSetInfo \endxx template */
		SI_DIRECTIONAL_LIGHT,						/*!< Directional light template */
		SI_ENVELOPE,								/*!< \xx ftk_SI_Envelope SI_Envelope \endxx template */
		SI_ENVELOPE_LIST,							/*!< \xx ftk_SI_EnvelopeList SI_EnvelopeList \endxx template */
		SI_FCURVE,									/*!< \xx ftk_SI_FCurve SI_FCurve \endxx template */
		SI_FILE_INFO,								/*!< \xx ftk_SI_FileInfo SI_FileInfo \endxx template */
		SI_FOG,										/*!< \xx ftk_SI_Fog SI_Fog \endxx template */
		SI_GLOBAL_MATERIAL,							/*!< \xx ftk_SI_GlobalMaterial SI_GlobalMaterial \endxx template */
		SI_IK_EFFECTOR,								/*!< \xx ftk_SI_IK_Effector SI_IK_Effector \endxx template */
		SI_IK_JOINT,								/*!< \xx ftk_SI_IK_Joint SI_IK_Joint \endxx template */
		SI_IK_ROOT,									/*!< \xx ftk_SI_IK_Root SI_IK_Root \endxx template */
		SI_INFINITE_LIGHT,							/*!< Infinite light */
		SI_INSTANCE,								/*!< \xx ftk_SI_Instance SI_Instance \endxx template */
		SI_LIGHT_INFO,								/*!< \xx ftk_SI_LightInfo SI_LightInfo \endxx template */
		SI_MATERIAL,								/*!< Legacy \xx ftk_SI_Material SI_Material \endxx template */
		SI_MATERIAL_LIBRARY,						/*!< \xx ftk_SI_MaterialLibrary SI_MaterialLibrary \endxx template */
		SI_MESH,									/*!< \xx ftk_SI_Mesh SI_Mesh \endxx template */
		SI_MODEL,									/*!< \xx ftk_SI_Model SI_Model \endxx template */
		SI_NULL_OBJECT,								/*!< \xx ftk_SI_Null SI_Null \endxx template */
		SI_NURBS_CURVE,								/*!< \xx ftk_SI_NurbsCurve SI_NurbsCurve \endxx template */
		SI_NURBS_SURFACE,							/*!< \xx ftk_SI_NurbsSurface SI_NurbsSurface \endxx template */
		SI_POINT_LIGHT,								/*!< Point Light */
		SI_POLYGON_LIST,							/*!< \xx ftk_SI_PolygonList SI_PolygonList \endxx template */
		SI_SCENE_INFO,								/*!< \xx ftk_SI_Scene SI_Scene \endxx template */
		SI_SHAPE,									/*!< \xx ftk_SI_Shape SI_Shape \endxx template */
		SI_SHAPE35,									/*!< \xx ftk_SI_Shape SI_Shape \endxx dotXSI Version 3.5+ template */
		SI_SHAPE_ANIMATION,							/*!< \xx ftk_SI_ShapeAnimation SI_ShapeAnimation \endxx template */
		SI_SPOT_LIGHT,								/*!< Spot light */
		SI_SURFACE_MESH,							/*!< \xx ftk_XSI_SurfaceMesh XSI_SurfaceMesh \endxx template */
		SI_TEXTURE_2D,								/*!< Legacy \xx ftk_SI_Texture2D SI_Texture2D \endxx template */
		SI_TRANSFORM,								/*!< \xx ftk_SI_Transform SI_Transform \endxx template */
		SI_TRIANGLE_LIST,							/*!< \xx ftk_SI_TriangleList SI_TriangleList \endxx template */
		SI_TRIANGLE_STRIP,							/*!< \xx ftk_SI_TriStrip SI_TriStrip \endxx template */
		SI_TRIANGLE_STRIP_LIST,						/*!< \xx ftk_SI_TriStripList SI_TriStripList \endxx template */
		SI_VISIBILITY,								/*!< \xx ftk_SI_Visibility SI_Visibility \endxx template */
		XSI_ACTION,									/*!< \xx ftk_XSI_Action XSI_Action \endxx template */
		XSI_ACTIONCLIP,								/*!< \xx ftk_XSI_ActionClip XSI_ActionClip \endxx template */
		XSI_CUSTOM_PARAM_INFO,						/*!< \xx ftk_XSI_CustomPSet XSI_CustomPSet \endxx template */
		XSI_EXTRAPOLATION,							/*!< \xx ftk_XSI_Extrapolation XSI_Extrapolation \endxx template */
		XSI_FXOPERATOR,								/*!< \xx ftk_XSI_FXOperator XSI_FXOperator \endxx template */
		XSI_FXTREE,									/*!< \xx ftk_XSI_FXTree XSI_FXTree \endxx template */
		XSI_IMAGE,									/*!< \xx ftk_XSI_Image XSI_Image \endxx template */
		XSI_IMAGE_DATA,								/*!< \xx ftk_XSI_ImageData XSI_ImageData \endxx template */
		XSI_IMAGE_FX,								/*!< \xx ftk_XSI_ImageFX XSI_ImageFX \endxx template */
		XSI_IMAGE_LIBRARY,							/*!< \xx ftk_XSI_ImageLibrary XSI_ImageLibrary \endxx template */
		XSI_MATERIAL,								/*!< \xx ftk_XSI_Material XSI_Material \endxx template */
		XSI_MATERIAL_INFO,							/*!< \xx ftk_XSI_MaterialInfo XSI_MaterialInfo \endxx template */
		XSI_MIXER,									/*!< \xx ftk_XSI_Mixer XSI_Mixer \endxx template */
		XSI_NURBS_PROJECTION,						/*!< \xx ftk_XSI_NurbsProjection XSI_NurbsProjection \endxx template */
		XSI_NURBS_TRIM,								/*!< \xx ftk_XSI_NurbsTrim XSI_NurbsTrim \endxx template */
		XSI_SHADER,									/*!< \xx ftk_XSI_Shader XSI_Shader \endxx template */
		XSI_SHADER_INSTANCE_DATA,					/*!< \xx ftk_XSI_ShaderInstanceData XSI_ShaderInstanceData \endxx template */
		XSI_STATIC_VALUES,							/*!< \xx ftk_XSI_StaticValue XSI_StaticValue \endxx template */
		XSI_TIMECONTROL,							/*!< \xx ftk_XSI_TimeControl XSI_TimeControl \endxx template */
		XSI_TRACK,									/*!< \xx ftk_XSI_Track XSI_Track \endxx template */
		XSI_USER_DATA,								/*!< \xx ftk_XSI_UserData XSI_UserData \endxx template */
		XSI_USER_DATA_LIST,							/*!< \xx ftk_XSI_UserDataList XSI_UserDataList \endxx template */
		XSI_SUB_COMPONENT_ATTRIBUTE_LIST,			/*!< \xx ftk_XSI_SubComponentAttributeList XSI_SubComponentAttributeList \endxx template */
		XSI_TRIANGLE_STRIP_LIST,					/*!< \xx ftk_XSI_TriangleStripList XSI_TriangleStripList \endxx template */
		XSI_TRIANGLE_LIST,							/*!< \xx ftk_XSI_TriangleList XSI_TriangleList \endxx template */
		XSI_POLYGON_LIST,							/*!< \xx ftk_XSI_PolygonList XSI_PolygonList \endxx template */
		XSI_VERTEX_LIST,							/*!< \xx ftk_XSI_VertexList XSI_VertexList \endxx template */
		XSI_SHAPE,									/*!< \xx ftk_XSI_Shape XSI_Shape \endxx template */
		XSI_MESH,									/*!< \xx ftk_XSI_Mesh XSI_Mesh \endxx template */
		XSI_SHAPE_ANIMATION,						/*!< \xx ftk_XSI_ShapeAnimation XSI_ShapeAnimation \endxx template */
		XSI_CLUSTER_INFO,							/*!< \xx ftk_XSI_ClusterInfo XSI_ClusterInfo \endxx template */
		XSI_USER_DATA_BLOB,							/*!< \xx ftk_XSI_UserDataBlob XSI_UserDataBlob \endxx template */
		XSI_TRANSFORM,								/*!< \xx ftk_XSI_Transform XSI_Transform \endxx template */
		XSI_LIMIT,									/*!< \xx ftk_XSI_Limit XSI_Limit \endxx template */
		XSI_BASEPOSE,								/*!< \xx ftk_XSI_BasePose XSI_BasePose \endxx template */
		COLLADA_MATERIAL,							/*!< COLLADA material template */
		COLLADA_EFFECT_LIBRARY,						/*!< COLLADA effect library template */
		COLLADA_EFFECT,								/*!< COLLADA effect template */
		COLLADA_EFFECT_COMMON_PROFILE,				/*!< COLLADA effect common profile template */
		COLLADA_EFFECT_CG_PROFILE,					/*!< COLLADA effect Cg profile template */
		COLLADA_EFFECT_COMMON_PARAM,				/*!< COLLADA effect common profile param template */
		COLLADA_EFFECT_COMMON_FLOAT,				/*!< COLLADA effect common profile float template */
		COLLADA_EFFECT_COMMON_COLOR,				/*!< COLLADA effect common profile color template */
		COLLADA_EFFECT_COMMON_TEXTURE,				/*!< COLLADA effect common profile texture template */
		COLLADA_EFFECT_COMMON_FLOAT_OR_PARAM,		/*!< COLLADA effect common profile float/param switch template */
		COLLADA_EFFECT_COMMON_COLOR_OR_TEXTURE,		/*!< COLLADA effect common profile color/param/texture switch template */
		COLLADA_EFFECT_COMMON_SHADER,				/*!< COLLADA effect common profile shader*/
		COLLADA_EFFECT_SETPARAM,					/*!< COLLADA setparam template */
		XSI_IK_RESOLUTIONPLANE,						/*!< \xx ftk_XSI_IK_ResolutionPlane XSI_IK_ResolutionPlane \endxx template */
		XSI_CAMERA,									/*!< \xx ftk_XSI_Camera XSI_Camera \endxx template */
		XSI_POLYMATRICKS,							/*!< \xx ftk_XSI_Polymatricks XSI_Polymatricks \endxx template */
		XSI_TRANSLATE,								/*!< \xx ftk_XSI_Translate XSI_Translate \endxx template */
		XSI_ROTATE,									/*!< \xx ftk_XSI_Rotate XSI_Rotate \endxx template */
		XSI_SCALE,									/*!< \xx ftk_XSI_Scale XSI_Scale \endxx template */
		XSI_SHEAR,									/*!< \xx ftk_XSI_Shear XSI_Shear \endxx template */
		XSI_LOOKAT,									/*!< \xx ftk_XSI_Lookat XSI_Lookat \endxx template */
		XSI_MATRIX,									/*!< \xx ftk_XSI_Matrix XSI_Matrix \endxx template */
		XSI_SHAPEREFERENCE,							/*!< \xx ftk_XSI_ShapeReference XSI_ShapeReference \endxx template */
		XSI_ACTIONCLIPCONTAINER,					/*!< \xx ftk_XSI_ActionClipContainer XSI_ActionClipContainer \endxx template */
		XSI_INDEX_LIST,								/*!< \xx ftk_XSI_IndexList XSI_IndexList \endxx template */
		XSI_CAMERA_FOCALLENGTH,						/*!< \xx ftk_XSI_CameraFocalLength XSI_CameraFocalLength \endxx template */
		XSI_SHADER_MULTI_PORT_CONNECTION,			/*!< \xx ftk_XSI_ShaderMultiPortConnection XSI_ShaderMultiPortConnection \endxx template */
		XSI_IMAGE_FX2,								/*!< \xx ftk_XSI_ImageFX2 XSI_ImageFX2 \endxx template */
		XSI_TEXTURE_LAYER,							/*!< \xx ftk_XSI_TextureLayer XSI_TextureLayer \endxx template */
		XSI_TEXTURE_LAYER_PORT,						/*!< \xx ftk_XSI_TextureLayerPort XSI_TextureLayerPort \endxx template */
		XSI_USER_KEYWORD,							/*!< \xx ftk_XSI_UserKeyword XSI_UserKeyword \endxx template */
		XSI_CLIP_TO_PARENT,							/*!< \xx ftk_XSI_ClipToParent XSI_ClipToParent \endxx*/
		XSI_SHADER_COMPOUND,						/*!< \xx ftk_XSI_ShaderCompound XSI_ShaderCompound \endxx template */
		XSI_SHADER_COMPOUND_PORT,					/*!< \xx ftk_XSI_ShaderCompoundPort XSI_ShaderCompoundPort \endxx template */
	};

	/*! The EFCurveType enum lists all animatable parameters.
	*/
	enum EFCurveType
	{
		SI_COLOR_R,				/*!< Color - Red component */
		SI_COLOR_G,				/*!< Color - Green component */
		SI_COLOR_B,				/*!< Color - Blue component */
		SI_POSITION_X,			/*!< Camera position in X */
		SI_POSITION_Y,			/*!< Camera position in Y */
		SI_POSITION_Z,			/*!< Camera position in Z */
		SI_ROLL,				/*!< Camera roll */
		SI_FOV,					/*!< Camera fov */
		SI_NEAR,				/*!< Camera near plane */
		SI_FAR,					/*!< Camera far plane */
		SI_INTEREST_X,			/*!< Camera interest position in X */
		SI_INTEREST_Y,			/*!< Camera interest position in Y */
		SI_INTEREST_Z,			/*!< Camera interest position in Z */
		SI_CONE,				/*!< Light cone angle */
		SI_SPREAD,				/*!< Light spread */
		SI_ORIENTATION_X,		/*!< Light orientation in X */
		SI_ORIENTATION_Y,		/*!< Light orientation in Y */
		SI_ORIENTATION_Z,		/*!< Light orientation in Z */
		SI_DIFFUSE_R,			/*!< Material diffuse - Red component */
		SI_DIFFUSE_G,			/*!< Material diffuse - Green component */
		SI_DIFFUSE_B,			/*!< Material diffuse - Blue component */
		SI_DIFFUSE,				/*!< Material diffuse */
		SI_PARAMETER,			/*!< Named parameter */
		SI_POWER,				/*!< Material specular power */
		SI_SPECULAR_R,			/*!< Material specular - Red component */
		SI_SPECULAR_G,			/*!< Material specular - Green component */
		SI_SPECULAR_B,			/*!< Material specular - Blue component */
		SI_EMISSIVE_R,			/*!< Material emissive - Red component */
		SI_EMISSIVE_G,			/*!< Material emissive - Green component */
		SI_EMISSIVE_B,			/*!< Material emissive - Blue component */
		SI_AMBIENT_R,			/*!< Material ambient - Red component */
		SI_AMBIENT_G,			/*!< Material ambient - Green component */
		SI_AMBIENT_B,			/*!< Material ambient - Blue component */
		SI_SCALING_X,			/*!< Scaling in X */
		SI_SCALING_Y,			/*!< Scaling in Y */
		SI_SCALING_Z,			/*!< Scaling in Z */
		SI_ROTATION_X,			/*!< Rotation in X */
		SI_ROTATION_Y,			/*!< Rotation in Y */
		SI_ROTATION_Z,			/*!< Rotation in Z */
		SI_TRANSLATION_X,		/*!< Translation in X */
		SI_TRANSLATION_Y,		/*!< Translation in Y */
		SI_TRANSLATION_Z,		/*!< Translation in Z */
		SI_SHPANIM,				/*!< ShapeAnimation */
		SI_NODEVIS,				/*!< Visibility */
		SI_HUE,					/*!< ImageFX hue */
		SI_GAIN,				/*!< ImageFX gain */
		SI_SATURATION,			/*!< ImageFX saturation */
		SI_BRIGHTNESS,			/*!< ImageFX brightness */
		SI_BLUR_RADIUS,			/*!< ImageFX blur */
		SI_BLUR_AMOUNT,			/*!< ImageFX blur */
		SI_BLUR_ALPHA,			/*!< ImageFX blur */
		SI_SCALING_TYPE,		/*!< ImageFX scale type */
		SI_SCALE_X,				/*!< ImageFX scale in X */
		SI_SCALE_Y,				/*!< ImageFX scale in Y */
		SI_FLIP_X,				/*!< ImageFX flip in X */
		SI_FLIP_Y,				/*!< ImageFX flip in Y */
		SI_RGBA2GRAYSCALE,		/*!< ImageFX rgba to grayscale */
		SI_BITS_PER_CHANNEL,	/*!< ImageFX bits per channel */
		SI_CROP_MIN_X,			/*!< ImageClip crop - minimum in X */
		SI_CROP_MAX_X,			/*!< ImageClip crop - maximum in X */
		SI_CROP_MIN_Y,			/*!< ImageClip crop - minimum in Y */
		SI_CROP_MAX_Y,			/*!< ImageClip crop - maximum in Y */
		SI_FALLOFF_ACTIVE,		/*!< Light falloff active */
		SI_FALLOFF_START,		/*!< Light falloff start */
		SI_FALLOFF_END,			/*!< Light falloff end */
		SI_SHADOWS_ENABLED,		/*!< Light shadows enabled */
		SI_UMBRA,				/*!< Light umbra */
		SI_LIGHT_AS_ENERGY,		/*!< Light as energy */
		SI_ENERGY_FACTOR,		/*!< Light energy factor */
		SI_INTENSITY,			/*!< Light intensity */
	};

	/*! The EFCurveInterpolationType enum contains possible interpolation types for an fcurve
	*/
	enum EFCurveInterpolationType
	{
		SI_CONSTANT,	/*!< Constant type */
		SI_LINEAR,		/*!< Linear type */
		SI_HERMITE,		/*!< Hermite type */
		SI_BEZIER,		/*!< Bezier type */
		SI_CUBIC,		/*!< Cubic type */
	};

	/*! The ERotationOrder enum contains possible rotation order for the
		\xx ftk_XSITransform XSITransform \endxx template.
	*/
	enum ERotationOrder
	{
		SI_XYZ,				/*!< XYZ rotation order */
		SI_XZY,				/*!< XZY rotation order */
		SI_YXZ,				/*!< YXZ rotation order */
		SI_YZX,				/*!< YZX rotation order */
		SI_ZXY,				/*!< ZXY rotation order */
		SI_ZYX,				/*!< ZYX rotation order */
	};

	/*! Constructor
		\param[in] in_pScene		Pointer to scene
		\param[in] in_pParentModel	Pointer to containing model
		\param[in] in_pTemplate		Pointer to dotXSI template
	*/
    CSLTemplate(CSLScene* in_pScene, CSLModel *in_pParentModel, CdotXSITemplate* in_pTemplate);
    virtual ~CSLTemplate();

	/*!	Sets the template name.
		\param[in] in_szNewName Name for the new template
	*/
    SI_Void SetName( const SI_Char *in_szNewName );

	/*!	Returns the template name.
	*/
    SI_Char* GetName();

	/*!	Returns the model parent of this template.
		\return Pointer to the parent model.
	*/
    CSLModel* ParentModel();

	/*!	Returns the current scene object.
		\return Pointer to the scene.
	*/
    CSLScene* Scene();

	/*!	Returns the Crosswalk SDK object associated with this template.
		\return Pointer to a Crosswalk SDK template.
	*/
    CdotXSITemplate* Template();

	// FCurve manipulation functions
	/*!	Creates a new FCurve on this template.
		\param[in]	in_Type		Type of fcurve to create
		\param[in]	in_InterpolationType	Type of interpolation for the fcurve
		\return Pointer to the newly created fcurve.
	*/
    CSLFCurve* CreateFCurve(EFCurveType in_Type, EFCurveInterpolationType in_InterpolationType);

	/*!	Creates a new FCurve on this template.
		\param[in]	in_szParameterName	Name of the parameter
		\param[in]	in_InterpolationType	Type of interpolation for the fcurve
		\return Pointer to the newly created fcurve.
	*/
    virtual CSLFCurve* CreateParameterFCurve(SI_Char* in_szParameterName, EFCurveInterpolationType in_InterpolationType);


	/*!	Destroys an existing FCurve on this template.
		\param[in]	in_Type	Type of fcurve to destroy
		\return Error code.
	*/
	SI_Error DestroyFCurve(EFCurveType in_Type);

	/*!	Removes a specific FCurve on this template.
		\param[in]	in_Index
		\return FCurve removed.
	*/
	CSLFCurve* RemoveFCurveAt(SI_Int in_Index);

	/*!	Lists all fcurves on the template.
		\return Array of pointers to fcurves.
	*/
	CSLFCurve **FCurves();

	/*!	Returns the number of fcurves currently present on the template.
		\return Number of fcurves.
	*/
	SI_Int GetFCurveCount();

	/*!	Returns a specific fcurve on the template.
		\param[in]	in_Type	Type of fcurve to retrieve.
		\return Pointer to the specified fcurve.
	*/
	CSLFCurve* GetSpecificFCurve(EFCurveType in_Type);

	/*!	Returns a specific fcurve on the template.
		\param[in]	in_szParameterName	Name of the parameter's FCurve to find
		\return Pointer to the specified fcurve.
	*/
	CSLFCurve* GetParameterFCurve(SI_Char* in_szParameterName);

	/*!	Removes all fcurves on the template.
		\return Error code.
	*/
	SI_Error ClearFCurves();

	// Custom parameter set manipulation functions.
	//todo : respect naming convention.


	/*!	Adds a custom pset to the template
		\return Pointer to the newly created custom pset, NULL if failed
	*/
	CSLCustomPSet* AddCustomPSet();

	/*!	Clears all the custom psets on that template
		\return whether the function failed or succeeded
	*/
	SI_Error ClearCustomPSets();

	/*!	Returns the list of custom psets on that template
		\return Array of custom psets instances
	*/
	CSLCustomPSet** GetCustomPSetList();

	/*!	Returns the custom pset with that name
		\param[in] in_pName Name of custom pset to retrieve
		\return the found custom pset
	*/
	CSLCustomPSet* FindCustomPSet(char *in_pName);

	/*!	Returns the number of custom psets on that template
		\return the number of custom psets on that template
	*/
	SI_Int GetCustomPSetCount();

	/*!	Removes a custom pset by index
		\param[in] in_nIndex Index of custom pset to remove
		\return whether the function failed or succeeded
	*/
	SI_Error RemoveCustomPSet(SI_Int in_nIndex);

	/*!	Removes a custom pset by name
		\param[in] in_pToRemove Custom pset to remove
		\return whether the function failed or succeeded
	*/
	SI_Error RemoveCustomPSet(CSLCustomPSet *in_pToRemove);

	// Connection functions.
	/*!	Connects an fcurve to this template
		\param[in]	in_pNewFCurve	the fcurve to connect
		\return Pointer to the specified fcurve.
	*/
	CSLFCurve *ConnectFCurve(CSLFCurve *in_pNewFCurve);

	/*!	Connects a custom pset to this template
		\param[in]	in_pNewCustomPSet	the custom pset to connect
		\return Pointer to the specified custom pset
	*/
	CSLCustomPSet *ConnectCustomPSet(CSLCustomPSet *in_pNewCustomPSet);

	/*!	Cleans invalid data from the template.
		\return Error code
	*/
	virtual SI_Error Fix();

	/*!	Synchronizes to ensure that the animated parameter is up to date.
		\return Error code
	*/
    virtual SI_Error Synchronize();

	/*!	Indicates which dotXSI template this object describes.
		\return Type of template
	*/
    virtual ETemplateType Type() = 0;

	/*!	Returns a proxy to the specified parameter.
		\param[in]	in_szName	Name of the parameter
		\return Pointer to a parameter proxy.
	*/
    virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);

	/*!	Returns a proxy to the specified parameter.
		\param[in]	in_Type	Type of parameter
		\param[in]	in_szParameterName	Name of the parameter if the type is SI_PARAMETER
		\return Pointer to a parameter proxy.
	*/
    virtual CSLAnimatableType* ParameterFromType(EFCurveType in_Type, SI_Char *in_szParameterName);

	/*!	Returns the object's fullname (Softimage path).
		\return Pointer to a string containing the object's fullname (Softimage path).
	*/
	virtual SI_Char* FullName();

	/*!	Connects a user data blob to this template
		\param[in]	in_pNewUserDataBlob	the user data blob to connect
		\return Pointer to the specified user data blob
	*/
	CSLUserDataBlob *ConnectUserDataBlob(CSLUserDataBlob *in_pNewUserDataBlob);


	/*!	Adds a user data blob to the template
		\return Pointer to the newly created user data blob, NULL if failed
	*/
	CSLUserDataBlob* AddUserDataBlob();

	/*!	Clears all the user data blobs on that template
		\return whether the function failed or succeeded
	*/
	SI_Error ClearUserDataBlobs();

	/*!	Returns the list of user data blobs on that template
		\return array of user data blobs instances
	*/
	CSLUserDataBlob** GetUserDataBlobList();

	/*!	Returns the number of user data blobs on that template
		\return the number of user data blobs on that template
	*/
	SI_Int GetUserDataBlobCount();

	/*!	Removes a user data blob by index
		\param[in] in_nIndex Index of blob to remove
		\return whether the function failed or succeeded
	*/
	SI_Error RemoveUserDataBlob(SI_Int in_nIndex);

	/*!	Removes a user data blob by name
		\param[in] in_pToRemove Blob to remove
		\return whether the function failed or succeeded
	*/
	SI_Error RemoveUserDataBlob(CSLUserDataBlob *in_pToRemove);

	/*! Returns the CSLXSIUserKeyword object
		\return The CSLXSIUserKeyword object if it exists, NULL if not.
	*/
	CSLXSIUserKeyword* GetUserKeyword();

	/*! Creates a CSLXSIUserKeyword object
		\return The CSLXSIUserKeyword object
	*/
	CSLXSIUserKeyword*	CreateUserKeyword();

	/*! Connects an existing CSLXSIUserKeyword object to the template
		\param[in]	in_pToConnect	The new CSLXSIUserKeyword
		\return The old CSLXSIUserKeyword
	*/
	CSLXSIUserKeyword* ConnectUserKeyword(CSLXSIUserKeyword* in_pToConnect);

	/*!	Returns the name (string) of a specified parameter.
		\param[in]	in_pParameter	The parameter
		\return Name of the parameter.
	*/
    virtual const SI_Char* GetParameterName(CSLAnimatableType* in_pParameter);

	/*! Checks if the version of dotXSI file exports with full names (e.g. "model.name") or just the name
		\retval true if the full name is exported for this version
	*/
	SI_Bool AreFullNamesExported();

	SI_Error Connect ( CdotXSITemplate* in_pConnection );


	/*!	Evalutes this class using the given time value
		\param[in]	in_fTime	The time
		\retval	SI_Error::SI_SUCCESS
	*/
	virtual SI_Error Evaluate( SI_Float in_fTime );

protected:
	/*! Resets the Parent to the given parent
		\param[in] in_pNewParent
		\retval SI_Error::SI_SUCCESS if successfull
	*/

	SI_Error SetParent( CSLModel *in_pNewParent );
	CSLAnimatableType**	m_pConnectionMap;

    CSIBCArray<CSLCustomPSet *>		m_CustomPSets;
	CSIBCArray<CSLFCurve *>			m_FCurves;
    CSIBCArray<CSLUserDataBlob *>	m_UserDataBlobs;

private:
	CSLFCurve* CreateCOLLADAFCurve(EFCurveType in_Type, EFCurveInterpolationType in_InterpolationType);
	CSLFCurve* CreateCOLLADAParameterFCurve(SI_Char* in_szParameterName, EFCurveInterpolationType in_InterpolationType);

	CdotXSITemplate*				m_pTemplate;
    CSLScene*						m_pScene;
    CSLModel*						m_pParentModel;
	CSIBCString*					m_szFullName;
	CSLXSIUserKeyword*				m_pUserKeyword;
	void*							m_pReserved;
};

#endif
