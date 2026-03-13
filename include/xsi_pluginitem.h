//*****************************************************************************
/*!	\file xsi_pluginitem.h
	\brief PluginItem class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIPLUGINITEM_H__
#define __XSIPLUGINITEM_H__

#include <xsi_siobject.h>

namespace XSI {

//*****************************************************************************
/*! \class PluginItem xsi_pluginitem.h
	\brief The PluginItem class contains the information on each item of a plug-in.

	A plug-in item is basically an XSI customizable component such as:

		\li Filter
		\li Command
		\li Operator
		\li   etc.

	\since 4.0
 */
//*****************************************************************************

class SICPPSDKDECL PluginItem : public SIObject
{
public:
	/*! Default constructor. */
	PluginItem();

	/*! Default destructor. */
	~PluginItem();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	PluginItem(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	PluginItem(const PluginItem& in_obj);

	/*! Returns true if a given class type is compatible with this API class.
	\param in_ClassID class type.
	\return true if the class is compatible, false otherwise.
	*/
	bool IsA( siClassID in_ClassID) const;

	/*! Returns the type of the API class.
	\return The class type.
	*/
	siClassID GetClassID() const;

	/*! Creates an object from another object. The new object is set to
	empty if the input object is not compatible.
	\param in_obj constant class object.
	\return The new PluginItem object.
	*/
	PluginItem& operator=(const PluginItem& in_obj);

	/*! Creates an object from a reference object. The new object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new PluginItem object.
	*/
	PluginItem& operator=(const CRef& in_ref);

	/*! Sets the help path for this plug-in item
	 \param in_strHelp The help path
	 \return CStatus OK if successful
	 \return CStatus Fail if not successful
	 */
	CStatus PutHelp( const CString& in_strHelp );

	/*! Returns the help button file replacing the factory "?" button in the plug-in item
	property page.

	\return The help button file of the plug-in item. An empty string is returned if the plug-in item has no help button file.
	\since 13.0 (2015)
	*/
	CString GetHelpButton() const;

	/*! Sets the help button file replacing the factory "?" button in the plug-in item
	property page.

	The help button will be shown in the plug-in item property page only if there is a help file 
	associated with the plug-in item.

	The plug-in item help button file must be a BMP file with a height of 18 pixels and a width no wider than 100 pixels.
	If the help button file doesn't respect the criteria, the factory "?" button will be displayed in the plug-in item property page.

	By default, Softimage looks for a plug-in item help button file in the "doc" subfolder of the plug-in 
	installation folder. Softimage assumes the help button file has the same name as the plug-in item, with
	the "_HelpButton" string appended to it. For example, if the property plug-in item "MyCustomProp" registered by the
	plug-in MyPlugin.dll located in the folder "C:\MyWorkgroup\Application\Plugins" then Softimage looks in the folder 
	"C:\MyWorkgroup\Application\Plugins\Doc" for a help button file named MyCustomProp_HelpButton.bmp.

	If a plug-in help button file has a different name or location, you can call this method
	to specify the name of help button file and, optionally, its location.

	\param in_strHelpButton The help button path.
	\return CStatus::OK if successful.
	\return CStatus::Fail if not successful.
	\since 13.0 (2015)
	*/
	CStatus PutHelpButton( const CString& in_strHelpButton );

	/*! Sets the categories for this plug-in item
	 \param in_strCat A comma-separated string representing the categories of
	 this plug-in item.
	 \return CStatus OK if successul
	 */
	CStatus PutCategories( const CString& in_strCat );

	private:
	PluginItem * operator&() const;
	PluginItem * operator&();
};

};

#endif // __XSIPluginItem_H__
