//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file ConstrainableType.h
	\brief Defines the CSLConstrainableType class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _CONSTRAINABLETYPE_H
#define _CONSTRAINABLETYPE_H

#include "Constraint.h"

/*! \brief Base class for all templates supporting constraints.
*/
class XSIEXPORT CSLConstrainableType
{
public:
	/*! Adds a constraint to the constraint list
		\param[in] in_ConstraintType Type of constraint to add
		\return Pointer to the newly added constraint
	*/
	virtual CSLConstraint* AddConstraint(CSLConstraint::EConstraintType in_ConstraintType) = 0;

	/*! Removes a constraint from the constraint list
		\param[in] in_nIndex Index of the constraint to remove
		\return Whether or not the constraint could be removed
	*/
    SI_Error RemoveConstraint( SI_Int in_nIndex );

	/*! Removes a constraint from the constraint list
		\param[in] in_pToRemove Pointer of the constraint to remove
		\return Whether or not the constraint could be removed
	*/
    SI_Error RemoveConstraint( CSLConstraint *in_pToRemove );

	/*! Returns the total number of constraints in the constraints list
		\return Number of constraints
	*/
    SI_Int GetConstraintCount();

	/*! Returns a pointer to the internally-stored constraint pointer list
		\return Pointer to the list
	*/
	CSLConstraint** GetConstraintList();

	/*! Removes all constraints from the internally-stored list and deallocate them
		\return Whether or not removal was a success
	*/
	SI_Error ClearConstraints();

	/*! Adds a reference to an existing constraint
		\param[in] in_pNewConstraint Pointer to the new object to refer to
		\return Pointer to the new reference
	*/
	CSLConstraint* ConnectConstraint( CSLConstraint* in_pNewConstraint );

	// overloaded methods /////////////////////////////////////////////////////
	SI_Error Synchronize();

protected:
	CSLConstrainableType(CSLScene* in_pScene);
	virtual ~CSLConstrainableType();

private:
	CSIBCArray<CSLConstraint*> m_Constraints;
	CSLScene *m_pScene;
};


#endif // _CONSTRAINABLETYPE_H

