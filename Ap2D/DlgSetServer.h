#if !defined(AFX_DLGSETSERVER_H__B0DC98DC_1F7D_4570_B4C3_16196A4BAAE7__INCLUDED_)
#define AFX_DLGSETSERVER_H__B0DC98DC_1F7D_4570_B4C3_16196A4BAAE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSetServer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgSetServer dialog

class DlgSetServer : public CDialog
{
// Construction
public:
	DlgSetServer(CWnd* pParent = NULL);   // standard constructor
	CString m_ip_str;
// Dialog Data
	//{{AFX_DATA(DlgSetServer)
	enum { IDD = IDD_DLG_SERVER };
	CIPAddressCtrl	m_ip;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgSetServer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgSetServer)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETSERVER_H__B0DC98DC_1F7D_4570_B4C3_16196A4BAAE7__INCLUDED_)
