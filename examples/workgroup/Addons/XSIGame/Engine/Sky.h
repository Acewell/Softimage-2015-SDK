#ifndef _SKY_H_
#define _SKY_H_

#include <SIBCVector.h>
#include <SIBCArray.h>
#include <SIBCColor.h>
#include "Display.h"
#include "Engine.h"

typedef struct tagSkyVertex
{
	float	x;
	float	y;
	float	z;
	float	nx;
	float	ny;
	float	nz;
	float	tu;
	float	tv;

} SkyVertex;
class ENGINE_API skylayer 
{
public:
	skylayer();
	~skylayer();

	void set ( Display* in_pDisplay, char *texturename, CSIBCVector3D layer_speed );
	void render ( void );

	CSIBCVector3D	position;
	CSIBCVector3D	speed;
	int				texture;

private:


};



class ENGINE_API sky
{
public:
	sky(Display *in_pDisplay);
	~sky();

	int create ( int layer_count, int detail_level, Display *in_pDisplay , CSIBCColorf fog);
	int tick ( float milliseconds );
	int sky::add_layer ( char *filename, int in_iIdx, CSIBCVector3D speed);
	skylayer *get_layer( int i );

	void render ( void );
	void render_background ( void );

	void set_fog_start ( float s ) { fog_start = s; };
	void set_fog_end ( float e ) { fog_end = e; };
	void set_fog_density ( float d ) { fog_density = d; };

	void set_fog_color ( CSIBCColorf );

	CSIBCColorf get_fog_color ();

	float get_fog_start () { return fog_start; };
	float get_fog_end () { return fog_end; };
	float get_fog_density () { return fog_density; };

	int	  create_geometry ();
	int create_patch_indicies(int m, int n, unsigned int *pinds, int maxind);
	void set_tilling ( int tile );
	void rendergeometry();

private:

	int	sky_detail;					// sky detail user varable

	int complexity;

	int	num_layers;
	int num_allocated;
	CSIBCArray<skylayer*> layers;
	
	float	fog_start;
	float	fog_end;
	float	fog_density;

	float	fog_color[4];

	Display *m_pDisplay;
	SkyVertex *vertex_list;
	unsigned int	*index_list;
	int	num_tri;
	int num_vertex;
	LONG vertex_stride;
	LONG uv_stride;

};



#endif