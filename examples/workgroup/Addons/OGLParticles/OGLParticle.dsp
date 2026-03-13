# Microsoft Developer Studio Project File - Name="OGLParticle" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=OGLParticle - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "OGLParticle.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "OGLParticle.mak" CFG="OGLParticle - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OGLParticle - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OGLParticle - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "OGLParticle - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2  /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "$(XSISDK_ROOT)\include" /I "$(XSISDK_ROOT)\examples\realtimeshader\XSI_OGLHelper\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FD /c
# SUBTRACT CPP /YX
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 XSI_OGLHelper.lib opengl32.lib /nologo /dll /machine:I386 /out:"OGLParticle.dll" /libpath:"$(XSISDK_ROOT)\\lib\\nt-x86"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "OGLParticle - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "$(XSISDK_ROOT)\include" /I "$(XSISDK_ROOT)\examples\realtimeshader\XSI_OGLHelper\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /YX /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 XSI_OGLHelper.lib opengl32.lib /nologo /dll /debug /machine:I386 /out:"OGLParticle.dll" /pdbtype:sept /libpath:"$(XSISDK_ROOT)\\lib\\nt-x86"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "OGLParticle - Win32 Release"
# Name "OGLParticle - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c"
# Begin Source File

SOURCE=.\OGLParticle.cpp
# End Source File

# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=.\OGLParticle.h
# End Source File

# End Group
# Begin Group "SPDL Files"

# PROP Default_Filter "spdl"
# Begin Source File

SOURCE=.\OGLParticle.spdl
# End Source File

# End Group

# End Target
# End Project
