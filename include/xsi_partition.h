//*****************************************************************************
/*!
   \file xsi_partition.h
   \brief Partition class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIPARTITION_H__
#define __XSIPARTITION_H__

#include <xsi_group.h>

namespace XSI {


//*****************************************************************************
/*! \class Partition xsi_partition.h
	\brief A Partition is a division of a Pass, which behaves like a Group.
	Partitions are used to organize scene elements within a Pass. There are
	only two types of partitions: object and light. Light partitions can only
	contain lights, and object partitions can only contain geometric objects.

	Each pass created has at least two partitions: a background objects
	partition, which contains most or all of the scene's objects, and a
	background lights partition, which contains most or all of the scene's
	lights.

	\sa Pass::GetPartitions, Pass::CreatePartition
	\since 7.0
*/
//*****************************************************************************

class SICPPSDKDECL Partition : public Group
{
public:
	/*! Default constructor. */
	Partition();

	/*! Default destructor. */
	~Partition();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	Partition(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	Partition(const Partition& in_obj);

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
	\return The new Partition object.
	*/
	Partition& operator=(const Partition& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new Partition object.
	*/
	Partition& operator=(const CRef& in_ref);

	/*! Returns the Partition type. A partition can be either an object or a light
	partition.
	\return The type of Partition
	*/
	XSI::siPartitionType GetPartitionType( ) const;

	/*! Returns true if the Partition is a background partition. A background partition is
	an undeletable system partition where new objects and lights are added by default.
	\return true if the Partition is a background partition.
	*/
	bool IsBackground( ) const;

	private:
	Partition * operator&() const;
	Partition * operator&();
};

};

#endif // __XSIPARTITION_H__
