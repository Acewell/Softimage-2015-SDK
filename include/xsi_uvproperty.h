//*****************************************************************************
/*!
	\file xsi_uvproperty.h
	\brief UVProperty class declaration.
   
	Copyright 2010 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIUVPROPERTY_H__
#define __XSIUVPROPERTY_H__

#include <xsi_clusterproperty.h>

namespace XSI {

class CBitArray;
class CLongArray;

//*****************************************************************************
/*! 
	\class UVProperty xsi_uvproperty.h
	\brief UVProperty is a kind of ClusterProperty object used for storing and accessing the UV 
	information of a cluster. 
	
	UVProperty supports a special API for pinning and unpinning UV components. Pinning acts like a lock.
	When UV components are pinned, they are not affected by operations performed on them.
	For instance, pinned UVs cannot be rotated or scaled in the Texture Editor. 

	\since 10.0 (2012)	
	
	\eg Demonstrates how to use the UVProperty pin/unpin API.
	\code
		using namespace XSI;
		Application app;
		Model root = app.GetActiveSceneRoot();

		X3DObject myCube;
		root.AddGeometry( "Cube", "MeshSurface", "", myCube );

		// install the texture support object
		CValueArray args(4);
		args[0] = CValue( CString("Image") );
		args[1] = CValue(myCube);
		args[2] = CValue((short)1);
		args[3] = CValue(false);

		CStatus st;
		CValue outArg;
		st = app.ExecuteCommand( "BlendInPresets", args, outArg );
		if ( st.GetCode() != CStatus::OK )
		{
			app.LogMessage( "BlendInPresets failed" );
			return;
		}

		args[0] = CValue(myCube);
		args[1] = CValue((LONG)siTxtUV);
		args[2] = CValue((LONG)siTxtDefaultSpherical);
		args[3] = CValue(CString(L"Texture_Support"));

		st = app.ExecuteCommand( "CreateTextureSupport", args, outArg );
		if ( st.GetCode() != CStatus::OK )
		{
			app.LogMessage( "CreateTextureSupport failed" );
			return;
		}

		// Get the uv property on the cube and set some components as pinned or unpinned
		PolygonMesh pm = myCube.GetActivePrimitive().GetGeometry();
		CGeometryAccessor ga = pm.GetGeometryAccessor();
		CRefArray uvs = ga.GetUVs();
		
		UVProperty uvprop( uvs[0] );
			
		// Pin some components 
		CLongArray toPin(5);
		toPin[0] = 0;
		toPin[1] = 5;
		toPin[2] = 10;
		toPin[3] = 15;
		toPin[4] = 20;		
		uvprop.PinComponents( toPin )

		// Use a CBitArray for a fast access to the pinned components
		XSI::CBitArray baComponents;
		uvprop.GetPinComponentArray( baComponents );

		LONG it = baComponents.GetIterator();
		LONG i = 0;
		while (baComponents.GetNextTrueBit(it))
		{
			app.LogMessage( "Pinned component index = " + CString( it ) );
		}	

		// Unpin all
		uvprop.UnPinAllComponents();

		uvprop.GetPinComponentArray( baComponents );
		    
		app.LogMessage( "Number of Pinned components = " + CString( baComponents.GetTrueCount() ) );
		
	\code
	\endcode
 */
//*****************************************************************************

class SICPPSDKDECL UVProperty : public ClusterProperty
{
	public:
	
	/*! Default constructor. */
	UVProperty();
    
	/*! Default destructor. */
	~UVProperty();
    
	/*! Constructor.
	\param in_ref constant reference object.
	*/
	UVProperty(const CRef& in_ref);
    
	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	UVProperty(const UVProperty& in_obj);
    
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
	\return The new UVProperty object.
	*/
	UVProperty& operator=(const UVProperty& in_obj);
    
	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new UVProperty object.
	*/
	UVProperty& operator=(const CRef& in_ref);

	/*! Mark all components referenced by this UV property as pinned.
	\return CStatus::OK success.
	*/
	CStatus PinAllComponents(  );

	/*! Mark specific components referenced by this UV property as pinned.
	\param in_componentArray Array of indices identifying the components to pin.
	\return CStatus::OK success.
	\return CStatus::False Empty indice array..
	\return CStatus::InvalidArgument Indices are out of bound.
	*/
	CStatus PinComponents( const CLongArray& in_componentArray ) ;

	/*! Mark all components referenced by this UV property as unpinned.
	\return CStatus::OK success.
	*/
	CStatus UnPinAllComponents(  ) ;

	/*! Mark specific components referenced by this UV property as unpinned.
	\param in_componentArray Array of indices identifying the components to unpin.
	\return CStatus::OK success.
	\return CStatus::False Empty indice array..
	\return CStatus::InvalidArgument Indices are out of bound.
	*/
	CStatus UnPinComponents( const CLongArray& in_componentArray ) ;

	/*! Returns an array of indices to identify the pinned components referenced by this UV property.
	\return CStatus::OK Success.
	
	*/
	CStatus GetPinComponentArray( CLongArray& out_componentArray ) const;

	/*! Returns a bit array of indices to identify the pinned components referenced by this UV property. This is the 	
	preferred method for accessing the pin component indices of a UV property.

	\return CStatus::OK Success.
	\return CStatus::False No pinned components.
	*/
	CStatus GetPinComponentArray( CBitArray& out_baComponents ) const;

	private:
	UVProperty * operator&() const;
	UVProperty * operator&();
};

};

#endif

