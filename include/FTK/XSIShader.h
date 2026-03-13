//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSIShader.h
	\brief Defines the CSLXSIShader class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _XSISHADER_H
#define _XSISHADER_H

#include "Template.h"
class CSLVariantParameter;
class CSLShaderConnectionPoint;
class CSLShaderInstanceData;
class CSLImage;
class CSLXSIShaderMultiPortConnection;
class CSLXSITextureLayer;
class CSLXSIMaterial;
class CSLXSIShaderCompound;

/*! \brief This class represents an \xx ftk_XSI_Shader XSI_Shader \endxx template.

	Describes a single Shader node (see the \xx ftk_XSI_Shader XSI_Shader \endxx template reference).
	\sa CSLVariantParameter
	\sa CSLShaderConnectionPoint
	\sa CSLShaderInstanceData
	\sa CSLXSIShaderMultiPortConnection
	\sa CSLXSITextureLayer
	\since dotXSI 3.6
*/
class XSIEXPORT CSLXSIShader
    : public CSLTemplate
{
public:

	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pParentModel Parent model
		\param[in] in_pTemplate Refered template
		\param[in] in_pParentMaterial Parent material
	*/
	CSLXSIShader(CSLScene* in_pScene, CSLModel *in_pParentModel, CdotXSITemplate* in_pTemplate, CSLXSIMaterial* in_pParentMaterial = NULL);

	//! Destructor
	virtual ~CSLXSIShader();

	/*! Commits the current template information
		\return Whether or not the commit was successful
	*/
	SI_Error Synchronize();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_SHADER The type of this template
	*/
	CSLTemplate::ETemplateType Type(){ return XSI_SHADER; }

	// Parameters Functionality ///////////////////////////////////////////////
	/*! Adds a parameter to the parameter list
		\return Pointer to the newly added parameter
	*/
	CSLVariantParameter* AddParameter();

	/*! Removes a parameter from the parameter list
		\param[in] in_nIndex Index of the parameter to remove
		\return Whether or not the parameter could be removed
	*/
	SI_Error RemoveParameter( SI_Int in_nIndex );

	/*! Removes a parameter from the parameter list
		\param[in] in_pToRemove Pointer to the parameter to remove
		\return Whether or not the parameter could be removed
	*/
	SI_Error RemoveParameter( CSLVariantParameter* in_pToRemove );

	/*! Removes all parameters from the parameter list
		\return Whether or not the list could be cleared
	*/
	SI_Error ClearParameters();

	/*! Adds an exisiting parameter to the parameter list
		\param[in] in_pToConnect Pointer to the parameter to add
		\return The added parameter or null if it already exists in the list
	*/
	CSLVariantParameter* ConnectParameter( CSLVariantParameter* in_pToConnect );

	/*! Returns a pointer to the internally-stored parameter pointer list
		\return Pointer to the list
	*/
	CSLVariantParameter** GetParameterList();

	/*! Finds a parameter by its name
		\param[in] in_pName Name of parameter to find
		\return the parameter
	*/
	CSLVariantParameter* FindParameterByName(char *in_pName);

	/*! Returns the total number of parameters
		\return Number of parameters
	*/
	SI_Int GetParameterCount();

	/*! Searches for a parameter by name
		\param[in] in_szName Name of the parameter to look for
		\return Pointer to the found parameter or null if not found
	*/
	virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);
    virtual CSLAnimatableType* ParameterFromType(EFCurveType in_Type, SI_Char *in_szParameterName);

	// Connection points functionality ////////////////////////////////////////

	/*! Adds a connection point to the connection point list
		\return Pointer to the newly added connection point
	*/
	CSLShaderConnectionPoint* AddConnectionPoint();

	/*! Removes a connection point from the connection point list
		\param[in] in_nIndex Index of the connection point to remove
		\return Whether or not the connection point could be removed
	*/
	SI_Error RemoveConnectionPoint( SI_Int in_nIndex );

	/*! Removes a connection point from the connection point list
		\param[in] in_pToRemove Pointer to the connection point to remove
		\return Whether or not the connection point could be removed
	*/
	SI_Error RemoveConnectionPoint( CSLShaderConnectionPoint* in_pToRemove );

	/*! Removes all connections points from the connection point list
		\return Whether or not the list could be cleared
	*/
	SI_Error ClearConnectionPoints();

	/*! Adds an exisiting connection point to the connection point list
		\param[in] in_pToConnect Pointer to the connection point to add
		\return The added connection point or null if it already exists in the list
	*/
	CSLShaderConnectionPoint* ConnectConnectionPoint( CSLShaderConnectionPoint* in_pToConnect );

	/*! Returns a pointer to the internally-stored connection point pointer list
		\return Pointer to the list
	*/
	CSLShaderConnectionPoint** GetConnectionPointList();

	/*! Gets the total number of connection points
		\return Number of connection points
	*/
	SI_Int GetConnectionPointCount();

	// instance data functionality ////////////////////////////////////////

	/*! Retrieves a parameter from a model referenced by an instance
		data.

		\param[in] in_szParamName Name of the parameter to fetch.
		\param[in] in_pFromModel Pointer to the model to get the parameter from
		\return Pointer to the found parameter or NULL if the model or the parameter does not exist.
	*/
	CSLAnimatableType* GetParameterFromModel( SI_Char *in_szParamName, CSLModel *in_pFromModel );

	/*! Adds an instance data to the instance data list
		\return Pointer to the newly added instance data
	*/
	CSLShaderInstanceData* AddInstanceData();

	/*! Removes an instance data from the instance data list
		\param[in] in_nIndex Index of the instance data to remove
		\return Whether or not the instance data could be removed
	*/
	SI_Error RemoveInstanceData( SI_Int in_nIndex );

	/*! Removes an instance data from the instance data list
		\param[in] in_pToRemove Pointer to the instance data to remove
		\return Whether or not the instance data could be removed
	*/
	SI_Error RemoveInstanceData( CSLShaderInstanceData* in_pToRemove );

	/*! Removes all instance datas from the shader
		\return Whether or not the list could be cleared
	*/
	SI_Error ClearInstanceDatas();

	/*! Adds an exisiting instance data to the instance data list
		\param[in] in_pToConnect Pointer to the instance data to add
		\return The added instance data or null if it already exists in the list
	*/
	CSLShaderInstanceData* ConnectInstanceData( CSLShaderInstanceData* in_pToConnect );

	/*! Returns a pointer to the internally-stored instance data pointer list
		\return Pointer to the list
	*/
	CSLShaderInstanceData** GetInstanceDataList();

	/*! Returns the total number of instance datas
		\return Number of instance datas
	*/
	SI_Int GetInstanceDataCount();

	// Prog ID Accessors //////////////////////////////////////////////////////

	/*! Returns the ProgID
		\return Pointer to a string representing the ProgID
	*/
	SI_Char* GetProgID();

	/*! Sets the ProgID
		\param[in] in_szProgID Pointer to a string representing the ProgID
	*/
	SI_Void SetProgID( SI_Char* in_szProgID );

	/*! Connects a subshader to this shader
		\param[in] in_pSource pointer to the subshader to connect
		\param[in] in_pConnection name of the connection
	*/
	CSLShaderConnectionPoint *ConnectShader( CSLXSIShader *in_pSource, char *in_pConnection);

	/*! Connects an image to this shader
		\param[in]	in_pSource	Image to connect to this shader
		\param[in]	in_pConnection name of the connection
	*/
	CSLShaderConnectionPoint  *ConnectImage(CSLImage *in_pSource, char *in_pConnection);

	// Output Type Accessors //////////////////////////////////////////////////
	//! Output types
	enum EOutputType
	{
		SI_OT_UNKNOWN,		/*!< Unknown output type */
		SI_OT_BOOLEAN,		/*!< Boolean shader output type */
		SI_OT_INTEGER,		/*!< Integer shader output type */
		SI_OT_SCALAR,		/*!< Scalar shader output type */
		SI_OT_COLOR,		/*!< Color shader output type */
		SI_OT_VECTOR,		/*!< Vector shader output type */
		SI_OT_TEXTURE_SPACE,/*!< Texture space shader output type */
		SI_OT_TEXTURE,		/*!< Texture shader output type */
		SI_OT_STRING,		/*!< String shader output type */
		SI_OT_FILENAME,		/*!< Filename shader output type */
		SI_OT_LENS,			/*!< Lens shader output type */
		SI_OT_LIGHT,		/*!< Light shader output type */
		SI_OT_MATERIAL,		/*!< Material shader output type */
		SI_OT_MODEL,		/*!< Model shader output type */
		SI_OT_MULTI,		/*!< Multiple output port shader */
	};

	/*! Returns the OutputType
		\return The output type
	*/
	EOutputType GetOutputType();

	/*! Sets the OutputType
		\param[in] in_OutputType New output type to use
	*/
	SI_Void SetOutputType( EOutputType in_OutputType );

	// Multi Port Connection functionality ////////////////////////////////////////

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
		\param[in] in_pParameter						Name of the multi port connection parameter you're looking for
		\return Pointer to the CSLXSIShaderMultiPortConnection found or NULL if not found
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

	// Texture Layer functionality ////////////////////////////////////////

	/*! Adds a texture layer to the texture layer list
		\return The added texture layer
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

	/*!	Sets the material parent of this template.
		\param[in] in_pParentMaterial	Pointer to the parent material.
	*/
	void SetParentMaterial(CSLXSIMaterial* in_pParentMaterial);

	/*!	Returns the material parent of this template.
		\return Pointer to the parent material.
	*/
	CSLXSIMaterial* ParentMaterial();

	///////////////////////////////////////////////////////////////////////////
	// Shader Compound Functionality //////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	/*! Adds a Shader Compound object to identify this shader as a compound and
	    to store it's compound specific data.
		\return The new Shader Compound object or null if there's already one
	*/
	CSLXSIShaderCompound* CreateShaderCompound();

	/*! Destroys the Shader Compound
		\return Whether or not the Shader Compound could be destroyed
	*/
	SI_Error DestroyShaderCompound();

	/*! Connects an exisiting Shader Compound
		\param[in] in_pToConnect Pointer to the Shader Compound to use
		\return The added Shader Compound or null if there's already one
	*/
	CSLXSIShaderCompound* ConnectShaderCompound( CSLXSIShaderCompound* in_pToConnect );

	/*! Returns a pointer to the Shader Compound
		\return Pointer to the Shader Compound
	*/
	CSLXSIShaderCompound* ShaderCompound();

private:

	CSLShaderInstanceData* InstanceDataFromModel( CSLModel *in_pModel );

	CSIBCArray<CSLVariantParameter *> m_Parameters;
    CSIBCArray<CSLShaderConnectionPoint *> m_ConnectionPoints;
	CSIBCArray<CSLShaderInstanceData*> m_InstanceDatas;
    CSLEnumProxy<EOutputType, SI_OT_MULTI> m_OutputType;
    CSLStringProxy m_ProgID;
	CSIBCArray<CSLXSIShaderMultiPortConnection *> m_MultiPortConnections;
	CSIBCArray<CSLXSITextureLayer *> m_TextureLayers;
	CSLXSIMaterial* m_pParentMaterial;
	CSLXSIShaderCompound* m_pShaderCompound;

	SI_Void *m_pReserved;	// reserved for future use
};

#endif
