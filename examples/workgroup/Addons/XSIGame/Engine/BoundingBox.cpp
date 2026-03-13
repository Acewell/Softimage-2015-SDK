// BoundingBox.cpp: implementation of the BoundingBox class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BoundingBox.h"

int triBoxOverlap(float boxcenter[3],float boxhalfsize[3],float triverts[3][3]);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BoundingBox::BoundingBox()
: m_bInitialized ( false )
, m_bTransformed ( false )
{

}

BoundingBox::~BoundingBox()
{

}

void	BoundingBox::Reset ()
{
	m_bInitialized = false;
	m_bTransformed = false;

}

void	BoundingBox::Grow ( CSIBCVector3D in_vVector )
{

	if ( !m_bInitialized )
	{
		m_vMin = CSIBCVector3D ( 10000.0f, 10000.0f, 10000.0f);
		m_vMax = CSIBCVector3D ( -10000.0f, -10000.0f, -10000.0f);

		
		m_bInitialized = true;
		
	}

	if ( in_vVector.m_fX > m_vMax.m_fX )
		m_vMax.m_fX  = in_vVector.m_fX;

	if ( in_vVector.m_fY > m_vMax.m_fY )
		m_vMax.m_fY  = in_vVector.m_fY;

	if ( in_vVector.m_fZ > m_vMax.m_fZ )
		m_vMax.m_fZ  = in_vVector.m_fZ;

	if ( in_vVector.m_fX < m_vMin.m_fX )
		m_vMin.m_fX  = in_vVector.m_fX;

	if ( in_vVector.m_fY < m_vMin.m_fY )
		m_vMin.m_fY  = in_vVector.m_fY;

	if ( in_vVector.m_fZ < m_vMin.m_fZ )
		m_vMin.m_fZ  = in_vVector.m_fZ;

	m_vCenter = m_vMax - m_vMin;
	m_vCenter.Scale ( 0.5f );
	m_vExtent = m_vCenter;
	m_vCenter.Add ( m_vMin );

	m_vPoints[0].m_fX = m_vCenter.m_fX - m_vExtent.m_fX;
	m_vPoints[0].m_fY = m_vCenter.m_fY - m_vExtent.m_fY;
	m_vPoints[0].m_fZ = m_vCenter.m_fZ - m_vExtent.m_fZ;
	
	m_vPoints[1].m_fX = m_vCenter.m_fX - m_vExtent.m_fX;
	m_vPoints[1].m_fY = m_vCenter.m_fY - m_vExtent.m_fY;
	m_vPoints[1].m_fZ = m_vCenter.m_fZ + m_vExtent.m_fZ;
	
	m_vPoints[2].m_fX = m_vCenter.m_fX - m_vExtent.m_fX;
	m_vPoints[2].m_fY = m_vCenter.m_fY + m_vExtent.m_fY;
	m_vPoints[2].m_fZ = m_vCenter.m_fZ + m_vExtent.m_fZ;
	
	m_vPoints[3].m_fX = m_vCenter.m_fX + m_vExtent.m_fX;
	m_vPoints[3].m_fY = m_vCenter.m_fY - m_vExtent.m_fY;
	m_vPoints[3].m_fZ = m_vCenter.m_fZ - m_vExtent.m_fZ;
	
	m_vPoints[4].m_fX = m_vCenter.m_fX + m_vExtent.m_fX;
	m_vPoints[4].m_fY = m_vCenter.m_fY + m_vExtent.m_fY;
	m_vPoints[4].m_fZ = m_vCenter.m_fZ - m_vExtent.m_fZ;
	
	
	m_vPoints[5].m_fX = m_vCenter.m_fX + m_vExtent.m_fX;
	m_vPoints[5].m_fY = m_vCenter.m_fY + m_vExtent.m_fY;
	m_vPoints[5].m_fZ = m_vCenter.m_fZ + m_vExtent.m_fZ;
	
	m_vPoints[6].m_fX = m_vCenter.m_fX + m_vExtent.m_fX;
	m_vPoints[6].m_fY = m_vCenter.m_fY - m_vExtent.m_fY;
	m_vPoints[6].m_fZ = m_vCenter.m_fZ + m_vExtent.m_fZ;
	
	m_vPoints[7].m_fX = m_vCenter.m_fX - m_vExtent.m_fX;
	m_vPoints[7].m_fY = m_vCenter.m_fY + m_vExtent.m_fY;
	m_vPoints[7].m_fZ = m_vCenter.m_fZ - m_vExtent.m_fZ;
}

void	BoundingBox::Transform()
{
	DEBUGENTRY ( "BoundingBox::Transform");

	//
	// transform bbox
	//
	
	m_pTransform->ComputeLocalMatrix();
	m_pTransform->ComputeGlobalMatrix();
	
	CSIBCMatrix4x4& mat = m_pTransform->GetGlobalMatrix();
	
	if ( !m_mOffset.IsIdentity() )
	{
		mat = m_mOffset;
	}

	mat.Multiply ( m_vMaxX, m_vMax );
	mat.Multiply ( m_vMinX, m_vMin );

	for (int v=0;v<8;v++)
		mat.Multiply (bc[v], m_vPoints[v]);

	m_vMaxX = CSIBCVector3D (-10000.0f, -10000.0f, -10000.0f);
	m_vMinX = CSIBCVector3D (10000.0f, 10000.0f, 10000.0f);
	for (int b=0;b<8;b++)
	{
	if ( bc[b].m_fX > m_vMaxX.m_fX )
		m_vMaxX.m_fX  = bc[b].m_fX;

	if ( bc[b].m_fY > m_vMaxX.m_fY )
		m_vMaxX.m_fY  = bc[b].m_fY;

	if ( bc[b].m_fZ > m_vMaxX.m_fZ )
		m_vMaxX.m_fZ  = bc[b].m_fZ;

	if ( bc[b].m_fX < m_vMinX.m_fX )
		m_vMinX.m_fX  = bc[b].m_fX;

	if ( bc[b].m_fY < m_vMinX.m_fY )
		m_vMinX.m_fY  = bc[b].m_fY;

	if ( bc[b].m_fZ < m_vMinX.m_fZ )
		m_vMinX.m_fZ  = bc[b].m_fZ;
	}

	m_vCenter = m_vMaxX - m_vMinX;
	m_vCenter.Scale ( 0.5f );
	m_vExtent = m_vCenter;
	m_vCenter.Add ( m_vMinX );

	m_bTransformed = true;


}
void	BoundingBox::GetXFormAABB ( CSIBCVector3D& out_vMax, CSIBCVector3D& out_vMin )
{

	out_vMax = m_vMaxX;
	out_vMin = m_vMinX;

}

bool	BoundingBox::TestCollision ( BoundingBox* in_pBox, CSIBCVector3D& out_vCollision )
{
	DEBUGENTRY ( "BoundingBox::TestCollision");

	if ( !in_pBox->m_bTransformed )
		return false;

	CSIBCVector3D T = in_pBox->GetCenter () - m_vCenter;
	
	CSIBCVector3D l_vExtent = in_pBox->GetExtent();

	bool result = 
		fabs(T.m_fX) <= fabs(l_vExtent.m_fX + m_vExtent.m_fX) &&
		fabs(T.m_fY) <= fabs(l_vExtent.m_fY + m_vExtent.m_fY) &&
		fabs(T.m_fZ) <= fabs(l_vExtent.m_fZ + m_vExtent.m_fZ);
	
	if ( result )
	{	
		out_vCollision.m_fX = fabs(T.m_fX) - (l_vExtent.m_fX + m_vExtent.m_fX);
		out_vCollision.m_fY = fabs(T.m_fY) - (l_vExtent.m_fY + m_vExtent.m_fY);
		out_vCollision.m_fZ = fabs(T.m_fZ) - (l_vExtent.m_fZ + m_vExtent.m_fZ);
		
		
		//
		// Recuperate the sign of the collision (lost by the use of the fabs above)
		//
		
		out_vCollision.m_fX *= ( T.m_fX > 0.0f ? 1.0f : -1.0f );
		out_vCollision.m_fY *= ( T.m_fY > 0.0f ? 1.0f : -1.0f );
		out_vCollision.m_fZ *= ( T.m_fZ > 0.0f ? 1.0f : -1.0f );
		
		
		//return TestMeshCollision ( in_pBox );
		//return TestTightCollision ( in_pBox );
		return true;
	}
	
	return false;
}

bool	BoundingBox::TestMeshCollision ( BoundingBox* in_pBox )
{

	DEBUGENTRY ( "BoundingBox::TestMeshCollision");

	float boxCenter[3];
	float boxHalfsize[3];

	boxCenter[0] = in_pBox->GetCenter ().m_fX;
	boxCenter[1] = in_pBox->GetCenter ().m_fY;
	boxCenter[2] = in_pBox->GetCenter ().m_fZ;
	boxHalfsize[0] = in_pBox->GetExtent ().m_fX * 0.5f;
	boxHalfsize[1] = in_pBox->GetExtent ().m_fY * 0.5f;
	boxHalfsize[2] = in_pBox->GetExtent ().m_fZ * 0.5f;

	CSLTriangleList** l_pTriLists = m_pMesh->TriangleLists();
	for (int t=0;t<this->m_pMesh->GetTriangleListCount();t++)
	{
		for (int i=0;i<l_pTriLists[t]->GetTriangleCount();i++)
		{
			int t1 = l_pTriLists[t]->GetVertexIndicesPtr()[(i*3)];
			int t2 = l_pTriLists[t]->GetVertexIndicesPtr()[(i*3)+1];
			int t3 = l_pTriLists[t]->GetVertexIndicesPtr()[(i*3)+2];

			CSIBCVector3D triangle[3];

			

			triangle[0] = m_pMeshVertices[t1];
			triangle[1] = m_pMeshVertices[t2];
			triangle[2] = m_pMeshVertices[t3];

			float tri[3][3];
			tri[0][0] = triangle[0].m_fX;
			tri[0][1] = triangle[0].m_fY;
			tri[0][2] = triangle[0].m_fZ;

			tri[1][0] = triangle[1].m_fX;
			tri[1][1] = triangle[1].m_fY;
			tri[1][2] = triangle[1].m_fZ;

			tri[2][0] = triangle[2].m_fX;
			tri[2][1] = triangle[2].m_fY;
			tri[2][2] = triangle[2].m_fZ;

			if ( triBoxOverlap ( boxCenter, boxHalfsize, tri ) )
				return true;
		}

	}

	return false;
}

#define TEST_COLLIDE_VTX(a,b,c)\
	tri[0][0] = bc[a].m_fX;\
	tri[0][1] = bc[a].m_fY;\
	tri[0][2] = bc[a].m_fZ;\
	tri[1][0] = bc[b].m_fX;\
	tri[1][1] = bc[b].m_fY;\
	tri[1][2] = bc[b].m_fZ;\
	tri[2][0] = bc[c].m_fX;\
	tri[2][1] = bc[c].m_fY;\
	tri[2][2] = bc[c].m_fZ;\
	if ( triBoxOverlap ( boxCenter, boxHalfsize, tri ) ) return true;

bool	BoundingBox::TestTightCollision ( BoundingBox* in_pBox )
{
	DEBUGENTRY ( "BoundingBox::TestMeshCollision");

	float boxCenter[3];
	float boxHalfsize[3];

	boxCenter[0] = in_pBox->GetCenter ().m_fX;
	boxCenter[1] = in_pBox->GetCenter ().m_fY;
	boxCenter[2] = in_pBox->GetCenter ().m_fZ;
	boxHalfsize[0] = in_pBox->GetExtent ().m_fX * 0.5f;
	boxHalfsize[1] = in_pBox->GetExtent ().m_fY * 0.5f;
	boxHalfsize[2] = in_pBox->GetExtent ().m_fZ * 0.5f;

	int triI = 0;

	float tri[3][3];
	
	TEST_COLLIDE_VTX (0,1,3)
	TEST_COLLIDE_VTX (1,2,3)
	TEST_COLLIDE_VTX (7,0,3)
	TEST_COLLIDE_VTX (3,4,7)
	TEST_COLLIDE_VTX (6,7,4)
	TEST_COLLIDE_VTX (4,5,6)
	TEST_COLLIDE_VTX (1,6,5)
	TEST_COLLIDE_VTX (5,2,1)
	TEST_COLLIDE_VTX (4,3,2)
	TEST_COLLIDE_VTX (3,2,5)
	TEST_COLLIDE_VTX (6,7,0)
	TEST_COLLIDE_VTX (7,0,1)


	return false;

}
inline bool TestTriIntersection ( CSIBCVector3D tri[3], BoundingBox* in_pBox )
{

	float fMin0, fMax0, fMin1, fMax1;
    CSIBCVector3D kD, akE[3];

    // test direction of triangle normal
    akE[0] = tri[1] - tri[0];
    akE[1] = tri[2] - tri[0];
    kD = akE[0].CrossProduct(akE[1]);
    fMin0 = kD.GetDot(tri[0]);
    fMax0 = fMin0;
    //ProjectBox(kD,rkBox,fMin1,fMax1);
    //if ( fMax1 < fMin0 || fMax0 < fMin1 )
      //  return false;

	return false;

}

//
// The following code is by Tomas Akenine-Möller
// more info can be found here: http://www.cs.lth.se/home/Tomas_Akenine_Moller/
//

#include <math.h>
#include <stdio.h>
#define X 0
#define Y 1
#define Z 2

#define CROSS(dest,v1,v2) \
dest[0]=v1[1]*v2[2]-v1[2]*v2[1]; \
dest[1]=v1[2]*v2[0]-v1[0]*v2[2]; \
dest[2]=v1[0]*v2[1]-v1[1]*v2[0]; 

#define DOT(v1,v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2])

#define SUB(dest,v1,v2) \
dest[0]=v1[0]-v2[0]; \
dest[1]=v1[1]-v2[1]; \
dest[2]=v1[2]-v2[2]; 

#define FINDMINMAX(x0,x1,x2,min,max) \
min = max = x0;   \
if(x1<min) min=x1;\
if(x1>max) max=x1;\
if(x2<min) min=x2;\
if(x2>max) max=x2;

int planeBoxOverlap(float normal[3], float vert[3], float maxbox[3])	// -NJMP-
{
  int q;
  float vmin[3],vmax[3],v;
  for(q=X;q<=Z;q++)
  {
    v=vert[q];					// -NJMP-
    if(normal[q]>0.0f)
    {
      vmin[q]=-maxbox[q] - v;	// -NJMP-
      vmax[q]= maxbox[q] - v;	// -NJMP-
    }
    else
    {
      vmin[q]= maxbox[q] - v;	// -NJMP-
      vmax[q]=-maxbox[q] - v;	// -NJMP-
    }
  }
  if(DOT(normal,vmin)>0.0f) return 0;	// -NJMP-
  if(DOT(normal,vmax)>=0.0f) return 1;	// -NJMP-
  
  return 0;
}


/*======================== X-tests ========================*/
#define AXISTEST_X01(a, b, fa, fb)			   \
	p0 = a*v0[Y] - b*v0[Z];			       	   \
	p2 = a*v2[Y] - b*v2[Z];			       	   \
        if(p0<p2) {min=p0; max=p2;} else {min=p2; max=p0;} \
	rad = fa * boxhalfsize[Y] + fb * boxhalfsize[Z];   \
	if(min>rad || max<-rad) return 0;

#define AXISTEST_X2(a, b, fa, fb)			   \
	p0 = a*v0[Y] - b*v0[Z];			           \
	p1 = a*v1[Y] - b*v1[Z];			       	   \
        if(p0<p1) {min=p0; max=p1;} else {min=p1; max=p0;} \
	rad = fa * boxhalfsize[Y] + fb * boxhalfsize[Z];   \
	if(min>rad || max<-rad) return 0;

/*======================== Y-tests ========================*/
#define AXISTEST_Y02(a, b, fa, fb)			   \
	p0 = -a*v0[X] + b*v0[Z];		      	   \
	p2 = -a*v2[X] + b*v2[Z];	       	       	   \
        if(p0<p2) {min=p0; max=p2;} else {min=p2; max=p0;} \
	rad = fa * boxhalfsize[X] + fb * boxhalfsize[Z];   \
	if(min>rad || max<-rad) return 0;

#define AXISTEST_Y1(a, b, fa, fb)			   \
	p0 = -a*v0[X] + b*v0[Z];		      	   \
	p1 = -a*v1[X] + b*v1[Z];	     	       	   \
        if(p0<p1) {min=p0; max=p1;} else {min=p1; max=p0;} \
	rad = fa * boxhalfsize[X] + fb * boxhalfsize[Z];   \
	if(min>rad || max<-rad) return 0;

/*======================== Z-tests ========================*/

#define AXISTEST_Z12(a, b, fa, fb)			   \
	p1 = a*v1[X] - b*v1[Y];			           \
	p2 = a*v2[X] - b*v2[Y];			       	   \
        if(p2<p1) {min=p2; max=p1;} else {min=p1; max=p2;} \
	rad = fa * boxhalfsize[X] + fb * boxhalfsize[Y];   \
	if(min>rad || max<-rad) return 0;

#define AXISTEST_Z0(a, b, fa, fb)			   \
	p0 = a*v0[X] - b*v0[Y];				   \
	p1 = a*v1[X] - b*v1[Y];			           \
        if(p0<p1) {min=p0; max=p1;} else {min=p1; max=p0;} \
	rad = fa * boxhalfsize[X] + fb * boxhalfsize[Y];   \
	if(min>rad || max<-rad) return 0;

int triBoxOverlap(float boxcenter[3],float boxhalfsize[3],float triverts[3][3])
{

  /*    use separating axis theorem to test overlap between triangle and box */
  /*    need to test for overlap in these directions: */
  /*    1) the {x,y,z}-directions (actually, since we use the AABB of the triangle */
  /*       we do not even need to test these) */
  /*    2) normal of the triangle */
  /*    3) crossproduct(edge from tri, {x,y,z}-directin) */
  /*       this gives 3x3=9 more tests */
   float v0[3],v1[3],v2[3];
//   float axis[3];
   float min,max,p0,p1,p2,rad,fex,fey,fez;		// -NJMP- "d" local variable removed
   float normal[3],e0[3],e1[3],e2[3];

   /* This is the fastest branch on Sun */
   /* move everything so that the boxcenter is in (0,0,0) */
   SUB(v0,triverts[0],boxcenter);
   SUB(v1,triverts[1],boxcenter);
   SUB(v2,triverts[2],boxcenter);

   /* compute triangle edges */
   SUB(e0,v1,v0);      /* tri edge 0 */
   SUB(e1,v2,v1);      /* tri edge 1 */
   SUB(e2,v0,v2);      /* tri edge 2 */

   /* Bullet 3:  */
   /*  test the 9 tests first (this was faster) */
   fex = fabsf(e0[X]);
   fey = fabsf(e0[Y]);
   fez = fabsf(e0[Z]);
   AXISTEST_X01(e0[Z], e0[Y], fez, fey);
   AXISTEST_Y02(e0[Z], e0[X], fez, fex);
   AXISTEST_Z12(e0[Y], e0[X], fey, fex);

   fex = fabsf(e1[X]);
   fey = fabsf(e1[Y]);
   fez = fabsf(e1[Z]);
   AXISTEST_X01(e1[Z], e1[Y], fez, fey);
   AXISTEST_Y02(e1[Z], e1[X], fez, fex);
   AXISTEST_Z0(e1[Y], e1[X], fey, fex);

   fex = fabsf(e2[X]);
   fey = fabsf(e2[Y]);
   fez = fabsf(e2[Z]);
   AXISTEST_X2(e2[Z], e2[Y], fez, fey);
   AXISTEST_Y1(e2[Z], e2[X], fez, fex);
   AXISTEST_Z12(e2[Y], e2[X], fey, fex);

   /* Bullet 1: */
   /*  first test overlap in the {x,y,z}-directions */
   /*  find min, max of the triangle each direction, and test for overlap in */
   /*  that direction -- this is equivalent to testing a minimal AABB around */
   /*  the triangle against the AABB */

   /* test in X-direction */
   FINDMINMAX(v0[X],v1[X],v2[X],min,max);
   if(min>boxhalfsize[X] || max<-boxhalfsize[X]) return 0;

   /* test in Y-direction */
   FINDMINMAX(v0[Y],v1[Y],v2[Y],min,max);
   if(min>boxhalfsize[Y] || max<-boxhalfsize[Y]) return 0;

   /* test in Z-direction */
   FINDMINMAX(v0[Z],v1[Z],v2[Z],min,max);
   if(min>boxhalfsize[Z] || max<-boxhalfsize[Z]) return 0;

   /* Bullet 2: */
   /*  test if the box intersects the plane of the triangle */
   /*  compute plane equation of triangle: normal*x+d=0 */
   CROSS(normal,e0,e1);
   // -NJMP- (line removed here)
   if(!planeBoxOverlap(normal,v0,boxhalfsize)) return 0;	// -NJMP-

   return 1;   /* box and triangle overlaps */
}

