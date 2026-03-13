//*****************************************************************************
/*!
   \file xsi_icenodeoutputport.h
   \brief ICENodeOutputPort class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIICENODEOUTPUTPORT_H__
#define __XSIICENODEOUTPUTPORT_H__

#include <xsi_icenodeport.h>

namespace XSI {

//*****************************************************************************
/*! \class ICENodeOutputPort xsi_icenodeoutputport.h
	\brief A ICENodeOutputPort object represents the output port of an ICENode.

	The %ICENodeOutputPort connects to one or multiple %ICENode objects. An %ICENode
	can have more than one %ICENodeOutputPort.

	\sa ICENodePort, ICENodeInputPort, ICENode::GetOutputPorts
	\since 7.0
*/
//*****************************************************************************

class SICPPSDKDECL ICENodeOutputPort : public ICENodePort
{
public:
	/*! Default constructor. */
	ICENodeOutputPort();

	/*! Default destructor. */
	~ICENodeOutputPort();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	ICENodeOutputPort(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	ICENodeOutputPort(const ICENodeOutputPort& in_obj);

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
	empty if the output object is not compatible.
	\param in_obj constant class object.
	\return The new ICENodeOutputPort object.
	*/
	ICENodeOutputPort& operator=(const ICENodeOutputPort& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the output reference object is not compatible.
	\param in_ref constant class object.
	\return The new ICENodeOutputPort object.
	*/
	ICENodeOutputPort& operator=(const CRef& in_ref);

	private:
	ICENodeOutputPort * operator&() const;
	ICENodeOutputPort * operator&();
};

};

#endif // __XSIICENODEOUTPUTPORT_H__
