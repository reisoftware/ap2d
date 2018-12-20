#if !defined(AFX_DLG_DIM_TEXTS_EDIT_H__B7F6FA12_D21E_4DF3_8E27_246DE18BF0A9__INCLUDED_)
#define AFX_DLG_DIM_TEXTS_EDIT_H__B7F6FA12_D21E_4DF3_8E27_246DE18BF0A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Dim_Texts_Edit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_Dim_Texts_Edit dialog

class Dlg_Dim_Texts_Edit : public CDialog
{
// Construction
public:
	Dlg_Dim_Texts_Edit(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dlg_Dim_Texts_Edit)
	enum { IDD = IDD_DLG_DIM_TEXTS_EDIT };
	CString	txt1_;
	CString	txt2_;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_Dim_Texts_Edit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dlg_Dim_Texts_Edit)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_DIM_TEXTS_EDIT_H__B7F6FA12_D21E_4DF3_8E27_246DE18BF0A9__INCLUDED_)
