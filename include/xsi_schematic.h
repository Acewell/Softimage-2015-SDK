//*****************************************************************************
/*!
	\file xsi_schematic.h
	\brief Schematic class declaration.
   
	Copyright 2010 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSISCHEMATIC_H__
#define __XSISCHEMATIC_H__

#include <xsi_view.h>

namespace XSI {

class SchematicNode;

//*****************************************************************************
/*! 
	\class Schematic xsi_schematic.h
	\brief The Schematic class represents the Schematic UI view and gives access to SchematicNode objects.
	
	\sa SchematicNode
    \since 10.0 (2012)
    
    \eg Demonstrates how to access a specific Schematic view object. The example creates a new view if it 
		doesn't already exist in the active layout.
	\code
		using namespace XSI;
				
		Application app;
		
		// Get a schematic view
		Layout layout = app.GetDesktop().GetActiveLayout();
		
		XSI::Schematic schematic = layout.FindView( "MySchematic" );
		
		if ( !schematic.IsValid() )
		{
			app.GetDesktop().GetActiveLayout().CreateView( "Schematic", "MySchematic", schematic );
		}
	
		// Log the top level nodes
		CRefArray nodes = schematic.GetNodes();
	
		for (ULONG i=0; i<nodes.GetCount(); i++)
		{
			SchematicNode node = nodes[i];
			
			LONG x,y,w,h;
			node.GetUIInfo( x,y,w,h );

			app.LogMessage( "*******************************************************************" );
			app.LogMessage( "Name: " + node.GetName() );
			app.LogMessage( "X=" + CString(x) );
			app.LogMessage( "Y=" + CString(y) );
			app.LogMessage( "W=" + CString(w) );
			app.LogMessage( "H=" + CString(h) );
			app.LogMessage( "Expanded=" + CString(node.IsExpanded()) );
			app.LogMessage( "Selected=" + CString(node.IsSelected()) );
			app.LogMessage( "Node count=" + CString(node.GetNodes().GetCount()) );
			app.LogMessage( "Parent object=" + SIObject(node.GetParent()).GetFullName() );
			app.LogMessage( "Underlying object=" + CString( SIObject(node.GetObject()).GetFullName()) );			
		}			
	\endcode
 */
//*****************************************************************************

class SICPPSDKDECL Schematic : public View
{
	public:
	
	/*! Default constructor. */
	Schematic();
    
	/*! Default destructor. */
	~Schematic();
    
	/*! Constructor.
	\param in_ref constant reference object.
	*/
	Schematic(const CRef& in_ref);
    
	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	Schematic(const Schematic& in_obj);
    
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
	\return The new Schematic object.
	*/
	Schematic& operator=(const Schematic& in_obj);
    
	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new Schematic object.
	*/
	Schematic& operator=(const CRef& in_ref);

	/*! Returns the Schematic node representation of a Softimage object.
	\param in_pObject Softimage object.
	\return SchematicNode object
	*/
	SchematicNode FindNode( const CRef& in_pObject ) ;

	/*! Returns an array of SchematicNode objects representing the top level nodes displayed in the view. The array contains 
	only the visible objects in the view. For instance, the scene root object is not visible in a schematic view and is not 
	accessible as a top level node. 
	\return Array of SchematicNode objects.
	*/
	CRefArray GetNodes( ) const;

	/*! Returns an array of SchematicNode objects representing the selected nodes displayed in the view.
	\return Array of SchematicNode objects.
	*/
	CRefArray GetSelectedNodes( ) const;

	private:
	Schematic * operator&() const;
	Schematic * operator&();
};

};

#endif

