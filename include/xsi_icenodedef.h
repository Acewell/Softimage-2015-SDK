//*****************************************************************************
/*!
   \file xsi_icenodedef.h
   \brief ICENodeDef class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIICENODEDEF_H__
#define __XSIICENODEDEF_H__

#include <xsi_base.h>
#include <xsi_value.h>

namespace XSI {

//*****************************************************************************
/*! \class ICENodeDef xsi_icenodedef.h
	\brief %ICENodeDef objects are used for describing a unique custom ICENode object.
	Instances of this object are used to register custom ICENode objects with
	PluginRegistrar::RegisterICENode.

	\sa ICENode, PluginRegistrar::RegisterICENode, \xt cb_icenodes %ICENode Callbacks \endxt
	\since 7.0
*/
//*****************************************************************************

class SICPPSDKDECL ICENodeDef : public CBase
{
public:

	/*! Default constructor. */
	ICENodeDef();

	/*! Default destructor. */
	~ICENodeDef();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	ICENodeDef(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	ICENodeDef(const ICENodeDef& in_obj);

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
	\return The new ICENodeDef object.
	*/
	ICENodeDef& operator=(const ICENodeDef& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new ICENodeDef object.
	*/
	ICENodeDef& operator=(const CRef& in_ref);

	/*! Sets this ICENode threading model, possible values are: single-thread, multi-thread and multi-phase. By default, ICENode objects
	are evaluated in a multi-threading process where the data is processed by the custom node in several passes. Single thread processing
	on the other hand performs data processing in one single pass which allows the node to get all the input data in one single chunk.
	The multi-phase model allows for a more flexible processing model where specific ports can be pulled and other ignored during the
	evaluation phases.

	\param in_nModel Threading model value.
	\return CStatus::OK Success.
	\return CStatus::Fail Operation failed.
	\sa ICENodeDef::GetThreadingModel
	*/
	CStatus PutThreadingModel( siICENodeThreadingModel in_nModel );

	/*! Returns the threading model for this ICENode.
	\return ICENode threading model.
	\sa ICENodeDef::PutThreadingModel
	*/
	siICENodeThreadingModel GetThreadingModel( ) const;

	/*! Defines a custom data type to be used as a data type when defining a custom node port. Custom types are typically used
	in ICE for propagating user-defined (binary) data through the graph as a regular data type. A custom type is identified with
	a global identifier (string name), a fundamental data type (::siICENodeDataCustomType) and a port connection handle color.

	\param in_strCustomType The custom type global string identifier. Softimage doesn't enforce any string format for defining
		the identifier, but it is recommended to use names that somewhat describe what the data type refers to. Naming your
		custom type appropriately is important because it is used throughout the system as a unique identifier to your type.
	\param in_strDisplayName The name of the custom type to display in the ICE graph.
	\param in_strDescription A short description of the custom type used for showing in the ICE graph.
	\param in_red Defines the value of red for the UI port connection handle of this custom type.
	\param in_green Defines the value of green for the UI port connection handle of this custom type.
	\param in_blue Defines the value of blue for the UI port connection handle of this custom type.
	\return CStatus::OK success.
	\return CStatus::Fail Type couldn't be registered.
	\since 8.0 (2010)
	*/
	CStatus DefineCustomType(	const CString&	in_strCustomType,
								const CString&	in_strDisplayName,
								const CString&	in_strDescription,
								unsigned char	in_red,
								unsigned char	in_green,
								unsigned char	in_blue );

	/*! Adds a port group to this ICENode definition. %Port groups must be defined with a unique identifier.

	\note AddPortGroup is restricted to input port groups only. You can still use this API to define output port groups but
		you have to make sure the maximum number of connections (\c in_nMax) is set to \c UINT_MAX. If \c in_nMAx is not set
		properly, multiple output port connections will not be allowed.

	\param in_uniqueGroupId The port group unique identifier.
	\param in_nMin Minimum number of objects required for a connection. Cannot be used for output port groups.
	\param in_nMax Maximum number of objects allowed to be connected. Cannot be used for output port groups.
	\param in_strGroupName %Port group name.
	\return The returned status code (CStatus::OK for success).
	*/
	CStatus	AddPortGroup(	ULONG in_uniqueGroupId,
							ULONG in_nMin=1,
							ULONG in_nMax=1,
							const CString in_strGroupName=CString() );

	/*! Adds an input port to this ICENode definition using a unique identifier. This API can be used for port types other than
	::siICENodeDataCustomType. The minimum and maximum UI range values for the new port is set to 1..10 by default (applicable to
	port types other than ::siICENodeDataCustomType, ::siICENodeDataGeometry and ::siICENodeDataShape).

	\param in_uniquePortId The port unique identifier.
	\param in_uniqueGroupId The port group unique identifier.
	\param in_nDataType The port data type (see ::siICENodeDataType).
	\param in_nStructType The structure type of the port data (see ::siICENodeStructureType).
	\param in_nContextType The context type of the port data (see ::siICENodeContextType).
	\param in_strName The port name.
	\param in_strScriptName The port scripting name.
	\param in_defaultVal The port default value.
	\param in_typeMapId The type map id for this port.
	\param in_structMapId The struct map id for this port.
	\param in_contextMapId The context map id for this port.
	\return The returned status code (CStatus::OK for success).
	*/
	CStatus	AddInputPort(	ULONG in_uniquePortId,
							ULONG in_uniqueGroupId,
							ULONG in_nDataType,
							ULONG in_nStructType,
							ULONG in_nContextType,
							const CString& in_strName,
							const CString& in_strScriptName,
							const CValue& in_defaultVal = CValue(),
							ULONG in_typeMapId = UINT_MAX,
							ULONG in_structMapId = UINT_MAX,
							ULONG in_contextMapId = UINT_MAX );

	/*! Adds an input port to this ICENode definition using a unique identifier. This method is used for port types other than
	::siICENodeDataCustomType and allows the minimum and maximum UI range values to be specified (applicable to
	port types other than ::siICENodeDataCustomType, ::siICENodeDataGeometry and ::siICENodeDataShape).

	\param in_uniquePortId The port unique identifier.
	\param in_uniqueGroupId The port group unique identifier.
	\param in_nDataType The port data type (see ::siICENodeDataType).
	\param in_nStructType The structure type of the port data (see ::siICENodeStructureType).
	\param in_nContextType The context type of the port data (see ::siICENodeContextType).
	\param in_strName The port name.
	\param in_strScriptName The port scripting name.
	\param in_defaultVal The port default value.
	\param in_minVal This port minimum value for configuring the range of the UI control. The minimum value defaults to 1 if
	in_minVal is not specified (i.e. empty).
	\param in_maxVal The port maximum value for configuring the range of the UI control. If in_maxVal is not specified (i.e. empty),
	the maximum value defaults to 10 or twice the default value if it exceeds 10.
	\param in_typeMapId The type map id for this port.
	\param in_structMapId The struct map id for this port.
	\param in_contextMapId The context map id for this port.
	\return The returned status code (CStatus::OK for success).
	*/
	CStatus	AddInputPort(	ULONG in_uniquePortId,
							ULONG in_uniqueGroupId,
							ULONG in_nDataType,
							ULONG in_nStructType,
							ULONG in_nContextType,
							const CString& in_strName,
							const CString& in_strScriptName,
							const CValue& in_defaultVal,
							const CValue& in_minVal,
							const CValue& in_maxVal,
							ULONG in_typeMapId,
							ULONG in_structMapId,
							ULONG in_contextMapId );

	/*! Adds an input port of type siICENodeDataCustomType to this ICENode definition.
	\param in_uniquePortId The port unique identifier.
	\param in_uniqueGroupId The port group unique identifier.
	\param in_strCustomDataTypes Array of custom type global identifier(s) to use.
	\param in_nStructType The structure type of the port data (see ::siICENodeStructureType).
	\param in_nContextType The context type of the port data (see ::siICENodeContextType).
	\param in_strName The port name.
	\param in_strScriptName The port scripting name.
	\param in_typeMapId The type map id for this port.
	\param in_structMapId The struct map id for this port.
	\param in_contextMapId The context map id for this port.
	\return The returned status code (CStatus::OK for success).
	\since 8.0 (2010)
	*/
	CStatus	AddInputPort(	ULONG				in_uniquePortId,
							ULONG				in_uniqueGroupId,
							const CStringArray& in_strCustomDataTypes,
							ULONG				in_nStructType,
							ULONG				in_nContextType,
							const CString&		in_strName,
							const CString&		in_strScriptName,
							ULONG				in_typeMapId,
							ULONG				in_structMapId,
							ULONG				in_contextMapId );

	/*! Adds an output port to this ICENode definition. 
	Note that ::siICENodeDataGeometry is not a supported output port type. 
	If an output port shares the same type map constraint as an input port, set both port types to ::siICENodeOutputDataAny. Otherwise the type map will not be successful. 
	\param in_uniquePortId The port unique identifier.
	\param in_nDataType The port data type (see ::siICENodeDataType).
	\param in_nStructType The structure type of the port data (see ::siICENodeStructureType).
	\param in_nContextType The context type of the port data (see ::siICENodeContextType).
	\param in_strName The port name.
	\param in_strScriptName The port scripting name.
	\param in_typeMapId The type map id for this port.
	\param in_structMapId The struct map id for this port.
	\param in_contextMapId The context map id for this port.
	\return The returned status code (CStatus::OK for success).
	*/
	CStatus	AddOutputPort(	ULONG in_uniquePortId,
							ULONG in_nDataType,
							ULONG in_nStructType,
							ULONG in_nContextType,
							const CString& in_strName,
							const CString& in_strScriptName,
							ULONG in_typeMapId = UINT_MAX,
							ULONG in_structMapId = UINT_MAX,
							ULONG in_contextMapId = UINT_MAX );

	/*! Adds an output port of type siICENodeDataCustomType to this ICENode definition.
	\param in_uniquePortId The port unique identifier.
	\param in_strCustomDataTypes Array of custom type global identifier(s) to use.
	\param in_nStructType The structure type of the port data (see ::siICENodeStructureType).
	\param in_nContextType The context type of the port data (see ::siICENodeContextType).
	\param in_strName The port name.
	\param in_strScriptName The port scripting name.
	\param in_typeMapId The type map id for this port.
	\param in_structMapId The struct map id for this port.
	\param in_contextMapId The context map id for this port.
	\return The returned status code (CStatus::OK for success).
	\since 8.0 (2010)
	*/
	CStatus	AddOutputPort(	ULONG				in_uniquePortId,
							const CStringArray&	in_strCustomDataTypes,
							ULONG				in_nStructType,
							ULONG				in_nContextType,
							const CString&		in_strName,
							const CString&		in_strScriptName,
							ULONG				in_typeMapId = UINT_MAX,
							ULONG				in_structMapId = UINT_MAX,
							ULONG				in_contextMapId = UINT_MAX );

	/*! \deprecated 8.0 (2010). This API doesn't support multiple connections and should not be used, use the other API 
	signature instead which takes no group identifier and supports multiple connections. 

	\param in_uniquePortId The port unique identifier.
	\param in_uniqueGroupId The port group unique identifier.
	\param in_nDataType The port data type (see \link siICENodeDataType \endlink).
	\param in_nStructType The structure type of the port data (see \link siICENodeStructureType \endlink).
	\param in_nContextType The context type of the port data (see \link siICENodeContextType \endlink).
	\param in_strName The port name.
	\param in_strScriptName The port scripting name.
	\param in_typeMapId The type map id for this port.
	\param in_structMapId The struct map id for this port.
	\param in_contextMapId The context map id for this port.
	\return The returned status code (CStatus::OK for success).
	*/
	CStatus	AddOutputPort(	ULONG in_uniquePortId,
							ULONG in_uniqueGroupId,
							ULONG in_nDataType,
							ULONG in_nStructType,
							ULONG in_nContextType,
							const CString& in_strName,
							const CString& in_strScriptName,
							ULONG in_typeMapId = UINT_MAX,
							ULONG in_structMapId = UINT_MAX,
							ULONG in_contextMapId = UINT_MAX );

	/*! Sets the UI color of the ICENode that is being defined by this %ICENodeDef object.

	\param in_red Defines the value of red for the UI color of this ICENode.
	\param in_green Defines the value of green for the UI color of this ICENode.
	\param in_blue Defines the value of blue for the UI color of this ICENode.
	\return CStatus::OK success.
	\return CStatus::Fail failure.
	\since 8.0 (2010)
	*/
	CStatus PutColor( unsigned char in_red, unsigned char in_green, unsigned char in_blue );

	private:
	ICENodeDef * operator&() const;
	ICENodeDef * operator&();
};

};
#endif // __XSIICENODEDEF_H__
