#if !defined(AFX_DLG_LOGIN_H__63052D8E_35C3_46F7_A677_7078B01631F8__INCLUDED_)
#define AFX_DLG_LOGIN_H__63052D8E_35C3_46F7_A677_7078B01631F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Login.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_Login dialog

class Dlg_Login : public CDialog
{
// Construction
public:
	Dlg_Login(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dlg_Login)
	enum { IDD = IDD_DLG_LOGIN };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_Login)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dlg_Login)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_LOGIN_H__63052D8E_35C3_46F7_A677_7078B01631F8__INCLUDED_)
