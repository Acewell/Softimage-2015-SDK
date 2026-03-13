// Geometry.h: interface for the Geometry class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GEOMETRY_H__8359AE6C_573B_4850_A659_9571B9A0F8EC__INCLUDED_)
#define AFX_GEOMETRY_H__8359AE6C_573B_4850_A659_9571B9A0F8EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SIBCArray.h"
#include "vector.h"
#include "Display.h"
#include "dotXSI.h"
#include "Sky.h"
#include "MaterialSystem.h"

void MultMatrix ( CSIBCMatrix4x4& in_mat, CSIBCVector3D& src, CSIBCVector3D& dst );

typedef struct tagAStarNode
{
	float	x;
	float	z;
	float	extent;
	bool	walkable;
	int		f;
	int		g;
	int		h;
	bool	open;

	tagAStarNode*	adjacent[8];
	tagAStarNode*	parent;

} AStarNode;

typedef struct tagPowerUp
{
	float			x;
	float			y;
	float			z;
	float			m_fRate;
	bool			m_bActive;
} PowerUp;

typedef struct tagVert
{
	vector3	position;
	vector3	normal;
	vector3	uv;
	int		index;
	float	friction;

} SingleVertex;

typedef struct tagPoly
{
	SingleVertex *v1;
	SingleVertex *v2;
	SingleVertex *v3;

	float r;
	float g;
	float b;
	float a;

	bool	m_bVisited;
	bool	m_bWalkable;
	bool	m_bSectorized;

	vector3	m_vNormal;

	CSIBCArray<tagPoly*>	m_pAdjacent;

} SinglePolygon;

typedef struct tagSector
{
	CSIBCVector3D	m_vCenter;
	CSIBCVector3D	m_vExtent;
	CSIBCArray<SinglePolygon*>	m_vPolys;
	bool			m_bVisible;
} Sector;

typedef struct tagLight
{
	float	x;
	float	y;
	float	z;
	float	w;
	float	r;
	float	g;
	float	b;
} GameLight;

#define WALKABLEONLY		1 << 1
#define REPARENT			1 << 2
#define SCORE				1 << 3
#define RESCORE				1 << 4

class Geometry  
{
public:
	Geometry( Display* in_pDisplay );
	virtual ~Geometry();

	void	SetNbVertices(LONG in_lNbVertex);

	SingleVertex* AddVertex ( float x, float y, float z,
							float nx, float ny, float nz,
							float u, float v, float friction);

	SinglePolygon* AddPolygon ( SingleVertex* v1, SingleVertex* v2, SingleVertex* v3, bool in_bWalkable );

	int				AddPowerUp ( PowerUp* in_pPowerUp );

	void			BuildAjdacentList();
	void			BuildNodes();
	void			Sectorize();

	AStarNode*		FindNode ( float x, float z, int connectivity = -1 );
	AStarNode*		FindClosestNode ( CSIBCVector3D vec, bool WalkableOnly = true );
	bool			FindPath ( CSIBCVector3D from, CSIBCVector3D to, AStarNode** out_Path );
	bool			AddAdjacent ( AStarNode* node,  AStarNode* target,CSIBCArray<AStarNode*>& list, CSIBCArray<AStarNode*>& closed, LONG flags);
	void			RemoveFromList ( AStarNode* node,  CSIBCArray<AStarNode*>& list);
	

	bool		BuildIntersectionList ( float fx, float fy, float fz,
										float tx, float ty, float tz,
										CSIBCArray<SinglePolygon*>& out_pIntersectionList);

	SinglePolygon*	FindPolygon ( float x, float z );


	bool		GetElevationFast ( CSIBCVector3D , float& out_value, CSIBCVector3D *out_Normal = NULL, float* out_Friction = NULL);

	void		DestroyGeometry();

	void		Render ( DWORD milliseconds );
	void		RenderNodes();
	void		RenderSectors();

	void		Load( char*	in_szFilename );
	void		Save( char*	in_szFilename );

	LONG		GetIndex ( SingleVertex* in_pVert );
	LONG		GetIndex ( float x, float y, float z );

	void		SetPowerUpMesh ( dotXSI* in_pPowerUp ) { m_pPowerUpMesh = in_pPowerUp; };


	CSIBCArray<SingleVertex>	m_Vertices;
	CSIBCArray<SinglePolygon>	m_Polygons;
	CSIBCArray<PowerUp>			m_PowerUps;
	CSIBCArray<GameLight>		m_Lights;
	AStarNode* start;
	AStarNode* end;
	AStarNode*	path;

	float						m_fLastElevation;
	float		m_fActiveAlpha;
	float		m_fLightingAlpha;
	float		m_fPUTime;
	int			m_iDirection;
	int			m_iDirection2;
	int			m_iTexture;
	char		m_szLevelTextureFilename[MAX_PATH];
	int			m_iLevelTexture;
	Display*	m_pDisplay;
		
	float		ambient[4];
	float		diffuse[4];
	float		specular[4];
	float		shininess;

	// path finding nodes
	CSIBCArray<AStarNode>	m_Nodes;

	// level sectors
	CSIBCArray<Sector>		m_Sectors;

	// Sky
	void	CreateSky();
	sky*	m_pSky;
	char		m_szSkyTexture1[MAX_PATH];
	char		m_szSkyTexture2[MAX_PATH];
	float		m_vFogColor[4];
	float		m_vFogDistance;

	// shaders
	GameShader* m_pShader;

	// powerup geometry
	dotXSI*		m_pPowerUpMesh;

};

#endif // !defined(AFX_GEOMETRY_H__8359AE6C_573B_4850_A659_9571B9A0F8EC__INCLUDED_)
