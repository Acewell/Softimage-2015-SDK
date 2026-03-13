 //*****************************************************************************
// WireframeShader.cpp
// 
// By Halfdan Ingvarsson, 10jul2003
// 
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   
//*****************************************************************************

#include <shader.h>
#include <float.h>

//////////////////////////////////////////////////////////////////////
//
// Types
//
//////////////////////////////////////////////////////////////////////
typedef struct
{
	miColor		m_wireColor;
	miColor		m_baseColor;
	miScalar	m_wireWidth;
} wireframe_p;

typedef struct
{
	miVector	m_vO;			// Origin
	miVector	m_vD;			// Direction
} line;

typedef struct
{
	int			m_nbLines;
	line		m_aLines[ 1 ];
} wireframe_ud;

typedef struct
{
	miBoolean	m_bValid;
	wireframe_ud *m_pWire;
} wireframe_private;

//////////////////////////////////////////////////////////////////////
//
// Implementation
//
//////////////////////////////////////////////////////////////////////
miScalar Point2LineDistance
(
	line		*in_pLine,
	miVector	*in_pPoint
	)
{
	// Return distance from the point to the line segment

	miScalar	l_fT;

	l_fT = - ( mi_vector_dot( &in_pLine->m_vO, &in_pLine->m_vD ) - mi_vector_dot( in_pPoint, &in_pLine->m_vD ) ) / 
			mi_vector_dot( &in_pLine->m_vD, &in_pLine->m_vD );

	if( l_fT < 0.0f || l_fT > 1.0f )
		return( FLT_MAX );

	miVector	l_vPointOnLine;

	l_vPointOnLine.x = in_pLine->m_vO.x + in_pLine->m_vD.x * l_fT;
	l_vPointOnLine.y = in_pLine->m_vO.y + in_pLine->m_vD.y * l_fT;
	l_vPointOnLine.z = in_pLine->m_vO.z + in_pLine->m_vD.z * l_fT;

	return( (miScalar)mi_vector_dist( &l_vPointOnLine, in_pPoint ) );
}

extern "C" DLLEXPORT int wireframe_version( ) { return( 1 ); }


extern "C" DLLEXPORT void wireframe_init
(
	miState		*state,
	wireframe_p	*in_pParam,
	miBoolean	*out_pbLocalInit
	)
{
	if( !in_pParam )
	{
		*out_pbLocalInit = miTRUE;
		return;
	}

	// Allocate shader local memory to store the pointer to the 
	// wireframe userdata.
	wireframe_private	**l_ppPrivate;

	mi_query( miQ_FUNC_USERPTR, state, 0, (void *)&l_ppPrivate );

	(*l_ppPrivate) = (wireframe_private *)mi_mem_allocate( sizeof( wireframe_private ) );

	// Get the wireframe userdata
	miTag	l_tUserData = miNULLTAG;

	if( !mi_query( miQ_INST_DATA, NULL, state->instance, (void *)&l_tUserData ) )
		return;

	for( ;; )
	{
		miUint	l_uiLabel;

		if( !mi_query( miQ_DATA_LABEL, NULL, l_tUserData, (void *)&l_uiLabel ) )
			break;

		// To avoid conflict with other possible uses of 
		// User Data a specific "magic" number
		// is used.  See UserDataID in Example.vbs
		if( l_uiLabel == 6789 )
		{
			mi_query( miQ_DATA_PARAM, NULL, l_tUserData, (void *)&((*l_ppPrivate)->m_pWire ) );
			(*l_ppPrivate)->m_bValid = miTRUE;
			break;
		}

		if( !mi_query( miQ_DATA_NEXT, NULL, l_tUserData, (void *)&l_tUserData ) )
			break;
	}
}

extern "C" DLLEXPORT void wireframe_exit
(
	miState		*state,
	wireframe_p	*in_pParam,
	miBoolean	*out_pbLocalInit
	)
{
	if( !in_pParam )
		return;
	
	wireframe_private	**l_ppPrivate;

	mi_query( miQ_FUNC_USERPTR, state, 0, (void *)&l_ppPrivate );

	mi_mem_release( (*l_ppPrivate) );
}

extern "C" DLLEXPORT miBoolean wireframe
(
	miColor		*out_pColor,
	miState		*state,
	wireframe_p	*in_pParam
	)
{
	wireframe_private	**l_ppPrivate;

	mi_query( miQ_FUNC_USERPTR, state, 0, (void *)&l_ppPrivate );

	if( !(*l_ppPrivate)->m_bValid )
	{
		*out_pColor = *mi_eval_color( &in_pParam->m_baseColor );
		return( miTRUE );
	}
	
	wireframe_ud	*l_pWire = (*l_ppPrivate)->m_pWire;
	miScalar		l_fWidth;
	miVector		l_vPointLocal;

	// See if this intersection point is within the given line width
	// for any line.

	l_fWidth = *mi_eval_scalar( &in_pParam->m_wireWidth );

	mi_point_to_object( state, &l_vPointLocal, &state->point );

	for( int i = 0; i < l_pWire->m_nbLines; i++ )
	{
		if( Point2LineDistance( &l_pWire->m_aLines[ i ], &l_vPointLocal ) < l_fWidth )
		{
			// The evaluated point is close enough to an edge, so color it
			*out_pColor = *mi_eval_color( &in_pParam->m_wireColor );
			return( miTRUE );
		}
	}

	// This point is not on an edge
	*out_pColor = *mi_eval_color( &in_pParam->m_baseColor );

	return( miTRUE );
}
