//*****************************************************************************
/*!
   \file xsi_value.h
   \brief CValue and CValueArray class declarations.

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIVALUE_H__
#define __XSIVALUE_H__

#include "sicppsdk.h"
#include "xsi_ref.h"

namespace XSI {

class CLongArray;
class CFloatArray;
class CValueArray;

namespace MATH {
	class CVector3;
	class CVector2f;
	class CVector3f;
	class CVector4f;
	class CQuaternionf;
	class CRotationf;
	class CMatrix3f;
	class CMatrix4f;
	class CColor4f;
	class CShape;
};

//*****************************************************************************
/*! \class CValue xsi_value.h
	\brief The CValue object provides the convenience of a loosely typed variable inside a strictly
	typed language like C++.

	In C++ all variables are strictly typed.  For example "x" may be declared as an INT and "y" as a
	double.  However scripting languages are often loosely typed, so a variable named x may contain a
	string or an integer or even a pointer to an object.  The exact type of x is only determined when
	it is assigned a value, and the type of x can be changed at runtime by re-assigning its value.

	For example, consider FCurve::AddKey. Because FCurves can be based on double, integer or boolean
	key values, there could be three versions of the function:

	\code
			%FCurve::AddKey( ...double in_value... )
			%FCurve::AddKey( ...integer in_value... )
			%FCurve::AddKey( ...bool in_value... )
	\endcode

	However, with the availability of a class like CValue, all three functions can be replaced by a
	single one:

	\code FCurve::AddKey( ...const CValue& in_value... ) \endcode

	A CValue can store basic types like longs, floats and CString. By storing a CRef it can also
	contain a reference to any object in the scene.  It can contain an entire array of values via
	CValueArray.  It can also be used to hold a raw pointer to your own data or objects.
	Exceptionnaly, CVector3 objects can be contained in a CValue but other math objects are not
	automatically supported since they are not based on CBase.

	The CValue::ChangeType and CValue::GetAsText methods are very useful for data conversion, for
	example to turn the value 55.5 to the string "55.5".

	CValue is very similar to the VARIANT structure used in Win32.  It is possible to convert between
	the two types using XSIVariantFromCValue and XSIVariantToCValue. However normally conversion is
	automatic, for example when using CComAPIHandler or when a custom C++ command is called from
	scripting.  As a result it is possible to use this object without any knowledge of difficult COM
	datatypes like BSTR and SAFEARRAY. Because CValue provides operator overloads and various constructors
	it is much easier to use than a VARIANT and code using CValue will look very similar to the equivalent
	script code.

  	\eg Demonstrates CValue usage
	\code
		using namespace XSI;
		Application app;

		// x has type "empty" and no value
		CValue x ;

		// Give x a value of type siInt4
		x = 5 ;

		// Change the type to siFloat by assigning a new value
		x = 6.0f;

		// Change the value 6.0 to the string "6.0"
		x.ChangeType( CValue::siString ) ;

		// Copy the value
		CValue y = x ;

		// It is possible to test exactly what type
		// of data a CValue contains
		if ( y.m_t == CValue::siString )
		{
			app.LogMessage( L"y has the value " + (CString)y ) ;
		}

		// CValueArray containing 3 CValue objects
		CValueArray a(3) ;

		a[0] = CValue( 125 ); // Explicit construction
		a[1] = 135 ;		   // Implicit call to CValue( int )
		a[2] = L"String" ;     // Implicit call to CValue( const wchar_t* )

		// Now copy the entire CValueArray into a CValue.
		// b will have type siArray
		CValue b( a ) ;

		// Use the cast operator to access the Array inside b
		LONG size = ((CValueArray&)b).GetCount() ;

		//Will print: 'INFO : "Array contents: (125,135,String)"
		app.LogMessage( L"Array contents: " + b.GetAsText() ) ;


		// Copy the first array item
		CValue item1 = ((CValueArray&)b)[1] ;

		// Will print: 'INFO : "Item1 contains 135 and has type 3"
		// Notice how using a temporary CValue can be a
		// convenient way to convert a number (m_t) to text.
		app.LogMessage( L"Item1 contains " + item1.GetAsText()
						+ L" and has type " + CValue( (LONG)item1.m_t ).GetAsText() ) ;

	\endcode

	\eg Demonstrates using CValue with the GetValue command
	\code
		using namespace XSI;
		Application app;
		Model root = app.GetActiveSceneRoot();

		X3DObject myCube;
		root.AddGeometry( L"Cube", L"MeshSurface", CString(L"MyCube"), myCube );

		// change the cube's position x parameter value
		Parameter posx( myCube.GetParameter(L"posx") );
		CValue posxVal( posx.GetValue() );

		posx.PutValue( ((double)posxVal + 5.75) * 2.0 );

		app.LogMessage( posx.GetValue().GetAsText() );
	\endcode
*/
//*****************************************************************************

class SICPPSDKDECL CValue
{
public:
	typedef void* siPtrType;

	struct Blob
	{
		ULONG m_nSize;
		unsigned char* m_pBlobData;
	};
	typedef Blob siBlobType;

	//! DataType enumerator.
	enum DataType
	{
		siEmpty = 0,	/*!< empty type */
		siInt2 = 2,		/*!< 2 bytes signed integer number type (-32768..32767) */
		siInt4 = 3,		/*!< 4 bytes signed integer number type (-2147483648..2147483647) */
		siInt8 = 10,	/*!< 8 bytes signed integer number type (-9223372036854775808..9223372036854775807) */
		siFloat = 4,	/*!< float type */
		siDouble = 5,	/*!< double type */
		siString = 8,	/*!< A normal Softimage string.  In the C++ API this corresponds to the CString object. */
		siIDispatch = 9, /*!< IDispatch pointer type. This is the data type for the COM objects that expose methods and properties to scripting
		in addition to all Softimage objects in the scripting Object %Model while \c siRef is the normal representation of Softimage objects in
		the C++ API.  See CComAPIHandler and XSI::ConvertObject for more information about handling objects of this type in the C++ API. The value
		is stored in \c m_u.pval; however you should \b never access it directly from this structure member, because the result may be undefined.
		Use CValue::operator siPtrType() instead to access the IDispatch pointer. */
		siBool = 11,	/*!< boolean type */
		siIUnknown = 13, /*!< IUnknown pointer type. This represents a COM object.  Normally such objects are not accessible to the C++ API or
		to scripting. The value is stored in \c m_u.pval; however you should \b never access it directly from this structure member, because the
		result may be undefined. Use CValue::operator siPtrType() instead to access the IUnknown pointer. */
		siInt1 = 16,	/*!< byte type (-128..127) */
		siUInt1 = 17,	/*!< unsigned byte type (0..255) */
		siUInt2 = 18,	/*!< 2 bytes unsigned integer number type (0..65535) */
		siUInt4 = 19,	/*!< 4 bytes unsigned integer number type (0..4294967295) */
		siUInt8 = 20,	/*!< 8 bytes unsigned integer number type (0..18446744073709551615) */
		siWStr  = 31,	/*!< Null-terminated wide character string.  This data type is rarely encountered because \c siString is the recommended
		representation of all Softimage strings. */
		siRef = 666,	/*!< CRef object type */
		siArray,		/*!< Array of type CValue */
		siPtr,			/*!< Pointer type */
		siRefArray,		/*!< CRefArray object type */
		siVector3,		/*!< CVector3 object type */
		siLongArray,	/*!< CLongArray object type */
		siFloatArray,	/*!< CFloatArray object type */
		siVector2f=800,	/*!< CVector2f object type */
		siVector3f,		/*!< CVector3f object type */
		siVector4f,		/*!< CVector4f object type */
		siQuaternionf,	/*!< CQuaternionf object type */
		siRotationf,	/*!< CRotationf object type */
		siMatrix3f,		/*!< CMatrix3f object type */
		siMatrix4f,		/*!< CMatrix4f object type */
		siColor4f,		/*!< CColor4f object type */
		siShape,		/*!< CShape object type */
		siBlob,			/*!< Blob object type */
		siStringArray   /*!< CStringArray object type */
	};

	/*! This union is used for storing the value described by the CValue::m_t data member. Instead
	of accessing the value stored in CValue::m_u directly, it is strongly recommended to use the
	extractor methods defined by CValue.

	\eg Demonstrates the CValue extractor methods
	\code
		CValue val((short)255);

		// good but not recommended
		short wrong = val.sval;

		// right way to do it
		short good = (short)val;

		CComAPIHandler uitoolkit;
		uitoolkit.CreateInstance( L"XSI.UIToolkit");

		CValue dispVal = uitoolkit.GetRef();

		// wrong way of accessing a COM object from a CValue, could return
		// an invalid pointer
		IDispatch* pDisp = dispVal.pval;

		// this is the right way to do it
		IDispatch* pDisp = (IDispatch*)(CValue::siPtrType)dispVal;
	\endcode
	*/
	union ValueField
	{
		short				sval;		/*!< 2 bytes signed integer number value (-32768..32767) */
		LONG				lval;		/*!< 4 bytes signed integer number value (-2147483648..2147483647) */
		float				fval;		/*!< float value */
		double				dval;		/*!< double value */
		bool				bval;		/*!< bool value */
		wchar_t*			pwval;		/*!< CString value */
		siPtrType			pval;		/*!< pointer value */
		signed char			cval;		/*!< byte value */
		unsigned char		ucval;		/*!< unsigned byte value */
		CValueArray*		paval;		/*!< Array value */
		CLongArray*			plaval;		/*!< Long Array value */
		CFloatArray*		pfaval;		/*!< Float Array value */
		unsigned short		usval;		/*!< 2 bytes unsigned integer number value (0..65535) */
		ULONG				ulval;		/*!< 4 bytes unsigned integer number value (0..4294967295) */
		MATH::CVector2f*	pv2f;		/*!< CVector2f pointer */
		MATH::CVector3f*	pv3f;		/*!< CVector3f pointer */
		MATH::CVector4f*	pv4f;		/*!< CVector4f pointer */
		MATH::CQuaternionf*	pqf;		/*!< CQuaternionf pointer */
		MATH::CRotationf*	prf;		/*!< CRotationf pointer */
		MATH::CMatrix3f*	pm3f;		/*!< CMatrix3f pointer */
		MATH::CMatrix4f*	pm4f;		/*!< CMatrix4f pointer */
		MATH::CColor4f*		pc4f;		/*!< CColor4f pointer */
		MATH::CShape*		pshp;		/*!< CShape pointer */
		LLONG				llval;		/*!< 8 bytes signed integer number type (-9223372036854775808..9223372036854775807) */
		ULLONG				ullval;		/*!< 8 bytes unsigned integer number type (0..18446744073709551615) */
		siBlobType*			pblobval;	/*!< siBlobType value */
		CStringArray*		pstrarrayval;		/*!< CStringArray value*/
	}m_u;
	DataType m_t;

	/*! Default constructor. */
	CValue();

	/*! Default destructor. */
	virtual ~CValue();

	/*! Constructor.
	\param valSrc CValue object
	*/
	CValue(const CValue& valSrc);

	/*! Constructor.
	\param valSrc short value
	*/
	CValue(short valSrc);

	/*! Constructor.
	\param valSrc unsigned short value
	*/
	CValue(unsigned short valSrc);

	/*! Constructor.
	\param valSrc LONG value
	*/
	CValue(LONG valSrc);

#if !defined(linux) || !defined(__x86_64)
	/*! Constructor.  Has the same results as using the LONG constructor.
	\param valSrc int value
	*/
	CValue(int valSrc);
#endif

	/*! Constructor.
	\param valSrc ULONG value
	*/
	CValue(ULONG valSrc);

	/*! Constructor.
	\param valSrc LLONG value
	\since 7.0
	*/
	CValue(LLONG valSrc);

	/*! Constructor.
	\param valSrc ULLONG value
	\since 7.0
	*/
	CValue(ULLONG valSrc);

	/*! Constructor.
	\param valSrc float value
	*/
	CValue(float valSrc);

	/*! Constructor.
	\param valSrc double value
	*/
	CValue(double valSrc);

	/*! Constructor.
	\param valSrc bool value
	*/
	CValue(bool valSrc);

	/*! Constructor.
	\param valSrc CString value
	*/
	CValue(const CString& valSrc);

	/*! Constructor.
	\param valSrc CRef value
	*/
	CValue(const CRef& valSrc);

	/*! Constructor.
	\param valSrc CRefArray value
	\since 4.0
	*/
	CValue(const CRefArray& valSrc);

	/*! Constructor.
	\param valSrc unsigned char value
	*/
	CValue(unsigned char valSrc);

	/*! Constructor.
	\param valSrc signed char value
	*/
	CValue(signed char valSrc);

	/*! Constructor.
	\param valSrc CValueArray value
	*/
	CValue(const CValueArray& valSrc);

	/*! Constructor.
	\param valSrc CLongArray value
	\since 7.0
	*/
	CValue(const CLongArray& valSrc);

	/*! Constructor.
	\param valSrc CFloatArray value
	\since 7.0
	*/
	CValue(const CFloatArray& valSrc);

	/*! Constructor.
	\param valSrc MATH::CVector3 value
	\since 5.1
	*/
	CValue(const MATH::CVector3& valSrc);

	/*! Constructor.
	\param valSrc MATH::CVector2f value
	\since 7.0
	*/
	CValue(const MATH::CVector2f& valSrc);

	/*! Constructor.
	\param valSrc MATH::CVector3f value
	\since 7.0
	*/
	CValue(const MATH::CVector3f& valSrc);

	/*! Constructor.
	\param val MATH::CVector4f value
	\since 7.0
	*/
	CValue(const MATH::CVector4f& val);

	/*! Constructor.
	\param val MATH::CQuaternionf value
	\since 7.0
	*/
	CValue(const MATH::CQuaternionf& val);

	/*! Constructor.
	\param val MATH::CRotationf value
	\since 7.0
	*/
	CValue(const MATH::CRotationf& val);

	/*! Constructor.
	\param val MATH::CMatrix3f value
	\since 7.0
	*/
	CValue(const MATH::CMatrix3f& val);

	/*! Constructor.
	\param val MATH::CMatrix4f value
	\since 7.0
	*/
	CValue(const MATH::CMatrix4f& val);

	/*! Constructor.
	\param val MATH::CColor4f value
	\since 7.0
	*/
	CValue(const MATH::CColor4f& val);

	/*! Constructor.
	\param val MATH::CShape value
	\since 7.0
	*/
	CValue(const MATH::CShape& val);

	/*! Constructor.
	\param valSrc pointer value
	*/
	CValue(siPtrType valSrc);

	/*! Constructor.
	\param valSrc siBlobType value
	*/
	CValue(const siBlobType& valSrc);

	/*! Constructor.
	\param valSrc string value
	*/
	CValue(const wchar_t* valSrc);

	/*! Constructor.
	\param valSrc Ascii string value
	*/
	CValue(const char* valSrc);

	/*! Constructor.
	\param valSrc CStringArray value
	\since 12.0 (2014)
	*/
	CValue(const CStringArray& valSrc);

	/*! Assignment
	\param valSrc CValue value
	*/
	CValue& operator=(const CValue& valSrc);

	/*! Assignment
	\param valSrc short value
	*/
	CValue& operator=(short valSrc);

	/*! Assignment
	\param valSrc unsigned short value
	*/
	CValue& operator=(unsigned short valSrc);

	/*! Assignment
	\param valSrc LONG value
	*/
	CValue& operator=(LONG valSrc);

#if !defined(linux) || !defined(__x86_64)
	/*! Assignment
	\param valSrc int value
	*/
	CValue& operator=(int valSrc);
#endif

	/*! Assignment
	\param valSrc ULONG value
	*/
	CValue& operator=(ULONG valSrc);

	/*! Assignment
	\param valSrc LLONG value
	\since 7.0
	*/
	CValue& operator=(LLONG valSrc);

	/*! Assignment
	\param valSrc ULLONG value
	\since 7.0
	*/
	CValue& operator=(ULLONG valSrc);

	/*! Assignment
	\param valSrc float value
	*/
	CValue& operator=(float valSrc);

	/*! Assignment
	\param valSrc double value
	*/
	CValue& operator=(double valSrc);

	/*! Assignment
	\param valSrc bool value
	*/
	CValue& operator=(bool valSrc);

	/*! Assignment
	\param valSrc CString value
	*/
	CValue& operator=(const CString& valSrc);

	/*! Assignment
	\param valSrc Wide Character String
	*/
	CValue& operator=(const wchar_t * valSrc );

	/*! Assignment
	\param valSrc Ascii string value.
	*/
	CValue& operator=(const char* valSrc );

	/*! Assignment
	\param valSrc CRef value
	*/
	CValue& operator=(const CRef& valSrc);

	/*! Assignment
	\param valSrc CRefArray value
	\since 4.0
	*/
	CValue& operator=(const CRefArray& valSrc);

	/*! Assignment
	\param valSrc MATH::CVector3 value
	\since 5.1
	*/
	CValue& operator=(const MATH::CVector3& valSrc);

	/*! Assignment
	\param valSrc MATH::CVector2f value
	\since 7.0
	*/
	CValue& operator=(const MATH::CVector2f& valSrc);

	/*! Assignment
	\param valSrc MATH::CVector3f value
	\since 7.0
	*/
	CValue& operator=(const MATH::CVector3f& valSrc);

	/*! Assignment
	\param valSrc MATH::CVector4f value
	\since 7.0
	*/
	CValue& operator=(const MATH::CVector4f& valSrc);

	/*! Assignment
	\param valSrc MATH::CMatrix3f value
	\since 7.0
	*/
	CValue& operator=(const MATH::CMatrix3f& valSrc);

	/*! Assignment
	\param valSrc MATH::CMatrix4f value
	\since 7.0
	*/
	CValue& operator=(const MATH::CMatrix4f& valSrc);

	/*! Assignment
	\param valSrc MATH::CRotationf value
	\since 7.0
	*/
	CValue& operator=(const MATH::CRotationf& valSrc);

	/*! Assignment
	\param valSrc MATH::CQuaternionf value
	\since 7.0
	*/
	CValue& operator=(const MATH::CQuaternionf& valSrc);

	/*! Assignment
	\param valSrc MATH::CColor4f value
	\since 7.0
	*/
	CValue& operator=(const MATH::CColor4f& valSrc);

	/*! Assignment
	\param valSrc MATH::CShape value
	\since 7.0
	*/
	CValue& operator=(const MATH::CShape& valSrc);

	/*! Assignment
	\param valSrc unsigned char value
	*/
	CValue& operator=(unsigned char valSrc);

	/*! Assignment
	\param valSrc signed char value
	*/
	CValue& operator=(signed char valSrc);

	/*! Assignment
	\param valSrc CValueArray value
	*/
	CValue& operator=(const CValueArray& valSrc);

	/*! Assignment
	\param valSrc CLongArray value
	*/
	CValue& operator=(const CLongArray& valSrc);

	/*! Assignment
	\param valSrc CFloatArray value
	*/
	CValue& operator=(const CFloatArray& valSrc);

	/*! Assignment
	\param valSrc pointer value
	*/
	CValue& operator=(siPtrType valSrc);

	/*! Assignment
	\param valSrc siBlobType value
	*/
	CValue& operator=(const siBlobType& valSrc );

	/*! Assignment
	\param valSrc CStringArray value
	\since 12.0 (2014)
	*/
	CValue& operator=(const CStringArray& valSrc );

	/*! short extractor	*/
	operator short () const;
	/*! unsigned short extractor	*/
	operator unsigned short () const;
	/*! LONG extractor	*/
	operator LONG () const;

#if !defined(linux) || !defined(__x86_64)
	/*! int extractor
	\since 5.1
	*/
	operator int () const;
#endif

	/*! ULONG extractor
	\since 5.0
	*/
	operator ULONG () const;

	/*! LLONG extractor
	\since 7.0
	*/
	operator LLONG () const;

	/*! ULLONG extractor
	\since 7.0
	*/
	operator ULLONG () const;

	/*! float extractor	*/
	operator float () const;
	/*! double extractor	*/
	operator double () const;
	/*! bool extractor	*/
	operator bool () const;
	/*! CString extractor	*/
	operator CString () const;
	/*! CRef extractor	*/
	operator CRef () const;
	/*! The CRefArray extractor returns a CRefArray if the source is a siRefArray type. If the source is
	a siRef type, the extractor returns a one element CRefArray containing the source object. The function
	returns an empty array if the source is invalid.
	*/
	operator CRefArray () const;
	/*! unsigned byte extractor	*/
	operator unsigned char () const;
	/*! byte extractor	*/
	operator signed char () const;
	/*! CValueArray& extractor	*/
	operator CValueArray& () const;

	/*! CLongArray& extractor
	\since 7.0
	*/
	operator CLongArray& () const;

	/*! CFloatArray& extractor
	\since 7.0
	*/
	operator CFloatArray& () const;

	/*! CVector3 extractor
	\since 5.1
	*/
	operator MATH::CVector3 () const;

	/*! CVector2f extractor
	\since 7.0
	*/
	operator MATH::CVector2f() const;

	/*! CVector3f extractor
	\since 7.0
	*/
	operator MATH::CVector3f() const;

	/*! CVector4f extractor
	\since 7.0
	*/
	operator MATH::CVector4f() const;

	/*! CMatrix3f extractor
	\since 7.0
	*/
	operator MATH::CMatrix3f() const;

	/*! CMatrix4f extractor
	\since 7.0
	*/
	operator MATH::CMatrix4f() const;

	/*! CRotationf extractor
	\since 7.0
	*/
	operator MATH::CRotationf() const;

	/*! CQuaternionf extractor
	\since 7.0
	*/
	operator MATH::CQuaternionf() const;

	/*! CColor4f extractor
	\since 7.0
	*/
	operator MATH::CColor4f() const;

	/*! CShape extractor
	\since 7.0
	*/
	operator MATH::CShape() const;

	/*! CValue::siPtrType extractor. The data returned by this function depends on the type of this CValue:

	\li \c siIDispatch, pointer type returned: \c IDispatch*
	\li \c siIUnknown, pointer type returned: \c IUnknown*
	\li \c siPtr, pointer type returned: \c void*

	\warning Always use this function to access the pointer stored in \c m_u.pval, do not access \c m_u.pval
		directly otherwise the result may be undefined.

	\note Returned pointers to IDispatch and IUnknown are reference counted.

	\eg
	\code
		using namespace XSI;

		CComAPIHandler uitoolkit;
		uitoolkit.CreateInstance( L"XSI.UIToolkit");

		// retrieves the IDispatch pointer of the Softimage UI toolkit object
		CValue dispVal = uitoolkit.GetRef();
		IDispatch* pDisp = (IDispatch*)(CValue::siPtrType)dispVal;
	\endcode
	*/
	operator siPtrType () const;

	/*! siBlobType extractor
	\since 8.0 (2010)
	*/
	operator siBlobType&() const;

	/*! CStringArray extractor
	\since 12.0 (2014)
	*/
	operator CStringArray&() const;

	/*! Comparison
	\param valSrc CValue value
	*/
	bool operator==(const CValue& valSrc) const;

	/*! short equality operator	*/
	inline bool operator== (short) const;
	/*! unsigned short equality operator	*/
	inline bool operator== (unsigned short) const;
	/*! LONG equality operator	*/
	inline bool operator== (LONG) const;
#if !defined(linux) || !defined(__x86_64)
	/*! int equality operator	*/
	inline bool operator== (int) const;
#endif
	/*! ULONG equality operator	*/
	inline bool operator== (ULONG) const;

	/*! LLONG equality operator
	\since 7.0
	*/
	inline bool operator== (LLONG) const;

	/*! ULLONG equality operator
	\since 7.0
	*/
	inline bool operator== (ULLONG) const;

	/*! float equality operator	*/
	inline bool operator== (float) const;
	/*! double equality operator	*/
	inline bool operator== (double) const;
	/*! bool equality operator	*/
	inline bool operator== (bool) const;
	/*! CString equality operator	*/
	inline bool operator== (const CString&) const;
	/*! wchar_t * equality operator	*/
	inline bool operator== (const wchar_t*) const;
	/*! char * equality operator	*/
	inline bool operator== (const char*) const;
	/*! CRef equality operator	*/
	inline bool operator== (const CRef&) const;
	/*! CRefArray equality operator
	\since 4.0
	*/
	inline bool operator== (const CRefArray&) const;
	/*! unsigned byte equality operator	*/
	inline bool operator== (unsigned char) const;
	/*! byte equality operator	*/
	inline bool operator== (signed char) const;
	/*! CValueArray& equality operator	*/
	bool operator== (const CValueArray&) const;

	/*! CLongArray& equality operator
		\since 7.0
	*/
	bool operator== (const CLongArray&) const;

	/*! CFloatArray& equality operator
		\since 7.0
	*/
	bool operator== (const CFloatArray&) const;

	/*! siPtrType equality operator	*/
	inline bool operator== (const siPtrType) const;

	/*! siBlobType equality operator	*/
	inline bool operator == (const siBlobType&) const;

	/*! CVector3 equality operator
		\since 5.1
	*/
	inline bool operator== (const MATH::CVector3&) const;

	/*! CVector2f equality operator
		\since 7.0
	*/
	inline bool operator== (const MATH::CVector2f&) const;

	/*! CVector3f equality operator
		\since 7.0
	*/
	inline bool operator== (const MATH::CVector3f&) const;

	/*! CVector4f equality operator
		\since 7.0
	*/
	inline bool operator== (const MATH::CVector4f&) const;

	/*! CMatrix3f equality operator
		\since 7.0
	*/
	inline bool operator== (const MATH::CMatrix3f&) const;

	/*! CMatrix4f equality operator
		\since 7.0
	*/
	inline bool operator== (const MATH::CMatrix4f&) const;

	/*! CRotationf equality operator
		\since 7.0
	*/
	inline bool operator== (const MATH::CRotationf&) const;

	/*! CQuaternionf equality operator
		\since 7.0
	*/
	inline bool operator== (const MATH::CQuaternionf&) const;

	/*! CColor4f equality operator
		\since 7.0
	*/
	inline bool operator== (const MATH::CColor4f&) const;

	/*! CShape equality operator
		\since 7.0
	*/
	inline bool operator== (const MATH::CShape&) const;

	/*! CStringArray equality operator
		\since 12.0 (2014)
	*/
	inline bool operator== (const CStringArray&) const;

	/*! Inequality
	\param valSrc CValue value
	*/
	bool operator!=(const CValue& valSrc) const;

	/*! Greater than operator. Return true if this value is greater than val, false otherwise. Return false if types don't match.
	\note operator > is not available for the following types and always returns false: 
	\li \ref CValue::siArray
	\li \ref CValue::siBlob
	\li \ref CValue::siEmpty
	\li \ref CValue::siFloatArray
	\li \ref CValue::siIDispatch
	\li \ref CValue::siIUnknown
	\li \ref CValue::siLongArray
	\li \ref CValue::siPtr
	\li \ref CValue::siRef
	\li \ref CValue::siRefArray
	\li \ref CValue::siShape
	\li \ref CValue::siVector3
	\param val Value to test.
	\since 10.5 (2012)
	*/
	bool operator > (const CValue& val ) const;

	/*! Less than operator. Return true if this value is less than val, false otherwise. Return false if types don't match.
	\note operator < is not available for the following types and always returns false: 
	\li \ref CValue::siArray
	\li \ref CValue::siBlob
	\li \ref CValue::siEmpty
	\li \ref CValue::siFloatArray
	\li \ref CValue::siIDispatch
	\li \ref CValue::siIUnknown
	\li \ref CValue::siLongArray
	\li \ref CValue::siPtr
	\li \ref CValue::siRef
	\li \ref CValue::siRefArray
	\li \ref CValue::siShape
	\li \ref CValue::siVector3
	\param val Value to test.
	\since 10.5 (2012)
	*/
	bool operator < (const CValue& val ) const;

	/*! Greater than or equal to operator. Return true if this value is greater or equal to val, false otherwise. Return false if types don't match.
	\param val Value to test.
	\since 10.5 (2012)
	*/
	bool operator >= (const CValue& val ) const;

	/*! Less than or equal to operator. Return true if this value is less or equal to val, false otherwise. Return false if types don't match.
	\param val Value to test.
	\since 10.5 (2012)
	*/
	bool operator <= (const CValue& val ) const;

	// low-level operations

	/*! Converts the object into a given type. If in_pSrc is NULL, the conversion is done in place,
	otherwise the object is copied from in_pSrc and then converted. This function can also be used
	to create a CValue object of type siIDispatch or siIUnknown, see example below.

	\param in_type Type to convert into.
	\param in_pSrc Pointer to the CValue to convert

	\eg Converting a LONG to double value
	\code
		using namespace XSI;
		Application app;

		CValue val((LONG)55);
		app.LogMessage( L"Value = " + val.GetAsText() );

		val.ChangeType( CValue::siDouble );
		app.LogMessage( L"Value = " + val.GetAsText() );
		\endcode

		\eg Setting a CValue as a IUnknown pointer
		\code
		using namespace XSI;
		Application app;

		CComAPIHandler uitoolkit;
		uitoolkit.CreateInstance( L"XSI.UIToolkit");

		// retrieves a IDispatch pointer from the Softimage UI toolkit object
		CValue dispVal = uitoolkit.GetRef();
		IDispatch* pDisp = (IDispatch*)(CValue::siPtrType)dispVal;

		// create a CValue of type IUnknown
		IUnknown* pUnk = NULL;
		pDisp->QueryInterface( IID_IUnknown, (void**)&pUnk );

		CValue valUnk((CValue::siPtrType)pUnk);
		valUnk.ChangeType( CValue::siIUnknown );

		pDisp->Release();
		pUnk->Release();

	\endcode
	*/
	void ChangeType( CValue::DataType in_type, const CValue* in_pSrc = NULL );

	/*! Clear this CValue object */
	void Clear();

	/*! Attaches a CValue into this object. The object takes ownership of a CValue by encapsulating
	it. This function releases any existing encapsulated CValue, then copies the input CValue.
	\param in_valSrc CValue object to encapsulate.
	*/
	void Attach( CValue& in_valSrc);

	/*! Detaches the encapsulated CValue object from this CValue object. Extracts and returns the
	encapsulated CValue, then clears this CValue object without destroying it.
	\return The encapsulated CValue.
	*/
	CValue Detach();

	/*! Returns the CValue content into a text string.
	\return The value in text format.
	*/
	CString GetAsText() const;

	/*! Convenient method to know if the object is set with a value or not.
	\return true if the CValue is empty or false otherwise.
	*/
	inline bool IsEmpty() const;
};

inline bool CValue::operator== (short val) const
{
	return *this == CValue(val);
}

inline bool CValue::operator== (unsigned short val) const
{
	return *this == CValue(val);
}

inline bool CValue::operator== (LONG val) const
{
	return *this == CValue(val);
}

#if !defined(linux) || !defined(__x86_64)
inline bool CValue::operator== (int val) const
{
	return *this == CValue(val);
}
#endif

inline bool CValue::operator== (ULONG val) const
{
	return *this == CValue(val);
}

inline bool CValue::operator== (LLONG val) const
{
	return *this == CValue(val);
}

inline bool CValue::operator== (ULLONG val) const
{
	return *this == CValue(val);
}

inline bool CValue::operator== (float val) const
{
	return *this == CValue(val);
}

inline bool CValue::operator== (double val) const
{
	return *this == CValue(val);
}

inline bool CValue::operator== (bool val) const
{
	return *this == CValue(val);
}

inline bool CValue::operator== (const CString& val) const
{
	return *this == CValue(val);
}

inline bool CValue::operator== (const wchar_t* val) const
{
	return *this == CValue(val);
}

inline bool CValue::operator== (const char* val) const
{
	return *this == CValue(val);
}

inline bool CValue::operator== (const CRef& val) const
{
	return *this == CValue(val);
}

inline bool CValue::operator== (const CRefArray& val) const
{
	return *this == CValue(val);
}

inline bool CValue::operator== (unsigned char val) const
{
	return *this == CValue(val);
}

inline bool CValue::operator== (signed char val) const
{
	return *this == CValue(val);
}

inline bool CValue::operator== (const siPtrType val) const
{
	return *this == CValue(val);
}

inline bool CValue::operator== (const siBlobType& val) const
{
	return *this == CValue(val);
}

inline bool CValue::operator== (const MATH::CVector3& val) const
{
	return *this == CValue(val);
}

inline bool CValue::operator== (const MATH::CVector2f& val) const
{
	return *this == CValue(val);
}
inline bool CValue::operator== (const MATH::CVector3f& val) const
{
	return *this == CValue(val);
}
inline bool CValue::operator== (const MATH::CVector4f& val) const
{
	return *this == CValue(val);
}
inline bool CValue::operator== (const MATH::CQuaternionf& val) const
{
	return *this == CValue(val);
}
inline bool CValue::operator== (const MATH::CRotationf& val) const
{
	return *this == CValue(val);
}
inline bool CValue::operator== (const MATH::CMatrix3f& val) const
{
	return *this == CValue(val);
}
inline bool CValue::operator== (const MATH::CMatrix4f& val) const
{
	return *this == CValue(val);
}
inline bool CValue::operator== (const MATH::CColor4f& val) const
{
	return *this == CValue(val);
}

inline bool CValue::operator== (const MATH::CShape& val) const
{
	return *this == CValue(val);
}

inline bool CValue::operator== (const CStringArray& val) const
{
	return *this == CValue(val);
}

inline bool CValue::IsEmpty() const
{
	return m_t == siEmpty;
}

//*************************************************************************
/*! \class CValueArray xsi_value.h
	\brief The CValueArray is an uni-dimensional array of CValue.

	The array is zero-based, which means that the first item index is 0 and the larger index
	is one less that the number of elements contained in the array.

	\sa CValue, FCurve::SetKeys, Application::ExecuteCommand
*/
//*************************************************************************
class SICPPSDKDECL CValueArray
{
public:
	/*! Constructs a CValueArray and optionally initializes the array to a known size.
	\param in_size Size of array, defaults to 0.
	*/
	CValueArray(LONG in_size=0);

	/*! Constructs a CValueArray object from another CValueArray object.
	\param in_array constant CValueArray object.
	*/
	CValueArray(const CValueArray& in_array);

	/*! Default destructor. */
	~CValueArray();

	/*! Assignment operator.
	\param in_array constant class object.
	\return A reference to this array.
	*/
	CValueArray& operator=( const CValueArray& in_array );

	/*! Returns the number of items in this CValueArray
	\return The number of items in the array.
	*/
	LONG GetCount() const;

	/*! Adds a CValue at the end of this array's.
	\param in_item New item to be added at the end of the array.
	\return CStatus::OK success
	*/
	CStatus Add( const CValue& in_item );

	/*! Erases all elements contained in the array.
	\return CStatus::OK success
	*/
	CStatus Clear();

	/*! Reallocates memory for the array, preserves its contents if the new size is larger
	than existing size.
	\param in_size New size of the array.
	\return CStatus::OK success
	\return CStatus::InvalidArgument in_size < 0
	*/
	CStatus Resize( LONG in_size);

	/*! Accessor to elements at a given index. This function can only be called by constant
	objects, the returned value is read-only.
	\param in_index index in this zero-based array.  The index must be greater or equal to zero
		and smaller than the number of element in the array, otherwise the results are unpredictable.
	\return A read-only reference to the indexed item.
	*/
	const CValue& operator[]( LONG in_index ) const;

	/*! Accessor to elements at a given index.
	\param in_index index in this zero-based array.  The index must be greater or equal to zero
		and smaller than the number of element in the array, otherwise the results are unpredictable.
	\return A reference to the indexed item.
	*/
	CValue& operator[]( LONG in_index );

	/*! Equality operator.
	\param in_array CValueArray to compare with.
	\return true if in_array contains the same number of elements as this array and if all members
		of in_array are equal to the corresponding one contained in this array.
	*/
	bool operator==(const CValueArray& in_array) const;

	/*! Inequality
	\param in_array
	\return true if one member of in_array is different from the corresponding members in this
		array or if the arrays are not of the same size.
	*/
	bool operator!=(const CValueArray& in_array) const;


private:

	void* m_ptr;
};


};

#endif // __XSIVALUE_H__
