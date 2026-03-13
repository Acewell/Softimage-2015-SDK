//*****************************************************************************
/*!
   \file xsi_layer.h
   \brief Layer class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSILAYER_H__
#define __XSILAYER_H__

#include <xsi_group.h>

namespace XSI {

//*****************************************************************************
/*! \class Layer xsi_layer.h
	\brief The Layer is a self-contained collection of SceneItem objects. It can be nested one level to provide Layer Group functionality

	Layers are exclusive group containers. An 3D object in the scene must belong to a layer, but can only belong one at a given time. 
	This can be changed by moving objects from layer to layer.

	Layers can be nested on level to provide layer grouping, meaning that users can control a set of layers in a non-destructive way.
	This can improve efficiency by quickly hiding/showing objects from a set of layers rather than having to change them and reset them afterward.

	You can create a new layer with the \xl CreateLayer command, and access a scene's layers via
	the Scene.

	\sa Scene::GetLayers, Scene::GetActiveLayer, \xl CreateLayer
	\eg
	\code
		using namespace XSI;
		Application app;

		Project project = app.GetActiveProject();
		Scene scn = project.GetActiveScene();


		Layer myLayer = scn.GetActiveLayer() ;

		using namespace XSI;
		CValueArray args(2);
		CValue outArg;
		args[0] = CValue( L"" );
		args[1] = CValue(L"MyNestedLayer");
		app.ExecuteCommand( L"CreateLayer", args, outArg );
		CValueArray result = outArg;
		Layer NestedLayer = result[0];

		myLayer.AddLayer( NestedLayer );
		app.LogMessage(L"Number of sub-Layers of myLayer is: " + myLayer.GetLayers().GetCount() );

		myLayer.AddLayer( myLayer );

		NestedLayer.AddLayer( myLayer );

		myLayer.RemoveLayer( NestedLayer );
		app.LogMessage(L"Number of sub-Layers of myLayer is: " + myLayer.GetLayers().GetCount() );
	\endcode
*/
//*****************************************************************************
class SICPPSDKDECL Layer : public Group
{
public:
	/*! Default constructor. */
	Layer();

	/*! Default destructor. */
	~Layer();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	Layer(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	Layer(const Layer& in_obj);

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
	\return The new Layer object.
	*/
	Layer& operator=(const Layer& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new Layer object.
	*/
	Layer& operator=(const CRef& in_ref);

	/*! property Layers

	Returns the array of the sub layers parented under this layer.
	\return The layer children
	*/
	CRefArray GetLayers(  ) const;
	/*! property AddLayer
		Adds an existing layer. The existing layer will be removed from its current owner (LayerContainer or another Layer).
		\param in_member The layer to add as a child.
	*/
	CStatus AddLayer( const Layer& in_member ) ;
	/*! property RemoveLayer
		Removes the layer from our child array. The layer will be reparented to the Layer Container.
		\param in_member The layer to remove
	*/
	CStatus RemoveLayer( const Layer& in_member ) ;

	private:
	Layer * operator&() const;
	Layer * operator&();

	public:


};

};

#endif // __XSILAYER_H__
