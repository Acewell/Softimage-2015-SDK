// CustomPrimitives example
//
//	Copyright 2012 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   
//
//	File:	CustomBox.cpp
//
//	Description:
//
//		Defines a Box primitive that is defined by 3 floating-point half-extents
//		representing height, width and length.
//
#ifndef linux
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h> // Needed for OpenGL on windows
#endif
#include <GL/gl.h>

#include <xsi_application.h>
#include <xsi_context.h>
#include <xsi_pluginregistrar.h>
#include <xsi_status.h>
#include <xsi_menu.h>
#include <xsi_customprimitive.h>
#include <xsi_factory.h>
#include <xsi_parameter.h>
#include <xsi_ppglayout.h>
#include <xsi_ppgeventcontext.h>
#include <xsi_customprimitivecontext.h>
#include <xsi_geometry.h>
#include <xsi_polygonmesh.h>

#include <map>

using namespace XSI; 

////////////////////////////////////////////////////////////////////////////
// Defines
//
#define kWidthName L"HalfWidth"
#define kHeightName L"HalfHeight"
#define kLengthName L"HalfLength"

#define kMinWidth 0.1
#define kMaxWidth 100.0

#define kMinHeight 0.1
#define kMaxHeight 100.0

#define kMinLength 0.1
#define kMaxLength 100.0

////////////////////////////////////////////////////////////////////////////
// Parameter cache.
//
// The cache is indexed by object ID and keep the last evaluation ID
// to detect that the object has changed.
//
// Warning: to be completely correct, we would need to evict entries
//          in the cache when the primitive is deleted by handling
//          various events like OnNestedObjectChange, BeginSceneOpen, etc.
//
//          See various _OnEvent below.

struct Box_CachedData
{
	Box_CachedData() : lastEvalID(-1) {}

	LONG    lastEvalID;
	double  halfWidth;
	double  halfHeight;
	double  halfLength;
};

struct Box_CacheContainer
{
	Box_CachedData& Get(CustomPrimitive& in_prim)
	{
		const ObjectID objectID = in_prim.GetObjectID();
		const LONG evalID = in_prim.GetEvaluationID();
		Box_CachedData& data = m_Cache[objectID];
		if ( data.lastEvalID != evalID )
		{
			CParameterRefArray& params = in_prim.GetParameters();
			data.halfWidth  = params.GetValue( kWidthName );
			data.halfHeight = params.GetValue( kHeightName );
			data.halfLength = params.GetValue( kLengthName );

			data.lastEvalID = evalID;
		}
		return data;
	}

	void Drop(CustomPrimitive& in_prim)
	{
		const ObjectID objectID = in_prim.GetObjectID();
		m_Cache.erase( objectID );
	}

	void Clear()
	{
		m_Cache.clear();
	}

private:
	typedef ULONG ObjectID;

	std::map<ObjectID, Box_CachedData> m_Cache;
};

static Box_CacheContainer g_Cache;


////////////////////////////////////////////////////////////////////////////
// Event used to evict dead objects from the cache.
//
// Currently crudely empty the cache. A more refined version would
// analyze the data provided in each event to only invalidate
// the affected objects.
//
// Other events would need to be treated too to cover all possible
// cases where the objects become invalid.
//
SICALLBACK BoxCacheSceneOpen_OnEvent( const CRef& in_ref )
{
	g_Cache.Clear();
	return CStatus::False;
}

SICALLBACK BoxCacheObjectRemoved_OnEvent( const CRef& in_ref )
{
	g_Cache.Clear();
	return CStatus::False;
}


////////////////////////////////////////////////////////////////////////////
// Softimage call-backs.
//
SICALLBACK Box_Define( const CRef& in_ref )
{
	Context in_ctxt( in_ref );
	CustomPrimitive in_prim( in_ctxt.GetSource() );
	if( in_prim.IsValid() )
	{
		Application().LogMessage(CString("Box_Define: ") + in_prim.GetFullName());
		Factory l_fact = Application().GetFactory();
		CRef l_widthDef = l_fact.CreateParamDef( kWidthName, CValue::siDouble, 1.0, kMinWidth, kMaxWidth );
		CRef l_heightDef = l_fact.CreateParamDef( kHeightName, CValue::siDouble, 1.0, kMinHeight, kMaxHeight );
		CRef l_lengthDef = l_fact.CreateParamDef( kLengthName, CValue::siDouble, 1.0, kMinLength, kMaxLength );
		Parameter l_width;
		Parameter l_height;
		Parameter l_length;
		in_prim.AddParameter( l_widthDef, l_width );
		in_prim.AddParameter( l_heightDef, l_height );
		in_prim.AddParameter( l_lengthDef, l_length );
	}
	return CStatus::OK;
}

SICALLBACK Box_DefineLayout( const CRef& in_ref )
{
	Context in_ctxt( in_ref );

	PPGLayout layout = in_ctxt.GetSource();
	if ( layout.IsValid() )
	{
		layout.Clear();
		layout.AddGroup("Box Group");
		layout.AddItem(kWidthName, "Half-Width");
		layout.AddItem(kHeightName, "Half-Height");
		layout.AddItem(kLengthName, "Half-Length");
		layout.AddButton("ConvertGeom", "Convert to PolygonMesh");
		layout.AddButton("CloseTheInspector", "Close the Inspector");
		layout.AddButton("RefreshTheInspector", "Refresh the Inspector");
		layout.EndGroup();
	}
	return CStatus::OK;
}

SICALLBACK Box_PPGEvent( const CRef& in_ref )
{
	PPGEventContext in_ctxt( in_ref );

	// Note: for PPGEvent related to custom primitives, everywhere in the SDK documentation
	//       about PPGEvent where they talk about CustomProperty, you need to replace the
	//       CustomProperty with Primitive.
	//
	//       For example, the source in siOnInit is the primitive, not a custom property.

	switch ( in_ctxt.GetEventID() )
	{
	case siOnInit:
		{
			CustomPrimitive primitive = in_ctxt.GetSource() ;
			Application().LogMessage(CString("Box_PPGEvent: OnInit: " + primitive.GetName()));
			break;
		}
	case siOnClosed:
		{
			CustomPrimitive primitive = in_ctxt.GetSource() ;
			Application().LogMessage(CString("Box_PPGEvent: siOnClosed: " + primitive.GetName()));
			break;
		}
	case siParameterChange:
		{
			Parameter changed   = in_ctxt.GetSource();
			CustomPrimitive primitive = changed.GetParent();
			CString paramName   = changed.GetScriptName(); 
			// Show that it is possible to change a value in the callback.
			// Note that the Draw() call may see the intermediary value before
			// it is changed this way.

			if (paramName == kWidthName)
			{
				primitive.PutParameterValue( kHeightName, changed.GetValue() );
			}
			else if ( paramName == kHeightName )
			{
				primitive.PutParameterValue( kWidthName, changed.GetValue() );
			}

			Application().LogMessage(CString("Box_PPGEvent: siParameterChange: " + primitive.GetName() + CString("/") + paramName + CString(" = ") + changed.GetValue().GetAsText()));
			break;
		}
	case siButtonClicked:
		{
			Application().LogMessage(CString("Box_PPGEvent: siButtonClicked"));
			CValue buttonPressed = in_ctxt.GetAttribute( L"Button" ) ;
			if ( buttonPressed.GetAsText() == "CloseTheInspector" )
			{
				in_ctxt.PutAttribute("Close", true);
			}
			else if ( buttonPressed.GetAsText() == "RefreshTheInspector" )
			{
				in_ctxt.PutAttribute("Refresh", true);
			}
			else if ( buttonPressed.GetAsText() == "ConvertGeom" )
			{
				CustomPrimitive primitive = in_ctxt.GetSource() ;
				CValue out_arg;
				CValueArray in_args;
				in_args.Add( "MeshSurface" );
				in_args.Add( primitive.GetName() );
				Application().ExecuteCommand( "SIConvert", in_args, out_arg );
			}
			break;
		}
	case siTabChange:
		{
			CustomPrimitive primitive = in_ctxt.GetSource();
			CValue tabLabel     = in_ctxt.GetAttribute( L"Tab" );
			Application().LogMessage(CString("Box_PPGEvent: siTabChange: " + primitive.GetName() + CString(": ") + tabLabel.GetAsText()));
			break;
		}
	default:
		Application().LogMessage(CString("Box_PPGEvent: unknown event."));
		break;
	}

	return CStatus::OK;
}

SICALLBACK Box_Draw( const CRef& in_ref )
{
	Context in_ctxt( in_ref );
	CustomPrimitive in_prim(in_ctxt.GetSource());
	if( !in_prim.IsValid() )
	{
		return CStatus::Fail;
	}

	// We keep a cache of primitive data.

	Box_CachedData& data = g_Cache.Get(in_prim);
	double boxHalfWidth  = data.halfWidth;
	double boxHalfHeight = data.halfHeight;
	double boxHalfLength = data.halfLength;

	// Note: the custom primitive API doesn't protect the OpenGL state
	//       for performance reasons. It is the duty of the custom primitive
	//       to leave the OpenGL state as it was on entry.

	// Draw Box
	//
	double boxMinPt[3];
	double boxMaxPt[3];

	boxMinPt[0] = -boxHalfWidth;
	boxMinPt[2] = -boxHalfLength;
	boxMinPt[1] = -boxHalfHeight;

	boxMaxPt[0] = boxHalfWidth;
	boxMaxPt[2] = boxHalfLength;
	boxMaxPt[1] = boxHalfHeight;

	GLdouble l_Verts[8][3];

	l_Verts[0][0] = boxMinPt[0];
	l_Verts[0][1] = boxMinPt[1];
	l_Verts[0][2] = boxMinPt[2];

	l_Verts[1][0] = boxMaxPt[0];
	l_Verts[1][1] = boxMinPt[1];
	l_Verts[1][2] = boxMinPt[2];

	l_Verts[2][0] = boxMaxPt[0];
	l_Verts[2][1] = boxMaxPt[1];
	l_Verts[2][2] = boxMinPt[2];

	l_Verts[3][0] = boxMinPt[0];
	l_Verts[3][1] = boxMaxPt[1];
	l_Verts[3][2] = boxMinPt[2];

	l_Verts[4][0] = boxMinPt[0];
	l_Verts[4][1] = boxMaxPt[1];
	l_Verts[4][2] = boxMaxPt[2];

	l_Verts[5][0] = boxMaxPt[0];
	l_Verts[5][1] = boxMaxPt[1];
	l_Verts[5][2] = boxMaxPt[2];

	l_Verts[6][0] = boxMaxPt[0];
	l_Verts[6][1] = boxMinPt[1];
	l_Verts[6][2] = boxMaxPt[2];

	l_Verts[7][0] = boxMinPt[0];
	l_Verts[7][1] = boxMinPt[1];
	l_Verts[7][2] = boxMaxPt[2];

	::glBegin( GL_LINE_STRIP );
	::glVertex3dv( l_Verts[0] );
	::glVertex3dv( l_Verts[1] );
	::glVertex3dv( l_Verts[2] );
	::glVertex3dv( l_Verts[3] );
	::glVertex3dv( l_Verts[0] );

	::glVertex3dv( l_Verts[7] );
	::glVertex3dv( l_Verts[6] );
	::glVertex3dv( l_Verts[5] );
	::glVertex3dv( l_Verts[4] );
	::glVertex3dv( l_Verts[7] );
	::glEnd();

	::glBegin( GL_LINES );
	::glVertex3dv( l_Verts[3] );
	::glVertex3dv( l_Verts[4] );
	::glVertex3dv( l_Verts[2] );
	::glVertex3dv( l_Verts[5] );
	::glVertex3dv( l_Verts[1] );
	::glVertex3dv( l_Verts[6] );
	::glEnd();

	return CStatus::OK;
}

SICALLBACK Box_BoundingBox( const CRef& in_ref )
{
	Context in_ctxt( in_ref );
	CustomPrimitive in_prim( in_ctxt.GetSource());
	if( !in_prim.IsValid() )
	{
		return CStatus::Fail;
	}

	// We keep a cache of primitive data.

	Box_CachedData& data = g_Cache.Get(in_prim);
	double boxHalfWidth  = data.halfWidth;
	double boxHalfHeight = data.halfHeight;
	double boxHalfLength = data.halfLength;

	in_ctxt.PutAttribute( "LowerBoundX", -boxHalfWidth );
	in_ctxt.PutAttribute( "LowerBoundY", -boxHalfHeight );
	in_ctxt.PutAttribute( "LowerBoundZ", -boxHalfLength );
	in_ctxt.PutAttribute( "UpperBoundX", boxHalfWidth );
	in_ctxt.PutAttribute( "UpperBoundY", boxHalfHeight );
	in_ctxt.PutAttribute( "UpperBoundZ", boxHalfLength );

	return CStatus::OK;
}

SICALLBACK Box_ConvertToGeom( const CRef& in_ref )
	//
	// This callback is invoked when the SIConvert or CreatePrim commands are run
	// for a custom primitive object. 
	//
{
	CustomPrimitiveContext in_ctxt( in_ref );
	CustomPrimitive in_prim( in_ctxt.GetSource() );
	if( !in_prim.IsValid() )
	{
		return CStatus::Fail;
	}

	Box_CachedData& data = g_Cache.Get(in_prim);
	double boxHalfWidth  = data.halfWidth;
	double boxHalfHeight = data.halfHeight;
	double boxHalfLength = data.halfLength;

	double boxMinPt[3];
	double boxMaxPt[3];

	boxMinPt[0] = -boxHalfWidth;
	boxMinPt[1] = -boxHalfHeight;
	boxMinPt[2] = 0;

	boxMaxPt[0] = boxHalfWidth;
	boxMaxPt[1] = boxHalfHeight;
	boxMaxPt[2] = 0;


	Geometry out_geo = in_ctxt.GetGeometry();

	// PolygonMesh support
	PolygonMesh out_mesh( out_geo );
	if( out_mesh.IsValid() )
	{
		// Convert to polygon.
		MATH::CVector3Array out_verts;
		CLongArray out_faces;

		int index = 0;
		for (int i = -boxHalfLength; i <= boxHalfLength; ++i){
			MATH::CVector3 vMinXMinY( -boxHalfWidth, -boxHalfHeight, 1.0 * i );
			MATH::CVector3 vMinXMaxY( -boxHalfWidth, boxHalfHeight, 1.0 * i );
			MATH::CVector3 vMaxXMinY( boxHalfWidth, -boxHalfHeight, 1.0 * i );
			MATH::CVector3 vMaxXMaxY( boxHalfWidth, boxHalfHeight, 1.0 * i );

			out_verts.Add( vMinXMinY );
			out_verts.Add( vMinXMaxY );
			out_verts.Add( vMaxXMaxY );
			out_verts.Add( vMaxXMinY );

			out_faces.Add( 4 ); // Vertex count for tri
			out_faces.Add( index + 0 );
			out_faces.Add( index + 1 );
			out_faces.Add( index + 2 );
			out_faces.Add( index + 3 );
			index += 4;
		}

		return out_mesh.Set( out_verts, out_faces );
	}

	return CStatus::OK;
}


SICALLBACK OnCustomBoxMenuItem( CRef& in_ref )
{
	Context ctxt( in_ref );
	MenuItem menuItem = ctxt.GetSource();

	Application app;
	CValue out_arg;
	CValueArray in_args;
	in_args.Add( L"Box" );
	app.ExecuteCommand( "GetPrim", in_args, out_arg );

	return CStatus::OK;
}


SICALLBACK OnCustomBoxMeshMenuItem( CRef& in_ref )
{
	Context ctxt( in_ref );
	MenuItem menuItem = ctxt.GetSource();

	Application app;
	CValue out_arg;
	CValueArray in_args;
	in_args.Add( L"Box" );
	in_args.Add( L"MeshSurface" );
	app.ExecuteCommand( "CreatePrim", in_args, out_arg );

	return CStatus::OK;
}
