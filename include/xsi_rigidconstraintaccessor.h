//*****************************************************************************
/*!
   \file xsi_rigidconstraintaccessor.h
   \brief CRigidConstraintAccessor class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIRIGIDCONSTRAINTACCESSOR_H__
#define __XSIRIGIDCONSTRAINTACCESSOR_H__

#include <xsi_siobject.h>
#include <xsi_value.h>
#include <xsi_status.h>

#ifdef _MSC_VER
#pragma warning(disable:4251)
#endif

namespace XSI {

class CBitArray;
class CLongArray;
class CDoubleArray;
class CFloatArray;
class CRefArray;
class SimulationEnvironment;

//*****************************************************************************
/*! \class CRigidConstraintAccessor xsi_rigidconstraintaccessor.h
	\brief The rigid constraint accessor provides an optimized access to the data and property values of a rigid
	constraint object. CRigidConstraintAccessor is suitable for data export applications as it allows access to
    rigid body data more quickly and efficiently than the regular API classes.

	\since 6.0
*/
//*****************************************************************************

class SICPPSDKDECL CRigidConstraintAccessor : public CBase
{
public:
	/*! Default constructor. */
	CRigidConstraintAccessor();

	/*! Default destructor. */
	~CRigidConstraintAccessor();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	CRigidConstraintAccessor(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	CRigidConstraintAccessor(const CRigidConstraintAccessor& in_obj);

	/*! Returns true if a given class type is compatible with this API class.
	\param in_ClassID class type.
	\return true if the class is compatible, false otherwise.
	*/
	bool IsA( siClassID in_ClassID) const;

	/*! Returns the type of the API class.
	\return The class type.
	*/
	siClassID GetClassID() const;

	/*! Creates an object from another object. The newly created object is set to
	empty if the input object is not compatible.
	\param in_obj constant class object.
	\return The new CRigidConstraintAccessor object.
	*/
	CRigidConstraintAccessor& operator=(const CRigidConstraintAccessor& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new CRigidConstraintAccessor object.
	*/
	CRigidConstraintAccessor& operator=(const CRef& in_ref);


	/*! Returns all rigid bodies attached to this rigid constraint.
	\return An array of references to X3DObject objects
	\sa CRigidBodyAccessor::GetAttachedRigidConstraints
	\sa SimulationEnvironment::GetRigidBodyObjects
	\since 6.0
	*/
	CRefArray GetAttachedRigidBodies( ) const;

	/*! Returns the number of rigid bodies attached to this rigid constraint as a LONG.
	\sa X3DObject::GetRigidConstraintAccessor
	\sa CRigidBodyAccessor::GetAttachedRigidBodies
	\since 6.0
	*/
	LONG GetAttachedRigidBodiesCount( ) const;

	/*! Returns the SimulationEnvironment that contains this rigid constraint.
	\since 6.0
	*/
	SimulationEnvironment GetSimulationEnvironment( ) const;


  private:
	CRigidConstraintAccessor * operator&() const;
	CRigidConstraintAccessor * operator&();
};

};
#endif // __XSIGEOMACCESSOR_H__
