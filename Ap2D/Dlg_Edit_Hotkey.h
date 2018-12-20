#if !defined(AFX_DLG_EDIT_HOTKEY_H__4AD61E52_CD14_46C3_9B67_8F39514395F8__INCLUDED_)
#define AFX_DLG_EDIT_HOTKEY_H__4AD61E52_CD14_46C3_9B67_8F39514395F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Edit_Hotkey.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_Edit_Hotkey dialog

class Dlg_Edit_Hotkey : public CDialog
{
// Construction
public:
	Dlg_Edit_Hotkey(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dlg_Edit_Hotkey)
	enum { IDD = IDD_DLG_EDIT_HOTKEY };
	int		cbk_;
	CString	hit_;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_Edit_Hotkey)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dlg_Edit_Hotkey)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
  void set(LPCTSTR kcmd, LPCTSTR kval);
  std::string kcmd()const;
  std::string kval()const;

private:
  std::string kcmd_;
  std::string kval_;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_EDIT_HOTKEY_H__4AD61E52_CD14_46C3_9B67_8F39514395F8__INCLUDED_)
