//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSITextureLayer.h
	\brief Defines the CSLXSITextureLayer class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************
#ifndef _XSITEXTURELAYER_H
#define _XSITEXTURELAYER_H

#include "Template.h"

class CSLXSITextureLayerPort;
class CSLXSIShaderMultiPortConnection;


/*! \brief This class represents an \xx ftk_XSI_TextureLayer XSI_TextureLayer \endxx template.

	Defines more image effects (see the \xx ftk_XSI_TextureLayer XSI_TextureLayer \endxx template reference).
	\since dotXSI 6.0
*/
class XSIEXPORT CSLXSITextureLayer
    : public CSLTemplate
{
public:
	/*! Constructor
		\param[in] in_pScene Parent scene
		\param[in] in_pModel Parent model
		\param[in] in_pTemplate Referred template
	*/
	CSLXSITextureLayer(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	//! Destructor
	virtual ~CSLXSITextureLayer();

	/*! Commits the current template information
		\return Whether or not the commit was successful
	*/
	SI_Error Synchronize();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_TEXTURE_LAYER The type of this template
	*/
	ETemplateType Type(){ return XSI_TEXTURE_LAYER; }

    virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);

	virtual CSLAnimatableType* ParameterFromType(EFCurveType in_Type, SI_Char *in_szParameterName);

	/*! Returns the Order value
		\return Order
	*/
	SI_Int GetOrder();

	/*! Sets the Order value
		\param[in]	in_nValue	new Order value
	*/
	SI_Void SetOrder( SI_Int in_nValue );

	/*! Returns the Mute value
		\return Mute
	*/
	SI_Bool GetMute();

	/*! Sets the Mute value
		\param[in]	in_bValue	new Mute value
	*/
	SI_Void SetMute( SI_Bool in_bValue );

	/*! Returns the Solo value
		\return Solo
	*/
	SI_Bool GetSolo();

	/*! Sets the Solo value
		\param[in]	in_bValue	new Solo value
	*/
	SI_Void SetSolo( SI_Bool in_bValue );

	/*! Returns the ColorConnection value
		\return ColorConnection
	*/
	SI_Char* GetColorConnection();

	/*! Sets the ColorConnection value
		\param[in]	in_pValue	new ColorConnection value
	*/
	SI_Void SetColorConnection( SI_Char* in_pValue );

	/*! Returns the Red value
		\return Red
	*/
	SI_Float GetRed();

	/*! Sets the Red value
		\param[in]	in_fValue	new Red value
	*/
	SI_Void SetRed( SI_Float in_fValue );

	/*! Returns the Green value
		\return Green
	*/
	SI_Float GetGreen();

	/*! Sets the Green value
		\param[in]	in_fValue	new Green value
	*/
	SI_Void SetGreen( SI_Float in_fValue );

	/*! Returns the Blue value
		\return Blue
	*/
	SI_Float GetBlue();

	/*! Sets the Blue value
		\param[in]	in_fValue	new Blue value
	*/
	SI_Void SetBlue( SI_Float in_fValue );

	/*! Returns the Alpha value
		\return Alpha
	*/
	SI_Float GetAlpha();

	/*! Sets the Alpha value
		\param[in]	in_fValue	new Alpha value
	*/
	SI_Void SetAlpha( SI_Float in_fValue );

	/*! Returns the ColorPremultiplied value
		\return ColorPremultiplied
	*/
	SI_Bool GetColorPremultiplied();

	/*! Sets the ColorPremultiplied value
		\param[in]	in_bValue	new ColorPremultiplied value
	*/
	SI_Void SetColorPremultiplied( SI_Bool in_bValue );

	/*! Returns the IgnoreColorAlpha value
		\return IgnoreColorAlpha
	*/
	SI_Bool GetIgnoreColorAlpha();

	/*! Sets the IgnoreColorAlpha value
		\param[in]	in_bValue	new IgnoreColorAlpha value
	*/
	SI_Void SetIgnoreColorAlpha( SI_Bool in_bValue );

	/*! Returns the InvertColorAlpha value
		\return InvertColorAlpha
	*/
	SI_Bool GetInvertColorAlpha();

	/*! Sets the InvertColorAlpha value
		\param[in]	in_bValue	new InvertColorAlpha value
	*/
	SI_Void SetInvertColorAlpha( SI_Bool in_bValue );

	/*! Returns the AlphaColor value
		\return AlphaColor
	*/
	SI_Bool GetAlphaColor();

	/*! Sets the AlphaColor value
		\param[in]	in_bValue	new AlphaColor value
	*/
	SI_Void SetAlphaColor( SI_Bool in_bValue );

	/*! Returns the MaskConnection value
		\return MaskConnection
	*/
	SI_Char* GetMaskConnection();

	/*! Sets the MaskConnection value
		\param[in]	in_pValue	new MaskConnection value
	*/
	SI_Void SetMaskConnection( SI_Char* in_pValue );

	/*! Returns the Mask value
		\return Mask
	*/
	SI_Float GetMask();

	/*! Sets the Mask value
		\param[in]	in_fValue	new Mask value
	*/
	SI_Void SetMask( SI_Float in_fValue );

	/*! Returns the InvertMask value
		\return InvertMask
	*/
	SI_Bool GetInvertMask();

	/*! Sets the InvertMask value
		\param[in]	in_bValue	new InvertMask value
	*/
	SI_Void SetInvertMask( SI_Bool in_bValue );

	/*! Returns the MaskMode value
		\return MaskMode
	*/
	SI_Int GetMaskMode();

	/*! Sets the MaskMode value
		\param[in]	in_nValue	new MaskMode value
	*/
	SI_Void SetMaskMode( SI_Int in_nValue );

	/*! Returns the MaskThreshold value
		\return MaskThreshold
	*/
	SI_Float GetMaskThreshold();

	/*! Sets the MaskThreshold value
		\param[in]	in_nValue	new MaskThreshold value
	*/
	SI_Void SetMaskThreshold( SI_Float in_nValue );

	/*! Returns the Weight value
		\return Weight
	*/
	SI_Float GetWeight();

	/*! Sets the Weight value
		\param[in]	in_fValue	new Weight value
	*/
	SI_Void SetWeight( SI_Float in_fValue );

	/*! Returns the Mode value
		\return Mode
	*/
	SI_Int GetMode();

	/*! Sets the Mode value
		\param[in]	in_nValue	new Mode value
	*/
	SI_Void SetMode( SI_Int in_nValue );

	CSLIntProxy*	GetOrderProxy() { return &m_Order; };
	CSLBoolProxy*	GetMuteProxy() { return &m_Mute; };
	CSLBoolProxy*	GetSoloProxy() { return &m_Solo; };
	CSLStringProxy*	GetColorConnectionProxy() { return &m_ColorConnection; };
	CSLFloatProxy*	GetRedProxy() { return &m_Red; };
	CSLFloatProxy*	GetGreenProxy() { return &m_Green; };
	CSLFloatProxy*	GetBlueProxy() { return &m_Blue; };
	CSLFloatProxy*	GetAlphaProxy() { return &m_Alpha; };
	CSLBoolProxy*	GetColorPremultipliedProxy() { return &m_ColorPremultiplied; };
	CSLBoolProxy*	GetIgnoreColorAlphaProxy() { return &m_IgnoreColorAlpha; };
	CSLBoolProxy*	GetInvertColorAlphaProxy() { return &m_InvertColorAlpha; };
	CSLBoolProxy*	GetAlphaColorProxy() { return &m_AlphaColor; };
	CSLStringProxy*	GetMaskConnectionProxy() { return &m_MaskConnection; };
	CSLFloatProxy*	GetMaskProxy() { return &m_Mask; };
	CSLBoolProxy*	GetInvertMaskProxy() { return &m_InvertMask; };
	CSLIntProxy*	GetMaskModeProxy() { return &m_MaskMode; };
	CSLFloatProxy*	GetMaskThresholdProxy() { return &m_MaskThreshold; };
	CSLFloatProxy*	GetWeightProxy() { return &m_Weight; };
	CSLIntProxy*	GetModeProxy() { return &m_Mode; };

	///////////////////////////////////////////////////////////////////////
	// Texture Layer port functionality ////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////

	/*! Adds a texture layer port to the texture layer port list
		\return	The added texture layer port
	*/
	CSLXSITextureLayerPort* AddTextureLayerPort();

	/*! Removes a texture layer port from the texture layer port list
		\param[in] in_nIndex	Index of the texture layer port to remove
	*/
	SI_Error RemoveTextureLayerPort(SI_Int in_nIndex);

	/*! Removes a texture layer port from the texture layer port list
		\param[in] in_pToRemove	The texture layer port to remove
	*/
	SI_Error RemoveTextureLayerPort(CSLXSITextureLayerPort* in_pToRemove);

	/*! Returns the CSLXSITextureLayerPort object by index.
		\param[in] in_nIndex	Index of the texture layer port to get
		\return The CSLXSITextureLayerPort.
	*/
	CSLXSITextureLayerPort* GetTextureLayerPort(SI_Int in_nIndex);

	/*! Returns the number of texture layer port in the texture layer port list
		\return The number of texture layer port in the texture layer port list
	*/
	SI_Int GetTextureLayerPortCount();

	/*! Deletes all the texture layer port form the texture layer port list
	*/
	SI_Error ClearTextureLayerPorts();

	/*! Returns a pointer to the internally-stored texture layer port pointer list
		\return Pointer to the list
	*/
	CSLXSITextureLayerPort** GetTextureLayerPortList();

	/*! Adds an exisiting texture layer port to the texture layer port list
		\param[in] in_pToConnect Pointer to the texture layer port to add
		\return The added texture layer port
	*/
	CSLXSITextureLayerPort* ConnectTextureLayerPort( CSLXSITextureLayerPort* in_pToConnect );

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

private:
	CSLIntProxy		m_Order;
	CSLBoolProxy	m_Mute;
	CSLBoolProxy	m_Solo;
	CSLStringProxy	m_ColorConnection;
	CSLFloatProxy	m_Red;
	CSLFloatProxy	m_Green;
	CSLFloatProxy	m_Blue;
	CSLFloatProxy	m_Alpha;
	CSLBoolProxy	m_ColorPremultiplied;
	CSLBoolProxy	m_IgnoreColorAlpha;
	CSLBoolProxy	m_InvertColorAlpha;
	CSLBoolProxy	m_AlphaColor;
	CSLStringProxy	m_MaskConnection;
	CSLFloatProxy	m_Mask;
	CSLBoolProxy	m_InvertMask;
	CSLIntProxy		m_MaskMode;
	CSLFloatProxy	m_MaskThreshold;
	CSLFloatProxy	m_Weight;
	CSLIntProxy		m_Mode;

	CSIBCArray<CSLXSITextureLayerPort*> m_TextureLayerPorts;

	CSIBCArray<CSLXSIShaderMultiPortConnection *> m_MultiPortConnections;

	SI_Void *m_pReserved;
};

#endif
