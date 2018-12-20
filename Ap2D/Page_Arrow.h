#if !defined(AFX_PAGE_ARROW_H__AC45F1C8_3D3C_4F31_B5AC_D3CB23C0027B__INCLUDED_)
#define AFX_PAGE_ARROW_H__AC45F1C8_3D3C_4F31_B5AC_D3CB23C0027B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Page_Arrow.h : header file
//
#include "Mgr_Dxfs.h"

/////////////////////////////////////////////////////////////////////////////
// Page_Arrow dialog

class Page_Arrow : public CPropertyPage
{
	DECLARE_DYNCREATE(Page_Arrow)

// Construction
public:
	Page_Arrow();
	~Page_Arrow();

	void set_ents(Entitys &ents){ents_ = ents;}
	void Updata();

// Dialog Data
	//{{AFX_DATA(Page_Arrow)
	enum { IDD = IDD_PAGE_ARROW };
	CComboBox	arrow_num_;
	CButton	check_arrow_num_;
	CButton	check_arrow_pos_;
	CButton	check_arrow_level_;
	CButton	check_arrow_kind_;
	CComboBox	arrow_style_;
	CComboBox	arrow_pos_;
	double	arrow_level_;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(Page_Arrow)
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
	//{{AFX_MSG(Page_Arrow)
	virtual BOOL OnInitDialog();
	afx_msg void OnButApply();
	afx_msg void OnButCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE_ARROW_H__AC45F1C8_3D3C_4F31_B5AC_D3CB23C0027B__INCLUDED_)
