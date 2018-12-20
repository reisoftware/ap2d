#if !defined(AFX_DLG_JOINT_DB_EDIT_H__2EA0FE9D_27EF_4D7E_96F5_497456C8C313__INCLUDED_)
#define AFX_DLG_JOINT_DB_EDIT_H__2EA0FE9D_27EF_4D7E_96F5_497456C8C313__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Joint_DB_Edit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_Joint_DB_Edit dialog

class PICFILE
{
public:
	PICFILE(){}
	virtual ~PICFILE(){;}
	CString name_;
	CString path_;
};
typedef std::vector<PICFILE> PICFILES;


class Dlg_Joint_DB_Edit : public CDialog
{
// Construction
public:
	Dlg_Joint_DB_Edit(CWnd* pParent = NULL);   // standard constructor
	virtual ~Dlg_Joint_DB_Edit(){;};
	void show_image(CString strFile);
	void Determine_is_have(CString DlgStr,CString DlgPath);
	CString get_files_path();
	void init_db();
	void save_pic_ifo();
	void init_show_dlg();
	void edit_btn(int,CString,CString);
	static PICFILES* instance();
	void set_sel_name(CString);
	void init_sel();
	
// Dialog Data
	//{{AFX_DATA(Dlg_Joint_DB_Edit)
	enum { IDD = IDD_DLG_JOINT_EDIT_DB };
	CEdit	edit_path_;
	CComboBox	combo_names_;
	CStatic	static_pics_;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_Joint_DB_Edit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	

	// Generated message map functions
	//{{AFX_MSG(Dlg_Joint_DB_Edit)
	afx_msg void OnButtonOpenPath();
	virtual BOOL OnInitDialog();
	afx_msg void OnButAdd();
	afx_msg void OnButEdit();
	afx_msg void OnButDel();
	afx_msg void OnButClear();
	virtual void OnCancel();
	afx_msg void OnSelchangeComboNames();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	PICFILES pics_db_;
	CString cur_path_;
	CString cur_sel_name_;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_JOINT_DB_EDIT_H__2EA0FE9D_27EF_4D7E_96F5_497456C8C313__INCLUDED_)
