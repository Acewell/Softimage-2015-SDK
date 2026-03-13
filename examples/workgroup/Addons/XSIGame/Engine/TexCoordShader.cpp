#include "TexCoordShader.h"

void ComputeTransforms(
	float		*mat, 
	float		scx,
	float		scy,
	float		scz,
	float		rx,
	float		ry,
	float		rz,
	float		tx,
	float		ty,
	float		tz);

TexCoordShader::TexCoordShader(CSLXSIShader* in_pShader, Display* in_pDisplay ) : Shader ( in_pShader,in_pDisplay  )
{
	m_iUVType = in_pShader->GetParameterList()[2]->GetValue ()->lVal;
	m_iNbComponents = in_pShader->GetParameterList()[3]->GetValue ()->lVal;
	uwrap = in_pShader->GetParameterList()[4]->GetValue ()->lVal;
	vwrap  = in_pShader->GetParameterList()[5]->GetValue ()->lVal;
	wwrap  = in_pShader->GetParameterList()[6]->GetValue ()->lVal;
	Transform  = in_pShader->GetParameterList()[7]->GetValue ()->boolVal;
	trsx  = in_pShader->GetParameterList()[8];
	trsy  = in_pShader->GetParameterList()[9];
	trsz  = in_pShader->GetParameterList()[10];
	rotx  = in_pShader->GetParameterList()[11];
	roty  = in_pShader->GetParameterList()[12];
	rotz  = in_pShader->GetParameterList()[13];
	sclx  = in_pShader->GetParameterList()[14];
	scly  = in_pShader->GetParameterList()[15];
	sclz  = in_pShader->GetParameterList()[16];
}

TexCoordShader::~TexCoordShader(void)
{
}

void TexCoordShader::execute ()
{

	switch(m_iUVType)
	{
		case 0: // Nothing to do
				break;
		case 1:	::glTexGenf( GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR );
				::glTexGenf( GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR );
				::glTexGenf( GL_R, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR );
				::glTexGenf( GL_Q, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR );
				break;
		case 2: ::glTexGenf( GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR );
				::glTexGenf( GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR );
				::glTexGenf( GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR );
				::glTexGenf( GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR );
				break;
		case 3: ::glTexGenf( GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );
				::glTexGenf( GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );
				break;
		case 4: {
					::glTexGenf( GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_NV );
					::glTexGenf( GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_NV );
					::glTexGenf( GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_NV );
				}
				break;
		case 5:	{
					::glTexGenf( GL_S, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP_NV );
					::glTexGenf( GL_T, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP_NV );
					::glTexGenf( GL_R, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP_NV );
				}
				break;
	}

	
	// set what texture coord will go through
	if(m_iUVType > 0)
	{
		::glEnable( GL_TEXTURE_GEN_S );
		::glDisable( GL_TEXTURE_GEN_T );
		::glDisable( GL_TEXTURE_GEN_R );
		::glDisable( GL_TEXTURE_GEN_Q );

		if(m_iNbComponents > 0)
		{
			::glEnable( GL_TEXTURE_GEN_T );
		}
		if(m_iNbComponents > 1)
		{
			::glEnable( GL_TEXTURE_GEN_R );
		}
		if(m_iNbComponents > 2)
		{
			::glEnable( GL_TEXTURE_GEN_Q );
		}

	}
	else
	{
		::glDisable( GL_TEXTURE_GEN_S );
		::glDisable( GL_TEXTURE_GEN_T );
		::glDisable( GL_TEXTURE_GEN_R );
		::glDisable( GL_TEXTURE_GEN_Q );
	}

	int		TextureTarget;

	if(::glIsEnabled(GL_TEXTURE_CUBE_MAP_ARB))
	{
		TextureTarget = GL_TEXTURE_CUBE_MAP_ARB;
	}
	else
	{
		TextureTarget = GL_TEXTURE_2D;
	}
	// set wrap modes
	switch(uwrap)
	{
		case 0:		::glTexParameteri(TextureTarget, GL_TEXTURE_WRAP_S, GL_REPEAT); break;
		case 1:		::glTexParameteri(TextureTarget, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT_ARB); break;
		case 2:		::glTexParameteri(TextureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP); break;
		case 3:		::glTexParameteri(TextureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); break;
		case 4:		::glTexParameteri(TextureTarget, GL_TEXTURE_WRAP_S, GL_MIRROR_CLAMP_ATI); break;
		case 5:		::glTexParameteri(TextureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); break;
	}

	switch(vwrap)
	{
		case 0:		::glTexParameteri(TextureTarget, GL_TEXTURE_WRAP_T, GL_REPEAT); break;
		case 1:		::glTexParameteri(TextureTarget, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT_ARB); break;
		case 2:		::glTexParameteri(TextureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP); break;
		case 3:		::glTexParameteri(TextureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER); 	break;
		case 4:		::glTexParameteri(TextureTarget, GL_TEXTURE_WRAP_T, GL_MIRROR_CLAMP_ATI); break;
		case 5:		::glTexParameteri(TextureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); break;
	}

	switch(wwrap)
	{
		case 0:		::glTexParameteri(TextureTarget, GL_TEXTURE_WRAP_R, GL_REPEAT); break;
		case 1:		::glTexParameteri(TextureTarget, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT_ARB); break;
		case 2:		::glTexParameteri(TextureTarget, GL_TEXTURE_WRAP_R, GL_CLAMP); break;
		case 3:		::glTexParameteri(TextureTarget, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER); break;
		case 4:		::glTexParameteri(TextureTarget, GL_TEXTURE_WRAP_R, GL_MIRROR_CLAMP_ATI); break;
		case 5:		::glTexParameteri(TextureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); break;
	}

	// set transforms now
	if(Transform)
	{
		float	transforms[16];

		::glMatrixMode(GL_TEXTURE);
		ComputeTransforms(transforms, 
			sclx->GetValue()->fVal, scly->GetValue()->fVal, sclz->GetValue()->fVal,
			rotx->GetValue()->fVal, roty->GetValue()->fVal, rotz->GetValue()->fVal, 
			trsx->GetValue()->fVal, trsy->GetValue()->fVal, trsz->GetValue()->fVal);
		::glLoadMatrixf(transforms);
		::glMatrixMode(GL_MODELVIEW);
	}
}

void TexCoordShader::enable ( bool in_bEnable )
{

	if ( !in_bEnable )
	{
		if(Transform)
		{
			::glMatrixMode(GL_TEXTURE);
			::glLoadIdentity();
			::glMatrixMode(GL_MODELVIEW);
		}
	}

	::glDisable( GL_TEXTURE_GEN_S );
	::glDisable( GL_TEXTURE_GEN_T );
	::glDisable( GL_TEXTURE_GEN_R );
	::glDisable( GL_TEXTURE_GEN_Q );
}

void ComputeTransforms(
	float		*mat, 
	float		scx,
	float		scy,
	float		scz,
	float		rx,
	float		ry,
	float		rz,
	float		tx,
	float		ty,
	float		tz)
{
	// rotation
	float   	sx, cx, sy, cy, sz, cz, tmp;

	rx *= 0.01745329251f;
	ry *= 0.01745329251f;
	rz *= 0.01745329251f;

	sx = sinf( rx );   cx = cosf( rx );
	sy = sinf( ry );   cy = cosf( ry );
	sz = sinf( rz );   cz = cosf( rz );
	
	mat[0]  	= cy * cz;
	mat[1]  	= cy * sz;
	mat[2]  	= -sy;

	tmp = sx * sy;
	mat[4]   = tmp * cz - cx * sz;
	mat[5]   = tmp * sz + cx * cz;
	mat[6]   = sx * cy;

	tmp = cx * sy;
	mat[8]   = tmp * cz + sx * sz;
	mat[9]   = tmp * sz - sx * cz;
	mat[10]   = cx * cy;

	// scaling
	mat[0] *= scx;
	mat[1] *= scx;
	mat[2] *= scx;
	mat[3] = 0;

	mat[4] *= scy;
	mat[5] *= scy;
	mat[6] *= scy;
	mat[7] = 0;

	mat[8] *= scz;
	mat[9] *= scz;
	mat[10] *= scz;
	mat[11] = 0;

	// translation
	mat[12] = tx;
	mat[13] = ty;
	mat[14] = tz;
	mat[15] = 1;
}