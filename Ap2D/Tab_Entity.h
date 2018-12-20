#if !defined(AFX_TAB_ENTITY_H__FA783F0D_D378_4813_94B4_C8AA314CE31C__INCLUDED_)
#define AFX_TAB_ENTITY_H__FA783F0D_D378_4813_94B4_C8AA314CE31C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Tab_Entity.h : header file
//
#include "TabCtrl_Sheet.h"
#include "Page_Arrow.h"
#include "Page_Common.h"
#include "Page_Dim.h"
#include "Page_Radius.h"
#include "Page_Text.h"
#include "Page_Dim_Texts.h"
#include "Page_Text_Common.h"


#include "Mgr_Control.h"
#include "DB_Configure.h"

/////////////////////////////////////////////////////////////////////////////
// Tab_Entity dialog

class Tab_Entity : public CDialog

{
// Construction
public:
	Tab_Entity(CWnd* pParent = NULL);   // standard constructor
	CString get_file_path();
	void 	save_data_to_file(CString );
	void reload();
	void add_data_to_files(CStringArray &files);
	void deal_get_files_input_dlg(CStringArray& files);
// Dialog Data
	//{{AFX_DATA(Tab_Entity)
	enum { IDD = IDD_TAB_ENTITY };
	CComboBox	combo_tpl_names_;
	TabCtrl_Sheet	tab_;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Tab_Entity)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	Page_Arrow page_arrow_;		
	Page_Common page_common_;		
	Page_Dim page_dim_;		
	Page_Radius page_radius_;		
	Page_Text page_text_;		
	Page_Text_Common page_text_common_;		
	Page_Dim_Texts page_dim_texts_;		
	

	CStringArray page_show_;
	void init_sheet();

	void set_current_val();
	void change_properties();


	DB_Configure configure_db;
	// Generated message map functions
	//{{AFX_MSG(Tab_Entity)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnButOk();
	afx_msg void OnButCancel();
	afx_msg void OnButTplSave();
	afx_msg void OnButTplDel();
	afx_msg void OnButSaveAs();
	afx_msg void OnSelchangeComboTplNames();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString files_path_;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TAB_ENTITY_H__FA783F0D_D378_4813_94B4_C8AA314CE31C__INCLUDED_)
