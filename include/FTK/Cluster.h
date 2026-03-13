//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file Cluster.h
	\brief Defines the CSLCluster class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _CLUSTER_H
#define _CLUSTER_H

#include "Template.h"
#include "XSIClusterInfo.h"

#ifndef _SL_INT_ARRAY_PROXY_EXPORT_
#define _SL_INT_ARRAY_PROXY_EXPORT_

//XSITEMPLATEEXP template class XSIEXPORT CSLArrayProxy<SI_Int, SI_Int, 1>;

#endif // _SL_INT_ARRAY_PROXY_EXPORT_

// Forward declaration
class CSLWeightingType;
class CLSModel;
class CSLBaseShape;
class CSLUserDataList;


/*! \brief This class represents an \xx ftk_SI_Cluster SI_Cluster \endxx template.

	Describes a cluster (see the \xx ftk_SI_Cluster SI_Cluster \endxx
	template reference).
*/
class XSIEXPORT CSLCluster
	: public CSLTemplate
{
public:
	/*! Proxy class that allows modifying a list of SI_Int like an array.
	*/
	typedef CSLArrayProxy<SI_Int, SI_Int, 1> CSLIntArray;

	/*! The EClusterWeightingType enum contains possible weighting types for a cluster
	*/
	enum EClusterWeightingType
	{
		SI_AVERAGE,		/*!< The cluster uses an averaging function to determine weights */
		SI_ADDITIVE,	/*!< The cluster uses an additive function to determine weights */
	};

	/*! Synchronizes this cluster instance with its IO layer representation
		\retval SI_Error::SI_SUCCESS
	*/
    virtual SI_Error Synchronize();

	/*! Returns the template type of the cluster
		\retval CSLTemplate::SI_CLUSTER the template type
	*/
	virtual ETemplateType Type() { return SI_CLUSTER; }

	/*! Constructor
		\param[in] in_pScene	Pointer to the scene containing the Cluster
		\param[in] in_pModel	Pointer to the model containing the Cluster
		\param[in] in_pTemplate	Pointer to the CdotXSITemplate containing the Cluster
		\return an instance of CSLCluster
	*/
	CSLCluster(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	/*! Destructor
	*/
	virtual ~CSLCluster();

	/*!	Return the model possessing this cluster.
		\return Pointer to the model that has this cluster
	*/
	CSLModel* GetReference();

	/*!	Return the center of the cluster.
		\return Pointer to the cluster center model.
	*/
	CSLModel* GetCenter();

	/*!	Change the center of the cluster.
		\param[in]	in_pNewCenter	New cluster center object.
	*/
	SI_Void SetCenter(CSLModel* in_pNewCenter);

	/*!	Create a new shape for the cluster.
		\return Newly creates shape object.
	*/
	CSLBaseShape* CreateShape();

	/*!	Return the shape of the cluster.
		\return Pointer to a shape object.
	*/
	CSLBaseShape* Shape();

	/*!	Destroy the shape of the cluster.
		\return Error code.
	*/
	SI_Error DestroyShape();

	/*! Return the number of vertex indices.
		\return Number of vertex index.
	*/
	SI_Int GetVertexIndicesCount();

	/*! Return the vertex indices in an array proxy.
		\return Pointer to an array proxy of vertex indices.
	*/
	CSLIntArray* GetVertexIndicesList();

	/*!	Returns an array of SI_Int containing the vertex indices.
		\return Array of vertex indices.
	*/
	SI_Int* GetVertexIndicesListPtr();

	/*!	Return the type of weighting for the cluster.
		\return Type of weighting.
	*/
	EClusterWeightingType GetWeightingType();

	/*!	Change the type of weighting of the cluster.
		\param[in]	in_Type	New weighting type.
	*/
	SI_Void SetWeightingType(EClusterWeightingType in_Type);

	// Connection functions.
	/*!	Connects a shape to that cluster
		\param[in]	in_pNewShape	New shape to connect
		\return Pointer to the connected shape
	*/
	CSLBaseShape* ConnectShape(CSLBaseShape* in_pNewShape);

	///////////////////////////////////////////////////////////////////////////
	// UserDataList Functionality /////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	/*! Adds an user data list to the user data lists
	\return Pointer to the newly added UserDataList
	*/
	CSLUserDataList* AddUserDataList();

	/*! Removes an user data list from the user data lists
		\param[in] in_nIndex Index of the UserDataList to remove
		\return Whether or not the user data list could be removed
	*/
	SI_Error RemoveUserDataList( SI_Int in_nIndex );

	/*! Removes an user data list from the user data lists
		\param[in] in_pToRemove Pointer to the user data list to remove
		\return Whether or not the user data list could be removed
	*/
	SI_Error RemoveUserDataList( CSLUserDataList* in_pToRemove );

	/*! Removes all connections points from the user data lists
		\return Whether or not the list could be cleared
	*/
	SI_Error ClearUserDataLists();

	/*! Adds an exisiting user data list to the user data lists
		\param[in] in_pToConnect Pointer to the user data list to add
		\return The added user data list or NULL if it already exists in the list
	*/
	CSLUserDataList* ConnectUserDataList( CSLUserDataList* in_pToConnect );

	/*! Returns a pointer to the internally-stored user data list pointer list
		\return Pointer to the list
	*/
	CSLUserDataList** GetUserDataLists();

	/*! Returns the total number of user data lists
		\return Number of user data lists
	*/
	SI_Int GetUserDataListCount();

	/*! Searches for a given user data list
		\param[in] in_szUserDataListName Name of the user data list to look for
		\return Pointer to the user data list or null if it cannot be found
	*/
	CSLUserDataList* FindUserDataList( SI_Char* in_szUserDataListName );

	CSLXSIClusterInfo* GetClusterInfo();

	CSLXSIClusterInfo* ConnectClusterInfo(CSLXSIClusterInfo* in_pClusterInfo);

	virtual SI_Error Fix();

private:
	CSLStrEnumProxy<EClusterWeightingType, SI_ADDITIVE> m_WeightingType;

/*
	We might activate this once the cluster type are set to strings.  It is also possible
	that we will need to add a separate implementation of the whole class in 3.6.  If we do
	use the line below, the constructor will have to be updated as well.

	CSLStrEnumProxy<EClusterType, SI_SUB_CURVE> m_ClusterType;
*/

	CSLModel* m_pClusterCenter;
	CSLBaseShape* m_pShape;
	CSLIntArray m_VertexIndices;
	CSIBCArray<CSLUserDataList*> m_UserDataLists;

	void *m_pReserved;	// reserved for future extension
};

#endif
