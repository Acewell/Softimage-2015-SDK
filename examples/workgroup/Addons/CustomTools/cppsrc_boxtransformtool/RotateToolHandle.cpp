///////////////////////////////////////////////////////////////////////////
//
// File: RotateToolHandle.cpp
//
// Description: Base class for rotate handles
//
// Copyright 2010 Autodesk, Inc. All rights reserved.
// Use of this software is subject to the terms of the Autodesk license
// agreement provided at the time of installation or download, or which
// otherwise accompanies this software in either electronic or hard copy
// form.
//
///////////////////////////////////////////////////////////////////////////
#include "RotateToolHandle.h"
#include <xsi_preferences.h>

// Arcball helper functions (courtesy of Ken Shoemake/Graphic Gems IV)
static CVector3 MouseOnSphere( const CVector3 &in_point, const CVector3 &in_center, double in_radius )
{
	CVector3 result;
	result.Sub(in_point, in_center).ScaleInPlace(1.0 / in_radius);
    double norm = result.GetLengthSquared();
    if ( norm > 1.0 )
		result *= 1.0 / sqrt(norm);
    else
		result.PutZ( sqrt(1.0 - norm) );
	return result;
}

static CRotation RotFromBallPoints( const CVector3 &in_from, const CVector3 &in_to )
{
	return CRotation( CQuaternion(
		in_from.GetX()*in_to.GetX() + in_from.GetY()*in_to.GetY() + in_from.GetZ()*in_to.GetZ(),
		in_from.GetY()*in_to.GetZ() - in_from.GetZ()*in_to.GetY(),
		in_from.GetZ()*in_to.GetX() - in_from.GetX()*in_to.GetZ(),
		in_from.GetX()*in_to.GetY() - in_from.GetY()*in_to.GetX() )
	);
}

static CVector3 ConstrainToAxis( const CVector3 &in_point, const CVector3 &in_axis )
{
	CVector3 result, axis, onPlane;
	axis.Scale( in_axis.Dot(in_point), in_axis );
	onPlane.Sub( in_point, axis );

	double norm = onPlane.GetLengthSquared();
	if ( norm > 0.0 ) {
		result.Scale( 1.0/sqrt(norm), onPlane );
	} else if ( in_axis.GetZ() == 1.0 ) {
		result.Set( 1.0, 0.0, 0.0 );
	} else {
		result.Set( -in_axis.GetY(), in_axis.GetX(), 0.0 ).NormalizeInPlace();
	}
	return result;
}

RotateToolHandle::RotateToolHandle()
:	m_dBallRadius( 0.0 )
{}

RotateToolHandle::~RotateToolHandle()
{}

CStatus RotateToolHandle::InitializeArcball( ToolContext &in_ctxt, LONG x, LONG y, const CVector3 &center, double in_dRadius )
{
	// Compute screen-space arcball from world coordinates
	m_ballDownX = x;
	m_ballDownY = y;
	m_dBallRadius = 0;
	if ( in_ctxt.WorldToView( center, m_ballCenter ) != CStatus::OK ) 
		return CStatus::Fail;	

	// Calculate silhouette point on sphere to get screen-space radius
	CVector3 ballExtent( m_ballCenter.GetX(), m_ballCenter.GetY() + 1.0/*pixels*/, m_ballCenter.GetZ() );
	if ( in_ctxt.ViewToWorld( ballExtent, ballExtent ) != CStatus::OK )
		return CStatus::Fail;

	// Scale point and then project back to screen-space
	ballExtent.SubInPlace( center ).NormalizeInPlace();
	ballExtent.ScaleInPlace( in_dRadius ).AddInPlace( center );
	if ( in_ctxt.WorldToView( ballExtent, ballExtent ) != CStatus::OK ) 
		return CStatus::Fail;

	// Calculate screen-space radius
	m_ballCenter.PutZ( 0.0 ); // Remove depth
	ballExtent.PutZ( 0.0 ).SubInPlace( m_ballCenter ); // Remove depth
	m_dBallRadius = ballExtent.GetLength() + kPickSize; // Add a few pixels to account for picking
	return CStatus::OK;
}

LONG RotateToolHandle::GetClosestArcballAxis( ToolContext &in_ctxt, LONG x, LONG y, LONG numConstraints, const CVector3 *constraintAxes )
{
	if ( numConstraints < 1 || m_dBallRadius == 0.0 )
		return -1; // Error

	// Note: arcball is very efficient so we compute the rotation for each axis and take the largest...
	LONG nearest = 0;
	double maxAngle = 0.0;
	CVector3 origin( 0.0, 0.0, 0.0 );
	in_ctxt.WorldToCamera( origin, origin );
	CVector3 from = MouseOnSphere( CVector3(m_ballDownX, m_ballDownY, 0.0), m_ballCenter, m_dBallRadius );
	CVector3 to = MouseOnSphere( CVector3(x, y, 0.0), m_ballCenter, m_dBallRadius );
	for ( int i = 0; i < numConstraints; ++i )
	{
		CVector3 axis;
		double dAngle = 0.0;
		in_ctxt.WorldToCamera( constraintAxes[i], axis );
		axis.SubInPlace( origin ).NormalizeInPlace();
		CRotation rot = RotFromBallPoints( ConstrainToAxis(from, axis), ConstrainToAxis(to, axis) );
		rot.GetAxisAngle( dAngle );
		dAngle = fabs( dAngle );
		if ( dAngle > maxAngle ) {
			maxAngle = dAngle;
			nearest = i;
		}
	}
	return nearest;
}

CRotation RotateToolHandle::GetArcballRotation( ToolContext &in_ctxt, LONG x, LONG y, const CVector3 *constraintAxis )
{
	CRotation result;
	if ( m_dBallRadius == 0.0 )
		return result;

	// Get intitial and current points
	CVector3 from = MouseOnSphere( CVector3(m_ballDownX, m_ballDownY, 0.0), m_ballCenter, m_dBallRadius );
	CVector3 to = MouseOnSphere( CVector3(x, y, 0.0), m_ballCenter, m_dBallRadius );

	// Handle axis contraint
	if ( constraintAxis != NULL )
	{
		// Constraint must be converted to camera-space
		CVector3 origin( 0.0, 0.0, 0.0 ), axis;
		in_ctxt.WorldToCamera( origin, origin );
		in_ctxt.WorldToCamera( *constraintAxis, axis );
		axis.SubInPlace( origin ).NormalizeInPlace();
		from = ConstrainToAxis( from, axis );
		to = ConstrainToAxis( to, axis );
	}

	// Get rotation and convert to world-space
	double dAngle = 0.0;
	CRotation rot = RotFromBallPoints( from, to );
	CVector3 axis = rot.GetAxisAngle( dAngle );
	// Choose an arbitrary axis if it is undefined (dAngle == 0)
	if (axis.GetX() == 0.0 && axis.GetY() == 0.0 && axis.GetZ() == 0.0 )
		axis.PutX( 1.0 );
	
	dAngle *= 0.5; // Half rotation value to map 1:1 with mouse movement
	CVector3 origin( 0.0, 0.0, 0.0 );
	in_ctxt.CameraToWorld( origin, origin );
	in_ctxt.CameraToWorld( axis, axis );
	axis.SubInPlace( origin ).NormalizeInPlace();
	rot.SetFromAxisAngle( axis, dAngle );
	return rot;
}

CRotation RotateToolHandle::GetNearestRotationIncrement( const CRotation &in_rot )
{
	CRotation result( in_rot );
	CValue rotSnap( 0.0 );
	Application().GetPreferences().GetPreferenceValue( L"TransformProperties.rotatesnap", rotSnap );

	double dAngle = 0.0;
	CVector3 axis = result.GetAxisAngle( dAngle );
	// Choose an arbitrary axis if it is undefined (dAngle == 0)
	if (axis.GetX() == 0.0 && axis.GetY() == 0.0 && axis.GetZ() == 0.0 )
		axis.PutX( 1.0 );

	dAngle = DegreesToRadians( GetClosestIncrement(RadiansToDegrees(dAngle), rotSnap) );
	result.SetFromAxisAngle( axis, dAngle );
	return result;
}
