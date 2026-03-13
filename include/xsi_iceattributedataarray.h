//*****************************************************************************
/*!
   \file xsi_iceattributedataarray.h
   \brief CICEAttributeDataArray classes declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIICEATTRIBUTEDATAARRAY_H__
#define __XSIICEATTRIBUTEDATAARRAY_H__

#include <sicppsdk.h>
#include <xsi_iceattribute.h>
#include <xsi_vector2f.h>
#include <xsi_vector3f.h>
#include <xsi_vector4f.h>
#include <xsi_quaternionf.h>
#include <xsi_rotationf.h>
#include <xsi_matrix3f.h>
#include <xsi_matrix4f.h>
#include <xsi_color4f.h>
#include <xsi_shape.h>
#include <xsi_indexset.h>
#include <xsi_bitarray.h>

namespace XSI {

//*****************************************************************************
/*!
	\brief Base class CICEAttributeDataArray class for the CICEAttributeDataArray and
	CICEAttributeDataArray2D template classes.

	\li \ref CICEAttributeDataArrayFloat "CICEAttributeDataArrayFloat"
	\li \ref CICEAttributeDataArrayLong "CICEAttributeDataArrayLong"
	\li \ref CICEAttributeDataArrayBool "CICEAttributeDataArrayBool"
	\li \ref CICEAttributeDataArrayVector2f "CICEAttributeDataArrayVector2f"
	\li \ref CICEAttributeDataArrayVector3f "CICEAttributeDataArrayVector3f"
	\li \ref CICEAttributeDataArrayVector4f "CICEAttributeDataArrayVector4f"
	\li \ref CICEAttributeDataArrayQuaternionf  "CICEAttributeDataArrayQuaternionf"
	\li \ref CICEAttributeDataArrayRotationf "CICEAttributeDataArrayRotationf"
	\li \ref CICEAttributeDataArrayMatrix3f "CICEAttributeDataArrayMatrix3f"
	\li \ref CICEAttributeDataArrayMatrix4f "CICEAttributeDataArrayMatrix4f"
	\li \ref CICEAttributeDataArrayColor4f "CICEAttributeDataArrayColor4f"
	\li \ref CICEAttributeDataArrayShape "CICEAttributeDataArrayShape"
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

	\sa ICEAttribute
	\since 8.0 (2010)
 */
//*****************************************************************************

class SICPPSDKDECL CBaseICEAttributeDataArray
{
public:
	friend class ICEAttribute;

	CBaseICEAttributeDataArray( XSI::siICENodeDataType in_dataType, XSI::siICENodeStructureType in_structType )
		:	m_nCount(0),
			m_bIsConstant(false),
			m_nAccessIndex(UINT_MAX),
			m_nHandle(ULONG_MAX),
			m_pData(NULL),
			m_structType( in_structType ),
			m_dataType( in_dataType ),
			m_pParent(NULL)
	{}

	/*! Accessor to the number of elements in the array.
	\return Number of elements in the array.
	*/
	ULONG GetCount() const
	{
		return m_nCount;
	}

	/*! Returns true if the array is constant in which case the array values are the same.
	\return True if array is constant or false otherwise.
	*/
	bool IsConstant() const
	{
		return m_bIsConstant;
	}

	/*! Returns the base data type of this array.
	\return XSI::siICENodeDataType value.
	*/
	XSI::siICENodeDataType GetDataType() const
	{
		return m_dataType;
	}

	/*! Returns the base structure type of this array.
	\return XSI::siICENodeStructureType value.
	*/
	XSI::siICENodeStructureType GetStructureType() const
	{
		return m_pParent ? m_pParent->GetStructureType( ) : m_structType;
	}

	virtual ~CBaseICEAttributeDataArray()
	{
		m_attrib.ReleaseDataArray( *this );
	}

protected:
	const void* GetDataPtr( ) const
	{
		return (const void*)m_pData;
	}

	ULONG GetHandle() const
	{
		return m_pParent ? m_pParent->GetHandle( ) : m_nHandle;
	}

	ULONG GetAccessIndex() const
	{
		return m_pParent ? m_pParent->GetAccessIndex( ) : m_nAccessIndex;
	}

	void*& GetDataRef( )
	{
		return m_pData;
	}

	ULONG& GetHandleRef()
	{
		return m_nHandle;
	}

	ULONG& GetCountRef()
	{
		return m_nCount;
	}

	ICEAttribute& GetICEAttributeRef()
	{
		return m_attrib;
	}

	const ICEAttribute& GetICEAttributeRef() const
	{
		return m_attrib;
	}

	CBitsetHelper& GetBitsetRef()
	{
		return m_bitset;
	}

	bool& GetConstantRef()
	{
		return m_bIsConstant;
	}

	void SetParent( CBaseICEAttributeDataArray* in_pParent )
	{
		m_pParent = in_pParent;
	}

	const CBaseICEAttributeDataArray* GetParent() const
	{
		return m_pParent;
	}

	CBaseICEAttributeDataArray* GetParent()
	{
		return m_pParent;
	}

	ULONG& GetAccessIndexRef()
	{
		return m_nAccessIndex;
	}

	const ULONG& GetAccessIndexRef() const
	{
		return m_nAccessIndex;
	}


protected:
	CStatus SetSubArrayElement( CBaseICEAttributeDataArray& in_dataArray2D, ULONG in_arrayIndex, ULONG in_subArrayIndex, void* in_value, ULONG in_size )
	{
		return m_attrib.SetArrayElementInternal( in_dataArray2D, in_arrayIndex, in_subArrayIndex, in_value, in_size );
	}

	CStatus GetSubArrayElement( const CBaseICEAttributeDataArray& in_dataArray2D, ULONG in_arrayIndex, ULONG in_subArrayIndex, void** out_value, ULONG& out_nSize ) const
	{
		return m_attrib.GetArrayElementInternal(  in_dataArray2D, in_arrayIndex, in_subArrayIndex, out_value, out_nSize );
	}

	CStatus GetSubDataArray( ULONG in_index, CBaseICEAttributeDataArray& out_dataArray ) const
	{
		CStatus st = m_attrib.GetSubDataArray( *(CBaseICEAttributeDataArray*)this, in_index, out_dataArray );
		assert( st == CStatus::OK );
		return st;
	}

	CStatus SetSubDataArray( CBaseICEAttributeDataArray& io_dataArray2D, CBaseICEAttributeDataArray* io_pSubDataArray, ULONG in_index, void* in_pData, ULONG in_count )
	{
		return m_attrib.SetSubDataArray(io_dataArray2D, io_pSubDataArray, in_index, in_pData, in_count);
	}

	CStatus SetStringSubDataArray( CBaseICEAttributeDataArray& io_dataArray2D, CBaseICEAttributeDataArray* io_pSubDataArray, ULONG in_index, const wchar_t** in_ppData, ULONG in_count )
	{
		CStatus st = m_attrib.SetStringSubDataArray(io_dataArray2D, io_pSubDataArray, in_index, in_ppData, in_count);
		assert( st == CStatus::OK );
		return st;
	}

	CStatus SetCustomTypeSubDataArray( CBaseICEAttributeDataArray& in_dataArray2D, CBaseICEAttributeDataArray* io_pSubDataArray, ULONG in_index, const unsigned char** in_ppData, ULONG in_count, ULONG in_fixedElemSize )
	{
		CStatus st = m_attrib.SetCustomTypeSubDataArray( in_dataArray2D, io_pSubDataArray, in_index, in_ppData, in_count, in_fixedElemSize);
		assert( st == CStatus::OK );
		return st;
	}

	CStatus SetCustomTypeSubDataArray( CBaseICEAttributeDataArray& in_dataArray2D, CBaseICEAttributeDataArray* io_pSubDataArray, ULONG in_index, const unsigned char** in_ppData, ULONG in_count, ULONG* in_pElemSizes )
	{
		CStatus st = m_attrib.SetCustomTypeSubDataArray(in_dataArray2D, io_pSubDataArray, in_index, in_ppData, in_count, in_pElemSizes);
		assert( st == CStatus::OK );
		return st;
	}


	CStatus SetBoolSubDataArray( CBaseICEAttributeDataArray& io_dataArray2D, CBaseICEAttributeDataArray* io_pSubDataArray, ULONG in_offset, const XSI::CBitArray& in_bitArray )
	{
		return m_attrib.SetBoolSubDataArray(io_dataArray2D, io_pSubDataArray, in_offset, in_bitArray );
	}

	CStatus ResizeSubDataArray( CBaseICEAttributeDataArray& in_dataArray2D, ULONG in_index, ULONG in_size, CBaseICEAttributeDataArray& out_dataArray )
	{
		if( m_attrib.IsReadonly() )
			return CStatus::AccessDenied; 

		CStatus st = m_attrib.ResizeSubDataArray(in_dataArray2D, in_index, in_size, out_dataArray );
		assert( st == CStatus::OK );
		return st;
	}

	CStatus SetDataArray2D( ULONG in_offset, void* in_pData, ULONG in_nbSubArrays, ULONG* in_pSubArraySizes )
	{
		return m_attrib.SetDataArrayInternal( *(CBaseICEAttributeDataArray*)this, NULL, in_offset, in_pData, in_nbSubArrays, in_pSubArraySizes, true );
	}


	CStatus SetStringDataArray2D( ULONG in_offset, const wchar_t*** in_pppData, ULONG in_count, ULONG* in_pSubArraySizes )
	{
		return m_attrib.SetCharDataArrayInternal( *(CBaseICEAttributeDataArray*)this, NULL, in_offset, in_pppData, in_count, in_pSubArraySizes, NULL, 0, true );
	}

	CStatus SetCustomTypeDataArray2D( ULONG in_offset, const unsigned char*** in_pppData, ULONG in_count, ULONG* in_pSubArraySizes, ULONG** in_ppElemSizes )
	{
		return m_attrib.SetCharDataArrayInternal( *(CBaseICEAttributeDataArray*)this, NULL, in_offset, in_pppData, in_count, in_pSubArraySizes, in_ppElemSizes, 0, true );
	}

	CStatus SetCustomTypeDataArray2D( ULONG in_offset, const unsigned char*** in_pppData, ULONG in_count, ULONG* in_pSubArraySizes, ULONG in_fixedElemSize )
	{
		return m_attrib.SetCharDataArrayInternal( *(CBaseICEAttributeDataArray*)this, NULL, in_offset, in_pppData, in_count, in_pSubArraySizes, NULL, in_fixedElemSize, true );
	}

	CStatus GetCustomTypeData( ULONG in_index, const unsigned char** out_ppData, ULONG& out_nSize ) const
	{
		if ( GetStructureType() == XSI::siICENodeStructureSingle )
		{
			return m_attrib.GetCustomTypeData( (CBaseICEAttributeDataArray&)*this, in_index, out_ppData, out_nSize );
		}
		return m_attrib.GetCustomTypeData2D( *(CBaseICEAttributeDataArray*)GetParent(), GetAccessIndexRef(), in_index, out_ppData, out_nSize );
	}

	CStatus GetStringData( ULONG in_index, const wchar_t** out_ppData, ULONG& out_nSize ) const
	{
		if ( GetStructureType() == XSI::siICENodeStructureSingle )
		{
			return m_attrib.GetStringData( (CBaseICEAttributeDataArray&)*this, in_index, out_ppData, out_nSize );
		}
		return m_attrib.GetStringData2D( *(CBaseICEAttributeDataArray*)GetParent(), GetAccessIndexRef(), in_index, out_ppData, out_nSize );
	}

	CStatus SetStringData( ULONG in_index, const wchar_t* in_pData, ULONG in_size )
	{
		if ( GetStructureType() == XSI::siICENodeStructureSingle )
		{
			return m_attrib.SetStringData( (CBaseICEAttributeDataArray&)*this, in_index, in_pData, in_size );
		}
		return m_attrib.SetStringData2D( *(CBaseICEAttributeDataArray*)GetParent(), GetAccessIndexRef(), in_index, in_pData, in_size );
	}

	CStatus SetArrayElement( ULONG in_index, void* in_value, ULONG in_size )
	{
		return m_attrib.SetArrayElementInternal(  (CBaseICEAttributeDataArray&)*this, in_index, ULONG_MAX, in_value, in_size );
	}

	CStatus GetArrayElement( ULONG in_index, void** out_value, ULONG& out_nSize ) const
	{
		return m_attrib.GetArrayElementInternal(  (CBaseICEAttributeDataArray&)*this, in_index, ULONG_MAX, out_value, out_nSize );
	}

	CStatus SetDataArray( ULONG in_offset, void* in_pData, ULONG in_count )
	{
		return m_attrib.SetDataArrayInternal( (CBaseICEAttributeDataArray&)*this, NULL, in_offset, in_pData, in_count, NULL, false );
	}

	CStatus SetStringDataArray( ULONG in_offset, const wchar_t** in_ppData, ULONG in_count )
	{
		return m_attrib.SetCharDataArrayInternal( (CBaseICEAttributeDataArray&)*this, NULL, in_offset, in_ppData, in_count, NULL, NULL, 0, false );
	}


	CStatus SetCustomTypeDataArray( ULONG in_offset, const unsigned char** in_ppData, ULONG in_count, ULONG in_fixedElemSize )
	{
		return m_attrib.SetCharDataArrayInternal( (CBaseICEAttributeDataArray&)*this, NULL, in_offset, in_ppData, in_count, NULL, NULL, in_fixedElemSize, false );
	}

	CStatus SetCustomTypeDataArray( ULONG in_offset, const unsigned char** in_ppData, ULONG in_count, ULONG* in_pElementSizes )
	{
		return m_attrib.SetCharDataArrayInternal( (CBaseICEAttributeDataArray&)*this, NULL, in_offset, in_ppData, in_count, NULL, in_pElementSizes, 0, false );
	}


	CStatus SetBoolDataArray( ULONG in_offset, const XSI::CBitArray& in_bitArray )
	{
		return m_attrib.SetBoolDataArray( (CBaseICEAttributeDataArray&)*this, in_offset, in_bitArray );
	}


	ULONG			m_nCount;
	CBitsetHelper	m_bitset;
	bool			m_bIsConstant;

private:
	ULONG						m_nAccessIndex;
	ULONG						m_nHandle;
	void*						m_pData;
	XSI::siICENodeStructureType	m_structType;
	XSI::siICENodeDataType		m_dataType;
	ICEAttribute				m_attrib;
	CBaseICEAttributeDataArray*	m_pParent;
};

//*****************************************************************************
/*! \brief This template class encapsulates ICEAttribute data as a 1D array. %CICEAttributeDataArray
	objects are read-only and can be filled with the methods supplied with the ICEAttribute class.
	%CICEAttributeDataArray is zero-based and can be one of the following types:

	\li \ref CICEAttributeDataArrayFloat "CICEAttributeDataArrayFloat"
	\li \ref CICEAttributeDataArrayLong "CICEAttributeDataArrayLong"
	\li \ref CICEAttributeDataArrayBool "CICEAttributeDataArrayBool"
	\li \ref CICEAttributeDataArrayVector2f "CICEAttributeDataArrayVector2f"
	\li \ref CICEAttributeDataArrayVector3f "CICEAttributeDataArrayVector3f"
	\li \ref CICEAttributeDataArrayVector4f "CICEAttributeDataArrayVector4f"
	\li \ref CICEAttributeDataArrayQuaternionf  "CICEAttributeDataArrayQuaternionf"
	\li \ref CICEAttributeDataArrayRotationf "CICEAttributeDataArrayRotationf"
	\li \ref CICEAttributeDataArrayMatrix3f "CICEAttributeDataArrayMatrix3f"
	\li \ref CICEAttributeDataArrayMatrix4f "CICEAttributeDataArrayMatrix4f"
	\li \ref CICEAttributeDataArrayColor4f "CICEAttributeDataArrayColor4f"
	\li \ref CICEAttributeDataArrayShape "CICEAttributeDataArrayShape"

	All types are associated to specific ICEAttribute types. Therefore, you need to declare the right
	array object type that matches the ICEAttribute data type you want to access. Otherwise a runtime
	error will occur and the returned array will be empty.

	\sa ICEAttribute::GetDataArray, ICEAttribute::GetDataArrayChunk,
		\ref CICEAttributeDataArrayTypedefs "Type Definitions for CICEAttributeDataArray"
	\since 7.0

	\eg This example demonstrates how to iterate over the PointPosition attribute data on a grid primitive.
	\code
		using namespace XSI;
		CValue CreatePrim( const CString& in_presetobj, const CString& in_geometrytype, const CString& in_name, const CString& in_parent );

		X3DObject grid = CreatePrim( L"Grid", L"MeshSurface", L"", L"");

		ICEAttribute attr = grid.GetActivePrimitive().GetGeometry().GetICEAttributeFromName( L"PointPosition" );

		CICEAttributeDataArrayVector3f points;
		attr.GetDataArray( points );

		Application xsi;
		for( ULONG i=0; i<points.GetCount( ); i++ )
		{
			xsi.LogMessage( CString( points[ i ] ) );
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
template<class T>
class CICEAttributeDataArray : public CBaseICEAttributeDataArray
{
public:

	/*! Constructor.*/
	CICEAttributeDataArray( ) : CBaseICEAttributeDataArray( GetDefaultType( ), XSI::siICENodeStructureSingle ) {}

	/*! Destructor.	*/
	~CICEAttributeDataArray( ) {}

	/*! Accessor to the encapsulated array. This operator is called when reading the data so the return value is read-only.
	\param in_index Index in the array. The index must be smaller than the number of elements in the array, otherwise the
	results are unpredictable. If the array is constant, the function always return the first item's value.
	\return A read-only reference to the indexed item.
	*/
	const T& operator[]( ULONG in_index ) const
	{
		const T* pData = (const T*)GetDataPtr();

		if (!pData) 
		{
			static T defVal;
			return defVal;
		}
		
		if (m_bIsConstant) 
		{
			return *pData;
		}
		
		return pData[in_index];

	}

	/*! Accessor to the encapsulated array. This operator is used for writing to the data array.
	\param in_index Index in the array. The index must be smaller than the number of elements in the array, otherwise the
	results are unpredictable. 
	\return A reference to the indexed item.
	\since 11.0 (2013)
	*/
	T& operator[]( ULONG in_index )
	{
		T* pData = (T*) GetDataPtr();

		if (!pData || in_index >=  GetCount()) 
		{
			static T defVal;
			return defVal;
		}
		
		if (m_bIsConstant) 
		{
			return  pData[0];
		}
		
		return pData[in_index];
	}

	/*! Accessor to the encapsulated array for writing to the data array.
	\param in_index Index in the array. The index must be smaller than the number of elements in the array, otherwise the
	results are unpredictable.
	\return CStatus::OK Success.
	\return CStatus::InvalidArgument Index out of range.
	\return CStatus::AccessDenied Array is read-only.
	\return CStatus::Fail Attribute is undefined or non-accessible
	\since 12.0 (2014)
	*/
	CStatus SetData( ULONG in_index, const T& in_value );

	/*! Set the values in the array

	\param in_pArray Input data array.
	\param in_count Number of elements in the input array

	\return CStatus::OK Success.
	\return CStatus::Fail Operation failed.
	\since 12.0 (2014)

	\eg This example demonstrates how to set the whole array
	\code
		Application xsi;
		Model root = xsi.GetActiveSceneRoot();
		X3DObject cone( CreatePrim( L"cone", L"MeshSurface", L"", L"") );
		{
			ICEAttribute attr = cone.GetActivePrimitive().GetGeometry().AddICEAttribute( "DataArrayLong", XSI::siICENodeDataLong, XSI::siICENodeStructureSingle, XSI::siICENodeContextComponent0D );

			CString l_connSet(L"cone");
			ApplyOp( L"ICETree", l_connSet, siConstructionModeModeling );

			AddICECompoundNode("Set Data", "cone.polymsh.ICETree");
			AddICENode("$XSI_DSPRESETS\\ICENodes\\GetDataNode.Preset", "cone.polymsh.ICETree");
			SetValue("cone.polymsh.ICETree.SceneReferenceNode.reference", "self.DataArrayLong");
			SetValue("cone.polymsh.ICETree.Set_Data.Reference", "self.foo");
			ConnectICENodes("cone.polymsh.ICETree.Set_Data.Value", "cone.polymsh.ICETree.SceneReferenceNode.value");
			ConnectICENodes("cone.polymsh.ICETree.port1", "cone.polymsh.ICETree.Set_Data.Execute");
		
			DisplayPortValues("cone.polymsh.ICETree.Set_Data.Value", true, 0, true, "", 0, 0, 0, 1, false, true, 0.62, 1, 0.62, 1, false, 0, 10000, 1, false, false, 0, 10, false, true, false, 100);
		
			CICEAttributeDataArray< LONG > data;
			attr.GetDataArray( data );

			CICEAttributeDataLogger< LONG >::Log( attr );	
			ULONG l_nbElem = attr.GetElementCount();

			{
				CLongArray l_Values(l_nbElem);

				for (ULONG i=0; i<l_nbElem; i++)
					l_Values[i] = (i%2==0) ? -1 : 1;

				data.SetArray(l_Values.GetArray(), l_nbElem);

				CICEAttributeDataLogger<LONG>::Log( attr );
			}

			data[0] = (LONG)5;
			data[4] = (LONG)12;
		}

	\endcode
	*/
	CStatus SetArray( const T* in_pArray, ULONG in_count );

private:
	static XSI::siICENodeDataType GetDefaultType( );
	const T* GetDataAccessor(ULONG in_index) const;
};

//*****************************************************************************
// NB: Do not use the Doxygen \class tag for this template!!!
/*!	\brief This class is a specialization of a CICEAttributeDataArray class of type \c bool.
	\sa CICEAttributeDataArray2D, ICEAttribute, \ref CICEAttributeDataArrayBool "CICEAttributeDataArrayBool typedef"
	\since 7.0
 */
//*****************************************************************************
template<>
class SICPPSDKDECL CICEAttributeDataArray<bool> : public CBaseICEAttributeDataArray
{
public:
	/*! Constructor.*/
	CICEAttributeDataArray<bool>( ) :
		CBaseICEAttributeDataArray( GetDefaultType( ), XSI::siICENodeStructureSingle )
	{}

	/*! Destructor.	*/
	~CICEAttributeDataArray<bool>( ) {}

	/*! Accessor to the bool array. This operator is called when reading the data so the return value is read-only.
	\param in_index Index in the array. The index must be smaller than the number of elements in the array, otherwise the
	results are unpredictable.
	\return A read-only value to the indexed item.
	*/
	const bool operator[]( ULONG in_index ) const
	{
		return m_bitset.GetBit( m_StartBitOffset + in_index );
	}

	/*! Accessor to the bool array for writing to the data array.
	\param in_index Index in the array. The index must be smaller than the number of elements in the array, otherwise the
	results are unpredictable.
	\return CStatus::OK Success.
	\return CStatus::InvalidArgument Index out of range.
	\return CStatus::AccessDenied Array is read-only.
	\since 11.0 (2013)
	*/
	CStatus SetData( ULONG in_index, bool in_bVal )
	{
		if( in_index >=  GetCount() )
			return CStatus::InvalidArgument; 
		
		if( GetICEAttributeRef().IsReadonly() )
			return CStatus::AccessDenied; 

		return m_bitset.SetBit( m_StartBitOffset + in_index, in_bVal );
	}

	/*! Set the values in the array

	\param in_pArray Input data array.
	\param in_count Number of elements in the input array

	\return CStatus::OK Success.
	\return CStatus::Fail Operation failed.
	\since 12.0 (2014)
	*/
	CStatus SetArray( const bool* in_pArray, ULONG in_count );

private:
	friend class ICEAttribute;
	static SICPPSDK_INLINE XSI::siICENodeDataType GetDefaultType( )
	{
		return siICENodeDataBool;
	}

	ULONG& GetStartBitOffsetRef() { return m_StartBitOffset;}

	ULONG m_StartBitOffset;
};

//*****************************************************************************
// NB: Do not use the Doxygen \class tag for this template!!!
/*!	\brief This class is a specialization of a CICEAttributeDataArray class of type \c MATH::CShape.
	\sa CICEAttributeDataArray2D, ICEAttribute, \ref CICEAttributeDataArrayBool "CICEAttributeDataArrayBool typedef"
	\since 7.0
 */
//*****************************************************************************
#ifndef XSI_CPPSDK_COMPATIBILITY_MODE
template<>
class SICPPSDKDECL CICEAttributeDataArray<XSI::MATH::CShape> : public CBaseICEAttributeDataArray
{
public:
	/*! Constructor.*/
	CICEAttributeDataArray<XSI::MATH::CShape>( ) :
		CBaseICEAttributeDataArray( GetDefaultType( ), XSI::siICENodeStructureSingle )
	{}

	/*! Destructor.	*/
	~CICEAttributeDataArray<XSI::MATH::CShape>( ) {}

	/*! Accessor to the encapsulated array. This operator is called when reading the data so the return value is read-only.
	\param in_index Index in the array. The index must be smaller than the number of elements in the array, otherwise the
	results are unpredictable. If the array is constant, the function always return the first item's value.
	\return A read-only reference to the indexed item.
	*/
	const MATH::CShape operator[]( ULONG in_index ) const;

	/*! Accessor to the shape array for writing to the data array.
	\param in_index Index in the array. The index must be smaller than the number of elements in the array, otherwise the
	results are unpredictable.
	\return CStatus::OK Success.
	\return CStatus::InvalidArgument Index out of range.
	\return CStatus::AccessDenied Array is read-only.
	\since 11.0 (2013)
	*/
	CStatus SetData( ULONG in_index, const XSI::MATH::CShape& in_value );

	/*! Set the values in the array

	\param in_pArray Input data array.
	\param in_count Number of elements in the input array

	\return CStatus::OK Success.
	\return CStatus::Fail Operation failed.
	\since 12.0 (2014)
	*/
	CStatus SetArray( const XSI::MATH::CShape* in_pArray, ULONG in_count );

private:
	static SICPPSDK_INLINE XSI::siICENodeDataType GetDefaultType( )
	{
		return siICENodeDataShape;
	}
	const XSI::MATH::CShape* GetDataAccessor(ULONG in_index) const;
};
#endif

//*****************************************************************************
/*! \brief This class is a specialization of CICEAttributeDataArray to give access to the ICEAttribute data as a 1D array of
	type ::siICENodeDataCustomType. %CICEAttributeDataArrayCustomType objects are read-only and can be filled with the methods
	supplied with the ICEAttribute class.

	\note Data of type ::siICENodeDataCustomType can be created with custom ICENodes.

	\sa ICEAttribute::GetDataArray, ICEAttribute::GetDataArrayChunk, CICEAttributeDataArray2DCustomType,
		\ref CICEAttributeDataArrayTypedefs "Type Definitions for CICEAttributeDataArray"
	\since 8.0 (2010)

	\eg This example demonstrates how to iterate over the siICENodeDataCustomType attributes on a geometry. Check out the SDK
	InspectICEAttributes sample for a more detailed example.
	\code
		using namespace XSI;

		Application app;
		X3DObject x3dObj = app.GetSelection().GetItem(0);
		ICEAttribute attr = x3dObj.GetActivePrimitive().GetGeometry().GetICEAttributeFromName( L"SomeCustomDataTypeAttribute" );

		// Log the data pointer address and size of data.
		CICEAttributeDataArrayCustomType customData;
		attr.GetDataArray( customData );

		for( ULONG i=0; i<customData.GetCount( ); i++ )
		{
			ULONG nSize;
			const CICEAttributeDataArrayCustomType::TData* pBuffer;
			customData.GetData( i, &pBuffer, nSize );

			app.LogMessage( CString( (void*)pBuffer ) + L":" + CString( nSize ) );
		}

	\endcode
 */
//*****************************************************************************

class SICPPSDKDECL CICEAttributeDataArrayCustomType : public CBaseICEAttributeDataArray
{
	public:
	typedef unsigned char TData;

	/*! Default Constructor.
	*/
	SICPPSDK_INLINE CICEAttributeDataArrayCustomType( ) : CBaseICEAttributeDataArray( GetDefaultType( ), XSI::siICENodeStructureSingle )
	{}

	/*! Destructor.
	*/
	SICPPSDK_INLINE ~CICEAttributeDataArrayCustomType( )
	{}

	/*! Returns a pointer to the user data stored at a specific index. The data is read-only and cannot be modified.
	\note The memory allocated for the data returned by CICEAttributeDataArrayCustomType::GetData is only available within the
		scope of this CICEAttributeDataArrayCustomType instance. Make sure to make a copy of the data if you need to access it
		outside the scope of CICEAttributeDataArrayCustomType.
	\param in_index Array index of the user data to retrieve. The size is 0 if no data is stored at this index.
	\retval out_ppData Read-only pointer to the data.
	\retval out_nSize Size in bytes of the user data.
	\return Success/failure
	*/
	SICPPSDK_INLINE CStatus GetData( ULONG in_index, const TData** out_ppData, ULONG& out_nSize  ) const;

	/*! Set the values in the custom-typed data array

	\param in_ppData The input custom-typed array. All elements must have the same size.
	\param in_count Number of elements in the input array
	\param in_fixedElemSize The fixed size of all elements

	\return CStatus::OK Success.
	\return CStatus::Fail Operation failed.
	\since 12.0 (2014)

	\eg This example demonstrates how to set the whole CustomType array
	\code

		// Data structure holding the states for each particule
		struct GridWalkerState
		{
			ULONG m_nRandomSequencePosition;
			ULONG m_nCurrentStep;

			LONG m_nCurrentPositionX, m_nCurrentPositionY;
			LONG m_nDirectionX, m_nDirectionY;

			GridWalkerState()
			{
				m_nRandomSequencePosition = 0;
				m_nCurrentStep = 0;

				m_nCurrentPositionX = 0;
				m_nCurrentPositionY = 0;
				m_nDirectionX = 0;
				m_nDirectionY = 0;
			}

			GridWalkerState(	ULONG in_nRandomSequencePosition,
										ULONG in_nCurrentStep,

										ULONG in_nCurrentPositionX,
										ULONG in_nCurrentPositionY,
										ULONG in_nDirectionX,
										ULONG in_nDirectionY)
			{
				m_nRandomSequencePosition = in_nRandomSequencePosition;
				m_nCurrentStep = 			in_nCurrentStep;

				m_nCurrentPositionX = 	in_nCurrentPositionX;
				m_nCurrentPositionY = 	in_nCurrentPositionY;
				m_nDirectionX = 		in_nDirectionX;
				m_nDirectionY = 		in_nDirectionY;
			}

			const GridWalkerState& operator=(const GridWalkerState& other)
			{
				m_nRandomSequencePosition = other.m_nRandomSequencePosition;
				m_nCurrentStep = 			other.m_nCurrentStep;

				m_nCurrentPositionX = 	other.m_nCurrentPositionX;
				m_nCurrentPositionY = 	other.m_nCurrentPositionY;
				m_nDirectionX = 		other.m_nDirectionX;
				m_nDirectionY = 		other.m_nDirectionY;

				return *this;
			}

			operator CString() const
			{
				CString result;
				result = L"[";
				result += L"Random Sequence Pos:";
				result += CString(m_nRandomSequencePosition) + CString(L", ");
			
				result += L"Step:";
				result += CString(m_nCurrentStep) + L", ";

				result += L"X:";
				result += CString(m_nCurrentPositionX) + L", ";

				result += L"Y:";
				result += CString(m_nCurrentPositionY) + L", ";

				result += L"Dir X:";
				result += CString(m_nDirectionX) + L", ";

				result += L"Dir Y:";
				result += CString(m_nDirectionY);

				result += L"]";
				return result;
			}
		};

		template < class CustomType >
		class CICEAttributeDataLoggerCustomType
		{
		public:
			static void Log( ICEAttribute& attr )
			{
				CICEAttributeDataArrayCustomType data;
				attr.GetDataArray( data );

				Application xsi;
				for( ULONG i=0; i<data.GetCount( ); i++ )
				{
					CustomType val;
					const CICEAttributeDataArrayCustomType::TData* addr = NULL;
					ULONG size=0;
					data.GetData(i, &addr, size);

					if (addr != NULL && size>0)
					{
						val = *(CustomType*)addr;
						xsi.LogMessage( CString(val) );
					}
				}
			}
		};

		Application app;

		// Loads the GridWalker custom node plug-in from the examples workgroup	
		CString strWrkgrp = CUtils::BuildPath( app.GetInstallationPath(siFactoryPath ), "..", "..", "Rayflex", "Sdk", "examples", "workgroup" );
		app.AddWorkgroup( strWrkgrp  );

		// Opens the GridWalker scene containing custom data types 
		CValueArray args(2);
		CValue retval;
		args[0] = CUtils::BuildPath( strWrkgrp, "Addons", "CustomICENodes", "Data", "Project", "Scenes", "GridWalker" ) + ".scn";
		args[1] = false;
		app.ExecuteCommand( "OpenScene", args, retval );

		// Logs custom data type
		CStringArray strNoFamily;
		CString strNoType;
		Geometry geom( app.GetActiveSceneRoot().FindChild("grid", strNoType, strNoFamily).GetActivePrimitive().GetGeometry() );
		ICEAttribute attr = geom.GetICEAttributeFromName( "GridWalkerState" );

		{
			typedef GridWalkerState* CustomTypePtr;

			CICEAttributeDataArrayCustomType data;
			attr.GetDataArray( data );

			CICEAttributeDataLoggerCustomType<GridWalkerState>::Log( attr );

			ULONG l_nbElem = attr.GetElementCount();

			{
				CustomTypePtr* l_Values = new CustomTypePtr[l_nbElem];

				for (ULONG i=0; i<l_nbElem; i++)
				{
					if (i%2==0)
						l_Values[i] = new GridWalkerState(0, 0, 0, 0, 0, 0);
					else
						l_Values[i] = new GridWalkerState(1, 1, 1, 1, 1, 1);
				}

				data.SetArray((const unsigned char**)l_Values, l_nbElem, sizeof(GridWalkerState));
			
				CICEAttributeDataLoggerCustomType<GridWalkerState>::Log( attr );

				for (ULONG i=0; i<l_nbElem; i++)
				{
					delete l_Values[i];
				}

				delete[] l_Values;
			}

			{
				const ULONG CHUNK_SIZE = 10;
				CustomTypePtr* l_Values = new CustomTypePtr[CHUNK_SIZE];

				for (ULONG i=0; i<CHUNK_SIZE; i++)
				{
					l_Values[i] = new GridWalkerState(i + 2, i + 2, i + 2, i + 2, i + 2, i + 2);
				}

				CICEAttributeDataArrayCustomType dataChunk;
				attr.GetDataArrayChunk(2, CHUNK_SIZE, dataChunk);

				data.SetArray((const unsigned char**)l_Values, CHUNK_SIZE, sizeof(GridWalkerState));

				CICEAttributeDataLoggerCustomType<GridWalkerState>::Log( attr );

				for (ULONG i=0; i<CHUNK_SIZE; i++)
				{
					delete l_Values[i];
				}

				delete[] l_Values;
			}

		}
	\endcode

	*/
	CStatus SetArray( const TData** in_ppData, ULONG in_count, ULONG in_fixedElemSize );

	/*! Set the values in the custom-typed data array

	\param in_ppData Input custom-typed array. The element sizes can vary.
	\param in_count Number of elements in the input array
	\param in_pElementSizes Array specifying the sizes of the elements.

	\return CStatus::OK Success.
	\return CStatus::Fail Operation failed.
	\since 12.0 (2014)
	*/
	CStatus SetArray( const TData** in_ppData, ULONG in_count, ULONG* in_pElementSizes );

private:
	static SICPPSDK_INLINE XSI::siICENodeDataType GetDefaultType( )
	{
		return siICENodeDataCustomType;
	}
};

CStatus CICEAttributeDataArrayCustomType::GetData( ULONG in_index, const TData** out_ppData, ULONG& out_nSize  ) const
{
	return GetCustomTypeData( in_index, out_ppData, out_nSize );
}

//*****************************************************************************
/*! \brief This class is a specialization of CICEAttributeDataArray which allows access to the ICEAttribute
	data as a 1D array of type ::siICENodeDataString. %CICEAttributeDataArrayString objects are read-only and
	can be filled with the methods supplied with the ICEAttribute class.

	\sa ICEAttribute::GetDataArray, ICEAttribute::GetDataArrayChunk, CICEAttributeDataArray2DString,
		\ref CICEAttributeDataArrayTypedefs "Type Definitions for CICEAttributeDataArray"
	\since 9.0 (2011)

	\eg This example demonstrates how to iterate over the siICENodeDataString attributes on a geometry. For a more
		detailed example, check out the \xm ICEAttribute/netview_ICEAttribute Inspect ICE Attributes \endxm
		example.
	\code
		using namespace XSI;

		Application app;
		X3DObject x3dObj = app.GetSelection().GetItem(0);
		ICEAttribute attr = x3dObj.GetActivePrimitive().GetGeometry().GetICEAttributeFromName( L"MyStringAttribute" );

		// Log the data pointer address and size of data.
		CICEAttributeDataArrayString strData;
		attr.GetDataArray( strData );

		for( ULONG i=0; i<strData.GetCount( ); i++ )
		{
			ULONG nCount;
			const CICEAttributeDataArrayString::TData* pStr;
			strData.GetData( i, &pStr, nCount );

			app.LogMessage( CString( pStr, nCount ) + L":" + CString( nCount ) );
		}

	\endcode
 */
//*****************************************************************************

class SICPPSDKDECL CICEAttributeDataArrayString : public CBaseICEAttributeDataArray
{
	public:
	typedef wchar_t TData;

	/*! Default Constructor.
	*/
	SICPPSDK_INLINE CICEAttributeDataArrayString( ) : CBaseICEAttributeDataArray( GetDefaultType( ), XSI::siICENodeStructureSingle )
	{}

	/*! Destructor.
	*/
	SICPPSDK_INLINE ~CICEAttributeDataArrayString( )
	{}

	/*! Returns a pointer to the string stored at a specific index. The data is read-only and cannot be modified.
	\note The memory allocated for the data returned by CICEAttributeDataArrayString::GetData is only available within the
		scope of this CICEAttributeDataArrayString instance. Make sure to make a copy of the data if you need to access it
		outside the scope of CICEAttributeDataArrayString.
	\note The string returned in \c out_ppStr is not null-terminated, the caller must make sure to take the number
		of characters in account when manipulating the string.

	\param in_index Array index of the user data to retrieve. The size is 0 if no data is stored at this index.
	\retval out_ppStr Read-only pointer to the data.
	\retval out_nCount Number of characters in the string.
	\return Success/failure
	*/
	SICPPSDK_INLINE CStatus GetData( ULONG in_index, const TData** out_ppStr, ULONG& out_nCount ) const;

	/*! Returns a CString object set with a copy of the string stored at a specific index.
	\param in_index Array index of the string to retrieve. The object is empty if no string is stored at this index.
	\retval out_str Copy of the string.
	\return Success/failure
	*/
	SICPPSDK_INLINE CStatus GetData( ULONG in_index, CString& out_str ) const;

	/*! Accessor to string array for writing to the data array.
	\param in_index Index in the array. The index must be smaller than the number of elements in the array, otherwise the
	results are unpredictable.
	\return CStatus::OK Success.
	\return CStatus::InvalidArgument Index out of range.
	\return CStatus::AccessDenied Array is read-only.
	\since 11.0 (2013)
	*/
	SICPPSDK_INLINE CStatus SetData( ULONG in_index, const CString& in_str );

	/*! Returns a CString stored at \c in_index.  The CString object will contain a copy of the string.
	\param in_index Index in the array. The index must be smaller than the number of elements in the array,
		otherwise the object returned is empty.
	\return Copy of the CString.
	*/
	SICPPSDK_INLINE CString operator[]( ULONG in_index ) const;

	/*! Set all the values in the string ICE attribute

	\param in_ppData Input string array. The strings must be null-terminated.
	\param in_count Number of strings in the input array

	\return CStatus::OK Success.
	\return CStatus::Fail Operation failed.
	\since 12.0 (2014)

	
	\eg This example demonstrates how to set the whole array
	\code
		Application xsi;
		Model root = xsi.GetActiveSceneRoot();
		X3DObject cone( CreatePrim( L"cone", L"MeshSurface", L"", L"") );
		{
			ICEAttribute attr = cone.GetActivePrimitive().GetGeometry().AddICEAttribute( "DataArrayString", XSI::siICENodeDataString, XSI::siICENodeStructureSingle, XSI::siICENodeContextComponent0D );

			CString l_connSet(L"cone");
			ApplyOp( L"ICETree", l_connSet, siConstructionModeModeling );

			AddICECompoundNode("Set Data", "cone.polymsh.ICETree");
			AddICENode("$XSI_DSPRESETS\\ICENodes\\GetDataNode.Preset", "cone.polymsh.ICETree");
			SetValue("cone.polymsh.ICETree.SceneReferenceNode.reference", "self.DataArrayString");
			SetValue("cone.polymsh.ICETree.Set_Data.Reference", "self.foo");
			ConnectICENodes("cone.polymsh.ICETree.Set_Data.Value", "cone.polymsh.ICETree.SceneReferenceNode.value");
			ConnectICENodes("cone.polymsh.ICETree.port1", "cone.polymsh.ICETree.Set_Data.Execute");

			DisplayPortValues("cone.polymsh.ICETree.Set_Data.Value", true, 0, true, "", 0, 0, 0, 1, false, true, 0.62, 1, 0.62, 1, false, 0, 10000, 1, false, false, 0, 10, false, true, false, 100);

			CICEAttributeDataArrayString data;
			attr.GetDataArray( data );


			CICEAttributeDataLogger<CString>::Log( attr );	
			ULONG l_nbElem = attr.GetElementCount();

			{
				typedef const wchar_t* RawWStringType;
				RawWStringType* l_Values = new RawWStringType[l_nbElem];

				for (ULONG i=0; i<l_nbElem; i++)
					l_Values[i] = (i%2==0) ? L"odd" : L"even";

				data.SetArray(l_Values, l_nbElem);

				CICEAttributeDataLogger<CString>::Log( attr );
				delete[] l_Values;
			}

			// These have no effect since the reference returned by operator[] are only temporary
			data[0] = L"str 0";

			// These work
			data.SetData(0, L"First string");
			data.SetData(4, L"String value at index 4");
		}

	\endcode
	*/
	CStatus SetArray( const TData** in_ppData, ULONG in_count );

private:
	static SICPPSDK_INLINE XSI::siICENodeDataType GetDefaultType( )
	{
		return siICENodeDataString;
	}
};

CStatus CICEAttributeDataArrayString::GetData( ULONG in_index, const TData** out_ppStr, ULONG& out_nCount ) const
{
	if( in_index >=  GetCount() )
		return CStatus::InvalidArgument; 

	const ICEAttribute& attr = GetICEAttributeRef();

	return GetStringData( in_index, out_ppStr, out_nCount );
}

SICPPSDK_INLINE CStatus CICEAttributeDataArrayString::GetData( ULONG in_index, CString& out_str ) const
{
	const wchar_t* pzStr;
	ULONG nSize;
	CStatus st = GetStringData( in_index, &pzStr, nSize );
	if (st == CStatus::OK)
		out_str = CString( pzStr, nSize );
	return st;
}

SICPPSDK_INLINE CStatus CICEAttributeDataArrayString::SetData( ULONG in_index, const CString& in_str )
{
	if( in_index >=  GetCount() )
		return CStatus::InvalidArgument; 

	const ICEAttribute& attr = GetICEAttributeRef();
	if( attr.IsReadonly() )
		return CStatus::AccessDenied; 

	return CBaseICEAttributeDataArray::SetStringData( in_index, in_str.GetWideString(), in_str.Length() );
}

SICPPSDK_INLINE CString CICEAttributeDataArrayString::operator[]( ULONG i ) const
{
	CString str;
	CStatus st = GetData( i, str );
	assert( st == CStatus::OK );
	return str;
}

/*! \page CICEAttributeDataArrayTypedefs Type Definitions for CICEAttributeDataArray
	The CICEAttributeDataArray class is a template class that encapsulates the following data arrays:

	\li \ref CICEAttributeDataArrayFloat "CICEAttributeDataArrayFloat"
	\li \ref CICEAttributeDataArrayLong "CICEAttributeDataArrayLong"
	\li \ref CICEAttributeDataArrayBool "CICEAttributeDataArrayBool"
	\li \ref CICEAttributeDataArrayVector2f "CICEAttributeDataArrayVector2f"
	\li \ref CICEAttributeDataArrayVector3f "CICEAttributeDataArrayVector3f"
	\li \ref CICEAttributeDataArrayVector4f "CICEAttributeDataArrayVector4f"
	\li \ref CICEAttributeDataArrayQuaternionf "CICEAttributeDataArrayQuaternionf"
	\li \ref CICEAttributeDataArrayRotationf "CICEAttributeDataArrayRotationf"
	\li \ref CICEAttributeDataArrayMatrix3f "CICEAttributeDataArrayMatrix3f"
	\li \ref CICEAttributeDataArrayMatrix4f "CICEAttributeDataArrayMatrix4f"
	\li \ref CICEAttributeDataArrayColor4f "CICEAttributeDataArrayColor4f"
	\li \ref CICEAttributeDataArrayShape "CICEAttributeDataArrayShape"


	\section CICEAttributeDataArrayFloat CICEAttributeDataArrayFloat Type
	\code typedef XSI::CICEAttributeDataArray< float > CICEAttributeDataArrayFloat \endcode
	A CICEAttributeDataArray class of type \c float.
	\since 7.0

	\section CICEAttributeDataArrayLong CICEAttributeDataArrayLong Type
	\code typedef XSI::CICEAttributeDataArray< LONG > CICEAttributeDataArrayLong \endcode
	A CICEAttributeDataArray class of type \c LONG.
	\since 7.0

	\section CICEAttributeDataArrayBool CICEAttributeDataArrayBool Type
	\code typedef XSI::CICEAttributeDataArray< bool > CICEAttributeDataArrayBool \endcode
	The CICEAttributeDataArray< bool > class.
	\since 7.0

	\section CICEAttributeDataArrayVector2f CICEAttributeDataArrayVector2f Type
	\code typedef XSI::CICEAttributeDataArray< CVector2f > CICEAttributeDataArrayVector2f \endcode
	A CICEAttributeDataArray class of type \link MATH::CVector2f CVector2f\endlink.
	\since 7.0

	\section CICEAttributeDataArrayVector3f CICEAttributeDataArrayVector3f Type
	\code typedef XSI::CICEAttributeDataArray< CVector3f > CICEAttributeDataArrayVector3f \endcode
	A CICEAttributeDataArray class of type \link MATH::CVector3f CVector3f\endlink.
	\since 7.0

	\section CICEAttributeDataArrayVector4f CICEAttributeDataArrayVector4f Type
	\code typedef XSI::CICEAttributeDataArray< CVector4f > CICEAttributeDataArrayVector4f \endcode
	A CICEAttributeDataArray class of type \link MATH::CVector4f CVector4f\endlink.
	\since 7.0

	\section CICEAttributeDataArrayQuaternionf CICEAttributeDataArrayQuaternionf Type
	\code typedef XSI::CICEAttributeDataArray< Quaternionf > CICEAttributeDataArrayQuaternionf \endcode
	A CICEAttributeDataArray class of type \link MATH::CQuaternionf CQuaternionf\endlink.
	\since 7.0

	\section CICEAttributeDataArrayRotationf CICEAttributeDataArrayRotationf Type
	\code typedef XSI::CICEAttributeDataArray< CRotationf > CICEAttributeDataArrayRotationf \endcode
	A CICEAttributeDataArray class of type \link MATH::CRotationf CRotationf\endlink.
	\since 7.0

	\section CICEAttributeDataArrayMatrix3f CICEAttributeDataArrayMatrix3f Type
	\code typedef XSI::CICEAttributeDataArray< CMatrix3f > CICEAttributeDataArrayMatrix3f \endcode
	A CICEAttributeDataArray class of type \link MATH::CMatrix3f CMatrix3f\endlink.
	\since 7.0

	\section CICEAttributeDataArrayMatrix4f CICEAttributeDataArrayMatrix4f Type
	\code typedef XSI::CICEAttributeDataArray< CMatrix4f > CICEAttributeDataArrayMatrix4f \endcode
	A CICEAttributeDataArray class of type \link MATH::CMatrix4f CMatrix4f\endlink.
	\since 7.0

	\section CICEAttributeDataArrayColor4f CICEAttributeDataArrayColor4f Type
	\code typedef XSI::CICEAttributeDataArray< CColor4f > CICEAttributeDataArrayColor4f \endcode
	A CICEAttributeDataArray class of type \link MATH::CColor4f CColor4f\endlink.
	\since 7.0

	\section CICEAttributeDataArrayShape CICEAttributeDataArrayShape Type
	\code \typedef XSI::CICEAttributeDataArray< CShape > CICEAttributeDataArrayShape \endcode
	A CICEAttributeDataArray class of type \link MATH::CShape CShape\endlink.
	\since 7.0
*/
typedef XSI::CICEAttributeDataArray< float > CICEAttributeDataArrayFloat;
typedef XSI::CICEAttributeDataArray< LONG > CICEAttributeDataArrayLong;
typedef XSI::CICEAttributeDataArray< bool > CICEAttributeDataArrayBool;
typedef XSI::CICEAttributeDataArray< XSI::MATH::CVector2f > CICEAttributeDataArrayVector2f;
typedef XSI::CICEAttributeDataArray< XSI::MATH::CVector3f > CICEAttributeDataArrayVector3f;
typedef XSI::CICEAttributeDataArray< XSI::MATH::CVector4f > CICEAttributeDataArrayVector4f;
typedef XSI::CICEAttributeDataArray< XSI::MATH::CQuaternionf > CICEAttributeDataArrayQuaternionf;
typedef XSI::CICEAttributeDataArray< XSI::MATH::CRotationf > CICEAttributeDataArrayRotationf;
typedef XSI::CICEAttributeDataArray< XSI::MATH::CMatrix3f > CICEAttributeDataArrayMatrix3f;
typedef XSI::CICEAttributeDataArray< XSI::MATH::CMatrix4f > CICEAttributeDataArrayMatrix4f;
typedef XSI::CICEAttributeDataArray< XSI::MATH::CColor4f > CICEAttributeDataArrayColor4f;
typedef XSI::CICEAttributeDataArray< XSI::MATH::CShape> CICEAttributeDataArrayShape;

template<> SICPPSDK_INLINE XSI::siICENodeDataType CICEAttributeDataArrayFloat::GetDefaultType( ){return siICENodeDataFloat;}
template<> SICPPSDK_INLINE XSI::siICENodeDataType CICEAttributeDataArrayLong::GetDefaultType( ){return siICENodeDataLong;}
template<> SICPPSDK_INLINE XSI::siICENodeDataType CICEAttributeDataArrayVector2f::GetDefaultType( ){return siICENodeDataVector2;}
template<> SICPPSDK_INLINE XSI::siICENodeDataType CICEAttributeDataArrayVector3f::GetDefaultType( ){return siICENodeDataVector3;}
template<> SICPPSDK_INLINE XSI::siICENodeDataType CICEAttributeDataArrayVector4f::GetDefaultType( ){return siICENodeDataVector4;}
template<> SICPPSDK_INLINE XSI::siICENodeDataType CICEAttributeDataArrayQuaternionf::GetDefaultType( ){return siICENodeDataQuaternion;}
template<> SICPPSDK_INLINE XSI::siICENodeDataType CICEAttributeDataArrayMatrix3f::GetDefaultType( ){return siICENodeDataMatrix33;}
template<> SICPPSDK_INLINE XSI::siICENodeDataType CICEAttributeDataArrayMatrix4f::GetDefaultType( ){return siICENodeDataMatrix44;}
template<> SICPPSDK_INLINE XSI::siICENodeDataType CICEAttributeDataArrayColor4f::GetDefaultType( ){return siICENodeDataColor4;}
template<> SICPPSDK_INLINE XSI::siICENodeDataType CICEAttributeDataArrayRotationf::GetDefaultType( ){return siICENodeDataRotation;}
};

#endif // __XSIICEATTRIBUTEDATAARRAY_H__
