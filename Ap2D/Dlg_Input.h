#if !defined(AFX_DLG_INPUT_H__6F057B7D_F414_429F_A1F7_549FAAA6053C__INCLUDED_)
#define AFX_DLG_INPUT_H__6F057B7D_F414_429F_A1F7_549FAAA6053C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Input.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_Input dialog

class Dlg_Input : public CDialog
{

// Construction
public:
	Dlg_Input(CWnd* pParent = NULL);   // standard constructor

	std::string val_;
// Dialog Data
	//{{AFX_DATA(Dlg_Input)
	enum { IDD = IDD_DLG_INPUT };
	CString	str_;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_Input)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dlg_Input)
	afx_msg void OnButSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_INPUT_H__6F057B7D_F414_429F_A1F7_549FAAA6053C__INCLUDED_)
