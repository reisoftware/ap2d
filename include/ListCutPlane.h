#if !defined(AFX_LISTCUTPLANE_H__A01EE3C7_93AD_4B0C_84CE_F05F06E4729A__INCLUDED_)
#define AFX_LISTCUTPLANE_H__A01EE3C7_93AD_4B0C_84CE_F05F06E4729A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListCutPlane.h : header file
//
#include "resource.h"
#include <map>
#include "Model_Geographic.h"
/////////////////////////////////////////////////////////////////////////////
// ListCutPlane dialog

class ListCutPlaneDlg : public CDialog
{
// Construction
	typedef std::map<std::string,gelib::Model_Geographic> GEOS;
public:
  BOOL is_del() const;
public:
	ListCutPlaneDlg(CWnd* pParent = NULL);   // standard constructor
	GEOS* geos_;
	
	// Dialog Data
	//{{AFX_DATA(ListCutPlane)
	enum { IDD = IDD_CUTLISTDLG };
	CComboBox	m_list;
	CString	m_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ListCutPlane)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ListCutPlane)
	virtual BOOL OnInitDialog();
	afx_msg void OnButdel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void init_comb();
	BOOL del_;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCUTPLANE_H__A01EE3C7_93AD_4B0C_84CE_F05F06E4729A__INCLUDED_)
