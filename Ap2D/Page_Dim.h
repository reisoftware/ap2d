#if !defined(AFX_PAGE_DIM_H__3E4CE3E1_A06C_4345_A063_1935167AAA40__INCLUDED_)
#define AFX_PAGE_DIM_H__3E4CE3E1_A06C_4345_A063_1935167AAA40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Page_Dim.h : header file
//
#include "Mgr_Dxfs.h"

/////////////////////////////////////////////////////////////////////////////
// Page_Dim dialog

class Page_Dim : public CPropertyPage

{
	DECLARE_DYNCREATE(Page_Dim)

// Construction
public:
	Page_Dim();
	~Page_Dim();

	void set_ents(Entitys &ents){ents_ = ents;}
	void Updata();
// Dialog Data
	//{{AFX_DATA(Page_Dim)
	enum { IDD = IDD_PAGE_DIM };
	CButton	check_start_offset_;
	CButton	check_start_dim_len_;
	CButton	check_end_offset_;
	CButton	check_end_dim_len_;
	CButton	check_dim_kind_;
	CComboBox	dim_kind_;
	double	end_dim_len_;
	double	end_offset_;
	double	start_dim_len_;
	double	start_offset_;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(Page_Dim)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	Entitys ents_;
	void init();
	void load_info();
	void set_checks(BOOL check);
	BOOL select_all_;
	void set_current_val();
	void change_properties();
	// Generated message map functions
	//{{AFX_MSG(Page_Dim)
	virtual BOOL OnInitDialog();
	afx_msg void OnButCheck();
	afx_msg void OnButApply();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE_DIM_H__3E4CE3E1_A06C_4345_A063_1935167AAA40__INCLUDED_)
