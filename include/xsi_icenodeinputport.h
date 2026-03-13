//*****************************************************************************
/*!
   \file xsi_icenodeinputport.h
   \brief ICENodeInputPort class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIICENODEINPUTPORT_H__
#define __XSIICENODEINPUTPORT_H__

#include <xsi_icenodeport.h>

namespace XSI {

//*****************************************************************************
/*! \class ICENodeInputPort xsi_icenodeinputport.h
	\brief A ICENodeInputPort object represents the input port of an ICENode.

	The ICENodeInputPort cannot connect to more than one %ICENode. An %ICENode
	can have more than one ICENodeInputPort.

	\sa ICENodePort, ICENodeOutputPort, ICENode::GetInputPorts
	\since 7.0
 */
//*****************************************************************************

class SICPPSDKDECL ICENodeInputPort : public ICENodePort
{
public:
	/*! Default constructor. */
	ICENodeInputPort();

	/*! Default destructor. */
	~ICENodeInputPort();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	ICENodeInputPort(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	ICENodeInputPort(const ICENodeInputPort& in_obj);

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
	\return The new ICENodeInputPort object.
	*/
	ICENodeInputPort& operator=(const ICENodeInputPort& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new ICENodeInputPort object.
	*/
	ICENodeInputPort& operator=(const CRef& in_ref);

	/*! Returns the port value as a CValue at a specific frame. The type of the value depends on
	ICENodePort::GetDataType. The value stored in this port is only accessible when the port is not
	connected. If the port is connected, it returns an empty CValue.

	\note This property only returns values for simple types such as float, integer and boolean.
		Returning other value types is not yet supported. If the port is unable to retrieve the
		value, it returns an empty CValue.
	\tip Values for non-supported types can be accessed with ICENodePort::GetParameters.

	\param in_time Time in frames. Defaults to the current frame if \c in_time is set with \c DBL_MAX.
	\return The port value.

	\eg %This example demonstrates how to get a non-connected %ICENodePort value at different times
	\code
		void CreatePrim( const CString& in_presetobj, const CString& in_geometrytype, const CString& in_name, const CString& in_parent );
		CRefArray ApplyOp( const CString& in_presetobj, CString & io_connectionset, const siConstructionMode& in_constructionmode );
		CValue AddICENode( const CValue&  in_presetobj, const CValue&  in_container );
		CValue SetValue( const CString& in_target, const CValue&  in_value, const CValue& in_time );
		void AddAttributeToSetDataICENode( const CValue&  in_setdatanode, const CString& in_attributename, siComponentDataType in_attributetype, siComponentDataContext in_attributecontext, siComponentDataStructure in_attributestructure );
		void SaveKey( const CString& in_inputobjs, CValue& io_time, const CValue& in_value );

		// Create an InitNode
		CreatePrim( L"Grid", L"MeshSurface", L"", L"" );
		ApplyOp( L"ICETree", CString(L"Grid"), siConstructionModeModeling );
		ICENode initDataNode = AddICENode( L"InitializeNode", L"grid.polymsh.ICETree" );
		SetValue( L"grid.polymsh.ICETree.InitDataNode.PredefinedAttributeName", L"EdgeLength", 0 );
		AddAttributeToSetDataICENode( L"grid.polymsh.ICETree.InitDataNode", L"EdgeLength", siComponentDataTypeFloat, siComponentDataContextComponent1D, siComponentDataStructureSingle );

		// Set some keys on the new created port
		ICENodeInputPort nodePort = initDataNode.GetInputPorts().GetItem(L"EdgeLength");

		CValue frame(1.0);
		CValue val(5.0);
		SaveKey( L"grid.polymsh.ICETree.InitDataNode.EdgeLength", frame, val );

		frame = 5.0;
		val = 25.0;
		SaveKey( L"grid.polymsh.ICETree.InitDataNode.EdgeLength", frame, val );

		// Access values on the port
		Application xsi;
		xsi.LogMessage( L"EdgeLentgh value at frame 1: " + CString(nodePort.GetValue(1.0)) );

		nodePort.PutValue( 85.0, 5.0 );
		xsi.LogMessage( L"EdgeLentgh value at frame 5: " + CString(nodePort.GetValue(5.0)) );

		// Expected results:
		// INFO : EdgeLentgh value at frame 1: 5.0
		// INFO : EdgeLentgh value at frame 5: 85.0

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
		void SaveKey( const CString& in_inputobjs, CValue& io_time, const CValue& in_value )
		{
			CValueArray args(8);
			CValue retval;

			args[0]= in_inputobjs;
			args[1]= io_time;
			args[2]= in_value;
			args[3]= -1;
			args[4]= -1;
			args[5]= false;
			args[6]= 0;

			Application app;
			app.ExecuteCommand( L"SaveKey", args, retval );

			io_time = args[1];
			return;
		}
	\endcode
	*/
	CValue GetValue( double in_time=DBL_MAX ) const;

	/*! Sets the port value as a CValue at a specific frame. The type of the value depends on
	ICENodePort::GetDataType. This method can be used only when the port is not connected. If the
	port is connected, the method has no effect.

	\note Only simple types such as float, integer and boolean are supported. Other value types
		are not yet supported.
	\tip Values for non-supported types can be set with ICENodePort.GetParameters.

	\param in_val The port value to set.
	\param in_time Time in frames. Defaults to the current frame if \c in_time is set with \c DBL_MAX.
	\return CStatus::OK success
	\return CStatus::False Trying to set an un-supported value type.
	\return CStatus::Fail Other failure.

	\eg %This example demonstrates how to set a non-connected Node port value at different times
	\code
		void CreatePrim( const CString& in_presetobj, const CString& in_geometrytype, const CString& in_name, const CString& in_parent );
		CRefArray ApplyOp( const CString& in_presetobj, CString & io_connectionset, const siConstructionMode& in_constructionmode );
		CValue AddICENode( const CValue&  in_presetobj, const CValue&  in_container );
		CValue SetValue( const CString& in_target, const CValue&  in_value, const CValue& in_time );
		void AddAttributeToSetDataICENode( const CValue&  in_setdatanode, const CString& in_attributename, siComponentDataType in_attributetype, siComponentDataContext in_attributecontext, siComponentDataStructure in_attributestructure );
		void SaveKey( const CString& in_inputobjs, CValue& io_time, const CValue& in_value );

		// Create an InitNode
		CreatePrim( L"Grid", L"MeshSurface", L"", L"" );
		ApplyOp( L"ICETree", CString(L"Grid"), siConstructionModeModeling );
		ICENode initDataNode = AddICENode( L"InitializeNode", L"grid.polymsh.ICETree" );
		SetValue( L"grid.polymsh.ICETree.InitDataNode.PredefinedAttributeName", L"EdgeLength", 0 );
		AddAttributeToSetDataICENode( L"grid.polymsh.ICETree.InitDataNode", L"EdgeLength", siComponentDataTypeFloat, siComponentDataContextComponent1D, siComponentDataStructureSingle );

		// Set some keys on the new created port
		ICENodeInputPort nodePort = initDataNode.GetInputPorts().GetItem(L"EdgeLength");

		CValue frame(1.0);
		CValue val(5.0);
		SaveKey( L"grid.polymsh.ICETree.InitDataNode.EdgeLength", frame, val );

		frame = 5.0;
		val = 25.0;
		SaveKey( L"grid.polymsh.ICETree.InitDataNode.EdgeLength", frame, val );

		// Access values on the port
		Application xsi;
		xsi.LogMessage( L"EdgeLentgh value at frame 1: " + CString(nodePort.GetValue(1.0)) );

		nodePort.PutValue( 85.0, 5.0 );
		xsi.LogMessage( L"EdgeLentgh value at frame 5: " + CString(nodePort.GetValue(5.0)) );

		// Expected results:
		// INFO : EdgeLentgh value at frame 1: 5.0
		// INFO : EdgeLentgh value at frame 5: 85.0

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
		void SaveKey( const CString& in_inputobjs, CValue& io_time, const CValue& in_value )
		{
			CValueArray args(8);
			CValue retval;

			args[0]= in_inputobjs;
			args[1]= io_time;
			args[2]= in_value;
			args[3]= -1;
			args[4]= -1;
			args[5]= false;
			args[6]= 0;

			Application app;
			app.ExecuteCommand( L"SaveKey", args, retval );

			io_time = args[1];
			return;
		}
	\endcode
	*/
	CStatus PutValue( const CValue& in_val, double in_time=DBL_MAX );

	private:
	ICENodeInputPort * operator&() const;
	ICENodeInputPort * operator&();

};

};

#endif // __XSIICENODEINPUTPORT_H__
