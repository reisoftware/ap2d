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
	CButton	check_show_right_menu_;
	double	reduce_scale_;
	double	reduce_scale_export_;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_Setting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dlg_Setting)
	afx_msg void OnCheckRightMenuShow();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_SETTING_H__B530B52D_CE66_4F11_8CCF_42BDFAE3FBAF__INCLUDED_)
