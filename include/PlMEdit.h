#if !defined(AFX_PLMEDIT_H__B8FAE05E_777F_4F40_B8C1_F846390157CC__INCLUDED_)
#define AFX_PLMEDIT_H__B8FAE05E_777F_4F40_B8C1_F846390157CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlMEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPlMEdit dialog
#include "resource.h"
class CGePlate;
class CPlMEdit : public CDialog
{
// Construction
public:
	CPlMEdit(CWnd* pParent = NULL);   // standard constructor
	
	CGePlate* lpPL;
// Dialog Data
	//{{AFX_DATA(CPlMEdit)
	enum { IDD = IDD_PLMEDIT };
	float	m_x;
	float	m_y;
	float	m_z;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlMEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPlMEdit)
	afx_msg void OnButrotate();
	afx_msg void OnButmove();
	afx_msg void OnButxy();
	afx_msg void OnButxz();
	afx_msg void OnButyz();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLMEDIT_H__B8FAE05E_777F_4F40_B8C1_F846390157CC__INCLUDED_)
