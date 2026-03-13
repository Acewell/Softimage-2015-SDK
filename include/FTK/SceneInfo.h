//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file SceneInfo.h
	\brief Defines the CSLSceneInfo class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

#ifndef _SCENEINFO_H
#define _SCENEINFO_H

#include "Template.h"

/*! \brief This class represents the \xx ftk_SI_SceneInfo SI_SceneInfo \endxx template.

	Base class to handle timing information for the scene (see the
	\xx ftk_SI_SceneInfo SI_SceneInfo \endxx template reference).
*/
class XSIEXPORT CSLSceneInfo
	: public CSLTemplate
{
// Methods
public:

	/*! Enumeration specifying the timing type
	*/
	typedef enum ETimingType
	{
		SI_SECONDS,	//*< Timing is in seconds */
		SI_FRAMES	//*< Timing is in frames */
	};

	/*! Constructor

		\param[in] in_pScene Pointer to the scene
		\param[in] in_pModel Pointer to the model
		\param[in] in_pTemplate Pointer to the parent template
		\param[in] in_DefaultETimingType Timing type to use if an invalid type is loaded
	*/
    CSLSceneInfo
	(
		CSLScene* in_pScene,
		CSLModel* in_pModel,
		CdotXSITemplate *in_pTemplate,
		ETimingType in_DefaultETimingType = SI_FRAMES
	);

	/*! Destructor
	*/
    virtual ~CSLSceneInfo();

	/*! Sets end time of the scene (Time type specified by ETimingType)
		\param[in] in_nEnd New end frame to use
	*/
	void SetEnd( SI_Float in_nEnd );

	/*! Returns end time of the scene (Time type specified by ETimingType)
		\return End frame
	*/
	SI_Float GetEnd();

	/*! Sets frames per second
		\param[in] in_fFrameRate New frame rate to use
	*/
    void SetFrameRate( SI_Float in_fFrameRate );

	/*! Returns frames per second
		\return Current frame rate
	*/
	SI_Float GetFrameRate();

	/*! Sets Start time of the scene (Time type specified by ETimingType)
		\param[in] in_nStart New start frame to use
	*/
	void SetStart( SI_Float in_nStart );

	/*! Returns Start time of the scene (Time type specified by ETimingType)
		\return The current start frame
	*/
	SI_Float GetStart();

	/*! Sets the timing type
		\param[in] in_Type New timing type to use
	*/
    void SetTimingType( ETimingType in_Type ) ;


	/*! Returns the timing type
		\return Current timing type
	*/
    ETimingType GetTimingType();

    /*! Returns the template type
    	\retval CSLTemplate::SI_SCENE_INFO Type of template
    */
    virtual CSLTemplate::ETemplateType Type();
    virtual CSLAnimatableType* ParameterFromName(SI_Char *in_szName);

	CSLFloatProxy*								GetStartProxy() { return &m_nStart;};
	CSLFloatProxy*								GetEndProxy() { return &m_nEnd;};
	CSLFloatProxy*								GetFrameRateProxy() { return &m_fFrameRate;};
	CSLStrEnumProxy<ETimingType, SI_FRAMES>*	GetTimingTypeProxy() { return &m_TimingType;};

// Members
private:
    CSLStrEnumProxy<ETimingType, SI_FRAMES> m_TimingType;
    CSLFloatProxy m_nStart;
    CSLFloatProxy m_nEnd;
    CSLFloatProxy m_fFrameRate;

	// This member is here to allow future improvement of the class.
	SI_Void *m_pReserved;
};

#endif

