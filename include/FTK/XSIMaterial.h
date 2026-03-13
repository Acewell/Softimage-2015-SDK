//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSIMaterial.h
	\brief Defines the CSLXSIMaterial class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _XSIMATERIAL_H
#define _XSIMATERIAL_H

#include "Material.h"

class CSLConnectionPoint;
class CSLXSIShader;
class CSLXSIMaterialInfo;
class CSLXSIShaderMultiPortConnection;
class CSLXSITextureLayer;

/*! \brief Base class to describe a Material for dotXSI 5.0+ (see the \xx ftk_XSI_Material XSI_Material \endxx template reference).

	The role of this class is to help build a shader tree that describes an effect. They are containers of CSLXSIShader objects
	and CSLConnectionPoint objects.

	\tip To get more information on Materials, see the Autodesk Softimage documentation on the render tree and the
		\xt cus_shaders_hwrenderers Realtime Shaders \endxt SDK documentation.

	\since dotXSI 3.6
*/
class XSIEXPORT CSLXSIMaterial
    : public CSLBaseMaterial
{
public:
	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Refered template
	*/
    CSLXSIMaterial(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	//! Destructor
	virtual ~CSLXSIMaterial();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_MATERIAL The type of this template
	*/
	CSLTemplate::ETemplateType Type(){ return XSI_MATERIAL; }

	/*! Commits the current template information
		\return Whether or not the commit was successful
	*/
	SI_Error Synchronize();

	/*! Searches for a parameter
		\param[in] in_szName Name of the parameter to look for
		\return Pointer to the found parameter, null otherwise
	*/
	virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);

	///////////////////////////////////////////////////////////////////////////
	// Connection points functionality ////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	/*! Adds a connection point to the connection point list
		\return Pointer to the newly added connection point
	*/
	CSLConnectionPoint* AddConnectionPoint();

	/*! Removes a connection point from the connection point list
		\param[in] in_nIndex Index of the connection point to remove
		\return Whether or not the connection point could be removed
	*/
	SI_Error RemoveConnectionPoint( SI_Int in_nIndex );

	/*! Removes a connection point from the connection point list
		\param[in] in_pToRemove Pointer to the connection point to remove
		\return Whether or not the connection point could be removed
	*/
	SI_Error RemoveConnectionPoint( CSLConnectionPoint* in_pToRemove );

	/*! Removes all connections points from the connection point list
		\return Whether or not the list could be cleared
	*/
	SI_Error ClearConnectionPoints();

	/*! Adds an exisiting connection point to the connection point list
		\param[in] in_pToConnect Pointer to the connection point to add
		\return The added connection point or null if it already exists in the list
	*/
	CSLConnectionPoint* ConnectConnectionPoint( CSLConnectionPoint* in_pToConnect );

	/*! Returns a pointer to the internally-stored connection point pointer list
		\return Pointer to the list
	*/
	CSLConnectionPoint** GetConnectionPointList();

	/*! Returns the total number of connection points
		\return Number of connection points
	*/
	SI_Int GetConnectionPointCount();

	///////////////////////////////////////////////////////////////////////////
	// Shaders functionality //////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	/*! Adds a shader to the shader list
		\return to the newly added shader
	*/
	CSLXSIShader* AddShader();

	/*! Removes a shader from the shader list
		\param[in] in_nIndex Index of the shader to remove
		\return Whether or not the shader could be removed
	*/
	SI_Error RemoveShader( SI_Int in_nIndex );

	/*! Removes a shader from the shader list
		\param[in] in_pToRemove Pointer to the shader to remove
		\return Whether or not the shader could be removed
	*/
	SI_Error RemoveShader( CSLXSIShader* in_pToRemove );

	/*! Removes all connections points from the shader list
		\return Whether or not the list could be cleared
	*/
	SI_Error ClearShaders();

	/*! Adds an exisiting shader to the shader list
		\param[in] in_pToConnect Pointer to the shader to add
		\return The added shader or null if it already exists in the list
	*/
	CSLXSIShader* ConnectShader( CSLXSIShader* in_pToConnect );

	/*! Returns a pointer to the internally-stored shader pointer list
		\return Pointer to the list
	*/
	CSLXSIShader** GetShaderList();

	/*! Returns the total number of Shaders
		\return Number of Shaders
	*/
	SI_Int GetShaderCount();

	/*! Searches for a given shader
		\param[in] in_szShaderName Name of the shader to look for
		\return Pointer to the shader or null if it cannot be found
	*/
	CSLXSIShader* FindShader( SI_Char* in_szShaderName );

	///////////////////////////////////////////////////////////////////////////
	// Material Info functionality ////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	/*! Creates a new material info
		\return The new material info or null if there's already one
	*/
	CSLXSIMaterialInfo* CreateMaterialInfo();

	/*! Destroys the material info
		\return Whether or not the material info could be destroyed
	*/
	SI_Error DestroyMaterialInfo();

	/*! Connects an exisiting material info
		\param[in] in_pToConnect Pointer to the material info to use
		\return The added material info or null if there's already one
	*/
	CSLXSIMaterialInfo* ConnectMaterialInfo( CSLXSIMaterialInfo* in_pToConnect );

	/*! Returns a pointer to the material info
		\return Pointer to the material info
	*/
	CSLXSIMaterialInfo* GetMaterialInfo();

	///////////////////////////////////////////////////////////////////////
	// Multi Port Connection functionality ////////////////////////////////
	///////////////////////////////////////////////////////////////////////

	/*! Adds a multi port connection to the multi port connection list
		\return The added multi port connection
	*/
	CSLXSIShaderMultiPortConnection* AddMultiPortConnection();

	/*! Removes a multi port connection from the multi port connection list
		\param[in] in_nIndex	Index of the multi port connection to remove
	*/
	SI_Error RemoveMultiPortConnection(SI_Int in_nIndex);

	/*! Removes a multi port connection from the multi port connection list
		\param[in] in_pToRemove	The multi port connection to remove
	*/
	SI_Error RemoveMultiPortConnection(CSLXSIShaderMultiPortConnection* in_pToRemove);

	/*! Returns the CSLXSIShaderMultiPortConnection object of a given multi port connection by index.
		\param[in] in_nIndex	Index of the multi port connection to get
		\return The CSLXSIShaderMultiPortConnection that holds the name and the type of a multi port connection.
	*/
	CSLXSIShaderMultiPortConnection* GetMultiPortConnection(SI_Int in_nIndex);

	/*! Returns the CSLXSIShaderMultiPortConnection object of a given multi port connection by parameter name.
		\param[in] in_pParameter Name of the multi port connection parameter you're looking for
		\return Pointer to the CSLXSIShaderMultiPortConnection found or NULL ff not found
	*/
	CSLXSIShaderMultiPortConnection* GetMultiPortConnectionByParameter(SI_Char* in_pParameter);

	/*! Returns the number of multi port connection in the multi port connection list
		\return The number of multi port connection in the multi port connection list
	*/
	SI_Int GetMultiPortConnectionCount();

	/*! Deletes all the multi port connection form the multi port connection list
	*/
	SI_Error ClearMultiPortConnections();

	/*! Returns a pointer to the internally-stored multi port connection pointer list
		\return Pointer to the list
	*/
	CSLXSIShaderMultiPortConnection** GetMultiPortConnectionList();

	/*! Adds an exisiting multi port connection to the multi port connection list
		\param[in] in_pToConnect Pointer to the multi port connection to add
		\return The added multi port connection
	*/
	CSLXSIShaderMultiPortConnection* ConnectMultiPortConnection( CSLXSIShaderMultiPortConnection* in_pToConnect );

	/*! Searches the multi port connection list for one with a corresponding parameter name
		\param[in] in_pName The parameter name to look for
		\return Pointer on the multi port connection if found, NULL if not found
	*/
	CSLXSIShaderMultiPortConnection* FindMultiPortConnectionByParameterName(SI_Char *in_pName);

	///////////////////////////////////////////////////////////////////////
	// Texture Layer functionality ////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////

	/*! Adds a texture layer to the texture layer list
		\return	The added texture layer
	*/
	CSLXSITextureLayer* AddTextureLayer();

	/*! Removes a texture layer from the texture layer list
		\param[in] in_nIndex	Index of the texture layer to remove
	*/
	SI_Error RemoveTextureLayer(SI_Int in_nIndex);

	/*! Removes a texture layer from the texture layer list
		\param[in] in_pToRemove	The texture layer to remove
	*/
	SI_Error RemoveTextureLayer(CSLXSITextureLayer* in_pToRemove);

	/*! Returns the CSLXSITextureLayer object by index.
		\param[in] in_nIndex	Index of the texture layer to get
		\return The CSLXSITextureLayer.
	*/
	CSLXSITextureLayer* GetTextureLayer(SI_Int in_nIndex);

	/*! Searches the texture layer list for one with a corresponding order index
		\param[in] in_nOrder	The order index of the texture layer to look for
		\return Pointer on the texture layer if found, NULL if not found
	*/
	CSLXSITextureLayer* FindTextureLayerByOrder(SI_Int in_nOrder);

	/*! Returns the number of texture layer in the texture layer list
		\return The number of texture layer in the texture layer list
	*/
	SI_Int GetTextureLayerCount();

	/*! Deletes all the texture layer form the texture layer list
	*/
	SI_Error ClearTextureLayers();

	/*! Returns a pointer to the internally-stored texture layer pointer list
		\return Pointer to the list
	*/
	CSLXSITextureLayer** GetTextureLayerList();

	/*! Adds an exisiting texture layer to the texture layer list
		\param[in] in_pToConnect Pointer to the texture layer to add
		\return The added texture layer
	*/
	CSLXSITextureLayer* ConnectTextureLayer( CSLXSITextureLayer* in_pToConnect );

// Members
private:
    CSIBCArray<CSLConnectionPoint*> m_ConnectionPoints;
    CSIBCArray<CSLXSIShader*> m_Shaders;
	CSLXSIMaterialInfo *m_pMaterialInfo;
	CSIBCArray<CSLXSIShaderMultiPortConnection *> m_MultiPortConnections;
	CSIBCArray<CSLXSITextureLayer*> m_TextureLayers;

	SI_Void *m_pReserved;	// reserved for future use
};

#endif // _XSIMATERIAL_H
