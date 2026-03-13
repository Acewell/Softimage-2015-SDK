// Camera.cpp: implementation of the Camera class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Camera.h"

#define DEG2RAD			0.01745329251994329547f
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Camera::Camera( Display* in_pDisplay )
{
	m_pDisplay = in_pDisplay;
}

Camera::~Camera()
{

}

void Camera::LookAt ( vector3 in_vFrom, vector3 in_vTo )
{
	m_vFrom = in_vFrom;
	m_vActualFrom = in_vFrom;
	m_vTo = in_vTo;
	m_vActualTo = in_vTo;


}

void Camera::SmoothLookAt ( vector3 in_vFrom, vector3 in_vTo )
{
	m_vFrom = in_vFrom;
	m_vTo = in_vTo;
}

void Camera::GetLookAt ( vector3& out_vFrom, vector3& out_vTo )
{
	out_vFrom = m_vActualFrom;
	out_vTo = m_vActualTo;

}

void Camera::Ensure2VectorsVisible ( vector3 v1, vector3 v2, float minimumY )
{
	DEBUGENTRY ( "Camera::Ensure2VectorsVisible");

	//
	// compute the center of the player and the Softimage eye bounding box
	//

	vector3	bbmin, bbmax;

	bbmin.x = ( v1.x < v2.x ) ? v1.x : v2.x;
	bbmin.y = ( v1.y < v2.y ) ? v1.y : v2.y;
	bbmin.z = ( v1.z < v2.z ) ? v1.z : v2.z;

	bbmax.x = ( v1.x > v2.x ) ? v1.x : v2.x;
	bbmax.y = ( v1.y > v2.y ) ? v1.y : v2.y;
	bbmax.z = ( v1.z > v2.z ) ? v1.z : v2.z;

	vector3 midpoint = ( ( bbmax - bbmin ) / 2.0f ) + bbmin;
	vector3 size = bbmax - bbmin;
	size *= 1.20f;	// make it 20% bigger

	if ( size.x < 15.0f )
		size.x = 15.0f;	// here we make sure that the camera doesn't go to close to the player
						// this would cause to loose sight of the level
	
	vector3 camerapos = m_vFrom;
	vector3 cameraint = m_vActualTo;
	vector3 lineofsight = camerapos - cameraint;

	float	l_fTan = tan((DEG2RAD* m_pDisplay->GetFOV())/2.0f);
	float	l_fLookAtDistance = size.x / 2.0f / l_fTan;		// vertical fov
	l_fLookAtDistance += size.z / 2.0f;

	float l_fLen = lineofsight.Lenght ();

	lineofsight *= l_fLookAtDistance / l_fLen;
	
	camerapos = midpoint + lineofsight;

	m_vFrom  = camerapos;

	if ( m_vFrom.y < minimumY )
	{
		m_vFrom.y += (minimumY - m_vFrom.y) + 1.0f;
	}


	m_vActualTo = midpoint;

}

void Camera::Follow ( Geometry*in_pGeo, CSIBCVector3D& in_vPosition, CSIBCVector3D& in_vForward )
{
	//m_vActualTo = vector3(in_vPosition.m_fX, in_vPosition.m_fY+2.5f, in_vPosition.m_fZ );
	m_vTo = vector3(in_vPosition.m_fX, in_vPosition.m_fY+2.5f, in_vPosition.m_fZ );
	CSIBCVector3D Direction = in_vForward.Normalize();
	CSIBCVector3D Result = in_vPosition;
	Result.Sub ( Direction.Scale(4.0f) );
	
	m_vFrom = vector3(Result.m_fX,Result.m_fY + 2.0f,Result.m_fZ );

}

void Camera::TurnTable	( CSIBCVector3D& in_vPosition )
{
	static float l_fAngle = 0.0f;

	float l_fDistanceFromSubject = 2.0f;

	CSIBCVector3D l_3dPosition;
	l_3dPosition.m_fX = l_fDistanceFromSubject * cosf(l_fAngle * 0.0174533f);
	l_3dPosition.m_fY = in_vPosition.m_fY + 2.0f;
	l_3dPosition.m_fZ = l_fDistanceFromSubject * sinf(l_fAngle* 0.0174533f);

	l_fAngle += 1.0f;

	m_vActualTo = vector3( in_vPosition.m_fX, in_vPosition.m_fY + 2.0f, in_vPosition.m_fZ );

	m_vActualFrom.x = l_3dPosition.m_fX;
	m_vActualFrom.y = l_3dPosition.m_fY;
	m_vActualFrom.z = l_3dPosition.m_fZ;
	m_vActualFrom += vector3 ( in_vPosition.m_fX, in_vPosition.m_fY, in_vPosition.m_fZ );
	m_vActualFrom.y = m_vActualTo.y;
	m_vFrom = m_vActualFrom;


}


void Camera::EnsureAllVectorsVisible ( CSIBCArray<vector3*>& in_aVectors, float minimumY )
{
	DEBUGENTRY ( "Camera::EnsureAllVectorsVisible");

	//
	// compute the center of the player and the Softimage eye bounding box
	//

#define BBSIZE 5

	vector3 bbmidmin, bbmidmax;
	
	bbmidmin.x = ( in_aVectors[0]->x < in_aVectors[0]->x + BBSIZE ) ? in_aVectors[0]->x : in_aVectors[0]->x + BBSIZE ;
	bbmidmin.y = ( in_aVectors[0]->y < in_aVectors[0]->y + BBSIZE ) ? in_aVectors[0]->y : in_aVectors[0]->y + BBSIZE ;
	bbmidmin.z = ( in_aVectors[0]->z < in_aVectors[0]->z + BBSIZE ) ? in_aVectors[0]->z : in_aVectors[0]->z + BBSIZE ;

	bbmidmax.x = ( in_aVectors[0]->x > in_aVectors[0]->x + BBSIZE ) ? in_aVectors[0]->x : in_aVectors[0]->x + BBSIZE ;
	bbmidmax.y = ( in_aVectors[0]->y > in_aVectors[0]->y + BBSIZE ) ? in_aVectors[0]->y : in_aVectors[0]->y + BBSIZE ;
	bbmidmax.z = ( in_aVectors[0]->z > in_aVectors[0]->z + BBSIZE ) ? in_aVectors[0]->z : in_aVectors[0]->z + BBSIZE ;

	vector3	bbmin, bbmax;

	bbmin.x = bbmin.y = bbmin.z = 10000.0f;
	bbmax.x = bbmax.y = bbmax.z = -10000.0f;

	for (int v=0;v<in_aVectors.GetUsed();v++)
	{
		vector3 *vv = in_aVectors[v];
		
		if ( vv->x > bbmax.x )
			bbmax.x = vv->x;

		if ( vv->y > bbmax.y )
			bbmax.y = vv->y;

		if ( vv->z > bbmax.z )
			bbmax.z = vv->z;

		if ( vv->x < bbmin.x )
			bbmin.x = vv->x;

		if ( vv->y < bbmin.y )
			bbmin.y = vv->y;

		if ( vv->z < bbmin.z )
			bbmin.z = vv->z;

	}

	vector3 midpoint = ( ( bbmidmax - bbmidmin ) / 2.0f ) + bbmidmin;
	vector3 size = bbmax - bbmin;
	size *= 1.00f;	// make it 20% bigger

	if ( size.x < 15.0f )
		size.x = 15.0f;	// here we make sure that the camera doesn't go to close to the player
						// this would cause to loose sight of the level

	if ( fabs ( minimumY ) > 0.000001f)
	{
		if ( fabs ( m_vFrom.y - minimumY ) > 1.5f )
		{
			m_vFrom.y += (minimumY - m_vFrom.y) + 1.0f;
		}
	}
	
	vector3 camerapos = m_vFrom;
	vector3 cameraint = m_vActualTo;
	vector3 lineofsight = camerapos - cameraint;

	float	l_fTan = tan((DEG2RAD* m_pDisplay->GetFOV())/2.0f);
	float	l_fLookAtDistance = size.x / 2.0f / l_fTan;		// vertical fov
	l_fLookAtDistance += size.z / 2.0f;

	float l_fLen = lineofsight.Lenght ();

	lineofsight *= l_fLookAtDistance / l_fLen;
	
	camerapos = midpoint + lineofsight;

	m_vFrom  = camerapos;




	m_vActualTo = midpoint;

}

void Camera::Tick ( Geometry* in_pGeo, DWORD milliseconds )
{
	
	if ( milliseconds > 50 )
		milliseconds = 50;

	//
	// smooth interpolate to new cam position
	//
		 
	m_vActualFrom = m_vActualFrom + (m_vFrom - m_vActualFrom) * (milliseconds/600.0f);
	m_vActualTo = m_vActualTo + (m_vTo - m_vActualTo) * (milliseconds/200.0f);

	float l_fMinimumElevation = 0.0f;

	CSIBCVector3D from;
	from.m_fX = m_vActualFrom.x;
	from.m_fY = m_vActualFrom.y;
	from.m_fZ = m_vActualFrom.z;

	bool success = in_pGeo->GetElevationFast (from, l_fMinimumElevation );

	if ( success )
	{
		if ( from.m_fY < l_fMinimumElevation + 2.0f)
		{
			m_vActualFrom.y = l_fMinimumElevation + 2.0f;
			m_vFrom.y = m_vActualFrom.y;  
		}
	} 
}

void Camera::UpdateFrustrumPlanes ()
{
	DEBUGENTRY ( "Camera::UpdateFrustrumPlanes");

	CSIBCMatrix4x4 l_mCameraSpace = m_mCurrentProjectionMatrix * m_mCurrentViewMatrix;
	SI_Float	*l_pRaw = l_mCameraSpace.Raw ();

	CSIBCVector4D*	l_pCurrentPlane;

	l_pCurrentPlane=&m_vFrustrumPlane[RIGHT];
	l_pCurrentPlane->m_fX=l_pRaw[3]-l_pRaw[0];
	l_pCurrentPlane->m_fY=l_pRaw[7]-l_pRaw[4];
	l_pCurrentPlane->m_fZ=l_pRaw[11]-l_pRaw[8];
	l_pCurrentPlane->m_fW=l_pRaw[15]-l_pRaw[12];

	l_pCurrentPlane=&m_vFrustrumPlane[LEFT];
	l_pCurrentPlane->m_fX=l_pRaw[3]+l_pRaw[0];
	l_pCurrentPlane->m_fY=l_pRaw[7]+l_pRaw[4];
	l_pCurrentPlane->m_fZ=l_pRaw[11]+l_pRaw[8];
	l_pCurrentPlane->m_fW=l_pRaw[15]+l_pRaw[12];

	l_pCurrentPlane=&m_vFrustrumPlane[BOTTOM];
	l_pCurrentPlane->m_fX=l_pRaw[3]+l_pRaw[1];
	l_pCurrentPlane->m_fY=l_pRaw[7]+l_pRaw[5];
	l_pCurrentPlane->m_fZ=l_pRaw[11]+l_pRaw[9];
	l_pCurrentPlane->m_fW=l_pRaw[15]+l_pRaw[13];

	l_pCurrentPlane=&m_vFrustrumPlane[TOP];
	l_pCurrentPlane->m_fX=l_pRaw[3]-l_pRaw[1];
	l_pCurrentPlane->m_fY=l_pRaw[7]-l_pRaw[5];
	l_pCurrentPlane->m_fZ=l_pRaw[11]-l_pRaw[9];
	l_pCurrentPlane->m_fW=l_pRaw[15]-l_pRaw[13];

	l_pCurrentPlane=&m_vFrustrumPlane[FFAR];
	l_pCurrentPlane->m_fX=l_pRaw[3]-l_pRaw[2];
	l_pCurrentPlane->m_fY=l_pRaw[7]-l_pRaw[6];
	l_pCurrentPlane->m_fZ=l_pRaw[11]-l_pRaw[10];
	l_pCurrentPlane->m_fW=l_pRaw[15]-l_pRaw[14];

	l_pCurrentPlane=&m_vFrustrumPlane[FNEAR];
	l_pCurrentPlane->m_fX=l_pRaw[3]+l_pRaw[2];
	l_pCurrentPlane->m_fY=l_pRaw[7]+l_pRaw[6];
	l_pCurrentPlane->m_fZ=l_pRaw[11]+l_pRaw[10];
	l_pCurrentPlane->m_fW=l_pRaw[15]+l_pRaw[14];

	//
	// Normalize vectors
	//


	for (SI_Int i=0;i<6;i++)
	{
		CSIBCVector4D*	l_pVec;

		l_pVec=&m_vFrustrumPlane[i];

		SI_Float l_fLength = sqrtf((l_pVec->m_fX * l_pVec->m_fX) + 
							(l_pVec->m_fY * l_pVec->m_fY) +
							(l_pVec->m_fZ * l_pVec->m_fZ));

		l_pVec->m_fX /= l_fLength;
		l_pVec->m_fY /= l_fLength;
		l_pVec->m_fZ /= l_fLength;
		l_pVec->m_fW /= l_fLength;	// ???

	}
}
bool Camera::Cull ( CSIBCVector3D& in_vCenter, CSIBCVector3D& in_vExtent)
{
	DEBUGENTRY ( "Camera::Cull");

	return ( CubeInFrustrum ( in_vCenter, in_vExtent) );
}


bool Camera::Cull ( BoundingBox* in_pBox )
{
	DEBUGENTRY ( "Camera::Cull");

	return ( CubeInFrustrum ( in_pBox->GetCenter(), in_pBox->GetExtent() ) );

}

float Camera::SphereInFrustrum ( CSIBCVector3D& in_pCenter, SI_Float in_fRadius )
{
   SI_Float l_fDistance;

   for( SI_Int i = 0; i<6; i++ )
   {
		CSIBCVector4D*	l_pVec;
		l_pVec=&m_vFrustrumPlane[i];

		l_fDistance = l_pVec->m_fX * in_pCenter.m_fX + 
						l_pVec->m_fY * in_pCenter.m_fY + 
						l_pVec->m_fZ * in_pCenter.m_fZ + l_pVec->m_fW;
		
		SI_Float l_fPreservedSign = (l_fDistance > 0.0f) ? 1.0f : -1.0f;

		l_fDistance = l_fDistance * l_fDistance;
		l_fDistance *= l_fPreservedSign;


		if( l_fDistance <= -in_fRadius )
			return 0;
   }

   return in_fRadius + in_fRadius;

}

bool	 Camera::CubeInFrustrum ( CSIBCVector3D& in_pCenter, CSIBCVector3D& in_fExtent )
{

	for( SI_Int i = 0; i<6; i++ )
	{
		CSIBCVector4D*	l_pVec;
		l_pVec=&m_vFrustrumPlane[i];

		if( l_pVec->m_fX * (in_pCenter.m_fX - in_fExtent.m_fX) + l_pVec->m_fY * (in_pCenter.m_fY - in_fExtent.m_fY) + l_pVec->m_fZ * (in_pCenter.m_fZ - in_fExtent.m_fZ) + l_pVec->m_fW > 0 )
			continue;
		if( l_pVec->m_fX * (in_pCenter.m_fX + in_fExtent.m_fX) + l_pVec->m_fY * (in_pCenter.m_fY - in_fExtent.m_fY) + l_pVec->m_fZ * (in_pCenter.m_fZ - in_fExtent.m_fZ) + l_pVec->m_fW > 0 )
		   continue;
		if( l_pVec->m_fX * (in_pCenter.m_fX - in_fExtent.m_fX) + l_pVec->m_fY * (in_pCenter.m_fY + in_fExtent.m_fY) + l_pVec->m_fZ * (in_pCenter.m_fZ - in_fExtent.m_fZ) + l_pVec->m_fW > 0 )
		   continue;
		if( l_pVec->m_fX * (in_pCenter.m_fX + in_fExtent.m_fX) + l_pVec->m_fY * (in_pCenter.m_fY + in_fExtent.m_fY) + l_pVec->m_fZ * (in_pCenter.m_fZ - in_fExtent.m_fZ) + l_pVec->m_fW > 0 )
		   continue;
		if( l_pVec->m_fX * (in_pCenter.m_fX - in_fExtent.m_fX) + l_pVec->m_fY * (in_pCenter.m_fY - in_fExtent.m_fY) + l_pVec->m_fZ * (in_pCenter.m_fZ + in_fExtent.m_fZ) + l_pVec->m_fW > 0 )
		   continue;
		if( l_pVec->m_fX * (in_pCenter.m_fX + in_fExtent.m_fX) + l_pVec->m_fY * (in_pCenter.m_fY - in_fExtent.m_fY) + l_pVec->m_fZ * (in_pCenter.m_fZ + in_fExtent.m_fZ) + l_pVec->m_fW > 0 )
		   continue;
		if( l_pVec->m_fX * (in_pCenter.m_fX - in_fExtent.m_fX) + l_pVec->m_fY * (in_pCenter.m_fY + in_fExtent.m_fY) + l_pVec->m_fZ * (in_pCenter.m_fZ + in_fExtent.m_fZ) + l_pVec->m_fW > 0 )
		   continue;
		if( l_pVec->m_fX * (in_pCenter.m_fX + in_fExtent.m_fX) + l_pVec->m_fY * (in_pCenter.m_fY + in_fExtent.m_fY) + l_pVec->m_fZ * (in_pCenter.m_fZ + in_fExtent.m_fZ) + l_pVec->m_fW > 0 )
		   continue;
		return false;
   }

   return true;
}

CSIBCVector3D Camera::GetFrom ( )
{
	return CSIBCVector3D( m_vActualFrom.x, m_vActualFrom.y, m_vActualFrom.z );
}
