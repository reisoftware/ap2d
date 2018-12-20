# Microsoft Developer Studio Project File - Name="display" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=display - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "display.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "display.mak" CFG="display - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "display - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "display - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/apcheck/ap2d/Ap2D", PGAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "display - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\lib"
# PROP Intermediate_Dir "..\obj\display_r"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DISPLAY_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /O2 /I "../afc/" /I "../object" /I "../Geometry" /I "../cadio" /I "../include" /D "_USRDLL" /D "DISPLAY_EXPORTS" /D "OBJ_COUNTER" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 afc.lib object.lib Geometry.lib cadio.lib trace.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opengl32.lib glu32.lib /nologo /dll /profile /machine:I386 /out:"..\bin/display.dll" /libpath:"..\lib"

!ELSEIF  "$(CFG)" == "display - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\lib"
# PROP Intermediate_Dir "..\obj\display_d"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DISPLAY_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "../afc/" /I "../object" /I "../Geometry" /I "../cadio" /I "../include" /D "_USRDLL" /D "DISPLAY_EXPORTS" /D "TRACE_ENABLE" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opengl32.lib glu32.lib trace.lib cadio_d.lib object_d.lib Geometry_d.lib afc_d.lib /nologo /dll /debug /machine:I386 /out:"..\bin/display_d.dll " /pdbtype:sept /libpath:"..\lib"

!ENDIF 

# Begin Target

# Name "display - Win32 Release"
# Name "display - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Add_Dim_Command.cpp
# End Source File
# Begin Source File

SOURCE=.\Array_Command.cpp
# End Source File
# Begin Source File

SOURCE=.\Block_Command.cpp
# End Source File
# Begin Source File

SOURCE=.\Blue_Frame_Tools.cpp
# End Source File
# Begin Source File

SOURCE=.\Break_Command.cpp
# End Source File
# Begin Source File

SOURCE=.\Cad_Command.cpp
# End Source File
# Begin Source File

SOURCE=.\CadLib.cpp
# End Source File
# Begin Source File

SOURCE=.\Cmd_Mgr_d.cpp
# End Source File
# Begin Source File

SOURCE=.\Cmdln.cpp
# End Source File
# Begin Source File

SOURCE=.\Command_Line.cpp
# End Source File
# Begin Source File

SOURCE=.\Command_Line_In.cpp
# End Source File
# Begin Source File

SOURCE=.\Create_Command.cpp
# End Source File
# Begin Source File

SOURCE=.\Create_Dim_Axis_Dimension.cpp
# End Source File
# Begin Source File

SOURCE=.\Create_Dim_Lead_Dimension.cpp
# End Source File
# Begin Source File

SOURCE=.\Create_Dim_Text_Dimension.cpp
# End Source File
# Begin Source File

SOURCE=.\Create_Entity.cpp
# End Source File
# Begin Source File

SOURCE=.\Create_Rect.cpp
# End Source File
# Begin Source File

SOURCE=.\Create_Text.cpp
# End Source File
# Begin Source File

SOURCE=.\DB_Blocks.cpp
# End Source File
# Begin Source File

SOURCE=.\Del_Dim_Command.cpp
# End Source File
# Begin Source File

SOURCE=.\display.cpp
# End Source File
# Begin Source File

SOURCE=.\dxf_o.cpp
# End Source File
# Begin Source File

SOURCE=.\Dxf_Read.cpp
# End Source File
# Begin Source File

SOURCE=.\Edit_Command.cpp
# End Source File
# Begin Source File

SOURCE=.\Edit_Cut_Section.cpp
# End Source File
# Begin Source File

SOURCE=.\Edit_Entity_Property.cpp
# End Source File
# Begin Source File

SOURCE=.\Edit_Rectentity.cpp
# End Source File
# Begin Source File

SOURCE=.\Extend_Command.cpp
# End Source File
# Begin Source File

SOURCE=.\Flags.cpp
# End Source File
# Begin Source File

SOURCE=.\Idle_Command.cpp
# End Source File
# Begin Source File

SOURCE=.\Insert_Command.cpp
# End Source File
# Begin Source File

SOURCE=.\Layout_Dim_Base_Command.cpp
# End Source File
# Begin Source File

SOURCE=.\Layout_Dim_Line_Command.cpp
# End Source File
# Begin Source File

SOURCE=.\lead_dim_block_tools.cpp
# End Source File
# Begin Source File

SOURCE=.\ln_dim_block_tools.cpp
# End Source File
# Begin Source File

SOURCE=.\Mirror_Command.cpp
# End Source File
# Begin Source File

SOURCE=.\Move_Command.cpp
# End Source File
# Begin Source File

SOURCE=.\Move_Dim_Line_Command.cpp
# End Source File
# Begin Source File

SOURCE=.\Multi_Insert_Command.cpp
# End Source File
# Begin Source File

SOURCE=.\Offset_Command.cpp
# End Source File
# Begin Source File

SOURCE=.\Offset_Drag_Pt.cpp
# End Source File
# Begin Source File

SOURCE=.\Paint_Entity.cpp
# End Source File
# Begin Source File

SOURCE=.\Paint_Entity_Tools.cpp
# End Source File
# Begin Source File

SOURCE=.\Painter.cpp
# End Source File
# Begin Source File

SOURCE=.\Painter_Windows.cpp
# End Source File
# Begin Source File

SOURCE=.\Paper_Space.cpp
# End Source File
# Begin Source File

SOURCE=.\Re0_Dim_Command.cpp
# End Source File
# Begin Source File

SOURCE=.\Red_Rect_Frame.cpp
# End Source File
# Begin Source File

SOURCE=.\Rotate_Command.cpp
# End Source File
# Begin Source File

SOURCE=.\Scale_Command.cpp
# End Source File
# Begin Source File

SOURCE=.\Scene_d.cpp
# End Source File
# Begin Source File

SOURCE=.\Scene_Wnd.cpp
# End Source File
# Begin Source File

SOURCE=.\Scene_Wnd_Windows.cpp
# End Source File
# Begin Source File

SOURCE=.\Select_Font.cpp
# End Source File
# Begin Source File

SOURCE=.\Select_Pen.cpp
# End Source File
# Begin Source File

SOURCE=.\Split_Block_Command.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Strech_Command.cpp
# End Source File
# Begin Source File

SOURCE=.\Three_Pt_Dim_Block_Tools.cpp
# End Source File
# Begin Source File

SOURCE=.\Three_Pt_Dim_Tools.cpp
# End Source File
# Begin Source File

SOURCE=.\Trim_Command.cpp
# End Source File
# Begin Source File

SOURCE=.\Unite_Group_Command.cpp
# End Source File
# Begin Source File

SOURCE=.\Virtual_Key.cpp
# End Source File
# Begin Source File

SOURCE=.\Vmove_Line_Command.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Add_Dim_Command.h
# End Source File
# Begin Source File

SOURCE=.\Array_Command.h
# End Source File
# Begin Source File

SOURCE=.\Block_Command.h
# End Source File
# Begin Source File

SOURCE=.\Blue_Frame_Tools.h
# End Source File
# Begin Source File

SOURCE=.\Break_Command.h
# End Source File
# Begin Source File

SOURCE=.\Cad_Command.h
# End Source File
# Begin Source File

SOURCE=.\CadLib.h
# End Source File
# Begin Source File

SOURCE=.\Cmd_Mgr_d.h
# End Source File
# Begin Source File

SOURCE=.\Cmdln.h
# End Source File
# Begin Source File

SOURCE=.\Command_Line.h
# End Source File
# Begin Source File

SOURCE=.\Command_Line_In.h
# End Source File
# Begin Source File

SOURCE=.\Create_Command.h
# End Source File
# Begin Source File

SOURCE=.\Create_Dim_Axis_Dimension.h
# End Source File
# Begin Source File

SOURCE=.\Create_Dim_Lead_Dimension.h
# End Source File
# Begin Source File

SOURCE=.\Create_Dim_Text_Dimension.h
# End Source File
# Begin Source File

SOURCE=.\Create_Entity.h
# End Source File
# Begin Source File

SOURCE=.\Create_Rect.h
# End Source File
# Begin Source File

SOURCE=.\Create_Text.h
# End Source File
# Begin Source File

SOURCE=.\DB_Blocks.h
# End Source File
# Begin Source File

SOURCE=.\Del_Dim_Command.h
# End Source File
# Begin Source File

SOURCE=.\dim_block_tools.h
# End Source File
# Begin Source File

SOURCE=.\display_export.h
# End Source File
# Begin Source File

SOURCE=.\Dxf_Entities.h
# End Source File
# Begin Source File

SOURCE=.\dxf_o.h
# End Source File
# Begin Source File

SOURCE=.\Dxf_Read.h
# End Source File
# Begin Source File

SOURCE=.\Edit_Command.h
# End Source File
# Begin Source File

SOURCE=.\Edit_Cut_Section.h
# End Source File
# Begin Source File

SOURCE=.\Edit_Entity_Property.h
# End Source File
# Begin Source File

SOURCE=.\Edit_Rectentity.h
# End Source File
# Begin Source File

SOURCE=.\Entity_Array.h
# End Source File
# Begin Source File

SOURCE=.\Extend_Command.h
# End Source File
# Begin Source File

SOURCE=.\Flags.h
# End Source File
# Begin Source File

SOURCE=.\Idle_Command.h
# End Source File
# Begin Source File

SOURCE=.\Insert_Command.h
# End Source File
# Begin Source File

SOURCE=.\Layout_Dim_Base_Command.h
# End Source File
# Begin Source File

SOURCE=.\Layout_Dim_Line_Command.h
# End Source File
# Begin Source File

SOURCE=.\lead_dim_block_tools.h
# End Source File
# Begin Source File

SOURCE=.\ln_dim_block_tools.h
# End Source File
# Begin Source File

SOURCE=.\Mirror_Command.h
# End Source File
# Begin Source File

SOURCE=.\Move_Command.h
# End Source File
# Begin Source File

SOURCE=.\Move_Dim_Line_Command.h
# End Source File
# Begin Source File

SOURCE=.\Multi_Insert_Command.h
# End Source File
# Begin Source File

SOURCE=.\myalgorithm.h
# End Source File
# Begin Source File

SOURCE=.\Offset_Command.h
# End Source File
# Begin Source File

SOURCE=.\Offset_Drag_Pt.h
# End Source File
# Begin Source File

SOURCE=.\Paint_Entity.h
# End Source File
# Begin Source File

SOURCE=.\Paint_Entity_Tools.h
# End Source File
# Begin Source File

SOURCE=.\Painter.h
# End Source File
# Begin Source File

SOURCE=.\Painter_Windows.h
# End Source File
# Begin Source File

SOURCE=.\Paper_Space.h
# End Source File
# Begin Source File

SOURCE=.\Re0_Dim_Command.h
# End Source File
# Begin Source File

SOURCE=.\Red_Rect_Frame.h
# End Source File
# Begin Source File

SOURCE=.\Rotate_Command.h
# End Source File
# Begin Source File

SOURCE=.\Scale_Command.h
# End Source File
# Begin Source File

SOURCE=.\Scene_d.h
# End Source File
# Begin Source File

SOURCE=.\Scene_Wnd.h
# End Source File
# Begin Source File

SOURCE=.\Scene_Wnd_Windows.h
# End Source File
# Begin Source File

SOURCE=.\Select_Font.h
# End Source File
# Begin Source File

SOURCE=.\Select_Pen.h
# End Source File
# Begin Source File

SOURCE=.\Split_Block_Command.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Strech_Command.h
# End Source File
# Begin Source File

SOURCE=.\Three_Pt_Dim_Block_Tools.h
# End Source File
# Begin Source File

SOURCE=.\Three_Pt_Dim_Tools.h
# End Source File
# Begin Source File

SOURCE=.\Trim_Command.h
# End Source File
# Begin Source File

SOURCE=.\Unite_Group_Command.h
# End Source File
# Begin Source File

SOURCE=.\Virtual_Key.h
# End Source File
# Begin Source File

SOURCE=.\Vmove_Line_Command.h
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
