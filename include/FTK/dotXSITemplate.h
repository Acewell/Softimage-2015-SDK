//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file dotXSITemplate.h
	\brief Defines the CdotXSITemplate and CdotXSITemplates classes

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

//***************************************************************************************
// Defines
//***************************************************************************************
#ifndef __DOTXSITEMPLATE_H
#define __DOTXSITEMPLATE_H

//***************************************************************************************
// Includes
//***************************************************************************************
#include "SIBCArray.h"
#include "SIBCNode.h"
#include "SIBCString.h"
#include "dotXSIParams.h"

//***************************************************************************************
// Typedefs
//***************************************************************************************
class CdotXSITemplate;
class CXSIParser;

// @type DOTXSICALLBACK | dotXSI Native Templates callback function.
typedef SI_Error ( *DOTXSIREADCALLBACK ) ( CXSIParser *in_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate );
typedef SI_Error ( *DOTXSIWRITECALLBACK ) ( CXSIParser *in_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate, SI_Int i_nLevel );

//***************************************************************************************
// @class CdotXSITemplates | container for an array of CdotXSITemplate
//***************************************************************************************

/*! \brief Used as a container class for CdotXSITemplate.

	This class supports methods for grouping CdotXSITemplate objects together,
	including indexing of objects, finding objects, etc.
*/
class XSIEXPORT CdotXSITemplates
{
public:

	/*! Default constructor. Creates a CdotXSITemplates object.
	Sets the \c m_bDeleteOnExit flag to true by default.
	*/
	CdotXSITemplates();

	/*! Constructor. Creates a CdotXSITemplates object.
	Sets the \c m_bDeleteOnExit flag to the input parameter value
	\param[in]	in_bDeleteOnExit	This flag has no effect.
	*/
	CdotXSITemplates( SI_Bool in_bDeleteOnExit);

	/*! Destructor.
	*/
	virtual ~CdotXSITemplates();


	/*! Returns the number of elements in this particular template hierarchy level.
	\return The number of elements in this hierarchy level.
	*/
	SI_Int GetCount();

	/*! Returns the total number of elements (recursive, including child templates).
	\return The total number of elements.
	*/
    SI_Int GetTotalCount();

	/*! Adds a CdotXSITemplate element to this container, in the specified position.
	\param[in] i_Template	Pointer to the object to add to this container.
	\param[in] i_nPosition	Position in which to add the item. To specify the current position, use \c -1 (default).
	*/
	SI_Void Add( CdotXSITemplate *i_Template, SI_Int i_nPosition = -1 );

	/*! Returns the specified element (indirectly). This call is equivalent to ::Item(SI_Int),
	except that it stores the return in an output parameter, rather than returning the pointer
	directly from the function itself.

	\param[in]	i_nPosition	Position of the item to receive.
	\param[out]	o_Template	Pointer where the reference to the item will be stored (or NULL if \c i_nPosition is invalid).
	*/
	SI_Void Item( SI_Int i_nPosition, CdotXSITemplate **o_Template );

	/*! Returns the specified element. This call is equivalent to ::Item(SI_Int, CdotXSITemplate **),
	except that it returns the pointer directly from the function instead of storing the return in an
	out parameter.
	\param[in]	i_nPosition	Position of the item to receive.
	\return	Item at position \c i_nPosition (or NULL if \c i_nPosition is invalid).
	*/
    CdotXSITemplate *Item( SI_Int i_nPosition );

	/*! Removes the specified element.
	\param[in]	i_nPosition	The position of the element to remove. If \c i_nPosition is invalid, nothing is removed.
	*/
    SI_Void Remove( SI_Int i_nPosition );

	/*! Removes all elements from the container.
	*/
    SI_Void Clear();

	/*! Checks to see if a template of the given type name is a member of this container.
	\param[in]	i_sName	Type name of the template to search for.
	\param[out]	o_nInd	Set to the position of the first element of the type given by \c i_sName.
			If none was found, this parameter is set to \c -1.
	\retval SI_Bool::TRUE if a template with the given type name was found
	\retval SI_Bool::FALSE otherwise
	*/
    SI_Bool IsSupported( CSIBCString *i_sName, SI_Int &o_nInd );

	/*! Searches all templates, and all children of templates contained within this container for
	a CdotXSITemplate whose type name matches the value passed in \c i_sTemplateName, and whose
	instance name matches the value specified in \c i_sInstanceName.
	\param[in]	i_sTemplateName	The type name of the template to find. (Required).
	\param[in]	i_sInstanceName	The instance name of the template to find. (Required).
	\param[out]	o_pTemplate		Pointer where the reference to the item will be stored (or NULL if no item is found).
	\retval SI_Bool::TRUE if a template matching the given parameters was found
	\retval SI_Bool::FALSE otherwise
	*/
	SI_Bool Find( CSIBCString *i_sTemplateName, CSIBCString *i_sInstanceName, CdotXSITemplate **o_pTemplate );	// Find an element by template and instance name

	/*! Searches all templates contained within this container for a CdotXSITemplate that has a type
	name matching the values specified in \c in_name.
	\param[in] in_name	Type name of the template to search for.
	\return First template within this container whose type name matches the \c in_name parameter (or NULL if there is no match).
	*/
	CdotXSITemplate	* FindByType( CSIBCString in_name );

	/*!	Creates a new container object that contains all elements within this container that have the specified type name.
	\param[in]	in_type	Type name of the elements to put in the new container.
	\return	Pointer to the new container created. If no elements match the specified type name, the container is empty (but still valid).
	*/
	CdotXSITemplates *ChildrenOfType( CSIBCString in_type );

	CdotXSITemplate**	ArrayPtr() { return m_Templates.ArrayPtr();} ;


	/*!	Reorders the children inside the template container
	\param[in] in_iTemplate	the position of the template to move (its old index)
	\param[in] in_iNewPos	the position to move the template to (its new index)
	*/
	SI_Void			MoveChild ( int in_iTemplate, int in_iNewPos );

private:
	SI_Int                          m_nCount;
	SI_Bool							m_bDeleteMembers;
	CSIBCArray< CdotXSITemplate * > m_Templates;
};

//***************************************************************************************
// @class CdotXSITemplate | a template
// @base public | CSIBCNode
//***************************************************************************************

/*! \brief Represents the base class for all template types in Softimage.

	All scene information in Softimage (excluding sources, such as image or audio files) is
	stored within templates. These templates contain parameters that define what type
	the template is, and given the type, what object/property the template represents
	in terms of the scene. This is the base class representing all templates used in
	Softimage.

	This class is distinct from the CSLTemplate class. That class, as its name indicates,
	is the template representation used in the Semantic Layer library, whereas this class
	represents the native Softimage template.

	Also unlike the CSLTemplate class, this class is concrete, meaning that it can be
	instantiated. This is not generally done however. Generally, CdotXSITemplate objects
	are only allocated within methods of the Semantic Layer.
*/
class XSIEXPORT CdotXSITemplate : public CSIBCNode
{
public:

	enum eCOLLADATemplateType
	{
		NORMAL = 0,
		LIBRARY,
		NODE,
		URL
	};

	/*! Default constructor.
	Sets the default version information, and the default read and write callbacks
	for the template.
	\return an instance of CdotXSITemplate
	*/
	CdotXSITemplate();

	/*! Constructor.
	Sets the type name of the template to the name give by \c i_sName.
	\param[in]	i_sName	Type name of the new template.
	\return	an instance of CdotXSITemplate
	*/
	CdotXSITemplate( CSIBCString *i_sName );

	/*! Constructor.
	Sets the type name, read and write callbacks, version information, as well as
	a variable number of CdotXSIParam parameter definitions to add to the new template.
	\param[in]	i_sName			Type name of the new template.
	\param[in]	i_ReadCallback	Pointer to the read callback function used to read this template.
	\param[in]	i_WriteCallback	Pointer to the write callback function used to write this template.
	\param[in]	i_lVersionMajor	Major version number used for this template.
	\param[in]	i_lVersionMinor	Minor version number used for this template.
	\param[in]	i_nNbParams		Number of variable CdotXSIParam arguments to follow.
	\param[in]	i_Param1		First parameter definition (if \c i_nNbParams > 0) to add to this template.
	\param[in]	...				More parameter definitions (of CdotXSIParam * type) to add to this template.
	\return	an instance of CdotXSITemplate
	*/
	CdotXSITemplate( CSIBCString i_sName,									// Constructor
                     DOTXSIREADCALLBACK i_ReadCallback,
                     DOTXSIWRITECALLBACK i_WriteCallback,
					 SI_Int i_lVersionMajor, SI_Int i_lVersionMinor,
                     SI_Int i_nNbParams,
                     CdotXSIParam *i_Param1, ... );

	/*! Constructor.
	Sets the type name, read and write callbacks, as well as a variable number of CdotXSIParam
	parameter definitions to add to the new template. Note that it does not contain an entry for
	version information, which is set the the default.

	\param[in]	i_sName			Type name of the new template.
	\param[in]	i_ReadCallback	Pointer to the read callback function used to read this template.
	\param[in]	i_WriteCallback	Pointer to the write callback function used to write this template.
	\param[in]	i_nNbParams		Number of variable CdotXSIParam arguments to follow.
	\param[in]	i_Param1		First parameter definition (if \c i_nNbParams > 0) to add to this template.
	\param[in]	...				More parameter definitions (of CdotXSIParam * type) to add to this template.
	\return	an instance of CdotXSITemplate
	*/
	CdotXSITemplate( CSIBCString i_sName,
                     DOTXSIREADCALLBACK i_ReadCallback,
                     DOTXSIWRITECALLBACK i_WriteCallback,
                     SI_Int i_nNbParams,
                     CdotXSIParam *i_Param1, ... );


	/*! Destructor
	*/
    virtual ~CdotXSITemplate();

	/*! Changes the instance name of this template to the one specified by \c i_sInstanceName
	\param[in]	i_sInstanceName	The new instance name of this template.
	*/
    virtual SI_Void SetInstanceName( CSIBCString i_sInstanceName );

	/*!	Returns the instance name of this template.
	\return Reference to the instance name of this template.
	*/
    CSIBCString &InstanceName() { return m_sInstanceName; }

	/*! Sets the user data type for this template.
	\param[in]	i_sUserDataType	String representing the type of user data contained in this template.
	*/
    SI_Void SetUserDataType( CSIBCString i_sUserDataType );

	/*! Returns the string representing the user data type name.
	\return Reference to the user data type name.
	*/
    CSIBCString &UserDataType() { return m_sUserDataType; }

	/*! Returns the CdotXSITemplates children container instance.
	\return Reference to the CdotXSITemplates children container instance.
	*/
    CdotXSITemplates &Children() { return m_ChildrenCol; }

	/*!	Sets the parent template of this template to the specified template.
	\param[in]	i_Parent	The new parent template
	*/
    SI_Void SetParent( CdotXSITemplate *i_Parent );

	/*!	Changes the parent template of this template to the specified template.
	\param[in]	i_Parent	The new parent template of this template.
	*/
	SI_Void Reparent(  CdotXSITemplate *i_Parent );

	/*! Returns the parent template of this template.
	\return	Pointer to the parent template of this template.
	*/
    CdotXSITemplate *Parent() { return m_Parent; }

    /*! Sets the system flags for this template. System flags have no specific meaning within
	the template. Applications using the Crosswalk SDK may set/query system flags as a convenient way
	to set application defined flags, per template.

	\note This function does not remove any flags previously set.
	\param[in]	i_nSystemFlags	Bit-wise system flags to set for this template.
	*/
	SI_Void SetSystemFlags( SI_Int i_nSystemFlags );


    /*! Returns the system flags for this template. System flags have no specific meaning within
	the template. Applications using the Crosswalk SDK may set/query system flags as a convenient way
	to set application defined flags, per template.
	\param[out]	o_nSystemFlags	Pointer to an SI_Int where system flags will be set for this template.
	*/
    SI_Void GetSystemFlags( SI_Int *o_nSystemFlags );

    /*! Sets the user flags for this template. User flags have no specific meaning within
	the template. Applications using the Crosswalk SDK may set/query user flags as a convenient way
	to set application defined flags, per template.

	\note This function does not remove any flags previously set.
	\param[in]	i_nUserFlags	Bit-wise user flags to set for this template.
	*/
    SI_Void SetUserFlags( SI_Int i_nUserFlags );

    /*! Returns the user flags for this template. User flags have no specific meaning within
	the template. Applications using the Crosswalk SDK may set/query user flags as a convenient
	way to set application defined flags, per template.
	\param[out]	o_nUserFlags	Pointer to an SI_Int where user flags will be set for this template.
	*/
    SI_Void GetUserFlags( SI_Int *o_nUserFlags );

	/*! Returns the container of CdotXSIParam entries for this template.
	\return	Reference to the CdotXSIParams container holding the CdotXSIParam entries for this template.
	*/
	CdotXSIParams &Params() { return m_ParamsCol; }

	/*! Initializes the template from a name in the native templates collection.
	\param[in] i_pChar	String representing the type name of the template to initialize.
	\param[in] in_pParser	Pointer to the parser object.
	*/
    virtual SI_Void InitializeFromName( SI_Char *i_pChar, CXSIParser *in_pParser );

	/*! Creates a new CdotXSITemplates container, containing all child templates of this template
	matching the specified type name. If there are no matches, the new container is empty (but still valid).

	\param[in]	in_type	The type name to match to the child type name.
	\return	Pointer to the newly created container.
	*/
	CdotXSITemplates *ChildrenOfType( CSIBCString in_type );

	/*!	Returns the first child template that has the specified type name instance name.
	\param[in]	in_type	The type name to match to a child template.
	\param[in]	in_name	The instance name to match to a child template.
	\return	The first child of the template that matches both the type name and instance name (or NULL
		if no children match the given parameters).
	*/
	CdotXSITemplate *ChildrenOfTypeNamed( CSIBCString in_type, CSIBCString in_name );

	virtual CdotXSITemplate *Clone();

	/*! Returns the template type as one of the \c eCOLLADATemplateType values
	\return	The template type
	*/
	eCOLLADATemplateType	GetTemplateType() { return m_eType; };

	/*! Sets the template type
	\param[in] in_etype One of the \c eCOLLADATemplateType values
	*/
	SI_Void					SetTemplateType (eCOLLADATemplateType in_etype) { m_eType = in_etype; };

	virtual bool IsCOLLADATemplate() { return false; }

private:
	CSIBCString        m_sInstanceName;
	CSIBCString        m_sUserDataType;
	CdotXSITemplates   m_ChildrenCol;
	CdotXSITemplate   *m_Parent;
	SI_Int             m_nSystemFlags;
	SI_Int             m_nUserFlags;
	CdotXSIParams      m_ParamsCol;
	SI_Int			   m_nVersionMajor, m_nVersionMinor;
	eCOLLADATemplateType	m_eType;

public:
    //! Callback function for reading the template.
    DOTXSIREADCALLBACK        m_ReadCallback;

    //! Callback function for writing the template.
    DOTXSIWRITECALLBACK       m_WriteCallback;

	//! Callback function for writing the end of the template (not used by dotXSI)
	DOTXSIWRITECALLBACK	m_WritePostCallback;

};

//***************************************************************************************
// Functions
//***************************************************************************************

/*! \addtogroup glbfunc_template Global dotXSI template functions
*  @{
*/

/*! Allocates a CdotXSITemplate
\return The newly created CdotXSITemplate
*/
XSIEXPORT CdotXSITemplate* CreatedotXSITemplate();							//

/*! Allocates a CdotXSITemplate collection
\return The newly created CdotXSITemplates
*/
XSIEXPORT CdotXSITemplates* CreatedotXSITemplates();						// Allocate a CdotXSITemplates

/* @} */

//***************************************************************************************
// Function prototype to create templates....
//***************************************************************************************

typedef	CdotXSITemplate* (*TemplateCreation)();

#endif // __DOTXSITEMPLATE_H
