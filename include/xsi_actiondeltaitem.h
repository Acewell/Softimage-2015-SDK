//*****************************************************************************
/*!
   \file xsi_actiondeltaitem.h
   \brief ActionDeltaItem class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************
#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIACTIONDELTAITEM_H__
#define __XSIACTIONDELTAITEM_H__

#include <xsi_siobject.h>

namespace XSI {

//*****************************************************************************
/*! \class ActionDeltaItem xsi_actiondeltaitem.h
	\brief The %ActionDeltaItem object tracks changes made on a parameter that is part of a reference
	model. Each %ActionDeltaItem represents a single change, or modification, to a referenced parameter.
	So each time there a change to a static value, an FCurve, a Constraint, an Expression or a GroupRelation,
	a new %ActionDeltaItem is generated.

	You can also create new ActionDeltaItems from a data set using one of these functions:

	\li ActionDelta::AddConstraintItem
	\li ActionDelta::AddExpressionItem
	\li ActionDelta::AddFCurveItem
	\li ActionDelta::AddStaticValueItem

	%ActionDeltaItem objects of the same type (see ::siModificationDeltaType) are stored in an ActionDelta
	which is accessible via the ActionDelta::GetItems function.

	\since 6.0
	\eg Illustrates how to assign a new value to an ActionDeltaItem.
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

			//Print the new value + some AuditInformation
			strmgs = L"New value: "; strmgs += item.GetValue();
			strmgs+= L", "; strmgs += item.GetAuditInfo();
			Application().LogMessage(strmgs);
		}

	\endcode

*/

class SICPPSDKDECL ActionDeltaItem : public SIObject
{
public:
	/*! Default constructor. */
	ActionDeltaItem();

	/*! Default destructor. */
	~ActionDeltaItem();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	ActionDeltaItem(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	ActionDeltaItem(const ActionDeltaItem& in_obj);

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
	\return The new ActionDeltaItem object.
	*/
	ActionDeltaItem& operator=(const ActionDeltaItem& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new ActionDeltaItem object.
	*/
	ActionDeltaItem& operator=(const CRef& in_ref);

	/*! Returns the name of the %ActionDeltaItem.
	\return The name of the %ActionDeltaItem.
	\eg See the main ActionDeltaItem example which demonstrates how to use this function.
	*/
	CString GetName()const;

	/*! Sets the name of the %ActionDeltaItem.
	\param in_Name New name for the object.
	\return CStatus::OK success
	\return CStatus::Fail is returned in case of failure
	*/
	CStatus PutName( const CString& in_Name )const;

	/*! Returns the type of the %ActionDeltaItem.
	\return One of the values from ::siModificationDeltaType.
	\eg See the main ActionDeltaItem example which demonstrates how to use this function.
	*/
	CString GetType()const;

	/*! Returns whether the %ActionDeltaItem is muted or not.
	\return True if the %ActionDeltaItem is muted; false if it's active.
	\eg See the ActionDeltaItem::PutMute example which demonstrates how to use this function.
	*/
	bool GetMute()const;

	/*! Sets whether the %ActionDeltaItem is muted or not.
	\param in_Mute True to mute the %ActionDeltaItem is muted; false to make it active.
	\return CStatus::OK success
	\return CStatus::Fail is returned in case of failure
  	\eg Illustrates how to mute a ActionDeltaItem
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

		// Mute the Item
		myActionDeltaItem.PutMute (true);
		app.LogMessage(L"muting " + myActionDeltaItem.GetName());

		// Apply modification
		myDelta.Apply();

		// UpdateReferencedModel command
		cargs.Add( L"Model" );
		app.ExecuteCommand( L"UpdateReferencedModel", cargs, oarg );
		cargs.Clear();

	\endcode
	*/
	CStatus PutMute( const bool in_Mute );

	/*! Returns the value of an %ActionDeltaItem. Depending on the type of the %ActionDeltaItem
	(see ActionDeltaItem::GetType) the returned CValue may contain several different types of data.

	\return CValue::m_t == CValue::siRef for item of type siModificationDeltaFCurves (CRef containing
		a reference to the FCurve).
	\return CValue::m_t == CValue::double for item of type siModificationDeltaStaticValue.
	\return CValue::m_t == CValue::string for item of other type.
	\sa Parameter::GetValue
  	\eg Illustrates how to get and set value for ActionDeltaItem of type siModificationDeltaFCurves
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

		// SaveKey command
		cargs.Add( L"Model.kine.local.posx,Model.kine.local.posy,Model.kine.local.posz" ); cargs.Add( 1 );
		app.ExecuteCommand( L"SaveKey", cargs, oarg );
		cargs.Clear();

		FCurve myFCurve;

		ActionDelta ActionDelta0 = myDelta.GetActionDeltas().GetItem(0);
		ActionDeltaItem ActionDeltaItem0 = ActionDelta0.GetItems().GetItem(0);
		myFCurve = ActionDeltaItem0.GetValue();

		LONG nbkeys = 100;
		myFCurve.BeginEdit();

		for(LONG i = 0; i < nbkeys; i++ )
		{
			double val = sin(1.0/(i+1.0) *10.0);
			myFCurve.AddKey(i, val);
		}

		myFCurve.EndEdit();

		CValue MyFCValue(myFCurve);
		ActionDeltaItem0.PutValue(MyFCValue);

		// Apply modification
		myDelta.Apply();

	\endcode
	*/
	CValue GetValue()const;

	/*! Sets the value of an %ActionDeltaItem. Depending on the type of the %ActionDeltaItem
	(see ActionDeltaItem::GetType) you may specify several different types of data in \c in_value.

	\param in_value CValue::m_t == CValue::siRef for item of type ::siModificationDeltaFCurves
		(CRef containing a reference to the FCurve).
	\param in_value CValue::m_t == CValue::double for item of type ::siModificationDeltaStaticValue.
	\param in_value CValue::m_t == CValue::string for item of any other type.
	\return CStatus::OK success
	\return CStatus::Fail is returned in case of failure
  	\eg Illustrates how to set a value for ActionDeltaItem of type siModificationTypeConstraints
	\code
		using namespace XSI;
		Application app;

		// NewScene command
		CValueArray cargs; CValue oarg;
		cargs.Add( L"" ); cargs.Add( false );
		app.ExecuteCommand( L"NewScene", cargs, oarg );
		cargs.Clear();

		//Add cube, cone and sphere geometries and create the reference model
		Model root = app.GetActiveSceneRoot();
		X3DObject myCube, myCone, mySphere;
		root.AddGeometry( L"Cube", L"MeshSurface",L"",myCube);
		root.AddGeometry( L"Cone", L"MeshSurface",L"",myCone);
		root.AddGeometry( L"Sphere", L"MeshSurface",L"",mySphere);

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
		cargs.Add(myCone.GetFullName()); cargs.Add(3.0); cargs.Add(3.0); cargs.Add(0.0);
		cargs.Add(L"siRelative"); cargs.Add(L"siView"); cargs.Add(L"siObj"); cargs.Add(L"siXYZ");
		app.ExecuteCommand( L"Translate", cargs, oarg );
		cargs.Clear();

		// Translate command
		cargs.Add(mySphere.GetFullName()); cargs.Add(-2.0); cargs.Add(-2.0); cargs.Add(0.0);
		cargs.Add(L"siRelative"); cargs.Add(L"siView"); cargs.Add(L"siObj"); cargs.Add(L"siXYZ");
		app.ExecuteCommand( L"Translate", cargs, oarg );
		cargs.Clear();

		// ApplyCns command
		cargs.Add( L"Position" ); cargs.Add(myCube.GetFullName()); cargs.Add(myCone.GetFullName());
		app.ExecuteCommand( L"ApplyCns", cargs, oarg );
		cargs.Clear();

		ActionDelta ActionDelta0 = myDelta.GetActionDeltas().GetItem(0);
		CRefArray ActionDeltaItems = ActionDelta0.GetItems();
		for ( LONG i=0; i<ActionDeltaItems.GetCount(); ++i ) {
			ActionDeltaItem item = ActionDeltaItems[i];
			item.PutValue(L"Scene_Root." + mySphere.GetFullName());
		}

		// Apply modification
		myDelta.Apply();

		// UpdateReferencedModel command
		cargs.Add( L"Model" );
		app.ExecuteCommand( L"UpdateReferencedModel", cargs, oarg );
		cargs.Clear();
	\endcode
	*/
	CStatus PutValue(CValue in_value);

	/*! Returns the Audit Information on the %ActionDeltaItem.
	\return The string containing the audit information
	\eg See the main ActionDeltaItem example which demonstrates how to use this function.
	*/
	CString GetAuditInfo();

	private:
	ActionDeltaItem * operator&() const;
	ActionDeltaItem * operator&();
};

}

#endif // __XSIACTIONDELTAITEM_H__
