// dotXSI.h: interface for the dotXSI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOTXSI_H__3FF3D3C1_B621_41D2_8DDB_6FE65B619993__INCLUDED_)
#define AFX_DOTXSI_H__3FF3D3C1_B621_41D2_8DDB_6FE65B619993__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <SemanticLayer.h>
#include "Display.h"
#include "BoundingBox.h"
#include "MaterialSystem.h"

#define PLAYBACK_DEFAULT	0
#define PLAYBACK_RESET		1 << 1
#define PLAYBACK_COMPLETE	1 << 2

typedef void (APIENTRY * PFNGLCLIENTACTIVETEXTUREARBPROC) (GLenum texture);

typedef struct tagSuperVertex
{
	float x;
	float y;
	float z;
	float nx;
	float ny;
	float nz;
	float r;
	float g;
	float b;
	float a;
	float uv[4][2];
	int	  index;
} SuperVertex;

typedef struct tagRenderNode 
{
	tagRenderNode()
	{
		m_pShader = NULL;
		m_lNBVertex = 0;
		m_pGeometry = NULL;
		m_bUseColor = false;
		m_iNbUvs = 0;
	};
	~tagRenderNode()
	{
		if ( m_pGeometry )
			delete [] m_pGeometry;
	};

	CSLModel					*m_pModel;
	CSIBCMatrix4x4				m_mMatrix;
	GameShader*					m_pShader;

	SuperVertex*				m_pGeometry;
	LONG						m_lNBVertex;
	bool						m_bUseColor;
	int							m_iNbUvs;

} RenderNode;

class CBone
{
	public:
		CBone() {m_pBoneNode = NULL;}
		~CBone() {;}

		CSLModel				*m_pBoneNode;
		CSIBCMatrix4x4			m_InvertedBasePose;
		CSIBCMatrix4x4			m_Current;
		CSIBCArray< SI_Float >	m_Weights;				
		CSIBCArray< SI_Float >	m_FirstWeights;			
		CSIBCArray< SI_Int >	m_Indices;				
		CSIBCArray< SI_Int >	m_WeightedIndices;		
		CSIBCArray< SI_Int >	m_FirstWeightedIndices;	
};

class dotXSI  
{
public:
	dotXSI();
	virtual ~dotXSI();

	virtual void Load ( TCHAR*	in_szPath, Display* in_pDisplay);
	virtual void Tick ( DWORD milliseconds );
	virtual void Render ();
	virtual void RenderUsingVertexArrays ( DWORD milliseconds );
	void SetCurrentShapeTrack ( int in_iShapeTrack ) { m_iShapeTrack = in_iShapeTrack; };
    void SetFrameRate ( float in_fFrameRate) {  m_fFrameRate = in_fFrameRate;};
	void UseDotXSIMaterials ( bool in_bUse ) { m_iUseDotXSIMaterials = in_bUse; };

	virtual bool TestCollision (dotXSI* in_pCollider, CSIBCVector3D& out_Collision);
	virtual CSIBCArray<BoundingBox*>& GetBoundingBoxList () { return m_BoundingBoxList; };
	virtual void RenderBoundingBoxList ();
	virtual void OffsetBoundingBox ( CSIBCMatrix4x4& in_offMatrix );
	virtual void OffsetBoundingBox ( CSIBCVector3D& in_offVector );
	virtual bool IsLoaded () { return m_bIsLoaded;};
	virtual	void SetTime ( float in_fTime ) { m_fTime = in_fTime; };
	virtual	float GetTime ( ) { return m_fTime; };
	virtual void	SetCurrentAction ( int in_iActionIdx, LONG in_lPlayFlags = 0);
	virtual int		GetCurrentAction ( ) { return m_iCurrentAction; };

private:

	virtual void RecursiveModelRender ( CSLModel* in_pModel );
	virtual void RecursiveModelRenderVA ( CSLModel* in_pModel );
	virtual float* Find4fParameter ( CSLXSIMaterial* in_pMat, char* in_szParamName );
	virtual LONG Find1lParameter( CSLXSIMaterial* in_pMat, char* in_szParamName );

	virtual void FindAllRenderNodes ( CSLModel* in_pModel );
	virtual void FlattenGeometry ( CSLModel* in_pModel, RenderNode* in_pNode );

	virtual void FindAllFCurves ( CSLModel* in_pModel );
	virtual void FindAllActions ( CSLModel* in_pModel );

	virtual void BuildBoundingBox ( CSLModel* in_pModel );
	virtual void CreateEnvelopes ();
	virtual	void AddEnvelope ( CSLEnvelope* in_pEnvelope );
	virtual void TickEnvelope ();
	


	CSLScene					m_Scene;
	float						tParams[4];
	int							m_iShapeTrack;
	float						m_fTime;
	float						m_fFrameRate;
	CSIBCArray<int>				m_iTextures;

	CSIBCArray<RenderNode*>		m_pRenderNodes;

	bool						m_iUseDotXSIMaterials;
	Display*					m_pDisplay;
	bool						m_bVisible;
	
	bool						m_bUseVertexArray;

	CSIBCArray<CSLFCurve*>	m_AllFCurves;
	CSIBCArray<BoundingBox*>	m_BoundingBoxList;
	float			ANIMATIONLENGHT;

	//
	// envelope support
	//

	CSLModel					*m_pEnvelope;
	CSIBCArray<CBone*>			m_EnvelopeList;
	CSIBCVector3D				*m_pSourceVertex;
	CSIBCVector3D				*m_pDestVertex;
	bool						m_bIsLoaded;
	LONG						m_iNumVertex;
	
	//
	// mixer support
	//
	
	CSIBCArray<CSLAction*>		m_lActionList;
	int							m_iCurrentAction;
	LONG						m_lPlaybackFlags;
	int							m_iPendingAction;
	
};

#endif // !defined(AFX_DOTXSI_H__3FF3D3C1_B621_41D2_8DDB_6FE65B619993__INCLUDED_)
