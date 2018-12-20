#if !defined(AFX_DLG_FILE_MGR_H__12AC5103_3699_472A_BD6F_3EEC0385D44B__INCLUDED_)
#define AFX_DLG_FILE_MGR_H__12AC5103_3699_472A_BD6F_3EEC0385D44B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_File_Mgr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_File_Mgr dialog

class Dlg_File_Mgr : public CDialog
{
// Construction
public:
	Dlg_File_Mgr(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dlg_File_Mgr)
	enum { IDD = IDD_DLG_FILE_MGR };
	CString	edit_copy_to_;
	CString	path_;
	CString	edit_postfix_;
	CString	delete_str_;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileManageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void change_name(CStringArray &files);
	CString get_name(CString n);
	void copy_to(CString path,CStringArray &files);
	
	HICON m_hIcon;

	void report_files(CStringArray &files) ;


	void init_radio() ;
	void load_status();
	int i_no_;
	int i_data_;
	int i_postfix_;
	int i_copy_to_;
	int i_delete_;

	// Generated message map functions
	//{{AFX_MSG(CFileManageDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButPath();
	virtual void OnOK();
	afx_msg void OnButCopyToPath();
	afx_msg void OnCheckCopyTo();
	afx_msg void OnRadioData();
	afx_msg void OnRadioPrefix();
	afx_msg void OnRadioNo();
	afx_msg void OnButDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_FILE_MGR_H__12AC5103_3699_472A_BD6F_3EEC0385D44B__INCLUDED_)
