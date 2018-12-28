#if !defined(AFX_DLG_SETTING_H__B530B52D_CE66_4F11_8CCF_42BDFAE3FBAF__INCLUDED_)
#define AFX_DLG_SETTING_H__B530B52D_CE66_4F11_8CCF_42BDFAE3FBAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Setting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_Setting dialog

class Dlg_Setting : public CDialog
{

// Construction
public:
	Dlg_Setting(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dlg_Setting)
	enum { IDD = IDD_DLG_SETTING };
	CListCtrl	m_lsit_font_db;
	CButton	check_show_right_menu_;
	double	reduce_scale_;
	double	reduce_scale_export_;
	CString	m_height_;
	CString	m_width_factor_;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_Setting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void set_list_prop(CListCtrl &list_ctrl); 
	void init_list_font_db();

	// Generated message map functions
	//{{AFX_MSG(Dlg_Setting)
	afx_msg void OnCheckRightMenuShow();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButAdd();
	afx_msg void OnButEdit();
	afx_msg void OnButDel();
	afx_msg void OnClickListWidthFactor(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_SETTING_H__B530B52D_CE66_4F11_8CCF_42BDFAE3FBAF__INCLUDED_)
