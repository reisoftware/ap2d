// PutBar.h: interface for the CPutBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUTBAR_H__2FA30A62_63E6_4E10_830C_2064A4ED00AB__INCLUDED_)
#define AFX_PUTBAR_H__2FA30A62_63E6_4E10_830C_2064A4ED00AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "InEdit.h"
#include "sizecbar.h" 

#ifndef baseBar
#define baseBar CGoodBar	//Option: CGoodBar or CBetterBar
#endif


class CPutBar : public baseBar
{
public:
	CPutBar();
	virtual ~CPutBar();

	void create_edit();
	CEdit* get_in();
	CEdit* get_out();
protected:
	InEdit in_;
	CEdit out_;
	CEdit tip_;


	// Generated message map functions
protected:
	//{{AFX_MSG(CMyBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_PUTBAR_H__2FA30A62_63E6_4E10_830C_2064A4ED00AB__INCLUDED_)
