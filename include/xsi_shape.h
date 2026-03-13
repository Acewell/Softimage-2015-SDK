//*****************************************************************************
/*!
   \file xsi_shape.h
   \brief CShape class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSISHAPE_H__
#define __XSISHAPE_H__

#include "sicppsdk.h"
#include <xsi_decl.h>

namespace XSI {

namespace MATH {

//*****************************************************************************
/*! \class CShape xsi_shape.h
	\brief A class representing primitive types for particles rendering. Shape objects
	are read-only and can be accessed with ICEAttribute properties such as
	ICEAttribute::GetDataArray and ICEAttribute::GetDataArray2D.

	\sa \ref CDataArrayShape "CDataArrayShape"
	\since 7.0

	\eg %This example shows how to access the shape attributes data from a cloud primitive.
	\code
		CValue CreatePrim( const CString& in_presetobj, const CString& in_geometrytype, const CString& in_name, const CString& in_parent )
		CRefArray ApplyOp( const CString& in_presetobj, CString & io_connectionset, const siConstructionMode& in_constructionmode );
		CValue AddICENode( const CValue&  in_presetobj, const CValue&  in_container );
		CValue SetValue( const CString& in_target, const CValue&  in_value, const CValue&  in_time = CValue() );
		void AddAttributeToSetDataICENode( const CValue&  in_setdatanode, const CString& in_attributename, siComponentDataType in_attributetype, siComponentDataContext in_attributecontext, siComponentDataStructure in_attributestructure );
		void ConnectICENodes( const CValue&  in_inputport, const CValue&  in_outputport );

		Application xsi;

		CreatePrim( L"Grid", L"PointCloud", L"", L"");

		Selection selection = xsi.GetSelection();
		X3DObject grid = selection[0];

		// Create shape reference types
		CString strGrid(L"grid");
		ApplyOp( L"ICETree", strGrid, siConstructionModeModeling );
		AddICENode( L"SetData", L"grid.pointcloud.ICETree");
		SetValue( L"grid.pointcloud.ICETree.SetData.PredefinedAttributeName", L"Shape", L"");
		AddAttributeToSetDataICENode(L"grid.pointcloud.ICETree.SetData", L"Shape", siComponentDataTypeShape, siComponentDataContextComponent0D, siComponentDataStructureSingle);
		SetValue(L"grid.pointcloud.ICETree.SetData.shape", 5, L"");
		ConnectICENodes(L"grid.pointcloud.ICETree.port1", L"grid.pointcloud.ICETree.SetData.set");
		AddICENode( L"InstanceShapeNode", L"grid.pointcloud.ICETree" );
		CreatePrim( L"Cylinder", L"MeshSurface", L"", L"" );
		SetValue( L"grid.pointcloud.ICETree.ShapeInstancingNode.Reference", L"cylinder", L"" );
		ConnectICENodes( L"grid.pointcloud.ICETree.SetData.shape", L"grid.pointcloud.ICETree.ShapeInstancingNode.shape" );
		ConnectICENodes( L"grid.pointcloud.ICETree.port2", L"grid.pointcloud.ICETree.SetData.set" );

		CRefArray attrs = grid.GetActivePrimitive().GetGeometry().GetICEAttributes();

		for( ULONG i = 0; i<attrs.GetCount(); i++ )
		{
			ICEAttribute attr = attrs[i];

			if ( attr.GetDataType() == XSI::siICENodeDataShape )
			{
				xsi.LogMessage( L"*******************************************************************" );
				xsi.LogMessage( L"Name: " + attr.GetName() );
				xsi.LogMessage( L"DataType: " + CString(attr.GetDataType()) );
				xsi.LogMessage( L"StructType: " + CString(attr.GetStructureType()) );
				xsi.LogMessage( L"ContextType: " + CString(attr.GetContextType()) );
				xsi.LogMessage( L"IsConstant: " + CString(attr.IsConstant()) );
				xsi.LogMessage( L"Readonly: " + CString(attr.IsReadonly()) );
				xsi.LogMessage( L"Category: " + CString(attr.GetAttributeCategory()) );
				xsi.LogMessage( L"Element count: " + CString(attr.GetElementCount()) );

				CICEAttributeDataArray< XSI::MATH::CShape > data;
				attr.GetDataArray( data );

				for( ULONG i=0; i<data.GetCount( ); i++ )
				{
					xsi.LogMessage( CString( data[ i ] ) );
				}
			}
		}

		// %This example shows how to access the shape attributes data from a cloud primitive by using GetDataArrayChunk.
		ULONG nChunkCount = 4;
		for( ULONG i = 0; i<attrs.GetCount(); i++ )
		{
			ICEAttribute attr = attrs[i];

			if ( attr.GetDataType() != XSI::siICENodeDataShape )
			{
				continue;
			}

			xsi.LogMessage( L"*******************************************************************" );

			//	Compute the chunk vector to access the data
			ULONG nChunkSize = attr.GetElementCount() / nChunkCount;
			ULONG nLastChunk = attr.GetElementCount()  % nChunkCount;

			CLongArray nChunks;
			for( ULONG iChunk = 0; iChunk < nChunkCount; iChunk++ )
			{
				nChunks.Add( nChunkSize );
			}
			nChunks.Add( nLastChunk );

			ULONG nOffset = 0;
			for ( ULONG j=0; j<nChunks.GetCount(); j++ )
			{
				ULONG nChunkSize = nChunks[j];
				if ( nChunkSize == 0 )
				{
					continue;
				}

				CICEAttributeDataArray< XSI::MATH::CShape > data;
				attr.GetDataArrayChunk( nOffset, nChunkSize, data );

				xsi.LogMessage( L"Chunk size: " + CString(data.GetCount( )) );
				for( ULONG i=0; i<data.GetCount( ); i++ )
				{
					xsi.LogMessage( CString( data[ i ] ) );
				}

				nOffset += nChunkSize;
			}
		}

		// Helpers
		CValue CreatePrim( const CString& in_presetobj, const CString& in_geometrytype, const CString& in_name, const CString& in_parent )
		{
			CValueArray args(4);
			CValue retval;
			args[0]= in_presetobj;
			args[1]= in_geometrytype;
			args[2]= in_name;
			args[3]= in_parent;

			Application app;
			app.ExecuteCommand( L"CreatePrim", args, retval );
			return retval;
		}

		CRefArray ApplyOp( const CString& in_presetobj, CString & io_connectionset, const siConstructionMode& in_constructionmode )
		{
			CValueArray args(6);
			CValue retval;

			args[0]=in_presetobj;
			args[1]=io_connectionset;
			args[2]=(LONG)siUnspecified;
			args[3]=(LONG)siPersistentOperation;
			if ( in_constructionmode != siConstructionModeDefault )
			{
				args[5]=(LONG)in_constructionmode;
			}

			Application app;
			CStatus st = app.ExecuteCommand( L"ApplyOp", args, retval );
			io_connectionset=args[1];
			return retval;
		}

		CValue AddICENode( const CValue&  in_presetobj, const CValue&  in_container )
		{
			CValueArray args(2);
			CValue retval;

			args[0]= in_presetobj;
			args[1]= in_container;

			Application app;
			CStatus st = app.ExecuteCommand( L"AddICENode", args, retval );

			return retval;
		}

		void AddAttributeToSetDataICENode( const CValue&  in_setdatanode, const CString& in_attributename, siComponentDataType in_attributetype, siComponentDataContext in_attributecontext, siComponentDataStructure in_attributestructure )
		{
			CValueArray args(5);
			CValue retval;

			args[0]= in_setdatanode;
			args[1]= in_attributename;
			args[2]= (LONG)in_attributetype;
			args[3]= (LONG)in_attributecontext;
			args[4]= (LONG)in_attributestructure;

			Application app;
			CStatus st = app.ExecuteCommand( L"AddAttributeToSetDataICENode", args, retval );

			return;
		}

		void ConnectICENodes( const CValue&  in_inputport, const CValue&  in_outputport )
		{
			CValueArray args(2);
			CValue retval;

			args[0]= in_inputport;
			args[1]= in_outputport;

			Application app;
			CStatus st = app.ExecuteCommand( L"ConnectICENodes", args, retval );

			return;
		}

		CValue SetValue( const CString& in_target, const CValue& in_value, const CValue&  in_time )
		{
			CValueArray args(3);
			CValue retval;

			args[0]= in_target;
			args[1]= in_value;
			args[2]= in_time;

			Application app;

			CStatus st = app.ExecuteCommand( L"SetValue", args, retval );

			return retval;
		}

	\endcode
 */
//*****************************************************************************
class CShape
{
public:
	/*! \struct ParameterInstance xsi_shape.h
		\brief	A struct to hold the parameters for a shape instance
		\since 12.0 (2014)
	*/
	struct ParameterInstance
	{
		bool operator==( const ParameterInstance& in_rOther ) const
		{
			return m_nInstanceIndex == in_rOther.m_nInstanceIndex;
		}
		ULONG m_nInstanceIndex;
	};

	/*! \struct ParameterReference xsi_shape.h
		\brief	A struct to hold the parameters for a shape reference
		\since 12.0 (2014)
	*/
	struct ParameterReference
	{
		bool operator==( const ParameterReference& in_rOther ) const
		{
			return m_nObjectID == in_rOther.m_nObjectID && m_bBranch == in_rOther.m_bBranch;
		}
		ULONG m_nObjectID;
		bool m_bBranch;
	};

	/*! Constructor. Creates a new object based on the specified shape type.
	\param in_type Type of particle shape to create
	*/
	CShape( XSI::siICEShapeType in_type = XSI::siICEShapePoint ) : m_type( in_type )
	{
	}

	/*! Copy constructor. Creates a new object as a CShape type.
	\param in_shape CShape object.
	 */
	CShape( const CShape& in_shape )
	{
		*this = in_shape;
	}

	/*! Destructor. */
	~CShape() {}

	/*! Assignment operator.
	\param in_shape Shape to copy
	\return A reference to this shape.
	 */
	CShape& operator = ( const CShape& in_shape )
	{
		m_type = in_shape.m_type;
		switch ( m_type )
		{
			case XSI::siICEShapeInstance:
			{
				m_description.m_shapeInstance = in_shape.m_description.m_shapeInstance;
			}
			break;

			case XSI::siICEShapeReference:
			{
				m_description.m_shapeReference = in_shape.m_description.m_shapeReference;
			}
			break;
		};
		return *this;
	}

	/*! Returns the shape type.
	\return One of the ::siICEShapeType enum values representing the shape type.
	*/
	XSI::siICEShapeType GetType()
	{
		return (XSI::siICEShapeType)m_type;
	}

	/*! Returns the object ID the shape is referring to. Applies only to the ::siICEShapeReference shape type.
		The returned ID can be used to access the object with Application::GetObjectFromID.
		\return Object ID.
	*/
	ULONG GetReferenceID( )
	{
		if ( m_type == XSI::siICEShapeReference )
		{
			return m_description.m_shapeReference.m_nObjectID;
		}
		return UINT_MAX;
	}

	/*! Returns true if the referenced object is set as branch-selected. Applies to ::siICEShapeReference shape
		types only.
		\return True if branch selected, false otherwise.
	*/
	bool IsBranchSelected( )
	{
		if ( m_type == XSI::siICEShapeReference )
		{
			return m_description.m_shapeReference.m_bBranch;
		}
		return false;
	}

	/*! Equality operator tests the strict equality of this shape with the specified shape.
	\param in_shape Operand \link MATH::CShape CShape\endlink.
	\return true if equal else false.
	*/
	bool operator == (const CShape & in_shape )const
	{
		if( m_type != in_shape.m_type )
		{
			return false;
		}

		switch( m_type )
		{
			case XSI::siICEShapeInstance:
			{
				return m_description.m_shapeInstance == in_shape.m_description.m_shapeInstance;
			}
			break;

			case XSI::siICEShapeReference:
			{
				return m_description.m_shapeReference == in_shape.m_description.m_shapeReference;
			}
			break;
		}
		return true;
	}
	
	/*! Set as shape instance
		\param in_instanceIndex Instance index
		\param in_rbdType Type for Rigid Body Dynamics
		\since 12.0 (2014)
	*/
	void SetAsInstance(ULONG in_instanceIndex)
	{
		m_type = (unsigned char)XSI::siICEShapeInstance;
		m_description.m_shapeInstance.m_nInstanceIndex = in_instanceIndex;
	}

	/*! Set as shape reference
		\param in_objectId Object Id
		\param in_branch Branch
		\param in_rbdType Type for Rigid Body Dynamics
		\since 12.0 (2014)
	*/
	void SetAsReference(ULONG in_objectId, bool in_branch)
	{
		m_type = (unsigned char)XSI::siICEShapeReference;
		m_description.m_shapeReference.m_nObjectID = in_objectId;
		m_description.m_shapeReference.m_bBranch = in_branch;
	}

	/*! Set as trivial shape type
		\param in_trivialType Trivial type
		\since 12.0 (2014)
	*/
	void SetAsTrivial( XSI::siICEShapeType in_trivialType ) 
	{ 
		m_type = (unsigned char)in_trivialType;  
	}

	/*! Returns the shape type.
	\return One of the ::siICEShapeType enum values representing the shape type.
	*/
	XSI::siICEShapeType GetType() const { return (XSI::siICEShapeType)m_type;}

	//! Get the reference shape description
	const ParameterReference& GetReferenceDescription() const
	{
		assert( m_type == (unsigned char)XSI::siICEShapeReference);
		return m_description.m_shapeReference;
	}
	
	//! Get the instance shape description
	const ParameterInstance& GetInstanceDescription() const
	{
		assert( m_type == (unsigned char)XSI::siICEShapeInstance);
		return m_description.m_shapeInstance;
	}

	private:
	union ParameterUnion
	{
		ParameterInstance	m_shapeInstance;
		ParameterReference	m_shapeReference;
	};

	unsigned char m_type; // XSI::siICEShapeType m_type;
	ParameterUnion m_description;
};

}; // MATH
}; // XSI

#endif // __XSISHAPE_H__
