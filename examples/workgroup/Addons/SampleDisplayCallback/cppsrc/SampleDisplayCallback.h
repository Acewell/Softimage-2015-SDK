//***************************************************************************************
//
// File supervisor: Dominic Laflamme
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   
//
//***************************************************************************************


#ifndef unix
#ifdef SAMPLEDISPLAYCALLBACK_EXPORTS
#define SAMPLEDISPLAYCALLBACK_API __declspec(dllexport)
#else
#define SAMPLEDISPLAYCALLBACK_API __declspec(dllimport)
#endif
#else
#define SAMPLEDISPLAYCALLBACK_API
#define LPVOID void*
#endif

// we can safely ignore this warning, since we know that the 
// implementation of these functions will be done in C++
#ifdef _WIN32
#pragma warning(disable:4190)
#endif

#ifdef __cplusplus
extern "C" 
{

SAMPLEDISPLAYCALLBACK_API XSI::CStatus XSILoadPlugin( XSI::PluginRegistrar& in_reg );
SAMPLEDISPLAYCALLBACK_API XSI::CStatus XSIUnloadPlugin( const XSI::PluginRegistrar& in_reg );

// Display callbacks
SAMPLEDISPLAYCALLBACK_API void	MyClearScreenBuffer_Execute			( XSI::CRef, LPVOID * );
SAMPLEDISPLAYCALLBACK_API void	MyClearScreenBuffer_Init			( XSI::CRef, LPVOID * );
SAMPLEDISPLAYCALLBACK_API void	MyClearScreenBuffer_Term			( XSI::CRef, LPVOID * );
SAMPLEDISPLAYCALLBACK_API void	MyClearScreenBuffer_InitInstance	( XSI::CRef, LPVOID * );
SAMPLEDISPLAYCALLBACK_API void	MyClearScreenBuffer_TermInstance	( XSI::CRef, LPVOID * );

// custom display pass
SAMPLEDISPLAYCALLBACK_API void	MyCustomPass_Execute			( XSI::CRef, LPVOID * );
SAMPLEDISPLAYCALLBACK_API void	MyCustomPass_Init				( XSI::CRef, LPVOID * );
SAMPLEDISPLAYCALLBACK_API void	MyCustomPass_Term				( XSI::CRef, LPVOID * );
SAMPLEDISPLAYCALLBACK_API void	MyCustomPass_InitInstance		( XSI::CRef, LPVOID * );
SAMPLEDISPLAYCALLBACK_API void	MyCustomPass_TermInstance		( XSI::CRef, LPVOID * );

};
#endif
