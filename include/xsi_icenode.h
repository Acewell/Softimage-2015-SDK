//*****************************************************************************
/*!
   \file xsi_icenode.h
   \brief ICENode class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIICENODE_H__
#define __XSIICENODE_H__

#include <xsi_projectitem.h>

namespace XSI {

class ICENodePort;
class ICENodeContainer;

//*****************************************************************************
/*! \class ICENode xsi_icenode.h
	\brief The ICENode object represents an effect node in the ICE graph.

	%ICENode objects can be used as building blocks for creating sub-graphs represented as
	ICECompoundNode objects. Custom node operators can be created by SDK users and are
	represented in the C++ API as ICENodeDef objects.

	The %ICENode class API is convenient for accessing the different components of an effect
	node such as its ports, port groups and port group instances. The node ports are organized
	in groups similar to the Softimage operator Port objects, where groups are logical groupings
	of multiple port connections. Other %ICENode objects can connect to a %ICENode object via
	its ports represented as ICENodeInputPort and ICENodeOutputPort objects.

	\sa ICENodeDef, ICENodePort, ICENodeContainer, ICETree, ICEDataModifierNode, ICEDataProviderNode
	\since 7.0

	\eg This example demonstrates how to access the %ICENode elements.

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

			// Log info on the visited node name
			xsi.LogMessage( L"* * *" );

			// Node info
			xsi.LogMessage( L"node: " + in_node.GetFullName() );
			xsi.LogMessage( L"node type: " + in_node.GetType() );
			xsi.LogMessage( L"node proxy class: " + in_node.GetClassIDName() );
			xsi.LogMessage( L"node connected: " + CString(in_node.IsConnected()) );
			xsi.LogMessage( L"node parent: " + SIObject(in_node.GetParent()).GetName() );
			xsi.LogMessage( L"node root: " + in_node.GetRootNodeContainer().GetName() );

			// ICENodePort group info
			LONG nPortGroupCount = in_node.GetPortGroupCount();
			xsi.LogMessage( L"number of groups: " + CString(nPortGroupCount) );

			for (LONG iGroup=0; iGroup<nPortGroupCount; iGroup++)
			{
				LONG nPortsInGroup = in_node.GetPortCount(iGroup);
				xsi.LogMessage( L"number of ports in group " + CString(iGroup) + L": " + CString(nPortsInGroup) );

				LONG nGroupInst = in_node.GetGroupInstanceCount(iGroup);
				xsi.LogMessage( L"number of instances of group " + CString(iGroup) + L": " + CString(nGroupInst) );

				for ( LONG iInst=0; iInst < nGroupInst; iInst++ )
				{
					for ( LONG iPort=0; iPort < nPortsInGroup; iPort++ )
					{
						xsi.LogMessage( L"port " + CString(iPort) + L"," + CString(iGroup) + L"," + CString(iInst) );
						ICENodePort port = in_node.GetPortFromIndex( iPort, iGroup, iInst);
						xsi.LogMessage( L"port name: " + port.GetName() );
						xsi.LogMessage( L"output port: " + CString(port.IsOutput()) );
					}
				}
			}

			// Node input port info
			CRefArray inPorts = in_node.GetInputPorts();
			LONG nInputPortCount = inPorts.GetCount();
			xsi.LogMessage( L"node input ports: " + CString(nInputPortCount) );

			//	Node output port info
			CRefArray outPorts = in_node.GetOutputPorts();
			LONG nOutputPortCount = outPorts.GetCount();
			xsi.LogMessage( L"node output ports: " + CString(nOutputPortCount) );

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
//*****************************************************************************

class SICPPSDKDECL ICENode : public ProjectItem
{
public:
	/*! Default constructor. */
	ICENode();

	/*! Default destructor. */
	~ICENode();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	ICENode(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	ICENode(const ICENode& in_obj);

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
	\return The new ICENode object.
	*/
	ICENode& operator=(const ICENode& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new ICENode object.
	*/
	ICENode& operator=(const CRef& in_ref);

	/*! Returns the enclosing node graph for this node as a ICENodeContainer object. If the node
	is part of a ICECompoundNode, ICENode::GetRootNodeContainer returns a ICECompoundNode object,
	otherwise it returns a ICETree object.
	\return The root ICENodeContainer object.
	 */
	ICENodeContainer GetRootNodeContainer() const;

	/*! Returns the ICENodePort object that matches a specific port name.
	\param in_portname %Port name to match.
	\return ICENodePort object (or an empty object if \c in_portname is invalid).
	*/
	ICENodePort GetPortFromName( const CString& in_portname ) const;

	/*! Returns the ICENodePort object specified by a port index, group index and group instance index.
	\param in_portindex %Port index to match.
	\param in_groupindex %Port group index to match.
	\param in_instanceindex %Group instance index to match. Defaults to 0.
	\return ICENodePort object (or an empty object if input parameters are invalid).
	*/
	ICENodePort GetPortFromIndex
	(
		LONG in_portindex,
		LONG in_groupindex,
		LONG in_instanceindex = 0
	) const;

	/*! Returns the number of port groups for this node operator.
	\return Number of port groups.
	 */
	LONG GetPortGroupCount( ) const;

	/*! Returns the number of ports defined for a specific group.
	\param in_groupindex %Port group index to match.
	\return Number of ports.
	 */
	LONG GetPortCount( LONG in_groupindex ) const;

	/*! Returns the number of instances of a specific group.
	\param groupindex %Port group index to match.
	\return Number of instances.
	 */
	LONG GetGroupInstanceCount( LONG groupindex ) const;

	/*! Returns true if one of the node output ports is connected.
	\return True if node is connected.
	 */
	bool IsConnected( ) const;

	/*! Returns an array of ICENodeInputPort objects as a CRefArray.
	\return Array of references to ICENodeInputPort objects.
	 */
	CRefArray GetInputPorts( ) const;

	/*! Returns an array of ICENodeOutputPort objects as a CRefArray.
	\return Array of references to ICENodeOutputPort objects.
	 */
	CRefArray GetOutputPorts( ) const;

	private:
	ICENode * operator&() const;
	ICENode * operator&();
};

};

#endif // __XSIICENODE_H__
