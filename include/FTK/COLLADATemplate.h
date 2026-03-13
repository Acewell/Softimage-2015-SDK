//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file COLLADATemplate.h
	\brief Defines the CCOLLADATemplate class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

//***************************************************************************************
// Defines
//***************************************************************************************
#ifndef __COLLADATEMPLATE_H
#define __COLLADATEMPLATE_H

//***************************************************************************************
// Includes
//***************************************************************************************
#include "SIBCArray.h"
#include "SIBCNode.h"
#include "SIBCString.h"
#include "dotXSIParams.h"
#include "dotXSITemplate.h"
#define XSI_TECHNIQUE_NAME	"XSI"

/*! \defgroup ColladaSimpleType ColladaSimpleType Enum
	COLLADA 1.4 Types
	\@{
*/
enum ColladaSimpleType
{
 CT_INVALIDTYPE = 0,		/*!< invalid */
 CT_BOOL,					/*!< bool */
 CT_DATETIME,				/*!< date time */
 CT_FLOAT,					/*!< float */
 CT_INT,					/*!< int */
 CT_NAME,					/*!< name */
 CT_STRING,					/*!< string */
 CT_TOKEN,					/*!< token */
 CT_LISTOFBOOLS,			/*!< list of bools */
 CT_LISTOFFLOATS,			/*!< list of floats */
 CT_LISTOFHEXBINARY,		/*!< list of hex binaries */
 CT_LISTOFINTS,				/*!< list of ints */
 CT_LISTOFNAMES,			/*!< list of names */
 CT_LISTOFTOKENS,			/*!< list of tokens */
 CT_FLOAT2,					/*!< float2 */
 CT_FLOAT3,					/*!< float3 */
 CT_FLOAT4,					/*!< float4 */
 CT_FLOAT7,					/*!< float7 */
 CT_FLOAT1X1,				/*!< float1x1 */
 CT_FLOAT1X2,				/*!< float1x2 */
 CT_FLOAT1X3,				/*!< float1x3 */
 CT_FLOAT1X4,				/*!< float1x4 */
 CT_FLOAT2X1,				/*!< float2x1 */
 CT_FLOAT2X2,				/*!< float2x2 */
 CT_FLOAT2X3,				/*!< float2x3 */
 CT_FLOAT2X4,				/*!< float2x4 */
 CT_FLOAT3X1,				/*!< float3x1 */
 CT_FLOAT3X2,				/*!< float3x2 */
 CT_FLOAT3X3,				/*!< float3x3 */
 CT_FLOAT3X4,				/*!< float3x4 */
 CT_FLOAT4X1,				/*!< float4x1 */
 CT_FLOAT4X2,				/*!< float4x2 */
 CT_FLOAT4X3,				/*!< float4x3 */
 CT_FLOAT4X4,				/*!< float4x4 */
 CT_INT2,					/*!< int2 */
 CT_INT3,					/*!< int3 */
 CT_INT4,					/*!< int4 */
 CT_INT1X1,					/*!< int1x1 */
 CT_INT1X2,					/*!< int1x2 */
 CT_INT1X3,					/*!< int1x3 */
 CT_INT1X4,					/*!< int1x4 */
 CT_INT2X1,					/*!< int2x1 */
 CT_INT2X2,					/*!< int2x2 */
 CT_INT2X3,					/*!< int2x3 */
 CT_INT2X4,					/*!< int2x4 */
 CT_INT3X1,					/*!< int3x1 */
 CT_INT3X2,					/*!< int3x2 */
 CT_INT3X3,					/*!< int3x3 */
 CT_INT3X4,					/*!< int3x4 */
 CT_INT4X1,					/*!< int4x1 */
 CT_INT4X2,					/*!< int4x2 */
 CT_INT4X3,					/*!< int4x3 */
 CT_INT4X4,					/*!< int4x4 */
 CT_BOOL2,					/*!< bool2 */
 CT_BOOL3,					/*!< bool3 */
 CT_BOOL4,					/*!< bool4 */
 CT_BOOL1X1,				/*!< bool1x1 */
 CT_BOOL1X2,				/*!< bool1x2 */
 CT_BOOL1X3,				/*!< bool1x3 */
 CT_BOOL1X4,				/*!< bool1x4 */
 CT_BOOL2X1,				/*!< bool2x1 */
 CT_BOOL2X2,				/*!< bool2x2 */
 CT_BOOL2X3,				/*!< bool2x3 */
 CT_BOOL2X4,				/*!< bool2x4 */
 CT_BOOL3X1,				/*!< bool3x1 */
 CT_BOOL3X2,				/*!< bool3x2 */
 CT_BOOL3X3,				/*!< bool3x3 */
 CT_BOOL3X4,				/*!< bool3x4 */
 CT_BOOL4X1,				/*!< bool4x1 */
 CT_BOOL4X2,				/*!< bool4x2 */
 CT_BOOL4X3,				/*!< bool4x3 */
 CT_BOOL4X4					/*!< bool4x4 */
 };
 /* \@}
 */

typedef struct tagCOLLADASimpleTypeEntry {
	char*					m_szName;
	ColladaSimpleType		m_iID;
	int						m_iCount;
} COLLADASimpleTypeEntry;

int	GetSimpleCount( int s );
const char* GetSimpleTypeName ( int s );
ColladaSimpleType GetSimpleType ( int s );

ColladaSimpleType GetColladaListType ( const char* in_szTag );
int					GetColladaListTypeCount ( const char* in_szTag );

//***************************************************************************************
// Typedefs
//***************************************************************************************
class CXSIParser;

// @type DOTXSICALLBACK | dotXSI Native Templates callback function.
typedef SI_Error ( *DOTXSIREADCALLBACK ) ( CXSIParser *in_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate );
typedef SI_Error ( *DOTXSIWRITECALLBACK ) ( CXSIParser *in_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate, SI_Int i_nLevel );

//***************************************************************************************
/*!	\brief This class represents a COLLADA template
*/
//***************************************************************************************

class XSIEXPORT CCOLLADATemplate : public CdotXSITemplate
{
public:

	/*! Default constructor.
	Sets the default version information, and the default read and write callbacks
	for the template.
	\return an instance of CCOLLADATemplate
	*/
	CCOLLADATemplate();

	/*! Constructor.
	Sets the type name of the template to the name give by \p i_sName.
	\param[in]	i_sName	Type name of the new template.
	\return	an instance of CCOLLADATemplate
	*/
	CCOLLADATemplate( CSIBCString *i_sName );

	/*! Destructor
	*/
    virtual ~CCOLLADATemplate();

	/*! Returns the attributes.
	\return	Reference to the CdotXSIParams container holding the CdotXSIParam attributes for this template.
	*/
	CdotXSIParams &Attributes() { return m_AttribCol; }

	/*! Adds a new attribute
	\param[in] in_szName name of the attribute
	\param[in] in_szValue value of the attribute
	*/
	CdotXSIParam *AddAttribute(const SI_Char* in_szName, const SI_Char* in_szValue);


	/*! Adds a new string parameter
	\param[in] in_szName name of the new parameter
	\param[in] in_iType type of the new parameter (corresponds to the ::ColladaSimpleType enum)
	\param[in] in_pStringValue value to use for the new parameter
	*/
	CdotXSIParam *AddParam(const SI_Char* in_szName, int in_iType, const SI_Char* in_pStringValue = NULL);

	/*! Adds a new float parameter
	\param[in] in_szName name of the new parameter
	\param[in] in_iType type of the new parameter (corresponds to the ::ColladaSimpleType enum)
	\param[in] in_fValue value to use for the new parameter
	*/
	CdotXSIParam *AddParam(const SI_Char* in_szName, int in_iType, SI_Float in_fValue);

	/*! Adds a new long parameter
	\param[in] in_szName name of the new parameter
	\param[in] in_iType type of the new parameter (corresponds to the ::ColladaSimpleType enum)
	\param[in] in_lValue value to use for the new parameter
	*/
	CdotXSIParam *AddParam(const SI_Char* in_szName, int in_iType, SI_Int in_lValue);

	/*! Adds a new short parameter
	\param[in] in_szName name of the new parameter
	\param[in] in_iType type of the new parameter (corresponds to the ::ColladaSimpleType enum)
	\param[in] in_sValue value to use for the new parameter
	*/
	CdotXSIParam *AddParam(const SI_Char* in_szName, int in_iType, SI_Short in_sValue);

	/*! Adds a new boolean parameter
	\param[in] in_szName name of the new parameter
	\param[in] in_iType type of the new parameter (corresponds to the ::ColladaSimpleType enum)
	\param[in] in_sValue value to use for the new parameter
	*/
	CdotXSIParam *AddParam(const SI_Char* in_szName, int in_iType, SI_Bool in_sValue);

	/*! Adds a template to the extra of this template
	\param[in] in_szName node name of the new extra
	\return	The extra template
	*/
	CCOLLADATemplate*	AddExtra ( const SI_Char* in_szName );

	/*! Attaches an existing template as an extra
	\param[in] in_pExtra pointer to the the extra to attach
	*/
	SI_Void				AttachExtra ( CdotXSITemplate* in_pExtra );

	/*! Attaches an existing template as an extra in a foreign profile
	\param[in] in_pExtra pointer to the the extra to attach
	*/
	SI_Void				AttachExtraForeignProfile ( CdotXSITemplate* in_pExtra );


	/*! Retrieves an extra template
	\param[in] in_szExtraName node name of the extra to retrieve
	\return	The extra template
	*/
	CCOLLADATemplate*	GetExtra ( const SI_Char* in_szExtraName );

	/*! Creates a named child template of this template
	\param[in] in_szName node name of the new child template
	\return	The child template
	*/
	CCOLLADATemplate*	CreateChildTemplate( const SI_Char* in_szName );

	/*! Initializes the template from its name
	\param[in] i_pChar		name from which the template will be initialized
	\param[in] in_pParser	pointer to the parser
	*/
	SI_Void				InitializeFromName( SI_Char *i_pChar, CXSIParser *in_pParser );

	/*! Sets the instance name of the template
	\param[in] i_sInstanceName	new instance name to set
	*/
	virtual				SI_Void SetInstanceName( CSIBCString i_sInstanceName );


	/*! Sets whether this template can carry COLLADA extras
	\param[in] in_bValue	true to allow extras
	*/
	SI_Void					SetCanCarryExtra (bool in_bValue) { m_bCanCarryExtra = in_bValue;};

	/*! Returns whether this template can carry COLLADA extras
	\retval	true if extras are allowed
	\retval	false if extras are not allowed
	*/
	bool					GetCanCarryExtra () { return m_bCanCarryExtra ;};

	/*! Returns the template associated with the source attribute
	\return	The template associated with the source
	*/
	CCOLLADATemplate*		ResolveSource();

	CSIBCString&			InstanciatedName() { return m_InstanciatedName; };

	virtual					CdotXSITemplate *Clone();
	void					Serialize ( CSIBCString& in_szBuffer );
	void					SerializeXML ( CSIBCString& in_szBuffer );
	void					UnSerialize ( CSIBCString& in_szBuffer );

	virtual 				bool IsCOLLADATemplate() { return true; }

protected:

	CCOLLADATemplate*		ResolveSource(SI_Char* in_pSourceName);
	CCOLLADATemplate*		CreateExtra();

	CdotXSIParams			m_AttribCol;
	CCOLLADATemplate*		m_pExtra;
	bool					m_bCanCarryExtra;
	CSIBCString				m_InstanciatedName;
};


//***************************************************************************************
// Functions
//***************************************************************************************

/*! \addtogroup glbfunc_template Global dotXSI template functions
	\@{

	Allocates a CCOLLADATemplate
	\param[in] in_pParent	Containing template (parent template)
	\param[in] in_szName	Node name of this template
	\return the newly created CCOLLADATemplate
*/
XSIEXPORT CCOLLADATemplate* CreateCOLLADATemplate(CdotXSITemplate* in_pParent = NULL, const SI_Char* in_szName = NULL);							//


/*! Allocates a CCOLLADATemplate for a dotXSI template
	\param[in] in_pParent	Containing template (parent template)
	\param[in] in_szName	Node name of this template
	\param[in] in_pParser	Pointer to the dotXSI parser
	\return the newly created CCOLLADATemplate
*/
XSIEXPORT CCOLLADATemplate* CreateCOLLADAdotXSITemplate(CdotXSITemplate* in_pParent, const SI_Char* in_szName, CXSIParser *in_pParser);

/* \@}
*/

//***************************************************************************************
// Function prototype to create templates....
//***************************************************************************************

typedef	CCOLLADATemplate* (*COLLADATemplateCreation)();
XSIEXPORT CCOLLADATemplate*	CreateGenericCOLLADATemplate ( const SI_Char* in_szName, SI_Int in_pParamCount, SI_Int in_VariantType );

//***************************************************************************************
// Write callbacks
//***************************************************************************************

XSIEXPORT SI_Error COLLADACompatibleWrite ( CXSIParser *in_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate, SI_Int i_nLevel );
XSIEXPORT SI_Error COLLADAGenericWrite ( CXSIParser *in_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate, SI_Int i_nLevel );
XSIEXPORT SI_Error COLLADAGenericWritePost ( CXSIParser *in_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate, SI_Int i_nLevel );
XSIEXPORT SI_Error COLLADACompatibleWritePost ( CXSIParser *in_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate, SI_Int i_nLevel );
XSIEXPORT SI_Error COLLADAGenericWriteNull ( CXSIParser *in_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate, SI_Int i_nLevel );


XSIEXPORT SI_Error COLLADATransformWriteCallback ( CXSIParser *in_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate, SI_Int i_nLevel );
XSIEXPORT SI_Error COLLADACustomPropertySetWriteCallback ( CXSIParser *in_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate, SI_Int i_nLevel );
XSIEXPORT SI_Error COLLADAInstanceAnimatioNWriteCallback ( CXSIParser *in_pParser, CdotXSITemplate *i_pCurrentTemplate, CdotXSITemplate *i_pNewTemplate, SI_Int i_nLevel );


//***************************************************************************************
// Helper Functions
//***************************************************************************************

/*! Searches for the \c in_iNth occurrence of a COLLADA xml element either recursively or directly under the node
	specified by name (\c &lt;in_szName&gt;>).
	\param[in]	in_pParent 			The element where to start searching recursively.
	\param[in]	in_szName			The node name of COLLADA xml elements to search for
	\param[in]	in_iNth				Number of the occurrence to find
	\param[in]	in_bSearchNodeOnly	Search only under \c in_pParent if it's a node or only inside the first node found.
	\return The CCOLLADATemplate found that corresponds to the COLLADA xml elements.
*/
XSIEXPORT CCOLLADATemplate*	FindNestedTemplateByName ( CCOLLADATemplate* in_pParent, SI_Char* in_szName, int in_iNth = 0, bool in_bSearchNodeOnly=false);

/*! Searches recursively for a COLLADA xml element by the \c id attribute (&lt;element id="in_szID"&gt;)
	\param[in]	in_pParent	The element where to start searching recursively.
	\param[in]	in_szID		The id of COLLADA xml elements to search for
	\return The CCOLLADATemplate found that corresponds to the specified COLLADA xml element
*/
XSIEXPORT CCOLLADATemplate*	FindNestedTemplateByID ( CdotXSITemplate* in_pParent, SI_Char* in_szID);

/*! Searches recursively for a COLLADA xml element by the \c sid attribute (&lt;element sid="in_szSID"&gt;)
	\param[in]	in_pParent	The element where to start searching recursively.
	\param[in]	in_szSID	The sid of COLLADA xml elements to search for
	\return CCOLLADATemplate* The CCOLLADATemplate found that corresponds to the COLLADA xml elements.
*/
XSIEXPORT CCOLLADATemplate*	FindNestedTemplateBySID ( CdotXSITemplate* in_pParent, SI_Char* in_szSID);

CCOLLADATemplate*	FindNestedTemplateByNameRec ( CCOLLADATemplate* in_pParent, SI_Char* in_szName, int in_iNth, int& i_iNth, bool in_bSearchNodeOnly);

#endif // __COLLADATEMPLATE_H
