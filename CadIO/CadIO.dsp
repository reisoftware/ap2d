# Microsoft Developer Studio Project File - Name="CadIO" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=CadIO - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CadIO.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CadIO.mak" CFG="CadIO - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CadIO - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CadIO - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/apcheck/ap2d/Ap2D", PGAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CadIO - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\lib"
# PROP Intermediate_Dir "..\obj\CadIO_r"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CADIO_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../afc/" /I "../object/" /I "../include" /D "_USRDLL" /D "CADIO_EXPORTS" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib object.lib geometry.lib /nologo /dll /machine:I386 /out:"..\bin/CadIO.dll" /libpath:"..\lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "CadIO - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\lib"
# PROP Intermediate_Dir "..\obj\CadIO_d"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CADIO_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../afc/" /I "../object/" /I "../include" /D "_USRDLL" /D "CADIO_EXPORTS" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "TRACE_ENABLE" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib object_d.lib Geometry_d.lib /nologo /dll /debug /machine:I386 /out:"..\bin/CadIO_d.dll" /pdbtype:sept /libpath:"..\lib"
# SUBTRACT LINK32 /incremental:no

!ENDIF 

# Begin Target

# Name "CadIO - Win32 Release"
# Name "CadIO - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CadIO.cpp
# End Source File
# Begin Source File

SOURCE=.\CadIO.rc
# End Source File
# Begin Source File

SOURCE=.\DimView.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawingDataChange.cpp
# End Source File
# Begin Source File

SOURCE=.\DRBlocks.cpp
# End Source File
# Begin Source File

SOURCE=.\DREntities.cpp
# End Source File
# Begin Source File

SOURCE=.\DRTables.cpp
# End Source File
# Begin Source File

SOURCE=.\DrwIO.cpp
# End Source File
# Begin Source File

SOURCE=.\DWBlocks.cpp
# End Source File
# Begin Source File

SOURCE=.\DWEntities.cpp
# End Source File
# Begin Source File

SOURCE=.\DWTables.cpp
# End Source File
# Begin Source File

SOURCE=.\DXFBase.cpp
# End Source File
# Begin Source File

SOURCE=.\DXFRead.cpp
# End Source File
# Begin Source File

SOURCE=.\DXFWrite.cpp
# End Source File
# Begin Source File

SOURCE=.\MemDrw.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TextView.cpp
# End Source File
# Begin Source File

SOURCE=.\View.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CadIO.def

!IF  "$(CFG)" == "CadIO - Win32 Release"

!ELSEIF  "$(CFG)" == "CadIO - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CadIO.h
# End Source File
# Begin Source File

SOURCE=.\CadIO_d.def

!IF  "$(CFG)" == "CadIO - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "CadIO - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Colors.h
# End Source File
# Begin Source File

SOURCE=.\DimView.h
# End Source File
# Begin Source File

SOURCE=.\DrawingDataChange.h
# End Source File
# Begin Source File

SOURCE=.\DrawingDef.h
# End Source File
# Begin Source File

SOURCE=.\DRBlocks.h
# End Source File
# Begin Source File

SOURCE=.\DREntities.h
# End Source File
# Begin Source File

SOURCE=.\DRTables.h
# End Source File
# Begin Source File

SOURCE=.\DrwIO.h
# End Source File
# Begin Source File

SOURCE=.\DWBlocks.h
# End Source File
# Begin Source File

SOURCE=.\DWEntities.h
# End Source File
# Begin Source File

SOURCE=.\DWTables.h
# End Source File
# Begin Source File

SOURCE=.\DXFBase.h
# End Source File
# Begin Source File

SOURCE=.\DXFDef.h
# End Source File
# Begin Source File

SOURCE=.\DXFRead.h
# End Source File
# Begin Source File

SOURCE=.\DXFWrite.h
# End Source File
# Begin Source File

SOURCE=.\MemDrw.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\SimpleList.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TextView.h
# End Source File
# Begin Source File

SOURCE=.\View.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
