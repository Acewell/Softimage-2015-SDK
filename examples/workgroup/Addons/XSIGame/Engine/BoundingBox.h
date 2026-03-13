// BoundingBox.h: interface for the BoundingBox class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOUNDINGBOX_H__2CE81342_9C6A_4C5D_BA54_08A48566E16B__INCLUDED_)
#define AFX_BOUNDINGBOX_H__2CE81342_9C6A_4C5D_BA54_08A48566E16B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "engine.h"
#include <SemanticLayer.h>

class BoundingBox  
{
public:
	BoundingBox();
	virtual ~BoundingBox();

	void	SetTransform ( CSLTransform* in_pXfo ) { m_pTransform = in_pXfo; };

	void	Grow ( CSIBCVector3D );
	void	Transform();
	void	GetXFormAABB ( CSIBCVector3D& m_vMax, CSIBCVector3D& m_vMin );

	bool	TestCollision ( BoundingBox* in_pBox, CSIBCVector3D& out_vCollision );
	bool	TestMeshCollision ( BoundingBox* in_pBox );
	bool	TestTightCollision ( BoundingBox* in_pBox );

	void	SetOffset		( CSIBCMatrix4x4& in_mOffset ) { m_mOffset = in_mOffset; };

	CSIBCVector3D	GetCenter () { return m_vCenter; };
	CSIBCVector3D	GetExtent () { return m_vExtent; };

	void			Reset ();


	CSIBCVector3D	m_vPoints[8];
	CSIBCVector3D	bc[8];
	bool			m_bTransformed;
	
	
	CSLMesh*		m_pMesh;
	CSIBCVector3D*	m_pMeshVertices;

private:

	CSLTransform*	m_pTransform;

	bool			m_bInitialized;
	
	CSIBCVector3D	m_vMaxX;
	CSIBCVector3D	m_vMinX;
	CSIBCVector3D	m_vMax;
	CSIBCVector3D	m_vMin;
	CSIBCVector3D	m_vCenter;
	CSIBCVector3D	m_vExtent;
	CSIBCMatrix4x4	m_mOffset;


	

};

#endif // !defined(AFX_BOUNDINGBOX_H__2CE81342_9C6A_4C5D_BA54_08A48566E16B__INCLUDED_)
