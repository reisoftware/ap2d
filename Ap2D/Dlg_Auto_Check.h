#if !defined(AFX_DLG_AUTO_CHECK_H__4C7A28AD_03B0_4DDA_9CD5_4E3768DEC145__INCLUDED_)
#define AFX_DLG_AUTO_CHECK_H__4C7A28AD_03B0_4DDA_9CD5_4E3768DEC145__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Auto_Check.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// Dlg_Auto_Check dialog



class Dlg_Auto_Check : public CDialog
{
// Construction
public:
	Dlg_Auto_Check(CWnd* pParent = NULL);   // standard constructor
	void init_dlg_type();
	void 	update_data();
	void init_data();

// Dialog Data
	//{{AFX_DATA(Dlg_Auto_Check)
	enum { IDD = IDD_DLG_JISHOU_CHECK };
	CListCtrl	list_add_data_;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_Auto_Check)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dlg_Auto_Check)
	afx_msg void OnButAdd();
	virtual BOOL OnInitDialog();
	afx_msg void OnEdit();
	afx_msg void OnDelete();
	virtual void OnCancel();
	afx_msg void OnClickListData(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_AUTO_CHECK_H__4C7A28AD_03B0_4DDA_9CD5_4E3768DEC145__INCLUDED_)
