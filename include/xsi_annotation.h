//*****************************************************************************
/*!
	\file xsi_annotation.h
	\brief Annotation class declaration.
   
	Copyright 2011 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIANNOTATION_H__
#define __XSIANNOTATION_H__

#include <xsi_x3dobject.h>

namespace XSI {

//*****************************************************************************
/*! 
	\class Annotation xsi_annotation.h
	\brief The Annotation class is a specialized X3DObject used for inserting text annotation in a scene.
	\since 10.5 (2012)

	\eg How to add a simple text annotation to a model object.    
	\code
	XSI::Model mymodel = Application().GetActiveSceneRoot().AddModel("MyModel");
	Annotation annotation = mymodel.AddAnnotation("This model is annotated");
	Application().LogMessage( mymodel.GetName() + " is annotated with " + annotation.GetName() + ": " + CString(annotation.GetParameterValue( "Message" )), siComment );
	\endcode

	\sa X3DObject::AddAnnotation
 */
//*****************************************************************************

class SICPPSDKDECL Annotation : public X3DObject
{
	public:
	
	/*! Default constructor. */
	Annotation();
    
	/*! Default destructor. */
	~Annotation();
    
	/*! Constructor.
	\param in_ref constant reference object.
	*/
	Annotation(const CRef& in_ref);
    
	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	Annotation(const Annotation& in_obj);
    
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
	\return The new Annotation object.
	*/
	Annotation& operator=(const Annotation& in_obj);
    
	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new Annotation object.
	*/
	Annotation& operator=(const CRef& in_ref);

	/*! Returns the URL string from an annotation at a given view position. Returns an empty string if there is no URL found. This is typically used from a custom tool for invoking a URL embedded in an annotation.
	\param in_viewid The view ID to query. This is typically available from ToolContext::GetViewIndex.
	\param in_xcoord The view X coordinate for the query.
	\param in_ycoord The view Y coordinate for the query.
	\return The URL string.
	*/
	CString GetURLAt( LONG in_viewid, LONG in_xcoord, LONG in_ycoord ) const;

	private:
	Annotation * operator&() const;
	Annotation * operator&();
};

};

#endif

