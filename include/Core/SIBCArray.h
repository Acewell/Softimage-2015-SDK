//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file SIBCArray.h
	\brief Defines the CSIBCArray and CElemType classes

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

//***************************************************************************************
// Defines
//***************************************************************************************
#ifndef __CSIBCArray_H__
#define __CSIBCArray_H__

#ifdef _DEBUG
#include <assert.h>
#define _SI_ASSERT(x) assert(x)
#else
#define _SI_ASSERT(exp)
#endif

#include "SIBCUtil.h"
#include <string.h>

// Disable "identifier was truncated to '255' characters in the debug information" warning.
#if defined(_WIN32) || defined(_WIN32_WCE) || defined( _XBOX )
#pragma warning( disable : 4786 )
#endif

//***************************************************************************************
// CSIBCArray | Simple, all-purpose chunked array used by other classes.
//***************************************************************************************

/*! \brief Simple, all-purpose chunked array used by other classes.

	This class is frequently used throughout the Crosswalk SDK and Semantic Layer.
	It is the recommended method for using arrays.
*/
template < class CElemType >
class CSIBCArray
{
    private :
        LONG        m_lNbUsedElem;      // Number of elements used in the array
		LONG		m_lNbAllocElem;		// Number of elements allocated to the array
        CElemType	*m_pElem;           // Array of elements

    public:

		/*! Constructor.
		Allocates \p in_lNbElem elements of storage in the new array.
		\param[in] in_lNbElem	Initial element storage space to allocate. (Defaults to 0).
		*/
        inline CSIBCArray( const LONG in_lNbElem = 0 );
		/*! Destructor.
		*/
        inline ~CSIBCArray() { DisposeData(); }

		/*! Returns the number of element storage spaces that contain valid elements.
		\return Number of used element storage spaces.
		\sa CSIBCArray::GetSize
		\sa CSIBCArray::UsedMem
		*/
        inline LONG GetUsed() const;

		/*! Returns the number of allocated element storage spaces.
		\return Number of allocated element storage spaces.
		\sa CSIBCArray::GetUsed
		\sa CSIBCArray::AllocatedMem
		*/
		inline LONG GetSize() const;

		/*! Returns the amount memory used by element storage spaces that contain valid elements.
		\return	The amount of memory used by valid element storage (in bytes).
		\sa CSIBCArray::GetUsed
		\sa CSIBCArray::AllocatedMem
		*/
		inline LONG UsedMem() const;

		/*! Returns the total memory allocated by element storage spaces in the array. This does
		not include the size of the CSIBCArray object itself.
		\return	The amount of memory allocated by element storage spaces (in bytes).
		\sa CSIBCArray::GetSize
		\sa CSIBCArray::AllocatedMem
		*/
		inline LONG AllocatedMem() const;

		/*! Marks \c in_lNbElem elements as used. If there is sufficient allocated space to reserve
		\c in_lNbElem, no extra element storage is allocated. Otherwise, storage space is resized
		to make room for exactly \c in_lNbElem storage spaces.
		\param[in] in_lNbElem	Number of element storage spaces to reserve.
		\return	The number of elements used in the array.
		\sa CSIBCArray::Resize
		\sa CSIBCArray::Extend
		\sa CSIBCArray::InsertAt
		*/
		inline LONG Reserve( const LONG in_lNbElem );

		/*! Changes the number of cells used in the array to \c in_lNewNbElem. If there is sufficient
		space allocated to set \c in_lNewNbElem elements used, no space is allocated. Otherwise,
		twice the requested number of elements are allocated to the array, and \c in_lNewNbElem
		spaces are set to used. This is done so allocation occurs less frequently.
		\param[in]	in_lNewNbElem	Number of elements to resize the array to.
		\return	Number of used elements in the resized array.
		\sa CSIBCArray::Reserve
		\sa CSIBCArray::Extend
		\sa CSIBCArray::InsertAt
		*/
        inline LONG Resize( const LONG in_lNewNbElem );

		/*! Extends the number of cells used in the array by \c in_lNbElem elements. This is equivalent
		to calling SIBCArray::Resize with \c in_lNbElem + SIBCArray::GetUsed().
		\param[in] in_lNbElem	Number of extra elements to set to used in the array.
		\return	Number of used elements in the extended array.
		\sa CSIBCArray::Reserve
		\sa CSIBCArray::Resize
		\sa CSIBCArray::InsertAt
		\sa CSIBCArray::Add
		*/
        inline LONG Extend( const LONG in_lNbElem );

		/*! Adds an element to the end of the array.
		\param[in]	in_Elem	Element of the template declaration type to add at the end of the array.
		\return	Number of used elements in the array, with the new element added.
		\sa CSIBCArray::Reserve
		\sa CSIBCArray::Resize
		\sa CSIBCArray::Extend
		\sa CSIBCArray::InsertAt
		\sa CSIBCArray::operator[]
		*/
		inline LONG Add(CElemType	in_Elem);

		/*! Inserts \c nb element storage spaces at the array index \c idx.
		\param[in]	idx	Index to insert element storage spaces at.
		\param[in]	nb	Number of element storage spaces to insert.
		\return	Number of used elements in the array, after the insertion.
		\sa CSIBCArray::Reserve
		\sa CSIBCArray::Resize
		\sa CSIBCArray::Extend
		\sa CSIBCArray::DeleteAt
		\sa CSIBCArray::Set
		*/
        inline LONG InsertAt(const LONG idx, const LONG nb);

		/*!	Deletes \c nb element storage spaces at the array index \c idx.
		\param[in]	idx	Index to begin element deletion
		\param[in]	nb	Number of elements to delete.
		\sa CSIBCArray::InsertAt
		\sa CSIBCArray::Set
		*/
        inline void DeleteAt(const LONG idx, const LONG nb);

		/*!	Indexing operator. Returns a reference to the element at the index \c in_lIndex.
		\param[in]	in_lIndex	Index of the parameter to get.
		\return	Reference to the element at the index \c in_lIndex.
		\sa CSIBCArray::Add
		\sa CSIBCArray::Set
		*/
        inline CElemType & operator [] ( const ULONG in_lIndex ) const;

		/*!	Indexing operator. Returns a reference to the element at the index \c in_lIndex.
		\param[in]	in_lIndex	Index of the parameter to get.
		\return	Reference to the element at the index \c in_lIndex.
		\sa CSIBCArray::Add
		\sa CSIBCArray::Set
		*/
        inline CElemType & operator [] ( const ULONG in_lIndex );

		/*! Discards element storage spaces allocated but not used in the array, if at least
		\c i_MaxWasted elements are unused.
		\note This function should only be used after major array sizing is done.
		\param[in]	i_MaxWasted	Number of elements required to be wasted before packing occurs (defaults to \c 4).
		\return	Number of elements used in the array.
		\sa CSIBCArray::DisposeData
		*/
        inline LONG Pack( LONG i_MaxWasted = 4 );

		/*! Deletes all element storage spaces, and sets allocated and used element storage spaces both
		to zero.
		\sa CSIBCArray::Become
		*/
        inline void DisposeData( void );

		/*! Sets this array to contain all data from the \c in_rSrcObject array, and then
		sets the \c in_rSrcObject to contain no elements. This destroys all data originally
		contained within this array.

		\param[in]	in_rSrcObject	The object to take data from.
		\return Always returns zero.
		\sa CSIBCArray::Copy
		*/
		inline int Become( CSIBCArray<CElemType>& in_rSrcObject );

		/*! Allocates memory in which to store as many (or more) elements contained in \c in_rSrcObject,
		and copies the data from \c in_rSrcObject into this array. This destroys all data originally
		stored within this array.

		\param[in]	in_rSrcObject	The array source to copy data from.
		\return	Returns the number of elements used.
		\sa CSIBCArray::operator=
		*/
        inline int Copy( const CSIBCArray<CElemType>& in_rSrcObject );

		/*! Sets this array to contain the same information as \c in_rSrcObject. The functionality is
		equivalent to CSIBCArray::Copy.
		\param[in]	in_rSrcObject	Array object to copy data from.
		\return	Reference to this array.
		\sa CSIBCArray::Copy
		*/
		inline CSIBCArray<CElemType>& operator = ( const CSIBCArray<CElemType>& in_rSrcObject );

		/*! Returns the array used internally by this object.
		\return Pointer to the first element in the internal array used by this object.
		*/
        inline CElemType * ArrayPtr( void ) { return m_pElem; }

		/*! Returns a pointer to the array used internally by this object.
		\return Pointer to a pointer to the first element in the internal array used
		by this object.
		*/
        inline CElemType * * ArrayPtrPtr( void ) { return &m_pElem; }

		/*! Sets a given number of elements, \c nb, starting at index \c start to the
		element given by \c value.
		\param[in]	start	The index to start the modification of elements.
		\param[in]	nb		Number of elements to set the value of.
		\param[in]	value	The value to set the elements to.
		*/
        inline void Set( LONG start, LONG nb, CElemType value );

	private:

};

// Constructor
template <class CElemType>
inline CSIBCArray<CElemType>::CSIBCArray
(
    const LONG in_lNbElem
) : m_lNbUsedElem( 0 ),
    m_pElem( NULL ),
	m_lNbAllocElem( 0 )
{
    if ( in_lNbElem > 0 )
        Resize( in_lNbElem );
}

template <class CElemType>
/* 	Returns the number of elements currently used in the array.
	\return Number of used elements
*/
inline LONG  CSIBCArray<CElemType>::GetUsed() const
{
	return m_lNbUsedElem;
}

template <class CElemType>
/* 	Returns the number of elements allocated in the array.
	\return Number of elements allocated
*/
inline LONG  CSIBCArray<CElemType>::GetSize() const
{
	return m_lNbAllocElem;
}

template <class CElemType>
/* 	Returns how much memory is used by the used array elements.
	\return Memory used by used array elements
*/
inline LONG CSIBCArray<CElemType>::UsedMem() const
{
	return m_lNbUsedElem * sizeof( CElemType );
}

template <class CElemType>
/* 	Returns how much memory is allocated for the array.
	\return Memory allocated for the array
*/
inline LONG CSIBCArray<CElemType>::AllocatedMem() const
{
	return m_lNbAllocElem * sizeof( CElemType );
}

template <class CElemType>
/* 	Like Resize(), but allocates only the requested amount. If the requested amount is
	greater than the specified one, it marks the number of used objects but does not
	allocate any more.
	\param[in] in_lNbElem Number of elements to allocate
	\return Number of used elements
*/
inline LONG CSIBCArray<CElemType>::Reserve( const LONG in_lNbElem )
{
    CElemType * l_pTmp;
	int loop;

	//If we've got allocated elements that are unused
	//use one of them instead of allocating more memory
    if ( m_lNbAllocElem >= in_lNbElem )
    {
        return ( m_lNbUsedElem = in_lNbElem );
    }
	else
	{
		//Create the new array consisting of the desired number of elements
		l_pTmp = new CElemType[in_lNbElem];

		//If it was successful, copy the old array over
    	if (l_pTmp != NULL )
    	{
			//Copy and remove memory
			if (m_pElem)
			{
/*
				memcpy( l_pTmp, m_pElem, m_lNbUsedElem * sizeof( CElemType ));
*/
				for (loop = 0; loop < m_lNbUsedElem; loop++)
					l_pTmp[loop] = m_pElem[loop];

				delete [] m_pElem;
			}

			//Assign member array to the newly created array.
        	m_pElem = l_pTmp;


			//Number allocated is different than the number used.
			m_lNbAllocElem = in_lNbElem;

        	return ( m_lNbUsedElem = in_lNbElem );
    	}

    	return m_lNbUsedElem;
	}
}

template <class CElemType>
/* 	Like Resize(), but allocates only the requested amount. If the requested amount is
	greater than the specified one, it marks the number of used objects but does not
	allocate any more.
	\param[in] in_lNewNbElem Number of elements to allocate
	\return Number of used elements
*/
inline LONG CSIBCArray<CElemType>::Resize( const LONG in_lNewNbElem )
{
    CElemType * l_pTmp;
    int i;

	//If we've got allocated elements that are unused
	//use one of them instead of allocating more memory
    if ( m_lNbAllocElem >= in_lNewNbElem )
    {
        return ( m_lNbUsedElem = in_lNewNbElem );
    }
	else
	{
		//Add 100% onto the array in order to buffer
		LONG l_lNbAlloc = in_lNewNbElem + in_lNewNbElem;

		//Create the new array consisting of the desired number of elements
		l_pTmp = new CElemType[l_lNbAlloc];

		//If it was successful, copy the old array over
    	if (l_pTmp != NULL )
    	{
			//Copy and remove memory
			if (m_pElem)
			{
				for ( i = 0; i < m_lNbUsedElem; i++ )
				{
					l_pTmp[i] = m_pElem[i];
				}

				delete [] m_pElem;
			}

			//Assign member array to the newly created array.
        	m_pElem = l_pTmp;


			//Number allocated is different than the number used.
			m_lNbAllocElem = l_lNbAlloc;

        	return ( m_lNbUsedElem = in_lNewNbElem );
    	}

    	return m_lNbUsedElem;
	}
}

template <class CElemType>
/* 	Calls Resize() with the current number used + the number requested.
	\param[in] in_lNbElem Number of elements requested
	\return Number of used elements
*/
inline LONG CSIBCArray<CElemType>::Extend( const LONG in_lNbElem )
{
	return Resize( m_lNbUsedElem + in_lNbElem );
}


template <class CElemType>
/* 	Copies another array.
	\param[in] in_rSrcObject Array to copy
	\return Number of used elements
*/
inline int CSIBCArray<CElemType>::Copy
(
    const CSIBCArray<CElemType> & in_rSrcObject
)
{
	int		loop;
	DisposeData();



	if (in_rSrcObject.GetUsed() > 0)
	{
		//Pre-allocate needed memory
		Reserve( in_rSrcObject.GetUsed() );

		//Say that we will use all of it.
		Resize( in_rSrcObject.GetUsed() );

		//Check to see that everything worked correctly
		if (m_lNbUsedElem >= in_rSrcObject.GetUsed())
		{
			//Copy over data from other object
			for (loop = 0; loop < m_lNbUsedElem; loop++)
				m_pElem[loop] = in_rSrcObject.m_pElem[loop];


			//Return the number of elements in the array
    		return m_lNbUsedElem;
		}
	}

	return 0;
}

template <class CElemType/*!< Object from which to move data*/>
/* 	Moves the array data from \c in_rSrcObject to this CSIBArray and sets \c in_rSrcObject to null.
	\param[in] in_rSrcObject Reference object from which to move data
	\return \c 0
*/
inline int CSIBCArray<CElemType>::Become( CSIBCArray<CElemType>& in_rSrcObject )
{
	DisposeData();

	//Copy values
	m_pElem			= in_rSrcObject.m_pElem;
	m_lNbUsedElem	= in_rSrcObject.m_lNbUsedElem;
	m_lNbAllocElem	= in_rSrcObject.m_lNbAllocElem;

	//kill source
	in_rSrcObject.m_pElem			= NULL;
	in_rSrcObject.m_lNbUsedElem		= 0;
	in_rSrcObject.m_lNbAllocElem	= 0;

	return 0;
}

template <class CElemType>
/* 	Copies another array.
	\param[in] i_That Type of element
	\return Pointer to the array
*/
inline CSIBCArray<CElemType> & CSIBCArray<CElemType>::operator =
(
	const CSIBCArray<CElemType> & i_That
)
{
    this->Copy( i_That );

	return *this;
}

template <class CElemType>
/* 	Deletes all the data allocated to the object and sets the number used/allocated to \c 0.
	\return void
*/
inline void CSIBCArray<CElemType>::DisposeData()
{
	//If the elements exist, delete them
    if ( m_pElem != NULL )
    {
		//Delete the array pointer and set it to null for reference
        delete [] m_pElem;
	}

	//Eliminate the counts to 0.
    m_lNbUsedElem = 0;
	m_lNbAllocElem = 0;
	m_pElem = NULL;
}

template <class CElemType>
/* 	Removes the excess space after the array by allocating a new one of the same length
	and then copying the old one over.  To be used after major array resizing only.
	\param[in] i_MaxWasted Number of elements in array
	\return The number possible based on the used elements
*/
LONG CSIBCArray<CElemType>::Pack( LONG i_MaxWasted )
{
	int loop;

	//Check to see if packing is neccesary
    if (( m_lNbAllocElem - m_lNbUsedElem ) > i_MaxWasted )
    {

		//Update the number of allocated element count
		m_lNbAllocElem = m_lNbUsedElem;

		//Create the new array
		CElemType * l_pTmp = new CElemType[m_lNbUsedElem];

		//If we were successful, copy the old elements over
        if ( l_pTmp != NULL )
        {
			//If there are old elements, copy them
			if (m_pElem)
			{
				//Byte copy old elements (number * size)
/*
				memcpy( l_pTmp, m_pElem, m_lNbUsedElem * sizeof(CElemType) );
*/
				for (loop = 0; loop < m_lNbUsedElem; loop++)
					l_pTmp[loop] = m_pElem[loop];

				//Delete original array
				delete [] m_pElem;
			}

			//copy pointer to new array since old was deleted or null
            m_pElem = l_pTmp;
        }

    }

	//Return the number possible based on the used elements
    return m_lNbUsedElem;

}

template <class CElemType>
/* 	Returns item at the specified position in the array.
	\param[in] in_lIndex Index of the element to retrieve
	\return Reference to the element in the array
*/
inline CElemType & CSIBCArray<CElemType>::operator []
(
    const ULONG in_lIndex
) const
{
	_SI_ASSERT(in_lIndex < ((ULONG)m_lNbUsedElem));
	_SI_ASSERT(in_lIndex >= 0);
    return m_pElem[in_lIndex];
}

// Operator [] overload
template <class CElemType>
inline CElemType & CSIBCArray<CElemType>::operator []
(
    const ULONG in_lIndex
)
{
	_SI_ASSERT(in_lIndex < ((ULONG)m_lNbUsedElem));
	_SI_ASSERT(in_lIndex >= 0);
    return m_pElem[in_lIndex];
}

template <class CElemType>
/* 	Sets a range of elements to the specified value.
	\param[in] start First element in the array
	\param[in] nb First element in the array
	\param[in] value Number of elements in the array
*/
inline void CSIBCArray<CElemType>::Set
(

    LONG start,
	LONG nb,
	CElemType value
)
{
	//Make sure elements exist
    if ( m_pElem != NULL )
    {
        LONG    l_lEnd = start + nb;

        if ( l_lEnd > m_lNbUsedElem )
            l_lEnd = m_lNbUsedElem;

        for ( LONG i = start; i < l_lEnd; i++ )
            m_pElem[i] = value;
    }
}

template <class CElemType>
/* 	Inserts elements at the specified location.
	\param[in] in_lIndex Index location
	\param[in] in_lNbElem Number of elements
	\return The number of used elements
*/
inline LONG CSIBCArray<CElemType>::InsertAt
(
    const LONG in_lIndex,
    const LONG in_lNbElem
)
{
    LONG    l_lOldNb	= m_lNbUsedElem;
    LONG    l_lNb		= m_lNbUsedElem + in_lNbElem;
	LONG	l_lInsert	= in_lIndex;

	//Check to make sure it's inside the boudns
	if (l_lInsert > m_lNbUsedElem)
		l_lInsert = m_lNbUsedElem;

	//Ensure we have enough space
    Reserve( l_lNb );

	//Use all of it
	Resize( l_lNb );

   	if (l_lOldNb > in_lIndex)
       	memmove(&m_pElem[in_lIndex + in_lNbElem], &m_pElem[in_lIndex], (unsigned int) (sizeof(CElemType) *  (l_lOldNb - in_lIndex)));

	return m_lNbUsedElem;
}

template <class CElemType>
/* 	Removes the specified elements from the array starting at the specified location.
	\param[in] in_lIndex Index location
	\param[in] in_lNbElem Number of elements
*/
inline void CSIBCArray<CElemType>::DeleteAt
(
    const LONG in_lIndex,
    const LONG in_lNbElem
)
{
	LONG l_lToDelete = in_lNbElem;

	if ( l_lToDelete > m_lNbUsedElem  )
		l_lToDelete = m_lNbUsedElem;

    if ((in_lIndex + in_lNbElem) < m_lNbUsedElem )
        memmove( &m_pElem[ in_lIndex ], &m_pElem [ in_lIndex + l_lToDelete ], (unsigned int) (sizeof(CElemType) * (m_lNbUsedElem -  (in_lIndex + l_lToDelete ))));

	m_lNbUsedElem -= l_lToDelete;
}

template <class CElemType>
/* 	Adds a new element to the end of the array.
	\param[in] in_Elem Element to add
	\return The number of used elements
*/
inline LONG CSIBCArray<CElemType>::Add
(
    CElemType in_Elem
)
{
	Extend(1);
	m_pElem[m_lNbUsedElem - 1] = in_Elem;
	return m_lNbUsedElem;

}

#ifdef _WIN32
#pragma warning(disable:4251)
#endif

#endif // ALREADY_INCLUDED_CSIBCArray
