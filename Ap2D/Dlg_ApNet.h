#if !defined(AFX_DLG_APNET_H__7B9F813D_09C2_46E0_8394_27FB93EE4D31__INCLUDED_)
#define AFX_DLG_APNET_H__7B9F813D_09C2_46E0_8394_27FB93EE4D31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_ApNet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_ApNet dialog

class Dlg_ApNet : public CDialog
{
// Construction
public:
	Dlg_ApNet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dlg_ApNet)
	enum { IDD = IDD_DLG_APNET };
	CString	user_;
	CString	password_;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_ApNet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dlg_ApNet)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_APNET_H__7B9F813D_09C2_46E0_8394_27FB93EE4D31__INCLUDED_)
