//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file SL_Double.h
	\brief Defines the CSLDoubleProxy class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _DOUBLE_H
#define _DOUBLE_H

#include <SIBCMath.h>		// SI_EPSILON
#include "AnimatableType.h" // CSLAnimatableType
class CCOLLADATemplate;
class CSLCOLLADAScene;

/*! \brief Class that allows modification of a double parameter in a template
*/
class XSIEXPORT CSLDoubleProxy : public CSLAnimatableType
{
public:
	/*! Constructor. Connects to a double parameter in the template
		\param[in] in_pTemplate Pointer to the template
		\param[in] in_nIndex Index of the parameter in the template
		\param[in] in_dThreshold Tolerance value used to determine equality between two doubles.
		\sa CSLDoubleProxy::Threshold
		\sa CSLDoubleProxy::SetThreshold
	 */
    CSLDoubleProxy(CdotXSITemplate *in_pTemplate, SI_Int in_nIndex, SI_Double in_dThreshold = SI_EPSILON);

	/*! Assignment operator. Assigns \p in_Value to the parameter referred by this proxy.
		\param[in]	in_Value	The new value
		\return Reference to the current object.
	*/
    CSLDoubleProxy& operator =(const CSLDoubleProxy &in_Value);

	/*! Assignment operator. Assigns \p in_Value to the parameter referred by this proxy.
		\param[in]	in_Value	The new value
		\return Reference to the current object.
	*/
    CSLDoubleProxy& operator =(const SI_Double &in_Value);

	/*! Comparison operator. Compares \p in_ToCompare with the value of the parameter referred by this proxy.
		\note Comparison is performed with a threshold value.  You can perform
			exact comparison by setting the Threshold value to zero.
		\param[in]	in_ToCompare	The instance to compare values with
		\return	Whether or not the referred parameter and \p in_ToCompare are equal
		\sa CSLDoubleProxy::SetThreshold
		\sa CSLDoubleProxy::Threshold
	*/
    SI_Bool operator ==(const CSLDoubleProxy &in_ToCompare);

	/*! Comparison operator. Compares \p in_ToCompare with the value of the parameter referred by this proxy.
		\note Comparison is performed with a threshold value.  You can perform
			exact comparison by setting the Threshold value to zero.
		\param[in]	in_ToCompare	The instance to compare values with
		\return	Whether or not the referred parameter and \p in_ToCompare are equal
		\sa CSLDoubleProxy::SetThreshold
		\sa CSLDoubleProxy::Threshold
	*/
    SI_Bool operator ==(const SI_Double &in_ToCompare);

	//! Conversion operator
    operator SI_Double();

	/*! Returns the threshold value
		\return Tolerance value used to determine equality between two doubles.
		\sa CSLDoubleProxy::SetThreshold
	*/
	SI_Double Threshold();

	/*! Sets the thresold value
		\param[in] in_dThreshold Tolerance value used to determine equality between two doubles.
		\b Example
		\code
		// no threshold, the values must be absolutely equal
		CSLDoubleProxy l_dProxy( in_pTemplate, in_paramIdx, 0.0 );
		l_dProxy = 0.00501;

		if ( l_dProxy == 0.005 )
		{
			// We get here because abs(0.00501 - 0.005) > 0
		}

		// use a tolerance of 0.0001
		l_dProxy.SetThreshold( 0.0001 );

		if ( l_dProxy == 0.005 )
		{
			// We get here because abs(0.00501 - 0.005) <= 0.0001
		}

		\endcode
		\sa CSLDoubleProxy::Threshold
	*/
	void SetThreshold( SI_Double in_dThreshold );

	/*! Returns the animatable type of this class
		\retval CSLAnimatableType::SI_DOUBLE_TYPE Animatable type
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
	CSLDoubleProxy( CSLDoubleProxy &in_pBasicType ){}
	SI_Bool Equal( SI_Double in_Double1, SI_Double in_Double2 );

	SI_Double m_dThreshold;
    SI_Double* m_pValue;
};

#endif
