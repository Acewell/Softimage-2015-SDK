//*****************************************************************************
/*!
   \file xsi_uiobject.h
   \brief UIObject class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIUIOBJECT_H__
#define __XSIUIOBJECT_H__

#include <xsi_siobject.h>
#include <xsi_value.h>
#include <xsi_status.h>

namespace XSI {

class View;

//*****************************************************************************
/*! \class UIObject xsi_uiobject.h
	\brief The UIObject is the base class for Softimage UI objects such as UIPersistable and
	MenuItem. This class has no specific functions.

	\sa UIPersistable, MenuItem
	\since 4.0
*/
//*****************************************************************************

class SICPPSDKDECL UIObject : public SIObject
{
public:
	/*! Default constructor. */
	UIObject();

	/*! Default destructor. */
	~UIObject();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	UIObject(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	UIObject(const UIObject& in_obj);

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
	\return The new UIObject object.
	*/
	UIObject& operator=(const UIObject& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new UIObject object.
	*/
	UIObject& operator=(const CRef& in_ref);

	private:
	UIObject * operator&() const;
	UIObject * operator&();
};

};
#endif // __XSIUIOBJECT_H__
