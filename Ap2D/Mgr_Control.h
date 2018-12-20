// Mgr_Control.h: interface for the Mgr_Control class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MGR_CONTROL_H__423E0E5A_45E1_47CD_B64A_F337332CC31E__INCLUDED_)
#define AFX_MGR_CONTROL_H__423E0E5A_45E1_47CD_B64A_F337332CC31E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//hotkey type
const CString SECTION_FILE = "File";
const CString SECTION_SETTING = "Setting";
const CString SECTION_EDIT = "Edit";
const CString SECTION_DRAWING = "Drawing";
const CString SECTION_MODIFY = "Modify";
const CString SECTION_DEAL_STEEL = "DealSteel";
const CString SECTION_FILRATE = "Filrate";
const CString SECTION_JOINT = "DrawJoint";
const CString SECTION_SNAP = "Snap";
const CString SECTION_LOCK_LAYER = "LockLayer";


//create file toolbar
const CString CMD_F_NEW_PROJECT = "NewProject";
const CString CMD_F_OPEN_PROJECT = "OpenProject";
const CString CMD_F_NEW_VIEW = "NewView";
const CString CMD_F_SAVE_PROJECT = "SaveProject";
const CString CMD_F_OPEN_PROJECT_PATH = "OpenProjectPath";
const CString CMD_F_SET_AXIS = "SetAxis";
const CString CMD_F_Show3D = "Show3D";
const CString CMD_F_Section_DB = "Section_DB";
const CString CMD_F_ProjectSet = "ProjectSet";
const CString CMD_F_Setting = "Setting";
const CString CMD_F_SetKey = "SetHotKey";
const CString CMD_F_CreateTable = "CreateTable";

class Mgr_Control  
{
public:
	Mgr_Control();
	virtual ~Mgr_Control();

};
void set_combo_txt(CComboBox &combo,CString str);
void set_combo_color(CComboBox &combo,int color_index);


void set_combo_line_type(CComboBox &combo);
void set_combo_arrow_pos(CComboBox &combo);
void set_combo_arrow_style(CComboBox &combo);
void set_combo_dim_kind(CComboBox &combo);
void set_combo_text_pos(CComboBox &combo);
void set_combo_frame_kind(CComboBox &combo);
void set_combo_arrow_num(CComboBox &combo);

#endif // !defined(AFX_MGR_CONTROL_H__423E0E5A_45E1_47CD_B64A_F337332CC31E__INCLUDED_)
