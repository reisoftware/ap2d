#if !defined(AFX_DLG_SIGN_REPLACE_H__418B1AC8_2689_4A71_8030_BA5DCFDDE8CB__INCLUDED_)
#define AFX_DLG_SIGN_REPLACE_H__418B1AC8_2689_4A71_8030_BA5DCFDDE8CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Sign_Replace.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_Sign_Replace dialog

class Dlg_Sign_Replace : public CDialog
{
// Construction
public:
	Dlg_Sign_Replace(CWnd* pParent = NULL);   // standard constructor
	void set_DropDownSize(CComboBox& box, UINT LinesToDisplay);
	void 	init_combo_data();
	void init_combo_text();
	void init_list();
	void	save_data();
	void update_db();
// Dialog Data
	//{{AFX_DATA(Dlg_Sign_Replace)
	enum { IDD = IDD_DLG_SIGN_REPLACE };
	CComboBox	combo_text_;
	CListCtrl	list_signs_;
	CComboBox	combo_signs_;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_Sign_Replace)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dlg_Sign_Replace)
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonEdit();
	afx_msg void OnButtonDel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButReplace();
	afx_msg void OnClickListSigns(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButSavePath();
	afx_msg void OnButLoadPath();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString file_all_path;
};
//CString get_file_path();

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_SIGN_REPLACE_H__418B1AC8_2689_4A71_8030_BA5DCFDDE8CB__INCLUDED_)
