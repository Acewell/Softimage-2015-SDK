//*****************************************************************************
/*!
	\file xsi_schematicnode.h
	\brief SchematicNode class declaration.
   
	Copyright 2010 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSISCHEMATICNODE_H__
#define __XSISCHEMATICNODE_H__

// make sure windows.h doesn't rename SchematicNode::GetObjet to GetObjectW
#undef GetObject

#include <xsi_uiobject.h>

namespace XSI {

//*****************************************************************************
/*! 
	\class SchematicNode xsi_schematicnode.h
	\brief The SchematicNode class represents a UI node as displayed in a Schematic view.
	\sa SchematicNode
    \since 10.0 (2012)

	\eg Demonstrates how to access all nodes in a Schematic view object.     
	\code
		using namespace XSI;
		
		void LogNode( SchematicNode& in_node );
		
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
			SchematicNode node = nodes[0];
			
			LogNode( node );
		}			
		
		void LogNode( SchematicNode& node )
		{
			LONG x,y,w,h;
			node.GetUIInfo( x,y,w,h );

			Application app;
			
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
			
			CRefArray nodes = node.GetNodes();
			
			for ( LONG i=0; i<nodes.GetCount(); i++ )
			{
				SchematicNode node = nodes[i];
				LogNode( node );
			}
		}
	\endcode
    
 */
//*****************************************************************************

class SICPPSDKDECL SchematicNode : public UIObject
{
	public:
	
	/*! Default constructor. */
	SchematicNode();
    
	/*! Default destructor. */
	~SchematicNode();
    
	/*! Constructor.
	\param in_ref constant reference object.
	*/
	SchematicNode(const CRef& in_ref);
    
	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	SchematicNode(const SchematicNode& in_obj);
    
	/*! Returns true if a given class type is compatible with this API class.
	\param in_ClassID class type.
	\return true if the class is compatible, false otherwise.
	*/
	bool IsA( siClassID in_ClassID ) const;
    
	/*! Returns the type of the API class.
	\return The class type.
	*/
	siClassID GetClassID() const;
    
	/*! Creates an object from another object. The newly created object is set to
	empty if the input object is not compatible.
	\param in_obj constant class object.
	\return The new SchematicNode object.
	*/
	SchematicNode& operator=(const SchematicNode& in_obj);
    
	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new SchematicNode object.
	*/
	SchematicNode& operator=(const CRef& in_ref);

	/*! Determine if the node is expanded or not. Children nodes are set as expanded if their parent are also expanded.
	\return True if expanded, false otherwise.
	*/
	bool IsExpanded( ) const;

	/*! Set the node as expanded or collapsed.
	\param in_bState true to expand or false to collapse the node.
	\return CStatus::OK
	*/
	CStatus PutExpanded( bool in_bState );

	/*! Determine if the node is selected (node or branch).
	\return Branch flag: siNode (node selected), siBranch (branch selected), siNotSelected (node is not selected). Children nodes are also set 
	as branch selected when the top parent is branch selected.
	*/
	siBranchFlag IsSelected( ) const;

	/*! Set the x and y position of the node. The position is in screen coordinates and is relative to the node's schematic view.
	\param in_x Position in x.
	\param in_y Position in y.
	\return CStatus::Ok Success
	*/
	CStatus Move( LONG in_x, LONG in_y ) ;

	/*! Returns the children nodes of this Schematic node as an array of SchematicNode objects. Only visible nodes are returned.
	\return Array of SchematicNode objects.
	*/
	CRefArray GetNodes( ) const;

	/*! Returns the node's underlying Softimage object.
	\return Softimage object.
	*/
	CRef GetObject( ) const;

	/*! Returns the 2D coordinates and size of the node. Cooordinate units are in screen coordinates and relative to the node's schematic view.
	\param out_x Position in x.
	\param out_y Position in y.
	\param out_w Width.
	\param out_h Height.
	\return CStatus::Ok Success
	*/
	CStatus GetUIInfo( LONG& out_x, LONG& out_y, LONG& out_w, LONG& out_h ) const;

	private:
	SchematicNode * operator&() const;
	SchematicNode * operator&();
};

};

#endif

