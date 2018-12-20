# Microsoft Developer Studio Project File - Name="Ap2D" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Ap2D - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Ap2D.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Ap2D.mak" CFG="Ap2D - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Ap2D - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Ap2D - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/apcheck/ap2d/Ap2D", PGAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Ap2D - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\lib"
# PROP Intermediate_Dir "..\obj\ap2d_r"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../afc/" /I "../object" /I "../Geometry" /I "../cadio" /I "../include" /I "../display" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "TRACE_ENABLE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 trace.lib cadio_d.lib object.lib afc.lib display.lib geometry.lib net.lib lua5.1.lib /nologo /subsystem:windows /machine:I386 /out:"..\bin/Ap2D.exe" /libpath:"..\lib"

!ELSEIF  "$(CFG)" == "Ap2D - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\lib"
# PROP Intermediate_Dir "..\obj\ap2d_d"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../afc/" /I "../object" /I "../Geometry" /I "../cadio" /I "../include" /I "../display" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "TRACE_ENABLE" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 trace.lib cadio_d.lib object_d.lib afc_d.lib display_d.lib geometry_d.lib net_d.lib lua5.1.lib /nologo /subsystem:windows /debug /machine:I386 /out:"..\bin/Ap2D_d.exe" /pdbtype:sept /libpath:"..\lib"

!ENDIF 

# Begin Target

# Name "Ap2D - Win32 Release"
# Name "Ap2D - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Ap2D.cpp
# End Source File
# Begin Source File

SOURCE=.\Ap2D.rc
# End Source File
# Begin Source File

SOURCE=.\ap2d_check.cpp
# End Source File
# Begin Source File

SOURCE=.\ap2d_objs.cpp
# End Source File
# Begin Source File

SOURCE=.\Ap2DDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Ap2DView.cpp
# End Source File
# Begin Source File

SOURCE=.\ApLayer_Ent.cpp
# End Source File
# Begin Source File

SOURCE=.\ApNet_Check.cpp
# End Source File
# Begin Source File

SOURCE=.\Array_Cad_Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Cmd_Cancel_Combination.cpp
# End Source File
# Begin Source File

SOURCE=.\Cmd_Check_Text.cpp
# End Source File
# Begin Source File

SOURCE=.\Cmd_Combination.cpp
# End Source File
# Begin Source File

SOURCE=.\Cmd_Dim_Solpe.cpp
# End Source File
# Begin Source File

SOURCE=.\Cmd_Draw_Center.cpp
# End Source File
# Begin Source File

SOURCE=.\Cmd_Draw_Middle.cpp
# End Source File
# Begin Source File

SOURCE=.\Cmd_Extend_Line.cpp
# End Source File
# Begin Source File

SOURCE=.\Cmd_Extend_Line_Arrow.cpp
# End Source File
# Begin Source File

SOURCE=.\Cmd_Insert_Block.cpp
# End Source File
# Begin Source File

SOURCE=.\Cmd_Select.cpp
# End Source File
# Begin Source File

SOURCE=.\Cmd_Select_Joint.cpp
# End Source File
# Begin Source File

SOURCE=.\Cmd_Select_Text.cpp
# End Source File
# Begin Source File

SOURCE=.\Color_ComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\Command_Line_Info.cpp
# End Source File
# Begin Source File

SOURCE=.\CreateCmd.cpp
# End Source File
# Begin Source File

SOURCE=.\DB_Change.cpp
# End Source File
# Begin Source File

SOURCE=.\DB_Company.cpp
# End Source File
# Begin Source File

SOURCE=.\DB_Configure.cpp
# End Source File
# Begin Source File

SOURCE=.\DB_Detail.cpp
# End Source File
# Begin Source File

SOURCE=.\DB_File.cpp
# End Source File
# Begin Source File

SOURCE=.\DB_File_Date.cpp
# End Source File
# Begin Source File

SOURCE=.\DB_Jishou.cpp
# End Source File
# Begin Source File

SOURCE=.\DB_Layer.cpp
# End Source File
# Begin Source File

SOURCE=.\DB_Text_Replace.cpp
# End Source File
# Begin Source File

SOURCE=.\DB_Tree.cpp
# End Source File
# Begin Source File

SOURCE=.\DB_View.cpp
# End Source File
# Begin Source File

SOURCE=.\Decompose_Entity.cpp
# End Source File
# Begin Source File

SOURCE=.\DimInfo_IO.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_ApNet.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Auto_Check.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Auto_Check_Main.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Block_Manage.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Compare_Dxf.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Dim_Name_Set.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Dim_Texts_Edit.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Edit_Hotkey.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_File_Mgr.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Find_Tool.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Hot_Key.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Input.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Jishou_add.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Joint_DB.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Joint_DB_Edit.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Layer_DB.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Login.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Project_Mgr.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Project_Paths_Save.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Replace_Material.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Select_Color.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Select_Name.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Select_Table_Text.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Setting.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Setup.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Sign_Replace.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Tip_Infoes.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSetServer.cpp
# End Source File
# Begin Source File

SOURCE=.\Draw_Entities.cpp
# End Source File
# Begin Source File

SOURCE=.\Dxf_Save.cpp
# End Source File
# Begin Source File

SOURCE=.\Ex_ListCtrl_Sort.cpp
# End Source File
# Begin Source File

SOURCE=.\Global.cpp
# End Source File
# Begin Source File

SOURCE=.\InEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\Left_Mgr.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\md5.cpp
# End Source File
# Begin Source File

SOURCE=.\Mgr_Control.cpp
# End Source File
# Begin Source File

SOURCE=.\Mgr_Convert.cpp
# End Source File
# Begin Source File

SOURCE=.\Mgr_Database.cpp
# End Source File
# Begin Source File

SOURCE=.\Mgr_Detail.cpp
# End Source File
# Begin Source File

SOURCE=.\Mgr_Dxfs.cpp
# End Source File
# Begin Source File

SOURCE=.\Mgr_Entity.cpp
# End Source File
# Begin Source File

SOURCE=.\Mgr_File.cpp
# End Source File
# Begin Source File

SOURCE=.\Mgr_Layers.cpp
# End Source File
# Begin Source File

SOURCE=.\Mgr_Lua.cpp
# End Source File
# Begin Source File

SOURCE=.\Mgr_Memory.cpp
# End Source File
# Begin Source File

SOURCE=.\Mgr_Toolbar.cpp
# End Source File
# Begin Source File

SOURCE=.\Mgr_Tree.cpp
# End Source File
# Begin Source File

SOURCE=.\Model_DB.cpp
# End Source File
# Begin Source File

SOURCE=.\Page_Arrow.cpp
# End Source File
# Begin Source File

SOURCE=.\Page_Common.cpp
# End Source File
# Begin Source File

SOURCE=.\Page_Dim.cpp
# End Source File
# Begin Source File

SOURCE=.\Page_Dim_Texts.cpp
# End Source File
# Begin Source File

SOURCE=.\Page_Radius.cpp
# End Source File
# Begin Source File

SOURCE=.\Page_Text.cpp
# End Source File
# Begin Source File

SOURCE=.\Page_Text_Common.cpp
# End Source File
# Begin Source File

SOURCE=.\Project_Check.cpp
# End Source File
# Begin Source File

SOURCE=.\PutBar.cpp
# End Source File
# Begin Source File

SOURCE=.\Replace_String.cpp
# End Source File
# Begin Source File

SOURCE=.\sizecbar.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Tab_Entity.cpp
# End Source File
# Begin Source File

SOURCE=.\TabCtrl_Left.cpp
# End Source File
# Begin Source File

SOURCE=.\TabCtrl_Sheet.cpp
# End Source File
# Begin Source File

SOURCE=.\Toolbar_Combo.cpp
# End Source File
# Begin Source File

SOURCE=.\TrueColorToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\View.cpp
# End Source File
# Begin Source File

SOURCE=.\View_Tree.cpp
# End Source File
# Begin Source File

SOURCE=.\Vis_Ent_Dblclk.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Ap2D.h
# End Source File
# Begin Source File

SOURCE=.\ap2d_check.h
# End Source File
# Begin Source File

SOURCE=.\ap2d_objs.h
# End Source File
# Begin Source File

SOURCE=.\Ap2DDoc.h
# End Source File
# Begin Source File

SOURCE=.\Ap2DView.h
# End Source File
# Begin Source File

SOURCE=.\ApLayer_Ent.h
# End Source File
# Begin Source File

SOURCE=.\ApNet_Check.h
# End Source File
# Begin Source File

SOURCE=.\Array_Cad_Dlg.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\Cmd_Cancel_Combination.h
# End Source File
# Begin Source File

SOURCE=.\Cmd_Check_Text.h
# End Source File
# Begin Source File

SOURCE=.\Cmd_Combination.h
# End Source File
# Begin Source File

SOURCE=.\Cmd_Dim_Solpe.h
# End Source File
# Begin Source File

SOURCE=.\Cmd_Draw_Center.h
# End Source File
# Begin Source File

SOURCE=.\Cmd_Draw_Middle.h
# End Source File
# Begin Source File

SOURCE=.\Cmd_Extend_Line.h
# End Source File
# Begin Source File

SOURCE=.\Cmd_Extend_Line_Arrow.h
# End Source File
# Begin Source File

SOURCE=.\Cmd_Insert_Block.h
# End Source File
# Begin Source File

SOURCE=.\Cmd_Select.h
# End Source File
# Begin Source File

SOURCE=.\Cmd_Select_Joint.h
# End Source File
# Begin Source File

SOURCE=.\Cmd_Select_Text.h
# End Source File
# Begin Source File

SOURCE=.\Color_ComboBox.h
# End Source File
# Begin Source File

SOURCE=.\Command_Line_Info.h
# End Source File
# Begin Source File

SOURCE=.\CreateCmd.h
# End Source File
# Begin Source File

SOURCE=.\DB_Change.h
# End Source File
# Begin Source File

SOURCE=.\DB_Company.h
# End Source File
# Begin Source File

SOURCE=.\DB_Configure.h
# End Source File
# Begin Source File

SOURCE=.\DB_Detail.h
# End Source File
# Begin Source File

SOURCE=.\DB_File.h
# End Source File
# Begin Source File

SOURCE=.\DB_File_Date.h
# End Source File
# Begin Source File

SOURCE=.\DB_Jishou.h
# End Source File
# Begin Source File

SOURCE=.\DB_Layer.h
# End Source File
# Begin Source File

SOURCE=.\DB_Templete.h
# End Source File
# Begin Source File

SOURCE=.\DB_Text_Replace.h
# End Source File
# Begin Source File

SOURCE=.\DB_Tree.h
# End Source File
# Begin Source File

SOURCE=.\DB_View.h
# End Source File
# Begin Source File

SOURCE=.\Decompose_Entity.h
# End Source File
# Begin Source File

SOURCE=.\DimInfo_IO.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_ApNet.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Auto_Check.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Auto_Check_Main.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Block_Manage.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Compare_Dxf.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Dim_Name_Set.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Dim_Texts_Edit.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Edit_Hotkey.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_File_Mgr.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Find_Tool.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Hot_Key.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Input.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Jishou_add.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Joint_DB.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Joint_DB_Edit.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Layer_DB.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Login.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Project_Mgr.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Project_Paths_Save.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Replace_Material.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Select_Color.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Select_Name.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Select_Table_Text.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Setting.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Setup.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Sign_Replace.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Tip_Infoes.h
# End Source File
# Begin Source File

SOURCE=.\DlgSetServer.h
# End Source File
# Begin Source File

SOURCE=.\Draw_Entities.h
# End Source File
# Begin Source File

SOURCE=.\Dxf_Save.h
# End Source File
# Begin Source File

SOURCE=.\Ex_ListCtrl_Sort.h
# End Source File
# Begin Source File

SOURCE=.\Global.h
# End Source File
# Begin Source File

SOURCE=.\InEdit.h
# End Source File
# Begin Source File

SOURCE=.\Left_Mgr.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\md5.h
# End Source File
# Begin Source File

SOURCE=.\Mgr_Control.h
# End Source File
# Begin Source File

SOURCE=.\Mgr_Convert.h
# End Source File
# Begin Source File

SOURCE=.\Mgr_Database.h
# End Source File
# Begin Source File

SOURCE=.\Mgr_Detail.h
# End Source File
# Begin Source File

SOURCE=.\Mgr_Dxfs.h
# End Source File
# Begin Source File

SOURCE=.\Mgr_Entity.h
# End Source File
# Begin Source File

SOURCE=.\Mgr_File.h
# End Source File
# Begin Source File

SOURCE=.\Mgr_Layers.h
# End Source File
# Begin Source File

SOURCE=.\Mgr_Lua.h
# End Source File
# Begin Source File

SOURCE=.\Mgr_Memory.h
# End Source File
# Begin Source File

SOURCE=.\Mgr_Toolbar.h
# End Source File
# Begin Source File

SOURCE=.\Mgr_Tree.h
# End Source File
# Begin Source File

SOURCE=.\Model_DB.h
# End Source File
# Begin Source File

SOURCE=.\Page_Arrow.h
# End Source File
# Begin Source File

SOURCE=.\Page_Common.h
# End Source File
# Begin Source File

SOURCE=.\Page_Dim.h
# End Source File
# Begin Source File

SOURCE=.\Page_Dim_Texts.h
# End Source File
# Begin Source File

SOURCE=.\Page_Radius.h
# End Source File
# Begin Source File

SOURCE=.\Page_Text.h
# End Source File
# Begin Source File

SOURCE=.\Page_Text_Common.h
# End Source File
# Begin Source File

SOURCE=.\Project_Check.h
# End Source File
# Begin Source File

SOURCE=.\PutBar.h
# End Source File
# Begin Source File

SOURCE=.\Replace_String.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\sizecbar.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Tab_Entity.h
# End Source File
# Begin Source File

SOURCE=.\TabCtrl_Left.h
# End Source File
# Begin Source File

SOURCE=.\TabCtrl_Sheet.h
# End Source File
# Begin Source File

SOURCE=.\Toolbar_Combo.h
# End Source File
# Begin Source File

SOURCE=.\TrueColorToolBar.h
# End Source File
# Begin Source File

SOURCE=.\View.h
# End Source File
# Begin Source File

SOURCE=.\View_Tree.h
# End Source File
# Begin Source File

SOURCE=.\Vis_Ent_Dblclk.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Ap2D.ico
# End Source File
# Begin Source File

SOURCE=.\res\Ap2D.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Ap2DDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\res\change.bmp
# End Source File
# Begin Source File

SOURCE=.\res\classica.bmp
# End Source File
# Begin Source File

SOURCE=.\res\current1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\error.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon3.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon4.ico
# End Source File
# Begin Source File

SOURCE=.\res\IDB_BMP_CREATE.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDB_BMP_EDIT.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDB_BMP_SNAP.bmp
# End Source File
# Begin Source File

SOURCE=.\res\project.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ap2d_check.loh
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
