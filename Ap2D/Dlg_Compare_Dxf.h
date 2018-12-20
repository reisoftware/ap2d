#if !defined(AFX_DLG_COMPARE_DXF_H__6FC456F1_3AF8_4E98_9E33_724EEF1F71D4__INCLUDED_)
#define AFX_DLG_COMPARE_DXF_H__6FC456F1_3AF8_4E98_9E33_724EEF1F71D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Compare_Dxf.h : header file
//
#include "Color_ComboBox.h"
#include "Mgr_Dxfs.h"

/////////////////////////////////////////////////////////////////////////////
// Dlg_Compare_Dxf dialog

class Dlg_Compare_Dxf : public CDialog
{
	
// Construction
public:
	Dlg_Compare_Dxf(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dlg_Compare_Dxf)
	enum { IDD = IDD_DLG_COMPARE };
	CButton	check_file_1_color_;
	CButton	check_file_0_color_;
	Color_ComboBox	color_file_1_;
	Color_ComboBox	color_file_0_;
	Color_ComboBox	color_;
	CString	file_0_;
	CString	file_1_;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_Compare_Dxf)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL change_color_;
	int ent_count_;
	Entitys old_ents_;

	int color_0_;
	int color_1_;
	// Generated message map functions
	//{{AFX_MSG(Dlg_Compare_Dxf)
	afx_msg void OnRadioChangeColor();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioNoChange();
	virtual void OnOK();
	afx_msg void OnButFile0();
	afx_msg void OnButFile1();
	afx_msg void OnButOpen();
	afx_msg void OnCheckFile0Color();
	afx_msg void OnCheckFile1Color();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_COMPARE_DXF_H__6FC456F1_3AF8_4E98_9E33_724EEF1F71D4__INCLUDED_)
