//*****************************************************************************
/*!
   \file xsi_rigidbodyaccessor.h
   \brief CRigidBodyAccessor class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIRIGIDBODYACCESSOR_H__
#define __XSIRIGIDBODYACCESSOR_H__

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
/*! \class CRigidBodyAccessor xsi_rigidbodyaccessor.h
	\brief The rigid body accessor provides an optimized access to the data and property values of a rigid body
	dynamics object. CRigidBodyAccessor is suitable for data export applications as it allows access to rigid body
    data more quickly and efficiently than the regular API classes.

	\since 6.0
*/
//*****************************************************************************

class SICPPSDKDECL CRigidBodyAccessor : public CBase
{
public:
	/*! Default constructor. */
	CRigidBodyAccessor();

	/*! Default destructor. */
	~CRigidBodyAccessor();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	CRigidBodyAccessor(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	CRigidBodyAccessor(const CRigidBodyAccessor& in_obj);

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
	\return The new CRigidBodyAccessor object.
	*/
	CRigidBodyAccessor& operator=(const CRigidBodyAccessor& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new CRigidBodyAccessor object.
	*/
	CRigidBodyAccessor& operator=(const CRef& in_ref);


	/*! Returns all rigid body constraints (such as hinges and sliders) attached to this rigid body.
	\return An array of references to X3DObject objects
	\sa SimulationEnvironment::GetRigidConstraintObjects
	\sa SimulationEnvironment::GetRigidConstraintObjectsCount
	\sa X3DObject::GetRigidConstraintAccessor
	\since 6.0
	*/
	CRefArray GetAttachedRigidConstraints( ) const;

	/*! Returns the number of rigid body constraints (such as hinges and sliders) attached to this
	rigid body as a LONG.
	\sa X3DObject::GetRigidConstraintAccessor
	\sa CRigidBodyAccessor::GetAttachedRigidConstraints
	\sa SimulationEnvironment::GetRigidConstraintObjects
	\sa SimulationEnvironment::GetRigidConstraintObjectsCount
	\since 6.0
	*/
	LONG GetAttachedRigidConstraintsCount( ) const;

	/*! Returns the SimulationEnvironment that contains this rigid body.
	\since 6.0
	*/
	SimulationEnvironment GetSimulationEnvironment( ) const;

	/*! Returns all rigid body objects that make up this rigid body.  Compound rigid bodies are composed
	of more than one rigid body object.

	\param in_bAllShapes True to return all rigid body objects that make up this rigid body. Otherwise,
		return all the rigid body objects except the current one.

	\return An array of references to X3DObject objects
	\sa CRigidBodyAccessor::GetPatriarch
	\sa CRigidBodyAccessor::GetShapesCount
	\sa SimulationEnvironment::GetPatriarchRigidBodyObjects
	\sa X3DObject::GetRigidBodyAccessor
	\since 6.0
	*/
	CRefArray GetShapes( bool in_bAllShapes ) const;

	/*! Returns a the number of rigid body objects that make up this rigid body as a LONG.  Compound rigid
	bodies are composed of more than one rigid body object.

	\param in_bAllShapes True to return the count of all rigid body objects that make up this rigid body.
		Otherwise, return this number minus one.

	\sa CRigidBodyAccessor::GetShapes
	\since 6.0
	*/
	LONG GetShapeCount( bool in_bAllShapes ) const;

	/*! Returns this rigid body's patriarch. A "patriarch" is the top-most rigid body object in a rigid body.
	The simplest rigid bodies consist of a single X3DObject with rigid body properties; for example a single
	sphere with the "bounding sphere" collision type.

	A compound rigid body, however, is made up of one or more rigid body objects parented under an active rigid
	body.  This top-most rigid body object is the patriarch, and controls such aspects of the rigid body as
	its center of mass and whether the entire compound rigid body is active or passive.

	\return A reference to an X3DObject
	\sa CRigidBodyAccessor::GetShapes
	\sa SimulationEnvironment::GetPatriarchRigidBodyObjects
	\since 6.0
	*/
	CRef GetPatriarch( ) const;

  private:
	CRigidBodyAccessor * operator&() const;
	CRigidBodyAccessor * operator&();
};

};
#endif // __XSIGEOMACCESSOR_H__
