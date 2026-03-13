// Geometry.cpp: implementation of the Geometry class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include "GameState.h"
#include "Geometry.h"
#include "SIBCVector.h"
#include "SIBCMatrix.h"

#define GRANULARITY	1.5f
#define NEXTNODE ( GRANULARITY * 2.0f )

#define SECTOR_GRANULARITY	8.0f
#define SECTOR_NEXTNODE ( SECTOR_GRANULARITY * 2.0f )

extern char* FixLevelPath (char* in_szString);
extern char* FixTexturePath (char* in_szString);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Geometry::Geometry( Display* in_pDisplay)
{
	m_fLastElevation = 0.0f;
	m_fActiveAlpha = 0.7f;
	m_fLightingAlpha = 0.0f;
	m_iDirection = 1;
	m_iDirection2 = 1;
	m_fPUTime = 0.0f;
	m_iLevelTexture = 0;
	m_pShader = NULL;

	m_iTexture = in_pDisplay->AddTexture ( _T("flare.bmp") );



	m_pDisplay = in_pDisplay;

	memset ( m_szLevelTextureFilename, 0, MAX_PATH );

	m_pSky = NULL;
}

Geometry::~Geometry()
{
	delete m_pSky;
	m_pPowerUpMesh = NULL;
}

void	Geometry::CreateSky()
{
	if ( m_pSky != NULL )
	{
		delete m_pSky;
	}

	m_pSky = new sky ( m_pDisplay );
	m_pSky->create ( 2,2,m_pDisplay, CSIBCColorf(1.0, 0.0, 0.0));
	m_pSky->add_layer ( m_szSkyTexture1, 0, CSIBCVector3D());
	m_pSky->add_layer ( m_szSkyTexture2, 1, CSIBCVector3D());

}

void	Geometry::SetNbVertices( LONG in_lNbVertex)
{
	m_Vertices.Extend ( in_lNbVertex );
}

SingleVertex* Geometry::AddVertex ( float x, float y, float z,
							float nx, float ny, float nz,
							float u, float v, float friction)
{
	m_Vertices.Extend(1);
	SingleVertex * poly = &m_Vertices[m_Vertices.GetUsed()-1];

	poly->position.x = x;
	poly->position.y = y;
	poly->position.z = z;
	
	poly->normal.x = nx;
	poly->normal.y = ny;
	poly->normal.z = nz;

	poly->uv.x = u;
	poly->uv.y = v;
	poly->friction = friction;

	poly->index = m_Vertices.GetUsed()-1;

	return poly;	
}

SinglePolygon* Geometry::AddPolygon ( SingleVertex* v1, SingleVertex* v2, SingleVertex* v3, bool in_bWalkable )
{
	m_Polygons.Extend(1);
	SinglePolygon*	poly = &m_Polygons[m_Polygons.GetUsed()-1];
	poly->m_bSectorized = false;
	poly->v1 = v1;
	poly->v2 = v2;
	poly->v3 = v3;
	poly->r = 0.75f;
	poly->g = 0.75f;
	poly->b = 0.75f;
	poly->a = 1.0f;
	poly->m_bVisited = false;
	poly->m_bWalkable = in_bWalkable;

	vector3 A = ( v2->position - v1->position );
	vector3 B = ( v3->position - v2->position );

	poly->m_vNormal = A ^ B;

	return poly;
}

int	Geometry::AddPowerUp ( PowerUp* in_pPowerUp )
{
	in_pPowerUp->m_bActive = true;
	m_PowerUps.Extend(1);
	PowerUp* p = &m_PowerUps[m_PowerUps.GetUsed()-1];
	memcpy ( p, in_pPowerUp, sizeof (PowerUp));

	return m_PowerUps.GetUsed()-1;
}

void Geometry::Load( char*	in_szFilename )
{
	FILE *f = fopen ( FixLevelPath(in_szFilename), "rb" );

	if ( !f )
	{
		// cant find level
		// create dummy geometry
		
		AddVertex ( -20.0f, -3.5f, -20.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		AddVertex ( -20.0f, -3.5f, 20.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		AddVertex ( 20.0f, -3.5f, 20.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		AddVertex ( 20.0f, -3.5f, -20.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			
		AddPolygon ( &m_Vertices[0], &m_Vertices[1],&m_Vertices[2], true);
		AddPolygon ( &m_Vertices[0], &m_Vertices[2],&m_Vertices[3], true);
		
		Save ( in_szFilename );
		
		
		return;
	}

	
	LONG numVert = 0;
	fread ( &numVert, sizeof(LONG), 1, f );
	
	//SetNbVertices ( numVert );
	for (LONG v=0;v<numVert;v++)
	{
		SingleVertex vert;
		
		fread ( &vert.position.x, sizeof(float), 1, f );
		fread ( &vert.position.y, sizeof(float), 1, f );
		fread ( &vert.position.z, sizeof(float), 1, f );
		fread ( &vert.normal.x, sizeof(float), 1, f );
		fread ( &vert.normal.y, sizeof(float), 1, f );
		fread ( &vert.normal.z, sizeof(float), 1, f );
		fread ( &vert.uv.x, sizeof(float), 1, f );
		fread ( &vert.uv.y, sizeof(float), 1, f );
		fread ( &vert.friction, sizeof(float), 1, f );

		AddVertex ( vert.position.x, vert.position.y, vert.position.z, 
					vert.normal.x, vert.normal.y, vert.normal.z, 
					vert.uv.x, vert.uv.y, vert.friction);
	}
	
	LONG numPoly = 0;
	fread ( &numPoly, sizeof(LONG), 1, f );
	
	for (LONG p=0;p<numPoly;p++)
	{
		LONG i1,i2,i3;
		bool walkable;

		fread ( &i1, sizeof(LONG), 1, f );
		fread ( &i2, sizeof(LONG), 1, f );
		fread ( &i3, sizeof(LONG), 1, f );
		fread ( &walkable, sizeof(bool), 1, f );
		AddPolygon ( &m_Vertices[i1], &m_Vertices[i2], &m_Vertices[i3], walkable );
	}

	LONG numPU = 0;
	fread ( &numPU, sizeof(LONG), 1, f );
	LONG u;
	for (u=0;u<numPU;u++)
	{
		PowerUp	power;

		fread ( &power, sizeof(PowerUp), 1, f );
		power.m_bActive = false;

		AddPowerUp ( &power );
	}

	fread ( m_szLevelTextureFilename, sizeof(char), MAX_PATH, f );

	if ( strlen ( m_szLevelTextureFilename))
	{
		FILE* testfile = fopen ( FixTexturePath(m_szLevelTextureFilename), "rb" );
		if ( !testfile )
		{
			memset ( m_szLevelTextureFilename, 0, MAX_PATH );
			strcpy ( m_szLevelTextureFilename, "noIcon.bmp");
		} else {
			fclose ( testfile );
		}
	} 

	fread ( ambient, sizeof(GLfloat), 4, f );
	fread ( diffuse, sizeof(GLfloat), 4, f );
	fread ( specular, sizeof(GLfloat), 4, f );
	fread ( &shininess, sizeof(GLfloat), 1, f );

	// levels have no specular.
	specular[0] = specular[1] = specular[2] = specular[3] = 0.0f;

	LONG numLights = 0;
	fread ( &numLights, sizeof(LONG), 1, f );
	
	for (u=0;u<numLights;u++)
	{
		m_Lights.Extend(1);

		fread ( &m_Lights[m_Lights.GetUsed()-1], sizeof(GameLight), 1, f );
	
	}

	//
	// Material library
	//

	char * l_szMatLib = FixLevelPath(in_szFilename);
	char filename[256];
	_splitpath ( l_szMatLib, NULL, NULL, filename, NULL );
	strcat ( filename, ".xsi" );
	GetMaterialSystem()->AddMaterialLibrary ( FixLevelPath(filename) );
	m_pShader = GetMaterialSystem()->FindShader ( "level");
	m_iLevelTexture = m_pDisplay->AddTexture ( m_szLevelTextureFilename );

	fclose ( f );

	glMatrixMode ( GL_MODELVIEW );

	glPushMatrix();

	glLoadIdentity();

	for (int o=0;o<GL_MAX_LIGHTS;o++)
	{
		glDisable ( GL_LIGHT0 + o );
	}

	
	
	for (int l=0;l<m_Lights.GetUsed();l++)
	{
		float values[4];
		float color[4];
		
		values[0] = m_Lights[l].x;
		values[1] = m_Lights[l].y;
		values[2] = m_Lights[l].z;
		values[3] = 1.0f;
		
		//color[0] = m_Lights[l].r;
		//color[1] = m_Lights[l].g;
		//color[2] = m_Lights[l].b;
		//color[3] = 1.0f;

		color[0] = 0.7f;
		color[1] = 0.7f;
		color[2] = 0.7f;
		color[3] = 1.0f;
		
		glEnable ( GL_LIGHT0 + l );
		glLightfv ( GL_LIGHT0 + l, GL_POSITION, values );
		glLightfv ( GL_LIGHT0 + l, GL_DIFFUSE, color );
		glLightfv ( GL_LIGHT0 + l, GL_SPECULAR, color );
		
		
	}

	glPopMatrix();

	BuildAjdacentList ();
}

void		Geometry::Save( char*	in_szFilename )
{
	FILE *f = fopen ( FixLevelPath(in_szFilename), "wb" );

	if ( !f )
	{
		//
		// file is readonly, abort
		//
		return;
	}


	// save the vertices
	LONG numVert = m_Vertices.GetUsed();
	fwrite ( &numVert, sizeof(LONG), 1, f );
	
	for (LONG v=0;v<m_Vertices.GetUsed();v++)
	{
		SingleVertex * vert = &m_Vertices[v];
		fwrite ( &vert->position.x, sizeof(float), 1, f );
		fwrite ( &vert->position.y, sizeof(float), 1, f );
		fwrite ( &vert->position.z, sizeof(float), 1, f );
		fwrite ( &vert->normal.x, sizeof(float), 1, f );
		fwrite ( &vert->normal.y, sizeof(float), 1, f );
		fwrite ( &vert->normal.z, sizeof(float), 1, f );
		fwrite ( &vert->uv.x, sizeof(float), 1, f );
		fwrite ( &vert->uv.y, sizeof(float), 1, f );
		fwrite ( &vert->friction, sizeof(float), 1, f );
		
	}
	
	// save te triangles
	LONG numPoly = m_Polygons.GetUsed();
	fwrite ( &numPoly, sizeof(LONG), 1, f );

	for (LONG p=0;p<m_Polygons.GetUsed();p++)
	{
		SinglePolygon*	poly = &m_Polygons[p];
	
		fwrite ( &poly->v1->index, sizeof(LONG), 1, f );
		fwrite ( &poly->v2->index, sizeof(LONG), 1, f );
		fwrite ( &poly->v3->index, sizeof(LONG), 1, f );
		fwrite ( &poly->m_bWalkable, sizeof(bool), 1, f );
	}

	//save the powerups

	LONG numPU = m_PowerUps.GetUsed();
	fwrite ( &numPU, sizeof(LONG), 1, f );

	LONG u;
	for ( u=0;u<m_PowerUps.GetUsed();u++)
	{
		fwrite ( &m_PowerUps[u], sizeof(PowerUp), 1, f );

	}

	fwrite ( m_szLevelTextureFilename, sizeof(char), MAX_PATH, f );

	fwrite ( ambient, sizeof(GLfloat), 4, f );
	fwrite ( diffuse, sizeof(GLfloat), 4, f );
	fwrite ( specular, sizeof(GLfloat), 4, f );
	fwrite ( &shininess, sizeof(GLfloat), 1, f );

	//
	// lights
	//

	LONG numLights = m_Lights.GetUsed();
	fwrite ( &numLights, sizeof(LONG), 1, f );

	for (u=0;u<m_Lights.GetUsed();u++)
	{
		fwrite ( &m_Lights[u], sizeof(GameLight), 1, f );

	}


	fclose(f);


}

LONG	Geometry::GetIndex ( SingleVertex* in_pVert )
{
	for (LONG v=0;v<m_Vertices.GetUsed();v++)
	{
		if ( in_pVert == &m_Vertices[v] )
			return v;
	}

	return -1;
}

LONG	Geometry::GetIndex ( float x, float y, float z )
{
	for (LONG v=0;v<m_Vertices.GetUsed();v++)
	{
		if ( ( m_Vertices[v].position.x == x ) && 
			( m_Vertices[v].position.y == y ) && 
			( m_Vertices[v].position.z == z ))
		{
			return v;
		}
	}

	return -1;

}

void	Geometry::BuildAjdacentList()
{
	for (LONG p=0;p<m_Polygons.GetUsed();p++)
	{
		SinglePolygon*	poly = &m_Polygons[p];
		//
		// conly consider walkable polys as adjacent
		if ( !poly->m_bWalkable )
				continue;
	
		for (LONG i=0;i<m_Polygons.GetUsed();i++)
		{
			//
			// check if they share 2 vertices
			//

			if ( p==i )
				continue;

			SinglePolygon*	poly2 = &m_Polygons[i];

			//
			// conly consider walkable polys as adjacent
			if ( !poly2->m_bWalkable )
				continue;

			int matches = 0;

			if (( poly->v1 ) == ( poly2->v1 )) matches++;
			if (( poly->v1 ) == ( poly2->v2 )) matches++;
			if (( poly->v1 ) == ( poly2->v3 )) matches++;

			if ( matches)
			{
				poly->m_pAdjacent.Extend(1);
				poly->m_pAdjacent[poly->m_pAdjacent.GetUsed()-1] = poly2;
			}
		}
	}

	Sectorize();

	BuildNodes();

}

void	Geometry::BuildNodes()
{
	path = NULL;
	m_Nodes.DisposeData ();

	//
	// find level extents
	//

	float minx = 10000.0f;
	float maxx = -10000.0f;
	float minz = 10000.0f;
	float maxz = -10000.0f;

	for (int v=0;v<m_Vertices.GetUsed();v++)
	{
		if ( m_Vertices[v].position.x > maxx )
			maxx = m_Vertices[v].position.x;

		if ( m_Vertices[v].position.z > maxz )
			maxz = m_Vertices[v].position.z;

		if ( m_Vertices[v].position.x < minx )
			minx = m_Vertices[v].position.x;

		if ( m_Vertices[v].position.z < minz )
			minz = m_Vertices[v].position.z;
	}

	float	sizeX = maxx - minx;
	float	sizeZ = maxz - minz;

	float numX = sizeX / NEXTNODE;
	float numZ = sizeZ / NEXTNODE;

	for (int h=0;h<(int)numX;h++)
	{
		for (int v=0;v<(int)numZ;v++)
		{
			SinglePolygon* polygons[5];

			polygons[0] = FindPolygon ( minx + ( h * NEXTNODE ), minz + ( v * NEXTNODE ) );
			polygons[1] = FindPolygon ( minx + ( h * NEXTNODE ) + GRANULARITY, minz + ( v * NEXTNODE ) + GRANULARITY );
			polygons[2] = FindPolygon ( minx + ( h * NEXTNODE ) + GRANULARITY, minz + ( v * NEXTNODE ) - GRANULARITY);
			polygons[3] = FindPolygon ( minx + ( h * NEXTNODE ) - GRANULARITY, minz + ( v * NEXTNODE ) + GRANULARITY);
			polygons[4] = FindPolygon ( minx + ( h * NEXTNODE ) - GRANULARITY, minz + ( v * NEXTNODE ) - GRANULARITY);

			for (int f=0;f<5;f++)
			{
				if ( polygons[f] )
				{
					bool addPoly = false;

					if ( polygons[f]->m_bWalkable )
						addPoly = true;

					if ( !addPoly )
					{
						//
						// check adjacent
						//
						for (int a=0;a<polygons[f]->m_pAdjacent.GetUsed();a++)
						{
							if ( polygons[f]->m_pAdjacent[a]->m_bWalkable )
							{
								addPoly = true;
								break;
							}
						}
					}
					if ( addPoly )
					{
						m_Nodes.Extend(1);
						AStarNode* node = &m_Nodes[m_Nodes.GetUsed()-1];
						node->walkable = true;
						node->x = minx + ( h * NEXTNODE );
						node->z = minz + ( v * NEXTNODE );
						node->extent = GRANULARITY;
					}

				}			
			}

		}
	}

	//
	// do node connectivity
	//

	for (int n=0;n<m_Nodes.GetUsed();n++)
	{
		AStarNode* l_pNode = &m_Nodes[n];
		l_pNode->parent = NULL;

		for (int a=0;a<8;a++)
		{
			l_pNode->adjacent[a] = FindNode ( l_pNode->x, l_pNode->z, a );
		}
	}

}

AStarNode*		Geometry::FindNode ( float x, float z, int connectivity)
{
	float nx,nz;

	switch (connectivity)
	{
	case 0: nx = x + NEXTNODE; nz = z;break;
	case 1: nx = x - NEXTNODE; nz = z;break;
	case 2: nx = x; nz = z + NEXTNODE;break;
	case 3: nx = x; nz = z - NEXTNODE;break;
	case 4: nx = x + NEXTNODE; nz = z + NEXTNODE;break;
	case 5: nx = x + NEXTNODE; nz = z - NEXTNODE;break;
	case 6: nx = x - NEXTNODE; nz = z + NEXTNODE;break;
	case 7: nx = x - NEXTNODE; nz = z - NEXTNODE;break;
	}

	for (int n=0;n<m_Nodes.GetUsed();n++)
	{
		if ( ( m_Nodes[n].x == nx) && ( m_Nodes[n].z == nz))
		{
			return &m_Nodes[n];
		}
	}
	return NULL;
}

bool	Geometry::FindPath ( CSIBCVector3D from, CSIBCVector3D to, AStarNode** out_Path )
{
	for (int n=0;n<m_Nodes.GetUsed();n++)
	{
		m_Nodes[n].open = false;
	}

	start = FindClosestNode ( from );
	end = FindClosestNode ( to );

	std::set<AStarNode*>	openList;
	std::set<AStarNode*>	closeList;
	std::set<AStarNode*>::iterator listIter;
	
	if (( !start ) || ( !end))
		return false;

	start->g = 0;
	openList.insert ( start );

	int maxNodes = 25;

	while((maxNodes--))
	{
		if ( openList.size () )
		{
			int cost = 10000;

			listIter = openList.begin ();
			AStarNode* l_pCurrent = NULL;
			std::set<AStarNode*>::iterator cachedIter;

			while ( listIter != openList.end() )
			{
				if ( (*listIter)->f < cost )
				{
					l_pCurrent = (*listIter);
					cost = l_pCurrent->f;
					cachedIter = listIter;
				}
				listIter++;
			}
			closeList.insert ( l_pCurrent );
			openList.erase ( cachedIter );
            
			for (int v=0;v<8;v++)
			{
				AStarNode* l_adj = l_pCurrent->adjacent[v];
				if ( !l_adj )
					continue;
				if ( !l_adj->walkable )
					continue;

				if ( closeList.find ( l_adj ) != closeList.end () )
					continue;

				if ( openList.find ( l_adj ) == openList.end () )
				{
					openList.insert ( l_adj );
					l_adj->parent = l_pCurrent;

					if (v<4)
					{
						l_adj->g = 10;
					} else {
						l_adj->g = 14;
					}
					l_adj->g += l_adj->parent->g;

					float dist1 = fabs(l_adj->x - end->x);
					float dist2 = fabs(l_adj->z - end->z);
					dist1 /= NEXTNODE;
					dist2 /= NEXTNODE;
					l_adj->h = ((int)dist1 * 10) + ((int)dist2 * 10 );
					
					l_adj->f = l_adj->g + l_adj->h;
				} else {

					if ( l_adj->g < l_pCurrent->g )
					{
						l_adj->parent = l_pCurrent;
						if (v<4)
						{
							l_adj->g = 10;
						} else {
							l_adj->g = 14;
						}
						l_adj->g += l_adj->parent->g;
						l_adj->f = l_adj->g + l_adj->h;
					}
				}
			}

			if ( openList.find ( end ) != openList.end() )
			{
				break;
			}

			if ( !openList.size() )
			{
				break;;
			}

		}
	}

	AStarNode* pnt = end;

	std::set<AStarNode*>	pathList;
	while ( pnt->parent )
	{
		pathList.insert ( pnt );
		pnt = pnt->parent;

		if ( pathList.find ( pnt ) != pathList.end() )
		{
			//
			// found a circular dependancy!
			//
			pnt->parent = NULL;
			break;
		}
	}

	*out_Path = end;
	path = end;
	return true;
}
void	Geometry::RemoveFromList ( AStarNode* node,  CSIBCArray<AStarNode*>& list)
{
	for (int a=0;a<list.GetUsed();a++)
	{
		if ( node == list[a] )
		{
			list.DeleteAt ( a,1);
			break;
		}
	}
}


bool	Geometry::AddAdjacent ( AStarNode* node, AStarNode* target, CSIBCArray<AStarNode*>& list, CSIBCArray<AStarNode*>& closed, LONG flags)
{
	int a;
	bool retval = false;

	for (a=0;a<4;a++)
	{
		AStarNode* l_panode = node->adjacent [a];

		if ( !l_panode )
		{
			continue;
		}

		for (int c=0;c<closed.GetUsed();c++)
		{
			if ( closed[c] == l_panode )
				continue;
		}

		if ( flags & WALKABLEONLY )
		{
			if ( !l_panode->walkable )
			{
				continue;
			}
		}

		bool found = false;
		for (int s=0;s<list.GetUsed();s++)
		{
			if ( list[s] == l_panode )
			{
				found = true;
				break;
			}
		}

		if ( !found)
		{
			list.Extend(1);
			list[list.GetUsed()-1] = l_panode;

			if ( target == l_panode )
				retval = true;
		}
		
		if ( !l_panode->open )
		{
			l_panode->open = true;
		} else {

			if ( l_panode->g < node->g )
			{
				l_panode->parent = node;
				l_panode->g = 10 + l_panode->parent->g;
				l_panode->f = l_panode->g + l_panode->h;
			}

		}

		if (( flags & REPARENT ) && ( l_panode->parent == NULL))
		{
			l_panode->parent = node;
		}

		if ( flags & SCORE )
		{
			l_panode->g = 10;
			if ( l_panode->parent )
			{
				l_panode->g += l_panode->parent->g;
			}

			float dist1 = CSIBCVector3D (l_panode->x, 0.0f, 0.0f).GetDistanceFrom ( CSIBCVector3D(target->x, 0.0f, 0.0f));
			float dist2 = CSIBCVector3D (0.0f, 0.0f, l_panode->z).GetDistanceFrom ( CSIBCVector3D(0.0f, 0.0f, target->z));

			int a1 = (int)( dist1 / NEXTNODE );
			int a2 = (int)( dist2 / NEXTNODE );
			l_panode->h = (a1 * 10) + (a2*10);
			l_panode->f = l_panode->g + l_panode->h;


		}
	}

	for (a=0;a<4;a++)
	{
		AStarNode* l_panode = node->adjacent [a];
		if ( !l_panode )
			continue;

		for (int c=0;c<closed.GetUsed();c++)
		{
			if ( closed[c] == l_panode )
				continue;
		}

		if ( flags & WALKABLEONLY )
		{
			if ( !l_panode->walkable )
			{
				continue;
			}
		}
		
		bool found = false;
		for (int s=0;s<list.GetUsed();s++)
		{
			if ( list[s] == l_panode )
			{
				found = true;
				break;
			}
		}

		if (!found)
		{
			list.Extend(1);
			list[list.GetUsed()-1] = l_panode;
			if ( target == l_panode )
				retval = true;
		}
		
		if ( !l_panode->open )
		{
			l_panode->open = true;
		} else {

			if ( l_panode->g < node->g )
			{
				l_panode->parent = node;
				l_panode->g = 10 + l_panode->parent->g;
				l_panode->f = l_panode->g + l_panode->h;
			}

		}

		if ( flags & REPARENT )
		{
			l_panode->parent = node;
		}

		if ( flags & SCORE )
		{
			l_panode->g = 14;
			if ( l_panode->parent )
			{
				l_panode->g += l_panode->parent->g;
			}

			float dist1 = CSIBCVector3D (l_panode->x, 0.0f, 0.0f).GetDistanceFrom ( CSIBCVector3D(target->x, 0.0f, 0.0f));
			float dist2 = CSIBCVector3D (0.0f, 0.0f, l_panode->z).GetDistanceFrom ( CSIBCVector3D(0.0f, 0.0f, target->z));

			int a1 = (int)( dist1 / NEXTNODE );
			int a2 = (int)( dist2 / NEXTNODE );
			l_panode->h = (a1 * 10) + (a2*10);
			l_panode->f = l_panode->g + l_panode->h;
		}
	}

	return retval;

}


AStarNode* Geometry::FindClosestNode ( CSIBCVector3D vec , bool WalkableOnly)
{
	float distance = 99999.0f;
	AStarNode* l_pReturn = NULL;

	for (int n=0;n<m_Nodes.GetUsed();n++)
	{
		AStarNode* l_pCurrentNode = &m_Nodes[n];

		if ( ( !l_pCurrentNode->walkable ) && WalkableOnly)
			continue;

		float nd = vec.GetDistanceFrom ( CSIBCVector3D(l_pCurrentNode->x, vec.GetY(), l_pCurrentNode->z));

		if ( nd < distance )
		{
			l_pReturn = l_pCurrentNode;
			distance = nd;

		}
	}

	return l_pReturn;
}

void	Geometry::Render ( DWORD milliseconds )
{

	// cull sectors
	GameState* gs = GetGameState ( m_pDisplay );
	for (int c=0;c<m_Sectors.GetUsed();c++)
	{
		m_Sectors[c].m_bVisible = gs->Cull ( m_Sectors[c].m_vCenter, m_Sectors[c].m_vExtent ); 
	}


	m_fActiveAlpha -= (milliseconds / 1000.0f) * m_iDirection;
	m_fLightingAlpha += (milliseconds / 2000.0f) * m_iDirection2;

	m_fPUTime += milliseconds;
	if ( m_fPUTime > 1000.0f )
	{
		m_fPUTime = 0.0f;
	}


	if ( m_fLightingAlpha > 0.5f )
	{
		m_iDirection2 = -1;
	}

	if ( m_fLightingAlpha < -0.5f )
	{
		m_iDirection2 = 1;
	}

	if ( m_fActiveAlpha < 0.5f )
	{
		m_iDirection = -1;
	} 

	if ( m_fActiveAlpha > 0.7f )
	{
		m_iDirection = 1;
	}

	glPushAttrib ( GL_ALL_ATTRIB_BITS );
	glEnable ( GL_LIGHTING );
	glDisable ( GL_COLOR_MATERIAL );

#define GL_LIGHT_MODEL_COLOR_CONTROL_EXT				0x81F8
#define GL_SEPARATE_SPECULAR_COLOR_EXT					0x81FA

	glLightModeli( GL_LIGHT_MODEL_COLOR_CONTROL_EXT, GL_SEPARATE_SPECULAR_COLOR_EXT );

	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	
	//
	// turn off all lights
	//
	
	for (int o=0;o<GL_MAX_LIGHTS;o++)
	{
		glDisable ( GL_LIGHT0 + o );
	}
	
	for (int l=0;l<m_Lights.GetUsed();l++)
	{
		float values[4];
		float color[4];
		
		values[0] = m_Lights[l].x;
		values[1] = m_Lights[l].y;
		values[2] = m_Lights[l].z;
		values[3] = 1.0f;
		
		color[0] = m_Lights[l].r;
		color[1] = m_Lights[l].g;
		color[2] = m_Lights[l].b;
		color[3] = 1.0f;
		
		glEnable ( GL_LIGHT0 + l );
		glLightfv ( GL_LIGHT0 + l, GL_POSITION, values );
		glLightfv ( GL_LIGHT0 + l, GL_DIFFUSE, color );
		glLightfv ( GL_LIGHT0 + l, GL_SPECULAR, color );
		
	}

	CSIBCVector3D eye = gs->GetCameraPosition ();

	glPushMatrix();
	if ( m_pSky )
	{
		m_pSky->set_fog_color ( CSIBCColorf ( m_vFogColor[0], m_vFogColor[1], m_vFogColor[2], 1.0f));
		glTranslatef ( eye.m_fX, eye.m_fY+100.0f, eye.m_fZ);
		m_pSky->render_background ();
		m_pSky->render ();
	}
	glPopMatrix();

	glEnable ( GL_FOG );
	glFogi (GL_FOG_MODE, GL_LINEAR); 
    glHint (GL_FOG_HINT, GL_FASTEST);  
    glFogf (GL_FOG_START,0.0f);     
	glFogf (GL_FOG_END, m_vFogDistance); 
	glFogfv (GL_FOG_COLOR, m_vFogColor);

	if ( m_pShader != NULL )
	{
		glEnable ( GL_TEXTURE_2D );
		GetMaterialSystem()->ExecuteShader ( m_pShader );
	} else {

		if ( m_iLevelTexture )
		{
			glEnable ( GL_TEXTURE_2D );
			glBindTexture ( GL_TEXTURE_2D, m_iLevelTexture );
		}
	}

	





	//
	// non-walkable
	//

	glBegin ( GL_TRIANGLES );
	
	for (int s=0;s<m_Sectors.GetUsed();s++)
	{
		Sector* sector = &m_Sectors[s];

		if ( !sector->m_bVisible )
			continue;

		for (int p=0;p<sector->m_vPolys.GetUsed();p++)
		{
			SinglePolygon *sp = sector->m_vPolys[p];

			if ( sp->m_bWalkable )
				continue;

			glTexCoord2d ( sp->v1->uv.x, sp->v1->uv.y );
			glNormal3f( sp->v1->normal.x, sp->v1->normal.y, sp->v1->normal.z );
			glVertex3f ( sp->v1->position.x, sp->v1->position.y, sp->v1->position.z );
			
			glTexCoord2d ( sp->v2->uv.x, sp->v2->uv.y );
			glNormal3f( sp->v2->normal.x, sp->v2->normal.y, sp->v2->normal.z );
			glVertex3f ( sp->v2->position.x, sp->v2->position.y, sp->v2->position.z );
			
			glTexCoord2d ( sp->v3->uv.x, sp->v3->uv.y );
			glNormal3f( sp->v3->normal.x, sp->v3->normal.y, sp->v3->normal.z );
			glVertex3f ( sp->v3->position.x, sp->v3->position.y, sp->v3->position.z );
		}

	}
	
	glEnd();

	glEnable ( GL_COLOR_MATERIAL );
	glEnable ( GL_BLEND );
	glDisable ( GL_TEXTURE_2D );

	glBegin ( GL_TRIANGLES );
	int v;
	for (v=0;v<m_Polygons.GetUsed();v++)
	{
		SinglePolygon *sp = &m_Polygons[v];

		if ( !sp->m_bWalkable )
			continue;
		if ( sp->r == 0.1f )
		{
			glColor4f ( sp->r, sp->g, sp->b, 1.0f );
		} else {
			glColor4f ( sp->r, sp->g, sp->b, 1.0f);
		}
		
		glTexCoord2d ( sp->v1->uv.x, sp->v1->uv.y );
		glNormal3f( sp->v1->normal.x, sp->v1->normal.y, sp->v1->normal.z );
		glVertex3f ( sp->v1->position.x, sp->v1->position.y, sp->v1->position.z );
		
		glTexCoord2d ( sp->v2->uv.x, sp->v2->uv.y );
		glNormal3f( sp->v2->normal.x, sp->v2->normal.y, sp->v2->normal.z );
		glVertex3f ( sp->v2->position.x, sp->v2->position.y, sp->v2->position.z );
		
		glTexCoord2d ( sp->v3->uv.x, sp->v3->uv.y );
		glNormal3f( sp->v3->normal.x, sp->v3->normal.y, sp->v3->normal.z );
		glVertex3f ( sp->v3->position.x, sp->v3->position.y, sp->v3->position.z );
	}
	
	glEnd();
	
	RenderNodes();

	RenderSectors();

	//
	// render a billboard behind the powerup
	for (int p=0;p<m_PowerUps.GetUsed();p++)
	{
		
		PowerUp* power = &m_PowerUps[p];

		if ( !power->m_bActive )
			continue;

		float adjustedY = power->y + (sin ( (m_fPUTime / 1000.0f) * 3.1415926f ));

		glPushMatrix();
		glTranslatef ( power->x, adjustedY, power->z);
		m_pPowerUpMesh->Render ();
		glPopMatrix();
	}

	//
	// render lighting effect

	//
	// Disable ZBuffer updates
	//

	//
	// IMPORTANT: 
	// Here we disable the ZBuffer write operations but keep the read operation active. This is because
	// we need to zbuffer the whole particle system against the world, but not against itself!

	glDepthMask ( GL_FALSE );
	glEnable( GL_DEPTH_TEST );

	glBlendFunc(GL_SRC_ALPHA ,GL_ONE);

	glDisable (GL_LIGHTING);
	glEnable (GL_BLEND);
	glDisable (GL_FOG);
	glDisable (GL_DITHER);
	glHint ( GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST );
	glDisable( GL_CULL_FACE );

	glEnable ( GL_TEXTURE_2D );
	glBindTexture (GL_TEXTURE_2D, m_iTexture);
	//
	// Get modelview matrix
	//

	GLfloat camera[16];

	glMatrixMode ( GL_MODELVIEW );

	glGetFloatv(GL_MODELVIEW_MATRIX, camera);

	CSIBCMatrix4x4	l_ModelView ( camera );
	CSIBCVector4D	z ( 0.0f,0.0f,0.0f,1.0f );

	l_ModelView.Set(3,0, 0.0f);
	l_ModelView.Set(3,1, 0.0f);
	l_ModelView.Set(3,2, 0.0f);
	l_ModelView.Set(3,3, 1.0f);

	for ( v=0;v<m_Polygons.GetUsed();v++)
	{
		SinglePolygon*	poly = &m_Polygons[v];

		if ( poly->r == 0.1f )
			continue;

		if ( !poly->m_bWalkable )
			continue;

		//if ( RANDOM_NUM > 0.5f )
		//	continue;

		//
		// tri centroid
		float cx = ( poly->v1->position.x + poly->v2->position.x + poly->v3->position.x  ) / 3.0f;
		float cy = ( poly->v1->position.y + poly->v2->position.y + poly->v3->position.y  ) / 3.0f;
		float cz = ( poly->v1->position.z + poly->v2->position.z + poly->v3->position.z  ) / 3.0f;

		//
		// calculate area
		//

		float a = ( poly->v1->position.Distance ( poly->v2->position ));
		float b = ( poly->v2->position.Distance ( poly->v3->position ));
		float c = ( poly->v3->position.Distance ( poly->v1->position ));

		float sp  = ( a + b + c ) / 2.0f;

		float area = sp;

		//int l_fSize = 2.0f;
		float l_fSize = area;
		CSIBCVector3D p1 ( l_fSize * 1.0f, 0.2f, l_fSize * 1.0f);
		CSIBCVector3D p2 ( -l_fSize * 1.0f, 0.2f, l_fSize * 1.0f );
		CSIBCVector3D p3 ( l_fSize * 1.0f, 0.2f, -l_fSize * 1.0f);
		CSIBCVector3D p4 ( -l_fSize * 1.0f, 0.2f, -l_fSize * 1.0f );
		/*
		p1.m_fX += cx;
		p2.m_fX += cx;
		p3.m_fX += cx;
		p4.m_fX += cx;

		p1.m_fZ += cz;
		p2.m_fZ += cz;
		p3.m_fZ += cz;
		p4.m_fZ += cz;

		p1.m_fY += cy;
		p2.m_fY += cy;
		p3.m_fY += cy;
		p4.m_fY += cy;
		*/
		CSIBCVector3D rp1, rp2, rp3, rp4;

		rp1 = p1;
		rp2 = p2;
		rp3 = p3;
		rp4 = p4;


		//MultMatrix ( l_ModelView, p1, rp1 );
		//MultMatrix ( l_ModelView, p2, rp2 );
		//MultMatrix ( l_ModelView, p3, rp3 );
		//MultMatrix ( l_ModelView, p4, rp4 );

		glColor4f(0.8f, 0.8f,1.0f, m_fLightingAlpha);

		glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(1.0f, 1.0f); 
		glVertex3f( rp1.m_fX + cx, rp1.m_fY + cy, rp1.m_fZ + cz);

		glTexCoord2f(0.0f, 1.0f); 
		glVertex3f( rp2.m_fX + cx, rp2.m_fY + cy, rp2.m_fZ + cz);

		glTexCoord2f(1.0f, 0.0f); 
		glVertex3f( rp3.m_fX + cx, rp3.m_fY + cy, rp3.m_fZ + cz);

		glTexCoord2f(0.0f, 0.0f); 
		glVertex3f( rp4.m_fX + cx, rp4.m_fY + cy, rp4.m_fZ + cz);
		glEnd();
	}


	//
	// render a billboard behind the powerup
	for (int b=0;b<m_PowerUps.GetUsed();b++)
	{
		
		PowerUp* power = &m_PowerUps[b];

		if ( !power->m_bActive )
			continue;

		int l_fSize = 2.0f;
		CSIBCVector3D p1 ( l_fSize * 1.0f, l_fSize * 1.0f, 0.0f );
		CSIBCVector3D p2 ( -l_fSize * 1.0f, l_fSize * 1.0f, 0.0f );
		CSIBCVector3D p3 ( l_fSize * 1.0f, -l_fSize * 1.0f, 0.0f );
		CSIBCVector3D p4 ( -l_fSize * 1.0f, -l_fSize * 1.0f, 0.0f );

		CSIBCVector3D rp1, rp2, rp3, rp4;

		MultMatrix ( l_ModelView, p1, rp1 );
		MultMatrix ( l_ModelView, p2, rp2 );
		MultMatrix ( l_ModelView, p3, rp3 );
		MultMatrix ( l_ModelView, p4, rp4 );

		glColor4f(1.0f, 0.8f,0.6f, 0.8f);

		float adjustedY = power->y + (sin ( (m_fPUTime / 1000.0f) * 3.1415926f ));

		glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(1.0f, 1.0f); 
		glVertex3f( rp1.m_fX + power->x, rp1.m_fY + adjustedY, rp1.m_fZ + power->z);

		glTexCoord2f(0.0f, 1.0f); 
		glVertex3f( rp2.m_fX + power->x, rp2.m_fY + adjustedY, rp2.m_fZ + power->z);

		glTexCoord2f(1.0f, 0.0f); 
		glVertex3f( rp3.m_fX + power->x, rp3.m_fY + adjustedY, rp3.m_fZ + power->z);

		glTexCoord2f(0.0f, 0.0f); 
		glVertex3f( rp4.m_fX + power->x, rp4.m_fY + adjustedY, rp4.m_fZ + power->z);
		glEnd();
		
	}



	glPopAttrib();

}

void	Geometry::RenderSectors()
{
	if ( !GetGameState(m_pDisplay)->GetShowSectors() )
		return;

	glDisable ( GL_TEXTURE_2D );
	glDisable ( GL_LIGHTING );
	glDisable ( GL_FOG );
	glBegin ( GL_LINES );
	for (int n=0;n<m_Sectors.GetUsed();n++)
	{
		glColor3f ( 1.0f, 1.0f, 1.0f);

		glVertex3f ( m_Sectors[n].m_vCenter.m_fX-m_Sectors[n].m_vExtent.m_fX, m_Sectors[n].m_vCenter.m_fY-m_Sectors[n].m_vExtent.m_fY, m_Sectors[n].m_vCenter.m_fZ-m_Sectors[n].m_vExtent.m_fZ );
		glVertex3f ( m_Sectors[n].m_vCenter.m_fX-m_Sectors[n].m_vExtent.m_fX, m_Sectors[n].m_vCenter.m_fY-m_Sectors[n].m_vExtent.m_fY, m_Sectors[n].m_vCenter.m_fZ+m_Sectors[n].m_vExtent.m_fZ );

		glVertex3f ( m_Sectors[n].m_vCenter.m_fX-m_Sectors[n].m_vExtent.m_fX,  m_Sectors[n].m_vCenter.m_fY-m_Sectors[n].m_vExtent.m_fY, m_Sectors[n].m_vCenter.m_fZ+m_Sectors[n].m_vExtent.m_fZ );
		glVertex3f ( m_Sectors[n].m_vCenter.m_fX+m_Sectors[n].m_vExtent.m_fX,  m_Sectors[n].m_vCenter.m_fY-m_Sectors[n].m_vExtent.m_fY, m_Sectors[n].m_vCenter.m_fZ+m_Sectors[n].m_vExtent.m_fZ );

		glVertex3f ( m_Sectors[n].m_vCenter.m_fX+m_Sectors[n].m_vExtent.m_fX,  m_Sectors[n].m_vCenter.m_fY-m_Sectors[n].m_vExtent.m_fY, m_Sectors[n].m_vCenter.m_fZ+m_Sectors[n].m_vExtent.m_fZ );
		glVertex3f ( m_Sectors[n].m_vCenter.m_fX+m_Sectors[n].m_vExtent.m_fX,  m_Sectors[n].m_vCenter.m_fY-m_Sectors[n].m_vExtent.m_fY, m_Sectors[n].m_vCenter.m_fZ-m_Sectors[n].m_vExtent.m_fZ );

		glVertex3f ( m_Sectors[n].m_vCenter.m_fX+m_Sectors[n].m_vExtent.m_fX,  m_Sectors[n].m_vCenter.m_fY-m_Sectors[n].m_vExtent.m_fY, m_Sectors[n].m_vCenter.m_fZ-m_Sectors[n].m_vExtent.m_fZ );
		glVertex3f ( m_Sectors[n].m_vCenter.m_fX-m_Sectors[n].m_vExtent.m_fX,  m_Sectors[n].m_vCenter.m_fY-m_Sectors[n].m_vExtent.m_fY, m_Sectors[n].m_vCenter.m_fZ-m_Sectors[n].m_vExtent.m_fZ );


		//
		// top
		glVertex3f ( m_Sectors[n].m_vCenter.m_fX-m_Sectors[n].m_vExtent.m_fX, m_Sectors[n].m_vCenter.m_fY+m_Sectors[n].m_vExtent.m_fY, m_Sectors[n].m_vCenter.m_fZ-m_Sectors[n].m_vExtent.m_fZ );
		glVertex3f ( m_Sectors[n].m_vCenter.m_fX-m_Sectors[n].m_vExtent.m_fX, m_Sectors[n].m_vCenter.m_fY+m_Sectors[n].m_vExtent.m_fY, m_Sectors[n].m_vCenter.m_fZ+m_Sectors[n].m_vExtent.m_fZ );

		glVertex3f ( m_Sectors[n].m_vCenter.m_fX-m_Sectors[n].m_vExtent.m_fX,  m_Sectors[n].m_vCenter.m_fY+m_Sectors[n].m_vExtent.m_fY, m_Sectors[n].m_vCenter.m_fZ+m_Sectors[n].m_vExtent.m_fZ );
		glVertex3f ( m_Sectors[n].m_vCenter.m_fX+m_Sectors[n].m_vExtent.m_fX,  m_Sectors[n].m_vCenter.m_fY+m_Sectors[n].m_vExtent.m_fY, m_Sectors[n].m_vCenter.m_fZ+m_Sectors[n].m_vExtent.m_fZ );
		
		glVertex3f ( m_Sectors[n].m_vCenter.m_fX+m_Sectors[n].m_vExtent.m_fX,  m_Sectors[n].m_vCenter.m_fY+m_Sectors[n].m_vExtent.m_fY, m_Sectors[n].m_vCenter.m_fZ+m_Sectors[n].m_vExtent.m_fZ );
		glVertex3f ( m_Sectors[n].m_vCenter.m_fX+m_Sectors[n].m_vExtent.m_fX,  m_Sectors[n].m_vCenter.m_fY+m_Sectors[n].m_vExtent.m_fY, m_Sectors[n].m_vCenter.m_fZ-m_Sectors[n].m_vExtent.m_fZ );

		glVertex3f ( m_Sectors[n].m_vCenter.m_fX+m_Sectors[n].m_vExtent.m_fX,  m_Sectors[n].m_vCenter.m_fY+m_Sectors[n].m_vExtent.m_fY, m_Sectors[n].m_vCenter.m_fZ-m_Sectors[n].m_vExtent.m_fZ );
		glVertex3f ( m_Sectors[n].m_vCenter.m_fX-m_Sectors[n].m_vExtent.m_fX,  m_Sectors[n].m_vCenter.m_fY+m_Sectors[n].m_vExtent.m_fY, m_Sectors[n].m_vCenter.m_fZ-m_Sectors[n].m_vExtent.m_fZ );

		// verticals
		glVertex3f ( m_Sectors[n].m_vCenter.m_fX-m_Sectors[n].m_vExtent.m_fX, m_Sectors[n].m_vCenter.m_fY-m_Sectors[n].m_vExtent.m_fY, m_Sectors[n].m_vCenter.m_fZ-m_Sectors[n].m_vExtent.m_fZ );
		glVertex3f ( m_Sectors[n].m_vCenter.m_fX-m_Sectors[n].m_vExtent.m_fX, m_Sectors[n].m_vCenter.m_fY+m_Sectors[n].m_vExtent.m_fY, m_Sectors[n].m_vCenter.m_fZ-m_Sectors[n].m_vExtent.m_fZ );

		glVertex3f ( m_Sectors[n].m_vCenter.m_fX-m_Sectors[n].m_vExtent.m_fX, m_Sectors[n].m_vCenter.m_fY-m_Sectors[n].m_vExtent.m_fY, m_Sectors[n].m_vCenter.m_fZ+m_Sectors[n].m_vExtent.m_fZ );
		glVertex3f ( m_Sectors[n].m_vCenter.m_fX-m_Sectors[n].m_vExtent.m_fX, m_Sectors[n].m_vCenter.m_fY+m_Sectors[n].m_vExtent.m_fY, m_Sectors[n].m_vCenter.m_fZ+m_Sectors[n].m_vExtent.m_fZ );

		glVertex3f ( m_Sectors[n].m_vCenter.m_fX+m_Sectors[n].m_vExtent.m_fX,  m_Sectors[n].m_vCenter.m_fY-m_Sectors[n].m_vExtent.m_fY, m_Sectors[n].m_vCenter.m_fZ+m_Sectors[n].m_vExtent.m_fZ );
		glVertex3f ( m_Sectors[n].m_vCenter.m_fX+m_Sectors[n].m_vExtent.m_fX,  m_Sectors[n].m_vCenter.m_fY+m_Sectors[n].m_vExtent.m_fY, m_Sectors[n].m_vCenter.m_fZ+m_Sectors[n].m_vExtent.m_fZ );

		glVertex3f ( m_Sectors[n].m_vCenter.m_fX-m_Sectors[n].m_vExtent.m_fX,  m_Sectors[n].m_vCenter.m_fY-m_Sectors[n].m_vExtent.m_fY, m_Sectors[n].m_vCenter.m_fZ-m_Sectors[n].m_vExtent.m_fZ );
		glVertex3f ( m_Sectors[n].m_vCenter.m_fX-m_Sectors[n].m_vExtent.m_fX,  m_Sectors[n].m_vCenter.m_fY+m_Sectors[n].m_vExtent.m_fY, m_Sectors[n].m_vCenter.m_fZ-m_Sectors[n].m_vExtent.m_fZ );
	
	}
    glEnd();

	
}

void	Geometry::RenderNodes()
{
	if ( !GetGameState(m_pDisplay)->GetShowAIGrid() )
		return;

	glDisable ( GL_TEXTURE_2D );
	glDisable ( GL_LIGHTING );
	glBegin ( GL_LINES );
    for (int n=0;n<m_Nodes.GetUsed();n++)
	{
		if ( m_Nodes[n].walkable )
		{
			glColor3f ( 1.0f, 1.0f, 1.0f);
		} else {
			continue;
		} 

		if ( ( &m_Nodes[n] == start )||( &m_Nodes[n] == end ))
		{
			glColor3f ( 1.0f, 0.0f, 0.0f );
		}

		glVertex3f ( m_Nodes[n].x-m_Nodes[n].extent, m_fLastElevation + 1.0f, m_Nodes[n].z-m_Nodes[n].extent );
		glVertex3f ( m_Nodes[n].x-m_Nodes[n].extent, m_fLastElevation + 1.0f, m_Nodes[n].z+m_Nodes[n].extent );
		
		glVertex3f ( m_Nodes[n].x-m_Nodes[n].extent, m_fLastElevation + 1.0f, m_Nodes[n].z+m_Nodes[n].extent );
		glVertex3f ( m_Nodes[n].x+m_Nodes[n].extent, m_fLastElevation + 1.0f, m_Nodes[n].z+m_Nodes[n].extent );
		
		glVertex3f ( m_Nodes[n].x+m_Nodes[n].extent, m_fLastElevation + 1.0f, m_Nodes[n].z+m_Nodes[n].extent );
		glVertex3f ( m_Nodes[n].x+m_Nodes[n].extent, m_fLastElevation + 1.0f, m_Nodes[n].z-m_Nodes[n].extent );

		glVertex3f ( m_Nodes[n].x+m_Nodes[n].extent, m_fLastElevation + 1.0f, m_Nodes[n].z-m_Nodes[n].extent );
		glVertex3f ( m_Nodes[n].x-m_Nodes[n].extent, m_fLastElevation + 1.0f, m_Nodes[n].z-m_Nodes[n].extent );

		int a;
		for (a=0;a<8;a++)
		{
			if ( m_Nodes[n].adjacent[a] )
			{
				AStarNode* l_pA = m_Nodes[n].adjacent[a];

				CSIBCVector3D to = CSIBCVector3D ( l_pA->x - m_Nodes[n].x, 0.0, l_pA->z - m_Nodes[n].z);
				to.Normalize();
				to = to.Scale( GRANULARITY / 2 );

				glColor3f ( 0.0f, 0.0f, 1.0f );
				glVertex3f ( m_Nodes[n].x, 2.0f, m_Nodes[n].z );
				glVertex3f ( m_Nodes[n].x + to.GetX(), 2.0f, m_Nodes[n].z+ to.GetZ() );
			}
		}
	}
    glEnd();

	if ( path )
	{
		glBegin(GL_LINES);
		AStarNode* l_node = path;

		while ( l_node->parent != NULL )
		{
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f ( l_node->x, m_fLastElevation, l_node->z );
			glVertex3f ( l_node->parent->x, m_fLastElevation, l_node->parent->z);
			l_node = l_node->parent;
		}
		glEnd();

	}

}

void	Geometry::DestroyGeometry()
{
	m_Polygons.DisposeData();
	m_Vertices.DisposeData();
}

SinglePolygon*	Geometry::FindPolygon ( float x, float z )
{
	vector3 origin = vector3(x,2.0f,z);
	vector3 to = vector3 ( 0.0f, -10.0f, 0.0f);
	
	Sector* in_pContainer = NULL;

	for (int s=0;s<m_Sectors.GetUsed();s++)
	{
		Sector* sector = &m_Sectors[s];

		if ( (x > ( sector->m_vCenter.m_fX - sector->m_vExtent.m_fX )) &&
				(x < ( sector->m_vCenter.m_fX + sector->m_vExtent.m_fX ))&&
				(z > ( sector->m_vCenter.m_fZ - sector->m_vExtent.m_fZ ))&&
				(z < ( sector->m_vCenter.m_fZ + sector->m_vExtent.m_fZ )))
			{
				in_pContainer = sector;
				break;
			}
	}

	if ( in_pContainer == NULL )
		return NULL;
    		

	for (int p=0;p<in_pContainer->m_vPolys.GetUsed();p++)
	{
		SinglePolygon*	poly = in_pContainer->m_vPolys[p];
		float u,v;
		
		vector3 tri[3];
		tri[0] = poly->v1->position;
		tri[1] = poly->v2->position;
		tri[2] = poly->v3->position;
		
		vector3 edge1 = tri[1] - tri[0];
		vector3 edge2 = tri[2] - tri[0];
		
		vector3 pvec = to ^ edge2;
		
		float det = edge1 % pvec;
		
		if ( det < EPSILON )
			continue;		// behind
		
		vector3 tvec = origin - tri[0];
		
		u = tvec % pvec;
		
		if ( u < 0.0f || u > det )
		{
			continue;
		}
		
		vector3 qvec = tvec ^ edge1;
		
		v = to % qvec;
		
		if ( v < 0.0f || u + v > det )
		{
			continue;
		}
		
		return poly;
	}

	return NULL;
}

bool	Geometry::GetElevationFast ( CSIBCVector3D in_vPosition, float& out_value, CSIBCVector3D *out_Normal, float* out_Friction )
{
	vector3 origin = vector3(in_vPosition.m_fX,in_vPosition.m_fY,in_vPosition.m_fZ);
	vector3 to = vector3 ( 0.0f, -1.0f, 0.0f);

	Sector* in_pContainer = NULL;
	bool found = false;

	if ( out_Friction )
		*out_Friction = 0.0f;

	for (int s=0;s<m_Sectors.GetUsed();s++)
	{
		Sector* sector = &m_Sectors[s];

		if ( (in_vPosition.m_fX > ( sector->m_vCenter.m_fX - sector->m_vExtent.m_fX )) &&
			(in_vPosition.m_fX < ( sector->m_vCenter.m_fX + sector->m_vExtent.m_fX ))&&
			(in_vPosition.m_fZ > ( sector->m_vCenter.m_fZ - sector->m_vExtent.m_fZ ))&&
			(in_vPosition.m_fZ < ( sector->m_vCenter.m_fZ + sector->m_vExtent.m_fZ )))
		{
			in_pContainer = sector;
			break;
		}
	}


	if ( in_pContainer )
	{
		for (int p=0;p<in_pContainer->m_vPolys.GetUsed();p++)
		{
			SinglePolygon*	poly = in_pContainer->m_vPolys[p];
			float t,u,v;

			vector3 tri[3];
			tri[0] = poly->v1->position;
			tri[1] = poly->v2->position;
			tri[2] = poly->v3->position;

			vector3 edge1 = tri[1] - tri[0];
			vector3 edge2 = tri[2] - tri[0];

			vector3 pvec = to ^ edge2;

			float det = edge1 % pvec;

			if ( det < EPSILON )
				continue;		// behind

			vector3 tvec = origin - tri[0];

			u = tvec % pvec;

			if ( u < 0.0f || u > det )
			{
				continue;
			}

			vector3 qvec = tvec ^ edge1;

			v = to % qvec;

			if ( v < 0.0f || u + v > det )
			{
				continue;
			}

			t = edge2 % qvec;

			float inv_det = 1.0f / det;

			found = true;

			// collision
			t *= inv_det;
			u *= inv_det;
			v *= inv_det;

			//
			// calculate player elevation
			//

			CSIBCVector3D sv;
			CSIBCVector3D temp;
			CSIBCVector3D i;
			float d1, d2, scale;

			float fy = poly->v1->position.y;
			float fx = origin.x;
			float fz = origin.z;

			sv.m_fX = origin.x;
			sv.m_fY = fy + 2.0f;
			sv.m_fZ = origin.z;

			temp.m_fX = sv.m_fX - poly->v1->position.x;
			temp.m_fY = sv.m_fY - poly->v1->position.y;
			temp.m_fZ = sv.m_fZ - poly->v1->position.z;

			CSIBCVector3D normal;
			normal.m_fX = poly->m_vNormal.x;
			normal.m_fY = poly->m_vNormal.y;
			normal.m_fZ = poly->m_vNormal.z;

			if ( out_Normal )
			{
				out_Normal->m_fX = poly->m_vNormal.x;
				out_Normal->m_fY = poly->m_vNormal.y;
				out_Normal->m_fZ = poly->m_vNormal.z;
			}

			if ( out_Friction )
			{
				float f = poly->v1->friction + poly->v2->friction + poly->v3->friction;
				f /= 3.0f;
				*out_Friction = f;
			}


			d1 = (temp.m_fX * normal.m_fX) + (temp.m_fY * normal.m_fY) + (temp.m_fZ * normal.m_fZ);

			if (d1==0.0f)
			{
				i.m_fX = sv.m_fX;
				i.m_fY = sv.m_fY;
				i.m_fZ = sv.m_fZ;

			}	else {

				temp.m_fX = sv.m_fX - fx;
				temp.m_fY = sv.m_fY - fy;
				temp.m_fZ = sv.m_fZ - fz;


				d2 = (temp.m_fX * normal.m_fX) + (temp.m_fY * normal.m_fY) + (temp.m_fZ * normal.m_fZ);

				scale = d1/d2;

				i.m_fX = sv.m_fX - (temp.m_fX * scale);
				i.m_fY = sv.m_fY - (temp.m_fY * scale);
				i.m_fZ = sv.m_fZ - (temp.m_fZ * scale);

				//float l_fDistance = fabs ( i.m_fY - fy );
			}

			out_value = i.m_fY;
			return true;
		}
	}
	
		if ( !found )
		{

			for (int p=0;p<m_Polygons.GetUsed();p++)
			{
				SinglePolygon*	poly = &m_Polygons[p];
				float t,u,v;

				vector3 tri[3];
				tri[0] = poly->v1->position;
				tri[1] = poly->v2->position;
				tri[2] = poly->v3->position;

				vector3 edge1 = tri[1] - tri[0];
				vector3 edge2 = tri[2] - tri[0];

				vector3 pvec = to ^ edge2;

				float det = edge1 % pvec;

				if ( det < EPSILON )
					continue;		// behind

				vector3 tvec = origin - tri[0];

				u = tvec % pvec;

				if ( u < 0.0f || u > det )
				{
					continue;
				}

				vector3 qvec = tvec ^ edge1;

				v = to % qvec;

				if ( v < 0.0f || u + v > det )
				{
					continue;
				}

				t = edge2 % qvec;

				float inv_det = 1.0f / det;

				found = true;

				// collision
				t *= inv_det;
				u *= inv_det;
				v *= inv_det;

				//
				// calculate player elevation
				//

				CSIBCVector3D sv;
				CSIBCVector3D temp;
				CSIBCVector3D i;
				float d1, d2, scale;

				float fy = poly->v1->position.y;
				float fx = origin.x;
				float fz = origin.z;

				sv.m_fX = origin.x;
				sv.m_fY = fy + 2.0f;
				sv.m_fZ = origin.z;

				temp.m_fX = sv.m_fX - poly->v1->position.x;
				temp.m_fY = sv.m_fY - poly->v1->position.y;
				temp.m_fZ = sv.m_fZ - poly->v1->position.z;

				CSIBCVector3D normal;
				normal.m_fX = poly->m_vNormal.x;
				normal.m_fY = poly->m_vNormal.y;
				normal.m_fZ = poly->m_vNormal.z;

				if ( out_Normal )
				{
					out_Normal->m_fX = poly->m_vNormal.x;
					out_Normal->m_fY = poly->m_vNormal.y;
					out_Normal->m_fZ = poly->m_vNormal.z;
				}

				if ( out_Friction )
				{
					float f = poly->v1->friction + poly->v2->friction + poly->v3->friction;
					f /= 3.0f;
					*out_Friction = f;
				}


				d1 = (temp.m_fX * normal.m_fX) + (temp.m_fY * normal.m_fY) + (temp.m_fZ * normal.m_fZ);

				if (d1==0.0f)
				{
					i.m_fX = sv.m_fX;
					i.m_fY = sv.m_fY;
					i.m_fZ = sv.m_fZ;

				}	else {

					temp.m_fX = sv.m_fX - fx;
					temp.m_fY = sv.m_fY - fy;
					temp.m_fZ = sv.m_fZ - fz;


					d2 = (temp.m_fX * normal.m_fX) + (temp.m_fY * normal.m_fY) + (temp.m_fZ * normal.m_fZ);

					scale = d1/d2;

					i.m_fX = sv.m_fX - (temp.m_fX * scale);
					i.m_fY = sv.m_fY - (temp.m_fY * scale);
					i.m_fZ = sv.m_fZ - (temp.m_fZ * scale);

					//float l_fDistance = fabs ( i.m_fY - fy );
				}

				out_value = i.m_fY;
				return true;
			}
		}


	return false;
}

void	Geometry::Sectorize()
{
	m_Sectors.DisposeData ();

	//
	// find level extents
	//

	float minx = 10000.0f;
	float maxx = -10000.0f;
	float minz = 10000.0f;
	float maxz = -10000.0f;
	float miny = 10000.0f;
	float maxy = -10000.0f;

	for (int v=0;v<m_Vertices.GetUsed();v++)
	{
		if ( m_Vertices[v].position.x > maxx )
			maxx = m_Vertices[v].position.x;

		if ( m_Vertices[v].position.z > maxz )
			maxz = m_Vertices[v].position.z;

		if ( m_Vertices[v].position.x < minx )
			minx = m_Vertices[v].position.x;

		if ( m_Vertices[v].position.z < minz )
			minz = m_Vertices[v].position.z;

		if ( m_Vertices[v].position.y > maxy )
			maxy = m_Vertices[v].position.y;

		if ( m_Vertices[v].position.y < miny )
			miny = m_Vertices[v].position.y;
	}

	float	sizeX = maxx - minx;
	float	sizeZ = maxz - minz;

#define CELL_SIZE 16.0f

	float numX = sizeX / CELL_SIZE;
	float numZ = sizeZ / CELL_SIZE;

	for (int h=0;h<(int)CELL_SIZE;h++)
	{
		for (int v=0;v<(int)CELL_SIZE;v++)
		{
			m_Sectors.Extend(1);
			Sector* sector = &m_Sectors[m_Sectors.GetUsed()-1];

			sector->m_vCenter.m_fX = minx + ( h * numX );
			sector->m_vCenter.m_fZ = minz + ( v * numZ );
			sector->m_vCenter.m_fY = ( (maxy - miny) / 2.0f) + miny ;

			sector->m_vExtent.m_fX = numX / 2;
			sector->m_vExtent.m_fZ = numZ / 2;
			sector->m_vExtent.m_fY = 0.0f;	// hack for now
		}
	}

	LONG p;
	for (p=0;p<m_Polygons.GetUsed();p++)
	{
		SinglePolygon * poly = &m_Polygons[p];

		if ( poly->m_bSectorized )
			continue;

		CSIBCVector3D centroid;
		centroid.m_fX = poly->v1->position.x + poly->v2->position.x + poly->v3->position.x;
		centroid.m_fY = poly->v1->position.y + poly->v2->position.y + poly->v3->position.y;
		centroid.m_fZ = poly->v1->position.z + poly->v2->position.z + poly->v3->position.z;
		centroid.Scale(1.0f / 3.0f);

		for (int s=0;s<m_Sectors.GetUsed();s++)
		{
			Sector *sector = &m_Sectors[s];

			if ( (centroid.m_fX > ( sector->m_vCenter.m_fX - sector->m_vExtent.m_fX )) &&
				(centroid.m_fX < ( sector->m_vCenter.m_fX + sector->m_vExtent.m_fX ))&&
				(centroid.m_fZ > ( sector->m_vCenter.m_fZ - sector->m_vExtent.m_fZ ))&&
				(centroid.m_fZ < ( sector->m_vCenter.m_fZ + sector->m_vExtent.m_fZ )))
			{
				sector->m_vPolys.Add ( poly );
/*
				if ( centroid.m_fY > ( sector->m_vExtent.m_fY + sector->m_vCenter.m_fY))
				{
					sector->m_vExtent.m_fY = centroid.m_fY - sector->m_vCenter.m_fY;
				} else {
					if ( centroid.m_fY < ( sector->m_vCenter.m_fY - sector->m_vExtent.m_fY))
					{
						sector->m_vExtent.m_fY = sector->m_vCenter.m_fY - centroid.m_fY;
					}
				}
*/
				poly->m_bSectorized = true;
				break;
			}

		}
	}

	for (int s=0;s<m_Sectors.GetUsed();s++)
	{
		Sector *sector = &m_Sectors[s];
		float miny = 10000.0f;
		float maxy = -10000.0f;
		for (int p=0;p<sector->m_vPolys.GetUsed();p++)
		{
			SinglePolygon *poly = sector->m_vPolys[p];
			if ( poly->v1->position.y > maxy )
				maxy = poly->v1->position.y;
			if ( poly->v1->position.y < miny )
				miny = poly->v1->position.y;
			if ( poly->v2->position.y > maxy )
				maxy = poly->v2->position.y;
			if ( poly->v2->position.y < miny )
				miny = poly->v2->position.y;
			if ( poly->v3->position.y > maxy )
				maxy = poly->v3->position.y;
			if ( poly->v3->position.y < miny )
				miny = poly->v3->position.y;
		}

		sector->m_vCenter.m_fY = ((maxy - miny) / 2.0) + miny;
		sector->m_vExtent.m_fY = ((maxy - miny) / 2.0);
	}

	//
	// last pass to add polygons that fall on the boundaries of sectors
	//

	for (p=0;p<m_Polygons.GetUsed();p++)
	{
		SinglePolygon * poly = &m_Polygons[p];

		if ( poly->m_bSectorized )
			continue;

		CSIBCVector3D centroid;
		centroid.m_fX = poly->v1->position.x + poly->v2->position.x + poly->v3->position.x;
		centroid.m_fY = poly->v1->position.y + poly->v2->position.y + poly->v3->position.y;
		centroid.m_fZ = poly->v1->position.z + poly->v2->position.z + poly->v3->position.z;
		centroid.Scale(1.0f / 3.0f);

		float distance = 99999.0f;	// some big number
		Sector *l_pClosest = NULL;
		for (int s=0;s<m_Sectors.GetUsed();s++)
		{
			Sector *sector = &m_Sectors[s];

			float ad = sector->m_vCenter.GetDistanceFrom ( centroid);
			if ( ad < distance )
			{
				l_pClosest = sector;
				distance = ad;
			}

		}

		assert ( l_pClosest != NULL );
		l_pClosest->m_vPolys.Add ( poly );
		poly->m_bSectorized = true;
	}

}


bool	Geometry::BuildIntersectionList ( float fx, float fy, float fz,
										float tx, float ty, float tz,
										CSIBCArray<SinglePolygon*>& out_pIntersectionList)
{
//DEBUG
	//FindPath ( CSIBCVector3D(0.0f, 0.0f, 0.0f), CSIBCVector3D(fx,fy,fz),&path);


	m_fLastElevation = -9999.0f;
	bool l_bFoundPoly = false;

	out_pIntersectionList.DisposeData();

	vector3 origin = vector3(fx,fy,fz);
	vector3 to = vector3(tx,ty,tz);

	bool	AllVisited = true;
	//bool	AllVisited = false;

	float l_fCurrentDistance = 9999.0f;

	Sector* in_pContainer = NULL;

	for (int s=0;s<m_Sectors.GetUsed();s++)
	{
		Sector* sector = &m_Sectors[s];

		if ( (origin.x > ( sector->m_vCenter.m_fX - sector->m_vExtent.m_fX )) &&
			(origin.x < ( sector->m_vCenter.m_fX + sector->m_vExtent.m_fX ))&&
			(origin.z > ( sector->m_vCenter.m_fZ - sector->m_vExtent.m_fZ ))&&
			(origin.z < ( sector->m_vCenter.m_fZ + sector->m_vExtent.m_fZ )))
		{
			in_pContainer = sector;
			break;
		}
	}

	if ( in_pContainer )
	{
		for (int p=0;p<in_pContainer->m_vPolys.GetUsed();p++)
		{
			SinglePolygon*	poly = in_pContainer->m_vPolys[p];
			float t,u,v;

			//	if (!poly->m_bWalkable)
			//		continue;

			if ( (poly->m_bWalkable) && (poly->m_bVisited == false) )
				AllVisited = false;

			vector3 tri[3];
			tri[0] = poly->v1->position;
			tri[1] = poly->v2->position;
			tri[2] = poly->v3->position;

			vector3 edge1 = tri[1] - tri[0];
			vector3 edge2 = tri[2] - tri[0];

			vector3 pvec = to ^ edge2;

			float det = edge1 % pvec;

			if ( det < EPSILON )
				continue;		// behind

			vector3 tvec = origin - tri[0];

			u = tvec % pvec;

			if ( u < 0.0f || u > det )
			{
				continue;
			}

			vector3 qvec = tvec ^ edge1;

			v = to % qvec;

			if ( v < 0.0f || u + v > det )
			{
				continue;
			}

			t = edge2 % qvec;

			float inv_det = 1.0f / det;

			// collision
			t *= inv_det;
			u *= inv_det;
			v *= inv_det;

			l_bFoundPoly = true;

			//
			// calculate player elevation
			//

			CSIBCVector3D sv;
			CSIBCVector3D temp;
			CSIBCVector3D i;
			float d1, d2, scale;

			fy = poly->v1->position.y;

			sv.m_fX = fx;
			sv.m_fY = fy + 2.0f;
			sv.m_fZ = fz;

			temp.m_fX = sv.m_fX - poly->v1->position.x;
			temp.m_fY = sv.m_fY - poly->v1->position.y;
			temp.m_fZ = sv.m_fZ - poly->v1->position.z;

			//
			// average the normal from the 3 points

			CSIBCVector3D normal;
			normal.m_fX += poly->v1->normal.x;
			normal.m_fY += poly->v1->normal.y;
			normal.m_fZ += poly->v1->normal.z;
			normal.m_fX += poly->v2->normal.x;
			normal.m_fY += poly->v2->normal.y;
			normal.m_fZ += poly->v2->normal.z;
			normal.m_fX += poly->v3->normal.x;
			normal.m_fY += poly->v3->normal.y;
			normal.m_fZ += poly->v3->normal.z;

			normal.m_fX /= 3.0f;
			normal.m_fY /= 3.0f;
			normal.m_fZ /= 3.0f;

			normal.m_fX = poly->m_vNormal.x;
			normal.m_fY = poly->m_vNormal.y;
			normal.m_fZ = poly->m_vNormal.z;

			//	normal.m_fX = 0.0f;
			//	normal.m_fY = 1.0f;
			//	normal.m_fZ = 0.0f;

			d1 = (temp.m_fX * normal.m_fX) + (temp.m_fY * normal.m_fY) + (temp.m_fZ * normal.m_fZ);

			if (d1==0.0f)
			{
				i.m_fX = sv.m_fX;
				i.m_fY = sv.m_fY;
				i.m_fZ = sv.m_fZ;

			}	else {

				temp.m_fX = sv.m_fX - fx;
				temp.m_fY = sv.m_fY - fy;
				temp.m_fZ = sv.m_fZ - fz;


				d2 = (temp.m_fX * normal.m_fX) + (temp.m_fY * normal.m_fY) + (temp.m_fZ * normal.m_fZ);

				scale = d1/d2;

				i.m_fX = sv.m_fX - (temp.m_fX * scale);
				i.m_fY = sv.m_fY - (temp.m_fY * scale);
				i.m_fZ = sv.m_fZ - (temp.m_fZ * scale);

				float l_fDistance = fabs ( i.m_fY - fy );

				if ( l_fDistance < l_fCurrentDistance )
				{
					m_fLastElevation = i.m_fY;
					l_fCurrentDistance = l_fDistance;
				}
			}

			if ( !poly->m_bVisited )
			{
				if ( poly->m_bWalkable )
				{
					out_pIntersectionList.Extend(1);
					out_pIntersectionList[out_pIntersectionList.GetUsed()-1] = poly;
					poly->r = 0.1f;
					poly->g = 0.1f;
					poly->b = 0.1f;
					poly->m_bVisited = true;

					for (int a=0;a<poly->m_pAdjacent.GetUsed();a++)
					{
						poly->m_pAdjacent[a]->r = 0.1f;
						poly->m_pAdjacent[a]->g = 0.1f;
						poly->m_pAdjacent[a]->b = 0.1f;
						poly->m_pAdjacent[a]->m_bVisited = true;
					}
				}

			}


		}
	}


	if ( !l_bFoundPoly )
	{
		for (int p=0;p<m_Polygons.GetUsed();p++)
		{
			SinglePolygon*	poly = &m_Polygons[p];
			float t,u,v;

			//	if (!poly->m_bWalkable)
			//		continue;

			if ( (poly->m_bWalkable) && (poly->m_bVisited == false) )
				AllVisited = false;

			vector3 tri[3];
			tri[0] = poly->v1->position;
			tri[1] = poly->v2->position;
			tri[2] = poly->v3->position;

			vector3 edge1 = tri[1] - tri[0];
			vector3 edge2 = tri[2] - tri[0];

			vector3 pvec = to ^ edge2;

			float det = edge1 % pvec;

			if ( det < EPSILON )
				continue;		// behind

			vector3 tvec = origin - tri[0];

			u = tvec % pvec;

			if ( u < 0.0f || u > det )
			{
				continue;
			}

			vector3 qvec = tvec ^ edge1;

			v = to % qvec;

			if ( v < 0.0f || u + v > det )
			{
				continue;
			}

			t = edge2 % qvec;

			float inv_det = 1.0f / det;

			// collision
			t *= inv_det;
			u *= inv_det;
			v *= inv_det;

			//
			// calculate player elevation
			//

			CSIBCVector3D sv;
			CSIBCVector3D temp;
			CSIBCVector3D i;
			float d1, d2, scale;

			fy = poly->v1->position.y;

			sv.m_fX = fx;
			sv.m_fY = fy + 2.0f;
			sv.m_fZ = fz;

			temp.m_fX = sv.m_fX - poly->v1->position.x;
			temp.m_fY = sv.m_fY - poly->v1->position.y;
			temp.m_fZ = sv.m_fZ - poly->v1->position.z;

			//
			// average the normal from the 3 points

			CSIBCVector3D normal;
			normal.m_fX += poly->v1->normal.x;
			normal.m_fY += poly->v1->normal.y;
			normal.m_fZ += poly->v1->normal.z;
			normal.m_fX += poly->v2->normal.x;
			normal.m_fY += poly->v2->normal.y;
			normal.m_fZ += poly->v2->normal.z;
			normal.m_fX += poly->v3->normal.x;
			normal.m_fY += poly->v3->normal.y;
			normal.m_fZ += poly->v3->normal.z;

			normal.m_fX /= 3.0f;
			normal.m_fY /= 3.0f;
			normal.m_fZ /= 3.0f;

			normal.m_fX = poly->m_vNormal.x;
			normal.m_fY = poly->m_vNormal.y;
			normal.m_fZ = poly->m_vNormal.z;

			//	normal.m_fX = 0.0f;
			//	normal.m_fY = 1.0f;
			//	normal.m_fZ = 0.0f;

			d1 = (temp.m_fX * normal.m_fX) + (temp.m_fY * normal.m_fY) + (temp.m_fZ * normal.m_fZ);

			if (d1==0.0f)
			{
				i.m_fX = sv.m_fX;
				i.m_fY = sv.m_fY;
				i.m_fZ = sv.m_fZ;

			}	else {

				temp.m_fX = sv.m_fX - fx;
				temp.m_fY = sv.m_fY - fy;
				temp.m_fZ = sv.m_fZ - fz;


				d2 = (temp.m_fX * normal.m_fX) + (temp.m_fY * normal.m_fY) + (temp.m_fZ * normal.m_fZ);

				scale = d1/d2;

				i.m_fX = sv.m_fX - (temp.m_fX * scale);
				i.m_fY = sv.m_fY - (temp.m_fY * scale);
				i.m_fZ = sv.m_fZ - (temp.m_fZ * scale);

				float l_fDistance = fabs ( i.m_fY - fy );

				if ( l_fDistance < l_fCurrentDistance )
				{
					m_fLastElevation = i.m_fY;
					l_fCurrentDistance = l_fDistance;
				}
			}

			if ( !poly->m_bVisited )
			{
				if ( poly->m_bWalkable )
				{
					out_pIntersectionList.Extend(1);
					out_pIntersectionList[out_pIntersectionList.GetUsed()-1] = poly;
					poly->r = 0.1f;
					poly->g = 0.1f;
					poly->b = 0.1f;
					poly->m_bVisited = true;

					for (int a=0;a<poly->m_pAdjacent.GetUsed();a++)
					{
						poly->m_pAdjacent[a]->r = 0.1f;
						poly->m_pAdjacent[a]->g = 0.1f;
						poly->m_pAdjacent[a]->b = 0.1f;
						poly->m_pAdjacent[a]->m_bVisited = true;
					}
				}

			}


		}
	}

	for (int a=0;a<m_Polygons.GetUsed();a++)
	{
		SinglePolygon*	poly = &m_Polygons[a];
		if ( (poly->m_bWalkable) && (poly->m_bVisited == false) )
				AllVisited = false;
	}

return AllVisited;
}

void MultMatrix ( CSIBCMatrix4x4& in_mat, CSIBCVector3D& src, CSIBCVector3D& dst )
{

	float w = (
		src.GetX() * in_mat.Get(3,0) +
		src.GetY() * in_mat.Get(3,1) +
		src.GetZ() * in_mat.Get(3,2) +
		in_mat.Get(3,3)          );


	dst.m_fX  = (
		src.GetX() * in_mat.Get(0,0) +
		src.GetY() * in_mat.Get(0,1) + 
		src.GetZ() * in_mat.Get(0,2) + 
		in_mat.Get(0,3)          ) / w;
	dst.m_fY  = (
		src.GetX() * in_mat.Get(1,0) +
		src.GetY() * in_mat.Get(1,1) +
		src.GetZ() * in_mat.Get(1,2) +
		in_mat.Get(1,3)          ) / w;
	dst.m_fZ  = (
		src.GetX() * in_mat.Get(2,0) +
		src.GetY() * in_mat.Get(2,1) +
		src.GetZ() * in_mat.Get(2,2) +
		in_mat.Get(2,3)          ) / w;
	
	
}
