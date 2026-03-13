//*****************************************************************************
/*!
   \file xsi_indexset.h
   \brief CIndexSet class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIINDEXSET_H__
#define __XSIINDEXSET_H__

#include <sicppsdk.h>
#include <xsi_icenodecontext.h>

namespace XSI {

static const char kRevLogTable256[] =
{
  8, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
};

const LONG kBitShift= 5;
const LONG kBitSize	= 32;

class CBitsetHelper
{
	public:
	SICPPSDK_INLINE CBitsetHelper( );

	SICPPSDK_INLINE LONG& GetCountRef( );
	SICPPSDK_INLINE LONG GetCount( ) const;
	SICPPSDK_INLINE ULONG*& GetArrayRef();

	SICPPSDK_INLINE bool GetNextBit( LONG& in_index) const;
	SICPPSDK_INLINE CStatus SetBit( LONG in_index, bool in_bVal );
	SICPPSDK_INLINE bool GetBit( LONG in_index ) const;
	SICPPSDK_INLINE void Clear( );

	SICPPSDK_INLINE CBitsetHelper& operator = ( const CBitsetHelper& in_bitset );

private:
	SICPPSDK_INLINE LONG GetNextBitInternal(LONG& in_index) const;
	SICPPSDK_INLINE LONG GetFirstBit( ULONG in_nVal) const;
	SICPPSDK_INLINE LONG GetRevLogBase2( ULONG in_nVal ) const;
	SICPPSDK_INLINE CStatus SetBit( LONG in_index );
	SICPPSDK_INLINE CStatus ClearBit( LONG in_index );

	LONG	m_nCount;
	ULONG*	m_pArray;
};

//*****************************************************************************
/*! \class CIndexSet xsi_indexset.h
	\brief CIndexSet encapsulates an index set for indexing CDataArray object types for the current evaluation.

	\eg
	\code
	XSIPLUGINCALLBACK CStatus YPosFilter_Evaluate( ICENodeContext& in_ctxt )
	{
		// The current output port being evaluated...
		ULONG out_portID = in_ctxt.GetEvaluatedOutputPortID( );

		switch( out_portID )
		{
			case OutPort200:
			{
				CDataArrayVector3f inputData( ctxt, InPort0 );
				CDataArrayVector3f outData( ctxt );

				// We need a CIndexSet to iterate over the data
				CIndexSet indexSet( in_ctxt );

				for(CIndexSet::Iterator it = indexSet.Begin(); it.HasNext(); )
				{
					outData[ it ] = inputData[ it ];

					if ( inputData[it].GetY() < 0.0 )
					{
						it.Remove( );
					}
					else
					{
						it.Next( );
					}
				}
			}
			break;
		};

		return CStatus::OK;
	}
	\endcode

	\since 7.0
	\sa CIndexSet::Iterator, CDataArray, CDataArray2D
*/
//*****************************************************************************

class CIndexSet
{
public:
	typedef CIndexSet* PtrType;

	enum StorageMode
	{
		Range,
		Bitset,
		Indices,
		Unknown
	};

	//*****************************************************************************
	/*! \class Iterator xsi_indexset.h
		\brief A class for iterating over CDataArray objects during an evaluation.
		Iterator objects must always be created with CIndexSet::Begin().

		\since 7.0
		\sa CIndexSet, CDataArray, CDataArray2D
	 */
	//*****************************************************************************
	class Iterator
	{
		public:
		friend class CIndexSet;

		/*! Removes the current index from the CIndexSet.
		\Note Removing an index will set CIndexSet with the next available index in the set. Make sure you don't call
		Iterator::Next again after Remove to avoid unexpected results while iterating.
		*/
		SICPPSDK_INLINE void Remove();

		/*! Use this method to know if there are more items in the set.
		\return True if there are more items.
		*/
		SICPPSDK_INLINE bool HasNext() const;

		/*! Returns the current index in the set.
		\return Current index.
		*/
		SICPPSDK_INLINE ULONG GetIndex() const;

		/*! Returns the absolute index based on the global index set of the evaluation.
		\return Absolute index.
		*/
		SICPPSDK_INLINE ULONG GetAbsoluteIndex() const;

		/*! Moves to the next index in the set.
		*/
		SICPPSDK_INLINE void Next();

		/*! Cast-operator which returns the current index in the set.
		\return Current index.
		*/
		SICPPSDK_INLINE operator ULONG () const;

		private:
		SICPPSDK_INLINE Iterator( PtrType in_pSet );

		bool 	m_bEnd;
		LONG 	m_nPos;
		PtrType	m_pSet;
	};

	friend class ICENodeContext;
	friend class Iterator;

	/*! Constructor.
	\param in_ctxt ICENode evaluation context.
	*/
	SICPPSDK_INLINE CIndexSet( const ICENodeContext& in_ctxt );

	/*! Constructor. Creates the index set for a specific port. \note The CIndexSet created can not be used to set the output port 
	data array and is only valid when the underlying custom ICENode is set with the ::siICENodeSingleThreading or 
	::siICENodeMultiEvaluationPhase mode. The object created is read-only, indices cannot be removed with CIndexSet::Iterator::Remove.

	\param in_ctxt ICENode evaluation context.
	\param in_nInputPortID Input port identifier.
	\param in_nInstanceIndex The group instance of the port.
	*/
	SICPPSDK_INLINE CIndexSet( const ICENodeContext& in_ctxt, ULONG in_nInputPortID, ULONG in_nInstanceIndex=0 ) ;

	/*! Destructor.
	*/
	SICPPSDK_INLINE ~CIndexSet();

	/*! Returns an Iterator object pointing to the first index element.
	\return An Iterator object.
	*/
	SICPPSDK_INLINE Iterator Begin();

	/*! Returns the filtered size of the index set.
	*/
	SICPPSDK_INLINE ULONG GetFilteredCount() const;

	protected:
	SICPPSDK_INLINE void			RemoveElement( Iterator& io_it );
	SICPPSDK_INLINE bool			GetNextBit(LONG& in_it) const;
	SICPPSDK_INLINE ULONG*&			GetDataRef();
	SICPPSDK_INLINE ULONG&			GetIndexOffsetRef();
	SICPPSDK_INLINE void*&			GetHandleRef();
	SICPPSDK_INLINE ULONG&			GetCountRef();
	SICPPSDK_INLINE StorageMode&	GetStorageModeRef();
	SICPPSDK_INLINE ICENodeContext&	GetContextRef();
	SICPPSDK_INLINE CBitsetHelper&	GetBitsetRef();

	ULONG*			m_pData;
	ULONG			m_nIndexOffset;
	void*			m_pHandle;
	ULONG			m_nCount;
	StorageMode		m_eStorageMode;
	ICENodeContext	m_ctxt;
	CBitsetHelper	m_bitset;
};

SICPPSDK_INLINE CIndexSet::CIndexSet( const ICENodeContext& in_ctxt )
{
	m_ctxt = in_ctxt;
	m_eStorageMode = Unknown;
	m_nIndexOffset = 0;
	m_pHandle = NULL;
	m_pData = NULL;
	m_nCount = 0;
	m_pData = NULL;

	m_ctxt.AcquireIndexSet( *this );	
}

SICPPSDK_INLINE CIndexSet::CIndexSet( const ICENodeContext& in_ctxt, ULONG in_nInputPortID, ULONG in_nInstanceIndex )	
{
	m_ctxt = in_ctxt;
	m_eStorageMode = Unknown;
	m_nIndexOffset = 0;
	m_pHandle = NULL;
	m_pData = NULL;
	m_nCount = 0;
	m_pData = NULL;
	
	m_ctxt.AcquireIndexSetFromPort( *this, in_nInputPortID, in_nInstanceIndex );
}

SICPPSDK_INLINE CIndexSet::~CIndexSet()
{
	m_ctxt.ReleaseIndexSet( *this );
}

SICPPSDK_INLINE CIndexSet::Iterator CIndexSet::Begin()
{
	return CIndexSet::Iterator((PtrType)this);
}

SICPPSDK_INLINE ULONG CIndexSet::GetFilteredCount() const
{
	ULONG l_ulCount = 0;
	m_ctxt.GetFilteredCountFromIndexSet( *this, l_ulCount );

	return l_ulCount;
}

SICPPSDK_INLINE void CIndexSet::RemoveElement( CIndexSet::Iterator& io_it )
{
	m_ctxt.RemoveElementFromIndexSet( *this, io_it.m_nPos, io_it.m_nPos, io_it.m_bEnd );
}

SICPPSDK_INLINE bool CIndexSet::GetNextBit(LONG& in_it) const
{
	if ( m_eStorageMode != Bitset )
	{
		assert(false);
		return false;
	}

	return m_bitset.GetNextBit( in_it );
}

SICPPSDK_INLINE ULONG*& CIndexSet::GetDataRef()
{
	return m_pData;
}

SICPPSDK_INLINE ULONG& CIndexSet::GetIndexOffsetRef()
{
	return m_nIndexOffset;
}

SICPPSDK_INLINE void*& CIndexSet::GetHandleRef()
{
	return m_pHandle;
}

SICPPSDK_INLINE ULONG& CIndexSet::GetCountRef()
{
	return m_nCount;
}

SICPPSDK_INLINE CIndexSet::StorageMode& CIndexSet::GetStorageModeRef()
{
	return m_eStorageMode;
}

SICPPSDK_INLINE ICENodeContext& CIndexSet::GetContextRef()
{
	return m_ctxt;
}

SICPPSDK_INLINE CBitsetHelper& CIndexSet::GetBitsetRef()
{
	return m_bitset;
}

SICPPSDK_INLINE CIndexSet::Iterator::Iterator( CIndexSet::PtrType in_pSet ) : 
	m_bEnd(false),
	m_nPos(-1), 
	m_pSet(in_pSet)
{
	Next();
}

// Goto next element
SICPPSDK_INLINE void CIndexSet::Iterator::Next()
{
	switch(m_pSet->m_eStorageMode)
	{
		case Range:
			m_bEnd = (ULONG)(++m_nPos) == m_pSet->m_nCount;
			break;
		case Bitset:
			m_bEnd = !m_pSet->GetNextBit(m_nPos);
			break;
		case Indices:
			while(true)
			{
				++m_nPos;
				if ((ULONG)m_nPos == m_pSet->m_nCount)
				{
					m_bEnd = true;
					break;
				}

				if(m_pSet->m_pData[m_nPos] != UINT_MAX)
				{
					break;
				}
			}
			break;
		default:
			break;
	};
}

SICPPSDK_INLINE ULONG CIndexSet::Iterator::GetIndex() const
{
	switch(m_pSet->m_eStorageMode)
	{
		case Indices:
			return m_pSet->m_pData[m_nPos];
		default:
			return m_nPos;
	}
}

SICPPSDK_INLINE ULONG CIndexSet::Iterator::GetAbsoluteIndex() const
{
	return GetIndex() + m_pSet->m_nIndexOffset;
}

SICPPSDK_INLINE CIndexSet::Iterator::operator ULONG () const
{
	return GetIndex( );
}

SICPPSDK_INLINE bool CIndexSet::Iterator::HasNext() const
{
	return m_bEnd == false && m_pSet->m_nCount > 0;
}

SICPPSDK_INLINE void CIndexSet::Iterator::Remove()
{
	if (m_bEnd )
	{
		return;
	}

	m_pSet->RemoveElement( *this );
}

// CBitsetHelper
SICPPSDK_INLINE CBitsetHelper::CBitsetHelper( ) : m_nCount(UINT_MAX), m_pArray(NULL) {}

SICPPSDK_INLINE void CBitsetHelper::Clear( )
{
	m_nCount = 0;
	m_pArray = 0;
}

SICPPSDK_INLINE CBitsetHelper& CBitsetHelper::operator = ( const CBitsetHelper& in_bitset )
{
	m_nCount = in_bitset.m_nCount;
	m_pArray = in_bitset.m_pArray;
	return *this;
}

SICPPSDK_INLINE LONG& CBitsetHelper::GetCountRef( )
{
	return m_nCount;
}

SICPPSDK_INLINE LONG CBitsetHelper::GetCount( ) const
{
	return m_nCount;
}

SICPPSDK_INLINE ULONG*& CBitsetHelper::GetArrayRef()
{
	return m_pArray;
}

SICPPSDK_INLINE bool CBitsetHelper::GetNextBit( LONG& in_it ) const
{
	return ( in_it = GetNextBitInternal( in_it ) ) != m_nCount;
}

SICPPSDK_INLINE bool CBitsetHelper::GetBit( LONG in_index ) const
{
	if ( !m_pArray )
	{
		return false;
	}

	return ( m_pArray[ in_index >> kBitShift ] & ( 1 << ( in_index % kBitSize ) ) ) != 0;
}

SICPPSDK_INLINE CStatus CBitsetHelper::SetBit( LONG in_index, bool in_bVal )
{
	if ( in_bVal )
	{
		SetBit( in_index );
	}
	else
	{
		ClearBit( in_index );
	}
	return CStatus::OK;
}

SICPPSDK_INLINE CStatus CBitsetHelper::SetBit( LONG in_index )
{
	if ( !m_pArray )
	{
		return CStatus::AccessDenied;
	}

	m_pArray[ in_index >> kBitShift ] |= ( 1 << ( in_index % kBitSize ) );
	return CStatus::OK;
}

SICPPSDK_INLINE CStatus CBitsetHelper::ClearBit( LONG in_index )
{
	if ( !m_pArray )
	{
		return CStatus::AccessDenied;
	}

	m_pArray[ in_index >> kBitShift ] &= ~( 1 << ( in_index % kBitSize ) );
	return CStatus::OK;
}

SICPPSDK_INLINE LONG CBitsetHelper::GetNextBitInternal( LONG& in_index ) const
{
	LONG nCurrentBit = in_index+1;
	if (nCurrentBit >= m_nCount)
	{
		return m_nCount;
	}

	LONG nCurrentIdx = nCurrentBit >> kBitShift;

	ULONG nVal = m_pArray[nCurrentIdx];
	nVal >>= (nCurrentBit - (nCurrentIdx << kBitShift));

	LONG nDeltaBit;
	if ((nDeltaBit = GetFirstBit(nVal)) == 32)
	{
		LONG nMaxIdx = ((m_nCount-1)>>kBitShift)+1;

		for( nCurrentIdx++; nCurrentIdx != nMaxIdx; nCurrentIdx++ )
		{
			nDeltaBit = GetFirstBit(m_pArray[nCurrentIdx]);

			if(nDeltaBit != 32)
			{
				break;
			}
		}

		if( nCurrentIdx == nMaxIdx )
		{
			return m_nCount;
		}
		else
		{
			nCurrentBit = ( nCurrentIdx << kBitShift ) + nDeltaBit;
		}
	}
	else
	{
		nCurrentBit += nDeltaBit;
	}

	if( nCurrentBit > m_nCount )
	{
		return m_nCount;
	}

	return nCurrentBit;
}

SICPPSDK_INLINE LONG CBitsetHelper::GetFirstBit( ULONG in_nVal ) const
{
	return GetRevLogBase2( in_nVal );
}

SICPPSDK_INLINE LONG CBitsetHelper::GetRevLogBase2( ULONG in_nVal ) const
{
	register unsigned int t, tt; // temporaries

	if ( tt = in_nVal & 0xFFFF, tt != 0 )
	{
	  return (t = in_nVal & 0xFF, t != 0 ) ? kRevLogTable256[t] : 8 + kRevLogTable256[tt >> 8];
	}
	else
	{
	  return (t = in_nVal & 0x00FF0000, t != 0 ) ? 16 + kRevLogTable256[t >> 16] : 24 + kRevLogTable256[in_nVal >> 24];
	}
}

};

#endif // __XSIINDEXSET_H__
