//*****************************************************************************
/*!
   \file xsi_dataarray2D.h
   \brief CDataArray2D classes declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIDATAARRAY2D_H__
#define __XSIDATAARRAY2D_H__

#include <sicppsdk.h>
#include <xsi_icenodecontext.h>
#include <xsi_indexset.h>
#include <xsi_dataarray.h>

#include <xsi_vector2f.h>
#include <xsi_vector3f.h>
#include <xsi_vector4f.h>
#include <xsi_quaternionf.h>
#include <xsi_rotationf.h>
#include <xsi_matrix3f.h>
#include <xsi_matrix4f.h>
#include <xsi_color4f.h>

namespace XSI {

class ICENodeContext;

class CBaseDataArray2D : public CBaseDataArray
{
	public:
	friend class ICENodeContext;

	CBaseDataArray2D() : m_bIsSubArrayConstant(false) {}

	protected:
	SICPPSDK_INLINE CStatus AcquireInputDataArray( XSI::siICENodeDataType in_arrayDataType, ULONG in_nInputPortID, ULONG in_nInstanceIndex );
	SICPPSDK_INLINE CStatus CopyFromInputDataArray( XSI::siICENodeDataType in_arrayDataType, ULONG in_nInputPortID, ULONG in_nInstanceIndex );
	SICPPSDK_INLINE CStatus AcquireOutputDataArray( XSI::siICENodeDataType in_arrayDataType );
	SICPPSDK_INLINE CStatus ReleaseDataArray( );
	SICPPSDK_INLINE CStatus GetSubArray( ULONG in_nArrayIndex, void*& out_ppData, ULONG& out_nCount, ULONG& out_nStartBit ) const;
	SICPPSDK_INLINE CStatus ResizeSubArray( ULONG in_nArrayIndex, ULONG in_nSize, void*& out_ppData, ULONG& out_nCount, ULONG& out_nStartBit );
	SICPPSDK_INLINE bool GetSubArrayConstant() const;
	SICPPSDK_INLINE bool& GetSubArrayConstantRef();

	SICPPSDK_INLINE CStatus SetCustomTypeData2D( ULONG in_nAccessIndex, ULONG in_nIndex, const unsigned char* in_pData, ULONG in_nSize );
	SICPPSDK_INLINE CStatus GetCustomTypeData2D( ULONG in_nAccessIndex, ULONG in_nIndex, const unsigned char** out_ppData, ULONG& out_nSize ) const;
	SICPPSDK_INLINE CStatus GetCustomTypeData2D( ULONG in_nAccessIndex, ULONG in_nIndex, unsigned char** out_ppData, ULONG& out_nSize ) const;
	SICPPSDK_INLINE unsigned char* ResizeCustomTypeData2D( ULONG in_nAccessIndex, ULONG in_nArrayIndex, ULONG in_nSize );

	SICPPSDK_INLINE CStatus SetStringData2D( ULONG in_nAccessIndex, ULONG in_nIndex, const wchar_t* in_pData, ULONG in_nCount );
	SICPPSDK_INLINE CStatus GetStringData2D( ULONG in_nAccessIndex, ULONG in_nIndex, const wchar_t** out_ppData, ULONG& out_nCount ) const;
	SICPPSDK_INLINE CStatus GetStringData2D( ULONG in_nAccessIndex, ULONG in_nIndex, wchar_t** out_ppData, ULONG& out_nCount ) const;
	SICPPSDK_INLINE wchar_t* ResizeStringData2D( ULONG in_nAccessIndex, ULONG in_nArrayIndex, ULONG in_nCount );

	private:
	bool m_bIsSubArrayConstant;
};

SICPPSDK_INLINE CStatus CBaseDataArray2D::AcquireInputDataArray( XSI::siICENodeDataType in_arrayDataType, ULONG in_nInputPortID, ULONG in_nInstanceIndex )
{
	return m_ctxt.AcquireInputDataArray2D( *this, in_arrayDataType, in_nInputPortID, in_nInstanceIndex );
}

SICPPSDK_INLINE CStatus CBaseDataArray2D::CopyFromInputDataArray( XSI::siICENodeDataType in_arrayDataType, ULONG in_nInputPortID, ULONG in_nInstanceIndex )
{
	return m_ctxt.CopyFromInputDataArray2D( *this, in_arrayDataType, in_nInputPortID, in_nInstanceIndex );
}

SICPPSDK_INLINE CStatus CBaseDataArray2D::AcquireOutputDataArray( XSI::siICENodeDataType in_arrayDataType )
{
	return m_ctxt.AcquireOutputDataArray2D( *this, in_arrayDataType );
}

SICPPSDK_INLINE CStatus CBaseDataArray2D::ReleaseDataArray( )
{
	return m_ctxt.ReleaseDataArray( *this );
}

SICPPSDK_INLINE CStatus CBaseDataArray2D::ResizeSubArray( ULONG in_nArrayIndex, ULONG in_nSize, void*& out_ppData, ULONG& out_nCount, ULONG& out_nStartBit )
{
	return m_ctxt.ResizeSubArray( *this, in_nArrayIndex, in_nSize, out_ppData, out_nCount, out_nStartBit );
}

SICPPSDK_INLINE CStatus CBaseDataArray2D::GetSubArray( ULONG in_nArrayIndex, void*& out_ppData, ULONG& out_nCount, ULONG& out_nStartBit ) const
{
	return m_ctxt.GetSubArray( (CBaseDataArray2D&)*this, in_nArrayIndex, out_ppData, out_nCount, out_nStartBit );
}

SICPPSDK_INLINE bool& CBaseDataArray2D::GetSubArrayConstantRef()
{
	return m_bIsSubArrayConstant;
}

SICPPSDK_INLINE bool CBaseDataArray2D::GetSubArrayConstant() const
{
	return m_bIsSubArrayConstant;
}

SICPPSDK_INLINE CStatus CBaseDataArray2D::SetCustomTypeData2D( ULONG in_nAccessIndex, ULONG in_nIndex, const unsigned char* in_pData, ULONG in_nSize )
{
	return m_ctxt.SetCustomTypeData2D( *this, in_nAccessIndex, in_nIndex, in_pData, in_nSize );
}

SICPPSDK_INLINE CStatus CBaseDataArray2D::GetCustomTypeData2D( ULONG in_nAccessIndex, ULONG in_nIndex, const unsigned char** out_ppData, ULONG& out_nSize ) const
{
	return m_ctxt.GetCustomTypeData2D( (CBaseDataArray&)*this, in_nAccessIndex, in_nIndex, out_ppData, out_nSize );
}

SICPPSDK_INLINE CStatus CBaseDataArray2D::GetCustomTypeData2D( ULONG in_nAccessIndex, ULONG in_nIndex, unsigned char** out_ppData, ULONG& out_nSize ) const
{
	return m_ctxt.GetCustomTypeData2D( (CBaseDataArray&)*this, in_nAccessIndex, in_nIndex, out_ppData, out_nSize );
}

SICPPSDK_INLINE unsigned char* CBaseDataArray2D::ResizeCustomTypeData2D( ULONG in_nAccessIndex, ULONG in_nArrayIndex, ULONG in_nSize )
{
	return m_ctxt.ResizeCustomTypeData2D( *this, in_nAccessIndex, in_nArrayIndex, in_nSize );
}

SICPPSDK_INLINE CStatus CBaseDataArray2D::SetStringData2D( ULONG in_nAccessIndex, ULONG in_nIndex, const wchar_t* in_pData, ULONG in_nCount )
{
	return m_ctxt.SetStringData2D( *this, in_nAccessIndex, in_nIndex, in_pData, in_nCount );
}

SICPPSDK_INLINE CStatus CBaseDataArray2D::GetStringData2D( ULONG in_nAccessIndex, ULONG in_nIndex, const wchar_t** out_ppData, ULONG& out_nCount ) const
{
	return m_ctxt.GetStringData2D( (CBaseDataArray&)*this, in_nAccessIndex, in_nIndex, out_ppData, out_nCount );
}

SICPPSDK_INLINE CStatus CBaseDataArray2D::GetStringData2D( ULONG in_nAccessIndex, ULONG in_nIndex, wchar_t** out_ppData, ULONG& out_nCount ) const
{
	return m_ctxt.GetStringData2D( (CBaseDataArray&)*this, in_nAccessIndex, in_nIndex, out_ppData, out_nCount );
}

SICPPSDK_INLINE wchar_t* CBaseDataArray2D::ResizeStringData2D( ULONG in_nAccessIndex, ULONG in_nArrayIndex, ULONG in_nCount )
{
	return m_ctxt.ResizeStringData2D( *this, in_nAccessIndex, in_nArrayIndex, in_nCount );
}

//*****************************************************************************
/*! \class CDataArray2D xsi_dataarray2D.h
	\brief This template class encapsulates 2D data arrays that are passed to custom node plug-ins
	during a graph evaluation. The underlying data arrays are zero-based, the following types are
	available:

	\li \ref CDataArray2DFloat "CDataArray2DFloat"
	\li \ref CDataArray2DLong "CDataArray2DLong"
	\li \ref CDataArray2DBool "CDataArray2DBool"
	\li \ref CDataArray2DVector2f "CDataArray2DVector2f"
	\li \ref CDataArray2DVector3f "CDataArray2DVector3f"
	\li \ref CDataArray2DVector4f "CDataArray2DVector4f"
	\li \ref CDataArray2DQuaternionf "CDataArray2DQuaternionf"
	\li \ref CDataArray2DRotationf "CDataArray2DRotationf"
	\li \ref CDataArray2DMatrix3f "CDataArray2DMatrix3f"
	\li \ref CDataArray2DMatrix4f "CDataArray2DMatrix4f"
	\li \ref CDataArray2DColor4f "CDataArray2DColor4f"
	\li \ref CDataArray2DShape "CDataArray2DShape"

	As for CDataArray, instances of CDataArray2D are created based on the current evaluation context
	and a specific port type (input ports only). CDataArray2D objects are also indexed with CIndexSet
	objects. Unlike CDataArray, CDataArray2D contains sub-arrays where data can be accessed  through
	the CDataArray2D::Accessor class.

	\note If the class type doesn't match the port data type being evaluated, an error occurs at run-time
		and a class instance is created with an empty array.

	\sa CDataArray2D, CIndexSet, ICENodeDef, \ref CDataArray2DTypedefs "Type Definitions for CDataArray2D"
	\since 7.0

	\eg
	\code
		using namespace XSI;

		XSIPLUGINCALLBACK CStatus Custom2DArray_Evaluate( ICENodeContext& in_ctxt )
		{
			// The current output port being evaluated...
			ULONG out_portID = in_ctxt.GetEvaluatedOutputPortID( );

			switch( out_portID )
			{
				case ID_OutPort:
				{
					// Here's how we access the input data buffers for each port
					CDataArray2DVector3f InPortData( in_ctxt, ID_InPort );

					// Declare the output port array ...
					CDataArray2DVector3f outData( in_ctxt );

					// We need a CIndexSet to iterate over the data
					CIndexSet indexSet( in_ctxt );

					for(CIndexSet::Iterator it = indexSet.Begin(); it.HasNext(); it.Next())
					{
						// Creates an Accessor object to iterate over the 2D array data
						CDataArray2DVector3f::Accessor floatArray = InPortData[it];

						// Output arrays must always be initialized first
						CDataArray2DVector3f::Accessor outAccessor = outData.Resize( it, floatArray.GetCount( ) );

						for (ULONG i=0; i<floatArray.GetCount( ); i++)
						{
							outAccessor[i].Scale( floatArray[i].GetX(), floatArray[i] );
						}
					}
				}
				break;
			};

			return CStatus::OK;
		}
	\endcode
 */
//*****************************************************************************

template <class T>
class CDataArray2D : public CBaseDataArray2D
{
	public:

	/*! \typedef T TData
	 *  \brief TData is the underlying data type of a CDataArray2D instance. Possible values are:

	 	\li \ref CDataArray2DFloat "float"
		\li \ref CDataArray2DLong "LONG"
		\li \ref CDataArray2DBool "bool"
		\li \ref CDataArray2DVector2f "CVector2f"
		\li \ref CDataArray2DVector3f "CVector3f"
		\li \ref CDataArray2DVector4f "CVector4f"
		\li \ref CDataArray2DQuaternionf "CQuaternionf"
		\li \ref CDataArray2DRotationf "CRotationf"
		\li \ref CDataArray2DMatrix3f "CMatrix3f"
		\li \ref CDataArray2DMatrix4f "CMatrix4f"
		\li \ref CDataArray2DColor4f "CColor4f"
		\li \ref CDataArray2DShape "CShape"
	*/
	typedef T TData;

	//*****************************************************************************
	/*! \class Accessor xsi_dataarray2D.h
		\brief A class for accessing the sub-array data of CDataArray2D objects.
		\since 7.0
		\sa CIndexSet, CDataArray, CDataArray2D
	 */
	//*****************************************************************************

	class Accessor
	{
		public:
		friend class CDataArray2D<T>;

		/*! Constructor.
		*/
		Accessor( ) : m_pData(NULL), m_nCount(0), m_bIsConstant(false)
		{
		}

		/*! Constructs an %Accessor object from another %Accessor object.
		\param in_accessor constant %Accessor object.*/
		Accessor( const Accessor& in_accessor )
		{
			*this = in_accessor;
		}

		/*! Assignment operator.
		\param in_accessor constant class object.
		\return A reference to this %Accessor.
		*/
		Accessor& operator=( const Accessor& in_accessor )
		{
			m_pData = in_accessor.m_pData;
			m_nCount = in_accessor.m_nCount;
			m_bIsConstant = in_accessor.m_bIsConstant;
			return *this;
		}

		/*! Returns the number of elements in the array.
		\return Number of elements.
		*/
		ULONG GetCount() const
		{
			return m_nCount;
		}

		/*! %Accessor to elements at a given index. This operator is called when reading the data so the return value is read-only.
		\param in_nIndex Index in the array. The index must be smaller than the number of elements in the array, otherwise the
			results are unpredicted.
		\return A read-only reference to the indexed item.
		*/
		const T& operator[]( ULONG in_nIndex ) const
		{
			return m_pData[ m_bIsConstant ? 0 : in_nIndex ];
		}

		/*! %Accessor to elements at a given index. This operator can also be used to access and modify the sub-array stored at
		the in_nIndex position.
		\param in_nIndex Index in this zero-based array. The index must be smaller than the number of elements in the array,
			otherwise the results are unpredicted.
		\return A reference to the indexed item.

		\eg
		\code
			// Demonstrates how to access/modify the CDataArray2D<T> sub-arrays from the CDataArray2D<T>::Accessor class.
			using namespace XSI;

			XSIPLUGINCALLBACK CStatus UnionArrayNode_Evaluate( ICENodeContext& in_ctxt )
			{
				// The current output port being evaluated...
				ULONG out_portID = in_ctxt.GetEvaluatedOutputPortID( );

				switch( out_portID )
				{
					case ID_OUT_result:
					{
						// Get the output port array ...
						CDataArray2DLong outData( in_ctxt );

						// Get the input data buffers for each port
						CDataArray2DLong InArray1Data( in_ctxt, ID_IN_InArray1 );
						CDataArray2DLong InArray2Data( in_ctxt, ID_IN_InArray2 );

						// We need a CIndexSet to iterate over the data
						CIndexSet indexSet( in_ctxt );
						for(CIndexSet::Iterator it = indexSet.Begin(); it.HasNext(); it.Next())
						{
							CDataArray2DLong::Accessor a1 = InArray1Data[it];
							CDataArray2DLong::Accessor a2 = InArray2Data[it];

							// Sort arrays in place
							ULONG nCount1 = a1.GetCount();
							ULONG nCount2 = a2.GetCount();
							std::sort( &a1[0], &a1[0]+nCount1 );
							std::sort( &a2[0], &a2[0]+nCount2 );

							// Resize out to max array
							CDataArray2DLong::Accessor out = outData.Resize( it, nCount1 + nCount2 );

							// Union of a1 + a2
							LONG* pLast = std::set_union( &a1[0], &a1[0]+nCount1, &a2[0], &a2[0]+nCount2, &out[0]);

							// resize out with number of elements in union
							ULONG nOutCount = (ULONG)(pLast - &out[0]);
							outData.Resize( it, nOutCount );
						}
					}
					break;
				};

				return CStatus::OK;
			}
		\endcode
		*/
		T& operator[]( ULONG in_nIndex )
		{
			return m_pData[ m_bIsConstant ? 0 : in_nIndex ];
		}

		private:
		void*& GetDataRef()
		{
			return (void*&)m_pData;
		}

		ULONG& GetCountRef()
		{
			return m_nCount;
		}

		void SetAsConstant( bool in_bConst )
		{
			m_bIsConstant = in_bConst;
		}

		T* m_pData;
		ULONG m_nCount;
		bool m_bIsConstant;
	};

	/*! Constructor for data types bound to input ports.
	\param in_ctxt ICENode evaluation context.
	\param in_nInputPortID Input port identifier.
	\param in_nInstanceIndex The group instance of the port.
	*/
	SICPPSDK_INLINE CDataArray2D( ICENodeContext& in_ctxt, ULONG in_nInputPortID, ULONG in_nInstanceIndex=0 ) ;

	/*! Constructor for data types bound to output ports.
	\param in_ctxt ICENode evaluation context.
	*/
	SICPPSDK_INLINE CDataArray2D( ICENodeContext& in_ctxt ) ;

	/*! Default constructor.
	*/
	SICPPSDK_INLINE CDataArray2D( ) ;

	/*! Destructor.
	*/
	SICPPSDK_INLINE ~CDataArray2D( );

	/*! Copy the data from a given input port to this object buffer without allocating memory. This is typically used for passing
	data by reference from input to output ports, similar to what the built-in 'pass through' node is doing.

	\param in_nInputPortID Input port identifier.
	\param in_nInstanceIndex The group instance of the port.
	\return CStatus::OK Success
	\return CStatus::InvalidArgument Fails if in_nInputPortID is not an input port identifier or in_nInstanceIndex is invalid.
	\return CStatus::AccessDenied This array is not an output type or wasn't created properly.

	\eg
	\code
		// Copy data from the ID_IN_2DPoints port to the current output port
		XSI::CDataArray2DVector3f outData( in_ctxt );
		outData.CopyFrom( ID_IN_2DPoints );
	\endcode
	*/
	SICPPSDK_INLINE CStatus CopyFrom( ULONG in_nInputPortID, ULONG in_nInstanceIndex=0 ) ;

	/*! Returns an accessor at a given index. This operator is called when reading the data so the return value is read-only.
	\param in_nArrayIndex Index in the array. The index must be smaller than the number of elements in the array, otherwise the
		results are unpredicted.
	\return %Accessor object.
	*/
	SICPPSDK_INLINE Accessor operator[]( ULONG in_nArrayIndex ) const;

	/*! Changes the size of the sub-array at a given position and returns an accessor pointing to the resized sub-array.
	\param in_nArrayIndex Index in the array. The index must be smaller than the number of elements in the array, otherwise the
	results are unpredicted.
	\param in_nSize The new size.
	\return %Accessor object.
	*/
	SICPPSDK_INLINE Accessor Resize( ULONG in_nArrayIndex, ULONG in_nSize );

	/*! Returns the number of elements in the array.
	\return Number of elements.
	*/
	SICPPSDK_INLINE ULONG GetCount() const;

	/*! Returns true if the array is constant or false otherwise. A constant array has only one value.
	\return True if constant, false otherwise.
	*/
	SICPPSDK_INLINE bool IsConstant() const;

private:
	SICPPSDK_INLINE Accessor Get( ULONG in_nArrayIndex ) const;
	SICPPSDK_INLINE void Clear();
	static SICPPSDK_INLINE XSI::siICENodeDataType GetDefaultType( );
};

template< class T >
SICPPSDK_INLINE CDataArray2D<T>::CDataArray2D( ICENodeContext& in_ctxt, ULONG in_nInputPortID, ULONG in_nInstanceIndex )
{
	m_ctxt = in_ctxt;

	AcquireInputDataArray( GetDefaultType(), in_nInputPortID, in_nInstanceIndex );
}

template< class T >
SICPPSDK_INLINE CDataArray2D<T>::CDataArray2D( ICENodeContext& in_ctxt )
{
	m_ctxt = in_ctxt;

	AcquireOutputDataArray( GetDefaultType() );
}

template< class T >
SICPPSDK_INLINE CDataArray2D<T>::~CDataArray2D( )
{
	ReleaseDataArray( );
}

template< class T >
SICPPSDK_INLINE CDataArray2D<T>::CDataArray2D( )
{
}

template< class T >
SICPPSDK_INLINE CStatus CDataArray2D<T>::CopyFrom( ULONG in_nInputPortID, ULONG in_nInstanceIndex )
{
	return CopyFromInputDataArray( GetDefaultType(), in_nInputPortID, in_nInstanceIndex );
}

template< class T >
SICPPSDK_INLINE typename CDataArray2D<T>::Accessor CDataArray2D<T>::Get( ULONG in_nArrayIndex ) const
{
	Accessor a;
	ULONG nNotused;
	GetSubArray( in_nArrayIndex, a.GetDataRef(), (ULONG&)a.GetCountRef(), nNotused );
	a.SetAsConstant( GetSubArrayConstant() );

	return a;
}

template< class T >
SICPPSDK_INLINE typename CDataArray2D<T>::Accessor CDataArray2D<T>::operator[]( ULONG in_nArrayIndex ) const
{
	return Get( in_nArrayIndex );
}

template< class T >
SICPPSDK_INLINE typename CDataArray2D<T>::Accessor CDataArray2D<T>::Resize( ULONG in_nArrayIndex, ULONG in_nSize )
{
	ULONG nNotused;
	Accessor a;
	ResizeSubArray( in_nArrayIndex, in_nSize, a.GetDataRef(), (ULONG&)a.GetCountRef(), nNotused );
	a.SetAsConstant( GetSubArrayConstant() );
	return a;
}

template< class T >
SICPPSDK_INLINE void CDataArray2D<T>::Clear()
{
	ReleaseDataArray( );
	m_nHandle = UINT_MAX;
	m_nCount = 0;
	m_bIsConstant = false;
	m_bIsSubArrayConstant = false;
}

template< class T >
SICPPSDK_INLINE ULONG CDataArray2D<T>::GetCount() const
{
	return m_nCount;
}

template< class T >
SICPPSDK_INLINE bool CDataArray2D<T>::IsConstant() const
{
	return m_bIsConstant;
}

//*****************************************************************************
// NB: Do not use the Doxygen \class tag for this template!!!
/*!
	\brief This class is a specialization of a CDataArray2D class of type \c bool.

	\since 7.0
	\sa CDataArray, CIndexSet, ICENodeDef, Accessor, \ref CDataArray2DBool "CDataArray2DBool typedef"
 */
//*****************************************************************************

template <>
class CDataArray2D<bool> : public CBaseDataArray2D
{
	public:
	//*****************************************************************************
	/*! \class Accessor xsi_dataarray2D.h
		\brief A class for accessing the sub-array data of CDataArray2D< bool > objects.

		\since 7.0
		\sa CIndexSet, CDataArray, CDataArray2D
	 */
	//*****************************************************************************
	class Accessor
	{
		public:
		friend class CDataArray2D<bool>;

		/*! Constructor.
		*/
		Accessor( ) : m_nStartbit(0), m_bIsConstant(false)
		{
		}

		/*! Constructs an %Accessor object from another %Accessor object.
		\param in_accessor constant %Accessor object.*/
		Accessor( const Accessor& in_accessor )
		{
			*this = in_accessor;
		}

		/*! Assignment operator.
		\param in_accessor constant class object.
		\return A reference to this %Accessor.
		*/
		Accessor& operator=( const Accessor& in_accessor )
		{
			m_bitset = in_accessor.m_bitset;
			m_nStartbit = in_accessor.m_nStartbit;
			m_bIsConstant = in_accessor.m_bIsConstant;
			return *this;
		}

		/*! %Accessor to elements at a given index. This operator is called when reading the data so the return value is read-only.
		\param in_nIndex Index in the array. The index must be smaller than the number of elements in the array, otherwise the
			results are unpredicted.
		\return A read-only reference to the indexed item.
		*/
		const bool operator[] ( ULONG in_nIndex ) const
		{
			ULONG nIndex = m_nStartbit + (m_bitset.GetCount() == UINT_MAX ? 0 : in_nIndex);
			return m_bitset.GetBit( nIndex );
		}

		/*! Sets the array at a given index with a value.
		\param in_nIndex Index in the array. The index must be smaller than the number of elements in the array, otherwise the
			results are unpredicted.
		\param in_bVal	Value to set.
		\return CStatus::OK Success
		*/
		CStatus Set( ULONG in_nIndex, bool in_bVal )
		{
			return m_bitset.SetBit( m_nStartbit + in_nIndex, in_bVal );
		}

		/*! Returns the number of elements in the array.
		\return Number of elements.
		*/
		ULONG GetCount() const
		{
			return m_bitset.GetCount( );
		}

		private:

		void SetAsConstant( bool in_bConst )
		{
			m_bIsConstant = in_bConst;
		}

		ULONG m_nStartbit;
		CBitsetHelper m_bitset;
		bool m_bIsConstant;
	};

	/*! Constructor for data types bound to input ports.
	\param in_ctxt ICENode evaluation context.
	\param in_nInputPortID Input port identifier.
	\param in_nInstanceIndex The group instance of the port.
	*/
	SICPPSDK_INLINE CDataArray2D( ICENodeContext& in_ctxt, ULONG in_nInputPortID, ULONG in_nInstanceIndex=0 ) ;

	/*! Constructor for data types bound to output ports.
	\param in_ctxt ICENode evaluation context.
	*/
	SICPPSDK_INLINE CDataArray2D( ICENodeContext& in_ctxt ) ;

	/*! Default constructor.
	*/
	SICPPSDK_INLINE CDataArray2D( ) ;

	/*! Destructor.
	*/
	SICPPSDK_INLINE ~CDataArray2D( );

	/*! Copy the data from a given input port to this object buffer without allocating memory. This is typically used for passing
	data by reference from input to output ports, similar to what the built-in 'pass through' node is doing.

	\param in_nInputPortID Input port identifier.
	\param in_nInstanceIndex The group instance of the port.
	\return CStatus::OK Success
	\return CStatus::InvalidArgument Fails if in_nInputPortID is not an input port identifier or in_nInstanceIndex is invalid.
	\return CStatus::AccessDenied This array is not an output type or wasn't created properly.

	\eg
	\code
		// Copy data from the ID_IN_2DPoints port to the current output port
		XSI::CDataArray2DVector3f outData( in_ctxt );
		outData.CopyFrom( ID_IN_2DPoints );
	\endcode
	*/
	SICPPSDK_INLINE CStatus CopyFrom( ULONG in_nInputPortID, ULONG in_nInstanceIndex=0 ) ;

	/*! Returns an accessor at a given index. This operator is called when reading the data so the return value is read-only.
	\param in_nArrayIndex Index in the array. The index must be smaller than the number of elements in the array, otherwise the
		results are unpredicted.
	\return %Accessor object.
	*/
	SICPPSDK_INLINE Accessor operator[]( ULONG in_nArrayIndex ) const;

	/*! Changes the size of the sub-array at a given position and returns an accessor pointing to the resized sub-array.
	\param in_nArrayIndex Index in the array. The index must be smaller than the number of elements in the array, otherwise the
		results are unpredicted.
	\param in_nSize The new size.
	\return %Accessor object.
	*/
	SICPPSDK_INLINE Accessor Resize( ULONG in_nArrayIndex, ULONG in_nSize );

	/*! Returns the number of elements in the array.
	\return Number of elements.
	*/
	SICPPSDK_INLINE ULONG GetCount() const;

	/*! Returns true if the array is constant or false otherwise. A constant array has only one value.
	\return True if constant, false otherwise.
	*/
	SICPPSDK_INLINE bool IsConstant() const;

private:
	SICPPSDK_INLINE Accessor Get( ULONG in_nArrayIndex ) const;
	static SICPPSDK_INLINE XSI::siICENodeDataType GetDefaultType( );
};

SICPPSDK_INLINE CDataArray2D<bool>::CDataArray2D( )
{
}

SICPPSDK_INLINE CDataArray2D<bool>::CDataArray2D( ICENodeContext& in_ctxt, ULONG in_nInputPortID, ULONG in_nInstanceIndex )
{
	m_ctxt = in_ctxt;

	AcquireInputDataArray( GetDefaultType(), in_nInputPortID, in_nInstanceIndex );
}

SICPPSDK_INLINE CDataArray2D<bool>::CDataArray2D( ICENodeContext& in_ctxt )
{
	m_ctxt = in_ctxt;

	AcquireOutputDataArray( GetDefaultType() );
}

SICPPSDK_INLINE CDataArray2D<bool>::~CDataArray2D( )
{
	ReleaseDataArray( );
}

SICPPSDK_INLINE CStatus CDataArray2D<bool>::CopyFrom( ULONG in_nInputPortID, ULONG in_nInstanceIndex )
{
	return CopyFromInputDataArray( GetDefaultType(), in_nInputPortID, in_nInstanceIndex );
}

SICPPSDK_INLINE CDataArray2D<bool>::Accessor CDataArray2D<bool>::Get( ULONG in_nArrayIndex ) const
{
	Accessor a;
	GetSubArray( in_nArrayIndex, (void*&)a.m_bitset.GetArrayRef(), (ULONG&)a.m_bitset.GetCountRef(), a.m_nStartbit );
	a.SetAsConstant( GetSubArrayConstant() );
	return a;
}

SICPPSDK_INLINE CDataArray2D<bool>::Accessor CDataArray2D<bool>::operator[]( ULONG in_nArrayIndex ) const
{
	return Get( in_nArrayIndex );
}

SICPPSDK_INLINE CDataArray2D<bool>::Accessor CDataArray2D<bool>::Resize( ULONG in_nArrayIndex, ULONG in_nSize )
{
	Accessor a;
	ResizeSubArray( in_nArrayIndex, in_nSize, (void*&)a.m_bitset.GetArrayRef(), (ULONG&)a.m_bitset.GetCountRef(), a.m_nStartbit );
	a.SetAsConstant( GetSubArrayConstant() );
	return a;
}

SICPPSDK_INLINE ULONG CDataArray2D<bool>::GetCount() const
{
	return m_nCount;
}

SICPPSDK_INLINE bool CDataArray2D<bool>::IsConstant() const
{
	return m_bIsConstant;
}

//*****************************************************************************
/*! \class CDataArray2DCustomType xsi_dataarray2D.h
	\brief CDataArray2DCustomType is used for storing binary data in a 2D element array of type CDataArray2DCustomType::TData.

	\since 8.0 (2010)
	\sa CDataArrayCustomType, CIndexSet
 */
//*****************************************************************************
class CDataArray2DCustomType : public CBaseDataArray2D
{
	public:

	typedef unsigned char TData;

	//*****************************************************************************
	/*! \class Accessor xsi_dataarray2D.h
		\brief %Accessor gives access to the user data values stored in a CDataArray2DCustomType object.
		\since 8.0 (2010)
	 */
	//*****************************************************************************

	class Accessor
	{
		public:
		friend class CDataArray2DCustomType;

		/*! Constructor.
		*/
		Accessor( ) : m_nAccessIndex(0), m_nCount(0), m_bIsConstant(false), m_pParent(NULL)
		{
		}

		/*! Constructs an %Accessor object from another %Accessor object.
		\param in_accessor constant %Accessor object.*/
		Accessor( const Accessor& in_accessor )
		{
			*this = in_accessor;
		}

		/*! Assignment operator.
		\param in_accessor constant class object.
		\return A reference to this %Accessor.
		*/
		Accessor& operator=( const Accessor& in_accessor )
		{
			m_nCount = in_accessor.m_nCount;
			m_nAccessIndex = in_accessor.m_nAccessIndex;
			m_bIsConstant = in_accessor.m_bIsConstant;
			m_pParent = in_accessor.m_pParent;
			return *this;
		}

		/*! Allocates \c in_nSize bytes of memory for the user data at a specified position and copies the content of
		\c in_pData to the new user array. Use Accessor::Resize if you only need to allocate the memory.
		\param in_nIndex Array index to store the user data.
		\param in_pData Pointer to user data.
		\param in_nSize Size in bytes of the data to store.
		\return CStatus::OK Success
		\sa CDataArray2DCustomType::Accessor::GetData, CDataArray2DCustomType::Accessor::Resize
		*/
		SICPPSDK_INLINE CStatus SetData( ULONG in_nIndex, const TData* in_pData, ULONG in_nSize );

		/*! Returns a pointer to the user data stored at a specified position. The data is read-only and cannot be modified.
		\note The memory allocated for the data returned by CDataArray2DCustomType::GetData is only available within the
			scope of this CDataArray2DCustomType instance. Make sure to make a copy of the data if you need to access it
			outside the scope of CDataArray2DCustomType.

		\param in_nIndex Array index of the user data to retrieve.
		\retval out_ppData Read-only pointer to the data.
		\retval out_nSize Size in bytes of the user data.
		\return CStatus::OK Success
		\sa CDataArray2DCustomType::Accessor::GetData, CDataArray2DCustomType::Accessor::Resize
		*/
		SICPPSDK_INLINE CStatus GetData( ULONG in_nIndex, const TData** out_ppData, ULONG& out_nSize  ) const;

		/*! Returns a pointer to the user data stored in at a specified position. The data can be modified directly.
		\note The memory allocated for the data returned by CDataArray2DCustomType::GetData is only available within the
			scope of this CDataArray2DCustomType instance. Make sure to make a copy of the data if you need to access it
			outside the scope of CDataArray2DCustomType.

		\param in_nIndex Array index of the user data to retrieve.
		\retval out_ppData Pointer to the data.
		\retval out_nSize Size in bytes of the user data.
		\return CStatus::OK Success
		\sa CDataArray2DCustomType::Accessor::SetData, CDataArray2DCustomType::Accessor::Resize
		*/
		SICPPSDK_INLINE CStatus GetData( ULONG in_nIndex, TData** out_ppData, ULONG& out_nSize  ) const;

		/*! Changes the size of the sub-array buffer at a specified position and returns a pointer to the allocated data.
		\param in_nIndex Array index of the user buffer to resize.
		\param in_nSize The size in bytes of the new array.
		\return Pointer to the newly allocated memory.
		\sa CDataArray2DCustomType::Accessor::SetData, CDataArray2DCustomType::Accessor::Resize
		*/
		SICPPSDK_INLINE TData* Resize( ULONG in_nIndex, ULONG in_nSize );

		/*! Returns the number of elements in the sub-array.
		\return Number of elements.
		*/
		ULONG GetCount() const
		{
			return m_nCount;
		}

		private:
		void SetAsConstant( bool in_bConst )
		{
			m_bIsConstant = in_bConst;
		}

		void SetIndex( ULONG in_nIndex )
		{
			m_nAccessIndex = in_nIndex;
		}

		void SetParent( CDataArray2DCustomType* in_pParent )
		{
			m_pParent = in_pParent;
		}

		ULONG& GetCountRef()
		{
			return m_nCount;
		}

		ULONG m_nAccessIndex;
		ULONG m_nCount;
		bool m_bIsConstant;
		CDataArray2DCustomType* m_pParent;
	};

	/*! Constructor for data types bound to input ports.
	\param in_ctxt ICENode evaluation context.
	\param in_nInputPortID Input port identifier.
	\param in_nInstanceIndex The group instance of the port.
	*/
	SICPPSDK_INLINE CDataArray2DCustomType( ICENodeContext& in_ctxt, ULONG in_nInputPortID, ULONG in_nInstanceIndex=0 ) ;

	/*! Constructor for data types bound to output ports.
	\param in_ctxt ICENode evaluation context.
	*/
	SICPPSDK_INLINE CDataArray2DCustomType( ICENodeContext& in_ctxt ) ;

	/*! Default constructor.
	*/
	SICPPSDK_INLINE CDataArray2DCustomType( ) ;

	/*! Destructor.
	*/
	SICPPSDK_INLINE ~CDataArray2DCustomType( );

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
		XSI::CDataArray2DCustomType outData( in_ctxt );
		outData.CopyFrom( ID_IN_CUSTOM_DATA );
	\endcode
	*/
	SICPPSDK_INLINE CStatus CopyFrom( ULONG in_nInputPortID, ULONG in_nInstanceIndex=0 ) ;

	/*! Returns an accessor at a given index. This operator is called when reading the data so the return value is read-only.
	\param in_nArrayIndex Index in the array. The index must be smaller than the number of elements in the array, otherwise the
		results are unpredicted.
	\return %Accessor object.
	*/
	SICPPSDK_INLINE Accessor operator[]( ULONG in_nArrayIndex ) const;

	/*! Changes the size of the sub-array at a given position and returns an accessor pointing to the resized sub-array.
	\param in_nArrayIndex Index in the array. The index must be smaller than the number of elements in the array, otherwise the
		results are unpredicted.
	\param in_nSize The size in bytes of the new array.
	\return %Accessor object.
	*/
	SICPPSDK_INLINE Accessor Resize( ULONG in_nArrayIndex, ULONG in_nSize );

	/*! Returns the number of elements in the array.
	\return Number of elements.
	*/
	SICPPSDK_INLINE ULONG GetCount() const;

	/*! Returns true if the array is constant or false otherwise. A constant array has only one value.
	\return True if constant, false otherwise.
	*/
	SICPPSDK_INLINE bool IsConstant() const;

private:
	SICPPSDK_INLINE Accessor Get( ULONG in_nArrayIndex ) const;
	SICPPSDK_INLINE void Clear();
	static SICPPSDK_INLINE XSI::siICENodeDataType GetDefaultType( );
};

SICPPSDK_INLINE CDataArray2DCustomType::CDataArray2DCustomType( ICENodeContext& in_ctxt, ULONG in_nInputPortID, ULONG in_nInstanceIndex )
{
	m_ctxt = in_ctxt;

	AcquireInputDataArray( GetDefaultType(), in_nInputPortID, in_nInstanceIndex );
}

SICPPSDK_INLINE CDataArray2DCustomType::CDataArray2DCustomType( ICENodeContext& in_ctxt )
{
	m_ctxt = in_ctxt;

	AcquireOutputDataArray( GetDefaultType() );
}

SICPPSDK_INLINE CDataArray2DCustomType::~CDataArray2DCustomType( )
{
	ReleaseDataArray( );
}

SICPPSDK_INLINE CDataArray2DCustomType::CDataArray2DCustomType( )
{
}

SICPPSDK_INLINE CStatus CDataArray2DCustomType::CopyFrom( ULONG in_nInputPortID, ULONG in_nInstanceIndex )
{
	return CopyFromInputDataArray( GetDefaultType(), in_nInputPortID, in_nInstanceIndex );
}

SICPPSDK_INLINE CDataArray2DCustomType::Accessor CDataArray2DCustomType::Get( ULONG in_nArrayIndex ) const
{
	ULONG nNotused;
	void* pNotused;

	Accessor a;
	GetSubArray( in_nArrayIndex, pNotused, (ULONG&)a.GetCountRef(), nNotused );
	a.SetParent( (CDataArray2DCustomType*)this );
	a.SetAsConstant( GetSubArrayConstant() );
	a.SetIndex( in_nArrayIndex );
	return a;
}

SICPPSDK_INLINE CDataArray2DCustomType::Accessor CDataArray2DCustomType::operator[]( ULONG in_nArrayIndex ) const
{
	return Get( in_nArrayIndex );
}

SICPPSDK_INLINE CDataArray2DCustomType::Accessor CDataArray2DCustomType::Resize( ULONG in_nArrayIndex, ULONG in_nSize )
{
	ULONG nNotused;
	void* pNotused;

	Accessor a;
	ResizeSubArray( in_nArrayIndex, in_nSize, pNotused, (ULONG&)a.GetCountRef(), nNotused );
	a.SetParent( (CDataArray2DCustomType*)this );
	a.SetAsConstant( GetSubArrayConstant() );
	a.SetIndex( in_nArrayIndex );
	return a;
}

SICPPSDK_INLINE void CDataArray2DCustomType::Clear()
{
	ReleaseDataArray( );
	m_nHandle = UINT_MAX;
	m_nCount = 0;
	m_bIsConstant = false;
}

SICPPSDK_INLINE ULONG CDataArray2DCustomType::GetCount() const
{
	return m_nCount;
}

SICPPSDK_INLINE bool CDataArray2DCustomType::IsConstant() const
{
	return m_bIsConstant;
}

SICPPSDK_INLINE CStatus CDataArray2DCustomType::Accessor::SetData( ULONG in_nIndex, const TData* in_pData, ULONG in_nSize )
{
	return m_pParent->SetCustomTypeData2D( m_nAccessIndex, in_nIndex, in_pData, in_nSize );
}

SICPPSDK_INLINE CStatus CDataArray2DCustomType::Accessor::GetData( ULONG in_nIndex, const TData** out_ppData, ULONG& out_nSize  ) const
{
	return m_pParent->GetCustomTypeData2D( m_nAccessIndex, in_nIndex, out_ppData, out_nSize );
}

SICPPSDK_INLINE CStatus CDataArray2DCustomType::Accessor::GetData( ULONG in_nIndex, TData** out_ppData, ULONG& out_nSize  ) const
{
	return m_pParent->GetCustomTypeData2D( m_nAccessIndex, in_nIndex, out_ppData, out_nSize );
}

SICPPSDK_INLINE CDataArray2DCustomType::TData* CDataArray2DCustomType::Accessor::Resize( ULONG in_nIndex, ULONG in_nSize )
{
	return m_pParent->ResizeCustomTypeData2D( m_nAccessIndex, in_nIndex, in_nSize );
}

//*****************************************************************************
/*! \class CDataArray2DString xsi_dataarray2D.h
	\brief CDataArray2DString is used for storing strings in a 2D element array.

	\since Ariane
	\sa CDataArrayString, CIndexSet
 */
//*****************************************************************************
class CDataArray2DString : public CBaseDataArray2D
{
	public:

	typedef wchar_t TData;

	//*****************************************************************************
	/*! \class Accessor xsi_dataarray2D.h
		\brief %Accessor gives access to the string data  stored in a CDataArray2DString object.
		\since Ariane
	 */
	//*****************************************************************************

	class Accessor
	{
		public:
		friend class CDataArray2DString;

		/*! Constructor.
		*/
		Accessor( ) : m_nAccessIndex(0), m_nCount(0), m_bIsConstant(false), m_pParent(NULL)
		{
		}

		/*! Constructs an %Accessor object from another %Accessor object.
		\param in_accessor constant %Accessor object.*/
		Accessor( const Accessor& in_accessor )
		{
			*this = in_accessor;
		}

		/*! Assignment operator.
		\param in_accessor constant class object.
		\return A reference to this %Accessor.
		*/
		Accessor& operator=( const Accessor& in_accessor )
		{
			m_nCount = in_accessor.m_nCount;
			m_nAccessIndex = in_accessor.m_nAccessIndex;
			m_bIsConstant = in_accessor.m_bIsConstant;
			m_pParent = in_accessor.m_pParent;
			return *this;
		}

		/*! Sets the sub-array at \c in_nIndex with the content of \c in_str. 
		\param in_nIndex Array index where to store the string.
		\param in_str CString object.
		\return Success/failure
		*/
		SICPPSDK_INLINE CStatus SetData( ULONG in_nIndex, const CString& in_str );

		/*! Returns a CString object set with a copy of the string stored at \c in_nIndex. 
		\param in_nIndex Array index of the string to retrieve. The returned CString is empty if no string is stored at this index.
		\retval out_str CString object containing a copy of the string.
		\return Success/failure
		*/
		SICPPSDK_INLINE CStatus GetData( ULONG in_nIndex, CString& out_str ) const;

		/*! Returns a CString object containing a copy of the string stored at\c in_nIndex.
		\param in_nIndex Index in the sub-array. The index must be smaller than the number of elements in the sub-array, otherwise the
		object returned is empty.
		\return CString object.
		*/
		SICPPSDK_INLINE CString operator[]( ULONG in_nIndex ) const;

		/*! Sets the sub-array at \c in_nIndex with the content of \c in_pStr. 
		\param in_nIndex Sub-array index to store the string data.
		\param in_pStr Pointer to string data.
		\param in_nCount Number of characters to store.
		\return CStatus::OK Success
		\sa CDataArrayString::Accessor::GetData, CDataArrayString::Accessor::Resize
		*/
		SICPPSDK_INLINE CStatus SetData( ULONG in_nIndex, const TData* in_pStr, ULONG in_nSize );

		/*! Returns a pointer to the string data stored at \c in_nIndex. The data is read-only and cannot be modified.
			\note The memory allocated for the data returned by CDataArray2DString::GetData is only available within the
			scope of this CDataArray2DString instance. Make sure to make a copy of the data if you need to access it
			outside the scope of CDataArray2DString.
			\note The string returned in \c out_ppStr is not null-terminated, the caller must make sure to take the number 
				of characters in account when manipulating the string.

		\param in_nIndex Array index of the string data to retrieve.
		\retval out_ppStr Read-only pointer to the string data.
		\retval out_nCount Number of characters in the string.
		\return CStatus::OK Success
		\sa CDataArray2DString::Accessor::GetData, CDataArray2DString::Accessor::Resize
		*/
		SICPPSDK_INLINE CStatus GetData( ULONG in_nIndex, const TData** out_ppStr, ULONG& out_nCount ) const;

		/*! Returns a pointer to the string data stored at \c in_nIndex. The data can be modified directly.
		\note The memory allocated for the data returned by CDataArray2DString::GetData is only available within the
			scope of this CDataArray2DString instance. Make sure to make a copy of the data if you need to access it
			outside the scope of CDataArray2DString.
		\note The string returned in \c out_ppStr is not null-terminated, the caller must make sure to take the number 
			of characters in account when manipulating the string.

		\param in_nIndex Array index of the string data to retrieve.
		\retval out_ppStr Pointer to the string data.
		\retval out_nCount Number of characters in the string.
		\return CStatus::OK Success
		\sa CDataArray2DString::Accessor::SetData, CDataArray2DString::Accessor::Resize
		*/
		SICPPSDK_INLINE CStatus GetData( ULONG in_nIndex, TData** out_ppStr, ULONG& out_nCount ) const;

		/*! Changes the size of the sub-array buffer at \c in_nIndex and returns a pointer to the allocated data.
		\param in_nIndex Array index of the string buffer to resize.
		\param in_nCount Number of characters to store.
		\return Pointer to the newly allocated memory.
		\sa CDataArray2DString::Accessor::SetData, CDataArray2DString::Accessor::Resize
		*/
		SICPPSDK_INLINE TData* Resize( ULONG in_nIndex, ULONG in_nCount );

		/*! Returns the number of characters in the sub-array.
		\return Number of characters.
		*/
		ULONG GetCount() const
		{
			return m_nCount;
		}

		private:
		void SetAsConstant( bool in_bConst )
		{
			m_bIsConstant = in_bConst;
		}

		void SetIndex( ULONG in_nIndex )
		{
			m_nAccessIndex = in_nIndex;
		}

		void SetParent( CDataArray2DString* in_pParent )
		{
			m_pParent = in_pParent;
		}

		ULONG& GetCountRef()
		{
			return m_nCount;
		}

		ULONG m_nAccessIndex;
		ULONG m_nCount;
		bool m_bIsConstant;
		CDataArray2DString* m_pParent;
	};

	/*! Constructor for string types bound to input ports.
	\param in_ctxt ICENode evaluation context.
	\param in_nInputPortID Input port identifier.
	\param in_nInstanceIndex The group instance of the port.
	*/
	SICPPSDK_INLINE CDataArray2DString( ICENodeContext& in_ctxt, ULONG in_nInputPortID, ULONG in_nInstanceIndex=0 ) ;

	/*! Constructor for string types bound to output ports.
	\param in_ctxt ICENode evaluation context.
	*/
	SICPPSDK_INLINE CDataArray2DString( ICENodeContext& in_ctxt ) ;

	/*! Default constructor.
	*/
	SICPPSDK_INLINE CDataArray2DString( ) ;

	/*! Destructor.
	*/
	SICPPSDK_INLINE ~CDataArray2DString( );

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
		XSI::CDataArray2DString outData( in_ctxt );
		outData.CopyFrom( ID_IN_CUSTOM_DATA );
	\endcode
	*/
	SICPPSDK_INLINE CStatus CopyFrom( ULONG in_nInputPortID, ULONG in_nInstanceIndex=0 ) ;

	/*! Returns a string accessor at \c in_nArrayIndex. This operator is called when reading the data so the return value is read-only.
	\param in_nArrayIndex Index in the array. The index must be smaller than the number of elements in the array, otherwise the
		results are unpredicted.
	\return %Accessor object.
	*/
	SICPPSDK_INLINE Accessor operator[]( ULONG in_nArrayIndex ) const;

	/*! Changes the size of the sub-array at \c in_nArrayIndex and returns an accessor pointing to the resized sub-array.
	\param in_nArrayIndex Index in the array. The index must be smaller than the number of elements in the array, otherwise the
		results are unpredicted.
	\param in_nCount The number fo characters of the new array.
	\return %Accessor object.
	*/
	SICPPSDK_INLINE Accessor Resize( ULONG in_nArrayIndex, ULONG in_nCount );

	/*! Returns the number of characters in the array.
	\return Number of characters.
	*/
	SICPPSDK_INLINE ULONG GetCount() const;

	/*! Returns true if the array is constant or false otherwise. A constant array has only one value.
	\return True if constant, false otherwise.
	*/
	SICPPSDK_INLINE bool IsConstant() const;

private:
	SICPPSDK_INLINE Accessor Get( ULONG in_nArrayIndex ) const;
	SICPPSDK_INLINE void Clear();
	static SICPPSDK_INLINE XSI::siICENodeDataType GetDefaultType( );
};

SICPPSDK_INLINE CDataArray2DString::CDataArray2DString( ICENodeContext& in_ctxt, ULONG in_nInputPortID, ULONG in_nInstanceIndex )
{
	m_ctxt = in_ctxt;

	AcquireInputDataArray( GetDefaultType(), in_nInputPortID, in_nInstanceIndex );
}

SICPPSDK_INLINE CDataArray2DString::CDataArray2DString( ICENodeContext& in_ctxt )
{
	m_ctxt = in_ctxt;

	AcquireOutputDataArray( GetDefaultType() );
}

SICPPSDK_INLINE CDataArray2DString::~CDataArray2DString( )
{
	ReleaseDataArray( );
}

SICPPSDK_INLINE CDataArray2DString::CDataArray2DString( )
{
}

SICPPSDK_INLINE CStatus CDataArray2DString::CopyFrom( ULONG in_nInputPortID, ULONG in_nInstanceIndex )
{
	return CopyFromInputDataArray( GetDefaultType(), in_nInputPortID, in_nInstanceIndex );
}

SICPPSDK_INLINE CDataArray2DString::Accessor CDataArray2DString::Get( ULONG in_nArrayIndex ) const
{
	ULONG nNotused;
	void* pNotused;

	Accessor a;
	GetSubArray( in_nArrayIndex, pNotused, (ULONG&)a.GetCountRef(), nNotused );
	a.SetParent( (CDataArray2DString*)this );
	a.SetAsConstant( GetSubArrayConstant() );
	a.SetIndex( in_nArrayIndex );
	return a;
}

SICPPSDK_INLINE CDataArray2DString::Accessor CDataArray2DString::operator[]( ULONG in_nArrayIndex ) const
{
	return Get( in_nArrayIndex );
}

SICPPSDK_INLINE CDataArray2DString::Accessor CDataArray2DString::Resize( ULONG in_nArrayIndex, ULONG in_nSize )
{
	ULONG nNotused;
	void* pNotused;

	Accessor a;
	ResizeSubArray( in_nArrayIndex, in_nSize, pNotused, (ULONG&)a.GetCountRef(), nNotused );
	a.SetParent( (CDataArray2DString*)this );
	a.SetAsConstant( GetSubArrayConstant() );
	a.SetIndex( in_nArrayIndex );
	return a;
}

SICPPSDK_INLINE void CDataArray2DString::Clear()
{
	ReleaseDataArray( );
	m_nHandle = UINT_MAX;
	m_nCount = 0;
	m_bIsConstant = false;
}

SICPPSDK_INLINE ULONG CDataArray2DString::GetCount() const
{
	return m_nCount;
}

SICPPSDK_INLINE bool CDataArray2DString::IsConstant() const
{
	return m_bIsConstant;
}

SICPPSDK_INLINE CStatus CDataArray2DString::Accessor::SetData( ULONG in_nIndex, const CString& in_str )
{
	return m_pParent->SetStringData2D( m_nAccessIndex, in_nIndex, in_str.GetWideString(), in_str.Length() );
}

SICPPSDK_INLINE CStatus CDataArray2DString::Accessor::GetData( ULONG in_nIndex, CString& out_str ) const
{
	const wchar_t* pzStr;
	ULONG nSize;
	CStatus st = m_pParent->GetStringData2D( m_nAccessIndex, in_nIndex, &pzStr, nSize );
	out_str = CString(pzStr,nSize);
	return st;
}

SICPPSDK_INLINE CString CDataArray2DString::Accessor::operator[]( ULONG i ) const
{
	CString str;
	GetData( i, str );
	return str;
}

SICPPSDK_INLINE CStatus CDataArray2DString::Accessor::SetData( ULONG in_nIndex, const TData* in_pData, ULONG in_nSize )
{
	return m_pParent->SetStringData2D( m_nAccessIndex, in_nIndex, in_pData, in_nSize );
}

SICPPSDK_INLINE CStatus CDataArray2DString::Accessor::GetData( ULONG in_nIndex, const TData** out_ppData, ULONG& out_nSize  ) const
{
	return m_pParent->GetStringData2D( m_nAccessIndex, in_nIndex, out_ppData, out_nSize );
}

SICPPSDK_INLINE CStatus CDataArray2DString::Accessor::GetData( ULONG in_nIndex, TData** out_ppData, ULONG& out_nSize  ) const
{
	return m_pParent->GetStringData2D( m_nAccessIndex, in_nIndex, out_ppData, out_nSize );
}

SICPPSDK_INLINE CDataArray2DString::TData* CDataArray2DString::Accessor::Resize( ULONG in_nIndex, ULONG in_nSize )
{
	return m_pParent->ResizeStringData2D( m_nAccessIndex, in_nIndex, in_nSize );
}

// Explicit template instances
/*! \page CDataArray2DTypedefs Type Definitions for CDataArray2D
	The CDataArray2D class is a template class that encapsulates the following 2D data arrays:

	\li \ref CDataArray2DFloat "CDataArray2DFloat"
	\li \ref CDataArray2DLong "CDataArray2DLong"
	\li \ref CDataArray2DBool "CDataArray2DBool"
	\li \ref CDataArray2DVector2f "CDataArray2DVector2f"
	\li \ref CDataArray2DVector3f "CDataArray2DVector3f"
	\li \ref CDataArray2DVector4f "CDataArray2DVector4f"
	\li \ref CDataArray2DQuaternionf "CDataArray2DQuaternionf"
	\li \ref CDataArray2DRotationf "CDataArray2DRotationf"
	\li \ref CDataArray2DMatrix3f "CDataArray2DMatrix3f"
	\li \ref CDataArray2DMatrix4f "CDataArray2DMatrix4f"
	\li \ref CDataArray2DColor4f "CDataArray2DColor4f"
	\li \ref CDataArray2DShape "CDataArray2DShape"

	\section CDataArray2DFloat CDataArray2DFloat Type
	\code typedef CDataArray2D< float > CDataArray2DFloat \endcode
	A CDataArray2D class of type \c float.
	\since 7.0

	\section CDataArray2DLong CDataArray2DLong Type
	\code typedef CDataArray2D< LONG > CDataArray2DLong \endcode
	A CDataArray2D class of type \c LONG.
	\since 7.0

	\section CDataArray2DBool CDataArray2DBool Type
	\code typedef CDataArray2D< bool > CDataArray2DBool \endcode
	The CDataArray2D< bool > class.
	\since 7.0

	\section CDataArray2DVector2f CDataArray2DVector2f Type
	\code typedef CDataArray2D< CVector2f > CDataArray2DVector2f \endcode
	A CDataArray2D class of type \link MATH::CVector2f CVector2f\endlink.
	\since 7.0

	\section CDataArray2DVector3f CDataArray2DVector3f Type
	\code typedef CDataArray2D< CVector3f > CDataArray2DVector3f \endcode
	A CDataArray2D class of type \link MATH::CVector3f CVector3f\endlink.
	\since 7.0

	\section CDataArray2DVector4f CDataArray2DVector4f Type
	\code typedef CDataArray2D< CVector4f > CDataArray2DVector4f \endcode
	A CDataArray2D class of type \link MATH::CVector4f CVector4f\endlink.
	\since 7.0

	\section CDataArray2DQuaternionf CDataArray2DQuaternionf Type
	\code typedef CDataArray2D< CQuaternionf > CDataArray2DQuaternionf \endcode
	A CDataArray2D class of type \link MATH::CQuaternionf CQuaternionf\endlink.
	\since 7.0

	\section CDataArray2DRotationf CDataArray2DRotationf Type
	\code typedef CDataArray2D< CRotationf > CDataArray2DRotationf \endcode
	A CDataArray2D class of type \link MATH::CRotationf CRotationf\endlink.
	\since 7.0

	\section CDataArray2DMatrix3f CDataArray2DMatrix3f Type
	\code typedef CDataArray2D< CMatrix3f > CDataArray2DMatrix3f \endcode
	A CDataArray2D class of type \link MATH::CMatrix3f CMatrix3f\endlink.
	\since 7.0

	\section CDataArray2DMatrix4f CDataArray2DMatrix4f Type
	\code typedef CDataArray2D< CMatrix4f > CDataArray2DMatrix4f \endcode
	A CDataArray2D class of type \link MATH::CMatrix4f CMatrix4f\endlink.
	\since 7.0

	\section CDataArray2DColor4f CDataArray2DColor4f Type
	\code typedef CDataArray2D< CColor4f > CDataArray2DColor4f \endcode
	A CDataArray2D class of type \link MATH::CColor4f CColor4f\endlink.
	\since 7.0

	\section CDataArray2DShape CDataArray2DShape Type
	\code typedef CDataArray2D< CShape> CDataArray2DShape \endcode
	A CDataArray2D class of type \link MATH::CShape CShape\endlink.
	\since 7.0

*/
typedef CDataArray2D< float > CDataArray2DFloat;
typedef CDataArray2D< LONG > CDataArray2DLong;
typedef CDataArray2D< bool > CDataArray2DBool;
typedef CDataArray2D< XSI::MATH::CVector2f > CDataArray2DVector2f;
typedef CDataArray2D< XSI::MATH::CVector3f > CDataArray2DVector3f;
typedef CDataArray2D< XSI::MATH::CVector4f > CDataArray2DVector4f;
typedef CDataArray2D< XSI::MATH::CQuaternionf > CDataArray2DQuaternionf;
typedef CDataArray2D< XSI::MATH::CRotationf > CDataArray2DRotationf;
typedef CDataArray2D< XSI::MATH::CMatrix3f > CDataArray2DMatrix3f;
typedef CDataArray2D< XSI::MATH::CMatrix4f > CDataArray2DMatrix4f;
typedef CDataArray2D< XSI::MATH::CColor4f > CDataArray2DColor4f;
typedef XSI::CDataArray2D< XSI::MATH::CShape> CDataArray2DShape;

template<> SICPPSDK_INLINE siICENodeDataType CDataArray2DFloat::GetDefaultType( ){return siICENodeDataFloat;}
SICPPSDK_INLINE siICENodeDataType CDataArray2DBool::GetDefaultType( ){return siICENodeDataBool;}
template<> SICPPSDK_INLINE siICENodeDataType CDataArray2DLong::GetDefaultType( ){return siICENodeDataLong;}
template<> SICPPSDK_INLINE siICENodeDataType CDataArray2DVector2f::GetDefaultType( ){return siICENodeDataVector2;}
template<> SICPPSDK_INLINE siICENodeDataType CDataArray2DVector3f::GetDefaultType( ){return siICENodeDataVector3;}
template<> SICPPSDK_INLINE siICENodeDataType CDataArray2DVector4f::GetDefaultType( ){return siICENodeDataVector4;}
template<> SICPPSDK_INLINE siICENodeDataType CDataArray2DQuaternionf::GetDefaultType( ){return siICENodeDataQuaternion;}
template<> SICPPSDK_INLINE siICENodeDataType CDataArray2DMatrix3f::GetDefaultType( ){return siICENodeDataMatrix33;}
template<> SICPPSDK_INLINE siICENodeDataType CDataArray2DMatrix4f::GetDefaultType( ){return siICENodeDataMatrix44;}
template<> SICPPSDK_INLINE siICENodeDataType CDataArray2DColor4f::GetDefaultType( ){return siICENodeDataColor4;}
template<> SICPPSDK_INLINE siICENodeDataType CDataArray2DRotationf::GetDefaultType( ){return siICENodeDataRotation;}
template<> SICPPSDK_INLINE XSI::siICENodeDataType CDataArray2DShape::GetDefaultType( ){return siICENodeDataShape;}
SICPPSDK_INLINE XSI::siICENodeDataType CDataArray2DCustomType::GetDefaultType( ){return siICENodeDataCustomType;}
SICPPSDK_INLINE XSI::siICENodeDataType CDataArray2DString::GetDefaultType( ){return siICENodeDataString;}
}; // XSI

#endif // __XSIDATAARRAY2D_H__
