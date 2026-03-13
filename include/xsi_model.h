//*****************************************************************************
/*!
   \file xsi_model.h
   \brief Model class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************
#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIMODEL_H__
#define __XSIMODEL_H__

#include <xsi_x3dobject.h>

namespace XSI {

class Group;
class Material;
class ActionSource;
class Mixer;

//*****************************************************************************
/*! \class Model xsi_model.h
	\brief The Model object represents any Softimage model node, including referenced models, and even the
	Scene Root. Softimage models act as a container for objects (usually hierarchies of objects) and many
	of their properties. Models are a type of X3DObject and as such can be positioned in space. A model can
	contain objects, Groups, or other models.

	The Scene Root can be accessed using Application::GetActiveSceneRoot. In addition, any ProjectItem or
	Parameter can return a reference to the model in which it lives via the ProjectItem::GetModel and
	Parameter::GetModel functions.

	You can also get list of all models under a given model by using X3DObject::GetModels (a %Model is a
	specialized kind of X3DObject). Therefore, if you use GetModels on the Scene Root recursively, it returns
	all models in the active scene.

	To create a new model, use X3DObject::AddModel, which also returns a Model object. There are also a few
	scripting commands which create model nodes as well: \xl CreateModel, \xl SICreateModel, etc.

	You can also import or export models (including referenced models) with a series of commands: \xl ImportModel,
	\xl ExportModel, \xl ImportRefModels, etc. When a referenced model is instantiated in the scene, changes
	to that model are tracked by the Delta system as of v6.0.

	\sa Group

	\eg Demonstrates how to work with groups in a model

	\code
		using namespace XSI;
		Application app;
		Model root = app.GetActiveSceneRoot();

		Null myNull;
		root.AddNull( L"MyNull", myNull );

		CRefArray groupMembersRef;
		groupMembersRef.Add(myNull);

		Group myGroup;
		root.AddGroup(groupMembersRef, L"MyGroup",false, myGroup);

		app.LogMessage( CString(L"The group: ") + myGroup.GetFullName() );
	\endcode
 */
//*****************************************************************************
class SICPPSDKDECL Model : public X3DObject
{
public:
	/*! Default constructor. */
	Model();

	/*! Default destructor. */
	~Model();

	/*! Constructor.
	* \param in_ref constant reference object.
	*/
	Model(const CRef& in_ref);

	/*! Copy constructor.
	* \param in_obj constant class object.
	*/
	Model(const Model& in_obj);

	/*! Returns true if a given class type is compatible with this API class.
	* \param in_ClassID class type.
	* \return bool true if the class is compatible, false otherwise.
	*/
	bool IsA( siClassID in_ClassID) const;

	/*! Returns the type of the API class.
	* \return siClassID the class type.
	*/
	siClassID GetClassID() const;

	/*! Creates an object from another object. The newly created object is set to
	* empty if the input object is not compatible.
	* \param in_obj constant class object.
	* \return Model& New Model object.
	*/
	Model& operator=(const Model& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	* set to empty if the input reference object is not compatible.
	* \param in_ref constant class object.
	* \return Model& New Model object.
	*/
	Model& operator=(const CRef& in_ref);

	/*! Returns an array of references to all Group objects in the model.
	\return CRefArray array of references to Group objects in the model.
	*/
	CRefArray	GetGroups() const;

	/*! Returns an array of references to all Source objects in the model. Currently,
	the only sources available to the model are of type ActionSource, which	is a
	specialized kind of %Source object.

	Audio and Image sources (which are basically references to audio and image files)
	are all stored under the Scene container (see Scene::GetExternalFiles).

	\note Prior to v6.0, %Model sources were also available using this property as a
	way to manage changes to reference models; however, this functionality is now
	provided by the Delta system.

	\return CRefArray array of references to data source objects in the model.

	\eg Demonstrates how to find all sources in the scene
	by using the Model.Sources property on every model returned from
	the X3DObject.Models property, given this structure:

	\code
		   Scene_Root (Model)
			   |- Herb (Model)
			   |    |- Mixer (animation clip on null.posx)
			   |    |- null  (null.size = FCurve)
			   |
			   |- Jesse (Model)
			   |    |- Mixer (animation clips on null.scly,null.sclz,null.rotz)
			   |    |- null
			   |
			   |- Sally (Model)
					|- Mixer (audio clip)
					|- grid (image on its texture projection)
	\endcode

	\code
		using namespace XSI;

		// Forward declarations
		CString GetRelativePath( Parameter& in_param );
		void MakeNewFCrvSource( Null& in_null );
		CRefArray FindSourcesUnderModel( Model& in_model );

		Application app;

		// NewScene command
		CValueArray cargs; CValue oarg;
		cargs.Add( L"" ); cargs.Add( false );
		app.ExecuteCommand( L"NewScene", cargs, oarg );
		cargs.Clear(); oarg.Clear();

		// Get the SceneRoot
		Model root = app.GetActiveSceneRoot();

		// Create a new model and add a null
		Model m; root.AddModel( CRefArray(), L"MyModel", m );
		Null n; m.AddNull( L"MyNull", n );

		// Add an fcurve ActionSource based on the new null
		MakeNewFCrvSource( n );

		// Find sources under the SceneRoot
		FindSourcesUnderModel( root );

		// Look under any other models
		CRefArray mdls = root.GetModels();
		for ( LONG i=0; i<mdls.GetCount(); ++i ) {
			Model m( mdls[i] );
			FindSourcesUnderModel( m );
		}


		// Expected results:
		//INFO : No sources found on Scene_Root
		//INFO : Sources.MyModel.StoredFcvAction is a ActionSource


		CRefArray FindSourcesUnderModel( Model& in_model )
		{
			Application app;
			CRefArray foundsrcs = in_model.GetSources();

		   // Loop through the collection of sources found under this model to print the
		   // name and add its name to the result string
		   if ( foundsrcs.GetCount() > LONG(0) ) {
			   for ( LONG i=0; i<foundsrcs.GetCount(); ++i ) {
				  Source src( foundsrcs[i] );
				  app.LogMessage( src.GetFullName() + L" is a " + src.GetClassIDName() );
			   }
		   } else {
			   app.LogMessage( L"No sources found on " + in_model.GetFullName() );
		   }

		   return foundsrcs;
		}


		// Function to remove the name of the model from the FullName of the specified parameter.
		// This is necessary when setting up a source that will later be used to instantiate a
		// clip when the parameter lives under a model other than the Scene_Root.
		CString GetRelativePath( Parameter& in_param )
		{
			Model mdl = in_param.GetModel();
			CString mdlname = mdl.GetFullName();
			if ( mdlname.IsEqualNoCase(L"Scene_Root") ) {
				return in_param.GetFullName();
			} else {
				CString tmp = in_param.GetFullName();
				CString lookfor = mdlname + L".";
				CString foundsofar = L"";
				CString relpath = L"";
				for ( ULONG i=0; i<tmp.Length(); ++i ) {
					if ( foundsofar.IsEqualNoCase(lookfor) ) {
						relpath += tmp[i];
					} else {
						foundsofar += tmp[i];
					}
				}
				return relpath;
			}
		}

		// Create a simple (fcurve) actionsource based on a null's position
		void MakeNewFCrvSource( Null& in_null )
		{
			Application app;
			Model mdl = in_null.GetModel();

			CTimeArray time; time.Add( CTime(1.000) ); time.Add( CTime(50.000) ); time.Add( CTime(100.000) );
			CValueArray vals;

			// X
			Parameter posx = in_null.GetParameter( L"posx" ); CString rposx = GetRelativePath(posx);
			FCurve fcx; posx.AddFCurve( siStandardFCurve, fcx );
			vals.Add( CValue(-8.153) ); vals.Add( CValue(0.197) ); vals.Add( CValue(9.413) );
			fcx.SetKeys( time, vals ); vals.Clear();

			// Y
			Parameter posy = in_null.GetParameter( L"posy" ); CString rposy = GetRelativePath(posy);
			FCurve fcy; posy.AddFCurve( siStandardFCurve, fcy );
			vals.Add( CValue(7.015) ); vals.Add( CValue(-1.92) ); vals.Add( CValue(7.015) );
			fcy.SetKeys( time, vals ); vals.Clear();

			// Z
			Parameter posz = in_null.GetParameter( L"posz" ); CString rposz = GetRelativePath(posz);
			FCurve fcz; posz.AddFCurve( siStandardFCurve, fcz );
			vals.Add( CValue(-0.702) ); vals.Add( CValue(0.192) ); vals.Add( CValue(-0.702) );
			fcz.SetKeys( time, vals );

			// Build an action with the fcurves as source items
			ActionSource src = mdl.AddActionSource( L"StoredFcvAction" );
			src.AddSourceItem( rposx, fcx, true );
			src.AddSourceItem( rposy, fcy, true );
			src.AddSourceItem( rposz, fcz, true );
		}

	\endcode
	*/
	CRefArray	GetSources() const;

	/*! Creates a group in the model and adds objects to the group.

	\param in_members	array of reference to members to add to the group.
	\param in_name		name of the group.
	\param in_branch	Add new members as branch members
	\param io_group		Group that was added.

	\return CStatus::OK success
	\return CStatus::Fail failure
	*/
	CStatus	AddGroup
	(
		const CRefArray&	in_members,
		const CString&		in_name,
		bool				in_branch,
		Group&				io_group
	);

	/*! Returns the active Mixer if there is one. If not, this method returns an invalid
	Mixer object. You can check its validity by using the CBase::IsValid method.
	\return Mixer
	\since 4.0
	*/
	Mixer   GetMixer() const;

	/*! Returns true if there is a mixer nested directly under the model, false otherwise.
	\return bool true if there's an active Mixer for this Model.
	\since 4.0
	*/
	bool  HasMixer() const;

	/*! Adds an empty action source. In order to fill the ActionSource you must use
	ActionSource::AddSourceItem.

	\param in_name Name of the new action source
	\return ActionSource the newly created ActionSource object
	\sa ActionSource::AddSourceItem, AnimationSourceItem, AnimationSourceItem::SetAsStatic
	\since 4.0

	\eg See the AnimationSourceItem page for an example of how to create an empty
		ActionSource, populate it and then change the source.
	*/
	ActionSource AddActionSource(const CString& in_name = CString());

	/*! Adds an empty Mixer object. If the current model does not have a
	mixer, this function fails and returns an invalid Mixer object.
	\return Mixer the newly created Mixer object
	\since 4.0
	*/
	Mixer AddMixer();

	/*! Returns the external file list for the model.
	\return Array of FileReference objects.
	\since 5.0
	*/
	CRefArray GetExternalFiles() const;

	/*! Returns the type of model. The type can be one of regular, referenced, or instance.
	\return The \link siModelKind \endlink type of model.
	\since 6.0
	*/
	XSI::siModelKind GetModelKind() const;

	/*! Returns the master model of this model, if this model is an instance. To check
	whether this model is an instance model, use Model::GetModelKind to query for the type.
	\return The master Model of this instance model (if applicable).
	\sa \link siModelKind \endlink
	\since 7.0
	*/
	Model GetInstanceMaster() const;

	/*! Returns all objects found in this model that match a class identifier. These identifiers are documented but can also be
	discovered by inspecting Softimage objects with the SDK Explorer. The supported class identifierss are the following:

	\li \ref XSI::siAnnotationID
	\li \ref XSI::siCameraID
	\li \ref XSI::siClusterID
	\li \ref XSI::siClusterPropertyID
	\li \ref XSI::siConstraintID
	\li \ref XSI::siCustomOperatorID
	\li \ref XSI::siCustomPropertyID
	\li \ref XSI::siEnvelopeID
	\li \ref XSI::siEnvelopeWeightID
	\li \ref XSI::siExpressionID
	\li \ref XSI::siGeometryID
	\li \ref XSI::siGroupID
	\li \ref XSI::siICETreeID
	\li \ref XSI::siLightID
	\li \ref XSI::siMaterialID
	\li \ref XSI::siModelID
	\li \ref XSI::siNullID
	\li \ref XSI::siNurbsSurfaceMeshID
	\li \ref XSI::siNurbsCurveListID
	\li \ref XSI::siOperatorID
	\li \ref XSI::siPolygonMeshID
	\li \ref XSI::siPropertyID
	\li \ref XSI::siShaderID
	\li \ref XSI::siShapeKeyID
	\li \ref XSI::siX3DObjectID
	
	\param in_nClassID An object class id as defined in XSI::siClassID.
	\return CSIObjectRefArray Array of objects. 
	\sa Application::FindObjects
	\since 9.5 (2011)

	\eg
	\code
		using namespace XSI;
		Application app;

		// Returns all 3d objects in the scene as X3DObjects objects
		Application app;
		CSIObjectRefArray objArray = app.GetActiveSceneRoot().FindObjects( siX3DObjectID );
		for ( LONG i=0; i<objArray.GetCount(); i++ )
		{
			app.LogMessage( "X3DObject: " + objArray[i].GetFullName() );
		}

		// Returns all lights found in model 'A' as Light 3D objects.
		Model modelA = app.GetActiveSceneRoot().GetModels().GetItem( "A" );
		objArray = modelA.FindObjects( siLightID );
		for ( LONG i=0; i<objArray.GetCount(); i++ )
		{
			app.LogMessage( "Lights: " + objArray[i].GetFullName() );
		}
	\endcode

	*/
	CSIObjectRefArray FindObjects( const XSI::siClassID& in_nClsID ) const;

	/*! Returns all objects found in this model that match a Softimage object \c CLSID. Object CLSID are not documented 
	but can be discovered with XSIUtils.DataRepository or by inspecting Softimage objects with the SDK Explorer. 
	
	\param in_sCLSID An object \c CLSID.
	\return CSIObjectRefArray Array of objects.
	\sa Application::FindObjects
	\since 9.5 (2011)

	\eg
	\code
		using namespace XSI;
		Application app;
		
		// Find all lights in model 'A'
		Model modelA = app.GetActiveSceneRoot().GetModels().GetItem( "A" );
		CSIObjectRefArray lights = modelA.FindObjects( "{F3705C30-5204-11D0-8298-00A0243E366B}" );

		for ( LONG i=0; i< lights.GetCount(); i++ )
		{
			app.LogMessage( "Light: " + lights[i].GetFullName() );
		}
	\endcode
	
	*/
	CSIObjectRefArray FindObjects( const CString& in_sCLSID ) const;

	private:
	Model * operator&() const;
	Model * operator&();
};

}

#endif // __XSIMODEL_H__
