#if !defined(AFX_PAGE_RADIUS_H__C9BD6FBD_3138_4EF9_8E2D_F96E6D473DF7__INCLUDED_)
#define AFX_PAGE_RADIUS_H__C9BD6FBD_3138_4EF9_8E2D_F96E6D473DF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Page_Radius.h : header file
//
#include "Mgr_Dxfs.h"

/////////////////////////////////////////////////////////////////////////////
// Page_Radius dialog

class Page_Radius : public CPropertyPage
{
	DECLARE_DYNCREATE(Page_Radius)

// Construction
public:
	Page_Radius();
	~Page_Radius();

	void set_ents(Entitys &ents){ents_ = ents;}
	void Updata();

// Dialog Data
	//{{AFX_DATA(Page_Radius)
	enum { IDD = IDD_PAGE_RADIUS };
	CButton	check_radius_;
	double	radius_;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(Page_Radius)
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
	//{{AFX_MSG(Page_Radius)
	virtual BOOL OnInitDialog();
	afx_msg void OnButApply();
	afx_msg void OnButCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE_RADIUS_H__C9BD6FBD_3138_4EF9_8E2D_F96E6D473DF7__INCLUDED_)
