#if !defined(AFX_DLG_LAYER_DB_H__5F92B7E5_8B19_4AA4_BD24_7813BE2D4D2F__INCLUDED_)
#define AFX_DLG_LAYER_DB_H__5F92B7E5_8B19_4AA4_BD24_7813BE2D4D2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Layer_DB.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_Layer_DB dialog

class Dlg_Layer_DB : public CDialog
{
// Construction
public:
	Dlg_Layer_DB(CWnd* pParent = NULL);   // standard constructor

	void get_select_layers(strings &layers);
// Dialog Data
	//{{AFX_DATA(Dlg_Layer_DB)
	enum { IDD = IDD_DLG_LAYER_DB };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_Layer_DB)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void init_select();
	// Generated message map functions
	//{{AFX_MSG(Dlg_Layer_DB)
	afx_msg void OnButDownLoad();
	afx_msg void OnButSetup();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_LAYER_DB_H__5F92B7E5_8B19_4AA4_BD24_7813BE2D4D2F__INCLUDED_)
