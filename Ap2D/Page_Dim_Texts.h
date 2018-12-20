#if !defined(AFX_PAGE_DIM_TEXTS_H__67203EA5_556C_4B03_81F7_604E1F156324__INCLUDED_)
#define AFX_PAGE_DIM_TEXTS_H__67203EA5_556C_4B03_81F7_604E1F156324__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Page_Dim_Texts.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Page_Dim_Texts dialog

class Page_Dim_Texts : public CPropertyPage
{
	DECLARE_DYNCREATE(Page_Dim_Texts)

// Construction
public:
	Page_Dim_Texts();
	~Page_Dim_Texts();

// Dialog Data
	//{{AFX_DATA(Page_Dim_Texts)
	enum { IDD = IDD_PAGE_DIM_TEXTS };
	CListCtrl	list_;
	BOOL	check_;
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(Page_Dim_Texts)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(Page_Dim_Texts)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListNames(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickListNames(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButApply();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

	void init_list();
	void init_list_lead();

public:
	void init_list_text();
	void reset_entities();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE_DIM_TEXTS_H__67203EA5_556C_4B03_81F7_604E1F156324__INCLUDED_)
