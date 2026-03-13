//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the CUSTOMUITEST_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// CUSTOMUITEST_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef CUSTOMUITEST_EXPORTS
#define CUSTOMUITEST_API __declspec(dllexport)
#else
#define CUSTOMUITEST_API __declspec(dllimport)
#endif

#include <xsi_decl.h>
#include <xsi_viewnotification.h>

// This class is exported from the CustomUITest.dll
class CUSTOMUITEST_API CCustomUITest {
public:
	CCustomUITest(void);
	// TODO: add your methods here.
};

extern CUSTOMUITEST_API int nCustomUITest;

CUSTOMUITEST_API int	fnCustomUITest(void);
CUSTOMUITEST_API void	CustomView_Init		(XSI::CRef in_pViewCtx);
CUSTOMUITEST_API void	CustomView_Term		(XSI::CRef in_pViewCtx);
CUSTOMUITEST_API void	CustomView_Notify	(XSI::CRef in_pViewCtx);
CUSTOMUITEST_API char*	CustomView_Describe	();

