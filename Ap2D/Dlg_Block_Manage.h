#if !defined(AFX_DLG_BLOCK_MANAGE_H__058C7D1E_34DC_45BD_A006_7D61C0C45A25__INCLUDED_)
#define AFX_DLG_BLOCK_MANAGE_H__058C7D1E_34DC_45BD_A006_7D61C0C45A25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Block_Manage.h : header file
//
#include "Database.h"

/////////////////////////////////////////////////////////////////////////////
// Dlg_Block_Manage dialog

class Dlg_Block_Manage : public CDialog
{
// Construction
public:
	Dlg_Block_Manage(CWnd* pParent = NULL);   // standard constructor

	void get_ents(std::vector<dlhml::Entity*> &ents) ;
// Dialog Data
	//{{AFX_DATA(Dlg_Block_Manage)
	enum { IDD = IDD_DLG_BLOCK_MANAGE };
	CListCtrl	list_;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_Block_Manage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	std::vector<dlhml::Entity*> ents_;

	// Generated message map functions
	//{{AFX_MSG(Dlg_Block_Manage)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDblclkListBlockNames(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_BLOCK_MANAGE_H__058C7D1E_34DC_45BD_A006_7D61C0C45A25__INCLUDED_)
