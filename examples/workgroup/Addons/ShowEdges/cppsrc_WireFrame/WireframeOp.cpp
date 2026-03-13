 //*****************************************************************************
/*
   WireframeOp.cpp 
   Implementation of the WireframeOp operator

   By Andrew Skowronski, July 2003

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#include <xsi_parameter.h>
#include <xsi_operatorcontext.h>
#include <xsi_primitive.h>
#include <xsi_geometry.h>
#include <xsi_userdatablob.h>
#include <xsi_segment.h>
#include <xsi_point.h>
#include <xsi_vector3.h>
#include <xsi_pluginregistrar.h>

using namespace XSI;

// CWireframeOp represents an instance of your
// operator.
class CWireframeOp
{
public:
	CWireframeOp() {}
	~CWireframeOp() {}

	CStatus Update(OperatorContext&,UserDataBlob&);
};

CStatus CWireframeOp::Update
(
	OperatorContext&	in_ctx,
	UserDataBlob&		outUserData
)
{
	// Get access to the geometry that the operator is connected
			
	Primitive inPrim( in_ctx.GetInputValue(0) );
	Geometry inGeom(inPrim.GetGeometry());

	// Because Mental Ray shaders cannot access the Softimage object model,
	// we will read the geometry now, and encode all the edges into a 
	// buffer.
	// Format of the user data is this:
	//
	//<int>			Number of lines
	//[
	//	<float>*3	Start point (xyz)
	//	<float>*3	Direction to end point (xyz)
	//] * nb_lines

	CSegmentRefArray segments( inGeom.GetSegments() ) ;
	int cntEdges = (int)segments.GetCount() ;
	int bufferSize =  sizeof( int ) + cntEdges * 6 * sizeof(float) ;

	void * pData = malloc( bufferSize ) ;
	if ( pData == NULL ) return CStatus::OutOfMemory ;

	// Fill in the number of edges
	int * pSize = (int*) pData ;
	*pSize = cntEdges;

	// Fill in the start and end position that defines each edge
	float * pEdgeData = (float*)(pSize+1) ;
	for ( int i = 0 ; i < cntEdges ; i++ )
	{
		Segment seg = segments[i] ;
		CPointRefArray points = seg.GetPoints() ;
		
		if ( points.GetCount() != 2 )
		{
			free( pData ) ; 
			return CStatus::Unexpected ;
		}
		
		MATH::CVector3 point0 =  ((Point)points[0]).GetPosition() ;

		pEdgeData[0] = (float) point0.GetX() ;
		pEdgeData[1] = (float) point0.GetY() ;
		pEdgeData[2] = (float) point0.GetZ() ;

		MATH::CVector3 point1 =  ((Point)points[1]).GetPosition() ;
		
		// To get direction
		point1 -= point0;

		pEdgeData[3] = (float) point1.GetX() ;
		pEdgeData[4] = (float) point1.GetY() ;
		pEdgeData[5] = (float) point1.GetZ() ;

		pEdgeData += 6 ;
	}

	// Save this buffer in the UserDataBlob
	outUserData.PutValue( (unsigned char*) pData, bufferSize ) ;

	// Cleanup
	free( pData ) ;

	return CStatus::OK ;
}

//////////////////////////////////////////////////////////////////////////////
// Entry Points
//////////////////////////////////////////////////////////////////////////////

XSIPLUGINCALLBACK CStatus WireframeOp_Init
(
	CRef& in_ctx
)
{
	Context ctx(in_ctx) ;	
	CWireframeOp* pThis = new CWireframeOp();	
	ctx.PutUserData( (CValue::siPtrType)pThis );
	return CStatus::OK;
}

XSIPLUGINCALLBACK CStatus WireframeOp_Term
(
	CRef& in_ctx
)
{
	Context ctx(in_ctx) ;
	CValue::siPtrType pUserData = ctx.GetUserData();
	delete (CWireframeOp*)pUserData;
	return CStatus::OK;
}

XSIPLUGINCALLBACK CStatus WireframeOp_Update
(
	CRef&	in_ctx
)
{
	OperatorContext ctx(in_ctx) ;
	
	CValue::siPtrType pUserData = ctx.GetUserData();
	CWireframeOp* pThis = (CWireframeOp*)pUserData;	

	UserDataBlob out = ctx.GetOutputTarget() ;
	return pThis->Update(ctx,out);
}


XSIPLUGINCALLBACK CStatus XSILoadPlugin( PluginRegistrar& in_reg )
{
	in_reg.PutAuthor(L"Softimage");
	in_reg.PutName(L"Wireframe Example");
	in_reg.PutVersion(1,0);
	in_reg.RegisterOperator(L"WireframeOp");
	
	//RegistrationInsertionPoint - do not remove this line

	return CStatus::OK;
}
