#if !defined(AFX_DLG_HOT_KEY_H__C2FF6F62_379F_46B0_BC58_D35D47E573D3__INCLUDED_)
#define AFX_DLG_HOT_KEY_H__C2FF6F62_379F_46B0_BC58_D35D47E573D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Hot_Key.h : header file
//
#include "../afc/hk_fhit.h"

/////////////////////////////////////////////////////////////////////////////
// Dlg_Hot_Key dialog

class Dlg_Hot_Key : public CDialog
{
// Construction
public:
	Dlg_Hot_Key(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dlg_Hot_Key)
	enum { IDD = IDD_DLG_HOT_KEY };
	CListCtrl	list_sec_;
	CListCtrl	list_key_;
	//}}AFX_DATA

  void on_ok();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_Hot_Key)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void add_keys(std::string type_name);

	// Generated message map functions
	//{{AFX_MSG(Dlg_Hot_Key)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickListSec(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListKey(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnDefault();
	afx_msg void OnBnAdvanced();
	afx_msg void OnBnOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
  void init_sec();
  void init_sec_column();
  void init_sec_item();

  void init_key();
  void init_key_column();
  void init_key_item();
  void init_key_item(LPCTSTR sec_name);

};
namespace hkdlg{
hk::Fhit& hotkey();
}//namespace

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_HOT_KEY_H__C2FF6F62_379F_46B0_BC58_D35D47E573D3__INCLUDED_)
