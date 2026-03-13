//*****************************************************************************
/*!
   \file xsi_timetransport.h
   \brief TimeTransport class declaration.

   © Copyright 1998-2008 Avid Technology, Inc. and its licensors. All rights
   reserved. This file contains confidential and proprietary information of
   Avid Technology, Inc., and is subject to the terms of the SOFTIMAGE|XSI
   end user license agreement (or EULA).
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIXSITIMETRANSPORT_H__
#define __XSIXSITIMETRANSPORT_H__

#include <xsi_decl.h>
#include <xsi_base.h>
#include <xsi_status.h>
#include <xsi_ref.h>
#include <xsi_timetransportcontext.h>

namespace XSI {

//*****************************************************************************
/*! \class TimeTransport xsi_timetransport.h
	\brief The TimeTransport object offers services to control XSI time transport
	service. This time service is responsible for control the deliver of time
	changes to time clients.

	Time clients include: 3D viewport, fcurve editor, animation editor, timeline 
	control panel, playback control panel, fx compositor, time change SDK events.

	You cannot instantiate a TimeTransport object directly. Rather, you receive 
	an instance through the XSIFactory.CreateTimeTransport() method or 
	when your TimeTransport event plug-ins are called.

	If you try an create the TimeTransport class any other way the methods will fail.

	\sa TimeTransportContext, ::siOnTimeTransportChangeEvent 
	\since 6.5.x

 */
//*****************************************************************************

class SICPPSDKDECL TimeTransport : public CBase
{ 
public:
	/*! Default constructor. */
	TimeTransport();

	/*! Default destructor. */
	~TimeTransport();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	TimeTransport(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	TimeTransport(const TimeTransport& in_obj);

	bool IsA( siClassID in_ClassID) const;
 
	siClassID GetClassID() const;

	TimeTransport& operator=(const TimeTransport& in_obj);
 
	TimeTransport& operator=(const CRef& in_ref);

	/*! Return name assigned to this time transport. This can use to indentified
	\return CString
	*/
	CString GetName	( ) const;

	/*! Set the time transport context used by the time transport. If you want to change
	    the current context get it first from the TimeTransport::GetContext method first.
		This method can be call during playback state and will result in playback state 
		using the new time transport context settings.

	\param in_ttContext				new time transport context. The time transport context defines the 
		start, end and current times, the frame rate, the jog step size.

	\return CStatus::OK 
	\return CStatus::Fail			
	*/
	CStatus PutContext	( const TimeTransportContext& in_ttContext ) const;

	/*! Returns a copy of the time transport context being used by this transport. The time transport context defines the 
		start, end and current times, the frame rate, the frame step size. Changes to the context only take effect on the
		transport once you set it back using the PutContext() method.

	\return TimeTransportContext	return the time transport context used by this time transport.
	*/
	XSI::TimeTransportContext GetContext	() const;

	/*! Returns the current time of the transport whether it is active or not.
		The time returned is in the transport's time format.

	\return CTime	return the current time transport time
	*/	CTime GetTime	() const;

	/*! Start delivering time to time clients as defined by the TimeTransportContext.

	\param in_ePlaybackMode			The playback mode. Normally the playback type is set to siTTPlaybackSlideShow
									this means that the playback will be sequential and no frames will be dropped.
									This also means that the desired frame rate may or may not be achieved.
									Playback in siTTPlaybackNormal will playback to achieve the desired frame
									rate and frames may be dropped to keep up.
	\return CStatus::OK 
	\return CStatus::Fail 
	*/
	CStatus Play	( XSI::siTimeTransportPlaybackMode in_ePlaybackMode = XSI::siTTPlaybackSlideShow ) const;

	/*! Stop delivering time to time clients. This is an unsynchronized stop so there may be a lag in hardware devices, 
		such as sound, complying to this request.

	\return CStatus::OK 
	\return CStatus::Fail 
	*/
	CStatus Stop	() const;

	/*! Move the time forward to the next frame defined by jog time

	\param in_tmJogTime				Jog time step defined in seconds or in frames using the same frame rate as used the CTimeContext.

	\return CStatus::OK 
	\return CStatus::Fail 
	*/
	CStatus JogForward ( const CTime& in_tmJogTime ) const;

	/*! Move the time backwards to the previous frame defined by jog time

	\param in_tmJogTime					The jog time step in seconds or the same frame rate as defined by the TimeTransportContext.

	\return CStatus::OK 
	\return CStatus::Fail 
	*/
	CStatus JogRewind ( const CTime& in_tmJogTime ) const;

	/*! Move the time transport to a specific time. If the time requested is out of bounds seek to boundary time which will 
	    be the start and end time. This method can be used in the context of a user interface implementing scrubbing as
		long as the seek mode is specified as siTTScrubActive. siTTScrubJob is not a valid seek mode but rather a state
		the time transport may transition to if a JogForward or JogBackward results in frames being dropped.

	\param in_tmTarget					 The target seek time in seconds or the same frame rate as defined by the TimeTransportContext.
	\param in_eSeekMode					 The seek mode to implement. This value may be siTTScrubActive or siTTScrubInactive.
										 Only use siTTScrubActive if you are implementing scrubbing. To seek to a specific frame
										 use the default siTTScrubInactive.	

	\return CStatus::OK 
	\return CStatus::Fail 
	*/
	CStatus Seek	( const CTime& in_tmTarget, XSI::siTimeTransportSeekMode in_eSeekMode = XSI::siTTScrubInactive ) const;

private:

	TimeTransport * operator&() const;
	TimeTransport * operator&();

	void*	m_pImpl;
};

}

#endif // __XSIXSITIMETRANSPORT_H__
