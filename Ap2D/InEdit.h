#if !defined(AFX_INEDIT_H__7E629D0D_EBB4_42C9_9177_351A068EFB5B__INCLUDED_)
#define AFX_INEDIT_H__7E629D0D_EBB4_42C9_9177_351A068EFB5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InEdit.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// InEdit window

class InEdit : public CEdit
{
// Construction
public:
	InEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(InEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~InEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(InEdit)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INEDIT_H__7E629D0D_EBB4_42C9_9177_351A068EFB5B__INCLUDED_)
