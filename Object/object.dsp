# Microsoft Developer Studio Project File - Name="object" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=object - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "object.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "object.mak" CFG="object - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "object - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "object - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/apcheck/ap2d/Ap2D", PGAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "object - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\lib"
# PROP Intermediate_Dir "..\obj\object_r"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "OBJECT_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /O2 /I "../afc/" /I "../include" /D "_USRDLL" /D "OBJECT_EXPORTS" /D "OBJ_COUNTER" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 trace.lib Geometry.lib afc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib lua51.lib trace.lib Geometry.lib afc.lib net.lib /nologo /dll /profile /machine:I386 /out:"..\bin/object.dll" /libpath:"..\lib"

!ELSEIF  "$(CFG)" == "object - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\lib"
# PROP Intermediate_Dir "..\obj\object_d"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "OBJECT_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "../afc/" /I "../include" /D "_USRDLL" /D "OBJECT_EXPORTS" /D "TRACE_ENABLE" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib trace.lib Geometry_d.lib afc_d.lib lua51.lib net.lib /nologo /dll /debug /machine:I386 /out:"..\bin/object_d.dll " /pdbtype:sept /libpath:"..\lib"

!ENDIF 

# Begin Target

# Name "object - Win32 Release"
# Name "object - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Angle_Dimension.cpp
# End Source File
# Begin Source File

SOURCE=.\Arc_Arrow.cpp
# End Source File
# Begin Source File

SOURCE=.\Block.cpp
# End Source File
# Begin Source File

SOURCE=.\calculate.cpp
# End Source File
# Begin Source File

SOURCE=.\Circle.cpp
# End Source File
# Begin Source File

SOURCE=.\Cloud_Line.cpp
# End Source File
# Begin Source File

SOURCE=.\Color.cpp
# End Source File
# Begin Source File

SOURCE=.\color_and_index.cpp
# End Source File
# Begin Source File

SOURCE=.\complex.cpp
# End Source File
# Begin Source File

SOURCE=.\Cut_Section.cpp
# End Source File
# Begin Source File

SOURCE=.\Database.cpp
# End Source File
# Begin Source File

SOURCE=.\Database_Private.cpp
# End Source File
# Begin Source File

SOURCE=.\dim.cpp
# End Source File
# Begin Source File

SOURCE=.\Dim_Angle.cpp
# End Source File
# Begin Source File

SOURCE=.\Dim_Angle_Lean.cpp
# End Source File
# Begin Source File

SOURCE=.\Dimension.cpp
# End Source File
# Begin Source File

SOURCE=.\Dimension_Style.cpp
# End Source File
# Begin Source File

SOURCE=.\Entity.cpp
# End Source File
# Begin Source File

SOURCE=.\Entity_Calculate.cpp
# End Source File
# Begin Source File

SOURCE=.\Entity_ID.cpp
# End Source File
# Begin Source File

SOURCE=.\Entity_Snap.cpp
# End Source File
# Begin Source File

SOURCE=.\File.cpp
# End Source File
# Begin Source File

SOURCE=.\geo2d.cpp
# End Source File
# Begin Source File

SOURCE=.\geo_obj.cpp
# End Source File
# Begin Source File

SOURCE=.\Global.cpp
# End Source File
# Begin Source File

SOURCE=.\Group.cpp
# End Source File
# Begin Source File

SOURCE=.\Group_Ents.cpp
# End Source File
# Begin Source File

SOURCE=.\intersect.cpp
# End Source File
# Begin Source File

SOURCE=.\Layer.cpp
# End Source File
# Begin Source File

SOURCE=.\Lead_Dimension.cpp
# End Source File
# Begin Source File

SOURCE=.\Lead_Dimension_Block.cpp
# End Source File
# Begin Source File

SOURCE=.\Lead_Dimension_Info.cpp
# End Source File
# Begin Source File

SOURCE=.\Lead_Dimension_MT.cpp
# End Source File
# Begin Source File

SOURCE=.\Line.cpp
# End Source File
# Begin Source File

SOURCE=.\Line_Arrow.cpp
# End Source File
# Begin Source File

SOURCE=.\line_dim.cpp
# End Source File
# Begin Source File

SOURCE=.\Line_Type.cpp
# End Source File
# Begin Source File

SOURCE=.\Ln_Dim.cpp
# End Source File
# Begin Source File

SOURCE=.\Ln_Dim_Block.cpp
# End Source File
# Begin Source File

SOURCE=.\Ln_Dim_Direct.cpp
# End Source File
# Begin Source File

SOURCE=.\Ln_Dim_PlateSide.cpp
# End Source File
# Begin Source File

SOURCE=.\Matrix_d.cpp
# End Source File
# Begin Source File

SOURCE=.\Normal.cpp
# End Source File
# Begin Source File

SOURCE=.\object.cpp
# End Source File
# Begin Source File

SOURCE=.\Object1.cpp
# End Source File
# Begin Source File

SOURCE=.\Paint_Snap.cpp
# End Source File
# Begin Source File

SOURCE=.\Point.cpp
# End Source File
# Begin Source File

SOURCE=.\Radius_Dimension.cpp
# End Source File
# Begin Source File

SOURCE=.\RArc.cpp
# End Source File
# Begin Source File

SOURCE=.\Rect.cpp
# End Source File
# Begin Source File

SOURCE=.\Rectentity.cpp
# End Source File
# Begin Source File

SOURCE=.\Replace_String.cpp
# End Source File
# Begin Source File

SOURCE=.\Replace_String_Center.cpp
# End Source File
# Begin Source File

SOURCE=.\Snap.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\String_Op.cpp
# End Source File
# Begin Source File

SOURCE=.\style.cpp
# End Source File
# Begin Source File

SOURCE=.\Text.cpp
# End Source File
# Begin Source File

SOURCE=.\Text_Dimension.cpp
# End Source File
# Begin Source File

SOURCE=.\Text_Dimension_Info.cpp
# End Source File
# Begin Source File

SOURCE=.\Text_Style.cpp
# End Source File
# Begin Source File

SOURCE=.\Three_Pt_Dimension.cpp
# End Source File
# Begin Source File

SOURCE=.\Three_Pt_Dimension_Block.cpp
# End Source File
# Begin Source File

SOURCE=.\Transform_Func.cpp
# End Source File
# Begin Source File

SOURCE=.\Visitor.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Angle_Dimension.h
# End Source File
# Begin Source File

SOURCE=.\Arc_Arrow.h
# End Source File
# Begin Source File

SOURCE=.\Block.h
# End Source File
# Begin Source File

SOURCE=.\calculate.h
# End Source File
# Begin Source File

SOURCE=.\Circle.h
# End Source File
# Begin Source File

SOURCE=.\Cloud_Line.h
# End Source File
# Begin Source File

SOURCE=.\Color.h
# End Source File
# Begin Source File

SOURCE=.\color_and_index.h
# End Source File
# Begin Source File

SOURCE=.\complex.h
# End Source File
# Begin Source File

SOURCE=.\Cut_Section.h
# End Source File
# Begin Source File

SOURCE=.\Database.h
# End Source File
# Begin Source File

SOURCE=.\Database_Private.h
# End Source File
# Begin Source File

SOURCE=.\dim.h
# End Source File
# Begin Source File

SOURCE=.\Dim_Angle.h
# End Source File
# Begin Source File

SOURCE=.\Dim_Angle_Lean.h
# End Source File
# Begin Source File

SOURCE=.\Dimension.h
# End Source File
# Begin Source File

SOURCE=.\Dimension_Style.h
# End Source File
# Begin Source File

SOURCE=.\DrawEntity.h
# End Source File
# Begin Source File

SOURCE=.\Edit_Entity.h
# End Source File
# Begin Source File

SOURCE=.\Entity.h
# End Source File
# Begin Source File

SOURCE=.\Entity_Calculate.h
# End Source File
# Begin Source File

SOURCE=.\Entity_ID.h
# End Source File
# Begin Source File

SOURCE=.\Entity_Snap.h
# End Source File
# Begin Source File

SOURCE=.\export.h
# End Source File
# Begin Source File

SOURCE=.\File.h
# End Source File
# Begin Source File

SOURCE=.\geo2d.h
# End Source File
# Begin Source File

SOURCE=.\geo_obj.h
# End Source File
# Begin Source File

SOURCE=.\Global.h
# End Source File
# Begin Source File

SOURCE=.\Group.h
# End Source File
# Begin Source File

SOURCE=.\Group_Ents.h
# End Source File
# Begin Source File

SOURCE=.\intersect.h
# End Source File
# Begin Source File

SOURCE=.\Layer.h
# End Source File
# Begin Source File

SOURCE=.\Lead_Dimension.h
# End Source File
# Begin Source File

SOURCE=.\Lead_Dimension_Block.h
# End Source File
# Begin Source File

SOURCE=.\Lead_Dimension_Info.h
# End Source File
# Begin Source File

SOURCE=.\Lead_Dimension_MT.h
# End Source File
# Begin Source File

SOURCE=.\Line.h
# End Source File
# Begin Source File

SOURCE=.\Line_Arrow.h
# End Source File
# Begin Source File

SOURCE=.\line_dim.h
# End Source File
# Begin Source File

SOURCE=.\Line_Type.h
# End Source File
# Begin Source File

SOURCE=.\Ln_Dim.h
# End Source File
# Begin Source File

SOURCE=.\Ln_Dim_Block.h
# End Source File
# Begin Source File

SOURCE=.\Ln_Dim_Direct.h
# End Source File
# Begin Source File

SOURCE=.\Ln_Dim_PlateSide.h
# End Source File
# Begin Source File

SOURCE=.\Matrix_d.h
# End Source File
# Begin Source File

SOURCE=.\Normal.h
# End Source File
# Begin Source File

SOURCE=.\Object1.h
# End Source File
# Begin Source File

SOURCE=.\Paint_Snap.h
# End Source File
# Begin Source File

SOURCE=.\Point.h
# End Source File
# Begin Source File

SOURCE=.\Radius_Dimension.h
# End Source File
# Begin Source File

SOURCE=.\RArc.h
# End Source File
# Begin Source File

SOURCE=.\Rect.h
# End Source File
# Begin Source File

SOURCE=.\Rectentity.h
# End Source File
# Begin Source File

SOURCE=.\Replace_String.h
# End Source File
# Begin Source File

SOURCE=.\Replace_String_Center.h
# End Source File
# Begin Source File

SOURCE=.\Snap.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\String_Op.h
# End Source File
# Begin Source File

SOURCE=.\style.h
# End Source File
# Begin Source File

SOURCE=.\Text.h
# End Source File
# Begin Source File

SOURCE=.\Text_Dimension.h
# End Source File
# Begin Source File

SOURCE=.\Text_Dimension_Info.h
# End Source File
# Begin Source File

SOURCE=.\Text_Style.h
# End Source File
# Begin Source File

SOURCE=.\Three_Pt_Dimension.h
# End Source File
# Begin Source File

SOURCE=.\Three_Pt_Dimension_Block.h
# End Source File
# Begin Source File

SOURCE=.\Transform_Func.h
# End Source File
# Begin Source File

SOURCE=.\Visitor.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
