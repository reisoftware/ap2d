#if !defined(AFX_DLG_SELECT_NAME_H__B1EA2D91_35D7_4475_8C7D_0DDB891AB7F8__INCLUDED_)
#define AFX_DLG_SELECT_NAME_H__B1EA2D91_35D7_4475_8C7D_0DDB891AB7F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Select_Name.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_Select_Name dialog

class Dlg_Select_Name : public CDialog
{
// Construction
public:
	Dlg_Select_Name(CWnd* pParent = NULL);   // standard constructor

	void set_names(const CStringArray& names);
	void deal_find_str_show(CString);
	CString get_name();
// Dialog Data
	//{{AFX_DATA(Dlg_Select_Name)
	enum { IDD = IDD_DLG_SELECT_NAME };
	CListCtrl	names_;
	CString	name_;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_Select_Name)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString str_name_;
	CStringArray names_ary_;
	// Generated message map functions
	//{{AFX_MSG(Dlg_Select_Name)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClickListNames(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEditName();
	afx_msg void OnDblclkListNames(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_SELECT_NAME_H__B1EA2D91_35D7_4475_8C7D_0DDB891AB7F8__INCLUDED_)
