//*****************************************************************************
/*!
   \file xsi_iceattribute.h
   \brief ICEAttribute class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIICEATTRIBUTE_H__
#define __XSIICEATTRIBUTE_H__

#include <xsi_siobject.h>

namespace XSI {

class CBaseICEAttributeDataArray;
class CBitArray;

//*****************************************************************************
/*! \class ICEAttribute xsi_iceattribute.h
	\brief The ICEAttribute object represents an attribute data set (a collection of
	information used in the ICE system, such as Age, PointPosition, NbrPolygons, etc.).

	Attribute data sets belong to scene objects such as geometries and properties.
	Some attributes are built-in, others may be user-defined. ICEAttribute objects can
	be accessed through Geometry::GetICEAttributes and ProjectItem::GetICEAttributes.

	\note ICE is pretty strict about optimization so if an attribute is not being used to 
	drive something visible in the scene, it will not get pulled. You must force ICE to require
	the underlying attribute in order to access the %ICEAttribute object.

	\sa Geometry::GetICEAttributes, ProjectItem::GetICEAttributes, ICENode, ICETree
	\since 7.0

	\eg %This example demonstrates how to log all the ICEAttributes of a geometry.
	\code
	CValue CreatePrim( const CString& in_presetobj, const CString& in_geometrytype, const CString& in_name, const CString& in_parent );

	Application xsi;

	CreatePrim( L"Cone", L"MeshSurface", L"", L"");
	Selection selection = xsi.GetSelection();

	X3DObject cone = selection[0];
	CRefArray attrs = cone.GetActivePrimitive().GetGeometry().GetICEAttributes();

	for( ULONG i = 0; i<attrs.GetCount(); i++ )
	{
		ICEAttribute attr = attrs[i];
		xsi.LogMessage( L"*******************************************************************" );
		xsi.LogMessage( L"Name: " + attr.GetName() );
		xsi.LogMessage( L"DataType: " + CString(attr.GetDataType()) );
		xsi.LogMessage( L"StructType: " + CString(attr.GetStructureType()) );
		xsi.LogMessage( L"ContextType: " + CString(attr.GetContextType()) );
		xsi.LogMessage( L"IsConstant: " + CString(attr.IsConstant()) );
		xsi.LogMessage( L"Readonly: " + CString(attr.IsReadonly()) );
		xsi.LogMessage( L"AttributeCategory: " + CString(attr.GetAttributeCategory()) );
		xsi.LogMessage( L"Element count: " + CString(attr.GetElementCount()) );
	}

	// Helper
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

	\endcode
 */
//*****************************************************************************

class SICPPSDKDECL ICEAttribute : public SIObject
{
public:
	friend class CBaseICEAttributeDataArray;

	/*! Default constructor. */
	ICEAttribute();

	/*! Default destructor. */
	~ICEAttribute();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	ICEAttribute(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	ICEAttribute(const ICEAttribute& in_obj);

	/*! Returns true if a given class type is compatible with this API class.
	\param in_ClassID class type.
	\return true if the class is compatible, false otherwise.
	*/
	bool IsA( siClassID in_ClassID) const;

	/*! Returns the type of the API class.
	\return The class type.
	*/
	siClassID GetClassID() const;

	/*! Creates an object from another object. The newly created object is set to
	empty if the input object is not compatible.
	\param in_obj constant class object.
	\return The new ICEAttribute object.
	*/
	ICEAttribute& operator=(const ICEAttribute& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new ICEAttribute object.
	*/
	ICEAttribute& operator=(const CRef& in_ref);

	/*! Returns a boolean value indicating whether the data for this attribute is
	ready to be used (true) or not (false). 
	\note 
	\return true if the data has been defined. If the underlying attribute is not required by ICE, 
	IsDefined returns false.
	 */
	bool IsDefined( ) const;

	/*! Returns a bool value indicating whether the data for this attribute is constant (true) or not (false).
	\return Attribute constant flag.
	 */
	bool IsConstant( ) const;

	/*! Returns a bool value indicating whether the data for this attribute is read-only (true) or not (false).
	\return Attribute read-only flag.
	 */
	bool IsReadonly( ) const;

	/*! Returns the type for this attribute data as an \link siICENodeDataType \endlink value.
	\return Attribute data type.
	 */
	XSI::siICENodeDataType GetDataType( ) const;

	/*! Returns the type for this attribute data as an \link siICENodeStructureType \endlink value. The returned
	type identifies how the data is structured: data can be a single element or an array.
	\return Attribute data structure type.
	 */
	XSI::siICENodeStructureType GetStructureType( ) const;

	/*! Returns the context type of this attribute data as an \link siICENodeContextType \endlink value. The
	returned type identifies the element set associated with the data (cardinality), such as vertices, polygons,
	or newly created particles.
	\return Attribute data context type.
	 */
	XSI::siICENodeContextType GetContextType( ) const;

	/*! Returns the category as an \link siICEAttributeCategory \endlink value describing how the attribute is defined.
	\return Attribute category type.
	 */
	XSI::siICEAttributeCategory GetAttributeCategory( ) const;

	/*! Returns the number of elements defined for this attribute given its context type \link siICENodeContextType \endlink.
	\return Number of elements.
	\sa ICEAttribute::GetContextType
	 */
	ULONG GetElementCount( ) const;

	/*! Returns CBaseICEAttributeDataArray object containing the data defined by this attribute. Returns an empty array if the structure type is not siICENodeStructureArray.
	\param io_dataArray Newly created array of ICEAttribute data.

	\return CStatus::OK Success.
	\return CStatus::False Attribute has no data set yet.
	\return CStatus::InvalidArgument \c io_dataArray is invalid. This is typically caused by an invalid type match between
		\c io_dataArray and this ICEAttribute.
	\return CStatus::Fail Operation failed.

	\eg %This example shows how to access all attribute data on a geometry.
	\code
		CValue CreatePrim( const CString& in_presetobj, const CString& in_geometrytype, const CString& in_name, const CString& in_parent );

		template < class T >
		class CICEAttributeDataLogger
		{
			public:
			static void Log( ICEAttribute& attr )
			{
				CICEAttributeDataArray< T > data;
				attr.GetDataArray( data );

				Application xsi;
				for( ULONG i=0; i<data.GetCount( ); i++ )
				{
					xsi.LogMessage( CString( data[ i ] ) );
				}
			}
		};

		template < >
		class CICEAttributeDataLogger< XSI::CString >
		{
			public:
			static void Log( ICEAttribute& attr )
			{
				CICEAttributeDataArrayString data;
				attr.GetDataArray( data );

				Application xsi;
				for( ULONG i=0; i<data.GetCount( ); i++ )
				{
					xsi.LogMessage( data[ i ] );
				}
			}
		};

		Application xsi;

		CreatePrim( L"Cone", L"MeshSurface", L"", L"");
		Selection selection = xsi.GetSelection();

		X3DObject cone = selection[0];
		CRefArray attrs = cone.GetActivePrimitive().GetGeometry().GetICEAttributes();

		for( ULONG i = 0; i<attrs.GetCount(); i++ )
		{
			ICEAttribute attr = attrs[i];
			xsi.LogMessage( L"*******************************************************************" );
			xsi.LogMessage( L"Name: " + attr.GetName() );
			xsi.LogMessage( L"DataType: " + CString(attr.GetDataType()) );
			xsi.LogMessage( L"StructType: " + CString(attr.GetStructureType()) );
			xsi.LogMessage( L"ContextType: " + CString(attr.GetContextType()) );
			xsi.LogMessage( L"IsConstant: " + CString(attr.IsConstant()) );
			xsi.LogMessage( L"Readonly: " + CString(attr.IsReadonly()) );
			xsi.LogMessage( L"AttributeCategory: " + CString(attr.GetAttributeCategory()) );
			xsi.LogMessage( L"Element count: " + CString(attr.GetElementCount()) );

			if ( attr.GetStructureType() != XSI::siICENodeStructureSingle )
			{
				// Only process 1D array data
				continue;
			}

			switch( attr.GetDataType() )
			{
				case XSI::siICENodeDataFloat: CICEAttributeDataLogger<float>::Log( attr ); break;
				case XSI::siICENodeDataLong: CICEAttributeDataLogger<LONG>::Log( attr ); break;
				case XSI::siICENodeDataBool: CICEAttributeDataLogger<bool>::Log( attr ); break;
				case XSI::siICENodeDataVector2: CICEAttributeDataLogger<XSI::MATH::CVector2f>::Log( attr ); break;
				case XSI::siICENodeDataVector3: CICEAttributeDataLogger<XSI::MATH::CVector3f>::Log( attr ); break;
				case XSI::siICENodeDataVector4: CICEAttributeDataLogger<XSI::MATH::CVector4f>::Log( attr ); break;
				case XSI::siICENodeDataQuaternion: CICEAttributeDataLogger<XSI::MATH::CQuaternionf>::Log( attr ); break;
				case XSI::siICENodeDataRotation: CICEAttributeDataLogger<XSI::MATH::CRotationf>::Log( attr ); break;
				case XSI::siICENodeDataMatrix33: CICEAttributeDataLogger<XSI::MATH::CMatrix3f>::Log( attr ); break;
				case XSI::siICENodeDataMatrix44: CICEAttributeDataLogger<XSI::MATH::CMatrix4f>::Log( attr ); break;
				case XSI::siICENodeDataColor4: CICEAttributeDataLogger<XSI::MATH::CColor4f>::Log( attr ); break;
				case XSI::siICENodeDataString: CICEAttributeDataLogger<XSI::CString>::Log( attr ); break;
			};
		}

		// Helper
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
	\endcode
	\eg %This example demonstrates how to set the data on a geometry attribute
	\code
		CValue CreatePrim( const CString& in_presetobj, const CString& in_geometrytype, const CString& in_name, const CString& in_parent );

		template < class T >
		class CICEAttributeDataLogger
		{
			public:
			static void Log( ICEAttribute& attr )
			{
				CICEAttributeDataArray< T > data;
				attr.GetDataArray( data );

				Application xsi;
				for( ULONG i=0; i<data.GetCount( ); i++ )
				{
					xsi.LogMessage( CString( data[ i ] ) );
				}
			}
		};

		template < >
		class CICEAttributeDataLogger< XSI::CString >
		{
			public:
			static void Log( ICEAttribute& attr )
			{
				CICEAttributeDataArrayString data;
				attr.GetDataArray( data );

				Application xsi;
				for( ULONG i=0; i<data.GetCount( ); i++ )
				{
					xsi.LogMessage( data[ i ] );
				}
			}
		};

		Application xsi;
		X3DObject cone( CreatePrim( L"Cone", L"MeshSurface", L"", L"") );

		// The number of elements on the attribute is governed by siICENodeContextComponent0D which is equivalent to the number of vertices on the cone.
		ICEAttribute attr = cone.GetActivePrimitive().GetGeometry().AddICEAttribute( "DataArrayMat44", XSI::siICENodeDataMatrix44, XSI::siICENodeStructureSingle, XSI::siICENodeContextComponent0D );
		MATH::CMatrix4f Mat4A( 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 );
		MATH::CMatrix4f Mat4B( 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 );

		CICEAttributeDataArray< MATH::CMatrix4f > data;
		attr.GetDataArray( data );

		data[0] = Mat4A;
		data[4] = Mat4B;

		CICEAttributeDataLogger<MATH::CMatrix4f>::Log( attr );	

		{
			// Example with memcpy for 6 elements 
			MATH::CMatrix4f l_Values[6] = { Mat4A, Mat4A, Mat4A, Mat4B, Mat4B, Mat4B };
			memcpy( &data[0], &l_Values[0], 6 * sizeof(MATH::CMatrix4f) );

			CICEAttributeDataLogger<MATH::CMatrix4f>::Log( attr );	
		}

		// Helper
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
	\endcode

	\sa ICEAttribute::GetStructureType
	 */
	CStatus GetDataArray( CBaseICEAttributeDataArray& io_dataArray ) const;

	/*! Returns a read-only CBaseICEAttributeDataArray object containing the data defined by this attribute. The data
	can be accessed in multiple chunks given an index offset that refers to the attribute's global data buffer and
	a chunk size. GetDataArrayChunk is particularly useful for minimizing the memory allocation required to store
	the data retrieved from a very large data set. An empty array is returned if the attribute's structure type is
	not a singleton.

	\param in_nOffset Index offset into the attribute data buffer.
	\param in_nSize Size of chunk to gather.
	\param io_dataArray Newly created array of ICEAttribute data.

	\return CStatus::OK Success.
	\return CStatus::False Attribute has no data set yet.
	\return CStatus::Fail Operation failed.

	\eg %This example shows how to access all attribute data of a geometry in chunk.
	\code
		CValue CreatePrim( const CString& in_presetobj, const CString& in_geometrytype, const CString& in_name, const CString& in_parent )

		template < class T >
		class CICEAttributeDataChunkLogger
		{
			public:
			static void Log( ICEAttribute& attr, ULONG in_nOffset, ULONG in_nSize )
			{
				CICEAttributeDataArray< T > data;
				attr.GetDataArrayChunk( in_nOffset, in_nSize, data );

				Application xsi;
				xsi.LogMessage( L"Chunk size: " + CString(data.GetCount( )) );
				for( ULONG i=0; i<data.GetCount( ); i++ )
				{
					xsi.LogMessage( CString( data[ i ] ) );
				}
			}
		};

		template < >
		class CICEAttributeDataChunkLogger< XSI::CString >
		{
			public:
			static void Log( ICEAttribute& attr, ULONG in_nOffset, ULONG in_nSize )
			{
				CICEAttributeDataArrayString data;
				attr.GetDataArrayChunk( in_nOffset, in_nSize, data );
				
				Application xsi;
				xsi.LogMessage( L"Chunk size: " + CString(data.GetCount( )) );
				for( ULONG i=0; i<data.GetCount( ); i++ )
				{
					xsi.LogMessage( data[ i ] );
				}
			}
		};

		Application xsi;

		CreatePrim( L"Cone", L"MeshSurface", L"", L"");
		Selection selection = xsi.GetSelection();

		X3DObject cone = selection[0];
		CRefArray attrs = cone.GetActivePrimitive().GetGeometry().GetICEAttributes();

		ULONG nChunkCount = 4;
		for( ULONG i = 0; i<attrs.GetCount(); i++ )
		{
			ICEAttribute attr = attrs[i];

			if ( attr.GetStructureType() != XSI::siICENodeStructureSingle )
			{
				// Only process 1D array data
				continue;
			}

			xsi.LogMessage( L"*******************************************************************" );
			xsi.LogMessage( L"Name: " + attr.GetName() );
			xsi.LogMessage( L"DataType: " + CString(attr.GetDataType()) );
			xsi.LogMessage( L"StructType: " + CString(attr.GetStructureType()) );
			xsi.LogMessage( L"ContextType: " + CString(attr.GetContextType()) );
			xsi.LogMessage( L"IsConstant: " + CString(attr.IsConstant()) );
			xsi.LogMessage( L"Readonly: " + CString(attr.IsReadonly()) );
			xsi.LogMessage( L"AttributeCategory: " + CString(attr.GetAttributeCategory()) );
			xsi.LogMessage( L"Element count: " + CString(attr.GetElementCount()) );

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

				switch( attr.GetDataType() )
				{
					case XSI::siICENodeDataFloat: CICEAttributeDataChunkLogger<float>::Log( attr, nOffset, nChunkSize ); break;
					case XSI::siICENodeDataLong: CICEAttributeDataChunkLogger<LONG>::Log( attr, nOffset, nChunkSize ); break;
					case XSI::siICENodeDataBool: CICEAttributeDataChunkLogger<bool>::Log( attr, nOffset, nChunkSize ); break;
					case XSI::siICENodeDataVector2: CICEAttributeDataChunkLogger<XSI::MATH::CVector2f>::Log( attr, nOffset, nChunkSize ); break;
					case XSI::siICENodeDataVector3: CICEAttributeDataChunkLogger<XSI::MATH::CVector3f>::Log( attr, nOffset, nChunkSize ); break;
					case XSI::siICENodeDataVector4: CICEAttributeDataChunkLogger<XSI::MATH::CVector4f>::Log( attr, nOffset, nChunkSize ); break;
					case XSI::siICENodeDataQuaternion: CICEAttributeDataChunkLogger<XSI::MATH::CQuaternionf>::Log( attr, nOffset, nChunkSize ); break;
					case XSI::siICENodeDataRotation: CICEAttributeDataChunkLogger<XSI::MATH::CRotationf>::Log( attr, nOffset, nChunkSize ); break;
					case XSI::siICENodeDataMatrix33: CICEAttributeDataChunkLogger<XSI::MATH::CMatrix3f>::Log( attr, nOffset, nChunkSize ); break;
					case XSI::siICENodeDataMatrix44: CICEAttributeDataChunkLogger<XSI::MATH::CMatrix4f>::Log( attr, nOffset, nChunkSize ); break;
					case XSI::siICENodeDataColor4: CICEAttributeDataChunkLogger<XSI::MATH::CColor4f>::Log( attr, nOffset, nChunkSize ); break;
					case XSI::siICENodeDataString: CICEAttributeDataChunkLogger<XSI::CString>::Log( attr, nOffset, nChunkSize ); break;
				};

				nOffset += nChunkSize;
			}
		}

		// Helper
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

	\endcode
	\sa ICEAttribute::GetStructureType
	 */
	CStatus GetDataArrayChunk( ULONG in_nOffset, ULONG in_nSize, CBaseICEAttributeDataArray& io_dataArray ) const;

	/*! Returns a read-only CBaseICEAttributeDataArray2D object containing the 2D data defined by this attribute. Returns
	an empty array if the attribute's structure type is not a 2D array.

	\param io_dataArray Newly created array of ICEAttribute data.

	\return CStatus::OK Success.
	\return CStatus::False Attribute has no data set yet.
	\return CStatus::Fail Operation failed.

	\eg %This example shows how to access all attribute data of an envelope weight property.
	\code
	CValue CreatePrim( const CString& in_presetobj, const CString& in_geometrytype, const CString& in_name, const CString& in_parent );
	CValue Create2DSkeleton( const CValue& in_rx, const CValue& in_ry, const CValue& in_rz, const CValue& in_ex, const CValue& in_ey, const CValue& in_ez, const CValue& in_nx, const CValue& in_ny, const CValue& in_nz, const CValue& in_viewtype,  CValue& out_bone,  CValue& out_effector );
	CValue AppendBone( const CValue&  in_inputobjs, const CValue& in_ex, const CValue& in_ey, const CValue& in_ez, bool in_pin );
	CValue ApplyFlexEnv( const CValue&  in_connectionset, bool in_assignnewdeformers,  XSI::siConstructionMode & io_constructionmode );
	void SelectObj( const CValue&  in_selectionlist, const CString& in_hierarchylevel, bool in_checkobjectselectability ) ;

	template < class T >
	class CICEAttributeData2DLogger
	{
		public:
		static void Log( ICEAttribute& attr )
		{
			CICEAttributeDataArray2D< T > data2D;
			attr.GetDataArray2D( data2D );

			Application xsi;
			for( ULONG i=0; i<data2D.GetCount( ); i++ )
			{
				CICEAttributeDataArray< T > data;
				data2D.GetSubArray( i, data );
				for( ULONG j=0; j<data.GetCount( ); j++ )
				{
					xsi.LogMessage( CString( data[ j ] ) );
				}
			}
		}
	};

	template < >
	class CICEAttributeDataChunk2DLogger<XSI::CString>
	{
		public:
		static void Log( ICEAttribute& attr, ULONG in_nOffset, ULONG in_nSize )
		{
			CICEAttributeDataArray2DString data2D;
			attr.GetDataArray2DChunk( in_nOffset, in_nSize, data2D );

			Application xsi;
			xsi.LogMessage( L"Chunk size: " + CString(data2D.GetCount( )) );
			for( ULONG i=0; i<data2D.GetCount( ); i++ )
			{
				CICEAttributeDataArrayString data;
				data2D.GetSubArray( i, data );
				for( ULONG j=0; j<data.GetCount( ); j++ )
				{
					xsi.LogMessage( data[ j ] );
				}
			}
		}
	};

	Application xsi;

	X3DObject cone = CreatePrim( L"Cone", L"MeshSurface", L"", L"");
	Create2DSkeleton( 2.95, 3.34, -0.33, 4.73, 0.0, 0.0, -5.71, 0, 0, 4, CValue(""), CValue(""));
	AppendBone( L"eff", 3.70, -3.02, 0.30, L"");

	XSI::siConstructionMode mode = siConstructionModeModeling;
	ApplyFlexEnv( L"cone;bone,bone1,eff", true, mode );
	SelectObj( L"cone.polymsh.cls.EnvelopWeightCls.Envelope_Weights", L"", L"" );

	cone.GetActivePrimitive().GetGeometry(0);
	ProjectItem EnvProp = xsi.GetSelection()[0];

	CRefArray attrs = EnvProp.GetICEAttributes();

	for( ULONG i = 0; i<attrs.GetCount(); i++ )
	{
		ICEAttribute attr = attrs[i];

		if ( attr.GetStructureType() != XSI::siICENodeStructureArray )
		{
			// Only process 2D array data
			continue;
		}

		xsi.LogMessage( L"*******************************************************************" );
		xsi.LogMessage( L"Name: " + attr.GetName() );
		xsi.LogMessage( L"DataType: " + CString(attr.GetDataType()) );
		xsi.LogMessage( L"StructType: " + CString(attr.GetStructureType()) );
		xsi.LogMessage( L"ContextType: " + CString(attr.GetContextType()) );
		xsi.LogMessage( L"IsConstant: " + CString(attr.IsConstant()) );
		xsi.LogMessage( L"Readonly: " + CString(attr.IsReadonly()) );
		xsi.LogMessage( L"AttributeCategory: " + CString(attr.GetAttributeCategory()) );
		xsi.LogMessage( L"Element count: " + CString(attr.GetElementCount()) );

		switch( attr.GetDataType() )
		{
			case XSI::siICENodeDataFloat: CICEAttributeData2DLogger<float>::Log( attr ); break;
			case XSI::siICENodeDataLong: CICEAttributeData2DLogger<LONG>::Log( attr ); break;
			case XSI::siICENodeDataBool: CICEAttributeData2DLogger<bool>::Log( attr ); break;
			case XSI::siICENodeDataVector2: CICEAttributeData2DLogger<XSI::MATH::CVector2f>::Log( attr ); break;
			case XSI::siICENodeDataVector3: CICEAttributeData2DLogger<XSI::MATH::CVector3f>::Log( attr ); break;
			case XSI::siICENodeDataVector4: CICEAttributeData2DLogger<XSI::MATH::CVector4f>::Log( attr ); break;
			case XSI::siICENodeDataQuaternion: CICEAttributeData2DLogger<XSI::MATH::CQuaternionf>::Log( attr ); break;
			case XSI::siICENodeDataRotation: CICEAttributeData2DLogger<XSI::MATH::CRotationf>::Log( attr ); break;
			case XSI::siICENodeDataMatrix33: CICEAttributeData2DLogger<XSI::MATH::CMatrix3f>::Log( attr ); break;
			case XSI::siICENodeDataMatrix44: CICEAttributeData2DLogger<XSI::MATH::CMatrix4f>::Log( attr ); break;
			case XSI::siICENodeDataColor4: CICEAttributeData2DLogger<XSI::MATH::CColor4f>::Log( attr ); break;
			case XSI::siICENodeDataString: CICEAttributeData2DLogger<XSI::CString>::Log( attr ); break;
			
		};
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

	CValue Create2DSkeleton( const CValue& in_rx, const CValue& in_ry, const CValue& in_rz, const CValue& in_ex, const CValue& in_ey, const CValue& in_ez, const CValue& in_nx, const CValue& in_ny, const CValue& in_nz, const CValue& in_viewtype,  CValue& out_bone,  CValue& out_effector )
	{
		CValueArray args(12);
		CValue retval;

		args[0]= in_rx;
		args[1]= in_ry;
		args[2]= in_rz;
		args[3]= in_ex;
		args[4]= in_ey;
		args[5]= in_ez;
		args[6]= in_nx;
		args[7]= in_ny;
		args[8]= in_nz;
		args[9]= in_viewtype;

		Application app;
		app.ExecuteCommand( L"Create2DSkeleton", args, retval );

		out_bone = args[10];
		out_effector = args[11];
		return retval;
	}

	CValue AppendBone( const CValue&  in_inputobjs, const CValue& in_ex, const CValue& in_ey, const CValue& in_ez, bool in_pin )
	{
		CValueArray args(5);
		CValue retval;

		args[0]= in_inputobjs;
		args[1]= in_ex;
		args[2]= in_ey;
		args[3]= in_ez;
		args[4]= in_pin;

		Application app;
		app.ExecuteCommand( L"AppendBone", args, retval );

		return retval;
	}

	CValue ApplyFlexEnv( const CValue&  in_connectionset, bool in_assignnewdeformers,  XSI::siConstructionMode & io_constructionmode )
	{
		CValueArray args(3);
		CValue retval;

		args[0]= in_connectionset;
		args[1]= in_assignnewdeformers;
		args[2]= io_constructionmode;

		Application app;
		app.ExecuteCommand( L"ApplyFlexEnv", args, retval );

		io_constructionmode = (XSI::siConstructionMode)(LONG)args[2];
		return retval;
	}

	void SelectObj( const CValue&  in_selectionlist, const CString& in_hierarchylevel, bool in_checkobjectselectability )
	{
		CValueArray args(3);
		CValue retval;
		args[0]= in_selectionlist;
		args[1]= in_hierarchylevel;
		args[2]= in_checkobjectselectability;

		Application app;

		CStatus st = app.ExecuteCommand( L"SelectObj", args, retval );
		return;
	}
	\endcode
	\eg %This example demonstrate how to set the data on a 2D array attribute type.
	\code
	CValue CreatePrim( const CString& in_presetobj, const CString& in_geometrytype, const CString& in_name, const CString& in_parent );

	template < class T >
	class CICEAttributeData2DLogger
	{
		public:
		static void Log( ICEAttribute& attr )
		{
			CICEAttributeDataArray2D< T > data2D;
			attr.GetDataArray2D( data2D );

			Application xsi;
			for( ULONG i=0; i<data2D.GetCount( ); i++ )
			{
				CICEAttributeDataArray< T > data;
				data2D.GetSubArray( i, data );
				for( ULONG j=0; j<data.GetCount( ); j++ )
				{
					xsi.LogMessage( CString( data[ j ] ) );
				}
			}
		}
	};
	Application xsi;
	X3DObject cone( CreatePrim( L"Cone", L"MeshSurface", L"", L"") );

	ICEAttribute attr = cone.GetActivePrimitive().GetGeometry().AddICEAttribute( "DataArray2DMat44", XSI::siICENodeDataMatrix44, XSI::siICENodeStructureArray, XSI::siICENodeContextComponent0D );
	MATH::CMatrix4f Mat4A( 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 );
	MATH::CMatrix4f Mat4B( 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 );

	CICEAttributeDataArray2D< MATH::CMatrix4f > data2D;
	attr.GetDataArray2D( data2D );

	CICEAttributeDataArray< MATH::CMatrix4f > data;
	ULONG subArraySize = 6; // This can be any number. 
	data2D.ResizeSubArray( 0, subArraySize, data);
	data[0] = Mat4A;
	data[1] = Mat4B;

	CICEAttributeData2DLogger<MATH::CMatrix4f>::Log( attr );	

	{
		// Example with memcpy for 6 elements 
		MATH::CMatrix4f l_Values[subArraySize] = { Mat4A, Mat4A, Mat4A, Mat4B, Mat4B, Mat4B };
		memcpy( &data[0], &l_Values[0], subArraySize * sizeof(MATH::CMatrix4f) );

		CICEAttributeData2DLogger<MATH::CMatrix4f>::Log( attr );	
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
	\endcode
	\sa ICEAttribute::GetStructureType
	*/
	CStatus GetDataArray2D( CBaseICEAttributeDataArray& io_dataArray ) const;

	/*! Returns CBaseICEAttributeDataArray2D object containing the 2D data defined by this attribute. The data
	can be accessed in multiple chunks given an index offset that refers to the attribute's global data buffer and a
	chunk size. GetDataArray2DChunk is particularly useful for minimizing the memory allocation required to store the
	data retrieved from a very large data set. An empty array is returned if the attribute's structure type is not a 2D array.

	\param in_nOffset Index offset into the attribute data buffer.
	\param in_nSize Size of chunk to gather.
	\param io_dataArray Newly created array of ICEAttribute data.

	\return CStatus::OK Success.
	\return CStatus::False Attribute has no data set yet.
	\return CStatus::Fail Operation failed.

	\eg %This example shows how to access all attribute data of an envelope weight property.
	\code
		CValue CreatePrim( const CString& in_presetobj, const CString& in_geometrytype, const CString& in_name, const CString& in_parent )
		CValue Create2DSkeleton( const CValue& in_rx, const CValue& in_ry, const CValue& in_rz, const CValue& in_ex, const CValue& in_ey, const CValue& in_ez, const CValue& in_nx, const CValue& in_ny, const CValue& in_nz, const CValue& in_viewtype,  CValue& out_bone,  CValue& out_effector );
		CValue AppendBone( const CValue&  in_inputobjs, const CValue& in_ex, const CValue& in_ey, const CValue& in_ez, bool in_pin );
		CValue ApplyFlexEnv( const CValue&  in_connectionset, bool in_assignnewdeformers,  XSI::siConstructionMode & io_constructionmode );
		void SelectObj( const CValue&  in_selectionlist, const CString& in_hierarchylevel, bool in_checkobjectselectability ) ;

		template < class T >
		class CICEAttributeDataChunk2DLogger
		{
			public:
			static void Log( ICEAttribute& attr, ULONG in_nOffset, ULONG in_nSize )
			{
				CICEAttributeDataArray2D< T > data2D;
				attr.GetDataArray2DChunk( in_nOffset, in_nSize, data2D );

				Application xsi;
				xsi.LogMessage( L"Chunk size: " + CString(data2D.GetCount( )) );
				for( ULONG i=0; i<data2D.GetCount( ); i++ )
				{
					CICEAttributeDataArray< T > data;
					data2D.GetSubArray( i, data );
					for( ULONG j=0; j<data.GetCount( ); j++ )
					{
						xsi.LogMessage( CString( data[ j ] ) );
					}
				}
			}
		};

		template < >
		class CICEAttributeDataChunk2DLogger<XSI::CString>
		{
			public:
			static void Log( ICEAttribute& attr, ULONG in_nOffset, ULONG in_nSize )
			{
				CICEAttributeDataArray2DString data2D;
				attr.GetDataArray2DChunk( in_nOffset, in_nSize, data2D );

				Application xsi;
				xsi.LogMessage( L"Chunk size: " + CString(data2D.GetCount( )) );
				for( ULONG i=0; i<data2D.GetCount( ); i++ )
				{
					CICEAttributeDataArrayString data;
					data2D.GetSubArray( i, data );
					for( ULONG j=0; j<data.GetCount( ); j++ )
					{
						xsi.LogMessage( data[ j ] );
					}
				}
			}
		};

		Application xsi;

		X3DObject cone = CreatePrim( L"Cone", L"MeshSurface", L"", L"");
		Create2DSkeleton( 2.95, 3.34, -0.33, 4.73, 0.0, 0.0, -5.71, 0, 0, 4, CValue(""), CValue(""));
		AppendBone( L"eff", 3.70, -3.02, 0.30, L"");

		XSI::siConstructionMode mode = siConstructionModeModeling;
		ApplyFlexEnv( L"cone;bone,bone1,eff", true, mode );
		SelectObj( L"cone.polymsh.cls.EnvelopWeightCls.Envelope_Weights", L"", L"" );

		cone.GetActivePrimitive().GetGeometry(0);

		ProjectItem EnvProp = xsi.GetSelection()[0];

		CRefArray attrs = EnvProp.GetICEAttributes();

		ULONG nChunkCount = 4;
		for( ULONG i = 0; i<attrs.GetCount(); i++ )
		{
			ICEAttribute attr = attrs[i];

			if ( attr.GetStructureType() != XSI::siICENodeStructureArray )
			{
				// Only process 2D array data
				continue;
			}

			xsi.LogMessage( L"*******************************************************************" );
			xsi.LogMessage( L"Name: " + attr.GetName() );
			xsi.LogMessage( L"DataType: " + CString(attr.GetDataType()) );
			xsi.LogMessage( L"StructType: " + CString(attr.GetStructureType()) );
			xsi.LogMessage( L"ContextType: " + CString(attr.GetContextType()) );
			xsi.LogMessage( L"IsConstant: " + CString(attr.IsConstant()) );
			xsi.LogMessage( L"Readonly: " + CString(attr.IsReadonly()) );
			xsi.LogMessage( L"AttributeCategory: " + CString(attr.GetAttributeCategory()) );
			xsi.LogMessage( L"Element count: " + CString(attr.GetElementCount()) );

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

				switch( attr.GetDataType() )
				{
					case XSI::siICENodeDataFloat: CICEAttributeDataChunk2DLogger<float>::Log( attr, nOffset, nChunkSize ); break;
					case XSI::siICENodeDataLong: CICEAttributeDataChunk2DLogger<LONG>::Log( attr, nOffset, nChunkSize ); break;
					case XSI::siICENodeDataBool: CICEAttributeDataChunk2DLogger<bool>::Log( attr, nOffset, nChunkSize ); break;
					case XSI::siICENodeDataVector2: CICEAttributeDataChunk2DLogger<XSI::MATH::CVector2f>::Log( attr, nOffset, nChunkSize ); break;
					case XSI::siICENodeDataVector3: CICEAttributeDataChunk2DLogger<XSI::MATH::CVector3f>::Log( attr, nOffset, nChunkSize ); break;
					case XSI::siICENodeDataVector4: CICEAttributeDataChunk2DLogger<XSI::MATH::CVector4f>::Log( attr, nOffset, nChunkSize ); break;
					case XSI::siICENodeDataQuaternion: CICEAttributeDataChunk2DLogger<XSI::MATH::CQuaternionf>::Log( attr, nOffset, nChunkSize ); break;
					case XSI::siICENodeDataRotation: CICEAttributeDataChunk2DLogger<XSI::MATH::CRotationf>::Log( attr, nOffset, nChunkSize ); break;
					case XSI::siICENodeDataMatrix33: CICEAttributeDataChunk2DLogger<XSI::MATH::CMatrix3f>::Log( attr, nOffset, nChunkSize ); break;
					case XSI::siICENodeDataMatrix44: CICEAttributeDataChunk2DLogger<XSI::MATH::CMatrix4f>::Log( attr, nOffset, nChunkSize ); break;
					case XSI::siICENodeDataColor4: CICEAttributeDataChunk2DLogger<XSI::MATH::CColor4f>::Log( attr, nOffset, nChunkSize ); break;
					case XSI::siICENodeDataString: CICEAttributeDataChunk2DLogger<XSI::CString>::Log( attr, nOffset, nChunkSize ); break;
				};

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

		CValue Create2DSkeleton( const CValue& in_rx, const CValue& in_ry, const CValue& in_rz, const CValue& in_ex, const CValue& in_ey, const CValue& in_ez, const CValue& in_nx, const CValue& in_ny, const CValue& in_nz, const CValue& in_viewtype,  CValue& out_bone,  CValue& out_effector )
		{
			CValueArray args(12);
			CValue retval;

			args[0]= in_rx;
			args[1]= in_ry;
			args[2]= in_rz;
			args[3]= in_ex;
			args[4]= in_ey;
			args[5]= in_ez;
			args[6]= in_nx;
			args[7]= in_ny;
			args[8]= in_nz;
			args[9]= in_viewtype;

			Application app;
			app.ExecuteCommand( L"Create2DSkeleton", args, retval );

			out_bone = args[10];
			out_effector = args[11];
			return retval;
		}

		CValue AppendBone( const CValue&  in_inputobjs, const CValue& in_ex, const CValue& in_ey, const CValue& in_ez, bool in_pin )
		{
			CValueArray args(5);
			CValue retval;

			args[0]= in_inputobjs;
			args[1]= in_ex;
			args[2]= in_ey;
			args[3]= in_ez;
			args[4]= in_pin;

			Application app;
			app.ExecuteCommand( L"AppendBone", args, retval );

			return retval;
		}

		CValue ApplyFlexEnv( const CValue&  in_connectionset, bool in_assignnewdeformers,  XSI::siConstructionMode & io_constructionmode )
		{
			CValueArray args(3);
			CValue retval;

			args[0]= in_connectionset;
			args[1]= in_assignnewdeformers;
			args[2]= io_constructionmode;

			Application app;
			app.ExecuteCommand( L"ApplyFlexEnv", args, retval );

			io_constructionmode = (XSI::siConstructionMode)(LONG)args[2];
			return retval;
		}

		void SelectObj( const CValue&  in_selectionlist, const CString& in_hierarchylevel, bool in_checkobjectselectability )
		{
			CValueArray args(3);
			CValue retval;
			args[0]= in_selectionlist;
			args[1]= in_hierarchylevel;
			args[2]= in_checkobjectselectability;

			Application app;

			CStatus st = app.ExecuteCommand( L"SelectObj", args, retval );
			return;
		}
	\endcode
	\sa ICEAttribute::GetStructureType
	*/
	CStatus GetDataArray2DChunk( ULONG in_nOffset, ULONG in_nSize, CBaseICEAttributeDataArray& io_dataArray ) const;

	/*! Returns an array of custom data types defined for this %ICEAttribute. Custom data types are defined by custom ICENodes and
	are used as data types for defining custom ICEPorts and ICEAttributes.
	\return Array of custom data type names. Returns an empty array if no custom types are defined on this %ICEAttribute.
	\sa ICENodeDef::DefineCustomType
	\sa ICENodePort::GetCustomDataTypes
	\since 8.0 (2010)

	\eg %This example demonstrates how to access custom data types from %ICEAttribute objects.
	\code
		Application app;

		// Loads the GridWalker custom node plug-in from the examples workgroup
		CString strWrkgrp = CUtils::BuildPath( app.GetInstallationPath(siFactoryPath ), "XSISDK", "examples", "workgroup" );
		app.AddWorkgroup( strWrkgrp  );

		// Opens the GridWalker scene containing custom data types
		CValueArray args(2);
		CValue retval;
		args[0] = CUtils::BuildPath( strWrkgrp, "Addons", "CustomICENodes", "Data", "Project", "Scenes", "GridWalker" ) + ".scn";
		args[2] = false;
		app.ExecuteCommand( "OpenScene", args, retval );

		// Logs custom data type
		CStringArray strNoFamily;
		CString strNoType;
		Geometry geom( app.GetActiveSceneRoot().FindChild("grid", strNoType, strNoFamily).GetActivePrimitive().GetGeometry() );
		ICEAttribute attrib = geom.GetICEAttributeFromName( "GridWalkerState" );
		app.LogMessage( CString("Custom data type for attribute <") + attrib.GetName() + ">: " + attrib.GetCustomDataTypes()[0] );

		// Output:
		// # INFO : Custom data type for attribute <GridWalkerState>: GridWalkState_v1
	\endcode
	*/
	CStringArray GetCustomDataTypes( ) const;


	/*! Returns a boolean value indicating whether the attribute is marked as always evaluated. If it is true than attribute will be always evaluated regardless 
	 of ICE optimization which excludes attributes from evaluation which are not required for data visualization
	\note 
	\return true if attribute is marked as always evaluated. 
	\since 13.0 (2015)
	 */
	bool IsAlwaysEvaluated( ) const;

	/*! Set/Reset attribute as always evaluated. If it is true than attribute will be always evaluated regardless 
	 of ICE optimization which excludes attributes from evaluation which are not required for data visualization
    \param in_bAlwaysEvaluated true if attribute should be always evaluated
	\return CStatus::OK Success.
	\since 13.0 (2015)
	 */
	CStatus SetAlwaysEvaluated( bool in_bAlwaysEvaluated );
private:

	CStatus ReleaseDataArray( CBaseICEAttributeDataArray& in_dataArray );
	CStatus GetSubDataArray( CBaseICEAttributeDataArray& in_dataArray2D, ULONG in_index, CBaseICEAttributeDataArray& io_dataArray ) const;
	CStatus ResizeSubDataArray( CBaseICEAttributeDataArray& in_dataArray2D, ULONG in_index, ULONG in_nSize, CBaseICEAttributeDataArray& io_dataArray );

	CStatus GetCustomTypeData( const CBaseICEAttributeDataArray& in_dataArray, ULONG in_nIndex, const unsigned char** out_ppData, ULONG& out_nSize ) const;
	CStatus GetCustomTypeData2D( const CBaseICEAttributeDataArray& in_dataArray2D, ULONG in_nArrayIndex, ULONG in_nSubArrayIndex, const unsigned char** out_ppData, ULONG& out_nSize ) const;
	CStatus GetCustomTypeData2D( const CBaseICEAttributeDataArray& in_dataArray2D, ULONG in_nIndex, const unsigned char** out_ppData, ULONG& out_nSize ) const;

	CStatus GetStringData( const CBaseICEAttributeDataArray& in_dataArray, ULONG in_nIndex, const wchar_t** out_ppData, ULONG& out_nSize ) const;
	CStatus GetStringData2D( const CBaseICEAttributeDataArray& in_dataArray2D, ULONG in_nArrayIndex, ULONG in_nSubArrayIndex, const wchar_t** out_ppData, ULONG& out_nSize ) const;

	CStatus GetStringData2D( const CBaseICEAttributeDataArray& in_dataArray, ULONG in_nIndex, const wchar_t** out_ppData, ULONG& out_nSize ) const;
	CStatus SetStringData( const CBaseICEAttributeDataArray& in_dataArray, ULONG in_nIndex, const wchar_t* in_pData, ULONG in_nSize );

	CStatus SetStringData( CBaseICEAttributeDataArray& in_dataArray, ULONG in_nIndex, const wchar_t* in_pData, ULONG in_nSize );
	CStatus SetStringData2D( CBaseICEAttributeDataArray& in_dataArray2D, ULONG in_nArrayIndex, ULONG in_nSubArrayIndex, const wchar_t* in_pData, ULONG in_nSize );

	CStatus SetDataArrayInternal( CBaseICEAttributeDataArray& io_dataArray, CBaseICEAttributeDataArray* io_pSubDataArray, ULONG in_nOffset, const CValueArray& in_array, ULONG in_nNbElem, bool in_bIs2D );
	CStatus SetDataArrayInternal( CBaseICEAttributeDataArray& io_dataArray, CBaseICEAttributeDataArray* io_pSubDataArray, ULONG in_nOffset, void* in_array, ULONG in_nNbElem, ULONG* in_pSubArraySizes, bool in_bIs2D );

	CStatus SetCharDataArrayInternal( CBaseICEAttributeDataArray& io_dataArray, CBaseICEAttributeDataArray* io_pSubDataArray, ULONG in_nOffset, const CValueArray& in_array, const CValueArray& in_elemSizes, bool in_bIs2D );
	CStatus SetCharDataArrayInternal( CBaseICEAttributeDataArray& io_dataArray, CBaseICEAttributeDataArray* io_pSubDataArray, ULONG in_nOffset, void* in_pArray, ULONG in_nNbElem, ULONG* in_pSubArraySizes, void* in_ppElemSizes, ULONG in_nFixedElemSize, bool in_bIs2D );

	CStatus GetArrayElementInternal( const CBaseICEAttributeDataArray& in_dataArray, ULONG in_nArrayIndex, ULONG in_nSubArrayIndex, void** out_ppData, ULONG& out_ulSize ) const;
	CStatus SetArrayElementInternal( CBaseICEAttributeDataArray& in_dataArray, ULONG in_nArrayIndex, ULONG in_nSubArrayIndex, void* in_pData, ULONG in_nSize );

	CStatus GetDataArrayInternal(ULONG in_nOffset, ULONG in_nSize, CBaseICEAttributeDataArray& io_dataArray) const;

	CStatus SetSubDataArray( CBaseICEAttributeDataArray& io_dataArray2D, CBaseICEAttributeDataArray* io_pSubDataArray, ULONG in_nIndex, const CValueArray& in_array );
	CStatus SetSubDataArray( CBaseICEAttributeDataArray& io_dataArray2D, CBaseICEAttributeDataArray* io_pSubDataArray, ULONG in_nIndex, void* in_pArray, ULONG in_nCount );
	CStatus SetStringSubDataArray( CBaseICEAttributeDataArray& io_dataArray2D, CBaseICEAttributeDataArray* io_pSubDataArray, ULONG in_nIndex, const wchar_t** in_ppData, ULONG in_nCount );

	CStatus SetCustomTypeSubDataArray( CBaseICEAttributeDataArray& io_dataArray2D, CBaseICEAttributeDataArray* io_pSubDataArray, ULONG in_nIndex, const unsigned char** in_ppData, ULONG in_nCount, ULONG in_nFixedElemSize );
	CStatus SetCustomTypeSubDataArray( CBaseICEAttributeDataArray& io_dataArray2D, CBaseICEAttributeDataArray* io_pSubDataArray, ULONG in_nIndex, const unsigned char** in_ppData, ULONG in_nCount, ULONG* in_pElemSizes );

	CStatus SetBoolDataArray( CBaseICEAttributeDataArray& in_dataArray, ULONG in_nOffset, const XSI::CBitArray& in_array );
	CStatus SetBoolSubDataArray( CBaseICEAttributeDataArray& io_dataArray2D, CBaseICEAttributeDataArray* io_pSubDataArray, ULONG in_nOffset, const XSI::CBitArray& in_array );

	ICEAttribute * operator&() const;
	ICEAttribute * operator&();
};

};

#endif // __XSIICEATTRIBUTE_H__
