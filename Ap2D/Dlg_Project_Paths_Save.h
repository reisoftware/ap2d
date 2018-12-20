#if !defined(AFX_DLG_PROJECT_PATHS_SAVE_H__319C9800_FC06_4E95_97E3_7682F0BD1957__INCLUDED_)
#define AFX_DLG_PROJECT_PATHS_SAVE_H__319C9800_FC06_4E95_97E3_7682F0BD1957__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Project_Paths_Save.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_Project_Paths_Save dialog

class Dlg_Project_Paths_Save : public CDialog
{
// Construction
public:
	Dlg_Project_Paths_Save(CWnd* pParent = NULL);   // standard constructor
	CString get_dir();
	void init_list_style();
	void get_file_Data_show();
	void show_data();
	BOOL is_have_same(CString);
	void save_to_file();
// Dialog Data
	//{{AFX_DATA(Dlg_Project_Paths_Save)
	enum { IDD = IDD_DLG_PRO_PATHS_SAVE };
	CListCtrl	list_save_paths_;
	CString	edit_path_;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_Project_Paths_Save)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dlg_Project_Paths_Save)
	afx_msg void OnDblclkListProPahtsSave(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickListProPahtsSave(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonOpenPath();
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString cur_sel_path_;
	CString save_data_ifo_file_name_;
	CStringArray paths_;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_PROJECT_PATHS_SAVE_H__319C9800_FC06_4E95_97E3_7682F0BD1957__INCLUDED_)
