//*****************************************************************************
/*!
   \file xsi_icenodecontainer.h
   \brief ICENodeContainer class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIICENODECONTAINER_H__
#define __XSIICENODECONTAINER_H__

#include <xsi_icenode.h>

namespace XSI {

//*****************************************************************************
/*! \class ICENodeContainer xsi_icenodecontainer.h
	\brief The ICENodeContainer object represents the base class for containers in a node graph.

	Node graph containers include ICETree and ICECompoundNode objects. The API of the
	ICENodeContainer allows for visiting all the nodes contained by a graph or sub-graph recursively.

	\sa ICETree, ICECompoundNode, ICENode
	\since 7.0
 */
//*****************************************************************************

class SICPPSDKDECL ICENodeContainer : public ICENode
{
public:
	/*! Default constructor. */
	ICENodeContainer();

	/*! Default destructor. */
	~ICENodeContainer();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	ICENodeContainer(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	ICENodeContainer(const ICENodeContainer& in_obj);

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
	\return The new ICENodeContainer object.
	*/
	ICENodeContainer& operator=(const ICENodeContainer& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new ICENodeContainer object.
	*/
	ICENodeContainer& operator=(const CRef& in_ref);

	/*! Returns each ICENode in the graph. This function is typically used for iterating over an
	entire node graph. The returned array can contain basic ICENode and ICECompoundNode objects
	but not the inner nodes of ICECompoundNode objects. To access these inner-nodes you need to
	call ICENodeContainer::GetNodes on their respective ICECompoundNode parent.

	\return Array of references to ICENode objects.

	\eg This example demonstrates how to traverse a node graph with ICENodeContainer
	\code
		void CreateNodeGraph( );
		void TraverseNodeGraph( const ICENode& in_node );

		// Create the node graph first
		CreateNodeGraph( );

		// Get the ICETree off the cube primitive and start navigating the graph
		Application xsi;
		Selection sel = xsi.GetSelection();
		X3DObject cube = sel[0];

		ICETree cubeICETree = cube.GetActivePrimitive().GetICETrees()[0];

		TraverseNodeGraph( cubeICETree );

		void TraverseNodeGraph( const ICENode& in_node )
		{
			Application xsi;

			// Log the visited node name
			xsi.LogMessage( in_node.GetName() );

			CRefArray nodes;
			if ( in_node.IsA( siICENodeContainerID ) )
			{
				//The input node might be a ICETree or ICECompoundNode, let's get their ICENodes
				ICENodeContainer container( in_node.GetRef() );
				nodes = container.GetNodes();
			}

			// 	Recursively traverse the graph
			for (LONG i=0; i<nodes.GetCount(); i++)
			{
				TraverseNodeGraph( nodes[i] );
			}
		}

		CValue CreateICECompoundNode( const CValue&  in_inputobj, const CString& in_name );
		void CreatePrim( const CString& in_presetobj, const CString& in_geometrytype, const CString& in_name, const CString& in_parent );
		CValue SetValue( const CString& in_target, const CValue&  in_value, const CValue&  in_time = CValue() );
		CRefArray ApplyOp( const CString& in_presetobj, CString & io_connectionset, const siConstructionMode& in_constructionmode );
		CValue AddICENode( const CValue&  in_presetobj, const CValue&  in_container );
		void AddAttributeToSetDataICENode( const CValue&  in_setdatanode, const CString& in_attributename, siComponentDataType in_attributetype, siComponentDataContext in_attributecontext, siComponentDataStructure in_attributestructure );
		void ConnectICENodes( const CValue&  in_inputport, const CValue&  in_outputport );

		// Create a twist deformer graph on a cube
		void CreateNodeGraph( )
		{
			CreatePrim( L"Cube", L"MeshSurface", L"", L"" );
			SetValue( L"cube.polymsh.geom.subdivu", 15, 0 );
			SetValue( L"cube.polymsh.geom.subdivv", 14, 0 );

			CString strCube(L"cube");
			ApplyOp( L"ICETree", strCube, siConstructionModeModeling );

			AddICENode( L"GetDataNode", L"cube.polymsh.ICETree" );
			SetValue( L"cube.polymsh.ICETree.SceneReferenceNode.Reference", L"cube.polymsh.PointPosition" );
			AddICENode( L"RotateVectorNode", L"cube.polymsh.ICETree" );
			AddICENode( L"3DVectorToScalarNode", L"cube.polymsh.ICETree" );
			AddICENode( L"SetData", L"cube.polymsh.ICETree" );
			SetValue( L"cube.polymsh.ICETree.SetData.PredefinedAttributeName", L"PointPosition" );
			AddAttributeToSetDataICENode( L"cube.polymsh.ICETree.SetData", L"PointPosition", siComponentDataTypeVector3, siComponentDataContextComponent0D, siComponentDataStructureSingle );
			ConnectICENodes( L"cube.polymsh.ICETree.port1", L"cube.polymsh.ICETree.SetData.set" );
			ConnectICENodes( L"cube.polymsh.ICETree.RotateVectorNode.vector", L"cube.polymsh.ICETree.SceneReferenceNode.value" );
			ConnectICENodes( L"cube.polymsh.ICETree.SetData.pointposition", L"cube.polymsh.ICETree.RotateVectorNode.result" );
			ConnectICENodes( L"cube.polymsh.ICETree.3DVectorToScalarNode.vector", L"cube.polymsh.ICETree.SceneReferenceNode.value" );
			AddICENode( L"MultiplyNode", L"cube.polymsh.ICETree" );
			ConnectICENodes( L"cube.polymsh.ICETree.MultiplyNode.value1", L"cube.polymsh.ICETree.3DVectorToScalarNode.y" );
			AddICENode( L"ScalarToRotationNode", L"cube.polymsh.ICETree" );
			ConnectICENodes( L"cube.polymsh.ICETree.ScalarToRotationNode.angle", L"cube.polymsh.ICETree.MultiplyNode.result" );
			ConnectICENodes( L"cube.polymsh.ICETree.RotateVectorNode.rotation", L"cube.polymsh.ICETree.ScalarToRotationNode.rotation" );
			SetValue( L"cube.polymsh.ICETree.ScalarToRotationNode.y", 1 );
			SetValue( L"cube.polymsh.ICETree.ScalarToRotationNode.x", 0 );
			SetValue( L"cube.polymsh.ICETree.MultiplyNode.value2", 20 );
			CreateICECompoundNode( L"cube.polymsh.ICETree.3DVectorToScalarNode,cube.polymsh.ICETree.MultiplyNode,cube.polymsh.ICETree.ScalarToRotationNode", L"Compound1");
			CreateICECompoundNode( L"cube.polymsh.ICETree.Compound1.ScalarToRotationNode,cube.polymsh.ICETree.Compound1.MultiplyNode", L"Compound2");
		}

		// Command stubs used by CreateNodeGraph
		CValue CreateICECompoundNode( const CValue&  in_inputobj, const CString& in_name )
		{
			CValueArray args(2);
			CValue retval;

			args[0]= in_inputobj;
			args[1]= in_name;

			Application app;
			CStatus st = app.ExecuteCommand( L"CreateICECompoundNode", args, retval );

			return retval;
		}
		void CreatePrim( const CString& in_presetobj, const CString& in_geometrytype, const CString& in_name, const CString& in_parent )
		{
			CValueArray args(4);
			CValue retval;

			args[0]= in_presetobj;
			args[1]= in_geometrytype;
			args[2]= in_name;
			args[3]= in_parent;

			Application app;
			CStatus st = app.ExecuteCommand( L"CreatePrim", args, retval );

			return;
		}
		CValue SetValue( const CString& in_target, const CValue& in_value, const CValue&  in_time )
		{
			CValueArray args(3);
			CValue retval;

			args[0]= in_target;
			args[1]= in_value;
			args[2]= in_time;

			Application app;
			CStatus st = app.ExecuteCommand( L"SetValue", args, retval );

			return retval;
		}

		CRefArray ApplyOp( const CString& in_presetobj, CString & io_connectionset, const siConstructionMode& in_constructionmode )
		{
			CValueArray args(6);
			CValue retval;

			args[0]=in_presetobj;
			args[1]=io_connectionset;
			args[2]=(LONG)siUnspecified;
			args[3]=(LONG)siPersistentOperation;
			if ( in_constructionmode != siConstructionModeDefault )
			{
				args[5]=(LONG)in_constructionmode;
			}

			Application app;
			CStatus st = app.ExecuteCommand( L"ApplyOp", args, retval );
			io_connectionset=args[1];
			return retval;
		}

		CValue AddICENode( const CValue&  in_presetobj, const CValue&  in_container )
		{
			CValueArray args(2);
			CValue retval;

			args[0]= in_presetobj;
			args[1]= in_container;

			Application app;
			CStatus st = app.ExecuteCommand( L"AddICENode", args, retval );

			return retval;
		}
		void AddAttributeToSetDataICENode( const CValue&  in_setdatanode, const CString& in_attributename, siComponentDataType in_attributetype, siComponentDataContext in_attributecontext, siComponentDataStructure in_attributestructure )
		{
			CValueArray args(5);
			CValue retval;

			args[0]= in_setdatanode;
			args[1]= in_attributename;
			args[2]= (LONG)in_attributetype;
			args[3]= (LONG)in_attributecontext;
			args[4]= (LONG)in_attributestructure;

			Application app;
			CStatus st = app.ExecuteCommand( L"AddAttributeToSetDataICENode", args, retval );

			return;
		}
		void ConnectICENodes( const CValue&  in_inputport, const CValue&  in_outputport )
		{
			CValueArray args(2);
			CValue retval;

			args[0]= in_inputport;
			args[1]= in_outputport;

			Application app;
			CStatus st = app.ExecuteCommand( L"ConnectICENodes", args, retval );

			return;
		}
	\endcode
	 */
	CRefArray GetNodes( ) const;

	/*! Returns each ICEDataModifierNode object in a graph. As for ICENodeContainer::GetNodes, the returned
	array doesn't contain the inner ICEDataModifierNode objects of a ICECompoundNode object. To access the
	inner ICEDataModifierNode objects, call ICENodeContainer::GetDataModifierNodes on their ICECompoundNode parent.
	\eg See the ICEDataModifierNode class reference page for a code example.
	\return Array of references to ICEDataModifierNode objects.
	 */
	CRefArray GetDataModifierNodes( ) const;

	/*! Returns all the ICEDataProviderNode objects of a graph. As for ICENodeContainer::GetNodes, the returned
	array doesn't contain the inner ICEDataProviderNode objects of a ICECompoundNode object. To access the
	inner ICEDataProviderNode objects, call ICENodeContainer::GetDataProviderNodes on their ICECompoundNode parent.
	\eg See the ICEDataProviderNode class reference page for a code example.
	\return Array of references to ICEDataProviderNode objects.
	 */
	CRefArray GetDataProviderNodes( ) const;

	/*! Returns each ICECompoundNode object in a graph. As for ICENodeContainer::GetNodes, the returned
	array doesn't contain the inner ICECompoundNode objects of a ICECompoundNode object. To access the
	inner ICECompoundNode objects, call ICENodeContainer::GetCompoundNodes on their ICECompoundNode parent.
	\eg See the ICECompoundNode class reference page for a code example.
	\return Array of references to ICECompoundNode objects.
	 */
	CRefArray GetCompoundNodes( ) const;

	private:
	ICENodeContainer * operator&() const;
	ICENodeContainer * operator&();

};

};

#endif // __XSIICENODECONTAINER_H__
