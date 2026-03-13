//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSITransform.h
	\brief Defines the CSLXSITranslate, CSLXSIRotate, CSLXSIScale, CSLXSIShear, CSLXSILookat,
		CSLXSIMatrix, CSLXSIPolymatricks, CSLXSITransform, and CSLXSIBasePoseclasses

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************
#ifndef _XSITRANSFORM_H
#define _XSITRANSFORM_H

#include "Template.h"
#include "XSILimit.h"

/*! \brief This class represents an \xx ftk_XSI_Translate XSI_Translate \endxx template.

	This class handles a translation in the polymatricks operator of a model (see the
	\xx ftk_XSI_Translate XSI_Translate \endxx template reference).
*/
class XSIEXPORT CSLXSITranslate
    : public CSLTemplate
{
public:
    CSLXSITranslate(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
    virtual ~CSLXSITranslate();

    virtual ETemplateType Type();

	virtual SI_Error Synchronize();

	CSIBCVector3D		GetTranslation();
	CSLVector3DProxy&	GetTranslationProxy();
	void				SetTranslation(CSIBCVector3D& in_Translation);

	virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);
    virtual CSLAnimatableType* ParameterFromType(EFCurveType in_Type, SI_Char *in_szParameterName);

	/*!	Returns the name (string) of a specified sub parameter.
		\param[in]	in_pParameter	The sub parameter
		\return Name of the sub parameter.
	*/
    virtual const SI_Char* GetParameterName(CSLAnimatableType* in_pParameter);
private:
	CSLVector3DProxy	m_Translation;
};

/*! \brief This class represents an \xx ftk_XSI_Rotate XSI_Rotate \endxx template.

	Handles a rotation in the polymatricks operator of a model (see the \xx ftk_XSI_Rotate XSI_Rotate \endxx
	template reference).
*/
class XSIEXPORT CSLXSIRotate
    : public CSLTemplate
{
public:
    CSLXSIRotate(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
    virtual ~CSLXSIRotate();

    /*! Returns the type of this template
    	\retval CSLTemplate::XSI_ROTATE Template type
    */
    virtual ETemplateType Type();

	virtual SI_Error Synchronize();

	CSIBCVector3D		GetAxis();
	CSLVector3DProxy&	GetAxisProxy();
	void				SetAxis(CSIBCVector3D& in_Axis);

	float				GetAngle();
	CSLFloatProxy&		GetAngleProxy();
	void				SetAngle(float in_Angle);

	virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);
    virtual CSLAnimatableType* ParameterFromType(EFCurveType in_Type, SI_Char *in_szParameterName);

	/*!	Returns the name (string) of a specified sub parameter.
		\param[in]	in_pParameter	The sub parameter
		\return Name of the sub parameter.
	*/
    virtual const SI_Char* GetParameterName(CSLAnimatableType* in_pParameter);
private:
	CSLVector3DProxy	m_Axis;
	CSLFloatProxy		m_Angle;
};

/*! \brief This class represents an \xx ftk_XSI_Scale XSI_Scale \endxx template.

	Handles a scale in the polymatricks operator of a model (see the \xx ftk_XSI_Scale XSI_Scale \endxx
	template reference).
*/
class XSIEXPORT CSLXSIScale
    : public CSLTemplate
{
public:
    CSLXSIScale(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
    virtual ~CSLXSIScale();

    /*! Returns the type of this template
    	\retval CSLTemplate::XSI_SCALE Template type
    */
    virtual ETemplateType Type();

	virtual SI_Error Synchronize();

	CSIBCVector3D		GetScale();
	CSLVector3DProxy&	GetScaleProxy();
	void				SetScale(CSIBCVector3D& in_Scale);

	virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);
    virtual CSLAnimatableType* ParameterFromType(EFCurveType in_Type, SI_Char *in_szParameterName);

	/*!	Returns the name (string) of a specified sub parameter.
		\param[in]	in_pParameter	The sub parameter
		\return Name of the sub parameter.
	*/
    virtual const SI_Char* GetParameterName(CSLAnimatableType* in_pParameter);
private:
	CSLVector3DProxy	m_Scale;
};

/*! \brief This class represents an \xx ftk_XSI_Shear XSI_Shear \endxx template.

	Handles a shear in the polymatricks operator of a model (see the \xx ftk_XSI_Shear XSI_Shear \endxx
	template reference).
*/
class XSIEXPORT CSLXSIShear
    : public CSLTemplate
{
public:
    CSLXSIShear(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
    virtual ~CSLXSIShear();

    /*! Returns the type of this template
    	\retval CSLTemplate::XSI_SHEAR Template type
    */
    virtual ETemplateType Type();

	virtual SI_Error Synchronize();

	CSIBCVector3D		GetFirstAxis();
	CSLVector3DProxy&	GetFirstAxisProxy();
	void				SetFirstAxis(CSIBCVector3D& in_Axis);

	CSIBCVector3D		GetSecondAxis();
	CSLVector3DProxy&	GetSecondAxisProxy();
	void				SetSecondAxis(CSIBCVector3D& in_Axis);

	float				GetAngle();
	CSLFloatProxy&		GetAngleProxy();
	void				SetAngle(float in_Angle);

	virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);
    virtual CSLAnimatableType* ParameterFromType(EFCurveType in_Type, SI_Char *in_szParameterName);

	/*!	Returns the name (string) of a specified sub parameter.
		\param[in]	in_pParameter	The sub parameter
		\return Name of the sub parameter.
	*/
    virtual const SI_Char* GetParameterName(CSLAnimatableType* in_pParameter);
private:
	CSLVector3DProxy	m_Axis1;
	CSLVector3DProxy	m_Axis2;
	CSLFloatProxy		m_Angle;
};

/*! \brief This class represents an \xx ftk_XSI_Lookat XSI_Lookat \endxx template.

	Handles a lookat in the polymatricks operator of a model (see the \xx ftk_XSI_Lookat XSI_Lookat \endxx
	template reference).
*/
class XSIEXPORT CSLXSILookat
    : public CSLTemplate
{
public:
    CSLXSILookat(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
    virtual ~CSLXSILookat();

    /*! Returns the type of this template
    	\retval CSLTemplate::XSI_LOOKAT Template type
    */
    virtual ETemplateType Type();

	virtual SI_Error Synchronize();

	CSIBCVector3D		GetPosition();
	CSLVector3DProxy&	GetPositionProxy();
	void				SetPosition(CSIBCVector3D& in_Position);
	CSIBCVector3D		GetInterest();
	CSLVector3DProxy&	GetInterestProxy();
	void				SetInterest(CSIBCVector3D& in_Interest);
	CSIBCVector3D		GetUpvector();
	CSLVector3DProxy&	GetUpvectorProxy();
	void				SetUpvector(CSIBCVector3D& in_Upvector);

	virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);
    virtual CSLAnimatableType* ParameterFromType(EFCurveType in_Type, SI_Char *in_szParameterName);
	/*!	Returns the name (string) of a specified sub parameter.
		\param[in]	in_pParameter	The sub parameter
		\return Name of the sub parameter.
	*/
    virtual const SI_Char* GetParameterName(CSLAnimatableType* in_pParameter);

private:
	CSLVector3DProxy	m_Position;
	CSLVector3DProxy	m_Interest;
	CSLVector3DProxy	m_Upvector;
};

/*! \brief This class represents an \xx ftk_XSI_Matrix XSI_Matrix \endxx template.

	Handles a matrix in the polymatricks operator of a model (see the \xx ftk_XSI_Matrix XSI_Matrix \endxx
	template reference).
*/
class XSIEXPORT CSLXSIMatrix
    : public CSLTemplate
{
public:
    CSLXSIMatrix(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
    virtual ~CSLXSIMatrix();

    /*! Returns the type of this template
    	\retval CSLTemplate::XSI_MATRIX Template type
    */
    virtual ETemplateType Type();

	virtual SI_Error Synchronize();

	CSIBCMatrix4x4		GetMatrix();
	void				SetMatrix(CSIBCMatrix4x4& in_Matrix);

	virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);
    virtual CSLAnimatableType* ParameterFromType(EFCurveType in_Type, SI_Char *in_szParameterName);

	/*!	Returns the name (string) of a specified sub parameter.
		\param[in]	in_pParameter	The sub parameter
		\return Name of the sub parameter.
	*/
    virtual const SI_Char* GetParameterName(CSLAnimatableType* in_pParameter);
private:
	CSLMatrix4x4Proxy	m_Matrix;
};

/*! \brief This class represents an \xx ftk_XSI_Polymatricks XSI_Polymatricks \endxx template.

	Handles the polymatricks operator of a model (see the \xx ftk_XSI_Polymatricks XSI_Polymatricks \endxx
	template reference).
*/
class XSIEXPORT CSLXSIPolymatricks
    : public CSLTemplate
{
public:
    CSLXSIPolymatricks(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
    virtual ~CSLXSIPolymatricks();

    /*! Returns the type of this template
    	\retval CSLTemplate::XSI_POLYMATRICKS Template type
    */
    virtual ETemplateType Type();

	virtual SI_Error Synchronize();

	CSLTemplate**				GetTransformNodes();
	int							GetTransformNodeCount();
	SI_Error					RemoveTransformNode(CSLTemplate *in_pNode);
	SI_Error					RemoveTransformNode(int index);
	SI_Error					ClearTransformNodes();

	CSLXSITranslate*			AddXSITranslate();
	CSLXSIRotate*				AddXSIRotate();
	CSLXSIScale*				AddXSIScale();
	CSLXSIShear*				AddXSIShear();
	CSLXSILookat*				AddXSILookat();
	CSLXSIMatrix*				AddXSIMatrix();

	CSLXSITranslate*			ConnectXSITranslate(CSLXSITranslate *in_pNode);
	CSLXSIRotate*				ConnectXSIRotate(CSLXSIRotate *in_pNode);
	CSLXSIScale*				ConnectXSIScale(CSLXSIScale *in_pNode);
	CSLXSIShear*				ConnectXSIShear(CSLXSIShear *in_pNode);
	CSLXSILookat*				ConnectXSILookat(CSLXSILookat *in_pNode);
	CSLXSIMatrix*				ConnectXSIMatrix(CSLXSIMatrix *in_pNode);

    virtual const SI_Char*		GetParameterName(CSLAnimatableType* in_pParameter);

private:
	CSIBCArray<CSLTemplate*>	m_TransformNodes;
};

/*! \brief This class represents an \xx ftk_XSI_Translate XSI_Translate \endxx template.

	Handles the transformation matrix of a model. It provides functions to set
	all aspects of the transformation like SRT, pivots, shearing, etc (see the
	\xx ftk_XSI_Translate XSI_Translate \endxx template reference).
*/
class XSIEXPORT CSLXSITransform
    : public CSLTemplate
{
public:
    CSLXSITransform(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
    virtual ~CSLXSITransform();

	/*!	Returns the transformation matrix.
		\return Transformation matrix.
	*/
	CSIBCMatrix4x4 GetMatrix();

	/*!	Returns the actual rotation in euler representation.
		\return Rotation value.
	*/
	CSIBCVector3D GetEulerRotation();

	/*!	Changes the rotation value in euler representation.
		\param[in]	in_rValue	New rotation value
	*/
	SI_Void SetEulerRotation(CSIBCVector3D &in_rValue);

	/*!	Returns the actual scale.
		\return Scale value.
	*/
	CSIBCVector3D GetScale();

	/*!	Changes the scale value.
		\param[in]	in_rValue	New scale value
	*/
	SI_Void SetScale(CSIBCVector3D &in_rValue);

	/*!	Returns the actual translation.
		\return Translation value.
	*/
	CSIBCVector3D GetTranslation();

	/*!	Changes the translation value.
		\param[in]	in_rValue	New translation value
	*/
	SI_Void SetTranslation(CSIBCVector3D &in_rValue);

	/*!	Returns the shear.
		\return Shear value.
	*/
	CSIBCVector3D GetShear();

	/*!	Changes the shear value.
		\param[in]	in_rValue	New translation value
	*/
	SI_Void SetShear(CSIBCVector3D &in_rValue);

	/*!	Returns the pivot position.
		\return Pivot position value.
	*/
	CSIBCVector3D GetPivotPosition();

	/*!	Changes the pivot position value.
		\param[in]	in_rValue	New pivot position value
	*/
	SI_Void SetPivotPosition(CSIBCVector3D &in_rValue);

	/*!	Returns the pivot rotation.
		\return Pivot rotation value.
	*/
	CSIBCVector3D GetPivotRotation();

	/*!	Changes the pivot rotation value.
		\param[in]	in_rValue	New pivot rotation value
	*/
	SI_Void SetPivotRotation(CSIBCVector3D &in_rValue);

	/*!	Returns the pivot scale.
		\return Pivot scale value.
	*/
	CSIBCVector3D GetPivotScale();

	/*!	Changes the pivot scale value.
		\param[in]	in_rValue	New translation value
	*/
	SI_Void SetPivotScale(CSIBCVector3D &in_rValue);

	/*!	Returns the pivot compensation position.
		\return pivot compensation position value.
	*/
	CSIBCVector3D GetPivotCompPosition();

	/*!	Changes the pivot compensation position value.
		\param[in]	in_rValue	New pivot compensation position value
	*/
	SI_Void SetPivotCompPosition(CSIBCVector3D &in_rValue);

	/*!	Returns the pivot compensation rotation.
		\return pivot compensation rotation value.
	*/
	CSIBCVector3D GetPivotCompRotation();

	/*!	Changes the pivot compensation rotation value.
		\param[in]	in_rValue	New pivot compensation rotation value
	*/
	SI_Void SetPivotCompRotation(CSIBCVector3D &in_rValue);

	/*!	Returns the pivot compensation scale.
		\return pivot compensation scale value.
	*/
	CSIBCVector3D GetPivotCompScale();

	/*!	Changes the pivot compensation scale value.
		\param[in]	in_rValue	New pivot compensation scale value
	*/
	SI_Void SetPivotCompScale(CSIBCVector3D &in_rValue);

	/*!	Returns the neutral pose position.
		\return neutral pose position value.
	*/
	CSIBCVector3D GetNeutralPosePosition();

	/*!	Changes the neutral pose position value.
		\param[in]	in_rValue	New neutral pose position value
	*/
	SI_Void SetNeutralPosePosition(CSIBCVector3D &in_rValue);

	/*!	Returns the neutral pose rotation.
		\return neutral pose rotation value.
	*/
	CSIBCVector3D GetNeutralPoseRotation();

	/*!	Changes the neutral pose rotation value.
		\param[in]	in_rValue	New neutral pose rotation value
	*/
	SI_Void SetNeutralPoseRotation(CSIBCVector3D &in_rValue);

	/*!	Returns the neutral pose scale.
		\return neutral pose scale value.
	*/
	CSIBCVector3D GetNeutralPoseScale();

	/*!	Changes the neutral pose scale value.
		\param[in]	in_rValue	New neutral pose scale value
	*/
	SI_Void SetNeutralPoseScale(CSIBCVector3D &in_rValue);

	/*!	Returns the neutral pose shear.
		\return neutral pose shear value.
	*/
	CSIBCVector3D GetNeutralPoseShear();

	/*!	Changes the neutral pose shear value.
		\param[in]	in_rValue	New neutral pose shear value
	*/
	SI_Void SetNeutralPoseShear(CSIBCVector3D &in_rValue);

	/*!	Returns the hirearchical scaling flag.
		\return hirearchical scaling flag value.
	*/
	SI_Bool GetHierarchicalScaling();

	/*!	Changes the hirearchical scaling flag value.
		\param[in]	in_bValue	New hirearchical scaling flag value
	*/
	SI_Void SetHierarchicalScaling(SI_Bool in_bValue);

	/*!	Returns the rotation order.
		\return Rotation order.
	*/
	CSLTemplate::ERotationOrder	GetRotationOrder();

	/*!	Returns the rotation order as a string.
		\return Rotation order.
	*/
	const SI_Char*				GetRotationOrderAsString();

	/*!	Changes the rotation order.
		\return Operation successful or not.
	*/
	SI_Error					SetRotationOrder(CSLTemplate::ERotationOrder /*!< New rotation order */);

	/*!	Changes the rotation order using a string value.
		\return Operation successful or not.
	*/
	SI_Error					SetRotationOrderAsString(const SI_Char* /*!< New rotation order */);


	/*!	Computes this CSLTransform's local matrix.
	\return	Error code
	*/
	SI_Error ComputeLocalMatrix();

	/*!	Computes this CSLTransform's global matrix.
	\return	Error code
	*/
	SI_Error ComputeGlobalMatrix();

	/*!	Returns the global matrix
	\return The global matrix
	*/
	CSIBCMatrix4x4 &GetGlobalMatrix();

	/*!	Computes this CSLTransform's local matrix at the specified time value.
	\param[in]	in_fTime	The time
	\return	Error code
	*/
	SI_Error ComputeLocalMatrix( SI_Float in_fTime );

	/*!	Computes this CSLTransform's global matrix at the specified time value.
		Also forces an evaluation of the parent global matrix to ensure a correct global matrix.
		\param[in]	in_fTime	The time
		\return	Error code
	*/
	SI_Error ComputeGlobalMatrix( SI_Float in_fTime );



	virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);
    virtual CSLAnimatableType* ParameterFromType(EFCurveType in_Type, SI_Char *in_szParameterName);

    /*! Returns the type of this template
    	\retval CSLTemplate::XSI_TRANSFORM Template type
    */
    virtual ETemplateType Type();

	virtual SI_Error Synchronize();

	/*!	Returns the name (string) of a specified sub parameter.
		\param[in]	in_pParameter	The sub parameter
		\return Name of the sub parameter.
	*/
    virtual const SI_Char* GetParameterName(CSLAnimatableType* in_pParameter);

	/*!	Returns the proxy to the scale vector
	\return	Proxy to the scale vector
	*/
	CSLVector3DProxy*	ScaleProxy() { return &m_Scale;};

	/*!	Returns the proxy to the hierarchical scaling value
	\return	Proxy to the hierarchical scaling value
	*/
	CSLBoolProxy*		HierarchicalScalingProxy() { return &m_HierarchicalScaling;};

	/*! Returns the proxy to the Rotation vector
	\return Proxy to the Rotation vector
	*/
	CSLVector3DProxy*	RotationProxy() { return &m_Rotation;};
	/*! Returns the proxy to the Translation vector
	\return Proxy to the Translation vector
	*/
	CSLVector3DProxy*	TranslationProxy() { return &m_Translation;};
	/*! Returns the proxy to the Shear vector
	\return CSLVector3DProxy*
	*/
	CSLVector3DProxy*	ShearProxy() { return &m_Shear;};

	/*! Returns the proxy to the Pivot Position vector
	\return Proxy to the Pivot Position vector
	*/
	CSLVector3DProxy*	PivotPositionProxy() { return &m_PivotPosition;};
	/*! Returns the proxy to the Pivot Rotation vector
	\return Proxy to the Pivot Rotation vector
	*/
	CSLVector3DProxy*	PivotRotationProxy() { return &m_PivotRotation;};
	/*! Returns the proxy to the Pivot Scale vector
	\return Proxy to the Pivot Scale vector
	*/
	CSLVector3DProxy*	PivotScaleProxy() { return &m_PivotScale;};

	/*! Returns the proxy to the Pivot Comp Position vector
	\return Proxy to the Pivot Comp Position vector
	*/
	CSLVector3DProxy*   PivotCompPositionProxy() { return &m_PivotCompPosition;};
	/*! Returns the proxy to the Pivot Comp Rotation vector
	\return Proxy to the Pivot Comp Rotation vector
	*/
	CSLVector3DProxy*	PivotCompRotationProxy() { return &m_PivotCompRotation;};
	/*! Returns the proxy to the Pivot Comp Scale vector
	\return Proxy to the Pivot Comp Scale vector
	*/
	CSLVector3DProxy*	PivotCompScaleProxy() { return &m_PivotCompScale;};

	/*! Returns the proxy to the Neutral Pose Scale vector
	\return Proxy to the Neutral Pose Scale vector
	*/
	CSLVector3DProxy*	NeutralPoseScaleProxy() { return &m_NeutralPoseScale;};
	/*! Returns the proxy to the Neutral Pose Rotation vector
	\return Proxy to the Neutral Pose Rotation vector
	*/
	CSLVector3DProxy*	NeutralPoseRotationProxy() { return &m_NeutralPoseRotation;};
	/*! Returns the proxy to the Neutral Pose Position vector
	\return Proxy to the Neutral Pose Position vector
	*/
	CSLVector3DProxy*	NeutralPosePositionProxy() { return &m_NeutralPosePosition;};
	/*! Returns the proxy to the Neutral Pose Shear vector
	\return Proxy to the Neutral Pose Shear vector
	*/
	CSLVector3DProxy*	NeutralPoseShearProxy() { return &m_NeutralPoseShear;};
	/*! Returns the proxy to the Rotation Order value
	\return Proxy to the Rotation Order value
	*/
	CSLStrEnumProxy<ERotationOrder, SI_ZYX>* RotationOrderProxy() { return &m_RotationOrder;};

	SI_Void SetMatrix ( CSIBCMatrix4x4& in_mMatrix ) { m_TransformMatrix = in_mMatrix;  m_bCanDecompose = false; };
	bool	CanDecompose ( ) { return m_bCanDecompose; };

	////////////// LIMIT
	/*!	Connects a limit to this template
		\param[in]	in_pXSILimit	the limit to connect
		\return Pointer to the specified limit
	*/
	CSLXSILimit *ConnectXSILimit(CSLXSILimit *in_pXSILimit);


	/*!	Adds a limit to this template
		\param[in] in_pParameter Animatable type of limit to add
		\return Pointer to the newly created limit, NULL if failed
	*/
	CSLXSILimit* AddXSILimit(CSLAnimatableType* in_pParameter);

	/*!	Clears all limits on that template
		\return	Whether the function failed or succeeded
	*/
	SI_Error ClearXSILimits();

	/*!	Returns the list of limits on that template
		\return Array of limits
	*/
	CSLXSILimit** GetXSILimitList();

	/*!	Returns the number of limits on that template
		\return Number of limits on that template
	*/
	SI_Int GetXSILimitCount();

	/*!	Removes a limit by index
		\param[in] in_nIndex Index of limit to remove
		\return Whether the function failed or succeeded
	*/
	SI_Error RemoveXSILimit(SI_Int in_nIndex);

	/*!	Removes a limit
		\param[in] in_pToRemove Limit to remove
		\return Whether the function failed or succeeded
	*/
	SI_Error RemoveXSILimit(CSLXSILimit *in_pToRemove);

	CSLXSIPolymatricks*	CreatePolymatricks();
	CSLXSIPolymatricks*	GetPolymatricks();
	void				ConnectPolymatricks(CSLXSIPolymatricks* in_pPolymatricks);
	bool				CollapsePolymatricks();

private:
	void										MoveAnimation(CSLTemplate* in_pFrom, CSLAnimatableType *in_pOldParam, CSLAnimatableType *in_pNewParam, const char* in_pNewName);

private:
	CSLStrEnumProxy<ERotationOrder, SI_ZYX>		m_RotationOrder;

    CSLVector3DProxy 							m_Scale;
	CSLBoolProxy	 							m_HierarchicalScaling;
    CSLVector3DProxy 							m_Rotation;
    CSLVector3DProxy 							m_Translation;
	CSLVector3DProxy 							m_Shear;

	CSLVector3DProxy 							m_PivotPosition;
	CSLVector3DProxy 							m_PivotRotation;
	CSLVector3DProxy 							m_PivotScale;

	CSLVector3DProxy 							m_PivotCompPosition;
	CSLVector3DProxy 							m_PivotCompRotation;
	CSLVector3DProxy 							m_PivotCompScale;

	CSLVector3DProxy 							m_NeutralPoseScale;
    CSLVector3DProxy 							m_NeutralPoseRotation;
    CSLVector3DProxy 							m_NeutralPosePosition;
	CSLVector3DProxy 							m_NeutralPoseShear;

	CSIBCMatrix4x4 								m_TransformMatrix;
	CSIBCMatrix4x4 								m_GlobalMatrix;
	bool										m_bCanDecompose;

    CSIBCArray<CSLXSILimit *>					m_XSILimits;
	CSLXSIPolymatricks*							m_pPolymatricks;
	void *										m_pReserved;	// reserved for future extension
};

/*! \brief This class represents an \xx ftk_XSI_BasePose XSI_BasePose \endxx template.

	Handles the base pose matrix of a model (see the \xx ftk_XSI_BasePose XSI_BasePose \endxx
	template reference). It provides functions to set all aspects of the base pose like SRT, pivots,
	shearing, etc.
*/
class XSIEXPORT CSLXSIBasePose
    : public CSLTemplate
{
public:
    CSLXSIBasePose(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
    virtual ~CSLXSIBasePose();

	/*!	Returns the BasePoseation matrix.
		\return Base pose matrix.
	*/
	CSIBCMatrix4x4 GetMatrix();

	/*!	Returns the actual rotation in euler representation.
		\return Rotation value.
	*/
	CSIBCVector3D GetEulerRotation();

	/*!	Changes the rotation value in euler representation.
		\param[in]	in_rValue	New rotation value
	*/
	SI_Void SetEulerRotation(const CSIBCVector3D &in_rValue);

	/*!	Return the actual scale.
		\return Scale value.
	*/
	CSIBCVector3D GetScale();

	/*!	Changes the scale value.
		\param[in]	in_rValue	New scale value
	*/
	SI_Void SetScale(CSIBCVector3D &in_rValue);

	/*!	Returns the actual translation.
		\return Translation value.
	*/
	CSIBCVector3D GetTranslation();

	/*!	Changes the translation value.
		\param[in]	in_rValue	New translation value
	*/
	SI_Void SetTranslation(CSIBCVector3D &in_rValue);

	virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);
    virtual CSLAnimatableType* ParameterFromType(EFCurveType in_Type, SI_Char *in_szParameterName);

    /*! Returns the type of this template
    	\retval CSLTemplate::XSI_BASEPOSE Template type
    */
    virtual ETemplateType Type();

	virtual SI_Error Synchronize();

	/*!	Returns the name (string) of a specified sub parameter.
		\param[in]	in_pParameter	The sub parameter
		\return Name of the sub parameter.
	*/
    virtual const SI_Char* GetParameterName(CSLAnimatableType* in_pParameter);

	/*!	Computes this CSLBasePose's local matrix.
	\return	Error code
	*/
	SI_Error ComputeMatrix();

	/*! Returns the value of the scale proxy vector.
		\return Scale proxy vector value
	*/
	CSLVector3DProxy& GetScaleProxy();

	/*! Returns the value of the rotation proxy vector.
		\return Rotation proxy vector value
	*/
	CSLVector3DProxy& GetRotationProxy();

	/*! Returns the value of the Translation proxy vector.
		\return Translation proxy vector value
	*/
	CSLVector3DProxy& GetTranslationProxy();

	/*!	Changes the base pose matrix values. The scale, rotation and translation values are also updated.
		\param[in]	in_Matrix	The matrix that contains the new values
	*/
	SI_Void SetMatrix( CSIBCMatrix4x4 &in_Matrix );

private:
    CSLVector3DProxy m_Scale;
    CSLVector3DProxy m_Rotation;
    CSLVector3DProxy m_Translation;
	CSIBCMatrix4x4 m_BasePoseMatrix;

	void *m_pReserved;	// reserved for future extension
};


#endif
