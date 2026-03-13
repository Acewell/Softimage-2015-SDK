//*****************************************************************************
/*!
   \file xsi_icenodecontext.h
   \brief ICENodeContext class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIICENODECONTEXT_H__
#define __XSIICENODECONTEXT_H__

#include <xsi_context.h>
#include <xsi_time.h>
#include <xsi_longarray.h>

namespace XSI {

class CStatus;
class CBaseDataArray;
class CBaseDataArray2D;
class CIndexSet;

//*****************************************************************************
/*! \class ICENodeContext xsi_icenodecontext.h
	\brief %ICENodeContext is used for accessing/handling custom node graph data. Instances
	of this object can pass information to the C++ API callbacks that implement the custom
	node plug-in item.

	\sa ICENode, PluginRegistrar::RegisterICENode, \xt cb_icenodes %ICENode Callbacks \endxt
	\since 7.0
*/
//*****************************************************************************

class SICPPSDKDECL ICENodeContext : public Context
{
public:

	friend class CBaseDataArray;
	friend class CBaseDataArray2D;
	friend class CIndexSet;
	friend class CICEGeometry;
	friend class CICEPortState;

	/*! Default constructor. */
	ICENodeContext();

	/*! Default destructor. */
	~ICENodeContext();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	ICENodeContext(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	ICENodeContext(const ICENodeContext& in_obj);

	/*! Returns true if a given class type is compatible with this API class.
	\param in_ClassID class type.
	\return true if the class is compatible, false otherwise.
	*/
	bool IsA( siClassID in_ClassID) const;

	/*! Returns the type of the API class.
	\return The class type.
	*/
	siClassID GetClassID() const;

	/*! Creates an object from another object.
	\param in_obj constant class object.
	\return The new ICENodeContext object.
	*/
	ICENodeContext& operator=(const ICENodeContext& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new ICENodeContext object.
	*/
	ICENodeContext& operator=(const CRef& in_ref);

	/*! Returns the number of instances for a given group.
	\param in_grpUniqID %Group index to query
	\retval out_inst_count Number of instances
	\return CStatus::OK success
	*/
	CStatus GetGroupInstanceCount( ULONG in_grpUniqID, ULONG& out_inst_count ) const;

	/*! Returns the number of threads used during the \xt cb_ICENode_Evaluate Evaluate \endxt callback.
	\return Thread count.
	*/
	ULONG GetEvaluationThreadCount( ) const;

	/*! Returns the current evaluation thread index. If called from \xt cb_ICENode_Evaluate Evaluate \endxt,
	the index ranges between 0 and GetEvaluationThreadCount()-1. Returns 0 if called from either the
	\xt cb_ICENode_BeginEvaluate BeginEvaluate \endxt or \xt cb_ICENode_EndEvaluate EndEvaluate \endxt callback.
	\return ULONG Thread index.
	*/
	ULONG GetCurrentThreadIndex( ) const;

	/*! Returns the total number of elements to process during the evaluation of an ICENode. Returns 0 if the
	operation fails. The return value can be set by the custom ICENode if an output port is set with the
	::siICENodeContextElementGenerator context type.
	\return ULONG Number of elements.
	\sa ICENodeContext::PutNumberOfElementsToProcess, ICENodeDef::AddOutputPort
	*/
	ULONG GetNumberOfElementsToProcess( ) const;

	/*! Sets the number of elements to generate for an element generator node. The new value will affect the current
	output port being evaluated.
	\param in_nElements Number of elements. The value is ignored if the current port has not been set with the
	::siICENodeContextElementGenerator context type.
	\return CStatus::OK Success.
	\return CStatus::Fail Operation failed.
	\sa ICENodeContext::GetNumberOfElementsToProcess, ICENodeDef::AddOutputPort

	\eg %This example shows how to set the number of elements to generate for an element generator type of ICENode.
	The \xt cb_ICENode_BeginEvaluate BeginEvaluate \endxt callback must be used for calling
	ICENodeContext::PutNumberOfElementsToProcess.
	\code

		XSIPLUGINCALLBACK CStatus MyICENodeGenerator_BeginEvaluate( ICENodeContext& in_ctxt )
		{
			// Get some values from an input port
			CDataArrayLong inSize( in_ctxt, ID_Size );

			// Total number of elements to generate
			ULONG nSize = inSize[ 0 ];
			ULONG nElements = nSize * nSize;
			in_ctxt.PutNumberOfElementsToProcess( nElements );

			return CStatus::OK;
		}
	\endcode
	*/
	CStatus PutNumberOfElementsToProcess( ULONG in_nElements );

	/*! Returns the resolved port types for the specified ICENodePort.
	\param in_nPortID Index of the port to query
	\retval out_type Data type for this port (see ICENodePort::GetDataType)
	\retval out_struct Structure for this port (see ICENodePort::GetStructureType)
	\retval out_context Context for this port (see ICENodePort::GetContextType)
	\return CStatus::OK success
	*/
	CStatus GetPortInfo( ULONG in_nPortID, siICENodeDataType& out_type, siICENodeStructureType& out_struct, siICENodeContextType& out_context ) const;

	/*! Returns the resolved port types for the specified ICENodePort. The method also returns the resolved custom data type identifier
	if the port type is set with ::siICENodeDataCustomType, otherwise the string returned is empty.
	\param in_nPortID Index of the port to query
	\retval out_type Data type for this port (see ICENodePort::GetDataType)
	\retval out_struct Structure for this port (see ICENodePort::GetStructureType)
	\retval out_context Context for this port (see ICENodePort::GetContextType)
	\retval out_customDataType The custom data type identifier for this port.
	\return CStatus::OK success
	*/
	CStatus GetPortInfo(	ULONG in_nPortID,
							siICENodeDataType& out_type,
							siICENodeStructureType& out_struct,
							siICENodeContextType& out_context,
							CString& out_customDataType ) const;

	/*! Returns the unique identifier of the output port being evaluated.
	\return CStatus::OK success
	*/
	ULONG GetEvaluatedOutputPortID( ) const;

	/*! Returns the evaluation time. For a custom ICENode, the evaluation time is not necessarily the same as the current
	scene time or that it is evaluated just once per frame.
	\return CTime Evaluation time
	*/
	CTime GetTime() const;

	/*! Returns the current evaluation phase index when the ICENode is configured for multi-phase evaluation. This method returns
	\c UINT_MAX if the node threading mode is not set accordingly or the method	is called during the last processing phase.
	\return Phase index.
	\sa ICENodeDef::PutThreadingModel, ::siICENodeMultiEvaluationPhase,
		ICENodeContext::AddEvaluationPhaseInputPorts, ICENodeContext::SetLastEvaluationPhase
	\since 8.0 (2010)
	*/
	ULONG GetEvaluationPhaseIndex( ) const;

	/*! Sets the current evaluation phase as the last phase to process. This tells Softimage to pull the input port(s) data
	for the final processing phase. This method is enabled only when the node threading model is set to
	::siICENodeMultiEvaluationPhase.
	\return CStatus::OK Operation succeeded.
	\sa ICENodeContext::GetEvaluationPhaseIndex, ICENodeContext::AddEvaluationPhaseInputPorts
	\since 8.0 (2010)
	*/
	CStatus SetLastEvaluationPhase( );

	/*! Adds an input port to evaluate for the current evaluation phase. This method must be used in the context of a custom
	node with multi-evaluation processing and from the \xt cb_ICENode_SubmitEvaluationPhaseInfo SubmitEvaluationPhaseInfo \endxt
	callback. The method is enabled only when the node threading model is set to ::siICENodeMultiEvaluationPhase.

	AddEvaluationPhaseInputPort takes a port identifier, as specified with ICENodeDef::AddInputPort, and an optional array of port
	instance numbers. By default, all port instances are evaluated, but you can specify the port instance number(s) corrsponding to
	which port(s) you want to be evaluated in the \c in_portInstances array. You can call AddEvaluationPhaseInputPort multiple
	times to specify multiple ports to evaluate. Ports are evaluated in the same order in which they are specified.

	Here are some important rules to follow when specifying the input ports to pull:
	\li Except for singleton contexts, ports with similar context types should be prepared together in the same phase for better performance.
	\li Unless input port contexts are specified as singletons, ports specified during the last phase must match the context of the output port(s).

	\param in_portid A unique identifier describing the input port.
	\param in_portInstances A CLongArray containing the instance(s) of the port(s) to evaluate.
	\return CStatus::OK Operation succeeded.
	\return CStatus::InvalidArgument Input port or instances are invalid.
	\sa ICENodeContext::GetEvaluationPhaseIndex, ICENodeContext::SetLastEvaluationPhase, ICENodeDef::AddInputPort
	\since 8.0 (2010)
	*/
	CStatus AddEvaluationPhaseInputPort( ULONG in_portid, const XSI::CLongArray& in_portInstances=XSI::CLongArray() );

	/*! In ICE, the data flowing in an ICETree is \a constant by default. For instance, the element data of a particle cloud do not
	vary at each evaluation when it's constant. In this case, the data array of an input port will always be set with one single
	value. SetAsElementDataVarying can be used to force the element data to vary independently of the input data state.

	A typical use of SetAsElementDataVarying is when a custom node needs to output data randomly regardless of the input data state.
	The \xm CustomICENodes/netview_CustomICENodes GridWalker example \endxm uses constants for all inputs and calling SetAsElementDataVarying will
	allow the \c GridWalker node to set the data for all particle elements.

	\note Calling this method could lead to performance issues when it is not strictly required.
	\return CStatus::OK Operation succeeded.
	\since 8.0 (2010)
	*/
	CStatus SetAsElementDataVarying( );

	/*! Forces the node to evaluate frame by frame regardless of the overall graph state. You can use this function instead of
	connecting the \xl CurrentFrameNode as input to the custom node.
	\return CStatus::OK Operation succeeded.
	\since 8.0 (2010)
	*/
	CStatus SetAsTimeVarying( );

	private:

	// API for handling the data array
	CStatus AcquireIndexSet( CIndexSet& io_set ) const;
	CStatus AcquireIndexSetFromPort( CIndexSet& io_set, ULONG in_nInputPortID, ULONG in_nInstanceIndex ) const;
	CStatus ReleaseIndexSet( CIndexSet& io_set );
	CStatus RemoveElementFromIndexSet( CIndexSet& io_set, LONG in_index, LONG& out_nNewIndex, bool& out_bEnd );
	CStatus GetFilteredCountFromIndexSet( const CIndexSet& in_set, ULONG& out_ulCount ) const;
	CStatus AcquireInputDataArray( CBaseDataArray& io_dataArray, siICENodeDataType in_requiredDataType, ULONG in_port_uniq_index, ULONG in_grp_instance_index ) const;
	CStatus CopyFromInputDataArray( CBaseDataArray& io_dataArray, siICENodeDataType in_requiredDataType, ULONG in_port_uniq_index, ULONG in_grp_instance_index ) const;
	CStatus AcquireOutputDataArray( CBaseDataArray& io_dataArray, siICENodeDataType in_requiredDataType ) const;
	CStatus ReleaseDataArray( CBaseDataArray& io_dataArray );

	CStatus SetCustomTypeData( CBaseDataArray& io_dataArray, ULONG in_nArrayIndex, const unsigned char* in_ptr, ULONG in_nSize );
	CStatus GetCustomTypeData( CBaseDataArray& io_dataArray, ULONG in_nArrayIndex, const unsigned char** out_pptr, ULONG& out_nSize ) const;
	CStatus GetCustomTypeData( CBaseDataArray& io_dataArray, ULONG in_nArrayIndex, unsigned char** out_pptr, ULONG& out_nSize ) const;
	unsigned char* ResizeCustomTypeData( CBaseDataArray& io_dataArray, ULONG in_index, ULONG in_nSize );

	CStatus SetStringData( CBaseDataArray& io_dataArray, ULONG in_nArrayIndex, const wchar_t* in_ptr, ULONG in_nSize );
	CStatus GetStringData( CBaseDataArray& io_dataArray, ULONG in_nArrayIndex, const wchar_t** out_pptr, ULONG& out_nSize ) const;
	CStatus GetStringData( CBaseDataArray& io_dataArray, ULONG in_nArrayIndex, wchar_t** out_pptr, ULONG& out_nSize ) const;
	wchar_t* ResizeStringData( CBaseDataArray& io_dataArray, ULONG in_index, ULONG in_nSize );

	// API for handling the 2D data array
	CStatus AcquireInputDataArray2D( CBaseDataArray2D& io_dataArray, siICENodeDataType in_requiredDataType, ULONG in_port_uniq_index, ULONG in_grp_instance_index ) const;
	CStatus CopyFromInputDataArray2D( CBaseDataArray2D& io_dataArray, siICENodeDataType in_requiredDataType, ULONG in_port_uniq_index, ULONG in_grp_instance_index ) const;
	CStatus AcquireOutputDataArray2D( CBaseDataArray2D& io_dataArray, siICENodeDataType in_requiredDataType ) const;
	CStatus ResizeSubArray( CBaseDataArray2D& io_dataArray, ULONG in_nArrayIndex, ULONG in_nSize, void*& out_ppData, ULONG& out_nCount, ULONG& out_nStartBit ) ;
	CStatus GetSubArray( CBaseDataArray2D& io_dataArray, ULONG in_nArrayIndex, void*& out_ppData, ULONG& out_nCount, ULONG& out_nStartBit ) const;

	CStatus SetCustomTypeData2D( CBaseDataArray& io_dataArray, ULONG in_nAccessIndex, ULONG in_nArrayIndex, const unsigned char* in_ptr, ULONG in_nSize );
	CStatus GetCustomTypeData2D( CBaseDataArray& io_dataArray, ULONG in_nAccessIndex,	ULONG in_nArrayIndex, const unsigned char**	out_pptr, ULONG& out_nSize ) const;
	CStatus GetCustomTypeData2D( CBaseDataArray& io_dataArray, ULONG in_nAccessIndex,	ULONG in_nArrayIndex, unsigned char**	out_pptr, ULONG& out_nSize ) const;
	unsigned char* ResizeCustomTypeData2D( CBaseDataArray& io_dataArray, ULONG in_nAccessIndex, ULONG in_nArrayIndex, ULONG in_nSize );

	CStatus SetStringData2D( CBaseDataArray& io_dataArray, ULONG in_nAccessIndex, ULONG in_nArrayIndex, const wchar_t* in_ptr, ULONG in_nCount );
	CStatus GetStringData2D( CBaseDataArray& io_dataArray, ULONG in_nAccessIndex,	ULONG in_nArrayIndex, const wchar_t**	out_pptr, ULONG& out_nCount ) const;
	CStatus GetStringData2D( CBaseDataArray& io_dataArray, ULONG in_nAccessIndex,	ULONG in_nArrayIndex, wchar_t**	out_pptr, ULONG& out_nCount ) const;
	wchar_t* ResizeStringData2D( CBaseDataArray& io_dataArray, ULONG in_nAccessIndex, ULONG in_nArrayIndex, ULONG in_nCount );

	ICENodeContext * operator&() const;
	ICENodeContext * operator&();
};

};
#endif // __XSIICENODECONTEXT_H__
