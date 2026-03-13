#ifdef _WIN32
#include <windows.h>
#endif

#include <gl/gl.h>

#include <string.h>
#include "Sky.h"
#include <SIBCMatrix.h>



skylayer ::skylayer()
{
}

skylayer::~skylayer()
{}

void skylayer::set ( Display* in_pDisplay,  char *texturename, CSIBCVector3D layer_speed)
{

	speed = layer_speed;

	//
	// load this layer's texture
	//
	texture = in_pDisplay->AddTexture ( texturename );
//	texture = get_texture_manager()->load_texture ( texturename, 0 );
}

void skylayer::render ()
{
	glEnable ( GL_TEXTURE_2D );
	glBindTexture ( GL_TEXTURE_2D, texture );

	//geo->render( 0 );

}

sky::sky(Display *in_pDisplay)
{
	layers = NULL;
	num_layers = 0;
	sky_detail = 3;

	//
	// fog variable
	//

	fog_start = 0.0f;
	fog_end = 1280.0f;
	fog_density = 0.006f;
	fog_color[0] = 0.4f;
	fog_color[1] = 0.6f;
	fog_color[2] = 0.9f;
	
	m_pDisplay = in_pDisplay;
}

sky::~sky()
{
	for (int t=0;t<layers.GetUsed();t++)
	{
		delete layers[t];
	}

	layers.DisposeData ();
}

//////////////////////////////////////////////////////////////////////////
// int create ( int layer_count, int detail_level, sk_video *video )
//
// Creates a new sky object and its geometry. 
//////////////////////////////////////////////////////////////////////////
int sky::create ( int layer_count, int detail_level, Display *in_pDisplay , CSIBCColorf fog)
{
	//
	// Adjust depending on user detail level
	//

	if ( sky_detail < 2 )
		layer_count = 1;

	if ( sky_detail <= 1 )
		detail_level = 1;

	for (int l=0;l<layer_count;l++)
	{
		layers.Add ( new skylayer );
	}

	num_layers = layer_count;

	complexity = detail_level;

	create_geometry();

	return 1;
}

int sky::add_layer ( char *filename, int in_iIdx, CSIBCVector3D speed)
{
	
	layers[in_iIdx]->set ( m_pDisplay, filename, speed);

	//
	//offset the texture just a little so that they dont overlap perfectly
	//
	layers[in_iIdx]->position.Add( speed.Scale ( 5.0f));


	return 1;
}

void sky::set_fog_color ( CSIBCColorf nc )
{
	fog_color[0] = nc.m_fR;
	fog_color[1] = nc.m_fG;
	fog_color[2] = nc.m_fB;
	
}

CSIBCColorf sky::get_fog_color ()
{
	CSIBCColorf ret;

	ret.m_fR = fog_color[0];
	ret.m_fG = fog_color[1];
	ret.m_fB = fog_color[2];

	return ret;
}

int sky::tick ( float delta_time )
{
	for (int l=0;l<num_layers;l++)
	{
		layers[l]->position.Add ( layers[l]->speed.Scale(delta_time));
	}
	
	return 1;
}


int sky::create_geometry ()
{
	//
	// create the surface
	//

	int n=4;	// complexity
	int m=4;

	int isize = (2*n+1)*m+4;
	
	index_list = new unsigned int [isize];

	num_tri = create_patch_indicies(m, n, index_list, isize);

	int vertex_step = 16;

	int mod = m + 1;

	vertex_list = new SkyVertex[ mod * mod ];

	for(int i=0; i< mod * mod; i++) 
	{        
		float fx, fy, fz;
        fx=(float) (i%mod) * vertex_step ;
        fz=(float) (i/mod) * vertex_step ;
        fy=(float) (2.0f);

		vertex_list[i].x = fx;
		vertex_list[i].z = fz;
		vertex_list[i].y = fy;

		vertex_list[i].nx = 0.0f;
		vertex_list[i].nz = 0.0f;
		vertex_list[i].ny = 1.0f;

		vertex_list[i].tu = fx / ( (mod-1) * vertex_step );
		vertex_list[i].tv = fz / ( (mod-1) * vertex_step );

	}

	num_vertex = mod * mod;

	vertex_stride = (LONG)&vertex_list[1].x;
	vertex_stride -= (LONG)&vertex_list[0].x;

	uv_stride = (LONG)&vertex_list[1].tu;
	uv_stride -= (LONG)&vertex_list[0].tu;

	//
	// set defaulyt tilling to 4
	// FIXME: this member should be part of the "forecast" parameter
	//

	set_tilling ( 2 );

	//
	// translate the center to 0
	//

	SkyVertex minimum, maximum;

	minimum.x = maximum.x = vertex_list[0].x;
	minimum.y = maximum.y = vertex_list[0].y;
	minimum.z = maximum.z = vertex_list[0].z;
	
	for (int n=0;n<num_vertex;n++)
	{
		if ( vertex_list[n].x < minimum.x )
			minimum.x = vertex_list[n].x;

		if ( vertex_list[n].y < minimum.y )
			minimum.y = vertex_list[n].y;

		if ( vertex_list[n].z < minimum.z )
			minimum.z = vertex_list[n].z;

		if ( vertex_list[n].x > maximum.x )
			maximum.x = vertex_list[n].x;

		if ( vertex_list[n].y > maximum.y )
			maximum.y = vertex_list[n].y;

		if ( vertex_list[n].z > maximum.z )
			maximum.z = vertex_list[n].z;
	}

	SkyVertex offset;
	offset.x = (( (maximum.x - minimum.x) / 2.0f ) + minimum.x ) * -1.0f;
	offset.y = (( (maximum.y - minimum.y) / 2.0f ) + minimum.y ) * -1.0f;
	offset.z = (( (maximum.z - minimum.z) / 2.0f ) + minimum.z ) * -1.0f;
	
	int v;
	for (v=0;v<num_vertex;v++)
	{
		vertex_list[v].x += offset.x;
		vertex_list[v].y += offset.y;
		vertex_list[v].z += offset.z;
	}

	//
	// apply the linear equation y = (x^2 + z^2) to deform the path into a "bell" shape
	//

	float highest = 0.0f;


	for (v=0;v<num_vertex;v++)
	{
		SkyVertex *ptr = &vertex_list[v];

		ptr->y = (ptr->x * ptr->x) + ( ptr->z * ptr->z );

		if ( fabs ( ptr->y ) > highest )
		{
			highest = (float)fabs(ptr->y);
		}

	}

	for (int s=0;s<num_vertex;s++)
	{
		SkyVertex *ptr = &vertex_list[s];

		ptr->y = ( ptr->y * 20.0f ) / highest;

	}

	//rotate_morph ( sk_vector ( INVERSEANGLE, 0.0f, 0.0f) );

	const float INVERSEANGLE		= 180.0f * 0.01745329251994329547f;
	CSIBCMatrix4x4 rotMat;
	rotMat.SetToRotation ( CSIBCVector3D(180.0f * 0.01745329251994329547f, 0.0f, 0.0f) );
	
	for (v=0;v<num_vertex;v++)
	{
		CSIBCVector3D vec ( vertex_list[v].x, vertex_list[v].y, vertex_list[v].z);
		rotMat.Multiply ( vec, vec );

		vertex_list[v].x = vec.m_fX;
		vertex_list[v].y = vec.m_fY;
		vertex_list[v].z = vec.m_fZ;
	}


	for (v=0;v<num_vertex;v++)
	{
		vertex_list[v].x *= 15.0f;
		vertex_list[v].y *= 10.0f;
		vertex_list[v].z *= 15.0f;
	}

	return 1;
}

int sky::create_patch_indicies(int m, int n, unsigned int *pinds, int maxind)
{
  int n1, m1;
  int nv;
  int j;
  int ii;
    int icycl2;
  int iout;
  int iby2;
  int nindex;  

  n1=n+1;
  m1=m+1;
  nv=n1*m1;

  nindex=(2*n+1)*m+1;

  if(nindex>=maxind) return -1;


  icycl2=2*n+1; 


  for(ii=0; ii<nindex; ii++) {
    j=ii / icycl2;
    iby2=(ii % icycl2) >> 1;
      if(j&1) {
        if(ii&1) {
          iout=(j+1)*n1-1-iby2;
        } else {
          iout=(j+2)*n1-1-iby2;
        }
      } else {
        if(ii&1) {
          iout=(j+1)*n1+iby2;
        } else {
          iout=j*n1+iby2;
        }
      }
      pinds[ii]=iout;
  }
  return nindex;
}

void sky::render ()
{
	glPushAttrib ( GL_ALL_ATTRIB_BITS );

	glEnable( GL_DEPTH_TEST ); 

	glEnable ( GL_FOG );

	if ( sky_detail >= 3 )
		glEnable ( GL_DITHER );
	
	glFogi(GL_FOG_MODE, GL_EXP);
	glFogf(GL_FOG_START, fog_start);
	glFogf(GL_FOG_END, fog_end);
	glFogf(GL_FOG_DENSITY, fog_density);
	glHint(GL_FOG_HINT, GL_NICEST);
	glFogfv (GL_FOG_COLOR, fog_color);

	for (int l=1;l<num_layers;l++)
	{
		
		if ( l > 0 )
		{
			
			glEnable ( GL_BLEND );
			
			glBlendFunc(GL_SRC_ALPHA,GL_ONE);
			
			glMatrixMode ( GL_TEXTURE );
			glLoadIdentity();
			glTranslatef ( layers[l]->position.m_fX , layers[l]->position.m_fZ,0.0f);
		}
		

		glEnable ( GL_TEXTURE_2D );
		glBindTexture ( GL_TEXTURE_2D, layers[l]->texture );
		rendergeometry();

		
	}

	glMatrixMode ( GL_TEXTURE );
	glLoadIdentity();

	glMatrixMode ( GL_MODELVIEW );

	glPopAttrib ();

	
}

void sky::set_tilling ( int tile )
{
	float MaxX,MaxZ;
	float MinX,MinZ;
	float TU;
	float TV;

	MinX=MinZ=1000.0f;
	MaxX=MaxZ=0.0f;


	for (int v=0;v<num_vertex;v++)
	{
		if (vertex_list[v].x>MaxX) MaxX=vertex_list[v].x;
		if (vertex_list[v].z>MaxZ) MaxZ=vertex_list[v].z;

		if (vertex_list[v].x<MinX) MinX=vertex_list[v].x;
		if (vertex_list[v].z<MinZ) MinZ=vertex_list[v].z;
	}

	for (int a=0;a<num_vertex;a++)
	{
		TU=vertex_list[a].x/(MaxX/(float)tile);
		TV=vertex_list[a].z/(MaxZ/(float)tile);
		vertex_list[a].tu=TU;
		vertex_list[a].tv=TV;
	}
	
}

void sky::render_background ( )
{
	glPushAttrib ( GL_ALL_ATTRIB_BITS );

	//glDisable ( GL_DEPTH_TEST );

/*
	glEnable ( GL_FOG );
	

	if ( sky_detail >= 3 )
		glEnable ( GL_DITHER );
	
	glFogi(GL_FOG_MODE, GL_EXP);
	glFogf(GL_FOG_START, fog_start);
	glFogf(GL_FOG_END, fog_end);
	glFogf(GL_FOG_DENSITY, fog_density);
	glHint(GL_FOG_HINT, GL_NICEST);
	glFogfv (GL_FOG_COLOR, fog_color);
*/
	if ( layers[0] != NULL )
	{
		glEnable ( GL_TEXTURE_2D );
		glBindTexture ( GL_TEXTURE_2D, layers[0]->texture );
		rendergeometry();
	}

	
	glPopAttrib ();

}

skylayer *sky::get_layer( int i )
{
	if ( ( i > num_layers ) || (i < 0 ) )
	{
		return NULL;
	}

	return layers[i];
}



void sky::rendergeometry()
{

	float		*vertexptr;
	float		*textureptr;
	
	vertexptr = &vertex_list[0].x;
	textureptr = &vertex_list[0].tu;

	//glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE );
	glEnableClientState(GL_VERTEX_ARRAY);     
	glEnableClientState(GL_TEXTURE_COORD_ARRAY); 
	glDisableClientState(GL_COLOR_ARRAY);
	glEnable ( GL_TEXTURE_2D );
	glDisable ( GL_LIGHTING );

	glVertexPointer(3,GL_FLOAT,vertex_stride, vertexptr);
	
	glTexCoordPointer( 2, GL_FLOAT,uv_stride,textureptr);



	unsigned int		*indexptr;
	int num_ogl_tri = 0;


	indexptr = &index_list[0];
	num_ogl_tri = num_tri;

	glDrawElements(GL_TRIANGLE_STRIP,num_ogl_tri,GL_UNSIGNED_INT,indexptr);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY); 

}
