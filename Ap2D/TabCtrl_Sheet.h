#if !defined(AFX_TABCTRL_SHEET_H__CC9C0576_E0EA_4E5F_B50E_EDCB297D8F61__INCLUDED_)
#define AFX_TABCTRL_SHEET_H__CC9C0576_E0EA_4E5F_B50E_EDCB297D8F61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabCtrl_Sheet.h : header file
//

#define MAXPAGE 16

/////////////////////////////////////////////////////////////////////////////
// TabCtrl_Sheet window

class TabCtrl_Sheet : public CTabCtrl
{
// Construction
public:
	TabCtrl_Sheet();

// Attributes
public:

// Operations
public:
	int GetCurSel();
	int SetCurSel(int nItem);
	void Show();
	void SetRect();
	BOOL AddPage(LPCTSTR title, CDialog *pDialog, UINT ID);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TabCtrl_Sheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~TabCtrl_Sheet();

	// Generated message map functions
protected:
	LPCTSTR m_Title[MAXPAGE];
	UINT m_IDD[MAXPAGE];
	CDialog* m_pPages[MAXPAGE];
	int m_nNumOfPages;
	int m_nCurrentPage;
	//{{AFX_MSG(TabCtrl_Sheet)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABCTRL_SHEET_H__CC9C0576_E0EA_4E5F_B50E_EDCB297D8F61__INCLUDED_)
