// Left_Mgr.h: interface for the Left_Mgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEFT_MGR_H__F78A006C_4894_48AC_A8EA_3631FCC71E9E__INCLUDED_)
#define AFX_LEFT_MGR_H__F78A006C_4894_48AC_A8EA_3631FCC71E9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STATUS_EDIT	0 
#define STATUS_CHANGE		1
#define STATUS_COMPLATE	2 
#define STATUS_ERROR	3 



#include "sizecbar.h"
#include "View_Tree.h"
#include "TabCtrl_Left.h"
#include "Ex_ListCtrl_Sort.h"
#include "Mgr_Database.h"
#include <vector>

class save_file  
{
public:
	save_file();
	virtual ~save_file();
	int file_status_;
	CString file_name_;

};
typedef std::vector<save_file> save_files;

class Left_Mgr : public CBetterBar  
{
public:
	Left_Mgr();
	virtual ~Left_Mgr();
	
	void load_tree(std::string dir_path);
	void download_tree();
	void upload_tree();

	void update_tree();
	void set_complate();
	View_Tree tree_;
	
	void load_tree_file(std::string dir_path);

	void show_reports(Group_Txts &group_txts);
	void show_same_reports(Group_Txts &group_txts);

	void deal_files_Data();
	void save_file_fun();
	int get_pos();
	CString save_as_cur_view(int );
	void init_tree_sel(int);
	void travel_tree_node(HTREEITEM,int,CString & );
	void 	deal_floder(CString filename,int file_status,HTREEITEM hCountry);
	void get_tree_all_path(HTREEITEM item,CString & FileName);
	void set_error();
	void clear_status();
	void message();
private:
	TabCtrl_Left tab_ctrl_;
	ListCtrl_Sort list_ctrl_;
	ListCtrl_Sort same_list_ctrl_;

	CImageList images_;

	void create_list_page();
	
	void create_views_page();
	void create_same_list_page();
	void create_tree_by_dxf_new(std::string dir_path,strings &files);
	void create_tree_by_dxf(std::string dir_path,strings &files);
	

protected:
	//{{AFX_MSG(CMyBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDblclkTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenuImportDxf();
	afx_msg void OnClickTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenuSetComplate();
	afx_msg void OnDblclkLists(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListSames(NMHDR* pNMHDR, LRESULT* pResult);
	//afx_msg void OnDbclickTree(NMHDR* pNMHDR, LRESULT* pResult);
	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	save_files files_db_;
	CString file_path_;
};

#endif // !defined(AFX_LEFT_MGR_H__F78A006C_4894_48AC_A8EA_3631FCC71E9E__INCLUDED_)
