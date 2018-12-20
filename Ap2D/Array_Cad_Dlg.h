#if !defined(AFX_ARRAY_CAD_DLG_H__84493BE2_EF99_4BD4_84EB_1289E16C2089__INCLUDED_)
#define AFX_ARRAY_CAD_DLG_H__84493BE2_EF99_4BD4_84EB_1289E16C2089__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Array_Cad_Dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Array_Cad_Dlg dialog

#include "../Display/Entity_Array.h"
#include "counter.h"
class Array_Cad_Dlg : public CDialog
{
// Construction
public:
	Array_Cad_Dlg(CWnd* pParent = NULL);   // standard constructor

	dlhml::Entity_Array ary;

// Dialog Data
	//{{AFX_DATA(Array_Cad_Dlg)
	enum { IDD = ID_ARRAY_CAD };
	double	degree_;
	double	col_dis_;
	int		col_num_;
	double	row_dis_;
	int		row_num_;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Array_Cad_Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Array_Cad_Dlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	MCT_DEF
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARRAY_CAD_DLG_H__84493BE2_EF99_4BD4_84EB_1289E16C2089__INCLUDED_)
