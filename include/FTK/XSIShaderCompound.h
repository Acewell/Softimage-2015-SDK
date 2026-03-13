//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSIShaderCompound.h
	\brief Defines the CSLXSIShaderCompound class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _XSISHADERCOMPOUND_H
#define _XSISHADERCOMPOUND_H

#include "Template.h"

class CSLXSIShaderCompoundPort;
class CSLXSIShader;

/*! \brief This class represents an \xx ftk_XSI_ShaderCompound XSI_ShaderCompound \endxx template.

	Defines a shader compound (see the \xx ftk_XSI_ShaderCompound XSI_ShaderCompound \endxx template reference).
	\since dotXSI 6.0
*/

class XSIEXPORT CSLXSIShaderCompound
    : public CSLTemplate
{
public:
	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Refered template
		\param[in] in_pParentShader Parent shader
	*/
	CSLXSIShaderCompound(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate, CSLXSIShader* in_pParentShader);

	//! Destructor
	virtual ~CSLXSIShaderCompound();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_SHADER_COMPOUND The type of this template
	*/
	ETemplateType Type(){ return XSI_SHADER_COMPOUND; }

	/*! Commits the current template information
		\return Whether or not the commit was successful
	*/
	SI_Error Synchronize();

	/*! Returns the Category value
		\return Category
	*/
	SI_Char* GetCategory();

	/*! Sets the Category value
		\param[in]	in_pValue	new Category value
	*/
	SI_Void SetCategory( SI_Char* in_pValue );

	/*! Returns the Description value
		\return Description
	*/
	SI_Char* GetDescription();

	/*! Sets the Description value
		\param[in]	in_pValue	new Description value
	*/
	SI_Void SetDescription( SI_Char* in_pValue );

	/*! Returns the Author value
		\return Author
	*/
	SI_Char* GetAuthor();

	/*! Sets the Author value
		\param[in]	in_pValue	new Author value
	*/
	SI_Void SetAuthor( SI_Char* in_pValue );

	/*! Returns the Date value
		\return Date
	*/
	SI_Char* GetDate();

	/*! Sets the Date value
		\param[in]	in_pValue	new Date value
	*/
	SI_Void SetDate( SI_Char* in_pValue );

	/*! Returns the VersionTag value
		\return VersionTag
	*/
	SI_Char* GetVersionTag();

	/*! Sets the VersionTag value
		\param[in]	in_pValue	new VersionTag value
	*/
	SI_Void SetVersionTag( SI_Char* in_pValue );

	/*! Returns the VersionMajor value
		\return VersionMajor
	*/
	SI_Int GetVersionMajor();

	/*! Sets the VersionMajor value
		\param[in]	in_nValue	new VersionMajor value
	*/
	SI_Void SetVersionMajor( SI_Int in_nValue );

	/*! Returns the VersionMinor value
		\return VersionMinor
	*/
	SI_Int GetVersionMinor();

	/*! Sets the VersionMinor value
		\param[in]	in_nValue	new VersionMinor value
	*/
	SI_Void SetVersionMinor( SI_Int in_nValue );

	/*! Returns the PPGLogic value
		\return PPGLogic
	*/
	SI_Char* GetPPGLogic();

	/*! Sets the PPGLogic value
		\param[in]	in_pValue	new PPGLogic value
	*/
	SI_Void SetPPGLogic( SI_Char* in_pValue );

	/*! Returns the PPGLogicLanguage value
		\return PPGLogicLanguage
	*/
	SI_Char* GetPPGLogicLanguage();

	/*! Sets the PPGLogicLanguage value
		\param[in]	in_pValue	new PPGLogicLanguage value
	*/
	SI_Void SetPPGLogicLanguage( SI_Char* in_pValue );

	/*! Returns the BackgroundColor value
		\return BackgroundColor
	*/
	SI_Int GetBackgroundColor();

	/*! Sets the BackgroundColor value
		\param[in]	in_nValue	new BackgroundColor value
	*/
	SI_Void SetBackgroundColor( SI_Int in_nValue );

	/*!	Sets the shader parent of this template.
		\param[in] in_pParentShader	Pointer to the parent shader.
	*/
	void SetParentShader(CSLXSIShader* in_pParentShader);

	/*!	Returns the shader parent of this template.
		\return Pointer to the parent shader.
	*/
	CSLXSIShader* ParentShader();


	CSLStringProxy* 	GetCategoryProxy()			{ return &m_Category; };
	CSLStringProxy* 	GetDescriptionProxy()		{ return &m_Description; };
	CSLStringProxy* 	GetAuthorProxy()			{ return &m_Author; };
	CSLStringProxy* 	GetDateProxy()				{ return &m_Date; };
	CSLStringProxy* 	GetVersionTagProxy()		{ return &m_VersionTag; };
	CSLIntProxy* 		GetVersionMajorProxy()		{ return &m_VersionMajor; };
	CSLIntProxy* 		GetVersionMinorProxy()		{ return &m_VersionMinor; };
	CSLStringProxy* 	GetPPGLogicProxy()			{ return &m_PPGLogic; };
	CSLStringProxy* 	GetPPGLogicLanguageProxy()	{ return &m_PPGLogicLanguage; };
	CSLIntProxy* 		GetBackgroundColorProxy()	{ return &m_BackgroundColor; };

	///////////////////////////////////////////////////////////////////////
	// Shader Compound Port functionality ////////////////////////////////
	///////////////////////////////////////////////////////////////////////

	/*! Adds a shader compound port to the shader compound port list
		\return The added shader compound port
	*/
	CSLXSIShaderCompoundPort* AddShaderCompoundPort();

	/*! Removes a shader compound port from the shader compound port list
		\param[in] in_nIndex	Index of the shader compound port to remove
	*/
	SI_Error RemoveShaderCompoundPort(SI_Int in_nIndex);

	/*! Removes a shader compound port from the shader compound port list
		\param[in] in_pToRemove	The shader compound port to remove
	*/
	SI_Error RemoveShaderCompoundPort(CSLXSIShaderCompoundPort* in_pToRemove);

	/*! Returns a CSLXSIShaderCompoundPort object by index.
		\param[in] in_nIndex	Index of the shader compound port to get
		\return The CSLXSIShaderCompoundPort object.
	*/
	CSLXSIShaderCompoundPort* GetShaderCompoundPort(SI_Int in_nIndex);

	/*! Returns the number of shader compound port in the shader compound port list
		\return The number of shader compound port in the shader compound port list
	*/
	SI_Int GetShaderCompoundPortCount();

	/*! Deletes all the shader compound port form the shader compound port list
	*/
	SI_Error ClearShaderCompoundPorts();

	/*! Returns a pointer to the internally-stored shader compound port pointer list
		\return Pointer to the list
	*/
	CSLXSIShaderCompoundPort** GetShaderCompoundPortList();

	/*! Adds an exisiting shader compound port to the shader compound port list
		\param[in] in_pToConnect Pointer to the shader compound port to add
		\return The added shader compound port
	*/
	CSLXSIShaderCompoundPort* ConnectShaderCompoundPort( CSLXSIShaderCompoundPort* in_pToConnect );

	/*! Searches for a given shader compound port
		\param[in] in_szPortName Name of the shader compound port to look for
		\return Pointer to the shader compound port or null if it cannot be found
	*/
	CSLXSIShaderCompoundPort* FindShaderCompoundPort( SI_Char* in_szPortName );

	///////////////////////////////////////////////////////////////////////////
	// Shaders functionality //////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	/*! Adds a shader to the shader list
		\return Pointer to the newly added shader
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

private:
	CSLStringProxy	m_Category;
	CSLStringProxy	m_Description;
	CSLStringProxy	m_Author;
	CSLStringProxy	m_Date;
	CSLStringProxy	m_VersionTag;
	CSLIntProxy		m_VersionMajor;
	CSLIntProxy		m_VersionMinor;
	CSLStringProxy	m_PPGLogic;
	CSLStringProxy	m_PPGLogicLanguage;
	CSLIntProxy		m_BackgroundColor;

	CSIBCArray<CSLXSIShaderCompoundPort *> m_ShaderCompoundPorts;
    CSIBCArray<CSLXSIShader*> m_Shaders;

	CSLXSIShader*	m_pParentShader;

	SI_Void *m_pReserved;
};

#endif
