//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file XSIShapeReference.h
	\brief Defines the CSLXSIShapeReference class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _XSISHAPEREFERENCE_H
#define _XSISHAPEREFERENCE_H

#include "Template.h"

// Forward declaration
class CSLXSIShape;

/*! \brief This class represents an \xx ftk_XSI_ShapeReference XSI_ShapeReference \endxx template.

	Defines a shape reference (see the \xx ftk_XSI_ShapeReference XSI_ShapeReference \endxx template reference).
	A shape reference is a pointer to an existing shape defined elsewhere in the file. This is used
	in shape key actions (CSLAction) so that the associated shape key (CSLXSIShape) can be identified.

	\sa CSLAction
	\sa CSLMixer
	\sa CSLTimeControl
	\sa CSLTrack
	\sa CSLXSIShape
	\sa CSLXSIShape
	\sa CSLXSIShapeAnimation
*/
class XSIEXPORT CSLXSIShapeReference
    : public CSLTemplate
{
public:

	/*! Constructor
		\param[in] in_pScene	Pointer to the scene containing the ActionClip
		\param[in] in_pModel	Pointer to the model containing the ActionClip
		\param[in] in_pTemplate	Pointer to the CdotXSITemplate defining the ActionClip
	*/
    CSLXSIShapeReference(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);

	/*! Destructor
	*/
    virtual ~CSLXSIShapeReference();

	SI_Error Synchronize();

	/*! Returns the type of this template
		\retval CSLTemplate::XSI_SHAPEREFERENCE Template type
	*/
	CSLTemplate::ETemplateType Type(){ return CSLTemplate::XSI_SHAPEREFERENCE; }

	/*! Returns the referenced shape
		\return Pointer to the referenced shape or NULL if the referenced shape corresponding
			to the current Softimage path was not found in the file.
	*/
	CSLXSIShape* GetReference();

	/*! Sets the referenced shape. Note, the Softimage Path is not set automatically, you also need to use SetReferenceXSIPath.
		\param[in] in_ReferenceShape The the referenced shape
	*/
	SI_Void				SetReference(CSLXSIShape* in_ReferenceShape);

	/*! Returns the Softimage path of the referenced shape
		\return The Softimage Path of the referenced shape
	*/
	SI_Char*			GetReferenceXSIPath();

	/*! Sets the Softimage path of the referenced shape
		\param[in] in_szPath The Softimage Path of the referenced shape
	*/
	SI_Void				SetReferenceXSIPath( SI_Char* in_szPath );

	/*! Returns the referenced shape Softimage path proxy
		\return Pointer to the referenced shape Softimage path proxy
	*/
	CSLStringProxy*		GetReferencePathProxy(){return &m_ReferencePath;};

private:
	CSLStringProxy m_ReferencePath;
	CSLXSIShape* m_pReference;
	SI_Void *m_pReserved;
};

#endif // XSISHAPEREFERENCE
