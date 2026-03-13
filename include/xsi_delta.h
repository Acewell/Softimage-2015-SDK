//*****************************************************************************
/*!	\file xsi_delta.h
	\brief Delta class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIDELTA_H__
#define __XSIDELTA_H__

#include <xsi_projectitem.h>

namespace XSI {

class ActionDelta;

//*****************************************************************************
/*! \class Delta xsi_delta.h
	\brief The Delta object represents a 'diff' or list of modifications to a reference model.

	These are grouped into types of changes called ActionDelta objects, which have a unique type
	similar to the Parameter::GetSource type (see ::siModificationDeltaType) and changes to Overrides
	(which are stored in a parameter called 'PropertiesAddedToRefModel' under the %Delta property), etc.

	Modifications stored in an override are used to save static modifications, such as a new material.

	Modifications stored in an ActionDelta are related to animation, such as FCurves, Constraints, etc.

	Delta properties are stored under the model and each model can only have one delta associated to it,
	so to access a delta, use the SIObject::GetNestedObjects on the model. When the user makes a change
	to a value or source on a parameter in a reference model, a new %Delta is automatically created
	containing an ActionDelta with the ActionDeltaItem to store the change.

	To create a new delta you can use the \xl %AddDelta command. You can also import a delta using the
	\xl %ImportDelta or \xl %ImportReferencedDelta commands.

	\since 6.0
	\eg Illustrates how to assign a new value to an ActionDeltaItem
	\code
		using namespace XSI;

		Application app;

		// NewScene command
		CValueArray cargs; CValue oarg;
		cargs.Add( L"" ); cargs.Add( false );
		app.ExecuteCommand( L"NewScene", cargs, oarg );
		cargs.Clear();

		//Add cube geometry and create the reference model
		Model root = app.GetActiveSceneRoot();
		X3DObject myCube, myCone;
		root.AddGeometry( L"Cube", L"MeshSurface",L"",myCube);

		// CreateModelAndConvertToRef command
		CString strFactPath = app.GetInstallationPath(siProjectPath) ;
			strFactPath += L"/Models/MyModel.emdl";
		cargs.Add( myCube.GetFullName() ); cargs.Add( strFactPath );
		app.ExecuteCommand( L"CreateModelAndConvertToRef", cargs, oarg );
		cargs.Clear();

		Delta myDelta;

		// AddDelta command
		cargs.Add( L"Model" );
		app.ExecuteCommand( L"AddDelta", cargs, oarg );
		cargs.Clear();
		myDelta = oarg;

		// Translate command
		cargs.Add(myCube.GetFullName()); cargs.Add(2.0); cargs.Add(1.3); cargs.Add(0.0);
		cargs.Add(L"siRelative"); cargs.Add(L"siView"); cargs.Add(L"siObj"); cargs.Add(L"siXYZ");
		app.ExecuteCommand( L"Translate", cargs, oarg );
		cargs.Clear();

		ActionDelta ActionDelta0 = myDelta.GetActionDeltas().GetItem(0);
		CRefArray ActionDeltaItems = ActionDelta0.GetItems();
		CString strmgs;
		for ( LONG i=0; i<ActionDeltaItems.GetCount(); ++i ) {

			ActionDeltaItem item = ActionDeltaItems[i];

			// Print info about the current ActionDeltaItem
			strmgs = L"ActionSourceItem["; strmgs += CValue(i).GetAsText(); strmgs += L"]";
			Application().LogMessage(strmgs);
			strmgs = L"Name: "; strmgs += item.GetName();
			Application().LogMessage(strmgs);
			strmgs = L"Type: "; strmgs += item.GetType();
			Application().LogMessage(strmgs);

			//Print the current value
			strmgs = L"Initiale Value: "; strmgs += item.GetValue();
			Application().LogMessage(strmgs);

			// Change the value of the item
			item.PutValue ( 1.2 * i );

			//Print the new value
			strmgs = L"New value: "; strmgs += item.GetValue();
			Application().LogMessage(strmgs);
		}
		// File to save delta
		CString deltaFile = app.GetInstallationPath(siProjectPath) + L"/Deltas/MyDelta.delta";
		myDelta.Save (deltaFile );

	\endcode

 */
//*****************************************************************************
class SICPPSDKDECL Delta : public ProjectItem
{
public:
	/*! Default constructor. */
	Delta();

	/*! Default destructor. */
	~Delta();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	Delta(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	Delta(const Delta& in_obj);

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
	\return The new Delta object.
	*/
	Delta& operator=(const Delta& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new Delta object.
	*/
	Delta& operator=(const CRef& in_ref);

	/*! Saves the %Delta (all modifications on the reference model) to the specified
	file. This file can be used later as external storage or when importing a delta.
	\param in_FileName The filename to save.
	\return CStatus::OK success
	\return CStatus::Fail is returned in case of failure
	\eg See Delta main example for an example of how to use this function.
	*/
	CStatus Save( const CString& in_FileName );

	/*! Loads a %Delta (all modifications on the reference model) from the specified file.
	\param in_FileName The name of the file to load.
	\return CStatus::OK success
	\return CStatus::Fail is returned in case of failure
	\eg This example demonstrates how to load a delta. Be sure to have a delta saved in
		Application.InstallationPath( siProjectPath) + "/Deltas/MyDelta.delta"
		( you can run the main %Delta example to do so ).
	\code
		using namespace XSI;
		Application app;

		// NewScene command
		CValueArray cargs; CValue oarg;
		cargs.Add( L"" ); cargs.Add( false );
		app.ExecuteCommand( L"NewScene", cargs, oarg );
		cargs.Clear();

		//Add cube geometry and create the reference model
		Model root = app.GetActiveSceneRoot();
		X3DObject myCube;
		root.AddGeometry( L"Cube", L"MeshSurface",L"",myCube);

		// CreateModelAndConvertToRef command
		CString strFactPath = app.GetInstallationPath(siProjectPath) ;
			strFactPath += L"/Models/MyModel.emdl";
		cargs.Add( myCube.GetFullName() ); cargs.Add( strFactPath );
		app.ExecuteCommand( L"CreateModelAndConvertToRef", cargs, oarg );
		cargs.Clear();

		Delta myDelta;

		// AddDelta command
		cargs.Add( L"Model" );
		app.ExecuteCommand( L"AddDelta", cargs, oarg );
		cargs.Clear();
		myDelta = oarg;

		// Add an action of type siModificationDeltaStaticValue
		ActionDelta myDeltaAction = myDelta.AddAction(siModificationDeltaStaticValue);

		// Add the Static value item
		ActionDeltaItem myActionDeltaItem = myDeltaAction.AddStaticValueItem ( myCube.GetFullName()
				+ L".kine.global.posx", 10.0);

		// ApplyShader command
		cargs.Add( CValue() ); cargs.Add( L"" );
		cargs.Add( CValue() ); cargs.Add( L"" ); cargs.Add( siLetLocalMaterialsOverlap );
		app.ExecuteCommand( L"ApplyShader", cargs, oarg );
		cargs.Clear();

		// File to load delta from
		CString deltaFile = app.GetInstallationPath(siProjectPath) + L"/Deltas/MyDelta.delta";
		myDelta.Load (deltaFile );
	\endcode
	*/
	CStatus Load( const CString& in_FileName );

	/*! Applies the %Delta to a reference model. Use this function when you add modifications
	to a delta (for example, using ActionDelta::AddFCurveItem) and you want to apply those
	changes back to the reference model.
	\return CStatus::OK success
	\return CStatus::Fail is returned in case of failure
	\eg See Delta::AddAction for an example of how to use this function.
	*/
	CStatus Apply()const;

	/*! Adds the specified ActionDelta to this %Delta.
	\note Only one ActionDelta for each type is permitted on the %Delta.
		If you try to add an ActionDelta type that already exists, it
		returns an error with the message "ERROR : 'siModificationDelta' is undefined".
	\param in_type The modification type (::siModificationDeltaType)
	\return A reference to the new ActionDelta
	\eg This example demonstrates how to add an ActionDelta to a Delta.
	\code
		using namespace XSI;
		Application app;

		// NewScene command
		CValueArray cargs; CValue oarg;
		cargs.Add( L"" ); cargs.Add( false );
		app.ExecuteCommand( L"NewScene", cargs, oarg );
		cargs.Clear();

		//Add cube geometry and create the reference model
		Model root = app.GetActiveSceneRoot();
		X3DObject myCube;
		root.AddGeometry( L"Cube", L"MeshSurface",L"",myCube);

		// CreateModelAndConvertToRef command
		CString strFactPath = app.GetInstallationPath(siProjectPath) ;
			strFactPath += L"/Models/MyModel.emdl";
		cargs.Add( myCube.GetFullName() ); cargs.Add( strFactPath );
		app.ExecuteCommand( L"CreateModelAndConvertToRef", cargs, oarg );
		cargs.Clear();

		Delta myDelta;

		// AddDelta command
		cargs.Add( L"Model" );
		app.ExecuteCommand( L"AddDelta", cargs, oarg );
		cargs.Clear();
		myDelta = oarg;

		// Add an action of type siModificationDeltaStaticValue
		ActionDelta myDeltaAction = myDelta.AddAction(siModificationDeltaStaticValue);

		// Add the Static value item
		ActionDeltaItem myActionDeltaItem = myDeltaAction.AddStaticValueItem ( myCube.GetFullName()
				+ L".kine.global.posx",  10.0);

		// To apply the modification
		myDelta.Apply();

	\endcode
	*/
	ActionDelta AddAction( siModificationDeltaType in_type );

	/*! Removes the specified ActionDelta from the %Delta.
	\param in_type The modification type (::siModificationDeltaType)
	\return CStatus::OK success
	\return CStatus::Fail is returned in case of failure
	\eg See Delta::RemoveOverride for an example of how to use this function.
	*/
 	CStatus RemoveAction( siModificationDeltaType in_type );

	/*! Adds an override to the Delta based on the specified preset.
	\deprecated 6.5. This method is obsolete and is maintained for informational purposes only. Use AddAction instead.
	\note If there already an override in the delta, remove it before running this method.
	\param in_Preset Filename of preset
	\return CStatus::OK success
	\return CStatus::Fail is returned in case of failure
  	\eg Illustrates how to add an override property from a preset
	\code
		using namespace XSI;

		// Forward declaration
		void CreateOverridePreset ( const CString &in_presetFile, Application &in_App );

		Application app;

		// NewScene command
		CValueArray cargs; CValue oarg;
		cargs.Add( L"" ); cargs.Add( false );
		app.ExecuteCommand( L"NewScene", cargs, oarg );
		cargs.Clear();

		// Preset file path
		CString presetFile = app.GetInstallationPath( siUserPath) +
						L"/Data/DSPresets/Properties/Override.Preset";

		// Create and save an override preset
		CreateOverridePreset(presetFile, app);

		//Add cube geometry and create the reference model
		Model root = app.GetActiveSceneRoot();
		X3DObject myCube, myCone;
		root.AddGeometry( L"Cube", L"MeshSurface",L"",myCube);

		// CreateModelAndConvertToRef command
		CString strFactPath = app.GetInstallationPath(siProjectPath) ;
			strFactPath += L"/Models/MyModel.emdl";
		cargs.Add( myCube.GetFullName() ); cargs.Add( strFactPath );
		app.ExecuteCommand( L"CreateModelAndConvertToRef", cargs, oarg );
		cargs.Clear();

		Delta myDelta;

		// AddDelta command
		cargs.Add( L"Model" );
		app.ExecuteCommand( L"AddDelta", cargs, oarg );
		cargs.Clear();

		// Add the override from preset
		myDelta = oarg;
		myDelta.AddOverrideFromPreset ( presetFile );

		//This function create the preset that is going to be add to the Delta
		void CreateOverridePreset ( const CString &in_presetFile, Application &in_App )
		{
			Model root = in_App.GetActiveSceneRoot();

			X3DObject myCube;
			root.AddGeometry( L"Cube", L"MeshSurface",L"",myCube);

			// CreateModelAndConvertToRef command
			CString strFactPath = in_App.GetInstallationPath(siProjectPath) ;
				strFactPath += L"/Models/MyModel.emdl";
			CValueArray cargs; CValue oarg;
			cargs.Add( myCube.GetFullName() ); cargs.Add( strFactPath );
			in_App.ExecuteCommand( L"CreateModelAndConvertToRef", cargs, oarg );
			cargs.Clear();

			// AddProp command
			cargs.Add( L"Synoptic Property" );
			cargs.Add( myCube.GetFullName() ); cargs.Add( L"" );
			in_App.ExecuteCommand( L"AddProp", cargs, oarg );
			cargs.Clear();

			// SetValue command
			cargs.Add( myCube.GetFullName() + L".Synoptic_Property.displayname"); cargs.Add( L"TestName" );
			in_App.ExecuteCommand( L"SetValue", cargs, oarg );
			cargs.Clear();

			// SavePreset command
			cargs.Add( L"Model.Delta.PropertiesAddedToRefModel" );
			cargs.Add( in_presetFile );
			in_App.ExecuteCommand( L"SavePreset", cargs, oarg );
			cargs.Clear();

			// NewScene command
			cargs.Add( L"" ); cargs.Add( false );
			in_App.ExecuteCommand( L"NewScene", cargs, oarg );
			cargs.Clear();

		}
	\endcode
	*/
	CStatus AddOverrideFromPreset( const CString& in_Preset );

	/*! Removes the stored override from the %Delta. Only one override is stored
	with each %Delta inside a property called "PropertiesAddedToRefModel".
	\deprecated 6.5. This method is obsolete and is maintained for informational purposes only. Use RemoveAction instead.
	\return CStatus::OK success
	\return CStatus::Fail is returned in case of failure
	\eg Illustrates how to remove override and action from the Delta.
	\code
		using namespace XSI;

		Application app;

		// NewScene command
		CValueArray cargs; CValue oarg;
		cargs.Add( L"" ); cargs.Add( false );
		app.ExecuteCommand( L"NewScene", cargs, oarg );
		cargs.Clear();

		//Add cube geometry and create the reference model
		Model root = app.GetActiveSceneRoot();
		X3DObject myCube;
		root.AddGeometry( L"Cube", L"MeshSurface",L"",myCube);

		// CreateModelAndConvertToRef command
		CString strFactPath = app.GetInstallationPath(siProjectPath) ;
			strFactPath += L"/Models/MyModel.emdl";
		cargs.Add( myCube.GetFullName() ); cargs.Add( strFactPath );
		app.ExecuteCommand( L"CreateModelAndConvertToRef", cargs, oarg );
		cargs.Clear();

		Delta myDelta;

		// AddDelta command
		cargs.Add( L"Model" );
		app.ExecuteCommand( L"AddDelta", cargs, oarg );
		cargs.Clear();
		myDelta = oarg;

		// Add an action of type siModificationDeltaStaticValue
		ActionDelta myDeltaAction = myDelta.AddAction(siModificationDeltaStaticValue);

		// Add the Static value item
		ActionDeltaItem myActionDeltaItem = myDeltaAction.AddStaticValueItem ( myCube.GetFullName()
				+ L".kine.global.posx",  10.0);

		// AddProp command
		cargs.Add( L"Synoptic Property" );
		cargs.Add( myCube.GetFullName() ); cargs.Add( L"" );
		in_App.ExecuteCommand( L"AddProp", cargs, oarg );
		cargs.Clear();

		myDelta.RemoveOverride();
		myDelta.RemoveAction(siModificationDeltaStaticValue);


		// UpdateReferencedModel command
		cargs.Add( L"Model" );
		app.ExecuteCommand( L"UpdateReferencedModel", cargs, oarg );
		cargs.Clear();
		myDelta = oarg;

	\endcode
	*/
	CStatus RemoveOverride();

	/*! Returns the name of the reference model associated to this %Delta.
	\return The target reference model name.
	\eg See Delta::PutTarget for an example of how to use the GetTarget function.
	*/
	CString GetTarget()const;

	/*! Sets the name of the reference model associated to this %Delta.
	\param in_Target The name of the target reference model.
	\return CStatus::OK success
	\return CStatus::Fail is returned in case of failure
  	\eg Illustrates how to change the target reference model
	\code
		using namespace XSI;
		Application app;

		// NewScene command
		CValueArray cargs; CValue oarg;
		cargs.Add( L"" ); cargs.Add( false );
		app.ExecuteCommand( L"NewScene", cargs, oarg );
		cargs.Clear();

		//Add cube geometry and create the reference model
		Model root = app.GetActiveSceneRoot();
		X3DObject myCube, myCone;
		root.AddGeometry( L"Cube", L"MeshSurface",L"Proxy3DObj",myCube);

		// CreateModelAndConvertToRef command
		CString strFactPath = app.GetInstallationPath(siProjectPath) ;
			strFactPath += L"/Models/MyModel.emdl";
		cargs.Add( myCube.GetFullName() ); cargs.Add( strFactPath );
		app.ExecuteCommand( L"CreateModelAndConvertToRef", cargs, oarg );
		cargs.Clear();

		//Create a second reference model with the cone
		root.AddGeometry( L"Cone", L"MeshSurface",L"Proxy3DObj",myCone);
		// CreateModelAndConvertToRef command
		CString strFactPath1 = app.GetInstallationPath(siProjectPath) ;
			strFactPath1 += L"/Models/MyModel1.emdl";
		app.LogMessage(strFactPath1);
		cargs.Add( myCone.GetFullName() ); cargs.Add( strFactPath1 );
		app.ExecuteCommand( L"CreateModelAndConvertToRef", cargs, oarg );
		cargs.Clear();

		Delta myDelta;

		// AddDelta command
		cargs.Add( L"Model" );
		app.ExecuteCommand( L"AddDelta", cargs, oarg );
		cargs.Clear();
		myDelta = oarg;

		// Add an action of type siModificationDeltaStaticValue
		ActionDelta myDeltaAction = myDelta.AddAction(siModificationDeltaStaticValue);

		// Add the Static value item
		ActionDeltaItem myActionDeltaItem = myDeltaAction.AddStaticValueItem ( myCube.GetFullName()
				+ L".kine.global.posx", 10.0);

		// Change the target reference model
		myDelta.PutTarget( myCone.GetModel().GetName() );

		// UpdateReferencedModel command
		cargs.Add( L"Model" );
		app.ExecuteCommand( L"UpdateReferencedModel", cargs, oarg );
		cargs.Clear();
		myDelta = oarg;

	\endcode
	*/
	CStatus PutTarget( const CString& in_Target );

	/*! Returns a boolean value indicating whether the Delta is muted or not.
	\return True if the delta is muted; false if it is active
	\eg See Delta::PutMute for an example of how to use the GetMute function.
	*/
	bool GetMute()const;

	/*! Sets a boolean value indicating whether the Delta is muted or not.
	\param in_Mute True to mute the delta; false to make it active
	\return CStatus::OK success
	\return CStatus::Fail is returned in case of failure
  	\eg Illustrates how to mute a Delta
	\code
		using namespace XSI;
		Application app;

		// NewScene command
		CValueArray cargs; CValue oarg;
		cargs.Add( L"" ); cargs.Add( false );
		app.ExecuteCommand( L"NewScene", cargs, oarg );
		cargs.Clear();

		//Add cube geometry and create the reference model
		Model root = app.GetActiveSceneRoot();
		X3DObject myCube, myCone;
		root.AddGeometry( L"Cube", L"MeshSurface",L"",myCube);

		// CreateModelAndConvertToRef command
		CString strFactPath = app.GetInstallationPath(siProjectPath) ;
			strFactPath += L"/Models/MyModel.emdl";
		cargs.Add( myCube.GetFullName() ); cargs.Add( strFactPath );
		app.ExecuteCommand( L"CreateModelAndConvertToRef", cargs, oarg );
		cargs.Clear();

		Delta myDelta;

		// AddDelta command
		cargs.Add( L"Model" );
		app.ExecuteCommand( L"AddDelta", cargs, oarg );
		cargs.Clear();
		myDelta = oarg;

		myDelta.PutMute (true);

		app.LogMessage(L"muting " + myDelta.GetName());

		// UpdateReferencedModel command
		cargs.Add( L"Model" );
		app.ExecuteCommand( L"UpdateReferencedModel", cargs, oarg );
		cargs.Clear();

	\endcode
	*/
	CStatus PutMute( const bool in_Mute );

	/*! Returns an array containing each ActionDelta object in the %Delta.
	\return Array of of references to all ActionDelta objects contained in the delta.
	\eg See Delta main example for an example of how to use the GetActionDeltas function.
	*/
	CRefArray GetActionDeltas()const;

	private:
	Delta * operator&() const;
	Delta * operator&();
};

};

#endif // __XSIDELTA_H__
