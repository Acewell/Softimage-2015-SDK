// Camera.h: interface for the Camera class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAMERA_H__30F73D90_BD9F_480E_AFE6_9D3F945255B4__INCLUDED_)
#define AFX_CAMERA_H__30F73D90_BD9F_480E_AFE6_9D3F945255B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "vector.h"
#include "Display.h"
#include "BoundingBox.h"
#include "Geometry.h"

#include <SemanticLayer.h>

#include <SIBCVector.h>
#include <SIBCMatrix.h>
#include <SIBCArray.h>


#define RIGHT	0
#define LEFT	1
#define BOTTOM	2
#define TOP		3
#define	FFAR	4
#define FNEAR	5

class Camera  
{
public:
	Camera( Display* in_pDisplay );
	virtual ~Camera();
	virtual	void LookAt ( vector3 in_vFrom, vector3 in_vTo );
	virtual	void SmoothLookAt ( vector3 in_vFrom, vector3 in_vTo );
	virtual	void GetLookAt ( vector3& out_vFrom, vector3& out_vTo );
	virtual void Ensure2VectorsVisible ( vector3 v1, vector3 v2, float minimumY );
	virtual void EnsureAllVectorsVisible ( CSIBCArray<vector3*>& in_aVectors, float minimumY );
	
	virtual void Follow		( Geometry*in_pGeo, CSIBCVector3D& in_vPosition, CSIBCVector3D& in_vForward );
	virtual void TurnTable	( CSIBCVector3D& in_vPosition );
	
	
	virtual void Tick ( Geometry*in_pGeo, DWORD milliseconds );
	virtual void UpdateFrustrumPlanes ();
	virtual bool Cull ( BoundingBox* );
	virtual bool Cull ( CSIBCVector3D& in_vCenter, CSIBCVector3D& in_vExtent);
	virtual float SphereInFrustrum ( CSIBCVector3D& in_pCenter, SI_Float in_fRadius );
	virtual bool CubeInFrustrum ( CSIBCVector3D& in_pCenter, CSIBCVector3D& in_fExtent );
	
	virtual CSIBCVector3D GetFrom ( );

	CSIBCVector4D		m_vFrustrumPlane[6];
	CSIBCMatrix4x4		m_mCurrentViewMatrix;
	CSIBCMatrix4x4		m_mCurrentProjectionMatrix;

private:

	Display* m_pDisplay;

	vector3  m_vActualFrom;
	vector3  m_vActualTo;

	vector3	 m_vFrom;
	vector3	 m_vTo;

};

#endif // !defined(AFX_CAMERA_H__30F73D90_BD9F_480E_AFE6_9D3F945255B4__INCLUDED_)
