//*****************************************************************************
/*!
   \file xsi_actiondelta.h
   \brief ActionDelta class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************
#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIACTIONDELTA_H__
#define __XSIACTIONDELTA_H__

#include <xsi_siobject.h>
#include <xsi_vector3.h>

namespace XSI {

class ActionDeltaItem;
class CDoubleArray;
//*****************************************************************************
/*! \class ActionDelta xsi_actiondelta.h
	\brief The %ActionDelta object tracks changes made on a parameter that is part of a reference
	model. Every %ActionDelta contains one or more ActionDeltaItem objects, each of which represents
	a single change, or modification, to a referenced parameter. Each %ActionDelta object has a
	specific type (see ::siModificationDeltaType) and each %ActionDeltaItem it contains is of the same type.

	ActionDeltas are stored in the Delta and are accessible via Delta::GetActionDeltas. To add a new
	%ActionDelta to an existing %Delta object, use Delta::AddAction.

	\since 6.0
	\eg Illustrates how to print some info about an ActionDelta
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

		CRefArray ActionDeltas = myDelta.GetActionDeltas();
		for ( LONG i=0; i<ActionDeltas.GetCount(); ++i ) {

			ActionDelta item = ActionDeltas[i];

			// Print info about the current ActionDelta
			Application().LogMessage(L"ActionSourceItem[" + CValue(i).GetAsText() + L"]");
			Application().LogMessage(L"Name: " + item.GetName());
			Application().LogMessage(L"Type: " + item.GetType());

		}
	\endcode

*/

class SICPPSDKDECL ActionDelta : public SIObject
{
public:
	/*! Default constructor. */
	ActionDelta();

	/*! Default destructor. */
	~ActionDelta();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	ActionDelta(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	ActionDelta(const ActionDelta& in_obj);

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
	\return The new ActionDelta object.
	*/
	ActionDelta& operator=(const ActionDelta& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new ActionDelta object.
	*/
	ActionDelta& operator=(const CRef& in_ref);

	/*! Adds a new ActionDeltaItem of type ::siModificationDeltaFCurves to an ActionDelta created
	with Delta::AddAction.

	The %ActionDelta should be of type ::siModificationDeltaFCurves to use this function (see
	::siModificationDeltaType for a list of %ActionDelta types).

	\param in_Target Target path for source item
	\param in_KeyValueArray An array containing 6 values per key for FCurve objects of interpolation
		type ::siCubicInterpolation (see ::siFCurveInterpolation) and 2 values per keys for the other
		%FCurve interpolation types. The first value is the key time (in frames) and the second is
		the key value (in value units). For Cubic (or bezier) FCurves the remaining 4 values are the
		tangency values for: \a lefttanx (in frames), \a lefttany (in value units), \a righttanx (in
		frames), and \a righttany (in value units).
	\param in_Interpolation The interpolation of the FCurve (default ::siCubicInterpolation).
	\param in_Type The type of the FCurve (siStandardFCurve).
	\param in_Extrapolation The extrapolation of the FCurve (default ::siConstantExtrapolation).
	\return The new ActionDeltaItem
	\eg Illustrates how to add an ActionDeltaItem of type siModificationDeltaFCurves to a ActionDelta.
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

		// Add an action of type siModificationDeltaFCurve
		ActionDelta myDeltaAction = myDelta.AddAction(siModificationDeltaFCurve);

		// Set the array
		CDoubleArray keys(12);
		keys[0] = 1.0; keys[1] = 5.0; keys[2] = 0.0; keys[3] = 0.0; keys[4] = 0.0; keys[5] = 0.0;
		keys[6] = 100.0; keys[7] = 8.0; keys[8] = 0.0; keys[9] = 0.0; keys[10] = 0.0; keys[11] = 0.0;

		// Add the fcurve item
		ActionDeltaItem myActionDeltaItem = myDeltaAction.AddFCurveItem ( myCube.GetFullName() + L".kine.global.posx", keys );

		// Apply modification
		myDelta.Apply();

	\endcode
	*/
	ActionDeltaItem	AddFCurveItem (
		const CString&		in_Target,
		const CDoubleArray&	in_KeyValueArray,
		siFCurveInterpolation  in_Interpolation = siCubicInterpolation,
		siFCurveType		   in_Type =siStandardFCurve,
		siFCurveExtrapolation  in_Extrapolation=siConstantExtrapolation
	);

	/*! Adds a new ActionDeltaItem of type ::siModificationDeltaConstraint to an ActionDelta created with
	Delta::AddAction.

	The %ActionDelta should be of type ::siModificationDeltaConstraint to use this function (see
	::siModificationDeltaType for a list of %ActionDelta types).

	\param in_preset The type of constraint to add.
	\param in_cnsned An array of references to X3DObject elements that will be constrained (see Constraint::GetConstrained).
	\param in_cnsning An array of references to X3DObject elements that will act as constrainers (see Constraint::GetConstraining).
	\param in_bComp Compensation mode: true to turn compensation on.
	\param in_offsetCnsned Optional offset which is applied in translation on the constrained object.
		The offset is used for Distance and Position constraints.
	\param in_offsetCnsning Optional offset applied on the constraining object for Distance, Position,
		Surface and Trajectory constraints. The offset will be applied in rotation for the Orientation
		constraint, in translation for the Direction constraint and in scaling for the Scaling constraint.
	\return An array of references to the new ActionDeltaItems (one for each parameter now being driven by the constraint)
	\eg Illustrates how to add an ActionDeltaItem of type siModificationDeltaConstraint to a ActionDelta.
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

		X3DObject myCone;
		root.AddGeometry( L"Cone", L"MeshSurface",L"",myCone);

		// Translate command
		cargs.Add(myCone.GetFullName()); cargs.Add(2.0); cargs.Add(1.3); cargs.Add(0.0);
		cargs.Add(L"siRelative"); cargs.Add(L"siView"); cargs.Add(L"siObj"); cargs.Add(L"siXYZ");
		app.ExecuteCommand( L"Translate", cargs, oarg );
		cargs.Clear();

		Delta myDelta;
		// AddDelta command
		cargs.Add( L"Model" );
		app.ExecuteCommand( L"AddDelta", cargs, oarg );
		cargs.Clear();
		myDelta = oarg;

		// Add an action of type siModificationDeltaConstraint
		ActionDelta myDeltaAction = myDelta.AddAction(siModificationDeltaConstraint);

		CRefArray constraineds(1);
		constraineds[0] = myCube;

		CRefArray constrainings(1);
		constrainings[0] = myCone;

		// Add the constraint item
		CRefArray myActionDeltaItems = myDeltaAction.AddConstraintItem ( L"Position",
			constraineds, constrainings, false, MATH::CVector3(), MATH::CVector3());

		// Apply modification
		myDelta.Apply();

	\endcode
	*/
	CRefArray AddConstraintItem (
		const CString&		in_preset,
		const CRefArray&	in_cnsned,
		const CRefArray&	in_cnsning,
		bool				in_bComp,
		const MATH::CVector3& in_offsetCnsned,
		const MATH::CVector3& in_offsetCnsning
	);

	/*! Adds a new ActionDeltaItem of type ::siModificationDeltaStaticValue to an %ActionDelta
	created with Delta::AddAction.

	The %ActionDelta should be of type ::siModificationDeltaStaticValue to use this function (see
	::siModificationDeltaType for a list of %ActionDelta types).

	\param in_Target Target path for source item
	\param in_Value The value of the static value
	\return The new ActionDeltaItem object
	\eg Illustrates how to add an ActionDeltaItem of type siModificationDeltaStaticValue to a ActionDelta.
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

		// Apply modification
		myDelta.Apply();

	\endcode
	*/
	ActionDeltaItem	AddStaticValueItem (
		const CString&		in_Target,
		double				in_Value
	);


	/*! Adds a new ActionDeltaItem of type ::siModificationDeltaExpression to an %ActionDelta
	created with Delta::AddAction.

	The %ActionDelta should be of type ""siModificationDeltaExpression to use this function (see
	::siModificationDeltaType for a list of %ActionDelta types).

	\param in_Target Target path for source item
	\param in_Expression The definition (formula) that defines the expression. For more information on how to
		define an expression, see "Expression Reference" in the Softimage User’s Guide.
	\return The new ActionDeltaItem
	\eg Illustrates how to add an ActionDeltaItem of type siModificationDeltaExpression to a ActionDelta.
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

		X3DObject myCone;
		root.AddGeometry( L"Cone", L"MeshSurface",L"",myCone);

		// Translate command
		cargs.Add(myCone.GetFullName()); cargs.Add(2.0); cargs.Add(1.3); cargs.Add(0.0);
		cargs.Add(L"siRelative"); cargs.Add(L"siView"); cargs.Add(L"siObj"); cargs.Add(L"siXYZ");
		app.ExecuteCommand( L"Translate", cargs, oarg );
		cargs.Clear();

		Delta myDelta;
		// AddDelta command
		cargs.Add( L"Model" );
		app.ExecuteCommand( L"AddDelta", cargs, oarg );
		cargs.Clear();
		myDelta = oarg;

		// Add an action of type siModificationDeltaExpression
		ActionDelta myDeltaAction = myDelta.AddAction(siModificationDeltaExpression);

		// Add the Expression item
		ActionDeltaItem myActionDeltaItem = myDeltaAction.AddExpressionItem ( myCube.GetFullName() + L".kine.global.posx",
			L"5*sin(" + myCone.GetFullName() + L".kine.local.posx * 15)");

		// Apply modification
		myDelta.Apply();
	\endcode
	*/
	ActionDeltaItem	AddExpressionItem (
		const CString&		in_Target,
		const CString&		in_Expression
	);

	/*! Returns the name of the %ActionDelta.
	\return The name of the %ActionDelta
	\eg See the main ActionDelta example which demonstrates how to use this function.
	*/
	CString GetName()const;

	/*! Returns the type of the %ActionDelta.
	\return A value from the ::siModificationDeltaType enum.
	\eg See the main ActionDelta example which demonstrates how to use this function.
	*/
	CString GetType()const;

	/*! Removes an ActionDeltaItem from the %ActionDelta.

	\note After a removal, the %ActionDeltaItem object may not target the same item
	(see example).

	\param in_target The name of the %ActionDeltaItem to remove.
	\return CStatus::OK success
	\return CStatus::Fail is returned in case of failure
	\eg Illustrates how to to remove an ActionDeltaItem.
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

		X3DObject myCone;
		root.AddGeometry( L"Cone", L"MeshSurface",L"",myCone);

		// Translate command
		cargs.Add(myCone.GetFullName()); cargs.Add(2.0); cargs.Add(1.3); cargs.Add(0.0);
		cargs.Add(L"siRelative"); cargs.Add(L"siView"); cargs.Add(L"siObj"); cargs.Add(L"siXYZ");
		app.ExecuteCommand( L"Translate", cargs, oarg );
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

		// Get the static item
		ActionDelta ActionDeltaStatic = myDelta.GetActionDeltas().GetItem(0);
		ActionDeltaItem ActionDeltaItem0 = ActionDeltaStatic.GetItems().GetItem(0);
		ActionDeltaItem ActionDeltaItem1 = ActionDeltaStatic.GetItems().GetItem(0);

		// Print the name of ActionDeltaItem1
		app.LogMessage ( L"Second item name before removing oActionDeltaItem1: " + ActionDeltaItem1.GetName());

		// Remove oActionDeltaItem0
		ActionDeltaStatic.RemoveItem(ActionDeltaItem0.GetName());

		// Print the name of ActionDeltaItem1
		app.LogMessage ( L"Second item name after removing oActionDeltaItem1: " + ActionDeltaItem1.GetName());


		// Add an action of type siModificationDeltaExpression
		ActionDelta DeltaActionExp = myDelta.AddAction(siModificationDeltaExpression);

		// Add the Expression item
		ActionDeltaItem myActionDeltaItem = DeltaActionExp.AddExpressionItem ( myCube.GetFullName() + L".kine.global.posx",
			L"5*sin(" + myCone.GetFullName() + L".kine.local.posx * 15)");

		DeltaActionExp.RemoveAllItems();

		// Apply modification
		myDelta.Apply();

	\endcode
	*/
	CStatus	RemoveItem ( const CString& in_target );

	/*! Removes all ActionDeltaItem objects from the %ActionDelta.
	\return CStatus::OK success
	\return CStatus::Fail is returned in case of failure
	\eg See the ActionDelta::RemoveItem example which demonstrates how to use this function.
	*/
	CStatus	RemoveAllItems ();

	/*! Returns all ActionDeltaItem objects that make up the %ActionDelta.
	\return Array of references to each ActionDeltaItem contained in the %ActionDelta.
	\eg See the main ActionDelta example which demonstrates how to use this function.
	*/
	CRefArray GetItems()const;


	private:
	ActionDelta * operator&() const;
	ActionDelta * operator&();
};

}

#endif // __XSIACTIONDELTA_H__
