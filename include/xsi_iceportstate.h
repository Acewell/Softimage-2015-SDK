//*****************************************************************************
/*!
	\file xsi_iceportstate.h
	\brief CICEPortState class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIICEPORTSTATE_H__
#define __XSIICEPORTSTATE_H__

namespace XSI {

class ICENodeContext;
//*****************************************************************************
/*! \class CICEPortState xsi_iceportstate.h
	\brief CICEPortState is used for accessing the state of a custom ICENode input port from the
	\xt cb_ICENode_BeginEvaluate BeginEvaluate \endxt callback.

	\idx dirty states:checking for port changes \endidx
	The state information is normally used by custom nodes for managing internal cache in order to optimize
	the computation and improve performance. The following port states are supported:

		\li CICEPortState::siTimeDirtyState: This state is true if the input data is animated and the time line has changed.
		\li CICEPortState::siDataDirtyState: This state is true when the data going through the port have been modified.
			CICEPortState::siTimeDirtyState is always true when \c siDataDirtyState is set to true. Disconnecting a port
			will set \c siDataDirtyState to true.
		\li CICEPortState::siTypeDirtyState: This state is true if the port connection type has changed. When
			CICEPortState::siTypeDirtyState is true all other states are also true.

	\tip CICEPortState::siAnyDirtyState can be used to test if at least one state is dirty.
	\note CICEPortState cannot be used in the \xt cb_ICENode_Evaluate Evaluate \endxt callback.

	\since 8.0 (2010)

	\eg This example logs the dirty state information of input ports by using the %CICEPortState class. For a more detailed example see the
		\xm CustomICENodes/netview_CustomICENodes PortStateObserver custom ICE node \endxm example
	\code
	XSIPLUGINCALLBACK CStatus Port_State_Observer_BeginEvaluate( ICENodeContext& in_ctxt )
	{
		CICEPortState portGeomGroup( in_ctxt, ID_IN_GeometryGroup );
		CICEPortState portGeomCurve( in_ctxt, ID_IN_NurbsCurve );
		CICEPortState portGeomMesh( in_ctxt, ID_IN_MeshSurf );
		CICEPortState portGeomNurbsSurf( in_ctxt, ID_IN_NurbsSurf );
		CICEPortState portGeomCloud( in_ctxt, ID_IN_PointCloud );
		CICEPortState data( in_ctxt, ID_IN_Data );

		double dCurrentFrame = in_ctxt.GetTime();
		LogPortStates( portGeomGroup, L"GeometryGroup", dCurrentFrame );
		LogPortStates( portGeomCurve, L"NurbsCurve", dCurrentFrame );
		LogPortStates( portGeomMesh, L"MeshSurf", dCurrentFrame );
		LogPortStates( portGeomNurbsSurf, L"NurbsSurf", dCurrentFrame );
		LogPortStates( portGeomCloud, L"PointCloud", dCurrentFrame );
		LogPortStates( data, L"Data", dCurrentFrame );
		return CStatus::OK;
	}

	static void LogPortStates( CICEPortState& in_port, const CString& in_portName, double in_dCurrentFrame )
	{
		if ( in_port.IsDirty( CICEPortState::siAnyDirtyState ) )
		{
			bool bTypeDirtyState = in_port.IsDirty( CICEPortState::siTypeDirtyState );
			bool bDataDirtyState = in_port.IsDirty( CICEPortState::siDataDirtyState );
			bool bTimeDirtyState = in_port.IsDirty( CICEPortState::siTimeDirtyState );

			in_port.ClearState();

			Application app;

			// Don't log redundant information:
			// bTypeDirtyState always implies bDataDirtyState + bTimeDirtyState
			// bDataDirtyState always implies bTimeDirtyState

			if ( bTypeDirtyState)
			{
				app.LogMessage( ">>> Port " + in_portName + " siTypeDirtyState at frame " + CString(in_dCurrentFrame) + " is dirty" );
			}
			else
			{
				if ( bDataDirtyState)
				{
					app.LogMessage( ">>> Port " + in_portName + " siDataDirtyState at frame " + CString(in_dCurrentFrame) + " is dirty" );
				}
				else if ( bTimeDirtyState)
				{
					app.LogMessage( ">>> Port " + in_portName + " siTimeDirtyState at frame " + CString(in_dCurrentFrame) + " is dirty" );
				}
			}
		}
	}
	\endcode
 */
//*****************************************************************************

class SICPPSDKDECL CICEPortState
{
	public:
	friend class ICENodeContext;

	/*! Defines the supported dirty port state types.
	*/
	enum DirtyState
	{
		siTypeDirtyState	= 1<<0,	/*!< %Port type change. This state is true if the port connection type has changed.
											When \c siTypeDirtyState is true all other states are also true. */
		siDataDirtyState	= 1<<1, /*!< Data change. This state is true when the data going through the port has been
											modified. \c siTimeDirtyState is always true when \c siDataDirtyState is set to true. */
		siTimeDirtyState	= 1<<2,	/*!< Time change. This state is true if the input data is animated and the time line has changed.*/
		siAnyDirtyState		= siTypeDirtyState|siDataDirtyState|siTimeDirtyState /*!< Any type. */
	};

	/*! Constructor for creating and initializing an instance of CICEPortState.
	\param in_ctxt ICENode evaluation context.
	\param in_nInputPortID Input port identifier.
	\param in_nInstanceIndex The group instance of the port. Defaults to \c 0.
	*/
	CICEPortState( ICENodeContext& in_ctxt, ULONG in_nInputPortID, ULONG in_nInstanceIndex=0 ) ;

	/*! Default constructor. */
	CICEPortState();

	/*! Default destructor. */
	~CICEPortState();

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	CICEPortState(const CICEPortState& in_obj);

	/*! Equality operator. Tests whether the states on two ports are the same.
	\param in_obj CICEPortState instance to compare.
	\return true if both objects are the same, false if different.
	*/
	bool operator == (const CICEPortState& in_obj) const;

	/*! Inequality operator. Tests whether the states on two ports are different.
	\param in_obj CICEPortState instance to compare.
	\return true if both objects are different, false otherwise.
	*/
	bool operator != (const CICEPortState& in_obj) const;

	/*! Assignment operator. Assign this CICEPortState to another CICEPortState.
	\param in_obj CICEPortState object to assign.
	\return A reference to new CICEPortState.
	*/
	CICEPortState& operator = (const CICEPortState& in_obj) ;

	/*! Returns true if the object is valid. Unless not created properly, the object is always valid.
	\return True if valid, false otherwise.
	*/
	bool IsValid() const;

	/*! Returns the dirty state of a port for a given state type defined in the CICEPortState::DirtyState enumerator. By
	default, IsDirty returns true if at least one of the port states is dirty or returns false otherwise.
	\return true if dirty, false otherwise.
	*/
	bool IsDirty( unsigned short in_flag=siAnyDirtyState ) const;

	/*! Clears the port states.
	*/
	void ClearState( );

	protected:
	CStatus Init( const ICENodeContext& in_ctxt, ULONG in_nInputPortID, ULONG in_nGroupInstID );

	void* m_pCtxt;
	ULONG m_nInputPortID;
};

};
#endif // __XSIICEPORTSTATE_H__
