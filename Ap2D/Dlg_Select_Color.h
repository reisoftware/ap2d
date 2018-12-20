#if !defined(AFX_DLG_SELECT_COLOR_H__4C841496_EE91_4581_AC6B_4BDDA788EA44__INCLUDED_)
#define AFX_DLG_SELECT_COLOR_H__4C841496_EE91_4581_AC6B_4BDDA788EA44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Select_Color.h : header file
//
#include "Color_ComboBox.h"

/////////////////////////////////////////////////////////////////////////////
// Dlg_Select_Color dialog

class Dlg_Select_Color : public CDialog
{
// Construction
public:
	Dlg_Select_Color(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dlg_Select_Color)
	enum { IDD = IDD_DLG_SELECT_COLOR };
	Color_ComboBox	error_color_;
	Color_ComboBox	color_no2_;
	Color_ComboBox	color_;
	BOOL	check_color_;
	BOOL	include_cur_txt_;
	CString	one_postfix_;
	CString	one_prefix_;
	CString	two_postfix_;
	CString	two_prefix_;
	CString	cur_txt_val_;
	//}}AFX_DATA

	int get_color();
	int get_color_no2();
	int get_error_color();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_Select_Color)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dlg_Select_Color)
	virtual BOOL OnInitDialog();
	afx_msg void OnButSelColor();
	afx_msg void OnCheckRecord();
	afx_msg void OnCheckIncludeCurrent();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_SELECT_COLOR_H__4C841496_EE91_4581_AC6B_4BDDA788EA44__INCLUDED_)
