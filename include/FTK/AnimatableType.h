//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file AnimatableType.h
	\brief Defines the CSLAnimatableType class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef __ANIMATABLETYPE_H__
#define __ANIMATABLETYPE_H__

#include <dotXSITemplate.h>	// CDotXSITemplate
#include <COLLADATemplate.h> // CCOLLADATemplate
#include <dotXSIParam.h>	// CdotXSIParam

class CSLCOLLADAScene;
class CSLTemplate;

////////////////////////////////////////////////////
// Actual definition of the CSLAnimatable class
////////////////////////////////////////////////////

/*! \brief This class represents the base class for animatable types.

	This class is abstract, but it defines basic operations of all animatable sub-classes.
*/
class XSIEXPORT CSLAnimatableType
{
public:

	/*! This enumeration lists all base types supported by animatable types
	*/
	enum EElementType
	{
		SI_BOOL_TYPE,		/*!<  The element is of type boolean */
		SI_BYTE_TYPE,		/*!<  The element is of type byte */
		SI_UBYTE_TYPE,		/*!<  The element is of type unsigned byte */
		SI_DOUBLE_TYPE,		/*!<  The element is of type double */
		SI_FLOAT_TYPE,		/*!<  The element is of type float */
		SI_INT_TYPE,		/*!<  The element is of type integer */
		SI_LONG_TYPE,		/*!<  The element is of type long */
		SI_ULONG_TYPE,		/*!<  The element is of type unsigned long */
		SI_SHORT_TYPE,		/*!<  The element is of type short */
		SI_VARIANT_TYPE,	/*!<  The element is of type variant */
		SI_ENUM_TYPE,		/*!<  The element is of type enumeration */
		SI_STRING_ENUM_TYPE,/*!<  The element is of type string enumeration */
	};

	/*! Returns the type of this parameter
		\return The type of this parameter (Defined by sub-class)
	*/
	virtual EElementType Type() = 0;

	/*! Returns the name of the parameter
		\return String representing the name of the parameter
	*/
	SI_Char* GetName();

	/*! Sets the name of the parameter
		\param[in] in_szName New name for the parameter
	*/
	SI_Void SetName( const SI_Char* in_szName );

	/*! Converts the value of the referred parameter to float
		\return The converted value
	*/
	virtual SI_Float GetFloatValue() = 0;

	/*! Sets the value of the referred parameter from a float
		\param[in] in_fValue The float value used to set the parameter
	*/
	virtual SI_Void SetFloatValue(SI_Float in_fValue) = 0;

	/*! Connects the proxy to the IO layer parameter
		\param[in] in_pTemplate the template that owns the parameter to connect to
		\param[in] in_iIndex the index of the parameter
		\return Whether the proxy was succesfully connected or not
	*/
	virtual SI_Error Connect ( CdotXSITemplate* in_pTemplate, SI_Int in_iIndex);

	/*! Connects the proxy to the IO layer parameter
		\param[in] in_pTemplate the template that virtually owns the parameter to connect to
		\param[in] in_pOwner the template that owns the parameter to connect to
		\param[in] in_nIndex the index of the parameter
		\param[in] in_szAddress the address of this parameter if it's in a complex type
		\param[in] in_pScene the COLLADA scene
		\param[in] in_CurveType the equivalent dotXSI Curve type in case of COLLADA/DOTXSI morphing
		\param[in] in_XSIName the Softimage parameter name
		\return Whether the proxy was succesfully connected or not
	*/
	virtual SI_Error ConnectSID (CSLTemplate *in_pTemplate, CCOLLADATemplate *in_pOwner, SI_Int in_nIndex, const char* in_szAddress, CSLCOLLADAScene* in_pScene, int in_CurveType, const char* in_XSIName );

	/*! Returns the CdotXSIParam reference of that proxy
		\return Reference to that proxy
	*/
	virtual CdotXSIParam*	ParameterReference();

protected:

	/*! Constructor (default). This member is protected so that the class cannot be instantiated.
	*/
	CSLAnimatableType();

	/*! Destructor
	*/
	~CSLAnimatableType();

private:
	// no copy constructor
	CSLAnimatableType(CSLAnimatableType&){};
	CdotXSIParam* m_pReference;
};

#endif //__ANIMATABLETYPE_H__
