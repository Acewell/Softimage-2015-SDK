//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file Constraint.h
	\brief Defines the CSLConstraint class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _CONSTRAINT_H
#define _CONSTRAINT_H

#include "Template.h"

// Forward declaration
class CSLModel;


/*! \brief This class represents the \xx ftk_SI_Constraint SI_Constraint \endxx template.

	Describes a constraint (see the \xx ftk_SI_Constraint SI_Constraint \endxx
	template reference).
*/
class XSIEXPORT CSLConstraint
	: public CSLTemplate
{
public:
	/*! The EConstraintType enum contains possible types for a constraint
	*/
	enum EConstraintType
	{
		SI_SCALING,			//!< Scaling constraint
		SI_ORIENTATION,		//!< Orientation constraint
		SI_DIRECTION,		//!< Direction constraint
		SI_POSITION,		//!< Position constraint
		SI_INTEREST,		//!< Interest constraint
		SI_UP_VECTOR,		//!< Up Vector constraint
		SI_PREFERED_AXIS,	//!< Preferred Axis constraint
	};

	/*! Constructor
		\param[in] in_pScene			Pointer to the scene containing the constraint
		\param[in] in_pModel			Pointer to the model containing the constraint
		\param[in] in_pTemplate			Pointer to the CdotXSITemplate containing the constraint
		\param[in] in_ConstraintType	Type of constraint to add
		\return an instance of CSLConstraint
	*/
	CSLConstraint(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate, EConstraintType in_ConstraintType);

	/*! Destructor
	*/
	virtual ~CSLConstraint();

	/*!	Returns the reference model of the constraint.
		\return Pointer to the reference model.
	*/
	CSLModel*				GetReference();

	/*!	Returns the type of the constraint.
		\return Type of constraint.
	*/
	EConstraintType			GetConstraintType();

	/*!	Adds a new constraining object to the constraint.
		\param[in]	in_pConstrainingObject	Pointer to the constraining object.
		\return Error code.
	*/
	SI_Error				AddConstrainingObject(CSLModel* in_pConstrainingObject);

	/*!	Returns the number of constraining objects in the constraint.
		\return Number of constraining objects.
	*/
	SI_Int					GetConstrainingObjectCount();

	/*!	Returns an array of all constraining objects in the constraint.
		\return Array of pointers to model objects.
	*/
	CSLModel**				ConstrainingObjects();

	/*!	Removes a single constraining object from the constraint.
		\param[in]	in_nIndex	Index of the constraining object to remove.
		\return Error code.
	*/
	SI_Error				RemoveConstrainingObject(SI_Int in_nIndex);

	/*!	Removes a single constraining object from the constraint.
		\param[in]	in_pConstrainingObject	Pointer to the constraining object (model) to remove.
		\return Error code.
	*/
	SI_Error				RemoveConstrainingObject(CSLModel* in_pConstrainingObject);

	/*!	Removes all constraining objects from the constraint.
		\return Error code.
	*/
	SI_Error				ClearConstrainingObjects();

	/*!	Creates a up vector constraint on the constraint.
		\return Newly creates constraint object.
	*/
	CSLConstraint*			CreateUpVector();

	/*!	Returns the up vector constraint of the constraint.
		\return Pointer to a constraint object.
	*/
	CSLConstraint*			UpVector();

	/*!	Destroys the up vector constraint of the constraint.
		\return Error code.
	*/
	SI_Error				DestroyUpVector();

	// Connection functions
	/*! Connects with an up vector constraint
		\param[in] in_pUpVector the up vector constraint to connect to
		\return the up vector constraint
	*/
	CSLConstraint*			ConnectUpVector(CSLConstraint* in_pUpVector);

	/*! Connects with a constraining object
		\param[in] in_pModel the constraining object to connect to
		\return the constraining model
	*/
	CSLModel*				ConnectConstrainingObject(CSLModel* in_pModel);

	/*! Synchronizes this constraint instance with its IO layer representation
		\retval SI_Error::SI_SUCCESS this function always returns SI_SUCCESS
	*/
    virtual SI_Error		Synchronize();

	/*! Returns the template type of the constraint
		\retval CSLTemplate::SI_CONSTRAINT The template type
	*/
	virtual ETemplateType	Type() { return CSLTemplate::SI_CONSTRAINT; }

private:
	CSLStrEnumProxy<EConstraintType, SI_PREFERED_AXIS>	m_ConstraintType;
	CSIBCArray<CSLModel *>	m_ConstrainingModels;
	CSLConstraint*			m_pUpVector;

	void *m_pReserved;	// reserved for future extension
};

#endif
