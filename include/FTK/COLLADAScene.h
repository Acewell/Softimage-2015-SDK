//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file COLLADAScene.h
	\brief Defines the CSLCOLLADAScene and CSLCOLLADALibrary classes

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _COLLADASCENE_H
#define _COLLADASCENE_H

#include "Template.h"
#include "Logger.h"
#include "Scene.h"
#include "COLLADATemplate.h"
#include "COLLADAMaterialLibrary.h"
#include "COLLADAEffectLibrary.h"
#include <SIBCArray.h>
#include <SIBCStringTable.h>

#if defined(unix)
# include <unistd.h>
# include <limits.h>
# if !defined(MAX_PATH)
#  define MAX_PATH PATH_MAX
# endif
#endif


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


typedef struct tagTemplateMap
{
	CCOLLADATemplate*	m_pCollada;
	CdotXSITemplate*	m_pLegacy;
} TemplateMap;

typedef struct tagSkinMap
{
	CCOLLADATemplate*	m_pSkinTemplate;
	CSLModel*			m_pEnvelope;
} SkinMap;


typedef struct tagSIDMap {
	CSLTemplate*				m_pTemplate;
	SI_Int						m_hSID;
	CSLAnimatableType*			m_pProxy;
	CSLTemplate::EFCurveType	m_CurveType;
	SI_Int						m_hXSIName;
} SIDMap;

typedef struct tagUnresolvedMaterialMap
{
	CSLCOLLADAMaterial*	m_pMaterial;
	CCOLLADATemplate*	m_pEffectTemplate;
	CCOLLADATemplate*	m_pInstanceEffect;
} UnresolvedMaterialMap;

/*! This class is a specialization of the CCOLLADATemplate class and stores a specific collection of data.

	Each library has a unique ID and is associated with one of the following classifications:
	\li \c effects		Corresponds to a CSLCOLLADAEffectLibrary
	\li \c geometries	Library for CSLGeometry data
	\li \c images		Library for CSLImageLibrary data
	\li \c materials	Corresponds to a CSLCOLLADAMaterialLibrary
	\li \c scenes		Library for a CSLCOLLADAScene

	To retrieve a specific library, use the GetLibrary::GetLibrary function with one of these classifications.
	For example,
	\code CSLCOLLADALibrary* l_pMatLib = GetLibrary("materials"); \endcode
	or
	\code CSLCOLLADALibrary* l_pEffectLibrary = GetLibrary("effects"); \endcode
	etc.
*/
class XSIEXPORT CSLCOLLADALibrary : public CCOLLADATemplate
{
public:
	/*! Constructor
		\param[in]	in_pParent	Containing template
		\param[in]	in_szName	Name for the new template
	*/
	CSLCOLLADALibrary(CCOLLADATemplate* in_pParent, const SI_Char* in_szName);
	/*! Destructor
	*/
	virtual ~CSLCOLLADALibrary();

	/*! Returns the template for the specified scene.
	\note This function is valid for \c library_visual_scenes only.
	\param[in] in_pScene Scene to get the template for
	\return Scene template
	*/
	CdotXSITemplate*	GetSceneTemplate(CSLCOLLADAScene* in_pScene);

	/*! Creates and returns an ID for the specified template.
	\return Template ID
	*/
	SI_Char*			GenerateID();

private:
	char				m_szSuffix[MAX_PATH];
	char				m_szID[MAX_PATH];
	LONG				m_iCount;
};

/*! This is the top level object for a dotXSI abstraction using the \xx ftk_TheSemanticLayer SemanticLayer \endxx.
From this class, you can access all the models, primitives, material etc. contained in the dotXSI.
*/
class XSIEXPORT CSLCOLLADAScene : public CSLScene
{
public:
	///////////////////////////////////////////////////////////////////////////
	// Construction/destruction
	///////////////////////////////////////////////////////////////////////////
	CSLCOLLADAScene();
	virtual ~CSLCOLLADAScene();

	static CSLCOLLADAScene * CreateScene();

	/*!	Cleans invalid data from the template.
	\return	Success/failure
	*/
	virtual SI_Error Fix();
	/*!	Ensures that the animated parameter is up to date.
	\return	Success/failure
	*/
	virtual SI_Error Synchronize();
	/*!	Writes a dotXSI file containing the data present in the semantic layer.
	\return	Success/failure
	*/
	virtual SI_Error Write();
	/*!	Writes a dotXSI file containing the data present in the semantic layer.
	\param[in]	in_szFileName	File to create.
	\param[in]	in_bSynchronize	True to synchronize all data within the Crosswalk SDK
	\return	Success/failure
	*/
	virtual SI_Error Write(SI_Char* in_szFileName, bool in_bSynchronize = true);
	/*!	Creates an image library
	\return	The new image library
	*/
	virtual CSLImageLibrary* CreateImageLibrary();
	/*!	Creates an envelope list
	\return	The new envelope list
	*/
	virtual CSLEnvelopeList* CreateEnvelopeList();

	/*! Adds a template to the extra list
	\param[in] in_pExtra Template to add
	*/
	void	AddExtra( CCOLLADATemplate* in_pExtra );

	/*! Returns a named COLLADA library
	\param[in] in_szLibrarySuffix Name of library to retrieve. See the main CSLCOLLADALibrary
		reference page for a list of valid values
	\return Requested library
	*/
	CSLCOLLADALibrary*	GetLibrary( const SI_Char* in_szLibrarySuffix );

	/*! Sets whether or not to export extra templates
	\param[in] in_bExtra True to export extras
	*/
	SI_Void	ExportExtra ( bool in_bExtra ) { m_bExportExtra = in_bExtra; };
	/*! Returns whether or not to export extra templates
	\retval true to export extras
	\retval false otherwise
	*/
	bool ExportExtra() { return m_bExportExtra; };

	/*! Generates a unique ID for an object and instantiates an element for it in the scene
	\param[in] in_pNode			Element to instantiate
	\param[in] in_pLib			Library to associate with this instance
	\param[in] in_szLibSuffix 	Type of associated library. See the main CSLCOLLADALibrary
		reference page for a list of valid values
	*/
	SI_Void	GenerateIDAndInstanciate ( CCOLLADATemplate *in_pNode, CCOLLADATemplate *in_pLib, const SI_Char* in_szLibSuffix );

	/*! Generates a unique ID for a scene and instantiates the visual scene in the scene template
	\param[in] in_pScene			Scene to instantiate
	*/
	SI_Void	InstanciateScene ( CCOLLADATemplate *in_pScene );

	/*! Returns the instantiated scene template
	*/
	CCOLLADATemplate*		GetInstanciatedSceneTemplate ();

	/*! Changes an existing instantiated element to another library and URL (useful for controllers)
	\param[in] in_szNodeID			Element ID to search for
	\param[in] in_szNewLib			Name of library to switch to
	\param[in] in_szNewURL			Name of URL to switch to
	\return Success/failure
	*/
	SI_Bool	ChangeNodeInstanciation		( SI_Char* in_szNodeID, SI_Char* in_szNewLib, SI_Char* in_szNewURL );

	/*! Returns the Effect Library object associated with this scene.
	\return The Effect Library object
	*/
	virtual CSLCOLLADAEffectLibrary* GetEffectLibrary();

	/*! Connects an existing CSLEffectLibrary object to the scene
	\param[in] in_pNewEffectLibrary		The new Effect Library
	\return The old Effect Library
	*/
	virtual CSLCOLLADAEffectLibrary* ConnectEffectLibrary(CSLCOLLADAEffectLibrary *in_pNewEffectLibrary);


	SI_Void	AddSIDMap ( CSLTemplate* in_pTemplate, const char* in_szSID,
						const char* in_szSIDSuffix, CSLAnimatableType* in_pProxy,
						CSLTemplate::EFCurveType in_CurveType, const char* in_szXSIName );
	SI_Void	ResetSIDMap();

	const char* GetString(SI_Int in_hString);
	SIDMap* ResolveTarget(CSLTemplate* in_pTemplate, char* in_szSID);
	SIDMap* ResolveTarget(char* in_szOwner, char* in_szSID);
	SIDMap* FindParameterSID(CSLAnimatableType* in_pParam);

	const char*		GetXSINameFromSIDTable ( CSLAnimatableType* in_pParam );

	SI_Void	AddSource ( CCOLLADATemplate *in_pParent,
								SI_Char* in_szName,
								SI_Char* in_szType,
								SI_TinyVariant* in_pData,
								SI_Long	in_lCount,
								SI_Long in_lStride,
								SI_Char* in_szAccessorType );

	/*! Returns the CCOLLADA template that corresponds to the root COLLADA xml elements
	\return The root COLLADA xml elements
	*/
	CCOLLADATemplate* GetRootTemplate() { return m_pRootTemplate; }

protected:

	virtual SI_Error RegisterAllCallbacks();
	virtual SI_Error PopulateScene();


	///////////////////////////////////////////////////////////////////////////
	// Helpers
	///////////////////////////////////////////////////////////////////////////

	void	FixWriteCallbacks( CdotXSITemplate* in_pTemplate);
	void	ReorderExtra( CdotXSITemplate* in_pTemplate);

	///////////////////////////////////////////////////////////////////////////
	// Members
	///////////////////////////////////////////////////////////////////////////

	CCOLLADATemplate*							m_pTechTemplate;
	CCOLLADATemplate*							m_pRootTemplate;
	CSLCOLLADAEffectLibrary*					m_pEffectLibrary;

	CSIBCArray<CSLCOLLADALibrary*>				m_Librairies;
	CSIBCArray<TemplateMap>						m_pReparentMap;
	bool										m_bExportExtra;
	CSIBCArray<CCOLLADATemplate*>				m_pInstanciatedNodes;
	CSIBCArray<SIDMap>							m_pSIDMap;
	CSIBCStringTable							m_pStringTable;

};

#endif
