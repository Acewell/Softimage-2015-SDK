//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file SIBCNode.h
	\brief Defines the CSIBCUserData and CSIBCNode classes

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

//***************************************************************************************
// Defines
//***************************************************************************************
#ifndef __CSIBCNode_H__
#define __CSIBCNode_H__

//***************************************************************************************
// Includes
//***************************************************************************************

#include <SIBCUtil.h>
#include <SIBCArray.h>
#include <SIBCString.h>
#include <SIBCMatrix.h>

/*! The release method is a function pointer which is called on object
	deletion to perform any additional destruction on an objects data
	(which is passed through the \c in_pObjectToDelete parameter.
*/
typedef	void (*SI_ReleaseMethod) (void *in_pObjectToDelete);


//***************************************************************************************
// CSIBCUserData | Base Class
//***************************************************************************************

/*! \brief Class that holds user data representation

	Instances of this class are created by instances of CSIBCNode objects or their derivatives
	using CSIBCNode::AttachUserData. These instances are stored within the CSIBCNode object
	until it is destroyed, at which point all user data object attached to it are destroyed
	aswell. These objects can also be used by an application outside of CSIBCNode objects, as
	an interface to user defined data.
*/
class XSICOREEXPORT CSIBCUserData
{
public:

	/*! Default constructor.
		Sets the data pointer, and release method for the data to \c NULL.
	*/
	CSIBCUserData()
	{
		m_pData = NULL;
		m_pReleaseMethod = (SI_ReleaseMethod)NULL;
		m_pUnused = NULL;
	};

	/*! Constructor.
		Sets the new object's data to the given parameters.

		\param[in] in_pName	The tag name associated with this object.
		\param[in] in_pData	Data pointer to the data associated with this object.
		\param[in] in_pReleaseMethod	Function pointer to the function used when this object is
				destroyed (NULL if no release method is required).
	*/
	CSIBCUserData
	(
		SI_Char				*in_pName,
		SI_Void				*in_pData,
		SI_ReleaseMethod	in_pReleaseMethod
	)
	{
		m_Name.SetText(in_pName);
		m_pData = in_pData;
		m_pReleaseMethod = in_pReleaseMethod;
		m_pUnused = NULL;
	};

	~CSIBCUserData()
	{
		if(m_pReleaseMethod != NULL)
			m_pReleaseMethod(m_pData);
	};

	/*! Returns a reference to the string which holds the tag name for this object.
		\return The tag name associated with this object
	*/
	CSIBCString 	&Name() { return m_Name; };

	/*! Returns a pointer to the data associated with this object.
		\return Pointer to the data associated with this object.
	*/
	virtual void	*GetData() { return m_pData; };

	/*! Sets the user data associated with this object
		\param[in] in_pData	Pointer to the data to be associated with this object
	*/
	virtual void	SetData(void *in_pData)
					{m_pData = in_pData;};

	/*! Gets the release method for this object.
		\return Function pointer to the release method for this object.
			NULL indicates no release method is used.
	*/
	virtual SI_ReleaseMethod	GetReleaseMethod()
					{ return m_pReleaseMethod; };

	/*! Sets the release method for this object.
		\param[in] in_pReleaseMethod	Pointer to the release method to be used on the user data pointer
			in this object, upon object deletion. NULL indicates that no function should be used.
	*/
	virtual SI_Void	SetReleaseMethod(SI_ReleaseMethod in_pReleaseMethod)
					{ m_pReleaseMethod = in_pReleaseMethod; };

private:
	CSIBCString			m_Name;
	SI_Void				*m_pData;
	SI_ReleaseMethod	m_pReleaseMethod;
	SI_Void				*m_pUnused;
};



//***************************************************************************************
// CSIBCNode | Base Class
//***************************************************************************************

/*! \brief Base class for most objects within the Crosswalk SDK.

	This class provides a set of methods available to all classes that are derived from
	it, including memory usage functions, identification functions, and functions dealing
	with user data, represented by CSIBCUserData objects.
*/
class XSICOREEXPORT CSIBCNode
{
public:

	//***************************************************************************************
	// constructor/destructor
	//***************************************************************************************

	/*! Default constructor.
		Simply clears all flags for the new node. (See CSIBCNode::SetFlags)
	*/
	CSIBCNode();

	virtual ~CSIBCNode();

	//***************************************************************************************
	// debug and profiling functions
	//***************************************************************************************

	/*! Outputs debugging information for the node. This method is over-ridable, but in
		this base class, it simply outputs the address of the node. Note: although this
		method is over-ridable, it is generally left to this base implementation.
	*/
	virtual void Dump();

	/*! Returns how much memory this node uses. This number does not include how much space
		the object itself requires (see CSIBCNode::LocalSize), only the memory used by its
		members. This number is distinct from the memory actually allocated by the object
		(See CSIBCNode::AllocatedMemory).

 		\return The amount of memory used by this object's members' (in bytes).
	*/
	virtual SI_UInt UsedMemory();

	/*! Returns how much memory this node has allocated. This number does not include how much space
		the object itself requires (see CSIBCNode::LocalSize), only the memory allocated by
		its members. This number is distinct from the memory actually used by the object
		(See CSIBCNode::UsedMemory).

		\return The amount of memory allocated by this object's members' (in bytes)
	*/
	virtual SI_UInt AllocatedMemory();

	/*!	Returns the size of this object (analogous to the sizeof operator). As such, it does
		not include any memory dynamically allocated by the members of the class.
	*/
	virtual SI_UInt LocalSize();

	//***************************************************************************************
	// properties
	//***************************************************************************************

	/*! Gets the name string for the object.
		\return Reference to the string which holds the name of this node.
	*/
	CSIBCString &Name() { return m_Name; }

	/*!	Get the flags associated with this node.
		\return Value indicating which flags are set for this node.
	*/
	SI_UInt GetFlags() { return m_Flags; }

	/*! Sets the flags associated with this node. Note that this function unsets all flags,
		thus if flags need to be persisted, they should first be obtained from SIBCNode::GetFlags,
		and bit-wise OR'd with the new flags, and then sent to this function.

		\param[in] in_lFlags	The new flag state for this node.
	*/
	SI_Void SetFlags(SI_UInt in_lFlags)
		{ m_Flags = in_lFlags; }

	/*! Returns a CSIBCArray of the user data attached to this node.
		\return Reference to the array of user data attached to this node.
	*/
	CSIBCArray < CSIBCUserData* > &UserDataList()
		{ return m_UserDataArray;}

	/*! Finds the first instance of CSIBCUserData attached to this node with the tag name
		given by \p in_pTag.
		\param[in]	in_pTag	The tag name to search attached user data objects for.
		\return Pointer to the first instance of user data attached to this node
			with tag name \p in_pTag. Returns NULL if no user data is attached with the tag name.
	*/
	CSIBCUserData *FindUserData(SI_Char *in_pTag);

	/*! Returns the user data attached at a given index.
		\param[in] in_iIndex	Index of the attached user data object to retrieve. Must be a valid index.
		\return Pointer to the user data element at the index given by \p in_iIndex
	*/
	CSIBCUserData *GetUserData(SI_Int in_iIndex);

	/*!	Attaches user data to this node. Creates a new CSIBCUserData object, containing
		\param[in] in_pTag	Tag name used to attach the data to the node. Must be unique per node.
		\param[in] in_pData	Pointer to the data to attach (may be of any type, cast to SI_Void *).
		\retval SI_Error::SI_SUCCESS The user data was attached properly
	*/
	SI_Error	   AttachUserData(SI_Char *in_pTag, SI_Void *in_pData);

	/*! Finds the first instance of CSIBCUserData attached to this node with the tag name
		given by \p in_pTag and remove it.
		\param[in]	in_pTag	The tag name of the user data object to remove.
		\return Error code indicating success or failure of function.
	*/
	SI_Error	RemoveUserData(SI_Char *in_pTag);

	//***************************************************************************************
	// methods
	//***************************************************************************************

	/*! Creates a duplicate node containing the information contained in this node. This
		method is intended to be over-ridden by subclasses, because the duplication process
		will always be derived class specific. If \p i_pNode is NULL, a new node is created
		to duplicate this node's information, otherwise, the data contained within \p i_pNode
		is overwritten by the information from this node.

		\param[in] i_pNode	Node to put the duplicate information into. If NULL, a new node is created.
		\return Pointer to the node containing the duplicated information
	*/
	virtual CSIBCNode *Duplicate(CSIBCNode * i_pNode);


protected:


private:
	CSIBCString						m_Name;
	CSIBCArray < CSIBCUserData* >	m_UserDataArray;
	SI_UInt							m_Flags;
	SI_Void							*m_pUnused;
};

#endif // CSIBCNode
