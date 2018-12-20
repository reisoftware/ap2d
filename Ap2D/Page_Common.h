#if !defined(AFX_PAGE_COMMON_H__61AB3E45_C0F9_4C70_BA14_ED7E42F47918__INCLUDED_)
#define AFX_PAGE_COMMON_H__61AB3E45_C0F9_4C70_BA14_ED7E42F47918__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Page_Common.h : header file
//
#include "Mgr_Dxfs.h"
#include "Color_ComboBox.h"
/////////////////////////////////////////////////////////////////////////////
// Page_Common dialog

class Page_Common : public CPropertyPage
{
	DECLARE_DYNCREATE(Page_Common)

// Construction
public:
	Page_Common();
	~Page_Common();


	void set_ents(Entitys &ents){ents_ = ents;}
	void Updata();
// Dialog Data
	//{{AFX_DATA(Page_Common)
	enum { IDD = IDD_PAGE_COMMON };
	CButton	check_line_color_;
	CButton	check_line_type_;
	CComboBox	line_type_;
	Color_ComboBox	color_;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(Page_Common)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	Entitys ents_;
	void init();
	void load_info();
	BOOL select_all_;
	void set_checks(BOOL check);

	void set_current_val();
	void change_properties();
	// Generated message map functions
	//{{AFX_MSG(Page_Common)
	virtual BOOL OnInitDialog();
	afx_msg void OnButApply();
	afx_msg void OnButCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE_COMMON_H__61AB3E45_C0F9_4C70_BA14_ED7E42F47918__INCLUDED_)
