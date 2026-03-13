//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file SL_Float.h
	\brief Defines the CSLFloatProxy class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _FLOAT_H
#define _FLOAT_H

#include <SIBCMath.h>			// SI_EPSILON
#include "AnimatableType.h"		// CSLAnimatableType
class CCOLLADATemplate;
class CSLCOLLADAScene;

/*! \brief Class that allows modification of a float parameter in a template
*/
class XSIEXPORT CSLFloatProxy : public CSLAnimatableType
{
public:
	/*! Constructor. Connects to a parameter in the parent template
		\param[in] in_pTemplate Pointer to the parent template
		\param[in] in_nIndex Index of the parameter in the template
		\param[in] in_fThreshold Tolerance value used to determine equality between two floats.
		\sa CSLFloatProxy::Threshold
		\sa CSLFloatProxy::SetThreshold
	 */
    CSLFloatProxy(CdotXSITemplate *in_pTemplate, SI_Int in_nIndex, SI_Float in_fThreshold = SI_EPSILON);

	/*! Assignment operator. Assigns \p in_Value to the parameter referred by this proxy.
		\param[in]	in_Value	The new value
		\return Reference to the current object.
	*/
    CSLFloatProxy& operator =(const CSLFloatProxy &in_Value);

	/*! Assignment operator. Assigns \p in_Value to the parameter referred by this proxy.
		\param[in]	in_Value	The new value
		\return Reference to the current object.
	*/
    CSLFloatProxy& operator =(const SI_Float &in_Value);

	/*! Comparison operator.
		Compares \p in_ToCompare with the value of the parameter referred by this proxy.
		\note Comparison is performed with a threshold value.  You can perform
			exact comparison by setting the Threshold value to zero.
		\param[in]	in_ToCompare	The instance to compare values with
		\return	Whether or not the referred parameter and \p in_ToCompare are equal
		\sa CSLFloatProxy::Threshold
		\sa CSLFloatProxy::SetThreshold
	*/
    SI_Bool operator ==(const CSLFloatProxy &in_ToCompare);

	/*! Comparison operator. Compares \p in_ToCompare with the value of the parameter referred by this proxy.
		\param[in]	in_ToCompare	The instance to compare values with
		\note Comparison is performed with a threshold value.  You can perform
			exact comparison by setting the Threshold value to zero.
		\return	Whether or not the referred parameter and \p in_ToCompare are equal
		\sa CSLFloatProxy::Threshold
		\sa CSLFloatProxy::SetThreshold
	*/
    SI_Bool operator ==(const SI_Float &in_ToCompare);

	//! Conversion operator
    operator SI_Float();

	/*! Returns the threshold value
		\return Tolerance value used to determine equality between two floats.
		\sa CSLFloatProxy::SetThreshold
	*/
	SI_Float Threshold();

	/*! Sets the thresold value
		\param[in] in_fThreshold Tolerance value used to determine equality between two floats.
		\eg Demonstrates how to set the threshold
		\code
		// no threshold, the values must be absolutely equal
		CSLFloatProxy l_fProxy( in_pTemplate, in_paramIdx, 0.0 );
		l_fProxy = 0.00501;

		if ( l_fProxy == 0.005F )
		{
			// We get here because abs(0.00501 - 0.005) > 0
		}

		// use a tolerance of 0.0001
		l_fProxy.SetThreshold( 0.0001F );

		if ( l_fProxy == 0.005F )
		{
			// We get here because abs(0.00501 - 0.005) <= 0.0001
		}

		\endcode
		\sa CSLDoubleProxy::Threshold
	*/
	void SetThreshold( SI_Float in_fThreshold );

	/*! Returns the animatable type of this class
		\retval CSLAnimatableType::SI_FLOAT_TYPE Animatable type
	*/
	virtual EElementType Type();

	/*! Converts the value of the referred parameter to float
		\return The converted value
	*/
	virtual SI_Float GetFloatValue();

	/*! Sets the value of the referred parameter from a float
		\param[in] in_fValue The float value used to set the parameter
	*/
	virtual SI_Void SetFloatValue(SI_Float in_fValue);

	/*! Connects the proxy to a parameter of a template
		\param[in] in_pTemplate Parent template
		\param[in] in_nIndex Index of the parameter in the parent template
		\retval SI_Error::SI_SUCCESS
	*/
	virtual SI_Error Connect (CdotXSITemplate *in_pTemplate, SI_Int in_nIndex );

private:
	// no copy constructor
	CSLFloatProxy( CSLFloatProxy &in_pBasicType ){}

	SI_Bool Equal( SI_Float in_Float1, SI_Float in_Float2 );

	SI_Float m_fThreshold;
    SI_Float* m_pValue;
};

#endif
