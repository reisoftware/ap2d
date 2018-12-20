#if !defined(AFX_PAGE_TEXT_COMMON_H__8C2AAFE0_C746_4499_BB5D_9CD2F64D4E93__INCLUDED_)
#define AFX_PAGE_TEXT_COMMON_H__8C2AAFE0_C746_4499_BB5D_9CD2F64D4E93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Page_Text_Common.h : header file
//
#include "Mgr_Dxfs.h"
#include "Color_ComboBox.h"

/////////////////////////////////////////////////////////////////////////////
// Page_Text_Common dialog

class Page_Text_Common : public CPropertyPage
{
	DECLARE_DYNCREATE(Page_Text_Common)

// Construction
public:
	Page_Text_Common();
	~Page_Text_Common();

	void set_ents(Entitys &ents){ents_ = ents;}
	void Updata();
// Dialog Data
	//{{AFX_DATA(Page_Text_Common)
	enum { IDD = IDD_PAGE_TEXT_COMMON };
	CButton	check_width_factor_;
	CButton	check_text_hight_;
	CButton	check_text_color_;
	CButton	check_text_angle_;
	CButton	check_text_;
	CButton	check_precision_;
	CButton	check_font_style_;
	CButton	check_arrow_pos_;
	CComboBox	font_style_;
	CComboBox	text_pos_;
	Color_ComboBox	text_color_;
	CString	content_;
	double	precision_;
	double	height_;
	double	angle_;
	double	width_factor_;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(Page_Text_Common)
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
	//{{AFX_MSG(Page_Text_Common)
	afx_msg void OnButApply();
	virtual BOOL OnInitDialog();
	afx_msg void OnButCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE_TEXT_COMMON_H__8C2AAFE0_C746_4499_BB5D_9CD2F64D4E93__INCLUDED_)
