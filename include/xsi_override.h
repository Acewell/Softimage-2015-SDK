//*****************************************************************************
/*!
   \file xsi_override.h
   \brief Override object class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIOVERRIDE_H__
#define __XSIOVERRIDE_H__

#include <xsi_property.h>
#include <xsi_status.h>

namespace XSI {

//*****************************************************************************
/*! \class Override xsi_override.h
	\brief This class represents an \xp Override override\endxp property. An override contains the
	parameters that are used for replacing an object's parameter with another value or a shader
	without removing the original object parameter.

	Parameters whose values are overriden by another parameter's value are called 'overridden parameters'
	and the parameters stored in the override property whose values are used to override an overriden
	parameter are called 'overriding parameters'.

	Override properties are created with SceneItem::AddProperty. You can get pointers to existing
	Override objects like any other property on an object:

	\code Override overrideProp = pointLight.GetProperties().GetItem(L"MyOverride"); \endcode

	\sa Parameter::GetOverridenObject, Parameter::GetOverridingObject, Parameter::GetOriginalValue
	\since 7.0

	\eg This example demonstrates how to create and access override parameters
	\code
		Application app;
		Model root = app.GetActiveSceneRoot();

		// Create a light object
		Light pointLight;
		root.AddLight( L"Point", false, L"PointLight", pointLight );

		pointLight.AddProperty( overridepreset, false, L"PointOverride" );
		Override overrideProp = pointLight.GetProperties().GetItem(L"PointOverride");
		Parameter posx = pointLight.GetKinematics().GetLocal().GetParameters().GetItem(L"posx");

		// Set the original (overridden) parameter value
		posx.PutValue( 5.0 );

		// Set the overriding value
		Parameter overridingPosx = overrideProp.AddParameterEntry( posx );
		SetValue( overridingPosx.GetFullName(), CValue(-4.0), CValue(0) );

		// Override the light shader color parameter
		Shader softLight = pointLight.GetShaders().GetItem( L"soft_light" );
		Parameter softLightColor = softLight.GetParameters().GetItem(L"Color");

		// Set the original value
		softLightColor.PutParameterValue( L"Red", 0.5 );
		softLightColor.PutParameterValue( L"Blue", 0.5 );

		// Set the overrding value
		Parameter overridingSoftLightColor = overrideProp.AddParameterEntry( softLightColor );
		SIApplyShaderToCnxPoint( L"Shaders\\Texture\\Color_Channels\\RGBA_combine.Preset",
			CValue(overridingSoftLightColor.GetFullName()) );


		// Log the overriding posx parameter values
		overridingPosx = overrideProp.GetParameterEntries().GetItem( L"posx" );
		Parameter overridenPosx = overridingPosx.GetOverridenObject();

		app.LogMessage( L"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" );
		app.LogMessage( L"Overriding posx: " + overridingPosx.GetFullName() );
		app.LogMessage( L"Overriding posx value: " + CString( overridingPosx.GetValue() ) );
		app.LogMessage( L"Overriding posx original value: " + CString( overridingPosx.GetOriginalValue() ) );
		app.LogMessage( L"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
		app.LogMessage( L"Overriden posx: " + overridenPosx.GetFullName() );
		app.LogMessage( L"Overriden posx value: " + CString( overridenPosx.GetValue() ) );
		app.LogMessage( L"Overriden posx original value: " + CString( overridenPosx.GetOriginalValue() ) );
		// INFO : * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		// INFO : Overriding posx: PointLight.PointOverride.posx
		// INFO : Overriding posx value: -4
		// INFO : Overriding posx original value: 5
		// INFO : * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		// INFO : Overriden posx: PointLight.kine.local.posx
		// INFO : Overriden posx value: -4
		// INFO : Overriden posx original value: 5


		// Log the overriding color parameter values
		Parameter overridingColor = overrideProp.GetParameterEntries().GetItem( L"light-soft_light-color" );
		Shader overridingColorSource = overridingColor.GetSource();
		MATH::CColor4f overridingColorOriginalValue = overridingColor.GetOriginalValue();

		app.LogMessage( L"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * ** ");
		app.LogMessage( L"Overriding color: " + overridingColorSource.GetFullName() );
		app.LogMessage( L"Overriding color value: " + CString( overridingColorSource.GetParameterValue( L"red" ) ) +L":"+ CString( overridingColorSource.GetParameterValue( L"green" ) )+L":"+ CString( overridingColorSource.GetParameterValue( L"blue" ) )+L":"+ CString( overridingColorSource.GetParameterValue( L"alpha" ) ) );
		app.LogMessage( L"Overriding color original value: " + CString( overridingColorOriginalValue.GetR( ) ) +L":"+ CString( overridingColorOriginalValue.GetG( ) )+L":"+ CString( overridingColorOriginalValue.GetB( ) )+L":"+ CString( overridingColorOriginalValue.GetA( ) ) );
		// INFO : * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
		// INFO : Overriding color: PointLight.PointOverride.RGBA_combine
		// INFO : Overriding color value: 1:1:1:1
		// INFO : Overriding color original value: 0.5:1:0.5:0


		Parameter overridenColor = overridingColor.GetOverridenObject();
		MATH::CColor4f overridenColorValue = overridenColor.GetValue();
		MATH::CColor4f overridenColorOriginalValue = overridenColor.GetOriginalValue();

		app.LogMessage( L"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
		app.LogMessage( L"Overriden color: " + overridenColor.GetFullName() );
		app.LogMessage( L"Overriden color value: " + CString( overridenColorValue.GetR( ) ) +L":"+ CString( overridenColorValue.GetG( ) )+L":"+ CString( overridenColorValue.GetB( ) )+L":"+ CString( overridenColorValue.GetA( ) ) );
		app.LogMessage( L"Overriden color original value: " + CString( overridenColorOriginalValue.GetR( ) ) +L":"+ CString( overridenColorOriginalValue.GetG( ) )+L":"+ CString( overridenColorOriginalValue.GetB( ) )+L":"+ CString( overridenColorOriginalValue.GetA( ) ) );
		// INFO : * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		// INFO : Overriden color: PointLight.light.soft_light.color
		// INFO : Overriden color value: 0.5:1:0.5:0
		// INFO : Overriden color original value: 0.5:1:0.5:0

		CValue SetValue( const CString& in_target, const CValue& in_value, const CValue&  in_time )
		{
			CValueArray args(3);
			CValue retval;

			args[0]= in_target;
			args[1]= in_value;
			args[2]= in_time;

			Application app;
			app.ExecuteCommand( L"SetValue", args, retval );

			return retval;
		}

		CValue SIApplyShaderToCnxPoint( const CValue& in_presetobj, const CValue& in_inputobjs )
		{
			CValueArray args(4);
			CValue retval;
			LONG i(0);

			args[i++]= in_presetobj;
			args[i++]= in_inputobjs;
			args[i++]= L"";
			args[i++]= true;

			Application app;
			app.ExecuteCommand( L"SIApplyShaderToCnxPoint", args, retval );

			return retval;
		}

	\endcode
 */
//*****************************************************************************

class SICPPSDKDECL Override : public Property
{
public:
	/*! Default constructor. */
	Override();

	/*! Default destructor. */
	~Override();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	Override(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	Override(const Override& in_obj);

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
	\return The new Override object.
	*/
	Override& operator=(const Override& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new Override object.
	*/
	Override& operator=(const CRef& in_ref);

	/*! Returns the overriding parameters of this override property.
	\return Array of overriding parameters.
	\eg This example demonstrates how to loop over override parameters
	\code
		Application app;
		Model root = app.GetActiveSceneRoot();

		// Create a light object
		Light pointLight;
		root.AddLight( L"Point", false, L"PointLight", pointLight );

		// Add entries to an override
		Override overrideProp = pointLight.AddProperty( L"Override", false, L"PointOverride" );
		Parameter posx = pointLight.GetKinematics().GetLocal().GetParameters().GetItem(L"posx");
		Parameter posy = pointLight.GetKinematics().GetLocal().GetParameters().GetItem(L"posy");
		Parameter posz = pointLight.GetKinematics().GetLocal().GetParameters().GetItem(L"posz");

		overrideProp.AddParameterEntry( posx );
		overrideProp.AddParameterEntry( posy );
		overrideProp.AddParameterEntry( posz );

		CParameterRefArray entries = overrideProp.GetParameterEntries();
		for (ULONG i = 0; i< entries.GetCount(); i++)
		{
			Parameter paramEntry(entries[i]);

			app.LogMessage( L"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" );
			app.LogMessage( L"Overriding: " + paramEntry.GetFullName() );
			app.LogMessage( L"Overriding value: " + CString( paramEntry.GetValue() ) );
		}

		// INFO : * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		// INFO : Overriding: PointLight.PointOverride.posx
		// INFO : Overriding value: 0
		// INFO : * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		// INFO : Overriding: PointLight.PointOverride.posy
		// INFO : Overriding value: 0
		// INFO : * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		// INFO : Overriding: PointLight.PointOverride.posz
		// INFO : Overriding value: 0

	\endcode
	*/
	CParameterRefArray GetParameterEntries() const;

	/*! Adds a new entry to override the input parameter and returns the new overriding parameter.
	\note Adding an entry to the override doesn't activate the override parameter automatically, you must first set its
	value with the \xl SetValue command. Parameter::PutValue will not activate the override parameter.
	\param in_param The parameter to override.
	\return The new overriding parameter.
	\return Empty CRef on failure.
	\sa Override::RemoveParameterEntry, Override::RemoveAllEntries

	\eg This example demonstrates how to add a parameter entry to an override
	\code
		Application app;
		Model root = app.GetActiveSceneRoot();

		// Create a light object
		Light pointLight;
		root.AddLight( L"Point", false, L"PointLight", pointLight );

		// Override the light posx parameter
		Override overrideProp = pointLight.AddProperty( L"Override", false, L"PointOverride" );
		Parameter posx = pointLight.GetKinematics().GetLocal().GetParameters().GetItem(L"posx");

		// Set the original value
		posx.PutValue( 5.0 );

		// Set the overriding value
		Parameter overridingPosx = overrideProp.AddParameterEntry( posx );
		SetValue( overridingPosx.GetFullName(), -4.0, 0 );

		// Log values
		app.LogMessage( L"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" );
		app.LogMessage( L"Overriding posx: " + overridingPosx.GetFullName() );
		app.LogMessage( L"Overriding posx value: " + CString( overridingPosx.GetValue() ) );
		app.LogMessage( L"Overriding posx original value: " + CString( overridingPosx.GetOriginalValue() ) );

		// INFO : * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		// INFO : Overriding posx: PointLight.PointOverride.posx
		// INFO : Overriding posx value: -4
		// INFO : Overriding posx original value: 5

		CValue SetValue( const CString& in_target, const CValue& in_value, const CValue&  in_time )
		{
			CValueArray args(3);
			CValue retval;

			args[0]= in_target;
			args[1]= in_value;
			args[2]= in_time;

			Application app;
			app.ExecuteCommand( L"SetValue", args, retval );

			return retval;
		}

	\endcode
	*/
	CRef AddParameterEntry( const Parameter& in_param );

	/*! Removes the entry corresponding to the input parameter object.
	\param in_param The parameter to remove. You can pass either the overriding Parameter that represents
		the entry or the overridden parameter.
	\return CStatus::OK Success
	\return CStatus::Fail Failure
	\sa Override::AddParameterEntry, Override::RemoveAllEntries
	\eg This example demonstrates how to remove an entry from an override.
	\code
		Application app;
		Model root = app.GetActiveSceneRoot();

		// Create a light object
		Light pointLight;
		root.AddLight( L"Point", false, L"PointLight", pointLight );

		// Override the light posx parameter
		Override overrideProp = pointLight.AddProperty( L"Override", false, L"PointOverride" );
		Parameter posx = pointLight.GetKinematics().GetLocal().GetParameters().GetItem(L"posx");
		overrideProp.AddParameterEntry( posx );

		// Override the light shader color parameter
		Shader softLight = pointLight.GetShaders().GetItem( L"soft_light" );
		Parameter softLightColor = softLight.GetParameters().GetItem(L"Color");
		Parameter overridingSoftLightColor = overrideProp.AddParameterEntry( softLightColor );
		SIApplyShaderToCnxPoint( L"Shaders\\Texture\\Color_Channels\\RGBA_combine.Preset", CValue(overridingSoftLightColor) );

		app.LogMessage( L"overrideProp.GetParameterEntries.Count: " + CString(overrideProp.GetParameterEntries().GetCount() ) );

		Parameter overridingParam = overrideProp.GetParameterEntries()[ 0 ];
		overrideProp.RemoveParameterEntry( overridingParam );

		app.LogMessage( L"overrideProp.GetParameterEntries.Count: " + CString(overrideProp.GetParameterEntries().GetCount() ) );

		// INFO : overrideProp.GetParameterEntries.Count: 2
		// INFO : overrideProp.GetParameterEntries.Count: 1

		CValue SIApplyShaderToCnxPoint( const CValue& in_presetobj, const CValue& in_inputobjs )
		{
			CValueArray args(4);
			CValue retval;
			LONG i(0);

			args[i++]= in_presetobj;
			args[i++]= in_inputobjs;
			args[i++]= L"";
			args[i++]= true;

			Application app;
			app.ExecuteCommand( L"SIApplyShaderToCnxPoint", args, retval );

			return retval;
		}

	\endcode
	*/
	CStatus RemoveParameterEntry( const Parameter& in_param );

	/*! Removes all entries from this override.
	\return CStatus::OK Success
	\return CStatus::Fail Failure
	\sa Override::RemoveParameterEntry, Override::AddParameterEntry
	\eg This example demonstrates how to remove all entries from an override.
	\code
		Application app;
		Model root = app.GetActiveSceneRoot();

		// Create a light object
		Light pointLight;
		root.AddLight( L"Point", false, L"PointLight", pointLight );

		// Override the light posx parameter
		Override overrideProp = pointLight.AddProperty( L"Override", false, L"PointOverride" );
		Parameter posx = pointLight.GetKinematics().GetLocal().GetParameters().GetItem(L"posx");
		overrideProp.AddParameterEntry( posx );

		// Override the light shader color parameter
		Shader softLight = pointLight.GetShaders().GetItem( L"soft_light" );
		Parameter softLightColor = softLight.GetParameters().GetItem(L"Color");
		Parameter overridingSoftLightColor = overrideProp.AddParameterEntry( softLightColor );
		SIApplyShaderToCnxPoint( L"Shaders\\Texture\\Color_Channels\\RGBA_combine.Preset", CValue(overridingSoftLightColor) );

		app.LogMessage( L"overrideProp.GetParameterEntries.Count: " + CString(overrideProp.GetParameterEntries().GetCount() ) );

		overrideProp.RemoveAllEntries( );

		app.LogMessage( L"overrideProp.GetParameterEntries.Count: " + CString(overrideProp.GetParameterEntries().GetCount() ) );

		// INFO : overrideProp.GetParameterEntries.Count: 2
		// INFO : overrideProp.GetParameterEntries.Count: 0

	\endcode
	*/
	CStatus RemoveAllEntries( );

	/*! Returns the list of shaders nested under this Override.
	\return CRefArray of references to the nested Shader objects.
	\since 7.0
	*/
	CRefArray	GetAllShaders() const;

	/*! Returns the list of image clips nested under this Override.
	\return CRefArray of references to the nested ImageClip2 objects.
	\sa Light::GetAllImageClips, Material::GetAllImageClips, Pass:GetAllImageClips,
		Shader::GetAllImageClips, Camera::GetAllImageClips
	\since 7.0
	*/
	CRefArray	GetAllImageClips() const;

	private:
	Override * operator&() const;
	Override * operator&();
};

};

#endif // __XSIOVERRIDE_H__
