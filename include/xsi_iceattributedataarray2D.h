//*****************************************************************************
/*!
   \file xsi_iceattributedataarray2D.h
   \brief CICEAttributeDataArray2D classes declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIICEATTRIBUTEDATAARRAY2D_H__
#define __XSIICEATTRIBUTEDATAARRAY2D_H__

#include <sicppsdk.h>
#include <xsi_iceattributedataarray.h>
#include <xsi_vector2f.h>
#include <xsi_vector3f.h>
#include <xsi_vector4f.h>
#include <xsi_quaternionf.h>
#include <xsi_rotationf.h>
#include <xsi_matrix3f.h>
#include <xsi_matrix4f.h>
#include <xsi_color4f.h>

namespace XSI {

class ICEAttribute;

//*****************************************************************************
/*! \brief This template class encapsulates ICEAttribute data as a 2D array. %CICEAttributeDataArray2D
	objects are read-only and can be filled with the methods supplied with the ICEAttribute class.
	%CICEAttributeDataArray2D is zero-based and can be one of the following types:

	\li \ref CICEAttributeDataArray2DFloat "CICEAttributeDataArray2DFloat"
	\li \ref CICEAttributeDataArray2DLong "CICEAttributeDataArray2DLong"
	\li \ref CICEAttributeDataArray2DBool "CICEAttributeDataArray2DBool"
	\li \ref CICEAttributeDataArray2DVector2f "CICEAttributeDataArray2DVector2f"
	\li \ref CICEAttributeDataArray2DVector3f "CICEAttributeDataArray2DVector3f"
	\li \ref CICEAttributeDataArray2DVector4f "CICEAttributeDataArray2DVector4f"
	\li \ref CICEAttributeDataArray2DQuaternionf "CICEAttributeDataArray2DQuaternionf"
	\li \ref CICEAttributeDataArray2DRotationf "CICEAttributeDataArray2DRotationf"
	\li \ref CICEAttributeDataArray2DMatrix3f "CICEAttributeDataArray2DMatrix3f"
	\li \ref CICEAttributeDataArray2DMatrix4f "CICEAttributeDataArray2DMatrix4f"
	\li \ref CICEAttributeDataArray2DColor4f "CICEAttributeDataArray2DColor4f"
	\li \ref CICEAttributeDataArray2DShape "CICEAttributeDataArray2DShape"

	All types are associated to specific ICEAttribute 2D types. Therefore, you need to declare the right
	array object type that matches the ICEAttribute data type you want to access. Otherwise a runtime error
	will occur and the returned array will be empty.

	\sa ICEAttribute::GetDataArray2D, ICEAttribute::GetDataArray2DChunk,
		\ref CICEAttributeDataArray2DTypedefs "Type Definitions for CICEAttributeDataArray2D"
	\since 7.0

	\eg This example demonstrates how to iterate over the EnvelopeWeightsPerDeformer ClusterProperty
		attribute data on en envelope.
	\code
		using namespace XSI;

		X3DObject cone = CreatePrim( L"Cone", L"MeshSurface", L"", L"");
		Create2DSkeleton( 2.95, 3.34, -0.33, 4.73, 0.0, 0.0, -5.71, 0, 0, 4, CValue(""), CValue(""));
		AppendBone( L"eff", 3.70, -3.02, 0.30, L"");

		XSI::siConstructionMode mode = siConstructionModeModeling;
		ApplyFlexEnv( L"cone;bone,bone1,eff", true, mode );
		SelectObj( L"cone.polymsh.cls.EnvelopWeightCls.Envelope_Weights", L"", L"" );

		// Make sure to generate the data first
		cone.GetActivePrimitive().GetGeometry(0);

		Application xsi;
		ProjectItem envProp = xsi.GetSelection()[0];

		ICEAttribute attr = envProp.GetICEAttributeFromName( L"EnvelopeWeightsPerDeformer" );

		CICEAttributeDataArray2DFloat weight2D;
		attr.GetDataArray2D( weight2D );

		for( ULONG i=0; i<weight2D.GetCount( ); i++ )
		{
			CICEAttributeDataArray< float > weights;
			weight2D.GetSubArray( i, weights );
			for( ULONG j=0; j<weights.GetCount( ); j++ )
			{
				xsi.LogMessage( CString( weights[ j ] ) );
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

	\eg This example demonstrates how to set an ICEAttribute of structure type siICENodeStructureArray.
	\code
		using namespace XSI;

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

		template < class T >
		class CICEAttributeData2D
		{
			public:
			static void Log( ICEAttribute& attr )
			{
				Application xsi;
				xsi.LogMessage( L"*******************************************************************" );
				xsi.LogMessage( L"Name: " + attr.GetName() );
				xsi.LogMessage( L"DataType: " + CString(attr.GetDataType()) );

				CICEAttributeDataArray2D< T > data2D;
				attr.GetDataArray2D( data2D );
				
				for( ULONG i=0; i<data2D.GetCount( ); i++ )
				{
					CICEAttributeDataArray< T > data;
					data2D.GetSubArray( i, data );
					for( ULONG j=0; j<data.GetCount( ); j++ )
					{
						xsi.LogMessage( CString( j ) + "   " + CString( data[ j ] ) );
					}
				}
			}
			static void SetData( const X3DObject & in_Obj, XSI::siICENodeDataType in_DataType, const CString& in_csDataName, const T in_Value )
			{
				ICEAttribute attr = in_Obj.GetActivePrimitive().GetGeometry().AddICEAttribute( in_csDataName, in_DataType, XSI::siICENodeStructureArray, XSI::siICENodeContextComponent0D );

				CICEAttributeDataArray2D< T > data2D;
				attr.GetDataArray2D( data2D );

				CICEAttributeDataArray< T > data;
				ULONG subArraySize = 6; // This can be any number. 
				data2D.ResizeSubArray( 0 ,subArraySize ,data );

				T l_Values[subArraySize] = { in_Value, in_Value, in_Value, in_Value, in_Value, in_Value };
				memcpy( &data[0], &l_Values[0], subArraySize * sizeof(T) );

				CICEAttributeData2D<T>::Log( attr );
			}

		};

		template <  >
		class CICEAttributeData2D< bool >
		{
			public:
			static void Log( ICEAttribute& attr )
			{
				Application xsi;
				xsi.LogMessage( L"*******************************************************************" );
				xsi.LogMessage( L"Name: " + attr.GetName() );
				xsi.LogMessage( L"DataType: " + CString(attr.GetDataType()) );

				CICEAttributeDataArray2D< bool > data2D;
				attr.GetDataArray2D( data2D );
				
				for( ULONG i=0; i<data2D.GetCount( ); i++ )
				{
					CICEAttributeDataArray< bool > data;
					data2D.GetSubArray( i, data );
					for( ULONG j=0; j<data.GetCount( ); j++ )
					{
						xsi.LogMessage( CString( j ) + "   " + CString( data[ j ] ) );
					}
				}
			}
			static void SetData( const X3DObject & in_Obj, XSI::siICENodeDataType in_DataType, const CString& in_csDataName, const bool in_Value )
			{
				ICEAttribute attr = in_Obj.GetActivePrimitive().GetGeometry().AddICEAttribute( in_csDataName, in_DataType, XSI::siICENodeStructureArray, XSI::siICENodeContextComponent0D );

				CICEAttributeDataArray2D< bool > data2D;
				attr.GetDataArray2D( data2D );

				CICEAttributeDataArray< bool > data;
				ULONG subArraySize = 6; // This can be any number. 
				data2D.ResizeSubArray( 0, subArraySize, data );

				data.SetData(0, in_Value);
				data.SetData(1, !in_Value);
				data.SetData(2, in_Value);
				data.SetData(3, !in_Value);
				data.SetData(4, in_Value);
				data.SetData(5, !in_Value);

				CICEAttributeData2D<bool>::Log( attr );
			}

		};

		template < >
		class CICEAttributeData2D< XSI::CString >
		{
			public:
			static void Log( ICEAttribute& attr )
			{
				CICEAttributeDataArray2DString data2D;
				attr.GetDataArray2D( data2D );
				
				Application xsi;
				for( ULONG i=0; i<data2D.GetCount( ); i++ )
				{
					CICEAttributeDataArrayString data;
					data2D.GetSubArray( i, data );
					for( ULONG j=0; j<data.GetCount( ); j++ )
					{
						xsi.LogMessage( CString( i ) + " , " + CString( j ) + " : " +data[ j ] );
					}
				}
			}

			static void SetData( const X3DObject & in_Cone, XSI::siICENodeDataType in_DataType, const CString& in_csDataName, const XSI::CString in_Value )
			{
				ICEAttribute attr = in_Cone.GetActivePrimitive().GetGeometry().AddICEAttribute( in_csDataName, in_DataType, XSI::siICENodeStructureArray, XSI::siICENodeContextComponent0D );

				CICEAttributeDataArray2DString data2D;
				attr.GetDataArray2D( data2D );

				{
					CICEAttributeDataArrayString data;
					ULONG subArraySize = 6; // This can be any number. 
					data2D.ResizeSubArray( 0, subArraySize, data );

					data.SetData(0, in_Value);
					data.SetData(2, in_Value);
					data.SetData(4, in_Value);
				}

				{
					CICEAttributeDataArrayString data;
					ULONG subArraySize = 24; // This can be any number. 
					data2D.ResizeSubArray( 1, subArraySize, data );

					data.SetData(0, in_Value);
					data.SetData(12, in_Value);
					data.SetData(60, in_Value);
				}

				CICEAttributeData2D<XSI::CString>::Log( attr );
			}

		};

		void  SetDataArray2D( const X3DObject & in_Cone )
		{

			CICEAttributeData2D<LONG>::SetData( in_Cone, XSI::siICENodeDataLong, "TestLong", 20 );

			CICEAttributeData2D<float>::SetData( in_Cone, XSI::siICENodeDataFloat, "Testfloat", -20 );

			CICEAttributeData2D<bool>::SetData( in_Cone, XSI::siICENodeDataBool, "TestBOOL", true );
			
			MATH::CVector2f Vec2f( 20, -20);
			CICEAttributeData2D<MATH::CVector2f>::SetData( in_Cone, XSI::siICENodeDataVector2, "TestVector2", Vec2f );

			MATH::CVector3f Vec3f( 20, -20, 20);
			CICEAttributeData2D<MATH::CVector3f>::SetData( in_Cone, XSI::siICENodeDataVector3, "TestVector3", Vec3f );

			MATH::CVector4f Vec4f( 20, -20, 20, -20);
			CICEAttributeData2D<MATH::CVector4f>::SetData( in_Cone, XSI::siICENodeDataVector4, "TestVector4", Vec4f );

			MATH::CQuaternionf Quat( 20, -20, 20 ,20);
			CICEAttributeData2D<MATH::CQuaternionf>::SetData( in_Cone, XSI::siICENodeDataQuaternion, "TestQuat", Quat );

			MATH::CRotationf Rot( 45, -45, 45 );
			CICEAttributeData2D<MATH::CRotationf>::SetData( in_Cone, XSI::siICENodeDataRotation, "TestRot", Rot );

			MATH::CMatrix3f Mat3( 1, 2, 3, 4, 5, 6, 7, 8, 9);
			CICEAttributeData2D<MATH::CMatrix3f>::SetData( in_Cone, XSI::siICENodeDataMatrix33, "TestMat3", Mat3 );

			MATH::CMatrix4f Mat4( 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 );
			CICEAttributeData2D<MATH::CMatrix4f>::SetData( in_Cone, XSI::siICENodeDataMatrix44, "TestMat4", Mat4 );

			MATH::CColor4f Col4( 20, -20, 20, 1);
			CICEAttributeData2D<MATH::CColor4f>::SetData( in_Cone, XSI::siICENodeDataColor4, "TestCol4", Col4 );

			CICEAttributeData2D<CString>::SetData( in_Cone, XSI::siICENodeDataString, "TestString", "hum!" );
		}

		{
			Application xsi;
			CreatePrim( L"Cone", L"MeshSurface", L"", L"");
			Selection selection = xsi.GetSelection();
			X3DObject cone = selection[0];
			SetDataArray2D( cone );
		}
	\endcode
 */
//*****************************************************************************
template<class T>
class CICEAttributeDataArray2D : public CBaseICEAttributeDataArray
{
public:
	/*! Constructor.*/
	CICEAttributeDataArray2D( ) : CBaseICEAttributeDataArray( GetDefaultType( ), XSI::siICENodeStructureArray ) {}

	/*! Destructor.	*/
	~CICEAttributeDataArray2D( ) {}

	/*! Accessor to the encapsulated array. This operator is called when reading the data so the return value is read-only.
	\param in_index Index in the array. The index must be smaller than the number of elements in the array, otherwise the
	result is unpredictable.
	\param out_dataArray A read-only reference to a \c CICEAttributeDataArray<T> object at a specific index.
	\return CStatus::OK Success
	\return CStatus::InvalidArgument If \c in_index or \c out_dataArray is invalid.
	*/
	CStatus GetSubArray( ULONG in_index, CICEAttributeDataArray<T>& out_dataArray ) const
	{
		return GetSubDataArray( in_index, (CBaseICEAttributeDataArray&)out_dataArray );
	}

	/*! Changes the size of the sub-array at a given index and returns a new array pointing to the resized sub-array. This is only supported for writable attributes and not available for built-in attributes.
	\param in_index Index in the array. The index must be smaller than the number of elements in the array, otherwise the
	result is unpredictable. If this DataArray2D is an array chunk, \c in_nIndex \c is relative to the chunk offset.
	\param out_dataArray A reference to a \c CICEAttributeDataArray<T> object at a specific index.
	\param in_size The size of the array. 
	\return CStatus::OK Success
	\return CStatus::InvalidArgument If \c in_index or \c out_dataArray is invalid.
	\since 11.0 (2013)
	*/
	CStatus ResizeSubArray( ULONG in_index, ULONG in_size, CICEAttributeDataArray<T>& out_dataArray )
	{
		return ResizeSubDataArray( *this, in_index, in_size, (CBaseICEAttributeDataArray&)out_dataArray );
	}

	/*! Set the sub-array at a given index
	This is only supported for writable attributes and not available for built-in attributes.
	\param in_index Index in the array. The index must be smaller than the number of elements in the array, otherwise the
	result is unpredictable. If this DataArray2D is an array chunk, \c in_index \c is relative to the chunk offset.
	\param in_pArray Array containing the input data
	\return CStatus::OK Success
	\return CStatus::InvalidArgument If \c in_index, \c in_pArray or \c in_count is invalid.
	\since 12.0 (2014)
	*/
	CStatus SetSubArray( ULONG in_index, const T* in_pArray, ULONG in_count );

	/*! Set all the values in the 2D ICE attribute

	\param in_ppArray Input 2D data array
	\param in_nbSubArrays Number of subarrays
	\param in_pSubArraySizes Sizes of the subarrays

	\return CStatus::OK Success.
	\return CStatus::InvalidArgument If \c in_ppArray, \c in_nbSubArrays or \c in_pSubArraySizes is invalid.
	\return CStatus::Fail Operation failed.
	\since 12.0 (2014)

	\eg This example demonstrates how to set the whole 2D array
	\code
		Application xsi;
		Model root = xsi.GetActiveSceneRoot();
		X3DObject grid( CreatePrim("Grid", "MeshSurface",  L"",  L""));

		SetValue("grid.grid.ulength", 256);
		SetValue("grid.grid.vlength", 256);
		SetValue("grid.polymsh.geom.subdivu", 256);
		SetValue("grid.polymsh.geom.subdivv", 256);

		ICEAttribute attr = grid.GetActivePrimitive().GetGeometry().AddICEAttribute( "DataArrayLong", XSI::siICENodeDataLong, XSI::siICENodeStructureArray, XSI::siICENodeContextComponent0D );

		CString l_connSet(L"grid");
		ApplyOp( L"ICETree", l_connSet, siConstructionModeModeling );

		AddICECompoundNode("Set Data", "grid.polymsh.ICETree");
		AddICENode("$XSI_DSPRESETS\\ICENodes\\GetDataNode.Preset", "grid.polymsh.ICETree");
		SetValue("grid.polymsh.ICETree.SceneReferenceNode.reference", "self.DataArrayLong");
		SetValue("grid.polymsh.ICETree.Set_Data.Reference", "self.foo");
		ConnectICENodes("grid.polymsh.ICETree.Set_Data.Value", "grid.polymsh.ICETree.SceneReferenceNode.value");
		ConnectICENodes("grid.polymsh.ICETree.port1", "grid.polymsh.ICETree.Set_Data.Execute");

		DisplayPortValues(	"grid.polymsh.ICETree.Set_Data.Value", true, 0, 
			true, "", 0, 
			0, 0, 1, false, 
			true, 0.62, 1, 0.62, 1, 
			false, 0, 10000, 1, 
			true, false, 0, 10, 
			false, true, false, 100);

		CICEAttributeDataArray2D< LONG > data;
		attr.GetDataArray2D( data );

		CICEAttributeData2DLogger< LONG >::Log( attr );	
		ULONG l_nbElem = attr.GetElementCount();

		{
			LONG** l_Values = new LONG*[l_nbElem];
			ULONG* subArraySizes = new ULONG[l_nbElem];

			LONG* sub0;
			LONG* sub1;
			const ULONG SUBARRAY_SIZE = 64;

			sub0 = new LONG[SUBARRAY_SIZE];
			sub1 = new LONG[SUBARRAY_SIZE];

			for (ULONG i=0; i<SUBARRAY_SIZE; i++)
			{
				sub0[i] = (i%2==0) ? -1 : 1;
				sub1[i] = (i%2==0) ? -2 : 2;
			}

			for (ULONG i=0; i<l_nbElem; i++)
			{
				l_Values[i] = (i%2==0) ? sub0 : sub1;
				subArraySizes[i] = SUBARRAY_SIZE;
			}

			data.SetArray2D((const LONG**)l_Values, l_nbElem, subArraySizes);

			delete[] sub0;
			delete[] sub1;
			delete[] l_Values;
			delete[] subArraySizes;
		}

	\endcode
	*/
	CStatus SetArray2D( const T** in_ppArray, ULONG in_nbSubArrays, ULONG* in_pSubArraySizes );

private:
	static SICPPSDK_INLINE XSI::siICENodeDataType GetDefaultType( )
	{
		return siICENodeDataCustomType;
	}
};

//*****************************************************************************
/*! \brief This class is a specialization of CICEAttributeDataArray@D to give access to the ICEAttribute data as a 2D array of
	type ::siICENodeDataCustomType. %CICEAttributeDataArray2DCustomType objects are read-only and can be filled with the methods
	supplied with the ICEAttribute class.

	\note Data of type ::siICENodeDataCustomType can be created with custom ICENodes.

	\sa ICEAttribute::GetDataArray2D, ICEAttribute::GetDataArray2DChunk, CICEAttributeDataArrayCustomType,
		\ref CICEAttributeDataArrayTypedefs "Type Definitions for CICEAttributeDataArray"
	\since Supernova

	\eg This example demonstrates how to iterate over the siICENodeDataCustomType 2D attributes on a geometry. Check out the SDK
	InspectICEAttributes sample for a more detailed example.
	\code
		using namespace XSI;

		Application app;
		X3DObject x3dObj = app.GetSelection().GetItem(0);
		ICEAttribute attr = x3dObj.GetActivePrimitive().GetGeometry().GetICEAttributeFromName( L"SomeCustomDataType2DAttribute" );

		// Log the data pointer address and size of data.
		CICEAttributeDataArray2DCustomType customData2D;

		attr.GetDataArray2D( customData2D );

		for( ULONG i=0; i<customData2D.GetCount( ); i++ )
		{
			CICEAttributeDataArrayCustomType customData;
			customData2D.GetSubArray( i, customData );
			for( ULONG j=0; j<customData.GetCount( ); j++ )
			{
				ULONG nSize;
				const CICEAttributeDataArrayCustomType::TData* pBuffer;
				customData.GetData( j, &pBuffer, nSize );

				app.LogMessage( CString( (void*)pBuffer ) + L":" + CString( nSize ) );
			}
		}

	\endcode
 */
//*****************************************************************************

class SICPPSDKDECL CICEAttributeDataArray2DCustomType : public CBaseICEAttributeDataArray
{
public:
	/*! Constructor.*/
	CICEAttributeDataArray2DCustomType( ) : CBaseICEAttributeDataArray( GetDefaultType( ), XSI::siICENodeStructureArray ) {}

	/*! Destructor.	*/
	~CICEAttributeDataArray2DCustomType( )
	{
		SetParent( NULL );
	}

	/*! Returns the sub-array containing the custom type data at a given index.
	\param in_index Index in the array. The index must be smaller than the number of elements in the array, otherwise the
	results are unpredictable.
	\param out_dataArray A read-only reference to a \c CICEAttributeDataArrayCustomType object at a specific index.
	\return CStatus::OK Success
	\return CStatus::InvalidArgument If \c in_index or \c out_dataArray is invalid.
	*/
	CStatus GetSubArray( ULONG in_index, CBaseICEAttributeDataArray& out_dataArray ) const
	{
		return GetSubDataArray( in_index, out_dataArray );
	}

	/*! Set the sub-array at a given index
	This is only supported for writable attributes and not available for built-in attributes.
	\param in_index Index in the array. The index must be smaller than the number of elements in the array, otherwise the
	result is unpredictable. If this DataArray2D is an array chunk, \c in_index \c is relative to the chunk offset.
	\param in_ppData Array containing the input custom-typed data
	\param in_count Number of elements
	\param in_pElemSizes Array specifying the element sizes
	\return CStatus::OK Success
	\return CStatus::InvalidArgument If \c in_index, \c in_ppData, \c in_count or \c in_pElemSizes is invalid.
	\since v12.0 (2014)
	*/
	CStatus SetSubArray( ULONG in_index, const unsigned char** in_ppData, ULONG in_count, ULONG* in_pElemSizes );
	
	/*! Set the sub-array at a given index
	This is only supported for writable attributes and not available for built-in attributes.
	\param in_index Index in the array. The index must be smaller than the number of elements in the array, otherwise the
	result is unpredictable. If this DataArray2D is an array chunk, \c in_index \c is relative to the chunk offset.
	\param in_ppData array containing the input custom type data
	\param in_count number of elements to be set
	\param in_fixedElemSize the fixed size of all elements
	\return CStatus::OK Success
	\return CStatus::InvalidArgument If \c in_index, \c in_ppData, \c in_count or \c in_fixedElemSize is invalid.
	\since 12.0 (2014)
	*/
	CStatus SetSubArray( ULONG in_index, const unsigned char** in_ppData, ULONG in_count, ULONG in_fixedElemSize );

private:
	static SICPPSDK_INLINE XSI::siICENodeDataType GetDefaultType( )
	{
		return XSI::siICENodeDataCustomType;
	}
};

//*****************************************************************************
/*! \brief This class is a specialization of CICEAttributeDataArray2D which allows access to the ICEAttribute
	data as a 2D array of type ::siICENodeDataString. %CICEAttributeDataArray2DString objects are read-only
	and can be filled with the methods  supplied with the ICEAttribute class.

	\note Data of type ::siICENodeDataString can be created with custom ICENodes.

	\sa ICEAttribute::GetDataArray2D, ICEAttribute::GetDataArray2DChunk, CICEAttributeDataArrayString,
		\ref CICEAttributeDataArrayTypedefs "Type Definitions for CICEAttributeDataArray"
	\since 9.0 (2011)

	\eg This example demonstrates how to iterate over the siICENodeDataString 2D attributes on a geometry. For a more
		detailed example, check out the \xm ICEAttribute/netview_ICEAttribute Inspect ICE Attributes \endxm
		example.
	\code
		using namespace XSI;

		Application app;
		X3DObject x3dObj = app.GetSelection().GetItem(0);
		ICEAttribute attr = x3dObj.GetActivePrimitive().GetGeometry().GetICEAttributeFromName( L"MyStringData2DAttribute" );

		// Log the string and number of characters.
		CICEAttributeDataArray2DString stringData2D;

		attr.GetDataArray2D( stringData2D );

		for( ULONG i=0; i<stringData2D.GetCount( ); i++ )
		{
			CICEAttributeDataArrayString stringData;
			stringData2D.GetSubArray( i, stringData );
			for( ULONG j=0; j<stringData.GetCount( ); j++ )
			{
				ULONG nCount;
				const CICEAttributeDataArrayString::TData* pStr;
				stringData.GetData( j, &pStr, nCount );

				app.LogMessage( CString( pStr, nCount ) + L":" + CString( nCount ) );
			}
		}

	\endcode
 */
//*****************************************************************************

class SICPPSDKDECL CICEAttributeDataArray2DString : public CBaseICEAttributeDataArray
{
public:
	/*! Constructor.*/
	CICEAttributeDataArray2DString( ) : CBaseICEAttributeDataArray( GetDefaultType( ), XSI::siICENodeStructureArray ) {}

	/*! Destructor.	*/
	~CICEAttributeDataArray2DString( )
	{
		SetParent( NULL );
	}

	/*! Returns the sub-array containing the string data at a given index.
	\param in_index Index in the array. The index must be smaller than the number of elements
		in the array, otherwise the result is unpredictable.
	\retval out_dataArray A read-only reference to a \c CICEAttributeDataArrayString object.
	\return CStatus::OK Success
	\return CStatus::InvalidArgument If \c in_index or \c out_dataArray is invalid.
	*/
	CStatus GetSubArray( ULONG in_index, CBaseICEAttributeDataArray& out_dataArray ) const
	{
		return GetSubDataArray( in_index, out_dataArray );
	}

	/*! Changes the size of the sub-array at a given index and returns a new array pointing to the resized sub-array.
	This is only supported for writable attributes and not available for built-in attributes.
	\param in_index Index in the array. The index must be smaller than the number of elements in the array, otherwise the
	result is unpredictable. If this DataArray2D is an array chunk, \c in_index is relative to the chunk offset.
	\param out_dataArray A reference to a \c CICEAttributeDataArray<T> object at a specific index.
	\param in_size The size of the array. 
	\return CStatus::OK Success
	\return CStatus::InvalidArgument If \c in_index or \c out_dataArray is invalid.
	*/
	CStatus ResizeSubArray( ULONG in_index, ULONG in_size, CBaseICEAttributeDataArray& out_dataArray )
	{
		return ResizeSubDataArray( *this, in_index, in_size, out_dataArray );
	}


	/*! Set the sub-array at a given index
	This is only supported for writable attributes and not available for built-in attributes.
	\param in_index Index in the array. The index must be smaller than the number of elements in the array, otherwise the
	result is unpredictable. If this DataArray2D is an array chunk, \c in_index is relative to the chunk offset.
	\param in_array array containing the input strings, all strings in the array must be NULL-terminated
	\return CStatus::OK Success
	\return CStatus::InvalidArgument If \c in_index, \c in_ppData or \c in_count is invalid.
	\since 12.0 (2014)

	\eg This example demonstrates how to set a subarray
	\code

		// Template class to log the values in a CICEAttributeDataArray2D
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

		// Template specilization to log the values in a CICEAttributeDataArray2DString
		template < >
		class CICEAttributeData2DLogger< XSI::CString >
		{
			public:
			static void Log( ICEAttribute& attr )
			{
				CICEAttributeDataArray2DString data2D;
				attr.GetDataArray2D( data2D );
		
				Application xsi;
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
		Model root = xsi.GetActiveSceneRoot();
		X3DObject cone( CreatePrim( L"cone", L"MeshSurface", L"", L"") );
		{
			ICEAttribute attr = cone.GetActivePrimitive().GetGeometry().AddICEAttribute( "DataArray2DString", XSI::siICENodeDataString, XSI::siICENodeStructureArray, XSI::siICENodeContextComponent0D );

			CString l_connSet(L"cone");
			ApplyOp( L"ICETree", l_connSet, siConstructionModeModeling );

			AddICECompoundNode("Set Data", "cone.polymsh.ICETree");
			AddICENode("$XSI_DSPRESETS\\ICENodes\\GetDataNode.Preset", "cone.polymsh.ICETree");
			SetValue("cone.polymsh.ICETree.SceneReferenceNode.reference", "self.DataArray2DString");
			SetValue("cone.polymsh.ICETree.Set_Data.Reference", "self.foo");
			ConnectICENodes("cone.polymsh.ICETree.Set_Data.Value", "cone.polymsh.ICETree.SceneReferenceNode.value");
			ConnectICENodes("cone.polymsh.ICETree.port1", "cone.polymsh.ICETree.Set_Data.Execute");

			DisplayPortValues("cone.polymsh.ICETree.Set_Data.Value", true, 0, true, "", 0, 0, 0, 1, false, true, 0.62, 1, 0.62, 1, false, 0, 10000, 1, false, false, 0, 10, false, true, false, 100);

			CICEAttributeDataArray2DString data;
			attr.GetDataArray2D( data );


			CICEAttributeData2DLogger<CString>::Log( attr );	
			ULONG l_nbElem = attr.GetElementCount();

			typedef const wchar_t* RawWStringType;
			typedef const wchar_t** RawWStringArray;

			{
				RawWStringType sub0[2] = {L"even", L"EVEN"};
				RawWStringType sub1[2] = {L"odd", L"ODD"};

				for (ULONG i=l_nbElem; i>0; i--)
				{
					data.SetSubArray(i-1, (i-1)%2==0 ? sub0 : sub1, 2);
				}

				CICEAttributeData2DLogger<CString>::Log( attr );
			}

			{
				RawWStringType sub3[3] = {L"three", L"THREE", L"thrEE"};
				RawWStringType sub4[4] = {L"four", L"Four", L"FouR", L"FOUR"};
				RawWStringType sub5[5] = {L"FIVE", L"FivE", L"fIVe", L"Five", L"five"};

				CICEAttributeDataArray2DString dataChunk;
				attr.GetDataArray2DChunk(3, 3, dataChunk);

				dataChunk.SetSubArray(0, sub3, 3);
				dataChunk.SetSubArray(1, sub4, 4);
				dataChunk.SetSubArray(2, sub5, 5);
			}

		}
	\endcode
	*/
	CStatus SetSubArray( ULONG in_index, const wchar_t** in_ppData, ULONG in_count );

private:
	static SICPPSDK_INLINE XSI::siICENodeDataType GetDefaultType( )
	{
		return XSI::siICENodeDataString;
	}
};

/*! \page CICEAttributeDataArray2DTypedefs Type Definitions for CICEAttributeDataArray2D
	The CICEAttributeDataArray2D class is a template class that encapsulates the following 2D data arrays:

	\li \ref CICEAttributeDataArray2DFloat "CICEAttributeDataArray2DFloat"
	\li \ref CICEAttributeDataArray2DLong "CICEAttributeDataArray2DLong"
	\li \ref CICEAttributeDataArray2DBool "CICEAttributeDataArray2DBool"
	\li \ref CICEAttributeDataArray2DVector2f "CICEAttributeDataArray2DVector2f"
	\li \ref CICEAttributeDataArray2DVector3f "CICEAttributeDataArray2DVector3f"
	\li \ref CICEAttributeDataArray2DVector4f "CICEAttributeDataArray2DVector4f"
	\li \ref CICEAttributeDataArray2DQuaternionf "CICEAttributeDataArray2DQuaternionf"
	\li \ref CICEAttributeDataArray2DRotationf "CICEAttributeDataArray2DRotationf"
	\li \ref CICEAttributeDataArray2DMatrix3f "CICEAttributeDataArray2DMatrix3f"
	\li \ref CICEAttributeDataArray2DMatrix4f "CICEAttributeDataArray2DMatrix4f"
	\li \ref CICEAttributeDataArray2DColor4f "CICEAttributeDataArray2DColor4f"
	\li \ref CICEAttributeDataArray2DShape "CICEAttributeDataArray2DShape"


	\section CICEAttributeDataArray2DFloat CICEAttributeDataArray2DFloat Type
	\code typedef XSI::CICEAttributeDataArray2D< float > CICEAttributeDataArray2DFloat \endcode
	A CICEAttributeDataArray2D class of type \c float.
	\since 7.0

	\section CICEAttributeDataArray2DLong CICEAttributeDataArray2DLong Type
	\code typedef XSI::CICEAttributeDataArray2D< LONG > CICEAttributeDataArray2DLong \endcode
	A CICEAttributeDataArray2D class of type \c LONG.
	\since 7.0

	\section CICEAttributeDataArray2DBool CICEAttributeDataArray2DBool Type
	\code typedef XSI::CICEAttributeDataArray2D< bool > CICEAttributeDataArray2DBool \endcode
	A CICEAttributeDataArray2D class of type \c bool.
	\since 7.0

	\section CICEAttributeDataArray2DVector2f CICEAttributeDataArray2DVector2f Type
	\code typedef XSI::CICEAttributeDataArray2D< CVector2f > CICEAttributeDataArray2DVector2f \endcode
	A CICEAttributeDataArray2D class of type \link MATH::CVector2f CVector2f\endlink.
	\since 7.0

	\section CICEAttributeDataArray2DVector3f CICEAttributeDataArray2DVector3f Type
	\code typedef XSI::CICEAttributeDataArray2D< CVector3f > CICEAttributeDataArray2DVector3f \endcode
	A CICEAttributeDataArray2D class of type \link MATH::CVector3f CVector3f\endlink.
	\since 7.0

	\section CICEAttributeDataArray2DVector4f CICEAttributeDataArray2DVector4f Type
	\code typedef XSI::CICEAttributeDataArray2D< CVector4f > CICEAttributeDataArray2DVector4f \endcode
	A CICEAttributeDataArray2D class of type \link MATH::CVector4f CVector4f\endlink.
	\since 7.0

	\section CICEAttributeDataArray2DQuaternionf CICEAttributeDataArray2DQuaternionf Type
	\code typedef XSI::CICEAttributeDataArray2D< Quaternionf > CICEAttributeDataArray2DQuaternionf \endcode
	A CICEAttributeDataArray2D class of type \link MATH::CQuaternionf CQuaternionf\endlink.
	\since 7.0

	\section CICEAttributeDataArray2DRotationf CICEAttributeDataArray2DRotationf Type
	\code typedef XSI::CICEAttributeDataArray2D< CRotationf > CICEAttributeDataArray2DRotationf \endcode
	A CICEAttributeDataArray2D class of type \link MATH::CRotationf CRotationf\endlink.
	\since 7.0

	\section CICEAttributeDataArray2DMatrix3f CICEAttributeDataArray2DMatrix3f Type
	\code typedef XSI::CICEAttributeDataArray2D< CMatrix3f > CICEAttributeDataArray2DMatrix3f \endcode
	A CICEAttributeDataArray2D class of type \link MATH::CMatrix3f CMatrix3f\endlink
	\since 7.0

	\section CICEAttributeDataArray2DMatrix4f CICEAttributeDataArray2DMatrix4f Type
	\code typedef XSI::CICEAttributeDataArray2D< CMatrix4f > CICEAttributeDataArray2DMatrix4f \endcode
	A CICEAttributeDataArray2D class of type \link MATH::CMatrix4f CMatrix4f\endlink.
	\since 7.0

	\section CICEAttributeDataArray2DColor4f CICEAttributeDataArray2DColor4f Type
	\code typedef XSI::CICEAttributeDataArray2D< CColor4f > CICEAttributeDataArray2DColor4f \endcode
	A CICEAttributeDataArray2D class of type \link MATH::CColor4f CColor4f\endlink.
	\since 7.0

	\section CICEAttributeDataArray2DShape CICEAttributeDataArray2DShape Type
	\code typedef XSI::CICEAttributeDataArray2D< CShape > CICEAttributeDataArray2DShape \endcode
	A CICEAttributeDataArray2D class of type \link MATH::CShape CShape\endlink.
	\since 7.0
*/
typedef XSI::CICEAttributeDataArray2D< float > CICEAttributeDataArray2DFloat;
typedef XSI::CICEAttributeDataArray2D< LONG > CICEAttributeDataArray2DLong;
typedef XSI::CICEAttributeDataArray2D< bool > CICEAttributeDataArray2DBool;
typedef XSI::CICEAttributeDataArray2D< XSI::MATH::CVector2f > CICEAttributeDataArray2DVector2f;
typedef XSI::CICEAttributeDataArray2D< XSI::MATH::CVector3f > CICEAttributeDataArray2DVector3f;
typedef XSI::CICEAttributeDataArray2D< XSI::MATH::CVector4f > CICEAttributeDataArray2DVector4f;
typedef XSI::CICEAttributeDataArray2D< XSI::MATH::CQuaternionf > CICEAttributeDataArray2DQuaternionf;
typedef XSI::CICEAttributeDataArray2D< XSI::MATH::CRotationf > CICEAttributeDataArray2DRotationf;
typedef XSI::CICEAttributeDataArray2D< XSI::MATH::CMatrix3f > CICEAttributeDataArray2DMatrix3f;
typedef XSI::CICEAttributeDataArray2D< XSI::MATH::CMatrix4f > CICEAttributeDataArray2DMatrix4f;
typedef XSI::CICEAttributeDataArray2D< XSI::MATH::CColor4f > CICEAttributeDataArray2DColor4f;
typedef XSI::CICEAttributeDataArray2D< XSI::MATH::CShape > CICEAttributeDataArray2DShape;

template<> SICPPSDK_INLINE XSI::siICENodeDataType CICEAttributeDataArray2DFloat::GetDefaultType( ){return siICENodeDataFloat;}
template<> SICPPSDK_INLINE XSI::siICENodeDataType CICEAttributeDataArray2DLong::GetDefaultType( ){return siICENodeDataLong;}
template<> SICPPSDK_INLINE XSI::siICENodeDataType CICEAttributeDataArray2DBool::GetDefaultType( ){return siICENodeDataBool;}
template<> SICPPSDK_INLINE XSI::siICENodeDataType CICEAttributeDataArray2DVector2f::GetDefaultType( ){return siICENodeDataVector2;}
template<> SICPPSDK_INLINE XSI::siICENodeDataType CICEAttributeDataArray2DVector3f::GetDefaultType( ){return siICENodeDataVector3;}
template<> SICPPSDK_INLINE XSI::siICENodeDataType CICEAttributeDataArray2DVector4f::GetDefaultType( ){return siICENodeDataVector4;}
template<> SICPPSDK_INLINE XSI::siICENodeDataType CICEAttributeDataArray2DQuaternionf::GetDefaultType( ){return siICENodeDataQuaternion;}
template<> SICPPSDK_INLINE XSI::siICENodeDataType CICEAttributeDataArray2DMatrix3f::GetDefaultType( ){return siICENodeDataMatrix33;}
template<> SICPPSDK_INLINE XSI::siICENodeDataType CICEAttributeDataArray2DMatrix4f::GetDefaultType( ){return siICENodeDataMatrix44;}
template<> SICPPSDK_INLINE XSI::siICENodeDataType CICEAttributeDataArray2DColor4f::GetDefaultType( ){return siICENodeDataColor4;}
template<> SICPPSDK_INLINE XSI::siICENodeDataType CICEAttributeDataArray2DRotationf::GetDefaultType( ){return siICENodeDataRotation;}
template<> SICPPSDK_INLINE XSI::siICENodeDataType CICEAttributeDataArray2DShape::GetDefaultType( ){return siICENodeDataShape;}
};

#endif // __XSIICEATTRIBUTEDATAARRAY2D_H__
