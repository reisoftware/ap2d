#if !defined(AFX_DLG_PROJECT_MGR_H__24EC878C_895F_4484_9A0C_D700F833CDF1__INCLUDED_)
#define AFX_DLG_PROJECT_MGR_H__24EC878C_895F_4484_9A0C_D700F833CDF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Project_Mgr.h : header file
//
#include "Ex_ListCtrl_Sort.h"
/////////////////////////////////////////////////////////////////////////////
// Dlg_Project_Mgr dialog

class Dlg_Project_Mgr : public CDialog
{
// Construction
public:
	Dlg_Project_Mgr(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dlg_Project_Mgr)
	enum { IDD = IDD_DLG_PROJECT_MGR };
	ListCtrl_Sort	list_company_;
	ListCtrl_Sort	list_projects_;
	CString	project_path_;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_Project_Mgr)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	std::string cur_company_name_;
	std::string cur_project_name_;
	void init_list();
	// Generated message map functions
	//{{AFX_MSG(Dlg_Project_Mgr)
	virtual BOOL OnInitDialog();
	afx_msg void OnButOpen();
	afx_msg void OnClickListCompany(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButSave();
	afx_msg void OnButSaveProject();
	afx_msg void OnButNewCompany();
	afx_msg void OnButEditCompany();
	afx_msg void OnButDelCompany();
	afx_msg void OnButNewProject();
	afx_msg void OnButEditProject();
	afx_msg void OnButDeleteProject();
	afx_msg void OnButClose();
	afx_msg void OnButDelTreeInfo();
	afx_msg void OnClickListProject(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListProject(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButProjectPath();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_PROJECT_MGR_H__24EC878C_895F_4484_9A0C_D700F833CDF1__INCLUDED_)
