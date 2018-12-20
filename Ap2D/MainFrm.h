// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__834C2BEE_D62E_4CB9_BEDB_F072C31C2F3E__INCLUDED_)
#define AFX_MAINFRM_H__834C2BEE_D62E_4CB9_BEDB_F072C31C2F3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "View.h"
#include "Left_Mgr.h"
#include "Dlg_Project_Paths_Save.h"
#include "PutBar.h"
#include "TrueColorToolBar.h"
#include "Toolbar_Combo.h"
#include "Mgr_Database.h"

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:
	bool is_open(View *v);
	void set_cur_view(std::string name);
	
	void create_left();
	CPutBar* command_line_bar(){return &put_bar_;}
	CEdit* in();
	CEdit* out();

	CToolBar& get_wnd_bar(){return m_wndToolBar;}
	CToolBar& get_snap_bar(){return snap_toolbar_;}
	CToolBar& get_create_bar(){return entity_toolbar_;}
	CToolBar& get_edit_bar(){return edit_toolBar_;}

	CToolBar& get_layer_bar(){return layer_toolBar_;}

	Toolbar_Combo& get_combo_layer_bar(){return combo_toolbar_;}

	void import_dxf();

	void set_status_str(std::string info);

	void set_status_num(int num);
	void load_tree(std::string pro_name,std::string company_name);


	void open_dir_create_tree();

	void load_layers();

	std::string get_layer_name();
	void set_combo_toolbar(int id,bool status);

	void show_list_report(Group_Txts &group_txts);
	void show_same_list_report(Group_Txts &group_txts);
	CString get_path_dlg();
// Operations
  static void init_hotkey();

public:
	void close_global();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:  // control bar embedded members
	void init_put_bar();
protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CTrueColorToolBar    m_wndToolBar;

	CTrueColorToolBar    edit_toolBar_;
	CTrueColorToolBar    snap_toolbar_;
	CTrueColorToolBar    entity_toolbar_;
	CTrueColorToolBar    layer_toolBar_;
	CTrueColorToolBar    right_toolbar_;

	Toolbar_Combo combo_toolbar_;


	void init_eidt_bar();
	void init_snap_bar();
	void init_entity_bar();
	void init_layer_bar();
	void init_right_toolbar();

	void init_combo_toolbar();

	Left_Mgr *left_mgr_;
	CPutBar		put_bar_;

	void DockControlBarLeftOf(CToolBar *Bar,CToolBar *LeftOf)  ;

	bool hotkey(MSG* pMsg);

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnButSetup();
	afx_msg void OnButOpenProjectPath();
	afx_msg void OnButNewView();
	afx_msg void OnButLogin();
	afx_msg void OnButOpenProject();
	afx_msg void OnButInputDxfs();
	afx_msg void OnButLoadLayer();
	afx_msg void OnButCreateTable();
	afx_msg void OnButSaveServer();
	afx_msg void OnButOpenServer();
	afx_msg void OnEditchangeCombo_Tool();
	afx_msg void OnMenuOpenProject();
	afx_msg void OnMenuCreateProject();
	afx_msg void OnMenuCloseProject();
	afx_msg void OnMenuAddView();
	afx_msg void OnMenuDeleteView();
	afx_msg void OnMenuEditView();
	afx_msg void OnButHotKey();
	afx_msg void OnButHotKeyP();
	afx_msg void OnButInLua();
	afx_msg void OnButOutLua();
	afx_msg void OnButInLuaP();
	afx_msg void OnButOutLuaP();
	afx_msg void OnButCompareXsteel();
	afx_msg void OnButCompareXsteelP();
	afx_msg void OnButFileMamage();
	afx_msg void OnBUTFILEMAMAGEp();
	afx_msg void OnMenuOpenProjectCheck();
	afx_msg void OnMenuCreateProjectCheck();
	afx_msg void OnMenuCloseProjectCheck();
	afx_msg void OnMenuSetComplateCheck();
	afx_msg void OnMenuSetComplateCheckP();
	afx_msg void OnMenuUpdate();
	afx_msg void OnMenuCreateDxf();
	afx_msg void OnMenuSave();
	afx_msg void OnMenuSetErrorCheckP();
	afx_msg void OnMenuClearStatus();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__834C2BEE_D62E_4CB9_BEDB_F072C31C2F3E__INCLUDED_)
