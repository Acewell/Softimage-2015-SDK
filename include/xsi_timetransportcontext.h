//*****************************************************************************
/*!
   \file xsi_timetransportcontext.h
   \brief TimeTransportContext class declaration.

   © Copyright 1998-2008 Avid Technology, Inc. and its licensors. All rights
   reserved. This file contains confidential and proprietary information of
   Avid Technology, Inc., and is subject to the terms of the SOFTIMAGE|XSI
   end user license agreement (or EULA).
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSITIMETRANSPORTCONTEXT_H__
#define __XSITIMETRANSPORTCONTEXT_H__

#include <xsi_decl.h>
#include <xsi_status.h>
#include <xsi_ref.h>
#include <xsi_time.h>
#include <xsi_fcurve.h>
#include <xsi_context.h>
#include <xsi_base.h>

namespace XSI {

//*****************************************************************************
/*! \class TimeTransportContext xsi_timetransportcontext.h

	\brief The TimeTransportContext object defines the time span (start and end time)
	current time, frame rate, jog step size used by the CTimeTransport object. 

	The TimeTransportContext is in an undefined state when created an must be
	initialized using the TimeTransportContext::Set method before it can be
	used with the CTimeTransport.

	The TimeTransportContext can define the playback of non-linear scene time.
	A sequence of scene playback clips can be defined using the 
	TimeTransportContext::AddGlobalTimeClip method.

	NOTE: This context is used to define the time span used by
	the time transport and may refer to times out side the global scene time 
	span the effect of this behavior is undefined. To ensure this does not 
	happen global time clips must be added to complete define the time
	transports time span.

	\sa TimeTransport, ::siOnTimeTransportChangeEvent 
	\since 6.5.x

 */
//*****************************************************************************

class SICPPSDKDECL TimeTransportContext : public CBase 
{
public:
	//! The time display to be used by time clients.
	enum TimeDisplay
	{
		SMPTE,		/*!< SMPTE, which stands for the Society of Motion Picture
					     and Television Engineers, is a method of displaying time. There are two ways that SMPTE can be displayed,
						  non-drop or drop frame:

						\par SMPTE non-drop
							Represented by the display; hours, minutes, seconds and frame number, or \c 0:00:00:00.

						\par SMPTE drop frame
							Represented by the display; hours, minutes, seconds and frame number, or \c 0:00:00;00. */
		Frames,		/*!< Frame format */
	};

	/*! Default constructor. */
	TimeTransportContext();

	/*! Default destructor. */
	~TimeTransportContext();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	TimeTransportContext(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	TimeTransportContext(const TimeTransportContext& in_obj);

	/*! Returns true if a given class type is compatible with this API class.
	\param in_eClassID class type.
	\return true if the class is compatible, false otherwise.
	*/
	bool IsA( siClassID in_eClassID) const;

	/*! Returns the type of the API class.
	\return The class type.
	*/
	siClassID GetClassID() const;

	/*! assignment from constant object operator
	*/
	TimeTransportContext& operator=(const TimeTransportContext& in_obj);
 
	/*! assignment from constant CRef operator
	*/
	TimeTransportContext& operator=(const CRef& in_ref);

	/*! Set the most common time context in one shot.

	\param in_eFormat			Time format specifying the frame rate such as PAL, FILM, NTSE or Custom.
	\param in_dFrameRate			Time frame rate. If you are using non-custom format then the rate is predefined and this value is ignored. 
	\param in_tmStart			Start time for time transport. If this is in a different format from the in_format argument it will be converted.
	\param in_tmEnd				End time for time transport. If this is in a different format from the in_format argument it will be converted.
	\param in_tmCurrent			Current time for time transport; this is usually the same as the start time.
	\param in_lStepSize			The frame step size to be used when playing, jogging forward or backwards; this is usually set to 1 frame.

	\return CStatus::OK 
	\return CStatus::Fail		This may fail if this TimeTransportContext was not first retrieve by using the CTimeTransport::GetContext method.
	*/
	CStatus Set	( CTime::Format in_eFormat, double in_dFrameRate, const CTime& in_tmStart, const CTime& in_tmEnd, const CTime& in_tmCurrent, LONG in_lStepSize ) const;

	/*! Return the time format used the time transport.
	\return CTime::Format 
	*/
	CTime::Format GetTimeFormat() const;

	/*! Return the time format rate used the time transport. This is only applicable for the custom format rate otherwise the standard frame rates are returned.
	\return double  
	*/
	double GetTimeFormatRate() const;

	/*! Add a new global time clip at the next available time transport offset. If this clip exceeds the bounds of the time span defined for this time transport
		it will be clipped to the boundary time, if the boundary time has already been reached the method will fail. The first transport offset (transport clip in)
		will be assumed to be the transport start time.
	
		The global in and clip out times refer to the where in global scene time we are using as a source. For example, The global scene in and out times  
		for a scene may be defined as starting at frame0 to frame100, of that entire scene time we are only interested in defining a clip from frame5 to frame15.
		Furthermore we are only interest in playing 20 frames at a frame rate of 30 fps.

		The global out time is inclusive with the next global time clip. For example, if you have two ten-frame clips abutting each other in global time,
		their in/outs look like 1-11,11-21 (inclusive) instead of 1-10,11-20 (exclusive).

		The scale determines the playback speed and duration of the clip for example we may be refering to frame5 to frame15 of global 
		scene time which we want to play back at 2x, this would be on time transport we would only be playback for 5 frames since we are going twice as fast.

		The clip time warp is an fcurve from a CustomProperty parameter representing the timewarp to be used on the clip in addition to the clip scale. The
		time warp is used to vary the speed at which the clip is playback, for example using the example above the first 2 frames may be playback back
		with a linear mapping but held constant for frame 3 and then go back to linear mapping for frames 4 and 5. When applying the time warp the clip will 
		be sampling rate will be determined by the global clip frame rate and the clip scaling. So for the above example where 10 frames of global time time
		are playback twice as fast 5 samples will be used. The fcurve may have any range on the X and Y axis; when mapping from transport time to global
		time the fcurve is normalized. The X axis represents transport clip time and the Y axis represents the global time.

		Global Time from Transport Time Mapping:

		1) scale only:    global time = global clip start + ( transport clip offset * scale )
		2) time warp:	  global time = global clip start + fcurve( transport clip offset * scale )

		If the transport clip offset or the mapped global time is out of range then the result will be clamped to the global clip in and global clip out times.

		Returned to you is the next transport time offset (transport clip out) available for this time transport; the time format will be in the transport time.
		Using the example above the new time offset for this time transport would be frame6 at a frame rate of 30 fps.

	\param in_tmGlobalIn			clip start time in global scene time.
	\param in_tmGlobalOut			clip end time in global scene time; this must start after the clip in time.
	\param in_dScale				clip's scale; determines playback speed and duration of clip. Must allow at least 1 frame to be transported.
	\param in_fcTimeWarp			clip's time warp profile curve 
	\param io_tmNextOffset			return the next time transport offset to be used by the next global time clip in the format specified for the time transport.

	\return CStatus::OK 
	\return CStatus::Fail			
	*/
	CStatus AddGlobalTimeClip( const CTime& in_tmGlobalIn, const CTime& in_tmGlobalOut, double in_dScale, const FCurve& in_fcClipTimeWarp, CTime& io_tmNextOffset ) const;

	/*! clear the global time clips. Time transport will now playback linear time as defined by the time transport start time, end time and frame rate.
	*/
	CStatus ClearGlobalTimeClips() const;

	/*! Return number of clips current held by context.
	\return LONG					return number of clips.
	*/
	LONG GetNumGlobalTimeClips() const;

	/*! Get global time clip at specific index.

	\param in_lIdx				index of clip	(0 <= idx < GetNumGlobalTimeClips().
	\param io_tmClipIn			clip start time in transport time.
	\param io_tmClipOut			clip stop time in transport time
	\param io_tmGlobalIn		global start time
	\param io_tmGlobalOut		global stop time
	\param io_dScale			scale as a value >0 but must allow at least 1 frame to be transported.
	\param io_fcTimeWarp		time warp profile curve; this is optional so may be invalid.
	\param io_tmNextOffset		return the next time transport offset to be used by the next global time clip in the format specified for the time transport.

	\return CStatus::OK 
	\return CStatus::Fail			
	*/
	CStatus GetGlobalTimeClip(LONG in_idx, CTime& io_rClipIn, CTime& io_rClipOut, CTime& io_rGlobalIn, CTime& io_rGlobalOut, double& in_dScale, FCurve& io_rfcTimeWarp);

private:

	TimeTransportContext * operator&() const;
	TimeTransportContext * operator&();

	void*	m_pImpl;
};

}

#endif // __XSITIMETRANSPORTCONTEXT_H__
