#if !defined(AFX_DLG_REPLACE_MATERIAL_H__20598408_7C76_4245_883D_E76D15EF0F8A__INCLUDED_)
#define AFX_DLG_REPLACE_MATERIAL_H__20598408_7C76_4245_883D_E76D15EF0F8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Replace_Material.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_Replace_Material dialog

class Dlg_Replace_Material : public CDialog
{
// Construction
public:
	Dlg_Replace_Material(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dlg_Replace_Material)
	enum { IDD = IDD_DLG_REPLACE_MATERIAL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_Replace_Material)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dlg_Replace_Material)
	virtual void OnOK();
	afx_msg void OnButReplace();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_REPLACE_MATERIAL_H__20598408_7C76_4245_883D_E76D15EF0F8A__INCLUDED_)
