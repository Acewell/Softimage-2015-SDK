//*****************************************************************************
/*!
   \file xsi_dataarray.h
   \brief CDataArray classes declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIDATAARRAY_H__
#define __XSIDATAARRAY_H__

#include <sicppsdk.h>
#include <xsi_icenodecontext.h>
#include <xsi_indexset.h>

#include <xsi_vector2f.h>
#include <xsi_vector3f.h>
#include <xsi_vector4f.h>
#include <xsi_quaternionf.h>
#include <xsi_rotationf.h>
#include <xsi_matrix3f.h>
#include <xsi_matrix4f.h>
#include <xsi_color4f.h>
#include <xsi_shape.h>

namespace XSI {

class CBaseDataArray
{
	public:
	friend class ICENodeContext;

	CBaseDataArray() :
		m_nHandle(UINT_MAX),
		m_pData(NULL),
		m_bIsConstant(true),
		m_nCount(1)
	{}

	protected:
	SICPPSDK_INLINE ICENodeContext& GetContextRef();
	SICPPSDK_INLINE ULONG& GetHandleRef();
	SICPPSDK_INLINE void*& GetDataRef();
	SICPPSDK_INLINE bool& GetConstantRef();
	SICPPSDK_INLINE ULONG& GetCountRef();

	virtual SICPPSDK_INLINE CStatus AcquireInputDataArray( XSI::siICENodeDataType in_arrayDataType, ULONG in_nInputPortID, ULONG in_nInstanceIndex );
	virtual SICPPSDK_INLINE CStatus CopyFromInputDataArray( XSI::siICENodeDataType in_arrayDataType, ULONG in_nInputPortID, ULONG in_nInstanceIndex );
	virtual SICPPSDK_INLINE CStatus AcquireOutputDataArray( XSI::siICENodeDataType in_arrayDataType );
	virtual SICPPSDK_INLINE CStatus ReleaseDataArray( );
	SICPPSDK_INLINE CStatus SetCustomTypeData( ULONG in_nIndex, const unsigned char* in_pData, ULONG in_nSize );
	SICPPSDK_INLINE CStatus GetCustomTypeData( ULONG in_nIndex, const unsigned char** out_ppData, ULONG& out_nSize ) const;
	SICPPSDK_INLINE CStatus GetCustomTypeData( ULONG in_nIndex, unsigned char** out_ppData, ULONG& out_nSize ) const;
	SICPPSDK_INLINE unsigned char* ResizeCustomTypeData( ULONG in_nIndex, ULONG in_nSize );

	SICPPSDK_INLINE CStatus SetStringData( ULONG in_nIndex, const wchar_t* in_pData, ULONG in_nSize );
	SICPPSDK_INLINE CStatus GetStringData( ULONG in_nIndex, const wchar_t** out_ppData, ULONG& out_nSize ) const;
	SICPPSDK_INLINE CStatus GetStringData( ULONG in_nIndex, wchar_t** out_ppData, ULONG& out_nSize ) const;
	SICPPSDK_INLINE wchar_t* ResizeStringData( ULONG in_nIndex, ULONG in_nSize );

	ICENodeContext m_ctxt;
	ULONG m_nHandle;
	void* m_pData;
	bool m_bIsConstant;
	ULONG m_nCount;
};

SICPPSDK_INLINE CStatus CBaseDataArray::AcquireInputDataArray( XSI::siICENodeDataType in_arrayDataType, ULONG in_nInputPortID, ULONG in_nInstanceIndex )
{
	return m_ctxt.AcquireInputDataArray( *this, in_arrayDataType, in_nInputPortID, in_nInstanceIndex );
}

SICPPSDK_INLINE CStatus CBaseDataArray::CopyFromInputDataArray( XSI::siICENodeDataType in_arrayDataType, ULONG in_nInputPortID, ULONG in_nInstanceIndex )
{
	return m_ctxt.CopyFromInputDataArray( *this, in_arrayDataType, in_nInputPortID, in_nInstanceIndex );
}

SICPPSDK_INLINE CStatus CBaseDataArray::AcquireOutputDataArray( XSI::siICENodeDataType in_arrayDataType )
{
	return m_ctxt.AcquireOutputDataArray( *this, in_arrayDataType );
}

SICPPSDK_INLINE CStatus CBaseDataArray::ReleaseDataArray( )
{
	return m_ctxt.ReleaseDataArray( *this );
}

SICPPSDK_INLINE CStatus CBaseDataArray::SetCustomTypeData( ULONG in_nIndex, const unsigned char* in_pData, ULONG in_nSize )
{
	return m_ctxt.SetCustomTypeData( *this, in_nIndex, in_pData, in_nSize );
}

SICPPSDK_INLINE CStatus CBaseDataArray::GetCustomTypeData( ULONG in_nIndex, const unsigned char** out_ppData, ULONG& out_nSize ) const
{
	return m_ctxt.GetCustomTypeData( (CBaseDataArray&)*this, in_nIndex, out_ppData, out_nSize );
}

SICPPSDK_INLINE CStatus CBaseDataArray::GetCustomTypeData( ULONG in_nIndex, unsigned char** out_ppData, ULONG& out_nSize ) const
{
	return m_ctxt.GetCustomTypeData( (CBaseDataArray&)*this, in_nIndex, out_ppData, out_nSize );
}

SICPPSDK_INLINE unsigned char* CBaseDataArray::ResizeCustomTypeData( ULONG in_nIndex, ULONG in_nSize )
{
	return m_ctxt.ResizeCustomTypeData( *this, in_nIndex, in_nSize );
}

SICPPSDK_INLINE CStatus CBaseDataArray::SetStringData( ULONG in_nIndex, const wchar_t* in_pData, ULONG in_nSize )
{
	return m_ctxt.SetStringData( *this, in_nIndex, in_pData, in_nSize );
}

SICPPSDK_INLINE CStatus CBaseDataArray::GetStringData( ULONG in_nIndex, const wchar_t** out_ppData, ULONG& out_nSize ) const
{
	return m_ctxt.GetStringData( (CBaseDataArray&)*this, in_nIndex, out_ppData, out_nSize );
}

SICPPSDK_INLINE CStatus CBaseDataArray::GetStringData( ULONG in_nIndex, wchar_t** out_ppData, ULONG& out_nSize ) const
{
	return m_ctxt.GetStringData( (CBaseDataArray&)*this, in_nIndex, out_ppData, out_nSize );
}

SICPPSDK_INLINE wchar_t* CBaseDataArray::ResizeStringData( ULONG in_nIndex, ULONG in_nSize )
{
	return m_ctxt.ResizeStringData( *this, in_nIndex, in_nSize );
}

SICPPSDK_INLINE ICENodeContext& CBaseDataArray::GetContextRef()
{
	return m_ctxt;
}

SICPPSDK_INLINE ULONG& CBaseDataArray::GetHandleRef()
{
	return m_nHandle;
}

SICPPSDK_INLINE void*& CBaseDataArray::GetDataRef()
{
	return m_pData;
}

SICPPSDK_INLINE bool& CBaseDataArray::GetConstantRef()
{
	return m_bIsConstant;
}

SICPPSDK_INLINE ULONG& CBaseDataArray::GetCountRef()
{
	return m_nCount;
}

//*****************************************************************************
/*! \class CDataArray xsi_dataarray.h
	\brief This template class encapsulates the 1D data arrays passed to custom node plug-ins
	during a graph evaluation. The underlying data arrays are zero-based, the following types
	are available:

	\li \ref CDataArrayFloat "CDataArrayFloat"
	\li \ref CDataArrayLong "CDataArrayLong"
	\li \ref CDataArrayBool "CDataArrayBool"
	\li \ref CDataArrayVector2f "CDataArrayVector2f"
	\li \ref CDataArrayVector3f "CDataArrayVector3f"
	\li \ref CDataArrayVector4f "CDataArrayVector4f"
	\li \ref CDataArrayQuaternionf "CDataArrayQuaternionf"
	\li \ref CDataArrayRotationf "CDataArrayRotationf"
	\li \ref CDataArrayMatrix3f "CDataArrayMatrix3f"
	\li \ref CDataArrayMatrix4f "CDataArrayMatrix4f"
	\li \ref CDataArrayColor4f "CDataArrayColor4f"
	\li \ref CDataArrayShape "CDataArrayShape"

	CDataArray objects are created based on the current evaluation context and a specific port
	type (input ports only). Data are usually indexed with a CIndexSet which contains the array
	index set for the whole evaluation graph.

	\note If the class type doesn't match the port data type being evaluated, an error occurs at
	run-time and a class instance is created with an empty array.

	\eg
	\code
		using namespace XSI;

		CDataArrayVector3f outData( in_ctxt );
		CDataArrayVector3f inData( in_ctxt, ID_IN_vector3 );
		CDataArrayFloat scalarData( in_ctxt, ID_IN_factor );

		CIndexSet indexSet( in_ctxt );
		for(CIndexSet::Iterator it = indexSet.Begin(); it.HasNext(); it.Next())
		{
			outData[it] = inData[it];
			outData[it].ScaleInPlace( scalarData[it] );
		}
	\endcode

	\since 7.0
	\sa CDataArray2D, CIndexSet, ICENodeDef, \ref CDataArrayTypedefs "Type Definitions for CDataArray"
 */
//*****************************************************************************

template <class T>
class CDataArray : public CBaseDataArray
{
public:
	/*! \typedef T TData
		\brief TData is the underlying data type of a CDataArray instance. Possible values are:

	 	\li \ref CDataArrayFloat "float"
		\li \ref CDataArrayLong "LONG"
		\li \ref CDataArrayBool "bool"
		\li \ref CDataArrayVector2f "CVector2f"
		\li \ref CDataArrayVector3f "CVector3f"
		\li \ref CDataArrayVector4f "CVector4f"
		\li \ref CDataArrayQuaternionf "CQuaternionf"
		\li \ref CDataArrayRotationf "CRotationf"
		\li \ref CDataArrayMatrix3f "CMatrix3f"
		\li \ref CDataArrayMatrix4f "CMatrix4f"
		\li \ref CDataArrayColor4f "CColor4f"
		\li \link MATH::CShape CShape\endlink
	*/
	typedef T TData;

	/*! Constructor for data types bound to input ports.
	\param in_ctxt ICENode evaluation context.
	\param in_nInputPortID Input port identifier.
	\param in_nInstanceIndex The group instance of the port.
	*/
	SICPPSDK_INLINE CDataArray( ICENodeContext& in_ctxt, ULONG in_nInputPortID, ULONG in_nInstanceIndex=0 ) ;

	/*! Constructor for data types bound to output ports.
	\param in_ctxt ICENode evaluation context.
	*/
	SICPPSDK_INLINE CDataArray( ICENodeContext& in_ctxt ) ;

	/*! Default Constructor.
	*/
	SICPPSDK_INLINE CDataArray< T >( ) ;

	/*! Destructor.
	*/
	SICPPSDK_INLINE ~CDataArray( );

	/*! Accessor to the encapsulated array. This operator is called when reading the data so the return value is read-only.
	\param in_nIndex Index in the array. The index must be smaller than the number of elements in the array, otherwise the
	results are unpredicted.
	\return A read-only reference to the indexed item.
	*/
	SICPPSDK_INLINE const TData& operator[]( ULONG in_nIndex ) const;

	/*! Accessor to elements at a given index.
	\param in_nIndex Index in this zero based array. The index must be smaller than the number of elements in the array,
	otherwise the results are unpredicted.
	\return A reference to the indexed item.
	\note CDataArray< bool >::operator [] cannot be used for setting an array element, you must use CDataArray< bool >::Set instead.
	*/
	SICPPSDK_INLINE TData& operator[]( ULONG in_nIndex ) ;

	/*! Copy the data from a given input port to this object buffer without allocating memory. This is typically used for passing
	data by reference from input to output ports, similar to what the built-in 'pass through' node is doing.

	\param in_nInputPortID Input port identifier.
	\param in_nInstanceIndex The group instance of the port.
	\return CStatus::OK Success
	\return CStatus::InvalidArgument Fails if in_nInputPortID is not an input port identifier or in_nInstanceIndex is invalid.
	\return CStatus::AccessDenied This array is not an output type or wasn't created properly.

	\eg
	\code
		// Copy data from the ID_IN_PointPosition port to the current output port
		XSI::CDataArrayVector3f outData( in_ctxt );
		outData.CopyFrom( ID_IN_PointPosition );
	\endcode
	*/
	SICPPSDK_INLINE CStatus CopyFrom( ULONG in_nInputPortID, ULONG in_nInstanceIndex=0 ) ;

	/*! Returns the number of elements in the array.
	\return Number of elements.
	*/
	SICPPSDK_INLINE ULONG GetCount() const;

	/*! Returns true if the array is constant or false otherwise. A constant array has only one value.
	\return True if constant, false otherwise.
	*/
	SICPPSDK_INLINE bool IsConstant() const;

private:
	SICPPSDK_INLINE void Clear();
	static SICPPSDK_INLINE XSI::siICENodeDataType GetDefaultType( );

#ifdef _DEBUG
	TData* m_pDebugData;
#endif

};

template< class T >
SICPPSDK_INLINE CDataArray<T>::CDataArray( )
{
#ifdef _DEBUG
	m_pDebugData = NULL;
#endif
}

template< class T >
SICPPSDK_INLINE CDataArray<T>::CDataArray( ICENodeContext& in_ctxt, ULONG in_nInputPortID, ULONG in_nInstanceIndex )
{
	m_ctxt = in_ctxt;

	AcquireInputDataArray( GetDefaultType(), in_nInputPortID, in_nInstanceIndex );

#ifdef _DEBUG
	m_pDebugData = (T*)GetDataRef();
#endif
}

template< class T >
SICPPSDK_INLINE CDataArray<T>::CDataArray( ICENodeContext& in_ctxt )
{
	m_ctxt = in_ctxt;

	AcquireOutputDataArray( GetDefaultType() );

#ifdef _DEBUG
	m_pDebugData = (T*)GetDataRef();
#endif
}

template< class T >
SICPPSDK_INLINE CDataArray<T>::~CDataArray( )
{
	ReleaseDataArray( );
}

template< class T >
SICPPSDK_INLINE const T& CDataArray<T>::operator[]( ULONG in_index ) const
{
	assert( !m_bIsConstant ? in_index < m_nCount : true );
	T* pData = (T*)GetDataRef();

	if (!pData) 
	{
		assert( pData != NULL );
		static T defVal;
		return defVal;
	}
	
	if (m_bIsConstant) 
	{
		return *pData;
	}
	
	return pData[in_index];	
}

template< class T >
SICPPSDK_INLINE T& CDataArray<T>::operator[]( ULONG in_index )
{
	assert( !m_bIsConstant ? in_index < m_nCount : true );
	T* pData = (T*)GetDataRef();
	
	if (!pData) 
	{
		assert( pData != NULL );
		static T defVal;
		return defVal;
	}
	
	if (m_bIsConstant) 
	{
		return *pData;
	}
	
	return pData[in_index];		
}

template< class T >
SICPPSDK_INLINE CStatus CDataArray<T>::CopyFrom( ULONG in_nInputPortID, ULONG in_nInstanceIndex )
{
	CStatus st = CopyFromInputDataArray( GetDefaultType(), in_nInputPortID, in_nInstanceIndex );

#ifdef _DEBUG
	m_pDebugData = (T*)GetDataRef();
#endif

	return st;
}

template< class T >
SICPPSDK_INLINE void CDataArray<T>::Clear()
{
	ReleaseDataArray( );
	m_nHandle = UINT_MAX;
	m_nCount = 0;
	m_bIsConstant = false;
}

template< class T >
SICPPSDK_INLINE ULONG CDataArray<T>::GetCount() const
{
	return m_nCount;
}

template< class T >
SICPPSDK_INLINE bool CDataArray<T>::IsConstant() const
{
	return m_bIsConstant;
}

//*****************************************************************************
// NB: Do not use the Doxygen \class tag for this template!!!
/*!
	\brief This class is a specialization of a CDataArray class of type \c bool.

	\since 7.0
	\sa CDataArray2D, CIndexSet, ICENodeDef, \ref CDataArrayBool "CDataArrayBool"
 */
//*****************************************************************************
template<>
class CDataArray< bool > : public CBaseDataArray
{
	public:

	/*! Default Constructor.
	*/
	SICPPSDK_INLINE CDataArray< bool >( ) ;

	/*! Constructor for \c bool array types bound to input ports.
	\param in_ctxt ICENode evaluation context.
	\param in_nInputPortID Input port identifier.
	\param in_nInstanceIndex The group instance of the port.
	*/
	SICPPSDK_INLINE CDataArray< bool >( ICENodeContext& in_ctxt, ULONG in_nInputPortID, ULONG in_nInstanceIndex=0 ) ;

	/*! Constructor for \c bool array types bound to output ports.
	\param in_ctxt ICENode evaluation context.
	*/
	SICPPSDK_INLINE CDataArray< bool >( ICENodeContext& in_ctxt ) ;

	/*! Destructor.
	*/
	SICPPSDK_INLINE ~CDataArray< bool >( );

	/*! Copy the data from a given input port to this object buffer without allocating memory. This is typically used for passing
	data by reference from input to output ports, similar to what the built-in 'pass through' node is doing.

	\param in_nInputPortID Input port identifier.
	\param in_nInstanceIndex The group instance of the port.
	\return CStatus::OK Success
	\return CStatus::InvalidArgument Fails if in_nInputPortID is not an input port identifier or in_nInstanceIndex is invalid.
	\return CStatus::AccessDenied This array is not an output type or wasn't created properly.

	\eg
	\code
		// Copy data from the ID_IN_BOOL port to the current output port
		XSI::CDataArrayBool outData( in_ctxt );
		outData.CopyFrom( ID_IN_BOOL );
	\endcode
	*/
	SICPPSDK_INLINE CStatus CopyFrom( ULONG in_nInputPortID, ULONG in_nInstanceIndex=0 ) ;

	/*! Accessor to the \c bool array. This operator is called when reading the data so the return value is read-only.
	\param in_nIndex Index in the array. The index must be smaller than the number of elements in the array, otherwise the
		results are unpredicted.
	\return A read-only value to the indexed item.
	*/
	SICPPSDK_INLINE const bool operator[]( ULONG in_nIndex ) const;

	/*! Sets the array at a given index with a value.
	\param in_nIndex Index in the array. The index must be smaller than the number of elements in the array, otherwise the
		results are unpredicted.
	\param in_bVal Value to set.
	\return CStatus::OK Success
	*/
	SICPPSDK_INLINE CStatus Set( ULONG in_nIndex, bool in_bVal ) ;

	/*! Returns the number of elements in the array.
	\return Number of elements.
	*/
	SICPPSDK_INLINE ULONG GetCount() const;

	/*! Returns true if the array is constant or false otherwise. A constant array has only one value.
	\return True if constant, false otherwise.
	*/
	SICPPSDK_INLINE bool IsConstant() const;

private:
	SICPPSDK_INLINE void Clear();
	static SICPPSDK_INLINE XSI::siICENodeDataType GetDefaultType( );

	CBitsetHelper m_bitset;
};

SICPPSDK_INLINE CDataArray<bool>::CDataArray( )
{
}

SICPPSDK_INLINE CDataArray<bool>::CDataArray( ICENodeContext& in_ctxt, ULONG in_nInputPortID, ULONG in_nInstanceIndex )
{
	m_ctxt = in_ctxt;

	AcquireInputDataArray( GetDefaultType(), in_nInputPortID, in_nInstanceIndex );

	m_bitset.GetCountRef() = GetCountRef();
	m_bitset.GetArrayRef() = (ULONG*)GetDataRef();
}

SICPPSDK_INLINE CDataArray<bool>::CDataArray( ICENodeContext& in_ctxt )
{
	m_ctxt = in_ctxt;
	m_bIsConstant = true;
	m_nCount = 1;

	AcquireOutputDataArray( GetDefaultType() );

	m_bitset.GetCountRef() = m_nCount;
	m_bitset.GetArrayRef() = (ULONG*)GetDataRef();
}

SICPPSDK_INLINE CDataArray<bool>::~CDataArray( )
{
	ReleaseDataArray( );
}

SICPPSDK_INLINE CStatus CDataArray<bool>::CopyFrom( ULONG in_nInputPortID, ULONG in_nInstanceIndex )
{
	CStatus st = CopyFromInputDataArray( GetDefaultType(), in_nInputPortID, in_nInstanceIndex );

	m_bitset.GetCountRef() = GetCountRef();
	m_bitset.GetArrayRef() = (ULONG*)GetDataRef();

	return st;
}

SICPPSDK_INLINE CStatus CDataArray<bool>::Set( ULONG in_nIndex, bool in_bVal )
{
	return m_bitset.SetBit( in_nIndex, in_bVal );
}

SICPPSDK_INLINE const bool CDataArray<bool>::operator[] ( ULONG in_nIndex ) const
{
	ULONG nIndex = m_bIsConstant ? 0 : in_nIndex;
	return m_bitset.GetBit( nIndex );
}

SICPPSDK_INLINE void CDataArray<bool>::Clear()
{
	ReleaseDataArray( );
	m_nHandle = UINT_MAX;
	m_bIsConstant = true;
	m_nCount = 1;
	m_bitset.Clear();
}

SICPPSDK_INLINE XSI::siICENodeDataType CDataArray<bool>::GetDefaultType()
{
	return siICENodeDataBool;
}

SICPPSDK_INLINE ULONG CDataArray<bool>::GetCount() const
{
	return m_nCount;
}

SICPPSDK_INLINE bool CDataArray<bool>::IsConstant() const
{
	return m_bIsConstant;
}

//*****************************************************************************
/*!
	\brief CDataArrayCustomType is used for storing binary data in a 1D element array of type CDataArrayCustomType::TData.

	\since 8.0 (2010)
	\sa CDataArray2DCustomType, CIndexSet
 */
//*****************************************************************************
class CDataArrayCustomType : public CBaseDataArray
{
	public:
	typedef unsigned char TData;

	/*! Default Constructor.
	*/
	SICPPSDK_INLINE CDataArrayCustomType( ) ;

	/*! Constructor for \c user array types bound to input ports.
	\param in_ctxt ICENode evaluation context.
	\param in_nInputPortID Input port identifier.
	\param in_nInstanceIndex The group instance of the port.
	*/
	SICPPSDK_INLINE CDataArrayCustomType( ICENodeContext& in_ctxt, ULONG in_nInputPortID, ULONG in_nInstanceIndex=0 ) ;

	/*! Constructor for \c bool array types bound to output ports.
	\param in_ctxt ICENode evaluation context.
	*/
	SICPPSDK_INLINE CDataArrayCustomType( ICENodeContext& in_ctxt ) ;

	/*! Destructor.
	*/
	SICPPSDK_INLINE ~CDataArrayCustomType( );

	/*! Copy the data from a given input port to this object buffer without allocating memory. This is typically used for passing
	data by reference from input to output ports, similar to what the built-in 'pass through' node is doing.

	\param in_nInputPortID Input port identifier.
	\param in_nInstanceIndex The group instance of the port.
	\return CStatus::OK Success
	\return CStatus::InvalidArgument Fails if in_nInputPortID is not an input port identifier or in_nInstanceIndex is invalid.
	\return CStatus::AccessDenied This array is not an output type or wasn't created properly.

	\eg
	\code
		// Copy data from the ID_IN_CUSTOM_DATA port to the current output port
		XSI::CDataArrayCustomType outData( in_ctxt );
		outData.CopyFrom( ID_IN_CUSTOM_DATA );
	\endcode
	*/
	SICPPSDK_INLINE CStatus CopyFrom( ULONG in_nInputPortID, ULONG in_nInstanceIndex=0 ) ;

	/*! Sets the array at a specific position with the content of \c in_pData. This API will allocate \c in_nSize bytes
	of memory to store the user data.
	\param in_nIndex Array index to store the user data.
	\param in_pData Pointer to user data.
	\param in_nSize Size in bytes of the data to store.
	\return Success/failure
	\sa CDataArrayCustomType::Resize
	*/
	SICPPSDK_INLINE CStatus SetData( ULONG in_nIndex, const TData* in_pData, ULONG in_nSize );

	/*! Returns a pointer to the user data stored at a specific index. The data is read-only and cannot be modified.
	\note The memory allocated for the data returned by CDataArrayCustomType::GetData is only available within the
		scope of this CDataArrayCustomType instance. Make sure to make a copy of the data if you need to access it
		outside the scope of CDataArrayCustomType.
	\param in_nIndex Array index of the user data to retrieve. The size is 0 if no data is stored at this index.
	\retval out_ppData Read-only pointer to the data.
	\retval out_nSize Size in bytes of the user data.
	\return Success/failure
	*/
	SICPPSDK_INLINE CStatus GetData( ULONG in_nIndex, const TData** out_ppData, ULONG& out_nSize  ) const;

	/*! Returns a pointer to the user data stored at a specific index. The data can be modified directly.
	\note The memory allocated for the data returned by CDataArrayCustomType::GetData is only available within the
		scope of this CDataArrayCustomType instance. Make sure to make a copy of the data if you need to access it
		outside the scope of CDataArrayCustomType.
	\param in_nIndex Array index of the user data to retrieve.
	\retval out_ppData Pointer to the data.
	\retval out_nSize Size in bytes of the user data.
	\return Success/failure
	*/
	SICPPSDK_INLINE CStatus GetData( ULONG in_nIndex, TData** out_ppData, ULONG& out_nSize  ) const;

	/*! Changes the sizes of the user buffer at a specific index to a specified size and returns a pointer to the allocated data.
	\param in_nIndex Array index of the user buffer to resize.
	\param in_nSize The size in bytes of the new array.
	\return Pointer to the allocated data.
	*/
	SICPPSDK_INLINE TData* Resize( ULONG in_nIndex, ULONG in_nSize );

	/*! Returns the number of elements in the array.
	\return Number of elements.
	*/
	SICPPSDK_INLINE ULONG GetCount() const;

	/*! Returns true if the array is constant or false otherwise. A constant array has only one value.
	\return True if constant, false otherwise.
	*/
	SICPPSDK_INLINE bool IsConstant() const;

private:
	SICPPSDK_INLINE void Clear();
	static SICPPSDK_INLINE XSI::siICENodeDataType GetDefaultType( );
};

SICPPSDK_INLINE CDataArrayCustomType::CDataArrayCustomType( )
{
}

SICPPSDK_INLINE CDataArrayCustomType::CDataArrayCustomType( ICENodeContext& in_ctxt, ULONG in_nInputPortID, ULONG in_nInstanceIndex )
{
	m_ctxt = in_ctxt;

	AcquireInputDataArray( GetDefaultType(), in_nInputPortID, in_nInstanceIndex );
}

SICPPSDK_INLINE CDataArrayCustomType::CDataArrayCustomType( ICENodeContext& in_ctxt )
{
	m_ctxt = in_ctxt;

	AcquireOutputDataArray( GetDefaultType() );
}

SICPPSDK_INLINE CDataArrayCustomType::~CDataArrayCustomType( )
{
	ReleaseDataArray( );
}

SICPPSDK_INLINE CStatus CDataArrayCustomType::CopyFrom( ULONG in_nInputPortID, ULONG in_nInstanceIndex )
{
	return CopyFromInputDataArray( GetDefaultType(), in_nInputPortID, in_nInstanceIndex );
}

SICPPSDK_INLINE void CDataArrayCustomType::Clear()
{
	ReleaseDataArray( );
	m_nHandle = UINT_MAX;
	m_bIsConstant = false;
	m_nCount = 0;
}

SICPPSDK_INLINE ULONG CDataArrayCustomType::GetCount() const
{
	return m_nCount;
}

SICPPSDK_INLINE bool CDataArrayCustomType::IsConstant() const
{
	return m_bIsConstant;
}

SICPPSDK_INLINE CStatus CDataArrayCustomType::SetData( ULONG in_nIndex, const TData* in_pData, ULONG in_nSize )
{
	return SetCustomTypeData( in_nIndex, in_pData, in_nSize );
}

SICPPSDK_INLINE CStatus CDataArrayCustomType::GetData( ULONG in_nIndex, const TData** out_ppData, ULONG& out_nSize ) const
{
	return GetCustomTypeData( in_nIndex, out_ppData, out_nSize );
}

SICPPSDK_INLINE CStatus CDataArrayCustomType::GetData( ULONG in_nIndex, TData** out_ppData, ULONG& out_nSize ) const
{
	return GetCustomTypeData( in_nIndex, out_ppData, out_nSize );
}

SICPPSDK_INLINE CDataArrayCustomType::TData* CDataArrayCustomType::Resize( ULONG in_nIndex, ULONG in_nSize )
{
	return ResizeCustomTypeData( in_nIndex, in_nSize );
}

//*****************************************************************************
/*!
	\brief CDataArrayString is used for storing wide character strings in a 1D
	element array.

	\since 9.0 (2011)
	\sa CDataArray2DString, CIndexSet
 */
//*****************************************************************************
class CDataArrayString : public CBaseDataArray
{
	public:
	typedef wchar_t TData;

	/*! Default Constructor.
	*/
	SICPPSDK_INLINE CDataArrayString( ) ;

	/*! Constructor for \c string array types bound to input ports.
	\param in_ctxt ICENode evaluation context.
	\param in_nInputPortID Input port identifier.
	\param in_nInstanceIndex The group instance of the port.
	*/
	SICPPSDK_INLINE CDataArrayString( ICENodeContext& in_ctxt, ULONG in_nInputPortID, ULONG in_nInstanceIndex=0 ) ;

	/*! Constructor for \c string array types bound to output ports.
	\param in_ctxt ICENode evaluation context.
	*/
	SICPPSDK_INLINE CDataArrayString( ICENodeContext& in_ctxt ) ;

	/*! Destructor.
	*/
	SICPPSDK_INLINE ~CDataArrayString( );

	/*! Copy the data from a given input port to this object buffer without allocating memory. This is typically used for passing
	data by reference from input to output ports, similar to what the built-in 'pass through' node is doing.

	\param in_nInputPortID Input port identifier.
	\param in_nInstanceIndex The group instance of the port.
	\return CStatus::OK Success
	\return CStatus::InvalidArgument Fails if in_nInputPortID is not an input port identifier or in_nInstanceIndex is invalid.
	\return CStatus::AccessDenied This array is not an output type or wasn't created properly.

	\eg
	\code
		// Copy data from the ID_IN_STRING port to the current output port
		XSI::CDataArrayString outData( in_ctxt );
		outData.CopyFrom( ID_IN_STRING );
	\endcode
	*/
	SICPPSDK_INLINE CStatus CopyFrom( ULONG in_nInputPortID, ULONG in_nInstanceIndex=0 ) ;

	/*! Sets the array at a specific position with the content of \c in_str.
	\param in_nIndex Array index to store the string.
	\param in_str CString object.
	\return Success/failure
	\sa CDataArrayString::Resize
	*/
	SICPPSDK_INLINE CStatus SetData( ULONG in_nIndex, const CString& in_str );

	/*! Returns a CString object set with a copy of the string stored at a specific index.
	\param in_nIndex Array index of the string to retrieve. The object is empty if no string is stored at this index.
	\retval out_str CString object containing a copy of the string.
	\return Success/failure
	*/
	SICPPSDK_INLINE CStatus GetData( ULONG in_nIndex, CString& out_str ) const;

	/*! Method returning a CString stored at \c in_nIndex.  The CString object will contain a copy of the string.
	\param in_nIndex Index in the array. The index must be smaller than the number of elements in the array, otherwise the
	object returned is empty.
	\return CString object.
	*/
	SICPPSDK_INLINE CString operator[]( ULONG in_nIndex ) const;

	/*! Sets the array at a specific position with the content of \c in_pStr. This API will allocate emmory for \c in_nCount
	characters to store the user data.
	\param in_nIndex Array index to store the user data.
	\param in_pStr Pointer to string data.
	\param in_nCount Number of characters to store.
	\return Success/failure
	\sa CDataArrayString::Resize
	*/
	SICPPSDK_INLINE CStatus SetData( ULONG in_nIndex, const TData* in_pData, ULONG in_nCount );

	/*! Returns a pointer to the string stored at \c in_nIndex. The data is read-only and cannot be modified.
	\note The memory allocated for the data returned by CDataArrayString::GetData is only available within the
		scope of this CDataArrayString instance. Make sure to make a copy of the data if you need to access it
		outside the scope of CDataArrayString.
	\note The string returned in \c out_ppStr is not null-terminated, the caller must make sure to take the number
	of characters in account when manipulating the string.

	\param in_nIndex Array index of the user data to retrieve. The size is 0 if no data is stored at this index.
	\retval out_ppStr Read-only pointer to the string data.
	\retval out_nCount Number of characters in the string.
	\return Success/failure
	*/
	SICPPSDK_INLINE CStatus GetData( ULONG in_nIndex, const TData** out_ppStr, ULONG& out_nCount ) const;

	/*! Returns a pointer to the string stored at \c in_nIndex. The data can be modified directly.
	\note The memory allocated for the data returned by CDataArrayString::GetData is only available within the
		scope of this CDataArrayString instance. Make sure to make a copy of the data if you need to access it
		outside the scope of CDataArrayString.
	\param in_nIndex Array index of the string to retrieve.
	\retval out_ppStr Pointer to the string.
	\retval out_nCount Number of characters in the string.
	\return Success/failure
	*/
	SICPPSDK_INLINE CStatus GetData( ULONG in_nIndex, TData** out_ppStr, ULONG& out_nCount ) const;

	/*! Changes the size of the string buffer at a specific index to a specified size and returns a pointer to the allocated data.
	\param in_nIndex Array index of the string buffer to resize.
	\param in_nCount The number of characters of the new array.
	\return Pointer to the allocated data.
	*/
	SICPPSDK_INLINE TData* Resize( ULONG in_nIndex, ULONG in_nCount );

	/*! Returns the number of characters in the array.
	\return Number of characters.
	*/
	SICPPSDK_INLINE ULONG GetCount() const;

	/*! Returns true if the array is constant or false otherwise. A constant array has only one value.
	\return True if constant, false otherwise.
	*/
	SICPPSDK_INLINE bool IsConstant() const;

private:
	SICPPSDK_INLINE void Clear();
	static SICPPSDK_INLINE XSI::siICENodeDataType GetDefaultType( );
};

SICPPSDK_INLINE CDataArrayString::CDataArrayString( )
{
}

SICPPSDK_INLINE CDataArrayString::CDataArrayString( ICENodeContext& in_ctxt, ULONG in_nInputPortID, ULONG in_nInstanceIndex )
{
	m_ctxt = in_ctxt;

	AcquireInputDataArray( GetDefaultType(), in_nInputPortID, in_nInstanceIndex );
}

SICPPSDK_INLINE CDataArrayString::CDataArrayString( ICENodeContext& in_ctxt )
{
	m_ctxt = in_ctxt;

	AcquireOutputDataArray( GetDefaultType() );
}

SICPPSDK_INLINE CDataArrayString::~CDataArrayString( )
{
	ReleaseDataArray( );
}

SICPPSDK_INLINE CStatus CDataArrayString::CopyFrom( ULONG in_nInputPortID, ULONG in_nInstanceIndex )
{
	return CopyFromInputDataArray( GetDefaultType(), in_nInputPortID, in_nInstanceIndex );
}

SICPPSDK_INLINE void CDataArrayString::Clear()
{
	ReleaseDataArray( );
	m_nHandle = UINT_MAX;
	m_bIsConstant = false;
	m_nCount = 0;
}

SICPPSDK_INLINE ULONG CDataArrayString::GetCount() const
{
	return m_nCount;
}

SICPPSDK_INLINE bool CDataArrayString::IsConstant() const
{
	return m_bIsConstant;
}

SICPPSDK_INLINE CStatus CDataArrayString::SetData( ULONG in_nIndex, const CString& in_str )
{
	return SetStringData( in_nIndex, in_str.GetWideString(), in_str.Length() );
}

SICPPSDK_INLINE CStatus CDataArrayString::GetData( ULONG in_nIndex, CString& out_str ) const
{
	const wchar_t* pzStr;
	ULONG nSize;
	CStatus st = GetStringData( in_nIndex, &pzStr, nSize );
	out_str = CString( pzStr, nSize );
	return st;
}

SICPPSDK_INLINE CString CDataArrayString::operator[]( ULONG i ) const
{
	CString str;
	GetData( i, str );
	return str;
}

SICPPSDK_INLINE CStatus CDataArrayString::SetData( ULONG in_nIndex, const TData* in_pData, ULONG in_nSize )
{
	return SetStringData( in_nIndex, in_pData, in_nSize );
}

SICPPSDK_INLINE CStatus CDataArrayString::GetData( ULONG in_nIndex, const TData** out_ppData, ULONG& out_nSize ) const
{
	return GetStringData( in_nIndex, out_ppData, out_nSize );
}

SICPPSDK_INLINE CStatus CDataArrayString::GetData( ULONG in_nIndex, TData** out_ppData, ULONG& out_nSize ) const
{
	return GetStringData( in_nIndex, out_ppData, out_nSize );
}

SICPPSDK_INLINE CDataArrayString::TData* CDataArrayString::Resize( ULONG in_nIndex, ULONG in_nSize )
{
	return ResizeStringData( in_nIndex, in_nSize );
}

/*! \page CDataArrayTypedefs Type Definitions for CDataArray
	The CDataArray class is a template class that encapsulates the following 1D data arrays:

	\li \ref CDataArrayFloat "CDataArrayFloat"
	\li \ref CDataArrayLong "CDataArrayLong"
	\li \ref CDataArrayBool "CDataArrayBool"
	\li \ref CDataArrayVector2f "CDataArrayVector2f"
	\li \ref CDataArrayVector3f "CDataArrayVector3f"
	\li \ref CDataArrayVector4f "CDataArrayVector4f"
	\li \ref CDataArrayQuaternionf "CDataArrayQuaternionf"
	\li \ref CDataArrayRotationf "CDataArrayRotationf"
	\li \ref CDataArrayMatrix3f "CDataArrayMatrix3f"
	\li \ref CDataArrayMatrix4f "CDataArrayMatrix4f"
	\li \ref CDataArrayColor4f "CDataArrayColor4f"
	\li \ref CDataArrayShape "CDataArrayShape"

	\section CDataArrayFloat CDataArrayFloat Type
	\code typedef CDataArray< float > CDataArrayFloat \endcode
	A CDataArray class of type \c float.
	\since 7.0

	\section CDataArrayLong CDataArrayLong Type
	\code typedef CDataArray< LONG > CDataArrayLong \endcode
	A CDataArray class of type \c LONG.
	\since 7.0

	\section CDataArrayBool CDataArrayBool Type
	\code typedef CDataArray< bool > CDataArrayBool \endcode
	The CDataArray< bool > class.
	\since 7.0

	\section CDataArrayVector2f CDataArrayVector2f Type
	\code typedef CDataArray< CVector2f > CDataArrayVector2f
	\endcode A CDataArray class of type \link MATH::CVector2f CVector2f\endlink.
	\since 7.0

	\section CDataArrayVector3f CDataArrayVector3f Type
	\code typedef CDataArray< CVector3f > CDataArrayVector3f \endcode
	A CDataArray class of type \link MATH::CVector3f CVector3f\endlink.
	\since 7.0

	\section CDataArrayVector4f CDataArrayVector4f Type
	\code typedef CDataArray< CVector4f > CDataArrayVector4f \endcode
	A CDataArray class of type \link MATH::CVector4f CVector4f\endlink.
	\since 7.0

	\section CDataArrayQuaternionf CDataArrayQuaternionf Type
	\code typedef CDataArray< Quaternionf > CDataArrayQuaternionf \endcode
	A CDataArray class of type \link MATH::CQuaternionf CQuaternionf\endlink.
	\since 7.0

	\section CDataArrayRotationf CDataArrayRotationf Type
	\code typedef CDataArray< CRotationf > CDataArrayRotationf \endcode
	A CDataArray class of type \link MATH::CRotationf CRotationf\endlink.
	\since 7.0

	\section CDataArrayMatrix3f CDataArrayMatrix3f Type
	\code typedef CDataArray< CMatrix3f > CDataArrayMatrix3f \endcode
	A CDataArray class of type \link MATH::CMatrix3f CMatrix3f\endlink.
	\since 7.0

	\section CDataArrayMatrix4f CDataArrayMatrix4f Type
	\code typedef CDataArray< CMatrix4f > CDataArrayMatrix4f \endcode
	A CDataArray class of type \link MATH::CMatrix4f CMatrix4f\endlink.
	\since 7.0

	\section CDataArrayColor4f CDataArrayColor4f Type
	\code typedef CDataArray< CColor4f > CDataArrayColor4f \endcode
	A CDataArray class of type \link MATH::CColor4f CColor4f\endlink.
	\since 7.0

	\section CDataArrayShape CDataArrayShape Type
	\code typedef CDataArray< CShape > CDataArrayShape \endcode
	A CDataArray class of type \link MATH::CShape CShape\endlink.
	\since 7.0
*/
typedef XSI::CDataArray< float > CDataArrayFloat;
typedef XSI::CDataArray< LONG > CDataArrayLong;
typedef XSI::CDataArray< bool > CDataArrayBool;
typedef XSI::CDataArray< XSI::MATH::CVector2f > CDataArrayVector2f;
typedef XSI::CDataArray< XSI::MATH::CVector3f > CDataArrayVector3f;
typedef XSI::CDataArray< XSI::MATH::CVector4f > CDataArrayVector4f;
typedef XSI::CDataArray< XSI::MATH::CQuaternionf > CDataArrayQuaternionf;
typedef XSI::CDataArray< XSI::MATH::CRotationf > CDataArrayRotationf;
typedef XSI::CDataArray< XSI::MATH::CMatrix3f > CDataArrayMatrix3f;
typedef XSI::CDataArray< XSI::MATH::CMatrix4f > CDataArrayMatrix4f;
typedef XSI::CDataArray< XSI::MATH::CColor4f > CDataArrayColor4f;
typedef XSI::CDataArray< XSI::MATH::CShape> CDataArrayShape;

template<> SICPPSDK_INLINE XSI::siICENodeDataType CDataArrayFloat::GetDefaultType( ){return siICENodeDataFloat;}
template<> SICPPSDK_INLINE XSI::siICENodeDataType CDataArrayLong::GetDefaultType( ){return siICENodeDataLong;}
template<> SICPPSDK_INLINE XSI::siICENodeDataType CDataArrayVector2f::GetDefaultType( ){return siICENodeDataVector2;}
template<> SICPPSDK_INLINE XSI::siICENodeDataType CDataArrayVector3f::GetDefaultType( ){return siICENodeDataVector3;}
template<> SICPPSDK_INLINE XSI::siICENodeDataType CDataArrayVector4f::GetDefaultType( ){return siICENodeDataVector4;}
template<> SICPPSDK_INLINE XSI::siICENodeDataType CDataArrayQuaternionf::GetDefaultType( ){return siICENodeDataQuaternion;}
template<> SICPPSDK_INLINE XSI::siICENodeDataType CDataArrayMatrix3f::GetDefaultType( ){return siICENodeDataMatrix33;}
template<> SICPPSDK_INLINE XSI::siICENodeDataType CDataArrayMatrix4f::GetDefaultType( ){return siICENodeDataMatrix44;}
template<> SICPPSDK_INLINE XSI::siICENodeDataType CDataArrayColor4f::GetDefaultType( ){return siICENodeDataColor4;}
template<> SICPPSDK_INLINE XSI::siICENodeDataType CDataArrayRotationf::GetDefaultType( ){return siICENodeDataRotation;}
template<> SICPPSDK_INLINE XSI::siICENodeDataType CDataArrayShape::GetDefaultType( ){return siICENodeDataShape;}
SICPPSDK_INLINE XSI::siICENodeDataType CDataArrayCustomType::GetDefaultType(){return siICENodeDataCustomType;}
SICPPSDK_INLINE XSI::siICENodeDataType CDataArrayString::GetDefaultType(){return siICENodeDataString;}

};

#endif // __XSIDATAARRAY_H__
