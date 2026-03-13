//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file Scene.h
	\brief Defines the CSLUnresolvedElement and CSLScene classes, and the SLTemplateCallback structure

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _SCENE_H
#define _SCENE_H

#include "Template.h"
#include "Logger.h"

class CSLScene;
class CSLModel;
class CSLAmbience;
class CSLAngle;
class CSLCoordinateSystem;
class CSLFileInfo;
class CSLSceneInfo;
class CSLEnvelopeList;
class CSLMaterialLibrary;
class CSLFog;
class CSLActionFCurve;
class CSLFCurve;
class CSLTransform;
class CSLAction;
class CSLShapeAnimation;
class CSLVisibility;
class CSLXSIMaterial;
class CSLImageLibrary;
class CSLImage;
class CSLXSIShader;

/*! \brief This class is used internally when parsing the dotXSI file to resolve
	template references.
*/
class XSIEXPORT CSLUnresolvedElement
{
public:
	CSLUnresolvedElement
	(
		CSLTemplate *in_pUnresolvedObject,
		CSLTemplate *in_pUnresolvedParent = 0,
		SI_Char *in_pReferenceName = 0,
		void *in_pUserData = 0
	);

	/*! Returns the unresolved temlpate.
		\return The unresolved template.
	*/
	inline CSLTemplate* UnresolvedObject();

	/*! Returns the unresolved parent temlpate.
		\return The unresolved parent template.
	*/
	inline CSLTemplate* UnresolvedParent();

	/*! Returns the reference name.
		\return The name of the reference.
	*/
	inline SI_Char*	 ReferenceName();

	/*! Returns the user data attached to this object.
		\return User data.
	*/
	inline void*		 UserData();

private:
	CSLTemplate *m_pUnresolvedObject;
	CSLTemplate *m_pUnresolvedParent;
	SI_Char *m_pReferenceName;
	void *m_pUserData;

	// This member is here to allow future improvement of the class.
	void *m_pReserved;
};

inline CSLTemplate* CSLUnresolvedElement::UnresolvedObject()
{
	return m_pUnresolvedObject;
}

inline CSLTemplate* CSLUnresolvedElement::UnresolvedParent()
{
	return m_pUnresolvedParent;
}
inline SI_Char* CSLUnresolvedElement::ReferenceName()
{
	return m_pReferenceName;
}

inline void* CSLUnresolvedElement::UserData()
{
	return m_pUserData;
}

#ifdef	FTK_KERNEL
typedef std::multimap<const SI_Char *, CSLUnresolvedElement, StrLessPred> CSLUnresolvedMap;
typedef CSLUnresolvedMap::iterator CSLUnresolvedMapIterator;
typedef std::pair<CSLUnresolvedMapIterator,CSLUnresolvedMapIterator> CSLUnresolvedMapRange;

typedef SI_StrMap<CSLModel *> CSLModelMap;
typedef CSLModelMap::iterator CSLModelMapIterator;
#else
typedef	void CSLUnresolvedMap;
typedef	void CSLModelMap;
#endif

/*! This struct is used to keep track of things when a scene if first constructed during a Load call. The SLContext
	is passed to template callback handlers so the callbacks know the current model, the current parent etc.
*/
struct XSIEXPORT SLContext
{
public:
	SLContext();
	/*! Adds a new orphan template to the global orphan list. This list will be resolved
		at the very end of the load function
		\param[in] in_pOrphanTemplate Template to add
	*/
	SI_Void AddOrphan(CSLTemplate *in_pOrphanTemplate);

	CSLTemplate *m_pCurrentTemplate;					/*!< The current template*/
	CSLModel *m_pCurrentModel;							/*!< The current model*/
	CSLScene *m_pScene;									/*!< Pointer to the scene*/
	CSLMaterialLibrary *m_pMaterialLibrary;				/*!< Pointer to the material library*/
	CSLXSIMaterial *m_pCurrentMaterial;					/*!< The current material*/
	CSIBCArray<CSLTemplate *> *m_pOrphanList;			/*!< The global orphan list*/
	void *m_pTemplateUserData;							/*!< User data associated with templates*/
	CSLUnresolvedMap *m_pUnresolvedMap;					/*!< The unresolved template map*/
	CSLModelMap *m_pModelMap;							/*!< A list of all models*/
	CSLImageLibrary *m_pImageLibrary;					/*!< A pointer to the image library*/
	CSLImage *m_pCurrentImage;							/*!< The current image*/
	CSLXSIShader *m_pCurrentXSIShader;					/*!< The current shader*/
	void *m_pUserData;									/*!< Generic user data*/

private:
	// This member is here to allow future improvement of the class.
	void *m_pReserved;
};

typedef CSLTemplate *(*CSLCALLBACK) (CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
typedef SI_Error (*CSLPOSTCHILDRENCALLBACK) (CSLTemplate *in_pTemplate, SLContext *in_pContext);
typedef SI_Error (*CSLLOADCALLBACK) (SLContext *in_pContext);

/*! \brief A dotXSI template callback.

	This structure allows to specify callbacks that must be call when a specific template
	is found. You may specify a callback for the following events:
	\li \c PreLoadCallback ( Will be called before the entire is parsed)
	<br>This is useful for initialization needs
	\li \c Callback		( Will be called when the template is found )
	<br>This is where most of the work should be done. This is where Semantic Layer object are created using the template passed and are attached to the Scene.
	\li \c PostChilrenCallback ( Will be called when the template's children have been called )
	<br>This useful for resolving items within a model. For instance, if a parent template references on of it's children, you should resolve the references here.
	\li \c PostLoadCallback ( Will be called when the file has been loaded entirly )
	<br>This is useful for resolving items within the entire scene.
	\sa CSLScene::RegisterCallback
*/
class XSIEXPORT SLTemplateCallback
{
public:
	SLTemplateCallback();
	void Clear();

	CSLLOADCALLBACK m_PreLoadCallback;
	CSLCALLBACK m_Callback;
	CSLPOSTCHILDRENCALLBACK m_PostChildrenCallback;
	CSLLOADCALLBACK m_PostLibraryCallback;
	CSLLOADCALLBACK m_PostLoadCallback;

	void *m_pUserData;

private:
	// This member is here to allow future improvement of the class.
	void *m_pReserved;
};

/*! This class manages a scene (reading/writing scene data, etc.).

	This is the top level object for a dotXSI abstraction using the SemanticLayer. From
	this class, you can access all the models, primitives, materials etc.
*/

class XSIEXPORT CSLScene
{
public:
	///////////////////////////////////////////////////////////////////////////
	// Construction/destruction
	///////////////////////////////////////////////////////////////////////////
	CSLScene();
	virtual ~CSLScene();

	///////////////////////////////////////////////////////////////////////////
	// File manipulation functions.
	///////////////////////////////////////////////////////////////////////////
	/*! Opens a dotXSI file for reading and writing.
		The file must exist for the function to succeed.
		\param[in]	in_szFileName	File to open.
		\return Error code.
	*/
	SI_Error Open(SI_Char *in_szFileName);

	/*! Opens a dotXSI file for reading and writing.
		The file must exist for the function to succeed.
		\param[in]	in_szFileName	File to open.
		\param[in]	in_pFunc		read callback
		\return Error code.
	*/
	SI_Error Open(SI_Char *in_szFileName, SI_READ_CALLBACK_FNC in_pFunc);

	/*! Creates a new dotXSI file.
		\param[in]	in_szFileName		File to create.
		\param[in]	in_nVersionMajor	Major version of the file.
		\param[in]	in_nVersionMinor	Minor version of the file.
		\param[in]	in_nFormat			Format of the file (text or binary) for dotXSI
		\return Error code.
	*/
	SI_Error Create(SI_Char *in_szFileName, SI_Int in_nVersionMajor, SI_Int in_nVersionMinor, SI_Int in_nFormat = FORMAT_TEXT);

	/*! Creates a new dotXSI file.
		\param[in]	in_nVersionMajor	Major version of the file.
		\param[in]	in_nVersionMinor	Minor version of the file.
		\param[in]	in_nFormat			Format of the file (text or binary) for dotXSI
		\return Error code.
	*/
	SI_Error Create(SI_Int in_nVersionMajor, SI_Int in_nVersionMinor, SI_Int in_nFormat = FORMAT_TEXT);

	/*! Creates a new dotXSI file.
		\param[in]	in_parser	Parser to use
		\return Error code.
	*/
	SI_Error Open(CXSIParser * in_parser);

	/*! Populates the semantic layer with data present in the file.
		\return Error code.
	*/
	SI_Error Read();

	/*! Writes a dotXSI file containing the data present in the semantic layer.
		\param[in] in_bSynchronize True to synchronize
		\return Error code.
	*/
	virtual SI_Error Write(bool in_bSynchronize = true);

	/*! Writes a dotXSI file containing the data present in the semantic layer.
		\param[in]	in_szFileName	File to create.
		\param[in] in_bSynchronize True to synchronize
		\return Error code.
	*/
	virtual SI_Error Write(SI_Char* in_szFileName, bool in_bSynchronize = true);

	/*! Closes the opened/created file.
		\return Error code.
	*/
	SI_Error Close();

	/*! Finds a SI_Model by name
		\param[in]	in_szModelName	The model's name
		\return The model, or NULL if not found.
	*/
	CSLModel*			FindModel(SI_Char* in_szModelName);

	/*! Finds a SI_Model, recursively.
		\param[in]	in_szModelName	The model's name
		\param[in]	in_pModel		A Pointer to a CSLModel
		\return The model, or NULL if not found.
	*/
	CSLModel*			FindModelRecursively(SI_Char* in_szModelName, CSLModel* in_pModel);

	/*! Finds a parameter by name.
		\param[in]	in_szParameterName	The Softimage path to the parameter; that is, the scripting name for the parameter. For example
			"MyModel.kine.local.posx" would refer to the X component of the position in the model "MyModel" transformation matrix.
		\return The parameter.
	*/
	CSLAnimatableType*	FindParameter(SI_Char* in_szParameterName);

	/*! Returns a parameter value.
		\param[in]	in_szParameterName	The Softimage path to the parameter; that is, the scripting name for the parameter. For example
			"MyModel.kine.local.posx" would refer to the X component of the position in the model "MyModel" transformation matrix.
		\param[out]	out_pfValue			The parameter's value
		\return Error code
	*/
	SI_Error			GetValue(SI_Char* in_szParameterName, SI_Float* out_pfValue);

	/*! Sets a parameter value.
		\param[in]	in_szParameterName	The Softimage path to the parameter; that is, the scripting name for the parameter. For example
			"MyModel.kine.local.posx" would refer to the X component of the position in the model "MyModel" transformation matrix.
		\param[in]	in_fValue			The parameter's new value
		\return Error code
	*/
	SI_Error			SetValue(SI_Char* in_szParameterName, SI_Float in_fValue);

	///////////////////////////////////////////////////////////////////////////
	// Accessors
	///////////////////////////////////////////////////////////////////////////

	/*! Returns the ambience object.
		\return The ambience object
	*/
	CSLAmbience *Ambience();

	/*! Creates an Ambience object
		\return Pointer to the ambience object
	*/
	CSLAmbience *CreateAmbience();

	/*! Removes the Ambience object
		\return Error code
	*/
	SI_Error DestroyAmbience();

	/*! Returns the coordinatesystem object
		\return Pointer to the CoordinateSystem object
	*/
	CSLCoordinateSystem* CoordinateSystem();

	/*! Returns the EnvelopeList object
		\return Pointer to the EnvelopeList object
	*/
	CSLEnvelopeList* EnvelopeList();

	/*! Returns the Fog object
		\return Pointer to the Fog object
	*/
	CSLFog* Fog();

	/*! Returns the MaterialLibrary object
		\return Pointer to the MaterialLibrary object
	*/
	CSLMaterialLibrary* GetMaterialLibrary();

	/*! Returns the Root Model
		\return Pointer to the Root Model
	*/
	CSLModel *Root();

	/*! Returns the CXSIParser object
		\return Pointer to the CXSIParser object
	*/
	CXSIParser* Parser();

	/*! Returns the Angle object
		\return Pointer to the Angle object
	*/
	CSLAngle* Angle();

	/*! Returns the FileInfo object
		\return Pointer to the FileInfo object
	*/
	CSLFileInfo* FileInfo();

	/*! Returns the SceneInfo object
		\return Pointer to the object containing the scene information (\xx ftk_SI_Scene SI_Scene \endxx template)
	*/
	CSLSceneInfo* SceneInfo();

	/*! Returns the Logger object
		\return Pointer to the Logger object
	*/
	CSLLogger* Logger();

	/*! Returns the filename for the current scene
		\return The filename
	*/
	CSIBCString	&FileName();

	/*! Returns the image library
		\return Pointer to the image library or null if there's none
	*/
	CSLImageLibrary* GetImageLibrary();

	/*! Removes the Fog object
		\return Error code
	*/
	SI_Error DestroyFog();

	/*! Creates Fog
		\return Pointer to the Fog
	*/
	CSLFog* CreateFog();

	/*! Removes the EnvelopeList object
		\return Error code
	*/
	SI_Error DestroyEnvelopeList();

	/*! Creates an envelope list
		\return Pointer to the envelope list
	*/
	virtual CSLEnvelopeList* CreateEnvelopeList();

	/*! Creates an Image Library
		\return Pointer to the image library
		\since dotXSI 3.6
	*/
	virtual CSLImageLibrary* CreateImageLibrary();

	/*! Removes of the Image Library
		\return Error code
		\since dotXSI 3.6
	*/
	SI_Error DestroyImageLibrary();


	///////////////////////////////////////////////////////////////////////////
	// Connection functions.
	///////////////////////////////////////////////////////////////////////////

	/*! Connects an existing CSLMaterialLibrary object to the scene
		\param[in]	in_pNewMaterialLibrary	The new CSLMaterialLibrary
		\return Pointer to the old CSLMaterialLibrary
	*/
	virtual CSLMaterialLibrary* ConnectMaterialLibrary(CSLMaterialLibrary *in_pNewMaterialLibrary);

	/*! Connects an existing CSLAngle object to the scene
		\param[in]	in_pNewAngle	The new CSLAngle
		\return Pointer to the old CSLAngle object
	*/
	CSLAngle* ConnectAngle(CSLAngle *in_pNewAngle);

	/*! Connects an existing CSLFileInfo object to the scene
		\param[in]	in_pNewFileInfo	The new CSLFileInfo
		\return Pointer to the old CSLFileInfo object
	*/
	CSLFileInfo* ConnectFileInfo(CSLFileInfo *in_pNewFileInfo);

	/*! Connects an existing CSLSceneInfo object to the scene
		\param[in]	in_pToConnect	The new CSLSceneInfo
		\return Pointer to the old CSLSceneInfo object
	*/
	CSLSceneInfo* ConnectSceneInfo(CSLSceneInfo* in_pToConnect);

	/*! Connects an existing CSLFog object to the scene
		\param[in]	in_pNewFog	The new CSLFog
		\return Pointer to the old CSLFog object
	*/
	CSLFog* ConnectFog( CSLFog *in_pNewFog );

	/*! Connects an existing CSLAmbience object to the scene
		\param[in]	in_pNewAmbience	The new CSLAmbience
		\return Pointer to the old CSLAmbience object
	*/
	CSLAmbience* ConnectAmbience( CSLAmbience *in_pNewAmbience );

	/*! Connects an existing CSLCoordinateSystem object to the scene
		\param[in]	in_pNewCoordSystem	The new CSLCoordinateSystem
		\return Pointer to the old CSLCoordinateSystem object
	*/
	CSLCoordinateSystem* ConnectCoordinateSystem( CSLCoordinateSystem *in_pNewCoordSystem );

	/*! Connects an existing CSLEnvelopeList object to the scene
		\param[in]	in_pNewEnvList	The new CSLEnvelopeList
		\return Pointer to the old CSLEnvelopeList object
	*/
	CSLEnvelopeList* ConnectEnvelopeList( CSLEnvelopeList* in_pNewEnvList );

	/*! Connects Image library
		\note The parser must support 3.6 templates in order to connect an image library
		\param[in] in_pImageLibrary Pointer to the pre-allocated image library to connect
		\return Pointer to the newly connected image library or null if there's already an
			image library or if the parser does not support 3.6 templates
	*/
	CSLImageLibrary* ConnectImageLibrary( CSLImageLibrary* in_pImageLibrary );

	/*! Registers a new template callback
		\param[in]	in_pName				The template name
		\param[in]	in_pTemplateCallback	The template callback structure
		\return Error code

		\eg Adding a new template callback
		\code
			//
			// Remember the native callbacks
			//

			SLTemplateCallback* l_pOldCallback = Scene->Callback ( "SI_Mesh" );
			memcpy ( &m_sNativeCallbacks, l_pOldCallback, sizeof ( SLTemplateCallback ));

			//
			// Create new set of callbacks
			//

			SLTemplateCallback	l_NewCallbacks;
			memcpy ( &l_NewCallbacks, l_pOldCallback, sizeof ( SLTemplateCallback ));

			//
			// Add a PostChilren callback and keep the others to the default
			//

			l_NewCallbacks.m_PostChildrenCallback  = SIMeshPostRTPCallback;

			//
			// Register the new callbacks
			//

			in_pCurrentScene->RegisterCallback ( "SI_Mesh", &l_NewCallbacks );
		\endcode
	*/
	SI_Error RegisterCallback(SI_Char *in_pName, SLTemplateCallback *in_pTemplateCallback);

	/*! Unregisters a template callback
		\param[in]	in_pName	The template name
		\return Error code
	*/
	SI_Error UnregisterCallback(SI_Char *in_pName);

	/*! Unregisters all template callback
		\return Error code
	*/
	SI_Error UnregisterAllCallbacks();

	/*! Returns a callback by name
		\param[in]  in_pName	Template name
		\return Pointer to a callback struct
	*/
	SLTemplateCallback *Callback(SI_Char *in_pName);

	///////////////////////////////////////////////////////////////////////////
	// Coherancy functions
	///////////////////////////////////////////////////////////////////////////
	virtual SI_Error Fix();
	virtual SI_Error Synchronize();

	///////////////////////////////////////////////////////////////////////////
	// Utility functions
	///////////////////////////////////////////////////////////////////////////
	SI_Error RemoveTemplate(CdotXSITemplate *in_pElement);
	SI_Error ClearSLObjectArray(CSIBCArray<CSLTemplate *> *in_pArray);

	/*! Checks if the parser of the scene supports templates of a specific version of the dotXSI format
		\param[in] in_nMajor Major version of the parser
		\param[in] in_nMinor Minor version of the parser
		\retval true if the version is supported
		\retval false otherwise
	*/
	SI_Bool SupportsTemplates( SI_Int in_nMajor, SI_Int in_nMinor );

	/*! Sets the callback that receives warning messages
		\param[in] in_pfncCallback Callback function
	*/
	SI_Void SetWarningCallback ( SI_WARNING_CALLBACK_FNC in_pfncCallback ) { m_pfncCallback = in_pfncCallback; };

	/*! Sets the callback that gets call for reading every template
		\param[in] in_pfncCallback Callback function
	*/
	SI_Void SetReadCallback ( SI_READ_CALLBACK_FNC in_pfncCallback ) { m_pfncReadCallback = in_pfncCallback; };
	/*! Returns the refcount (how many others uses the specified template)
		\param[in]	in_ppObjects	which objects to check
		\param[out]	out_ppRefCounts	Counts for each one
		\param[in]	in_iObjectCount	How many objects in the array
		\param[in]	in_eType		Types (either CSLTemplate::SI_MODEL or CSLTemplate::SI_MATERIAL)
	*/
	SI_Error	GetRefCount( CSLTemplate				** in_ppObjects,
							 SI_Int						** out_ppRefCounts,
							 SI_Int					    in_iObjectCount,
							 CSLTemplate::ETemplateType in_eType );


	static CSLScene * CreateScene();
protected:

	SI_Error	GetRefCountRecursively		( CSLModel* in_pModel,
													CSLTemplate** in_ppObjects,
													SI_Int**	out_ppRefCounts,
													SI_Int		in_iObjectCount,
													CSLTemplate::ETemplateType in_eType );


protected:
	CSLModel	* FindFullyQualifiedObject( SI_Char * in_pName, SI_Char ** out_pContainer, SI_Char ** out_pParameter );
	virtual SI_Error PopulateScene();
	SI_Error ReadTemplateRecursively(CdotXSITemplate *in_pTemplate, SLContext *in_pContext);
	SI_Error ExecutePreLoadCallbacks(SLContext *in_pContext);
	SI_Error ExecutePostLibraryCallbacks(SLContext *in_pContext);
	SI_Error ExecutePostLoadCallbacks(SLContext *in_pContext);
	virtual SI_Error RegisterAllCallbacks();
	SI_Error Clear();

#ifdef	FTK_KERNEL
	typedef SI_StrMap<SLTemplateCallback> CSLCallbackMap;
	typedef CSLCallbackMap::iterator CSLCallbackMapIterator;
#else
	typedef	void	CSLCallbackMap;
#endif

	CSLSceneInfo* m_pSceneInfo;
	CSLFileInfo* m_pFileInfo;
	CSLAmbience* m_pAmbience;
	CSLAngle* m_pAngle;
	CSLFog* m_pFog;
	CSLEnvelopeList* m_pEnvelopeList;
	CSLMaterialLibrary* m_pMaterialLibrary;
	CSLCoordinateSystem* m_pCoordinateSystem;
	CXSIParser* m_pParser;
	CSLCallbackMap* m_pCallbackMap;
	CSLModel *m_pRoot;
	CSLLogger m_Logger;
	CSLImageLibrary *m_pImageLibrary;

	CSIBCString m_FileName;

	SI_WARNING_CALLBACK_FNC	m_pfncCallback;
	SI_READ_CALLBACK_FNC	m_pfncReadCallback;

	// This member is here to allow future improvement of the class.
	void *m_pReserved;
};

#endif
