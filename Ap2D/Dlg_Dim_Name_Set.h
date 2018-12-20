#if !defined(AFX_DLG_DIM_NAME_SET_H__EB0AE2D1_F0A8_467C_B8DE_1EDA89FE3B6C__INCLUDED_)
#define AFX_DLG_DIM_NAME_SET_H__EB0AE2D1_F0A8_467C_B8DE_1EDA89FE3B6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Dim_Name_Set.h : header file
//
#include<vector>
#include "DB_Configure.h"
/////////////////////////////////////////////////////////////////////////////
// Dlg_Dim_Name_Set dialog

class Dlg_Dim_Name_Set : public CDialog
{
// Construction
public:
	Dlg_Dim_Name_Set(CWnd* pParent = NULL);   // standard constructor
	
	void get_dim_styles(CStringArray &strs);
	void 	save_data_to_file(CString get_text);

// Dialog Data
	//{{AFX_DATA(Dlg_Dim_Name_Set)
	enum { IDD = IDD_DLG_DIM_NAME_SET };
	CComboBox	combo_tpl_names_;
	CListCtrl	list_signs_;
	CListCtrl	list_set_name_;
	CListCtrl	list_names_;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_Dim_Name_Set)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	std::vector<CString> names_;
	std::vector<CString> signs_;

	CStringArray select_strs_;
	void init_list_names();
	void init_list_signs();
	void init_list_set_name();
	void set_list_prop(CListCtrl &list_ctrl) ;
	
	BOOL check_have_name(CString name);
	BOOL check_have_sign(CString name);
	BOOL check_have_name_in_list(CListCtrl &list_ctrl,CString name);
	void get_listctrl_strs(CListCtrl &list_ctrl,std::vector<CString> &items) ;
	DB_Configure configure_db;

	// Generated message map functions
	//{{AFX_MSG(Dlg_Dim_Name_Set)
	afx_msg void OnButAddName();
	afx_msg void OnButSubName();
	afx_msg void OnButAddSign();
	afx_msg void OnButSubSign();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListNames(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListSigns(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickListSetInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListSetInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButTplDel();
	afx_msg void OnButTplSave();
	afx_msg void OnSelchangeComboTplNames();
	afx_msg void OnButSaveAs();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int states;
	CString files_path_;
};

CString get_file_path();


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_DIM_NAME_SET_H__EB0AE2D1_F0A8_467C_B8DE_1EDA89FE3B6C__INCLUDED_)
