//*****************************************************************************
/*!
   \file xsi_fcurvekey.h
   \brief FCurveKey class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIFCURVEKEY_H__
#define __XSIFCURVEKEY_H__

#include <xsi_siobject.h>
#include <xsi_value.h>
#include <xsi_time.h>

namespace XSI {

class CFCurveKeyRefArray;

//*****************************************************************************
/*! \class FCurveKey xsi_fcurvekey.h
	\brief This class represents a key on a function curve (FCurve).

	If one method returns CStatus::AccessDenied, this may due to different reasons:
	the function curve key is locked (see the FCurveKey::GetLocked method),
	the function curve key is constrained (see the FCurveKey::GetConstraint method) or
	the function curve key is part of a function curve used by a locked animation layer (see the IsAnimationLayerLocked command).

	\sa FCurve, FCurve::SetKeys, FCurve::GetKeys, \xt dev_FCurves About FCurves \endxt

	\eg
	\code
		using namespace XSI;
		Application app;
		Model root = app.GetActiveSceneRoot();

		Null myNull;
		root.AddNull( L"", myNull );
		Parameter posx(	myNull.GetParameter( L"posx" ) );

		// create and connect a function curve to the position x
		FCurve fcrv;
		posx.AddFCurve( siUnknownFCurve, fcrv );

		// set the keys
		LONG i = 0;
		CTimeArray timeArray(3);
		CValueArray valueArray(3);

		timeArray[i] = 1;	valueArray[i] = (double)10; i++;
		timeArray[i] = 50; 	valueArray[i] = (double)0; i++;
		timeArray[i] = 100; valueArray[i] = (double)10; i++;

		fcrv.SetKeys(timeArray,valueArray);

		// set the zero slopes on the key tangents
		CDoubleArray tangentsArray(12);
		i=0;
		tangentsArray[i++]=-10.5; tangentsArray[i++]=0; tangentsArray[i++]=10.5; tangentsArray[i++] = 0;
		tangentsArray[i++]=-10.5; tangentsArray[i++]=0; tangentsArray[i++]=10.5; tangentsArray[i++] = 0;
		tangentsArray[i++]=-10.5; tangentsArray[i++]=0; tangentsArray[i++]=10.5; tangentsArray[i++] = 0;

		fcrv.SetKeyTangents( tangentsArray );
	\endcode
*/
//*****************************************************************************

class SICPPSDKDECL FCurveKey : public SIObject
{
public:
	/*! Default constructor. */
	FCurveKey();

	/*! Default destructor. */
	~FCurveKey();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	FCurveKey(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	FCurveKey(const FCurveKey& in_obj);

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
	\return The new FCurveKey object.
	*/
	FCurveKey& operator=(const FCurveKey& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new FCurveKey object.
	*/
	FCurveKey& operator=(const CRef& in_ref);

	/*! Returns the value type of the function curve key.
	\return The type of the fcurve key's value.
	*/
	CValue::DataType 			GetValueType() const;

	/*! Returns the value of the function curve key.
	\return The fcurve key's value.
	*/
	CValue 						GetValue(void) const;

	/*! Sets the value of the function curve key.
	\param in_value Function curve key value
	\return CStatus::OK success
	\return CStatus::AccessDenied Access denied. See more information in the FCurveKey class description.
	\return CStatus::Fail failure
	*/
	CStatus						PutValue(const CValue& in_value);

	/*! Returns the key frame for the function curve key.
	\return The FCurveKey time.
	*/
	CTime	 					GetTime(void) const;

	/*! Sets the frame for the function curve key.
	\param in_time Function curve key frame
	\return CStatus::OK success
	\return CStatus::AccessDenied Access denied. See more information in the FCurveKey class description.
	\return CStatus::Fail failure
	*/
	CStatus						PutTime(const CTime& in_time);

	/*! Returns the locked state of the function curve key.
	\return True if the FCurveKey is locked; false otherwise.
	*/
	bool	 					GetLocked(void) const;

	/*! Sets the locked state of the function curve key.
	\param in_bFlag Function curve key locked state value.
	\return CStatus::OK success
	\return CStatus::AccessDenied Access denied. See more information in the FCurveKey class description.
	\return CStatus::Fail failure
	*/
	CStatus 					PutLocked(bool in_bFlag);

	/*! Returns the selected state of the function curve key.
	\return True if the FCurveKey is selected; false otherwise.
	\since 6.0
	*/
	bool	 					GetSelected(void) const;

	/*! Returns the left value of the function curve key.
	\return The FCurveKey left value.
	*/
	CValue	 					GetLeft() const;

	/*! Sets the left value of the function curve key.
	\param in_value New left value.
	\return CStatus::OK success
	\return CStatus::AccessDenied Access denied. See more information in the FCurveKey class description.
	\return CStatus::Fail failure
	*/
	CStatus 					PutLeft(const CValue& in_value);

	/*! Returns the right value of the function curve key.
	\return The FCurveKey right value.
	*/
	CValue	 					GetRight(void) const;

	/*! Sets the right value of the function curve key.
	\param in_value New right value.
	\return CStatus::OK success
	\return CStatus::AccessDenied Access denied. See more information in the FCurveKey class description.
	\return CStatus::Fail failure
	*/
	CStatus 					PutRight(const CValue& in_value);

	/*! Returns the left tangent Y value of the function curve key.
	\return The FCurveKey left tangent Y value.
	*/
	double	 					GetLeftTanY(void) const;

	/*! Sets the left tangent Y value of the function curve key.
	\param in_value New left tangent Y value.
	\return CStatus::OK success
	\return CStatus::AccessDenied Access denied. See more information in the FCurveKey class description.
	\return CStatus::Fail failure
	*/
	CStatus 					PutLeftTanY(double in_value);

	/*! Returns the right tangent Y value of the function curve key.
	\return The FCurveKey right tangent Y value.
	*/
	double	 					GetRightTanY(void) const;

	/*! Sets the right tangent Y value of the function curve key.
	\param in_value New right tangent Y value.
	\return CStatus::OK success
	\return CStatus::AccessDenied Access denied. See more information in the FCurveKey class description.
	\return CStatus::Fail failure
	*/
	CStatus 					PutRightTanY(double in_value);

	/*! Returns the left tangent key of the function curve key.
	\return The FCurveKey left tangent X value.
	*/
	CTime	 					GetLeftTanX(void) const;

	/*! Sets the left tangent X value of the function curve key.
	\param in_value new left tangent X value.
	\return CStatus::OK success
	\return CStatus::AccessDenied Access denied. See more information in the FCurveKey class description.
	\return CStatus::Fail failure
	*/
	CStatus 					PutLeftTanX(const CTime& in_value);

	/*! Returns the right tangent key of the function curve key.
	\return The FCurveKey right tangent X value.
	*/
	CTime	 					GetRightTanX(void) const;

	/*! Sets the right tangent X value of the function curve key.
	\param in_value new right tangent X value.
	\return CStatus::OK success
	\return CStatus::AccessDenied Access denied. See more information in the FCurveKey class description.
	\return CStatus::Fail failure
	*/
	CStatus 					PutRightTanX(const CTime& in_value);

	/*! Returns the interpolation type of the function curve key.
	\return The FCurveKey interpolation type.
	\sa \xt dev_animation_FCurveInterpolationAndExtrapolation FCurve Interpolation and Extrapolation \endxt
	*/
	siFCurveKeyInterpolation 	GetInterpolation(void) const;

	/*! Sets the interpolation for the function curve key.
	\param in_value New interpolation
	\return CStatus::OK success
	\return CStatus::AccessDenied Access denied. See more information in the FCurveKey class description.
	\return CStatus::Fail failure
	\sa \xt dev_animation_FCurveInterpolationAndExtrapolation FCurve Interpolation and Extrapolation \endxt
	*/
	CStatus 					PutInterpolation(siFCurveKeyInterpolation in_value);

	/*! Returns true if the specified constraint is turned on.
	\param in_eKC Type of constraint to query (one of the ::siFCurveKeyConstraint values).
	\return true if the specified constraint is turned on.
	*/
	bool GetConstraint(siFCurveKeyConstraint in_eKC) const;

	/*! Sets the constraint for the function curve key.
	\param in_eKC Type of constraint to set (one of the ::siFCurveKeyConstraint values).
	\param in_bSet True to turn constraint on.
	\return CStatus::OK success
	\return CStatus::AccessDenied Access denied. See more information in the FCurveKey class description.
	\return CStatus::Fail failure
	*/
	CStatus PutConstraint(siFCurveKeyConstraint in_eKC, bool in_bSet );

	/*! Sets the function curve key's frame and value.
	\param in_frame New key frame.
	\param in_value New key value.
	\param in_overridekeylock True to override key lock.
	\return CStatus::OK success
	\return CStatus::AccessDenied Access denied. See more information in the FCurveKey class description.
	\return CStatus::Fail failure
	*/
	CStatus Set( const CTime& in_frame, const CValue& in_value, bool in_overridekeylock=false );

	/*! Returns the index of this key in the function curve.
	\return The key index
	\since 6.0
	*/
	LONG GetIndex(void) const;

private:
	FCurveKey * operator&() const;
	FCurveKey * operator&();
    friend void * FCurveKeyPtr(const FCurveKey &);
};

//*****************************************************************************
/*! \class CFCurveKeyRefArray xsi_fcurvekey.h
	\brief This class represents an array of keys on a function curve (FCurve). Duplicate keys are not allowed
	and a single array can only hold keys from the same fcurve.
	\sa CRefArray, FCurveKeys, FCurve::GetKeys, FCurve::GetKeysBetween
	\since 6.0

	\eg This example demonstrates how to get a list of references to all keys in an FCurve
	\code
		using namespace XSI;
		Application app;
		Model root = app.GetActiveSceneRoot();

		Null myNull;
		root.AddNull( L"", myNull );
		Parameter posx(	myNull.GetParameter( L"posx" ) );

		// Create and connect a function curve to the position x
		FCurve fcrv;
		posx.AddFCurve( siUnknownFCurve, fcrv );

		// Set the keys
		LONG i = 0;
		CTimeArray timeArray(3);
		CValueArray valueArray(3);

		timeArray[i] = 1;	valueArray[i] = (double)10; i++;
		timeArray[i] = 50; 	valueArray[i] = (double)0; i++;
		timeArray[i] = 100; valueArray[i] = (double)10; i++;

		fcrv.SetKeys(timeArray,valueArray);

		// Get the keys
		CFCurveKeyRefArray keys = fcrv.GetKeys();
	\endcode
*/
//*****************************************************************************
class SICPPSDKDECL CFCurveKeyRefArray : public CRefArray
{
public:

	/*! Default constructor. */
	CFCurveKeyRefArray();

	/*! Copy constructor.  Performs a shallow copy, so any change
	to one instance will appear in any of the copies.
	*/
	CFCurveKeyRefArray( const CFCurveKeyRefArray& );

	/*! Default destructor. */
	~CFCurveKeyRefArray();

	/*! Assigns a CFCurveKeyRefArray object to this one.
	\param in_refArray A constant CFCurveKeyRefArray object.
	\return A new reference array.
	\since 6.0
	*/
	CFCurveKeyRefArray& operator=( const CFCurveKeyRefArray& in_refArray );

	/*! Adds a CFCurveKeyRefArray object to this one.
	\param in_refArray A constant CFCurveKeyRefArray object.
	\return A new reference object.
	*/
	CFCurveKeyRefArray& operator+=( const CFCurveKeyRefArray& in_refArray );

	/*! Adds another FCurveKey to this array. The item will be added only if it is not already in the
	array and it belongs to the same FCurve as existing keys. CFCurveKeyRefArray will add keys to the
	array so that the array is sorted by frame time.
	\param in_item The reference to an FCurveKey to be added.
	\since 6.0
	*/
	virtual void Add( const CRef& in_item );

	/*! Adds the keys from another CFCurveKeyRefArray into this array. The keys will be added to this
	array only if they are not already in the array and they belong to the same FCurve as existing keys.

	Keys will be added to the array sorted by frame time.

	\param in_keys Array of references to FCurveKey objects to add
	\since 6.0
	*/
	void AddItems( const CFCurveKeyRefArray& in_keys );

	/*! Removes an item from the specified location in the array.
	\param in_index Index of item to remove
	\since 6.0
	*/
	void RemoveAt( LONG in_index );

	/*! Returns the smallest key time in the CFCurveKeyRefArray.
	\return Minimum key time
	\return CStatus::Fail If the array has no keys
	\since 6.0
	*/
	CTime GetMinKeyFrame(void) const;

	/*! Returns the average of the first and last key times in the array.
	\return Center key time
	\return CStatus::Fail If the array has no keys
	\since 6.0
	*/
	CTime GetMidKeyFrame(void) const;

	/*! Returns the largest key time in the array.
	\return Maximum key time
	\return CStatus::Fail If the array has no keys
	\since 6.0
	*/
	CTime GetMaxKeyFrame(void) const;

	/*! Returns the smallest key value in the array.
	\return Minimum key value
	\return CStatus::Fail If the array has no keys
	\since 6.0
	*/
	CValue GetMinKeyValue(void) const;

	/*! Returns the average of the largest and smallest key values in the array.
	\return Center key value
	\return CStatus::Fail If the array has no keys
	\since 6.0
	*/
	CValue GetMidKeyValue(void) const;

	/*! Returns the largest key value in the array.
	\return Maximum key value
	\return CStatus::Fail If the array has no keys
	\since 6.0
	*/
	CValue GetMaxKeyValue(void) const;
};

}; // namespace XSI

#endif // __XSIFCURVEKEY_H__
