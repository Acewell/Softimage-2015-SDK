//*****************************************************************************
/*!
	\file xsi_memocamera.h
	\brief MemoCamera class declaration.
   
	Copyright 2011 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIMEMOCAMERA_H__
#define __XSIMEMOCAMERA_H__

#include <xsi_uiobject.h>

namespace XSI {

//*****************************************************************************
/*! 
	\class MemoCamera xsi_memocamera.h
	\brief The MemoCamera class represents a memo camera control in a view.
	\sa MemoCamera
    \since 10.5 (2012)

	\eg Demonstrates how to record the 4 memo cameras in the perspective view.    
	\code
	
		using namespace XSI;

		Application app;

		// Get the View Manager
		View vm = app.GetDesktop().GetActiveLayout().GetViews().GetItem( "vm" );

		// Get view B (perspective)
		View viewB = vm.GetViews()[ 1 ];

		// Get memocams for view B
		CRefArray memoCameras = viewB.GetMemoCameras();
		app.LogMessage( "Memo camera count for view B: " +  CString( memoCameras.GetCount() ) );

		// Get View B's camera object
		Camera camB = app.GetActiveSceneRoot().FindObjects( XSI::siCameraID )[ 0 ];

		// Get the camera global KinematicState
		KinematicState kinestate = camB.GetKinematics().GetGlobal();

		// Record 4 memo cameras in view B
		for ( int index = 0; index < 4; index++ )
		{
			switch( index )
			{
				case 0:
					kinestate.PutParameterValue( "posx", -10.0 );
					kinestate.PutParameterValue( "posy", 2.0 );
					kinestate.PutParameterValue( "posz", 20.0 );
					break;
				case 1:
					kinestate.PutParameterValue( "posx", 0.0 );
					break;
				case 2:
					kinestate.PutParameterValue( "posx", 10.0 );
					break;
				case 3:
					kinestate.PutParameterValue( "posx", 0.0 );
					kinestate.PutParameterValue( "posy", -2.0 );
					break;
			}

			MemoCamera memoCamera = memoCameras[ index] ;
			memoCamera.Record();
		}

		\endcode
 */
//*****************************************************************************

class SICPPSDKDECL MemoCamera : public UIObject
{
	public:
	
	/*! Default constructor. */
	MemoCamera();
    
	/*! Default destructor. */
	~MemoCamera();
    
	/*! Constructor.
	\param in_ref constant reference object.
	*/
	MemoCamera(const CRef& in_ref);
    
	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	MemoCamera(const MemoCamera& in_obj);
    
	/*! Returns true if a given class type is compatible with this API class.
	\param in_ClassID class type.
	\return true if the class is compatible, false otherwise.
	*/
	bool IsA( siClassID in_ClassID ) const;
    
	/*! Returns the type of the API class.
	\return The class type.
	*/
	siClassID GetClassID() const;
    
	/*! Creates an object from another object. The newly created object is set to
	empty if the input object is not compatible.
	\param in_obj constant class object.
	\return The new MemoCamera object.
	*/
	MemoCamera& operator=(const MemoCamera& in_obj);
    
	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new MemoCamera object.
	*/
	MemoCamera& operator=(const CRef& in_ref);

	/*! Records a memo camera.
	\return CStatus::OK Success.
	*/
	CStatus Record( ) const;

	/*! Recalls a memo camera.
	\return CStatus::OK Success.
	*/
	CStatus Recall( ) const;

	/*! Resets a memo camera.
	\return CStatus::OK Success.
	*/
	CStatus Reset( ) const;

	private:
	MemoCamera * operator&() const;
	MemoCamera * operator&();
};

};

#endif

