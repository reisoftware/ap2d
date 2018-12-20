#if !defined(AFX_DLG_SELECT_TABLE_TEXT_H__0EEF8045_6708_4975_B208_5215EAF81EA9__INCLUDED_)
#define AFX_DLG_SELECT_TABLE_TEXT_H__0EEF8045_6708_4975_B208_5215EAF81EA9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Select_Table_Text.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_Select_Table_Text dialog
#include "Mgr_Entity.h"

class Dlg_Select_Table_Text : public CDialog
{
// Construction
public:
	Dlg_Select_Table_Text(CWnd* pParent = NULL);   // standard constructor
	void set_sel_ifo(std::vector<dlhml::Entity*>,std::vector<dlhml::Entity*>,Dlg_Select_Table_Text*);
	void init_matrix_ifo();
	void init_matrix_type();
// Dialog Data
	//{{AFX_DATA(Dlg_Select_Table_Text)
	enum { IDD = IDD_DLG_SELECT_TABLE_TEXT };
	CListCtrl	LIST_NUMBERS_;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_Select_Table_Text)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dlg_Select_Table_Text)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListNumbers(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonRecovery();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	std::vector<dlhml::Entity*> cur_sel_;
	std::vector<dlhml::Entity*> all_ents_;
	Dlg_Select_Table_Text* dlg_tab_txt_;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_SELECT_TABLE_TEXT_H__0EEF8045_6708_4975_B208_5215EAF81EA9__INCLUDED_)
