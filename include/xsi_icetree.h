//*****************************************************************************
/*!
   \file xsi_icetree.h
   \brief ICETree class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIICETREE_H__
#define __XSIICETREE_H__

#include <xsi_icenodecontainer.h>

namespace XSI {

//*****************************************************************************
/*! \class ICETree xsi_icetree.h
	\brief The ICETree object represents a node graph and holds all the effect nodes together.

	It serves as a container for objects such as ICENode and ICECompoundNode. The ICETree is
	attached to the Primitive being modified and acts like the evaluation entry-point for the
	entire graph. ICETree objects can be created with the \xl ApplyOp command by passing the
	ICETree preset as argument.

	\sa ICENode, ICECompoundNode, ICEDataProviderNode, ICEDataModifierNode
	\sa \xl ApplyOp, \xl ApplyICEOp, \xl ApplyICETemplate
	\since 7.0

	\eg This example demonstrates how to create an ICETree object.
	\code
		void CreatePrim( const CString& in_presetobj, const CString& in_geometrytype, const CString& in_name, const CString& in_parent );
		CRefArray ApplyOp( const CString& in_presetobj, CString & io_connectionset, const siConstructionMode& in_constructionmode );

		// Create agrid primitive and apply a ICETree on it
		CreatePrim( L"Grid", L"MeshSurface", L"", L"" );

		CString strGrid(L"grid");
		CRefArray outOps = ApplyOp( L"ICETree", strGrid, siConstructionModeModeling );

		// The new ICETree returned by ApplyOp is encapsulated within outOps at position 0
		ICETree t = outOps[0];

		Application xsi;
		xsi.LogMessage( t.GetClassIDName() );
	\endcode

	\eg This example demonstrates how to get the ICETree object(s) from the primitive.
	\code
		void CreatePrim( const CString& in_presetobj, const CString& in_geometrytype, const CString& in_name, const CString& in_parent );
		CRefArray ApplyOp( const CString& in_presetobj, CString & io_connectionset, const siConstructionMode& in_constructionmode );

		// Create agrid primitive and apply a ICETree on it
		CreatePrim( L"Grid", L"MeshSurface", L"", L"" );

		CString strGrid(L"grid");
		ApplyOp( L"ICETree", strGrid, siConstructionModeModeling );

		// Get the ICETree(s) from the primitive
		Selection selection = xsi.GetSelection();
		X3DObject x3DGrid = selection[ 0 ];
		CRefArray trees = x3DGrid.GetActivePrimitive().GetICETrees();
		for (LONG i=0; i<trees.GetCount(); i++)
		{
			ICETree t = trees[i];
			xsi.LogMessage( t.GetClassIDName() );
		}
	\endcode

 */
//*****************************************************************************

class SICPPSDKDECL ICETree : public ICENodeContainer
{
public:
	/*! Default constructor. */
	ICETree();

	/*! Default destructor. */
	~ICETree();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	ICETree(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	ICETree(const ICETree& in_obj);

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
	\return The new ICETree object.
	*/
	ICETree& operator=(const ICETree& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new ICETree object.
	*/
	ICETree& operator=(const CRef& in_ref);

	private:
	ICETree * operator&() const;
	ICETree * operator&();
};

};

#endif // __XSIICETREE_H__
