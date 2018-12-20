#if !defined(AFX_PAGE_TEXT_H__36D5E3C5_98DC_4123_B5A5_9F8462C3FA8C__INCLUDED_)
#define AFX_PAGE_TEXT_H__36D5E3C5_98DC_4123_B5A5_9F8462C3FA8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Page_Text.h : header file
//
#include "Mgr_Dxfs.h"
#include "Color_ComboBox.h"

/////////////////////////////////////////////////////////////////////////////
// Page_Text dialog

class Page_Text : public CPropertyPage
{
	DECLARE_DYNCREATE(Page_Text)

// Construction
public:
	Page_Text();
	~Page_Text();

	void set_ents(Entitys &ents){ents_ = ents;}
	void Updata();
// Dialog Data
	//{{AFX_DATA(Page_Text)
	enum { IDD = IDD_PAGE_TEXT };
	CButton	check_precision_;
	CComboBox	frame_out_;
	CButton	check_text_height_;
	CButton	check_text_color_;
	CButton	check_text_angle_;
	CButton	check_text_;
	CButton	check_out_frame_;
	CButton	check_frame_kind_;
	CButton	check_frame_color_;
	CButton	check_arrow_pos_;
	CComboBox	text_pos_;
	CComboBox	frame_kind_;
	Color_ComboBox	frame_color_;
	Color_ComboBox	text_color_;
	double	angle_;
	double	height_;
	CString	content_;
	double		precision_;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(Page_Text)
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
	//{{AFX_MSG(Page_Text)
	virtual BOOL OnInitDialog();
	afx_msg void OnButApply();
	afx_msg void OnButCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE_TEXT_H__36D5E3C5_98DC_4123_B5A5_9F8462C3FA8C__INCLUDED_)
