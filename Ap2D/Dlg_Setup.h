#if !defined(AFX_DLG_SETUP_H__3C958E1F_DD3D_42A0_97DC_33E44F241C21__INCLUDED_)
#define AFX_DLG_SETUP_H__3C958E1F_DD3D_42A0_97DC_33E44F241C21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Setup.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_Setup dialog

class Dlg_Setup : public CDialog
{
// Construction
public:
	Dlg_Setup(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dlg_Setup)
	enum { IDD = IDD_DLG_SETUP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_Setup)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dlg_Setup)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_SETUP_H__3C958E1F_DD3D_42A0_97DC_33E44F241C21__INCLUDED_)
