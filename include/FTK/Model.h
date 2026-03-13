//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file Model.h
	\brief Defines the CSLModel class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************
#ifndef _MODEL_H
#define _MODEL_H

#include "Template.h"
#include "ConstrainableType.h"

// Forward declaration
class CSLVisibility;
class CSLCluster;
class CSLTransform;
class CSLGlobalMaterial;
class CSLPrimitive;
class CSLMixer;
class CSLEnvelope;
class CSLFXTree;
class CSLXSITransform;
class CSLXSIBasePose;

/*! \brief This class represents an \xx ftk_SI_Model SI_Model \endxx template.

Handles the Model template (see the \xx ftk_SI_Model SI_Model \endxx
template reference).
*/
class XSIEXPORT CSLModel
    : public CSLTemplate
	, public CSLConstrainableType
{
public:
	/*! Constructor
		\param[in] in_pScene Parent Scene
		\param[in] in_pModel Parent Model
		\param[in] in_pTemplate Parent Template
		\return an instance of CSLModel
	*/
    CSLModel(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	//! Destructor
    virtual ~CSLModel();

	/*! Updates the template with information from this instance
		\return Whether or not the template could be updated
	*/
    virtual SI_Error Synchronize();

	/*! Returns the type of this template
		\retval CSLTemplate::SI_Model Template type
	*/
    virtual ETemplateType Type();

	/*! Returns a handle on one of this model's parameters by using its name
		\param[in] in_szName the name of the parameter to get the handle from
		\return the handle to the parameter
	*/
    virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);

	/*! Fixes all problems in the model to ensure it is valid
		\return Whether or not the model could be fixed
	*/
	virtual SI_Error Fix();

	/*! Adds a cluster to the cluster list
		\return Pointer to the newly added cluster
	*/
    CSLCluster* AddCluster();

	/*! Adds a constraint to the constraint list
		\param[in] in_ConstraintType Pointer to the newly added constraint
	*/
	CSLConstraint* AddConstraint(CSLConstraint::EConstraintType in_ConstraintType);

	/*! Removes a cluster from the cluster list
		\param[in] in_nIndex Index of the cluster to remove
		\return Whether or not the cluster could be removed
	*/
	SI_Error RemoveCluster( SI_Int in_nIndex );

	/*! Removes a cluster from the cluster list
		\param[in] in_pToRemove Pointer of the cluster to remove
		\return Whether or not the cluster could be removed
	*/
	SI_Error RemoveCluster( CSLCluster *in_pToRemove );

	/*! Returns the total number of clusters in the cluster list
		\return Number of clusters
	*/
	SI_Int GetClusterCount();

	/*! Returns the total number of envelopes in the envelope list
		\return Number of envelopes
	*/
	SI_Int GetEnvelopeCount();

	/*! Returns a pointer to the internally-stored cluster pointer list
		\return Pointer to the list
	*/
	CSLCluster** GetClusterList();

	/*! Returns a pointer to the internally-stored envelope pointer list
		\return Pointer to the list
	*/
	CSLEnvelope** GetEnvelopeList();

	/*! Removes all clusters from the internally-stored list and deallocate them
		\return Whether or not removal was a success
	*/
	SI_Error ClearClusters();

	/*! Removes the reference to the specified envelope
		\param[in] in_pToUnconnect Pointer to the envelope whose reference is to be removed
		\return Whether or not the removal was a success
	*/
	SI_Error UnconnectEnvelope( CSLEnvelope* in_pToUnconnect );

	/*! Adds a reference to an existing cluster
		\param[in] in_pNewCluster Pointer to the new object to refer to
		\return Pointer to the new reference
	*/
	CSLCluster* ConnectCluster( CSLCluster* in_pNewCluster );

	/*! Adds a reference to an existing envelope
		\param[in] in_pNewEnvelope Pointer to the new object to refer to
		\return Pointer to the new reference
	*/
	CSLEnvelope* ConnectEnvelope( CSLEnvelope* in_pNewEnvelope );

	/*! Returns the base position
		\return Pointer to the base position
	*/
    CSLTransform* GetBasePose();

	/*! Allocates and connects a new base position to the model
		\return Pointer to the newly allocated base position
	*/
    CSLTransform* CreateBasePose();

	/*! Deallocates the base position
		\return Whether or not the base position was removed
	*/
    SI_Error DestroyBasePose();

	/*! Returns the global material
		\return Pointer to the global material
	*/
    CSLGlobalMaterial* GlobalMaterial();

	/*! Adds a new GlobalMaterial to this model
		\return success or error
	*/
    SI_Error AddGlobalMaterial();

	/*! Returns the transform
		\return Pointer to the transform
	*/
	CSLTransform* Transform();

	/*! Returns visibility
		\return Pointer to the visibility
	*/
    CSLVisibility* Visibility();

	/*! Returns the parent of the model
		\return Pointer to the parent
	*/
	CSLModel* Parent();

	/*! Returns the primitive of the model
		\return Pointer to the primitive
	*/
    CSLPrimitive* Primitive();

	/*! Connects a mixer to the model
		\param[in] in_pNewMixer Mixer to connect
		\return Pointer to the newly connected mixer
	*/
	CSLMixer* ConnectMixer(CSLMixer *in_pNewMixer);

	/*! Allocates and connects a new mixer to the model
		\return Pointer to the newly allocated mixer
	*/
	virtual CSLMixer* CreateMixer();

	/*! Deallocates the mixer
		\return Whether or not the mixer was removed
	*/
	SI_Error DestroyMixer();

	/*! Returns the mixer
		\return Pointer to the mixer
	*/
	CSLMixer* Mixer();

	/*! Connects to an existing model
		\param[in] in_pNewModel Pointer to the model to connect
		\return Pointer to the newly connected model
	*/
	CSLModel* ConnectModel(CSLModel *in_pNewModel);

	/*! Connects to an existing visibility
		\param[in] in_pNewVisibility Pointer to the visibility to connect
		\return Pointer to the newly connected visibility
	*/
	CSLVisibility* ConnectVisibility(CSLVisibility *in_pNewVisibility);

	/*! Connects to an existing transform
		\param[in] in_pNewTransform Pointer to the transform to connect
		\return Pointer to the newly connected transform
	*/
	CSLTransform* ConnectTransform(CSLTransform *in_pNewTransform);

	/*! Connects to an existing base position
		\param[in] in_pNewBasePose Pointer to the base pose to connect
		\return Pointer to the newly connected base pose
	*/
	CSLTransform* ConnectBasePose(CSLTransform *in_pNewBasePose);

	/*! Connects to an existing primitive
		\param[in] in_pNewPrimitive Pointer to the primitive to connect
		\return Pointer to the newly connected primitive
	*/
	CSLPrimitive* ConnectPrimitive(CSLPrimitive *in_pNewPrimitive);

	/*! Connects to an existing global material
		\param[in] in_pNewGlobalMaterial Pointer to the global material to connect
		\return Pointer to the newly connected global material
	*/
	CSLGlobalMaterial* ConnectGlobalMaterial(CSLGlobalMaterial* in_pNewGlobalMaterial);

	// Primitive and children manipulation.

	/*! Returns the primitive type of this model
		\return Type of the primitive
	*/
	ETemplateType GetPrimitiveType();

	/*! Adds a camera to the children list
		\return Pointer to the new children
	*/
    virtual CSLModel* AddCamera();

	/*! Adds a camera to the children list
		\return Pointer to the new children
	*/
    virtual CSLModel* AddXSICamera();

	/*! Adds a curve list to the children list
		\return Pointer to the new children
	*/
    CSLModel* AddCurveList();

	/*! Adds a directional light to the children list
		\return Pointer to the new children
	*/
    virtual CSLModel* AddDirectionalLight();

	/*! Adds an IK Chain to the children list
		\param[in] in_nNbJoints	Number of joints
		\return Pointer to the new children
	*/
    CSLModel* AddIKChain(SI_Int in_nNbJoints);

	/*! Adds an IK Root to the children list
		\return Pointer to the new children
	*/
    CSLModel* AddIKRoot();

	/*! Adds an IK Joint to the children list
		\return Pointer to the new children
	*/
    CSLModel* AddIKJoint();

	/*! Adds an IK effector to the children list
		\return Pointer to the new children
	*/
    CSLModel* AddIKEffector();

	/*! Adds an infinite light to the children list
		\return Pointer to the new children
	*/
    virtual CSLModel* AddInfiniteLight();

	/*! Adds an instance to the children list
		\return Pointer to the new children
	*/
    virtual CSLModel* AddInstance();

	/*! Adds a mesh to the children list
		\return Pointer to the new children
	*/
    CSLModel* AddMesh();

	/*! Adds a mesh to the children list
		\return Pointer to the new children
	*/
	virtual CSLModel* AddXSIMesh();

	/*! Adds a model to the children list
		\return Pointer to the new children
	*/
    virtual CSLModel* AddModel();

	/*! Adds a null object to the children list
		\return Pointer to the new children
	*/
    CSLModel* AddNull();

	/*! Adds a patch to the children list
		\return Pointer to the new children
	*/
    CSLModel* AddPatch();

	/*! Adds a point light to the children list
		\return Pointer to the new children
	*/
    virtual CSLModel* AddPointLight();

	/*! Adds a spot light to the children list
		\return Pointer to the new children
	*/
    virtual CSLModel* AddSpotLight();

	/*! Adds a surface mesh to the children list
		\return Pointer to the new children
	*/
    CSLModel* AddSurfaceMesh();

	/*! Returns the children of the model
		\return List of the children
	*/
    CSLModel** GetChildrenList();

	/*! Deallocates all the children of the model
		\return Whether or not clearance was a success
	*/
    SI_Error ClearChildren();

	/*! Returns the number of children
		\return Number of children
	*/
    SI_Int GetChildrenCount();

	/*! Removes a child
		\param[in] in_pChild Pointer to the child to remove
		\return Whether or not removal was a success
	*/
    SI_Error RemoveChild(CSLModel* in_pChild);

	/*! Removes a child
		\param[in] in_nIndex Index of the child to remove
		\return Whether or not removal was a success
	*/
    SI_Error RemoveChild(SI_Int in_nIndex);

	/*! Sets a new parent for the model
		\param[in] in_pNewParent The new parent
		\return Whether or not reparenting was a success
	*/
	SI_Error Reparent(CSLModel *in_pNewParent);

	/*! Adds an FX tree to the FX tree list
		\return Pointer to the newly added FX tree
	*/
	CSLFXTree* AddFXTree();

	/*! Removes an FX tree from the FX tree list
		\param[in] in_nIndex Index of the FX tree to remove
		\return Whether or not the FX tree could be removed
	*/
	SI_Error RemoveFXTree( SI_Int in_nIndex );

	/*! Removes an FX tree from the FX tree list
		\param[in] in_pToRemove Pointer to the FX tree to remove
		\return Whether or not the FX tree could be removed
	*/
	SI_Error RemoveFXTree( CSLFXTree* in_pToRemove );

	/*! Removes all connections points from the FX tree list
		\return Whether or not the list could be cleared
	*/
	SI_Error ClearFXTrees();

	/*! Adds an exisiting FX tree to the FX tree list
		\param[in] in_pToConnect Pointer to the FX tree to add
		\return The added FX tree or null if it already exists in the list
	*/
	CSLFXTree* ConnectFXTree( CSLFXTree* in_pToConnect );

	/*! Returns a pointer to the internally-stored FX tree pointer list
		\return Pointer to the list
	*/
	CSLFXTree** GetFXTreeList();

	/*! Returns the total number of FXTrees
		\return Number of FXTrees
	*/
	SI_Int GetFXTreeCount();

	/*! Searches for a given FX tree
		\param[in] in_szFXTreeName Name of the FX tree to look for
		\return Pointer to the FX tree or null if it cannot be found
	*/
	CSLFXTree* FindFXTree( SI_Char* in_szFXTreeName );

	/*! Returns the transform
		\return Pointer to the transform
	*/
	CSLXSITransform* XSITransform();

	/*! Connects to an existing transform
		\param[in] in_pNewTransform Pointer to the transform to connect
		\return Pointer to the newly connected transform
	*/
	CSLXSITransform* ConnectXSITransform(CSLXSITransform *in_pNewTransform);

	/*! Returns the base pose
		\return Pointer to the base pose
	*/
	CSLXSIBasePose* GetXSIBasePose();

	/*! Connects to an existing base pose
		\param[in] in_pNewBasePose Pointer to the basepose to connect
		\return Pointer to the newly connected basepose
	*/
	CSLXSIBasePose* ConnectXSIBasePose(CSLXSIBasePose *in_pNewBasePose);

	/*! Allocates and connects a new base position to the model
		\return Pointer to the newly allocated base position
	*/
    CSLXSIBasePose* CreateXSIBasePose();

	/*! Deallocates the base pose
		\return Whether or not the base pose was removed
	*/
    SI_Error DestroyXSIBasePose();

	/*!	Return the name (string) of a specified parameter.
		\param[in]	in_pParameter	The parameter
		\return Name of the parameter.
	*/
    virtual const SI_Char* GetParameterName(CSLAnimatableType* in_pParameter);

	/*! Unconnects a child model
		\param[in] in_pModel the child model to unconnect
		\return success or failure
	*/
	SI_Error UnconnectModel(CSLModel *in_pModel);

protected:

	CSLModel* CreateLightTemplate(CdotXSITemplate **out_ppLightTemplate);
	SI_Bool FindSpecificChildrenRecursively(CSLModel *in_pSource, CSLModel *in_pTarget);

    CSLVisibility* m_pVisibility;
    CSIBCArray<CSLCluster*> m_Clusters;
    CSLMixer* m_pMixer;
	CSIBCArray<CSLEnvelope*> m_Envelopes;
    CSLTransform* m_pLocalTransform;
    CSLTransform* m_pBasepose;
    CSLGlobalMaterial* m_pGlobalMaterial;
    CSLPrimitive* m_pPrimitive;
    CSIBCArray<CSLModel*> m_Children;
	CSIBCArray<CSLFXTree*> m_FXTrees;
	CSLXSITransform* m_pXSITransform;
	CSLXSIBasePose* m_pXSIBasePose;
};

#endif
