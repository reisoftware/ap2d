#if !defined(AFX_DLG_JISHOU_ADD_H__C67824DE_1D1A_4D1D_9B5C_49A04FAA5538__INCLUDED_)
#define AFX_DLG_JISHOU_ADD_H__C67824DE_1D1A_4D1D_9B5C_49A04FAA5538__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Jishou_add.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// Dlg_Jishou_add dialog


class Dlg_Jishou_add : public CDialog
{
// Construction
public:
	Dlg_Jishou_add(CWnd* pParent = NULL);   // standard constructor

	
	void init_dlg_data();
	//JiShou per_jishou_;
// Dialog Data
	//{{AFX_DATA(Dlg_Jishou_add)
	enum { IDD = IDD_DLG_JISHOU_ADD };
	CComboBox	combo_joint_right_;
	CComboBox	combo_joint_left_;
	CComboBox	combo_ass_no_;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_Jishou_add)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dlg_Jishou_add)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_JISHOU_ADD_H__C67824DE_1D1A_4D1D_9B5C_49A04FAA5538__INCLUDED_)
