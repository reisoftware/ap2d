// Toolbar_Combo.h: interface for the Toolbar_Combo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOOLBAR_COMBO_H__710D89C1_B92A_467E_8043_B87A3C3804CE__INCLUDED_)
#define AFX_TOOLBAR_COMBO_H__710D89C1_B92A_467E_8043_B87A3C3804CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Toolbar_Combo : public CToolBar   
{
public:
	Toolbar_Combo();
	virtual ~Toolbar_Combo();

public:
	CComboBox combo_;
	CButton *but_;
	CEdit edit_;
protected:

	// Generated message map functions
	//{{AFX_MSG(CC_testDlg)
	afx_msg void OnSelchangeCombo1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#endif // !defined(AFX_TOOLBAR_COMBO_H__710D89C1_B92A_467E_8043_B87A3C3804CE__INCLUDED_)
