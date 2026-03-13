#include <xsi_application.h>
#include <xsi_context.h>
#include <xsi_pluginregistrar.h>
#include <xsi_status.h>

#include <xsi_icenodecontext.h>
#include <xsi_icenodedef.h>
#include <xsi_command.h>
#include <xsi_factory.h>
#include <xsi_longarray.h>
#include <xsi_doublearray.h>
#include <xsi_math.h>
#include <xsi_vector2f.h>
#include <xsi_vector3f.h>
#include <xsi_vector4f.h>
#include <xsi_matrix3f.h>
#include <xsi_matrix4f.h>
#include <xsi_rotationf.h>
#include <xsi_quaternionf.h>
#include <xsi_color4f.h>
#include <xsi_shape.h>
#include <xsi_icegeometry.h>
#include <xsi_iceportstate.h>
#include <xsi_indexset.h>
#include <xsi_dataarray.h>
#include <xsi_dataarray2D.h>

/////////////////////////////////// Softimage Documentation //////////////////////////////////////////////////////
// <node id="BuildArrayFromSet" label="Build Array From Set" introduced="10.0 (2012)" categories="Array">
// <description>
// Return each values from a set of elements (points, edges, polygons, etc...) into a single array.
// </description>
// <inputs>
// <portgroup id="100" instances="1">
// 	<inputport id="Value" label="Value">
// 		<description>The Value per Element. Its structure can be single or array</description>
// 	<type map="-1">
//				<object idref="siICENodeDataType#siICENodeDataBool"/> or <br/>
//				<object idref="siICENodeDataType#siICENodeDataLong"/> or <br/>
// 				<object idref="siICENodeDataType#siICENodeDataLong"/> or <br/>
// 				<object idref="siICENodeDataType#siICENodeDataFloat"/> or <br/>
// 				<object idref="siICENodeDataType#siICENodeDataVector2"/> or <br/>
// 				<object idref="siICENodeDataType#siICENodeDataVector3"/> or <br/>
// 				<object idref="siICENodeDataType#siICENodeDataVector4"/> or <br/>
// 				<object idref="siICENodeDataType#siICENodeDataQuaternion"/> or <br/>
// 				<object idref="siICENodeDataType#siICENodeDataRotation"/> or <br/>
// 				<object idref="siICENodeDataType#siICENodeDataMatrix33"/> or <br/>
// 				<object idref="siICENodeDataType#siICENodeDataMatrix44"/> or <br/>
// 				<object idref="siICENodeDataType#siICENodeDataColor4"/>
//	</type>
// 	<structure map="-1"><object idref="siICENodeStructureType#siICENodeStructureAny"/></structure>
// 	<context map="402"><object idref="siICENodeContextType#siICENodeContextAny"/></context>
// </inputport>
// </portgroup>
// </inputs>
// <outputs>
// <outputport id="Array" label="Array">
// 	<description>A per object array.</description>
// 	<type map="-1">
//				<object idref="siICENodeDataType#siICENodeDataBool"/> or <br/>
//				<object idref="siICENodeDataType#siICENodeDataLong"/> or <br/>
// 				<object idref="siICENodeDataType#siICENodeDataLong"/> or <br/>
// 				<object idref="siICENodeDataType#siICENodeDataFloat"/> or <br/>
// 				<object idref="siICENodeDataType#siICENodeDataVector2"/> or <br/>
// 				<object idref="siICENodeDataType#siICENodeDataVector3"/> or <br/>
// 				<object idref="siICENodeDataType#siICENodeDataVector4"/> or <br/>
// 				<object idref="siICENodeDataType#siICENodeDataQuaternion"/> or <br/>
// 				<object idref="siICENodeDataType#siICENodeDataRotation"/> or <br/>
// 				<object idref="siICENodeDataType#siICENodeDataMatrix33"/> or <br/>
// 				<object idref="siICENodeDataType#siICENodeDataMatrix44"/> or <br/>
// 				<object idref="siICENodeDataType#siICENodeDataColor4"/>
//	</type>
// 	<structure map="-1"><object idref="siICENodeStructureType#siICENodeStructureArray"/></structure>
// 	<context map="402"><object idref="siICENodeContextType#siICENodeContextSingleton"/></context>
// </outputport>
// </outputs>
// <seealso>
// <node idref="BuildArrayFromConstantNode"/>
// <node idref="BuildArrayNode"/>
// <node idref="GetArraySizeNode"/>
// <node idref="ReserveArrayNode"/>
// <node idref="ResizeArrayNode"/>
// </seealso>
// </node>

// Defines port, group and map identifiers used for registering the ICENode
enum IDs
{
	ID_IN_InValue = 0,
	ID_G_100 = 100,
	ID_OUT_SingletonArray = 200,
	ID_TYPE_CNS = 400,
	ID_STRUCT_CNS,
	ID_CTXT_CNS,
	ID_CTXT_CNS_SINGLE,
	ID_UNDEF = ULONG_MAX
};

using namespace XSI; 

// supported input output types
static const ULONG sBuildArrayFromSetDataType = 
	siICENodeDataBool		|
	siICENodeDataLong		|
	siICENodeDataFloat		|
	siICENodeDataVector2	|
	siICENodeDataVector3	|
	siICENodeDataVector4	|
	siICENodeDataQuaternion	|
	siICENodeDataRotation	|
	siICENodeDataMatrix33	|	
	siICENodeDataMatrix44	|
	siICENodeDataColor4;

CStatus RegisterBuildArrayFromSet( PluginRegistrar& in_reg )
{
	ICENodeDef nodeDef;
	nodeDef = Application().GetFactory().CreateICENodeDef(L"BuildArrayFromSet",L"Build Array from Set");

	CStatus st;
	st = nodeDef.PutColor(154,188,102);
	st.AssertSucceeded( ) ;

	st = nodeDef.PutThreadingModel(XSI::siICENodeSingleThreading);
	st.AssertSucceeded( ) ;

	// Add input ports and groups.
	st = nodeDef.AddPortGroup(ID_G_100);
	st.AssertSucceeded( ) ;

	st = nodeDef.AddInputPort(ID_IN_InValue,ID_G_100,sBuildArrayFromSetDataType ,siICENodeStructureAny,siICENodeContextAny,L"Value",L"Value",CValue(),CValue(),CValue(),ID_TYPE_CNS,ID_UNDEF,ID_UNDEF);
	st.AssertSucceeded( ) ;

	// Add output ports.
	st = nodeDef.AddOutputPort(ID_OUT_SingletonArray,sBuildArrayFromSetDataType ,siICENodeStructureArray,siICENodeContextSingleton,L"Array",L"Array",ID_TYPE_CNS,ID_UNDEF,ID_UNDEF);
	st.AssertSucceeded( ) ;

	PluginItem nodeItem = in_reg.RegisterICENode(nodeDef);

	// This node is deprecated. The native BuildArrayFromSet node should be used instead.
	// Do not put a category!
	//nodeItem.PutCategories(L"Array");

	return CStatus::OK;
}

template < class T >
class CEvaluator
{
public:
	static void Do( ICENodeContext& in_ctxt, ULONG in_nInPortID, XSI::siICENodeStructureType in_Struct )
	{
		CDataArray2D<T> outData( in_ctxt );
		CIndexSet indexSet( in_ctxt, in_nInPortID );
		typename CDataArray2D<T>::Accessor outAccessor;
		
		if ( in_Struct == XSI::siICENodeStructureSingle )
		{
			CDataArray<T> InData( in_ctxt, in_nInPortID );
			ULONG l_ulNbElements = indexSet.GetFilteredCount();
			outAccessor = outData.Resize(0, l_ulNbElements);

			ULONG l_ulIndex = 0;
			for(CIndexSet::Iterator it = indexSet.Begin(); it.HasNext(); it.Next())
			{
				SetAccessorValue(outAccessor, l_ulIndex++, InData[it]);
			}
		}
		else if ( in_Struct == XSI::siICENodeStructureArray )
		{
			CDataArray2D<T> InData( in_ctxt, in_nInPortID );
			
			ULONG l_ulCurrentOutCount = 0;
			for(CIndexSet::Iterator it = indexSet.Begin(); it.HasNext(); it.Next())
			{
				typename CDataArray2D<T>::Accessor inAccessor = InData[it];
				
				ULONG l_ulNbSubElementsInput = inAccessor.GetCount();

				outAccessor = outData.Resize(0, l_ulCurrentOutCount +  l_ulNbSubElementsInput );
				for ( ULONG i=0; i<inAccessor.GetCount(); i++ )
				{
					SetAccessorValue(outAccessor, i+l_ulCurrentOutCount, inAccessor[i]);
				}		
				l_ulCurrentOutCount += inAccessor.GetCount();		
			}			
		}
	}

private:
	static void SetAccessorValue(typename CDataArray2D<T>::Accessor& io_acc, const ULONG& in_ulIndex, const T& in_value)
	{
		io_acc[in_ulIndex] = in_value;
	}
};


// Specialization for the Bool type (need to use "Set()" instead of "[]")
template<>
void CEvaluator<bool>::SetAccessorValue(CDataArray2D<bool>::Accessor& io_acc, const ULONG& in_ulIndex, const bool& in_value)
{
	io_acc.Set(in_ulIndex, in_value);
}


SICALLBACK BuildArrayFromSet_Evaluate( ICENodeContext& in_ctxt )
{
	ULONG out_portID = in_ctxt.GetEvaluatedOutputPortID( );
	
	switch( out_portID )
	{		
		case ID_OUT_SingletonArray :
		{
			XSI::siICENodeDataType inPortType;
			XSI::siICENodeStructureType inPortStruct;
			XSI::siICENodeContextType inPortContext;
			in_ctxt.GetPortInfo( ID_IN_InValue, inPortType, inPortStruct, inPortContext );

			switch( inPortType )
			{
				case siICENodeDataBool:			CEvaluator<bool>::Do( in_ctxt, ID_IN_InValue, inPortStruct); break;
				case siICENodeDataLong:			CEvaluator<LONG>::Do( in_ctxt, ID_IN_InValue, inPortStruct); break;
				case siICENodeDataFloat:		CEvaluator<float>::Do( in_ctxt, ID_IN_InValue, inPortStruct); break;
				case siICENodeDataVector2:		CEvaluator<MATH::CVector2f>::Do( in_ctxt, ID_IN_InValue, inPortStruct); break;
				case siICENodeDataVector3:		CEvaluator<MATH::CVector3f>::Do( in_ctxt, ID_IN_InValue, inPortStruct); break;
				case siICENodeDataVector4:		CEvaluator<MATH::CVector4f>::Do( in_ctxt, ID_IN_InValue, inPortStruct); break;
				case siICENodeDataQuaternion:	CEvaluator<MATH::CQuaternionf>::Do( in_ctxt, ID_IN_InValue, inPortStruct); break;
				case siICENodeDataRotation:		CEvaluator<MATH::CRotationf>::Do( in_ctxt, ID_IN_InValue, inPortStruct); break;
				case siICENodeDataMatrix33:		CEvaluator<MATH::CMatrix3f>::Do( in_ctxt, ID_IN_InValue, inPortStruct); break;
				case siICENodeDataMatrix44:		CEvaluator<MATH::CMatrix4f>::Do( in_ctxt, ID_IN_InValue, inPortStruct); break;
				case siICENodeDataColor4:		CEvaluator<MATH::CColor4f>::Do( in_ctxt, ID_IN_InValue, inPortStruct); break;
			};			  		
		}
		break;		
	};

	return CStatus::OK;
}

