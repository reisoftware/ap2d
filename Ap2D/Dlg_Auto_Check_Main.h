#if !defined(AFX_DLG_AUTO_CHECK_MAIN_H__51820E54_6FC8_4D97_8FC9_10156CD66A2C__INCLUDED_)
#define AFX_DLG_AUTO_CHECK_MAIN_H__51820E54_6FC8_4D97_8FC9_10156CD66A2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Auto_Check_Main.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_Auto_Check_Main dialog

class Dlg_Auto_Check_Main : public CDialog
{
// Construction
public:
	Dlg_Auto_Check_Main(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dlg_Auto_Check_Main)
	enum { IDD = IDD_DLG_AUTO_CHECK };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_Auto_Check_Main)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dlg_Auto_Check_Main)
	afx_msg void OnButJishouStandart();
	afx_msg void OnButJishouStandart3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_AUTO_CHECK_MAIN_H__51820E54_6FC8_4D97_8FC9_10156CD66A2C__INCLUDED_)
