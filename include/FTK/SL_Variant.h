//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file SL_Variant.h
	\brief Defines the CSLVariantProxy class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef __VARIANT_H__
#define __VARIANT_H__

#include "SLTypes.h"
//#include <memory.h>

/*! \brief Class that allows the modification of any type of parameter in a template.

	\note A specialized proxy should be used whenever possible in order to
		limit unnecessary conversion.

	\sa CSLBoolProxy
	\sa CSLByteProxy
	\sa CSLDoubleProxy
	\sa CSLEnumProxy
	\sa CSLStrEnumProxy
	\sa CSLFloatProxy
	\sa CSLIntProxy
	\sa CSLLongProxy
	\sa CSLStringProxy
	\sa CSLUByteProxy
	\sa CSLULongProxy
*/
class XSIEXPORT CSLVariantProxy
{
public:
	/*! Type of the contained parameter
	*/
	 enum EValueType
	{
		SI_SLVT_INVALID  = 0,/*!< Invalid type.  The default value for unconnected variant.  \sa CSLVariantProxy::Connect */
		SI_SLVT_BOOL,		/*!< CSLBoolProxy type */
		SI_SLVT_BYTE,		/*!< CSLByteProxy type */
		SI_SLVT_UBYTE,		/*!< CSLUByteProxy type */
		SI_SLVT_DOUBLE,		/*!< CSLDoubleProxy type */
		SI_SLVT_FLOAT,		/*!< CSLFloatProxy type */
		SI_SLVT_INT,		/*!< CSLIntProxy type */
		SI_SLVT_LONG,		/*!< CSLLongProxy type */
		SI_SLVT_ULONG,		/*!< CSLULongProxy type */
		SI_SLVT_SHORT,		/*!< CSLShortProxy type */
		SI_SLVT_STRING		/*!< CSLStringProxy type */
	};

	/*! Pointer to the contained parameter
		\warning You must acces the pointer that matches the variant type
		defined by CSLVariantProxy::EValueType.

		\sa CSLVariant::GetType
		\sa CSLVariant::GetValue
		\sa CSLVariant::SetValue
	*/
	union
	{
		CSLBoolProxy	*m_pBool;	/*!< CSLVariant::SI_SLVT_BOOL */
		CSLByteProxy	*m_pByte;	/*!< CSLVariant::SI_SLVT_BYTE */
		CSLUByteProxy	*m_pUByte;	/*!< CSLVariant::SI_SLVT_UBYTE */
		CSLDoubleProxy	*m_pDouble;	/*!< CSLVariant::SI_SLVT_DOUBLE */
		CSLFloatProxy	*m_pFloat;	/*!< CSLVariant::SI_SLVT_FLOAT */
		CSLIntProxy		*m_pInt;	/*!< CSLVariant::SI_SLVT_INT */
		CSLLongProxy	*m_pLong;	/*!< CSLVariant::SI_SLVT_LONG */
		CSLULongProxy	*m_pULong;	/*!< CSLVariant::SI_SLVT_ULONG */
		CSLShortProxy	*m_pShort;	/*!< CSLVariant::SI_SLVT_SHORT */
		CSLStringProxy	*m_pString;	/*!< CSLVariant::SI_SLVT_STRING */
	};

	/*! Default constructor.
		\note This constructor does not call CSLVariantProxy::Connect and will
		set the variant type to CSLVariant::SI_SLVT_INVALID.
	*/
	CSLVariantProxy();

	//! Destructor
	~CSLVariantProxy();

	/*! Connects the variant to a parameter in a template
		\param in_pTemplate Template containing the parameter to connect to
		\param in_nIndex Index of the parameter to connect to
		\note Once connected, you can modify the parameter's value trough this
		proxy.
	*/
	SI_Error Connect( CdotXSITemplate *in_pTemplate, SI_Int in_nIndex );

	/*! Constructor that connects to a parameter in a template
		\param in_pTemplate Template containing the parameter to connect to
		\param in_nIndex Index of the parameter to connect to
	*/
	CSLVariantProxy( CdotXSITemplate *in_pTemplate, SI_Int in_nIndex );

	/*! Gets the type of the parameter referred by this proxy
	*/
	EValueType GetType() const;

	/*! Gets the value of the parameter referred by this proxy
		\param out_Variant The value of the parameter
		\retval SI_SUCCESS Got the value of the parameter
		\retval SI_ERR_BAD_ARGUMENT Failed to get the value of the variant.  This happens when CSLVariantProxy::Connect failed or wasn't called (i.e. The type of the variant is CSLVariantProxy::SI_SLVT_INVALID );
		\warning You must \b not free the string pointer of SI_SLVT_STRING
	*/
	SI_Error GetValue( SI_TinyVariant &out_Variant ) const;

	/*! Sets the value of the parameter referred by this proxy
		\param in_vVariant Value to put.
		\retval SI_SUCCESS Value was set
		\retval SI_ERR_BAD_ARGUMENT The value types don't match or the proxy isn't connected
		\sa CSLVariantProxy::Connect
		\sa CSLVariantProxy::TinyVarType2SLVarType
	*/
	SI_Error SetValue( const SI_TinyVariant &in_vVariant );

	/*! Sets the value of the parameter referred by this proxy
		\param in_vVariant Value to put.
		\retval SI_SUCCESS Value was set
		\retval SI_ERR_BAD_ARGUMENT The value types don't match or the proxy isn't connected
		\sa CSLVariantProxy::Connect
		\sa CSLVariantProxy::TinyVarType2SLVarType
	*/
	SI_Error SetValue( const CSLVariantProxy &in_vVariant );

	/*! Returns the equivalent CSLVariantProxy::EValueType of a given SI_TinyVariant
		\param in_TinyVariant The tiny variant with the type to extract
		\param out_Type The equivalent type in CSLVariantProxy::EValueType.
		\retval SI_SUCCESS Equivalent variant type found and put in \p out_Type
		\retval SI_ERR_BAD_ARGUMENT The SI_TinyVariant has no equivalent CSLVariantProxy::EValueType.
	*/
	static SI_Error TinyVarType2SLVarType( const SI_TinyVariant &in_TinyVariant, EValueType &out_Type );

	/*! Gets the equivalent SI_TinyVariant variant type for this instance
		\param out_VariantType The equivalent SI_TinyVariant variant type
		\retval SI_SUCCESS Equivalent variant type found and put in \p out_VariantType
		\retval SI_ERR_BAD_ARGUMENT The proxy is unconnected or failed to connect
		\sa CSLVariantProxy::Connect
	*/
	SI_Error GetTinyVarType( SI_Int &out_VariantType ) const;

private:
	CSLVariantProxy(const CSLVariantProxy& );					// @cmember  Disable Copy Constructor
	const CSLVariantProxy& operator=(const CSLVariantProxy );	//@cmember Disable Assignment operator

	void Clear();
	EValueType m_ValueType;
};

#endif //__VARIANT_H__
