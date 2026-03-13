//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file ImageClip.h
	\brief Defines the CSLImageClip class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _IMAGECLIP_H
#define _IMAGECLIP_H

#include "Template.h"

// Forward declaration
class CSLTexture2D;

/*! \brief This class represents an \xx ftk_SI_ImageClip SI_ImageClip \endxx template.

Class not implemented (see the \xx ftk_SI_ImageClip SI_ImageClip \endxx
template reference)
*/
class CSLImageClip
    : public CSLTemplate
{

//@START_USER2
//@END_USER2

// Members
private:
    CSLTexture2D* m_pReference;
    CSLFloatProxy* m_pStartTime;
    CSLFloatProxy* m_pEndTime;
    CSLFloatProxy* m_pRate;
    CSLIntProxy* m_pRepeatType;
    CSIBCArray<CSLStringProxy *> m_pImages;

protected:

public:

// Methods
private:

protected:

public:
    CSLImageClip(CSLScene* in_pScene, CSLModel *in_pModel, CdotXSITemplate* in_pTemplate);
    virtual ~CSLImageClip();
    CSLStringProxy* AddImage();
    CSLFloatProxy* EndTime() const;
    CSLStringProxy** Images() const;
    SI_Int* NbImages() const;
    CSLFloatProxy* Rate() const;
    CSLTexture2D* Reference() const;
    SI_Error RemoveImage();
    CSLIntProxy* RepeatType() const;
    CSLFloatProxy* StartTime() const;
};

#endif


#ifdef CB_INLINES
#ifndef _IMAGECLIP_H_INLINES
#define _IMAGECLIP_H_INLINES

//@START_USER3
//@END_USER3

#endif
#endif
