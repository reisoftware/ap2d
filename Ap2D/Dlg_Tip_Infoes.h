#if !defined(AFX_DLG_TIP_INFOES_H__7F3AFAAD_1DF8_4A01_A659_57D296BF6257__INCLUDED_)
#define AFX_DLG_TIP_INFOES_H__7F3AFAAD_1DF8_4A01_A659_57D296BF6257__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Tip_Infoes.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_Tip_Infoes dialog

class Dlg_Tip_Infoes : public CDialog
{
// Construction
public:
	Dlg_Tip_Infoes(CWnd* pParent = NULL);   // standard constructor
	CString get_files_path();
	void init();
	void init_db();
	void init_dlg_show();
	void init_dlg_type();
	void save_db();
	CString get_str();
// Dialog Data
	//{{AFX_DATA(Dlg_Tip_Infoes)
	enum { IDD = IDD_DLG_TIP_INFO };
	CListCtrl	list_tip_datas_;
	CEdit	edit_tip_;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_Tip_Infoes)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dlg_Tip_Infoes)
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonDel();
	afx_msg void OnClickListTips(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListTips(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString file_path_;
	CStringArray tips_db_;
	CString cur_txt_;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_TIP_INFOES_H__7F3AFAAD_1DF8_4A01_A659_57D296BF6257__INCLUDED_)
