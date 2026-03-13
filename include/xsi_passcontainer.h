//*****************************************************************************
/*!
   \file xsi_passcontainer.h
   \brief PassContainer class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSI_PASSCONTAINER_H__
#define __XSI_PASSCONTAINER_H__

#include <xsi_projectitem.h>
#include <xsi_customproperty.h>
#include <xsi_status.h>

namespace XSI {

class Pass;
class Property;

//*****************************************************************************
/*! \class PassContainer xsi_passcontainer.h
	\brief The PassContainer object represents the pass container object found in the
	scene. The pass container holds all the render passes in the scene, the global
	render options and individual render options for all installed rendering engines.
	\sa Pass
	\since 6.0
 */
//*****************************************************************************

class SICPPSDKDECL PassContainer : public ProjectItem
{
public:
	/*! Default constructor. */
	PassContainer();

	/*! Default destructor. */
	~PassContainer();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	PassContainer(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	PassContainer(const PassContainer& in_obj);

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
	\return The new PassContainer object.
	*/
	PassContainer& operator=(const PassContainer& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new PassContainer object.
	*/
	PassContainer& operator=(const CRef& in_ref);

	/*! Returns all passes associated with the scene.
	\return An array of references to the Pass objects.
	\sa Scene::GetActivePass PassContainer::AddPass Scene::GetPasses Scene::GetPassContainer
	\sa Pass \xl GetCurrentPass \xl CreatePass \xl DeleteCurrentPass
	*/
	CRefArray 	GetPasses() const;

	/*! Returns all applied properties on the pass container.
	\note All properties on the PassContainer are local properties, since it doesn't inherit any.
		Hence there is no corresponding GetLocalProperties member function for the PassContainer class.
	\return Array of references to Property objects.
	*/
	CRefArray 	GetProperties() const;

	/*! Creates and adds a new Pass to the scene.
	\param in_preset Name of a \xt PassPresets pass preset \endxt to apply to the new pass.
		The pass preset is optional. If no pass preset is supplied then a default, empty pass
		is created and added.
	\param in_name	 The name of the new Pass object.
	\return The new Pass object.
	\sa Scene::GetActivePass Scene::GetPassContainer Pass PassContainer
	\sa \xl GetCurrentPass \xl CreatePass \xl DeleteCurrentPass
	*/
	Pass AddPass
	(
		const CString&	in_preset,
		const CString&	in_name
	);

	/*! Creates and adds a property to a PassContainer object.
	\param in_preset This argument contains the filename or full path to a Preset file (see the
		\xt PassPresets list of available pass presets \endxt ). The type of property that is created is
		determined by this argument. For example \c "CustomProperty" creates an empty CustomProperty and
		\c "UserDataMap" creates a UserDataMap. Is is also possible to specify the name of a CustomProperty
		that is installed as a PluginItem.
	\param in_bBranch True to apply property in branch; false to apply it on the node of the pass container.
	\param in_name	 The name of the new Property object (see SIObject::GetName). If not specified
		the name is derived from the \c in_preset argument.
	\return The new Property object.
	\sa PassContainer::AddCustomProperty, PassContainer::GetProperties, CustomProperty, UserDataMap,
		UserDataBlob, PluginRegistrar::RegisterProperty
	*/
	Property AddProperty
	(
		const CString&	in_preset,
		bool			in_bBranch = false,
		const CString&	in_name = CString()
	);

	/*! Creates and adds an empty CustomProperty to a PassContainer object.
	\param in_name	 Represents the name of the new CustomProperty object.
	\param in_bBranch True to apply property in branch; false to apply it on the node of the pass container.
	\retval out_customprop   Returns the new property.
	\return CStatus::OK success
	\return CStatus::Fail other failure
	\sa PassContainer::AddProperty CustomProperty
	*/
	CStatus 	AddCustomProperty
	(
		const CString&	in_name,
		bool			in_bBranch ,
		CustomProperty&	out_customprop
	);

	private:
	PassContainer * operator&() const;
	PassContainer * operator&();
};

};

#endif // __XSI_PASSCONTAINER_H__
