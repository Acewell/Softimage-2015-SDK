//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file IK.h
	\brief Defines the CSLIK class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _IK_H
#define _IK_H

#include "Primitive.h"

// Forward declaration
class CSLIKRoot;


/*! \brief This is the base class for all IK classes.
*/
class XSIEXPORT CSLIK
    : public CSLPrimitive
{
public:

	/*! Destructor
	*/
    virtual ~CSLIK();

	/*!	Return the root associated with the IK component.
	* \return	CSLIKRoot*	Pointer to an IK root.
	*/
    CSLModel* GetRoot();

	/*! Connects a root model to this IK chain
	* \param in_pNewRoot the root to connect
	* \return CSLModel* the root
	*/
	CSLModel* ConnectRoot(CSLModel* in_pNewRoot);

protected:
    CSLIK(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate, CSLModel* in_pRoot);

private:
    CSLModel* m_pRoot;

	void *m_pReserved;	// reserved for future extension
};

#endif
