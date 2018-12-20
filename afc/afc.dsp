# Microsoft Developer Studio Project File - Name="afc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=afc - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "afc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "afc.mak" CFG="afc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "afc - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "afc - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/apcheck/ap2d/Ap2D", PGAAAAAA"
# PROP Scc_LocalPath "..\ap2d"
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "afc - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../lib/"
# PROP Intermediate_Dir "../obj/afc_r/"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "AFC_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../include" /D "_USRDLL" /D "AFC_EXPORTS" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib Wininet.lib libtcc.lib trace.lib lua51.lib net.lib /nologo /dll /machine:I386 /out:"../bin/afc.dll" /libpath:"../lib"

!ELSEIF  "$(CFG)" == "afc - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../lib/"
# PROP Intermediate_Dir "../obj/afc_d/"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "AFC_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "../include/" /D "_USRDLL" /D "AFC_EXPORTS" /D "TRACE_ENABLE" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib Wininet.lib libtcc.lib trace.lib lua51.lib net_d.lib /nologo /dll /debug /machine:I386 /out:"../bin/afc_d.dll" /pdbtype:sept /libpath:"../lib"

!ENDIF 

# Begin Target

# Name "afc - Win32 Release"
# Name "afc - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\afc.rc
# End Source File
# Begin Source File

SOURCE=.\array.cpp
# End Source File
# Begin Source File

SOURCE=.\ary.cpp
# End Source File
# Begin Source File

SOURCE=.\bool.cpp
# End Source File
# Begin Source File

SOURCE=.\call_tcc.cpp
# End Source File
# Begin Source File

SOURCE=.\case_sensitive.cpp
# End Source File
# Begin Source File

SOURCE=.\cbk.cpp
# End Source File
# Begin Source File

SOURCE=.\check.cpp
# End Source File
# Begin Source File

SOURCE=.\counter.cpp
# End Source File
# Begin Source File

SOURCE=.\dat.cpp
# End Source File
# Begin Source File

SOURCE=.\date_time.cpp
# End Source File
# Begin Source File

SOURCE=.\dir.cpp
# End Source File
# Begin Source File

SOURCE=.\dllmain.cpp
# End Source File
# Begin Source File

SOURCE=.\Dog_Check.cpp
# End Source File
# Begin Source File

SOURCE=.\dog_mgr.cpp
# End Source File
# Begin Source File

SOURCE=.\for_net.cpp
# End Source File
# Begin Source File

SOURCE=.\format.cpp
# End Source File
# Begin Source File

SOURCE=.\hk_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\hk_edit_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\hk_fhit.cpp
# End Source File
# Begin Source File

SOURCE=.\hk_key.cpp
# End Source File
# Begin Source File

SOURCE=.\hk_key_value.cpp
# End Source File
# Begin Source File

SOURCE=.\hk_sec.cpp
# End Source File
# Begin Source File

SOURCE=.\hotkey.cpp
# End Source File
# Begin Source File

SOURCE=.\ini.cpp
# End Source File
# Begin Source File

SOURCE=.\iolua.cpp
# End Source File
# Begin Source File

SOURCE=.\list_ctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\log.cpp
# End Source File
# Begin Source File

SOURCE=.\log_mgr.cpp
# End Source File
# Begin Source File

SOURCE=.\lua_fun.cpp
# End Source File
# Begin Source File

SOURCE=.\lua_mgr.cpp
# End Source File
# Begin Source File

SOURCE=.\Lua_Tab.cpp
# End Source File
# Begin Source File

SOURCE=.\mem_tools.cpp
# End Source File
# Begin Source File

SOURCE=.\net_ap.cpp
# End Source File
# Begin Source File

SOURCE=.\net_client.cpp
# End Source File
# Begin Source File

SOURCE=.\net_field.cpp
# End Source File
# Begin Source File

SOURCE=.\pass.cpp
# End Source File
# Begin Source File

SOURCE=.\rpt.cpp
# End Source File
# Begin Source File

SOURCE=.\rpt_add_symbol.cpp
# End Source File
# Begin Source File

SOURCE=.\rpt_api.cpp
# End Source File
# Begin Source File

SOURCE=.\rpt_api_state.cpp
# End Source File
# Begin Source File

SOURCE=.\rpt_book.cpp
# End Source File
# Begin Source File

SOURCE=.\rpt_column.cpp
# End Source File
# Begin Source File

SOURCE=.\rpt_fptr.cpp
# End Source File
# Begin Source File

SOURCE=.\rpt_pos_state.cpp
# End Source File
# Begin Source File

SOURCE=.\rpt_rule.cpp
# End Source File
# Begin Source File

SOURCE=.\rpt_rule_state.cpp
# End Source File
# Begin Source File

SOURCE=.\rpt_sheet.cpp
# End Source File
# Begin Source File

SOURCE=.\rpt_style_db.cpp
# End Source File
# Begin Source File

SOURCE=.\rpt_table.cpp
# End Source File
# Begin Source File

SOURCE=.\str.cpp
# End Source File
# Begin Source File

SOURCE=.\str_tools.cpp
# End Source File
# Begin Source File

SOURCE=.\tcc.cpp
# End Source File
# Begin Source File

SOURCE=.\test.cpp
# End Source File
# Begin Source File

SOURCE=.\trace.cpp
# End Source File
# Begin Source File

SOURCE=.\xls_book.cpp
# End Source File
# Begin Source File

SOURCE=.\xls_cell.cpp
# End Source File
# Begin Source File

SOURCE=.\xls_cell_style.cpp
# End Source File
# Begin Source File

SOURCE=.\xls_pos.cpp
# End Source File
# Begin Source File

SOURCE=.\xls_sheet.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\array.h
# End Source File
# Begin Source File

SOURCE=.\array_ptr.h
# End Source File
# Begin Source File

SOURCE=.\ary.h
# End Source File
# Begin Source File

SOURCE=.\bool.h
# End Source File
# Begin Source File

SOURCE=.\call_tcc.h
# End Source File
# Begin Source File

SOURCE=.\case_sensitive.h
# End Source File
# Begin Source File

SOURCE=.\cbk.h
# End Source File
# Begin Source File

SOURCE=.\char.h
# End Source File
# Begin Source File

SOURCE=.\check.h
# End Source File
# Begin Source File

SOURCE=.\counter.h
# End Source File
# Begin Source File

SOURCE=.\dat.h
# End Source File
# Begin Source File

SOURCE=.\dat_mgr.h
# End Source File
# Begin Source File

SOURCE=.\date_time.h
# End Source File
# Begin Source File

SOURCE=.\def_tools.h
# End Source File
# Begin Source File

SOURCE=.\dir.h
# End Source File
# Begin Source File

SOURCE=.\dllmain.h
# End Source File
# Begin Source File

SOURCE=.\Dog_Check.h
# End Source File
# Begin Source File

SOURCE=.\dog_mgr.h
# End Source File
# Begin Source File

SOURCE=.\export.h
# End Source File
# Begin Source File

SOURCE=.\for_net.h
# End Source File
# Begin Source File

SOURCE=.\format.h
# End Source File
# Begin Source File

SOURCE=.\group.h
# End Source File
# Begin Source File

SOURCE=.\Gsmh.h
# End Source File
# Begin Source File

SOURCE=.\hk_dlg.h
# End Source File
# Begin Source File

SOURCE=.\hk_edit_dlg.h
# End Source File
# Begin Source File

SOURCE=.\hk_fhit.h
# End Source File
# Begin Source File

SOURCE=.\hk_fptr.h
# End Source File
# Begin Source File

SOURCE=.\hk_key.h
# End Source File
# Begin Source File

SOURCE=.\hk_key_value.h
# End Source File
# Begin Source File

SOURCE=.\hk_sec.h
# End Source File
# Begin Source File

SOURCE=.\hotkey.h
# End Source File
# Begin Source File

SOURCE=.\ini.h
# End Source File
# Begin Source File

SOURCE=.\iolua.h
# End Source File
# Begin Source File

SOURCE=.\list_ctrl.h
# End Source File
# Begin Source File

SOURCE=.\log.h
# End Source File
# Begin Source File

SOURCE=.\log_mgr.h
# End Source File
# Begin Source File

SOURCE=.\lua_fun.h
# End Source File
# Begin Source File

SOURCE=.\lua_mgr.h
# End Source File
# Begin Source File

SOURCE=.\Lua_Tab.h
# End Source File
# Begin Source File

SOURCE=.\lua_tools.h
# End Source File
# Begin Source File

SOURCE=.\mem_tools.h
# End Source File
# Begin Source File

SOURCE=.\msg_mgr.h
# End Source File
# Begin Source File

SOURCE=.\net_ap.h
# End Source File
# Begin Source File

SOURCE=.\net_client.h
# End Source File
# Begin Source File

SOURCE=.\net_field.h
# End Source File
# Begin Source File

SOURCE=.\pass.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\rpt.h
# End Source File
# Begin Source File

SOURCE=.\rpt_add_symbol.h
# End Source File
# Begin Source File

SOURCE=.\rpt_api.h
# End Source File
# Begin Source File

SOURCE=.\rpt_api_state.h
# End Source File
# Begin Source File

SOURCE=.\rpt_book.h
# End Source File
# Begin Source File

SOURCE=.\rpt_column.h
# End Source File
# Begin Source File

SOURCE=.\rpt_def.h
# End Source File
# Begin Source File

SOURCE=.\rpt_fptr.h
# End Source File
# Begin Source File

SOURCE=.\rpt_pos_state.h
# End Source File
# Begin Source File

SOURCE=.\rpt_rule.h
# End Source File
# Begin Source File

SOURCE=.\rpt_rule_state.h
# End Source File
# Begin Source File

SOURCE=.\rpt_sheet.h
# End Source File
# Begin Source File

SOURCE=.\rpt_style_db.h
# End Source File
# Begin Source File

SOURCE=.\rpt_table.h
# End Source File
# Begin Source File

SOURCE=.\std_tools.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\str.h
# End Source File
# Begin Source File

SOURCE=.\str_tools.h
# End Source File
# Begin Source File

SOURCE=.\tcc.h
# End Source File
# Begin Source File

SOURCE=.\tcc_def.h
# End Source File
# Begin Source File

SOURCE=.\test.h
# End Source File
# Begin Source File

SOURCE=.\trace.h
# End Source File
# Begin Source File

SOURCE=.\xls_book.h
# End Source File
# Begin Source File

SOURCE=.\xls_cell.h
# End Source File
# Begin Source File

SOURCE=.\xls_cell_style.h
# End Source File
# Begin Source File

SOURCE=.\xls_pos.h
# End Source File
# Begin Source File

SOURCE=.\xls_sheet.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\hotkey_test\res\test.ico
# End Source File
# Begin Source File

SOURCE=..\hotkey_test\res\testDoc.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\obj\MHWIN32C.OBJ
# End Source File
# End Target
# End Project
