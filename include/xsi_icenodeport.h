//*****************************************************************************
/*!
   \file xsi_icenodeport.h
   \brief ICENodePort class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIICENODEPORT_H__
#define __XSIICENODEPORT_H__

#include <xsi_siobject.h>

namespace XSI {

//*****************************************************************************
/*! \class ICENodePort xsi_icenodeport.h
	\brief ICENodePort is the base class for ICENode ports such as ICENodeInputPort and
	ICENodeOutputPort.

	A ICENodePort is a connection point on a ICENode and connects to other ICENodePort objects.
	ICENodePort may be connected to something or not connected at all. Ports are organized in
	groups similar to the Softimage operator Port objects where groups are logical groupings of
	multiple port connections.

	\sa ICENodeInputPort, ICENodeOutputPort, ICENode
	\since 7.0

	\eg This example shows how to access the ports of ICENode objects
	\code
		void CreateNodeGraph( );
		void TraverseNodeGraph( const ICENode& in_node );
		void LogICENodePort( const ICENodePort& in_nodeport );

		// Create the node graph first
		CreateNodeGraph( );

		// Get the ICETree off the cube primitive and start navigating the graph
		Application xsi;
		Selection sel = xsi.GetSelection();
		X3DObject cube = sel[0];

		ICETree cubeICETree = cube.GetActivePrimitive().GetICETrees()[0];

		TraverseNodeGraph( cubeICETree );

		// ICENodePort introspection
		void LogICENodePort( const ICENodePort& in_nodeport )
		{
			Application xsi;

			// Log info
			xsi.LogMessage( L"* * *" );

			xsi.LogMessage( L"node port: " + in_nodeport.GetFullName() );
			xsi.LogMessage( L"node port parent: " + SIObject(in_nodeport.GetParent()).GetFullName() );
			xsi.LogMessage( L"node port class: " + in_nodeport.GetClassIDName() );
			xsi.LogMessage( L"output node port: " + CString(in_nodeport.IsOutput()) );
			xsi.LogMessage( L"connected: " + CString(in_nodeport.IsConnected()) );
			xsi.LogMessage( L"group port index: " + CString(in_nodeport.GetIndex()) );
			xsi.LogMessage( L"group index: " + CString(in_nodeport.GetGroupIndex()) );
			xsi.LogMessage( L"group instance index: " + CString(in_nodeport.GetGroupInstanceIndex() ) );
			xsi.LogMessage( L"data type: " + CString(in_nodeport.GetDataType()) );
			xsi.LogMessage( L"structure type: " + CString(in_nodeport.GetStructureType()) );
			xsi.LogMessage( L"evaluation context type: " + CString(in_nodeport.GetContextType()) );

			CRefArray connectednodes = in_nodeport.GetConnectedNodes();
			LONG nCount = connectednodes.GetCount();
			xsi.LogMessage( L"connected nodes: " + CString(nCount) );
			for (LONG i=0; i<nCount; i++)
			{
				xsi.LogMessage( L"connected node: " + SIObject(connectednodes[i]).GetName() );
			}

			// Log port parameters
			CRefArray params = in_nodeport.GetParameters();
			for (LONG i=0; i<params.GetCount(); i++)
			{
				Parameter param = params[i];
				xsi.LogMessage( L"parameter: " + param.GetScriptName() + L":" + CString(param.GetValue()) );
			}
		}

		void TraverseNodeGraph( const ICENode& in_node )
		{
			Application xsi;

			// Log info on the visited node name
			xsi.LogMessage( L"* * * * * * * * * * " );
			xsi.LogMessage( L"node: " + in_node.GetFullName() );

			// Node input port info
			CRefArray inPorts = in_node.GetInputPorts();
			LONG nCount = inPorts.GetCount();
			xsi.LogMessage( L"node input ports: " + CString(nCount) );

			for (LONG i=0; i<nCount; i++)
			{
				LogICENodePort( inPorts[i] );
			}

			// Node output port info
			CRefArray outPorts = in_node.GetOutputPorts();
			nCount = outPorts.GetCount();
			xsi.LogMessage( L"node output ports: " + CString(nCount) );

			for (LONG i=0; i<nCount; i++)
			{
				LogICENodePort( outPorts[i] );
			}

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

class SICPPSDKDECL ICENodePort : public SIObject
{
public:
	/*! Default constructor. */
	ICENodePort();

	/*! Default destructor. */
	~ICENodePort();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	ICENodePort(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	ICENodePort(const ICENodePort& in_obj);

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
	\return The new ICENodePort object.
	*/
	ICENodePort& operator =(const ICENodePort& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new ICENodePort object.
	*/
	ICENodePort& operator =(const CRef& in_ref);

	/*! Returns a boolean value indicating whether the port is connected (true) or not (false).
	\return True if port is connected.
	\sa ICENode::IsConnected
	 */
	bool IsConnected() const;

	/*! Returns a boolean value indicating whether the port direction is output (true) or input (false).
	\return The port direction flag.
	\sa ICENodeOutputPort
	 */
	bool IsOutput() const;

	/*! Returns the index of this port within its port group.
	\note This property refers to the index of the port within the ICENodePort group. It is different
		from the index used to access the array of ports returned by ICENode::GetInputPorts,
		ICENode::GetOutputPorts, and ICENodePort::GetConnectedPorts.
	\return The port index.
	 */
	LONG GetIndex() const;

	/*! Returns the node port group instance that this port belongs to. There may be many objects of the
	same type connected to the same port group. Each ICENode is connected to a port group instance, and
	within the port group instance there may be many ports.
	\return The port group instance index.
	 */
	LONG GetGroupInstanceIndex() const;

	/*! Returns the node port group index to which this port belongs.
	\return The port group index.
	 */
	LONG GetGroupIndex() const;

	/*! Returns the data type for this port as an \link siICENodeDataType \endlink value. The returned type
	identifies the data that can travel through this port.
	\return The port data type.
	 */
	XSI::siICENodeDataType GetDataType() const;

	/*! Returns the data structure type for this port as an \link siICENodeStructureType \endlink value. The
	returned type identifies how the data is structured: data can be a single element or an array.
	\return The port data structure type.
	 */
	XSI::siICENodeStructureType GetStructureType() const;

	/*! Returns the context type for this port as an \link siICENodeContextType \endlink value. The returned
	type identifies the element set associated with the data (cardinality), such as vertices, polygons, or
	newly created particles.
	\return The port evaluation context type.
	 */
	XSI::siICENodeContextType GetContextType() const;

	/*! Returns all the ICENodePort objects connected to this port. ICENodeInputPort objects can only have one
	connected port; on the other hand, ICENodeOutputPort objects can have multiple ports connected. The returned
	array is empty if the port is not connected.
	\return Array of references to the connected ports.
	 */
	CRefArray GetConnectedPorts( ) const;

	/*! Returns all the ICENode objects connected to this port. ICENodeInputPort objects can only have one
	connected node; ICENodeOutputPort objects can have multiple nodes connected.
	\return Array of references to the connected ICENode objects.
	 */
	CRefArray GetConnectedNodes( ) const;

	/*! Returns all the Parameter objects defined for this port. For instance, calling ICENodePort::GetParameters
	on a port which supports the ::siICENodeDataVector3 data type will return an array of 3 parameters:
	\c x, \c y, \c z. These parameters can then be used for setting keys for instance.
	\return Array of references to the parameters for this port.
	 */
	CRefArray GetParameters() const;

	/*! Returns an array of custom data types defined for this %ICENodePort. Custom data types are defined by custom ICENodes and
	are used as data type for defining custom ICEPorts and ICEAttributes.
	\return Array of custom data type names. Returns an empty array if no custom types are defined on this port.
	\sa ICENodeDef::DefineCustomType
	\sa ICEAttribute::GetCustomDataTypes
	\since 8.0 (2010)

	\eg This example demonstrates how to access custom data types from %ICENodePort objects.
	\code
		Application app;

		// Loads the GridWalker custom node plug-in from the examples workgroup
		CString strWrkgrp = CUtils::BuildPath( app.GetInstallationPath(siFactoryPath ), "XSISDK", "examples", "workgroup" );
		app.AddWorkgroup( strWrkgrp  );

		// Opens the GridWalker scene containing custom data types
		CValueArray args(2);
		CValue retval;
		args[0] = CUtils::BuildPath( strWrkgrp, "Addons", "CustomICENodes", "Data", "Project", "Scenes", "GridWalker" ) + ".scn";
		args[2] = false;
		app.ExecuteCommand( "OpenScene", args, retval );

		// Logs ports with custom data types
		CStringArray strNoFamily;
		CString strNoType;
		ICETree tree = app.GetActiveSceneRoot().FindChild("grid", strNoType, strNoFamily).GetActivePrimitive().GetICETrees()[0];
		ICENode node = tree.GetNodes().GetItem("GridWalker");

		CRefArray inPorts = node.GetInputPorts();
		for ( ULONG i=0; i<inPorts.GetCount(); i++ )
		{
			ICENodePort p = inPorts[i];
			if ( p.GetDataType() == siICENodeDataCustomType )
			{
				app.LogMessage( CString("Custom data type for input port <") + p.GetName() + ">: " + p.GetCustomDataTypes()[0] );
			}
		}

		CRefArray outPorts = node.GetOutputPorts();
		for ( ULONG i=0; i<outPorts.GetCount(); i++ )
		{
			ICENodePort p = outPorts[i];
			if ( p.GetDataType() == siICENodeDataCustomType )
			{
				app.LogMessage( CString("Custom data type for output port <") + p.GetName() + ">: " + p.GetCustomDataTypes()[0] );
			}
		}

		// Output:
		// # INFO : Custom data type for input port <InState>: GridWalkState_v1
		// # INFO : Custom data type for output port <OutState>: GridWalkState_v1
	\endcode
	*/
	CStringArray GetCustomDataTypes( ) const;

	private:
	ICENodePort * operator&() const;
	ICENodePort * operator&();

};

};

#endif // __XSIICENODEPORT_H__
