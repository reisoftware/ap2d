#if !defined(AFX_DLG_FIND_TOOL_H__CDF6F0EB_445C_41C6_B958_E4902213BF13__INCLUDED_)
#define AFX_DLG_FIND_TOOL_H__CDF6F0EB_445C_41C6_B958_E4902213BF13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Find_Tool.h : header file
//
#include "Color_ComboBox.h"
#include "DB_Configure.h"
/////////////////////////////////////////////////////////////////////////////
// Dlg_Find_Tool dialog

class Dlg_Find_Tool : public CDialog
{
// Construction
public:


	Dlg_Find_Tool(CWnd* pParent = NULL);   // standard constructor
	void init();
	void init_combo_type();
	void set_checks(BOOL);
	void load_info();
	void deal_type(std::vector<dlhml::Entity*>,std::vector<dlhml::Entity*>&);
	void deal_text_sel(std::vector<dlhml::Entity*>,std::vector<dlhml::Entity*>&);
	void deal_line_type_sel(std::vector<dlhml::Entity*>,std::vector<dlhml::Entity*>&);
	void deal_color_sel(std::vector<dlhml::Entity*>,std::vector<dlhml::Entity*>);
	void add_data_to_files(CStringArray &files);
	void save_data_to_file(CString get_text);
	void deal_get_files_input_dlg(CStringArray& files);
	void init_show_data();

// Dialog Data
	//{{AFX_DATA(Dlg_Find_Tool)
	enum { IDD = IDD_DLG_FIND_TOOL };
	CComboBox	combo_tpl_names_;
	CComboBox	combo_type_;
	CButton	check_type_;
	Color_ComboBox	combo_color_;
	CComboBox	combo_line_;
	CButton	check_color_find_;
	CButton	check_type_line_;
	CButton	check_text_;
	CString	edit_text_;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_Find_Tool)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	//}}AFX_VIRTUAL

// Implementation
protected:
	DB_Configure configure_db;
	// Generated message map functions
	//{{AFX_MSG(Dlg_Find_Tool)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
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

#endif // !defined(AFX_DLG_FIND_TOOL_H__CDF6F0EB_445C_41C6_B958_E4902213BF13__INCLUDED_)
