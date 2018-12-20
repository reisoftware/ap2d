#if !defined(AFX_VIEW_TREE_H__D05820E6_0938_4787_ADC9_A00C10C13A5D__INCLUDED_)
#define AFX_VIEW_TREE_H__D05820E6_0938_4787_ADC9_A00C10C13A5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// View_Tree.h : header file
//
#pragma warning (disable : 4786)

#include "Ap2D.h"
/////////////////////////////////////////////////////////////////////////////
// View_Tree window

class View_Tree : public CTreeCtrl
{
// Construction
public:
	View_Tree();

// Attributes
public:

	void get_parents(HTREEITEM cur,strings &parents);
	HTREEITEM get_item(std::string name);
	void create_paths(strings &all_paths);

	void expand_nodes(HTREEITEM root, BOOL expand,std::string &path);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(View_Tree)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~View_Tree();

	// Generated message map functions
private:
	void selected(CString &cur,CString &parent);
	HTREEITEM begin();
	HTREEITEM end();
	HTREEITEM next(HTREEITEM item);
	HTREEITEM get_next_item(HTREEITEM item);
	HTREEITEM get_uncle_item(HTREEITEM item);
	void travel_tree(HTREEITEM hItem, UINT  nState,std::string &path);

	strings all_paths_;	
protected:
	//{{AFX_MSG(View_Tree)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEW_TREE_H__D05820E6_0938_4787_ADC9_A00C10C13A5D__INCLUDED_)
