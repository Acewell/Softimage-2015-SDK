//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file dotXSIParams.h
	\brief Defines the CdotXSIParams class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

//***************************************************************************************
// Defines
//***************************************************************************************
#ifndef __DOTXSIPARAMS_H
#define __DOTXSIPARAMS_H

//***************************************************************************************
// Includes
//***************************************************************************************
#include "dotXSIParam.h"
#include "SIBCArray.h"
#include "SIBCString.h"


/*! \brief Container for an array of CdotXSIParam elements
*/
class XSIEXPORT CdotXSIParams
{
public:

	/*! Constructor
	*/
	CdotXSIParams();

	/*! Destructor
	*/
	virtual ~CdotXSIParams();

	/*! Returns the number of elements
	\return the number of CdotXSIParam items in this collection
	*/
	SI_Int GetCount();

	/*! Adds an element to this collection
	\param[in] i_Param the CdotXSIParam to add to this collection
	\param[in] i_nPosition the position to add this element at
	*/
	SI_Void Add( CdotXSIParam *i_Param, SI_Int i_nPosition );

	/*! Stores a reference to the specified item in the collection
	\param[in] i_nPosition position to get the item at
	\param[out] o_Param a pointer containing the reference to the item
	*/
	SI_Void Item( SI_Int i_nPosition, CdotXSIParam **o_Param );

	/*! Returns the item at the specified position in the collection
	\param[in] i_nPosition position to get the item at
	\return a pointer to the requested item
	*/
    CdotXSIParam *Item( SI_Int i_nPosition );

	/*! Removes the specified element from the collection
	\param[in] i_nPosition the position at which to remove the item
	*/
    SI_Void Remove( SI_Int i_nPosition );

	/*! Clears the entire collection of all elements
	*/
    SI_Void Clear();

	/*! Finds an element in the collection by name
	\param[in] i_sParamName the name of the parameter to find
	\param[out] o_pParam a pointer containing the reference to the item
	\return whether the element has been found or not
	*/
	SI_Bool Find( CSIBCString *i_sParamName, CdotXSIParam **o_pParam );

	/*! Returns an element in the collection by name
	\param[in] in_szParamName the name of the parameter to find
	\return a pointer to the requested item or NULL
	*/
	CdotXSIParam* Find( const SI_Char* in_szParamName );

private:
	SI_Int                          m_nCount;
    CSIBCArray< CdotXSIParam * >    m_Params;
};

//***************************************************************************************
// Global Functions
//***************************************************************************************

/*! \addtogroup glbfunc_param Global dotXSI parameter collections functions
*  @{
*/

/*! Creates a new CdotXSIParams collection
\return the newly created collection
*/
XSIEXPORT CdotXSIParams* CreatedotXSIParams();

/* @} */

#endif // __DOTXSIPARAMS_H
